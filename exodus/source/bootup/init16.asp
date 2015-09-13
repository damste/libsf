; init16.asp
;
; Exodus initialization routines
;
;  Functions:
;    ÀÂ verify_crc16                            ; Verify the CRC16 value stored in the bootup entries
;     Ã enable_gate_a20                         ; Enables gate A20 so we can access all memory
;     À setup_pmode_variables                   ; Sets up GDT and IDT
;       ÀÂ create_null_data_descriptor
;        Ã create_data_descriptor
;        Ã create_code_descriptor
;        Ã create_interrupt_descriptor_32_bit   ; Creates a 32-bit descriptor entry
;        Ã create_interrupt_descriptors
;        Ã create_exodus_tss_descriptor
;        Ã create_call_gate_descriptor
;        À create_task_gate_descriptor
;




verify_crc16    PROC    NEAR
; This routine scans all of the loaded data to ensure that the calculated CRC matches the CRC stored in the DT
;
; Upon entry:   boot_parameter_block - holds the linear address of all the files loaded in memory
;
; Upon exit:    This routine is self-terminating.  If there is a CRC error the program is terminated here.
;
    enter   2,0
  ; [bp-2] - item
    pushad
    push    ds
    push    es


    mov     esi,ds:boot_parameter_block
    inc     esi
    mov     edx,esi
    shr     edx,4
    mov     ds,dx
    and     esi,0fh
  ; Right now, ds:[si] - far ptr to the boot parameter block
    mov     word ptr [bp-2],0
    .WHILE (byte ptr ds:[si+_BOOT_PB_entry_type] != 0ffh)
        mov     al,byte ptr ds:[si+_BOOT_PB_entry_type]
        shr     al,1
        and     al,111b
        .IF (al != 011b)
          ; It's not bootup.bin (this program is bootup.bin, and whenever memory variables change the CRC will change,
          ;                      so we don't do any crc calculations on bootup.bin)
            mov     ecx,dword ptr ds:[si+_BOOT_PB_size]
            mov     edi,dword ptr ds:[si+_BOOT_PB_linear_offset]
            mov     edx,edi
            shr     edx,4
            mov     es,dx
            and     edi,0fh

          ; Right now, es:[di] - far ptr to start of this entry
          ;                 bx - used for crc16 value
            xor     bx,bx
          @@:
            push    word ptr 0a001h         ; mask
            xor     ah,ah
            mov     al,byte ptr es:[di]
            push    ax                      ; c
            push    bx                      ; crc

            call    update_crc16_value
            mov     bx,ax
            add     sp,6

            inc     di
            loop    @B
          ; Right now, bx is the crc16 value for this entry
            cmp     word ptr ds:[si+_BOOT_PB_crc16],bx
            jz      next_one

          ; This CRC value does not match the one on disk
          ; Display a message and then lockup the system
            mov     bx,cs
            mov     ds,bx
            mov     es,bx

            mov     ax,word ptr [bp-2]
            add     al,'A'
            mov     crc_error_code[3],al                        ; Store the error code for display
            mov     bx,07
            mov     dx,00400h
            mov     bp,offset crc_error_start
            mov     cx,offset crc_error_end - offset crc_error_start
            xor     bh,bh
            mov     ax,01301h
            int     10h
          ; Now that the message is displayed, lock up the system
          ; They have to press reset to fix this error
          @@:
            hlt
            jmp     @B

        .ENDIF

      next_one:
        inc     word ptr [bp-2]
        add     si,_BOOT_PB_structure_size
    .ENDW

    pop     es
    pop     ds
    popad
    leave
    ret
verify_crc16    ENDP




display_crc_comparitive     PROC    NEAR
    xor     bh,bh
    mov     bx,07
    mov     dh,byte ptr [bp-2]
    add     dh,5
    xor     dl,dl
    push    bp
    mov     bp,offset crc_comparitive
    mov     cx,sizeof crc_comparitive
    mov     ax,01301h
    int     10h
    pop     bp
    ret
display_crc_comparitive     ENDP




