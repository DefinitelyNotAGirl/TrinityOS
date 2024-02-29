/**
 * Created Date: Thursday October 27th 2022
 * Author: DefinitelyNotAGirl@github
 * -----
 * Last Modified: Thursday October 27th 2022 9:15:49 am
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

#define INTERRUPT_SYSCALL       0x80
#define INTERRUPT_GPFAULT       0x0D
#define INTERRUPT_DUMMY         0xFF
#define INTERRUPT_INVALID       0xFE
#define INTERRUPT_INVALIDOPCODE 0x06
#define INTERRUPT_DOUBLEFAULT   0x08
#define INTERRUPT_PAGEFAULT     0x0E
#define INTERRUPT_GEOSCALL      0x81

#define INTERRUPT_ARGS

//declare handlers
INTERRUPT GPFaultHandler          (INTERRUPT_ARGS);
INTERRUPT syscall                 (INTERRUPT_ARGS);
INTERRUPT invalidInterruptHandler (INTERRUPT_ARGS);
INTERRUPT dummyInt                (INTERRUPT_ARGS);
INTERRUPT doubleFaultHandler      (INTERRUPT_ARGS);
INTERRUPT pageFaultHandler        (INTERRUPT_ARGS);
INTERRUPT geosCallHandler         (INTERRUPT_ARGS);
namespace interrupts
{
   INTERRUPT invalidopcode(INTERRUPT_ARGS);
}

extern "C" uint64_t interruptGetError();

//misc
struct InterruptDescriptor64 {
   uint64_t data[2];// bits 0-127
} _pack;

#define GATETYPE_INTERRUPT 0x8E
#define GATETYPE_TRAP      0x8F

InterruptDescriptor64 createIDTEntry64(void(*ISR)(INTERRUPT_ARGS),u8 gateType,u8 privilegeLevel,u8 isValid,u8 IST,u16 selector);

bool isTestInterrupt = 0;//only intended to verify that all handlers get called correctly when the system boots

InterruptDescriptor64* IDT;

extern "C" void sysentry();
extern "C" void __attribute__((noreturn)) sysfuckoff();//couldnt use sysexit so here we are