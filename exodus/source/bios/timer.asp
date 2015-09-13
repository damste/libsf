; timer.asp
;
; Exodus BIOS Timer related functions
;







timer_busy      dd  0


    TIMER_handler   PROC
    ; This routine is the timer interrupt handler
    ;
    ; Upon entry:   The timer has just fired
    ;
    ; Upon exit:    All the necessary routines are called
    ;
        push    ds
        push    eax

        mov     eax,_sSYSTEM
        mov     ds,eax
      ; Increment 1/182 of a second
        inc     byte ptr ds:[_SYSTEM_182S_OF_A_SECOND]
        cmp     byte ptr ds:[_SYSTEM_182S_OF_A_SECOND],182
        jb      timer_continue
        mov     byte ptr ds:[_SYSTEM_182S_OF_A_SECOND],0
        inc     dword ptr ds:[_SYSTEM_SECONDS_SINCE_BOOTUP]
        inc     dword ptr ds:[_SYSTEM_SECONDS_SINCE_MIDNIGHT]

      timer_continue:
      ; Signal end of interrupt and allow interrupts again
        mov     al,020h
        out     020h,al
        sti

        .IF (cs:timer_busy == 0)
            mov     ds,cs:data_segment
            mov     ds:timer_busy,1
            .IF (ds:debi_timer_feed != 0)
              ; Tell Debi another tick has occurred
                call    fword ptr ds:_iDEBI_timer_interface
            .ELSE
              ; See if it's time to signal an event
