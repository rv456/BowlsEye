/*!
 * @file bluetoothController.c
 *
 * 
 * @author Harvey Leicester
 */

#include "bluetoothController.h"

char PC_ADDRESS_[18] = "34:E6:AD:06:21:46";

/*!
 * Constructor for BluetoothServer_t
 * @param server			Instance of BluetoothServer_t
 */
void BluetoothServer_construct(BluetoothServer_t *server){

	server->opt = sizeof(server->remAddr);
	server->sock = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

	server->locAddr.rc_family = AF_BLUETOOTH;
	server->locAddr.rc_bdaddr = *BDADDR_ANY;
	server->locAddr.rc_channel = (uint8_t)1;

	bind(server->sock, (struct sockaddr *)&(server->locAddr), sizeof(server->locAddr));

	for(int i=0; i<1024; i++){

		server->recData[i] = 0;
	}

	BluetoothServer_enable(server);
}

/*!
 * Enablea the Bluetooth server
 * @param server			Instance of BluetoothServer_t
 */
void BluetoothServer_enable(BluetoothServer_t *server){

	listen(server->sock, 1);
	server->client = accept(server->sock, (struct sockaddr *)&(server->remAddr), &server->opt);

	ba2str(&server->remAddr.rc_bdaddr, server->buf);
	fprintf(stderr, "accepted connection from %s\n", server->buf);
	memset(server->buf, 0, sizeof(server->buf));
}

/*!
 * Disables Bluetooth server
 * @param server			Instance of BluetoothServer_t
 */
void BluetoothServer_disable(BluetoothServer_t *server){

	close(server->client);
	close(server->sock);
}

/*!
 * Read integer value(s) from a connected Bluetooth client
 * @param server			Instance of BluetoothServer_t
 * @param dst				Destination of received data
 */
void BluetoothServer_readInt(BluetoothServer_t *server, int *dst){

	int bytesRead = read(server->client, server->recData, sizeof(server->recData));
	if(bytesRead > 0){

		for(uint16_t i=0; i<bytesRead; i++){

			printf("received [%i]\t", (int)(server->recData[i]));
		}

		printf("\n");
		*dst = (int)(server->recData[0]);
	}
}

/*!
 * Read character value(s) from a connected Bluetooth client
 * @param server			Instance of BluetoothServer_t
 * @param dst				Destination of received data
 */
void BluetoothServer_readChar(BluetoothServer_t *server, char *dst){

	int bytesRead = read(server->client, server->recData, sizeof(server->recData));
	if(bytesRead > 0){

		printf("received [%s]", (server->recData));

		printf("\n");
		*dst = (char)(server->recData[0]);
	}
}

/*!
 * constructor for BluetoothClient_t
 * @param client			Instance of BluetoothClient_t
 */
void BluetoothClient_construct(BluetoothClient_t *client){

	client->dst = PC_ADDRESS_;
	client->sock = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

	client->addr.rc_family = AF_BLUETOOTH;
	client->addr.rc_channel = (uint8_t)1;
	str2ba(client->dst, &(client->addr.rc_bdaddr));

	BluetoothClient_enable(client);
}

/*!
 * Enables a Bluetooth client
 * @param client			Instance of BluetoothClient_t
 */
void BluetoothClient_enable(BluetoothClient_t *client){

	client->status = connect(client->sock, (struct sockaddr *)&(client->addr), sizeof(client->addr));
	BluetoothClient_checkError(client);
}

/*!
 * Disables a Bluetooth client
 * @param client			Instance of BluetoothClient_t
 */
void BluetoothClient_disable(BluetoothClient_t *client){

	close(client->sock);
}

/*!
 * Send a string of data to connected Bluetooth server
 * @param client			Instance of bluetoothClient_t
 * @param data				Data to send
 * @param size				Size of data to send
 */
void BluetoothClient_sendString(BluetoothClient_t *client, char *data, int size){

	client->status = write(client->sock, data, size);
	BluetoothClient_checkError(client);
}

/*!
 * Check for errors in status of Bluetooth client
 * @param client			Instance of BluetoothClient_t
 */
void BluetoothClient_checkError(BluetoothClient_t *client){

	if(client->status < 0){
		perror(":(\t");
	}
}









