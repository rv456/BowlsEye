all: adcTest

CXXFLAGS += -Wall 

LDLIBS += -pthread -lpigpio

adcTest: adcTest.o adc.o  

clean: 
	rm -f *.o 
