#include <string.h>
#include "stepperMotor.h"

int RUN = 1;

void exitHandler(int s){
	
	RUN = 0;
}

int main(int argc, char** argv)
{

	struct sigaction sigIntHandler;

	sigIntHandler.sa_handler = exitHandler;
	sigemptyset(&sigIntHandler.sa_mask);
	sigIntHandler.sa_flags = 0;

	sigaction(SIGINT, &sigIntHandler, NULL);

    pi = pigpio_start(NULL, NULL);

    if (pi < 0) return -1;
   
    StepperMotor_construct(&stepper);

   
    while(RUN){  

		StepperMotor_incrementStep(&stepper);

    }

    printf("\ntidying up\n");

	StepperMotor_disable(&stepper);

    pigpio_stop(pi);

    return 0;
}
