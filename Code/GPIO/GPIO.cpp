#include <wiringPi.h>
#include <signal.h>
#include <iostream>

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

	for(;;){

		digitalWrite(0, HIGH);
		delay(500);
		
		digitalWrite(0, LOW);
		delay(500);
	
	}

	return 0;
}