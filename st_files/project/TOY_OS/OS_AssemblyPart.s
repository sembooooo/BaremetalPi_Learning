
	
	AREA |.text|, CODE,READONLY,ALIGN=2 
		;The above directive will tell the compiler that the below written is code 
        ; and to keep the code in the .text section with an alignment of 2 bytes and it is only readonly 
	THUMB                
		;This assembler directive will tell the compiler to create only thumb instruction set
	REQUIRE8
		;The REQUIRE8 directive specifies that the current file requires eight-byte alignment of the stack. 
	PRESERVE8
		;This directive instructs the linker to preserve 8-byte alignment of the stack. 
		;This is a requirement of the Arm Architecture Procedure Call Standard (AAPCS).

	EXTERN RunPt
		;This tells the compiler that RunPt is defined in another file
	EXPORT startOS
	EXPORT SysTick_Handler
		;The export directive will allow the functions to be used in another file also
		



;This startOS function runs only once that too during startng of our OS
;Things this will do is
;	1. restore all the registers
;	2. enable interrupts
;	3. make the processor run the current task
; note: after this SysTick_Handler comes into play to swap the tasks.
	
startOS PROC
	LDR R0,=RunPt   ; Currently running thread
	LDR R2,[R0]     ; store the value of the address of TCB in R2
	LDR SP,[R2]		; Store the stack address of the current thread
	POP {R4-R11}	; Restoring registers        
	POP {R0-R3}		; Restoring registers
	POP {R12}
	;now what we will do is we will add the stack pointer by 4 bytes so that we can skip the LR (link register)
	;and will go to PC and will store that in LR so that we can use BX LR instruction to go back to the code
	ADD SP,SP,#4
	POP {LR}
	CPSIE I			; Enable interrupts at processor level
	BX LR
	ENDP 
	
; BREIF ABOUT SYSTICK HANDLER: 
; ----------------------------
;This handler method is invoked periodically after certain duration of time.
;As this an interupt the following registers will get stacked automatically with SP at its top 
;	1. PSR 
;	2. PC
;	3. LR
;	4. R12
;	5. R3,R2,R1,R0
; So we do not have to stack them again so here what we have to do is store the current R4-R11 registers
; Point the stack towards the next TCB and restore the next tasks R4-R11 registers 
; and when exiting from the handler the processor will automatically restore the above set of registers but of the next
; task as the SP is now pointing towards the next task stack

SysTick_Handler
	CPSID I			; Disable all the interrupts
	PUSH {R4-R11}	; store the other register apart from those that were automatically stored
	LDR R0,=RunPt	; Current running thread
	LDR R1,[R0]
	STR SP, [R1]	; Store the SP value in the current TCB 
	LDR R1,[R1,#4]  ; R1 = RunPt->next.
	STR R1,[R0]		; RunPt = RunPt->next   Traversing in the linked list
	LDR SP,[R1]
	POP {R4-R11}	; restore regs r4-11
    CPSIE   I       ; tasks run with interrupts enabled
    BX      LR      ; restore R0-R3,R12,LR,PC,PSR
	
	ALIGN
	END
	
	
	
	

	
	
