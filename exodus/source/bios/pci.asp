; pci.asp
;
; Exodus Peripheral Controller Interconnect routines
;
;   iPCI_read_dword()                       - Reads a value from a particular bus, device, function and doubleword
;   iPCI_write_dword()                      - Writes a value to a particular bus, device, function and doubleword
;   iPCI_verbalize_device_type()            - Looks at aspects of a PCI device and returns structured verbose description of it
;   iPCI_verbalize_device_manufacturer()    - Looks in the database of known PCI devices to return information about it
;
;   invPCI_parse_CSM_register()             - Builds the CSM register (Configuration Space Mapping)
;   invPCI_read_dword()                     - Reads a dword from the PCI bus based on the CSM value in eax
;   invPCI_write_dword()                    - Reads a dword from the PCI bus based on the CSM value in eax
;
; * Note:  These are all local routines (there are no CALL GATES to these functions)
; * Note:  Refer to INF\PCI.INF for more information
;



iPCI_read_dword     PROC
; This routine reads a doubleword value from a particular bus, device, function and doubleword
;
; Upon entry:   dh - bus
;               dl - function
;               bh - device
;               bl - doubleword
;
; Upon exit:    eax - value
;
    push    edx
    push    ebx

    call    invPCI_parse_CSM_register
    call    invPCI_read_dword

    pop     ebx
    pop     edx
    ret
iPCI_read_dword     ENDP




iPCI_write_dword    PROC
; This routine writes a doubleword value from a particular bus, device, function and doubleword
;
; Upon entry:   dh - bus
;               dl - function
;               bh - device
;               bl - doubleword
;              eax - value
;
; Upon exit:    Nothing
;
    push    edx
    push    ebx

    push    eax
    call    invPCI_parse_CSM_register
    pop     ebx
    call    invPCI_write_dword

    pop     ebx
    pop     edx
    ret
iPCI_write_dword    ENDP




iPCI_verbalize_device_type      PROC
; This routine writes a doubleword value from a particular bus, device, function and doubleword
;
; Upon entry:   al - Prog I/F
;               ah - sub-class code
;              eal - class code
;
; Upon exit:    ds:[esi] - far ptr to NULL-terminated string representing device classification
;               ds:[edi] - far ptr to NULL-termianted string representing device sub-classification
;
; * For information about these class_codes and sub_class_codes, look to data.asp.  Contained within is a fixed structure which
;   is what these little .WHILE ... .ENDW loops are parsing.
;
    push    eax
    push    ebx
    push    ecx

    mov     bl,al
    shr     eax,8
  ; Right now, ah - class code
  ;            al - sub-class code
  ;            bl - Prog I/F
    mov     esi,offset class_codes
    xor     ecx,ecx
    .WHILE (byte ptr [esi] != 0ffh)
        cmp     byte ptr [esi],ah
        jz      @F
        mov     cl,byte ptr [esi+1]
        add     ecx,3
        add     esi,ecx
    .ENDW
  ; It is unknown, which means it goes to the "undetermined" category on the list
  @@:
    add     esi,2

    mov     edi,offset sub_class_codes
    xor     ecx,ecx
    .WHILE (byte ptr [edi] != 0ffh)
        cmp     byte ptr [edi],ah
        jnz     skip_it
        cmp     byte ptr [edi+1],al
        jnz     skip_it
        cmp     byte ptr [edi+2],bl
        jz      @F
      skip_it:
        mov     cl,byte ptr [edi+3]
        add     ecx,5
        add     edi,ecx
    .ENDW
  ; It is unknown, which means it goes to "other"
  @@:
    add     edi,4

    pop     ecx
    pop     ebx
    pop     eax
    ret
iPCI_verbalize_device_type      ENDP




iPCI_verbalize_device_manufacturer      PROC
; This routine determines the device manufacturer/model based on the Vendor ID and Device ID
;
; Upon entry:   ax - Vendor ID
;               upper 16-bits of eax - Device ID
;               * Note, this is the 0-doubleword returned from the iPCI_read_dword
;
; Upon exit:    es:[edi] - far ptr to NULL-terminated string of the manufacturer/model
;
    ;; REMEMBER
    push    eax

    mov     ax,_sDATA
    mov     es,ax
    mov     edi,offset feature_not_finished

    pop     eax
    ret
iPCI_verbalize_device_manufacturer      ENDP




