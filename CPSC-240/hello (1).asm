;********************************************************************************************
; Program name:          Hello World                                 								        *
; Programming Language:  x86 Assembly                                                       *
; Program Description:   This program prompts user for name, title, and favorite            *
;                        book/movie/game as part of a simulated conversation                *
;********************************************************************************************
; Author Information:                                                                       *
; Name:         Jesus Cazares                                                 		          *
; Email:        CazaresJMH50@csu.fullerton.edu                            		              *
; Institution:  California State University - Fullerton                                     *
; Course:       CPSC 240-03 Assembly Language                                               *
;                                                                                           *
;********************************************************************************************
; Copyright (C) 2021 Jesus Cazares                                                			    *
; This program is free software: you can redistribute it and/or modify it under the terms   *
; of the GNU General Public License version 3 as published by the Free Software Foundation. *
; This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY  *
; without even the implied Warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. *
; See the GNU General Public License for more details. A copy of the GNU General Public     *
; License v3 is available here:  <https://www.gnu.org/licenses/>.                           *
;                                                                                           *
;********************************************************************************************
; Program information                                                                       *
;   Program name: Sum of Integers - Array                                                   *
;   Programming languages: One module in C, One modules in X86.										          *
;   Files in this program: hello.asm, welcome.c, r.sh															          *
;   					                    																												  *
;                                                                                           *
;********************************************************************************************
; This File                                                                                 *
;    Name:      hello.asm                                                                   *
;    Purpose:   Prompt user for input and output a response using the user's input; then    *
;               return to welcome.c with return value of 0                                  *
;                                                                                           *
;********************************************************************************************

section .data
	;Layout the various prompts and responses for the simulated conversation

	text1 db "What is your name: ", 0
	text2 db "Enter your title (Mr, Ms, Programmer, Grunt, High Lord) ", 0
	text3_pt1 db "Hello %s ", 0
	text3_pt2 db "%s, what is your favorite book/movie/video game? ", 0
	text4 db "%s is really cool", 10, 0
	text5 db "This marks the end of this Hello program coded in x86 assembly", 10, 0
	text6 db "Until then, %s.", 10, 0
	text7 db "Take care. 0 will be returned to the os.", 10, 0
	stringFormat db "%s", 0 ; %s means any string


section .bss
	;Variables for the user input

	name resb 16
	title resb 15
	response resb 14

section .text
	extern printf ;For printing strings to console
	extern scanf  ;For recieving input from user
	global start

start:
	;Back up registers and set rbp to rsp
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

	;Prompt user for name
	mov rdi, stringFormat
	mov rsi, text1
	mov rax, 0
	call printf

	;Receive user input and set to variable 'name'
	mov rdi, stringFormat
	mov rsi, name                  ; stack pointer points to rsi were scanf input will be placed
	mov rax, 0
	call scanf

	;Prompt user for title
	mov rdi, stringFormat
	mov rsi, text2
	mov rax, 0
	call printf

	;Receive user input and set to variable 'title'
	mov rdi, stringFormat
	mov rsi, title                  ; stack pointer points to rsi were scanf input will be placed
	mov rax, 0
	call scanf

	;Greet user and prompt for favorite book/movie/game
	mov rdi, text3_pt1
	mov rsi, title
	mov rax, 0
	call printf
	mov rdi, text3_pt2
	mov rsi, name
	mov rax, 0
	call printf

	;Receive user input and set to variable 'response'
	mov rdi, stringFormat
	mov rsi, response                  ; stack pointer points to rsi were scanf input will be placed
	mov rax, 0
	call scanf

	;Comment on user's response
	mov rdi, text4
	mov rsi, response
	mov rax, 0
	call printf

	;Mark the end of program
	mov rdi, stringFormat
	mov rsi, text5
	mov rax, 0
	call printf

	;Say bye to user
	mov rdi, text6
	mov rsi, name
	mov rax, 0
	call printf

	;Explain that 0 will be returned to os
	mov rdi, stringFormat
	mov rsi, text7
	mov rax, 0
	call printf

	;Restore registers

	mov rax, 0 ;0 will be returned to os
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
