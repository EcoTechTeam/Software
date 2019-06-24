/*
 * led_driver.h
 */

#ifndef LED_DRIVER_H_
#define LED_DRIVER_H_


#include "hardware.h"
#include <stdbool.h>

typedef enum
{
	LED1 = LED_1_PIN,
	LED2 = LED_2_PIN,
	LED3 = LED_3_PIN
} LED;


void LED_Init(void);
void LED_SetLedOn(LED led);
void LED_SetLedOff(LED led);
void LED_ToggleLed(LED led);
void LED_SetLed(LED led, bool state);


#endif /* LED_DRIVER_H_ */
