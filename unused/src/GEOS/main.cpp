/**
 * Created Date: Wednesday October 26th 2022
 * Author: DefinitelyNotAGirl@github
 * -----
 * Last Modified: Saturday November 19th 2022 8:05:57 pm
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
#include "master.h"

NORETURN void bootstrap(uint32_t coreID);

void syserr()
{
    out << "the system encountered an internal error!" << endl;
    __asm__("hlt");
}

uint32_t getCurrentCoreID()
{
    __cpuid__(0x01);
    uint32_t EBX = getEBX();
    u8* data = (u8*)&EBX;
    uint8_t localApicId = data[3];
    return localApicId;
}

void sysfreeze()
{
    __asm__("cli");
    __asm__("hlt");
}

void geos_main()
{
    uint32_t coreID = getCurrentCoreID();
    if(coreID == 104) {
        /* things to do on the bootstrap processor */
        bootstrap(coreID);
        printERROR("fuck...");
        sysfreeze();
    } else {
        while(1)__asm__("hlt");
    }
}
