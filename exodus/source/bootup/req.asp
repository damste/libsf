; req.asp
;
; Exodus requestor()
; January 02, 2001
;
; * Refer to inf\requestr.inf for more information
; * The Exodus requestor call gate points here.  It is _sEXODUS_REQUESTOR
;
;  Functions:
;    À requestor                        ; Exodus's requestor function
;
;





requestor       PROC    NEAR
; This routine is responsible for all Exodus requestor functions
; Only FAR CALLS will be made to this routine
; * Refer to inf\requestr.inf for info on this function
; * Refer to inf\exodus.inf for info on the data structures used in memory regions _sEXODUS_MEM, _sEXODUS_PORTS and _sEXODUS_INTS
;
; Upon entry:   eax - requestor request
;             other - varies
;
; Upon exit:  varies based on input
;
  ; [ebp+08] - dword, cs
  ; [ebp+04] - dword, eip
  ; [ebp+00] - dword, ebp
    enter   20,0
  ; [ebp-04] - dword, --Nuserved                                    ; This space was reserved for future expansion
  ; [ebp-08] - dword, --Nuserved
  ; [ebp-12] - dword, --Nuserved
  ; [ebp-16] - dword, --Nuserved
  ; [ebp-20] - dword, --Nuserved
    push    fs
  ; [ebp-24] - dword, fs
    pushad
  ; [ebp-28] - dword, eax                                           ; These locations are noted in case some variables need
  ; [ebp-32] - dword, ecx                                           ; to be updated for the return
  ; [ebp-36] - dword, edx
  ; [ebp-40] - dword, ebx
  ; [ebp-44] - dword, esp
  ; [ebp-48] - dword, ebp
  ; [ebp-52] - dword, esi
  ; [ebp-56] - dword, edi

    .IF (eax == 'bmem')
      ; They're requesting a quantity of memory
      ; Upon entry: dl - action ÄÄÂ 0-free memory
      ;                           ³   À ebx - number of bytes requested
      ;                           Ã 1-allocate memory
      ;                           ³   À dx - previous selector
      ;                           À 2-make smaller
      ;                               Ã ebx - new number of bytes
      ;                               À dx - previous selector
      ; Upon exit:  carry? - SET if ERROR, CLEAR if OK
      ;                 dx - block selector if successful
      ;
        mov     ax,_sEXODUS_MEM
        mov     fs,ax
        mov     esi,4
        .IF (dl == 0)
          ; They want to free up a little memory, you know ... for old time's sake.
        .ELSEIF (dl == 1)
          ; They want a hunk of our precious memory ... so, what the hell ... we'll oblige
            .WHILE (esi < dword ptr fs:[0])
                mov     al,byte ptr fs:[esi]
                .IF (al == 0 && dword ptr fs:[esi+_EXODUS_MEM_limit] >= ebx)
                  ; This block is free and it's big enough
                  ; Update it with the new information
                    mov     edx,dword ptr ss:[ebp+08]               ; Get the calling code segment off the stack
                    mov     ecx,edx                                 ; Find out what PL it is
                    and     ecx,011b
                    .IF (dword ptr fs:[esi+_EXODUS_MEM_limit] == ebx)
                      ; They're exactly the same size
                        .IF (dx == _sCODE)
                          ; It's Exodus itself
                            mov     byte ptr fs:[esi+_EXODUS_MEM_type],1
                            mov     word ptr fs:[esi+_EXODUS_MEM_gdt],dx
                            clc
                        .ELSEIF (dx >= (_MIN_PRIMATIVE * 8) && dx <= (_MAX_PRIMATIVE * 8) && ecx == 0)
                          ; It's a native primative
                            mov     word ptr fs:[esi+_EXODUS_MEM_gdt],dx
                            push    ds
                            mov     cx,_sPRIMATIVES
                            mov     ds,cx
                            .IF (dword ptr ds:[4] < _MAX_PRIMATIVE)
                              ; We have room to add this into their memory space
                                mov     eax,dword ptr ds:[4]
                                inc     dword ptr ds:[4]                            ; Move to next call gate
                                mov     byte ptr fs:[esi+_EXODUS_MEM_type],2        ; This is a user application (primative)
                                mov     word ptr fs:[esi+_EXODUS_MEM_gdt],dx        ; Store their code segment
                                mov     word ptr fs:[esi+_EXODUS_MEM_ldt],ax        ; Store the GDT where this block will go
                              ; Right now, ebx - number of bytes requested
                              ;             ax - GDT slot where it will go
                                clc
                            .ELSE
                                stc
                            .ENDIF
                            pop     ds
                            jmp     requestor_quit
                        .ELSE
                          ; It's a user application
                            mov     word ptr fs:[esi+_EXODUS_MEM_gdt],dx
                          ; We have to add in the LDT of the calling program
