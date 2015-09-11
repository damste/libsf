; mouse.asp
;
; Exodus TASK Mouse Handler
;          ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
; * Note * ´ This is not a mouse driver!! ³
;          ÀÃÃÃÃÃÃÃÃÃÃÃÃÃÃÃÃÃÃÃÃÃÃÃÃÃÃÃÃÃÃÙ
;          It just handles information sent from the mouse driver.
;




; Status
mouse_status                    dd  0                               ; Is mouse displayed?  1-Yes, 0-No
mouse_pointer_type              dd  0                               ; Refer to INF\MOUSE.INF or VGA\MOUSE.FNT
mouse_processing                dd  0                               ; Is this program processing?  1-Yes, 0-No
dragging_something              dd  0                               ; Dragging something?  1-Yes, 0-No

; Mouse coordinates
mouse_current_x                 dd  160
mouse_current_y                 dd  100
mouse_hovering_x                dd  0ffffffffh
mouse_hovering_y                dd  0ffffffffh
mouse_pointer_save_area         db  16*20 dup(0)

; Dragging activity
dragging_x                      dd  0
dragging_y                      dd  0
dragging_height                 dd  0
dragging_width                  dd  0
dragging_offset_x               dd  0
dragging_offset_y               dd  0
dragging_snap_x                 dd  0
dragging_snap_y                 dd  0
dragging_last_x                 dd  0
dragging_last_y                 dd  0
dragging_skipped                dd  0

; Counts used to activate various things
mouse_hovering_count_start      dd  91
mouse_hovering_count            dd  0ffffffffh
mouse_clicking_count_start      dd  30
mouse_clicking_count            dd  0ffffffffh
mouse_immediate_count_start     dd  2
mouse_immediate_count           dd  0ffffffffh

; Relating to click activity
mouse_last_event                db  0                               ; Relates to clicking or dragging
mouse_right_click_x_start       dd  0
mouse_right_click_y_start       dd  0
mouse_left_click_x_start        dd  0
mouse_left_click_y_start        dd  0
mouse_right_click_x_stop        dd  0
mouse_right_click_y_stop        dd  0
mouse_left_click_x_stop         dd  0
mouse_left_click_y_stop         dd  0
mouse_right_click               dd  0
mouse_left_click                dd  0
mouse_both_click                dd  0
mouse_left_dragging             dd  0
mouse_right_dragging            dd  0

; Relating to button activity
mouse_last_buttons              dd  0                               ; Button status from previous mouse packet
mouse_last_button_left          dd  0
mouse_last_button_right         dd  0
mouse_button_left               dd  0
mouse_button_right              dd  0

