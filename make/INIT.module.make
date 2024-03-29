# 
# File Generated by GEOS buildExec 
# Copyright (c) 2023 DefinitelyNotAGirl@github 
#
INIT_SOURCE_asm_asm=$(wildcard modules/INIT/src/*.asm)
INIT_OBJECTS_asm_asm=$(patsubst modules/INIT/src/%.asm,build/INIT/%.o,$(INIT_SOURCE_asm_asm))
INIT_DEPFILES_asm_asm=$(patsubst modules/INIT/src/%.asm,build/INIT/%.d,$(INIT_SOURCE_asm_asm))
INIT_SOURCE_asm_s=$(wildcard modules/INIT/src/*.s)
INIT_OBJECTS_asm_s=$(patsubst modules/INIT/src/%.s,build/INIT/%.o,$(INIT_SOURCE_asm_s))
INIT_DEPFILES_asm_s=$(patsubst modules/INIT/src/%.s,build/INIT/%.d,$(INIT_SOURCE_asm_s))
INIT_SOURCE_cpp_cpp=$(wildcard modules/INIT/src/*.cpp)
INIT_OBJECTS_cpp_cpp=$(patsubst modules/INIT/src/%.cpp,build/INIT/%.o,$(INIT_SOURCE_cpp_cpp))
INIT_DEPFILES_cpp_cpp=$(patsubst modules/INIT/src/%.cpp,build/INIT/%.d,$(INIT_SOURCE_cpp_cpp))
INIT_SOURCE_cpp_cxx=$(wildcard modules/INIT/src/*.cxx)
INIT_OBJECTS_cpp_cxx=$(patsubst modules/INIT/src/%.cxx,build/INIT/%.o,$(INIT_SOURCE_cpp_cxx))
INIT_DEPFILES_cpp_cxx=$(patsubst modules/INIT/src/%.cxx,build/INIT/%.d,$(INIT_SOURCE_cpp_cxx))
INIT_SOURCE_c_c=$(wildcard modules/INIT/src/*.c)
INIT_OBJECTS_c_c=$(patsubst modules/INIT/src/%.c,build/INIT/%.o,$(INIT_SOURCE_c_c))
INIT_DEPFILES_c_c=$(patsubst modules/INIT/src/%.c,build/INIT/%.d,$(INIT_SOURCE_c_c))
build/INIT/%.o: modules/INIT/src/%.asm
	@as -M -MD -c -o $@ $<
	$(info  	AS	$<)
build/INIT/%.o: modules/INIT/src/%.s
	@as -M -MD -c -o $@ $<
	$(info  	AS	$<)
build/INIT/%.o: modules/INIT/src/%.cpp
	@g++ -O0 -fno-rtti -fno-exceptions -nostdlib -ffreestanding -fno-stack-protector -fno-builtin -nostartfiles -Wunreachable-code -std=c++20 -Wno-literal-suffix -Wno-pointer-arith -MP -MD -fpermissive -Wno-int-to-pointer-cast -Wno-pointer-to-int-cast -Iinc/ -Ishared/ -Imodules/INIT/inc -march=x86-64 -c -o $@ $<
	$(info 	C++	$<)
build/INIT/%.o: modules/INIT/src/%.cxx
	@g++ -O0 -fno-rtti -fno-exceptions -nostdlib -ffreestanding -fno-stack-protector -fno-builtin -nostartfiles -Wunreachable-code -std=c++20 -Wno-literal-suffix -Wno-pointer-arith -MP -MD -fpermissive -Wno-int-to-pointer-cast -Wno-pointer-to-int-cast -Iinc/ -Ishared/ -Imodules/INIT/inc -march=x86-64 -c -o $@ $<
	$(info 	C++	$<)
build/INIT/%.o: modules/INIT/src/%.c
	@gcc -Wunreachable-code -Iinc/ -Ishared/ -Imodules/INIT/inc -march=x86-64 -c -o $@ $<
	$(info  	CC	$<)
m-INIT-clean:
	@-rm -r build/INIT/*.o
	$(info  	DELETE	build/INIT/*.o)
	@-rm -r build/INIT/*.d
	$(info  	DELETE	build/INIT/*.d)
m-INIT: out/kernel/INIT.elf64
out/kernel/INIT.elf64:  $(INIT_OBJECTS_asm_asm) $(INIT_OBJECTS_asm_s) $(INIT_OBJECTS_cpp_cpp) $(INIT_OBJECTS_cpp_cxx) $(INIT_OBJECTS_c_c)
	@ld -nostdlib -T LDS/INIT.ld  $(INIT_OBJECTS_asm_asm) $(INIT_OBJECTS_asm_s) $(INIT_OBJECTS_cpp_cpp) $(INIT_OBJECTS_cpp_cxx) $(INIT_OBJECTS_c_c)  $(klib_OBJECTS_asm_asm) $(klib_OBJECTS_asm_s) $(klib_OBJECTS_cpp_cpp) $(klib_OBJECTS_cpp_cxx) $(klib_OBJECTS_c_c) -o out/kernel/INIT.elf64
	$(info  	LD	$@)
	@objcopy out/kernel/INIT.elf64 --remove-section text_klib --remove-section rodata_klib --remove-section data_klib --remove-section bss_klib
	$(info  	OBJCOPY	$@)
-include $(INIT_DEPFILES_asm_asm)
-include $(INIT_DEPFILES_asm_s)
-include $(INIT_DEPFILES_cpp_cpp)
-include $(INIT_DEPFILES_cpp_cxx)
-include $(INIT_DEPFILES_c_c)
