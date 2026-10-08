section .bss
stack_space: resb 16384
stack_top:
extern kernel_main
section .text
global _start

_start:

    mov esi, eax
    mov edi, ebx
    lea esp, [stack_space + 16384]
    lgdt [gdt_descriptor]
    mov eax, cr0
    or eax, 1
    mov cr0, eax
    jmp 0x08:protected_mode
[bits 32]
protected_mode:

    mov ax, 0x10
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov esp, stack_top
    push edi
    push esi
    cli
    call kernel_main

gdt_start:
    ;segment descriptors
    ;Null Descriptor
    dw 0x0000
    dw 0x0000
    db 0x00
    db 0x00
    db 0x00
    db 0x00
    ;Code Segment
    dw 0xFFFF
    dw 0x0000
    db 0x00
    db 0x9A
    db  0xCF
    db  0x00
    ;Data Segment
    dw 0xFFFF
    dw 0x0000
    db 0x00
    db 0x92
    db 0xCF
    db 0x00
;lgdt
gdt_descriptor:
    dw 0x0017
    dd gdt_start
