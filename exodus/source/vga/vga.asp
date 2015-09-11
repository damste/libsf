; vga.asp
;
; Exodus VGA driver VGA algorithms
;




    VID_position_cursor_vga     PROC
        callf   VID_set_registers_for_vga
        call    _position_cursor
        retf
    VID_position_cursor_vga     ENDP




    VID_get_cursor_vga      PROC
        push    ebx
        push    eax

        xor     edx,edx
        movzx   eax,cs:offset_vga
        mov     ebx,160
        div     ebx
        mov     dh,al
        shr     dl,1

        pop     eax
        pop     ebx
        retf
    VID_get_cursor_vga      ENDP




    VID_set_registers_for_vga   PROC
        push    ds
        mov     ds,cs:data_segment

        mov     ds:reg1,CRTC_INDEX
        mov     ds:reg2,CRTC_DATA
        mov     ds:storage_ptr,offset offset_vga

        pop     ds
        retf
    VID_set_registers_for_vga   ENDP




    VID_display_string_vga    PROC
    ; ds:[si] - far pointer to null-terminated string
    ; offset_vga - pointer into the screen where to start writing
        pushad
        push    es
        push    fs

        mov     es,cs:data_segment
        mov     di,_sVGA
        mov     fs,di
        mov     di,es:offset_vga                                    ; Offset we're writing to
        mov     ah,es:attribute_vga                                 ; Color we're using
        .IF (es:bootup == 1)
          ; During bootup, strings can be terminated with 255 as well as 0
            .WHILE (byte ptr ds:[esi] != 0 && byte ptr ds:[esi] != 255)     ; Loop until one of two chars is found
                lodsb
                mov     byte ptr fs:[edi],al                        ; Write character
                inc     di
                mov     byte ptr fs:[edi],ah                        ; Write color
                inc     di
            .ENDW
        .ELSE
            .WHILE (byte ptr ds:[esi] != 0)                         ; Loop until the NULL terminated string is found
                lodsb
                mov     byte ptr fs:[edi],al                        ; Write character
                inc     di
                mov     byte ptr fs:[edi],ah                        ; Write color
                inc     di
            .ENDW
        .ENDIF
        mov     bx,di                                               ; Adjust the cursor position
        shr     bx,1
        callf   VID_set_registers_for_vga
        call    _position_cursor_raw_data
        mov     es:offset_vga,di                                    ; Store our new offset

        pop     fs
        pop     es
        popad
        retf
    VID_display_string_vga    ENDP




    VID_display_string_ecx_vga    PROC
    ; ds:[si] - far pointer to null-terminated string
    ;     ecx - number of bytes to display
    ; offset_vga - pointer into the screen where to start writing
        pushad
        push    es
        push    fs

        mov     es,cs:data_segment
        mov     di,_sVGA
        mov     fs,di
        mov     di,es:offset_vga                                    ; Offset we're writing to
        mov     ah,es:attribute_vga                                 ; Color we're using
        .REPEAT                                                     ; Loop until the NULL terminated string is found
            lodsb
            mov     byte ptr fs:[edi],al                            ; Write character
            inc     di
            mov     byte ptr fs:[edi],ah                            ; Write color
            inc     di
        .UNTILCXZ
        mov     bx,di                                               ; Adjust the cursor position
        shr     bx,1
        callf   VID_set_registers_for_vga
        call    _position_cursor_raw_data
        mov     es:offset_vga,di                                    ; Store our new offset

        pop     fs
        pop     es
        popad
        retf
    VID_display_string_ecx_vga    ENDP




    VID_display_hex_string_ecx_vga      PROC
    ; ds:[si] - far pointer to null-terminated string
    ;     ecx - number of hexidecimal digits to display
    ; offset_vga - pointer into the screen where to start writing
        pushad
        push    es
        push    fs

        mov     es,cs:data_segment
        mov     di,_sVGA
        mov     fs,di
        mov     di,es:offset_vga                                    ; Offset we're writing to
        mov     ah,es:attribute_vga                                 ; Color we're using
        .REPEAT
            lodsb
            mov     dl,al
            call    hex_adjust_al_dl
            mov     byte ptr fs:[edi],32                            ; Write a space before hexidecimal values
            inc     di
            mov     byte ptr fs:[edi],ah                            ; Write color
            inc     di
            mov     byte ptr fs:[edi],dl                            ; Write left 1/2 of hexidecimal values character
            inc     di
            mov     byte ptr fs:[edi],ah                            ; Write color
            inc     di
            mov     byte ptr fs:[edi],al                            ; Write right 1/2 of hexidecimal values character
            inc     di
            mov     byte ptr fs:[edi],ah                            ; Write color
            inc     di
            mov     byte ptr fs:[edi],32                            ; Write a space after hexidecimal values
            inc     di
            mov     byte ptr fs:[edi],ah                            ; Write color
            inc     di
        .UNTILCXZ
        mov     bx,di                                               ; Adjust the cursor position
        shr     bx,1
        callf   VID_set_registers_for_vga
        call    _position_cursor_raw_data
        mov     es:offset_vga,di                                    ; Store our new offset

        pop     fs
        pop     es
        popad
        retf
    VID_display_hex_string_ecx_vga      ENDP




    VID_display_hex_string_ecx_ro_vga    PROC
        pushfd
        pushad

        add     esi,ecx
        dec     esi                                                 ; Change base-1 to base-0
        std
        callf   VID_display_hex_string_ecx_vga

        popad
        popfd
        retf
    VID_display_hex_string_ecx_ro_vga    ENDP




    VID_display_string_nr_vga     PROC
        pushad
        push    es

        callf   VID_display_string_vga
        callf   VID_move_to_next_line_vga

        pop     es
        popad
        retf
    VID_display_string_nr_vga     ENDP




    VID_display_string_ecx_nr_vga     PROC
        pushad
        push    es

        callf   VID_display_string_ecx_vga
        callf   VID_move_to_next_line_vga

        pop     es
        popad
        retf
    VID_display_string_ecx_nr_vga     ENDP




    VID_display_hex_string_ecx_nr_vga     PROC
        pushad
        push    es

        callf   VID_display_hex_string_ecx_vga
        callf   VID_move_to_next_line_vga

        pop     es
        popad
        retf
    VID_display_hex_string_ecx_nr_vga     ENDP




    VID_move_to_next_line_vga   PROC
        pushad
        push    es
        push    fs

        mov     es,cs:data_segment
        mov     ax,_sVGA
        mov     fs,ax
        mov     ax,es:offset_vga                                    ; Move to the next row
        xor     dx,dx                                               ; Divide offset_vga by 80*2 to get # of lines
        mov     bx,80*2
        div     bx
        inc     ax                                                  ; Ignore the remainder and move down to the next line
        mul     bx
        .IF (ax > 24*(80*2))                                        ; Are we past the bottom of the screen?
            .IF (es:freeze_vga == 0)
                xor     di,di                                       ; Yes, scroll everything up
                mov     si,80*2
                mov     cx,24*(80*2)                                ; 24 lines are scrolling
            .ELSE
                mov     al,es:freeze_vga
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
                mov     al,byte ptr fs:[esi]                        ; Load a byte
                mov     byte ptr fs:[edi],al                        ; Store a byte
                inc     esi
                inc     edi
            .UNTILCXZ
            mov     es:offset_vga,di                                ; This is our new offset (the left-most char on bottom line)
            mov     cx,80                                           ; Clear off the last 80 characters (the new blank bottom line)
            mov     ah,es:attribute_vga
            .REPEAT
                mov     byte ptr fs:[edi]," "
                inc     edi
                mov     byte ptr fs:[edi],ah
                inc     edi
            .UNTILCXZ
        .ELSE
            mov     es:offset_vga,ax
        .ENDIF
        mov     bx,es:offset_vga
        shr     bx,1
        call    _position_cursor_raw_data

        pop     fs
        pop     es
        popad
        retf
    VID_move_to_next_line_vga   ENDP




    VID_display_radix_in_edx_vga    PROC
        pushad
        push    ds
        sub     esp,16                                              ; Assume a maximum length of 12 chars (4 extra for boundary)
        mov     ebp,esp

        call    _generate_radix_string
        callf   VID_display_string_vga

        add     esp,16
        pop     ds
        popad
        retf
    VID_display_radix_in_edx_vga    ENDP




    VID_display_radix_in_edx_nr_vga     PROC
        pushad
        push    ds
        sub     esp,16                                              ; Assume a maximum length of 12 characters
        mov     ebp,esp

        call    _generate_radix_string
        callf   VID_display_string_nr_vga

        add     esp,16
        pop     ds
        popad
        retf
    VID_display_radix_in_edx_nr_vga     ENDP




    VID_set_attribute_vga   PROC
        push    ds

        mov     ds,cs:data_segment
        mov     ds:attribute_vga,al

        pop     ds
        retf
    VID_set_attribute_vga   ENDP




    VID_clear_screen_vga    PROC
    ; This routine clears the vga screen buffer
        pushad
        push    es
        push    fs

        mov     es,cs:data_segment
        mov     di,_sVGA
        mov     fs,di
        mov     es:offset_vga,0
        xor     di,di
        mov     cx,80 * 25
        mov     al,32
        mov     ah,es:attribute_vga
        .REPEAT
            mov     word ptr fs:[edi],ax
            add     edi,2
        .UNTILCXZ
        xor     dx,dx
        callf   VID_position_cursor_vga

        pop     fs
        pop     es
        popad
        retf
    VID_clear_screen_vga    ENDP




    VID_freeze_frame_vga    PROC    NEAR
    ; This routine is used to indicate how much of the top portion of the screen should be frozen
    ;
    ; Upon entry:   al - lines to freeze (must be 0-24)
    ;
    ; Upon exit:    if al is valid, freeze_vga is updated
    ;
        push    ds

        .IF (al <= 24)
            mov     ds,cs:data_segment
            mov     ds:freeze_vga,al
        .ENDIF

        pop     ds
        retf
    VID_freeze_frame_vga    ENDP




    VID_draw_logo   PROC
    ; This routine is used to draw the 18x16 logo's used during driver initialization
    ; It is only used during bootup
    ;
    ; Upon entry:   ds:[esi] - far ptr to 300-byte logo structure
    ;
    ; Upon exit:    The logo is drawn
    ;
        push    es
        push    fs
        pushad

        mov     fs,cs:data_segment
        mov     ax,_sGRAPHICS
        mov     es,ax
      ;; Get the offset into video memory
      try_again:
        mov     edi,320*140                                     ; Starting location regardless
        add     edi,fs:logo_x
        add     edi,fs:logo_y
        mov     fs:highest_palette,0
        add     edi,641                                         ; Always start two lines down and one pixel over
                                                                ;   (for a visual spacing, it looks nicer I think)
      ; Adjust for a multi-picture image
        mov     bl,byte ptr ds:[esi]
        and     bl,0111b
        .IF (bl == 1)
          ; Make sure there's enough room on this line for a double-wide on the current line
            mov     ebx,40
          try_this_slot:
            add     fs:logo_x,ebx
            push    fs:logo_x
            push    fs:logo_y
            call    invVID_draw_logo_next_slot
            mov     eax,fs:logo_x
            .IF (eax != dword ptr ss:[esp+4])
              ; It changed, we're now where we need to be, let's get our new offset
                add     esp,8
                jmp     try_again
            .ENDIF
          ; It hasn't changed to the next row, so we go ahead and use these values
            sub     fs:logo_x,ebx
            add     esp,8
        .ELSEIF (bl == 2)
          ; Make sure there's enough room on this line for a triple-wide on the current line
            mov     ebx,60
            jmp     try_this_slot
        .ELSEIF (bl == 3)
          ; Make sure there's enough room on this line for a quad-wide on the current line
            mov     ebx,80
            jmp     try_this_slot
        .ELSEIF (bl == 4)
          ; Make sure there's enough room on this line for a quint-wide on the current line
            mov     ebx,100
            jmp     try_this_slot
        .ELSEIF (bl == 5)
          ; Make sure there's enough room on this line for a sex-wide on the current line
            mov     ebx,120
            jmp     try_this_slot
        .ELSEIF (bl == 6)
          ; Make sure there's enough room on this line for a sept-wide on the current line
            mov     ebx,140
            jmp     try_this_slot
        .ELSEIF (bl == 7)
          ; Make sure there's enough room on this line for a oct-wide on the current line
            mov     ebx,160
            jmp     try_this_slot
        .ENDIF

      ; Do the border color
        mov     bl,byte ptr ds:[esi]
        .IF (bl >= 80h)
          ; They want a dark grey box around drawn their logo
            and     bl,01111111b                                ; Turn off the "border" bit

            mov     bh,bl                                       ; Get the color of the border into bh
            shr     bh,3
            add     bh,20h                                      ; To get to our appropriate palette

            pushad
            sub     edi,641
            and     bl,0111b
            mov     ecx,20
            .IF (bl == 1)
              ; It's a double-wide
                mov     ecx,40
            .ELSEIF (bl == 2)
              ; It's a tripple-wide
                mov     ecx,60
            .ELSEIF (bl == 3)
              ; It's a quad-wide
                mov     ecx,80
            .ELSEIF (bl == 4)
              ; It's a quint-wide
                mov     ecx,100
            .ELSEIF (bl == 5)
              ; It's a sex-wide
                mov     ecx,120
            .ELSEIF (bl == 6)
              ; It's a sept-wide
                mov     ecx,140
            .ELSEIF (bl == 7)
              ; It's a oct-wide
                mov     ecx,160
            .ENDIF

          ; Draw the top and bottom
            push    ecx
            .WHILE (ecx > 0)
                mov     byte ptr es:[edi+ecx-1],bh
                mov     byte ptr es:[edi+ecx+(19*320)-1],bh
                dec     ecx
            .ENDW
            pop     ecx

          ; Draw the sides
            add     edi,320
            xor     eax,eax
            .WHILE (eax < 19)
                mov     byte ptr es:[edi],bh
                mov     byte ptr es:[edi+ecx-1],bh
                add     edi,320
                inc     eax
            .ENDW

            popad
        .ENDIF
        and     bl,0111b

      ; Physically draw the logo
        inc     esi
        mov     ecx,16
      @@:
            push    ecx
            push    edi
            mov     ecx,18
            .IF (bl != 0)
                .IF (bl == 1)
                  ; Multiply by 2
                    mov     ecx,18 + (20*1)
                .ELSEIF (bl == 2)
                  ; Multiply by 3
                    mov     ecx,18 + (20*2)
                .ELSEIF (bl == 3)
                  ; Multiply by 4
                    mov     ecx,18 + (20*3)
                .ELSEIF (bl == 4)
                  ; Multiply by 5
                    mov     ecx,18 + (20*4)
                .ELSEIF (bl == 5)
                  ; Multiply by 6
                    mov     ecx,18 + (20*5)
                .ELSEIF (bl == 6)
                  ; Multiply by 7
                    mov     ecx,18 + (20*6)
                .ELSEIF (bl == 7)
                  ; Multiply by 8
                    mov     ecx,18 + (20*7)
                .ENDIF
            .ENDIF
            .REPEAT
                mov     al,byte ptr ds:[esi]
                .IF (al >= 10h)
                    sub     al,10h
                    .IF (al > 3)
                      ; This palette value is not valid, default to black
                        xor     al,al
                    .ELSE
                        add     al,fs:next_custom_palette
                        .IF (al > fs:highest_palette)
                            mov     fs:highest_palette,al
                        .ENDIF
                    .ENDIF
                .ELSE
                    add     al,20h
                .ENDIF
                mov     byte ptr es:[edi],al
                inc     esi
                inc     edi
            .UNTILCXZ
            pop     edi
            add     edi,320
            pop     ecx
        dec     ecx
        jnz     @B

      ;; Update the custom palettes (if any)
        .IF (fs:highest_palette != 0)
          ; There are some, let's do 'em!
            mov     al,fs:next_custom_palette
            xor     ecx,ecx
            .WHILE (al <= fs:highest_palette && ecx < 4)
                push    eax

                mov     edx,RAMDAC_INDEX_WRITE
                out     dx,al
                call    invWait_a_bit

                mov     edx,RAMDAC_DATA
                mov     al,byte ptr ds:[esi]
                inc     esi
                out     dx,al
                call    invWait_a_bit
                mov     al,byte ptr ds:[esi]
                inc     esi
                out     dx,al
                call    invWait_a_bit
                mov     al,byte ptr ds:[esi]
                inc     esi
                out     dx,al
                call    invWait_a_bit

                pop     eax
                inc     ecx
                inc     al
            .ENDW
            mov     fs:next_custom_palette,al
        .ENDIF

      ;; Move to the next location (for the next logo)
        .IF (bl == 0)
            add     fs:logo_x,20
        .ELSEIF (bl == 1)
            add     fs:logo_x,40
        .ELSEIF (bl == 2)
            add     fs:logo_x,60
        .ELSEIF (bl == 3)
            add     fs:logo_x,80
        .ELSEIF (bl == 4)
            add     fs:logo_x,100
        .ELSEIF (bl == 5)
            add     fs:logo_x,120
        .ELSEIF (bl == 6)
            add     fs:logo_x,140
        .ELSEIF (bl == 7)
            add     fs:logo_x,160
        .ENDIF
        call    invVID_draw_logo_next_slot
        popad
        pop     fs
        pop     es
        retf
    VID_draw_logo   ENDP



    invVID_draw_logo_next_slot      PROC
    ; This routine is called to move to the next location for the next logo
    ;
    ; Upon entry:   fs:logo_x = desired next X value
    ;               fs:logo_y = desired next Y value
    ;
    ; Upon exit:    If this will be off the screen the values are changed to the next logical line down, and if the next logical
    ;               line down will be off the screen then the logo area is scrolled up to make room
    ;
        pushad
        .IF (fs:logo_x >= 320)
            mov     fs:logo_x,0
            add     fs:logo_y,320*20
            .IF (fs:logo_y >= 320*60)
              ; We've gone past 3 full lines (we need to scroll everything up)
                mov     esi,320*140 + 320*20
                mov     edi,320*140
                mov     ecx,320*40 / 4
                .REPEAT
                    mov     eax,dword ptr es:[esi]
                    mov     dword ptr es:[edi],eax
                    add     esi,4
                    add     edi,4
                .UNTILCXZ

              ; Clear off the bottom part of the screen
                mov     ecx,320*20 / 4
                mov     eax,20202020h
                .REPEAT
                    mov     dword ptr es:[edi],eax
                    add     edi,4
                .UNTILCXZ
                sub     fs:logo_y,320*20
            .ENDIF
        .ENDIF
        popad
        ret
    invVID_draw_logo_next_slot      ENDP




    VID_g_fill_rectangle        PROC
    ; This routine is called to fill a rectangle area of the screen with a particular color
    ;
    ; Upon entry:   The stack is arranged as below
    ;
    ; Upon exit:    The rectangle is filled
    ;
      ; [ebp+28], dword, top
      ; [ebp+24], dword, left
      ; [ebp+20], dword, width
      ; [ebp+16], dword, height
      ; [ebp+12], dword, color
      ; [ebp+08], dword, cs
      ; [ebp+04], dword, eip
      ; [ebp+00], dword, ebp
        enter   0,0
        push    ds

        mov     ds,cs:data_segment
        .IF (ds:horizontal_pixels == 320 && ds:vertical_pixels == 200)
          ; We're in 320x200 mode
            .IF (dword ptr ss:[ebp+28] < 320 && dword ptr ss:[ebp+20] != 0 && dword ptr ss:[ebp+24] < 200 && dword ptr ss:[ebp+16] != 0)
                pushad
                push    es
                mov     ebx,_sGRAPHICS
                mov     es,ebx

              ;; Verify width
                mov     eax,dword ptr ss:[ebp+24]
                add     eax,dword ptr ss:[ebp+20]
                .IF (eax > 320)
                    sub     eax,320
                    sub     dword ptr ss:[ebp+20],eax
                .ENDIF

              ;; Verify height
                mov     ebx,dword ptr ss:[ebp+28]
                add     ebx,dword ptr ss:[ebp+16]
                .IF (ebx > 200)
                    sub     ebx,200
                    sub     dword ptr ss:[ebp+16],ebx
                .ENDIF
              ; Right now, we know the coordinates will fit on the screen

              ;; Determine the starting coordinate in memory
                mov     eax,dword ptr ss:[ebp+28]                   ; (top * 320) + left
                mov     ebx,320
                mul     ebx
                add     eax,dword ptr ss:[ebp+24]
                mov     edi,eax
              ; Right now, es:[edi] - far ptr to starting point in memory

              ;; Draw the rectangle
                mov     edx,dword ptr ss:[ebp+16]
                mov     eax,dword ptr ss:[ebp+12]
                mov     ebx,edi
              @@:
                mov     edi,ebx
                mov     ecx,dword ptr ss:[ebp+20]
                add     ebx,cs:horizontal_pixels
                rep     stosb
                dec     edx
                jnz     @B

                pop     es
                popad
            .ELSE
                stc
            .ENDIF
        .ELSE
            stc
        .ENDIF

        pop     ds
        leave
        retf 20
    VID_g_fill_rectangle        ENDP




    VID_g_derive_color      PROC
    ; This routine is used to derive the color based on the current video mode
    ;
    ; Upon entry:   ds:[esi+ebx] - far ptr to RGB color sequence
    ;
    ; Upon exit:    eax - color, packed bytes <byte|byte|byte|byte> as <null|r|g|b> or <null|null|null|color>
    ;
        .IF (cs:bits_per_pixel == 16)
          ; 16 million color mode
            movzx   eax,byte ptr ds:[esi+ebx+_OBJECT_RED]
            shl     eax,8
            mov     al,byte ptr ds:[esi+ebx+_OBJECT_GREEN]
            shl     eax,8
            mov     al,byte ptr ds:[esi+ebx+_OBJECT_BLUE]
          ; Right now, eax = <null|r|g|b>

        .ELSE
          ; Assume 256 color mode
          ; The interactive palette may already be setup for this color, we have to search for it
            push    ds
            pushad

          ; Load the user colors
            mov     al,byte ptr ds:[esi+ebx+_OBJECT_RED]
            mov     ah,byte ptr ds:[esi+ebx+_OBJECT_GREEN]
            mov     dl,byte ptr ds:[esi+ebx+_OBJECT_BLUE]

          ; Begin the comparison
            mov     ds,cs:data_segment
            mov     ebx,offset exodus_interactive_256_start
            .WHILE (ebx < offset exodus_interactive_256_end)
                .IF (byte ptr ds:[ebx+1] == al && byte ptr ds:[ebx+2] == ah && byte ptr ds:[ebx+3] == dl)
                  ; This is it
                    movzx   eax,byte ptr ds:[ebx]
                    mov     dword ptr ss:[esp+28],eax
                    jmp     quit
                .ENDIF
                add     ebx,4
            .ENDW
          ; It wasn't found

          ;; Search for the next available slot in the variable area and use it
            mov     ebx,offset exodus_interactive_256_variable_start
            .WHILE (ebx < offset exodus_interactive_256_end)
                .IF (word ptr ds:[ebx+1] == 0 && byte ptr ds:[ebx+3] == 0)
                  ; This is it
                    mov     byte ptr ds:[ebx+1],al
                    mov     byte ptr ds:[ebx+2],ah
                    mov     byte ptr ds:[ebx+3],dl
                    call    invVID_VGA_set_interactive_palette
                    movzx   eax,byte ptr ds:[ebx]
                    mov     dword ptr ss:[esp+28],eax
                    jmp     quit
                .ENDIF
                add     ebx,4
            .ENDW
          ; There are no free slots

          ;; Find the closest available palette
          ;---------------------------------
