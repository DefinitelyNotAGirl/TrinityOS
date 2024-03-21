/**
Created Date: Tuesday March 12th 2024
Author: Lilith (definitelynotagirl115169@gmail.com)
-----
Last Modified: Tuesday March 12th 2024 4:12:55 pm
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

#include <Interrupts.hxx>
#include <Log.hxx>
#include <INIT.h>

namespace Interrupts
{
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
	//- ██     ██  ██████       █████  ██████  ██  ██████
	//- ██    ██  ██    ██     ██   ██ ██   ██ ██ ██
	//- ██   ██   ██    ██     ███████ ██████  ██ ██
	//- ██  ██    ██    ██     ██   ██ ██      ██ ██
	//- ██ ██      ██████      ██   ██ ██      ██  ██████
	IOApic::IOApic(uint64_t VirtualAddress,uint64_t PhysicalAddress,uint64_t InterruptBase)
		:VirtualAddress(VirtualAddress),PhysicalAddress(PhysicalAddress),InterruptBase(InterruptBase){}

	void IOApic::setRegister(uint32_t val,uint64_t n)
	{
		return cpuWriteIoApic(this->VirtualAddress,n,val);
	}
	uint32_t IOApic::readRegister(uint64_t n)
	{
		return cpuReadIoApic(this->VirtualAddress,n);
	}

	//+ ██████  ███████ ██████  ██ ██████  ███████  ██████ ████████ ██  ██████  ███    ██     ███████ ███    ██ ████████ ██████  ██    ██
	//+ ██   ██ ██      ██   ██ ██ ██   ██ ██      ██         ██    ██ ██    ██ ████   ██     ██      ████   ██    ██    ██   ██  ██  ██
	//+ ██████  █████   ██   ██ ██ ██████  █████   ██         ██    ██ ██    ██ ██ ██  ██     █████   ██ ██  ██    ██    ██████    ████
	//+ ██   ██ ██      ██   ██ ██ ██   ██ ██      ██         ██    ██ ██    ██ ██  ██ ██     ██      ██  ██ ██    ██    ██   ██    ██
	//+ ██   ██ ███████ ██████  ██ ██   ██ ███████  ██████    ██    ██  ██████  ██   ████     ███████ ██   ████    ██    ██   ██    ██
	RedirectionEntry::RedirectionEntry(IOApic* _ioApic,uint64_t _RedirectionEntryNumber)
		:ioApic(_ioApic),RedirectionEntryNumber(_RedirectionEntryNumber){}

	void RedirectionEntry::SetSystemInterrupt(uint8_t Interrupt)
	{
		uint64_t reg = 0x10+(this->RedirectionEntryNumber*2);
		uint32_t val = this->ioApic->readRegister(reg);
		val &= 0xFFFFFF00 | Interrupt;
		this->ioApic->setRegister(val,reg);
		TrinityLog::print("["ANSI_BLUE"INFO"ANSI_RESET"]done!\n");
	}

	uint64_t RedirectionEntry::GetSystemInterrupt()
	{
		return this->ioApic->readRegister(0x10+(this->RedirectionEntryNumber*2)) & 0xFF;
	}

	IOApic* RedirectionEntry::GetIOApic()
	{
		return this->ioApic;
	}

	//, ██████  ███████ ██████  ██ ██████  ███████  ██████ ████████     ██      ██ ███████ ████████
	//, ██   ██ ██      ██   ██ ██ ██   ██ ██      ██         ██        ██      ██ ██         ██
	//, ██████  █████   ██   ██ ██ ██████  █████   ██         ██        ██      ██ ███████    ██
	//, ██   ██ ██      ██   ██ ██ ██   ██ ██      ██         ██        ██      ██      ██    ██
	//, ██   ██ ███████ ██████  ██ ██   ██ ███████  ██████    ██        ███████ ██ ███████    ██
}