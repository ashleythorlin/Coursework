;================================================================================================================================
;
;	Ashley Thorlin
;	CPSC 240-01
;	ashleythorlin@csu.fullerton.edu
;	Electricity Program
;
;================================================================================================================================

extern  printf

extern scanf

extern fgets

extern strlen

extern stdin
 
global copernicus

constant_k equ 0x4200BEC41C000000

max_name equ 32

max_title equ 32
 
;================================================================================================================================

;Declare messages used in program 
segment .data

align 16

description db "This program will help you find the force.", 10, 0

input_part1 db "Please enter the electrical charge on particle 1: ", 0

input_part2 db "Please enter the electrical charge on particle 2: ", 0

input_dist db "Please enter the distance between the particles in meters: ", 0

input_name db "", 0

input_title db "Please enter your title: ", 0

endmessage db "Thank you. Your force is %1.18lf Newtons.", 10, 0

stringformat db "%s", 0

floatformat db "%lf", 0

align 64

;================================================================================================================================

segment .bss

user_name resb max_name

user_title resb max_title

;================================================================================================================================

segment .text

copernicus:

	;Backup registers
	push rbp
	mov  rbp, rsp
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
	
	;display description of program
	mov qword rax, 0
	mov 	rdi, stringformat
	mov 	rsi, description				;"This program will help you find the force."
	call 	printf
	
	;---particle 1---
	
	;prompt user for particle 1 charge
	mov qword rax, 0
	mov 	rdi, stringformat
	mov 	rsi, input_part1				;"Please enter the electrical charge on particle 1:"
	call 	printf
	
	;get charge 1 from user
	push qword 0
	mov qword rax, 0
	mov 	rdi, floatformat
	mov 	rsi, rsp
	call 	scanf
	
	movsd 	xmm10, [rsp]
	pop 	rax
	
	;---particle 2---
	
	;prompt user for particle 2 charge
	mov qword rax, 0
	mov 	rdi, stringformat
	mov 	rsi, input_part2				;"Please enter the electrical charge on particle 2:"
	call 	printf
	
	;get charge 2 from user
	push qword 0
	mov qword rax, 0
	mov 	rdi, floatformat
	mov 	rsi, rsp
	call 	scanf
	
	movsd 	xmm11, [rsp]
	pop 	rax
	
	;---distance---
	
	;prompt user for distance
	mov qword rax, 0
	mov 	rdi, stringformat
	mov 	rsi, input_dist					;"Please enter the distance between the particles in meters:"
	call 	printf
	
	;get distance from user
	push qword 0
	mov qword rax, 0
	mov 	rdi, floatformat
	mov 	rsi, rsp
	call 	scanf
	
	movsd 	xmm12, [rsp]
	pop 	rax
	
	call fgets 
	
	;---name---
	
	;prompt user for last name
	mov qword rax, 0
	mov 	rdi, stringformat
	mov 	rsi, input_name					;"Please enter your last name:"
	call 	printf
	
	;get last name from user
	push qword 0
	mov qword rax, 0
	mov 	rdi, user_name
	mov 	rsi, max_name
	mov 	rdx, [stdin]
	call 	fgets
	
	pop rax
	
	mov		rdi, user_name
	call	strlen
	mov 	r14, rax
	mov 	[user_name+r14-1], byte 0
	
	;---title---
	
	;prompt user for title
	mov qword rax, 0
	mov 	rdi, stringformat
	mov 	rsi, input_title				;"Please enter your title:"
	call 	printf
	
	;get title from user
	push qword 0
	mov qword rax, 0
	mov 	rdi, user_title
	mov 	rsi, max_title
	mov 	rdx, [stdin]
	call 	fgets
	
	pop rax
	
	mov		rdi, user_title
	call	strlen
	mov 	r14, rax
	mov 	[user_title+r14-1], byte 0
	
	pop rax
	
	;---calculate force---
	
	push qword 0
	mulsd 	xmm10, xmm11		;multiply q1 * q2
	mulsd 	xmm12, xmm12		;square distance (xmm12)
	divsd 	xmm10, xmm12		;divide xmm10/xmm12 ((q1*q2)/r^2)
	mov 	rbx, constant_k		;put k value on xmm13 for multiplying
	push 	rbx
	mulsd 	xmm10, [rsp]		;multiply quotient by k
	pop rax
	
	push qword 0				;save copy of result before calling printf
	movsd 	[rsp], xmm10
	
	;---end message---
	mov 	rax, 3
	mov 	rdi, endmessage					;"Thank you. Your force is %7.5lf Newtons."
	call 	printf
	
	pop 	rax
	pop 	rax
	
	mov 	rax, user_title					;return user_title to the os
	
	;pop the system stack
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
	
;================================================================================================================================