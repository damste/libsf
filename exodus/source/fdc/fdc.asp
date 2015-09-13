; fdc.asp
;
; This routines handles all low-level FDC routines
;
;
;   iFDC_initialize_drive()                 ; Initializes the drive (turns motor off, positions head at track 0)
;   iFDC_determine_media()                  ; Determines the file system on the disk in the drive (if possible to do so)
;   iFDC_clear_fdc_output()                 ; Clears the FDC of any bytes to send, if none are there it tries sending a command
;                                           ;   to see if it was in the middle of a command
;   iFDC_clear_fdc_input()                  ; Clears the FDC of any bytes to receive (used if a task ended prematurely)
;   iFDC_sense_interrupt()                  ; Senses the interrupt status
;
;   iFDC_send_byte()                        ; Sends one byte to the FDC controller
;   iFDC_read_byte()                        ; Reads one byte back from the FDC controller
;
;   iFDC_motor_on()                         ; Turns the FDC motor on for a particular drive
;   iFDC_motor_off()                        ; Turns the FDC motor off for a particular drive
;
;   iFDC_read_sector()                      ; Reads one sector of data
;   iFDC_read_track()                       ; Reads one entire track of data
;   iFDC_write_sector()                     ; Writes one sector of data
;   iFDC_write_track()                      ; Writes one entire track of data
;
;   iFDC_format_track()                     ; Formats one entire track
;
;   iFDC_seek_track()                       ; Seeks to a particular track
;   iFDC_seek_relative()                    ; Seeks to a particular track relative to the current track
;





iFDC_initialize_drive      PROC
; This routine is used to initialize the floppy drive (turns off motor, seeks to track 0, etc.)
;
; Upon entry:   al - drive letter, "A" or "B"
;
; Upon exit:    carry? - CLEAR if ok, SET if error
;               CF? SET:
;                   <nothing, drive could not be initialized>
;               CF? CLEAR:
;                   al - tracks
;                   ah - sectors per track
;                  ebx - total formatted capacity (in bytes)
;                   cl - gap length
;
    pushad      ; [ebp+32] DWORD, eax
                ; [ebp+28] DWORD, ecx
                ; [ebp+24] DWORD, edx
                ; [ebp+20] DWORD, ebx
                ; [ebp+16] DWORD, esp
                ; [ebp+12] DWORD, ebp
                ; [ebp+08] DWORD, esi
                ; [ebp+04] DWORD, edi
    enter   12,0
  ; [ebp+00] DWORD, ebp
  ; [ebp-02] WORD,  Nuserved
  ; [ebp-03] BYTE,  Nuserved
  ; [ebp-04] BYTE,  drive letter
  ; [ebp-08] DWORD, count for seek retries
  ; [ebp-12] DWORD, count for total # of retries
    mov     byte ptr ss:[ebp-4],al
    mov     dword ptr ss:[ebp-12],-3                                ; Initialize our maximum total-retry count (3 tries)

;; Clear off any bytes that might be in the drive
  iFDC_initialize_drive_top:
    mov     dword ptr ss:[ebp-8],-5                                 ; Maximum of 5 tries on re-seek
    call    fword ptr cs:_iFDC_clear_fdc_output

;; Turn the motor on
    mov     al,byte ptr ss:[ebp-4]
    call    fword ptr cs:_iFDC_motor_on
    push    dword ptr 182/2                                         ; Wait for 1/2 second
    call    fword ptr cs:_xTIMER_wait_x_ticks

;; Seek the head back to track 0
  iFDC_initialize_drive_seek_again:
    push    dword ptr 0                                             ; Result
    xor     eax,eax                                                 ; al-drive, ah-head, eax[byte2]-cylinder
    mov     al,byte ptr ss:[ebp-4]
    push    eax
    call    fword ptr cs:_iFDC_seek_track
    pop     eax

;; Sense interrupt (to insure it was moved)
    call    fword ptr cs:_iFDC_sense_interrupt
    .IF (al != 0)
      ; Error seeking, we're not at cylinder 0.  Try again
        inc     dword ptr ss:[ebp-8]
        jno     iFDC_initialize_drive_seek_again

      ; If we're here then we've already tried our maximum number of re-seek times
        inc     dword ptr ss:[ebp-12]
        jno     iFDC_initialize_drive_top

      ; If we're here then we've totally failed, it's useless, no point really ... we'll just leave the drive to itself
        stc
        jmp     iFDC_initialize_drive_quit
    .ENDIF
  ; If we're here then the SEEK was completed correctly, and we're now ... back home again ... in Indiana!

;; Determine what type of media exists on this disk
    mov     al,byte ptr ss:[ebp-4]
    call    fword ptr cs:_iFDC_determine_media
    mov     dword ptr ss:[ebp+32],eax                               ; Update eax on the stack (for popad below)
    mov     dword ptr ss:[ebp+20],ebx                               ; and ebx
    mov     dword ptr ss:[ebp+28],ecx                               ; and ecx

;; Turn the motor off
    mov     al,byte ptr ss:[ebp-4]
    call    fword ptr cs:_iFDC_motor_off
    clc

  iFDC_initialize_drive_quit:
    leave
    popad
    retf
iFDC_initialize_drive      ENDP




