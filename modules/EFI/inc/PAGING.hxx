/*
 * Created Date: Monday February 5th 2024
 * Author: Lilith
 * -----
 * Last Modified: Monday February 5th 2024 8:56:29 pm
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

struct pml5_t 
{
    uint64_t data;
};
#define pml5_addr_mask 0x000FFFFFFFFFF000

struct pml4_t 
{
    uint64_t data;
};
#define pml4_addr_mask 0x000FFFFFFFFFF000

struct pdpe_t 
{
    uint64_t data;
};
#define pdpe_addr_mask 0x000FFFFFFFFFF000

struct pde_t 
{
    uint64_t data;
};
#define pde_addr_mask 0x000FFFFFFFFFF000

struct pte_t 
{
    uint64_t data;
};
#define pte_addr_mask 0x000FFFFFFFFFF000

void paging_print_pml5(pml5_t* pml4);
void paging_print_pml4(pml4_t* pml4);
void paging_print_pdpe(pdpe_t* pdpe);
void paging_print_pde(pde_t* pde);
void paging_print_pte(pte_t* pde);
void pagetable_search(uint64_t physaddr);
