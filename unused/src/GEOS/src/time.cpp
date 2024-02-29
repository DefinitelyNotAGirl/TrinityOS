/**
 * Created Date: Monday November 14th 2022
 * Author: DefinitelyNotAGirl@github
 * -----
 * Last Modified: Monday November 14th 2022 2:28:47 am
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

namespace time
{
    timestamp::operator uint64_t(void){return ((uint64_t*)this->second)[0];}
    timestamp::timestamp(uint64_t ts){((uint64_t*)this->second)[0] = ts;}
    timestamp::timestamp(){}

    timestamp createTimeStamp(uint32_t year,uint8_t month,uint8_t day,uint8_t hour,uint8_t minute,uint8_t second)
    {
        timestamp ts;
        uint16_t yearLOW = year;
        uint8_t yearHIGH = ((uint8_t*)&year)[2];
        
        ts.yearLOW = yearLOW;
        ts.yearHIGH = yearHIGH;

        ts.month = month;
        ts.day = day;
        ts.hour = hour;
        ts.minute = minute;
        ts.second = second;

        return ts;
    }

    uint64_t getTimeStamp(){return createTimeStamp(year,month,day,hour,minute,second);}

    void writeTime(ostream& dst,format tf)
    {
        switch(tf)
        {
            case(format::yyyy_mm_dd_hh_ii_ss):
            {   
                dst << year << '/' << month << '/' << day << ' ' <<  hour << ':' << minute << ':' << second;
                break;
            }
            default:
                dst << INVALIDTIME;
        }
    }

    void writeTime(char* dst,format tf,timestamp ts)
    {
        switch(tf)
        {
            case(format::yyyy_mm_dd_hh_ii_ss):
            {
                char ITSOUT[INTTS_SIZE];

                INTTS((uint32_t)ts.yearLOW,10,ITSOUT);
                memcpy(ITSOUT,dst,4);

                INTTS((uint32_t)ts.month,10,ITSOUT);
                memcpy(ITSOUT,dst+5,2);

                INTTS((uint32_t)ts.day,10,ITSOUT);
                memcpy(ITSOUT,dst+8,2);

                INTTS((uint32_t)ts.hour,10,ITSOUT);
                memcpy(ITSOUT,dst+11,2);

                INTTS((uint32_t)ts.minute,10,ITSOUT);
                memcpy(ITSOUT,dst+14,2);

                INTTS((uint32_t)ts.second,10,ITSOUT);
                memcpy(ITSOUT,dst+17,2);
                break;
            }
            default:
                dst = (char*)INVALIDTIME;
        }
    }

    void writeTime(char* dst,format tf)
    {
        switch(tf)
        {
            case(format::yyyy_mm_dd_hh_ii_ss):
            {
                char ITSOUT[INTTS_SIZE];

                INTTS((uint32_t)year,10,ITSOUT);
                memcpy(ITSOUT,dst,4);

                INTTS((uint32_t)month,10,ITSOUT);
                memcpy(ITSOUT,dst+5,2);

                INTTS((uint32_t)day,10,ITSOUT);
                memcpy(ITSOUT,dst+8,2);

                INTTS((uint32_t)hour,10,ITSOUT);
                memcpy(ITSOUT,dst+11,2);

                INTTS((uint32_t)minute,10,ITSOUT);
                memcpy(ITSOUT,dst+14,2);

                INTTS((uint32_t)second,10,ITSOUT);
                memcpy(ITSOUT,dst+17,2);
                break;
            }
            default:
                dst = (char*)INVALIDTIME;
        }
    }

    void writeTime(ostream& dst,format tf,timestamp ts)
    {
        switch(tf)
        {
            case(format::yyyy_mm_dd_hh_ii_ss):
            {
                dst << get24Bits(&ts.yearLOW) << '/' << ts.month << '/' << ts.day << ' ' <<  ts.hour << ':' << ts.minute << ':' << ts.second;
                break;
            }
            default:
                dst << INVALIDTIME;
        }
    }

    void init()
    {
        out << "setting initial time..." << endl;
        uint64_t BCD = ((uint64_t*)&bootboot.datetime)[0];
        char str[14];
        str[14] = 0x00;
        for(uint8_t I = 0;I<15;I+=2)
        {
            uint8_t bcdDigit = 0;

            setBit(&bcdDigit,0,getBit((u8*)&BCD,0));
            setBit(&bcdDigit,1,getBit((u8*)&BCD,1));
            setBit(&bcdDigit,2,getBit((u8*)&BCD,2));
            setBit(&bcdDigit,3,getBit((u8*)&BCD,3));

            str[I+1] = DIGITS[bcdDigit];
            BCD >>= 4;

            //second run
            bcdDigit = 0;

            setBit(&bcdDigit,0,getBit((u8*)&BCD,0));
            setBit(&bcdDigit,1,getBit((u8*)&BCD,1));
            setBit(&bcdDigit,2,getBit((u8*)&BCD,2));
            setBit(&bcdDigit,3,getBit((u8*)&BCD,3));

            str[I] = DIGITS[bcdDigit];
            BCD >>= 4;
        }
        str[14] = 0x00;

        time::year   = 2000+strToUInt(str+0  ,3);
        time::month  =      strToUInt(str+3  ,2);
        time::day    =      strToUInt(str+5  ,2);
        time::hour   =      strToUInt(str+7  ,2);
        time::minute =      strToUInt(str+9  ,2);
        time::second =      strToUInt(str+11 ,2);

        out << endl;
    }
}