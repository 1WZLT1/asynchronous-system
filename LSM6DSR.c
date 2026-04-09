#include "LSM6DSR.h"

#include "spi_serve.h"
#include "at32f435_437_gpio.h"
#include "at32f435_437_int.h" 
#include "rtio.h"
#include "rtthread.h"

#define LSM6DSR_Transmit_DMA         DMA1_CHANNEL6
#define LSM6DSR_Receive_DMA          DMA1_CHANNEL5
#define Device                       SPI1 

static uint8_t whoamI;
static int8_t LSM6DSR_Initial = 0;
LSM6DSR_Status_Type LSM6DSR;

uint8_t LSM6DR_Data_Transmit[15];
uint8_t LSM6DR_Data_Receive[15];
void LSM6DSR_transmit(rtio_t *rtio,rtio_node_t *node)
{
		rt_memset(&LSM6DR_Data_Transmit,0,sizeof(LSM6DR_Data_Transmit));
		node->Device_Name = LSM6DSR_E;
	
		LSM6DR_Data_Transmit[0] = 0x20 | 0x80;
		LSM6DSR_CS_enable;
	
		SPI_TransmitReceive_DMA(LSM6DSR_Transmit_DMA,\
														LSM6DSR_Receive_DMA,\
														(uint32_t)&Device->dt,\
														(uint32_t)&LSM6DR_Data_Transmit,\
														(uint32_t)&LSM6DR_Data_Receive,\
														15
														);
}

static inline int16_t LSM6DSR_GetS16(const uint8_t *p)
{
    return (int16_t)(((uint16_t)p[2] << 8) | p[1]);
}

uint64_t last_us = 0,now_us = 0,Interval_us = 0;

void LSM6DSR_Conversion(uint8_t *Data_Receive)
{
	now_us = Micros();
	Interval_us = now_us -  last_us;
  LSM6DSR.Temp     = 25.0f     + (LSM6DSR_GetS16(&Data_Receive[0]) / 256.0f);
  LSM6DSR.Accs[0]  = AccScale  *  LSM6DSR_GetS16(&Data_Receive[8]);
  LSM6DSR.Accs[1]  = AccScale  *  LSM6DSR_GetS16(&Data_Receive[10]);
  LSM6DSR.Accs[2]  = AccScale  *  LSM6DSR_GetS16(&Data_Receive[12]);

  LSM6DSR.Gyros[0] = GyroScale *  LSM6DSR_GetS16(&Data_Receive[2]);
  LSM6DSR.Gyros[1] = GyroScale *  LSM6DSR_GetS16(&Data_Receive[4]);
  LSM6DSR.Gyros[2] = GyroScale *  LSM6DSR_GetS16(&Data_Receive[6]);

  RawBuffer_Input(&LSM6DSR.BufAccX,  LSM6DSR.Accs[0]);
  RawBuffer_Input(&LSM6DSR.BufAccY,  LSM6DSR.Accs[1]);
  RawBuffer_Input(&LSM6DSR.BufAccZ,  LSM6DSR.Accs[2]);

  RawBuffer_Input(&LSM6DSR.BufGyroX, LSM6DSR.Gyros[0]);
  RawBuffer_Input(&LSM6DSR.BufGyroY, LSM6DSR.Gyros[1]);
  RawBuffer_Input(&LSM6DSR.BufGyroZ, LSM6DSR.Gyros[2]);

  RawBuffer_Input(&LSM6DSR.BufTemp,  LSM6DSR.Temp);
	last_us = now_us;
}

