#include "blinkThread.h"
#include <iostream>

BlinkThread::BlinkThread(int noBlinks) : _noBlinks(noBlinks){
	
	wiringPiSetup();

	//horrible dependency but who cares for now 
	pinMode(0, OUTPUT);	
}

void BlinkThread::run(){
	
	cout << "In thread " << endl;
	
	for(int i=0; i<_noBlinks; i++){
		digitalWrite(0, HIGH);
		delay(500);				//probs shouldn't have delays in the thread...
						
		digitalWrite(0, LOW);
		delay(500);	
	}
}
