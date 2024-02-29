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
#pragma once

#include <EFIConfig.hxx>
#include <Uefi.h>
#include <stdint>

#define NULL 0

#define MC64(constant) *((uint64_t*)((char*)constant))

extern "C" void stackPush(uint64_t);
extern "C" uint64_t stackPop();
extern "C" uint64_t getStackPointer();
extern "C" void setStackPointer(uint64_t);
extern "C" void tripleFault(uint64_t errorCode);
extern "C" uint64_t getRIP();
extern "C" uint64_t readP32(uint64_t addr);

extern EFI_GUID GUID_ACPI;
extern EFI_GUID GUID_SAL_SYSTEM;
extern EFI_GUID GUID_SMBIOS;
extern EFI_GUID GUID_SMBIOS3;
extern EFI_GUID GUID_MPS;
extern EFI_GUID GUID_PROPERTIES_TABLE;

extern efiConfig econf;
extern uint64_t entryRIP;

extern "C" void print64(uint64_t value);
extern "C" void print32(uint32_t value);
extern "C" void print64r(uint64_t value);
extern "C" void print32r(uint32_t value);
extern "C" void printHex64(uint64_t value);
void print(const char16_t* msg,uint64_t n);

char* strreverse(char* str);
void print(uint16_t* msg);
uint64_t print(const char16_t* msg);
uint64_t malloc(uint64_t size);
void readACPI();
