; boot.asm
;
; Exodus - 512 byte boot record for floppy disk
;          * Note:  It is known that this disk is bootable, the only error we'll have to report is missing "Exodus Boot Program"
;          * Note:  Many of the labels have been added for illustrative purposes.  They may not be referenced.
;          * Note:  The final thing this boot algorithm does before transferring control to BOOTUP.COM is point ds:[si] to
;                   a parameter block.  Refer to parameter_block: below for more information.

    .MODEL tiny

    .386P
;_XDEBUG     EQU 1

INCLUDE \exodus\source\common\equates.asp

_MAIN       SEGMENT WORD PUBLIC 'CODE'
    ORG 0
  ; Transfer control to linear 7c0h:<offset> (it makes it a SEG0 reference)
  absolute_begin:
  ; These next two lines are the same as JMP FAR 07C0H:000Fh
    db  0eah
    dd  007c0000fh                                                  ; cs = 07c0h, ip = 000fh

  ; Identify this version
    db  1,0                                                         ; version 1.0
    db  "DT/NP/RP"                                                  ; TAG/identifier

; Note, start_of_code is at offset 15=0fh
  start_of_code:
  ; Execution resumes here (it's a far jump to ensure we're at CS:0 for our starting point)
    cli
    push    word ptr 4000h
    pop     ss
    mov     sp,0fffeh                                               ; Stack points to 4fffeh
    sti                                                             ;  (this is because Exodus loads from 10000h to 50000h (256k))

  Setup_Local_Variables:
    enter   32,0
  ; [bp-4]  - --Nuserved
  ; [bp-8]  - --Nuserved
  ; [bp-10] - --Nuserved
  ; [bp-11] - byte, start track
  ; [bp-12] - byte, start head
  ; [bp-13] - byte, start sector
  ; [bp-14] - byte, end track
  ; [bp-15] - byte, end head
  ; [bp-16] - byte, end sector
  ; [bp-17] - byte, DT identifier
  ; [bp-18] - --Nuserved
  ; [bp-22] - --Nuserved
  ; [bp-24] - --Nuserved
  ; [bp-28] - dword, offset into memory where we're loading data from disk
  ; [bp-32] - dword, bytes loaded so far
  ;  others - --Nuserved

;; Display bootup identification
  display_bootup_id:
    push    cs
    push    cs
    pop     ds
    pop     es
    mov     ax,01301h                                               ; Write string
    mov     bx,31                                                   ; Color 31, bright white on blue
    mov     cx,offset Boot_Message_End - offset Boot_Message
    xor     dx,dx                                                   ; 0,0
    mov     bp,offset Boot_Message
    int     10h


;; Load the Data Table, Name Pool and Resource Pool
;; BIOS disk read of sectors 2, 3 and 4, plus the debugger
  Read_Sectors:
    mov     ax,0200h + 03                                           ; Read 3 DT, NP & RP sectors
    push    word ptr 0800h                                          ; Store at 0800:0000h, or 8000h
    pop     es
    xor     bx,bx
    mov     cx,0002h                                                ; track 0/sector 2
    xor     dx,dx                                                   ; head 0/drive 0
    int     13h                                                     ; Read the bad boy
    jnc     Read_Sectors1
    jmp     Read_Sectors
  Read_Sectors1:
;; Note - Here is where the LOAD_XDEBUG() function would go if a debugger is required (see SAVE.ASP)
;; Identify which entries are load-bootable
    push    word ptr 0800h                                          ; Set ES to point to the DT
    pop     es
    mov     si,(512 * 2) + 2                                        ; Pointer to RP (stored at 0800:0000 + (512*2) (from the BIOS disk read above))
    mov     edx,offset end_of_data_label                            ; Get our starting offset from the memory variable
    xor     cx,cx
    mov     di,2
