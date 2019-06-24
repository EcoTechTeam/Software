/*
 * button_driver.c
 */


#include "button_driver.h"
#include "hardware.h"


void BTN_Init(void)
{
	/*!
	 * BTN_PIN = GPIOA_PIN15
	 *
	 * CNF1		CNF0	MODE1	MODE0	ODR
	 * 1		0		0		0		0
	 *
	 * Input pull-up
	 */
	BTN_GPIO->CRH &= ~GPIO_CRH_CNF15;
	BTN_GPIO->CRH |= GPIO_CRH_CNF15_1;
	BTN_GPIO->BSRR = BTN_PIN;
}


bool BTN_State(void)
{
	if(BTN_GPIO->IDR & BTN_PIN) return false;
	else return true;
}
