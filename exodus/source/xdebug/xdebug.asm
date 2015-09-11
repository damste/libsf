; xdebug.asm
;
; xDebug - Exodus real mode debug program
;          * Note:  INT3 is redirected to this procedure
;

    .MODEL tiny

    .386

INCLUDE \assembly\keylist.asp                                       ; EQU List of all the keyboard scan codes
    .CODE
_XDEBUG     SEGMENT WORD PUBLIC 'CODE'
    ORG 0
    push    AX
    mov     al,20h
    out     20h,al
    pop     AX
    pushf                                                           ; Saved once
    .IF (CS:already_here == 1)
        popf                                                        ; Popped twice depending on branch
        sti
        iret
    .ENDIF
    popf                                                            ; Popped twice
    mov     CS:already_here,1
    mov     CS:current_sp,sp
    mov     CS:current_bp,bp

  ; Save all registers for the return
    fsave   CS:save_fpu_state
    pushad
    push    DS
    push    ES
    push    FS
    push    GS

    enter 38,0
  ; flags   - SS:[CS:current_sp+4]
  ; cs      - SS:[CS:current_sp+2]
  ; ip      - SS:[CS:current_sp+0]
  ; [bp+2],  word, bp
  ; [bp+0],  sp from "enter 38,0"
  ; [bp-4],  dword, eax
  ; [bp-8],  dword, ebx
  ; [bp-12], dword, ecx
  ; [bp-16], dword, edx
  ; [bp-20], dword, esi
  ; [bp-24], dword, edi
  ; [bp-28], dword, sp
  ; [bp-30], word, ds
  ; [bp-32], word, es
  ; [bp-34], word, fs
  ; [bp-36], word, gs
  ; [bp-38], word, ss

;; Save all registers not already saved
    mov     dword ptr [bp-4],eax
    mov     dword ptr [bp-8],ebx
    mov     dword ptr [bp-12],ecx
    mov     dword ptr [bp-16],edx
    mov     dword ptr [bp-20],esi
    mov     dword ptr [bp-24],edi
    mov     word ptr [bp-28],sp
    mov     word ptr [bp-30],ds
    mov     word ptr [bp-32],es
    mov     word ptr [bp-34],fs
    mov     word ptr [bp-36],gs
    mov     word ptr [bp-38],ss
    sti

  ; Setup our expected segment references
    mov     si,cs
    mov     ds,si
    mov     di,0b000h
    mov     es,di
  ; If it's the first time, setup all the current "last" values to whatever they are now (so the colors appear normal)
    .IF (CS:first_time == 0)
        mov     CS:first_time,1
        call    copy_debug_screen
        call    copy_current_to_last                                ; Initialize everything to the current color
        call    show_flags_status                                   ; Show it once so it will be non-highlighted next time
    .ENDIF

  ; Display all the registers
    call    display_registers
    call    show_stack
    call    display_disassembly
    call    show_fpu
    call    show_mem1
    call    show_mem2

  ; Wait for a key
  get_a_key:
    xor     ah,ah
    int     16h
    mov     bx,CS:current_sp
    .IF (AX == F8)
        or      word ptr SS:[bx+4],100000000b
    .ELSEIF (AX == F5 || AX == Escape)
        and     word ptr SS:[bx+4],not 100000000b
    .ELSE
        jmp     get_a_key
    .ENDIF

;; Copy current register values to the "last" register values
    call    copy_current_to_last

    leave
    frstor  CS:save_fpu_state
    pop     GS
    pop     FS
    pop     ES
    pop     DS
    popad
    mov     CS:already_here,0
    iret


;-----------------------------------------------
copy_debug_screen:
    mov     si,offset debug_screen
    xor     di,di
    mov     CX,25*80
    mov     ah,7
  @@:
    lodsb
    cmp     al,"פ"
    jz      make_reverse
    cmp     al,"ץ"
    jnz     store_it
    mov     ah,7
    jmp     @B
  make_reverse:
    mov     ah,112
    jmp     @B
  store_it:
    stosw
    loop    @B
    ret


