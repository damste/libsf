display_register_name_indirect_sib:
    push    cx
    push    edx
    cmp     al,0100b
    jz      @F
    mov     cx,3
    .IF (al == 000b)
      ; eax
        mov     dx,offset eax_register
    .ELSEIF (al == 001b)
        mov     dx,offset ecx_register
    .ELSEIF (al == 010b)
        mov     dx,offset edx_register
    .ELSEIF (al == 011b)
        mov     dx,offset ebx_register
    .ELSEIF (al == 101b)
        mov     dx,offset ebp_register
    .ELSEIF (al == 110b)
        mov     dx,offset esi_register
    .ELSE ; (al == 111b)
        mov     dx,offset edi_register
    .ENDIF
    jmp     sib_display_it

  @@:
    ; sib byte is present
    xor     edx,edx
    mov     cx,3
    mov     al,CS:sib_byte
    and     al,0111b
    .IF (al == 000b)
        mov     dx,offset eax_register
    .ELSEIF (al == 001b)
        mov     dx,offset ecx_register
    .ELSEIF (al == 010b)
        mov     dx,offset edx_register
    .ELSEIF (al == 011b)
        mov     dx,offset ebx_register
    .ELSEIF (al == 100b)
        mov     dx,offset esp_register
    .ELSEIF (al == 101b)
        mov     al,CS:sib_byte
        shr     al,6
        cmp     al,00
        jnz     @F
        jmp     check_index
      @@:
        mov     dx,offset ebp_register
    .ELSEIF (al == 110b)
        mov     dx,offset esi_register
    .ELSE
        mov     dx,offset edi_register
    .ENDIF
    call    write_screen_cs_edx_no_color
  check_index:
    mov     cx,3
    mov     al,CS:sib_byte
    shr     al,3
    and     al,0111b
    .IF (al == 000b)
        mov     dx,offset eax_register
    .ELSEIF (al == 001b)
        mov     dx,offset ecx_register
    .ELSEIF (al == 010b)
        mov     dx,offset edx_register
    .ELSEIF (al == 011b)
        mov     dx,offset ebx_register
    .ELSEIF (al == 100b)
        jmp     sib_done
    .ELSEIF (al == 101b)
        mov     dx,offset ebp_register
    .ELSEIF (al == 110b)
        mov     dx,offset esi_register
    .ELSEIF (al == 111b)
        mov     dx,offset edi_register
    .ENDIF
    call    display_plus_sign
    call    write_screen_cs_edx_no_color

    mov     al,CS:sib_byte
    shr     al,6
    cmp     al,01b
    jnz     @F
    jmp     sib_mod_01
  @@:
    cmp     al,10b
    jnz     @F
    jmp     sib_mod_10
  @@:
    cmp     al,11b
    jnz     sib_done
    jmp     sib_mod_11

  sib_mod_01:
    call    display_scale_2
    jmp     sib_done
  sib_mod_10:
    call    display_scale_4
    jmp     sib_done
  sib_mod_11:
    call    display_scale_8
    jmp     sib_done

  sib_display_it:
    call    write_screen_cs_edx_no_color
  sib_done:
    pop     edx
    pop     cx
    ret


display_register_name_indirect_32:
    push    cx
    push    edx
    xor     edx,edx
    mov     cx,3
    .IF (al == 000b)
        mov     dx,offset ebx_esi_register
        mov     cx,7
    .ELSEIF (al == 001b)
        mov     dx,offset ebx_edi_register
        mov     cx,7
    .ELSEIF (al == 010b)
        mov     dx,offset ebp_esi_register
        mov     cx,7
    .ELSEIF (al == 011b)
        mov     dx,offset ebp_edi_register
        mov     cx,7
    .ELSEIF (al == 100b)
        mov     dx,offset esi_register
    .ELSEIF (al == 101b)
        mov     dx,offset edi_register
    .ELSEIF (al == 110b)
        mov     dx,offset ebp_register
    .ELSE
        mov     dx,offset ebx_register
    .ENDIF
    call    write_screen_cs_edx_no_color
    pop     edx
    pop     cx
    ret


display_register_name_indirect_16:
    push    cx
    push    edx
    cmp     CS:op_size_override,0
    jnz     @F
    jmp     drni16_cont_1
  @@:
  ; It has a SIB byte
    mov     al,CS:sib_byte
    call    display_register_name_indirect_sib
    ret
  drni16_cont_1:
    xor     edx,edx
    mov     cx,2
    .IF (al == 000b)
        mov     dx,offset bx_si_register
        mov     cx,5
    .ELSEIF (al == 001b)
        mov     dx,offset bx_di_register
        mov     cx,5
    .ELSEIF (al == 010b)
        mov     dx,offset bp_si_register
        mov     cx,5
    .ELSEIF (al == 011b)
        mov     dx,offset bp_di_register
        mov     cx,5
    .ELSEIF (al == 100b)
        mov     dx,offset si_register
    .ELSEIF (al == 101b)
        mov     dx,offset di_register
    .ELSEIF (al == 110b)
        mov     dx,offset bp_register
    .ELSE
        mov     dx,offset bx_register
    .ENDIF
    call    write_screen_cs_edx_no_color
    pop     edx
    pop     cx
    ret

display_register_name_op_size_override:
    cmp     CS:op_size_override,0
    jz      small_register
    call    display_register_name_32
    ret
  small_register:
    call    display_register_name_16
    ret


display_register_name_op_size_override_8_16:
    cmp     CS:op_size_override,0
    jz      small_register_2
    call    display_register_name_16
    ret
  small_register_2:
    call    display_register_name_8
    ret


display_register_name_indirect_op_size_override:
    cmp     CS:op_size_override,0
    jz      small_index
    call    display_register_name_indirect_32
    ret
  small_index:
    call    display_register_name_indirect_16
    ret


show_register_adr_size_override_no_color:
    cmp     CS:adr_size_override,0
    jz      small_number
    call    show_register_32_no_color
    add     di,8*2
    ret
  small_number:
    call    show_register_16_no_color
    add     di,4*2
    ret


;;;;; Load in the debug program
    mov     ax,0203h + 14                                           ; Read 3 DT, NP & RP sectors (+14 debug prog sectors)
    mov     bx,0800h                                                ; Store at 0800:0000h, or 8000h
    mov     es,bx
    xor     bx,bx
    mov     cx,2h                                                   ; track 0/sector 2
    xor     dx,dx                                                   ; head 0/drive 0
    int     13h                                                     ; Read the bad boy
    jnc     Read_Sectors2
    cmp     ah,6
    jz      Read_Sectors
    jmp     Reboot_With_Message_And_Key
  Read_Sectors2:
    mov     ax,0200h + 18                                           ; Read next 18 debug prog sectors
    mov     bx,512 * 17
    dec     cx                                                      ; track 0/sector 1
    inc     dh                                                      ; head 1/drive 0
    int     13h                                                     ; Read the bad boy
    jnc     Read_Sectors3
    cmp     ah,6
    jz      Read_Sectors2
    jmp     Reboot_With_Message_And_Key

  Read_Sectors3:
    mov     ax,0200h + 18                                           ; Read next 18 debug prog sectors
    mov     bx,512 * (18+17)
    mov     cx,4f01h                                                ; track 79/sector 1
    xor     dx,dx                                                   ; head 0/drive 0
    int     13h                                                     ; Read the bad boy
    jnc     setup_debugger
    cmp     ah,6
    jz      Read_Sectors3
    jmp     Reboot_With_Message_And_Key
;; Point INT1 and INT3 to the debug routine (loaded from the floppy disk from sectors 5 through 17)
  Setup_Debugger:
    xor     ax,ax
    mov     fs,ax
    mov     eax,08600000h                                           ; Segment (860h), Offset (0h), linear = 8600h
    mov     dword ptr FS:[0*4],eax                                  ; INT0, divide by zero or divide is too big for dest
    mov     dword ptr FS:[1*4],eax                                  ; INT1, single-step
    mov     dword ptr FS:[3*4],eax                                  ; INT3, software breakpoint
    mov     dword ptr FS:[4*4],eax                                  ; INT4, overflow
    mov     dword ptr FS:[6*4],eax                                  ; INT6, invalid opcode


; From BOOTUP.COM, initialize_kbd code
        mov     si,offset comma
        call    display_string_both
      ; Send the command to have the 8042 controller perform a self-diagnostic
        mov     al,0aah
        out     64h,al
      @@:
      ; Wait for bit 0 of the status port (64h) to become zero
        in      al,64h
        shr     al,1
        jnc     @F
        jmp     @B
      @@:
        in      al,60h
        .IF (al == 55h)
            mov     si,offset initialized_ok
        .ELSE
            mov     si,offset initialized_error
        .ENDIF

;    mov     edx,dword ptr [eax*4]
;    and     edx,0400h
;    .IF (!zero?)
;        mov     dword ptr [eax*4],0
;        in      al,060h
;    .ENDIF



_sHIGH_MEM      EQU 102 * 8     ; Pointer to HIGH memory structure (shows what HIGH MEMORY is available (memory between 640k and 1MB))

  ;; Slot 102, data (high memory mapping area)
    mov     eax,102                                                 ; GDT slot
    mov     ebx,082000h                                             ; base
    mov     edx,256                                                 ; limit
    call    create_data_descriptor

find_high_memory_blocks     PROC
;; This routine tries to find out how many regions there are above 640k that can be written in the 1st Megabyte
;; * Note:  These memory regions will be used by Exodus for buffers requiring < 20-bit addresses for I/O (DMA transfers, etc)
;; * Note:  We know there is memory at 0a0000h - 0bffffh for video memory, so we start searching at 0c0000h
    mov     si,offset finding_high_memory                           ; This makes the screen appear like:
    call    display_string_next_row_both                            ;   "þ Memory between 640k and 1MB:"

    push    ds
    push    es

    mov     ax,_sHIGH_MEM                                           ; We store our findings at es:[edi]
    mov     es,ax
    xor     edi,edi

    mov     ax,_sALL_MEM                                            ; We scan from ds:[0c0000h] through ds:[0fffffh]
    mov     ds,ax
    mov     esi,0c0000h

  find_high_memory_next_block:
    .IF (esi >= 0fffffh)
      ; We're to the end
        mov     bx,0
        jmp     find_high_memory_end_of_memory
    .ENDIF
    mov     al,byte ptr [esi]                                       ; Read the byte there
    not     al                                                      ; Reverse all bits
    mov     byte ptr [esi],al                                       ; Write it back
    .IF (byte ptr [esi] == al)                                      ; See if we can read what we just wrote
      ; We can write here, it's the start of a block
        not     al                                                  ; Put back whatever byte was there originally
        mov     byte ptr [esi],al
        mov     dword ptr es:[edi],esi                              ; Store the start of this block
        add     edi,4

        push    ds
        push    es
        push    esi

        mov     ax,_sDATA
        mov     ds,ax
        mov     es,ax
        mov     edx,esi
        mov     si,offset option_last                               ; Show the "À " text
        call    display_string_both
        call    display_hexidecimal_in_edx_both                     ; Start of block
        mov     si,offset hyphen
        call    display_string_both

        pop     esi
        pop     es
        pop     ds
      @@:
      ; Now, continue scanning until we can't write anymore (marking the end of a block)
        .IF (esi >= 0fffffh)
          ; We're to the end
            mov     bx,1
            jmp     find_high_memory_end_of_memory
        .ENDIF
        mov     al,byte ptr [esi]                                   ; Read the byte there
        not     al                                                  ; Reverse all bits
        mov     byte ptr [esi],al                                   ; Write it back
        .IF (byte ptr [esi] != al)                                  ; See if we can read what we just wrote
          ; We can't write here, it's the end of a block
            dec     esi                                             ; The previous byte was the last writeable byte
            mov     dword ptr es:[edi],esi                          ; Store it
            add     edi,4                                           ; Move to our next area in the structure
            mov     edx,esi
            inc     esi                                             ; Go back to the first byte that failed

          ;; Show the users the end of the block we found
            push    ds
            push    es
            push    esi

            mov     ax,_sDATA
            mov     ds,ax
            mov     es,ax
            call    display_hexidecimal_in_edx_next_row_both        ; End of block

            pop     esi
            pop     es
            pop     ds

            jmp     find_high_memory_next_block
        .ENDIF
        not     al                                                  ; Restore the byte that was there
        mov     byte ptr [esi],al
        inc     esi                                                 ; Move to the next byte to try
        jmp     @B
    .ENDIF
  ; We couldn't write it
    add     esi,1024                                                ; Move to the next byte to try
    jmp     find_high_memory_next_block

  find_high_memory_end_of_memory:
  ; We're at the end of memory
    mov     dword ptr es:[edi],0ffffffffh                           ; Terminate the listing
    mov     ax,_sDATA
    mov     ds,ax
    mov     es,ax
    .IF (bx == 0)
      ; We couldn't find any memory we could write to
        .IF (edi == 0)
            mov     si,offset option_last                           ;   "  À "
            call    display_string_both                             ; so we display the memory blocks found
            mov     si,offset not_available
            call    display_string_next_row_both
        .ENDIF
    .ELSE
      ; We reached the end of the 1MB in the last block
        mov     edx,esi
        call    display_hexidecimal_in_edx_next_row_both
    .ENDIF

  find_high_memory_finished:
    pop     es
    pop     ds
    ret
find_high_memory_blocks     ENDP
;; DEBUG DISPLAY, shows the value returned from the mouse
    push    ecx
    mov     si,offset open_parenthesis
    call    display_string_both
    mov     edx,ebx
    call    display_hexidecimal_in_edx_both
    mov     si,offset close_parenthesis
    call    display_string_both
    pop     ecx
_sFLOPPY0_DT                EQU 112 * 8
_sFLOPPY0_NP                EQU 113 * 8
_sFLOPPY0_RP                EQU 114 * 8
_sFLOPPY0_BUFFER_READ       EQU 115 * 8
_sFLOPPY0_BUFFER_WRITE      EQU 116 * 8
_sFLOPPY0_RESERVED          EQU 117 * 8; Floppy drive 1 (drive B:)
_sFLOPPY1_DT                EQU 118 * 8     ; Pointer to floppy disk 1 (drive B:) memory areas
_sFLOPPY1_NP                EQU 119 * 8
_sFLOPPY1_RP                EQU 120 * 8
_sFLOPPY1_BUFFER_READ       EQU 121 * 8
_sFLOPPY1_BUFFER_WRITE      EQU 122 * 8
_sFLOPPY1_RESERVED          EQU 123 * 8
      ; Try to determine what media is in the drive
        mov     al,"A"                                              ; Drive letter
        call    fword ptr cs:_iFDC_initialize_drive
        .IF (!carry?)
          ; There is media in the drive, so we know what capacity this diskette currently is
            mov     edx,eax
            mov     al,"A"
            call    fword ptr cs:_iDISK_update_media
        .ENDIF
      ; Try to determine what media is in the drive
        mov     al,"B"                                              ; Drive letter
        call    fword ptr cs:_iFDC_initialize_drive
        .IF (!carry?)
          ; There is media in the drive, so we know what capacity this diskette currently is
            mov     edx,eax
            mov     al,"B"
            call    fword ptr cs:_iDISK_update_media
        .ENDIF
    pushad                                                          ;;
    mov     edx,eax                                                 ;;
    mov     ax,0b800h                                               ;;
    mov     es,ax                                                   ;;
    mov     ecx,8                                                   ;;
    xor     di,di                                                   ;;
    .REPEAT                                                         ;;
        rol     edx,4                                               ;;
        mov     al,dl                                               ;;
        and     al,0fh                                              ;;
        .IF (al > 9)                                                ;;
            add     al,'A'-10                                       ;;
        .ELSE                                                       ;;
            add     al,'0'                                          ;;
        .ENDIF                                                      ;;
        stosb                                                       ;;
        mov     al,7                                                ;;
        stosb                                                       ;;
    .UNTILCXZ                                                       ;;
    popad                                                           ;;
    mov     ecx,21                                                  ;;
    mov     di,80*2                                                 ;;
    .REPEAT                                                         ;;
        lodsb                                                       ;;
        stosb                                                       ;;
        mov     al,7                                                ;;
        stosb                                                       ;;
    .UNTILCXZ                                                       ;;
    xor     ax,ax                                                   ;;
    int     16h                                                     ;;


; Initializes the ISR counts
    call    initialize_isr_counts                                   ; Set all ISR count arrays to zero

;; Gather required system information
    call    find_above_1MB_memory                                   ; Find memory above 1 MB
    call    initialize_pic                                          ; Setup PIC (Programmable interrupt controller)
    sti
    call    initialize_timer                                        ; Setup timer
    call    initialize_keyboard                                     ; Setup keyboard
    call    initialize_mouse_ps2                                    ; Setup PS/2 Mouse                     ; Can't get it to work!
    call    initialize_pci                                          ; Identify and flag any PCI devices
    call    initialize_serial                                       ; Setup serial ports
    call    initialize_parallel                                     ; Setup parallel ports
    call    initialize_disk_drives                                  ; Setup floppys and basic IDE/SCSI hard disks

;; Load the base exodus configuration

;;; Load user-defined drivers
;    call    load_drivers

    call    iVT_clear_screen_mono
    mov     ax,_sDATA
    mov     ds,ax
    mov     ax,_sSYSTEM_AREA
    mov     es,ax  ; Display the hours
    mov     ds:offset_mono,0
    xor     edx,edx
    mov     dl,byte ptr es:[_SYSTEM_HOURS]
    call    iVT_display_decimal_in_edx_nr_mono

  ; Display the minutes
    xor     edx,edx
    mov     dl,byte ptr es:[_SYSTEM_MINUTES]
    call    iVT_display_decimal_in_edx_nr_mono

  ; Display the seconds
    xor     edx,edx
    mov     dl,byte ptr es:[_SYSTEM_SECONDS]
    call    iVT_display_decimal_in_edx_nr_mono

  ; Display the 1/182 of a seconds
    xor     edx,edx
    mov     dl,byte ptr es:[_SYSTEM_182S_OF_A_SECOND]
    call    iVT_display_decimal_in_edx_nr_mono

  ; Display the month
    xor     edx,edx
    mov     dl,byte ptr es:[_SYSTEM_MONTH]
    call    iVT_display_decimal_in_edx_nr_mono

  ; Display the day
    xor     edx,edx
    mov     dl,byte ptr es:[_SYSTEM_DAY]
    call    iVT_display_decimal_in_edx_nr_mono

  ; Display the year
    xor     edx,edx
    mov     dx,word ptr es:[_SYSTEM_YEAR]
    call    iVT_display_decimal_in_edx_nr_mono

  ; Display the keyboard port data
    in      al,64h
    xor     edx,edx
    mov     dl,al
    call    iVT_display_hexidecimal_in_edx_nr_mono

  ; Display the MSR status bit from the floppy disk controller
    mov     edx,_FDC_PORT_MSR
    xor     eax,eax
    in      al,dx
    xchg    eax,edx
    call    iVT_display_hexidecimal_in_edx_nr_mono

  ; Display the ISR counts
    push    ds
    mov     ax,_sISR_COUNT
    mov     ds,ax

    xor     eax,eax
    .WHILE (eax < 256)
        mov     edx,dword ptr [eax*4]
        push    eax
        .IF (edx != 0)
            push    edx
            mov     edx,eax
            call    iVT_display_decimal_in_edx_mono

            pushad
            push    ds
            mov     ax,_sDATA
            mov     ds,ax
            mov     esi,offset hyphen
            call    iVT_display_string_mono
            pop     ds
            popad

            pop     edx
            call    iVT_display_hexidecimal_in_edx_nr_mono
        .ENDIF
        pop     eax
        inc     eax
    .ENDW
    pop     ds


debug_set_pause    PROC
    pushad
    push    ds

    mov     cx,_sDATA
    mov     ds,cx
    mov     ds:debug_pause_time,eax

    pop     ds
    popad
    ret
debug_set_pause    ENDP


debug_vga:
    pushad
    push    gs
    push    fs
    push    es
    push    ds
    mov     ax,_sDATA
    mov     ds,ax

    mov     esi,offset debug_text
    call    iVT_display_string_nr_vga
    jmp     debug_pause

debug_mono:
    pushad
    push    gs
    push    fs
    push    es
    push    ds
    mov     ax,_sDATA
    mov     ds,ax

    mov     esi,offset debug_text
    call    iVT_display_string_nr_mono
  debug_pause:
    .IF (ds:debug_pause_time != 0)
        mov     eax,ds:debug_pause_time
        push    eax
        call    fword ptr cs:_xTIMER_wait_x_ticks
    .ENDIF

    pop     ds
    pop     es
    pop     fs
    pop     gs
    popad
    ret

    INCLUDE pic.asp                                                 ; Programmable interrupt controller (APIC controller)
    INCLUDE dma.asp                                                 ; Direct memory access
    INCLUDE video.asp                                               ; Graphics and text

    INCLUDE debi.asp                                                ; Debugger! :)


