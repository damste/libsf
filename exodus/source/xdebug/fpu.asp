; fpu.asp
;
; xDebug
; This routines updates the FPU variables on the display
;

show_fpu:
;
; Upon entry:   Nothing
;
; Upon exit:  everything is preserved
;
    pushad
    push    ds
    push    es

    mov     ax,cs
    mov     ds,ax
    mov     ax,0b000h
    mov     es,ax

    finit
    fld     real10 ptr save_fpu_state[14]
    mov     di,((80 * 8) + 2) * 2
    call    show_register_fpu

    fld     real10 ptr save_fpu_state[24]
    mov     di,((80 * 9) + 2) * 2
    call    show_register_fpu

    fld     real10 ptr save_fpu_state[34]
    mov     di,((80 * 10) + 2) * 2
    call    show_register_fpu

    fld     real10 ptr save_fpu_state[44]
    mov     di,((80 * 11) + 2) * 2
    call    show_register_fpu

    fld     real10 ptr save_fpu_state[54]
    mov     di,((80 * 8) + 34) * 2
    call    show_register_fpu

    fld     real10 ptr save_fpu_state[64]
    mov     di,((80 * 9) + 34) * 2
    call    show_register_fpu

    fld     real10 ptr save_fpu_state[74]
    mov     di,((80 * 10) + 34) * 2
    call    show_register_fpu

    fld     real10 ptr save_fpu_state[84]
    mov     di,((80 * 11) + 34) * 2
    call    show_register_fpu

    mov     bx,last_cw
    mov     dx,word ptr save_fpu_state[0]
    mov     di,((80 * 12) + 4) * 2
    call    show_register_16_binary

    mov     bx,last_sw
    mov     dx,word ptr save_fpu_state[2]
    mov     di,((80 * 12) + 24) * 2
    call    show_register_16_binary

    mov     bx,last_tw
    mov     dx,word ptr save_fpu_state[4]
    mov     di,((80 * 12) + 44) * 2
    call    show_register_16_binary

    pop     es
    pop     ds
    popad
    ret


show_register_fpu:
; This routine converts a 80-bit REAL into a string
;
; Upon Entry:      st0 - number to convert
;              es:[di] - where to display
;
; Upon Exit:  screen is updated
;
    mov     Exponent,0

    fxam                                                            ; Examine the # for weird values
    fstsw   fpu_stat
    mov     BX,fpu_stat

  ; Copy high bits to low.
    mov     bl,bh
    shr     bh,3
    and     bh,008h
    and     bl,007h
    or      bl,bh
  ; bl now has C3, C2, C1 and C0 in low 4 bits
    .if (bl == 0)
        mov     si,offset badnumber0
    .elseif (bl == 1)
        mov     si,offset badnumber1
    .elseif (bl == 2)
        mov     si,offset badnumber2
    .elseif (bl == 3)
        mov     si,offset badnumber3
;    .elseif (bl == 4)
;        mov     si,offset badnumber4
    .elseif (bl == 5)
        mov     si,offset badnumber5
;    .elseif (bl == 6)
;        mov     si,offset badnumber6
    .elseif (bl == 7)
        mov     si,offset badnumber7
    .elseif (bl == 8)
        mov     si,offset badnumber8
    .elseif (bl == 9)
        mov     si,offset badnumber9
    .elseif (bl == 10)
        mov     si,offset badnumber10
    .elseif (bl == 11)
        mov     si,offset badnumber11
    .elseif (bl == 12)
        mov     si,offset badnumber12
    .elseif (bl == 13)
        mov     si,offset badnumber13
    .elseif (bl == 14)
        mov     si,offset badnumber14
    .elseif (bl == 15)
        mov     si,offset badnumber13
    .else
        jmp     @f
    .endif
    .while (byte ptr [si] != 0)
        lodsb
        stosb
        mov     al,112
        stosb
    .endw
    fistp   dword ptr temp_buffer[0]
    ret

  @@:
  ; Is it greater than zero?
    ftst
    fstsw   AX
    mov     fpu_stat,AX
    sahf
    .IF (carry?)
      ; It is < than zero...Put a minus sign
        mov     al,"-"
        fchs
    .ELSE
      ; It is > than zero...Put a space (plus is the assumption if no sign)
        mov     al," "
    .ENDIF
    stosb
    mov     al,112
    stosb

    .REPEAT
        fld1
        fcomp
        fstsw   AX
        sahf
        .IF (!carry?)
            pushf
            dec     exponent
            fld     number10
            fmul
            popf
        .ENDIF
    .UNTIL carry?

  ; While the number is greater than or equal to 10, divide it by 10 and increment the exponent
    .REPEAT
        fcom    number10
        fstsw   AX
        sahf
        .IF (!carry?)
            pushf
            inc     exponent
            fld     number10
            fdivp   st(1),st
            popf
        .ENDIF
    .UNTIL carry?
  ; The value is now a number in the range of 1.0<=Number<10

  ; Apply rounding
    fld     point5
    mov     CX,19                                                   ; Round to 19 decimal places
    .REPEAT
        fld     number10
        fdivp   st(1),st
    .UNTILCXZ
  ; Now apply the rounding
    fadd
  ; Now set up rounding by chopping
    call    fpu_round_chop
    call    extract_digit                                           ; Get the first character

    mov     al,"."                                                  ; Store the decimal point
    stosb
    mov     al,112
    stosb

  ; Now get the 19 decimals
    mov     CX,19
    .REPEAT
        call    extract_digit
    .UNTILCXZ

  ; Now write the exponent
    .IF (exponent < 0)
      ; A negative exponent
        mov     al,"-"
    .ELSE
      ; A positive exponent
        mov     al,"+"
    .ENDIF
    stosb
    mov     al,112
    stosb

    mov     DX,exponent
    call    signed_convert_word_to_decimal
    fistp   dword ptr temp_buffer[0]
    ret

fpu_round_chop:
    fstcw   ControlWord
    and     ControlWord,1001111111111b
    or      ControlWord,0110000000000b
    fldcw   ControlWord
    ret

extract_digit:
    fld     st                                                      ; Duplicate st(0)
    frndint                                                         ; Round the duplicate
    fsub    st(1),st                                                ; Get the 'remainder' in st(1)
    fistp   digit                                                   ; Pop the integer into memory
    fld     number10                                                ; Multiply the remainder by 10
    fmul
    mov     AX,CS:Digit                                             ; Get the digit and convert it and write it
    add     al,"0"
    stosb
    mov     al,112
    stosb
    ret

signed_convert_word_to_decimal:
; Upon entry:  DX is a signed number
    .if (dx > 32768)
      ; it's a negative
        neg     dx
    .endif

    mov     si,offset temp_buffer+4
    mov     eax,"0000"
    mov     dword ptr [si-4],eax
    mov     dword ptr [si],eax
    mov     dword ptr [si+4],eax
    mov     bx,10
    mov     ax,dx
  @@:
    xor     dx,dx
    div     bx

    add     dl,030h
    mov     byte ptr [si],dl
    inc     si
    cmp     ax,0
    jnz     @B

    mov     cx,4
  @@:
    dec     si
    mov     al,byte ptr [si]
    stosb
    mov     al,112
    stosb
    loop    @B
    ret