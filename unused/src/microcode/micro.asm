;
; Created Date: Wednesday March 22nd 2023
; Author: DefinitelyNotAGirl@github
; -----
; Last Modified: Wednesday March 22nd 2023 10:31:23 pm
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


global write64
global write32
global write16
global write8

global get64
global get32
global get16
global get8

section .text

write64:
    mov [rdi], rsi
    ret

write32:
    mov [rdi], esi
    ret

write16:
    mov [rdi], si
    ret

write8:
    mov rax, rsi
    mov [rdi], al
    ret

get64:
    mov rax, [rdi]
    ret

get32:
    mov eax, [rdi]
    ret

get16:
    xor rax, rax
    mov ax, [rdi]
    ret

get8:
    xor rax, rax
    mov al, [rdi]
    ret