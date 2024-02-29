/*
 * Created Date: Tuesday June 27th 2023
 * Author: DefinitelyNotAGirl@github
 * -----
 * Last Modified: Tuesday June 27th 2023 2:52:23 am
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
#include <main.h>
#include <IndustryStandard/Acpi62.h>

void readACPI_r1(void* RSDP);
void readACPI_r2(void* RSDP);

void readACPI()
{
    EFI_ACPI_6_2_ROOT_SYSTEM_DESCRIPTION_POINTER* acpi_table = (EFI_ACPI_6_2_ROOT_SYSTEM_DESCRIPTION_POINTER*)econf.ACPI;
    if(acpi_table == NULL)
    {
        print(u"ERROR: acpi config table is nullptr");
        while(1);
    }

    if(acpi_table->Signature == EFI_ACPI_6_2_ROOT_SYSTEM_DESCRIPTION_POINTER_SIGNATURE)
        print(u"RSDT found! Finally, inner peace...\n\r");
    else
    {
        print(u"ERROR: acpi table signature is invalid");
        while(1);
    }

    if(acpi_table->Revision == 0x00)
        readACPI_r1(acpi_table);
    else if(acpi_table->Revision == 0x02)
        readACPI_r2(acpi_table);
    else
    {
        print(u"ERROR: invalid acpi revision!");
        tripleFault(acpi_table->Revision);
        while(1);
    }
}