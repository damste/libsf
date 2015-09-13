; exodus.asm
;
; 旼컴컴컴컴컴컴컴컴컴컴컴컴커
; � Exodus Top-Level Program �
; 읕컴컴컴컴컴컴컴컴컴컴컴컴켸
;
; Exodus Top-Level Program.  From here all things are done
;
;

TITLE Exodus

    .MODEL tiny

    .STACK 0h

INCLUDE \exodus\source\common\equates.asp
INCLUDE \exodus\source\common\objects.asp
INCLUDE ex_eq.asp

    .386P
_TEXT32 SEGMENT BYTE 'CODE' USE32
    ASSUME NOTHING
; These are required to be the first 2 dwords in the file
dd  offset main
dd  offset requestor




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
        clc
        retf
    main    ENDP




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



    EXODUS_dot_com      PROC
    ; This routine is the first program called after the initial bootup is completed
      ;; Indicate system status
        mov     ds,cs:data_segment
        mov     ds:booting_up,1
        mov     ds:shutdown,0

      ;; Clear the VGA screen
        push    0                                                   ; upper-left
        push    0                                                   ; lower-right
        mov     eax,_sSYSTEM
        mov     ds,eax
        movzx   eax,word ptr ds:[_SYSTEM_VGA_HORIZONTAL]            ; width
        movzx   ebx,word ptr ds:[_SYSTEM_VGA_VERTICAL]              ; height
        mov     ds,cs:data_segment
        mov     ds:desktop_width,eax
        mov     ds:desktop_height,ebx
        push    eax
        push    ebx
        push    0                                                   ; color
        call    fword ptr ds:_VID_g_fill_rectangle

      ;; Create the main window
        call    invEXODUS_create_desktop

      ;; Set focus on the main Exodus program
        mov     ax,1                                                ; This task's handle
        call    fword ptr ds:_TASK_set_focus


;        call    fword ptr ds:_VID_test_routine

;;
;;
;; Wait for events!
;;
;;
;; Note, this bit of code does two things.
;;
;;   #1 it sets up Exodus to wait for events so the system can act on them when they occur
;;   #2 it receives control from the tasking system when it is is in an idle state an no tasks are using idle cpu time
;;      When #2 occurs this task simply waits for an interrupt and then returns
;;
        mov     ds,cs:data_segment
        mov     ds:booting_up,0
        call    fword ptr ds:_TASK_read_events
        .WHILE (cs:shutdown != 10101010b)
            call    fword ptr cs:_Exodus_TASK_release_timeslice
        .ENDW

;;
;; When control reaches this point we're shutting down Exodus
;;
      @@:
;int 3
        hlt
        jmp @B
    EXODUS_dot_com      ENDP




    invEXODUS_create_desktop        PROC
    ; This routine creates the main desktop window based on the current screen resolution
    ;
    ; Upon entry:   Nothing
    ;
    ; Upon exit:    The VGA screen is displayed with the standard Exodus Screen
    ;
        push    eax
        push    esi

      ;; Set some required variables based on the current video mode
      ; Exodus bar rectangle records
        mov     edx,ds:desktop_height
        sub     edx,29
        mov     ds:ebr_top,edx
        mov     ecx,ds:desktop_width
        mov     ds:ebr_width,ecx
      ; Exodus bar line
        mov     edx,ds:desktop_height
        sub     edx,30
        mov     ds:ebl_top,edx
        mov     ecx,ds:desktop_width
        mov     ds:ebl_width,ecx
      ; The Exodus button
        mov     edx,ds:desktop_height
        sub     edx,27
        mov     ds:ebb_top,edx
      ; The "Exodus" text on the button
        mov     edx,ds:desktop_height
        sub     edx,22
        mov     ds:ebt_top,edx
        mov     ds:ebt_segment,ds
      ; The Exodus button rectangle (where the spinning logo will be displayed)
        mov     edx,ds:desktop_height
        sub     edx,25
        mov     ds:eblr_top,edx

      ;; Create the desktop
        mov     eax,1                                               ; This task's handle
        mov     esi,offset exodus_desktop
        call    fword ptr ds:_OBJECT_create_base_object

      ;; Add items to the desktop
        xor     ebx,ebx
        mov     esi,offset exodus_bar_rectangle                     ; Rectangle beneath the Exodus button
        call    fword ptr ds:_OBJECT_create_object

        mov     esi,offset exodus_bar_line                          ; Line above the rectangle
        call    fword ptr ds:_OBJECT_create_object

        mov     esi,offset exodus_button_border                     ; Box around the Exodus button
        call    fword ptr ds:_OBJECT_create_object

        mov     esi,offset exodus_button_text                       ; The "Exodus" text
        call    fword ptr ds:_OBJECT_create_object

        mov     esi,offset exodus_button_logo_rectangle             ; The Exodus button logo rectangle
        call    fword ptr ds:_OBJECT_create_object

        pop     esi
        pop     eax
        ret
    invEXODUS_create_desktop        ENDP




    invEXODUS_write_screen      PROC
        pushad
        push    es
        mov     ax,_sMONO
        mov     es,ax
        .REPEAT
            mov     al,byte ptr cs:[esi]
            inc     esi
            stosb
            mov     al,7
            stosb
        .UNTILCXZ
        pop     es
        popad
        ret
    invEXODUS_write_screen      ENDP







; DATA relating to Exodus objects
    INCLUDE ex_data.asp


; DATA
    driver_name                             db  "Exodus Operating System",0
    version                                 db  "10.10.2010 BETA",0
    copyright                               db  "(c) Copyright Beatleworks, Inc.",0
    author                                  db  "Rick C. Hodgin",0
    bootup                                  db  1                   ; Changed to 0 after initial bootup is complete

    exodus_button                           db  "Exodus",0

    booting_up                              dd  1                   ; Changed to 0 after Exodus.com has fully initialized itself
    shutdown                                dd  0
    data_segment                            dw  0


    _EXODUS_requestor                       dw  0
  primative_call_gates:
    _TASK_set_focus                         dw  0
    _VID_display_string_nr_vga              dw  _sEXODUS_REQUESTOR
    _VID_g_fill_rectangle                   dw  0f000h
    _OBJECT_create_base_object              dw  0f000h
    _OBJECT_create_object                   dw  0f000h
    _VID_g_derive_color                     dw  0f000h
    _TASK_read_events                       dw  0f000h
    _Exodus_TASK_release_timeslice          dw  0f000h
                                            dw  0f000h
                                            dw  0f000h

    required_primatives                     db  14, "TASK_set_focus"
                                            db  25, "VID_display_string_nr_vga"
                                            db  20, "VID_g_fill_rectangle"
                                            db  25, "OBJECT_create_base_object"
                                            db  20, "OBJECT_create_object"
                                            db  18, "VID_g_derive_color"
                                            db  16, "TASK_read_events"
                                            db  29, "Exodus_TASK_release_timeslice"
                                            db  0ffh

 end_of_required_data:
    driver_primatives:
                                            db  14, "EXODUS_dot_com"
                                            dd  offset EXODUS_dot_com
                                            dw  0

                                            dw  0ffffh              ; Teriminator

_TEXT32 ENDS

END