;Û
;Û  ;; Slot 10, data (xDebug)
;Û    mov     eax,_sxDEBUG / 8                                        ; GDT slot
;Û    mov     ebx,070000h                                             ; base
;Û    mov     edx,0ffffh                                              ; limit
;Û    call    create_data_descriptor
;Û
;Û  ;; Slot 13, STACK0 ptr
;Û    mov     eax,_sSTACK0 / 8                                        ; GDT slot
;Û    mov     ebx,40000h                                              ; base
;Û    mov     edx,077ffh                                              ; limit
;Û    call    create_data_descriptor
;Û
;Û  ;; Slot 14, STACK1 ptr
;Û    mov     eax,_sSTACK1 / 8                                        ; GDT slot
;Û    mov     ebx,47fffh                                              ; base
;Û    mov     edx,077ffh                                              ; limit
;Û    call    create_data_descriptor
;Û
;Û  ;; Slot 15, STACK2 ptr
;Û    mov     eax,_sSTACK2 / 8                                        ; GDT slot
;Û    mov     ebx,50000h                                              ; base
;Û    mov     edx,077ffh                                              ; limit
;Û    call    create_data_descriptor
;Û
;Û  ;; Slot 98, bogus LDT ptr (used for tasks because they require one, whoopee!)
;Û    mov     eax,_sNULL_LDT / 8                                      ; GDT slot
;Û    mov     ebx,0                                                   ; base
;Û    mov     edx,0                                                   ; limit
;Û    call    create_ldt_descriptor
;Û
;Û  ;; Slot 99, data (internal memory sub-structure, 08d900-09ffff)
;Û    mov     eax,_sMEMORY / 8                                        ; GDT slot
;Û    mov     ebx,08d900h                                             ; base
;Û    mov     edx,75520                                               ; limit
;Û    call    create_data_descriptor
;Û
;Û  ;; Slot 100, data (keyboard input buffer)
;Û    mov     eax,_sKEYBOARD / 8                                      ; GDT slot
;Û    mov     ebx,080000h                                             ; base
;Û    mov     edx,4096                                                ; limit
;Û    call    create_data_descriptor
;Û
;Û  ;; Slot 101, data (mouse input buffer)
;Û    mov     eax,_sMOUSE / 8                                         ; GDT slot
;Û    mov     ebx,081000h                                             ; base
;Û    mov     edx,4096                                                ; limit
;Û    call    create_data_descriptor
;Û
;Û;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; FREE (128 bytes)
;Û;  ;; Slot 102, unused
;Û;    mov     eax,_sUNUSED_1 / 8                                      ; GDT slot
;Û;    mov     ebx,082080h                                             ; base
;Û;    mov     edx,128                                                 ; limit
;Û;    call    create_data_descriptor
;Û
;Û  ;; Slot 103, data (ISR count array)
;Û    mov     eax,_sISR_COUNT / 8                                     ; GDT slot
;Û    mov     ebx,082100h                                             ; base
;Û    mov     edx,1024                                                ; limit
;Û    call    create_data_descriptor
;Û
;Û  ;; Slot 104, data (task-timer structure array)
;Û    mov     eax,_sTIMER / 8                                         ; GDT slot
;Û    mov     ebx,082500h                                             ; base
;Û    mov     edx,37630                                               ; limit
;Û    call    create_data_descriptor
;Û
;Û  ;; Slot 105, data (task "scratch" space)
;Û    mov     eax,_sTIMER_TMP / 8                                     ; GDT slot
;Û    mov     ebx,08b800h                                             ; base
;Û    mov     edx,256                                                 ; limit
;Û    call    create_data_descriptor
;Û
;Û  ;; Slot 106, data (system memory area for DPL=00)
;Û    mov     eax,_sSYSTEM_AREA / 8                                   ; GDT slot
;Û    mov     ebx,08b900h                                             ; base
;Û    mov     edx,3072                                                ; limit
;Û    call    create_data_descriptor
;Û
;Û  ;; Slot 107, data (system memory area for DPL=01)
;Û    mov     eax,_sSYSTEM_AREA1 / 8                                  ; GDT slot
;Û    mov     ebx,08b900h                                             ; base
;Û    mov     edx,2048                                                ; limit
;Û    mov     cx,01b                                                  ; PL=01
;Û    call    create_data_descriptor_read_only_dpl
;Û
;Û  ;; Slot 108, data (system memory area for DPL=10)
;Û    mov     eax,_sSYSTEM_AREA2 / 8                                  ; GDT slot
;Û    mov     ebx,08b900h                                             ; base
;Û    mov     edx,2048                                                ; limit
;Û    mov     cx,10b                                                  ; PL=10
;Û    call    create_data_descriptor_read_only_dpl
;Û
;Û  ;; Slot 109, data (system memory area for DPL=11)
;Û    mov     eax,_sSYSTEM_AREA3 / 8                                  ; GDT slot
;Û    mov     ebx,08b900h                                             ; base
;Û    mov     edx,2048                                                ; limit
;Û    mov     cx,11b                                                  ; PL=11
;Û    call    create_data_descriptor_read_only_dpl
;Û
;Û  ;; Slot 110, data (disk drive structure)
;Û    mov     eax,_sDISK_DRIVES / 8                                   ; GDT slot
;Û    mov     ebx,08c500h                                             ; base
;Û    mov     edx,1024                                                ; limit
;Û    call    create_data_descriptor
;Û
;Û  ;; Slot 111, data (disk partition structure)
;Û    mov     eax,_sDISK_PARTITIONS / 8                               ; GDT slot
;Û    mov     ebx,08c900h                                             ; base
;Û    mov     edx,4096                                                ; limit
;Û    call    create_data_descriptor
;Û
;Û  ;; Exodus TSS for this environment
;Û    mov     eax,_sEXODUS_TSS / 8                                    ; GDT slot
;Û    mov     ebx,082000h                                             ; base
;Û    mov     ecx,offset first_pmode_instruction
;Û    mov     edx,7fh                                                 ; limit (128 bytes)
;Û    call    create_exodus_tss_descriptor
;Û
;Û  ;; Task gate to Exodus TSS
;Û    mov     eax,_sEXODUS_TASK_GATE / 8                              ; GDT slot
;Û    mov     ebx,_sEXODUS_TSS                                        ; GDT slot of TSS this task gate points to
;Û    call    create_task_gate_descriptor
;Û
;Û  ;; Task Mgr TSS for this environment
;Û  ;; * Note:  The Task Mgr TSS gets initialized later from the initialize_timer() in SOURCE\INIT32.ASP
;Û
;Û  ;; Slot 17, Task Manager stack
;Û    mov     eax,_sTASK_MGR_STACK / 8                                ; GDT slot
;Û    mov     ebx,58000h                                              ; base
;Û    mov     edx,2000h                                               ; limit (8k)
;Û    call    create_data_descriptor


create_ldt_descriptor   PROC
; Upon entry, ds:[esi] - far ptr to GDT
;                  eax - slot # to insert
;                  ebx - base
;                  edx - limit
;
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
    ret
    ret
create_ldt_descriptor   ENDP


create_data_descriptor_read_only_dpl    PROC    NEAR
; Upon entry, ds:[esi] - far ptr to GDT
;                  eax - slot # to insert
;                  ebx - base
;                  edx - limit
;                   cl - DPL
    mov     word ptr [esi+eax*8+0],dx                           ; limit 0:15
    mov     word ptr [esi+eax*8+2],bx                           ; base 0:15
    shr     ebx,16
    mov     byte ptr [esi+eax*8+4],bl                           ; base 16:23
    shr     ebx,8
    shl     cl,5                                                ; Move DPL over to bits 6,5
    or      cl,10010000b                                        ; Not accessed, read-only, expand=0, DPL=00
    mov     byte ptr [esi+eax*8+5],cl
    .IF (edx > 0fffffh)
      ; This is a BIG data descriptor (so, we have to change the granularity to 1)
        shr     edx,12                                          ; Divide by 4096
        mov     word ptr [esi+eax*8+0],dx                       ; Store the new limit 0:15
        shr     edx,16                                          ; Move over to store the next part of the limit
        and     dl,0fh                                          ; Mask off the top nibble (the limit is only 20 bits)
        or      dl,11000000b                                    ; make granularity=1, big=1 (high bits in dl)
    .ELSE
      ; It's a small data descriptor (leave the granularity at 0)
        shr     edx,16
        and     dl,0fh
    .ENDIF
    mov     byte ptr [esi+eax*8+6],dl                           ; limit 16:19, Granularity=0/1, big=0/1 (0/1 depends on size)
    mov     byte ptr [esi+eax*8+7],bl                           ; base 24:31
    ret
create_data_descriptor_read_only_dpl    ENDP


create_data_descriptor_expand_down      PROC    NEAR
; Upon entry, ds:[esi] - far ptr to GDT
;                  eax - slot # to insert
;                  ebx - base
;                  edx - limit
    neg     edx
    mov     word ptr [esi+eax*8+0],dx                           ; limit 0:15
    shr     edx,16
    mov     word ptr [esi+eax*8+2],bx                           ; base 0:15
    shr     ebx,16
    mov     byte ptr [esi+eax*8+4],bl                           ; base 16:23
    shr     ebx,8
    mov     byte ptr [esi+eax*8+5],10010110b                    ; Not accessed, writeable, expand=1, DPL=00
    and     dl,0fh
    mov     byte ptr [esi+eax*8+6],dl                           ; limit 16:19, Granularity=0, big=0
    mov     byte ptr [esi+eax*8+7],bl                           ; base 24:31
    ret
create_data_descriptor_expand_down      ENDP


create_interrupt_descriptor_16_bit      PROC    NEAR
; Upon entry, eax - interrupt # to update (0-based)
;        ds:[esi] - far pointer to start of IDT
;             edx - offset in bx to routine
;              bx - segment selector of routine
    push    ecx
    push    edx

    mov     ecx,edx                                             ; Copy 32-bit offset to ecx
    and     edx,00000ffffh                                      ; Keep lower 16-bits in edx
    and     ecx,0ffff0000h                                      ; Keep upper 16-bits in ecx
    mov     cx,1000011000000000b                                ; Add lower 16-bits in ecx, 16-bit, DPL=0, Present
    ror     edx,16                                              ; Move edx around so we can access the high word
    mov     dx,bx                                               ; Segment selector
    ror     edx,16                                              ; Ok, put it back the way it was

    mov     dword ptr [esi+eax*8+0],edx                         ; Store the IDT descriptor
    mov     dword ptr [esi+eax*8+4],ecx

    pop     edx
    pop     ecx
    ret
create_interrupt_descriptor_16_bit      ENDP


create_exodus_tss_descriptor    PROC
; Upon entry, ds:[esi] - far ptr to memory location for the TSS descriptor
;                  eax - slot # to insert
;                  ebx - base
;                  ecx - offset of first instruction
;                  edx - limit
    push    es
    push    edi
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
    mov     dword ptr es:[edi+76],eax                           ; cs
  ; Instruction Pointer
    mov     dword ptr es:[edi+32],ecx                           ; eip
  ; Data segment registers
    mov     eax,_sDATA
    mov     dword ptr es:[edi+84],eax                           ; ds
    mov     dword ptr es:[edi+72],eax                           ; es
  ; Extra segment registers
    mov     eax,_sVGA
    mov     dword ptr es:[edi+88],eax                           ; fs
    mov     eax,_sMONO
    mov     dword ptr es:[edi+92],eax                           ; gs
  ; Stack
    mov     eax,_sSTACK
    mov     dword ptr es:[edi+80],eax                           ; ss
    mov     dword ptr es:[edi+56],077fch                        ; esp
  ; Stack 2
    mov     eax,_sSTACK2
    mov     dword ptr es:[edi+24],eax                           ; ss2
    mov     dword ptr es:[edi+20],077fch                        ; esp2
  ; Stack 1
    mov     eax,_sSTACK1
    mov     dword ptr es:[edi+16],eax                           ; ss1
    mov     dword ptr es:[edi+12],077fch                        ; esp1
  ; Stack 0
    mov     eax,_sSTACK0
    mov     dword ptr es:[edi+8],eax                            ; ss0
    mov     dword ptr es:[edi+4],077fch                         ; esp0
  ; General purpose registers
    xor     eax,eax
    mov     dword ptr es:[edi+40],eax                           ; eax
    mov     dword ptr es:[edi+44],eax                           ; ecx
    mov     dword ptr es:[edi+48],eax                           ; edx
    mov     dword ptr es:[edi+52],eax                           ; ebx
    mov     dword ptr es:[edi+60],eax                           ; ebp
    mov     dword ptr es:[edi+64],eax                           ; esi
    mov     dword ptr es:[edi+68],eax                           ; edi
    mov     dword ptr es:[edi+28],eax                           ; CR3, paging (not used in Exodus)
    mov     dword ptr es:[edi+100],eax                          ; IO Map Base Address, Trap bit
    mov     dword ptr es:[edi+0],eax                            ; Previous task link
    mov     eax,_sNULL_LDT
    mov     dword ptr es:[edi+96],eax                           ; LDT segment selector
  ; EFLAGS
    pushfd
    pop     eax
    mov     dword ptr es:[edi+36],eax

  ; Finished
    pop     edi
    pop     es
    ret
create_exodus_tss_descriptor    ENDP


create_task_gate_descriptor     PROC
; Upon entry, ds:[esi] - far ptr to memory location for the TSS descriptor
;                  eax - slot # to insert
;                  bx - GDT slot for TSS
    shl     ebx,16                                              ; Move bx(TSS selector) to high-order word in ebx
    mov     dword ptr [esi+eax*8+0],ebx
    xor     ebx,ebx
    mov     bh,10000101b                                        ; present=1:dpl=00:00101
    mov     dword ptr [esi+eax*8+4],ebx
    ret
create_task_gate_descriptor     ENDP


_sEXODUS_TSS                EQU 11 * 8      ; Exodus kernel TSS
_sEXODUS_TASK_GATE          EQU 12 * 8      ; Exodus kernel task gate
_sSTACK0                    EQU 13 * 8      ; Stack segments for Exodus main task
_sSTACK1                    EQU 14 * 8      ;
_sSTACK2                    EQU 15 * 8      ;
_sTASK_MGR_TSS              EQU 16 * 8      ; Task manager TSS
_sTASK_MGR_STACK            EQU 17 * 8      ; Task manager stack
_sTASK_MGR_RLS_TIMESLICE_TSS EQU 18 * 8     ; Task manager Release_Timeslice TSS
_sTASK_MGR_RLS_STACK        EQU 19 * 8      ; Task manager Release_Timeslice stack
; Exodus internal memory regions
_sNULL_LDT                  EQU 98 * 8      ; LDT selector (NULL)
_sMEMORY                    EQU 99 * 8      ; Exodus internal memory sub-structure (defines all memory blocks)
; Input buffers
_sKEYBOARD                  EQU 100 * 8     ; Keyboard input buffer selector
_sMOUSE                     EQU 101 * 8     ; Mouse input buffer selector
_sUNUSED_1                  EQU 102 * 8     ; unused
; Indicates how many times an interrupt has been serviced by Exodus
_sISR_COUNT                 EQU 103 * 8     ; Pointer to a 256*4 byte array which indicates how many times each interrupt has been called
; Timer related functions (tasks)
_sTIMER                     EQU 104 * 8     ; Pointer to a 36.75k buffer for task timer processes
_sTIMER_TMP                 EQU 105 * 8     ; Pointer to a 256-byte temp area
; User memory area
_sSYSTEM_AREA               EQU 106 * 8     ; Pointer to system-memory area (read/write access to Exodus, DPL=00)
_sSYSTEM_AREA1              EQU 107 * 8     ; Pointer to system-memory area (read-only available to all applications at DPL=01)
_sSYSTEM_AREA2              EQU 108 * 8     ; Pointer to system-memory area (read-only available to all applications at DPL=10)
_sSYSTEM_AREA3              EQU 109 * 8     ; Pointer to system-memory area (read-only available to all applications at DPL=11)

; Disk information
_sDISK_DRIVES               EQU 110 * 8     ; Pointer to disk drive device structure table, refer to INF\DISKS.INF
_sDISK_PARTITIONS           EQU 111 * 8     ; Pointer to disk drive partition structure table, refer to INF\DISKS.INF

; Floppy drives
_sFLOPPY0_BASE_DESC         EQU 112 * 8     ; Pointer to floppy disk 0 (drive A:) memory areas
_sFLOPPY1_BASE_DESC         EQU 118 * 8     ; Pointer to floppy disk 1 (drive B:) memory areas

; Fixed data descriptors
_sTASK_POOL                 EQU 200 * 8     ; Pointer to the task pool structure
_sPCI_DEVICES               EQU 201 * 8     ; Pointer to all the system identified PCI devices

;; Exodus public function 32-bit call gates, task gates and code segment definitions
;; The "cg" indicates call gates, "tg" indicates task gates
_cgxTIMER_wait_full_tick            EQU 500 * 8         ; Constants used to access these call/task gates
_cgxTIMER_wait_next_tick            EQU 501 * 8
_cgxTIMER_wait_x_ticks              EQU 502 * 8
_cgxTIMER_evaluate_interval         EQU 503 * 8
_cgiTIMER_set_interrupt_interval    EQU 504 * 8
_cgiFDC_initialize_drive            EQU 505 * 8
_cgiFDC_determine_media             EQU 506 * 8
_cgiFDC_send_byte                   EQU 507 * 8
_cgiFDC_read_byte                   EQU 508 * 8
_cgiFDC_motor_on                    EQU 509 * 8
_cgiFDC_motor_off                   EQU 510 * 8
_cgiFDC_clear_fdc_output            EQU 511 * 8
_cgiFDC_clear_fdc_input             EQU 512 * 8
_cgiKBD_ll_wait_key                 EQU 513 * 8
_cgiFDC_read_sector                 EQU 514 * 8
_cgiFDC_read_track                  EQU 515 * 8
_cgiFDC_write_sector                EQU 516 * 8
_cgiFDC_write_track                 EQU 517 * 8
_cgiFDC_format_track                EQU 518 * 8
_cgiFDC_seek_track                  EQU 519 * 8
_cgiFDC_seek_relative               EQU 520 * 8
_cgiFDC_sense_interrupt             EQU 521 * 8
_cgiDISK_requestor                  EQU 522 * 8
_cgiDISK_update_media               EQU 523 * 8
_cgiDMA_setup                       EQU 524 * 8

_tgxTASK_release_timeslice          EQU 1000 * 8        ; Task gate
_cgiTASK_irq6_prep_wait             EQU 1001 * 8        ; Call gate
_cgiTASK_irq6_wait_for_signal       EQU 1002 * 8

; EFLAGS register constants to access individual flags
_EFLAGS_CF      EQU 0
_EFLAGS_PF      EQU 2
_EFLAGS_ACF     EQU 4
_EFLAGS_ZF      EQU 6
_EFLAGS_SF      EQU 7
_EFLAGS_TF      EQU 8
_EFLAGS_IF      EQU 9
_EFLAGS_DF      EQU 10
_EFLAGS_OF      EQU 11
_EFLAGS_IOPL    EQU 12
_EFLAGS_NT      EQU 14
_EFLAGS_RF      EQU 16
_EFLAGS_VM      EQU 17


; CR0 constants to access individual flags
_CR0_PE         EQU 0
_CR0_MP         EQU 1
_CR0_EM         EQU 2
_CR0_TS         EQU 3
_CR0_NE         EQU 4


; CR4 constants to access individual flags
_CR4_VME        EQU 0
_CR4_DE         EQU 3

;----------------------------------------------------------------------------------------------------------------------------------
; IRQ vectors for the exodus design (the MASTER controller is remapped 70h-77h, the SLAVE to 78h-7fh)
_IRQ0_VECTOR    EQU 70h         ; master
_IRQ1_VECTOR    EQU 71h
_IRQ2_VECTOR    EQU 72h
_IRQ3_VECTOR    EQU 73h
_IRQ4_VECTOR    EQU 74h
_IRQ5_VECTOR    EQU 75h
_IRQ6_VECTOR    EQU 76h
_IRQ7_VECTOR    EQU 77h

_IRQ8_VECTOR    EQU 78h         ; slave
_IRQ9_VECTOR    EQU 79h
_IRQ10_VECTOR   EQU 7ah
_IRQ11_VECTOR   EQU 7bh
_IRQ12_VECTOR   EQU 7ch
_IRQ13_VECTOR   EQU 7dh
_IRQ14_VECTOR   EQU 7eh
_IRQ15_VECTOR   EQU 7fh

; These constants are for the _sDISK_DRIVES area
; Types of controller
_DISK_CONTROLLER_NONE           EQU 0
_DISK_CONTROLLER_FLOPPY         EQU 1
_DISK_CONTROLLER_IDE            EQU 2
_DISK_CONTROLLER_SCSI           EQU 3
_DISK_CONTROLLER_PCMCIA         EQU 4
; Types of device
_DISK_DEVICE_RAM_DISK           EQU 0
_DISK_DEVICE_DISK_DRIVE         EQU 1
_DISK_DEVICE_CDROM_DRIVE        EQU 2
_DISK_DEVICE_DVD_DRIVE          EQU 3
_DISK_DEVICE_CDR_DRIVE          EQU 4
_DISK_DEVICE_CDRW_DRIVE         EQU 5
; Offsets to access data in this structure
_DISK_CONTROLLER_OFFSET         EQU 0
_DISK_DEVICE_OFFSET             EQU 1
_DISK_CAPACITY_OFFSET           EQU 2
_DISK_NUM_HEADS_OFFSET          EQU 10
_DISK_NUM_TRACKS_OFFSET         EQU 14
_DISK_NUM_SECTORS_OFFSET        EQU 18
_DISK_DEVICE_SPECS_OFFSET       EQU 22
_DISK_FLOPPY_DRIVE_TYPE_OFFSET  EQU 23
_DISK_BYTES_PER_SECTOR_OFFSET   EQU 24
_DISK_FLOPPY_GAP_LENGTH_OFFSET  EQU 28
_DISK_STRUCTURE_SIZE            EQU 32
; Device specs constants
_DISK_DEVICE_INTERNAL           EQU    1b
_DISK_DEVICE_MEDIA_REMOVABLE    EQU   10b
_DISK_DEVICE_HOT_SWAPPABLE      EQU  100b
_DISK_DEVICE_POWER_DOWN         EQU 1000b

