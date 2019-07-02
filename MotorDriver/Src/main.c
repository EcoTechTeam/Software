/*
 * main.c
 */


#include "system_driver.h"
#include "led_driver.h"
#include "motor_driver.h"
#include "button_driver.h"
#include "encoder_driver.h"
#include "bus_driver.h"
#include "msg_lib.h"


bool _ProcessSamples;
uint16_t *_SamplesPointer;
uint16_t _AvgSample;
uint32_t _Rotations;
int16_t _Rpm;
uint8_t _TableIndex;


bool _MotorState = false;
uint8_t _ControllerState;
uint8_t _MessageTimer = 0;


const uint16_t _CurrentTable[118] = {2500, 2541, 2592, 2643, 2694, 2744, 2795, 2846, 2896, 2947, 2947, 2947, 2947, 2947, 2947, 2947, 2947, 2947, 2947,
		2947, 2947, 2947, 2947, 2947, 2947, 2947, 2926, 2910, 2894, 2877, 2861, 2845, 2828, 2812, 2795, 2779, 2763, 2746,
		2730, 2714, 2697, 2681, 2665, 2648, 2632, 2615, 2599, 2583, 2566, 2551, 2543, 2543, 2543, 2543, 2543, 2543, 2543,
		2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543,
		2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543,
		2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543,
		2543, 2543, 2543, 2543 };

const uint16_t _CurrentTable2[118] = {2500, 2541, 2592, 2643, 2694, 2744, 2795, 2846, 2896, 2947, 2947, 2947, 2947, 2947, 2947, 2947, 2947, 2947, 2947,
		2947, 2947, 2947, 2947, 2947, 2947, 2947, 2926, 2910, 2894, 2877, 2861, 2845, 2828, 2812, 2795, 2779, 2763, 2746,
		2730, 2714, 2697, 2681, 2665, 2648, 2632, 2615, 2599, 2583, 2566, 2551, 2543, 2543, 2543, 2543, 2543, 2543, 2543,
		2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543,
		2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543,
		2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543,
		2543, 2543, 2543, 2543 };

const uint16_t _CurrentTable3[118] = {2500, 2541, 2592, 2643, 2694, 2744, 2795, 2846, 2896, 2947, 2947, 2947, 2947, 2947, 2947, 2947, 2947, 2947, 2947,
		2947, 2947, 2947, 2947, 2947, 2947, 2947, 2926, 2910, 2894, 2877, 2861, 2845, 2828, 2812, 2795, 2779, 2763, 2746,
		2730, 2714, 2697, 2681, 2665, 2648, 2632, 2615, 2599, 2583, 2566, 2551, 2543, 2543, 2543, 2543, 2543, 2543, 2543,
		2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543,
		2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543,
		2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543, 2543,
		2543, 2543, 2543, 2543 };



int main(void)
{

	SYS_Init();
	LED_Init();
	MTR_Init();
	BTN_Init();
	ENC_Init();
	BUS_Init();
	MSG_CrcInit();

	while(1)
	{
		SYS_KickWatchdog();

		if(_ProcessSamples)
		{
			_ProcessSamples = false;
			uint32_t acc = 0;
			for(uint16_t i=0; i<MTR_BUFFLEN; i++)
				acc += _SamplesPointer[i];
			_AvgSample = acc / MTR_BUFFLEN;
		}

		if(_ControllerState==0 && _MotorState)
		{
			MTR_TurnOff();
			_MotorState=false;

		}
		else if(!_MotorState)
		{
			MTR_TurnOn();
			_MotorState=true;

		}

		//! TESTING PURPOSES!!!!
		if(_ControllerState==1) //standard mapa
		{
			LED_SetLedOn(LED3);
			LED_SetLedOff(LED2);
			LED_SetLedOff(LED1);
		}
		else if(_ControllerState==2) //res
		{
			LED_SetLedOn(LED2);
			LED_SetLedOff(LED3);
			LED_SetLedOff(LED1);
		}
		else if(_ControllerState==3) //mapa slow
		{
			LED_SetLedOn(LED2);
			LED_SetLedOn(LED3);
			LED_SetLedOff(LED1);
		}
		else if(_ControllerState==4) //mapa fast
				{
			LED_SetLedOff(LED2);
			LED_SetLedOff(LED3);
			LED_SetLedOn(LED1);
				}
		else {
			LED_SetLedOff(LED2);
			LED_SetLedOff(LED3);
			LED_SetLedOff(LED1);
		}
	}
}


//! Systick handler called in interrupt
void SYS_Tick(void)
{
	//! Read rpm value from encoder
	_Rpm = ENC_ReadAndReset();
	//! Calculate rpm to table index value
	if(_Rpm >=0) _TableIndex = _Rpm / 40;
	else _TableIndex = 0;
	if(_TableIndex >= 118) _TableIndex = 117;

	if(_ControllerState == 2) MTR_SetLimit(_CurrentTable2[_TableIndex]);
	if(_ControllerState == 3) MTR_SetLimit(_CurrentTable3[_TableIndex]);
	else MTR_SetLimit(_CurrentTable[_TableIndex]);

	//! TODO: Handle events
	if(_MessageTimer > 10)
	{

		_ControllerState=0;



	}
	else _MessageTimer++;
}


//! Samples handler called in interrupt
void MTR_SamplesReady(uint16_t *samples)
{
	_SamplesPointer = samples;
	_ProcessSamples = true;
	//	LED_ToggleLed(LED2);
}


void ENC_FullRotation(void)
{
	_Rotations++;
}


void MSG_Received(uint8_t *buff, uint8_t len)
{
	_MessageTimer = 0;
	//! TODO: Do something with message
	if(buff[0]) _ControllerState = 1;
	else if(buff[1]) _ControllerState = 2;
	else if(buff[2]) _ControllerState = 3;
	else if(buff[3]) _ControllerState = 4;
	else _ControllerState = 0;
}
