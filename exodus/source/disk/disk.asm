; disk.asm
;
; 旼컴컴컴컴컴컴컴컴컴컴컴커
; � Exodus Disk Primatives �
; 읕컴컴컴컴컴컴컴컴컴컴컴켸
;
; Exodus native primative disk driver
; This routines handles all logical disk functions as well as internal drive scheduling
;


TITLE Disk

    .MODEL tiny

    .STACK 0h

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
            mov     esi,offset required_primatives          ; This primative requires these functions
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
        mov     ds,cs:data_segment
        mov     ds:bootup,0
        call    initialize_driver
      ; Right now, carry? is SET or CLEAR indicating status of driver
        retf
    main    ENDP




    DISK_open_file      PROC
        retf
    DISK_open_file      ENDP




    DISK_read_file      PROC
        retf
    DISK_read_file      ENDP




    DISK_seek_file      PROC
        retf
    DISK_seek_file      ENDP




    DISK_insert_file        PROC
        retf
    DISK_insert_file        ENDP




    DISK_write_file     PROC
        retf
    DISK_write_file     ENDP




    DISK_close_file     PROC
        retf
    DISK_close_file     ENDP




    DISK_delete_file        PROC
        retf
    DISK_delete_file        ENDP




;    iDISK_add_drive     PROC
;    ; This routine is used to add a physical drive to the drive structure table
;    ; Upon entry:   The stack is populated with the structure below
;    ;
;    ; Upon exit:    al - internal disk number identifier
;    ;
;        push    ebp
;        mov     ebp,esp
;      ; stack frame
;      ; -----------
;      ; [ebp+31] - BYTE,  FLOPPY:  Drive type
;      ;                   OTHERS:  --Nuserved
;      ; [ebp+30] - BYTE,  device specs
;      ; [ebp+29] - BYTE,  type of device
;      ; [ebp+28] - BYTE,  type of controller
;      ; [ebp+24] - DWORD, number_of_heads
;      ; [ebp+20] - DWORD, bytes_per_sector
;      ; [ebp+16] - DWORD, sectors_per_track
;      ; [ebp+12] - DWORD, number_of_tracks
;      ; [ebp+08] - DWORD, capacity in bytes
;      ; [ebp+04] - eip
;      ; [ebp+00] - ebp
;      ; [ebp-02] - es
;        push    es
;
;        mov     ax,_sDISK_DRIVES
;        mov     es,ax
;        xor     edi,edi
;        xor     cx,cx
;        .WHILE (byte ptr es:[edi] != 0ffh && edi < 1024)
;            add     edi,_DISK_STRUCTURE_SIZE
;            inc     cx
;        .ENDW
;        .IF (edi < 1024)
;          ; Type of controller
;            mov     al,byte ptr ss:[ebp+28]
;            mov     byte ptr es:[edi+_DISK_CONTROLLER_OFFSET],al
;            .IF (al == _DISK_CONTROLLER_FLOPPY)
;              ; Drive type (drive is physically only a 360k, or a 1.2MB, or a 720k, or a 1.44MB or even a 2.88MB drive)
;                mov     al,byte ptr ss:[ebp+31]
;                mov     byte ptr es:[edi+_DISK_FLOPPY_DRIVE_TYPE_OFFSET],al
;            .ENDIF
;          ; Type of device
;            mov     al,byte ptr ss:[ebp+29]
;            mov     byte ptr es:[edi+_DISK_DEVICE_OFFSET],al
;          ; Capacity
;            mov     eax,dword ptr ss:[ebp+8]
;            mov     dword ptr es:[edi+_DISK_CAPACITY_OFFSET],eax
;          ; Number of heads
;            mov     eax,dword ptr ss:[ebp+24]
;            mov     dword ptr es:[edi+_DISK_NUM_HEADS_OFFSET],eax
;          ; Number of tracks
;            mov     eax,dword ptr ss:[ebp+12]
;            mov     dword ptr es:[edi+_DISK_NUM_TRACKS_OFFSET],eax
;          ; Number of sectors
;            mov     eax,dword ptr ss:[ebp+16]
;            mov     dword ptr es:[edi+_DISK_NUM_SECTORS_OFFSET],eax
;          ; Device specs
;            mov     al,byte ptr ss:[ebp+30]
;            mov     byte ptr es:[edi+_DISK_DEVICE_SPECS_OFFSET],al
;          ; Bytes per sector
;            mov     eax,dword ptr ss:[ebp+20]
;            mov     dword ptr es:[edi+_DISK_BYTES_PER_SECTOR_OFFSET],eax
;          ; Mark the next record as the last one
;            add     di,_DISK_STRUCTURE_SIZE
;            mov     byte ptr es:[edi+_DISK_CONTROLLER_OFFSET],_STOPPER
;          ; Get the disk number for this entry (returned in al)
;            mov     al,cl
;            clc
;        .ELSE
;            stc
;            mov     al,0ffh                                             ; Disk #
;        .ENDIF
;
;        pop     es
;        pop     ebp
;        ret     24
;    iDISK_add_drive     ENDP
;
;
;
;
;    iDISK_add_partition     PROC
;    ; This routine is used to add a physical drive to the drive structure table
;        enter   0,0
;      ; stack frame
;      ; -----------
;      ; [ebp+46] - WORD,  Nuserved
;      ; [ebp+45] - BYTE,  file system
;      ; [ebp+44] - BYTE,  disk number
;      ; [ebp+40] - DWORD, starting head
;      ; [ebp+36] - DWORD, starting track
;      ; [ebp+32] - DWORD, starting sector
;      ; [ebp+28] - DWORD, ending head
;      ; [ebp+24] - DWORD, ending track
;      ; [ebp+20] - DWORD, ending sector
;      ; [ebp+16] - DWORD, GDT selector
;      ; [ebp+12] - DWORD, access rights
;      ; [ebp+08] - DWORD, drive letter
;      ; [ebp+04] - eip
;      ; [ebp+00] - ebp
;      ; [ebp-04] - es
;        push    es
;
;        mov     ax,_sDISK_PARTITIONS
;        mov     es,ax
;        xor     edi,edi
;        .WHILE (byte ptr es:[edi] != _STOPPER && edi < 4096)
;            add     edi,_PARTITION_STRUCTURE_SIZE
;        .ENDW
;        .IF (edi < 4096)
;          ; Disk number
;            mov     ax,word ptr ss:[ebp+44]
;            mov     byte ptr es:[edi+_PARTITION_DISK_NUMBER_OFFSET],al
;          ; File system type
;            mov     byte ptr es:[edi+_PARTITION_FILE_SYSTEM_TYPE_OFFSET],ah
;          ; Starting head
;            mov     eax,dword ptr ss:[ebp+40]
;            mov     dword ptr es:[edi+_PARTITION_STARTING_HEAD_OFFSET],eax
;          ; Starting track
;            mov     eax,dword ptr ss:[ebp+36]
;            mov     dword ptr es:[edi+_PARTITION_STARTING_TRACK_OFFSET],eax
;          ; Starting sector
;            mov     eax,dword ptr ss:[ebp+32]
;            mov     dword ptr es:[edi+_PARTITION_STARTING_SECTOR_OFFSET],eax
;          ; Ending head
;            mov     eax,dword ptr ss:[ebp+28]
;            mov     dword ptr es:[edi+_PARTITION_ENDING_HEAD_OFFSET],eax
;          ; Ending track
;            mov     eax,dword ptr ss:[ebp+24]
;            mov     dword ptr es:[edi+_PARTITION_ENDING_TRACK_OFFSET],eax
;          ; Ending sector
;            mov     eax,dword ptr ss:[ebp+20]
;            mov     dword ptr es:[edi+_PARTITION_ENDING_SECTOR_OFFSET],eax
;          ; starting GDT
;            mov     eax,dword ptr ss:[ebp+16]
;            mov     word ptr es:[edi+_PARTITION_STARTING_GDT_OFFSET],ax
;          ; Access rights
;            mov     eax,dword ptr ss:[ebp+12]
;            mov     word ptr es:[edi+_PARTITION_ACCESS_WORD_OFFSET],ax
;          ; Drive letter
;            mov     eax,dword ptr ss:[ebp+08]
;            mov     byte ptr es:[edi+_PARTITION_DRIVE_LETTER_OFFSET],al
;          ; Mark the next record as the last one
;            add     edi,_PARTITION_STRUCTURE_SIZE
;            mov     byte ptr es:[edi+_PARTITION_DISK_NUMBER_OFFSET],_STOPPER
;            clc
;        .ELSE
;            stc
;        .ENDIF
;
;        pop     es
;        leave
;        ret     40
;    iDISK_add_partition     ENDP
;
;
;
;
;    iDISK_update_media      PROC
;    ; This routine is used to update the media type (it updates the partition information to the type of media currently in the drive)
;    ; * Note:  This routine is a primative, so not too much checking goes on.  It is possible to corrupt the information for this
;    ;          device.  Care should be taken when issuing this command.
;    ;
;    ; Upon entry:   al - drive letter to update
;    ;               cl - (floppy only) gap length
;    ;               dh - sectors
;    ;               dl - tracks
;    ;              ebx - total capacity in bytes
;    ;
;    ;  Upon exit:   carry? - CLEAR if ok, SET if error
;    ;                  eax - error code if error
;    ;               CLEAR:
;    ;                   The sectors, tracks, capacity, (gap length) are updated and "Accessed yet?" bit is updated in the Access byte
;    ;
;        push    ds      ; [esp+24]
;        push    esi     ; [esp+20]
;        push    es      ; [esp+16]
;        push    edi     ; [esp+12]
;        push    eax     ; [esp+08]
;        push    ecx     ; [esp+04]
;        push    ebx     ; [esp+00]
;
;        mov     bl,al
;        call    invDISK_find_drive_by_letter
;        .IF (!carry?)
;          ; Right now, ds:[esi] - far pointer to disk drive structure
;          ;            es:[edi] - far pointer to disk partition structure
;            mov     al,byte ptr ds:[esi+_DISK_DEVICE_SPECS_OFFSET]
;            and     al,_DISK_DEVICE_MEDIA_REMOVABLE
;            .IF (al != 0)
;              ; This device is removable, so it's ok that they define it
;                mov     ebx,dword ptr ss:[esp]
;                xor     ecx,ecx
;                mov     cl,dh
;                and     edx,0ffh
;              ; Check to see if these ending values are beyond the physical capabilities of the drive
;                .IF (edx < dword ptr es:[edi+_PARTITION_STARTING_TRACK_OFFSET])
;                  ; The ending track is less than the starting track
;                  @@:
;                    stc
;                    mov     eax,_DISK_INVALID_PARAMETERS
;                .ELSEIF (ecx < dword ptr es:[edi+_PARTITION_STARTING_SECTOR_OFFSET])
;                  ; The ending sector is less than the starting sector
;                    jmp     @B
;                .ELSEIF (edx > dword ptr ds:[esi+_DISK_NUM_TRACKS_OFFSET])
;                  ; They've specified a track greater than the number physically available on the device
;                    jmp     @B
;                .ELSEIF (ecx > dword ptr ds:[esi+_DISK_NUM_SECTORS_OFFSET])
;                  ; They've specified a sector greater than the number physically available on the device
;                    jmp     @B
;                .ELSE
;                  ; It's ok
;                    mov     dword ptr es:[edi+_PARTITION_ENDING_TRACK_OFFSET],edx
;                    mov     dword ptr es:[edi+_PARTITION_ENDING_SECTOR_OFFSET],ecx
;                  ; Turn off "accessed yet?" and "read/write pending" flags
;                    and     word ptr es:[edi+_PARTITION_ACCESS_WORD_OFFSET],not 1000000010000000b
;                    mov     dword ptr es:[edi+_PARTITION_PARTITION_CAPACITY],ebx
;                    mov     dword ptr es:[edi+_PARTITION_PARTITION_CAPACITY+4],0
;                    .IF (byte ptr ds:[esi+_DISK_CONTROLLER_OFFSET] == _DISK_CONTROLLER_FLOPPY)
;                      ; It's a floppy disk, update the gap length
;                        mov     ecx,dword ptr ss:[esp+04]
;                        mov     byte ptr ds:[esi+_DISK_FLOPPY_GAP_LENGTH_OFFSET],cl
;                    .ENDIF
;                  ; Everything is updated
;                    clc
;                .ENDIF
;            .ELSE
;              ; This device is not removable.  They're trying to update something that's invalid
;                stc
;                mov     eax,_DISK_INVALID_REQUEST
;            .ENDIF
;        .ELSE
;            stc
;            mov     eax,_DISK_INVALID_DRIVE
;        .ENDIF
;
;        pop     ebx
;        pop     ecx
;        pop     eax
;        pop     edi
;        pop     es
;        pop     esi
;        pop     ds
;        retf
;    iDISK_update_media      ENDP




    DISK_requestor     PROC
    ; This procedure is used to answer general requests
    ; Upon entry:   eax - request code
    ; Upon exit:    carry? - CLEAR if ok, SET if error
    ;
