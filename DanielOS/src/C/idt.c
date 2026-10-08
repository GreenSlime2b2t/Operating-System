#include "idt.h"
#include "library.h"

idt_entry_t idt[256] = { {0} };

idt_ptr_t idt_ptr;
void pic_remap(void) {

    outb(0x20, 0x11);
    outb(0xA0, 0x11);

    outb(0x21, 0x20);
    outb(0xA1, 0x28); 

    outb(0x21, 0x04); 
    outb(0xA1, 0x02); 

    outb(0x21, 0x01);
    outb(0xA1, 0x01);

    outb(0x21, 0x00);
    outb(0xA1, 0x00);
}
void k_handler(void) {
    uint8_t scancode = inb(0x60);
    static bool shift = false;
    if (scancode == 0xAA || scancode == 0xB6){
    shift = false;
}
    if (scancode == 0x2A || scancode == 0x36){
        shift = true;
    }

    if (!(scancode & 0x80)) {
        if (shift==false){
            if (scancode == 0x0E){
                cursorx--;
                printf(" ");
                cursorx--;
        }
            else if (scancode == 0x1C) {   
                printf("\n");
                cmd_commands();

                ptr_char = characters;
                characters[0] = '\0';
                count = 0;

                title();
                cursorx = 0;
            }
            else if(scancode == 0x1C){
                title();
                cursory++;
                cursorx = 0;
            }
            else{
                printf_letter(scancode);   
            }
        }
        else if(shift==true){
            printf_letters_shift(scancode);
            cursorx++;
        }


    } else {
        
    }

    outb(0x20, 0x20); 
}

void c_handler(void)
{
    outb(0x20,0x20);
}

void set_idt_state(
    idt_entry_t *entry,
    uint32_t address,
    uint16_t selector,
    uint8_t flags
)
{
    entry->offset_low = address & 0xFFFF;
    entry->selector = selector;
    entry->zero = 0;
    entry->type_attributes = flags;
    entry->offset_high = (address >> 16) & 0xFFFF;
}

void init_idt(void)
{
    pic_remap();
    //Random
    set_idt_state(
        &idt[32],
        (uint32_t)&isr_wrapper,
        0x08,
        0x8E
    );

    //Keyboard

        set_idt_state(
        &idt[33],
        (uint32_t)&keyisr_wrapper,
        0x08,
        0x8E
    );

    idt_ptr.limit = sizeof(idt) - 1;
    idt_ptr.base = (uint32_t)idt; //&idt[0] geht auch!
    

    load_table(&idt_ptr);
    __asm__ volatile ("sti");
}