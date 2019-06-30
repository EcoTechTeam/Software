/*
 * button_driver.c
 */

#include "led_driver.h"
#include "timer_driver.h"
#include "hardware.h"


void TIM_Init(void)
{
	//inicjuje timer odmierzajacy kilka ms od ostatniej wiadomosc i wylaczajacy silnik todo
}


void przerwanieTIM()//todo
{

TIM_tick();
}

void TIM_reset(void)
{
	//todo reset
}