extract_word_to_ds_di       PROC    NEAR
; This routine is used to extract the dword
;
; Upon entry:   dx - word to extract
;          ds:[si] - where to store
;
; Upon exit:    4 hex characters are stored at ds:[si]
;
    push    di
    push    ax

    mov     al,dh
    shr     al,4
    call    adjust_al
    mov     byte ptr ds:[di],al
    inc     di

    mov     al,dh
    and     al,0fh
    call    adjust_al
    mov     byte ptr ds:[di],al
    inc     di

    mov     al,dl
    shr     al,4
    call    adjust_al
    mov     byte ptr ds:[di],al
    inc     di

    mov     al,dl
    and     al,0fh
    call    adjust_al
    mov     byte ptr ds:[di],al
    inc     di

    pop     ax
    pop     di
    ret
extract_word_to_ds_di       ENDP




adjust_al   proc    near
    .IF (al >= 0 && al <= 9)
        add     al,'0'
    .ELSE
        add     al,'a'-10
    .ENDIF
    ret
adjust_al   endp




update_crc16_value      PROC    NEAR
; This is the assembly generated by this CRC16 algorithm
;
; Upon entry:   On the stack:   mask, c, crc (each a word, in that order)
;
; [bp+8] - word, mask
; [bp+6] - word, c
; [bp+4] - word, crc
; [bp+2] - word, ip
; [bp+0] - word, bp
    enter   2,0
; [bp-2] - word, i
    push    di
    push    si
    push    cx

    mov     word ptr [bp-2],8   ; i
    mov     si,word ptr [bp+4]  ; crc
    mov     di,word ptr [bp+6]  ; c
  F515:
    mov     ax,si
    mov     cx,di
    xor     al,cl
    test    al,1
    je      I518
    mov     ax,si
    shr     ax,1
    xor     ax,word ptr [bp+8]  ; mask
    mov     si,ax
    jmp     I519

  I518:
    shr     si,1

  I519:
    shr     di,1
    dec     word ptr [bp-2]     ; i
    jne     F515
    mov     ax,si

    pop     cx
    pop     si
    pop     di
    leave
    ret
update_crc16_value      ENDP




enable_gate_a20     PROC    NEAR
  ;; Clear interrupts
    cli

  ;; Take control of gate A20
    xor     cx,cx                                                   ; Only loop 64k times
  eg_loop1:
    in      al,64h                                                  ; Are we able to send our data yet?
    test    al,2
    loopnz  eg_loop1                                                ; No if loop

    mov     al,0d1h                                                 ; Send command "get ready to receive Output Port byte"
    out     64h,al

    xor     cx,cx
  eg_loop2:
    in      al,64h                                                  ; Are we able to send our data yet?
    test    al,2
    loopnz  eg_loop2

    mov     al,00110011b                                            ; Send "Output Port" byte
    out     60h,al                                                  ; Ú7Â6Â5Â4Â3Â2Â1Â0¿
                                                                    ; ³x³x³1³1³x³x³1³1³
    xor     cx,cx                                                   ; ÀÂÁÂÁÂÁÂÁÂÁÂÁÂÁÂÙ
  eg_loop3:                                                         ;  ³ ³ ³ ³ ³ ³ ³ ÀÄ system reset (0-reset)
    in      al,64h                                                  ;  ³ ³ ³ ³ ³ ³ ÀÄÄÄ gate A20 (1-access above 1MB)
    test    al,2                                                    ;  ³ ³ ³ ³ ³ ÀÄÄÄÄÄ mouse data clock
    loopnz  eg_loop3                                                ;  ³ ³ ³ ³ ÀÄÄÄÄÄÄÄ data to mouse
                                                                    ;  ³ ³ ³ ÀÄÄÄÄÄÄÄÄÄ IRQ1 int 71h
  ;; Enable interrupts                                              ;  ³ ³ ÀÄÄÄÄÄÄÄÄÄÄÄ IRQ12 int 74h
    sti                                                             ;  ³ ÀÄÄÄÄÄÄÄÄÄÄÄÄÄ keyboard clock
    ret                                                             ;  ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ data to keyboard
