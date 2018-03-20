#include "bluetoothController.h"

int main(int argc, char** argv){

	BluetoothClient_t client;
	BluetoothClient_construct(&client);
	
	BluetoothServer_t server;
	BluetoothServer_construct(&server);

	char data;

	for(;;){
			

		BluetoothClient_sendString(&client, "rPi", 3);
		BluetoothServer_readChar(&server, &data);	
	}

	BluetoothServer_disable(&server);
	BluetoothClient_disable(&client);
}

