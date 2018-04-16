/*!
 * @file adc.h
 *
 * 
 * @author Harvey Leicester
 */

#ifndef ADC_H_
#define ADC_H_

#include <pigpio.h>
#include <stdio.h>
#include <pthread.h>

#define SPI_CHAN_		(int)0
#define SPI_FLAGS_		(int)3

#define MAX_BYTE_BUFFER_SIZE_	6000

char ADC_TX0_BUFFER_[MAX_BYTE_BUFFER_SIZE_];
char ADC_TX1_BUFFER_[MAX_BYTE_BUFFER_SIZE_];
char ADC_RX_BUFFER_[MAX_BYTE_BUFFER_SIZE_];
int RAW_ADC_BUFFER_[MAX_BYTE_BUFFER_SIZE_/2];

/*!
 * Structure for interfacing with ADC
 */
typedef struct{

	int spiHandle;					/*!<Handle containing SPI configuration*/
	char *txBuf[2];					/*!<Transmitting buffers*/
	char *rxBuf;					/*!<Receiving buffer*/
	int *userMaxDistance;			/*!<User parameter frim GUI*/
	uint8_t channel;				/*!<ADC channel*/
}ADCController_t;

ADCController_t adcController;

int ADCController_construct(ADCController_t *adcCont, int spiHandle, int userParam);
void ADCController_constructBuffers(void);
void ADCController_convertToInt(ADCController_t *adcCont, int *dst);
int ADCController_readChan0(ADCController_t *adcCont);
int ADCController_readChan1(ADCController_t *adcCont);
int ADCController_read(ADCController_t *adcCont);
void ADCController_selChan(ADCController_t *adcCont);
void ADCController_update(ADCController_t *adcCont);

#endif /* ADC_H_ */