enable_gate_a20     ENDP




setup_pmode_variables   PROC    NEAR
    push    ds

;; Setup all the IDT entries to point to an "iret"
    mov     ax,_sIDT_base SHR 4
    mov     ds,ax
    xor     esi,esi
    call    create_interrupt_descriptors

;; Setup all the GDT entries to point to a NULL data descriptor
    xor     ax,ax
    mov     ds,ax
    mov     esi,_sGDT_base                                          ; GDT is defined in common\equates.asp
    mov     cx,_sGDT_init                                           ; But, only the first 200 entries are initialized at bootup
    push    esi
    .REPEAT
        call    create_null_data_descriptor
        add     esi,8
    .UNTILCXZ
    pop     esi

;; Now, setup only the ones we'll need for the Exodus bootup.com requirements
;; Additional entries will be created during initialization and exodus.ini processing
  ;; Slot 1, IDT ptr
    mov     eax,_sIDT / 8                                           ; slot in GDT
    mov     ebx,_sIDT_base                                          ; base
    mov     edx,_sIDT_limit                                         ; limit
    call    create_data_descriptor

  ;; Slot 2, GDT ptr
    mov     eax,_sGDT / 8
    mov     ebx,_sGDT_base
    mov     edx,_sGDT_limit
    call    create_data_descriptor

  ;; Slot 3, STACK ptr
    mov     eax,_sSTACK / 8
    mov     ebx,_sSTACK_base
    mov     edx,_sSTACK_limit
    call    create_data_descriptor

  ;; Slot 4, kernel code (this program)
    mov     eax,_sCODE / 8
    mov     ebx,_sCODE_base
    mov     edx,_sCODE_limit
    call    create_code_descriptor

  ;; Slot 9, kernel data (same area as code, just mapped as read/write)
    mov     eax,_sDATA / 8
    mov     ebx,_sDATA_base
    mov     edx,_sDATA_limit
    call    create_data_descriptor

  ;; Slot 5, data (graphics video memory)
    mov     eax,_sGRAPHICS / 8
    mov     ebx,_sGRAPHICS_base
    mov     edx,_sGRAPHICS_limit
    call    create_data_descriptor

  ;; Slot 6, data (mono video memory)
    mov     eax,_sMONO / 8
    mov     ebx,_sMONO_base
    mov     edx,_sMONO_limit
    call    create_data_descriptor

  ;; Slot 7, data (vga video memory)
    mov     eax,_sVGA / 8
    mov     ebx,_sVGA_base
    mov     edx,_sVGA_limit
    call    create_data_descriptor

  ;; Slot 8, data (access to all memory)
    mov     eax,_sALL_MEM / 8
    mov     ebx,_sALL_MEM_base
    mov     edx,_sALL_MEM_limit
    call    create_data_descriptor

  ;; Slot 10, Exodus assigned memory
    mov     eax,_sEXODUS_MEM / 8
    mov     ebx,_sEXODUS_MEM_base
    mov     edx,_sEXODUS_MEM_limit
    call    create_data_descriptor

  ;; Slot 11, Exodus assigned ports
    mov     eax,_sEXODUS_PORTS / 8
    mov     ebx,_sEXODUS_PORTS_base
    mov     edx,_sEXODUS_PORTS_limit
    call    create_data_descriptor

  ;; Slot 12, Exodus assigned ints
    mov     eax,_sEXODUS_INTS / 8
    mov     ebx,_sEXODUS_INTS_base
    mov     edx,_sEXODUS_INTS_limit
    call    create_data_descriptor

  ;; Slot 13, --Nuserved
  ;; Slot 14, Exodus TSS
    mov     eax,_sEXODUS_TSS / 8
    mov     ebx,_sEXODUS_TSS_base
    mov     ecx,offset first_pmode_instruction
    mov     edx,_sEXODUS_TSS_limit
    call    create_exodus_tss_descriptor

  ;; Slot 15, Task gate to Exodus TSS
    mov     eax,_sEXODUS_TASK_GATE / 8                              ; GDT slot
    mov     ebx,_sEXODUS_TSS                                        ; GDT slot of TSS this task gate points to
    call    create_task_gate_descriptor

  ;; Slot 16, Exodus TSS
    mov     eax,_sEXODUS_SLAVE_TSS / 8
    mov     ebx,_sEXODUS_SLAVE_TSS_base
    mov     ecx,offset first_pmode_instruction
    mov     edx,_sEXODUS_SLAVE_TSS_limit
    call    create_exodus_tss_descriptor

  ;; Slot 17, Task gate to Exodus TSS
    mov     eax,_sEXODUS_SLAVE_TASK_GATE / 8                        ; GDT slot
    mov     ebx,_sEXODUS_SLAVE_TSS                                  ; GDT slot of TSS this task gate points to
    call    create_task_gate_descriptor

  ;; Slot 18, --Nuserved
  ;; Slot 19, PRIMATIVES
    mov     eax,_sPRIMATIVES / 8
    mov     ebx,_sPRIMATIVES_base
    mov     edx,_sPRIMATIVES_limit
    call    create_data_descriptor

  ;; Slot 20, PRIMATIVES
    mov     eax,_sPRIMATIVE_LOAD_INFO / 8
    mov     ebx,_sPRIMATIVE_LOAD_INFO_base
    mov     edx,_sPRIMATIVE_LOAD_INFO_limit
    call    create_data_descriptor

  ;; Slot 21, Exodus system memory
    mov     eax,_sSYSTEM / 8
    mov     ebx,_sSYSTEM_base
    mov     edx,_sSYSTEM_limit
    call    create_data_descriptor

  ;; Slot 22, Exodus's requestor() call gate
    mov     eax,_sEXODUS_REQUESTOR / 8
    mov     ebx,offset requestor
    xor     ecx,ecx
    mov     dx,_sCODE
    call    create_call_gate_descriptor

  ;; Slot 23, Exodus system memory (ring-1)
    mov     eax,_sSYSTEM_RING1 / 8
    mov     ebx,_sSYSTEM_base
    mov     edx,_sSYSTEM_USER_limit
    mov     cl,1
    call    create_data_descriptor_pl

  ;; Slot 24, Exodus system memory (ring-2)
    mov     eax,_sSYSTEM_RING2 / 8
    mov     ebx,_sSYSTEM_base
    mov     edx,_sSYSTEM_USER_limit
    mov     cl,2
    call    create_data_descriptor_pl

  ;; Slot 25, Exodus system memory (ring-3)
    mov     eax,_sSYSTEM_RING3 / 8
    mov     ebx,_sSYSTEM_base
    mov     edx,_sSYSTEM_USER_limit
    mov     cl,3
    call    create_data_descriptor_pl

  ;; Slot 26, low-level DEBI screen memory
    mov     eax,_sDEBI_screen / 8
    mov     ebx,_sDEBI_screen_base
    mov     edx,_sDEBI_screen_limit
    call    create_data_descriptor

  ;; Slot 27, low-level DEBI objects memory
    mov     eax,_sDEBI_memory / 8
    mov     ebx,_sDEBI_memory_base
    mov     edx,_sDEBI_memory_limit
    call    create_data_descriptor

  ;; Slot 28, low-level DEBI objects memory
    mov     eax,_sFLOPPY_TRACK / 8
    mov     ebx,_sFLOPPY_TRACK_base
    mov     edx,_sFLOPPY_TRACK_limit
    call    create_data_descriptor

  ;; Slot 29, data (vga backup video memory)
    mov     eax,_sVGA_BACKUP / 8
    mov     ebx,_sVGA_BACKUP_base
    mov     edx,_sVGA_BACKUP_limit
    call    create_data_descriptor

  ;; Slot 30, low-level DEBI screen memory2
    mov     eax,_sDEBI_screen2 / 8
    mov     ebx,_sDEBI_screen2_base
    mov     edx,_sDEBI_screen2_limit
    call    create_data_descriptor

  ;; Slot 32, Exodus objects
    mov     eax,_sEXODUS_OBJECTS / 8
    mov     ebx,_sEXODUS_OBJECTS_base
    mov     edx,_sEXODUS_OBJECTS_limit
    call    create_data_descriptor

  ;; Slot 33, task_switch() TSS
  ;; Note, the value of ecx is filled in later by the TASK primative itself, for now we just use NULL to get it created
    mov     eax,_sTASK_SWITCH_TSS / 8
    mov     ebx,_sTASK_SWITCH_TSS_base
    xor     ecx,ecx                                                 ; starting instruction
    mov     edx,_sTASK_SWITCH_TSS_limit
    call    create_exodus_tss_descriptor

  ;; Slot 34, Task gate to task_switch()
    mov     eax,_sTASK_SWITCH_TASK_GATE / 8                         ; GDT slot
    mov     ebx,_sTASK_SWITCH_TSS                                   ; GDT slot of TSS this task gate points to
    call    create_task_gate_descriptor

  ;; Slot 35, Task manager's stack for its TSS
    mov     eax,_sTASK_STACK / 8
    mov     ebx,_sTASK_STACK_base
    mov     edx,_sTASK_STACK_limit
    call    create_data_descriptor

  ;; Slot 50, Exodus.ini parsing area
    mov     eax,_sEXODUS_INI / 8
    mov     ebx,_sEXODUS_INI_base
    mov     edx,_sEXODUS_INI_limit
    call    create_data_descriptor

  ;; Slot 36, STACK 0
    mov     eax,_sSTACK0 / 8
    mov     ebx,_sSTACK0_base
    mov     edx,_sSTACK0_limit
    call    create_data_descriptor

  ;; Slot 37, STACK 1
    mov     eax,_sSTACK1 / 8
    mov     ebx,_sSTACK1_base
    mov     edx,_sSTACK1_limit
    call    create_data_descriptor

  ;; Slot 38, STACK 2
    mov     eax,_sSTACK2 / 8
    mov     ebx,_sSTACK2_base
    mov     edx,_sSTACK2_limit
    call    create_data_descriptor

  ;; Slot 51, Exodus.ini parsing area
    mov     eax,_sEXODUS_INI_ERRORS / 8
    mov     ebx,_sEXODUS_INI_ERRORS_base
    mov     edx,_sEXODUS_INI_ERRORS_limit
    call    create_data_descriptor

  ;; Slot 52, TASK system
    mov     eax,_sTASK_SYSTEM / 8
    mov     ebx,_sTASK_SYSTEM_base
    mov     edx,_sTASK_SYSTEM_limit
    call    create_data_descriptor

    pop     ds
    ret
