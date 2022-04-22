;****************************************************************************************************************************
;Program name: " ".      
;white space.  Copyright (C) 2021  Cyrus Baybay                                                                         
;This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License  *
;version 3 as published by the Free Software Foundation.                                                                    *
;This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied         *
;warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.     *
;A copy of the GNU General Public License v3 is available here:  <https://www.gnu.org/licenses/>.                           *
;****************************************************************************************************************************




;========1=========2=========3=========4=========5=========6=========7=========8=========9=========0=========1=========2=========3=========4=========5=========6=========7**
;Author information
;  Author name: Cyrus Baybay
;  Author email: cyrusbaybay@csu.fullerton.edu
;
;Program information
; Program name: 
;  Programming languages X86 with one module in C++
;  Date development of version 1.5 began 
;  Date development of version 1.5 completed 
;
;Purpose
;  
;
;Project information
;  Files: .cpp, .asm, r.sh
;  Status: The program has been tested extensively with no detectable errors. Improved on documation, and fixed bugs on the r.sh file.
;
;Translator information
;  Linux: nasm -f elf64 -l .lis -o .o .asm
;  References and credits
;  
;  

;Format information
;  
;  
;  
;  

;=============================================================================================================================
;=============================================Begin code area=================================================================
;=============================================================================================================================

extern printf       ;printing strings 

extern scanf        ;recieving input from user

extern fgets

extern stdin

extern strlen

global triangle     ;Making the fuction callable by other linked files

max_name_size equ 32

max_title_size equ 32

max_float_size equ 64


;=============================================================================================================================
;=============================================Declare messages================================================================
;=============================================================================================================================
section .data 

align 16

input_name db "Please enter your last name: ", 0

input_title db "Please enter your title: " , 0

input_sides db "Please enter the sides of your triangle separated by ws: ", 0

area_output db "The area of this triangle is %.5lf square units. ", 10, 0

length_output db "The length of the hypotenuse is %.5lf units" , 10, 0

goodbye db "Please enjoy your triangles ", 0

stringFormat db "%s", 0 

floatFormat db "%.5lf", 0

two_floatFormat db "%lf %lf", 0

align 64

;=============================================================================================================================
;=============================================Declare pointers================================================================
;=============================================================================================================================
segment .bss

m_name resb max_name_size

m_title resb max_title_size

float_result resb max_float_size

;=============================================================================================================================
;=============================================Begin application===============================================================
;=============================================================================================================================

segment .text

triangle:

;Back up the GPRs
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

;Backing up the reg

push    qword 0

;Show input message for last name

mov     rax, 0
mov     rdi, stringFormat   ; "%s"
mov     rsi, input_name     ; Please enter your last name
call    printf

;Take the user's name with white spaces

mov     rax, 0
mov     rdi, m_name         ;User's last name with whitespaces just incase
mov     rsi, max_name_size
mov     rdx, [stdin]
call    fgets

;Show the input message for user title

mov     rax, 0
mov     rdi, stringFormat   ; "%s"
mov     rsi, input_title    ; Please enter your title
call    printf

;Take the user's title with white spaces

mov     rax, 0
mov     rdi, m_title        ; User Title
mov     rsi, max_title_size
mov     rdx, [stdin]
call    fgets

;Show input message for the triangle separated by ws

mov     rax, 0
mov     rdi, stringFormat
mov     rsi, input_sides
call    printf

;Get the user's input for their sides of the triangle
push    qword 99

push    qword -1
push    qword -2

mov     rax, 0
mov     rdi, two_floatFormat
mov     rsi, rsp
mov     rdx, rsp
add     rdx, 8
call    scanf

movsd   xmm10, [rsp]
movsd   xmm13, [rsp]
movsd   xmm11, [rsp+8]
movsd   xmm14, [rsp+8]

pop     rax
pop     rax
;Putting the value 2.0 on to the XMM12 for division

mov     rax, 0x4000000000000000
push    rax
movsd   xmm12, [rsp]
pop     rax

;Calculate the area of the triangle

mulsd   xmm10, xmm11
divsd   xmm10, xmm12

;Output the area of the triangle message

movsd   xmm0, xmm10
mov     rdi, area_output
mov     rax, 1
call    printf

;Calculate the length hypotunes of the triangle

mulsd   xmm13, xmm13
mulsd   xmm14, xmm14
addsd   xmm13, xmm14
sqrtsd  xmm2, xmm13

;Output the length hypotenuse the triangle message

movsd   xmm0, xmm2
mov     rdi,  length_output
mov     rax,  1
mov     r13, rax
call    printf

;Show the goodbye message

mov     rax, 0
mov     rdi, stringFormat   ; "%s"
mov     rsi, goodbye        ; goodbye
call    printf

mov     rax, 0                           
mov     rdi, stringFormat                             
mov     rsi, m_title
call    printf

mov     rax, 0
mov     rdi, stringFormat              
mov     rsi, m_name
call    printf

;Keep the length of the triangle and output it on to the global function triangle.

movsd   xmm0, xmm2

pop     rax
pop     rax

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

;=============================================================================================================================
;=============================================End=============================================================================
;=============================================================================================================================