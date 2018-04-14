#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <pigpio.h>

#include "bluetoothController.h"




int main(int argc, char** argv)
{

   BluetoothClient_t blueClient;

   BluetoothClient_construct(&blueClient);


   char raw[8] = {0};

   double distance = 0.086;
   double angle = 90.0;

  	
    for(;;){
	
	sprintf(raw, "%f", distance);
	BluetoothClient_sendString(&blueClient, raw, 8);
	sprintf(raw, "%f", angle);   	
	BluetoothClient_sendString(&blueClient, raw, 8);
    }

}
