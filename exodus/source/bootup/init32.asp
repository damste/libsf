; init32.asp
;
; Exodus initialization routines (32-bit code)
;
;  Functions:
;     Ã invCreate_call_gate_descriptor32            ; Creates a new call gate in the GDT
;     Ã invCreate_task_gate_descriptor32            ; Creates a new task gate in the GDT
;     Ã invCreate_interrupt_task_gate_descriptor32  ; Creates a new task gate in the IDT
;     Ã invCreate_code_descriptor32                 ; Creates a new code segment descriptor
;     Ã invCreate_data_descriptor32                 ; Creates a new data segment descriptor
;     Ã invCreate_tss_descriptor32                  ; Creates a new 32-bit TSS descriptor entry
;     Ã invCreate_tss32                             ; Initializes a 32-bit TSS
;     Ã invUpdate_interrupt_descriptor16            ; Used after initialization to update an IDT entry
;     Ã invUpdate_interrupt_descriptor32            ; Used after initialization to update an IDT entry
;     Ã invExtract_code_descriptor32                ; Extracts the information in a code descriptor segment
;     Ã invExtract_call_gate_descriptor32           ; Extracts the information in a call gate descriptor segment
;     Ã invExtract_data_descriptor32                ; Extracts the information in a data descriptor segment
;     Ã invAlter_descriptor32_base_limit            ; Used after initialization to alter a GDT entry's base and/or limit
;     Ã invSetup_memory_blocks                      ; Sets up the initial values in Exodus memory blocks
;     Ã invExtract_linear_offset_into_edx_from_ds   ; Extracts a linear offset from the current value of DS
;     Ã invSet_80x25_text_mode                      ; Calls the VID_requestor() function to enter 80x25 text mode (for errors)
;     À init_failed                                 ; Used when there is a problem initializing primatives
;



invCreate_call_gate_descriptor32   PROC
; This routine is used to create a call gate
; Upon entry:   cpu is in pmode
;               eax - GDT slot # to create/update
;               ebx - Offset for start of function
;               ecx - Number of dwords to copy
;                dx - code segment selector
;
    pushfd
    .IF (eax <= _lastGDT)
        push    ds
        push    esi
        push    ecx
        push    ebx

        mov     si,_sGDT
        mov     ds,si
        mov     word ptr ds:[eax*8+2],dx                            ; code segment selector
        and     cx,011111b                                          ; Keep the lower 5 bits
        or      cx,1000110000000000b                                ; Put parameters in the upper 11 bits
        mov     word ptr ds:[eax*8+4],cx                            ; dword count + constants
        mov     word ptr ds:[eax*8+0],bx                            ; Lower 16-bits of 32-bit offset
        ror     ebx,16
        mov     word ptr ds:[eax*8+6],bx                            ; Upper 16-bits of 32-bit offset

        pop     ebx
        pop     ecx
        pop     esi
        pop     ds
    .ENDIF
    popfd
    ret
invCreate_call_gate_descriptor32   ENDP




invCreate_task_gate_descriptor32   PROC
; This routine is used to create a task gate in the GDT
; Upon entry:   cpu is in pmode
;               eax - GDT slot # to create/update
;                bx - Task's TSS
;
    pushfd
    .IF (eax <= _lastGDT)
        push    ds
        push    esi
        push    ebx

        mov     si,_sGDT
        mov     ds,si

        shl     ebx,16
        mov     dword ptr ds:[eax*8+0],ebx                          ; TSS Segment Selector
        xor     ebx,ebx
        mov     bh,10000101b                                        ; P=1:DPL=00:00101:00000000
        mov     dword ptr ds:[eax*8+4],ebx

        pop     ebx
        pop     esi
        pop     ds
    .ENDIF
    popfd
    ret
invCreate_task_gate_descriptor32   ENDP




