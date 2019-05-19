/*
 * button_driver.c
 */

#include <avr/io.h>
#include <stdint.h>
#include "button_driver.h"


void BTN_Init(void)
{

	// Set GPIO in input configuration
	DDRC&=!(1<<PC0); //input
	PORTC|=(1<<PC0); //pull up

	DDRC&=!(1<<PC1);
	PORTC|=(1<<PC1);

	DDRD&=!(1<<PD2);
	PORTD|=(1<<PD2);

	DDRD&=!(1<<PD3);
	PORTD|=(1<<PD3);
}


bool BTN_StateA(void)
{
	// Return state of selected button
	if (PIND & (1<<PD2)) return false;
	else return true;
}


bool BTN_StateB(void)
{
    // Return state of selected button
	if (PIND & (1<<PD3)) return false;
	else return true;
}


bool BTN_StateC(void)
{
    // Return state of selected button
	if (PINC & (1<<PC0)) return false;
	else return true;
}


bool BTN_StateD(void)
{
    // Return state of selected button
	if (PINC & (1<<PC1)) return false;
	else return true;
}


bool BTN_Pressed(BTN_Button button)
{
	switch (button)
	{
	case BTN_A:
		return BTN_StateA();
		break;
	case BTN_B:
		return BTN_StateB();
		break;
	case BTN_C:
		return BTN_StateC();
		break;
	case BTN_D:
		return BTN_StateD();
		break;
	default:
		return false;
	}
}


