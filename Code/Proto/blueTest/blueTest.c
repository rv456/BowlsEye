#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include "thread.h"
//#include <pigpio.h>

//#include "bluetoothController.h"

//#define TX_1_PIN_			13

int RUN_MAIN_THREAD_ = 1;

void stop(int signum){
   RUN_MAIN_THREAD_ = 0;
   RUN_THREAD_ = 0;
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

	setSignalHandler(SIGINT, stop);


	pthread_create(&t, NULL, blueToothThread, NULL);


	BluetoothServer_t server;

	BluetoothServer_construct(&server);

        RUN_THREAD_ = 0;
        pthread_join(t, NULL);


        BluetoothClient_t client;

	BluetoothClient_construct(&client);

	int recDataConverted = 0;

	char *token;

	char raw[8];
	double distance = 3.14;

	//uint16_t recData[10] = {0};

	while(RUN_MAIN_THREAD_){

		BluetoothServer_readChar(&server);

		token= strtok(server.recData, ",");

		while(token != NULL){

			recDataConverted = atoi(token);

			printf("%i\n", recDataConverted);

			token = strtok(NULL, ",");

		}

	for(int i=0; i<20; i++){
	sprintf(raw, "%f", distance*i);
   	BluetoothClient_sendString(&client, raw, 8); 
	}

	}

//        pthread_join(t, NULL);

	BluetoothServer_disable(&server);
}
