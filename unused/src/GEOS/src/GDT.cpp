/**
 * Created Date: Saturday October 29th 2022
 * Author: DefinitelyNotAGirl@github
 * -----
 * Last Modified: Saturday October 29th 2022 1:10:05 pm
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

struct gdtEntry64
{
    uint64_t* data[1];
};

struct SystemGDTEntry64
{
    uint64_t* data[2];
};

u8 createGDTFlags64(bool is64BitCode)
{
    u8 ret = 0;
    setBit(&ret,1,is64BitCode);

    return ret;
}

u8 createAccessByte64(u8 DPL,bool DT,bool executable, bool DC, bool RW, bool AB)
{
    u8 ret = 0;
    
    setBit(&ret,0,AB);
    setBit(&ret,1,RW);
    setBit(&ret,2,DC);
    setBit(&ret,3,executable);
    setBit(&ret,4,DT);
    setBit(&ret,5,getBit(&DPL,0));
    setBit(&ret,6,getBit(&DPL,1));
    setBit(&ret,7,1);

    return ret;
}

SystemGDTEntry64 createSystemGDTEntry64(u8 accessByte,u8 flags,uint64_t base)
{
    SystemGDTEntry64 entry;
    //entry bits: 0-127

    //base (set to 0 since in 64 bit mode, this value is ignored)
        //bits 16-39
        for(int I = 16;I<40;I++)
            setBit((u8*)entry.data,I,getBit((u8*)&base,I-16));
        //bits 56-63
        for(int I = 56;I<64;I++)
            setBit((u8*)entry.data,I,getBit((u8*)&base,I-40));
        //bits 64-95
        for(int I = 64;I<96;I++)
            setBit((u8*)entry.data,I,getBit((u8*)&base,I-40));

    //limit (set to 0 since in 64 bit mode, this value is ignored)
        //bits 0-15
        for(int I = 0;I<16;I++)
            setBit((u8*)entry.data,I,0);
        //bits 48-51
        for(int I = 48;I<52;I++)
            setBit((u8*)entry.data,I,0);

    //access byte
    //bits 40-47
    for(int I = 40;I<48;I++)
        setBit((u8*)entry.data,I,getBit(&accessByte,I-40));

    //flags
    //bits 52-55
    for(int I = 52;I<56;I++)
        setBit((u8*)entry.data,I,getBit(&flags,I-52));
        
    return entry;
}

gdtEntry64 createGDTEntry64(u8 accessByte,u8 flags)
{
    gdtEntry64 entry;
    //entry bits: 0-63

    //base (set to 0 since in 64 bit mode, this value is ignored)
        //bits 16-39
        for(int I = 16;I<40;I++)
            setBit((u8*)entry.data,I,0);
        //bits 56-63
        for(int I = 56;I<64;I++)
            setBit((u8*)entry.data,I,0);

    //limit (set to 0 since in 64 bit mode, this value is ignored)
        //bits 0-15
        for(int I = 0;I<16;I++)
            setBit((u8*)entry.data,I,0);
        //bits 48-51
        for(int I = 48;I<52;I++)
            setBit((u8*)entry.data,I,0);

    //access byte
    //bits 40-47
    for(int I = 40;I<48;I++)
        setBit((u8*)entry.data,I,getBit(&accessByte,I-40));

    //flags
    //bits 52-55
    for(int I = 52;I<56;I++)
        setBit((u8*)entry.data,I,getBit(&flags,I-52));
        
    return entry;
}
