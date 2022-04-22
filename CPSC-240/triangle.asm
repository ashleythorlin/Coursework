;================================================================================================================================
;																																*
;  Author information																											*
;  Author name: Ashley Thorlin																									*
;  Author email: ashleythorlin@csu.fullerton.edu																				*
;																																*
;===============================================================================================================================*
;																																*
;Program information																											*
;  Program name: Triangle Program																								*
;  Programming languages: Main function in C++; "Triangle" function in X86-64													*
;  Files in the program: pythagoras.c, triangle.asm, r.sh																		*
;																																*
;===============================================================================================================================*
;																																*
;Copyright (C) 2021 Ashley Thorlin                                                                    				            *
;	This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License   *
;	version 3 as published by the Free Software Foundation.                                                                     *
;	This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied          *
;	warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.      *
;	A copy of the GNU General Public License v3 is available here:  <https://www.gnu.org/licenses/>.  							*
;																																*
;===============================================================================================================================*
;																																*
;Purpose																														*
;  The intent of this program is to allow the user to input the lengths of two sides of a right triangle and the program will	*
;	output the triangle's area and the length of the hypotenuse.																*
;																																*
;================================================================================================================================

extern printf

extern scanf

global triangle

two_point equ 0x4000000000000000

max_name_size equ 32

max_title_size equ 32

;================================================================================================================================

segment .data 							;Declare messages

align 16

input_name db "Please enter your last name: ", 0

input_title db "Please enter your title (Mr, Ms, Nurse, Engineer, etc): ", 0

input_sides db "Please enter the sides of your triangle separated by whitespace: ", 0

output_area db "The area of this triangle is %.5lf sq units.", 10, 0

output_hypo db "The length of the hypotenuse is %.5lf units", 10, 0

exit_message db "Enjoy your triangle ", 0

stringformat db "%s", 0

floatformat db "%.5lf", 0

floatsformat db "%lf%lf", 0

align 64

;================================================================================================================================

segment .bss							;Define pointers for user input

user_name resb max_name_size

user_title resb max_title_size

;================================================================================================================================

segment .text

triangle:

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
	
	push 	qword 0
	
	;prompt user for name
	
	mov 	rax, 0
	mov 	rdi, stringformat
	mov 	rsi, input_name			;"Please enter your last name: "
	call 	printf
	
	;get user input for name
	mov		rax, 0
	mov		rdi, user_name			;example: Thorlin
	mov		rsi, max_name_size
	call	scanf
	
	;prompt user for title
	mov		rax, 0
	mov		rdi, stringformat
	mov 	rsi, input_title		;"Please enter your title (Mr, Ms, Nurse, Engineer, etc): "
	call 	printf
	
	
	;get user input for title
	mov		rax, 0
	mov		rdi, user_title			;example: Programmer
	mov		rsi, max_title_size
	call	scanf
	
	;prompt user for triangle sides
	mov 	rax, 0
	mov 	rdi, stringformat
	mov 	rsi, input_sides		;"Please enter the sides of your triangle separated by whitespace: "
	call 	printf
	
	;get user input for sides
	push 	qword -1
	push 	qword -2
	mov 	rax, 0
	mov 	rdi, floatsformat
	mov 	rsi, rsp				;move first to top of stack
	mov		rdx, rsp				;move second side to top of stack (first is now below)
	add 	rdx, 8					;idk tbh
	call 	scanf
	
	movsd 	xmm1, [rsp]				;set xmm1 to value at top of stack
	movsd 	xmm2, xmm1				;copy xmm1 to xmm2 (one copy to use for area, other for hypotenuse)
	movsd 	xmm3, [rsp+8]			;set xmm3 to value second in the stack
	movsd 	xmm4, xmm3				;copy xmm3 to xmm4
	pop 	rax                     ;Reverse "push qword -2"
	pop 	rax                     ;Reverse "push qword -1"
	
	;-----Calculate Area------
	
	;put 2.0 on stack
	mov     rax, 0x4000000000000000
	push    rax
	movsd   xmm12, [rsp]
	pop     rax

	;multiply sides
	mulsd 	xmm1, xmm3				;multiply side 1 by side 2
		
	;divide by two
	;mov 	rbx, two_point				;prepare "two" (initialized value of 2.0) for stack
	;push 	rbx						;push "two" to top of stack
	divsd	xmm1, xmm12				;divide xmm0 (side 1 X side 2) by 2.0
	;pop 	rax						;remove "two" from top of stack
	
	;output area of triangle
	movsd	xmm0, xmm1
	mov 	rdi, output_area		;"The area of this triangle is <area>"
	mov 	rax, 1
	call 	printf
	
	;calculate hypotenuse length
	mulsd 	xmm2, xmm2				;square xmm2 (copy of side 1 value)
	mulsd 	xmm4, xmm4				;square xmm4 (copy of side 2 value)
	addsd 	xmm2, xmm4				;add xmm2 and xmm4 (squared side values)
	sqrtsd	xmm5, xmm2				;get square root of the added values, save to xmm5
	
	;output hypotenuse
	movsd 	xmm0, xmm5
	mov 	rdi, output_hypo		;"The length of the hypotenuse is %.5lf units"
	mov 	rax, 1
	mov 	r13, rax
	call 	printf
	
	;goodbye message
	mov		rax, 0
	mov 	rdi, stringformat
	mov		rsi, exit_message			;"Enjoy your triangle "
	call	printf
	
	mov 	rax, 0
	mov		rdi, stringformat
	mov		rsi, user_title
	call 	printf
	
	mov 	rax, 0
	mov		rdi, stringformat
	mov		rsi, user_name
	call 	printf
	
	;return hypotenuse length to triangle
	movsd 	xmm0, xmm5
	
	pop 	rax
	pop 	rax
	
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