/**
 * Created Date: Sunday January 8th 2023
 * Author: DefinitelyNotAGirl@github
 * -----
 * Last Modified: Sunday January 8th 2023 9:39:54 am
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
#pragma once
#include "../master.h"

struct PACKED RSDPDescriptor {
    char Signature[8];
    uint8_t Checksum;
    char OEMID[6];
    uint8_t Revision;
    uint32_t RsdtAddress;
};
struct PACKED RSDPDescriptor2 {
    char Signature[8];
    uint8_t Checksum;
    char OEMID[6];
    uint8_t Revision;
    uint32_t RsdtAddress;
    //revision 2.0
    uint32_t Length;
    uint64_t XsdtAddress;
    uint8_t ExtendedChecksum;
    uint8_t reserved[3];
};

struct PACKED ACPISDTHeader {
  //char Signature[4];
  uint32_t Signature;//+4
  uint32_t Length;//+4
  uint8_t Revision;//+1
  uint8_t Checksum;//+1
  char OEMID[6];//+6
  char OEMTableID[8];//+8
  uint32_t OEMRevision;//+4
  uint32_t CreatorID;//+4
  uint32_t CreatorRevision;//+4
};

struct PACKED RSDT {
  ACPISDTHeader header;
  uint32_t PointerToOtherSDT[1];
};

struct PACKED XSDT {
  ACPISDTHeader header;
  uint64_t PointerToOtherSDT[1];
};