;-[ loop ]------
  Top_Loop:
        cmp     byte ptr es:[di],128                                ; Is this a bootable entry?
        jnz     Next_Item                                           ; No if branch

      ; This is a bootable entry
        mov     ah,byte ptr es:[di+10]                              ; Get the boot attribute byte
        mov     byte ptr [bp-17],ah                                 ; Store for future use
        cmp     ah,0101b                                            ; See if it's a special boot loader (this replaces this program as boot loader)
        jnz     @F                                                  ; No if branch
      Boot_Loader_Found:
      ; Is is a boot loader, we load this and transfer control
        mov     dx,offset end_of_data_label                         ; Restore the original value
        xor     cx,cx                                               ; Sortof fake out any previous loads that might've taken place
        jmp     Do_This_One                                         ; Continue on and load this one
      @@:
        test    ah,1b                                               ; Should we load it immediately?
        jz      Next_Item                                           ; No if branch
      ; Yes, load it immediately
      Boot_Program_Found:
      Do_This_One:
        mov     bx,si
        add     bx,word ptr es:[di+8]                               ; Store the data structure in the following format:
                                                                    ; See the complete breakdown of this structure at end of file
        mov     eax,dword ptr es:[bx]                               ; 0-3, File size (in bytes)
        mov     dword ptr [edx+_BOOT_PB_size],eax

        mov     eax,dword ptr es:[bx+4]                             ; 4-7, Offset into executable for main() (where to jmp far)
        mov     dword ptr [edx+_BOOT_PB_main],eax

        mov     eax,dword ptr es:[bx+8]                             ; 8-11, Offset into executable for requestor()
        mov     dword ptr [edx+_BOOT_PB_requestor],eax

        mov     eax,dword ptr es:[bx+12]                            ; 12-15, Start Head/Track/Sector/not used
        mov     dword ptr [edx+_BOOT_PB_start_head],eax

        mov     eax,dword ptr es:[bx+16]                            ; 16-20, End Head/Track/Sector/not used
        mov     dword ptr [edx+_BOOT_PB_end_head],eax                              ;        * Note:  This information is *NOT USED* during bootup

        mov     al,byte ptr es:[di+10]                              ; 20, Entry type
        mov     word ptr [edx+_BOOT_PB_entry_type],ax

        mov     word ptr [edx+_BOOT_PB_dt_offset],di                ; 26, DT offset for this entry
        sub     word ptr [edx+_BOOT_PB_dt_offset],2

        mov     ax,word ptr es:[di+13]                              ; 28, CRC16
        mov     word ptr [edx+_BOOT_PB_crc16],ax

        add     dx,_BOOT_PB_structure_size                          ; Move to the next one
        inc     cx                                                  ; Increase our count
        cmp     byte ptr [bp-17],0101b                              ; If this is a special boot loader then we don't need to load any more programs, just this one
        jz      Load_It                                             ; It is a special boot loader if branch
  Next_Item:
    add     di,16                                                   ; Move to the next item in the DT
    cmp     di,512                                                  ; Are we beyond the size of the DT?
    jl      Top_Loop                                                ; No if branch
;---------------


  ; We're through scanning the first DT
    mov     byte ptr [edx+_BOOT_PB_entry_type],0ffh                 ; Terminate our listing
    or      cx,cx
    jz      Reboot_With_Message_And_Key                             ; If branch here there then no were bootable record(s) found

;; Load the data from the disk
  Load_It:                                                          ; Load at 10000h, or 64k
    mov     total_bp_bytes,dx
    sub     total_bp_bytes,(offset parameter_block)
    mov     esi,offset end_of_data_label                            ; Get the pointer to load information
    mov     dword ptr [bp-28],10000h
  Read_Next_File:
    mov     eax,dword ptr [bp-28]
    mov     dword ptr [si+_BOOT_PB_linear_offset],eax
    mov     dword ptr [bp-32],0                                     ; Reset our "bytes loaded so far" count
  Read_Next_Sector:
    xor     ecx,ecx
    xor     ebx,ebx

    mov     dh,byte ptr [si+_BOOT_PB_start_head]                    ; Head
    mov     ch,byte ptr [si+_BOOT_PB_start_track]                   ; Track
    mov     cl,byte ptr [si+_BOOT_PB_start_sector]                  ; Sector
    xor     dl,dl                                                   ; drive

    push    word ptr 0900h                                          ; Load this sector of data to 9000h
    pop     es
    xor     bx,bx

    mov     ax,0201h                                                ; BIOS Read disk sectors/read 1
    int     13h                                                     ; Read it
    jnc     @F
    cmp     ah,6
    jz      Read_Next_Sector
