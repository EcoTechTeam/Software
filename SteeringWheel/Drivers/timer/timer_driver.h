/*
 * timer_driver.h
 */

#ifndef TIMER_DRIVER_H_
#define TIMER_DRIVER_H_


//! TODO: concider frequency
#define TIM_TICK_MS	10


//! TODO: Pass frequency?
void TIM_Init(void);
void __attribute__((weak)) TIM_SysTick(void);


#endif
