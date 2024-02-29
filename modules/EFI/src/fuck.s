/*
 * Created Date: Tuesday June 27th 2023
 * Author: DefinitelyNotAGirl@github
 * -----
 * Last Modified: Tuesday July 18th 2023 4:41:54 pm
 * Modified By: Lilith (definitelynotagirl115169@gmail.com)
 * -----
 * Copyright (c) 2023 DefinitelyNotAGirl@github
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

.global getRIP
.global readP32
.global getCR3
.global getCR4

.global efiLoaderHang
efiLoaderHang:
    cli
    hlt
    jmp efiLoaderHang //just in case

.global kjump
kjump:
    pushq %rcx
    ret

getCR3:
    mov %cr3, %rax
    ret

getCR4:
    mov %cr4, %rax
    ret

# addr in rcx
readP32:
    movl (%rcx), %eax
    ret

getRIP:
    pop %rax
    ret