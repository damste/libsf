; x86.asm
;
; 旼컴컴컴컴컴컴컴컴컴컴컴커
; � Disassembly Algorithms �
; 읕컴컴컴컴컴컴컴컴컴컴컴켸
;
; Exodus native primative
;


TITLE Disasm

    .MODEL tiny

    .STACK 0h

INCLUDE \exodus\source\common\keylist.asp
INCLUDE \exodus\source\common\equates.asp
INCLUDE \exodus\source\common\macros.asp


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
        mov     esi,offset x86_boot_logo
        call    fword ptr cs:_VID_draw_logo
        clc
        ret
    initialize_driver   ENDP




;  x86_disassemble()
;  x86_simplify_disassembly()
;  x86_assemble()
;  x86_disassemble_fpu_opcode()
    INCLUDE disasm.asp
    INCLUDE asm.asp




; DATA
    driver_name                             db  "Low-Level x86 Disassember",0
    version                                 db  "10.10.2010 BETA",0
    copyright                               db  "(c) Copyright Beatleworks, Inc.",0
    author                                  db  "Rick C. Hodgin",0
    x86_text                                db  "x86 Disassembler",0
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
    x86_boot_logo                           db  89h         ; * Refer to VGA\INF\VGA.INF for information on this byte's format
                                            db  11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,09h,09h,09h,09h,09h,09h,09h,09h,11h,11h,11h,11h,09h,09h,09h,09h,09h,09h,09h,09h,11h,11h,11h
                                            db  11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,09h,10h,10h,01h,10h,10h,01h,10h,10h,09h,11h,11h,09h,10h,10h,01h,10h,10h,01h,10h,10h,09h,11h,11h
                                            db  11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,09h,10h,10h,01h,10h,10h,01h,10h,10h,09h,11h,11h,09h,10h,10h,01h,10h,10h,01h,10h,10h,09h,11h,11h
                                            db  11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,09h,01h,01h,09h,09h,09h,09h,01h,01h,09h,11h,11h,09h,01h,01h,09h,09h,09h,09h,09h,09h,09h,11h,11h
                                            db  11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,11h,09h,10h,10h,09h,11h,11h,09h,10h,10h,09h,11h,11h,09h,10h,10h,09h,11h,11h,11h,11h,11h,11h,11h,11h
                                            db  11h,11h,11h,09h,09h,09h,11h,11h,11h,09h,09h,09h,11h,11h,09h,10h,10h,09h,11h,11h,09h,10h,10h,09h,11h,11h,09h,10h,10h,09h,11h,11h,11h,11h,11h,11h,11h,11h
                                            db  11h,11h,09h,01h,01h,01h,09h,11h,09h,01h,01h,01h,09h,11h,09h,01h,01h,09h,09h,09h,09h,01h,01h,09h,11h,11h,09h,01h,01h,09h,09h,09h,09h,09h,09h,11h,11h,11h
                                            db  11h,11h,09h,01h,01h,01h,09h,11h,09h,01h,01h,01h,09h,11h,09h,10h,10h,01h,10h,10h,01h,10h,10h,09h,11h,11h,09h,10h,10h,01h,10h,10h,01h,10h,10h,09h,11h,11h
                                            db  11h,11h,11h,09h,01h,01h,01h,09h,01h,01h,01h,09h,11h,11h,09h,10h,10h,01h,10h,10h,01h,10h,10h,09h,11h,11h,09h,10h,10h,01h,10h,10h,01h,10h,10h,09h,11h,11h
                                            db  11h,11h,11h,11h,09h,01h,01h,01h,01h,01h,09h,11h,11h,11h,09h,01h,01h,09h,09h,09h,09h,01h,01h,09h,11h,11h,09h,01h,01h,09h,09h,09h,09h,01h,01h,09h,11h,11h
                                            db  11h,11h,11h,11h,11h,09h,01h,01h,01h,09h,11h,11h,11h,11h,09h,10h,10h,09h,11h,11h,09h,10h,10h,09h,11h,11h,09h,10h,10h,09h,11h,11h,09h,10h,10h,09h,11h,11h
                                            db  11h,11h,11h,11h,09h,01h,01h,01h,01h,01h,09h,11h,11h,11h,09h,10h,10h,09h,11h,11h,09h,10h,10h,09h,11h,11h,09h,10h,10h,09h,11h,11h,09h,10h,10h,09h,11h,11h
                                            db  11h,11h,11h,09h,01h,01h,01h,09h,01h,01h,01h,09h,11h,11h,09h,01h,01h,09h,09h,09h,09h,01h,01h,09h,11h,11h,09h,01h,01h,09h,09h,09h,09h,01h,01h,09h,11h,11h
                                            db  11h,11h,09h,01h,01h,01h,09h,11h,09h,01h,01h,01h,09h,11h,09h,10h,10h,01h,10h,10h,01h,10h,10h,09h,11h,11h,09h,10h,10h,01h,10h,10h,01h,10h,10h,09h,11h,11h
                                            db  11h,11h,09h,01h,01h,01h,09h,11h,09h,01h,01h,01h,09h,11h,09h,10h,10h,01h,10h,10h,01h,10h,10h,09h,11h,11h,09h,10h,10h,01h,10h,10h,01h,10h,10h,09h,11h,11h
                                            db  11h,11h,11h,09h,09h,09h,11h,11h,11h,09h,09h,09h,11h,11h,11h,09h,09h,09h,09h,09h,09h,09h,09h,11h,11h,11h,11h,09h,09h,09h,09h,09h,09h,09h,09h,11h,11h,11h
                                            db  0,0,45      ; Slightly brighter blue
                                            db  0,0,21      ; Darker background blue

 end_of_required_data:
    driver_primatives                       db  15, "x86_disassemble"
                                            dd  offset x86_disassemble
                                            dw  0

                                            db  24, "x86_simplify_disassembly"
                                            dd  offset x86_simplify_disassembly
                                            dw  0

                                            db  12, "x86_assemble"
                                            dd  offset x86_assemble
                                            dw  0

                                            db  14, "x86_fpu_opcode"
                                            dd  offset x86_fpu_opcode
                                            dw  0

                                            dw  0ffffh              ; Teriminator

_TEXT32 ENDS

END
