/*
 * button_driver.h
 */

#ifndef BUTTON_DRIVER_H_
#define BUTTON_DRIVER_H_


#include <stdbool.h>
#include "hardware.h"


typedef enum
{
	BTN_A = 0x01,
	BTN_B = 0x02,
	BTN_C = 0x04,
	BTN_D = 0x08
} BTN_Button;


//! Init button GPIO peripheral
void BTN_Init(void);
bool BTN_StateA(void);
bool BTN_StateB(void);
bool BTN_StateC(void);
bool BTN_StateD(void);
bool BTN_Pressed(BTN_Button button);


#endif
