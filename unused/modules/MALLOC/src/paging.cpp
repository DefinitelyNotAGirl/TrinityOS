/**
 * Created Date: Wednesday March 22nd 2023
 * Author: DefinitelyNotAGirl@github
 * -----
 * Last Modified: Tuesday April 25th 2023 10:46:08 am
 * Modified By: DefinitelyNotAGirl@github (definitelynotagirl115169@gmail.com)
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
#include <stdint>
#include <bits>
#include <micro>

void writePDE(
        uint64_t physBaseAddr,
        uint64_t entry_addr,
        //flags
        uint8_t present,
        uint8_t readwrite, 
        uint8_t supervisoronly,
        uint8_t pagewritetrough,
        uint8_t pagecachedisable,
        uint8_t PageSize,
        uint8_t global,
        uint8_t PAT,
        uint8_t executable)
{
    uint64_t entry = physBaseAddr;

    SCBIT_00(entry,present);
    SCBIT_01(entry,readwrite);
    SCBIT_02(entry,!supervisoronly);
    SCBIT_03(entry,pagewritetrough);
    SCBIT_04(entry,pagecachedisable);
    SCBIT_07(entry,PageSize);
    SCBIT_08(entry,global);
    SCBIT_12(entry,PAT);
    SCBIT_63(entry,!executable);

    //clear ignored (available) bits
    CLEARBIT_52(entry);
    CLEARBIT_53(entry);
    CLEARBIT_54(entry);
    CLEARBIT_55(entry);
    CLEARBIT_56(entry);
    CLEARBIT_57(entry);
    CLEARBIT_58(entry);
    CLEARBIT_59(entry);
    CLEARBIT_60(entry);
    CLEARBIT_61(entry);
    CLEARBIT_62(entry);

    //clear reserved bits
    CLEARBIT_13(entry);
    CLEARBIT_14(entry);
    CLEARBIT_15(entry);
    CLEARBIT_16(entry);
    CLEARBIT_17(entry);
    CLEARBIT_18(entry);
    CLEARBIT_19(entry);
    CLEARBIT_20(entry);

    write64(entry_addr,entry);
}

void writePDPE(
        uint64_t PD_ADDR,//page directory address
        uint64_t entry_addr,
        //flags
        uint8_t present,
        uint8_t readwrite, 
        uint8_t supervisoronly,
        uint8_t pagewritetrough,
        uint8_t pagecachedisable,
        uint8_t PageSize,
        uint8_t global,
        uint8_t executable)
{
    uint64_t entry = PD_ADDR;

    SCBIT_00(entry,present);
    SCBIT_01(entry,readwrite);
    SCBIT_02(entry,!supervisoronly);
    SCBIT_03(entry,pagewritetrough);
    SCBIT_04(entry,pagecachedisable);
    SCBIT_07(entry,PageSize);
    SCBIT_08(entry,global);
    SCBIT_63(entry,!executable);

    //clear ignored bits
    CLEARBIT_06(entry);
    CLEARBIT_07(entry);
    CLEARBIT_08(entry);

    write64(entry_addr,entry);
}

void writePML4E(
        uint64_t PDP_ADDR,//page directory address
        uint64_t entry_addr,
        //flags
        uint8_t present,
        uint8_t readwrite, 
        uint8_t supervisoronly,
        uint8_t pagewritetrough,
        uint8_t pagecachedisable,
        uint8_t PageSize,
        uint8_t global,
        uint8_t executable)
{
    uint64_t entry = PDP_ADDR;
    
    SCBIT_00(entry,present);
    SCBIT_01(entry,readwrite);
    SCBIT_02(entry,!supervisoronly);
    SCBIT_03(entry,pagewritetrough);
    SCBIT_04(entry,pagecachedisable);
    SCBIT_07(entry,PageSize);
    SCBIT_08(entry,global);
    SCBIT_63(entry,!executable);

    //clear ignored bits
    CLEARBIT_06(entry);

    //clear reserved bits
    CLEARBIT_07(entry);
    CLEARBIT_08(entry);

    write64(entry_addr,entry);
}
