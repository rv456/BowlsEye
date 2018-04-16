/*!
 * @file thread.h
 *
 * 
 * @author Harvey Leicester
 */

#ifndef THREAD_H_
#define THREAD_H_

#include <pthread.h>
#include "bluetoothController.h"
#include "led.h"

int RUN_BLUETOOTH_LED_THREAD_ = 1;
int RUN_BLUETOOTH_LISTENER_THREAD_ = 1;

pthread_t t_btIndicator;
pthread_t t_btListener;

/*!
 * Bluetooth status indicator thread
 *
 * Toggles @ref bluetoothIndicatorLED while Bluetooth connections are being established
 * @param threadArg				Instance of LED_t
 */
static void* bluetoothStatusIndicator(void *threadArg){

	LED_t *localLED = (LED_t *)threadArg;

	while(RUN_BLUETOOTH_LED_THREAD_){

		printf("waiting for bluetooth connection...\n");
		LED_toggle(localLED, 0.2);
	}

	LED_high(localLED);
	return NULL;
}

/*!
 * Thread for listening Bluetooth data
 * @param threadArg				Instance of BluetoothServer_t
 */
static void *bluetoothListener(void *threadArg){

	BluetoothServer_t *localServer = (BluetoothServer_t *)threadArg;


	printf("in bluetooth listener thread\n");
	while(RUN_BLUETOOTH_LISTENER_THREAD_){

		BluetoothServer_receiveParams(localServer, USER_PARAMS_, 4);
	}

	printf("closing bluetooth listener thread\n");

	return NULL;
}

#endif /* THREAD_H_ */

