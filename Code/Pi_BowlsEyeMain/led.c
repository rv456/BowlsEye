/*!
 * @file led.c
 *
 * 
 * @author Harvey Leicester
 */

#include "led.h"

/*!
 * Constructor for LED_t
 * @param led				Instance of LED_t
 * @param pin				Pin to assign to LED
 */
void LED_construct(LED_t *led, int pin){


	led->pin = pin;
	led->state = 0;
	gpioSetMode(led->pin, PI_OUTPUT);
	gpioWrite(led->pin, led->state);
}

/*!
 * Toggle LED
 * @param led				Instance of LED_t
 * @param time				Time to toggle
 */
void LED_toggle(LED_t *led, double time){

	gpioWrite(led->pin, led->state);
	led->state = 1-led->state;
	time_sleep(time);
	gpioWrite(led->pin, led->state);
	led->state = 1-led->state;
	time_sleep(time);
}

/*!
 * Set LED high
 * @param led				Instance of LED_t
 */
void LED_high(LED_t *led){

	led->state = 1;
	gpioWrite(led->pin, led->state);
}

/*!
 * Set LED low
 * @param led				Instance of LED_t
 */
void LED_low(LED_t *led){

	led->state = 0;
	gpioWrite(led->pin, led->state);
}