; These constants are used for floppy disk references
_FLOPPY_360K                    EQU 0
_FLOPPY_1_2MB                   EQU 1
_FLOPPY_720K                    EQU 2
_FLOPPY_1_44MB                  EQU 3
_FLOPPY_2_88MB                  EQU 4

; These constants are for the iDISK_requestor() routines
_RQ_iDISK_FLOPPY_DRIVE_TYPE     EQU 1000


; These constants are for the _sDISK_PARTITIONS area
; File system types
_PARTITION_FILE_TYPE_NOT_ACCESSED   EQU 0
_PARTITION_FILE_TYPE_UNKNOWN        EQU 0ffh
_PARTITION_FILE_TYPE_DOS12          EQU 1
_PARTITION_FILE_TYPE_DOS16          EQU 2
_PARTITION_FILE_TYPE_DOS32          EQU 3
_PARTITION_FILE_TYPE_EXODUS         EQU 11
; Offsets to access data in this structure
_PARTITION_DISK_NUMBER_OFFSET       EQU 0
_PARTITION_FILE_SYSTEM_TYPE_OFFSET  EQU 1
_PARTITION_STARTING_HEAD_OFFSET     EQU 2
_PARTITION_STARTING_TRACK_OFFSET    EQU 6
_PARTITION_STARTING_SECTOR_OFFSET   EQU 10
_PARTITION_ENDING_HEAD_OFFSET       EQU 14
_PARTITION_ENDING_TRACK_OFFSET      EQU 18
_PARTITION_ENDING_SECTOR_OFFSET     EQU 22
_PARTITION_STARTING_GDT_OFFSET      EQU 26
_PARTITION_ACCESS_WORD_OFFSET       EQU 28
_PARTITION_DRIVE_LETTER_OFFSET      EQU 30
_PARTITION_PARTITION_CAPACITY       EQU 32
_PARTITION_STRUCTURE_SIZE           EQU 48

; TIMER memory accesses
_TIMER_STRUCT_LENGTH            EQU 32
_TIMER_GDT_LDT                  EQU 0
_TIMER_GDT                      EQU 0
_TIMER_LDT                      EQU 2
_TIMER_INC_VALUE                EQU 4
_TIMER_CURRENT_VALUE            EQU 12
_TIMER_ORIGINAL_FREQ            EQU 20
_TIMER_RESERVED                 EQU 24


; PIC register access (programmable interrupt controller)
_PIC_20h                        EQU 20h                             ; input  = 8259-1 read interrupt request/service registers
                                                                    ; output = 8259-1 interrupt command
_PIC_21h                        EQU 21h                             ; input  = 8259-1 interrupt mask register
                                                                    ; output = 8259-1 interrupt commands
_PIC_70h                        EQU 70h                             ; output = 8259-1 NMI enable (output only)
_PIC_A0h                        EQU 0a0h                            ; input  = 8259-2 read interrupt request / service registers
                                                                    ; output = 8259-2 interrupt command
                                                                    ; output = 8259-2 NMI control
_PIC_A1h                        EQU 0a1h                            ; input  = 8259-2 interrupt mask register
                                                                    ; output = 8259-2 interrupt commands


; PIT register access (8254 programmable interrupt timer)
_PIT_FREQUENCY                  EQU 1193181 ; Equivelent to 1.193181 Mhz
_PIT_0_BASE                     EQU 40h     ; Timer 0
_PIT_1_BASE                     EQU 41h     ; Timer 1
_PIT_2_BASE                     EQU 42h     ; Timer 2
_PIT_MODE                       EQU 43h     ; Mode control for timer's 0-2


; PCI device registers
_PCI_INDEX                      EQU 0CF8h                           ; Refer to inf\pci.inf for more info
_PCI_DATA                       EQU 0CFCh


; KEYBOARD memory access
_KBD_NEXT_ENTRY                 EQU 0
_KBD_BUFFER_START               EQU 4
_KBD_BUFFER_END                 EQU 8


; MOUSE memory access
_MOUSE_NEXT_ENTRY               EQU 0
_MOUSE_BUFFER_START             EQU 4
_MOUSE_BUFFER_END               EQU 8
; Mouse types
_MOUSE_NOT_INSTALLED            EQU 0
_MOUSE_PS_2                     EQU 1
_MOUSE_SERIAL                   EQU 2


; SERIAL memory accesses
_SERIAL_STRUCT_SIZE             EQU 16
_SERIAL_UNINITIALIZED           EQU 0
_SERIAL_NOT_IN_USE              EQU 1
_SERIAL_IN_USE                  EQU 2
; Communications ports to be added to the com port base to derive the correct port
_SERIAL_IER                     EQU 1                               ; Interrupt Enable
_SERIAL_IIR                     EQU 2                               ; Interrupt Identification
_SERIAL_FCR                     EQU 2                               ; FIFO Control
_SERIAL_LCR                     EQU 3                               ; Line Control
_SERIAL_MCR                     EQU 4                               ; Modem Control
_SERIAL_LSR                     EQU 5                               ; Line Status
_SERIAL_MSR                     EQU 6                               ; Modem Status
_SERIAL_DLL                     EQU 0                               ; Divisor Latch Least
_SERIAL_DLM                     EQU 1                               ; Divisor Latch Most
; Communcations values returned from the device
_SERIAL_RX_RDY                  EQU 1                               ; Ready to receive data
_SERIAL_INT_MASK                EQU 7                               ; Interrupt mask
_SERIAL_RX_ID                   EQU 4                               ; Receive ID (what changed on the serial status line)
_SERIAL_RTS                     EQU 2                               ; Ready to send
_SERIAL_DTR                     EQU 1                               ; Data terminal ready
_SERIAL_XON                     EQU 11h                             ; Xon
_SERIAL_XOFF                    EQU 13h                             ; Xoff


; PARALLEL memory accesses
_PARALLEL_STRUCT_SIZE           EQU 8
_PARALLEL_UNINITIALIZED         EQU 0
_PARALLEL_NOT_IN_USE            EQU 1
_PARALLEL_IN_USE                EQU 2


; FDC commands
_FDC_PORT_DOR                   EQU 03f2h                           ; DOR - Digital Output Register
_FDC_PORT_MSR                   EQU 03f4h                           ; MSR - Main Status Register
_FDC_PORT_DR                    EQU 03f5h                           ; DR - Data Register
_FDC_PORT_CCR                   EQU 03f7h                           ; CCR - Configuration Control Register
                                                                    ;       (aka DRSR - Data Rate Select Register)
_FDC_PORT_DIR                   EQU 03f7h                           ; DIR - Digital Input Register
_FDC_CMD_SEEK                   EQU 15
_FDC_CMD_SENSE_INTERRUPT        EQU 8
_FDC_CMD_READ_TRACK             EQU 6


; DMA constants
_DMA_mode_demand_transfer       EQU 00b
_DMA_mode_single_transfer       EQU 01b
_DMA_mode_block_transfer        EQU 10b

_DMA_operation_verify           EQU 0
_DMA_operation_write            EQU 1
_DMA_operation_read             EQU 2

_DMA_increment                  EQU 0                               ; Data is moved from low address to high
_DMA_decrement                  EQU 1                               ; Data is moved from high address to low

_DMA_channel_0                  EQU 0
_DMA_channel_1                  EQU 1
_DMA_channel_2                  EQU 2
_DMA_channel_fdc                EQU 2                               ; alias
_DMA_channel_3                  EQU 3
_DMA_channel_hdc                EQU 3                               ; alias
_DMA_channel_4                  EQU 4
_DMA_channel_5                  EQU 5
_DMA_channel_6                  EQU 6
_DMA_channel_7                  EQU 7

; DMA1 information
_DMA1_port_bca_channel_0        EQU 00h                             ; base and current address
_DMA1_port_bcc_channel_0        EQU 01h                             ; base and current count
_DMA1_port_pr_channel_0         EQU 87h                             ; page registers
_DMA1_port_bca_channel_1        EQU 02h
_DMA1_port_bcc_channel_1        EQU 03h
_DMA1_port_pr_channel_1         EQU 83h
_DMA1_port_bca_channel_2        EQU 04h
_DMA1_port_bcc_channel_2        EQU 05h
_DMA1_port_pr_channel_2         EQU 81h
_DMA1_port_bca_channel_3        EQU 06h
_DMA1_port_bcc_channel_3        EQU 07h
_DMA1_port_pr_channel_3         EQU 82h
;
_DMA1_port_status_register      EQU 08h
_DMA1_port_command_register     EQU 08h
_DMA1_port_request_register     EQU 09h
_DMA1_port_mask_register        EQU 0ah                             ; mask register bit
_DMA1_port_mode_register        EQU 0bh
_DMA1_port_clear_register       EQU 0ch                             ; clear byte, flip/flop
_DMA1_port_temporary_register   EQU 0dh
_DMA1_port_master_disable       EQU 0dh
_DMA1_port_clear_mask_register  EQU 0eh
_DMA1_port_write_all_register   EQU 0fh                             ; write all mask bits

; DMA2 information
_DMA2_port_bca_channel_4        EQU 0c0h                            ; base and current address
_DMA2_port_bcc_channel_4        EQU 0c2h                            ; base and current count
_DMA2_port_pr_channel_4         EQU 8fh                             ; page register
_DMA2_port_bca_channel_5        EQU 0c4h
_DMA2_port_bcc_channel_5        EQU 0c6h
_DMA2_port_pr_channel_5         EQU 8bh
_DMA2_port_bca_channel_6        EQU 0c8h
_DMA2_port_bcc_channel_6        EQU 0cah
_DMA2_port_pr_channel_6         EQU 89h
_DMA2_port_bca_channel_7        EQU 0cch
_DMA2_port_bcc_channel_7        EQU 0ceh
_DMA2_port_pr_channel_7         EQU 8ah
;
_DMA2_port_status_register      EQU 0d0h
_DMA2_port_command_register     EQU 0d0h
_DMA2_port_request_register     EQU 0d2h
_DMA2_port_mask_register        EQU 0d4h                            ; mask register bit
_DMA2_port_mode_register        EQU 0d6h
_DMA2_port_clear_register       EQU 0d8h                            ; clear byte, flip/flop
_DMA2_port_temporary_register   EQU 0dah
_DMA2_port_master_disable       EQU 0dah
_DMA2_port_clear_mask_register  EQU 0dch
_DMA2_port_write_all_register   EQU 0deh                            ; write all mask bits


; CMOS register access
_CMOS_70h                       EQU 70h
_CMOS_71h                       EQU 71h

; CMOS data registers, write the requested data value (from this list) to port 70h, then read one-byte data from port 71h
; * Note:  All values are returned in one-byte in BCD form
_NO_CONVERT                     EQU 0                               ; Does not convert CMOS value
_BCD_CONVERT                    EQU 1                               ; Converts CMOS BCD value to true value
_CMOS_SECONDS                   EQU 00h
_CMOS_SECONDS_ALARM             EQU 01h
_CMOS_MINUTES                   EQU 02h
_CMOS_MINUTES_ALARM             EQU 03h
_CMOS_HOURS                     EQU 04h
_CMOS_HOURS_ALARM               EQU 05h
_CMOS_DAY_OF_WEEK               EQU 06h
_CMOS_DAY                       EQU 07h
_CMOS_MONTH                     EQU 08h
_CMOS_YEAR                      EQU 09h     ; Stored as "00" through "99"
_CMOS_STATUS_REGISTER_A         EQU 0ah
_CMOS_STATUS_REGISTER_B         EQU 0bh
_CMOS_STATUS_REGISTER_C         EQU 0ch
_CMOS_STATUS_REGISTER_D         EQU 0dh
_CMOS_DIAGNOSTIC_STATUS_BYTE    EQU 0eh
_CMOS_SHUTDOWN_STATUS_BYTE      EQU 0fh
_CMOS_DISKETTE_TYPE             EQU 10h
_CMOS_HARD_DISK_TYPE            EQU 12h
_CMOS_EQUIPMENT_BYTE            EQU 14h
_CMOS_HARD_DISK0_EXTENDED_TYPE  EQU 19h
_CMOS_HARD_DISK1_EXTENDED_TYPE  EQU 1ah
OFF             EQU 0   ; These constants are used various places, makes it easier to understand
ON              EQU 1
NO              EQU 0
YES             EQU 1
TRUE            EQU 1
FALSE           EQU 0
_STOPPER        EQU 0ffh
_STOPPER_WORD   EQU 0ffffh
_STOPPER_DWORD  EQU 0ffffffffh


    finding_high_memory     db  "þ Memory blocks between 768k and 1MB",0
    total_memory            db  "þ Total memory: ",0
    initializing_pic        db  "þ PIC",0
    initializing_timer      db  "þ PIT",0
    initializing_pci        db  "þ PCI bus",0
    initializing_kbd        db  "þ Keyboard, ",0
    initializing_mouse      db  "þ Mouse, ",0
    initializing_serial     db  "þ Serial",0
    initializing_parallel   db  "þ Parallel",0
    initializing_floppy     db  "þ Floppy",0
    initializing_ide        db  "þ IDE",0
    initializing_scsi       db  "þ SCSI",0
    initializing_sound_card db  "þ Audio",0
    initializing_network    db  "þ Network",0


    kbd_101_key             db  "101/104-key",0
    mouse_serial            db  "Serial",0
    mouse_ps2               db  "PS/2",0
    drive_letter            db  "drive ?:, ",0                      ; Floppy drives A:, B:
    floppy_288              db  "3«",34,", 2.88m",0
    floppy_144              db  "3«",34,", 1.44m",0
    floppy_12               db  "5¬",34,", 1.2m",0
    floppy_720              db  "3«",34,", 720k",0
    floppy_360              db  "3«",34,", 360k",0
    disk_number             db  "disk ??, ",0                       ; Disk drives 00 through ??
    unknown                 db  "unknown",0
    memory_mb               db  " MB",0

    colon                   db  ":",0
    comma                   db  ",",0
    comma_space             db  ", ",0
    open_parenthesis        db  "(",0
    close_parenthesis       db  ")",0
    hyphen                  db  " - ",0
    option_blank            db  "  Ã ",0
    option_last             db  "  À ",0
    option_last_ok          db  "  À ok",0
    option_last_error       db  "  À error",0
    sub_option_last_ok      db  "    À ok"
    sub_option_last_error   db  "    À error"
    option_port_blank       db  "  Ã com1 - ",0
    option_port_last        db  "  À com1 - ",0
    initialized_ok          db  ", ok",0
    initialized_error       db  ", error",0
    not_available           db  ", not available",0




    divide_by_zero_text     db  "#0 - Divide by zero",0
    single_step_text        db  "#1 - Single Step",0
    breakpoint_text         db  "#3 - INT3 Breakpoint",0
    overflow_text           db  "#4 - Overflow",0
    bound_exception_text    db  "#5 - Bound",0
    invalid_opcode          db  "#6 - Invalid opcode",0
    device_na_text          db  "#7 - Device not available",0
    double_fault            db  "#8 - Double fault - Haulted",0
    coprocessor_text        db  "#9 - Coprocessor Segment Overrun",0
    invalid_tss             db  "#10 - Invalid TSS",0
    not_present_text        db  "#11 - Segment Not Present",0
    stack_fault_text        db  "#12 - Stack fault",0
    gp_fault_text           db  "#13 - GP fault",0
    page_fault_text         db  "#14 - Page fault",0
    floating_point_text     db  "#16 - Floating-Point",0
    alignment_check_text    db  "#17 - Alignment",0
    machine_check_text      db  "#18 - Machine-check - Haulted",0

    class_codes             db  00h, 28, "unavailable (PCI spec < 2.0)",0
                            db  01h, 12, "mass storage",0
                            db  02h,  7, "network",0
                            db  03h,  7, "display",0
                            db  04h, 10, "multimedia",0
                            db  05h,  6, "memory",0
                            db  06h,  6, "bridge",0
                            db  07h, 21, "simple communications",0
                            db  08h, 22, "base system peripheral",0
                            db  09h,  5, "input",0
                            db  0ah, 15, "docking station",0
                            db  0bh,  9, "processor",0
                            db  0ch, 10, "serial bus",0
                            db  0dh,  8, "wireless",0
                            db  0eh, 15, "intelligent i/o",0
                            db  0fh, 24, "satellite communications",0
                            db  10h, 21, "encryption/decryption",0
                            db  11h, 38, "data acquisition and signal processing",0
    class_stopper           db 0ffh, 12, "undetermined",0

    sub_class_codes         db  00h, 00h, 00h,  7, "Non-VGA",0
                            db  00h, 01h, 00h,  3, "VGA",0
                            db  01h, 00h, 00h,  4, "SCSI",0
                            db  01h, 01h, 00h,  3, "IDE",0
                            db  01h, 02h, 00h,  6, "floppy",0
                            db  01h, 03h, 00h,  3, "IPI",0
                            db  01h, 04h, 00h,  4, "RAID",0
                            db  02h, 00h, 00h,  8, "ethernet",0
                            db  02h, 01h, 00h, 10, "token ring",0
                            db  02h, 02h, 00h,  4, "FDDI",0
                            db  02h, 03h, 00h,  3, "ATM",0
                            db  02h, 04h, 00h,  4, "ISDN",0
                            db  03h, 00h, 00h,  3, "VGA",0
                            db  03h, 00h, 01h,  4, "8514",0
                            db  03h, 01h, 00h,  3, "XGA",0
                            db  03h, 02h, 00h,  2, "3D",0
                            db  04h, 00h, 00h,  5, "video",0
                            db  04h, 01h, 00h,  5, "audio",0
                            db  04h, 02h, 00h, 18, "computer telephony",0
                            db  05h, 00h, 00h,  3, "RAM",0
                            db  05h, 01h, 00h,  5, "flash",0
                            db  06h, 00h, 00h,  8, "host/PCI",0
                            db  06h, 01h, 00h,  7, "PIC/ISA",0
                            db  06h, 02h, 00h,  8, "PCI/EISA",0
                            db  06h, 03h, 00h,  7, "PCI/MCA",0
                            db  06h, 04h, 00h,  7, "PCI/PCI",0
                            db  06h, 04h, 01h, 10, "PCI/PCI SD",0
                            db  06h, 05h, 00h, 10, "PCI/PCMCIA",0
                            db  06h, 06h, 00h,  9, "PCI/NuBus",0
                            db  06h, 07h, 00h, 11, "PCI/CardBus",0
                            db  06h, 08h, 00h,  7, "RACEway",0
                            db  07h, 00h, 00h, 13, "XT-compatible",0
                            db  07h, 00h, 01h,  5, "16450",0
                            db  07h, 00h, 02h,  5, "16550",0
                            db  07h, 00h, 03h,  5, "16650",0
                            db  07h, 00h, 04h,  5, "16750",0
                            db  07h, 00h, 05h,  5, "16850",0
                            db  07h, 00h, 06h,  5, "16950",0
                            db  07h, 01h, 00h,  3, "std",0
                            db  07h, 01h, 01h,  2, "bi",0
                            db  07h, 01h, 02h,  7, "ECP 1.x",0
                            db  07h, 01h, 03h, 20, "IEEE 1284 controller",0
                            db  07h, 01h,0feh, 16, "IEEE 1284 device",0
                            db  07h, 02h, 00h,  9, "multiport",0
                            db  07h, 03h, 00h,  5, "modem",0
                            db  07h, 03h, 01h, 11, "16450 modem",0
                            db  07h, 03h, 02h, 11, "16550 modem",0
                            db  07h, 03h, 03h, 11, "16650 modem",0
                            db  07h, 03h, 04h, 11, "16750 modem",0
                            db  08h, 00h, 00h,  8, "8259 PIC",0
                            db  08h, 00h, 01h,  7, "ISA PIC",0
                            db  08h, 00h, 02h,  8, "EISA PIC",0
                            db  08h, 00h, 10h,  7, "IO APIC",0
                            db  08h, 00h, 20h, 10, "IO(x) APIC",0
                            db  08h, 01h, 00h,  8, "8237 DMA",0
                            db  08h, 01h, 01h,  7, "ISA DMA",0
                            db  08h, 01h, 02h,  8, "EISA DMA",0
                            db  08h, 02h, 00h,  8, "8254 PIT",0
                            db  08h, 02h, 01h,  9, "ISA timer",0
                            db  08h, 02h, 02h, 10, "EISA timer",0
                            db  08h, 03h, 00h, 15, "real-time clock",0
                            db  08h, 03h, 01h, 19, "ISA real-time clock",0
                            db  08h, 04h, 00h, 23, "PCI hot-plug controller",0
                            db  09h, 00h, 00h,  8, "keyboard",0
                            db  09h, 01h, 00h, 15, "digitizer (pen)",0
                            db  09h, 02h, 00h,  5, "mouse",0
                            db  09h, 03h, 00h,  7, "scanner",0
                            db  09h, 04h, 00h,  8, "gameport",0
                            db  0ah, 00h, 00h,  7, "generic",0
                            db  0bh, 00h, 00h,  3, "386",0
                            db  0bh, 01h, 00h,  3, "486",0
                            db  0bh, 02h, 00h,  7, "pentium",0
                            db  0bh, 03h, 00h,  5, "alpha",0
                            db  0bh, 04h, 00h,  7, "powerpc",0
                            db  0bh, 05h, 00h,  4, "mips",0
                            db  0bh, 06h, 00h, 12, "co-processor",0
                            db  0ch, 00h, 00h,  9, "IEEE 1394",0
                            db  0ch, 00h, 01h, 17, "IEEE 1394 OpenHCI",0
                            db  0ch, 01h, 00h, 10, "ACCESS.bus",0
                            db  0ch, 02h, 00h,  3, "SSA",0
                            db  0ch, 03h, 01h,  3, "USB",0
                            db  0ch, 03h, 10h, 12, "USB OpenHost",0
                            db  0ch, 03h, 80h, 28, "USB no programming interface",0
                            db  0ch, 03h,0feh, 10, "USB device",0
                            db  0ch, 04h, 00h,  5, "fibre",0
                            db  0ch, 05h, 00h, 21, "system management bus",0
                            db  0dh, 00h, 00h, 15, "iRDA controller",0
                            db  0dh, 01h, 00h, 11, "consumer IR",0
                            db  0dh, 10h, 00h, 13, "RF controller",0
                            db  0eh, 00h, 00h,  4, "FIFO",0
                            db  0eh,0ffh, 00h,  3, "I2O",0
                            db  0fh, 01h, 00h,  2, "TV",0
                            db  0fh, 02h, 00h,  5, "audio",0
                            db  0fh, 03h, 00h,  5, "voice",0
                            db  0fh, 04h, 00h,  4, "data",0
                            db  10h, 00h, 00h, 17, "network/computing",0
                            db  10h, 10h, 00h, 13, "entertainment",0
                            db  11h, 00h, 00h,  4, "DPIO",0
    sub_class_other         db 0ffh, 00h, 00h,  5, "other",0

