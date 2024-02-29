#!/usr/bin/env python3
# -*- coding:utf-8 -*-
###
# Created Date: Wednesday March 8th 2023
# Author: DefinitelyNotAGirl@github
# -----
# Last Modified: Wednesday March 8th 2023 11:57:37 pm
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
import json
import sys

rootdir = sys.argv[1]
diskroot = sys.argv[2]
mod = sys.argv[3]
config = []
prefix = "modules/"

with open("../../BUILD_CONFIG/modules.json") as f:
    config = json.load(f)

for I in config[mod]:
    dstdir = ""
    if(I.startswith("efi")):
        dstdir="ESP/GEOS"
    elif(I.startswith("sys")):
        dstdir="GFS0MSP/sys/dll"
    src = rootdir+"/"+mod+"/bin/a.elf64"
    dst = diskroot+"/"+dstdir+"/"+mod
    print("[FILESYSTEM] "+mod + " ==> "+"("+I+") "+  dst)
    if(os.path.isfile(src)):
        os.system("cp "+src+" "+dst)
    else:
        print("[FILESYSTEM] module: "+mod+" does not exit!")