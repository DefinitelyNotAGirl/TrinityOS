/**
 * Author: DefinitelyNotAGirl@github
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

#include <Uefi.h>
#include <SimpleFileSystem.h>
#include <LoadedImage.h>

#include <main.h>
#include <PCIe.hxx>

EFI_SYSTEM_TABLE* sysTable;

EFI_STATUS status = 0;

void print(uint16_t* msg)
{
    //return;
    //sysTable->ConOut->OutputString(sysTable->ConOut,msg);
}

uint64_t print(const char16_t* msg)
{
    //return 0;
    //sysTable->ConOut->OutputString(sysTable->ConOut,(UINT16*)msg);
    return 0;
}

uint64_t nodbg_print(const char16_t* msg)
{
    sysTable->ConOut->OutputString(sysTable->ConOut,(UINT16*)msg);
    return 0;
}

static void* memMap;
static void* EFImemmap;

void meminit()
{
}

uint64_t strlen(char* str){uint64_t counter = 0;while(*(str++)!=0)counter++;return counter;}

uint64_t malloc(uint64_t size)
{
    for(uint64_t* entry = (uint64_t*)memMap; entry != 0; entry+=8)
    {
        if(*entry == MC64("TRINITYFREE"))
        {
            *entry = MC64("TRINITYUSED");
            return ((entry-(uint64_t*)memMap)/8*0x200000);
        }
    }
    return 0;
}

static const char* HEXDIG = "0123456789abcdef";

extern "C" void printHex64(uint64_t value)
{
    uint16_t data[19];
    data[18] = 0x0000;
    ((uint32_t*)data)[0] = 0x00780030;// '0x'
    for(uint8_t I = 17;I>1;I--)
    {
        data[I] = HEXDIG[value&0xF];
        value>>=4;
    }
    print(data);
}

extern "C" void print64(uint64_t value)
{
    uint64_t i = 0;
    while(i < 8)
    {
        uint32_t v = ((uint8_t*)&value)[i++] | 0b11111111111111110000000000000000;
        print((uint16_t*)(&v));
    }
}
extern "C" void print32(uint32_t value)
{
    uint64_t i = 0;
    while(i < 4)
    {
        uint32_t v = ((uint8_t*)&value)[i++] | 0b11111111111111110000000000000000;
        print((uint16_t*)(&v));
    }
}

extern "C" void print64r(uint64_t value)
{
    uint64_t i = 7;
    while(i >= 0 && i != 0xFFFFFFFFFFFFFFFF)
    {
        uint32_t v = ((uint8_t*)&value)[i--] | 0b11111111111111110000000000000000;
        print((uint16_t*)(&v));
    }
}
extern "C" void print32r(uint32_t value)
{
    uint64_t i = 3;
    while(i >= 0 && i != 0xFFFFFFFFFFFFFFFF)
    {
        uint32_t v = ((uint8_t*)&value)[i--] | 0b11111111111111110000000000000000;
        print((uint16_t*)(&v));
    }
}

bool operator==(GUID& a, GUID& b)
{
    if(((uint64_t*)(&a))[0] != ((uint64_t*)(&b))[0])
        return false;
    if(((uint64_t*)(&a))[1] != ((uint64_t*)(&b))[1])
        return false;
    return true;
}

bool guidWasUnknown = false;
const char16_t* getDtId(EFI_GUID* guid)
{
    if(*guid == GUID_ACPI) return u"ACPI 1";
    if(false) return u"ACPI 2";
    if(*guid == GUID_SAL_SYSTEM) return u"SAL SYSTEM";
    if(*guid == GUID_SMBIOS) return u"SMBIOS";
    if(*guid == GUID_SMBIOS3) return u"SMBIOS3";
    if(*guid == GUID_MPS) return u"MPS";
    if(*guid == GUID_PROPERTIES_TABLE) return u"PROPERTIES_TABLE";
    guidWasUnknown = true;
    return u"UNKNOWN";
}

extern "C" uint64_t printSDT(uint64_t address,void* guid)
{
    print(u"######### SDT #########\n\r");
    print(u"address: ");
    printHex64(address);
    print(u"\n\rID: ");
    print(getDtId((EFI_GUID*)guid));
    if((uint64_t)guid % (uint64_t)8 != 0)
        print(u"\n\rguid not aligned!");
    if(guidWasUnknown)
    {
        guidWasUnknown = false;
        print(u"\n\rguid1: ");
        printHex64(*(((uint64_t*)guid)+0));
        print(u"\n\rguid2: ");
        printHex64(*(((uint64_t*)guid)+1));
    }
    print(u"\n\r");
    return 0;
}

void listConfigTable()
{
    // EFI_CONFIGURATION_TABLE is 24 bytes long
    //  +0: VendorGUID (0-63)
    //  +8: VendorGUID (64-127)
    // +16: address of table data
    EFI_CONFIGURATION_TABLE* efiConfigTable = sysTable->ConfigurationTable;
    uint64_t entries = sysTable->NumberOfTableEntries;

    //read data
    for(uint64_t i = 0; i < entries; i++)
    {
        if(efiConfigTable[i].VendorGuid == GUID_ACPI){print(u"ACPI");econf.ACPI = efiConfigTable[i].VendorTable;}
        else if(efiConfigTable[i].VendorGuid == GUID_SAL_SYSTEM){print(u"SAL_SYSTEM");econf.SAL_SYSTEM = efiConfigTable[i].VendorTable;}
        else if(efiConfigTable[i].VendorGuid == GUID_SMBIOS){print(u"SMBIOS");econf.SMBIOS = efiConfigTable[i].VendorTable;}
        else if(efiConfigTable[i].VendorGuid == GUID_SMBIOS3){print(u"SMBIOS3");econf.SMBIOS3 = efiConfigTable[i].VendorTable;}
        else if(efiConfigTable[i].VendorGuid == GUID_MPS){print(u"MPS");econf.MPS = efiConfigTable[i].VendorTable;}
        else if(efiConfigTable[i].VendorGuid == GUID_PROPERTIES_TABLE){print(u"PROPERTIES");econf.PROPERTIES = efiConfigTable[i].VendorTable;}
        else goto LCT_skipFoundPrint;
        print(u" table found!\n\r");
        LCT_skipFoundPrint: ;
    }
}

char* strreverse(char* str)
{
    uint64_t len = strlen(str);
    uint64_t start = 0;
    uint64_t end = len-1;
    while(start < end)
    {
        str[start] ^= str[end];
        str[end] ^= str[start];
        str[start] ^= str[end];

        start++;
        end--;
    }
    return str;
}

EFI_FILE_HANDLE Volume;

EFI_FILE_HANDLE GetVolume(EFI_HANDLE image)
{
    EFI_LOADED_IMAGE *loaded_image = NULL;                  /* image interface */
    EFI_GUID lipGuid = EFI_LOADED_IMAGE_PROTOCOL_GUID;      /* image interface GUID */
    EFI_FILE_IO_INTERFACE *IOVolume;                        /* file system interface */
    EFI_GUID fsGuid = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID; /* file system interface GUID */
    EFI_FILE_HANDLE Volume;                                 /* the volume's interface */
    /* get the loaded image protocol interface for our "image" */
    sysTable->BootServices->HandleProtocol(image, &lipGuid, (void **) &loaded_image);
    /* get the volume handle */
    sysTable->BootServices->HandleProtocol(loaded_image->DeviceHandle, &fsGuid, (VOID**)&IOVolume);
    IOVolume->OpenVolume(IOVolume, &Volume);
    return Volume;
}


