#ifndef RS485_H_
#define RS485_H_
#include <stdint.h>
#define FRAME_LENGTH 4
#define RECEIVED_FRAMES_BUFFER_SIZE 50
#define FRAMES_TO_SEND_BUFFER_SIZE 20


union Frame{
	struct{

		uint8_t adress;
		uint8_t data[FRAME_LENGTH-2];
		uint8_t crc;
	};
	uint8_t bytes[FRAME_LENGTH];
};
void sendFrame(Frame frame);
void RS485_Init( unsigned int ubrr);

//void USART_Transmit( unsigned char data );
//unsigned char USART_Receive( void );




#endif /* RS485_H_ */
