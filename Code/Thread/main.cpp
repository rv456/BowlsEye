#include <signal.h>
#include <iostream>
#include "blinkThread.h"

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

	if(argc < 2){
		cout << "Usage: " << argv[0] << " <num>" << endl;
		return 1;
	}
	
	struct sigaction sigIntHandler;

	sigIntHandler.sa_handler = exitHandler;
	sigemptyset(&sigIntHandler.sa_mask);
	sigIntHandler.sa_flags = 0;

	sigaction(SIGINT, &sigIntHandler, NULL);

	/* This also works for catching ctrl+c
	*signal(SIGINT, exitHandler);
	*/

	BlinkThread blinkThread(atoi(argv[1]));

	blinkThread.start();
	
	for(uint8_t i=0; i<100; i++){
		
		cout << "can still do other stuff" << endl;
	}
	
	cout << "Waiting for thread to finish" << endl;
	
	blinkThread.join();
	
	cout << "Thread finished" << endl;
	return 0;
}
