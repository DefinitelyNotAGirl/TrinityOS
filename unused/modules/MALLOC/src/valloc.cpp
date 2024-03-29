/**
 * Created Date: Wednesday March 22nd 2023
 * Author: DefinitelyNotAGirl@github
 * -----
 * Last Modified: Tuesday April 25th 2023 10:46:08 am
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
#include <stdint>
#include <litop>
#include <misc>

#include "../headers/MALLOC.h"

extern "C" void allocPage(malloc_type type,malloc_priv priv,uint64_t vaddr,uint64_t procID)
{
    uint64_t physAddr = (priv == malloc_priv::kernel) ? getFreePageAddr(0) : getFreePageAddr(M_BASE_KERNEL_PAGES);
    
}

void tallocPage(
        uint8_t readwrite, 
        uint8_t supervisoronly,
        uint8_t pagewritetrough,
        uint8_t pagecachedisable,
        uint8_t global,
        uint8_t executeable)
{
}