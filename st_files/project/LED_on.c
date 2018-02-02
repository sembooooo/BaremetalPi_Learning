#include "Gpio.h"

int main()
{
		GPIO_setmode(GPIOD,13,OUTPUT);
		GPIO_setpupdr(GPIOD,13,PULLUP);
	  GPIO_setodr(GPIOD,(1<<13));
		while(1);
}


