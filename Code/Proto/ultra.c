#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <pthread.h>

#include <pigpio.h>

#define TX_1_PIN_		13
#define ADC_TIME_		100

int RUN_THREAD_	= 1;
int run=1;
int spiHandle;

int recData;

char dataBuf[2] = {0x00, 0x00};
char recBuf[2] = {0x00, 0x00};


void stop(int signum){
   run = 0; 
   RUN_THREAD_ = 0;
}

static void *adcThread(void *threadArg){

	printf("in thread\n");
	while(RUN_THREAD_){

		spiXfer(spiHandle, dataBuf, recBuf, 2);

		recData = 0;
		recData |= (((recBuf[0] & 0x0F) << 8 ) | recBuf[1]);

		if(recData > 100){

		printf("%i\n", recData);

		}

	}

	return NULL;
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

int adcRead(void){   	

	spiXfer(spiHandle, dataBuf, recBuf, 2);

	recData = 0;
	recData |= (((recBuf[0] & 0x0F) << 8 ) | recBuf[1]);

	return recData;
}

int main(int argc, char** argv)
{

   if(gpioInitialise() < 0) return -1;   


   setSignalHandler(SIGINT, stop);

   //SPI setup

   spiHandle = spiOpen(0, 1000000, 3);


   if(spiHandle < 0) return -1;

   pthread_t t;


   //Construct the excitation signal

   gpioWaveClear();
   Exciter_construct(TX_1_PIN_, 16, 13, 12); 
   uint32_t wid = gpioWaveCreate();

   pthread_create(&t, NULL, adcThread, NULL);

   while(run){

	gpioWaveTxSend(wid, PI_WAVE_MODE_ONE_SHOT);

		
	printf("delay\n");
	time_sleep(1);
   }

   printf("\ntidying up\n");

   pthread_join(t, NULL);
   spiClose(spiHandle);
   gpioWrite(13, 0);

   gpioTerminate();
}