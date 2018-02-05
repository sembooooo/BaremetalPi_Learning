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
}GPIO_Typedef;

/*
Macros for all the gpio base address
*/

#define GPIOA	((GPIO_Typedef *)0x40020000)
#define GPIOB	((GPIO_Typedef *)0x40020400)
#define GPIOC	((GPIO_Typedef *)0x40020800)
#define GPIOD	((GPIO_Typedef *)0x40020c00)
#define GPIOE	((GPIO_Typedef *)0x40021000)
#define GPIOH	((GPIO_Typedef *)0x40021c00)
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
  __IO uint32_t CR;            /*!< RCC clock control register,                                  Address offset: 0x00 */
  __IO uint32_t PLLCFGR;       /*!< RCC PLL configuration register,                              Address offset: 0x04 */
  __IO uint32_t CFGR;          /*!< RCC clock configuration register,                            Address offset: 0x08 */
  __IO uint32_t CIR;           /*!< RCC clock interrupt register,                                Address offset: 0x0C */
  __IO uint32_t AHB1RSTR;      /*!< RCC AHB1 peripheral reset register,                          Address offset: 0x10 */
  __IO uint32_t AHB2RSTR;      /*!< RCC AHB2 peripheral reset register,                          Address offset: 0x14 */
  __IO uint32_t AHB3RSTR;      /*!< RCC AHB3 peripheral reset register,                          Address offset: 0x18 */
  uint32_t      RESERVED0;     /*!< Reserved, 0x1C                                                                    */
  __IO uint32_t APB1RSTR;      /*!< RCC APB1 peripheral reset register,                          Address offset: 0x20 */
  __IO uint32_t APB2RSTR;      /*!< RCC APB2 peripheral reset register,                          Address offset: 0x24 */
  uint32_t      RESERVED1[2];  /*!< Reserved, 0x28-0x2C                                                               */
  __IO uint32_t AHB1ENR;       /*!< RCC AHB1 peripheral clock register,                          Address offset: 0x30 */
  __IO uint32_t AHB2ENR;       /*!< RCC AHB2 peripheral clock register,                          Address offset: 0x34 */
  __IO uint32_t AHB3ENR;       /*!< RCC AHB3 peripheral clock register,                          Address offset: 0x38 */
  uint32_t      RESERVED2;     /*!< Reserved, 0x3C                                                                    */
  __IO uint32_t APB1ENR;       /*!< RCC APB1 peripheral clock enable register,                   Address offset: 0x40 */
  __IO uint32_t APB2ENR;       /*!< RCC APB2 peripheral clock enable register,                   Address offset: 0x44 */
  uint32_t      RESERVED3[2];  /*!< Reserved, 0x48-0x4C                                                               */
  __IO uint32_t AHB1LPENR;     /*!< RCC AHB1 peripheral clock enable in low power mode register, Address offset: 0x50 */
  __IO uint32_t AHB2LPENR;     /*!< RCC AHB2 peripheral clock enable in low power mode register, Address offset: 0x54 */
  __IO uint32_t AHB3LPENR;     /*!< RCC AHB3 peripheral clock enable in low power mode register, Address offset: 0x58 */
  uint32_t      RESERVED4;     /*!< Reserved, 0x5C                                                                    */
  __IO uint32_t APB1LPENR;     /*!< RCC APB1 peripheral clock enable in low power mode register, Address offset: 0x60 */
  __IO uint32_t APB2LPENR;     /*!< RCC APB2 peripheral clock enable in low power mode register, Address offset: 0x64 */
  uint32_t      RESERVED5[2];  /*!< Reserved, 0x68-0x6C                                                               */
  __IO uint32_t BDCR;          /*!< RCC Backup domain control register,                          Address offset: 0x70 */
  __IO uint32_t CSR;           /*!< RCC clock control & status register,                         Address offset: 0x74 */
  uint32_t      RESERVED6[2];  /*!< Reserved, 0x78-0x7C                                                               */
  __IO uint32_t SSCGR;         /*!< RCC spread spectrum clock generation register,               Address offset: 0x80 */
  __IO uint32_t PLLI2SCFGR;    /*!< RCC PLLI2S configuration register,                           Address offset: 0x84 */
  uint32_t      RESERVED7[1];  /*!< Reserved, 0x88                                                                    */
  __IO uint32_t DCKCFGR;       /*!< RCC Dedicated Clocks configuration register,                 Address offset: 0x8C */
} RCC_TypeDef;

#define RCC ((RCC_TypeDef *)0x40023800)