invCreate_interrupt_task_gate_descriptor32   PROC
; This routine is used to create a task gate in the IDT
; Upon entry:   cpu is in pmode
;               eax - IDT slot # to create/update
;                bx - Task's TSS
;
    pushfd
    .IF (eax <= 256)
        push    ds
        push    esi
        push    ebx

        mov     si,_sIDT
        mov     ds,si

        shl     ebx,16
        mov     dword ptr ds:[eax*8+0],ebx                          ; TSS Segment Selector
        xor     ebx,ebx
        mov     bh,10000101b                                        ; P=1:DPL=00:00101:00000000
        mov     dword ptr ds:[eax*8+4],ebx

        pop     ebx
        pop     esi
        pop     ds
    .ENDIF
    popfd
    ret
invCreate_interrupt_task_gate_descriptor32   ENDP




invCreate_code_descriptor32    PROC    NEAR
; Upon entry, eax - slot # to insert
;             ebx - base
;             edx - limit
;
    pushfd
    .IF (eax <= _lastGDT)
        push    ds
        push    esi
        push    ebx
        push    edx

        mov     di,_sGDT
        mov     ds,di

      ; Fixed information, not accessed, readable, conforming=0, DPL=00
        mov     byte ptr ds:[eax*8+5],10011010b

      ; Base
        mov     word ptr ds:[eax*8+2],bx                            ; base 0:15
        shr     ebx,16
        mov     byte ptr ds:[eax*8+4],bl                            ; base 16:23
        shr     ebx,8
        mov     byte ptr ds:[eax*8+7],bl                            ; base 24:31

      ; Limit
        .IF (edx > 0fffffh)
          ; It's bigger than 20 bits (so, we have to change the granularity to 1)
          ; This is a BIG data descriptor
          ; Also, setting the granularity bit makes the limit value be the number of 4k segments
            shr     edx,12                                          ; Divide by 4096
            mov     word ptr ds:[eax*8+0],dx                        ; Store the new limit 0:15
            shr     edx,16                                          ; Move over to store the next part of the limit
            and     dl,0fh                                          ; Mask off the top nibble (the limit is only 20 bits)
            or      dl,10000000b                                    ; make granularity=1
        .ELSE
          ; It's a small data descriptor (leave the granularity at 0)
            mov     word ptr ds:[eax*8+0],dx                        ; limit 0:15
            shr     edx,16
            and     dl,0fh
        .ENDIF
        or      dl,01000000b                                        ; 32-bit code
        mov     byte ptr ds:[eax*8+6],dl                            ; limit 16:19, Granularity=0

        pop     edx
        pop     ebx
        pop     esi
        pop     ds
    .ENDIF
    popfd
    ret
invCreate_code_descriptor32    ENDP




invCreate_data_descriptor32    PROC    NEAR
; Upon entry, eax - slot # to insert
;             ebx - base
;             edx - limit
;
    pushfd
    .IF (eax <= _lastGDT)
        push    ds
        push    ecx
        push    ebx
        push    edx

        mov     cx,_sGDT
        mov     ds,cx

        mov     word ptr ds:[eax*8+2],bx                            ; base 0:15
        shr     ebx,16
        mov     byte ptr ds:[eax*8+4],bl                            ; base 16:23
        mov     byte ptr ds:[eax*8+7],bh                            ; base 24:31
        mov     byte ptr ds:[eax*8+5],10010010b                     ; Not accessed, writeable, expand=0, DPL=00
        .IF (edx > 0fffffh)
          ; It's bigger than 20 bits (so, we have to change the granularity to 1)
          ; This is a BIG data descriptor
          ; Also, setting the granularity bit makes the limit value be the number of 4k segments
            shr     edx,12                                          ; Divide by 4096
            mov     word ptr ds:[eax*8+0],dx                        ; Store the new limit 0:15
            shr     edx,16                                          ; Move over to store the next part of the limit
            and     dl,0fh                                          ; Mask off the top nibble (the limit is only 20 bits)
            or      dl,11000000b                                    ; make granularity=1, big=1 (high bits in dl)
        .ELSE
          ; It's a small data descriptor (leave the granularity at 0)
            mov     word ptr ds:[eax*8+0],dx                        ; limit 0:15
            shr     edx,16
            and     dl,0fh
        .ENDIF
        mov     byte ptr ds:[eax*8+6],dl                            ; limit 16:19, Granularity=0/1, big=0/1 (depends on size)

        pop     edx
        pop     ebx
        pop     ecx
        pop     ds
    .ENDIF
    popfd
    ret
