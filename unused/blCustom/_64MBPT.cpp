/**
 * Created Date: Tuesday November 15th 2022
 * Author: DefinitelyNotAGirl@github
 * -----
 * Last Modified: Tuesday November 15th 2022 9:09:59 pm
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

#include <iostream>
#include <bitset>

#define KILOBYTE 1024
#define MEGABYTE 1000*KILOBYTE

void setBit(uint8_t* array,uint64_t bit,bool value)
{
    uint64_t n = bit/8;
    uint64_t k = bit-(8*n);
    array[n] ^= (-value ^ array[n]) & (1UL << k);
}

bool getBit(uint8_t* array,uint64_t bit)
{
    uint64_t n = bit/8;
    uint64_t k = bit-(8*n);
    return (array[n] & (1 << k)) >> k;
}

const char* TAB = "    ";
int main()
{
    uint32_t physAddr = 0;
    for(uint32_t I = 0;I<32;I++)
    {
        uint64_t entry = 0;

        for(uint64_t bit = 21;bit<52;bit++) 
            setBit((uint8_t*)&entry,bit,getBit((uint8_t*)&physAddr,bit-21));

        std::bitset<64> bits(entry);
        std::cout << "HARD_PDE" << I << ": " << std::endl;
        std::cout << TAB << "dq 0b" << bits << std::endl;

        physAddr+=2*MEGABYTE; 
    }
}