/**
 * Created Date: Sunday November 6th 2022
 * Author: DefinitelyNotAGirl@github
 * -----
 * Last Modified: Sunday November 6th 2022 10:40:32 am
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
#include "../../master.h"

enum class CPU_VENDOR
{
    INVALID,AMD,INTEL,QEMU,KVM,VMWARE,VirtualBox
};

const char* CPU_VENDOR_STRING(CPU_VENDOR vendor);
CPU_VENDOR getVendor(uint32_t EBX,uint32_t ECX,uint32_t EDX);

class CPUID
{
public:
    bool hasLocalAPIC = false;

    uint8_t familiy;
    uint8_t model;

    CPU_VENDOR vendor = CPU_VENDOR::INVALID;

    void update();
};

class CPU
{
public:
    CPUID cpuid;

    uint64_t coreCount;
    uint64_t clockSpeed; // clockspeed in hz
};