#include <wiringPi.h>
#include <signal.h>
#include <iostream>
#include "myTimer.h"

/*
*Simple hello world gpio program for testing wiring pi library
*/

using namespace std;

void exitHandler(int s){
	cout << "Caught signal " << s << endl;

	digitalWrite(0, LOW);
	exit(1);
}


int main(int argc, char **argv){

	struct sigaction sigIntHandler;

	sigIntHandler.sa_handler = exitHandler;
	sigemptyset(&sigIntHandler.sa_mask);
	sigIntHandler.sa_flags = 0;

	sigaction(SIGINT, &sigIntHandler, NULL);

	/* This also works for catching ctrl+c
	*signal(SIGINT, exitHandler);
	*/

	wiringPiSetup();

	pinMode(0, OUTPUT);

	piHiPri(20);

	MyTimer timer;
	timer.start(12500);
	
	cout << "timer started" << endl;

	for(;;){

	/*Toggle output pin high+low to create square
	*wave pulse, piHiPri sets high priority to reduce lag
	*/
		if(timer.poll()){
			digitalWrite(0, HIGH);
			cout << "HIGH" << endl;
		}
		else{
			digitalWrite(0, LOW);
		}	
		
		//digitalWrite(0, timer.enable);
		//cout << (int)timer.enable << endl;
		
	}

	return 0;
}
