#include <avr/io.h>
#include <stdint.h>                     // needed for uint8_t
#include <avr/interrupt.h>

#define BAUD 4800
#define MYUBRR F_CPU/16/BAUD-1

#include "crc.h"
#include "RS485.h"
#include "Queue.h"
#define ADRESS_OF_THIS_uC 'K'
#define ADRESS_OF_ENGINE_uC 'E'
volatile bool shallSendButtonState=false;
void timer1Init();


int main(void){
	DDRB&=!(1<<PB2); //pin pb2 jako input.
	PORTB|=(1<<PB2); // pull up
	uint8_t buttonDeBounc=0;
	sei(); //global interrupt enable
	timer1Init();
	RS485_Init(MYUBRR);

	bool button1=false;
	bool button2=false;
	Frame frameOUT;
	Frame frameIN;
	extern QueueF framesReceived;


	while(1){
		if(bit_is_clear(PINB,PB2)){
			if(buttonDeBounc++ >250){ //todo wartość losowa, trzeba ją dobrać
				buttonDeBounc=0;
				button1=true;
			}
		}else{
			buttonDeBounc=0;
			button1=false;
		}

		while( !isQueEmptyF(&framesReceived)){
			frameIN=fromQueF(&framesReceived);
			if(frameIN.adress == ADRESS_OF_THIS_uC  || crc8_check(&frameIN)){

				//todo interpretacja danych
			}else {

				//ramka nie adresowana do tego uC lub błędna.
			}
			//############################
			frameOUT=frameIN; //w tym wypadku tylko do testu wysyłam echo 
			sendFrame(&frameOUT);
			//############################
		}
		if( shallSendButtonState  && button1){ //przycisk trzymany

		        	frameOUT.adress=ADRESS_OF_ENGINE_uC;
		        	for(int i=0;i<FRAME_LENGTH-2;i++){
		        		frameOUT.data[i]='X'; //patern który oznacza wciśniety guzik
		        	}
		        	crc8_update(&frameOUT);


		        	sendFrame(&frameOUT);

		        	shallSendButtonState=false;

		  }else if(!button1 && button2){ //przycisk odpuszczony

			  	  	 frameOUT.adress=ADRESS_OF_ENGINE_uC;
		    		for(int i=0;i<FRAME_LENGTH-2;i++){
		    			frameOUT.data[i]='O'; //patern który oznacza puszcznie guzika
		    		}
		    		crc8_update(&frameOUT);

		    		sendFrame(&frameOUT);;




		 }
		button2=button1;

	}
}
ISR(TIMER1_COMPA_vect){
	shallSendButtonState=true;
}

void timer1Init(){ //timer odliczający okresy po których wysyłać stan guzika.
	TCCR1B|=(1<<WGM12); //CTC Mode
	OCR1A=420; //przy jakiej wartosci odpala przerwanie,  todo ##################### to na pewno trzeba dobrać #####################
	TIMSK|=(1<<OCIE1A); //włączenie przrwania po przekroczeniu wartości w OCR1b
	TCCR1B|=(1<<CS10)|(1<<CS12); //start liczenia co 1024 cykle
}



