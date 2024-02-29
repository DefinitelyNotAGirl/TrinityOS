/**
 * Author: DefinitelyNotAGirl@github
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

#include <stdint>

#define PAGE_SIZE 0x200000

#define PROC_ID_MAPEND  0x0000000000000000
#define PROC_ID_NONE    0x0000000000000001
#define PROC_ID_FIRM    0x0000000000000002
#define PROC_ID_MMIO    0x0000000000000003
#define PROC_ID_KERNEL  0x0000000000000004
#define PROC_ID_GSHARE  0x0000000000000005
#define PROC_ID_DAMAGED 0x0000000000000006

#define MEM_STATUS_OK 0x00000000000000
#define MEM_STATUS_BAD 0x0000000000000001
