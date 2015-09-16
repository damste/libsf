; vga.asm
;
; �������������������Ŀ
; � standard VGA/Mono �
; ���������������������
;
; Exodus native primative video functions for VGA and Mono
;
; Note:  Exodus logo is referenced in BOOTUP\REQ.ASP, stored in BOOTUP\BOOT_SCR.INC, and is displayed via VGA\GLOBAL.ASP's VID_draw_exodus_boot_screen() function
;

TITLE standard VGA/Mono Driver

    .386P
    .MODEL tiny
    .STACK 0h
INCLUDE \exodus\source\common\equates.asp
INCLUDE \exodus\source\common\macros.asp
INCLUDE \exodus\source\common\objects.asp

MONO_CRTC_INDEX         EQU 3b4h
MONO_CRTC_DATA          EQU 3b5h
MONO_CRTC_CNTRL         EQU 3b8h
MONO_SCREEN_ON          EQU 8
MONO_GRAPH              EQU 2
MONO_TEXT               EQU 0

MOTHERBOARD_ENABLE      EQU 3c3h
STATUS_REG1             EQU 3dah
CRTC_INDEX              EQU 3d4h
CRTC_DATA               EQU 3d5h
MISC_OUTPUT             EQU 3c2h
SEQ_INDEX               EQU 3c4h
SEQ_DATA                EQU 3c5h
GRAPH_INDEX             EQU 3ceh
GRAPH_DATA              EQU 3cfh
ATTRIB_INDEX            EQU 3c0h
ATTRIB_DATA_WRITE       EQU 3c0h
ATTRIB_DATA_READ        EQU 3c1h
RAMDAC_PIXEL_MASK       EQU 3c6h
RAMDAC_INDEX_READ       EQU 3c7h
RAMDAC_INDEX_WRITE      EQU 3c8h
RAMDAC_DATA             EQU 3c9h

_TEXT32 SEGMENT BYTE 'CODE' USE32
    ASSUME NOTHING

; These are required to be the first 2 dwords in the file
dd offset main
dd offset requestor



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

            mov     esi,offset this_drivers_primatives      ; Offset to the native primatives structure
            mov     edi,offset driver_name
            mov     ebx,offset version
            mov     edx,offset copyright
            mov     ebp,offset author
            clc
        .ELSEIF (eax == 'prim')
          ; Native primatives this program will use
            mov     ds:data_segment,ds
            mov     esi,-1
            clc
        .ELSEIF (eax == 'id  ')
          ; Display this program's ID on the VGA monitor
            mov     esi,offset driver_name
            callf   VID_display_string_nr_vga
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
        mov     ds,cs:data_segment
        mov     ds:bootup,0
        call    initialize_driver
      ; Right now, carry? is SET or CLEAR indicating status of driver
        retf
    main    ENDP




    initialize_driver   PROC
    ; This routine is used to initialize the driver.
    ; It basically enter 320x200 256 color mode and draws the Exodus boot screen
    ; Then draws the VGA logo (since this is the VGA driver)

      ;; Set the VGA video mode to 320x200x8
        push    0                                                   ; return: bits per pixel
        push    0                                                   ; return: horizontal pixels
        push    0                                                   ; return: vertical pixels
        push    0                                                   ; return: refresh rate
        push    0                                                   ; return: status
        push    0                                                   ; input: graphics mode
        push    8                                                   ; input: bits per pixel
        push    320                                                 ; input: horizontal pixels
        push    200                                                 ; input: vertical pixels
        push    60                                                  ; input: refresh rate
        mov     eax,1
        callf   VID_requestor
        add     esp,20                                              ; get the values off the stack (we know this works)

      ;; Tell Exodus we're ready to draw the boot screen
        mov     eax,'boot'
        mov     ebx,'logo'
        call    fword ptr cs:_EXODUS_requestor

      ;; Display the VGA boot logo
        mov     esi,offset vga_logo
        callf   VID_draw_logo

        clc
        ret
    initialize_driver   ENDP




    INCLUDE vga.asp                                                 ; VGA algorithms
    INCLUDE mono.asp                                                ; Monochrome algorithms
    INCLUDE global.asp                                              ; Global algorithms




    VID_requestor   PROC
    ; This routine is used to answer queries by other applications
    ; * Refer to source\inf\requestr.inf for more information
    ;
    ; Upon entry:   eax = request number
    ;               stack is appropriately setup based on request
    ;
    ; Upon exit:    various registers might be updated
    ;
        .IF (eax == 1)
          ; This routine is used to enter a particular video mode
          ;
          ; Upon entry:   stack is setup as shown below
          ;
          ; Upon exit:    return params on stack are updated
          ;               If failure, the horizontal pixels, vertical pixels and refresh rate represent the
          ;                           closest legal value allowed
          ;
          ; [ebp+48] - dword, return - bits per pixel (if graphics was requested, 0 if text)
          ; [ebp+44] - dword, return - horizontal pixels
          ; [ebp+40] - dword, return - vertical pixels
          ; [ebp+36] - dword, return - refresh rate
          ; [ebp+32] - dword, return - status, 1-success, 0-failure
          ; [ebp+28] - dword, 0-graphics, 1-text
          ; [ebp+24] - dword, bits per pixel (if graphics, 0 if text)
          ; [ebp+20] - dword, horizontal pixels
          ; [ebp+16] - dword, vertical pixels
          ; [ebp+12] - dword, refresh rate
          ; [ebp+08] - dword, cs
          ; [ebp+04] - dword, eip
          ; [ebp+00] - dword, ebp
            enter   0,0
            pushad
            push    es
            push    ds

            mov     ds,cs:data_segment
            mov     eax,dword ptr ss:[ebp+20]                       ; horizontal
            mov     ebx,dword ptr ss:[ebp+16]                       ; vertical
            mov     ecx,dword ptr ss:[ebp+24]                       ; bits per pixel
            mov     edx,dword ptr ss:[ebp+28]                       ; video mode
            .IF (eax == 320 && ebx == 200 && ecx == 8 && edx == 0)
              ; graphics, 320x200x8
                call    invVID_entering_graphics_mode
                push    dword ptr offset misc_320x200x8
                push    dword ptr offset seq_320x200x8
                push    dword ptr offset crtc_320x200x8
                push    dword ptr offset graph_320x200x8
                push    dword ptr offset attrib_320x200x8
                push    dword ptr offset exodus_interactive_256_start
                push    dword ptr (offset exodus_interactive_256_end - offset exodus_interactive_256_start) / 4
                call    invVID_write_registers
              ; Right now, we're in 320x200,8 mode
                mov     ax,_sGRAPHICS                               ; Clear the screen
                mov     es,ax
                xor     edi,edi
                mov     ecx,320*200
                xor     al,al
                rep     stosb
                mov     dword ptr ss:[ebp+32],1

              ; Update the system memory area
                mov     ax,_sSYSTEM
                mov     es,ax
                xor     edi,edi
                mov     word ptr es:[edi+_SYSTEM_VGA_HORIZONTAL],320
                mov     word ptr es:[edi+_SYSTEM_VGA_VERTICAL],200
                mov     byte ptr es:[edi+_SYSTEM_VGA_VIDEO_MODE],0  ; 0-graphics
                mov     ds:horizontal_pixels,320
                mov     ds:vertical_pixels,200
                mov     ds:bits_per_pixel,8
            .ELSEIF (eax == 80 && ebx == 25 && edx == 1)
              ; text, 80x25
              ; Set the video mode
                push    dword ptr offset misc_80x25
                push    dword ptr offset seq_80x25
                push    dword ptr offset crtc_80x25
                push    dword ptr offset graph_80x25
                push    dword ptr offset attrib_80x25
                push    dword ptr offset ramdac_16_standard_start
                push    dword ptr (offset ramdac_16_standard_end - offset ramdac_16_standard_start) / 4
                call    invVID_write_registers
              ; Right now, we're in 80x25 text mode

              ; Set the font
                push    dword ptr 16
                push    dword ptr offset font_8x16_base
                call    invVID_vga_set_font

              ; Restore the text mode from it's _sVGA_BACKUP location (if it was there)
                call    invVID_restore_text_mode
                mov     dword ptr ss:[ebp+32],1

              ; Reset the cursor location
                callf   VID_get_cursor_vga
                callf   VID_position_cursor_vga

              ; Update the system memory area
                mov     ax,_sSYSTEM
                mov     es,ax
                xor     edi,edi
                mov     word ptr es:[edi+_SYSTEM_VGA_HORIZONTAL],80
                mov     word ptr es:[edi+_SYSTEM_VGA_VERTICAL],25
                mov     byte ptr es:[edi+_SYSTEM_VGA_VIDEO_MODE],1  ; 1-text
                mov     ds:horizontal_pixels,-1
                mov     ds:vertical_pixels,-1
                mov     ds:bits_per_pixel,-1
            .ELSE
                mov     dword ptr ss:[ebp+32],0
            .ENDIF
            .IF (dword ptr ss:[ebp+32] != 0)
                mov     eax,dword ptr ss:[ebp+28]
                mov     byte ptr ds:current_mode,al
            .ENDIF

            pop     ds
            pop     es
            popad
            leave
            retf 20
        .ELSEIF (eax == 2)
          ; This routine is used to get the parameters of the current video mode
          ;
          ; Upon entry:   bh = device, 0-vga, 1-mono
          ;               bl = vga device number if al=0
          ;
          ; Upon exit:    upper word of eax = bits per pixel (if graphics mode)
          ;               ax = horizontal pixels
          ;               bx = vertical pixels
          ;               ch = refresh rate
          ;               cl = 8x8 font characters per line
          ;               dh = (lower-nibble) 0-primary, 1-secondary display
          ;               dh = (upper-nibble) 0-graphics, 1-text mode
          ;               dl = 8x8 font rows per screen
          ;
            .IF (bh == 0)
              ; Primary
                xor     dh,dh
            .ELSE
              ; Secondary
                mov     dh,1 SHL 4
            .ENDIF
            or      dh,byte ptr cs:current_mode

            xor     eax,eax
            mov     al,byte ptr cs:bits_per_pixel
            shl     eax,16
            mov     ax,word ptr cs:horizontal_pixels
            mov     bx,word ptr cs:vertical_pixels
            mov     ch,byte ptr cs:refresh_rate
            mov     cl,byte ptr cs:chars_per_line
            mov     dl,byte ptr cs:rows_per_screen
        .ENDIF
        retf
    VID_requestor   ENDP







