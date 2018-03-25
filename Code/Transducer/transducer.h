/*!
 * @file transducer.h
 *
 * 
 * @author Harvey Leicester
 */

#ifndef TRANSDUCER_H_
#define TRANSDUCER_H_

#include <pigpiod_if2.h>
#include "globals.h"

#define TRANSDUCER_FRES_				40000
#define HALF_DUTY_CYCLE_				128

/*!
 * @brief Structure for interfacing with ultrasound transducer
 */
typedef struct{

	int txPin;					/*!<Pin used to drive transducer*/
	double timeStamp;			/*!<Time stamp for determining distance*/
}Transducer_t;

void Transducer_construct(Transducer_t *transducer, int pin);
double Transducer_excite(Transducer_t *transducer);

#endif /* TRANSDUCER_H_ */

