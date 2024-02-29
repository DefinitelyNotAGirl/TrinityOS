# 
# File Generated by GEOS buildExec 
# Copyright (c) 2023 DefinitelyNotAGirl@github 
#
gfs0.fs_SOURCE_asm_asm=$(wildcard modules/gfs0.fs/src/*.asm)
gfs0.fs_OBJECTS_asm_asm=$(patsubst modules/gfs0.fs/src/%.asm,build/gfs0.fs/%.o,$(gfs0.fs_SOURCE_asm_asm))
gfs0.fs_DEPFILES_asm_asm=$(patsubst modules/gfs0.fs/src/%.asm,build/gfs0.fs/%.d,$(gfs0.fs_SOURCE_asm_asm))
gfs0.fs_SOURCE_asm_s=$(wildcard modules/gfs0.fs/src/*.s)
gfs0.fs_OBJECTS_asm_s=$(patsubst modules/gfs0.fs/src/%.s,build/gfs0.fs/%.o,$(gfs0.fs_SOURCE_asm_s))
gfs0.fs_DEPFILES_asm_s=$(patsubst modules/gfs0.fs/src/%.s,build/gfs0.fs/%.d,$(gfs0.fs_SOURCE_asm_s))
gfs0.fs_SOURCE_cpp_cpp=$(wildcard modules/gfs0.fs/src/*.cpp)
gfs0.fs_OBJECTS_cpp_cpp=$(patsubst modules/gfs0.fs/src/%.cpp,build/gfs0.fs/%.o,$(gfs0.fs_SOURCE_cpp_cpp))
gfs0.fs_DEPFILES_cpp_cpp=$(patsubst modules/gfs0.fs/src/%.cpp,build/gfs0.fs/%.d,$(gfs0.fs_SOURCE_cpp_cpp))
gfs0.fs_SOURCE_cpp_cxx=$(wildcard modules/gfs0.fs/src/*.cxx)
gfs0.fs_OBJECTS_cpp_cxx=$(patsubst modules/gfs0.fs/src/%.cxx,build/gfs0.fs/%.o,$(gfs0.fs_SOURCE_cpp_cxx))
gfs0.fs_DEPFILES_cpp_cxx=$(patsubst modules/gfs0.fs/src/%.cxx,build/gfs0.fs/%.d,$(gfs0.fs_SOURCE_cpp_cxx))
gfs0.fs_SOURCE_c_c=$(wildcard modules/gfs0.fs/src/*.c)
gfs0.fs_OBJECTS_c_c=$(patsubst modules/gfs0.fs/src/%.c,build/gfs0.fs/%.o,$(gfs0.fs_SOURCE_c_c))
gfs0.fs_DEPFILES_c_c=$(patsubst modules/gfs0.fs/src/%.c,build/gfs0.fs/%.d,$(gfs0.fs_SOURCE_c_c))
build/gfs0.fs/%.o: modules/gfs0.fs/src/%.asm
	@as -M -MD -c -o $@ $<
	$(info  	AS	$<)
build/gfs0.fs/%.o: modules/gfs0.fs/src/%.s
	@as -M -MD -c -o $@ $<
	$(info  	AS	$<)
build/gfs0.fs/%.o: modules/gfs0.fs/src/%.cpp
	@g++ -O0 -fno-rtti -fno-exceptions -nostdlib -ffreestanding -fno-stack-protector -fno-builtin -nostartfiles -Wunreachable-code -std=c++20 -Wno-literal-suffix -Wno-pointer-arith -MP -MD -Imodules/klib/inc/ -Iinc/ -Ishared/ -Imodules/gfs0.fs/inc -march=x86-64 -c -o $@ $<
	$(info 	C++	$<)
build/gfs0.fs/%.o: modules/gfs0.fs/src/%.cxx
	@g++ -O0 -fno-rtti -fno-exceptions -nostdlib -ffreestanding -fno-stack-protector -fno-builtin -nostartfiles -Wunreachable-code -std=c++20 -Wno-literal-suffix -Wno-pointer-arith -MP -MD -Imodules/klib/inc/ -Iinc/ -Ishared/ -Imodules/gfs0.fs/inc -march=x86-64 -c -o $@ $<
	$(info 	C++	$<)
build/gfs0.fs/%.o: modules/gfs0.fs/src/%.c
	@gcc -Wunreachable-code -Imodules/klib/inc/ -Iinc/ -Ishared/ -Imodules/gfs0.fs/inc -march=x86-64 -c -o $@ $<
	$(info  	CC	$<)
m-gfs0.fs-clean:
	@-rm -r build/gfs0.fs/*.o
	$(info  	DELETE	build/gfs0.fs/*.o)
	@-rm -r build/gfs0.fs/*.d
	$(info  	DELETE	build/gfs0.fs/*.d)
m-gfs0.fs: out/gfs0.fs.elf64
out/gfs0.fs.elf64:  $(gfs0.fs_OBJECTS_asm_asm) $(gfs0.fs_OBJECTS_asm_s) $(gfs0.fs_OBJECTS_cpp_cpp) $(gfs0.fs_OBJECTS_cpp_cxx) $(gfs0.fs_OBJECTS_c_c)
	@ld -nostdlib -T LDS/gfs0.fs.ld  $(gfs0.fs_OBJECTS_asm_asm) $(gfs0.fs_OBJECTS_asm_s) $(gfs0.fs_OBJECTS_cpp_cpp) $(gfs0.fs_OBJECTS_cpp_cxx) $(gfs0.fs_OBJECTS_c_c)  $(klib_OBJECTS_asm_asm) $(klib_OBJECTS_asm_s) $(klib_OBJECTS_cpp_cpp) $(klib_OBJECTS_cpp_cxx) $(klib_OBJECTS_c_c) -o out/gfs0.fs.elf64
	$(info  	LD	$@)
	@objcopy out/gfs0.fs.elf64 --remove-section text_klib --remove-section rodata_klib --remove-section data_klib --remove-section bss_klib
	$(info  	OBJCOPY	$@)
-include $(gfs0.fs_DEPFILES_asm_asm)
-include $(gfs0.fs_DEPFILES_asm_s)
-include $(gfs0.fs_DEPFILES_cpp_cpp)
-include $(gfs0.fs_DEPFILES_cpp_cxx)
-include $(gfs0.fs_DEPFILES_c_c)
