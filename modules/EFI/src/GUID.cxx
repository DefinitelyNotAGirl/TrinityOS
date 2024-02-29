/*
 * Created Date: Tuesday June 27th 2023
 * Author: DefinitelyNotAGirl@github
 * -----
 * Last Modified: Tuesday June 27th 2023 2:20:11 am
 * Modified By: DefinitelyNotAGirl@github (definitelynotagirl115169@gmail.com)
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

#include <Uefi.h>
#include <Guid/Acpi.h>
#include <Guid/Apriori.h>
#include <Guid/AprioriFileName.h>
#include <Guid/Btt.h>
#include <Guid/CapsuleReport.h>
#include <Guid/Cper.h>
#include <Guid/DebugImageInfoTable.h>
#include <Guid/DxeServices.h>
#include <Guid/EventGroup.h>
#include <Guid/EventLegacyBios.h>
#include <Guid/FileInfo.h>
#include <Guid/FileSystemInfo.h>
#include <Guid/FileSystemVolumeLabelInfo.h>
#include <Guid/FirmwareContentsSigned.h>
#include <Guid/FirmwareFileSystem2.h>
#include <Guid/FirmwareFileSystem3.h>
#include <Guid/FmpCapsule.h>
#include <Guid/GlobalVariable.h>
#include <Guid/Gpt.h>
#include <Guid/GraphicsInfoHob.h>
#include <Guid/HardwareErrorVariable.h>
#include <Guid/HiiFormMapMethodGuid.h>
#include <Guid/HiiKeyBoardLayout.h>
#include <Guid/HiiPlatformSetupFormset.h>
#include <Guid/HobList.h>
#include <Guid/ImageAuthentication.h>
#include <Guid/MdePkgTokenSpace.h>
#include <Guid/MemoryAllocationHob.h>
#include <Guid/MemoryAttributesTable.h>
#include <Guid/MemoryOverwriteControl.h>
#include <Guid/Mps.h>
#include <Guid/PcAnsi.h>
#include <Guid/PropertiesTable.h>
#include <Guid/SalSystemTable.h>
#include <Guid/SmBios.h>
#include <Guid/StatusCodeDataTypeId.h>
#include <Guid/SystemResourceTable.h>
#include <Guid/VectorHandoffTable.h>
#include <Guid/WinCertificate.h>

EFI_GUID GUID_ACPI                   = ACPI_TABLE_GUID;
EFI_GUID GUID_SAL_SYSTEM             = SAL_SYSTEM_TABLE_GUID;
EFI_GUID GUID_SMBIOS                 = SMBIOS_TABLE_GUID;
EFI_GUID GUID_SMBIOS3                = SMBIOS3_TABLE_GUID;
EFI_GUID GUID_MPS                    = MPS_TABLE_GUID;
EFI_GUID GUID_PROPERTIES_TABLE       = EFI_PROPERTIES_TABLE_GUID;