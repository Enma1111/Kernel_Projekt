global _start

section .multiboot_header
    align 4
    dd 0x1BADB002            
    dd 0x00                  
    dd -(0x1BADB002 + 0x00) 

section .text
_start:
    extern kernel_main
    call kernel_main          
hang:
    jmp hang                 
