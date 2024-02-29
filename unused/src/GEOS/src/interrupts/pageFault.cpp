/**
 * Created Date: Friday November 11th 2022
 * Author: DefinitelyNotAGirl@github
 * -----
 * Last Modified: Friday November 11th 2022 7:42:20 pm
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

INTERRUPT pageFaultHandler(INTERRUPT_ARGS)
{
    sysentry();
    uint64_t error = interruptGetError();
    uint8_t basicError = 0;

    uint64_t cr2 = getcr2();

    printERROR("page fault!\n");

    bool present          = getBit((uint8_t*)&error,0);
    bool write            = getBit((uint8_t*)&error,1);
    bool user             = getBit((uint8_t*)&error,2);
    bool reservedWrite    = getBit((uint8_t*)&error,3);
    bool instructionFetch = getBit((uint8_t*)&error,4);
    bool MPKViolation = getBit((uint8_t*)&error,5);
    bool ShadowStackAccess = getBit((uint8_t*)&error,6);

    setBit(&basicError,present,0);
    setBit(&basicError,write  ,1);
    setBit(&basicError,user   ,2);

    printHEXU64(cr2,"[PAGE FAULT] addr");
    lterm->write('\n');

    switch(basicError)
    {
        //supervisor page fault
        case(0b000)://supervisor tried to read non present page
            printERROR("[PAGE FAULT] supervisor read non present\n");
            break;
        case(0b001)://supervisor tried to read page and caused protection fault
            printERROR("[PAGE FAULT] supervisor read GPF\n");
            break;
        case(0b010)://supervisor tried to write to non-present page
            printERROR("[PAGE FAULT] supervisor write non present\n");
            break;
        case(0b011)://supervisor tried to write page and caused protection fault
            printERROR("[PAGE FAULT] supervisor write GPF\n");
            break;

        //user software page fault
        case(0b100)://user software tried to read non present page
            break;
        case(0b101)://user software tried to read page and caused protection fault
            break;
        case(0b110)://user software tried to write to non-present page
            break;
        case(0b111)://user software tried to write page and caused protection fault
            break;
    }

    if(reservedWrite)
        printERROR("[PAGE FAULT] reseved field not 0\n");

    if(instructionFetch)
        printERROR("[PAGE FAULT] instruction fetch (no-execute)\n");

    if(MPKViolation)
        printERROR("[PAGE FAULT] memory protection key violation\n");
    
    if(ShadowStackAccess)
        printERROR("[PAGE FAULT] Shadow Stack Access\n");

    sysfuckoff();
}