; Relating to screen saver
screen_saver_active             dd  0                               ; 1-Yes, 0-No
screen_saver_count              dd  18200                           ; 100 seconds
screen_saver_count_start        dd  18200





    iTASK_mouse_interface       PROC
    ; This routine is called when there is mouse information for Exodus
    ;
    ; Upon entry:   eax = X delta
    ;               edx = Y delta
    ;               ebx = button status
    ;
    ; Upon exit:    The mouse information is updated
    ;
        push    ds
        pushad
        mov     ds,cs:data_segment


      ;; Cancel screen saver (if it's active)
        .IF (ds:screen_saver_active == 1)
            call    invTASK_cancel_screen_saver
            mov     ecx,ds:screen_saver_count_start
            mov     ds:screen_saver_count,ecx
        .ENDIF


      ;; Remove the mouse pointer that's already displayed
        .IF (ds:mouse_processing == 0 && ds:mouse_status == 1)
            mov     ds:mouse_processing,1
            call    invTASK_hide_mouse_pointer
            mov     ds:mouse_processing,0
        .ENDIF


      ;; Update to new mouse coordinates
        call    invTASK_adjust_mouse_coordinates


      ;; Process the data
        .IF (ds:mouse_processing == 0)
            mov     ds:mouse_processing,1
            .IF (ebx != 0 || ebx != ds:mouse_last_buttons)
              ; There is button activity
              ; This process might take a bit of time to complete so we indicate we're processing thereby removing
              ; the possibility of attempted processing in the future until such time as all the processing we're about
              ; to start gets completed.
                call    invTASK_mouse_button_activity
            .ELSE
              ; No button activity
              ; We still have to see if we're over anything that needs to be updated because we also display information about
              ; certain things in the Quick Watch window.  Isn't it great? :)
                mov     edx,ds:mouse_current_x
                mov     ds:mouse_hovering_x,edx
                mov     edx,ds:mouse_current_y
                mov     ds:mouse_hovering_y,edx
                mov     ecx,ds:mouse_hovering_count_start
                mov     ds:mouse_hovering_count,ecx
                mov     ds:mouse_last_event,_HOVER
                mov     ecx,ds:mouse_immediate_count_start
                mov     ds:mouse_immediate_count,ecx
                call    invTASK_show_mouse_pointer
            .ENDIF
            mov     ds:mouse_processing,0
        .ENDIF

        popad
        pop     ds
        retf
    iTASK_mouse_interface       ENDP




    invTASK_adjust_mouse_coordinates        PROC
    ; This routine is called to adjust the mouse coordinates
    ;
    ; Upon entry:   eax - X delta
    ;               edx - Y delta
    ;               ebx - buton status
    ;
    ; Upon exit:    mouse_current_x - updated
    ;               mouse_current_y - updated
    ;
        push    es
        mov     ecx,_sSYSTEM
        mov     es,ecx

      ; Adjust the mouse based on the distance it's moved
        add     ds:mouse_current_x,eax
        add     ds:mouse_current_y,edx

      ; Find the maximum coordinates
        movzx   eax,word ptr es:[_SYSTEM_VGA_HORIZONTAL]
        dec     eax                                                 ; Change base-1 to base-0
        movzx   edx,word ptr es:[_SYSTEM_VGA_VERTICAL]
        dec     edx                                                 ; Change base-1 to base-0
      ; Right now, eax - maximum horizontal
      ;            edx - maximum vertical

        .IF (ds:dragging_something == 0)
          ; Verify X
            .IF (ds:mouse_current_x > 7fffffffh)
              ; It's negative (it's off the left of the screen or it's at the very left of the screen)
                mov     ds:mouse_current_x,0
            .ELSEIF (ds:mouse_current_x > eax)
              ; It's heading off the right side of the screen
                mov     ds:mouse_current_x,eax
            .ENDIF

          ; Verify Y
            .IF (ds:mouse_current_y > 7fffffffh)
              ; It's negative (it's above the top of the screen or it's at the very top of the screen)
                mov     ds:mouse_current_y,0
            .ELSEIF (ds:mouse_current_y > edx)
              ; It's heading off the bottom of the screen
                mov     ds:mouse_current_y,edx
            .ENDIF
        .ELSE
          ; The mouse is only allowed to move in certain areas when something is being dragged
          ; This logic is a little more complex than the above no-drag logic

          ; Make sure they're not negative
            .IF (ds:mouse_current_x > 7fffffffh)
                neg     ds:mouse_current_x
            .ENDIF
            .IF (ds:mouse_current_y > 7fffffffh)
                neg     ds:mouse_current_y
            .ENDIF

          ; Verify X
            mov     ecx,ds:mouse_current_x
            sub     ecx,ds:dragging_offset_x
            .IF (carry?)
              ; We're less than zero
                neg     ecx
                add     ds:mouse_current_x,ecx
            .ELSE
              ; We're good on the left-side.  Now, how about the right?
                mov     ecx,ds:mouse_current_x
                sub     ecx,ds:dragging_offset_x
                add     ecx,ds:dragging_width
                .IF (ecx > eax)
                  ; We're to far
                    sub     ecx,eax
                    sub     ds:mouse_current_x,ecx
                .ENDIF
            .ENDIF

          ; Verify Y
            mov     ecx,ds:mouse_current_y
            sub     ecx,ds:dragging_offset_y
            .IF (carry?)
              ; We're less than zero
                neg     ecx
                add     ds:mouse_current_y,ecx
            .ELSE
              ; We're good on the top.  Now, how about the bottom?
                mov     ecx,ds:mouse_current_y
                sub     ecx,ds:dragging_offset_y
                add     ecx,ds:dragging_height
                .IF (ecx > edx)
                  ; We're to far
                    sub     ecx,edx
                    sub     ds:mouse_current_y,ecx
                .ENDIF
            .ENDIF
        .ENDIF

        pop     es
        ret
    invTASK_adjust_mouse_coordinates        ENDP




    invTASK_hide_mouse_pointer      PROC
    ; This routine is called when they want to hide the mouse pointer
    ;
    ; Upon entry:   Nothing
    ;
    ; Upon exit:    The mouse pointer is displayed
    ;
        pushfd
        push    dword ptr ds:mouse_current_x
        push    dword ptr ds:mouse_current_y
        push    0                                                   ; 0-hide, 1-show
        push    dword ptr ds:mouse_pointer_type                     ; mouse pointer type
        push    dword ptr offset mouse_pointer_save_area
        cli
        call    fword ptr ds:_VID_g_mouse_pointer
        mov     ds:mouse_status,0
        popfd
        ret
    invTASK_hide_mouse_pointer      ENDP




    invTASK_show_mouse_pointer      PROC
    ; This routine is called when they want to show the mouse pointer
    ;
    ; Upon entry:   Nothing
    ;
    ; Upon exit:    The mouse pointer is displayed
    ;
.IF (ds:mouse_current_x > 320 || ds:mouse_current_y > 200)
    int 3
.ENDIF
        pushfd
        push    dword ptr ds:mouse_current_x
        push    dword ptr ds:mouse_current_y
        push    1
        push    dword ptr ds:mouse_pointer_type                     ; mouse pointer type
        push    dword ptr offset mouse_pointer_save_area
        cli
        call    fword ptr ds:_VID_g_mouse_pointer
        mov     ds:mouse_status,1
        popfd
        ret
    invTASK_show_mouse_pointer      ENDP




    invTASK_mouse_button_activity       PROC
    ; This routine is called to process button activity
    ;
    ; Upon entry:   Nothing
    ;
    ; Upon exit:    Any change in button activity is appropriately handled
    ;
        ret
    invTASK_mouse_button_activity       ENDP




    invTASK_activate_screen_saver       PROC
    ; This routine is used to cancel a previously activated screen saver
    ;
    ; Upon entry:   Nothing
    ;
    ; Upon exit:    The screen is saved if it's not already in a saved screen state
    ;
        ret
    invTASK_activate_screen_saver       ENDP




    invTASK_cancel_screen_saver     PROC
    ; This routine is used to cancel a previously activated screen saver
    ;
    ; Upon entry:   Nothing
    ;
    ; Upon exit:    The screen is restored if it was previously in a saved screen state
    ;
        ret
    invTASK_cancel_screen_saver     ENDP