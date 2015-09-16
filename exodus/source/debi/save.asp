        .IF (cs:debi_count != 0)
          ; The system was already here in this debug section when we encountered another fault (double fault)
            call    DEBI_exception
        .ENDIF
    ;; Allow interrupts (we actually need them for Mouse and Keyboard)
        sti
    ;; Save all registers for display purposes
        push    ebx
        push    ecx
        push    edx
        push    edi
        push    ebp
        push    esp
        push    ds
        push    es
        push    fs
        push    gs
        mov     ebp,esp
        sub     esp,108
        fwait
        fnsave  ss:[ebp-108]

    ;; Clear the monochrome display
        call    fword ptr cs:_VID_clear_screen_mono

    ;; Display the text they want to show on the monochrome monitor, it goes on line 0
        mov     ax,_sMONO
        mov     es,ax                                                   ; Output goes to 0b0002h
        mov     edi,1*2

        mov     ax,_sDATA                                               ; Input comes from the
        mov     ds,ax
        mov     ds:debi_count,1                                         ; Raise the flag to indicate we're already here
        mov     ds:debi_mouse_pointer_update,0                          ; Lower the flag to force a mouse update first time through
        mov     ds:debi_udf_window_areas,0                              ; Initialize our count of things on the screen to 0
        mov     ds:debi_single_step,0
        mov     ds:debi_resume,0
        mov     ds:debi_busy,0                                          ; Lower the busy flag
        xor     ecx,ecx
      @@:
        lodsb                                                           ; Read a byte from the string
        or      al,al
        jz      @F
        stosb                                                           ; Store the byte
        mov     al,112                                                  ; Store the attribute
        stosb
        inc     ecx
        jmp     @B
      @@:
      ; Store the item at the top of the screen as the error message
        push    ebp
        sub     esp,48
        mov     ebp,esp
        mov     dword ptr ss:[ebp+04],1*2                               ; Starting location
        mov     dword ptr ss:[ebp+08],38*2                              ; Ending location on screen
        mov     dword ptr ss:[ebp+12],_sDATA                            ; Segment of text to display
        mov     dword ptr ss:[ebp+16],offset DEBI_text_1                ; Offset of text to display
        mov     dword ptr ss:[ebp+20],sizeof DEBI_text_1                ; Length of text to display
        mov     byte ptr ss:[ebp+24],0                                  ; Number of items following this one?
        mov     dword ptr ss:[ebp+00],05h                               ; Type of item we're adding (general, 5-raw_string)
        call    DEBI_object_stuff
        pop     ebp

    ; Display the debug information, it goes on lines 1 through 24
        xor     edi,edi                                                 ; Start at the upper-left most corner
        mov     esi,offset DEBI_debug_info_screen
        mov     ah,7
        xor     cl,cl
        .WHILE (byte ptr ds:[esi] != 0)
            lodsb
            .IF (al == '�')
                mov     ah,112
                jmp     @F
            .ELSEIF (al == '�')
                mov     ah,7
                jmp     @F
            .ELSEIF (al == 255)
                add     edi,(16*(80*2))
                jmp     @F
            .ELSEIF (al == '�')
                mov     cl,al
                jmp     @F
            .ELSEIF (al == '�')
                mov     cl,al
                jmp     @F
            .ENDIF
            .IF (cl == '�')
                inc     edi
            .ELSE
                stosb
            .ENDIF
            mov     byte ptr es:[edi],ah
            inc     edi
          @@:
        .ENDW

    ;; Now, populate the screen with fixed information
    ;; Instruction stream
        push    ds
        mov     edx,dword ptr ss:[ebp+64]
        mov     ds,dx
        mov     esi,dword ptr ss:[ebp+60]
      ; Display the address
        mov     edi,(1*(80*2)) + (21*2)
        xor     ebx,ebx
        call    DEBI_reg16                                              ; cs
        mov     edi,(1*(80*2)) + (26*2)
        xor     ebx,ebx
        mov     edx,esi
        call    DEBI_reg32                                              ; eip
      ; Display the bytes
        sub     esi,16                                                  ; Where to start displaying
        mov     edi,(2*(80*2)) + (6*2)
        xor     ebx,ebx
        mov     ecx,16
        call    DEBI_hex_string_exp
        mov     edi,(3*(80*2)) + (6*2)
        xor     ebx,ebx
        mov     ecx,16
        call    DEBI_hex_string_exp
        mov     edi,(4*(80*2)) + (6*2)
        xor     ebx,ebx
        mov     ecx,16
        call    DEBI_hex_string_exp
        pop     ds

    ;; cs:eip, cr0 and cr4
        mov     edx,dword ptr ss:[ebp+64]                               ; cs
        mov     edi,(2*(80*2)) + (62*2)
        xor     ebx,ebx
        call    DEBI_reg16
        mov     edx,dword ptr ss:[ebp+60]                               ; eip
        mov     edi,(3*(80*2)) + (58*2)
        xor     ebx,ebx
        call    DEBI_reg32

        mov     edx,cr0                                                 ; cr0
        mov     edi,(2*(80*2)) + (72*2)
        xor     ebx,ebx
        call    DEBI_reg32

        db      0fh, 20h, 11100010b                                     ; cr4, this is "mov edx,cr4", stupid MASM won't compile it
        mov     edi,(3*(80*2)) + (72*2)
        xor     ebx,ebx
        call    DEBI_reg32
      ; Display the flags
        mov     eax,cr0
        xor     ebx,ebx
      ; ne - Numeric exception
        mov     edi,(4*(80*2)) + (70*2)
        mov     edx,eax
        shr     edx,_CR0_NE + 1
        call    DEBI_flag_up_down
      ; ts - Task switch has occurred sicne last use of FPU/MMX?
        mov     ebx,(4*(80*2)) + (74*2)
        mov     edx,eax
        shr     edx,_CR0_TS + 1
        call    DEBI_flag_up_down
      ; vme - Virtual mode extensions
        db      0fh, 20h, 11100000b                                     ; cr4, this is "mov eax,cr4", stupid MASM won't compile it
        mov     ebx,(4*(80*2)) + (66*2)
        mov     edx,eax
        shr     edx,_CR4_VME + 1
        call    DEBI_flag_up_down
      ; de - Debug extensions
        mov     ebx,(4*(80*2)) + (78*2)
        mov     edx,eax
        shr     edx,_CR4_DE + 1
        call    DEBI_flag_up_down

    ;; Now, populate the screen with user-defined windows of information
        mov     esi,offset DEBI_screen_format
        mov     edi,5*(80*2)
        xor     ecx,ecx
        .WHILE (ecx < 4)
            push    ecx
            push    esi

            mov     al,byte ptr cs:[esi]                                ; Get the type of window to display here
            .IF (al == 1)
              ; GDT/IDT display
                call    DEBI_gdt_idt
            .ELSEIF (al == 2)
              ; FPU registers
                call    DEBI_fpu_box
            .ELSEIF (al == 3)
              ; disassembly
                call    DEBI_disasm
            .ELSEIF (al == 4)
              ; stack
                call    DEBI_stack
            .ELSEIF (al == 5)
              ; GP registers display
                call    DEBI_registers
            .ELSEIF (al == 6)
              ; Stack and memory
                call    DEBI_stack_mem
            .ENDIF
            .IF (edi > 20*(80*2))
                mov     edi,5*(80*2) + 40*2
            .ENDIF

            pop     esi
            inc     esi                                                 ; Move to the next window data
            pop     ecx
            inc     ecx                                                 ; Increase the window count (we stop at 4)
        .ENDW
        call    DEBI_update_mouse_pointer

    ;; This is an object oriented system.
    ;; All tasks are handled via interrupt.
    ;; So, we wait in a tight loop.
    ;; -------------------------
    ;; Oh Sheila!  Oh Sheila!
    ;; It's your birthday!  It's your birthday!
    ;; -------------------------
      @@:
        hlt                                                             ; Wait for an interrupt
        .IF (cs:debi_busy == 0)                                         ; (before proceeding in an unadulterated manner)
          ; If we're here, then Debi is not currently processing an interrupt or doing something else
            .IF (cs:debi_single_step == 1)
              ; They've decided to continue via a single step, baby!
    ;            or      dword ptr ss:[ebp+68],1 shl (_EFLAGS_TF-1)      ; Turn on the "trap flag"
                or      dword ptr ss:[ebp+68],100000000b
            .ELSEIF (cs:debi_resume == 1)
              ; They are continuing from here
                or      dword ptr ss:[ebp+68],not 100000000b
            .ELSE
                jmp     @B
            .ENDIF
        .ELSE
          ; If we're here, Debi is busy ... we wait.  Note, we should not have to wait long, just until the next interrupt
          ; (which should be, at most, 1/182 of a second because the timer is there)
            jmp     @B
        .ENDIF

    ;; Clear the mono screen
        call    fword ptr cs:_VID_clear_screen_mono

    ;; Lower all the internal Debi flags
        mov     ax,_sDATA                                               ; Input comes from the
        mov     ds,ax
        mov     ds:debi_count,0                                         ; Raise the flag to indicate we're already here

    ;; Restore the FPU state to its previous state of glory
        fwait
        frstor  ss:[ebp-108]

    ;; Lower the task-switched flag
        clts

    ;; Get back the stack pointer (get back, Jo Jo!)
        mov     esp,ebp

    ;; Get the saved registers off the stack
        pop     gs
        pop     fs
        pop     es
        pop     ds
        pop     esp
        pop     ebp
        pop     edi
        pop     edx
        pop     ecx
        pop     ebx



    DEBI_gdt_idt     PROC
    ; This routine is used to display the GDT/IDT window
    ;
    ;; Display the GDT/IDT screen
        push    ds
        mov     si,_sDATA
        mov     ds,si
        mov     esi,offset DEBI_debug_gdt_idt
        mov     byte ptr ds:[esi+2],"G"                                 ; Default to GDT window
        call    DEBI_draw_window

    ;; Display the GDT value for the represented offset (default to 8)
      ; Display the offset
        mov     edx,8
        mov     ebx,(8*2)
        call    DEBI_reg32
      ; Display the data
        mov     si,_sGDT
        mov     ds,si
        mov     esi,8
        mov     edx,dword ptr ds:[esi]                                  ; Get the lower 4 bytes of the GDT
        mov     ebx,(4*(80*2)) + (1*2)
        call    DEBI_binary32_expanded

        mov     edx,dword ptr ds:[esi+4]                                ; Get the upper 4 bytes of the GDT
        mov     ebx,(3*(80*2)) + (1*2)
        call    DEBI_binary32_expanded

        add     edi,9*(80*2)                                            ; Move down the screen for the next portion
        pop     ds
        ret
    DEBI_gdt_idt    ENDP






    DEBI_disasm      PROC
    ; This routine is used to display the disassembly window
    ; Upon entry:  ss:[ebp+64] - cs
    ;              ss:[ebp+60] - eip
    ;
        push    es
        push    fs
        push    gs
        push    edi
        push    edx

    ;; Display the disassembly screen
        mov     esi,offset DEBI_debug_disasm
        call    DEBI_draw_window

    ;; Display the address
        mov     edx,dword ptr ss:[ebp+64]
        mov     ebx,(14*2)
        call    DEBI_reg16                                              ; cs

        mov     edx,dword ptr ss:[ebp+60]
        mov     ebx,(19*2)
        call    DEBI_reg32                                              ; eip

    ;; Show the disassembly
        mov     edx,edi                                                 ; For this portion only, gs acts like es, edx acts as edi

        mov     di,_sMONO                                               ;   and ebx is in its normal use
        mov     gs,di

        mov     di,_sDATA                                               ; Data segment into FS
        mov     es,di
        mov     fs,di

        push    ds
        mov     ds,word ptr ss:[ebp+64]                                 ; ds:[esi] = source of the cs:eip fault
        mov     esi,dword ptr ss:[ebp+60]
        mov     ebx,(1*(80*2))                                          ; Start at one line down, left-justified
        mov     ecx,6
        mov     ah,112                                                  ; Color to use
        .REPEAT
            push    ecx
            mov     edi,offset DEBI_instruction_output                  ; Store the instruction text to this variable
            call    DEBI_generate_disassembly                           ; Let's do it!
            mov     ecx,39
            call    DEBI_raw_string                                     ; Show the generated text
            add     ebx,(1*(80*2))
            pop     ecx
            mov     ah,15                                               ; Color to use
        .UNTILCXZ
        pop     ds

    ;; We're finished
        pop     edx
        pop     edi
        pop     gs
        pop     fs
        pop     es

    ;; Move down the screen for the next portion
        add     edi,7*(80*2)
        ret
    DEBI_disasm     ENDP

    ; * Note:  This DEBI_generate_disassembly() routine is a fairly large routine.  It is in its own editable file
        INCLUDE DEBI_dis.asp




    DEBI_stack       PROC
    ; This routine is used to display the general purpose register window
    ;
    ;; Display the stack register screen
        mov     esi,offset DEBI_debug_stack
        call    DEBI_draw_window

    ;; Display the stack values
      ; Display the address
      ; Segment
        xor     edx,edx
        mov     dx,ss
        mov     ebx,(8*2)
        call    DEBI_reg16
      ; Offset
        mov     edx,ebp                                                 ; See note below *
        add     edx,68
        mov     ebx,(13*2)
        call    DEBI_reg32

      ; Display the memory there
        mov     esi,72                                                  ; * This takes us passed the values that have been placed on
                                                                        ;   the stack due to the exception/trap taking place
        mov     ecx,16                                                  ; We're doing this for 16 entries (if we can)
        mov     ebx,(8*(80*2)) + (20*2)                                 ; Starting point in the window (near the lower-right corner)
        jmp     @F
        .WHILE (ecx > 0 && edx <= 77fch)
            push    ecx

            push    ebx
            mov     edx,dword ptr ss:[ebp+esi]
            call    DEBI_reg32_expanded
            add     esi,4                                               ; Move to the next item on the stack
            pop     ebx
            sub     ebx,(1*(80*2))                                      ; Move up one line on the screen
            .IF (ebx < (1*(80*2)))
              ; We're to the top of the column
                mov     ebx,(8*(80*2)) + (1*2)                          ; Starting point in the left column
            .ENDIF

            pop     ecx
            dec     ecx
          @@:
            mov     edx,ebp
            add     edx,esi
        .ENDW

        add     edi,9*(80*2)                                            ; Move down the screen for the next portion
        ret
    DEBI_stack       ENDP




    DEBI_stack_mem   PROC
    ; This routine is used to display the general purpose register window
    ;

    ;; Display the stack/memory screen
        mov     esi,offset DEBI_debug_stack_mem
        call    DEBI_draw_window

    ;; Display the stack values
        mov     esi,72                                                  ; This takes us passed the values that have been placed on
                                                                        ;   the stack due to the exception/trap taking place
        mov     ecx,8                                                   ; We're doing this for 8 entries (if we can)
        mov     ebx,(8*(80*2)) + (1*2)                                  ; Starting point in the window (near the lower-right corner)
        jmp     @F
        .WHILE (ecx > 0 && edx <= 77fch)
            push    ecx

            push    ebx
            mov     edx,dword ptr ss:[ebp+esi]
            call    DEBI_reg32_expanded
            add     esi,4                                               ; Move to the next item on the stack
            pop     ebx
            sub     ebx,(1*(80*2))                                      ; Move up one line on the screen

            pop     ecx
            dec     ecx
          @@:
            mov     edx,ebp
            add     edx,esi
        .ENDW

    ;; Display the memory values
      ; Display the address
        xor     edx,edx
        mov     ebx,(23*2)
        call    DEBI_reg32
      ; Display the memory there
        push    fs
        mov     bx,_sALL_MEM
        mov     fs,bx
        xor     esi,esi                                                 ; This takes us passed the values that have been placed on
                                                                        ;   the stack due to the exception/trap taking place
        mov     ecx,8                                                   ; We're doing this for 8 entries
        mov     ebx,(8*(80*2)) + (20*2)                                 ; Starting point in the window (near the lower-right corner)
        .REPEAT
            push    ecx

            push    ebx
            mov     edx,dword ptr fs:[esi]
            call    DEBI_reg32_expanded
            add     esi,4                                               ; Move to the next item on the stack
            pop     ebx
            sub     ebx,(1*(80*2))                                      ; Move up one line on the screen

            pop     ecx
        .UNTILCXZ
        pop     fs

        add     edi,9*(80*2)                                            ; Move down the screen for the next portion
        ret
    DEBI_stack_mem   ENDP




    DEBI_registers   PROC
    ; This routine is used to display the general purpose register window
    ;
    ;; Display the general purpose register screen
        mov     esi,offset DEBI_debug_registers
        call    DEBI_draw_window

    ;; Display left-column (general purpose registers)
        mov     edx,dword ptr ss:[ebp+52]                               ; eax
        mov     ebx,(1*(80*2)) + (5*2)
        call    DEBI_reg32
        mov     edx,dword ptr ss:[ebp+36]                               ; ebx
        mov     ebx,(2*(80*2)) + (5*2)
        call    DEBI_reg32
        mov     edx,dword ptr ss:[ebp+32]                               ; ecx
        mov     ebx,(3*(80*2)) + (5*2)
        call    DEBI_reg32
        mov     edx,dword ptr ss:[ebp+28]                               ; edx
        mov     ebx,(4*(80*2)) + (5*2)
        call    DEBI_reg32
        mov     edx,dword ptr ss:[ebp+44]                               ; esi
        mov     ebx,(5*(80*2)) + (5*2)
        call    DEBI_reg32
        mov     edx,dword ptr ss:[ebp+24]                               ; edi
        mov     ebx,(6*(80*2)) + (5*2)
        call    DEBI_reg32

    ;; Display middle-column (flags and stack)
        mov     edx,dword ptr ss:[ebp+68]                               ; eflags
        mov     ebx,(1*(80*2)) + (31*2)
        call    DEBI_reg32
      ; Do the eflags that we're visually indicating
        mov     eax,dword ptr ss:[ebp+68]
      ; nt
        mov     ebx,(2*(80*2)) + (28*2)
        mov     edx,eax
        shr     edx,_EFLAGS_NT + 1
        call    DEBI_flag_up_down
      ; of
        mov     ebx,(2*(80*2)) + (33*2)
        mov     edx,eax
        shr     edx,_EFLAGS_OF + 1
        call    DEBI_flag_up_down
      ; acf
        mov     ebx,(2*(80*2)) + (38*2)
        mov     edx,eax
        shr     edx,_EFLAGS_ACF + 1
        call    DEBI_flag_up_down
      ; pf
        mov     ebx,(3*(80*2)) + (28*2)
        mov     edx,eax
        shr     edx,_EFLAGS_PF + 1
        call    DEBI_flag_up_down
      ; sf
        mov     ebx,(3*(80*2)) + (33*2)
        mov     edx,eax
        shr     edx,_EFLAGS_SF + 1
        call    DEBI_flag_up_down
      ; if
        mov     ebx,(3*(80*2)) + (38*2)
        mov     edx,eax
        shr     edx,_EFLAGS_IF + 1
        call    DEBI_flag_up_down
      ; df
        mov     ebx,(4*(80*2)) + (28*2)
        mov     edx,eax
        shr     edx,_EFLAGS_DF + 1
        call    DEBI_flag_up_down
      ; zf
        mov     ebx,(4*(80*2)) + (33*2)
        mov     edx,eax
        shr     edx,_EFLAGS_ZF + 1
        call    DEBI_flag_up_down
      ; cf
        mov     ebx,(4*(80*2)) + (38*2)
        mov     edx,eax
        shr     edx,_EFLAGS_CF + 1
        call    DEBI_flag_up_down

    ;; Display right-column (segment registers)
        mov     edx,dword ptr ss:[ebp+12]                               ; ds
        mov     ebx,(1*(80*2)) + (18*2)
        call    DEBI_reg16
        mov     edx,dword ptr ss:[ebp+8]                                ; es
        mov     ebx,(2*(80*2)) + (18*2)
        call    DEBI_reg16
        mov     edx,dword ptr ss:[ebp+4]                                ; fs
        mov     ebx,(3*(80*2)) + (18*2)
        call    DEBI_reg16
        mov     edx,dword ptr ss:[ebp+0]                                ; gs
        mov     ebx,(4*(80*2)) + (18*2)
        call    DEBI_reg16

    ;; Stack related
        xor     edx,edx
        mov     dx,ss                                                   ; ss
        mov     ebx,(6*(80*2)) + (18*2)
        call    DEBI_reg16
        mov     edx,dword ptr ss:[ebp+20]                               ; ebp
        mov     ebx,(5*(80*2)) + (29*2)
        call    DEBI_reg32
        mov     edx,ebp                                                 ; esp
        add     edx,72
        mov     ebx,(6*(80*2)) + (29*2)
        call    DEBI_reg32

        add     edi,7*(80*2)                                            ; Move down the screen for the next portion
        ret
    DEBI_registers   ENDP




    DEBI_fpu_box     PROC
    ; This routine is used to display the general purpose register window
    ;

    ;; Display the fpu screen
        mov     esi,offset DEBI_debug_fpu
        call    DEBI_draw_window

    ;; Display the FPU registers
        push    ds                                                      ; Save ds
        push    ss                                                      ; Get ss into ds
        pop     ds
        mov     esi,ebp                                                 ; st0
        sub     esi,108-28
        mov     ebx,(1*(80*2)) + (4*2)
        mov     ecx,10
        call    DEBI_hex_string

        mov     ebx,(2*(80*2)) + (4*2)                                  ; st1
        mov     ecx,10
        call    DEBI_hex_string

        mov     ebx,(3*(80*2)) + (4*2)                                  ; st2
        mov     ecx,10
        call    DEBI_hex_string

        mov     ebx,(4*(80*2)) + (4*2)                                  ; st3
        mov     ecx,10
        call    DEBI_hex_string

        mov     ebx,(5*(80*2)) + (4*2)                                  ; st4
        mov     ecx,10
        call    DEBI_hex_string

        mov     ebx,(6*(80*2)) + (4*2)                                  ; st5
        mov     ecx,10
        call    DEBI_hex_string

        mov     ebx,(7*(80*2)) + (4*2)                                  ; st6
        mov     ecx,10
        call    DEBI_hex_string

        mov     ebx,(8*(80*2)) + (4*2)                                  ; st7
        mov     ecx,10
        call    DEBI_hex_string
        pop     ds                                                      ; Restore ds

        mov     edx,dword ptr ss:[ebp-108+0]                            ; Control word
        mov     ebx,(1*(80*2)) + (29*2)
        call    DEBI_reg32

        mov     edx,dword ptr ss:[ebp-108+4]                            ; Status word
        mov     ebx,(2*(80*2)) + (29*2)
        call    DEBI_reg32

        mov     edx,dword ptr ss:[ebp-108+8]                            ; Tag word
        mov     ebx,(3*(80*2)) + (29*2)
        call    DEBI_reg32

        mov     edx,dword ptr ss:[ebp-108+16]                           ; fcs
        mov     ebx,(5*(80*2)) + (30*2)
        call    DEBI_reg32

        mov     edx,dword ptr ss:[ebp-108+12]                           ; feip
        mov     ebx,(6*(80*2)) + (30*2)
        call    DEBI_reg32

        mov     edx,dword ptr ss:[ebp-108+24]                           ; fds
        mov     ebx,(7*(80*2)) + (30*2)
        call    DEBI_reg32

        mov     edx,dword ptr ss:[ebp-108+20]                           ; fesi
        mov     ebx,(8*(80*2)) + (30*2)
        call    DEBI_reg32

        add     edi,9*(80*2)                                            ; Move down the screen for the next portion
        ret
    DEBI_fpu_box     ENDP




    DEBI_draw_window     PROC
    ; This routine is used to draw one of the four user-definable windows in the main Debi screen
    ; Upon entry:   edi - offset into video memory for upper-left portion of window
    ;               esi - offset in memory for the source screen
        push    ebx
        push    edi

        mov     ebx,edi                                                 ; Save value (used to increment when ASCII-255 is found)
        mov     ah,7                                                    ; Default to color 7
        .WHILE (byte ptr cs:[esi] != 0 && edi < 21*(80*2))
            lodsb
            .IF (al == '�')
              ; Highlight on
                mov     ah,112
            .ELSEIF (al == '�')
              ; Highlight off
                mov     ah,7
            .ELSEIF (al == 255)
              ; Go to next line
                mov     edi,ebx
                add     edi,80*2
                mov     ebx,edi
            .ELSE
              ; Store it
                stosb
                mov     byte ptr es:[edi],ah
                inc     edi
            .ENDIF
        .ENDW

        pop     edi
        pop     ebx
        ret
    DEBI_draw_window     ENDP




    DEBI_reg16   PROC
    ; Displays all hexidecimal nibbles in the dx register, outputs to es:[edi]
        push    ebp
        sub     esp,48
        mov     ebp,esp
        mov     dword ptr ss:[ebp+04],edi                               ; Starting location
        add     dword ptr ss:[ebp+04],ebx
        mov     dword ptr ss:[ebp+08],edi                               ; Ending location on screen
        add     dword ptr ss:[ebp+08],ebx
        add     dword ptr ss:[ebp+08],3*2
        mov     word ptr ss:[ebp+12],dx                                 ; Word value to store
        mov     byte ptr ss:[ebp+01],0                                  ; Number of items following this one?
        mov     dword ptr ss:[ebp+00],01h                               ; Type of item we're adding (general, 1-word value)
        call    DEBI_object_stuff
        pop     ebp

        mov     ecx,4
      @@:
        rol     dx,4
        mov     al,dl
        and     al,0fh
        call    hex_adjust_al
        mov     byte ptr es:[edi+ebx],al
        inc     ebx
        mov     byte ptr es:[edi+ebx],15
        inc     ebx
        loop    @B
        ret
    DEBI_reg16   ENDP




    DEBI_reg32   PROC
    ; Displays all hexidecimal nibbles in the edx register, outputs to es:[edi]
        push    ebp
        sub     esp,48
        mov     ebp,esp
        mov     dword ptr ss:[ebp+04],edi                               ; Starting location
        add     dword ptr ss:[ebp+04],ebx
        mov     dword ptr ss:[ebp+08],edi                               ; Ending location on screen
        add     dword ptr ss:[ebp+08],ebx
        add     dword ptr ss:[ebp+08],7*2
        mov     dword ptr ss:[ebp+12],edx                               ; Word value to store
        mov     byte ptr ss:[ebp+01],0                                  ; Number of items following this one?
        mov     dword ptr ss:[ebp+00],02h                               ; Type of item we're adding (general, 1-word value)
        call    DEBI_object_stuff
        pop     ebp

        mov     ecx,8
      @@:
        rol     edx,4
        mov     al,dl
        and     al,0fh
        call    hex_adjust_al
        mov     byte ptr es:[edi+ebx],al
        inc     ebx
        mov     byte ptr es:[edi+ebx],15
        inc     ebx
        loop    @B

        ret
    DEBI_reg32   ENDP




    DEBI_reg32_expanded      PROC
    ; Displays all hexidecimal nibbles in the edx register, outputs to es:[edi]
        push    ebp
        sub     esp,48
        mov     ebp,esp
        mov     dword ptr ss:[ebp+04],edi                               ; Starting location
        add     dword ptr ss:[ebp+04],ebx
        mov     dword ptr ss:[ebp+08],edi                               ; Ending location on screen
        add     dword ptr ss:[ebp+08],ebx
        add     dword ptr ss:[ebp+08],10*2
        mov     dword ptr ss:[ebp+12],edx                               ; Word value to store
        mov     byte ptr ss:[ebp+01],0                                  ; Number of items following this one?
        mov     dword ptr ss:[ebp+00],11                                ; Type of item we're adding (general, 11-reg32 expanded)
        call    DEBI_object_stuff
        pop     ebp

        mov     ecx,8
      @@:
        rol     edx,4                                                   ; Move the upper nibble into the lower nibble of dl
        mov     al,dl                                                   ; Print the nibble
        and     al,0fh
        call    hex_adjust_al
        mov     byte ptr es:[edi+ebx],al
        inc     ebx
        mov     byte ptr es:[edi+ebx],15
        inc     ebx                                                     ; Move to the next nibble

        mov     eax,ecx
        shr     eax,1
        .IF (carry?)
            mov     byte ptr es:[edi+ebx],32                            ; Show a leading space every other nibble
            inc     ebx
            mov     byte ptr es:[edi+ebx],7
            inc     ebx
        .ENDIF

        loop    @B
        ret
    DEBI_reg32_expanded      ENDP




    DEBI_binary32_expanded       PROC
    ; Displays all binary digits in a 32-bit number in this format:
    ;       �������� �������� �������� ��������
    ;
        push    ebp
        sub     esp,48
        mov     ebp,esp
        mov     dword ptr ss:[ebp+04],edi                               ; Starting location
        add     dword ptr ss:[ebp+04],ebx
        mov     dword ptr ss:[ebp+08],edi                               ; Ending location on screen
        add     dword ptr ss:[ebp+08],ebx
        add     dword ptr ss:[ebp+08],34*2
        mov     dword ptr ss:[ebp+12],edx                               ; Word value to store
        mov     byte ptr ss:[ebp+01],0                                  ; Number of items following this one?
        mov     dword ptr ss:[ebp+00],07h                               ; Type of item we're adding (general, 7-binary32 expanded)
        call    DEBI_object_stuff
        pop     ebp

        mov     ecx,4                                                   ; Do it for 4 bytes
      outer_loop:
        push    ecx
        mov     ecx,8                                                   ; 8 bits per byte
          inner_loop:
            rcl     edx,1                                               ; Move the upper nibble into the lower nibble of dl
            .IF (carry?)
                mov     al,'�'
            .ELSE
                mov     al,'�'
            .ENDIF
            mov     byte ptr es:[edi+ebx],al
            inc     ebx
            mov     byte ptr es:[edi+ebx],15
            inc     ebx                                                 ; Move to the next nibble
            loop    inner_loop

        pop     ecx
        mov     byte ptr es:[edi+ebx],32                                ; Show a trailing space every other byte (8 bits)
        inc     ebx
        mov     byte ptr es:[edi+ebx],7
        inc     ebx
        loop    outer_loop

        ret
    DEBI_binary32_expanded       ENDP




    DEBI_hex_string  PROC
    ; Displays all hexidecimal nibbles in pointed to by ds:[esi] for ecx characters, outputs to es:[edi]
    ; It reads a byte at a time and then displays the high order nibble first, then the low order
    ; Upon entry:   ds:[esi] - far ptr to string to display
    ;                    ecx - length of string
    ;
        push    edx
        push    ebp
        sub     esp,48
        mov     ebp,esp
        mov     dword ptr ss:[ebp+04],edi                               ; Starting location
        add     dword ptr ss:[ebp+04],ebx
        mov     dword ptr ss:[ebp+08],edi                               ; Ending location on screen
        add     dword ptr ss:[ebp+08],ebx
        mov     edx,ecx
        shl     edx,2
        dec     edx                                                     ; Change base-1 to base-0
        add     dword ptr ss:[ebp+08],edx
        mov     word ptr ss:[ebp+12],ds
        mov     dword ptr ss:[ebp+16],esi
        mov     dword ptr ss:[ebp+20],ecx
        mov     byte ptr ss:[ebp+01],0                                  ; Number of items following this one?
        mov     dword ptr ss:[ebp+00],03h                               ; Type of item we're adding (general, 3-hex_string)
        call    DEBI_object_stuff
        pop     ebp
        pop     edx

      ; * Note, string is displayed backwards (MSB on left side, LSB on right)
        add     esi,ecx
        push    esi
        dec     esi
      outer_loop:
        push    ecx
        mov     al,byte ptr ds:[esi]
        ror     al,4                                                    ; Swap nibbles
        mov     ah,al                                                   ; Save for later

            mov     ecx,2
          inner_loop:
            and     al,0fh                                              ; Display this nibble
            call    hex_adjust_al
            mov     byte ptr es:[edi+ebx],al
            inc     ebx
            mov     byte ptr es:[edi+ebx],15
            inc     ebx
            mov     al,ah                                               ; Get the next nibble
            ror     al,4
            loop    inner_loop

        pop     ecx
        dec     esi
        loop    outer_loop

        pop     esi
        ret
    DEBI_hex_string  ENDP




    DEBI_raw_string  PROC
    ; Displays all bytes pointed to by es:[edi] for ecx characters, outputs to gs:[edx+ebx]
    ; It reads a byte at a time and then displays the high order nibble first, then the low order
    ; Upon entry:   es:[edi] - far ptr to string to display
    ;                    ecx - length of string
    ;                     ah - Color to display in
    ;
        push    edi
        push    ebx
        push    eax

        .REPEAT
            mov     al,byte ptr es:[edi]                                ; Read the byte and
            mov     byte ptr es:[edi],' '                               ;   clear the buffer simultaneously
            inc     edi                                                 ; Move to the next location
            mov     word ptr gs:[edx+ebx],ax
            add     ebx,2
        .UNTILCXZ

        pop     eax
        pop     ebx
        pop     edi
        ret
    DEBI_raw_string  ENDP




    DEBI_hex_string_exp      PROC
    ; Displays all hexidecimal nibbles in pointed to by ds:[esi] for ecx characters, outputs to es:[edi]
    ; It reads a byte at a time and then displays the high order nibble first, then the low order
    ; Upon entry:   ds:[esi] - far ptr to string to display
    ;                    ecx - length of string
    ;
        push    edx
        push    ebp
        sub     esp,48
        mov     ebp,esp
        mov     dword ptr ss:[ebp+04],edi                               ; Starting location
        add     dword ptr ss:[ebp+04],ebx
        mov     dword ptr ss:[ebp+08],edi                               ; Ending location on screen
        add     dword ptr ss:[ebp+08],ebx
        mov     edx,ecx
        dec     edx
        shl     edx,1
        add     edx,ecx
        shl     edx,1
        add     dword ptr ss:[ebp+08],edx
        mov     word ptr ss:[ebp+12],ds
        mov     dword ptr ss:[ebp+16],esi
        mov     dword ptr ss:[ebp+20],ecx
        mov     byte ptr ss:[ebp+01],0                                  ; Number of items following this one?
        mov     dword ptr ss:[ebp+00],04h                               ; Type of item we're adding (general, 3-hex_string expanded)
        call    DEBI_object_stuff
        pop     ebp
        pop     edx

      ; Note, string is displayed forward (LSB on left-side, MSB on right)
      outer_loop:
        push    ecx
        mov     al,byte ptr ds:[esi]
        ror     al,4                                                    ; Swap nibbles
        mov     ah,al                                                   ; Save for later

            mov     ecx,2
          inner_loop:
            and     al,0fh                                              ; Display this nibble
            call    hex_adjust_al
            mov     byte ptr es:[edi+ebx],al
            inc     ebx
            mov     byte ptr es:[edi+ebx],15
            inc     ebx
            mov     al,ah                                               ; Get the next nibble
            ror     al,4
            loop    inner_loop

        mov     word ptr es:[edi+ebx],0720h                             ; Display a trailing space after each byte
        add     ebx,2
        pop     ecx
        inc     esi
        loop    outer_loop

        ret
    DEBI_hex_string_exp      ENDP




    DEBI_flag_up_down    PROC
    ; This routine is used to display the  and  arrows for given flags conditions
    ; Upon entry:  carry? - set, clear
    ;
        push    eax
        setc    ah
        pushfd
        push    ebp
        sub     esp,48
        mov     ebp,esp
        mov     dword ptr ss:[ebp+04],edi                               ; Starting location
        add     dword ptr ss:[ebp+04],ebx
        sub     dword ptr ss:[ebp+04],2*2
        mov     dword ptr ss:[ebp+08],edi                               ; Ending location on screen
        add     dword ptr ss:[ebp+08],ebx
        mov     byte ptr ss:[ebp+12],ah                                 ; Store the value of the FLAG
        mov     byte ptr ss:[ebp+01],0                                  ; Number of items following this one?
        mov     dword ptr ss:[ebp+00],06h                               ; Type of item we're adding (general, 6-flag value)
        call    DEBI_object_stuff
        pop     ebp
        popfd

        .IF (carry?)
          ; Up arrow
            mov     word ptr es:[edi+ebx],0f18h
        .ELSE
          ; Down arrow
            mov     word ptr es:[edi+ebx],0719h
        .ENDIF
        pop     eax
        ret
    DEBI_flag_up_down    ENDP




    mouse_offset            dd  0
    mouse_bytes             db  3 dup(0)
    mouse_intercept_busy    db  0

    DEBI_mouse_intercept     PROC
    ; This routine is the mouse intercept during debugging routines
    ; It utilizes the monochrome monitor and updates a mouse pointer on the screen
    ; It also contains a mini object oriented section of code which allows the person using the debugger the ability to view different
    ; types of information in different ways just by moving the mouse pointer over it.
    ;
        pushad
        push    ds
        mov     bx,_sDATA
        mov     ds,bx
        inc     ds:debi_busy                                            ; Raise the busy flag
        mov     ebx,ds:mouse_offset

    ;; Store the byte from the mouse
        mov     byte ptr ds:mouse_bytes[ebx],al
        inc     ds:mouse_offset
        .IF (ds:mouse_offset >= 3)
            mov     ds:mouse_offset,0                                   ; Reset our pointer for the next bit of mouse info

          ; If we're not already busy, process this packet, otherwise we ignore it
          ;   (used for slow PCs that might not be able to complete all processing before the next mouse packet is received)
            .IF (ds:mouse_intercept_busy == 0)
                mov     ds:mouse_intercept_busy,1                       ; Mark it as busy
    ;; We've received a full packet.  It's time to decipher its meaning.
                mov     al,byte ptr ds:mouse_bytes[0]
                mov     ah,al
                shr     al,5                                            ; al = X sign
                shr     ah,6                                            ; ah = Y sign
                xor     ecx,ecx
                xor     edx,edx
                mov     cl,byte ptr ds:mouse_bytes[1]                   ; X distance
                mov     dl,byte ptr ds:mouse_bytes[2]                   ; Y distance
                neg     dl
                .IF (cl <= 07fh)
                  ; We're adding X
                    add     ds:debi_mouse_x_counter,ecx
                .ELSE
                  ; We're subtracting X
                    neg     cl
                    sub     ds:debi_mouse_x_counter,ecx
                .ENDIF
                .IF (dl <= 07fh)
                  ; We're adding Y
                    add     ds:debi_mouse_y_counter,edx
                .ELSE
                  ; We're adding Y
                    neg     dl
                    sub     ds:debi_mouse_y_counter,edx
                .ENDIF

              ; Now, see if we're beyond the threshold for movement

    ;; Update the X mouse coordinate
              ; Horizontal takes 2 counts before it moves 1 character
                .IF (ds:debi_mouse_x_counter >= 0f0000000h)
                  ; It's a negative value, so we add positive
                    mov     ebx,ds:debi_mouse_x_counter
                    neg     ebx
                    mov     edx,2
                    mov     cl,-1
                .ELSE
                  ; It's a positive value, so we add negative
                    mov     ebx,ds:debi_mouse_x_counter
                    mov     edx,-2
                    mov     cl,1
                .ENDIF
              ; We might need to move a little
                mov     esi,ebx
                .WHILE (((ds:debi_mouse_x > 0 && cl == -1) || (ds:debi_mouse_x < 79 && cl == 1)) && ebx >= 2)
                    add     ds:debi_mouse_x,cl
                    add     ds:debi_mouse_x_counter,edx
                    mov     ds:debi_mouse_pointer_update,1
                    sub     ebx,2
                .ENDW
                .IF ((ds:debi_mouse_x == 0 || ds:debi_mouse_x == 79) && esi >= 2)
                    mov     ds:debi_mouse_x_counter,0
                .ENDIF

    ;; Update the Y mouse coordinate
              ; Vertical takes 4 counts before it moves 1 character
                .IF (ds:debi_mouse_y_counter >= 0f0000000h)
                  ; It's a negative value, so we add positive
                    mov     ebx,ds:debi_mouse_y_counter
                    neg     ebx
                    mov     edx,4
                    mov     cl,-1
                .ELSE
                  ; It's a positive value, so we add negative
                    mov     ebx,ds:debi_mouse_y_counter
                    mov     edx,-4
                    mov     cl,1
                .ENDIF
              ; We might need to move a little
                mov     esi,ebx
                .WHILE (((ds:debi_mouse_y > 0 && cl == -1) || (ds:debi_mouse_y < 24 && cl == 1)) && ebx >= 4)
                    add     ds:debi_mouse_y,cl
                    add     ds:debi_mouse_y_counter,edx
                    mov     ds:debi_mouse_pointer_update,1
                    sub     ebx,4
                .ENDW
                .IF ((ds:debi_mouse_y == 0 || ds:debi_mouse_y == 24) && esi >= 4)
                    mov     ds:debi_mouse_y_counter,0
                .ENDIF

    ;; If the coordinates have changed, we need to update if necessary
                .IF (ds:debi_mouse_pointer_update == 1)
                  ; * Note:  The "debi_mouse_pointer_update" variable will only be !0 when either the X or Y coordinate have changed
                    mov     ds:debi_mouse_pointer_update,0
                    call    DEBI_update_mouse_pointer
                .ENDIF
                mov     ds:mouse_intercept_busy,0                       ; We're no longer busy! :)
            .ENDIF
        .ENDIF
        dec     ds:debi_busy                                            ; Lower the busy flag
        pop     ds
        popad
        ret
    DEBI_mouse_intercept     ENDP




    DEBI_update_mouse_pointer    PROC
    ; This routine physically updates the mouse pointer on the screen
        pushad
        push    ds
        push    es
        push    fs

        mov     ax,_sDATA
        mov     ds,ax
        mov     ax,_sMONO
        mov     es,ax
        mov     ax,_sxDEBUG
        mov     fs,ax

        xor     eax,eax                                                 ;
        mov     al,ds:debi_mouse_y_last                                 ;
        mov     ebx,160                                                 ;
        mul     ebx                                                     ;
        xor     edx,edx                                                 ;
        mov     dl,ds:debi_mouse_x_last                                 ;
        shl     edx,1                                                   ; Remove the old mouse pointer
        add     eax,edx                                                 ;
        mov     edi,eax                                                 ;
        mov     al,ds:debi_color_last                                   ;
        mov     byte ptr es:[edi+1],al                                  ;

      ; See if we're at a location where we need to update the display
        mov     ebx,ds:debi_udf_window_areas
        shl     ebx,4                                                   ; Multiply by 16 to get offset
        xor     esi,esi
        mov     dh,ds:debi_mouse_x
        mov     dl,ds:debi_mouse_y
        mov     edi,(22*(80*2)) + (38*2)
        .WHILE (esi < ebx)
            mov     ax,word ptr fs:[esi+1]
            mov     cx,word ptr fs:[esi+3]
            .IF (dh >= ah && dh <= ch && dl >= al && dl <= cl)
              ; This is a match
                call    DEBI_object_unhighlight_last_area
                call    DEBI_object_highlight_new_area
                call    DEBI_object_show
                jmp     @F
            .ENDIF
            add     esi,16
        .ENDW
      ; Nothing was found, unhighlight the last item
        call    DEBI_object_unhighlight_last_area
        mov     ds:highlight_last_point1,0
        mov     ds:highlight_last_point2,0
      @@:

        xor     eax,eax                                                 ;
        mov     al,ds:debi_mouse_y                                      ;
        mov     ds:debi_mouse_y_last,al                                 ;
        mov     ebx,160                                                 ;
        mul     ebx                                                     ;
        xor     edx,edx                                                 ;
        mov     dl,ds:debi_mouse_x                                      ;
        mov     ds:debi_mouse_x_last,dl                                 ;
        shl     edx,1                                                   ;
        add     eax,edx                                                 ; Add the new one
        mov     edi,eax                                                 ;
        mov     al,byte ptr es:[edi+1]                                  ;
        mov     ds:debi_color_last,al                                   ;
        .IF (al >= 112)                                                 ;
            mov     byte ptr es:[edi+1],7                               ;
        .ELSE                                                           ;
            mov     byte ptr es:[edi+1],112                             ;
        .ENDIF                                                          ;

        pop     fs
        pop     es
        pop     ds
        popad
        ret
    DEBI_update_mouse_pointer    ENDP




    DEBI_object_stuff    PROC
    ; This routine is used to stuff an object into the UDF memory areas
    ; It will be used (when the mouse pointer passes over an item) to display additional information for the user
    ; Upon entry:   DEBI_udf_window_areas = how many items have already been stored
    ;               48 bytes are on the stack for this procedure
    ;               ss:[ebp+00] - BYTE, Object type
    ;               ss:[ebp+01] - BYTE, Number of items that follow
    ;               ss:[ebp+02] - WORD, Nuserved
    ;               ss:[ebp+04] - DWORD, starting offset on screen
    ;               ss:[ebp+08] - DWORD, ending offset on screen
    ;               other - (depends on type, see each item below)
    ;
        pushad
        push    es
        push    fs

      ; Setup the local data segments
        mov     ax,_sDATA
        mov     fs,ax
        mov     ax,_sxDEBUG
        mov     es,ax

      ; Calculate the starting offset to store this object
        mov     esi,fs:debi_udf_window_areas
        shl     esi,4                                                   ; Multiply by 16 to get offset

      ; Starting offset into screen
        mov     ebx,dword ptr ss:[ebp+04]
        call    DEBI_calculate_x_y
        mov     word ptr es:[esi+01],bx

      ; Ending offset into screen
        mov     ebx,dword ptr ss:[ebp+08]
        call    DEBI_calculate_x_y
        mov     word ptr es:[esi+03],bx

      ; Number of items that follow
        mov     bl,byte ptr ss:[ebp+01]                                 ; Additional information?
        mov     byte ptr es:[esi+5],bl
      ; Store the object type and store relevant data
        mov     dl,byte ptr ss:[ebp+00]
        mov     byte ptr es:[esi+00],dl
        .IF (dl == 0)
          ; BYTE (reg8)
          ; [ebp+12] - byte value to display
            mov     bl,byte ptr ss:[ebp+12]                            ; Word value
            mov     byte ptr es:[esi+6],bl
        .ELSEIF (dl == 1)
          ; WORD (reg16)
          ; [ebp+12] - word value to display
            mov     bx,word ptr ss:[ebp+12]                             ; Word value
            mov     word ptr es:[esi+6],bx
        .ELSEIF (dl == 2 || dl == 7 || dl == 8 || dl == 11)
          ; 02 = DWORD (reg32)
          ; 07 = BINARY (binary32 value)
          ; 08 = FLOAT32 (float32 value)
          ; 0b = REG32 expanded (reg3_exp)
          ; [ebp+12] - dword value to display
            mov     ebx,dword ptr ss:[ebp+12]                           ; Dword/float32 value
            mov     dword ptr es:[esi+6],ebx
        .ELSEIF (dl == 3 || dl == 4 || dl == 5)
          ; 03 = STRING (hex_string)
          ; 04 = STRING (hex_string_expanded)
          ; 05 = STRING (raw_string)
          ; [ebp+12] - segment of text to display
          ; [ebp+16] - offset of text to display
          ; [ebp+20] - length of text to display
            mov     ebx,dword ptr ss:[ebp+12]                           ; Text segment
            mov     word ptr es:[esi+6],bx
            mov     ebx,dword ptr ss:[ebp+16]                           ; Text offset
            mov     dword ptr es:[esi+8],ebx
            mov     ebx,dword ptr ss:[ebp+20]                           ; Length offset
            mov     word ptr es:[esi+12],bx
        .ELSEIF (dl == 6)
          ; FLAG? (flag? value)
            mov     bl,byte ptr ss:[ebp+12]                             ; FLAG value
            mov     byte ptr es:[esi+6],bl
        .ELSEIF (dl == 9)
          ; FLOAT64 (float64 value)
          ; [ebp+12] - qword value to display
            mov     ebx,dword ptr ss:[ebp+12]                           ; Low 32-bit dword of the 64-bit qword
            mov     dword ptr es:[esi+6],ebx
            mov     ebx,dword ptr ss:[ebp+16]                           ; High 32-bit dword
            mov     dword ptr es:[esi+10],ebx
        .ELSEIF (dl == 10)
          ; FLOAT80 (float80 value)
          ; [ebp+12] - tbyte value to display
            mov     ebx,dword ptr ss:[ebp+12]                           ; Low 32-bit dword of the 80-bit tbyte
            mov     dword ptr es:[esi+6],ebx
            mov     ebx,dword ptr ss:[ebp+16]                           ; Middle 32-bit dword
            mov     dword ptr es:[esi+10],ebx
            mov     bx,word ptr ss:[ebp+20]                             ; High 16-bit word
            mov     word ptr es:[esi+14],bx
        .ELSE
          ; Unknown option
            jmp     @F
        .ENDIF
        inc     fs:debi_udf_window_areas

      @@:
        pop     fs
        pop     es
        popad
        ret     48
    DEBI_object_stuff    ENDP





    DEBI_object_show     PROC
    ; This routine is used to stuff an object into the UDF memory areas
    ; It will be used (when the mouse pointer passes over an item) to display additional information for the user
    ; Upon entry:  fs:[esi] - far ptr to object
    ;                    es - MONO segment
    ;                    ds - DATA segment
    ;
        pushad

        mov     ds:last_object_segment,fs
        mov     ax,fs
        mov     ds:last_object_offset,esi
        .IF (ax != 0)
    ;; Update the window with the relavent information for this object type
            mov     al,byte ptr fs:[esi]
            .IF (al == 0)
              ; reg8
                mov     esi,offset infobox_byte
                call    DEBI_clear_info_box
            .ELSEIF (al == 1)
              ; reg16
                mov     esi,offset infobox_word
                call    DEBI_clear_info_box
            .ELSEIF (al == 2)
              ; reg32
                .IF (cs:intercept_key_alt != 0)
                  ; ALT key is depressed
                    mov     esi,offset infobox_dworda
                .ELSEIF (cs:intercept_key_ctrl != 0)
                  ; CTRL key is depressed
                    mov     esi,offset infobox_dwordc
                .ELSE
                    mov     esi,offset infobox_dword
                .ENDIF
                call    DEBI_clear_info_box
            .ELSEIF (al == 3)
              ; hex string
                mov     esi,offset infobox_clear
                call    DEBI_clear_info_box
            .ELSEIF (al == 4)
              ; hex string expanded
                mov     esi,offset infobox_clear
                call    DEBI_clear_info_box
            .ELSEIF (al == 5)
              ; hex string raw
                mov     esi,offset infobox_clear
                call    DEBI_clear_info_box
            .ELSEIF (al == 6)
              ; flat
                mov     esi,offset infobox_flag
                call    DEBI_clear_info_box
            .ELSEIF (al == 7)
              ; bin32
                mov     esi,offset infobox_bin32
                call    DEBI_clear_info_box
            .ELSEIF (al == 8)
              ; float32
                .IF (cs:intercept_key_alt != 0)
                  ; ALT key is depressed
                    mov     esi,offset infobox_f32a
                .ELSE
                    mov     esi,offset infobox_f32
                .ENDIF
                call    DEBI_clear_info_box
            .ELSEIF (al == 9)
              ; float64
                .IF (cs:intercept_key_alt != 0)
                  ; ALT key is depressed
                    mov     esi,offset infobox_f64a
                .ELSE
                    mov     esi,offset infobox_f64
                .ENDIF
                call    DEBI_clear_info_box
            .ELSEIF (al == 10)
              ; float80
                .IF (cs:intercept_key_alt != 0)
                  ; ALT key is depressed
                    mov     esi,offset infobox_f80a
                .ELSE
                    mov     esi,offset infobox_f80
                .ENDIF
                call    DEBI_clear_info_box
            .ELSEIF (al == 11)
              ; reg32 expanded
                .IF (cs:intercept_key_alt != 0)
                  ; ALT key is depressed
                    mov     esi,offset infobox_reg32a
                .ELSEIF (cs:intercept_key_ctrl != 0)
                  ; CTRL key is depressed
                    mov     esi,offset infobox_reg32c
                .ELSE
                    mov     esi,offset infobox_reg32
                .ENDIF
                call    DEBI_clear_info_box
            .ENDIF
        .ENDIF

        popad
        ret
    DEBI_object_show     ENDP




    DEBI_clear_info_box      PROC
    ; This routine clears off the InfoBox
    ; Upon entry:  cs:[esi] - far ptr to box to draw
    ; Upon exit:  The box is cleared
    ;
    ;; HERE
        pushad
        push    es

        mov     bx,_sMONO
        mov     es,bx
        mov     edi,(21*(80*2)) + (20*2)                                ; Starting part of window on-screen
        xor     ebx,ebx
        mov     ecx,4
        mov     ah,07h
      outer_loop:
        push    ecx
        push    ebx

            mov     ecx,60                                              ; 60 characters across the window
          inner_loop:
            mov     al,byte ptr cs:[esi]
            inc     esi
            or      al,al
            jz      done_inner_loop
            cmp     al,1
            jz      clear_and_move_to_next_line_1                       ; Clear to end of line with the � (ASCII 196) character
            cmp     al,255
            jz      clear_and_move_to_next_line_2                       ; Clear to end of line with spaces
            .IF (al >= 2 && al <= 18)
                jmp     insert_text
            .ENDIF
            .IF (al == '�')
                mov     ah,112
                jmp     inner_loop                                      ; These codes don't count against our 60 characters
            .ELSEIF (al == '�' || al == '�')
                mov     ah,07
                jmp     inner_loop
            .ELSEIF (al == '�')
                mov     ah,15
                jmp     inner_loop
            .ENDIF
            mov     word ptr es:[edi+ebx],ax
            add     ebx,2
          @@:
            loop    inner_loop
            jmp     done_inner_loop

          clear_and_move_to_next_line_1:
            mov     al,'�'
            jmp     clear_and_move_to_next_line
          clear_and_move_to_next_line_2:
            mov     al,20h

          clear_and_move_to_next_line:
            .REPEAT
                mov     word ptr es:[edi+ebx],ax
                add     ebx,2
            .UNTILCXZ
            jmp     done_inner_loop

          insert_text:
            push    esi
            cmp     al,2
            jz      insert_text_and_move_to_next_line_2
            cmp     al,3
            jz      insert_text_and_move_to_next_line_3
            cmp     al,4
            jz      insert_text_and_move_to_next_line_4
            cmp     al,5
            jz      insert_text_and_move_to_next_line_5
            cmp     al,6
            jz      insert_text_and_move_to_next_line_6
            cmp     al,7
            jz      insert_text_and_move_to_next_line_7
            cmp     al,8
            jz      insert_text_and_move_to_next_line_8
            cmp     al,9
            jz      insert_text_and_move_to_next_line_9
            cmp     al,10
            jz      insert_text_and_move_to_next_line_10
            cmp     al,11
            jz      insert_text_and_move_to_next_line_11
            cmp     al,12
            jz      insert_text_and_move_to_next_line_12
            cmp     al,13
            jz      insert_text_and_move_to_next_line_13
            cmp     al,14
            jz      insert_text_and_move_to_next_line_14
            cmp     al,15
            jz      insert_text_and_move_to_next_line_15
            cmp     al,16
            jz      insert_text_and_move_to_next_line_16
            cmp     al,17
            jz      insert_text_and_move_to_next_line_17
            jmp     insert_text_and_move_to_next_line_18

          insert_text_and_move_to_next_line_2:
            mov     esi,offset insert_text_2
            jmp     insert_text_and_move_to_next_line

          insert_text_and_move_to_next_line_3:
            mov     esi,offset insert_text_3
            jmp     insert_text_and_move_to_next_line

          insert_text_and_move_to_next_line_4:
            mov     esi,offset insert_text_4
            jmp     insert_text_and_move_to_next_line

          insert_text_and_move_to_next_line_5:
            mov     esi,offset insert_text_5
            jmp     insert_text_and_move_to_next_line

          insert_text_and_move_to_next_line_6:
            mov     esi,offset insert_text_6
            jmp     insert_text_and_move_to_next_line

          insert_text_and_move_to_next_line_7:
            mov     esi,offset insert_text_7
            jmp     insert_text_and_move_to_next_line

          insert_text_and_move_to_next_line_8:
            mov     esi,offset insert_text_8
            jmp     insert_text_and_move_to_next_line

          insert_text_and_move_to_next_line_9:
            mov     esi,offset insert_text_9
            jmp     insert_text_and_move_to_next_line

          insert_text_and_move_to_next_line_10:
            mov     esi,offset insert_text_10
            jmp     insert_text_and_move_to_next_line

          insert_text_and_move_to_next_line_11:
            mov     esi,offset insert_text_11
            jmp     insert_text_and_move_to_next_line

          insert_text_and_move_to_next_line_12:
            mov     esi,offset insert_text_12
            jmp     insert_text_and_move_to_next_line

          insert_text_and_move_to_next_line_13:
            mov     esi,offset insert_text_13
            jmp     insert_text_and_move_to_next_line

          insert_text_and_move_to_next_line_14:
            mov     esi,offset insert_text_14
            jmp     insert_text_and_move_to_next_line

          insert_text_and_move_to_next_line_15:
            mov     esi,offset insert_text_15
            jmp     insert_text_and_move_to_next_line

          insert_text_and_move_to_next_line_16:
            mov     esi,offset insert_text_16
            jmp     insert_text_and_move_to_next_line

          insert_text_and_move_to_next_line_17:
            mov     esi,offset insert_text_17
            jmp     insert_text_and_move_to_next_line

          insert_text_and_move_to_next_line_18:
            mov     esi,offset insert_text_18
    ;        jmp     insert_text_and_move_to_next_line

          insert_text_and_move_to_next_line:
            .WHILE (byte ptr cs:[esi] != 0 && ecx > 0)
                mov     al,byte ptr cs:[esi]
                inc     esi
                mov     word ptr es:[edi+ebx],ax
                add     ebx,2
                dec     ecx
            .ENDW
            pop     esi
            or      ecx,ecx
            jz      finished
            jmp     inner_loop

      done_inner_loop:
        pop     ebx
        add     ebx,(1*(80*2))                                          ; Move to the next line
        pop     ecx
        or      al,al                                                   ; See if we're finished
        jz      finished
        dec     ecx
        jz      finished
        jmp     outer_loop

      finished:
        pop     es
        popad
        ret
    DEBI_clear_info_box      ENDP




    DEBI_object_unhighlight_last_area    PROC
    ; This routine is used to highlight an area of the screen
    ; Upon entry:   Nothing
    ;
        push    eax
        push    ecx

        mov     ax,ds:highlight_last_point1
        mov     cx,ds:highlight_last_point2
        .IF (ax != 0 && dx != 0)
            call    DEBI_object_highlight_new_area
        .ENDIF

        pop     ecx
        pop     eax
        ret
    DEBI_object_unhighlight_last_area    ENDP




    DEBI_object_highlight_new_area   PROC
    ; This routine is used to highlight an area of the screen
    ; Upon entry:        ds - DATA segment
    ;                    es - MONO segment
    ;              fs:[esi] - far ptr to object
    ;                    ah - X of left-most point
    ;                    al - Y of left-most point
    ;                    ch - X of right-most point
    ;                    cl - Y of right-most point
    ;
        push    eax
        push    ebx
        push    ecx
        push    edx

        mov     ds:highlight_last_point1,ax                             ; Store first coodinate
        mov     ds:highlight_last_point2,cx                             ; Store second coordinate

        xor     ebx,ebx
        mov     bl,al                                                   ; Get Y coordinate
        mov     edx,ebx
        shl     ebx,7                                                   ; multiply by 128
        shl     edx,5                                                   ; multiply by 32
        add     ebx,edx                                                 ; ebx = (ah * 160)

        xor     edx,edx
        mov     dl,ah                                                   ; Add in X coordinate
        shl     edx,1
        add     ebx,edx

        inc     ebx                                                     ; Move to attribute
        .WHILE (ah <= ch)
            mov     al,byte ptr es:[ebx]
            .IF (al >= 112)
                mov     byte ptr es:[ebx],15
            .ELSE
                mov     byte ptr es:[ebx],112
            .ENDIF
            inc     ah
            add     ebx,2
        .ENDW

        pop     edx
        pop     ecx
        pop     ebx
        pop     eax
        ret
    DEBI_object_highlight_new_area   ENDP




    DEBI_calculate_x_y   PROC
    ; This routine calculates the on-screen values of X & Y based on the input video memory offset
    ; Upon entry:   ebx - offset into video memory where a write would go to store information
    ; Upon exit:    bh = x
    ;               bl = y
        push    eax
        push    edx

        xor     edx,edx
        mov     eax,ebx
        mov     ebx,80*2
        div     ebx
        mov     bl,al                                                   ; al = # of rows
        mov     bh,dl                                                   ; dl = # of columns * 2
        shr     bh,1

        pop     edx
        pop     eax
        ret
    DEBI_calculate_x_y   ENDP




    keyboard_byte       db  0
    intercept_key_alt   db  0
    intercept_key_ctrl  db  0
    intercept_key_shift db  0

    DEBI_keyboard_intercept      PROC
    ; This routine is the keyboard intercept during debugging routines
        push    ds
        mov     bx,_sDATA
        mov     ds,bx
        inc     ds:debi_busy                                            ; Raise the busy flag
        .IF (al < 80h)
          ; This is a key depress, we're only concerned with CTRL, ALT and SHIFT keys here
            .IF (al == 5ch || al == 38h)
              ; Left or right ALT key is pressed
                mov     ds:intercept_key_alt,1
            .ELSEIF (al == 5ah || al == 1dh)
              ; Left or right CTRL key is pressed
                mov     ds:intercept_key_ctrl,1
            .ELSEIF (al == 36h || al == 2ah)
              ; Left or right SHIFT key is pressed
                mov     ds:intercept_key_shift,1
            .ELSE
                jmp     @F
            .ENDIF
            jmp     show_object_change
        .ELSEIF (al >= 80h)
          ; This is a key release
            mov     ds:keyboard_byte,al
          ; See what they want to do
            and     al,not 80h
            .IF (al == 5ch || al == 38h)
              ; Left or right ALT key is pressed
                mov     ds:intercept_key_alt,0
            .ELSEIF (al == 5ah || al == 1dh)
              ; Left or right CTRL key is pressed
                mov     ds:intercept_key_ctrl,0
            .ELSEIF (al == 36h || al == 2ah)
              ; Left or right SHIFT key is pressed
                mov     ds:intercept_key_shift,0
            .ELSEIF (al == 58h)
              ; F12 (reset the mouse)
                mov     ds:mouse_offset,0
    ;        .ELSEIF (al == 44h)
    ;          ; F10
    ;            mov     ds:debi_step_over,1
    ;        .ELSEIF (al == 43h)
    ;          ; F9
    ;            mov     ds:debi_breakpoint,1
            .ELSEIF (al == 42h)
              ; F8
                mov     ds:debi_single_step,1
            .ELSEIF (al == 3fh)
              ; F5
                mov     ds:debi_resume,1
            .ELSE
                jmp     @F
            .ENDIF
          show_object_change:
            push    ds
            push    es
            push    fs
            push    esi

            mov     fs,cs:last_object_segment
            mov     esi,cs:last_object_offset
            call    DEBI_object_show

            pop     esi
            pop     fs
            pop     es
            pop     ds
        .ENDIF
      @@:
        dec     ds:debi_busy                                            ; Lower the busy flag
        pop     ds
        ret
    DEBI_keyboard_intercept      ENDP




    DEBI_exception   PROC
    ; This procedure is called during a fatal error for which there is no recovery.  The system will be halted.
    ; Upon entry:   esi - ptr to string to display
    ;
    ;; Display the text they want to show on the monochrome monitor, it goes on line 0
        mov     ax,_sMONO
        mov     es,ax                                                   ; Output goes to 0b0050h
        mov     edi,40*2                                                ;

        mov     ax,_sDATA                                               ; Input comes from the
        mov     ds,ax
      @@:
        lodsb                                                           ; Read a byte from the string
        or      al,al
        jz      @F
        stosb                                                           ; Store the byte
        mov     al,248                                                  ; Store the attribute (blinking reverse video)
        stosb
        jmp     @B

    ;; Lock up the system, baby!  Woo hoo!  Oh Sheila!  Oh Sheila!  It's your birthday!  It's your birthday!
      @@:
        jmp     @B
    DEBI_exception   ENDP