invCreate_data_descriptor32    ENDP




invExtract_code_descriptor32        PROC    NEAR
; This routine takes an already existent code segment and extracts the base and limit
;
; Upon entry, eax - GDT offset
;
; Upon exit:  ebx - base
;             edx - limit
;
    pushfd
    .IF (eax <= _lastGDT * 8)
        push    ds
        push    ecx

        mov     cx,_sGDT
        mov     ds,cx

      ; Get the limit
        xor     edx,edx
        mov     dx,word ptr [eax]
        ror     edx,16
        mov     dl,byte ptr [eax+6]
        and     dl,0fh
        rol     edx,16
        test    byte ptr [eax+6],10000000b                          ; See if the "G" bit is set
        .IF (!zero?)
          ; It is set for granularity
            shl     edx,12
        .ENDIF

      ; Get the base
        mov     ebx,dword ptr [eax+2]
        and     ebx,0ffffffh
        rol     ebx,8
        mov     bl,byte ptr [eax+7]
        ror     ebx,8

        pop     ecx
        pop     ds
    .ENDIF
    popfd
    ret
invExtract_code_descriptor32        ENDP




invExtract_call_gate_descriptor32       PROC    NEAR
; This routine takes an already existent code segment and extracts the base and limit
;
; Upon entry, eax - GDT offset
;
; Upon exit:  ebx - offset
;             ecx - param count
;             edx - code segment
;
    pushfd
    .IF (eax <= _lastGDT * 8)
        push    ds

        mov     edx,_sGDT
        mov     ds,edx

      ; Get the offset
        xor     ebx,ebx
        mov     bx,word ptr ds:[eax]
        ror     ebx,16
        mov     bx,word ptr ds:[eax+6]
        ror     ebx,16

      ; Get the param count
        movzx   ecx,byte ptr ds:[eax+4]

      ; Get the code selector
        movzx   edx,word ptr ds:[eax+2]

        pop     ds
    .ENDIF
    popfd
    ret
invExtract_call_gate_descriptor32       ENDP




invExtract_data_descriptor32        PROC    NEAR
; This routine takes an already existent data segment and extracts the base and offset
;
; Upon entry:   eax - GDT offset
;
; Upon exit:    ebx - base
;               edx - limit
;
    pushfd
    .IF (eax <= _lastGDT * 8)
        push    ds
        push    ecx

        mov     ecx,_sGDT
        mov     ds,ecx

      ; Get the limit
        xor     edx,edx
        mov     dx,word ptr [eax]
        ror     edx,16
        mov     dl,byte ptr [eax+6]
        and     dl,0fh
        rol     edx,16
        test    byte ptr [eax+6],10000000b                          ; See if the "G" bit is set
        .IF (!zero?)
          ; It is set for granularity
            shl     edx,12
        .ENDIF

      ; Get the base
        mov     ebx,dword ptr [eax+2]
        and     ebx,0ffffffh
        rol     ebx,8
        mov     bl,byte ptr [eax+7]
        ror     ebx,8

        pop     ecx
        pop     ds
    .ENDIF
    popfd
    ret
invExtract_data_descriptor32        ENDP




