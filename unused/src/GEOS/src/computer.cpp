/**
 * Created Date: Thursday November 10th 2022
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
#include "../master.h"

const char* CPU_VENDOR_STRING(CPU_VENDOR vendor)
{
    if(vendor == CPU_VENDOR::AMD       ) return "AMD"       ;
    if(vendor == CPU_VENDOR::INTEL     ) return "Intel"     ;
    if(vendor == CPU_VENDOR::QEMU      ) return "QEMU"      ;
    if(vendor == CPU_VENDOR::KVM       ) return "KVM"       ;
    if(vendor == CPU_VENDOR::VMWARE    ) return "VMware"    ;
    if(vendor == CPU_VENDOR::VirtualBox) return "VirtualBox";
    return "INVALID";
}

CPU_VENDOR getVendor(uint32_t EBX,uint32_t ECX,uint32_t EDX)
{
    if(EBX == 'htua' && EDX == 'ntic' && ECX == 'DMAc')return CPU_VENDOR::AMD       ; //AuthenticAMD//
    if(EBX == 'iDMA' && EDX == 'tebs' && ECX == '!ret')return CPU_VENDOR::AMD       ; //AMDisbetter!//
    if(EBX == 'uneG' && EDX == 'Ieni' && ECX == 'letn')return CPU_VENDOR::INTEL     ; //GenuineIntel//
    if(EBX == 'TGCT' && EDX == 'TGCT' && ECX == 'TGCT')return CPU_VENDOR::QEMU      ; //TCGTCGTCGTCG//
    if(EBX == 'MVK ' && EDX == 'KMVK' && ECX == 'MV  ')return CPU_VENDOR::KVM       ; // KVMKVMKVM  //
    if(EBX == 'awMV' && EDX == 'MVer' && ECX == 'eraw')return CPU_VENDOR::VMWARE    ; //VMwareVMware//
    if(EBX == 'xoBV' && EDX == 'xoBV' && ECX == 'xoBV')return CPU_VENDOR::VirtualBox; //VBoxVBoxVBox//
    return CPU_VENDOR::INVALID;
}

void CPUID::update()
{
    //vendor
    __cpuid__(0x00);
    this->vendor = getVendor(getEDX(),getECX(),getEBX());


    //features
    uint64_t __CPUID__ = getCPUFeatures();
    
    this->hasLocalAPIC = getBit((u8*)&__CPUID__,9);
}

void hardware::print()
{
    //CPU
    out << "CPU vendor: " << CPU_VENDOR_STRING(this->cpu.cpuid.vendor) << endl;
    out << "CPU core count: " << this->cpu.coreCount << endl;
    out << "CPU local APIC: " << this->cpu.cpuid.hasLocalAPIC << endl;

    //memory
    out << "available memory: " << (BYTES)this->memorySize << endl;
}