void FreePool(void* pool)
{
    void* memory;
    sysTable->BootServices->FreePool(pool);
}


void* AllocatePool(uint64_t size)
{
    void* memory;
    sysTable->BootServices->AllocatePool(EfiLoaderData,size,&memory);
    return memory;
}

EFI_GUID EFI_FILE_INFO_ID = {0x09576e92,0x6d3f,0x11d2,{0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b}};

uint64_t FileSize(EFI_FILE_HANDLE handle)
{
    UINTN bufferSize = 0x100;
    void* buffer = AllocatePool(bufferSize);
    if(handle->GetInfo(handle,&EFI_FILE_INFO_ID,&bufferSize,buffer) == EFI_BUFFER_TOO_SMALL)
    {
        FreePool(buffer);
        buffer = AllocatePool(bufferSize);
        handle->GetInfo(handle,&EFI_FILE_INFO_ID,&bufferSize,buffer);
    }
    print(u"struct size: ",((uint64_t*)buffer)[0]);
    print(u"file size: ",((uint64_t*)buffer)[1]);
    uint64_t size = ((uint64_t*)buffer)[1];
    FreePool(buffer);
    return size;
}

char* loadFile(const char16_t* path)
{
    EFI_FILE_HANDLE     FileHandle;
    /* open the file */
    Volume->Open(Volume, &FileHandle, (CHAR16*)path, EFI_FILE_MODE_READ, EFI_FILE_READ_ONLY | EFI_FILE_HIDDEN | EFI_FILE_SYSTEM);
    /* read from the file */
    UINT64 ReadSize = FileSize(FileHandle);
    UINT8* Buffer = (UINT8*)AllocatePool(ReadSize);
    FileHandle->SetPosition(FileHandle, 0);
    FileHandle->Read(FileHandle, &ReadSize, Buffer);
    print(u"bytes read: ",(uint64_t)ReadSize);
    FileHandle->Close(FileHandle);
    return (char*) Buffer;
}

