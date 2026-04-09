#include "qmc6309.h"
#include "i2c_serve.h"
#include "rtio.h"

#define QMC6309_Saddr 0x7C
#define QMC6309_ID    0x90

#define QMC6309_Scale 0.0010

QMC6309_Status_Type QMC6309;

uint8_t QMC6309_Init_ok = 0;

uint8_t who_am_i = 0;
void QMC6309_who_am_i()
{
	uint8_t who_am_i_reg = 0x00;
	i2c_write_read(&i2c_dev2,&who_am_i_reg,1,&who_am_i, 1,QMC6309_Saddr);
}

void QMC6309_mode_config()
{
	uint8_t mode_config_reg[2] = {0x0A,0xFB};//配置为continue mode osr1 = 1 osr2 = 111为了滤波项拉到最小
	uint8_t mode_config        = 0;
	i2c_write(&i2c_dev2,mode_config_reg,2,QMC6309_Saddr);
	i2c_write_read(&i2c_dev2,&mode_config_reg[0],1,&mode_config,1,QMC6309_Saddr);
}

void QMC6309_set_reset_mode_config()
{
	uint8_t set_reset_mode_config_reg[2] = {0x0B,0x00};
	uint8_t set_reset_mode_config        = 0;
	
	i2c_write_read(&i2c_dev2,&set_reset_mode_config_reg[0],1,&set_reset_mode_config,1,QMC6309_Saddr);
	set_reset_mode_config &= ~(0x03);
	
	set_reset_mode_config_reg[1] = set_reset_mode_config; 
	i2c_write(&i2c_dev2,set_reset_mode_config_reg,2,QMC6309_Saddr);
	i2c_write_read(&i2c_dev2,&set_reset_mode_config_reg[0],1,&set_reset_mode_config,1,QMC6309_Saddr);
}

void QMC6309_range_config()
{
	uint8_t range_reg[2] = {0x0B,0x00};
	uint8_t range_config  = 0;
	
	i2c_write_read(&i2c_dev2,&range_reg[0],1,&range_config,1,QMC6309_Saddr);
	range_config &= ~(0x03 << 2);
	
	range_reg[1] = range_config;
	i2c_write(&i2c_dev2,range_reg,2,QMC6309_Saddr);
	i2c_write_read(&i2c_dev2,&range_reg[0],1,&range_config,1,QMC6309_Saddr);
}

void QMC6309_odr_config()
{
	uint8_t odr_reg[2] = {0x0B,0x00};
	uint8_t odr_config  = 0;
	
	i2c_write_read(&i2c_dev2,&odr_reg[0],1,&odr_config,1,QMC6309_Saddr);
	odr_config |= 0x04 << 4;
	
	odr_reg[1] = odr_config;
	i2c_write(&i2c_dev2,odr_reg,2,QMC6309_Saddr);
	i2c_write_read(&i2c_dev2,&odr_reg[0],1,&odr_config,1,QMC6309_Saddr);
}

uint8_t OMC6309_Data_Receive[6];
void QMC6309_transmit(rtio_t *rtio,rtio_node_t *node)
{
	node->Device_Name = QMC6309_E;
	uint8_t data_read_reg = 0x01;
	i2c_write_read(&i2c_dev2,&data_read_reg,1,OMC6309_Data_Receive,6,QMC6309_Saddr);
}

void QMC6309_callback(rtio_t *rtio)
{
	rtio_node_t *node;
  rt_base_t level;	
	
	node = rtio_acquire(rtio);
  if (node == RT_NULL)
  {
      return;
  }
	
  node->dev = QMC6309_transmit;
  node->op  = 0;
	rtio_submit_sq(rtio, node);
	
	rt_mb_send(sensor_sqe_mb, (rt_ubase_t)rtio);
}

static inline int16_t QMC6309_GetS16(const uint8_t *p)
{
    return (int16_t)(((uint16_t)p[1] << 8) | p[0]);
}

uint64_t last_us_1 = 0,now_us_1 = 0,Interval_us_1 = 0;
void QMC6309_Conversion(uint8_t *Data_Receive)
{
	now_us_1 = Micros();
	Interval_us_1 = now_us_1 -  last_us_1;
	QMC6309.Mags[0] = QMC6309_GetS16(&Data_Receive[0]) * QMC6309_Scale;
	QMC6309.Mags[1] = QMC6309_GetS16(&Data_Receive[2]) * QMC6309_Scale;
	QMC6309.Mags[2] = QMC6309_GetS16(&Data_Receive[4]) * QMC6309_Scale;
	
	RawBuffer_Input(&QMC6309.BufMagX,  QMC6309.Mags[0]);
  RawBuffer_Input(&QMC6309.BufMagY,  QMC6309.Mags[1]);
  RawBuffer_Input(&QMC6309.BufMagZ,  QMC6309.Mags[2]);
	
	last_us_1 = Micros();
}

void QMC6309_Init()
{
	QMC6309_who_am_i();
	if(who_am_i != QMC6309_ID)return;
	QMC6309_mode_config();
	QMC6309_set_reset_mode_config();
	QMC6309_range_config();
	QMC6309_odr_config();
	QMC6309_Init_ok = 1;
}