invAlter_descriptor32_base_limit    PROC
; This routine is used to alter the base and/or limit of an existing GDT entry
;
; Upon entry:   edx - slot
;               esi - new base
;               edi - new limit
;
; Upon exit:    Value is updated if edx is valid
;

    pushfd
    .IF (edx <= _lastGDT)
        push    ds
        push    ecx
        push    ebx
        push    eax

        mov     ecx,_sGDT
        mov     ds,ecx
      ; Right now,  ds:[edx*8] - far ptr to GDT entry
      ;             esi - new base
      ;             edi - new limit
        mov     ebx,esi
        mov     eax,edi
        .IF (eax > 0fffffh)
          ; Turn on the granularity bit
            shr     eax,12
            or      byte ptr ds:[edx*8+6],10000000b
        .ELSE
          ; Turn off the granularity bit
            and     byte ptr ds:[edx*8+6],not 10000000b
        .ENDIF

        mov     word ptr ds:[edx*8+0],ax                            ; limit 0-15
        mov     word ptr ds:[edx*8+2],bx                            ; base 0-15
        shr     eax,16
        shr     ebx,16
        mov     byte ptr ds:[edx*8+4],bl                            ; base 16-23
        mov     byte ptr ds:[edx*8+7],bh                            ; base 24-31

        and     al,0fh
        and     byte ptr ds:[edx*8+6],0f0h
        or      byte ptr ds:[edx*8+6],al
      ; Right now, it's updated

        pop     eax
        pop     ebx
        pop     ecx
        pop     ds
    .ENDIF
    popfd
    ret
invAlter_descriptor32_base_limit    ENDP




invExtract_linear_offset_into_edx_from_ds   PROC
; This routine is used to extract the linear offset from the GDT value in ds
;
; Upon entry:   ds - GDT slot being searched for
;
; Upon exit:    edx - linear offset
;
    pushfd
    push    eax

    mov     eax,ds
    .IF (eax <= _lastGDT * 8)
        push    ds
        push    ecx

        mov     cx,_sGDT
        mov     ds,cx

      ; Get the base (linear offset)
        mov     edx,dword ptr [eax+2]
        and     edx,0ffffffh
        rol     edx,8
        mov     dl,byte ptr [eax+7]
        ror     edx,8

        pop     ecx
        pop     ds
    .ENDIF

    pop     eax
    popfd
    ret
invExtract_linear_offset_into_edx_from_ds   ENDP




invCreate_tss_descriptor32     PROC
; Upon entry, eax - slot # to insert
;             ebx - base
;             edx - limit
;
    pushfd
    .IF (eax <= _lastGDT)
        push    ds
        push    esi
        push    ebx
        push    edx

        mov     si,_sGDT
        mov     ds,si

        mov     word ptr [eax*8+2],bx                               ; base 0:15
        shr     ebx,16
        mov     byte ptr [eax*8+4],bl                               ; base 16:23
        mov     byte ptr [eax*8+7],bh                               ; base 24:31
        mov     word ptr [eax*8+0],dx                               ; limit 0:15
        shr     edx,16
        and     dl,0fh                                              ; make the top nibble be all 0s
        mov     byte ptr [eax*8+6],dl                               ; Granularity=0:0:0:Available=0:limit 16:19
        mov     byte ptr [eax*8+5],10001001b                        ; present=1:dpl=00:010:busy=0:1

        pop     edx
        pop     ebx
        pop     esi
        pop     ds
    .ENDIF
    popfd
    ret
invCreate_tss_descriptor32     ENDP




