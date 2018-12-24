        ; 8080 assembler code
        .hexfile binary.hex
        .binfile binary.com
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


Numbers: DS 100

Error: DW 'ERROR',00AH,00H ; null terminated error str
left: DW 'left',00AH,00H ; null terminated error str
right: DW 'right',00AH,00H ; null terminated error str
   
Begin:
	LXI SP, stack	; Always initialize the SP
	mvi c, 50	; c = 50
	MVI A, GET_RND	;
	LXI H, Numbers		; 
loopRand:
	call GTU_OS	; call the OS
	mov m,B	;
	INX H			;
	INX H			;
	DCR c		; -- c
	JNZ loopRand	; goto loop if C!=0



	
	mvi d, 50	; size of the list for outer loop
outerLoop:  
	mvi c, 50	; size of the list for inner loop
	LXI H, Numbers	;  store list address to HL
	
innerLoop:  
	mov a,m		; Take the first element
	INX H			;
	INX H			;
	
	cmp m		; Compare A and new m
	JC dont_swap	; If A < M, no need to swap       	

	MOV B, M	;
	mov m,a		; 
	dcx h		; 
	dcx h		; 
	mov m,B		; 
	inx h		; Increase again so we updated
	inx h		; the list index for another iteration
	
dont_swap: 
	dcr c		; --C
	jnz innerLoop	; Loop until C == 0

	DCR D		; -- D
	jnz outerLoop	; Loop until D = 0
	


	mvi c, 50	; c = 50
	LXI H, Numbers		; 
	mov B,m	;
        MVI A, PRINT_B	; store the OS call code to A
	call GTU_OS	; call the OS


loopPrint:
	
	call GTU_OS	; call the OS
	INX H			;
	INX H			;
	mov B,M	;
	DCR c		; -- c
	JNZ loopPrint	; goto loop if C!=0



	;Read from keyboard
	MVI A, READ_B		; Store the OS call code to A
	call GTU_OS		; Call the OS
	
	
	mov E,B			;
	mvi d,100	;
	
	mvi c,0		;
	

Search:
	MOV A, D		;
	CMP C			;
	JC NotFound		; 
	JZ NotFound		; 

	MOV A, E		; A = B, move the key into Register A
	LXI H,Numbers+48	; middle of array
	CMP M			; Compare A with current element
	JZ Found		; If zero, element found, jump to Found
	JC leftHalf		; If M < B
	jmp rightHalf		;


leftHalf:
	
	LXI B, left		; Put the address of error string 
						; in registers B and C
	MVI A, PRINT_STR	; Store the OS call code to A 
	call GTU_OS			; Call the OS 
	LDA d		;	
	
	
	
	MOV B,d		; 
						
	MVI A, PRINT_B	; Store the OS call code to A 
	call GTU_OS			; Call the OS
	  
	JMP Search		;
rightHalf:
	LXI B, right		; Put the address of error string 
						; in registers B and C
	MVI A, PRINT_STR	; Store the OS call code to A 
	call GTU_OS			; Call the OS 
	Mov A,c		;
	RRC;
	
	mov B, A		; 
						
	MVI A, PRINT_B	; Store the OS call code to A 
	call GTU_OS			; Call the OS  
	JMP Search		;
	
NotFound:
	LXI B, Error		; Put the address of error string 
						; in registers B and C
	MVI A, PRINT_STR	; Store the OS call code to A 
	call GTU_OS			; Call the OS 
	hlt			;
	
Found:
	MOV B, D		; Move the index of the key to Register B
					; into Register B
	MVI A, PRINT_B	; Store the OS call code to A 
	call GTU_OS		; Call the OS 




	hlt		; end program









