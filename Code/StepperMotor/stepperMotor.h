#ifndef __STEPPERMOTOR_H_
#define __STEPPERMOTOR_H_

#include <pigpiod_if2.h>

#include "globals.h"

#define NO_STEPS				4
#define STEP_DELAY				0.005

#define PIN_IN_1				2
#define PIN_IN_2				3
#define PIN_IN_3				4
#define PIN_IN_4				17
#define PIN_EN_A				27
#define PIN_EN_B				22

typedef struct StepperMotor_t StepperMotor_t;

struct StepperMotor_t{
	
	void (*step[NO_STEPS])(StepperMotor_t *stepper);
	uint8_t pinEnA, pinEnB, pinA0, pinA1, pinB0, pinB1;
	int8_t currentStep;
	double waitTime;
};

StepperMotor_t stepper;

void StepperMotor_construct(StepperMotor_t *stepper);
void StepperMotor_enable(StepperMotor_t *stepper);
void StepperMotor_disable(StepperMotor_t *stepper);
void StepperMotor_incrementStep(StepperMotor_t *stepper);
void StepperMotor_setStep(StepperMotor_t *stepper, uint8_t step);
void StepperMotor_setAngle(StepperMotor_t *stepper, uint8_t angle);
void StepperMotor_wrapStep(StepperMotor_t *stepper);

void StepperMotor_step0(StepperMotor_t *stepper);
void StepperMotor_step1(StepperMotor_t *stepper);
void StepperMotor_step2(StepperMotor_t *stepper);
void StepperMotor_step3(StepperMotor_t *stepper);

#endif
