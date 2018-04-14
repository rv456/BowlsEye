#include "FIFO.h"

#define ADC_VAL_INDEX_			0
#define TIME_STAMP_INDEX_		1
#define BUFFER_SIZE_			6000

double ADC_VALUE_ARRAY_[BUFFER_SIZE_];
double TIME_STAMP_ARRAY_[BUFFER_SIZE_];

//RingBuffer_t ringBuffer;
FIFO_t timeStampBuffer;
FIFO_t adcDataBuffer;

FIFO_t *BUFFER_[2];

void globals_config(void){


	FIFO_construct(&adcDataBuffer, ADC_VALUE_ARRAY_, BUFFER_SIZE_);
	FIFO_construct(&timeStampBuffer, TIME_STAMP_ARRAY_, BUFFER_SIZE_);
	BUFFER_[ADC_VAL_INDEX_] = &adcDataBuffer;
	BUFFER_[TIME_STAMP_INDEX_] = &timeStampBuffer;
}
