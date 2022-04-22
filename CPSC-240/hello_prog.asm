;================================================================================================================================
;																																*
;  Author information																												*
;  Author name: Ashley Thorlin																									*
;  Author email: ashleythorlin@csu.fullerton.edu																				*
;																																*
;===============================================================================================================================*
;																																*
;Program information																											*
;  Program name: Hello World Program																							*
;  Programming languages: Main function in C++; "Hello" function in X86-64														*
;  Files in the program: hello_program.cpp, hello_prog.asm, run.sh															*
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
;  The intent of this program is to allow the user to input their name and receive a greeting from the program.					*
;																																*
;================================================================================================================================

extern printf

extern scanf

extern fgets

extern stdin

extern strlen

global hello_program

;================================================================================================================================

segment .data 							;Declare messages

inputname db "Please enter your first and last names: ", 0

inputtitle db "Please enter your title (Ms, Mr, Engineer, Programmer, etc): ", 0

outputmessage db "Hello %s %s. How has your day been so far? ", 0

outputday db " is nice.", 10, 0

endmessage db "The concludes the 'Hello' program written in x86.", 10, 0

stringformat db "%s", 0

;================================================================================================================================

segment .bss							;Define pointers for user input

user_name resb 16
user_title resb 16
user_day resb 16

;================================================================================================================================

segment .text

hello_program:

	;Backup registers
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

	;Show message for name input
	mov 	rax, 0
	mov		rdi, stringformat
	mov		rsi, inputname				;"Please enter your first and last names: "
	call 	printf
	
	;Get user input for name
	mov qword rax, 0
	mov		rdi, user_name				;example: Ashley Thorlin
	mov		rsi, 32
	mov 	rdx, [stdin]
	call	fgets
	
	mov		rdi, user_name
	call 	strlen
	mov		r14, rax
	mov 	[user_name+r14-1], byte 0
	
	
	
	;Show message for title input
	mov		rax, 0
	mov		rdi, stringformat
	mov 	rsi, inputtitle				;"Please enter your title (Ms, Mr, Engineer, Programmer, etc): "
	call 	printf	
	
	;Get user input for title
	mov	 	rax, 0
	mov 	rdi, user_title				;example: Programmer
	mov		rsi, 16
	mov		rdx, [stdin]
	call	fgets
	
	mov		rdi, user_title
	call 	strlen
	mov		r14, rax
	mov 	[user_title+r14-1], byte 0
	
	;Show greeting
	mov		rax, 0
	mov		rdi, outputmessage
	mov 	rsi, user_title			; "Hello Programmer Ashley Thorlin"
	mov 	rdx, user_name
	call	printf
	
	;Get user input for day
	mov		rax, 0
	mov		rdi, user_day				;example: "Good"
	mov 	rsi, 16
	mov 	rdx, [stdin]
	call	fgets
	
	mov		rdi, user_day
	call 	strlen
	mov		r14, rax
	mov 	[user_day+r14-1], byte 0
	
	;Show message for day response
	mov		rax, 0
	mov		rdi, stringformat			
	mov 	rsi, user_day				;"Good"	(prints the users previous response)
	call	printf
	
	mov		rax, 0
	mov		rdi, stringformat
	mov 	rsi, outputday				;" is nice."
	call	printf
	
	;Show end of program message
	mov		rax, 0
	mov		rdi, stringformat
	mov 	rsi, endmessage				;"The concludes the 'Hello' program written in x86."
	call	printf
	
	mov rax, user_name					;return user_name to the os
	
	;Restore registers to original state
	popf		
	pop r15
	pop r14
	pop r13
	pop	r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rsi
	pop rdi
	pop rdx
	pop rcx
	pop rbx
	pop rbp
	
	ret
	
;================================================================================================================================
	
	
	
	
	
	