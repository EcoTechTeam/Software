/*
 * led_driver.c
 */

#include <stdbool.h>
#include <avr/io.h>

#include "led_driver.h"


void LED_Init(void)
{
	DDRC  |= (1<<PC2) | (1<<PC3);
}


void LED_RedOn(void)
{
	PORTC |= (1<<PC2);
}


void LED_RedOff(void)
{
	PORTC &=!(1<<PC2);
}


void LED_RedToggle(void)
{
	PORTC ^=(1<<PC2);
}


void LED_RedSet(LED_State state)
{
	if(state) PORTC |= (1<<PC2);
	else PORTC &=!(1<<PC2);
}


void LED_GreenOn(void)
{
	PORTC |= (1<<PC3);
}


void LED_GreenOff(void)
{
	PORTC &=!(1<<PC3);
}


void LED_GreenToggle(void)
{
	PORTC ^=(1<<PC3);
}


void LED_GreenSet(LED_State state)
{
	if(state) PORTC |= (1<<PC3);
	else PORTC &=!(1<<PC3);
}