#include <ELF.hxx>
#include <MEMMAP.hxx>
uint64_t AllocateDataPage(uint64_t address,uint64_t size);
bool AllocateCodePage(uint64_t address,uint64_t size);
uint64_t* TRINITY_MEMORY_MAP_SIZE;
TRINITY_MEMORY_VITAL* TrinityVitalMemoryAddresses;
TRINITY_MEMORY_MAP_ENTRY* TrinityMemoryMap;

extern "C" void kjump(uint64_t entrypoint,TRINITY_MEMORY_VITAL* TRINITY_VITAL);
extern "C" void efiLoaderHang();

void loadKernelINIT(EFI_HANDLE image, UINTN mapKey)
{
    uint64_t k_init_entry = 0;
    {
        print(u"loading: TrinityOS\\kernel\\INIT.elf64\n\r");
        char* data = loadFile(u"TrinityOS\\kernel\\INIT.elf64");
        print(u"data: ",(uint64_t)data);
        k_init_entry = loadELF64(data);
        FreePool(data);
    }
    print(u"init phys start: ",TrinityVitalMemoryAddresses->INIT_CODE_PHYS);
    print(u"TRINITY_MEMORY_MAP_SIZE: ",*TRINITY_MEMORY_MAP_SIZE);
    nodbg_print(u"transfering control to kernel now...");
    //for(uint64_t i = 0;i<1000;i++){}
    sysTable->BootServices->ExitBootServices(image,mapKey);
    kjump(k_init_entry,TrinityVitalMemoryAddresses);
    efiLoaderHang();
}

