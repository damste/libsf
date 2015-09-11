; native.asp
;
; Exodus Native Primatives declaration
; December 24, 2000
;
; * Refer to inf\native.inf for more information
; * Note, the mechanical operations of this process are governed by inf\primload.inf
; * Native Primatives run in the call gate range of 200 - 2999
;
;  Functions:
;    Ã invSetup_native_primatives               ; sets up the native primates specified as boot drivers
;    Ã default_primative_response               ; provides a system for undefined primatives
;    Ã invCopy_this_part                        ; copies a portion of data (called multiple times)
;    Ã invMove_temp_gdts_to_permanent           ; copies the temporary primative GDT entries to their permanent locations
;    Ã invAdd_primative                         ; adds a primative to between _MIN_PRIMATIVE and _MAX_PRIMATIVE call gates
;    À invUpdate_required_primatives            ; updates an driver/program with the required call gates to run
;
;





invSetup_native_primatives      PROC    NEAR
; This routine is responsible for setting up all Exodus native primatives
;
; Upon entry:   It is known that the GDT slots setup in the init16 algorithms are used
;
; Upon exit:    The native primative call gates are defined in the GDT and IDT
;
    push    gs
    push    fs
    push    es
    push    ds
  ; * Note:  Can't use EBP here because it is returned as a parameter from the primatives
  ; * Note:  These references all use ESP.  No PUSH/POP's are to be used unless they are self-terminating
  ;          and in-between references of ss:[esp+xx].
    sub     esp,68
  ; [esp+64] - <Used for debugging>
  ; [esp+60] - temporary
  ; [esp+56] - temporary
  ; [esp+52] - temporary
  ; [esp+48] - temporary
  ; [esp+44] - holds primative selector
  ; [esp+40] - ptr to NP in linear memory
  ; [esp+36] - ptr to DT in linear memory
  ; [esp+32] - holds current value of esi (boot_parameter_block)
  ; [esp+28] - temporary "Length of definition block" ptr into _sPRIMATIVE_LOAD_INFO
  ; [esp+24] - requestor(-1) ebp - ptr to author text (null-terminated)
  ; [esp+20] - requestor(-1) ebx - ptr to version text (null-terminated)
  ; [esp+16] - requestor(-1) edi - ptr to driver self-identified name (null-terminated)
  ; [esp+12] - requestor(-1) esi - ptr to native primative structure for this driver
  ; [esp+08] - --Nuserved
  ; [esp+04] - requestor(-1) ecx - actual number of bytes to keep after each driver is initialized
  ; [esp+00] - driver name from NP (linear offset in memory)
  ;

    cld
  ;; Setup the parameters for the default primative response
    xor     eax,eax
    mov     ebx,offset default_primative_response                   ; Offset to function
    xor     ecx,ecx                                                 ; Number of dword to copy if privledge level change
    mov     dx,_sCODE                                               ; Code segment selector
    mov     eax,_MIN_PRIMATIVE
    .WHILE (eax <= _MAX_PRIMATIVE)
        call    invCreate_call_gate_descriptor32
        inc     eax
    .ENDW

  ;; Initialize our primative memory areas
    mov     eax,_sPRIMATIVES
    mov     es,eax
    xor     edi,edi
    mov     ecx,_sPRIMATIVES_limit
    mov     al,0ffh
    rep     stosb
    mov     dword ptr es:[0],8
    mov     dword ptr es:[4],_MIN_PRIMATIVE

    mov     eax,_sPRIMATIVE_LOAD_INFO
    mov     es,eax
    xor     edi,edi
    mov     ecx,_sPRIMATIVE_LOAD_INFO_limit
    xor     al,al
    rep     stosb
    mov     dword ptr es:[0],4

  ;; Now, process all of the drivers that were loaded at bootup
    mov     eax,_sALL_MEM
    mov     ds,eax
    mov     esi,cs:boot_parameter_block
    inc     esi                                                     ; Move passed the boot drive letter
    mov     ebx,cs:boot_dt_linear
    mov     ecx,cs:boot_np_linear
    mov     dword ptr ss:[esp+36],ebx
    mov     dword ptr ss:[esp+40],ecx
    mov     dword ptr ss:[esp+64],0                                 ; Used for debugging
    .WHILE (byte ptr ds:[esi+_BOOT_PB_entry_type] != 0ffh)
      ; Let's see what this bad boy is
        mov     al,byte ptr ds:[esi+_BOOT_PB_entry_type]
        and     al,1111b
        .IF (al == 011b)
          ; It's a driver
          ; Store driver name (linear offset to it)
            mov     dword ptr ss:[esp+32],esi
            mov     ebx,dword ptr ss:[esp+36]
            mov     edx,dword ptr ss:[esp+40]

            xor     eax,eax
            mov     ax,word ptr ds:[esi+_BOOT_PB_dt_offset]
            add     ebx,eax
            .IF (word ptr ds:[ebx+_BOOT_DT_np_offset] != 0ffffh)
              ; Name was specified
                mov     edx,cs:boot_np_linear
                xor     eax,eax
                mov     ax,word ptr ds:[esi+_BOOT_DT_np_offset]
                add     edx,eax
            .ELSE
                mov     edx,0ffffffffh
            .ENDIF
            mov     dword ptr ss:[esp+00],edx

          ;; Build the temporary GDT entries for our initialization

          ; Build the temporary code segment
            mov     eax,_csTEMP_PRIMATIVE / 8
            mov     ebx,dword ptr ds:[esi+_BOOT_PB_linear_offset]
            mov     edx,dword ptr ds:[esi+_BOOT_PB_size]
            call    invCreate_code_descriptor32

          ; Build the temporary data segment
            mov     eax,_dsTEMP_PRIMATIVE / 8
            mov     ebx,dword ptr ds:[esi+_BOOT_PB_linear_offset]
            mov     edx,dword ptr ds:[esi+_BOOT_PB_size]
            call    invCreate_data_descriptor32

          ; Build the temporary call gates
            mov     eax,_cgTEMP_PRIMATIVE_MAIN / 8
            mov     ebx,dword ptr ds:[esi+_BOOT_PB_main]
            xor     ecx,ecx
            mov     dx,_csTEMP_PRIMATIVE
            call    invCreate_call_gate_descriptor32

            mov     eax,_cgTEMP_PRIMATIVE_REQUESTOR / 8
            mov     ebx,dword ptr ds:[esi+_BOOT_PB_requestor]
            xor     ecx,ecx
            mov     dx,_csTEMP_PRIMATIVE
            call    invCreate_call_gate_descriptor32