;        pushad
;        push    ds
;        push    es
;        push    fs
;        push    gs
;        enter   0,0
;
;        .IF (eax == _RQ_iDISK_FLOPPY_DRIVE_TYPE)
;          ; They want to know the floppy drive type
;          ; Upon entry:  bl - drive letter they're querying
;          ;  Upon exit: eax - physical drive type   * Note, refer to _DISK_CONTROLLER_* equate variables
;            call    invDISK_find_drive_by_letter
;            .IF (!carry?)
;                xor     eax,eax
;                mov     al,byte ptr ds:[esi+_DISK_FLOPPY_DRIVE_TYPE_OFFSET]
;                clc
;            .ELSE
;                stc
;                mov     eax,_RQ_iDISK_DRIVE_NOT_FOUND
;            .ENDIF
;        .ELSE
;            mov     eax,_RQ_UNKNOWN_REQUEST
;          iDISK_requestor_error:
;            stc
;        .ENDIF
;
;      iDISK_requestor_done:
;        mov     dword ptr ss:[esp+48],eax                               ; Save eax's new value on the stack
;        leave
;        pop     gs
;        pop     fs
;        pop     es
;        pop     ds
;        popad
        retf
    DISK_requestor     ENDP




    invDISK_find_drive_by_letter    PROC
    ; This routine is used to find a drive partition by its letter
    ; Upon entry:   bl - drive letter we're searching for
    ;  Upon exit:   ds:[esi] - far pointer to drive information
    ;               es:[edi] - far pointer to partition information
