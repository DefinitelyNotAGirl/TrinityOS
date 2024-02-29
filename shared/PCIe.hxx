/**
Created Date: Thursday February 8th 2024
Author: Lilith (definitelynotagirl115169@gmail.com)
-----
Last Modified: Thursday February 8th 2024 1:54:20 pm
Modified By: Lilith (definitelynotagirl115169@gmail.com)
-----
Copyright (c) 2024 Lilith (definitelynotagirl115169@gmail.com)

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

#include "stdint.hxx"

#define PCIe_OK 0
#define PCIe_END 1
#define PCIe_NO_DEVICE 2

typedef char PCIE_PADDING_BYTE;

enum class PCIe_Class : uint8_t {
    MassStorageController = 0x01,
    DisplayController = 0x03,
};
typedef uint8_t PCIe_SubClass;
enum class PCIe_MassStorageController_SubClass : PCIe_SubClass {
    IDEController = 0x01,
    ATAController = 0x05,
    SerialATAController = 0x06,
};
enum class PCIe_DisplayController_SubClass : PCIe_SubClass {
    VGAController = 0x00,
    XGAController = 0x01,
    _3DController = 0x02,
};
enum class PCIe_Bridge_SubClass : PCIe_SubClass {
    HostBridge = 0x00,
};
enum class PCIe_Vendor : uint16_t {
    INTEL = 0x8086,
    NO_SUCH_DEVICE = 0xFFFF,
};

struct PCIE_DEVICE_CONFIG_HEADER_BASE
{
    uint16_t VendorID;
    uint16_t DeviceID;
    uint16_t Command;
    uint16_t Status;
    uint8_t Revision;
    uint8_t ProgrammingInterface;
    PCIe_SubClass SubClass;
    PCIe_Class ClassCode;
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
