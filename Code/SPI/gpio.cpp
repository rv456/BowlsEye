#include "gpio.h"
#include <signal.h>

GPIOClass::GPIOClass(uint16_t pinNo, uint8_t mode) : _pinNo(pinNo){
	
	switch (mode){
		
		case MODE_OUTPUT_:
			pinMode(_pinNo, OUTPUT);
			break;
			
		case MODE_INPUT_:
			pinMode(_pinNo, INPUT);
			break;
	}
}

void GPIOClass::write(uint8_t state){
	
	digitalWrite(_pinNo, state);
}

void GPIOClass::high(){
	
	digitalWrite(_pinNo, HIGH);
}

void GPIOClass::low(){
	
	digitalWrite(_pinNo, LOW);
}

uint8_t GPIOClass::read(){
	
	return digitalRead(_pinNo);
}
