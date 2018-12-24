        ; 8080 assembler code
        .hexfile Program1.hex
        .binfile Program1.com
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
TExit		equ 8
TJoin		equ 9
TYield		equ 10
FileCreate  equ 12
FileClose   equ 13
FileOpen    equ 14
FileRead    equ 15
FileWrite   equ 16
FileSeek    equ 17



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
	




Numbers: DS 100

   
Begin:
	LXI SP, stack	; Always initialize the SP
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


	MVI A, READ_STR		; Store the OS call code to A
	call GTU_OS			; Call the OS

	MVI A,FileCreate    ;
	call GTU_OS			;

	MVI A,FileOpen      ;
	call GTU_OS			;


	MOV E, B            ;

	MVI D, 100			;

	LXI H, Numbers	;  store list address to HL
	MVI A,FileWrite     ;
	call GTU_OS			;

	MOV B, E            ;

	MVI A,FileClose	    ;
	call GTU_OS			;



	hlt		;	