; Upon entry into this algorithm no memory locations have been specified.  They will be updated during the first screen
; updating algorithm or possibly when DEBI is exited (saving the current state prior to continuing).
; Each of these items is 16-bytes in length.  One paragraph.  One happy paragraph. :)
DEBI_screen_table:
                            dd  offset DEBI_m_window        ; +_ST_OBJECT_WINDOW,         Type
                            dd  0                           ; +_ST_OBJECT_UL_HORIZONTAL,  ul-Horizontal
                            dd  0                           ; +_ST_OBJECT_UL_VERTICAL,    ul-Vertical
                            dd  15*8                        ; +_ST_OBJECT_LR_HORIZONTAL,  lr-Horizontal
                            dd  9*8                         ; +_ST_OBJECT_LR_VERTICAL,    lr-Vertical
                            dd  0ffffffffh                  ; +_ST_OBJECT_MEMORY_OFFSET,  Starting offset in _sDEBI_objects memory
                            dd  0                           ; +--Nuserved
                            dd  offset DEBI_m_objects       ; +_ST_OBJECT_OFFSET,         Offset to this item's objects

                            dd  offset DEBI_l_window        ; Type
                            dd  120                         ; ul-Horizontal
                            dd  0                           ; ul-Vertical
                            dd  120+(15*8)                  ; lr-Horizontal
                            dd  9*8                         ; lr-Vertical
                            dd  0ffffffffh                  ; Starting offset
                            dd  0                           ; --Nuserved
                            dd  offset DEBI_l_objects       ; Offset to this item's objects

                            dd  offset DEBI_i_window        ; Type
                            dd  240                         ; ul-Horizontal
                            dd  0                           ; ul-Vertical
                            dd  240+(15*8)                  ; lr-Horizontal
                            dd  9*8                         ; lr-Vertical
                            dd  0ffffffffh                  ; Starting offset
                            dd  0                           ; --Nuserved
                            dd  offset DEBI_i_objects       ; Offset to this item's objects

                            dd  offset DEBI_f_window        ; Type
                            dd  360                         ; ul-Horizontal
                            dd  0                           ; ul-Vertical
                            dd  360+(45*8)                  ; lr-Horizontal
                            dd  18*8                        ; lr-Vertical
                            dd  0ffffffffh                  ; Starting offset
                            dd  0                           ; --Nuserved
                            dd  offset DEBI_f_objects       ; Offset to this item's objects

                            dd  offset DEBI_c_window        ; Type
                            dd  0                           ; ul-Horizontal
                            dd  72                          ; ul-Vertical
                            dd  45*8                        ; lr-Horizontal
                            dd  72+(18*8)                   ; lr-Vertical
                            dd  0ffffffffh                  ; Starting offset
                            dd  0                           ; --Nuserved
                            dd  offset DEBI_c_objects       ; Offset to this item's objects

                            dd  offset DEBI_b_window        ; Type
                            dd  360                         ; ul-Horizontal
                            dd  144                         ; ul-Vertical
                            dd  360+(45*8)                  ; lr-Horizontal
                            dd  144+(9*8)                   ; lr-Vertical
                            dd  0ffffffffh                  ; Starting offset
                            dd  0                           ; --Nuserved
                            dd  offset DEBI_b_objects       ; Offset to this item's objects

                            dd  offset DEBI_h_window        ; Type
                            dd  0                           ; ul-Horizontal
                            dd  216                         ; ul-Vertical
                            dd  60*8                        ; lr-Horizontal
                            dd  216+(9*8)                   ; lr-Vertical
                            dd  0ffffffffh                  ; Starting offset
                            dd  0                           ; --Nuserved
                            dd  offset DEBI_h_objects       ; Offset to this item's objects

                            dd  offset DEBI_j_window        ; Type
                            dd  480                         ; ul-Horizontal
                            dd  216                         ; ul-Vertical
                            dd  480+(30*8)                  ; lr-Horizontal
                            dd  216+(9*8)                   ; lr-Vertical
                            dd  0ffffffffh                  ; Starting offset
                            dd  0                           ; --Nuserved
                            dd  offset DEBI_j_objects       ; Offset to this item's objects

                            dd  offset DEBI_k_window        ; Type
                            dd  0                           ; ul-Horizontal
                            dd  288                         ; ul-Vertical
                            dd  90*8                        ; lr-Horizontal
                            dd  288+(9*8)                   ; lr-Vertical
                            dd  0ffffffffh                  ; Starting offset
                            dd  0                           ; --Nuserved
                            dd  offset DEBI_k_objects       ; Offset to this item's objects

                            dd  offset DEBI_o_window        ; Type
                            dd  0                           ; ul-Horizontal
                            dd  340                         ; ul-Vertical
                            dd  90*8                        ; lr-Horizontal
                            dd  340+(1*8)                   ; lr-Vertical
                            dd  0ffffffffh                  ; Starting offset
                            dd  0                           ; --Nuserved
                            dd  offset DEBI_o_objects       ; Offset to this item's objects

                            db  5*_ST_LENGTH dup(0ffh)      ; Allow space for the maximum of 15 windows on-screen
                                                            ; at any one time.  That's 10 items above, plus the
                                                            ; possibilty of 5 more = 15 items. :)        .IF (al == 0fh)
          ; We know it's at least a two-byte expression
            mov     ebx,2
            .IF (ah == 00000110b)
              ; clts
                mov     edx,offset clts_text
                mov     ecx,4
            .ELSEIF (ah == 00001000b)
              ; invd
                mov     edx,offset invd_text
                mov     ecx,4
            .ELSEIF (ah == 00001001b)
              ; wbinvd
                mov     edx,offset wbinvd_text
                mov     ecx,6
            .ELSE
                mov     dl,ah
                and     dl,11111000b
                .IF (dl == 11001000b)
                  ; bswap
                    mov     edx,offset bswap_text
                    mov     ecx,5
                    cmp     fs:op_size_override,0
                    jz      @F
                    dec     esi
                    mov     ebx,3
                  @@:
