/**
 * Created Date: Wednesday May 31st 2023
 * Author: DefinitelyNotAGirl@github
 * -----
 * Last Modified: Tuesday July 18th 2023 4:41:54 pm
 * Modified By: Lilith (definitelynotagirl115169@gmail.com)
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

#include <PCIe.hxx>
#include <INIT.h>
#include <APP_INFO.hxx>
#include <PAGING.hxx>
#include <DESCRIPTOR_TABLES.hxx>
#include <MiscStructs.hxx>
#include <MemoryConstants.hxx>
#include <ASM.hxx>
#include <print.hxx>

PROCESS_INFO* Kernel;

DebugData_T* DebugData = (DebugData_T*)0x600000;

//, ██ ███    ██ ████████ ███████ ██████  ██████  ██    ██ ██████  ████████ ███████
//, ██ ████   ██    ██    ██      ██   ██ ██   ██ ██    ██ ██   ██    ██    ██
//, ██ ██ ██  ██    ██    █████   ██████  ██████  ██    ██ ██████     ██    ███████
//, ██ ██  ██ ██    ██    ██      ██   ██ ██   ██ ██    ██ ██         ██         ██
//, ██ ██   ████    ██    ███████ ██   ██ ██   ██  ██████  ██         ██    ███████
extern "C" void interrupt_disassemble();

//+ ███████ ███    ██ ████████ ██████  ██    ██
//+ ██      ████   ██    ██    ██   ██  ██  ██
//+ █████   ██ ██  ██    ██    ██████    ████
//+ ██      ██  ██ ██    ██    ██   ██    ██
//+ ███████ ██   ████    ██    ██   ██    ██
extern "C" void kernel_entry_cpp()
{
    //*
    //* init kernel PROCESS_INFO struct
    //*
    Kernel = (PROCESS_INFO*)(0x2400000);
    Kernel->AppID = 0;
    Kernel->ProccessID = 0;
    Kernel->MemoryLimit = 0;
    Kernel->MemoryUsage = TRINITY_PAGE_SIZE*8;
    Kernel->ProcessMode = TrinityProcessMode::Kernel;
    Kernel->SystemInterface = TrinitySystemInterfaceMode::TRINITY;
    Kernel->VirtualAddressLimit = 0x40000*TRINITY_PAGE_SIZE;
    setPage(TrinityPageType::ReadWriteData,RandomPhysicalAddress,0x2600000,Kernel);// upper page table
    //*
    //* mark used physical pages
    //*
    setPhysicalPageUsed(getPhysicalAddress(0x0800000,Kernel));
    setPhysicalPageUsed(getPhysicalAddress(0x0A00000,Kernel));
    setPhysicalPageUsed(getPhysicalAddress(0x0C00000,Kernel));
    setPhysicalPageUsed(getPhysicalAddress(0x0E00000,Kernel));
    setPhysicalPageUsed(getPhysicalAddress(0x0400000,Kernel));
    setPhysicalPageUsed(getPhysicalAddress(0x2400000,Kernel));
    setPhysicalPageUsed(getPhysicalAddress(0x1800000,Kernel));
    setPhysicalPageUsed(VitalMemoryValues->PCIE_PHYS);
	setPhysicalPageUsed(VitalMemoryValues->RSDT_PHYS);
    setPage(TrinityPageType::ReadWriteData,VitalMemoryValues->PCIE_PHYS,0x200000,Kernel);
    //*
    //* initate GDT
    //*
    TrinitySetPageReturn status;
    status = setPage(TrinityPageType::ReadWriteData,RandomPhysicalAddress,0x3000000,Kernel);// descriptor table page
    if(status != TrinitySetPageReturn::OK)
        sysDBGExit(0xFEDCBA9876543210,(uint64_t)status);
    setupGDT();
    setupIDT();
	//*
    //* map PCI Express Devices into memory
    //*
    for(uint64_t i = 0;i<PCIeEntryInfo->deviceCount;i++)
    {
        //sysDBGExit(0x3333,&PCIeEntryInfo->devices,PCIeEntryInfo->devices[i]);
        PCIE_DEVICE_CONFIG* device = PCIeEntryInfo->devices[i];
        uint64_t physp = ((uint64_t)device/TRINITY_PAGE_SIZE)*TRINITY_PAGE_SIZE;
        uint64_t virt = getVirtualAddress(physp,Kernel);
        if(virt == UINT64_T_MAX)
        {
            setPage(TrinityPageType::MemoryMappedIO,physp,mmioAddress,Kernel);
            PCIeEntryInfo->devices[i] = mmioAddress+((uint64_t)device%TRINITY_PAGE_SIZE);
            mmioAddress += TRINITY_PAGE_SIZE;
        }
    }
	//*
	//* initiate misc data areas
	//*
	setPage(TrinityPageType::ReadWriteData,RandomPhysicalAddress,0x600000,Kernel);
	setPage(TrinityPageType::ReadWriteData,0x000000,MEM_ADDR_BOTTOM,Kernel);
	//*
    //* check if we have a trinity log device
    //*
	for(uint64_t i = 0;i<PCIeEntryInfo->deviceCount;i++)
    {
        PCIE_DEVICE_CONFIG* device = PCIeEntryInfo->devices[i];
        if((uint64_t)device->Header.ClassCode == 0xFF)
        {
            switch((uint64_t)device->Header.SubClass)
            {
                case(0xFE):
                {
					TrinityLog::init(device);
                    break;
                }
            }
        }
    }
	TrinityLog::disassemble(0x008031b2);
	//*
	//* ACPI
	//*
	TrinityLog::print("Initiating ACPI...\n");
	ACPI::Init(VitalMemoryValues->RSDT_PHYS);
	ACPI::InitAPICs();
	sti;
    //*
    //* find boot disk and load remaining kernel modules
    //*
	TrinityLog::print("Searching for boot disk...\n");
    FindBootDisk();
    //!
    //! success output
    //!
}
