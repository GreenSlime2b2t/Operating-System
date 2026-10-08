#ifndef IDT_H
#define IDT_H
#include <stdint.h>
//Define INB AND OUTB

typedef struct {
    uint16_t offset_low;
    uint16_t selector;
    uint8_t zero;
    uint8_t type_attributes;
    uint16_t offset_high;
} __attribute__((packed)) idt_entry_t;

typedef struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) idt_ptr_t;

extern void isr_wrapper(void);
extern void keyisr_wrapper(void);
extern uint8_t inb(uint16_t port);
extern void outb(uint16_t port, uint8_t value);
extern void load_table(idt_ptr_t *idt_ptr_address);
void k_handler(void);
void pic_remap(void);
void init_idt(void);

#endif