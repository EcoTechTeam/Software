#ifndef QUEUE_H_
#define QUEUE_H_
#include "RS485.h"

struct QueueF{
	Frame* data;
	const uint8_t size;
	volatile uint8_t head;
	volatile uint8_t tail;
};

struct QueueB{
	uint8_t* data;
	const uint8_t size;
	volatile uint8_t head;
	volatile uint8_t tail;
};



void toQue(QueueF& q,const Frame& ndata);


Frame fromQue(QueueF& q);


bool isQueEmpty(const QueueF& q);


bool isQueFull(const QueueF& q);


void toQue(QueueB& q,const uint8_t& ndata);


uint8_t fromQue(QueueB& q);


bool isQueEmpty(const QueueB& q);


bool isQueFull(const QueueB& q);


#endif /* QUEUE_H_ */
