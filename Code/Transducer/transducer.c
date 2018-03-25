/*!
 * @file transducer.c
 *
 * 
 * @author Harvey Leicester
 */

#include "transducer.h"

/*!
 * Constructor for Transducer_t
 * @param transducer			Instance of Transducer_t
 * @param pin					Pin used to drive transducer
 */
void Transducer_construct(Transducer_t *transducer, int pin){

	transducer->txPin = pin;
	transducer->timeStamp = 0;
	set_PWM_frequency(pi, transducer->txPin, TRANSDUCER_FRES_);
	set_PWM_dutycycle(pi, transducer->txPin, HALF_DUTY_CYCLE_);
	gpio_write(pi, transducer->txPin, 0);
}

/*!
 * Excite/drive the transducer
 * @param transducer			Instance of Transducer_t
 * @return						Time of excitation
 */
double Transducer_excite(Transducer_t *transducer){

	transducer->timeStamp = time_time();
	set_PWM_dutycycle(pi, transducer->txPin, HALF_DUTY_CYCLE_);
	gpio_write(pi, transducer->txPin, 0);

	return (transducer->timeStamp);
}