;-----------------------------------------------
display_registers:
  ; eax
    mov     ebx,CS:last_eax
    mov     edx,dword ptr [bp-4]
    mov     di,(1*80 + 72) * 2
    call    show_register_32
  ; ebx
    mov     ebx,CS:last_ebx
    mov     edx,dword ptr [bp-8]
    mov     di,(2*80 + 72) * 2
    call    show_register_32
  ; ecx
    mov     ebx,CS:last_ecx
    mov     edx,dword ptr [bp-12]
    mov     di,(3*80 + 72) * 2
    call    show_register_32
  ; edx
    mov     ebx,CS:last_edx
    mov     edx,dword ptr [bp-16]
    mov     di,(4*80 + 72) * 2
    call    show_register_32
  ; esi
    mov     ebx,CS:last_esi
    mov     edx,dword ptr [bp-20]
    mov     di,(5*80 + 72) * 2
    call    show_register_32
  ; edi
    mov     ebx,CS:last_edi
    mov     edx,dword ptr [bp-24]
    mov     di,(6*80 + 72) * 2
    call    show_register_32
  ; ds
    mov     bx,CS:last_ds
    mov     dx,word ptr [bp-30]
    mov     di,(7*80 + 72) * 2
    call    show_register_16
  ; es
    mov     bx,CS:last_es
    mov     dx,word ptr [bp-32]
    mov     di,(8*80 + 72) * 2
    call    show_register_16
  ; fs
    mov     bx,CS:last_fs
    mov     dx,word ptr [bp-34]
    mov     di,(9*80 + 72) * 2
    call    show_register_16
  ; gs
    mov     bx,CS:last_gs
    mov     dx,word ptr [bp-36]
    mov     di,(10*80 + 72) * 2
    call    show_register_16
  ; ss
    mov     bx,CS:last_ss
    mov     dx,word ptr [bp-38]
    mov     di,(11*80 + 72) * 2
    call    show_register_16
  ; bp
    mov     bx,CS:last_bp
    mov     dx,CS:current_bp
    mov     di,(12*80 + 75) * 2
    call    show_register_16
  ; sp
    mov     bx,CS:last_sp
    mov     dx,CS:current_sp
    mov     di,(13*80 + 75) * 2
    call    show_register_16
  ; cs
    mov     bx,CS:current_sp
    mov     dx,word ptr SS:[bx+2]
    mov     bx,CS:last_cs
    mov     di,(14*80 + 72) * 2
    call    show_register_16
  ; ip
    mov     bx,CS:current_sp
    mov     dx,word ptr SS:[bx+0]
    mov     bx,CS:last_ip
    mov     di,(15*80 + 75) * 2
    call    show_register_16
  ; flags
    mov     bx,CS:current_sp
    mov     dx,word ptr SS:[bx+4]
    mov     bx,CS:last_flags
    mov     di,(16*80 + 75) * 2
    call    show_register_16
    call    show_flags_status
    ret


;-----------------------------------------------
show_register_32:
    push    di
    cmp     ebx,edx
    jz      normal_color_1
    mov     ah,7
    jmp     @F
  normal_color_1:
    mov     ah,112
  @@:
    mov     cx,8
  again_1:
    rol     edx,4
    mov     al,dl
    and     al,0fh
    cmp     al,9
    ja      show_letter_1
    add     al,"0"
    jmp     store_value_1
  show_letter_1:
    add     al,"A"-10
  store_value_1:
    stosw
    loop    again_1
    pop     di
    ret


;-----------------------------------------------
show_register_16:
    push    di
    cmp     bx,dx
    jz      normal_color_2
    mov     ah,7
    jmp     @F
  normal_color_2:
    mov     ah,112
  @@:
    mov     cx,4
  again_2:
    rol     dx,4
    mov     al,dl
    and     al,0fh
    cmp     al,9
    ja      show_letter_2
    add     al,"0"
    jmp     store_value_2
  show_letter_2:
    add     al,"A"-10
  store_value_2:
    stosw
    loop    again_2
    pop     di
    ret


;-----------------------------------------------
show_register_8:
    push    di
    cmp     bl,dl
    jz      normal_color_3
    mov     ah,7
    jmp     @F
  normal_color_3:
    mov     ah,112
  @@:
    mov     cx,2
  again_3:
    rol     dl,4
    mov     al,dl
    and     al,0fh
    cmp     al,9
    ja      show_letter_3
    add     al,"0"
    jmp     store_value_3
  show_letter_3:
    add     al,"A"-10
  store_value_3:
    stosw
    loop    again_3
    pop     di
    ret


;-----------------------------------------------
show_register_8_no_color:
    push    di
    mov     cx,2
  again_4:
    rol     dl,4
    mov     al,dl
    and     al,0fh
    cmp     al,9
    ja      show_letter_4
    add     al,"0"
    jmp     store_value_4
  show_letter_4:
    add     al,"A"-10
  store_value_4:
    stosb
    inc     di
    loop    again_4
    pop     di
    ret


;-----------------------------------------------
show_register_16_binary:
    push    di
    cmp     bx,dx
    jz      normal_color_5
    mov     ah,7
    jmp     @F
  normal_color_5:
    mov     ah,112
  @@:
    mov     cx,16
  again_5:
    rcl     dx,1
    jc      show_one
    mov     al,"0"
    jmp     store_value_5
  show_one:
    mov     al,"1"
  store_value_5:
    stosw
    loop    again_5
    pop     di
    ret


;-----------------------------------------------
show_register_16_no_color:
    push    di
    mov     cx,4
  again_6:
    rol     dx,4
    mov     al,dl
    and     al,0fh
    cmp     al,9
    ja      show_letter_6
    add     al,"0"
    jmp     store_value_6
  show_letter_6:
    add     al,"A"-10
  store_value_6:
    stosb
    inc     di
    loop    again_6
    pop     di
    ret


