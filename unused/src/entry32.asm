;
; Created Date: Friday November 25th 2022
; Author: DefinitelyNotAGirl@github
; -----
; Last Modified: Friday November 25th 2022 4:16:03 pm
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
%define EFER_LME   1 << 8
%define EFER_NXE   1 << 11
%define CR0_PE     1 << 0
%define CR0_PG     1 << 31
%define CR4_PSE    1 << 4
%define CR4_PAE    1 << 5
%define CR4_PGE    1 << 7

extern stage3
global _start
global exit
global passCRT64
section .text
_start:
    cli

    ;reset stack
    mov esp, 0x0000FFEF
    mov ebp, 0x00000000

    mov eax, 0x10
    mov es, eax;reset ES, former screen segment
    mov fs, eax;
    mov gs, eax;
    xor eax, eax

    push dword 0xB8000
    push edi
    call stage3

    cli
    hlt

passCRT64:
    pop edi; pop bootInfo address into EDI
    ;copy entry64 to from 0xbc00 to 0x800000
    mov edx, 0x00bc00
    mov eax, 0x800000
    mov ecx, 0x004000
    ;kids, dont forget to actually call the functions you wanna use 
    ;(i deff. didnt just run into bug due to not calling memcpy *cough* cough*)
    call memcpy

    ;set EFER.LME
    mov ecx, 0xC0000080; EFER MSR selector.
    rdmsr
    or eax, EFER_LME
    or eax, EFER_NXE
    wrmsr 

    ; Point CR3 to PML4
    mov eax, 0x200000
    mov cr3, eax

    mov  eax, CR4_PAE | CR4_PGE | CR4_PSE; Set PAE- (Physical Address Extensions) and
    mov  cr4, eax              ; PGE- (Page Global Enable) and PSE- (Page Size Extensions)

    mov ebx, cr0            ; Get CR0.
    or  ebx, CR0_PG | CR0_PE; Set PG (Paging) and PE (Protection Enabled).
    mov cr0, ebx            ; Set flags to CR0.

    jmp 0x30:0x800000; far jump to entry64
    
    cli
    hlt

; edx: source
; eax: dst
; ecx: len
memcpy:
    push edi

    mov edi, ecx
    xor ecx, ecx
.loop:
    cmp edi, 0
    je .epi
    dec edi

    mov ecx, [edx]
    mov [eax], ecx

    inc edx
    inc eax
    jmp .loop
.epi:
    pop edi
    ret


exit:
    cli
    hlt

section .data
align 4096