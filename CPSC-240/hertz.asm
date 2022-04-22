;Header info
;
;
;
;
;

extern printf
extern scanf
extern atof
extern isfloat
extern stdin

global calc_hertz

two_point_zero equ 0x4000000000000000 ;change to hex form of 2.0

;============ Declare Messages ====================

segment .data

	intromessage db "We will find your power.", 10, 0
	inputname db "Please enter your name. You choose the format of your name: ", 0
	welcome db "Welcome %s", 10, 0
	inputresist db "Please enter the resistance in your circuit: ", 0
	inpucurrent db "Please enter the current flow in this circuit: ", 0
	thankyou db "Thank you %s.", 0
	output db "Your power consumption is %1.18lf watts.", 10, 0
	
	invalidinput db "Invalid input detected. You may run this program again.", 10, 0

	stringformat db "%s", 0
	floatformat db "%1.18lf", 0


;========== Declare Arrays =========================

segment .bss

	array: resq 2


;========= Instructions =========================

segment .text

calc_hertz:

	;push registers and set stack pointer to the base pointer
	push rbp
	mov rbp, rsp
	push rbx
	push rcx
	push rdx
	push rdi
	push rsi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
	pushf

	push qword 0 	;extra push to make an even number of pushes 

;===============================================================================================================================
	
	;prepare for loop later
	mov r12, 0	;counter
	mov r13, 2	;max num of inputs
	
	;display intro message
	mov qword rax, 0
	mov rdi, stringformat
	mov rsi, intromessage

	call printf

	;prompt user for name
	mov qword rax, 0
	mov rdi, stringformat
	mov rsi, inputname
	call printf

	;get user input
	mov qword rax, 0
	mov rdi, username
	mov rsi, 32
	mov rdx, [stdin]
	call fgets
	
	;display welcome
	mov qword rax, username
	mov rdi, stringformat
	mov rsi, welcome
	call printf
	
	; mov rax, 0					;tried to optimize above, if it doesn't work then just do old fashion "print welcome then print username" after removing newline from welcome string in .data
	; mov rdi, stringformat
	; mov rsi, username
	; call printf

;===============================================================================================================================

;input loop
input_nums:

	mov r14, 0x3ff0000000000000		;used to flag input if wrong input (in hexadecimal/ieee-754 format)
	mov r15, 0						;used to return 0 to c file if input is invalid
	
	cmp r12, r13					;compare counter (r12) to the input limit (r13)
	jge valid_input

	;prompt user for resistance
	add r12, 1 						;increments through the "loop"
	mov qword rax, 0
	mov rdi, stringformat
	mov rsi, inputresist
	call printf
	
	push qword 0
	
	;input float into rsp
	push qword 0
	mov rdi, stringformat			;takes user input as a string
	mov rsi, rsp					;points rsi to top of the stack to place input from scanf
	mov rax, 1						;set rax to 1 to tell scanf that it is a float
	call scanf
	
	;input validation
	mov rdi, rsp					;copies address of stack pointer to rdi to pass input value
	mov rax, 0
	call isfloat
	
	cmp rax, 0						;checks if isfloat returns false (if so, return 0 and exit asm file)
	je invalid_input
	
	mov rax, 1						;set rax to 1 to allow function to place float in xmm0
	call atof 						;c library function
	
	;move valid input into array
	movq [array + 8 * (r12 - 1)], xmm0    ; Copy atof output into array.  
    addsd xmm15, [array + 8 * (r12 - 1)] 	;add atof output to xmm15 registers
	
	
	pop rax 						;pops the offset before scanf
	
	jmp input_nums					;restarts loop

;===============================================================================================================================

invalid_input:
	mov rax, 0
	mov rdi, stringformat
	mov rsi, invalidinput
	call printf
	
	movq xmm15, r14
	
	jmp end_function				;jump to end of file

;===============================================================================================================================

;calculate hertz
valid_inputs:
	
	push qword 0
	
	movsd xmm13, [array] 				;copy resistance to xmm13
	mulsd xmm13, xmm13
	
	movsd xmm14, [array + 8]
	mulsd xmm14, xmm13
	
	movq xmm1, r14
	ucomisd xmm14, xmm1
	jb invalid_input
	
;===============================================================================================================================

end_function:
	
	;thank user	
	mov rax, username
	mov rdi, stringformat
	mov rsi, thankyou
	call printf
	
	;output power consumption ;theres a string and float input, check if you can even do that in one sentence, if not, split like explained below
	
	movsd xmm0, xmm14
	mov rdi, output
	mox rax, 1
	call printf
	
    movsd xmm0, xmm15               ; Copy area from xmm15 to xmm0 to be returned.
   
    pop rax                         ; Extra pop to align stack to 16 bytes.
    pop rax                         ; Remove extra push of -1 from stack.

    ; Restores all registers to their original state.
    popf                                                 
    pop rbx                                                     
    pop r15                                                     
    pop r14                                                      
    pop r13                                                      
    pop r12                                                      
    pop r11                                                     
    pop r10                                                     
    pop r9                                                      
    pop r8                                                      
    pop rcx                                                     
    pop rdx                                                     
    pop rsi                                                     
    pop rdi                                                     
    pop rbp

    ret
