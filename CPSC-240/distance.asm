;================================================================================================================================
;
;	Name: Ashley Thorlin
;	Class/Section: CPSC 240-01
;	Email: ashleythorlin@csu.fullerton.edu
;	Program Name: Heron's Area
;
;================================================================================================================================

;external functions
extern printf
extern scanf
extern isfloat
extern atof

global area

;================================================================================================================================

section .data

    intro db "Welcome to SSE bench marking program.", 10, 0

    rate db "Please enter the rate (m/sec): ", 0
	prompttime db "Please enter the time duration (seconds): ", 0
    validmessage db 10, "The distance traveled was %.3lf meters.", 10, 0
	
	semiperimeter db 10, "The semi perimeter is %.5lf ", 10, 0
	
	driver db 10, "The area will be returned to the driver.", 10, 0
	
    stringformat db "%s", 0 

;================================================================================================================================

section .bss

    array: resq 2  ;will hold the side input              

;================================================================================================================================

section .text

area:

; Back up registers
    push rbp
    mov rbp, rsp
    push rdi
    push rsi
    push rdx
    push rcx
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15
    push rbx
    pushf

    push qword 0

    mov r12, 0                 ;counter for loop
    mov r13, 2                 ;max iterations
    mov r14, 0                 ; flag for square root of negative   


	;print introduction
    mov rdi, stringformat
    mov rsi, intro
    mov rax, 0
    call printf

;================================================================================================================================


	;print sides
    mov rdi, stringformat 
    mov rsi, rate
    mov rax, 0                 
    call printf

	;get input from user
    push qword 0
    mov rdi, stringformat      ;get user's input as a string
    mov rsi, rsp 
    mov rax, 0 
    call scanf

	;convert string to float
    mov rax, 1
    call atof                  ;call atof to convert ascii to float

	add r12, 1                 ;increment counter

	;put valid input in array
    movq [array + 8 * (r12 - 1)], xmm0    ;copy atof output to array
    addsd xmm15, [array + 8 * (r12 - 1)]  ;add output to xmm15
	
	pop rax
	
	;print sides
    mov rdi, stringformat 
    mov rsi, rate
    mov rax, 0                 
    call printf

	;get input from user
    push qword 0
    mov rdi, stringformat      ;get user's input as a string
    mov rsi, rsp 
    mov rax, 0 
    call scanf

	;convert string to float
    mov rax, 1
    call atof                  ;call atof to convert ascii to float

	add r12, 1                 ;increment counter

	;put valid input in array
    movq [array + 8 * (r12 - 1)], xmm0    ;copy atof output to array
    addsd xmm15, [array + 8 * (r12 - 1)]  ;add output to xmm15
	


    pop rax

    jmp inputloop              ;back to top of loop
	;end of loop

;================================================================================================================================

	;if invalid input, jump to end of  program
    invalidinput:
	
	pop rax
	;print invalid message
    mov rax, 0
    mov rdi, stringformat
    mov rsi, invalidmessage
    call printf

    jmp inputloop				;jump back to loop

;================================================================================================================================

;calculates valid inputs
    validinput:
	
    push qword 0

;prints out sides
    movsd xmm0, [array]             ;side 1 in xmm0 (a)
    movsd xmm1, [array + 8]         ;side 2 in xmm1 (b)
    movsd xmm2, [array + 16]        ;side 3 in xmm2 (c)
    mov rdi, validmessage             ;message to print out sides
    mov rax, 3                      ;will print 3 floats
    call printf

;formula: sqrt(s(s-a)(s-b)(s-c))  
;semi-perimeter = s = (a + b + c)/2  

;calculate output

;calculate semi-perimeter
    mov rax, 0x4000000000000000     ;hex value of 2.0
    movq xmm8, rax                  ;move value to xmm8 for division

    divsd xmm15, xmm8               ;(a + b + c)/2.0 
	
;print out perimeter of triangle

    movsd xmm0, xmm15               ;copy area to xmm0 for printing
    mov rdi, semiperimeter           ;output message
    mov rax, 1
    call printf

;calculate area

    movsd xmm13, xmm15              ;copy semi-perimeter to xmm13
    subsd xmm13, [array]            ;(s-a)

    movsd xmm10, xmm15              ;copy semi-perimeter to xmm10
    subsd xmm10, [array + 8]        ;(s - b)

    movsd xmm11, xmm15              ;copy semi-perimeter to xmm11
    subsd xmm11, [array + 16]       ;(s - c)

    mulsd xmm15, xmm13              ;s(s-a)
    mulsd xmm15, xmm10              ;X (s-b)
    mulsd xmm15, xmm11              ;X (s-c)

	;ensure value is positive in order to take square root
    movq xmm1, r14                  ;copy r14 = 0 to xmm1 register
    ucomisd xmm15, xmm1             ;compare s(s-a)(s-b)(s-c) to 0
    jb invalidinput                 ;if negative, jump to invalidinput
    
    sqrtsd xmm15, xmm15             ;square root xmm15 (sqrt(s(s-a)(s-b)(s-c)))

;end of program
endprogram:

	;return message
    mov rax, 0
    mov rdi, stringformat
    mov rsi, driver
    call printf

    movsd xmm0, xmm15               ;move area from xmm15 to xmm0 to return
   
    pop rax
    pop rax

    ;pop registers to normal state
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
