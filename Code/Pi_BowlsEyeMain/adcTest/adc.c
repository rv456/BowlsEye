#include "adc.h"

int ADCController_construct(ADCController_t *adcCont, int spiHandle){

	for(uint8_t i=0; i<2; i++){

		adcCont->txBuf[i] = 0x00;	
		adcCont->rxBuf[i] = 0x00;
	}

	adcCont->adcVal = 0;

	adcCont->spiHandle = spiHandle;	
	return adcCont->spiHandle;
}

int ADCController_readChan0(ADCController_t *adcCont){

	adcCont->txBuf[0] = 0x00;

	spiWrite(adcCont->spiHandle, adcCont->txBuf, 2);
	ADCController_read(adcCont);

	return (ADCController_read(adcCont));
}

int ADCController_readChan1(ADCController_t *adcCont){

	adcCont->txBuf[0] = 0x08;

	spiWrite(adcCont->spiHandle, adcCont->txBuf, 2);
        return (ADCController_read(adcCont));

}

int ADCController_read(ADCController_t *adcCont){

	spiXfer(adcCont->spiHandle, adcCont->txBuf, adcCont->rxBuf, 2);
	
	adcCont->adcVal = 0;

	adcCont->adcVal |= (((adcCont->rxBuf[0] & 0x0F) << 8 ) | adcCont->rxBuf[1]);

	return (adcCont->adcVal);
}