invCreate_tss32    PROC
; Upon entry, ds:[esi] - far ptr to offset in memory to create the TSS
;                  ebx - code segment selector
;                  ecx - first instruction offset
;                  edx - stack segment selector
;                  edi - esp value
    push eax

  ; Code segment register
    mov     dword ptr ds:[esi+76],ebx                           ; cs
  ; Instruction Pointer
    mov     dword ptr ds:[esi+32],ecx                           ; eip
  ; Stack
    mov     dword ptr ds:[esi+80],edx                           ; ss
    mov     dword ptr ds:[esi+56],edi                           ; esp
  ; Data segment registers
    mov     eax,_sDATA
    mov     dword ptr ds:[esi+84],eax                           ; ds
    mov     dword ptr ds:[esi+72],eax                           ; es
  ; Extra segment registers
    mov     eax,_sVGA
    mov     dword ptr ds:[esi+88],eax                           ; fs
    mov     eax,_sMONO
    mov     dword ptr ds:[esi+92],eax                           ; gs
  ; Stack 2
    mov     eax,_sSTACK2
    mov     dword ptr ds:[esi+24],eax                           ; ss2
    mov     dword ptr ds:[esi+20],07fch                         ; esp2
  ; Stack 1
    mov     eax,_sSTACK1
    mov     dword ptr ds:[esi+16],eax                           ; ss1
    mov     dword ptr ds:[esi+12],07fch                         ; esp1
  ; Stack 0
    mov     eax,_sSTACK0
    mov     dword ptr ds:[esi+8],eax                            ; ss0
    mov     dword ptr ds:[esi+4],07fch                          ; esp0
  ; General purpose registers
    xor     eax,eax
    mov     dword ptr ds:[esi+40],eax                           ; eax
    mov     dword ptr ds:[esi+44],eax                           ; ecx
    mov     dword ptr ds:[esi+48],eax                           ; edx
    mov     dword ptr ds:[esi+52],eax                           ; ebx
    mov     dword ptr ds:[esi+60],eax                           ; ebp
    mov     dword ptr ds:[esi+64],eax                           ; esi
    mov     dword ptr ds:[esi+68],eax                           ; edi
    mov     dword ptr ds:[esi+28],eax                           ; CR3, paging (not used in Exodus)
    mov     dword ptr ds:[esi+100],eax                          ; IO Map Base Address, Trap bit
    mov     dword ptr ds:[esi+0],eax                            ; Previous task link
    xor     eax,eax
    mov     dword ptr ds:[esi+96],eax                           ; LDT segment selector
  ; EFLAGS
    pushfd
    pop     eax
    mov     dword ptr ds:[esi+36],eax

    pop     eax
    ret
invCreate_tss32    ENDP




invUpdate_interrupt_descriptor16   PROC
; Upon entry, eax - interrupt # to update (0-based)
;             edx - offset in bx to routine
;              bx - segment selector of routine
    push    ecx
    push    edx
    push    fs

    mov     cx,_sIDT                                                ; IDT slot in GDT
    mov     fs,cx
    mov     ecx,edx                                                 ; Copy 32-bit offset to ecx
    and     edx,00000ffffh                                          ; Keep lower 16-bits in edx
    and     ecx,0ffff0000h                                          ; Keep upper 16-bits in ecx
    mov     cx,1000011000000000b                                    ; Add lower 16-bits in ecx, 16-bit, DPL=0, Present
    ror     edx,16                                                  ; Move edx around so we can access the high word
    mov     dx,bx                                                   ; Segment selector
    ror     edx,16                                                  ; Ok, put it back the way it was

    cli
    mov     dword ptr fs:[eax*8+0],edx                              ; Store the IDT descriptor
    mov     dword ptr fs:[eax*8+4],ecx
    sti

    pop     fs
    pop     edx
    pop     ecx
    ret
invUpdate_interrupt_descriptor16   ENDP




invUpdate_interrupt_descriptor32   PROC
; Upon entry, eax - interrupt # to update (0-based)
;             edx - offset in bx to routine
;              bx - segment selector of routine
    push    ecx
    push    edx
    push    fs

    mov     cx,_sIDT                                                ; IDT slot in GDT
    mov     fs,cx
    mov     ecx,edx                                                 ; Copy 32-bit offset to ecx
    and     edx,00000ffffh                                          ; Keep lower 16-bits in edx
    and     ecx,0ffff0000h                                          ; Keep upper 16-bits in ecx
    mov     cx,1000111000000000b                                    ; Add control bits to ecx, 32-bit, DPL=0, Present
    ror     edx,16                                                  ; Move edx around so we can access the high word
    mov     dx,bx                                                   ; Segment selector
    ror     edx,16                                                  ; Ok, put it back the way it was

    cli
    mov     dword ptr fs:[eax*8+0],edx                              ; Store the IDT descriptor
    mov     dword ptr fs:[eax*8+4],ecx
    sti

    pop     fs
    pop     edx
    pop     ecx
    ret
