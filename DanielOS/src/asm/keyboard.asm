global keyisr_wrapper
extern k_handler

keyisr_wrapper:
    pusha
    call k_handler
    popa
    iretd