;                    call    display_instruction
                    mov     al,ah
                    and     al,111b
                    cmp     fs:op_size_override,0
                    jz      @F
;                    call    display_register_name_32
                    jmp     done_disasm
                  @@:
;                    call    display_register_name_16
                    jmp     done_disasm
                .ENDIF
                mov     dl,ah
                and     dl,11000111b
                .IF (dl == 10000001b)
                  ; It's a possible pop fs/gs.  We have to examine the last three bits to see
                    mov     al,ah
                    shr     al,3
                    and     al,0111b
                    cmp     al,100b
                    jz      try_again1_cont1
                    cmp     al,101b
                    jz      try_again1_cont1
                    jmp     try_again2                              ; If we branch here, then it's not pop fs/gs
                  try_again1_cont1:
                    mov     edx,offset pop_text
                    mov     ecx,3
;                    call    display_instruction
;                    call    display_register_name_sreg
                    jmp     done_disasm
                .ENDIF
              try_again2:
                mov     dl,ah
                and     dl,11000111b
                .IF (dl == 10000000b)
                  ; It's a possible push fs/gs.  We have to examine the last three bits to see
                    mov     al,ah
                    shr     al,3
                    and     al,0111b
                    cmp     al,100b
                    jz      try_again2_success
                    cmp     al,101b
                    jz      try_again2_success
                    jmp     try_again3                              ; If we branch here, then it's not pop fs/gs
                  try_again2_success:
                    mov     edx,offset push_text
                    mov     ecx,4
