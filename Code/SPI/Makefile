all: spi

CXXFLAGS += -g -Wall

LDLIBS += -lstdc++ -lwiringPi

spi: gpio.o spi.o

clean: 
	rm -f *.o 
