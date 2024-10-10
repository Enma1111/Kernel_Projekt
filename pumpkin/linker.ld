ENTRY(_start)          /* Startpunkt für den Linker */

SECTIONS
{
    . = 1M;            /* Beginne die Kernel-Lastadresse bei 1 MB */

    .multiboot_header ALIGN(4) :
    {
        KEEP(*(.multiboot_header))   /* Halte den Multiboot-Header */
    }

    .text ALIGN(4) :
    {
        *(.text)                     /* Alle .text-Sektionen */
    }

    .data ALIGN(4) :
    {
        *(.data)                     /* Alle .data-Sektionen */
    }

    .bss ALIGN(4) :
    {
        *(.bss)                      /* Alle .bss-Sektionen */
    }
}
