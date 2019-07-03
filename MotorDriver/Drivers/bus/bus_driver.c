/*
 * bus_driver.c
 */


#include <stdbool.h>
#include "bus_driver.h"


//! Receive buffer
static uint8_t _RxBuff[BUS_BUFF_NUM][BUS_BUFF_LEN];
//! Rx message index
static uint8_t _RxMsg = 0;
//! Rx data intex
static uint8_t _RxData = 0;
//! Rx overflowed
static bool _RxOverflow = false;

static uint8_t _TempDR;


void BUS_Init(void)
{
	/*!
	 * BUS_RX_PIN = GPIOB_PIN11
	 *
	 * CNF1		CNF0	MODE1	MODE0	ODR
	 * 0		1		0		0		0
	 *
	 * Input floating
	 *
	 * BUS_TX_PIN = GPIOB_PIN10
	 *
	 * CNF1		CNF0	MODE1	MODE0	ODR
	 * 1		0		1		0		0
	 *
	 * Alternate function push-pull @ 2 MHz
	 *
	 */

	BUS_GPIO->ODR |= GPIO_ODR_ODR10;
	BUS_GPIO->CRH &= ~(GPIO_CRH_CNF10 | GPIO_CRH_CNF11 | GPIO_CRH_MODE11);
	BUS_GPIO->CRH |= GPIO_CRH_CNF11_0 | GPIO_CRH_MODE10_1;

	//! Calculated on asap:
	//! 36000000 / (16 * 38400) = 585.9375
	//! DIV_Mantissa = 585
	//! DIV_Fraction = 0.9375 * 16 = 15
	//! TODO: Change to calculations based on BUS_BAUD macro
	BUS_UART->BRR = (58 << 4) | 10;
	BUS_UART->CR1 |= USART_CR1_UE | USART_CR1_RXNEIE | USART_CR1_IDLEIE | USART_CR1_RE;

	NVIC_EnableIRQ(USART3_IRQn);
}


void USART3_IRQHandler(void)
{
	uint16_t sr = BUS_UART->SR;
	if(sr & USART_SR_RXNE)
	{
		if(_RxData < BUS_BUFF_LEN) _RxBuff[_RxMsg][_RxData++] = BUS_UART->DR;
		else _RxOverflow = true;
	}
	if(sr & USART_SR_IDLE)
	{
		//! Read DR to clear flag
		_TempDR = BUS_UART->DR;

        uint8_t temp_RxMsg = _RxMsg;
        uint8_t temp_RxData = _RxData;
        bool temp_RxOverflow = _RxOverflow;

        _RxMsg = (_RxMsg + 1) % BUS_BUFF_NUM;
        _RxData = 0;
        _RxOverflow = false;

		//! Call receive function if receive buffer is not overflowed
		if(!temp_RxOverflow) BUS_Received(_RxBuff[temp_RxMsg], temp_RxData);
	}
}

