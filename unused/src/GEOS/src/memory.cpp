/**
 * Created Date: Monday November 14th 2022
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
#include "../master.h"

void detectMemoryUEFI()
{
}

void detectMemory()
{
    out << "detecting memory..." << endl;
    return detectMemoryUEFI();

    mmap_entry mmap[128];//~3KB
    uint64_t highestHole = 0;
    uint64_t totalMem    = 0;

    uint64_t* mmap_ent_ptr = (uint64_t*)&bootboot.mmap;
    uint64_t* mmap_ent_size = mmap_ent_ptr+0x8;
    uint8_t index = 0;
    uint64_t mmapMax = (uint64_t)(&bootboot.mmap+bootboot.size);

    while((uint64_t)mmap_ent_size<mmapMax)
    {
        mmap[index].base = *mmap_ent_ptr;
        mmap[index].size = *mmap_ent_size&0xFFFFFFFFFFFFFFF0;
        mmap[index++].type = *mmap_ent_size&0xF;

        mmap_ent_ptr+=0x10;
        mmap_ent_size+=0x10;
    }

    for(uint8_t I = 0;I<index;I++)
    {
        out << mmap[I];
        if(mmap[I].type == 1)
            totalMem+=mmap[I].size;
    }

    computer.memorySize = totalMem;
}