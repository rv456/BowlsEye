#include <pigpio.h>
#include <stdio.h>
#include <pthread.h>

#define SPI_CHAN_		(int)0
#define SPI_FLAGS_		(int)3

//1m ~ 583ms, = 5830 ints = 11660 bytes
#define MAX_BYTE_BUFFER_SIZE_	11660   	

char ADC_TX0_BUFFER_[MAX_BYTE_BUFFER_SIZE_];
char ADC_TX1_BUFFER_[MAX_BYTE_BUFFER_SIZE_];
char ADC_RX_BUFFER_[MAX_BYTE_BUFFER_SIZE_];

typedef struct{
	
	int spiHandle;
	char *txBuf[2];
	char *rxBuf;
	int *userMaxDistance;
	uint8_t channel;
}ADCController_t;

ADCController_t adcController;


int ADCController_construct(ADCController_t *adcCont, int spiHandle, int userParam);
void ADCController_constructBuffers(void);

int ADCController_readChan0(ADCController_t *adcCont);
int ADCController_readChan1(ADCController_t *adcCont);

int ADCController_read(ADCController_t *adcCont);
void ADCController_selChan(ADCController_t *adcCont);

void ADCController_update(ADCController_t *adcCont);