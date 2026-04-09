/* add user code begin Header */
/**
  **************************************************************************
  * @file     at32f435_437_int.c
  * @brief    main interrupt service routines.
  **************************************************************************
  *                       Copyright notice & Disclaimer
  *
  * The software Board Support Package (BSP) that is made available to
  * download from Artery official website is the copyrighted work of Artery.
  * Artery authorizes customers to use, copy, and distribute the BSP
  * software and its related documentation for the purpose of design and
  * development in conjunction with Artery microcontrollers. Use of the
  * software is governed by this copyright notice and the following disclaimer.
  *
  * THIS SOFTWARE IS PROVIDED ON "AS IS" BASIS WITHOUT WARRANTIES,
  * GUARANTEES OR REPRESENTATIONS OF ANY KIND. ARTERY EXPRESSLY DISCLAIMS,
  * TO THE FULLEST EXTENT PERMITTED BY LAW, ALL EXPRESS, IMPLIED OR
  * STATUTORY OR OTHER WARRANTIES, GUARANTEES OR REPRESENTATIONS,
  * INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
  *
  **************************************************************************
  */
/* add user code end Header */

/* includes ------------------------------------------------------------------*/
#include "at32f435_437_int.h"
/* private includes ----------------------------------------------------------*/
/* add user code begin private includes */
#include "at32f435_437_gpio.h"
#include "string.h"

#include "LSM6DSR.h"
#include "imu_task.h"
#include "uart_serve.h"
#include "i2c_serve.h"
#include "rtio.h"
#include "use_fdilink.h"
#include "qmc6309.h"
#include "sensor.h"
/* add user code end private includes */

/* private typedef -----------------------------------------------------------*/
/* add user code begin private typedef */
extern rtio_t  rtio_spi1;
extern rtio_t  rtio_i2c2;
extern uint8_t sqe_init_ok;
/* add user code end private typedef */

/* private define ------------------------------------------------------------*/
/* add user code begin private define */

/* add user code end private define */

/* private macro -------------------------------------------------------------*/
/* add user code begin private macro */

/* add user code end private macro */

/* private variables ---------------------------------------------------------*/
/* add user code begin private variables */

/* add user code end private variables */

/* private function prototypes --------------------------------------------*/
/* add user code begin function prototypes */

/* add user code end function prototypes */

/* private user code ---------------------------------------------------------*/
/* add user code begin 0 */
extern uint8_t all_init;

uint16_t TMR2_Cnt = 0;
uint32_t Tick_Us_High = 0;
uint8_t  tmr5_first_bk = 0;
int64_t CortexM_Get_Us(void)
{
	while(1)
	{
		volatile uint32_t tick_0  = TMR5->cval;
		volatile uint32_t tick_32 = Tick_Us_High;
		if(tick_0 > TMR5->cval)
			continue;
		return ((int64_t) tick_32 << 32) | tick_0;
	}
}
/* add user code end 0 */

/* external variables ---------------------------------------------------------*/
/* add user code begin external variables */

/* add user code end external variables */

/**
  * @brief  this function handles nmi exception.
  * @param  none
  * @retval none
  */
void NMI_Handler(void)
{
  /* add user code begin NonMaskableInt_IRQ 0 */

  /* add user code end NonMaskableInt_IRQ 0 */

  /* add user code begin NonMaskableInt_IRQ 1 */

  /* add user code end NonMaskableInt_IRQ 1 */
}

/**
  * @brief  this function handles hard fault exception.
  * @param  none
  * @retval none
  */
//void HardFault_Handler(void)
//{
//  /* add user code begin HardFault_IRQ 0 */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  /* add user code end HardFault_IRQ 0 */
//  /* go to infinite loop when hard fault exception occurs */
//  while (1)
//  {
//    /* add user code begin W1_HardFault_IRQ 0 */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    /* add user code end W1_HardFault_IRQ 0 */
//  }
//}

