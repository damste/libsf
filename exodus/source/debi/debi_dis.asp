; debi_dis.asp
;
; Debi Debugger disassembly algorithms
;



debi_generate_disassembly   PROC
; Upon entry:  ds:[esi] - far ptr to instruction stream
;              es:[edi] - far ptr to store the disassembled instruction text (no color information)
;                    fs - _sDATA segment
;
; Upon exit:   esi - far ptr to start of next instruction
;              ecx - # of bytes generated in the es:[edi] variable
;
    enter   20,0
    push    eax
    push    ebx
    push    edx
    push    edi
    push    ds
    push    es

  ; Create a local stack frame (of sorts) for temporary variables
  ;
  ; ss:[ebp-_INS_DISPLAYED] - Holds start of the most recent instruction that has been displayed
  ; ss:[ebp-_SHIFT_LEFT] - Holds # of bytes to shift left for display of instruction text "mov"
  ; ss:[ebp-_SHIFT_RIGHT] - Holds # of bytes to shift right for display of instruction bytes "6766"
  ; ss:[ebp-_INS_BYTES] - Holds the end of the most recent instruction bytes that were displayed
  ; ss:[ebp-_TEMP_DATA] - Used in temporary calculations for displaying additional instruction bytes (usually immed data)
  ;


  disassemble_loop:
    mov     fs:seg_override,0                                       ; Default to no segment override
    mov     fs:op_size_override,1                                   ; Default to operand size override
    mov     fs:adr_size_override,1                                  ; Default to address size override
    mov     fs:sib_byte,0                                           ; Default to no SIB byte
    mov     fs:byte_word_size,1                                     ; Default to a 16-bit instruction size
    mov     fs:reverse_regs,0                                       ; Default to *NOT* reverse the regs
    mov     fs:sign_extend,0                                        ; Default to no sign extension
    mov     fs:movxx,0                                              ; Default to not the movxx instruction
    mov     fs:sreg_override,0                                      ; Default to no data segment override

  next_byte:
    xor     ebx,ebx
    mov     eax,dword ptr ds:[esi]
    xor     edx,edx
    .IF (al == 066h)
      ; 32/16-bit register override
        dec     fs:op_size_override
        inc     si
        jmp     next_byte
    .ENDIF
    .IF (al == 067h)
      ; 32/16-bit memory override
        dec     fs:adr_size_override
        inc     si
        jmp     next_byte
    .ENDIF
    .IF (al == 02eh)
      ; CS segment override
        mov     fs:seg_override,1
        inc     si
        jmp     next_byte
    .ENDIF
    .IF (al == 03eh)
      ; DS segment override
        mov     fs:seg_override,2
        inc     si
        jmp     next_byte
    .ENDIF
    .IF (al == 026h)
      ; ES segment override
        mov     fs:seg_override,3
        inc     si
        jmp     next_byte
    .ENDIF
    .IF (al == 036h)
      ; SS segment override
        mov     fs:seg_override,4
        inc     si
        jmp     next_byte
    .ENDIF
    .IF (al == 064h)
      ; FS segment override
        mov     fs:seg_override,5
        inc     si
        jmp     next_byte
    .ENDIF
    .IF (al == 065h)
      ; GS segment override
        mov     fs:seg_override,6
        inc     si
        jmp     next_byte
    .ENDIF
    .IF (al != 0fh)
        jmp     one_byte_instructions
    .ENDIF

