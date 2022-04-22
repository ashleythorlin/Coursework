
;===============================================================================================================================
;
;	Name: Ashley Thorlin
;	Class/Section: CPSC 240-01 (took final with 240-05)
;	Email: ashleythorlin@csu.fullerton.edu
;	Program Name: SSE Benchmarking Program
;
;===============================================================================================================================

extern printf
extern scanf
extern clock_speed
extern atof

global benchmark

section .data
	welcome db "Welcome to SSE bench marking program.", 10, 0
    promptrate db "Please enter the rate (m/sec): ", 0 
	prompttime db "Please enter the time duration (seconds): ", 0
    ;startclock db "[Invisible: Read cpu clock and save %ld", 10, 0
	;computedistance db "[Invisible: Compute the distance and save it]", 10, 0
    ;endclock db "[Invisible: Read the cpu clock one more time and save %ld.", 10, 0

    outputdistance db "The distance traveled was %.3lf meters.", 10, 0
    outputtics db "The computation required %ld tics or %lf nanosec.",10, 0

    stringformat db "%s", 0
    floatformat db "%lf",0

section .bss
section .text

benchmark:

;backup registers
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

push qword -1

;initialize 
mov r15, 0x0000000000000000               
movq xmm12, r15
movq xmm13, r15

;print welcome
mov rax, 0
mov rdi, stringformat
mov rsi, welcome			;"Welcome to SSE bench marking program."
call printf

;prompt
mov rax, 0
mov rdi, stringformat       
mov rsi, promptrate		;"Please enter the rate (m/sec): "
call printf                 

;get input
push qword -1
mov rax, 1
mov rdi, floatformat
mov rsi, rsp
call scanf

movsd xmm12, [rsp]

pop rax

;prompt
mov rax, 0
mov rdi, stringformat       
mov rsi, prompttime		;"Please enter the time duration (seconds): "
call printf              	   

;get input
push qword -1
mov rax, 1
mov rdi, floatformat
mov rsi, rsp
call scanf

movsd xmm13, [rsp]

pop rax

;==============================================================================================

;starting clock
mov rax, 0  
mov rdx, 0

cpuid                              ;identify cpu
rdtsc                             	;counts number of tics

shl rdx, 32
add rax, rdx

mov r14, rax                    	;save start clock time in r14

;print startclock
;mov rax, 0
;mov rdi, startclock             ;"[Invisible: Read cpu clock and save"
;mov rsi, r14                    ;tics from gettime function
;call printf                     

;==============================================================================================

;calculate distance
mulsd xmm12, xmm13

;==============================================================================================

;print computedistance
;mov rax, 0
;mov rdi, stringformat       
;mov rsi, computedistance	;"[Invisible: Compute the distance and save it]"
;call printf 

;ending clock
mov rax, 0  
mov rdx, 0

cpuid                              ;identify cpu
rdtsc                             	;counts number of tics

shl rdx, 32
add rax, rdx

mov r15, rax                    	;save start clock time in r15

pop rax

;print finalclock
;mov rax, 0
;mov rdi, endclock               ;"[Invisible: Read the cpu clock one more time and save it."
;mov rsi, r15
;call printf

;output distance
mov rax, 1
mov rdi, outputdistance             ; "The computation required %ld tics or %lf nanosec.",
movsd xmm0, xmm12                   ; elapsed time in tics
call printf

;calculate and print elapsed time

cvtsi2sd xmm10, r15             ;end clock to float
cvtsi2sd xmm7, r14              ;start clock to float
subsd xmm10, xmm7               ;end clock - start clock = elapsed time in tics

cvtsd2si r15, xmm10             ;elapsed time to int

mov r9, 0x4066666600000000		;3.6 in ieee
movq xmm11, r9 

divsd xmm10, xmm11              ; divide elapsed time by cpu speed (cpu GHz) = nanosec

mov rax, 1
mov rdi, outputtics             ; "The computation required %ld tics or %lf nanosec.",
mov rsi, r15                    ; elapsed time in tics
movsd xmm0, xmm10               ; elasped time in nanosec
call printf

;return to driver

movq xmm0, xmm10              ; pass nanosec to driver
;restore registers

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