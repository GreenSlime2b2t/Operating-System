#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#include "library.h"
#define MAX_MEMORY_REGIONS 64
struct memory_region {
    uint64_t base;
    uint64_t length;
    uint32_t type;
};

struct multiboot_info {
    uint32_t flags;
    uint32_t mem_lower;
    uint32_t mem_upper;
    uint32_t boot_device;
    uint32_t cmdline;
    uint32_t mods_count;
    uint32_t mods_addr;
    uint32_t syms[4];
    uint32_t mmap_length;
    uint32_t mmap_addr;
};

/* Multiboot memory map entry (packed, matches the actual layout used by bootloaders) */
struct multiboot_mmap_entry {
    uint32_t size;      /* size of the entry *excluding* this field */
    uint64_t base_addr;
    uint64_t length;
    uint32_t type;
} __attribute__((packed));

#define MULTIBOOT_MEMORY_AVAILABLE 1

uint64_t available_memory(uint32_t multiboot_addr);

#endif