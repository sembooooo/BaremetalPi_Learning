/* these .equ lines are just like #define lines for the assembler */
.equ CORE0, 0x0
.equ CORE1, 0x1
.equ CORE2, 0x2
.equ CORE3, 0x3 
.equ CORE0_MAILBOX0, 0X40000080	
.equ CORE1_MAILBOX0, 0X40000090
.equ CORE2_MAILBOX0, 0X400000A0
.equ CORE3_MAILBOX0, 0X400000B0
/* here starts our .text.startup where our startup code is present */
.section ".text.startup" 
.globl _start
.balign 4
_start: 

/*
 Here what we will do first is we allocate  stack for each and every core. By doing this each and every core will get its own stack
 Here i am giving a 512 bytes of stack. It is just a vague number which i took.
how do we achieve this? 
1. check which core it is either core0, core1, core2, core3 by reading the multi processor affinity id register ---> for more information see this folder readme.md
2. r0 stores the stack starting address 
3. so for core0 r0 holds __stack_pointer_core0  address and for core 1 r0 holds __stack_pointer_core1 etc.,. 
4. __stack_pointer_core0, __stack_pointer_core1 etc are defined in the linker script for now just think them as address in the memory 
5. we will store those values in stack pointer register [SP] and this can be seen at the label set_stack_func 
6. So finally we now have got four different stacks for four cores.
*/
	ldr r4,=CORE0					
	ldr r0,=__stack_pointer_core0 
	mrc p15,0,r5,c0,c0,5  				
	ands r5, r5, #0x3				
	cmp r4,r5					
	beq set_stack_func				
	ldr r0,=__stack_pointer_core1
	ldr r4,=CORE1
	cmp r4,r5
	beq set_stack_func
	ldr r0,=__stack_pointer_core2
	ldr r4,=CORE2
	cmp r4,r5
	beq set_stack_func
	ldr r0,=__stack_pointer_core3
	set_stack_func:
		mov sp,r0
		
/*
Disclaimer : for those who know GPU mailboxes and for their information these are not those GPU mailboxes
	     instead they are just memory location . For those who dont know GPU mailboxes ignore this disclaimer
	    
After setting up the stack now we need to make our cores execute

*/
	b mailbox
 	loop_in_mailbox:
		ldr r2,[r2]              // every core comes and checks whether  the value specified at the mailbox address is 0 or non zero
		cmp r2,#0                // here it compares 
		beq loop_in_mailbox	 // if it is non-zero then it means that CORE-0 has written the address where our core needs 
					 //to go and to execute 	
	bx r2                            // jump to the particular address given by CORE-0 and start executing the program.

	mailbox:
	ldr r4,=CORE3
	ldr r2,=CORE3_MAILBOX0
	cmp r4,r5
	beq loop_in_mailbox
	ldr r4,=CORE2
	ldr r2,=CORE2_MAILBOX0
	cmp r4,r5
	beq loop_in_mailbox
	ldr r4,=CORE1
	ldr r2,=CORE1_MAILBOX0
	cmp r4,r5
	beq loop_in_mailbox
	bl main

