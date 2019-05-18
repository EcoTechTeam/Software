/*
 * bus_driver.c
 */

#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "bus_driver.h"


//! Free bus flag
static bool _BusFree = true;
//! Message is pending to send
static bool _TxPending = false;
//! Receive buffer
static uint8_t _RxBuff[BUS_BUFF_NUM][BUS_BUFF_LEN];
//! Rx message index
static uint8_t _RxMsg = 0;
//! Rx data intex
static uint8_t _RxData = 0;
//! Rx overflowed
static bool _RxOverflow = false;
//! Transmit buffer
static uint8_t _TxBuff[BUS_BUFF_LEN];
//! Tx data index
static uint8_t _TxData = 0;
//! Tx data to send
static uint8_t _TxLen = 0;


void BUS_Init(void)
{
	//! TODO: Implement UART peripheral initialization
	//! TODO: Implement TIM peripheral initialization
}


void BUS_Send(uint8_t *buff, uint8_t len)
{
	//! Copy passed message to internal buffer
	_TxLen = len;
	_TxData = 0;
	for(uint8_t i=0; i<len; i++)
		_TxBuff[i] = buff[i];
	
	if(_BusFree)
	{
		//! TODO: start uart transmission
	}
	else _TxPending = true;
}


void BUS_SendBlocking(uint8_t *buff, uint8_t len)
{
	for(uint8_t i=0; i<len; i++)
	{
		//! TODO: Send bytes
	}
}


ISR(USART_RXC_vect)
{
	if(_RxData < BUS_BUFF_LEN)
	{
		//! TODO: copy data to buffer
	}
	else _RxOverflow = true;
	//! TODO: start and reset timer to fire the isr if this is last byte
}


ISR(USART_TXC_vect)
{
	if(_TxData < _TxLen)
	{
		//! TODO: copy byte from _TxBuff to uart
	}
	else _BusFree = true;
}


ISR(TIMER2_COMP_vect)
{
	//! TODO: stop timer
	
	//! Call receive function if receive buffer is not overflowed
	if(!_RxOverflow) BUS_Received(_RxBuff[_RxMsg], _RxData);
	//! Set next rx buffer and reset data index to 0
	_RxMsg = (_RxMsg + 1) % BUS_BUFF_NUM;
	_RxData = 0;
	_RxOverflow = false;

	if(_TxPending)
	{
		_TxPending = false;
		//! TODO: start uart transmission
	}
	else _BusFree = true;
}


