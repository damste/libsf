; xdebug.asp
;
; xDebug
; This is a global routine, called by both xDebug.com
;

;; Turns on a debugging-of-the-debugger scenario, where debugger source code can be viewed
;.IF (CS:already_here_2 == 0)
;    mov     CS:already_here,0
;    mov     CS:already_here_2,1
;    int 3
;.ENDIF

generate_disassembly:
;
; Upon entry:   ds:[si] - Far ptr to instruction stream
;               es:[di] - Far ptr to location on screen to display first line (each line is increased by 80*2 bytes)
;                    cx - Number of lines to disassemble
;
; Upon exit:  Nothing (everything is preserved)
;
    enter   10,0
  ; Create a local stack frame (of sortws) for temporary variables
  ;
  ; [bp-2] - Holds start of the most recent instruction that has been displayed
  ; [bp-4] - Holds # of bytes to shift left for display of instruction text "mov"
  ; [bp-6] - Holds # of bytes to shift right for display of instruction bytes "6766"
  ; [bp-8] - Holds the end of the most recent instruction bytes that were displayed
  ; [bp-10] - Used in temporary calculations for displaying additional instruction bytes (usually immed data)
  ;
    pushad
    push    DS
    push    ES

    mov     ax,0b000h
    mov     es,ax

    xor     di,di
    mov     cx,7
    mov     edx,offset debug_screen
  disassemble_loop:
    push    di
    push    cx

