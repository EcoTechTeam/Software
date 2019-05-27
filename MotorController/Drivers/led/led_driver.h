/*
 * led_driver.h
 */

#ifndef LED_DRIVER_H_
#define LED_DRIVER_H_


#include "hardware.h"


typedef enum
{
	LED_OFF=0,
	LED_ON=1,
} LED_State;


void LED_Init(void);
void LED_RedOn(void);
void LED_RedOff(void);
void LED_RedToggle(void);
void LED_RedSet(LED_State state);
void LED_GreenOn(void);
void LED_GreenOff(void);
void LED_GreenToggle(void);
void LED_GreenSet(LED_State state);


#endif
