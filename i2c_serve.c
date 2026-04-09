#include "i2c_serve.h"
#include "rthw.h"
#include "at32f435_437_int.h"

#define OPERATION(msg) (((i2c_msg_t *) msg)->flags & I2C_MSG_RW_MASK)

i2c_dev_t i2c_dev1;
i2c_dev_t i2c_dev2;

int i2c_time_out(i2c_dev_t *dev, i2c_wait_mode_t mode)
{
	if(dev == NULL)return -2;
	i2c_type* i2c_dev = (i2c_type *)dev->dev;
	if(i2c_dev == NULL)return -2;
	
	uint64_t insert_time = Micros();
	while(1)
	{
		if(Micros() - insert_time > 25000)
		{
			return -1;
		}
		
		if(mode == I2C_WAIT_BUSYF)
		{
			if(i2c_dev->sts_bit.busyf == 0)return 0;
		}
		else if(mode == I2C_WAIT_RESTART)
		{
			if(i2c_dev->sts_bit.tdc == 1)return 0;
		}
		else if(mode == I2C_WAIT_STOP)
		{
			if(i2c_dev->sts_bit.stopf == 1 || dev->stop_bit == 1)
			{
				dev->stop_bit          = 0;
				i2c_dev->clr_bit.stopc = 1;
				return 0;
			}
		}
	}
}

int i2c_time_out_thread(i2c_dev_t *dev, i2c_wait_mode_t mode)
{
	if(dev == NULL)return -2;
	i2c_type* i2c_dev = (i2c_type *)dev->dev;
	if(i2c_dev == NULL)return -2;
	
	uint64_t insert_time = Micros();
	if(mode == I2C_WAIT_BUSYF)
	{
		while(1)
		{
			if(Micros() - insert_time > 25000)
			{
				return -1;
			}

			if(i2c_dev->sts_bit.busyf == 0)return 0;
		}	
	}
	else 
	{
		rt_tick_t timeout = rt_tick_from_millisecond(25);
		if(mode == I2C_WAIT_STOP)
		{
			if (rt_sem_take(&dev->i2c_wait_sem_stopf, timeout) != RT_EOK)
			{
				return -1;
			}
		}
		else if(mode == I2C_WAIT_RESTART)
		{
			if (rt_sem_take(&dev->i2c_wait_sem_tdf, timeout) != RT_EOK)
			{
				return -1;
			}
		}
	}
	return 0;
}

inline rt_bool_t i2c_can_thread_wait(void)
{
    if (rt_interrupt_get_nest() != 0) return RT_FALSE;  // 在中断里，不能阻塞等
    if (rt_thread_self() == RT_NULL)  return RT_FALSE;  // 调度器还没起来
    return RT_TRUE;
}

extern uint8_t all_init;
static int i2c_wait_auto(i2c_dev_t *dev, i2c_wait_mode_t mode)
{
    if (i2c_can_thread_wait() && all_init == 1)
        return i2c_time_out_thread(dev, mode);
    else
        return i2c_time_out(dev, mode);
}

