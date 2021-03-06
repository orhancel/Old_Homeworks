        ; 8080 assembler code
        .hexfile Program5.hex
        .binfile Program5.com
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

	;This program adds numbers from 0 to 50. The result is stored at variable
	





	
F1:
	mvi c, 50	; c = 50
	mvi B, 0	; init B with 0
        MVI A, PRINT_B	; store the OS call code to A

	loop1:
	
		MVI A, TYield	; 
		call GTU_OS	; call the OS
		MVI A, PRINT_B	; store the OS call code to A
		call GTU_OS	; call the OS
		INR B		; ++B
		DCR c		; -- c
		JNZ loop1	; goto loop if C!=0

	MVI A, TExit	; 
	call GTU_OS	; call the OS

F3:

	mvi c, 100	; c = 50
	mvi B, 50	; init B with 0
        MVI A, PRINT_B	; store the OS call code to A

	loop2:
		MVI A, TYield	; 
		call GTU_OS	; call the OS
		MVI A, PRINT_B	; store the OS call code to A
		call GTU_OS	; call the OS
		INR B		; ++B
		DCR c		; -- c
		JNZ loop2	; goto loop if C!=0

	MVI A, TExit	; 
	call GTU_OS	; call the OS

begin:
	LXI SP,stack 	; always initialize the stack pointer

	LXI b,F1	;
        MVI A, TCreate	; store the OS call code to A
	call GTU_OS	; call the OS
	MOV D, B	;

	LXI b,F3	;
        MVI A, TCreate	; store the OS call code to A
	call GTU_OS	; call the OS
	
        MVI A, TJoin	; store the OS call code to A
	call GTU_OS	; call the OS

	MOV B,D		;
	MVI A, TJoin	; store the OS call code to A
	call GTU_OS	; call the OS
	hlt		;	




