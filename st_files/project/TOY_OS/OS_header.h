/* this header file contains all the necessary function declarations*/3
extern void OS_Launch(uint32_t timeslice);
extern void OS_Init();
extern uint32_t OS_AddThreads(void(*task0)(void), void(*task1)(void), void(*task2)(void));
