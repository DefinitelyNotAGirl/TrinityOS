/**
 * Created Date: Wednesday April 26th 2023
 * Author: DefinitelyNotAGirl@github
 * -----
 * Last Modified: Wednesday April 26th 2023 8:22:13 am
 * Modified By: DefinitelyNotAGirl@github (definitelynotagirl115169@gmail.com)
 * -----
 * Copyright (c) 2023 DefinitelyNotAGirl@github
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

#include "../headers/MALLOC.h"
#include <macros>

static uint64_t malloc_page(void* vaddr,)
{
    void* pageAddr = getFreePageAddr(0);
    return 0;
}

extern "C" void* malloc(uint64_t size)
{
    //determine number of pages
    uint64_t pages = 0;
    while(size >= PAGE_SIZE){pages++;size -= PAGE_SIZE;}
    if(size > 0)pages++;

    //determine base vaddr
    void* baseVaddr = 0x0000000000000000;
    void* vaddr = baseVaddr;

    for(uint64_t I = 0;I<pages;I++)
    {
        malloc_page(vaddr);
        vaddr+=PAGE_SIZE;
    }

    return baseVaddr;
}