;; Call the requestor function to get "Program Information"
;; 'info'

          ; Ok, the temporary code segment, data segment and call gate are built
          ; Now, we need to call the requestor function so it can work its magic
            mov     eax,_dsTEMP_PRIMATIVE
            mov     ds,eax
            mov     eax,'info'                                      ; Requestor function for "Program Information"
            callg   _cgTEMP_PRIMATIVE_REQUESTOR
          ; Right now, the information specified in INF\REQUESTR.INF is supposed to be available
            .IF (eax != 'nati')
              ; This program was identified as a driver in DT, but it's not a native primative.  This is a fatal error.
                call    init_failed                                 ; at the bottom of this source file
                ; * Note:  The init_failed() routine is terminal.  Control will never return here.
            .ENDIF
          ; It is a driver.  We should treat it as such. :)
          ; Store the information it provided to us
            mov     dword ptr ss:[esp+04],ecx
            mov     dword ptr ss:[esp+12],esi
            mov     dword ptr ss:[esp+16],edi
            mov     dword ptr ss:[esp+20],ebx
            mov     dword ptr ss:[esp+24],ebp

          ; Now, let's copy the relevent information
            mov     eax,_sPRIMATIVES
            mov     es,eax
            mov     eax,_sPRIMATIVE_LOAD_INFO
            mov     fs,eax
            mov     eax,_sALL_MEM
            mov     gs,eax

          ; Copy the this driver's code and data segment GDT entries from their temporary area to a permanent area
            mov     eax,dword ptr es:[4]
            shl     eax,3                                           ; Multiply by 8
            mov     esi,dword ptr ss:[esp+32]
            call    invMove_temp_gdts_to_permanent
            shr     eax,3                                           ; Divide by 8
            mov     dword ptr es:[4],eax

          ; Get our starting offsets into the two memory areas
            mov     edi,dword ptr fs:[0]
            mov     ebx,dword ptr es:[0]


          ;; Do the load info structure
          ;; * Refer to inf\primload.inf for information on this structure
            mov     word ptr fs:[edi],bx                            ; store the offset in our load info structure
            mov     eax,edi
            add     eax,2
            mov     dword ptr ss:[esp+28],eax                       ; Now, store a ptr to the location where we'll eventually
                                                                    ;   store the length of the primative structure this driver
                                                                    ;   has requested (the ptr is stored in temp variable space)
          ; Move past those two word entries
            add     edi,4

          ; Store the driver's filename
          ; A small degree of indirection here :)
            mov     eax,dword ptr ss:[esp+32]                       ; Get a pointer to this driver's boot_parameter_block entry
            xor     ebx,ebx
            mov     bx,word ptr gs:[eax+_BOOT_PB_dt_offset]         ; Which tells us where our DT entry is
            add     ebx,2                                           ; Move past the sector indicator
            add     ebx,dword ptr ss:[esp+36]
            mov     bx,word ptr gs:[ebx+_BOOT_DT_np_offset]         ; Which tells us where our NP entry is
            and     ebx,0ffffh
            add     ebx,2
            add     ebx,dword ptr ss:[esp+40]
            xor     ecx,ecx
            mov     cl,byte ptr gs:[ebx]                            ; Where we get our filename length
            inc     ecx
            .REPEAT                                                 ; And finally, where we copy the text from
                mov     al,byte ptr gs:[ebx]
                mov     byte ptr fs:[edi],al
                inc     ebx
                inc     edi
            .UNTILCXZ

          ; Store the driver's self-assigned name (what it calls itself)
            mov     ebx,dword ptr ss:[esp+16]
            call    invCopy_this_part

          ; Store the driver's version text
            mov     ebx,dword ptr ss:[esp+20]
            call    invCopy_this_part

          ; Store the author's name text
            mov     ebx,dword ptr ss:[esp+24]
            call    invCopy_this_part

          ; Store the GDT offsets for the main portions of this function
            push    gs
            mov     eax,_sSYSTEM
            mov     gs,eax
            mov     eax,dword ptr gs:[_SYSTEM_i_CODE_GDT_OFFSET]
            mov     dword ptr fs:[edi],eax
            mov     ebp,eax
            add     edi,4
            mov     eax,dword ptr gs:[_SYSTEM_i_DATA_GDT_OFFSET]
            mov     dword ptr fs:[edi],eax
            add     edi,4
            mov     eax,dword ptr gs:[_SYSTEM_i_MAIN_GDT_OFFSET]
            mov     dword ptr fs:[edi],eax
            add     edi,4
            mov     eax,dword ptr gs:[_SYSTEM_i_REQUESTOR_GDT_OFFSET]
            mov     dword ptr fs:[edi],eax
            add     edi,4
            pop     gs

          ; And, finally, update the next location pointer in this _sPRIMATIVE_LOAD_INFO structure
            mov     dword ptr fs:[0],edi

          ;; Parse their primatives structure
          ;; * Refer to inf\primload.inf for information on the structure this information is converted to in Exodus
          ;; * Refer to inf\requestr.inf for information on the structure the driver provides
            mov     esi,dword ptr ss:[esp+12]
            xor     ecx,ecx
            .WHILE (byte ptr [esi] != 0ffh)
                mov     cl,byte ptr [esi]
                inc     esi
                mov     edx,dword ptr [esi+ecx]                     ; Offset to function
                mov     bx,word ptr [esi+ecx+4]                     ; Dwords to copy
                mov     eax,dword ptr es:[4]                        ; Call gate for this primative
                shl     eax,3                                       ; Multiply by 8 to get the call gate offset (rather than slot)
              ; Right now,      ds:[esi] - far ptr to primative function name
              ;                      ebp - code segment for this driver
              ;                      eax - GDT slot
              ;                      ecx - length
              ;                      edx - offset into driver for access to this function
              ;                       bx - dwords to copy

              ; Let's add it
                call    invAdd_primative
                inc     dword ptr es:[4]                            ; Move to the next primative SLOT

                add     esi,ecx                                     ; Move past the function name
                add     esi,6                                       ; Move past the function offset (dword)
            .ENDW                                                   ;   and number of dwords to copy (word)


          ; At this point, we've received all the information from this first REQUESTOR request
          ; The additional request, 'prim' and 'ints' are not executed until after *ALL* the drivers are loaded (in case they're
          ;                         loaded out of order.  Look below for the followup loads that take place once all the
          ;                         primatives have been installed.

          ; Phew!
          ; It's loaded and all processed and everything
            .IF (cs:vga_kbd_support == 0)
              ; We don't have our VGA/keyboard drivers installed yet, let's see if this most recent driver installed any of them
                mov     eax,_sDATA
                mov     ds,eax

                mov     esi,offset required_native_primatives
                mov     edi,offset _VID_clear_screen_vga
                call    invUpdate_required_primatives
                .IF (!carry?)
                  ; All required primatives were found
                  ; We have the ability to display stuff on the screen and get a key
                    mov     ds:vga_kbd_support,1
                .ENDIF
            .ENDIF

          @@:
          ; Proceed along happily to the next driver :)
            mov     eax,_sALL_MEM
            mov     ds,eax
            mov     esi,dword ptr ss:[esp+32]
        .ENDIF

      next_native_primative:
        add     esi,_BOOT_PB_structure_size
    .ENDW


  ; If we're here, then everything has loaded ok, or the ones that didn't load correctly were ignored
  ; Now, since all of the drivers were loaded we need to go ahead and call the remaining requestor() functions, 'prim' and 'ints'
  ; Once those are called we call main() in each one in the order loaded
  ;
  ; * Note:  When we get here, all of the [esp+xx] references above are no longer in use
  ;



  ; Setup the video information for the following portion of code.  From here on out we're fully digital, baby! :)
  ;
    mov     eax,_sDATA
    mov     es,eax
    mov     ebx,_sPRIMATIVE_LOAD_INFO
    mov     fs,ebx
    mov     eax,4
    .WHILE (eax < dword ptr fs:[0])

        xor     ecx,ecx
        add     eax,4
        mov     cl,byte ptr fs:[eax]                                ; Get the length of the driver file name
        inc     eax
        add     eax,ecx
        mov     cl,byte ptr fs:[eax]                                ; Get the length of the driver's self-assigned name
        inc     eax
        add     eax,ecx
        mov     cl,byte ptr fs:[eax]                                ; Get the length of the version text
        inc     eax
        add     eax,ecx
        mov     cl,byte ptr fs:[eax]                                ; Get the length of the author text
        inc     eax
        add     eax,ecx
        mov     edi,eax

      ;
      ; Right now, fs:[edi] - far ptr to GDT offsets for:
      ;
      ;                     Offset  Length  Description             How to access
      ;                     ------  ------  --------------------    -------------------------------------
      ;                        0      4     code segment            to access (word ptr fs:[eax+0])
      ;                        4      4     data segment            to access (word ptr fs:[eax+4])
      ;                        8      4     main call gate          to access (call fword ptr fs:[eax+4])
      ;                        12     4     requestor, call gate    to access (call fword ptr fs:[eax+8])
      ;

      ; Physically call the primative
        push    eax

        xor     ebx,ebx
        mov     bx,word ptr fs:[eax+12]                             ; Modify the selector for this primative
        mov     esi,offset id_offset
        mov     word ptr es:[esi],bx
        mov     esi,offset prim_offset
        mov     word ptr es:[esi],bx
        mov     esi,offset note_offset
        mov     word ptr es:[esi],bx
        jmp     $+2                                                 ; Clear the prefetch cache (just in case)

        mov     eax,'prim'                                          ; requested primative function
        mov     ds,word ptr fs:[edi+4]                              ; this primative's permanent data segment
        mov     ebx,dword ptr fs:[edi+8]                            ; main() call gate
        mov     ecx,dword ptr fs:[edi+12]                           ; requestor() call gate
        xor     edx,edx
        xor     esi,esi
        xor     edi,edi
        xor     ebp,ebp
        mov     es,edx
        mov     fs,edx
        mov     gs,edx
