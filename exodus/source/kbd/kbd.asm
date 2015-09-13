; kbd.asm
;
; ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
; ³ standard 104-keyboard ³
; ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
;
; Exodus native primative keyboard functions for 104-key keyboards
;

TITLE standard 104-keyboard Driver

    .MODEL tiny

    .STACK 0h

INCLUDE \exodus\source\common\equates.asp

    .386P
_TEXT32 SEGMENT BYTE 'CODE' USE32
    ASSUME NOTHING

; These are required to be the first 2 dwords in the file
dd  offset main
dd  offset requestor




    requestor   PROC
    ; This routine is called by Exodus.  When this function is called multi-tasking is not installed.  This is a linear function.
    ;
    ; Upon entry:   eax - requested function
    ;                ds - temporary ORG 0h data segment for use with these requestor() functions
    ;
    ; Upon exit:    results vary based on value of eax
    ;
        .IF (eax == 'info')
          ; Program information
            mov     eax,'nati'                              ; Identifying this program as a native primative
            mov     ecx,offset end_of_required_data         ; The maximum number of bytes to retain after loading

            mov     esi,offset driver_primatives            ; Offset to the native primatives structure
            mov     edi,offset driver_name
            mov     ebx,offset version
            mov     edx,offset copyright
            mov     ebp,offset author
            clc
        .ELSEIF (eax == 'prim')
          ; Native primatives this program will use
            mov     ds:data_segment,ds
            mov     esi,offset required_primatives          ; This primative requires these external influence
            mov     edi,offset primative_call_gates
            clc
        .ELSEIF (eax == 'id  ')
          ; Display this program's ID on the VGA monitor
            mov     esi,offset driver_name
            call    fword ptr cs:_VID_display_string_nr_vga
            clc
        .ELSEIF (eax == 'note')
          ; Exodus has a note for us
            mov     eax,'stop'
            mov     ebx,'load'
            mov     esi,offset driver_name
            call    fword ptr cs:_EXODUS_requestor
        .ELSE
            stc
        .ENDIF
        retf
    requestor   ENDP




    main    PROC
    ; This routine is called once by Exodus once initialization is complete (all calls to requestor() are finished)
    ; It is used by Exodus to allow this driver to properly initialize itself.
    ; When this function is called multi-tasking is not installed.  This is a linear function.
    ;
    ; Upon entry:   Nothing
    ;
    ; Upon exit:    A "continued status of execution" is expected by Exodus.  This indicates whether or not everything
    ;               initialized ok or is available.  If everything is OK the carry? flag is CLEAR.  If there is an error
    ;               and this driver cannot continue then the carry? should be SET.
    ;               carry? - CLEAR=Ok to continue
    ;                          SET=Error initializing
    ;
        mov     ds,cs:data_segment
        mov     ds:bootup,0
        call    initialize_driver
      ; Right now, carry? is SET or CLEAR indicating status of driver
        retf
    main    ENDP




    initialize_driver   PROC
    ; This routine initializes the keyboard to ensure it's setup correctly
    ;
    ; Upon entry:   Nothing
    ;
    ; Upon exit:    The keyboard is initialized if carry? is clear
    ;
      ;; Point IRQ1 to the KBD ISR (Exodus remaps IRQs to 70h - 7fh ... how thoughtful. :))
        mov     eax,'bint'
        mov     bl,71h
        mov     ecx,1
        mov     edx,offset KBD_handler                              ; Offset to the keyboard ISR
        call    fword ptr ds:_EXODUS_requestor

        call    fword ptr ds:_iBIOS_read_8042_64h                   ; See if the keyboard is active
        test    al,10000b
        .IF (!zero?)
          kbd_ok:
            call    invDisable_keyboard
          ;; Set the delay and repeat rate
            mov     ah,0f3h                                         ; Typematic control (repeating character rate)
            call    fword ptr ds:_iBIOS_write_8042_60h
            xor     ah,ah                                           ; Delay = 250ms, 30 cps (min delay, max speed)
            call    fword ptr ds:_iBIOS_write_8042_60h

          ;; Set the LEDs to all off
            mov     ah,0edh                                         ; LED write
            call    fword ptr ds:_iBIOS_write_8042_60h
            xor     ah,ah                                           ; 00000:x:x:x = CAPS:NUM:SCROLL; 1-on, 0-off
            call    fword ptr ds:_iBIOS_write_8042_60h
            call    invEnable_keyboard

          ;; Display the keyboard logo
            mov     esi,offset keyboard_logo
            call    fword ptr ds:_VID_draw_logo

          ;; Everything's fine
            clc
        .ELSE
            stc
        .ENDIF

        clc
        ret
    initialize_driver   ENDP




    invDisable_keyboard    PROC
    ; Sends the disable keyboard command to port 64h
        push    eax
        mov     ah,0adh                                             ; Disable keyboard command
        call    fword ptr ds:_iBIOS_write_8042_64h
        call    fword ptr ds:_TIMER_wait_full_tick
        pop     eax
        ret
    invDisable_keyboard    ENDP




    invEnable_keyboard     PROC
    ; Sends the enable keyboard command to port 64h
        push    eax
        mov     ah,0aeh                                             ; Enable keyboard command
        call    fword ptr ds:_iBIOS_write_8042_64h
        call    fword ptr ds:_TIMER_wait_full_tick
        pop     eax
        ret
    invEnable_keyboard     ENDP




    KBD_handler     PROC
    ; Right now, we know there's some data ready for us
        push    ds
        pushad

    ;; Just store it for later processing
    ;; * Note:  The logic to decode the key's scancode isn't in this routine because the ISR should be fast-and-efficient.

        mov     ds,cs:data_segment
        in      al,060h                                                 ; Read the scan code
