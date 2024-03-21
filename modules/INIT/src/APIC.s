/**
* Created Date: Monday March 11th 2024
* Author: Lilith (definitelynotagirl115169@gmail.com)
* -----
* Last Modified: Monday March 11th 2024 4:38:15 am
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

.global GetLocalProcessorID
GetLocalProcessorID:
	# ;+ fetch Local APIC base
	mov rcx, 0x0000001B
	rdmsr # ;. EDX:EAX now holds contents of the APIC base register
	shr rdx, 32
	or rax, rdx # ;. rax now holds all 64 bits of the APIC base register
	and rax, 0xFFFFFFFFFFFFF000 # ;- clear bits 0-11 as they are not part of the address
	# ;+ get APIC ID (Treat APIC id as processor id)
	mov rax, rdi # ;. rdi now APIC base address
	mov eax, [rdi+0x20]
	shl rax, 24
	ret