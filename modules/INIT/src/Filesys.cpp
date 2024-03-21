/**
Created Date: Friday March 15th 2024
Author: Lilith (definitelynotagirl115169@gmail.com)
-----
Last Modified: Friday March 15th 2024 1:55:44 pm
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

#include <INIT.h>
#include <GPT.hxx>
#include <Log.hxx>
#include <MemoryConstants.hxx>
#include <print.hxx>

bool CheckFilesystem(uint64_t SectorSize)
{
	TrinityLog::print("["ANSI_BLUE"INFO"ANSI_RESET"]Check filesystem...\n");
	if(SectorSize == 512)
	{
		uint8_t sig[9];
		sig[8] = 0;
		//
		//
		//
		GPT::Primary<512>* gpt = (GPT::Primary<512>*)MEM_ADDR_DISK_READ_INIT;
		*((uint64_t*)&sig[0]) = gpt->lba1.Signature;
		TrinityLog::print("Signature: ");
		TrinityLog::print((char*)sig);
		TrinityLog::print("\n");
		TrinityDebugHex(gpt->lba1.Signature);
	}
	else
	{
		TrinityLog::print("["ANSI_RED"ERROR"ANSI_RESET"]Invalid sector size!\n");
		TrinityDebugHex(SectorSize);
	}
	return true;
}
