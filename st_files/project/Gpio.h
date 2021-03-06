#ifndef STDINT_H_
#include <stdint.h>
#endif


/*
Macros for read only , read  write  varaibles 

*/
#define __IO volatile

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
}GPIO_typedef;

/*
Macros for all the gpio base address
*/

#define GPIOA	((GPIO_typedef *)0x40020000)
#define GPIOB	((GPIO_typedef *)0x40020400)
#define GPIOC	((GPIO_typedef *)0x40020800)
#define GPIOD	((GPIO_typedef *)0x40020c00)
#define GPIOE	((GPIO_typedef *)0x40021000)
#define GPIOH	((GPIO_typedef *)0x40021c00)
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

#define GPIO_setmode(gpio, pinnumber, modetype)    gpio->GPIOx_MODER |=modetype << 2*pinnumber
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

#define GPIO_setpupdr(gpio,pinnumber,pull_type)  gpio->GPIOx_PUPDR |=pull_type<< 2*pinnumber
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


typedef struct
{
  __IO uint32_t CR;           
  __IO uint32_t PLLCFGR;       
  __IO uint32_t CFGR;        
  __IO uint32_t CIR;         
  __IO uint32_t AHB1RSTR;    
  __IO uint32_t AHB2RSTR;    
  __IO uint32_t AHB3RSTR;    
       uint32_t  RESERVED0;   
  __IO uint32_t APB1RSTR;     
  __IO uint32_t APB2RSTR;     
  uint32_t      RESERVED1[2];  
  __IO uint32_t AHB1ENR;       
  __IO uint32_t AHB2ENR;       
  __IO uint32_t AHB3ENR;       
  uint32_t      RESERVED2;     
  __IO uint32_t APB1ENR;       
  __IO uint32_t APB2ENR;       
  uint32_t      RESERVED3[2];  
  __IO uint32_t AHB1LPENR;     
  __IO uint32_t AHB2LPENR;     
  __IO uint32_t AHB3LPENR;     
  uint32_t      RESERVED4;     
  __IO uint32_t APB1LPENR;     
  __IO uint32_t APB2LPENR;     
  uint32_t      RESERVED5[2];  
  __IO uint32_t BDCR;          
  __IO uint32_t CSR;           
  uint32_t      RESERVED6[2];  
  __IO uint32_t SSCGR;         
  __IO uint32_t PLLI2SCFGR;    
  uint32_t      RESERVED7[1];  
  __IO uint32_t DCKCFGR;       
} RCC_typeDef;

#define RCC ((RCC_typeDef *)0x40023800)
