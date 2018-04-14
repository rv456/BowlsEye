#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

#include <pigpiod_if2.h>

/*
This software requires the pigpio daemon to be running.

sudo pigpiod -s 1

./pwmDemo          # Start 40kHz 50% duty cycle PWM on gpio 4

*/


int run=1;
int tx_1=13;

void stop(int signum)
{
   run = 0;
}

typedef void (*signalFunc_t) (int signum);

static void setSignalHandler(int signum, signalFunc_t sigHandler)
{
   struct sigaction new;

   memset(&new, 0, sizeof(new));
   new.sa_handler = sigHandler;

   sigaction(signum, &new, NULL);
}

void pwm_setup(int pi, int channel){
   set_PWM_frequency(pi, channel, 40000);
   set_PWM_dutycycle(pi, channel, 128);
}

void pulse(int pi, int channel){

//    set_PWM_dutycycle(pi, channel, 128);
    set_PWM_frequency(pi, channel, 40000);
    set_PWM_frequency(pi, channel, 0);
   //gpio_write(pi, channel, 0);
  // set_PWM_dutycycle(pi,channel,128);
 //   set_PWM_dutycycle(pi,channel,0);

}

void Exciter_construct(int pi, int pin, int noPulses, int onTime, int offTime){

	gpioPulse_t pulseInfo[noPulses];

        for (int i=0; i<noPulses; i+=2){

		pulseInfo[i].gpioOn = 1<< pin;
		pulseInfo[i].gpioOff = 0;
                pulseInfo[i].usDelay = onTime;

		pulseInfo[i+1].gpioOn = 0;
                pulseInfo[i+1].gpioOff = 1<<pin;
                pulseInfo[i+1].usDelay = offTime;

        }

        wave_add_generic(pi, noPulses, pulseInfo);
}


int main(int argc, char** argv)
{
   int pi;

   pi = pigpio_start(NULL, NULL);

   if (pi < 0) return -1;

   setSignalHandler(SIGINT, stop);
 //  gpioPulse_t pulse;

   set_mode(pi, tx_1, PI_OUTPUT);

//   pulse.gpioOn = tx_1;
//   pulse.gpioOff = 0;
//   pulse.usDelay = 50;

   wave_clear(pi);
   printf("PWM out on GPIO4\nControl C to stop.\n");

   Exciter_construct(pi, tx_1, 16, 13, 12);
   //wave_add_generic(pi, 16, (gpioPulse_t[]){{1 << tx_1, 0, 50},{0,1 << tx_1, 50},{1 << tx_1, 0, 50},{0,1 << tx_1, 50},{1 << tx_1, 0, 50},{0,1 << tx_1, 50},{1 << tx_1, 0, 50},{0,1 << tx_1, 50},{1 << tx_1, 0, 50},{0,1 << tx_1, 50},{1 << tx_1, 0, 50},{0,1 << tx_1, 50},{1 << tx_1, 0, 50},{0,1 << tx_1, 50},{1 << tx_1, 0, 50},{0,1 << tx_1, 50}});


   uint32_t wid = wave_create(pi);
   //pwm_setup(pi,tx_1);

   printf("pulses %i\n", wave_get_pulses(pi));
   printf("micros %i\n", wave_get_micros(pi));

   while(run){


    
    // wave_chain(pi, (char []){wid , 255, 1, 8 ,0}, 5);
         wave_send_once(pi, wid);
	time_sleep(1);    
  //   while(wave_tx_busy(pi)){
     
//	printf("busy\n");

//pulse(pi,tx_1);
     //time_sleep(0.5);
//	}
   }

   printf("\ntidying up\n");

   gpio_write(pi, 13, 0);

   pigpio_stop(pi);

   return 0;
}