; DATA
    driver_name                             db  "Bootup VGA/Mono Driver",0
    version                                 db  "10.10.2010",0
    copyright                               db  "(c) Copyright Beatleworks, Inc.",0
    author                                  db  "Rick C. Hodgin",0
    bootup                                  db  1                   ; Indicates bootup status, changes to 0 after initialization

    VID_g_owner                             dd  0ffffffffh
    VID_g_count                             dd  0

    data_segment                            dw  (_MIN_PRIMATIVE+1) * 8
    reg1                                    dw  03d4h
    reg2                                    dw  03d5h
    offset_vga                              dw  7*80*2              ; Starts on line 7
    offset_mono                             dw  0
    attribute_vga                           db  7
    attribute_mono                          db  7
    freeze_vga                              db  0
    freeze_mono                             db  0
    storage_ptr                             dd  offset offset_vga   ; pointer to either offset_vga or offset_mono

    bits_per_pixel                          dd  8
    horizontal_pixels                       dd  320
    vertical_pixels                         dd  200
    refresh_rate                            dd  70
    chars_per_line                          dd  40
    rows_per_screen                         dd  25
    current_mode                            dd  1
    vga_backup_mode                         dd  0

    logo_x                                  dd  0
    logo_y                                  dd  0
    highest_palette                         db  0
    next_custom_palette                     db  30h

    VID_g_mono_insert_mode                  dd  1                   ; Default to insert mode


  ;; Monochrome screen data
    mono_write_mode                         dd  0
    mono_display_mode                       dd  0
    mono_video                              dd  MONO_TEXT
    mono_text_crtc                          db  61h,50h,52h,0fh,19h,06h,19h,19h,02h,0dh,0bh,0ch
    mono_graphics_crtc                      db  35h,2dh,2eh,07h,5bh,02h,57h,57h,02h,03h,00h,00h

    current_font                            dd  offset font_8x8_name

    font_8x6_name                           dd  8                   ; bits wide
                                            dd  6                   ; bits tall
                                            dd  offset font_8x6_base
                                            db  "Bitmap 8x6",0

    font_8x8_name                           dd  8                   ; bits wide
                                            dd  8                   ; bits tall
                                            dd  offset font_8x8_base
                                            db  "Bitmap 8x8",0

    font_8x14_name                          dd  8                   ; bits wide
                                            dd  14                  ; bits tall
                                            dd  offset font_8x14_base
                                            db  "Bitmap 8x14",0

    font_8x16_name                          dd  8                   ; bits wide
                                            dd  16                  ; bits tall
                                            dd  offset font_8x16_base
                                            db  "Bitmap 8x16",0

    font_16x16_name                         dd  16                  ; bits wide
                                            dd  16                  ; bits tall
                                            dd  offset font_16x16_base
                                            db  "Bitmap 16x16",0

    INCLUDE bit8x6.fnt
    INCLUDE bit8x8.fnt
    INCLUDE bit8x14.fnt
    INCLUDE bit8x16.fnt
    INCLUDE bit16x16.fnt
    INCLUDE mouse.fnt


  ;; 320x200,8
    misc_320x200x8                          dw  03c2h, 063h, 0ffffh
    seq_320x200x8                           db  03h,01h,0fh,00h,0eh
    crtc_320x200x8                          db  05fh,04fh,050h,082h,054h,080h,0bfh,01fh,000h,041h,000h,000h,000h,000h,000h,000h
                                            db  09ch,08eh,08fh,028h,040h,096h,0b9h,0a3h,0ffh,0ffh,000h,000h,0fch,000h,080h,000h
    graph_320x200x8                         db  00h,00h,00h,00h,00h,40h,05h,0fh,0ffh
    attrib_320x200x8                        db  0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,41h,00h,0fh,00h,00h

  ;; 80x25 text
    misc_80x25                              dw  03c2h, 067h, 0ffffh
    seq_80x25                               db  03h,00h,03h,00h,02h
    crtc_80x25                              db  05fh,04fh,050h,082h,055h,081h,0bfh,01fh,000h,04fh,00dh,00eh,000h,000h,000h,000h
                                            db  09ch,08eh,08fh,028h,01fh,096h,0b9h,0a3h,0ffh,0ffh,000h,000h,0fch,000h,080h,000h
    graph_80x25                             db  00h,00h,00h,00h,00h,10h,0eh,00h,0ffh
    attrib_80x25                            db  0,1,2,3,4,5,14,07,38h,39h,3ah,3bh,3ch,3dh,3eh,3fh,04h,00h,0fh,08h,00h


  ;; Standard VGA palette for 256-color modes
    ramdac_256_standard_start:
                                            db  000, 00h, 00h, 00h, 001, 00h, 00h, 2ah, 002, 00h, 2ah, 00h, 003, 00h, 2ah, 2ah, 004, 2ah, 00h, 00h, 005, 2ah, 00h, 2ah, 006, 2ah, 15h, 00h, 007, 2ah, 2ah, 2ah
                                            db  008, 15h, 15h, 15h, 009, 15h, 15h, 3fh, 010, 15h, 3fh, 15h, 011, 15h, 3fh, 3fh, 012, 3fh, 15h, 15h, 013, 3fh, 15h, 3fh, 014, 3fh, 3fh, 15h, 015, 3fh, 3fh, 3fh
                                            db  016, 00h, 00h, 00h, 017, 05h, 05h, 05h, 018, 08h, 08h, 08h, 019, 0bh, 0bh, 0bh, 020, 0eh, 0eh, 0eh, 021, 11h, 11h, 11h, 022, 14h, 14h, 14h, 023, 18h, 18h, 18h
                                            db  024, 1ch, 1ch, 1ch, 025, 20h, 20h, 20h, 026, 24h, 24h, 24h, 027, 28h, 28h, 28h, 028, 2dh, 2dh, 2dh, 029, 32h, 32h, 32h, 030, 38h, 38h, 38h, 031, 3fh, 3fh, 3fh
                                            db  032, 00h, 00h, 3fh, 033, 10h, 00h, 3fh, 034, 1fh, 00h, 3fh, 035, 2fh, 00h, 3fh, 036, 3fh, 00h, 3fh, 037, 3fh, 00h, 2fh, 038, 3fh, 00h, 1fh, 039, 3fh, 00h, 10h
                                            db  040, 3fh, 00h, 00h, 041, 3fh, 10h, 00h, 042, 3fh, 1fh, 00h, 043, 3fh, 2fh, 00h, 044, 3fh, 3fh, 00h, 045, 2fh, 3fh, 00h, 046, 1fh, 3fh, 00h, 047, 10h, 3fh, 00h
                                            db  048, 00h, 3fh, 00h, 049, 00h, 3fh, 10h, 050, 00h, 3fh, 1fh, 051, 00h, 3fh, 2fh, 052, 00h, 3fh, 3fh, 053, 00h, 2fh, 3fh, 054, 00h, 1fh, 3fh, 055, 00h, 10h, 3fh
                                            db  056, 1fh, 1fh, 3fh, 057, 27h, 1fh, 3fh, 058, 2fh, 1fh, 3fh, 059, 37h, 1fh, 3fh, 060, 3fh, 1fh, 3fh, 061, 3fh, 1fh, 37h, 062, 3fh, 1fh, 2fh, 063, 3fh, 1fh, 27h
                                            db  064, 3fh, 1fh, 1fh, 065, 3fh, 27h, 1fh, 066, 3fh, 2fh, 1fh, 067, 3fh, 37h, 1fh, 068, 3fh, 3fh, 1fh, 069, 37h, 3fh, 1fh, 070, 2fh, 3fh, 1fh, 071, 27h, 3fh, 1fh
                                            db  072, 1fh, 3fh, 1fh, 073, 1fh, 3fh, 27h, 074, 1fh, 3fh, 2fh, 075, 1fh, 3fh, 37h, 076, 1fh, 3fh, 3fh, 077, 1fh, 37h, 3fh, 078, 1fh, 2fh, 3fh, 079, 1fh, 27h, 3fh
                                            db  080, 2dh, 2dh, 3fh, 081, 31h, 2dh, 3fh, 082, 36h, 2dh, 3fh, 083, 3ah, 2dh, 3fh, 084, 3fh, 2dh, 3fh, 085, 3fh, 2dh, 3ah, 086, 3fh, 2dh, 36h, 087, 3fh, 2dh, 31h
                                            db  088, 3fh, 2dh, 2dh, 089, 3fh, 31h, 2dh, 090, 3fh, 36h, 2dh, 091, 3fh, 3ah, 2dh, 092, 3fh, 3fh, 2dh, 093, 3ah, 3fh, 2dh, 094, 36h, 3fh, 2dh, 095, 31h, 3fh, 2dh
                                            db  096, 2dh, 3fh, 2dh, 097, 2dh, 3fh, 31h, 098, 2dh, 3fh, 36h, 099, 2dh, 3fh, 3ah, 100, 2dh, 3fh, 3fh, 101, 2dh, 3ah, 3fh, 102, 2dh, 36h, 3fh, 103, 2dh, 31h, 3fh
                                            db  104, 00h, 00h, 1ch, 105, 07h, 00h, 1ch, 106, 0eh, 00h, 1ch, 107, 15h, 00h, 1ch, 108, 1ch, 00h, 1ch, 109, 1ch, 00h, 15h, 110, 1ch, 00h, 0eh, 111, 1ch, 00h, 07h
                                            db  112, 1ch, 00h, 00h, 113, 1ch, 07h, 00h, 114, 1ch, 0eh, 00h, 115, 1ch, 15h, 00h, 116, 1ch, 1ch, 00h, 117, 15h, 1ch, 00h, 118, 0eh, 1ch, 00h, 119, 07h, 1ch, 00h
                                            db  120, 00h, 1ch, 00h, 121, 00h, 1ch, 07h, 122, 00h, 1ch, 0eh, 123, 00h, 1ch, 15h, 124, 00h, 1ch, 1ch, 125, 00h, 15h, 1ch, 126, 00h, 0eh, 1ch, 127, 00h, 07h, 1ch
                                            db  128, 0eh, 0eh, 1ch, 129, 11h, 0eh, 1ch, 130, 15h, 0eh, 1ch, 131, 18h, 0eh, 1ch, 132, 1ch, 0eh, 1ch, 133, 1ch, 0eh, 18h, 134, 1ch, 0eh, 15h, 135, 1ch, 0eh, 11h
                                            db  136, 1ch, 0eh, 0eh, 137, 1ch, 11h, 0eh, 138, 1ch, 15h, 0eh, 139, 1ch, 18h, 0eh, 140, 1ch, 1ch, 0eh, 141, 18h, 1ch, 0eh, 142, 15h, 1ch, 0eh, 143, 11h, 1ch, 0eh
                                            db  144, 0eh, 1ch, 0eh, 145, 0eh, 1ch, 11h, 146, 0eh, 1ch, 15h, 147, 0eh, 1ch, 18h, 148, 0eh, 1ch, 1ch, 149, 0eh, 18h, 1ch, 150, 0eh, 15h, 1ch, 151, 0eh, 11h, 1ch
                                            db  152, 14h, 14h, 1ch, 153, 16h, 14h, 1ch, 154, 18h, 14h, 1ch, 155, 1ah, 14h, 1ch, 156, 1ch, 14h, 1ch, 157, 1ch, 14h, 1ah, 158, 1ch, 14h, 18h, 159, 1ch, 14h, 16h
                                            db  160, 1ch, 14h, 14h, 161, 1ch, 16h, 14h, 162, 1ch, 18h, 14h, 163, 1ch, 1ah, 14h, 164, 1ch, 1ch, 14h, 165, 1ah, 1ch, 14h, 166, 18h, 1ch, 14h, 167, 16h, 1ch, 14h
                                            db  168, 14h, 1ch, 14h, 169, 14h, 1ch, 16h, 170, 14h, 1ch, 18h, 171, 14h, 1ch, 1ah, 172, 14h, 1ch, 1ch, 173, 14h, 1ah, 1ch, 174, 14h, 18h, 1ch, 175, 14h, 16h, 1ch
                                            db  176, 00h, 00h, 10h, 177, 04h, 00h, 10h, 178, 08h, 00h, 10h, 179, 0ch, 00h, 10h, 180, 10h, 00h, 10h, 181, 10h, 00h, 0ch, 182, 10h, 00h, 08h, 183, 10h, 00h, 04h
                                            db  184, 10h, 00h, 00h, 185, 10h, 04h, 00h, 186, 10h, 08h, 00h, 187, 10h, 0ch, 00h, 188, 10h, 10h, 00h, 189, 0ch, 10h, 00h, 190, 08h, 10h, 00h, 191, 04h, 10h, 00h
                                            db  192, 00h, 10h, 00h, 193, 00h, 10h, 04h, 194, 00h, 10h, 08h, 195, 00h, 10h, 0ch, 196, 00h, 10h, 10h, 197, 00h, 0ch, 10h, 198, 00h, 08h, 10h, 199, 00h, 04h, 10h
                                            db  200, 08h, 08h, 10h, 201, 0ah, 08h, 10h, 202, 0ch, 08h, 10h, 203, 0eh, 08h, 10h, 204, 10h, 08h, 10h, 205, 10h, 08h, 0eh, 206, 10h, 08h, 0ch, 207, 10h, 08h, 0ah
                                            db  208, 10h, 08h, 08h, 209, 10h, 0ah, 08h, 210, 10h, 0ch, 08h, 211, 10h, 0eh, 08h, 212, 10h, 10h, 08h, 213, 0eh, 10h, 08h, 214, 0ch, 10h, 08h, 215, 0ah, 10h, 08h
                                            db  216, 08h, 10h, 08h, 217, 08h, 10h, 0ah, 218, 08h, 10h, 0ch, 219, 08h, 10h, 0eh, 220, 08h, 10h, 10h, 221, 08h, 0eh, 10h, 222, 08h, 0ch, 10h, 223, 08h, 0ah, 10h
                                            db  224, 0bh, 0bh, 10h, 225, 0ch, 0bh, 10h, 226, 0dh, 0bh, 10h, 227, 0fh, 0bh, 10h, 228, 10h, 0bh, 10h, 229, 10h, 0bh, 0fh, 230, 10h, 0bh, 0dh, 231, 10h, 0bh, 0ch
                                            db  232, 10h, 0bh, 0bh, 233, 10h, 0ch, 0bh, 234, 10h, 0dh, 0bh, 235, 10h, 0fh, 0bh, 236, 10h, 10h, 0bh, 237, 0fh, 10h, 0bh, 238, 0dh, 10h, 0bh, 239, 0ch, 10h, 0bh
                                            db  240, 0bh, 10h, 0bh, 241, 0bh, 10h, 0ch, 242, 0bh, 10h, 0dh, 243, 0bh, 10h, 0fh, 244, 0bh, 10h, 10h, 245, 0bh, 0fh, 10h, 246, 0bh, 0dh, 10h, 247, 0bh, 0ch, 10h
                                            db  248, 00h, 00h, 00h, 249, 00h, 00h, 00h, 250, 00h, 00h, 00h, 251, 00h, 00h, 00h, 252, 00h, 00h, 00h, 253, 00h, 00h, 00h, 254, 00h, 00h, 00h, 255, 00h, 00h, 00h
    ramdac_256_standard_end:

    exodus_interactive_256_start:
                                            db  000, 00h, 00h, 00h, 001, 00h, 00h, 2ah, 002, 00h, 2ah, 00h, 003, 00h, 2ah, 2ah, 004, 2ah, 00h, 00h, 005, 2ah, 00h, 2ah, 006, 2ah, 15h, 00h, 007, 2ah, 2ah, 2ah
                                            db  008, 15h, 15h, 15h, 009, 15h, 15h, 3fh, 010, 15h, 3fh, 15h, 011, 15h, 3fh, 3fh, 012, 3fh, 15h, 15h, 013, 3fh, 15h, 3fh, 014, 3fh, 3fh, 15h, 015, 3fh, 3fh, 3fh
    exodus_interactive_256_variable_start:
                                            db  016, 00h, 00h, 00h, 017, 00h, 00h, 00h, 018, 00h, 00h, 00h, 019, 00h, 00h, 00h, 020, 00h, 00h, 00h, 021, 00h, 00h, 00h, 022, 00h, 00h, 00h, 023, 00h, 00h, 00h
                                            db  024, 00h, 00h, 00h, 025, 00h, 00h, 00h, 026, 00h, 00h, 00h, 027, 00h, 00h, 00h, 028, 00h, 00h, 00h, 029, 00h, 00h, 00h, 030, 00h, 00h, 00h, 031, 00h, 00h, 00h
                                            db  032, 00h, 00h, 00h, 033, 00h, 00h, 00h, 034, 00h, 00h, 00h, 035, 00h, 00h, 00h, 036, 00h, 00h, 00h, 037, 00h, 00h, 00h, 038, 00h, 00h, 00h, 039, 00h, 00h, 00h
                                            db  040, 00h, 00h, 00h, 041, 00h, 00h, 00h, 042, 00h, 00h, 00h, 043, 00h, 00h, 00h, 044, 00h, 00h, 00h, 045, 00h, 00h, 00h, 046, 00h, 00h, 00h, 047, 00h, 00h, 00h
                                            db  048, 00h, 00h, 00h, 049, 00h, 00h, 00h, 050, 00h, 00h, 00h, 051, 00h, 00h, 00h, 052, 00h, 00h, 00h, 053, 00h, 00h, 00h, 054, 00h, 00h, 00h, 055, 00h, 00h, 00h
                                            db  056, 00h, 00h, 00h, 057, 00h, 00h, 00h, 058, 00h, 00h, 00h, 059, 00h, 00h, 00h, 060, 00h, 00h, 00h, 061, 00h, 00h, 00h, 062, 00h, 00h, 00h, 063, 00h, 00h, 00h
                                            db  064, 00h, 00h, 00h, 065, 00h, 00h, 00h, 066, 00h, 00h, 00h, 067, 00h, 00h, 00h, 068, 00h, 00h, 00h, 069, 00h, 00h, 00h, 070, 00h, 00h, 00h, 071, 00h, 00h, 00h
                                            db  072, 00h, 00h, 00h, 073, 00h, 00h, 00h, 074, 00h, 00h, 00h, 075, 00h, 00h, 00h, 076, 00h, 00h, 00h, 077, 00h, 00h, 00h, 078, 00h, 00h, 00h, 079, 00h, 00h, 00h
                                            db  080, 00h, 00h, 00h, 081, 00h, 00h, 00h, 082, 00h, 00h, 00h, 083, 00h, 00h, 00h, 084, 00h, 00h, 00h, 085, 00h, 00h, 00h, 086, 00h, 00h, 00h, 087, 00h, 00h, 00h
                                            db  088, 00h, 00h, 00h, 089, 00h, 00h, 00h, 090, 00h, 00h, 00h, 091, 00h, 00h, 00h, 092, 00h, 00h, 00h, 093, 00h, 00h, 00h, 094, 00h, 00h, 00h, 095, 00h, 00h, 00h
                                            db  096, 00h, 00h, 00h, 097, 00h, 00h, 00h, 098, 00h, 00h, 00h, 099, 00h, 00h, 00h, 100, 00h, 00h, 00h, 101, 00h, 00h, 00h, 102, 00h, 00h, 00h, 103, 00h, 00h, 00h
                                            db  104, 00h, 00h, 00h, 105, 00h, 00h, 00h, 106, 00h, 00h, 00h, 107, 00h, 00h, 00h, 108, 00h, 00h, 00h, 109, 00h, 00h, 00h, 110, 00h, 00h, 00h, 111, 00h, 00h, 00h
                                            db  112, 00h, 00h, 00h, 113, 00h, 00h, 00h, 114, 00h, 00h, 00h, 115, 00h, 00h, 00h, 116, 00h, 00h, 00h, 117, 00h, 00h, 00h, 118, 00h, 00h, 00h, 119, 00h, 00h, 00h
                                            db  120, 00h, 00h, 00h, 121, 00h, 00h, 00h, 122, 00h, 00h, 00h, 123, 00h, 00h, 00h, 124, 00h, 00h, 00h, 125, 00h, 00h, 00h, 126, 00h, 00h, 00h, 127, 00h, 00h, 00h
                                            db  128, 00h, 00h, 00h, 129, 00h, 00h, 00h, 130, 00h, 00h, 00h, 131, 00h, 00h, 00h, 132, 00h, 00h, 00h, 133, 00h, 00h, 00h, 134, 00h, 00h, 00h, 135, 00h, 00h, 00h
                                            db  136, 00h, 00h, 00h, 137, 00h, 00h, 00h, 138, 00h, 00h, 00h, 139, 00h, 00h, 00h, 140, 00h, 00h, 00h, 141, 00h, 00h, 00h, 142, 00h, 00h, 00h, 143, 00h, 00h, 00h
                                            db  144, 00h, 00h, 00h, 145, 00h, 00h, 00h, 146, 00h, 00h, 00h, 147, 00h, 00h, 00h, 148, 00h, 00h, 00h, 149, 00h, 00h, 00h, 150, 00h, 00h, 00h, 151, 00h, 00h, 00h
                                            db  152, 00h, 00h, 00h, 153, 00h, 00h, 00h, 154, 00h, 00h, 00h, 155, 00h, 00h, 00h, 156, 00h, 00h, 00h, 157, 00h, 00h, 00h, 158, 00h, 00h, 00h, 159, 00h, 00h, 00h
                                            db  160, 00h, 00h, 00h, 161, 00h, 00h, 00h, 162, 00h, 00h, 00h, 163, 00h, 00h, 00h, 164, 00h, 00h, 00h, 165, 00h, 00h, 00h, 166, 00h, 00h, 00h, 167, 00h, 00h, 00h
                                            db  168, 00h, 00h, 00h, 169, 00h, 00h, 00h, 170, 00h, 00h, 00h, 171, 00h, 00h, 00h, 172, 00h, 00h, 00h, 173, 00h, 00h, 00h, 174, 00h, 00h, 00h, 175, 00h, 00h, 00h
                                            db  176, 00h, 00h, 00h, 177, 00h, 00h, 00h, 178, 00h, 00h, 00h, 179, 00h, 00h, 00h, 180, 00h, 00h, 00h, 181, 00h, 00h, 00h, 182, 00h, 00h, 00h, 183, 00h, 00h, 00h
                                            db  184, 00h, 00h, 00h, 185, 00h, 00h, 00h, 186, 00h, 00h, 00h, 187, 00h, 00h, 00h, 188, 00h, 00h, 00h, 189, 00h, 00h, 00h, 190, 00h, 00h, 00h, 191, 00h, 00h, 00h
                                            db  192, 00h, 00h, 00h, 193, 00h, 00h, 00h, 194, 00h, 00h, 00h, 195, 00h, 00h, 00h, 196, 00h, 00h, 00h, 197, 00h, 00h, 00h, 198, 00h, 00h, 00h, 199, 00h, 00h, 00h
                                            db  200, 00h, 00h, 00h, 201, 00h, 00h, 00h, 202, 00h, 00h, 00h, 203, 00h, 00h, 00h, 204, 00h, 00h, 00h, 205, 00h, 00h, 00h, 206, 00h, 00h, 00h, 207, 00h, 00h, 00h
                                            db  208, 00h, 00h, 00h, 209, 00h, 00h, 00h, 210, 00h, 00h, 00h, 211, 00h, 00h, 00h, 212, 00h, 00h, 00h, 213, 00h, 00h, 00h, 214, 00h, 00h, 00h, 215, 00h, 00h, 00h
                                            db  216, 00h, 00h, 00h, 217, 00h, 00h, 00h, 218, 00h, 00h, 00h, 219, 00h, 00h, 00h, 220, 00h, 00h, 00h, 221, 00h, 00h, 00h, 222, 00h, 00h, 00h, 223, 00h, 00h, 00h
                                            db  224, 00h, 00h, 00h, 225, 00h, 00h, 00h, 226, 00h, 00h, 00h, 227, 00h, 00h, 00h, 228, 00h, 00h, 00h, 229, 00h, 00h, 00h, 230, 00h, 00h, 00h, 231, 00h, 00h, 00h
                                            db  232, 00h, 00h, 00h, 233, 00h, 00h, 00h, 234, 00h, 00h, 00h, 235, 00h, 00h, 00h, 236, 00h, 00h, 00h, 237, 00h, 00h, 00h, 238, 00h, 00h, 00h, 239, 00h, 00h, 00h
                                            db  240, 00h, 00h, 00h, 241, 00h, 00h, 00h, 242, 00h, 00h, 00h, 243, 00h, 00h, 00h, 244, 00h, 00h, 00h, 245, 00h, 00h, 00h, 246, 00h, 00h, 00h, 247, 00h, 00h, 00h
                                            db  248, 00h, 00h, 00h, 249, 00h, 00h, 00h, 250, 00h, 00h, 00h, 251, 00h, 00h, 00h, 252, 00h, 00h, 00h, 253, 00h, 00h, 00h, 254, 00h, 00h, 00h, 255, 00h, 00h, 00h
    exodus_interactive_256_end:

    ramdac_16_standard_start:
                                            db  000, 00h, 00h, 00h, 001, 00h, 00h, 2ah, 002, 00h, 2ah, 00h, 003, 00h, 2ah, 2ah, 004, 2ah, 00h, 00h, 005, 2ah, 00h, 2ah, 006, 2ah, 2ah, 00h, 007, 2ah, 2ah, 2ah
                                            db  008, 00h, 00h, 15h, 009, 00h, 00h, 3fh, 010, 00h, 2ah, 15h, 011, 00h, 2ah, 3fh, 012, 2ah, 00h, 15h, 013, 2ah, 00h, 3fh, 014, 2ah, 2ah, 15h, 015, 2ah, 2ah, 3fh
                                            db  016, 00h, 15h, 00h, 017, 00h, 15h, 2ah, 018, 00h, 3fh, 00h, 019, 00h, 3fh, 2ah, 020, 2ah, 15h, 00h, 021, 2ah, 15h, 2ah, 022, 2ah, 3fh, 00h, 023, 2ah, 3fh, 2ah
                                            db  024, 00h, 15h, 15h, 025, 00h, 15h, 3fh, 026, 00h, 3fh, 15h, 027, 00h, 3fh, 3fh, 028, 2ah, 15h, 15h, 029, 2ah, 15h, 3fh, 030, 2ah, 3fh, 15h, 031, 2ah, 3fh, 3fh
                                            db  032, 15h, 00h, 00h, 033, 15h, 00h, 2ah, 034, 15h, 2ah, 00h, 035, 15h, 2ah, 2ah, 036, 3fh, 00h, 00h, 037, 3fh, 00h, 2ah, 038, 3fh, 2ah, 00h, 039, 3fh, 2ah, 2ah
                                            db  040, 15h, 00h, 15h, 041, 15h, 00h, 3fh, 042, 15h, 2ah, 15h, 043, 15h, 2ah, 3fh, 044, 3fh, 00h, 15h, 045, 3fh, 00h, 3fh, 046, 3fh, 2ah, 15h, 047, 3fh, 2ah, 3fh
                                            db  048, 15h, 15h, 00h, 049, 15h, 15h, 2ah, 050, 15h, 3fh, 00h, 051, 15h, 3fh, 2ah, 052, 3fh, 15h, 00h, 053, 3fh, 15h, 2ah, 054, 3fh, 3fh, 00h, 055, 3fh, 3fh, 2ah
                                            db  056, 15h, 15h, 15h, 057, 15h, 15h, 3fh, 058, 15h, 3fh, 15h, 059, 15h, 3fh, 3fh, 060, 3fh, 15h, 15h, 061, 3fh, 15h, 3fh, 062, 3fh, 3fh, 15h, 063, 3fh, 3fh, 3fh
                                            db  064, 00h, 00h, 00h, 065, 00h, 00h, 00h, 066, 00h, 00h, 00h, 067, 00h, 00h, 00h, 068, 00h, 00h, 00h, 069, 00h, 00h, 00h, 070, 00h, 00h, 00h, 071, 00h, 00h, 00h
                                            db  072, 00h, 00h, 00h, 073, 00h, 00h, 00h, 074, 00h, 00h, 00h, 075, 00h, 00h, 00h, 076, 00h, 00h, 00h, 077, 00h, 00h, 00h, 078, 00h, 00h, 00h, 079, 00h, 00h, 00h
                                            db  080, 00h, 00h, 00h, 081, 00h, 00h, 00h, 082, 00h, 00h, 00h, 083, 00h, 00h, 00h, 084, 00h, 00h, 00h, 085, 00h, 00h, 00h, 086, 00h, 00h, 00h, 087, 00h, 00h, 00h
                                            db  088, 00h, 00h, 00h, 089, 00h, 00h, 00h, 090, 00h, 00h, 00h, 091, 00h, 00h, 00h, 092, 00h, 00h, 00h, 093, 00h, 00h, 00h, 094, 00h, 00h, 00h, 095, 00h, 00h, 00h
                                            db  096, 00h, 00h, 00h, 097, 00h, 00h, 00h, 098, 00h, 00h, 00h, 099, 00h, 00h, 00h, 100, 00h, 00h, 00h, 101, 00h, 00h, 00h, 102, 00h, 00h, 00h, 103, 00h, 00h, 00h
                                            db  104, 00h, 00h, 00h, 105, 00h, 00h, 00h, 106, 00h, 00h, 00h, 107, 00h, 00h, 00h, 108, 00h, 00h, 00h, 109, 00h, 00h, 00h, 110, 00h, 00h, 00h, 111, 00h, 00h, 00h
                                            db  112, 00h, 00h, 00h, 113, 00h, 00h, 00h, 114, 00h, 00h, 00h, 115, 00h, 00h, 00h, 116, 00h, 00h, 00h, 117, 00h, 00h, 00h, 118, 00h, 00h, 00h, 119, 00h, 00h, 00h
                                            db  120, 00h, 00h, 00h, 121, 00h, 00h, 00h, 122, 00h, 00h, 00h, 123, 00h, 00h, 00h, 124, 00h, 00h, 00h, 125, 00h, 00h, 00h, 126, 00h, 00h, 00h, 127, 00h, 00h, 00h
                                            db  128, 00h, 00h, 00h, 129, 00h, 00h, 00h, 130, 00h, 00h, 00h, 131, 00h, 00h, 00h, 132, 00h, 00h, 00h, 133, 00h, 00h, 00h, 134, 00h, 00h, 00h, 135, 00h, 00h, 00h
                                            db  136, 00h, 00h, 00h, 137, 00h, 00h, 00h, 138, 00h, 00h, 00h, 139, 00h, 00h, 00h, 140, 00h, 00h, 00h, 141, 00h, 00h, 00h, 142, 00h, 00h, 00h, 143, 00h, 00h, 00h
                                            db  144, 00h, 00h, 00h, 145, 00h, 00h, 00h, 146, 00h, 00h, 00h, 147, 00h, 00h, 00h, 148, 00h, 00h, 00h, 149, 00h, 00h, 00h, 150, 00h, 00h, 00h, 151, 00h, 00h, 00h
                                            db  152, 00h, 00h, 00h, 153, 00h, 00h, 00h, 154, 00h, 00h, 00h, 155, 00h, 00h, 00h, 156, 00h, 00h, 00h, 157, 00h, 00h, 00h, 158, 00h, 00h, 00h, 159, 00h, 00h, 00h
                                            db  160, 00h, 00h, 00h, 161, 00h, 00h, 00h, 162, 00h, 00h, 00h, 163, 00h, 00h, 00h, 164, 00h, 00h, 00h, 165, 00h, 00h, 00h, 166, 00h, 00h, 00h, 167, 00h, 00h, 00h
                                            db  168, 00h, 00h, 00h, 169, 00h, 00h, 00h, 170, 00h, 00h, 00h, 171, 00h, 00h, 00h, 172, 00h, 00h, 00h, 173, 00h, 00h, 00h, 174, 00h, 00h, 00h, 175, 00h, 00h, 00h
                                            db  176, 00h, 00h, 00h, 177, 00h, 00h, 00h, 178, 00h, 00h, 00h, 179, 00h, 00h, 00h, 180, 00h, 00h, 00h, 181, 00h, 00h, 00h, 182, 00h, 00h, 00h, 183, 00h, 00h, 00h
                                            db  184, 00h, 00h, 00h, 185, 00h, 00h, 00h, 186, 00h, 00h, 00h, 187, 00h, 00h, 00h, 188, 00h, 00h, 00h, 189, 00h, 00h, 00h, 190, 00h, 00h, 00h, 191, 00h, 00h, 00h
                                            db  192, 00h, 00h, 00h, 193, 00h, 00h, 00h, 194, 00h, 00h, 00h, 195, 00h, 00h, 00h, 196, 00h, 00h, 00h, 197, 00h, 00h, 00h, 198, 00h, 00h, 00h, 199, 00h, 00h, 00h
                                            db  200, 00h, 00h, 00h, 201, 00h, 00h, 00h, 202, 00h, 00h, 00h, 203, 00h, 00h, 00h, 204, 00h, 00h, 00h, 205, 00h, 00h, 00h, 206, 00h, 00h, 00h, 207, 00h, 00h, 00h
                                            db  208, 00h, 00h, 00h, 209, 00h, 00h, 00h, 210, 00h, 00h, 00h, 211, 00h, 00h, 00h, 212, 00h, 00h, 00h, 213, 00h, 00h, 00h, 214, 00h, 00h, 00h, 215, 00h, 00h, 00h
                                            db  216, 00h, 00h, 00h, 217, 00h, 00h, 00h, 218, 00h, 00h, 00h, 219, 00h, 00h, 00h, 220, 00h, 00h, 00h, 221, 00h, 00h, 00h, 222, 00h, 00h, 00h, 223, 00h, 00h, 00h
                                            db  224, 00h, 00h, 00h, 225, 00h, 00h, 00h, 226, 00h, 00h, 00h, 227, 00h, 00h, 00h, 228, 00h, 00h, 00h, 229, 00h, 00h, 00h, 230, 00h, 00h, 00h, 231, 00h, 00h, 00h
                                            db  232, 00h, 00h, 00h, 233, 00h, 00h, 00h, 234, 00h, 00h, 00h, 235, 00h, 00h, 00h, 236, 00h, 00h, 00h, 237, 00h, 00h, 00h, 238, 00h, 00h, 00h, 239, 00h, 00h, 00h
                                            db  240, 00h, 00h, 00h, 241, 00h, 00h, 00h, 242, 00h, 00h, 00h, 243, 00h, 00h, 00h, 244, 00h, 00h, 00h, 245, 00h, 00h, 00h, 246, 00h, 00h, 00h, 247, 00h, 00h, 00h
                                            db  248, 00h, 00h, 00h, 249, 00h, 00h, 00h, 250, 00h, 00h, 00h, 251, 00h, 00h, 00h, 252, 00h, 00h, 00h, 253, 00h, 00h, 00h, 254, 00h, 00h, 00h, 255, 00h, 00h, 00h
    ramdac_16_standard_end:


    vga_logo                                db  0       ; how many extra 18x16 pictures wide?
                                            db  00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
                                            db  00h,00h,00h,10h,10h,10h,10h,07h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
                                            db  00h,00h,01h,0fh,0fh,0fh,0fh,10h,10h,10h,07h,00h,00h,00h,00h,00h,00h,00h
                                            db  00h,00h,09h,0fh,0fh,0fh,0fh,0fh,0fh,0fh,10h,10h,07h,00h,00h,00h,00h,00h
                                            db  00h,00h,09h,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,10h,10h,10h,10h,10h,00h
                                            db  00h,00h,09h,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,11h,00h
                                            db  00h,00h,09h,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,11h,00h
                                            db  00h,00h,09h,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,11h,00h
                                            db  00h,00h,09h,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,11h,00h
                                            db  00h,00h,09h,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,10h,11h,00h
                                            db  00h,00h,01h,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,10h,10h,10h,10h,11h,00h
                                            db  00h,00h,0ah,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,10h,00h,00h,00h,00h,00h
                                            db  00h,00h,00h,0fh,0fh,0fh,0fh,0fh,0fh,0fh,10h,10h,10h,00h,00h,00h,00h,00h
                                            db  00h,00h,00h,00h,00h,00h,00h,07h,07h,07h,00h,00h,00h,00h,00h,00h,00h,00h
                                            db  00h,00h,00h,00h,00h,00h,07h,07h,07h,07h,07h,00h,00h,00h,00h,00h,00h,00h
                                            db  00h,00h,00h,00h,07h,07h,07h,07h,07h,07h,07h,07h,07h,00h,00h,00h,00h,00h
                                            db  3ah,3ah,3ah
                                            db  37h,37h,37h

    _EXODUS_requestor                       dw  0
                                            dw  0
                                            dw  _sEXODUS_REQUESTOR

 end_of_required_data:
    this_drivers_primatives                 db  20, "VID_clear_screen_vga"
                                            dd  offset VID_clear_screen_vga
                                            dw  0

                                            db  33, "VID_display_decimal_in_edx_nr_vga"
                                            dd  offset VID_display_decimal_in_edx_nr_vga
                                            dw  0

                                            db  30, "VID_display_decimal_in_edx_vga"
                                            dd  offset VID_display_decimal_in_edx_vga
                                            dw  0

                                            db  33, "VID_display_hex_string_ecx_nr_vga"
                                            dd  offset VID_display_hex_string_ecx_nr_vga
                                            dw  0

                                            db  33, "VID_display_hex_string_ecx_ro_vga"
                                            dd  offset VID_display_hex_string_ecx_ro_vga
                                            dw  0

                                            db  30, "VID_display_hex_string_ecx_vga"
                                            dd  offset VID_display_hex_string_ecx_vga
                                            dw  0

                                            db  37, "VID_display_hexidecimal_in_edx_nr_vga"
                                            dd  offset VID_display_hexidecimal_in_edx_nr_vga
                                            dw  0

                                            db  34, "VID_display_hexidecimal_in_edx_vga"
                                            dd  offset VID_display_hexidecimal_in_edx_vga
                                            dw  0

                                            db  31, "VID_display_radix_in_edx_nr_vga"
                                            dd  offset VID_display_radix_in_edx_nr_vga
                                            dw  0

                                            db  28, "VID_display_radix_in_edx_vga"
                                            dd  offset VID_display_radix_in_edx_vga
                                            dw  0

                                            db  29, "VID_display_string_ecx_nr_vga"
                                            dd  offset VID_display_string_ecx_nr_vga
                                            dw  0

                                            db  26, "VID_display_string_ecx_vga"
                                            dd  offset VID_display_string_ecx_vga
                                            dw  0

                                            db  25, "VID_display_string_nr_vga"
                                            dd  offset VID_display_string_nr_vga
                                            dw  0

                                            db  22, "VID_display_string_vga"
                                            dd  offset VID_display_string_vga
                                            dw  0

                                            db  20, "VID_freeze_frame_vga"
                                            dd  offset VID_freeze_frame_vga
                                            dw  0

                                            db  18, "VID_get_cursor_vga"
                                            dd  offset VID_get_cursor_vga
                                            dw  0

                                            db  25, "VID_move_to_next_line_vga"
                                            dd  offset VID_move_to_next_line_vga
                                            dw  0

                                            db  23, "VID_position_cursor_vga"
                                            dd  offset VID_position_cursor_vga
                                            dw  0

                                            db  21, "VID_set_attribute_vga"
                                            dd  offset VID_set_attribute_vga
                                            dw  0

                                            db  25, "VID_set_registers_for_vga"
                                            dd  offset VID_set_registers_for_vga
                                            dw  0

                                            db  21, "VID_clear_screen_mono"
                                            dd  offset VID_clear_screen_mono
                                            dw  0

                                            db  31, "VID_display_decimal_in_edx_mono"
                                            dd  offset VID_display_decimal_in_edx_mono
                                            dw  0

                                            db  34, "VID_display_decimal_in_edx_nr_mono"
                                            dd  offset VID_display_decimal_in_edx_nr_mono
                                            dw  0

                                            db  31, "VID_display_hex_string_ecx_mono"
                                            dd  offset VID_display_hex_string_ecx_mono
                                            dw  0

                                            db  34, "VID_display_hex_string_ecx_nr_mono"
                                            dd  offset VID_display_hex_string_ecx_nr_mono
                                            dw  0

                                            db  34, "VID_display_hex_string_ecx_ro_mono"
                                            dd  offset VID_display_hex_string_ecx_ro_mono
                                            dw  0

                                            db  35, "VID_display_hexidecimal_in_edx_mono"
                                            dd  offset VID_display_hexidecimal_in_edx_mono
                                            dw  0

                                            db  38, "VID_display_hexidecimal_in_edx_nr_mono"
                                            dd  offset VID_display_hexidecimal_in_edx_nr_mono
                                            dw  0

                                            db  29, "VID_display_radix_in_edx_mono"
                                            dd  offset VID_display_radix_in_edx_mono
                                            dw  0

                                            db  32, "VID_display_radix_in_edx_nr_mono"
                                            dd  offset VID_display_radix_in_edx_nr_mono
                                            dw  0

                                            db  27, "VID_display_string_ecx_mono"
                                            dd  offset VID_display_string_ecx_mono
                                            dw  0

                                            db  30, "VID_display_string_ecx_nr_mono"
                                            dd  offset VID_display_string_ecx_nr_mono
                                            dw  0

                                            db  23, "VID_display_string_mono"
                                            dd  offset VID_display_string_mono
                                            dw  0

                                            db  26, "VID_display_string_nr_mono"
                                            dd  offset VID_display_string_nr_mono
                                            dw  0

                                            db  21, "VID_freeze_frame_mono"
                                            dd  offset VID_freeze_frame_mono
                                            dw  0

                                            db  19, "VID_get_cursor_mono"
                                            dd  offset VID_get_cursor_mono
                                            dw  0

                                            db  26, "VID_move_to_next_line_mono"
                                            dd  offset VID_move_to_next_line_mono
                                            dw  0

                                            db  24, "VID_position_cursor_mono"
                                            dd  offset VID_position_cursor_mono
                                            dw  0

                                            db  22, "VID_set_attribute_mono"
                                            dd  offset VID_set_attribute_mono
                                            dw  0

                                            db  26, "VID_set_registers_for_mono"
                                            dd  offset VID_set_registers_for_mono
                                            dw  0

                                            db  21, "VID_clear_screen_both"
                                            dd  offset VID_clear_screen_both
                                            dw  0

                                            db  31, "VID_display_decimal_in_edx_both"
                                            dd  offset VID_display_decimal_in_edx_both
                                            dw  0

                                            db  34, "VID_display_decimal_in_edx_nr_both"
                                            dd  offset VID_display_decimal_in_edx_nr_both
                                            dw  0

                                            db  31, "VID_display_hex_string_ecx_both"
                                            dd  offset VID_display_hex_string_ecx_both
                                            dw  0

                                            db  34, "VID_display_hex_string_ecx_nr_both"
                                            dd  offset VID_display_hex_string_ecx_nr_both
                                            dw  0

                                            db  34, "VID_display_hex_string_ecx_ro_both"
                                            dd  offset VID_display_hex_string_ecx_ro_both
                                            dw  0

                                            db  35, "VID_display_hexidecimal_in_edx_both"
                                            dd  offset VID_display_hexidecimal_in_edx_both
                                            dw  0

                                            db  38, "VID_display_hexidecimal_in_edx_nr_both"
                                            dd  offset VID_display_hexidecimal_in_edx_nr_both
                                            dw  0

                                            db  23, "VID_display_string_both"
                                            dd  offset VID_display_string_both
                                            dw  0

                                            db  32, "VID_display_radix_in_edx_nr_both"
                                            dd  offset VID_display_radix_in_edx_nr_both
                                            dw  0

                                            db  27, "VID_display_string_ecx_both"
                                            dd  offset VID_display_string_ecx_both
                                            dw  0

                                            db  30, "VID_display_string_ecx_nr_both"
                                            dd  offset VID_display_string_ecx_nr_both
                                            dw  0

                                            db  26, "VID_display_string_nr_both"
                                            dd  offset VID_display_string_nr_both
                                            dw  0

                                            db  21, "VID_freeze_frame_both"
                                            dd  offset VID_freeze_frame_both
                                            dw  0

                                            db  26, "VID_move_to_next_line_both"
                                            dd  offset VID_move_to_next_line_both
                                            dw  0

                                            db  24, "VID_position_cursor_both"
                                            dd  offset VID_position_cursor_both
                                            dw  0

                                            db  22, "VID_set_attribute_both"
                                            dd  offset VID_set_attribute_both
                                            dw  0

                                            db  30, "VID_g_mono_enter_graphics_mode"
                                            dd  offset VID_g_mono_enter_graphics_mode
                                            dw  0

                                            db  24, "VID_mono_enter_text_mode"
                                            dd  offset VID_mono_enter_text_mode
                                            dw  0

                                            db  23, "VID_g_mono_display_text"
                                            dd  offset VID_g_mono_display_text
                                            dw  0

                                            db  28, "VID_g_mono_display_text_mode"
                                            dd  offset VID_g_mono_display_text_mode
                                            dw  0

                                            db  24, "VID_g_mono_mouse_pointer"
                                            dd  offset VID_g_mono_mouse_pointer
                                            dw  0

                                            db  26, "VID_g_mono_window_function"
                                            dd  offset VID_g_mono_window_function
                                            dw  0

                                            db  17, "VID_g_mono_cursor"
                                            dd  offset VID_g_mono_cursor
                                            dw  0

                                            db  27, "VID_g_mono_cursor_no_insert"
                                            dd  offset VID_g_mono_cursor_no_insert
                                            dw  0

                                            db  23, "VID_g_mono_clear_screen"
                                            dd  offset VID_g_mono_clear_screen
                                            dw  0

                                            db  18, "VID_g_set_font_8x6"
                                            dd  offset VID_g_set_font_8x6
                                            dw  0

                                            db  18, "VID_g_set_font_8x8"
                                            dd  offset VID_g_set_font_8x8
                                            dw  0

                                            db  19, "VID_g_set_font_8x14"
                                            dd  offset VID_g_set_font_8x14
                                            dw  0

                                            db  20, "VID_g_set_font_16x16"
                                            dd  offset VID_g_set_font_16x16
                                            dw  0

                                            db  13, "VID_draw_logo"
                                            dd  offset VID_draw_logo
                                            dw  0

                                            db  13, "VID_requestor"
                                            dd  offset VID_requestor
                                            dw  0

                                            db  31, "VID_g_display_radix_in_edx_mono"
                                            dd  offset VID_g_display_radix_in_edx_mono
                                            dw  0

                                            db  21, "VID_g_claim_ownership"
                                            dd  offset VID_g_claim_ownership
                                            dw  0

                                            db  23, "VID_g_release_ownership"
                                            dd  offset VID_g_release_ownership
                                            dw  0

                                            db  20, "VID_g_fill_rectangle"
                                            dd  offset VID_g_fill_rectangle
                                            dw  0

                                            db  27, "VID_draw_exodus_boot_screen"
                                            dd  offset VID_draw_exodus_boot_screen
                                            dw  0

                                            db  18, "VID_g_derive_color"
                                            dd  offset VID_g_derive_color
                                            dw  0

                                            db  15, "VID_g_draw_text"
                                            dd  offset VID_g_draw_text
                                            dw  0

                                            db  19, "VID_g_mouse_pointer"
                                            dd  offset VID_g_mouse_pointer
                                            dw  0

                                            dw  0ffffh              ; Teriminator

_TEXT32 ENDS

END