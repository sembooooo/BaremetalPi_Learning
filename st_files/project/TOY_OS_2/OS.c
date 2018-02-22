
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

#define NUMTHREADS 3  // maximum number of threads

#define STACKSIZE 19 // number of 32-bit words in stack
/*******************Function Prototypes*****************/
extern void startOS(void);
void OS_Launch(void);
void OS_Init(void);
uint32_t OS_AddThreads(void(*task0)(void), void(*task1)(void), void(*task2)(void));
/******************GLOBAL VARIABLES*******************	
*/

typedef struct 
{
	sint8_t numberoftasks;  // holds the number of tasks -1 count 
	uint8_t  STK_PT;                // holds the amount of stack that was used
} kernel_table;

kernel_table KERNEL; 
/***************INTIALIZATION OF KERNEL TABLE***************/

 KERNEL.numberoftasks = -1 ; 
 KERNEL.STK_PT = 0 ;
/******************************************************
			TCB -Thread Control block structure 
This only contains two feilds. 
	1. a pointer to its stack
	2. a pointer to the other TCB.
******************************************************/
typedef struct tcb{
  uint32_t *sp;      // pointer to stack, valid for threads not running
  struct tcb *next; // linked-list pointer
} TCB;
TCB Thread[NUMTHREADS];

TCB *RunPt;

uint32_t stack[NUMTHREADS][STACKSIZE]; /* Stack for our processor*/


/**
		The SetIntialStack() will only intialize the stack memory of a particular task.
		this is called in the function ToyOS_CreateTask() so as soon as a task is created
		this function is called and the stack is intialized
*/
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
  stack[i][STACKSIZE-14] = 0x06060606; // R6 
  stack[i][STACKSIZE-15] = 0x05050505; // R5 
  stack[i][STACKSIZE-16] = 0x04040404; // R4     
} 
void OS_Launch()
{
	/*
		This line here configures the systick and sets the priority
	*/
	systick_config(2000000,0xF0);
	
	/*
		check if there is atleast one thread is created.
		Assign the first thread to the current running task pointer " RunPt ".
		If no tasks are there then just be in a loop for now.
	*/
		if(KERNEL.numberoftasks == -1) 
		{
			while(1);
		}
		else
		{
			RunPt = &Thread[0]	
		}
	
	/*
		We are calling the function startOS() to start the operating system.
		This startOS() is written in assembly.
	*/
	startOS();
}
/**
		This OS_Init for now will only disable the interrupts
*/

 void OS_Init()
{
		__asm( "CPSID I ");  /* Disable interrupts */
}

/**
@ToyOS_CreateTask()
This will create and intialize a TCB for a task or thread. We use the word thread and a task interchangibly	
@parameters - Takes in the starting address of the code for that task
@return  0 -  success
        -1 -  failure
*/
 uint32_t ToyOS_CreateTask( void (*task)(void))
 {
		
	/*
		as one more task is going to be creaetd increment the kernel variable for number of tasks -KERNEL.numberoftasks
	*/
	KERNEL.numberoftasks++;
	 
	 
	 /*
	 1. There should be a variable in the kernel telling us how many tasks are present.
	 By this we will get to know whether there is space to allow one more task to create or to return 0 
	 */
	 if( KERNEL.numberoftasks <= NUMTHREADS)
	 {
		 /*
		 if this is the first thread that we are creating then we the thread. next is to pointed to that thread only as there are no other threads.
		 */
		 if( KERNEL.numberoftasks = =0)
		 {
			 Thread[0].next = Thread[0] ;
			 return 0;
		 }
		 /*
			As we have created a new thread or task we have link the last TCB to the current TCB and the current TCB to first TCB 
			in order to maintain the linked list. 
		 */
		 Thread[KERNEL.numberoftasks-1].next = Thread[KERNEL.numberoftasks];
		 /* Set up the stack for the thread */
		 SetInitialStack(STK_PT);
		 stack[STK_PT][STACKSIZE-2] = (uint32_t * )(*task) 
		 STK_PT++;
	 }
	 else
		 return -1;
 }
