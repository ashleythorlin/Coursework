;===============================================================================================================================
;
;	Name: Ashley Thorlin
;	Class/Section: CPSC 240-01 (took final with 240-05)
;	Email: ashleythorlin@csu.fullerton.edu
;	Program Name: Hello World
;
;===============================================================================================================================

extern printf

global hello_world

section .data
	helloworld db "Hello, World", 10, 0

    stringformat db "%s", 0

section .bss
section .text

hello_world:

; Backup registers
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

mov rax, 0
mov rdi, stringformat
mov rdx, helloworld
call printf

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