;    jmp     Read_Next_Sector
    jmp     Reboot_With_Message_And_Key
  @@:
  ; Right now the file was loaded to 09000h, we need to copy it to the correct location
  ; So, we do that here
    push    si
    push    ds

    push    es
    pop     ds
    xor     si,si
  ; Get es:[di] - far ptr to where it's supposed to go
    mov     eax,dword ptr [bp-28]                                   ; Memory location to load into es:[bx]
    mov     di,ax
    and     di,0fh
    shr     eax,4
    mov     es,ax
    mov     cx,512
  ; Right now, es:[di] - far ptr to where it's supposed to go
    cld
    rep     movsb

    pop     ds
    pop     si

    mov     ebx,512                                                 ; Bytes_per_sector
    add     dword ptr [bp-28],ebx                                   ; Increase the offset by the bytes per sector
    add     dword ptr [bp-32],ebx                                   ; Increase the number of bytes loaded so far
    mov     edx,dword ptr [bp-32]
    cmp     edx,dword ptr [si]                                      ; Total number of bytes to load
    jae     Check_More_Boot_Programs

    inc     byte ptr [si+_BOOT_PB_start_sector]
    mov     al,cs:sectors
    cmp     byte ptr [si+_BOOT_PB_start_sector],al
    jle     Read_Next_Sector
    mov     byte ptr [si+_BOOT_PB_start_sector],1                   ; We're passed the last sector

  ; Display a dot each time we read an entire track for one head
    pusha
    mov     ax,00e2eh                                               ; Write character (2eh = ".")
    mov     bx,31                                                   ; bh=page, bl=color
    int     10h
    popa
    inc     byte ptr [si+_BOOT_PB_start_head]
    cmp     byte ptr [si+_BOOT_PB_start_head],1
    jle     Read_Next_Sector
    mov     byte ptr [si+_BOOT_PB_start_head],0                     ; We're past the maximum head

    inc     byte ptr [si+_BOOT_PB_start_track]                      ; Move to the next track
    jmp     Read_Next_Sector

  Check_More_Boot_Programs:
    add     si,_BOOT_PB_structure_size
    add     dword ptr [bp-28],16                                    ; Paragraph align the next item (if any)
    and     dword ptr [bp-28],0fffffff0h
    cmp     byte ptr [si+_BOOT_PB_entry_type],0ffh
    jne     Read_Next_File

  Finished:
    push    cs
    pop     ds
    mov     si,offset parameter_block
    mov     cx,total_bp_bytes
    mov     edx,dword ptr [bp-28]
  ; Transfer control to linear 10000h
    push    word ptr 1000h                                          ; cs
    push    word ptr 0                                              ; ip
    retf


  Reboot_With_Message_And_Key:
    push    cs
    pop     es
    mov     ax,01301h
    mov     bx,31
    mov     cx,offset Disk_Message_End - offset Disk_Message
    mov     dx,1600h                                                ; 22,0
    mov     bp,offset Disk_Message
    int     10h
  Wait_For_Key:
    xor     ah,ah
    int     16h
  Reboot:
    int     19h

  Boot_Message:
    db  " Exodus 10.10.2010 "
  Boot_Message_End:

  Disk_Message:
    db  "� Error "
  Disk_Message_End:

    sectors         db  18
    total_bp_bytes  dw  0

    dt_linear       dd 8000h
    np_linear       dd 8200h
    rp_linear       dd 8300h
  parameter_block:
    boot_drive      db  "A"                                         ; Drive letter the operating system was booting from

  End_Of_Data_Label:

;
; boot_parameter_block
;
; Bootable program structure
; --------------------------
; Repeat once entry for every "Exodus Boot Program" found in the first DT:
;     Offset  Length    Decription
;     ------  ------    -------------
;       0       4       file size
;       4       4       Offset for main()
;       8       4       Offset for requestor()
;       12      1       (starting) Head
;       13      1       (starting) Track
;       14      1       (starting) Sector
;       15      1       --Nuserved
;       16      1       (ending) Head
;       17      1       (ending) Track
;       18      1       (ending) Sector
;       19      1       --Nuserved
;       20      1       Entry type
;       21      1       --Nuserved
;       22      4       Linear offset in memory where this file starts
;       26      2       DT offset
;       28      2       CRC16 (copied from DT)
;       30      2       --Nuserved
;     Total = 32 bytes
;

_MAIN   ENDS

END