;        push    ecx
;
;        mov     cx,_sDISK_DRIVES                                        ; ds:[esi] - far pointer to disk drives
;        mov     ds,cx
;
;        mov     cx,_sDISK_partitions                                    ; es:[edi] - far pointer to partitions
;        mov     es,cx
;        xor     edi,edi
;
;        .WHILE (byte ptr es:[edi+_PARTITION_DISK_NUMBER_OFFSET] != _STOPPER && edi < 4096)
;            .IF (byte ptr es:[edi+_PARTITION_DRIVE_LETTER_OFFSET] == bl)
;              ; This is the drive letter, now we point ds:[esi] to the disk information
;                xor     ecx,ecx
;                mov     cl,byte ptr es:[edi+_PARTITION_DISK_NUMBER_OFFSET]
;                shl     ecx,5                                           ; Multiply by 32
;                mov     esi,ecx
;              ; Right now, ds:esi - pointer to the drive information
;              ;            es:edi - pointer to the partition information
;                clc
;                jmp     @F
;            .ENDIF
;            add     edi,_PARTITION_STRUCTURE_SIZE
;        .ENDW
;      ; If we're here, it wasn't found
;        stc
;
;      @@:
;        pop     ecx
        ret
    invDISK_find_drive_by_letter    ENDP




    initialize_driver   PROC
    ; This routine is used to initialize the driver
    ; But, there is no initialization in this system
        mov     esi,offset DISK_boot_logo
        call    fword ptr cs:_VID_draw_logo
        clc
        ret
    initialize_driver   ENDP




