#ifndef STDINT_H_
#include <stdint.h>
#endif



/*
	Structure used for accessing the GPIO registers
*/
typedef struct{
	uint32_t GPIOx_MODER;
	uint32_t GPIOx_oTYPER;
	uint32_t GPIOx_SPEEDER;
	uint32_t GPIOx_PUPDR;
	uint32_t GPIOx_IDR;
	uint32_t GPIOx_ODR;
}GPIO_Typedef;

/*
Macros for all the gpio base address
*/

#define GPIOA	(GPIO_Typedef *)0x40020000UL
#define GPIOB	(GPIO_Typedef *)0x40020400UL	
#define GPIOC	(GPIO_Typedef *)0x40020800UL
#define GPIOD	(GPIO_Typedef *)0x40020c00UL
#define GPIOE	(GPIO_Typedef *)0x40021000UL
#define GPIOH	(GPIO_Typedef *)0x40021c00UL
/*
	MAcros for the modes of GPIO's
*/
#define INPUT                     (uint32_t)0
#define OUTPUT                    (uint32_t)1
#define ALTERNATE_FUNCTION        (uint32_t)2
#define ANALOG                    (uint32_t)3

/*
brief- This sets the desired mode for the desired gpio pin 
	name: GPIO_setmode 
	parameters: 
	1. name of the gpio from gpio macro
	2. pin number
	3. mode type either input ,output , analog or alternate function from mode macros
	
*/

#define GPIO_setmode(gpio, pinnumber, modetype)    gpio->GPIOx_MODER |=(modetype << 2*(pinnumber-1))
/*
	Macros for the pull up pull down register
*/
#define PULLUP              (uint32_t)1
#define PULLDOWN            (uint32_t)2
#define NOPULLUP_NOPULLDOWN (uint32_t)0
/*
brief- This sets the desired pullup or pull down  for the desired gpio pin 
	name: GPIO_setpupdr
	parameters: 
	1. name of the gpio from gpio macro
	2. pin number
	3. mode type either input ,output , analog or alternate function from mode macros
	
*/

#define GPIO_setpupdr(gpio,pinnumber,pull_type) gpio->GPIOx_PUPDR |=(pull_type<< 2*(pinnumber-1))
/*
brief- This sets the desired output for the port  
	name: GPIO_setodr
	parameters: 
	1. name of the GPIO
	2. value that is to be written in the register 
	
	EX: if we want to set the pin13 and pin 14 to 1 then the value paramter that is be passed should be in the following fashion
	(1<<13)|(1<<14)
	
*/


#define GPIO_setodr(gpio,value) (gpio->GPIOx_ODR |=value)

