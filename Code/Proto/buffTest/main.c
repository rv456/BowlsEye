#include <stdio.h>
#include "ringBuffer.h"

int main(int argc, char** argv){

    int bufferArray[16] = {0};

    RingBuffer_t ringBuff;

    RingBuffer_construct(&ringBuff, bufferArray, 16);

    for(uint8_t i=0; i<15; i++){

	RingBuffer_push(&ringBuff, i);

    }


    int sample = 0;

    for(uint8_t i=0; i<16; i++){

	RingBuffer_pop(&ringBuff, &sample);
	printf("sample %i\ti %i\n", sample, i);
	}
}
