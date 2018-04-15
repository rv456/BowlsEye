/*!
 * @file stepperMotor.c
 *
 * 
 * @author Harvey Leicester
 */

#include "stepperMotor.h"
#include <pthread.h>


pthread_mutex_t usrParamLock = PTHREAD_MUTEX_INITIALIZER;

void initMutexes(void){

	

}

/*!
 * Constructor for StepperMotor_t
 * @param stepper			Instance of StepperMotor_t
 * @param multiple			Multiple of minimum step angle (0.9deg), defines angular resolution of system
 */
void StepperMotor_construct(StepperMotor_t *stepper){

	stepper->pinEnA = PIN_EN_A_;
	stepper->pinEnB = PIN_EN_B_;
	stepper->pinA0 = PIN_IN_1_;
	stepper->pinA1 = PIN_IN_2_;
	stepper->pinB0 = PIN_IN_3_;
	stepper->pinB1 = PIN_IN_4_;

	gpioSetMode(stepper->pinEnA, PI_OUTPUT);
	gpioSetMode(stepper->pinEnB, PI_OUTPUT);
	gpioSetMode(stepper->pinA0, PI_OUTPUT);
	gpioSetMode(stepper->pinA1, PI_OUTPUT);
	gpioSetMode(stepper->pinB0, PI_OUTPUT);
	gpioSetMode(stepper->pinB1, PI_OUTPUT);

	stepper->step[0] = StepperMotor_step0;
	stepper->step[1] = StepperMotor_step1;
	stepper->step[2] = StepperMotor_step2;
	stepper->step[3] = StepperMotor_step3;

	stepper->currentStep = 0;
	stepper->totalSteps = 0;
	stepper->waitTime = STEP_DELAY_;	

	stepper->stepMultiple = &(USER_PARAMS_[2]);
	stepper->direction = DIRECTION_CLOCKWISE_;

	StepperMotor_enable(stepper);
}

/*!
 * Update the stepper motor position
 * @param stepper			Instance of StepperMotor_t
 */
void StepperMotor_update(StepperMotor_t *stepper){

	if(stepper->direction == DIRECTION_CLOCKWISE_){

		pthread_mutex_lock(&usrParamLock);
		for(uint8_t i=0; i<*(stepper->stepMultiple); i++){

			StepperMotor_incrementStep(stepper);
			time_sleep(stepper->waitTime);
		}
		pthread_mutex_unlock(&usrParamLock);
	}
	else{

		pthread_mutex_lock(&usrParamLock);
		for(uint8_t i=0; i<*(stepper->stepMultiple); i++){

			StepperMotor_decrementStep(stepper);
			time_sleep(stepper->waitTime);
		}
		pthread_mutex_lock(&usrParamLock);
	}
}

/*!
 * Set the size of the motor step increment, defines the angular resolution of the system
 * @param stepper			Instance of StepperMotor_t
 * @param multiple			Multiple of minimum step increment (0.9deg)
 */
void StepperMotor_setStepSize(StepperMotor_t *stepper, int *multiple){

	stepper->stepMultiple = multiple;
}

/*!
 * Set the rotational direction of the motor
 * @param stepper			Instance of StepperMotor_t
 * @param direction			Direction to assign
 */
void StepperMotor_setDirection(StepperMotor_t *stepper, uint8_t direction){

	stepper->direction = direction;
}

/*!
 * Enable the stepper motor
 * @param stepper			Instance of StepperMotor_t
 */
void StepperMotor_enable(StepperMotor_t *stepper){

	gpioWrite(stepper->pinEnA, 1);
	gpioWrite(stepper->pinEnB, 1);

	gpioWrite(stepper->pinA0, 0);
	gpioWrite(stepper->pinA1, 0);
	gpioWrite(stepper->pinB0, 0);
	gpioWrite(stepper->pinB1, 0);
}

/*!
 * Disable the stepper motor
 * @param stepper			Instance of StepperMotor_t
 */
void StepperMotor_disable(StepperMotor_t *stepper){

	gpioWrite(stepper->pinEnA, 0);
	gpioWrite(stepper->pinEnB, 0);

	gpioWrite(stepper->pinA0, 0);
	gpioWrite(stepper->pinA1, 0);
	gpioWrite(stepper->pinB0, 0);
	gpioWrite(stepper->pinB1, 0);
}

/*!
 * Enable the A H bridge of the stepper motor driver
 * @param stepper
 */
void StepperMotor_enA(StepperMotor_t *stepper){

	gpioWrite(stepper->pinEnA, 1);
}

/*!
 * Enable the B H bridge of the stepper motor driver
 * @param stepper
 */
void StepperMotor_enB(StepperMotor_t *stepper){

	gpioWrite(stepper->pinEnB, 1);
}

/*!
 * Increment the current step of the motor
 * @param stepper			Instance of StepperMotor_t
 */
void StepperMotor_incrementStep(StepperMotor_t *stepper){

	stepper->step[stepper->currentStep](stepper);

	stepper->currentStep++;
	stepper->totalSteps++;
	StepperMotor_wrapStep(stepper);
}

/*!
 * Decrement the current step of the motor
 * @param stepper			Instance of StepperMotor_t
 */
void StepperMotor_decrementStep(StepperMotor_t *stepper){

	stepper->step[stepper->currentStep](stepper);
	stepper->currentStep--;
	stepper->totalSteps--;
	StepperMotor_wrapStep(stepper);
}

/*!
 * Wrap current step of motor at limits
 * @param stepper			Instance of StepperMotor_t
 */
void StepperMotor_wrapStep(StepperMotor_t *stepper){

	if(stepper->currentStep >= NO_STEPS_){
		stepper->currentStep = 0;
	}

	if(stepper->currentStep < 0){
		stepper->currentStep = NO_STEPS_ - 1;
	}
}


void StepperMotor_zero(StepperMotor_t *stepper){


	while(stepper->totalSteps > 0){

		StepperMotor_decrementStep(stepper);
		time_sleep(stepper->waitTime);
	}

	while(stepper->totalSteps < 0){

		StepperMotor_incrementStep(stepper);
		time_sleep(stepper->waitTime);
	}
}

/*!
 * Method for performing a step
 * @param stepper			Instance of StepperMotor_t
 */
void StepperMotor_step0(StepperMotor_t *stepper){

	gpioWrite(stepper->pinA0, 0);
	gpioWrite(stepper->pinA1, 1);
	gpioWrite(stepper->pinB0, 1);
	gpioWrite(stepper->pinB1, 0);
}

/*!
 * Method for performing a step
 * @param stepper			Instance of StepperMotor_t
 */
void StepperMotor_step1(StepperMotor_t *stepper){

	gpioWrite(stepper->pinA0, 0);
	gpioWrite(stepper->pinA1, 1);
	gpioWrite(stepper->pinB0, 0);
	gpioWrite(stepper->pinB1, 1);
}

/*!
 * Method for performing a step
 * @param stepper			Instance of StepperMotor_t
 */
void StepperMotor_step2(StepperMotor_t *stepper){

	gpioWrite(stepper->pinA0, 1);
	gpioWrite(stepper->pinA1, 0);
	gpioWrite(stepper->pinB0, 0);
	gpioWrite(stepper->pinB1, 1);
}

/*!
 * Method for performing a step
 * @param stepper			Instance of StepperMotor_t
 */
void StepperMotor_step3(StepperMotor_t *stepper){

	gpioWrite(stepper->pinA0, 1);
	gpioWrite(stepper->pinA1, 0);
	gpioWrite(stepper->pinB0, 1);
	gpioWrite(stepper->pinB1, 0);
}

