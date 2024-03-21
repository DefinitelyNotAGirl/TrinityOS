/*
 * Created Date: Monday March 18th 2024
 * Author: Lilith (definitelynotagirl115169@gmail.com)
 * -----
 * Last Modified: Monday March 18th 2024 11:22:40 am
 * Modified By: Lilith (definitelynotagirl115169@gmail.com)
 * -----
 * Copyright (c) 2024 Lilith Nitschke-Höfer (lilithnitschkehoefer@gmail.com)
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
.intel_syntax noprefix

.global interrupt_disassemble
interrupt_disassemble:
	;-
	;- prologue
	;- keep in mind: this is an interrupt handler
	.interrupt_disassemble.prologue:
	;-
	;- body
	;-
	.interrupt_disassemble.body:
		;? rdi holds mode
		;? rsi holds address or 0 if mode==0
		mov r8, [0x600008]
		mov r9, r8
		add r9, 96
		;? r8 holds trinity log bar0
		;? r9 holds data base address
		;+ get address of caller function
		pop rax ;* pop caller address from stack
		push rax ;* push address back to stack so we can actually return
		;+ figure out address to send
		test rdi, 0
		cmove rsi, rax
		;? rsi now holds address to send to debugger
		;+ send command to trinityLog device
		mov [r9], rsi
		movq [r8], (1<<0) | (1<<4)
		;+ wait on hardware to clear status
		.L1:
			mov rax, 0[r8]
			test r8, 0
			jne .L1
	;
	;-
	;- epilogue
	;-
	.interrupt_disassemble.epilogue:
		ret
