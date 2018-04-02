#include <pthread.h>
#include "bluetoothController.h"

uint8_t RUN_THREAD_ = 1;

pthread_t t;

static void* blueToothThread(void *threadArg){
	
	BluetoothServer_t *localInst = (BluetoothServer_t*)threadArg;
	printf("in thread\n");
	
	while(RUN_THREAD_){
	
		BluetoothServer_readInt(localInst, BLUETOOTH_DATA_);
	}
	
	printf("closed thread\n");
	
	return NULL;
}
