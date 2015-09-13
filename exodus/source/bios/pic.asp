; pic.asp
;
; Exodus Programmable Interrupt Controller routines
;
;   iPIC_redirect_irq()    - Redirects IRQ vectors to point to a new interrupt
;   iPIC_mask_irq()        - Masks a particular IRQ from initiating interrupts
;   iPIC_unmask_irq()      - Undoes a previous mask
;   iPIC_mask_all_irqs()   - Masks all IRQs
;   iPIC_unmask_all_irqs() - Unmasks all IRQs
;
; * Note:  These are all local routines (there are no CALL GATES to these functions)
;


iPIC_redirect_irq   PROC
; This routine re-maps the IRQ interrupts to the desired range
;
; Upon entry:   ah = 0 or 1             (0-Master PIC, 1-Slave PIC)
;               bl = New Interrupt      (00h, 10h, 20h, 30h, etc.)
;
    pusha
;; Setup the appropriate port values for the requested PIC
    .IF (ah == 0)
        mov     dx,_PIC_21h                                         ; 8259-1 (master)
        mov     cx,_PIC_20h
    .ELSE
        mov     dx,_PIC_A1h                                         ; 8259-2 (slave)
        mov     cx,_PIC_A0h
    .ENDIF

;; Read interrupt mask
    in      al,dx                                                   ; Read the current mask (we restore this below)
    mov     ah,al
    @IO_pause

;; Disable interrupts
    cli

;; Command 1
    xchg    dx,cx
    mov     al,11h                                                  ; Cascade, require 4th init byte in this sequence
    out     dx,al
    @IO_pause

