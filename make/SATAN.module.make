# 
# File Generated by GEOS buildExec 
# Copyright (c) 2023 DefinitelyNotAGirl@github 
#
SATAN_SOURCE_asm_asm=$(wildcard modules/SATAN/src/*.asm)
SATAN_OBJECTS_asm_asm=$(patsubst modules/SATAN/src/%.asm,build/SATAN/%.o,$(SATAN_SOURCE_asm_asm))
SATAN_DEPFILES_asm_asm=$(patsubst modules/SATAN/src/%.asm,build/SATAN/%.d,$(SATAN_SOURCE_asm_asm))
SATAN_SOURCE_asm_s=$(wildcard modules/SATAN/src/*.s)
SATAN_OBJECTS_asm_s=$(patsubst modules/SATAN/src/%.s,build/SATAN/%.o,$(SATAN_SOURCE_asm_s))
SATAN_DEPFILES_asm_s=$(patsubst modules/SATAN/src/%.s,build/SATAN/%.d,$(SATAN_SOURCE_asm_s))
SATAN_SOURCE_cpp_cpp=$(wildcard modules/SATAN/src/*.cpp)
SATAN_OBJECTS_cpp_cpp=$(patsubst modules/SATAN/src/%.cpp,build/SATAN/%.o,$(SATAN_SOURCE_cpp_cpp))
SATAN_DEPFILES_cpp_cpp=$(patsubst modules/SATAN/src/%.cpp,build/SATAN/%.d,$(SATAN_SOURCE_cpp_cpp))
SATAN_SOURCE_cpp_cxx=$(wildcard modules/SATAN/src/*.cxx)
SATAN_OBJECTS_cpp_cxx=$(patsubst modules/SATAN/src/%.cxx,build/SATAN/%.o,$(SATAN_SOURCE_cpp_cxx))
SATAN_DEPFILES_cpp_cxx=$(patsubst modules/SATAN/src/%.cxx,build/SATAN/%.d,$(SATAN_SOURCE_cpp_cxx))
SATAN_SOURCE_c_c=$(wildcard modules/SATAN/src/*.c)
SATAN_OBJECTS_c_c=$(patsubst modules/SATAN/src/%.c,build/SATAN/%.o,$(SATAN_SOURCE_c_c))
SATAN_DEPFILES_c_c=$(patsubst modules/SATAN/src/%.c,build/SATAN/%.d,$(SATAN_SOURCE_c_c))
build/SATAN/%.o: modules/SATAN/src/%.asm
	@as -M -MD -c -o $@ $<
	$(info  	AS	$<)
build/SATAN/%.o: modules/SATAN/src/%.s
	@as -M -MD -c -o $@ $<
	$(info  	AS	$<)
build/SATAN/%.o: modules/SATAN/src/%.cpp
	@g++ -O0 -fno-rtti -fno-exceptions -nostdlib -ffreestanding -fno-stack-protector -fno-builtin -nostartfiles -Wunreachable-code -std=c++20 -Wno-literal-suffix -Wno-pointer-arith -MP -MD -Imodules/klib/inc/ -Iinc/ -Ishared/ -Imodules/SATAN/inc -march=x86-64 -c -o $@ $<
	$(info 	C++	$<)
build/SATAN/%.o: modules/SATAN/src/%.cxx
	@g++ -O0 -fno-rtti -fno-exceptions -nostdlib -ffreestanding -fno-stack-protector -fno-builtin -nostartfiles -Wunreachable-code -std=c++20 -Wno-literal-suffix -Wno-pointer-arith -MP -MD -Imodules/klib/inc/ -Iinc/ -Ishared/ -Imodules/SATAN/inc -march=x86-64 -c -o $@ $<
	$(info 	C++	$<)
build/SATAN/%.o: modules/SATAN/src/%.c
	@gcc -Wunreachable-code -Imodules/klib/inc/ -Iinc/ -Ishared/ -Imodules/SATAN/inc -march=x86-64 -c -o $@ $<
	$(info  	CC	$<)
m-SATAN-clean:
	@-rm -r build/SATAN/*.o
	$(info  	DELETE	build/SATAN/*.o)
	@-rm -r build/SATAN/*.d
	$(info  	DELETE	build/SATAN/*.d)
m-SATAN: out/SATAN.elf64
out/SATAN.elf64:  $(SATAN_OBJECTS_asm_asm) $(SATAN_OBJECTS_asm_s) $(SATAN_OBJECTS_cpp_cpp) $(SATAN_OBJECTS_cpp_cxx) $(SATAN_OBJECTS_c_c)
	@ld -nostdlib -T LDS/SATAN.ld  $(SATAN_OBJECTS_asm_asm) $(SATAN_OBJECTS_asm_s) $(SATAN_OBJECTS_cpp_cpp) $(SATAN_OBJECTS_cpp_cxx) $(SATAN_OBJECTS_c_c)  $(klib_OBJECTS_asm_asm) $(klib_OBJECTS_asm_s) $(klib_OBJECTS_cpp_cpp) $(klib_OBJECTS_cpp_cxx) $(klib_OBJECTS_c_c) -o out/SATAN.elf64
	$(info  	LD	$@)
	@objcopy out/SATAN.elf64 --remove-section text_klib --remove-section rodata_klib --remove-section data_klib --remove-section bss_klib
	$(info  	OBJCOPY	$@)
-include $(SATAN_DEPFILES_asm_asm)
-include $(SATAN_DEPFILES_asm_s)
-include $(SATAN_DEPFILES_cpp_cpp)
-include $(SATAN_DEPFILES_cpp_cxx)
-include $(SATAN_DEPFILES_c_c)