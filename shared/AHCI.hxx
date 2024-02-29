/**
Created Date: Thursday February 8th 2024
Author: Lilith (definitelynotagirl115169@gmail.com)
-----
Last Modified: Thursday February 29th 2024 5:18:25 am
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

#include "PCIe.hxx"
#include "DISK.hxx"
#include "SATA.hxx"
#include "gcc.hxx"

#define HBA_PxIS_TFES 0x40000000

#define ATA_CMD_READ_DMA_EX 0x25

#define	SATA_SIG_ATA	0x00000101	// SATA drive
#define	SATA_SIG_ATAPI	0xEB140101	// SATAPI drive
#define	SATA_SIG_SEMB	0xC33C0101	// Enclosure management bridge
#define	SATA_SIG_PM	0x96690101	// Port multiplier

#define AHCI_DEV_NULL 0
#define AHCI_DEV_SATA 1
#define AHCI_DEV_SEMB 2
#define AHCI_DEV_PM 3
#define AHCI_DEV_SATAPI 4

#define HBA_PORT_IPM_ACTIVE 1
#define HBA_PORT_DET_PRESENT 3

#define ATA_DEV_BUSY 0x80
#define ATA_DEV_DRQ 0x08

enum class FIS_TYPE : uint8_t
{
	REG_H2D		= 0x27,	// Register FIS - host to device
	REG_D2H		= 0x34,	// Register FIS - device to host
	DMA_ACT		= 0x39,	// DMA activate FIS - device to host
	DMA_SETUP	= 0x41,	// DMA setup FIS - bidirectional
	DATA		= 0x46,	// Data FIS - bidirectional
	BIST		= 0x58,	// BIST activate FIS - bidirectional
	PIO_SETUP	= 0x5F,	// PIO setup FIS - device to host
	DEV_BITS	= 0xA1,	// Set device bits FIS - device to host
};

struct AHCI_GENERIC_HOST_CONTROL
{
    /*(+0x00)*/ uint32_t HostCapabilities; //CAP
    /*(+0x04)*/ uint32_t GlobalHostControl; //GHC
    /*(+0x08)*/ uint32_t InterruptStatus; //IS
    /*(+0x0C)*/ uint32_t PortsImplemented; //PI
    /*(+0x10)*/ uint32_t Version; //VS
    /*(+0x14)*/ uint32_t CommandCompletionCoalescingControl;// CCC_CTL
    /*(+0x18)*/ uint32_t CommandCompletionCoalescingPorts;// CCC_PORTS
    /*(+0x1C)*/ uint32_t EnclosureManagementLocation;// EM_LOC
    /*(+0x20)*/ uint32_t EnclosureManagementControl;// EM_CTL
    /*(+0x24)*/ uint32_t HostCapabilitiesExtended; // CAP2
    /*(+0x28)*/ uint32_t BIOS_OS_HandoffControlAndStatus; //BOHC
};

namespace AHCI
{
	//? support only 1.024 out of the 65.535 physical region descriptors that hardware could support, this is done to save memory
	const uint64_t maxSupportedPhysicalRegionDescriptors = 1024;

	struct PORT
	{
	    /*(+0x00)*/ uint32_t CommandListPhysicalBaseAddress_LOW;//CLB
	    /*(+0x04)*/ uint32_t CommandListPhysicalBaseAddress_HIGH;//CLBU
	    /*(+0x08)*/ uint32_t FisPhysicalBaseAddress_LOW;//FB
	    /*(+0x0C)*/ uint32_t FisPhysicalBaseAddress_HIGH;//FBU
	    /*(+0x10)*/ uint32_t InterruptStatus;//IS
	    /*(+0x14)*/ uint32_t InterruptEnable;//IE
	    /*(+0x18)*/ uint32_t CommandAndStatus;//CMD
	    /*(+0x1C)*/ uint32_t Reserved0;
	    /*(+0x20)*/ uint32_t TaskFileData;//TFD
	    /*(+0x24)*/ uint32_t Signature;//SIG
	    /*(+0x28)*/ uint32_t SerialAtaStatus;//SSTS
	    /*(+0x2C)*/ uint32_t SerialAtaControl;//SCTL
	    /*(+0x30)*/ uint32_t SerialAtaError;//SERR
	    /*(+0x34)*/ uint32_t SerialAtaActive;//SACT
	    /*(+0x38)*/ uint32_t CommandIssue;//CI
	    /*(+0x3C)*/ uint32_t SerialAtaNotification;//SNTF
	    /*(+0x40)*/ uint32_t FisBasedSwitchingControl;//FBS
	    /*(+0x44)*/ uint32_t DeviceSleep;//DEVSLP
	    /*(+0x48)*/ uint8_t Reserved1[40];//DEVSLP
	    /*(+0x70)*/ uint8_t VendorSpecific[16];//VS
	};

