/**
 * Created Date: Friday October 28th 2022
 * Author: DefinitelyNotAGirl@github
 * -----
 * Last Modified: Friday October 28th 2022 7:59:04 am
 * Modified By: DefinitelyNotAGirl@github (definitelynotagirl115199@gmail.com)
 * -----
 * Copyright (c) 2022 DefinitelyNotAGirl@github
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
#include "../../master.h"

InterruptDescriptor64 createIDTEntry64(void(*ISR)(INTERRUPT_ARGS),u8 gateType,u8 privilegeLevel,u8 isValid,u8 IST,u16 selector)
{
    InterruptDescriptor64 desc;

    uint64_t offset = (uint64_t)ISR;
    u8 offsetBit = 0;

    //offset bits 0-15 go into bits 0-15 
    for(u8 I = 0;I<16;I++)
        setBit((u8*)desc.data,I,getBit((u8*)&offset,offsetBit++));

    //offset bits 16-63 go into bits 48-95
    for(u8 I = 48;I<96;I++)
        setBit((u8*)desc.data,I,getBit((u8*)&offset,offsetBit++));

    //selector
    for(u8 I = 0;I<16;I++)
        setBit((u8*)desc.data,I+16,getBit((u8*)&selector,I));

    //IST
    setBit((u8*)desc.data,32,getBit(&IST,0));
    setBit((u8*)desc.data,33,getBit(&IST,1));
    setBit((u8*)desc.data,34,getBit(&IST,2));
    //zero
    setBit((u8*)desc.data,44,0);
    //gate type
    setBit((u8*)desc.data,40,getBit(&gateType,0));
    setBit((u8*)desc.data,41,getBit(&gateType,1));
    setBit((u8*)desc.data,42,getBit(&gateType,2));
    setBit((u8*)desc.data,43,getBit(&gateType,3));
    //cpu privilege level
    setBit((u8*)desc.data,45,getBit(&privilegeLevel,0));
    setBit((u8*)desc.data,46,getBit(&privilegeLevel,1));
    //present bit
    setBit((u8*)desc.data,47,isValid);

    return desc;
}