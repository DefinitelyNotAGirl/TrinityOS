;
; Created Date: Friday November 25th 2022
; Author: DefinitelyNotAGirl@github
; -----
; Last Modified: Friday November 25th 2022 3:23:44 pm
; Modified By: DefinitelyNotAGirl@github (definitelynotagirl115199@gmail.com)
; -----
; Copyright (c) 2022 DefinitelyNotAGirl@github
; 
; Permission is hereby granted, free of charge, to any person
; obtaining a copy of this software and associated documentation
; files (the "Software"), to deal in the Software without
; restriction, including without limitation the rights to use, copy,
; modify, merge, publish, distribute, sublicense, and/or sell copies
; of the Software, and to permit persons to whom the Software is
; furnished to do so, subject to the following conditions:
; 
; The above copyright notice and this permission notice shall be
; included in all copies or substantial portions of the Software.
; 
; THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
; EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
; MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
; NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
; HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
; WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
; OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
; DEALINGS IN THE SOFTWARE.
;

;used registers:
;   es, screen output buffer
;   di, screen output position

;sector 0
[BITS 16    ]
[ORG  0x7C00]
section .text
_start:
    cli
    mov bl, 0x0F    ;white text on black background
    mov bh, 0x00    ;page 0

    ;read 32-bit code from disk
    call disk_read32BitLoader

    ;reconfigure screen
    mov ah, 0x00    ; function 0, set video mode
    mov al, 264     ; video mode 264: text 80x60 (makes no sense but works (???))
    int 0x10

    mov ax, 0xB800; 0xB8000/16
    mov es, ax; ax->es

    ;clear screen
    mov di, 80*60*2
screen_clear_loop:
    cmp di, 0
    je screen_clear_loop_end
    sub di, 2
    mov word [es:di], 0x0000
    jmp screen_clear_loop
screen_clear_loop_end:

    mov bx, welcome
    call print

    jmp stage2

welcome:
    db "welcome"
    dw 0x0A00
str_diskerror:
    db "disk error"
    dw 0x0A00
str_error:
    db "disk error"
    dq 0x000000000000000A
str_stage2:
    db "stage 2 engaged"
    dq 0x000000000000000A
str_jump32:
    db "jumping to 32 bit code..."
    dq 0x000000000000000A
str_32bit:
    db "Something's wrong, i can feel it."
    dq 0x000000000000000A

print:
    mov ah, 0x0F; white on black
.pstrLoop:
    mov byte al, [bx]
    jmp .pstrcmp

.pstrnl:
    ;di=(floor(di/80)+1)*80
    xor dx,dx; reset dx
    mov ax, di; dx ==> ax
    mov cx, 160; 80*2 ==> cx
    div cx; ax/=cx ax=result dx=remainder
    inc ax
    mul cx
    sub ax, 2
    mov di, ax
    jmp .pstrLoop_Final

.pstrcmp:
    cmp al, 0x00
    je .pstrLoopEnd
    cmp al, 0xA
    je .pstrnl

.pstrchar:
    mov word [es:di], ax
    jmp .pstrLoop_Final

.pstrLoop_Final:
    add di, 2
    inc bx
    jmp .pstrLoop
.pstrLoopEnd:
    ret

;read the entire 64 sectors used for the 32-bit section of the bootloader and entry64
disk_read32BitLoader:
    ;never just assume you did something right, this shit was set to 0x7E00 
    ;and i just lost my mind over LGDT loading 0 to the GDTR for like 30 hours
    ;(yes the comment about the address was already there at that time)
    mov bx, 0x7C00; address to load first sector at -0x200
    mov si, 64  ;number of sectors to load
    mov ch, 0x00;initial cylinder
    mov cl, 0x01;initial sector (sectors start at 1 not 0)
    mov dh, 0x00;initial head

.disk_r32Loop:
    cmp si, 0
    je .disk_r32LoopEnd

    dec si          ; decrement loop counter
    add bx, 0x200   ; set address for next sector
    inc cl          ; increment sector by 1
    call disk_readSector

    jmp .disk_r32Loop
