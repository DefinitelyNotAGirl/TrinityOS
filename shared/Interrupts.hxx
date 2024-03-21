/**
Created Date: Tuesday March 12th 2024
Author: Lilith (definitelynotagirl115169@gmail.com)
-----
Last Modified: Tuesday March 12th 2024 3:22:58 pm
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
#pragma once
#include "FixedSizeList.hxx"
#include <gcc.hxx>

namespace Interrupts
{
	//* ██ ███    ██ ████████     ███    ██ ██    ██ ███    ███ ██████  ███████ ██████  ███████
	//* ██ ████   ██    ██        ████   ██ ██    ██ ████  ████ ██   ██ ██      ██   ██ ██
	//* ██ ██ ██  ██    ██        ██ ██  ██ ██    ██ ██ ████ ██ ██████  █████   ██████  ███████
	//* ██ ██  ██ ██    ██        ██  ██ ██ ██    ██ ██  ██  ██ ██   ██ ██      ██   ██      ██
	//* ██ ██   ████    ██        ██   ████  ██████  ██      ██ ██████  ███████ ██   ██ ███████
	namespace Int {
		//+ 0x00-0x1F reserved for exceptions
		//+ 0x20 range reserved for specific devices
		constexpr uint8_t Timer 				= 0x21;
		constexpr uint8_t KeyboardController 	= 0x22;
		constexpr uint8_t InterruptController 	= 0x23;
		constexpr uint8_t FloppyDiskController 	= 0x24;
		constexpr uint8_t RealTimeClock 		= 0x25;
		constexpr uint8_t Mouse 				= 0x26;
		//+ 0x30 range reserved for PCI interrupts
		constexpr uint8_t PCI_0 				= 0x30;
		constexpr uint8_t PCI_1 				= 0x31;
		constexpr uint8_t PCI_2 				= 0x32;
		//+0x40 - 0x7F reserved for misc IRQs
		constexpr uint8_t MiscIRQBase			= 0x40;
		//+ system calls
		constexpr uint8_t Syscall				= 0x80;
		constexpr uint8_t SysMalloc				= 0x81;
		constexpr uint8_t SysSleep				= 0x82;
		//+ misc
		constexpr uint8_t UnknownIRQ			= 0xE0;
	}

	//! ██ ██████   ██████      ███    ██ ██    ██ ███    ███ ██████  ███████ ██████  ███████
	//! ██ ██   ██ ██    ██     ████   ██ ██    ██ ████  ████ ██   ██ ██      ██   ██ ██
	//! ██ ██████  ██    ██     ██ ██  ██ ██    ██ ██ ████ ██ ██████  █████   ██████  ███████
	//! ██ ██   ██ ██ ▄▄ ██     ██  ██ ██ ██    ██ ██  ██  ██ ██   ██ ██      ██   ██      ██
	//! ██ ██   ██  ██████      ██   ████  ██████  ██      ██ ██████  ███████ ██   ██ ███████
	namespace IRQ {
		constexpr uint8_t Timer 				= 0;
		constexpr uint8_t KeyboardController 	= 1;
		constexpr uint8_t InterruptController 	= 2;
		constexpr uint8_t FloppyDiskController 	= 6;
		constexpr uint8_t RealTimeClock 		= 8;
		constexpr uint8_t Mouse 				=12;
		constexpr uint8_t PCI_0 				= 5;
		constexpr uint8_t PCI_1 				=10;
		constexpr uint8_t PCI_2 				=11;
	}

	//- ██     ██  ██████       █████  ██████  ██  ██████
	//- ██    ██  ██    ██     ██   ██ ██   ██ ██ ██
	//- ██   ██   ██    ██     ███████ ██████  ██ ██
	//- ██  ██    ██    ██     ██   ██ ██      ██ ██
	//- ██ ██      ██████      ██   ██ ██      ██  ██████
	class __packed__ IOApic {
		//*
		//* Members
		//*
		protected:
			uint64_t VirtualAddress;
			uint64_t PhysicalAddress;
		public:
			uint64_t InterruptBase;
		//!
		//! Functions
		//!
		protected:
		public:
			IOApic(uint64_t VirtualAddress,uint64_t PhysicalAddress,uint64_t InterruptBase);
			void setRegister(uint32_t val,uint64_t n);
			uint32_t readRegister(uint64_t n);
	};

	//+ ██████  ███████ ██████  ██ ██████  ███████  ██████ ████████ ██  ██████  ███    ██     ███████ ███    ██ ████████ ██████  ██    ██
	//+ ██   ██ ██      ██   ██ ██ ██   ██ ██      ██         ██    ██ ██    ██ ████   ██     ██      ████   ██    ██    ██   ██  ██  ██
	//+ ██████  █████   ██   ██ ██ ██████  █████   ██         ██    ██ ██    ██ ██ ██  ██     █████   ██ ██  ██    ██    ██████    ████
	//+ ██   ██ ██      ██   ██ ██ ██   ██ ██      ██         ██    ██ ██    ██ ██  ██ ██     ██      ██  ██ ██    ██    ██   ██    ██
	//+ ██   ██ ███████ ██████  ██ ██   ██ ███████  ██████    ██    ██  ██████  ██   ████     ███████ ██   ████    ██    ██   ██    ██
	class __packed__ RedirectionEntry {
		//*
		//* Members
		//*
		protected:
			IOApic* ioApic;
		public:
			uint64_t RedirectionEntryNumber;
		//!
		//! Functions
		//!
		protected:
		public:
			RedirectionEntry(IOApic* _ioApic,uint64_t _RedirectionEntryNumber);
			void SetSystemInterrupt(uint8_t Interrupt);
			uint64_t GetSystemInterrupt();
			IOApic* GetIOApic();
	};

	//, ██████  ███████ ██████  ██ ██████  ███████  ██████ ████████     ██      ██ ███████ ████████
	//, ██   ██ ██      ██   ██ ██ ██   ██ ██      ██         ██        ██      ██ ██         ██
	//, ██████  █████   ██   ██ ██ ██████  █████   ██         ██        ██      ██ ███████    ██
	//, ██   ██ ██      ██   ██ ██ ██   ██ ██      ██         ██        ██      ██      ██    ██
	//, ██   ██ ███████ ██████  ██ ██   ██ ███████  ██████    ██        ███████ ██ ███████    ██
	class IOApicRedirects_T {
	public:
		uint64_t Flags;
		FixedList<RedirectionEntry,(256*1024)/sizeof(RedirectionEntry)> Redirects;//256KiB of data
		FixedList<IOApic,64> IOApicList;
	};
	extern IOApicRedirects_T* IOApicRedirects;
}