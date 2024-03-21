/**
Created Date: Thursday March 7th 2024
Author: Lilith (definitelynotagirl115169@gmail.com)
-----
Last Modified: Thursday March 7th 2024 10:35:19 pm
Modified By: Lilith (definitelynotagirl115169@gmail.com)
-----
Copyright (c) 2024 Lilith Nitschke-Höfer (lilithnitschkehoefer@gmail.com)

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without
restriction, including without limitation the rights to use, copy,
modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
*/
#pragma once

#define MEM_ADDR_VIRT_PCIE			0x0200000 //.  2MiB
#define MEM_ADDR_VIRT_PHYS_MEMMAP 	0x1800000 //.  4MiB
#define MEM_ADDR_VIRT_PROC_KERNEL 	0x2400000 //.  4MiB
#define MEM_ADDR_VIRT_DESC_TABLES 	0x3000000 //.  2MiB
#define MEM_ADDR_DISK_READ_INIT 	0x3200000 //. 20MiB
#define MEM_ADDR_VIRT_ACPI_TABLES 	0x4E00000 //.  2MiB
#define MEM_ADDR_VIRT_ACPI_DATA 	0x5000000 //. 20MiB
#define MEM_ADDR_CPU_INFO			0x6400000 //.  2MiB
#define MEM_ADDR_INTERRUPT_DATA		0x6600000 //.  2MiB
#define MEM_ADDR_BOTTOM				0x7000000 //.  2MiB - this page holds the bottom of physical memory (0x000000-0x200000)
