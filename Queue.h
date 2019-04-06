#ifndef QUEUE_H_
#define QUEUE_H_

template<typename T>
struct Queue{
	T* data;
	uint8_t size;
	volatile uint8_t head;
	volatile uint8_t tail;
};

template<typename T>
void toQue(Queue<T>& q, T ndata);

template<typename T>
T fromQue(Queue<T>& q);

template<typename T>
bool isQueEmpty(Queue<T>& q);

template<typename T>
bool isQueFull(Queue<T>& q);

#endif /* QUEUE_H_ */