;        call    invExtract_linear_offset_into_edx_from_ds
      ;
      ; Right now, eax - 'prim', indicating what requestor() function we're calling
      ;             bx - main() call gate
      ;             cx - requestor() call gate
      ;            edx - null
      ;            esi - null
      ;            edi - null
      ;            ebp - null
      ;             ds - permanent data segment for this primative
      ;             es - null
      ;             fs - null
      ;             gs - null
        db  9ah                     ; Call immed16:32
        dd  0                       ; Offset (the value here doesn't matter because we're calling a call gate)
      prim_offset:
        dw  0                       ; Selector (this part changes for each primative, see the code above (before jmp $+2))

      ; Right now, esi - offset to list of names to find
      ;            edi - offset to corresponding call gate area
        .IF (esi != 0ffffffffh)
          ; They have specified a list of primatives they need
            call    invUpdate_required_primatives
            .IF (carry?)
              ; Not all of them are available, we need to call the driver and tell them
                mov     eax,_sSYSTEM
                mov     fs,eax
                mov     eax,'note'
                mov     ebx,'prim'
                mov     ecx,dword ptr fs:[_SYSTEM_i_SCRATCH_DWORD1]     ; Total
                mov     ebp,dword ptr fs:[_SYSTEM_i_SCRATCH_DWORD2]     ; Number that weren't found
                xor     edx,edx
                xor     esi,esi
                xor     edi,edi
                mov     fs,edx
              ; Now, call the 'note' requestor function
                db  9ah             ; Call immed16:32
                dd  0               ; Offset (the value here doesn't matter because we're calling a call gate)
              note_offset:
                dw  0               ; Selector (this part changes for each primative, see the code above (before jmp $+2))

                .IF (carry?)
                  ; They've indicated this driver cannot continue without those primatives
                    call    init_failed
                .ENDIF
            .ENDIF

          ; Right now, everything's loaded OK.
            mov     ebx,_sPRIMATIVE_LOAD_INFO
            mov     fs,ebx
            mov     eax,dword ptr ss:[esp]                          ; Get our offset off the stack
            add     eax,16                                          ; And move to the next location to see WHERE IT'S AT! (Got 2 turn tables and a microphone...)
            push    ds
            pushad
            mov     esi,offset _VID_display_string_vga + 4
            .IF (eax < dword ptr fs:[0])
                mov     esi,offset next_item
            .ELSE
                mov     esi,offset last_item
            .ENDIF
            mov     eax,_sDATA
            mov     ds,eax
            .IF (ds:loading_primatives_displayed == _NO)
                mov     ds:loading_primatives_displayed,_YES
                pushad
                mov     esi,offset loading_primatives
                call    fword ptr cs:_VID_display_string_nr_vga
                popad
            .ENDIF
            call    fword ptr cs:_VID_display_string_vga
            popad
            pop     ds
          ; Ask the driver to identify itself on the VGA display
            mov     eax,'id  '
            db  9ah                 ; Call immed16:32
            dd  0                   ; Offset (the value here doesn't matter because we're calling a call gate)
          id_offset:
            dw  0                   ; Selector (this part changes for each primative, see the code above (before jmp $+2))

        .ENDIF

        pop     eax
      ; Reset the data segments for use in our procedure
        mov     ebx,_sDATA
        mov     es,ebx
        mov     ebx,_sPRIMATIVE_LOAD_INFO
        mov     fs,ebx

        add     eax,16
    .ENDW


  ; At this point, all of the requestor() functions have been setup for all drivers
  ; Now, it's time to call main() on each one of them
  ; Before we do that we need to setup Exodus's requestor() memory blocks
    mov     eax,_sEXODUS_MEM
    mov     ds,eax
    mov     dword ptr ds:[0],4                                      ; Starting location to write data for memory blocks
    mov     eax,_sEXODUS_PORTS
    mov     ds,eax
    mov     dword ptr ds:[0],4                                      ; Starting location to write data for port requests
    mov     eax,_sEXODUS_INTS
    mov     ds,eax
    mov     dword ptr ds:[0],4                                      ; Starting location to write data for interrupt requests

  ; Display the driver's name before we begin call main()
    mov     eax,_sDATA
    mov     ds,eax
    mov     esi,offset loading_drivers
    call    fword ptr cs:_VID_display_string_nr_vga

    mov     ebx,_sPRIMATIVE_LOAD_INFO
    mov     ds,ebx
    mov     eax,4
    mov     ebp,esp
    .WHILE (eax < dword ptr ds:[0])
        xor     ecx,ecx
        add     eax,4
        mov     cl,byte ptr ds:[eax]                                ; Get the length of the driver file name
        inc     eax
        add     eax,ecx
        mov     cl,byte ptr ds:[eax]                                ; Get the length of the driver's self-assigned name
        inc     eax
        mov     dword ptr ss:[ebp+48],eax                           ; Save for later use (below)
        mov     dword ptr ss:[ebp+52],ecx                           ; Save for later use (below)
        add     eax,ecx
        mov     cl,byte ptr ds:[eax]                                ; Get the length of the version text
        inc     eax
        mov     dword ptr ss:[ebp+56],eax                           ; Save for later use (below)
        mov     dword ptr ss:[ebp+60],ecx                           ; Save for later use (below)
        add     eax,ecx
        mov     cl,byte ptr ds:[eax]                                ; Get the length of the author text
        inc     eax
        add     eax,ecx
        mov     edi,eax
        push    eax

        xor     ebx,ebx
        mov     bx,word ptr fs:[eax+4]                              ; Get the data segment for this primative
        mov     dword ptr ss:[ebp+44],ebx
        mov     bx,word ptr fs:[eax+8]                              ; Get the main() selector for this primative
        mov     esi,offset main_offset
        mov     word ptr es:[esi],bx
      ;
      ; Right now,          ds - data segment for this primative's name in the _sPRIMATIVE_LOAD_INFO structure
      ;            ss:[ebp+48] - ptr to offset of driver's self-assigned name
      ;            ss:[ebp+52] - length of the name at that location
      ;
        add     edi,16
        .IF (edi < dword ptr ds:[0])
            mov     esi,offset next_item
        .ELSE
            mov     esi,offset last_item
        .ENDIF

        push    ds
        mov     eax,_sDATA
        mov     ds,eax
        call    fword ptr cs:_VID_display_string_vga
        pop     ds

      ; Display what the driver calls itself
        mov     esi,dword ptr ss:[ebp+48]
        mov     ecx,dword ptr ss:[ebp+52]
      ; This code removes anything that comes after the ASCII-255 (indicating not-displayed information)
        mov     eax,ecx
        .WHILE (eax > 0)
            .IF (byte ptr ds:[esi+eax-1] == 255)
                mov     ecx,eax
                dec     ecx
            .ENDIF
            dec     eax
        .ENDW
        .IF (ecx != 0 && ecx < 7fffffffh)
          ; Display the name
            call    fword ptr cs:_VID_display_string_ecx_vga

            push    ds
            mov     eax,_sDATA
            mov     ds,eax
            mov     esi,offset comma_space
            call    fword ptr cs:_VID_display_string_vga
            pop     ds
        .ENDIF

      ; Display the version information
        mov     esi,dword ptr ss:[ebp+56]
        mov     ecx,dword ptr ss:[ebp+60]
        call    fword ptr cs:_VID_display_string_ecx_nr_vga

        pushad
        push    ds
        push    es
        push    fs
        push    gs
        mov     ds,word ptr ss:[ebp+44]
        xor     ebp,ebp
        xor     eax,eax
        xor     ebx,ebx
        xor     ecx,ecx
        xor     edx,edx
        xor     esi,esi
        xor     edi,edi
        mov     es,eax
        mov     fs,eax
        mov     gs,eax
      ; Ok, we've displayed its name on the screen....
      ; Right now:  ds - The primative data segment
      ;             everything else is NULL
      ; Now, we let it initialize itself
        db  9ah                     ; Call immed16:32
        dd  0                       ; Offset (the value here doesn't matter because we're calling a call gate)
      main_offset:
        dw  0                       ; Selector (this part changes for each primative, see the code near "offset main_offset")
        pop     gs
        pop     fs
        pop     es
        pop     ds
        popad

        pop     eax
        add     eax,16
    .ENDW

    add     esp,68
    pop     ds
    pop     es
    pop     fs
    pop     gs
    ret
