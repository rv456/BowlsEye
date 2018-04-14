#include "ringBuffer.h"

void RingBuffer_construct(RingBuffer_t *buf, int *array, int size){

	buf->data = array;
	buf->size = size;


	//flush the buffer
	for(int i=0; i < buf->size; i++){

		buf->data[i] = 0;
	}

	buf->head = 0;
	buf->tail = 0;
}

uint8_t RingBuffer_push(RingBuffer_t *buf, int value){

	uint8_t temp = !(RingBuffer_isFull(buf));

	if(temp){

		(buf->data)[buf->head] = value;
	        (buf->head)++;
	        buf->head = (buf->head >= buf->size) ? 0 : buf->head;

	}

	return temp;
}

uint8_t RingBuffer_pop(RingBuffer_t *buf, int *dst){

	uint8_t temp = !(RingBuffer_isEmpty(buf));

	if(temp){


		*dst = (buf->data)[buf->tail];
                (buf->tail)++;
		buf->tail = (buf->tail >= buf->size) ? 0 : buf->tail;

	}

	return temp;
}

uint8_t RingBuffer_isFull(RingBuffer_t *buf){

	return (buf->head == (buf->tail - 1));
}

uint8_t RingBuffer_isEmpty(RingBuffer_t *buf){

	return (buf->head == buf->tail);
}
