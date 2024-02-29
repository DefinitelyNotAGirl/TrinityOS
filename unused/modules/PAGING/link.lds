OUTPUT_FORMAT("binary")

ENTRY(init)
SECTIONS
{
    . = 0x000000;
    
    .text :
    {
        *(.text)
    }

    . = ALIGN(0x200000);

    .data :
    {
        *(.data)
    }

    . = ALIGN(0x200000);

    .rodata :
    {
        *(.rodata)
    }

    . = ALIGN(0x200000);

    .bss : 
    {
        *(.bss)
    }

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