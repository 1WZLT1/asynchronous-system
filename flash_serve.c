#include "flash_serve.h"
#include "params.h"
#include <string.h>

/**************************************************flash_external_interface*****************************************/
flash_serve_box_t flash_serve_box;
/******************************************************************************************************************/

/**************************************************flash_internal_interface****************************************/
__attribute__((section("fdi_param_len"),used)) \
uint32_t fdi_sram_len = 0;
__attribute__((section("fdi_param_crc"),used)) \
uint32_t fdi_sram_crc = 0;
__attribute__((section("fdi_flash_param_len"),used)) \
uint32_t flash_flash_len;
__attribute__((section("fdi_flash_param_crc"),used)) \
uint32_t flash_flash_crc;

/*
 * @brief   SRAM To Flash function
 * @param   none
 * @explain 
 */
void SRAM_To_Flash(uint8_t Mode)
{
	uint32_t FDI_FLASH_BASE     = FDI_FLASH_PARAME_BASE;
	uint32_t FDI_SRAM_LOAD_BASE = 0;
	
			 if(Mode == Default_Press) FDI_SRAM_LOAD_BASE = (uint32_t)&Load$$FDI_PARAME$$Base;
	else if(Mode == Write_Press  ) FDI_SRAM_LOAD_BASE = (uint32_t)&Image$$FDI_PARAME$$Base;
	
	flash.flash_lock_config.func.flash_unlock();
	flash.flash_erase.func.flash_sector_erase(FDI_FLASH_PARAME_BASE - 0x08);
	for(int i = 0;i < fdi_sram_len;i++)
	{
			flash.flash_program.func.flash_byte_program(FDI_FLASH_BASE,(*(uint8_t *)FDI_SRAM_LOAD_BASE));
			FDI_FLASH_BASE 		 += sizeof(uint8_t);
			FDI_SRAM_LOAD_BASE += sizeof(uint8_t);
	}
	flash_serve_box.flash_last_address = FDI_FLASH_BASE;
	flash.flash_program.func.flash_word_program(FDI_FLASH_PARAME_BASE - 0x08 , fdi_sram_len);
	flash.flash_program.func.flash_word_program(FDI_FLASH_PARAME_BASE - 0x04 , fdi_sram_crc);
	flash.flash_lock_config.func.flash_lock();
}

void Flash_To_SRAM()
{
	/*一致就把flash的值丢到load*/
		memcpy((void *)&Image$$FDI_PARAME$$Base,
					 (const void *)FDI_FLASH_PARAME_BASE,
						fdi_sram_len);
}

uint32_t address_t;
void fdi_parame_init()
{
	address_t = (uint32_t)&IMU_TEMP0;
	fdi_sram_len = (uint32_t)&PARAM_END - FDI_SRAM_PARAME_BASE; 
	fdi_sram_crc = FDI_StringGetCRC32();
	/*先load区取长度给fdi_param_len赋值*/

	/*get flash段的fdi_flash_param_len是否有值*/
	if(flash_flash_len == 0xFFFFFFFF)
	{
			/*把sram load段的数据赋值到 扇区511*/
			SRAM_To_Flash(Write_Press);
	}
	else
	{
		/*不为空*/
		/*读值看一下0x080FF804是不是默认值*/
		if(*((uint32_t*)FDI_FLASH_PARAME_BASE) == 0xFFFFFFFF)
		{
				/*是就清除*/
				flash.flash_lock_config.func.flash_unlock();
			  flash.flash_erase.func.flash_sector_erase(flash.flash_adderess_get.func.sector_address_get(511));
				flash.flash_lock_config.func.flash_bank1_lock();
		}
		else 
		{		
				/*不是就比较长度*/
				if(fdi_sram_crc == flash_flash_crc)
					Flash_To_SRAM();
				else
					SRAM_To_Flash(Default_Press);
		}
	}
}
/******************************************************************************************************************/

