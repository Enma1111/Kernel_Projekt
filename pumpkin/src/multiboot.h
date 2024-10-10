#ifndef MULTIBOOT_H
#define MULTIBOOT_H

#define MULTIBOOT_MAGIC 0x2BADB002
#define MULTIBOOT_BOOTLOADER_MAGIC 0x2BADB003

/* Multiboot-Flags */
#define MULTIBOOT_INFO_MEMORY (1 << 0)
#define MULTIBOOT_INFO_BOOTDEV (1 << 1)
#define MULTIBOOT_INFO_CMDLINE (1 << 2)
#define MULTIBOOT_INFO_MODS (1 << 3)
#define MULTIBOOT_INFO_AOUT_SYMS (1 << 4)
#define MULTIBOOT_INFO_ELF_SHDR (1 << 5)
#define MULTIBOOT_INFO_MEM_MAP (1 << 6)

/* Definiere die Struktur für den Multiboot-Header */
struct multiboot_header {
    unsigned long flags;
    unsigned long mem_lower;
    unsigned long mem_upper;
    unsigned long boot_device;
    unsigned long cmdline;
    unsigned long mods_count;
    unsigned long mods_addr;
    unsigned long syms[4];
    unsigned long mmap_length;
    unsigned long mmap_addr;
};

#endif // MULTIBOOT_H