;-----------------------------------------------
show_register_20_no_color:
    push    di
    mov     cx,5
    rol     edx,12                                                  ; Get the part of edx over there in the left bits
  again_7:
    rol     edx,4
    mov     al,dl
    and     al,0fh
    cmp     al,9
    ja      show_letter_7
    add     al,"0"
    jmp     store_value_7
  show_letter_7:
    add     al,"A"-10
  store_value_7:
    stosb
    inc     di
    loop    again_7
    pop     di
    ret


;-----------------------------------------------
show_register_32_no_color:
    push    di
    mov     cx,8
  again_8:
    rol     edx,4
    mov     al,dl
    and     al,0fh
    cmp     al,9
    ja      show_letter_8
    add     al,"0"
    jmp     store_value_8
  show_letter_8:
    add     al,"A"-10
  store_value_8:
    stosb
    inc     di
    loop    again_8
    pop     di
    ret


;-----------------------------------------------
show_register_32_16_16_no_color:
    push    di
  @@:
  ; Display the first 4 nibbles
    mov     cx,4
  again_9:
    rol     edx,4
    mov     al,dl
    and     al,0fh
    cmp     al,9
    ja      show_letter_9
    add     al,"0"
    jmp     store_value_9
  show_letter_9:
    add     al,"A"-10
  store_value_9:
    stosb
    inc     di
    loop    again_9

  ; Display the colon
    mov     al,":"
    stosb
    inc     di

  ; Display the next 4 nibbles
    mov     cx,4
  again_10:
    rol     edx,4
    mov     al,dl
    and     al,0fh
    cmp     al,9
    ja      show_letter_10
    add     al,"0"
    jmp     store_value_10
  show_letter_10:
    add     al,"A"-10
  store_value_10:
    stosb
    inc     di
    loop    again_10
    pop     di
    ret


;-----------------------------------------------
show_register_8_no_color_signed:
    push    di
    .IF (dl > 80h)
        mov     al,"-"
        neg     dl
    .ELSE
        mov     al,"+"
    .ENDIF
    stosb
    inc     di
    mov     cx,2
  again_11:
    rol     dl,4
    mov     al,dl
    and     al,0fh
    cmp     al,9
    ja      show_letter_11
    add     al,"0"
    jmp     store_value_11
  show_letter_11:
    add     al,"A"-10
  store_value_11:
    stosb
    inc     di
    loop    again_11
    pop     di
    ret


;-----------------------------------------------
show_register_16_no_color_signed:
    push    di
    .IF (dx > 8000h)
        mov     al,"-"
        neg     dx
    .ELSE
        mov     al,"+"
    .ENDIF
    stosb
    inc     di
    mov     cx,4
  again_12:
    rol     dx,4
    mov     al,dl
    and     al,0fh
    cmp     al,9
    ja      show_letter_12
    add     al,"0"
    jmp     store_value_12
  show_letter_12:
    add     al,"A"-10
  store_value_12:
    stosb
    inc     di
    loop    again_12
    pop     di
    ret


;-----------------------------------------------
show_register_32_no_color_signed:
    push    di
    .IF (edx > 80000000h)
        mov     al,"-"
        neg     edx
    .ELSE
        mov     al,"+"
    .ENDIF
    stosb
    inc     di
    mov     cx,8
  again_13:
    rol     edx,4
    mov     al,dl
    and     al,0fh
    cmp     al,9
    ja      show_letter_13
    add     al,"0"
    jmp     store_value_13
  show_letter_13:
    add     al,"A"-10
  store_value_13:
    stosb
    inc     di
    loop    again_13
    pop     di
    ret


;-----------------------------------------------
show_flags_status:
    mov     bx,CS:current_sp
    mov     ax,word ptr SS:[bx+4]
  ; Nested task
    mov     di,(17*80 + 70) * 2
    mov     bl,CS:last_nt_flag
    mov     si,offset last_nt_flag
    test    ax,100000000000000b
    call    show_flag
  ; Overflow
    mov     di,(17*80 + 74) * 2
    mov     bl,CS:last_of_flag
    mov     si,offset last_of_flag
    test    ax,000100000000000b
    call    show_flag
  ; Direction
    mov     di,(17*80 + 78) * 2
    mov     bl,CS:last_df_flag
    mov     si,offset last_df_flag
    test    ax,000010000000000b
    call    show_flag
  ; Parity
    mov     di,(18*80 + 70) * 2
    mov     bl,CS:last_pf_flag
    mov     si,offset last_pf_flag
    test    ax,000000000000010b
    call    show_flag
  ; Sign
    mov     di,(18*80 + 74) * 2
    mov     bl,CS:last_sf_flag
    mov     si,offset last_sf_flag
    test    ax,000000010000000b
    call    show_flag
  ; Zero
    mov     di,(18*80 + 78) * 2
    mov     bl,CS:last_zf_flag
    mov     si,offset last_zf_flag
    test    ax,000000001000000b
    call    show_flag
  ; Aux carry
    mov     di,(19*80 + 74) * 2
    mov     bl,CS:last_acf_flag
    mov     si,offset last_acf_flag
    test    ax,000000000010000b
    call    show_flag
  ; Carry
    mov     di,(19*80 + 78) * 2
    mov     bl,CS:last_cf_flag
    mov     si,offset last_cf_flag
    test    ax,000000000000001b
    call    show_flag
    ret


