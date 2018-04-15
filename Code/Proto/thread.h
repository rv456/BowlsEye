#include <pthread.h>
#include "bluetoothController.h"

int RUN_BLUETOOTH_LED_THREAD_ = 1;
int RUN_BLUETOOTH_LISTENER_THREAD_ = 1;

pthread_t t_btIndicator;
pthread_t t_btListener;


static void* bluetoothStatusIndicator(void *threadArg){

	while(RUN_BLUETOOTH_LED_THREAD_){

		printf("waiting for bluetooth connection...\n");
	}

	return NULL;
}

static void *bluetoothListener(void *threadArg){

	BluetoothServer_t *localServer = (BluetoothServer_t *)threadArg;


	printf("in bluetooth listener thread\n");
	while(RUN_BLUETOOTH_LISTENER_THREAD_){

		BluetoothServer_receiveParams(localServer, USER_PARAMS_, 4);
	}

	printf("closing bluetooth listener thread\n");

	return NULL;
}
