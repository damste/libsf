; bios.asm
;
; 旼컴컴컴컴컴컴컴�
; � standard BIOS �
; 읕컴컴컴컴컴컴컴�
;
; Exodus native primative BIOS functions
;

TITLE standard BIOS Driver

    .MODEL tiny

    .STACK 0h

INCLUDE \exodus\source\common\equates.asp
INCLUDE \exodus\source\common\macros.asp
INCLUDE \exodus\source\common\errors.asp
INCLUDE \exodus\source\common\objects.asp
INCLUDE bios_eq.asp
INCLUDE task_eq.asp
INCLUDE obj_eq.asp


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

            mov     esi,offset this_drivers_primatives      ; Offset to the native primatives structure
            mov     edi,offset driver_name
            mov     ebx,offset version
            mov     edx,offset copyright
            mov     ebp,offset author
            clc
        .ELSEIF (eax == 'prim')
          ; Native primatives this program will use
            mov     ds:data_segment,ds
            mov     esi,offset required_primatives                  ; This primative requires these external influence
            mov     edi,offset primative_call_gates
            clc
        .ELSEIF (eax == 'id  ')
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




    initialize_driver   PROC
    ; This routine is used to initialize the driver
    ;
    ; Upon entry:   Nothing
    ;
    ; Upon exit:    The BIOS logo is displayed
    ;
        call    initialize_TASKING
        call    initialize_PIC
        call    initialize_TIMER

      ;; Display the BIOS logo
        mov     esi,offset bios_logo
        call    fword ptr cs:_VID_draw_logo

        clc
        ret
    initialize_driver   ENDP




    initialize_PIC      PROC
    ; This routine initializes the PIC to the bootup state Exodus expects/relies upon
    ;
    ; Upon entry:   Nothing
    ;
    ; Upon exit:    Nothing
    ;
        pushad

      ;; Redirect master IRQs to INT 70h-77h
        mov     ah,0
        mov     bl,70h
        callf   BIOS_iPIC_redirect_irq
      ;; Unmask all IRQ's on master
        mov     ah,0
        callf   BIOS_iPIC_unmask_all_irqs

      ;; Redirect slave IRQs to INT 78h-7fh
        mov     ah,1
        mov     bl,78h
        callf   BIOS_iPIC_redirect_irq
      ;; Unmask all IRQ's on slave
        mov     ah,1
        callf   BIOS_iPIC_unmask_all_irqs

      ;; Enable NMI interrupts
        xor     al,al                                               ; High bit is the only one that matters, 0-enables, 1-masks
        out     _PIC_70h,al

        popad
        ret
    initialize_PIC      ENDP




    initialize_TIMER    PROC
    ; This routine initializes the timer to ensure it's setup correctly
    ;
    ; Upon entry:   Nothing
    ;
    ; Upon exit:    Nothing
    ;
    ; Initialize the timer memory to have one event which goes to the system event (for task switching and clock maintenance)
    ;
    ; * Note:  The manner in which we reprent the 182 ticks per second is not exact.  This is due to the fact that the minimum
    ;          firing time the timer can execute is when it contains a count value of 0xffff, which represents 18.2064971924 ticks
    ;          per second.  However, when we multiply that frequency by 10, to get our ~182 times per second, we lose some ability
    ;          to store the exact value in the timer.  This is due to the fact that ~18.2 ticks = 0xffff, and ~182 ticks = 1999h
    ;          with .6 (in base 10) remaining, or approximately 9.6 (in base 16).  So the actual value we need for the timer is
    ;          1999.96h, but since we can't load decimals we are forced to round.  This creates a problem of the timer not truly
    ;          firing at the rate of 182.064971924 (as it should).  So, to compensave for this, we take the actual value and
    ;          divide it by the calculated value, that yields a result of 0.999923710711 (6553.6 / 6554), which we then multiply
    ;          by our timer constant (119318100000) to obtain our actual add frequency of 119308997307 (which is slightly less
    ;          then our actual value).  This will cause the timer to not fire exactly as often, thereby compensating for the
    ;          difference.  119308997307 = 1bc75ed2bah
    ;
        pushad

      ;; Set the timer to interrupt 182Hz
        mov     eax,1999h
        call    invTIMER_set_interrupt_interval

      ;; Setup the TASK GATE in the IDT (point IRQ0 to the timer ISR)
        mov     eax,'bint'
        mov     bl,70h                                              ; INT 70h
        mov     ecx,1
        mov     edx,offset TIMER_handler
        call    fword ptr ds:_EXODUS_requestor

        popad
        ret
    initialize_TIMER    ENDP




    BIOS_iPIC_redirect_irq      PROC
    ; This routine re-maps the IRQ interrupts to the desired range
    ;
    ; Upon entry:   ah = 0 or 1             (0-Master PIC, 1-Slave PIC)
    ;               bl = New Interrupt      (00h, 10h, 20h, 30h, etc.)
    ;
        pushad
    ;; Setup the appropriate port values for the requested PIC
        .IF (ah == 0)
            mov     edx,_PIC_21h                                    ; 8259-1 (master)
            mov     ecx,_PIC_20h
        .ELSE
            mov     edx,_PIC_A1h                                    ; 8259-2 (slave)
            mov     ecx,_PIC_A0h
        .ENDIF

    ;; Read interrupt mask
        in      al,dx                                               ; Read the current mask (we restore this below)
        mov     ah,al
        @IO_pause

    ;; Disable interrupts
        cli

    ;; Command 1
        xchg    edx,ecx
        mov     al,11h                                              ; Cascade, require 4th init byte in this sequence
        out     dx,al
        @IO_pause

    ;; Command 2
        xchg    edx,ecx
        mov     al,bl                                               ; User defined interrupt redirect value
        and     al,11111000b                                        ; Mask off lower 3 bits (they're not used here)
        out     dx,al
        @IO_pause

    ;; Command 3
        .IF (edx >= _PIC_A0h)
          ; slave controller receives value 2 here
            mov     al,010b                                         ; Slave controller ID (value of 2 indicates IRQ2)
        .ELSE
          ; master controller receives value 4 here
            mov     al,0100b                                        ; Slave controller on IRQ 2
        .ENDIF
        out     dx,al
        @IO_pause

    ;; Command 4
        mov     al,1                                                ; Normal EOI, nonbuffered, 80x86
        out     dx,al
        @IO_pause

    ;; Restore original interrupt mask register
        mov     al,ah
        out     dx,al

    ;; Enable interrupts
        sti

    ;; Finished
        popad
        retf
    BIOS_iPIC_redirect_irq      ENDP




    BIOS_iPIC_mask_irq      PROC
    ; This routine masks a specific IRQ
    ;
    ; Upon entry:   ah = IRQ # to mask
    ;
        .IF (ah <= 15)
            pushad
          ;; Setup the appropriate port values
            mov     edx,_PIC_21h                                    ; Default to 8259-1 (master)
            .IF (ah >= 8)
                mov     edx,_PIC_A1h                                ; Nope, it's 8259-2 (slave)
                sub     ah,8                                        ; Subtract 8 (makes IRQ #'s 8-15 appear as 0-7, used below)
            .ENDIF
          ;; Get current mask values
            in      al,dx
            .IF (ah == 0)
                or      al,1b                                       ; Mask IRQ 0/8
            .ELSEIF (ah == 1)
                or      al,10b                                      ; Mask IRQ 1/9
            .ELSEIF (ah == 2)
                or      al,100b                                     ; Mask IRQ 2/10
            .ELSEIF (ah == 3)
                or      al,1000b                                    ; Mask IRQ 3/11
            .ELSEIF (ah == 4)
                or      al,10000b                                   ; Mask IRQ 4/12
            .ELSEIF (ah == 5)
                or      al,100000b                                  ; Mask IRQ 5/13
            .ELSEIF (ah == 6)
                or      al,1000000b                                 ; Mask IRQ 6/14
            .ELSE
                or      al,10000000b                                ; Mask IRQ 7/15
            .ENDIF
          ;; Set the new mask values
            out     dx,al

          ;; Finished
            popad
        .ENDIF
        retf
    BIOS_iPIC_mask_irq      ENDP




    BIOS_iPIC_unmask_irq    PROC
    ; This routine un-masks a specific IRQ
    ;
    ; Upon entry:   ah = IRQ # to unmask
    ;
        .IF (ah <= 15)
            pushad
          ;; Setup the appropriate port values
            mov     edx,_PIC_21h                                    ; Default to 8259-1 (master)
            .IF (ah >= 8)
                mov     edx,_PIC_A1h                                ; Nope, it's 8259-2 (slave)
                sub     ah,8                                        ; Subtract 8 (makes IRQ #'s 8-15 appear as 0-7, used below)
            .ENDIF
          ;; Get current mask values
            in      al,dx
            .IF (ah == 0)
                and     al,not 1b                                   ; Unmask IRQ 0/8
            .ELSEIF (ah == 1)
                and     al,not 10b                                  ; Unmask IRQ 1/9
            .ELSEIF (ah == 2)
                and     al,not 100b                                 ; Unmask IRQ 2/10
            .ELSEIF (ah == 3)
                and     al,not 1000b                                ; Unmask IRQ 3/11
            .ELSEIF (ah == 4)
                and     al,not 10000b                               ; Unmask IRQ 4/12
            .ELSEIF (ah == 5)
                and     al,not 100000b                              ; Unmask IRQ 5/13
            .ELSEIF (ah == 6)
                and     al,not 1000000b                             ; Unmask IRQ 6/14
            .ELSE
                and     al,not 10000000b                            ; Unmask IRQ 7/15
            .ENDIF
          ;; Set the new mask values
            out     dx,al

          ;; Finished
            popad
        .ENDIF
        retf
    BIOS_iPIC_unmask_irq    ENDP




    BIOS_iPIC_mask_all_irqs     PROC
    ; This routine masks all IRQs (disables them)
    ;
    ; Upon entry:   ah = 0 or 1             (0-Master PIC, 1-Slave PIC)
    ;
        push    eax
        push    edx

      ;; Setup the appropriate port values
        .IF (ah == 0)
            mov     dx,_PIC_21h                                     ; 8259-1 (master)
        .ELSE
            mov     dx,_PIC_A1h                                     ; 8259-2 (slave)
        .ENDIF

      ;; Set the new mask values
        mov     al,0ffh                                             ; Disable all
        out     dx,al

      ;; Finished
        pop     edx
        pop     eax
        retf
    BIOS_iPIC_mask_all_irqs     ENDP




    BIOS_iPIC_unmask_all_irqs       PROC
    ; This routine unmasks all IRQs (enables them)
    ;
    ; Upon entry:   ah = 0 or 1             (0-Master PIC, 1-Slave PIC)
    ;
        push    eax
        push    edx

      ;; Setup the appropriate port values
        .IF (ah == 0)
            mov     dx,_PIC_21h                                     ; 8259-1 (master)
        .ELSE
            mov     dx,_PIC_A1h                                     ; 8259-2 (slave)
        .ENDIF

      ;; Set the new mask values
        xor     al,al                                               ; Enable all
        out     dx,al

      ;; Finished
        pop     edx
        pop     eax
        retf
    BIOS_iPIC_unmask_all_irqs       ENDP




    iBIOS_read_8042_64h     PROC
    ; This routine reads one byte from port 60h into al
        in      al,064h
        callf   TIMER_wait_full_tick
        retf
    iBIOS_read_8042_64h     ENDP




    iBIOS_read_8042_60h     PROC
    ; This routine reads the byte in from port 60h to al
        push    ecx
        xor     ecx,ecx
      @@:
        callf   iBIOS_read_8042_64h                                 ; Wait for bit 0 of port (64h) to become zero before reading
        shr     al,1
        jc      @F
        loope   @B
      @@:
        callf   TIMER_wait_full_tick
        in      al,060h
        pop     ecx
        retf
    iBIOS_read_8042_60h     ENDP




    iBIOS_write_8042_64h    PROC
    ; This routine writes a byte to port 64h
        callf   TIMER_wait_full_tick
        mov     al,ah
        out     064h,al
        retf
    iBIOS_write_8042_64h    ENDP




    iBIOS_write_8042_60h    PROC
    ; This routine writes the byte in ah to port 60h
        push    ecx
        xor     ecx,ecx
      @@:
        callf   iBIOS_read_8042_64h                                 ; Wait for bit 1 of port (64h) to become zero before writing
        shr     al,2
        jnc     @F
        loope   @B
      @@:
        callf   TIMER_wait_full_tick
        mov     al,ah                                               ; Write it
        out     060h,al
        callf   TIMER_wait_full_tick
        pop     ecx
        retf
    iBIOS_write_8042_60h      ENDP




    iBIOS_read_8042_64h_fast    PROC
    ; This routine reads one byte from port 60h into al
        in      al,064h
        jmp     $+2
        retf
    iBIOS_read_8042_64h_fast    ENDP




    iBIOS_read_8042_60h_fast    PROC
    ; This routine reads the byte in from port 60h to al
        push    ecx
        xor     ecx,ecx
      @@:
        callf   iBIOS_read_8042_64h_fast                            ; Wait for bit 0 of port (64h) to become zero before reading
        shr     al,1
        jc      @F
        loope   @B
      @@:
        in      al,060h
        jmp     $+2
        pop     ecx
        retf
    iBIOS_read_8042_60h_fast    ENDP




    iBIOS_write_8042_64h_fast   PROC
    ; This routine writes a byte to port 64h
        mov     al,ah
        out     064h,al
        retf
    iBIOS_write_8042_64h_fast   ENDP




    iBIOS_write_8042_60h_fast   PROC
    ; This routine writes the byte in ah to port 60h
        mov     al,ah                                               ; Write it
        out     060h,al
        retf
    iBIOS_write_8042_60h_fast   ENDP




    BIOS_requestor      PROC
    ; This routine is used to answer queries by other applications
    ; * Refer to source\inf\requestr.inf for more information
    ;
    ; Upon entry:   eax = request number
    ;               stack is appropriately setup based on request
    ;
    ; Upon exit:    various registers might be updated
    ;
        retf
    BIOS_requestor      ENDP




    INCLUDE timer.asp
    INCLUDE tasks.asp
    INCLUDE objects.asp





; DATA
    driver_name                             db  "Motherboard BIOS Driver",0
    version                                 db  "10.10.2010",0
    copyright                               db  "(c) Copyright Beatleworks, Inc.",0
    author                                  db  "Rick C. Hodgin",0
    bootup                                  db  1                   ; Indicates bootup status, changes to 0 after initialization
    data_segment                            dw  0

; CALL GATES
    _EXODUS_requestor                       dw  0
  primative_call_gates:
    _VID_draw_logo                          dw  0
    _VID_display_string_nr_vga              dw  _sEXODUS_REQUESTOR
    _iDEBI_timer_interface                  dw  0f000h
    _VID_g_derive_color                     dw  0f000h
    _VID_g_fill_rectangle                   dw  0f000h
    _VID_g_draw_text                        dw  0f000h
    _VID_g_display_radix_in_edx_mono        dw  0f000h
    _VID_g_mouse_pointer                    dw  0f000h
                                            dw  0f000h
                                            dw  0f000h

; DATA only used at load time (released thereafter)
    required_primatives                     db  13, "VID_draw_logo"
                                            db  25, "VID_display_string_nr_vga"
                                            db  21, "iDEBI_timer_interface"
                                            db  18, "VID_g_derive_color"
                                            db  20, "VID_g_fill_rectangle"
                                            db  15, "VID_g_draw_text"
                                            db  31, "VID_g_display_radix_in_edx_mono"
                                            db  19, "VID_g_mouse_pointer"
                                            db  0ffh

    bios_logo                               db  1       ; how many extra 18x16 pictures wide?
                                            db  00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
                                            db  07h,07h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
                                            db  00h,07h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h
                                            db  00h,07h,07h,02h,02h,02h,02h,02h,02h,02h,02h,02h,02h,02h,02h,02h,02h,02h,02h,02h,02h,02h,02h,02h,02h,02h,02h,02h,02h,02h,02h,02h,02h,02h,02h,02h,02h,00h
                                            db  00h,07h,07h,02h,02h,02h,02h,02h,02h,02h,02h,02h,02h,02h,02h,02h,02h,02h,0ah,0ah,0ah,0ah,0ah,0ah,0ah,0ah,0ah,0ah,02h,02h,02h,02h,07h,07h,07h,07h,02h,00h
                                            db  00h,07h,00h,02h,02h,07h,07h,07h,07h,07h,07h,07h,02h,02h,07h,07h,07h,07h,07h,07h,07h,07h,02h,02h,02h,02h,02h,0ah,0ah,0ah,0ah,0ah,07h,08h,08h,07h,02h,00h
                                            db  00h,07h,00h,02h,02h,07h,00h,00h,00h,00h,00h,07h,0ah,0ah,07h,00h,00h,00h,00h,00h,00h,07h,02h,02h,02h,02h,02h,02h,02h,02h,02h,02h,07h,07h,07h,07h,02h,00h
                                            db  00h,07h,00h,02h,02h,07h,00h,08h,08h,08h,00h,07h,02h,02h,07h,00h,08h,08h,08h,08h,00h,07h,02h,02h,02h,02h,07h,07h,07h,07h,07h,02h,02h,02h,0ah,02h,02h,00h
                                            db  00h,07h,00h,02h,02h,07h,00h,08h,08h,08h,00h,07h,0ah,0ah,07h,00h,08h,08h,08h,08h,00h,07h,0ah,0ah,0ah,0ah,07h,08h,08h,00h,07h,0ah,0ah,0ah,0ah,02h,02h,00h
                                            db  00h,07h,00h,02h,02h,07h,00h,00h,00h,00h,00h,07h,02h,02h,07h,00h,08h,08h,08h,08h,00h,07h,02h,02h,02h,02h,07h,00h,08h,08h,07h,02h,02h,02h,02h,02h,02h,00h
                                            db  00h,07h,00h,02h,02h,07h,07h,07h,07h,07h,07h,07h,02h,02h,07h,07h,07h,07h,07h,07h,07h,07h,0ah,0ah,0ah,0ah,07h,07h,07h,07h,07h,02h,02h,02h,02h,02h,02h,00h
                                            db  00h,07h,00h,02h,02h,02h,0ah,02h,02h,02h,02h,0ah,02h,02h,02h,02h,0ah,02h,02h,02h,02h,02h,02h,02h,02h,02h,02h,02h,02h,02h,02h,02h,02h,02h,02h,02h,02h,00h
                                            db  00h,07h,07h,02h,02h,02h,0ah,02h,02h,02h,02h,02h,0ah,02h,02h,02h,02h,0ah,02h,02h,02h,02h,02h,02h,02h,02h,02h,02h,02h,02h,02h,02h,02h,02h,02h,02h,02h,00h
                                            db  00h,07h,07h,02h,0eh,02h,0eh,02h,0eh,02h,0eh,02h,0eh,02h,0eh,02h,0eh,02h,02h,0eh,02h,0eh,02h,0eh,02h,0eh,02h,02h,02h,02h,02h,02h,02h,02h,02h,02h,02h,00h
                                            db  00h,07h,00h,02h,0eh,06h,0eh,06h,0eh,06h,0eh,06h,0eh,06h,0eh,06h,0eh,02h,02h,0eh,06h,0eh,06h,0eh,06h,0eh,02h,02h,02h,02h,02h,02h,02h,02h,02h,02h,02h,00h
                                            db  00h,07h,00h,00h,0eh,06h,0eh,06h,0eh,06h,0eh,06h,0eh,06h,0eh,06h,0eh,00h,00h,0eh,06h,0eh,06h,0eh,06h,0eh,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h,00h

 end_of_required_data:
    this_drivers_primatives                 db  14, "BIOS_requestor"
                                            dd  offset BIOS_requestor
                                            dw  0

                                            db  22, "BIOS_iPIC_redirect_irq"
                                            dd  offset BIOS_iPIC_redirect_irq
                                            dw  0

                                            db  18, "BIOS_iPIC_mask_irq"
                                            dd  offset BIOS_iPIC_mask_irq
                                            dw  0

                                            db  20, "BIOS_iPIC_unmask_irq"
                                            dd  offset BIOS_iPIC_unmask_irq
                                            dw  0

                                            db  23, "BIOS_iPIC_mask_all_irqs"
                                            dd  offset BIOS_iPIC_mask_all_irqs
                                            dw  0

                                            db  25, "BIOS_iPIC_unmask_all_irqs"
                                            dd  offset BIOS_iPIC_unmask_all_irqs
                                            dw  0

                                            db  19, "iBIOS_read_8042_64h"
                                            dd  offset iBIOS_read_8042_64h
                                            dw  0

                                            db  19, "iBIOS_read_8042_60h"
                                            dd  offset iBIOS_read_8042_60h
                                            dw  0

                                            db  20, "iBIOS_write_8042_64h"
                                            dd  offset iBIOS_write_8042_64h
                                            dw  0

                                            db  20, "iBIOS_write_8042_60h"
                                            dd  offset iBIOS_write_8042_60h
                                            dw  0

                                            db  24, "iBIOS_read_8042_64h_fast"
                                            dd  offset iBIOS_read_8042_64h_fast
                                            dw  0

                                            db  24, "iBIOS_read_8042_60h_fast"
                                            dd  offset iBIOS_read_8042_60h_fast
                                            dw  0

                                            db  25, "iBIOS_write_8042_64h_fast"
                                            dd  offset iBIOS_write_8042_64h_fast
                                            dw  0

                                            db  25, "iBIOS_write_8042_60h_fast"
                                            dd  offset iBIOS_write_8042_60h_fast
                                            dw  0

                                            db  20, "TIMER_wait_next_tick"
                                            dd  offset TIMER_wait_next_tick
                                            dw  0

                                            db  20, "TIMER_wait_full_tick"
                                            dd  offset TIMER_wait_full_tick
                                            dw  0

                                            db  18, "TIMER_wait_x_ticks"
                                            dd  offset TIMER_wait_x_ticks
                                            dw  0

                                            db  31, "iTIMER_activate_debi_timer_feed"
                                            dd  offset iTIMER_activate_debi_timer_feed
                                            dw  0

                                            db  33, "iTIMER_deactivate_debi_timer_feed"
                                            dd  offset iTIMER_deactivate_debi_timer_feed
                                            dw  0

                                            db  14, "TASK_set_focus"
                                            dd  offset TASK_set_focus
                                            dw  0

                                            db  16, "TASK_read_events"
                                            dd  offset TASK_read_events
                                            dw  0

                                            db  22, "TASK_release_timeslice"
                                            dd  offset TASK_release_timeslice
                                            dw  0

                                            db  19, "iTASK_kbd_interface"
                                            dd  offset iTASK_kbd_interface
                                            dw  0

                                            db  25, "OBJECT_create_base_object"
                                            dd  offset OBJECT_create_base_object
                                            dw  0

                                            db  20, "OBJECT_create_object"
                                            dd  offset OBJECT_create_object
                                            dw  0

                                            db  29, "Exodus_TASK_release_timeslice"
                                            dd  offset Exodus_TASK_release_timeslice
                                            dw  0

                                            db  25, "iTASK_prevent_task_switch"
                                            dd  offset iTASK_prevent_task_switch
                                            dw  0

                                            db  23, "iTASK_allow_task_switch"
                                            dd  offset iTASK_allow_task_switch
                                            dw  0

                                            db  21, "iTASK_mouse_interface"
                                            dd  offset iTASK_mouse_interface
                                            dw  0

                                            dw  0ffffh              ; Teriminator

_TEXT32 ENDS

END