.disk_r32LoopEnd:
    ret

disk_readSector:
    mov al, 0x01    ; sectors to read
    mov dl, 0x80    ; first hard disk
    mov ah, 0x02    ; function 2, read sectors from disk
    int 0x13        ; fire interrupt
    jc disk_error   ; jumps if carry flag is set
    ret

disk_error:
    mov bx, str_diskerror
    call print
    ret

;MBR BOOT SIGNATURE
times 510-($-$$) db 0
dw 0xAA55

;sector 1
detectMemory:
    mov di, 0x0000
    mov eax, 0x0050;
    mov es, eax

    ;function
    xor ebx, ebx                ; ebx must start out at 0
    xor ebp, ebp                ; keep entry count in bp
    mov edx, 0x534D4150	    ; Place "SMAP" into edx
    mov eax, 0xE820             ; BIOS function int 0x15, EAX=0xE820
    mov [es:di + 20], dword 1	; force a valid ACPI 3.X entry
    mov ecx, 24		            ; ask for 24 bytes
    int 0x15
    jc .dctMemERR           ; unsupported
    mov edx, 0x534D4150    ; Some BIOSes apparently trash this register?
    cmp eax, edx		    ; on success, eax must have been reset to "SMAP"
    jne .dctMemERR
	cmp ebx, 0		    ; ebx = 0 implies list is only 1 entry long (worthless)
	je .dctMemERR
    jmp .dctMemIN
.dctMemLoop:
	;mov [es:di + 20], dword 1	; force a valid ACPI 3.X entry
	;mov ecx, 24		            ; ask for 24 bytes again 
    ;xor ecx, ecx                ; reset ecx to 0
    mov eax, 0xe820		        ; eax, ecx get trashed on every int 0x15 call
    int 0x15
    jc .dctMemEPI               ; carry set means "end of list already reached"
	mov edx, 0x534D4150	    ; repair potentially trashed register
.dctMemIN:
	cmp cl, 24		            ; got a 24 byte ACPI 3.X response?
	je .dctMemnotext
    cmp cl, 20                  ; got a 20 byte response?
	je .dctMemnotext20
    jne .dctMemERR
.dctMemnotext:
    test byte [es:di + 20], 1	; if 24 byte entry: is the "ignore this data" bit clear?
	jnz .dctMemskipent
	mov ecx, [es:di + 8]	; get lower uint32_t of memory region length
	or ecx, [es:di + 12]	; "or" it with upper uint32_t to test for zero
	jz .dctMemskipent		; if length uint64_t is 0, skip entry
	inc ebp			        ; got a good entry: ++count, move to next storage spot
	add edi, 24
    jmp .dctMemLoop
.dctMemnotext20:
    mov dword [es:di + 20], 0; set ACPI 3.x ext attribs to 0 (no 3.x response, invalid)
	mov ecx, [es:di + 8]	; get lower uint32_t of memory region length
	or ecx, [es:di + 12]	; "or" it with upper uint32_t to test for zero
	jz .dctMemskipent		; if length uint64_t is 0, skip entry
	inc ebp			; got a good entry: ++count, move to next storage spot
	add edi, 24
    jmp .dctMemLoop
.dctMemskipent:
	cmp ebx, 0		; if ebx resets to 0, list is complete
    je .dctMemEPI
	jne .dctMemLoop
.dctMemERR:
    mov eax, 1
    jmp .dctMemEPI
.dctMemEPI:
    clc ;clear potential carry flag
    mov [0xFFFB], ebp
    ret

stage2:
    mov bx, str_stage2
    call print

    mov [0xFFF0], edi
    call detectMemory
    cmp eax, 0
    je .skip1
    mov bx, str_error
    call print
.skip1:
    mov edi, [0xFFF0]

    jmp jump32

jump32:
    mov bx, str_jump32
    call print

    ;load GDT and jump
    lgdt [gdt32.pointer]

    ;set cr0.PE
    mov eax, cr0
    or  eax, 1
    mov cr0, eax

    jmp 0x8:entry32

idt32:
    dq 0

