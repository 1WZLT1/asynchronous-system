#ifndef __sensor_h
#define __sensor_h

#include "rtthread.h"

typedef struct RawBuffer{
	//一个周期内塞入变量的计数值
	int value_count;
	//一个周期内塞入变量总值
	float value_sum;
	//上一个周期的输出
	float last_value;
	//重复计数,塞入相同值则进行计数
	int repeat_count ;
}RawBuffer_t;

void  RawBuffer_Input(RawBuffer_t* buffer, float value);
void  Sensor_Init(void);
float RawBuffer_Output(RawBuffer_t* buffer);

extern rt_mailbox_t sensor_sqe_mb;
extern rt_mailbox_t sensor_cqe_mb;

#endif

