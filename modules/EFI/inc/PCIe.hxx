/*
 * Created Date: Monday February 5th 2024
 * Author: Lilith
 * -----
 * Last Modified: Monday February 5th 2024 7:22:08 pm
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

#define PCIe_OK 0
#define PCIe_END 1
#define PCIe_NO_DEVICE 2

typedef char PCIE_PADDING_BYTE;

struct PCIE_DEVICE_CONFIG_HEADER_BASE
{
    uint16_t VendorID;
    uint16_t DeviceID;
    uint16_t Command;
    uint16_t Status;
    uint8_t Revision;
    uint8_t ProgIF;
    uint8_t SubClass;
    uint8_t ClassCode;
    uint8_t CacheLineSize;
    uint8_t LatencyTimer;
    uint8_t HeaderType;
    uint8_t BIST;
};

struct PCIE_DEVICE_CONFIG
{
    PCIE_DEVICE_CONFIG_HEADER_BASE Header;
    PCIE_PADDING_BYTE padding[4096-sizeof(PCIE_DEVICE_CONFIG_HEADER_BASE)];
};

struct PCIE_HEADER_0
{
    PCIE_DEVICE_CONFIG_HEADER_BASE Header;
    uint32_t BAR0;
    uint32_t BAR1;
    uint32_t BAR2;
    uint32_t BAR3;
    uint32_t BAR4;
    uint32_t BAR5;
    uint32_t cardBusCisPointer;
    uint16_t SubSystemVendorID;
    uint16_t SubSystemID;
    uint32_t ExpansionRomBaseAddress;
    uint8_t CapabilitiesPointer;
    uint8_t Reserved0;
    uint16_t Reserved1;
    uint8_t InterruptLine;
    uint8_t InterruptPin;
    uint8_t MinGrant;
    uint8_t MaxLatency;
};

struct PCIE_DEVICE_AHCI_CONTROLLER
{
    PCIE_HEADER_0 Header;
};

uint64_t PCIe_check_device(PCIE_DEVICE_CONFIG* config);
void PCIe_check_mmio_area(PCIE_DEVICE_CONFIG* area);

struct PCIeEntryInfo_T
{
    uint64_t deviceCount;
    PCIE_DEVICE_CONFIG* devices[];
};
