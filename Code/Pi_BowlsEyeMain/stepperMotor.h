/*!
 * @file stepperMotor.h
 *
 * 
 * @author Harvey Leicester
 */

#ifndef STEPPERMOTOR_H_
#define STEPPERMOTOR_H_

#include <pigpio.h>
#include "globals.h"

#define MAX_STEPS_					400
#define NO_STEPS_					4
#define STEP_DELAY_					0.005


#define DIRECTION_CLOCKWISE_		1
#define DIRECTION_ANTICLOCKWISE_	0

#define PIN_IN_1_					22
#define PIN_IN_2_					27
#define PIN_IN_3_					3
#define PIN_IN_4_					2
#define PIN_EN_A_					14
#define PIN_EN_B_					17

typedef struct StepperMotor_t StepperMotor_t;

/*!
 * Structure for interfacing with stepper motor and its dual H bridge driver
 */
struct StepperMotor_t{

	void (*step[NO_STEPS_])(StepperMotor_t *stepper);   /*!Contains the methods for performing each step<*/
	uint8_t pinEnA, pinEnB, pinA0, pinA1, pinB0, pinB1;	/*!<The pins used to enable the coils of the motor*/
	int8_t currentStep;
	int totalSteps;									/*!<Current step of the motor*/
	double waitTime;									/*!<Time to wait/delay between steps*/
	uint8_t direction;	 					/*!<Rotational direction and angular resolution*/
	int *stepMultiple;
};

StepperMotor_t stepper;

void StepperMotor_construct(StepperMotor_t *stepper);
void StepperMotor_enable(StepperMotor_t *stepper);
void StepperMotor_update(StepperMotor_t *stepper);
void StepperMotor_setDirection(StepperMotor_t *stepper, uint8_t direction);
void StepperMotor_setStepSize(StepperMotor_t *stepper, int *multiple);
void StepperMotor_enA(StepperMotor_t *stepper);
void StepperMotor_enB(StepperMotor_t *stepper);
void StepperMotor_disable(StepperMotor_t *stepper);
void StepperMotor_incrementStep(StepperMotor_t *stepper);
void StepperMotor_decrementStep(StepperMotor_t *stepper);
void StepperMotor_wrapStep(StepperMotor_t *stepper);
void StepperMotor_zero(StepperMotor_t *stepper);


void StepperMotor_step0(StepperMotor_t *stepper);
void StepperMotor_step1(StepperMotor_t *stepper);
void StepperMotor_step2(StepperMotor_t *stepper);
void StepperMotor_step3(StepperMotor_t *stepper);

#endif /* STEPPERMOTOR_H_ */

