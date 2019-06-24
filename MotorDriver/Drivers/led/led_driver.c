/*
 * led_driver.c
 */


#include "led_driver.h"


void LED_Init(void)
{
	/*!
	 * LED_1 = GPIOA5
	 * LED_2 = GPIOA4
	 * LED_3 = GPIOA3
	 *
	 * CNF1		CNF0	MODE1	MODE0	ODR
	 * 0		0		1		0		1
	 *
	 * General purpose output
	 * Maximum output speed 2MHz
	 */
	LED_GPIO->CRL &= ~(GPIO_CRL_CNF5 | GPIO_CRL_CNF4 | GPIO_CRL_CNF3);
	LED_GPIO->CRL |= GPIO_CRL_MODE5_1 | GPIO_CRL_MODE4_1 | GPIO_CRL_MODE3_1;
	LED_GPIO->BRR = LED_1_PIN | LED_2_PIN | LED_3_PIN;
}


void LED_SetLedOn(LED led)
{
	LED_GPIO->BSRR = led;
}


void LED_SetLedOff(LED led)
{
	LED_GPIO->BRR = led;
}


void LED_ToggleLed(LED led)
{
	LED_GPIO->ODR ^= led;
}


void LED_SetLed(LED led, bool state)
{
	if(state) LED_SetLedOn(led);
	else LED_SetLedOff(led);
}

