; todo.asp
;
; Low-Level Debi Debugger algorithms still left to complete
;
;









    null_function       PROC
    ; This function doesn't do anything.  It is used where a function definition is required, but not necessary.
    ;
    ; Upon entry:   Doesn't matter
    ;
    ; Upon exit:    Returns everything exactly as it was prior to calling
    ;
        ret
    null_function       ENDP




    invDEBI_button      PROC
        ret
    invDEBI_button      ENDP




    invDEBI_checkbox        PROC
        ret
    invDEBI_checkbox        ENDP




    invDEBI_CFSCA_kbd_handler       PROC
        ret
    invDEBI_CFSCA_kbd_handler       ENDP









;-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
;
; Text displayed while hovering over an object
;
; ----
; Common to all of the below sub-routines.  This information is passed to each of them.
;
; Upon entry:   ds:[esi] - far ptr to screen object
;               ds:[edi] - far ptr to mouse object
;
; Upon exit:    Information about this opcode is displayed
;
;
;-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    invDEBI_descriptor_hover        PROC
        call    invDEBI_quick_watch_add_divider
        ret
    invDEBI_descriptor_hover        ENDP




    invDEBI_quick_watch_mem_32      PROC
        call    invDEBI_quick_watch_add_divider
        ret
    invDEBI_quick_watch_mem_32      ENDP




    invDEBI_quick_watch_mem_8       PROC
        call    invDEBI_quick_watch_add_divider
        ret
    invDEBI_quick_watch_mem_8       ENDP




    invDEBI_quick_watch_show_EBP_relative_80        PROC
        call    invDEBI_quick_watch_add_divider
        ret
    invDEBI_quick_watch_show_EBP_relative_80        ENDP




    invDEBI_quick_watch_show_EBP_relative_eflags        PROC
        call    invDEBI_quick_watch_add_divider
        ret
    invDEBI_quick_watch_show_EBP_relative_eflags        ENDP




    invDEBI_quick_watch_show_selector       PROC
        call    invDEBI_quick_watch_add_divider
        ret
    invDEBI_quick_watch_show_selector       ENDP




    invDEBI_quick_watch_mem_ascii_8     PROC
        call    invDEBI_quick_watch_add_divider
        ret
    invDEBI_quick_watch_mem_ascii_8     ENDP




    invDEBI_quick_watch_show_EBP_relative_64        PROC
        call    invDEBI_quick_watch_add_divider
        ret
    invDEBI_quick_watch_show_EBP_relative_64        ENDP




    invDEBI_quick_watch_show_32_selector_separated      PROC
        call    invDEBI_quick_watch_add_divider
        ret
    invDEBI_quick_watch_show_32_selector_separated      ENDP




    invDEBI_object_close        PROC
    ; This routine is calld when they want to remove an object from the screen
    ;
    ; Upon entry:   ds:[esi] - far ptr to screen table item
    ;
    ; Upon exit:    If the item is alterable, then it is closed
    ;
        .IF (byte ptr ds:[esi+_ST_OBJECT_ALTERABLE] == _YES)
            mov     byte ptr ds:[esi+_ST_OBJECT_ACTIVE],_NO
            call    invDEBI_clear_screen_and_redraw_windows
        .ENDIF
        ret
    invDEBI_object_close        ENDP
;-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
;
; END - Text displayed while hovering over an object
;
;-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=









;-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
;
; SCREEN OBJECT handlers
;
; -----
; The following routines are all called with these parameters
; Upon entry:   The stack is arranged as below
;               ds:[esi] - ptr to screen table structure
;               ds:[edi] - ptr to this item's objects (which is the @FunctionHandlesIt macro)
;
;-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    invDEBI_pop_line_mem_window_float32         PROC
    ; This routine is called to display a line of data in a FLOAT32 format
        call    invDEBI_pop_line_show_displacement
        ret
    invDEBI_pop_line_mem_window_float32         ENDP




    invDEBI_pop_line_mem_window_float64         PROC
    ; This routine is called to display a line of data in a FLOAT64 format
        call    invDEBI_pop_line_show_displacement
        ret
    invDEBI_pop_line_mem_window_float64         ENDP




    invDEBI_pop_line_mem_window_float80         PROC
    ; This routine is called to display a line of data in a FLOAT80 format
        call    invDEBI_pop_line_show_displacement
        ret
    invDEBI_pop_line_mem_window_float80         ENDP




    invDEBI_quick_watch_window      PROC
    ; This routine is called when updating the screen.  It is called from the @FunctionHandlesObject macro
    ;
    ; Upon entry:   ds:[esi] - far ptr to screen info
    ;               ds:[edi] - far ptr to function handle
    ;
    ; Upon exit:    Nothing
    ;
        ret
    invDEBI_quick_watch_window      ENDP
;-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
;
; END - SCREEN OBJECT handlers
;
;-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=