int  3
            enter   20,0
          ; [ebp-04] - ptr to closest palette
          ; [ebp-08] - closest difference
          ; [ebp-12] - red value
          ; [ebp-16] - green value
          ; [ebp-20] - blue value
            mov     dword ptr ss:[ebp-04],-1
            mov     dword ptr ss:[ebp-08],-1
            movzx   ecx,al
            mov     dword ptr ss:[ebp-12],ecx
            movzx   ecx,ah
            mov     dword ptr ss:[ebp-16],ecx
            movzx   ecx,dl
            mov     dword ptr ss:[ebp-20],ecx

            mov     esi,offset exodus_interactive_256_variable_start
            .WHILE (ebx < offset exodus_interactive_256_end)
                xor     edi,edi
              ; Red
                movzx   ebx,byte ptr ds:[esi+1]
                sub     ebx,dword ptr ss:[ebp-12]
                .IF (carry?)
                    neg     ebx
                .ENDIF
                add     edi,ebx

              ; Green
                movzx   ebx,byte ptr ds:[esi+2]
                sub     ebx,dword ptr ss:[ebp-16]
                .IF (carry?)
                    neg     ebx
                .ENDIF
                add     edi,ebx

              ; Blue
                movzx   ebx,byte ptr ds:[esi+3]
                sub     ebx,dword ptr ss:[ebp-20]
                .IF (carry?)
                    neg     ebx
                .ENDIF
                add     edi,ebx

              ; See if it's closer
                .IF (edi < dword ptr ss:[ebp-08])
                  ; This one's closer
                    mov     dword ptr ss:[ebp-04],esi
                .ENDIF

              ; Try next one
                add     esi,4
            .ENDW
            mov     esi,dword ptr ss:[ebp-04]
            movzx   eax,byte ptr ds:[esi]
            leave
            mov     dword ptr ss:[esp+28],eax
          ;---------------------------------

          quit:
            popad
            pop     ds
        .ENDIF
        retf
    VID_g_derive_color      ENDP




    VID_g_draw_text     PROC
    ; This routine is used to draw text in the specified font
    ;
    ; Upon exit:    Stack is arranged as below
    ;
    ; Upon entry:   carry? - CLEAR, text was displayed
    ;                          SET, error
    ;
      ; [ebp+60] - dword, top
      ; [ebp+56] - dword, left
      ; [ebp+52] - dword, width
      ; [ebp+48] - dword, height
      ; [ebp+44] - dword, background color
      ; [ebp+40] - dword, foreground color
      ; [ebp+36] - dword, left margin
      ; [ebp+32] - dword, top margin
      ; [ebp+28] - dword, font name ID
      ; [ebp+24] - dword, source ptr segment
      ; [ebp+20] - dword, source ptr offset
      ; [ebp+19] - byte,  --Nuserved
      ; [ebp+18] - byte,  --Nuserved
      ; [ebp+17] - byte,  Bold
      ; [ebp+16] - byte,  Dither
      ; [ebp+15] - byte,  Italics
      ; [ebp+14] - byte,  Reverse
      ; [ebp+13] - byte,  Strikethrough
      ; [ebp+12] - byte,  Underline
      ; [ebp+08] - dword, cs
      ; [ebp+04] - dword, eip
      ; [ebp+00] - dword, ebp
        enter   48,0
      ; [ebp-04] - dword, pointer to font
      ; [ebp-08] - dword, total bytes per character (8x14 = 14, for example)
      ; [ebp-12] - dword, character pixel width
      ; [ebp-16] - dword, character pixel height
      ; [ebp-20] - dword, offset to font table
      ; [ebp-24] - dword, count (indicating how far down this character we are)
      ; [ebp-28] - dword, middle of character (for strikethrough)
      ; [ebp-32] - dword, dither pattern
      ; [ebp-36] - dword, italics shift bits
      ; [ebp-40] - dword, temporary italics shift bits
      ; [ebp-44] - dword, italics rollover count (how often the shift is made)
      ; [ebp-48] - dword, temporary italics rollover count
        pushad
        push    ds
        push    es
        push    fs

        .IF (dword ptr ss:[ebp+20] != -1)
            mov     eax,dword ptr ss:[ebp+28]
            test    eax,80000000h
            .IF (!zero?)
              ; It's a fixed point font
                test    eax,10000h
                .IF (!zero?)
                  ; It's a scalable bitmap
                    int  3
                    db  'Scaling bitmap font'
                .ELSE
                  ; It's a fixed bitmap
                    .IF (ax == 0806h)
                      ; 8x6 font
                        mov     dword ptr ss:[ebp-04],offset font_8x6_name
                        mov     eax,2
                        mov     ebx,2
                    .ELSEIF (ax == 0808h)
                      ; 8x8 font
                        mov     dword ptr ss:[ebp-04],offset font_8x8_name
                        mov     eax,3
                        mov     ebx,3
                    .ELSEIF (ax == 080eh)
                      ; 8x14 font
                        mov     dword ptr ss:[ebp-04],offset font_8x14_name
                        mov     eax,3
                        mov     ebx,4
                    .ELSEIF (ax == 0810h)
                      ; 8x16 font
                        mov     dword ptr ss:[ebp-04],offset font_8x16_name
                        mov     eax,3
                        mov     ebx,4
                    .ELSEIF (ax == 1010h)
                      ; 16x16 font
                        mov     dword ptr ss:[ebp-04],offset font_16x16_name
                        mov     eax,3
                        mov     ebx,4
                    .ELSE
                      ; Unrecognized fixed bitmap
                        stc
                        jmp     quit
                    .ENDIF
                    mov     dword ptr ss:[ebp-36],eax
                    mov     dword ptr ss:[ebp-44],ebx

                  ;; Verify width
                    mov     eax,dword ptr ss:[ebp+56]               ; left
                    add     eax,dword ptr ss:[ebp+52]               ; +width
                    add     eax,dword ptr ss:[ebp+36]               ; +left margin
                    .IF (eax > cs:horizontal_pixels)
                        sub     eax,cs:horizontal_pixels
                        sub     dword ptr ss:[ebp+52],eax
                    .ENDIF


                  ;; Verify height
                    mov     ebx,dword ptr ss:[ebp+60]               ; top
                    add     ebx,dword ptr ss:[ebp+48]               ; +height
                    add     ebx,dword ptr ss:[ebp+32]               ; +top margin
                    .IF (ebx > cs:vertical_pixels)
                        sub     ebx,cs:vertical_pixels
                        sub     dword ptr ss:[ebp+48],ebx
                    .ENDIF


                  ;; Apply left margin
                    mov     edx,dword ptr ss:[ebp+36]
                    add     dword ptr ss:[ebp+56],edx
                    sub     dword ptr ss:[ebp+52],edx


                  ;; Apply top margin
                    mov     edx,dword ptr ss:[ebp+32]
                    add     dword ptr ss:[ebp+60],edx
                    sub     dword ptr ss:[ebp+48],edx

                  ; Right now, we know the coordinates will fit on the screen
                  ;; Calculate the starting offset
                    mov     eax,dword ptr ss:[ebp+60]
                    mov     ebx,cs:horizontal_pixels
                    mul     ebx
                    add     eax,dword ptr ss:[ebp+56]
                    mov     edi,eax


                  ;; Calculate variables for the loop
                    mov     esi,dword ptr ss:[ebp-04]               ; Pointer to font information
                    mov     ebx,dword ptr cs:[esi+0]
                    mov     dword ptr ss:[ebp-12],ebx               ; Horizontal pixels per char
                    shr     ebx,3                                   ; Divide by 8
                    mov     eax,dword ptr cs:[esi+4]
                    mov     dword ptr ss:[ebp-16],eax               ; Vertical pixels
                    mul     ebx
                    mov     dword ptr ss:[ebp-08],eax               ; Total bytes per char
                    mov     eax,dword ptr ss:[ebp-16]               ; Vertical pixels
                    shr     eax,1
                    mov     dword ptr ss:[ebp-28],eax               ; Middle of character
                    mov     ebx,dword ptr cs:[esi+8]                ; Offset
                    mov     dword ptr ss:[ebp-20],ebx

                  ;; Verify font height (we're only displaying how ever many pixels there are for this character)
                    mov     ebx,dword ptr cs:[esi+4]
                    .IF (ebx < dword ptr ss:[ebp+48])
                        mov     dword ptr ss:[ebp+48],ebx
                    .ENDIF


                  ;; Display the ext
                    mov     eax,_sGRAPHICS
                    mov     es,eax
                    mov     fs,cs:data_segment
                    mov     ds,dword ptr ss:[ebp+24]
                    mov     esi,dword ptr ss:[ebp+20]
                    mov     dword ptr ss:[ebp-32],1010101010101010b ; Dither bitmap
                  ; Right now, ds:[esi] - far ptr to source string to display
                  ;            es:[edi] - upper-left pixel to start at
                  ;            [ebp+52] - maximum width
                  ;            [ebp+48] - maximum height

                  ;; Display the text
                    mov     dword ptr ss:[ebp-24],0
                    .WHILE (byte ptr ds:[esi] != 0 && dword ptr ss:[ebp+52] > 0)
                        movzx   eax,byte ptr ds:[esi]
                        mul     dword ptr ss:[ebp-08]
                        add     eax,dword ptr ss:[ebp-20]
                        mov     ebx,dword ptr ss:[ebp-36]           ; Reinitialize our italics shift bits
                        mov     dword ptr ss:[ebp-40],ebx
                        mov     ebx,dword ptr ss:[ebp-44]           ; Reinitialize our italics rollover count
                        mov     dword ptr ss:[ebp-48],ebx
                      ; Right now, fs:[eax] - far ptr to the data for this character
                        .IF (dword ptr ss:[ebp-12] == 8)
                          ; It's 8bpp wide
                            .IF (dword ptr ss:[ebp+52] >= 8)
                              ; There's enough room for all of this character
                              display_8:
                                mov     ebx,dword ptr ss:[ebp+48]
                                mov     dword ptr ss:[ebp-24],ebx
                                mov     bl,byte ptr ss:[ebp+44]     ; background color
                                mov     bh,byte ptr ss:[ebp+40]     ; foreground color
                                push    edi
                                .WHILE (dword ptr ss:[ebp-24] > 0)
                                    mov     dl,byte ptr fs:[eax]
                                    inc     eax
                                    mov     ecx,dword ptr ss:[ebp-24]
                                    .IF (byte ptr ss:[ebp+13] != 0 && ecx == dword ptr ss:[ebp-28])
                                      ; It's strikethrough
                                        mov     dl,0ffh
                                    .ENDIF
                                    .IF (ecx == 1 && byte ptr ss:[ebp+12] != 0)
                                      ; It's underline
                                        mov     dl,0ffh
                                    .ENDIF
                                    .IF (byte ptr ss:[ebp+14] != 0)
                                      ; It's reversed
                                        not     dl
                                    .ENDIF
                                    .IF (byte ptr ss:[ebp+16] != 0)
                                      ; It's dithered
                                        and     dl,byte ptr ss:[ebp-32]
                                    .ENDIF
                                    mov     ecx,8
                                    push    edi
                                    .IF (byte ptr ss:[ebp+15] != 0 && byte ptr ds:[esi] >= 32 && byte ptr ds:[esi] <= 122)
                                      ; It's italics
                                        add     edi,dword ptr ss:[ebp-40]               ; Adjust the destination for italics shift
                                      ; See if this will go past the right-border of this character
                                        push    ecx
                                        add     ecx,dword ptr ss:[ebp-40]
                                        .IF (ecx >= dword ptr ss:[ebp+52])
                                          ; We'll go outside of the defined box if we display all the bits
                                            mov     ecx,dword ptr ss:[ebp+52]
                                            sub     ecx,dword ptr ss:[ebp-40]
                                            mov     dword ptr ss:[esp],ecx              ; Adjust ecx on the stack to back off a few
                                        .ENDIF
                                        dec     dword ptr ss:[ebp-48]
                                        .IF (zero?)
                                          ; It's time to shift again
                                            mov     ecx,dword ptr ss:[ebp-44]
                                            dec     dword ptr ss:[ebp-40]
                                            mov     dword ptr ss:[ebp-48],ecx
                                        .ENDIF
                                        pop     ecx
                                    .ELSE
                                        .IF (ecx >= dword ptr ss:[ebp+52])
                                          ; We'll go outside of the defined box
                                            mov     ecx,dword ptr ss:[ebp+52]
                                        .ENDIF
                                    .ENDIF
                                    .REPEAT
                                        rcl     dl,1
                                        .IF (carry?)
                                          ; This bit is set, store it as foreground color
                                            mov     byte ptr es:[edi],bh
                                        .ELSE
                                          ; This bit is clear, store it as background color
                                            mov     byte ptr es:[edi],bl
                                        .ENDIF
                                        inc     edi
                                    .UNTILCXZ
                                    pop     edi
                                  ; Move to next line down on screen
                                    add     edi,cs:horizontal_pixels

                                  ; Move to next line down in the character
                                    dec     dword ptr ss:[ebp-24]

                                  ; Toggle the bits in our dither control byte
                                    not     dword ptr ss:[ebp-32]
                                .ENDW
                                pop     edi
                                add     edi,8                       ; Move horizontally to next character
                                sub     dword ptr ss:[ebp+52],8
                            .ELSE
                              ; Only part of this character can be displayed
                                mov     ecx,dword ptr ss:[ebp+52]
                                mov     dword ptr ss:[ebp-12],ecx
                                jmp     display_8
                            .ENDIF
                        .ELSE
                          ; It's 16bpp wide
                            .IF (dword ptr ss:[ebp+52] >= 16)
                              ; There's enough room for all of this character
                              display_16:
                                mov     ebx,dword ptr ss:[ebp+48]
                                mov     dword ptr ss:[ebp-24],ebx
                                mov     bl,byte ptr ss:[ebp+44]     ; background color
                                mov     bh,byte ptr ss:[ebp+40]     ; foreground color
                                push    edi
                                .WHILE (dword ptr ss:[ebp-24] > 0)
                                    mov     dx,word ptr fs:[eax]
                                    add     eax,2
                                    mov     ecx,dword ptr ss:[ebp-24]
                                    .IF (byte ptr ss:[ebp+13] != 0 && ecx == dword ptr ss:[ebp-28])
                                      ; It's strikethrough
                                        mov     dx,0ffffh
                                    .ENDIF
                                    .IF (ecx == 1 && byte ptr ss:[ebp+12] != 0)
                                      ; It's underline
                                        mov     dx,0ffffh
                                    .ENDIF
                                    .IF (byte ptr ss:[ebp+14] != 0)
                                      ; It's reversed
                                        not     dx
                                    .ENDIF
                                    .IF (byte ptr ss:[ebp+16] != 0)
                                      ; It's dithered
                                        and     dx,word ptr ss:[ebp-32]
                                    .ENDIF
                                    mov     ecx,16
                                    push    edi
                                    .IF (byte ptr ss:[ebp+15] != 0 && byte ptr ds:[esi] >= 32 && byte ptr ds:[esi] <= 122)
                                      ; It's italics
                                        add     edi,dword ptr ss:[ebp-40]               ; Adjust the destination for italics shift
                                      ; See if this will go past the right-border of this character
                                        push    ecx
                                        add     ecx,dword ptr ss:[ebp-40]
                                        .IF (ecx >= dword ptr ss:[ebp+52])
                                          ; We'll go outside of the defined box if we display all the bits with italics shifting
                                            mov     ecx,dword ptr ss:[ebp+52]
                                            sub     ecx,dword ptr ss:[ebp-40]
                                            mov     dword ptr ss:[esp],ecx              ; Adjust ecx on the stack to back off a few
                                        .ENDIF
                                        dec     dword ptr ss:[ebp-48]
                                        .IF (zero?)
                                          ; It's time to shift again
                                            mov     ecx,dword ptr ss:[ebp-44]
                                            dec     dword ptr ss:[ebp-40]
                                            mov     dword ptr ss:[ebp-48],ecx
                                        .ENDIF
                                        pop     ecx
                                    .ELSE
                                        .IF (ecx >= dword ptr ss:[ebp+52])
                                          ; We'll go outside of the defined box
                                            mov     ecx,dword ptr ss:[ebp+52]
                                        .ENDIF
                                    .ENDIF
                                    .REPEAT
                                        rcl     dx,1
                                        .IF (carry?)
                                          ; This bit is set, store it as foreground color
                                            mov     byte ptr es:[edi],bh
                                        .ELSE
                                          ; This bit is clear, store it as background color
                                            mov     byte ptr es:[edi],bl
                                        .ENDIF
                                        inc     edi
                                    .UNTILCXZ
                                    pop     edi
                                  ; Move to next line down on screen
                                    add     edi,cs:horizontal_pixels

                                  ; Move to next line down in the character
                                    dec     dword ptr ss:[ebp-24]

                                  ; Toggle the bits in our dither control byte
                                    not     dword ptr ss:[ebp-32]
                                .ENDW
                                pop     edi
                                add     edi,16                      ; Move horizontally to next character
                                sub     dword ptr ss:[ebp+52],16
                            .ELSE
                              ; Only part of this character can be displayed
                                mov     ecx,dword ptr ss:[ebp+52]
                                mov     dword ptr ss:[ebp-12],ecx
                                jmp     display_16
                            .ENDIF
                        .ENDIF
                      ; Move to next character
                        inc     esi
                    .ENDW
                .ENDIF
            .ELSE
              ; It's a variable pitch font
                int  3
                db  'Variable pitch font'
            .ENDIF
        .ENDIF

      quit:
        pop     fs
        pop     es
        pop     ds
        popad
        leave
        retf 52                                                     ; 13 dwords
    VID_g_draw_text     ENDP




    VID_g_mouse_pointer     PROC
    ; This routine is used to display the mouse pointer
    ;
    ; Upon entry:   The stack is arranged as below
    ;
    ; Upon exit:    The appropriate mouse pointer action is taken
    ;
      ; [ebp+28] - dword, horizontal
      ; [ebp+24] - dword, vertical
      ; [ebp+20] - dword, display mode (0-hide, 1-show)
      ; [ebp+16] - dword, mouse pointer type (Refer to INF\MOUSE.INF or VGA\MOUSE.FNT)
      ; [ebp+12] - dword, offset to store/retrieve mouse pointer data from
      ; [ebp+08] - cs
      ; [ebp+04] - eip
      ; [ebp+00] - ebp
        enter   20,0
      ; [ebp-04] - dword, pixels to skip horizontally (from left)
      ; [ebp-08] - dword, bytes to skip in mouse pointer data to reach first visible line (from top)
      ; [ebp-12] - dword, lines to skip vertically (from top)
      ; [ebp-16] - dword, pixels to skip horizontally (from bottom)
      ; [ebp-20] - dword, lines to skip vertically (from bottom)
        pushad
        push    es
        push    fs
        push    gs


      ;; Make sure the hot-spot coordinates are within the screen
        mov     ebx,_sSYSTEM
        mov     gs,ebx
        movzx   ecx,word ptr gs:[_SYSTEM_VGA_HORIZONTAL]
        movzx   edx,word ptr gs:[_SYSTEM_VGA_VERTICAL]
      ; Horizontal
        .IF (dword ptr ss:[ebp+28] > ecx)
            mov     dword ptr ss:[ebp+28],ecx
        .ENDIF
      ; Vertical
        .IF (dword ptr ss:[ebp+24] > edx)
            mov     dword ptr ss:[ebp+24],edx
        .ENDIF


      ;; Make sure the mouse pointer they've specified is valid
        .IF (dword ptr ss:[ebp+16] > _MAX_VGA_MOUSE_POINTERS)       ; This constant is defined in MOUSE.FNT
            mov     dword ptr ss:[ebp+16],0
        .ENDIF


      ;; Apply the current mouse pointer's hot-spot to the specified mouse coordinates to obtain the starting offset
        mov     fs,cs:data_segment
        mov     eax,dword ptr ss:[ebp+16]                           ; Mouse pointer type
        mov     ecx,eax
        imul    eax,16*20
        shl     ecx,3                                               ; Multiply by 8 (to get past extra header bytes (8 each))
        add     eax,ecx
        mov     ebx,eax
        add     ebx,offset vga_mouse_0
      ; Right now, fs:[ebx] - far ptr to base of correct mouse pointer based on info specified
        mov     eax,dword ptr fs:[ebx+0]                            ; Horizontal hot spot coords
        mov     edx,dword ptr fs:[ebx+4]                            ; Vertical hot spot coords
        add     ebx,8
        sub     dword ptr ss:[ebp+28],eax
        sub     dword ptr ss:[ebp+24],edx
      ; Right now, the horizontal and vertical coordinates are adjusted
      ;            fs:[ebx] - far ptr to mouse font


      ;; Verify mouse pointer is still fully on-screen after applying hot-spot coords
        mov     dword ptr ss:[ebp-04],0
        mov     dword ptr ss:[ebp-16],0
        .IF (dword ptr ss:[ebp+28] > 7fffffffh)
          ; Horizontal is negative, we have to skip a few pixels (edx tells us how many)
            mov     edx,dword ptr ss:[ebp+28]
            neg     edx
            mov     dword ptr ss:[ebp-04],edx
            mov     dword ptr ss:[ebp+28],0                         ; And tell it to begin at visible
        .ENDIF
        mov     edx,dword ptr ss:[ebp+28]
        mov     eax,16
        sub     eax,dword ptr ss:[ebp-04]
        add     edx,eax
        movzx   ecx,word ptr gs:[_SYSTEM_VGA_HORIZONTAL]
        .IF (edx > ecx)
          ; We'll go off the right side of the screen
            sub     edx,ecx
            mov     dword ptr ss:[ebp-16],edx
        .ENDIF

      ; Verify vertical
        mov     dword ptr ss:[ebp-08],0
        mov     dword ptr ss:[ebp-12],0
        mov     dword ptr ss:[ebp-20],0
        .IF (dword ptr ss:[ebp+24] > 7fffffffh)
          ; Vertical is negative, we have to skip a few lines (edx tells us how many bytes to skip (16 bytse per line))
            mov     edx,dword ptr ss:[ebp+24]
            neg     edx
            mov     dword ptr ss:[ebp-12],edx                       ; Store # of lines
            shl     edx,4                                           ; Multiply by 16 (to get the number of bytes to skip)
            mov     dword ptr ss:[ebp-08],edx
            mov     dword ptr ss:[ebp+24],0                         ; And tell it to begin at visible
        .ENDIF
        mov     edx,dword ptr ss:[ebp+24]
        mov     eax,20
        sub     eax,dword ptr ss:[ebp-12]
        add     edx,eax
        movzx   ecx,word ptr gs:[_SYSTEM_VGA_VERTICAL]
        .IF (edx > ecx)
          ; We'll go off the bottom of the screen
            sub     edx,ecx
            mov     dword ptr ss:[ebp-20],edx
        .ENDIF


      ;; Compute the starting offset in memory
        movzx   ecx,word ptr gs:[_SYSTEM_VGA_HORIZONTAL]
        mov     edx,_sGRAPHICS
        mov     es,edx
        mov     eax,dword ptr ss:[ebp+24]
        mul     ecx
        add     eax,dword ptr ss:[ebp+28]
        mov     edi,eax
      ; Right now, es:[edi] - far ptr to upper-left corner of mouse coordinate
        mov     esi,dword ptr ss:[ebp+12]                           ; Where to store/retrieve the bitmap
        mov     edx,dword ptr ss:[ebp-04]                           ; Apply pixels to skip each horizontal line
        add     ebx,dword ptr ss:[ebp-08]
        mov     ecx,20
        sub     ecx,dword ptr ss:[ebp-12]
        sub     ecx,dword ptr ss:[ebp-20]
        add     ebx,edx
        .WHILE (ecx > 0)
            push    ecx
            push    edi

            mov     ecx,16
            sub     ecx,edx                                         ; number of pixels to display
            sub     ecx,dword ptr ss:[ebp-16]
            .IF (dword ptr ss:[ebp+20] == 1)
              ; We're putting from the screen to the buffer and writing the mouse pointer
                push    ebx
                .WHILE (ecx > 0)
                  ; Store the data that's currently on the screen to the buffer
                    mov     al,byte ptr es:[edi]
                    mov     byte ptr ds:[esi],al
                    inc     esi

                  ; Write the mouse pixel
                    mov     al,byte ptr fs:[ebx]
                    .IF (al != 254)
                        stosb
                    .ELSE
                        inc     edi
                    .ENDIF
                    dec     ecx
                    inc     ebx
                .ENDW
                pop     ebx
                add     ebx,16                                          ; Move to next line

            .ELSE
              ; We're putting from the buffer to the screen
                rep     movsb                                       ; Move from save buffer to screen
            .ENDIF

            movzx   eax,word ptr gs:[_SYSTEM_VGA_HORIZONTAL]
            pop     edi
            pop     ecx
            add     edi,eax
            dec     ecx
        .ENDW

        pop     gs
        pop     fs
        pop     es
        popad
        leave
        retf 20
    VID_g_mouse_pointer     ENDP