#
# Created Date: Wednesday March 8th 2023
# Author: DefinitelyNotAGirl@github
# -----
# Last Modified: Tuesday April 25th 2023 10:46:08 am
# Modified By: DefinitelyNotAGirl@github (definitelynotagirl115169@gmail.com)
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

include ../make/util.mak

OUT=OUTPUT_NOT_CONFIGURED
build=build
OPT=-O0
DEPFLAGS_GPP=-MP -MD
DEPFLAGS_ASM=-M -MD

LD_ARGS=-T link.ld $(LDMISC)
NOWARN=-Wno-literal-suffix
GPP_ARGS=$(GPPMISC) $(NOWARN) $(OPT) $(DEPFLAGS_GPP) $(foreach D,$(INCDIRS),-I$(D)) -nostdlib -ffreestanding -fno-stack-protector
AS_ARGS=$(DEPFLAGS_ASM)

SOURCE_CPP:=$(wildcard src/*.cpp)
SOURCE_ASM:=$(wildcard src/*.s)
OBJECTS_CPP:=$(patsubst src/%.cpp,$(build)/%.o,$(SOURCE_CPP))
OBJECTS_ASM:=$(patsubst src/%.s,$(build)/%.o,$(SOURCE_ASM))
DEPFILES_CPP:=$(patsubst src/%.cpp,$(build)/%.d,$(SOURCE_CPP))
DEPFILES_ASM:=$(patsubst src/%.s,$(build)/%.d,$(SOURCE_ASM))

all: $(BINARY)

$(BINARY): $(OBJECTS_CPP) $(OBJECTS_ASM)
	$(LD) $(LD_ARGS) -o $@ $^
	$(info [BUILD] compiled module: $(shell basename $(CURDIR)))

bin/%.o: src/%.cpp
	$(GPP) $(GPP_ARGS) -c -o $@ $<
bin/%.o: src/%.s
	$(AS) $(AS_ARGS) -c -o $@ $<

# include dependencies
-include $(DEPFILES_CPP) $(DEPFILES_ASM)

clean:
	@-rm $(DEPFILES_CPP) $(DEPFILES_ASM) $(OBJECTS_CPP) $(OBJECTS_ASM) $(BINARY)