invSetup_native_primatives      ENDP




default_primative_response      PROC    NEAR
; This routine is called on any primative that has not been defined.
;
; * The primative call gates represent a range defined at the top of this program
;   Any primative call gate that has not been used by a defined function points to this routine
;   It returns the text "no support for primative" in the registers
;
    mov     eax,dword ptr cs:no_support_for_primative[00]
    mov     ebx,dword ptr cs:no_support_for_primative[04]
    mov     ecx,dword ptr cs:no_support_for_primative[08]
    mov     edx,dword ptr cs:no_support_for_primative[12]
    mov     esi,dword ptr cs:no_support_for_primative[16]
    mov     edi,dword ptr cs:no_support_for_primative[20]
    stc
    retf
default_primative_response      ENDP




invCopy_this_part   PROC    NEAR
; This routine is used to copy data from ds:[ebx] to fs:[edi]
;
; Upon entry:   ds:[ebx] - ptr to source string
;               fs:[edi] - ptr to destination string
;
; Upon exit:    ecx - number of bytes copied
;
    push    edx
    push    ecx
    push    ebx
    push    eax

    mov     edx,edi
    inc     edi
    xor     ecx,ecx
    .WHILE (byte ptr ds:[ebx] != 0)
        mov     al,byte ptr ds:[ebx]
        mov     byte ptr fs:[edi],al
        inc     ebx
        inc     edi
        inc     ecx
    .ENDW
    mov     byte ptr fs:[edx],cl

    pop     eax
    pop     ebx
    pop     ecx
    pop     edx
    ret
