/**
Created Date: Sunday March 10th 2024
Author: Lilith (definitelynotagirl115169@gmail.com)
-----
Last Modified: Sunday March 10th 2024 11:59:54 pm
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
#pragma once

#include "FixedSizeList.hxx"

//+  ██████ ██████  ██    ██
//+ ██      ██   ██ ██    ██
//+ ██      ██████  ██    ██
//+ ██      ██      ██    ██
//+  ██████ ██       ██████
struct CPU {
	union {
		struct {
		public:
			uint64_t ID;
			uint64_t ApicID;
			uint64_t TypeID;
			uint64_t Flags;
		};
		uint8_t reservedSpace[128];//- size: 128 Bytes
	};
};
namespace CPUFlags {
	constexpr uint64_t Enabled = 1<<0;
	constexpr uint64_t Active  = 1<<1;
}

//+  ██████ ██████  ██    ██     ██ ███    ██ ███████  ██████
//+ ██      ██   ██ ██    ██     ██ ████   ██ ██      ██    ██
//+ ██      ██████  ██    ██     ██ ██ ██  ██ █████   ██    ██
//+ ██      ██      ██    ██     ██ ██  ██ ██ ██      ██    ██
//+  ██████ ██       ██████      ██ ██   ████ ██       ██████
struct CPU_INFO {
	/* 0x000000 */FixedList<CPU,4096> CPUs; //- size: 0x80000, 512KiB
};
extern CPU_INFO* CPUInfo;
