        ; 8080 assembler code
        .hexfile test.hex
        .binfile test.com
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



    
Strinput: DS 100		; Reserve memory for the input string
EnterIn: dw "Enter integer : ", 00AH, 00H ; For explanation 
EnterStr: dw "Enter string : ", 00AH, 00H ; For explanation 
ReadMemExplain: dw "Read into Memory : ", 00AH, 00H ; For explanation



begin:
	LXI SP, stack 		; Always initialize the stack pointer
	LXI B, EnterStr		; 
	MVI A, PRINT_STR	; Store the OS call code to A
	call GTU_OS			; Call the OS

	LXI B, Strinput		; Initialize memory for the input
	
	
	;Read a string 
	MVI A, READ_STR		; Store the OS call code to A
	call GTU_OS			; Call the OS
	;Print that string
	MVI A, PRINT_STR	; Store the OS call code to A
	call GTU_OS			; Call the OS

	LXI B, EnterIn		; For explanation
	MVI A, PRINT_STR	; Store the OS call code to A
	call GTU_OS			; Call the OS

	; Read a number and store it in Register B
	
	MVI A, READ_B		; Store the OS call code to A
	call GTU_OS			; Call the OS
	; Print that number on the screen
	MVI A, PRINT_B		; Store the OS call code to A
	call GTU_OS			; Call the OS

	
	LXI B, ReadMemExplain		; For explanation
	MVI A, PRINT_STR	; Store the OS call code to A
	call GTU_OS			; Call the OS

	;Read into memory adress 0
	LXI B, 0		; Adress to store
	MVI A, READ_MEM 	; Store the OS call code to A
	call GTU_OS		; Call the OS

	;Read memory adress 0
	MVI A, PRINT_MEM 	; Store the OS call code to A
	call GTU_OS		; Call the OS

	;Get a random number
	MVI A, GET_RND		;Get random number	
	call GTU_OS		; Call the OS
	MVI A, PRINT_B		; Store the OS call code to A
	call GTU_OS			; Call the OS


	hlt					; end program
