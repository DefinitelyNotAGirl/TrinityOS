/**
Created Date: Friday March 15th 2024
Author: Lilith (definitelynotagirl115169@gmail.com)
-----
Last Modified: Friday March 15th 2024 3:27:29 am
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

#include "gcc.hxx"
#include "FixedSizeList.hxx"

namespace GPT
{
	template<int SectorSize>
	class __packed__ LBA0 {
		//*
		//* Members
		//*
		protected:
		public:
		//!
		//! Functions
		//!
		protected:
		public:
	};

	template<int SectorSize>
	class __packed__ PartitionEntry {
		//*
		//* Members
		//*
		protected:
		public:
			/* 0x00 */uint8_t	Reserved_0[SectorSize];
		//!
		//! Functions
		//!
		protected:
		public:
	};

	template<int SectorSize>
	class __packed__ LBA1 {
		//*
		//* Members
		//*
		protected:
		public:
			/* 0x00 */uint64_t 	Signature;
			/* 0x08 */uint32_t 	Revision;
			/* 0x0C */uint32_t 	HeaderSize;
			/* 0x10 */uint32_t 	crc32;
			/* 0x14 */uint8_t	Reserved_0[4];
			/* 0x18 */uint64_t 	CurrentLBA;
			/* 0x20 */uint64_t 	BackupLBA;
			/* 0x28 */uint64_t 	FirstUsableLBA;
			/* 0x30 */uint64_t 	LastUsableLBA;
			/* 0x38 */uint8_t	GUID[16];
			/* 0x48 */uint64_t	PartitionTableStartLBA;
			/* 0x50 */uint32_t	PartitionCount;
			/* 0x54 */uint32_t	PartitionEntrySize;
			/* 0x58 */uint32_t	PartitionTableCRC32;
			/* 0x5C */uint8_t	Reserved_1[SectorSize-0x5C];
		//!
		//! Functions
		//!
		protected:
		public:
	};

	template<int SectorSize>
	class __packed__ Primary {
		//*
		//* Members
		//*
		protected:
		public:
			LBA0<SectorSize> lba0;
			LBA1<SectorSize> lba1;
		//!
		//! Functions
		//!
		protected:
		public:
	};
}
