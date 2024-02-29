/**
 * Created Date: Saturday November 12th 2022
 * Author: DefinitelyNotAGirl@github
 * -----
 * Last Modified: Saturday November 12th 2022 5:25:08 pm
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

extern "C" uint64_t getRAX();
extern "C" uint64_t getRBX();
extern "C" uint64_t getRCX();
extern "C" uint64_t getRDX();
extern "C" uint64_t getRDI();
extern "C" uint64_t getRSI();
extern "C" uint64_t getRBP();
extern "C" uint64_t getRSP();
extern "C" uint32_t getEAX();
extern "C" uint32_t getEBX();
extern "C" uint32_t getECX();
extern "C" uint32_t getEDX();
extern "C" uint32_t getEDI();
extern "C" uint32_t getESI();
extern "C" uint32_t getEBP();
extern "C" uint32_t getESP();
extern "C" uint64_t getR8();
extern "C" uint64_t getR9();
extern "C" uint64_t getR10();
extern "C" uint64_t getR11();
extern "C" uint64_t getR12();
extern "C" uint64_t getR13();
extern "C" uint64_t getR14();
extern "C" uint64_t getR15();

extern "C" uint64_t getcr0();
extern "C" uint64_t getcr2();
extern "C" uint64_t getcr3();
extern "C" uint64_t getcr4();

void detectMemory();