;dont fuck up the little endian part, i just wasted an embarassingly long time, even by my standarts
gdt32:
    dq 0
;stage 1&2 code
    dw 0xFFFF
    dw 0x0000  
    db 0x0000
    db 0b10011000; access byte
    db 0b01001111; flags and limit
    db 0x00
;stage 1&2 data
    dw 0xFFFF
    dw 0x0000
    db 0x0000
    db 0b10010010; access byte
    db 0b01001111; flags and limit
    db 0x00
;VGA
    dw 0x4B00
    dw 0x8000
    db 0x000B
    db 0b10010010; access byte
    db 0b01000000; flags and limit
    db 0x00
;stage 3 code
    dw 0x3D09; 64MB
    dw 0x0000
    db 0x00
.S3CAB:
    db 0b10010010; access byte
    db 0b11000000; flags and limit
    db 0x00
;stage 3 data
    dw 0x3D09; 64MB
    dw 0x0000
    db 0x00
    db 0b10010010; access byte
    db 0b11000000; flags and limit
    db 0x00
;64 bit code
    dw 0x0000
    dw 0x0000
    db 0x00
    db 0b10011010; access byte
    db 0b00100000; flags and limit
    db 0x00
.pointer:
    dw .pointer - gdt32 - 1
    dd gdt32

;sector 2
align 512
section .text
[BITS 32]
entry32:
    cli
    ;set data segments
    mov eax, 0x10
    mov ds, eax
    mov ss, eax
    ;set VGA segment
    mov eax, 0x18
    mov es, eax

    mov esp, 0x7E00

    mov ebx, str_32bit
    call print32

    mov ebp, 0x08400; source
    mov eax, 0x10000; copy to 0x10000
    mov ecx, 0x07800; copy 60 sectors
    call memcpy

    ;make stage 3 code segment an actual code segment
    mov al, [gdt32.S3CAB]
    or al, 0b00001000
    mov [gdt32.S3CAB], al

    jmp 0x20:0x10000; far jump to 0x10000
    
    ;hangup (remove this later)
    cli
    hlt

; ebp: source  
; eax: dst
; ecx: len
memcpy:
    push edx
.memcpyLoop:
    cmp ecx, 0
    je .memcpyLoopEnd
    dec ecx

    mov edx, [ebp]
    mov [eax], edx

    inc ebp
    inc eax
    jmp .memcpyLoop
.memcpyLoopEnd:
    pop edx
    ret

; eax: string address a
; ebx: string address b
strcomp:
    ret

;yes, this is the same code as above
print32:
    xor eax, eax
    mov ah, 0x0F; white on black
.pstrLoop32:
    mov byte al, [ebx]
    jmp .pstrcmp32

.pstrnl32:
    ;di=(floor(di/80)+1)*80
    xor edx,edx; reset dx
    mov eax, edi; dx ==> ax
    mov ecx, 160; 80*2 ==> cx
    div ecx; ax/=cx ax=result dx=remainder
    inc eax
    mul ecx
    sub eax, 2
    mov edi, eax
    jmp .pstrLoop_Final32

.pstrcmp32:
    cmp al, 0x00
    je .pstrLoopEnd32
    cmp al, 0xA
    je .pstrnl32

.pstrchar32:
    mov word [es:edi], ax
    jmp .pstrLoop_Final32

.pstrLoop_Final32:
    add edi, 2
    inc ebx
    jmp .pstrLoop32
.pstrLoopEnd32:
    ret

;sector 3
align 512
str_ELF_COMPLETE:
    db "elf executable read successfully"
    dq 0x000000000000000A
str_ERROR_ELF:
    db "error reading ELF executable"
    dq 0x000000000000000A
str_ERROR_ELF_BITS:
    db "error reading ELF executable: not 32 bit"
    dq 0x000000000000000A
str_ERROR_ELF_ABI:
    db "error reading ELF executable: ABI not set to system V"
    dq 0x000000000000000A
str_ERROR_ELF_EXE:
    db "error reading ELF executable: not an executable"
    dq 0x000000000000000A
