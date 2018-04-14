#include <stdio.h>
#include "FIFO.h"

#define BUFFSIZE_		16

int main(int argc, char** argv){


	float  buffArray[BUFFSIZE_];

	FIFO_t fifo;
	FIFO_construct(&fifo, buffArray, BUFFSIZE_);

	for(uint8_t i=0; i<BUFFSIZE_; i++){

		FIFO_push(&fifo, i);
	}

	float sample = 0;

	for(uint8_t i=0; i<BUFFSIZE_; i++){

		FIFO_pop(&fifo, &sample);
		printf("%f\n", sample);
	}

}
