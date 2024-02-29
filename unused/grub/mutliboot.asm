;
; Created Date: Friday November 25th 2022
; Author: DefinitelyNotAGirl@github
; -----
; Last Modified: Friday November 25th 2022 12:42:26 pm
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

section .rodata
multibootHeader:
    ;magic
    dd 0x1BADB002           ; magic
    dw 0b1100000000000000   ; required features
                            ; 0: require modules to be 4KiB aligned
                            ; 1: require memory information to be available
    dw 0b0000000000000000   ; optional features
    dd 0x00000000           ; all magic fields added up must be uint32 0
    ;irrelevant
    dd 0x00000000           ; irrelevant for the time being
    dd 0x00000000           ; irrelevant for the time being
    dd 0x00000000           ; irrelevant for the time being
    dd 0x00000000           ; irrelevant for the time being
    dd 0x00000000           ; irrelevant for the time being
    ;video
    dd 0x00000001           ; mode_type (request text mode)
    dd 0x00000000           ; width
    dd 0x00000000           ; height
    dd 0x00000000           ; depth     (doesent matter, text mode)
