/**
 * Created Date: Wednesday November 9th 2022
 * Author: DefinitelyNotAGirl@github
 * -----
 * Last Modified: Wednesday November 9th 2022 2:42:14 am
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

//working integer types
#ifndef PARTINT_uMAX
    #define PARTINT_uMAX uint64_t
#endif
#ifndef PARTINT_iMAX
    #define PARTINT_iMAX int64_t
#endif
#ifndef PARTINT_u64
    #define PARTINT_u64 uint64_t
#endif
#ifndef PARTINT_i64
    #define PARTINT_i64 int64_t
#endif
#ifndef PARTINT_u32
    #define PARTINT_u32 uint32_t
#endif
#ifndef PARTINT_i32
    #define PARTINT_i32 int32_t
#endif
#ifndef PARTINT_u16
    #define PARTINT_u16 uint16_t
#endif
#ifndef PARTINT_i16
    #define PARTINT_i16 int16_t
#endif
#ifndef PARTINT_u8
    #define PARTINT_u8 uint8_t
#endif
#ifndef PARTINT_i8
    #define PARTINT_i8 int8_t
#endif

//max bit width
#ifndef PARTINT_MAXW
    #define PARTINT_MAXW 64
#endif

template<typename intType>
class partInt
{
public:
    uint32_t parts;
    uint32_t* partDesc;
    /*
        partDesc structure:

        [starting bit] [part length]
        PDi = PD+2i
    */
    byte* data;

    partInt(uint32_t parts,uint32_t* partDesc,byte* data);

    void set(intType value);

    operator intType(void);
};