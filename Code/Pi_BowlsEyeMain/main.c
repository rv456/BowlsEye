#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <pigpio.h>

#include "adc.h"
#include "stepperMotor.h"
#include "thread.h"
#include "transducer.h"

int RUN_MAIN_THREAD_ = 1;

void stop(int signum){
   	RUN_MAIN_THREAD_ = 0;
	RUN_BLUETOOTH_LED_THREAD_ = 0;
	RUN_BLUETOOTH_LISTENER_THREAD_ = 0;

}

typedef void (*signalFunc_t) (int signum);

static void setSignalHandler(int signum, signalFunc_t sigHandler)
{
   	struct sigaction new;

   	memset(&new, 0, sizeof(new));
	new.sa_handler = sigHandler;

	sigaction(signum, &new, NULL);
}

int main(int argc, char** argv){

   	if(gpioInitialise() < 0) return -1;   

   	setSignalHandler(SIGINT, stop);


	int TEMP_ADC_BUFFER_SIZE_ = MAX_BYTE_BUFFER_SIZE_;
   	
	//SPI setup

   	int spiHandle = spiOpen(0, 8000000, 3);			//500KHz sampling rate
   	if(spiHandle < 0) return -1;

   	ADCController_construct(&adcController, spiHandle, TEMP_ADC_BUFFER_SIZE_);

	StepperMotor_construct(&stepper);

	LED_construct(&bluetoothIndicatorLED, 4);

   	pthread_create(&t_btIndicator, NULL, bluetoothStatusIndicator, &bluetoothIndicatorLED);

   	BluetoothServer_construct(&server);
   	BluetoothClient_construct(&client);

   	RUN_BLUETOOTH_LED_THREAD_ = 0;
   	pthread_join(t_btIndicator, NULL);

	printf("bluetooth all good\n");

	//start bluetooth listener thread
	pthread_create(&t_btListener, NULL, bluetoothListener, &server);



   	//Construct the excitation signals
	Transducer_config();

   	double timeStamp = 0;
	double distance = 0;

	


	while(RUN_MAIN_THREAD_){
		
		if(USER_PARAMS_[0] == 1){		//wait for trigger

			USER_PARAMS_[0] = 0; //reset trigger
			
			while(stepper.totalSteps < MAX_STEPS_/2){

				for(uint8_t currentChannel=0; currentChannel<2; currentChannel++){
				
					Transducer_excite(transducer[currentChannel]);		//send excitation signal
	
					ADCController_update(&adcController);				//sample reflected wave

					ADCController_convertToInt(&adcController, RAW_ADC_BUFFER_);	//convert to integer values

					for(int i=0; i<MAX_BYTE_BUFFER_SIZE_/2; i++){

						if(RAW_ADC_BUFFER_[i] > 100.0 && i > 300){		

							timeStamp = i;
						}
					}

					distance = (((timeStamp)/(500000)) * 343.0)/2.0;

					BluetoothClient_sendDoubleAsStr(&client, distance, ((stepper.totalSteps * 0.9)+(currentChannel*180)));

				}

				StepperMotor_update(&stepper);
				time_sleep(0.05);

			}

			StepperMotor_zero(&stepper);
			BluetoothClient_sendString(&client, "complete", 8); 
		}

	}

   	printf("tidying up\n");
	pthread_join(t_btListener, NULL);
	spiClose(adcController.spiHandle);
   	StepperMotor_disable(&stepper);
	BluetoothServer_disable(&server);
	BluetoothClient_disable(&client);
	Transducer_disable(transducer[0]);
	Transducer_disable(transducer[1]);
	LED_low(&bluetoothIndicatorLED);
  
   	gpioTerminate();
}
