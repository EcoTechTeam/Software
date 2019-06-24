/*
 * main.c
 */


#include "system_driver.h"
#include "led_driver.h"
#include "motor_driver.h"
#include "button_driver.h"
#include "encoder_driver.h"


uint8_t _LedTim = 0;
bool _ProcessSamples;
uint16_t *_SamplesPointer;
uint16_t _AvgSample;
uint32_t _Rotations;
int16_t _Rpm;
uint8_t _TableIndex;

bool _ButtonState = false;

const uint16_t _CurrentTable[118] = {2500, 2541, 2592, 2643, 2694, 2744, 2795, 2846, 2896, 2947, 2947, 2947, 2947, 2947, 2947, 2947, 2947, 2947, 2947,
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

		//! TESTING PURPOSES!!!!
		if(BTN_State())
		{
			if(!_ButtonState)
			{
				MTR_TurnOn();
				_ButtonState = true;
			}
			LED_SetLedOn(LED3);
		}
		else
		{
			if(_ButtonState)
			{
				MTR_TurnOff();
				_ButtonState = false;
			}
			LED_SetLedOff(LED3);
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
	MTR_SetLimit(_CurrentTable[_TableIndex]);

	//! TODO: Handle events
	_LedTim++;
	if(_LedTim == 100)
	{
		_LedTim = 0;
		LED_ToggleLed(LED1);
	}
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