;; REMEMBER
                        .ENDIF
                    .ELSE
                      ; It's bigger, so we have to update this one and add a new entry

                    .ENDIF
                  ; Create an entry in the user's LDT
                    clc
                    jmp     requestor_quit
                .ENDIF
                add     esi,_EXODUS_MEM_size
            .ENDW
          ; If we're here then there were no free memory blocks, or none of sufficient size (out of memory)

        .ELSEIF (dl == 2)
          ; They want to decrease a previously allocated block of memory

        .ELSE
          ; And now ... here they are on our doorstep asking for more.  The greedy little programs!
            stc
        .ENDIF
      ; If we're here, then there were some error
        stc
    .ELSEIF (eax == 'bprt')
      ; They're requesting exclusive access to a particular port (or range of ports)
      ; Upon entry: ebx - number of ports
      ;             edx - starting port
      ;
      ; Upon exit:  carry? - CLEAR=ok, SET=nope, can't have it
      ;
        mov     ax,_sEXODUS_PORTS
        mov     fs,ax
        mov     esi,4
        .WHILE (esi < dword ptr fs:[0])
            add     esi,_EXODUS_PORTS_size
        .ENDW
    .ELSEIF (eax == 'bint')
      ; They're requesting exclusive access to a particular interrupt (or range of interrupts)
      ; Upon entry:  bl - interrupt
      ;              cl - count
      ;             edx - offset to interrupt service routine
      ;
      ; Upon exit:  carry? - CLEAR=ok, SET=nope, can't have it
      ;
        mov     ax,_sEXODUS_INTS
        mov     fs,ax
        mov     esi,4

        mov     bh,bl
        add     bh,cl
        dec     bh
      ; Right now, bl - starting interrupt
      ;            bh - ending interrupt
        .WHILE (esi < dword ptr fs:[0])
            mov     ax,word ptr fs:[esi]
            mov     ch,ah
            dec     al
            add     ch,al
          ; Right now, ah - starting interrupt
          ;            ch - ending interrupt
            .IF ((bl >= ah && bl <= ch) || (bh >= ah && bh <= ch))
              ; This one is already used
                stc
                jmp     requestor_quit
            .ENDIF
            add     esi,_EXODUS_INTS_size
        .ENDW
        .IF (esi == _sEXODUS_INTS_limit)
          ; We're at the end
            stc
            jmp     requestor_quit
        .ENDIF
      ; If we're here, then it wasn't used.  We add it.
        mov     byte ptr fs:[esi],cl
        mov     byte ptr fs:[esi+1],bl

      ; Now, create the IDT entry(s)
        and     ecx,0ffh
      ; Right now,  bl - starting interrupt number
      ;            ecx - number of interrupts to intercept/keep
      ;            edx - offset to ISR
        mov     al,bl
        and     eax,0ffh
        mov     ebx,dword ptr ss:[ebp+08]
        .REPEAT
          ; Right now, eax - interrupt number to update
          ;            edx - offset to ISR
          ;             bx - selector to ISR
            call    invUpdate_interrupt_descriptor32
            inc     eax
        .UNTILCXZ
        clc
    .ELSEIF (eax == 'boot')
        .IF (ebx == 'logo')
            push    ds

            mov     eax,_sDATA
            mov     ds,eax
            mov     esi,offset bootscreen_start
            mov     ecx,offset bootscreen_end - bootscreen_start
            call    fword ptr cs:_VID_draw_exodus_boot_screen

            pop     ds
        .ENDIF
    .ELSEIF (eax == 'find' && edi == 'func')
      ; They want to find a function by it's call gate and an offset
      ;
      ; Upon entry:   edx - code segment
      ;               ebx - instruction pointer
      ;          ds:[esi] - far ptr where to store
      ;               ecx - maximum # of bytes to store
      ;
      ; Upon exit:    If found it's inserted, if not then it's not
      ;
      ; [ebp+12]+ (other parameters)
      ; [ebp+08] - cs
      ; [ebp+04] - eip
      ; [ebp+00] - ebp
        enter   20,0
      ; [ebp-04] - dword, edx at start
      ; [ebp-08] - dword, ebx at start
      ; [ebp-12] - dword, Last pointer to primative that was found
      ; [ebp-16] - dword, Distance from primative offset to ebx at start (indicates how far away from start of function it is)
      ; [ebp-20] - dword, ecx at start
        mov     dword ptr ss:[ebp-04],edx
        mov     dword ptr ss:[ebp-08],ebx
        mov     dword ptr ss:[ebp-12],0ffffffffh
        mov     dword ptr ss:[ebp-16],0ffffffffh
        mov     dword ptr ss:[ebp-20],ecx

        push    es
        mov     eax,_sDATA
        mov     es,ax
        mov     eax,edx
        and     eax,011b
        .IF (eax == 011b)
          ; It's a ring-3 application
