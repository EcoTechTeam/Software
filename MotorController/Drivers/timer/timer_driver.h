/*
 * timer_driver.h
 */

#ifndef TIMER_DRIVER_H_
#define TIMER_DRIVER_H_


#include "hardware.h"


//! TODO: concider frequency
#define TIM_TICK_MS	10


//! TODO: Pass frequency?
void TIM_Init(void);
void __attribute__((weak)) TIM_SysTick(void);
void TIM_Reset(void);
void TIM_Stop(void);
void TIM_Start(void);


#endif
