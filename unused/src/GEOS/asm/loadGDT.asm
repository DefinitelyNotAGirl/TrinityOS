section .text
global loadGDT
loadGDT:
    lgdt [gdt64.pointer]
    ret

global loadIDT
loadIDT:
    lidt [idt64.pointer]
    ret

global getIDTaddr
getIDTaddr:
    mov rax, idt64; fill rax with idt address
    ret

global getGDTaddr
getGDTaddr:
    mov rax, gdt64; fill rax with gdt address (c assumes rax to be return value)
    ret

section .data
idt64:
    times 512 dq 0;write idt full of 0's
.pointer:
    dw .pointer - idt64
    dq idt64

gdt64:
    dq 0x00
.kCode: equ $ - gdt64
    dq (1<<21) | (0<<22) | (1<<44) | (1<<47) | (1<<41) | (1<<43) | (1<<53)
.kData: equ $ - gdt64
    dq (1<<44) | (1<<47) | (1<<41)
.pointer:
    dw .pointer - gdt64
    dq gdt64