TRINITY_MEMORY_MAP_ENTRY* findTRINITY_MEMORY_MAP_ENTRY(uint64_t address)
{
    for(uint64_t i = 0;i<*TRINITY_MEMORY_MAP_SIZE;i++)
    {
        if(TrinityMemoryMap[i].MemoryControllerAddress == address)
            return &TrinityMemoryMap[i];
    }
    return nullptr;
}
TRINITY_MEMORY_TYPE EfiToTrinityMemoryType(uint32_t EfiType)
{
    switch(EfiType)
    {
        #ifndef IGNORE_EFI_RESERVED_MEMORY_TYPE
            case(EfiReservedMemoryType):
        #endif
        case(EfiRuntimeServicesCode):
        case(EfiRuntimeServicesData):
        case(EfiACPIMemoryNVS):
        case(EfiPalCode):
            return TRINITY_MEMORY_TYPE_PRESERVE;
        case(EfiMemoryMappedIO):
        case(EfiMemoryMappedIOPortSpace):
            return TRINITY_MEMORY_TYPE_MMIO;
        #ifdef IGNORE_EFI_RESERVED_MEMORY_TYPE
            case(EfiReservedMemoryType):
        #endif
        case(EfiLoaderCode):
        case(EfiLoaderData):
        case(EfiBootServicesCode):
        case(EfiBootServicesData):
        case(EfiConventionalMemory):
        case(EfiPersistentMemory):
            return TRINITY_MEMORY_TYPE_RAM;
        default:
            return TRINITY_MEMORY_TYPE_UNKNOWN;
    }
    return TRINITY_MEMORY_TYPE_UNKNOWN;
}
UINTN loadMemoryMap()
{
    print(u"---- Fetching Memory Map ----\n\r");
    uint64_t MEMMAP_PHYS = AllocateDataPage(0x1800000,0x400000);
    TRINITY_MEMORY_MAP_SIZE = (uint64_t*)MEMMAP_PHYS;
    TrinityVitalMemoryAddresses = (TRINITY_MEMORY_VITAL*)(MEMMAP_PHYS+sizeof(uint64_t));
    TrinityMemoryMap = (TRINITY_MEMORY_MAP_ENTRY*)(MEMMAP_PHYS+sizeof(uint64_t)+sizeof(TRINITY_MEMORY_VITAL));
    TrinityVitalMemoryAddresses->MEMMAP_PHYS       = MEMMAP_PHYS;
    TrinityVitalMemoryAddresses->STACK_PHYS        = AllocateDataPage(0x0400000,0x200000);
    TrinityVitalMemoryAddresses->PAGETABLE_PHYS    = AllocateDataPage(0x2400000,0x200000);
    TrinityVitalMemoryAddresses->PAGETABLE_PHYS_2  = AllocateDataPage(0x2600000,0x200000);
    TrinityVitalMemoryAddresses->MEMMAP_PHYS_2     = AllocateDataPage(0x2800000,0x200000);
    *TRINITY_MEMORY_MAP_SIZE = 0;
    //print(u"TRINITY_MEMORY_MAP_SIZE: ",*TRINITY_MEMORY_MAP_SIZE);
    uint64_t MemoryMapSize = 0;
    uint64_t EfiMemoryMap;
    UINTN EfiMemoryMapKey = 0;
    uint64_t EfiMemoryMapEntrySize = 0;
    uint32_t EfiMemoryDescriptorVersion = 0;
    //print(u"init buffer size: ",MemoryMapSize);
    sysTable->BootServices->GetMemoryMap(&MemoryMapSize,(EFI_MEMORY_DESCRIPTOR*)EfiMemoryMap,&EfiMemoryMapKey,&EfiMemoryMapEntrySize,&EfiMemoryDescriptorVersion);
    //print(u"new buffer size: ",MemoryMapSize);
    MemoryMapSize+=EfiMemoryMapEntrySize;
    EfiMemoryMap = (uint64_t)AllocatePool(MemoryMapSize);
    switch(sysTable->BootServices->GetMemoryMap(&MemoryMapSize,(EFI_MEMORY_DESCRIPTOR*)EfiMemoryMap,&EfiMemoryMapKey,&EfiMemoryMapEntrySize,&EfiMemoryDescriptorVersion))
    {
        case(EFI_SUCCESS):
            print(u"memory map fetch successful!\n\r");
            break;
        case(EFI_BUFFER_TOO_SMALL):
            print(u"error: EFI_BUFFER_TOO_SMALL\n\r");
            print(u"required buffer size: ",MemoryMapSize);
            return 0;
        case(EFI_INVALID_PARAMETER):
            print(u"error: EFI_INVALID_PARAMETER\n\r");
            return 0;
    }
    print(u"efi memory descriptor version: ",(uint64_t)EfiMemoryDescriptorVersion);
    uint64_t DescriptorCount = MemoryMapSize/EfiMemoryMapEntrySize;
    for(uint64_t i = 0;i<DescriptorCount;i++)
    {
        EFI_MEMORY_DESCRIPTOR* EfiDescriptor = (EFI_MEMORY_DESCRIPTOR*)EfiMemoryMap;
        //if(EfiDescriptor->VirtualStart <= 0x800000 && EfiDescriptor->VirtualStart+(EfiDescriptor->NumberOfPages*0x1000) >= 0xA00000)
        //{
        //    print(u"detected kernel range\n\r");
        //    print(u"virt start: ",EfiDescriptor->VirtualStart);
        //    print(u"phys start: ",EfiDescriptor->PhysicalStart);
        //    print(u"kernel code phys start: ",EfiDescriptor->PhysicalStart+(0x800000-EfiDescriptor->VirtualStart));
        //    uint64_t INIT_CODE_PHYS = EfiDescriptor->PhysicalStart+(0x800000-EfiDescriptor->VirtualStart);
        //    TrinityVitalMemoryAddresses->INIT_CODE_PHYS = INIT_CODE_PHYS;
        //    TrinityVitalMemoryAddresses->INIT_RW_PHYS  = INIT_CODE_PHYS+0x200000;
        //    TrinityVitalMemoryAddresses->INIT_RO_PHYS  = INIT_CODE_PHYS+0x400000;
        //    TrinityVitalMemoryAddresses->INIT_BSS_PHYS = INIT_CODE_PHYS+0x600000;
        //}
        print(u"Efi Phys Start: ",EfiDescriptor->PhysicalStart);
        //print(u"Efi Virt Start: ",EfiDescriptor->VirtualStart);
        switch(EfiDescriptor->Type)
        {
            case(EfiLoaderCode):
                print(u"Type: EfiLoaderCode\n\r");break;
            case(EfiLoaderData):
                print(u"Type: EfiLoaderData\n\r");break;
            case(EfiReservedMemoryType):
                print(u"Type: EfiReservedMemoryType\n\r");break;
            case(EfiRuntimeServicesCode):
                print(u"Type: EfiRuntimeServicesCode\n\r");break;
            case(EfiRuntimeServicesData):
                print(u"Type: EfiRuntimeServicesData\n\r");break;
            case(EfiACPIMemoryNVS):
                print(u"Type: EfiACPIMemoryNVS\n\r");break;
            case(EfiPalCode):
                print(u"Type: EfiPalCode\n\r");break;
            case(EfiMemoryMappedIO):
                print(u"Type: EfiMemoryMappedIO\n\r");break;
            case(EfiMemoryMappedIOPortSpace):
                print(u"Type: EfiMemoryMappedIOPortSpace\n\r");break;
            case(EfiBootServicesCode):
                print(u"Type: EfiBootServicesCode\n\r");break;
            case(EfiBootServicesData):
                print(u"Type: EfiBootServicesData\n\r");break;
            case(EfiConventionalMemory):
                print(u"Type: EfiConventionalMemory\n\r");break;
            case(EfiPersistentMemory):
                print(u"Type: EfiPersistentMemory\n\r");break;
            default:
                print(u"Type: ",(uint64_t)EfiDescriptor->Type);
        }
        {
            uint64_t TrinityPageCount = (EfiDescriptor->NumberOfPages*0x1000)/TRINITY_PAGE_SIZE;
            if((EfiDescriptor->NumberOfPages*0x1000)%TRINITY_PAGE_SIZE != 0)
                TrinityPageCount++;
            print(u"TrinityPageCount: ",TrinityPageCount);
            {
                uint64_t size = EfiDescriptor->NumberOfPages*0x1000;
                uint64_t Kibibytes = size/0x1000;
                uint64_t Mebibytes = size/0x00100000;
                uint64_t Gibibytes = size/0x40000000;
                if(Gibibytes > 0)
                    print(u"size (GiB): ",Gibibytes);
                else if(Mebibytes > 0)
                    print(u"size (MiB): ",Mebibytes);
                else
                    print(u"size (KiB): ",Kibibytes);
                if(Gibibytes > 0)
                {
                    //do not map pages
                    goto skipRegionMapping;
                }
            }
            for(uint64_t i = 0;i<TrinityPageCount;i++)
            {
                //print(u"TRINITY_MEMORY_MAP_SIZE: ",*TRINITY_MEMORY_MAP_SIZE);
                uint64_t TrinityPhysicalStartPage = ((EfiDescriptor->PhysicalStart/TRINITY_PAGE_SIZE)*TRINITY_PAGE_SIZE)+(i*TRINITY_PAGE_SIZE);
                TRINITY_MEMORY_MAP_ENTRY* mapEntry = findTRINITY_MEMORY_MAP_ENTRY(TrinityPhysicalStartPage);
                if(mapEntry != nullptr)
                {
                    switch(mapEntry->Type)
                    {
                        case(TRINITY_MEMORY_TYPE_RAM):
                        {
                            TRINITY_MEMORY_TYPE et = EfiToTrinityMemoryType(EfiDescriptor->Type);
                            mapEntry->Type = et;
                            break;
                        }
                        case(TRINITY_MEMORY_TYPE_MMIO):
                        {
                            TRINITY_MEMORY_TYPE et = EfiToTrinityMemoryType(EfiDescriptor->Type);
                            if(et == TRINITY_MEMORY_TYPE_RAM);
                            else mapEntry->Type = et;
                            break;
                        }
                        case(TRINITY_MEMORY_TYPE_PRESERVE):
                        {
                            TRINITY_MEMORY_TYPE et = EfiToTrinityMemoryType(EfiDescriptor->Type);
                            if(et == TRINITY_MEMORY_TYPE_RAM);
                            else if(et == TRINITY_MEMORY_TYPE_MMIO);
                            else if(et == TRINITY_MEMORY_TYPE_ACPI_RECLAIM);
                            else mapEntry->Type = et;
                            break;
                        }
                        case(TRINITY_MEMORY_TYPE_ACPI_RECLAIM):
                        {
                            TRINITY_MEMORY_TYPE et = EfiToTrinityMemoryType(EfiDescriptor->Type);
                            if(et == TRINITY_MEMORY_TYPE_RAM);
                            else if(et == TRINITY_MEMORY_TYPE_MMIO);
                            else mapEntry->Type = et;
                            break;
                        }
                        case(TRINITY_MEMORY_TYPE_BORKED):
                        case(TRINITY_MEMORY_TYPE_UNACCEPTED):
                        case(TRINITY_MEMORY_TYPE_UNKNOWN):
                        {
                            break;
                        }
                    }
                }
                else
                {
                    TRINITY_MEMORY_MAP_ENTRY* mapEntry = (TRINITY_MEMORY_MAP_ENTRY*)((uint64_t)TrinityMemoryMap+(sizeof(TRINITY_MEMORY_MAP_ENTRY)*(*TRINITY_MEMORY_MAP_SIZE)));
                    (*TRINITY_MEMORY_MAP_SIZE)++;
                    mapEntry->Type = EfiToTrinityMemoryType(EfiDescriptor->Type);
                    mapEntry->MemoryControllerAddress = TrinityPhysicalStartPage;
                    mapEntry->Attributes = 0;
                }
            }
        }
        skipRegionMapping:;
        EfiMemoryMap+=EfiMemoryMapEntrySize;
    }
    //
    // print TRINITY memory map for verification
    //
    for(uint64_t i = 0;i<*TRINITY_MEMORY_MAP_SIZE;i++)
    {
        if(TrinityMemoryMap[i].Type == TRINITY_MEMORY_TYPE_RAM)
        {
            TrinityVitalMemoryAddresses->RAM_SIZE+=0x200000;
        }
        //print(u"---- TRINITY MEMORY MAP ENTRY ----\n\r");
        //switch(TrinityMemoryMap[i].Type)
        //{
        //    case(TRINITY_MEMORY_TYPE_MMIO):
        //        print(u"Type: TRINITY_MEMORY_TYPE_MMIO\n\r");
        //        break;
        //    case(TRINITY_MEMORY_TYPE_PRESERVE):
        //        print(u"Type: TRINITY_MEMORY_TYPE_PRESERVE\n\r");
        //        break;
        //    case(TRINITY_MEMORY_TYPE_RAM):
        //        print(u"Type: TRINITY_MEMORY_TYPE_RAM\n\r");
        //        break;
        //    case(TRINITY_MEMORY_TYPE_BORKED):
        //        print(u"Type: TRINITY_MEMORY_TYPE_BORKED\n\r");
        //        break;
        //    case(TRINITY_MEMORY_TYPE_ACPI_RECLAIM):
        //        print(u"Type: TRINITY_MEMORY_TYPE_ACPI_RECLAIM\n\r");
        //        break;
        //    case(TRINITY_MEMORY_TYPE_UNACCEPTED):
        //        print(u"Type: TRINITY_MEMORY_TYPE_UNACCEPTED\n\r");
        //        break;
        //    case(TRINITY_MEMORY_TYPE_UNKNOWN):
        //        print(u"Type: TRINITY_MEMORY_TYPE_UNKNOWN\n\r");
        //        break;
        //    default:
        //        print(u"Type: ",TrinityMemoryMap[i].Type);
        //        break;
        //}
        //print(u"Address: ",TrinityMemoryMap[i].MemoryControllerAddress);
    }
    //if(findTRINITY_MEMORY_MAP_ENTRY(0x800000)->Type != TRINITY_MEMORY_TYPE_RAM)
    //{
    //    TrinityVitalMemoryAddresses->NeedToMoveInit = 1;
    //}
    print(u"usable ram: ",TrinityVitalMemoryAddresses->RAM_SIZE);
    return EfiMemoryMapKey;
}

