/* 
 * File Generated by GEOS buildExec 
 * Copyright (c) 2023 DefinitelyNotAGirl@github 
 */
OUTPUT_FORMAT("elf64-x86-64")
ENTRY(init)
SECTIONS {
	. = 0x0000000004600000;
	text : {
		build/SATAN/*.o (.text*)
	}
	. = 0x0000000004800000;
	data : {
		build/SATAN/*.o (.data*)
	}
	. = 0x0000000004A00000;
	rodata : {
		build/SATAN/*.o (.rodata*)
	}
	. = 0x0000000004C00000;
	bss : {
		build/SATAN/*.o (.bss*)
	}
	. = 0x1C00000;
	text_klib : {
		build/klib/*.o (.text*)
	}
	. = 0x1E00000;
	data_klib : {
		build/klib/*.o (.data*)
	}
	. = 0x2000000;
	rodata_klib : {
		build/klib/*.o (.rodata*)
	}
	. = 0x2200000;
	bss_klib : {
		build/klib/*.o (.bss*)
	}
	/DISCARD/ : {
		*(.note*)
		*(.iplt*)
		*(.igot*)
		*(.rel*)
		*(.comment*)
		*(.eh_frame*)
	}
}
