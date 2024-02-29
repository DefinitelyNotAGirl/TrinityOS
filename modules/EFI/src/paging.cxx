/*
 * Created Date: Monday February 5th 2024
 * Author: Lilith
 * -----
 * Last Modified: Monday February 5th 2024 8:56:38 pm
 * Modified By: Lilith (definitelynotagirl115169@gmail.com)
 * -----
 * Copyright (c) 2024 Lilith
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

#include <main.h>
#include <bits>
#include <PAGING.hxx>

bool printPML5 = true;
bool printPML4 = true;
bool printPDPE = true;
bool printPDE = true;
uint64_t searchPTE = 0;

void pagetable_search(uint64_t physaddr)
{
    searchPTE = physaddr;
}

void paging_print_pml5(pml5_t* pml5)
{
    if(printPML5)
    {
    print(u"---- Page Map Level 5 ----\n\r");
    //
    print(u"No Execute: ");
    if(EXPR_GETBIT_63(pml5->data))
        print(u"clear\n\r");
    else
        print(u"set\n\r");
    //
    print(u"Page Cache Disable: ");
    if(EXPR_GETBIT_04(pml5->data))
        print(u"clear\n\r");
    else
        print(u"set\n\r");
    //
    print(u"Page Write Through: ");
    if(EXPR_GETBIT_03(pml5->data))
        print(u"clear\n\r");
    else
        print(u"set\n\r");
    //
    print(u"user/supervisor: ");
    if(EXPR_GETBIT_02(pml5->data))
        print(u"clear\n\r");
    else
        print(u"set\n\r");
    //
    print(u"read/write: ");
    if(EXPR_GETBIT_01(pml5->data))
        print(u"clear\n\r");
    else
        print(u"set\n\r");
    //
    print(u"present: ");
    if(EXPR_GETBIT_04(pml5->data))
        print(u"clear\n\r");
    else
        print(u"set\n\r");
    }
    //print pml4 tables
    pml4_t* table = (pml4_t*)(pml5->data&pml5_addr_mask);
    for(uint64_t i = 0;i<512;i++)
    {
        paging_print_pml4(&table[i]);
    }
}

void paging_print_pml4(pml4_t* pml4)
{
    if(printPML4)
    {
    print(u"---- Page Map Level 4 ----\n\r");
    //
    print(u"No Execute: ");
    if(EXPR_GETBIT_63(pml4->data))
        print(u"clear\n\r");
    else
        print(u"set\n\r");
    //
    print(u"Page Cache Disable: ");
    if(EXPR_GETBIT_04(pml4->data))
        print(u"clear\n\r");
    else
        print(u"set\n\r");
    //
    print(u"Page Write Through: ");
    if(EXPR_GETBIT_03(pml4->data))
        print(u"clear\n\r");
    else
        print(u"set\n\r");
    //
    print(u"user/supervisor: ");
    if(EXPR_GETBIT_02(pml4->data))
        print(u"clear\n\r");
    else
        print(u"set\n\r");
    //
    print(u"read/write: ");
    if(EXPR_GETBIT_01(pml4->data))
        print(u"clear\n\r");
    else
        print(u"set\n\r");
    //
    print(u"present: ");
    if(EXPR_GETBIT_04(pml4->data))
        print(u"clear\n\r");
    else
        print(u"set\n\r");
    }
    //print pdpe tables
    pdpe_t* table = (pdpe_t*)(pml4->data&pml4_addr_mask);
    for(uint64_t i = 0;i<512;i++)
    {
        paging_print_pdpe(&table[i]);
    }
}

void paging_print_pdpe(pdpe_t* pdpe)
{
    if(printPDPE)
    {
    print(u"---- Page Directory Pointer Entry ----\n\r");
    //
    print(u"No Execute: ");
    if(EXPR_GETBIT_63(pdpe->data))
        print(u"clear\n\r");
    else
        print(u"set\n\r");
    //
    print(u"Page Cache Disable: ");
    if(EXPR_GETBIT_04(pdpe->data))
        print(u"clear\n\r");
    else
        print(u"set\n\r");
    //
    print(u"Page Write Through: ");
    if(EXPR_GETBIT_03(pdpe->data))
        print(u"clear\n\r");
    else
        print(u"set\n\r");
    //
    print(u"user/supervisor: ");
    if(EXPR_GETBIT_02(pdpe->data))
        print(u"clear\n\r");
    else
        print(u"set\n\r");
    //
    print(u"read/write: ");
    if(EXPR_GETBIT_01(pdpe->data))
        print(u"clear\n\r");
    else
        print(u"set\n\r");
    //
    print(u"present: ");
    if(EXPR_GETBIT_04(pdpe->data))
        print(u"clear\n\r");
    else
        print(u"set\n\r");
    }
    //print pd tables
    pde_t* table = (pde_t*)(pdpe->data&pdpe_addr_mask);
    for(uint64_t i = 0;i<512;i++)
    {
        paging_print_pde(&table[i]);
    }
}

void paging_print_pde(pde_t* pde)
{
    if(printPDE)
    {
    print(u"---- Page Directory Entry ----\n\r");
    //
    print(u"No Execute: ");
    if(EXPR_GETBIT_63(pde->data))
        print(u"clear\n\r");
    else
        print(u"set\n\r");
    //
    print(u"Page Cache Disable: ");
    if(EXPR_GETBIT_04(pde->data))
        print(u"clear\n\r");
    else
        print(u"set\n\r");
    //
    print(u"Page Write Through: ");
    if(EXPR_GETBIT_03(pde->data))
        print(u"clear\n\r");
    else
        print(u"set\n\r");
    //
    print(u"user/supervisor: ");
    if(EXPR_GETBIT_02(pde->data))
        print(u"clear\n\r");
    else
        print(u"set\n\r");
    //
    print(u"read/write: ");
    if(EXPR_GETBIT_01(pde->data))
        print(u"clear\n\r");
    else
        print(u"set\n\r");
    //
    print(u"present: ");
    if(EXPR_GETBIT_04(pde->data))
        print(u"clear\n\r");
    else
        print(u"set\n\r");
    }
    //print pd tables
    pte_t* table = (pte_t*)(pde->data&pde_addr_mask);
    for(uint64_t i = 0;i<512;i++)
    {
        paging_print_pte(&table[i]);
    }
}

void paging_print_pte(pte_t* pte)
{
    uint64_t physAddr = pte->data&pte_addr_mask;
    if((physAddr == searchPTE || searchPTE == 0) && physAddr != 0)
    {
    print(u"---- Page Table Entry ----\n\r");
    //
    print(u"physical address: ",physAddr);
    //
    print(u"No Execute: ");
    if(EXPR_GETBIT_63(pte->data))
        print(u"clear\n\r");
    else
        print(u"set\n\r");
    //
    print(u"Page Cache Disable: ");
    if(EXPR_GETBIT_04(pte->data))
        print(u"clear\n\r");
    else
        print(u"set\n\r");
    //
    print(u"Page Write Through: ");
    if(EXPR_GETBIT_03(pte->data))
        print(u"clear\n\r");
    else
        print(u"set\n\r");
    //
    print(u"user/supervisor: ");
    if(EXPR_GETBIT_02(pte->data))
        print(u"clear\n\r");
    else
        print(u"set\n\r");
    //
    print(u"read/write: ");
    if(EXPR_GETBIT_01(pte->data))
        print(u"clear\n\r");
    else
        print(u"set\n\r");
    //
    print(u"present: ");
    if(EXPR_GETBIT_04(pte->data))
        print(u"clear\n\r");
    else
        print(u"set\n\r");
    }
}
