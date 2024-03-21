# 
# Created Date: Friday November 25th 2022
# Author: DefinitelyNotAGirl@github
# -----
# Last Modified: Friday November 25th 2022 3:33:05 pm
# Modified By: DefinitelyNotAGirl@github (definitelynotagirl115199@gmail.com)
# -----
# Copyright (c) 2022 DefinitelyNotAGirl@github
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

all: modinc-all m-all m-EFI

clean: m-all-clean

INSTALL_DIR="../geosTestEnv/content"

install:
	@cp out/kernel/INIT.elf64 $(INSTALL_DIR)/TrinityOS/kernel/
	@cp out/kernel/BOOTX64.EFI $(INSTALL_DIR)/EFI/BOOT/BOOTX64.EFI

CODE_FILE_SELECT=./modules/**/src ./modules/**/inc shared -type f \( -iname \*.cxx -o -iname \*.cpp -o -iname \*.c2 -o -iname \*.cp2 -o -iname \*.c -o -iname \*.h -o -iname \*.hpp -o -iname \*.s -o -iname \*.asm -o -iname \*.hxx \)

countLines:
	@find $(CODE_FILE_SELECT) -exec cat {} \; | wc -l

listCodeFiles:
	@find $(CODE_FILE_SELECT) -print

include make/include.make
include make/EFI.make