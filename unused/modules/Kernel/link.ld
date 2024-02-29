OUTPUT_FORMAT("binary")

ENTRY(init)
SECTIONS
{
    . = 0x800000;
    
    .text :
    {
        *(.text)
    }

    . = 0x10000000;

    .data :
    {
        *(.data)
    }

    . = 0x10200000;

    .rodata :
    {
        *(.rodata)
    }

    . = 0x10400000;

    .bss : 
    {
        *(.bss)
    }

    . = 0x10600000;

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