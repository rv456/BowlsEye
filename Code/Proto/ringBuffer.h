#include <stdint.h>

typedef struct{

	int *data;
	int size;
	int head;
	int tail;
}RingBuffer_t;

void RingBuffer_construct(RingBuffer_t *buf, int *array, int size);
uint8_t RingBuffer_push(RingBuffer_t *buf, int value);
uint8_t RingBuffer_pop(RingBuffer_t *buf, int *dst);
uint8_t RingBuffer_isFull(RingBuffer_t *buf);
uint8_t RingBuffer_isEmpty(RingBuffer_t *buf);