invCopy_this_part   ENDP




invMove_temp_gdts_to_permanent      PROC    NEAR
; This routine is used to copy the temporary primative GDT entries to their permanent location
;
; Upon entry:   eax - starting GDT offset to use
;               ecx - actual code segment/data segment length
;               _csTEMP_PRIMATIVE - defined as Code segment
;               _dsTEMP_PRIMATIVE - defined as Data segment
;          _cgTEMP_PRIMATIVE_MAIN - defined as call gate to main()
;     _cgTEMP_PRIMATIVE_REQUESTOR - defined as call gate to requestor()
;
; Upon exit:    _csTEMP_PRIMATIVE - copied to the next available location
;               _dsTEMP_PRIMATIVE - copied to the one after that
;                             eax - next GDT offset to use
;                                   * Note:  If the value in ebx != 0, then the limit of the
;
    push    edi
    push    ebx
    push    ds
    push    es
    push    fs
    push    gs

    mov     ebx,_sGDT
    mov     ds,ebx
    mov     ebx,_sSYSTEM
    mov     es,ebx
    mov     ebx,_sDATA
    mov     fs,ebx
    mov     ebx,_sSYSTEM
    mov     gs,ebx

  ; Copy the code segment
    mov     edi,_csTEMP_PRIMATIVE
    mov     ebx,dword ptr [edi]
    mov     dword ptr [eax],ebx
    mov     ebx,dword ptr [edi+4]
    mov     dword ptr [eax+4],ebx
  ; Derive the GDT information (to see if we need to adjust it)
    call    invExtract_code_descriptor32
