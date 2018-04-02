all: main

CXXFLAGS += -Wall

LDLIBS += -lbluetooth -lpthread -lpigpiod_if2

main: main.o bluetoothController.o stepperMotor.o

clean: 
	rm -f *.o 
