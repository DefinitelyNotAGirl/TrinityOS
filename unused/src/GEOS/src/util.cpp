/**
 * Created Date: Sunday October 30th 2022
 * Author: DefinitelyNotAGirl@github
 * -----
 * Last Modified: Tuesday April 25th 2023 10:46:07 am
 * Modified By: DefinitelyNotAGirl@github (definitelynotagirl115169@gmail.com)
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

void INTTS(int64_t value,int base,char* result)
{
    char str[INTTS_SIZE] = {0x00};
    char* ret = std::itoa(value,str,base);

    memcpy(str,result,INTTS_SIZE);
}

bool strEqual(char* a,char* b);

uint64_t strlen(const char* str)
{
    uint64_t I = 0;
    while(str[I++]);
    return I;
}

void PTS(char* str,uint32_t addr)
{
    ((uint16_t*)str)[0] = 'x0';
    for(uint8_t I = 9;I>1;I--)
    {
        str[I] = HEXDIG[addr&0xF];
        addr>>=4;
    }
}

void PTS(char* str,uint16_t addr)
{
    ((uint16_t*)str)[0] = 'x0';
    for(uint8_t I = 5;I>1;I--)
    {
        str[I] = HEXDIG[addr&0xF];
        addr>>=4;
    }
}

void PTS(char* str,uint8_t addr)
{
    ((uint16_t*)str)[0] = 'x0';
    for(uint8_t I = 3;I>1;I--)
    {
        str[I] = HEXDIG[addr&0xF];
        addr>>=4;
    }
}

void PTS(char* str,uint64_t addr)
{
    ((uint16_t*)str)[0] = 'x0';
    for(uint8_t I = 17;I>1;I--)
    {
        str[I] = HEXDIG[addr&0xF];
        addr>>=4;
    }
}

uint64_t hexStrToUInt(char* str)
{
    uint64_t result = 0;
    uint8_t len = strlen(str)-1;
    uint8_t I;

    if(((uint16_t*)str)[0] == 'x0'/*not a typo*/)// if str[0] == 0 && str[1] == x
        I = 2;
    else
        I = 0;
    
    for(I=I;I<len;I++)
    {
        uint8_t c = str[I];
        if(c>0x60)
            c-=0x57;
        else if(c>0x40)
            c-=0x37;
        else
            c-=0x30;

        result <<= 4;
        result |= c;
    }
    return result;
}

uint64_t strToUInt(char* str,uint64_t len = 0)
{
    uint64_t result = 0;
    uint64_t I = len;
    if(I == 0)
        I = strlen(str);
    uint64_t mult = 1;
    for(I=I;I>0;I--)
    {
        result+=((str[I]-0x30)*mult);
        mult*=10;
    }
    return result;
}

uint32_t get24Bits(void* addr)
{
    uint32_t res = 0x00000000;
    uint8_t* dst = (uint8_t*)&res;
    uint8_t* src = (uint8_t*)addr;
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
    return res; 
}