;; Here we check all first-byte-0fh instructions
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
            cmp     dl,11001000b
            jz      @F
            jmp     try_again1
          @@:
              ; bswap
                mov     edx,offset bswap_text
                mov     ecx,5
                cmp     fs:op_size_override,0
                jz      @F
                dec     esi
                mov     ebx,3
              @@:
                call    display_instruction
                mov     al,ah
                and     al,111b
                cmp     fs:op_size_override,0
                jz      @F
                call    display_register_name_32
                jmp     done_disasm
              @@:
                call    display_register_name_16
                jmp     done_disasm

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
                mov     edx,offset pop_text
                mov     ecx,3
                call    display_instruction
                call    display_register_name_sreg
                jmp     done_disasm

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
                mov     edx,offset push_text
                mov     ecx,4
                call    display_instruction
                call    display_register_name_sreg
                jmp     done_disasm

          try_again3:
            mov     dl,ah
            and     dl,11000111b
            cmp     dl,10000011b
            jz      @F
            jmp     try_again4
          @@:
              ; bt?
                mov     ebx,3
                mov     ecx,3                                       ; Default to an instruction length of three
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
                call    display_instruction_with_mod_reg_rm
                jmp     done_disasm

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
                mov     fs:byte_word_size,dl
                mov     edx,offset cmpxchg_text
                mov     ebx,3
                mov     ecx,7
                call    display_instruction_with_mod_reg_rm
                jmp     done_disasm

          try_again5:
            mov     dl,ah
            and     dl,11110000b
            cmp     dl,10000000b
            jz      @F
            jmp     try_again6
          @@:
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
                ; It's jg/jnle (signed)                                 ; It's the only combination left
                mov     edx,offset jg_text
                mov     ecx,2
              try_again5_success:
                call    display_instruction
                mov     dx,word ptr ds:[esi-2]
                call    show_register_16_signed
                add     edi,6
                call    show_new_cs_ip
                jmp     done_disasm

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
                inc     ebx
                mov     edx,offset mov_text
                mov     ecx,3
                cmp     ah,0
                jz      @F
                ; Direction is 1
                mov     fs:special_reg,0
              try_again7_direction_1:
                call    display_instruction
                mov     al,byte ptr ds:[esi-1]
                and     al,111b
                call    display_register_name_special_reg
                call    display_comma
                mov     al,byte ptr ds:[esi-1]
                shr     al,3
                and     al,111b
                call    display_register_name_32
                jmp     done_disasm
              @@:
                ; Direction is 0
                mov     fs:special_reg,0
              try_again7_direction_0:
                call    display_instruction
                mov     al,byte ptr ds:[esi-1]
                and     al,111b
                call    display_register_name_32
                call    display_comma
                mov     al,byte ptr ds:[esi-1]
                shr     al,3
                and     al,111b
                call    display_register_name_special_reg
                jmp     done_disasm

          try_again7:
            cmp     dl,00100001b
            jz      @F
            jmp     try_again8
            ; It's a "mov dreg,reg32; reg32,dreg"
          @@:
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
          @@:
          try_again8:
            cmp     dl,00100100b
            jz      @F
            jmp     try_again9
          @@:
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
                mov     fs:byte_word_size,dh
                mov     edx,offset movsx_text
                mov     ecx,5
                inc     ebx
                call    display_instruction_with_mod_reg_rm_movxx
                jmp     done_disasm
          try_again10:
            cmp     dl,10110110b
            jz      @F
            jmp     try_again11
          @@:
            ; It's movzx
                mov     fs:byte_word_size,dh
                mov     edx,offset movzx_text
                mov     ecx,5
                inc     ebx
                call    display_instruction_with_mod_reg_rm_movxx
                jmp     done_disasm

          try_again11:
            mov     dl,ah
            and     dl,11110000b
            cmp     dl,10010000b
            jz      @F
            jmp     try_again12
          @@:
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
                call    display_instruction_with_mod_rm
                jmp     done_disasm

          try_again12:
            and     dl,11111110b
            cmp     dl,11000000b
            jz      @F
            jmp     try_again13
          @@:
            ; It's xadd
                mov     ebx,3
                mov     dl,al
                and     dl,1b
                mov     fs:byte_word_size,dl
                mov     edx,offset xadd_text
                mov     ecx,4
                call    display_instruction_with_mod_reg_rm
                jmp     done_disasm

          try_again13:
            mov     ebx,3                                          ; This next batch of instructions are all at least 3 bytes
            cmp     ah,00000000b
            jz      @F
            jmp     try_again14
          @@:
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
                call    display_instruction_with_mod_rm
                jmp     done_disasm

              try_again13_sub6:
                ; Don't know what it is, continue looking
                jmp     try_again14

          try_again14:
            cmp     ah,00000001b
            jz      @F
            jmp     try_again15
          @@:
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
;                    jmp     try_again14_success
              try_again14_success:
                call    display_instruction_with_mod_rm
                jmp     done_disasm

              try_again14_sub7:
                ; Who knows what is is, continue looking
                jmp     try_again15

          try_again15:
            cmp     ah,00000010b
            jz      @F
            jmp     try_again16
          @@:
            ; It's lar
                inc     ebx
                mov     edx,offset lar_text
                mov     ecx,3
                call    display_instruction_with_mod_reg_rm
                jmp     done_disasm

          try_again16:
            cmp     ah,00000011b
            jz      @F
            jmp     try_again17
          @@:
            ; It's lsl
                inc     ebx
                mov     edx,offset lsl_text
                mov     ecx,3
                call    display_instruction_with_mod_reg_rm
                jmp     done_disasm

          try_again17:
            mov     ecx,4
            cmp     ah,10100100b
            jz      @F
            jmp     try_again18
          @@:
            ; It's shld by immed
                mov     edx,offset shld_text
                jmp     show_instruction

          try_again18:
            cmp     ah,10100101b
            jz      @F
            jmp     try_again19
          @@:
            ; It's shld by cl
                mov     edx,offset shld_text
                jmp     show_instruction

          try_again19:
            cmp     ah,10101100b
            jz      @F
            jmp     try_again20
          @@:
            ; It's shrd by immed
                mov     edx,offset shrd_text
                jmp     show_instruction

          try_again20:
            cmp     ah,10101101b
            jz      @F
            jmp     try_again21
          @@:
            ; It's shrd by cl
                mov     edx,offset shrd_text
                jmp     show_instruction

          try_again21:
            cmp     ah,10101111b
            jz      @F
            jmp     try_again22
          @@:
            ; It's imul
                inc     ebx
                mov     edx,offset imul_text
                call    display_instruction_with_mod_reg_rm
                jmp     done_disasm

          try_again22:
            mov     ecx,3
            cmp     ah,10110010b
            jz      @F
            jmp     try_again23
          @@:
            ; lss
                mov     fs:reverse_regs,1
                mov     edx,offset lss_text
                mov     ebx,3
                call    display_instruction_with_mod_reg_rm
                jmp     done_disasm

          try_again23:
            cmp     ah,10110100b
            jz      @F
            jmp     try_again24
          @@:
            ; lfs
                mov     fs:reverse_regs,1
                mov     edx,offset lfs_text
                mov     ebx,3
                call    display_instruction_with_mod_reg_rm
                jmp     done_disasm

          try_again24:
            cmp     ah,10110101b
            jz      @F
            jmp     try_again25
          @@:
            ; lgs
                mov     fs:reverse_regs,1
                mov     edx,offset lgs_text
                mov     ebx,3
                call    display_instruction_with_mod_reg_rm
                jmp     done_disasm

          try_again25:
            cmp     ah,10111010b
            jz      @F
            jmp     try_again26
          @@:
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

          try_again26:
            cmp     ah,10111100b
            jz      @F
            jmp     try_again27
          @@:
            ; It's bsf
                mov     edx,offset bsf_text
                jmp     show_instruction

          try_again27:
            cmp     ah,10111101b
            jz      @F
            jmp     try_again28
          @@:
            ; It's bsr
                mov     edx,offset bsr_text
                jmp     show_instruction

          try_again28:
            jmp     unknown_instruction
        .ENDIF
        jmp     show_instruction

  one_byte_instructions:
    mov     ecx,3                                                   ; Assume 3-byte widths
    mov     ebx,1                                                   ; The next group are all one-byte instructions
    .IF (al == 00110111b)
      ; aaa
        mov     edx,offset aaa_text
    .ELSEIF (al ==  00111111b)
      ; aas
        mov     edx,offset aas_text
    .ELSEIF (al ==  10011000b)
      ; cbw
        cmp     fs:op_size_override,0
        jz      @F
            mov     edx,offset cwde_text
            mov     ecx,4
            dec     esi                                             ; This just become a two-byte instruction, backup one byte
            inc     bl
            jmp     show_instruction
        @@:
            mov     edx,offset cbw_text
    .ELSEIF (al ==  10011001b)
      ; cwd
        cmp     fs:op_size_override,0
        jz      @F
            mov     edx,offset cdq_text
            dec     esi                                             ; This just become a two-byte instruction, backup one byte
            inc     bl
            jmp     show_instruction
        @@:
            mov     edx,offset cwd_text
    .ELSEIF (al ==  11111000b)
      ; clc
        mov     edx,offset clc_text
        mov     ecx,3
    .ELSEIF (al ==  11111100b)
      ; cld
        mov     edx,offset cld_text
        mov     ecx,3
    .ELSEIF (al ==  11111010b)
      ; cli
        mov     edx,offset cli_text
        mov     ecx,3
    .ELSEIF (al ==  11110101b)
      ; cmc
        mov     edx,offset cmc_text
        mov     ecx,3
    .ELSEIF (al ==  00100111b)
      ; daa
        mov     edx,offset daa_text
        mov     ecx,3
    .ELSEIF (al ==  00101111b)
      ; das
        mov     edx,offset das_text
        mov     ecx,3
    .ELSEIF (al ==  11110100b)
      ; hlt
        mov     edx,offset hlt_text
        mov     ecx,3
    .ELSEIF (al ==  11001110b)
      ; into
        mov     edx,offset into_text
        mov     ecx,4
    .ELSEIF (al ==  11001111b)
      ; iret
        cmp     fs:op_size_override,0
        jz      @F
            mov     edx,offset iretd_text
            mov     ecx,5
            dec     esi                                             ; This just become a two-byte instruction, backup one byte
            mov     ebx,2
            jmp     show_instruction
        @@:
            mov     edx,offset iret_text
            mov     ecx,4
    .ELSEIF (al ==  10011111b)
      ; lahf
        mov     edx,offset lahf_text
        mov     ecx,4
    .ELSEIF (al ==  11001001b)
      ; leave
        mov     edx,offset leave_text
        mov     ecx,5
    .ELSEIF (al ==  11110000b)
      ; lock
        mov     edx,offset lock_text
        mov     ecx,4
    .ELSEIF (al == 0f3h)
      ; rep/repe prefix
        mov     edx,offset rep_text
        mov     ecx,3
        mov     eax,2
        call    display_instruction_shifted
        jmp     done_disasm
    .ELSEIF (al == 0f2h)
      ; repne prefix
        mov     edx,offset repne_text
        mov     ecx,5
        mov     eax,2
        call    display_instruction_shifted
        jmp     done_disasm
    .ELSEIF (al ==  10010000b)
      ; nop
        mov     edx,offset nop_text
        mov     ecx,3
    .ELSEIF (al ==  11001100b)
      ; int3
        mov     edx,offset int3_text
        mov     ecx,4
    .ELSEIF (al ==  01100001b)
      ; popa
        cmp     fs:op_size_override,0
        jz      @F
            mov     edx,offset popad_text
            mov     ecx,5
            dec     esi                                             ; This just become a two-byte instruction, backup one byte
            mov     ebx,2
            jmp     show_instruction
        @@:
            mov     edx,offset popa_text
            mov     ecx,4
    .ELSEIF (al ==  10011101b)
      ; popf
        cmp     fs:op_size_override,0
        jz      @F
            mov     edx,offset popfd_text
            mov     ecx,5
            jmp     show_instruction
        @@:
            mov     edx,offset popf_text
            mov     ecx,4
    .ELSEIF (al ==  01100000b)
      ; pusha
        cmp     fs:op_size_override,0
        jz      @F
            mov     edx,offset pushad_text
            mov     ecx,6
            dec     esi                                             ; This just become a two-byte instruction, backup one byte
            mov     ebx,2
            jmp     show_instruction
        @@:
            mov     edx,offset pusha_text
            mov     ecx,5
    .ELSEIF (al ==  10011100b)
      ; pushf
        cmp     fs:op_size_override,0
        jz      @F
            mov     edx,offset pushfd_text
            mov     ecx,6
            dec     esi                                             ; This just become a two-byte instruction, backup one byte
            mov     ebx,2
            jmp     show_instruction
        @@:
            mov     edx,offset pushf_text
            mov     ecx,5
    .ELSEIF (al ==  11000011b)
      ; ret
        mov     edx,offset ret_text
    .ELSEIF (al == 11001011b)
      ; retf
        mov     edx,offset retf_text
        mov     ecx,4
    .ELSEIF (al == 11001010b)
      ; retf
        mov     edx,offset retf_text
        mov     ebx,3
        call    display_instruction
        mov     dx,word ptr ds:[esi-2]
        call    show_register_16
        add     edi,5
        jmp     done_disasm
    .ELSEIF (al ==  10011110b)
      ; sahf
        mov     edx,offset sahf_text
        mov     ecx,4
    .ELSEIF (al ==  11111001b)
      ; stc
        mov     edx,offset stc_text
    .ELSEIF (al ==  11111101b)
      ; std
        mov     edx,offset std_text
    .ELSEIF (al ==  11111011b)
      ; sti
        mov     edx,offset sti_text
    .ELSEIF (al ==  10011011b)
      ; wait
        mov     edx,offset wait_text
        mov     ecx,4
    .ELSEIF (al ==  11010111b)
      ; xlat
        mov     ecx,4
        mov     edx,offset xlat_text
        call    display_instruction
        call    display_segment_override
        jmp     done_disasm
    .ELSEIF (al == 01100011b)
      ; arpl
        mov     edx,offset arpl_text
        mov     ecx,4
        call    display_instruction_with_mod_reg_rm
        jmp     done_disasm
    .ELSEIF (al == 01100010b)
      ; bound
        mov     edx,offset bound_text
        mov     ecx,5
    .ELSEIF (al == 11101000b)
      ; call rel16/32
        mov     ebx,1
        mov     edx,offset call_text
        mov     ecx,4
        call    display_instruction
        .IF (fs:adr_size_override == 0)
            mov     dx,word ptr ds:[esi]
            add     esi,2
            call    show_register_16_signed
            add     edi,6
            call    show_new_cs_ip
        .ELSE
            mov     edx,dword ptr ds:[esi]
            add     esi,4
            call    show_register_32_signed
            add     edi,9
            call    show_new_cs_eip
        .ENDIF
        jmp     done_disasm
    .ELSEIF (al == 10011010b)
      ; call abs16:16/16:32
        mov     ebx,2
        mov     edx,offset call_text
        mov     ecx,4
        call    display_instruction
        .IF (fs:adr_size_override == 0)
            mov     dx,word ptr ds:[esi]
            add     esi,2
            call    show_register_16
            add     edi,4
            call    display_colon
            mov     dx,word ptr ds:[esi+2]
            call    show_register_16
            add     edi,5
            call    show_new_cs_ip_far
        .ELSE
            mov     ebx,7
            mov     dx,word ptr ds:[esi]
            add     esi,4
            call    show_register_16
            add     edi,4
            call    display_colon
            mov     edx,dword ptr ds:[esi+2]
            call    show_register_32
            add     edi,9
            call    show_new_cs_eip_far
        .ENDIF
        jmp     done_disasm
    .ELSEIF (al == 11111111b)
      ; call, jmp or push
        mov     dl,ah
        shr     dl,3
        and     dl,0111b
        .IF (dl == 010b)
          ; call near ptr; ax
            mov     edx,offset call_text
            mov     ecx,4
            call    display_instruction_with_mod_rm
            jmp     done_disasm
        .ELSEIF (dl == 011b)
          ; call far ptr ds:[di]
            mov     edx,offset call_far_text
            mov     ecx,5
            call    display_instruction_with_mod_rm
            jmp     done_disasm
        .ELSEIF (dl == 100b)
          ; jmp ax; word ptr
            mov     edx,offset jmp_text
            call    display_instruction_with_mod_rm
            jmp     done_disasm
        .ELSEIF (dl == 101b)
          ; jmp far ptr ds:[di]
            mov     edx,offset jmp_far_text
            mov     ecx,4
            call    display_instruction_with_mod_rm
            jmp     done_disasm
        .ELSEIF (dl == 110b)
          ; push mem16
            mov     ebx,2
            .IF (fs:op_size_override == 0)
                mov     edx,offset push_text
                mov     ecx,4
            .ELSE
                mov     edx,offset pushd_text
                mov     ecx,5
            .ENDIF
            call    display_instruction_with_mod_rm
            jmp     done_disasm
        .ELSE
          ; Who knows, it might be decoded later because we didn't hit all bit combinations
            jmp     @F
        .ENDIF
    .ELSEIF (al == 11001000b)
      ; enter
        mov     ebx,4
        mov     edx,offset enter_text
        mov     ecx,5
        call    display_instruction
        mov     dx,word ptr ds:[esi-3]
        call    show_register_16
        add     edi,4
        call    display_comma
        mov     dl,byte ptr ds:[esi-1]
        call    show_register_8
        add     edi,2
        jmp     done_disasm
    .ELSEIF (al == 11001101b)
      ; int
        mov     ebx,2
        mov     edx,offset int_text
        call    display_instruction
        mov     dl,byte ptr ds:[esi-1]
        call    show_register_8
        add     edi,2
        jmp     done_disasm
    .ELSEIF (al == 11100011b)
      ; jcxz
        mov     ebx,2
        .IF (fs:adr_size_override == 0)
            mov     edx,offset jcxz_text
            mov     ecx,4
        .ELSE
            dec     esi
            inc     ebx
            mov     edx,offset jecxz_text
            mov     ecx,5
        .ENDIF
      show_new_disp1_address:
        call    display_instruction
        xor     edx,edx
        mov     dl,byte ptr ds:[esi-1]
        call    show_register_8_signed
        add     edi,4
        call    show_new_cs_ip
        jmp     done_disasm
    .ELSEIF (al == 11101011b)
      ; jmp disp1
        mov     ebx,2
        mov     ecx,3
        mov     edx,offset jmp_text
        jmp     show_new_disp1_address
    .ELSEIF (al == 11101001b)
      ; jmp disp2/disp4
        mov     ebx,3
        mov     edx,offset jmp_text
        .IF (fs:op_size_override != 0)
            add     ebx,2
            call    display_instruction
            mov     edx,dword ptr ds:[esi-4]
            call    show_register_32
            add     edi,9
            call    show_new_cs_ip_far
        .ELSE
            call    display_instruction
            mov     dx,word ptr ds:[esi-4]
            call    show_register_16
            add     edi,5
            call    show_new_cs_ip
        .ENDIF
        jmp     done_disasm
    .ELSEIF (al == 11101010b)
      ; jmp disp4/disp6
        mov     ebx,5
        mov     edx,offset jmp_text
        .IF (fs:op_size_override != 0)
            add     ebx,2
            call    display_instruction
            mov     dx,word ptr ds:[esi-6]
            call    show_register_16
            add     edi,4
            call    display_colon
            mov     edx,dword ptr ds:[esi-4]
            call    show_register_32
            add     edi,9
        .ELSE
            call    display_instruction
            mov     edx,dword ptr ds:[esi-4]
            call    show_register_32
            add     edi,9
            call    show_new_cs_ip_far
        .ENDIF
        jmp     done_disasm
    .ELSEIF (al == 11000101b)
      ; lds
        mov     fs:reverse_regs,1
        mov     ebx,2
        mov     edx,offset lds_text
        call    display_instruction_with_mod_reg_rm
        jmp     done_disasm
    .ELSEIF (al == 11000100b)
      ; les
        mov     fs:reverse_regs,1
        mov     ebx,2
        mov     edx,offset les_text
        call    display_instruction_with_mod_reg_rm
        jmp     done_disasm
    .ELSEIF (al == 10001101b)
      ; lea
        mov     fs:reverse_regs,1
        mov     ebx,2
        mov     edx,offset lea_text
        call    display_instruction_with_mod_reg_rm
        jmp     done_disasm
    .ELSEIF (al == 11100010b)
      ; loop
        mov     ebx,2
        mov     edx,offset loop_text
        mov     ecx,4
      loop_instructions:
        call    display_instruction
        .IF (fs:op_size_override != 0)
            mov     al,CONST_ECX
            call    display_register_name_32
            add     edi,1
        .ENDIF
        xor     edx,edx
        mov     dl,byte ptr ds:[esi-1]
        call    show_register_8_signed
        add     edi,4
        call    show_new_cs_ip
        jmp     done_disasm
    .ELSEIF (al == 11100001b)
      ; loope
        mov     edx,offset loope_text
        mov     ecx,5
        jmp     loop_instructions
    .ELSEIF (al == 11100000b)
      ; loopne
        mov     edx,offset loopne_text
        mov     ecx,6
        jmp     loop_instructions
    .ELSEIF (al == 11000010b)
      ; ret immed
        mov     ebx,3
        mov     edx,offset ret_text
        call    display_instruction
        mov     dx,word ptr ds:[esi-2]
        call    show_register_16
        add     edi,5
        jmp     done_disasm
    .ELSEIF (al == 10001111b)
      ; might be pop
        mov     dl,ah
        shr     dl,3
        and     dl,0111b
        cmp     dl,000b
        jnz     @F
        ; It's pop
        mov     edx,offset pop_text
        mov     ebx,2
        call    display_instruction_with_mod_rm
        jmp     done_disasm
    .ELSE
        jmp     two_byte_instructions
    .ENDIF
  ; It was a one-byte instruction
    jmp     show_instruction

  two_byte_instructions:
    mov     ebx,2
    .IF (ax == 0000101011010101b)
      ; aad
        mov     edx,offset aad_text
    .ELSEIF (ax == 0000101011010100b)
      ; aam
        mov     edx,offset aam_text
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
    mov     ecx,4
    mov     ebx,1
    .IF (dl == 1010010b)
      ; movs
        mov     ecx,5
        .IF (dh == 0)
            mov     edx,offset movsb_text
        .ELSEIF (fs:op_size_override != 0)
            mov     edx,offset movsd_text
        .ELSE
            mov     edx,offset movsw_text
        .ENDIF
        call    display_instruction
        jmp     done_disasm
    .ELSEIF (dl == 1010101b)
      ; stos
        mov     ecx,5
        .IF (dh == 0)
            mov     edx,offset stosb_text
        .ELSEIF (fs:op_size_override != 0)
            mov     edx,offset stosd_text
        .ELSE
            mov     edx,offset stosw_text
        .ENDIF
        call    display_instruction
        jmp     done_disasm
    .ELSEIF (dl == 1010110b)
      ; lods
        mov     ecx,5
        .IF (dh == 0)
            mov     edx,offset lodsb_text
        .ELSEIF (fs:op_size_override != 0)
            mov     edx,offset lodsd_text
        .ELSE
            mov     edx,offset lodsw_text
        .ENDIF
        call    display_instruction
        jmp     done_disasm
    .ELSEIF (dl == 0110110b)
      ; ins
        mov     ecx,4
        mov     ebx,1
        .IF (dh == 0)
            mov     edx,offset insb_text
        .ELSEIF (fs:op_size_override != 0)
            mov     edx,offset insd_text
        .ELSE
            mov     edx,offset insw_text
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
        jmp     done_disasm
    .ELSEIF (dl == 0110111b)
      ; outs
        mov     ecx,5
        mov     ebx,1
        .IF (dh == 0)
            mov     edx,offset outsb_text
        .ELSEIF (fs:op_size_override != 0)
            mov     edx,offset outsd_text
        .ELSE
            mov     edx,offset outsw_text
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
        jmp     done_disasm
    .ELSEIF (dl == 1010011b)
      ; cmps
        mov     ecx,5
        .IF (dh == 0)
            mov     edx,offset cmpsb_text
        .ELSEIF (fs:op_size_override != 0)
            mov     edx,offset cmpsd_text
        .ELSE
            mov     edx,offset cmpsw_text
        .ENDIF
        call    display_instruction
        jmp     done_disasm
    .ELSEIF (dl == 1010111b)
      ; scas
        mov     ecx,5
        .IF (dh == 0)
            mov     edx,offset scasb_text
        .ELSEIF (fs:op_size_override != 0)
            mov     edx,offset scasd_text
        .ELSE
            mov     edx,offset scasw_text
        .ENDIF
        call    display_instruction
        jmp     done_disasm
    .ELSEIF (dl == 0000010b)
      ; add accum,immed
        mov     al,dh
        mov     edx,offset add_text
        mov     ecx,3
      display_accum_instruction:
        .IF (al == 0)
            mov     ebx,2
            call    display_instruction
            mov     al,CONST_AL
            call    display_register_name_8
            call    display_comma
            mov     dl,byte ptr ds:[esi-1]
            call    show_register_8
            add     edi,2
        .ELSE
            .IF (fs:op_size_override != 0)
              ; eax
                mov     ebx,5
                call    display_instruction
                mov     al,CONST_EAX
                call    display_register_name_32
                call    display_comma
                mov     edx,dword ptr ds:[esi-4]
                call    show_register_32
                add     edi,9
            .ELSE
              ; ax
                mov     ebx,3
                call    display_instruction
                mov     al,CONST_AX
                call    display_register_name_16
                call    display_comma
                mov     dx,word ptr ds:[esi-2]
                call    show_register_16
                add     edi,5
            .ENDIF
        .ENDIF
        jmp     done_disasm
    .ELSEIF (dl == 0000110b)
      ; or accum,immed
        mov     al,dh
        mov     edx,offset or_text
        mov     ecx,2
        jmp     display_accum_instruction
    .ELSEIF (dl == 0001010b)
      ; adc accum,immed
        mov     al,dh
        mov     edx,offset adc_text
        mov     ecx,3
        jmp     display_accum_instruction
    .ELSEIF (dl == 0001110b)
      ; sbb accum,immed
        mov     al,dh
        mov     edx,offset sbb_text
        mov     ecx,3
        jmp     display_accum_instruction
    .ELSEIF (dl == 0010010b)
      ; and accum,immed
        mov     al,dh
        mov     edx,offset and_text
        mov     ecx,3
        jmp     display_accum_instruction
    .ELSEIF (dl == 0010110b)
      ; sub accum,immed
        mov     al,dh
        mov     edx,offset sub_text
        mov     ecx,3
        jmp     display_accum_instruction
    .ELSEIF (dl == 0011010b)
      ; xor accum,immed
        mov     al,dh
        mov     edx,offset xor_text
        mov     ecx,3
        jmp     display_accum_instruction
    .ELSEIF (dl == 0011110b)
      ; cmp accum,immed
        mov     al,dh
        mov     edx,offset cmp_text
        mov     ecx,3
        jmp     display_accum_instruction
    .ELSEIF (dl == 1000010b)
      ; test reg,reg; reg,mem; mem,reg
        mov     fs:byte_word_size,dh
        mov     ebx,2
        mov     edx,offset test_text
        mov     ecx,4
        call    display_instruction_with_mod_reg_rm
        jmp     done_disasm
    .ELSEIF (dl == 1010100b)
      ; test accum,immed
        mov     al,dh
        mov     edx,offset test_text
        mov     ecx,4
        jmp     display_accum_instruction
    .ELSEIF (dl == 1110010b)
      ; in ax,60h
        mov     ebx,2
        mov     edx,offset in_text
        mov     ecx,2
        call    display_instruction
        .IF (dh == 0)
          ; al
            mov     al,CONST_AL
            call    display_register_name_8
        .ELSE
            .IF (fs:op_size_override != 0)
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
        mov     dl,byte ptr ds:[esi-1]
        call    show_register_8
        add     edi,2
        jmp     done_disasm
    .ELSEIF (dl == 1110011b)
      ; out 60h,al
        mov     ebx,2
        mov     edx,offset outsb_text
        mov     ecx,3
        call    display_instruction
        mov     dl,byte ptr ds:[esi-1]
        call    show_register_8
        add     edi,2
        call    display_comma
        .IF (dh == 0)
          ; al
            mov     al,CONST_AL
            call    display_register_name_8
        .ELSE
            .IF (fs:op_size_override != 0)
              ; eax
                mov     al,CONST_EAX
                call    display_register_name_32
            .ELSE
              ; ax
                mov     al,CONST_AX
                call    display_register_name_16
            .ENDIF
        .ENDIF
        jmp     done_disasm
    .ELSEIF (dl == 1110110b)
      ; in al,dx
        mov     ebx,1
        mov     edx,offset in_text
        mov     ecx,2
        call    display_instruction
        .IF (dh == 0)
          ; al
            mov     al,CONST_AL
            call    display_register_name_8
        .ELSE
            .IF (fs:op_size_override != 0)
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
        jmp     done_disasm
    .ELSEIF (dl == 1110111b)
      ; out dx,al
        push    edx
        mov     ebx,1
        mov     edx,offset outsb_text
        mov     ecx,3
        call    display_instruction
        mov     al,CONST_DX
        call    display_register_name_16
        call    display_comma
        pop     edx
        .IF (dh == 0)
          ; al
            mov     al,CONST_AL
            call    display_register_name_8
        .ELSE
            .IF (fs:op_size_override != 0)
              ; eax
                mov     al,CONST_EAX
                call    display_register_name_32
            .ELSE
              ; ax
                mov     al,CONST_AX
                call    display_register_name_16
            .ENDIF
        .ENDIF
        jmp     done_disasm
    .ELSEIF (dl == 1111011b)
      ; It could be test, not, neg, mul, imul, div, idiv
        mov     ebx,2
        mov     fs:byte_word_size,dh
        mov     ecx,3
        mov     dh,ah
        shr     dh,3
        and     dh,0111b
        .IF (dh == 000b)
          ; test
            mov     edx,offset test_text
            mov     ecx,4
        .ELSEIF (dh == 010b)
          ; not
            mov     edx,offset not_text
        .ELSEIF (dh == 011b)
          ; neg
            mov     edx,offset neg_text
        .ELSEIF (dh == 100b)
          ; mul
            mov     edx,offset mul_text
        .ELSEIF (dh == 101b)
          ; imul
            mov     edx,offset imul_text
            mov     ecx,4
        .ELSEIF (dh == 110b)
          ; div
            mov     edx,offset div_text
        .ELSEIF (dh == 111b)
          ; idiv
            mov     edx,offset idiv_text
            mov     ecx,4
        .ELSE
          ; It's not one of the recognized encodings, continue to search
            mov     dl,al
            shr     dl,1
            mov     dh,al
            and     dh,1b
            jmp     @F
        .ENDIF
        call    display_instruction_with_mod_rm
        jmp     done_disasm
    .ELSE
        jmp     @F
    .ENDIF
    jmp     show_instruction

  @@:
    mov     ah,byte ptr ds:[esi+1]
    shr     ah,3
    and     ah,111b
    .IF (dl == 1111111b)
      ; It could be dec, inc
        mov     fs:byte_word_size,dh
        .IF (ah == 000b)
          ; inc
            mov     edx,offset inc_text
          inc_dec_locals:
            mov     ecx,3
            mov     ebx,2
            call    display_instruction_with_mod_rm
            jmp     done_disasm
        .ELSEIF (ah == 001b)
          ; dec
            mov     edx,offset dec_text
            jmp     inc_dec_locals
        .ELSE
            jmp     @F
        .ENDIF
        call    display_instruction_with_mod_rm
        jmp     done_disasm
    .ELSEIF (dl == 1100011b)
      ; It could be mov mem,immed
        .IF (ah == 000b)
          ; mov mem,immed
            mov     dl,al
            and     dl,1b
            mov     fs:byte_word_size,dl
            mov     ebx,2
            mov     edx,offset mov_text
            mov     ecx,3
            call    display_instruction_with_mod_rm
            call    display_comma
            mov     edx,dword ptr ds:[esi]
            .IF (fs:byte_word_size == 0)
              ; 8-bits
                call    show_register_8
                add     edi,2
                mov     ecx,1
            .ELSE
                .IF (fs:op_size_override != 0)
                  ; 32-bits
                    call    show_register_32
                    add     edi,9
                    mov     ecx,4
                .ELSE
                  ; 16-bits
                    call    show_register_16
                    add     edi,5
                    mov     ecx,2
                .ENDIF
            .ENDIF
            call    display_instruction_additional_bytes
            jmp     done_disasm
        .ELSE
            jmp     @F
        .ENDIF
    .ELSEIF (dl == 1100000b)
      ; sar,sal,shl,shr r/m,immed
        mov     ecx,3
        mov     ebx,2
        .IF (ah == 000b)
          ; rol
            mov     edx,offset rol_text
        .ELSEIF (ah == 001b)
          ; ror
            mov     edx,offset ror_text
        .ELSEIF (ah == 010b)
          ; rcl
            mov     edx,offset rcl_text
        .ELSEIF (ah == 011b)
          ; rcr
            mov     edx,offset rcr_text
        .ELSEIF (ah == 100b)
          ; shl
            mov     edx,offset shl_text
        .ELSEIF (ah == 101b)
          ; shr
            mov     edx,offset shr_text
        .ELSEIF (ah == 111b)
          ; sar
            mov     edx,offset sar_text
        .ELSE
            mov     edx,offset unknown_text
        .ENDIF
        call    display_instruction_with_mod_rm
        mov     dl,byte ptr ds:[esi]
        mov     ecx,1
        call    display_instruction_additional_bytes
        call    display_comma
        call    show_register_8
        add     edi,2
        jmp     done_disasm
    .ELSEIF (dl == 1101000b)
      ; It is either rotate or shift by 1
        mov     ecx,3
        mov     ebx,2
        .IF (ah == 000b)
          ; rol
            mov     edx,offset rol_text
        .ELSEIF (ah == 001b)
          ; ror
            mov     edx,offset ror_text
        .ELSEIF (ah == 010b)
          ; rcl
            mov     edx,offset rcl_text
        .ELSEIF (ah == 011b)
          ; rcr
            mov     edx,offset rcr_text
        .ELSEIF (ah == 100b)
          ; shl
            mov     edx,offset shl_text
        .ELSEIF (ah == 101b)
          ; shr
            mov     edx,offset shr_text
        .ELSEIF (ah == 111b)
          ; sar
            mov     edx,offset sar_text
        .ELSE
            mov     edx,offset unknown_text
        .ENDIF
        call    display_instruction_with_mod_rm
        call    display_comma
        call    display_one
        jmp     done_disasm
    .ELSEIF (dl == 1101001b)
      ; It is either rotate or shift by cl
        mov     ecx,3
        mov     ebx,2
        .IF (ah == 000b)
          ; rol
            mov     edx,offset rol_text
        .ELSEIF (ah == 001b)
          ; ror
            mov     edx,offset ror_text
        .ELSEIF (ah == 010b)
          ; rcl
            mov     edx,offset rcl_text
        .ELSEIF (ah == 011b)
          ; rcr
            mov     edx,offset rcr_text
        .ELSEIF (ah == 100b)
          ; shl
            mov     edx,offset shl_text
        .ELSEIF (ah == 101b)
          ; shr
            mov     edx,offset shr_text
        .ELSEIF (ah == 111b)
          ; sar
            mov     edx,offset sar_text
        .ELSE
            mov     edx,offset unknown_text
        .ENDIF
        call    display_instruction_with_mod_rm
        call    display_comma
        mov     al,CONST_CL
        call    display_register_name_8
        jmp     done_disasm
    .ELSEIF (dl == 1000011b)
      ; xchg
        mov     ebx,2
        .IF (fs:op_size_override != 0)
            dec     esi
            inc     ebx
        .ENDIF
        mov     dl,al
        and     dl,1b
        mov     fs:byte_word_size,dl
        mov     edx,offset xchg_text
        mov     ecx,4
        mov     fs:reverse_regs,1
        call    display_instruction_with_mod_reg_rm
        jmp     done_disasm
    .ELSE
        jmp     @F
    .ENDIF
    jmp     show_instruction

  @@:
    shr     dl,1
    mov     ecx,3
    mov     fs:byte_word_size,dh
    .IF (dl == 000000b)
      ; add
        mov     edx,offset add_text
      local_mod_reg_rm_instructions:
        mov     ah,al
        shr     ah,1
        and     ah,1
        mov     fs:reverse_regs,ah
        mov     ebx,2
        call    display_instruction_with_mod_reg_rm
        jmp     done_disasm
    .ELSEIF (dl == 000010b)
      ; or
        mov     edx,offset or_text
        mov     ecx,2
        jmp     local_mod_reg_rm_instructions
    .ELSEIF (dl == 000100b)
      ; adc
        mov     edx,offset adc_text
        jmp     local_mod_reg_rm_instructions
    .ELSEIF (dl == 000110b)
      ; sbb
        mov     edx,offset sbb_text
        jmp     local_mod_reg_rm_instructions
    .ELSEIF (dl == 001000b)
      ; and
        mov     edx,offset and_text
        jmp     local_mod_reg_rm_instructions
    .ELSEIF (dl == 001010b)
      ; sub
        mov     edx,offset sub_text
        jmp     local_mod_reg_rm_instructions
    .ELSEIF (dl == 001100b)
      ; xor
        mov     edx,offset xor_text
        jmp     local_mod_reg_rm_instructions
    .ELSEIF (dl == 001110b)
      ; cmp
        mov     edx,offset cmp_text
        jmp     local_mod_reg_rm_instructions
    .ELSEIF (dl == 100000b)
      ; It is one of these; add, or, adc, sbb, and, sub, xor, cmp
        mov     dl,al
        shr     dl,1
        and     dl,1b
        mov     fs:sign_extend,dl
        mov     dl,al
        and     dl,1b
        mov     fs:byte_word_size,dl

        mov     ah,byte ptr ds:[esi+1]
        shr     ah,3
        and     ah,111b
        .IF (ah == 000b)
          ; add
            mov     edx,offset add_text
        .ELSEIF (ah == 001b)
          ; or
            mov     edx,offset or_text
            mov     ecx,2
        .ELSEIF (ah == 010b)
          ; adc
            mov     edx,offset adc_text
        .ELSEIF (ah == 011b)
          ; sbb
            mov     edx,offset sbb_text
        .ELSEIF (ah == 100b)
          ; and
            mov     edx,offset and_text
        .ELSEIF (ah == 101b)
          ; sub
            mov     edx,offset sub_text
        .ELSEIF (ah == 110b)
          ; xor
            mov     edx,offset xor_text
        .ELSE
          ; cmp
            mov     edx,offset cmp_text
        .ENDIF
        mov     ebx,2
        call    display_instruction_with_mod_rm
        call    display_comma
        mov     edx,dword ptr ds:[esi]
        .IF (fs:byte_word_size == 0)
          ; 8-bits
            call    show_register_8
            add     edi,2
            mov     ecx,1
        .ELSE
            .IF (fs:op_size_override != 0)
              ; 32-bits
                call    show_register_32
                add     edi,9
                mov     ecx,4
            .ELSE
              ; 16-bits
                .IF (fs:sign_extend == 0)
                    call    show_register_16
                    add     edi,5
                    mov     ecx,2
                .ELSE
                    movsx   edx,dl                                   ; Sign extend 8-bits to 32-bits
                    call    show_register_16
                    add     edi,5
                    mov     ecx,1
                .ENDIF
            .ENDIF
        .ENDIF
        call    display_instruction_additional_bytes
        jmp     done_disasm
    .ELSEIF (dl == 100010b)
      ; mov reg,reg; mem,reg; reg,mem
        mov     dl,al
        and     dl,1b
        mov     fs:byte_word_size,dl
        mov     dl,al
        shr     dl,1
        and     dl,1b
        mov     fs:reverse_regs,dl
        mov     edx,offset mov_text
        mov     ecx,3
        mov     ebx,2
        call    display_instruction_with_mod_reg_rm
        jmp     done_disasm
    .ELSEIF (dl == 101000b)
      ; mov accum,mem; mem,accum
        mov     dh,al
        shr     dh,2
        and     dh,1b
        mov     fs:reverse_regs,dh
        mov     edx,offset mov_text
        mov     ecx,3
        mov     ebx,1
        call    adjust_for_overrides
        call    display_instruction
        mov     dx,word ptr ds:[esi]
        mov     ecx,2
        call    display_instruction_additional_bytes
        .IF (fs:reverse_regs == 1)
            call    mov_show_part
            call    display_comma
            call    display_register_name_accumulator
        .ELSE
            call    display_register_name_accumulator
            call    display_comma
            call    mov_show_part
        .ENDIF
        jmp     done_disasm
    .ELSE
        jmp     @F
    .ENDIF
    jmp     show_instruction

