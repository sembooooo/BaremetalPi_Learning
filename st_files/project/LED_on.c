#include "Gpio.h"
#include "Systick.h"
uint32_t value=1;
int main()
{
		
		/* Enable Clock for the GPIOD port*/
		RCC->AHB1ENR|=(1<<3);
	
	
		GPIO_setmode(GPIOD,13,OUTPUT);
		GPIO_setpupdr(GPIOD,13,PULLUP);
	  systick_config(20000, 0xF0);
	 GPIO_setodr(GPIOD,(value<<13));
	
		while(1);
}
void SysTick_Handler(void)
{
	 value ^=value;
	 GPIO_setodr(GPIOD,(value<<13));
}