;    .IF (ecx < edx)
;      ; We need to make the limit field shorter because they don't need all of the memory in the file
;        push    eax
;        shr     eax,3                                               ; Divide by 8
;        mov     edx,ecx                                             ; Decrease the limit to the value specified by requestor()
;        call    invCreate_code_descriptor32
;        pop     eax
;    .ENDIF
    mov     dword ptr gs:[_SYSTEM_i_CODE_GDT_OFFSET],eax
    add     eax,8

  ; Copy the data segment
    mov     edi,_dsTEMP_PRIMATIVE
    mov     ebx,dword ptr [edi]
    mov     dword ptr [eax],ebx
    mov     ebx,dword ptr [edi+4]
    mov     dword ptr [eax+4],ebx
    call    invExtract_data_descriptor32
;    .IF (ecx < edx)
;      ; We need to make the limit field shorter because they don't need all of the memory in the file
;        push    eax
;        shr     eax,3                                               ; Divide by 8
;        mov     edx,ecx                                             ; Decrease the limit to the value specified by requestor()
;        call    invCreate_data_descriptor32
;        pop     eax
;    .ENDIF
    mov     dword ptr gs:[_SYSTEM_i_DATA_GDT_OFFSET],eax
    add     eax,8

  ; Copy the main call gate
    mov     edi,_cgTEMP_PRIMATIVE_MAIN
    mov     ebx,dword ptr [edi]
    mov     dword ptr [eax],ebx
    mov     ebx,dword ptr [edi+4]
    mov     dword ptr [eax+4],ebx
    mov     dword ptr gs:[_SYSTEM_i_MAIN_GDT_OFFSET],eax
  ; Now, update the code segment selector for this newly located code segment (see above)
    mov     ebx,dword ptr gs:[_SYSTEM_i_CODE_GDT_OFFSET]
    mov     word ptr [eax+2],bx
    add     eax,8

  ; Copy the requestor call gate
    mov     edi,_cgTEMP_PRIMATIVE_REQUESTOR
    mov     ebx,dword ptr [edi]
    mov     dword ptr [eax],ebx
    mov     ebx,dword ptr [edi+4]
    mov     dword ptr [eax+4],ebx
    mov     dword ptr gs:[_SYSTEM_i_REQUESTOR_GDT_OFFSET],eax
  ; And, update this one's code selector also (see above)
    mov     ebx,dword ptr gs:[_SYSTEM_i_CODE_GDT_OFFSET]
    mov     word ptr [eax+2],bx
    add     eax,8

    pop     gs
    pop     fs
    pop     es
    pop     ds
    pop     ebx
    pop     edi
    ret
invMove_temp_gdts_to_permanent      ENDP




invAdd_primative    PROC    NEAR
; This routine is used to add a primative to the following items:
;   #1 - The _sPRIMATIVE structure
;   #2 - The GDT as a call gate
;
; Upon entry:        eax - GDT offset for this primative's call gate
;               ds:[esi] - far ptr to primative function name
;                     bx - dword to copy
;                    ecx - length
;                    edx - offset into the driver for this function
;                    ebp - Code segment for the driver this primative comes from
;
; Upon exit:    This routine is self contained
;               If control is returned to the calling function then it can be assumed that it is ok to continue
;               The data is added (or not added)
;
    pushad
    push    es

    .IF (eax < _MAX_PRIMATIVE*8)
      ; We're within the range for this primative
        mov     edi,_sPRIMATIVES
        mov     es,edi

        mov     edi,dword ptr es:[0]
        mov     word ptr es:[edi],ax                                ; store the call gate
        add     edi,2

        mov     byte ptr es:[edi],1                                 ; active? (0-No, 1-Yes)
        inc     edi

        mov     byte ptr es:[edi],cl                                ; length of the function name
        inc     edi

      ; Store the primative function name
      ; Right now, ds:[esi] - far ptr to their primative name
      ;            es:[edi] - far ptr to store it
      ;                 ecx - length of that name
        push    eax
        .REPEAT
            mov     al,byte ptr [esi]
            .IF (al >= "A" && al <= "Z")
                or      al,20h                                      ; force the name to lower-case
            .ENDIF
            inc     esi
            mov     byte ptr es:[edi],al
            inc     edi
        .UNTILCXZ
        pop     eax

      ; Update for the next location
        mov     dword ptr es:[0],edi

      ; Now, physically create the call gate to this primative
        mov     ecx,ebx                                             ; dwords to copy
        mov     ebx,edx                                             ; Offset to start of function
        mov     edx,ebp                                             ; Code segment
        shr     eax,3                                               ; Divide by 8 to get the GDT slot
        call    invCreate_call_gate_descriptor32
    .ENDIF

    pop     es
    popad
    ret
invAdd_primative    ENDP




