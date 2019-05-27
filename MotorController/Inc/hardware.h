/*
 * hardware.h
 */

#ifndef HARDWARE_H_
#define HARDWARE_H_

#include <avr/io.h>
#include <avr/interrupt.h>

//! Clock define
#define F_CPU		8000000

//! Bus timer defines
#define BUS_TCNT	TCNT0
#define BUS_TCCR	TCCR0
#define BUS_TOIE	TOIE0

//! Button defines
#define BTN_P_A		PD2
#define BTN_DDR_A	DDRD
#define BTN_PORT_A	PORTD
#define BTN_PIN_A	PIND

#define BTN_P_B		PD3
#define BTN_DDR_B	DDRD
#define BTN_PORT_B	PORTD
#define BTN_PIN_B	PIND

#define BTN_P_C		PC0
#define BTN_DDR_C	DDRC
#define BTN_PORT_C	PORTC
#define BTN_PIN_C	PINC

#define BTN_P_D		PC1
#define BTN_DDR_D	DDRC
#define BTN_PORT_D	PORTC
#define BTN_PIN_D	PINC

//! Led defines
#define LED_DDR		DDRC
#define LED_PORT	PORTC
#define LED_R		PC2
#define LED_G		PC3

#endif
