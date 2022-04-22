;****************************************************************************************************************************
;Program name: "Xsave Example".  This program demonstrates the use of assembly instructions xsave and xrstor to back up and *
;restore values in the state compnents of an X86 processor.  Copyright (C) 2020  Floyd Holliday                             *
;This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License  *
;version 3 as published by the Free Software Foundation.                                                                    *
;This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied         *
;warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.     *
;A copy of the GNU General Public License v3 is available here:  <https://www.gnu.org/licenses/>.                           *
;****************************************************************************************************************************
;
;
;
;
;========1=========2=========3=========4=========5=========6=========7=========8=========9=========0=========1=========2=========3**
;Author information
; Author name: Floyd Holliday
;  Author email: holliday@fullerton.edu
;
;Program information
;  Program name: Xsave Example
;  Programming languages: One modules in C++, one module in X86-64, and one module in Bash.
;  Date program began: 2020-Apr-12
;  Date of last update: 2020-Feb-15
;  Files in this program: sxavexrstordriver.cpp, xsavexrstor.asm, run.sh
;  Status: This program was tested by the author many times.
;  Purpose: The purpsoe of this program is to call xsavexrstormain
;
;This file
;  Name: xsavexrstor.asm
;  Language: X86
;  Syntax: Intel
;  Assemble: nasm -f elf64 -l xsavexrstor.lis -o xsavexrstor.o xsavexrstor.asm
;  Purpose: Demonstrate how to use xsave and xrstor.  Show that data backed up by xsave are really recovered by xrstor.
;  Limitations: The two instructions back component data (FPU,SSE,AVX).  They do not back up GPRs.
;
;References and credits:
;  Intel 64 and IA-32 Architectures Software Developer's Manual, Volume 3B, Chapter 13. [A free ebook at the Intel website.] 
;
;
;========1=========2=========3=========4=========5=========6=========7=========8=========9=========0=========1=========2=========3**
;
;===== Begin code area ======================================================================================================

extern printf                                     ;External C++ function for writing to standard output device

global xsavexrstormain                            ;This makes xsavexrstormain callable by functions outside of this file.

segment .data                                     ;Place initialized data here

welcomemessage db "Welcome to xsave and xrstor.", 10, 0

intentmessage db "This program will demonstrate the use of xsave and xrstor.", 10, 0

unsupportedmessage db "The xsave and xrstor instructions are not supported by this CPU.  No data will be backed up.", 10,
                   db "Use other strategies for backing up data.", 10, 0

firstvalues db "The program will assign 3 arbitrary values to 3 selected xmm registers as follows:",10,0
backup db "The program will now back all registers (except GPRs) by using xsave",10,0
secondvalues db "The program is assigning 3 new values to those registers as follows",10,0

restoreall db "The program will now restore the original values by use of xrstor", 10,
           db "The restored values are these:",10,0

threenumberform db "xmm5 = %7.4lf, xmm10 = %7.4lf, xmm14 = %7.4lf",10,10,0

goodbye db "This program will now return to the driver.  Have a nice day.", 10, 0

segment .bss                                      ;Place un-initialized data here.

segment .text                                     ;Place executable instructions in this segment.
xsavexrstormain:                                  ;Entry point.  Execution begins here.

;=========== Back up all the integer registers used in this program =======================================================
;Omitted from back up are rax, rip.
push       rbp                                    ;Save a copy of the stack base pointer
mov        rbp, rsp                               ;We do this in order to be 100% compatible with C and C++.
push       rbx                                    ;Back up rbx
push       rcx                                    ;Back up rcx
push       rdx                                    ;Back up rdx
push       rsi                                    ;Back up rsi
push       rdi                                    ;Back up rdi
push       r8                                     ;Back up r8
push       r9                                     ;Back up r9
push       r10                                    ;Back up r10
push       r11                                    ;Back up r11
push       r12                                    ;Back up r12
push       r13                                    ;Back up r13
push       r14                                    ;Back up r14
push       r15                                    ;Back up r15
pushf                                             ;Back up rflags

;=========== Show the welcome message =====================================================================================

mov qword  rax, 0                                 ;Zero indicates no data from SSE will be outputted.
mov        rdi, welcomemessage                    ;"Welcome to xsave and xrstor."
call       printf                                 ;Display the message using library function

;=========== Show the intent message ======================================================================================
mov qword  rax, 0                                 ;Zero indicates no data from SSE will be outputted.
mov        rdi, intentmessage                     ;"This program will demonstrate the use of xsave and xrstor."
call       printf                                 ;Display the message using library function

;=========== Test the current machine to determine if it supports xsave and xrstor. =======================================
mov        rax,1
cpuid
and        rcx,0x0000000004000000
cmp        rcx, 0
je         notsupported

mov rax,0
mov rdi,firstvalues
call printf

;=========== Set up some values in 3 registers of SSE =====================================================================
mov        rax, 0x4000000000000000      ;1.0
push       rax
movsd      xmm5, [rsp]
pop        rax

mov        rax, 0x4030000000000000      ;16.0
push       rax
movsd      xmm10, [rsp]
pop        rax

mov        rax, 0x408E000000000000      ;960.0
push       rax
movsd      xmm14, [rsp]
pop        rax

;Now there are values in xmm5, xmm10, and xmm14.  Let's display those values.
mov rax,3
movsd xmm0,xmm5
movsd xmm1,xmm10
movsd xmm2,xmm14
mov rdi,threenumberform
call printf

mov rax,0
mov rdi,backup
call printf

mov rax,0
mov rdi,secondvalues
call printf

