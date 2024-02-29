/**
 * Created Date: Friday December 2nd 2022
 * Author: DefinitelyNotAGirl@github
 * -----
 * Last Modified: Friday December 2nd 2022 10:49:17 am
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
#include "../code32.c"

#define AT_ADDR(addr,type) ((type*)addr)[0]
#include "memory.h"
void moveMMAP()
{
    char* RAM = "reading memory map\n";
    uint32_t* ancientMap = (uint32_t*)0x7C00;
    uint32_t* mapSize = AT_ADDR(0xFFFB,uint32_t);
    printStr("map size: ");
    printuint(mapSize);
    printChar('\n');
    uint32_t tSize = 0;
    for(uint32_t I = 0;I<mapSize;I++)
    {
        mmap_entries[I].baseLOW  = ancientMap[0];
        mmap_entries[I].baseHIGH = ancientMap[1];

        mmap_entries[I].lengthLOW  = ancientMap[2];
        mmap_entries[I].lengthHIGH = ancientMap[3];

        mmap_entries[I].type = ancientMap[4];
        mmap_entries[I].ext_attr = ancientMap[5];

        printStr(" | ");
        printuint(I);
        printStr(" | ");
        printuint(ancientMap[0]);
        printStr(" | ");
        printuint(ancientMap[2]);
        printStr(" | ");
        printuint(ancientMap[4]);
        printStr(" | ");
        printuint(ancientMap[5]);
        printStr(" |\n");

        tSize += ancientMap[2];
        ancientMap+=24;//next entry
    }

    printStr("total mem size: ");
    printuint(tSize);
    printChar('\n');
}