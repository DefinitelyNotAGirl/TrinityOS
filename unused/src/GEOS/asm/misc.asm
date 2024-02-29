;
; Created Date: Friday November 4th 2022
; Author: DefinitelyNotAGirl@github
; -----
; Last Modified: Saturday November 19th 2022 8:05:57 pm
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

global tripleFault

global getRAX
global getRBX
global getRCX
global getRDX
global getRDI
global getRSI
global getRBP
global getRSP
global getEAX
global getEBX
global getECX
global getEDX
global getEDI
global getESI
global getEBP
global getESP
global getR8
global getR9
global getR10
global getR11
global getR12
global getR13
global getR14
global getR15

global getcr0
global getcr2
global getcr3
global getcr4

section .text

; uint64_t getR..()
getEAX:
    mov rax, 0
    mov eax, EAX
    ret

getEBX:
    mov rax, 0
    mov eax, EBX
    ret

getECX:
    mov rax, 0
    mov eax, ECX
    ret

getEDX:
    mov rax, 0
    mov eax, EDX
    ret

getEDI:
    mov rax, 0
    mov eax, EDI
    ret

getESI:
    mov rax, 0
    mov eax, ESI
    ret

getEBP:
    mov rax, 0
    mov eax, EBP
    ret

getESP:
    mov rax, 0
    mov eax, ESP
    ret

getRAX:
    mov rax, RAX
    ret

getRBX:
    mov rax, RBX
    ret

getRCX:
    mov rax, RCX
    ret

getRDX:
    mov rax, RDX
    ret

getRDI:
    mov rax, RDI
    ret

getRSI:
    mov rax, RSI
    ret

getRBP:
    mov rax, RBP
    ret

getRSP:
    mov rax, RSP
    ret

getR8:
    mov rax, R8
    ret

getR9:
    mov rax, R9
    ret

getR10:
    mov rax, R10
    ret

getR11:
    mov rax, R11
    ret

getR12:
    mov rax, R12
    ret

getR13:
    mov rax, R13
    ret

getR14:
    mov rax, R14
    ret

getR15:
    mov rax, R15
    ret

getcr0:
    mov rax, cr0
    ret

getcr2:
    mov rax, cr2
    ret

getcr3:
    mov rax, cr3
    ret

getcr4:
    mov rax, cr4
    ret