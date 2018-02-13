#ifndef __GPIO_H_
#define __GPIO_H_

#include <wiringPi.h>
#include <stdint.h>

#define MODE_OUTPUT_	(uint8_t)0
#define MODE_INPUT_		(uint8_t)1

/*
 * Simple wrapper for wiring pi library
 */

class GPIOClass{
	
	public:
	
	GPIOClass(uint16_t pinNo, uint8_t mode);
	virtual ~GPIOClass(){};
	
	void write(uint8_t state);
	void high();
	void low();
	
	uint8_t read();
	
	private:
	
	uint16_t _pinNo;
};

#endif