;                    call    display_instruction
;                    call    display_register_name_sreg
                    jmp     done_disasm
                .ENDIF
              try_again3:
                mov     dl,ah
                and     dl,11000111b
                .IF (dl == 10000011b)
                  ; bt?
                    mov     ebx,3
                    mov     ecx,3                                   ; Default to an instruction length of three
                    mov     dl,ah
                    shr     dl,3
                    and     dl,0111b
                    cmp     dl,100b
                    jnz     try_again_3_sub1
                    ; bt
                    mov     edx,offset bt_text
                    mov     ecx,2
                    jmp     try_again_3_success
                  try_again_3_sub1:
                    cmp     dl,111b
                    jnz     try_again_3_sub2
                    ; btc
                    mov     edx,offset btc_text
                    jmp     try_again_3_success
                  try_again_3_sub2:
                    cmp     dl,110b
                    jnz     try_again_3_sub3
                    ; btr
                    mov     edx,offset btr_text
                    jmp     try_again_3_success
                  try_again_3_sub3:
                    cmp     dl,101b
                    jnz     try_again_3_sub4
                    ; bts
                    mov     edx,offset bts_text
                    jmp     try_again_3_success
                  try_again_3_sub4:
                    ; Who knows what it is?  Maybe it's an instruction to be decoded later, continue searching
                    jmp     try_again4

                  try_again_3_success:
;                    call    display_instruction_with_mod_reg_rm
                    jmp     done_disasm
                .ENDIF
              try_again4:
                mov     dl,ah
                and     dl,11111110b
                .IF (dl == 10110000b)
                  ; cmpxchg
                    mov     dl,ah
                    and     dl,1b
                    mov     fs:byte_word_size,dl
                    mov     edx,offset cmpxchg_text
                    mov     ebx,3
                    mov     ecx,7
;                    call    display_instruction_with_mod_reg_rm
                    jmp     done_disasm
                .ENDIF
                mov     dl,ah
                and     dl,11110000b
                .IF (dl == 10000000b)
                  ; It's jccc disp2
                    mov     ebx,4
                    mov     dl,ah
                    and     dl,1111b
                    cmp     dl,0000b
                    jnz     try_again5_sub1
                    ; It's jo
                    mov     edx,offset jo_text
                    mov     ecx,2
                    jmp     try_again5_success
                  try_again5_sub1:
                    cmp     dl,0001b
                    jnz     try_again5_sub2
                    ; It's jno
                    mov     edx,offset jno_text
                    mov     ecx,3
                    jmp     try_again5_success
                  try_again5_sub2:
                    cmp     dl,0010b
                    jnz     try_again5_sub3
                    ; It's jc/jb/jnae (unsigned)
                    mov     edx,offset jc_text
                    mov     ecx,2
                    jmp     try_again5_success
                  try_again5_sub3:
                    cmp     dl,0011b
                    jnz     try_again5_sub4
                    ; It's jnc/jnb/jae (unsigned)
                    mov     edx,offset jnc_text
                    mov     ecx,3
                    jmp     try_again5_success
                  try_again5_sub4:
                    cmp     dl,0100b
                    jnz     try_again5_sub5
                    ; It's jz/je
                    mov     edx,offset jz_text
                    mov     ecx,2
                    jmp     try_again5_success
                  try_again5_sub5:
                    cmp     dl,0101b
                    jnz     try_again5_sub6
                    ; It's jnz/jne
                    mov     edx,offset jnz_text
                    mov     ecx,3
                    jmp     try_again5_success
                  try_again5_sub6:
                    cmp     dl,0110b
                    jnz     try_again5_sub7
                    ; It's jbe/jna (unsigned)
                    mov     edx,offset jbe_text
                    mov     ecx,3
                    jmp     try_again5_success
                  try_again5_sub7:
                    cmp     dl,0111b
                    jnz     try_again5_sub8
                    ; It's ja/jnbe (unsigned)
                    mov     edx,offset ja_text
                    mov     ecx,2
                    jmp     try_again5_success
                  try_again5_sub8:
                    cmp     dl,1000b
                    jnz     try_again5_sub9
                    ; It's js
                    mov     edx,offset js_text
                    mov     ecx,2
                    jmp     try_again5_success
                  try_again5_sub9:
                    cmp     dl,1001b
                    jnz     try_again5_sub10
                    ; It's jns
                    mov     edx,offset jns_text
                    mov     ecx,3
                    jmp     try_again5_success
                  try_again5_sub10:
                    cmp     dl,1010b
                    jnz     try_again5_sub11
                    ; It's jp
                    mov     edx,offset jp_text
                    mov     ecx,2
                    jmp     try_again5_success
                  try_again5_sub11:
                    cmp     dl,1011b
                    jnz     try_again5_sub12
                    ; It's jnp
                    mov     edx,offset jnp_text
                    mov     ecx,3
                    jmp     try_again5_success
                  try_again5_sub12:
                    cmp     dl,1100b
                    jnz     try_again5_sub13
                    ; It's jl/jnge (signed)
                    mov     edx,offset jl_text
                    mov     ecx,2
                    jmp     try_again5_success
                  try_again5_sub13:
                    cmp     dl,1101b
                    jnz     try_again5_sub14
                    ; It's jge/nl (signed)
                    mov     edx,offset jge_text
                    mov     ecx,3
                    jmp     try_again5_success
                  try_again5_sub14:
                    cmp     dl,1110b
                    jnz     try_again5_sub15
                    ; It's jle/jng (signed)
                    mov     edx,offset jle_text
                    mov     ecx,3
                    jmp     try_again5_success
                  try_again5_sub15:
                    ; It's jg/jnle (signed)                         ; It's the only combination left
                    mov     edx,offset jg_text
                    mov     ecx,2
                  try_again5_success:
