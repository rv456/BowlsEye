#include <pthread.h>
#include "bluetoothController.h"

uint8_t RUN_THREAD_ = 1;

uint16_t BLUETOOTH_DATA_[4];

pthread_t t;

static void* blueToothThread(void *threadArg){

//	BluetoothServer_t *localInst = (BluetoothServer_t*)threadArg;
//	printf("in thread\n");

	while(RUN_THREAD_){

		printf("waiting for bluetooth connection...\n");
//		BluetoothServer_readChar(localInst);
	}

	printf("closed thread\n");

	return NULL;
}
