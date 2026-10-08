#include "library.h"
#include "idt.h"
#include "memory.h"

void kernel_main(uint32_t magic, uint32_t multiboot_addr)
{
    struct multiboot_info *mbi =
        (struct multiboot_info *)multiboot_addr;

    uint32_t map_addr = mbi->mmap_addr;
    uint32_t map_length = mbi->mmap_length;
    
    clear_screen();
    init_idt();
    uint64_t availablem = available_memory(multiboot_addr);
    uint64_t available_mem_mb = (availablem) / (1024*1024);


    while (1)
    {
    }
}