;                sub     ds:mouse_immediate_count,1
;                .IF (carry?)
;                    push    edx
;                    mov     dl,ds:mouse_last_event
;                    call    invTASK_check_immediate
;                    pop     edx
;                .ENDIF
;
;                sub     ds:mouse_hovering_count,1
;                .IF (carry?)
;                    call    invTASK_check_hovering
;                .ENDIF
;
;                sub     ds:mouse_clicking_count,1
;                .IF (carry?)
;                    call    invTASK_check_objects_click
;                .ENDIF

              ; See if it's time for a task switch
                mov     eax,_sTASK_SYSTEM
                mov     ds,eax
                .IF (dword ptr ds:[_TASK_SYSTEM_CURRENT_TASK_OFFSET] != _FIRST_TASK_ENTRY)
                  ; It's not the main Exodus task
                    mov     eax,dword ptr ds:[_TASK_SYSTEM_CURRENT_TASK_OFFSET]
                    dec     byte ptr ds:[eax+_TASK_ENTRY_TICKS_LEFT]
                    .IF (carry?)
                      ; It's time for a task switch
                        cli                                         ; a CLI is required before a task switch
                        callg   _sTASK_SWITCH_TASK_GATE
                        sti                                         ; an STI is expected after a task switch
                    .ENDIF
                .ENDIF
            .ENDIF
            mov     ds,cs:data_segment
            mov     ds:timer_busy,0
        .ENDIF
        sti

        pop     eax
        pop     ds
        iretd
    TIMER_handler   ENDP




    invTIMER_system_event       PROC
    ; This routine handles the time-of-day functions (updated 182 times per second)
        ret
    invTIMER_system_event       ENDP




    invTIMER_set_interrupt_interval     PROC
    ; This routine sets a TIMER frequency.  It is only called by algorithms in this program
    ;
    ; Upon entry:   eax - desired interval (_PIT_FREQUENCY / interval = eax)
    ;
    ; Upon exit:    timer channel 0 is updated to the new frequency
    ;               updated - timer_max_hz
    ;               updated - timer_max_value
    ;
      ;; Setup timer 0 to the mode we're desiring
        mov     al,00110110b                                        ; 0011:011:0 - TIMER 0, mode 3, binary counter mode (16-bit)
        out     _PIT_MODE,al                                        ; Select channel/mode
        @IO_pause
        out     _PIT_0_BASE,al                                      ; Send low byte
        xchg    ah,al
        @IO_pause
        out     _PIT_0_BASE,al                                      ; Send high byte

        ret
    invTIMER_set_interrupt_interval     ENDP




    iTIMER_activate_DEBI_timer_feed     PROC
    ; This routine is called by DEBI to indicate that a timer feed is requested
    ; The timer gives iDEBI_timer_interface() a call 18.2 times per second
    ;
    ; Upon entry:   Nothing
    ;
    ; Upon exit:    The timer feed begins
    ;
        push    ds
        mov     ds,cs:data_segment
        mov     ds:debi_timer_feed,1
        mov     ds:debi_timer_counter,0
        pop     ds
        retf
    iTIMER_activate_DEBI_timer_feed     ENDP




    iTIMER_deactivate_DEBI_timer_feed       PROC
    ; This routine is called by DEBI to indicate that a timer feed is requested
    ; The timer gives iDEBI_timer_interface() a call 18.2 times per second
    ;
    ; Upon entry:   Nothing
    ;
    ; Upon exit:    The timer feed is stopped
    ;
        push    ds
        mov     ds,cs:data_segment
        mov     ds:debi_timer_feed,0
        pop     ds
        retf
    iTIMER_deactivate_DEBI_timer_feed       ENDP




    TIMER_wait_next_tick    PROC
    ; This routine waits for the next system tick to come
        pushfd
        push    eax
        push    esi
        push    ds

    ;; Setup ds to point to the system memory area
        mov     eax,_sSYSTEM
        mov     ds,ax
        mov     esi,_SYSTEM_182S_OF_A_SECOND

    ;; Wait for change
        mov     al,byte ptr ds:[esi]
      @@:
        cmp     byte ptr ds:[esi],al
        jz      @B

    ;; We're done
        pop     ds
        pop     esi
        pop     eax
        popfd
        retf
    TIMER_wait_next_tick    ENDP




    TIMER_wait_full_tick    PROC
    ; This routine waits for one full system tick to go by
    ;
    ; Upon entry:   Nothing
    ;
    ; Upon exit:    At least one full tick has passed
    ;
    ; * Note:  This algorithm waits for two tick changes because it's never known how close to the end of the first tick we were
    ;          when this routine was called.  The only way to be sure we've waited at least one full tick is to wait for two.
    ;
        push    eax
        push    esi
        push    ds
        pushfd

      ;; Setup ds to point to the system memory area
        mov     eax,_sSYSTEM
        mov     ds,ax
        mov     esi,_SYSTEM_182S_OF_A_SECOND

      ;; Wait for first change
        mov     al,byte ptr ds:[esi]
      @@:
        cmp     byte ptr ds:[esi],al
        jz      @B

      ;; Wait for second change
        mov     al,byte ptr ds:[esi]
      @@:
        cmp     byte ptr ds:[esi],al
        jz      @B

      ;; We're done
        popfd
        pop     ds
        pop     esi
        pop     eax
        retf
    TIMER_wait_full_tick    ENDP




    TIMER_wait_x_ticks      PROC
    ; This routine waits for a user-specified number of ticks to go by (this is 1/182 of a second)
    ;
    ; Upon entry:   param1 - Number of ticks to wait
    ;
      ; [ebp+12] - dword, Number of ticks to wiat
      ; [ebp+08] - dword, cs
      ; [ebp+04] - dword, eip
      ; [ebp+00] - dword, ebp
        enter   0,0
        push    eax
        push    esi
        push    ds
        push    ecx
        pushfd

        mov     eax,_sSYSTEM
        mov     ds,eax
        mov     esi,_SYSTEM_182S_OF_A_SECOND

      ;; Get the count parameter
        mov     ecx,dword ptr ss:[ebp+12]
        inc     ecx                                                 ; +1 for the reasons stated in TIMER_wait_full_tick()
      wait_x_ticks_loop:
        mov     al,byte ptr ds:[esi]
      @@:
        cmp     byte ptr ds:[esi],al
        jz      @B
        loopd   wait_x_ticks_loop                                   ; Wait until their count has gone away

        popfd
        pop     ecx
        pop     ds
        pop     esi
        pop     eax
        leave
        retf    4
    TIMER_wait_x_ticks      ENDP




    TIMER_evaluate_interval     PROC
    ; This routine evalutes a timer interval to report its inconsistencies
    ;
    ; Upon entry:  The stack is arranged as below
    ;
    ; Upon exit:   Values on the stack are updated, everything else is preserved
    ;
    ; The formula is:   counter_value = PIT_freq / their_interval (which is "User's desired frequency" on the stack)
    ;                   percent = (counter_value-integer_part(counter_value)) / counter_value
    ;                   gain_loss = percent * their_interval
    ;                   double_interval = their_interval / gain_loss
    ;
    ; Example:     44100 Hz;   counter_value = 1193181 / 44100      = 27.0562585
    ;                          percent = (27.0562585 - 27) / 44100  = 0.00207932
    ;                          gain_loss = 0.00207932 * 44100       = 91.6978229
    ;                          odd_interval = 44100 / 91.6978229    = 481
    ;
      ; [ebp+28] - float32,   actual_interval                       ; result
      ; [ebp+24] - float32,   gain_loss                             ; result
      ; [ebp+20] - float32,   odd_interval                          ; result
      ; [ebp+16] - float32,   User's desired frequency              ; parameter
      ; [ebp+12] - cs
      ; [ebp+08] - eip
      ; [ebp+04] - eflags
      ; [ebp+00] - ebp
      ;; Save FPU state
        fwait
        fnsave  ss:[ebp-120]

        pushfd
        enter   4+4+4+108,0                                         ; Add space on stack for local variables
      ; [ebp-04] - dword,     const PIT frequency                   ; local (4)
      ; [ebp-08] - float32,   PIT_freq / their_interval             ; local (4)
      ; [ebp-12] - dword,     const 100,000                         ; local (4)
      ; [ebp-120]- 108 bytes, FPU save state                        ; local (108)

      ;; Calculate gain_loss and odd_interval
        mov     dword ptr ss:[ebp-4],_PIT_FREQUENCY
        mov     dword ptr ss:[ebp-12],100000
        fld     real4 ptr ss:[ebp+16]                               ; their frequency       After this block:   st(3)
        fld     st(0)                                               ; their frequency                           st(2)
        fild    dword ptr ss:[ebp-4]                                ; PIT frequency                             st(1)
        fld     st(1)                                               ; their frequency                           st(0)

        fdivp   st(1),st(0)                                         ; After this, st(0) - PIT_freq / their_interval
        fst     real4 ptr ss:[ebp-8]
        fld     st(0)
        fld     st(0)                                               ; st(1) and st(2) are copies of st(0)
        frndint                                                     ; After this, we lose the fraction in st(0)
        fsubp   st(1),st(0)                                         ; After this, st(0) is the fractional portion left over
                                                                    ;             negative means loss, positive means gain
        fdivrp  st(1),st(0)                                         ; After this, st(0) is the % off the desired interval
        fmulp   st(1),st(0)                                         ; After this, st(0) is # of cycles gaining/losing per second

      ;; Store results
        fst     real4 ptr ss:[ebp+24]                               ; result; gain_loss
        fdivp   st(1),st(0)                                         ; After this, st(0) holds the double-increment value
        fstp    real4 ptr ss:[ebp+20]                               ; result; odd_interval

      ;; Calculate actual_interval
        fild    dword ptr ss:[ebp-4]                                ; Load PIT frequency
        fild    dword ptr ss:[ebp-12]                               ; Load 100,000
        fmulp   st(1),st(0)                                         ; After this, st(0) is PIT frequency * 100000

        fld     real4 ptr ss:[ebp+16]                               ; Load PIT_freq / their interval
        fild    dword ptr ss:[ebp-4]                                ; Load 100,000
        fmulp   st(1),st(0)                                         ; After this, st(0) is (PIT_freq / their_interval) * 100000

        fdivp   st(1),st(0)                                         ; After this, st(0) is actual frequency
      ;; Store result
        fstp    real4 ptr ss:[ebp+28]                               ; result; actual_frequency

      ;; Restore the FPU and return
        frstor  ss:[ebp-120]

        leave
        popfd
        retf    4
    TIMER_evaluate_interval     ENDP




; DATA
    timer_max_hz                            dd  0
    timer_max_value                         dq  0
    timer_interval                          real4 182.064971924
    debi_timer_feed                         dd  0
    debi_timer_counter                      dd  0