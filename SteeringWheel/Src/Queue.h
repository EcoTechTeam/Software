#ifndef QUEUE_H_
#define QUEUE_H_
#include "RS485.h"
#include <stdbool.h>


typedef struct
{
	Frame* data;
	const uint8_t size;
	volatile uint8_t head;
	volatile uint8_t tail;
} QueueF;


typedef struct
{
	uint8_t *data;
	const uint8_t size;
	volatile uint8_t head;
	volatile uint8_t tail;
} QueueB;



void toQueF(QueueF *q, Frame *ndata);

Frame fromQueF(QueueF *q);

bool isQueEmptyF(QueueF *q);

bool isQueFullF(QueueF *q);

void toQueB(QueueB *q, uint8_t ndata);

uint8_t fromQueB(QueueB *q);

bool isQueEmptyB(QueueB *q);

bool isQueFullB(QueueB *q);


#endif /* QUEUE_H_ */
