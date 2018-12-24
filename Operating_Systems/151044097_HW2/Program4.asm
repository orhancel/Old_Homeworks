        ; 8080 assembler code
        .hexfile Program4.hex
        .binfile Program4.com
        ; try "hex" for downloading in hex format
        .download bin  
        .objcopy gobjcopy
        .postbuild echo "OK!"
        ;.nodump

	; OS call list
PRINT_B		equ 1
PRINT_MEM	equ 2
READ_B		equ 3
READ_MEM	equ 4
PRINT_STR	equ 5
READ_STR	equ 6
GET_RND		equ 7
TCreate 	equ 11
Texit		equ 8
TJoin		equ 9
TYield		equ 10

	; Position for stack pointer
stack   equ 0F000h

	org 000H
	jmp begin

	; Start of our Operating System
GTU_OS:	PUSH D
	push D
	push H
	push psw
	nop	; This is where we run our OS in C++, see the CPU8080::isSystemCall()
		; function for the detail.
	pop psw
	pop h
	pop d
	pop D
	ret
	; ---------------------------------------------------------------
	; YOU SHOULD NOT CHANGE ANYTHING ABOVE THIS LINE 


Numbers: DS 100

Numbers2: DS 100

   
F4:
	mvi c, 50	; c = 50
	MVI A, GET_RND	;
	LXI H, Numbers		; 

	loopRand:
		call GTU_OS	; call the OS
		mov m,B	;
		INX H		;
		INX H		;
		DCR c		; -- c
		JNZ loopRand	; goto loop if C!=0



		;Buble Sort

		mvi d, 50	; size of the list for outer loop
	outerLoop:  
		mvi c, 50	; size of the list for inner loop
		LXI H, Numbers	;  store list address to HL
	
	innerLoop:  
		mov a,m		; Take the first element
		INX H		; Get to next element
		INX H		;
	
		cmp m		; Compare A and new m
		JC dont_swap	; If A < M, no need to swap    
	   	
		;Do swap here

		MOV B, M	; Store M to B for temporarily
		mov m,a		; store A to second element's address
		dcx h		; Decrease address
		dcx h		; 
		mov m,B		; store temp B to first element's address
		inx h		; Increase again 
		inx h		; 
	
	dont_swap: 
		dcr c		; --C
		jnz innerLoop	; Loop until C == 0

		DCR D		; -- D
		jnz outerLoop	; Loop until D = 0
	

		;Print Sorted List
		mvi c, 50	; c = 50
		LXI H, Numbers	; 
		mov B,m		;
		MVI A, PRINT_B	; store the OS call code to A
		call GTU_OS	; call the OS

	loopPrint:
	
		call GTU_OS	; call the OS
		INX H		;
		INX H		;
		mov B,M		;
		DCR c		; -- c
		JNZ loopPrint	; goto loop if C!=0

	MVI A, TExit	; 
	call GTU_OS	; call the OS


F5:

	mvi c, 50	; c = 50
	MVI A, GET_RND	;
	LXI H, Numbers2		; 

	loopRand:
		call GTU_OS	; call the OS
		mov m,B	;
		INX H		;
		INX H		;
		DCR c		; -- c
		JNZ loopRand	; goto loop if C!=0



		;Buble Sort

		mvi d, 50	; size of the list for outer loop
	outerLoop:  
		mvi c, 50	; size of the list for inner loop
		LXI H, Numbers2	;  store list address to HL
	
	innerLoop:  
		mov a,m		; Take the first element
		INX H		; Get to next element
		INX H		;
	
		cmp m		; Compare A and new m
		JC dont_swap	; If A < M, no need to swap    
	   	
		;Do swap here

		MOV B, M	; Store M to B for temporarily
		mov m,a		; store A to second element's address
		dcx h		; Decrease address
		dcx h		; 
		mov m,B		; store temp B to first element's address
		inx h		; Increase again 
		inx h		; 
	
	dont_swap: 
		dcr c		; --C
		jnz innerLoop	; Loop until C == 0

		DCR D		; -- D
		jnz outerLoop	; Loop until D = 0
	

		;Print Sorted List
		mvi c, 50	; c = 50
		LXI H, Numbers	; 
		mov B,m		;
		MVI A, PRINT_B	; store the OS call code to A
		call GTU_OS	; call the OS

	loopPrint:
	
		call GTU_OS	; call the OS
		INX H		;
		INX H		;
		mov B,M		;
		DCR c		; -- c
		JNZ loopPrint	; goto loop if C!=0

	
	LXI H, Numbers2		; 
	mov B,m		;    First element
	MVI A, PRINT_B	; store the OS call code to A
	call GTU_OS	; call the OS

	mvi c, 10	; c = 10

	iterasyon:
		INX H		;   iterate to tenth element
		INX H		;
		DCR c		; -- c
		JNZ iterasyon	; goto loop if C!=0

	mov B,m		;    Tenth element
	MVI A, PRINT_B	; store the OS call code to A
	call GTU_OS	; call the OS

	mvi c, 40	; c = 40

	iterasyon2:
		INX H		;   iterate to tenth element
		INX H		;
		DCR c		; -- c
		JNZ iterasyon2	; goto loop if C!=0

	mov B,m		;    Tenth element
	MVI A, PRINT_B	; store the OS call code to A
	call GTU_OS	; call the OS
	
	MVI A, TExit	; 
	call GTU_OS	; call the OS



begin:
	LXI SP,stack 	; always initialize the stack pointer

	LXI b,F4	;
        MVI A, TCreate	; store the OS call code to A
	call GTU_OS	; call the OS
	MOV D, B	;

	LXI b,F5	;
        MVI A, TCreate	; store the OS call code to A
	call GTU_OS	; call the OS
	
        MVI A, TJoin	; Join with F5
	call GTU_OS	; call the OS

	MOV B,D		;  

	MVI A, PRINT_B	; store the OS call code to A
	call GTU_OS	; call the OS

	MVI A, TJoin	; Join with  F4
	call GTU_OS	; call the OS
	hlt		;	


