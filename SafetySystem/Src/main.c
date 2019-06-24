#define F_CPU 8000000UL		//taktowanie procesora

#include <avr/io.h>
#include <stdint.h>                     // needed for uint8_t
#include <util/delay.h>
#include <avr/interrupt.h>

#define SIGNALL				(1<<PD7)
#define LED_RED 			(1<<PB0)
#define LED_GREEN 			(1<<PB1)
#define BUZZER 				(1<<PB2)


uint16_t pomiar (uint8_t kanal);					// deklaracja funkcji pomiaru

uint16_t potValue;
uint16_t h2Value;
uint16_t kanal;


int main( void )
{
	PORTD |= SIGNALL;										//inicjalizacja stanu wysokiego na SIGNAL

	ADCSRA |= (1<<ADEN)|(1<<ADSC);					// wlacz ADC
	ADMUX |= (1<<REFS0);							// napięcie referencyjne 5 [V]
	ADCSRA |=(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);		// preskaler ustawiony na wartosc 128


	DDRB |= LED_RED | LED_GREEN | BUZZER ; 			// kierunek wyjsciowy na pinach portu B
	DDRD |= SIGNALL;									// kierunek wyjciowy na pinie portu D

	PORTB |= LED_RED;										// wstępny test elementów sygnalizacyjnych
	PORTB |= LED_GREEN;

	for (int p=0; p<3; p++)
	{
		PORTB |= BUZZER;
		_delay_ms(200);
		PORTB &= ~BUZZER;
		_delay_ms(200);
	}

	PORTB &= ~LED_RED;
	PORTB &= ~LED_GREEN;
	PORTB &= ~BUZZER;

	// 20-sekundowe wygrzanie sensora MQ-8
	for (int w=0; w<20; w++)
	{
		PORTB |= LED_RED, PORTB |= LED_GREEN;
		_delay_ms(500);
		PORTB &= ~LED_RED, PORTB &= ~LED_GREEN;
		_delay_ms(500);

		if(w>17) PORTB |= BUZZER;
	}

	PORTB &= ~LED_RED;					// wygaszenie elementów sygnalizacyjnych, koniec wygrzewania sensora MQ - 8
	PORTB &= ~LED_GREEN;
	PORTB &= ~BUZZER;
	sei();
	while(1){
		h2Value = pomiar(1);// odczytana wartosc z ADC
		potValue =pomiar(0);//odczytana wartosc z potencjometru

		if (h2Value > potValue)					// warunek wyboru rodzaju sygnalizacji
		{
			PORTD &= ~SIGNALL;			// ustawienie stanu niskiego na SIGNAL
			PORTB |= LED_RED;					// sygnalizacja czerwoną LED
			PORTB |= BUZZER;					// sygnalizacja BUZZER
			_delay_ms(50);
			PORTB &= ~LED_RED;
			_delay_ms(50);
			PORTB |= LED_RED;
			PORTB &= ~BUZZER;
			_delay_ms(50);
			PORTB &= ~LED_RED;
			_delay_ms(100);
		}

		else
		{
			PORTD |=SIGNALL;				// ustawienie stanu wysokiego na SIGNAL
			PORTB |= LED_GREEN;				// sygnalizacja zieloną LED
			_delay_ms(50);
			PORTB &= ~LED_GREEN;
			_delay_ms(400);
		}
	}
}


uint16_t pomiar (uint8_t kanal)

{
	ADMUX = (ADMUX & 0xF8) | kanal;
	ADCSRA |= (1<<ADSC);
	while  (ADCSRA & (1<<ADSC));
	return ADCW;
}

