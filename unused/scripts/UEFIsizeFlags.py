#!/usr/bin/env python3
# -*- coding:utf-8 -*-
###
# Created Date: Tuesday February 21st 2023
# Author: DefinitelyNotAGirl@github
# -----
# Last Modified: Tuesday February 21st 2023 4:52:58 am
# Modified By: DefinitelyNotAGirl@github (definitelynotagirl115199@gmail.com)
# -----
# Copyright (c) 2023 DefinitelyNotAGirl@github
# 
# Permission is hereby granted, free of charge, to any person
# obtaining a copy of this software and associated documentation
# files (the "Software"), to deal in the Software without
# restriction, including without limitation the rights to use, copy,
# modify, merge, publish, distribute, sublicense, and/or sell copies
# of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be
# included in all copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
# HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
# WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
# DEALINGS IN THE SOFTWARE.
###

import os

files   = ["GFS0.fs.dll" ,"ACPI.dll"  ,"AHCI.dll","IDE.dll"  ,"SATA.dll" ]
DEFNAME = ["GFS0"        ,"ACPI"      ,"AHCI"    ,"IDE"      ,"SATA"     ]
prefix = "GEOS_DISK_ROOT/ESP/GEOS/"

FLAGS=""

def filesize(filename):
    return os.path.getsize(filename)

for I in range(len(files)):
    size = str(filesize(prefix+files[I]))
    flag = " -D GEOS_FSIZE_" + DEFNAME[I] + "=" + size
    FLAGS+=flag

os.system("make --no-print-directory UEFI_compile_2 UEFI_SIZE_FLAG=\""+FLAGS+"\"");
    