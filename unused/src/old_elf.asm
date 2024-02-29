;
; Created Date: Wednesday November 30th 2022
; Author: DefinitelyNotAGirl@github
; -----
; Last Modified: Wednesday November 30th 2022 12:42:58 pm
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
%define ELF_MAGIC 0x464c457f
ELF_ERROR_EXE:
    mov ebx, str_ERROR_ELF_EXE
    call print32
    cli
    hlt
ELF_ERROR_ABI:
    mov ebx, str_ERROR_ELF_ABI
    call print32
    cli
    hlt
ELF_ERROR_BITS:
    mov ebx, str_ERROR_ELF_BITS
    call print32
    cli
    hlt
ELF_ERROR_MAGIC:
    mov ebx, str_ERROR_ELF
    call print32
    cli
    hlt

ELF_COMPLETE:
    mov ebx, str_ELF_COMPLETE
    call print32
    ret

loadELF:
    ;read elf file at 0x8600
    ;use esi for data structure base addresses
    mov esi, 0x8600;bruh, i just debugged for like 3 hours, this crap was set to 0x8000 instead of 0x8400

    ;first 4 bytes should be elf magic
    mov eax, [esi]
    cmp eax, ELF_MAGIC
    jne ELF_ERROR_MAGIC

    xor eax, eax; mov to 8 or 16 bit register doesent implicitly zero extend
    mov al, [esi+4]
    cmp al, 1
    jne ELF_ERROR_BITS

    mov al, [esi+8]
    cmp al, 0
    jne ELF_ERROR_ABI

    mov ax, [esi+16]
    cmp ax, 2
    jne ELF_ERROR_EXE

    mov edx, [esi+24]; program entry point
    mov [0x7C00], edx
    xor ebx, ebx
    xor ecx, ecx
    mov cx , [esi+42]; size of program headers
    mov bx , [esi+44]; number of program headers
    mov esi, [esi+28]; base address of program header table
    add esi, 0x8600

.programHeaderLoop:
    cmp bx, 0
    je .programHeaderLoopEnd

    mov eax, [esi]
    cmp eax, 1
    jne .programHeaderLoopFinal
    
    xor eax, eax
    mov al, [esi+24]
    cmp al, 0
    je .programHeaderSegData
.programHeaderSegCode:
    mov eax, 0x10200
    jmp .programHeaderLoopLoad
.programHeaderSegData:
    mov eax, 0x16000
.programHeaderLoopLoad:
    push ecx
    xor ebp, ebp
    add ebp, 0x8400; base address of file
    add ebp, [esi+4];offset into file
    mov ecx, [esi+16]
    call memcpy
    pop ecx
.programHeaderLoopFinal:
    dec bx
    add esi, ecx
    jmp .programHeaderLoop
.programHeaderLoopEnd:
    ret