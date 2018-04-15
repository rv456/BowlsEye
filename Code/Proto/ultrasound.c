#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <pigpio.h>

#include "adc.h"
//#include "bluetoothController.h"
#include "stepperMotor.h"
#include "thread.h"
//#include "globals.h"
#include <string.h>

#define TX_1_PIN_			13

int RUN_MAIN_THREAD_ = 1;
int RUN_ADC_THREAD_ = 0;

void stop(int signum){
   	RUN_MAIN_THREAD_ = 0;
	RUN_ADC_THREAD_ = 0;
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

void Exciter_construct(int pin, int noPulses, int onTime, int offTime){

	gpioPulse_t pulseInfo[noPulses];

        for (int i=0; i<noPulses; i+=2){

		pulseInfo[i].gpioOn = 1<< pin;
		pulseInfo[i].gpioOff = 0;
                pulseInfo[i].usDelay = onTime;

		pulseInfo[i+1].gpioOn = 0;
                pulseInfo[i+1].gpioOff = 1<<pin;
                pulseInfo[i+1].usDelay = offTime;

        }

        gpioWaveAddGeneric(noPulses, pulseInfo);
}

int main(int argc, char** argv){

   	if(gpioInitialise() < 0) return -1;   

  	printf("gpio ok\n");

   	setSignalHandler(SIGINT, stop);

   	//globals_config();

   	//SPI setup

   	//int spiHandle = spiOpen(0, 16000000, 3);
   	//if(spiHandle < 0) return -1;

   	//ADCController_construct(&adcController, spiHandle);

   	//printf("spi ok\n");

	StepperMotor_construct(&stepper);

   	//pthread_create(&t_btIndicator, NULL, bluetoothStatusIndicator, NULL);

   	BluetoothServer_construct(&server);
   	BluetoothClient_construct(&client);

   	//RUN_BLUETOOTH_LED_THREAD_ = 0;
   	//pthread_join(t_btIndicator, NULL);

	printf("bluetooth all good\n");


	pthread_create(&t_btListener, NULL, bluetoothListener, &server);



   	//Construct the excitation signal

   	//gpioWaveClear();
   	//Exciter_construct(TX_1_PIN_, 16, 13, 12); 
   	//uint32_t wid = gpioWaveCreate();

   	//double sample = 0;
   	//double timeStamp = 0;
	double distance = 0;
	

	while(RUN_MAIN_THREAD_){


		
		if(USER_PARAMS_[0] == 1){

			USER_PARAMS_[0] = 0; //reset trigger
			
			while(stepper.totalSteps < MAX_STEPS_){
	
				//gpioWaveTxSend(wid, PI_WAVE_MODE_ONE_SHOT);
//				double startTime = gpioTick();

				/*for(int i=0; i<BUFFER_SIZE_; i++){
					ADCController_read(&adcController);
					FIFO_push(BUFFER_[TIME_STAMP_INDEX_], gpioTick());
					FIFO_push(BUFFER_[ADC_VAL_INDEX_], adcController.adcVal);

	      			}*/


				/*for(int i=0; i<BUFFER_SIZE_; i++){

					FIFO_pop(BUFFER_[ADC_VAL_INDEX_], &sample);
					FIFO_pop(BUFFER_[TIME_STAMP_INDEX_], &timeStamp);

					timeStamp -= startTime;

					timeStamp = timeStamp / 1000000;
					//printf("timestamp tick %f\n", timeStamp);

					if((sample > 86.0) && (timeStamp > 0.0005)){

						break;
					}*/
				//}

				time_sleep(0.003);

				printf("angle = %f\n", stepper.totalSteps * 0.9);

				distance += 0.02;

				if(distance > 1.0){

					distance = 0;
				}

				BluetoothClient_sendDoubleAsStr(&client, distance, stepper.totalSteps * 0.9);
				//BluetoothClient_sendDoubleAsStr(&client, stepper.totalSteps * 0.9);
				
				StepperMotor_update(&stepper);

			}//while

			StepperMotor_zero(&stepper);

			BluetoothClient_sendString(&client, "complete", 8); 

		}//if


	}//while

   	printf("tidying up\n");

//	spiClose(adcController.spiHandle);

   	StepperMotor_disable(&stepper);

	pthread_join(t_btListener, NULL);
	BluetoothServer_disable(&server);
	BluetoothClient_disable(&client);

   	//gpioWrite(13, 0);

   	gpioTerminate();
}//main