int LSM6DSR_Decode(LSM6DSR_Status_Type* LSM6DSR)
{
//	LSM6DSR->lastUpdate = Micros(); 
	int primask = __get_PRIMASK();
	__set_PRIMASK(1);
	LSM6DSR->Accs[0] = RawBuffer_Output(&LSM6DSR->BufAccX);
	LSM6DSR->Accs[1] = RawBuffer_Output(&LSM6DSR->BufAccY);
	LSM6DSR->Accs[2] = RawBuffer_Output(&LSM6DSR->BufAccZ);
	LSM6DSR->Gyros[0] = RawBuffer_Output(&LSM6DSR->BufGyroX);
	LSM6DSR->Gyros[1] = RawBuffer_Output(&LSM6DSR->BufGyroY);
	LSM6DSR->Gyros[2] = RawBuffer_Output(&LSM6DSR->BufGyroZ);
	LSM6DSR->Temp = RawBuffer_Output(&LSM6DSR->BufTemp);
	
	if(LSM6DSR_Initial)
	{
		LSM6DSR->AccsValid[0] = LSM6DSR->BufAccX.repeat_count < 50;
		LSM6DSR->AccsValid[1] = LSM6DSR->BufAccY.repeat_count < 50;
		LSM6DSR->AccsValid[2] = LSM6DSR->BufAccZ.repeat_count < 50;
		LSM6DSR->GyrosValid[0] = LSM6DSR->BufGyroX.repeat_count < 50;
		LSM6DSR->GyrosValid[1] = LSM6DSR->BufGyroY.repeat_count < 50;
		LSM6DSR->GyrosValid[2] = LSM6DSR->BufGyroZ.repeat_count < 50;
		LSM6DSR->TempValid = LSM6DSR->BufTemp.repeat_count < 50;
	}
	else
	{
		LSM6DSR->AccsValid[0] = 0;
		LSM6DSR->AccsValid[1] = 0;
		LSM6DSR->AccsValid[2] = 0;
		LSM6DSR->GyrosValid[0] = 0;
		LSM6DSR->GyrosValid[1] = 0;
		LSM6DSR->GyrosValid[2] = 0;
		LSM6DSR->TempValid = 0;
	}
	__set_PRIMASK(primask);
	return 0;
}

void LSM6DSR_callback(rtio_t *rtio)
{
  rtio_node_t *node;
  rt_base_t level;
  rt_bool_t need_wakeup = RT_FALSE;

  node = rtio_acquire(rtio);
  if (node == RT_NULL)
  {
      return;
  }

  node->dev = LSM6DSR_transmit;
  node->op  = 0;

  rtio_submit_sq(rtio, node);

	rt_mb_send(sensor_sqe_mb, (rt_ubase_t)rtio);
}

uint8_t LSM6DR_transmit_buffer[2] = {0};
uint8_t LSM6DR_receive_buffer[2]  = {0};
void LSM6DR_Write_Reg(uint8_t  reg,\
											uint8_t  data,\
											uint16_t len)
{
		LSM6DR_transmit_buffer[0] = reg & 0x7f;
		LSM6DR_transmit_buffer[1] = data;
	
		LSM6DSR_CS_enable;
	
		SPI_TransmitReceive_DMA(LSM6DSR_Transmit_DMA,\
														LSM6DSR_Receive_DMA,\
														(uint32_t)&Device->dt,\
														(uint32_t)&LSM6DR_transmit_buffer,\
														(uint32_t)&LSM6DR_receive_buffer,\
														len
														);
		while(SPI1->sts_bit.bf == 1){}
		LSM6DSR_CS_disenable;
}

void LSM6DR_Read_Reg(uint8_t  reg,\
										 uint8_t  *data,\
										 uint16_t len)
{
		LSM6DR_transmit_buffer[0] = reg | 0x80;
		LSM6DR_transmit_buffer[1] = 0x00;
	
		LSM6DSR_CS_enable;
		SPI_TransmitReceive_DMA(LSM6DSR_Transmit_DMA,\
														LSM6DSR_Receive_DMA,\
														(uint32_t)&Device->dt,\
														(uint32_t)&LSM6DR_transmit_buffer,\
														(uint32_t)&LSM6DR_receive_buffer,\
														len
														);
		while(SPI1->sts_bit.bf == 1){}
		LSM6DSR_CS_disenable;
			
		*data = LSM6DR_receive_buffer[1];
}

void LSM6DSR_I3C_Disable()
{
	uint8_t CTRL9_Register;
	LSM6DR_Read_Reg(LSM6DSR_CTRL9_XL,&CTRL9_Register,2);
	CTRL9_Register |= (0x01 << 1);
	LSM6DR_Write_Reg(LSM6DSR_CTRL9_XL,CTRL9_Register,2);
}

void LSM6DR_Updata()
{
	uint8_t CTRL3_Register;
	LSM6DR_Read_Reg(LSM6DSR_CTRL3_C,&CTRL3_Register,2);	
	CTRL3_Register |= (0x01<<6);
	LSM6DR_Write_Reg(LSM6DSR_CTRL3_C,CTRL3_Register,2);
}

