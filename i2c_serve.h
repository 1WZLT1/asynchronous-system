#ifndef __i2c_serve_h
#define __i2c_serve_h

#include "stdint.h"
#include "string.h"
#include "wk_dma.h"
#include "rtthread.h"
#include "at32f435_437_int.h"

#include "LIS2MDL.h"

#define BIT(n)            (1UL << (n))
#define I2C_MSG_WRITE			(0U << 0U)
#define I2C_MSG_READ			 BIT(0)
#define I2C_MSG_RW_MASK		 BIT(0)
#define I2C_MSG_STOP			 BIT(1)
#define I2C_MSG_RESTART		 BIT(2)

typedef struct 
{
    void*               dev;      
		dma_channel_type*   I2C_DMA_Transmit_Channel;
	  dma_channel_type*   I2C_DMA_Receive_Channel;
		struct rt_semaphore i2c_wait_sem_stopf;
		struct rt_semaphore i2c_wait_sem_tdf;
		uint8_t		          flags;
		uint8_t             stop_bit;
    uint8_t             initialized;
}i2c_dev_t;

typedef struct 
{
	uint8_t		*buf;
	uint32_t	len;
	uint8_t		flags;
}i2c_msg_t;

typedef enum {
    I2C_WAIT_RESTART,   // 当前段结束后还要 repeated start
    I2C_WAIT_STOP,       // 当前段就是最后一段
		I2C_WAIT_BUSYF
} i2c_wait_mode_t;

extern i2c_dev_t i2c_dev1;
extern i2c_dev_t i2c_dev2;

int i2c_write_read(i2c_dev_t *dev,uint8_t *txbuf,uint32_t txlen,uint8_t *rxbuf,uint32_t rxlen, uint16_t saddr);
int i2c_write(i2c_dev_t *dev,uint8_t *buf,uint32_t num_bytes, uint16_t saddr);
#endif

