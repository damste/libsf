; mouseps2.asm
;
; ÚÄÄÄÄÄÄÄÄÄÄÄÄ¿
; ³ PS/2 Mouse ³
; ÀÄÄÄÄÄÄÄÄÄÄÄÄÙ
;
; Exodus native primative mouse functions for PS/2 mice
;


TITLE PS/2 Mouse Driver

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
      ;; Display the logo on the bootup screen
        mov     esi,offset mouse_logo
        call    fword ptr ds:_VID_draw_logo

      ;; Point IRQ12 to the MOUSE ISR
        mov     eax,'bint'
        mov     bl,7ch                                              ; IRQ 12
        mov     ecx,1
        mov     edx,offset MOUSE_handler                            ; Offset to the mouse ISR
        call    fword ptr ds:_EXODUS_requestor

      ;; Disable IRQ12
        mov     ah,12
        call    fword ptr ds:_BIOS_iPIC_mask_irq

      ;; Tell the 8042 controller to issue IRQ12 each time the mouse input buffer has data
        mov     ah,060h
        call    fword ptr ds:_iBIOS_write_8042_64h
        mov     ah,01000111b
        call    fword ptr ds:_iBIOS_write_8042_60h

      ;; Enable the PS/2 mouse
        mov     ah,0d4h
        call    fword ptr ds:_iBIOS_write_8042_64h
        mov     ah,0f4h                                             ; Enable the mouse
        call    fword ptr ds:_iBIOS_write_8042_60h

      ;; Enable IRQ12
        mov     ah,12
        call    fword ptr ds:_BIOS_iPIC_unmask_irq
        mov     ds:packet_count,-1                                  ; The mouse will send a one byte response
        clc
        ret
    initialize_driver   ENDP




    MOUSE_handler       PROC
    ; The mouse has signaled that it has data for us
    ;
    ; Upon entry:   Data is waiting at port 60h
    ;
    ; Upon exit:    The byte is stored and/or send to the calling routine for processing
    ;
        pushad
        push    ds
        mov     ds,cs:data_segment

      ;; Signal end-of-interrupt (for IRQ8-IRQ15 we must send two commands)
      MOUSE_handler_quit:
        mov     al,20h
        out     0a0h,al
        out     20h,al
        sti

      ;; See if there is data read
      read_mouse_again:
        in      al,64h
        and     al,21h                                              ; 21h = 20h-mouse has byte + 1h-ready to send
        .IF (al == 21h)
          ;; Read the byte
            in      al,060h
            .IF (cs:packet_count > 7fffffffh)
              ; It's negative, we're loading bytes that are of no consequence
                inc     ds:packet_count
                jmp     read_mouse_again
            .ENDIF

          ;; Store the byte
            mov     esi,offset mouse_buffer
            mov     ebx,cs:packet_count
            mov     byte ptr ds:[esi+ebx],al
            inc     ds:packet_count
            .IF (ebx >= 2)
              ; We have our full packet
                mov     ds:packet_count,0
                mov     esi,offset mouse_buffer

              ;; Get the buttons and sign
                movzx   ebx,byte ptr ds:[esi+0]
                and     ebx,0111b                                   ; ebx = button status

              ;; Get the delta-x
                movsx   eax,byte ptr ds:[esi+1]

              ;; Get the delta-y
                movsx   edx,byte ptr ds:[esi+2]
                neg     edx                                         ; The logical mouse system goes from 0 to max_y in a negative
                                                                    ; direction (0 is top, max_y is bottom of screen).  For this
                                                                    ; reason the sign of this delta-y value is reversed.

              ; Right now,  eax = X delta
              ;             edx = Y delta
              ;             ebx = button status
                .IF (ds:debi_intercept == 1)
                    call    fword ptr ds:_iDEBI_mouse_interface
                .ELSE
                    call    fword ptr ds:_iTASK_mouse_interface
                .ENDIF
            .ENDIF
        .ENDIF

        pop     ds
        popad
        iretd
    MOUSE_handler       ENDP




    iMOUSE_activate_DEBI_intercept      PROC
    ; This routine is called only from DEBI.  It indicates that any MOUSE information should be
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
    iMOUSE_activate_DEBI_intercept      ENDP




;; Bochs hack
    iMOUSE_bochs_DEBI_intercept     PROC
        push    ds
        pushfd
        pushad
        mov     ds,cs:data_segment
        mov     eax,_BOCHS1
        mov     ebx,_BOCHS2
        mov     ecx,_BOCHS_GET_MONO_MOUSE_XY
        int     0ffh
        .IF (!carry?)
            ; Returns new X coordinate in eax
            ; Returns new Y coordinate in ebx
            ; Returns new button state in ecx
            ; Store new mouse coordinates
            mov     ds:_mouseX,ax
            mov     ds:_mouseX,bx

            ; Call DEBI's bochs mouse handler
            call    fword ptr ds:_iDEBI_bochs_mouse_interface
        .ENDIF

        popad
        popfd
        pop     ds
        retf
    iMOUSE_bochs_DEBI_intercept     ENDP
