#include <pigpio.h>

#define NO_PULSES_			16

#define TX_0_PIN_			12
#define TX_1_PIN_			13

typedef struct{

	gpioPulse_t pulseInfo[NO_PULSES_];
	int pin;
	uint32_t wid;
}Transducer_t;

Transducer_t tx0;
Transducer_t tx1;

Transducer_t *transducer[2];

void Transducer_construct(Transducer_t *transducer, int pin, int onTime, int offTime);
void Transducer_excite(Transducer_t *transducer);
void Transducer_disable(Transducer_t *transducer); 
void Transducer_config(void);