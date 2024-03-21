/**
Created Date: Friday March 8th 2024
Author: Lilith (definitelynotagirl115169@gmail.com)
-----
Last Modified: Friday March 8th 2024 4:08:30 pm
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

//- ██████  ███████ ██████  ██    ██  ██████      ██████   █████  ████████  █████
//- ██   ██ ██      ██   ██ ██    ██ ██           ██   ██ ██   ██    ██    ██   ██
//- ██   ██ █████   ██████  ██    ██ ██   ███     ██   ██ ███████    ██    ███████
//- ██   ██ ██      ██   ██ ██    ██ ██    ██     ██   ██ ██   ██    ██    ██   ██
//- ██████  ███████ ██████   ██████   ██████      ██████  ██   ██    ██    ██   ██
//- should be located at 0x600000
struct DebugData_T{
	uint64_t Flags;//0: use trinity log; 1:63 reserved, MBZ
	volatile uint64_t TrinityLogBar0;
};extern DebugData_T* DebugData;