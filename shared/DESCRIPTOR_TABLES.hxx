/*
 * Created Date: Saturday February 10th 2024
 * Author: Lilith
 * -----
 * Last Modified: Saturday February 10th 2024 12:06:25 pm
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

#include "stdint.hxx"
#include "gcc.hxx"

struct GDTPseudo
{
    uint16_t limit;
    uint64_t address;
} PACKED;

struct GDTEntry
{
    uint16_t limit00t15;
    uint16_t base00t15;
    uint8_t  base16t23;
    uint8_t  Attributes;
    uint8_t  Flags;
    uint8_t  base24t31;
};

enum class Interrupt : uint64_t {
    DivideByZero                    = 0x00,
    Debug                           = 0x01,
    NonMaskableInterrupt            = 0x02,
    Breakpoint                      = 0x03,
    Overflow                        = 0x04,
    BoundRange                      = 0x05,
    InvalidOpcode                   = 0x06,
    DeviceNotAvailable              = 0x07,
    DoubleFault                     = 0x08,
    CoprocessorSegmentOverrun       = 0x09,
    InvalidTaskStateSegment         = 0x0A,
    SegmentNotPresent               = 0x0B,
    Stack                           = 0x0C,
    GeneralProtectionFault          = 0x0D,
    PageFault                       = 0x0E,
    //? 0x0F reserved as per AMD64 Volume 2 Page 306
    x87FloatingPointExceptionPending= 0x10,
    AlignmentCheck                  = 0x11,
    MachineCheck                    = 0x12,
    SIMDFloatingPoint               = 0x13,
    //? 0x14 reserved as per AMD64 Volume 2 Page 306
    ControlProtectionException      = 0x15,
    //? 0x16 - 0x1B reserved as per AMD64 Volume 2 Page 306
    HypervisorInjectionException    = 0x1C,
    VMMCommunicationException       = 0x1D,
    SecurityException               = 0x1E,
    //? 0x1F reserved as per AMD64 Volume 2 Page 306
};

struct GATE_DESCRIPTOR_64
{
	uint16_t TargetOffset_0t15;
	uint16_t TargetSelector;
	uint8_t IST;//bits 2-7 reserved
	uint8_t Type;
	uint16_t TargetOffset_16t31;
	uint32_t TargetOffset_32t63;
	uint32_t reserved0;
};

struct IDTPseudo
{
    uint16_t limit;
    uint64_t address;
} PACKED;
