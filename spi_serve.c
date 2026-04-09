#include "spi_serve.h"

void SPI_TransmitReceive_DMA(dma_channel_type* SPI_DMA_Transmit_Channel,\
														 dma_channel_type* SPI_DMA_Receive_Channel,\
														 uint32_t          Peripheral_Address,\
														 uint32_t          Transmit_Buffer_Address,\
														 uint32_t          Reseive_Buffer_Address,\
														 uint32_t          Size)
{
	dma_flag_clear(DMA1_FDT5_FLAG);
  dma_flag_clear(DMA1_FDT6_FLAG);
	
	wk_dma_channel_config(SPI_DMA_Transmit_Channel, 
                        Peripheral_Address, 
                        Transmit_Buffer_Address, 
                        Size);
	wk_dma_channel_config(SPI_DMA_Receive_Channel, 
                        Peripheral_Address, 
                        Reseive_Buffer_Address, 
                        Size);
	
	dma_channel_enable(DMA1_CHANNEL5, TRUE);
  dma_channel_enable(DMA1_CHANNEL6, TRUE);
}

