; global.asp
;
; Exodus VGA driver global algorithms
;
;




    _position_cursor    PROC
    ; Calculate the offset into the screen, then output the values to monochrome ports
    ;   dh == Row (up/down)
    ;   dl == Column (left/right)
        pushad
        push    ds

        xor     eax,eax                                             ; Clear out ax and bx
        xor     ebx,ebx
        mov     al,dh                                               ; Copy the row there
        mov     bl,dh
        shl     eax,6                                               ; Multiply by 64
        shl     ebx,4                                               ; Multiply by 16
        add     ebx,eax                                             ; 64 + 16 = 80
        and     edx,0ffh
        add     ebx,edx
      ; BX is the offset
        mov     ds,cs:data_segment
        mov     esi,ds:storage_ptr                                  ; Store current offset into video memory
        mov     edx,ebx
        shl     edx,1                                               ; Video memory has two bytes for every one on-screen
        mov     word ptr ds:[esi],dx
      ; bh == high bits, reg1 for index 0xE, reg2 for data
      ; bl == low bits, reg1 for index 0xF, reg2 for data
        call    _position_cursor_raw_data

        pop     ds
        popad
        ret
    _position_cursor    ENDP

    _position_cursor_raw_data    PROC
    ; bx - offset to write
    ; regs1 - index register
    ; regs2 - data register
      ; Send high 8 bits
        mov     dx,cs:reg1
        mov     al,0eh
        out     dx,al
        call    invWait_a_bit
        mov     dx,cs:reg2
        mov     al,bh
        out     dx,al
        call    invWait_a_bit

      ; Send low 8 bits
        mov     dx,cs:reg1
        mov     al,0fh
        out     dx,al
        call    invWait_a_bit
        mov     dx,cs:reg2
        mov     al,bl
        out     dx,al
        call    invWait_a_bit
        ret
    _position_cursor_raw_data    ENDP

    _generate_radix_string   PROC
        mov     byte ptr [ebp+12],0                                 ; NULL terminate the string we're building
        mov     esi,ebp
        add     esi,11
        mov     eax,edx
        and     ebx,0ffffh
        .IF (ebx <= 1)
          ; They've forgotten to set the value, so we correct their little blunder
            mov     ebx,16
        .ENDIF
      @@:
        xor     edx,edx
        div     ebx
        .IF (dl > 9)
            add     dl,'a'-10                                       ; Make it a letter if it's above 9 (10+ cannot be represented in 1 digit)
        .ELSE
            add     dl,'0'                                          ; Make it a number
        .ENDIF
        mov     byte ptr ss:[esi],dl
        dec     esi                                                 ; Decrement (move to next position to store data)
        cmp     esi,ebp
        jz      @F
        cmp     eax,0
        jnz     @B
      @@:
        push    ss
        pop     ds
        inc     esi                                                 ; Add back for the one we decremented above
      ; Right now, ds:[esi] - pointer to the value to display
        ret
    _generate_radix_string   ENDP

    _generate_radix_string_ecx      PROC
    ; Note that the space on the stack for this string must be at least 40 characters
        mov     esi,ebp
        add     esi,35
        mov     eax,edx
        and     ebx,0ffffh
        .IF (ebx <= 1 || ebx > 26)
          ; They've forgotten to set the value, so we correct their little blunder
            mov     ebx,16
        .ENDIF
        .IF (ecx > 7fffffffh)
          ; It's negative
            mov     byte ptr [ebp+36],'ú'
            neg     ecx
        .ELSE
            mov     byte ptr [ebp+36],'0'
        .ENDIF
        .IF (ecx > 32)
            mov     ecx,32
        .ENDIF
      @@:
        xor     edx,edx
        div     ebx
        .IF (dl > 9)
            add     dl,'a'-10                                       ; Make it a letter if it's above 9 (10+ cannot be represented in 1 digit)
        .ELSE
            add     dl,'0'                                          ; Make it a number
        .ENDIF
        mov     byte ptr ss:[esi],dl
        dec     esi                                                 ; Decrement (move to next position to store data)
        cmp     esi,ebp
        jz      @F
        .IF (eax == 0 && byte ptr ss:[esi+1] == '0')
          ; These are all leading 0's.  But, the user might've wanted leading ú's instead, so we do that here
            push    ebx
            mov     bl,byte ptr [ebp+36]
            mov     byte ptr ss:[esi+1],bl
            pop     ebx
        .ENDIF
        loop    @B
      @@:
        mov     byte ptr [ebp+36],0                                 ; NULL terminate the string we're building
        push    ss
        pop     ds
        inc     esi                                                 ; Add back for the one we decremented above
      ; Right now, ds:[esi] - pointer to the value to display
        ret
    _generate_radix_string_ecx      ENDP

    hex_adjust_al_dl    PROC
        shr     dl,4
        .IF (dl <= 9)
            add     dl,'0'
        .ELSE
            add     dl,'a'-10
        .ENDIF
        and     al,0fh
        .IF (al <= 9)
            add     al,'0'
        .ELSE
            add     al,'a'-10
        .ENDIF
        ret
    hex_adjust_al_dl    ENDP

    hex_adjust_al   PROC
        .IF (al <= 9)
            add     al,'0'
        .ELSE
            add     al,'a'-10
        .ENDIF
        ret
    hex_adjust_al   ENDP




    VID_position_cursor_both    PROC
        callf   VID_position_cursor_vga
        callf   VID_position_cursor_mono
        retf
    VID_position_cursor_both    ENDP




    VID_display_string_both     PROC
        callf   VID_display_string_vga
        .IF (cs:mono_video == MONO_TEXT)
            callf   VID_display_string_mono
        .ELSE
            call    invVID_g_display_string_mono
        .ENDIF
        retf
    VID_display_string_both     ENDP




    VID_display_string_ecx_both     PROC
        callf   VID_display_string_ecx_vga
        callf   VID_display_string_ecx_mono
        retf
    VID_display_string_ecx_both     ENDP




    VID_display_string_ecx_nr_both      PROC
        callf   VID_display_string_ecx_nr_vga
        callf   VID_display_string_ecx_nr_mono
        retf
    VID_display_string_ecx_nr_both      ENDP




    VID_display_hex_string_ecx_both     PROC
        callf   VID_display_hex_string_ecx_vga
        callf   VID_display_hex_string_ecx_mono
        retf
    VID_display_hex_string_ecx_both     ENDP




    VID_display_string_nr_both      PROC
        callf   VID_display_string_nr_vga
        callf   VID_display_string_nr_mono
        retf
    VID_display_string_nr_both      ENDP




    VID_display_hex_string_ecx_nr_both      PROC
        callf   VID_display_hex_string_ecx_nr_vga
        callf   VID_display_hex_string_ecx_nr_mono
        retf
    VID_display_hex_string_ecx_nr_both      ENDP




    VID_display_decimal_in_edx_both     PROC
        callf   VID_display_decimal_in_edx_vga
        callf   VID_display_decimal_in_edx_mono
        retf
    VID_display_decimal_in_edx_both     ENDP




    VID_display_decimal_in_edx_nr_both    PROC
        callf   VID_display_decimal_in_edx_nr_vga
        callf   VID_display_decimal_in_edx_nr_mono
        retf
    VID_display_decimal_in_edx_nr_both    ENDP




    VID_display_hexidecimal_in_edx_both     PROC
        callf   VID_display_hexidecimal_in_edx_vga
        callf   VID_display_hexidecimal_in_edx_mono
        retf
    VID_display_hexidecimal_in_edx_both     ENDP




    VID_display_hexidecimal_in_edx_nr_both    PROC
        callf   VID_display_hexidecimal_in_edx_nr_vga
        callf   VID_display_hexidecimal_in_edx_nr_mono
        retf
    VID_display_hexidecimal_in_edx_nr_both    ENDP




    VID_set_attribute_both  PROC
        callf   VID_set_attribute_vga
        callf   VID_set_attribute_mono
        retf
    VID_set_attribute_both  ENDP




    VID_clear_screen_both   PROC
        callf   VID_clear_screen_vga
        callf   VID_clear_screen_mono
        retf
    VID_clear_screen_both   ENDP




    VID_freeze_frame_both   PROC
        callf   VID_freeze_frame_vga
        callf   VID_freeze_frame_mono
        retf
    VID_freeze_frame_both   ENDP




    VID_display_hex_string_ecx_ro_both      PROC
        callf   VID_display_hex_string_ecx_ro_vga
        callf   VID_display_hex_string_ecx_ro_mono
        ret
    VID_display_hex_string_ecx_ro_both      ENDP




    VID_display_radix_in_edx_nr_both        PROC
        callf   VID_display_radix_in_edx_nr_vga
        callf   VID_display_radix_in_edx_nr_mono
        ret
    VID_display_radix_in_edx_nr_both        ENDP




    VID_move_to_next_line_both      PROC
        callf   VID_move_to_next_line_vga
        callf   VID_move_to_next_line_mono
        ret
    VID_move_to_next_line_both      ENDP




    VID_g_set_font_8x6      PROC
        .IF (cs:VID_g_owner != 0ffffffffh)
            push    ds
            mov     ds,cs:data_segment
            mov     ds:current_font,offset font_8x6_name
            pop     ds
        .ENDIF
        retf
    VID_g_set_font_8x6      ENDP




    VID_g_set_font_8x8      PROC
        .IF (cs:VID_g_owner != 0ffffffffh)
            push    ds
            mov     ds,cs:data_segment
            mov     ds:current_font,offset font_8x8_name
            pop     ds
        .ENDIF
        retf
    VID_g_set_font_8x8      ENDP




    VID_g_set_font_8x14     PROC
        .IF (cs:VID_g_owner != 0ffffffffh)
            push    ds
            mov     ds,cs:data_segment
            mov     ds:current_font,offset font_8x14_name
            pop     ds
        .ENDIF
        retf
    VID_g_set_font_8x14     ENDP




    VID_g_set_font_16x16    PROC
        .IF (cs:VID_g_owner != 0ffffffffh)
            push    ds
            mov     ds,cs:data_segment
            mov     ds:current_font,offset font_16x16_name
            pop     ds
        .ENDIF
        retf
    VID_g_set_font_16x16    ENDP




    invVID_entering_graphics_mode       PROC
    ; This function is used to save the current text mode (if we're in text mode)
    ;
    ; Upon entry:   Nothing
    ;
    ; Upon exit:    If we're currently in a text mode then _sVGA's base is changed to _sVGA_BACKUP_base
    ;               Otherwise, nothing
    ;
        .IF (cs:current_mode == 1)
          ; We're currently in a text mode, we have to update our backup information
          ; This is done so writes to the VGA text screen are still valid even though the graphics screen is being displayed
            pushad
            pushfd
            push    ds
            push    es

          ; Copy the current screen to the save buffer
            mov     ax,_sVGA
            mov     ds,ax
            mov     ax,_sVGA_BACKUP
            mov     es,ax
            xor     esi,esi
            xor     edi,edi
            mov     ecx,32768 / 4
            cld
            rep     movsd

          ; Change the base
            mov     eax,'altr'
            mov     ebx,'gdt '
            mov     edx,_sVGA / 8
            mov     esi,_sVGA_BACKUP_base
            mov     edi,_sVGA_BACKUP_limit
            call    fword ptr cs:_EXODUS_requestor

          ; Raise the flag
            mov     ds,cs:data_segment
            mov     ds:vga_backup_mode,1

            pop     es
            pop     ds
            popfd
            popad
        .ENDIF
        ret
    invVID_entering_graphics_mode       ENDP




    invVID_restore_text_mode        PROC
    ; This function is used to save the current text mode (if we're in text mode)
    ;
    ; Upon entry:   Nothing
    ;
    ; Upon exit:    If we're currently in a text mode then _sVGA's base is changed to _sVGA_BACKUP_base
    ;               Otherwise, nothing
    ;
        .IF (cs:vga_backup_mode != 0)
          ; We're currently in a backup mode
            pushad
            pushfd
            push    ds
            push    es

          ; Change the base
            mov     eax,'altr'
            mov     ebx,'gdt '
            mov     edx,_sVGA / 8
            mov     esi,_sVGA_base
            mov     edi,_sVGA_limit
            call    fword ptr cs:_EXODUS_requestor

          ; Copy the save buffer to the current screen
            mov     ax,_sVGA_BACKUP
            mov     ds,ax
            mov     ax,_sVGA
            mov     es,ax
            xor     esi,esi
            xor     edi,edi
            mov     ecx,32768 / 4
            cld
            rep     movsd

          ; Lower the flag
            mov     ds,cs:data_segment
            mov     ds:vga_backup_mode,0

            pop     es
            pop     ds
            popfd
            popad
        .ENDIF
        ret
    invVID_restore_text_mode        ENDP




    invVID_write_registers      PROC
    ; This routine is used to write values specific to a video mode to the vga controller
    ;
    ; Upon entry:   Stack is arranged as outlined below
    ;
    ; Upon exit:    Values are written
    ;
      ; [esp+28] - MISC structure
      ; [esp+24] - SEQ structure
      ; [esp+20] - CRTC structure
      ; [esp+16] - GRAPH structure
      ; [esp+12] - ATTRIB structure
      ; [esp+08] - RAMDAC structure
      ; [esp+04] - RAMDAC count
      ; [esp+00] - eip

      ;; MISC registers
        mov     esi,dword ptr ss:[esp+28]
        xor     ebx,ebx
        .WHILE (word ptr cs:[esi+ebx*4] != 0ffffh)
            mov     dx,word ptr cs:[esi+ebx*4]                      ; port
            mov     ax,word ptr cs:[esi+ebx*4+2]                    ; data
            out     dx,al
            call    invWait_a_bit

            inc     ebx
        .ENDW

      ;; CRTC registers
        mov     esi,dword ptr ss:[esp+20]
        xor     ebx,ebx
        mov     ecx,32
        .REPEAT
            mov     edx,CRTC_INDEX
            mov     al,bl
            out     dx,al
            call    invWait_a_bit

            mov     edx,CRTC_DATA
            mov     al,byte ptr cs:[esi]
            out     dx,al
            call    invWait_a_bit

            inc     esi
            inc     ebx
        .UNTILCXZ

      ;; SEQ registers
        mov     esi,dword ptr ss:[esp+24]
        xor     ebx,ebx
        mov     ecx,5
        .REPEAT
            mov     edx,SEQ_INDEX
            mov     al,bl
            out     dx,al
            call    invWait_a_bit

            mov     edx,SEQ_DATA
            mov     al,byte ptr cs:[esi]
            out     dx,al
            call    invWait_a_bit

            inc     esi
            inc     ebx
        .UNTILCXZ

      ;; GRAPH registers
        mov     esi,dword ptr ss:[esp+16]
        xor     ebx,ebx
        mov     ecx,9
        .REPEAT
            mov     edx,GRAPH_INDEX
            mov     al,bl
            out     dx,al
            call    invWait_a_bit

            mov     edx,GRAPH_DATA
            mov     al,byte ptr cs:[esi]
            out     dx,al
            call    invWait_a_bit

            inc     esi
            inc     ebx
        .UNTILCXZ

      ;; ATTRIB registers
        mov     esi,dword ptr ss:[esp+12]
        xor     ebx,ebx
        mov     ecx,21
        .REPEAT
            mov     edx,STATUS_REG1                                 ; clear the flip-flop
            in      al,dx
            call    invWait_a_bit

            mov     edx,ATTRIB_INDEX
            mov     al,bl
            out     dx,al
            call    invWait_a_bit

            mov     edx,ATTRIB_DATA_WRITE
            mov     al,byte ptr cs:[esi]
            out     dx,al
            call    invWait_a_bit

            inc     esi
            inc     ebx
        .UNTILCXZ
        mov     edx,STATUS_REG1                                     ; clear the flip-flop
        in      al,dx
        call    invWait_a_bit

        mov     edx,ATTRIB_INDEX                                    ; enable palettes
        mov     al,20h
        out     dx,al
        call    invWait_a_bit

      ;; RAMDAC registers
        mov     ecx,dword ptr ss:[esp+04]
        mov     esi,dword ptr ss:[esp+08]
        mov     edx,RAMDAC_PIXEL_MASK
        mov     al,0ffh
        out     dx,al
        call    invWait_a_bit
        .REPEAT
            mov     edx,RAMDAC_INDEX_WRITE
            mov     al,byte ptr cs:[esi]
            inc     esi
            out     dx,al
            call    invWait_a_bit

            mov     edx,RAMDAC_DATA
            mov     al,byte ptr cs:[esi]                            ; red
            inc     esi
            out     dx,al
            call    invWait_a_bit

            mov     al,byte ptr cs:[esi]                            ; green
            inc     esi
            out     dx,al
            call    invWait_a_bit

            mov     al,byte ptr cs:[esi]                            ; blue
            inc     esi
            out     dx,al
            call    invWait_a_bit
        .UNTILCXZ

        ret 28
    invVID_write_registers      ENDP




    invVID_VGA_set_interactive_palette      PROC
    ; This routine is used to set a single palette after it has interactively been set
    ;
    ; Upon entry:   ds:[ebx] - far ptr to <palette register|R|G|B>
    ;
    ; Upon exit:    The particular palette register is set
    ;
        push    edx
        push    eax
        pushfd
        cli
        mov     edx,RAMDAC_PIXEL_MASK
        mov     al,0ffh
        out     dx,al
        mov     edx,RAMDAC_INDEX_WRITE
        mov     al,byte ptr ds:[ebx]
        out     dx,al
        jmp     $+2

        .IF (cs:bits_per_pixel == 8)
            mov     edx,RAMDAC_DATA
            mov     al,byte ptr ds:[ebx+1]                          ; red
            shr     al,2                                            ; divide by 4 (only 64 values per register in 8bpp mode)
            out     dx,al
            jmp     $+2

            mov     al,byte ptr ds:[ebx+2]                          ; green
            shr     al,2
            out     dx,al
            jmp     $+2

            mov     al,byte ptr ds:[ebx+3]                          ; blue
            shr     al,2
            out     dx,al
            jmp     $+2
        .ELSE
            mov     edx,RAMDAC_DATA
            mov     al,byte ptr ds:[ebx+1]                          ; red
            out     dx,al
            jmp     $+2

            mov     al,byte ptr ds:[ebx+2]                          ; green
            out     dx,al
            jmp     $+2

            mov     al,byte ptr ds:[ebx+3]                          ; blue
            out     dx,al
            jmp     $+2
        .ENDIF
        popfd
        pop     eax
        pop     edx
        ret
    invVID_VGA_set_interactive_palette      ENDP




    invVID_VGA_initialize_interactive_palette       PROC
    ; This routine is used to reset all interactive palette colors to 0
    ; It's used when a full redraw is issued (it gets rid of colors no-longer used)
    ;
    ; Upon entry:   Nothing
    ;
    ; Upon exit:    The palette is reset
    ;
        push    ds
        pushfd
        pushad

        mov     esi,offset ramdac_256_standard_start
        mov     edi,offset exodus_interactive_256_start
        mov     ecx,16
        cld
        rep     movsd
        mov     eax,00000010h
        mov     ecx,256 - 16
      @@:
        stosd
        inc     eax
        dec     ecx
        jnz     @B

        popad
        popfd
        pop     ds
        ret
    invVID_VGA_initialize_interactive_palette       ENDP




    invVID_vga_set_font     PROC
    ; This routine is used to set the font
    ;
    ; Upon entry:   The stack is arranged as below
    ;
    ; Upon exit:    The font is setup
    ;
      ; [ebp+12] - Bytes per character (maximum of 32)
      ; [ebp+08] - Offset to font table
      ; [ebp+04] - eip
      ; [ebp+00] - ebp
        enter   0,0
        pushad
        pushfd
        push    es

        call    invVID_vga_prepare_for_font
      ;-----------
        mov     esi,dword ptr ss:[ebp+08]
        mov     ebx,dword ptr ss:[ebp+12]
        mov     ax,_sGRAPHICS
        mov     es,eax
        xor     edi,edi
        mov     eax,32
        sub     eax,ebx
      ; Right now, es:[edi] - far ptr to start of video memory
      ;            ds:[esi] - far ptr to font table
      ;                edx - count
      ;                eax - extras bytes to add per character
        cld
      loop_top:
        mov     ecx,ebx
        rep     movsb
        add     edi,eax
        dec     dx
        jnz     loop_top
      ;-----------
        call    invVID_vga_reset_after_font

        pop     es
        popfd
        popad
        leave
        ret 8
    invVID_vga_set_font     ENDP




    invVID_vga_prepare_for_font     PROC
    ; This routine is used to prepare for the upcoming font setup
    ;
    ; Upon entry:   Nothing
    ;
    ; Upon exit:    The regs are stored to memory variables
    ;
        push    edx
        push    eax
        push    ds

        mov     ds,cs:data_segment
        mov     dx,SEQ_INDEX
        mov     ax,402h         ; Send 4 to index-2
        out     dx,ax

        mov     ax,704h         ; Send 7 to index-4
        out     dx,ax

        mov     dx,GRAPH_INDEX
        mov     ax,204h         ; Send 2 to index-4
        out     dx,ax

        mov     ax,5            ; Send 0 to index-5
        out     dx,ax

        mov     ax,406h         ; Send 4 to index-6
        out     dx,ax

        pop     ds
        pop     eax
        pop     edx
        ret
    invVID_vga_prepare_for_font     ENDP




    invVID_vga_reset_after_font     PROC
    ; This routine is used to reset the regs after a font setup
    ;
    ; Upon entry:   Nothing
    ;
    ; Upon exit:    The regs are reset from memory variables
    ;
        push    edx
        push    eax
        push    ds

        mov     ds,cs:data_segment
        mov     dx,SEQ_INDEX
        mov     ax,302h
        out     dx,ax

        mov     ax,304h
        out     dx,ax

        mov     dx,GRAPH_INDEX
        mov     ax,4
        out     dx,ax

        mov     ax,1005h
        out     dx,ax

        mov     ax,0e06h
        out     dx,ax

        pop     ds
        pop     eax
        pop     edx
        ret
    invVID_vga_reset_after_font     ENDP




    VID_draw_exodus_boot_screen         PROC
    ; This routine draws the main boot screen on the vga
    ; Note, this algorithm uses the lower 20h palette registers for the boot screen.  It sets the palette registers from 21h
    ;       to 2fh to the standard 0-fh colors.
    ;
    ; Upon entry:   It is known the video mode is 320x200
    ;               ds:[esi] - far ptr to boot screen
    ;                    ecx - length of boot screen
    ;
    ; Upon exit:    The screen is updated
    ;
      ; Note, EXODUS_requestor is the only algorithm that calls this function.  It saves/restore all registers.
        mov     edx,ecx
        mov     fs,cs:data_segment
        mov     edi,esi
      ; The palette is first (this boot screen must use less than or equal to the first 1fh color registers)
        xor     eax,eax                                             ; The first byte says how many palette entries there are
        inc     esi
        mov     ecx,1
        push    edx
        .WHILE (al < byte ptr ds:[edi])
            mov     ebx,eax

            mov     edx,RAMDAC_INDEX_WRITE
            out     dx,al
            call    invWait_a_bit
            mov     edx,RAMDAC_DATA
            mov     al,byte ptr ds:[esi]                            ; Red
            out     dx,al
            call    invWait_a_bit
            mov     al,byte ptr ds:[esi+1]                          ; Green
            out     dx,al
            call    invWait_a_bit
            mov     al,byte ptr ds:[esi+2]                          ; Blue
            out     dx,al
            add     esi,3

            mov     eax,ebx
            add     ecx,3
            inc     eax
        .ENDW
        pop     edx
        sub     edx,ecx

      ; Then the physical boot screen
        mov     eax,_sGRAPHICS
        mov     es,eax
        xor     edi,edi
        .WHILE (edx > 0)
            sub     edx,2
            movzx   ecx,byte ptr ds:[esi]
            mov     al,byte ptr ds:[esi+1]
            rep     stosb
            add     esi,2
        .ENDW

      ; Now, set the fixed palette (for any subsequent 18x16 logos that will be displayed)
        mov     fs:logo_x,0
        mov     fs:logo_y,0
        mov     esi,offset ramdac_256_standard_start
        mov     ecx,20h
        .WHILE (ecx < 30h)
            mov     al,cl
            mov     edx,RAMDAC_INDEX_WRITE
            out     dx,al
            call    invWait_a_bit

            mov     edx,RAMDAC_DATA
            mov     al,byte ptr fs:[esi+1]                          ; red
            out     dx,al
            call    invWait_a_bit

            mov     al,byte ptr fs:[esi+2]                          ; green
            out     dx,al
            call    invWait_a_bit

            mov     al,byte ptr fs:[esi+3]                          ; blue
            out     dx,al
            call    invWait_a_bit

            add     esi,4
            inc     cx
        .ENDW
        retf
    VID_draw_exodus_boot_screen         ENDP




    invWait_a_bit   PROC
        push    edx
        pushf

        mov     edx,0fh
      @@:                                                           ; compensate for a hardware limitation somewhere
        sub     edx,1
        jnc     @B

        popf
        pop     edx
        ret
    invWait_a_bit   ENDP




    VID_g_claim_ownership       PROC
    ; This routine is called when ownership of the VID_g_routines() algorithm is desired
    ;
    ; Upon entry:   The stack has CS on it, that is the program desiring access
    ;
    ; Upon exit:    carry? - SET if error, CLEAR if ok
    ;
        .IF (cs:VID_g_owner == 0ffffffffh)
          ; It's not currently owned
          ; [ebp+08] - cs
          ; [ebp+04] - eip
          ; [ebp+00] - ebp
            enter   0,0
            push    ds
            push    eax

            mov     ds,cs:data_segment
            mov     eax,dword ptr ss:[ebp+08]
            mov     ds:VID_g_owner,eax

            pop     eax
            pop     ds
            leave
            clc
        .ELSE
            stc
        .ENDIF
        retf
    VID_g_claim_ownership       ENDP




    VID_g_release_ownership     PROC
    ; This routine is called when ownership of the VID_g_routines() algorithm is desired
    ;
    ; Upon entry:   The stack has CS on it, that is the program desiring access
    ;
    ; Upon exit:    carry? - SET if error, CLEAR if ok
    ;
      ; [ebp+08] - cs
      ; [ebp+04] - eip
      ; [ebp+00] - ebp
        enter   0,0
        push    eax

        mov     eax,dword ptr ss:[ebp+08]
        .IF (cs:VID_g_owner == eax)
          ; This is actually the owner, and they're releasing it
            push    ds
            mov     ds,cs:data_segment
            mov     ds:VID_g_owner,0ffffffffh
            pop     ds
            clc
        .ELSE
            stc
        .ENDIF

        pop     eax
        leave
        retf
    VID_g_release_ownership     ENDP
