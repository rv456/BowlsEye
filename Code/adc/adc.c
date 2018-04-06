#include <stdio.h>
#include <pigpiod_if2.h>

int main(int argc, char** argv){

	int pi = pigpio_start(NULL, NULL);

    	if (pi < 0) return -1;

	int spiHandle = spi_open(pi, 0, 1000000, 3);

	printf("handle %i", spiHandle);

	if(spiHandle < 0) return -1;

	char dataBuf[2] = {0x00, 0x00};
	char recBuf[2] = {0x00, 0x00};

	int rec = 0;

	for(;;){

		printf("sending chan 0\n");

		dataBuf[0] = 0x00;
		spi_xfer(pi, spiHandle, dataBuf, recBuf, 2);

		rec = 0;
		rec |= (((recBuf[0] & 0x0F) << 8) | recBuf[1]);
		//rec |= recBuf[1];
		printf("rec = %i\n", rec);

		time_sleep(0.1);

		printf("sending chan 1\n");

		dataBuf[0] = 0x08;

		spi_xfer(pi, spiHandle, dataBuf, recBuf, 2);

		rec = 0;
		rec |= (((recBuf[0] & 0x0F) << 8 ) | recBuf[1]);

		printf("rec %i\n", rec);

		time_sleep(0.1);
	}
}