;; REMEMBER
          ; Indicate it's an unknown user function
            mov     edi,offset unknown_user_function_text
            stc
            jmp     find_func_copy_text
        .ELSE
            .IF (edx >= _MIN_PRIMATIVE*8 && edx <= _MAX_PRIMATIVE*8)
                mov     eax,_sPRIMATIVES
                mov     fs,ax
                mov     edi,8                                       ; Start after this structure, see inf\primload.inf
                .WHILE (edi < dword ptr fs:[0])
                    .IF (byte ptr fs:[edi+2] == 1)
                      ; This one is active, lookup the GDT entry to determine the code selector and offset
                        movzx   eax,word ptr fs:[edi]               ; Get the GDT entry for this primative
                        call    invExtract_call_gate_descriptor32
                        .IF (edx == dword ptr ss:[ebp-04])
                          ; It's the right code segment, is it the right offset?
                            .IF (ebx <= dword ptr ss:[ebp-08])
                              ; It's before the current instruction pointer ... so it's a candidate
                                mov     ecx,dword ptr ss:[ebp-08]
                                sub     ecx,ebx
                                .IF (ecx < dword ptr ss:[ebp-16])
                                  ; We're closer than the previous one
                                    mov     dword ptr ss:[ebp-12],edi
                                    mov     dword ptr ss:[ebp-16],ecx
                                .ENDIF
                            .ENDIF
                        .ENDIF
                    .ENDIF
                    movzx   eax,byte ptr fs:[edi+3]
                    add     edi,eax
                    add     edi,4
                .ENDW
                .IF (dword ptr ss:[ebp-12] != 0ffffffffh)
                  ; We found something
                    mov     edi,dword ptr ss:[ebp-12]
                    movzx   ecx,byte ptr fs:[edi+3]
                    add     edi,4
                    mov     eax,dword ptr ss:[ebp-20]
                  ; Right now, fs:[edi] - far ptr to the name of this function
                  ;                 ecx - length of the function name
                  ;            ds:[esi] - far ptr to where we're supposed to store this name
                  ;                 eax - maximum # of characters ds:[esi] can hold
                    .IF (eax > 4)
                      ; Store the word " at "
                        mov     dword ptr ds:[esi],' ta '
                        add     esi,4
                        sub     eax,4
                    .ELSEIF (eax > 1)
                      ; Not enough room for the phrase " at ", so we just add a space and copy what we can
                        mov     byte ptr ds:[esi],32
                        inc     esi
                        dec     eax
                    .ENDIF
                  ; Now, copy the function name
                    .WHILE (byte ptr fs:[edi] != 0 && ecx > 0 && eax > 0)
                        mov     al,byte ptr fs:[edi]
                        mov     byte ptr ds:[esi],al
                        inc     esi
                        inc     edi
                        dec     ecx
                        dec     eax
                    .ENDW
                  ; Ok, right now the name has been copied
                    .IF (eax > 2)
                      ; Store the () part of a function()
                        mov     word ptr ds:[esi],')('
                        sub     eax,2
                        add     esi,2
                    .ENDIF
                    .IF (eax > 0)
                      ; We need to try to copy the offset
                        mov     byte ptr ds:[esi],"+"
                        inc     esi
                        dec     eax
                        .IF (eax > 0)
                          ; Now, copy the offset text to the string
                            mov     edx,dword ptr ss:[ebp-16]
                            mov     ecx,8
                          ; Skip past any leading 0s
                          @@:
                            rol     edx,4
                            mov     bl,dl
                            and     bl,0fh
                            .IF (bl != 0)
                                jmp     @F
                            .ENDIF
                            loop    @B
                            .IF (ecx == 0)
                              ; There are no values to store
                                mov     ecx,1
                            .ENDIF
                          ; Write the string
                          @@:
                            mov     bl,dl
                            and     bl,0fh
                            .IF (bl <= 9)                           ; Convert from ASCII to text, "0" to "9" or "a" to "f"
                                add     bl,'0'
                            .ELSE
                                add     bl,'a'-10
                            .ENDIF
                            mov     byte ptr ds:[esi],bl
                            inc     esi
                            dec     eax
                            .IF (eax == 0)
                                jmp     @F
                            .ENDIF
                            rol     edx,4
                            loop    @B
                          @@:
                        .ENDIF
                    .ENDIF
                    clc
                    jmp     find_func_quit
                .ELSE
                  ; We didn't find it
                    mov     edi,offset unknown_primative_text
                    stc
                    jmp     find_func_copy_text
                .ENDIF
            .ELSEIF (edx == _sCODE)
              ; It's Exodus itself!!!  WOAH!  This is bad.  We're not supposed to have any problems.  "It must be a human error."
                mov     edi,offset exodus_internal_text
                clc
              find_func_copy_text:
                pushfd
                .WHILE (byte ptr es:[edi] != 0 && ecx > 0)
                    mov     al,byte ptr es:[edi]
                    mov     byte ptr ds:[esi],al
                    inc     esi
                    inc     edi
                    dec     ecx
                .ENDW
                popfd
            .ELSE
              ; It's an unknown function
                mov     edi,offset unknown_function_text
                stc
                jmp     find_func_copy_text
            .ENDIF
        .ENDIF

      find_func_quit:
        pop     es
        leave
    .ELSEIF (eax == 'altr')
      ; They want to alter something
        .IF (ebx == 'gdt ')
          ; This function is used to alter the base/limit of a GDT entry
          ;
          ; Upon entry: edx - GDT slot
          ;             esi - new base
          ;             edi - new limit
          ;
          ; Upon exit:  carry? - clear if acceptable
          ;
            .IF (edx == _sVGA/8 && (esi == _sVGA_base || esi == _sVGA_BACKUP_base) && (edi == _sVGA_limit || edi == _sVGA_BACKUP_limit))
              ; It's the _sVGA, this one is acceptable to alter
                call    invAlter_descriptor32_base_limit
                clc
            .ELSE
              ; Unrecognized request
                stc
            .ENDIF
        .ELSE
          ; Unrecognized request
            stc
        .ENDIF
    .ELSEIF (eax == 'get ')
      ; They want to get some information about something
        .IF (ebx == 'gdtd')
          ; This function is used extract the base/limit of a data GDT entry
          ;
          ; Upon entry: edx - GDT slot
          ;
          ; Upon exit:  carry? - clear if acceptable
          ;             ebx - base
          ;             edx - limit
          ;
            test    dword ptr ss:[ebp+08],111b
            .IF (zero?)
              ; This function is only available to PL=00 tasks
                mov     eax,edx
                shl     eax,3
                call    invExtract_data_descriptor32
                mov     dword ptr ss:[ebp-40],ebx
                mov     dword ptr ss:[ebp-36],edx
                clc
            .ELSE
                stc
            .ENDIF

        .ELSEIF (ebx == 'gdtc')
          ; This function is used extract the base/limit of a code GDT entry
          ;
          ; Upon entry: edx - GDT slot
          ;
          ; Upon exit:  carry? - clear if acceptable
          ;             ebx - base
          ;             edx - limit
          ;
            test    dword ptr ss:[ebp+08],111b
            .IF (zero?)
              ; This function is only available to PL=00 tasks
                mov     eax,edx
                shl     eax,3
                call    invExtract_code_descriptor32
                mov     dword ptr ss:[ebp-40],ebx
                mov     dword ptr ss:[ebp-36],edx
                clc
            .ELSE
                stc
            .ENDIF

        .ELSEIF (ebx == 'gdt ')
          ; This function is used extract the quadword GDT entry
          ;
          ; Upon entry: edx - GDT slot
          ;
            test    dword ptr ss:[ebp+08],111b
            .IF (zero?)
                push    ds
                mov     eax,_sGDT
                mov     ds,eax
                mov     ebx,dword ptr ds:[edx*8+4]
                mov     edx,dword ptr ds:[edx*8+0]
                mov     dword ptr ss:[ebp-40],ebx
                mov     dword ptr ss:[ebp-36],edx
                pop     ds
                clc
            .ELSE
                stc
            .ENDIF

        .ELSEIF (ebx == 'tss ')
          ; This function is used extract the TSS base address from a CALL GATE GDT entry
          ;
          ; Upon entry: edx - call gate GDT slot
          ;
            test    dword ptr ss:[ebp+08],111b
            .IF (zero?)
                mov     eax,edx
                shl     eax,3
                call    invExtract_call_gate_descriptor32
                mov     eax,edx
                call    invExtract_data_descriptor32
                mov     dword ptr ss:[ebp-40],ebx
                clc
            .ELSE
                stc
            .ENDIF

        .ELSEIF (ebx == 'base')
          ; They want the base from an unknown selector (could be local, could be global)
          ;
          ; Upon entry: edx - offset in GDT
          ;
          ; Upon exit:  carry? - clear if found, set if not
          ;                ecx - base if found
          ;
            test dword ptr ss:[ebp+08],111b
            .IF (zero?)
                test dword ptr ss:[ebp-36],111b                     ; Check edx
                .IF (zero?)
                  ; It's a PL=00 descriptor
                    mov     eax,edx
                    call    invExtract_data_descriptor32
                    mov     dword ptr ss:[ebp-32],ebx               ; Store base in ecx
                    clc
                .ELSE
                  ; We have to find it the hard way
                .ENDIF
            .ELSE
                stc
            .ENDIF

        .ELSEIF (ebx == 'limi')
          ; They want the limit from an unknown selector (could be local, could be global)
          ;
          ; Upon entry: edx - offset in GDT
          ;
          ; Upon exit:  carry? - clear if found, set if not
          ;                ecx - limit if found
          ;
            test dword ptr ss:[ebp+08],111b
            .IF (zero?)
                test dword ptr ss:[ebp-36],111b                     ; Check edx
                .IF (zero?)
                  ; It's a PL=00 descriptor
                    mov     eax,edx
                    call    invExtract_data_descriptor32
                    mov     dword ptr ss:[ebp-32],edx               ; Store limit in ecx
                    clc
                .ELSE
                  ; We have to find it the hard way
                .ENDIF
            .ELSE
                stc
            .ENDIF

        .ELSE
          ; Unrecognized request
            stc
        .ENDIF
    .ELSEIF (eax == 'set ')
      ; They want to set some information about something
        .IF (ebx == 'gdtd')
          ; This function is used extract the base/limit of a data GDT entry
          ;
          ; Upon entry: edx - GDT slot
          ;             esi - base
          ;             edi - limit
          ;
          ; Upon exit:  carry? - clear if acceptable
          ;
            test    dword ptr ss:[ebp+08],111b
            .IF (zero?)
              ; This function is only available to PL=00 tasks
                .IF (edx == _sDEBI_temp/8)
                    mov     eax,edx
                    mov     ebx,esi
                    mov     edx,edi
                    call    invCreate_data_descriptor32
                .ENDIF
                clc
            .ELSE
                stc
            .ENDIF

        .ELSEIF (ebx == 'gdtc')
          ; This function is used extract the base/limit of a code GDT entry
          ;
          ; Upon entry: edx - GDT slot
          ;             esi - base
          ;             edi - limit
          ;
          ; Upon exit:  carry? - clear if acceptable
          ;
            test    dword ptr ss:[ebp+08],111b
            .IF (zero?)
              ; This function is only available to PL=00 tasks
                .IF (edx == _sDEBI_temp/8)
                    mov     eax,edx
                    mov     ebx,esi
                    mov     edx,edi
                    call    invCreate_code_descriptor32
                .ENDIF
                clc
            .ELSE
                stc
            .ENDIF

        .ELSE
          ; Unrecognized request
            stc
        .ENDIF
    .ELSEIF (eax == 'stop')
        .IF (ebx == 'load')
          ; An error occurred during initialization
          ;
          ; Upon entry: ds:[esi] - far ptr to null-terminated ID string to display
          ;
          ; Upon exit:  No exit. This routine locks up Debi
          ;
          ; Clear the screens for this message
          ; Mono
            mov     eax,_sMONO
            mov     es,eax
            mov     fs,eax
            xor     edi,edi
            mov     ecx,80*2*25 / 4
            xor     eax,eax
            rep     stosd

          ; VGA
            mov     eax,_sVGA
            mov     es,eax
            xor     edi,edi
            mov     ecx,80*2*25 / 4
            xor     eax,eax
            rep     stosd

          ; Store the name they've provided
            mov     ecx,80
            xor     edi,edi
            .REPEAT
                mov     al,byte ptr ds:[esi]
                .IF (al != 0 && ecx != 80)
                    inc     esi
                .ELSE
                    mov     al,32
                .ENDIF
                mov     byte ptr es:[edi],al                        ; VGA
                mov     byte ptr fs:[edi],al                        ; Mono
                inc     edi
                mov     al,112
                mov     byte ptr es:[edi],al
                mov     byte ptr fs:[edi],al
                inc     edi
            .UNTILCXZ

          ; Store the generic text
            mov     esi,offset failed
            mov     edi,80*2*5
            .WHILE (esi < offset failed_end)
                mov     al,byte ptr cs:[esi]
                inc     esi
                .IF (al == 13)
                  ; Move to start of current line
                    xor     edx,edx
                    mov     eax,edi
                    mov     ebx,80*2
                    div     ebx
                    mul     ebx
                    mov     edi,eax
                .ELSEIF (al == 10)
                  ; Move down one line
                    add     edi,80*2
                .ELSE
                    mov     byte ptr es:[edi],al
                    mov     byte ptr fs:[edi],al
                    inc     edi
                    mov     al,7
                    mov     byte ptr es:[edi],al
                    mov     byte ptr fs:[edi],al
                    inc     edi
                .ENDIF
            .ENDW

          ; Lock up the system
          @@:
            hlt
            jmp @B
        .ENDIF
    .ELSE
        stc
    .ENDIF

  requestor_quit:
    popad
    pop     fs
    leave
    retf
requestor       ENDP