;; DEBUG codes
    debug1_text             db  " DEBUG1 ",0
    debug2_text             db  " DEBUG2 ",0
    debug3_text             db  " DEBUG3 ",0
    debug4_text             db  " DEBUG4 ",0
    clear_debug_text        db  "ÛÛÛÛÛÛÛÛ",0

    debug_text              db  "þ Debug trap",0
    debug_pause_time        dd  182 * 10        ; Default to 10 seconds between items

    cmos_conversion_table   db  _CMOS_SECONDS, _BCD_CONVERT, _SYSTEM_SECONDS      ; This table is used to take data from CMOS and store it in
                            db  _CMOS_MINUTES, _BCD_CONVERT, _SYSTEM_MINUTES      ; our SYSTEM memory area.  This is done during the
                            db  _CMOS_HOURS, _BCD_CONVERT, _SYSTEM_HOURS          ; initialize_timer() routine because the timer is responsible
                            db  _CMOS_DAY, _BCD_CONVERT, _SYSTEM_DAY              ; for updating these values.  Refer to SOURCE\INIT.ASP
                            db  _CMOS_MONTH, _BCD_CONVERT, _SYSTEM_MONTH
                            db  _CMOS_YEAR, _BCD_CONVERT, _SYSTEM_YEAR
                            db  _CMOS_DISKETTE_TYPE, _NO_CONVERT, _SYSTEM_FLOPPY_DRIVE_TYPE
                            db  _CMOS_HARD_DISK_TYPE, _NO_CONVERT, _SYSTEM_HARD_DRIVE_TYPE
                            db  _CMOS_HARD_DISK0_EXTENDED_TYPE, _NO_CONVERT, _SYSTEM_HARD_DRIVE0_EXTENDED
                            db  _CMOS_HARD_DISK1_EXTENDED_TYPE, _NO_CONVERT, _SYSTEM_HARD_DRIVE1_EXTENDED
                            db  0ffh

    timer_max_hz            dd  0
    timer_max_value         dq  0

    installed_memory        dd  0           ; Number of bytes found



;; Exodus public functions that are called by Exodus BOOTUP.COM
;; * Note:  The CALL GATE reference requires a value for the EIP, but it doesn't matter what it is.  For that reason all of
;;          the memory variables below are shifted down 4 bytes, this allows the bogus EIP to be there before the valid CALL GATE
    _xTIMER_wait_full_tick              dw  0                       ; Bogus EIP DWORD
    _xTIMER_wait_next_tick              dw  0
    _xTIMER_wait_x_ticks                dw  _cgxTIMER_wait_full_tick
    _xTIMER_evaluate_interval           dw  _cgxTIMER_wait_next_tick
    _iTIMER_set_interrupt_interval      dw  _cgxTIMER_wait_x_ticks
    _iFDC_initialize_drive              dw  _cgxTIMER_evaluate_interval
    _iFDC_determine_media               dw  _cgiTIMER_set_interrupt_interval
    _iFDC_send_byte                     dw  _cgiFDC_initialize_drive
    _iFDC_read_byte                     dw  _cgiFDC_determine_media
    _iFDC_motor_on                      dw  _cgiFDC_send_byte
    _iFDC_motor_off                     dw  _cgiFDC_read_byte
    _iFDC_clear_fdc_output              dw  _cgiFDC_motor_on
    _xTASK_release_timeslice            dw  _cgiFDC_motor_off
    _iKBD_ll_wait_key                   dw  _cgiFDC_clear_fdc_output
    _iFDC_clear_fdc_input               dw  _tgxTASK_release_timeslice
    _iTASK_irq6_prep_wait               dw  _cgiKBD_ll_wait_key
    _iTASK_irq6_wait_for_signal         dw  _cgiFDC_clear_fdc_input
    _iFDC_read_sector                   dw  _cgiTASK_irq6_prep_wait
    _iFDC_read_track                    dw  _cgiTASK_irq6_wait_for_signal
    _iFDC_write_sector                  dw  _cgiFDC_read_sector
    _iFDC_write_track                   dw  _cgiFDC_read_track
    _iFDC_format_track                  dw  _cgiFDC_write_sector
    _iFDC_seek_track                    dw  _cgiFDC_write_track
    _iFDC_seek_relative                 dw  _cgiFDC_format_track
    _iFDC_sense_interrupt               dw  _cgiFDC_seek_track
    _iDISK_requestor                    dw  _cgiFDC_seek_relative
    _iDISK_update_media                 dw  _cgiFDC_sense_interrupt
    _iDMA_setup                         dw  _cgiDISK_requestor
                                        dw  _cgiDISK_update_media
                                        dw  _cgiDMA_setup


    reg1                    dw  03d4h
    reg2                    dw  03d5h
    offset_vga              dw  0
    offset_mono             dw  0
    attribute_vga           db  7
    attribute_mono          db  7
    freeze_vga              db  0
    freeze_mono             db  0
    storage_ptr             dd  offset offset_vga                         ; pointer to either offset_vga or offset_mono


interrupt_1_handler:
    push    eax
    mov     eax,1
    call    debug_exception_handler
    pop     eax
    iretd
interrupt_2_handler:
    push    eax
    mov     eax,2
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_3_handler:
    push    eax
    mov     eax,3
    call    breakpoint_exception_handler
    pop     eax
    iretd
interrupt_4_handler:
    push    eax
    mov     eax,4
    call    overflow_exception_handler
    pop     eax
    iretd
interrupt_5_handler:
    push    eax
    mov     eax,5
    call    bound_range_exceeded_handler
    pop     eax
    iretd
interrupt_6_handler:
    push    eax
    mov     eax,6
    call    invalid_opcode_handler
    pop     eax
    iretd
interrupt_7_handler:
    push    eax
    mov     eax,7
    call    device_not_available_handler
    pop     eax
    iretd
interrupt_8_handler:
    push    eax
    mov     eax,8
    call    double_fault_handler
    pop     eax
    iretd
interrupt_9_handler:
    push    eax
    mov     eax,9
    call    coprocessor_segment_overrun_handler
    pop     eax
    iretd
interrupt_10_handler:
    push    eax
    mov     eax,10
    call    invalid_tss_handler
    pop     eax
    iretd
interrupt_11_handler:
    push    eax
    mov     eax,11
    call    segment_not_present_handler
    pop     eax
    iretd
interrupt_12_handler:
    push    eax
    mov     eax,12
    call    stack_fault_handler
    pop     eax
    iretd
interrupt_13_handler:
    push    eax
    mov     eax,13
    call    gp_fault_handler
    pop     eax
    iretd
interrupt_14_handler:
    push    eax
    mov     eax,14
    call    page_fault_handler
    pop     eax
    iretd
interrupt_15_handler:
    push    eax
    mov     eax,15
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_16_handler:
    push    eax
    mov     eax,16
    call    floating_point_error_handler
    pop     eax
    iretd
interrupt_17_handler:
    push    eax
    mov     eax,17
    call    alignment_check_handler
    pop     eax
    iretd
interrupt_18_handler:
    push    eax
    mov     eax,18
    call    machine_check_handler
    pop     eax
    iretd
interrupt_19_handler:
    push    eax
    mov     eax,19
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_20_handler:
    push    eax
    mov     eax,20
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_21_handler:
    push    eax
    mov     eax,21
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_22_handler:
    push    eax
    mov     eax,22
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_23_handler:
    push    eax
    mov     eax,23
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_24_handler:
    push    eax
    mov     eax,24
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_25_handler:
    push    eax
    mov     eax,25
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_26_handler:
    push    eax
    mov     eax,26
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_27_handler:
    push    eax
    mov     eax,27
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_28_handler:
    push    eax
    mov     eax,28
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_29_handler:
    push    eax
    mov     eax,29
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_30_handler:
    push    eax
    mov     eax,30
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_31_handler:
    push    eax
    mov     eax,31
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_32_handler:
    push    eax
    mov     eax,32
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_33_handler:
    push    eax
    mov     eax,33
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_34_handler:
    push    eax
    mov     eax,34
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_35_handler:
    push    eax
    mov     eax,35
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_36_handler:
    push    eax
    mov     eax,36
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_37_handler:
    push    eax
    mov     eax,37
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_38_handler:
    push    eax
    mov     eax,38
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_39_handler:
    push    eax
    mov     eax,39
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_40_handler:
    push    eax
    mov     eax,40
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_41_handler:
    push    eax
    mov     eax,41
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_42_handler:
    push    eax
    mov     eax,42
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_43_handler:
    push    eax
    mov     eax,43
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_44_handler:
    push    eax
    mov     eax,44
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_45_handler:
    push    eax
    mov     eax,45
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_46_handler:
    push    eax
    mov     eax,46
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_47_handler:
    push    eax
    mov     eax,47
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_48_handler:
    push    eax
    mov     eax,48
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_49_handler:
    push    eax
    mov     eax,49
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_50_handler:
    push    eax
    mov     eax,50
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_51_handler:
    push    eax
    mov     eax,51
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_52_handler:
    push    eax
    mov     eax,52
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_53_handler:
    push    eax
    mov     eax,53
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_54_handler:
    push    eax
    mov     eax,54
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_55_handler:
    push    eax
    mov     eax,55
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_56_handler:
    push    eax
    mov     eax,56
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_57_handler:
    push    eax
    mov     eax,57
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_58_handler:
    push    eax
    mov     eax,58
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_59_handler:
    push    eax
    mov     eax,59
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_60_handler:
    push    eax
    mov     eax,60
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_61_handler:
    push    eax
    mov     eax,61
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_62_handler:
    push    eax
    mov     eax,62
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_63_handler:
    push    eax
    mov     eax,63
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_64_handler:
    push    eax
    mov     eax,64
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_65_handler:
    push    eax
    mov     eax,65
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_66_handler:
    push    eax
    mov     eax,66
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_67_handler:
    push    eax
    mov     eax,67
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_68_handler:
    push    eax
    mov     eax,68
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_69_handler:
    push    eax
    mov     eax,69
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_70_handler:
    push    eax
    mov     eax,70
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_71_handler:
    push    eax
    mov     eax,71
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_72_handler:
    push    eax
    mov     eax,72
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_73_handler:
    push    eax
    mov     eax,73
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_74_handler:
    push    eax
    mov     eax,74
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_75_handler:
    push    eax
    mov     eax,75
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_76_handler:
    push    eax
    mov     eax,76
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_77_handler:
    push    eax
    mov     eax,77
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_78_handler:
    push    eax
    mov     eax,78
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_79_handler:
    push    eax
    mov     eax,79
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_80_handler:
    push    eax
    mov     eax,80
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_81_handler:
    push    eax
    mov     eax,81
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_82_handler:
    push    eax
    mov     eax,82
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_83_handler:
    push    eax
    mov     eax,83
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_84_handler:
    push    eax
    mov     eax,84
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_85_handler:
    push    eax
    mov     eax,85
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_86_handler:
    push    eax
    mov     eax,86
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_87_handler:
    push    eax
    mov     eax,87
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_88_handler:
    push    eax
    mov     eax,88
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_89_handler:
    push    eax
    mov     eax,89
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_90_handler:
    push    eax
    mov     eax,90
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_91_handler:
    push    eax
    mov     eax,91
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_92_handler:
    push    eax
    mov     eax,92
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_93_handler:
    push    eax
    mov     eax,93
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_94_handler:
    push    eax
    mov     eax,94
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_95_handler:
    push    eax
    mov     eax,95
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_96_handler:
    push    eax
    mov     eax,96
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_97_handler:
    push    eax
    mov     eax,97
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_98_handler:
    push    eax
    mov     eax,98
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_99_handler:
    push    eax
    mov     eax,99
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_100_handler:
    push    eax
    mov     eax,100
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_101_handler:
    push    eax
    mov     eax,101
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_102_handler:
    push    eax
    mov     eax,102
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_103_handler:
    push    eax
    mov     eax,103
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_104_handler:
    push    eax
    mov     eax,104
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_105_handler:
    push    eax
    mov     eax,105
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_106_handler:
    push    eax
    mov     eax,106
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_107_handler:
    push    eax
    mov     eax,107
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_108_handler:
    push    eax
    mov     eax,108
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_109_handler:
    push    eax
    mov     eax,109
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_110_handler:
    push    eax
    mov     eax,110
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_111_handler:
    push    eax
    mov     eax,111
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_112_handler:                                              ; IRQ 0
    push    eax
    mov     eax,112
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_113_handler:                                              ; IRQ 1
    push    eax
    mov     eax,113
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_114_handler:                                              ; IRQ 2
    push    eax
    mov     eax,114
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_115_handler:                                              ; IRQ 3
    push    eax
    mov     eax,115
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_116_handler:                                              ; IRQ 4
    push    eax
    mov     eax,116
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_117_handler:                                              ; IRQ 5
    push    eax
    mov     eax,117
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_118_handler:                                              ; IRQ 6
    push    eax
    mov     eax,118
;    call    IRQ6_handler
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_119_handler:                                              ; IRQ 7
    push    eax
    mov     eax,119
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_120_handler:                                              ; IRQ 8
    push    eax
    mov     eax,120
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_121_handler:                                              ; IRQ 9
    push    eax
    mov     eax,121
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_122_handler:                                              ; IRQ 10
    push    eax
    mov     eax,122
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_123_handler:                                              ; IRQ 11
    push    eax
    mov     eax,123
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_124_handler:                                              ; IRQ 12
    push    eax
    mov     eax,124
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_125_handler:                                              ; IRQ 13
    push    eax
    mov     eax,125
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_126_handler:                                              ; IRQ 14
    push    eax
    mov     eax,126
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_127_handler:                                              ; IRQ 15
    push    eax
    mov     eax,127
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_128_handler:
    push    eax
    mov     eax,128
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_129_handler:
    push    eax
    mov     eax,129
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_130_handler:
    push    eax
    mov     eax,130
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_131_handler:
    push    eax
    mov     eax,131
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_132_handler:
    push    eax
    mov     eax,132
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_133_handler:
    push    eax
    mov     eax,133
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_134_handler:
    push    eax
    mov     eax,134
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_135_handler:
    push    eax
    mov     eax,135
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_136_handler:
    push    eax
    mov     eax,136
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_137_handler:
    push    eax
    mov     eax,137
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_138_handler:
    push    eax
    mov     eax,138
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_139_handler:
    push    eax
    mov     eax,139
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_140_handler:
    push    eax
    mov     eax,140
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_141_handler:
    push    eax
    mov     eax,141
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_142_handler:
    push    eax
    mov     eax,142
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_143_handler:
    push    eax
    mov     eax,143
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_144_handler:
    push    eax
    mov     eax,144
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_145_handler:
    push    eax
    mov     eax,145
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_146_handler:
    push    eax
    mov     eax,146
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_147_handler:
    push    eax
    mov     eax,147
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_148_handler:
    push    eax
    mov     eax,148
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_149_handler:
    push    eax
    mov     eax,149
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_150_handler:
    push    eax
    mov     eax,150
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_151_handler:
    push    eax
    mov     eax,151
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_152_handler:
    push    eax
    mov     eax,152
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_153_handler:
    push    eax
    mov     eax,153
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_154_handler:
    push    eax
    mov     eax,154
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_155_handler:
    push    eax
    mov     eax,155
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_156_handler:
    push    eax
    mov     eax,156
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_157_handler:
    push    eax
    mov     eax,157
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_158_handler:
    push    eax
    mov     eax,158
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_159_handler:
    push    eax
    mov     eax,159
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_160_handler:
    push    eax
    mov     eax,160
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_161_handler:
    push    eax
    mov     eax,161
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_162_handler:
    push    eax
    mov     eax,162
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_163_handler:
    push    eax
    mov     eax,163
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_164_handler:
    push    eax
    mov     eax,164
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_165_handler:
    push    eax
    mov     eax,165
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_166_handler:
    push    eax
    mov     eax,166
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_167_handler:
    push    eax
    mov     eax,167
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_168_handler:
    push    eax
    mov     eax,168
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_169_handler:
    push    eax
    mov     eax,169
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_170_handler:
    push    eax
    mov     eax,170
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_171_handler:
    push    eax
    mov     eax,171
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_172_handler:
    push    eax
    mov     eax,172
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_173_handler:
    push    eax
    mov     eax,173
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_174_handler:
    push    eax
    mov     eax,174
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_175_handler:
    push    eax
    mov     eax,175
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_176_handler:
    push    eax
    mov     eax,176
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_177_handler:
    push    eax
    mov     eax,177
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_178_handler:
    push    eax
    mov     eax,178
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_179_handler:
    push    eax
    mov     eax,179
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_180_handler:
    push    eax
    mov     eax,180
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_181_handler:
    push    eax
    mov     eax,181
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_182_handler:
    push    eax
    mov     eax,182
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_183_handler:
    push    eax
    mov     eax,183
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_184_handler:
    push    eax
    mov     eax,184
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_185_handler:
    push    eax
    mov     eax,185
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_186_handler:
    push    eax
    mov     eax,186
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_187_handler:
    push    eax
    mov     eax,187
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_188_handler:
    push    eax
    mov     eax,188
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_189_handler:
    push    eax
    mov     eax,189
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_190_handler:
    push    eax
    mov     eax,190
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_191_handler:
    push    eax
    mov     eax,191
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_192_handler:
    push    eax
    mov     eax,192
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_193_handler:
    push    eax
    mov     eax,193
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_194_handler:
    push    eax
    mov     eax,194
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_195_handler:
    push    eax
    mov     eax,195
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_196_handler:
    push    eax
    mov     eax,196
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_197_handler:
    push    eax
    mov     eax,197
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_198_handler:
    push    eax
    mov     eax,198
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_199_handler:
    push    eax
    mov     eax,199
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_200_handler:
    push    eax
    mov     eax,200
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_201_handler:
    push    eax
    mov     eax,201
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_202_handler:
    push    eax
    mov     eax,202
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_203_handler:
    push    eax
    mov     eax,203
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_204_handler:
    push    eax
    mov     eax,204
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_205_handler:
    push    eax
    mov     eax,205
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_206_handler:
    push    eax
    mov     eax,206
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_207_handler:
    push    eax
    mov     eax,207
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_208_handler:
    push    eax
    mov     eax,208
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_209_handler:
    push    eax
    mov     eax,209
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_210_handler:
    push    eax
    mov     eax,210
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_211_handler:
    push    eax
    mov     eax,211
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_212_handler:
    push    eax
    mov     eax,212
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_213_handler:
    push    eax
    mov     eax,213
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_214_handler:
    push    eax
    mov     eax,214
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_215_handler:
    push    eax
    mov     eax,215
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_216_handler:
    push    eax
    mov     eax,216
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_217_handler:
    push    eax
    mov     eax,217
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_218_handler:
    push    eax
    mov     eax,218
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_219_handler:
    push    eax
    mov     eax,219
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_220_handler:
    push    eax
    mov     eax,220
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_221_handler:
    push    eax
    mov     eax,221
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_222_handler:
    push    eax
    mov     eax,222
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_223_handler:
    push    eax
    mov     eax,223
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_224_handler:
    push    eax
    mov     eax,224
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_225_handler:
    push    eax
    mov     eax,225
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_226_handler:
    push    eax
    mov     eax,226
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_227_handler:
    push    eax
    mov     eax,227
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_228_handler:
    push    eax
    mov     eax,228
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_229_handler:
    push    eax
    mov     eax,229
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_230_handler:
    push    eax
    mov     eax,230
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_231_handler:
    push    eax
    mov     eax,231
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_232_handler:
    push    eax
    mov     eax,232
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_233_handler:
    push    eax
    mov     eax,233
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_234_handler:
    push    eax
    mov     eax,234
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_235_handler:
    push    eax
    mov     eax,235
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_236_handler:
    push    eax
    mov     eax,236
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_237_handler:
    push    eax
    mov     eax,237
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_238_handler:
    push    eax
    mov     eax,238
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_239_handler:
    push    eax
    mov     eax,239
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_240_handler:
    push    eax
    mov     eax,240
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_241_handler:
    push    eax
    mov     eax,241
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_242_handler:
    push    eax
    mov     eax,242
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_243_handler:
    push    eax
    mov     eax,243
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_244_handler:
    push    eax
    mov     eax,244
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_245_handler:
    push    eax
    mov     eax,245
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_246_handler:
    push    eax
    mov     eax,246
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_247_handler:
    push    eax
    mov     eax,247
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_248_handler:
    push    eax
    mov     eax,248
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_249_handler:
    push    eax
    mov     eax,249
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_250_handler:
    push    eax
    mov     eax,250
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_251_handler:
    push    eax
    mov     eax,251
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_252_handler:
    push    eax
    mov     eax,252
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_253_handler:
    push    eax
    mov     eax,253
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_254_handler:
    push    eax
    mov     eax,254
    call    count_interrupt_handler_eoi
    pop     eax
    iretd
