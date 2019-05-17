/*Implementation of queue with basic operation using arrays */

#include <stdint.h>
#include <stdbool.h>
#include "Queue.h"
#include "RS485.h"


void toQueF(QueueF *q, Frame *ndata)
{
    q->data[q->tail] = *ndata;
    q->tail =(q->tail+1)%q->size;
}

Frame fromQueF(QueueF *q){

    Frame temp =q->data[q->head];
    q->head =(q->head+1)%q->size ;
    return temp;
}



bool isQueEmptyF(QueueF *q){
    if(q->head == q->tail)
        return true;
    else
        return false;
}


bool isQueFullF(QueueF *q){
    if((q->tail==(q->size-1) && q->head == 0) || (q->head == (q->tail + 1))  )
        return true;
    else
        return false;
}

void toQueB(QueueB *q, uint8_t ndata){

    q->data[q->tail] = ndata;
    q->tail =(q->tail+1)%q->size;
}

uint8_t  fromQueB(QueueB *q){

	uint8_t temp =q->data[q->head];
    q->head =(q->head+1)%q->size ;
    return temp;
}



bool isQueEmptyB( QueueB *q){
    if(q->head == q->tail)
        return true;
    else
        return false;
}


bool isQueFullB( QueueB *q){
    if((q->tail==(q->size-1) && q->head == 0) || (q->head == (q->tail + 1))  )
        return true;
    else
        return false;
}