int i2c_at32_msg_write(i2c_dev_t *dev,i2c_msg_t *msgs,uint16_t saddr)
{
	if(msgs == NULL || dev == NULL || dev->dev == NULL)return -2;
	if (msgs->buf == NULL || msgs->len == 0) return -2;
	
	i2c_type* i2c_dev = (i2c_type *)dev->dev;
	if(i2c_dev == NULL)return -2;
	
	dev->flags = msgs->flags;
	
	if(!(msgs->flags & I2C_MSG_RESTART))//不是restart
	{	
		if(i2c_time_out(dev,I2C_WAIT_BUSYF) < 0)
		{
			return -1;
		}			
	}
	
	i2c_dev->ctrl2_bit.saddr    = saddr << 1;
	i2c_dev->ctrl2_bit.cnt      = msgs->len;
	i2c_dev->ctrl2_bit.dir      = I2C_DIR_TRANSMIT;
	i2c_dev->ctrl2_bit.astopen  = (msgs->flags & I2C_MSG_STOP) ? 1 : 0;   
	
	if(!i2c_dev->ctrl2_bit.astopen)i2c_interrupt_enable(i2c_dev,I2C_TDC_INT,TRUE);
	
	if(dev->I2C_DMA_Transmit_Channel == NULL)return -2;
	wk_dma_channel_config(dev->I2C_DMA_Transmit_Channel, 
											  (uint32_t)&i2c_dev->txdt, 
											  (uint32_t)msgs->buf, 
											   msgs->len);

	i2c_dma_enable(dev->dev, I2C_DMA_REQUEST_TX, TRUE);
	dma_channel_enable(dev->I2C_DMA_Transmit_Channel,TRUE);
	
	i2c_dev->ctrl2_bit.genstart = 1; 
	if(msgs->flags & I2C_MSG_STOP)
	{
		if(i2c_wait_auto(dev,I2C_WAIT_STOP) < 0)
		{
			i2c_interrupt_enable(i2c_dev,I2C_TDC_INT,FALSE);
			dma_channel_enable(dev->I2C_DMA_Transmit_Channel,FALSE);
			return -1;
		}
	}
	else 
	{
		if(i2c_wait_auto(dev,I2C_WAIT_RESTART) < 0)
		{
			i2c_interrupt_enable(i2c_dev,I2C_TDC_INT,FALSE);
			dma_channel_enable(dev->I2C_DMA_Transmit_Channel,FALSE);
			return -1;
		}
	}
	i2c_interrupt_enable(i2c_dev,I2C_TDC_INT,FALSE);
	dma_channel_enable(dev->I2C_DMA_Transmit_Channel,FALSE);
	return 0;
}

int i2c_at32_msg_read(i2c_dev_t *dev,i2c_msg_t *msgs,uint16_t saddr)
{
	if(msgs == NULL || dev == NULL || dev->dev == NULL)return -2;
	if (msgs->buf == NULL || msgs->len == 0) return -2;
	
	i2c_type* i2c_dev = (i2c_type *)dev->dev;
	if(i2c_dev == NULL)return -2;
	
	dev->flags = msgs->flags;
	
	if(!(msgs->flags & I2C_MSG_RESTART))
	{	
		if(i2c_time_out(dev,I2C_WAIT_BUSYF) < 0)return -1;                              
	}
	
	i2c_dev->ctrl2_bit.saddr    = saddr << 1;
	i2c_dev->ctrl2_bit.cnt      = msgs->len;
	i2c_dev->ctrl2_bit.dir      = I2C_DIR_RECEIVE;
	i2c_dev->ctrl2_bit.astopen  = (msgs->flags & I2C_MSG_STOP) ? 1 : 0;  
	
	if(!i2c_dev->ctrl2_bit.astopen)i2c_interrupt_enable(i2c_dev,I2C_TDC_INT,TRUE);
	
	if(dev->I2C_DMA_Receive_Channel == NULL)return -2;
	wk_dma_channel_config(dev->I2C_DMA_Receive_Channel, 
											  (uint32_t)&i2c_dev->rxdt, 
											  (uint32_t)msgs->buf, 
											   msgs->len);
	
	i2c_dma_enable(dev->dev, I2C_DMA_REQUEST_RX, TRUE);
	dma_channel_enable(dev->I2C_DMA_Receive_Channel,TRUE);
	
	i2c_dev->ctrl2_bit.genstart = 1; 
	
	if(msgs->flags & I2C_MSG_STOP)
	{
		if(i2c_wait_auto(dev,I2C_WAIT_STOP) < 0)
		{
			i2c_interrupt_enable(i2c_dev,I2C_TDC_INT,FALSE);
			dma_channel_enable(dev->I2C_DMA_Receive_Channel,FALSE);
			return -1;
		}
		dma_channel_enable(dev->I2C_DMA_Receive_Channel,FALSE);
	}
	/*else //这部分没有具体测试需要read 后 追加restart需要再打开测试
	{
		if(i2c_wait_auto(dev,I2C_WAIT_RESTART) < 0)
		{
			i2c_interrupt_enable(i2c_dev,I2C_TDC_INT,FALSE);
			dma_channel_enable(dev->I2C_DMA_Receive_Channel,FALSE);
			return -1;
		}
		i2c_interrupt_enable(i2c_dev,I2C_TDC_INT,FALSE);
		dma_channel_enable(dev->I2C_DMA_Receive_Channel,FALSE);
	}*/
	return 0;
}

