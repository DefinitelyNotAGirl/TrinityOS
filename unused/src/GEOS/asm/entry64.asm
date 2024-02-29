;
; Created Date: Monday December 5th 2022
; Author: DefinitelyNotAGirl@github
; -----
; Last Modified: Monday December 5th 2022 6:27:16 am
; Modified By: DefinitelyNotAGirl@github (definitelynotagirl115199@gmail.com)
; -----
; Copyright (c) 2022 DefinitelyNotAGirl@github
; 
; Permission is hereby granted, free of charge, to any person
; obtaining a copy of this software and associated documentation
; files (the "Software"), to deal in the Software without
; restriction, including without limitation the rights to use, copy,
; modify, merge, publish, distribute, sublicense, and/or sell copies
; of the Software, and to permit persons to whom the Software is
; furnished to do so, subject to the following conditions:
; 
; The above copyright notice and this permission notice shall be
; included in all copies or substantial portions of the Software.
; 
; THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
; EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
; MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
; NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
; HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
; WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
; OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
; DEALINGS IN THE SOFTWARE.
;

;.pro:
;.main:
;.epi:

global printError
global printSuccess
global kexit
global clearRSI
global setR15
global setR14

extern entry64

section .entry64Code
_start:
    cli

    mov rbx, 1200
    mov rcx, 0xB8000
    xor rax, rax
.screen_clear_loop:
    mov qword [rcx], rax
    add rcx, 8
    dec rbx
    cmp rbx, 0
    jne .screen_clear_loop

    ;configure stack
    mov rsp, 0x5FFFF0
    mov rbp, rsp

    ;clear registers (dont clear rdi,rsp and rbp)
    xor rax, rax
    xor rbx, rbx
    xor rcx, rcx
    xor rdx, rdx
    xor rsi, rsi
    xor r8 , r8 
    xor r9 , r9 
    xor r10, r10
    xor r12, r12
    xor r13, r13
    xor r14, r14
    xor r15, r15

    call entry64

setR15:
    mov r15, rdi
    ret

setR14:
    mov r14, rdi
    ret
    
kexit:
    cli
    hlt

;(not my proudest moment ngl)
; mom, can we have reboot?
; no, we have reboot at home.
; reboot at home:
tripleFault:
    lgdt [TRIPLEFAULTGDT.pointer]; load invalid gdt
    int 0xFF;attempt to raise interrupt, should cause triple fault

TRIPLEFAULTGDT:
.pointer:
    dq 0
    dw 0
