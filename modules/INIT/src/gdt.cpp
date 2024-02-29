/**
 * Created Date: Saturday February 10th 2024
 * Author: Lilith
 * -----
 * Last Modified: Saturday February 10th 2024 12:07:01 pm
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

#include <DESCRIPTOR_TABLES.hxx>
#include <bits.hxx>

extern "C" void updateGDT();
void setupGDT()
{
    //assume 0x3000000 to have been set up as a data page prior to this function being called
    //establish gdt on 2MiB boundry at 0x3000000
    GDTEntry* gdt = (GDTEntry*)0x3000000;
    GDTPseudo* pseudo = (GDTPseudo*)0x3011000;
    uint16_t size = 0;
    //
    //NULL descriptor
    //
    {
        size+=8;
        *((uint64_t*)(&gdt[0])) = 0;
    }
    //
    //CPL 0 Code Descriptor +0x08
    //
    {
        size+=8;
        *((uint64_t*)(&gdt[1])) = 0;
        //flags
        gdt[1].Flags = 0x20;//Long mode
        //Attributes
        gdt[1].Attributes = 0x9C;// cpl = 0,user, conforming, execute
    }
    //
    //CPL 0 Data Descriptor +0x10
    //
    {
        size+=8;
        *((uint64_t*)(&gdt[2])) = 0;
        //flags
        gdt[2].Flags = 0x10;//Long mode
        //Attributes
        gdt[2].Attributes = 0x92;// cpl = 0, user, data
    }
    //
    //write pseudo descriptor
    //
    pseudo->address = (uint64_t)gdt;
    pseudo->limit = size;
    updateGDT();
}
