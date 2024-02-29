OUTPUT_FORMAT("binary")
ENTRY(init)
INPUT(library/klib/exception.o)
INPUT(library/klib/string.o)
INPUT(library/klib/list.o)
INPUT(library/klib/litop.o)
INPUT(library/klib/init.o)
INPUT(library/klib/memcpy.o)
INPUT(library/klib/strlen.o)
SECTIONS
{
	. = 0x1C00000;
	.text_klib : { library/klib/*.o (.text) }
	. = 0x1E00000;
	.data_klib : { library/klib/*.o (.data) }
	. = 0x2000000;
	.rodata_klib : { library/klib/*.o (.rodata) }
	. = 0x2200000;
	.bss_klib : { library/klib/*.o (.bss) }
	. = 0x23FFFFF;

}
SECTIONS
{
	. = 0x1000000;
	.text : { *(.text) }
	. = 0x1200000;
	.data : { *(.data) }
	. = 0x1400000;
	.rodata : { *(.rodata) }
	. = 0x1600000;
	.bss : { *(.bss) }
	. = 0x17FFFFF;
	/DISCARD/ : 
	{
		*(.note*);
		*(.iplt*);
		*(.igot*);
		*(.rel*);
		*(.comment);
		*(.eh_frame);
	}

}