mov_show_part:
    call    display_segment_override
    call    display_open_bracket
    call    show_register_16
    add     edi,4
    call    display_close_bracket
    ret

  @@:
    shr     dl,1                                                    ; This makes a total of 3 bits shifted, 2 from above
    .IF (dl == 01000b)
      ; inc
        mov     edx,offset inc_text
      inc_dec_locals_2:
        mov     ecx,3
        mov     ebx,1
        call    display_instruction
        mov     al,byte ptr ds:[esi-1]
        and     al,111b
        .IF (fs:op_size_override == 0)
            call    display_register_name_16
        .ELSE
            call    display_register_name_32
        .ENDIF
        jmp     done_disasm
    .ELSEIF (dl == 01001b)
      ; dec
        mov     edx,offset dec_text
        jmp     inc_dec_locals_2
    .ELSEIF (dl == 01010b)
      ; push
        mov     ebx,1
        .IF (fs:op_size_override != 0)
            dec     esi
            inc     ebx
        .ENDIF
        mov     edx,offset push_text
        mov     ecx,4
      push_pop_locals:
        call    display_instruction
        mov     al,byte ptr ds:[esi-1]
        and     al,0111b
        .IF (fs:op_size_override == 0)
            call    display_register_name_16
        .ELSE
            call    display_register_name_32
        .ENDIF
        jmp     done_disasm
    .ELSEIF (dl == 01011b)
      ; pop
        mov     edx,offset pop_text
        jmp     push_pop_locals
    .ELSEIF (dl == 10010b)
      ; xchg accum,reg
        .IF (fs:op_size_override != 0)
            dec     esi
            inc     ebx
        .ENDIF
        mov     edx,offset xchg_text
        mov     ecx,4
        call    display_instruction
        mov     al,CONST_AX
        .IF (fs:op_size_override == 0)
            call    display_register_name_16
            call    display_comma
            mov     al,byte ptr ds:[esi-1]
            and     al,111b
            call    display_register_name_16
        .ELSE
            call    display_register_name_32
            call    display_comma
            mov     al,byte ptr ds:[esi-1]
            and     al,111b
            call    display_register_name_32
        .ENDIF
        jmp     done_disasm
    .ELSE
        jmp     @F
    .ENDIF
    jmp     show_instruction

  @@:
    mov     dl,al
    and     dl,11111101b
    .IF (dl == 01101000b)
      ; push
        mov     edx,offset push_text
        mov     ecx,4
    .ELSEIF (dl == 01101001b)
      ; imul
        mov     edx,offset imul_text
        mov     ecx,4
    .ELSEIF (dl == 10001100b)
      ; mov sreg,reg
        mov     ebx,2
        mov     dl,al
        shr     dl,1
        and     dl,1b
        mov     fs:reverse_regs,dl
        mov     fs:sreg_override,1
        mov     fs:byte_word_size,1
        mov     edx,offset mov_text
        mov     ecx,3
        call    display_instruction_with_mod_reg_rm
        jmp     done_disasm
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
        mov     fs:byte_word_size,al
        mov     ebx,1
        mov     edx,offset mov_text
        mov     ecx,3
        call    display_instruction
        mov     al,byte ptr ds:[esi-1]
        and     al,111b
        mov     edx,dword ptr ds:[esi]
        .IF (fs:byte_word_size == 0)
          ; 8-bit
            call    display_register_name_8
            mov     ecx,1
            call    display_comma
            call    display_instruction_additional_bytes
            call    show_register_8
            add     edi,2
        .ELSE
            .IF (fs:op_size_override != 0)
              ; 32-bit
                call    display_register_name_32
                mov     ecx,4
                call    display_comma
                call    display_instruction_additional_bytes
                call    show_register_32
                add     edi,9
            .ELSE
              ; 16-bit
                call    display_register_name_16
                mov     ecx,2
                call    display_comma
                call    display_instruction_additional_bytes
                call    show_register_16
                add     edi,5
            .ENDIF
        .ENDIF
        jmp     done_disasm
    .ELSEIF (dl == 0111b)
      ; jccc +/- 128
        mov     ebx,2
        mov     dl,al
        and     dl,01111b
        .IF (dl == 0000b)
          ; It's jo
            mov     edx,offset jo_text
            mov     ecx,2
        .ELSEIF (dl ==  0001b)
          ; It's jno
            mov     edx,offset jno_text
        .ELSEIF (dl ==  0010b)
          ; It's jc/jb/jnae (unsigned)
            mov     edx,offset jc_text
            mov     ecx,2
        .ELSEIF (dl ==  0011b)
          ; It's jnc/jnb/jae (unsigned)
            mov     edx,offset jnc_text
        .ELSEIF (dl ==  0100b)
          ; It's jz/je
            mov     edx,offset jz_text
            mov     ecx,2
        .ELSEIF (dl ==  0101b)
          ; It's jnz/jne
            mov     edx,offset jnz_text
        .ELSEIF (dl ==  0110b)
          ; It's jbe/jna (unsigned)
            mov     edx,offset jbe_text
        .ELSEIF (dl ==  0111b)
          ; It's ja/jnbe (unsigned)
            mov     edx,offset ja_text
            mov     ecx,2
        .ELSEIF (dl ==  1000b)
          ; It's js
            mov     edx,offset js_text
            mov     ecx,2
        .ELSEIF (dl ==  1001b)
          ; It's jns
            mov     edx,offset jns_text
        .ELSEIF (dl ==  1010b)
          ; It's jp
            mov     edx,offset jp_text
            mov     ecx,2
        .ELSEIF (dl ==  1011b)
          ; It's jnp
            mov     edx,offset jnp_text
        .ELSEIF (dl ==  1100b)
          ; It's jl/jnge (signed)
            mov     edx,offset jl_text
            mov     ecx,2
        .ELSEIF (dl ==  1101b)
          ; It's jge/nl (signed)
            mov     edx,offset jge_text
        .ELSEIF (dl ==  1110b)
          ; It's jle/jng (signed)
            mov     edx,offset jle_text
        .ELSE
            ; It's jg/jnle (signed)                                 ; It's the only combination left
            mov     edx,offset jg_text
            mov     ecx,2
        .ENDIF
        call    display_instruction
        movsx   edx,byte ptr ds:[esi-1]
        call    show_register_8_signed
        add     edi,4
        call    show_new_cs_ip
        jmp     done_disasm
    .ELSE
        mov     dl,al
        and     dl,11000111b
        .IF (dl == 00000111b)
          ; pop
            mov     edx,offset pop_text
            mov     ecx,3
          push_pop_locals_2:
            call    display_instruction
            shr     al,3
            and     al,111b
            call    display_register_name_sreg
            jmp     done_disasm
        .ELSEIF (dl == 00000110b)
          ; push
            mov     edx,offset push_text
            mov     ecx,4
            jmp     push_pop_locals_2
        .ELSE
            jmp     check_fpu_instructions
        .ENDIF
    .ENDIF
  show_instruction:
    call    display_instruction
    jmp     done_disasm


