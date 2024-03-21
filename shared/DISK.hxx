/**
Created Date: Thursday February 8th 2024
Author: Lilith (definitelynotagirl115169@gmail.com)
-----
Last Modified: Thursday February 29th 2024 5:18:25 am
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

#include "stdint.hxx"
#include "PCIe.hxx"

//struct Disk
//{
//    uint64_t DiskID;
//    uint64_t TotalSize;
//    PCIE_DEVICE_CONFIG* PCIe;
//};

namespace Disk
{
    enum class ReadReturn {
        OK,
        OUT_OF_BOUNDS,
        NO_SUCH_DEVICE,
        FAILURE,
        TIMEOUT,
		oddLength,
    };
};
