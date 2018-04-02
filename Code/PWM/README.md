# PWM Demo
-------

Quick demo showing PWM functionality of rPi.  Requires pigpio library, which can be downloaded [here](http://abyz.me.uk/rpi/pigpio/download.html)

## Usage

	git clone https://github.com/rv456/BowlsEye.git
	cd BowlsEye/Code/PWM
	make
	./pwmDemo

Note that the pigpio daemon must be running with the following sample rate to allow for a stable 40kHz output:

    sudo piogpiod -s 1

You can also remove unused object files with

	make clean

