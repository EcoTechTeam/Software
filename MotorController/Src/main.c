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


static volatile bool _Button=true;
static bool _Active=false;
static uint8_t a[]={0xff,0xee,0xee,0xff};


int main(void)
{
	BUS_Init();
	TIM_Init();
	MSG_CrcInit();
	wdt_enable(WDTO_1S);
	LED_Init();
	BTN_Init();
	sei();

	while(1)
	{
		wdt_reset();
		if( _Button && BTN_StateC()) //holding & pushed
		{
			MSG_Send(a,4,0xee);
			TIM_Reset();
			_Button=false;
			_Active=true;
		}
		else if(_Active && !BTN_StateC())//released
		{
			MSG_Send(a,4,0xdd);
			_Active=false;
			_Button=true;
		}
	}
}


void TIM_SysTick(void)
{
	_Button=true;
}


void MSG_Received(uint8_t* data, uint8_t len)
{
    (void) data;
    (void) len;
	//u can interpret input date here
}


