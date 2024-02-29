/*
 * Created Date: Friday February 9th 2024
 * Author: Lilith
 * -----
 * Last Modified: Friday February 9th 2024 4:10:06 pm
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

#include "stdint.hxx"
#include "PAGING.hxx"

enum class TrinityProcessMode : uint32_t
{
    INVALID,
    Kernel,
    Driver,
    User,
};

enum class TrinitySystemInterfaceMode : uint32_t
{
    INVALID,
    TRINITY,
    Windows,
    MacOSX,
    Linux,
};

struct PROCESS_INFO
{
    /* 0x000000 */PT_512GiB PageTables;
    /* 0x202010 */uint64_t VirtualAddressLimit;
    /* 0x202000 */uint64_t AppID;
    /* 0x202008 */uint64_t ProccessID;
    /* 0x202010 */uint64_t MemoryLimit;
    /* 0x202018 */uint64_t MemoryUsage;
    /* 0x202020 */TrinityProcessMode ProcessMode;
    /* 0x202028 */TrinitySystemInterfaceMode SystemInterface;
};