;-----------------------------------------------
show_flag:
    push    AX
    jz      flag_down
  flag_up:
  ; The flag is up
    mov     byte ptr CS:[si],1
    .IF (bl == 0)
      ; It's changed, last time it was down
        mov     ah,7
    .ELSE
        mov     ah,112
    .ENDIF
    mov     al,""
    jmp     show_flag_done

  flag_down:
  ; The flag is down
    mov     byte ptr CS:[si],0
    .IF (bl == 1)
      ; It's changed, last time it was up
        mov     ah,7
    .ELSE
        mov     ah,112
    .ENDIF
    mov     al,""
  show_flag_done:
    stosw
    pop     AX
    ret


;-----------------------------------------------
show_stack:
    mov     si,CS:current_sp
    add     si,6
    mov     di,(19*80 + 63) * 2                                     ; Show the stack from line 19 up to
  show_stack_loop:
    mov     bx,word ptr ss:[si]
    mov     dx,bx
    call    show_register_16
    add     si,2
    sub     di,80*2
    cmp     di,(1*80 + 63) * 2                                      ; line 1
    jae     show_stack_loop
    ret


;-----------------------------------------------
display_disassembly:
    mov     bx,CS:current_sp
    mov     ds,word ptr SS:[bx+2]
    mov     si,word ptr SS:[bx]
    mov     di,0b000h
    mov     ES,di
    mov     di,1*80*2                                               ; Start on the first line
    mov     CX,13
    call    generate_disassembly
    ret

INCLUDE xdebug.asp
INCLUDE showmem.asp
INCLUDE fpu.asp


;-----------------------------------------------
clear_debug_screen:
    xor     di,di
    mov     AX,0720h
    mov     CX,80*25
    rep     stosw
    ret


;-----------------------------------------------
copy_current_to_last:
    push    DS
    push    CS
    pop     DS
    mov     eax,dword ptr [bp-4]                                    ; eax
    mov     last_eax,eax
    mov     eax,dword ptr [bp-8]                                    ; ebx
    mov     last_ebx,eax
    mov     eax,dword ptr [bp-12]                                   ; ecx
    mov     last_ecx,eax
    mov     eax,dword ptr [bp-16]                                   ; edx
    mov     last_edx,eax
    mov     eax,dword ptr [bp-20]                                   ; esi
    mov     last_esi,eax
    mov     eax,dword ptr [bp-24]                                   ; edi
    mov     last_edi,eax
    mov     ax,CS:current_sp                                        ; sp
    mov     last_sp,ax
    mov     ax,word ptr [bp-30]                                     ; ds
    mov     last_ds,ax
    mov     ax,word ptr [bp-32]                                     ; es
    mov     last_es,ax
    mov     ax,word ptr [bp-34]                                     ; fs
    mov     last_fs,ax
    mov     ax,word ptr [bp-36]                                     ; gs
    mov     last_gs,ax
    mov     ax,word ptr [bp-38]                                     ; ss
    mov     last_ss,ax
    mov     bx,current_sp                                           ; cs
    mov     ax,word ptr SS:[bx+2]
    mov     last_cs,ax
    mov     ax,word ptr SS:[bx+0]                                   ; ip
    mov     last_ip,ax
    mov     ax,word ptr SS:[bx+4]                                   ; flags
    mov     last_flags,ax
    mov     ax,current_bp                                           ; bp
    mov     last_bp,ax
  ; Update the FPU registers
    mov     ax,word ptr save_fpu_state[0]                           ; control word
    mov     last_cw,ax
    mov     ax,word ptr save_fpu_state[2]                           ; status word
    mov     last_sw,ax
    mov     ax,word ptr save_fpu_state[4]                           ; tag word
    mov     last_tw,ax
    fld     tbyte ptr save_fpu_state[14]                            ; st0
    fstp    tbyte ptr last_st0
    fld     tbyte ptr save_fpu_state[24]                            ; st1
    fstp    tbyte ptr last_st1
    fld     tbyte ptr save_fpu_state[34]                            ; st2
    fstp    tbyte ptr last_st2
    fld     tbyte ptr save_fpu_state[44]                            ; st3
    fstp    tbyte ptr last_st3
    fld     tbyte ptr save_fpu_state[54]                            ; st4
    fstp    tbyte ptr last_st4
    fld     tbyte ptr save_fpu_state[64]                            ; st5
    fstp    tbyte ptr last_st5
    fld     tbyte ptr save_fpu_state[74]                            ; st6
    fstp    tbyte ptr last_st6
    fld     tbyte ptr save_fpu_state[84]                            ; st7
    fstp    tbyte ptr last_st7
    mov     eax,mem1_address
    mov     last_mem1_addr,eax
    mov     eax,mem2_address
    mov     last_mem2_addr,eax
    pop     DS
    ret


