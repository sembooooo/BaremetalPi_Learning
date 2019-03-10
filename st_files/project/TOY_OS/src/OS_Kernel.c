/*
			***************************************************
							Thread control block 
			***************************************************						
			
Some brief info regarding thread control block TCB
1. TCB stores the private information of each thread
2. There will be a TCB struncture and a stack for each thread
3. The following are the things that our TCB contains
	a. A pointer so it can be chained to a linked list 
	b. The value of its stack pointer
4.In addition to these necessary components, the TCB might also contain:
  a. Status, showing resources that this thread has or wants 
  b. A sleep counter used to implement sleep mode
  c. Thread number, type, or name
  d. Age, or how long this thread has been active
  e. Priority (not used in a round robin scheduler)
		
*/

#ifndef STDINT_H_
#include<stdint.h>
#endif 
#include "Systick.h"
#include "OS_Config.h"
#include "OS.h"
#include "OS_Kernel.h"



void SetInitialStack(int i){ 
  Thread[i].sp = &stack[i][STACKSIZE-16]; // thread stack pointer 
	
  stack[i][STACKSIZE-1] = 0x01000000; // Thumb bit 
	/* stack[i][STACKSIZE -2] contains PC address where we will assign the task address */
  stack[i][STACKSIZE-3] = 0x14141414; // R14 
  stack[i][STACKSIZE-4] = 0x12121212; // R12 
  stack[i][STACKSIZE-5] = 0x03030303; // R3 
  stack[i][STACKSIZE-6] = 0x02020202; // R2 
  stack[i][STACKSIZE-7] = 0x01010101; // R1 
  stack[i][STACKSIZE-8] = 0x00000000; // R0 
  stack[i][STACKSIZE-9] = 0x11111111; // R11 
  stack[i][STACKSIZE-10] = 0x10101010; // R10 
  stack[i][STACKSIZE-11] = 0x09090909; // R9 
  stack[i][STACKSIZE-12] = 0x08080808; // R8 
  stack[i][STACKSIZE-13] = 0x07070707; // R7 
  stack[i][STACKSIZE-14] = 0x06060606; // R6 
  stack[i][STACKSIZE-15] = 0x05050505; // R5 
  stack[i][STACKSIZE-16] = 0x04040404; // R4 
} 
/**
Fucntion summary:
 @parameters: 3 function pointers which contains no paramters and a void return type 
 @return : returns 1 
*/
uint32_t OS_AddThreads(void(*task0)(void), void(*task1)(void), void(*task2)(void))
	{  
  Thread[0].next = &Thread[1]; // 0 points to 1 
  Thread[1].next = &Thread[2]; // 1 points to 2 
  Thread[2].next = &Thread[0]; // 2 points to 0 

  SetInitialStack(0);
	stack[0][STACKSIZE-2] = (uint32_t)(task0); // PC
  SetInitialStack(1);
	stack[1][STACKSIZE-2] = (uint32_t)(task1); // PC
  SetInitialStack(2); 
	stack[2][STACKSIZE-2] = (uint32_t)(task2); // PC
  RunPt = &Thread[0];        // thread 0 will run first  
  return 1; // successful 
	}

void OS_Launch()
{
	systick_config(2000000,0xF0);
	startOS();
}



/**
@ToyOS_CreateTask()
This will create and intialize a TCB for a task or thread. 
We use the word thread and a task interchangibly	
@parameters - Takes in the starting address of the code for that task
@return  0 -  success
        -1 -  failure
*/
 err_status_N ToyOS_CreateTask( void (*task)(void))
 {
	err_status_N retval = E_OK;
	uint32_t prev_taskindex;
	TCB_INIT(Thread[KERNEL_numberoftasks]);
		
	
	 if( KERNEL_numberoftasks <= NUMTHREADS)
	 {
		/**
			if this is the first thread that we are creating then the thread.next 
			is to pointed to that thread only as there are no other threads.
		*/
		 if( KERNEL_numberoftasks != 0)
		 {
			 prev_taskindex = KERNEL_numberoftasks-1
		 }
		 else
		 {
			 prev_taskindex =0;
		 }
		/**
			As we have created a new thread or task we have link the last
			TCB to the current TCB and the current TCB to first TCB 
			in order to maintain the linked list. 
		*/
		 Thread[prev_taskindex].next = Thread[KERNEL_numberoftasks] ;
		 }
		 KERNEL_numberoftasks++;
	 }
	 else
	 {
		retval = E_ERROR;
	 }
	 
	 return retval;
 }