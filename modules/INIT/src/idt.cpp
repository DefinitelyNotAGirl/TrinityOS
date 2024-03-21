/**
 * Created Date: Sunday February 11th 2024
 * Author: Lilith
 * -----
 * Last Modified: Sunday February 11th 2024 6:52:27 pm
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
#pragma once

#include <stdint.hxx>
#include <DESCRIPTOR_TABLES.hxx>

extern "C" void updateIDT();
extern "C" void DebugInterruptHandler_Entry();
GATE_DESCRIPTOR_64* InterruptDescriptorTable = (GATE_DESCRIPTOR_64*)0x3012000;
void setupIDT()
{
    //initialize idt to 0
    for(uint64_t i = 0;i<256;i++)
    {
		//skip page fault, double fault and GP fault handler so we can triple fault the cpu on demand
		if(i == 0x08)continue;
		if(i == 0x0D)continue;
		if(i == 0x0E)continue;
		uint64_t addr = &DebugInterruptHandler_Entry;
		GATE_DESCRIPTOR_64* Gate = &InterruptDescriptorTable[i];
		Gate->Type = 0x8E;//P = 1, DPL = 0, Type = 0xE
		Gate->TargetSelector = 0x0008;//kernel code segment selector
		Gate->IST = 0;
		Gate->reserved0 = 0;
		Gate->TargetOffset_0t15 = addr;
		Gate->TargetOffset_16t31 = addr>>16;
		Gate->TargetOffset_32t63 = addr>>32;
	}
    // memory descriptor
    IDTPseudo* pseudo = (IDTPseudo*)0x3011010;
    pseudo->limit = sizeof(GATE_DESCRIPTOR_64[256]);
    pseudo->address = 0x3012000;
    // set IDTR
    updateIDT();
}