invPCI_parse_CSM_register   PROC
; This routine is only used internally.  It parses the entry information into the output information
;
; Upon entry:   dh - bus
;               dl - function
;               bh - device
;               bl - doubleword
;
; Upon exit:    eax - Configuration Space Mapping register in a format to send to port 03C8h
;
    and     dl,111b                                                 ; Only 0-7 allowed
    and     bh,11111b                                               ; Only 0-31 allowed
    and     bl,111111b                                              ; Only 0-63 allowed
    mov     eax,80000000h                                           ; Enable bit=1
    and     ebx,0ffffh
    ror     ebx,16                                                  ; Swap ebx words
    mov     bl,dh
    ror     ebx,16
    shl     bh,3                                                    ; Move device to bits [15..11]
    or      bh,dl
    shl     bl,2
    or      eax,ebx
    ret
invPCI_parse_CSM_register   ENDP




invPCI_read_dword       PROC
; This routine is only used internally.  It parses the entry information into the output information
;
; Upon entry:   eax - CSM register
;
; Upon exit:    eax - value
;
    push    edx

    mov     dx,_PCI_INDEX
    out     dx,eax                                                  ; Set the index
    jmp     $+2
    mov     dx,_PCI_DATA
    in      eax,dx                                                  ; Read the value

    pop     edx
    ret
invPCI_read_dword       ENDP




invPCI_write_dword      PROC
; This routine is only used internally.  It parses the entry information into the output information
;
; Upon entry:   eax - CSM register
;               ebx - value to write
;
; Upon exit:    Nothing
;
    push    edx

    mov     dx,_PCI_INDEX
    out     dx,eax                                                  ; Set the index
    jmp     $+2
    mov     dx,_PCI_DATA
    mov     eax,ebx                                                 ; Restored as eax
    in      eax,dx                                                  ; Write the value

    pop     edx
    ret
invPCI_write_dword      ENDP



initialize_pci      PROC
; This routine gathers information from the PCI bus and stores it for later use
    pushad
    push    fs
    enter   8,0
  ; [ebp-01] - byte, --nuserved
  ; [ebp-02] - byte, device
  ; [ebp-03] - byte, count of devices found
  ; [ebp-04] - byte, bus
  ; [ebp-08] - dword, ptr into _sPCI_DEVICES

    mov     esi,offset initializing_pci
    call    iVT_display_string_nr_vga

    mov     ax,_sPCI_DEVICES
    mov     fs,ax

;; Now, scan for PCI devices
    xor     eax,eax
    mov     dword ptr ss:[ebp-04],eax
    mov     dword ptr ss:[ebp-08],eax
  @@:
    mov     dh,byte ptr ss:[ebp-04]                                 ; bus
    mov     bh,byte ptr ss:[ebp-02]                                 ; device
    xor     dl,dl                                                   ; function
    xor     bl,bl                                                   ; doubleword
    call    iPCI_read_dword
    .IF (eax != 0ffffffffh)
      ; This is a valid item.  Let's determine what it is
      ; Save the vendor id/device id
        mov     esi,dword ptr ss:[ebp-08]
        mov     dword ptr fs:[esi],eax
        add     dword ptr ss:[ebp-08],4

      ; Now, get the classification information.. heh heh
        mov     bl,2
        call    iPCI_read_dword
        shr     eax,8

      ; Save the classification information
        mov     esi,dword ptr ss:[ebp-08]
        mov     dword ptr fs:[esi],eax
        add     dword ptr ss:[ebp-08],4

      ; Right now, eax contains the class code data
        call    iPCI_verbalize_device_type
      ; Right now, ds:[esi] - far ptr to classification
      ;            ds:[edi] - far ptr to sub-classification
        push    edi

        push    esi
        mov     esi,offset option_blank
        call    iVT_display_string_vga
        pop     esi
        call    iVT_display_string_vga

        mov     esi,offset comma_space
        call    iVT_display_string_vga

        pop     esi
        call    iVT_display_string_nr_vga
        inc     byte ptr ss:[ebp-03]
    .ENDIF
    inc     byte ptr ss:[ebp-02]
    .IF (byte ptr ss:[ebp-02] <= 31)
        jmp     @B
    .ENDIF
    mov     byte ptr ss:[ebp-02],0
    inc     byte ptr ss:[ebp-04]
    .IF (byte ptr ss:[ebp-04] <= 7)
        jmp     @B
    .ENDIF
  ; We've scanned all the PCI devices

;; Terminate our structure
    mov     esi,dword ptr ss:[ebp-08]
    mov     dword ptr fs:[esi+00],0ffffffffh
    mov     dword ptr fs:[esi+04],0ffffffffh

;; Update the display
    .IF (byte ptr ss:[ebp-03] != 0)
        call    iVT_get_cursor_vga
        dec     dh
        call    iVT_position_cursor_vga
        mov     esi,offset option_last
        call    IVT_display_string_nr_vga
    .ENDIF

;; We're finished
    leave
    pop     fs
    popad
    ret
initialize_pci      ENDP

    INCLUDE pci.asp