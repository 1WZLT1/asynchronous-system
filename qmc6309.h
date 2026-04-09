#ifndef __qmc_6309_h
#define __qmc_6309_h

#include "rtio.h"
#include "sensor.h"

typedef struct
{
  RawBuffer_t		      BufMagX;
  RawBuffer_t		      BufMagY;
  RawBuffer_t		      BufMagZ;
  float		            Temp;
  float               Mags[3];
  uint8_t             MagsValid[3];
  int64_t             lastUpdate;
  volatile int 		    Initialized;
}QMC6309_Status_Type;

extern uint8_t OMC6309_Data_Receive[6];
extern QMC6309_Status_Type QMC6309;

void QMC6309_Init(void);
void QMC6309_transmit(rtio_t *rtio,rtio_node_t *node);
void QMC6309_callback(rtio_t *rtio);
void QMC6309_Conversion(uint8_t *Data_Receive);

#endif

