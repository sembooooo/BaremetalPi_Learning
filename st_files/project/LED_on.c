#include "Gpio.h"

int main()
{
		/* Enable Clock for the GPIOD port*/
		RCC->AHB1ENR|=(1<<3);
	        
	        /* Configure the GPIO port for desired settings */
		GPIO_setmode(GPIOD,13,OUTPUT);
		GPIO_setpupdr(GPIOD,13,PULLUP);
	        GPIO_setodr(GPIOD,(1<<13));
		while(1);


	
}







