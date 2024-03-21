/**
Created Date: Monday February 12th 2024
Author: Lilith (definitelynotagirl115169@gmail.com)
-----
Last Modified: Thursday February 29th 2024 5:18:25 am
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

#include <INIT.h>
#include <PCIe.hxx>
#include <Log.hxx>

PCIeEntryInfo_T* PCIeEntryInfo = (PCIeEntryInfo_T*)0x200000;
uint64_t mmioAddress = 0x10000000;

void FindBootDisk()
{
	TrinityLog::print("["ANSI_BLUE"INFO"ANSI_RESET"]Searching for boot disk...\n");
    //*
    //* map a read page at 0x3200000
    //*
    if(setPage(TrinityPageType::ReadWriteData,RandomPhysicalAddress,0x3200000,Kernel) != TrinitySetPageReturn::OK)
        sysDBGExit(ERROR_R15,ERROR_SETPAGE,(uint64_t)lastSetPageError);
    //*
    //* search for mass storage controllers
    //*
    for(uint64_t i = 0;i<PCIeEntryInfo->deviceCount;i++)
    {
        PCIE_DEVICE_CONFIG* device = PCIeEntryInfo->devices[i];
        if(device->Header.ClassCode == PCIe_Class::MassStorageController)
        {
            switch((PCIe_MassStorageController_SubClass)device->Header.SubClass)
            {
                case(PCIe_MassStorageController_SubClass::SerialATAController):
                {
                    if(device->Header.ProgrammingInterface == 0x01)
                    {//* AHCI
                        AHCI::checkController(device);
                    }
                    break;
                }
            }
        }
    }
}