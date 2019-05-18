/*
 * message_lib.h
 */

#ifndef MESSAGE_LIB_H_
#define MESSAGE_LIB_H_


typedef struct
{
	uint8_t Start;
	uint8_t Address;
	uint8_t Length;
	uint8_t Crc;
	uint8_t *Payload;
} MSG_Message;


#endif
