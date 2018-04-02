/*!
 * @file bluetoothController.h
 *
 * 
 * @author Harvey Leicester
 */

#ifndef BLUETOOTHCONTROLLER_H_
#define BLUETOOTHCONTROLLER_H_

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

extern char PC_ADDRESS_[18];

/*!
 * Structure for creating a Bluetooth server
 */
typedef struct{

	struct sockaddr_rc locAddr;
	struct sockaddr_rc remAddr;
	char buf[1024];
	int sock, client;
	char recData[1024];
	socklen_t opt;
}BluetoothServer_t;

/*!
 * Structure for creating a Bluetooth client
 */
typedef struct{

	struct sockaddr_rc addr;
	int sock, status;
	char *dst;
}BluetoothClient_t;


void BluetoothServer_construct(BluetoothServer_t *server);
void BluetoothServer_enable(BluetoothServer_t *server);
void BluetoothServer_disable(BluetoothServer_t *server);
void BluetoothServer_readInt(BluetoothServer_t *server, int *dst);
void BluetoothServer_readFloat(BluetoothServer_t *server, float *dst);
void BluetoothServer_readChar(BluetoothServer_t *server, char *dst);

void BluetoothClient_construct(BluetoothClient_t *client);
void BluetoothClient_enable(BluetoothClient_t *client);
void BluetoothClient_disable(BluetoothClient_t *client);
void BluetoothClient_sendString(BluetoothClient_t *client, char *data, int size);
void BluetoothClient_checkError(BluetoothClient_t *client);



#endif /* BLUETOOTHCONTROLLER_H_ */

