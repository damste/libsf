; mono.asp
;
; Exodus VGA Driver MONO algorithms
;




    VID_position_cursor_mono    PROC
        callf   VID_set_registers_for_mono
        call    _position_cursor
        retf
    VID_position_cursor_mono    ENDP




    VID_get_cursor_mono     PROC
        push    ebx
        push    eax

        xor     edx,edx
        xor     eax,eax
        mov     ax,cs:offset_mono
        mov     ebx,160
        div     ebx
        mov     dh,al
        shr     dl,1

        pop     eax
        pop     ebx
        retf
    VID_get_cursor_mono     ENDP




    VID_set_registers_for_mono  PROC
        push    ds
        mov     ds,cs:data_segment

        mov     ds:reg1,MONO_CRTC_INDEX
        mov     ds:reg2,MONO_CRTC_DATA
        mov     ds:storage_ptr,offset offset_mono

        pop     ds
        retf
    VID_set_registers_for_mono  ENDP




    VID_display_string_mono   PROC
    ; ds:[si] - far pointer to null-terminated string
    ; offset_mono- pointer into the screen where to start writing
        pushad
        push    es
        push    gs

        .IF (cs:mono_video == MONO_GRAPH)
            call    invVID_g_display_string_mono
        .ELSE
            mov     es,cs:data_segment
            mov     di,_sMONO
            mov     gs,di
            mov     di,es:offset_mono                               ; Offset we're writing to
            mov     ah,es:attribute_mono                            ; Color we're using
            .IF (es:bootup == 1)
              ; During bootup, strings can be terminated with 255 as well as 0
                .WHILE (byte ptr ds:[esi] != 0 && byte ptr ds:[esi] != 255)     ; Loop until one of two chars is found
                    lodsb
                    mov     byte ptr gs:[edi],al                    ; Write character
                    inc     di
                    mov     byte ptr gs:[edi],ah                    ; Write color
                    inc     di
                .ENDW
            .ELSE
                .WHILE (byte ptr ds:[esi] != 0)                     ; Loop until the NULL terminated string is found
                    lodsb
                    mov     byte ptr gs:[edi],al                    ; Write character
                    inc     edi
                    mov     byte ptr gs:[edi],ah                    ; Write color
                    inc     edi
                .ENDW
            .ENDIF
            mov     ebx,edi                                         ; Adjust the cursor position
            shr     ebx,1
            callf   VID_set_registers_for_mono
            call    _position_cursor_raw_data
            mov     es:offset_mono,di                               ; Store our new offset
        .ENDIF

        pop     gs
        pop     es
        popad
        retf
    VID_display_string_mono   ENDP




    VID_display_string_ecx_mono   PROC
    ; ds:[si] - far pointer to null-terminated string
    ;     ecx - number of bytes to print
    ; offset_mono- pointer into the screen where to start writing
        pushad
        push    es
        push    gs

        mov     es,cs:data_segment
        mov     di,_sMONO
        mov     gs,di
        mov     di,es:offset_mono                                   ; Offset we're writing to
        mov     ah,es:attribute_mono                                ; Color we're using
        .REPEAT
            lodsb
            mov     byte ptr gs:[edi],al                            ; Write character
            inc     edi
            mov     byte ptr gs:[edi],ah                            ; Write color
            inc     edi
        .UNTILCXZ
        mov     ebx,edi                                             ; Adjust the cursor position
        shr     ebx,1
        callf   VID_set_registers_for_mono
        call    _position_cursor_raw_data
        mov     es:offset_mono,di                                   ; Store our new offset

        pop     gs
        pop     es
        popad
        retf
    VID_display_string_ecx_mono   ENDP




    VID_display_hex_string_ecx_mono     PROC
    ; ds:[esi] - far pointer to null-terminated string
    ;     ecx - number of hexidecimal digits to display
    ; offset_mono- pointer into the screen where to start writing
        pushad
        push    es
        push    gs

        mov     es,cs:data_segment
        mov     di,_sMONO
        mov     gs,di
        mov     di,es:offset_mono                                   ; Offset we're writing to
        mov     ah,es:attribute_mono                                ; Color we're using
        .REPEAT
            lodsb
            mov     dl,al
            call    hex_adjust_al_dl
            mov     byte ptr gs:[edi],32                            ; Write a space before hexidecimal values
            inc     di
            mov     byte ptr gs:[edi],ah                            ; Write color
            inc     di
            mov     byte ptr gs:[edi],dl                            ; Write left 1/2 of hexidecimal values character
            inc     di
            mov     byte ptr gs:[edi],ah                            ; Write color
            inc     di
            mov     byte ptr gs:[edi],al                            ; Write right 1/2 of hexidecimal values character
            inc     di
            mov     byte ptr gs:[edi],ah                            ; Write color
            inc     di
            mov     byte ptr gs:[edi],32                            ; Write a space after hexidecimal value
            inc     di
            mov     byte ptr gs:[edi],ah                            ; Write color
            inc     di
        .UNTILCXZ
        mov     ebx,edi                                             ; Adjust the cursor position
        shr     ebx,1
        callf   VID_set_registers_for_mono
        call    _position_cursor_raw_data
        mov     es:offset_mono,di                                   ; Store our new offset

        pop     gs
        pop     es
        popad
        retf
    VID_display_hex_string_ecx_mono     ENDP




    VID_display_hex_string_ecx_ro_mono      PROC
        pushfd
        pushad

        add     esi,ecx
        dec     esi                                                 ; Change base-1 to base-0
        std
        callf   VID_display_hex_string_ecx_mono

        popad
        popfd
        retf
    VID_display_hex_string_ecx_ro_mono      ENDP




    VID_display_string_nr_mono      PROC
        pushad
        push    es

        .IF (cs:mono_video == MONO_TEXT)
            callf   VID_display_string_mono
            callf   VID_move_to_next_line_mono
        .ELSE
            call    invVID_g_display_string_mono
        .ENDIF

        pop     es
        popad
        retf
    VID_display_string_nr_mono      ENDP




    VID_display_string_ecx_nr_mono      PROC
        pushad
        push    es

        callf   VID_display_string_ecx_mono
        callf   VID_move_to_next_line_mono

        pop     es
        popad
        retf
    VID_display_string_ecx_nr_mono      ENDP




    VID_display_hex_string_ecx_nr_mono      PROC
        pushad
        push    es

        callf   VID_display_hex_string_ecx_mono
        callf   VID_move_to_next_line_mono

        pop     es
        popad
        retf
    VID_display_hex_string_ecx_nr_mono      ENDP




    VID_move_to_next_line_mono      PROC
        pushad
        push    es
        push    gs

        mov     es,cs:data_segment
        mov     ax,_sMONO
        mov     gs,ax
        mov     ax,es:offset_mono                                   ; Move to the next row
        xor     dx,dx                                               ; Divide offset_mono by 80*2 to get # of lines
        mov     bx,80*2
        div     bx
        inc     ax                                                  ; Ignore the remainder and move down to the next line
        mul     bx
        .IF (ax > 24*(80*2))                                        ; Are we past the bottom of the screen?
            .IF (es:freeze_mono == 0)
                xor     di,di                                       ; Yes, scroll everything up
                mov     si,80*2
                mov     cx,24*(80*2)                                ; 24 lines are scrolling
            .ELSE
                mov     al,es:freeze_mono
                and     eax,0ffh
                push    eax
                mov     ebx,80*2
                mul     ebx
                mov     di,ax
                add     ax,80*2
                mov     si,ax
                pop     eax
                mov     ecx,24
                sub     ecx,eax
                mov     eax,ecx
                mul     ebx
                mov     ecx,eax
            .ENDIF
            .REPEAT
                mov     al,byte ptr gs:[esi]                        ; Load a byte
                mov     byte ptr gs:[edi],al                        ; Store a byte
                inc     esi
                inc     edi
            .UNTILCXZ
            mov     es:offset_mono,di                               ; This is our new offset (the left-most char on bottom line)
            mov     cx,80                                           ; Clear off the last 80 characters (the new blank bottom line)
            mov     ah,es:attribute_mono
            .REPEAT
                mov     byte ptr gs:[edi]," "
                inc     edi
                mov     byte ptr gs:[edi],ah
                inc     edi
            .UNTILCXZ
        .ELSE
            mov     es:offset_mono,ax
        .ENDIF
        mov     bx,es:offset_mono
        shr     bx,1
        call    _position_cursor_raw_data

        pop     gs
        pop     es
        popad
        retf
    VID_move_to_next_line_mono      ENDP
    VID_display_radix_in_edx_mono   PROC
        pushad
        push    ds
        sub     esp,16                                              ; Assume a maximum length of 12 chars (4 extra for boundry)
        mov     ebp,esp

        call    _generate_radix_string
        .IF (cs:mono_video == MONO_TEXT)
            callf   VID_display_string_mono
        .ELSE
            call    invVID_g_display_string_mono
        .ENDIF

        add     esp,16
        pop     ds
        popad
        retf
    VID_display_radix_in_edx_mono   ENDP




    invVID_g_display_string_mono    PROC
    ; This routine is called from this driver when the monochrome screen is in graphics mode
    ;
    ; Upon entry:   ds:[esi] - far ptr to null-terminated string
    ;
    ; Upon exit:    The text is displayed
    ;
        callf   VID_get_cursor_mono
        mov     cl,dh
        and     ecx,04fh
        and     edx,01fh
        shl     edx,3                                               ; Multiply each coordinate by 3
        shl     ecx,3

        push    edx
        push    ecx
        push    esi
        callf   VID_g_mono_display_text

        ret
    invVID_g_display_string_mono    ENDP




    VID_display_radix_in_edx_nr_mono    PROC
        pushad
        push    ds
        sub     esp,16                                              ; Assume a maximum length of 12 characters
        mov     ebp,esp

        call    _generate_radix_string
        callf   VID_display_string_nr_mono

        add     esp,16
        pop     ds
        popad
        retf
    VID_display_radix_in_edx_nr_mono    ENDP




    VID_g_display_radix_in_edx_mono     PROC
    ; This routine is used to display a specific number of characters derived from the value of edx based on the base in ebx
    ; at a particular x/y coordinate on the monochrome graphics screen
    ;
    ; Upon entry:   edx - value to convert
    ;               ebx - base to convert in
    ;               ecx - number of digits to convert (filled with 0s if value is less than this many digits)
    ;               Other parameters are arranged on the stack as below
    ;
    ; Upon exit:
    ;
        .IF (cs:VID_g_owner != 0ffffffffh)
            pushad
            push    ds
            sub     esp,44                                          ; Assume a maximum length of 40 characters
            mov     ebp,esp
          ; [ebp+92] - param, x coord
          ; [ebp+88] - param, y coord
          ; [ebp+84] - cs
          ; [ebp+80] - eip
          ; [ebp+76] - eax
          ; [ebp+72] - ecx
          ; [ebp+68] - edx
          ; [ebp+64] - ebx
          ; [ebp+60] - esp
          ; [ebp+56] - ebp
          ; [ebp+52] - esi
          ; [ebp+48] - edi
          ; [ebp+44] - ds

            call    _generate_radix_string_ecx
          ; Right now, ds:[esi] - far ptr to string to display
            push    dword ptr ss:[ebp+92]
            push    dword ptr ss:[ebp+88]
            push    esi
            callf   VID_g_mono_display_text

            add     esp,44
            pop     ds
            popad
        .ENDIF
        retf 8
    VID_g_display_radix_in_edx_mono     ENDP




    ; These routines takes the value in dx, converts it to their radix equivelent (value in bx) and displays it on the VGA/MONO
    ; at the current screen coordinates.  Cursor position is updated.
    VID_display_decimal_in_edx_vga      PROC
        push    ebx
        mov     ebx,10
        callf   VID_display_radix_in_edx_vga
        pop     ebx
        retf
    VID_display_decimal_in_edx_vga      ENDP




    VID_display_decimal_in_edx_mono     PROC
        push    ebx
        mov     ebx,10
        callf   VID_display_radix_in_edx_mono
        pop     ebx
        retf
    VID_display_decimal_in_edx_mono     ENDP




    VID_display_decimal_in_edx_nr_vga   PROC
        push    ebx
        mov     ebx,10
        callf   VID_display_radix_in_edx_nr_vga
        pop     ebx
        retf
    VID_display_decimal_in_edx_nr_vga   ENDP




    VID_display_decimal_in_edx_nr_mono      PROC
        push    ebx
        mov     ebx,10
        callf   VID_display_radix_in_edx_nr_mono
        pop     ebx
        retf
    VID_display_decimal_in_edx_nr_mono      ENDP




    VID_display_hexidecimal_in_edx_vga      PROC
        push    ebx
        mov     ebx,16
        callf   VID_display_radix_in_edx_vga
        pop     ebx
        retf
    VID_display_hexidecimal_in_edx_vga      ENDP




    VID_display_hexidecimal_in_edx_mono     PROC
        push    ebx
        mov     ebx,16
        callf   VID_display_radix_in_edx_mono
        pop     ebx
        retf
    VID_display_hexidecimal_in_edx_mono     ENDP




    VID_display_hexidecimal_in_edx_nr_vga     PROC
        push    ebx
        mov     ebx,16
        callf   VID_display_radix_in_edx_nr_vga
        pop     ebx
        retf
    VID_display_hexidecimal_in_edx_nr_vga     ENDP




    VID_display_hexidecimal_in_edx_nr_mono    PROC
        push    ebx
        mov     ebx,16
        callf   VID_display_radix_in_edx_nr_mono
        pop     ebx
        retf
    VID_display_hexidecimal_in_edx_nr_mono    ENDP




    VID_set_attribute_mono  PROC
        push    ds

        mov     ds,cs:data_segment
        mov     ds:attribute_mono,al

        pop     ds
        retf
    VID_set_attribute_mono  ENDP




    VID_clear_screen_mono   PROC
    ; This routine clears the vga screen buffer
        pushad
        push    es
        push    gs

        mov     es,cs:data_segment
        mov     di,_sMONO
        mov     gs,di
        mov     es:offset_mono,0
        xor     edi,edi
        mov     ecx,80 * 25
        mov     al,32
        mov     ah,es:attribute_mono
        .REPEAT
            mov     word ptr gs:[edi],ax
            add     edi,2
        .UNTILCXZ
        xor     edx,edx
        callf   VID_position_cursor_mono

        pop     gs
        pop     es
        popad
        retf
    VID_clear_screen_mono   ENDP




    VID_freeze_frame_mono   PROC    NEAR
    ; This routine is used to indicate how much of the top portion of the screen should be frozen
    ;
    ; Upon entry:   al - lines to freeze (must be 0-24)
    ;
    ; Upon exit:    if al is valid, freeze_mono is updated
    ;
        push    ds

        .IF (al <= 24)
            mov     ds,cs:data_segment
            mov     ds:freeze_mono,al
        .ENDIF

        pop     ds
        retf
    VID_freeze_frame_mono   ENDP




    VID_g_mono_display_text     PROC
    ; This routine provides a simplied input for the users to write text to the screen
    ;
    ; Upon entry:   The stack is arranged as displayed below
    ;
    ; Upon exit:    The text is displayed
    ;               ecx - how many characters were processed including the NULL
    ;
        .IF (cs:VID_g_owner != 0ffffffffh)
            push    edx
            enter   0,0
          ; [esp+24] - param, dword, horizontal
          ; [esp+20] - param, dword, vertical
          ; [esp+16] - param, dword, offset to text
          ; [esp+12] - cs
          ; [esp+08] - eip
          ; [esp+04] - edx
          ; [esp+00] - ebp

            mov     edx,cs:mono_write_mode
            push    edx
            push    dword ptr ss:[ebp+24]
            push    dword ptr ss:[ebp+20]
            mov     edx,cs:mono_display_mode
            push    edx
            push    dword ptr ss:[ebp+16]
            callf   VID_g_mono_display_text_mode

            leave
            pop     edx
        .ENDIF
        retf    12
    VID_g_mono_display_text     ENDP




    VID_g_mono_display_text_mode    PROC
    ; This routine draws information on the screen
    ;
    ; Upon entry:   Parameters are passed on the stack as below
    ;               ds - data segment for the expression to be displayed
    ;
    ; Upon exit:    The text is displayed
    ;               ecx - how many characters were processed including the NULL
    ;
        .IF (cs:VID_g_owner != 0ffffffffh)
          ; [ebp+32] - param, dword, write operation (0-overlay, 1-or, 2-and, 3-xor)
          ; [ebp+28] - param, dword, horizontal
          ; [ebp+24] - param, dword, vertical
          ; [ebp+20] - param, dword, display mode (0-normal, 1-reverse)
          ; [ebp+16] - param, dword, offset to text to the display
          ; [ebp+12] - cs
          ; [ebp+08] - eip
          ; [ebp+04] - es
          ; [ebp+00] - ebp
            push    es
            enter   92,0
          ; [ebp-04] - dword, font base for current font
          ; [ebp-05] -  byte, Temporary reverse holder (used when cask characters are found)
          ; [ebp-06] -  byte, 0-No scatter, 1-scatter
          ; [ebp-07] -  byte, Working mask (for SCATTER operations)
          ; [ebp-08] -  byte, number of bits to rotate each character right
          ; [ebp-12] - dword, baseline bitmap for this character (stays the same, based on the font)
          ; [ebp-16] - dword, working bitmap for this character (changes each iteration)
          ; [ebp-20] - dword, Count, number of characters displayed
          ; [ebp-24] - dword, starting address
          ; [ebp-28] - dword, incremental values after each line of data
          ;  .                .
          ;  .                . (up to 16 lines)
          ;  .                .
          ; [ebp-92] - dword, incremental values after each line of data
            push    eax
            push    ebx
            push    edx
            push    esi
            push    edi
            .IF (dword ptr ss:[ebp+20] != 0)
                mov     dword ptr ss:[ebp+20],0ffffffffh
            .ENDIF
          ;; Make sure the text coordinates are not off the screen
            .IF (dword ptr ss:[ebp+28] > 718)
                mov     dword ptr ss:[ebp+28],718
            .ENDIF
            .IF (dword ptr ss:[ebp+24] > 346)
                mov     dword ptr ss:[ebp+24],346
            .ENDIF

            mov     byte ptr ss:[ebp-06],0
            mov     byte ptr ss:[ebp-07],10101010b

          ;; Calculate the starting offset into video memory
          ; do vertical
            mov     eax,dword ptr ss:[ebp+24]
            mov     ebx,4
            xor     edx,edx
            div     ebx
            .IF (dl == 00b)
              ; They're exactly on a boundary
                xor     ecx,ecx
            .ELSEIF (dl == 01b)
              ; They're on the first boundary
                mov     ecx,2000h
            .ELSEIF (dl == 10b)
              ; They're on the second boundary
                mov     ecx,4000h
            .ELSE
              ; They're on the third boundary
                mov     ecx,6000h
            .ENDIF
          ; Continue on vertical (to get the correct offset into the screen)
            mov     ebx,90
            mul     ebx
            add     eax,ecx
            mov     dword ptr ss:[ebp-24],eax

          ; Right now, eax contains the starting offset into video memory (not including the X coordinate)
            mov     eax,dword ptr ss:[ebp+28]
            mov     ebx,8
            xor     edx,edx
            div     ebx
          ; Right now, eax - offset across the line for the first character
          ;            edx - Number of bits to use for the first character
            add     dword ptr ss:[ebp-24],eax
            .IF (edx == 0)
              ; They're on a solid boundary (no bit shifting)
                mov     byte ptr ss:[ebp-08],0
            .ELSE
              ; They're going across multiple characters
                mov     byte ptr ss:[ebp-08],dl
            .ENDIF
          ; Right now, ss:[ebp-24] - starting offset into video memory
          ;            ss:[ebp-08] - number of bits to shift each character right
          ; [ebp+28] - dword, --Nuserved        ; These are freed up because they do not need to be used right now
          ; [ebp+24] - dword, --Nuserved

          ; Now, build the array indicating the offset increments per iteration
          ; We use edx as our source value, we calculate the offsets each time
            mov     ebx,-28
            mov     edi,cs:current_font
            mov     edx,dword ptr cs:[edi+8]
            mov     dword ptr ss:[ebp-04],edx                       ; Base font offset
            mov     ecx,dword ptr cs:[edi+4]
            .IF (ecx > 16)
              ; Just to make sure our algorithm doesn't fail
                mov     ecx,16
            .ENDIF
            mov     edx,dword ptr ss:[ebp-24]                       ; prime our starting address
            mov     eax,edx                                         ; and copy to our "hold" value
            and     eax,1fffh
            .REPEAT
                push    ecx
                .IF (edx < 6000h)
                    add     edx,2000h
                    mov     ecx,2000h
                .ELSE
                  ; We can't just block-increment anymore
                  ; We now have to go back to our original value and add 90 to it
                    add     eax,90
                    mov     edx,eax
                    mov     ecx,0ffffffffh-6000h + 90 + 1
                .ENDIF
                mov     dword ptr ss:[ebp+ebx],ecx
                sub     ebx,4
                pop     ecx
            .UNTILCXZ
            mov     dword ptr ss:[ebp+ebx],0ffffffffh
          ; Right now, every value is setup for our write operation.
          ; All we have to do to output our text is get the pointer to the appropriate character bitmap,
          ; then start writing bytes at a time (accounting, of course, for the bit shifting and write masks)

            mov     esi,dword ptr ss:[ebp+16]                       ; Source
          ;
          ; [ebp+28] - dword, bits wide for each character
          ; [ebp+24] - dword, maximum offset to achieve (before text is ignored because it would go off the right side of the screen)
          ; [ebp+16] - dword, multiplication factor for each character
            mov     eax,dword ptr cs:[edi]
            mov     dword ptr ss:[ebp+28],eax                       ; bits wide
            mov     ecx,eax
            xor     edx,edx
            .REPEAT
                stc
                rcl     edx,1
            .UNTILCXZ
            mov     cl,byte ptr ss:[ebp-08]
          ; Adjust for multi-character fonts
            .IF (dword ptr ss:[ebp+28] > 8)
                push    eax
                mov     eax,dword ptr ss:[ebp+28]
                sub     eax,8
                add     cl,al
                add     byte ptr ss:[ebp-08],al
                pop     eax
            .ENDIF
            ror     edx,cl

          ; Right now, edx is a bitmap of this character's width
            mov     dword ptr ss:[ebp-12],edx                       ; base bitmap
            mov     dword ptr ss:[ebp-16],edx                       ; working bitmap
            shr     eax,3                                           ; Divide by 8
            mov     ebx,dword ptr cs:[edi+4]                        ; bytes high
            mul     ebx
            mov     dword ptr ss:[ebp+16],eax                       ; Multiplication factor

          ;; Start drawing the characters
            mov     ax,_sMONO
            mov     es,ax
            mov     edi,dword ptr ss:[ebp-24]                       ; Destination starting address
            mov     dword ptr ss:[ebp-20],1                         ; Start the count at 1 (because the count includes the NULL)
            mov     byte ptr ss:[ebp-05],0                          ; Indicate originally that nothing was here
            .WHILE (byte ptr ds:[esi] != 0)
                inc     dword ptr ss:[ebp-20]                       ; increase the count
                xor     eax,eax
                mov     al,byte ptr ds:[esi]
                .IF (al == '�')
                    mov     dword ptr ss:[ebp+20],0ffffffffh
                .ELSEIF (al == '�')
                    mov     dword ptr ss:[ebp+20],0
                .ELSEIF (al == 168)
                  ; This character signifies that the one to its right is one to display regardless
                    inc     esi
                    mov     al,byte ptr ds:[esi]
                    jmp     display_this_one
                .ELSEIF (al >= 128 && al <= 151)
                    .IF ((al >= 128 && al <= 131) || (al >= 136 && al <= 139) || (al >= 144 && al <= 147))
                      ; It's a starting cask character
                        mov     byte ptr ss:[ebp-05],0ffh
                      ; Note that we don't turn the reverse on until after this character is displayed.  The code that turns
                      ; the reverse on is down below.  Look for ss:[ebp-05] below followed by a modification to ss:[ebp+20]
                    .ELSE
                      ; It's an ending cask character
                        not     dword ptr ss:[ebp+20]
                    .ENDIF
                    jmp     display_this_one
                .ELSEIF (al == '�')
                    mov     byte ptr ss:[ebp-06],1
                .ELSEIF (al == '�')
                    mov     byte ptr ss:[ebp-06],0
                .ELSE
                  display_this_one:
                    mov     ebx,dword ptr ss:[ebp+16]
                    mul     ebx
                    add     eax,dword ptr ss:[ebp-04]

                  ; Right now, cs:[eax] - far ptr to the base of this character's font
                    mov     ebx,-28                                 ; Starting offset into stack for add to offsets
                    push    edi
                    .WHILE (dword ptr ss:[ebp+ebx] != 0ffffffffh)
                        mov     edx,dword ptr ss:[ebp-12]           ; Update our working bitmap
                        mov     dword ptr ss:[ebp-16],edx

                        mov     edx,dword ptr ss:[ebp+28]
                        .IF (edx == 16)
                          ; We have to load 2 bytes
                            xor     edx,edx
                            mov     dx,word ptr cs:[eax]
                            add     eax,2
                            .IF (dword ptr ss:[ebp+20] != 0)
                                not     dx
                            .ENDIF
                        .ELSE
                          ; We load one byte
                            xor     edx,edx
                            mov     dl,byte ptr cs:[eax]
                            inc     eax
                            .IF (dword ptr ss:[ebp+20] != 0)
                                not     dl
                            .ENDIF
                        .ENDIF
                      ; Right now, dl or dx is this line of the character
                        mov     cl,byte ptr ss:[ebp-08]
                        ror     edx,cl
                        push    edi
                        .WHILE (dword ptr ss:[ebp-16] != 0)
                            mov     ecx,dword ptr ss:[ebp+32]
                            .IF (byte ptr ss:[ebp-06] != 0)
                                and     dl,byte ptr ss:[ebp-07]
                                not     byte ptr ss:[ebp-07]
                            .ENDIF
                            .IF (ecx == 0)
                              ; MOV the data here
                                push    edx
                                mov     edx,dword ptr ss:[ebp-16]
                                not     dl
                                and     byte ptr es:[edi],dl
                                pop     edx
                                or      byte ptr es:[edi],dl
                            .ELSEIF (ecx == 1)
                              ; OR the data here
                                or      byte ptr es:[edi],al
                            .ELSEIF (ecx == 2)
                              ; AND the data here
                                and     byte ptr es:[edi],al
                            .ELSEIF (ecx == 3)
                              ; XOR the data here
                                xor     byte ptr es:[edi],al
                            .ENDIF
                          ; Move to the next byte
                            inc     edi

                          ; Now, rotate the characters around for the next part
                            rol     edx,8
                            and     edx,0ffff00ffh                  ; Get rid of the byte we just drew
                            rol     dword ptr ss:[ebp-16],8
                            and     dword ptr ss:[ebp-16],0ffff00ffh
                        .ENDW
                        pop     edi
                        add     edi,dword ptr ss:[ebp+ebx]
                        sub     ebx,4
                    .ENDW
                    pop     edi
                    .IF (dword ptr ss:[ebp+28] == 16)
                        add     edi,2
                    .ELSE
                        inc     edi
                    .ENDIf
                .ENDIF

                .IF (byte ptr ss:[ebp-05] != 0)
                  ; We're currently working between two cask characters (this was added down here so the initial cask chracter won't
                  ; be reversed.  The closing one is covered by the code above.
                    not     dword ptr ss:[ebp+20]                   ; Make everything reversed between the cask characters
                    mov     byte ptr ss:[ebp-05],0
                .ENDIF
                inc     esi                                         ; Move to next source character
            .ENDW

            pop     edi
            pop     esi
            pop     edx
            pop     ebx
            pop     eax
            mov     ecx,dword ptr ss:[ebp-20]                       ; Get the count into ecx
            leave
            pop     es
        .ENDIF
        retf    20
    VID_g_mono_display_text_mode    ENDP




    VID_g_mono_mouse_pointer    PROC
    ; This routine draws the mouse pointer on the screen (or removes it from the screen)
    ;
    ; Upon entry:   Parameters are passed on the stack as below
    ;               The offset must be a 64 byte buffer
    ;
    ; Upon exit:    The mouse is either displayed or undisplayed
    ;
        .IF (cs:VID_g_owner != 0ffffffffh)
          ; [ebp+28] - dword, horizontal
          ; [ebp+24] - dword, vertical
          ; [ebp+20] - dword, display mode (0-hide, 1-show)
          ; [ebp+16] - dword, offset to store/retrieve mouse pointer data from, stored in ds:
          ; [ebp+12] - cs
          ; [ebp+08] - eip
          ; [ebp+04] - es
          ; [ebp+00] - ebp
            push    es
            enter   100,0
          ; [ebp-04] - dword, Holder for maximum byte on screen for each scanline of the mouse bitmap (so it doesn't go off the right)
          ; [ebp-05] -  byte, --Nuserved
          ; [ebp-06] -  byte, --Nuserved
          ; [ebp-07] -  byte, --Nuserved
          ; [ebp-08] -  byte, number of bits to rotate each character right
          ; [ebp-12] - dword, baseline bitmap for this character (stays the same, based on the font)
          ; [ebp-16] - dword, working bitmap for this character (changes each iteration)
          ; [ebp-20] - dword, Count, number of characters displayed
          ; [ebp-24] - dword, starting address
          ; [ebp-28] - dword, incremental values after each line of data
          ;  .                .
          ;  .                . (up to 16 lines)
          ;  .                .
          ; [ebp-92] - dword, incremental values after each line of data
          ; [ebp-96] - dword, pointer mask
          ; [ebp-100]- dword, pointer bitmap
            pushad
          ;; Make sure the mouse coordinates are not off the screen
            .IF (dword ptr ss:[ebp+28] > 718)
                mov     dword ptr ss:[ebp+28],718
            .ENDIF
            .IF (dword ptr ss:[ebp+24] > 346)
                mov     dword ptr ss:[ebp+24],346
            .ENDIF

          ;; Calculate the starting offset into video memory
          ; do vertical
            mov     eax,dword ptr ss:[ebp+24]
            mov     ebx,4
            xor     edx,edx
            div     ebx
            .IF (dl == 00b)
              ; They're exactly on a boundary
                xor     ecx,ecx
            .ELSEIF (dl == 01b)
              ; They're on the first boundary
                mov     ecx,2000h
            .ELSEIF (dl == 10b)
              ; They're on the second boundary
                mov     ecx,4000h
            .ELSE
              ; They're on the third boundary
                mov     ecx,6000h
            .ENDIF
          ; Continue on vertical (to get the correct offset into the screen)
            mov     ebx,90
            mul     ebx
            add     eax,ecx
            mov     dword ptr ss:[ebp-24],eax

          ; Right now, eax contains the starting offset into video memory (not including the X coordinate)
            mov     eax,dword ptr ss:[ebp+28]
            mov     ebx,8
            xor     edx,edx
            div     ebx
          ; Right now, eax - offset across the line for the first character
          ;            edx - Number of bits to use for the first character
            add     dword ptr ss:[ebp-24],eax
            mov     byte ptr ss:[ebp-08],dl
          ; Right now, ss:[ebp-24] - starting offset into video memory
          ;            ss:[ebp-08] - number of bits to shift each character right
          ; [ebp+28] - dword, --Nuserved        ; These are freed up because they do not need to be used right now
          ; [ebp+24] - dword, --Nuserved

          ; Now, build the array indicating the offset increments per iteration
          ; We use edx as our source value, we calculate the offsets each time
            mov     edx,dword ptr ss:[ebp-24]                       ; prime our starting address
            mov     eax,edx                                         ; and copy to our "hold" value
            and     eax,1fffh
            mov     ebx,-28
            mov     ecx,16
            .REPEAT
                push    ecx
                .IF (edx < 6000h)
                    add     edx,2000h
                    mov     ecx,2000h
                .ELSE
                  ; We can't just block-increment anymore
                  ; We now have to go back to our original value and add 90 to it
                    add     eax,90
                    mov     edx,eax
                    mov     ecx,0ffffffffh-6000h + 90 + 1
                .ENDIF
                mov     dword ptr ss:[ebp+ebx],ecx
                sub     ebx,4
                pop     ecx
            .UNTILCXZ
          ; Terminate the addresses with our stopper
            mov     dword ptr ss:[ebp+ebx],0ffffffffh
          ; Right now, every value is setup for our write operation.
          ; All we have to do to output our text is get the pointer to the appropriate character bitmap,
          ; then start writing bytes at a time (accounting, of course, for the bit shifting and write masks)

          ; [ebp+28] - dword, bits wide for each character
          ; [ebp+24] - dword, maximum offset to achieve (before text is ignored because it would go off the right side of the screen)
            mov     dword ptr ss:[ebp+28],16                        ; bits wide
            mov     ecx,16
            xor     edx,edx
            .REPEAT
                stc
                rcl     edx,1
            .UNTILCXZ
            mov     cl,byte ptr ss:[ebp-08]
          ; Adjust our bit rotation factor for the extra characters involved in multi-character fonts
            .IF (dword ptr ss:[ebp+28] > 8)
                mov     eax,dword ptr ss:[ebp+28]
                sub     eax,8
                add     cl,al
                add     byte ptr ss:[ebp-08],al
            .ENDIF
            ror     edx,cl

          ; Right now, edx is a bitmap of this character's width
            mov     dword ptr ss:[ebp-12],edx                       ; base bitmap (used for masking operations)

;; Bochs intercept start
;.IF (dword ptr ss:[ebp+20] == 0)
;    pushad
;
;    mov     ecx,0
;    mov     esi,-28
;    mov     edi,11223344h
;    mov     esi,dword ptr ss:[ebp+16]
;    .WHILE (ecx < 16)
;        mov     eax,_BOCHS1
;        mov     ebx,_BOCHS2
;        mov     edx,dword ptr ds:[esi]
;        int     0ffh
;        add     esi,4
;        inc     ecx
;    .ENDW
;
;    popad
;.ENDIF
;; Bochs intercept end

          ;; Start drawing the characters
            mov     eax,_sMONO
            mov     es,ax
            mov     edi,dword ptr ss:[ebp-24]                       ; Destination starting address on screen
            mov     eax,offset mono_mouse_font_base
            mov     esi,dword ptr ss:[ebp+16]                       ; Where to store/retrieve the mouse data (depending on mode)
          ; * Note:  If additional mouse pointers are to be added later, they can be incorporated right here:
          ;          eax = eax + pointer_number * (2*16) => Offset to mouse pointer in mouse.fnt
          ; Right now, cs:[eax] - far ptr to the base of this mouse pointer
            mov     ebx,-28                                         ; Starting offset into stack for add to offsets
            .WHILE (dword ptr ss:[ebp+ebx] != 0ffffffffh)
                .IF (dword ptr ss:[ebp+20] == 0)
                  ; We're hiding the existing mouse pointer, so we pull data from our previously saved area
                    mov     edx,dword ptr ds:[esi]                  ; Load the background from our previously saved area
                    mov     dword ptr es:[edi],edx
                    add     esi,4
                .ELSE
                  ; We're putting a mouse pointer onto the screen, so we get ready to write the data from the mouse pointer font
                  ; We're displaying our mouse pointer, so we store what's here now, then write our pointer afterwards
                    mov     edx,dword ptr ss:[ebp-12]               ; Update our working bitmap (use this push/pop sequence)
                    mov     dword ptr ss:[ebp-16],edx
                    mov     edx,dword ptr es:[edi]                  ; Store the dword that's currently here
                    mov     dword ptr ds:[esi],edx
                    add     esi,4

                  ; Calculate the maximum byte that can be written to before the mouse wraps around to the other side of the screen
                    push    eax
                    push    ebx
                    push    edx

                    xor     edx,edx
                    mov     eax,edi
                    .IF (eax > 6000h)
                        sub     eax,6000h
                    .ELSEIF (eax > 4000h)
                        sub     eax,4000h
                    .ELSEIF (eax > 2000h)
                        sub     eax,2000h
                    .ENDIF
                    mov     ebx,90
                    div     ebx
                    .IF (edx >= 88)
                      ; We're within 2 bytes of the side
                        sub     ebx,edx                             ; 90-edx
                        dec     ebx                                 ; Decrement 1 (change base-1 to base-0)
                        add     ebx,edi                             ; Add in our current pointer
                        mov     dword ptr ss:[ebp-04],ebx           ; And we have our ending bit
                    .ELSE
                        mov     dword ptr ss:[ebp-04],07fffh        ; Make it some outrageously high value (so it will always pass)
                    .ENDIF
                    pop     edx
                    pop     ebx
                    pop     eax

                    xor     edx,edx
                    mov     cl,byte ptr ss:[ebp-08]                 ; Load the number of bits to rotate
                    mov     dx,word ptr cs:[eax]                    ; Get the bit mask for this line of the mouse pointer
                    not     edx                                     ; Reverse it
                    ror     edx,cl                                  ; Rotate it
                    mov     dword ptr ss:[ebp-96],edx               ; Store it

                    xor     edx,edx
                    mov     dx,word ptr cs:[eax+32]                 ; Load the actual bitmap from our mouse pointer font
                    ror     edx,cl                                  ; And rotate
                    push    edi
                    .WHILE (dword ptr ss:[ebp-16] != 0 && edi <= dword ptr ss:[ebp-04])
                      ; Write the mouse pointer (or previous buffer, depending on what they're doing)

                      ; Apply the mask (removes all bits that will be inside the bitmap below)
                      ; To understand why this is done, refer to mouse.fnt and look at the two pointers.  You'll see why.
                      ; Basically it adds a black outline around the mouse pointer by masking off a larger area first, then
                      ; adding a smaller bitmap which represent the mouse pointer bits to keep on
                        push    edx
                        mov     dl,byte ptr ss:[ebp-96]
                        and     byte ptr es:[edi],dl
                        pop     edx

                      ; Add the bitmap
                        or      byte ptr es:[edi],dl

                      ; Move to the next byte
                        inc     edi

                      ; Now, rotate everything for the next part
                        rol     edx,8
                        and     edx,0ffff00ffh                      ; Get rid of the byte we just drew
                        rol     dword ptr ss:[ebp-96],8
                        and     dword ptr ss:[ebp-96],0ffff00ffh
                        rol     dword ptr ss:[ebp-16],8
                        and     dword ptr ss:[ebp-16],0ffff00ffh
                    .ENDW
                  done_writing:
                    pop     edi
                .ENDIF
                add     edi,dword ptr ss:[ebp+ebx]
                add     eax,2                                       ; Move to the next mask from the mouse pointer font
                sub     ebx,4
            .ENDW

            popad
            leave
            pop     es
        .ENDIF
        retf    16
    VID_g_mono_mouse_pointer    ENDP




    VID_g_mono_window_function      PROC
    ; This routine draws/retrieves information on/from the mono screen in a window format
    ;
    ; Upon entry:   Parameters are passed on the stack as below
    ;               ds - data segment for the offset to data
    ;
    ; Upon exit:    The window is either stored, displayed or cleared (depending on the action)
    ;
        .IF (cs:VID_g_owner != 0ffffffffh)
          ; [ebp+36] - dword, ul-x
          ; [ebp+32] - dword, ul-y
          ; [ebp+28] - dword, lr-x
          ; [ebp+24] - dword, lr-y
          ; [ebp+20] - dword, request (0  - put,
          ;                            1  - get,
          ;                            2  - clear,
          ;                            3  - calculate (required buffer for action)
          ;                            11 - get NOT)
          ; [ebp+16] - dword, offset to data location if [ebp+20] = 0 or 1
          ; [ebp+12] - cs
          ; [ebp+08] - eip
          ; [ebp+04] - es
          ; [ebp+00] - ebp
            push    es
            enter   24,0
          ; [ebp-04] - dword, number of bits to get/write to the screen
          ; [ebp-05] -  byte, --Nuserved
          ; [ebp-06] -  byte, --Nuserved
          ; [ebp-07] -  byte, --Nuserved
          ; [ebp-08] -  byte, number of bits to rotate each character right
          ; [ebp-12] - dword, baseline bitmap for this character (stays the same, based on the font)
          ; [ebp-16] - dword, --Nuserved
          ; [ebp-20] - dword, --Nuserved
          ; [ebp-24] - dword, starting address
            pushad
          ; [esp+24] - dword, access to ecx (for request=3)     ; * Note, this is part of the PUSHAD command.  Refer to IA-32 manuals.

            .IF (dword ptr ss:[ebp+20] > 3 && dword ptr ss:[ebp+20] != 11)
              ; This is not a valid request, we ignore it.  YEAH BABY!
                jmp     total_quit
            .ENDIF
          ;; Calculate the starting offset into video memory
          ; do vertical
            mov     eax,dword ptr ss:[ebp+32]
            mov     ebx,4
            xor     edx,edx
            div     ebx
            .IF (dl == 00b)
              ; They're exactly on a boundary
                xor     ecx,ecx
            .ELSEIF (dl == 01b)
              ; They're on the first boundary
                mov     ecx,2000h
            .ELSEIF (dl == 10b)
              ; They're on the second boundary
                mov     ecx,4000h
            .ELSE
              ; They're on the third boundary
                mov     ecx,6000h
            .ENDIF
          ; Continue on vertical (to get the correct offset into the screen)
            mov     ebx,90
            mul     ebx
            add     eax,ecx
            mov     dword ptr ss:[ebp-24],eax

          ; Right now, eax contains the starting offset into video memory (not including the X coordinate)
            mov     eax,dword ptr ss:[ebp+36]
            mov     ebx,8
            xor     edx,edx
            div     ebx
            add     dword ptr ss:[ebp-24],eax

            mov     byte ptr ss:[ebp-08],dl
          ; Right now, [ebp-24] - offset to start getting data from
          ;            [ebp-08] - number of bits to shift each character right
            mov     cl,dl
            mov     edx,0ff00h
            ror     edx,cl
            xchg    dh,dl
            not     edx
          ; Right now, edx is a bitmap this byte's reverse image (used below for masking)
            mov     dword ptr ss:[ebp-12],edx                       ; base bitmap

            mov     edx,dword ptr ss:[ebp+28]
            .IF (edx <= dword ptr ss:[ebp+36])
              ; They're doing it wrong, they have the values reversed.  We ignore this as it, too, is an error.
                jmp     quit
            .ENDIF
            sub     edx,dword ptr ss:[ebp+36]
            mov     dword ptr ss:[ebp-04],edx                       ; Store the maximum # of bits to get

          ; Now, we traverse memory at the offsets required to complete this iterate maneuver (whew!)
          ; We use edi as our source value, calculating the new offset each time the vertical line changes
            mov     ax,_sMONO
            mov     es,ax
            mov     edi,dword ptr ss:[ebp-24]                       ; Our starting address in video memory
            mov     esi,dword ptr ss:[ebp+16]                       ; Where we're supposed to get/put data
            mov     eax,edi                                         ; Our iterate increase value for when we get above 6000h
            and     eax,1fffh
          vertical_loop:
            push    edi
            xor     ecx,ecx
            .WHILE (ecx < dword ptr ss:[ebp-04])
                push    ecx
                mov     edx,dword ptr ss:[ebp-12]                   ; Update our working bitmap

                .IF (dword ptr ss:[ebp+20] == 0)
                  ; We're putting data to the screen, we scroll right first, drop back, then punt, on two, on four, READY!? ... BREAK!
                    .IF (byte ptr ss:[ebp-08] == 0)
                      ; We can write a byte at a time because we're byte-aligned.  We like this.  We really do. :)
                        movzx   edx,byte ptr ds:[esi]
                        mov     byte ptr es:[edi],dl
                        jmp     next_part
                    .ELSE
                      ; We have to write across two bytes.  No biggie, just one of those things
                        xor     edx,edx
                        mov     dh,byte ptr ds:[esi]
                        mov     cl,byte ptr ss:[ebp-08]
                      ; Mask off the bits that are already there first
                        mov     ebx,dword ptr ss:[ebp-12]
                        and     word ptr es:[edi],bx

                      ; Apply the part we're putting
                        shr     edx,cl
                        xchg    dh,dl
                        or      word ptr es:[edi],dx
                        jmp     next_part
                    .ENDIF
                .ELSEIF (dword ptr ss:[ebp+20] == 1 || dword ptr ss:[ebp+20] == 11)
                  ; We're getting the data from the screen.  This is an important operation.  Please treat it as such.
                    xor     edx,edx
                    .IF (byte ptr ss:[ebp-08] == 0)
                      ; We're bit aligned
                        mov     dl,byte ptr es:[edi]
                    .ELSE
                      ; We have to shift this data to get it
                        mov     dx,word ptr es:[edi]                ; Get the byte from the screen (and the one to its right)
                        xchg    dh,dl
                        mov     cl,byte ptr ss:[ebp-08]
                        shl     edx,cl
                        xchg    dl,dh
                    .ENDIF
                    .IF (dword ptr ss:[ebp+20] == 11)
                        not     dl
                    .ENDIF
                    mov     byte ptr ds:[esi],dl

                .ELSEIF (dword ptr ss:[ebp+20] == 2)
                  ; We're clearing
                    mov     byte ptr es:[edi],0

                ;.ELSEIF (dword ptr ss:[ebp+20] == 3)
                ;  ; We're counting, but we don't really do anything
                ;  ; Our only purpose is to serve our master
                ;  ; As such, we are just here counting to find out how big the buffer will need to be
                ;  ; We are only servants and do as we're told.  We love our lives.
                .ENDIF
              ; Move to the next location in our buffer
              next_part:
                pop     ecx
                inc     esi
                inc     edi
                add     ecx,8
            .ENDW
            .IF (ecx > dword ptr ss:[ebp-04] && dword ptr ss:[ebp+20] == 1)
              ; We obtained more bits than we were supposed to, we need to mask off part of the last one
              ; Right now, ecx indicates how many bits we need to mask off
                xor     edx,edx
                .REPEAT
                    stc
                    rcl     edx,1
                .UNTILCXZ
                not     edx
                and     byte ptr ds:[esi-1],dl                      ; Mask off the extra bits
            .ENDIF

            pop     edi
          ; Move to the next vertical line on the screen
            .IF (edi < 6000h)
                add     edi,2000h
            .ELSE
              ; We can't just block-increment anymore
              ; We now have to go back to our original value and add 90 to it
                add     eax,90
                mov     edi,eax
            .ENDIF
            inc     dword ptr ss:[ebp+32]                           ; Update our line count
            mov     edx,dword ptr ss:[ebp+32]
            cmp     edx,dword ptr ss:[ebp+24]
          ; If we branch, still some lines yet to do (Yes, I'll take something a cocaine addict might say for a thousand, Alex)
            jbe     vertical_loop


          quit:
            .IF (dword ptr ss:[ebp+20] == 3)
              ; They want to know how big it should be
                sub     esi,dword ptr ss:[ebp+16]
              ; Right now, esi is our length
                inc     esi                                         ; And add one for good measure
                mov     dword ptr ss:[esp+24],esi                   ; This accesses ecx from the PUSHAD above
            .ENDIF
          total_quit:
            popad
            leave
            pop     es
        .ENDIF
        retf    24
    VID_g_mono_window_function      ENDP




    VID_g_mono_cursor_no_insert     PROC
        .IF (cs:VID_g_owner == 0ffffffffh)
            retf 8
        .ENDIF
        push    ds
        mov     ds,cs:data_segment
        mov     ds:VID_g_mono_insert_mode,0
        pop     ds
        jmp     invVID_g_mono_cursor
    VID_g_mono_cursor_no_insert     ENDP




    VID_g_mono_cursor       PROC
        .IF (cs:VID_g_owner == 0ffffffffh)
            retf 8
        .ENDIF
        push    ds
        mov     ds,cs:data_segment
        mov     ds:VID_g_mono_insert_mode,1
        pop     ds
        jmp     invVID_g_mono_cursor
    VID_g_mono_cursor       ENDP





    invVID_g_mono_cursor        PROC
    ; This routine draws the cursor on the screen (or removes it from the screen)
    ;
    ; Upon entry:   Parameters are passed on the stack as below
    ;               The offset must be a 64 byte buffer
    ;
    ; Upon exit:    The mouse is either displayed or undisplayed
    ;
        .IF (cs:VID_g_owner != 0ffffffffh)
          ; [ebp+20] - dword, horizontal
          ; [ebp+16] - dword, vertical
          ; [ebp+12] - cs
          ; [ebp+08] - eip
          ; [ebp+04] - es
          ; [ebp+00] - ebp
            push    es
            enter   104,0
          ; [ebp-04] - dword, --Nuserved
          ; [ebp-05] -  byte, --Nuserved
          ; [ebp-06] -  byte, --Nuserved
          ; [ebp-07] -  byte, --Nuserved
          ; [ebp-08] -  byte, number of bits to rotate each character right
          ; [ebp-12] - dword, --Nuserved
          ; [ebp-16] - dword, --Nuserved
          ; [ebp-20] - dword, --Nuserved
          ; [ebp-24] - dword, starting address
          ; [ebp-28] - dword, --Nuserved
          ;  .                .
          ;  .                . (up to 16 lines)
          ;  .                .
          ; [ebp-92] - dword, incremental values after each line of data
          ; [ebp-96] - dword, pointer mask
          ; [ebp-100]- dword, pointer bitmap
          ; [ebp-104]- dword, lines to skip if not in insert mode
            pushad
          ;; Make sure the mouse coordinates are not off the screen
            .IF (dword ptr ss:[ebp+20] > 712)
                mov     dword ptr ss:[ebp+20],712
            .ENDIF
            .IF (dword ptr ss:[ebp+16] > 340)
                mov     dword ptr ss:[ebp+16],340
            .ENDIF

          ;; Calculate the starting offset into video memory
          ; do vertical
            mov     eax,dword ptr ss:[ebp+16]
            mov     ebx,4
            xor     edx,edx
            div     ebx
            .IF (dl == 00b)
              ; They're exactly on a boundary
                xor     ecx,ecx
            .ELSEIF (dl == 01b)
              ; They're on the first boundary
                mov     ecx,2000h
            .ELSEIF (dl == 10b)
              ; They're on the second boundary
                mov     ecx,4000h
            .ELSE
              ; They're on the third boundary
                mov     ecx,6000h
            .ENDIF
          ; Continue on vertical (to get the correct offset into the screen)
            mov     ebx,90
            mul     ebx
            add     eax,ecx
            mov     dword ptr ss:[ebp-24],eax

          ; Right now, eax contains the starting offset into video memory (not including the X coordinate)
            mov     eax,dword ptr ss:[ebp+20]
            mov     ebx,8
            xor     edx,edx
            div     ebx
          ; Right now, eax - offset across the line for the first character
          ;             dl - Number of bits to use for the first character
            add     dword ptr ss:[ebp-24],eax
            mov     byte ptr ss:[ebp-08],dl
          ; Right now, ss:[ebp-24] - starting offset into video memory
          ;            ss:[ebp-08] - number of bits to shift each character right
          ; [ebp+20] - dword, --Nuserved        ; These are freed up because they do not need to be used right now
          ; [ebp+16] - dword, --Nuserved

          ; Now, build the array indicating the offset increments per iteration
          ; We use edx as our source value, we calculate the offsets each time
            mov     edx,dword ptr ss:[ebp-24]                       ; prime our starting address
            mov     eax,edx                                         ; and copy to our "hold" value
            and     eax,1fffh
            mov     ebx,-28
            mov     edi,cs:current_font
            mov     ecx,dword ptr cs:[edi+4]
            .IF (ecx > 16)
              ; Just to make sure our algorithm doesn't fail
                mov     ecx,16
            .ENDIF

            .IF (cs:VID_g_mono_insert_mode == 0)
              ; We're not in insert mode, make the cursor 1/4th as tall as it is in insert mode
                push    eax
                mov     eax,ecx
                shr     eax,2
                adc     eax,0
                neg     eax
                add     eax,ecx
                mov     dword ptr ss:[ebp-104],eax
                pop     eax
            .ELSE
              ; We're in insert mode
                mov     dword ptr ss:[ebp-104],0
            .ENDIF
            .REPEAT
                push    ecx
                .IF (edx < 6000h)
                    add     edx,2000h
                    mov     ecx,2000h
                .ELSE
                  ; We can't just block-increment anymore
                  ; We now have to go back to our original value and add 90 to it
                    add     eax,90
                    mov     edx,eax
                    mov     ecx,0ffffffffh-6000h + 90 + 1
                .ENDIF
                mov     dword ptr ss:[ebp+ebx],ecx
                sub     ebx,4
                pop     ecx
            .UNTILCXZ
            mov     dword ptr ss:[ebp+ebx],0ffffffffh
          ; Right now, every value is setup for our write operation.
          ; [ebp+20] - dword, bits wide for each character
          ; [ebp+16] - dword, maximum offset to achieve (before text is ignored because it would go off the right side of the screen)

            mov     ecx,dword ptr cs:[edi]
            mov     dword ptr ss:[ebp+20],ecx                       ; bits wide
            xor     edx,edx
            .REPEAT
                stc
                rcl     edx,1
            .UNTILCXZ
            movzx   ecx,byte ptr ss:[ebp-08]
            .IF (ecx != 0)
                rol     edx,8
                ror     edx,cl
            .ENDIF

          ; Right now, edx is a bitmap of this character's width
          ;; Start drawing the characters
            mov     eax,_sMONO
            mov     es,ax
            mov     edi,dword ptr ss:[ebp-24]                       ; Destination starting address on screen
          ; * Note:  If additional mouse pointers are to be added later, they can be incorporated right here:
          ;          eax = eax + pointer_number * (2*16) => Offset to mouse pointer in mouse.fnt
          ; Right now, cs:[eax] - far ptr to the base of this mouse pointer
            xchg    dh,dl
            mov     ebx,-28                                         ; Starting offset into stack for add to offsets
            xor     eax,eax                                         ; Used as a count
            .WHILE (dword ptr ss:[ebp+ebx] != 0ffffffffh)
                .IF (eax >= dword ptr ss:[ebp-104])
                  ; We're OK to do this one (depending on what insert mode we're in, we may have to wait a few lines)
                    .IF (dword ptr ss:[ebp+20] != 8)
                        .IF (ecx != 0)
                            ror     edx,16
                            xor     byte ptr es:[edi],dl
                            ror     edx,16
                            xor     word ptr es:[edi+1],dx
                        .ELSE
                            xor     word ptr es:[edi],dx
                        .ENDIF
                    .ELSE
                        .IF (ecx != 0)
                            xor     word ptr es:[edi],dx
                        .ELSE
                            xor     byte ptr es:[edi],dh
                        .ENDIF
                    .ENDIF
                .ENDIF
                inc     eax                                         ; Increase our count

              ; Move to next line on screen
                add     edi,dword ptr ss:[ebp+ebx]
              ; Go back up our list of "incremental values"
                sub     ebx,4
            .ENDW

            popad
            leave
            pop     es
        .ENDIF
        retf    8
    invVID_g_mono_cursor        ENDP




    VID_g_mono_enter_graphics_mode    PROC    NEAR
    ; This routine programs the 6845 CRT controller for the 720x348 graphics mode.
    ; The active page for both writing and display is set to the default value of page 0.
        .IF (cs:VID_g_owner != 0ffffffffh)
            push    ds
            pushad

            mov     ds,cs:data_segment
            mov     ds:mono_video,MONO_GRAPH

            mov     dx,03bfh
            mov     al,01b
            out     dx,al

            mov     al,MONO_GRAPH
            mov     esi,offset mono_graphics_crtc
            call    _set_mono_mode
            callf   VID_g_mono_clear_screen

          ; Update the system memory
            mov     eax,_sSYSTEM
            mov     ds,ax
            mov     word ptr ds:[_SYSTEM_MONO_VIDEO_MODE],0

            popad
            pop     ds
        .ENDIF
        retf
    VID_g_mono_enter_graphics_mode    ENDP




    VID_g_mono_clear_screen     PROC
        .IF (cs:VID_g_owner != 0ffffffffh)
            push    es
            pushad

            mov     eax,_sMONO
            mov     es,ax
            xor     edi,edi
            mov     ecx,7fffh
            xor     eax,eax
            rep     stosb

            popad
            pop     es
        .ENDIF
        retf
    VID_g_mono_clear_screen     ENDP




    VID_mono_enter_text_mode    PROC    NEAR
    ; This routine programs the 6845 and CRT control register to produce text mode.
        .IF (cs:VID_g_owner != 0ffffffffh)
            push    ds
            pushad

            mov     ds,cs:data_segment
            mov     ds:mono_video,MONO_TEXT

            mov     dx,03bfh
            mov     al,01b
            out     dx,al

            mov     al,MONO_TEXT
            mov     esi,offset mono_text_crtc
            call    _set_mono_mode
            callf    VID_clear_screen_mono

          ; Update the system memory
            mov     eax,_sSYSTEM
            mov     ds,ax
            mov     word ptr ds:[_SYSTEM_MONO_VIDEO_MODE],1

            popad
            pop     ds
        .ENDIF
        retf
    VID_mono_enter_text_mode    ENDP




    _set_mono_mode      PROC    NEAR
    ; This routine sets mode to graphics or text depending on al
    ;
    ; Upon entry:   si = parameter table
    ;               cx = number of words to be cleared
    ;               bx = blank value
    ;

    ;; Turn the screen off to set the mode
        push    eax
        mov     edx,MONO_CRTC_CNTRL
        out     dx,al

    ;; Now, initialize the 6845
        mov     edx,MONO_CRTC_INDEX
        mov     ecx,12      ; 12 parameters to be output
        xor     ah,ah       ; starting from register 0
      parms:
      ; Write the index
        mov     al,ah
        out     dx,al
        inc     edx

      ; Get the CRT value
        mov     al,byte ptr cs:[esi]
        inc     esi

      ; Write the CRT value
        out     dx,al       ; write the CRT value
        dec     edx

      ; Move to next index
        inc     ah
        loop    parms


    ;; Turn the screen on now because ... we're finished! :)
        pop     eax
        add     al,MONO_SCREEN_ON
        mov     edx,MONO_CRTC_CNTRL
        out     dx,al

        ret
    _set_mono_mode      ENDP