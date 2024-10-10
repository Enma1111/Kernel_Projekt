# Compiler- und Linker-Variablen
CC = i686-elf-gcc
LD = i686-elf-ld
AS = i686-elf-as
CFLAGS = -ffreestanding -nostdlib -lgcc -O2 -Wall -Wextra -Isrc
LDFLAGS = -T linker.ld

# Verzeichnisse
SRC_DIR = src
BUILD_DIR = build
ISO_DIR = iso
ISO_IMAGE = $(BUILD_DIR)/os-image.iso

# Objekt-Dateien
OBJS = $(BUILD_DIR)/multiboot_header.o $(BUILD_DIR)/kernel.o

# Ziel: Erstelle die ISO-Image
all: $(ISO_IMAGE)

# Regel für das Erstellen des Kernel-Binärformats
$(BUILD_DIR)/kernel.bin: $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

# Regel für das Erstellen des Multiboot-Headers
$(BUILD_DIR)/multiboot_header.o: $(SRC_DIR)/multiboot_header.asm
	@mkdir -p $(BUILD_DIR)
	nasm -f elf32 $< -o $@

# Regel für das Erstellen des Kernel-Objekts
$(BUILD_DIR)/kernel.o: $(SRC_DIR)/kernel.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Regel für das Kopieren der grub.cfg
$(ISO_DIR)/boot/grub/grub.cfg:
	@mkdir -p $(ISO_DIR)/boot/grub
	cp grub.cfg $(ISO_DIR)/boot/grub/grub.cfg

# Regel für das Erstellen des ISO-Images
$(ISO_IMAGE): $(BUILD_DIR)/kernel.bin $(ISO_DIR)/boot/grub/grub.cfg
	@mkdir -p $(ISO_DIR)/boot
	cp $(BUILD_DIR)/kernel.bin $(ISO_DIR)/boot/kernel.bin
	grub-mkrescue -o $@ $(ISO_DIR)

# Regel zum Bereinigen von Build-Outputs
clean:
	rm -rf $(BUILD_DIR)/*.o $(BUILD_DIR)/*.bin $(ISO_DIR) os-image.iso