; Initialize the display line (so it returns to its default viewing
    mov     cx,62
    mov     ah,7
  draw_next_char:
    mov     al,cs:[edx]
    cmp     al,"ô"
    jnz     @F
    mov     ah,112
    inc     edx
    jmp     draw_next_char
  @@:
    cmp     al,"õ"
    jnz     store_this_char
    mov     ah,7
    inc     edx
    jmp     draw_next_char
  store_this_char:
    stosw
    inc     edx
    loop    draw_next_char

    pop     cx
    pop     di
    push    di
    push    cx
    mov     dx,ds                                                   ; Display the address
    add     di,2
    call    show_register_16_no_color

    mov     dx,si                                                   ; Display the address
    mov     bx,dx                                                   ; ip
    add     di,5 * 2
    call    show_register_16_no_color

    mov     CS:seg_override,0
    mov     CS:op_size_override,0
    mov     CS:adr_size_override,0
    mov     CS:sib_byte,0
    mov     CS:byte_word_size,1
    mov     CS:reverse_regs,0
    mov     CS:sign_extend,0
    mov     CS:movxx,0
    mov     CS:sreg_override,0

  next_byte:
    xor     bx,bx
    mov     ax,word ptr [si]
    xor     edx,edx
    cmp     al,066h
    jnz     @F
      ; 32/16-bit register override
        inc     CS:op_size_override
        inc     si
        jmp     next_byte
  @@:
    cmp     al,067h
    jnz     @F
      ; 32/16-bit memory override
        inc     CS:adr_size_override
        inc     si
        jmp     next_byte
  @@:
    cmp     al,02eh
    jnz     @F
      ; CS segment override
        mov     CS:seg_override,1
        inc     si
        jmp     next_byte
  @@:
    cmp     al,03eh
    jnz     @F
      ; DS segment override
        mov     CS:seg_override,2
        inc     si
        jmp     next_byte
  @@:
    cmp     al,026h
    jnz     @F
      ; ES segment override
        mov     CS:seg_override,3
        inc     si
        jmp     next_byte
  @@:
    cmp     al,036h
    jnz     @F
      ; SS segment override
        mov     CS:seg_override,4
        inc     si
        jmp     next_byte
  @@:
    cmp     al,064h
    jnz     @F
      ; FS segment override
        mov     CS:seg_override,5
        inc     si
        jmp     next_byte
  @@:
    cmp     al,065h
    jnz     @F
      ; GS segment override
        mov     CS:seg_override,6
        inc     si
        jmp     next_byte
  @@:
    cmp     al,0fh
    jz     @F
    jmp     one_byte_instructions

; Here we check all first-byte-0fh instructions
  @@:
        mov     bx,2
        .IF (ah == 00000110b)
          ; clts
            mov     dx,offset clts_text
            mov     cx,4
        .ELSEIF (ah == 00001000b)
          ; invd
            mov     dx,offset invd_text
            mov     cx,4
        .ELSEIF (ah == 00001001b)
          ; wbinvd
            mov     dx,offset wbinvd_text
            mov     cx,6
        .ELSE
            mov     dl,ah
            and     dl,11111000b
            cmp     dl,11001000b
            jz      @F
            jmp     try_again1
          @@:
              ; bswap
                mov     dx,offset bswap_text
                mov     cx,5
                cmp     CS:op_size_override,0
                jz      @F
                dec     si
                mov     bl,3
              @@:
                call    display_instruction
                mov     al,ah
                and     al,111b
                cmp     CS:op_size_override,0
                jz      @F
                call    display_register_name_32
                jmp     next_instruction
              @@:
                call    display_register_name_16
                jmp     next_instruction

          try_again1:
            mov     dl,ah
            and     dl,11000111b
            cmp     dl,10000001b
            jz      @F
            jmp     try_again2
          @@:
              ; It's a possible pop fs/gs.  We have to examine the last three bits to see
                mov     al,ah
                shr     al,3
                and     al,0111b
                cmp     al,100b
                jz      try_again1_cont1
                cmp     al,101b
                jz      try_again1_cont1
                jmp     try_again2                                  ; If we branch here, then it's not pop fs/gs
              try_again1_cont1:
                mov     dx,offset pop_text
                mov     cx,3
                call    display_instruction
                call    display_register_name_sreg
                jmp     next_instruction

          try_again2:
            mov     dl,ah
            and     dl,11000111b
            cmp     dl,10000000b
            jz      @F
            jmp     try_again3
          @@:
              ; It's a possible push fs/gs.  We have to examine the last three bits to see
                mov     al,ah
                shr     al,3
                and     al,0111b
                cmp     al,100b
                jz      try_again2_success
                cmp     al,101b
                jz      try_again2_success
                jmp     try_again3                                  ; If we branch here, then it's not pop fs/gs
              try_again2_success:
                mov     dx,offset push_text
                mov     cx,4
                call    display_instruction
                call    display_register_name_sreg
                jmp     next_instruction

          try_again3:
            mov     dl,ah
            and     dl,11000111b
            cmp     dl,10000011b
            jz      @F
            jmp     try_again4
          @@:
              ; bt?
                mov     bl,3
                mov     cx,3                                        ; Default to an instruction length of three
                mov     dl,ah
                shr     dl,3
                and     dl,0111b
                cmp     dl,100b
                jnz     try_again_3_sub1
                ; bt
                mov     dx,offset bt_text
                mov     cx,2
                jmp     try_again_3_success
              try_again_3_sub1:
                cmp     dl,111b
                jnz     try_again_3_sub2
                ; btc
                mov     dx,offset btc_text
                jmp     try_again_3_success
              try_again_3_sub2:
                cmp     dl,110b
                jnz     try_again_3_sub3
                ; btr
                mov     dx,offset btr_text
                jmp     try_again_3_success
              try_again_3_sub3:
                cmp     dl,101b
                jnz     try_again_3_sub4
                ; bts
                mov     dx,offset bts_text
                jmp     try_again_3_success
              try_again_3_sub4:
                ; Who knows what it is?  Maybe it's an instruction to be decoded later, continue searching
                jmp     try_again4

              try_again_3_success:
                call    display_instruction_with_mod_reg_rm
                jmp     next_instruction

          try_again4:
            mov     dl,ah
            and     dl,11111110b
            cmp     dl,10110000b
            jz      @F
            jmp     try_again5
          @@:
            ; cmpxchg
                mov     dl,ah
                and     dl,1b
                mov     CS:byte_word_size,dl
                mov     dx,offset cmpxchg_text
                mov     bl,3
                mov     cx,7
                call    display_instruction_with_mod_reg_rm
                jmp     next_instruction

          try_again5:
            mov     dl,ah
            and     dl,11110000b
            cmp     dl,10000000b
            jz      @F
            jmp     try_again6
          @@:
            ; It's jccc disp2
                mov     bl,4
                mov     dl,ah
                and     dl,1111b
                cmp     dl,0000b
                jnz     try_again5_sub1
                ; It's jo
                mov     dx,offset jo_text
                mov     cx,2
                jmp     try_again5_success
              try_again5_sub1:
                cmp     dl,0001b
                jnz     try_again5_sub2
                ; It's jno
                mov     dx,offset jno_text
                mov     cx,3
                jmp     try_again5_success
              try_again5_sub2:
                cmp     dl,0010b
                jnz     try_again5_sub3
                ; It's jc/jb/jnae (unsigned)
                mov     dx,offset jc_text
                mov     cx,2
                jmp     try_again5_success
              try_again5_sub3:
                cmp     dl,0011b
                jnz     try_again5_sub4
                ; It's jnc/jnb/jae (unsigned)
                mov     dx,offset jnc_text
                mov     cx,3
                jmp     try_again5_success
              try_again5_sub4:
                cmp     dl,0100b
                jnz     try_again5_sub5
                ; It's jz/je
                mov     dx,offset jz_text
                mov     cx,2
                jmp     try_again5_success
              try_again5_sub5:
                cmp     dl,0101b
                jnz     try_again5_sub6
                ; It's jnz/jne
                mov     dx,offset jnz_text
                mov     cx,3
                jmp     try_again5_success
              try_again5_sub6:
                cmp     dl,0110b
                jnz     try_again5_sub7
                ; It's jbe/jna (unsigned)
                mov     dx,offset jbe_text
                mov     cx,3
                jmp     try_again5_success
              try_again5_sub7:
                cmp     dl,0111b
                jnz     try_again5_sub8
                ; It's ja/jnbe (unsigned)
                mov     dx,offset ja_text
                mov     cx,2
                jmp     try_again5_success
              try_again5_sub8:
                cmp     dl,1000b
                jnz     try_again5_sub9
                ; It's js
                mov     dx,offset js_text
                mov     cx,2
                jmp     try_again5_success
              try_again5_sub9:
                cmp     dl,1001b
                jnz     try_again5_sub10
                ; It's jns
                mov     dx,offset jns_text
                mov     cx,3
                jmp     try_again5_success
              try_again5_sub10:
                cmp     dl,1010b
                jnz     try_again5_sub11
                ; It's jp
                mov     dx,offset jp_text
                mov     cx,2
                jmp     try_again5_success
              try_again5_sub11:
                cmp     dl,1011b
                jnz     try_again5_sub12
                ; It's jnp
                mov     dx,offset jnp_text
                mov     cx,3
                jmp     try_again5_success
              try_again5_sub12:
                cmp     dl,1100b
                jnz     try_again5_sub13
                ; It's jl/jnge (signed)
                mov     dx,offset jl_text
                mov     cx,2
                jmp     try_again5_success
              try_again5_sub13:
                cmp     dl,1101b
                jnz     try_again5_sub14
                ; It's jge/nl (signed)
                mov     dx,offset jge_text
                mov     cx,3
                jmp     try_again5_success
              try_again5_sub14:
                cmp     dl,1110b
                jnz     try_again5_sub15
                ; It's jle/jng (signed)
                mov     dx,offset jle_text
                mov     cx,3
                jmp     try_again5_success
              try_again5_sub15:
                ; It's jg/jnle (signed)                                 ; It's the only combination left
                mov     dx,offset jg_text
                mov     cx,2
              try_again5_success:
                call    display_instruction
                mov     dx,word ptr [si-2]
                call    show_register_16_no_color_signed
                add     di,6*2
                call    show_new_cs_ip
                jmp     next_instruction

          try_again6:
            mov     dl,ah
            mov     dh,ah
            and     dl,11111101b
            and     dh,00000010b
            shr     dh,1
            cmp     dl,00100000b
            jz      @F
            jmp     try_again7
          @@:
            ; It's a "mov creg,reg32; reg32,cref"
                mov     ah,dh
                inc     bx
                mov     dx,offset mov_text
                mov     cx,3
                cmp     ah,0
                jz      @F
                ; Direction is 1
                mov     CS:special_reg,0
              try_again7_direction_1:
                call    display_instruction
                mov     al,byte ptr [si-1]
                and     al,111b
                call    display_register_name_special_reg
                call    display_comma
                mov     al,byte ptr [si-1]
                shr     al,3
                and     al,111b
                call    display_register_name_32
                jmp     next_instruction
              @@:
                ; Direction is 0
                mov     CS:special_reg,0
              try_again7_direction_0:
                call    display_instruction
                mov     al,byte ptr [si-1]
                and     al,111b
                call    display_register_name_32
                call    display_comma
                mov     al,byte ptr [si-1]
                shr     al,3
                and     al,111b
                call    display_register_name_special_reg
                jmp     next_instruction

          try_again7:
            cmp     dl,00100001b
            jz      @F
            jmp     try_again8
            ; It's a "mov dreg,reg32; reg32,dreg"
          @@:
                mov     CS:special_reg,1
                mov     ah,dh
                inc     bx
                mov     dx,offset mov_text
                mov     cx,3
                cmp     ah,0
                jz      @F
                ; Direction is 1
                jmp     try_again7_direction_1
              @@:
                ; Direction is 0
                jmp     try_again7_direction_0
          @@:
          try_again8:
            cmp     dl,00100100b
            jz      @F
            jmp     try_again9
          @@:
            ; It's a "mov treg,reg32; reg32,treg"
                mov     CS:special_reg,2
                mov     ah,dh
                inc     bx
                mov     dx,offset mov_text
                mov     cx,3
                cmp     ah,0
                jz      @F
                ; Direction is 1
                jmp     try_again7_direction_1
              @@:
                ; Direction is 0
                jmp     try_again7_direction_0

          try_again9:
            mov     dl,ah
            mov     dh,ah
            and     dl,11111110b
            and     dh,00000001b
            cmp     dl,10111110b
            jz      @F
            jmp     try_again10
          @@:
            ; It's movsx
                mov     CS:byte_word_size,dh
                mov     dx,offset movsx_text
                mov     cx,5
                inc     bx
                call    display_instruction_with_mod_reg_rm_movxx
                jmp     next_instruction
          try_again10:
            cmp     dl,10110110b
            jz      @F
            jmp     try_again11
          @@:
            ; It's movzx
                mov     CS:byte_word_size,dh
                mov     dx,offset movzx_text
                mov     cx,5
                inc     bx
                call    display_instruction_with_mod_reg_rm_movxx
                jmp     next_instruction

          try_again11:
            mov     dl,ah
            and     dl,11110000b
            cmp     dl,10010000b
            jz      @F
            jmp     try_again12
          @@:
            ; It's setccc
                mov     bl,3
                mov     dl,ah
                and     dl,1111b
                cmp     dl,0000b
                jnz     try_again11_sub1
                ; It's seto
                mov     dx,offset seto_text
                mov     cx,4
                jmp     try_again11_success
              try_again11_sub1:
                cmp     dl,0001b
                jnz     try_again11_sub2
                ; It's setno
                mov     dx,offset setno_text
                mov     cx,5
                jmp     try_again11_success
              try_again11_sub2:
                cmp     dl,0010b
                jnz     try_again11_sub3
                ; It's setc/setb/setnae (unsigned)
                mov     dx,offset setc_text
                mov     cx,4
                jmp     try_again11_success
              try_again11_sub3:
                cmp     dl,0011b
                jnz     try_again11_sub4
                ; It's setnc/setnb/setae (unsigned)
                mov     dx,offset setnc_text
                mov     cx,5
                jmp     try_again11_success
              try_again11_sub4:
                cmp     dl,0100b
                jnz     try_again11_sub5
                ; It's setz/sete
                mov     dx,offset setz_text
                mov     cx,4
                jmp     try_again11_success
              try_again11_sub5:
                cmp     dl,0101b
                jnz     try_again11_sub6
                ; It's setnz/setne
                mov     dx,offset setnz_text
                mov     cx,5
                jmp     try_again11_success
              try_again11_sub6:
                cmp     dl,0110b
                jnz     try_again11_sub7
                ; It's setbe/setna (unsigned)
                mov     dx,offset setbe_text
                mov     cx,5
                jmp     try_again11_success
              try_again11_sub7:
                cmp     dl,0111b
                jnz     try_again11_sub8
                ; It's seta/setnbe (unsigned)
                mov     dx,offset seta_text
                mov     cx,4
                jmp     try_again11_success
              try_again11_sub8:
                cmp     dl,1000b
                jnz     try_again11_sub9
                ; It's sets
                mov     dx,offset sets_text
                mov     cx,4
                jmp     try_again11_success
              try_again11_sub9:
                cmp     dl,1001b
                jnz     try_again11_sub10
                ; It's setns
                mov     dx,offset setns_text
                mov     cx,5
                jmp     try_again11_success
              try_again11_sub10:
                cmp     dl,1010b
                jnz     try_again11_sub11
                ; It's setp
                mov     dx,offset setp_text
                mov     cx,4
                jmp     try_again11_success
              try_again11_sub11:
                cmp     dl,1011b
                jnz     try_again11_sub12
                ; It's setnp
                mov     dx,offset setnp_text
                mov     cx,5
                jmp     try_again11_success
              try_again11_sub12:
                cmp     dl,1100b
                jnz     try_again11_sub13
                ; It's setl/setnge (signed)
                mov     dx,offset setl_text
                mov     cx,4
                jmp     try_again11_success
              try_again11_sub13:
                cmp     dl,1101b
                jnz     try_again11_sub14
                ; It's setge/nl (signed)
                mov     dx,offset setge_text
                mov     cx,5
                jmp     try_again11_success
              try_again11_sub14:
                cmp     dl,1110b
                jnz     try_again11_sub15
                ; It's setle/setng (signed)
                mov     dx,offset setle_text
                mov     cx,5
                jmp     try_again11_success
              try_again11_sub15:
                ; It's setg/setnle (signed)                                 ; It's the only combination left
                mov     dx,offset setg_text
                mov     cx,4
              try_again11_success:
                mov     CS:byte_word_size,0
                call    display_instruction_with_mod_rm
                jmp     next_instruction

          try_again12:
            and     dl,11111110b
            cmp     dl,11000000b
            jz      @F
            jmp     try_again13
          @@:
            ; It's xadd
                mov     bl,3
                mov     dl,al
                and     dl,1b
                mov     CS:byte_word_size,dl
                mov     dx,offset xadd_text
                mov     cx,4
                call    display_instruction_with_mod_reg_rm
                jmp     next_instruction

          try_again13:
            mov     bl,3                                            ; This next batch of instructions are all at least 3 bytes
            cmp     ah,00000000b
            jz      @F
            jmp     try_again14
          @@:
            ; It's sldt, str, lldg, ltr, verr or verw
                mov     dl,byte ptr [si+2]
                shr     dl,3
                and     dl,111b
                cmp     dl,000b
                jz      @F
                jmp     try_again13_sub1
              @@:
                ; It's sldt
                    mov     dx,offset sldt_text
                    mov     cx,4
                    jmp     try_again13_success
              try_again13_sub1:
                cmp     dl,001b
                jz      @F
                jmp     try_again13_sub2
              @@:
                ; It's str
                    mov     dx,offset str_text
                    mov     cx,3
                    jmp     try_again13_success
              try_again13_sub2:
                cmp     dl,010b
                jz      @F
                jmp     try_again13_sub3
              @@:
                ; It's lldt
                    mov     dx,offset lldt_text
                    mov     cx,4
                    jmp     try_again13_success
              try_again13_sub3:
                cmp     dl,011b
                jz      @F
                jmp     try_again13_sub4
              @@:
                ; It's ltr
                    mov     dx,offset ltr_text
                    mov     cx,3
                    jmp     try_again13_success
              try_again13_sub4:
                cmp     dl,100b
                jz      @F
                jmp     try_again13_sub5
              @@:
                ; It's verr
                    mov     dx,offset verr_text
                    mov     cx,4
                    jmp     try_again13_success
              try_again13_sub5:
                cmp     dl,101b
                jz      @F
                jmp     try_again13_sub6
              @@:
                ; It's verw
                    mov     dx,offset verw_text
                    mov     cx,4
              try_again13_success:
                call    display_instruction_with_mod_rm
                jmp     next_instruction

              try_again13_sub6:
                ; Don't know what it is, continue looking
                jmp     try_again14

          try_again14:
            cmp     ah,00000001b
            jz      @F
            jmp     try_again15
          @@:
            ; It's sgdt, sidt, lgdt, lidt, smsw, lmsw or invlpg
                mov     cx,4
                mov     dl,byte ptr [si+2]
                shr     dl,3
                and     dl,111b
                cmp     dl,000b
                jz      @F
                jmp     try_again14_sub1
              @@:
                ; It's sgdt
                    mov     dx,offset sgdt_text
                    jmp     try_again14_success
              try_again14_sub1:
                cmp     dl,001b
                jz      @F
                jmp     try_again14_sub2
              @@:
                ; It's sidt
                    mov     dx,offset sidt_text
                    jmp     try_again14_success
              try_again14_sub2:
                cmp     dl,010b
                jz      @F
                jmp     try_again14_sub3
              @@:
                ; It's lgdt
                    mov     dx,offset lgdt_text
                    jmp     try_again14_success
              try_again14_sub3:
                cmp     dl,011b
                jz      @F
                jmp     try_again14_sub4
              @@:
                ; It's lidt
                    mov     dx,offset lidt_text
                    jmp     try_again14_success
              try_again14_sub4:
                cmp     dl,100b
                jz      @F
                jmp     try_again14_sub5
              @@:
                ; It's smsw
                    mov     dx,offset smsw_text
                    jmp     try_again14_success
              try_again14_sub5:
                cmp     dl,110b
                jz      @F
                jmp     try_again14_sub6
              @@:
                ; It's lmsw
                    mov     dx,offset lmsw_text
                    jmp     try_again14_success
              try_again14_sub6:
                cmp     dl,111b
                jz      @F
                jmp     try_again14_sub7
              @@:
                ; It's invlpg
                    mov     dx,offset invlpg_text
                    mov     cx,6
;                    jmp     try_again14_success
              try_again14_success:
                call    display_instruction_with_mod_rm
                jmp     next_instruction

              try_again14_sub7:
                ; Who knows what is is, continue looking
                jmp     try_again15

          try_again15:
            cmp     ah,00000010b
            jz      @F
            jmp     try_again16
          @@:
            ; It's lar
                inc     bx
                mov     dx,offset lar_text
                mov     cx,3
                call    display_instruction_with_mod_reg_rm
                jmp     next_instruction

          try_again16:
            cmp     ah,00000011b
            jz      @F
            jmp     try_again17
          @@:
            ; It's lsl
                inc     bx
                mov     dx,offset lsl_text
                mov     cx,3
                call    display_instruction_with_mod_reg_rm
                jmp     next_instruction

          try_again17:
            mov     cx,4
            cmp     ah,10100100b
            jz      @F
            jmp     try_again18
          @@:
            ; It's shld by immed
                mov     dx,offset shld_text
                jmp     show_instruction

          try_again18:
            cmp     ah,10100101b
            jz      @F
            jmp     try_again19
          @@:
            ; It's shld by cl
                mov     dx,offset shld_text
                jmp     show_instruction

          try_again19:
            cmp     ah,10101100b
            jz      @F
            jmp     try_again20
          @@:
            ; It's shrd by immed
                mov     dx,offset shrd_text
                jmp     show_instruction

          try_again20:
            cmp     ah,10101101b
            jz      @F
            jmp     try_again21
          @@:
            ; It's shrd by cl
                mov     dx,offset shrd_text
                jmp     show_instruction

          try_again21:
            cmp     ah,10101111b
            jz      @F
            jmp     try_again22
          @@:
            ; It's imul
                inc     bx
                mov     dx,offset imul_text
                call    display_instruction_with_mod_reg_rm
                jmp     next_instruction

          try_again22:
            mov     cx,3
            cmp     ah,10110010b
            jz      @F
            jmp     try_again23
          @@:
            ; lss
                mov     CS:reverse_regs,1
                mov     dx,offset lss_text
                mov     bx,3
                call    display_instruction_with_mod_reg_rm
                jmp     next_instruction

          try_again23:
            cmp     ah,10110100b
            jz      @F
            jmp     try_again24
          @@:
            ; lfs
                mov     CS:reverse_regs,1
                mov     dx,offset lfs_text
                mov     bx,3
                call    display_instruction_with_mod_reg_rm
                jmp     next_instruction

          try_again24:
            cmp     ah,10110101b
            jz      @F
            jmp     try_again25
          @@:
            ; lgs
                mov     CS:reverse_regs,1
                mov     dx,offset lgs_text
                mov     bx,3
                call    display_instruction_with_mod_reg_rm
                jmp     next_instruction

          try_again25:
            cmp     ah,10111010b
            jz      @F
            jmp     try_again26
          @@:
            ; It's bt/btc/btr/btc
                mov     cx,3
                mov     dl,byte ptr [si+2]
                shr     dl,3
                and     dl,111b
                cmp     dl,100b
                jnz     @F
                mov     dx,offset bt_text
                mov     cx,2
                jmp     try_again25_success
              @@:
                cmp     dl,101b
                jnz     @F
                mov     dx,offset bts_text
                jmp     try_again25_success
              @@:
                cmp     dl,110b
                jnz     @F
                mov     dx,offset btr_text
                jmp     try_again25_success
              @@:
                cmp     dl,111b
                jnz     try_again26
                mov     dx,offset btc_text
              try_again25_success:
                jmp     show_instruction

          try_again26:
            cmp     ah,10111100b
            jz      @F
            jmp     try_again27
          @@:
            ; It's bsf
                mov     dx,offset bsf_text
                jmp     show_instruction

          try_again27:
            cmp     ah,10111101b
            jz      @F
            jmp     try_again28
          @@:
            ; It's bsr
                mov     dx,offset bsr_text
                jmp     show_instruction

          try_again28:
            jmp     unknown_instruction
        .ENDIF
        jmp     show_instruction

  one_byte_instructions:
    mov     cx,3                                                    ; Assume 3-byte widths
    mov     bx,1                                                    ; The next group are all one-byte instructions
    .IF (al == 00110111b)
      ; aaa
        mov     dx,offset aaa_text
    .ELSEIF (al ==  00111111b)
      ; aas
        mov     dx,offset aas_text
    .ELSEIF (al ==  10011000b)
      ; cbw
        cmp     CS:op_size_override,0
        jz      @F
            mov     dx,offset cwde_text
            mov     cx,4
            dec     si                                              ; This just become a two-byte instruction, backup one byte
            inc     bl
            jmp     show_instruction
        @@:
            mov     dx,offset cbw_text
    .ELSEIF (al ==  10011001b)
      ; cwd
        cmp     CS:op_size_override,0
        jz      @F
            mov     dx,offset cdq_text
            dec     si                                              ; This just become a two-byte instruction, backup one byte
            inc     bl
            jmp     show_instruction
        @@:
            mov     dx,offset cwd_text
    .ELSEIF (al ==  11111000b)
      ; clc
        mov     dx,offset clc_text
        mov     cx,3
    .ELSEIF (al ==  11111100b)
      ; cld
        mov     dx,offset cld_text
        mov     cx,3
    .ELSEIF (al ==  11111010b)
      ; cli
        mov     dx,offset cli_text
        mov     cx,3
    .ELSEIF (al ==  11110101b)
      ; cmc
        mov     dx,offset cmc_text
        mov     cx,3
    .ELSEIF (al ==  00100111b)
      ; daa
        mov     dx,offset daa_text
        mov     cx,3
    .ELSEIF (al ==  00101111b)
      ; das
        mov     dx,offset das_text
        mov     cx,3
    .ELSEIF (al ==  11110100b)
      ; hlt
        mov     dx,offset hlt_text
        mov     cx,3
    .ELSEIF (al ==  11001110b)
      ; into
        mov     dx,offset into_text
        mov     cx,4
    .ELSEIF (al ==  11001111b)
      ; iret
        cmp     CS:op_size_override,0
        jz      @F
            mov     dx,offset iretd_text
            mov     cx,5
            dec     si                                              ; This just become a two-byte instruction, backup one byte
            mov     bl,2
            jmp     show_instruction
        @@:
            mov     dx,offset iret_text
            mov     cx,4
    .ELSEIF (al ==  10011111b)
      ; lahf
        mov     dx,offset lahf_text
        mov     cx,4
    .ELSEIF (al ==  11001001b)
      ; leave
        mov     dx,offset leave_text
        mov     cx,5
    .ELSEIF (al ==  11110000b)
      ; lock
        mov     dx,offset lock_text
        mov     cx,4
    .ELSEIF (al == 0f3h)
      ; rep/repe prefix
        mov     dx,offset rep_text
        mov     cx,3
        mov     AX,2*2
        call    display_instruction_shifted
        jmp     next_instruction
    .ELSEIF (al == 0f2h)
      ; repne prefix
        mov     dx,offset repne_text
        mov     cx,5
        mov     AX,2*2
        call    display_instruction_shifted
        jmp     next_instruction
    .ELSEIF (al ==  10010000b)
      ; nop
        mov     dx,offset nop_text
        mov     cx,3
    .ELSEIF (al ==  11001100b)
      ; int3
        mov     dx,offset int3_text
        mov     cx,4
    .ELSEIF (al ==  01100001b)
      ; popa
        cmp     CS:op_size_override,0
        jz      @F
            mov     dx,offset popad_text
            mov     cx,5
            dec     si                                              ; This just become a two-byte instruction, backup one byte
            mov     bl,2
            jmp     show_instruction
        @@:
            mov     dx,offset popa_text
            mov     cx,4
    .ELSEIF (al ==  10011101b)
      ; popf
        cmp     CS:op_size_override,0
        jz      @F
            mov     dx,offset popfd_text
            mov     cx,5
            jmp     show_instruction
        @@:
            mov     dx,offset popf_text
            mov     cx,4
    .ELSEIF (al ==  01100000b)
      ; pusha
        cmp     CS:op_size_override,0
        jz      @F
            mov     dx,offset pushad_text
            mov     cx,6
            dec     si                                              ; This just become a two-byte instruction, backup one byte
            mov     bl,2
            jmp     show_instruction
        @@:
            mov     dx,offset pusha_text
            mov     cx,5
    .ELSEIF (al ==  10011100b)
      ; pushf
        cmp     CS:op_size_override,0
        jz      @F
            mov     dx,offset pushfd_text
            mov     cx,6
            dec     si                                              ; This just become a two-byte instruction, backup one byte
            mov     bl,2
            jmp     show_instruction
        @@:
            mov     dx,offset pushf_text
            mov     cx,5
    .ELSEIF (al ==  11000011b)
      ; ret
        mov     dx,offset ret_text
    .ELSEIF (al == 11001011b)
      ; retf
        mov     dx,offset retf_text
        mov     cx,4
    .ELSEIF (al == 11001010b)
      ; retf
        mov     dx,offset retf_text
        mov     bl,3
        call    display_instruction
        mov     dx,word ptr [si-2]
        call    show_register_16_no_color
        jmp     next_instruction
    .ELSEIF (al ==  10011110b)
      ; sahf
        mov     dx,offset sahf_text
        mov     cx,4
    .ELSEIF (al ==  11111001b)
      ; stc
        mov     dx,offset stc_text
    .ELSEIF (al ==  11111101b)
      ; std
        mov     dx,offset std_text
    .ELSEIF (al ==  11111011b)
      ; sti
        mov     dx,offset sti_text
    .ELSEIF (al ==  10011011b)
      ; wait
        mov     dx,offset wait_text
        mov     cx,4
    .ELSEIF (al ==  11010111b)
      ; xlat
        mov     cx,4
        mov     dx,offset xlat_text
        call    display_instruction
        call    display_segment_override
        jmp     next_instruction
    .ELSE
        jmp     two_byte_instructions
    .ENDIF
  ; It was a one-byte instruction
    jmp     show_instruction

  two_byte_instructions:
    mov     bx,2
    .IF (AX == 0000101011010101b)
      ; aad
        mov     dx,offset aad_text
    .ELSEIF (AX == 0000101011010100b)
      ; aam
        mov     dx,offset aam_text
    .ELSEIF (al == 01100011b)
      ; arpl
        mov     dx,offset arpl_text
        mov     cx,4
        call    display_instruction_with_mod_reg_rm
        jmp     next_instruction
    .ELSEIF (al == 01100010b)
      ; bound
        mov     dx,offset bound_text
        mov     cx,5
    .ELSEIF (al == 11101000b)
      ; call
        mov     bx,3
        mov     dx,offset call_text
        mov     cx,4
        call    display_instruction
        mov     dx,word ptr [si-2]
        call    show_register_16_no_color_signed
        add     di,6*2
        call    show_new_cs_ip
        jmp     next_instruction
    .ELSEIF (al == 10011010b)
      ; call
        add     bx,4
        mov     dx,offset call_text
        mov     cx,4
        call    display_instruction
        mov     edx,dword ptr [si-4]
        call    show_register_32_no_color_signed
        add     di,10*2
        call    show_new_cs_ip_far
        jmp     next_instruction
    .ELSEIF (al == 11111111b)
      ; call, jmp or push
        mov     dl,ah
        shr     dl,3
        and     dl,0111b
        .IF (dl == 010b)
          ; call near ptr; ax
            mov     dx,offset call_text
            mov     cx,4
            call    display_instruction_with_mod_rm
            jmp     next_instruction
        .ELSEIF (dl == 011b)
          ; call far ptr [di]
            mov     dx,offset call_far_text
            mov     cx,5
            call    display_instruction_with_mod_rm
            jmp     next_instruction
        .ELSEIF (dl == 100b)
          ; jmp ax; word ptr
            mov     dx,offset jmp_text
            call    display_instruction_with_mod_rm
            jmp     next_instruction
        .ELSEIF (dl == 101b)
          ; jmp far ptr [di]
            mov     dx,offset jmp_far_text
            mov     cx,4
            call    display_instruction_with_mod_rm
            jmp     next_instruction
        .ELSEIF (dl == 110b)
          ; push mem16
            mov     bx,2
            .IF (CS:op_size_override == 0)
                mov     dx,offset push_text
                mov     cx,4
            .ELSE
                mov     dx,offset pushd_text
                mov     cx,5
            .ENDIF
            call    display_instruction_with_mod_rm
            jmp     next_instruction
        .ELSE
          ; Who knows, it might be decoded later because we didn't hit all bit combinations
            jmp     @F
        .ENDIF
    .ELSE
        jmp     @F
    .ENDIF
    jmp     show_instruction

  @@:
    .IF (al == 11001000b)
      ; enter
        mov     bx,4
        mov     dx,offset enter_text
        mov     cx,5
        call    display_instruction
        mov     dx,word ptr [si-3]
        call    show_register_16_no_color
        add     di,4*2
        call    display_comma
        mov     dl,byte ptr [si-1]
        call    show_register_8_no_color
        jmp     next_instruction
    .ELSEIF (al == 11001101b)
      ; int
        mov     bx,2
        mov     dx,offset int_text
        call    display_instruction
        mov     dl,byte ptr [si-1]
        call    show_register_8_no_color
        jmp     next_instruction
    .ELSEIF (al == 11100011b)
      ; jcxz
        mov     bx,2
        .IF (CS:adr_size_override == 0)
            mov     dx,offset jcxz_text
            mov     cx,4
        .ELSE
            dec     si
            inc     bx
            mov     dx,offset jecxz_text
            mov     cx,5
        .ENDIF
      show_new_disp1_address:
        call    display_instruction
        xor     dx,dx
        mov     dl,byte ptr [si-1]
        call    show_register_8_no_color_signed
        add     di,4*2
        call    show_new_cs_ip
        jmp     next_instruction
    .ELSEIF (al == 11101011b)
      ; jmp disp1
        mov     bx,2
        mov     cx,3
        mov     dx,offset jmp_text
        jmp     show_new_disp1_address
    .ELSEIF (al == 11101001b)
      ; jmp disp2/disp4
        mov     bx,3
        mov     dx,offset jmp_text
        .IF (CS:op_size_override != 0)
            add     bx,2
            call    display_instruction
            mov     edx,dword ptr [si-4]
            call    show_register_32_no_color
            add     di,9*2
            call    show_new_cs_ip_far
        .ELSE
            call    display_instruction
            mov     dx,word ptr [si-4]
            call    show_register_16_no_color
            add     di,5*2
            call    show_new_cs_ip
        .ENDIF
        jmp     next_instruction
    .ELSEIF (al == 11101010b)
      ; jmp disp4/disp6
        mov     bx,5
        mov     dx,offset jmp_text
        .IF (CS:op_size_override != 0)
            add     bx,2
            call    display_instruction
            mov     dx,word ptr [si-6]
            call    show_register_16_no_color
            add     di,4*2
            call    display_colon
            mov     edx,dword ptr [si-4]
            call    show_register_32_no_color
        .ELSE
            call    display_instruction
            mov     edx,dword ptr [si-4]
            call    show_register_32_no_color
            add     di,9*2
            call    show_new_cs_ip_far
        .ENDIF
        jmp     next_instruction
    .ELSEIF (al == 11000101b)
      ; lds
        mov     CS:reverse_regs,1
        mov     bx,2
        mov     dx,offset lds_text
        call    display_instruction_with_mod_reg_rm
        jmp     next_instruction
    .ELSEIF (al == 11000100b)
      ; les
        mov     CS:reverse_regs,1
        mov     bx,2
        mov     dx,offset les_text
        call    display_instruction_with_mod_reg_rm
        jmp     next_instruction
    .ELSEIF (al == 10001101b)
      ; lea
        mov     CS:reverse_regs,1
        mov     bx,2
        mov     dx,offset lea_text
        call    display_instruction_with_mod_reg_rm
        jmp     next_instruction
    .ELSEIF (al == 11100010b)
      ; loop
        mov     bx,2
        mov     dx,offset loop_text
        mov     cx,4
      loop_instructions:
        call    display_instruction
        .IF (CS:op_size_override != 0)
            mov     al,CONST_ECX
            call    display_register_name_32
            add     di,1*2
        .ENDIF
        xor     dx,dx
        mov     dl,byte ptr [si-1]
        call    show_register_8_no_color_signed
        add     di,4*2
        call    show_new_cs_ip
        jmp     next_instruction
    .ELSEIF (al == 11100001b)
      ; loope
        mov     dx,offset loope_text
        mov     cx,5
        jmp     loop_instructions
    .ELSEIF (al == 11100000b)
      ; loopne
        mov     dx,offset loopne_text
        mov     cx,6
        jmp     loop_instructions
    .ELSEIF (al == 11000010b)
      ; ret immed
        mov     bx,3
        mov     dx,offset ret_text
        call    display_instruction
        mov     dx,word ptr [si-2]
        call    show_register_16_no_color
        jmp     next_instruction
    .ELSEIF (al == 10001111b)
      ; might be pop
        mov     dl,ah
        shr     dl,3
        and     dl,0111b
        cmp     dl,000b
        jnz     @F
        ; It's pop
        mov     dx,offset pop_text
        mov     bx,2
        call    display_instruction_with_mod_rm
        jmp     next_instruction
    .ELSE
        jmp     @F
    .ENDIF
    jmp     show_instruction

  @@:
    mov     dl,al
    shr     dl,1
    mov     dh,al
    and     dh,1b
  ; Check the instructions that have fixed left-7 bits
    mov     cx,4
    mov     bx,1
    .IF (dl == 1010010b)
      ; movs
        mov     cx,5
        .IF (dh == 0)
            mov     dx,offset movsb_text
        .ELSEIF (CS:op_size_override != 0)
            mov     dx,offset movsd_text
        .ELSE
            mov     dx,offset movsw_text
        .ENDIF
        call    display_instruction
        jmp     next_instruction
    .ELSEIF (dl == 1010101b)
      ; stos
        mov     cx,5
        .IF (dh == 0)
            mov     dx,offset stosb_text
        .ELSEIF (CS:op_size_override != 0)
            mov     dx,offset stosd_text
        .ELSE
            mov     dx,offset stosw_text
        .ENDIF
        call    display_instruction
        jmp     next_instruction
    .ELSEIF (dl == 1010110b)
      ; lods
        mov     cx,5
        .IF (dh == 0)
            mov     dx,offset lodsb_text
        .ELSEIF (CS:op_size_override != 0)
            mov     dx,offset lodsd_text
        .ELSE
            mov     dx,offset lodsw_text
        .ENDIF
        call    display_instruction
        jmp     next_instruction
    .ELSEIF (dl == 0110110b)
      ; ins
        mov     cx,4
        mov     bx,1
        .IF (dh == 0)
            mov     dx,offset insb_text
        .ELSEIF (CS:op_size_override != 0)
            mov     dx,offset insd_text
        .ELSE
            mov     dx,offset insw_text
        .ENDIF
        call    display_instruction
        mov     al,CONST_ES
        call    display_register_name_sreg
        call    display_colon
        call    display_open_bracket
        mov     al,CONST_DI
        call    display_register_name_16
        call    display_close_bracket
        call    display_comma
        mov     al,CONST_DX
        call    display_register_name_16
        jmp     next_instruction
    .ELSEIF (dl == 0110111b)
      ; outs
        mov     cx,5
        mov     bx,1
        .IF (dh == 0)
            mov     dx,offset outsb_text
        .ELSEIF (CS:op_size_override != 0)
            mov     dx,offset outsd_text
        .ELSE
            mov     dx,offset outsw_text
        .ENDIF
        call    display_instruction
        mov     al,CONST_DX
        call    display_register_name_16
        call    display_comma
        mov     al,CONST_DS
        call    display_register_name_sreg
        call    display_colon
        call    display_open_bracket
        mov     al,CONST_SI
        call    display_register_name_16
        call    display_close_bracket
        jmp     next_instruction
    .ELSEIF (dl == 1010011b)
      ; cmps
        mov     cx,5
        .IF (dh == 0)
            mov     dx,offset cmpsb_text
        .ELSEIF (CS:op_size_override != 0)
            mov     dx,offset cmpsd_text
        .ELSE
            mov     dx,offset cmpsw_text
        .ENDIF
        call    display_instruction
        jmp     next_instruction
    .ELSEIF (dl == 1010111b)
      ; scas
        mov     cx,5
        .IF (dh == 0)
            mov     dx,offset scasb_text
        .ELSEIF (CS:op_size_override != 0)
            mov     dx,offset scasd_text
        .ELSE
            mov     dx,offset scasw_text
        .ENDIF
        call    display_instruction
        jmp     next_instruction
    .ELSEIF (dl == 0000010b)
      ; add accum,immed
        mov     al,dh
        mov     dx,offset add_text
        mov     cx,3
      display_accum_instruction:
        .IF (al == 0)
            mov     bx,2
            call    display_instruction
            mov     al,CONST_AL
            call    display_register_name_8
            call    display_comma
            mov     dl,byte ptr [si-1]
            call    show_register_8_no_color
        .ELSE
            .IF (CS:op_size_override != 0)
              ; eax
                mov     bx,5
                call    display_instruction
                mov     al,CONST_EAX
                call    display_register_name_32
                call    display_comma
                mov     edx,dword ptr [si-4]
                call    show_register_32_no_color
            .ELSE
              ; ax
                mov     bx,3
                call    display_instruction
                mov     al,CONST_AX
                call    display_register_name_16
                call    display_comma
                mov     dx,word ptr [si-2]
                call    show_register_16_no_color
            .ENDIF
        .ENDIF
        jmp     next_instruction
    .ELSEIF (dl == 0000110b)
      ; or accum,immed
        mov     al,dh
        mov     dx,offset or_text
        mov     cx,2
        jmp     display_accum_instruction
    .ELSEIF (dl == 0001010b)
      ; adc accum,immed
        mov     al,dh
        mov     dx,offset adc_text
        mov     cx,3
        jmp     display_accum_instruction
    .ELSEIF (dl == 0001110b)
      ; sbb accum,immed
        mov     al,dh
        mov     dx,offset sbb_text
        mov     cx,3
        jmp     display_accum_instruction
    .ELSEIF (dl == 0010010b)
      ; and accum,immed
        mov     al,dh
        mov     dx,offset and_text
        mov     cx,3
        jmp     display_accum_instruction
    .ELSEIF (dl == 0010110b)
      ; sub accum,immed
        mov     al,dh
        mov     dx,offset sub_text
        mov     cx,3
        jmp     display_accum_instruction
    .ELSEIF (dl == 0011010b)
      ; xor accum,immed
        mov     al,dh
        mov     dx,offset xor_text
        mov     cx,3
        jmp     display_accum_instruction
    .ELSEIF (dl == 0011110b)
      ; cmp accum,immed
        mov     al,dh
        mov     dx,offset cmp_text
        mov     cx,3
        jmp     display_accum_instruction
    .ELSEIF (dl == 1000010b)
      ; test reg,reg; reg,mem; mem,reg
        mov     CS:byte_word_size,dh
        mov     bx,2
        mov     dx,offset test_text
        mov     cx,4
        call    display_instruction_with_mod_reg_rm
        jmp     next_instruction
    .ELSEIF (dl == 1010100b)
      ; test accum,immed
        mov     al,dh
        mov     dx,offset test_text
        mov     cx,4
        jmp     display_accum_instruction
    .ELSEIF (dl == 1110010b)
      ; in ax,60h
        mov     bx,2
        mov     dx,offset in_text
        mov     cx,2
        call    display_instruction
        .IF (dh == 0)
          ; al
            mov     al,CONST_AL
            call    display_register_name_8
        .ELSE
            .IF (CS:op_size_override != 0)
              ; eax
                mov     al,CONST_EAX
                call    display_register_name_32
            .ELSE
              ; ax
                mov     al,CONST_AX
                call    display_register_name_16
            .ENDIF
        .ENDIF
        call    display_comma
        mov     dl,byte ptr [si-1]
        call    show_register_8_no_color
        jmp     next_instruction
    .ELSEIF (dl == 1110011b)
      ; out 60h,al
        mov     bx,2
        mov     dx,offset outsb_text
        mov     cx,3
        call    display_instruction
        mov     dl,byte ptr [si-1]
        call    show_register_8_no_color
        add     di,2*2
        call    display_comma
        .IF (dh == 0)
          ; al
            mov     al,CONST_AL
            call    display_register_name_8
        .ELSE
            .IF (CS:op_size_override != 0)
              ; eax
                mov     al,CONST_EAX
                call    display_register_name_32
            .ELSE
              ; ax
                mov     al,CONST_AX
                call    display_register_name_16
            .ENDIF
        .ENDIF
        jmp     next_instruction
    .ELSEIF (dl == 1110110b)
      ; in al,dx
        mov     bx,1
        mov     dx,offset in_text
        mov     cx,2
        .IF (dh == 0)
          ; al
            mov     al,CONST_AL
            call    display_register_name_8
        .ELSE
            .IF (CS:op_size_override != 0)
              ; eax
                mov     al,CONST_EAX
                call    display_register_name_32
            .ELSE
              ; ax
                mov     al,CONST_AX
                call    display_register_name_16
            .ENDIF
        .ENDIF
        call    display_comma
        mov     al,CONST_DX
        call    display_register_name_16
        jmp     next_instruction
    .ELSEIF (dl == 1110111b)
      ; out dx,al
        push    dx
        mov     bx,1
        mov     dx,offset outsb_text
        mov     cx,3
        call    display_instruction
        mov     al,CONST_DX
        call    display_register_name_16
        call    display_comma
        pop     dx
        .IF (dh == 0)
          ; al
            mov     al,CONST_AL
            call    display_register_name_8
        .ELSE
            .IF (CS:op_size_override != 0)
               ; eax
                mov     al,CONST_EAX
                call    display_register_name_32
            .ELSE
               ; ax
                mov     al,CONST_AX
                call    display_register_name_16
            .ENDIF
        .ENDIF
        jmp     next_instruction
    .ELSEIF (dl == 1111011b)
      ; It could be test, not, neg, mul, imul, div, idiv
        mov     bx,2
        mov     CS:byte_word_size,dh
        mov     cx,3
        mov     dh,ah
        shr     dh,3
        and     dh,0111b
        .IF (dh == 000b)
          ; test
            mov     dx,offset test_text
            mov     cx,4
        .ELSEIF (dh == 010b)
          ; not
            mov     dx,offset not_text
        .ELSEIF (dh == 011b)
          ; neg
            mov     dx,offset neg_text
        .ELSEIF (dh == 100b)
          ; mul
            mov     dx,offset mul_text
        .ELSEIF (dh == 101b)
          ; imul
            mov     dx,offset imul_text
            mov     cx,4
        .ELSEIF (dh == 110b)
          ; div
            mov     dx,offset div_text
        .ELSEIF (dh == 111b)
          ; idiv
            mov     dx,offset idiv_text
            mov     cx,4
        .ELSE
          ; It's not one of the recognized encodings, continue to search
            mov     dl,al
            shr     dl,1
            mov     dh,al
            and     dh,1b
            jmp     @F
        .ENDIF
        call    display_instruction_with_mod_rm
        jmp     next_instruction
    .ELSE
        jmp     @F
    .ENDIF
    jmp     show_instruction

  @@:
    mov     ah,byte ptr [si+1]
    shr     ah,3
    and     ah,111b
    .IF (dl == 1111111b)
      ; It could be dec, inc
        mov     CS:byte_word_size,dh
        .IF (ah == 000b)
          ; inc
            mov     dx,offset inc_text
          inc_dec_locals:
            mov     cx,3
            mov     bx,2
            call    display_instruction_with_mod_rm
            jmp     next_instruction
        .ELSEIF (ah == 001b)
          ; dec
            mov     dx,offset dec_text
            jmp     inc_dec_locals
        .ELSE
            jmp     @F
        .ENDIF
        call    display_instruction_with_mod_rm
        jmp     next_instruction
    .ELSEIF (dl == 1100011b)
      ; It could be mov mem,immed
        .IF (ah == 000b)
          ; mov mem,immed
            mov     dl,al
            and     dl,1b
            mov     CS:byte_word_size,dl
            mov     bx,2
            mov     dx,offset mov_text
            mov     cx,3
            call    display_instruction_with_mod_rm
            call    display_comma
            mov     edx,dword ptr [si]
            .IF (CS:byte_word_size == 0)
              ; 8-bits
                call    show_register_8_no_color
                mov     cx,1
            .ELSE
                .IF (CS:op_size_override != 0)
                  ; 32-bits
                    call    show_register_32_no_color
                    mov     cx,4
                .ELSE
                  ; 16-bits
                    call    show_register_16_no_color
                    mov     cx,2
                .ENDIF
            .ENDIF
            call    display_instruction_additional_bytes
            jmp     next_instruction
        .ELSE
            jmp     @F
        .ENDIF
    .ELSEIF (dl == 1100000b)
      ; sar,sal,shl,shr r/m,immed
        mov     cx,3
        mov     bx,2
        .IF (ah == 000b)
          ; rol
            mov     dx,offset rol_text
        .ELSEIF (ah == 001b)
          ; ror
            mov     dx,offset ror_text
        .ELSEIF (ah == 010b)
          ; rcl
            mov     dx,offset rcl_text
        .ELSEIF (ah == 011b)
          ; rcr
            mov     dx,offset rcr_text
        .ELSEIF (ah == 100b)
          ; shl
            mov     dx,offset shl_text
        .ELSEIF (ah == 101b)
          ; shr
            mov     dx,offset shr_text
        .ELSEIF (ah == 111b)
          ; sar
            mov     dx,offset sar_text
        .ELSE
            mov     dx,offset unknown_text
        .ENDIF
        call    display_instruction_with_mod_rm
        mov     dl,byte ptr [si]
        mov     cx,1
        call    display_instruction_additional_bytes
        call    display_comma
        call    show_register_8_no_color
        jmp     next_instruction
    .ELSEIF (dl == 1101000b)
      ; It is either rotate or shift by 1
        mov     cx,3
        mov     bx,2
        .IF (ah == 000b)
          ; rol
            mov     dx,offset rol_text
        .ELSEIF (ah == 001b)
          ; ror
            mov     dx,offset ror_text
        .ELSEIF (ah == 010b)
          ; rcl
            mov     dx,offset rcl_text
        .ELSEIF (ah == 011b)
          ; rcr
            mov     dx,offset rcr_text
        .ELSEIF (ah == 100b)
          ; shl
            mov     dx,offset shl_text
        .ELSEIF (ah == 101b)
          ; shr
            mov     dx,offset shr_text
        .ELSEIF (ah == 111b)
          ; sar
            mov     dx,offset sar_text
        .ELSE
            mov     dx,offset unknown_text
        .ENDIF
        call    display_instruction_with_mod_rm
        call    display_comma
        call    display_one
        jmp     next_instruction
    .ELSEIF (dl == 1101001b)
      ; It is either rotate or shift by cl
        mov     cx,3
        mov     bx,2
        .IF (ah == 000b)
          ; rol
            mov     dx,offset rol_text
        .ELSEIF (ah == 001b)
          ; ror
            mov     dx,offset ror_text
        .ELSEIF (ah == 010b)
          ; rcl
            mov     dx,offset rcl_text
        .ELSEIF (ah == 011b)
          ; rcr
            mov     dx,offset rcr_text
        .ELSEIF (ah == 100b)
          ; shl
            mov     dx,offset shl_text
        .ELSEIF (ah == 101b)
          ; shr
            mov     dx,offset shr_text
        .ELSEIF (ah == 111b)
          ; sar
            mov     dx,offset sar_text
        .ELSE
            mov     dx,offset unknown_text
        .ENDIF
        call    display_instruction_with_mod_rm
        call    display_comma
        mov     al,CONST_CL
        call    display_register_name_8
        jmp     next_instruction
    .ELSEIF (dl == 1000011b)
      ; xchg
        mov     bx,2
        .IF (CS:op_size_override != 0)
            dec     si
            inc     bx
        .ENDIF
        mov     dl,al
        and     dl,1b
        mov     CS:byte_word_size,dl
        mov     dx,offset xchg_text
        mov     cx,4
        mov     CS:reverse_regs,1
        call    display_instruction_with_mod_reg_rm
        jmp     next_instruction
    .ELSE
        jmp     @F
    .ENDIF
    jmp     show_instruction

  @@:
    shr     dl,1
    mov     cx,3
    mov     CS:byte_word_size,dh
    .IF (dl == 000000b)
      ; add
        mov     dx,offset add_text
      local_mod_reg_rm_instructions:
        mov     ah,al
        shr     ah,1
        and     ah,1
        mov     CS:reverse_regs,ah
        mov     bx,2
        call    display_instruction_with_mod_reg_rm
        jmp     next_instruction
    .ELSEIF (dl == 000010b)
      ; or
        mov     dx,offset or_text
        mov     cx,2
        jmp     local_mod_reg_rm_instructions
    .ELSEIF (dl == 000100b)
      ; adc
        mov     dx,offset adc_text
        jmp     local_mod_reg_rm_instructions
    .ELSEIF (dl == 000110b)
      ; sbb
        mov     dx,offset sbb_text
        jmp     local_mod_reg_rm_instructions
    .ELSEIF (dl == 001000b)
      ; and
        mov     dx,offset and_text
        jmp     local_mod_reg_rm_instructions
    .ELSEIF (dl == 001010b)
      ; sub
        mov     dx,offset sub_text
        jmp     local_mod_reg_rm_instructions
    .ELSEIF (dl == 001100b)
      ; xor
        mov     dx,offset xor_text
        jmp     local_mod_reg_rm_instructions
    .ELSEIF (dl == 001110b)
      ; cmp
        mov     dx,offset cmp_text
        jmp     local_mod_reg_rm_instructions
    .ELSEIF (dl == 100000b)
      ; It is one of these; add, or, adc, sbb, and, sub, xor, cmp
        mov     dl,al
        shr     dl,1
        and     dl,1b
        mov     CS:sign_extend,dl
        mov     dl,al
        and     dl,1b
        mov     CS:byte_word_size,dl

        mov     ah,byte ptr [si+1]
        shr     ah,3
        and     ah,111b
        .IF (ah == 000b)
          ; add
            mov     dx,offset add_text
        .ELSEIF (ah == 001b)
          ; or
            mov     dx,offset or_text
            mov     cx,2
        .ELSEIF (ah == 010b)
          ; adc
            mov     dx,offset adc_text
        .ELSEIF (ah == 011b)
          ; sbb
            mov     dx,offset sbb_text
        .ELSEIF (ah == 100b)
          ; and
            mov     dx,offset and_text
        .ELSEIF (ah == 101b)
          ; sub
            mov     dx,offset sub_text
        .ELSEIF (ah == 110b)
          ; xor
            mov     dx,offset xor_text
        .ELSE
          ; cmp
            mov     dx,offset cmp_text
        .ENDIF
        mov     bx,2
        call    display_instruction_with_mod_rm
        call    display_comma
        mov     edx,dword ptr [si]
        .IF (CS:byte_word_size == 0)
          ; 8-bits
            call    show_register_8_no_color
            mov     cx,1
        .ELSE
            .IF (CS:op_size_override != 0)
              ; 32-bits
                call    show_register_32_no_color
                mov     cx,4
            .ELSE
              ; 16-bits
                .IF (CS:sign_extend == 0)
                    call    show_register_16_no_color
                    mov     cx,2
                .ELSE
                    movsx   dx,dl                                   ; Sign extend 8-bits to 16-bits
                    call    show_register_16_no_color
                    mov     cx,1
                .ENDIF
            .ENDIF
        .ENDIF
        call    display_instruction_additional_bytes
        jmp     next_instruction
    .ELSEIF (dl == 100010b)
      ; mov reg,reg; mem,reg; reg,mem
        mov     dl,al
        and     dl,1b
        mov     CS:byte_word_size,dl
        mov     dl,al
        shr     dl,1
        and     dl,1b
        mov     CS:reverse_regs,dl
        mov     dx,offset mov_text
        mov     cx,3
        mov     bx,2
        call    display_instruction_with_mod_reg_rm
        jmp     next_instruction
    .ELSEIF (dl == 101000b)
      ; mov accum,mem; mem,accum
        mov     dh,al
        shr     dh,2
        and     dh,1b
        mov     CS:reverse_regs,dh
        mov     dx,offset mov_text
        mov     cx,3
        mov     bx,1
        call    adjust_for_overrides
        call    display_instruction
        mov     dx,word ptr [si]
        mov     cx,2
        call    display_instruction_additional_bytes
        .IF (CS:reverse_regs == 1)
            call    mov_show_part
            call    display_comma
            call    display_register_name_accumulator
        .ELSE
            call    display_register_name_accumulator
            call    display_comma
            call    mov_show_part
        .ENDIF
        jmp     next_instruction
    .ELSE
        jmp     @F
    .ENDIF
    jmp     show_instruction

mov_show_part:
    call    display_segment_override
    call    display_open_bracket
    call    show_register_16_no_color
    add     di,4*2
    call    display_close_bracket
    ret

  @@:
    shr     dl,1                                                    ; This makes a total of 3 bits shifted, 2 from above
    .IF (dl == 01000b)
      ; inc
        mov     dx,offset inc_text
      inc_dec_locals_2:
        mov     cx,3
        mov     bx,1
        call    display_instruction
        mov     al,byte ptr [si-1]
        and     al,111b
        .IF (CS:op_size_override == 0)
            call    display_register_name_16
        .ELSE
            call    display_register_name_32
        .ENDIF
        jmp     next_instruction
    .ELSEIF (dl == 01001b)
      ; dec
        mov     dx,offset dec_text
        jmp     inc_dec_locals_2
    .ELSEIF (dl == 01010b)
      ; push
        mov     bx,1
        .IF (CS:op_size_override != 0)
            dec     si
            inc     bx
        .ENDIF
        mov     dx,offset push_text
        mov     cx,4
      push_pop_locals:
        call    display_instruction
        mov     al,byte ptr [si-1]
        and     al,0111b
        .IF (CS:op_size_override == 0)
            call    display_register_name_16
        .ELSE
            call    display_register_name_32
        .ENDIF
        jmp     next_instruction
    .ELSEIF (dl == 01011b)
      ; pop
        mov     dx,offset pop_text
        jmp     push_pop_locals
    .ELSEIF (dl == 10010b)
      ; xchg accum,reg
        .IF (CS:op_size_override != 0)
            dec     si
            inc     bx
        .ENDIF
        mov     dx,offset xchg_text
        mov     cx,4
        call    display_instruction
        mov     al,CONST_AX
        .IF (CS:op_size_override == 0)
            call    display_register_name_16
            call    display_comma
            mov     al,byte ptr [si-1]
            and     al,111b
            call    display_register_name_16
        .ELSE
            call    display_register_name_32
            call    display_comma
            mov     al,byte ptr [si-1]
            and     al,111b
            call    display_register_name_32
        .ENDIF
        jmp     next_instruction
    .ELSE
        jmp     @F
    .ENDIF
    jmp     show_instruction

  @@:
    mov     dl,al
    and     dl,11111101b
    .IF (dl == 01101000b)
      ; push
        mov     dx,offset push_text
        mov     cx,4
    .ELSEIF (dl == 01101001b)
      ; imul
        mov     dx,offset imul_text
        mov     cx,4
    .ELSEIF (dl == 10001100b)
      ; mov sreg,reg
        mov     bx,2
        mov     dl,al
        shr     dl,1
        and     dl,1b
        mov     CS:reverse_regs,dl
        mov     CS:sreg_override,1
        mov     CS:byte_word_size,1
        mov     dx,offset mov_text
        mov     cx,3
        call    display_instruction_with_mod_reg_rm
        jmp     next_instruction
    .ELSE
        jmp     @F
    .ENDIF
    jmp     show_instruction

  @@:
    mov     dl,al
    shr     dl,4
    .IF (dl == 1011b)
      ; mov reg,immed
        shr     al,3
        and     al,1b
        mov     CS:byte_word_size,al
        mov     bx,1
        mov     dx,offset mov_text
        mov     cx,3
        call    display_instruction
        mov     al,byte ptr [si-1]
        and     al,111b
        mov     edx,dword ptr [si]
        .IF (CS:byte_word_size == 0)
          ; 8-bit
            call    display_register_name_8
            mov     cx,1
            call    display_comma
            call    display_instruction_additional_bytes
            call    show_register_8_no_color
        .ELSE
            .IF (CS:op_size_override != 0)
              ; 32-bit
                call    display_register_name_32
                mov     cx,4
                call    display_comma
                call    display_instruction_additional_bytes
                call    show_register_32_no_color
            .ELSE
              ; 16-bit
                call    display_register_name_16
                mov     cx,2
                call    display_comma
                call    display_instruction_additional_bytes
                call    show_register_16_no_color
            .ENDIF
        .ENDIF
        jmp     next_instruction
    .ELSEIF (dl == 0111b)
      ; jccc +/- 128
        mov     bx,2
        mov     dl,al
        and     dl,01111b
        .IF (dl == 0000b)
          ; It's jo
            mov     dx,offset jo_text
            mov     cx,2
        .ELSEIF (dl ==  0001b)
          ; It's jno
            mov     dx,offset jno_text
        .ELSEIF (dl ==  0010b)
          ; It's jc/jb/jnae (unsigned)
            mov     dx,offset jc_text
            mov     cx,2
        .ELSEIF (dl ==  0011b)
          ; It's jnc/jnb/jae (unsigned)
            mov     dx,offset jnc_text
        .ELSEIF (dl ==  0100b)
          ; It's jz/je
            mov     dx,offset jz_text
            mov     cx,2
        .ELSEIF (dl ==  0101b)
          ; It's jnz/jne
            mov     dx,offset jnz_text
        .ELSEIF (dl ==  0110b)
          ; It's jbe/jna (unsigned)
            mov     dx,offset jbe_text
        .ELSEIF (dl ==  0111b)
          ; It's ja/jnbe (unsigned)
            mov     dx,offset ja_text
            mov     cx,2
        .ELSEIF (dl ==  1000b)
          ; It's js
            mov     dx,offset js_text
            mov     cx,2
        .ELSEIF (dl ==  1001b)
          ; It's jns
            mov     dx,offset jns_text
        .ELSEIF (dl ==  1010b)
          ; It's jp
            mov     dx,offset jp_text
            mov     cx,2
        .ELSEIF (dl ==  1011b)
          ; It's jnp
            mov     dx,offset jnp_text
        .ELSEIF (dl ==  1100b)
          ; It's jl/jnge (signed)
            mov     dx,offset jl_text
            mov     cx,2
        .ELSEIF (dl ==  1101b)
          ; It's jge/nl (signed)
            mov     dx,offset jge_text
        .ELSEIF (dl ==  1110b)
          ; It's jle/jng (signed)
            mov     dx,offset jle_text
        .ELSE
            ; It's jg/jnle (signed)                                 ; It's the only combination left
            mov     dx,offset jg_text
            mov     cx,2
        .ENDIF
        call    display_instruction
        movsx   dx,byte ptr [si-1]
        call    show_register_8_no_color_signed
        add     di,4*2
        call    show_new_cs_ip
        jmp     next_instruction
    .ELSE
        mov     dl,al
        and     dl,11000111b
        .IF (dl == 00000111b)
          ; pop
            mov     dx,offset pop_text
            mov     cx,3
          push_pop_locals_2:
            call    display_instruction
            shr     al,3
            and     al,111b
            call    display_register_name_sreg
            jmp     next_instruction
        .ELSEIF (dl == 00000110b)
          ; push
            mov     dx,offset push_text
            mov     cx,4
            jmp     push_pop_locals_2
        .ELSE
            jmp     check_fpu_instructions
        .ENDIF
    .ENDIF
  show_instruction:
    call    display_instruction
    jmp     next_instruction


; Check the FPU instructions
  check_fpu_instructions:
    ; Check for FPU instructions
    mov     ax,word ptr [si]
    mov     cx,4                                                    ; Default to a 4-byte wide instruction name
    .IF (al == 0d8h)
        mov     al,ah
        and     al,not 0111b
        .IF (al == 0c0h)
          ; fadd st(0),st(i)
            mov     dx,offset fadd_text
        .ELSEIF (al == 0c8h)
          ; fmul st(0),st(i)
            mov     dx,offset fmul_text
        .ELSEIF (al == 0d0h)
          ; fcom st(0),st(i)
            mov     dx,offset fcom_text
        .ELSEIF (al == 0d8h)
          ; fcomp st(0),st(i)
            mov     dx,offset fcomp_text
            mov     cx,5
        .ELSEIF (al == 0e0h)
          ; fsub st(0),st(i)
            mov     dx,offset fsub_text
        .ELSEIF (al == 0e8h)
          ; fsubr st(0),st(i)
            mov     dx,offset fsubr_text
            mov     cx,5
        .ELSEIF (al == 0f0h)
          ; fdiv st(0),st(i)
            mov     dx,offset fdiv_text
        .ELSEIF (al == 0f8h)
          ; fdivr  st(0),st(i)
            mov     dx,offset fdivr_text
            mov     cx,5
        .ELSE
            jmp     @F
        .ENDIF
        jmp     show_instruction

      @@:
        shr     ah,3
        and     ah,0111b
        .IF (ah == 0)
          ; fadd real32
            mov     dx,offset fadd_text
        .ELSEIF (ah == 1)
          ; fmul real32
            mov     dx,offset fmul_text
        .ELSEIF (ah == 2)
          ; fcom real32
            mov     dx,offset fcom_text
        .ELSEIF (ah == 3)
          ; fcomp real32
            mov     dx,offset fcomp_text
            mov     cx,5
        .ELSEIF (ah == 4)
          ; fsub real32
            mov     dx,offset fsub_text
        .ELSEIF (ah == 5)
          ; fsubr real32
            mov     dx,offset fsubr_text
            mov     cx,5
        .ELSEIF (ah == 6)
          ; fdiv real32
            mov     dx,offset fdiv_text
        .ELSEIF (ah == 7)
          ; fdivr real32
            mov     dx,offset fdivr_text
            mov     cx,5
        .ELSE
          ; Invalid opcode
            jmp     unknown_instruction
        .ENDIF
    .ELSEIF (al == 0d9h)
        mov     al,ah
        and     al,not 0111b
        mov     cx,4
        .IF (al == 0c0h)
          ; fld st(i)
            mov     dx,offset fld_text
            mov     cx,3
        .ELSEIF (al == 0c8h)
          ; fxch st(i)
            mov     dx,offset fxch_text
        .ELSEIF (ah == 0d0h)
          ; fnop
            mov     dx,offset fnop_text
        .ELSEIF (ah == 0e0h)
          ; fchs
            mov     dx,offset fchs_text
        .ELSEIF (ah == 0e1h)
          ; fabs
            mov     dx,offset fabs_text
        .ELSEIF (ah == 0e4h)
          ; ftst
            mov     dx,offset ftst_text
        .ELSEIF (ah == 0e5h)
          ; fxam
            mov     dx,offset fxam_text
        .ELSEIF (ah == 0e8h)
          ; fld1
            mov     dx,offset fld1_text
        .ELSEIF (ah == 0e9h)
          ; fldl2t
            mov     dx,offset fldl2t_text
            mov     cx,6
        .ELSEIF (ah == 0eah)
          ; fldl2e
            mov     dx,offset fldl2e_text
            mov     cx,6
        .ELSEIF (ah == 0ebh)
          ; fldpi
            mov     dx,offset fldpi_text
            mov     cx,5
        .ELSEIF (ah == 0ech)
          ; fldg2
            mov     dx,offset fldg2_text
            mov     cx,5
        .ELSEIF (ah == 0edh)
          ; fldn2
            mov     dx,offset fldn2_text
            mov     cx,5
        .ELSEIF (ah == 0eeh)
          ; fldz
            mov     dx,offset fldz_text
        .ELSEIF (ah == 0f0h)
          ; f2xm1
            mov     dx,offset f2xm1_text
            mov     cx,5
        .ELSEIF (ah == 0f1h)
          ; fyl2x
            mov     dx,offset fyl2x_text
            mov     cx,5
        .ELSEIF (ah == 0f2h)
          ; fptan
            mov     dx,offset fptan_text
            mov     cx,5
        .ELSEIF (ah == 0f3h)
          ; fpatan
            mov     dx,offset fpatan_text
            mov     cx,6
        .ELSEIF (ah == 0f4h)
          ; fxtract
            mov     dx,offset fxtract_text
            mov     cx,7
        .ELSEIF (ah == 0f5h)
          ; fprem1
            mov     dx,offset fprem1_text
            mov     cx,6
        .ELSEIF (ah == 0f6h)
          ; fdecstp
            mov     dx,offset fdecstp_text
            mov     cx,7
        .ELSEIF (ah == 0f7h)
          ; fincstp
            mov     dx,offset fincstp_text
            mov     cx,7
        .ELSEIF (ah == 0f8h)
          ; fprem
            mov     dx,offset fprem_text
            mov     cx,5
        .ELSEIF (ah == 0f9h)
          ; fyl2xp1
            mov     dx,offset fyl2xp1_text
            mov     cx,7
        .ELSEIF (ah == 0fah)
          ; fsqrt
            mov     dx,offset fsqrt_text
            mov     cx,5
        .ELSEIF (ah == 0fbh)
          ; fsincos
            mov     dx,offset fsincos_text
            mov     cx,7
        .ELSEIF (ah == 0fch)
          ; frndint
            mov     dx,offset frndint_text
            mov     cx,7
        .ELSEIF (ah == 0fdh)
          ; fscale
            mov     dx,offset fscale_text
            mov     cx,6
        .ELSEIF (ah == 0feh)
          ; fsin
            mov     dx,offset fsin_text
        .ELSEIF (ah == 0ffh)
          ; fcos
            mov     dx,offset fcos_text
        .ELSE
            jmp     @F
        .ENDIF
        jmp     show_instruction

      @@:
        mov     al,ah
        shr     al,3
        and     al,0111b
        .IF (al == 0)
          ; fld real32
            mov     dx,offset fld_text
            mov     cx,3
        .ELSEIF (al == 2)
          ; fst real32
            mov     dx,offset fst_text
            mov     cx,3
        .ELSEIF (al == 3)
          ; fstp real32
            mov     dx,offset fstp_text
        .ELSEIF (al == 4)
          ; fldenv
            mov     dx,offset fldenv_text
            mov     cx,6
        .ELSEIF (al == 5)
          ; fldcw
            mov     dx,offset fldcw_text
            mov     cx,5
        .ELSEIF (al == 6)
          ; fstenv
            mov     dx,offset fstenv_text
            mov     cx,6
        .ELSEIF (al == 7)
          ; fstcw
            mov     dx,offset fstcw_text
            mov     cx,5
        .ELSE
          ; Invalid opcode
            jmp     unknown_instruction
        .ENDIF
    .ELSEIF (al == 0dah)
        mov     al,ah
        and     al,0111000b
        shr     al,3
        .IF (ah == 0e9h)
          ; fucompp
            mov     dx,offset fucompp_text
            mov     cx,7
        .ELSEIF (al == 0)
          ; fiadd int32
            mov     dx,offset fiadd_text
            mov     cx,5
        .ELSEIF (al == 1)
          ; fimul int32
            mov     dx,offset fimul_text
            mov     cx,5
        .ELSEIF (al == 2)
          ; ficom int32
            mov     dx,offset ficom_text
            mov     cx,5
        .ELSEIF (al == 3)
          ; ficomp int32
            mov     dx,offset ficomp_text
            mov     cx,6
        .ELSEIF (al == 4)
          ; fisub int32
            mov     dx,offset fisub_text
            mov     cx,5
        .ELSEIF (al == 5)
          ; fisubr int32
            mov     dx,offset fisubr_text
            mov     cx,7
        .ELSEIF (al == 6)
          ; fidiv int32
            mov     dx,offset fidiv_text
            mov     cx,5
        .ELSEIF (al == 7)
          ; fidivr int32
            mov     dx,offset fidivr_text
            mov     cx,6
        .ELSE
          ; Invalid opcode
            jmp     unknown_instruction
        .ENDIF
    .ELSEIF (al == 0dbh)
        mov     al,ah
        shr     al,3
        and     al,0111b
        .IF (ah == 0e2h)
          ; fclex
            mov     dx,offset fclex_text
            mov     cx,5
        .ELSEIF (ah == 0e3h)
          ; finit
            mov     dx,offset finit_text
            mov     cx,5
        .ELSEIF (al == 0)
          ; fild int32
            mov     dx,offset fild_text
        .ELSEIF (al == 2)
          ; fist int32
            mov     dx,offset fist_text
        .ELSEIF (al == 3)
          ; fistp int32
            mov     dx,offset fistp_text
            mov     cx,5
        .ELSEIF (al == 4)
          ; fld real80
            mov     dx,offset fld_text
            mov     cx,3
        .ELSEIF (al == 6)
          ; fstp real80
            mov     dx,offset fstp_text
        .ELSE
          ; Invalid opcode
            jmp     unknown_instruction
        .ENDIF
    .ELSEIF (al == 0dch)
        mov     al,ah
        and     al,not 0111b
        .IF (al == 0c0h)
          ; fadd st(i),st(0)
            mov     dx,offset fadd_text
        .ELSEIF (al == 0c8h)
          ; fmul st(i),st(0)
            mov     dx,offset fmul_text
        .ELSEIF (al == 0e0h)
          ; fsubr st(i),st(0)
            mov     dx,offset fsubr_text
            mov     cx,5
        .ELSEIF (al == 0e8h)
          ; fsub st(i),st(0)
            mov     dx,offset fsub_text
        .ELSEIF (al == 0f0h)
          ; fidivr st(i),st(0)
            mov     dx,offset fidivr_text
            mov     cx,6
        .ELSEIF (al == 0f8h)
          ; fidiv st(i),st(0)
            mov     dx,offset fidiv_text
            mov     cx,5
        .ELSE
            jmp     @F
        .ENDIF
        jmp     show_instruction

      @@:
        mov     al,ah
        shr     al,3
        and     al,0111b
        .IF (al == 0)
          ; fadd real64
            mov     dx,offset fadd_text
        .ELSEIF (al == 1)
          ; fmul real64
            mov     dx,offset fmul_text
        .ELSEIF (al == 2)
          ; fcom real64
            mov     dx,offset fcom_text
        .ELSEIF (al == 3)
          ; fcomp real64
            mov     dx,offset fcomp_text
            mov     cx,5
        .ELSEIF (al == 4)
          ; fsub real64
            mov     dx,offset fsub_text
        .ELSEIF (al == 5)
          ; fsubr real64
            mov     dx,offset fsubr_text
            mov     cx,5
        .ELSEIF (al == 6)
          ; fdiv real64
            mov     dx,offset fdiv_text
        .ELSEIF (al == 7)
          ; fdivr real64
            mov     dx,offset fdivr_text
            mov     cx,5
        .ELSE
          ; Invalid opcode
            jmp     unknown_instruction
        .ENDIF
    .ELSEIF (al == 0ddh)
        mov     al,ah
        and     al,not 0111b
        .IF (al == 0c0h)
          ; ffree st(i)
            mov     dx,offset ffree_text
        .ELSEIF (al == 0d0h)
          ; fst st(i)
            mov     dx,offset fst_text
            mov     cx,3
        .ELSEIF (al == 0d8h)
          ; fstp st(i)
            mov     dx,offset fstp_text
        .ELSEIF (al == 0e0h)
          ; fucom st(i)
            mov     dx,offset fucom_text
            mov     cx,5
        .ELSEIF (al == 0e8h)
          ; fucomp st(i)
            mov     dx,offset fucomp_text
            mov     cx,6
        .ELSE
            jmp     @F
        .ENDIF
        jmp     show_instruction

      @@:
        mov     al,ah
        shr     al,3
        and     al,0111b
        .IF (al == 0)
          ; fld real64
            mov     dx,offset fld_text
            mov     cx,3
        .ELSEIF (al == 2)
          ; fst real64
            mov     dx,offset fst_text
            mov     cx,3
        .ELSEIF (al == 3)
          ; fstp real64
            mov     dx,offset fstp_text
        .ELSEIF (al == 4)
          ; frstor
            mov     dx,offset frstor_text
            mov     cx,6
        .ELSEIF (al == 6)
          ; fsave
            mov     dx,offset fsave_text
            mov     cx,5
        .ELSEIF (al == 7)
          ; fstsw
            mov     dx,offset fstsw_text
            mov     cx,5
        .ELSE
          ; Invalid opcode
            jmp     unknown_instruction
        .ENDIF
    .ELSEIF (al == 0deh)
        .IF (ah == 0d9h)
          ; fcompp
            mov     dx,offset fcompp_text
            mov     cx,6
            jmp     show_instruction
        .ENDIF
        mov     al,ah
        and     al,not 0111b
        .IF (al == 0c0h)
          ; faddp st(i),st(0)
            mov     dx,offset fadd_text
        .ELSEIF (al == 0c8h)
          ; fmulp st(i),st(0)
            mov     dx,offset fmulp_text
            mov     cx,5
        .ELSEIF (al == 0e0h)
          ; fsubrp st(i),st(0)
            mov     dx,offset fsubrp_text
            mov     cx,6
        .ELSEIF (al == 0e8h)
          ; fsub st(i),st(0)
            mov     dx,offset fsub_text
        .ELSEIF (al == 0f0h)
          ; fdivrp st(i),st(0)
            mov     dx,offset fsubrp_text
            mov     cx,6
        .ELSEIF (al == 0f8h)
          ; fdivp st(i),st(0)
            mov     dx,offset fdivp_text
            mov     cx,5
        .ELSE
            jmp     @F
        .ENDIF
        jmp     show_instruction

      @@:
        mov     al,ah
        shr     al,3
        and     al,0111b
        .IF (al == 0)
          ; fiadd int16
            mov     dx,offset fiadd_text
            mov     cx,5
        .ELSEIF (al == 1)
          ; fimul int16
            mov     dx,offset fimul_text
            mov     cx,5
        .ELSEIF (al == 2)
          ; ficom int16
            mov     dx,offset ficom_text
            mov     cx,5
        .ELSEIF (al == 3)
          ; fisub int16
            mov     dx,offset fisub_text
            mov     cx,5
        .ELSEIF (al == 4)
          ; fisub int16
            mov     dx,offset fisub_text
            mov     cx,5
        .ELSEIF (al == 5)
          ; fisubr int16
            mov     dx,offset fisubr_text
            mov     cx,6
        .ELSEIF (al == 6)
          ; fidiv int16
            mov     dx,offset fidiv_text
            mov     cx,5
        .ELSEIF (al == 7)
          ; fidivr int16
            mov     dx,offset fidivr_text
            mov     cx,6
        .ELSE
          ; Invalid opcode
            jmp     unknown_instruction
        .ENDIF
    .ELSEIF (al == 0dfh)
        .IF (ah == 0e0h)
          ; fstsw ax
            mov     dx,offset fstsw_text
            mov     cx,5
            jmp     show_instruction
        .ENDIF
        mov     al,ah
        shr     al,3
        and     al,0111b
        .IF (al == 0)
          ; fild int16
            mov     dx,offset fild_text
        .ELSEIF (al == 2)
          ; fist int16
            mov     dx,offset fist_text
        .ELSEIF (al == 3)
          ; fistp int16
            mov     dx,offset fistp_text
            mov     cx,5
        .ELSEIF (al == 4)
          ; fbld bcd80
            mov     dx,offset fbld_text
        .ELSEIF (al == 5)
          ; fild int64
            mov     dx,offset fild_text
        .ELSEIF (al == 6)
          ; fbstp bcd80
            mov     dx,offset fbstp_text
            mov     cx,5
        .ELSEIF (al == 7)
          ; fistp int64
            mov     dx,offset fistp_text
            mov     cx,5
        .ELSE
          ; Invalid opcode
            jmp     unknown_instruction
        .ENDIF
    .ELSE
      ; It's an unknown instruction
        jmp     unknown_instruction
    .ENDIF
    jmp     show_instruction

  unknown_instruction:
    mov     dx,offset unknown_text
    mov     cx,3
    mov     bl,1
    call    display_instruction

  next_instruction:
    pop     cx
    pop     di
    add     di,(80 * 2)
    dec     cx
    or      cx,cx
    jz      done_disasm
    mov     edx,offset initialize_line
    jmp     disassemble_loop

  next_instruction_same_line:
    pop     cx
    pop     di
    mov     edx,offset initialize_line
    jmp     disassemble_loop

  done_disasm:
    pop     ES
    pop     DS
    popad
    leave
    ret


display_instruction:
    push    ax
    xor     ax,ax
    call    display_instruction_base
    pop     ax
    ret

display_instruction_shifted:
display_instruction_base:
; Upon entry:   ds:[si] - far pointer to instruction stream
;              cs:[edx] - far pointer to instruction name
;                    bx - length of instruction
;                    al - # of bytes to shift left for display of the text
;                    ah - # of bytes to shift right for display of the instruction bytes
  ; Display the instruction
    push    ax
    push    cx
    push    edx

    push    di                                                      ; Save current screen pointer
    mov     word ptr [bp-2],di
    mov     dword ptr [bp-6],0
    mov     byte ptr [bp-6],al
    mov     byte ptr [bp-6],ah

    add     di,18 * 2
    sub     di,word ptr [bp-4]
    call    write_screen_cs_edx_no_color

    pop     di                                                      ; Restore
  ; Display the instruction byte(s)
    add     di,5 * 2                                                ; Move over to display the instruction bytes
    add     di,word ptr [bp-6]
    push    di                                                      ; Save the location of the start of the bytes
    xor     cx,cx
    mov     cl,bl
    cmp     cl,6
    jle     @F
    mov     byte ptr es:[di+(10*2)],""                             ; The max to display is 6, but if it's more than 6 we only
    mov     byte ptr es:[di+(11*2)],""
    mov     cl,5                                                    ; display 5 with an indicator that the instruction is longer
  @@:
    push    si
    call    display_instruction_bytes
    mov     word ptr [bp-8],di                                      ; Store the ending location, in case they have additional bytes to print
    pop     si
    add     si,bx
    pop     di                                                      ; Restore the location of the start of the bytes
    add     di,21 * 2                                               ; Point to the location for the parameters
    sub     di,word ptr [bp-6]                                      ; Take back the bytes we shifted over for the instruction bytes

    pop     edx
    pop     cx
    pop     ax
    .IF (ax != 0)
        mov     di,word ptr [bp-2]                                  ; Something was shifted
    .ENDIF
    ret


display_instruction_bytes:
  @@:
    mov     dl,[si]
    pusha
    call    show_register_8_no_color
    popa
    inc     si
    add     di,4
    loop    @B
    ret


display_instruction_additional_bytes:
; cx - number of additional bytes to display
; ds:[si] - far ptr to the instruction bytes to print
    pusha

    pusha
    mov     ax,word ptr [bp-8]
    xor     dx,dx
    mov     bx,80*2
    div     bx
    mov     ax,dx
    shr     ax,1
    mov     word ptr [bp-10],ax
    popa

    sub     word ptr [bp-10],22
    neg     word ptr [bp-10]
    shl     cx,1
    .IF (word ptr [bp-10] <= cx)
      ; We cannot display all the bytes
        mov     cx,word ptr [bp-10]
        dec     cx                                                  ; Decrement for the 's
        shr     cx,1                                                ; Two bytes are displayed for every each character
        mov     di,word ptr [bp-2]
        mov     byte ptr es:[di+(15*2)],""                         ; The max to display is 6, but if it's more than 6 we only
        mov     byte ptr es:[di+(16*2)],""
    .ELSE
        shr     cx,1
    .ENDIF
    .IF (CX >= 1 && CX < 6)
        mov     di,word ptr [bp-8]
        call    display_instruction_bytes
    .ENDIF
    popa
    add     si,cx
    ret


write_screen_cs_edx_no_color:
  @@:
    mov     al,CS:[edx]
    stosb
    inc     di
    inc     edx
    loop    @B
    ret


display_register_name_accumulator:
    push    cx
    push    edx
    mov     cx,2
    .IF (CS:byte_word_size == 0)
      ; It's an 8-bit operand
        mov     dx,offset al_register
    .ELSE
        .IF (CS:op_size_override == 0)
          ; This is 16-bit
            mov     dx,offset ax_register
        .ELSE
          ; This is 32-bit
            mov     cx,3
            mov     dx,offset eax_register
        .ENDIF
    .ENDIF
    call    write_screen_cs_edx_no_color
    pop     edx
    pop     cx
    ret


display_register_name_sreg:
    push    cx
    push    edx
    xor     edx,edx
    mov     cx,2
    .IF (al == 000b)
        mov     dx,offset es_register
    .ELSEIF (al == 001b)
        mov     dx,offset cs_register
    .ELSEIF (al == 010b)
        mov     dx,offset ss_register
    .ELSEIF (al == 011b)
        mov     dx,offset ds_register
    .ELSEIF (al == 100b)
        mov     dx,offset fs_register
    .ELSEIF (al == 101b)
        mov     dx,offset gs_register
    .ELSE
        mov     dx,offset illegal_register
    .ENDIF
    call    write_screen_cs_edx_no_color
    pop     edx
    pop     cx
    ret


display_segment_override:
    push    ax
    push    cx
    push    edx
    xor     edx,edx
    mov     cx,2
    mov     al,CS:seg_override
    .IF (al == 1)
        mov     dx,offset cs_register
    .ELSEIF (al == 2)
        mov     dx,offset ds_register
    .ELSEIF (al == 3)
        mov     dx,offset es_register
    .ELSEIF (al == 4)
        mov     dx,offset ss_register
    .ELSEIF (al == 5)
        mov     dx,offset fs_register
    .ELSEIF (al == 6)
        mov     dx,offset gs_register
    .ELSE
        jmp     dso_done
    .ENDIF
    call    write_screen_cs_edx_no_color
    call    display_colon
  dso_done:
    pop     edx
    pop     cx
    pop     ax
    ret


display_register_name_32:
    push    cx
    push    edx
    xor     edx,edx
    mov     cx,3
    .IF (al == 000b)
        mov     dx,offset eax_register
    .ELSEIF (al == 001b)
        mov     dx,offset ecx_register
    .ELSEIF (al == 010b)
        mov     dx,offset edx_register
    .ELSEIF (al == 011b)
        mov     dx,offset ebx_register
    .ELSEIF (al == 100b)
        mov     dx,offset esp_register
    .ELSEIF (al == 101b)
        mov     dx,offset ebp_register
    .ELSEIF (al == 110b)
        mov     dx,offset esi_register
    .ELSE
        mov     dx,offset edi_register
    .ENDIF
    call    write_screen_cs_edx_no_color
    pop     edx
    pop     cx
    ret


display_register_name_special_reg:
    push    ax
    push    cx
    push    edx
    xor     edx,edx
    mov     cx,3
    mov     ah,CS:special_reg
    .IF (ah == 0)
      ; Control registers
        .IF (al == 000b)
            mov     dx,offset cr0_register
        .ELSEIF (al == 001b)
            mov     dx,offset cr1_register
        .ELSEIF (al == 010b)
            mov     dx,offset cr2_register
        .ELSEIF (al == 011b)
            mov     dx,offset cr3_register
        .ELSEIF (al == 100b)
            mov     dx,offset cr4_register
        .ELSEIF (al == 101b)
            mov     dx,offset cr5_register
        .ELSEIF (al == 110b)
            mov     dx,offset cr6_register
        .ELSE
            mov     dx,offset cr7_register
        .ENDIF
    .ELSEIF (ah == 1)
      ; Debug resgisters
        .IF (al == 000b)
            mov     dx,offset dr0_register
        .ELSEIF (al == 001b)
            mov     dx,offset dr1_register
        .ELSEIF (al == 010b)
            mov     dx,offset dr2_register
        .ELSEIF (al == 011b)
            mov     dx,offset dr3_register
        .ELSEIF (al == 100b)
            mov     dx,offset dr4_register
        .ELSEIF (al == 101b)
            mov     dx,offset dr5_register
        .ELSEIF (al == 110b)
            mov     dx,offset dr6_register
        .ELSE
            mov     dx,offset dr7_register
        .ENDIF
    .ELSE
      ; Test registers
        .IF (al == 000b)
            mov     dx,offset tr0_register
        .ELSEIF (al == 001b)
            mov     dx,offset tr1_register
        .ELSEIF (al == 010b)
            mov     dx,offset tr2_register
        .ELSEIF (al == 011b)
            mov     dx,offset tr3_register
        .ELSEIF (al == 100b)
            mov     dx,offset tr4_register
        .ELSEIF (al == 101b)
            mov     dx,offset tr5_register
        .ELSEIF (al == 110b)
            mov     dx,offset tr6_register
        .ELSE
            mov     dx,offset tr7_register
        .ENDIF
    .ENDIF
    call    write_screen_cs_edx_no_color
    pop     edx
    pop     cx
    pop     ax
    ret


display_register_name_16:
    push    cx
    push    edx
    xor     edx,edx
    mov     cx,2
    .IF (al == 000b)
        mov     dx,offset ax_register
    .ELSEIF (al == 001b)
        mov     dx,offset cx_register
    .ELSEIF (al == 010b)
        mov     dx,offset dx_register
    .ELSEIF (al == 011b)
        mov     dx,offset bx_register
    .ELSEIF (al == 100b)
        mov     dx,offset sp_register
    .ELSEIF (al == 101b)
        mov     dx,offset bp_register
    .ELSEIF (al == 110b)
        mov     dx,offset si_register
    .ELSE
        mov     dx,offset di_register
    .ENDIF
    call    write_screen_cs_edx_no_color
    pop     edx
    pop     cx
    ret


display_register_name_8:
    push    cx
    push    edx
    xor     edx,edx
    mov     cx,2
    .IF (al == 000b)
        mov     dx,offset al_register
    .ELSEIF (al == 001b)
        mov     dx,offset cl_register
    .ELSEIF (al == 010b)
        mov     dx,offset dl_register
    .ELSEIF (al == 011b)
        mov     dx,offset bl_register
    .ELSEIF (al == 100b)
        mov     dx,offset ah_register
    .ELSEIF (al == 101b)
        mov     dx,offset ch_register
    .ELSEIF (al == 110b)
        mov     dx,offset dh_register
    .ELSE
        mov     dx,offset bh_register
    .ENDIF
    call    write_screen_cs_edx_no_color
    pop     edx
    pop     cx
    ret


display_register_name_indirect_adr_size_override:
    push    cx
    push    edx
    .IF (CS:adr_size_override == 0)
      ; We're in 16-bit addressing mode
        xor     edx,edx
        mov     cx,5
        .IF (al == 000b)
            mov     dx,offset bx_si_register
        .ELSEIF (al == 001b)
            mov     dx,offset bx_di_register
        .ELSEIF (al == 010b)
            mov     dx,offset bp_si_register
        .ELSEIF (al == 011b)
            mov     dx,offset bp_di_register
        .ELSE
            mov     cx,2
            .IF (al == 100b)
                mov     dx,offset si_register
            .ELSEIF (al == 101b)
                mov     dx,offset di_register
            .ELSEIF (al == 110b)
                mov     dx,offset bp_register
            .ELSE
                mov     dx,offset bx_register
            .ENDIF
        .ENDIF
    .ELSE
      ; We're in 32-bit addressing mode
        xor     edx,edx
        mov     cx,3
        .IF (al == 000b)
            mov     dx,offset eax_register
        .ELSEIF (al == 001b)
            mov     dx,offset ecx_register
        .ELSEIF (al == 010b)
            mov     dx,offset edx_register
        .ELSEIF (al == 011b)
            mov     dx,offset ebx_register
;        .ELSEIF (al == 100b)
;            SIB byte would be used, so this combination would never be here
        .ELSEIF (al == 101b)
            mov     dx,offset ebp_register
        .ELSEIF (al == 110b)
            mov     dx,offset esi_register
        .ELSE
            mov     dx,offset edi_register
        .ENDIF
    .ENDIF
    call    write_screen_cs_edx_no_color
    pop     edx
    pop     cx
    ret


display_register_name_op_size_override:
    .IF (CS:byte_word_size == 0 && CS:movxx == 0)
      ; It's an 8-bit operand
        call    display_register_name_8
    .ELSE
        .IF (CS:op_size_override == 0)
          ; This is 16-bit
            call    display_register_name_16
        .ELSE
          ; This is 32-bit
            call    display_register_name_32
        .ENDIF
    .ENDIF
    ret


display_register_name_byte_word_size_override:
    .IF (CS:byte_word_size == 0)
      ; It's an 8-bit operand
        call    display_register_name_8
    .ELSE
      ; This is 16-bit
        call    display_register_name_16
    .ENDIF
    ret


display_comma:
    push    ax
    mov     al,","
    stosb
    inc     di
    pop     ax
    ret


display_one:
    push    ax
    mov     al,"1"
    stosb
    inc     di
    pop     ax
    ret


display_open_bracket:
    push    ax
    mov     al,"["
    stosb
    inc     di
    pop     ax
    ret


display_close_bracket:
    push    ax
    mov     al,"]"
    stosb
    inc     di
    pop     ax
    ret


display_open_parenthesis:
    push    ax
    mov     al,"("
    stosb
    inc     di
    pop     ax
    ret


display_close_parenthesis:
    push    ax
    mov     al,")"
    stosb
    inc     di
    pop     ax
    ret


display_plus_sign:
    push    ax
    mov     al,"+"
    stosb
    inc     di
    pop     ax
    ret


display_colon:
    push    ax
    mov     al,":"
    stosb
    inc     di
    pop     ax
    ret


display_scale_2:
    push    ax
    mov     al,"*"
    stosb
    inc     di
    mov     al,"2"
    stosb
    inc     di
    pop     ax
    ret


display_scale_4:
    push    ax
    mov     al,"*"
    stosb
    inc     di
    mov     al,"4"
    stosb
    inc     di
    pop     ax
    ret


display_scale_8:
    push    ax
    mov     al,"*"
    stosb
    inc     di
    mov     al,"8"
    stosb
    inc     di
    pop     ax
    ret


show_new_cs_ip:
; Values for CS:[ip] are actually DS & si, distance to jump is dx
    push    dx                                                      ; Save current offset
    push    ds
    pop     dx
    call    display_open_parenthesis
    call    show_register_16_no_color
    add     di,4*2
    call    display_colon
    mov     dx,si
    pop     ax                                                      ; Restore and add to current value
    add     dx,ax
    call    show_register_16_no_color
    add     di,4*2
    call    display_close_parenthesis
    ret


show_new_cs_ip_far:
; Values for CS:[ip] are actually DS & si, distance to jump is edx
    call    display_open_parenthesis
    xor     eax,eax
    mov     ax,ds
    shl     eax,16
    and     esi,0ffffh
    add     eax,esi                                                 ; Add current IP value
    add     edx,eax                                                 ; Add to the distance to move
    call    show_register_32_16_16_no_color
    add     di,9*2
    call    display_close_parenthesis
    ret


display_instruction_with_mod_rm:
  ; Show how many bytes there are in the override prefixes
    call    adjust_for_overrides

  ; Get the mod,reg,r/m byte
    mov     al,byte ptr [si+bx-1]
    mov     ah,al
    shr     ah,6
    .IF (ah == 11b)
        ; It's a two-register instruction
        call    display_instruction
        call    display_segment_override
        mov     ah,al
        and     al,0111b
        call    display_register_name_op_size_override
    .ELSE
        mov     ah,al
        and     ah,0111b
        .IF (ah == 100b && CS:adr_size_override != 0)
            mov     CS:mod_reg_rm_byte,al
            inc     bx                                              ; We have to use the SIB byte
            mov     al,[si+bx-1]
            mov     CS:sib_byte,al
            mov     ah,CS:mod_reg_rm_byte
            shr     ah,6
            .IF (ah == 01b)
                inc     bx
                call    display_instruction
                call    display_segment_override
                call    part1_1_disp8
            .ELSEIF (ah == 10b)
                add     bx,4
                call    display_instruction
                call    display_segment_override
                call    part1_1_disp32
            .ELSE
                call    display_instruction
                call    display_segment_override
                call    part1_1
            .ENDIF
        .ELSEIF (CS:adr_size_override != 0)
          ; 32-bit mode
            mov     ah,al
            shr     ah,6
            .IF (ah == 10b)
              ; It's an indirect memory operand with a 32-bit displacement
                add     bx,4
                call    display_instruction
                call    display_segment_override
                call    part1_2
            .ELSEIF (ah == 01b)
              ; It's an indirect memory operand with an 8-bit displacement
                inc     bx
                call    display_instruction
                call    display_segment_override
                call    part1_3
            .ELSE
              ; It is 00b, which means it's either direct memory operand or a based, indexed or based & indexed operand
                mov     ah,al
                and     ah,0111b
                .IF (ah == 101b)
                  ; It's a 32-bit direct memory operand
                    add     bx,4
                    call    display_instruction
                    call    display_segment_override
                    call    part1_4
                .ELSE
                    call    display_instruction
                    call    display_segment_override
                    call    part1_5
                .ENDIF
            .ENDIF
        .ELSE
          ; 16-bit mode
          ; Just the modr/m byte
            mov     ah,al
            shr     ah,6
            .IF (ah == 10b)
              ; It's an indirect memory operand with a 16-bit displacement
                add     bx,2
                call    display_instruction
                call    display_segment_override
                call    part1_6
            .ELSEIF (ah == 01b)
              ; It's an indirect memory operand with an 8-bit displacement
                inc     bx
                call    display_instruction
                call    display_segment_override
                call    part1_7
            .ELSE
              ; It is 00b, which means it's either direct memory operand or a based, indexed or based & indexed operand
                mov     ah,al
                and     ah,0111b
                .IF (ah == 110b)
                  ; It's a direct memory operand
                    add     bx,2
                    call    display_instruction
                    call    display_segment_override
                    call    part1_8
                .ELSE
                  ; It's a based, indexed or based & indexed operand
                    call    display_instruction
                    call    display_segment_override
                    call    part1_9
                .ENDIF
            .ENDIF
        .ENDIF
    .ENDIF
    ret


display_instruction_with_mod_reg_rm_movxx:
    mov     al,byte ptr [si+2]
    shr     al,6
    .IF (al == 11b)
      ; It's register to register
        sub     si,CS:op_size_override
        add     bx,CS:op_size_override
        call    display_instruction
        call    display_segment_override
        mov     al,byte ptr [si-1]
        mov     ah,al
        shr     al,3
        and     al,0111b
        .IF (CS:op_size_override != 0)
            call    display_register_name_32
        .ELSE
            call    display_register_name_16
        .ENDIF
        call    display_comma
        mov     al,ah
        and     al,0111b
        call    display_register_name_byte_word_size_override
    .ELSE
        mov     CS:reverse_regs,1
        mov     CS:movxx,1
        call    display_instruction_with_mod_reg_rm
        mov     CS:movxx,0
    .ENDIF
    ret


display_instruction_with_mod_reg_rm:
  ; Show how many bytes there are in the override prefixes
    call    adjust_for_overrides

  ; Get the mod,reg,r/m byte
    mov     al,byte ptr [si+bx-1]
    mov     ah,al
    shr     ah,6
    .IF (ah == 11b)
        ; It's a two-register instruction
        call    display_instruction
        .IF (CS:reverse_regs == 0)
            mov     ah,al
            and     al,0111b
            call    display_register_name_op_size_override
            call    display_comma
            mov     al,ah
            shr     al,3
            and     al,0111b
            .IF (CS:sreg_override == 1)
                call    display_register_name_sreg
            .ELSE
                call    display_register_name_op_size_override
            .ENDIF
        .ELSE
            mov     ah,al
            shr     al,3
            and     al,0111b
            .IF (CS:sreg_override == 1)
                call    display_register_name_sreg
            .ELSE
                call    display_register_name_op_size_override
            .ENDIF
            call    display_comma
            mov     al,ah
            and     al,0111b
            call    display_register_name_op_size_override
        .ENDIF
    .ELSE
        mov     ah,al
        and     ah,0111b
        .IF (ah == 100b && CS:adr_size_override != 0)
          ; We have to use the SIB byte
            mov     CS:mod_reg_rm_byte,al
            inc     bx
            mov     al,[si+bx-1]
            mov     CS:sib_byte,al
            mov     ah,CS:mod_reg_rm_byte
            shr     ah,6
            .IF (CS:reverse_regs == 0)
                .IF (ah == 01b)
                    inc     bx
                    call    display_instruction
                    call    display_segment_override
                    call    part1_1_disp8
                    call    display_comma
                    call    part2_1
                .ELSEIF (ah == 10b)
                    add     bx,4
                    call    display_instruction
                    call    display_segment_override
                    call    part1_1_disp32
                    call    display_comma
                    call    part2_1
                .ELSE
                    call    display_instruction
                    call    display_segment_override
                    call    part1_1
                    call    display_comma
                    call    part2_1
                .ENDIF
            .ELSE
                .IF (ah == 01b)
                    inc     bx
                    call    display_instruction
                    call    part2_1
                    call    display_comma
                    call    display_segment_override
                    call    part1_1_disp8
                .ELSEIF (ah == 10b)
                    add     bx,4
                    call    display_instruction
                    call    part2_1
                    call    display_comma
                    call    display_segment_override
                    call    part1_1_disp32
                .ELSE
                    call    display_instruction
                    call    part2_1
                    call    display_comma
                    call    display_segment_override
                    call    part1_1
                .ENDIF
            .ENDIF
        .ELSEIF (CS:adr_size_override != 0)
          ; 32-bit mode
            mov     ah,al
            shr     ah,6
            .IF (ah == 10b)
              ; It's an indirect memory operand with a 32-bit displacement
                add     bx,4
                call    display_instruction
                mov     ah,al
                .IF (CS:reverse_regs == 0)
                    call    display_segment_override
                    call    part1_2
                    call    display_comma
                    mov     al,ah
                    call    part2_2
                .ELSE
                    call    part2_2
                    call    display_comma
                    call    display_segment_override
                    mov     al,ah
                    call    part1_2
                .ENDIF
            .ELSEIF (ah == 01b)
              ; It's an indirect memory operand with an 8-bit displacement
                inc     bx
                call    display_instruction
                mov     ah,al
                .IF (CS:reverse_regs == 0)
                    call    display_segment_override
                    call    part1_3
                    call    display_comma
                    mov     al,ah
                    call    part2_3
                .ELSE
                    call    part2_3
                    call    display_comma
                    call    display_segment_override
                    mov     al,ah
                    call    part1_3
                .ENDIF
            .ELSE
              ; It is 00b, which means it's either direct memory operand or a based, indexed or based & indexed operand
                mov     ah,al
                and     ah,0111b
                .IF (ah == 101b)
                  ; It's a 32-bit direct memory operand
                    add     bx,4
                    call    display_instruction
                    mov     ah,al
                    .IF (CS:reverse_regs == 0)
                        call    display_segment_override
                        call    part1_4
                        call    display_comma
                        mov     al,ah
                        call    part2_4
                    .ELSE
                        call    part2_4
                        call    display_comma
                        call    display_segment_override
                        mov     al,ah
                        call    part1_4
                    .ENDIF
                .ELSE
                    call    display_instruction
                    mov     ah,al
                    .IF (CS:reverse_regs == 0)
                        call    display_segment_override
                        call    part1_5
                        call    display_comma
                        mov     al,ah
                        call    part2_5
                    .ELSE
                        call    part2_5
                        call    display_comma
                        call    display_segment_override
                        mov     al,ah
                        call    part1_5
                    .ENDIF
                .ENDIF
            .ENDIF
        .ELSE
          ; 16-bit mode
          ; Just the modr/m byte
            mov     ah,al
            shr     ah,6
            .IF (ah == 10b)
              ; It's an indirect memory operand with a 16-bit displacement
                add     bx,2
                call    display_instruction
                mov     ah,al
                .IF (CS:reverse_regs == 0)
                    call    display_segment_override
                    call    part1_6
                    call    display_comma
                    mov     al,ah
                    call    part2_6
                .ELSE
                    call    part2_6
                    call    display_comma
                    call    display_segment_override
                    mov     al,ah
                    call    part1_6
                .ENDIF
            .ELSEIF (ah == 01b)
              ; It's an indirect memory operand with an 8-bit displacement
                inc     bx
                call    display_instruction
                mov     ah,al
                .IF (CS:reverse_regs == 0)
                    call    display_segment_override
                    call    part1_7
                    call    display_comma
                    mov     al,ah
                    call    part2_7
                .ELSE
                    call    part2_7
                    call    display_comma
                    call    display_segment_override
                    mov     al,ah
                    call    part1_7
                .ENDIF
            .ELSE
              ; It is 00b, which means it's either direct memory operand or a based, indexed or based & indexed operand
                mov     ah,al
                and     ah,0111b
                .IF (ah == 110b)
                  ; It's a direct memory operand
                    add     bx,2
                    call    display_instruction
                    mov     ah,al
                    .IF (CS:reverse_regs == 0)
                        call    display_segment_override
                        call    part1_8
                        call    display_comma
                        mov     al,ah
                        call    part2_8
                    .ELSE
                        call    part2_8
                        call    display_comma
                        call    display_segment_override
                        mov     al,ah
                        call    part1_8
                    .ENDIF
                .ELSE
                  ; It's a based, indexed or based & indexed operand
                    call    display_instruction
                    mov     ah,al
                    .IF (CS:reverse_regs == 0)
                        call    display_segment_override
                        call    part1_9
                        call    display_comma
                        mov     al,ah
                        call    part2_9
                    .ELSE
                        call    part2_9
                        call    display_comma
                        call    display_segment_override
                        mov     al,ah
                        call    part1_9
                    .ENDIF
                .ENDIF
            .ENDIF
        .ENDIF
    .ENDIF
    ret


adjust_for_overrides:
    .IF (CS:seg_override != 0)
        dec     si
        inc     bx
    .ENDIF

    sub     si,CS:adr_size_override
    add     bx,CS:adr_size_override

    sub     si,CS:op_size_override
    add     bx,CS:op_size_override
    ret


part1_1:
    call    part1_1_base
    call    display_close_bracket
    ret

part1_1_disp8:
    call    part1_1_base
    mov     dl,byte ptr [si-1]
    call    show_register_8_no_color_signed
    add     di,3*2
    call    display_close_bracket
    ret

part1_1_disp32:
    call    part1_1_base
    mov     edx,dword ptr [si-4]
    call    show_register_32_no_color_signed
    add     di,9*2
    call    display_close_bracket
    ret

part1_1_base:
    mov     al,CS:sib_byte
    mov     ah,al
    shr     ah,6
    .IF (ah == 00b)
      ; Scale *1
        mov     ah,al
        and     ah,111b
        .IF (al != 100b)
          ; Scale register is used
            call    display_open_bracket
            shr     al,3
            and     al,0111b
            call    display_register_name_32
            call    display_plus_sign
            jmp     @F
        .ELSE
          ; No scale, just the base
            call    display_open_bracket
        @@:
            mov     al,CS:sib_byte
            and     al,111b
            call    display_register_name_32
        .ENDIF
    .ELSE
      ; Some scale factor
        mov     ah,al
        and     ah,111b
        .IF (al != 100b)
          ; Scale register is used
            call    display_open_bracket
            shr     al,3
            and     al,0111b
            call    display_register_name_32
            mov     ah,CS:sib_byte
            shr     ah,6
            .IF (ah == 01b)
              ; Scale *2
                call    display_scale_2
            .ELSEIF (ah == 10b)
              ; Scale *4
                call    display_scale_4
            .ELSE
              ; Scale *8
                call    display_scale_8
            .ENDIF
            call    display_plus_sign
            jmp     @F
        .ELSE
          ; No scale, just the base
            call    display_open_bracket
        @@:
            mov     al,CS:sib_byte
            and     al,111b
            call    display_register_name_32
        .ENDIF
    .ENDIF
    ret

part2_1:
    mov     al,CS:mod_reg_rm_byte
    shr     al,3
    and     al,111b
    .IF (CS:sreg_override == 1)
        call    display_register_name_sreg
    .ELSE
        call    display_register_name_op_size_override
    .ENDIF
    ret

part1_2:
    and     al,0111b
    call    display_open_bracket
    call    display_register_name_indirect_adr_size_override
    mov     edx,dword ptr [si-4]
    call    show_register_32_no_color_signed
    add     di,9*2
    call    display_close_bracket
    ret

part2_2:
    shr     al,3
    and     al,0111b
    .IF (CS:sreg_override == 1)
        call    display_register_name_sreg
    .ELSE
        call    display_register_name_op_size_override
    .ENDIF
    ret

part1_3:
    and     al,0111b
    call    display_open_bracket
    call    display_register_name_indirect_adr_size_override
    mov     dl,byte ptr [si-1]
    call    show_register_8_no_color_signed
    add     di,3*2
    call    display_close_bracket
    ret

part2_3:
    shr     al,3
    and     al,0111b
    .IF (CS:sreg_override == 1)
        call    display_register_name_sreg
    .ELSE
        call    display_register_name_op_size_override
    .ENDIF
    ret

part1_4:
    and     al,0111b
    call    display_open_bracket
    mov     edx,dword ptr [si-4]
    call    show_register_32_no_color
    add     di,8*2
    call    display_close_bracket
    ret

part2_4:
    shr     al,3
    and     al,0111b
    .IF (CS:sreg_override == 1)
        call    display_register_name_sreg
    .ELSE
        call    display_register_name_op_size_override
    .ENDIF
    ret

part1_5:
    and     al,0111b
    call    display_open_bracket
    call    display_register_name_indirect_adr_size_override
    call    display_close_bracket
    ret

part2_5:
    shr     al,3
    and     al,0111b
    .IF (CS:sreg_override == 1)
        call    display_register_name_sreg
    .ELSE
        call    display_register_name_op_size_override
    .ENDIF
    ret

part1_6:
    and     al,0111b
    call    display_open_bracket
    call    display_register_name_indirect_adr_size_override
    mov     dx,word ptr [si-2]
    call    show_register_16_no_color_signed
    add     di,5*2
    call    display_close_bracket
    ret

part2_6:
    shr     al,3
    and     al,0111b
    .IF (CS:sreg_override == 1)
        call    display_register_name_sreg
    .ELSE
        call    display_register_name_op_size_override
    .ENDIF
    ret

part1_7:
    and     al,0111b
    call    display_open_bracket
    call    display_register_name_indirect_adr_size_override
    mov     dl,byte ptr [si-1]
    call    show_register_8_no_color_signed
    add     di,3*2
    call    display_close_bracket
    ret

part2_7:
    shr     al,3
    and     al,0111b
    .IF (CS:sreg_override == 1)
        call    display_register_name_sreg
    .ELSE
        call    display_register_name_op_size_override
    .ENDIF
    ret

part1_8:
    and     al,0111b
    call    display_open_bracket
    mov     dx,word ptr [si-2]
    call    show_register_16_no_color
    add     di,4*2
    call    display_close_bracket
    ret

part2_8:
    shr     al,3
    and     al,0111b
    .IF (CS:sreg_override == 1)
        call    display_register_name_sreg
    .ELSE
        call    display_register_name_op_size_override
    .ENDIF
    ret

part1_9:
    and     al,0111b
    call    display_open_bracket
    call    display_register_name_indirect_adr_size_override
    call    display_close_bracket
    ret

part2_9:
    shr     al,3
    and     al,0111b
    .IF (CS:sreg_override == 1)
        call    display_register_name_sreg
    .ELSE
        call    display_register_name_op_size_override
    .ENDIF
    ret