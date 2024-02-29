OUTPUT_FORMAT("binary")

ENTRY(init)
SECTIONS
{
    . = 0x_00000;
    
    .text :
    {
        *(.text)
    }

    . = 0x10_00000;

    .data :
    {
        *(.data)
    }

    . = 0x10_00000;

    .rodata :
    {
        *(.rodata)
    }

    . = 0x10_00000;

    .bss : 
    {
        *(.bss)
    }

    . = 0x10_00000;

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