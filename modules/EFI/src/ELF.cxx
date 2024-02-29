/*
 * Created Date: Tuesday February 6th 2024
 * Author: Lilith
 * -----
 * Last Modified: Tuesday February 6th 2024 7:16:42 pm
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
#include <ELF.hxx>
#include <bits>
#include <Uefi.h>
#include <MEMMAP.hxx>

extern EFI_SYSTEM_TABLE* sysTable;

EFI_STATUS Allocate2MiBDataPage(EFI_PHYSICAL_ADDRESS* memory)
{
    switch(sysTable->BootServices->AllocatePages(AllocateAnyPages,EfiLoaderData,0x600,memory))
    {
        case(EFI_NOT_FOUND):
            print(u"error: The requested pages could not be found.\n\r");
            return NULL;
        case(EFI_INVALID_PARAMETER):
            print(u"error: EFI_INVALID_PARAMETER.\n\r");
            return NULL;
        case(EFI_SUCCESS):
            break;
        default:
            print(u"error: UNKNOWN\n\r");
            return NULL;
    }
    uint64_t addr = *memory;
    for(uint64_t i = 0;i<0x600;i++)
    {
        uint64_t paddr = addr+(i*0x1000);
        if(paddr%0x200000 == 0)
        {
            return paddr;
        }
    }
    return 0;
}

uint64_t AllocateDataPage(uint64_t address,uint64_t size)
{
    EFI_PHYSICAL_ADDRESS memory = address;
    //uint64_t pages = size/0x1000;if(size%0x1000 != 0)pages++;
    //print(u"page count: ",pages);
    return Allocate2MiBDataPage(&memory);
}

bool AllocateCodePage(uint64_t address,uint64_t size)
{
    EFI_PHYSICAL_ADDRESS memory = address;
    uint64_t pages = size/0x1000;if(size%0x1000 != 0)pages++;
    print(u"page count: ",pages);
    switch(sysTable->BootServices->AllocatePages(AllocateAnyPages,EfiLoaderCode,pages,&memory))
    {
        case(EFI_NOT_FOUND):
            print(u"error: The requested pages could not be found.\n\r");
            return false;
        case(EFI_INVALID_PARAMETER):
            print(u"error: EFI_INVALID_PARAMETER.\n\r");
            return false;
        case(EFI_SUCCESS):
            return true;
        default:
            print(u"error: UNKNOWN\n\r");
            return false;
    }
    return false;
}

void copy(void* __src,void* __dst,uint64_t len)
{
    uint8_t* src = (uint8_t*)__src;
    uint8_t* dst = (uint8_t*)__dst;
    for(uint64_t i = 0;i<len;i++)
        dst[i] = src[i];
}

uint64_t loadELF64(char* data)
{
    print(u"---- LOADING ELF64 BINARY ----\n\r");
    ELF64_HEADER* Header = (ELF64_HEADER*)data;
    if(Header->Magic != 0x464c457f)
        return print(u"Invalid magic value!");
    switch(Header->Type)
    {
        case(2):
            print(u"Type: Executable\n\r");
            break;
        default:
            print(u"Type: ",Header->Type);
    }
    print(u"Entrypoint: ",Header->EntryPoint);
    ELF64_PROGRAM_HEADER* ProgramHeaderTable = (ELF64_PROGRAM_HEADER*)(((uint64_t)data)+Header->ProgramHeaderTableOffset);
    ELF64_SECTION_HEADER* SectionHeaderTable = (ELF64_SECTION_HEADER*)(((uint64_t)data)+Header->SectionHeaderTableOffset);
    for(uint64_t i = 0;i<Header->ProgramHeaderCount;i++)
    {
        ELF64_PROGRAM_HEADER* ProgramHeader = &ProgramHeaderTable[i];
        if(ProgramHeader->Type == 0)continue;
        print(u" ==> PROGRAM HEADER <==\n\r");
        print(u"Type: ",ProgramHeader->Type);
        switch(ProgramHeader->Type)
        {
            case(1): // loadable segment (PT_LOAD)
            {
                print(u"Virtual Address: ",ProgramHeader->VirtualAddress);
                bool Execute = false;
                bool read = false;
                bool write = false;
                print(u"permissions: ");
                if(EXPR_GETBIT_00(ProgramHeader->Flags))
                {
                    Execute = true;
                    print(u"X");
                }
                if(EXPR_GETBIT_02(ProgramHeader->Flags))
                {
                    read = true;
                    print(u"R");
                }
                if(EXPR_GETBIT_01(ProgramHeader->Flags))
                {
                    write = true;
                    print(u"W");
                }
                print(u"\n\r");
                print(u"Size in file: ",ProgramHeader->SizeInFile);
                print(u"Size in memory: ",ProgramHeader->SizeInMemory);
                if(ProgramHeader->SizeInMemory == 0)
                    continue;
                uint64_t addr = AllocateDataPage(ProgramHeader->VirtualAddress,0x200000);
                switch(ProgramHeader->VirtualAddress)
                {
                    case(0x800000):
                        TrinityVitalMemoryAddresses->INIT_CODE_PHYS = addr;break;
                    case(0xA00000):
                        TrinityVitalMemoryAddresses->INIT_RW_PHYS = addr;break;
                    case(0xC00000):
                        TrinityVitalMemoryAddresses->INIT_RO_PHYS = addr;break;
                    case(0xE00000):
                        TrinityVitalMemoryAddresses->INIT_BSS_PHYS = addr;break;
                }
                void* srcData = (void*)(((uint64_t)data)+ProgramHeader->OffsetInFile);
                if(ProgramHeader->SizeInFile == ProgramHeader->SizeInMemory)
                    copy(srcData,(void*)addr,ProgramHeader->SizeInFile);
                else
                    print(u"error: source size != memory size\n\r");
                if(Execute)
                    AllocateCodePage(addr,0x200000);
                break;
            }
        }
    }
    for(uint64_t i = 0;i<Header->SectionHeaderCount;i++)
    {
        ELF64_SECTION_HEADER* SectionHeader = &SectionHeaderTable[i];
        if(SectionHeader->Type == 0)continue;
        print(u" ==> SECTION HEADER <==\n\r");
        print(u"Type: ",SectionHeader->Type);
        switch(SectionHeader->Type)
        {
            case(0x11): //section group (SHT_GROUP)
            {
                break;
            }
        }
    }
    uint64_t entryPoint = TrinityVitalMemoryAddresses->INIT_CODE_PHYS+(Header->EntryPoint-0x800000);
    return entryPoint;
    //return Header->EntryPoint;
}
