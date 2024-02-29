/**
 * Created Date: Sunday January 8th 2023
 * Author: DefinitelyNotAGirl@github
 * -----
 * Last Modified: Sunday January 8th 2023 9:08:12 am
 * Modified By: DefinitelyNotAGirl@github (definitelynotagirl115199@gmail.com)
 * -----
 * Copyright (c) 2023 DefinitelyNotAGirl@github
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

struct PACKED __ACPITABLES__
{
    ptr64 MADT;
    ptr64 BERT;
    ptr64 CPEP;
    ptr64 DSDT;
    ptr64 ECDT;
    ptr64 EINJ;
    ptr64 ERST;
    ptr64 FADT;
    ptr64 FACS;
    ptr64 HEST;
    ptr64 MSCT;
    ptr64 MPST;
    ptr64 PMTT;
    ptr64 PSDT;
    ptr64 RASF;
    ptr64 RSDT;
    ptr64 SBST;
    ptr64 SLIT;
    ptr64 SRAT;
    ptr64 SSDT;
    ptr64 XSDT;
    ptr64 MCFG;
};

struct PACKED __bootInfo__
{
    //Memory Map
    uint64_t mmap_base;
    uint64_t mmap_size;

    //stack
    uint64_t stack_base;
    uint64_t stack_size;

    //misc
    uint64_t VirtualMemoryMAX;
    uint8_t ACPI_REVISION;
    __ACPITABLES__ ACPIT;
};

