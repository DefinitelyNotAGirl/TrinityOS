/**
 * Created Date: Saturday November 12th 2022
 * Author: DefinitelyNotAGirl@github
 * -----
 * Last Modified: Saturday November 12th 2022 5:49:34 pm
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

namespace controlRegisters
{
    namespace cr0
    {
        void write()
        {
            if(!PG)//in long mode cr0 controls long mode
                return printERROR("cannot clear cr0.PG!");
        }

        void read()
        {
            uint64_t reg = getcr0();
            u8* data = (u8*)&reg;

            PG = getBit(data,31);
        }
    }

    namespace cr3
    {
        void write(){}
        void read(){}
    }

    namespace cr4
    {
        void write()
        {
        }

        void read()
        {
            uint64_t reg = getcr4();
            u8* data = (u8*)&reg;

            PSE = getBit(data,4);
            PAE = getBit(data,5);
            PGE = getBit(data,7);//enables global pages
        }
    }

    namespace EFER
    {
        void write(){}
        void read(){}
    }

    void readAll()
    {
        cr0::read();
        cr3::read();
        cr4::read();
        EFER::read();
    }

    void writeAll()
    {
        cr0::write();
        cr3::write();
        cr4::write();
        EFER::write();
    }
}