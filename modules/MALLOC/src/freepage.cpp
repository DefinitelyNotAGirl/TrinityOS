/**
 * Created Date: Wednesday May 24th 2023
 * Author: DefinitelyNotAGirl@github
 * -----
 * Last Modified: Thursday May 25th 2023 2:27:13 am
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
#include <MALLOC>
#include <main>
#include <stdint>

u64 getFreeVirtPageAddr()
{
    return 0;//invalid addr
}

u64 getFreePageAddr(u64 skipPages)
{
    u64* mmap = PHYS_MMAP_BASE;
    while(mmap[0] != PROC_ID_MAPEND)
    {
        if(mmap[0] == PROC_ID_NONE)
            return (mmap-PHYS_MMAP_BASE)*PAGE_SIZE;
        mmap+=8;
    }
    return 0;//invalid addr
}