;                    call    display_instruction
                    mov     dx,word ptr ds:[esi-2]
;                    call    show_register_16_signed
                    add     edi,6
;                    call    show_new_cs_ip
                    jmp     done_disasm
                .ENDIF
                mov     dl,ah
                mov     dh,ah
                and     dl,11111101b
                and     dh,00000010b
                shr     dh,1
                .IF (dl == 00100000b)
                  ; It's a "mov creg,reg32; reg32,cref"
                    mov     ah,dh
                    inc     ebx
                    mov     edx,offset mov_text
                    mov     ecx,3
                    cmp     ah,0
                    jz      @F
                    ; Direction is 1
                    mov     fs:special_reg,0
                  try_again7_direction_1:
;                    call    display_instruction
                    mov     al,byte ptr ds:[esi-1]
                    and     al,111b
;                    call    display_register_name_special_reg
;                    call    display_comma
                    mov     al,byte ptr ds:[esi-1]
                    shr     al,3
                    and     al,111b
;                    call    display_register_name_32
                    jmp     done_disasm
                  @@:
                    ; Direction is 0
                    mov     fs:special_reg,0
                  try_again7_direction_0:
;                    call    display_instruction
                    mov     al,byte ptr ds:[esi-1]
                    and     al,111b
;                    call    display_register_name_32
;                    call    display_comma
                    mov     al,byte ptr ds:[esi-1]
                    shr     al,3
                    and     al,111b
;                    call    display_register_name_special_reg
                    jmp     done_disasm
                .ENDIF
              try_again7:
                .IF (dl == 00100001b)
                  ; It's a "mov dreg,reg32; reg32,dreg"
                    mov     fs:special_reg,1
                    mov     ah,dh
                    inc     ebx
                    mov     edx,offset mov_text
                    mov     ecx,3
                    cmp     ah,0
                    jz      @F
                    ; Direction is 1
                    jmp     try_again7_direction_1
                  @@:
                    ; Direction is 0
                    jmp     try_again7_direction_0
                .ENDIF
                .IF (dl == 00100100b)
                  ; It's a "mov treg,reg32; reg32,treg"
                    mov     fs:special_reg,2
                    mov     ah,dh
                    inc     ebx
                    mov     edx,offset mov_text
                    mov     ecx,3
                    cmp     ah,0
                    jz      @F
                    ; Direction is 1
                    jmp     try_again7_direction_1
                  @@:
                    ; Direction is 0
                    jmp     try_again7_direction_0
                .ENDIF
                mov     dl,ah
                mov     dh,ah
                and     dl,11111110b
                and     dh,00000001b
                .IF (dl == 10111110b)
                  ; It's movsx
                    mov     fs:byte_word_size,dh
                    mov     edx,offset movsx_text
                    mov     ecx,5
                    inc     ebx
;                    call    display_instruction_with_mod_reg_rm_movxx
                    jmp     done_disasm
                .ENDIF

                .IF (dl == 10110110b)
                  ; It's movzx
                    mov     fs:byte_word_size,dh
                    mov     edx,offset movzx_text
                    mov     ecx,5
                    inc     ebx
;                    call    display_instruction_with_mod_reg_rm_movxx
                    jmp     done_disasm
                .ENDIF
                mov     dl,ah
                and     dl,11110000b
                .IF (dl == 10010000b)
                  ; It's setccc
                    mov     ebx,3
                    mov     dl,ah
                    and     dl,1111b
                    cmp     dl,0000b
                    jnz     try_again11_sub1
                    ; It's seto
                    mov     edx,offset seto_text
                    mov     ecx,4
                    jmp     try_again11_success
                  try_again11_sub1:
                    cmp     dl,0001b
                    jnz     try_again11_sub2
                    ; It's setno
                    mov     edx,offset setno_text
                    mov     ecx,5
                    jmp     try_again11_success
                  try_again11_sub2:
                    cmp     dl,0010b
                    jnz     try_again11_sub3
                    ; It's setc/setb/setnae (unsigned)
                    mov     edx,offset setc_text
                    mov     ecx,4
                    jmp     try_again11_success
                  try_again11_sub3:
                    cmp     dl,0011b
                    jnz     try_again11_sub4
                    ; It's setnc/setnb/setae (unsigned)
                    mov     edx,offset setnc_text
                    mov     ecx,5
                    jmp     try_again11_success
                  try_again11_sub4:
                    cmp     dl,0100b
                    jnz     try_again11_sub5
                    ; It's setz/sete
                    mov     edx,offset setz_text
                    mov     ecx,4
                    jmp     try_again11_success
                  try_again11_sub5:
                    cmp     dl,0101b
                    jnz     try_again11_sub6
                    ; It's setnz/setne
                    mov     edx,offset setnz_text
                    mov     ecx,5
                    jmp     try_again11_success
                  try_again11_sub6:
                    cmp     dl,0110b
                    jnz     try_again11_sub7
                    ; It's setbe/setna (unsigned)
                    mov     edx,offset setbe_text
                    mov     ecx,5
                    jmp     try_again11_success
                  try_again11_sub7:
                    cmp     dl,0111b
                    jnz     try_again11_sub8
                    ; It's seta/setnbe (unsigned)
                    mov     edx,offset seta_text
                    mov     ecx,4
                    jmp     try_again11_success
                  try_again11_sub8:
                    cmp     dl,1000b
                    jnz     try_again11_sub9
                    ; It's sets
                    mov     edx,offset sets_text
                    mov     ecx,4
                    jmp     try_again11_success
                  try_again11_sub9:
                    cmp     dl,1001b
                    jnz     try_again11_sub10
                    ; It's setns
                    mov     edx,offset setns_text
                    mov     ecx,5
                    jmp     try_again11_success
                  try_again11_sub10:
                    cmp     dl,1010b
                    jnz     try_again11_sub11
                    ; It's setp
                    mov     edx,offset setp_text
                    mov     ecx,4
                    jmp     try_again11_success
                  try_again11_sub11:
                    cmp     dl,1011b
                    jnz     try_again11_sub12
                    ; It's setnp
                    mov     edx,offset setnp_text
                    mov     ecx,5
                    jmp     try_again11_success
                  try_again11_sub12:
                    cmp     dl,1100b
                    jnz     try_again11_sub13
                    ; It's setl/setnge (signed)
                    mov     edx,offset setl_text
                    mov     ecx,4
                    jmp     try_again11_success
                  try_again11_sub13:
                    cmp     dl,1101b
                    jnz     try_again11_sub14
                    ; It's setge/nl (signed)
                    mov     edx,offset setge_text
                    mov     ecx,5
                    jmp     try_again11_success
                  try_again11_sub14:
                    cmp     dl,1110b
                    jnz     try_again11_sub15
                    ; It's setle/setng (signed)
                    mov     edx,offset setle_text
                    mov     ecx,5
                    jmp     try_again11_success
                  try_again11_sub15:
                    ; It's setg/setnle (signed)                                 ; It's the only combination left
                    mov     edx,offset setg_text
                    mov     ecx,4
                  try_again11_success:
                    mov     fs:byte_word_size,0
;                    call    display_instruction_with_mod_rm
                    jmp     done_disasm
                .ENDIF
                and     dl,11111110b
                .IF (dl == 11000000b)
                  ; It's xadd
                    mov     ebx,3
                    mov     dl,al
                    and     dl,1b
                    mov     fs:byte_word_size,dl
                    mov     edx,offset xadd_text
                    mov     ecx,4
;                    call    display_instruction_with_mod_reg_rm
                    jmp     done_disasm
                .ENDIF
                mov     ebx,3                                          ; This next batch of instructions are all at least 3 bytes
                .IF (ah == 00000000b)
                  ; It's sldt, str, lldg, ltr, verr or verw
                    mov     dl,byte ptr ds:[esi+2]
                    shr     dl,3
                    and     dl,111b
                    cmp     dl,000b
                    jz      @F
                    jmp     try_again13_sub1
                  @@:
                    ; It's sldt
                        mov     edx,offset sldt_text
                        mov     ecx,4
                        jmp     try_again13_success
                  try_again13_sub1:
                    cmp     dl,001b
                    jz      @F
                    jmp     try_again13_sub2
                  @@:
                    ; It's str
                        mov     edx,offset str_text
                        mov     ecx,3
                        jmp     try_again13_success
                  try_again13_sub2:
                    cmp     dl,010b
                    jz      @F
                    jmp     try_again13_sub3
                  @@:
                    ; It's lldt
                        mov     edx,offset lldt_text
                        mov     ecx,4
                        jmp     try_again13_success
                  try_again13_sub3:
                    cmp     dl,011b
                    jz      @F
                    jmp     try_again13_sub4
                  @@:
                    ; It's ltr
                        mov     edx,offset ltr_text
                        mov     ecx,3
                        jmp     try_again13_success
                  try_again13_sub4:
                    cmp     dl,100b
                    jz      @F
                    jmp     try_again13_sub5
                  @@:
                    ; It's verr
                        mov     edx,offset verr_text
                        mov     ecx,4
                        jmp     try_again13_success
                  try_again13_sub5:
                    cmp     dl,101b
                    jz      @F
                    jmp     try_again13_sub6
                  @@:
                    ; It's verw
                        mov     edx,offset verw_text
                        mov     ecx,4
                  try_again13_success:
;                    call    display_instruction_with_mod_rm
                    jmp     done_disasm

                  try_again13_sub6:
                .ENDIF
                .IF (ah == 00000001b)
                  ; It's sgdt, sidt, lgdt, lidt, smsw, lmsw or invlpg
                    mov     ecx,4
                    mov     dl,byte ptr ds:[esi+2]
                    shr     dl,3
                    and     dl,111b
                    cmp     dl,000b
                    jz      @F
                    jmp     try_again14_sub1
                  @@:
                    ; It's sgdt
                        mov     edx,offset sgdt_text
                        jmp     try_again14_success
                  try_again14_sub1:
                    cmp     dl,001b
                    jz      @F
                    jmp     try_again14_sub2
                  @@:
                    ; It's sidt
                        mov     edx,offset sidt_text
                        jmp     try_again14_success
                  try_again14_sub2:
                    cmp     dl,010b
                    jz      @F
                    jmp     try_again14_sub3
                  @@:
                    ; It's lgdt
                        mov     edx,offset lgdt_text
                        jmp     try_again14_success
                  try_again14_sub3:
                    cmp     dl,011b
                    jz      @F
                    jmp     try_again14_sub4
                  @@:
                    ; It's lidt
                        mov     edx,offset lidt_text
                        jmp     try_again14_success
                  try_again14_sub4:
                    cmp     dl,100b
                    jz      @F
                    jmp     try_again14_sub5
                  @@:
                    ; It's smsw
                        mov     edx,offset smsw_text
                        jmp     try_again14_success
                  try_again14_sub5:
                    cmp     dl,110b
                    jz      @F
                    jmp     try_again14_sub6
                  @@:
                    ; It's lmsw
                        mov     edx,offset lmsw_text
                        jmp     try_again14_success
                  try_again14_sub6:
                    cmp     dl,111b
                    jz      @F
                    jmp     try_again14_sub7
                  @@:
                    ; It's invlpg
                        mov     edx,offset invlpg_text
                        mov     ecx,6
;                        jmp     try_again14_success
                  try_again14_success:
;                    call    display_instruction_with_mod_rm
                    jmp     done_disasm

                  try_again14_sub7:
                    ; Who knows what is is, continue looking
                .ENDIF

                .IF (ah == 00000010b)
                  ; It's lar
                    inc     ebx
                    mov     edx,offset lar_text
                    mov     ecx,3
;                    call    display_instruction_with_mod_reg_rm
                    jmp     done_disasm
                .ELSEIF (ah == 00000011b)
                  ; It's lsl
                    inc     ebx
                    mov     edx,offset lsl_text
                    mov     ecx,3
;                    call    display_instruction_with_mod_reg_rm
                    jmp     done_disasm
                .ENDIF
                mov     ecx,4
                .IF (ah == 10100100b)
                  ; It's shld by immed
                    mov     edx,offset shld_text
                    jmp     show_instruction
                .ELSEIF (ah == 10100101b)
                  ; It's shld by cl
                    mov     edx,offset shld_text
                    jmp     show_instruction
                .ELSEIF (ah == 10101100b)
                  ; It's shrd by immed
                    mov     edx,offset shrd_text
                    jmp     show_instruction
                .ELSEIF (ah == 10101101b)
                  ; It's shrd by cl
                    mov     edx,offset shrd_text
                    jmp     show_instruction
                .ELSEIF (ah == 10101111b)
                  ; It's imul
                    inc     ebx
                    mov     edx,offset imul_text
;                    call    display_instruction_with_mod_reg_rm
                    jmp     done_disasm
                .ENDIF
                mov     ecx,3
                .IF (ah == 10110010b)
                  ; lss
                    mov     fs:reverse_regs,1
                    mov     edx,offset lss_text
                    mov     ebx,3
;                    call    display_instruction_with_mod_reg_rm
                    jmp     done_disasm
                .ELSEIF (ah == 10110100b)
                  ; lfs
                    mov     fs:reverse_regs,1
                    mov     edx,offset lfs_text
                    mov     ebx,3
;                    call    display_instruction_with_mod_reg_rm
                    jmp     done_disasm
                .ELSEIF (ah == 10110101b)
                  ; lgs
                    mov     fs:reverse_regs,1
                    mov     edx,offset lgs_text
                    mov     ebx,3
;                    call    display_instruction_with_mod_reg_rm
                    jmp     done_disasm
                .ELSEIF (ah == 10111010b)
                  ; It's bt/btc/btr/btc
                    mov     ecx,3
                    mov     dl,byte ptr ds:[esi+2]
                    shr     dl,3
                    and     dl,111b
                    cmp     dl,100b
                    jnz     @F
                    mov     edx,offset bt_text
                    mov     ecx,2
                    jmp     try_again25_success
                  @@:
                    cmp     dl,101b
                    jnz     @F
                    mov     edx,offset bts_text
                    jmp     try_again25_success
                  @@:
                    cmp     dl,110b
                    jnz     @F
                    mov     edx,offset btr_text
                    jmp     try_again25_success
                  @@:
                    cmp     dl,111b
                    jnz     try_again26
                    mov     edx,offset btc_text
                  try_again25_success:
                    jmp     show_instruction
                .ENDIF

              try_again26:
                .IF (ah == 10111100b)
                  ; It's bsf
                    mov     edx,offset bsf_text
                    jmp     show_instruction
                .ELSEIF (ah == 10111101b)
                  ; It's bsr
                    mov     edx,offset bsr_text
                    jmp     show_instruction
                .ENDIF
                jmp     unknown_instruction
            .ENDIF
