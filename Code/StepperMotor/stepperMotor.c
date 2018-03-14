#include "stepperMotor.h"

void StepperMotor_construct(StepperMotor_t *stepper, uint8_t multiple){
	
	stepper->pinEnA = PIN_EN_A_;
	stepper->pinEnB = PIN_EN_B_;
	stepper->pinA0 = PIN_IN_1_;
	stepper->pinA1 = PIN_IN_2_;
	stepper->pinB0 = PIN_IN_3_;
	stepper->pinB1 = PIN_IN_4_;
	
	stepper->step[0] = StepperMotor_step0;
	stepper->step[1] = StepperMotor_step1;
	stepper->step[2] = StepperMotor_step2;
	stepper->step[3] = StepperMotor_step3;

	stepper->currentStep = 0;
	stepper->waitTime = STEP_DELAY_;
	
	stepper->stepMultiple = multiple;
	stepper->direction = DIRECTION_CLOCKWISE_;
	
	StepperMotor_enable(stepper);
}

void StepperMotor_update(StepperMotor_t *stepper){
	
	if(stepper->direction == DIRECTION_CLOCKWISE_){
		
		for(uint8_t i=0; i<stepper->stepMultiple; i++){
			
			StepperMotor_incrementStep(stepper);
			time_sleep(stepper->waitTime);
		}		
	}
	else{
		
		for(uint8_t i=0; i<stepper->stepMultiple; i++){
			
			StepperMotor_decrementStep(stepper);
			time_sleep(stepper->waitTime);
		}
	}
}

void StepperMotor_setStepSize(StepperMotor_t *stepper, uint8_t multiple){
	
	stepper->stepMultiple = multiple;
}

void StepperMotor_setDirection(StepperMotor_t *stepper, uint8_t direction){
	
	stepper->direction = direction;
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

void StepperMotor_enA(StepperMotor_t *stepper){
	
	gpio_write(pi, stepper->pinEnA, 1);
}

void StepperMotor_enB(StepperMotor_t *stepper){
	
	gpio_write(pi, stepper->pinEnB, 1);
}

void StepperMotor_incrementStep(StepperMotor_t *stepper){
	
	stepper->step[stepper->currentStep](stepper);

	stepper->currentStep++;
	
	StepperMotor_wrapStep(stepper);	
}

void StepperMotor_decrementStep(StepperMotor_t *stepper){
	
	stepper->step[stepper->currentStep](stepper);
	stepper->currentStep--;
	
	StepperMotor_wrapStep(stepper);
}

void StepperMotor_wrapStep(StepperMotor_t *stepper){
	
	if(stepper->currentStep >= NO_STEPS_){
		stepper->currentStep = 0;
	}
	
	if(stepper->currentStep < 0){
		stepper->currentStep = NO_STEPS_ - 1;
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
