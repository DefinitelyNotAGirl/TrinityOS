/**
Created Date: Friday March 8th 2024
Author: Lilith (definitelynotagirl115169@gmail.com)
-----
Last Modified: Friday March 8th 2024 3:14:53 pm
Modified By: Lilith (definitelynotagirl115169@gmail.com)
-----
Copyright (c) 2024 Lilith Nitschke-Höfer (lilithnitschkehoefer@gmail.com)

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

#include <PCIe.hxx>
#include <MiscStructs.hxx>
#include <INIT.h>
#include <print.hxx>
#include <Log.hxx>

namespace TrinityLog
{
	void printChar(char c) {
		char str[2];
		str[0] = c;
		str[1] = 0;
		print(str);
	}
	void printDouble(double d) {
	}
	void print(const char* data){print((char*)data);}

	void printHex(uint64_t n){TrinityLogPrintHex(n);}

	void disassemble(uint64_t address)
	{
		*((uint64_t*)(DebugData->TrinityLogBar0+96))= address;
		*((uint64_t*)(DebugData->TrinityLogBar0+0)) = (1<<0) | (1<<4);
		while(*((uint64_t*)(DebugData->TrinityLogBar0+0)) != 0){};//- wait for hardware to clear the status register
	}

	void print(char* data)
	{
		uint64_t len = strlen(data);
		//+ copy data
		char* outdata = (char*)(DebugData->TrinityLogBar0+96);
		for(uint64_t i = 0;i<len;i++)
			outdata[i] = data[i];
		outdata[len] = 0;
		//+ send command
		*((uint64_t*)(DebugData->TrinityLogBar0+0)) = (1<<0) | (1<<1);
		while(*((uint64_t*)(DebugData->TrinityLogBar0+0)) != 0){};//wait for hardware to clear the status register
	}

	void init(PCIE_DEVICE_CONFIG* config)
	{
		PCIE_DEVICE_TRINITY_LOG* device = (PCIE_DEVICE_TRINITY_LOG*)config;
		DebugData->Flags |= (1<<0);// set bit 0, use trinity log
		uint64_t BAR0 = (uint64_t)device->Header.BAR0;
		uint64_t virt = getVirtualAddress(BAR0,Kernel);
	    if(virt == UINT64_T_MAX)
	    {
	        if(setPage(TrinityPageType::MemoryMappedIO,BAR0,mmioAddress,Kernel) != TrinitySetPageReturn::OK)
	            sysDBGExit(ERROR_R15,ERROR_SETPAGE);
	        virt = (mmioAddress)+(BAR0%TRINITY_PAGE_SIZE);
	        mmioAddress+=TRINITY_PAGE_SIZE;
	    }
		DebugData->TrinityLogBar0 = virt;
		//*
		//* send init command
		//*
		*((uint64_t*)(DebugData->TrinityLogBar0+0)) = (1<<0) | (1<<3);
		//+
		//+ update print streams
		//+
		info = printStream(
			&print,
			&print,
			&printChar,
			&printHex,
			&printDouble,
			ANSI_BLUE"[INFO]"ANSI_RESET
		);
		warn = printStream(
			&print,
			&print,
			&printChar,
			&printHex,
			&printDouble,
			ANSI_GREEN"[WARNING]"ANSI_RESET
		);
		error = printStream(
			&print,
			&print,
			&printChar,
			&printHex,
			&printDouble,
			ANSI_RED"[ERROR]"ANSI_RESET
		);
		debug = printStream(
			&print,
			&print,
			&printChar,
			&printHex,
			&printDouble,
			ANSI_BLUE"[DEBUG]"ANSI_RESET
		);
	}
}