/**
  * @brief  this function handles memory manage exception.
  * @param  none
  * @retval none
  */
void MemManage_Handler(void)
{
  /* add user code begin MemoryManagement_IRQ 0 */

  /* add user code end MemoryManagement_IRQ 0 */
  /* go to infinite loop when memory manage exception occurs */
  while (1)
  {
    /* add user code begin W1_MemoryManagement_IRQ 0 */

    /* add user code end W1_MemoryManagement_IRQ 0 */
  }
}

/**
  * @brief  this function handles bus fault exception.
  * @param  none
  * @retval none
  */
void BusFault_Handler(void)
{
  /* add user code begin BusFault_IRQ 0 */

  /* add user code end BusFault_IRQ 0 */
  /* go to infinite loop when bus fault exception occurs */
  while (1)
  {
    /* add user code begin W1_BusFault_IRQ 0 */

    /* add user code end W1_BusFault_IRQ 0 */
  }
}

/**
  * @brief  this function handles usage fault exception.
  * @param  none
  * @retval none
  */
void UsageFault_Handler(void)
{
  /* add user code begin UsageFault_IRQ 0 */

  /* add user code end UsageFault_IRQ 0 */
  /* go to infinite loop when usage fault exception occurs */
  while (1)
  {
    /* add user code begin W1_UsageFault_IRQ 0 */

    /* add user code end W1_UsageFault_IRQ 0 */
  }
}

/**
  * @brief  this function handles svcall exception.
  * @param  none
  * @retval none
  */
//void SVC_Handler(void)
//{
//  /* add user code begin SVCall_IRQ 0 */
////////////////////////////////////////////////////////////	
////////////////////////////////////////////////////////////  /* add user code end SVCall_IRQ 0 */
//  /* add user code begin SVCall_IRQ 1 */

////////////////////////////////////////////////////////////  /* add user code end SVCall_IRQ 1 */
//}

/**
  * @brief  this function handles debug monitor exception.
  * @param  none
  * @retval none
  */
void DebugMon_Handler(void)
{
  /* add user code begin DebugMonitor_IRQ 0 */

//  /* add user code end DebugMonitor_IRQ 0 */
  /* add user code begin DebugMonitor_IRQ 1 */

//  /* add user code end DebugMonitor_IRQ 1 */
}

/**
  * @brief  this function handles pendsv_handler exception.
  * @param  none
  * @retval none
  */
//void PendSV_Handler(void)
//{
//  /* add user code begin PendSV_IRQ 0 */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  /* add user code end PendSV_IRQ 0 */
//  /* add user code begin PendSV_IRQ 1 */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  /* add user code end PendSV_IRQ 1 */
//}

/**
  * @brief  this function handles systick handler.
  * @param  none
  * @retval none
  */
//void SysTick_Handler(void)
//{
//  /* add user code begin SysTick_IRQ 0 */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  /* add user code end SysTick_IRQ 0 */


//  /* add user code begin SysTick_IRQ 1 */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  /* add user code end SysTick_IRQ 1 */
//}

/**
  * @brief  this function handles EXINT Line 1 handler.
  * @param  none
  * @retval none
  */
void EXINT1_IRQHandler(void)
{
  /* add user code begin EXINT1_IRQ 0 */
	rt_interrupt_enter();
	exint_flag_clear(EXINT_LINE_1);	
	rt_interrupt_leave();
  /* add user code end EXINT1_IRQ 0 */
  /* add user code begin EXINT1_IRQ 1 */

  /* add user code end EXINT1_IRQ 1 */
}

/**
  * @brief  this function handles EXINT Line [9:5] handler.
  * @param  none
  * @retval none
  */
void EXINT9_5_IRQHandler(void)
{
  /* add user code begin EXINT9_5_IRQ 0 */
	rt_interrupt_enter();
	exint_flag_clear(EXINT_LINE_6);	
	if(all_init == 1)LSM6DSR_callback(&rtio_spi1);
	rt_interrupt_leave();
  /* add user code end EXINT9_5_IRQ 0 */
  /* add user code begin EXINT9_5_IRQ 1 */
  /* add user code end EXINT9_5_IRQ 1 */
}