#include <PAGING.hxx>
#include <bits>
extern "C" uint64_t getCR3();
extern "C" uint64_t getCR4();
void print_memmap();
PCIeEntryInfo_T* PCIeEntryInfo;
extern "C" uint64_t __sys_helloworld(EFI_HANDLE image,EFI_SYSTEM_TABLE* systemTable)
{
    sysTable = systemTable;
    //UINT16* msg = (UINT16*)u"Hello World!\n\r";
    systemTable->ConOut->ClearScreen(systemTable->ConOut);
    //systemTable->ConOut->OutputString(systemTable->ConOut, msg);
    print64(MC64("TRINTEST"));
    print(u"\n\r");

	PCIeEntryInfo = (PCIeEntryInfo_T*)AllocateDataPage(0x200000,0x200000);

	//Load Memory Map
    UINTN mapKey = loadMemoryMap();
    TrinityVitalMemoryAddresses->PCIE_PHYS = (uint64_t)PCIeEntryInfo;
	
    listConfigTable();
    TrinityVitalMemoryAddresses->RSDT_PHYS = readACPI();

    //load INIT from disk
    Volume = GetVolume(image);
    loadKernelINIT(image,mapKey);
    return 0;
}

EFI_STATUS __main(EFI_HANDLE imageHandle,EFI_SYSTEM_TABLE* systemTable)
{
    sysTable = systemTable;
    UINT16* msg = (UINT16*)u"Hello World!\n\r";

    systemTable->ConOut->ClearScreen(systemTable->ConOut);
	systemTable->ConOut->OutputString(systemTable->ConOut, msg);

    print64(MC64("TRINTEST"));
    print(u"\n\r");
    listConfigTable();

    readACPI();

    while(1);
    return EFI_SUCCESS;//we could return to the firmware but we won't, just hang up instead
}