/**
 @Description 
 In this file we are going to write three tasks for our round robin scheduler 
		Task1 - glows led on pin 13 
		Task2- glows led on pin 14
		Task3-  glows led on pin 15
  For led's we will use our own macro's and functions that are written in Gpio.h header file
	
	After creation of these tasks we will add them into scheduler by using the functions present in OS.c files
	
*/
#include "Gpio.h"
/* this header file contains all the necessary function declarations*/
extern void OS_Launch(void);
extern void OS_Init(void);
extern uint32_t OS_AddThreads(void(*task0)(void), void(*task1)(void), void(*task2)(void));
uint32_t  status=1;

void Task1()
{
		/* Enable Clock for the GPIOD port*/
		RCC->AHB1ENR|=(1<<3);
	
	
		GPIO_setmode(GPIOD,13,OUTPUT);
		GPIO_setpupdr(GPIOD,13,PULLUP);
		while(1)
		{
			if(status==1){
			GPIO_setodr(GPIOD,(1<<13));
				status=2;
			}
		}
	
}

void Task2()
{
	  GPIO_setmode(GPIOD,14,OUTPUT);
		GPIO_setpupdr(GPIOD,14,PULLUP);
		while(1)
		{
			if(status==2)
			{
			GPIO_setodr(GPIOD,(1<<14));
				status=3;
			}
		}
}

void Task3()
{
	  GPIO_setmode(GPIOD,15,OUTPUT);
		GPIO_setpupdr(GPIOD,15,PULLUP);
			
	while(1)
		{
			if(status==3)
			{
			GPIO_setodr(GPIOD,(1<<15));
				status=1;
			}
		}
}


int main()
{
	OS_Init();
	OS_AddThreads(&Task1,&Task2,&Task3);
	OS_Launch();
	while(1);
}
