This is a very basic scheduler code. 
This is a pre-emptive roundrobin scheduler.

The entire OS related code is present in two files one is OS.c and another is OS_assembler.s

The scheduler is written in assembly. 
The all the API's are written in c.


Lets start understanding the code. 

First of all we have a create a TASK. To create a task we have to call an API called 

To Create a task we need Thread control block to store the informatino 

ToyOS_CreateTask()
    inputs : void (*task)(void)        address of the function 
    return value: either 1 or 0 . return 0 on success and return 1 on failure

What happens when we call this function ?
This does the following things
(1) If the number of tasks that are getting created exceed the macro #NUMTHREADS which inidates maximum number of 
    tasks that this OS allows then this returns 1 and exits
(2) creates link between TCB
(3) Initializes the Stack space

The comments in the code will help to understand how the code flow works. 


next 

