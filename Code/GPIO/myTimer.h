#ifndef __MYTIMER_H_
#define __MYTIMER_H_

#include "CppTimer.h"

class MyTimer : public CppTimer{
	
	public:
	
	MyTimer(){
		enable = 0;
	}
	virtual ~MyTimer(){};
	
	uint8_t enable;
	
	void timerEvent(){
		
		enable = 1-enable;
	}
	
	uint8_t poll(){
		return enable;
	}
	
};

#endif