;-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
;
; CASK clicking
;
; -----
; The following routines are all called with these parameters
; Upon entry:   The stack is arranged as below
;               ds:[esi] - ptr to screen table structure
;               ds:[edi] - ptr to this item's objects
;
;-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    invDEBI_center_item_around_mouse    PROC
    ; This routine is used to center the object around the current mouse coordinates
    ;
    ; Upon entry:   ds:[esi] - far ptr to screen object (_ST_xxx structure)
    ;                    eax - width of item
    ;                    edx - height of item
    ;
    ; Upon exit:    ds:[esi+_ST_OBJECT_UL_HORIZONTAL] - updated
    ;               ds:[esi+_ST_OBJECT_UL_VERTICAL]   - updated
    ;
        push    eax
        push    ecx
        push    edx

      ; Do X
        mov     ecx,ds:mouse_current_x
        shr     eax,1
        sub     ecx,eax
        .IF (sign?)
          ; It's negative
            xor     ecx,ecx
        .ENDIF
        mov     dword ptr ds:[esi+_ST_OBJECT_UL_HORIZONTAL],ecx

      ; Do Y
        mov     ecx,ds:mouse_current_y
        shr     edx,1
        sub     ecx,edx
        .IF (sign?)
          ; It's negative
            xor     ecx,ecx
        .ENDIF
        mov     dword ptr ds:[esi+_ST_OBJECT_UL_VERTICAL],ecx

        pop     edx
        pop     ecx
        pop     eax
        ret
    invDEBI_center_item_around_mouse    ENDP




    invDEBI_address_expression      PROC
    ; This routine is used to input an address expression for a mem.x window
    ;
    ; Upon entry:   ds:[esi] - far ptr to screen object
    ;               ds:[edi] - far ptr to mouse object which called this function
    ;
    ; Upon exit:    This sets up the conditions whereby the address can be updated
    ;
        pushad
        push    es
      ; Save this information
        mov     ds:exp_esi,esi
        mov     ds:exp_edi,edi

      ; Setup the input field
        mov     eax,_sDEBI_memory 
        mov     es,eax
        .IF (dword ptr ds:[esi+_ST_MEMVAR_OFFSET] == -1)
          ; No memory has yet been defined for this item, so we set it up here (only done once per mem.x window)
            mov     ebx,es:[0]
            mov     dword ptr ds:[esi+_ST_MEMVAR_OFFSET],ebx
            mov     edi,offset DEBI_exp_memvar_list
            xor     ecx,ecx
          ; Right now,      ebx - offset in _sDEBI_memory where these memory variables will go
          ;            ds:[edi] - far ptr to DEBI_exp_memvar_list (which tells us what variables get stored where)
          ;            ds:[esi] - far ptr to the mem.x screen object which called this routine
          ;                 ecx - used as a count below (to determine how much to add to ebx (for next offset))
          ;              es:[0] - (ebx) current offset into _sDEBI_memory
            .WHILE (dword ptr ds:[edi+_MEMVAR_MEMORY_VARIABLE] != -1)
                add     ecx,dword ptr ds:[edi+_MEMVAR_LENGTH]
                mov     eax,ecx
              ; Initialize as we go
                .WHILE (eax > 0)
                    mov     byte ptr es:[ebx],32
                    inc     ebx
                    dec     eax
                .ENDW
                add     edi,_MEMVAR_STRUCT_LENGTH
            .ENDW
            add     dword ptr es:[0],ecx                            ; Increase offset for next window
        .ENDIF

      ; Copy the string that's there to our temporary input variables
        pushfd
        mov     esi,dword ptr ds:[esi+_ST_MEMVAR_OFFSET]
        mov     ebx,offset DEBI_exp_memvar_list
        call    invDEBI_from_object_memvar

      ; Save the current screen
        cli
        call    invDEBI_hide_mouse_pointer
        call    invDEBI_turn_cursor_off
        call    invDEBI_save_screen2

      ; Display the window
        mov     esi,offset exp_screen_object
        mov     ds:screen_object,esi
        mov     edi,offset exp_screen_screen_objects
        mov     eax,_EXP_SCREEN_WIDTH * FONT_X
        mov     edx,_EXP_SCREEN_HEIGHT * FONT_Y
        call    invDEBI_center_item_around_mouse
        call    invDEBI_draw_objects                                ; Draw the window

      ; Setup the input
        mov     ds:kbd_object,offset exp_screen_keyboard_top_object
        mov     ds:mouse_objects,offset exp_screen_mouse_objects
        mov     ds:object_mode,1                                    ; Indicate we're no longer processing defaults
        call    invDEBI_setFocus
        call    invDEBI_screen_refresh
        popfd

        pop     es
        popad
        ret
    invDEBI_address_expression      ENDP




    invDEBI_store_hex_address_in_eax        PROC
    ; This routine is used to store the hexidecimal address stored in eax into the current string
    ;
    ; Upon entry:       eax - 32-bit address
    ;              ds:[esi] - where the address will be stored
    ;
    ; Upon exit:    Address is stored like "0x12345678"
    ;
        push    ecx
        push    edx

        mov     word ptr ds:[esi],'x0'
        add     esi,2
        mov     ecx,8
      @@:
        rol     eax,4
        mov     dl,al
        and     dl,0fh
        .IF (dl <= 9)
            add     dl,'0'
        .ELSE
            add     dl,'a'-10
        .ENDIF
        mov     byte ptr ds:[esi],dl
        inc     esi
        loop    @B

        pop     edx
        pop     ecx
        ret
    invDEBI_store_hex_address_in_eax        ENDP




    invDEBI_store_bytes_in_eax      PROC
    ; This routine is used to store bytes from eax into the current string
    ;
    ; Upon entry:       eax - contains something like "  ds"
    ;              ds:[esi] - where "ds" will be stored
    ;
    ; Upon exit:    Any characters after the first non-space are stored
    ;
        push    ecx
        push    ebx

        mov     ecx,4
        xor     ebx,ebx
      @@:
        rol     eax,8
        .IF (al != 32 || ebx != 0)
            mov     ebx,1
            mov     byte ptr ds:[esi],al
            inc     esi
        .ENDIF
        loop    @B

        pop     ebx
        pop     ecx
        ret
    invDEBI_store_bytes_in_eax      ENDP




    invDEBI_quick_watch_click       PROC
