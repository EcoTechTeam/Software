/*
 * motor_driver.h
 */

#ifndef MOTOR_DRIVER_H_
#define MOTOR_DRIVER_H_


#include "hardware.h"


#define MTR_BUFFLEN		2000


#define MTR_HIST		20
#define MTR_TIM_ARR		30000
#define MTR_TIM_ON		29900
#define MTR_TIM_OFF		0
#define MTR_DT          40

#define MTR_ADC_ARR		1799


#pragma pack(2)
typedef struct
{
	uint16_t A[MTR_BUFFLEN];
	uint16_t B[MTR_BUFFLEN];
} MTR_Samples;


void MTR_Init(void);
void MTR_TurnOn(void);
void MTR_TurnOff(void);
void MTR_SetLimit(uint16_t limit);
void __attribute__((weak)) MTR_SamplesReady(uint16_t *samples);
void __attribute__((weak)) MTR_UnderVoltage(void);


#endif /* MOTOR_DRIVER_H_ */
