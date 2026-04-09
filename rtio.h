#ifndef __rtio_h
#define __rtio_h

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "util.h"
#include "rtthread.h"

#define SENSOR_DATA_MAX 15

typedef struct rtio_node rtio_node_t;
typedef struct rtio_node_rx rtio_node_rx_t;

enum 
{
	RTIO_NODE_FREE = 0,
	RTIO_NODE_ALLOC,
  RTIO_NODE_IN_SQ,
  RTIO_NODE_IN_CQ,
	RTIO_NODE_EXEC,
};

enum
{
	Dev_IDLE = 0,
	Dev_BUSY
};

enum
{
	LSM6DSR_E = 1,
	QMC6309_E = 2,
};

typedef struct 
{
  rtio_node_t *free_list;
  rtio_node_t *sq_head;
  rtio_node_t *sq_tail;
  rtio_node_t *cq_head;
  rtio_node_t *cq_tail;
	rtio_node_t *current_node;
	
	uint8_t     Dev_busy_State;
	rt_tick_t   start_tick;
}rtio_t;

struct rtio_node
{
	uint16_t Device_Name;
	uint16_t op;
	void (*dev)(rtio_t *rtio,rtio_node_t *node);
	volatile uint8_t state;
	struct rtio_node *next;
};

struct rtio_node_rx
{
		uint16_t Device_Name;
	 uint8_t rx[SENSOR_DATA_MAX];
};

#define Rtio_Sqe_Pool_Define(name,sq_sz)\
				static struct rtio_node UTIL_CAT_1(name,_sqe_pool)[sq_sz];
				
#define Rtio_Cqe_Pool_Define(name,cq_sz)\
				static struct rtio_node UTIL_CAT_1(name,_cqe_pool)[cq_sz];

#define Rtio_Define_Pool(name,sq_sz,cq_sz)\
				Rtio_Sqe_Pool_Define(name,sq_sz)\
				rtio_t UTIL_CAT_1(rtio_,name)

void rtio_pool_init(rtio_node_t *rtio_node_head,\
										uint16_t size,\
										rtio_t   *rtio
									 );
rtio_node_t *rtio_acquire(rtio_t *rtio);
void rtio_submit_sq(rtio_t *rtio,\
										rtio_node_t *node);

rtio_node_t *rtio_sq_pop(rtio_t *rtio);
void rtio_release(rtio_t *rtio,\
									rtio_node_t *node);

#endif
 