;========== Perform a back up using xsave =================================================================================
;Here is the setup for calling xsave
mov        rax, 0x000000000000000d                ;Place 13 in rax.  This number is provided in the Intel manual
mov        rcx, 0                                 ;0 is parameter for subfunction 0, also found in the Intel manual
cpuid                                             ;Obtain information about the cpu
;Now rcx hold the number of bytes needed to store all the data in all the components: FPU,SSE,AVX

sub rsp, rcx                                      ;Create space on the stack for all the data to be backed up
mov rax, rsp
cqo
mov r8,64
div r8
;The remainder, rdx, is important.  By subtracting rdx from rsp then rsp will be on a 64-byte boundary
sub rsp, rdx
push rdx                      ;Save this number for later use.  The 64-byte boundary is at rsp+8.
mov        rax, 0x000000000000000d
mov        rcx, 0
cpuid
xsave      [rsp+1*8]          ;All data have been copied to the stack starting at rsp+8, which is a 64-byte boundary

;=========== The back up using xsave is complete ==========================================================================









;=========== Begin the intended purpose of this module ====================================================================

;This is the region where the working source code for this function belongs.  The programmer may use and modify
;any registers

;Now let's change the values in those three registers
mov        rax, 0x3FF0000000000000      ;1.0
push       rax
movsd      xmm5, [rsp]
pop        rax

mov        rax, 0x3FD0000000000000      ;0.25
push       rax
movsd      xmm10, [rsp]
pop        rax

mov        rax, 0x3FBE000000000000      ;0.1172
push       rax
movsd      xmm14, [rsp]
pop        rax

;Now confirm the values stored in the three selected registers
push qword 0                            ;As usual get on the 16-byte boundary
mov rax,3
movsd xmm0,xmm5
movsd xmm1,xmm10
movsd xmm2,xmm14
mov rdi, threenumberform
call printf
add rsp, 8                              ;Same as pop a quadword from the stack

;=========== End of the intended purpose of this module ===================================================================













;========== Next restore the original values using xrstor =================================================================
mov rax,0
mov rdi,restoreall
call printf

;Perform the setup block
mov        rax, 0x000000000000000d
mov        rcx, 0
cpuid
xrstor     [rsp+8]    ;Restore the original data to all the registers by reading it from rsp+8

pop        rdx                          ;Recover the number of bytes subtracted from the top of stack
add        rsp, rdx
add        rsp, rcx                     ;Remove from the stack the area used to store state components 0, 1, and 2.

;The stack is now in the state it was before xsave was called.
;========== End of restoring the original values to all the registers (except GPRs) =======================================

;Let's find out if our three selected registers have their original values.
mov rax,3
movsd xmm0,xmm5
movsd xmm1,xmm10
movsd xmm2,xmm14
mov rdi, threenumberform
call printf

jmp conclusion

notsupported:
mov        rax, 0                                 ;Make sure printf does not attempt to output any floating point values.
mov        rdi, unsupportedmessage                ;"The xsave and xrstor instructions are not supported by this CPU...."
call       printf
jmp        done

conclusion:
push qword 0                                      ;Make rsp divisible by 16 for the benefit of printf
mov qword  rax, 0                                 ;Zero indicates no data from SSE will be outputted.
mov        rdi, goodbye                           ;"This program will now return to the driver.  Have a nice day."
call       printf                                 ;Display the message using library function
add        rsp,8                                  ;Reverse the push of 5 lines earlier.

done:
;=========== Now cleanup and return to the caller =========================================================================

popf                                              ;Restore rflags
pop        r15                                    ;Restore r15
pop        r14                                    ;Restore r14
pop        r13                                    ;Restore r13
pop        r12                                    ;Restore r12
pop        r11                                    ;Restore r11
pop        r10                                    ;Restore r10
pop        r9                                     ;Restore r9
pop        r8                                     ;Restore r8
pop        rdi                                    ;Restore rdi
pop        rsi                                    ;Restore rsi
pop        rdx                                    ;Restore rdx
pop        rcx                                    ;Restore rcx
pop        rbx                                    ;Restore rbx
pop        rbp                                    ;Restore rbp

mov qword  rax, -5                                ;Send the -5 to the caller program.

ret
;====== The End ===========================================================================================================

;To computer science students:
;There is a matter of nice etiquete involved here.  When we assembly programmers create a function to be called by 
;functions written by others we have the responsibility to leave the playing field in the same state in which we found it.
;Here is an example for another part of life: when you and your friends have picnic in a city park and when you finish you are
;responsible to pick up your trash and leave the area as clean as you found it.  That principle carries over to assembly 
;programming.  When we create a function in assembly we want to put the data back in the same places where we found it.
;That is the reason we do a lot of pushes at the beginning of a function and a lot of pops at the end of the function.
;That responsibility is also way we should xsave other registers are the beginning of a function and xrstor them at the
;end of the function.  Will all this backup and restore really be enforced in our class?  Probably not.  Right now your 
;professor would just like to see nice modular working programs.












;Lesson learned:  During development of this program the author learned that printf will change 
;the value stored in xmm9.  That means xmm9 must be individually backedup before any call to printf
;and restored after calling printf.







;====== Secondary information not related to backing up xmm registers ==============================================
;The following pair of instructions writes information about the cpu to rcx.
;       mov rax,1
;       cpuid
;The contents of rcx can be checked to determine the presence of hardware and instructions according to 
;the following table.  If the bit in the left column is 1 then the hardware written to the right is
;present in the processor.
;   bit # | Outcome
;   ------|-----------------------
;       0 | SSE3 supported
;       9 | SSSE3 supported
;      19 | SSSE4.1 supported
;      20 | SSSE4.2 supported
;      26 | xsave/xrstor supported
;      28 | AVX supported
;
;Of interest to this program is the fact that bit #26 must be 1 in order for software to execute either
;of the xsave or xrstor instruction.
