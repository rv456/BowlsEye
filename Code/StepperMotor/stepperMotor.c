#include "stepperMotor.h"

void StepperMotor_construct(StepperMotor_t *stepper){
	
	stepper->pinEnA = PIN_EN_A;
	stepper->pinEnB = PIN_EN_B;
	stepper->pinA0 = PIN_IN_1;
	stepper->pinA1 = PIN_IN_2;
	stepper->pinB0 = PIN_IN_3;
	stepper->pinB1 = PIN_IN_4;
	
	stepper->step[0] = StepperMotor_step0;
	stepper->step[1] = StepperMotor_step1;
	stepper->step[2] = StepperMotor_step2;
	stepper->step[3] = StepperMotor_step3;

	stepper->currentStep = 0;
	stepper->waitTime = STEP_DELAY;
	
	StepperMotor_enable(stepper);
}

void StepperMotor_enable(StepperMotor_t *stepper){
	
	gpio_write(pi, stepper->pinEnA, 1);
    gpio_write(pi, stepper->pinEnB, 1);
   
    gpio_write(pi, stepper->pinA0, 0);
    gpio_write(pi, stepper->pinA1, 0);
    gpio_write(pi, stepper->pinB0, 0);
    gpio_write(pi, stepper->pinB1, 0); 
}

void StepperMotor_disable(StepperMotor_t *stepper){
	
	gpio_write(pi, stepper->pinEnA, 0);
    gpio_write(pi, stepper->pinEnB, 0);
   
    gpio_write(pi, stepper->pinA0, 0);
    gpio_write(pi, stepper->pinA1, 0);
    gpio_write(pi, stepper->pinB0, 0);
    gpio_write(pi, stepper->pinB1, 0); 
}

void StepperMotor_incrementStep(StepperMotor_t *stepper){
	
	stepper->step[stepper->currentStep](stepper);
	
	time_sleep(stepper->waitTime);
	stepper->currentStep++;
	
	StepperMotor_wrapStep(stepper);	
}

void StepperMotor_setStep(StepperMotor_t *stepper, uint8_t step){
	
	stepper->currentStep = step;
	
	StepperMotor_wrapStep(stepper);
}
void StepperMotor_setAngle(StepperMotor_t *stepper, uint8_t angle){
	
	/*
	 * ToDo: FIGURE THIS OUT!!
	 *
	 */
	
}

void StepperMotor_wrapStep(StepperMotor_t *stepper){
	
	if(stepper->currentStep >= NO_STEPS){
		stepper->currentStep = 0;
	}
}

void StepperMotor_step0(StepperMotor_t *stepper){
	
	gpio_write(pi, stepper->pinA0, 0);
    gpio_write(pi, stepper->pinA1, 1);
    gpio_write(pi, stepper->pinB0, 1);
    gpio_write(pi, stepper->pinB1, 0);
}

void StepperMotor_step1(StepperMotor_t *stepper){
	
    gpio_write(pi, stepper->pinA0, 0);
    gpio_write(pi, stepper->pinA1, 1);
    gpio_write(pi, stepper->pinB0, 0);
    gpio_write(pi, stepper->pinB1, 1);	
}

void StepperMotor_step2(StepperMotor_t *stepper){
	
    gpio_write(pi, stepper->pinA0, 1);
    gpio_write(pi, stepper->pinA1, 0);
    gpio_write(pi, stepper->pinB0, 0);
    gpio_write(pi, stepper->pinB1, 1);	
}

void StepperMotor_step3(StepperMotor_t *stepper){
	
	gpio_write(pi, stepper->pinA0, 1);
    gpio_write(pi, stepper->pinA1, 0);
    gpio_write(pi, stepper->pinB0, 1);
    gpio_write(pi, stepper->pinB1, 0);
}
