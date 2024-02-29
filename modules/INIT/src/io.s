/*
 * Created Date: Thursday February 8th 2024
 * Author: Lilith
 * -----
 * Last Modified: Thursday February 8th 2024 9:02:26 pm
 * Modified By: Lilith (definitelynotagirl115169@gmail.com)
 * -----
 * Copyright (c) 2024 Lilith
 * 
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

.global inbyte
inbyte:
    xor %rax, %rax
    mov %rdi, %rdx
    inb %dx, %al
    ret

.global inword
inword:
    xor %rax, %rax
    mov %rdi, %rdx
    inw %dx, %ax
    ret

.global indoubleword
indoubleword:
    xor %rax, %rax
    mov %rdi, %rdx
    in %dx, %eax
    ret

.global outbyte
outbyte:
    mov %rsi, %rax
    mov %rdi, %rdx
    outb %al, %dx
    ret

.global outword
outword:
    mov %rsi, %rax
    mov %rdi, %rdx
    outw %ax, %dx
    ret

.global outdoubleword
outdoubleword:
    mov %rsi, %rax
    mov %rdi, %rdx
    out %eax, %dx
    ret