;; Check the FPU instructions
  check_fpu_instructions:
    mov     ebx,2
    mov     eax,dword ptr ds:[esi]
    mov     ecx,4                                                   ; Default to a 4-byte wide instruction name
    .IF (al == 0d8h)
        mov     al,ah
        and     al,not 0111b
        .IF (al == 0c0h)
          ; fadd st(0),st(i)
            mov     edx,offset fadd_text
        .ELSEIF (al == 0c8h)
          ; fmul st(0),st(i)
            mov     edx,offset fmul_text
        .ELSEIF (al == 0d0h)
          ; fcom st(0),st(i)
            mov     edx,offset fcom_text
        .ELSEIF (al == 0d8h)
          ; fcomp st(0),st(i)
            mov     edx,offset fcomp_text
            mov     ecx,5
        .ELSEIF (al == 0e0h)
          ; fsub st(0),st(i)
            mov     edx,offset fsub_text
        .ELSEIF (al == 0e8h)
          ; fsubr st(0),st(i)
            mov     edx,offset fsubr_text
            mov     ecx,5
        .ELSEIF (al == 0f0h)
          ; fdiv st(0),st(i)
            mov     edx,offset fdiv_text
        .ELSEIF (al == 0f8h)
          ; fdivr  st(0),st(i)
            mov     edx,offset fdivr_text
            mov     ecx,5
        .ELSE
            jmp     @F
        .ENDIF
        jmp     show_instruction

      @@:
        shr     ah,3
        and     ah,0111b
        .IF (ah == 0)
          ; fadd real32
            mov     edx,offset fadd_text
        .ELSEIF (ah == 1)
          ; fmul real32
            mov     edx,offset fmul_text
        .ELSEIF (ah == 2)
          ; fcom real32
            mov     edx,offset fcom_text
        .ELSEIF (ah == 3)
          ; fcomp real32
            mov     edx,offset fcomp_text
            mov     ecx,5
        .ELSEIF (ah == 4)
          ; fsub real32
            mov     edx,offset fsub_text
        .ELSEIF (ah == 5)
          ; fsubr real32
            mov     edx,offset fsubr_text
            mov     ecx,5
        .ELSEIF (ah == 6)
          ; fdiv real32
            mov     edx,offset fdiv_text
        .ELSEIF (ah == 7)
          ; fdivr real32
            mov     edx,offset fdivr_text
            mov     ecx,5
        .ELSE
          ; Invalid opcode
            jmp     unknown_instruction
        .ENDIF
    .ELSEIF (al == 0d9h)
        mov     al,ah
        and     al,not 0111b
        .IF (al == 0c0h)
          ; fld st(i)
            mov     edx,offset fld_text
            mov     ecx,3
        .ELSEIF (al == 0c8h)
          ; fxch st(i)
            mov     edx,offset fxch_text
        .ELSEIF (ah == 0d0h)
          ; fnop
            mov     edx,offset fnop_text
        .ELSEIF (ah == 0e0h)
          ; fchs
            mov     edx,offset fchs_text
        .ELSEIF (ah == 0e1h)
          ; fabs
            mov     edx,offset fabs_text
        .ELSEIF (ah == 0e4h)
          ; ftst
            mov     edx,offset ftst_text
        .ELSEIF (ah == 0e5h)
          ; fxam
            mov     edx,offset fxam_text
        .ELSEIF (ah == 0e8h)
          ; fld1
            mov     edx,offset fld1_text
        .ELSEIF (ah == 0e9h)
          ; fldl2t
            mov     edx,offset fldl2t_text
            mov     ecx,6
        .ELSEIF (ah == 0eah)
          ; fldl2e
            mov     edx,offset fldl2e_text
            mov     ecx,6
        .ELSEIF (ah == 0ebh)
          ; fldpi
            mov     edx,offset fldpi_text
            mov     ecx,5
        .ELSEIF (ah == 0ech)
          ; fldg2
            mov     edx,offset fldg2_text
            mov     ecx,5
        .ELSEIF (ah == 0edh)
          ; fldn2
            mov     edx,offset fldn2_text
            mov     ecx,5
        .ELSEIF (ah == 0eeh)
          ; fldz
            mov     edx,offset fldz_text
        .ELSEIF (ah == 0f0h)
          ; f2xm1
            mov     edx,offset f2xm1_text
            mov     ecx,5
        .ELSEIF (ah == 0f1h)
          ; fyl2x
            mov     edx,offset fyl2x_text
            mov     ecx,5
        .ELSEIF (ah == 0f2h)
          ; fptan
            mov     edx,offset fptan_text
            mov     ecx,5
        .ELSEIF (ah == 0f3h)
          ; fpatan
            mov     edx,offset fpatan_text
            mov     ecx,6
        .ELSEIF (ah == 0f4h)
          ; fxtract
            mov     edx,offset fxtract_text
            mov     ecx,7
        .ELSEIF (ah == 0f5h)
          ; fprem1
            mov     edx,offset fprem1_text
            mov     ecx,6
        .ELSEIF (ah == 0f6h)
          ; fdecstp
            mov     edx,offset fdecstp_text
            mov     ecx,7
        .ELSEIF (ah == 0f7h)
          ; fincstp
            mov     edx,offset fincstp_text
            mov     ecx,7
        .ELSEIF (ah == 0f8h)
          ; fprem
            mov     edx,offset fprem_text
            mov     ecx,5
        .ELSEIF (ah == 0f9h)
          ; fyl2xp1
            mov     edx,offset fyl2xp1_text
            mov     ecx,7
        .ELSEIF (ah == 0fah)
          ; fsqrt
            mov     edx,offset fsqrt_text
            mov     ecx,5
        .ELSEIF (ah == 0fbh)
          ; fsincos
            mov     edx,offset fsincos_text
            mov     ecx,7
        .ELSEIF (ah == 0fch)
          ; frndint
            mov     edx,offset frndint_text
            mov     ecx,7
        .ELSEIF (ah == 0fdh)
          ; fscale
            mov     edx,offset fscale_text
            mov     ecx,6
        .ELSEIF (ah == 0feh)
          ; fsin
            mov     edx,offset fsin_text
        .ELSEIF (ah == 0ffh)
          ; fcos
            mov     edx,offset fcos_text
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
            mov     edx,offset fld_text
            mov     ecx,3
        .ELSEIF (al == 2)
          ; fst real32
            mov     edx,offset fst_text
            mov     ecx,3
        .ELSEIF (al == 3)
          ; fstp real32
            mov     edx,offset fstp_text
        .ELSEIF (al == 4)
          ; fldenv
            mov     edx,offset fldenv_text
            mov     ecx,6
        .ELSEIF (al == 5)
          ; fldcw
            mov     edx,offset fldcw_text
            mov     ecx,5
        .ELSEIF (al == 6)
          ; fstenv
            mov     edx,offset fstenv_text
            mov     ecx,6
        .ELSEIF (al == 7)
          ; fstcw
            mov     edx,offset fstcw_text
            mov     ecx,5
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
            mov     edx,offset fucompp_text
            mov     ecx,7
        .ELSEIF (al == 0)
          ; fiadd int32
            mov     edx,offset fiadd_text
            mov     ecx,5
        .ELSEIF (al == 1)
          ; fimul int32
            mov     edx,offset fimul_text
            mov     ecx,5
        .ELSEIF (al == 2)
          ; ficom int32
            mov     edx,offset ficom_text
            mov     ecx,5
        .ELSEIF (al == 3)
          ; ficomp int32
            mov     edx,offset ficomp_text
            mov     ecx,6
        .ELSEIF (al == 4)
          ; fisub int32
            mov     edx,offset fisub_text
            mov     ecx,5
        .ELSEIF (al == 5)
          ; fisubr int32
            mov     edx,offset fisubr_text
            mov     ecx,7
        .ELSEIF (al == 6)
          ; fidiv int32
            mov     edx,offset fidiv_text
            mov     ecx,5
        .ELSEIF (al == 7)
          ; fidivr int32
            mov     edx,offset fidivr_text
            mov     ecx,6
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
            mov     edx,offset fclex_text
            mov     ecx,5
        .ELSEIF (ah == 0e3h)
          ; finit
            mov     edx,offset finit_text
            mov     ecx,5
        .ELSEIF (al == 0)
          ; fild int32
            mov     edx,offset fild_text
        .ELSEIF (al == 2)
          ; fist int32
            mov     edx,offset fist_text
        .ELSEIF (al == 3)
          ; fistp int32
            mov     edx,offset fistp_text
            mov     ecx,5
        .ELSEIF (al == 4)
          ; fld real80
            mov     edx,offset fld_text
            mov     ecx,3
        .ELSEIF (al == 6)
          ; fstp real80
            mov     edx,offset fstp_text
        .ELSE
          ; Invalid opcode
            jmp     unknown_instruction
        .ENDIF
    .ELSEIF (al == 0dch)
        mov     al,ah
        and     al,not 0111b
        .IF (al == 0c0h)
          ; fadd st(i),st(0)
            mov     edx,offset fadd_text
        .ELSEIF (al == 0c8h)
          ; fmul st(i),st(0)
            mov     edx,offset fmul_text
        .ELSEIF (al == 0e0h)
          ; fsubr st(i),st(0)
            mov     edx,offset fsubr_text
            mov     ecx,5
        .ELSEIF (al == 0e8h)
          ; fsub st(i),st(0)
            mov     edx,offset fsub_text
        .ELSEIF (al == 0f0h)
          ; fidivr st(i),st(0)
            mov     edx,offset fidivr_text
            mov     ecx,6
        .ELSEIF (al == 0f8h)
          ; fidiv st(i),st(0)
            mov     edx,offset fidiv_text
            mov     ecx,5
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
            mov     edx,offset fadd_text
        .ELSEIF (al == 1)
          ; fmul real64
            mov     edx,offset fmul_text
        .ELSEIF (al == 2)
          ; fcom real64
            mov     edx,offset fcom_text
        .ELSEIF (al == 3)
          ; fcomp real64
            mov     edx,offset fcomp_text
            mov     ecx,5
        .ELSEIF (al == 4)
          ; fsub real64
            mov     edx,offset fsub_text
        .ELSEIF (al == 5)
          ; fsubr real64
            mov     edx,offset fsubr_text
            mov     ecx,5
        .ELSEIF (al == 6)
          ; fdiv real64
            mov     edx,offset fdiv_text
        .ELSEIF (al == 7)
          ; fdivr real64
            mov     edx,offset fdivr_text
            mov     ecx,5
        .ELSE
          ; Invalid opcode
            jmp     unknown_instruction
        .ENDIF
    .ELSEIF (al == 0ddh)
        mov     al,ah
        and     al,not 0111b
        .IF (al == 0c0h)
          ; ffree st(i)
            mov     edx,offset ffree_text
        .ELSEIF (al == 0d0h)
          ; fst st(i)
            mov     edx,offset fst_text
            mov     ecx,3
        .ELSEIF (al == 0d8h)
          ; fstp st(i)
            mov     edx,offset fstp_text
        .ELSEIF (al == 0e0h)
          ; fucom st(i)
            mov     edx,offset fucom_text
            mov     ecx,5
        .ELSEIF (al == 0e8h)
          ; fucomp st(i)
            mov     edx,offset fucomp_text
            mov     ecx,6
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
            mov     edx,offset fld_text
            mov     ecx,3
        .ELSEIF (al == 2)
          ; fst real64
            mov     edx,offset fst_text
            mov     ecx,3
        .ELSEIF (al == 3)
          ; fstp real64
            mov     edx,offset fstp_text
        .ELSEIF (al == 4)
          ; frstor
            mov     edx,offset frstor_text
            mov     ecx,6
        .ELSEIF (al == 6)
          ; fsave
            mov     edx,offset fsave_text
            mov     ecx,5
        .ELSEIF (al == 7)
          ; fstsw
            mov     edx,offset fstsw_text
            mov     ecx,5
        .ELSE
          ; Invalid opcode
            jmp     unknown_instruction
        .ENDIF
    .ELSEIF (al == 0deh)
        .IF (ah == 0d9h)
          ; fcompp
            mov     edx,offset fcompp_text
            mov     ecx,6
            jmp     show_instruction
        .ENDIF
        mov     al,ah
        and     al,not 0111b
        .IF (al == 0c0h)
          ; faddp st(i),st(0)
            mov     edx,offset fadd_text
        .ELSEIF (al == 0c8h)
          ; fmulp st(i),st(0)
            mov     edx,offset fmulp_text
            mov     ecx,5
        .ELSEIF (al == 0e0h)
          ; fsubrp st(i),st(0)
            mov     edx,offset fsubrp_text
            mov     ecx,6
        .ELSEIF (al == 0e8h)
          ; fsub st(i),st(0)
            mov     edx,offset fsub_text
        .ELSEIF (al == 0f0h)
          ; fdivrp st(i),st(0)
            mov     edx,offset fsubrp_text
            mov     ecx,6
        .ELSEIF (al == 0f8h)
          ; fdivp st(i),st(0)
            mov     edx,offset fdivp_text
            mov     ecx,5
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
            mov     edx,offset fiadd_text
            mov     ecx,5
        .ELSEIF (al == 1)
          ; fimul int16
            mov     edx,offset fimul_text
            mov     ecx,5
        .ELSEIF (al == 2)
          ; ficom int16
            mov     edx,offset ficom_text
            mov     ecx,5
        .ELSEIF (al == 3)
          ; fisub int16
            mov     edx,offset fisub_text
            mov     ecx,5
        .ELSEIF (al == 4)
          ; fisub int16
            mov     edx,offset fisub_text
            mov     ecx,5
        .ELSEIF (al == 5)
          ; fisubr int16
            mov     edx,offset fisubr_text
            mov     ecx,6
        .ELSEIF (al == 6)
          ; fidiv int16
            mov     edx,offset fidiv_text
            mov     ecx,5
        .ELSEIF (al == 7)
          ; fidivr int16
            mov     edx,offset fidivr_text
            mov     ecx,6
        .ELSE
          ; Invalid opcode
            jmp     unknown_instruction
        .ENDIF
    .ELSEIF (al == 0dfh)
        .IF (ah == 0e0h)
          ; fstsw ax
            mov     edx,offset fstsw_text
            mov     ecx,5
            jmp     show_instruction
        .ENDIF
        mov     al,ah
        shr     al,3
        and     al,0111b
        .IF (al == 0)
          ; fild int16
            mov     edx,offset fild_text
        .ELSEIF (al == 2)
          ; fist int16
            mov     edx,offset fist_text
        .ELSEIF (al == 3)
          ; fistp int16
            mov     edx,offset fistp_text
            mov     ecx,5
        .ELSEIF (al == 4)
          ; fbld bcd80
            mov     edx,offset fbld_text
        .ELSEIF (al == 5)
          ; fild int64
            mov     edx,offset fild_text
        .ELSEIF (al == 6)
          ; fbstp bcd80
            mov     edx,offset fbstp_text
            mov     ecx,5
        .ELSEIF (al == 7)
          ; fistp int64
            mov     edx,offset fistp_text
            mov     ecx,5
        .ELSE
          ; Invalid opcode
            jmp     unknown_instruction
        .ENDIF
    .ELSE
      ; It's an unknown instruction
      unknown_instruction:
        mov     edx,offset unknown_text
        mov     ecx,3
        mov     ebx,1
    .ENDIF
    call    display_instruction

  done_disasm:
    mov     byte ptr es:[edi],0                                     ; Null terminate the generated disassembly
    inc     edi
    mov     ecx,edi
    pop     es
    pop     ds
    pop     edi
    sub     ecx,edi                                                 ; This shows how many bytes there are in the disassembly string
    pop     edx
    pop     ebx
    pop     eax
    leave
    ret
