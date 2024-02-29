/**
 * Created Date: Saturday November 12th 2022
 * Author: DefinitelyNotAGirl@github
 * -----
 * Last Modified: Saturday November 12th 2022 5:28:22 pm
 * Modified By: DefinitelyNotAGirl@github (definitelynotagirl115199@gmail.com)
 * -----
 * Copyright (c) 2022 DefinitelyNotAGirl@github
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
#include "../master.h"

namespace paging
{
    /*
        NOTE:   40 bits should in theory cover all physical memory (for the time being anyway) 
                40 bits should cover about 1PiB of memory
    */

    bool RUNTIME_ENABLE_PML5 = false;

    class PDE
    {
    public:
        uint8_t AVL = 0;
        bool PAT = 0;
        bool PS  = 1;
        bool G   = 0;
        bool D   = 0;
        bool A   = 0;
        bool PCD = 0;
        bool PWT = 0;
        bool US  = 0;
        bool RW  = 0;
        bool P   = 0;
        bool NX  = 0;

        ptr64 PhysPageBaseAddr = 0x0000;//40 bits

        uint64_t getData();
        void loadFromAddr(ptr64 addr);
    };

    class PDPE
    {
    public:
        uint8_t AVL  = 0;
        bool IGN  = 0;
        bool IGN_ = 0;
        bool A    = 0;
        bool PCD  = 0;
        bool PWT  = 0;
        bool US   = 0;
        bool RW   = 0;
        bool P    = 0;
        bool NX   = 0;

        ptr64 ADDR_PD = 0x0000;//40 bits

        uint64_t getData();
        void loadFromAddr(ptr64 addr);
    };

    class PML4E
    {
    public:
        uint8_t AVL  = 0;
        bool IGN  = 0;
        bool MBZ  = 0;
        bool MBZ_ = 0;
        bool A    = 0;
        bool PCD  = 0;
        bool PWT  = 0;
        bool US   = 0;
        bool RW   = 0;
        bool P    = 0;
        bool NX   = 0;

        ptr64 ADDR_PDPT = 0x0000;//40 bits

        uint64_t getData();
        void loadFromAddr(ptr64 addr);
    };

    class PML5E
    {
    public:
        uint8_t AVL = 0;
        bool IGN  = 0;
        bool MBZ  = 0;
        bool MBZ_ = 0;
        bool A    = 0;
        bool PCD  = 0;
        bool PWT  = 0;
        bool US   = 0;
        bool RW   = 0;
        bool P    = 0;
        bool NX   = 0;

        ptr64 ADDR_PML4T = 0x0000;//40 bits

        uint64_t getData();
        void loadFromAddr(ptr64 addr);
    };

    #ifdef ENABLE_PML5
        PDE   * masterPageTableL2 ;
        PDPE  * masterPageTableL3 ;
        PML4E * masterPageTableL4 ;
        PML5E * masterPageTable   ;
        #define PAGING_LVL 5
    #else
        PDE   * masterPageTableL2 ;
        PDPE  * masterPageTableL3 ;
        PML4E * masterPageTable   ;
        #define PAGING_LVL 4
    #endif

    void createMasterPageTable();

    bool isPML5Capable();
}