; DATA
    driver_name                             db  "Disk Driver",255,"(source:disk.dbg)",0
    version                                 db  "10.10.2010 BETA",0
    copyright                               db  "(c) Copyright Beatleworks, Inc.",0
    author                                  db  "Rick C. Hodgin",0
    debi_text                               db  "Disk Primative",0
    beatleworks_text                        db  "(c) Beatleworks, Inc.",0
    bootup                                  db  1                   ; Changed to 0 after bootup is complete
    data_segment                            dw  0

    _EXODUS_requestor                       dw  0
  primative_call_gates:
    _VID_draw_logo                          dw  0
    _VID_display_string_nr_vga              dw  _sEXODUS_REQUESTOR
                                            dw  0f000h
                                            dw  0f000h

    required_primatives                     db  13, "VID_draw_logo"
                                            db  25, "VID_display_string_nr_vga"
                                            db  0ffh


    ; This logo consists of a three-wide image (the +2 portion (the 2 stands for "an extra 2 18x16 images wide"))
    ; It wants a box drawn around it (the +80h portion)
    ; And the color we want to use is 8 (dark grey, the "+(8 SHL 3) portion)
    ; * Refer to
    DISK_boot_logo                          db  0c9h     ; * Refer to VGA\INF\VGA.INF for information on this byte's format
                                            db  0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh
                                            db  0fh,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,0fh
                                            db  0fh,07h,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,07h,0fh
                                            db  0fh,07h,0fh,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,0fh,07h,0fh
                                            db  0fh,07h,0fh,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,0fh,07h,0fh
                                            db  0fh,07h,0fh,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,0fh,07h,0fh
                                            db  0fh,07h,0fh,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,0fh,07h,0fh
                                            db  0fh,07h,0fh,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,0fh,07h,0fh
                                            db  0fh,07h,0fh,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,0fh,07h,0fh
                                            db  0fh,07h,0fh,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,0fh,07h,0fh
                                            db  0fh,07h,0fh,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,0ah,0ah,07h,0fh,07h,0fh
                                            db  0fh,07h,0fh,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,0ah,0ah,07h,0fh,07h,0fh
                                            db  0fh,07h,0fh,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,0fh,07h,0fh
                                            db  0fh,07h,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,07h,0fh
                                            db  0fh,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,07h,0fh
                                            db  0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh,0fh


 end_of_required_data:
    driver_primatives                       db  14, "DISK_open_file"
                                            dd  offset DISK_open_file
                                            dw  0

                                            db  14, "DISK_read_file"
                                            dd  offset DISK_read_file
                                            dw  0

                                            db  14, "DISK_seek_file"
                                            dd  offset DISK_seek_file
                                            dw  0

                                            db  16, "DISK_insert_file"
                                            dd  offset DISK_insert_file
                                            dw  0

                                            db  15, "DISK_write_file"
                                            dd  offset DISK_write_file
                                            dw  0

                                            db  15, "DISK_close_file"
                                            dd  offset DISK_close_file
                                            dw  0

                                            db  16, "DISK_delete_file"
                                            dd  offset DISK_delete_file
                                            dw  0

                                            db  14, "DISK_requestor"
                                            dd  offset DISK_requestor
                                            dw  0

                                            dw  0ffffh              ; Teriminator


_TEXT32 ENDS

END