;    ; This routine forces a redraw of the t_and_s_logo image
;        mov     ds:t_and_s_displayed,0
;        call    invDEBI_quick_watch_window
        ret
    invDEBI_quick_watch_click       ENDP
;-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
;
; END - CASK clicking
;
;-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=









;-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
;
; EDITING
;
;-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    invDEBI_edit_variable       PROC
        ret
    invDEBI_edit_variable       ENDP



    invDEBI_kbd_handler     PROC
    ; This is the default keyboard handler for DEBI
    ;
    ; Upon entry:   eax - key pressed
    ;               ebx - keyboard flags
    ;
    ; Upon exit:    Internal flags are raised, or the key is ignored if not recognized
    ;
        .IF (ax == F5)
          ; F5 (go)
            mov     ds:debi_ok_to_quit,2
        .ELSEIF (ax == F8)
          ; F8 (single step)
          single_step:
            mov     ds:debi_ok_to_quit,1
        .ELSEIF (ax == F10)
          ; F10 (step over)
          try_again:
            mov     ebx,ds:instruction_offset
            push    ds
            mov     ds,dword ptr ss:[ebp+56]
            mov     ax,word ptr ds:[ebx]
            mov     dx,ax
            shr     ah,3
            and     ah,111b
            pop     ds
            .IF (al != 09ah && al != 0e8h && al != 0cch && al != 0cdh && al != 0ceh && !(al == 0ffh && (ah == 010b || ah == 011b)))
              ; This instruction is not a CALL/INT3/INTO/INT x instruction, so we just single-step because it
              ; will have the same effect
              ; But, check certain conditions
                .IF (al == 0f2h || al == 0f3h)
                  ; it's a REP prefix
                    .IF (dh >= 0a4h && dh <= 0afh && dh != 0a8h && dh != 0a9h)
                      ; It's part of a proper REP XXX instruction combination
                        inc     ebx
                        jmp     @F
                    .ENDIF
                .ELSEIF (al == 0f0h || al == 26h || al == 2eh || al == 36h || al == 3eh || al == 64h || al == 65h || al == 66h || al == 67h)
                  ; it's an LOCK(0f0h) or override prefix
                    inc     ds:instruction_offset
                    dec     ds:instruction_length
                    jmp     try_again
                .ENDIF
                jmp     single_step
            .ELSE
              ; Right now, ebx is the offset of the next instruction
              @@:
                add     ebx,ds:instruction_length
                mov     ds:step_offset,ebx
              ; Get the base/limit for this code segment
                mov     eax,'get '
                mov     ebx,'gdtc'
                mov     edx,dword ptr ss:[ebp+56]
                shr     edx,3
                call    fword ptr cs:_EXODUS_requestor
                .IF (!carry?)
                  ; Set a data segment that's the same base/limit as the code segment
                    mov     esi,ebx
                    mov     edi,edx
                    mov     eax,'set '
                    mov     ebx,'gdtd'
                    mov     edx,_sDEBI_temp / 8
                    call    fword ptr cs:_EXODUS_requestor
                    .IF (!carry?)
                      ; Right now, _sDEBI_temp is a data segment to the code segment that's being debugged
                        mov     ebx,ds:step_offset
                        push    fs
                        mov     eax,_sDEBI_temp
                        mov     fs,eax
                        mov     al,byte ptr fs:[ebx]
                        mov     byte ptr fs:[ebx],0cch
                        mov     ds:step_replaced_byte,al
                        pop     fs
                        mov     ds:step_over,1
                        mov     ds:debi_ok_to_quit,3
                    .ENDIF
                .ENDIF
            .ENDIF
        .ENDIF
        ret
    invDEBI_kbd_handler     ENDP
;-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
;
; END - EDITING
;
;-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=


;break_here  proc
;    push    ds
;    mov     ds,cs:data_segment
;    mov     ds:object_mode,0
;    mov     ds:kbd_focus,-1
;    pop     ds
;    int 3
;    ret
;break_here  endp