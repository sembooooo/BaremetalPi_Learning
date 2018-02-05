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
#define STDINT_H_
#endif 

typedef struct 
{
	uint32_t CTRL;
	uint32_t LOAD;
	uint32_t VAL;
	uint32_t CALIB;
}Systick_Typedef;

#define STK  ((Systick_Typedef *)0x0xE000E010)

__inline void systick_config(uint32_t count )
{
	
	
	/* 1. Program the reload value */
	STK->LOAD = count-1 ;
	/* Clear the current register */                          
	STK->VAL = 0X00000000;
	/* Program control and status register */
	STK_CTRL |= 0X00000003; 
	S
	
}


