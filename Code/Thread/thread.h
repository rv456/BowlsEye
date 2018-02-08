#ifndef __THREAD_H_
#define __THREAD_H_

#include <pthread.h>
#include <string.h>

class Thread{
	
	public:
	
	Thread(){};		//default constructor
	virtual ~Thread(){};	//default destructor
	
	/*
	 * method for starting the thread
	 */
	void start(){
		/*
		 * create thread with our id member
		 * no attributes and pass our execution method
		 * 
		 * do some error checking
		 */
		if(pthread_create(&tid, NULL, &Thread::exec, this) != 0){
			throw "Cannot create thread";
		} 
	}
	
	/*
	 * wait for thread to execute
	 */
	void join(){
		pthread_join(tid, NULL);  //returns NULL!
	}
	/*
	 * pure virtual function for defining behaviour of thread in 
	 * inherited classes
	 */
	virtual void run() = 0;
	
	private:

	pthread_t tid = 0;		//the actual thread structure
	
	
	
	static void *exec(void *thr){		//executes the thread
		/*
		 * cast to Thread class type and 
		 * call the run method 
		 * (remember it's a virtual fcn!)
		 */
		reinterpret_cast<Thread *>(thr)->run();	
		return NULL;
	}	
};

#endif
