/*Implementation of queue with basic operation using arrays */

#include <stdint.h>
#include "Queue.h"
#include "RS485.h"


void toQue(QueueF& q,const Frame& ndata){

    q.data[q.tail] = ndata;
    q.tail =(q.tail+1)%q.size;
}

Frame fromQue(QueueF& q){

    Frame temp =q.data[q.head];
    q.head =(q.head+1)%q.size ;
    return temp;
}



bool isQueEmpty(const QueueF& q){
    if(q.head == q.tail)
        return true;
    else
        return false;
}


bool isQueFull(const QueueF& q){
    if((q.tail==(q.size-1) && q.head == 0) || (q.head == (q.tail + 1))  )
        return true;
    else
        return false;
}

void toQue(QueueB& q,const uint8_t& ndata){

    q.data[q.tail] = ndata;
    q.tail =(q.tail+1)%q.size;
}

uint8_t  fromQue(QueueB& q){

	uint8_t temp =q.data[q.head];
    q.head =(q.head+1)%q.size ;
    return temp;
}



bool isQueEmpty(const QueueB& q){
    if(q.head == q.tail)
        return true;
    else
        return false;
}


bool isQueFull(const QueueB& q){
    if((q.tail==(q.size-1) && q.head == 0) || (q.head == (q.tail + 1))  )
        return true;
    else
        return false;
}


