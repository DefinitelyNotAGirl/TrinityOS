/**
Created Date: Thursday February 15th 2024
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

#include <stdint.hxx>
#include <AHCI.hxx>
#include <PCIe.hxx>
#include <INIT.h>
#include <bits.hxx>

namespace AHCI {
	//*
	//* global variables
	//*
	uint64_t diskNum = 0;
	const uint64_t PRD_MAX_SECTORS = 16;//16 sectors of 512 bytes each, 8KiB total

	//*
	//* ahci disk read
	//*
	Disk::ReadReturn read(PORT_EXTERNALS* port,uint64_t dst,uint64_t StartingSector,uint64_t SectorCount)
	{
		volatile PORT* HBAPort = port->HBAPortAddress;
		volatile HBA_T* HBA = port->HBAAddress;
		//we'll just use cmd slot 0 for now and simply assume that its available (as it should be)
		volatile CommandHeader* cmdHeader = &port->CommandList[0];
		volatile CommandTable* cmdTbl = &port->CommandTables[0];
		volatile H2DRegisterFIS* cFIS = (H2DRegisterFIS*)&cmdTbl->CommandFIS;
		volatile ReceivedFIS* rFIS = &port->receivedFIS;
		//*
		//* prepare command header
		//*
		cmdHeader->dw0_lower = sizeof(H2DRegisterFIS)/sizeof(uint32_t); // command FIS size
		//?dw0_lower:6 (W) should already be set to 0
		cmdHeader->PhysicalRegionDescriptorTableLength = 1+(SectorCount/PRD_MAX_SECTORS); // PRDT entries count, 2MiB per descriptor
		//*
		//* prepare command table
		//*
		memset(cmdTbl,0,sizeof(CommandTable));
		uint64_t dst_phys;
		for(uint64_t i = 0;i<cmdHeader->PhysicalRegionDescriptorTableLength-1;i++)
		{
			dst_phys = getPhysicalAddress(dst,Kernel);
			cmdTbl->PhysicalRegionDescriptorTable[i].PhysicalDataBaseAddress = dst_phys;
			cmdTbl->PhysicalRegionDescriptorTable[i].PhysicalDataBaseAddressUpper = dst_phys>>32;
			cmdTbl->PhysicalRegionDescriptorTable[i].dw3 = (512*PRD_MAX_SECTORS)-1;
			cmdTbl->PhysicalRegionDescriptorTable[i].dw3 |= 1<<31;
			dst+=PRD_MAX_SECTORS*512;
		}
		dst_phys = getPhysicalAddress(dst,Kernel);
		cmdTbl->PhysicalRegionDescriptorTable[cmdHeader->PhysicalRegionDescriptorTableLength-1].PhysicalDataBaseAddress = dst_phys;
		cmdTbl->PhysicalRegionDescriptorTable[cmdHeader->PhysicalRegionDescriptorTableLength-1].PhysicalDataBaseAddressUpper = dst_phys>>32;
		cmdTbl->PhysicalRegionDescriptorTable[cmdHeader->PhysicalRegionDescriptorTableLength-1].dw3 = ((SectorCount%PRD_MAX_SECTORS)*512)-1;
		cmdTbl->PhysicalRegionDescriptorTable[cmdHeader->PhysicalRegionDescriptorTableLength-1].dw3 |= 1<<31;
		//*
		//* prepare command FIS
		//*
		cFIS->FISType = (uint8_t)(FIS_TYPE::REG_H2D);
		cFIS->byte1   |= 0x80; //? set C bit since we are issuing a command
		cFIS->Command  = 0xC8; //? DMA Read
		cFIS->LBA_0t7   = (uint8_t)StartingSector	   ;
		cFIS->LBA_8t15  = (uint8_t)StartingSector >> 8 ;
		cFIS->LBA_16t23 = (uint8_t)StartingSector >> 16;
		cFIS->LBA_24t31 = (uint8_t)StartingSector >> 24;
		cFIS->LBA_32t39 = (uint8_t)StartingSector >> 32;
		cFIS->LBA_40t47 = (uint8_t)StartingSector >> 40;
		cFIS->device = 64;//LBA mode (?)
		cFIS->Count = SectorCount;
		//*
		//* wait for no busy
		//*
		uint64_t spin = 0;
		while((HBAPort->TaskFileData & (1<<3 | 1<<7)) != 0)
		{
			if(spin == 10000000)
			{
				sysDBGint(
					0xdebac03,
					HBAPort->CommandAndStatus,
					HBAPort->TaskFileData,
					HBAPort->CommandIssue,
					HBA->GenericHostControl.InterruptStatus,
					HBA->GenericHostControl.GlobalHostControl
				);
				return Disk::ReadReturn::TIMEOUT;
			}
			spin++;
		}
		//*
		//* issue command
		//*
		HBAPort->CommandIssue |= 1;
		//?wait for completion
		spin = 0;
		while(true)
		{
			if((HBAPort->CommandIssue) == 0)// check if hardware cleared the command issue bit to 0
				break;
			if(HBAPort->InterruptStatus & 1<<30)//check for error
				goto AHCIReadReturnFailure;
			if(spin == 10000000)
			{
				sysDBGint(
					/* rdi */0xdebac01,
					/* rsi */HBAPort->CommandAndStatus,
					/* rdx */HBAPort->TaskFileData,
					/* rcx */HBAPort->CommandIssue,
					/* r8  */HBA->GenericHostControl.InterruptStatus,
					/* r9  */HBA->GenericHostControl.GlobalHostControl
				);
				sysDBGint(
					/* rdi */0xdebac02,
					/* rsi */HBAPort->SerialAtaStatus,
					/* rdx */HBAPort->SerialAtaControl,
					/* rcx */HBAPort->SerialAtaActive,
					/* r8  */HBAPort->SerialAtaError
				);
				return Disk::ReadReturn::TIMEOUT;
			}
			spin++;
		}
		if((HBAPort->InterruptStatus & 1<<30) != 0)//check for error
			goto AHCIReadReturnFailure;
		//
		//
		//
	    return Disk::ReadReturn::OK;
		AHCIReadReturnFailure:
		{
			sysDBGint(
				/* rdi */0xdebac01,
				/* rsi */HBAPort->CommandAndStatus,
				/* rdx */HBAPort->TaskFileData,
				/* rcx */HBAPort->CommandIssue,
				/* r8  */HBA->GenericHostControl.InterruptStatus,
				/* r9  */HBA->GenericHostControl.GlobalHostControl
			);
			sysDBGint(
				/* rdi */0xdebac02,
				/* rsi */HBAPort->SerialAtaStatus,
				/* rdx */HBAPort->SerialAtaControl,
				/* rcx */HBAPort->SerialAtaActive,
				/* r8  */HBAPort->SerialAtaError
			);
			return Disk::ReadReturn::FAILURE;
		}
	}

	//*
	//* check disk for TRINITY system
	//*
	void checkDisk(PORT_EXTERNALS* port)
	{
		//*
		//* check if disk is even present
		//*
		if(EXPR_GETBIT_00(port->Flags) == 0)
			return;//disk not present (Flags:0 is clear)
		//identify file system
	    Disk::ReadReturn status = read(port,0x3200000,0,2);
	    if(status != Disk::ReadReturn::OK)
	        sysDBGExit(ERROR_R15,ERROR_DISK_READ,(uint64_t)status);
	}

	//*
	//* check port for disk
	//*
	AHCI::PortCheck checkPort(PORT* port)
	{
	    if(port->SerialAtaStatus == 0)return PortCheck::NO_DISK;
	    diskNum++;
	    return PortCheck::OK;
	}

	//*
	//* initialize ahci controller
	//*
	const uint64_t CONTROLLER_REQUIRED_SPACE = sizeof(PORT_EXTERNALS)*32;
	void initializePort(volatile PORT* port,PORT_EXTERNALS* PortExternals,volatile HBA_T* HBAAddress,PCIE_DEVICE_AHCI_CONTROLLER* controller)
	{
		//*
		//* stop hba port
		//*
		port->CommandAndStatus &= ~(1<<0 | 1<<4); // clear ST and FRE
		//wait for hardware to clear FR and CR
		while((port->CommandAndStatus & (1<<14 | 1<<15)) != 0);
		//*
		//* initialize to our liking
		//*

		PORT_EXTERNALS* PhysPortExternals = (PORT_EXTERNALS*)getPhysicalAddress(PortExternals,Kernel);
		PortExternals->HBAAddress = HBAAddress;
		PortExternals->HBAPortAddress = port;
		PortExternals->PCIe = controller;
		if(checkPort(port) == PortCheck::OK)
			PortExternals->Flags |= 1;//set present bit
		port->FisPhysicalBaseAddress_LOW  = ((uint64_t)&PhysPortExternals->receivedFIS);
		port->FisPhysicalBaseAddress_HIGH = ((uint64_t)&PhysPortExternals->receivedFIS)>>32;
		port->CommandListPhysicalBaseAddress_LOW  = ((uint64_t)&PhysPortExternals->CommandList);
		port->CommandListPhysicalBaseAddress_HIGH = ((uint64_t)&PhysPortExternals->CommandList)>>32;
		for(uint64_t i = 0;i<32;i++)
		{
			PortExternals->CommandList[i].CommandTableBaseAddress 	   = ((uint64_t)&PhysPortExternals->CommandTables[i])    ;
			PortExternals->CommandList[i].CommandTableBaseAddressUpper = ((uint64_t)&PhysPortExternals->CommandTables[i])>>32;
		}
		//*
		//* start hba port
		//*
		//wait for hardware to clear CR
		while((port->CommandAndStatus & (1<<15)) != 0);
		port->CommandAndStatus |= (1<<0 | 1<<4);//set FRE and ST
		//request port to be put into active state
		port->CommandAndStatus |= 0x10000000;//set bit 28
		port->CommandAndStatus &= ~(1<<29 | 1<<30 | 1<<31);//clear bits 29-31
	}
	PORT_EXTERNALS* initializeController(PCIE_DEVICE_AHCI_CONTROLLER* controller)
	{
	    //?
	    //? configure controller and its ports to take up 36MiB in memory
	    //?
		PORT_EXTERNALS* PortExternals[32];
	    HBA_T* HBA;
	    {
	        uint32_t __ABAR = controller->Header.BAR5 & 0xFFFFE000;
	        uint64_t virt = getVirtualAddress(__ABAR,Kernel);
	        if(virt == UINT64_T_MAX)
	        {
	            if(setPage(TrinityPageType::MemoryMappedIO,__ABAR,mmioAddress,Kernel) != TrinitySetPageReturn::OK)
	                sysDBGExit(ERROR_R15,ERROR_SETPAGE);
	            virt = (mmioAddress)+(__ABAR%TRINITY_PAGE_SIZE);
	            mmioAddress+=TRINITY_PAGE_SIZE;
	        }
	        HBA = (HBA_T*)virt;
	    }
		//*
		//* initialize controller
		//*
		//PCI express
		controller->Header.Header.Command &= ~(1<<10); //clear CMD.ID (Interrupt disable)
		controller->Header.Header.Command |= (1<<1 | 1<<2); // set MSE and BME
		//ABAR
		HBA->GenericHostControl.GlobalHostControl |= 1<<31;//set GHC.AE (AHCI enable)
		HBA->GenericHostControl.GlobalHostControl |= 1<<1;// set GHC.IE (Interrupt enable)
		//*
	    //* allocate memory for port externals
		//*
		PORT_EXTERNALS* ret = (PORT_EXTERNALS*)mmioAddress;
		for(uint64_t i = 0;i<32;i+=2)
		{
			if(setPage(TrinityPageType::MemoryMappedIO,RandomPhysicalAddress,mmioAddress,Kernel) != TrinitySetPageReturn::OK)
	            sysDBGExit(ERROR_R15,ERROR_SETPAGE);
			uint64_t physAddr = getPhysicalAddress(mmioAddress,Kernel);
			PortExternals[i] = mmioAddress;
			PortExternals[i+1] = mmioAddress+0x100000;
			mmioAddress+=TRINITY_PAGE_SIZE;
		}
		//*
	    //* initialize ports
		//*
	    for(uint64_t i = 0;i<32;i++)
	        if((HBA->GenericHostControl.PortsImplemented & (1<<i)) != 0)
	            initializePort(&HBA->Ports[i],PortExternals[i],HBA,controller);
		return ret;
	}

	//*
	//* check controller for boot disk
	//*
	void checkController(PCIE_DEVICE_CONFIG* __controller)
	{
	    PCIE_DEVICE_AHCI_CONTROLLER* controller = (PCIE_DEVICE_AHCI_CONTROLLER*)__controller;
	    PORT_EXTERNALS* ports  = initializeController(controller);
		//*
	    //* check disks for boot signature
		//*
	    for(uint64_t i = 0;i<32;i++)
			checkDisk(&ports[i]);
	    sysDBGExit(0xdebac,0x3333,diskNum);
	}
}