invUpdate_required_primatives   PROC    NEAR
; This routine is used to update the required primatives required by a particular function
; * Refer to inf\
;
; Upon entry:   ds:[esi] - Offset to name structure of the required primatives
;               ds:[edi] - Offset to the start of the structure used for the call gates to assign to them
;
; Upon exit:    carry? - CLEAR=all functions were found (meaning they've already been installed)
;                          SET=error
;                              À ecx - number of functions not found
;
    pushad
    push    es
    push    fs
    enter   20,0
  ; [ebp-04] - dword, --Nuserved
  ; [ebp-08] - dword, current value of eax
  ; [ebp-12] - dword, current value of ecx for inner loop
  ; [ebp-16] - dword, current value of esi
  ; [ebp-20] - dword, curent value of ecx for outter loop
    mov     eax,_sPRIMATIVES
    mov     es,eax
    mov     eax,_sSYSTEM
    mov     fs,eax

    mov     dword ptr fs:[_SYSTEM_i_SCRATCH_DWORD1],0               ; Holds total number of primative names found
    mov     dword ptr fs:[_SYSTEM_i_SCRATCH_DWORD2],0               ; Holds total number not matched with installed primatives

    xor     ecx,ecx
    .WHILE (byte ptr ds:[esi] != 0ffh)
        mov     dword ptr ss:[ebp-16],esi
        mov     cl,byte ptr ds:[esi]
        mov     dword ptr ss:[ebp-20],ecx
        inc     dword ptr fs:[_SYSTEM_i_SCRATCH_DWORD1]

      ; Start at the beginning of the _sPRIMATIVE structure for each pass
        mov     eax,8
      ; Right now, es:[eax] - far ptr to start of primative's structure, refer to inf\primload.inf for information
        .WHILE (eax < dword ptr es:[0])
            mov     cl,byte ptr es:[eax+3]
            mov     dword ptr ss:[ebp-12],ecx
            mov     esi,dword ptr ss:[ebp-16]
            .IF (byte ptr es:[eax+2] == 1 && cl == byte ptr ds:[esi])
                mov     bx,word ptr es:[eax]                        ; Get the call gate
                mov     dword ptr ss:[ebp-08],eax
                add     eax,4
                inc     esi
              ; Right now, es:[eax] - far ptr to _sPRIMATIVE name
              ;            ds:[esi] - far ptr to current native primative name the application is requiring
              ;                 ecx - length
              ;                  bx - call gate for this primative
                .REPEAT
                    mov     dl,byte ptr ds:[esi]
                    .IF (dl >= 'A' && dl <= 'Z')
                        add     dl,020h                             ; force lowercase
                    .ENDIF
                    .IF (dl != byte ptr es:[eax])
                      ; It wasn't a match
                        jmp     @F
                    .ENDIF
                    inc     eax
                    inc     esi
                .UNTILCXZ
              ; If we're here, then this was a match
                mov     word ptr ds:[edi+4],bx
                jmp     next_primative

              @@:
                mov     ecx,dword ptr ss:[ebp-12]
                mov     eax,dword ptr ss:[ebp-08]
            .ENDIF
            add     eax,ecx
            add     eax,4
        .ENDW
      ; If we're here, then the item wasn't found
        mov     word ptr ds:[edi+4],0ffffh                          ; Set it so it will indicate it "wasn't found"
        inc     dword ptr fs:[_SYSTEM_i_SCRATCH_DWORD2]             ; Increase the number of items not found

      next_primative:
        mov     ecx,dword ptr ss:[ebp-20]
        mov     esi,dword ptr ss:[ebp-16]
        add     esi,ecx
        inc     esi
        add     edi,2
    .ENDW


    .IF (dword ptr fs:[_SYSTEM_i_SCRATCH_DWORD2] != 0)
        stc
    .ELSE
        clc
    .ENDIF

    leave
    pop     fs
    pop     es
    popad
    ret
invUpdate_required_primatives   ENDP




default_interrupt_handler32     PROC
; This is the default interrupt handler
; All IDT entries are initially setup to this in init16.asp
; invSetup_native_primatives updates those that are relevant to
    push    eax
    mov     al,20h
    out     20h,al
    pop     eax
    iretd
default_interrupt_handler32     ENDP




;VID_display_radix_in_edx_vga    PROC
;    pushad
;    push    ds
;    sub     esp,16                                                  ; Assume a maximum length of 12 chars (4 extra for boundary)
;    mov     ebp,esp
;
;    call    iString_generate_radix_string
;    call    VID_display_string_vga
;
;    add     esp,16
;    pop     ds
;    popad
;    ret
;VID_display_radix_in_edx_vga    ENDP




VID_display_radix_in_edx_mono   PROC
    pushad
    push    ds
    sub     esp,16                                                  ; Assume a maximum length of 12 chars (4 extra for boundry)
    mov     ebp,esp

    call    iString_generate_radix_string
    call    VID_display_string_mono

    add     esp,16
    pop     ds
    popad
    ret
VID_display_radix_in_edx_mono   ENDP




iString_generate_radix_string   PROC
    mov     byte ptr [ebp+12],0                                 ; NULL terminate the string we're building
    mov     esi,ebp
    add     esi,11
    mov     eax,edx
    and     ebx,0ffffh
  @@:
    xor     edx,edx
    div     ebx
    .IF (dl > 9)
        add     dl,'a'-10                                       ; Make it a letter if it's above 9 (10+ cannot be represented in 1 digit)
    .ELSE
        add     dl,'0'                                          ; Make it a number
    .ENDIF
    mov     byte ptr ss:[esi],dl
    dec     esi                                                 ; Decrement (move to next position to store data)
    cmp     esi,ebp
    jz      @F
    cmp     eax,0
    jnz     @B
  @@:
    push    ss
    pop     ds
    inc     esi                                                 ; Add back for the one we decremented above
  ; Right now, ds:[esi] - pointer to the value to display
    ret
iString_generate_radix_string   ENDP




;VID_display_string_vga    PROC
;; ds:[esi] - far pointer to null-terminated string
;;      edi - offset into video memory to write
;    pushad
;    push    es
;    push    fs
;
;    mov     eax,_sDATA
;    mov     es,eax
;    mov     eax,_sVGA
;    mov     fs,eax
;    mov     ah,7
;    .WHILE (byte ptr ds:[esi] != 0)                                 ; Loop until the NULL terminated string is found
;        lodsb
;        mov     byte ptr fs:[edi],al                                ; Write character
;        inc     di
;        mov     byte ptr fs:[edi],ah                                ; Write color
;        inc     di
;    .ENDW
;
;    pop     fs
;    pop     es
;    popad
;    ret
;VID_display_string_vga    ENDP




VID_display_string_mono   PROC
; ds:[esi] - far pointer to null-terminated string
;      edi - offset into video memory to write
    pushad
    push    es
    push    fs

    mov     eax,_sDATA
    mov     es,eax
    mov     eax,_sMONO
    mov     fs,eax
    mov     ah,7
    .WHILE (byte ptr ds:[esi] != 0)                                 ; Loop until the NULL terminated string is found
        lodsb
        mov     byte ptr fs:[edi],al                                ; Write character
        inc     di
        mov     byte ptr fs:[edi],ah                                ; Write color
        inc     di
    .ENDW

    pop     fs
    pop     es
    popad
    ret
VID_display_string_mono   ENDP




;VID_display_string_ecx_vga      PROC
;; ds:[esi] - far pointer to null-terminated string
;;      edi - offset into video memory to write
;;      ecx - count
;    pushad
;    push    es
;    push    fs
;
;    mov     eax,_sDATA
;    mov     es,eax
;    mov     eax,_sVGA
;    mov     fs,eax
;    mov     ah,7
;    .REPEAT
;        lodsb
;        mov     byte ptr fs:[edi],al                                ; Write character
;        inc     di
;        mov     byte ptr fs:[edi],ah                                ; Write color
;        inc     di
;    .UNTILCXZ
;
;    pop     fs
;    pop     es
;    popad
;    ret
;VID_display_string_ecx_vga      ENDP
;
;
;
;
VID_display_string_ecx_mono     PROC
; ds:[esi] - far pointer to null-terminated string
;      edi - offset into video memory to write
;      ecx - count
    pushad
    push    es
    push    fs

    .IF (ecx != 0)
        mov     eax,_sDATA
        mov     es,eax
        mov     eax,_sMONO
        mov     fs,eax
        mov     ah,7
        .REPEAT
            lodsb
            mov     byte ptr fs:[edi],al                                ; Write character
            inc     di
            mov     byte ptr fs:[edi],ah                                ; Write color
            inc     di
        .UNTILCXZ
    .ENDIF

    pop     fs
    pop     es
    popad
    ret
VID_display_string_ecx_mono     ENDP
;
;
;
;
;
VID_display_hex_string_ecx_mono     PROC
; ds:[esi] - far pointer to null-terminated string
;     ecx - number of hexidecimal digits to display
; offset_mono- pointer into the screen where to start writing
    pushad
    push    gs

    .IF (ecx != 0)
        mov     eax,_sMONO
        mov     gs,eax
        mov     ah,7
        .REPEAT
            lodsb
            mov     dl,al
            call    hex_adjust_al_dl
            mov     byte ptr gs:[edi],32                                ; Write a space before hexidecimal values
            inc     di
            mov     byte ptr gs:[edi],ah                                ; Write color
            inc     di
            mov     byte ptr gs:[edi],dl                                ; Write left 1/2 of hexidecimal values character
            inc     di
            mov     byte ptr gs:[edi],ah                                ; Write color
            inc     di
            mov     byte ptr gs:[edi],al                                ; Write right 1/2 of hexidecimal values character
            inc     di
            mov     byte ptr gs:[edi],ah                                ; Write color
            inc     di
            mov     byte ptr gs:[edi],32                                ; Write a space after hexidecimal value
            inc     di
            mov     byte ptr gs:[edi],ah                                ; Write color
            inc     di
        .UNTILCXZ
    .ENDIF

    pop     gs
    popad
    ret
VID_display_hex_string_ecx_mono     ENDP




hex_adjust_al_dl    PROC
    shr     dl,4
    .IF (dl <= 9)
        add     dl,'0'
    .ELSE
        add     dl,'a'-10
    .ENDIF
    and     al,0fh
    .IF (al <= 9)
        add     al,'0'
    .ELSE
        add     al,'a'-10
    .ENDIF
    ret
hex_adjust_al_dl    ENDP




init_failed     PROC    NEAR
; This routine returns to real mode and goes to a section of code that indicates a failed to boot message.
; It is called when Exodus is trying to boot up but received unexpected information from a device driver before VGA/keyboard
; support had been installed.
;
    mov     eax,_sVGA
    mov     fs,eax
    mov     eax,_sMONO
    mov     gs,eax
    mov     edi,6*80*2

    mov     esi,offset failed
    mov     ah,7
    .WHILE (esi < offset failed_end)
        mov     al,byte ptr cs:[esi]
        inc     esi
        .IF (al == 13)
          ; It's a carriage return
            add     edi,80*2
        .ELSEIF (al == 10)
          ; It's a line feed
            push    eax
            xor     edx,edx
            mov     eax,edi
            mov     ebx,80*2
            div     ebx
            mul     ebx
            mov     edi,eax
            pop     eax
        .ELSEIF (al == 'ô')
            mov     ah,112
        .ELSEIF (al == 'õ')
            mov     ah,7
        .ELSEIF (al == 'Ý')
            mov     ah,15
        .ELSEIF (al == 'Þ')
            mov     ah,7
        .ELSEIF (al == '¨')
            add     ah,128
        .ELSE
            mov     word ptr fs:[edi],ax
            mov     word ptr gs:[edi],ax
            add     edi,2
        .ENDIF
    .ENDW

  @@:
    hlt
    jmp     @B
init_failed     ENDP
