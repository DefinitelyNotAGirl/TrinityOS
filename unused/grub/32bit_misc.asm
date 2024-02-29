;
; Created Date: Friday November 25th 2022
; Author: DefinitelyNotAGirl@github
; -----
; Last Modified: Friday November 25th 2022 12:23:02 pm
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

section .text

global getEAX
global getEBX
global getECX
global getEDX
global getEDI
global getESI
global getEBP
global getESP

getEAX:
    mov eax, 0
    mov eax, EAX
    ret

getEBX:
    mov eax, 0
    mov eax, EBX
    ret

getECX:
    mov eax, 0
    mov eax, ECX
    ret

getEDX:
    mov eax, 0
    mov eax, EDX
    ret

getEDI:
    mov eax, 0
    mov eax, EDI
    ret

getESI:
    mov eax, 0
    mov eax, ESI
    ret

getEBP:
    mov eax, 0
    mov eax, EBP
    ret

getESP:
    mov eax, 0
    mov eax, ESP
    ret
    