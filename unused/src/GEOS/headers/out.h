/**
 * Created Date: Thursday November 17th 2022
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

char endl;

class ostream
{
public:
    ostream();

    void(*putchar)(char c);

    void out(HEX64 i);
    void out(HEX32 i);
    void out(HEX16 i);
    void out(HEX8  i);

    void out(uint64_t i);
    void out(uint32_t i);
    void out(uint16_t i);
    void out(uint8_t  i);

    void out(int64_t i);
    void out(int32_t i);
    void out(int16_t i);
    void out(int8_t  i);

    void out(      char* str);
    void out(const char* str);
    void out(      char  c  );

    void out(bool b);
    void out(time::timestamp ts);

    template<typename T, int size>
    void out(StaticRingBuffer<T,size>);
}_pack;

ostream operator<<(ostream ko,const char * arg);
ostream operator<<(ostream ko,      char * arg);
ostream operator<<(ostream ko,      char   arg);

ostream operator<<(ostream ko, uint64_t arg);
ostream operator<<(ostream ko, uint32_t arg);
ostream operator<<(ostream ko, uint16_t arg);
ostream operator<<(ostream ko, uint8_t  arg);

ostream operator<<(ostream ko, BYTES arg);

ostream operator<<(ostream ko, HEX64 arg);
ostream operator<<(ostream ko, HEX32 arg);
ostream operator<<(ostream ko, HEX16 arg);
ostream operator<<(ostream ko, HEX8  arg);

ostream operator<<(ostream ko, int64_t arg);
ostream operator<<(ostream ko, int32_t arg);
ostream operator<<(ostream ko, int16_t arg);
ostream operator<<(ostream ko, int8_t  arg);

ostream operator<<(ostream ko, bool             arg);
ostream operator<<(ostream ko, time ::timestamp arg);

ostream operator<<(ostream,mmap_entry&);

template<typename T,int size>
ostream operator<<(ostream,StaticRingBuffer<T,size>);