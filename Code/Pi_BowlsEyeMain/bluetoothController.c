#include "bluetoothController.h"

char PC_ADDRESS_[18] = "34:E6:AD:06:21:46";  //Harvey
//char PC_ADDRESS_[18] = "A4:17:31:EE:C2:02";   //Calum

/*!
 * Constructor for BluetoothServer_t
 * @param server				Instance of BluetoothServer_t
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
 * Enable the Bluetooth server
 * @param server			Instance of BluetoothServer_t
 */
void BluetoothServer_enable(BluetoothServer_t *server){

	listen(server->sock, 1);
	server->client = accept(server->sock, (struct sockaddr *)&(server->remAddr), &server->opt);
	printf("accepted\n");
	ba2str(&server->remAddr.rc_bdaddr, server->buf);
	fprintf(stderr, "accepted connection from %s\n", server->buf);
	memset(server->buf, 0, sizeof(server->buf));
}

/*!
 * Disable the Bluetooth server
 * @param server				Instance of BluetoothServer_t
 */
void BluetoothServer_disable(BluetoothServer_t *server){

	close(server->client);
	close(server->sock);
}

/*!
 * Read a string via Bluetooth
 * @param server				Instance of BluetoothServer_t
 * @return						Number of bytes received
 */
int BluetoothServer_readString(BluetoothServer_t *server){

	int bytesRead = read(server->client, server->recData, sizeof(server->recData));
	if(bytesRead > 0){

		printf("received [%s]", (server->recData));

		printf("\n");
	}

	return bytesRead;
}

/*!
 * Constructor for BluetoothClient_t
 * @param client				Instance of BluetoothClient_t
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
 * Enable the Bluetooth client
 * @param client				Instance of BluetoothClient_t
 */
void BluetoothClient_enable(BluetoothClient_t *client){

	client->status = connect(client->sock, (struct sockaddr *)&(client->addr), sizeof(client->addr));
	BluetoothClient_checkError(client);
}

/*!
 * Disable the Bluetooth client
 * @param client				Instance of BluetoothClient_t
 */
void BluetoothClient_disable(BluetoothClient_t *client){

	close(client->sock);
}

/*!
 * Send two doubles as a string, used to send the distance and angle in one transaction
 * @param client				Instance of BluetoothClient_t
 * @param data0					value to send
 * @param data1					value to send
 */
void BluetoothClient_sendDoubleAsStr(BluetoothClient_t *client, double data0, double data1){

	sprintf(client->txData, "%f%f", data0, data1);
   	BluetoothClient_sendString(client, client->txData, 16);
}

/*!
 * Send a string via bluetooth
 * @param client				Instance of BluetoothClient_t
 * @param data					value to send
 * @param size					length of data to send
 */
void BluetoothClient_sendString(BluetoothClient_t *client, char *data, int size){

	client->status = write(client->sock, data, size);
	BluetoothClient_checkError(client);
}

/*!
 * Check for errors in the bluetooth client communications
 * @param client				Instance of BluetoothClient_t
 */
void BluetoothClient_checkError(BluetoothClient_t *client){

	if(client->status < 0){
		perror(":(\t");
	}
}

/*!
 * Receive the user parameters from the GUI
 * @param server				Instance of BluetoothServer_t
 * @param dst					Desination to store the parameters
 * @param size					Size of desination
 */
void BluetoothServer_receiveParams(BluetoothServer_t *server, int *dst, int size){

	if(BluetoothServer_readString(server)){

		/*convert received data from comma separated string
		 *to the user parameters
		 */
		char *token = strtok(server->recData, ",");


		for(int i=0; i<size; i++){
			if(token != NULL){
			dst[i] = atoi(token);

			printf("dst %i\n", dst[i]);
			token = strtok(NULL, ",");
			}
		}
	}
}