/**
  * @brief  this function handles TMR2 handler.
  * @param  none
  * @retval none
  */
void TMR2_GLOBAL_IRQHandler(void)
{
  /* add user code begin TMR2_GLOBAL_IRQ 0 */
	if(TMR2->ists & 0x01)
	{
		rt_interrupt_enter();
		IMU_Handler();
		
		/**************attention********************/
		/**************attention********************/
		/**************attention********************/
		/*Moderately increase the data request frequency to compensate for the I2C wait time and keep the received data rate around 100 Hz.*/
		if(TMR2_Cnt++ == 3)
		{
				TMR2_Cnt = 0;
				if(all_init == 1)QMC6309_callback(&rtio_i2c2);
		}
		
		TMR2->ists &= ~(0x01);
		rt_interrupt_leave();
	}	
  /* add user code end TMR2_GLOBAL_IRQ 0 */


  /* add user code begin TMR2_GLOBAL_IRQ 1 */

  /* add user code end TMR2_GLOBAL_IRQ 1 */
}

/**
  * @brief  this function handles I2C1 Event handler.
  * @param  none
  * @retval none
  */
void I2C1_EVT_IRQHandler(void)
{
  /* add user code begin I2C1_EVT_IRQ 0 */
    rt_interrupt_enter();

    if (i2c_dev1.initialized)
    {
        if (I2C1->sts_bit.stopf == 1)
        {
            i2c_flag_clear(I2C1, I2C_STOPF_FLAG);
						i2c_dev1.stop_bit = 1;
            if(rt_thread_self() != RT_NULL && all_init == 1 && i2c_dev1.flags & I2C_MSG_STOP)
						{
							rt_sem_release(&i2c_dev1.i2c_wait_sem_stopf);
						}
        }
        else if (!(i2c_dev1.flags & I2C_MSG_STOP) &&
                 (I2C1->sts_bit.tdc == 1))
        {	
						i2c_interrupt_enable(I2C1,I2C_TDC_INT,FALSE);
            if(rt_thread_self() != RT_NULL && all_init == 1)
						{
							rt_sem_release(&i2c_dev1.i2c_wait_sem_tdf);
						}
        }
    }

    rt_interrupt_leave();
  /* add user code end I2C1_EVT_IRQ 0 */
  /* add user code begin I2C1_EVT_IRQ 1 */

  /* add user code end I2C1_EVT_IRQ 1 */
}

/**
  * @brief  this function handles I2C1 Error handler.
  * @param  none
  * @retval none
  */
void I2C1_ERR_IRQHandler(void)
{
  /* add user code begin I2C1_ERR_IRQ 0 */

  /* add user code end I2C1_ERR_IRQ 0 */
  /* add user code begin I2C1_ERR_IRQ 1 */

  /* add user code end I2C1_ERR_IRQ 1 */
}

/**
  * @brief  this function handles I2C2 Event handler.
  * @param  none
  * @retval none
  */
