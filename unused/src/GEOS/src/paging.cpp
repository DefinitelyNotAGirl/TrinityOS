/**
 * Created Date: Saturday November 12th 2022
 * Author: DefinitelyNotAGirl@github
 * -----
 * Last Modified: Saturday November 12th 2022 5:29:18 pm
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

void setupPaging()
{
    lterm->write('\n');
    printINFO("setting up paging...\n");

    printValue(controlRegisters::cr0::PG ,"paging enabled"                     );
    lterm->write("\n");
    printValue(controlRegisters::cr4::PSE,"Page Size Extensions enabled"       );
    lterm->write("\n");
    printValue(controlRegisters::cr4::PAE,"Physical Address Extensions enabled");
    lterm->write("\n");
    printValue(paging::isPML5Capable(),"PML5 available");
    lterm->write("\n");

    //TODO: create page table
    //TODO: load page table

    return lterm->write('\n');
}

namespace paging
{
    bool isPML5Capable()
    {
        __cpuid__(0x7);
        uint64_t ECX = getECX();
        return getBit((u8*)&ECX,16);
    }

    uint64_t PDE::getData()
    {
        uint64_t data = 0x0000;
        u8* bin = (u8*)&data;
        
        setBit(bin,0  , this->P   );
        setBit(bin,1  , this->RW  );
        setBit(bin,2  , this->US  );
        setBit(bin,3  , this->PWT );
        setBit(bin,4  , this->PCD );
        setBit(bin,5  , this->A   );
        setBit(bin,6  , this->D   );
        setBit(bin,7  , this->PS  );
        setBit(bin,8  , this->G   );
        setBit(bin,63 , this->NX  );

        setBit(bin,9  ,getBit(&this->AVL  ,0));
        setBit(bin,10 ,getBit(&this->AVL  ,1));
        setBit(bin,11 ,getBit(&this->AVL  ,2));

        //input address
        for(uint64_t I = 12;I<52;I++)
            setBit(bin,I,getBit((u8*)&this->PhysPageBaseAddr,I-12));

        return data;
    }

    uint64_t PDPE::getData()
    {
        uint64_t data = 0x0000;
        u8* bin = (u8*)&data;
        
        setBit(bin,0  , this->P    );
        setBit(bin,1  , this->RW   );
        setBit(bin,2  , this->US   );
        setBit(bin,3  , this->PWT  );
        setBit(bin,4  , this->PCD  );
        setBit(bin,5  , this->A    );
        setBit(bin,6  , this->IGN  );
        setBit(bin,7  , 0          );
        setBit(bin,8  , this->IGN_ );
        setBit(bin,63 , this->NX   );

        setBit(bin,9  ,getBit(&this->AVL  ,0));
        setBit(bin,10 ,getBit(&this->AVL  ,1));
        setBit(bin,11 ,getBit(&this->AVL  ,2));

        //input address
        for(uint64_t I = 12;I<52;I++)
            setBit(bin,I,getBit((u8*)&this->ADDR_PD,I-12));
        //10 bits free

        return data;
    }

    uint64_t PML4E::getData()
    {
        uint64_t data = 0x0000;
        u8* bin = (u8*)&data;
        
        setBit(bin,0  , this->P    );
        setBit(bin,1  , this->RW   );
        setBit(bin,2  , this->US   );
        setBit(bin,3  , this->PWT  );
        setBit(bin,4  , this->PCD  );
        setBit(bin,5  , this->A    );
        setBit(bin,6  , this->IGN  );
        setBit(bin,7  , this->MBZ  );
        setBit(bin,8  , this->MBZ_ );
        setBit(bin,63 , this->NX   );

        setBit(bin,9  ,getBit(&this->AVL  ,0));
        setBit(bin,10 ,getBit(&this->AVL  ,1));
        setBit(bin,11 ,getBit(&this->AVL  ,2));

        //input address
        for(uint64_t I = 12;I<52;I++)
            setBit(bin,I,getBit((u8*)&this->ADDR_PDPT,I-12));
        //10 bits free

        return data;
    }

    uint64_t PML5E::getData()
    {
        uint64_t data = 0x0000;
        u8* bin = (u8*)&data;
        
        setBit(bin,0  , this->P    );
        setBit(bin,1  , this->RW   );
        setBit(bin,2  , this->US   );
        setBit(bin,3  , this->PWT  );
        setBit(bin,4  , this->PCD  );
        setBit(bin,5  , this->A    );
        setBit(bin,6  , this->IGN  );
        setBit(bin,7  , this->MBZ  );
        setBit(bin,8  , this->MBZ_ );
        setBit(bin,63 , this->NX   );

        setBit(bin,9  ,getBit(&this->AVL  ,0));
        setBit(bin,10 ,getBit(&this->AVL  ,1));
        setBit(bin,11 ,getBit(&this->AVL  ,2));

        //input address
        for(uint64_t I = 12;I<52;I++)
            setBit(bin,I,getBit((u8*)&this->ADDR_PML4T,I-12));
        //10 bits freec

        return data;
    }

    void createMasterPageTable()
    {
        if(RUNTIME_ENABLE_PML5)
        {
        }
        else
        {
        }
    }
}