setup_pmode_variables   ENDP




create_null_data_descriptor     PROC    NEAR
; Upon entry, ds:[esi] - far ptr to memory location for null data descriptor
    mov     dword ptr [esi+0],00000000000000000000000000000000b
    mov     dword ptr [esi+4],00000000000000001001000000000000b
    ret
create_null_data_descriptor     ENDP




create_data_descriptor      PROC    NEAR
; Upon entry, ds:[esi] - far ptr to GDT
;                  eax - slot # to insert
;                  ebx - base
;                  edx - limit
;
    pushad

    mov     word ptr [esi+eax*8+2],bx                           ; base 0:15
    shr     ebx,16
    mov     byte ptr [esi+eax*8+4],bl                           ; base 16:23
    shr     ebx,8
    mov     byte ptr [esi+eax*8+5],10010010b                    ; Not accessed, writeable, expand=0, DPL=00
    .IF (edx > 0fffffh)
      ; This is a BIG data descriptor (so, we have to change the granularity to 1)
      ; Also, setting the granularity bit makes the limit value be the number of 4k segments
        shr     edx,12                                          ; Divide by 4096
        mov     word ptr [esi+eax*8+0],dx                       ; Store the new limit 0:15
        shr     edx,16                                          ; Move over to store the next part of the limit
        and     dl,0fh                                          ; Mask off the top nibble (the limit is only 20 bits)
        or      dl,11000000b                                    ; make granularity=1, big=1 (high bits in dl)
    .ELSE
      ; It's a small data descriptor (leave the granularity at 0)
        mov     word ptr [esi+eax*8+0],dx                       ; limit 0:15
        shr     edx,16
        and     dl,0fh
    .ENDIF
    mov     byte ptr [esi+eax*8+6],dl                           ; limit 16:19, Granularity=0/1, big=0/1 (depends on size)
    mov     byte ptr [esi+eax*8+7],bl                           ; base 24:31

    popad
    ret