interrupt_255_handler:
    push    eax
    mov     eax,255
    call    count_interrupt_handler_eoi
    pop     eax
    iretd

irq6_handler    PROC
; IRQ6 (76h) ISR
    call    count_interrupt_handler_eoi                             ; Update count and signal end of interrupt
    push    esi
    push    ds

    mov     si,_sSYSTEM
    mov     ds,si
    inc     byte ptr ds:[_SYSTEM_i_IRQ6_INDICATOR]                  ; Raise the flag indicating this one is completed

    pop     ds
    pop     esi
    ret
irq6_handler    ENDP


divide_by_zero_handler PROC
;; INT 0, Divide by 0
    call    count_interrupt_handler_eoi                             ; Update count and signal end of interrupt
    call    exception_handler_fake_error_code
    push    esi
    mov     esi,offset divide_by_zero_text
    call    debi_debug
    pop     esi
;    call    debi_exception
    call    exception_handler_remove_error_code
    ret
divide_by_zero_handler ENDP

debug_exception_handler PROC
;; INT 1, Single-step exception
    call    count_interrupt_handler_eoi                             ; Update count and signal end of interrupt
    call    exception_handler_fake_error_code
    push    esi
    mov     esi,offset single_step_text
    call    debi_debug
;    call    debi_exception
    pop     esi
    call    exception_handler_remove_error_code
    ret
debug_exception_handler ENDP

breakpoint_exception_handler PROC
;; INT 3, Breakpoint exception
    call    count_interrupt_handler_eoi                             ; Update count and signal end of interrupt
    call    exception_handler_fake_error_code
    push    esi
    mov     esi,offset breakpoint_text
    call    debi_debug
;    call    debi_exception
    pop     esi
    call    exception_handler_remove_error_code
    ret
breakpoint_exception_handler ENDP

overflow_exception_handler PROC
;; INT 4, Overflow exception
    call    count_interrupt_handler_eoi                             ; Update count and signal end of interrupt
    call    exception_handler_fake_error_code
    push    esi
    mov     esi,offset overflow_text
    call    debi_debug
;    call    debi_exception
    pop     esi
    call    exception_handler_remove_error_code
    ret
overflow_exception_handler ENDP

bound_range_exceeded_handler PROC
;; INT 5, BOUND range exceeded exception
    call    count_interrupt_handler_eoi                             ; Update count and signal end of interrupt
    call    exception_handler_fake_error_code
    push    esi
    mov     esi,offset bound_exception_text
    call    debi_debug
;    call    debi_exception
    pop     esi
    call    exception_handler_remove_error_code
    ret
bound_range_exceeded_handler ENDP

invalid_opcode_handler PROC
;; INT 6, Invalid opcode
    call    count_interrupt_handler_eoi                             ; Update count and signal end of interrupt
    call    exception_handler_fake_error_code
    push    esi
    mov     esi,offset invalid_opcode
    call    debi_debug
;    call    debi_exception
    pop     esi
    call    exception_handler_remove_error_code
    ret
invalid_opcode_handler ENDP

device_not_available_handler PROC
;; INT 7, device not available exception
    call    count_interrupt_handler_eoi                             ; Update count and signal end of interrupt
; REMEMBER
    clts
;    push    esi
;    mov     esi,offset device_na_text
;    call    debi_debug
;    call    debi_exception
    ret
device_not_available_handler ENDP

double_fault_handler PROC
;; INT 8, Double-fault
    call    count_interrupt_handler_eoi                             ; Update count and signal end of interrupt
    push    esi
    mov     esi,offset double_fault
    call    debi_debug
;    call    debi_exception
    pop     esi
    call    exception_handler_remove_error_code
    ret
double_fault_handler ENDP

coprocessor_segment_overrun_handler PROC
;; INT 9, coprocessor segment overrun exception
    call    count_interrupt_handler_eoi                             ; Update count and signal end of interrupt
    call    exception_handler_fake_error_code
    push    esi
    mov     esi,offset coprocessor_text
    call    debi_debug
;    call    debi_exception
    pop     esi
    call    exception_handler_remove_error_code
    ret
coprocessor_segment_overrun_handler ENDP

invalid_tss_handler PROC
;; INT 10, Invalid TSS
    call    count_interrupt_handler_eoi                             ; Update count and signal end of interrupt
    push    esi
    mov     esi,offset invalid_tss
    call    debi_debug
;    call    debi_exception
    pop     esi
    call    exception_handler_remove_error_code
    ret
invalid_tss_handler ENDP

segment_not_present_handler PROC
;; INT 11, segment not present exception
    call    count_interrupt_handler_eoi                             ; Update count and signal end of interrupt
    push    esi
    mov     esi,offset not_present_text
    call    debi_debug
;    call    debi_exception
    pop     esi
    call    exception_handler_remove_error_code
    ret
segment_not_present_handler ENDP

stack_fault_handler PROC
;; INT 12, Stack fault
    call    count_interrupt_handler_eoi                             ; Update count and signal end of interrupt
    push    esi
    mov     esi,offset stack_fault_text
    call    debi_debug
;    call    debi_exception
    pop     esi
    call    exception_handler_remove_error_code
    ret
stack_fault_handler ENDP

gp_fault_handler PROC
;; INT 13, GP fault
    call    count_interrupt_handler_eoi                             ; Update count and signal end of interrupt
    push    esi
    mov     esi,offset gp_fault_text
    call    debi_debug
;    call    debi_exception
    pop     esi
    call    exception_handler_remove_error_code
    ret
gp_fault_handler ENDP

page_fault_handler PROC
;; INT 14, page fault exception
    call    count_interrupt_handler_eoi                             ; Update count and signal end of interrupt
    push    esi
    mov     esi,offset page_fault_text
    call    debi_debug
;    call    debi_exception
    pop     esi
    call    exception_handler_remove_error_code
    ret
page_fault_handler ENDP

floating_point_error_handler PROC
;; INT 16, floating point exception
    call    count_interrupt_handler_eoi                             ; Update count and signal end of interrupt
    call    exception_handler_fake_error_code
    push    esi
    mov     esi,offset floating_point_text
    call    debi_debug
;    call    debi_exception
    pop     esi
    call    exception_handler_remove_error_code
    ret
floating_point_error_handler ENDP

alignment_check_handler PROC
;; INT 17, alignment check exception
    call    count_interrupt_handler_eoi                             ; Update count and signal end of interrupt
    push    esi
    mov     esi,offset alignment_check_text
    call    debi_debug
;    call    debi_exception
    pop     esi
    call    exception_handler_remove_error_code
    ret
alignment_check_handler ENDP

machine_check_handler PROC
;; INT 18, machine check exception
    call    count_interrupt_handler_eoi                             ; Update count and signal end of interrupt
    call    exception_handler_fake_error_code
    push    esi
    mov     esi,offset machine_check_text
    call    debi_debug
;    call    debi_exception
    pop     esi
    call    exception_handler_remove_error_code
    ret
machine_check_handler ENDP




exception_handler_fake_error_code   PROC
; This routine compensates for the fact that many faults do not push error codes on the stack.
; In doing so it makes everything nice, neat and tidy
;
    sub     esp,4
    push    eax
;
; Right now:  [esp+28] - eflags - code that caused the fault
;             [esp+24] -  cs - code that cause the fault
;             [esp+20] - eip - code that caused the fault
;             [esp+16] - original eax value from code that originally caused the fault/trap/interrupt handler
;             [esp+12] - return address to original fault/trap/interrupt handler
;             [esp+8] - return address to calling procedure
;             [esp+4] - space reserved for the insertion of the fake error code
;             [esp+0] - eax value saved here

;; Move the return address to calling procedure down the stack
    mov     eax,dword ptr ss:[esp+8]
    mov     dword ptr ss:[esp+4],eax

;; Move the return address to the original fault/trap/interrupt handler routine
    mov     eax,dword ptr ss:[esp+12]
    mov     dword ptr ss:[esp+8],eax

;; Move the original eax value
    mov     eax,dword ptr ss:[esp+16]
    mov     dword ptr ss:[esp+12],eax

;; Stick a value of 0 in where the error # would normally go
    mov     dword ptr ss:[esp+16],0
;
; And now:  [esp+28] - eflags - code that caused the fault
;           [esp+24] -  cs - code that cause the fault
;           [esp+20] - eip - code that caused the fault
;           [esp+16] - fake error code
;           [esp+12] - original eax value from code that originally caused the fault/trap/interrupt handler
;           [esp+8]  - return address to original fault/trap/interrupt handler
;           [esp+4]  - return address to calling procedure
;           [esp+0]  - eax value saved here

    pop     eax
    ret
exception_handler_fake_error_code   ENDP




exception_handler_remove_error_code     PROC
; This routine removes the error code from the stack before returning to the interrupted procedure
; In doing so it makes everything nice, neat and tidy
;
    push    eax
;
; Right now:  [esp+28] - eflags - code that caused the fault
;             [esp+24] - cs - code that cause the fault
;             [esp+20] - eip - code that caused the fault
;             [esp+16] - error code
;             [esp+12] - original eax value from code that originally caused the fault/trap/interrupt handler
;             [esp+8]  - return address to original fault/trap/interrupt handler
;             [esp+4]  - return address to calling procedure
;             [esp+0]  - eax value saved here

;; Move the original eax value up one notch on the stack ladder of success
    mov     eax,dword ptr ss:[esp+12]
    mov     dword ptr ss:[esp+16],eax

;; Move the return address to original f/t/i handler up one
    mov     eax,dword ptr ss:[esp+8]
    mov     dword ptr ss:[esp+12],eax

;; Move the return address to calling procedure up one
    mov     eax,dword ptr ss:[esp+4]
    mov     dword ptr ss:[esp+8],eax

;; Move the saved eax value here
    mov     eax,dword ptr ss:[esp+0]
    mov     dword ptr ss:[esp+4],eax
    add     esp,4
;
; And now:  [esp+24] - eflags - code that caused the fault
;           [esp+20] - cs - code that cause the fault
;           [esp+16] - eip - code that caused the fault
;           [esp+12] - original eax value from code that originally caused the fault/trap/interrupt handler
;           [esp+8]  - return address to original fault/trap/interrupt handler
;           [esp+4]  - return address to calling procedure
;           [esp+0]  - eax value saved here
;
    pop     eax
    ret
exception_handler_remove_error_code     ENDP




count_interrupt_handler_eoi     PROC
; This routine signals end-of-interrupt and increments a count for the interrupt handlers
    push    eax
    .IF (eax >= 78h && eax <= 7fh)
      ; It's from the SLAVE PIC, send both commands
        mov     al,20h
        out     0a0h,al
    .ELSE
        mov     al,20h
    .ENDIF
    out     20h,al
    pop     eax
  ; Note, execution continues here in count_interrupt_handler().  This routine was just added as a common entry point to
  ;       send out the end-of-interrupt signal for interrupts that do not have a service
count_interrupt_handler_eoi     ENDP
count_interrupt_handler     PROC
  ; Now, display a count on the screen which indicates how many keys have been pressed
    push    ds
    push    edx
    push    eax

    mov     dx,_sISR_COUNT
    mov     ds,dx
    and     eax,0ffh
    inc     dword ptr [eax*4]                                       ; We're updating the dword, so multiply by 4

    pop     eax
    pop     edx
    pop     ds
    ret
count_interrupt_handler     ENDP




IFNDEF _DEBI
    debi_debug      PROC    NEAR
        ret
    debi_debug      ENDP
ENDIF



initialize_isr_counts   PROC
; This routine initializes all of the ISR counts to zero
    push    ds
    push    ecx

    mov     ax,_sISR_COUNT
    mov     ds,ax
    mov     ecx,256                                                 ; Do it for all 256 interrupt vectors
  @@:
    mov     dword ptr ds:[ecx*4-4],0                                ; ecx*4 = 256*4 = 1024, but we're writing 4 bytes there, so -4
    loope   @B

    pop     ecx
    pop     ds
    ret
initialize_isr_counts   ENDP



tss32_offset0           db  "L16 ³ +000 ³  link:",0
tss32_offset4           db  " 32 ³ +004 ³  esp0:",0
tss32_offset8           db  "L16 ³ +008 ³   ss0:",0
tss32_offset12          db  " 32 ³ +012 ³  esp1:",0
tss32_offset16          db  "L16 ³ +016 ³   ss1:",0
tss32_offset20          db  " 32 ³ +020 ³  esp2:",0
tss32_offset24          db  "L16 ³ +024 ³   ss2:",0
tss32_offset28          db  " 32 ³ +028 ³   cr3:",0
tss32_offset32          db  " 32 ³ +032 ³   eip:",0
tss32_offset36          db  " 32 ³ +036 ³eflags:",0
tss32_offset40          db  " 32 ³ +040 ³   eax:",0
tss32_offset44          db  " 32 ³ +044 ³   ecx:",0
tss32_offset48          db  " 32 ³ +048 ³   edx:",0
tss32_offset52          db  " 32 ³ +052 ³   ebx:",0
tss32_offset56          db  " 32 ³ +056 ³   esp:",0
tss32_offset60          db  " 32 ³ +060 ³   ebp:",0
tss32_offset64          db  " 32 ³ +064 ³   esi:",0
tss32_offset68          db  " 32 ³ +068 ³   edi:",0
tss32_offset72          db  "L16 ³ +072 ³    es:",0
tss32_offset76          db  "L16 ³ +076 ³    cs:",0
tss32_offset80          db  "L16 ³ +080 ³    ss:",0
tss32_offset84          db  "L16 ³ +084 ³    ds:",0
tss32_offset88          db  "L16 ³ +088 ³    fs:",0
tss32_offset92          db  "L16 ³ +092 ³    gs:",0
tss32_offset96          db  "L16 ³ +096 ³   ldt:",0
tss32_offset100         db  "H16 ³ +100 ³   i/o:",0

iVT_display_tss32_mono  PROC
; This procedure is used to display TSS data on the monochrome screen
; Upon entry:   ds:[esi] - far ptr to TSS in memory
    pushad
    push    ds
    push    esi

    mov     ax,_sDATA
    mov     ds,ax

;; Clear the screen
    call    iVT_clear_screen_mono                                       ; Clear mono screen (the TSS display takes up most of screen)

;; Display all identifiers
    mov     esi,offset tss32_offset0                                ; Display each header so the user knows what the data means
    call    iVT_display_string_nr_mono
    mov     esi,offset tss32_offset4
    call    iVT_display_string_nr_mono
    mov     esi,offset tss32_offset8
    call    iVT_display_string_nr_mono
    mov     esi,offset tss32_offset12
    call    iVT_display_string_nr_mono
    mov     esi,offset tss32_offset16
    call    iVT_display_string_nr_mono
    mov     esi,offset tss32_offset20
    call    iVT_display_string_nr_mono
    mov     esi,offset tss32_offset24
    call    iVT_display_string_nr_mono
    mov     esi,offset tss32_offset28
    call    iVT_display_string_nr_mono
    mov     esi,offset tss32_offset32
    call    iVT_display_string_nr_mono
    mov     esi,offset tss32_offset36
    call    iVT_display_string_nr_mono
    mov     esi,offset tss32_offset40
    call    iVT_display_string_nr_mono
    mov     esi,offset tss32_offset44
    call    iVT_display_string_nr_mono
    mov     esi,offset tss32_offset48
    call    iVT_display_string_nr_mono
    mov     esi,offset tss32_offset52
    call    iVT_display_string_nr_mono
    mov     esi,offset tss32_offset56
    call    iVT_display_string_nr_mono
    mov     esi,offset tss32_offset60
    call    iVT_display_string_nr_mono
    mov     esi,offset tss32_offset64
    call    iVT_display_string_nr_mono
    mov     esi,offset tss32_offset68
    call    iVT_display_string_nr_mono
    mov     esi,offset tss32_offset72
    call    iVT_display_string_nr_mono
    mov     esi,offset tss32_offset76
    call    iVT_display_string_nr_mono
    mov     esi,offset tss32_offset80
    call    iVT_display_string_nr_mono
    mov     esi,offset tss32_offset84
    call    iVT_display_string_nr_mono
    mov     esi,offset tss32_offset88
    call    iVT_display_string_nr_mono
    mov     esi,offset tss32_offset92
    call    iVT_display_string_nr_mono

  ; These get displayed in their own column
    mov     dh,00
    mov     dl,40
    call    iVT_position_cursor_mono
    mov     esi,offset tss32_offset96
    call    iVT_display_string_nr_mono
    mov     dh,1
    mov     dl,40
    call    iVT_position_cursor_mono
    mov     esi,offset tss32_offset100
    call    iVT_display_string_nr_mono

;; Now, display TSS data
    pop     esi
    pop     ds

  ; Save current color
    mov     al,cs:attribute_mono
    push    eax
  ; Set new color
    mov     al,112
    call    iVT_set_attribute_mono

  ; Begin displaying the raw data
    mov     ecx,24                                                  ; We repeat for the 24 items in the left-most column
    mov     dh,00                                                   ; Start at Y=0, X=21
    mov     dl,21
  @@:
    push    ecx
    push    edx
    call    iVT_position_cursor_mono                                ; Move cursor there
    mov     ecx,4                                                   ; Display 4 bytes
    call    iVT_display_hex_string_ecx_ro_mono                      ;  in hexidecimal format
    pop     edx
    pop     ecx
    inc     dh                                                      ; Move down one line
    add     esi,4                                                   ; Move to next item in TSS
    loop    @B

;; Now, display the remaining two items in the other column
    mov     dh,00
    mov     dl,61
    push    edx
    call    iVT_position_cursor_mono
    mov     ecx,4
    call    iVT_display_hex_string_ecx_ro_mono
    pop     edx
    add     esi,4

    inc     dh
    call    iVT_position_cursor_mono
    mov     ecx,4
    call    iVT_display_hex_string_ecx_ro_mono

    pop     eax                                                     ; Returns saved attribute in al
    call    iVT_set_attribute_mono

    popad
    ret
iVT_display_tss32_mono  ENDP

    xor     esi,esi
    mov     dword ptr fs:[esi],'OY'
    mov     dword ptr gs:[esi],'OY'
@@:
jmp     @B
;pushad
;mov edx,ebx
;mov ebx,16
;mov edi,10*80*2
;call VID_display_radix_in_edx_mono
;popad
;@@:
;jmp @B

  ;; Now, get ready to update the program structure
    mov     ax,_sPRIMATIVE_LOAD_INFO
    mov     fs,ax
    xor     ebp,ebp
  ; Right now, fs:[ebp] - far ptr to the pimative load info memory region

;;;pushad
;;;push ds
;;;mov edx,ebx
;;;mov ebx,16
;;;xor edi,edi
;;;call VID_display_radix_in_edx_mono
;;;pop ds
;;;popad
;;;
;;;mov edx,dword ptr ds:[esi+_BOOT_PB_size]
;;;mov ebx,16
;;;mov edi,80*2
;;;call VID_display_radix_in_edx_mono
;;;@@:
;;;hlt
;;;jmp @B


pushad
pushfd
.IF (edx != 0c8h)
    mov ebx,16
    xor edi,edi
    call VID_display_radix_in_edx_mono
.ENDIF
popfd
popad



pushad
mov ax,_sGDT
mov ds,ax
mov esi,830h
mov ecx,8
xor edi,edi
call VID_display_hex_string_ecx_mono
popad
@@:
hlt
jmp @B


