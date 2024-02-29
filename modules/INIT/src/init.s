/*
 * Created Date: Wednesday February 7th 2024
 * Author: Lilith
 * -----
 * Last Modified: Thursday February 29th 2024 5:18:25 am
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
.extern kernel_entry_cpp

.global sysDBGExit
sysDBGExit:
    mov %rdi, %r15
    mov %rsi, %r14
    mov %rdx, %r13
    mov %rcx, %r12
    mov %r8, %r11
    mov %r9, %r10
    int $0x08

.global sysDBGint
sysDBGint:
    int $0xFF
	ret

clearObsoleteCodePage:
    //xor %rax, %rax
    //mov %rax, (%r15)
    mov $kernel_entry_cpp, %rax
    call %rax

.global init
init:
    //*
    //* disable interrupts
    //*
    cli
    //*
    //* everything sucks so lets just hardcode a bit of page table data
    //*
    //! we cannot use any symbols at this time
    //? assume %rdx to hold physical address of TRINITY_MEMORY_VITAL* TRINITY_VITAL
    mov 0x10(%rdx), %r14
    mov 0x18(%rdx), %r10
    mov 0x20(%rdx), %r11
    mov 0x28(%rdx), %r12
    mov 0x30(%rdx), %r13
    mov 0x38(%rdx), %rsp
    mov 0x40(%rdx), %rbp
    mov 0x48(%rdx), %r15
    mov 0x50(%rdx), %r9
    xor %rdx, %rdx # reset rdx for later division operations
    //? assume %r10 to hold physical address of init module code
    //? assume %r11 to hold physical address of init module rw data
    //? assume %r12 to hold physical address of init module ro data
    //? assume %r13 to hold physical address of init module bss
    //? assume %r14 to hold physical address of data page where we will put the page tables
    //*
    //* construct pml4e
    //*
    mov %r14, %rax
    mov $0x7 ,%rbx
    or %rbx, %rax
    add $0x1000, %rax
    //mov %rax, %rbp
    mov %rax,(%r14)
    //*
    //* construct pdpe
    //*
    add $0x1000, %rax
    mov %rax, 0x1000(%r14)
    //*
    //* construct pages
    //*
    //? memory map
    mov %rbp, %rax
    mov $0x8000000000000087, %rbx
    or %rbx, %rax
    mov %rax, 0x2060(%r14)
    //? memory map 2
    mov %r9, %rax
    mov $0x8000000000000087, %rbx
    or %rbx, %rax
    mov %rax, 0x2068(%r14)
    //? page table page 1
    mov %r14, %rax
    mov $0x8000000000000087, %rbx
    or %rbx, %rax
    mov %rax, 0x2090(%r14)
    //? page table page 2
    mov %r15, %rax
    mov $0x8000000000000087, %rbx
    or %rbx, %rax
    mov %rax, 0x2098(%r14)
    //? stack
    mov %rsp, %rax
    mov $0x8000000000000087, %rbx
    or %rbx, %rax
    mov %rax, 0x2010(%r14)
    //? init module code
    mov %r10, %rax
    mov $0x87, %rbx
    or %rbx, %rax
    mov %rax, 0x2020(%r14)
    //? init module rw data
    mov %r11, %rax
    mov $0x8000000000000087, %rbx
    or %rbx, %rax
    mov %rax, 0x2028(%r14)
    //? init module ro data
    mov %r12, %rax
    mov $0x8000000000000087, %rbx
    or %rbx, %rax
    mov %rax, 0x2030(%r14)
    //? init module bss
    mov %r13, %rax
    mov $0x8000000000000087, %rbx
    or %rbx, %rax
    mov %rax, 0x2038(%r14)
    //? identity map current page for jump instruction fetch
    mov %r10, %rax
    mov $0x200000, %r9
    div %r9
    mov $0x8, %r9
    mul %r9
    mov %rax, %r15 # ? r15 now holds page number*8
    div %r9
    add %r14, %r15
    add $0x2000, %r15 # ? r15 now holds page table entry address
    mov $0x200, %r9
    div %r9
    mov %rax, %rsi # ? rsi now holds PML3 number
    mov $0x8, %r9
    mul %r9
    mov %rax, %rdi # ? rdi now holds PML3 number*8
    add %r14, %rdi
    add $0x1000, %rdi # ? rdi now holds PML3 entry address
    mov %rsi, %rax
    mov $0x200, %r9
    mul %r9
    mov %rax, %rsi
    add %r14, %rsi
    add $0x2000, %rsi # ? rsi now holds address of page directory
    //? rsi: address of page directory
    //? rdi: PML3 entry address
    mov %rsi, %rax
    mov $0x7 ,%rbx
    or %rbx, %rax
    mov %rax, %r8 # this is just for debugging purposes
    mov %rax, (%rdi)
    //? r15: page table entry address
    mov %r10, %rax
    mov $0x87, %rbx
    or %rbx, %rax
    mov %rax, (%r15)
    //*
    //* update cr3
    //*
    mov %r14, %cr3
    mov $0x600000, %rsp
    //*
    //* initiate kernel
    //*
    call clearObsoleteCodePage
    //*
    //* should not be called, just here in case
    //*
    //call sysEXIT_SUCCESS
    //!
    //! debug exit code
    //!

.global sysEXIT_SUCCESS
sysEXIT_SUCCESS:
    movq $0xFFFFFFFFFFFFFFFF, %rax
    mov %rax, %rbx
    mov %rax, %rcx
    mov %rax, %rdx
    mov %rax, %rdi
    mov %rax, %rsi
    mov %rax, %rbp
    mov %rax, %rsp
    mov %rax, %r8
    mov %rax, %r9
    mov %rax, %r10
    mov %rax, %r11
    mov %rax, %r12
    mov %rax, %r13
    mov %rax, %r14
    mov %rax, %r15
    LIDT (%rax)
    int $0xFF

