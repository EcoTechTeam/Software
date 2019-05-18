/*
 * timer_driver.c
 */

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "timer_driver.h"


//! Global SysTick timer. Can be externed in other files
uint16_t SysTick = 0;


void TIM_Init(void)
{
	//! TODO: Init timer
}


//! Select right timer
ISR(TIMER0_OVF_vect)
{
	//! Reset timer flags?
	SysTick++;
	TIM_SysTick();
}


