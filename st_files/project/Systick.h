/**
	
	USEFULL HINTS ON SYSTICK PROGRAMMING:
	-------------------------------------
	Ensure software uses aligned word accesses to access the SysTick registers.
	The SysTick counter reload and current value are undefined at reset, the correct initialization sequence for the SysTick counter is:
		1.Program reload value.
	@details: STKLOAD register is loaded with necessary value . say if we need a dealy of 100 cycles then we should
						load a value of 99 in this register
						If we load a value zero there will be no effect as to raise an interrupt the count should be atleast
						from  1 to 0.
		2. Clear current value.
	@details: The register STK_CURVAL register contains the current value of the systick count. 
						To intialize or to clear this, write any value into that register the registers will be intialized to zero 
						and the count flag bit in the STK_CTRL register will be set to zero
		3. Program Control and Status register 
	@details: 
		----------------------------------------------------------------------------
		|    @RESERVED          | @CF|   @RESERVED  | @CLKSOURCE| @TICKINT |  @EN  |
		----------------------------------------------------------------------------
		31                    17  16  15           3      2           1         0
		
		
		Count Flag: This is for reading purpose during init stage we will not touch this.
		Clock Source: If this is 0 selects (AHB/8) else it will select AHB value . 
									We will init this bit to zero 
		Tick Init: To raise an interrupt request we need to set this to 1
		Enable: The counter starts as soon as this bit is set to 1
*/

#ifndef STDINT_H_
#include<stdint.h>
#endif 
/*
			A typedef structure to ease the access of systick registers 
*/
typedef struct 
{
	uint32_t CTRL;
	uint32_t LOAD;
	uint32_t VAL;
	uint32_t CALIB;
}Systick_typedef;

/*
     A Macro that is used for accessing the systick registers
*/

#define STK  ((Systick_typedef *) 0xE000E010)

/*
			A typedef structure for the SHP [ 'S'ystem 'H'andler 'p'riority register  ]
			in this we set the priority for the Systick handler

*/

typedef struct
{
	 uint16_t RESERVED;
	 uint8_t PENDSV;
	 uint8_t SYSTICK;
} SHP3_typedef;

#define SHP3 ((SHP3_typedef *)0xE000ED20)

__inline void systick_config( uint32_t count , uint8_t prio  )
{
	
	
	/* 1. Program the reload value */
	STK->LOAD = (count-1) ;
	/* Clear the current register */                          
	STK->VAL = 0UL;
	/* Program control and status register */
	STK->CTRL |= 0X00000003; 
	/* set the priority in the SHP block */
	SHP3->SYSTICK = prio;
}