	struct HBA_T
	{
	    /*(+0x000)*/ AHCI_GENERIC_HOST_CONTROL GenericHostControl;
	    /*(+0x02c)*/ uint8_t reserved0[51];
	    /*(+0x05f)*/ uint8_t reserved1[64];
	    /*(+0x0a0)*/ uint8_t VendorSpecificRegisters[95];
	    /*(+0x100)*/ PORT Ports[32];
	};

    struct DMASetupFIS {
		uint8_t FISType;
		uint8_t byte1;
		uint16_t reserved0; //MBZ
		uint32_t DMABufferIdentifierLow;
		uint32_t DMABufferIdentifierHigh;
		uint32_t reserved1; //MBZ
		uint32_t DMABufferOffset;
		uint32_t DMATransferCount;
		uint32_t reserved2; //MBZ
    } PACKED ;

    struct PIOSetupFIS {
		uint8_t FISType;
		uint8_t byte1;
		uint8_t Status;
		uint8_t Error;
		uint16_t LBA_0t15;
		uint8_t LBA_16t23;
		uint8_t device;
		uint32_t LBA_24t47; //upper 8 bits reserved, MBZ
		uint16_t count;
		uint8_t reserved0;
		uint8_t E_Status;
		uint16_t TransferCount;
		uint16_t reserved1;
    } PACKED ;

	struct D2HRegisterFIS {
		uint8_t FISType;
		uint8_t byte1;
		uint8_t Status;
		uint8_t Error;
		uint16_t LBA_0t15;
		uint8_t LBA_16t23;
		uint8_t device;
		uint32_t LBA_24t47; //upper 8 bits reserved, MBZ
		uint16_t count;
		uint16_t reserved0;
		uint32_t reserved1;
    } PACKED ;

	struct H2DRegisterFIS {
		/* 0x00  */uint8_t FISType;
		/* 0x01  */uint8_t byte1;
		/* 0x02  */uint8_t Command;
		/* 0x03  */uint8_t Features_0t7;
		/* 0x04  */uint8_t LBA_0t7;
		/* 0x05  */uint8_t LBA_8t15;
		/* 0x06  */uint8_t LBA_16t23;
		/* 0x07  */uint8_t device;
		/* 0x08  */uint8_t LBA_24t31;
		/* 0x09  */uint8_t LBA_32t39;
		/* 0x09  */uint8_t LBA_40t47;
		/* 0x0B  */uint8_t Features_8t15;
		/* 0x0C  */uint16_t Count;
		/* 0x0E  */uint8_t ICC;
		/* 0x0F  */uint8_t Control;
		/* 0x10  */uint16_t Auxiliary;
		/* 0x12  */uint16_t reserved0;
		/* 0x14  */
	} PACKED ;

    struct SetDeviceBitsFIS {
		uint8_t FISType;
		uint8_t byte1;
		uint8_t Status;
		uint8_t Error;
		uint32_t ProtocolSpecific;
    };

    struct ReceivedFIS {
		DMASetupFIS dmaSetup;
		uint8_t reserved0[0x20-0x1C];
		PIOSetupFIS pioSetup;
		uint8_t reserved1[0x40-0x34];
		D2HRegisterFIS D2HRegister;
		uint8_t reserved2[0x58-0x54];
		SetDeviceBitsFIS setDeviceBits;
		SATA::GenericFIS UnknownFIS;
		uint8_t reserved3[0xFF-0xA0];
    };

	struct CommandHeader {
		uint16_t dw0_lower;
		uint16_t PhysicalRegionDescriptorTableLength;
		uint32_t PhysicalRegionDescriptorByteCount;
		uint32_t CommandTableBaseAddress;
		uint32_t CommandTableBaseAddressUpper;
		uint32_t dw4;
		uint32_t dw5;
		uint32_t dw6;
		uint32_t dw7;
	};

	struct PhysicalRegionDescriptor {
		uint32_t PhysicalDataBaseAddress;
		uint32_t PhysicalDataBaseAddressUpper;
		uint32_t dw2;
		uint32_t dw3;
	};

	struct CommandTable {
		SATA::GenericFIS CommandFIS;
		SATA::ATAPICommand ACMD;
		uint8_t reserved0[0x80-0x50];
		PhysicalRegionDescriptor PhysicalRegionDescriptorTable[maxSupportedPhysicalRegionDescriptors];
	};

	struct PORT_EXTERNALS {
		union {
			struct {
				//?
				//? AHCI and/or SATA data
				//?
				ReceivedFIS receivedFIS;
				uint8_t padding0[1024-sizeof(ReceivedFIS)];
				CommandHeader CommandList[32];
				CommandTable CommandTables[32];
				//*
				//* TRINITY data
				//*
				HBA_T* HBAAddress;// Virtual address of the HBA this port belongs to
				PORT* HBAPortAddress;// Virtual address of the port registers for this port
				uint64_t Flags;
				PCIE_DEVICE_AHCI_CONTROLLER* PCIe;
			};
			//!
			//! leftover space
			//!
			uint8_t reserved[/*1MiB*/0x100000];
		};
	};

    enum class PortCheck {
        OK,
        NO_DISK
    };
}//! namespace AHCI
