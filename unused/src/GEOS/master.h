/**
 * Created Date: Sunday November 6th 2022
 * Author: DefinitelyNotAGirl@github
 * -----
 * Last Modified: Saturday November 19th 2022 8:05:57 pm
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

//###############################################//
//###############################################//
//################### headers ###################//
//###############################################//
//###############################################//

void sysfreeze();

//define ATTRIBUTES
#define PACKED __attribute__((packed))
#define ENTRY64 __attribute__((section(".entry64Code")))
#define ENTRY64_DATA __attribute__((section(".entry64Data")))
#define NORETURN __attribute__((noreturn))

//get basics
#include "headers/pre.h"
#include "headers/std.h"
#include "headers/fixedInt.h"
#include "headers/GEOS_META.h"
#include "headers/macros.h"
#include "headers/miscFunctions.h"
#include "headers/miscClasses.h"
#include "headers/hardware/misc.h"
#include "headers/litop.h"
#include "headers/memory.h"

//data structures
#include "headers/ringbuff.h"
#include "headers/bootInfo.h"
#include "headers/lowLevelStructs.h"

//time
#include "headers/time.h"
using time::timestamp;

//output
#include "headers/out.h"

//interrupts
#include "headers/interrupts/ISR.h"
#include "headers/interrupts/APIC.h"

//exceptions
#include "headers/except.h"
//bootboot
#include "../bootboot.h"
BOOTBOOT bootboot;
//#include "../kernel.cpp"

//stdlibc++
#include <itoa.cpp>

//hardware
#include "headers/hardware/CPU.h"
#include "headers/hardware/GPU.h"
#include "headers/hardware/drive.h"
#include "headers/hardware/computer.h"

//data manipulation
#include "headers/bits.h"

//display
#include "headers/video.hpp"
#include "headers/terminal.h"

//misc headers
#include "headers/load.h"
#include "headers/ERROR.h"
#include "headers/partInt.h"
#include "headers/mem.h"
#include "headers/paging.h"

//include global variables
#include "headers/global.h"

//######################################################//
//######################################################//
//################### implementation ###################//
//######################################################//
//######################################################//

//entry64
#include "src/entry64.cpp"

//main source
#include "main.cpp"
#include "src/bootstrap.cpp"
#include "src/load.cpp"
#include "src/paging.cpp"
#include "src/controlRegs.cpp"

//data structures
#include "src/ringbuff.cpp"

//output
#include "src/out.cpp"

//hardware
#include "src/computer.cpp"

//interrupts
#include "src/interrupts/defaultInterruptHandler.cpp"
#include "src/interrupts/GPFault.cpp"
#include "src/interrupts/IDT.cpp"
#include "src/interrupts/syscall.cpp"
#include "src/interrupts/APIC.cpp"
#include "src/interrupts/doubleFaulthandler.cpp"
#include "src/interrupts/pageFault.cpp"
#include "src/interrupts/miscHandlers.cpp"
#include "src/geoscall.cpp"

//time
#include "src/time.cpp"

//data manipulation
#include "src/bits.cpp"
#include "src/mem.cpp"

//display
#include "src/sysout.cpp"
#include "src/terminal.cpp"

//misc source
#include "src/util.cpp"
#include "src/GDT.cpp"
#include "src/partInt.cpp"
#include "src/memory.cpp"
#include "src/litop.cpp"
#include "src/misc.cpp"