debi_generate_disassembly   ENDP


display_instruction     PROC
    push    eax
    xor     eax,eax
    call    display_instruction_base
    pop     eax
    ret
display_instruction     ENDP


display_instruction_shifted     PROC
display_instruction_shifted     ENDP
display_instruction_base        PROC
; Upon entry:  ds:[esi] - far pointer to instruction stream
;              es:[edi] - where to store to
;              fs:[edx] - far pointer to instruction name
;                    bx - length of instruction
;                    al - # of bytes to shift left for display of the text
;                    ah - # of bytes to shift right for display of the instruction bytes
  ; Display the instruction
    push    eax
    push    ecx
    push    edx

;; Write the instruction address
    pushad
    mov     edx,esi
    call    show_register_32
    popad

;; Write the instruction name
    push    edi
    add     edi,12
    call    write_screen_fs_edx
    pop     edi                                                     ; Restore the location of the start of the bytes
    add     edi,20                                                  ; Point to the location for the parameters

    pop     edx
    pop     ecx
    pop     eax
    add     esi,ebx                                                 ; Move past this instruction to the start of any
                                                                    ;   parameters, etc
    ret
display_instruction_base        ENDP


display_instruction_additional_bytes    PROC
; This routine does not do anything in the Debi version of this algorithm
    add     esi,ecx
    ret