;@@:
;hlt
;jmp @B



    read_8042_64h       PROC
    ; This routine reads one byte from port 60h into al
        in      al,064h
        call    fword ptr cs:_xTIMER_wait_full_tick
        ret
    read_8042_64h       ENDP




    read_8042_60h       PROC
    ; This routine reads the byte in from port 60h to al
        push    ecx
        xor     ecx,ecx
      @@:
        call    read_8042_64h                                       ; Wait for bit 0 of port (64h) to become zero before reading
        shr     al,1
        jc      @F
        loope   @B
      @@:
        call    fword ptr cs:_xTIMER_wait_full_tick
        in      al,060h
        pop     ecx
        ret
    read_8042_60h       ENDP




    write_8042_64h      PROC
    ; This routine writes a byte to port 64h
        call    fword ptr cs:_xTIMER_wait_full_tick
        mov     al,ah
        out     064h,al
        ret
    write_8042_64h      ENDP




    write_8042_60h      PROC
    ; This routine writes the byte in ah to port 60h
        push    ecx
        xor     ecx,ecx
      @@:
        call    read_8042_64h                                       ; Wait for bit 1 of port (64h) to become zero before writing
        shr     al,2
        jnc     @F
        loope   @B
      @@:
        call    fword ptr cs:_xTIMER_wait_full_tick
        mov     al,ah                                               ; Write it
        out     060h,al
        call    fword ptr cs:_xTIMER_wait_full_tick
        pop     ecx
        ret
    write_8042_60h      ENDP




    read_8042_64h_fast       PROC
    ; This routine reads one byte from port 60h into al
        in      al,064h
        jmp     $+2
        ret
    read_8042_64h_fast       ENDP




    read_8042_60h_fast       PROC
    ; This routine reads the byte in from port 60h to al
        push    ecx
        xor     ecx,ecx
      @@:
        call    read_8042_64h_fast                                  ; Wait for bit 0 of port (64h) to become zero before reading
        shr     al,1
        jc      @F
        loope   @B
      @@:
        in      al,060h
        jmp     $+2
        pop     ecx
        ret
    read_8042_60h_fast       ENDP




    write_8042_64h_fast      PROC
    ; This routine writes a byte to port 64h
      @@:
        mov     al,ah
        out     064h,al
        jmp     $+2
        ret
    write_8042_64h_fast      ENDP




    write_8042_60h_fast      PROC
    ; This routine writes the byte in ah to port 60h
        push    ecx
        xor     ecx,ecx
      @@:
        call    read_8042_64h                                       ; Wait for bit 1 of port (64h) to become zero before writing
        shr     al,2
        jnc     @F
        loope   @B
      @@:
        mov     al,ah                                               ; Write it
        out     060h,al
        jmp     $+2
        pop     ecx
        ret
    write_8042_60h_fast      ENDP




    disable_keyboard    PROC
    ; Sends the disable keyboard command to port 64h
        push    eax
        mov     ah,0adh                                             ; Disable keyboard command
        call    write_8042_64h
        call    fword ptr cs:_xTIMER_wait_full_tick
        pop     eax
        ret
    disable_keyboard    ENDP




    enable_keyboard     PROC
    ; Sends the enable keyboard command to port 64h
        push    eax
        mov     ah,0aeh                                             ; Enable keyboard command
        call    write_8042_64h
        call    fword ptr cs:_xTIMER_wait_full_tick
        pop     eax
        ret
    enable_keyboard     ENDP


;pushad
;mov edx,ebp
;mov ebx,16
;add dword ptr gs:[_SYSTEM_i_SCRATCH_DWORD1],80
;mov edi,dword ptr gs:[_SYSTEM_i_SCRATCH_DWORD1]
;call VID_display_radix_in_edx_mono
;popad



;pushad
;mov ax,_sPRIMATIVE_LOAD_INFO
;mov ds,ax
;mov esi,4
;mov ecx,2
;mov edi,80*2*0
;call VID_display_hex_string_ecx_mono
;
;add esi,2
;mov ecx,2
;mov edi,80*2*1
;call VID_display_hex_string_ecx_mono
;add esi,2
;
;mov ecx,1
;mov edi,80*2*2
;call VID_display_hex_string_ecx_mono
;mov cl,byte ptr [esi]
;inc esi
;call VID_display_hex_string_ecx_mono
;add esi,ecx
;
;mov ecx,1
;mov edi,80*2*3
;call VID_display_hex_string_ecx_mono
;mov cl,byte ptr [esi]
;inc esi
;call VID_display_hex_string_ecx_mono
;add esi,ecx
;
;mov ecx,1
;mov edi,80*2*4
;call VID_display_hex_string_ecx_mono
;mov cl,byte ptr [esi]
;inc esi
;call VID_display_hex_string_ecx_mono
;add esi,ecx
;
;mov ecx,1
;mov edi,80*2*5
;call VID_display_hex_string_ecx_mono
;mov cl,byte ptr [esi]
;inc esi
;call VID_display_hex_string_ecx_mono
;add esi,ecx
;
;mov ecx,4
;mov edi,80*2*6
;call VID_display_hex_string_ecx_mono
;add esi,4
;
;mov ecx,4
;mov edi,80*2*7
;call VID_display_hex_string_ecx_mono
;add esi,4
;
;mov ecx,4
;mov edi,80*2*8
;call VID_display_hex_string_ecx_mono
;add esi,4
;
;mov ecx,4
;mov edi,80*2*9
;call VID_display_hex_string_ecx_mono
;popad
;@@:
;hlt
;jmp @B


;pushad
;mov esi,edi
;mov ecx,16
;mov edi,80*2*14
;call VID_display_hex_string_ecx_mono
;popad
;@@:
;hlt
;jmp @B
;@@:
;hlt
;jmp @B
      ; Now, display the palette on the mono monitor so we can determine what the fuck is wrong!!!!
;        xor     eax,eax
;        .WHILE (eax < 14h)
;            push    eax
            mov     edx,RAMDAC_INDEX_READ
            mov     al,6
            out     dx,al
            jmp     $+2
            mov     edx,RAMDAC_DATA
            in      al,dx                                           ; Red
            call    display_al
            in      al,dx                                           ; Green
            call    display_al
            in      al,dx                                           ; Blue
            call    display_al
            callf   VID_move_to_next_line_mono
;            pop     eax
;            inc     eax
;        .ENDW
      ; Now, display the palette on the mono monitor so we can determine what the fuck is wrong!!!!
        xor     eax,eax
        .WHILE (eax <= 14h)
            mov     ebx,eax
            call    display_al

            mov     edx,STATUS_REG1
            in      al,dx
            jmp     $+2
            mov     edx,ATTRIB_INDEX
            mov     al,bl
            or      al,20h
            out     dx,al
            jmp     $+2
            jmp     $+2
            jmp     $+2
            jmp     $+2
            jmp     $+2
            mov     edx,ATTRIB_DATA_READ
            jmp     $+2
            jmp     $+2
            jmp     $+2
            jmp     $+2
            jmp     $+2
            in      al,dx                                           ; Red
            call    display_al
            callf   VID_move_to_next_line_mono

            mov     eax,ebx
            inc     eax
        .ENDW


;      ; Now, display the palette on the mono monitor so we can determine what the fuck is wrong!!!!
;        xor     eax,eax
;        .WHILE (eax <= 14h)
;            mov     ebx,eax
;            call    display_al
;
;            mov     edx,STATUS_REG1
;            in      al,dx
;            call    invWait_a_bit
;
;            mov     edx,ATTRIB_INDEX
;            mov     al,bl
;            or      al,20h
;            out     dx,al
;            call    invWait_a_bit
;
;            mov     edx,ATTRIB_DATA_READ
;            in      al,dx                                           ; Red
;            call    display_al
;            callf   VID_move_to_next_line_mono
;
;            mov     eax,ebx
;            inc     eax
;        .ENDW






    keyboard_logo                           db  00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
                                            db  00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
                                            db  0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh
                                            db  0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh
                                            db  0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh
                                            db  0fh,0fh,0fh,07h,07h,10h,0fh,07h,07h,10h,07h,07h,10h,07h,07h,10h,07h,07h
                                            db  0fh,0fh,0fh,07h,07h,10h,0fh,07h,07h,10h,07h,07h,10h,07h,07h,10h,07h,07h
                                            db  0fh,0fh,0fh,10h,10h,10h,0fh,10h,10h,10h,10h,10h,10h,10h,10h,10h,10h,10h
                                            db  0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh
                                            db  0fh,0fh,0fh,07h,07h,10h,07h,07h,10h,07h,07h,10h,07h,07h,10h,07h,07h,10h
                                            db  0fh,0fh,0fh,07h,07h,10h,07h,07h,10h,07h,07h,10h,07h,07h,10h,07h,07h,10h
                                            db  0fh,0fh,0fh,10h,10h,10h,10h,10h,10h,10h,10h,10h,10h,10h,10h,10h,10h,10h
                                            db  0fh,0fh,0fh,07h,07h,07h,10h,07h,07h,10h,07h,07h,10h,07h,07h,10h,07h,07h
                                            db  0fh,0fh,0fh,07h,07h,07h,10h,07h,07h,10h,07h,07h,10h,07h,07h,10h,07h,07h
                                            db  0fh,0fh,0fh,10h,10h,10h,10h,10h,10h,10h,10h,10h,10h,10h,10h,10h,10h,10h
                                            db  0fh,0fh,0fh,07h,07h,07h,07h,10h,07h,07h,10h,07h,07h,10h,07h,07h,10h,07h
                                            db  20h,20h,20h

    mouse_logo                              db  00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,07h,07h,07h,00h,00h,00h,00h,00h
                                            db  00h,00h,00h,00h,00h,00h,00h,00h,07h,07h,00h,00h,00h,00h,00h,00h,00h,00h
                                            db  00h,00h,00h,00h,00h,00h,00h,07h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
                                            db  00h,00h,00h,00h,00h,00h,00h,07h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
                                            db  00h,00h,00h,00h,00h,0fh,0fh,0fh,00h,0fh,0fh,0fh,00h,00h,00h,00h,00h,00h
                                            db  00h,00h,00h,00h,0fh,10h,10h,10h,00h,10h,10h,10h,0fh,00h,00h,00h,00h,00h
                                            db  00h,00h,00h,00h,0fh,10h,10h,10h,00h,10h,10h,10h,0fh,00h,00h,00h,00h,00h
                                            db  00h,00h,00h,00h,0fh,10h,10h,10h,00h,10h,10h,10h,0fh,00h,00h,00h,00h,00h
                                            db  00h,00h,00h,00h,0fh,00h,00h,00h,00h,00h,00h,00h,0fh,00h,00h,00h,00h,00h
                                            db  00h,00h,00h,00h,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,00h,00h,00h,00h,00h
                                            db  00h,00h,00h,00h,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,00h,00h,00h,00h,00h
                                            db  00h,00h,00h,00h,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,00h,00h,00h,00h,00h
                                            db  00h,00h,00h,00h,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,00h,00h,00h,00h,00h
                                            db  00h,00h,00h,00h,11h,0fh,0fh,0fh,0fh,0fh,0fh,0fh,11h,00h,00h,00h,00h,00h
                                            db  00h,00h,00h,00h,08h,0fh,0fh,0fh,0fh,0fh,0fh,0fh,08h,00h,00h,00h,00h,00h
                                            db  00h,00h,00h,00h,00h,07h,0fh,0fh,0fh,0fh,0fh,07h,00h,00h,00h,00h,00h,00h
                                            db  35h,35h,35h
                                            db  30h,30h,30h

    chip_logo                               db  00h,00h,00h,00h,00h,00h,00h,00h,0fh,00h,00h,00h,00h,00h,00h,00h,00h,00h
                                            db  00h,00h,00h,00h,00h,00h,00h,00h,0fh,00h,00h,00h,0fh,00h,00h,00h,00h,00h
                                            db  0ch,0ch,00h,00h,00h,0fh,0fh,00h,0fh,0fh,00h,00h,00h,00h,0fh,0fh,00h,00h
                                            db  0ch,0ch,00h,00h,0fh,00h,00h,00h,0fh,00h,0fh,00h,0fh,00h,0fh,00h,0fh,00h
                                            db  0ch,0ch,00h,00h,0fh,00h,00h,00h,0fh,00h,0fh,00h,0fh,00h,0fh,00h,0fh,00h
                                            db  0ch,0ch,00h,00h,00h,0fh,0fh,00h,0fh,00h,0fh,00h,0fh,00h,0fh,0fh,00h,00h
                                            db  00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,0fh,00h,00h,00h
                                            db  00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,0fh,00h,00h,00h
                                            db  10h,10h,10h,10h,10h,10h,10h,10h,10h,10h,10h,10h,10h,10h,10h,10h,10h,10h
                                            db  10h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h
                                            db  10h,11h,07h,07h,07h,11h,07h,07h,07h,11h,07h,07h,07h,11h,07h,07h,07h,11h
                                            db  10h,11h,07h,07h,07h,11h,07h,07h,07h,11h,07h,07h,07h,11h,07h,07h,07h,11h
                                            db  10h,11h,11h,07h,11h,11h,11h,07h,11h,11h,11h,07h,11h,11h,11h,07h,11h,11h
                                            db  10h,10h,10h,07h,10h,10h,10h,07h,10h,10h,10h,07h,10h,10h,10h,07h,10h,10h
                                            db  00h,00h,00h,07h,00h,00h,00h,07h,00h,00h,00h,07h,00h,00h,00h,07h,00h,00h
                                            db  00h,00h,00h,07h,00h,00h,00h,07h,00h,00h,00h,07h,00h,00h,00h,07h,00h,00h
                                            db  15,15,15
                                            db  20,20,20

    card_logo                               db  00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
                                            db  00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
                                            db  00h,07h,07h,07h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
                                            db  00h,00h,00h,07h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
                                            db  00h,00h,00h,07h,0ah,0ah,0ah,0ah,0ah,0ah,0ah,0ah,0ah,0ah,0ah,0ah,0ah,00h
                                            db  00h,00h,00h,07h,0ah,0ah,0ah,11h,11h,11h,11h,11h,0ah,0ah,0ah,0ah,0ah,00h
                                            db  00h,00h,00h,07h,0ah,0ah,11h,0ch,0ch,0ch,0ch,0ch,11h,0ah,0ah,0ah,0ah,00h
                                            db  00h,00h,00h,07h,0ah,0ah,11h,0ch,0ch,0ch,0ch,0ch,11h,0ah,0ah,0ah,0ah,00h
                                            db  00h,00h,00h,07h,0ah,0ah,11h,0ch,0ch,0ch,0ch,0ch,11h,0ah,0ah,0ah,0ah,00h
                                            db  00h,00h,00h,07h,0ah,0ah,11h,0ch,0ch,0ch,0ch,0ch,11h,0ah,0ah,0ah,0ah,00h
                                            db  00h,00h,00h,07h,0ah,0ah,0ah,11h,11h,11h,11h,11h,0ah,0ah,0ah,0ah,0ah,00h
                                            db  00h,00h,00h,07h,0ah,0ah,0ah,0ah,0ah,0ah,0ah,0ah,0ah,0ah,0ah,0ah,00h,00h
                                            db  00h,00h,00h,07h,00h,0eh,10h,0eh,10h,0eh,10h,0eh,10h,0eh,00h,00h,00h,00h
                                            db  00h,00h,00h,07h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
                                            db  00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
                                            db  00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
                                            db  037h,037h,010h
                                            db  000h,032h,000h

    com_logo                                db  0eh,0eh,0eh,0eh,0eh,0eh,0eh,0eh,0eh,0eh,0eh,0eh,0eh,0eh,0eh,0eh,0eh,0eh
                                            db  0eh,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,0eh
                                            db  0eh,00h,00h,00h,00h,00h,11h,11h,11h,11h,11h,11h,00h,00h,00h,00h,00h,0eh
                                            db  0eh,00h,00h,00h,00h,10h,12h,12h,12h,12h,12h,12h,10h,00h,00h,00h,00h,0eh
                                            db  0eh,00h,00h,00h,00h,10h,12h,12h,12h,12h,12h,12h,10h,00h,00h,00h,00h,0eh
                                            db  0eh,00h,00h,00h,00h,10h,12h,12h,12h,12h,12h,12h,10h,00h,00h,00h,00h,0eh
                                            db  0eh,00h,00h,00h,00h,10h,10h,10h,12h,12h,10h,10h,10h,00h,00h,00h,00h,0eh
                                            db  0eh,00h,00h,00h,00h,00h,00h,10h,10h,10h,10h,00h,00h,00h,00h,00h,00h,0eh
                                            db  0eh,00h,00h,00h,00h,00h,00h,10h,10h,10h,10h,00h,00h,00h,00h,00h,00h,0eh
                                            db  0eh,00h,00h,00h,00h,00h,00h,00h,10h,10h,00h,00h,00h,00h,00h,00h,00h,0eh
                                            db  0eh,00h,00h,00h,00h,00h,00h,00h,10h,10h,00h,00h,00h,00h,00h,00h,00h,0eh
                                            db  0eh,00h,00h,00h,00h,00h,00h,00h,10h,10h,00h,00h,00h,00h,00h,00h,00h,0eh
                                            db  0eh,00h,00h,00h,00h,00h,00h,00h,10h,10h,00h,00h,00h,00h,00h,00h,00h,0eh
                                            db  0eh,00h,00h,00h,00h,00h,00h,00h,10h,10h,00h,00h,00h,00h,00h,00h,00h,0eh
                                            db  0eh,00h,00h,00h,00h,00h,00h,00h,10h,10h,00h,00h,00h,00h,00h,00h,00h,0eh
                                            db  0eh,0eh,0eh,0eh,0eh,0eh,0eh,0eh,10h,10h,0eh,0eh,0eh,0eh,0eh,0eh,0eh,0eh
                                            db  22h,22h,22h
                                            db  34h,34h,34h
                                            db  27h,27h,27h

    lpt_logo                                db  0eh,0eh,0eh,0eh,0eh,0eh,0eh,0eh,0eh,0eh,0eh,0eh,0eh,0eh,0eh,0eh,0eh,0eh
                                            db  0eh,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,0eh
                                            db  0eh,00h,00h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,00h,00h,0eh
                                            db  0eh,00h,00h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,00h,00h,0eh
                                            db  0eh,00h,10h,12h,12h,12h,12h,12h,12h,12h,12h,12h,12h,12h,12h,10h,00h,0eh
                                            db  0eh,00h,10h,12h,12h,12h,12h,12h,12h,12h,12h,12h,12h,12h,12h,10h,00h,0eh
                                            db  0eh,00h,10h,10h,10h,12h,12h,12h,12h,12h,12h,12h,12h,10h,10h,10h,00h,0eh
                                            db  0eh,00h,00h,00h,10h,10h,10h,12h,12h,12h,12h,10h,10h,10h,00h,00h,00h,0eh
                                            db  0eh,00h,00h,00h,00h,00h,10h,10h,10h,10h,10h,10h,00h,00h,00h,00h,00h,0eh
                                            db  0eh,00h,00h,00h,00h,00h,00h,10h,10h,10h,10h,00h,00h,00h,00h,00h,00h,0eh
                                            db  0eh,00h,00h,00h,00h,00h,00h,00h,10h,10h,00h,00h,00h,00h,00h,00h,00h,0eh
                                            db  0eh,00h,00h,00h,00h,00h,00h,00h,10h,10h,00h,00h,00h,00h,00h,00h,00h,0eh
                                            db  0eh,00h,00h,00h,00h,00h,00h,00h,10h,10h,00h,00h,00h,00h,00h,00h,00h,0eh
                                            db  0eh,00h,00h,00h,00h,00h,00h,00h,10h,10h,00h,00h,00h,00h,00h,00h,00h,0eh
                                            db  0eh,00h,00h,00h,00h,00h,00h,00h,10h,10h,00h,00h,00h,00h,00h,00h,00h,0eh
                                            db  0eh,0eh,0eh,0eh,0eh,0eh,0eh,0eh,10h,10h,0eh,0eh,0eh,0eh,0eh,0eh,0eh,0eh
                                            db  22h,22h,22h
                                            db  34h,34h,34h
                                            db  27h,27h,27h

    debi_logo                               db  09h,09h,09h,09h,09h,09h,09h,09h,09h,09h,09h,09h,09h,09h,00h,00h,00h,00h
                                            db  09h,01h,01h,01h,01h,01h,01h,01h,01h,01h,01h,01h,01h,09h,09h,00h,00h,00h
                                            db  09h,09h,09h,01h,01h,01h,01h,09h,09h,09h,09h,01h,01h,01h,01h,09h,00h,00h
                                            db  00h,00h,09h,01h,01h,01h,01h,09h,00h,00h,00h,09h,09h,01h,01h,01h,09h,00h
                                            db  00h,00h,09h,01h,01h,01h,0eh,09h,0eh,00h,00h,00h,09h,01h,01h,01h,01h,09h
                                            db  00h,00h,09h,0fh,0fh,01h,04h,0ch,0ch,04h,00h,0fh,0fh,0fh,01h,01h,01h,09h
                                            db  00h,00h,0fh,01h,01h,0fh,04h,0ch,0ch,04h,0fh,00h,00h,09h,0fh,01h,01h,09h
                                            db  00h,00h,09h,01h,01h,01h,0ch,0ch,0ch,0ch,00h,00h,00h,09h,01h,01h,01h,09h
                                            db  00h,00h,09h,01h,0fh,0fh,0ch,0ch,0ch,0ch,0fh,0fh,00h,09h,01h,01h,01h,09h
                                            db  00h,00h,09h,0fh,01h,01h,04h,0ch,0ch,04h,00h,00h,0fh,0fh,01h,01h,01h,09h
                                            db  00h,00h,0fh,01h,01h,01h,0fh,0ch,0ch,0fh,00h,00h,09h,01h,0fh,01h,01h,09h
                                            db  00h,00h,09h,01h,01h,0fh,01h,09h,00h,00h,0fh,00h,09h,01h,01h,01h,01h,09h
                                            db  00h,00h,09h,01h,01h,0fh,01h,09h,00h,00h,00h,0fh,09h,01h,01h,01h,09h,00h
                                            db  09h,09h,09h,01h,0fh,01h,01h,09h,09h,09h,09h,0fh,01h,01h,01h,09h,00h,00h
                                            db  09h,01h,01h,01h,0fh,01h,01h,01h,01h,01h,01h,01h,0fh,09h,09h,00h,00h,00h
                                            db  09h,09h,09h,09h,09h,09h,09h,09h,09h,09h,09h,09h,09h,00h,00h,00h,00h,00h

    floppy_35_logo                          db  00h,11h,10h,09h,09h,09h,09h,09h,09h,09h,09h,09h,09h,09h,09h,10h,11h,00h
                                            db  00h,11h,10h,09h,09h,09h,09h,09h,09h,09h,09h,09h,09h,09h,09h,10h,11h,00h
                                            db  00h,11h,00h,09h,09h,09h,09h,09h,09h,09h,09h,09h,09h,09h,09h,10h,11h,00h
                                            db  00h,11h,10h,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,10h,11h,00h
                                            db  00h,11h,10h,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,10h,11h,00h
                                            db  00h,11h,10h,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,10h,11h,00h
                                            db  00h,11h,10h,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,10h,11h,00h
                                            db  00h,11h,10h,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,10h,11h,00h
                                            db  00h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,00h
                                            db  00h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,00h
                                            db  00h,11h,11h,11h,11h,0ch,0ch,0ch,0ch,0ch,0ch,10h,10h,10h,11h,11h,11h,00h
                                            db  00h,11h,11h,11h,11h,0ch,10h,10h,0ch,0ch,0ch,10h,10h,10h,11h,11h,11h,00h
                                            db  00h,11h,11h,11h,11h,0ch,10h,10h,0ch,0ch,0ch,10h,10h,10h,11h,11h,11h,00h
                                            db  00h,11h,11h,11h,11h,0ch,10h,10h,0ch,0ch,0ch,10h,10h,10h,11h,11h,11h,00h
                                            db  00h,00h,11h,11h,11h,0ch,10h,10h,0ch,0ch,0ch,10h,10h,10h,11h,11h,11h,00h
                                            db  00h,00h,00h,11h,11h,0ch,0ch,0ch,0ch,0ch,0ch,11h,11h,11h,11h,11h,11h,00h
                                            db  19h,19h,19h
                                            db  1fh,1fh,1fh

    floppy_525_logo                         db  08h,08h,08h,08h,08h,08h,08h,08h,08h,08h,08h,08h,08h,08h,08h,08h,08h,08h
                                            db  08h,08h,08h,08h,08h,08h,08h,08h,08h,08h,08h,08h,08h,08h,08h,08h,08h,08h
                                            db  08h,08h,08h,08h,08h,08h,08h,08h,08h,08h,08h,08h,08h,08h,08h,08h,08h,08h
                                            db  08h,08h,08h,08h,08h,08h,08h,08h,08h,08h,08h,08h,08h,08h,08h,08h,08h,00h
                                            db  08h,08h,08h,08h,08h,08h,08h,08h,08h,08h,08h,08h,08h,08h,08h,08h,08h,08h
                                            db  08h,08h,08h,08h,08h,08h,08h,08h,00h,00h,08h,08h,08h,08h,08h,08h,08h,08h
                                            db  08h,08h,08h,08h,08h,08h,08h,00h,00h,00h,00h,08h,08h,08h,08h,08h,08h,08h
                                            db  08h,08h,08h,08h,08h,08h,00h,00h,00h,00h,00h,00h,08h,08h,08h,08h,08h,08h
                                            db  08h,08h,08h,08h,08h,08h,08h,00h,00h,00h,00h,08h,08h,08h,08h,08h,08h,08h
                                            db  08h,08h,08h,08h,08h,08h,08h,08h,00h,00h,08h,08h,07h,08h,08h,08h,08h,08h
                                            db  08h,08h,08h,08h,08h,08h,08h,08h,08h,08h,08h,08h,08h,08h,08h,08h,08h,08h
                                            db  08h,08h,08h,08h,08h,08h,08h,08h,08h,08h,08h,08h,08h,08h,08h,08h,08h,08h
                                            db  08h,08h,08h,08h,08h,08h,08h,08h,07h,07h,08h,08h,08h,08h,08h,08h,08h,08h
                                            db  08h,08h,08h,08h,08h,08h,08h,08h,07h,07h,08h,08h,08h,08h,08h,08h,08h,08h
                                            db  08h,08h,08h,08h,08h,08h,08h,08h,07h,07h,08h,08h,08h,08h,08h,08h,08h,08h
                                            db  08h,08h,08h,08h,08h,08h,08h,08h,08h,08h,08h,08h,08h,08h,08h,08h,08h,08h

    hard_drive_logo                         db  00h,0ch,00h,10h,10h,11h,11h,11h,11h,11h,11h,11h,10h,10h,10h,10h,10h,00h
                                            db  00h,00h,00h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,10h,10h,00h
                                            db  00h,10h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,10h,00h
                                            db  00h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,00h
                                            db  00h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,00h
                                            db  00h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,00h
                                            db  00h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,00h
                                            db  00h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,00h
                                            db  00h,10h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,10h,00h
                                            db  00h,10h,10h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,10h,10h,00h
                                            db  00h,10h,10h,10h,10h,11h,11h,11h,11h,11h,11h,11h,10h,10h,10h,10h,10h,00h
                                            db  00h,10h,10h,10h,10h,10h,10h,10h,10h,10h,10h,10h,10h,10h,10h,10h,10h,00h
                                            db  00h,08h,08h,08h,08h,08h,08h,08h,08h,08h,08h,10h,0fh,0fh,0fh,0fh,10h,00h
                                            db  00h,08h,08h,08h,08h,08h,08h,08h,08h,08h,08h,10h,0fh,0fh,0fh,0fh,10h,00h
                                            db  00h,04h,07h,07h,07h,07h,07h,07h,07h,07h,07h,00h,0fh,0fh,0fh,0fh,00h,00h
                                            db  00h,04h,07h,07h,07h,07h,07h,07h,07h,07h,07h,00h,0ch,08h,12h,0eh,00h,00h
                                            db  18h,18h,18h
                                            db  14h,14h,14h
                                            db  1ah,1ah,1ah

    sound_logo                              db  00h,00h,00h,00h,00h,00h,12h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
                                            db  00h,00h,00h,00h,00h,07h,11h,11h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
                                            db  00h,00h,00h,00h,07h,12h,11h,11h,00h,00h,00h,00h,00h,00h,07h,00h,00h,00h
                                            db  00h,00h,00h,08h,13h,12h,11h,10h,0eh,00h,00h,00h,00h,07h,00h,00h,00h,00h
                                            db  00h,00h,08h,0eh,13h,12h,11h,10h,0eh,00h,00h,00h,07h,00h,00h,00h,00h,00h
                                            db  00h,08h,0eh,0eh,13h,12h,11h,10h,0eh,00h,00h,00h,00h,00h,00h,00h,00h,00h
                                            db  08h,0eh,0eh,0eh,08h,08h,11h,10h,0eh,00h,00h,00h,00h,00h,00h,00h,00h,00h
                                            db  08h,0eh,0eh,0eh,08h,0eh,08h,10h,0eh,00h,00h,00h,07h,07h,07h,07h,07h,00h
                                            db  08h,0eh,0eh,0eh,08h,0eh,08h,10h,0eh,00h,00h,00h,00h,00h,00h,00h,00h,00h
                                            db  08h,10h,0eh,0eh,08h,08h,11h,10h,0eh,00h,00h,00h,00h,00h,00h,00h,00h,00h
                                            db  00h,08h,10h,0eh,13h,12h,11h,10h,0eh,00h,00h,00h,07h,00h,00h,00h,00h,00h
                                            db  00h,00h,08h,10h,13h,12h,11h,10h,0eh,00h,00h,00h,00h,07h,00h,00h,00h,00h
                                            db  00h,00h,00h,08h,13h,12h,11h,10h,0eh,00h,00h,00h,00h,00h,07h,00h,00h,00h
                                            db  00h,00h,00h,00h,07h,12h,11h,11h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
                                            db  00h,00h,00h,00h,00h,07h,11h,11h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
                                            db  00h,00h,00h,00h,00h,00h,12h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
                                            db  38h,38h,12h
                                            db  30h,30h,10h
                                            db  2bh,2bh,08h
                                            db  24h,24h,07h

    dtnprp_logo                             db  00h,00h,00h,00h,00h,0fh,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
                                            db  00h,00h,00h,00h,00h,0fh,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
                                            db  00h,00h,00h,0fh,0fh,0fh,00h,0fh,0fh,0fh,00h,00h,0fh,0fh,0fh,00h,00h,00h
                                            db  00h,00h,0fh,00h,00h,0fh,00h,0fh,00h,00h,0fh,00h,0fh,00h,00h,0fh,00h,00h
                                            db  00h,00h,0fh,00h,00h,0fh,00h,0fh,00h,00h,0fh,00h,0fh,00h,00h,00h,00h,00h
                                            db  00h,00h,00h,0fh,0fh,0fh,00h,0fh,00h,00h,0fh,00h,0fh,00h,00h,00h,00h,00h
                                            db  00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
                                            db  00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
                                            db  00h,00h,00h,00h,00h,00h,0fh,0fh,0fh,0fh,0fh,0fh,00h,00h,00h,00h,00h,00h
                                            db  00h,00h,00h,09h,09h,09h,0fh,0fh,0fh,0fh,0fh,0fh,09h,09h,09h,00h,00h,00h
                                            db  00h,00h,00h,09h,00h,00h,0fh,0fh,0fh,0fh,0fh,0fh,00h,00h,09h,00h,00h,00h
                                            db  00h,00h,00h,09h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,09h,00h,00h,00h
                                            db  00h,00h,00h,09h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,09h,00h,00h,00h
                                            db  00h,0ch,0ch,0ch,0ch,0ch,00h,00h,00h,00h,00h,00h,0ah,0ah,0ah,0ah,0ah,00h
                                            db  00h,0ch,0ch,0ch,0ch,0ch,00h,00h,00h,00h,00h,00h,0ah,0ah,0ah,0ah,0ah,00h
                                            db  00h,0ch,0ch,0ch,0ch,0ch,00h,00h,00h,00h,00h,00h,0ah,0ah,0ah,0ah,0ah,00h

    fat_logo                                db  00h,00h,00h,00h,00h,0fh,0fh,00h,00h,00h,00h,00h,00h,0fh,00h,00h,00h,00h
                                            db  00h,00h,00h,00h,0fh,00h,00h,00h,0fh,0fh,00h,00h,0fh,0fh,0fh,00h,00h,00h
                                            db  00h,00h,00h,0fh,0fh,0fh,00h,00h,00h,00h,0fh,00h,00h,0fh,00h,00h,00h,00h
                                            db  00h,00h,00h,00h,0fh,00h,00h,00h,0fh,0fh,0fh,00h,00h,0fh,00h,00h,00h,00h
                                            db  00h,00h,00h,00h,0fh,00h,00h,0fh,00h,00h,0fh,00h,00h,0fh,00h,00h,00h,00h
                                            db  00h,00h,00h,00h,0fh,00h,00h,00h,0fh,0fh,0fh,00h,00h,00h,0fh,00h,00h,00h
                                            db  00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
                                            db  00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
                                            db  0fh,0fh,0fh,0fh,0fh,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
                                            db  0fh,0fh,0fh,0fh,0fh,09h,09h,09h,09h,09h,09h,09h,09h,09h,09h,00h,00h,00h
                                            db  0fh,0fh,0fh,0fh,0fh,00h,00h,00h,09h,00h,00h,00h,00h,00h,09h,00h,00h,00h
                                            db  00h,00h,09h,00h,00h,00h,00h,00h,09h,00h,00h,00h,00h,00h,09h,00h,00h,00h
                                            db  00h,00h,09h,00h,00h,00h,00h,00h,09h,00h,00h,00h,00h,00h,09h,00h,00h,00h
                                            db  00h,0ch,0ch,0ch,0ch,00h,00h,0ah,0ah,0ah,0ah,00h,00h,0eh,0eh,0eh,0eh,00h
                                            db  00h,0ch,0ch,0ch,0ch,00h,00h,0ah,0ah,0ah,0ah,00h,00h,0eh,0eh,0eh,0eh,00h
                                            db  00h,0ch,0ch,0ch,0ch,00h,00h,0ah,0ah,0ah,0ah,00h,00h,0eh,0eh,0eh,0eh,00h

    network_logo                            db  00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,0fh,00h,00h,00h
                                            db  00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,0fh,0fh,0fh,00h,00h
                                            db  00h,00h,00h,0fh,0fh,0fh,00h,00h,00h,0fh,0fh,00h,00h,00h,0fh,00h,00h,00h
                                            db  00h,00h,00h,0fh,00h,00h,0fh,00h,0fh,00h,0fh,0fh,00h,00h,0fh,00h,00h,00h
                                            db  00h,00h,00h,0fh,00h,00h,0fh,00h,0fh,0fh,00h,00h,00h,00h,0fh,00h,00h,00h
                                            db  00h,00h,00h,0fh,00h,00h,0fh,00h,00h,0fh,0fh,0fh,00h,00h,00h,0fh,00h,00h
                                            db  00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
                                            db  00h,00h,00h,00h,00h,00h,00h,0fh,0fh,0fh,0fh,0fh,00h,00h,00h,00h,00h,00h
                                            db  00h,00h,00h,00h,00h,00h,00h,0fh,0fh,0fh,0fh,0fh,00h,00h,00h,00h,00h,00h
                                            db  00h,00h,00h,00h,00h,00h,00h,00h,00h,10h,00h,00h,00h,00h,00h,00h,00h,00h
                                            db  00h,0fh,0fh,0fh,00h,00h,00h,00h,00h,02h,00h,00h,00h,00h,00h,0fh,0fh,0fh
                                            db  00h,0fh,0fh,0fh,02h,02h,02h,02h,02h,00h,02h,02h,02h,02h,02h,0fh,0fh,0fh
                                            db  00h,0fh,0fh,0fh,00h,00h,00h,00h,00h,02h,00h,00h,00h,00h,00h,0fh,0fh,0fh
                                            db  00h,00h,00h,00h,00h,00h,00h,00h,00h,02h,00h,00h,00h,00h,00h,00h,00h,00h
                                            db  00h,00h,00h,00h,00h,00h,00h,0fh,0fh,0fh,0fh,0fh,00h,00h,00h,00h,00h,00h
                                            db  00h,00h,00h,00h,00h,00h,00h,0fh,0fh,0fh,0fh,0fh,00h,00h,00h,00h,00h,00h
                                            db  00h,26h,00

