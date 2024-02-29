/*
 * Created Date: Tuesday June 27th 2023
 * Author: DefinitelyNotAGirl@github
 * -----
 * Last Modified: Tuesday June 27th 2023 12:35:22 am
 * Modified By: DefinitelyNotAGirl@github (definitelynotagirl115169@gmail.com)
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

 # fuck clang

 /*

.global strreverse
.extern strlen

.text

# rcx is str address
strreverse:
    call strlen # rax is now string length
    movq %crcx, %rdx
    add %rax, %rdx # str end on rdx
    movq %rcx, %rax # write return value to rax (return input for syntax reasons)
    movq %rcx, %r8 # copy rcx to r8 for later use
.loopPUSH:
    # should rcx == rdx move on to next loop
    cmp %rcx, %rdx
    je .loopPOP

    movq [%rcx], %r9
    push %r9
    inc %rax # rax++

    jmp .loopPUSH # loop
.loopPOP:
    # should rax be 0 return from function
    cmp %r8, %rax
    je .exit

    pop %r9
    movq %r9, [%r8]
    dec %r8 # r8--

    jmp .loopPOP # loop
.exit:
    ret


*/