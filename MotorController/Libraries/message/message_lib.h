/*
 * message_lib.h
 */

#ifndef MESSAGE_LIB_H_
#define MESSAGE_LIB_H_

#define POLYNOMIAL 0x9b
#define START_BYTE 0x7E
#define MY_ADDRESS 1
#define Frames_BUFF_LEN 20


typedef struct
{
	uint8_t Length;
	uint8_t *Payload;
} MSG_Message;



MSG_Message MSG_FromQue();
void MSG_ToQue(uint8_t frame[], uint8_t len, uint8_t address);
bool MSG_IsQueFull(uint8_t space);
bool MSG_IsQueEmpty();

void MSG_CrcInit(void);
uint8_t MSG_Crc(uint8_t const message[], uint8_t nBytes);

void MSG_Send(uint8_t* data, uint8_t len, uint8_t address);
void BUS_Received(uint8_t *buff, uint8_t len);
void __attribute__((weak)) MSG_Received(uint8_t *data, uint8_t len);


#endif