create_data_descriptor      ENDP




create_data_descriptor_pl       PROC    NEAR
; Upon entry, ds:[esi] - far ptr to GDT
;                  eax - slot # to insert
;                  ebx - base
;                  edx - limit
;                   cl - privledge level
;
    pushad

    mov     word ptr [esi+eax*8+2],bx                           ; base 0:15
    shr     ebx,16
    mov     byte ptr [esi+eax*8+4],bl                           ; base 16:23
    shr     ebx,8
    shl     cl,5
    mov     byte ptr [esi+eax*8+5],10010010b                    ; Not accessed, writeable, expand=0, (PL=00 for now)
    or      byte ptr [esi+eax*8+5],cl                           ; Apply the privledge level
    .IF (edx > 0fffffh)
      ; This is a BIG data descriptor (so, we have to change the granularity to 1)
      ; Also, setting the granularity bit makes the limit value be the number of 4k segments
        shr     edx,12                                          ; Divide by 4096
        mov     word ptr [esi+eax*8+0],dx                       ; Store the new limit 0:15
        shr     edx,16                                          ; Move over to store the next part of the limit
        and     dl,0fh                                          ; Mask off the top nibble (the limit is only 20 bits)
        or      dl,11000000b                                    ; make granularity=1, big=1 (high bits in dl)
    .ELSE
      ; It's a small data descriptor (leave the granularity at 0)
        mov     word ptr [esi+eax*8+0],dx                       ; limit 0:15
        shr     edx,16
        and     dl,0fh
    .ENDIF
    mov     byte ptr [esi+eax*8+6],dl                           ; limit 16:19, Granularity=0/1, big=0/1 (depends on size)
    mov     byte ptr [esi+eax*8+7],bl                           ; base 24:31

    popad
    ret
