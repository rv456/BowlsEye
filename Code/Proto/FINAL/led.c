#include "led.h"

void LED_construct(LED_t *led, int pin){


	led->pin = pin;
	led->state = 0;
	gpioSetMode(led->pin, PI_OUTPUT);
	gpioWrite(led->pin, led->state);
}

void LED_toggle(LED_t *led, double time){

	gpioWrite(led->pin, led->state);
	led->state = 1-led->state;
	time_sleep(time);
	gpioWrite(led->pin, led->state);
	led->state = 1-led->state;
	time_sleep(time);
}

void LED_high(LED_t *led){

	led->state = 1;
	gpioWrite(led->pin, led->state);
}

void LED_low(LED_t *led){

	led->state = 0;
	gpioWrite(led->pin, led->state);
}

