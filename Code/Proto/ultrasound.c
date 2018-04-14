#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <pigpio.h>

#include "adc.h"
#include "bluetoothController.h"
#include "stepperMotor.h"
#include "globals.h"
#include <string.h>

#define TX_1_PIN_			13

int RUN_MAIN_THREAD_ = 1;
int RUN_ADC_THREAD_ = 0;
int RUN_BLUETOOTH_THREAD_ = 1;

void stop(int signum){
   RUN_MAIN_THREAD_ = 0;
   RUN_ADC_THREAD_ = 0;
   RUN_BLUETOOTH_THREAD_ = 0;

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

static void *ADCThread(void *threadArg){

	ADCController_t *localInst = (ADCController_t *)threadArg;

	while(RUN_ADC_THREAD_){

		ADCController_read(localInst);

			//if(fifo.head == BUFFER_SIZE_-1){
			//	RUN_ADC_THREAD_ = 0;
			//}
                        FIFO_push(BUFFER_[ADC_VAL_INDEX_], localInst->adcVal);
			if(localInst->adcVal > 100){
			printf("%i\n", localInst->adcVal);	
			}
	}

	return NULL;
}

static void *BluetoothThread(void *threadArg){

	BluetoothClient_t *localInst = (BluetoothClient_t *)threadArg;

	double sample = 0;
	char raw[8] = {0};

        while(RUN_BLUETOOTH_THREAD_){

		FIFO_pop(BUFFER_[ADC_VAL_INDEX_], &sample);

		sprintf(raw, "%f", sample);
		BluetoothClient_sendString(localInst, raw, 8);
		

	}

	return NULL;

}

int main(int argc, char** argv)
{

   if(gpioInitialise() < 0) return -1;   

   printf("gpio ok\n");

   setSignalHandler(SIGINT, stop);

   globals_config();

   //SPI setup

   int spiHandle = spiOpen(0, 16000000, 3);
   if(spiHandle < 0) return -1;

   ADCController_construct(&adcController, spiHandle);

   printf("spi ok\n");

   StepperMotor_construct(&stepper, 100);

   pthread_t adcTID;
   //pthread_t blueTID;

   BluetoothClient_t blueClient;

   BluetoothClient_construct(&blueClient);

   //Construct the excitation signal

   gpioWaveClear();
   Exciter_construct(TX_1_PIN_, 16, 13, 12); 
   uint32_t wid = gpioWaveCreate();

   //pthread_create(&blueTID, NULL, BluetoothThread, &blueClient);
	
	double distance = 0;
	double angle = 0;
	double sample = 0;
	double timeStamp = 0;
 
	char raw[8] = {0};

	while(stepper.totalSteps <= MAX_STEPS_){

	gpioWaveTxSend(wid, PI_WAVE_MODE_ONE_SHOT);
	double startTime = gpioTick();

	//pthread_create(&adcTID, NULL, ADCThread, &adcController);


	for(int i=0; i<BUFFER_SIZE_; i++){
		
		ADCController_read(&adcController);
		FIFO_push(BUFFER_[TIME_STAMP_INDEX_], gpioTick());
		FIFO_push(BUFFER_[ADC_VAL_INDEX_], adcController.adcVal);
		
      	}


	for(int i=0; i<BUFFER_SIZE_; i++){

		FIFO_pop(BUFFER_[ADC_VAL_INDEX_], &sample);
		FIFO_pop(BUFFER_[TIME_STAMP_INDEX_], &timeStamp);

		timeStamp -= startTime;

		
		timeStamp = timeStamp / 1000000;
		//printf("timestamp tick %f\n", timeStamp);

		if((sample > 86.0) && (timeStamp > 0.0005)){
 
			break;
		}
	}

	distance = ((343.0 * timeStamp) / 2);
	angle = 0.9 * (stepper.totalSteps);

	printf("Distance = %f\tAngle = %f\n", distance, angle); 


	sprintf(raw, "%f", distance);
   	BluetoothClient_sendString(&blueClient, raw, 8); 

	sprintf(raw, "%f", angle);
   	BluetoothClient_sendString(&blueClient, raw, 8); 
	//time_sleep(0.5);

	StepperMotor_update(&stepper);

	}

//	time_sleep(1);
//	RUN_ADC_THREAD_ = 1;
//	pthread_create(&adcTID, NULL, ADCThread, &adcController);
       


   printf("\ntidying up\n");

   StepperMotor_zero(&stepper);
   //pthread_join(adcTID, NULL);

  // char raw[8] = {0};

   printf("distance! %fcm\n", (distance*100));
   printf("timestamp %f\n", timeStamp);
   printf("sample %f\n", sample);

   //sprintf(raw, "%f", distance);
   //BluetoothClient_sendString(&blueClient, raw, 8);   	
    
   //BUFFER_[ADC_VAL_INDEX_]->head = 0;
  /* for(int i=0; i<BUFFER_SIZE_; i++){
  	FIFO_pop(BUFFER_[ADC_VAL_INDEX_], &sample);

	
	sprintf(raw, "%f", sample);
	BluetoothClient_sendString(&blueClient, raw, 8);   	
    }*/
   
   
   //for(int i=0; i<BUFFER_SIZE_; i++){
  //	FIFO_pop(BUFFER_[TIME_STAMP_INDEX_], &sample);
	
//	printf("%f\n", sample);
//	sprintf(raw, "%f", sample);
//	BluetoothClient_sendString(&blueClient, raw, 8);	
//    }

   //pthread_join(blueTID, NULL);
   spiClose(adcController.spiHandle);

   StepperMotor_disable(&stepper);
   gpioWrite(13, 0);

   gpioTerminate();
}
