/**
 * Created Date: Friday November 25th 2022
 * Author: DefinitelyNotAGirl@github
 * -----
 * Last Modified: Friday November 25th 2022 4:18:32 pm
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

#include <stdint.h>

#include "code32/memory.h"
memoryMap mmap;
memoryMapEntry mmap_entries[128];
#include "code32/memory.c"

#define PAGE(x) x*0x200000

uint32_t screen_position;
uint8_t* VGA;

void exit();
void loadCR3();

void setBit(uint8_t* array,uint32_t bit,uint8_t value)
{
    uint32_t n = bit/8;
    uint32_t k = bit-(8*n);
    array[n] ^= (-value ^ array[n]) & (1UL << k);
}

uint8_t getBit(uint8_t* array,uint32_t bit)
{
    uint32_t n = bit/8;
    uint32_t k = bit-(8*n);
    return (array[n] & (1 << k)) >> k;
}

uint32_t strlen(char* str)
{
    uint32_t I = 0;
    while(str[I]!=0x00)I++;
    return I;
}
void printChar(char c)
{
    if(c == '\n')
    {
        screen_position = ((screen_position/160)+1)*160;
        return;
    }
    if(c == '\b')
    {
        screen_position--;
        return;
    }
    else
    {
        VGA[screen_position++] = c;
        VGA[screen_position++] = 0x0F;
    }
}
void printStr(char* str)
{
    uint32_t len = strlen(str);
    for(uint32_t I = 0;I<len;I++)
        printChar(str[I]);
}
const char* HEXDIG = "0123456789ABCDEF";
void printuint(uint32_t n,uint8_t print0x)
{
    char* buff[8];
    if(print0x == 1)
    {
        printChar('0');
        printChar('x');
    }
    for(uint8_t I = 0;I<8;I++)
    {
        buff[I] = HEXDIG[n&0xF];
        n>>=4;
    }
    printChar(buff[7]);
    printChar(buff[6]);
    printChar(buff[5]);
    printChar(buff[4]);
    printChar(buff[3]);
    printChar(buff[2]);
    printChar(buff[1]);
    printChar(buff[0]);
}

char* helloworld = "hello world from C\n";
char* mmapComplete = "Memory map loaded\n";

//PML4 address range: 0x10000 - 0x800000000000 (~140TB)
//PDP  address range: 0x10000 - 0x800000000000 (~140TB)
//PD   address range: 0x10000 - 0x800000000000 (~140TB)

void createPML4E(uint32_t PDP_ADDR,uint32_t target_addr, uint8_t present, uint8_t rw, uint8_t executeable)
{
    uint32_t* target = target_addr;
    uint8_t* btarget = (uint8_t*)target;

    //write 32-bit base address
    target[0] = PDP_ADDR;

    //set flags
    setBit(btarget,0  ,present      );//present bit
    setBit(btarget,1  ,rw           );//read/write bit
    setBit(btarget,2  ,0            );//SU bit, supervisor only access
    setBit(btarget,3  ,0            );//PWT
    setBit(btarget,4  ,1            );//PCD (not cacheable)
    setBit(btarget,7  ,0            );//Page-Size (PS), 2MByte
    setBit(btarget,8  ,0            );//G (not a global page)
    setBit(btarget,63 ,!executeable );//no execute

    //clear reserved bits
    setBit(btarget,7,0);
    setBit(btarget,8,0);

    //clear ingnored bits
    setBit(btarget,6,0);

    //dump to screen
    printuint(target[1],1);
    printuint(target[0],0);
    printChar('\n');
}

void createPDPE(uint32_t PD_ADDR,uint32_t target_addr, uint8_t present, uint8_t rw, uint8_t executeable)
{
    uint32_t* target = target_addr;
    uint8_t* btarget = (uint8_t*)target;

    //write 32-bit base address
    target[0] = PD_ADDR;

    //set flags
    setBit(btarget,0  ,present      );//present bit
    setBit(btarget,1  ,rw           );//read/write bit
    setBit(btarget,2  ,0            );//SU bit, supervisor only access
    setBit(btarget,3  ,0            );//PWT
    setBit(btarget,4  ,1            );//PCD (not cacheable)
    setBit(btarget,7  ,0            );//Page-Size (PS), 2MByte
    setBit(btarget,8  ,0            );//G (not a global page)
    setBit(btarget,63 ,!executeable );//no execute

    //clear ingnored bits
    setBit(btarget,6,0);
    setBit(btarget,7,0);
    setBit(btarget,8,0);
 
    //dump to screen
    printuint(target[1],1);
    printuint(target[0],0);
    printChar('\n');
}

void createPDE(uint32_t physBaseAddr,uint32_t target_addr, uint8_t present, uint8_t rw, uint8_t executeable)
{
    uint32_t* target = target_addr;
    uint8_t* btarget = (uint8_t*)target;

    //write 32-bit base address
    target[0] = physBaseAddr;
    target[1] = 0;

    //set flags
    setBit(btarget,0  ,present      );//present bit
    setBit(btarget,1  ,rw           );//read/write bit
    setBit(btarget,2  ,0            );//SU bit, supervisor only access
    setBit(btarget,3  ,0            );//PWT
    setBit(btarget,4  ,1            );//PCD (not cacheable)
    setBit(btarget,7  ,1            );//Page-Size (PS), 2MByte
    setBit(btarget,8  ,0            );//G (not a global page)
    setBit(btarget,12 ,0            );//PAT
    setBit(btarget,63 ,!executeable );//no execute

    //clear ingnored bits
    setBit(btarget,52,0);
    setBit(btarget,53,0);
    setBit(btarget,54,0);
    setBit(btarget,55,0);
    setBit(btarget,56,0);
    setBit(btarget,57,0);
    setBit(btarget,58,0);
    setBit(btarget,59,0);
    setBit(btarget,60,0);
    setBit(btarget,61,0);
    setBit(btarget,62,0);

    //clear reserved bits
    setBit(btarget,13,0);
    setBit(btarget,14,0);
    setBit(btarget,15,0);
    setBit(btarget,16,0);
    setBit(btarget,17,0);
    setBit(btarget,18,0);
    setBit(btarget,19,0);
    setBit(btarget,20,0);

    //dump to screen
    printuint(target[1],1);
    printuint(target[0],0);
    printChar('\n');
}

uint32_t ADDR_PPT;
uint32_t ADDR_KCD;
uint32_t ADDR_STACK_TOP;
uint32_t PAGE_COUNT;

void setupPaging()
{
    uint32_t PAGE_SIZE = 0x200000;//2MiB
    uint32_t PAGE_ADDR = 0x000000;
    PAGE_COUNT = 0;

    uint32_t PML4_ADDR = PAGE      (1    );
    uint32_t PDPE_ADDR = PML4_ADDR+(8*512);
    uint32_t PDE_ADDR  = PDPE_ADDR+(8*512);

    //
    //create page PML4 entries
    //
    //content entry
    createPML4E(PDPE_ADDR,PML4_ADDR,1,1,1);

    //
    //create page directory pointer entries
    //
    createPDPE(PDE_ADDR+(0*512*8),PDPE_ADDR+(0*8),1,1,1);
    createPDPE(PDE_ADDR+(1*512*8),PDPE_ADDR+(1*8),1,1,0);
    createPDPE(PDE_ADDR+(2*512*8),PDPE_ADDR+(2*8),1,1,0);
    createPDPE(PDE_ADDR+(3*512*8),PDPE_ADDR+(3*8),1,1,0);
    createPDPE(PDE_ADDR+(4*512*8),PDPE_ADDR+(4*8),1,1,0);
    createPDPE(PDE_ADDR+(5*512*8),PDPE_ADDR+(5*8),1,1,0);
    createPDPE(PDE_ADDR+(6*512*8),PDPE_ADDR+(6*8),1,1,0);
    createPDPE(PDE_ADDR+(7*512*8),PDPE_ADDR+(7*8),1,1,0);

    //
    //create page directory entries
    //
    createPDE(PAGE_ADDR,PDE_ADDR,1,1,1);//reserved low memory
    PAGE_ADDR+=PAGE_SIZE;
    PDE_ADDR+=8;
    PAGE_COUNT++;

    createPDE(PAGE_ADDR,PDE_ADDR,1,0,0);//prime page table
    ADDR_PPT = PAGE_ADDR;
    PAGE_ADDR+=PAGE_SIZE;
    PDE_ADDR+=8;
    PAGE_COUNT++;

    createPDE(PAGE_ADDR,PDE_ADDR,1,1,0);//STACK AREA
    ADDR_STACK_TOP = PAGE_ADDR;
    PAGE_ADDR+=PAGE_SIZE;
    PDE_ADDR+=8;
    PAGE_COUNT++;

    createPDE(PAGE_ADDR,PDE_ADDR,1,1,0);//bootInfo page
    ADDR_KCD = PAGE_ADDR;
    PAGE_ADDR+=PAGE_SIZE;
    PDE_ADDR+=8;
    PAGE_COUNT++;

    //kernel code area
    for(uint32_t c = 0;c<64;c++)
    {
        createPDE(PAGE_ADDR,PDE_ADDR,1,0,1);
        PAGE_ADDR+=PAGE_SIZE;
        PDE_ADDR+=8;
        PAGE_COUNT++;
    }

    //generic memory
    //0x7FFE18FE
    //0xFFFFFFFF
    //0xFFE00000
    //0x80000000
    while(PAGE_ADDR <= 0x80000000)
    {
        createPDE(PAGE_ADDR,PDE_ADDR,1,1,0);
        PAGE_ADDR+=PAGE_SIZE;
        PDE_ADDR+=8;
        PAGE_COUNT++;
    }
}

void passCRT64(uint32_t BIA);
void jmp64()
{
    printStr("passing control to entry64...");
    passCRT64(ADDR_KCD);
}

void stage3(uint32_t screenPos, uint32_t VGA_ADDR)
{
    screen_position = screenPos;
    VGA = (uint16_t*)VGA_ADDR;

    printStr(helloworld);

    mmap.size = ((uint16_t*)0xFFFB)[0];
    mmap.mmap = mmap_entries;
    moveMMAP();
    printStr(mmapComplete);
    
    setupPaging();

    jmp64();
}
