#include <stdint.h>

typedef struct{

	double *data;
	int size;
	int head;
}FIFO_t;

void FIFO_construct(FIFO_t *fifo, double *array, int size);
void FIFO_push(FIFO_t *fifo, double value);
void FIFO_pop(FIFO_t *fifo, double *dst);
void FIFO_flush(FIFO_t *fifo);
