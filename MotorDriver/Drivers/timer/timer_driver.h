/*
 * timer_driver.h
 */

#ifndef TIMER_DRIVER_H_
#define TIMER_DRIVER_H_


#include <stdbool.h>


void TIM_Init(void);
void __attribute__((weak)) TIM_tick(void);
void TIM_reset(void);

#endif /* TIMER_DRIVER_H_ */
