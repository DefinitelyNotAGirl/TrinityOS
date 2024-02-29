/**
 * Created Date: Wednesday May 24th 2023
 * Author: DefinitelyNotAGirl@github
 * -----
 * Last Modified: Wednesday May 24th 2023 10:07:09 am
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
#include <paging>
#include <bits>

namespace paging
{
    //
    //
    // PDE
    //
    //
    PDE::PDE(uint64_t* en)
        :e(en){}

    void PDE::setPhysicalPageBaseAddress(uint64_t addr)
    {
        //set fixed (MBZ, AVL & MBO bits)
        uint64_t fixed0 = 0b0000000000001111111111111111111111111111111000000001111111111111;
        uint64_t addr0  = 0b1111111111110000000000000000000000000000000111111111111111111111;

        addr &= fixed0;//clear all MBZ bits
        *e &= addr0; //clear physical base address
        *e |= addr;  //place new address
    }

    bool PDE::isDirty()
    {
        if(EXPR_GETBIT_06(*e))
            return true;
        return false;
    }

    bool PDE::wasAccessed()
    {
        if(EXPR_GETBIT_05(*e))
            return true;
        return false;
    }

    void PDE::enableGlobal()            {SETBIT_08(*e);}
    void PDE::enablePageCache()         {CLEARBIT_04(*e);}
    void PDE::enablePageWriteThrough()  {SETBIT_03(*e);}
    void PDE::enableSupervisorOnly()    {SETBIT_02(*e);}
    void PDE::enableWrite()             {SETBIT_01(*e);}
    void PDE::enablePresent()           {SETBIT_00(*e);}
    void PDE::enableExecute()           {SETBIT_63(*e);}

    void PDE::disableGlobal()            {CLEARBIT_08(*e);}
    void PDE::disablePageCache()         {SETBIT_04(*e);}
    void PDE::disablePageWriteThrough()  {CLEARBIT_03(*e);}
    void PDE::disableSupervisorOnly()    {CLEARBIT_02(*e);}
    void PDE::disableWrite()             {CLEARBIT_01(*e);}
    void PDE::disablePresent()           {CLEARBIT_00(*e);}
    void PDE::disableExecute()           {CLEARBIT_63(*e);}

    //
    //
    // PDPE
    //
    //
    PDPE::PDPE(uint64_t* en)
        :e(en){}

    void PDPE::setPhysicalPageBaseAddress(uint64_t addr)
    {
        //set fixed (MBZ, AVL & MBO bits)
        uint64_t fixed0 = 0b0000000000001111111111111111111111111111111000000001111000111111;
        uint64_t addr0  = 0b1111111111110000000000000000000000000000000000000001111111111111;

        addr &= fixed0;//clear all MBZ bits
        *e &= addr0; //clear physical base address
        *e |= addr;  //place new address
    }

    //bool PDPE::isDirty()
    //{
    //    if(EXPR_GETBIT_06(*e))
    //        return true;
    //    return false;
    //}

    bool PDPE::wasAccessed()
    {
        if(EXPR_GETBIT_05(*e))
            return true;
        return false;
    }

    void PDPE::enablePageCache()         {CLEARBIT_04(*e);}
    void PDPE::enablePageWriteThrough()  {SETBIT_03(*e);}
    void PDPE::enableSupervisorOnly()    {SETBIT_02(*e);}
    void PDPE::enableWrite()             {SETBIT_01(*e);}
    void PDPE::enablePresent()           {SETBIT_00(*e);}
    void PDPE::enableExecute()           {SETBIT_63(*e);}

    void PDPE::disablePageCache()         {SETBIT_04(*e);}
    void PDPE::disablePageWriteThrough()  {CLEARBIT_03(*e);}
    void PDPE::disableSupervisorOnly()    {CLEARBIT_02(*e);}
    void PDPE::disableWrite()             {CLEARBIT_01(*e);}
    void PDPE::disablePresent()           {CLEARBIT_00(*e);}
    void PDPE::disableExecute()           {CLEARBIT_63(*e);}

    //
    //
    // PML4E
    //
    //
    PML4E::PML4E(uint64_t* en)
        :e(en){}

    void PML4E::setPhysicalPageBaseAddress(uint64_t addr)
    {
        //set fixed (MBZ, AVL & MBO bits)
        uint64_t fixed0 = 0b0000000000001111111111111111111111111111111000000001111000111111;
        uint64_t addr0  = 0b1111111111110000000000000000000000000000000000000001111111111111;

        addr &= fixed0;//clear all MBZ bits
        *e &= addr0; //clear physical base address
        *e |= addr;  //place new address
    }

    //bool PML4E::isDirty()
    //{
    //    if(EXPR_GETBIT_06(*e))
    //        return true;
    //    return false;
    //}

    bool PML4E::wasAccessed()
    {
        if(EXPR_GETBIT_05(*e))
            return true;
        return false;
    }

    void PML4E::enablePageCache()         {CLEARBIT_04(*e);}
    void PML4E::enablePageWriteThrough()  {SETBIT_03(*e);}
    void PML4E::enableSupervisorOnly()    {SETBIT_02(*e);}
    void PML4E::enableWrite()             {SETBIT_01(*e);}
    void PML4E::enablePresent()           {SETBIT_00(*e);}
    void PML4E::enableExecute()           {SETBIT_63(*e);}

    void PML4E::disablePageCache()         {SETBIT_04(*e);}
    void PML4E::disablePageWriteThrough()  {CLEARBIT_03(*e);}
    void PML4E::disableSupervisorOnly()    {CLEARBIT_02(*e);}
    void PML4E::disableWrite()             {CLEARBIT_01(*e);}
    void PML4E::disablePresent()           {CLEARBIT_00(*e);}
    void PML4E::disableExecute()           {CLEARBIT_63(*e);}

    //
    //
    // PML5E
    //
    //
    PML5E::PML5E(uint64_t* en)
        :e(en){}

    void PML5E::setPhysicalPageBaseAddress(uint64_t addr)
    {
        //set fixed (MBZ, AVL & MBO bits)
        uint64_t fixed0 = 0b0000000000001111111111111111111111111111111000000001111000111111;
        uint64_t addr0  = 0b1111111111110000000000000000000000000000000000000001111111111111;

        addr &= fixed0;//clear all MBZ bits
        *e &= addr0; //clear physical base address
        *e |= addr;  //place new address
    }

    //bool PML5E::isDirty()
    //{
    //    if(EXPR_GETBIT_06(*e))
    //        return true;
    //    return false;
    //}

    bool PML5E::wasAccessed()
    {
        if(EXPR_GETBIT_05(*e))
            return true;
        return false;
    }

    void PML5E::enablePageCache()         {CLEARBIT_04(*e);}
    void PML5E::enablePageWriteThrough()  {SETBIT_03(*e);}
    void PML5E::enableSupervisorOnly()    {SETBIT_02(*e);}
    void PML5E::enableWrite()             {SETBIT_01(*e);}
    void PML5E::enablePresent()           {SETBIT_00(*e);}
    void PML5E::enableExecute()           {SETBIT_63(*e);}

    void PML5E::disablePageCache()         {SETBIT_04(*e);}
    void PML5E::disablePageWriteThrough()  {CLEARBIT_03(*e);}
    void PML5E::disableSupervisorOnly()    {CLEARBIT_02(*e);}
    void PML5E::disableWrite()             {CLEARBIT_01(*e);}
    void PML5E::disablePresent()           {CLEARBIT_00(*e);}
    void PML5E::disableExecute()           {CLEARBIT_63(*e);}
}