iFDC_determine_media       PROC
; This routine is used to determine the type of media on a disk.
; This looks for things like 360k vrs 1.2MB, 720k vrs 1.44MB, it does not identify the file format.
;
; Upon entry:   al - drive letter, "A" or "B"
;               * Note:  The heads must already be retracted to cylinder 0
;
; Upon exit:    carry? - CLEAR if ok, SET if error
;               CF? SET:
;                  eax - FDC error number
;                  ebx - additional error information
;               CF? CLEAR:
;                   al - tracks
;                   ah - sectors per track
;                  ebx - total formatted capacity (in bytes)
;                   cl - gap length
;
    push    edx     ; [esp+28]
    push    ebp     ; [esp+24]
    push    esi     ; [esp+20]
    push    edi     ; [esp+16]
    push    ds      ; [esp+12]
    push    es      ; [esp+08]
    push    fs      ; [esp+04]
    push    gs      ; [esp+00]

    .IF (al == 'A' || al == 'B')
      ; It's a valid drive letter
        mov     cl,al                                               ; cl is used below if we find the disk
        mov     bl,al
        mov     eax,_RQ_iDISK_FLOPPY_DRIVE_TYPE
        call    fword ptr cs:_iDISK_requestor
        .IF (!carry?)
          ; It was found
            .IF (al == 0)
              ; 360k drive
              iFDC_determine_media_360:
                mov     bl,9
                mov     bh,2                                        ; 512-byte sector size
                mov     ah,0                                        ; Not double-density
                call    invFDC_read_sector
                .IF (carry?)
                  ; Sector was not found
                  ; Unknown drive type
                    mov     eax,_FDC_INVALID_MEDIA
                    stc
                .ELSE
                  ; It is a 360k diskette
                    mov     ebx,9 * 40 * 512 * 2                    ; total capacity
                    mov     ah,9                                    ; sectors per track
                    mov     al,40                                   ; tracks per side
                    clc
                .ENDIF
            .ELSEIF (al == 1)
              ; 1.2MB drive
              iFDC_determine_media_1_2:
                mov     bl,15
                mov     bh,2                                        ; 512-byte sector size
                mov     ah,1
                call    invFDC_read_sector
                .IF (carry?)
                  ; Sector was not found
                  ; Try to see if it's a 360k diskette
                    jmp     iFDC_determine_media_360
                .ELSE
                  ; It is a 1.2MB diskette
                    mov     ebx,15 * 80 * 512 * 2                   ; total capacity
                    mov     ah,15                                   ; sectors per track
                    mov     al,80                                   ; tracks per side
                    mov     cl,1bh                                  ; All floppy disks use 1bh for gap length
                    clc
                .ENDIF
            .ELSEIF (al == 2)
              ; 720k drive
              iFDC_determine_media_720:
                mov     bl,9
                mov     bh,2                                        ; 512-byte sector size
                mov     ah,0
                call    invFDC_read_sector
                .IF (carry?)
                  ; Sector was not found
                  ; Unknown drive type
                    mov     eax,_FDC_INVALID_MEDIA
                    stc
                .ELSE
                  ; It is a 720k diskette
                    mov     ebx,9 * 80 * 512 * 2                    ; total capacity
                    mov     ah,9                                    ; sectors per track
                    mov     al,80                                   ; tracks per side
                    mov     cl,1bh                                  ; All floppy disks use 1bh for gap length
                    clc
                .ENDIF
            .ELSEIF (al == 3)
              ; 1.44MB drive
              iFDC_determine_media_1_44:
                mov     bl,18
                mov     bh,2                                        ; 512-byte sector size
                mov     ah,1
                call    invFDC_read_sector
                .IF (carry?)
                  ; Sector was not found
                  ; Try to see if it's a 720k diskette
                    jmp     iFDC_determine_media_720
                .ELSE
                  ; It is a 1.44MB diskette
                    mov     ebx,18 * 80 * 512 * 2                   ; total capacity
                    mov     ah,18                                   ; sectors per track
                    mov     al,80                                   ; tracks per side
                    mov     cl,1bh                                  ; All floppy disks use 1bh for gap length
                    clc
                .ENDIF
            .ELSEIF (al == 4)
              ; 2.88MB drive
                mov     bl,36
                mov     bh,2                                        ; 512-byte sector size
                mov     ah,1
                call    invFDC_read_sector
                .IF (carry?)
                  ; See if it's a 1.44MB diskette
                    jmp     iFDC_determine_media_1_44
                .ELSE
                  ; It is a 2.88MB diskette
                    mov     ebx,36 * 80 * 512 * 2                   ; total capacity
                    mov     ah,36                                   ; sectors per track
                    mov     al,80                                   ; tracks per side
                    mov     cl,1bh                                  ; All floppy disks use 1bh for gap length
                    clc
                .ENDIF
            .ELSE
              ; Unsupported drive type
                mov     eax,_FDC_UNKNOWN_DRIVE_TYPE
                stc
            .ENDIF
        .ELSE
            mov     ebx,eax                                         ; Store returned error code from iDISK_requestor in ebx
            mov     eax,_FDC_INVALID_DRIVE
        .ENDIF
    .ELSE
        mov     eax,_FDC_INVALID_PARAMETERS
        stc
    .ENDIF

  ; Note, results are returned in eax, ebx and ecx

    pop     gs
    pop     fs
    pop     es
    pop     ds
    pop     edi
    pop     esi
    pop     ebp
    pop     edx
    retf
