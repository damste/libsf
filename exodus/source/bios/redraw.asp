; redraw.asp
;
; Exodus BIOS Object Handler - Object redraw algorithms
;
;





    iOBJECT_redraw_task         PROC
    ; This routine is called when the entire task's objects need to be redrawn
    ;
    ; Upon entry:   gs:[edi] - far ptr to this task's structure
    ;
    ; Upon exit:    All objects for this task are re-drawn
    ;
        pushad
        push    ds

        mov     ds,dword ptr gs:[edi+_TASK_ENTRY_SELECTOR_OBJECTS]
        mov     esi,dword ptr ds:[_OBJECT_HEADER_FIRST_BASE_OBJECT]
        .WHILE (esi != -1)
          ; Display this base object
            call    invOBJECT_redraw_base_object
            .IF (!carry?)
              ; Now, draw any objects on it
                push    esi
                push    edi

                mov     edi,esi
                mov     esi,dword ptr ds:[esi+_OBJECT_FIRST_OBJECT]
                .WHILE (esi != -1)
                    call    invOBJECT_redraw_object
                    mov     esi,dword ptr ds:[esi+_OBJECT_NEXT_OBJECT]
                .ENDW

                pop     edi
                pop     esi
            .ENDIF

          ; Move to the next base object
            mov     esi,dword ptr ds:[esi+_OBJECT_NEXT_BASE_OBJECT]
        .ENDW
      ; Right now, all base objects and objects have been redrawn (everything's been brought to the front)

      ;; Now, redraw the base object and objects that currently have focus (to bring them to the very front

        pop     ds
        popad
        retf
    iOBJECT_redraw_task         ENDP




    invOBJECT_redraw_base_object        PROC
    ; This routine is used to redraw a base object.  When it is called it is known that the entire object should be redrawn
    ; completely overlaying whatever is underneath the area it will inhabit on the screen.
    ;
    ; Upon entry:   ds:[esi] - far ptr to base object
    ;
    ; Upon exit:    The base object is redrawn (if it has visual components)
    ;
        mov     al,byte ptr ds:[esi+_BASE_OBJECT_TYPE]
        .IF (al == _DESKTOP)
          ; It's a desktop item
            call    invOBJECT_redraw_desktop
        .ELSEIF (al == _WINDOW)
          ; It's a window item
            call    invOBJECT_redraw_window
        .ELSEIF (al == _CONSOLE)
          ; It's a console item
            call    invOBJECT_redraw_console
        .ELSEIF (al == _MONO_DESKTOP)
          ; It's a desktop item (on the mono monitor)
            call    invOBJECT_redraw_mono_desktop
        .ELSEIF (al == _MONO_WINDOW)
          ; It's a window item (on the mono monitor)
            call    invOBJECT_redraw_mono_window
        .ELSEIF (al == _MONO_CONSOLE)
          ; It's a console item (on the mono monitor)
            call    invOBJECT_redraw_mono_console
        .ENDIF
        ret
    invOBJECT_redraw_base_object        ENDP




    invOBJECT_redraw_desktop        PROC
    ; This routine is called to redraw a desktop object
    ;
    ; Upon entry:   ds:[esi] - far ptr to desktop object
    ;
    ; Upon exit:    The object is redrawn
    ;               carry? - Object is not currently visible
    ;
        .IF (dword ptr ds:[esi+_BO_D_VISIBLE] != 0)
            .IF (dword ptr ds:[esi+_BO_D_WALLPAPER] == -1)
              ; No wallpaper, just a color
                pushfd
                push    dword ptr ds:[esi+_BO_D_TOP]
                push    dword ptr ds:[esi+_BO_D_LEFT]
                push    dword ptr ds:[esi+_BO_D_WIDTH]
                push    dword ptr ds:[esi+_BO_D_HEIGHT]
                mov     ebx,_BO_D_BACKGROUND
                call    fword ptr cs:_VID_g_derive_color
                push    eax
                cli
                call    fword ptr cs:_VID_g_fill_rectangle
                popfd
                clc
            .ELSE
              ; Wallpaper
                int  3
                db  'Wallpaper algorithm for desktop'
            .ENDIF
        .ELSE
            stc
        .ENDIF
        ret
    invOBJECT_redraw_desktop        ENDP




    invOBJECT_redraw_window     PROC
    ; This routine is called to redraw a window object
    ;
    ; Upon entry:   ds:[esi] - far ptr to window object
    ;
    ; Upon exit:    The object is redrawn
    ;               carry? - Object is not currently visible
    ;
        ret
    invOBJECT_redraw_window     ENDP




    invOBJECT_redraw_console    PROC
    ; This routine is called to redraw a console object
    ;
    ; Upon entry:   ds:[esi] - far ptr to console object
    ;
    ; Upon exit:    The object is redrawn
    ;               carry? - Object is not currently visible
    ;
        ret
    invOBJECT_redraw_console    ENDP




    invOBJECT_redraw_mono_desktop       PROC
    ; This routine is called to redraw a mono desktop object
    ;
    ; Upon entry:   ds:[esi] - far ptr to mono desktop object
    ;
    ; Upon exit:    The object is redrawn
    ;               carry? - Object is not currently visible
    ;
        ret
    invOBJECT_redraw_mono_desktop       ENDP




    invOBJECT_redraw_mono_window        PROC
    ; This routine is called to redraw a mono window object
    ;
    ; Upon entry:   ds:[esi] - far ptr to mono window object
    ;
    ; Upon exit:    The object is redrawn
    ;               carry? - Object is not currently visible
    ;
        ret
    invOBJECT_redraw_mono_window        ENDP




    invOBJECT_redraw_mono_console       PROC
    ; This routine is called to redraw a mono console object
    ;
    ; Upon entry:   ds:[esi] - far ptr to mono console object
    ;
    ; Upon exit:    The object is redrawn
    ;               carry? - Object is not currently visible
    ;
        ret
    invOBJECT_redraw_mono_console       ENDP




    invOBJECT_redraw_object     PROC
    ; This routine is used
    ;
    ; Upon entry:   ds:[esi] - far ptr to object
    ;
    ; Upon exit:    The object is redrawn (if it has visual components)
    ;
        mov     al,byte ptr ds:[esi+_OBJECT_TYPE]
        .IF (al == _INPUT_FIELD)
          ; It's a input field
            call    invOBJECT_redraw_input_field
        .ELSEIF (al == _TEXT_FIELD)
          ; It's a text field
            call    invOBJECT_redraw_text_field
        .ELSEIF (al == _BUTTON)
          ; It's a button
            call    invOBJECT_redraw_button
        .ELSEIF (al == _MENU_BAR)
          ; It's a menu bar
            call    invOBJECT_redraw_menu_bar
        .ELSEIF (al == _MENU_POPUP)
          ; It's a menu popup
            call    invOBJECT_redraw_popup
        .ELSEIF (al == _RADIO_DIAL)
          ; It's a radio dail
            call    invOBJECT_redraw_radio_dial
        .ELSEIF (al == _CHECK_BOX)
          ; It's a check box
            call    invOBJECT_redraw_check_box
        .ELSEIF (al == _CIRCLE_BOX)
          ; It's a circle box
            call    invOBJECT_redraw_circle_box
        .ELSEIF (al == _PULLDOWN)
          ; It's a pulldown
            call    invOBJECT_redraw_pulldown
        .ELSEIF (al == _SLIDE_BAR)
          ; It's a slide bar
            call    invOBJECT_redraw_slide_bar
        .ELSEIF (al == _PERCENT_BAR)
          ; It's a percent bar
            call    invOBJECT_redraw_percent_bar
        .ELSEIF (al == _TRAY)
          ; It's a tray
            call    invOBJECT_redraw_tray
        .ELSEIF (al == _ICON)
          ; It's an icon
            call    invOBJECT_redraw_icon
        .ELSEIF (al == _BITMAP)
          ; It's a bitmap
            call    invOBJECT_redraw_bitmap
        .ELSEIF (al == _HLINE)
          ; It's a horizontal line
            call    invOBJECT_redraw_horizontal_line
        .ELSEIF (al == _VLINE)
          ; It's a vertical line
            call    invOBJECT_redraw_vertical_line
        .ELSEIF (al == _LINE)
          ; It's a diagonal line
            call    invOBJECT_redraw_line
        .ELSEIF (al == _OVAL)
          ; It's a oval
            call    invOBJECT_redraw_oval
        .ELSEIF (al == _RECTANGLE)
          ; It's a rectangle
            call    invOBJECT_redraw_rectangle
        .ELSEIF (al == _SCROLL_BAR_HORIZONTAL)
          ; It's a horizontal scroll bar
            call    invOBJECT_redraw_horizontal_scroll_bar
        .ELSEIF (al == _SCROLL_BAR_VERTICAL)
          ; It's a vertical scroll bar
            call    invOBJECT_redraw_vertical_scroll_bar
        .ELSEIF (al == _CASK)
          ; It's a cask
            call    invOBJECT_redraw_cask
        .ELSEIF (al == _CFSCA_WINDOW)
          ; It's a cfsca window
            call    invOBJECT_redraw_cfsca_window
        .ELSEIF (al == _NUMBERS_WINDOW)
          ; It's a numbers window
            call    invOBJECT_redraw_numbers_window
        .ELSEIF (al == _TYPESET_WINDOW)
          ; It's a typeset window
            call    invOBJECT_redraw_typeset_window
        .ELSEIF (al == _BORDER_BOX)
          ; It's a border box
            call    invOBJECT_redraw_border_box
        .ENDIF
        ret
    invOBJECT_redraw_object     ENDP




    invOBJECT_redraw_input_field        PROC
    ; This routine is called to redraw an input field object
    ;
    ; Upon entry:   ds:[esi] - far ptr to input field object
    ;               ds:[edi] - far ptr to base object
    ;
    ; Upon exit:    The object is redrawn
    ;               carry? - Object is not currently visible
    ;
        ret
    invOBJECT_redraw_input_field        ENDP




    invOBJECT_redraw_text_field     PROC
    ; This routine is called to redraw a text field object
    ;
    ; Upon entry:   ds:[esi] - far ptr to text field object
    ;               ds:[edi] - far ptr to base object
    ;
    ; Upon exit:    The object is redrawn
    ;               carry? - Object is not currently visible
    ;
        .IF (byte ptr ds:[esi+_O_TF_VISIBLE] != 0)
          ; Draw the rectangle around the text
            pushfd
            mov     ebx,dword ptr ds:[esi+_O_TF_TOP]
            add     ebx,dword ptr ds:[edi+_BO_TOP]
            push    ebx
            mov     ebx,dword ptr ds:[esi+_O_TF_LEFT]
            add     ebx,dword ptr ds:[edi+_BO_LEFT]
            push    ebx
            push    dword ptr ds:[esi+_O_TF_WIDTH]
            push    dword ptr ds:[esi+_O_TF_HEIGHT]
            .IF (byte ptr ds:[esi+_O_TF_FONT_TYPEFACE_REVERSE] != 0)
                mov     ebx,_O_TF_FOREGROUND
            .ELSE
                mov     ebx,_O_TF_BACKGROUND
            .ENDIF
            call    fword ptr cs:_VID_g_derive_color
            push    eax
            cli
            call    fword ptr cs:_VID_g_fill_rectangle
            popfd

          ; Draw the text
            pushfd
            mov     ebx,dword ptr ds:[esi+_O_TF_TOP]
            add     ebx,dword ptr ds:[edi+_BO_TOP]
            push    ebx
            mov     ebx,dword ptr ds:[esi+_O_TF_LEFT]
            add     ebx,dword ptr ds:[edi+_BO_LEFT]
            push    ebx
            push    dword ptr ds:[esi+_O_TF_WIDTH]
            push    dword ptr ds:[esi+_O_TF_HEIGHT]

            mov     ebx,_O_TF_BACKGROUND
            call    fword ptr cs:_VID_g_derive_color
            push    eax

            mov     ebx,_O_TF_FOREGROUND
            call    fword ptr cs:_VID_g_derive_color
            push    eax

            movzx   ebx,word ptr ds:[esi+_O_TF_MARGIN_LEFT]
            push    ebx

            movzx   ebx,word ptr ds:[esi+_O_TF_MARGIN_TOP]
            push    ebx

            push    dword ptr ds:[esi+_O_TF_FONT_NAME_ID]
            push    dword ptr ds:[esi+_O_TF_SOURCE_PTR_SEGMENT]
            push    dword ptr ds:[esi+_O_TF_SOURCE_PTR_OFFSET]

            xor     eax,eax
            mov     al,byte ptr ds:[esi+_O_TF_FONT_TYPEFACE_BOLD]
            shl     eax,8
            mov     al,byte ptr ds:[esi+_O_TF_FONT_TYPEFACE_DITHER]
            push    eax

            xor     eax,eax
            mov     al,byte ptr ds:[esi+_O_TF_FONT_TYPEFACE_ITALICS]
            shl     eax,8
            mov     al,byte ptr ds:[esi+_O_TF_FONT_TYPEFACE_REVERSE]
            shl     eax,8
            mov     al,byte ptr ds:[esi+_O_TF_FONT_TYPEFACE_STRIKETHROUGH]
            shl     eax,8
            mov     al,byte ptr ds:[esi+_O_TF_FONT_TYPEFACE_UNDERLINE]
            push    eax
            cli
            call    fword ptr cs:_VID_g_draw_text
            popfd
            clc
        .ELSE
            stc
        .ENDIF
        ret
    invOBJECT_redraw_text_field     ENDP




    invOBJECT_redraw_button     PROC
    ; This routine is called to redraw a button object
    ;
    ; Upon entry:   ds:[esi] - far ptr to button object
    ;               ds:[edi] - far ptr to base object
    ;
    ; Upon exit:    The object is redrawn
    ;               carry? - Object is not currently visible
    ;
        ret
    invOBJECT_redraw_button     ENDP




    invOBJECT_redraw_menu_bar       PROC
    ; This routine is called to redraw a menu bar object
    ;
    ; Upon entry:   ds:[esi] - far ptr to menu bar object
    ;               ds:[edi] - far ptr to base object
    ;
    ; Upon exit:    The object is redrawn
    ;               carry? - Object is not currently visible
    ;
        ret
    invOBJECT_redraw_menu_bar       ENDP




    invOBJECT_redraw_popup      PROC
    ; This routine is called to redraw a popup object
    ;
    ; Upon entry:   ds:[esi] - far ptr to popup object
    ;               ds:[edi] - far ptr to base object
    ;
    ; Upon exit:    The object is redrawn
    ;               carry? - Object is not currently visible
    ;
        ret
    invOBJECT_redraw_popup      ENDP




    invOBJECT_redraw_radio_dial     PROC
    ; This routine is called to redraw a radio dial object
    ;
    ; Upon entry:   ds:[esi] - far ptr to radio dial object
    ;               ds:[edi] - far ptr to base object
    ;
    ; Upon exit:    The object is redrawn
    ;               carry? - Object is not currently visible
    ;
        ret
    invOBJECT_redraw_radio_dial     ENDP




    invOBJECT_redraw_check_box      PROC
    ; This routine is called to redraw a check box object
    ;
    ; Upon entry:   ds:[esi] - far ptr to check box object
    ;               ds:[edi] - far ptr to base object
    ;
    ; Upon exit:    The object is redrawn
    ;               carry? - Object is not currently visible
    ;
        ret
    invOBJECT_redraw_check_box      ENDP




    invOBJECT_redraw_circle_box     PROC
    ; This routine is called to redraw a circle box object
    ;
    ; Upon entry:   ds:[esi] - far ptr to circle box object
    ;               ds:[edi] - far ptr to base object
    ;
    ; Upon exit:    The object is redrawn
    ;               carry? - Object is not currently visible
    ;
        ret
    invOBJECT_redraw_circle_box     ENDP




    invOBJECT_redraw_pulldown       PROC
    ; This routine is called to redraw a pulldown object
    ;
    ; Upon entry:   ds:[esi] - far ptr to pulldown object
    ;               ds:[edi] - far ptr to base object
    ;
    ; Upon exit:    The object is redrawn
    ;               carry? - Object is not currently visible
    ;
        ret
    invOBJECT_redraw_pulldown       ENDP




    invOBJECT_redraw_slide_bar      PROC
    ; This routine is called to redraw a slide bar object
    ;
    ; Upon entry:   ds:[esi] - far ptr to slide bar object
    ;               ds:[edi] - far ptr to base object
    ;
    ; Upon exit:    The object is redrawn
    ;               carry? - Object is not currently visible
    ;
        ret
    invOBJECT_redraw_slide_bar      ENDP




    invOBJECT_redraw_percent_bar        PROC
    ; This routine is called to redraw a percent bar object
    ;
    ; Upon entry:   ds:[esi] - far ptr to percent bar object
    ;               ds:[edi] - far ptr to base object
    ;
    ; Upon exit:    The object is redrawn
    ;               carry? - Object is not currently visible
    ;
        ret
    invOBJECT_redraw_percent_bar        ENDP




    invOBJECT_redraw_tray       PROC
    ; This routine is called to redraw a tray object
    ;
    ; Upon entry:   ds:[esi] - far ptr to tray object
    ;               ds:[edi] - far ptr to base object
    ;
    ; Upon exit:    The object is redrawn
    ;               carry? - Object is not currently visible
    ;
        ret
    invOBJECT_redraw_tray       ENDP




    invOBJECT_redraw_icon       PROC
    ; This routine is called to redraw a icon object
    ;
    ; Upon entry:   ds:[esi] - far ptr to icon object
    ;               ds:[edi] - far ptr to base object
    ;
    ; Upon exit:    The object is redrawn
    ;               carry? - Object is not currently visible
    ;
        ret
    invOBJECT_redraw_icon       ENDP




    invOBJECT_redraw_bitmap     PROC
    ; This routine is called to redraw a bitmap object
    ;
    ; Upon entry:   ds:[esi] - far ptr to bitmap object
    ;               ds:[edi] - far ptr to base object
    ;
    ; Upon exit:    The object is redrawn
    ;               carry? - Object is not currently visible
    ;
        ret
    invOBJECT_redraw_bitmap     ENDP




    invOBJECT_redraw_horizontal_line        PROC
    ; This routine is called to redraw a horizontal line object
    ;
    ; Upon entry:   ds:[esi] - far ptr to horizontal line object
    ;               ds:[edi] - far ptr to base object
    ;
    ; Upon exit:    The object is redrawn
    ;               carry? - Object is not currently visible
    ;
        .IF (byte ptr ds:[esi+_O_HL_VISIBLE] != 0)
            pushfd
            mov     ebx,dword ptr ds:[esi+_O_HL_TOP]
            add     ebx,dword ptr ds:[edi+_BO_TOP]
            push    ebx
            mov     ebx,dword ptr ds:[esi+_O_HL_LEFT]
            add     ebx,dword ptr ds:[edi+_BO_LEFT]
            push    ebx
            push    dword ptr ds:[esi+_O_HL_WIDTH]
            push    1
            mov     ebx,_O_HL_BACKGROUND
            call    fword ptr cs:_VID_g_derive_color
            push    eax
            cli
            call    fword ptr cs:_VID_g_fill_rectangle
            popfd
            clc
        .ELSE
            stc
        .ENDIF
        ret
    invOBJECT_redraw_horizontal_line        ENDP




    invOBJECT_redraw_vertical_line      PROC
    ; This routine is called to redraw a vertical line object
    ;
    ; Upon entry:   ds:[esi] - far ptr to vertical line object
    ;               ds:[edi] - far ptr to base object
    ;
    ; Upon exit:    The object is redrawn
    ;               carry? - Object is not currently visible
    ;
        ret
    invOBJECT_redraw_vertical_line      ENDP




    invOBJECT_redraw_line       PROC
    ; This routine is called to redraw a line object
    ;
    ; Upon entry:   ds:[esi] - far ptr to line object
    ;               ds:[edi] - far ptr to base object
    ;
    ; Upon exit:    The object is redrawn
    ;               carry? - Object is not currently visible
    ;
        ret
    invOBJECT_redraw_line       ENDP




    invOBJECT_redraw_oval       PROC
    ; This routine is called to redraw a oval object
    ;
    ; Upon entry:   ds:[esi] - far ptr to oval object
    ;               ds:[edi] - far ptr to base object
    ;
    ; Upon exit:    The object is redrawn
    ;               carry? - Object is not currently visible
    ;
        ret
    invOBJECT_redraw_oval       ENDP




    invOBJECT_redraw_rectangle      PROC
    ; This routine is called to redraw a rectangle object
    ;
    ; Upon entry:   ds:[esi] - far ptr to rectangle object
    ;               ds:[edi] - far ptr to base object
    ;
    ; Upon exit:    The object is redrawn
    ;               carry? - Object is not currently visible
    ;
        .IF (byte ptr ds:[esi+_O_R_VISIBLE] != 0)
            pushfd
            mov     ebx,dword ptr ds:[esi+_O_R_TOP]
            add     ebx,dword ptr ds:[edi+_BO_TOP]
            push    ebx
            mov     ebx,dword ptr ds:[esi+_O_R_LEFT]
            add     ebx,dword ptr ds:[edi+_BO_LEFT]
            push    ebx
            push    dword ptr ds:[esi+_O_R_WIDTH]
            push    dword ptr ds:[esi+_O_R_HEIGHT]
            mov     ebx,_O_R_BACKGROUND
            call    fword ptr cs:_VID_g_derive_color
            push    eax
            cli
            call    fword ptr cs:_VID_g_fill_rectangle
            popfd
            clc
        .ELSE
            stc
        .ENDIF
        ret
    invOBJECT_redraw_rectangle      ENDP




    invOBJECT_redraw_horizontal_scroll_bar      PROC
    ; This routine is called to redraw a horizontal scroll bar object
    ;
    ; Upon entry:   ds:[esi] - far ptr to horizontal scroll bar object
    ;               ds:[edi] - far ptr to base object
    ;
    ; Upon exit:    The object is redrawn
    ;               carry? - Object is not currently visible
    ;
        ret
    invOBJECT_redraw_horizontal_scroll_bar      ENDP




    invOBJECT_redraw_vertical_scroll_bar        PROC
    ; This routine is called to redraw a vertical scroll bar object
    ;
    ; Upon entry:   ds:[esi] - far ptr to vertical scroll bar object
    ;               ds:[edi] - far ptr to base object
    ;
    ; Upon exit:    The object is redrawn
    ;               carry? - Object is not currently visible
    ;
        ret
    invOBJECT_redraw_vertical_scroll_bar        ENDP




    invOBJECT_redraw_cask       PROC
    ; This routine is called to redraw a cask object
    ;
    ; Upon entry:   ds:[esi] - far ptr to cask object
    ;               ds:[edi] - far ptr to base object
    ;
    ; Upon exit:    The object is redrawn
    ;               carry? - Object is not currently visible
    ;
        ret
    invOBJECT_redraw_cask       ENDP




    invOBJECT_redraw_cfsca_window       PROC
    ; This routine is called to redraw a cfsca window object
    ;
    ; Upon entry:   ds:[esi] - far ptr to cfsca window object
    ;               ds:[edi] - far ptr to base object
    ;
    ; Upon exit:    The object is redrawn
    ;               carry? - Object is not currently visible
    ;
        ret
    invOBJECT_redraw_cfsca_window       ENDP




    invOBJECT_redraw_numbers_window     PROC
    ; This routine is called to redraw a numbers window object
    ;
    ; Upon entry:   ds:[esi] - far ptr to numbers window object
    ;               ds:[edi] - far ptr to base object
    ;
    ; Upon exit:    The object is redrawn
    ;               carry? - Object is not currently visible
    ;
        ret
    invOBJECT_redraw_numbers_window     ENDP




    invOBJECT_redraw_typeset_window     PROC
    ; This routine is called to redraw a typeset window object
    ;
    ; Upon entry:   ds:[esi] - far ptr to typeset window object
    ;               ds:[edi] - far ptr to base object
    ;
    ; Upon exit:    The object is redrawn
    ;               carry? - Object is not currently visible
    ;
        ret
    invOBJECT_redraw_typeset_window     ENDP




    invOBJECT_redraw_border_box     PROC
    ; This routine is called to redraw a border box object
    ;
    ; Upon entry:   ds:[esi] - far ptr to border box object
    ;               ds:[edi] - far ptr to base object
    ;
    ; Upon exit:    The object is redrawn
    ;               carry? - Object is not currently visible
    ;
        .IF (byte ptr ds:[esi+_O_BB_VISIBLE] != 0)
          ;; Draw the rectangle
            pushfd
            mov     ebx,dword ptr ds:[esi+_O_BB_TOP]
            add     ebx,dword ptr ds:[edi+_BO_TOP]
            push    ebx
            mov     ebx,dword ptr ds:[esi+_O_BB_LEFT]
            add     ebx,dword ptr ds:[edi+_BO_LEFT]
            push    ebx
            push    dword ptr ds:[esi+_O_BB_WIDTH]
            push    dword ptr ds:[esi+_O_BB_HEIGHT]
            mov     ebx,_O_BB_BACKGROUND
            call    fword ptr cs:_VID_g_derive_color
            push    eax
            cli
            call    fword ptr cs:_VID_g_fill_rectangle

          ;; Draw the bottom
            mov     ebx,dword ptr ds:[esi+_O_BB_TOP]
            add     ebx,dword ptr ds:[esi+_O_BB_HEIGHT]
            add     ebx,dword ptr ds:[edi+_BO_TOP]
            push    ebx
            mov     ebx,dword ptr ds:[esi+_O_BB_LEFT]
            add     ebx,dword ptr ds:[edi+_BO_LEFT]
            push    ebx
            push    dword ptr ds:[esi+_O_BB_WIDTH]
            push    1
            mov     ebx,_O_BB_SHADOW_BORDER
            call    fword ptr cs:_VID_g_derive_color
            push    eax
            call    fword ptr cs:_VID_g_fill_rectangle

          ;; Draw the right-side
            mov     ebx,dword ptr ds:[esi+_O_BB_TOP]
            add     ebx,dword ptr ds:[edi+_BO_TOP]
            push    ebx
            mov     ebx,dword ptr ds:[esi+_O_BB_LEFT]
            add     ebx,dword ptr ds:[esi+_O_BB_WIDTH]
            dec     ebx
            add     ebx,dword ptr ds:[edi+_BO_LEFT]
            push    ebx
            push    1
            push    dword ptr ds:[esi+_O_BB_HEIGHT]
            inc     dword ptr ss:[esp+00]
            mov     ebx,_O_BB_SHADOW_BORDER
            call    fword ptr cs:_VID_g_derive_color
            push    eax
            call    fword ptr cs:_VID_g_fill_rectangle

          ;; Draw the top
            mov     ebx,dword ptr ds:[esi+_O_BB_TOP]
            add     ebx,dword ptr ds:[edi+_BO_TOP]
            push    ebx
            mov     ebx,dword ptr ds:[esi+_O_BB_LEFT]
            add     ebx,dword ptr ds:[edi+_BO_LEFT]
            push    ebx
            push    dword ptr ds:[esi+_O_BB_WIDTH]
            push    1
            mov     ebx,_O_BB_LIGHT_BORDER
            call    fword ptr cs:_VID_g_derive_color
            push    eax
            call    fword ptr cs:_VID_g_fill_rectangle

          ;; Draw the left-side
            mov     ebx,dword ptr ds:[esi+_O_BB_TOP]
            add     ebx,dword ptr ds:[edi+_BO_TOP]
            push    ebx
            mov     ebx,dword ptr ds:[esi+_O_BB_LEFT]
            add     ebx,dword ptr ds:[edi+_BO_LEFT]
            push    ebx
            push    1
            push    dword ptr ds:[esi+_O_BB_HEIGHT]
            inc     dword ptr ss:[esp+00]
            mov     ebx,_O_BB_LIGHT_BORDER
            call    fword ptr cs:_VID_g_derive_color
            push    eax
            call    fword ptr cs:_VID_g_fill_rectangle
            popfd
            clc
        .ELSE
            stc
        .ENDIF
        ret
    invOBJECT_redraw_border_box     ENDP