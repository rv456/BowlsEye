#include "thread.h"
#include "stepperMotor.h"

void exitHandler(int s){
	
	RUN_THREAD_ = 0;
	StepperMotor_disable(&stepper);
	//pthread_join(t, NULL);
	BluetoothServer_disable(&server);
}

int main(int argc, char** argv){

	//BluetoothClient_t client;
	//BluetoothClient_construct(&client);
	
	struct sigaction sigIntHandler;

	sigIntHandler.sa_handler = exitHandler;
	sigemptyset(&sigIntHandler.sa_mask);
	sigIntHandler.sa_flags = 0;

	sigaction(SIGINT, &sigIntHandler, NULL);

    pi = pigpio_start(NULL, NULL);

    if (pi < 0) return -1;
	
	BLUETOOTH_DATA_[0] = 100;
	BLUETOOTH_DATA_[1] = 1;
	
	pi = pigpio_start(NULL, NULL);

    if (pi < 0) return -1;
	
	BluetoothServer_construct(&server);
	
	pthread_create(&t, NULL, blueToothThread, &server);
	
	StepperMotor_construct(&stepper, BLUETOOTH_DATA_);

	for(;;){
			
			//printf("bluetooth data: %i\n", BLUETOOTH_DATA_);
			
		StepperMotor_update(&stepper);
		time_sleep(0.2);
		//BluetoothServer_readInt(&server, &BLUETOOTH_DATA_);
		
		//BluetoothClient_sendString(&client, "rPi", 3);
		//BluetoothServer_readChar(&server, &data);	
	}
	
	//BluetoothClient_disable(&client);
}

