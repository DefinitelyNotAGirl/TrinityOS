/*
 * Created Date: Tuesday June 27th 2023
 * Author: DefinitelyNotAGirl@github
 * -----
 * Last Modified: Tuesday July 18th 2023 4:41:54 pm
 * Modified By: Lilith (definitelynotagirl115169@gmail.com)
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

#include <main.h>
#include <ACPI.hxx>
#include <PCIe.hxx>
#include <bits>

static uint32_t SIG_T_MCFG = 'MCFG'; // MCFG
static uint32_t SIG_T_APIC = 'APIC'; // Multiple APIC Description Table (MADT)
static uint32_t SIG_T_BERT = 'BERT'; // Boot Error Record Table (BERT)
static uint32_t SIG_T_CPEP = 'CPEP'; // Corrected Platform Error Polling Table (CPEP)
static uint32_t SIG_T_DSDT = 'DSDT'; // Differentiated System Description Table (DSDT)
static uint32_t SIG_T_ECDT = 'ECDT'; // Embedded Controller Boot Resources Table (ECDT)
static uint32_t SIG_T_EINJ = 'EINJ'; // Error Injection Table (EINJ)
static uint32_t SIG_T_ERST = 'ERST'; // Error Record Serialization Table (ERST)
static uint32_t SIG_T_FACP = 'FACP'; // Fixed ACPI Description Table (FADT)
static uint32_t SIG_T_FACS = 'FACS'; // Firmware ACPI Control Structure (FACS)
static uint32_t SIG_T_HEST = 'HEST'; // Hardware Error Source Table (HEST)
static uint32_t SIG_T_MSCT = 'MSCT'; // Maximum System Characteristics Table (MSCT)
static uint32_t SIG_T_MPST = 'MPST'; // Memory Power State Table (MPST)
static uint32_t SIG_T_OEMx = 'OEMx'; // OEM Specific Information Tables (Any table with a signature beginning with "OEM" falls into this definition)
static uint32_t SIG_T_PMTT = 'PMTT'; // Platform Memory Topology Table (PMTT)
static uint32_t SIG_T_PSDT = 'PSDT'; // Persistent System Description Table (PSDT)
static uint32_t SIG_T_RASF = 'RASF'; // ACPI RAS Feature Table (RASF)
static uint32_t SIG_T_RSDT = 'RSDT'; // Root System Description Table (This wiki page; included for completeness)
static uint32_t SIG_T_SBST = 'SBST'; // Smart Battery Specification Table (SBST)
static uint32_t SIG_T_SLIT = 'SLIT'; // System Locality System Information Table (SLIT)
static uint32_t SIG_T_SRAT = 'SRAT'; // System Resource Affinity Table (SRAT)
static uint32_t SIG_T_SSDT = 'SSDT'; // Secondary System Description Table (SSDT)
static uint32_t SIG_T_XSDT = 'XSDT'; // Extended System Description Table (XSDT; 64-bit version of the RSDT)

static void doCheckSum(RSDPDescriptor* rsdp)
{
    uint8_t sum = 0;
    for(uint64_t i = 0; i < sizeof(RSDPDescriptor); i++)
        sum += ((uint8_t*)(rsdp))[i];
    if(sum == 0)
        return;
    print(u"ERROR: invalid acpi checksum!");
    while(1);
}

void print(const char16_t* msg,uint64_t n)
{
    print(msg);
    printHex64(n);
    print(u"\n\r");
}

extern "C" void acpi_table_proc_MCFG(ACPI_TABLE_MCFG* table)
{
    uint64_t descriptorCount = (table->header.Length-sizeof(ACPISDTHeader))/sizeof(ACPI_MCFG_DESC);
    print(u"---- MCFG ----\n\r");
    print(u"descriptor count: ",descriptorCount);
    for(uint64_t i = 0;i<descriptorCount;i++)
    {
        ACPI_MCFG_DESC desc = table->descriptors[i];
        desc.address>>=32;
        print(u"---- MCFG DESCRIPTOR ----\n\r");
        print(u"address: ",desc.address);
        print(u"PCI segment group: ",desc.PCISegmentGroupNumber);
        print(u"start pci bus: ",desc.StartPCIBusNumber);
        print(u"end pci bus: ",desc.EndPCIBusNumber);
        PCIe_check_mmio_area((PCIE_DEVICE_CONFIG*)desc.address);
    }
}

extern "C" void acpi_table_proc_DSDT(ACPI_TABLE_DSDT* table)
{
    print(u"---- DSDT ----\n\r");
}

extern "C" void acpi_table_proc_FADT(ACPI_TABLE_FADT* table)
{
    print(u"---- FADT ----\n\r");
    print(u"DSDT: ",table->Dsdt);
    acpi_table_proc_DSDT((ACPI_TABLE_DSDT*)table->Dsdt);
}

extern "C" void acpi_table_proc_MADT(ACPI_TABLE_MADT* table)
{
    print(u"---- MADT ----\n\r");
    print(u"Local APIC address: ",table->LocalApicAddress);
    uint64_t dataMax = (uint64_t)table+table->header.Length;
    uint64_t data = (uint64_t)table+0x2C;
    while(data < dataMax)
    {
        APIC_MADT_HEADER* Entry = (APIC_MADT_HEADER*)data;
        if(Entry->Length == 0)break;
        data+=Entry->Length;
        print(u"---- MADT ENTRY ----\n\r");
        if(Entry->EntryType == 0)
        {
            APIC_MADT_0* entry = (APIC_MADT_0*)Entry;
            print(u"Entry Type: Logical Processor\n\r");
            print(u"ID: ",entry->ApicID);
            if(EXPR_GETBIT_00(entry->Flags))
                print(u"enabled: true\n\r");
            else
                print(u"enabled: false\n\r");
            if(EXPR_GETBIT_01(entry->Flags))
                print(u"can be enabled: true\n\r");
            else
                print(u"can be enabled: false\n\r");
        }
        else if(Entry->EntryType == 1)
        {
            APIC_MADT_1* entry = (APIC_MADT_1*)Entry;
            print(u"Entry Type: I/O APIC\n\r");
        }
        else if(Entry->EntryType == 2)
        {
            APIC_MADT_2* entry = (APIC_MADT_2*)Entry;
            print(u"Entry Type: I/O APIC Interrupt Source Override\n\r");
        }
        else if(Entry->EntryType == 3)
        {
            APIC_MADT_3* entry = (APIC_MADT_3*)Entry;
            print(u"Entry Type: I/O APIC Non-maskable interrupt source\n\r");
        }
        else if(Entry->EntryType == 4)
        {
            APIC_MADT_4* entry = (APIC_MADT_4*)Entry;
            print(u"Entry Type: Local APIC Non-maskable interrupts\n\r");
        }
        else if(Entry->EntryType == 5)
        {
            APIC_MADT_5* entry = (APIC_MADT_5*)Entry;
            print(u"Entry Type: Local APIC Address Override\n\r");
        }
        else if(Entry->EntryType == 9)
        {
            APIC_MADT_9* entry = (APIC_MADT_9*)Entry;
            print(u"Entry Type: Logical Processor x2\n\r");
        }
        else
        {
            print(u"Entry Type: Unknown");
        }
    }
}

static void readSDT(ACPISDTHeader* sdt)
{
    if(sdt->Signature == 'GFCM')
        acpi_table_proc_MCFG((ACPI_TABLE_MCFG*)sdt);
    else if(sdt->Signature == 'PCAF')
        acpi_table_proc_FADT((ACPI_TABLE_FADT*)sdt);
    else if(sdt->Signature == 'CIPA')
        acpi_table_proc_MADT((ACPI_TABLE_MADT*)sdt);
    else if(sdt->Signature == 'TRGB');
    else if(sdt->Signature == 'TEPH');
    else if(sdt->Signature == 'TEAW');
    else
    {
        print(u"---- UNKNOWN SDT ----\n\r");
        print(u"address: ",(uint64_t)sdt);
        print(u"signature: ");
        print32(sdt->Signature);
        print(u"\n\r");
    }
    print(u"\n\r");
}

uint64_t readACPI_r1(void* rsdp)
{
    print(u"ACPI version 1 detected!\n\r");
    doCheckSum((RSDPDescriptor*)rsdp);
    print(u"ACPI checksum valid!\n\r");

    RSDT* rsdt = (RSDT*)((RSDPDescriptor*)rsdp)->RsdtAddress;
	
    uint8_t sum = 0;
    for(uint64_t i = 0; i < rsdt->Length; i++)
        sum += ((uint8_t*)(rsdt))[i];
    if(sum != 0)
    {
        print(u"ERROR: invalid rsdt checksum!\n\r");
        print(u"RSDT checksum: ");
        //uint64_t checksum = rsdt->Checksum;
        uint64_t checksum = sum;
        printHex64(checksum);
        print(u"\n\r");
        while(1);
    }
    print(u"rsdt checksum valid!\n\r");
    print(u"rsdt signature: ");
    print32(rsdt->Signature);
    print(u"\n\r");
    print(u"rsdt address: ");
    printHex64((uint64_t)rsdt);
    print(u"\n\r");

    uint64_t sdtCount = (rsdt->Length - sizeof(ACPISDTHeader))/4;
    uint32_t* SDTs = (uint32_t*)(&rsdt->otherSDTs);
    print(u"sdt count: ");
    printHex64(sdtCount);
    print(u"\n\r\n\rreading SDTs...\n\r");
    for(uint64_t i = 0; i < sdtCount; i++)
    {
        //print(u"sdt descriptor address ");
        //uint64_t addr = SDTs[i];
        //printHex64(addr);
        //print(u"\n\r");
        ACPISDTHeader* sdt = (ACPISDTHeader*)SDTs[i];
        readSDT(sdt);
    }
	return (uint64_t)rsdt;
}