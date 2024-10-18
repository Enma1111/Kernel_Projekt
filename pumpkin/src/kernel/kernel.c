#include <multiboot.h>

extern void kernel_main(); // Stelle sicher, dass der Hauptkernel definiert ist

__attribute__((section(".multiboot_header")))
struct multiboot_header header = {
    .flags = MULTIBOOT_INFO_MEMORY, // Beispiel für die Verwendung eines Flags
    .mem_lower = 0,
    .mem_upper = 0,
    .boot_device = 0,
    .cmdline = 0,
    .mods_count = 0,
    .mods_addr = 0,
    .syms = {0, 0, 0, 0},
    .mmap_length = 0,
    .mmap_addr = 0,
};

void kernel_main() {
    char *video_memory = (char *) 0xB8000;
    const char *message = "Hello, World!";

    for (int i = 0; message[i] != '\0'; i++)
    {
        video_memory[i * 2] = message[i];
        video_memory[i * 2 + 1] = 0x07; // Grau auf Schwarz
    }
    while (1);
}