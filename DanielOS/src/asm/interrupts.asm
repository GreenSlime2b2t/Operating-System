global isr_wrapper
global load_table

extern c_handler

isr_wrapper:
    pusha      
    call c_handler  
    popa           
    iretd          

load_table:
    mov eax, [esp + 4]  
    lidt [eax]        
    ret                