void I2C2_EVT_IRQHandler(void)
{
  /* add user code begin I2C2_EVT_IRQ 0 */
    rt_interrupt_enter();

		rtio_node_t *node = rtio_i2c2.current_node;
    if (i2c_dev2.initialized)
    {
        if (I2C2->sts_bit.stopf == 1)
        {
            i2c_flag_clear(I2C2, I2C_STOPF_FLAG);
						i2c_dev2.stop_bit = 1;
            if(rt_thread_self() != RT_NULL && all_init == 1 && i2c_dev2.flags & I2C_MSG_STOP)
						{
							if(node != NULL)
							{
								if(rtio_i2c2.current_node->Device_Name == QMC6309_E)
								{						
									rtio_node_rx_t dev;
									dev.Device_Name = QMC6309_E;
									rt_memcpy(&dev.rx,&OMC6309_Data_Receive,sizeof(OMC6309_Data_Receive));
									rt_mq_send(sensor_cqe_mq,&dev, sizeof(rtio_node_rx_t));
								}
								
								rtio_i2c2.current_node = NULL;
								rtio_release(&rtio_i2c2,node);
								rtio_i2c2.Dev_busy_State = Dev_IDLE; 
							}
							rt_sem_release(&i2c_dev2.i2c_wait_sem_stopf);
						}
        }
        else if (!(i2c_dev2.flags & I2C_MSG_STOP) &&
                 (I2C2->sts_bit.tdc == 1))
        {	
						i2c_interrupt_enable(I2C2,I2C_TDC_INT,FALSE);
            if(rt_thread_self() != RT_NULL && all_init == 1)
						{
							rt_sem_release(&i2c_dev2.i2c_wait_sem_tdf);
						}
        }
    }

    rt_interrupt_leave();
  /* add user code end I2C2_EVT_IRQ 0 */
  /* add user code begin I2C2_EVT_IRQ 1 */

  /* add user code end I2C2_EVT_IRQ 1 */
}

/**
  * @brief  this function handles I2C2 Error handler.
  * @param  none
  * @retval none
  */
void I2C2_ERR_IRQHandler(void)
{
  /* add user code begin I2C2_ERR_IRQ 0 */

  /* add user code end I2C2_ERR_IRQ 0 */
  /* add user code begin I2C2_ERR_IRQ 1 */

  /* add user code end I2C2_ERR_IRQ 1 */
}

/**
  * @brief  this function handles SPI1 handler.
  * @param  none
  * @retval none
  */
void SPI1_IRQHandler(void)
{
  /* add user code begin SPI1_IRQ 0 */
  /* add user code end SPI1_IRQ 0 */
  /* add user code begin SPI1_IRQ 1 */

  /* add user code end SPI1_IRQ 1 */
}

/**
  * @brief  this function handles USART2 handler.
  * @param  none
  * @retval none
  */
void USART2_IRQHandler(void)
{
  /* add user code begin USART2_IRQ 0 */

  /* add user code end USART2_IRQ 0 */
  /* add user code begin USART2_IRQ 1 */

  /* add user code end USART2_IRQ 1 */
}

/**
  * @brief  this function handles DMA1 Channel 1 handler.
  * @param  none
  * @retval none
  */
void DMA1_Channel1_IRQHandler(void)
{
  /* add user code begin DMA1_Channel1_IRQ 0 */

  /* add user code end DMA1_Channel1_IRQ 0 */
  /* add user code begin DMA1_Channel1_IRQ 1 */

  /* add user code end DMA1_Channel1_IRQ 1 */
}

/**
  * @brief  this function handles DMA1 Channel 3 handler.
  * @param  none
  * @retval none
  */
void DMA1_Channel3_IRQHandler(void)
{
  /* add user code begin DMA1_Channel3_IRQ 0 */
	if(DMA1->sts_bit.fdtf3 == 1)
	{
		rt_interrupt_enter();
		
		dma_flag_clear(DMA1_FDT3_FLAG);
		dma_channel_enable(DMA1_CHANNEL3, FALSE);
		commData.portHandles[0]->State = STREAM_READY;
		if(Stream_Handler(commData.portHandles[0]) == 0 && commData.portHandles[0]->sendover_callback)
		{
			commData.portHandles[0]->sendover_callback(commData.portHandles[0]->sendover_param);
		}
		
		rt_interrupt_leave();
	}
  /* add user code end DMA1_Channel3_IRQ 0 */
  /* add user code begin DMA1_Channel3_IRQ 1 */

  /* add user code end DMA1_Channel3_IRQ 1 */
}

/**
  * @brief  this function handles DMA1 Channel 5 handler.
  * @param  none
  * @retval none
  */
