/*Implementation of queue with basic operation using arrays */

#include <stdint.h>
#include "Queue.h"


template<typename T>
void toQue(Queue<T>& q, T ndata){

    q.data[q.tail] = ndata;
    q.tail =(q.tail+1)%q.size;
}
template<typename T>
T  fromQue(Queue<T>& q){

    T temp =q.data[q.head];
    q.head =(q.head+1)%q.size ;
    return temp;
}


template<typename T>
bool isQueEmpty(Queue<T>& q){
    if(q.head == q.tail)
        return true;
    else
        return false;
}

template<typename T>
bool isQueFull(Queue<T>& q){
    if((q.tail==(q.size-1) && q.head == 0) || (q.head == (q.tail + 1))  )
        return true;
    else
        return false;
}


