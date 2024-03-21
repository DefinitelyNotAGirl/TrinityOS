/**
 * Created Date: Saturday May 27th 2023
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
#pragma once

#include <INIT.h>
#include <PAGING.hxx>
#include <MEMMAP.hxx>
#include <APP_INFO.hxx>
#include <bits.hxx>

#define TRINITY_PAGE_SIZE 0x200000

uint64_t* PhysicalMemoryMapSize = (uint64_t*)0x1800000;
TRINITY_MEMORY_VITAL* VitalMemoryValues = (TRINITY_MEMORY_VITAL*)(0x1800000+sizeof(uint64_t));
TRINITY_MEMORY_MAP_ENTRY* PhysicalMemoryMap = (TRINITY_MEMORY_MAP_ENTRY*)(0x1800000+sizeof(uint64_t)+sizeof(TRINITY_MEMORY_VITAL));

//, ███████ ██ ███████ ██      ██████      ███    ███  █████  ██████  ███████
//, ██      ██ ██      ██      ██   ██     ████  ████ ██   ██ ██   ██ ██
//, █████   ██ █████   ██      ██   ██     ██ ████ ██ ███████ ██████  ███████
//, ██      ██ ██      ██      ██   ██     ██  ██  ██ ██   ██ ██           ██
//, ██      ██ ███████ ███████ ██████      ██      ██ ██   ██ ██      ███████
namespace paging::FieldMaps {
	void print_pde(FieldMap<uint64_t, 10> *map)
	{
	}
	FieldMap<uint64_t,10> PDE({
			Field<uint64_t>((1<<0),FieldType::Boolean,"P"),
			Field<uint64_t>((1<<1),FieldType::Boolean,"R/W"),
			Field<uint64_t>((1<<2),FieldType::Boolean,"U/S"),
			Field<uint64_t>((1<<3),FieldType::Boolean,"PWT"),
			Field<uint64_t>((1<<4),FieldType::Boolean,"PCD"),
			Field<uint64_t>((1<<5),FieldType::Boolean,"A"),
			Field<uint64_t>((1<<6),FieldType::Boolean,"D"),
			Field<uint64_t>((1<<8),FieldType::Boolean,"G"),
			Field<uint64_t>((1<<12),FieldType::Boolean,"PAT"),
			Field<uint64_t>((1<<63),FieldType::Boolean,"NX")
		},nullptr
	);
}

uint64_t getPhysicalAddress(uint64_t virtualAddress,PROCESS_INFO* process)
{
    return ((process->PageTables.PAGES[virtualAddress/TRINITY_PAGE_SIZE] & 0xFFFFFFFE00000)+virtualAddress%TRINITY_PAGE_SIZE);
}

void setPhysicalPageUsed(uint64_t address)
{
    for(uint64_t i = 0;i<*PhysicalMemoryMapSize;i++)
    {
        TRINITY_MEMORY_MAP_ENTRY* Entry = &PhysicalMemoryMap[i];
        if(Entry->MemoryControllerAddress == address)
        {
            Entry->Type = TRINITY_MEMORY_TYPE_RAM_USED;
            return;
        }
    }
}

void initiatePageTable(PROCESS_INFO* process)
{
    {//initiate PML4 table
        {//[0]
            uint64_t entry = &process->PageTables.PML3[0];//address of page-directory-pointer
            CLEARBIT_03(entry); // clear PWT
            CLEARBIT_05(entry); // clear Accessed
            CLEARBIT_06(entry); // clear Dirty
            CLEARBIT_07(entry); // MBZ
            CLEARBIT_08(entry); // MBZ
            CLEARBIT_04(entry); // enable page cache
            SETBIT_00(entry); // set present
            SETBIT_01(entry); // set write
            if(process->ProcessMode == TrinityProcessMode::Kernel)
                SETBIT_02(entry); // set supervisoronly
            else
                CLEARBIT_02(entry); // clear supervisoronly
            CLEARBIT_63(entry); // set NoExecute
            process->PageTables.PML4[0] = entry;
        }
        for(uint64_t i = 1;i<512;i++)
        {//[1-511]
            process->PageTables.PML4[i] = 0;
        }
    }
    for(uint64_t i = 0;i<512;i++)
    {//initiate page-directory-pointers
        uint64_t entry = &process->PageTables.PAGES[i*0x200];//address of page-directory
        CLEARBIT_03(entry); // clear PWT
        CLEARBIT_05(entry); // clear Accessed
        CLEARBIT_06(entry); // IGN
        CLEARBIT_07(entry); // MBZ
        CLEARBIT_08(entry); // IGN
        CLEARBIT_04(entry); // enable page cache
        SETBIT_00(entry); // set present
        SETBIT_01(entry); // set write
        if(process->ProcessMode == TrinityProcessMode::Kernel)
            SETBIT_02(entry); // set supervisoronly
        else
            CLEARBIT_02(entry); // clear supervisoronly
        CLEARBIT_63(entry); // set NoExecute
        process->PageTables.PML3[i] = entry;
    }
}

uint64_t findFreePhysicalPage()
{
    //sysDBGExit(0xBBBBBBBBBBBBBBBB,*PhysicalMemoryMapSize,PhysicalMemoryMapSize,sizeof(TRINITY_MEMORY_MAP_ENTRY),getPhysicalAddress(PhysicalMemoryMapSize,Kernel));
    for(uint64_t i = 0;i<*PhysicalMemoryMapSize;i++)
    {
        TRINITY_MEMORY_MAP_ENTRY* Entry = &PhysicalMemoryMap[i];
        if(Entry->Type == TRINITY_MEMORY_TYPE_RAM)
        {
            if(Entry->MemoryControllerAddress == nullptr)
                continue;
            Entry->Type = TRINITY_MEMORY_TYPE_RAM_USED;
            return Entry->MemoryControllerAddress;
        }
    }
    return nullptr;
}

uint64_t findFreeVirtualPage(PROCESS_INFO* process)
{
    for(uint64_t i = 1;i<0x40000;i++)
    {
        if(process->PageTables.PAGES[i] == 0)
            return i*TRINITY_PAGE_SIZE;
    }
    return nullptr;
}

uint64_t getVirtualAddress(uint64_t physicalAddress, PROCESS_INFO* process)
{
    for(uint64_t i = 0;i<0x40000;i++)
    {
        if(process->PageTables.PAGES[i] & 0xFFFFFFFE00000 == ((physicalAddress/TRINITY_PAGE_SIZE)*TRINITY_PAGE_SIZE))
            return i*TRINITY_PAGE_SIZE+(physicalAddress%TRINITY_PAGE_SIZE);
    }
    return UINT64_T_MAX;
}

TrinitySetPageReturn lastSetPageError = TrinitySetPageReturn::OK;
TrinitySetPageReturn setPage(TrinityPageType mode,uint64_t physicalAddress,uint64_t virtualAddress,PROCESS_INFO* process)
{
    if(virtualAddress == RandomVirtualAddress)
    {
        uint64_t fvirt = findFreeVirtualPage(Kernel);
        if(fvirt == nullptr)
        {
            lastSetPageError = TrinitySetPageReturn::OutOfVirtualMemory;
            return TrinitySetPageReturn::OutOfVirtualMemory;
        }
        virtualAddress = fvirt;
    }
    if(virtualAddress > process->VirtualAddressLimit-TRINITY_PAGE_SIZE)
    {
        lastSetPageError = TrinitySetPageReturn::VirtualOutOfBounds;
        return TrinitySetPageReturn::VirtualOutOfBounds;
    }
    if(physicalAddress == RandomPhysicalAddress)
    {
        uint64_t fphys = findFreePhysicalPage();
        if(fphys == nullptr)
        {
            lastSetPageError = TrinitySetPageReturn::OutOfPhysicalMemory;
            return TrinitySetPageReturn::OutOfPhysicalMemory;
        }
        physicalAddress = fphys;
    }
    //
    //form data entry
    //
    uint64_t entry = physicalAddress;
    SETBIT_00(entry);//set present
    if(process->ProcessMode == TrinityProcessMode::Kernel)
        SETBIT_02(entry); // set supervisoronly
    else
        CLEARBIT_02(entry); // clear supervisoronly
    CLEARBIT_05(entry); //clear accessed
    CLEARBIT_06(entry); //clear dirty
    SETBIT_07(entry); //set 7 (MBO)
    CLEARBIT_08(entry); //clear global
    //clear 13-20
    entry &= 0xFFFFFFFFFFE01FFF;
    switch(mode)
    {
        case(TrinityPageType::Code):
        {
            CLEARBIT_63(entry);//Allow Execution
            SETBIT_01(entry);//Allow Reading
            CLEARBIT_03(entry);//Enable Caching
            CLEARBIT_04(entry);//Disable Write Through
            break;
        }
        case(TrinityPageType::ReadWriteData):
        {
            SETBIT_63(entry);// prevent execution
            SETBIT_01(entry);// allow writing
            CLEARBIT_03(entry);// enable caching
            CLEARBIT_04(entry);// disable write through
            break;
        }
        case(TrinityPageType::ReadOnlyData):
        {
            SETBIT_63(entry);// prevent execution
            CLEARBIT_01(entry);// prevent writing
            CLEARBIT_03(entry);// enable caching
            CLEARBIT_04(entry);// disable write through
            break;
        }
        case(TrinityPageType::MemoryMappedIO):
        {
            SETBIT_63(entry);// prevent execution
            SETBIT_01(entry);// allow writing
            SETBIT_03(entry);// disable caching
            CLEARBIT_04(entry);// disable write through
            break;
        }
        case(TrinityPageType::NotPresent):
        {
            CLEARBIT_00(entry); // clear present
            break;
        }
        default:
            return TrinitySetPageReturn::InvalidMode;
    }
    //
    //write to page table
    //
    process->PageTables.PAGES[virtualAddress/TRINITY_PAGE_SIZE] = entry;
    //
    //return
    //
    return TrinitySetPageReturn::OK;
}