;pushad
;push ds:text_x
;push ds:text_y
;movzx edx,al
;mov ebx,16
;call fword ptr ds:_VID_g_display_radix_in_edx_mono
;add ds:text_x,8*4
;.IF (ds:text_x > 720-(8*4))
;    mov ds:text_x,0
;    add ds:text_y,10
;.ENDIF
;popad
        call    invKBD_interpret_keystroke

        .IF (!carry?)
          ; Action is required (they've done something that might trigger something else)
            .IF (ds:debi_intercept == 1)
                call    fword ptr ds:_iDEBI_kbd_interface
            .ELSE
                call    fword ptr ds:_iTASK_kbd_interface
            .ENDIF
        .ENDIF

      ; Signal end-of-interrupt
        mov     al,20h
        out     20h,al

        popad
        pop     ds
        iretd
    KBD_handler     ENDP




    invKBD_interpret_keystroke      PROC
    ; This routine is an unusual one.  It doesn't get directly called usually, but it can
    ; When it is directly called the application is specifically waiting for a key
    ;
    ; Upon entry:   al - key that was just intercepted
    ;
    ; Upon exit:    carry? - SET if key was nothing of significance (such as the release of a key)
    ;                        CLEAR if action is required (such as this is the user pressing a key)
    ;
        .IF (al == 0e0h)
          ; It's an extended keycode
            mov     ds:extended_data,1
            stc
            jmp     quit
        .ENDIF

        test    al,80h
        .IF (!zero?)
          ; They're releasing a key
            and     al,not 80h
            .IF (ds:extended_data == 1)
                mov     esi,offset extended_keys
                .WHILE (dword ptr ds:[esi] != 0ffffffffh)
                    .IF (byte ptr ds:[esi] == al)
                      ; We found our match
                        and     eax,0ffh
                        mov     ah,0e0h
                        mov     ds:extended_data,0
                        .IF (dword ptr ds:[esi+1] != 0ffffffffh)
                          ; The press of this key updates the status of an internal flag only, it doesn't cause any action
                            mov     esi,dword ptr ds:[esi+1]
                            .IF (esi >= 80000000h)
                              ; When the high bit is set it indicates this needs to be toggled
                                and     esi,not 80000000h
                                .IF (byte ptr ds:[esi] != 0)
                                    mov     byte ptr ds:[esi],0
                                .ELSE
                                    mov     byte ptr ds:[esi],1
                                .ENDIF
                            .ELSE
                                mov     byte ptr ds:[esi],0
                            .ENDIF
                            stc
                            jmp     quit
                        .ENDIF
                      ; Right now, eax - key they've pressed.  This one causes action, we have to report it to the active task
                        jmp     derive_keyboard_status
                    .ENDIF
                    add     esi,5
                .ENDW
              ; It wasn't a match, ignore it
                mov     ds:extended_data,0
                stc
                jmp     quit
            .ELSE
                mov     esi,offset release_keys
                .WHILE (word ptr ds:[esi] != 0ffffh)
                    .IF (byte ptr ds:[esi] == al)
                        movzx   esi,word ptr ds:[esi+1]
                        mov     byte ptr ds:[esi],0
                        stc
                        jmp     quit
                    .ENDIF
                    add     esi,5
                .ENDW
            .ENDIF
          ; It's some other key, ignore it
            stc
            jmp     quit
        .ELSE
          ; They're pressing a key
            .IF (ds:extended_data == 1)
                mov     esi,offset extended_keys
                .WHILE (dword ptr ds:[esi] != 0ffffffffh)
                    .IF (byte ptr ds:[esi] == al)
                      ; We found our match
                        and     eax,0ffh
                        mov     ah,0e0h
                        mov     ds:extended_data,0
                        .IF (dword ptr ds:[esi+1] != 0ffffffffh)
                          ; The press of this key updates the status of an internal flag only, it doesn't cause any action
                            mov     esi,dword ptr ds:[esi+1]
                            .IF (esi >= 80000000h)
                              ; When the high bit is set it indicates this needs to be toggled
                                and     esi,not 80000000h
                                .IF (byte ptr ds:[esi] != 0)
                                    mov     byte ptr ds:[esi],0
                                .ELSE
                                    mov     byte ptr ds:[esi],1
                                .ENDIF
                            .ELSE
                                mov     byte ptr ds:[esi],1
                            .ENDIF
                            stc
                            jmp     quit
                        .ENDIF
                      ; Right now, eax - key they've pressed.  This one causes action, we have to report it to the active task
                        jmp     derive_keyboard_status
                    .ENDIF
                    add     esi,5
                .ENDW
              ; It wasn't a match, ignore it
                mov     ds:extended_data,0
                stc
                jmp     quit
            .ELSE
              ; Normal mode
              ; See if it needs immediate action (like shift/ctrl/alt)
                mov     esi,offset depress_keys
                .WHILE (dword ptr ds:[esi] != 0ffffffffh)
                    .IF (byte ptr ds:[esi] == al)
                      ; We've found our match, now act on what it says to do
                        mov     esi,dword ptr ds:[esi+1]
                        .IF (esi >= 80000000h)
                          ; When the high bit is set it indicates this needs to be toggled
                            and     esi,not 80000000h
                            .IF (byte ptr ds:[esi] != 0)
                                mov     byte ptr ds:[esi],0
                            .ELSE
                                mov     byte ptr ds:[esi],1
                            .ENDIF
                        .ELSE
                            mov     byte ptr ds:[esi],1
                        .ENDIF
                        stc
                        jmp     quit
                    .ENDIF
                    add     esi,5
                .ENDW

                and     eax,0ffh
                .IF (eax <= 58h)
                    .IF (ds:l_ctrl_status != 0 || ds:r_ctrl_status != 0)
                        mov     esi,offset ctrl_keys
                    .ELSEIF ((ds:l_shift_status != 0 || ds:r_shift_status != 0) && ds:caps_status == 0)
                      ; Shift by itself
                        mov     esi,offset shift_key_set
                    .ELSEIF ((ds:l_shift_status != 0 || ds:r_shift_status != 0) && ds:caps_status != 0)
                      ; CAPS + Shift (reverses capitalization on letters)
                        mov     esi,offset caps_shift_key_set
                    .ELSEIF (ds:l_shift_status == 0 && ds:r_shift_status == 0 && ds:caps_status != 0)
                      ; CAPS by itself
                        mov     esi,offset caps_raw_key_set
                    .ELSEIF (ds:l_alt_status != 0 || ds:r_alt_status != 0)
                        mov     esi,offset alt_keys
                      ;; REMEMBER, need to add an algorithm to allow 3-digit input from the numeric keypad (ASCII code)
                    .ELSE
                        mov     esi,offset raw_key_set
                    .ENDIF
                    shl     eax,1
                    movzx   eax,word ptr ds:[esi+eax]
                .ELSE
                    stc
                .ENDIF
              ; Right now, eax - key they've pressed
            .ENDIF
        .ENDIF

      derive_keyboard_status:
      ; Right now, eax - key they've pressed
      ; Now, build the ebx value (keyboard flags, indicates status of CTRL/ALT/SHIFT, etc.)
      ; * Refer to KBD\KBD.INF for information about the format of this status dword
        clc

      quit:
      ; Right now, the carry? flag indicates whether or not action is required
      ;   SET-No
      ; CLEAR-Yes
        ret
    invKBD_interpret_keystroke      ENDP




    iKBD_activate_DEBI_intercept    PROC
    ; This routine is called only from DEBI.  It indicates that any KBD information should be
    ; sent to the DEBI algorithm
    ;
    ; Upon entry:   Nothing
    ;
    ; Upon exit:    Input is diverted
    ;
        push    ds
        mov     ds,cs:data_segment
        mov     ds:debi_intercept,1
        pop     ds
        retf
    iKBD_activate_DEBI_intercept    ENDP




    iKBD_deactivate_DEBI_intercept      PROC
    ; This routine is called only from DEBI.  It indicates that any KBD information should now be
    ; handled in the normal manner (it should not be sent to the DEBI algorithm)
    ;
    ; Upon entry:   Nothing
    ;
    ; Upon exit:    Input is diverted
    ;
        push    ds
        mov     ds,cs:data_segment
        mov     ds:debi_intercept,1
        pop     ds
        retf
    iKBD_deactivate_DEBI_intercept      ENDP









; Key definitions and constants
    INCLUDE kbd.asp

; DATA
    driver_name                             db  "PS/2 Keyboard Driver",0
    version                                 db  "10.10.2010",0
    copyright                               db  "(c) Copyright Beatleworks, Inc.",0
    author                                  db  "Rick C. Hodgin",0
    bootup                                  db  1                   ; Changed to 0 after bootup is complete

    data_segment                            dw  0
    debi_intercept                          db  0
    extended_data                           db  0                   ; Are we in extended data mode?

    keyboard_logo                           db  0       ; how many extra 16x16 pictures wide?
                                            db  00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
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

    text_x                                  dd  0
    text_y                                  dd  0

    _EXODUS_requestor                       dw  0
  primative_call_gates:
    _VID_draw_logo                          dw  0
    _VID_display_string_nr_vga              dw  _sEXODUS_REQUESTOR
    _iDEBI_kbd_interface                    dw  0f000h
    _iTASK_kbd_interface                    dw  0f000h
    _TIMER_wait_full_tick                   dw  0f000h
    _iBIOS_read_8042_64h                    dw  0f000h
    _iBIOS_read_8042_60h                    dw  0f000h
    _iBIOS_write_8042_64h                   dw  0f000h
    _iBIOS_write_8042_60h                   dw  0f000h
    _VID_g_mono_display_text                dw  0f000h
    _VID_g_display_radix_in_edx_mono        dw  0f000h
                                            dw  0f000h
                                            dw  0f000h

    required_primatives                     db  13, "VID_draw_logo"
                                            db  25, "VID_display_string_nr_vga"
                                            db  19, "iDEBI_kbd_interface"
                                            db  19, "iTASK_kbd_interface"
                                            db  20, "TIMER_wait_full_tick"
                                            db  19, "iBIOS_read_8042_64h"
                                            db  19, "iBIOS_read_8042_60h"
                                            db  20, "iBIOS_write_8042_64h"
                                            db  20, "iBIOS_write_8042_60h"
                                            db  23, "VID_g_mono_display_text"
                                            db  31, "VID_g_display_radix_in_edx_mono"
                                            db  0ffh

 end_of_required_data:

    driver_primatives:
                                            db  28,"iKBD_activate_DEBI_intercept"
                                            dd  offset iKBD_activate_DEBI_intercept
                                            dw  0

                                            db  30,"iKBD_deactivate_DEBI_intercept"
                                            dd  offset iKBD_deactivate_DEBI_intercept
                                            dw  0

                                            dw  0ffffh              ; Teriminator

_TEXT32 ENDS

END