display_instruction_additional_bytes    ENDP


write_screen_fs_edx     PROC
  @@:
    mov     al,byte ptr fs:[edx]
    inc     edx
    stosb
    loop    @B
    ret
write_screen_fs_edx     ENDP


display_register_name_accumulator   PROC
    push    ecx
    push    edx
    mov     cx,2
    .IF (fs:byte_word_size == 0)
      ; It's an 8-bit operand
        mov     edx,offset al_register
    .ELSE
        .IF (fs:op_size_override == 0)
          ; This is 16-bit
            mov     edx,offset ax_register
        .ELSE
          ; This is 32-bit
            mov     ecx,3
            mov     edx,offset eax_register
        .ENDIF
    .ENDIF
    call    write_screen_fs_edx
    pop     edx
    pop     ecx
    ret
display_register_name_accumulator   ENDP


display_register_name_sreg      PROC
    push    ecx
    push    edx
    xor     edx,edx
    mov     ecx,2
    .IF (al == 000b)
        mov     edx,offset es_register
    .ELSEIF (al == 001b)
        mov     edx,offset cs_register
    .ELSEIF (al == 010b)
        mov     edx,offset ss_register
    .ELSEIF (al == 011b)
        mov     edx,offset ds_register
    .ELSEIF (al == 100b)
        mov     edx,offset fs_register
    .ELSEIF (al == 101b)
        mov     edx,offset gs_register
    .ELSE
        mov     edx,offset illegal_register
    .ENDIF
    call    write_screen_fs_edx
    pop     edx
    pop     ecx
    ret
display_register_name_sreg      ENDP


display_segment_override    PROC
    push    eax
    push    ecx
    push    edx
    xor     edx,edx
    mov     ecx,2
    mov     al,fs:seg_override
    .IF (al == 1)
        mov     edx,offset cs_register
    .ELSEIF (al == 2)
        mov     edx,offset ds_register
    .ELSEIF (al == 3)
        mov     edx,offset es_register
    .ELSEIF (al == 4)
        mov     edx,offset ss_register
    .ELSEIF (al == 5)
        mov     edx,offset fs_register
    .ELSEIF (al == 6)
        mov     edx,offset gs_register
    .ELSE
        jmp     dso_done
    .ENDIF
    call    write_screen_fs_edx
    call    display_colon
  dso_done:
    pop     edx
    pop     ecx
    pop     eax
    ret
display_segment_override    ENDP


display_register_name_32    PROC
    push    ecx
    push    edx
    xor     edx,edx
    mov     ecx,3
    .IF (al == 000b)
        mov     edx,offset eax_register
    .ELSEIF (al == 001b)
        mov     edx,offset ecx_register
    .ELSEIF (al == 010b)
        mov     edx,offset edx_register
    .ELSEIF (al == 011b)
        mov     edx,offset ebx_register
    .ELSEIF (al == 100b)
        mov     edx,offset esp_register
    .ELSEIF (al == 101b)
        mov     edx,offset ebp_register
    .ELSEIF (al == 110b)
        mov     edx,offset esi_register
    .ELSE
        mov     edx,offset edi_register
    .ENDIF
    call    write_screen_fs_edx
    pop     edx
    pop     ecx
    ret
display_register_name_32    ENDP