;   grace_logo                              db  úúúúúúúúúúúúúúúúúú
;                                           db  úúúúúúúúúúúúúúúúúú
;                                           db  úúúúúúúúúúúúúúúúúú
;                                           db  úúúúúúúúúúúúúúúúúú
;                                           db  úúúúúúúúúúúúúúúúúú
;                                           db  úúúúúúúúúúúúúúúúúú
;                                           db  úúúúúúúúúúúúúúúúúú
;                                           db  úúúúúúúúúúúúúúúúúú
;                                           db  úúúúúúúúúúúúúúúúúú
;                                           db  úúúúúúúúúúúúúúúúúú
;                                           db  úúúúúúúúúúúúúúúúúú
;                                           db  úúúúúúúúúúúúúúúúúú
;                                           db  úúúúúúúúúúúúúúúúúú
;                                           db  úúúúúúúúúúúúúúúúúú
;                                           db  úúúúúúúúúúúúúúúúúú
;                                           db  úúúúúúúúúúúúúúúúúú
;
;   elegance_logo                           db  úúúúúúúúúúúúúúúúúú
;                                           db  úúúúúúúúúúúúúúúúúú
;                                           db  úúúúúúúúúúúúúúúúúú
;                                           db  úúúúúúúúúúúúúúúúúú
;                                           db  úúúúúúúúúúúúúúúúúú
;                                           db  úúúúúúúúúúúúúúúúúú
;                                           db  úúúúúúúúúúúúúúúúúú
;                                           db  úúúúúúúúúúúúúúúúúú
;                                           db  úúúúúúúúúúúúúúúúúú
;                                           db  úúúúúúúúúúúúúúúúúú
;                                           db  úúúúúúúúúúúúúúúúúú
;                                           db  úúúúúúúúúúúúúúúúúú
;                                           db  úúúúúúúúúúúúúúúúúú
;                                           db  úúúúúúúúúúúúúúúúúú
;                                           db  úúúúúúúúúúúúúúúúúú
;                                           db  úúúúúúúúúúúúúúúúúú

    typeset_logo                            db  12h,12h,12h,12h,12h,12h,12h,12h,12h,12h,12h,12h,12h,12h,12h,12h,12h,0fh
                                            db  12h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,0fh
                                            db  12h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,0fh
                                            db  12h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,0fh
                                            db  12h,12h,12h,12h,12h,12h,11h,11h,11h,11h,11h,12h,12h,12h,12h,12h,12h,0fh
                                            db  12h,10h,10h,10h,10h,10h,11h,11h,11h,11h,11h,10h,10h,10h,10h,10h,12h,0fh
                                            db  12h,12h,12h,12h,12h,12h,11h,11h,11h,11h,11h,12h,12h,12h,12h,12h,12h,0fh
                                            db  12h,10h,10h,10h,10h,10h,11h,11h,11h,11h,11h,10h,10h,10h,10h,12h,12h,0fh
                                            db  12h,12h,12h,12h,12h,12h,11h,11h,11h,11h,11h,12h,12h,12h,12h,12h,12h,0fh
                                            db  12h,10h,10h,10h,10h,10h,11h,11h,11h,11h,11h,10h,10h,10h,10h,10h,10h,0fh
                                            db  12h,12h,12h,12h,12h,12h,11h,11h,11h,11h,11h,12h,12h,12h,12h,12h,12h,0fh
                                            db  12h,10h,10h,10h,10h,12h,11h,11h,11h,11h,11h,12h,12h,12h,12h,12h,12h,0fh
                                            db  12h,12h,12h,12h,12h,12h,11h,11h,11h,11h,11h,12h,12h,12h,12h,12h,12h,0fh
                                            db  12h,12h,12h,12h,12h,12h,11h,11h,11h,11h,11h,12h,12h,12h,12h,12h,12h,0fh
                                            db  12h,10h,10h,10h,10h,12h,11h,11h,11h,11h,11h,12h,12h,12h,12h,12h,12h,0fh
                                            db  12h,12h,12h,12h,12h,12h,12h,12h,12h,12h,12h,12h,12h,12h,12h,12h,12h,0fh
                                            db  2dh,2dh,2dh
                                            db  33h,00h,33h
                                            db  3ah,3ah,3ah

    numbers_logo                            db  10h,10h,10h,10h,12h,10h,10h,10h,10h,12h,10h,10h,10h,10h,12h,10h,10h,10h
                                            db  10h,10h,11h,11h,11h,11h,10h,10h,10h,12h,10h,10h,11h,11h,11h,11h,10h,10h
                                            db  12h,12h,11h,11h,11h,11h,11h,12h,12h,12h,12h,12h,11h,11h,11h,11h,12h,0fh
                                            db  10h,10h,11h,11h,11h,11h,11h,11h,10h,12h,10h,10h,11h,11h,11h,11h,10h,10h
                                            db  10h,10h,11h,11h,11h,11h,11h,11h,11h,12h,10h,10h,11h,11h,11h,11h,10h,10h
                                            db  12h,12h,11h,11h,11h,11h,11h,11h,11h,11h,12h,12h,11h,11h,11h,11h,12h,0fh
                                            db  10h,10h,11h,11h,11h,11h,11h,11h,11h,11h,11h,12h,11h,11h,11h,11h,10h,10h
                                            db  10h,10h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,10h,10h
                                            db  12h,12h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,12h,0fh
                                            db  10h,10h,11h,11h,11h,11h,12h,11h,11h,11h,11h,11h,11h,11h,11h,11h,10h,10h
                                            db  10h,10h,11h,11h,11h,11h,12h,12h,11h,11h,11h,11h,11h,11h,11h,11h,10h,10h
                                            db  12h,12h,11h,11h,11h,11h,10h,10h,10h,11h,11h,11h,11h,11h,11h,11h,12h,0fh
                                            db  10h,10h,11h,11h,11h,11h,10h,10h,10h,12h,11h,11h,11h,11h,11h,11h,10h,10h
                                            db  10h,10h,11h,11h,11h,11h,12h,12h,12h,12h,12h,11h,11h,11h,11h,11h,10h,10h
                                            db  12h,12h,11h,11h,11h,11h,10h,10h,10h,12h,10h,10h,11h,11h,11h,11h,12h,0fh
                                            db  10h,10h,10h,10h,12h,10h,10h,10h,10h,12h,10h,10h,10h,10h,12h,10h,10h,10h
                                            db  2dh,2dh,2dh
                                            db  33h,00h,33h
                                            db  3ah,3ah,3ah      ;; Initialize internal constants
        mov     ds:timer_max_hz,182                                 ; timer_max_hz = 182
        mov     dword ptr ds:timer_max_value[0],0c7e9b820h          ; timer_max_value = 119318100000 = 1bc7e9b820h
        mov     dword ptr ds:timer_max_value[4],01bh

        mov     esi,offset timer_area
        mov     word ptr [esi+_TIMER_GDT],0ffffh                    ; GDT entry (0ffffh means it's the system time-of-day event)
        mov     word ptr [esi+_TIMER_LDT],0                         ; LDT (it's the _sTIMER descriptor)
        mov     dword ptr [esi+_TIMER_INC_VALUE],0c75ed2bah         ; We have set the timer to interrupt ~182 times/second.  See
        mov     dword ptr [esi+_TIMER_INC_VALUE+4],01bh             ; the note above about this value.
        mov     dword ptr [esi+_TIMER_CURRENT_VALUE],0
        mov     dword ptr [esi+_TIMER_CURRENT_VALUE+4],0
        mov     dword ptr [esi+_TIMER_ORIGINAL_FREQ],433610A2h      ; * Note:  433610A2h = real4 182.064971924 in dword format
      ; Terminate the listings entry                                ;          MASM won't recognize "mov real4 ptr [si+20],182.0"
        add     esi,_TIMER_STRUCT_LENGTH                            ;          even though it's only a 4-byte move.  Oh well!
        mov     dword ptr [esi],0ffffffffh

      ;; Wait for CMOS to be ready for us to read
        mov     al,_CMOS_STATUS_REGISTER_A                          ; Tell CMOS we want to read the status register A
        out     _CMOS_70h,al                                        ; First, wait for it to go high (because we could've been very
        @IO_pause                                                   ; lucky and gotten in while it was low, but it could've been

        xor     ecx,ecx                                             ; Set a limit as to how long it waits
      wait_high:
        in      al,_CMOS_71h                                        ; Read the data
        test    al,80h                                              ; We're waiting for it to go high (1)
        loopnzd wait_high                                           ; If branch then it's low (0)

        xor     ecx,ecx
      wait_low:
        in      al,_CMOS_71h                                        ; Read the data
        test    al,80h                                              ; We're waiting for it to go low (0)
        loopzd  wait_low                                            ; If branch then it's high (1)

      ;; Initialize constants
        mov     ax,_sSYSTEM_AREA                                    ; We're going to be storing time and date information
        mov     ds,ax
        mov     byte ptr ds:[_SYSTEM_SECONDS_SINCE_BOOTUP],0        ; Initialize the one's that aren't calculation dependent
        mov     byte ptr ds:[_SYSTEM_182S_OF_A_SECOND],0

      ;; Read CMOS and store the converted BCD data as integers
        fninit                                                      ; Initialize the fpu (we'll be using it shortly)
        xor     eax,eax                                             ; Clear off all bits (we'll be loading BCD into fpu)
        xor     ebx,ebx
        mov     edi,offset cmos_conversion_table                    ; * Note:  Refer to bootup.com for information
        .WHILE (byte ptr cs:[edi] != 0ffh)
            mov     al,byte ptr cs:[edi]                            ; Read the CMOS register to read in
            inc     di
            out     _CMOS_70h,al                                    ; Tell CMOS what we'll be reading
            @IO_pause
            in      al,_CMOS_71h                                    ; Read it

            mov     ah,byte ptr cs:[edi]
            inc     di
            .IF (ah == _BCD_CONVERT)
                push    dword ptr 0                                 ; Stick 6 extra bytes on the stack (fbld loads tbyte ptr)
                push    word ptr 0
                and     eax,0ffh
                push    eax                                         ; Stick it on the stack (remember eax's other bits are clear)
                mov     ebp,esp
                fbld    tbyte ptr [ebp]                             ; Load it as a BCD
                fistp   dword ptr [ebp]                             ; Store it as an integer
                pop     eax                                         ; And load it back into eax as an integer
                add     esp,6                                       ; Clear the 6 bytes back off the stack
            .ENDIF

            mov     bl,byte ptr cs:[edi]                            ; Populate bx with the offset in _sSYSTEM_AREA to store this byte
            inc     edi
            mov     byte ptr [ebx],al                               ; And store the integer version of the BCD data
        .ENDW                                                       ; Do the next one
        add     word ptr ds:[_SYSTEM_YEAR],2000                     ; Adjust the century (CMOS stores xx=00-99, we assume 2000+xx)
        mov     ds,cs:data_segment
      ;; Setup the TSS in the GDT
        mov     eax,_sTASK_MGR_TSS / 8
        mov     ebx,82080h
        mov     edx,07fh                                            ; 128 bytes
        call    create_tss_descriptor32

      ;; Physically create the TSS in memory
        push    ds
        mov     ax,_sALL_MEM
        mov     ds,ax
        mov     esi,82080h
      ; Right now, ds:[esi] - far ptr to TSS location in memory
        mov     ebx,_sCODE
        mov     ecx,offset timer_handler
        mov     edx,_sTASK_MGR_STACK
        mov     edi,1ffch                                           ; 8k stack
        call    create_tss32
        pop     ds


        mov     ebx,dword ptr ds:timer_max_value[0]
        mov     ecx,dword ptr ds:timer_max_value[4]

    ;; Increment all of the timer event counters
        mov     esi,offset timer_area
        jmp     timer_loop                                          ; We know there is always at least one event (the system timer)
        .WHILE (dword ptr ds:[esi+_TIMER_GDT_LDT] != -1)
          timer_loop:
            .IF (dword ptr ds:[esi+_TIMER_GDT_LDT] != 0fffffffeh)
              ; This is 64-bit math.  Rather than use the FPU we do it in integers because it's faster
              ; This routine is called a minimum of 182 times per second, and possible one hell of a lot more!
                mov     eax,dword ptr ds:[esi+_TIMER_INC_VALUE]                 ; Load increment value into edx:eax
                mov     edx,dword ptr ds:[esi+_TIMER_INC_VALUE+4]
                add     dword ptr ds:[esi+_TIMER_CURRENT_VALUE],eax             ; Increment the current value
                adc     dword ptr ds:[esi+_TIMER_CURRENT_VALUE+4],edx

                cmp     dword ptr ds:[esi+_TIMER_CURRENT_VALUE+4],ecx           ; Are we beyond the maximum count value in the high dword?
                ja      timer_adjust_counter                                    ; Yes if branch, this means we're definately over
                jnz     timer_next_slot                                         ; If branch, then it's less than the high dword (not yet)

                cmp     dword ptr ds:[esi+_TIMER_CURRENT_VALUE],ebx             ; Is the low dword >= ebx?
                jb      timer_next_slot                                         ; No if branch

              timer_adjust_counter:                                             ; Yes, it is!  Process it!
                sub     dword ptr ds:[esi+_TIMER_CURRENT_VALUE],ebx             ; Reset the counter value down (keeping the overflow)
                sbb     dword ptr ds:[esi+_TIMER_CURRENT_VALUE+4],ecx
              timer_execute_task:
                cmp     word ptr ds:[esi+_TIMER_GDT],0ffffh
                jnz     timer_application_event                jmp     timer_next_slot


              timer_application_event:                              ;; It's an application event
                ;; REMEMBER
                jmp     timer_next_slot
            .ENDIF
          timer_next_slot:
            add     esi,_TIMER_STRUCT_LENGTH
        .ENDW



;        dec     esi
;        inc     byte ptr ds:[esi]
;        cmp     byte ptr ds:[esi],60
;        jb      timer_system_event_done
;        mov     byte ptr ds:[esi],al
;
;    ;; Increment the minutes
;        dec     esi
;        inc     byte ptr ds:[esi]
;        cmp     byte ptr ds:[esi],59
;        jb      timer_system_event_done
;        mov     byte ptr ds:[esi],al
;
;    ;; Increment the hours
;        dec     esi
;        inc     byte ptr ds:[esi]
;        cmp     byte ptr ds:[esi],24
;        jb      timer_system_event_done
;        mov     byte ptr ds:[esi],0
;
;    ;; Increment the date (we're into the next day here)
;        call    invTIMER_system_event_next_date


    invTIMER_system_event_next_date     PROC
    ; This routine ensures that the date is valid
    ; It has to do some more complex math so it was brought into its own algorithm
        push    ax
        push    dx

      ;; Increment the day of the month
        inc     byte ptr ds:[_SYSTEM_DAY]

      ;; See if we're into the next month
        mov     dl,byte ptr ds:[_SYSTEM_MONTH]
        .IF (dl == 1 || dl == 3 || dl == 5 || dl == 7 || dl == 8 || dl == 10 || dl == 12)
          ; We're in months with 31 days, Jan, Mar, May, Jul, Aug, Oct, Dec
            .IF (byte ptr ds:[_SYSTEM_DAY] > 31)
                jmp     goto_next_month
            .ENDIF
        .ELSEIF (dl == 2)
          ; We're in February, we need to see if it's a leap year
            mov     ax,word ptr ds:[_SYSTEM_YEAR]
            shr     ax,1
            .IF (carry?)
              not_a_leap_year:                                      ; It's not a leap year, because it's odd
                .IF (byte ptr ds:[_SYSTEM_DAY] > 28)                ; Is the day > 28?
                    jmp     goto_next_month                         ; If branch, yes
                .ENDIF
            .ELSE
                shr     ax,1
                .IF (carry?)
                    jmp     not_a_leap_year                         ; It's not a leap year, (not evenly divisible by 4)
                .ELSE
;; REMEMBER, have to add an algorithm here to weed out any century not evenly divisble by 400, those aren't leap years
                    .IF (byte ptr ds:[_SYSTEM_DAY] > 29)            ; It's a leap year
                        jmp     goto_next_month
                    .ENDIF
                .ENDIF
            .ENDIF
        .ELSE
          ; We're in months with 30 days, Apr, Jun, Sep, Nov
            .IF (byte ptr ds:[_SYSTEM_DAY] > 30)
              goto_next_month:
                mov     byte ptr ds:[_SYSTEM_DAY],1
                inc     byte ptr ds:[_SYSTEM_MONTH]
                .IF (byte ptr ds:[_SYSTEM_MONTH] > 12)
                    mov     byte ptr ds:[_SYSTEM_MONTH],1
                    inc     word ptr ds:[_SYSTEM_YEAR]
                .ENDIF
            .ENDIF
        .ENDIF

      ;; Reset the seconds since midnight
        mov     dword ptr ds:[_SYSTEM_SECONDS_SINCE_MIDNIGHT],0

        pop     dx
        pop     ax
        ret
    invTIMER_system_event_next_date     ENDP

                        .ELSEIF (al == _16_8_8)
                            mov     dword ptr ss:[ebp-092],edx
                          ; Do the upper 16-bits
                            shr     edx,16
                          ; Right now, edx - lower word contains the upper 16-bits of the value specified
                          ;            ebx - 16 (base-16 number, it will be displayed in hexidecimal)
                            mov     eax,dword ptr ds:[edi+5]        ; x
                            add     eax,dword ptr ds:[esi+_ST_OBJECT_UL_HORIZONTAL]
                            push    eax
                            mov     eax,dword ptr ds:[edi+9]        ; y
                            add     eax,dword ptr ds:[esi+_ST_OBJECT_UL_VERTICAL]
                            push    eax
                            mov     ecx,4                           ; number of digits to display
                            call    invDEBI_add_radix_object
                            call    fword ptr ds:_VID_g_display_radix_in_edx_mono

                          ; Do the xh byte (bits 8-15)
                            mov     edx,dword ptr ss:[ebp-092]
                            shr     edx,8
                            and     edx,0ffh
                          ; Right now, edx - lower byte contains the bits 8-15
                          ;            ebx - 16 (base-16number, it will be displayed in hexidecimal)
                            mov     eax,dword ptr ds:[edi+5]        ; x
                            add     eax,dword ptr ds:[esi+_ST_OBJECT_UL_HORIZONTAL]
                            add     eax,5*8
                            push    eax
                            mov     eax,dword ptr ds:[edi+9]        ; y
                            add     eax,dword ptr ds:[esi+_ST_OBJECT_UL_VERTICAL]
                            push    eax
                            mov     ecx,2                           ; number of digits to display
                            call    invDEBI_add_radix_object
                            call    fword ptr ds:_VID_g_display_radix_in_edx_mono

                          ; Do the xl byte (bits 0-7)
                            mov     edx,dword ptr ss:[ebp-092]
                            and     edx,0ffh
                          ; Right now, edx - lower byte contains the bits 0-7
                          ;            ebx - 16 (base-16 number, it will be displayed in hexidecimal)
                            mov     eax,dword ptr ds:[edi+5]        ; x
                            add     eax,dword ptr ds:[esi+_ST_OBJECT_UL_HORIZONTAL]
                            add     eax,8*8
                            push    eax
                            mov     eax,dword ptr ds:[edi+9]        ; y
                            add     eax,dword ptr ds:[esi+_ST_OBJECT_UL_VERTICAL]
                            push    eax
                            mov     ecx,2                           ; number of digits to display
                            call    invDEBI_add_radix_object
                            call    fword ptr ds:_VID_g_display_radix_in_edx_mono
                        .ELSEIF (al == _16_16)
                            mov     dword ptr ss:[ebp-092],edx
                          ; Do the upper 16-bits
                            shr     edx,16
                          ; Right now, edx - lower word contains the upper 16-bits of the value specified
                          ;            ebx - 16 (base-16 number, it will be displayed in hexidecimal)
                            mov     eax,dword ptr ds:[edi+5]        ; x
                            add     eax,dword ptr ds:[esi+_ST_OBJECT_UL_HORIZONTAL]
                            push    eax
                            mov     eax,dword ptr ds:[edi+9]        ; y
                            add     eax,dword ptr ds:[esi+_ST_OBJECT_UL_VERTICAL]
                            push    eax
                            mov     ecx,4                           ; number of digits to display
                            call    invDEBI_add_radix_object
                            call    fword ptr ds:_VID_g_display_radix_in_edx_mono

                          ; Do the lower 16-bits
                            mov     edx,dword ptr ss:[ebp-092]
                            and     edx,0ffffh
                          ; Right now, edx - lower word of the value specified
                          ;            ebx - 16 (base-16 number, it will be displayed in hexidecimal)
                            mov     eax,dword ptr ds:[edi+5]        ; x
                            add     eax,dword ptr ds:[esi+_ST_OBJECT_UL_HORIZONTAL]
                            add     eax,5*8
                            push    eax
                            mov     eax,dword ptr ds:[edi+9]        ; y
                            add     eax,dword ptr ds:[esi+_ST_OBJECT_UL_VERTICAL]
                            push    eax
                            mov     ecx,4                           ; number of digits to display
                            call    invDEBI_add_radix_object
                            call    fword ptr ds:_VID_g_display_radix_in_edx_mono

;--------------------------
inc     dword ptr ss:[esp+64]
cmp     dword ptr ss:[esp+64],6
jnz     skip_halt
   mov edx,ss:[esp+68]
   mov edi,(80*2)*0
   mov ebx,16
   call VID_display_radix_in_edx_mono

   mov edx,ss:[esp+72]
   mov edi,(80*2)*1
   call VID_display_radix_in_edx_mono

   mov edx,ss:[esp+76]
   mov edi,(80*2)*2
   call VID_display_radix_in_edx_mono

   mov edx,ss:[esp+80]
   mov edi,(80*2)*3
   call VID_display_radix_in_edx_mono
   @@:
     hlt
     jmp @B
skip_halt:
;--------------------------



; LOAD_XDEBUG()
IFDEF _XDEBUG
    mov     ax,0200h + 14                                           ; Read 14 debug program sectors
    mov     bx,7000h                                                ; Store at 7000:0000h, or 7000h
    mov     es,bx
    xor     bx,bx
    mov     cx,5h                                                   ; track 0/sector 5
    xor     dx,dx                                                   ; head 0/drive 0
    int     13h                                                     ; Read the bad boy
    jnc     Read_Sectors2
    jmp     Read_Sectors1
  Read_Sectors2:
; * Note:  If this is turned on, make sure code in PB.ASM puts XDEBUG.COM in this file area
    mov     ax,0200h + 18                                           ; Read next 18 debug prog sectors
    mov     bx,512 * 14
    mov     cx,1                                                    ; track 0/sector 1
    mov     dx,100h                                                 ; head 1/drive 0
    int     13h                                                     ; Read the bad boy
    jnc     Read_Sectors3
    jmp     Read_Sectors2
  Read_Sectors3:
    mov     ax,0200h + 18                                           ; Read next 18 debug prog sectors
    mov     bx,512 * (18+14)
    mov     cx,4f01h                                                ; track 79/sector 1
    xor     dx,dx                                                   ; head 0/drive 0
    int     13h                                                     ; Read the bad boy
    jnc     setup_debugger
    jmp     Read_Sectors3
  Setup_Debugger:
    xor     ax,ax
    mov     fs,ax
    mov     eax,70000000h                                           ; Segment (7000h), Offset (0h), linear = 70000h
    mov     dword ptr FS:[1*4],eax                                  ; INT1, single-step
    mov     dword ptr FS:[3*4],eax                                  ; INT3, software breakpoint
ENDIF; Turn off the floppy drive motor
    mov     al,001100b
    mov     edx,03f2h
    out     dx,al



;-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
;
; ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
; ³ _TEXT_FIELD PARAMETERS ³
; ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
_TFP_ENABLED                        EQU
_TFP_VISIBLE                        EQU
_TFP_ALIGNMENT                      EQU
_TFP_AUTO_SIZE                      EQU
_TFP_BORDER                         EQU
_TFP_COLOR_DISABLEP_BACKGROUND      EQU
_TFP_COLOR_DISABLEP_FOREGROUND      EQU
_TFP_COLOR_DISABLEP_STYLE           EQU
_TFP_COLOR_ENABLEP_BACKGROUND       EQU
_TFP_COLOR_ENABLEP_FOREGROUND       EQU
_TFP_COLOR_ENABLEP_STYLE            EQU
_TFP_COLOR_SELECTEP_BACKGROUND      EQU
_TFP_COLOR_SELECTEP_FOREGROUND      EQU
_TFP_COLOR_SELECTEP_STYLE           EQU
_TFP_FONT_NAME                      EQU
_TFP_FONT_SIZE                      EQU
_TFP_FONT_TYPEFACE_BOLD             EQU
_TFP_FONT_TYPEFACE_DITHER           EQU
_TFP_FONT_TYPEFACE_ITALICS          EQU
_TFP_FONT_TYPEFACE_REVERSE          EQU
_TFP_FONT_TYPEFACE_STRIKETHROUGH    EQU
_TFP_FONT_TYPEFACE_UNDERLINE        EQU
_TFP_FONT_NAME_ID                   EQU
_TFP_MARGIN_LEFT                    EQU
_TFP_MARGIN_RIGHT                   EQU
_TFP_MARGIN_TOP                     EQU
_TFP_MARGIN_BOTTOM                  EQU
_TFP_MISC_1                         EQU
_TFP_MISC_2                         EQU
_TFP_MISC_3                         EQU
_TFP_MISC_4                         EQU
_TFP_MOUSE_POINTER                  EQU
_TFP_POSITION_HEIGHT                EQU
_TFP_POSITION_LEFT                  EQU
_TFP_POSITION_TOP                   EQU
_TFP_POSITION_WIDTH                 EQU
_TFP_SELECTEP_END                   EQU
_TFP_SELECTEP_START                 EQU
_TFP_SELECT_ALL_AT_GET_FOCUS        EQU
_TFP_MISC_FLAG_1                    EQU
_TFP_MISC_FLAG_2                    EQU
_TFP_MISC_FLAG_3                    EQU
_TFP_SIZEABLE                       EQU
_TFP_SOURCE_INPUT_FORMAT            EQU
_TFP_SOURCE_INPUT_MASK              EQU
_TFP_SOURCE_MAX_LENGTH              EQU
_TFP_SOURCE_OFFSET                  EQU
_TFP_TAB_INDEX                      EQU
_TFP_TAB_STOP                       EQU
_TFP_UNDO                           EQU
_TFP_WRAP_TEXT                      EQU
_TFP_ZERO_CHAR                      EQU
_TFP_ZERO_CONTENTS                  EQU

_TFE_CLICK_BOTH_SINGLE              EQU
_TFE_CLICK_BOTH_DOUBLE              EQU
_TFE_CLICK_LEFT_SINGLE              EQU
_TFE_CLICK_LEFT_DOUBLE              EQU
_TFE_CLICK_LEFT_DOWN                EQU
_TFE_CLICK_LEFT_UP                  EQU
_TFE_CLICK_RIGHT_SINGLE             EQU
_TFE_CLICK_RIGHT_DOUBLE             EQU
_TFE_CLICK_RIGHT_DOWN               EQU
_TFE_CLICK_RIGHT_UP                 EQU
_TFE_DROPPED_INTO_LEFT              EQU
_TFE_DROPPED_INTO_RIGHT             EQU
_TFE_DRAG_LEFT_START                EQU
_TFE_DRAG_LEFT_STOP                 EQU
_TFE_DRAG_RIGHT_START               EQU
_TFE_DRAG_RIGHT_STOP                EQU
_TFE_FOCUS_GOT                      EQU
_TFE_FOCUS_LOST                     EQU
_TFE_FOCUS_SET                      EQU
_TFE_HOVER                          EQU
_TFE_KEYSTROKE_BEFORE               EQU
_TFE_KEYSTROKE_AFTER                EQU
_TFE_WHEN_CREATED                   EQU
_TFE_WHEN_DESTROYED                 EQU
_TFE_REQUESTOR                      EQU
_TFE_RESIZED_AFTER                  EQU
_TFE_RESIZED_BEFORE                 EQU
_TFE_UNDO_BEFORE                    EQU
_TFE_UNDO_AFTER                     EQU
pushad
xor     eax,eax
mov     edx,dword ptr ds:[_TASK_SYSTEM_CURRENT_TASK_OFFSET]
.IF (edx != _FIRST_TASK_ENTRY)
    mov     ebx,16
    mov     ecx,8
    push    0
    push    0
    call    fword ptr cs:_VID_g_display_radix_in_edx_mono
.ENDIF
popad