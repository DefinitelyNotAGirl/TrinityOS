/*
 * Created Date: Tuesday February 6th 2024
 * Author: Lilith
 * -----
 * Last Modified: Tuesday February 6th 2024 12:31:54 pm
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
#include <AHCI.hxx>
#include <DISK.hxx>

extern "C" void memset(volatile void* __target, int c, uint64_t n)
{
    char* target = (char*)__target;
    for(uint64_t i = 0;i<n;i++)
    {
        target[i] = c;
    }
}

void AHCI_checkPort(AHCI_PORT_REGISTERS* port)
{
    if(port->SerialAtaStatus == 0)return;
    print(u"---- AHCI PORT ----\n\r");
    print(u"SATA status: ",port->SerialAtaStatus);
} 

void AHCI_enumerateDisks(PCIE_DEVICE_CONFIG* __controller)
{
    PCIE_DEVICE_AHCI_CONTROLLER* controller = (PCIE_DEVICE_AHCI_CONTROLLER*)__controller;
    print(u"enumerating disks on AHCI controller...\n\r");
    uint32_t __ABAR = controller->Header.BAR5 & 0xFFFFE000;
    ABAR_T* ABAR = (ABAR_T*)__ABAR;
    print(u"ABAR address: ",(uint64_t)ABAR);
    for(uint64_t i = 0;i<32;i++)
        AHCI_checkPort(&ABAR->Ports[i]);
}
