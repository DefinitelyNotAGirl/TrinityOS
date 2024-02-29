/**
 * Created Date: Friday February 17th 2023
 * Author: DefinitelyNotAGirl@github
 * -----
 * Last Modified: Friday February 17th 2023 1:39:09 am
 * Modified By: DefinitelyNotAGirl@github (definitelynotagirl115199@gmail.com)
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
#include <efi.h>
#include <efilib.h>

#ifndef GEOS_FSIZE_GFS0
    #error FSIZE_GFS0 not defined!
#endif

#ifndef GEOS_FSIZE_ACPI
    #error FSIZE_ACPI not defined!
#endif

#ifndef GEOS_FSIZE_AHCI
    #error FSIZE_AHCI not defined!
#endif

#ifndef GEOS_FSIZE_IDE 
    #error FSIZE_IDE not defined!
#endif

#ifndef GEOS_FSIZE_SATA
    #error FSIZE_SATA not defined!
#endif

EFI_FILE_HANDLE getVolume(EFI_HANDLE image)
{
    EFI_LOADED_IMAGE *loaded_image = NULL;                  /* image interface */
    EFI_GUID lipGuid = EFI_LOADED_IMAGE_PROTOCOL_GUID;      /* image interface GUID */
    EFI_FILE_IO_INTERFACE *IOVolume;                        /* file system interface */
    EFI_GUID fsGuid = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID; /* file system interface GUID */
    EFI_FILE_HANDLE Volume;                                 /* the volume's interface */

    /* get the loaded image protocol interface for our "image" */
    uefi_call_wrapper(BS->HandleProtocol, 3, image, &lipGuid, (void **) &loaded_image);
    /* get the volume handle */
    uefi_call_wrapper(BS->HandleProtocol, 3, loaded_image->DeviceHandle, &fsGuid, (VOID*)&IOVolume);
    uefi_call_wrapper(IOVolume->OpenVolume, 2, IOVolume, &Volume);
    return Volume;
}

UINT8* readFile(CHAR16* filename,EFI_FILE_HANDLE Volume,UINT64 filesize,UINT8* Buffer)
{
    Print(L"loading file: ");
    Print(filename);
    Print(L"\n");
    Print(L"debug 3\n");
    EFI_FILE_HANDLE FileHandle;

    /* open the file */
    uefi_call_wrapper(Volume->Open, 5, Volume, &FileHandle, filename, EFI_FILE_MODE_READ, EFI_FILE_READ_ONLY | EFI_FILE_HIDDEN | EFI_FILE_SYSTEM);
    Print(L"debug 4\n");

    /* read from the file */
    uefi_call_wrapper(FileHandle->Read, 3, &FileHandle, &filesize, Buffer);
    Print(L"debug 6\n");

    /* close the file */
    uefi_call_wrapper(FileHandle->Close, 1, &FileHandle);
    Print(L"debug 7\n");
    return Buffer;
}

UINT8 BUFFER_GFS0[GEOS_FSIZE_GFS0] = {0x00};
UINT8 BUFFER_ACPI[GEOS_FSIZE_ACPI] = {0x00};
UINT8 BUFFER_AHCI[GEOS_FSIZE_AHCI] = {0x00};
UINT8 BUFFER_IDE [GEOS_FSIZE_IDE ] = {0x00};
UINT8 BUFFER_SATA[GEOS_FSIZE_SATA] = {0x00};

EFI_STATUS EFIAPI efi_main (EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
    InitializeLib(ImageHandle, SystemTable);
    Print(L"Hello world!\n");

    Print(L"debug 1\n");
    EFI_FILE_HANDLE Volume = getVolume(ImageHandle);

    Print(L"debug 2\n");
    UINT8* gfs0_dll = readFile(L"/GEOS/GFS0.fs.dll"  ,Volume,GEOS_FSIZE_GFS0,BUFFER_GFS0);
    UINT8* ACPI_dll = readFile(L"/GEOS/ACPI.dll"     ,Volume,GEOS_FSIZE_ACPI,BUFFER_ACPI);
    UINT8* AHCI_dll = readFile(L"/GEOS/AHCI.dll"     ,Volume,GEOS_FSIZE_AHCI,BUFFER_AHCI);
    UINT8* IDE_dll  = readFile(L"/GEOS/IDE.dll"      ,Volume,GEOS_FSIZE_IDE ,BUFFER_IDE );
    UINT8* SATA_dll = readFile(L"/GEOS/SATA.dll"     ,Volume,GEOS_FSIZE_SATA,BUFFER_SATA);
    //UINT8* KERNEL   = readFile(L"/GEOS/KERNEL",Volume);

    Print(L"files loaded to memory\n");

    while(1);
}
