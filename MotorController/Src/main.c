/*
 * main.c
 */

#include <stdint.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>

#include "bus_driver.h"
#include "button_driver.h"
#include "led_driver.h"
#include "timer_driver.h"
#include "message_lib.h"


static volatile bool _SendState = false;


int main(void)
{
	bool btnA;
	bool btnB;
	bool btnC;
	bool btnD;
	uint8_t messageBuffer[8];

	BUS_Init();
	TIM_Init();
	LED_Init();
	BTN_Init();
	MSG_CrcInit();

	wdt_enable(WDTO_1S);
	sei();

	while(1)
	{
		//! Reset watchdog
		wdt_reset();
		//! Get actual button states
		btnA = BTN_StateA();
		btnB = BTN_StateB();
		btnC = BTN_StateC();
		btnD = BTN_StateD();
		//! Send frame flag set by timer
		if(_SendState)
		{
			//LED_RedToggle();
			uint8_t len = MSG_PackButtonStates(btnA, btnB, btnC, btnD, messageBuffer);
			BUS_Send(messageBuffer, len);
			_SendState = false;
		}
	}
}


void TIM_SysTick(void)
{
	_SendState = true;
}


void MSG_Received(uint8_t* data, uint8_t len)
{
    (void) data;
    (void) len;
	//! Do something with received data
}