;            jmp     show_instruction
        .ELSE
          ; We'll check the one-byte expressions
        .ENDIF
    .ENDIF
    inc     esi
    jmp     next_byte
            mov     eax,_sDEBI_screen
            mov     ds,ax
            push    dword ptr 264
            push    dword ptr 0
            push    dword ptr 264+(15*8)
            push    dword ptr 9*8
            push    dword ptr 1
            push    dword ptr 0
            call    fword ptr cs:_VID_g_mono_window_function

            push    dword ptr cs:debi_mouse_current_x
            push    dword ptr cs:debi_mouse_current_y
            mov     edx,cs:debi_mouse_current_x
            add     edx,15*8
            push    edx
            mov     edx,cs:debi_mouse_current_y
            add     edx,9*8
            push    edx
            push    dword ptr 0
            push    dword ptr 0
            call    fword ptr cs:_VID_g_mono_window_function

              ; They've either released one of the two previously clicked mouse buttons
              ; Or they've clicked on another one
                mov     edx,ds:mouse_last_buttons
                test    edx,01b
                .IF (zero?)
                  ; The right button was previously down
                    test    edx,10b
                    .IF (zero?)
                      ; Both buttons were previously down
                        test    ebx,01b
                        .IF (zero?)
                          ; They've released the left button
                            mov     ds:mouse_last_buttons,ebx
                            mov     esi,offset left_release_text
                            call    invDEBI_quick_watch_add_item
                            jmp     quit
                        .ENDIF
                        test    ebx,10b
                        .IF (zero?)
                          ; They've released the right button
                            mov     ds:mouse_last_buttons,ebx
                            mov     esi,offset right_release_text
                            call    invDEBI_quick_watch_add_item
                            jmp     quit
                        .ENDIF
                    .ELSE
                      ; Only the right button was previously down
                        test    ebx,10b
                        .IF (zero?)
                          ; They've clicked down on the left-button
                            mov     ds:mouse_last_buttons,ebx
                            mov     esi,offset left_click_text
                            call    invDEBI_quick_watch_add_item
                            jmp     quit
                        .ENDIF
                    .ENDIF
                .ENDIF
                test    edx,10b
                .IF (zero?)
                  ; The left button was previously down
                    test    ebx,01b
                    .IF (zero?)
                      ; They've now clicked down on the right button
                        mov     ds:mouse_last_buttons,ebx
                        mov     esi,offset right_click_text
                        call    invDEBI_quick_watch_add_item
                        jmp     quit
                    .ENDIF
                    test    ebx,10b
                    .IF (!zero?)
                      ; They've released the left button
                        mov     ds:mouse_last_buttons,ebx
                        mov     esi,offset left_release_text
                        call    invDEBI_quick_watch_add_item
                        jmp     quit
                    .ENDIF
                .ENDIF
            .ENDIF
        .IF (ds:mouse_last_buttons != 0)
          ; They previously had buttons down
            .IF (ebx == 0)
              ; They've released all mouse buttons
                mov     ebx,ds:mouse_last_buttons
                test    ebx,01b
                .IF (zero?)
                  ; It was the right button they released
                    mov     ds:mouse_last_buttons,0
                    mov     esi,offset right_release_text
                    call    invDEBI_quick_watch_add_item
                    jmp     quit
                .ENDIF
                test    ebx,10b
                .IF (zero?)
                  ; It was the left button they released
                    mov     ds:mouse_last_buttons,0
                    mov     esi,offset left_release_text
                    call    invDEBI_quick_watch_add_item
                    jmp     quit
                .ENDIF
            .ELSE
                jmp     new_click
            .ENDIF
        .ELSE
          ; They've just started to click something
          new_click:
            test    ebx,01b
            .IF (zero?)
              ; It's a right click
                mov     ds:mouse_last_buttons,ebx
                mov     esi,offset right_click_text
                call    invDEBI_quick_watch_add_item
                jmp     quit
            .ENDIF
            test    ebx,10b
            .IF (zero?)
              ; It's a left click
                mov     ds:mouse_last_buttons,ebx
                mov     esi,offset left_click_text
                call    invDEBI_quick_watch_add_item
                jmp     quit
            .ENDIF
        .ENDIF
    @Abandon_if_not          6,  1, 57, 12
    @Hover                   6,  1,  7,  1,  0+12, invDEBI_quick_watch_mem_8          ; +00 - +15
    @Hover                   8,  1,  9,  1,  1+12, invDEBI_quick_watch_mem_8
    @Hover                  10,  1, 11,  1,  2+12, invDEBI_quick_watch_mem_8
    @Hover                  12,  1, 13,  1,  3+12, invDEBI_quick_watch_mem_8
    @Hover                  14,  1, 15,  1,  4+12, invDEBI_quick_watch_mem_8
    @Hover                  16,  1, 17,  1,  5+12, invDEBI_quick_watch_mem_8
    @Hover                  18,  1, 19,  1,  6+12, invDEBI_quick_watch_mem_8
    @Hover                  20,  1, 21,  1,  7+12, invDEBI_quick_watch_mem_8
    @Hover                  22,  1, 23,  1,  8+12, invDEBI_quick_watch_mem_8
    @Hover                  24,  1, 25,  1,  9+12, invDEBI_quick_watch_mem_8
    @Hover                  26,  1, 27,  1, 10+12, invDEBI_quick_watch_mem_8
    @Hover                  28,  1, 29,  1, 11+12, invDEBI_quick_watch_mem_8
    @Hover                  30,  1, 31,  1, 12+12, invDEBI_quick_watch_mem_8
    @Hover                  32,  1, 33,  1, 13+12, invDEBI_quick_watch_mem_8
    @Hover                  34,  1, 35,  1, 14+12, invDEBI_quick_watch_mem_8
    @Hover                  36,  1, 37,  1, 15+12, invDEBI_quick_watch_mem_8

    @Hover                   6,  2,  7,  2, 16+12, invDEBI_quick_watch_mem_8          ; +06 - +31
    @Hover                   8,  2,  9,  2, 17+12, invDEBI_quick_watch_mem_8
    @Hover                  10,  2, 11,  2, 18+12, invDEBI_quick_watch_mem_8
    @Hover                  12,  2, 13,  2, 19+12, invDEBI_quick_watch_mem_8
    @Hover                  14,  2, 15,  2, 20+12, invDEBI_quick_watch_mem_8
    @Hover                  16,  2, 17,  2, 21+12, invDEBI_quick_watch_mem_8
    @Hover                  18,  2, 19,  2, 22+12, invDEBI_quick_watch_mem_8
    @Hover                  20,  2, 21,  2, 23+12, invDEBI_quick_watch_mem_8
    @Hover                  22,  2, 23,  2, 24+12, invDEBI_quick_watch_mem_8
    @Hover                  24,  2, 25,  2, 25+12, invDEBI_quick_watch_mem_8
    @Hover                  26,  2, 27,  2, 26+12, invDEBI_quick_watch_mem_8
    @Hover                  28,  2, 29,  2, 27+12, invDEBI_quick_watch_mem_8
    @Hover                  30,  2, 31,  2, 28+12, invDEBI_quick_watch_mem_8
    @Hover                  32,  2, 33,  2, 29+12, invDEBI_quick_watch_mem_8
    @Hover                  34,  2, 35,  2, 30+12, invDEBI_quick_watch_mem_8
    @Hover                  36,  2, 37,  2, 31+12, invDEBI_quick_watch_mem_8

    @Hover                   6,  3,  7,  3, 32+12, invDEBI_quick_watch_mem_8          ; +32 - +47
    @Hover                   8,  3,  9,  3, 33+12, invDEBI_quick_watch_mem_8
    @Hover                  10,  3, 11,  3, 34+12, invDEBI_quick_watch_mem_8
    @Hover                  12,  3, 13,  3, 35+12, invDEBI_quick_watch_mem_8
    @Hover                  14,  3, 15,  3, 36+12, invDEBI_quick_watch_mem_8
    @Hover                  16,  3, 17,  3, 37+12, invDEBI_quick_watch_mem_8
    @Hover                  18,  3, 19,  3, 38+12, invDEBI_quick_watch_mem_8
    @Hover                  20,  3, 21,  3, 39+12, invDEBI_quick_watch_mem_8
    @Hover                  22,  3, 23,  3, 40+12, invDEBI_quick_watch_mem_8
    @Hover                  24,  3, 25,  3, 41+12, invDEBI_quick_watch_mem_8
    @Hover                  26,  3, 27,  3, 42+12, invDEBI_quick_watch_mem_8
    @Hover                  28,  3, 29,  3, 43+12, invDEBI_quick_watch_mem_8
    @Hover                  30,  3, 31,  3, 44+12, invDEBI_quick_watch_mem_8
    @Hover                  32,  3, 33,  3, 45+12, invDEBI_quick_watch_mem_8
    @Hover                  34,  3, 35,  3, 46+12, invDEBI_quick_watch_mem_8
    @Hover                  36,  3, 37,  3, 47+12, invDEBI_quick_watch_mem_8

    @Hover                   6,  4,  7,  4, 48+12, invDEBI_quick_watch_mem_8          ; +48 - +63
    @Hover                   8,  4,  9,  4, 49+12, invDEBI_quick_watch_mem_8
    @Hover                  10,  4, 11,  4, 50+12, invDEBI_quick_watch_mem_8
    @Hover                  12,  4, 13,  4, 51+12, invDEBI_quick_watch_mem_8
    @Hover                  14,  4, 15,  4, 52+12, invDEBI_quick_watch_mem_8
    @Hover                  16,  4, 17,  4, 53+12, invDEBI_quick_watch_mem_8
    @Hover                  18,  4, 19,  4, 54+12, invDEBI_quick_watch_mem_8
    @Hover                  20,  4, 21,  4, 55+12, invDEBI_quick_watch_mem_8
    @Hover                  22,  4, 23,  4, 56+12, invDEBI_quick_watch_mem_8
    @Hover                  24,  4, 25,  4, 57+12, invDEBI_quick_watch_mem_8
    @Hover                  26,  4, 27,  4, 58+12, invDEBI_quick_watch_mem_8
    @Hover                  28,  4, 29,  4, 59+12, invDEBI_quick_watch_mem_8
    @Hover                  30,  4, 31,  4, 60+12, invDEBI_quick_watch_mem_8
    @Hover                  32,  4, 33,  4, 61+12, invDEBI_quick_watch_mem_8
    @Hover                  34,  4, 35,  4, 62+12, invDEBI_quick_watch_mem_8
    @Hover                  36,  4, 37,  4, 63+12, invDEBI_quick_watch_mem_8

    @Hover                   6,  5,  7,  5, 64+12, invDEBI_quick_watch_mem_8          ; +64 - +79
    @Hover                   8,  5,  9,  5, 65+12, invDEBI_quick_watch_mem_8
    @Hover                  10,  5, 11,  5, 66+12, invDEBI_quick_watch_mem_8
    @Hover                  12,  5, 13,  5, 67+12, invDEBI_quick_watch_mem_8
    @Hover                  14,  5, 15,  5, 68+12, invDEBI_quick_watch_mem_8
    @Hover                  16,  5, 17,  5, 69+12, invDEBI_quick_watch_mem_8
    @Hover                  18,  5, 19,  5, 70+12, invDEBI_quick_watch_mem_8
    @Hover                  20,  5, 21,  5, 71+12, invDEBI_quick_watch_mem_8
    @Hover                  22,  5, 23,  5, 72+12, invDEBI_quick_watch_mem_8
    @Hover                  24,  5, 25,  5, 73+12, invDEBI_quick_watch_mem_8
    @Hover                  26,  5, 27,  5, 74+12, invDEBI_quick_watch_mem_8
    @Hover                  28,  5, 29,  5, 75+12, invDEBI_quick_watch_mem_8
    @Hover                  30,  5, 31,  5, 76+12, invDEBI_quick_watch_mem_8
    @Hover                  32,  5, 33,  5, 77+12, invDEBI_quick_watch_mem_8
    @Hover                  34,  5, 35,  5, 78+12, invDEBI_quick_watch_mem_8
    @Hover                  36,  5, 37,  5, 79+12, invDEBI_quick_watch_mem_8

    @Hover                   6,  6,  7,  6, 80+12, invDEBI_quick_watch_mem_8          ; +80 - +125
    @Hover                   8,  6,  9,  6, 81+12, invDEBI_quick_watch_mem_8
    @Hover                  10,  6, 11,  6, 82+12, invDEBI_quick_watch_mem_8
    @Hover                  12,  6, 13,  6, 83+12, invDEBI_quick_watch_mem_8
    @Hover                  14,  6, 15,  6, 84+12, invDEBI_quick_watch_mem_8
    @Hover                  16,  6, 17,  6, 85+12, invDEBI_quick_watch_mem_8
    @Hover                  18,  6, 19,  6, 86+12, invDEBI_quick_watch_mem_8
    @Hover                  20,  6, 21,  6, 87+12, invDEBI_quick_watch_mem_8
    @Hover                  22,  6, 23,  6, 88+12, invDEBI_quick_watch_mem_8
    @Hover                  24,  6, 25,  6, 89+12, invDEBI_quick_watch_mem_8
    @Hover                  26,  6, 27,  6, 90+12, invDEBI_quick_watch_mem_8
    @Hover                  28,  6, 29,  6, 91+12, invDEBI_quick_watch_mem_8
    @Hover                  30,  6, 31,  6, 92+12, invDEBI_quick_watch_mem_8
    @Hover                  32,  6, 33,  6, 93+12, invDEBI_quick_watch_mem_8
    @Hover                  34,  6, 35,  6, 94+12, invDEBI_quick_watch_mem_8
    @Hover                  36,  6, 37,  6, 95+12, invDEBI_quick_watch_mem_8

    @Hover                   6,  7,  7,  7, 96+12, invDEBI_quick_watch_mem_8          ; +126 - +111
    @Hover                   8,  7,  9,  7, 97+12, invDEBI_quick_watch_mem_8
    @Hover                  10,  7, 11,  7, 98+12, invDEBI_quick_watch_mem_8
    @Hover                  12,  7, 13,  7, 99+12, invDEBI_quick_watch_mem_8
    @Hover                  14,  7, 15,  7,100+12, invDEBI_quick_watch_mem_8
    @Hover                  16,  7, 17,  7,101+12, invDEBI_quick_watch_mem_8
    @Hover                  18,  7, 19,  7,102+12, invDEBI_quick_watch_mem_8
    @Hover                  20,  7, 21,  7,103+12, invDEBI_quick_watch_mem_8
    @Hover                  22,  7, 23,  7,104+12, invDEBI_quick_watch_mem_8
    @Hover                  24,  7, 25,  7,105+12, invDEBI_quick_watch_mem_8
    @Hover                  26,  7, 27,  7,106+12, invDEBI_quick_watch_mem_8
    @Hover                  28,  7, 29,  7,107+12, invDEBI_quick_watch_mem_8
    @Hover                  30,  7, 31,  7,108+12, invDEBI_quick_watch_mem_8
    @Hover                  32,  7, 33,  7,109+12, invDEBI_quick_watch_mem_8
    @Hover                  34,  7, 35,  7,110+12, invDEBI_quick_watch_mem_8
    @Hover                  36,  7, 37,  7,111+12, invDEBI_quick_watch_mem_8

    @Hover                   6,  8,  7,  8,112+12, invDEBI_quick_watch_mem_8          ; +112 - +127
    @Hover                   8,  8,  9,  8,113+12, invDEBI_quick_watch_mem_8
    @Hover                  10,  8, 11,  8,114+12, invDEBI_quick_watch_mem_8
    @Hover                  12,  8, 13,  8,115+12, invDEBI_quick_watch_mem_8
    @Hover                  14,  8, 15,  8,116+12, invDEBI_quick_watch_mem_8
    @Hover                  16,  8, 17,  8,117+12, invDEBI_quick_watch_mem_8
    @Hover                  18,  8, 19,  8,118+12, invDEBI_quick_watch_mem_8
    @Hover                  20,  8, 21,  8,119+12, invDEBI_quick_watch_mem_8
    @Hover                  22,  8, 23,  8,120+12, invDEBI_quick_watch_mem_8
    @Hover                  24,  8, 25,  8,121+12, invDEBI_quick_watch_mem_8
    @Hover                  26,  8, 27,  8,122+12, invDEBI_quick_watch_mem_8
    @Hover                  28,  8, 29,  8,123+12, invDEBI_quick_watch_mem_8
    @Hover                  30,  8, 31,  8,124+12, invDEBI_quick_watch_mem_8
    @Hover                  32,  8, 33,  8,125+12, invDEBI_quick_watch_mem_8
    @Hover                  34,  8, 35,  8,126+12, invDEBI_quick_watch_mem_8
    @Hover                  36,  8, 37,  8,127+12, invDEBI_quick_watch_mem_8

    @Hover                  42,  1, 42,  1,  0+12, invDEBI_quick_watch_mem_ascii_8    ; +00 - +15
    @Hover                  43,  1, 43,  1,  1+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  44,  1, 44,  1,  2+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  45,  1, 45,  1,  3+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  46,  1, 46,  1,  4+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  47,  1, 47,  1,  5+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  48,  1, 48,  1,  6+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  49,  1, 49,  1,  7+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  50,  1, 50,  1,  8+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  51,  1, 51,  1,  9+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  52,  1, 52,  1, 10+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  53,  1, 53,  1, 11+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  54,  1, 54,  1, 12+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  55,  1, 55,  1, 13+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  56,  1, 56,  1, 14+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  57,  1, 57,  1, 15+12, invDEBI_quick_watch_mem_ascii_8

    @Hover                  42,  2, 42,  2, 16+12, invDEBI_quick_watch_mem_ascii_8    ; +06 - +31
    @Hover                  43,  2, 43,  2, 17+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  44,  2, 44,  2, 18+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  45,  2, 45,  2, 19+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  46,  2, 46,  2, 20+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  47,  2, 47,  2, 21+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  48,  2, 48,  2, 22+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  49,  2, 49,  2, 23+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  50,  2, 50,  2, 24+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  51,  2, 51,  2, 25+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  52,  2, 52,  2, 26+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  53,  2, 53,  2, 27+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  54,  2, 54,  2, 28+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  55,  2, 55,  2, 29+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  56,  2, 56,  2, 30+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  57,  2, 57,  2, 31+12, invDEBI_quick_watch_mem_ascii_8

    @Hover                  42,  3, 42,  3, 32+12, invDEBI_quick_watch_mem_ascii_8    ; +32 - +47
    @Hover                  43,  3, 43,  3, 33+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  44,  3, 44,  3, 34+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  45,  3, 45,  3, 35+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  46,  3, 46,  3, 36+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  47,  3, 47,  3, 37+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  48,  3, 48,  3, 38+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  49,  3, 49,  3, 39+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  50,  3, 50,  3, 40+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  51,  3, 51,  3, 41+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  52,  3, 52,  3, 42+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  53,  3, 53,  3, 43+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  54,  3, 54,  3, 44+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  55,  3, 55,  3, 45+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  56,  3, 56,  3, 46+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  57,  3, 57,  3, 47+12, invDEBI_quick_watch_mem_ascii_8

    @Hover                  42,  4, 42,  4, 48+12, invDEBI_quick_watch_mem_ascii_8    ; +48 - +63
    @Hover                  43,  4, 43,  4, 49+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  44,  4, 44,  4, 50+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  45,  4, 45,  4, 51+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  46,  4, 46,  4, 52+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  47,  4, 47,  4, 53+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  48,  4, 48,  4, 54+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  49,  4, 49,  4, 55+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  50,  4, 50,  4, 56+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  51,  4, 51,  4, 57+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  52,  4, 52,  4, 58+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  53,  4, 53,  4, 59+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  54,  4, 54,  4, 60+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  55,  4, 55,  4, 61+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  56,  4, 56,  4, 62+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  57,  4, 57,  4, 63+12, invDEBI_quick_watch_mem_ascii_8

    @Hover                  42,  5, 42,  5, 64+12, invDEBI_quick_watch_mem_ascii_8    ; +64 - +79
    @Hover                  43,  5, 43,  5, 65+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  44,  5, 44,  5, 66+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  45,  5, 45,  5, 67+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  46,  5, 46,  5, 68+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  47,  5, 47,  5, 69+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  48,  5, 48,  5, 70+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  49,  5, 49,  5, 71+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  50,  5, 50,  5, 72+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  51,  5, 51,  5, 73+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  52,  5, 52,  5, 74+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  53,  5, 53,  5, 75+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  54,  5, 54,  5, 76+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  55,  5, 55,  5, 77+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  56,  5, 56,  5, 78+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  57,  5, 57,  5, 79+12, invDEBI_quick_watch_mem_ascii_8

    @Hover                  42,  6, 42,  6, 80+12, invDEBI_quick_watch_mem_ascii_8    ; +80 - +125
    @Hover                  43,  6, 43,  6, 81+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  44,  6, 44,  6, 82+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  45,  6, 45,  6, 83+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  46,  6, 46,  6, 84+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  47,  6, 47,  6, 85+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  48,  6, 48,  6, 86+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  49,  6, 49,  6, 87+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  50,  6, 50,  6, 88+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  51,  6, 51,  6, 89+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  52,  6, 52,  6, 90+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  53,  6, 53,  6, 91+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  54,  6, 54,  6, 92+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  55,  6, 55,  6, 93+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  56,  6, 56,  6, 94+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  57,  6, 57,  6, 95+12, invDEBI_quick_watch_mem_ascii_8

    @Hover                  42,  7, 42,  7, 96+12, invDEBI_quick_watch_mem_ascii_8    ; +126 - +111
    @Hover                  43,  7, 43,  7, 97+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  44,  7, 44,  7, 98+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  45,  7, 45,  7, 99+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  46,  7, 46,  7,100+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  47,  7, 47,  7,101+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  48,  7, 48,  7,102+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  49,  7, 49,  7,103+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  50,  7, 50,  7,104+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  51,  7, 51,  7,105+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  52,  7, 52,  7,106+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  53,  7, 53,  7,107+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  54,  7, 54,  7,108+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  55,  7, 55,  7,109+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  56,  7, 56,  7,110+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  57,  7, 57,  7,111+12, invDEBI_quick_watch_mem_ascii_8

    @Hover                  42,  8, 42,  8,112+12, invDEBI_quick_watch_mem_ascii_8    ; +112 - +127
    @Hover                  43,  8, 43,  8,113+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  44,  8, 44,  8,114+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  45,  8, 45,  8,115+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  46,  8, 46,  8,116+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  47,  8, 47,  8,117+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  48,  8, 48,  8,118+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  49,  8, 49,  8,119+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  50,  8, 50,  8,120+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  51,  8, 51,  8,121+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  52,  8, 52,  8,122+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  53,  8, 53,  8,123+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  54,  8, 54,  8,124+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  55,  8, 55,  8,125+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  56,  8, 56,  8,126+12, invDEBI_quick_watch_mem_ascii_8
    @Hover                  57,  8, 57,  8,127+12, invDEBI_quick_watch_mem_ascii_8



;.IF (ds:already_here == 1)
;    ret
;.ENDIF
;mov ds:already_here,1
;mov ds:object_mode,0
;mov ds:debug_screen_shown,1
;mov ds:mouse_status,0
;int 3