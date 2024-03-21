/*
 * Created Date: Wednesday February 7th 2024
 * Author: Lilith
 * -----
 * Last Modified: Thursday February 8th 2024 1:54:20 pm
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

#define TRINITY_PAGE_SIZE 0x200000

enum TRINITY_MEMORY_TYPE : uint64_t {
    TRINITY_MEMORY_TYPE_MIN = 0,
    TRINITY_MEMORY_TYPE_MMIO,// memory on MMIO pages outside of MMIO data structures is to be treated as TRINITY_MEMORY_TYPE_UNKNOWN
    TRINITY_MEMORY_TYPE_PRESERVE,
    TRINITY_MEMORY_TYPE_RAM,
    TRINITY_MEMORY_TYPE_BORKED,
    TRINITY_MEMORY_TYPE_ACPI_RECLAIM,
    TRINITY_MEMORY_TYPE_UNACCEPTED,
    TRINITY_MEMORY_TYPE_UNKNOWN,
    TRINITY_MEMORY_TYPE_RAM_USED,
    TRINITY_MEMORY_TYPE_MAX
};

struct TRINITY_MEMORY_VITAL
{
    uint64_t RAM_SIZE;
    uint64_t NeedToMoveInit;
    uint64_t PAGETABLE_PHYS;
    uint64_t INIT_CODE_PHYS;
    uint64_t INIT_RW_PHYS;
    uint64_t INIT_RO_PHYS;
    uint64_t INIT_BSS_PHYS;
    uint64_t STACK_PHYS;
    uint64_t MEMMAP_PHYS;
    uint64_t PAGETABLE_PHYS_2;
    uint64_t MEMMAP_PHYS_2;
    uint64_t PCIE_PHYS;
	uint64_t RSDT_PHYS;
};

struct TRINITY_MEMORY_MAP_ENTRY
{
    TRINITY_MEMORY_TYPE Type;
    uint64_t MemoryControllerAddress;
    uint64_t Attributes;//currently unused
};
