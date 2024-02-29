/**
 * Created Date: Sunday January 8th 2023
 * Author: DefinitelyNotAGirl@github
 * -----
 * Last Modified: Sunday January 8th 2023 2:31:46 am
 * Modified By: DefinitelyNotAGirl@github (definitelynotagirl115199@gmail.com)
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

/*
extern "C" void ENTRY64
*/

#pragma once

#include "../master.h"

#define ADDR(type,addr) (type)(((type*)addr)[0])

extern "C" void printError();
extern "C" void printSuccess();
extern "C" void kexit();
extern "C" void setR14(uint64_t n);

ENTRY64_DATA uint64_t DEBUG_R_14_15[2];

ENTRY64_DATA enum class DEBUG_TFF
{
    /*R14: */
    entry64             /*00: entry64 engaged*/
    ,RSDPD              /*01: RSDPD found*/
    ,acpi2              /*02: acpi revision 2+ detected*/
    ,acpiChecksumValid  /*03: acpi chekcsum valid*/
    ,MADTnotZero        /*04: MADT address not zero*/
    ,BERTnotZero        /*05: BERT address not zero*/
    ,CPEPnotZero        /*06: CPEP address not zero*/
    ,DSDTnotZero        /*07: DSDT address not zero*/
    ,ECDTnotZero        /*08: ECDT address not zero*/
    ,EINJnotZero        /*09: EINJ address not zero*/
    ,ERSTnotZero        /*10: ERST address not zero*/
    ,FADTnotZero        /*11: FADT address not zero*/
    ,FACSnotZero        /*12: FACS address not zero*/
    ,HESTnotZero        /*13: HEST address not zero*/
    ,MSCTnotZero        /*14: MSCT address not zero*/
    ,MPSTnotZero        /*15: MPST address not zero*/
    ,PMTTnotZero        /*16: PMTT address not zero*/
    ,PSDTnotZero        /*17: PSDT address not zero*/
    ,RASFnotZero        /*18: RASF address not zero*/
    ,SBSTnotZero        /*19: SBST address not zero*/
    ,SLITnotZero        /*20: SLIT address not zero*/
    ,SRATnotZero        /*21: SRAT address not zero*/
    ,MCFGnotZero        /*22: MCFG address not zero*/
};

ENTRY64 void setTFF(DEBUG_TFF tff)
{
    if((uint64_t)tff>127)
        return;
    setBit((uint8_t*)DEBUG_R_14_15,(uint64_t)tff,1);
}
ENTRY64 void clearTFF(DEBUG_TFF tff)
{
    if((uint64_t)tff>127)
        return;
    setBit((uint8_t*)DEBUG_R_14_15,(uint64_t)tff,0);
}

ENTRY64_DATA uint16_t* PrintAddr = 0xB8000;
ENTRY64_DATA __bootInfo__* bootInfo = 0x0000;

ENTRY64 void printError()
{
    //PrintAddr[0] = 0x4020;
    *PrintAddr = 0x0445;
    PrintAddr+=2;
}

ENTRY64 void printSuccess()
{
    //PrintAddr[0] = 0x2020;
    *PrintAddr = 0x0253;
    PrintAddr+=2;
}

ENTRY64 void errExit(uint64_t error)
{
    printError();
    #ifdef GEOS_DEBUG
        setR15(error);
        setR14(DEBUG_R_14_15[0]);
    #endif
    tripleFault();
}

ENTRY64 ptr64 memscan64(uint64_t target,uint64_t base,uint64_t end,uint64_t boundry)
{
    if(base%boundry != 0)
        return 0;

    ptr64 addr = base;
    while(addr < end)
    {
        if(ADDR(uint64_t,addr) == target)
            return addr;
        addr+=boundry;
    }

    return 0;
}

ENTRY64 bool doChecksum(ACPISDTHeader* tableHeader)
{
    uint8_t sum = 0;
 
    for (uint64_t i = 0; i < tableHeader->Length; i++)
        sum += ((uint8_t*)tableHeader)[i];
 
    return (sum == 0);
}