void LSM6DR_SPI4Write()
{
	uint8_t CTRL3_Register;
	LSM6DR_Read_Reg(LSM6DSR_CTRL3_C,&CTRL3_Register,2);	
	CTRL3_Register &= ~(0x01 << 3);
	LSM6DR_Write_Reg(LSM6DSR_CTRL3_C,CTRL3_Register,2);
}

void LSM6DR_INT1_DRDY()
{
	uint8_t CTRL3_Register;
	LSM6DR_Read_Reg(LSM6DSR_CTRL3_C,&CTRL3_Register,2);	
	CTRL3_Register &= ~(0x01<<4);//推挽
	CTRL3_Register &= ~(0x01<<5);//有效高
	CTRL3_Register |=  (0x01<<2);//连续
	LSM6DR_Write_Reg(LSM6DSR_CTRL3_C,CTRL3_Register,2);
	
	uint8_t INT1_CTRL_Register;
	LSM6DR_Read_Reg(LSM6DSR_INT1_CTRL,&INT1_CTRL_Register,2);	
	#if(1)
	INT1_CTRL_Register = (0x01);
	#else
	INT1_CTRL_Register = (0x01 << 7);
	#endif
	LSM6DR_Write_Reg(LSM6DSR_INT1_CTRL,INT1_CTRL_Register,2);
	LSM6DR_Read_Reg(LSM6DSR_INT1_CTRL,&INT1_CTRL_Register,2);	
	
	uint8_t COUNTER_BDR_Register;
	LSM6DR_Read_Reg(LSM6DSR_COUNTER_BDR_REG1,&COUNTER_BDR_Register,2);	
	COUNTER_BDR_Register |= 0x01 <<7;
	LSM6DR_Write_Reg(LSM6DSR_COUNTER_BDR_REG1,COUNTER_BDR_Register,2);
}

void LM6DR_DEN_DRDY()
{
	#if(1)
	{
		uint8_t CTRL6_Register;
		LSM6DR_Read_Reg(LSM6DSR_CTRL6_C,&CTRL6_Register,2);	
		CTRL6_Register &= ~(0x01 << 5);
		CTRL6_Register &= ~(0x01 << 6);
		CTRL6_Register &= ~(0x01 << 7);
		LSM6DR_Write_Reg(LSM6DSR_CTRL6_C,CTRL6_Register,2);
	}
	#else 
	{
		uint8_t CTRL6_Register;
		LSM6DR_Read_Reg(LSM6DSR_CTRL6_C,&CTRL6_Register,2);	
		CTRL6_Register &= ~(0x01 << 7);   // TRIG_EN = 0
		CTRL6_Register |=  (0x01 << 6);   // LVL1_EN = 1
		CTRL6_Register |=  (0x01 << 5);   // LVL2_EN = 1
		LSM6DR_Write_Reg(LSM6DSR_CTRL6_C,CTRL6_Register,2);
		
		uint8_t CTRL9_Register;
		LSM6DR_Read_Reg(LSM6DSR_CTRL9_XL,&CTRL9_Register,2);
		CTRL9_Register |= (0x01 << 1);
		CTRL9_Register |= (0x01 << 2);	
		CTRL9_Register |= (0x01 << 3);	
		CTRL9_Register |= (0x01 << 4);			
		LSM6DR_Write_Reg(LSM6DSR_CTRL9_XL,CTRL9_Register,2);
	}
	#endif
}

void LM6DR_RANGE_CONFIG()
{
	uint8_t CTRL2_XL_Register;
	LSM6DR_Read_Reg(LSM6DSR_CTRL1_XL,&CTRL2_XL_Register,2);
	CTRL2_XL_Register &= ~(0x03 << 2);
	CTRL2_XL_Register |=  (0x03 << 2);//8g
	LSM6DR_Write_Reg(LSM6DSR_CTRL1_XL,CTRL2_XL_Register,2);
	
	uint8_t CTRL2_G_Register;
	LSM6DR_Read_Reg(LSM6DSR_CTRL2_G,&CTRL2_G_Register,2);	
	CTRL2_G_Register &= ~((0x3 << 2) | (1 << 1) | (1 << 0));
	CTRL2_G_Register |=  (0x03 << 2);//2000dps
	LSM6DR_Write_Reg(LSM6DSR_CTRL2_G,CTRL2_G_Register,2);
}

