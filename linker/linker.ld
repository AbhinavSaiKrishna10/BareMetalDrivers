ENTRY(Reset_Handler)

MEMORY
{
    FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 512K
    RAM   (rwx) : ORIGIN = 0x20000000, LENGTH = 128K
}

_estack = ORIGIN(RAM) + LENGTH(RAM);

SECTIONS
{
    .isr_vector :
    {
        . = ALIGN(4);
        KEEP(*(.isr_vector))
    } > FLASH

    .text :
    {
        . = ALIGN(4);

        *(.text)
        *(.text.*)

        . = ALIGN(4);
    } > FLASH

    .rodata :
    {
        . = ALIGN(4);

        *(.rodata)
        *(.rodata.*)

        . = ALIGN(4);
    } > FLASH

    .data :
    {
        . = ALIGN(4);

        *(.data)
        *(.data.*)

        . = ALIGN(4);
    } > RAM

    .bss :
    {
        . = ALIGN(4);

        *(.bss)
        *(.bss.*)
        *(COMMON)

        . = ALIGN(4);
    } > RAM
}