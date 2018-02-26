Folder still in developement.

Once its is finished the readme file will be updated with the chagnes that are done in this. 

algorithm for the new OS:


aims: should use two stack pointers .
	1. PSP for Threads
	2. MSP for interrupts

in keil :
----------

first think about TCB section 


TCB { 
	/* the below are the elements that TCB contains */
	1. SP 
	2. pointer to the next TCB 
	3. Stack size
	4. < reserved for future >
}


As of now we shall create TCB's statically using arrays with the help of the macro MAX_TASKS. 
 		---------------------------------------				 ------------

Create two areas one is Thread stack and one more is main stack which will be used by 
interrupt handlers


untill now what we have done is we have just used an array. so we got the starting address of the stack

Problems now: 
 1. how to get the starting address of the memory region that is allocated as stack ?

possible answer:
----------------
int descriptor[3] __attribute__((section ("descr"))) ;
We can use the above  method to control the given memory area. 
(not sure should be tested on the board)

 2. How to give configurable size to the directive SPACE.
possible answer:
----------------
try to write an assembly inline function so that we can use macros there. 


