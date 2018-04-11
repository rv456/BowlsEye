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
int tx_1=13

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

void pulse(int pi, int pwm_chan){

   set_PWM_dutycycle(pi,channel,128);
   set_PWM_dutycycle(pi,channel,0);

}

int main(int argc, char** argv)
{
   int pi;

   pi = pigpio_start(NULL, NULL);

   if (pi < 0) return -1;

   setSignalHandler(SIGINT, stop);

   printf("PWM out on GPIO4\nControl C to stop.\n");

   pwm_setup(pi,tx_1);

   while(run){
     pulse(pi,tx_1);
     time_sleep(0.003);
   };

   printf("\ntidying up\n");

   gpio_write(pi, 13, 0);

   pigpio_stop(pi);

   return 0;
}
