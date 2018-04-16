/*!
 * @file adc.c
 *
 * 
 * @author Harvey Leicester
 */

#include "adc.h"


/*!
 * @brief Construct the ADC buffers
 */
void ADCController_constructBuffers(void){

	for(int i=0; i<MAX_BYTE_BUFFER_SIZE_; i++){

		ADC_TX0_BUFFER_[i] = 0x00;
		ADC_TX1_BUFFER_[i] = 0x08;
		ADC_RX_BUFFER_[i] = 0x00;
	}

	ADC_TX0_BUFFER_[MAX_BYTE_BUFFER_SIZE_ - 2] = 0x08;
	ADC_TX1_BUFFER_[MAX_BYTE_BUFFER_SIZE_ - 2] = 0x00;
}

/*!
 * Constructor for ADCController_t
 * @param adcCont					Instance of ADCController_t
 * @param spiHandle					SPI configuation to assign
 * @param userParam					User parameters to assign
 * @return							SPI handle
 */
int ADCController_construct(ADCController_t *adcCont, int spiHandle, int userParam){

	ADCController_constructBuffers();

	adcCont->txBuf[0] = ADC_TX0_BUFFER_;
	adcCont->txBuf[1] = ADC_TX1_BUFFER_;

	adcCont->rxBuf = ADC_RX_BUFFER_;
	adcCont->channel = 0;

	adcCont->userMaxDistance = &userParam;

	adcCont->spiHandle = spiHandle;
	return adcCont->spiHandle;
}

/*!
 * Update the ADC reading routine
 * @param adcCont				Instance of ADCController_t
 */
void ADCController_update(ADCController_t *adcCont){

	spiXfer(adcCont->spiHandle, adcCont->txBuf[adcCont->channel], adcCont->rxBuf, *(adcCont->userMaxDistance));

	adcCont->channel = 1-adcCont->channel;
}

/*!
 * Convert read bytes from ADC to integer values
 * @param adcCont				Instance of ADCController_t
 * @param dst					Destination to store ADC values
 */
void ADCController_convertToInt(ADCController_t *adcCont, int *dst){

	int temp = 0;
	int index = 0;

	for(int i=0; i<*(adcCont->userMaxDistance); i+=2){

		temp = 0;
		temp |= (((adcCont->rxBuf[i] & 0x0F) << 8) | adcCont->rxBuf[i+1]);

		dst[index] = temp;
		index++;

	}
}


