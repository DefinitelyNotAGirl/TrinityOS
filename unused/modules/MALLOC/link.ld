SECTIONS
{
    . = 0x000000;
    
    .text : 
    {
        *(.text)
    }

    .data :
    {
        *(.data)
    }

    .rodata :
    {
        *(.rodata)
    }

    .bss : 
    {
        *(.bss)
    }

    . = 0x000000;
}