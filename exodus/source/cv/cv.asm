; cv.asm
;
; ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
; ³ CodeView Reader ³
; ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
;
; Exodus native primative
;


TITLE CodeView_Reader

    .MODEL tiny

    .STACK 0h

INCLUDE \exodus\source\common\keylist.asp
INCLUDE \exodus\source\common\equates.asp
INCLUDE \exodus\source\common\macros.asp


    .386P
_TEXT32 SEGMENT BYTE 'CODE' USE32
    ORG 0h
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
            mov     esi,offset required_primatives
            mov     edi,offset primative_call_gates
            clc
        .ELSEIF (eax == 'id  ')
          ; Display this program's ID on the VGA monitor
             mov     esi,offset driver_name
            call    fword ptr cs:_VID_display_string_nr_vga
            clc
        .ELSEIF (eax == 'note')
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
        call    initialize_driver
      ; Right now, carry? is SET or CLEAR indicating status of driver
        retf
    main    ENDP



    initialize_driver   PROC
    ; This routine is used to initialize the driver
    ; But, there is no initialization in this system
        mov     esi,offset cv_boot_logo
        call    fword ptr cs:_VID_draw_logo
        clc
        ret
    initialize_driver   ENDP



    cv_parse      PROC
    ; Main algorithm for parsing a CV debug output block of memory
        retf
    cv_parse      ENDP




; DATA
; This header is part of a continuous NULL-terminated structure
    driver_name                             db  "Low-Level CodeView Reader",0
    version                                 db  "10.10.2010 BETA",0
    copyright                               db  "(c) Copyright Beatleworks, Inc.",0
    author                                  db  "Rick C. Hodgin",0
    cv_reader_text                          db  "CodeView Reader",0
    beatleworks_text                        db  "(c) Beatleworks, Inc.",0

    data_segment                            dw  0

    _EXODUS_requestor                       dw  0
  primative_call_gates:
    _VID_draw_logo                          dw  0
    _VID_display_string_nr_vga              dw  _sEXODUS_REQUESTOR
    _VID_display_string_mono                dw  0f000h
                                            dw  0f000h
                                            dw  0f000h

    required_primatives                     db  13, "VID_draw_logo"
                                            db  25, "VID_display_string_nr_vga"
                                            db  23, "VID_display_string_mono"
                                            db  0ffh

    ; This logo consists of a one-wide image
    cv_boot_logo                            db  88h         ; * Refer to VGA\INF\VGA.INF for information on this byte's format
                                            db  10h,10h,10h,10h,10h,10h,09h,09h,09h,09h,09h,09h,09h,10h,10h,10h,10h,10h
                                            db  10h,10h,10h,10h,09h,0eh,01h,0eh,01h,01h,01h,01h,01h,09h,09h,10h,10h,10h
                                            db  10h,10h,0fh,0fh,01h,04h,0ch,0ch,04h,01h,0fh,0fh,0fh,01h,01h,09h,10h,10h
                                            db  10h,0fh,09h,01h,0fh,04h,0ch,0ch,04h,0fh,09h,09h,01h,0fh,01h,01h,09h,10h
                                            db  10h,09h,01h,01h,01h,0ch,0ch,0ch,0ch,10h,10h,10h,09h,01h,01h,01h,09h,10h
                                            db  10h,09h,01h,0fh,0fh,0ch,0ch,0ch,0ch,0fh,0fh,10h,10h,09h,09h,09h,10h,10h
                                            db  10h,09h,0fh,01h,01h,04h,0ch,0ch,04h,10h,10h,0fh,0fh,10h,10h,10h,10h,10h
                                            db  10h,0fh,01h,01h,01h,0fh,0ch,0ch,0fh,10h,10h,10h,10h,0fh,10h,10h,10h,10h
                                            db  10h,09h,01h,01h,0fh,01h,09h,10h,10h,0fh,10h,10h,10h,10h,10h,10h,10h,10h
                                            db  10h,09h,01h,01h,0fh,01h,09h,10h,10h,10h,0fh,10h,10h,10h,10h,10h,10h,10h
                                            db  10h,09h,01h,0fh,01h,01h,09h,10h,10h,10h,0fh,10h,10h,09h,09h,09h,10h,10h
                                            db  10h,09h,01h,0fh,01h,01h,01h,09h,10h,10h,10h,0fh,09h,01h,01h,01h,09h,10h
                                            db  10h,10h,09h,01h,01h,01h,01h,01h,09h,09h,09h,09h,01h,01h,01h,01h,09h,10h
                                            db  10h,10h,10h,09h,01h,01h,01h,01h,01h,01h,01h,01h,01h,01h,01h,09h,10h,10h
                                            db  10h,10h,10h,10h,09h,09h,01h,01h,01h,01h,01h,01h,01h,09h,09h,10h,10h,10h
                                            db  10h,10h,10h,10h,10h,10h,09h,09h,09h,09h,09h,09h,09h,10h,10h,10h,10h,10h
                                            db  0,0,15h     ; A dark shade of blue for the background

 end_of_required_data:
    driver_primatives                       db  8, "cv_parse"
                                            dd  offset cv_parse
                                            dw  0

                                            dw  0ffffh              ; Teriminator

_TEXT32 ENDS

END
