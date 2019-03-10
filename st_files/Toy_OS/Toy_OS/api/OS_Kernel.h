#ifndef OS_KERNEL_H
#define OS_KERNEL_H





/**
 * functions externs from other files
*/
extern void startOS(void);

/**
 *  Structures and variables declaration and needed 
 *  #defines declaration area
*/

/******************************************************
			TCB -Thread Control block structure 
This only contains the following feild feilds. 
	1. a pointer to its stack
	2. a pointer to the other TCB.
	3. a feild for priority
******************************************************/
typedef struct tcb{
  uint32_t *sp;      /* pointer to stack, valid for threads not running*/
  struct tcb *next;  /* linked-list pointer */
  uint32_t Prio;     /* priority */
} TCB;

TCB Thread[NUMTHREADS];
TCB *RunPt;          /* pointer to the current task */
uint32_t stack[NUMTHREADS][STACKSIZE];
uint32_t KERNEL_numberoftasks = 0;


#endif
