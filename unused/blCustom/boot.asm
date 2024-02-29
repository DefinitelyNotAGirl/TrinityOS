;
; Created Date: Tuesday November 15th 2022
; Author: DefinitelyNotAGirl@github
; -----
; Last Modified: Tuesday November 15th 2022 1:05:46 am
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

[BITS 16    ]
[ORG  0x7C00]

%define MEMRESERVEDEND 0x100FF
%define MEMSIZE 0x10000

section .text
_start:
    mov bl, 0x0F    ;white text on black background
    mov bh, 0x00    ;page 0

    mov al, 0x41
    call printChar

    ;load rest of bootloader

    ;load 64-bit kernel

    ;load empty idt (will be disabled until the 64-bit kernel actually puts handlers in place)
    ;load minimal gdt (nothing fancy, we dont use segmentation in long mode anyways)
    ;flip PE
    ;flip PAE

    ;obligatory hangup
    cli
    hlt

printChar:
    mov ah, 0x0E
    int 0x10
    ret


;MBR BOOT SIGNATURE
times 510-($-$$) db 0
dw 0xAA55

%include "src/data.asm"
%include "src/entry32.asm"
%include "src/entry64.asm"

;FILL BOOTLOADER TO 32KB
times 32768-($-$$) db 0
