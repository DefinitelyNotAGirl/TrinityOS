#
# Created Date: Wednesday May 31st 2023
# Author: DefinitelyNotAGirl@github
# -----
# Last Modified: Tuesday July 18th 2023 4:41:54 pm
# Modified By: Lilith (definitelynotagirl115169@gmail.com)
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

EFI_SOURCE_asm_asm=$(wildcard modules/EFI/src/*.asm)
EFI_OBJECTS_asm_asm=$(patsubst modules/EFI/src/%.asm,build/EFI/%.o,$(EFI_SOURCE_asm_asm))
EFI_DEPFILES_asm_asm=$(patsubst modules/EFI/src/%.asm,build/EFI/%.d,$(EFI_SOURCE_asm_asm))
EFI_SOURCE_asm_s=$(wildcard modules/EFI/src/*.s)
EFI_OBJECTS_asm_s=$(patsubst modules/EFI/src/%.s,build/EFI/%.o,$(EFI_SOURCE_asm_s))
EFI_DEPFILES_asm_s=$(patsubst modules/EFI/src/%.s,build/EFI/%.d,$(EFI_SOURCE_asm_s))
EFI_SOURCE_cpp_cpp=$(wildcard modules/EFI/src/*.cpp)
EFI_OBJECTS_cpp_cpp=$(patsubst modules/EFI/src/%.cpp,build/EFI/%.o,$(EFI_SOURCE_cpp_cpp))
EFI_DEPFILES_cpp_cpp=$(patsubst modules/EFI/src/%.cpp,build/EFI/%.d,$(EFI_SOURCE_cpp_cpp))
EFI_SOURCE_cpp_cxx=$(wildcard modules/EFI/src/*.cxx)
EFI_OBJECTS_cpp_cxx=$(patsubst modules/EFI/src/%.cxx,build/EFI/%.o,$(EFI_SOURCE_cpp_cxx))
EFI_DEPFILES_cpp_cxx=$(patsubst modules/EFI/src/%.cxx,build/EFI/%.d,$(EFI_SOURCE_cpp_cxx))
EFI_SOURCE_c_c=$(wildcard modules/EFI/src/*.c)
EFI_OBJECTS_c_c=$(patsubst modules/EFI/src/%.c,build/EFI/%.o,$(EFI_SOURCE_c_c))
EFI_DEPFILES_c_c=$(patsubst modules/EFI/src/%.c,build/EFI/%.d,$(EFI_SOURCE_c_c))
EFI_SOURCE_c2_c2=$(wildcard modules/EFI/src/*.c2)
EFI_OBJECTS_c2_c2=$(patsubst modules/EFI/src/%.c2,build/EFI/%.o,$(EFI_SOURCE_c2_c2))
EFI_DEPFILES_c2_c2=$(patsubst modules/EFI/src/%.c2,build/EFI/%.d,$(EFI_SOURCE_c2_c2))

EFI_LIBS=../EFI/lib
EFI_HEADERS=-I../EFI/inc -I../EFI/inc/X64 -I../EFI/inc/Protocol -I../EFI/inc/Guid

CLANG_NOSTDLIBCXX=-nostdinc++ -nogpulib -nobuiltininc -nostdlib
CLANG_NOSTDLIBC=-nostdinc -nogpulib -nobuiltininc -nostdlib

cc2 = ../c+=2/cp2

build/EFI/%.o: build/EFI/%.s
	clang -target x86_64-unknown-windows -c -o $@ $<
	$(info 	AS	$<)

build/EFI/%.s: modules/EFI/src/%.c2
	@$(cc2) -s --fcpl 0 --fno-stdlib --fno-libc --ffreestanding -MD -NOD -Imodules/EFI/inc -Imodules/klib/inc/c2 -o $@o $<
	$(info 	cp2	$<)

build/EFI/%.o: modules/EFI/src/%.cpp
	@clang++ -c -target x86_64-unknown-windows -Wno-multichar -Wno-language-extension-token -Wno-microsoft-enum-value -Wno-c99-extensions -pedantic $(CLANG_NOSTDLIBCXX) -mno-red-zone -MP -MD -fshort-wchar -fno-stack-check -fno-stack-protector -fno-rtti -fno-exceptions -ffreestanding -I modules/EFI/inc $(EFI_HEADERS) -o $@ $<
	$(info 	C++	$<)
build/EFI/%.o: modules/EFI/src/%.cxx
	@clang++ -c -target x86_64-unknown-windows -Wno-multichar -Wno-language-extension-token -Wno-microsoft-enum-value -Wno-c99-extensions -pedantic $(CLANG_NOSTDLIBCXX) -mno-red-zone -MP -MD -fshort-wchar -fno-stack-check -fno-stack-protector -fno-rtti -fno-exceptions -ffreestanding -Iinc -I modules/EFI/inc $(EFI_HEADERS) -o $@ $<
	$(info 	C++	$<)
build/EFI/%.o: modules/EFI/src/%.c
	@clang -c -target x86_64-unknown-windows -Wno-multichar -Wno-language-extension-token -Wno-microsoft-enum-value -Wno-c99-extensions -pedantic $(CLANG_NOSTDLIBC) -mno-red-zone -MP -MD -fshort-wchar -fno-stack-check -fno-stack-protector -fno-rtti -fno-exceptions -ffreestanding -I modules/EFI/inc $(EFI_HEADERS) -o $@ $<
	$(info  CC	$<)
build/EFI/%.o: modules/EFI/src/%.s
	@clang -target x86_64-unknown-windows -c -o $@ $<
	$(info  AS	$<)

m-EFI-clean:
	@-rm -r build/EFI/*.o
	$(info  	DELETE	build/EFI/*.o)
	@-rm -r build/EFI/*.d
	$(info  	DELETE	build/EFI/*.d)
	@-rm -r build/EFI/*.SO
	$(info  	DELETE	build/EFI/*.SO)

out/kernel/BOOTX64.EFI:  $(EFI_OBJECTS_c2_c2) $(EFI_OBJECTS_asm_asm) $(EFI_OBJECTS_asm_s) $(EFI_OBJECTS_cpp_cpp) $(EFI_OBJECTS_cpp_cxx) $(EFI_OBJECTS_c_c)
	@lld-link /entry:main /subsystem:efi_application /nodefaultlib $(EFI_OBJECTS_asm_asm) $(EFI_OBJECTS_asm_s) $(EFI_OBJECTS_cpp_cpp) $(EFI_OBJECTS_cpp_cxx) $(EFI_OBJECTS_c_c) $(EFI_OBJECTS_c2_c2) /out:out/kernel/BOOTX64.EFI
	$(info  LD	$@)

m-EFI: out/kernel/BOOTX64.EFI
