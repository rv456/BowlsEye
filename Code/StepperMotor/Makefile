all: stepper

CXXFLAGS += -Wall

LDLIBS += -pthread -lpigpiod_if2

stepper: stepperMotor.o stepper.o

clean: 
	rm -f *.o 
