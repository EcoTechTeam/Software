/*
 * button_driver.c
 */

#include <avr/io.h>
#include <stdint.h>
#include "button_driver.h"


void BTN_Init(void)
{
	//! TODO: Set GPIO in input configuration
}


bool BTN_StateA(void)
{
	bool state = false;
	//! TODO: Return state of selected button
	return state;
}


bool BTN_StateB(void)
{
        bool state = false;
        //! TODO: Return state of selected button
        return state;
}


bool BTN_StateC(void)
{
        bool state = false;
        //! TODO: Return state of selected button
        return state;
}


bool BTN_StateD(void)
{
        bool state = false;
        //! TODO: Return state of selected button
        return state;
}


bool BTN_State(BTN_Button button)
{
	bool state = false;
	//! Get state of selected button
	return state;
}
