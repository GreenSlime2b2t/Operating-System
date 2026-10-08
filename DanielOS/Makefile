BUILD = build

SRC = src
C = $(SRC)/C
ASM = $(SRC)/asm

ISO = iso

KERNEL = $(BUILD)/kernel.elf
IMAGE = myos.iso

.PHONY: all iso run clean

all: $(KERNEL)

$(BUILD)/boot.o: $(ASM)/boot.asm
	nasm -f elf32 $< -o $@

$(BUILD)/multiboot_header.o: $(ASM)/multiboot_header.asm
	nasm -f elf32 $< -o $@

$(BUILD)/interrupts.o: $(ASM)/interrupts.asm
	nasm -f elf32 $< -o $@

$(BUILD)/keyboard.o: $(ASM)/keyboard.asm
	nasm -f elf32 $< -o $@

$(BUILD)/io.o: $(ASM)/io.asm
	nasm -f elf32 $< -o $@

$(BUILD)/kernel.o: $(C)/kernel.c $(C)/library.h $(C)/idt.h $(C)/memory.h
	gcc -m32 -ffreestanding -c $< -o $@

$(BUILD)/library.o: $(C)/library.c $(C)/library.h
	gcc -m32 -ffreestanding -c $< -o $@

$(BUILD)/idt.o: $(C)/idt.c $(C)/idt.h
	gcc -m32 -ffreestanding -c $< -o $@

$(BUILD)/memory.o: $(C)/memory.c $(C)/memory.h
	gcc -m32 -ffreestanding -c $< -o $@

$(KERNEL): $(BUILD)/boot.o \
           $(BUILD)/multiboot_header.o \
           $(BUILD)/interrupts.o \
           $(BUILD)/keyboard.o \
           $(BUILD)/io.o \
           $(BUILD)/kernel.o \
           $(BUILD)/library.o \
           $(BUILD)/idt.o \
           $(BUILD)/memory.o \
           linker.ld
	ld -m elf_i386 -T linker.ld \
	   $(BUILD)/boot.o \
	   $(BUILD)/multiboot_header.o \
	   $(BUILD)/interrupts.o \
	   $(BUILD)/keyboard.o \
	   $(BUILD)/io.o \
	   $(BUILD)/kernel.o \
	   $(BUILD)/library.o \
	   $(BUILD)/idt.o \
	   $(BUILD)/memory.o \
	   -o $@

$(IMAGE): $(KERNEL)
	cp $(KERNEL) $(ISO)/boot/kernel.elf
	grub-mkrescue -o $(IMAGE) $(ISO)/

iso: $(IMAGE)

run: $(IMAGE)
	qemu-system-i386 -cdrom $(IMAGE)

clean:
	rm -f $(BUILD)/*.o $(BUILD)/kernel.elf $(IMAGE)