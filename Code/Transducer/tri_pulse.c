#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <pigpiod_if2.h>

int run=1;
double period=0.0000125;
int p_out=13;
unsigned int usecs=25;

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

void pulse(int pi, int p_out, int usecs){
  gpio_write(pi, p_out, 1);
  usleep(usecs);
  gpio_write(pi, p_out, 0);
  usleep(usecs);
  gpio_write(pi, p_out, 1);
  usleep(usecs);
  gpio_write(pi, p_out, 0);
  usleep(usecs);
  gpio_write(pi, p_out, 1);
  usleep(usecs);
  gpio_write(pi, p_out, 0);
}

int main(int argc, char** argv){
  int pi;

  pi = pigpio_start(NULL, NULL);

  if (pi < 0) return -1;

  setSignalHandler(SIGINT, stop);
  printf("PWM out on GPIO13\nControl C to stop.\n");

  while(run){
     pulse(pi,p_out,period);
     time_sleep(0.1);
  }

  printf("Tidying..");
  gpio_write(pi,p_out,0);
  pigpio_stop(pi);
  return 0;



}
