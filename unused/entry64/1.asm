;
; Created Date: Sunday January 8th 2023
; Author: DefinitelyNotAGirl@github
; -----
; Last Modified: Sunday January 8th 2023 2:48:01 am
; Modified By: DefinitelyNotAGirl@github (definitelynotagirl115199@gmail.com)
; -----
; Copyright (c) 2023 DefinitelyNotAGirl@github
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

loadRSDT:
.pro:
.main:
.epi:
    ret

loadXSDT:
.pro:
.main:
.epi:
    ret

getACPI:
.pro:
    push rbx
    push rcx

    xor rcx, rcx
    xor rbx, rbx
.main:
    call getRSDP
    cmp rax, 0
    je .error

    mov rbx, rax; copy RSDP address to rbx

    ;
    ; check ACPI revision
    ;
    add rbx, 15; get address of revision field
    mov byte rcx, [rbx]; rcx now contains ACPI revision (version)

    ;print ACPI revision (this only works of rumbers <= 9)
    add rcx, 0x0230
    mov word [r13], cx
    add r13, 2

    ;return rcx back to the revision number
    sub rcx, 0x0230
    cmp rcx, 2
    jge .xsdt
    call loadRSDT
    jmp .rsdt
.xsdt:
    call loadXSDT
.rsdt:

    jmp .epi
.error:
    call printError
.epi:
    pop rcx
    pop rbx
    ret

getRSDP:
.pro:
    push rbx
    push rcx
    push r14
    xor rbx, rbx
    xor rcx, rcx
    xor r14, r14
.main:
    mov r14, 0x2052545020445352
.CHECKKNOWN:
    ;
    ; SEA BIOS (qemu)
    ;
    mov rbx, 0xF6CB0
    mov qword rax, [rbx]
    cmp rax, r14
    je .epi

.CHECKEBDA:
    call getEBDAbase
    mov rbx, rax
    mov rcx, rax
    add rcx, 1024; EBDA+1KiB
.EBDALOOP:
    mov qword rax, [rbx]
    cmp rax, r14
    je .epi

    add rbx, 16
    cmp rbx, rcx
    jne .EBDALOOP
.MEMREG_IN:
    mov rbx, 0xE0000
    mov rcx, 0xFFFFF
.MEMREG_LOOP:
    mov qword rax, [rbx]
    cmp rax, r14
    je .epi

    add rbx, 16
    cmp rbx, rcx
    jge .MEMREG_LOOP
.notFound:
    call printError
    xor rax, rax
    jmp .epi_ret
.epi:
    mov rax, rbx
.epi_ret:
    pop r14
    pop rcx
    pop rbx
    ret

getEBDAbase:
.pro:
    push rbx
    push rcx
    xor rax, rax
    xor rbx, rbx
    xor rcx, rcx
.main:
    mov bx, [0x40E]; EBDA pointer
    mov ah, bh
    mov rcx, 16
    mul rcx
    add al, bl
.epi:
    pop rcx
    pop rbx
    ret

