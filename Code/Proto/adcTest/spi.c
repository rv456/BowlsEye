#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <pigpio.h>

#define TX_1_PIN_			13

int RUN_MAIN_THREAD_ = 1;

void stop(int signum){
   RUN_MAIN_THREAD_ = 0;
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

   	printf("gpio ok\n");

   	setSignalHandler(SIGINT, stop);


	int spiHandle = spiOpen(0, 16000000, 3);
   	if(spiHandle < 0) return -1;


	char txBuf[2] = {0xAA, 0xAA};
	char rxBuf[2] = {0x00, 0x00};

	while(RUN_MAIN_THREAD_){

		spiXfer(spiHandle, txBuf, rxBuf, 2);

	}

	spiClose(spiHandle);
}