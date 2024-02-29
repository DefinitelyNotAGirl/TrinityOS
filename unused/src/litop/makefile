#
# Created Date: Monday February 20th 2023
# Author: DefinitelyNotAGirl@github
# -----
# Last Modified: Wednesday March 22nd 2023 10:20:53 pm
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
#

GPP=/git/GEOS_CROSSCOMPILER/bin/x86_64-elf-g++

OPT=-O0

GPP_ARGS= $(OPT) -c -nostdlib -ffreestanding -fno-stack-protector

all:
	$(GPP) $(GPP_ARGS) litop.cpp -o litop.o
	cp litop.o ../../lib/litop.o
	cp litop.h ../../lib/inc/litop

clean:
	-rm litop.o