invUpdate_interrupt_descriptor32   ENDP





invSetup_memory_blocks      PROC
; This routine is used to setup required memory blocks for Exodus
;
; Upon entry:   This function is called as the first function in protected mode
;               It is known that all of the standard GDT entries are setup (those before _sEXODUS_REQUESTOR)
;
; Upon exit:    These memory blocks are setup with their default structures/info:
;                   _sEXODUS_MEM            ; Refer to inf\exodus.inf for more information
;                   _sEXODUS_PORTS          ; Refer to inf\exodus.inf for more information
;                   _sEXODUS_INTS           ; Refer to inf\exodus.inf for more information
;                   _sSYSTEM                ; Various memory regions
;
    push    eax
    push    esi
    push    ds


;; Do the Exodus memory block regions
    mov     ax,_sEXODUS_MEM
    mov     ds,ax
    mov     dword ptr ds:[0],4 + _EXODUS_MEM_size                   ; The length of this structure plus the initial dword
    mov     esi,4
    mov     byte ptr ds:[esi+_EXODUS_MEM_type],0                    ; Free block
    mov     dword ptr ds:[esi+_EXODUS_MEM_base],100000h             ; Start at 1MB
    mov     dword ptr ds:[esi+_EXODUS_MEM_limit],100000h            ; Limit (1MB, Exodus requires 2MB of RAM to boot)
    mov     dword ptr ds:[esi+_EXODUS_MEM_gdt],0


;; Do the Exodus port assignments
    mov     ax,_sEXODUS_PORTS
    mov     ds,ax
    mov     dword ptr ds:[0],4                                      ; 4 = The initial dword only (no ports are auto reserved)


;; Do the Exodus interrupt assignments
    mov     ax,_sEXODUS_INTS
    mov     ds,ax
    mov     dword ptr ds:[0],4                                      ; 4 = The initial dword only (no ports are auto reserved)


;; Do the Exodus system memory area
    mov     ax,_sSYSTEM
    mov     ds,ax
  ; These values are Exodus internal
    mov     word ptr ds:[_SYSTEM_i_GDT_TO_ASSIGN],_firstASSIGNMENT
    mov     word ptr ds:[_SYSTEM_i_USER_GDT_TO_ASSIGN],_firstUSER_ASSIGNMENT
  ; These values are user application accessible
    mov     dword ptr ds:[_SYSTEM_TOTAL_MEMORY],200000h             ; Default to 2MB until we know otherwise


    pop     ds
    pop     esi
    pop     eax
    ret
invSetup_memory_blocks      ENDP




invSet_80x25_text_mode      PROC
; This routine is called from various places in Exodus's core.  It calls the VID_requestor() function to enter an 80x25 text mode
; This is usually used for displaying errors, etc.
;
; Upon entry:   Nothing
;
; Upon exit:    Nothing
;
    push    dword ptr 0                                         ; return: bits per pixel
    push    dword ptr 0                                         ; return: horizontal pixels
    push    dword ptr 0                                         ; return: vertical pixels
    push    dword ptr 0                                         ; return: refresh rate
    push    dword ptr 0                                         ; return: status
    push    dword ptr 1                                         ; input: text mode
    push    dword ptr 8                                         ; input: bits per pixel
    push    dword ptr 80                                        ; input: horizontal pixels
    push    dword ptr 25                                        ; input: vertical pixels
    push    dword ptr 60                                        ; input: refresh rate
    mov     eax,1
    call    fword ptr cs:_VID_requestor
    add     esp,20                                              ; get the values off the stack (we know this works)
    ret
invSet_80x25_text_mode      ENDP