create_data_descriptor_pl       ENDP




create_ldt_descriptor   PROC
; Upon entry, ds:[esi] - far ptr to GDT
;                  eax - slot # to insert
;                  ebx - base
;                  edx - limit
;
    pushad

    mov     word ptr [esi+eax*8+2],bx                           ; base 0:15
    shr     ebx,16
    mov     byte ptr [esi+eax*8+4],bl                           ; base 16:23
    shr     ebx,8
    mov     byte ptr [esi+eax*8+5],10000010b                    ; Not accessed, writeable, expand=0, DPL=00
    .IF (edx > 0fffffh)
      ; This is a BIG data descriptor (so, we have to change the granularity to 1)
      ; Also, setting the granularity bit makes the limit value be the number of 4k segments
        shr     edx,12                                          ; Divide by 4096
        mov     word ptr [esi+eax*8+0],dx                       ; Store the new limit 0:15
        shr     edx,16                                          ; Move over to store the next part of the limit
        and     dl,0fh                                          ; Mask off the top nibble (the limit is only 20 bits)
        or      dl,11000000b                                    ; make granularity=1, big=1 (high bits in dl)
    .ELSE
      ; It's a small data descriptor (leave the granularity at 0)
        mov     word ptr [esi+eax*8+0],dx                       ; limit 0:15
        shr     edx,16
        and     dl,0fh
    .ENDIF
    mov     byte ptr [esi+eax*8+6],dl                           ; limit 16:19, Granularity=0/1, big=0/1 (depends on size)
    mov     byte ptr [esi+eax*8+7],bl                           ; base 24:31

    popad
    ret
create_ldt_descriptor   ENDP




