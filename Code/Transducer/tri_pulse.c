#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

#include <pigpiod_if2.h>

int run=1;
double period=0.000025

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


int main(int argc, char** argv){
  int pi;

  pi = pigpio_start(NULL, NULL);

  if (pi < 0) return -1;

  setSignalHandler(SIGINT, stop);
  printf("PWM out on GPIO4\nControl C to stop.\n");

  while(run);

  gpio_write(pi, 4, 1);
  time_sleep(period/2);
  gpio_write(pi, 4, 0);
  time_sleep(period/2);
  gpio_write(pi, 4, 1);
  time_sleep(period/2);
  gpio_write(pi, 4, 0);
  time_sleep(period/2);
  gpio_write(pi, 4, 1);
  time_sleep(period/2);
  gpio_write(pi, 4, 0);
  time_sleep(period/2);

  time_sleep(1.0);

  return 0;



}