;; Command 2
    xchg    dx,cx
    mov     al,bl                                                   ; User defined interrupt redirect value
    and     al,11111000b                                            ; Mask off lower 3 bits (they're not used here)
    out     dx,al
    @IO_pause

;; Command 3
    .IF (dx >= _PIC_A0h)
      ; slave controller receives value 2 here
        mov     al,010b                                             ; Slave controller ID (value of 2 indicates IRQ2)
    .ELSE
      ; master controller receives value 4 here
        mov     al,0100b                                            ; Slave controller on IRQ 2
    .ENDIF
    out     dx,al
    @IO_pause

;; Command 4
    mov     al,1                                                    ; Normal EOI, nonbuffered, 80x86
    out     dx,al
    @IO_pause

;; Restore original interrupt mask register
    mov     al,ah
    out     dx,al

;; Enable interrupts
    sti

;; Finished
    popa
    ret
iPIC_redirect_irq   ENDP



iPIC_mask_irq       PROC
; This routine masks a specific IRQ
;
; Upon entry:   ah = IRQ # to mask
;
    .IF (ah <= 15)
        pusha
;; Setup the appropriate port values
        mov     dx,_PIC_21h                                         ; Default to 8259-1 (master)
        .IF (ah >= 8)
            mov     dx,_PIC_A1h                                     ; Nope, it's 8259-2 (slave)
            sub     ah,8                                            ; Subtract 8 (makes IRQ #'s 8-15 appear as 0-7, used below)
        .ENDIF
;; Get current mask values
        in      al,dx
        .IF (ah == 0)
            or      al,1b                                           ; Mask IRQ 0/8
        .ELSEIF (ah == 1)
            or      al,10b                                          ; Mask IRQ 1/9
        .ELSEIF (ah == 2)
            or      al,100b                                         ; Mask IRQ 2/10
        .ELSEIF (ah == 3)
            or      al,1000b                                        ; Mask IRQ 3/11
        .ELSEIF (ah == 4)
            or      al,10000b                                       ; Mask IRQ 4/12
        .ELSEIF (ah == 5)
            or      al,100000b                                      ; Mask IRQ 5/13
        .ELSEIF (ah == 6)
            or      al,1000000b                                     ; Mask IRQ 6/14
        .ELSE
            or      al,10000000b                                    ; Mask IRQ 7/15
        .ENDIF
;; Set the new mask values
        out     dx,al

;; Finished
        popa
    .ENDIF
    ret
iPIC_mask_irq       ENDP



iPIC_unmask_irq     PROC
; This routine un-masks a specific IRQ
;
; Upon entry:   ah = IRQ # to unmask
;
    .IF (ah <= 15)
        pusha
;; Setup the appropriate port values
        mov     dx,_PIC_21h                                         ; Default to 8259-1 (master)
        .IF (ah >= 8)
            mov     dx,_PIC_A1h                                     ; Nope, it's 8259-2 (slave)
            sub     ah,8                                            ; Subtract 8 (makes IRQ #'s 8-15 appear as 0-7, used below)
        .ENDIF
;; Get current mask values
        in      al,dx
        .IF (ah == 0)
            and     al,not 1b                                       ; Unmask IRQ 0/8
        .ELSEIF (ah == 1)
            and     al,not 10b                                      ; Unmask IRQ 1/9
        .ELSEIF (ah == 2)
            and     al,not 100b                                     ; Unmask IRQ 2/10
        .ELSEIF (ah == 3)
            and     al,not 1000b                                    ; Unmask IRQ 3/11
        .ELSEIF (ah == 4)
            and     al,not 10000b                                   ; Unmask IRQ 4/12
        .ELSEIF (ah == 5)
            and     al,not 100000b                                  ; Unmask IRQ 5/13
        .ELSEIF (ah == 6)
            and     al,not 1000000b                                 ; Unmask IRQ 6/14
        .ELSE
            and     al,not 10000000b                                ; Unmask IRQ 7/15
        .ENDIF
;; Set the new mask values
        out     dx,al

;; Finished
        popa
    .ENDIF
    ret
iPIC_unmask_irq     ENDP



iPIC_mask_all_irqs      PROC
; This routine masks all IRQs (disables them)
;
; Upon entry:   ah = 0 or 1             (0-Master PIC, 1-Slave PIC)
;
    push    ax
    push    dx

;; Setup the appropriate port values
    .IF (ah == 0)
        mov     dx,_PIC_21h                                         ; 8259-1 (master)
    .ELSE
        mov     dx,_PIC_A1h                                         ; 8259-2 (slave)
    .ENDIF

;; Set the new mask values
    mov     al,0ffh                                                 ; Disable all
    out     dx,al

;; Finished
    pop     dx
    pop     ax
    ret
iPIC_mask_all_irqs      ENDP



iPIC_unmask_all_irqs    PROC
; This routine unmasks all IRQs (enables them)
;
; Upon entry:   ah = 0 or 1             (0-Master PIC, 1-Slave PIC)
;
    push    ax
    push    dx

;; Setup the appropriate port values
    .IF (ah == 0)
        mov     dx,_PIC_21h                                         ; 8259-1 (master)
    .ELSE
        mov     dx,_PIC_A1h                                         ; 8259-2 (slave)
    .ENDIF

;; Set the new mask values
    xor     al,al                                                   ; Enable all
    out     dx,al

;; Finished
    pop     dx
    pop     ax
    ret
iPIC_unmask_all_irqs    ENDP



initialize_pic  PROC
; This routine initializes the PIC to ensure it's setup correctly
    mov     esi,offset initializing_pic
    call    iVT_display_string_vga

;; Redirect master PIC to 70h-77h
    mov     ah,0
    mov     bl,70h
    call    iPIC_redirect_irq
;; Redirect slave PIC to 78h-7fh
    mov     ah,1
    mov     bl,78h
    call    iPIC_redirect_irq
;; Unmask all IRQ's on master PIC
    mov     ah,0
    call    iPIC_unmask_all_irqs
;; Unmask all IRQ's on slave PIC
    mov     ah,1
    call    iPIC_unmask_all_irqs
;; Enable NMI IRQ2 interrupt
    xor     al,al                                                   ; High bit is the only one that matters, 0-enables, 1-masks
    out     _PIC_70h,al

    mov     esi,offset initialized_ok
    call    iVT_display_string_nr_vga
    ret
initialize_pic  ENDP