create_code_descriptor   PROC    NEAR
; Upon entry, ds:[esi] - far ptr to GDT
;                  eax - slot # to insert
;                  ebx - base
;                  edx - limit
    pushad

    mov     word ptr [esi+eax*8+0],dx                           ; limit 0:15
    shr     edx,16
    mov     word ptr [esi+eax*8+2],bx                           ; base 0:15
    shr     ebx,16
    mov     byte ptr [esi+eax*8+4],bl                           ; base 16:23
    shr     ebx,8
    mov     byte ptr [esi+eax*8+5],10011010b                    ; Not accessed, readable, conforming=0, DPL=00
    and     dl,0fh
    or      dl,01000000b
    mov     byte ptr [esi+eax*8+6],dl                           ; limit 16:19, Granularity=0, big=0
    mov     byte ptr [esi+eax*8+7],bl                           ; base 24:31

    popad
    ret
create_code_descriptor   ENDP




create_interrupt_descriptor_32_bit      PROC    NEAR
; Upon entry: eax - interrupt # to update (0-based)
;        ds:[esi] - far pointer to start of IDT
;             edx - offset in bx to routine
;             ebx - segment selector of routine
    pushad

    mov     ecx,edx                                             ; Copy 32-bit offset to ecx
    and     edx,00000ffffh                                      ; Keep lower 16-bits in edx
    and     ecx,0ffff0000h                                      ; Keep upper 16-bits in ecx
    mov     cx,1000111000000000b                                ; Add lower 16-bits in ecx, 32-bit, DPL=0, Present
    ror     edx,16                                              ; Move edx around so we can access the high word
    mov     dx,bx                                               ; Segment selector
    ror     edx,16                                              ; Ok, put it back the way it was

    mov     dword ptr [esi+eax*8+0],edx                         ; Store the IDT descriptor
    mov     dword ptr [esi+eax*8+4],ecx

    popad
    ret
create_interrupt_descriptor_32_bit      ENDP




create_interrupt_descriptors    PROC    NEAR
; Create all of the interrupt descriptors.  All 256 of them.
; Upon entry:   ds:[esi] - far ptr to start of IDT
;
    pushad

    mov     ebx,_sCODE                                              ; Code segment
    mov     edx,offset default_interrupt_handler32                  ; Default interrupt handler for 32-bit code
    mov     ecx,255
    mov     eax,0                                                   ; Start at int 0 in the IDT
  @@:
    call    create_interrupt_descriptor_32_bit
    inc     eax
    loop    @b

    popad
    ret
create_interrupt_descriptors    ENDP




