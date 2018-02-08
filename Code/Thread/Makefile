all: main

CXXFLAGS += -g -Wall

LDLIBS += -lstdc++ -pthread -lwiringPi

main: blinkThread.o main.o

clean: 
	rm -f *.o 
