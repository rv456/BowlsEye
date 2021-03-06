#include <signal.h>
#include <iostream>
#include <wiringPiSPI.h>
#include "gpio.h"

using namespace std;

void exitHandler(int s){
	
	digitalWrite(0, LOW);
	exit(1);
}

int main(int argc, char** argv){
	
	signal(SIGINT, exitHandler); 
	
	wiringPiSetup();
	
	GPIOClass led(0, MODE_OUTPUT_);
	
	led.high();
		
	wiringPiSPISetup(0, 500000);
		
	unsigned char buffer[2];
		
	int i;
	
	for(;;){
		
		wiringPiSPIDataRW(0, buffer, 2);
		
		i = (static_cast<int>(buffer[0]) << 7) | (static_cast<int>(buffer[1]));
		
		
		cout << ((i) & 0x0FFF) << endl;
		
	}
		
}


