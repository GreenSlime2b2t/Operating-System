#include "memory.h"
#include "library.h"
#include "idt.h"


void set_mr(struct memory_region *entry, uint64_t base, uint64_t length, uint32_t type)
{
    entry->base   = base;
    entry->length = length;
    entry->type   = type;
}
uint64_t available_memory(uint32_t multiboot_addr){
    int total_memory=0;
    int region_count = 0;

    struct multiboot_info *mbi =
    (struct multiboot_info *)multiboot_addr;
    uint64_t available_mem = 0;
    if (!(mbi->flags & (1 << 6))) {
        return 0;
    }
    uint32_t map_addr = mbi->mmap_addr;
    uint32_t map_length = mbi->mmap_length;


    struct memory_region mr[MAX_MEMORY_REGIONS];

    uint32_t *mem_addr_ptr = (uint32_t*) map_addr;

    struct multiboot_mmap_entry *entry =
        (struct multiboot_mmap_entry *)mbi->mmap_addr;
    struct multiboot_mmap_entry *end =
        (struct multiboot_mmap_entry *)(mbi->mmap_addr + mbi->mmap_length);
    while(entry < end && region_count < MAX_MEMORY_REGIONS){
        set_mr(&mr[region_count],
                    entry->base_addr,
                    entry->length,
                    entry->type);
        region_count++;
    
    if (entry->type == MULTIBOOT_MEMORY_AVAILABLE){
        available_mem += entry->length;
    }
    entry = (struct multiboot_mmap_entry *)
                ((uint8_t *)entry + entry->size + sizeof(entry->size));
}   
    uint64_t available_mem_mb = (available_mem) / (1024*1024);
    printf_int64(available_mem_mb);
    printf(" MiB");
    return available_mem;


}
