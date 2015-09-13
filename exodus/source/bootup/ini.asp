; ini.asp
;
; Exodus parse EXODUS.INI routines
;
;  Functions:
;     Ã invParse_Exodus_ini                             ; Locate the Exodus.INI table
;     Ã invParse_Exodus_ini_build_structure             ; Physically build the bootup structure
;     À invDetermine_Exodus_ini_ownership               ; Calls the requestor('ini ') functions of all native primatives to
;                                                       ;  find out who the owner of each item is
;



invFind_Exodus_ini      PROC    NEAR
; This routine is used to parse the EXODUS.INI
;
; Upon entry:   Nothing
;
; Upon exit:    The EXODUS.INI text file has been converted
;
    enter   84,0
  ;------------
  ; These two variables are defined in this procedure
  ; [ebp-04] - dword, length of exodus.ini
  ; [ebp-08] - dword, linear offset in memory to start of exodus.ini
  ; [ebp-12] - dword, count (number of exodus.ini's found)
  ;------------
  ; The rest of this local variable space is defined and used in invParse_Exodus_ini()
  ; Please look there for their definitions
  ;
    pushad
    push    ds
    push    es
    push    fs
    push    gs

    mov     dword ptr ss:[ebp-04],0ffffffffh                        ; length
    mov     dword ptr ss:[ebp-08],0ffffffffh                        ; linear offset
    mov     dword ptr ss:[ebp-12],0                                 ; count

    mov     ax,_sALL_MEM
    mov     ds,eax
    mov     edi,cs:boot_parameter_block
    inc     edi                                                     ; Skip past the "drive booted from" byte
  ; Right now, ds:[edi] - far ptr to the boot parameter block
    .WHILE (byte ptr ds:[edi] != 0ffh)
        mov     al,byte ptr ds:[edi+_BOOT_PB_entry_type]
        and     al,1111b
        .IF (al == 0001b)
          ; It's EXODUS.INI (refer to INF\FILE_SYS.INF for information on these bits)
            mov     edx,dword ptr ds:[edi+_BOOT_PB_size]
            mov     dword ptr ss:[ebp-04],edx
            mov     edx,dword ptr ds:[edi+_BOOT_PB_linear_offset]
            mov     dword ptr ss:[ebp-08],edx
            inc     dword ptr ss:[ebp-12]
        .ENDIF

        add     edi,_BOOT_PB_structure_size
    .ENDW
    .IF (dword ptr ss:[ebp-12] == 1)
      ; Only one EXODUS.INI was found, so we're in business
        call    invParse_Exodus_ini
        .IF (carry?)
          ; Some error occurred during the parse
            mov     dword ptr ss:[ebp-12],0ffffffffh
            jmp     @F
        .ENDIF
    .ELSE
      ; More than one EXODUS.INI was found, or there were errors from processing invParse_Exodus_ini() above
      @@:
      ;; Set the VGA video mode to 80x25 text and the color to red
        mov     ax,_sDATA
        mov     ds,eax
        call    invSet_80x25_text_mode
        mov     al,12
        call    fword ptr cs:_VID_set_attribute_vga
        call    fword ptr cs:_VID_move_to_next_line_vga
        .IF (dword ptr ss:[ebp-12] == 0ffffffffh)
          ; Error occurred during processing
            mov     esi,offset error_loading_exodus_ini_1
        .ELSEIF (dword ptr ss:[ebp-12] == 0)
          ; No EXODUS.INI was found
            mov     esi,offset error_loading_exodus_ini_2
        .ELSE
          ; Multiple EXODUS.INI's were found
            mov     esi,offset error_loading_exodus_ini_3
        .ENDIF
        call    fword ptr cs:_VID_display_string_nr_vga

      ; These messages are in BOOTUP\DATA32.ASP
        mov     esi,offset error_loading_exodus_ini_4
        call    fword ptr cs:_VID_display_string_nr_vga

        mov     esi,offset system_halted
        call    fword ptr cs:_VID_display_string_nr_vga
      @@:
        hlt
        jmp @B
    .ENDIF


  finished:
    pop     gs
    pop     fs
    pop     es
    pop     ds
    popad
    leave
    ret
invFind_Exodus_ini      ENDP





invParse_Exodus_ini     PROC
; This routine is used to parse the Exodus.INI file and build an internal structure that's suitable for parsing.
;
; Upon entry:   [ebp-04] - length of file
;               [ebp-08] - offset to start of EXODUS.INI
;                     ds - _sALL_MEM (used for Exodus.ini and the output structure)
;               * Note also that this algorithm uses the stack frame/local variables created in invFind_Exodus_ini
;               * Refer to that algorithm for local variables
;
; Upon exit:    The structure is updated
;               edx - !zero if any errors encountered
;
;
  ; The variables above are defined in the invFind_Exodus_ini() algorithm above.
  ; They already exist when this procedure gets control.
  ; [ebp-04] - dword, length of exodus.ini
  ; [ebp-08] - dword, linear offset in memory to start of exodus.ini
  ; [ebp-12] - Note, this value is reused as its significance is no longer significant. :)
  ;----------
  ; These slots are all defined here and are used here and in invParse_Exodus_ini_store_error()
  ; [ebp-12] - dword, line number of exodus.ini
  ; [ebp-16] - dword, are we in a bracket grouping?  0-no, 1-yes
  ; [ebp-20] - dword, are we in a paren grouping?  0-no, 1-yes
  ; [ebp-24] - dword, source line offset (start of)
  ; [ebp-28] - dword, store line to error area?  0-no, 1-yes
  ; [ebp-32] - dword, header offset
  ; [ebp-36] - dword, current bracket group structure item
  ; [ebp-40] - dword, currently processing a bracket group? 0-no, 1-yes
  ; [ebp-44] - dword, currently processing a paren cask? 0-no, 1-yes
  ; [ebp-48] - dword, total # of paren casks
  ; [ebp-52] - dword, count of bytes left in exodus.ini
  ; [ebp-56] - dword, souce line offset (first non-whitespace)
  ; [ebp-60] - dword, current paren cask structure
  ; [ebp-64] - dword, number of chars to backup (due to ¯'s being found)
  ; [ebp-68] - dword, current paren cask structure (if more than one per line)
  ; [ebp-70] - word,  --Nuserved
  ; [ebp-80] - tbyte, miscellaneous BCD values used to report error line numbers, etc
  ; [ebp-84] - dword, last data item
int 3
    ret
    mov     dword ptr ss:[ebp-12],1                                 ; starting line number (base-1)
    mov     dword ptr ss:[ebp-16],0                                 ; bracket grouping?  0-no
    mov     dword ptr ss:[ebp-20],0                                 ; paren grouping?  0-no

  ; Load the EXODUS.INI variables
    mov     ecx,dword ptr ss:[ebp-04]
    mov     esi,dword ptr ss:[ebp-08]
    mov     dword ptr ss:[ebp-52],ecx

    mov     edx,_sEXODUS_INI
    mov     es,edx
    mov     edx,_sEXODUS_INI_ERRORS
    mov     fs,edx
    xor     edi,edi
    xor     edx,edx
  ; Right now,   ecx - count
  ;         ds:[esi] - far ptr to start of exodus.ini
  ;         es:[edi] - where we'll store our converted structure
  ;         fs:[edx] - where we'll store error text

  ; Initialize our EXODUS.INI structure
    mov     dword ptr es:[edi+_EXODUS_INI_FIRST_BRACKET],0ffffffffh
    mov     dword ptr es:[edi+_EXODUS_INI_TOTAL_BYTES],0
    mov     dword ptr es:[edi+_EXODUS_INI_TOTAL_BRACKET_GROUPS],0
    mov     dword ptr es:[edi+_EXODUS_INI_TOTAL_PAREN_CASKS],0

  ; Initalize our starting variables
    mov     dword ptr ss:[ebp-32],edi                               ; Start of header
    add     edi,_EXODUS_INI_HEADER_LENGTH
    mov     dword ptr ss:[ebp-36],edi                               ; Start of data

    mov     dword ptr ss:[ebp-40],0                                 ; No bracket group
    mov     dword ptr ss:[ebp-44],0                                 ; No paren cask

  ; Right now, es:[edi] - ready for starting structure
    .WHILE (dword ptr ss:[ebp-52] > 0)
      ; Skip passed any leading spaces or tabs
        mov     dword ptr ss:[ebp-28],0                             ; store line to error area?  0-no
        mov     dword ptr ss:[ebp-24],esi                           ; start of line
        .WHILE (byte ptr ds:[esi] == 32 || byte ptr ds:[esi] == 9 && dword ptr ss:[ebp-52] > 0)
            inc     esi
            dec     dword ptr ss:[ebp-52]
        .ENDW
        cmp     dword ptr ss:[ebp-52],0
        jz      finished

      ; Right now we're passed the white spaces
        mov     eax,dword ptr ds:[esi]
        .IF (al == ';' || ax == 0d0ah || ax == 0a0dh)
          ; This is a comment line, we skip it
            jmp     next_line
        .ENDIF

      ; Store first non-whitespace offset
        mov     dword ptr ss:[ebp-56],esi

      ; Right now we're at the start of something
        .IF (al == '[')
          ; It's the start of a bracket grouping
            .IF (dword ptr ss:[ebp-40] != 0)
              ; We're already processing a bracket group, we have to close this one out
                mov     ebx,dword ptr ss:[ebp-36]
              ; Right now, es:[ebx] - far ptr to previous bracket group structure
                mov     dword ptr es:[ebx+_EXODUS_BRACKET_NEXT],edi
            .ELSE
              ; We're starting anew
              ; Update header (if necessary)
                 mov     ebx,dword ptr ss:[ebp-32]
                .IF (dword ptr es:[ebx+_EXODUS_INI_FIRST_BRACKET] == 0ffffffffh)
                    mov     eax,dword ptr ss:[ebp-36]
                    mov     dword ptr es:[ebx+_EXODUS_INI_FIRST_BRACKET],eax
                .ENDIF
            .ENDIF
          ; Get the name into eax
            xor     eax,eax
            xor     ecx,ecx
            inc     esi
            dec     dword ptr ss:[ebp-52]
            .WHILE (dword ptr ss:[ebp-52] > 0 && ecx < 4 && byte ptr ds:[esi] != ']')
                shl     eax,8
                mov     al,byte ptr ds:[esi]
                inc     esi
                dec     dword ptr ss:[ebp-52]
                inc     ecx
            .ENDW
            .IF (ecx == 4)
              ; The bracket group's name is too long
                mov     ebx,offset parse_bracket_group_name_too_long
                call    invParse_Exodus_ini_store_error
                mov     dword ptr ss:[ebp-28],1
                jmp     next_line
            .ENDIF
            .IF (byte ptr ds:[esi] != ']')
              ; We hit the end of file before we loaded everything
                mov     ebx,offset parse_unexpected_end_of_file
                call    invParse_Exodus_ini_store_error
                mov     dword ptr ss:[ebp-28],1
                jmp     next_line
            .ENDIF

          ; Everything is good
          ; Pad any names less than 4 characters with spaces
            .WHILE (ecx < 4)
                shl     eax,8
                mov     al,32
                inc     ecx
            .ENDW

          ; Right now, eax contains the name to use
          ; Initialize this item's structure
            mov     dword ptr es:[edi+_EXODUS_BRACKET_NEXT],0ffffffffh
            mov     dword ptr es:[edi+_EXODUS_BRACKET_PAREN_CASKS],0ffffffffh
            mov     dword ptr es:[edi+_EXODUS_BRACKET_TOTAL_PARENS],0
            mov     dword ptr es:[edi+_EXODUS_BRACKET_NAME],eax
            mov     dword ptr es:[edi+_EXODUS_BRACKET_HANDLE],0ffffffffh
            mov     word ptr es:[edi+_EXODUS_BRACKET_REQUESTOR],0ffffh
            mov     dword ptr es:[edi+_EXODUS_BRACKET_REQUESTOR_FUNC],0ffffffffh
            mov     dword ptr es:[edi+_EXODUS_BRACKET_SCRATCH_AREA],0ffffffffh

          ; Raise/lower the flags
            mov     dword ptr ss:[ebp-40],1                     ; Bracket group flag
            mov     dword ptr ss:[ebp-44],0                     ; Paren cask flag

          ; Store the current bracket group pointer
            mov     dword ptr ss:[ebp-36],edi

          ; Move past this structure (for future data)
            add     edi,_EXODUS_BRACKET_LENGTH

        .ELSEIF (al == '(')
          ; It's the start of a paren cask
int 3
            .IF (dword ptr ss:[ebp-44] != 0)
              ; We're already processing a cask, we have to close this one out
                mov     ebx,dword ptr ss:[ebp-60]
              ; Right now, es:[ebx] - far ptr to previous bracket group structure
                mov     dword ptr es:[ebx+_EXODUS_PAREN_NEXT],edi
            .ELSE
              ; We're starting anew
              ; Update bracket group item (if necessary)
                mov     ebx,dword ptr ss:[ebp-36]
                mov     dword ptr es:[ebx+_EXODUS_BRACKET_PAREN_CASKS],eax
            .ENDIF

          ; Lower flag for more than one cask per line
            mov     dword ptr ss:[ebp-68],0ffffffffh

          ; Initialize this item's structure
          do_next_cask:
            mov     dword ptr es:[edi+_EXODUS_PAREN_NEXT],0ffffffffh
            mov     dword ptr es:[edi+_EXODUS_PAREN_NEXT_SAME_LINE],0ffffffffh
            mov     dword ptr es:[edi+_EXODUS_PAREN_DATA_ITEMS],0ffffffffh
            mov     dword ptr es:[edi+_EXODUS_PAREN_TOTAL_DATA_ITEMS],0
            mov     dword ptr es:[edi+_EXODUS_PAREN_SOURCE_LINE],esi
            mov     dword ptr es:[edi+_EXODUS_PAREN_SOURCE_LINE_LENGTH],0
            mov     dword ptr es:[edi+_EXODUS_PAREN_HANDLE],0ffffffffh
            mov     word ptr es:[edi+_EXODUS_PAREN_REQUESTOR],0ffffh
            mov     dword ptr es:[edi+_EXODUS_PAREN_REQUESTOR_FUNC],0ffffffffh
            mov     dword ptr es:[edi+_EXODUS_PAREN_SCRATCH_AREA],0ffffffffh

          ; Raise/lower the flags
            mov     dword ptr ss:[ebp-44],1                         ; Raise the "processing paren cask" flag
            mov     dword ptr ss:[ebp-64],0                         ; Back off for ¯ chars

          ; Copy current structure pointer to ebx
            mov     ebx,edi
          ; And move to next structure pointer in edi
            add     edi,_EXODUS_PAREN_LENGTH

          ; Now, process the cask to load all of its data items
          ; Right now, ebx - used as the pointer to the current structure
            inc     esi
            dec     dword ptr ss:[ebp-52]
            inc     dword ptr es:[ebx+_EXODUS_PAREN_SOURCE_LINE_LENGTH]

          ; Create the data item structure
            mov     dword ptr ss:[ebp-84],0ffffffffh                ; Lower the "last data item" flag
          do_next_data_item:
            mov     dword ptr es:[edi+_EXODUS_DATA_NEXT],0ffffffffh
            mov     dword ptr es:[edi+_EXODUS_DATA_DATA_ITEM_SOURCE],esi
            mov     dword ptr es:[edi+_EXODUS_DATA_DATA_ITEM_LENGTH],0
            .WHILE (byte ptr ds:[esi] != ')' && dword ptr ss:[ebp-52] > 0 && word ptr ds:[esi] != 0d0ah && word ptr ds:[esi] != 0a0dh)
                .IF (byte ptr ds:[esi] == '¯')
                  ; We skip past this character and assume that the next one is the real one
                  ; This character means "whatever is next is to be used literally", thereby giving a way for () and | chars to
                  ; be used as data within a cask (also, if the ¯ character needs to appear it has to be represented by ¯¯)
                    inc     dword ptr ss:[ebp-64]
                .ELSE
                    .IF (byte ptr ds:[esi] == '|' || byte ptr ds:[esi] == ')')
                      ; This is a data item separator or a cask closer
                        mov     edx,esi
                        sub     edx,dword ptr es:[edi+_EXODUS_DATA_DATA_ITEM_SOURCE]
                        mov     dword ptr es:[edi+_EXODUS_DATA_DATA_ITEM_LENGTH],edx
                        .IF (dword ptr ss:[ebp-84] == 0ffffffffh)
                          ; This is the first data item
                            mov     dword ptr ss:[ebp-84],edi
                            mov     dword ptr es:[ebx+_EXODUS_PAREN_DATA_ITEMS],edi
                        .ELSE
                            mov     edx,dword ptr ss:[ebp-84]
                            mov     dword ptr es:[edx+_EXODUS_DATA_NEXT],edi
                        .ENDIF
                        inc     dword ptr es:[ebx+_EXODUS_PAREN_TOTAL_DATA_ITEMS]
                        add     edi,_EXODUS_DATA_LENGTH
                        jmp     do_next_data_item
                    .ENDIF
                .ENDIF
                .IF (dword ptr ss:[ebp-52] > 0)
                    inc     esi
                    dec     dword ptr ss:[ebp-52]
                    inc     dword ptr es:[ebx+_EXODUS_PAREN_SOURCE_LINE_LENGTH]
                .ENDIF
            .ENDW
            .IF (dword ptr ss:[ebp-52] == 0 || word ptr ds:[esi] != 0d0ah || word ptr ds:[esi] != 0a0dh)
              ; We have unexpectedly hit the end of file
                mov     ebx,offset parse_unexpected_end_of_file
                call    invParse_Exodus_ini_store_error
                mov     dword ptr ss:[ebp-28],1
                jmp     next_line
            .ENDIF

          cask_finished:
          ; We're past this cask, see if there are any more on the same line
            .WHILE (byte ptr ds:[esi] == 32 || byte ptr ds:[esi] == 9 && dword ptr ss:[ebp-52] > 0)
                inc     esi
                dec     dword ptr ss:[ebp-52]
            .ENDW
            .IF (dword ptr ss:[ebp-52] == 0 || byte ptr ds:[esi] != '(')
                jmp     next_line
            .ENDIF

            .IF (byte ptr ds:[esi] == '(')
              ; There is another cask, we need to process this one
                mov     dword ptr es:[ebx+_EXODUS_PAREN_NEXT_SAME_LINE],edi
                mov     dword ptr ss:[ebp-68],edi
                jmp     do_next_cask
            .ELSE
                mov     ebx,offset parse_expected_paren
                call    invParse_Exodus_ini_store_error
                mov     dword ptr ss:[ebp-28],1
            .ENDIF

        .ELSE
          ; This is an error.  Lines cannot stand by themselves with data on it
            mov     ebx,offset parse_expected_bracket_paren
            call    invParse_Exodus_ini_store_error
            mov     dword ptr ss:[ebp-28],1
        .ENDIF

      next_line:
      ; Skip until we reach the end of the line
        .IF (dword ptr ss:[ebp-28] != 0)
          ; We have to copy this line to the error output
            mov     esi,dword ptr ss:[ebp-24]
        .ENDIF
        .WHILE (word ptr ds:[esi] != 0d0ah && word ptr ds:[esi] != 0a0dh && dword ptr ss:[ebp-52] > 0)
            .IF (dword ptr ss:[ebp-28] != 0)
              ; We need to copy this line to the error area
                mov     al,byte ptr ds:[esi]
                mov     byte ptr fs:[edx],al
                inc     edx
            .ENDIF
            inc     esi
            dec     dword ptr ss:[ebp-52]
        .ENDW
        .IF (dword ptr ss:[ebp-28] != 0)
          ; Store CR/LF to the error line
            mov     word ptr fs:[edx],0a0dh
            add     edx,2
        .ENDIF
        .IF ((word ptr ds:[esi] == 0d0ah || word ptr ds:[esi] == 0a0dh) && dword ptr ss:[ebp-52] >= 2)
            add     esi,2
            sub     dword ptr ss:[ebp-52],2
        .ENDIF
        inc     dword ptr ss:[ebp-12]                               ; increase line number
    .ENDW

  finished:
    ret
invParse_Exodus_ini     ENDP




invParse_Exodus_ini_store_error     PROC
; This routine is used to copy the line number and an error message from cs:[ebx] to fs:[edx]
;
; Upon entry:   cs:[ebx] - far ptr to null-terminated message to store
;               fs:[edx] - far ptr to where to store
;
; Upon exit:    It's stored
;               edx - where the next message will be stored
;
    push    ebx

;-------
    push    esi
    push    ecx
    push    ebx
    push    es

  ; Store the line number
    mov     eax,_sDATA
    mov     es,eax
    finit
    fild    dword ptr ss:[ebp-12]
    fbstp   tbyte ptr ss:[ebp-80]
    mov     eax,dword ptr ss:[ebp-80]
    mov     esi,offset line_text + 5
  ; Right now, eax contains the BCD nibbles of the current line number
    mov     ecx,8                                                   ; This lowers the flag in ch and stores 8 to cl
  @@:
    rol     eax,4
    mov     bl,al
    and     bl,0fh
    .IF (bl != 0 || (bl == 0 && ch != 0))
      ; We're storing this value
        add     bl,'0'
        mov     byte ptr es:[esi],bl
        inc     esi
        mov     ch,1                                                ; raise the flag to copy bytes
    .ENDIF
    dec     cl
    jnz     @B
    mov     dword ptr es:[esi+0],00202d20h                          ; this is "<null>_-_"

  ; Store the line number
    mov     esi,offset line_text
    .WHILE (byte ptr es:[esi] != 0)
        mov     al,byte ptr es:[esi]
        inc     esi
        mov     byte ptr fs:[edx],al
        inc     edx
    .ENDW

    pop     es
    pop     ebx
    pop     ecx
    pop     esi
;-------

  ; Store the error message
    .WHILE (byte ptr cs:[ebx] != 0)
        mov     al,byte ptr cs:[ebx]
        inc     ebx
        mov     byte ptr fs:[edx],al
        inc     edx
    .ENDW

  ; Store the trailing CR/LF
    mov     word ptr fs:[edx],0a0dh
    add     edx,2

    pop     ebx
    ret
invParse_Exodus_ini_store_error     ENDP



invDetermine_Exodus_ini_ownership       PROC    NEAR
; This routine is used to call all of the Requestor('ini ') routines for all the native primatives.  It allows them to decide
; what items in the exodus.ini file they have ownership of
;
; Upon entry:   Nothing
;
; Upon exit:    Nothing
;

    ret

invDetermine_Exodus_ini_ownership       ENDP
