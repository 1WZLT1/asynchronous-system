#ifndef __flash_serve_h
#define __flash_serve_h

#include "fdi_parame.h"
#include "params.h"
#include "use_fdilink.h"
#include "flash.h"

#define Default_Press 1
#define Write_Press   2

/**************************************************flash_external_interface*****************************************/
typedef struct
{
	uint32_t flash_last_address;
}flash_serve_box_t;

void fdi_parame_init(void);
void SRAM_To_Flash(uint8_t Mode);
/*******************************************************************************************************************/
extern uint32_t fdi_sram_crc;
#endif

