/*
 * Created Date: Monday February 5th 2024
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

#include "stdint.hxx"

struct APIC_MADT_HEADER
{
    uint8_t EntryType;
    uint8_t Length;
};

struct APIC_MADT_0
{
    APIC_MADT_HEADER Header;
    uint8_t AcpiProcessorID;
    uint8_t ApicID;
    uint32_t Flags;
    //0: enabled
    //1: can be enabled
};

struct APIC_MADT_1
{
    APIC_MADT_HEADER Header;
    uint8_t IO_APIC_ID;
    uint8_t reserved;
    uint32_t IO_APIC_ADDRESS;
    uint32_t GLOBAL_SYSTEM_INTERRUPT_BASE;
};

struct APIC_MADT_2
{
    APIC_MADT_HEADER Header;
    uint8_t BusSource;
    uint8_t IrqSource;
    uint32_t GlobalSystemInterrupt;
    uint16_t Flags;
};

struct APIC_MADT_3
{
    APIC_MADT_HEADER Header;
    uint8_t NmiSource;
    uint8_t reserved;
    uint16_t Flags;
    uint16_t GlobalSystemInterrupt;
};

struct APIC_MADT_4
{
    APIC_MADT_HEADER Header;
    uint8_t ACPIProcessorID; //0xFF means all
    uint16_t Flags;
    uint8_t LINT;
};

struct APIC_MADT_5
{
    APIC_MADT_HEADER Header;
    uint16_t reserved;
    uint64_t LocalApicAddress;
};

struct APIC_MADT_9
{
    APIC_MADT_HEADER Header;
    uint16_t reserved;
    uint32_t ProcessorLocalApicID;
    uint32_t Flags;
    //0: enabled
    //1: can be enabled
    uint32_t AcpiID;
};