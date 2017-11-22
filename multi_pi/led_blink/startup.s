/* these .equ lines are just like #define lines for the assembler */
.equ CORE0, 0x0
.equ CORE1, 0x1
.equ CORE2, 0x2
.equ CORE3, 0x3 
/*
------------------------------------------------------------------------------------------------------------------------------------
	FIQ,IRQ,SVC and HYP mode values
------------------------------------------------------------------------------------------------------------------------------------
*/

.equ CPU_HYPMODE, 0X11
.equ CPU_IRQMODE, 0X12
.equ CPU_SVCMODE, 0X13
.equ CPU_FIQMODE, 0X1A

/*
------------------------------------------------------------------------------------------------------------------------------------
	FIQ and IRQ flag position in program status register
------------------------------------------------------------------------------------------------------------------------------------
*/

.equ I_BIT, (1<<7)
.equ F_BIT, (1<<6)

/*
------------------------------------------------------------------------------------------------------------------------------------
A LITTLE INTRODUCTON ON THESE MACROS':
In these macros we are mentioning the value that is to be present in the program status register
what we do is, we will enter into one mode and we will disable the IRQ and FIQ exceptions from occuring. This means we are disabling
those exceptions
Say we want to go to FIQ Mode what we do we will make the processor go in FIQ mode and will just disable the Exceptions from arising.
this does not mean that we are not in FIQ mode
-------------------------------------------------------------------------------------------------------------------------------------
*/
.equ CPU_FIQMODEVALUE, (CPU_FIQMODE)|(F_BIT)|(I_BIT)
.equ CPU_IRQMODEVALUE, (CPU_IRQMODE)|(F_BIT)|(I_BIT)
.equ CPU_HYPMODEVALUE, (CPU_HYPMODE)|(F_BIT)|(I_BIT)
.equ CPU_SVCMODEVALUE, (CPU_SVCMODE)|(F_BIT)|(I_BIT)

/*
--------------------------------------------------------------------------------------------------------------------------------------
 Here our.text.startup section is located where our startup code is present
--------------------------------------------------------------------------------------------------------------------------------------
 */
.section ".text.startup" 
.globl _start
.balign 4
_start: 

/*
---------------------------------------------------------------------------------------------------------------------------------------
	 GETTING OUT OF HYPERVISOR MODE AND ENTERING TO SVC MODE 
---------------------------------------------------------------------------------------------------------------------------------------
*/
	mrs r0, cpsr 			// READ THE CURRENT PROGRAM STAUS REGISTER
	and r1, r0, #0x1F		// CLEAR ALL THE BITS OTHER THAN MODE BITS	
	cmp r1, #CPU_HYPMODEVALUE	// CHECK WHETHER WE ARE IN HYP MODE OR NOT	
	bne STACK_ALLOCATION		//
 	bic r0, r0, 0x1F		// clear the mode bits in the program status register
	orr r0, r0, #CPU_SVCMODEVALUE
	mrs spsr_cxsf, r0		// NOW WRITE THE VALUE INORDER TO BRING OUR PROCESSOR TO SVC MODE
/*
---------------------------------------------------------------------------------------------------------------------------------------
 Here what we will do first is we allocate  stack for each and every core. By doing this each and every core will get its own stack
 Here i am giving a 512 bytes of stack. It is just a vague number which i took.
how do we achieve this? 
1. check which core it is either core0, core1, core2, core3 by reading the multi processor affinity id register
---> for more information see this folder readme.md note 1 
2. r0 stores the stack starting address 
3. so for core0 r0 holds __stack_pointer_core0  address and for core 1 r0 holds __stack_pointer_core1 etc.,. 
4. __stack_pointer_core0, __stack_pointer_core1 etc are defined in the linker script for now just think them as address in the memory 
5. we will store those values in stack pointer register [SP] and this can be seen at the label set_stack_func 
6. So finally we now have got four different stacks for four cores.
----------------------------------------------------------------------------------------------------------------------------------------
*/
STACK_ALLOCATION:
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
---------------------------------------------------------------------------------------------------------------------------------------
Disclaimer : for those who know GPU mailboxes and for their information these are not those GPU mailboxes
	     instead they are just memory location . For those who dont know GPU mailboxes ignore this disclaimer
	     And these are my own mailboxes which we intentionally make the cores to loop around 
	    
After setting up the stack now we need to make our cores execute some code and we need to direct them to that code. 
As our aim is to make diferrent cores to execute different code what we do is

how we do this ?

1. we will make our cores to loop over a single memory address. 

2. we will make one of our core (here core0) to write the memory location where they need to jump to and start executing the code  

3. These other cores (here core 1,core 2,core 3) will read the memory location which is named as CORE1_MAILBOX  in the top of the file 
   and if its values is zero it will again read and repeat this untill some non zero value is written in those memory locations by 
   some core(here core 0)

4. here in this example every other core except core 0 loops and core 0 jumps to main function and sets the value at CORE1_MAILBOX 
   in the main function. 
---------------------------------------------------------------------------------------------------------------------------------------
*/
	b mailbox
 	loop_in_mailbox:
		ldr r1,[r2]              // every core comes and checks whether  the value specified at the mailbox address is 0 or non zero
		cmp r1,#0                // here it compares 
		beq loop_in_mailbox	 // if it is non-zero then it means that CORE-0 has written the address where our core needs 
					 //to go and to execute 	
	bx r2                            // jump to the particular address given by CORE-0 and start executing the program.

	mailbox:
	ldr r4,=CORE3
	ldr r2,=CORE3_MAILBOX
	cmp r4,r5
	beq loop_in_mailbox
	ldr r4,=CORE2
	ldr r2,=CORE2_MAILBOX
	cmp r4,r5
	beq loop_in_mailbox
	ldr r4,=CORE1
	ldr r2,=CORE1_MAILBOX
	cmp r4,r5
	beq loop_in_mailbox
	bl main
	
	.section ".data" "aw"
	.balign 4
	
	.globl Cores_Ready 
	Cores_Ready: .4bytes 0;
	
	.globl CORE1_MAILBOX 
	CORE1_MAILBOX: .4bytes 0;
	
	.globl CORE2_MAILBOX 
	CORE2_MAILBOX: .4bytes 0;
	
	.globl CORE3_MAILBOX 
	CORE3_MAILBOX: .4bytes 0;
