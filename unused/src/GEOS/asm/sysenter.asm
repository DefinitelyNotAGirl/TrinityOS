;
; Created Date: Saturday November 12th 2022
; Author: DefinitelyNotAGirl@github
; -----
; Last Modified: Saturday November 12th 2022 5:44:06 am
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

global sysentry
global interruptGetError

section .text

interruptGetError:
    mov rax, 0; explicitly zero out rax
    push 0x00000000; push 32-bit 0
    pop rax; pop 64 bits off stack into rax
    ret; return value assumed in rax

sysentry:
    ret