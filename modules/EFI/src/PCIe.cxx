/*
 * Created Date: Monday February 5th 2024
 * Author: Lilith
 * -----
 * Last Modified: Monday February 5th 2024 7:22:35 pm
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

#include <main.h>
#include <PCIe.hxx>
#include <DISK.hxx>

extern PCIeEntryInfo_T* PCIeEntryInfo;
uint64_t PCIe_check_device(PCIE_DEVICE_CONFIG* config)
{
    if(config->Header.VendorID == 0xFFFF)
        return PCIe_NO_DEVICE;
    if(PCIeEntryInfo->deviceCount == 0x40000)
    {
        print(u"error: PCIe device list overflow.");
        return PCIe_END;
    }
    PCIeEntryInfo->devices[PCIeEntryInfo->deviceCount] = config;
    PCIeEntryInfo->deviceCount++;
    print(u"---- PCI EXPRESS DEVICE ----\n\r");
    print(u"vendor: ",config->Header.VendorID);
    print(u"device: ",config->Header.DeviceID);
    print(u"class code: ",config->Header.ClassCode);
    print(u"sub class: ",config->Header.SubClass);
    print(u"Header type: ",config->Header.HeaderType);
    switch(config->Header.ClassCode)
    {
        case(0x01):
        {
            switch(config->Header.SubClass)
            {
                case(0x06):
                {
                    //Serial ATA Controller
                    //SATA_check_controller(config);
                }
            }
        }
    }
    return PCIe_OK;
}

void PCIe_check_mmio_area(PCIE_DEVICE_CONFIG* area)
{
    //print(u"device config size: ",sizeof(PCIE_DEVICE_CONFIG));
    uint64_t status = PCIe_OK;
    for(uint64_t i = 0;i<256;i++)
    {
        status = PCIe_check_device(&area[i]);
        if(status == PCIe_END)break;
    }
}
