#define F_CPU 1000000UL		//taktowanie procesora


#include <avr/io.h>
#include <stdint.h>                     // needed for uint8_t
#include <avr/interrupt.h>

#define BAUD 2400
#define MYUBRR F_CPU/16/BAUD-1


#include "RS485.h"
#include "Queue.h"
//#define ADRESS_OF_uC 1



int main(void){
	Frame frameOUT;
	Frame frameIN;
	sei(); //global interrupt enable
	RS485_Init(MYUBRR);
	extern Queue<Frame> framesReceived;


	while(1){


		while( !isQueEmpty(framesReceived)){
			frameIN=fromQue(framesReceived);
			//tu bedzie interpretacja ramki,
			//sprawdzenie czy crc się zgadza i czy to ramka przeznaczona dla nas.
		}
		//tutaj będzie tworzenie ramki frameOUT w zależnosci od guzikow itp
		frameOUT=frameIN; //w tym wypadku wysyłam echo
    	sendFrame(frameOUT);

	}

}