void LM6DR_FREQ_CONFIG(void)
{
    uint8_t CTRL1_XL_Register;
	  uint8_t CTRL2_G_Register;

		#if(1)
    LSM6DR_Read_Reg(LSM6DSR_CTRL1_XL, &CTRL1_XL_Register, 2);
    CTRL1_XL_Register &= ~(0xF << 4);
    CTRL1_XL_Register |=  (0x8 << 4);
    LSM6DR_Write_Reg(LSM6DSR_CTRL1_XL, CTRL1_XL_Register, 2);

    LSM6DR_Read_Reg(LSM6DSR_CTRL2_G, &CTRL2_G_Register, 2);
    CTRL2_G_Register &= ~(0xF << 4);
    CTRL2_G_Register |=  (0x8 << 4);
    LSM6DR_Write_Reg(LSM6DSR_CTRL2_G, CTRL2_G_Register, 2);
		#else
		LSM6DR_Read_Reg(LSM6DSR_CTRL1_XL, &CTRL1_XL_Register, 2);
    CTRL1_XL_Register &= ~(0xF << 4);//3.33k
    CTRL1_XL_Register |=  (0x9 << 4);
    LSM6DR_Write_Reg(LSM6DSR_CTRL1_XL, CTRL1_XL_Register, 2);

    LSM6DR_Read_Reg(LSM6DSR_CTRL2_G, &CTRL2_G_Register, 2);
    CTRL2_G_Register &= ~(0xF << 4);
    CTRL2_G_Register |=  (0x9 << 4);
    LSM6DR_Write_Reg(LSM6DSR_CTRL2_G, CTRL2_G_Register, 2);
		#endif
}

void LSM6DR_ACC_LPF_CONFIG()
{
	uint8_t CTRL6_Register;
	LSM6DR_Read_Reg(LSM6DSR_CTRL6_C,&CTRL6_Register,2);	
	CTRL6_Register &= ~(0x01 << 4);//开启动高性能
	LSM6DR_Write_Reg(LSM6DSR_CTRL6_C,CTRL6_Register,2);
	
	uint8_t CTRL1_XL_Register;
	LSM6DR_Read_Reg(LSM6DSR_CTRL1_XL, &CTRL1_XL_Register, 2);
	CTRL1_XL_Register &= ~(0x01<<1);//不开启LPF2
	LSM6DR_Write_Reg(LSM6DSR_CTRL1_XL, CTRL1_XL_Register, 2);
	
	uint8_t CTRL8_XL_Register;
	LSM6DR_Read_Reg(LSM6DSR_CTRL8_XL,&CTRL8_XL_Register,2);
	/*关闭高通相关*/
	CTRL8_XL_Register &= ~(0x01 << 2);
	CTRL8_XL_Register &= ~(0x01 << 3);
	CTRL8_XL_Register &= ~(0x01 << 4);
	
	CTRL8_XL_Register &= ~(0xE0); 
	LSM6DR_Write_Reg(LSM6DSR_CTRL8_XL,CTRL8_XL_Register,2);
}

void LSM6DR_GYRO_LPF_CONFIG()
{
	uint8_t CTRL4_Register;
	LSM6DR_Read_Reg(LSM6DSR_CTRL4_C,&CTRL4_Register,2);	
	CTRL4_Register &= ~(0x01 << 1);//关闭陀螺低通
	LSM6DR_Write_Reg(LSM6DSR_CTRL4_C,CTRL4_Register,2);
}

void LSM6DSR_Init()
{
	LSM6DR_Write_Reg(LSM6DSR_CTRL3_C,0x01,2);//rest
	LSM6DR_Read_Reg(LSM6DSR_WHO_AM_I,&whoamI,2);
	if(whoamI != LSM6DSR_ID)return;
	LSM6DSR_I3C_Disable();
	LSM6DR_SPI4Write();
	LSM6DR_Updata();
	LSM6DR_INT1_DRDY();
	LM6DR_DEN_DRDY();
	LM6DR_RANGE_CONFIG();
	LM6DR_FREQ_CONFIG();
	LSM6DR_ACC_LPF_CONFIG();
	LSM6DR_GYRO_LPF_CONFIG();
	LSM6DSR_Initial = 1;
}
