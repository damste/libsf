



find_above_1MB_memory   PROC
; This routine tries to write a byte to each 1MB block, starting at 1MB + 1
; If it reads back the same value it wrote then it assumes memory is there, if it reads back 0 then no memory is there
; Returns:  dx - number of megabytes installed
    mov     esi,offset total_memory                                  ; Tell the what we're doing
    call    iVT_display_string_vga

;; Scan through memory checking the first byte of each Megabyte block.  It is known that all memory above 1 MB must be installed
;; in one or two-megabyte blocks, so we just check every megabyte.  We write a byte and see if we can read back the byte we wrote
    push    ds
    mov     ax,_sALL_MEM                                            ; Load the "all memory" selector
    mov     ds,ax
    mov     esi,0100000h                                            ; Start scanning above 1MB
    .WHILE (esi < 0fffe0000h)                                       ; Scan up through 4GB
        mov     byte ptr ds:[esi],'E'                               ; Write an E
        .IF (byte ptr ds:[esi] != 'E')                              ; See if we can read back an E, will read back 0 if no memory
          ; No memory here
            jmp     @F
        .ENDIF
        add     esi,010000h                                         ; Move to the next 64k block
    .ENDW
  @@:
    pop     ds

;; Store the # of bytes and calculate the # of megabytes
    mov     ds:installed_memory,esi                                 ; Store how much memory we found (in bytes)

;; Update the memory sub-structure
    push    es
    mov     ax,_sMEMORY
    mov     es,ax
    xor     edi,edi
    .WHILE (byte ptr es:[edi] != _STOPPER)
        mov     al,byte ptr es:[edi]
        .IF (al == _MEMORY_FREE && dword ptr es:[edi+_MEMORY_FREE_LIMIT] == 0ffffffffh)
          ; This is the one!
            mov     dword ptr es:[edi+_MEMORY_FREE_LIMIT],esi
            jmp     @F
        .ENDIF
        add     edi,_MEMORY_SUBSTRUCT_SIZE
    .ENDW
  @@:
    pop     es

;; Show the user how many megabytes total memory were found
    mov     edx,esi                                                 ; Now, find out how many MB's
    shr     edx,20                                                  ; Divide by 2^20 = 0100000h
    call    iVT_display_decimal_in_edx_vga                          ; Display the # of Megabytes for the user
    mov     esi,offset memory_mb
    call    iVT_display_string_nr_vga

    ret
find_above_1MB_memory   ENDP