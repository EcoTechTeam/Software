#include <avr/io.h>
#include <stdint.h>                     // needed for uint8_t
//#include <util/twi.h>
#include <avr/interrupt.h>
#include "RS485.h"
#define START_BYTE 0x7E
#define STOP_BYTE 0x7B
#define ESCAPE_BYTE 0x7D
#include "Queue.h"


uint8_t bytesSe[(FRAME_LENGTH*2)+2];
Queue<uint8_t> bytesBuffer = {bytesSe,(FRAME_LENGTH*2)+2,0,0};


Frame framesRe[RECEIVED_FRAMES_BUFFER_SIZE]; //todo powinno być volatile
Queue< Frame> framesReceived = {framesRe,RECEIVED_FRAMES_BUFFER_SIZE, 0 ,0};



Frame framesSe[FRAMES_TO_SEND_BUFFER_SIZE];
Queue<Frame> framesToSend = {framesSe,FRAMES_TO_SEND_BUFFER_SIZE, 0, 0};



volatile bool busEmpty=false;



void getFrameReady(Frame frame){
	busEmpty=false;
	if(UCSRA & (1 << UDRE)){ // sprawdzenie czy TX jest wolne, jeśli tak wysyłanie pierwszej wiadomości.
		UDR = START_BYTE;
		//todo jest to ryzykowne, bo jeśli ta wiadomość się wyśle przed napełnienem buffora kolejnymi wiadomościami kolene przerwanie USART_RXC_vect nie wypali i wysyłanie wiadomości się przerwie.
	}else {
		toQue(bytesBuffer,(uint8_t)START_BYTE);
	}
	for(int i=0;i<=FRAME_LENGTH;i++){

		if(frame.bytes[i]==START_BYTE || frame.bytes[i]==STOP_BYTE || frame.bytes[i]==ESCAPE_BYTE){
			toQue(bytesBuffer,(uint8_t)ESCAPE_BYTE);
		}
		toQue(bytesBuffer,frame.bytes[i]);
	}
	toQue(bytesBuffer,(uint8_t)STOP_BYTE);

}

void sendFrame(Frame frame){
	if(busEmpty){
		getFrameReady(frame);
	}else if(isQueFull(framesToSend)){
		//todo kolejka ramek do wysłania jest pełna.
	} else{
		toQue(framesToSend,frame);
	}
}



ISR(USART_RXC_vect){
	TCCR2&=!((1<<CS00)|(1<<CS02)); //zatrzymuje timer2
	busEmpty=false;
	static bool LastByteWasEscape=false;
	static int8_t i=-1;
	static Frame buff;
	uint8_t temp=UDR;
	if(i==-1){
		if(temp==START_BYTE){
			i++;
		}else{
			i=-1;
			//error
		}
	} else if(i==FRAME_LENGTH){
		if(temp==STOP_BYTE){
			i=-1;
			if(isQueFull(framesReceived)){
				//todo Nie wiem co jak uC nie będzie nadążać z ogarnianiem ramka.
			} else{
				toQue(framesReceived,buff);
			}

		}else{
			i=-1;
			//error! ostatni bajt ramki nie był stop bajtem.
		}
	}else if(LastByteWasEscape){ //poprzedni bajt był escape bajtem
		buff.bytes[i++]=temp;
		LastByteWasEscape=false;
	}else if(temp==ESCAPE_BYTE){
		LastByteWasEscape=true;
	}else if(temp==STOP_BYTE || temp==START_BYTE){
		i=-1;
		//error! stop albo start bajt był gdzieś w środku ramki.
	}else{

		buff.bytes[i++]=temp;
	}
	TCNT2 =0; //reset timera0
	TCCR2|=(1<<CS00)|(1<<CS02); //wznowienie timera2

}

ISR(USART_TXC_vect){
	 if(isQueEmpty(bytesBuffer))
	    {
		 TCNT2 =0; //reset timera0
		 TCCR2|=(1<<CS00)|(1<<CS02); //wznowienie  timera2

	    } else{
	    	UDR = fromQue(bytesBuffer);
	    }

}
ISR(TIMER2_COMP_vect){  //Timer liczy czas od ostatniej wiadomosci na magistrali i odpala to przerwanie kiedy minął wymagany czas pomiedzy wiadomosciami
	if(isQueEmpty(framesToSend)){
		TCCR2&=!((1<<CS00)|(1<<CS02)); //zatrzymuje timer2
		TCNT2 =0; // i go resetuje
		busEmpty=true;
	} else{
		getFrameReady(fromQue(framesToSend));
	}
}



void timer2Init(){
	TCCR2|=(1<<WGM21); //CTC Mode
	OCR2=200; //przy jakiej wartosci odpala przerwanie,   !!to na pewno trzeba dobrać!!
	TIMSK|=(1<<OCIE2); //włączenie przrwania po przekroczeniu wartości w OCR2
	TCCR2|=(1<<CS00)|(1<<CS02); //start liczenia co 1024 cykle
}

void RS485_Init( unsigned int ubrr)
{   /*Set baud rate */
	UBRRH  = (unsigned char)(ubrr>>8);
	UBRRL  = (unsigned char)ubrr;
	//Enable receiver and transmitter */
	UCSRB = (1<<RXEN)|(1<<TXEN);
	/* Set frame format: 8data, 1stop bit , parity even*/
	UCSRC |= (1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1)|(1<<UPM1); //todo przystosować to do rs485
	UCSRC &=!(1<<UPM0);

	timer2Init();
}


/*
void USART_sendByte( unsigned char data )
{
	while ( !( UCSRA & (1<<UDRE)) )      ;
	UDR = data;
}

unsigned char USART_Receive( void )
{
	while ( !(UCSRA & (1<<RXC)) )      ;
	unsigned char data =UDR;

	return data;
}
*/



