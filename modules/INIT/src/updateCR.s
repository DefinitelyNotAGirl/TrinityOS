/*
 * Created Date: Thursday February 8th 2024
 * Author: Lilith
 * -----
 * Last Modified: Thursday February 8th 2024 11:32:25 pm
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

.global updateGDT
updateGDT:
    mov $0x3011000, %rax
    LGDT (%rax)
    mov $0x3000000, %rax
    mov 0x08(%rax), %rdi
    mov 0x10(%rax), %rsi
    xor %rax, %rax
    mov $0x10, %ax
    mov %ax, %ss
    mov %ax, %es
    mov %ax, %ds
    mov %ax, %fs
    mov %ax, %gs
    popq %rax
    pushq $0x08
    pushq %rax
    retfq

.global updateIDT
updateIDT:
    mov $0x3011010, %rax
    LIDT (%rax)
	sti
    ret

.global updateCR3
updateCR3:
    mov %rdi, %cr3
    ret
