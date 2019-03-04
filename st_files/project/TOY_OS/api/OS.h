#ifndef OS_HEADER_H_INCLUDED
#define OS_HEADER_H_INCLUDED

extern void OS_Launch(uint32_t timeslice);
extern uint32_t OS_AddThreads(void(*task0)(void), void(*task1)(void), void(*task2)(void));

typedef enum
{
  E_OK    = 0,
  E_ERROR = 1 
} err_status_N;

static inline void OS_Init()
{
		__asm( "CPSID I ");  /* Disable interrupts */
}
#endif