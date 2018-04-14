#include <stdint.h>

typedef struct{

	float *data;
	int size;
	int head;
}FIFO_t;

void FIFO_construct(FIFO_t *fifo, float *array, int size);
void FIFO_push(FIFO_t *fifo, float value);
void FIFO_pop(FIFO_t *fifo, float *dst);
void FIFO_flush(FIFO_t *fifo);