display_register_name_special_reg       PROC
    push    eax
    push    ecx
    push    edx
    xor     edx,edx
    mov     ecx,3
    mov     ah,fs:special_reg
    .IF (ah == 0)
      ; Control registers
        .IF (al == 000b)
            mov     edx,offset cr0_register
        .ELSEIF (al == 001b)
            mov     edx,offset cr1_register
        .ELSEIF (al == 010b)
            mov     edx,offset cr2_register
        .ELSEIF (al == 011b)
            mov     edx,offset cr3_register
        .ELSEIF (al == 100b)
            mov     edx,offset cr4_register
        .ELSEIF (al == 101b)
            mov     edx,offset cr5_register
        .ELSEIF (al == 110b)
            mov     edx,offset cr6_register
        .ELSE
            mov     edx,offset cr7_register
        .ENDIF
    .ELSEIF (ah == 1)
      ; Debug resgisters
        .IF (al == 000b)
            mov     edx,offset dr0_register
        .ELSEIF (al == 001b)
            mov     edx,offset dr1_register
        .ELSEIF (al == 010b)
            mov     edx,offset dr2_register
        .ELSEIF (al == 011b)
            mov     edx,offset dr3_register
        .ELSEIF (al == 100b)
            mov     edx,offset dr4_register
        .ELSEIF (al == 101b)
            mov     edx,offset dr5_register
        .ELSEIF (al == 110b)
            mov     edx,offset dr6_register
        .ELSE
            mov     edx,offset dr7_register
        .ENDIF
    .ELSE
      ; Test registers
        .IF (al == 000b)
            mov     edx,offset tr0_register
        .ELSEIF (al == 001b)
            mov     edx,offset tr1_register
        .ELSEIF (al == 010b)
            mov     edx,offset tr2_register
        .ELSEIF (al == 011b)
            mov     edx,offset tr3_register
        .ELSEIF (al == 100b)
            mov     edx,offset tr4_register
        .ELSEIF (al == 101b)
            mov     edx,offset tr5_register
        .ELSEIF (al == 110b)
            mov     edx,offset tr6_register
        .ELSE
            mov     edx,offset tr7_register
        .ENDIF
    .ENDIF
    call    write_screen_fs_edx
    pop     edx
    pop     ecx
    pop     eax
    ret
display_register_name_special_reg       ENDP


display_register_name_16    PROC
    push    ecx
    push    edx
    xor     edx,edx
    mov     ecx,2
    .IF (al == 000b)
        mov     edx,offset ax_register
    .ELSEIF (al == 001b)
        mov     edx,offset cx_register
    .ELSEIF (al == 010b)
        mov     edx,offset dx_register
    .ELSEIF (al == 011b)
        mov     edx,offset bx_register
    .ELSEIF (al == 100b)
        mov     edx,offset sp_register
    .ELSEIF (al == 101b)
        mov     edx,offset bp_register
    .ELSEIF (al == 110b)
        mov     edx,offset si_register
    .ELSE
        mov     edx,offset di_register
    .ENDIF
    call    write_screen_fs_edx
    pop     edx
    pop     ecx
    ret
display_register_name_16    ENDP


display_register_name_8     PROC
    push    ecx
    push    edx
    xor     edx,edx
    mov     ecx,2
    .IF (al == 000b)
        mov     edx,offset al_register
    .ELSEIF (al == 001b)
        mov     edx,offset cl_register
    .ELSEIF (al == 010b)
        mov     edx,offset dl_register
    .ELSEIF (al == 011b)
        mov     edx,offset bl_register
    .ELSEIF (al == 100b)
        mov     edx,offset ah_register
    .ELSEIF (al == 101b)
        mov     edx,offset ch_register
    .ELSEIF (al == 110b)
        mov     edx,offset dh_register
    .ELSE
        mov     edx,offset bh_register
    .ENDIF
    call    write_screen_fs_edx
    pop     edx
    pop     ecx
    ret
display_register_name_8     ENDP


display_register_name_indirect_adr_size_override    PROC
    push    ecx
    push    edx
    .IF (fs:adr_size_override == 0)
      ; We're in 16-bit addressing mode
        xor     edx,edx
        mov     ecx,5
        .IF (al == 000b)
            mov     edx,offset bx_si_register
        .ELSEIF (al == 001b)
            mov     edx,offset bx_di_register
        .ELSEIF (al == 010b)
            mov     edx,offset bp_si_register
        .ELSEIF (al == 011b)
            mov     edx,offset bp_di_register
        .ELSE
            mov     ecx,2
            .IF (al == 100b)
                mov     edx,offset si_register
            .ELSEIF (al == 101b)
                mov     edx,offset di_register
            .ELSEIF (al == 110b)
                mov     edx,offset bp_register
            .ELSE
                mov     edx,offset bx_register
            .ENDIF
        .ENDIF
    .ELSE
      ; We're in 32-bit addressing mode
        xor     edx,edx
        mov     ecx,3
        .IF (al == 000b)
            mov     edx,offset eax_register
        .ELSEIF (al == 001b)
            mov     edx,offset ecx_register
        .ELSEIF (al == 010b)
            mov     edx,offset edx_register
        .ELSEIF (al == 011b)
            mov     edx,offset ebx_register
;        .ELSEIF (al == 100b)
;            SIB byte would be used, so this combination would never be here
        .ELSEIF (al == 101b)
            mov     edx,offset ebp_register
        .ELSEIF (al == 110b)
            mov     edx,offset esi_register
        .ELSE
            mov     edx,offset edi_register
        .ENDIF
    .ENDIF
    call    write_screen_fs_edx
    pop     edx
    pop     ecx
    ret
display_register_name_indirect_adr_size_override    ENDP


display_register_name_op_size_override      PROC
    .IF (fs:byte_word_size == 0 && fs:movxx == 0)
      ; It's an 8-bit operand
        call    display_register_name_8
    .ELSE
        .IF (fs:op_size_override == 0)
          ; This is 16-bit
            call    display_register_name_16
        .ELSE
          ; This is 32-bit
            call    display_register_name_32
        .ENDIF
    .ENDIF
    ret
display_register_name_op_size_override      ENDP


display_register_name_byte_word_size_override   PROC
    .IF (fs:byte_word_size == 0)
      ; It's an 8-bit operand
        call    display_register_name_8
    .ELSE
      ; This is 16-bit
        call    display_register_name_16
    .ENDIF
    ret
display_register_name_byte_word_size_override   ENDP


display_comma   PROC
    push    eax
    mov     al,","
    stosb
    pop     eax
    ret
display_comma   ENDP


display_one     PROC
    push    eax
    mov     al,"1"
    stosb
    pop     eax
    ret
display_one     ENDP


display_open_bracket    PROC
    push    eax
    mov     al,"["
    stosb
    pop     eax
    ret
display_open_bracket    ENDP


display_close_bracket   PROC
    push    eax
    mov     al,"]"
    stosb
    pop     eax
    ret
display_close_bracket   ENDP


display_open_parenthesis    PROC
    push    eax
    mov     al,"("
    stosb
    pop     eax
    ret
display_open_parenthesis    ENDP


display_close_parenthesis   PROC
    push    eax
    mov     al,")"
    stosb
    pop     eax
display_close_parenthesis   ENDP
    ret


display_plus_sign   PROC
    push    eax
    mov     al,"+"
    stosb
    pop     eax
    ret
display_plus_sign   ENDP


display_colon   PROC
    push    eax
    mov     al,":"
    stosb
    pop     eax
    ret
display_colon   ENDP


display_scale_2     PROC
    push    eax
    mov     al,"*"
    stosb
    mov     al,"2"
    stosb
    pop     eax
    ret
display_scale_2     ENDP


display_scale_4     PROC
    push    eax
    mov     al,"*"
    stosb
    mov     al,"4"
    stosb
    pop     eax
    ret
display_scale_4     ENDP


display_scale_8     PROC
    push    eax
    mov     al,"*"
    stosb
    mov     al,"8"
    stosb
    pop     eax
    ret
display_scale_8     ENDP


show_new_cs_eip     PROC
show_new_cs_eip     ENDP
show_new_cs_ip      PROC
; Values for cs:[eip] are actually ds & esi, distance to jump is dx
; REMEMBER, this has to be modified to accept 32-bit values
;    push    edx                                                     ; Save current offset
;    push    ds                                                      ; Pushes a 32-bit value
;    pop     edx
;    call    display_open_parenthesis
;    call    show_register_16
;    add     edi,4
;    call    display_colon
;    mov     edx,esi
;    pop     eax                                                     ; Restore and add to current value
;    add     edx,eax
;    call    show_register_16
;    add     edi,4
;    call    display_close_parenthesis
    ret
show_new_cs_ip      ENDP


show_new_cs_eip_far     PROC
show_new_cs_eip_far     ENDP
show_new_cs_ip_far      PROC
; Values for cs:[eip] are actually DS & esi, distance to jump is edx
;    call    display_open_parenthesis
;    xor     eax,eax
;    mov     ax,ds
;    shl     eax,16
;    and     esi,0ffffh
;    add     eax,esi                                                 ; Add current IP value
;    add     edx,eax                                                 ; Add to the distance to move
;    call    show_register_32_as_16_16
;    add     edi,9
;    call    display_close_parenthesis
    ret
show_new_cs_ip_far      ENDP


display_instruction_with_mod_rm     PROC
  ; Show how many bytes there are in the override prefixes
    call    adjust_for_overrides

  ; Get the mod,reg,r/m byte
    mov     al,byte ptr ds:[esi+ebx-1]
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
        .IF (ah == 100b && fs:adr_size_override != 0)
            mov     fs:mod_reg_rm_byte,al
            inc     ebx                                             ; We have to use the SIB byte
            mov     al,byte ptr ds:[esi+ebx-1]
            mov     fs:sib_byte,al
            mov     ah,fs:mod_reg_rm_byte
            shr     ah,6
            .IF (ah == 01b)
                inc     ebx
                call    display_instruction
                call    display_segment_override
                call    part1_1_disp8
            .ELSEIF (ah == 10b)
                add     ebx,4
                call    display_instruction
                call    display_segment_override
                call    part1_1_disp32
            .ELSE
                call    display_instruction
                call    display_segment_override
                call    part1_1
            .ENDIF
        .ELSEIF (fs:adr_size_override != 0)
          ; 32-bit mode
            mov     ah,al
            shr     ah,6
            .IF (ah == 10b)
              ; It's an indirect memory operand with a 32-bit displacement
                add     ebx,4
                call    display_instruction
                call    display_segment_override
                call    part1_2
            .ELSEIF (ah == 01b)
              ; It's an indirect memory operand with an 8-bit displacement
                inc     ebx
                call    display_instruction
                call    display_segment_override
                call    part1_3
            .ELSE
              ; It is 00b, which means it's either direct memory operand or a based, indexed or based & indexed operand
                mov     ah,al
                and     ah,0111b
                .IF (ah == 101b)
                  ; It's a 32-bit direct memory operand
                    add     ebx,4
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
                add     ebx,2
                call    display_instruction
                call    display_segment_override
                call    part1_6
            .ELSEIF (ah == 01b)
              ; It's an indirect memory operand with an 8-bit displacement
                inc     ebx
                call    display_instruction
                call    display_segment_override
                call    part1_7
            .ELSE
              ; It is 00b, which means it's either direct memory operand or a based, indexed or based & indexed operand
                mov     ah,al
                and     ah,0111b
                .IF (ah == 110b)
                  ; It's a direct memory operand
                    add     ebx,2
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
display_instruction_with_mod_rm     ENDP


display_instruction_with_mod_reg_rm_movxx   PROC
    mov     al,byte ptr ds:[esi+2]
    shr     al,6
    .IF (al == 11b)
      ; It's register to register
        sub     si,fs:op_size_override
        add     bx,fs:op_size_override
        call    display_instruction
        call    display_segment_override
        mov     al,byte ptr ds:[esi-1]
        mov     ah,al
        shr     al,3
        and     al,0111b
        .IF (fs:op_size_override != 0)
            call    display_register_name_32
        .ELSE
            call    display_register_name_16
        .ENDIF
        call    display_comma
        mov     al,ah
        and     al,0111b
        call    display_register_name_byte_word_size_override
    .ELSE
        mov     fs:reverse_regs,1
        mov     fs:movxx,1
        call    display_instruction_with_mod_reg_rm
        mov     fs:movxx,0
    .ENDIF
    ret
display_instruction_with_mod_reg_rm_movxx   ENDP


