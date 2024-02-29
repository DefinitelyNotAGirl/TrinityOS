/**
 * Created Date: Monday November 14th 2022
 * Author: DefinitelyNotAGirl@github
 * -----
 * Last Modified: Monday November 14th 2022 2:10:20 am
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

#ifndef TIME_DEFAULT_FORMAT_SIZE
    #define TIME_DEFAULT_FORMAT_SIZE 20// yyyy mm dd hh:ii:ss + null
#endif

namespace time
{
    char globalTimeStr[TIME_DEFAULT_FORMAT_SIZE] = "   0/ 0/ 0  0: 0: 0";
    const char* INVALIDTIME = "INVALID TIME FORMAT";

    enum class format
    {
        DEFAULT,INVALID,yyyy_mm_dd_hh_ii_ss
    };

    //i am very much aware that this struct is omega scuffed
    //usage:
    //timestamp A;
    //timestamp B = timestamp(0);
    //(uint64_t)A == (uint64_t)B (checks for equal)
    //(uint64_t)A = 0x0F00; (sets minutes to 15(0x0F) and seconds to 0(0x00))
    //A.hour = 24 (sets hour to 24)
    //A.second = 8 (sets second to 8)
    //btw yes, i feel like i just outsmarted everyone in the history of computer sience LMFAO
    struct timestamp
    {
        operator uint64_t(void);//uint64_t conversion
        timestamp(uint64_t ts);
        timestamp();
        //64 bits
        uint8_t  second   = 0x00   ;//could be compressed to 6 bits
        uint8_t  minute   = 0x00   ;//could be compressed to 6 bits
        uint8_t  hour     = 0x00   ;//could be compressed to 5 bits
        uint8_t  day      = 0x00   ;//could be compressed to 5 bits
        uint8_t  month    = 0x00   ;//could be compressed to 4 bits
        uint16_t yearLOW  = 0x0000 ;//low 16 bits of year (max year: 65 536)
        uint8_t  yearHIGH = 0x00   ;//high 8 bits of year (max year: 16 777 216)
        //wasted bits: 14
        //if we were to use those 14 bits we could represent years up to 38 bits (or use 32 bits and not have to do the weird year year_ shennanigans)
    }_pack;

    uint32_t year   = 0x00000000;
    uint8_t  month  = 0x00;
    uint8_t  day    = 0x00;
    uint8_t  hour   = 0x00;
    uint8_t  minute = 0x00;
    uint8_t  second = 0x00;

    //year is actually a 24 bit value (high 8 bits are ignored)
    //usage:
    //timestamp ts = (timestamp)createTimeStamp(...);
    timestamp createTimeStamp(uint32_t year,uint8_t month,uint8_t day,uint8_t hour,uint8_t minute,uint8_t second);

    //usage:
    //timestamp ts = (timestamp)getTimeStamp();
    uint64_t getTimeStamp();

    void writeTime(char* dst,format tf);
    void writeTime(char* dst,format tf,timestamp ts);
    void writeTime(ostream& dst,format tf);
    void writeTime(ostream& dst,format tf,timestamp ts);

    void init();
}