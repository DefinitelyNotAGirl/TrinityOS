/*
 * Created Date: Thursday February 8th 2024
 * Author: Lilith
 * -----
 * Last Modified: Thursday February 8th 2024 9:29:01 pm
 * Modified By: Lilith (definitelynotagirl115169@gmail.com)
 * -----
 * Copyright (c) 2024 Lilith
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

#include <MEMMAP.hxx>
#include <APP_INFO.hxx>

#define RandomPhysicalAddress UINT64_T_MAX
#define RandomVirtualAddress UINT64_T_MAX

enum class TrinitySetPageReturn : uint64_t 
{
    OK,
    OutOfPhysicalMemory,
    OutOfVirtualMemory,
    VirtualOutOfBounds,
    InvalidMode,
};

enum class TrinityPageType : uint64_t
{
    NotPresent,
    Code,
    ReadWriteData,
    ReadOnlyData,
    MemoryMappedIO,
};

struct PT_512GiB
{
    uint64_t PML4 [0x200];  //PML4
    uint64_t PML3 [0x200];  //PDP
    uint64_t PAGES[0x40000];//PD
};//size: 0x202000 bytes

struct PROCESS_INFO;
