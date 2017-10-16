/*detailed info on how this code works is present in the readme.txt file */
#define CORE0 0x0
#define CORE1 0x1
#define CORE2 0x2
#define CORE3 0x3 
#define CORE0_MAILBOX0 0X400000c0	
#define CORE1_MAILBOX0 0X400000d0
#define CORE2_MAILBOX0 0X400000e0
#define CORE3_MAILBOX0 0X400000f0
.section ".text.startup" 
.globl _start
.balign 4
_start: 
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

