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

#define DEBUG_EXIT sysDBGExit(0xDEBAC,__LINE__);

#define ERROR_R15 0xEEEEEEEEEEEEEEEE

#include <stdint.hxx>
#include <APP_INFO.hxx>
#include <PAGING.hxx>
#include <PCIe.hxx>

extern PROCESS_INFO* Kernel;

extern "C" void     outdoubleword(uint16_t port,uint32_t value);
extern "C" uint32_t indoubleword (uint16_t port);
extern "C" void     outword(uint16_t port,uint16_t value);
extern "C" uint16_t inword (uint16_t port);
extern "C" void     outbyte(uint16_t port,uint8_t value);
extern "C" uint8_t  inbyte (uint16_t port);

extern "C" void sysDBGExit(
    uint64_t r15 = 0, 
    uint64_t r14 = 0, 
    uint64_t r13 = 0, 
    uint64_t r12 = 0,
    uint64_t r11 = 0,
    uint64_t r10 = 0
);
extern "C" void sysDBGint(
    uint64_t rdi = 0, 
    uint64_t rsi = 0, 
    uint64_t rdx = 0, 
    uint64_t rcx = 0,
    uint64_t r8 = 0,
    uint64_t r9 = 0
);
extern "C" void sysEXIT_SUCCESS();

void* memset(void* target, int c, uint64_t n);

//? ██████  ███████ ███████  ██████ ██████  ██ ██████  ████████  ██████  ██████      ████████  █████  ██████  ██      ███████ ███████
//? ██   ██ ██      ██      ██      ██   ██ ██ ██   ██    ██    ██    ██ ██   ██        ██    ██   ██ ██   ██ ██      ██      ██
//? ██   ██ █████   ███████ ██      ██████  ██ ██████     ██    ██    ██ ██████         ██    ███████ ██████  ██      █████   ███████
//? ██   ██ ██           ██ ██      ██   ██ ██ ██         ██    ██    ██ ██   ██        ██    ██   ██ ██   ██ ██      ██           ██
//? ██████  ███████ ███████  ██████ ██   ██ ██ ██         ██     ██████  ██   ██        ██    ██   ██ ██████  ███████ ███████ ███████
void setupGDT();
void setupIDT();

//? ██████   █████   ██████  ██ ███    ██  ██████
//? ██   ██ ██   ██ ██       ██ ████   ██ ██
//? ██████  ███████ ██   ███ ██ ██ ██  ██ ██   ███
//? ██      ██   ██ ██    ██ ██ ██  ██ ██ ██    ██
//? ██      ██   ██  ██████  ██ ██   ████  ██████
#define ERROR_SETPAGE 0x01
extern TRINITY_MEMORY_VITAL* VitalMemoryValues;
extern TrinitySetPageReturn lastSetPageError;
uint64_t getPhysicalAddress(uint64_t virtualAddress,PROCESS_INFO* process);
uint64_t getVirtualAddress(uint64_t physicalAddress, PROCESS_INFO* process);
void setPhysicalPageUsed(uint64_t address);
void initiatePageTable(PROCESS_INFO* process);
TrinitySetPageReturn setPage(TrinityPageType mode,uint64_t physicalAddress,uint64_t virtualAddress,PROCESS_INFO* process);

//* ██████   ██████ ██     ███████ ██   ██ ██████  ██████  ███████ ███████ ███████
//* ██   ██ ██      ██     ██       ██ ██  ██   ██ ██   ██ ██      ██      ██
//* ██████  ██      ██     █████     ███   ██████  ██████  █████   ███████ ███████
//* ██      ██      ██     ██       ██ ██  ██      ██   ██ ██           ██      ██
//* ██       ██████ ██     ███████ ██   ██ ██      ██   ██ ███████ ███████ ███████
extern PCIeEntryInfo_T* PCIeEntryInfo;

//+ ██       ██████   █████  ██████      ███    ███  ██████  ██████  ███████     ███    ███  ██████  ██████  ██    ██ ██      ███████ ███████
//+ ██      ██    ██ ██   ██ ██   ██     ████  ████ ██    ██ ██   ██ ██          ████  ████ ██    ██ ██   ██ ██    ██ ██      ██      ██
//+ ██      ██    ██ ███████ ██   ██     ██ ████ ██ ██    ██ ██████  █████       ██ ████ ██ ██    ██ ██   ██ ██    ██ ██      █████   ███████
//+ ██      ██    ██ ██   ██ ██   ██     ██  ██  ██ ██    ██ ██   ██ ██          ██  ██  ██ ██    ██ ██   ██ ██    ██ ██      ██           ██
//+ ███████  ██████  ██   ██ ██████      ██      ██  ██████  ██   ██ ███████     ██      ██  ██████  ██████   ██████  ███████ ███████ ███████
extern uint64_t mmioAddress;
void FindBootDisk();

//- ██████  ██ ███████ ██   ██
//- ██   ██ ██ ██      ██  ██
//- ██   ██ ██ ███████ █████
//- ██   ██ ██      ██ ██  ██
//- ██████  ██ ███████ ██   ██
#define ERROR_DISK_READ 0x02

//- ███████  █████  ████████  █████
//- ██      ██   ██    ██    ██   ██
//- ███████ ███████    ██    ███████
//-      ██ ██   ██    ██    ██   ██
//- ███████ ██   ██    ██    ██   ██
namespace AHCI
{
    void checkController(PCIE_DEVICE_CONFIG* controller);
}

//. ██       ██████   ██████
//. ██      ██    ██ ██
//. ██      ██    ██ ██   ███
//. ██      ██    ██ ██    ██
//. ███████  ██████   ██████
extern "C" void TrinityLogPrintHex(uint64_t n);
#define TrinityDebugHex(var) TrinityLog::print(#var": ");TrinityLog::printHex((uint64_t)var);TrinityLog::print("\n")
namespace TrinityLog
{
	void init(PCIE_DEVICE_CONFIG* config);

	void disassemble(uint64_t address);

	void print(char*);
	void print(const char* data);
	void printHex(uint64_t n);
}

//+ ██    ██ ████████ ██ ██      ██ ████████ ██    ██
//+ ██    ██    ██    ██ ██      ██    ██     ██  ██
//+ ██    ██    ██    ██ ██      ██    ██      ████
//+ ██    ██    ██    ██ ██      ██    ██       ██
//+  ██████     ██    ██ ███████ ██    ██       ██
uint64_t strlen(char* str);

//?  █████   ██████ ██████  ██
//? ██   ██ ██      ██   ██ ██
//? ███████ ██      ██████  ██
//? ██   ██ ██      ██      ██
//? ██   ██  ██████ ██      ██
#include <ACPI.hxx>
namespace ACPI
{
	void Init(RSDT* rsdt);
	void InitAPICs();
}

//?  █████  ██████  ██  ██████
//? ██   ██ ██   ██ ██ ██
//? ███████ ██████  ██ ██
//? ██   ██ ██      ██ ██
//? ██   ██ ██      ██  ██████
extern "C" uint64_t GetLocalProcessorID();

//, ███████ ██ ██      ███████     ███████ ██    ██ ███████ ████████ ███████ ███    ███
//, ██      ██ ██      ██          ██       ██  ██  ██         ██    ██      ████  ████
//, █████   ██ ██      █████       ███████   ████   ███████    ██    █████   ██ ████ ██
//, ██      ██ ██      ██               ██    ██         ██    ██    ██      ██  ██  ██
//, ██      ██ ███████ ███████     ███████    ██    ███████    ██    ███████ ██      ██
bool CheckFilesystem(uint64_t SectorSize);