create_exodus_tss_descriptor    PROC
; Upon entry, ds:[esi] - far ptr to memory location for the TSS descriptor
;                  eax - slot # to insert
;                  ebx - base
;                  ecx - offset of first instruction
;                  edx - limit
    push    es
    pushad
    mov     edi,ebx

  ; Create the TSS descriptor
    mov     word ptr [esi+eax*8+0],dx                           ; limit 0:15
    mov     word ptr [esi+eax*8+2],bx                           ; base 0:15
    shr     ebx,16
    mov     byte ptr [esi+eax*8+4],bl                           ; base 16:23
    shr     ebx,8
    mov     byte ptr [esi+eax*8+5],10001001b                    ; present=1:dpl=00:010:busy=1:1
    shr     edx,16
    and     dl,0fh                                              ; make the top nibble be all 0s
    mov     byte ptr [esi+eax*8+6],dl                           ; Granularity=0:0:0:Available=0:limit 16:19
    mov     byte ptr [esi+eax*8+7],bl                           ; base 24:31

  ; Write the Exodus variables there
    mov     ebx,edi
    shr     ebx,4
    mov     es,bx
    and     edi,0fh
  ; Right now, es:[edi] - far ptr the memory location for Exodus
  ; Code segment register
    mov     eax,_sCODE
    mov     dword ptr es:[edi+_TSS_CS],eax                          ; cs
  ; Instruction Pointer
    mov     dword ptr es:[edi+_TSS_EIP],ecx                         ; eip
  ; Data segment registers
    mov     eax,_sDATA
    mov     dword ptr es:[edi+_TSS_DS],eax                          ; ds
    mov     dword ptr es:[edi+_TSS_ES],eax                          ; es
  ; Extra segment registers
    mov     eax,_sVGA
    mov     dword ptr es:[edi+_TSS_FS],eax                          ; fs
    mov     eax,_sMONO
    mov     dword ptr es:[edi+_TSS_GS],eax                          ; gs
  ; Stack
    mov     eax,_sSTACK
    mov     dword ptr es:[edi+_TSS_SS],eax                          ; ss
    mov     dword ptr es:[edi+_TSS_ESP],_sSTACK_limit               ; esp
  ; Stack 2
    mov     eax,_sSTACK2
    mov     dword ptr es:[edi+_TSS_SS2],eax                         ; ss2
    mov     dword ptr es:[edi+_TSS_ESP2],_sSTACK2_limit             ; esp2
  ; Stack 1
    mov     eax,_sSTACK1
    mov     dword ptr es:[edi+_TSS_SS1],eax                         ; ss1
    mov     dword ptr es:[edi+_TSS_ESP1],_sSTACK1_limit             ; esp1
  ; Stack 0
    mov     eax,_sSTACK0
    mov     dword ptr es:[edi+_TSS_SS0],eax                         ; ss0
    mov     dword ptr es:[edi+_TSS_ESP0],_sSTACK0_limit             ; esp0
  ; General purpose registers
    xor     eax,eax
    mov     dword ptr es:[edi+_TSS_EAX],eax                         ; eax
    mov     dword ptr es:[edi+_TSS_ECX],eax                         ; ecx
    mov     dword ptr es:[edi+_TSS_EDX],eax                         ; edx
    mov     dword ptr es:[edi+_TSS_EBX],eax                         ; ebx
    mov     dword ptr es:[edi+_TSS_EBP],eax                         ; ebp
    mov     dword ptr es:[edi+_TSS_ESI],eax                         ; esi
    mov     dword ptr es:[edi+_TSS_EDI],eax                         ; edi
    mov     dword ptr es:[edi+_TSS_CR3],eax                         ; CR3, paging (not used in Exodus)
    mov     dword ptr es:[edi+_TSS_IO_MAP],eax                      ; IO Map Base Address, Trap bit
    mov     dword ptr es:[edi+_TSS_BACK_LINK],eax                   ; Previous task link
    xor     eax,eax
    mov     dword ptr es:[edi+_TSS_LDT],eax                         ; LDT segment selector
  ; EFLAGS
    pushfd
    pop     eax
    mov     dword ptr es:[edi+_TSS_EFLAGS],eax

  ; Finished
    popad
    pop     es
    ret
create_exodus_tss_descriptor    ENDP





create_call_gate_descriptor     PROC
; This routine is used to create a call gate
; Upon entry: ds:[esi] - far ptr to GDT
;                  eax - GDT slot # to create/update
;                  ebx - Offset for start of function
;                  ecx - Number of dwords to copy
;                   dx - code segment selector
;
    pushad

    mov     word ptr [esi+eax*8+2],dx                               ; code segment selector
    and     cx,011111b                                              ; Keep the lower 5 bits
    or      cx,1000110000000000b                                    ; Put parameters in the upper 11 bits
    mov     word ptr [esi+eax*8+4],cx                               ; dword count + constants
    mov     word ptr [esi+eax*8+0],bx                               ; Lower 16-bits of 32-bit offset
    ror     ebx,16
    mov     word ptr [esi+eax*8+6],bx                               ; Upper 16-bits of 32-bit offset

    popad
    ret
create_call_gate_descriptor     ENDP





create_task_gate_descriptor     PROC
; Upon entry, ds:[esi] - far ptr to memory location for the TSS descriptor
;                  eax - slot # to insert
;                  bx - GDT slot for TSS
    pushad

    shl     ebx,16                                              ; Move bx(TSS selector) to high-order word in ebx
    mov     dword ptr [esi+eax*8+0],ebx
    xor     ebx,ebx
    mov     bh,10000101b                                        ; present=1:dpl=00:00101
    mov     dword ptr [esi+eax*8+4],ebx

    popad
    ret
create_task_gate_descriptor     ENDP