iFDC_determine_media       ENDP




invFDC_read_sector      PROC
; This routine is used to try to read data from the last sector on the disk (for a particular format)
; * Note:  This routine does not actually transfer any data from the disk to memory (the DMA transfer is never setup)
;          but it does read the sector and return the correct status.  The only difference is it will show a buffer under/overrun
;
; Upon entry:   bl - Sector to try to read (should be the last sector available on a particular format)
;               bh - Sector size code
;               ah - 0 or 1, use double-density mode?
;               cl - drive letter, "A" or "B"
;               The read/write heads must already be at track 0
;
; Upon exit:    carry? - CLEAR if OK, SET if ERROR
;
    enter   20,0
  ; [ebp-04] - DWORD, count used for retries
  ; [ebp-08] - DWORD, eax
  ; [ebp-12] - DWORD, ebx
  ; [ebp-20] - 8 BYTES, temporary space used for storing result from READ TRACK command
  ;
    push    es
    push    edi
    push    ecx

    mov     dword ptr ss:[ebp-04],-3
    mov     dword ptr ss:[ebp-08],eax
    mov     dword ptr ss:[ebp-12],ebx

  invFDC_read_sector_top:
;; Build the command based on their command
    mov     eax,dword ptr ss:[ebp-08]
    mov     ebx,dword ptr ss:[ebp-12]
    shl     ah,6                                                    ; Shift into bit position 6
    mov     al,_FDC_CMD_READ_TRACK
    or      al,ah
  ; Right now, al - the command byte (per what the user setup)
