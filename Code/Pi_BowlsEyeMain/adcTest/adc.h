#include <pigpio.h>
#include <stdio.h>
#include <pthread.h>

#define SPI_CHAN_		(int)0
#define SPI_FLAGS_		(int)3

typedef struct{
	
	int spiHandle;
	char txBuf[2];
	char rxBuf[2];
	int adcVal;
}ADCController_t;

ADCController_t adcController;

int ADCController_construct(ADCController_t *adcCont, int clkFreq);
int ADCController_readChan0(ADCController_t *adcCont);
int ADCController_readChan1(ADCController_t *adcCont);

int ADCController_read(ADCController_t *adcCont);
void ADCController_selChan(ADCController_t *adcCont);
