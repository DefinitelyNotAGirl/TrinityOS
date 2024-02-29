/**
 * Created Date: Wednesday November 9th 2022
 * Author: DefinitelyNotAGirl@github
 * -----
 * Last Modified: Wednesday November 9th 2022 2:56:57 am
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

template<typename intType>
partInt<intType>::partInt(uint32_t parts,uint32_t* partDesc,u8* data)
    :parts(parts),partDesc(partDesc),data(data){}

template<typename intType>
void partInt<intType>::set(intType value)
{
    uint32_t bits = sizeof(value)*8;
    uint32_t dataOffset = 0;
    uint32_t cDataLen = 0;
    uint32_t dataEnd = 0;
    u8 part = 0;

    PARTINT_nextPart: ;
        cDataLen = this->partDesc[part*2+1];
        dataOffset = this->partDesc[part*2];
        dataEnd = dataOffset+cDataLen;
        _return;

    PARTINT_SET_LOOP: ;
    for(uint32_t bit = 0;bit<bits;bit++)
    {
        if(dataOffset=dataEnd)
        {
            part++;
            call(PARTINT_nextPart);
        }
        setBit(this->data,dataOffset,getBit((u8*)&value,bit));
        dataOffset++;
    }
}

template<typename intType>
partInt<intType>::operator intType(void)
{
    intType temp;
    for(uint32_t I = 0;I<this->parts;I++)
    {
        uint32_t offset = this->partDesc[I*2];
        uint32_t len = this->partDesc[I*2+1];
        for(uint32_t II = offset;II<offset+len;II++)
            setBit((u8*)&temp,II-offset,getBit(this->data,II));
    }
    return temp;
}