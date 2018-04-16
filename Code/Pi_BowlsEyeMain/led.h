/*!
 * @file led.h
 *
 * 
 * @author Harvey Leicester
 */

#ifndef LED_H_
#define LED_H_

#include <pigpio.h>
#include <stdint.h>

/*!
 * @brief Wrapper for interfacing with LEDs (or other gpio pins)
 */
typedef struct{

	int pin;				/*!<pin of LED*/
	uint8_t state;			/*!<state of pin/LED*/
}LED_t;

LED_t bluetoothIndicatorLED;

void LED_construct(LED_t *led, int pin);
void LED_toggle(LED_t *led, double time);
void LED_high(LED_t *led);
void LED_low(LED_t *led);


#endif /* LED_H_ */

