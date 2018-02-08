#ifndef __BLINK_THREAD_H_
#define __BLINK_THREAD_H_

#include "thread.h"
#include <wiringPi.h>

using namespace std;

/*
 * Class for implementing our hello world
 * blinky led thing
 */
class BlinkThread : public Thread{
	
public:
	
	BlinkThread(int noBlinks);
	virtual ~BlinkThread(){};
	
private:
	
	void run();		//our method to run in the thread	
	int _noBlinks;
	
};

#endif
