# 
# File Generated by GEOS buildExec 
# Copyright (c) 2023 DefinitelyNotAGirl@github 
#
FUNCDIS_SOURCE_asm_asm=$(wildcard modules/FUNCDIS/src/*.asm)
FUNCDIS_OBJECTS_asm_asm=$(patsubst modules/FUNCDIS/src/%.asm,build/FUNCDIS/%.o,$(FUNCDIS_SOURCE_asm_asm))
FUNCDIS_DEPFILES_asm_asm=$(patsubst modules/FUNCDIS/src/%.asm,build/FUNCDIS/%.d,$(FUNCDIS_SOURCE_asm_asm))
FUNCDIS_SOURCE_asm_s=$(wildcard modules/FUNCDIS/src/*.s)
FUNCDIS_OBJECTS_asm_s=$(patsubst modules/FUNCDIS/src/%.s,build/FUNCDIS/%.o,$(FUNCDIS_SOURCE_asm_s))
FUNCDIS_DEPFILES_asm_s=$(patsubst modules/FUNCDIS/src/%.s,build/FUNCDIS/%.d,$(FUNCDIS_SOURCE_asm_s))
FUNCDIS_SOURCE_cpp_cpp=$(wildcard modules/FUNCDIS/src/*.cpp)
FUNCDIS_OBJECTS_cpp_cpp=$(patsubst modules/FUNCDIS/src/%.cpp,build/FUNCDIS/%.o,$(FUNCDIS_SOURCE_cpp_cpp))
FUNCDIS_DEPFILES_cpp_cpp=$(patsubst modules/FUNCDIS/src/%.cpp,build/FUNCDIS/%.d,$(FUNCDIS_SOURCE_cpp_cpp))
FUNCDIS_SOURCE_cpp_cxx=$(wildcard modules/FUNCDIS/src/*.cxx)
FUNCDIS_OBJECTS_cpp_cxx=$(patsubst modules/FUNCDIS/src/%.cxx,build/FUNCDIS/%.o,$(FUNCDIS_SOURCE_cpp_cxx))
FUNCDIS_DEPFILES_cpp_cxx=$(patsubst modules/FUNCDIS/src/%.cxx,build/FUNCDIS/%.d,$(FUNCDIS_SOURCE_cpp_cxx))
FUNCDIS_SOURCE_c_c=$(wildcard modules/FUNCDIS/src/*.c)
FUNCDIS_OBJECTS_c_c=$(patsubst modules/FUNCDIS/src/%.c,build/FUNCDIS/%.o,$(FUNCDIS_SOURCE_c_c))
FUNCDIS_DEPFILES_c_c=$(patsubst modules/FUNCDIS/src/%.c,build/FUNCDIS/%.d,$(FUNCDIS_SOURCE_c_c))
build/FUNCDIS/%.o: modules/FUNCDIS/src/%.asm
	@as -M -MD -c -o $@ $<
	$(info  	AS	$<)
build/FUNCDIS/%.o: modules/FUNCDIS/src/%.s
	@as -M -MD -c -o $@ $<
	$(info  	AS	$<)
build/FUNCDIS/%.o: modules/FUNCDIS/src/%.cpp
	@g++ -O0 -fno-rtti -fno-exceptions -nostdlib -ffreestanding -fno-stack-protector -fno-builtin -nostartfiles -Wunreachable-code -std=c++20 -Wno-literal-suffix -Wno-pointer-arith -MP -MD -Imodules/klib/inc/ -Iinc/ -Ishared/ -Imodules/FUNCDIS/inc -march=x86-64 -c -o $@ $<
	$(info 	C++	$<)
build/FUNCDIS/%.o: modules/FUNCDIS/src/%.cxx
	@g++ -O0 -fno-rtti -fno-exceptions -nostdlib -ffreestanding -fno-stack-protector -fno-builtin -nostartfiles -Wunreachable-code -std=c++20 -Wno-literal-suffix -Wno-pointer-arith -MP -MD -Imodules/klib/inc/ -Iinc/ -Ishared/ -Imodules/FUNCDIS/inc -march=x86-64 -c -o $@ $<
	$(info 	C++	$<)
build/FUNCDIS/%.o: modules/FUNCDIS/src/%.c
	@gcc -Wunreachable-code -Imodules/klib/inc/ -Iinc/ -Ishared/ -Imodules/FUNCDIS/inc -march=x86-64 -c -o $@ $<
	$(info  	CC	$<)
m-FUNCDIS-clean:
	@-rm -r build/FUNCDIS/*.o
	$(info  	DELETE	build/FUNCDIS/*.o)
	@-rm -r build/FUNCDIS/*.d
	$(info  	DELETE	build/FUNCDIS/*.d)
m-FUNCDIS: out/kernel/FUNCDIS.elf64
out/kernel/FUNCDIS.elf64:  $(FUNCDIS_OBJECTS_asm_asm) $(FUNCDIS_OBJECTS_asm_s) $(FUNCDIS_OBJECTS_cpp_cpp) $(FUNCDIS_OBJECTS_cpp_cxx) $(FUNCDIS_OBJECTS_c_c)
	@ld -nostdlib -T LDS/FUNCDIS.ld  $(FUNCDIS_OBJECTS_asm_asm) $(FUNCDIS_OBJECTS_asm_s) $(FUNCDIS_OBJECTS_cpp_cpp) $(FUNCDIS_OBJECTS_cpp_cxx) $(FUNCDIS_OBJECTS_c_c)  $(klib_OBJECTS_asm_asm) $(klib_OBJECTS_asm_s) $(klib_OBJECTS_cpp_cpp) $(klib_OBJECTS_cpp_cxx) $(klib_OBJECTS_c_c) -o out/kernel/FUNCDIS.elf64
	$(info  	LD	$@)
	@objcopy out/kernel/FUNCDIS.elf64 --remove-section text_klib --remove-section rodata_klib --remove-section data_klib --remove-section bss_klib
	$(info  	OBJCOPY	$@)
-include $(FUNCDIS_DEPFILES_asm_asm)
-include $(FUNCDIS_DEPFILES_asm_s)
-include $(FUNCDIS_DEPFILES_cpp_cpp)
-include $(FUNCDIS_DEPFILES_cpp_cxx)
-include $(FUNCDIS_DEPFILES_c_c)