void DMA1_Channel5_IRQHandler(void)
{
  /* add user code begin DMA1_Channel5_IRQ 0 */
	if(DMA1->sts_bit.fdtf5 == 1)
	{
		rt_interrupt_enter();
		
		dma_flag_clear(DMA1_FDT5_FLAG);
		dma_flag_clear(DMA1_GL5_FLAG);
		
		rtio_node_t *node = rtio_spi1.current_node;
		if(node != NULL)
		{
			if(rtio_spi1.current_node->Device_Name == LSM6DSR_E)
			{
				LSM6DSR_CS_disenable;
				
				rtio_node_rx_t dev;
				dev.Device_Name = LSM6DSR_E;
				rt_memcpy(&dev.rx,&LSM6DR_Data_Receive,sizeof(LSM6DR_Data_Receive));
				rt_mq_send(sensor_cqe_mq,&dev, sizeof(rtio_node_rx_t));
			}
			
			rtio_spi1.current_node = NULL;
			rtio_release(&rtio_spi1,node);
			rtio_spi1.Dev_busy_State = Dev_IDLE; 
		}
		
		dma_channel_enable(DMA1_CHANNEL5, FALSE);
		rt_interrupt_leave();
	}
  /* add user code end DMA1_Channel5_IRQ 0 */
  /* add user code begin DMA1_Channel5_IRQ 1 */

  /* add user code end DMA1_Channel5_IRQ 1 */
}

/**
  * @brief  this function handles CAN2 RX0 handler.
  * @param  none
  * @retval none
  */
void CAN2_RX0_IRQHandler(void)
{
  /* add user code begin CAN2_RX0_IRQ 0 */
	Fdican_Request_Callback(CAN2);
  /* add user code end CAN2_RX0_IRQ 0 */
  /* add user code begin CAN2_RX0_IRQ 1 */

  /* add user code end CAN2_RX0_IRQ 1 */
}

/**
  * @brief  this function handles CAN2 RX1 handler.
  * @param  none
  * @retval none
  */
void CAN2_RX1_IRQHandler(void)
{
  /* add user code begin CAN2_RX1_IRQ 0 */

  /* add user code end CAN2_RX1_IRQ 0 */
  /* add user code begin CAN2_RX1_IRQ 1 */

  /* add user code end CAN2_RX1_IRQ 1 */
}

/**
  * @brief  this function handles CAN2 SE handler.
  * @param  none
  * @retval none
  */
void CAN2_SE_IRQHandler(void)
{
  /* add user code begin CAN2_SE_IRQ 0 */

  /* add user code end CAN2_SE_IRQ 0 */
  /* add user code begin CAN2_SE_IRQ 1 */

  /* add user code end CAN2_SE_IRQ 1 */
}

/**
  * @brief  this function handles DMA1 Channel 6 handler.
  * @param  none
  * @retval none
  */
void DMA1_Channel6_IRQHandler(void)
{
  /* add user code begin DMA1_Channel6_IRQ 0 */
	if(DMA1->sts_bit.fdtf6 == 1)
	{
		rt_interrupt_enter();
		dma_flag_clear(DMA1_FDT6_FLAG);
		dma_channel_enable(DMA1_CHANNEL6, FALSE);
		rt_interrupt_leave();
	}
  /* add user code end DMA1_Channel6_IRQ 0 */
  /* add user code begin DMA1_Channel6_IRQ 1 */

  /* add user code end DMA1_Channel6_IRQ 1 */
}

/**
  * @brief  this function handles DMA2 Channel 3 handler.
  * @param  none
  * @retval none
  */
void DMA2_Channel3_IRQHandler(void)
{
  /* add user code begin DMA2_Channel3_IRQ 0 */

  /* add user code end DMA2_Channel3_IRQ 0 */
  /* add user code begin DMA2_Channel3_IRQ 1 */

  /* add user code end DMA2_Channel3_IRQ 1 */
}

/* add user code begin 1 */

/* add user code end 1 */