display_instruction_with_mod_reg_rm     PROC
  ; Show how many bytes there are in the override prefixes
    call    adjust_for_overrides

  ; Get the mod,reg,r/m byte
    mov     al,byte ptr ds:[esi+ebx-1]
    mov     ah,al
    shr     ah,6
    .IF (ah == 11b)
        ; It's a two-register instruction
        call    display_instruction
        .IF (fs:reverse_regs == 0)
            mov     ah,al
            and     al,0111b
            call    display_register_name_op_size_override
            call    display_comma
            mov     al,ah
            shr     al,3
            and     al,0111b
            .IF (fs:sreg_override == 1)
                call    display_register_name_sreg
            .ELSE
                call    display_register_name_op_size_override
            .ENDIF
        .ELSE
            mov     ah,al
            shr     al,3
            and     al,0111b
            .IF (fs:sreg_override == 1)
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
        .IF (ah == 100b && fs:adr_size_override != 0)
          ; We have to use the SIB byte
            mov     fs:mod_reg_rm_byte,al
            inc     ebx
            mov     al,[esi+ebx-1]
            mov     fs:sib_byte,al
            mov     ah,fs:mod_reg_rm_byte
            shr     ah,6
            .IF (fs:reverse_regs == 0)
                .IF (ah == 01b)
                    inc     ebx
                    call    display_instruction
                    call    display_segment_override
                    call    part1_1_disp8
                    call    display_comma
                    call    part2_1
                .ELSEIF (ah == 10b)
                    add     ebx,4
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
                    inc     ebx
                    call    display_instruction
                    call    part2_1
                    call    display_comma
                    call    display_segment_override
                    call    part1_1_disp8
                .ELSEIF (ah == 10b)
                    add     ebx,4
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
        .ELSEIF (fs:adr_size_override != 0)
          ; 32-bit mode
            mov     ah,al
            shr     ah,6
            .IF (ah == 10b)
              ; It's an indirect memory operand with a 32-bit displacement
                add     ebx,4
                call    display_instruction
                mov     ah,al
                .IF (fs:reverse_regs == 0)
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
                inc     ebx
                call    display_instruction
                mov     ah,al
                .IF (fs:reverse_regs == 0)
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
                    add     ebx,4
                    call    display_instruction
                    mov     ah,al
                    .IF (fs:reverse_regs == 0)
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
                    .IF (fs:reverse_regs == 0)
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
                add     ebx,2
                call    display_instruction
                mov     ah,al
                .IF (fs:reverse_regs == 0)
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
                inc     ebx
                call    display_instruction
                mov     ah,al
                .IF (fs:reverse_regs == 0)
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
                    add     ebx,2
                    call    display_instruction
                    mov     ah,al
                    .IF (fs:reverse_regs == 0)
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
                    .IF (fs:reverse_regs == 0)
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
display_instruction_with_mod_reg_rm     ENDP


adjust_for_overrides    PROC
    .IF (fs:seg_override != 0)
        dec     esi
        inc     ebx
    .ENDIF

;    sub     si,fs:adr_size_override
;    add     bx,fs:adr_size_override
;
;    sub     si,fs:op_size_override
;    add     bx,fs:op_size_override
    ret
adjust_for_overrides    ENDP


part1_1     PROC
    call    part1_1_base
    call    display_close_bracket
    ret
part1_1     ENDP

part1_1_disp8   PROC
    call    part1_1_base
    mov     dl,byte ptr ds:[esi-1]
    call    show_register_8_signed
    add     edi,3
    call    display_close_bracket
    ret
part1_1_disp8   ENDP

part1_1_disp32      PROC
    call    part1_1_base
    mov     edx,dword ptr ds:[esi-4]
    call    show_register_32_signed
    add     edi,9
    call    display_close_bracket
    ret
part1_1_disp32      ENDP

part1_1_base    PROC
    mov     al,fs:sib_byte
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
            mov     al,fs:sib_byte
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
            mov     ah,fs:sib_byte
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
            mov     al,fs:sib_byte
            and     al,111b
            call    display_register_name_32
        .ENDIF
    .ENDIF
    ret
part1_1_base    ENDP

part2_1     PROC
    mov     al,fs:mod_reg_rm_byte
    shr     al,3
    and     al,111b
    .IF (fs:sreg_override == 1)
        call    display_register_name_sreg
    .ELSE
        call    display_register_name_op_size_override
    .ENDIF
    ret
part2_1     ENDP

part1_2     PROC
    and     al,0111b
    call    display_open_bracket
    call    display_register_name_indirect_adr_size_override
    mov     edx,dword ptr ds:[esi-4]
    call    show_register_32_signed
    add     edi,9
    call    display_close_bracket
    ret
part1_2     ENDP

part2_2     PROC
    shr     al,3
    and     al,0111b
    .IF (fs:sreg_override == 1)
        call    display_register_name_sreg
    .ELSE
        call    display_register_name_op_size_override
    .ENDIF
    ret
part2_2     ENDP

part1_3     PROC
    and     al,0111b
    call    display_open_bracket
    call    display_register_name_indirect_adr_size_override
    mov     dl,byte ptr ds:[esi-1]
    call    show_register_8_signed
    add     edi,3
    call    display_close_bracket
    ret
part1_3     ENDP

part2_3     PROC
    shr     al,3
    and     al,0111b
    .IF (fs:sreg_override == 1)
        call    display_register_name_sreg
    .ELSE
        call    display_register_name_op_size_override
    .ENDIF
    ret
part2_3     ENDP

part1_4     PROC
    and     al,0111b
    call    display_open_bracket
    mov     edx,dword ptr ds:[esi-4]
    call    show_register_32
    add     edi,8
    call    display_close_bracket
    ret
part1_4     ENDP

part2_4     PROC
    shr     al,3
    and     al,0111b
    .IF (fs:sreg_override == 1)
        call    display_register_name_sreg
    .ELSE
        call    display_register_name_op_size_override
    .ENDIF
    ret
part2_4     ENDP

part1_5     PROC
    and     al,0111b
    call    display_open_bracket
    call    display_register_name_indirect_adr_size_override
    call    display_close_bracket
    ret
part1_5     ENDP

part2_5     PROC
    shr     al,3
    and     al,0111b
    .IF (fs:sreg_override == 1)
        call    display_register_name_sreg
    .ELSE
        call    display_register_name_op_size_override
    .ENDIF
    ret
part2_5     ENDP

part1_6     PROC
    and     al,0111b
    call    display_open_bracket
    call    display_register_name_indirect_adr_size_override
    mov     dx,word ptr ds:[esi-2]
    call    show_register_16_signed
    add     edi,5
    call    display_close_bracket
    ret
part1_6     ENDP

part2_6     PROC
    shr     al,3
    and     al,0111b
    .IF (fs:sreg_override == 1)
        call    display_register_name_sreg
    .ELSE
        call    display_register_name_op_size_override
    .ENDIF
    ret
part2_6     ENDP

part1_7     PROC
    and     al,0111b
    call    display_open_bracket
    call    display_register_name_indirect_adr_size_override
    mov     dl,byte ptr ds:[esi-1]
    call    show_register_8_signed
    add     edi,3
    call    display_close_bracket
    ret
part1_7     ENDP

part2_7     PROC
    shr     al,3
    and     al,0111b
    .IF (fs:sreg_override == 1)
        call    display_register_name_sreg
    .ELSE
        call    display_register_name_op_size_override
    .ENDIF
    ret
part2_7     ENDP

part1_8     PROC
    and     al,0111b
    call    display_open_bracket
    mov     dx,word ptr ds:[esi-2]
    call    show_register_16
    add     edi,4
    call    display_close_bracket
    ret
part1_8     ENDP

part2_8     PROC
    shr     al,3
    and     al,0111b
    .IF (fs:sreg_override == 1)
        call    display_register_name_sreg
    .ELSE
        call    display_register_name_op_size_override
    .ENDIF
    ret
part2_8     ENDP

part1_9     PROC
    and     al,0111b
    call    display_open_bracket
    call    display_register_name_indirect_adr_size_override
    call    display_close_bracket
    ret
part1_9     ENDP

part2_9     PROC
    shr     al,3
    and     al,0111b
    .IF (fs:sreg_override == 1)
        call    display_register_name_sreg
    .ELSE
        call    display_register_name_op_size_override
    .ENDIF
    ret
part2_9     ENDP


;-----------------------------------------------
show_register_32    PROC
    push    edi
    mov     ecx,8
  again_1:
    rol     edx,4
    mov     al,dl
    and     al,0fh
    cmp     al,9
    ja      show_letter_1
    add     al,"0"
    jmp     store_value_1
  show_letter_1:
    add     al,"a"-10
  store_value_1:
    stosb
    loop    again_1
    pop     edi
    ret
show_register_32    ENDP


;-----------------------------------------------
show_register_16    PROC
    push    edi
    mov     ecx,4
  again_2:
    rol     dx,4
    mov     al,dl
    and     al,0fh
    cmp     al,9
    ja      show_letter_2
    add     al,"0"
    jmp     store_value_2
  show_letter_2:
    add     al,"a"-10
  store_value_2:
    stosb
    loop    again_2
    pop     edi
    ret
show_register_16    ENDP


;-----------------------------------------------
show_register_8     PROC
    push    edi
    mov     ecx,2
  again_3:
    rol     dl,4
    mov     al,dl
    and     al,0fh
    cmp     al,9
    ja      show_letter_3
    add     al,"0"
    jmp     store_value_3
  show_letter_3:
    add     al,"a"-10
  store_value_3:
    stosb
    loop    again_3
    pop     edi
    ret
show_register_8     ENDP


;-----------------------------------------------
show_register_16_binary     PROC
    push    edi
    mov     ecx,16
  again_5:
    rcl     dx,1
    jc      show_one
    mov     al,"0"
    jmp     store_value_5
  show_one:
    mov     al,"1"
  store_value_5:
    stosb
    loop    again_5
    pop     edi
    ret
show_register_16_binary     ENDP


;-----------------------------------------------
show_register_20    PROC
    push    edi
    mov     ecx,5
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
    add     al,"a"-10
  store_value_7:
    stosb
    loop    again_7
    pop     edi
    ret
show_register_20    ENDP


;-----------------------------------------------
show_register_32_as_16_16   PROC
    push    edi
  @@:
  ; Display the first 4 nibbles
    mov     ecx,4
  again_9:
    rol     edx,4
    mov     al,dl
    and     al,0fh
    cmp     al,9
    ja      show_letter_9
    add     al,"0"
    jmp     store_value_9
  show_letter_9:
    add     al,"a"-10
  store_value_9:
    stosb
    loop    again_9

  ; Display the colon
    mov     al,":"
    stosb

  ; Display the next 4 nibbles
    mov     ecx,4
  again_10:
    rol     edx,4
    mov     al,dl
    and     al,0fh
    cmp     al,9
    ja      show_letter_10
    add     al,"0"
    jmp     store_value_10
  show_letter_10:
    add     al,"a"-10
  store_value_10:
    stosb
    loop    again_10
    pop     edi
    ret
show_register_32_as_16_16   ENDP


;-----------------------------------------------
show_register_8_signed      PROC
    push    edi
    .IF (dl > 80h)
        mov     al,"-"
        neg     dl
    .ELSE
        mov     al,"+"
    .ENDIF
    stosb
    mov     ecx,2
  again_11:
    rol     dl,4
    mov     al,dl
    and     al,0fh
    cmp     al,9
    ja      show_letter_11
    add     al,"0"
    jmp     store_value_11
  show_letter_11:
    add     al,"a"-10
  store_value_11:
    stosb
    loop    again_11
    pop     edi
    ret
show_register_8_signed      ENDP


;-----------------------------------------------
show_register_16_signed     PROC
    push    edi
    .IF (dx > 8000h)
        mov     al,"-"
        neg     dx
    .ELSE
        mov     al,"+"
    .ENDIF
    stosb
    mov     ecx,4
  again_12:
    rol     dx,4
    mov     al,dl
    and     al,0fh
    cmp     al,9
    ja      show_letter_12
    add     al,"0"
    jmp     store_value_12
  show_letter_12:
    add     al,"a"-10
  store_value_12:
    stosb
    loop    again_12
    pop     edi
    ret
show_register_16_signed     ENDP


;-----------------------------------------------
show_register_32_signed     PROC
    push    edi
    .IF (edx > 80000000h)
        mov     al,"-"
        neg     edx
    .ELSE
        mov     al,"+"
    .ENDIF
    stosb
    mov     ecx,8
  again_13:
    rol     edx,4
    mov     al,dl
    and     al,0fh
    cmp     al,9
    ja      show_letter_13
    add     al,"0"
    jmp     store_value_13
  show_letter_13:
    add     al,"a"-10
  store_value_13:
    stosb
    loop    again_13
    pop     edi
    ret
show_register_32_signed     ENDP