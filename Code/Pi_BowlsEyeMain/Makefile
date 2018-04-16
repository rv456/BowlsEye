all: main

CXXFLAGS += -Wall 

LDLIBS += -pthread -lpigpio -lbluetooth

main: main.o adc.o blutoothController.o led.o stepperMotor.o transducer.o

clean: 
	rm -f *.o 