;; Bochs hack




    iMOUSE_deactivate_DEBI_intercept    PROC
    ; This routine is called only from DEBI.  It indicates that any MOUSE information should now be
    ; handled in the normal manner (it should not be sent to the DEBI algorithm)
    ;
    ; Upon entry:   Nothing
    ;
    ; Upon exit:    Input is diverted
    ;
        push    ds
        mov     ds,cs:data_segment
        mov     ds:debi_intercept,0
        pop     ds
        retf
    iMOUSE_deactivate_DEBI_intercept    ENDP









; DATA
    driver_name                             db  "PS/2 Mouse Driver",0
    version                                 db  "10.10.2010 BETA",0
    copyright                               db  "(c) Copyright Beatleworks, Inc.",0
    author                                  db  "Rick C. Hodgin",0
    bootup                                  db  1                   ; Changed to 0 after bootup is complete

    data_segment                            dw  0
    debi_intercept                          db  0
    packet_count                            dd  0

    _rightClick                             db  0                                       ; Right ctrl-key status
    _leftClick                              db  0
    _middleClick                            db  0
    _mouseX                                 dw  0
    _mouseY                                 dw  0

    mouse_buffer                            db  3 dup(0)

    mouse_logo                              db  0           ; * Refer to VGA\INF\VGA.INF for information on this byte's format
                                            db  00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,07h,07h,07h,00h,00h,00h,00h,00h
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


    _EXODUS_requestor                       dw  0
  primative_call_gates:
    _VID_draw_logo                          dw  0
    _VID_display_string_nr_vga              dw  _sEXODUS_REQUESTOR
    _iDEBI_mouse_interface                  dw  0f000h
    _BIOS_iPIC_unmask_irq                   dw  0f000h
    _BIOS_iPIC_mask_irq                     dw  0f000h
    _iBIOS_write_8042_64h                   dw  0f000h
    _iBIOS_write_8042_60h                   dw  0f000h
    _iBIOS_read_8042_64h                    dw  0f000h
    _iBIOS_read_8042_60h                    dw  0f000h
    _iBIOS_read_8042_64h_fast               dw  0f000h
    _iBIOS_read_8042_60h_fast               dw  0f000h
    _iBIOS_write_8042_64h_fast              dw  0f000h
    _iBIOS_write_8042_60h_fast              dw  0f000h
    _TIMER_wait_full_tick                   dw  0f000h
    _TIMER_wait_x_ticks                     dw  0f000h
    _iTASK_mouse_interface                  dw  0f000h
    _iDEBI_bochs_mouse_interface            dw  0f000h
                                            dw  0f000h
                                            dw  0f000h

    required_primatives                     db  13, "VID_draw_logo"
                                            db  25, "VID_display_string_nr_vga"
                                            db  21, "iDEBI_mouse_interface"
                                            db  20, "BIOS_iPIC_unmask_irq"
                                            db  18, "BIOS_iPIC_mask_irq"
                                            db  20, "iBIOS_write_8042_64h"
                                            db  20, "iBIOS_write_8042_60h"
                                            db  19, "iBIOS_read_8042_64h"
                                            db  19, "iBIOS_read_8042_60h"
                                            db  24, "iBIOS_read_8042_64h_fast"
                                            db  24, "iBIOS_read_8042_60h_fast"
                                            db  25, "iBIOS_write_8042_64h_fast"
                                            db  25, "iBIOS_write_8042_60h_fast"
                                            db  20, "TIMER_wait_full_tick"
                                            db  18, "TIMER_wait_x_ticks"
                                            db  21, "iTASK_mouse_interface"
                                            db  27, "iDEBI_bochs_mouse_interface"
                                            db  0ffh

 end_of_required_data:

    driver_primatives                       db  30, "iMOUSE_activate_DEBI_intercept"
                                            dd  offset iMOUSE_activate_DEBI_intercept
                                            dw  0

                                            db  32, "iMOUSE_deactivate_DEBI_intercept"
                                            dd  offset iMOUSE_deactivate_DEBI_intercept
                                            dw  0

                                            db  27, "iMOUSE_bochs_DEBI_intercept"
                                            dd  offset iMOUSE_bochs_DEBI_intercept
                                            dw  0

                                            dw  0ffffh              ; Teriminator

_TEXT32 ENDS

END