int i2c_at32_transaction(i2c_dev_t *dev,i2c_msg_t *msgs,uint16_t saddr)
{
	if(msgs == NULL)return -1;
	int ret = 0;
	if ((msgs->flags & I2C_MSG_RW_MASK) == I2C_MSG_WRITE) 
	{
		ret = i2c_at32_msg_write(dev,msgs,saddr);
		return ret;	
	}
	else
	{
		ret = i2c_at32_msg_read(dev,msgs,saddr);
		return ret;	
	}
}

int i2c_transfer(i2c_dev_t *dev,i2c_msg_t *msgs, uint8_t num_msgs,uint16_t saddr)
{
	i2c_msg_t *current;
	i2c_msg_t *next = NULL;
	
	if(msgs == NULL || num_msgs == 0 || dev == NULL || dev->dev == NULL)return -2;
	msgs[num_msgs - 1].flags |= I2C_MSG_STOP;
	
	current = msgs;
	
	for (int i = 0; i + 1 < num_msgs; i++)
	{
			current = &msgs[i];
			next    = &msgs[i + 1];

			if (OPERATION(current) != OPERATION(next))
			{
					if (!(next->flags & I2C_MSG_RESTART)) return -3;
					if (current->flags & I2C_MSG_STOP)    return -3;
			}
	}
	
	current = msgs;
	int num_msgs_len = num_msgs;
	while (num_msgs_len > 0) 
	{
		int ret = i2c_at32_transaction(dev,current,saddr);
		if(ret < 0)
		{
			//__ASM("BKPT #0");
			return ret;
		}
		current++;
		num_msgs_len--;
	}
	return 0;
}

inline int i2c_write(i2c_dev_t *dev,uint8_t *buf,uint32_t num_bytes, uint16_t saddr)
{
	rt_base_t level;
	level = rt_hw_interrupt_disable();
	i2c_msg_t msg;
	msg.buf   = buf;
	msg.len   = num_bytes;
	msg.flags = I2C_MSG_WRITE;
	rt_hw_interrupt_enable(level);
	
	return i2c_transfer(dev,&msg, 1, saddr);
}

inline int i2c_read(i2c_dev_t *dev,uint8_t *buf,uint32_t num_bytes, uint16_t saddr)
{
	rt_base_t level;
	level = rt_hw_interrupt_disable();
	
	i2c_msg_t msg;
	msg.buf   = buf;
	msg.len   = num_bytes;
	msg.flags = I2C_MSG_READ;
	rt_hw_interrupt_enable(level);
	
	return i2c_transfer(dev,&msg, 1, saddr);
}

inline int i2c_write_read(i2c_dev_t *dev,uint8_t *txbuf,uint32_t txlen,uint8_t *rxbuf,uint32_t rxlen, uint16_t saddr)
{
	rt_base_t level;
	level = rt_hw_interrupt_disable();
	
	i2c_msg_t msg[2];
	msg[0].buf   = txbuf;
	msg[0].len   = txlen;
	msg[0].flags = I2C_MSG_WRITE;
	
	msg[1].buf   = rxbuf;
	msg[1].len   = rxlen;
	msg[1].flags = I2C_MSG_READ|I2C_MSG_RESTART;
	rt_hw_interrupt_enable(level);
	
	return i2c_transfer(dev,&msg[0], 2, saddr);
}

	