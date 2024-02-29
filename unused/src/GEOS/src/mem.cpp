/**
 * Created Date: Wednesday October 26th 2022
 * Author: DefinitelyNotAGirl@github
 * -----
 * Last Modified: Wednesday October 26th 2022 9:56:43 pm
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

template<typename T>
void memcpyT(void* src,void* dst,u64 len)
{
    for(u64 I = 0;I<len*sizeof(T);I+=sizeof(T))
        ((T*)dst)[I] = ((T*)src)[I];
}

template<typename T>
void memzeroT(void* target,u64 len)
{
    for(u64 I = 0;I<len*sizeof(T);I+=sizeof(T))
        ((T*)target)[I] = 0x00;
}

template<typename T>
void memmoveT(void* src, void* dst, u64 len)
{
    memcpyT<T>(src,dst,len);
    memzeroT<T>(src,len);
}

void memcpy(void* src, void* dst, u64 bytes){return memcpyT<char>(src,dst,bytes);}
void memzero(void* target,u64 bytes){return memzeroT<char>(target,bytes);}
void memmove(void* src, void* dst, u64 bytes)
{
    memcpy(src,dst,bytes);
    memzero(src,bytes);
}

template<typename T>
void memset(T* start,uint64_t len,T value)
{
    for(uint64_t I = 0;I<len;I++)
        start[I] = value;
}