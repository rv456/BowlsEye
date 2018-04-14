#include "FIFO.h"

void FIFO_construct(FIFO_t *fifo, float *array, int size){

	fifo->data = array;
	fifo->size = size;
	
	FIFO_flush(fifo);
}

void FIFO_push(FIFO_t *fifo, float value){

	fifo->data[fifo->head] = value;
	
	fifo->head++;
	fifo->head = (fifo->head >= fifo->size) ? 0 : fifo->head;
}

void FIFO_pop(FIFO_t *fifo, float *dst){

	*dst = fifo->data[fifo->head];
	fifo->head++;
	fifo->head = (fifo->head >= fifo->size) ? 0 : fifo->head;
}

void FIFO_flush(FIFO_t *fifo){

	for(int i=0; i< fifo->size; i++){

		fifo->data[i] = 0;
	}

	fifo->head = 0;
}