;=============================
;; Data used in this procedure
    already_here    db  0
    already_here_2  db  0
    first_time      db  0

    last_mem1_addr  dd  0ffffffffh
    mem1_address    dd  0
    mem1_seg        db  10
    mem1_offset     db  24

    last_mem2_addr  dd  0ffffffffh
    mem2_address    dd  0
    mem2_seg        db  0
    mem2_offset     db  1

                                                            ; Identified internally as:
    last_cs         dw  0ffffh                              ;  cs=0
    last_ip         dw  0ffffh                              ;  ip=1
    last_bp         dw  0ffffh                              ;  bp=2
    last_eax        dd  0ffffffffh                          ; eax=3, ax=20, ah=30, al=35
    last_ebx        dd  0ffffffffh                          ; ebx=4, bx=21, bh=31, bl=36
    last_ecx        dd  0ffffffffh                          ; ecx=5, cx=22, ch=32, cl=37
    last_edx        dd  0ffffffffh                          ; edx=6, dx=23, dh=33, dl=38
    last_esi        dd  0ffffffffh                          ; esi=7, si=24
    last_edi        dd  0ffffffffh                          ; edi=8, di=25
    last_sp         dw  0ffffh                              ;  sp=9
    current_sp      dw  0
    current_bp      dw  0
    last_ds         dw  0ffffh                              ; ds=10
    last_es         dw  0ffffh                              ; es=11
    last_fs         dw  0ffffh                              ; fs=12
    last_gs         dw  0ffffh                              ; gs=13
    last_ss         dw  0ffffh                              ; ss=14
    last_flags      dw  0ffffh                              ; flags=15
    last_nt_flag    db  0
    last_of_flag    db  0
    last_df_flag    db  0
    last_pf_flag    db  0
    last_sf_flag    db  0
    last_zf_flag    db  0
    last_acf_flag   db  0
    last_cf_flag    db  0
    last_st0        REAL10 0.00                             ; 50
    last_st1        REAL10 0.00                             ; 51
    last_st2        REAL10 0.00                             ; 52
    last_st3        REAL10 0.00                             ; 53
    last_st4        REAL10 0.00                             ; 54
    last_st5        REAL10 0.00                             ; 55
    last_st6        REAL10 0.00                             ; 56
    last_st7        REAL10 0.00                             ; 57
    last_cw         dw  0
    last_sw         dw  0
    last_tw         dw  0

    save_fpu_state  db  94 dup(0)

    sreg_override       db  0
    sign_extend         db  0
    movxx               db  0
    reverse_regs        db  0
    special_reg         db  0
    mod_reg_rm_byte     db  0
    sib_byte            db  0
    byte_word_size      db  0
    seg_override        db  0
    op_size_override    dw  0
    adr_size_override   dw  0

    int3_text       db  "int3"
    aaa_text        db  "aaa"
    xadd_text       db  "x"
    add_text        db  "add"
    aas_text        db  "aas"
    cbw_text        db  "cbw"
  cwde_text:
    cwd_text        db  "cwd"
                    db  "e"
    cdq_text        db  "cdq"
    clc_text        db  "clc"
    cld_text        db  "cld"
    cli_text        db  "cli"
    cmc_text        db  "cmc"
    daa_text        db  "daa"
    das_text        db  "das"
    hlt_text        db  "hlt"
    into_text       db  "into"
  iretd_text:
    iret_text       db  "iret"
                    db  "d"
    lahf_text       db  "lahf"
    leave_text      db  "leave"
    lock_text       db  "lock"
    nop_text        db  "nop"
  popad_text:
    popa_text       db  "popa"
                    db  "d"
  popfd_text:
    popf_text       db  "popf"
                    db  "d"
  pushad_text:
    pusha_text      db  "pusha"
                    db  "d"
  pushfd_text:
    pushf_text      db  "pushf"
                    db  "d"
    ret_text        db  "ret"
    retf_text       db  "retf"
    sahf_text       db  "sahf"
    stc_text        db  "stc"
    std_text        db  "std"
    sti_text        db  "sti"
    wait_text       db  "wait"
    xlat_text       db  "xlat"
    aad_text        db  "aad"
    aam_text        db  "aam"
    clts_text       db  "clts"
    wbinvd_text     db  "wb"
    invd_text       db  "invd"
    arpl_text       db  "arpl"
    bound_text      db  "bound"
    bswap_text      db  "bswap"
  call_far_text:
    call_text       db  "call"
                    db  "f"
    cmpxchg_text    db  "cmpxchg"
    enter_text      db  "enter"
    int_text        db  "int"
    ja_text         db  "ja.u"
    jc_text         db  "jc"
    jnc_text        db  "jnc"
    jbe_text        db  "jbe.u"
    jz_text         db  "jz"
    jnz_text        db  "jnz"
    jl_text         db  "jl.s"
    jg_text         db  "jg.s"
    jle_text        db  "jle.s"
    jge_text        db  "jge.s"
    js_text         db  "js"
    jns_text        db  "jns"
    jp_text         db  "jp"
    jnp_text        db  "jnp"
    jo_text         db  "jo"
    jno_text        db  "jno"
    seta_text       db  "seta.u"
    setc_text       db  "setc"
    setnc_text      db  "setnc"
    setbe_text      db  "setbe.u"
    setz_text       db  "setz"
    setnz_text      db  "setnz"
    setl_text       db  "setl.s"
    setg_text       db  "setg.s"
    setle_text      db  "setle.s"
    setge_text      db  "setge.s"
    sets_text       db  "sets"
    setns_text      db  "setns"
    setp_text       db  "setp"
    setnp_text      db  "setnp"
    seto_text       db  "seto"
    setno_text      db  "setno"
    jcxz_text       db  "jcxz"
    jecxz_text      db  "jecxz"
  jmp_far_text:
    jmp_text        db  "jmp"
                    db  "f"
  movsx_text:
    mov_text        db  "mov"
                    db  "sx"
    movzx_text      db  "movzx"
    lds_text        db  "lds"
    les_text        db  "les"
    lea_text        db  "lea"
  loopne_text:
    loop_text       db  "loop"
                    db  "ne"
  looped_text:
    loope_text      db  "loope"
    pop_text        db  "pop"
  pushd_text:
    push_text       db  "push"
                    db  "d"
  repne_text:
    rep_text        db  "rep"
                    db  "ne"
    repe_text       db  "repe"
    movsb_text      db  "movsb"
    movsw_text      db  "movsw"
    movsd_text      db  "movsd"
    stosb_text      db  "stosb"
    stosw_text      db  "stosw"
    stosd_text      db  "stosd"
    lodsb_text      db  "lodsb"
    lodsw_text      db  "lodsw"
    lodsd_text      db  "lodsw"
    insb_text       db  "insb"
    insw_text       db  "insw"
    insd_text       db  "insd"
    outsb_text      db  "outs"
    outsw_text      db  "outsw"
    outsd_text      db  "outsd"
    cmpsb_text      db  "cmpsb"
    cmpsw_text      db  "cmpsw"
    cmpsd_text      db  "cmpsd"
    scasb_text      db  "scasb"
    scasw_text      db  "scasw"
    scasd_text      db  "scasd"
    setccc_text     db  "setccc"
    bsf_text        db  "bsf"
    bsr_text        db  "bsr"
  btc_text:
    bt_text         db  "bt"
                    db  "c"
    bts_text        db  "bts"
    btr_text        db  "btr"
    invlpg_text     db  "invlpg"
    lar_text        db  "lar"
    lfs_text        db  "lfs"
    lgs_text        db  "lgs"
    lss_text        db  "lss"
    lgdt_text       db  "lgdt"
    lidt_text       db  "lidt"
    lldt_text       db  "lldt"
    lmsw_text       db  "lmsw"
    lsl_text        db  "lsl"
    ltr_text        db  "ltr"
    sldt_text       db  "sldt"
    str_text        db  "str"
    verr_text       db  "verr"
    verw_text       db  "verw"
    sgdt_text       db  "sgdt"
    sidt_text       db  "sidt"
    smsw_text       db  "smsw"
  shld_text:
    shl_text        db  "shl"
                    db  "d"
    sal_text        db  "sal"
  shrd_text:
    shr_text        db  "shr"
                    db  "d"
    sar_text        db  "sar"
    imul_text       db  "i"
    mul_text        db  "mul"
    test_text       db  "test"
    not_text        db  "not"
    neg_text        db  "neg"
    idiv_text       db  "i"
    div_text        db  "div"
  inc_text:
    in_text         db  "in"
                    db  "c"
    dec_text        db  "dec"
    rol_text        db  "rol"
    rcl_text        db  "rcl"
    ror_text        db  "ror"
    rcr_text        db  "rcr"
    xchg_text       db  "xchg"
    or_text         db  "or"
    adc_text        db  "adc"
    sbb_text        db  "sbb"
    and_text        db  "and"
    sub_text        db  "sub"
    xor_text        db  "xor"
    cmp_text        db  "cmp"

    fadd_text       db  "fadd"
  fmulp_text:
    fmul_text       db  "fmul"
                    db  "p"
  fcompp_text:
  fcomp_text:
    fcom_text       db  "fcom"
                    db  "p"
                    db  "p"
  fsubrp_text:
  fsubr_text:
    fsub_text       db  "fsub"
                    db  "r"
                    db  "p"
  fdivr_text:
    fdiv_text       db  "fdiv"
                    db  "r"
    fdivp_text      db  "fdivp"
  fldcw_text:
    fld_text        db  "fld"
                    db  "cw"
  fstp_text:
    fst_text        db  "fst"
                    db  "p"
    fxch_text       db  "fxch"
    fnop_text       db  "fnop"
    fchs_text       db  "fchs"
    fabs_text       db  "fabs"
    ftst_text       db  "ftst"
    fxam_text       db  "fxam"
    fld1_text       db  "fld1"
    fldl2t_text     db  "fldl2t"
    fldl2e_text     db  "fldl2e"
    fldpi_text      db  "fldpi"
    fldg2_text      db  "fldg2"
    fldn2_text      db  "fldn2"
    fldz_text       db  "fldz"
    f2xm1_text      db  "f2xm1"
    fyl2x_text      db  "fyl2x"
    fptan_text      db  "fptan"
    fpatan_text     db  "fpatan"
    fxtract_text    db  "fxtract"
  fprem_text:
    fprem1_text     db  "fprem1"
    fdecstp_text    db  "fdecstp"
    fincstp_text    db  "fincstp"
    fyl2xp1_text    db  "fyl2xp1"
    fsqrt_text      db  "fsqrt"
    fsincos_text    db  "fsincos"
    frndint_text    db  "frndint"
    fscale_text     db  "fscale"
    fsin_text       db  "fsin"
    fcos_text       db  "fcos"
    fldenv_text     db  "fldenv"
    fstenv_text     db  "fstenv"
    fstcw_text      db  "fstcw"
    fucompp_text    db  "fucompp"
    fiadd_text      db  "fiadd"
    fimul_text      db  "fimul"
  ficomp_text:
    ficom_text      db  "ficom"
                    db  "p"
  fisubr_text:
    fisub_text      db  "fisub"
                    db  "r"
  fidivr_text:
    fidiv_text      db  "fidiv"
                    db  "r"
    fclex_text      db  "fclex"
    finit_text      db  "finit"
    fild_text       db  "fild"
  fistp_text:
    fist_text       db  "fist"
                    db  "p"
    ffree_text      db  "ffree"
  fucomp_text:
    fucom_text      db  "fucom"
                    db  "p"
    frstor_text     db  "frstor"
    fstsw_text      db  "fstsw"
    fbld_text       db  "fbld"
    fbstp_text      db  "fbstp"
    fsave_text      db  "fsave"


  illegal_register:
    unknown_text    db  "???"

    CONST_AL    EQU 000b
    CONST_AX    EQU 000b
    CONST_EAX   EQU 000b
    CONST_ES    EQU 000b

    CONST_CL    EQU 001b
    CONST_CX    EQU 001b
    CONST_ECX   EQU 001b
    CONST_CS    EQU 001b

    CONST_DL    EQU 010b
    CONST_DX    EQU 010b
    CONST_EDX   EQU 010b
    CONST_SS    EQU 010b

    CONST_BL    EQU 011b
    CONST_BX    EQU 011b
    CONST_EBX   EQU 011b
    CONST_DS    EQU 011b

    CONST_AH    EQU 100b
    CONST_SP    EQU 100b
    CONST_ESP   EQU 100b
    CONST_FS    EQU 100b

    CONST_CH    EQU 101b
    CONST_BP    EQU 101b
    CONST_EBP   EQU 101b
    CONST_GS    EQU 101b

    CONST_DH    EQU 110b
    CONST_SI    EQU 110b
    CONST_ESI   EQU 110b

    CONST_BH    EQU 111b
    CONST_DI    EQU 111b
    CONST_EDI   EQU 111b

    ebx_esi_register    db  "ebx+esi"
    ebx_edi_register    db  "ebx+edi"
    ebp_esi_register    db  "ebp+esi"
    ebp_edi_register    db  "ebp+edi"
    bx_si_register  db  "bx+si"
    bx_di_register  db  "bx+di"
    bp_si_register  db  "bp+si"
    bp_di_register  db  "bp+di"
    cs_register     db  "cs"
    ds_register     db  "ds"
    es_register     db  "es"
    fs_register     db  "fs"
    gs_register     db  "gs"
    ss_register     db  "ss"
    eax_register    db  "e"
    ax_register     db  "ax"
    ebx_register    db  "e"
    bx_register     db  "bx"
    ecx_register    db  "e"
    cx_register     db  "cx"
    edx_register    db  "e"
    dx_register     db  "dx"
    esi_register    db  "e"
    si_register     db  "si"
    edi_register    db  "e"
    di_register     db  "di"
    ebp_register    db  "e"
    bp_register     db  "bp"
    ah_register     db  "ah"
    al_register     db  "al"
    bh_register     db  "bh"
    bl_register     db  "bl"
    ch_register     db  "ch"
    cl_register     db  "cl"
    dh_register     db  "dh"
    dl_register     db  "dl"
    ip_register     db  "ip"
    esp_register    db  "e"
    sp_register     db  "sp"
    st0_register    db  "st0"
    st1_register    db  "st1"
    st2_register    db  "st2"
    st3_register    db  "st3"
    st4_register    db  "st4"
    st5_register    db  "st5"
    st6_register    db  "st6"
    st7_register    db  "st7"
    cr0_register    db  "cr0"
    cr1_register    db  "cr1"
    cr2_register    db  "cr2"
    cr3_register    db  "cr3"
    cr4_register    db  "cr4"
    cr5_register    db  "cr5"
    cr6_register    db  "cr6"
    cr7_register    db  "cr7"
    dr0_register    db  "dr0"
    dr1_register    db  "dr1"
    dr2_register    db  "dr2"
    dr3_register    db  "dr3"
    dr4_register    db  "dr4"
    dr5_register    db  "dr5"
    dr6_register    db  "dr6"
    dr7_register    db  "dr7"
    tr0_register    db  "tr0"
    tr1_register    db  "tr1"
    tr2_register    db  "tr2"
    tr3_register    db  "tr3"
    tr4_register    db  "tr4"
    tr5_register    db  "tr5"
    tr6_register    db  "tr6"
    tr7_register    db  "tr7"
    flags_register  db  "flags"
    zero_ffff       db  "0ffffh"


    badnumber0      db  " +Unsupported               ",0
    badnumber1      db  " +NaN                       ",0
    badnumber2      db  " -Unsupported               ",0
    badnumber3      db  " -NaN                       ",0
    badnumber4      db  " +Normal                    ",0
    badnumber5      db  " +Infinity                  ",0
    badnumber6      db  " -Normal                    ",0
    badnumber7      db  " -Infinity                  ",0
    badnumber8      db  " 0.0000000000000000000+00000",0
    badnumber9      db  " +Empty                     ",0
    badnumber10     db  "-0.0000000000000000000+00000",0
    badnumber11     db  " -Empty                     ",0
    badnumber12     db  " +Denormals                 ",0
    badnumber13     db  " ?Unknown?                  ",0
    badnumber14     db  " -Denormals                 ",0

    fpu_stat        dw  ?
    exponent        sword   0
    number10        real4   10.0
    point5          real4    0.5
    digit           dw  ?
    controlword     dw  ?

    temp_buffer     db  40 dup(0)

  debug_screen:
    db  "פ תתתת:תתתת ת            ת       ת                            ץ פÚstackִִregistersִץ"
  initialize_line:
    db  " תתתת:תתתת ת            ת       ת                             פ³תתתת³eax תתתתתתתתץ"
    db  " תתתת:תתתת ת            ת       ת                             פ³תתתת³ebx תתתתתתתתץ"
    db  " תתתת:תתתת ת            ת       ת                             פ³תתתת³ecx תתתתתתתתץ"
    db  " תתתת:תתתת ת            ת       ת                             פ³תתתת³edx תתתתתתתתץ"
    db  " תתתת:תתתת ת            ת       ת                             פ³תתתת³esi תתתתתתתתץ"
    db  " תתתת:תתתת ת            ת       ת                             פ³תתתת³edi תתתתתתתתץ"
    db  "פִfpuִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִ³תתתת³ ds תתתת    ץ"
    db  "פs0 ת.תתתתתתתתתתתתתתתתתתת+תתתתת  s4 ת.תתתתתתתתתתתתתתתתתתת+תתתתת³תתתת³ es תתתת    ץ"
    db  "פs1 ת.תתתתתתתתתתתתתתתתתתת+תתתתת  s5 ת.תתתתתתתתתתתתתתתתתתת+תתתתת³תתתת³ fs תתתת    ץ"
    db  "פs2 ת.תתתתתתתתתתתתתתתתתתת+תתתתת  s6 ת.תתתתתתתתתתתתתתתתתתת+תתתתת³תתתת³ gs תתתת    ץ"
    db  "פs3 ת.תתתתתתתתתתתתתתתתתתת+תתתתת  s7 ת.תתתתתתתתתתתתתתתתתתת+תתתתת³תתתת³ ss תתתת    ץ"
    db  "פ  C[תתתתתתתתתתתתתתתת] S[תתתתתתתתתתתתתתתת] T[תתתתתתתתתתתתתתתת] ³תתתת³    bp תתתת ץ"
    db  "פִִִִwatchֲִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִmem1ִ´תתתת³    sp תתתת ץ"
    db  "תת:תת     תתפ³תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת תתתתתתתתתתתתתתתת³תתתת³ cs תתתת    ץ"
    db  "תת:תת     תתפ³תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת תתתתתתתתתתתתתתתת³תתתת³    ip תתתת ץ"
    db  "תת:תת   תתתתפ³תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת תתתתתתתתתתתתתתתת³תתתת³ flags תתתת ץ"
    db  "תת:תת   תתתתפ³תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת תתתתתתתתתתתתתתתת³תתתת³NT  OF  DF  ץ"
    db  "תת:תת   תתתתפֳִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִmem2ִ´תתתת³PF  SF  ZF  ץ"
    db  "תת:תת       פ³תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת תתתתתתתתתתתתתתתת³תתתת³   ACF  CF  ץ"
    db  "    תתתתתתתתפ³תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת תתתתתתתתתתתתתתתתֱֳִִִִִִִִִִִִִִִִץ"
    db  "תת:תתתת תתתתפ³תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת תתתתתתתתתתתתתתתת³ץ   xDebug for    "
    db  "תתתתתתתתתתתתפ³תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת תתתתתתתתתתתתתתתת³ץ    פ[ Exodus ]ץ   "
    db  "פֱִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִִ´ץ     version 1.0 "
    db  "פF5ץ:go  פF8ץ:step                      פF1ץ:mem1  פF2ץ:mem2  פF3ץ:fpu  פְִִִִִִִִִִִִִִִִִץ"
_XDEBUG     ENDS

END
