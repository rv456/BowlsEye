/*!
 * @file trandducer.c
 */

#include "transducer.h"

/*!
 * Constructor for Transducer_t
 * @param transducer				Instance of Transducer_t
 * @param pin						Pin to enable excitation signal
 * @param onTime					On duration of pulse
 * @param offTime					Off duration of pulse
 */
void Transducer_construct(Transducer_t *transducer, int pin, int onTime, int offTime){

	transducer->pin = pin;

	for (int i=0; i<NO_PULSES_; i+=2){

		transducer->pulseInfo[i].gpioOn = 1<<(transducer->pin);
		transducer->pulseInfo[i].gpioOff = 0;
                transducer->pulseInfo[i].usDelay = onTime;

		transducer->pulseInfo[i+1].gpioOn = 0;
                transducer->pulseInfo[i+1].gpioOff = 1<<(transducer->pin);
                transducer->pulseInfo[i+1].usDelay = offTime;

        }

        gpioWaveAddGeneric(NO_PULSES_, transducer->pulseInfo);

	transducer->wid = gpioWaveCreate();
}

/*!
 * Excite a transducer
 * @param transducer			Instance of Transducer_t
 */
void Transducer_excite(Transducer_t *transducer){

	gpioWaveTxSend(transducer->wid, PI_WAVE_MODE_ONE_SHOT);
}

/*!
 * Disable a transducer
 * @param transducer			Instance of Transducer_t
 */
void Transducer_disable(Transducer_t *transducer){

	gpioWrite(transducer->pin, 0);
}

/*!
 * Configure the global Transducer_t's
 */
void Transducer_config(void){


	Transducer_construct(&tx0, TX_0_PIN_, 13, 12);
	Transducer_construct(&tx1, TX_1_PIN_, 13, 12);

	transducer[0] = &tx0;
	transducer[1] = &tx1;
}

