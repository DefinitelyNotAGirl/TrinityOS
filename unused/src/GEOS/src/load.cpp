/**
 * Created Date: Wednesday October 26th 2022
 * Author: DefinitelyNotAGirl@github
 * -----
 * Last Modified: Wednesday October 26th 2022 9:37:59 pm
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
#include "../master.h"

void dumpIDT()
{
    printINFO("##### IDT dump #####\n");
    for(int entry = 0x80;entry<0x81;entry++)
    {
        u8* idtEbits = (u8*)(&IDT[entry]);

        //idt values
        uint64_t offset = 0;
        uint8_t selector = 0;
        uint8_t IST = 0;
        uint8_t gateType = 0;
        uint8_t privelegeLevel = 0;

        bool presentBit = 0;

        u8 offsetBit = 0;

        //offset bits 0-15 go into bits 0-15
        for(u8 I = 0;I<16;I++)
            setBit((u8*)&offset,I,getBit(idtEbits,offsetBit++));

        //offset bits 16-63 go into bits 48-95
        for(u8 I = 48;I<96;I++)
            setBit((u8*)&offset,I,getBit(idtEbits,offsetBit++));

        for(u8 I = 0;I<16;I++)
            setBit((u8*)&selector,I,getBit(idtEbits,I+16));

        //IST
        setBit(&IST,32,getBit(idtEbits,0));
        setBit(&IST,33,getBit(idtEbits,1));
        setBit(&IST,34,getBit(idtEbits,2));
        //gate type
        setBit(&gateType,0,getBit(idtEbits,40));
        setBit(&gateType,1,getBit(idtEbits,41));
        setBit(&gateType,2,getBit(idtEbits,42));
        setBit(&gateType,3,getBit(idtEbits,43));
        //cpu privilege level
        setBit(&privelegeLevel,0,getBit(idtEbits,46));
        setBit(&privelegeLevel,1,getBit(idtEbits,46));
        //present bit
        presentBit = getBit(idtEbits,47);

        //output data
        printINFO("##### entry: 0x"); 
        const char entry__[INTTS_SIZE] = {0x00};
        INTTS(entry,16,(char*)entry__);
        lterm->write(entry__);
        lterm->write(" #####\n");

        //pb
        if(presentBit)
            printINFO("present bit: true\n");
        else
            printINFO("present bit: false\n");
        
        //DPL
        printINFO("CPU privilege level: 0x");
        INTTS(privelegeLevel,16,(char*)entry__);
        lterm->write(entry__);
        lterm->write('\n');

        setR15(0x5888);

        //offset
        printINFO("offset: 0x");
        INTTS((uint32_t)offset,16,(char*)entry__);
        lterm->write(entry__);
        lterm->write('\n');

        setR15(0x4888);

        //selector
        printINFO("selector: 0x");
        INTTS(selector,16,(char*)entry__);
        lterm->write(entry__);
        lterm->write('\n');

        //IST
        printINFO("IST: 0x");
        INTTS(IST,16,(char*)entry__);
        lterm->write(entry__);
        lterm->write('\n');

        //gate Type
        printINFO("gate Type: 0x");
        INTTS(gateType,16,(char*)entry__);
        lterm->write(entry__);
        lterm->write('\n');

        setR15(0x8888);

    }
}

void setupGDT()
{
    out << "setting up GDT..." << endl;

    //gdtEntry64* GDT = getGDTaddr();
    //GDT[0].data[0] = 0;
    //GDT[1] = createGDTEntry64(createAccessByte64(0x00,0,1,0,1,0),createGDTFlags64(1));
    //GDT[2] = createGDTEntry64(createAccessByte64(0x00,0,1,0,1,0),createGDTFlags64(0));

    loadGDT();
}

void setupIDT()
{
    out << "setting up IDT..." << endl;

    //TODO: write interupt handlers
    //fetch IDT address
    IDT = (InterruptDescriptor64*)getIDTaddr();

    IDT[INTERRUPT_GPFAULT       ] = createIDTEntry64(& GPFaultHandler                        ,GATETYPE_INTERRUPT ,0x00,0x01,0x00,0x08);//General protection fault
    IDT[INTERRUPT_SYSCALL       ] = createIDTEntry64(& syscall                               ,GATETYPE_INTERRUPT ,0x03,0x01,0x00,0x08);//syscall interrupt
    IDT[INTERRUPT_DUMMY         ] = createIDTEntry64(& dummyInt                              ,GATETYPE_INTERRUPT ,0x03,0x01,0x00,0x08);//dummy interrupt
    IDT[INTERRUPT_INVALID       ] = createIDTEntry64(& invalidInterruptHandler               ,GATETYPE_INTERRUPT ,0x03,0x01,0x00,0x08);//invalid interrupt
    IDT[INTERRUPT_DOUBLEFAULT   ] = createIDTEntry64(& doubleFaultHandler                    ,GATETYPE_INTERRUPT ,0x00,0x01,0x00,0x08);//double fault
    IDT[INTERRUPT_PAGEFAULT     ] = createIDTEntry64(& pageFaultHandler                      ,GATETYPE_INTERRUPT ,0x00,0x01,0x00,0x08);//page fault
    IDT[INTERRUPT_INVALIDOPCODE ] = createIDTEntry64(& interrupts             ::invalidopcode,GATETYPE_INTERRUPT ,0x00,0x01,0x00,0x08);//invalid opcode

    //load IDT
    loadIDT();
}