;; Send the read-track command to the FDC
    call    fword ptr cs:_iFDC_send_byte
    mov     al,cl                                                   ; Drive letter
    sub     al,"A"
    call    fword ptr cs:_iFDC_send_byte
    mov     al,0                                                    ; Cylinder
    call    fword ptr cs:_iFDC_send_byte
    mov     al,0                                                    ; Head
    call    fword ptr cs:_iFDC_send_byte
    mov     al,bl                                                   ; Sector
    call    fword ptr cs:_iFDC_send_byte
    mov     al,bh                                                   ; Sector size code
    call    fword ptr cs:_iFDC_send_byte
    mov     al,bl                                                   ; EOT number (the same as the sector they're trying to read)
    call    fword ptr cs:_iFDC_send_byte
    mov     al,01bh                                                 ; Gap length
    call    fword ptr cs:_iFDC_send_byte
    mov     al,0ffh                                                 ; Data length (force 0ffh)
    call    fword ptr cs:_iTASK_irq6_prep_wait
    call    fword ptr cs:_iFDC_send_byte
    call    fword ptr cs:_iTASK_irq6_wait_for_signal
  ; Right now it should've read the data

;; Read the result bytes
    push    ss
    pop     es
    mov     edi,ebp
    sub     edi,20                                                  ; This brings us down on the stack to [ebp-20]
  ; Right now, es:[edi] - far pointer to location to store 7 result bytes
    mov     ecx,7
    call    invFDC_read_result_bytes
    mov     al,byte ptr es:[edi+5]                                  ; Get the first byte (this is new sector number)
    .IF (al >= byte ptr ss:[ebp-12])
      ; The sector was found and we're sitting passed it.
      ; This one is it
        clc
    .ELSE
      ; Some kind of abnormal termination
        inc     dword ptr ss:[ebp-04]
        jno     invFDC_read_sector_top
      ; If we're here, then we've retried 3 times already, no success
        stc
    .ENDIF

    pop     ecx
    pop     edi
    pop     es
    leave
    ret
invFDC_read_sector      ENDP




invFDC_read_result_bytes    PROC
; This routine is used to read the result bytes from the previous operation
;
; Upon entry:        ecx - Number of result bytes to read
;               es:[edi] - where to store result bytes
;
    push    edi
    push    ecx

   @@:
    call    fword ptr cs:_iFDC_read_byte
    mov     byte ptr es:[edi],al
    inc     edi
    loop    @B

    pop     ecx
    pop     edi
    ret
invFDC_read_result_bytes    ENDP




iFDC_clear_fdc_output   PROC
; This routine is used to clear out the FDC output buffer.  It reads any and all bytes to be output, discarding them.
; Upon entry:   al - drive to clear
;
; Upon exit:    Nothing, the FDC is not waiting to send any commands
;
    pushfd
    push    eax
    push    edx

;; See if the FDC has data to send, this is true when BIT7 is 1 and BIT6 is 1
  @@:
    mov     edx,_FDC_PORT_MSR
    in      al,dx
    and     al,11000000b                                            ; Check RQM, DIO
    .IF (al == 11000000b)
      ; It has something to send, we'll read it and clear it out
        mov     edx,_FDC_PORT_DR
        in      al,dx
        jmp     @B
    .ENDIF
  ; Right now, the FDC is not waiting for any data

    pop     edx
    pop     eax
    popfd
    retf
iFDC_clear_fdc_output   ENDP




iFDC_clear_fdc_input    PROC
; This routine is used to clear out any corresponding FDC commands that might be incomplete.  It checks the CB bit of MSR.
; If CB is 1 (meaning a command is busy) then it sends 0xff commands until it goes low and the MSR's RQM and DIO bits read 10b.
; Upon entry:   al - drive to clear
;
; Upon exit:    Nothing, the FDC is not waiting to send any commands

    pushfd
    push    eax
    push    edx

;; See if the FDC has data to send, this is true when BIT7 is 1 and BIT6 is 1
  @@:
    mov     edx,_FDC_PORT_MSR
    in      al,dx
    and     al,10000b                                               ; Check CB
    .IF (al == 10000b)
      ; The CB bit is high (it is waiting for a command to complete)
        mov     edx,_FDC_PORT_DR
        mov     al,0ffh
        out     dx,al
        jmp     @B
    .ENDIF
  ; Right now, the FDC is not waiting for any data, we're good to go

  @@:
    pop     edx
    pop     eax
    popfd
    retf
iFDC_clear_fdc_input    ENDP




iFDC_send_byte     PROC
; This routine is used to send a byte to the FDC
;
;  Upon entry:  al - byte to send
;
;  Upon exit:   carry? - SET if error, CLEAR if ok
;
    push    edx
    sub     esp,4
    mov     dword ptr ss:[esp],-100000                              ; Try 100,000 times
    mov     ah,al

  @@:
    mov     edx,_FDC_PORT_MSR
    in      al,dx
    and     al,11000000b
    .IF (al != 10000000b)
        inc     dword ptr ss:[esp]
        jno     @B
      ; If we're here then we've retried 100,000 times with no success
        stc
        jmp     @F
    .ENDIF
  ; It's ready to receive data
    mov     edx,_FDC_PORT_DR
    mov     al,ah
    out     dx,al
    clc

  @@:
    add     esp,4
    pop     edx
    retf
iFDC_send_byte      ENDP




iFDC_read_byte      PROC
; This routine is used to read a byte from the FDC
;
;  Upon entry:  Nothing
;
;  Upon exit:   carry? - SET if error, CLEAR if ok
;                   al - byte read, everything else is preserved
;
    push    edx
    sub     esp,4
    mov     dword ptr ss:[esp],-5

  @@:
    mov     edx,_FDC_PORT_MSR
    in      al,dx
    and     al,11000000b
    .IF (al != 11000000b)
        inc     dword ptr ss:[esp]
        jno     @B
      ; If we're here then we've retried 5 times with no success
        stc
        jmp     @F
    .ENDIF
  ; It's ready to send data
    mov     edx,_FDC_PORT_DR
    in      al,dx
    clc

  @@:
    add     esp,4
    pop     edx
    retf
iFDC_read_byte      ENDP




iFDC_motor_on       PROC
; This routine turns the floppy motor on
;
;  Upon entry:  al - drive letter, "A" or "B"
;
;  Upon exit:   Nothing, everything is preserved
;               * Note, after this function is called at least 1/2 second should pass before attempting to read or write data
;
    push    edx
    push    eax

  ; Turn on floppy motor
    .IF (al == "A")
      ; Drive A:
        mov     al,011100b
    .ELSE
      ; Drive B:
        mov     al,101101b
    .ENDIF
    mov     edx,_FDC_PORT_DOR
    out     dx,al

    pop     eax
    pop     edx
    retf
iFDC_motor_on       ENDP




iFDC_motor_off      PROC
; This routine turns the floppy motor off
;
; Upon entry:   al - drive letter, "A" or "B"
;
; Upon exit:    Nothing
;
    pushf
    push    edx
    push    eax

  ; Turn off floppy motor
    .IF (al == "A")
      ; Drive A:
        mov     al,001100b
    .ELSE
      ; Drive B:
        mov     al,001101b
    .ENDIF
    mov     edx,_FDC_PORT_DOR
    out     dx,al

    pop     eax
    pop     edx
    popf
    retf
iFDC_motor_off      ENDP




iFDC_read_sector    PROC
; This procedure is used to read one sector of data from the floppy disk
; Upon entry:   Parameters are passed on the stack, see below
; Upon exit:    carry? - SET or CLEAR indicating error status
;               return value - error code or 512, depending on error status
;
int 3
    enter   12,0
  ; [ebp+24] - DWORD, (return) error code or # of bytes read (constant of 512 if all goes well)
  ; [ebp+22] - WORD,  nuserved
  ; [ebp+21] - BYTE,  nuserved
  ; [ebp+20] - BYTE,  (param)  use double-density mode (0-no or 1-yes)
  ; [ebp+16] - DWORD, (param)  physical address to read disk data to
  ; [ebp+15] - BYTE,  (param)  sector
  ; [ebp+14] - BYTE,  (param)  head
  ; [ebp+13] - BYTE,  (param)  cylinder number
  ; [ebp+12] - BYTE,  (param)  drive letter
  ; [ebp+8]  - DWORD, cs
  ; [ebp+4]  - DWORD, eip
  ; [ebp+0]  - DWORD, ebp
  ; [ebp-04] - DWORD, count used for retries
  ; [ebp-12] - 8 BYTES, temporary space used for storing result from READ TRACK command
  ;
    push    ds
    push    es
    pushad

;; See if it's a valid drive letter
    mov     bl,byte ptr ss:[ebp+12]
    call    invDISK_find_drive_by_letter
    .IF (carry? || byte ptr ds:[esi+_DISK_CONTROLLER_OFFSET] != _DISK_CONTROLLER_FLOPPY)
        mov     dword ptr ss:[ebp+24],_FDC_INVALID_DRIVE
        stc
    .ELSE
      ; It's a valid floppy drive
        mov     eax,dword ptr ds:[esi+_DISK_NUM_HEADS_OFFSET]       ; base-0
        mov     ebx,dword ptr ds:[esi+_DISK_NUM_TRACKS_OFFSET]      ; base-0
        mov     ecx,dword ptr ds:[esi+_DISK_NUM_SECTORS_OFFSET]     ; base-1
        mov     edx,dword ptr ss:[ebp+24]
        .IF (bl >= byte ptr ss:[ebp+13] || al >= byte ptr ss:[ebp+14] || cl > byte ptr ss:[ebp+15] || dl > 1)
          ; At least one of the parameters specified is beyond the acceptable scope.  This is bad.  Very bad.
            mov     dword ptr ss:[ebp+24],_FDC_INVALID_PARAMETERS
            stc
            jmp     iFDC_read_sector_quit
        .ENDIF
      ; All parameters are withing the physical capabilities of the drive

;; Initialize our retry count
        mov     dword ptr ss:[ebp-04],-3

      iFDC_read_sector_top:
;; Build the command based on their command
        push    dword ptr _DMA_channel_fdc                          ; channel to use
        push    dword ptr _DMA_mode_single_transfer                 ; type of transfer
        push    dword ptr _DMA_increment                            ; direction
        mov     eax,dword ptr ss:[ebp+16]                           ; where to write
        push    eax
        push    word ptr _DMA_operation_read                        ; operation type - read from the device
        push    word ptr 512                                        ; number of bytes to transfer
        call    fword ptr cs:_iDMA_setup

;; Send the read-track commands to the FDC
        mov     ah,byte ptr ss:[ebp+24]                             ; Double density mode?
        shl     ah,6                                                ; Shift into bit position 6
        mov     al,_FDC_CMD_READ_TRACK
        or      al,ah
      ; Right now, al - the command byte (per what the user setup)
        call    fword ptr cs:_iFDC_send_byte
        mov     al,byte ptr ss:[ebp+12]                             ; Drive letter
        sub     al,"A"
        call    fword ptr cs:_iFDC_send_byte
        mov     al,byte ptr ss:[ebp+13]                             ; Cylinder
        call    fword ptr cs:_iFDC_send_byte
        mov     al,byte ptr ss:[ebp+14]                             ; Head
        call    fword ptr cs:_iFDC_send_byte
        mov     al,byte ptr ss:[ebp+15]                             ; Sector
        call    fword ptr cs:_iFDC_send_byte
        mov     al,bh                                               ; Sector size code
        call    fword ptr cs:_iFDC_send_byte
        mov     al,byte ptr ds:[esi+_DISK_NUM_SECTORS_OFFSET]       ; EOT number (the same as the sector they're trying to read)
        call    fword ptr cs:_iFDC_send_byte
        mov     al,byte ptr ds:[esi+_DISK_FLOPPY_GAP_LENGTH_OFFSET] ; Gap length
        call    fword ptr cs:_iFDC_send_byte
        mov     al,0ffh                                             ; Data length (force 0ffh)
        call    fword ptr cs:_iTASK_irq6_prep_wait
        call    fword ptr cs:_iFDC_send_byte
        call    fword ptr cs:_iTASK_irq6_wait_for_signal
      ; Right now it should've read the data

;; Read the result bytes
        push    ss
        pop     es
        mov     edi,ebp
        sub     edi,20                                              ; This brings us down on the stack to [ebp-20]
      ; Right now, es:[edi] - far pointer to location to store 7 result bytes
        mov     ecx,7
        call    invFDC_read_result_bytes
        mov     al,byte ptr es:[edi+5]                              ; Get the first byte (this is new sector number)
        .IF (al >= byte ptr ss:[ebp-12])
;; Success
            mov     dword ptr ss:[ebp+24],512                       ; # of bytes read
            clc
        .ELSE
;; Failure this attempt
            inc     dword ptr ss:[ebp-04]
            jno     iFDC_read_sector_top
;; Failure after 3 retries
            mov     dword ptr ss:[ebp+24],_FDC_SECTOR_NOT_FOUND
            stc
        .ENDIF
    .ENDIF

  iFDC_read_sector_quit:
    popad
    pop     es
    pop     ds
    leave
    retf    12
iFDC_read_sector    ENDP




iFDC_read_track     PROC
; This procedure is used to read one track from the floppy disk
; Upon entry:   Parameters are passed on the stack, see below
; Upon exit:    carry? - SET or CLEAR indicating error status
;               return value - error code or 512 * num_sectors, depending on error status
;
  ; [esp+20] - DWORD, (return) error code or # of bytes read (constant of 512 * num_sectors if all goes well)
  ; [esp+16] - DWORD, (param)  dest es
  ; [esp+12] - DWORD, (param)  dest edi  * Note, es:[edi] must point to a (512 * num_sectors) byte buffer for the transfer
  ; [esp+11] - BYTE,  (param)  nuserved
  ; [esp+10] - BYTE,  (param)  head
  ; [esp+9]  - BYTE,  (param)  cylinder number
  ; [esp+8]  - BYTE,  (param)  drive letter
  ; [esp+4]  - DWORD, cs
  ; [esp+0]  - DWORD, eip
    stc
    retf    12
iFDC_read_track     ENDP




iFDC_write_sector   PROC
; This procedure is used to write one sector of data from the floppy disk
; Upon entry:   Parameters are passed on the stack, see below
; Upon exit:    carry? - SET or CLEAR indicating error status
;               return value - error code or 512, depending on error status
;
  ; [esp+20] - DWORD, (return) error code or # of bytes written (constant of 512 if all goes well)
  ; [esp+16] - DWORD, (param)  dest ds
  ; [esp+12] - DWORD, (param)  dest esi  * Note, ds:[esi] must point to a 512 byte buffer for the transfer
  ; [esp+11] - BYTE,  (param)  sector
  ; [esp+10] - BYTE,  (param)  head
  ; [esp+9]  - BYTE,  (param)  cylinder number
  ; [esp+8]  - BYTE,  (param)  drive letter
  ; [esp+4]  - DWORD, cs
  ; [esp+0]  - DWORD, eip
    stc
    retf    12
iFDC_write_sector   ENDP




iFDC_write_track    PROC
; This procedure is used to write one track to the floppy disk
; Upon entry:   Parameters are passed on the stack, see below
; Upon exit:    carry? - SET or CLEAR indicating error status
;               return value - error code or 512 * num_sectors, depending on error status
;
  ; [esp+20] - DWORD, (return) error code or # of bytes written (constant of 512 * num_sectors if all goes well)
  ; [esp+16] - DWORD, (param)  dest ds
  ; [esp+12] - DWORD, (param)  dest esi  * Note, ds:[esi] must point to a (512 * num_sectors) byte buffer for the transfer
  ; [esp+11] - BYTE,  (param)  nuserved
  ; [esp+10] - BYTE,  (param)  head
  ; [esp+9]  - BYTE,  (param)  cylinder number
  ; [esp+8]  - BYTE,  (param)  drive letter
  ; [esp+4]  - DWORD, cs
  ; [esp+0]  - DWORD, eip
    stc
    retf    12
iFDC_write_track    ENDP




iFDC_format_track   PROC
; This procedure is used to format a track
; Upon entry:   Parameters are passed on the stack, see below
; Upon exit:    carry? - SET or CLEAR indicating error status
;
  ; [esp+12] - DWORD, (return) error code or # of sectors formatted
  ; [esp+11] - BYTE,  (param)  nuserved
  ; [esp+10] - BYTE,  (param)  head
  ; [esp+9]  - BYTE,  (param)  cylinder number
  ; [esp+8]  - BYTE,  (param)  drive letter
  ; [esp+4]  - DWORD, cs
  ; [esp+0]  - DWORD, eip
    stc
    retf    4
iFDC_format_track   ENDP




iFDC_seek_track     PROC
; This procedure is used to move the read/write head to a specific track (or cylinder)
; Upon entry:   Parameters are passed on the stack, see below
; Upon exit:    carry? - SET or CLAER indicating error status
;
    enter   0,0
  ; [ebp+16] - DWORD, (return) error code
  ; [ebp+15] - BYTE,  Nuserved
  ; [ebp+14] - BYTE,  (param)  cylinder number
  ; [ebp+13] - BYTE,  (param)  head
  ; [ebp+12] - BYTE,  (param)  drive letter
  ; [ebp+8]  - DWORD, cs
  ; [ebp+4]  - DWORD, eip
  ; [ebp+0]  - DWORD, ebp
    pushad

;; Initialize our retry count
    mov     dword ptr ss:[ebp+16],-5                                ; Try a maximum of 5 times

  iFDC_seek_track_again:
    mov     eax,dword ptr ss:[ebp+12]
    mov     ebx,dword ptr ss:[ebp+14]
    .IF (al == 'A' || al == 'B' && ah <= 1 && bl < 80)
      ; We're good.  The drive letter is OK, the head is OK and the cylinder is in the range 0-79
;; Issue the seek
        mov     al,_FDC_CMD_SEEK
        call    fword ptr cs:_iFDC_send_byte
        sub     al,'A'
        shl     ah,2                                                ; It is known from above that ah is only 0 or 1
        or      al,ah                                               ; After this, al = 00000:H:DD, where DD=drive code (00-A, 01-B)
        call    fword ptr cs:_iFDC_send_byte
        mov     al,bl                                               ; cylinder was in bl (from above)
        call    fword ptr cs:_iTASK_irq6_prep_wait                  ; Prepare for the IRQ6
        call    fword ptr cs:_iFDC_send_byte                        ; Send last command byte

;; Wait for IRQ6 acknowledgement
        call    fword ptr cs:_iTASK_irq6_wait_for_signal            ; Wait for the IRQ6
        jnc     @F
      ; If we're here, then the _iTASK_irq6_wait_for_signal did not happen after 5 seconds, it's a timeout error :(
        mov     eax,_FDC_TIMEOUT
        jmp     iFDC_seek_track_error

      @@:
      ; If we're here, then the IRQ6 was received correctly :)  Woo hoo!
;; Sense interrupt (see if the seek was completed correctly)
        call    fword ptr cs:_iFDC_sense_interrupt                  ; Now, see if that bad boy completed it's duties with all the
                                                                    ;   respect you'd come to expect from a such a viscious bad boy
        cmp     al,bl                                               ; If the PCN (Present Cylinder Number) matches our CN we're ok
        jz      @F                                                  ; Branch if we're good to go, baby! :)

      ; If we're here, then the seek didn't work.  DAMN!  Try again
        inc     dword ptr ss:[ebp-16]
        jno     iFDC_seek_track_again                               ; Note, I see your mind popping with the big question "Why
                                                                    ; do we loop up so high" ... It's because al, ah and bl were
                                                                    ; destroyed.  That's my only reason, I sware!  Now listen here!
                                                                    ; We're only looping there when something fails, so this little
                                                                    ; bit of inefficient code means nothing in the overall grand
                                                                    ; scheme of things.  But, thank you for recognizing it.  I'm
                                                                    ; proud to work with such keen observers of my code.  It does
                                                                    ; my heart good to know that ... oh, shuttup!  Right.  Sorry.

      ; If we're here, then we've already tried 5 times now and failed.  Do you believe this?  5 retries ... they all failed!
        mov     eax,_FDC_SEEK_FAILED                                ; Oh well, what to do ... leave the disk to its misery
        jmp     iFDC_seek_track_error                               ; Report the error and head back to base.  Yes, sir.

      @@:
;; Everything was successful
      ; If we're here, then we're good to go.  Everything's running smoothly.  And you?
        clc
    .ELSE
;; Report the error
        mov     eax,_FDC_INVALID_PARAMETERS
      iFDC_seek_track_error:
        mov     dword ptr ss:[ebp+16],eax
        stc
    .ENDIF

    popad
    leave
    retf    4
iFDC_seek_track     ENDP




iFDC_seek_relative      PROC
; This procedure is used to move the read/write head out or in a specified number of tracks (or cylinders)
; Upon entry:   Parameters are passed on the stack, see below
; Upon exit:    carry? - SET or CLAER indicating error status
;
  ; [esp+16] - DWORD, (return) error code or # of sectors formatted
  ; [esp+12] - INT32, (param)  cylinders to move out (positive) or in (negative)
  ; [esp+10] - WORD,  Nuserved
  ; [esp+9]  - BYTE,  Nuserved
  ; [esp+8]  - BYTE,  (param)  drive letter
  ; [esp+4]  - DWORD, cs
  ; [esp+0]  - DWORD, eip
    stc
    retf    4
iFDC_seek_relative      ENDP




iFDC_sense_interrupt    PROC
; This procedure is used to
; Upon entry:   Nothing
; Upon exit:    ax - two bytes returned from the sense interrupt command (ah=status register 0, al=present cylinder number)
;
;; Send the command
    mov     al,_FDC_CMD_SENSE_INTERRUPT
    call    fword ptr cs:_iFDC_send_byte

;; Read the results
    call    fword ptr cs:_iFDC_read_byte
    mov     ah,al                                                   ; Move the first byte returned into ah
    call    fword ptr cs:_iFDC_read_byte                            ; This means the second byte returned into al

    retf
iFDC_sense_interrupt    ENDP


initialize_disk_drives      PROC
; This routine is used to determine if basic floppy drives and IDE/SCSI hard drives are on the system
    mov     esi,offset initializing_floppy
    call    iVT_display_string_nr_vga

    mov     ax,_sSYSTEM_AREA
    mov     es,ax
    xor     edi,edi

;; Drive A:
    mov     esi,offset option_blank
    call    iVT_display_string_vga
    mov     esi,offset drive_letter
    mov     byte ptr [esi+6],"A"
    call    iVT_display_string_vga
;; Get the CMOS drive info
    mov     al,byte ptr es:[edi+_SYSTEM_FLOPPY_DRIVE_TYPE]
    shr     al,4                                                    ; al = upper nibble of source value (drive A:)
    call    determine_floppy_parameters
    pushf
    call    iVT_display_string_nr_vga
    popf
;; Build the memory tables for this disk drive (if applicable)
    .IF (!carry?)
                                                                    ; ah already contains the drive type (360k, 1.2MB, etc)
        mov     al,00000011b                                        ; device specs (removable media, internal device)
        shl     eax,16                                              ; move ax to high word of dword
        mov     al,01h                                              ; type of controller - floppy
        mov     ah,01h                                              ; type of device - disk
        push    eax                                                 ; eax = (bytes) specs:device:controller
        push    dword ptr 2                                         ; number of heads
        push    dword ptr 512                                       ; number of bytes per sector
        push    ecx                                                 ; number of sectors per track
        push    edx                                                 ; number of tracks per side
        push    ebx                                                 ; total capacity
        call    iDISK_add_drive
      ; Returns al = disk number

        xor     ah,ah                                               ; File system type (unknown, drive has not been accessed yet)
        and     eax,0ffffh
        push    eax                                                 ; disk_number:file_system
        push    dword ptr 0                                         ; starting_head
        push    dword ptr 0                                         ; starting_track
        push    dword ptr 1                                         ; starting_sector
        push    dword ptr 1                                         ; ending_head
        push    edx                                                 ; ending_track
        push    ecx                                                 ; ending_sector
        push    dword ptr 0ffffh                                    ; GDT selector (this indicates none yet)
        push    dword ptr 0000000000000111b                         ; seekable:writeable:readable
        push    dword ptr "A"
        call    iDISK_add_partition
    .ENDIF

;; Drive B:
    mov     esi,offset option_last
    call    iVT_display_string_vga
    mov     esi,offset drive_letter
    inc     byte ptr [esi+6]
    call    iVT_display_string_vga
;; Get the CMOS drive info
    mov     al,byte ptr es:[edi+_SYSTEM_FLOPPY_DRIVE_TYPE]
    and     al,0fh                                                  ; al = lower nibble of source value (drive B:)
    call    determine_floppy_parameters
    pushf
    call    iVT_display_string_nr_vga
    popf
;; Build the memory tables for this disk drive (if applicable)
    .IF (!carry?)
                                                                    ; ah already contains the drive type (360k, 1.2MB, etc)
        mov     al,00000011b                                        ; device specs (removable media, internal device)
        shl     eax,16                                              ; move ax to high word of dword
        mov     al,01h                                              ; type of controller - floppy
        mov     ah,01h                                              ; type of device - disk
        push    eax                                                 ; eax = (bytes) specs:device:controller
        push    dword ptr 2                                         ; number of heads
        push    dword ptr 512                                       ; number of bytes per sector
        push    ecx                                                 ; number of sectors per track
        push    edx                                                 ; number of tracks per side
        push    ebx                                                 ; total capacity
        call    iDISK_add_drive
      ; Returns al = disk number

        xor     ah,ah                                               ; File system type (unknown, drive has not been accessed yet)
        and     eax,0ffffh
        push    eax                                                 ; disk_number:file_system
        push    dword ptr 0                                         ; starting_head
        push    dword ptr 0                                         ; starting_track
        push    dword ptr 1                                         ; starting_sector
        push    dword ptr 1                                         ; ending_head
        push    edx                                                 ; ending_track
        push    ecx                                                 ; ending_sector
        push    dword ptr 0ffffh                                    ; GDT selector (this indicates none yet)
        push    dword ptr 0000000000000111b                         ; seekable:writeable:readable
        push    dword ptr "B"
        call    iDISK_add_partition
    .ENDIF

; REMEMBER
;;; Hard disk 0
;    mov     si,offset initializing_ide
;    call    display_string_next_row_vga
;    mov     si,offset disk_number
;    mov     word ptr [si+5],"00"
;    call    iVT_display_string_vga
;    mov     al,byte ptr es:[di+_SYSTEM_HARD_DRIVE_TYPE]
;    mov     bl,al

    ret
initialize_disk_drives      ENDP

    determine_floppy_parameters     PROC
    ; Upon entry, al = value returned from BIOS about the type of floppy drive
    ; Upon exit:  Everything is updated, see below
    ;             cf - CLEAR if OK, SET if error
        .IF (al == 0)
            mov     esi,offset not_available + 2
            stc
        .ELSEIF (al == 1)
            mov     esi,offset floppy_360
            mov     ebx,9 * 40 * 512 * 2                                ; total capacity
            mov     ecx,9                                               ; sectors per track
            mov     edx,40                                              ; tracks per side
            mov     ah,_FLOPPY_360K
            clc
        .ELSEIF (al == 2)
            mov     esi,offset floppy_12
            mov     ebx,15 * 80 * 512 * 2                               ; total capacity
            mov     ecx,15                                              ; sectors per track
            mov     edx,80                                              ; tracks per side
            mov     ah,_FLOPPY_1_2MB
            clc
        .ELSEIF (al == 3)
            mov     esi,offset floppy_720
            mov     ebx,9 * 80 * 512 * 2                                ; total capacity
            mov     ecx,9                                               ; sectors per track
            mov     edx,80                                              ; tracks per side
            mov     ah,_FLOPPY_720K
            clc
        .ELSEIF (al == 4)
            mov     esi,offset floppy_144
            mov     ebx,18 * 80 * 512 * 2                               ; total capacity
            mov     ecx,18                                              ; sectors per track
            mov     edx,80                                              ; tracks per side
            mov     ah,_FLOPPY_1_44MB
            clc
        .ELSEIF (al == 5)
            mov     esi,offset floppy_288
            mov     ebx,36 * 80 * 512 * 2                               ; total capacity
            mov     ecx,36                                              ; sectors per track
            mov     edx,80                                              ; tracks per side
            mov     ah,_FLOPPY_2_88MB
            stc
        .ELSE
            mov     esi,offset unknown
            stc
        .ENDIF
        ret
    determine_floppy_parameters     ENDP

    INCLUDE disk.asp
    INCLUDE fdc.asp