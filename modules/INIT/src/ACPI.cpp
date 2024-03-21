/**
Created Date: Thursday March 7th 2024
Author: Lilith (definitelynotagirl115169@gmail.com)
-----
Last Modified: Thursday March 7th 2024 7:19:26 pm
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

#include <stdint.hxx>
#include <INIT.h>
#include <ACPI.hxx>
#include <MemoryConstants.hxx>
#include <MEMMAP.hxx>
#include <Log.hxx>
#include <CPUInfo.hxx>
#include <Interrupts.hxx>

CPU_INFO* CPUInfo = MEM_ADDR_CPU_INFO;
Interrupts::IOApicRedirects_T* IOApicRedirects = MEM_ADDR_INTERRUPT_DATA;
namespace ACPI
{
	TrinityACPI_T* SysInfo = MEM_ADDR_VIRT_ACPI_TABLES;
	uint64_t acpiAddress = MEM_ADDR_VIRT_ACPI_DATA;
	void Init(RSDT* __rsdt)
	{
		TrinityLog::print("["ANSI_BLUE"INFO"ANSI_RESET"]mapping rsdt...\n");
		uint64_t virt = getVirtualAddress(__rsdt,Kernel);
	    if(virt == UINT64_T_MAX)
	    {
	        if(setPage(TrinityPageType::ReadWriteData,__rsdt,acpiAddress,Kernel) != TrinitySetPageReturn::OK)
	            sysDBGExit(ERROR_R15,ERROR_SETPAGE);
	        virt = (acpiAddress)+((uint64_t)__rsdt%TRINITY_PAGE_SIZE);
	        acpiAddress+=TRINITY_PAGE_SIZE;
	    }
		RSDT* rsdt = (RSDT*)virt;
		setPage(TrinityPageType::ReadWriteData,RandomPhysicalAddress,(uint64_t)SysInfo,Kernel);
		SysInfo->TableCount = 0;
		SysInfo->flags = 0;
		//+ we already know the checksum to be good as the EFI loader should only pass a known good rsdt
		TrinityLog::print("["ANSI_BLUE"INFO"ANSI_RESET"]reading sdts...\n");
		uint64_t sdtCount = (rsdt->Length - sizeof(ACPISDTHeader))/4;
		//TrinityLog::print("["ANSI_BLUE"INFO"ANSI_RESET"]debug 0\n");
    	uint32_t* SDTs = (uint32_t*)(&rsdt->otherSDTs);
		TrinityDebugHex(sdtCount);
		TrinityDebugHex(SDTs);
		TrinityDebugHex(__rsdt);
		TrinityDebugHex(rsdt);
		TrinityDebugHex(rsdt->Length);
		//TrinityLog::print("["ANSI_BLUE"INFO"ANSI_RESET"]debug 1\n");
    	for(uint64_t i = 0; i < sdtCount; i++)
    	{
    	    ACPISDTHeader* sdt = (ACPISDTHeader*)SDTs[i];
			TrinityDebugHex(sdt);
			//TrinityLog::print("["ANSI_BLUE"INFO"ANSI_RESET"]debug 2\n");
			virt = getVirtualAddress((uint64_t)sdt,Kernel);
	    	if(virt == UINT64_T_MAX)
	    	{
	    	    if(setPage(TrinityPageType::ReadWriteData,(uint64_t)sdt,acpiAddress,Kernel) != TrinitySetPageReturn::OK)
	    	        sysDBGExit(ERROR_R15,ERROR_SETPAGE);
	    	    virt = (acpiAddress)+((uint64_t)sdt%TRINITY_PAGE_SIZE);
	    	    acpiAddress+=TRINITY_PAGE_SIZE;
	    	}
			sdt = (ACPISDTHeader*)virt;
			//TrinityLog::print("["ANSI_BLUE"INFO"ANSI_RESET"]debug 3\n");
			SysInfo->Tables[SysInfo->TableCount].Signature = (ACPI::SIGNATURE)sdt->Signature;
			SysInfo->Tables[SysInfo->TableCount].Address = (uint64_t)sdt;
			SysInfo->TableCount++;
			//TrinityLog::print("["ANSI_BLUE"INFO"ANSI_RESET"]debug 4\n");
    	}
	}

	static uint32_t cpuReadIoApic(uint64_t ioapicaddr, uint32_t reg)
	{
		volatile uint32_t* ioapic = (volatile uint32_t*)ioapicaddr;
	   ioapic[0] = (reg & 0xff);
	   return ioapic[4];
	}

	static void cpuWriteIoApic(void *ioapicaddr, uint32_t reg, uint32_t value)
	{
		volatile uint32_t* ioapic = (volatile uint32_t*)ioapicaddr;
	   	ioapic[0] = (reg & 0xff);
	   	ioapic[4] = value;
	}

	static inline void outb(uint16_t port, uint8_t val)
	{
	    __asm__ volatile ( "outb %b0, %w1" : : "a"(val), "Nd"(port) : "memory");
	    /* There's an outb %al, $imm8 encoding, for compile-time constant port numbers that fit in 8b. (N constraint).
	     * Wider immediate constants would be truncated at assemble-time (e.g. "i" constraint).
	     * The  outb  %al, %dx  encoding is the only option for all other cases.
	     * %1 expands to %dx because  port  is a uint16_t.  %w1 could be used if we had the port number a wider C type */
	}

	static inline uint8_t inb(uint16_t port)
	{
	    uint8_t ret;
	    __asm__ volatile ( "inb %w1, %b0"
	                   : "=a"(ret)
	                   : "Nd"(port)
	                   : "memory");
	    return ret;
	}

	static inline void io_wait(void)
	{
	    outb(0x80, 0);
	}

	#define PIC1		0x20		/* IO base address for master PIC */
	#define PIC2		0xA0		/* IO base address for slave PIC */
	#define PIC1_DATA	(PIC1+1)
	#define PIC2_DATA	(PIC2+1)
	void Mask8259Interrupts()
	{
		TrinityLog::print("["ANSI_BLUE"INFO"ANSI_RESET"]disabling 8259 PIC...");
		outb(PIC1_DATA, 0xff);
    	outb(PIC2_DATA, 0xff);
		TrinityLog::print(ANSI_GREEN"OK"ANSI_RESET"\n");
	}

	void InitAPICs()
	{
		TrinityLog::print("["ANSI_BLUE"INFO"ANSI_RESET"]initiating APICs...\n");
		setPage(TrinityPageType::ReadWriteData,RandomPhysicalAddress,(uint64_t)CPUInfo,Kernel);
		setPage(TrinityPageType::ReadWriteData,RandomPhysicalAddress,(uint64_t)IOApicRedirects,Kernel);
		CPUInfo->CPUs.size = 0;
		IOApicRedirects->Redirects.size = 16384;
		for(Interrupts::RedirectionEntry& e : IOApicRedirects->Redirects)
			e = Interrupts::RedirectionEntry(0,UINT64_T_MAX);
		IOApicRedirects->Redirects.size = 0;
		IOApicRedirects->IOApicList.size = 0;
		char sig[5];
		sig[4] = 0;
		for(uint64_t I = 0;I<SysInfo->TableCount;I++)
		{
			TrinityACPITable_T* Table = &SysInfo->Tables[I];
			if(Table->Signature == SIGNATURE::MADT)
			{
				TrinityLog::print("detected MADT\n");
				//- ██████  ██████   ██████   ██████ ███████ ███████ ███████     ███    ███  █████  ██████  ████████
				//- ██   ██ ██   ██ ██    ██ ██      ██      ██      ██          ████  ████ ██   ██ ██   ██    ██
				//- ██████  ██████  ██    ██ ██      █████   ███████ ███████     ██ ████ ██ ███████ ██   ██    ██
				//- ██      ██   ██ ██    ██ ██      ██           ██      ██     ██  ██  ██ ██   ██ ██   ██    ██
				//- ██      ██   ██  ██████   ██████ ███████ ███████ ███████     ██      ██ ██   ██ ██████     ██
				uint32_t Length 			= *(uint32_t*)(((uint64_t)Table->Address)+0x04);
				uint32_t localAPICAddress 	= *(uint32_t*)(((uint64_t)Table->Address)+0x24);
				uint32_t MADTFlags 			= *(uint32_t*)(((uint64_t)Table->Address)+0x28);
				TrinityDebugHex(MADTFlags);
				if(MADTFlags & (1<<0) != 0)
					Mask8259Interrupts();
				uint64_t EBO = 0x2C;
				while(true)
				{
					uint8_t Type 		= *(uint8_t*)(((uint64_t)Table->Address)+EBO+0x00);
					uint8_t RecordLength= *(uint8_t*)(((uint64_t)Table->Address)+EBO+0x01);
					switch(Type)
					{
						case(0):
						{
							TrinityLog::print("["ANSI_BLUE"INFO"ANSI_RESET"]Processor local APIC record...\n");
							CPU cpu;
							cpu.ID 			= *(uint8_t*) (((uint64_t)Table->Address)+EBO+0x02);
							cpu.ApicID 		= *(uint8_t*) (((uint64_t)Table->Address)+EBO+0x03);
							cpu.Flags = 0;
							uint32_t Flags 	= *(uint32_t*)(((uint64_t)Table->Address)+EBO+0x04);
							TrinityDebugHex(cpu.ApicID);
							if(Flags & (1<<0))
							{
								cpu.Flags |= CPUFlags::Enabled;
							}
							else if(Flags & (1<<1))
							{
								cpu.Flags |= CPUFlags::Enabled;
								//- enable cpu (whatever that means...) (skip for current cpu)
							}
							else
							{
								//. cpu cant be enabled
							}
							CPUInfo->CPUs << cpu;
							break;
						}
						case(1):
						{
							TrinityLog::print("["ANSI_BLUE"INFO"ANSI_RESET"]I/O APIC record...\n");
							uint64_t IOApicID 		= *(uint8_t*) (((uint64_t)Table->Address)+EBO+0x02);
							uint64_t IOApicAddress 	= *(uint32_t*)(((uint64_t)Table->Address)+EBO+0x04);
							uint64_t InterruptBase 	= *(uint32_t*)(((uint64_t)Table->Address)+EBO+0x08);
							TrinityDebugHex(IOApicID);
							TrinityDebugHex(IOApicAddress);
							TrinityDebugHex(InterruptBase);
							uint64_t virt = getVirtualAddress(IOApicAddress,Kernel);
	    					if(virt == UINT64_T_MAX)
	    					{
	    					    if(setPage(TrinityPageType::ReadWriteData,IOApicAddress,acpiAddress,Kernel) != TrinitySetPageReturn::OK)
	    					        sysDBGExit(ERROR_R15,ERROR_SETPAGE);
	    					    virt = (acpiAddress)+((uint64_t)IOApicAddress%TRINITY_PAGE_SIZE);
	    					    acpiAddress+=TRINITY_PAGE_SIZE;
	    					}
							IOApicAddress = virt;
							uint64_t RedirectionEntries = (cpuReadIoApic(IOApicAddress,0x1)>>16)&0xFF;
							TrinityDebugHex(RedirectionEntries);
							TrinityDebugHex(IOApicAddress);
							//*
							//*	push
							//*
							{
								Interrupts::IOApic apic(IOApicAddress,*(uint32_t*)(((uint64_t)Table->Address)+EBO+0x04),InterruptBase);
								IOApicRedirects->IOApicList << apic;
							}
							IOApicRedirects->Redirects.size += RedirectionEntries;
							Interrupts::IOApic* ioApic = &IOApicRedirects->IOApicList[IOApicRedirects->IOApicList.size-1];
							for(uint64_t i = 0;i<RedirectionEntries;i++)
								IOApicRedirects->Redirects[InterruptBase+i] = Interrupts::RedirectionEntry(ioApic,i);
							break;
						}
						case(2):
						{
							TrinityLog::print("["ANSI_BLUE"INFO"ANSI_RESET"]I/O APIC Interrupt Source Override record...\n");
							uint64_t BusSource = *(uint8_t*) (((uint64_t)Table->Address)+EBO+0x02);
							uint64_t IRQSource = *(uint8_t*) (((uint64_t)Table->Address)+EBO+0x03);
							uint64_t GlobalSystemInterrupt = *(uint32_t*)(((uint64_t)Table->Address)+EBO+0x04);
							TrinityDebugHex(BusSource);
							TrinityDebugHex(IRQSource);
							TrinityDebugHex(GlobalSystemInterrupt);
							switch(IRQSource)
							{
								case(Interrupts::IRQ::Timer):
									IOApicRedirects->Redirects[Interrupts::IRQ::Timer].SetSystemInterrupt(Interrupts::Int::Timer);
									break;
								case(Interrupts::IRQ::KeyboardController):
									IOApicRedirects->Redirects[Interrupts::IRQ::KeyboardController].SetSystemInterrupt(Interrupts::Int::KeyboardController);
									break;
								case(Interrupts::IRQ::Mouse):
									IOApicRedirects->Redirects[Interrupts::IRQ::Mouse].SetSystemInterrupt(Interrupts::Int::Mouse);
									break;
								case(Interrupts::IRQ::FloppyDiskController):
									IOApicRedirects->Redirects[Interrupts::IRQ::FloppyDiskController].SetSystemInterrupt(Interrupts::Int::FloppyDiskController);
									break;
								case(Interrupts::IRQ::RealTimeClock):
									IOApicRedirects->Redirects[Interrupts::IRQ::RealTimeClock].SetSystemInterrupt(Interrupts::Int::RealTimeClock);
									break;
								default:
									IOApicRedirects->Redirects[IRQSource].SetSystemInterrupt(Interrupts::Int::UnknownIRQ);
									break;
							}
							break;
						}
						case(3):
						{
							TrinityLog::print("["ANSI_BLUE"INFO"ANSI_RESET"]I/O APIC Non-Maskable Interrupt Source record...\n");
							break;
						}
						case(4):
						{
							TrinityLog::print("["ANSI_BLUE"INFO"ANSI_RESET"]Local APIC Non-Maskable Interrupts record...\n");
							uint64_t cpuID = *(uint8_t*) (((uint64_t)Table->Address)+EBO+0x02);
							TrinityDebugHex(cpuID);
							//TODO: configure some value here with LINT0/LINT1
							break;
						}
						case(5):
						{
							TrinityLog::print("["ANSI_BLUE"INFO"ANSI_RESET"]Local APIC Address Override record...\n");
							break;
						}
						case(9):
						{
							TrinityLog::print("["ANSI_BLUE"INFO"ANSI_RESET"]Processor Local x2APIC record...\n");
							break;
						}
					}
					EBO+=RecordLength;
					if(EBO == Length)
						break;
				}
			}
		}
		//* ██ ███    ██ ██ ████████     ██████   ██████ ██
		//* ██ ████   ██ ██    ██        ██   ██ ██      ██
		//* ██ ██ ██  ██ ██    ██        ██████  ██      ██
		//* ██ ██  ██ ██ ██    ██        ██      ██      ██
		//* ██ ██   ████ ██    ██        ██       ██████ ██
		if(IOApicRedirects->Redirects[Interrupts::IRQ::PCI_0].RedirectionEntryNumber != UINT64_T_MAX)
		{TrinityLog::print("["ANSI_RED"WARNING"ANSI_RESET"]PCI_0 IRQ occupied\n");}else
		{
			IOApicRedirects->Redirects[Interrupts::IRQ::PCI_0].SetSystemInterrupt(Interrupts::Int::PCI_0);
		}
		if(IOApicRedirects->Redirects[Interrupts::IRQ::PCI_1].RedirectionEntryNumber != UINT64_T_MAX)
		{TrinityLog::print("["ANSI_RED"WARNING"ANSI_RESET"]PCI_1 IRQ occupied\n");}else
		{
			IOApicRedirects->Redirects[Interrupts::IRQ::PCI_1].SetSystemInterrupt(Interrupts::Int::PCI_1);
		}
		if(IOApicRedirects->Redirects[Interrupts::IRQ::PCI_2].RedirectionEntryNumber != UINT64_T_MAX)
		{TrinityLog::print("["ANSI_RED"WARNING"ANSI_RESET"]PCI_2 IRQ occupied\n");}else
		{
			IOApicRedirects->Redirects[Interrupts::IRQ::PCI_2].SetSystemInterrupt(Interrupts::Int::PCI_2);
		}
		//? ███    ███ ██ ███████  ██████     ██ ██████   ██████
		//? ████  ████ ██ ██      ██          ██ ██   ██ ██    ██
		//? ██ ████ ██ ██ ███████ ██          ██ ██████  ██    ██
		//? ██  ██  ██ ██      ██ ██          ██ ██   ██ ██ ▄▄ ██
		//? ██      ██ ██ ███████  ██████     ██ ██   ██  ██████
		uint64_t i = 0;
		for(Interrupts::RedirectionEntry& e : IOApicRedirects->Redirects)
		{
			if(e.GetSystemInterrupt() == 0xFE)
			{
				e.SetSystemInterrupt(Interrupts::Int::MiscIRQBase+i);
			}
			i++;
		}
	}
}
