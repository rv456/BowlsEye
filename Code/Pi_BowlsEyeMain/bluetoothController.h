#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

extern char PC_ADDRESS_[18];

/*!
 * @brief Structure for implementing a Bluetooth server
 */
typedef struct{

	struct sockaddr_rc locAddr;			/*!<local address*/
	struct sockaddr_rc remAddr;			/*!<remote address*/
	char buf[1024];						/*!<buffer for storing bluetooth address*/
	int sock, client;					/*!<socket and client*/
	char recData[1024];					/*!<received data buffer*/
	socklen_t opt;						/*!<socket info*/
}BluetoothServer_t;

/*!
 * @brief Structure for implementing a Bluetooth client
 */
typedef struct{

	struct sockaddr_rc addr;			/*!<socket info*/
	int sock, status;					/*!<socket and status for error checking*/
	char *dst;							/*!<server bluetooth address*/
	char txData[16];					/*!<buffer of data to send*/
}BluetoothClient_t;

BluetoothServer_t server;
BluetoothClient_t client;

void BluetoothServer_construct(BluetoothServer_t *server);
void BluetoothServer_enable(BluetoothServer_t *server);
void BluetoothServer_disable(BluetoothServer_t *server);
int BluetoothServer_readString(BluetoothServer_t *server);
void BluetoothServer_receiveParams(BluetoothServer_t *server, int *dst, int size);


void BluetoothClient_construct(BluetoothClient_t *client);
void BluetoothClient_enable(BluetoothClient_t *client);
void BluetoothClient_disable(BluetoothClient_t *client);
void BluetoothClient_sendString(BluetoothClient_t *client, char *data, int size);
void BluetoothClient_sendDoubleAsStr(BluetoothClient_t *client, double data0, double data1);
void BluetoothClient_checkError(BluetoothClient_t *client);