extern "C" void ENTRY64 NORETURN entry64(uint64_t bootInfoAddr)
{
    printSuccess();
    setTFF(DEBUG_TFF::entry64);

    bootInfo = (__bootInfo__*)bootInfoAddr;
    //bootInfo = 0x600000;

    RSDPDescriptor* RSDPD = 0;
    {
        ptr64 EBDA_BASE = ADDR(uint16_t,0x40A);
        ptr64 MBDA_BASE = 0xE0000;
        ptr64 MBDA_END  = 0xFFFFF;

        uint64_t RSDP_SIG = 0x2052545020445352;//"RSD PTR " -> " RTP DSR"

        RSDPD = memscan64(RSDP_SIG,EBDA_BASE,EBDA_BASE+1024,16);
        if(RSDPD == 0)
            RSDPD = memscan64(RSDP_SIG,MBDA_BASE,MBDA_END,16);

        if(RSDPD == 0)
            errExit(0x0000);
    }
    setTFF(DEBUG_TFF::RSDPD);

    //reset ACPI table addresses to 0
    bootInfo->ACPIT.MADT = 0x0000000000000000;
    bootInfo->ACPIT.BERT = 0x0000000000000000;
    bootInfo->ACPIT.CPEP = 0x0000000000000000;
    bootInfo->ACPIT.DSDT = 0x0000000000000000;
    bootInfo->ACPIT.ECDT = 0x0000000000000000;
    bootInfo->ACPIT.EINJ = 0x0000000000000000;
    bootInfo->ACPIT.ERST = 0x0000000000000000;
    bootInfo->ACPIT.FADT = 0x0000000000000000;
    bootInfo->ACPIT.FACS = 0x0000000000000000;
    bootInfo->ACPIT.HEST = 0x0000000000000000;
    bootInfo->ACPIT.MSCT = 0x0000000000000000;
    bootInfo->ACPIT.MPST = 0x0000000000000000;
    bootInfo->ACPIT.PMTT = 0x0000000000000000;
    bootInfo->ACPIT.PSDT = 0x0000000000000000;
    bootInfo->ACPIT.RASF = 0x0000000000000000;
    bootInfo->ACPIT.SBST = 0x0000000000000000;
    bootInfo->ACPIT.SLIT = 0x0000000000000000;
    bootInfo->ACPIT.SRAT = 0x0000000000000000;
    bootInfo->ACPIT.MCFG = 0x0000000000000000;

    //check revision
    if(RSDPD->Revision >= 2)
    {
        //ACPI 2.0+
        setTFF(DEBUG_TFF::acpi2);
        
        //check checksum
        uint8_t sum = 0;
        for(uint8_t I = 0;I<sizeof(RSDPDescriptor2);I++)
            sum+=((uint8_t*)RSDPD)[I];

        if(sum != 0)
            errExit(0x9201);

        //get RSDT
        XSDT* xsdt = (XSDT*)(((RSDPDescriptor2*)RSDPD)->XsdtAddress);
        uint64_t entries = (xsdt->header.Length - sizeof(xsdt->header)) / 4;

        bootInfo->ACPIT.XSDT = xsdt;
        bootInfo->ACPIT.RSDT = 0;

        if(xsdt->header.Signature != 'TDSR')
            errExit(0x9204);

        if(!doChecksum(&(xsdt->header)))
            errExit(0x9202);

        setTFF(DEBUG_TFF::acpiChecksumValid);

        if(entries == 0)
            errExit(0x9203);

        for(uint64_t I = 0;I<entries;I++)
        {
            ACPISDTHeader* header = 0;
            header = (ACPISDTHeader*)(xsdt->PointerToOtherSDT[I]);
            switch(header->Signature)
            {
                case('CIPA'):bootInfo->ACPIT.MADT = (ptr64)header;setTFF(DEBUG_TFF::MADTnotZero);break;//APCI
                case('TREB'):bootInfo->ACPIT.BERT = (ptr64)header;setTFF(DEBUG_TFF::BERTnotZero);break;
                case('PEPC'):bootInfo->ACPIT.CPEP = (ptr64)header;setTFF(DEBUG_TFF::CPEPnotZero);break;
                case('TDSD'):bootInfo->ACPIT.DSDT = (ptr64)header;setTFF(DEBUG_TFF::DSDTnotZero);break;
                case('TDCE'):bootInfo->ACPIT.ECDT = (ptr64)header;setTFF(DEBUG_TFF::ECDTnotZero);break;
                case('JNIE'):bootInfo->ACPIT.EINJ = (ptr64)header;setTFF(DEBUG_TFF::EINJnotZero);break;
                case('TSRE'):bootInfo->ACPIT.ERST = (ptr64)header;setTFF(DEBUG_TFF::ERSTnotZero);break;
                case('PCAF'):bootInfo->ACPIT.FADT = (ptr64)header;setTFF(DEBUG_TFF::FADTnotZero);break;//FACP
                case('SCAF'):bootInfo->ACPIT.FACS = (ptr64)header;setTFF(DEBUG_TFF::FACSnotZero);break;
                case('TSEH'):bootInfo->ACPIT.HEST = (ptr64)header;setTFF(DEBUG_TFF::HESTnotZero);break;
                case('TCSM'):bootInfo->ACPIT.MSCT = (ptr64)header;setTFF(DEBUG_TFF::MSCTnotZero);break;
                case('TSPM'):bootInfo->ACPIT.MPST = (ptr64)header;setTFF(DEBUG_TFF::MPSTnotZero);break;
                case('TTMP'):bootInfo->ACPIT.PMTT = (ptr64)header;setTFF(DEBUG_TFF::PMTTnotZero);break;
                case('TDSP'):bootInfo->ACPIT.PSDT = (ptr64)header;setTFF(DEBUG_TFF::PSDTnotZero);break;
                case('FSAR'):bootInfo->ACPIT.RASF = (ptr64)header;setTFF(DEBUG_TFF::RASFnotZero);break;
                case('TSBS'):bootInfo->ACPIT.SBST = (ptr64)header;setTFF(DEBUG_TFF::SBSTnotZero);break;
                case('TILS'):bootInfo->ACPIT.SLIT = (ptr64)header;setTFF(DEBUG_TFF::SLITnotZero);break;
                case('TARS'):bootInfo->ACPIT.SRAT = (ptr64)header;setTFF(DEBUG_TFF::SRATnotZero);break;
                case('GFCM'):bootInfo->ACPIT.MCFG = (ptr64)header;setTFF(DEBUG_TFF::MCFGnotZero);break;
            }
        }
    }
    else
    {
        //ACPI 1.0
        
        //check checksum
        uint8_t sum = 0;
        for(uint8_t I = 0;I<sizeof(RSDPDescriptor);I++)
            sum+=((uint8_t*)RSDPD)[I];

        if(sum != 0)
            errExit(0x9101);

        //get RSDT
        RSDT* rsdt = (RSDT*)(RSDPD->RsdtAddress);
        uint64_t entries = (rsdt->header.Length - sizeof(rsdt->header)) / 4;

        bootInfo->ACPIT.RSDT = RSDPD->RsdtAddress;
        bootInfo->ACPIT.XSDT = 0;

        if(rsdt->header.Signature != 'TDSR')
            errExit(0x9104);

        if(!doChecksum(&(rsdt->header)))
            errExit(0x9102);

        setTFF(DEBUG_TFF::acpiChecksumValid);

        if(entries == 0)
            errExit(0x9103);

        for(uint64_t I = 0;I<entries;I++)
        {
            ACPISDTHeader* header = 0;
            header = (ACPISDTHeader*)(rsdt->PointerToOtherSDT[I]);
            switch(header->Signature)
            {
                case('CIPA'):bootInfo->ACPIT.MADT = (ptr64)header;setTFF(DEBUG_TFF::MADTnotZero);break;//APCI
                case('TREB'):bootInfo->ACPIT.BERT = (ptr64)header;setTFF(DEBUG_TFF::BERTnotZero);break;
                case('PEPC'):bootInfo->ACPIT.CPEP = (ptr64)header;setTFF(DEBUG_TFF::CPEPnotZero);break;
                case('TDSD'):bootInfo->ACPIT.DSDT = (ptr64)header;setTFF(DEBUG_TFF::DSDTnotZero);break;
                case('TDCE'):bootInfo->ACPIT.ECDT = (ptr64)header;setTFF(DEBUG_TFF::ECDTnotZero);break;
                case('JNIE'):bootInfo->ACPIT.EINJ = (ptr64)header;setTFF(DEBUG_TFF::EINJnotZero);break;
                case('TSRE'):bootInfo->ACPIT.ERST = (ptr64)header;setTFF(DEBUG_TFF::ERSTnotZero);break;
                case('PCAF'):bootInfo->ACPIT.FADT = (ptr64)header;setTFF(DEBUG_TFF::FADTnotZero);break;//FACP
                case('SCAF'):bootInfo->ACPIT.FACS = (ptr64)header;setTFF(DEBUG_TFF::FACSnotZero);break;
                case('TSEH'):bootInfo->ACPIT.HEST = (ptr64)header;setTFF(DEBUG_TFF::HESTnotZero);break;
                case('TCSM'):bootInfo->ACPIT.MSCT = (ptr64)header;setTFF(DEBUG_TFF::MSCTnotZero);break;
                case('TSPM'):bootInfo->ACPIT.MPST = (ptr64)header;setTFF(DEBUG_TFF::MPSTnotZero);break;
                case('TTMP'):bootInfo->ACPIT.PMTT = (ptr64)header;setTFF(DEBUG_TFF::PMTTnotZero);break;
                case('TDSP'):bootInfo->ACPIT.PSDT = (ptr64)header;setTFF(DEBUG_TFF::PSDTnotZero);break;
                case('FSAR'):bootInfo->ACPIT.RASF = (ptr64)header;setTFF(DEBUG_TFF::RASFnotZero);break;
                case('TSBS'):bootInfo->ACPIT.SBST = (ptr64)header;setTFF(DEBUG_TFF::SBSTnotZero);break;
                case('TILS'):bootInfo->ACPIT.SLIT = (ptr64)header;setTFF(DEBUG_TFF::SLITnotZero);break;
                case('TARS'):bootInfo->ACPIT.SRAT = (ptr64)header;setTFF(DEBUG_TFF::SRATnotZero);break;
                case('GFCM'):bootInfo->ACPIT.MCFG = (ptr64)header;setTFF(DEBUG_TFF::MCFGnotZero);break;
            }
        }
    }
    bootInfo->ACPI_REVISION = RSDPD->Revision;

    errExit(0xFFFFFFFFFFFFFFFF);
}
