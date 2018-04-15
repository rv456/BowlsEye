#include <pigpio.h>
#include <stdint.h>

typedef struct{

	int pin;
	uint8_t state;
}LED_t;

LED_t bluetoothIndicatorLED;

void LED_construct(LED_t *led, int pin);
void LED_toggle(LED_t *led, double time);
void LED_high(LED_t *led);
void LED_low(LED_t *led);