#
# mykernel/cpp/Makefile
#
# Copyright (C) 2017 - 2021 bzt (bztsrc@gitlab)
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
# This file is part of the BOOTBOOT Protocol package.
# @brief An example Makefile for sample kernel
#
#

#NOTE: this is a fairly modified version of the original, for the original source go to gitlab

M=BIOS
IMG=geos.img
RUN=./scripts/run64_$(M).sh

GCC=/git/GEOS_CROSSCOMPILER/bin/x86_64-elf-gcc
CPP=/git/GEOS_CROSSCOMPILER/bin/x86_64-elf-g++
LD=/git/GEOS_CROSSCOMPILER/bin/x86_64-elf-ld
STRIP=/git/GEOS_CROSSCOMPILER/bin/x86_64-elf-strip
READELF=/git/GEOS_CROSSCOMPILER/bin/x86_64-elf-readelf
OBJCOPY=/git/GEOS_CROSSCOMPILER/bin/x86_64-elf-objcopy

#GCC=gcc
#CPP=g++
#LD=ld
#STRIP=strip
#READELF=readelf
#OBJCOPY=objcopy
#EFI_MAIN=BOOTX64.EFI

BUILD_NUMBER_FILE=VERSION_FILE
BUILD_NUM := $(shell cat ${BUILD_NUMBER_FILE})
BUILD_NUMBER_LDFLAGS = --defsym __BUILD_DATE=$$(date +'%Y%m%d')
BUILD_NUMBER_LDFLAGS += --defsym __BUILD_NUMBER=$$(cat $(BUILD_NUMBER_FILE))
BUILD_NUM_FLAG = -D GEOS_BUILD_NUM=\"$(BUILD_NUM)\"

include loopback.make.mdep
MNT_0 = ./mnt/fs0
MNT_1 = ./mnt/fs1

OUT=./build

NOWARN = -Wno-multichar -Wno-unused-variable -Wno-literal-suffix
CPPFLAGS = -Wall -fpic -ffreestanding -fno-stack-protector -fno-exceptions -fno-rtti -nostdinc -nostdlib -I../../dist/ -fpermissive -I"/git/GEOS/stdlibc++/" -ffixed-r15 $(NOWARN)
LDFLAGS = -nostdlib -n
LDFLAGS += $(BUILD_NUMBER_LDFLAGS)
CPPFLAGS += $(BUILD_NUM_FLAG)

#EFI_LINK = -fPIC -shared -Bsymbolic -LUEFI/x86_64/lib -LUEFI/x86_64/gnuefi -TUEFI/elf_x86_64_efi.lds UEFI/x86_64/gnuefi/crt0-efi-x86_64.o -lgnuefi -lefi
#CPPFLAGS_EFI = -fno-stack-check -fshort-wchar -maccumulate-outgoing-args
#LDFLAGS += $(EFI_LINK)
#CPPFLAGS += $(CPPFLAGS_EFI)

STRIPFLAGS = -s -K mmio -K fb -K bootboot -K environment -K initstack

all: compile updateRootFS

rebooted: init_loop

run: code_clean all
	$(RUN)

init_mount:
	-mount $(DEV_LOOP1) $(MNT_1)

init_loop:
	-losetup $(DEV_LOOP0) $(IMG)
	-losetup $(DEV_LOOP1) $(IMG) -o 1048576

init_wipeimg:
	dd if=/dev/zero of=$(IMG) bs=512 count=131072
	echo -e "o\nn\np\n1\n2048\n\na\nw\n" | fdisk $(IMG)

fs_init:
	mkfs.ext4 $(DEV_LOOP1)

grub_init:
	grub-install --root-directory=$(MNT_1) --no-floppy --modules="normal part_msdos ext2 multiboot" $(DEV_LOOP0)

init: init_wipeimg init_loop fs_init grub_init init_mount

updateRootFS: fillRootFS copyRootFS

fillRootFS:
	cp -rf stdlibc/* geosfsroot/sys/inc
	cp -rf stdlibc++/* geosfsroot/sys/inc
	cp -rf src/* geosfsroot/geos/src_backup
	cp -f grub.cfg geosfsroot/boot/grub/grub.cfg

copyRootFS:
	cp -rf geosfsroot/* $(MNT_1)

wipeRootFS:
	rm -r geosfsroot

structRootFS:
	mkdir geosfsroot
	mkdir geosfsroot/boot
	mkdir geosfsroot/boot/grub
	mkdir geosfsroot/geos
	mkdir geosfsroot/geos/src
	mkdir geosfsroot/geos/src_backup
	mkdir geosfsroot/sys
	mkdir geosfsroot/sys/inc

mkRootFS: wipeRootFS structRootFS fillRootFS copyRootFS
	
compile: src/kernel.cpp
	scripts/builtnum.sh
	nasm -f elf64 src/GEOS/asm/asm_main.asm -o build/kernel_2.o
	$(CPP) $(CPPFLAGS) -mno-red-zone -c src/kernel.cpp -o $(OUT)/kernel.o
	$(LD) $(LDFLAGS) $(OUT)/kernel_2.o $(OUT)/kernel.o -o $(OUT)/geos.elf

code_clean:
	rm *.o *.elf || true

clean: code_clean
	rm *.txt *.iso *.img *.efi *.EFI || true
