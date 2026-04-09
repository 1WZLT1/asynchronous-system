#ifndef __spi_serve_h
#define __spi_serve_h

#include "at32f435_437_spi.h"
#include "at32f435_437_dma.h"
#include "wk_dma.h"

void SPI_TransmitReceive_DMA(dma_channel_type* SPI_DMA_Transmit_Channel,\
														 dma_channel_type* SPI_DMA_Receive_Channel,\
														 uint32_t          Peripheral_Address,\
														 uint32_t          Transmit_Buffer_Address,\
														 uint32_t          Reseive_Buffer_Address,\
														 uint32_t          Size);

#endif

