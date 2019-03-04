#ifndef OS_KERNEL_H
#define OS_KERNEL_H


extern void startOS(void);

/******************************************************
			TCB -Thread Control block structure 
This only contains two feilds. 
	1. a pointer to its stack
	2. a pointer to the other TCB.
******************************************************/
typedef struct tcb{
  uint32_t *sp;      /* pointer to stack, valid for threads not running*/
  struct tcb *next;  /* linked-list pointer */
} TCB;

TCB Thread[NUMTHREADS];
TCB *RunPt;
uint32_t stack[NUMTHREADS][STACKSIZE];
uint32_t KERNEL_numberoftasks = -1 ;


#endif
