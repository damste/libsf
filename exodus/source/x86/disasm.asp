; disasm.asp
;
; x86 disassembly algorithms
;
;  Functions:
;     � x86_disassemble                             ; Disassembles an instruction at ds:[esi]
;     � x86_simplify_disassembly                    ; Simplifies the disassembly listing
;
;  Shortcuts:
;     � STORE_THE_INSTRUCTION
;




; Data and macros
INCLUDE dis_data.asp


x86_disassemble:
; This routine is used to disassemble an instruction
;
; Upon entry:   ds:[esi] - far ptr to instruction bytes (code)
;               es:[edi] - where to store instruction decoding format
;                          * Refer to x86\inf\disasm.inf for information on the disassembly format
; Upon exit:    string at es:[edi] is updated
;               ecx - total number of bytes in this instruction
;               no other registers or flags affected
;
    xor     ecx,ecx                                                 ; Initialize the count to zero at the start
  ; [ebp+40] - eax
  ; [ebp+36] - ecx
  ; [ebp+32] - edx
  ; [ebp+28] - ebx
  ; [ebp+24] - esp
  ; [ebp+20] - ebp
  ; [ebp+16] - esi
  ; [ebp+12] - edi
  ; [ebp+08] - eflags
  ; [ebp+04] - fs
  ; [ebp+00] - bogus ebp (do not update)
    pushad
    pushfd
    push    fs
    enter   0,0

    mov     fs,cs:data_segment
    mov     fs:cpu_mode,0
    mov     fs:prefix_bytes,0
    mov     fs:sreg_override,0
    mov     fs:sign_extend,0
    mov     fs:reverse_regs,0
    mov     fs:special_reg,0
    mov     fs:sib_byte,0
    mov     fs:byte_word_size,0
    mov     fs:seg_override,0
    mov     fs:op_size_override,0
    mov     fs:adr_size_override,0
    mov     fs:reverse_mod_reg_rm,0
    mov     fs:scale_factor,0
    mov     fs:movxx_register,0
    mov     fs:first_gp_register,0
    mov     fs:second_gp_register,0
    mov     fs:display_second_register,1
    mov     fs:special_control,0
    mov     fs:gp_reg_count,0

    mov     fs:instruction_offset,0
    mov     fs:instruction_bytes,0
    mov     fs:instruction_text_length,0
    mov     fs:instruction_text_offset,0
    mov     fs:parameters_text_length,0
    mov     fs:parameters_text_offset,offset temp_buffer
    mov     fs:displacement_offset,0
    mov     fs:displacement_bytes,0
    mov     fs:displacement_data,0
    mov     fs:mod_reg_rm_bytes,0
    mov     fs:mod_reg_rm_offset,0
    mov     fs:sib_bytes,0
    mov     fs:sib_offset,0
    mov     fs:immediate_offset,0
    mov     fs:immediate_bytes,0
    mov     fs:immediate_data,0
    mov     fs:operand_size,0

  next_byte:
    mov     fs:instruction_offset,esi
    mov     eax,dword ptr ds:[esi]
    movzx   ecx,al
    movzx   ebx,word ptr fs:[ecx*2 + offset opcode_map]
    jmp     ebx

  _two_byte_instruction:
    mov     eax,dword ptr ds:[esi+1]
    movzx   ecx,al
    movzx   ebx,word ptr fs:[ecx*2 + offset two_byte_opcode_map]
    jmp     ebx


;; OVERRIDES
  _op_size_override:
  ; 32/16-bit register override
    inc     fs:op_size_override
  process_override_byte:
    inc     fs:prefix_bytes
    inc     esi
    jmp     next_byte

  _adr_size_override:
  ; 32/16-bit memory override
    inc     fs:adr_size_override
    jmp     process_override_byte

  _cs_override:
  ; cs segment override
    mov     fs:seg_override,1
    jmp     process_override_byte

  _ds_override:
  ; ds segment override
    mov     fs:seg_override,2
    jmp     process_override_byte

  _es_override:
  ; es segment override
    mov     fs:seg_override,3
    jmp     process_override_byte

  _ss_override:
  ; SS segment override
    mov     fs:seg_override,4
    jmp     process_override_byte

  _fs_override:
  ; FS segment override
    mov     fs:seg_override,5
    jmp     process_override_byte

  _gs_override:
  ; GS segment override
    mov     fs:seg_override,6
    jmp     process_override_byte



;; INSTRUCTIONS
  _aaa:
    @instr_bytes    1
    @instr_text     aaa_text, 3
    jmp     store_instruction

  _aad:
    @instr_bytes    2
    @instr_text     aad_text, 3
    jmp     store_instruction

  _aam:
    @instr_bytes    2
    @instr_text     aam_text, 3
    jmp     store_instruction

  _aas:
    @instr_bytes    1
    @instr_text     aas_text, 3
    jmp     store_instruction

  _adc_immed8:
    @instr_bytes    1
    @instr_text     adc_text, 3
  _al_w_immed8_common:
    call    start_offsets
    mov     fs:operand_size,8
    xor     ebx,ebx
    call    store_gp_register
    call    store_comma
    call    store_8_bit_signed_value
    call    end_offsets
    jmp     store_instruction

  _adc_immed16_32:
    @instr_bytes    1
    @instr_text     adc_text, 3
  _xax_w_immed16_32_common:
    call    start_offsets
    call    determine_standard_operand_size
    xor     ebx,ebx
    call    store_gp_register
    call    store_comma
    call    store_signed_value
    call    end_offsets
    jmp     store_instruction

  _adc_rm_immed8:
    @instr_bytes    1
    @instr_text     adc_text, 3
  _xxx_rm_immed8:
    mov     fs:operand_size,8
    call    extract_mod_rm
    call    store_comma
    call    store_8_bit_signed_value
    jmp     store_instruction

  _adc_rm_immed16_32:
    @instr_bytes    1
    @instr_text     adc_text, 3
  _xxx_rm_immed16_32:
    call    determine_standard_operand_size
    call    extract_mod_rm
    call    store_comma
    call    store_signed_value
    jmp     store_instruction

  _adc_rm_16_32_with_immed8:
    @instr_bytes    1
    @instr_text     adc_text, 3
  _xxx_rm_16_32_with_immed8:
    call    determine_standard_operand_size
    call    start_offsets
    call    extract_mod_rm
    call    store_comma
    call    store_8_bit_signed_value
    call    end_offsets
    jmp     store_instruction

  _adc:
    @instr_bytes    1
    @instr_text     adc_text, 3
  _dw_mod_reg_rm_common:
  ; This label is used when the last two digits of the one-byte instruction are dw and a mod/reg/rm byte follows
    movzx   edx,al
    and     edx,10b
    mov     fs:reverse_mod_reg_rm,edx
    and     eax,1b
    push    eax
    call    determine_operand_size
    call    extract_mod_reg_rm
    jmp     store_instruction

  _add_immed8:
    @instr_bytes    1
    @instr_text     add_text, 3
    jmp     _al_w_immed8_common

  _add_immed16_32:
    @instr_bytes    1
    @instr_text     add_text, 3
    jmp     _xax_w_immed16_32_common

  _add_rm_immed8:
    @instr_bytes    1
    @instr_text     add_text, 3
    jmp     _xxx_rm_immed8

  _add_rm_immed16_32:
    @instr_bytes    1
    @instr_text     add_text, 3
    jmp     _xxx_rm_immed16_32

  _add_rm_16_32_with_immed8:
    @instr_bytes    1
    @instr_text     add_text, 3
    jmp     _xxx_rm_16_32_with_immed8

  _add:
    @instr_bytes    1
    @instr_text     add_text, 3
    jmp     _dw_mod_reg_rm_common

  _and:
    @instr_bytes    1
    @instr_text     and_text, 3
    jmp     _dw_mod_reg_rm_common

  _and_immed8:
    @instr_bytes    1
    @instr_text     and_text, 3
    jmp     _al_w_immed8_common

  _and_immed16_32:
    @instr_bytes    1
    @instr_text     and_text, 3
    jmp     _xax_w_immed16_32_common

  _and_rm_immed8:
    @instr_bytes    1
    @instr_text     and_text, 3
    jmp     _xxx_rm_immed8

  _and_rm_immed16_32:
    @instr_bytes    1
    @instr_text     and_text, 3
    jmp     _xxx_rm_immed16_32

  _and_rm_16_32_with_immed8:
    @instr_bytes    1
    @instr_text     and_text, 3
    jmp     _xxx_rm_16_32_with_immed8

  _arpl:
    @instr_bytes    1
    @instr_text     arpl_text, 4
    mov     fs:operand_size,16
    call    extract_mod_reg_rm
    jmp     store_instruction

  _bound:
    @instr_bytes    1
    @instr_text     bound_text, 5
    call    determine_standard_operand_size
    mov     fs:reverse_mod_reg_rm,1
    call    extract_mod_reg_rm
    jmp     store_instruction

  _bsf:
    @instr_bytes    2
    @instr_text     bsf_text, 3
    mov     fs:reverse_mod_reg_rm,1
    call    extract_mod_reg_rm
    jmp     store_instruction

  _bsr:
    @instr_bytes    2
    @instr_text     bsr_text, 3
    mov     fs:reverse_mod_reg_rm,1
    call    extract_mod_reg_rm
    jmp     store_instruction

  _bswap_eax:
  _bswap_ebp:
  _bswap_ebx:
  _bswap_ecx:
  _bswap_edi:
  _bswap_edx:
  _bswap_esi:
  _bswap_esp:
    mov     bl,byte ptr ds:[esi]
    @instr_bytes    2
    @instr_text     bswap_text, 5
    call    start_offsets
    and     al,111b
    mov     bl,al
    mov     fs:operand_size,32
    call    store_gp_register
    call    end_offsets
    jmp     store_instruction

  _bt:
    @instr_bytes    2
    @instr_text     bt_text, 2
    call    extract_mod_reg_rm
    jmp     store_instruction

  _bt_immed8:
    @instr_bytes    2
    @instr_text     bt_text, 2
    jmp     _xxx_rm_16_32_with_immed8

  _btc:
    @instr_bytes    2
    @instr_text     btc_text, 3
    call    extract_mod_reg_rm
    jmp     store_instruction

  _btc_immed8:
    @instr_bytes    2
    @instr_text     btc_text, 3
    jmp     _xxx_rm_16_32_with_immed8

  _btr:
    @instr_bytes    2
    @instr_text     btr_text, 3
    call    extract_mod_reg_rm
    jmp     store_instruction

  _btr_immed8:
    @instr_bytes    2
    @instr_text     btr_text, 3
    jmp     _xxx_rm_16_32_with_immed8

  _bts:
    @instr_bytes    1
    @instr_text     bts_text, 3
    call    extract_mod_reg_rm
    jmp     store_instruction

  _bts_immed8:
    @instr_bytes    2
    @instr_text     bts_text, 3
    jmp     _xxx_rm_16_32_with_immed8

  _call_near_relative:
    @instr_bytes    1
    @instr_text     call_text, 4
    call    start_offsets
    call    determine_standard_operand_size
    call    store_signed_value
    call    end_offsets
    jmp     store_instruction

  _call_rm:
    @instr_bytes    1
    @instr_text     call_text, 4
    call    extract_mod_rm
    jmp     store_instruction

  _call_far_rm:
  ; This is a far call with the operand specified in a mod/rm byte
    @instr_bytes    1
    @instr_text     call_text, 4
    call    extract_mod_rm
    jmp     store_instruction

  _call_far_operand:
  ; This is a far call with the operand specified in the instruction
    @instr_bytes    1
    @instr_text     call_text, 4
    call    start_offsets
    call    store_16_bit_value
    call    store_colon
    call    store_value
    call    end_offsets
    jmp     store_instruction

  _cbw:
    @instr_bytes    1
    .IF ((fs:cpu_mode == 0 && fs:op_size_override != 0) || (fs:cpu_mode != 0 && fs:op_size_override == 0))
        @instr_text     cbw_text, 3
    .ELSE
        @instr_text     cwde_text, 4
    .ENDIF
    jmp     store_instruction

  _clc:
    @instr_bytes    1
    @instr_text     clc_text, 3
    jmp     store_instruction

  _cld:
    @instr_bytes    1
    @instr_text     cld_text, 3
    jmp     store_instruction

  _cli:
    @instr_bytes    1
    @instr_text     cli_text, 3
    jmp     store_instruction

  _clts:
    @instr_bytes    2
    @instr_text     clts_text, 4
    jmp     store_instruction

  _cmc:
    @instr_bytes    1
    @instr_text     cmc_text, 3
    jmp     store_instruction

  _cmovo:
    @instr_bytes    2
    @instr_text     cmovo_text, 5
  cmovxx_common:
    mov     fs:reverse_mod_reg_rm,1
    call    determine_standard_operand_size
    call    extract_mod_reg_rm
    jmp     store_instruction

  _cmovno:
    @instr_bytes    2
    @instr_text     cmovno_text, 6
    jmp     cmovxx_common

  _cmovc:
    @instr_bytes    2
    @instr_text     cmovc_text, 5
    jmp     cmovxx_common

  _cmovnc:
    @instr_bytes    2
    @instr_text     cmovnc_text, 6
    jmp     cmovxx_common

  _cmovz:
    @instr_bytes    2
    @instr_text     cmovz_text, 5
    jmp     cmovxx_common

  _cmovnz:
    @instr_bytes    2
    @instr_text     cmovnz_text, 6
    jmp     cmovxx_common

  _cmovna:
    @instr_bytes    2
    @instr_text     cmovna_text, 6
    jmp     cmovxx_common

  _cmova:
    @instr_bytes    2
    @instr_text     cmova_text, 5
    jmp     cmovxx_common

  _cmovs:
    @instr_bytes    2
    @instr_text     cmovs_text, 5
    jmp     cmovxx_common

  _cmovns:
    @instr_bytes    2
    @instr_text     cmovns_text, 6
    jmp     cmovxx_common

  _cmovpe:
    @instr_bytes    2
    @instr_text     cmovpe_text, 6
    jmp     cmovxx_common

  _cmovpo:
    @instr_bytes    2
    @instr_text     cmovpo_text, 6
    jmp     cmovxx_common

  _cmovl:
    @instr_bytes    2
    @instr_text     cmovl_text, 5
    jmp     cmovxx_common

  _cmovnl:
    @instr_bytes    2
    @instr_text     cmovnl_text, 6
    jmp     cmovxx_common

  _cmovng:
    @instr_bytes    2
    @instr_text     cmovng_text, 6
    jmp     cmovxx_common

  _cmovg:
    @instr_bytes    2
    @instr_text     cmovg_text, 5
    jmp     cmovxx_common

  _cmp_immed8:
    @instr_bytes    1
    @instr_text     cmp_text, 3
    jmp     _al_w_immed8_common

  _cmp_immed16_32:
    @instr_bytes    1
    @instr_text     cmp_text, 3
    jmp     _xax_w_immed16_32_common

;;;;;;;;;;;;;;
  _cmp_rm8_r8:
    @instr_bytes    1
    @instr_text     cmp_text, 3
    mov     fs:operand_size,8
    call    extract_mod_reg_rm
    jmp     store_instruction

  _cmp_rm16_r16:
    @instr_bytes    1
    @instr_text     cmp_text, 3
    call    determine_standard_operand_size
    call    extract_mod_reg_rm
    jmp     store_instruction

  _cmp_r8_rm8:
    @instr_bytes    1
    @instr_text     cmp_text, 3
    mov     fs:operand_size,8
    mov     fs:reverse_mod_reg_rm,1
    call    extract_mod_reg_rm
    jmp     store_instruction

  _cmp_r16_rm16:
    @instr_bytes    1
    @instr_text     cmp_text, 3
    call    determine_standard_operand_size
    mov     fs:reverse_mod_reg_rm,1
    call    extract_mod_reg_rm
    jmp     store_instruction
;;;;;;;;;;;;;;

  _cmp_rm_immed8:
    @instr_bytes    1
    @instr_text     cmp_text, 3
    jmp     _xxx_rm_immed8

  _cmp_rm_immed16_32:
    @instr_bytes    1
    @instr_text     cmp_text, 3
    jmp     _xxx_rm_immed16_32

  _cmp_rm_16_32_with_immed8:
    @instr_bytes    1
    @instr_text     cmp_text, 3
    jmp     _xxx_rm_16_32_with_immed8

  _cmpsb:
    @instr_bytes    1
    @instr_text     cmpsb_text, 5
    jmp     store_instruction

  _cmpsw:
    @instr_bytes    1
    .IF ((fs:cpu_mode == 0 && fs:op_size_override != 0) || (fs:cpu_mode != 0 && fs:op_size_override == 0))
        @instr_text     cmpsw_text, 5
    .ELSE
        @instr_text     cmpsd_text, 5
    .ENDIF
    jmp     store_instruction

  _cmpxchg_byte:
    @instr_bytes    2
    @instr_text     cmpxchg_text, 7
    mov     fs:operand_size,8
    call    extract_mod_reg_rm
    jmp     store_instruction

  _cmpxchg:
    @instr_bytes    2
    @instr_text     cmpxchg_text, 7
    call    determine_standard_operand_size
    call    extract_mod_reg_rm
    jmp     store_instruction

  _cmpxchg8b:
    @instr_bytes    2
    @instr_text     cmpxchg8b_text, 9
    mov     fs:operand_size,64
    call    extract_mod_rm
    jmp     store_instruction

  _cpuid:
    @instr_bytes    2
    @instr_text     cpuid_text, 5
    jmp     store_instruction

  _cwd:
    @instr_bytes    1
    .IF ((fs:cpu_mode == 0 && fs:op_size_override != 0) || (fs:cpu_mode != 0 && fs:op_size_override == 0))
        @instr_text     cwd_text, 3
    .ELSE
        @instr_text     cdq_text, 3
    .ENDIF
    jmp     store_instruction

  _daa:
    @instr_bytes    1
    @instr_text     daa_text, 3
    jmp     store_instruction

  _das:
    @instr_bytes    1
    @instr_text     das_text, 3
    jmp     store_instruction

  _dec_xax:
  _dec_xbp:
  _dec_xbx:
  _dec_xcx:
  _dec_xdi:
  _dec_xdx:
  _dec_xsi:
  _dec_xsp:
    @instr_bytes    1
    @instr_text     dec_text, 3
  xnc_common1:
    call    start_offsets
    and     eax,111b
    mov     bl,al
    call    determine_standard_operand_size
    call    store_gp_register
    call    end_offsets
    jmp     store_instruction

  _dec_rm8:
    @instr_bytes    1
    @instr_text     dec_text, 3
  xnc_common2:
    mov     fs:operand_size,8
    call    extract_mod_rm
    jmp     store_instruction

  _dec_rm16_32:
    @instr_bytes    1
    @instr_text     dec_text, 3
  xnc_common3:
    call    determine_standard_operand_size
    call    extract_mod_rm
    jmp     store_instruction

  _div_byte:
    @instr_bytes    1
    @instr_text     div_text, 3
    mov     fs:operand_size,8
    call    extract_mod_rm
    jmp     store_instruction

  _div:
    @instr_bytes    1
    @instr_text     div_text, 3
    call    determine_standard_operand_size
    call    extract_mod_rm
    jmp     store_instruction

  _emms:
    @instr_bytes    2
    @instr_text     emms_text, 4
    jmp     store_instruction

  _enter:
    @instr_bytes    1
    @instr_text     enter_text, 5
    call    start_offsets
    call    store_16_bit_value
    call    store_comma
    call    store_8_bit_value
    call    end_offsets
    jmp     store_instruction

  _fpu_d8:
    mov     al,byte ptr ds:[esi+1]
    .IF (al >= 0c0h && al <= 0c7h)
      ; It's FADD st(0),st(i)
        @instr_bytes    2
        @instr_text     fadd_text, 4
      _st0_sti_common:
        call    start_offsets
        mov     fs:operand_size,80
        mov     fs:special_reg,_STx_REGS
        and     al,111b
        mov     bl,al
        push    ebx
        xor     bl,bl
        call    store_gp_register
        call    store_comma
        pop     ebx
        call    store_gp_register
        call    end_offsets
        jmp     store_instruction
    .ELSEIF (al >= 0c8h && al <= 0cfh)
      ; It's FMUL st(0),st(i)
        @instr_bytes    2
        @instr_text     fmul_text, 4
        jmp     _st0_sti_common
    .ELSEIF (al >= 0d0h && al <= 0d7h)
      ; It's FCOM st(0),st(i)
        @instr_bytes    2
        @instr_text     fcom_text, 4
        jmp     _st0_sti_common
    .ELSEIF (al >= 0d8h && al <= 0dfh)
      ; It's FCOMP st(0),st(i)
        @instr_bytes    2
        @instr_text     fcomp_text, 5
        jmp     _st0_sti_common
    .ELSEIF (al >= 0e0h && al <= 0e7h)
      ; It's FSUB st(0),st(i)
        @instr_bytes    2
        @instr_text     fsub_text, 4
        jmp     _st0_sti_common
    .ELSEIF (al >= 0e8h && al <= 0efh)
      ; It's FSUBR st(0),st(i)
        @instr_bytes    2
        @instr_text     fsubr_text, 5
        jmp     _st0_sti_common
    .ELSEIF (al >= 0f0h && al <= 0f7h)
      ; It's FDIV st(0),st(i)
        @instr_bytes    1
        @instr_text     fdiv_text, 4
        jmp     _st0_sti_common
    .ELSEIF (al >= 0f8h && al <= 0ffh)
      ; It's FDIVR st(0),st(i)
        @instr_bytes    1
        @instr_text     fdivr_text, 5
        jmp     _st0_sti_common
    .ENDIF
    shr     al,3
    and     al,111b
    .IF (al == 000b)
      ; It's FADD real4
        @instr_bytes    1
        @instr_text     fadd_text, 4
        mov     fs:operand_size,32
        call    extract_mod_rm
        jmp     store_instruction
    .ELSEIF (al == 001b)
      ; It's FMUL real4
        @instr_bytes    1
        @instr_text     fmul_text, 4
        mov     fs:operand_size,32
        call    extract_mod_rm
        jmp     store_instruction
    .ELSEIF (al == 010b)
      ; It's FCOM real4
        @instr_bytes    1
        @instr_text     fcom_text, 4
        mov     fs:operand_size,32
        call    extract_mod_rm
        jmp     store_instruction
    .ELSEIF (al == 011b)
      ; It's FCOMP real4
        @instr_bytes    1
        @instr_text     fcomp_text, 5
        mov     fs:operand_size,32
        call    extract_mod_rm
        jmp     store_instruction
    .ELSEIF (al == 100b)
      ; It's FSUB real4
        @instr_bytes    1
        @instr_text     fsub_text, 4
        mov     fs:operand_size,32
        call    extract_mod_rm
        jmp     store_instruction
    .ELSEIF (al == 101b)
      ; It's FSUBR real4
        @instr_bytes    1
        @instr_text     fsubr_text, 5
        mov     fs:operand_size,32
        call    extract_mod_rm
        jmp     store_instruction
    .ELSEIF (al == 110b)
      ; It's FDIV real4
        @instr_bytes    1
        @instr_text     fdiv_text, 4
        mov     fs:operand_size,32
        call    extract_mod_rm
        jmp     store_instruction
    .ELSEIF (al == 111b)
      ; It's FDIVR real4
        @instr_bytes    1
        @instr_text     fdivr_text, 5
        mov     fs:operand_size,32
        call    extract_mod_rm
        jmp     store_instruction
    .ENDIF
    jmp     _fpu_unused

  _fpu_d9:
    mov     al,byte ptr ds:[esi+1]
    .IF (al >= 0c0h && al <= 0c7h)
      ; It's FLD st(i)
        @instr_bytes    1
        @instr_text     fld_text, 3
        jmp     _sti_common
    .ELSEIF (al >= 0c8h && al <= 0cfh)
      ; It's FXCH st(i)
        @instr_bytes    1
        @instr_text     fxch_text, 4
        jmp     _sti_common
    .ELSEIF (al == 0d0h)
      ; fnop
        @instr_bytes    2
        @instr_text     fnop_text, 4
        jmp     store_instruction
    .ELSEIF (al == 0e0h)
      ; fchs
        @instr_bytes    2
        @instr_text     fchs_text, 4
        jmp     store_instruction
    .ELSEIF (al == 0e1h)
      ; fabs
        @instr_bytes    2
        @instr_text     fabs_text, 4
        jmp     store_instruction
    .ELSEIF (al == 0e4h)
      ; ftst
        @instr_bytes    2
        @instr_text     ftst_text, 4
        jmp     store_instruction
    .ELSEIF (al == 0e5h)
      ; fxam
        @instr_bytes    2
        @instr_text     fxam_text, 4
        jmp     store_instruction
    .ELSEIF (al == 0e8h)
      ; fld1
        @instr_bytes    2
        @instr_text     fld1_text, 4
        jmp     store_instruction
    .ELSEIF (al == 0e9h)
      ; fldl2t
        @instr_bytes    2
        @instr_text     fldl2t_text, 6
        jmp     store_instruction
    .ELSEIF (al == 0eah)
      ; fldl2e
        @instr_bytes    2
        @instr_text     fldl2e_text, 6
        jmp     store_instruction
    .ELSEIF (al == 0ebh)
      ; fldpi
        @instr_bytes    2
        @instr_text     fldpi_text, 5
        jmp     store_instruction
    .ELSEIF (al == 0ech)
      ; fldlg2
        @instr_bytes    2
        @instr_text     fldlg2_text, 6
        jmp     store_instruction
    .ELSEIF (al == 0edh)
      ; fldln2
        @instr_bytes    2
        @instr_text     fldln2_text, 6
        jmp     store_instruction
    .ELSEIF (al == 0eeh)
      ; fldz
        @instr_bytes    2
        @instr_text     fldz_text, 4
        jmp     store_instruction
    .ELSEIF (al == 0f0h)
      ; f2xm1
        @instr_bytes    2
        @instr_text     f2xm1_text, 5
        jmp     store_instruction
    .ELSEIF (al == 0f1h)
      ; fyl2x
        @instr_bytes    2
        @instr_text     fyl2x_text, 5
        jmp     store_instruction
    .ELSEIF (al == 0f2h)
      ; fptan
        @instr_bytes    2
        @instr_text     fptan_text,5
        jmp     store_instruction
    .ELSEIF (al == 0f3h)
      ; fpatan
        @instr_bytes    2
        @instr_text     fpatan_text,6
        jmp     store_instruction
    .ELSEIF (al == 0f4h)
      ; fxtract
        @instr_bytes    2
        @instr_text     fxtract_text,7
        jmp     store_instruction
    .ELSEIF (al == 0f5h)
      ; fprem1
        @instr_bytes    2
        @instr_text     fprem1_text,6
        jmp     store_instruction
    .ELSEIF (al == 0f6h)
      ; fdecstp
        @instr_bytes    2
        @instr_text     fdecstp_text,7
        jmp     store_instruction
    .ELSEIF (al == 0f7h)
      ; fincstp
        @instr_bytes    2
        @instr_text     fincstp_text,7
        jmp     store_instruction
    .ELSEIF (al == 0f8h)
      ; fprem
        @instr_bytes    2
        @instr_text     fprem_text,5
        jmp     store_instruction
    .ELSEIF (al == 0f9h)
      ; fyl2xp1
        @instr_bytes    2
        @instr_text     fyl2xp1_text,7
        jmp     store_instruction
    .ELSEIF (al == 0fah)
      ; fsqrt
        @instr_bytes    2
        @instr_text     fsqrt_text,5
        jmp     store_instruction
    .ELSEIF (al == 0fbh)
      ; fsincos
        @instr_bytes    2
        @instr_text     fsincos_text,7
        jmp     store_instruction
    .ELSEIF (al == 0fch)
      ; frndint
        @instr_bytes    2
        @instr_text     frndint_text,7
        jmp     store_instruction
    .ELSEIF (al == 0fdh)
      ; fscale
        @instr_bytes    2
        @instr_text     fscale_text,6
        jmp     store_instruction
    .ELSEIF (al == 0feh)
      ; fsin
        @instr_bytes    2
        @instr_text     fsin_text,4
        jmp     store_instruction
    .ELSEIF (al == 0ffh)
      ; fcos
        @instr_bytes    2
        @instr_text     fcos_text, 4
        jmp     store_instruction
    .ENDIF
    shr     al,3
    and     al,111b
    .IF (al == 000b)
      ; It's FLD real4
        @instr_bytes    1
        @instr_text     fld_text, 3
        mov     fs:operand_size,32
        call    extract_mod_rm
        jmp     store_instruction
    .ELSEIF (al == 010b)
      ; It's FST real4
        @instr_bytes    1
        @instr_text     fst_text, 3
        mov     fs:operand_size,32
        call    extract_mod_rm
        jmp     store_instruction
    .ELSEIF (al == 011b)
      ; It's FSTP real4
        @instr_bytes    1
        @instr_text     fstp_text, 4
        mov     fs:operand_size,32
        call    extract_mod_rm
        jmp     store_instruction
    .ELSEIF (al == 100b)
      ; It's fldenv
        @instr_bytes    1
        @instr_text     fldenv_text, 6
        .IF ((fs:cpu_mode == 0 && fs:op_size_override != 0) || (fs:cpu_mode != 0 && fs:op_size_override == 0))
            mov     fs:operand_size,14
        .ELSE
            mov     fs:operand_size,28
        .ENDIF
        call    extract_mod_rm
        jmp     store_instruction
    .ELSEIF (al == 101b)
      ; It's fldcw m16
        @instr_bytes    1
        @instr_text     fldcw_text, 5
        mov     fs:operand_size,16
        call    extract_mod_rm
        jmp     store_instruction
    .ELSEIF (al == 110b)
      ; It's fnstenv
        @instr_bytes    1
        @instr_text     fnstenv_text, 7
        .IF ((fs:cpu_mode == 0 && fs:op_size_override != 0) || (fs:cpu_mode != 0 && fs:op_size_override == 0))
            mov     fs:operand_size,14
        .ELSE
            mov     fs:operand_size,28
        .ENDIF
        call    extract_mod_rm
        jmp     store_instruction
    .ELSEIF (al == 111b)
      ; It's fnstcw m16
        @instr_bytes    1
        @instr_text     fnstcw_text, 6
        mov     fs:operand_size,16
        call    extract_mod_rm
        jmp     store_instruction
    .ENDIF
    jmp     _fpu_unused

  _fpu_da:
    mov     al,byte ptr ds:[esi+1]
    .IF (al >= 0c0h && al <= 0c7h)
      ; It's FCMOVB st0,sti
        @instr_bytes    1
        @instr_text     fcmovb_text, 6
        jmp     _st0_sti_common
    .ELSEIF (al >= 0c8h && al <= 0cfh)
      ; It's FCMOVZ st0,sti
        @instr_bytes    1
        @instr_text     fcmovz_text, 6
        jmp     _st0_sti_common
    .ELSEIF (al >= 0d0h && al <= 0d7h)
      ; It's FCMOVNG st0,sti
        @instr_bytes    1
        @instr_text     fcmovng_text, 7
        jmp     _st0_sti_common
    .ELSEIF (al >= 0d8h && al <= 0dFh)
      ; It's FCMOVPO st0,sti
        @instr_bytes    1
        @instr_text     fcmovpo_text, 7
        jmp     _st0_sti_common
    .ELSEIF (al == 0e9h)
      ; It's FUCOMPP
        @instr_bytes    1
        @instr_text     fucompp_text, 7
        jmp     store_instruction
    .ENDIF
    shr     al,3
    and     al,111b
    .IF (al == 000b)
      ; It's FIADD m32_int
        @instr_bytes    1
        @instr_text     fiadd_text, 5
        mov     fs:operand_size,32
        call    extract_mod_rm
        jmp     store_instruction
    .ELSEIF (al == 001b)
      ; It's FIMUL m32_int
        @instr_bytes    1
        @instr_text     fimul_text, 5
        mov     fs:operand_size,32
        call    extract_mod_rm
        jmp     store_instruction
    .ELSEIF (al == 010b)
      ; It's FICOM m32_int
        @instr_bytes    1
        @instr_text     ficom_text, 5
        mov     fs:operand_size,32
        call    extract_mod_rm
        jmp     store_instruction
    .ELSEIF (al == 011b)
      ; It's FICOMP m32_int
        @instr_bytes    1
        @instr_text     ficomp_text, 6
        mov     fs:operand_size,32
        call    extract_mod_rm
        jmp     store_instruction
    .ELSEIF (al == 100b)
      ; It's FISUB m32_int
        @instr_bytes    1
        @instr_text     fisub_text, 5
        mov     fs:operand_size,32
        call    extract_mod_rm
        jmp     store_instruction
    .ELSEIF (al == 101b)
      ; It's FISUBR m32_int
        @instr_bytes    1
        @instr_text     fisubr_text, 6
        mov     fs:operand_size,32
        call    extract_mod_rm
        jmp     store_instruction
    .ELSEIF (al == 110b)
      ; It's FIDIV m32_int
        @instr_bytes    1
        @instr_text     fidiv_text, 5
        mov     fs:operand_size,32
        call    extract_mod_rm
        jmp     store_instruction
    .ELSEIF (al == 111b)
      ; It's FIDIVR m32_int
        @instr_bytes    1
        @instr_text     fidivr_text, 6
        mov     fs:operand_size,32
        call    extract_mod_rm
        jmp     store_instruction
    .ENDIF
    jmp     _fpu_unused

  _fpu_db:
    mov     al,byte ptr ds:[esi+1]
    .IF (al >= 0c0h && al <= 0c7h)
      ; It's FCMOVNB st0,sti
        @instr_bytes    1
        @instr_text     fcmovnb_text, 7
        jmp     _st0_sti_common
    .ELSEIF (al >= 0c8h && al <= 0cfh)
      ; It's FCMOVNZ st0,sti
        @instr_bytes    1
        @instr_text     fcmovnz_text, 7
        jmp     _st0_sti_common
    .ELSEIF (al >= 0d0h && al <= 0d7h)
      ; It's FCMOVG st0,sti
        @instr_bytes    1
        @instr_text     fcmovg_text, 6
        jmp     _st0_sti_common
    .ELSEIF (al >= 0d8h && al <= 0dfh)
      ; It's FCMOVPE st0,sti
        @instr_bytes    1
        @instr_text     fcmovpe_text, 7
        jmp     _st0_sti_common
    .ELSEIF (al == 0e2h)
      ; It's fnclex
        @instr_bytes    2
        @instr_text     fnclex_text, 6
        jmp     store_instruction
    .ELSEIF (al == 0e3h)
      ; It's fninit
        @instr_bytes    2
        @instr_text     fninit_text, 6
        jmp     store_instruction
    .ELSEIF (al >= 0e8h && al <= 0efh)
      ; It's FUCOMI st(0),st(i)
        @instr_bytes    2
        @instr_text     fucomi_text, 6
        jmp     _st0_sti_common
    .ELSEIF (al >= 0f0h && al <= 0f7h)
      ; It's FCOMI st(0),st(i)
        @instr_bytes    2
        @instr_text     fcomi_text, 5
        jmp     _st0_sti_common
    .ENDIF
    shr     al,3
    and     al,111b
    .IF (al == 000b)
      ; It's FILD m32_int
        @instr_bytes    1
        @instr_text     fild_text, 4
        mov     fs:operand_size,32
        call    extract_mod_rm
        jmp     store_instruction
    .ELSEIF (al == 010b)
      ; It's FIST m32_int
        @instr_bytes    1
        @instr_text     fist_text, 4
        mov     fs:operand_size,32
        call    extract_mod_rm
        jmp     store_instruction
    .ELSEIF (al == 011b)
      ; It's FISTP m32_int
        @instr_bytes    1
        @instr_text     fistp_text, 5
        mov     fs:operand_size,32
        call    extract_mod_rm
        jmp     store_instruction
    .ELSEIF (al == 101b)
      ; It's FLD real10
        @instr_bytes    1
        @instr_text     fld_text, 3
        mov     fs:operand_size,80
        call    extract_mod_rm
        jmp     store_instruction
    .ELSEIF (al == 111b)
      ; It's FSTP real10
        @instr_bytes    1
        @instr_text     fstp_text, 4
        mov     fs:operand_size,80
        call    extract_mod_rm
        jmp     store_instruction
    .ENDIF
    jmp     _fpu_unused

  _fpu_dc:
    mov     al,byte ptr ds:[esi+1]
    .IF (al >= 0c0h && al <= 0c7h)
      ; It's FADD st(i),st(0)
        @instr_bytes    2
        @instr_text     fadd_text, 4
      _sti_st0_common:
        call    start_offsets
        mov     fs:operand_size,80
        mov     fs:special_reg,_STx_REGS
        and     al,111b
        mov     bl,al
        call    store_gp_register
        call    store_comma
        xor     bl,bl
        call    store_gp_register
        call    end_offsets
        jmp     store_instruction
    .ELSEIF (al >= 0c8h && al <= 0cfh)
      ; It's FMUL st(i),st(0)
        @instr_bytes    2
        @instr_text     fmul_text, 4
        jmp     _sti_st0_common
    .ELSEIF (al >= 0e0h && al <= 0e7h)
      ; It's FSUBR st(i),st(0)
        @instr_bytes    2
        @instr_text     fsubr_text, 5
        jmp     _sti_st0_common
    .ELSEIF (al >= 0e8h && al <= 0efh)
      ; It's FSUB st(i),st(0)
        @instr_bytes    2
        @instr_text     fsub_text, 4
        jmp     _sti_st0_common
    .ELSEIF (al >= 0f0h && al <= 0f7h)
      ; It's FDIVR st(i),st(0)
        @instr_bytes    1
        @instr_text     fdivr_text, 5
        jmp     _sti_st0_common
    .ELSEIF (al >= 0f8h && al <= 0ffh)
      ; It's FDIV st(i),st(0)
        @instr_bytes    1
        @instr_text     fdiv_text, 4
        jmp     _sti_st0_common
    .ENDIF
    shr     al,3
    and     al,111b
    .IF (al == 000b)
      ; It's FADD real8
        @instr_bytes    1
        @instr_text     fadd_text, 4
        mov     fs:operand_size,64
        call    extract_mod_rm
        jmp     store_instruction
    .ELSEIF (al == 001b)
      ; It's FMUL real8
        @instr_bytes    1
        @instr_text     fmul_text, 4
        mov     fs:operand_size,64
        call    extract_mod_rm
        jmp     store_instruction
    .ELSEIF (al == 010b)
      ; It's FCOM real8
        @instr_bytes    1
        @instr_text     fcom_text, 4
        mov     fs:operand_size,64
        call    extract_mod_rm
        jmp     store_instruction
    .ELSEIF (al == 011b)
      ; It's FCOMP real8
        @instr_bytes    1
        @instr_text     fcomp_text, 5
        mov     fs:operand_size,64
        call    extract_mod_rm
        jmp     store_instruction
    .ELSEIF (al == 100b)
      ; It's FSUB real8
        @instr_bytes    1
        @instr_text     fsub_text, 4
        mov     fs:operand_size,64
        call    extract_mod_rm
        jmp     store_instruction
    .ELSEIF (al == 101b)
      ; It's FSUBR real8
        @instr_bytes    1
        @instr_text     fsubr_text, 5
        mov     fs:operand_size,64
        call    extract_mod_rm
        jmp     store_instruction
    .ELSEIF (al == 110b)
      ; It's FDIV real8
        @instr_bytes    1
        @instr_text     fdiv_text, 4
        mov     fs:operand_size,64
        call    extract_mod_rm
        jmp     store_instruction
    .ELSEIF (al == 111b)
      ; It's FDIVR real8
        @instr_bytes    1
        @instr_text     fdivr_text, 5
        mov     fs:operand_size,64
        call    extract_mod_rm
        jmp     store_instruction
    .ENDIF
    jmp     _fpu_unused

  _fpu_dd:
    mov     al,byte ptr ds:[esi+1]
    .IF (al >= 0c0h && al <= 0c7h)
      ; It's FFREE st(i)
        @instr_bytes    1
        @instr_text     ffree_text, 5
      _sti_common:
        call    start_offsets
        mov     fs:special_reg,_STx_REGS
        and     al,111b
        mov     bl,al
        call    store_gp_register
        call    end_offsets
        jmp     store_instruction
    .ELSEIF (al >= 0d0h && al <= 0d7h)
      ; It's FST st(i)
        @instr_bytes    1
        @instr_text     fst_text, 3
        jmp     _sti_common
    .ELSEIF (al >= 0d8h && al <= 0dfh)
      ; It's FSTP st(i)
        @instr_bytes    1
        @instr_text     fstp_text, 4
        jmp     _sti_common
    .ELSEIF (al >= 0e0h && al <= 0e7h)
      ; It's FUCOM st(i)
        @instr_bytes    1
        @instr_text     fucom_text, 5
        jmp     _sti_common
    .ELSEIF (al >= 0e8h && al <= 0efh)
      ; It's FUCOMP st(i)
        @instr_bytes    1
        @instr_text     fucomp_text, 6
        jmp     _sti_common
    .ELSEIF (al == 0e9h)
      ; It's FUCOMPP
        @instr_bytes    1
        @instr_text     fucompp_text, 7
        jmp     store_instruction
    .ENDIF
    shr     al,3
    and     al,111b
    .IF (al == 000b)
      ; It's FLD real8
        @instr_bytes    1
        @instr_text     fld_text, 3
        mov     fs:operand_size,64
        call    extract_mod_rm
        jmp     store_instruction
    .ELSEIF (al == 010b)
      ; It's FST real8
        @instr_bytes    1
        @instr_text     fst_text, 3
        mov     fs:operand_size,64
        call    extract_mod_rm
        jmp     store_instruction
    .ELSEIF (al == 011b)
      ; It's FSTP real8
        @instr_bytes    1
        @instr_text     fstp_text, 4
        mov     fs:operand_size,64
        call    extract_mod_rm
        jmp     store_instruction
    .ELSEIF (al == 100b)
      ; It's FRSTOR m94/108
        @instr_bytes    1
        @instr_text     frstor_text, 6
        .IF ((fs:cpu_mode == 0 && fs:op_size_override != 0) || (fs:cpu_mode != 0 && fs:op_size_override == 0))
            mov     fs:operand_size,94
        .ELSE
            mov     fs:operand_size,108
        .ENDIF
        call    extract_mod_rm
        jmp     store_instruction
    .ELSEIF (al == 110b)
      ; It's FNSAVE
        @instr_bytes    1
        @instr_text     fnsave_text, 6
        .IF ((fs:cpu_mode == 0 && fs:op_size_override != 0) || (fs:cpu_mode != 0 && fs:op_size_override == 0))
            mov     fs:operand_size,94
        .ELSE
            mov     fs:operand_size,108
        .ENDIF
        call    extract_mod_rm
        jmp     store_instruction
    .ELSEIF (al == 111b)
      ; It's FNSTSW
        @instr_bytes    1
        @instr_text     fnstsw_text, 6
        mov     fs:operand_size,16
        call    extract_mod_rm
        jmp     store_instruction
    .ENDIF
    jmp     _fpu_unused

  _fpu_de:
    mov     al,byte ptr ds:[esi+1]
    .IF (al >= 0c0h && al <= 0c7h)
      ; It's FADDP st(i),st(0)
        @instr_bytes    2
        @instr_text     faddp_text, 5
        jmp     _sti_st0_common
    .ELSEIF (al >= 0c8h && al <= 0cfh)
      ; It's FMULP st(i),st(0)
        @instr_bytes    2
        @instr_text     fmulp_text, 5
        jmp     _sti_st0_common
    .ELSEIF (al == 0d9h)
      ; It's FCOMPP
        @instr_bytes    2
        @instr_text     fcompp_text, 6
        jmp     store_instruction
    .ELSEIF (al >= 0e0h && al <= 0e7h)
      ; It's FSUBRP st(i),st(0)
        @instr_bytes    2
        @instr_text     fsubrp_text, 6
        jmp     _sti_st0_common
    .ELSEIF (al >= 0e8h && al <= 0efh)
      ; It's FSUBP st(i),st(0)
        @instr_bytes    2
        @instr_text     fsubp_text, 5
        jmp     _sti_st0_common
    .ELSEIF (al >= 0f0h && al <= 0f7h)
      ; It's FDIVRP st(i),st(0)
        @instr_bytes    1
        @instr_text     fdivrp_text, 6
        jmp     _sti_st0_common
    .ELSEIF (al >= 0f8h && al <= 0ffh)
      ; It's FDIVP st(i),st(0)
        @instr_bytes    1
        @instr_text     fdivp_text, 5
        jmp     _sti_st0_common
    .ENDIF
    shr     al,3
    and     al,111b
    .IF (al == 000b)
      ; It's FIADD m64_int
        @instr_bytes    1
        @instr_text     fiadd_text, 5
        mov     fs:operand_size,16
        call    extract_mod_rm
        jmp     store_instruction
    .ELSEIF (al == 001b)
      ; It's FIMUL m16_int
        @instr_bytes    1
        @instr_text     fimul_text, 5
        mov     fs:operand_size,16
        call    extract_mod_rm
        jmp     store_instruction
    .ELSEIF (al == 010b)
      ; It's FICOM m16_int
        @instr_bytes    1
        @instr_text     ficom_text, 5
        mov     fs:operand_size,16
        call    extract_mod_rm
        jmp     store_instruction
    .ELSEIF (al == 011b)
      ; It's FICOMP m16_int
        @instr_bytes    1
        @instr_text     ficomp_text, 6
        mov     fs:operand_size,16
        call    extract_mod_rm
        jmp     store_instruction
    .ELSEIF (al == 100b)
      ; It's FISUB m16_int
        @instr_bytes    1
        @instr_text     fisub_text, 5
        mov     fs:operand_size,16
        call    extract_mod_rm
        jmp     store_instruction
    .ELSEIF (al == 101b)
      ; It's FISUBR m16_int
        @instr_bytes    1
        @instr_text     fisubr_text, 6
        mov     fs:operand_size,16
        call    extract_mod_rm
        jmp     store_instruction
    .ELSEIF (al == 110b)
      ; It's FIDIV m16_int
        @instr_bytes    1
        @instr_text     fidiv_text, 5
        mov     fs:operand_size,16
        call    extract_mod_rm
        jmp     store_instruction
    .ELSEIF (al == 111b)
      ; It's FIDIVR m16_int
        @instr_bytes    1
        @instr_text     fidivr_text, 6
        mov     fs:operand_size,16
        call    extract_mod_rm
        jmp     store_instruction
    .ENDIF
    jmp     _fpu_unused

  _fpu_df:
    mov     al,byte ptr ds:[esi+1]
    .IF (al == 0e0h)
      ; It's FNSTSW ax
        @instr_bytes    1
        @instr_text     fnstsw_text, 6
        call    start_offsets
        xor     bl,bl
        mov     fs:operand_size,16
        call    store_gp_register
        call    end_offsets
        jmp     store_instruction
    .ELSEIF (al >= 0e8h && al <= 0efh)
      ; It's FUCOMIP st(0),st(i)
        @instr_bytes    2
        @instr_text     fucomip_text, 7
        jmp     _st0_sti_common
    .ELSEIF (al >= 0f0h && al <= 0f7h)
      ; It's FCOMIP st(0),st(i)
        @instr_bytes    2
        @instr_text     fcomip_text, 6
        jmp     _st0_sti_common
    .ENDIF
    shr     al,3
    and     al,111b
    .IF (al == 000b)
      ; It's FILD m16_int
        @instr_bytes    1
        @instr_text     fild_text, 4
        mov     fs:operand_size,16
        call    extract_mod_rm
        jmp     store_instruction
    .ELSEIF (al == 010b)
      ; It's FIST m16_int
        @instr_bytes    1
        @instr_text     fist_text, 4
        mov     fs:operand_size,16
        call    extract_mod_rm
        jmp     store_instruction
    .ELSEIF (al == 011b)
      ; It's FISTP m16_int
        @instr_bytes    1
        @instr_text     fistp_text, 5
        mov     fs:operand_size,16
        call    extract_mod_rm
        jmp     store_instruction
    .ELSEIF (al == 100b)
      ; It's fbld m80_bcd
        @instr_bytes    1
        @instr_text     fbld_text, 4
        mov     fs:operand_size,80
        call    extract_mod_rm
        jmp     store_instruction
    .ELSEIF (al == 110b)
      ; It's fbstp m80_bcd
        @instr_bytes    1
        @instr_text     fbstp_text, 5
        mov     fs:operand_size,80
        call    extract_mod_rm
        jmp     store_instruction
    .ELSEIF (al == 101b)
      ; It's FILD m64_int
        @instr_bytes    1
        @instr_text     fild_text, 4
        mov     fs:operand_size,64
        call    extract_mod_rm
        jmp     store_instruction
    .ELSEIF (al == 111b)
      ; It's FISTP m64_int
        @instr_bytes    1
        @instr_text     fistp_text, 5
        mov     fs:operand_size,64
        call    extract_mod_rm
        jmp     store_instruction
    .ENDIF
    jmp     _fpu_unused

  _hlt:
    @instr_bytes    1
    @instr_text     hlt_text, 3
    jmp     store_instruction

  _idiv_byte:
    @instr_bytes    1
    @instr_text     idiv_text, 4
  _ixxx_common1:
    mov     fs:operand_size,8
    call    extract_mod_rm
    jmp     store_instruction

  _idiv:
    @instr_bytes    1
    @instr_text     idiv_text, 4
  _ixxx_common2:
    call    determine_standard_operand_size
    call    extract_mod_rm
    jmp     store_instruction

  _imul_byte:
    @instr_bytes    1
    @instr_text     imul_text, 4
    jmp     _ixxx_common1

  _imul:
    @instr_bytes    1
    @instr_text     imul_text, 4
    jmp     _ixxx_common2

  _imul_2_params:
    @instr_bytes    2
    @instr_text     imul_text, 4
    mov     fs:reverse_mod_reg_rm,1
    call    determine_standard_operand_size
    call    extract_mod_reg_rm
    jmp     store_instruction

  _imul_3_parms_immed8:
    @instr_bytes    1
    @instr_text     imul_text, 4
    call    start_offsets
    mov     fs:operand_size,16
    mov     fs:reverse_mod_reg_rm,1
    mov     fs:display_second_register,0
    call    extract_mod_reg_rm
    call    end_offsets
  ; Add the 3rd parameter
    call    store_comma
    call    store_8_bit_signed_value
    add     fs:parameters_text_length,3
    jmp     store_instruction

  _imul_3_parms_immed16_32:
    @instr_bytes    1
    @instr_text     imul_text, 4
    call    start_offsets
    mov     fs:reverse_mod_reg_rm,1
    call    determine_standard_operand_size
    call    extract_mod_reg_rm
    call    end_offsets
  ; Store the 3rd parameter
    call    store_comma
    call    store_signed_value
    .IF ((fs:cpu_mode == 0 && fs:op_size_override != 0) || (fs:cpu_mode != 0 && fs:op_size_override == 0))
        add     fs:parameters_text_length,5
    .ELSE
        add     fs:parameters_text_length,9
    .ENDIF
    jmp     store_instruction

  _in8_immed8:
  _in16_32_immed8:
    @instr_bytes    1
    @instr_text     in_text, 2
    call    start_offsets
    and     eax,1b
    push    eax
    call    determine_operand_size
    xor     bl,bl
    call    store_gp_register
    call    store_comma
    call    store_8_bit_value
    call    end_offsets
    jmp     store_instruction

  _in_byte:
    @instr_bytes    1
    @instr_text     in_text, 2
    call    start_offsets
    mov     fs:operand_size,8
    xor     bl,bl
    call    store_gp_register
    call    store_comma
    mov     fs:operand_size,16
    mov     bl,010b
    call    store_gp_register
    call    end_offsets
    mov     fs:operand_size,8
    jmp     store_instruction

  _in:
    @instr_bytes    1
    @instr_text     in_text, 2
    call    start_offsets
    call    determine_standard_operand_size
    push    fs:operand_size
    xor     bl,bl
    call    store_gp_register
    call    store_comma
    mov     fs:operand_size,16
    mov     bl,010b
    call    store_gp_register
    call    end_offsets
    pop     fs:operand_size
    jmp     store_instruction

  _inc_xax:
  _inc_xbp:
  _inc_xbx:
  _inc_xcx:
  _inc_xdi:
  _inc_xdx:
  _inc_xsi:
  _inc_xsp:
    @instr_bytes    1
    @instr_text     inc_text, 3
    jmp     xnc_common1

  _inc_rm8:
    @instr_bytes    1
    @instr_text     inc_text, 3
    jmp     xnc_common2

  _inc_rm16_32:
    @instr_bytes    1
    @instr_text     inc_text, 3
    jmp     xnc_common3

  _insb:
    @instr_bytes    1
    @instr_text     insb_text, 4
    jmp     store_instruction

  _insw:
    @instr_bytes    1
    .IF ((fs:cpu_mode == 0 && fs:op_size_override != 0) || (fs:cpu_mode != 0 && fs:op_size_override == 0))
        @instr_text     insw_text, 4
    .ELSE
        @instr_text     insd_text, 4
    .ENDIF
    jmp     store_instruction

  _int3:
    @instr_bytes    1
    @instr_text     int3_phrase, 4
    jmp     store_instruction

  _into:
    @instr_bytes    1
    @instr_text     into_text, 4
    jmp     store_instruction

  _intx:
    @instr_bytes    1
    @instr_text     int_text, 3
    call    start_offsets
    call    store_8_bit_value
    call    end_offsets
    jmp     store_instruction

  _invd:
    @instr_bytes    2
    @instr_text     invd_text, 4
    jmp     store_instruction

  _invlpg:
    @instr_bytes    2
    @instr_text     invlpg_text, 6
    call    extract_mod_rm
    jmp     store_instruction

  _iret:
    @instr_bytes    1
    .IF ((fs:cpu_mode == 0 && fs:op_size_override != 0) || (fs:cpu_mode != 0 && fs:op_size_override == 0))
        @instr_text     iret_text, 4
    .ELSE
        @instr_text     iretd_text, 5
    .ENDIF
    jmp     store_instruction

  _jmp8:
    @instr_bytes    1
    @instr_text     jmp_text, 3
    call    start_offsets
    call    store_8_bit_signed_value
    call    end_offsets
    jmp     store_instruction

  _jmp16_32:
    @instr_bytes    1
    @instr_text     jmp_text, 3
    call    start_offsets
    .IF ((fs:cpu_mode == 0 && fs:adr_size_override != 0) || (fs:cpu_mode != 0 && fs:adr_size_override == 0))
        call    store_16_bit_signed_value
    .ELSE
        call    store_32_bit_signed_value
    .ENDIF
    call    end_offsets
    jmp     store_instruction

  _jmp_far:
    @instr_bytes    1
    @instr_text     jmp_text, 3
    call    start_offsets
    call    store_16_bit_signed_value
    call    store_colon
    .IF ((fs:cpu_mode == 0 && fs:adr_size_override != 0) || (fs:cpu_mode != 0 && fs:adr_size_override == 0))
        call    store_16_bit_signed_value
    .ELSE
        call    store_32_bit_signed_value
    .ENDIF
    call    end_offsets
    jmp     store_instruction

  _jmp_near_rm:
    @instr_bytes    1
    @instr_text     jmp_text, 3
    .IF ((fs:cpu_mode == 0 && fs:adr_size_override != 0) || (fs:cpu_mode != 0 && fs:adr_size_override == 0))
        mov     fs:operand_size,16
    .ELSE
        mov     fs:operand_size,32
    .ENDIF
    call    extract_mod_rm
    jmp     store_instruction

  _jmp_far_rm:
    @instr_bytes    1
    @instr_text     jmp_text, 3
    .IF ((fs:cpu_mode == 0 && fs:adr_size_override != 0) || (fs:cpu_mode != 0 && fs:adr_size_override == 0))
        mov     fs:operand_size,32
    .ELSE
        mov     fs:operand_size,48
    .ENDIF
    call    extract_mod_rm
    jmp     store_instruction

  _jcxz:
    @instr_bytes    1
    .IF ((fs:cpu_mode == 0 && fs:adr_size_override != 0) || (fs:cpu_mode != 0 && fs:adr_size_override == 0))
        @instr_text     jcxz_text, 4
    .ELSE
        @instr_text     jecxz_text, 5
    .ENDIF
    call    start_offsets
    call    store_8_bit_signed_value
    call    end_offsets
    jmp     store_instruction

  _jz:
    @instr_bytes    1
    @instr_text     jz_text, 2
  jxx_common:
    call    start_offsets
    call    store_8_bit_signed_value
    call    end_offsets
    jmp     store_instruction

  _jnz:
    @instr_bytes    1
    @instr_text     jnz_text, 3
    jmp     jxx_common

  _jz_l:
    @instr_bytes    2
    @instr_text     jz_text, 2
  jxx_common_l:
    call    start_offsets
    .IF ((fs:cpu_mode == 0 && fs:adr_size_override != 0) || (fs:cpu_mode != 0 && fs:adr_size_override == 0))
        call    store_16_bit_signed_value
    .ELSE
        call    store_32_bit_signed_value
    .ENDIF
    call    end_offsets
    jmp     store_instruction

  _jnz_l:
    @instr_bytes    2
    @instr_text     jnz_text, 3
    jmp     jxx_common_l

  _ja:
    @instr_bytes    1
    @instr_text     ja_text, 2
    jmp     jxx_common

  _jna:
    @instr_bytes    1
    @instr_text     jna_text, 3
    jmp     jxx_common

  _ja_l:
    @instr_bytes    2
    @instr_text     ja_text, 2
    jmp     jxx_common_l

  _jna_l:
    @instr_bytes    2
    @instr_text     jna_text, 3
    jmp     jxx_common_l

  _jc:
    @instr_bytes    1
    @instr_text     jc_text, 2
    jmp     jxx_common

  _jnc:
    @instr_bytes    1
    @instr_text     jnc_text, 3
    jmp     jxx_common

  _jc_l:
    @instr_bytes    2
    @instr_text     jc_text, 2
    jmp     jxx_common_l

  _jnc_l:
    @instr_bytes    2
    @instr_text     jnc_text, 3
    jmp     jxx_common_l

  _jg:
    @instr_bytes    1
    @instr_text     jg_text, 2
    jmp     jxx_common

  _jng:
    @instr_bytes    1
    @instr_text     jng_text, 3
    jmp     jxx_common

  _jg_l:
    @instr_bytes    2
    @instr_text     jg_text, 2
    jmp     jxx_common_l

  _jng_l:
    @instr_bytes    2
    @instr_text     jng_text, 3
    jmp     jxx_common_l

  _jl:
    @instr_bytes    1
    @instr_text     jl_text, 2
    jmp     jxx_common

  _jnl:
    @instr_bytes    1
    @instr_text     jnl_text, 3
    jmp     jxx_common

  _jl_l:
    @instr_bytes    2
    @instr_text     jl_text, 2
    jmp     jxx_common_l

  _jnl_l:
    @instr_bytes    2
    @instr_text     jnl_text, 3
    jmp     jxx_common_l

  _jo:
    @instr_bytes    1
    @instr_text     jo_text, 2
    jmp     jxx_common

  _jno:
    @instr_bytes    1
    @instr_text     jno_text, 3
    jmp     jxx_common

  _jo_l:
    @instr_bytes    2
    @instr_text     jo_text, 2
    jmp     jxx_common_l

  _jno_l:
    @instr_bytes    2
    @instr_text     jno_text, 3
    jmp     jxx_common_l

  _jpe:
    @instr_bytes    1
    @instr_text     jpe_text, 3
    jmp     jxx_common

  _jpo:
    @instr_bytes    1
    @instr_text     jpo_text, 3
    jmp     jxx_common

  _jpe_l:
    @instr_bytes    2
    @instr_text     jpe_text, 3
    jmp     jxx_common_l

  _jpo_l:
    @instr_bytes    2
    @instr_text     jpo_text, 3
    jmp     jxx_common_l

  _js:
    @instr_bytes    1
    @instr_text     js_text, 2
    jmp     jxx_common

  _jns:
    @instr_bytes    1
    @instr_text     jns_text, 3
    jmp     jxx_common

  _js_l:
    @instr_bytes    2
    @instr_text     js_text, 2
    jmp     jxx_common_l

  _jns_l:
    @instr_bytes    2
    @instr_text     jns_text, 3
    jmp     jxx_common_l

  _lahf:
    @instr_bytes    1
    @instr_text     lahf_text, 4
    jmp     store_instruction

  _lar:
    @instr_bytes    2
    @instr_text     lar_text, 3
    mov     fs:reverse_mod_reg_rm,1
    call    determine_standard_operand_size
    call    extract_mod_reg_rm
    jmp     store_instruction

  _lds:
    @instr_bytes    1
    @instr_text     lds_text, 3
  _lxx_common:
    mov     fs:reverse_mod_reg_rm,1
    call    determine_standard_operand_size
    call    extract_mod_reg_rm
    jmp     store_instruction

  _les:
    @instr_bytes    1
    @instr_text     les_text, 3
    jmp     _lxx_common

  _lfs:
    @instr_bytes    2
    @instr_text     lfs_text, 3
    jmp     _lxx_common

  _lgs:
    @instr_bytes    2
    @instr_text     lgs_text, 3
    jmp     _lxx_common

  _lss:
    @instr_bytes    2
    @instr_text     lss_text, 3
    jmp     _lxx_common

  _lea:
    @instr_bytes    1
    @instr_text     lea_text, 3
    jmp     _lxx_common

  _leave:
    @instr_bytes    1
    @instr_text     leave_text, 5
    jmp     store_instruction

  _lgdt:
    @instr_bytes    2
    @instr_text     lgdt_text, 4
  xxdt_common:
    mov     fs:operand_size,48
    call    extract_mod_rm
    jmp     store_instruction

  _lidt:
    @instr_bytes    2
    @instr_text     lidt_text, 4
    jmp     xxdt_common

  _lldt:
    @instr_bytes    2
    @instr_text     lldt_text, 4
  xldt_common:
    call    determine_standard_operand_size
    call    extract_mod_rm
    jmp     store_instruction

  _ltr:
    @instr_bytes    2
    @instr_text     ltr_text, 3
    mov     fs:operand_size,16
    call    extract_mod_rm
    jmp     store_instruction

  _lmsw:
    @instr_bytes    2
    @instr_text     lmsw_text, 4
    mov     fs:operand_size,16
    call    extract_mod_rm
    jmp     store_instruction

  _lock_prefix:
    @instr_bytes    1
    @instr_text     lock_text, 4
    jmp     store_instruction

  _lodsb:
    @instr_bytes    1
    @instr_text     lodsb_text, 5
    jmp     store_instruction

  _lodsw:
    @instr_bytes    1
    .IF ((fs:cpu_mode == 0 && fs:op_size_override != 0) || (fs:cpu_mode != 0 && fs:op_size_override == 0))
        @instr_text     lodsw_text, 5
    .ELSE
        @instr_text     lodsd_text, 5
    .ENDIF
    jmp     store_instruction

  _loop:
    @instr_bytes    1
    @instr_text     loop_text, 4
    jmp     _loopxx_common

  _loope:
    @instr_bytes    1
    @instr_text     loope_text, 5
    jmp     _loopxx_common

  _loopne:
    @instr_bytes    1
    @instr_text     loopne_text, 6
  _loopxx_common:
    call    start_offsets
    call    store_8_bit_signed_value
    call    end_offsets
    jmp     store_instruction

  _lsl:
    @instr_bytes    2
    @instr_text     lsl_text, 3
    mov     fs:reverse_mod_reg_rm,1
    call    determine_standard_operand_size
    call    extract_mod_reg_rm
    jmp     store_instruction

  _mov_rm_reg_8:
    @instr_bytes    1
    @instr_text     mov_text, 3
    mov     fs:operand_size,8
    call    extract_mod_reg_rm
    jmp     store_instruction

  _mov_rm_reg_16_32:
    @instr_bytes    1
    @instr_text     mov_text, 3
    call    determine_standard_operand_size
    call    extract_mod_reg_rm
    jmp     store_instruction

  _mov_reg_rm_8:
    @instr_bytes    1
    @instr_text     mov_text, 3
    mov     fs:operand_size,8
    mov     fs:reverse_mod_reg_rm,1
    call    extract_mod_reg_rm
    jmp     store_instruction

  _mov_reg_rm_16_32:
    @instr_bytes    1
    @instr_text     mov_text, 3
    mov     fs:reverse_mod_reg_rm,1
    call    determine_standard_operand_size
    call    extract_mod_reg_rm
    jmp     store_instruction

  _mov_sreg_reg16_32:
    @instr_bytes    1
    @instr_text     mov_text, 3
    mov     fs:special_control,1
    mov     fs:reverse_mod_reg_rm,1
    call    determine_standard_operand_size
    call    extract_mod_reg_rm
    jmp     store_instruction

  _mov_reg16_32_sreg:
    @instr_bytes    1
    @instr_text     mov_text, 3
    mov     fs:special_control,2
    call    determine_standard_operand_size
    call    extract_mod_reg_rm
    jmp     store_instruction

  _mov_accum_mem_8:
    @instr_bytes    1
    @instr_text     mov_text, 3
    call    start_offsets
    mov     fs:operand_size,8
    xor     bl,bl
    call    store_gp_register
    call    store_comma
    call    store_segment_override
    call    store_open_bracket
    .IF ((fs:cpu_mode == 0 && fs:adr_size_override != 0) || (fs:cpu_mode != 0 && fs:adr_size_override == 0))
        call    store_16_bit_value
    .ELSE
        call    store_32_bit_value
    .ENDIF
    call    store_close_bracket
    call    end_offsets
    jmp     store_instruction

  _mov_accum_mem_16_32:
    @instr_bytes    1
    @instr_text     mov_text, 3
    call    start_offsets
    call    determine_standard_operand_size
    xor     bl,bl
    call    store_gp_register
    call    store_comma
    call    store_segment_override
    call    store_open_bracket
    .IF ((fs:cpu_mode == 0 && fs:adr_size_override != 0) || (fs:cpu_mode != 0 && fs:adr_size_override == 0))
        call    store_16_bit_value
    .ELSE
        call    store_32_bit_value
    .ENDIF
    call    store_close_bracket
    call    end_offsets
    jmp     store_instruction

  _mov_mem_accum_8:
    @instr_bytes    1
    @instr_text     mov_text, 3
    call    start_offsets
    mov     fs:operand_size,8
    xor     bl,bl
    call    store_segment_override
    call    store_open_bracket
    .IF ((fs:cpu_mode == 0 && fs:adr_size_override != 0) || (fs:cpu_mode != 0 && fs:adr_size_override == 0))
        call    store_16_bit_value
    .ELSE
        call    store_32_bit_value
    .ENDIF
    call    store_close_bracket
    call    store_comma
    call    store_gp_register
    call    end_offsets
    jmp     store_instruction

  _mov_mem_accum_16_32:
    @instr_bytes    1
    @instr_text     mov_text, 3
    call    start_offsets
    call    store_segment_override
    call    store_open_bracket
    .IF ((fs:cpu_mode == 0 && fs:adr_size_override != 0) || (fs:cpu_mode != 0 && fs:adr_size_override == 0))
        call    store_16_bit_value
    .ELSE
        call    store_32_bit_value
    .ENDIF
    call    store_close_bracket
    call    store_comma
    call    determine_standard_operand_size
    xor     bl,bl
    call    store_gp_register
    call    end_offsets
    jmp     store_instruction

  _mov_reg_immed8:
    @instr_bytes    1
    @instr_text     mov_text, 3
    call    start_offsets
    mov     fs:operand_size,8
    and     eax,111b
    mov     bl,al
    call    store_gp_register
    call    store_comma
    call    store_8_bit_signed_value
    call    end_offsets
    jmp     store_instruction

  _mov_reg_immed16_32:
    @instr_bytes    1
    @instr_text     mov_text, 3
    call    start_offsets
    push    eax
    shr     eax,3
    and     eax,1b
    push    eax
    call    determine_operand_size
    pop     eax
    and     eax,111b
    mov     bl,al
    call    store_gp_register
    call    store_comma
    call    store_signed_value
    call    end_offsets
    jmp     store_instruction

  _mov_rm_immed8:
    @instr_bytes    1
    @instr_text     mov_text, 3
    call    start_offsets
    mov     fs:operand_size,8
    call    extract_mod_rm
    call    store_comma
    call    store_8_bit_signed_value
    call    end_offsets
    jmp     store_instruction

  _mov_rm_immed16_32:
    @instr_bytes    1
    @instr_text     mov_text, 3
    call    start_offsets
    shr     eax,3
    and     eax,1b
    push    eax
    call    determine_operand_size
    pop     eax
    call    extract_mod_rm
    call    store_comma
    call    store_signed_value
    call    end_offsets
    jmp     store_instruction

  _mov_gp_control:
    @instr_bytes    2
    @instr_text     mov_text, 3
    and     eax,10b
    mov     fs:reverse_mod_reg_rm,eax
    .IF (fs:reverse_mod_reg_rm != 0)
        mov     fs:special_control,3
    .ELSE
        mov     fs:special_control,4
    .ENDIF
    mov     fs:operand_size,32
    call    extract_mod_reg_rm
    jmp     store_instruction

  _mov_gp_debug:
    @instr_bytes    2
    @instr_text     mov_text, 3
    and     eax,10b
    mov     fs:reverse_mod_reg_rm,eax
    .IF (fs:reverse_mod_reg_rm != 0)
        mov     fs:special_control,5
    .ELSE
        mov     fs:special_control,6
    .ENDIF
    mov     fs:operand_size,32
    call    extract_mod_reg_rm
    jmp     store_instruction

  _mov_gp_test:
    @instr_bytes    2
    @instr_text     mov_text, 3
    and     eax,10b
    mov     fs:reverse_mod_reg_rm,eax
    .IF (fs:reverse_mod_reg_rm != 0)
        mov     fs:special_control,7
    .ELSE
        mov     fs:special_control,8
    .ENDIF
    mov     fs:operand_size,32
    call    extract_mod_reg_rm
    jmp     store_instruction

  _movd_gp_mmx:
    @instr_bytes    2
    @instr_text     movd_text, 4
    mov     fs:special_control,11
    mov     fs:operand_size,32
    call    extract_mod_reg_rm
    jmp     store_instruction

  _movd_mmx_gp:
    @instr_bytes    2
    @instr_text     movd_text, 4
    mov     fs:special_control,10
    mov     fs:operand_size,32
    mov     fs:reverse_mod_reg_rm,1
    call    extract_mod_reg_rm
    jmp     store_instruction

  _movq_mm_mmx_mmx:
    @instr_bytes    2
    @instr_text     movq_text, 4
    mov     fs:special_control,9
    mov     fs:operand_size,64
    call    extract_mod_reg_rm
    jmp     store_instruction

  _movq_mmx_mm_mmx:
    @instr_bytes    2
    @instr_text     movq_text, 4
    mov     fs:special_control,9
    mov     fs:operand_size,64
    mov     fs:reverse_mod_reg_rm,1
    call    extract_mod_reg_rm
    jmp     store_instruction

  _movsb:
    @instr_bytes    1
    @instr_text     movsb_text, 5
    jmp     store_instruction

  _movsw:
    @instr_bytes    1
    .IF ((fs:cpu_mode == 0 && fs:op_size_override != 0) || (fs:cpu_mode != 0 && fs:op_size_override == 0))
        @instr_text     movsw_text, 5
    .ELSE
        @instr_text     movsd_text, 5
    .ENDIF
    jmp     store_instruction

  _movsx_byte:
  _movsx_word:
    @instr_bytes    2
    @instr_text     movsx_text, 5
  _movxx_common:
    mov     fs:reverse_mod_reg_rm,1
    mov     fs:movxx_register,1
    and     eax,1b
    .IF ((fs:cpu_mode == 0 && fs:op_size_override != 0) || (fs:cpu_mode != 0 && fs:op_size_override == 0))
        ; They're going from whatever the current operand size is to 16-bits
        mov     fs:first_gp_register,16
        .IF (al == 0)
          ; They're going from 8-bit to 16-bit
            mov     fs:second_gp_register,8
        .ELSE
          ; They're going from 16-bit to 16-bit
            mov     fs:second_gp_register,16
        .ENDIF
    .ELSE
        ; They're going from whatever the current operand size is to 32-bits
        mov     fs:first_gp_register,32
        .IF (al == 0)
          ; They're going from 8-bit to 32-bit
            mov     fs:second_gp_register,8
        .ELSE
          ; They're going from 16-bit to 32-bit
            mov     fs:second_gp_register,16
        .ENDIF
    .ENDIF
    call    extract_mod_reg_rm
    mov     fs:movxx_register,0
    jmp     store_instruction

  _movzx_byte:
  _movzx_word:
    @instr_bytes    2
    @instr_text     movzx_text, 5
    jmp     _movxx_common

  _mul_byte:
    @instr_bytes    1
    @instr_text     mul_text, 3
    jmp     _ixxx_common1

  _mul:
    @instr_bytes    1
    @instr_text     mul_text, 3
    jmp     _ixxx_common2

  _neg_byte:
    @instr_bytes    1
    @instr_text     neg_text, 3
    jmp     _ixxx_common1

  _neg:
    @instr_bytes    1
    @instr_text     neg_text, 3
    jmp     _ixxx_common2

  _not_byte:
    @instr_bytes    1
    @instr_text     not_text, 3
    jmp     _ixxx_common1

  _not:
    @instr_bytes    1
    @instr_text     not_text, 3
    jmp     _ixxx_common2

  _nop:
    @instr_bytes    1
    @instr_text     nop_text, 3
    jmp     store_instruction

  _or_accum:
    @instr_bytes    1
    @instr_text     or_text, 2
    call    start_offsets
    test    eax,1b
    .IF (zero?)
      ; 8-bit mode
        xor     bl,bl
        mov     fs:operand_size,8
        call    store_gp_register
        call    store_comma
        call    store_8_bit_signed_value
    .ELSE
        xor     bl,bl
        call    determine_standard_operand_size
        call    store_gp_register
        call    store_comma
        call    store_signed_value
    .ENDIF
    call    end_offsets
    jmp     store_instruction

  _or_rm:
    @instr_bytes    1
    @instr_text     or_text, 2
    jmp     _dw_mod_reg_rm_common

  _or_rm_16_32_with_immed8:
    call    determine_standard_operand_size
    jmp     or_rm_immed8_common

  _or_rm_immed8:
    mov     fs:operand_size,8
  or_rm_immed8_common:
    @instr_bytes    1
    @instr_text     or_text, 2
    call    start_offsets
    call    extract_mod_rm
    call    store_comma
    call    store_8_bit_signed_value
    call    end_offsets
    jmp     store_instruction

  _or_rm_immed16_32:
    @instr_bytes    1
    @instr_text     or_text, 2
    call    start_offsets
    call    determine_standard_operand_size
    call    extract_mod_rm
    call    store_comma
    call    store_signed_value
    call    end_offsets
    jmp     store_instruction

  _out_byte:
    @instr_bytes    1
    @instr_text     outsb_text, 3
    call    start_offsets
    mov     fs:operand_size,16
    mov     bl,010b
    call    store_gp_register
    call    store_comma
    mov     fs:operand_size,8
    xor     bl,bl
    call    store_gp_register
    call    end_offsets
    jmp     store_instruction

  _out:
    @instr_bytes    1
    @instr_text     outsb_text, 3
    call    start_offsets
    mov     fs:operand_size,16
    mov     bl,010b
    call    store_gp_register
    call    store_comma
    call    determine_standard_operand_size
    xor     bl,bl
    call    store_gp_register
    call    end_offsets
    jmp     store_instruction

  _outsb:
    @instr_bytes    1
    @instr_text     outsb_text, 5
    jmp     store_instruction

  _outsw:
    @instr_bytes    1
    .IF ((fs:cpu_mode == 0 && fs:op_size_override != 0) || (fs:cpu_mode != 0 && fs:op_size_override == 0))
        @instr_text     outsw_text, 5
    .ELSE
        @instr_text     outsd_text, 5
    .ENDIF
    jmp     store_instruction

  _packsswb:
    @instr_bytes    2
    @instr_text     packsswb_text, 8
  pack_mmx_rm_common:
    mov     fs:special_reg,_MMX_REGS
    mov     fs:reverse_mod_reg_rm,1
    call    extract_mod_reg_rm
    jmp     store_instruction

  _packssdw:
    @instr_bytes    2
    @instr_text     packssdw_text, 8
    jmp     pack_mmx_rm_common

  _packuswb:
    @instr_bytes    2
    @instr_text     packuswb_text, 8
    jmp     pack_mmx_rm_common

  _paddb:
    @instr_bytes    2
    @instr_text     paddb_text, 5
    jmp     pack_mmx_rm_common

  _paddw:
    @instr_bytes    2
    @instr_text     paddw_text, 5
    jmp     pack_mmx_rm_common

  _paddd:
    @instr_bytes    2
    @instr_text     paddd_text, 5
    jmp     pack_mmx_rm_common

  _paddsb:
    @instr_bytes    2
    @instr_text     paddsb_text, 6
    jmp     pack_mmx_rm_common

  _paddsw:
    @instr_bytes    2
    @instr_text     paddsw_text, 6
    jmp     pack_mmx_rm_common

  _paddusb:
    @instr_bytes    2
    @instr_text     paddusb_text, 7
    jmp     pack_mmx_rm_common

  _paddusw:
    @instr_bytes    2
    @instr_text     paddusw_text, 7
    jmp     pack_mmx_rm_common

  _pand:
    @instr_bytes    2
    @instr_text     pand_text, 4
    jmp     pack_mmx_rm_common

  _pandn:
    @instr_bytes    2
    @instr_text     pandn_text, 5
    jmp     pack_mmx_rm_common

  _pcmpeqb:
    @instr_bytes    2
    @instr_text     pcmpeqb_text, 7
    jmp     pack_mmx_rm_common

  _pcmpeqw:
    @instr_bytes    2
    @instr_text     pcmpeqw_text, 7
    jmp     pack_mmx_rm_common

  _pcmpeqd:
    @instr_bytes    2
    @instr_text     pcmpeqd_text, 7
    jmp     pack_mmx_rm_common

  _pcmpgtb:
    @instr_bytes    2
    @instr_text     pcmpgtb_text, 7
    jmp     pack_mmx_rm_common

  _pcmpgtd:
    @instr_bytes    2
    @instr_text     pcmpgtd_text, 7
    jmp     pack_mmx_rm_common

  _pcmpgtw:
    @instr_bytes    2
    @instr_text     pcmpgtw_text, 7
    jmp     pack_mmx_rm_common

  _pmaddwd:
    @instr_bytes    2
    @instr_text     pmaddwd_text, 7
    jmp     pack_mmx_rm_common

  _pmulhw:
    @instr_bytes    2
    @instr_text     pmulhw_text, 6
    jmp     pack_mmx_rm_common

  _pmullw:
    @instr_bytes    2
    @instr_text     pmullw_text, 6
    jmp     pack_mmx_rm_common

  _pop_mem:
    @instr_bytes    1
    @instr_text     pop_text, 3
    call    determine_standard_operand_size
    call    extract_mod_rm
    jmp     store_instruction

  _pop_ds:
    @instr_bytes    1
    mov     bl,011b
  _pop_xs_common:
    @instr_text     pop_text, 3
    call    start_offsets
    mov     fs:special_reg,_SEG_REGS
    call    store_gp_register
    call    end_offsets
    jmp     store_instruction

  _pop_es:
    @instr_bytes    1
    xor     bl,bl
    jmp     _pop_xs_common

  _pop_fs:
    @instr_bytes    2
    mov     bl,100b
    jmp     _pop_xs_common

  _pop_gs:
    @instr_bytes    2
    mov     bl,101b
    jmp     _pop_xs_common

  _pop_ss:
    @instr_bytes    1
    mov     bl,010b
    jmp     _pop_xs_common

  _pop_xax:
  _pop_xbp:
  _pop_xbx:
  _pop_xcx:
  _pop_xdi:
  _pop_xdx:
  _pop_xsi:
  _pop_xsp:
    @instr_bytes    1
    @instr_text     pop_text, 3
    call    start_offsets
    and     eax,111b
    call    determine_standard_operand_size
    mov     bl,al
    call    store_gp_register
    call    end_offsets
    jmp     store_instruction

  _popa:
    @instr_bytes    1
    .IF ((fs:cpu_mode == 0 && fs:op_size_override != 0) || (fs:cpu_mode != 0 && fs:op_size_override == 0))
        @instr_text     popa_text, 4
    .ELSE
        @instr_text     popad_text, 5
    .ENDIF
    jmp     store_instruction

  _popf:
    @instr_bytes    1
    .IF ((fs:cpu_mode == 0 && fs:op_size_override != 0) || (fs:cpu_mode != 0 && fs:op_size_override == 0))
        @instr_text     popf_text, 4
    .ELSE
        @instr_text     popfd_text, 5
    .ENDIF
    jmp     store_instruction

  _por:
    @instr_bytes    2
    @instr_text     por_text, 3
    jmp     pack_mmx_rm_common

  _pslld:
    @instr_bytes    2
    @instr_text     pslld_text, 5
    jmp     pack_mmx_rm_common

  _psllq:
    @instr_bytes    2
    @instr_text     psllq_text, 5
    jmp     pack_mmx_rm_common

  _psllw:
    @instr_bytes    2
    @instr_text     psllw_text, 5
    jmp     pack_mmx_rm_common

  _psrad:
    @instr_bytes    2
    @instr_text     psrad_text, 5
    jmp     pack_mmx_rm_common

  _psrad_immed8:
    @instr_bytes    2
    @instr_text     psrad_text, 5
  psrax_immed8_common:
    call    start_offsets
    mov     fs:special_reg,_MMX_REGS
    call    extract_mod_rm
    call    store_comma
    call    store_8_bit_value
    call    end_offsets
    jmp     store_instruction

  _psraw:
    @instr_bytes    2
    @instr_text     psraw_text, 5
    jmp     pack_mmx_rm_common

  _psraw_immed8:
    @instr_bytes    2
    @instr_text     psraw_text, 5
    jmp     psrax_immed8_common

  _psrld:
    @instr_bytes    2
    @instr_text     psrld_text, 5
    jmp     pack_mmx_rm_common

  _psrlq:
    @instr_bytes    2
    @instr_text     psrlq_text, 5
    jmp     pack_mmx_rm_common

  _psrlw:
    @instr_bytes    2
    @instr_text     psrlw_text, 5
    jmp     pack_mmx_rm_common

  _psubb:
    @instr_bytes    2
    @instr_text     psubb_text, 5
    jmp     pack_mmx_rm_common

  _psubd:
    @instr_bytes    2
    @instr_text     psubd_text, 5
    jmp     pack_mmx_rm_common

  _psubsb:
    @instr_bytes    2
    @instr_text     psubsb_text, 6
    jmp     pack_mmx_rm_common

  _psubsw:
    @instr_bytes    2
    @instr_text     psubsw_text, 6
    jmp     pack_mmx_rm_common

  _psubusb:
    @instr_bytes    2
    @instr_text     psubusb_text, 7
    jmp     pack_mmx_rm_common

  _psubusw:
    @instr_bytes    2
    @instr_text     psubusw_text, 7
    jmp     pack_mmx_rm_common

  _psubw:
    @instr_bytes    2
    @instr_text     psubw_text, 5
    jmp     pack_mmx_rm_common

  _punpckhbw:
    @instr_bytes    2
    @instr_text     punpckhbw_text, 9
    jmp     pack_mmx_rm_common

  _punpckhwd:
    @instr_bytes    2
    @instr_text     punpckhwd_text, 9
    jmp     pack_mmx_rm_common

  _punpckhdq:
    @instr_bytes    2
    @instr_text     punpckhdq_text, 9
    jmp     pack_mmx_rm_common

  _punpcklbw:
    @instr_bytes    2
    @instr_text     punpcklbw_text, 9
    jmp     pack_mmx_rm_common

  _punpcklwd:
    @instr_bytes    2
    @instr_text     punpcklwd_text, 9
    jmp     pack_mmx_rm_common

  _punpckldq:
    @instr_bytes    2
    @instr_text     punpckldq_text, 9
    jmp     pack_mmx_rm_common

  _push_immed16_32:
    @instr_bytes    1
    @instr_text     push_text, 4
    call    start_offsets
    call    determine_standard_operand_size
    call    store_signed_value
    call    end_offsets
    jmp     store_instruction

  _push_immed8:
    @instr_bytes    1
    @instr_text     push_text, 4
    call    start_offsets
    mov     al,byte ptr ds:[esi]
    call    convert_al_to_hex
    mov     word ptr fs:[edi],ax
    add     edi,2
    inc     esi
    inc     fs:instruction_bytes
    .IF ((fs:cpu_mode == 0 && fs:op_size_override != 0) || (fs:cpu_mode != 0 && fs:op_size_override == 0))
        push    dword ptr offset sx_to_word_text
    .ELSE
        push    dword ptr offset sx_to_dword_text
    .ENDIF
    call    store_string
    call    end_offsets
    jmp     store_instruction

  _push_rm:
    @instr_bytes    1
    @instr_text     push_text, 4
    call    determine_standard_operand_size
    call    extract_mod_rm
    jmp     store_instruction

  _push_cs:
    @instr_bytes    1
    mov     bl,001b
  _push_xs_common:
    @instr_text     push_text, 4
    call    start_offsets
    mov     fs:special_reg,_SEG_REGS
    call    store_gp_register
    call    end_offsets
    jmp     store_instruction

  _push_ds:
    @instr_bytes    1
    mov     bl,011b
    jmp     _push_xs_common

  _push_es:
    @instr_bytes    1
    mov     bl,000b
    jmp     _push_xs_common

  _push_fs:
    @instr_bytes    2
    mov     bl,100b
    jmp     _push_xs_common

  _push_gs:
    @instr_bytes    2
    mov     bl,101b
    jmp     _push_xs_common

  _push_ss:
    @instr_bytes    1
    mov     bl,010b
    jmp     _push_xs_common

  _push_xax:
  _push_xbp:
  _push_xbx:
  _push_xcx:
  _push_xdi:
  _push_xdx:
  _push_xsi:
  _push_xsp:
    @instr_bytes    1
    @instr_text     push_text, 4
    call    start_offsets
    and     eax,111b
    call    determine_standard_operand_size
    mov     bl,al
    call    store_gp_register
    call    end_offsets
    jmp     store_instruction

  _pusha:
    @instr_bytes    1
    .IF ((fs:cpu_mode == 0 && fs:op_size_override != 0) || (fs:cpu_mode != 0 && fs:op_size_override == 0))
        @instr_text     pusha_text, 5
    .ELSE
        @instr_text     pushad_text, 6
    .ENDIF
    jmp     store_instruction

  _pushf:
    @instr_bytes    1
    .IF ((fs:cpu_mode == 0 && fs:op_size_override != 0) || (fs:cpu_mode != 0 && fs:op_size_override == 0))
        @instr_text     pushf_text, 5
    .ELSE
        @instr_text     pushfd_text, 6
    .ENDIF
    jmp     store_instruction

  _pxor:
    @instr_bytes    2
    @instr_text     pxor_text, 4
    jmp     pack_mmx_rm_common

  _rol_rm8_immed8:
    @instr_bytes    1
    @instr_text     rol_text, 3
  rxx_rm8_immed8_common:
    mov     fs:operand_size,8
    call    extract_mod_rm
    call    store_comma
    call    store_8_bit_signed_value
    jmp     store_instruction

  _ror_rm8_immed8:
    @instr_bytes    1
    @instr_text     ror_text, 3
    jmp     rxx_rm8_immed8_common

  _rcl_rm8_immed8:
    @instr_bytes    1
    @instr_text     rcl_text, 3
    jmp     rxx_rm8_immed8_common

  _rcr_rm8_immed8:
    @instr_bytes    1
    @instr_text     rcr_text, 3
    jmp     rxx_rm8_immed8_common

  _rol_immed8:
    @instr_bytes    1
    @instr_text     rol_text, 3
  rxx_rm_immed8_common:
    call    determine_standard_operand_size
    call    extract_mod_rm
    call    store_comma
    call    store_8_bit_signed_value
    jmp     store_instruction

  _ror_immed8:
    @instr_bytes    1
    @instr_text     ror_text, 3
    jmp     rxx_rm_immed8_common

  _rcl_immed8:
    @instr_bytes    1
    @instr_text     rcl_text, 3
    jmp     rxx_rm_immed8_common

  _rcr_immed8:
    @instr_bytes    1
    @instr_text     rcr_text, 3
    jmp     rxx_rm_immed8_common

  _rol_rm8_1:
    @instr_bytes    1
    @instr_text     rol_text, 3
  rxx_rm8_1_common:
    mov     fs:operand_size,8
    call    extract_mod_rm
    call    store_comma_one
    jmp     store_instruction

  _ror_rm8_1:
    @instr_bytes    1
    @instr_text     ror_text, 3
    jmp     rxx_rm8_1_common

  _rcl_rm8_1:
    @instr_bytes    1
    @instr_text     rcl_text, 3
    jmp     rxx_rm8_1_common

  _rcr_rm8_1:
    @instr_bytes    1
    @instr_text     rcr_text, 3
    jmp     rxx_rm8_1_common

  _rol_rm_1:
    @instr_bytes    1
    @instr_text     rol_text, 3
  rxx_rm_1_common:
    call    determine_standard_operand_size
    call    extract_mod_rm
    call    store_comma_one
    jmp     store_instruction

  _ror_rm_1:
    @instr_bytes    1
    @instr_text     ror_text, 3
    jmp     rxx_rm_1_common

  _rcl_rm_1:
    @instr_bytes    1
    @instr_text     rcl_text, 3
    jmp     rxx_rm_1_common

  _rcr_rm_1:
    @instr_bytes    1
    @instr_text     rcr_text, 3
    jmp     rxx_rm_1_common

  _rol_rm8_cl:
    @instr_bytes    1
    @instr_text     rol_text, 3
  _rxx_rm8_cl_common:
    mov     fs:operand_size,8
    call    extract_mod_rm
    call    store_comma_cl
    jmp     store_instruction

  _ror_rm8_cl:
    @instr_bytes    1
    @instr_text     ror_text, 3
    jmp     _rxx_rm8_cl_common

  _rcl_rm8_cl:
    @instr_bytes    1
    @instr_text     rcl_text, 3
    jmp     _rxx_rm8_cl_common

  _rcr_rm8_cl:
    @instr_bytes    1
    @instr_text     rcr_text, 3
    jmp     _rxx_rm8_cl_common

  _rol_rm_cl:
    @instr_bytes    1
    @instr_text     rol_text, 3
  rxx_rm_cl_common:
    call    determine_standard_operand_size
    call    extract_mod_rm
    call    store_comma_cl
    jmp     store_instruction

  _ror_rm_cl:
    @instr_bytes    1
    @instr_text     ror_text, 3
    jmp     rxx_rm_cl_common

  _rcl_rm_cl:
    @instr_bytes    1
    @instr_text     rcl_text, 3
    jmp     rxx_rm_cl_common

  _rcr_rm_cl:
    @instr_bytes    1
    @instr_text     rcr_text, 3
    jmp     rxx_rm_cl_common

  _rdmsr:
    @instr_bytes    2
    @instr_text     rdmsr_text, 5
    jmp     store_instruction

  _rdpmc:
    @instr_bytes    2
    @instr_text     rdpmc_text, 5
    jmp     store_instruction

  _rdtsc:
    @instr_bytes    2
    @instr_text     rdtsc_text, 5
    jmp     store_instruction

  _repe_prefix:
    @instr_bytes    1
    @instr_text     rep_text, 3
    jmp     store_instruction

  _repne_prefix:
    @instr_bytes    1
    @instr_text     repne_text, 5
    jmp     store_instruction

  _retf:
    @instr_bytes    1
    @instr_text     retf_text, 4
    jmp     store_instruction

  _retf_immed:
    @instr_bytes    1
    @instr_text     retf_text, 4
  retx_immed16_common:
    call    start_offsets
    call    store_16_bit_value
    call    end_offsets
    jmp     store_instruction

  _retn:
    @instr_bytes    1
    @instr_text     ret_text, 3
    jmp     store_instruction

  _retn_immed:
    @instr_bytes    1
    @instr_text     ret_text, 3
    jmp     retx_immed16_common

  _rsm:
    @instr_bytes    2
    @instr_text     rsm_text, 3
    jmp     store_instruction

  _sahf:
    @instr_bytes    1
    @instr_text     sahf_text, 4
    jmp     store_instruction

  _sbb_rm_reg8:
    mov     dword ptr fs:xxx_text,' bbs'
    jmp     _xxx_rm_reg8

  _sbb_rm_reg16_32:
    mov     dword ptr fs:xxx_text,' bbs'
    jmp     _xxx_rm_reg16_32

  _sbb_reg8_rm:
    mov     dword ptr fs:xxx_text,' bbs'
    jmp     _xxx_reg8_rm

  _sbb_reg16_32_rm:
    mov     dword ptr fs:xxx_text,' bbs'
    jmp     _xxx_reg16_32_rm

  _sbb_accum_immed8:
    mov     dword ptr fs:xxx_text,' bbs'
    jmp     _xxx_accum_immed8

  _sbb_accum_immed16_32:
    mov     dword ptr fs:xxx_text,' bbs'
    jmp     _xxx_accum_immed16_32

  _sbb_rm8_immed8:
    mov     dword ptr fs:xxx_text,' bbs'
    jmp     _xxx_rm8_immed8

  _sbb_rm_immed:
    mov     dword ptr fs:xxx_text,' bbs'
    jmp     _xxx_rm_immed

  _sbb_rm16_32_immed8:
    mov     dword ptr fs:xxx_text,' bbs'
    jmp     _xxx_rm16_32_immed8

  _sub_rm_reg8:
    mov     dword ptr fs:xxx_text,' bus'
    jmp     _xxx_rm_reg8

  _sub_rm_reg16_32:
    mov     dword ptr fs:xxx_text,' bus'
    jmp     _xxx_rm_reg16_32

  _sub_reg8_rm:
    mov     dword ptr fs:xxx_text,' bus'
    jmp     _xxx_reg8_rm

  _sub_reg16_32_rm:
    mov     dword ptr fs:xxx_text,' bus'
    jmp     _xxx_reg16_32_rm

  _sub_accum_immed8:
    mov     dword ptr fs:xxx_text,' bus'
    jmp     _xxx_accum_immed8

  _sub_accum_immed16_32:
    mov     dword ptr fs:xxx_text,' bus'
    jmp     _xxx_accum_immed16_32

  _sub_rm8_immed8:
    mov     dword ptr fs:xxx_text,' bus'
    jmp     _xxx_rm8_immed8

  _sub_rm_immed:
    mov     dword ptr fs:xxx_text,' bus'
    jmp     _xxx_rm_immed

  _xor_rm_reg8:
    mov     dword ptr fs:xxx_text,' rox'
    jmp     _xxx_rm_reg8

  _xor_rm_reg16_32:
    mov     dword ptr fs:xxx_text,' rox'
    jmp     _xxx_rm_reg16_32

  _xor_reg8_rm:
    mov     dword ptr fs:xxx_text,' rox'
    jmp     _xxx_reg8_rm

  _xor_reg16_32_rm:
    mov     dword ptr fs:xxx_text,' rox'
    jmp     _xxx_reg16_32_rm

  _xor_accum_immed8:
    mov     dword ptr fs:xxx_text,' rox'
    jmp     _xxx_accum_immed8

  _xor_accum_immed16_32:
    mov     dword ptr fs:xxx_text,' rox'
    jmp     _xxx_accum_immed16_32

  _xor_rm8_immed8:
    mov     dword ptr fs:xxx_text,' rox'
    jmp     _xxx_rm8_immed8

  _xor_rm_immed:
    mov     dword ptr fs:xxx_text,' rox'
    jmp     _xxx_rm_immed

  _sub_rm16_32_immed8:
    mov     dword ptr fs:xxx_text,' bus'
    jmp     _xxx_rm16_32_immed8

  _xxx_rm_reg8:
    @instr_bytes    1
    @instr_text     xxx_text, 3
    mov     fs:operand_size,8
    call    extract_mod_reg_rm
    jmp     store_instruction

  _xxx_rm_reg16_32:
    @instr_bytes    1
    @instr_text     xxx_text, 3
    call    determine_standard_operand_size
    call    extract_mod_reg_rm
    jmp     store_instruction

  _xxx_reg8_rm:
    @instr_bytes    1
    @instr_text     xxx_text, 3
    mov     fs:operand_size,8
    mov     fs:reverse_mod_reg_rm,1
    call    extract_mod_reg_rm
    jmp     store_instruction

  _xxx_reg16_32_rm:
    @instr_bytes    1
    @instr_text     xxx_text, 3
    mov     fs:reverse_mod_reg_rm,1
    call    determine_standard_operand_size
    call    extract_mod_reg_rm
    jmp     store_instruction

  _xxx_accum_immed8:
    @instr_bytes    1
    @instr_text     xxx_text, 3
    mov     fs:operand_size,8
    call    start_offsets
    xor     bl,bl
    call    store_gp_register
    call    store_comma
    call    store_8_bit_signed_value
    call    end_offsets
    jmp     store_instruction

  _xxx_accum_immed16_32:
    @instr_bytes    1
    @instr_text     xxx_text, 3
    call    determine_standard_operand_size
    call    start_offsets
    xor     bl,bl
    call    store_gp_register
    call    store_comma
    call    store_signed_value
    call    end_offsets
    jmp     store_instruction

  _xxx_rm8_immed8:
    @instr_bytes    1
    @instr_text     xxx_text, 3
    mov     fs:operand_size,8
    call    start_offsets
    call    extract_mod_rm
    call    store_comma
    call    store_8_bit_signed_value
    call    end_offsets
    jmp     store_instruction

  _xxx_rm_immed:
    @instr_bytes    1
    @instr_text     xxx_text, 3
    call    determine_standard_operand_size
    call    start_offsets
    call    extract_mod_rm
    call    store_comma
    call    store_signed_value
    call    end_offsets
    jmp     store_instruction

  _xxx_rm16_32_immed8:
    @instr_bytes    1
    @instr_text     xxx_text, 3
    call    determine_standard_operand_size
    call    start_offsets
    call    extract_mod_rm
    call    store_comma
    call    store_8_bit_signed_value
    call    end_offsets
    jmp     store_instruction

  _scasb:
    @instr_bytes    1
    @instr_text     scasb_text, 5
    jmp     store_instruction

  _scasw:
    @instr_bytes    1
    .IF ((fs:cpu_mode == 0 && fs:op_size_override != 0) || (fs:cpu_mode != 0 && fs:op_size_override == 0))
        @instr_text     scasw_text, 5
    .ELSE
        @instr_text     scasd_text, 5
    .ENDIF
    jmp     store_instruction

  _seto:
    @instr_bytes    2
    @instr_text     seto_text, 4
  setxx_common:
    mov     fs:operand_size,8
    call    extract_mod_rm
    jmp     store_instruction

  _setno:
    @instr_bytes    2
    @instr_text     setno_text, 5
    jmp     setxx_common

  _setc:
    @instr_bytes    2
    @instr_text     setc_text, 4
    jmp     setxx_common

  _setnc:
    @instr_bytes    2
    @instr_text     setnc_text, 5
    jmp     setxx_common

  _setz:
    @instr_bytes    2
    @instr_text     setz_text, 4
    jmp     setxx_common

  _setnz:
    @instr_bytes    2
    @instr_text     setnz_text, 5
    jmp     setxx_common

  _setna:
    @instr_bytes    2
    @instr_text     setna_text, 5
    jmp     setxx_common

  _seta:
    @instr_bytes    2
    @instr_text     seta_text, 4
    jmp     setxx_common

  _sets:
    @instr_bytes    2
    @instr_text     sets_text, 4
    jmp     setxx_common

  _setns:
    @instr_bytes    2
    @instr_text     setns_text, 5
    jmp     setxx_common

  _setpe:
    @instr_bytes    2
    @instr_text     setpe_text, 5
    jmp     setxx_common

  _setpo:
    @instr_bytes    2
    @instr_text     setpo_text, 5
    jmp     setxx_common

  _setl:
    @instr_bytes    2
    @instr_text     setl_text, 4
    jmp     setxx_common

  _setnl:
    @instr_bytes    2
    @instr_text     setnl_text, 5
    jmp     setxx_common

  _setng:
    @instr_bytes    2
    @instr_text     setng_text, 5
    jmp     setxx_common

  _setg:
    @instr_bytes    2
    @instr_text     setg_text, 4
    jmp     setxx_common

  _sgdt_label:
    @instr_bytes    2
    @instr_text     sgdt_text, 4
    jmp     setxx_common

  _sidt_label:
    @instr_bytes    2
    @instr_text     sidt_text, 4
    jmp     setxx_common

  _sldt:
    @instr_bytes    2
    @instr_text     sldt_text, 4
    jmp     xldt_common

  _shl_rm8_immed8:
    @instr_bytes    1
    @instr_text     shl_text, 3
  sxx_rm8_immed8_common:
    mov     fs:operand_size,8
    call    extract_mod_rm
    call    store_comma
    call    store_8_bit_signed_value
    jmp     store_instruction

  _shr_rm8_immed8:
    @instr_bytes    1
    @instr_text     shr_text, 3
    jmp     sxx_rm8_immed8_common

  _sar_rm8_immed8:
    @instr_bytes    1
    @instr_text     sar_text, 3
    jmp     sxx_rm8_immed8_common

  _shl_immed8:
    @instr_bytes    1
    @instr_text     shl_text, 3
  sxx_rm_immed8_common:
    call    determine_standard_operand_size
    call    extract_mod_rm
    call    store_comma
    call    store_8_bit_signed_value
    jmp     store_instruction

  _shr_immed8:
    @instr_bytes    1
    @instr_text     shr_text, 3
    jmp     sxx_rm_immed8_common

  _sar_immed8:
    @instr_bytes    1
    @instr_text     sar_text, 3
    jmp     sxx_rm_immed8_common

  _shl_rm8_1:
    @instr_bytes    1
    @instr_text     shl_text, 3
  sxx_rm8_1_common:
    mov     fs:operand_size,8
    call    extract_mod_rm
    call    store_comma_one
    jmp     store_instruction

  _shr_rm8_1:
    @instr_bytes    1
    @instr_text     shr_text, 3
    jmp     sxx_rm8_1_common

  _sar_rm8_1:
    @instr_bytes    1
    @instr_text     sar_text, 3
    jmp     sxx_rm8_1_common

  _shl_rm_1:
    @instr_bytes    1
    @instr_text     shl_text, 3
  sxx_rm_1_common:
    call    determine_standard_operand_size
    call    extract_mod_rm
    call    store_comma_one
    jmp     store_instruction

  _shr_rm_1:
    @instr_bytes    1
    @instr_text     shr_text, 3
    jmp     sxx_rm_1_common

  _sar_rm_1:
    @instr_bytes    1
    @instr_text     sar_text, 3
    jmp     sxx_rm_1_common

  _shl_rm8_cl:
    @instr_bytes    1
    @instr_text     shl_text, 3
  _sxx_rm8_cl_common:
    mov     fs:operand_size,8
    call    extract_mod_rm
    call    store_comma_cl
    jmp     store_instruction

  _shr_rm8_cl:
    @instr_bytes    1
    @instr_text     shr_text, 3
    jmp     _sxx_rm8_cl_common

  _sar_rm8_cl:
    @instr_bytes    1
    @instr_text     sar_text, 3
    jmp     _sxx_rm8_cl_common

  _shl_rm_cl:
    @instr_bytes    1
    @instr_text     shl_text, 3
  sxx_rm_cl_common:
    call    determine_standard_operand_size
    call    extract_mod_rm
    call    store_comma_cl
    jmp     store_instruction

  _shr_rm_cl:
    @instr_bytes    1
    @instr_text     shr_text, 3
    jmp     sxx_rm_cl_common

  _sar_rm_cl:
    @instr_bytes    1
    @instr_text     sar_text, 3
    jmp     sxx_rm_cl_common

  _shld_cl:
    @instr_bytes    2
    @instr_text     shld_text, 4
  shxd_cl_common:
    call    determine_standard_operand_size
    call    start_offsets
    call    extract_mod_reg_rm
    call    store_comma
    mov     bl,01b
    mov     fs:operand_size,8
    call    store_gp_register
    call    end_offsets
    mov     fs:operand_size,0
    jmp     store_instruction

  _shld_immed:
    @instr_bytes    2
    @instr_text     shld_text, 4
  shxd_immed_common:
    call    determine_standard_operand_size
    call    start_offsets
    call    extract_mod_reg_rm
    call    store_comma
    call    store_8_bit_value
    call    end_offsets
    mov     fs:operand_size,0
    jmp     store_instruction

  _shrd_cl:
    @instr_bytes    2
    @instr_text     shrd_text, 4
    jmp     shxd_cl_common

  _shrd_immed:
    @instr_bytes    2
    @instr_text     shrd_text, 4
    jmp     shxd_immed_common

  _smsw:
    @instr_bytes    2
    @instr_text     smsw_text, 4
    call    determine_standard_operand_size
    call    extract_mod_rm
    jmp     store_instruction

  _stc:
    @instr_bytes    1
    @instr_text     stc_text, 3
    jmp     store_instruction

  _std:
    @instr_bytes    1
    @instr_text     std_text, 3
    jmp     store_instruction

  _sti:
    @instr_bytes    1
    @instr_text     sti_text, 3
    jmp     store_instruction

  _str:
    @instr_bytes    2
    @instr_text     str_text, 3
    mov     fs:operand_size,16
    call    extract_mod_rm
    jmp     store_instruction

  _stosb:
    @instr_bytes    1
    @instr_text     stosb_text, 5
    jmp     store_instruction

  _stosw:
    @instr_bytes    1
    .IF ((fs:cpu_mode == 0 && fs:op_size_override != 0) || (fs:cpu_mode != 0 && fs:op_size_override == 0))
        @instr_text     stosw_text, 5
    .ELSE
        @instr_text     stosd_text, 5
    .ENDIF
    jmp     store_instruction

  _test_rm_reg_8:
    @instr_bytes    1
    @instr_text     test_text, 4
    mov     fs:operand_size,8
    call    extract_mod_reg_rm
    jmp     store_instruction

  _test_rm_reg16_32:
    @instr_bytes    1
    @instr_text     test_text, 4
    call    determine_standard_operand_size
    call    extract_mod_reg_rm
    jmp     store_instruction

  _test_accum_imm8:
    @instr_bytes    1
    @instr_text     test_text, 4
    mov     fs:operand_size,8
    call    start_offsets
    xor     bl,bl
    call    store_gp_register
    call    store_comma
    call    store_8_bit_signed_value
    call    end_offsets
    jmp     store_instruction

  _test_accum_imm16_32:
    @instr_bytes    1
    @instr_text     test_text, 4
    call    determine_standard_operand_size
    call    start_offsets
    xor     bl,bl
    call    store_gp_register
    call    store_comma
    call    store_signed_value
    call    end_offsets
    jmp     store_instruction

  _test_rm_imm8:
    @instr_bytes    1
    @instr_text     test_text, 4
    mov     fs:operand_size,8
    call    start_offsets
    call    extract_mod_rm
    call    store_comma
    call    store_8_bit_signed_value
    call    end_offsets
    jmp     store_instruction

  _test_rm_imm16_32:
    @instr_bytes    1
    @instr_text     test_text, 4
    call    determine_standard_operand_size
    call    start_offsets
    call    extract_mod_rm
    call    store_comma
    call    store_signed_value
    call    end_offsets
    jmp     store_instruction

  _ud2_f0b:
    @instr_bytes    2
    @instr_text     ud2_0f0b_text, 8
    jmp     store_instruction

  _ud2_fb9:
    @instr_bytes    2
    @instr_text     ud2_0fb9_text, 8
    jmp     store_instruction

  _verr:
    @instr_bytes    2
    @instr_text     verr_text, 4
    mov     fs:operand_size,16
    call    extract_mod_rm
    jmp     store_instruction

  _verw:
    @instr_bytes    2
    @instr_text     verw_text, 4
    mov     fs:operand_size,16
    call    extract_mod_rm
    jmp     store_instruction

  _wait:
    @instr_bytes    1
    @instr_text     wait_text, 4
    jmp     store_instruction

  _wbinvd:
    @instr_bytes    1
    @instr_text     wbinvd_text, 6
    jmp     store_instruction

  _wrmsr:
    @instr_bytes    2
    @instr_text     wrmsr_text, 5
    jmp     store_instruction

  _xadd_byte:
    @instr_bytes    2
    @instr_text     xadd_text, 4
    mov     fs:operand_size,8
    call    extract_mod_reg_rm
    jmp     store_instruction

  _xadd:
    @instr_bytes    2
    @instr_text     xadd_text, 4
    call    determine_standard_operand_size
    call    extract_mod_reg_rm
    jmp     store_instruction

  _xchg_byte:
    @instr_bytes    1
    @instr_text     xchg_text, 4
    mov     fs:operand_size,8
    call    extract_mod_reg_rm
    jmp     store_instruction

  _xchg:
    @instr_bytes    1
    @instr_text     xchg_text, 4
    call    determine_standard_operand_size
    call    extract_mod_reg_rm
    jmp     store_instruction

  _xchg_xbp:
  _xchg_xbx:
  _xchg_xcx:
  _xchg_xdi:
  _xchg_xdx:
  _xchg_xsi:
  _xchg_xsp:
    @instr_bytes    1
    @instr_text     xchg_text, 4
    call    determine_standard_operand_size
    call    start_offsets
    and     al,111b
    mov     bl,al
    call    store_gp_register
    call    store_comma
    xor     bl,bl
    call    store_gp_register
    jmp     store_instruction

  _xlat:
    @instr_bytes    1
    @instr_text     xlat_text, 4
    jmp     store_instruction

  _check_reg_80:
  ; Check the REG portion of the Mod/Reg/RM byte
    movzx   eax,byte ptr ds:[esi+1]
    shr     eax,3
    and     eax,111b
    .IF (al == 000b)
      ; It's ADD r/m8,imm8
        jmp     _add_rm_immed8
    .ELSEIF (al == 001b)
      ; It's OR r/m8,immed8
        jmp     _or_rm_immed8
    .ELSEIF (al == 010b)
      ; It's ADC r/m8,imm8
        jmp     _adc_rm_immed8
    .ELSEIF (al == 011b)
      ; It's SBB r/m8,imm8
        mov     dword ptr fs:xxx_text,' bbs'
        jmp     _xxx_rm8_immed8
    .ELSEIF (al == 100b)
      ; It's AND r/m8,imm8
        jmp     _and_rm_immed8
    .ELSEIF (al == 101b)
      ; It's SUB r/m8,imm8
        mov     dword ptr fs:xxx_text,' bus'
        jmp     _xxx_rm8_immed8
    .ELSEIF (al == 110b)
      ; It's XOR r/m8,imm8
        mov     dword ptr fs:xxx_text,' rox'
        jmp     _xxx_rm8_immed8
    .ELSEIF (al == 111b)
      ; It's CMP r/m8,imm8
        jmp     _cmp_rm_immed8
    .ENDIF
    jmp    _unused

  _check_reg_81:
  ; Check the REG portion of the Mod/Reg/RM byte
    movzx   eax,byte ptr ds:[esi+1]
    shr     eax,3
    and     eax,111b
    .IF (al == 000b)
      ; It's ADD r/m16,imm16
      ; or   ADD r/m32,imm32
        jmp     _add_rm_immed16_32
    .ELSEIF (al == 001b)
      ; It's OR r/m16,immed16
      ; or   OR r/m32,immed32
        jmp     _or_rm_immed16_32
    .ELSEIF (al == 010b)
      ; It's ADC r/m16,imm16
      ; or   ADC r/m32,imm32
        jmp     _adc_rm_immed16_32
    .ELSEIF (al == 011b)
      ; It's SBB r/m16,imm16
      ; or   SBB r/m32,imm32
        mov     dword ptr fs:xxx_text,' bbs'
        jmp     _xxx_rm_immed
    .ELSEIF (al == 100b)
      ; It's AND r/m16,imm16
      ; or   AND r/m32,imm32
        jmp     _and_rm_immed16_32
    .ELSEIF (al == 101b)
      ; It's SUB r/m16,imm16
      ; or   SUB r/m32,imm32
        mov     dword ptr fs:xxx_text,' bus'
        jmp     _xxx_rm_immed
    .ELSEIF (al == 110b)
      ; It's XOR r/m16,imm16
      ; or   XOR r/m32,imm32
        mov     dword ptr fs:xxx_text,' rox'
        jmp     _xxx_rm_immed
    .ELSEIF (al == 111b)
      ; It's CMP r/m16,imm16
      ; or   CMP r/m32,imm32
        jmp     _cmp_rm_immed16_32
    .ENDIF
    jmp    _unused

  _check_reg_82:
  ; Check the REG portion of the Mod/Reg/RM byte
    movzx   eax,byte ptr ds:[esi+1]
    shr     eax,3
    and     eax,111b
;    .IF (eax == 010b)
        jmp    _unused
;    .ENDIF

  _check_reg_83:
  ; Check the REG portion of the Mod/Reg/RM byte
    movzx   eax,byte ptr ds:[esi+1]
    shr     eax,3
    and     eax,111b
    .IF (al == 000b)
      ; It's ADD r/m16,imm8
      ; or   ADD r/m32,imm8
        jmp     _add_rm_16_32_with_immed8
    .ELSEIF (al == 001b)
      ; It's OR r/m16,immed8
      ; or   OR r/m32,immed8
        jmp     _or_rm_16_32_with_immed8
    .ELSEIF (al == 010b)
      ; It's ADC r/m16,immed8
      ; or   ADC r/m32,immed8
        jmp     _adc_rm_16_32_with_immed8
    .ELSEIF (al == 011b)
      ; It's SBB r/m16,immed8
      ; or   SBB r/m32,immed8
        mov     dword ptr fs:xxx_text,' bbs'
        jmp     _xxx_rm16_32_immed8
    .ELSEIF (al == 100b)
      ; It's AND r/m16,immed8
      ; or   AND r/m32,immed8
        jmp     _and_rm_16_32_with_immed8
    .ELSEIF (al == 101b)
      ; It's SUB r/m16,immed8
      ; or   SUB r/m32,immed8
        mov     dword ptr fs:xxx_text,' bus'
        jmp     _xxx_rm16_32_immed8
    .ELSEIF (al == 110b)
      ; It's XOR r/m16,immed8
      ; or   XOR r/m32,immed8
        mov     dword ptr fs:xxx_text,' rox'
        jmp     _xxx_rm16_32_immed8
    .ELSE
      ; It's CMP r/m16,immed8
      ; or   CMP r/m32,immed8
        jmp     _cmp_rm_16_32_with_immed8
    .ENDIF

  _check_reg_8f:
  ; Check the REG portion of the Mod/Reg/RM byte
    movzx   eax,byte ptr ds:[esi+1]
    shr     eax,3
    and     eax,111b
    .IF (al == 000b)
      ; It's pop m16/32
        jmp     _pop_mem
    .ENDIF
    jmp     _unused

  _check_reg_c0:
  ; Check the REG portion of the Mod/Reg/RM byte
    movzx   eax,byte ptr ds:[esi+1]
    shr     eax,3
    and     eax,111b
    .IF (al == 000b)
      ; It's ROL rm8,immed8
        jmp     _rol_rm8_immed8
    .ELSEIF (al == 001b)
      ; It's ROR rm8,immed8
        jmp     _ror_rm8_immed8
    .ELSEIF (al == 010b)
      ; It's RCL rm8,immed8
        jmp     _rcl_rm8_immed8
    .ELSEIF (al == 011b)
      ; It's RCR rm8,immed8
        jmp     _rcr_rm8_immed8
    .ELSEIF (al == 100b)
      ; It's SHL rm8,immed8
        jmp     _shl_rm8_immed8
    .ELSEIF (al == 101b)
      ; It's SHR rm8,immed8
        jmp     _shr_rm8_immed8
    .ELSEIF (al == 111b)
      ; It's SAR rm8,immed8
        jmp     _sar_rm8_immed8
    .ENDIF
    jmp     _unused

  _check_reg_c1:
  ; Check the REG portion of the Mod/Reg/RM byte
    movzx   eax,byte ptr ds:[esi+1]
    shr     eax,3
    and     eax,111b
    .IF (al == 000b)
      ; It's ROL rm16,immed8
      ; or   ROL rm32,immed8
        jmp     _rol_immed8
    .ELSEIF (al == 001b)
      ; It's ROR rm16,immed8
      ; or   ROR rm32,immed8
        jmp     _ror_immed8
    .ELSEIF (al == 010b)
      ; It's RCL rm16,immed8
      ; or   RCL rm32,immed8
        jmp     _rcl_immed8
    .ELSEIF (al == 011b)
      ; It's RCR rm16,immed8
      ; or   RCR rm32,immed8
        jmp     _rcr_immed8
    .ELSEIF (al == 100b)
      ; It's SHL rm16,immed8
      ; or   SHL rm32,immed8
        jmp     _shl_immed8
    .ELSEIF (al == 101b)
      ; It's SHR rm16,immed8
      ; or   SHR rm32,immed8
        jmp     _shr_immed8
    .ELSEIF (al == 111b)
      ; It's SAR rm16,immed8
      ; or   SAR rm32,immed8
        jmp     _sar_immed8
    .ENDIF
    jmp     _unused

  _check_reg_c6:
  ; Check the REG portion of the Mod/Reg/RM byte
    movzx   eax,byte ptr ds:[esi+1]
    shr     eax,3
    and     eax,111b
    .IF (al == 000b)
      ; It's MOV rm8,immed8
        jmp     _mov_rm_immed8
    .ENDIF
    jmp     _unused

  _check_reg_c7:
  ; Check the REG portion of the Mod/Reg/RM byte
    movzx   eax,byte ptr ds:[esi+1]
    shr     eax,3
    and     eax,111b
    .IF (al == 000b)
      ; It's MOV rm16/32,immed16/32
        jmp     _mov_rm_immed16_32
    .ENDIF
    jmp     _unused

  _check_reg_d0:
  ; Check the REG portion of the Mod/Reg/RM byte
    movzx   eax,byte ptr ds:[esi+1]
    shr     eax,3
    and     eax,111b
    .IF (al == 000b)
      ; It's ROL rm8,1
        jmp     _rol_rm8_1
    .ELSEIF (al == 001b)
      ; It's ROR rm8,1
        jmp     _ror_rm8_1
    .ELSEIF (al == 010b)
      ; It's RCL rm8,1
        jmp     _rcl_rm8_1
    .ELSEIF (al == 011b)
      ; It's RCR rm8,1
        jmp     _rcr_rm8_1
    .ELSEIF (al == 100b)
      ; It's SHL rm8,1
        jmp     _shl_rm8_1
    .ELSEIF (al == 101b)
      ; It's SHR rm8,1
        jmp     _shr_rm8_1
    .ELSEIF (al == 111b)
      ; It's SAR rm8,1
        jmp     _sar_rm8_1
    .ENDIF
    jmp     _unused

  _check_reg_d1:
  ; Check the REG portion of the Mod/Reg/RM byte
    movzx   eax,byte ptr ds:[esi+1]
    shr     eax,3
    and     eax,111b
    .IF (al == 000b)
      ; It's ROL rm16,1
      ; or   ROL rm32,1
        jmp     _rol_rm_1
    .ELSEIF (al == 001b)
      ; It's ROR rm16,1
      ; or   ROR rm32,1
        jmp     _ror_rm_1
    .ELSEIF (al == 010b)
      ; It's RCL rm16,1
      ; or   RCL rm32,1
        jmp     _rcl_rm_1
    .ELSEIF (al == 011b)
      ; It's RCR rm16,1
      ; or   RCR rm32,1
        jmp     _rcr_rm_1
    .ELSEIF (al == 100b)
      ; It's SHL rm16,1
      ; or   SHL rm32,1
        jmp     _shl_rm_1
    .ELSEIF (al == 101b)
      ; It's SHR rm16,1
      ; or   SHR rm32,1
        jmp     _shr_rm_1
    .ELSEIF (al == 111b)
      ; It's SAR rm16,1
      ; or   SAR rm32,1
        jmp     _sar_rm_1
    .ENDIF
    jmp     _unused

  _check_reg_d2:
  ; Check the REG portion of the Mod/Reg/RM byte
    movzx   eax,byte ptr ds:[esi+1]
    shr     eax,3
    and     eax,111b
    .IF (al == 000b)
      ; It's ROL rm8,cl
        jmp     _rol_rm8_cl
    .ELSEIF (al == 001b)
      ; It's ROR rm8,cl
        jmp     _ror_rm8_cl
    .ELSEIF (al == 010b)
      ; It's RCL rm8,cl
        jmp     _rcl_rm8_cl
    .ELSEIF (al == 011b)
      ; It's RCR rm8,cl
        jmp     _rcr_rm8_cl
    .ELSEIF (al == 100b)
      ; It's SHL rm8,cl
        jmp     _shl_rm8_cl
    .ELSEIF (al == 101b)
      ; It's SHR rm8,cl
        jmp     _shr_rm8_cl
    .ELSEIF (al == 111b)
      ; It's SAR rm8,cl
        jmp     _sar_rm8_cl
    .ENDIF
    jmp     _unused

  _check_reg_d3:
  ; Check the REG portion of the Mod/Reg/RM byte
    movzx   eax,byte ptr ds:[esi+1]
    shr     eax,3
    and     eax,111b
    .IF (al == 000b)
      ; It's ROL rm16,cl
      ; or   ROL rm32,cl
        jmp     _rol_rm_cl
    .ELSEIF (al == 001b)
      ; It's ROR rm16,cl
      ; or   ROR rm32,cl
        jmp     _ror_rm_cl
    .ELSEIF (al == 010b)
      ; It's RCL rm16,cl
      ; or   RCL rm32,cl
        jmp     _rcl_rm_cl
    .ELSEIF (al == 011b)
      ; It's RCR rm16,cl
      ; or   RCR rm32,cl
        jmp     _rcr_rm_cl
    .ELSEIF (al == 100b)
      ; It's SHL rm16,cl
      ; or   SHL rm32,cl
        jmp     _shl_rm_cl
    .ELSEIF (al == 101b)
      ; It's SHR rm16,cl
      ; or   SHR rm32,cl
        jmp     _shr_rm_cl
    .ELSEIF (al == 111b)
      ; It's SAR rm16,cl
      ; or   SAR rm32,cl
        jmp     _sar_rm_cl
    .ENDIF
    jmp     _unused

  _check_reg_f6:
  ; Check the REG portion of the Mod/Reg/RM byte
    movzx   eax,byte ptr ds:[esi+1]
    shr     eax,3
    and     eax,111b
    .IF (al == 000b)
      ; It's TEST r/m8,immed8
        jmp     _test_rm_imm8
    .ELSEIF (al == 010b)
      ; It's NOT r/m8
        jmp     _not_byte
    .ELSEIF (al == 011b)
      ; It's NEG r/m8
        jmp     _neg_byte
    .ELSEIF (al == 100b)
      ; It's MUL r/m8
        jmp     _mul_byte
    .ELSEIF (al == 101b)
      ; It's IMUL r/m8
        jmp     _imul_byte
    .ELSEIF (al == 110b)
      ; It's DIV r/m8
        jmp     _div_byte
    .ELSEIF (al == 111b)
      ; It's IDIV r/m8
        jmp     _idiv_byte
    .ENDIF
    jmp    _unused

  _check_reg_f7:
  ; Check the REG portion of the Mod/Reg/RM byte
    movzx   eax,byte ptr ds:[esi+1]
    shr     eax,3
    and     eax,111b
    .IF (al == 000b)
      ; It's TEST r/m16,immed16
      ; or   TEST r/m32,immed32
        jmp     _test_rm_imm16_32
    .ELSEIF (al == 011b)
      ; It's NEG r/m16
      ; or   NEG r/m32
        jmp     _neg
    .ELSEIF (al == 010b)
      ; It's NOT r/m16
      ; or   NOT r/m32
        jmp     _not
    .ELSEIF (al == 100b)
      ; It's MUL r/m16
      ; or   MUL r/m32
        jmp     _mul
    .ELSEIF (al == 101b)
      ; It's IMUL  r/m16
      ; or   IMUL  r/m32
        jmp     _imul
    .ELSEIF (al== 110b)
      ; It's DIV r/m16
      ; or   DIV r/m32
        jmp     _div
    .ELSEIF (al == 111b)
      ; It's IDIV r/m16
      ; or   IDIV r/m32
        jmp     _idiv
    .ENDIF
    jmp    _unused

  _check_reg_fe:
  ; Check the REG portion of the Mod/Reg/RM byte
    movzx   eax,byte ptr ds:[esi+1]
    shr     eax,3
    and     eax,111b
    .IF (al== 000b)
      ; It's INC r/m8
        jmp     _inc_rm8
    .ELSEIF (al== 001b)
      ; It's DEC r/m8
        jmp     _dec_rm8
    .ENDIF
    jmp    _unused

  _check_reg_ff:
  ; Check the REG portion of the Mod/Reg/RM byte
    movzx   eax,byte ptr ds:[esi+1]
    shr     eax,3
    and     eax,111b
    .IF (al == 000b)
      ; It's INC r/m16
      ; or   INC r/m32
        jmp     _inc_rm16_32
    .ELSEIF (al == 001b)
      ; It's DEC r/m16
      ; or   DEC r/m32
        jmp     _dec_rm16_32
    .ELSEIF (al == 010b)
      ; It's CALL r/m16 absolute
      ; or   CALL r/m32 absolute
        jmp     _call_rm
    .ELSEIF (al == 011b)
      ; It's CALL m16&16
      ; or   CALL m16&32
        jmp     _call_far_rm
    .ELSEIF (al == 100b)
      ; It's JMP m16&16
      ; or   JMP m16&32
        jmp     _jmp_near_rm
    .ELSEIF (al == 101b)
      ; It's JMP FAR m16&16
      ; or   JMP FAR m16&32
        jmp     _jmp_far_rm
    .ELSEIF ( al == 110b)
      ; It's PUSH r/m16
      ; or   PUSH r/m32
        jmp     _push_rm
    .ENDIF
    jmp    _unused

  _check_reg_0f00:
    movzx   eax,byte ptr ds:[esi+2]
    shr     eax,3
    and     eax,111b
    .IF (al == 000b)
      ; It's SLDT
        jmp     _sldt
    .ELSEIF (al == 001b)
      ; It's STR r/m16
        jmp _str
    .ELSEIF (al == 010b)
      ; It's LLDT
        jmp     _lldt
    .ELSEIF (al == 011b)
      ; It's LTR
        jmp     _ltr
    .ELSEIF (al == 100b)
      ; It's VERR r/m16
        jmp     _verr
    .ELSEIF (al == 101b)
      ; It's VERW r/m16
        jmp     _verw
    .ENDIF
    jmp     _unused

  _check_reg_0f01:
    movzx   eax,byte ptr ds:[esi+2]
    shr     eax,3
    and     eax,111b
    .IF (al == 000b)
      ; It's SGDT
        jmp     _sgdt_label
    .ELSEIF (al == 001b)
      ; It's SIDT
        jmp     _sidt_label
    .ELSEIF (al == 010b)
      ; It's LGDT
        jmp     _lgdt
    .ELSEIF (al == 011b)
      ; It's LIDT
        jmp     _lidt
    .ELSEIF (al == 100b)
      ; It's SMSW r/m16
      ; or   SMSR r32/m16
        jmp     _smsw
    .ELSEIF (al == 110b)
      ; It's LMSW mem
        jmp     _lmsw
    .ELSEIF (al == 111b)
      ; It's INVLPG mem
        jmp     _invlpg
    .ENDIF
    jmp     _unused

  _check_reg_0fba:
  ; Check the REG portion of the Mod/Reg/RM byte
    movzx   eax,byte ptr ds:[esi+2]
    shr     eax,3
    and     eax,111b
    .IF (al == 100b)
      ; It's BT r/m16,imm8
      ; or   BT r/m32,imm8
        jmp     _bt_immed8
    .ELSEIF (al == 101b)
      ; It's BTS r/m16,imm8
      ; or   BTS r/m32,imm8
        jmp     _bts_immed8
    .ELSEIF (al == 110b)
      ; It's BTR r/m16,imm8
      ; or   BTR r/m32,imm8
        jmp     _btr_immed8
    .ELSEIF (al == 111b)
      ; It's BTC r/m16,imm8
      ; or   BTC r/m32,imm8
        jmp     _btc_immed8
    .ENDIF
    jmp    _unused

  _check_reg_0f71:
  ; Check the REG portion of the Mod/Reg/RM byte
    movzx   eax,byte ptr ds:[esi+2]
    shr     eax,3
    and     eax,111b
    .IF (al == 100b)
      ; It's PSRAW mm,immed8
        jmp     _psraw_immed8
    .ENDIF
    jmp     _unused

  _check_reg_0f72:
  ; Check the REG portion of the Mod/Reg/RM byte
    movzx   eax,byte ptr ds:[esi+2]
    shr     eax,3
    and     eax,111b
    .IF (al == 100b)
      ; It's PSRAD mm,immed8
        jmp     _psrad_immed8
    .ENDIF
    jmp     _unused

  _check_reg_0fc7:
  ; Check the REG portion of the Mod/Reg/RM byte
    movzx   eax,byte ptr ds:[esi+2]
    shr     eax,3
    and     eax,111b
    .IF (al == 001b)
      ; It's CMPXCHG8B m64
        jmp     _cmpxchg8b
    .ENDIF
    jmp     _unused

  _two_byte_unused:
    @instr_bytes    2
    @instr_text     unknown_opcode,9
    jmp     store_instruction

  _unused:
    @instr_bytes    1
    mov     al,byte ptr ds:[esi]
    call    convert_al_to_hex
    mov     ebx,sizeof unknown_opcode - 2
    mov     word ptr fs:unknown_opcode[ebx],ax
    @instr_text     unknown_opcode, sizeof unknown_opcode
    jmp     store_instruction

  _fpu_unused:
    @instr_bytes    2
    mov     al,byte ptr ds:[esi]
    call    convert_al_to_hex
    mov     ebx,sizeof fpu_unknown_opcode -5
    mov     word ptr fs:fpu_unknown_opcode[ebx],ax
    mov     al,byte ptr ds:[esi+1]
    call    convert_al_to_hex
    mov     ebx,sizeof fpu_unknown_opcode -2
    mov     word ptr fs:fpu_unknown_opcode[ebx],ax
    @instr_text     fpu_unknown_opcode, sizeof fpu_unknown_opcode
    jmp     store_instruction


;; STORE_THE_INSTRUCTION
  store_instruction:
    mov     edi,dword ptr ss:[ebp+12]
;; Opening parenthesis
    mov     al,'('
    stosb

;; Mode
    mov     eax,fs:cpu_mode
    .IF (al == 0)
      ; 32-bit pmode
        mov     ax,'23'
        stosw
    .ELSEIF (al == 1)
      ; 16-bit pmode
        mov     ax,'61'
        stosw
    .ELSEIF (al == 2)
      ; REAL
        mov     eax,'laer'
        stosd
    .ELSE
      ; V86 mode
        mov     eax,' 68v'
        stosd
        dec     edi
    .ENDIF
    mov     al,'|'
    stosb

;; Prefix bytes
    .IF (fs:prefix_bytes != 0)
        mov     ecx,fs:prefix_bytes
        mov     ebx,dword ptr ss:[ebp+16]                           ; Get esi from the stack
      ; Right now, ds:[ebx] - far ptr to start of code instruction
      ;                 ecx - number of bytes
        add     dword ptr ss:[ebp+36],ecx
      @@:
        mov     al,byte ptr ds:[ebx]
        call    convert_al_to_hex
        stosw
        inc     ebx
        loop    @B
    .ENDIF
    mov     al,'|'
    stosb

;; Instruction bytes
    mov     ecx,fs:instruction_bytes
    mov     ebx,fs:instruction_offset
  ; Right now, ds:[ebx] - far ptr to start of actual instruction (after prefix bytes)
    add     dword ptr ss:[ebp+36],ecx
  @@:
    mov     al,byte ptr ds:[ebx]
    call    convert_al_to_hex
    stosw
    inc     ebx
    loop    @B
    mov     al,'|'
    stosb

;; Mod/R/RM
    .IF (fs:mod_reg_rm_bytes != 0)
        mov     ecx,fs:mod_reg_rm_bytes
        mov     ebx,fs:mod_reg_rm_offset
      ; Right now, ds:[ebx] - far ptr to start of code instruction
      ;                 ecx - number of bytes
      @@:
        mov     al,byte ptr ds:[ebx]
        call    convert_al_to_hex
        stosw
        inc     ebx
        loop    @B
    .ENDIF
    mov     al,'|'
    stosb

;; SIB
    .IF (fs:sib_bytes != 0)
        mov     ecx,fs:sib_bytes
        mov     ebx,fs:sib_offset
      ; Right now, ds:[ebx] - far ptr to start of code instruction
      ;                 ecx - number of bytes
      @@:
        mov     al,byte ptr ds:[ebx]
        call    convert_al_to_hex
        stosw
        inc     ebx
        loop    @B
    .ENDIF
    mov     al,'|'
    stosb

;; Displacement in instruction
    .IF (fs:displacement_bytes != 0)
        mov     ecx,fs:displacement_bytes
        mov     ebx,fs:displacement_offset
      ; Right now, fs:[ebx] - far ptr to start of displacement text in expression
      ;                 ecx - number of bytes
      @@:
        mov     al,byte ptr fs:[ebx]
        stosb
        inc     ebx
        loop    @B
    .ENDIF
    mov     al,'|'
    stosb

;; Immediate in instruction
    .IF (fs:immediate_bytes != 0)
        mov     eax,dword ptr fs:immediate_data
        call    convert_and_store_eax_to_hex
    .ENDIF
    mov     al,'|'
    stosb

;; Operand size of instruction
    mov     eax,fs:operand_size
    call    convert_al_to_hex
    stosw
    mov     al,'|'
    stosb

;; Instruction text
    mov     ecx,fs:instruction_text_length
    mov     ebx,fs:instruction_text_offset
  ; Right now, fs:[ebx] - far ptr to the instruction text
  ;                 ecx - number of characters in
  @@:
    mov     al,byte ptr fs:[ebx]
    stosb
    inc     ebx
    loop    @B
    mov     al,'|'
    stosb

;; Parameters text
    .IF (fs:parameters_text_length != 0)
        mov     ecx,fs:parameters_text_length
        mov     ebx,fs:parameters_text_offset
      ; Right now, fs:[ebx] - far ptr to the instruction parameters text
      ;                 ecx - number of characters in
      @@:
        mov     al,byte ptr fs:[ebx]
        stosb
        inc     ebx
        loop    @B
    .ENDIF
    mov     al,'|'
    stosb

;; Data text
    mov     al,'|'
    stosb

;; Immediate text
    mov     al,'|'
    stosb

;; Timing
    mov     al,'|'
    stosb

;; Pipe
    mov     al,'|'
    stosb

;; Pairable
    mov     al,'|'
    stosb

;; CPU
    mov     al,'|'
    stosb

;; More casqs?
    mov     ax,'on'
    stosw

;; Closing parenthesis
    mov     al,')'
    stosb

;; NULL terminate
    xor     al,al
    stosb

  done_disasm:
    leave
    pop     fs
    popfd
    popad
    retf




convert_al_to_hex       PROC    NEAR
; This routine is used to convert the value in al to
;
; Upon entry:   al - value to convert
;
; Upon exit:    ax - converted value in hexidecimal
;               others - preserved
;
    mov     ah,al
    and     ah,0fh
    shr     al,4

  do_al:
    cmp     al,9
    ja      @F
    add     al,'0'
    jmp     do_ah
  @@:
    add     al,'a'-10

  do_ah:
    cmp     ah,9
    ja      @F
    add     ah,'0'
    ret

  @@:
    add     ah,'a'-10
    ret
convert_al_to_hex       ENDP




convert_and_store_ax_to_hex     PROC    NEAR
; This routine is used to convert a word of data to a text string
;
; Upon entry:   ax - dword to convert
;          es:[edi] - where to store string
;
; Upon exit:    es:[edi] - updated with string
;
    push    ebx
    push    ecx

    mov     ebx,eax
    mov     ecx,2
  @@:
    rol     ebx,8
    mov     al,bl
    call    convert_al_to_hex
    stosw
    loop    @B

    pop     ecx
    pop     ebx
    ret
convert_and_store_ax_to_hex     ENDP




convert_and_store_eax_to_hex    PROC    NEAR
; This routine is used to convert a dword of data to a text string
;
; Upon entry:   eax - dword to convert
;          es:[edi] - where to store string
;
; Upon exit:    es:[edi] - updated with string
;
    push    ebx
    push    ecx

    mov     ebx,eax
    mov     ecx,4
  @@:
    rol     ebx,8
    mov     al,bl
    call    convert_al_to_hex
    stosw
    loop    @B

    pop     ecx
    pop     ebx
    ret
convert_and_store_eax_to_hex    ENDP




start_offsets       PROC    NEAR
; This routine is called repeatedly.  It marks the starting location for generated output
;
; Upon entry:   parameters_text_offset + parameters_text_length = where to store
;
; Upon exit:    edi - updated to current value
;
    mov     edi,fs:parameters_text_offset
    add     edi,fs:parameters_text_length
    mov     fs:displacement_offset,edi
    ret
start_offsets       ENDP




end_offsets     PROC    NEAR
; This routine is called repeatedly.  It makrs the ending location for generated output
;
; Upon entry:   displacement_offset - starting location
;               edi - ending location
;
; Upon exit:    eax - number of bytes between start_offsets and end_offsets

    mov     eax,edi
    sub     eax,fs:displacement_offset
    mov     fs:displacement_bytes,eax
    mov     fs:parameters_text_length,eax
    ret
end_offsets     ENDP




determine_operand_size      PROC    NEAR
; This routine is used to determine the operand size
;
; Upon entry:   The stack is arranged as below
;               0 is assumed byte, !0 is assumed to be either 16 or 32 depending on current CPU mode and value on the stack
;
; Upon exit:    fs:operand_size is updated to either 8, 16, 32
;
  ; [esp+04] - parameter they're specifying
  ; [esp+00] - ip of calling procedure
    .IF (dword ptr ss:[esp+4] == 0)
      ; Byte
        mov     fs:operand_size,8
    .ELSE
      ; It's either a word or dword
        .IF (fs:cpu_mode == 0)
          ; It will be a 32-bit register unless there's an operand override
            .IF (fs:op_size_override != 0)
              ; It's 16-bit
                mov     fs:operand_size,16
            .ELSE
              ; It's 32-bit
                mov     fs:operand_size,32
            .ENDIF
        .ELSE
          ; It will be a 16-bit register unless there's an operand override
            .IF (fs:op_size_override != 0)
              ; It's 32-bit
                mov     fs:operand_size,32
            .ELSE
              ; It's 16-bit
                mov     fs:operand_size,16
            .ENDIF
        .ENDIF
    .ENDIF
    ret 4
determine_operand_size      ENDP




determine_standard_operand_size     PROC
; This routien is used to determine the standard operand size based on the current CPU mode and any prefix bytes
;
; Upon entry:   cpu_mode and op_size_override are setup
;
; Upon exit:    operand_size is assigned to 16 or 32
;
    .IF ((fs:cpu_mode == 0 && fs:op_size_override != 0) || (fs:cpu_mode != 0 && fs:op_size_override == 0))
        mov     fs:operand_size,16
    .ELSE
        mov     fs:operand_size,32
    .ENDIF
    ret
determine_standard_operand_size     ENDP




extract_mod_reg_rm      PROC    NEAR
; This routine is used to
;
; Upon entry:   ds:[esi] - far ptr to the execution code
;               fs:[edi] - where to store to
;
; Upon exit:    The mod/reg/rm byte is extracted, and possibly a SIB byte, etc.
;
    push    eax
    push    ebx
    push    edx

    mov     edi,fs:parameters_text_offset
    add     edi,fs:parameters_text_length

    mov     al,byte ptr ds:[esi]
    inc     esi
    inc     fs:instruction_bytes

    mov     bl,al
    shr     bl,6
  ; Right now, bl is the Mod byte
    mov     dl,al
    mov     dh,al
    shr     dl,3
    and     dl,111b
    and     dh,111b
  ; Right now, bl - mod
  ;            dl - reg
  ;            dh - r/m
    .IF (bl == 00b)
        .IF ((fs:cpu_mode == 0 && fs:adr_size_override != 0) || (fs:cpu_mode != 0 && fs:adr_size_override == 0))
          ; It's 16-bit code
            .IF (dh == 110b)
              ; It's a direct memory operand at some displacement
                .IF (fs:reverse_mod_reg_rm != 0)
                  ; Memory to register
                    mov     bl,dl
                    call    store_gp_register
                    inc     fs:gp_reg_count
                    call    store_comma
                    mov     bl,dh
                    call    store_direct
                    inc     fs:gp_reg_count
                .ELSE
                  ; Register to memory
                    mov     bl,dh
                    call    store_direct
                    inc     fs:gp_reg_count
                    call    store_comma
                    mov     bl,dl
                    call    store_gp_register
                    inc     fs:gp_reg_count
                .ENDIF
            .ELSE
              ; It's an indirect memory operand without displacement
                .IF (fs:reverse_mod_reg_rm != 0)
                  ; Memory to register
                    mov     bl,dl
                    call    store_gp_register
                    inc     fs:gp_reg_count
                    call    store_comma
                    mov     bl,dh
                    call    store_indirect_no_displacement
                    inc     fs:gp_reg_count
                .ELSE
                  ; Register to memory
                    mov     bl,dh
                    call    store_indirect_no_displacement
                    inc     fs:gp_reg_count
                    call    store_comma
                    mov     bl,dl
                    call    store_gp_register
                    inc     fs:gp_reg_count
                .ENDIF
            .ENDIF
        .ELSE
          ; It's 32-bit code
            .IF (fs:reverse_mod_reg_rm != 0)
              ; Memory to register
                mov     bl,dl
                call    store_gp_register
                inc     fs:gp_reg_count
                call    store_comma
                mov     bl,dh
                call    store_indirect_no_displacement
                inc     fs:gp_reg_count
            .ELSE
              ; Register to memory
                mov     bl,dh
                call    store_indirect_no_displacement
                inc     fs:gp_reg_count
                call    store_comma
                mov     bl,dl
                call    store_gp_register
                inc     fs:gp_reg_count
            .ENDIF
        .ENDIF
    .ELSEIF (bl == 01b)
      ; It's an indirect memory operand with an 8-bit displacement
        .IF (fs:reverse_mod_reg_rm != 0)
          ; Memory to register
            mov     bl,dl
            call    store_gp_register
            inc     fs:gp_reg_count
            call    store_comma
            mov     bl,dh
            call    store_indirect_with_8bit_displacement
            inc     fs:gp_reg_count
        .ELSE
          ; Register to memory
            mov     bl,dh
            call    store_indirect_with_8bit_displacement
            inc     fs:gp_reg_count
            call    store_comma
            mov     bl,dl
            call    store_gp_register
            inc     fs:gp_reg_count
        .ENDIF
    .ELSEIF (bl == 10b)
      ; It's an indirect memory operand with a 16-bit or 32-bit displacement
        .IF (fs:reverse_mod_reg_rm != 0)
          ; Memory to register
            mov     bl,dl
            call    store_gp_register
            inc     fs:gp_reg_count
            call    store_comma
            mov     bl,dh
            call    store_indirect_with_xbit_displacement
            inc     fs:gp_reg_count
        .ELSE
          ; Register to memory
            mov     bl,dh
            call    store_indirect_with_xbit_displacement
            inc     fs:gp_reg_count
            call    store_comma
            mov     bl,dl
            call    store_gp_register
            inc     fs:gp_reg_count
        .ENDIF
    .ELSE
      ; It's a register to register
        .IF (fs:reverse_mod_reg_rm != 0)
            mov     bl,dl
            call    store_gp_register
            inc     fs:gp_reg_count
            .IF (fs:display_second_register != 0)
                call    store_comma
                mov     bl,dh
                call    store_gp_register
                inc     fs:gp_reg_count
            .ENDIF
        .ELSE
            mov     bl,dh
            call    store_gp_register
            inc     fs:gp_reg_count
            .IF (fs:display_second_register != 0)
                call    store_comma
                mov     bl,dl
                call    store_gp_register
                inc     fs:gp_reg_count
            .ENDIF
        .ENDIF
    .ENDIF

    pop     edx
    pop     ebx
    pop     eax
    ret
extract_mod_reg_rm      ENDP




extract_mod_rm      PROC    NEAR
; This routine is used to
;
; Upon entry:   ds:[esi] - far ptr to the execution code
;               fs:[edi] - where to store to
;
; Upon exit:    The mod/reg/rm byte is extracted, and possibly a SIB byte, etc.
;
    push    eax
    push    ebx
    push    edx

    mov     edi,fs:parameters_text_offset
    add     edi,fs:parameters_text_length

    mov     al,byte ptr ds:[esi]
    inc     esi
    inc     fs:instruction_bytes

    mov     bl,al
    shr     bl,6
  ; Right now, bl is the Mod byte
    mov     dl,al
    mov     dh,al
    shr     dl,3
    and     dl,111b
    and     dh,111b
  ; Right now, bl - mod
  ;            dl - reg
  ;            dh - r/m
    .IF (bl == 00b)
        .IF ((fs:cpu_mode == 0 && fs:adr_size_override != 0) || (fs:cpu_mode != 0 && fs:adr_size_override == 0))
          ; It's 16-bit code
            .IF (dh == 110b)
              ; It's a direct memory operand at some displacement
                mov     bl,dh
                call    store_direct
            .ELSE
              ; It's an indirect memory operand without displacement
                mov     bl,dh
                call    store_indirect_no_displacement
            .ENDIF
        .ELSE
          ; It's 32-bit code
            mov     bl,dh
            call    store_indirect_no_displacement
        .ENDIF
    .ELSEIF (bl == 01b)
      ; It's an indirect memory operand with an 8-bit displacement
        mov     bl,dh
        call    store_indirect_with_8bit_displacement
    .ELSEIF (bl == 10b)
      ; It's an indirect memory operand with a 16-bit or 32-bit displacement
        mov     bl,dh
        call    store_indirect_with_xbit_displacement
    .ELSE
      ; It's a register to register
        mov     bl,dh
        call    store_gp_register
    .ENDIF
    inc     fs:gp_reg_count

    pop     edx
    pop     ebx
    pop     eax
    ret
extract_mod_rm      ENDP




store_gp_register       PROC    NEAR
; This routine is used to store a general purpose register.
;
; Upon entry:   fs:[edi] - where to store
;                     bl - register to store (only lower 3 bits should be populated)
;        fs:operand_size - indicates what size we're using
;
; Upon exit:    fs:[edi] - updated with the register
;               fs:parameters_text_length - updated with the length of the register
;
    push    eax
    .IF (fs:special_control != 0)
      ; Some special control is required (such as different registers on each side)
        .IF (fs:special_control == 1)
          ; Special control #1 - sreg,gp
            .IF (fs:gp_reg_count == 0)
              ; We're on the left side
                mov     fs:special_reg,_SEG_REGS
            .ELSE
              ; We're on the right side
                mov     fs:special_reg,_NO_SPECIAL
            .ENDIF
        .ELSEIF (fs:special_control == 2)
          ; Special control #2 - gp,sreg
            .IF (fs:gp_reg_count == 0)
              ; We're on the left side
                mov     fs:special_reg,_NO_SPECIAL
            .ELSE
              ; We're on the right side
                mov     fs:special_reg,_SEG_REGS
            .ENDIF
        .ELSEIF (fs:special_control == 3)
          ; Special control #3 - crx,reg32
            .IF (fs:gp_reg_count == 0)
              ; We're on the left side
                mov     fs:special_reg,_CONTROL_REGS
            .ELSE
              ; We're on the right side
                mov     fs:special_reg,_NO_SPECIAL
            .ENDIF
        .ELSEIF (fs:special_control == 4)
          ; Special control #4 - reg32,crx
            .IF (fs:gp_reg_count == 0)
              ; We're on the left side
                mov     fs:special_reg,_NO_SPECIAL
            .ELSE
              ; We're on the right side
                mov     fs:special_reg,_CONTROL_REGS
            .ENDIF
        .ELSEIF (fs:special_control == 5)
          ; Special control #5 - drx,reg32
            .IF (fs:gp_reg_count == 0)
              ; We're on the left side
                mov     fs:special_reg,_DEBUG_REGS
            .ELSE
              ; We're on the right side
                mov     fs:special_reg,_NO_SPECIAL
            .ENDIF
        .ELSEIF (fs:special_control == 6)
          ; Special control #6 - reg32,drx
            .IF (fs:gp_reg_count == 0)
              ; We're on the left side
                mov     fs:special_reg,_NO_SPECIAL
            .ELSE
              ; We're on the right side
                mov     fs:special_reg,_DEBUG_REGS
            .ENDIF
        .ELSEIF (fs:special_control == 7)
          ; Special control #7 - trx,reg32
            .IF (fs:gp_reg_count == 0)
              ; We're on the left side
                mov     fs:special_reg,_TEST_REGS
            .ELSE
              ; We're on the right side
                mov     fs:special_reg,_NO_SPECIAL
            .ENDIF
        .ELSEIF (fs:special_control == 8)
          ; Special control #8 - reg32,trx
            .IF (fs:gp_reg_count == 0)
              ; We're on the left side
                mov     fs:special_reg,_NO_SPECIAL
            .ELSE
              ; We're on the right side
                mov     fs:special_reg,_TEST_REGS
            .ENDIF
        .ELSEIF (fs:special_control == 9)
          ; Special control #9 - mmx,mmx
            mov     fs:special_reg,_MMX_REGS
        .ELSEIF (fs:special_control == 10)
          ; Special control #10 - mmx,reg32
            .IF (fs:gp_reg_count == 0)
              ; We're on the left side
                mov     fs:special_reg,_MMX_REGS
            .ELSE
              ; We're on the right side
                mov     fs:special_reg,_NO_SPECIAL
            .ENDIF
        .ELSEIF (fs:special_control == 11)
          ; Special control #11 - reg32,mmx
            .IF (fs:gp_reg_count == 0)
              ; We're on the left side
                mov     fs:special_reg,_NO_SPECIAL
            .ELSE
              ; We're on the right side
                mov     fs:special_reg,_MMX_REGS
            .ENDIF
        .ENDIF
    .ENDIF
    .IF (fs:special_reg == _NO_SPECIAL)
        .IF (fs:movxx_register != 0)
            .IF (fs:first_gp_register != 0)
              ; We're storing the first gp register
                mov     eax,fs:first_gp_register
                mov     fs:first_gp_register,0
            .ELSE
              ; We're storing the second gp register
                mov     eax,fs:second_gp_register
                mov     fs:second_gp_register,0
            .ENDIF
            mov     fs:operand_size,eax
            .IF (fs:operand_size == 8)
                jmp     force_8
            .ELSEIF (fs:operand_size == 16)
                jmp     force_16
            .ENDIF
            jmp     force_32
        .ENDIF
        .IF (fs:operand_size == 8)
          ; It's a byte register
          force_8:
            .IF (bl == 000b)
              ; It's al
                mov     ax,'la'
            .ELSEIF (bl == 001b)
              ; It's cl
                mov     ax,'lc'
            .ELSEIF (bl == 010b)
              ; It's dl
                mov     ax,'ld'
            .ELSEIF (bl == 011b)
              ; It's bl
                mov     ax,'lb'
            .ELSEIF (bl == 100b)
              ; It's ah
                mov     ax,'ha'
            .ELSEIF (bl == 101b)
              ; It's ch
                mov     ax,'hc'
            .ELSEIF (bl == 110b)
              ; It's dh
                mov     ax,'hd'
            .ELSE
              ; It's bh
                mov     ax,'hb'
            .ENDIF
            mov     word ptr fs:[edi],ax
            add     fs:parameters_text_length,2
            add     edi,2
        .ELSEIF (fs:operand_size == 16)
          ; It's a word register
;            .IF (fs:op_size_override != 0)
;              ; They've overriden the default
;                jmp     force_32
;            .ENDIF
          force_16:
            .IF (bl == 000b)
              ; It's al
                mov     ax,'xa'
            .ELSEIF (bl == 001b)
              ; It's cl
                mov     ax,'xc'
            .ELSEIF (bl == 010b)
              ; It's dl
                mov     ax,'xd'
            .ELSEIF (bl == 011b)
              ; It's bl
                mov     ax,'xb'
            .ELSEIF (bl == 100b)
              ; It's ah
                mov     ax,'ps'
            .ELSEIF (bl == 101b)
              ; It's ch
                mov     ax,'pb'
            .ELSEIF (bl == 110b)
              ; It's dh
                mov     ax,'is'
            .ELSE
              ; It's bh
                mov     ax,'id'
            .ENDIF
            mov     word ptr fs:[edi],ax
            add     fs:parameters_text_length,2
            add     edi,2
        .ELSEIF (fs:operand_size == 64)
          ; 64-bit registers
            .IF (bl == 000b)
              ; It's al
                mov     eax,'xa?'
            .ELSEIF (bl == 001b)
              ; It's cl
                mov     eax,'xc?'
            .ELSEIF (bl == 010b)
              ; It's dl
                mov     eax,'xd?'
            .ELSEIF (bl == 011b)
              ; It's bl
                mov     eax,'xb?'
            .ELSEIF (bl == 100b)
              ; It's ah
                mov     eax,'ps?'
            .ELSEIF (bl == 101b)
              ; It's ch
                mov     eax,'pb?'
            .ELSEIF (bl == 110b)
              ; It's dh
                mov     eax,'is?'
            .ELSE
              ; It's bh
                mov     eax,'id?'
            .ENDIF
            mov     word ptr fs:[edi],ax
            shr     eax,16
            mov     byte ptr fs:[edi+2],al
            add     fs:parameters_text_length,3
            add     edi,3
        .ELSE
          ; It's a dword register
;            .IF (fs:op_size_override != 0)
;              ; They've overriden the default
;                jmp     force_16
;            .ENDIF
          force_32:
            .IF (bl == 000b)
              ; It's al
                mov     eax,'xae'
            .ELSEIF (bl == 001b)
              ; It's cl
                mov     eax,'xce'
            .ELSEIF (bl == 010b)
              ; It's dl
                mov     eax,'xde'
            .ELSEIF (bl == 011b)
              ; It's bl
                mov     eax,'xbe'
            .ELSEIF (bl == 100b)
              ; It's ah
                mov     eax,'pse'
            .ELSEIF (bl == 101b)
              ; It's ch
                mov     eax,'pbe'
            .ELSEIF (bl == 110b)
              ; It's dh
                mov     eax,'ise'
            .ELSE
              ; It's bh
                mov     eax,'ide'
            .ENDIF
            mov     word ptr fs:[edi],ax
            shr     eax,16
            mov     byte ptr fs:[edi+2],al
            add     fs:parameters_text_length,3
            add     edi,3
        .ENDIF
    .ELSEIF (fs:special_reg == _SEG_REGS)
        .IF (bl == 000b)
          ; es
            mov     ax,'se'
        .ELSEIF (bl == 001b)
          ; cs
            mov     ax,'sc'
        .ELSEIF (bl == 010b)
          ; ss
            mov     ax,'ss'
        .ELSEIF (bl == 011b)
          ; ds
            mov     ax,'sd'
        .ELSEIF (bl == 100b)
          ; fs
            mov     ax,'sf'
        .ELSEIF (bl == 101b)
          ; gs
            mov     ax,'sg'
        .ELSE
          ; ?s
            mov     ax,'s?'
        .ENDIF
        mov     word ptr fs:[edi],ax
        add     edi,2
        add     fs:parameters_text_length,2
    .ELSE
        mov     eax,fs:special_reg
        .IF (eax == _CONTROL_REGS)
          ; CR0-7
            mov     word ptr fs:[edi],'rc'
        .ELSEIF (eax == _DEBUG_REGS)
          ; DR0-7
            mov     word ptr fs:[edi],'rd'
        .ELSEIF (eax == _TEST_REGS)
          ; TR0-7
            mov     word ptr fs:[edi],'rt'
        .ELSEIF (eax == _STx_REGS)
            mov     word ptr fs:[edi],'ts'
        .ELSEIF (eax == _MMX_REGS)
            mov     word ptr fs:[edi],'mm'
        .ELSEIF (eax == _XMM_REGS)
            mov     word ptr fs:[edi],'mx'
        .ELSE
          ; Who knows ... something else
            mov     word ptr fs:[edi],'??'
        .ENDIF
        add     bl,'0'
        mov     byte ptr fs:[edi+2],bl
        add     fs:parameters_text_length,3
        add     edi,3
    .ENDIF
    pop     eax
    ret
store_gp_register       ENDP




store_displacement_registers        PROC    NEAR
; This routine is used to store a displacement register.
;
; Upon entry:   fs:[edi] - where to store
;                     bl - register to store (only lower 3 bits should be populated)
;        fs:operand_size - indicates what size we're using
;
; Upon exit:    fs:[edi] - updated with the register
;               fs:parameters_text_length - updated with the length of the register
;
    .IF ((fs:cpu_mode == 0 && fs:adr_size_override != 0) || (fs:cpu_mode != 0 && fs:adr_size_override == 0))
      ; It's a 16-bit displacement (small registers)
        call    store_16_bit_displacement_registers
    .ELSE
        .IF (bl == 000b)
          ; It's eax
            mov     dword ptr fs:[edi+0],'xae'
            add     fs:parameters_text_length,3
            add     edi,3
        .ELSEIF (bl == 001b)
          ; It's ecx
            mov     dword ptr fs:[edi+0],'xce'
            add     fs:parameters_text_length,3
            add     edi,3
        .ELSEIF (bl == 010b)
          ; It's edx
            mov     dword ptr fs:[edi+0],'xde'
            add     fs:parameters_text_length,3
            add     edi,3
        .ELSEIF (bl == 011b)
          ; It's ebx
            mov     dword ptr fs:[edi+0],'xbe'
            add     fs:parameters_text_length,3
            add     edi,3
        .ELSEIF (bl == 100b)
          ; It has a SIB byte
            push    ebx
            mov     fs:sib_offset,esi
            mov     fs:sib_bytes,1
            mov     bl,ds:[esi]
            inc     esi
            inc     fs:instruction_bytes
            call    store_displacement_registers_sib
            pop     ebx
        .ELSEIF (bl == 101b)
          ; It's disp32
            call    store_32_bit_value
        .ELSEIF (bl == 110b)
          ; It's esi
            mov     dword ptr fs:[edi],'ise'
            add     fs:parameters_text_length,3
            add     edi,3
        .ELSE
          ; It's edi
            mov     dword ptr fs:[edi],'ide'
            add     fs:parameters_text_length,3
            add     edi,3
        .ENDIF
    .ENDIF
    ret
store_displacement_registers        ENDP




store_16_bit_displacement_registers     PROC    NEAR
; This routine is used to store the displacement registers for 16-bit coding modes
;
; Upon entry:   bl - r/m value
;               fs:[edi] - where to store
;
; Upon exit:    fs:[edi] - updated
;                    edi - updated
;
    .IF (bl == 000b)
      ; It's si+bx
        mov     dword ptr fs:[edi],'b+is'
        mov     byte ptr fs:[edi+4],'x'
        add     fs:parameters_text_length,5
        add     edi,5
    .ELSEIF (bl == 001b)
      ; It's di+bx
        mov     dword ptr fs:[edi],'b+id'
        mov     byte ptr fs:[edi+4],'x'
        add     fs:parameters_text_length,5
        add     edi,5
    .ELSEIF (bl == 010b)
      ; It's si+bp
        mov     dword ptr fs:[edi],'b+is'
        mov     byte ptr fs:[edi+4],'p'
        add     fs:parameters_text_length,5
        add     edi,5
    .ELSEIF (bl == 011b)
      ; It's di+bp
        mov     dword ptr fs:[edi],'b+id'
        mov     byte ptr fs:[edi+4],'p'
        add     fs:parameters_text_length,5
        add     edi,5
    .ELSEIF (bl == 100b)
      ; It's si
        mov     word ptr fs:[edi],'is'
        add     fs:parameters_text_length,2
        add     edi,2
    .ELSEIF (bl == 101b)
      ; It's di
        mov     word ptr fs:[edi],'id'
        add     fs:parameters_text_length,2
        add     edi,2
    .ELSEIF (bl == 110b)
      ; It's bp
        mov     word ptr fs:[edi],'pb'
        add     fs:parameters_text_length,2
        add     edi,2
    .ELSE
      ; It's bx
        mov     word ptr fs:[edi],'xb'
        add     fs:parameters_text_length,2
        add     edi,2
    .ENDIF
    ret
store_16_bit_displacement_registers     ENDP





store_disp_displacement_registers       PROC    NEAR
; This routine is used to store the various registers used in 8-bit and 32-bit displacement encodings
;
; Upon entry:   bl - r/m value to use
;               fs:[edi] - where to store
;
; Upon exit:    fs:[edi] - updated
;                    edi - updated
;
    .IF ((fs:cpu_mode == 0 && fs:adr_size_override != 0) || (fs:cpu_mode != 0 && fs:adr_size_override == 0))
      ; It's a 16-bit displacement (small registers)
        call    store_16_bit_displacement_registers
    .ELSE
        .IF (bl == 000b)
          ; It's eax
            mov     dword ptr fs:[edi+0],'xae'
            add     fs:parameters_text_length,3
            add     edi,3
        .ELSEIF (bl == 001b)
          ; It's ecx
            mov     dword ptr fs:[edi+0],'xce'
            add     fs:parameters_text_length,3
            add     edi,3
        .ELSEIF (bl == 010b)
          ; It's edx
            mov     dword ptr fs:[edi+0],'xde'
            add     fs:parameters_text_length,3
            add     edi,3
        .ELSEIF (bl == 011b)
          ; It's ebx
            mov     dword ptr fs:[edi+0],'xbe'
            add     fs:parameters_text_length,3
            add     edi,3
        .ELSEIF (bl == 100b)
          ; It has a SIB byte
            push    ebx
            mov     fs:sib_offset,esi
            mov     fs:sib_bytes,1
            mov     bl,ds:[esi]
            inc     esi
            inc     fs:instruction_bytes
            call    store_disp_displacement_registers_sib
            pop     ebx
        .ELSEIF (bl == 101b)
          ; It's ebp
            mov     dword ptr fs:[edi],'pbe'
            add     fs:parameters_text_length,3
            add     edi,3
        .ELSEIF (bl == 110b)
          ; It's esi
            mov     dword ptr fs:[edi],'ise'
            add     fs:parameters_text_length,3
            add     edi,3
        .ELSE
          ; It's edi
            mov     dword ptr fs:[edi],'ide'
            add     fs:parameters_text_length,3
            add     edi,3
        .ENDIF
    .ENDIF
    ret
store_disp_displacement_registers       ENDP




store_displacement_registers_sib    PROC    NEAR
; This routine is used to process the SIB byte
;
; Upon entry:         bl - SIB byte
;               fs:[edi] - where to store output
;
; Upon exit:    fs:[edi] - updated
;
    push    edx
    push    ebx

    movzx   edx,bl
    shr     edx,6
    mov     fs:scale_factor,edx

    mov     dl,bl
    mov     dh,bl
    shr     dh,3
    and     dh,111b
    and     dl,111b
  ; Right now, dh - index
  ;            dl - base
  ;            fs:scale_factor - scale
    .IF (dl == 000b)
      ; It's eax+(scale*index)
        mov     dword ptr fs:[edi],'+xae'
    .ELSEIF (dl == 001b)
      ; It's ecx+(scale*index)
        mov     dword ptr fs:[edi],'+xce'
    .ELSEIF (dl == 010b)
      ; It's edx+(scale*index)
        mov     dword ptr fs:[edi],'+xde'
    .ELSEIF (dl == 011b)
      ; It's ebx+(scale*index)
        mov     dword ptr fs:[edi],'+xbe'
    .ELSEIF (dl == 100b)
      ; It's esp+(scale*index)
        mov     dword ptr fs:[edi],'+pse'
    .ELSEIF (dl == 101b)
      ; It's (scale*index)+disp32
        jmp     @F
    .ELSEIF (dl == 110b)
      ; It's esi+(scale*index)
        mov     dword ptr fs:[edi],'+ise'
    .ELSE
      ; It's edi+(scale*index)
        mov     dword ptr fs:[edi],'+ide'
    .ENDIF
    add     edi,4
    add     fs:parameters_text_length,4

  @@:
  ; Now, process the index
    .IF (dh == 000b)
      ; eax
        mov     dword ptr fs:[edi],'xae'
    .ELSEIF (dh == 001b)
      ; ecx
        mov     dword ptr fs:[edi],'xce'
    .ELSEIF (dh == 010b)
      ; edx
        mov     dword ptr fs:[edi],'xde'
    .ELSEIF (dh == 011b)
      ; ebx
        mov     dword ptr fs:[edi],'xbe'
    .ELSEIF (dh == 100b)
      ; no index
        dec     fs:parameters_text_length
        dec     edi
        jmp     @F
    .ELSEIF (dh == 101b)
      ; ebp
        mov     dword ptr fs:[edi],'pbe'
    .ELSEIF (dh == 110b)
      ; esi
        mov     dword ptr fs:[edi],'ise'
    .ELSE
      ; edi
        mov     dword ptr fs:[edi],'ide'
    .ENDIF
    add     fs:parameters_text_length,3
    add     edi,3

    mov     ebx,fs:scale_factor
    .IF (ebx != 00b)
        .IF (bl == 01b)
          ; It's *2
            mov     word ptr fs:[edi],'2*'
        .ELSEIF (bl == 10b)
          ; It's *4
            mov     word ptr fs:[edi],'4*'
        .ELSE
          ; It's *8
            mov     word ptr fs:[edi],'8*'
        .ENDIF
        add     fs:parameters_text_length,2
        add     edi,2
    .ENDIF

  @@:
    .IF (dl == 101b)
      ; We now have to store the disp32
        call    store_32_bit_signed_value
        add     fs:sib_bytes,4
    .ENDIF

    pop     ebx
    pop     edx
    ret
store_displacement_registers_sib    ENDP




store_disp_displacement_registers_sib       PROC    NEAR
; This routine is used to process the SIB byte
;
; Upon entry:         bl - SIB byte
;               fs:[edi] - where to store output
;
; Upon exit:    fs:[edi] - updated
;
    push    edx
    push    ebx

    movzx   edx,bl
    shr     edx,6
    mov     fs:scale_factor,edx

    mov     dl,bl
    mov     dh,bl
    shr     dh,3
    and     dh,111b
    and     dl,111b
  ; Right now, dh - index
  ;            dl - base
  ;            fs:scale_factor - scale
    .IF (dl == 000b)
      ; It's eax+(scale*index)
        mov     dword ptr fs:[edi],'+xae'
    .ELSEIF (dl == 001b)
      ; It's ecx+(scale*index)
        mov     dword ptr fs:[edi],'+xce'
    .ELSEIF (dl == 010b)
      ; It's edx+(scale*index)
        mov     dword ptr fs:[edi],'+xde'
    .ELSEIF (dl == 011b)
      ; It's ebx+(scale*index)
        mov     dword ptr fs:[edi],'+xbe'
    .ELSEIF (dl == 100b)
      ; It's esp+(scale*index)
        mov     dword ptr fs:[edi],'+pse'
    .ELSEIF (dl == 101b)
      ; It's ebp+(scale*index)
        mov     dword ptr fs:[edi],'+pbe'
    .ELSEIF (dl == 110b)
      ; It's esi+(scale*index)
        mov     dword ptr fs:[edi],'+ise'
    .ELSE
      ; It's edi+(scale*index)
        mov     dword ptr fs:[edi],'+ide'
    .ENDIF
    add     edi,4
    add     fs:parameters_text_length,4

  ; Now, process the index
    .IF (dh == 000b)
      ; eax
        mov     dword ptr fs:[edi],'xae'
    .ELSEIF (dh == 001b)
      ; ecx
        mov     dword ptr fs:[edi],'xce'
    .ELSEIF (dh == 010b)
      ; edx
        mov     dword ptr fs:[edi],'xde'
    .ELSEIF (dh == 011b)
      ; ebx
        mov     dword ptr fs:[edi],'xbe'
    .ELSEIF (dh == 100b)
      ; no index
        dec     fs:parameters_text_length
        dec     edi
        jmp     @F
    .ELSEIF (dh == 101b)
      ; ebp
        mov     dword ptr fs:[edi],'pbe'
    .ELSEIF (dh == 110b)
      ; esi
        mov     dword ptr fs:[edi],'ise'
    .ELSE
      ; edi
        mov     dword ptr fs:[edi],'ide'
    .ENDIF
    add     fs:parameters_text_length,3
    add     edi,3

    mov     ebx,fs:scale_factor
    .IF (ebx != 00b)
        .IF (bl == 01b)
          ; It's *2
            mov     word ptr fs:[edi],'2*'
        .ELSEIF (bl == 10b)
          ; It's *4
            mov     word ptr fs:[edi],'4*'
        .ELSE
          ; It's *8
            mov     word ptr fs:[edi],'8*'
        .ENDIF
        add     fs:parameters_text_length,2
        add     edi,2
    .ENDIF

  @@:
    pop     ebx
    pop     edx
    ret
store_disp_displacement_registers_sib       ENDP




store_direct    PROC    NEAR
; This routine is used to store a direct memory operand in the [disp] format
;
; Upon entry:   ds:[esi] - far ptr to the execution code
;               fs:[edi] - far ptr to store data
;
; Upon exit:    fs:[edi] is updated
;
    push    eax
    mov     fs:displacement_offset,edi
    call    store_segment_override
    call    store_open_bracket
    .IF ((fs:cpu_mode == 0 && fs:adr_size_override == 0) || (fs:cpu_mode != 0 && fs:adr_size_override != 0))
      ; 32-bit
        call    store_32_bit_value
    .ELSE
      ; 16-bit
        call    store_16_bit_value
    .ENDIF
    call    store_close_bracket
    mov     eax,edi
    sub     eax,fs:displacement_offset
    mov     fs:displacement_bytes,eax
    pop     eax
    ret
store_direct    ENDP




store_indirect_no_displacement      PROC    NEAR
; This routine is used to store an indirect memory combination
;
; Upon entry:   ds:[esi] - far ptr to the execution code
;               fs:[edi] - far ptr to store data
;
; Upon exit:    fs:[edi] is updated
;
    push    eax
    mov     fs:displacement_offset,edi
    call    store_segment_override
    call    store_open_bracket
    call    store_displacement_registers
    call    store_close_bracket
    mov     eax,edi
    sub     eax,fs:displacement_offset
    mov     fs:displacement_bytes,eax
    pop     eax
    ret
store_indirect_no_displacement      ENDP




store_indirect_with_8bit_displacement       PROC    NEAR
; This routine is used to store an indirect memory combination with an 8-bit displacement
;
; Upon entry:   ds:[esi] - far ptr to the execution code
;               fs:[edi] - far ptr to store data
;
; Upon exit:    fs:[edi] is updated
;
    push    eax
    mov     fs:displacement_offset,edi
    call    store_segment_override
    call    store_open_bracket
    call    store_disp_displacement_registers
    call    store_8_bit_signed_value
    call    store_close_bracket
    mov     eax,edi
    sub     eax,fs:displacement_offset
    mov     fs:displacement_bytes,eax
    pop     eax
    ret
store_indirect_with_8bit_displacement       ENDP




store_indirect_with_xbit_displacement       PROC    NEAR
; This routine is used to store an indirect memory combination with an xx-bit displacement (either 16 or 32)
;
; Upon entry:   ds:[esi] - far ptr to the execution code
;               fs:[edi] - far ptr to store data
;
; Upon exit:    fs:[edi] is updated
;
    push    eax
    mov     fs:displacement_offset,edi
    call    store_segment_override
    call    store_open_bracket
    call    store_disp_displacement_registers
    call    store_signed_value
    call    store_close_bracket
    mov     eax,edi
    sub     eax,fs:displacement_offset
    mov     fs:displacement_bytes,eax
    pop     eax
    ret
store_indirect_with_xbit_displacement       ENDP




store_segment_override      PROC    NEAR
; This routine is used to store a segment override text
;
; Upon entry:   fs:seg_override - indicates what override (if any)
;                      fs:[edi] - where to store
;
; Upon exit:    fs:[edi] is updated
;
    .IF (fs:seg_override != 0)
        push    eax
        .IF (fs:seg_override == 1)
          ; CS:
            mov     ax,'sc'
        .ELSEIF (fs:seg_override == 2)
          ; DS:
            mov     ax,'sd'
        .ELSEIF (fs:seg_override == 3)
          ; ES:
            mov     ax,'se'
        .ELSEIF (fs:seg_override == 4)
          ; SS:
            mov     ax,'ss'
        .ELSEIF (fs:seg_override == 5)
          ; FS:
            mov     ax,'sf'
        .ELSE
          ; GS:
            mov     ax,'sg'
        .ENDIF
        mov     word ptr fs:[edi],ax
        add     fs:parameters_text_length,2
        add     edi,2
        call    store_colon
        pop     eax
    .ENDIF
    ret
store_segment_override      ENDP




store_32_bit_value      PROC    NEAR
; This routine is used to store a 32-bit value
;
; Upon entry:   ds:[esi] - far ptr to value bytes in execution code
;               fs:[edi] - where to store output
;
; Upon exit:    fs:[edi] - is updated
;
    push    eax
    mov     al,byte ptr ds:[esi+3]
    call    convert_al_to_hex
    mov     word ptr fs:[edi+0],ax
    mov     al,byte ptr ds:[esi+2]
    call    convert_al_to_hex
    mov     word ptr fs:[edi+2],ax
    mov     al,byte ptr ds:[esi+1]
    call    convert_al_to_hex
    mov     word ptr fs:[edi+4],ax
    mov     al,byte ptr ds:[esi+0]
    call    convert_al_to_hex
    mov     word ptr fs:[edi+6],ax
    add     edi,8
    add     fs:parameters_text_length,8
    mov     eax,dword ptr ds:[esi]
    mov     dword ptr fs:displacement_data,eax
    add     esi,4
    add     fs:instruction_bytes,4
    pop     eax
    ret
store_32_bit_value      ENDP




store_16_bit_value      PROC    NEAR
; This routine is used to store a 16-bit value
;
; Upon entry:   ds:[esi] - far ptr to value bytes in execution code
;               fs:[edi] - where to store output
;
; Upon exit:    fs:[edi] - is updated
;
    push    eax
    mov     al,byte ptr ds:[esi+1]
    call    convert_al_to_hex
    mov     word ptr fs:[edi+0],ax
    mov     al,byte ptr ds:[esi+0]
    call    convert_al_to_hex
    mov     word ptr fs:[edi+2],ax
    add     edi,4
    add     fs:parameters_text_length,4
    movzx   eax,word ptr ds:[esi]
    mov     dword ptr fs:displacement_data,eax
    add     esi,2
    add     fs:instruction_bytes,2
    pop     eax
    ret
store_16_bit_value      ENDP




store_8_bit_value       PROC    NEAR
; This routine is used to store a 8-bit value
;
; Upon entry:   ds:[esi] - far ptr to value bytes in execution code
;               fs:[edi] - where to store output
;
; Upon exit:    fs:[edi] - is updated
;
    push    eax
    mov     al,byte ptr ds:[esi]
    call    convert_al_to_hex
    mov     word ptr fs:[edi+0],ax
    add     edi,2
    add     fs:parameters_text_length,2
    movzx   eax,byte ptr ds:[esi]
    mov     dword ptr fs:displacement_data,eax
    inc     esi
    inc     fs:instruction_bytes
    pop     eax
    ret
store_8_bit_value       ENDP




store_value     PROC    NEAR
; This routine is used to store the value based on the current size
;
; Upon entry:   ds:[esi] - far ptr to value bytes in instruction
;               fs:[edi] - where to store output
;
; Upon exit:
;
    .IF ((fs:cpu_mode == 0 && fs:op_size_override == 0) || (fs:cpu_mode != 0 && fs:op_size_override != 0))
      ; 32-bit
        call    store_32_bit_value
    .ELSE
      ; 16-bit
        call    store_16_bit_value
    .ENDIF
    ret
store_value     ENDP




store_32_bit_signed_value       PROC    NEAR
; This routine is used to store a 32-bit value
;
; Upon entry:   ds:[esi] - far ptr to value bytes in execution code
;               fs:[edi] - where to store output
;
; Upon exit:    fs:[edi] - is updated
;
    push    eax
    mov     eax,dword ptr ds:[esi]
    .IF (eax >= 80000000h || eax == 0)
      ; It's negative
        push    ebx
        mov     ebx,eax
        neg     ebx
        rol     ebx,8
        mov     byte ptr fs:[edi+0],'-'
        mov     al,bl
        call    convert_al_to_hex
        mov     word ptr fs:[edi+1],ax
        rol     ebx,8
        mov     al,bl
        call    convert_al_to_hex
        mov     word ptr fs:[edi+3],ax
        rol     ebx,8
        mov     al,bl
        call    convert_al_to_hex
        mov     word ptr fs:[edi+5],ax
        rol     ebx,8
        mov     al,bl
        pop     ebx
    .ELSE
      ; It's positive
        mov     byte ptr fs:[edi+0],'+'
        mov     al,byte ptr ds:[esi+3]
        call    convert_al_to_hex
        mov     word ptr fs:[edi+1],ax
        mov     al,byte ptr ds:[esi+2]
        call    convert_al_to_hex
        mov     word ptr fs:[edi+3],ax
        mov     al,byte ptr ds:[esi+1]
        call    convert_al_to_hex
        mov     word ptr fs:[edi+5],ax
        mov     al,byte ptr ds:[esi+0]
    .ENDIF
    call    convert_al_to_hex
    mov     word ptr fs:[edi+7],ax
    add     edi,9
    add     fs:parameters_text_length,9
    mov     eax,dword ptr ds:[esi]
    mov     dword ptr fs:displacement_data,eax
    add     esi,4
    add     fs:instruction_bytes,4
    pop     eax
    ret
store_32_bit_signed_value       ENDP




store_signed_dword_in_eax       PROC    NEAR
; This routine is used to store a 32-bit value
;
; Upon entry:   eax - dword to store
;          fs:[edi] - where to store output
;
; Upon exit:    fs:[edi] - is updated
;
  ; We have to emulate a bswap here because this code could be run on 386
    push    eax
    .IF (eax >= 80000000h || eax == 0)
      ; It's negative
        push    eax
        push    ebx
        mov     ebx,eax
        neg     ebx
        mov     byte ptr fs:[edi+0],'-'
        rol     ebx,8
        mov     al,bl
        call    convert_al_to_hex
        mov     word ptr fs:[edi+1],ax
        rol     ebx,8
        mov     al,bl
        call    convert_al_to_hex
        mov     word ptr fs:[edi+3],ax
        rol     ebx,8
        mov     al,bl
        call    convert_al_to_hex
        mov     word ptr fs:[edi+5],ax
        pop     ebx
        neg     dword ptr ss:[esp]
    .ELSE
      ; It's positive
        mov     byte ptr fs:[edi+0],'+'
        mov     al,byte ptr ss:[esp+3]
        call    convert_al_to_hex
        mov     word ptr fs:[edi+1],ax
        mov     al,byte ptr ss:[esp+2]
        mov     al,ah
        call    convert_al_to_hex
        mov     word ptr fs:[edi+3],ax
        mov     al,byte ptr ss:[esp+1]
        mov     al,ah
        call    convert_al_to_hex
        mov     word ptr fs:[edi+5],ax
    .ENDIF
    pop     eax
    call    convert_al_to_hex
    mov     word ptr fs:[edi+7],ax
    add     edi,9
    ret
store_signed_dword_in_eax       ENDP




store_16_bit_signed_value       PROC    NEAR
; This routine is used to store a 16-bit value
;
; Upon entry:   ds:[esi] - far ptr to value bytes in execution code
;               fs:[edi] - where to store output
;
; Upon exit:    fs:[edi] - is updated
;
    push    eax

    mov     ax,word ptr ds:[esi]
    .IF (ax >= 8000h || ax == 0)
      ; It's negative
        push    ebx
        mov     ebx,eax
        shl     ebx,16
        neg     ebx
        mov     byte ptr fs:[edi+0],'-'
        rol     ebx,8
        mov     al,bl
        call    convert_al_to_hex
        mov     word ptr fs:[edi+1],ax
        rol     ebx,8
        mov     al,bl
        pop     ebx
    .ELSE
      ; It's positive
        mov     byte ptr fs:[edi+0],'+'
        mov     al,byte ptr ds:[esi+1]
        call    convert_al_to_hex
        mov     word ptr fs:[edi+1],ax
        mov     al,byte ptr ds:[esi+0]
    .ENDIF
    call    convert_al_to_hex
    mov     word ptr fs:[edi+3],ax
    add     edi,5
    add     fs:parameters_text_length,5
    movzx   eax,word ptr ds:[esi]
    mov     dword ptr fs:displacement_data,eax
    add     esi,2
    add     fs:instruction_bytes,2

    pop     eax
    ret
store_16_bit_signed_value       ENDP




store_signed_word_in_ax     PROC    NEAR
; This routine is used to store a 16-bit value in ax
;
; Upon entry:   ax - word to store
;         fs:[edi] - where to store output
;
; Upon exit:    fs:[edi] - is updated
;
    .IF (ax >= 8000h || ax == 0)
      ; It's negative
        push    eax
        mov     byte ptr fs:[edi+0],'-'
        neg     al
        call    convert_al_to_hex
        mov     word ptr fs:[edi+1],ax
        pop     eax
        mov     al,ah
        neg     al
    .ELSE
      ; It's positive
        push    eax
        mov     byte ptr fs:[edi+0],'+'
        mov     al,byte ptr ds:[esi+1]
        call    convert_al_to_hex
        mov     word ptr fs:[edi+1],ax
        pop     eax
        mov     al,ah
    .ENDIF
    call    convert_al_to_hex
    mov     word ptr fs:[edi+3],ax
    add     edi,5

    pop     eax
    ret
store_signed_word_in_ax     ENDP




store_8_bit_signed_value        PROC    NEAR
; This routine is used to store a 8-bit value
;
; Upon entry:   ds:[esi] - far ptr to value bytes in execution code
;               fs:[edi] - where to store output
;
; Upon exit:    fs:[edi] - is updated
;
    push    eax
    push    ebx

    mov     al,byte ptr ds:[esi]
    .IF (al >= 80h || al == 0)
      ; It's negative
        neg     al
        mov     bl,'-'
    .ELSE
      ; It's positive
        mov     bl,'+'
    .ENDIF
    call    convert_al_to_hex
    mov     byte ptr fs:[edi+0],bl
    mov     word ptr fs:[edi+1],ax
    add     edi,3
    add     fs:parameters_text_length,3
    movzx   eax,byte ptr ds:[esi]
    mov     fs:displacement_data,eax
    inc     esi
    inc     fs:instruction_bytes

    pop     ebx
    pop     eax
    ret
store_8_bit_signed_value        ENDP




store_signed_value      PROC    NEAR
; This routine is used to store the value based on the current size
;
; Upon entry:   ds:[esi] - far ptr to value bytes in instruction
;               fs:[edi] - where to store output
;
; Upon exit:
;
    .IF ((fs:cpu_mode == 0 && fs:op_size_override != 0) || (fs:cpu_mode != 0 && fs:op_size_override == 0))
      ; 16-bit
        call    store_16_bit_signed_value
    .ELSE
      ; 32-bit
        call    store_32_bit_signed_value
    .ENDIF
    ret
store_signed_value      ENDP




store_string    PROC    NEAR
; This routine is used to store a string
;
; Upon entry:   stack is arranged as below
;               fs:[edi] - where to store string
;
; Upon exit:    fs:[edi] - updated
;
    push    eax

  ; [esp+08] - offset to string
  ; [esp+04] - calling ip
  ; [esp+00] - eax
    xchg    esi,dword ptr ss:[esp+8]
    .WHILE (byte ptr fs:[esi] != 0)
        mov     al,byte ptr fs:[esi]
        mov     byte ptr fs:[edi],al
        inc     edi
        inc     esi
    .ENDW
    xchg    dword ptr ss:[esp+8],esi

    pop     eax
    ret 4
store_string    ENDP




store_comma     PROC    NEAR
; This routine stores a comma
;
; Upon entry:   es:[edi] - where to store
;
; Upon exit:    It's stored
;
    mov     byte ptr fs:[edi],','
    inc     edi
    inc     fs:parameters_text_length
    ret
store_comma     ENDP




store_comma_one     PROC    NEAR
; This routine stores a ",1"
;
; Upon entry:   es:[edi] - where to store
;
; Upon exit:    It's stored
;
    mov     word ptr fs:[edi],'1,'
    add     edi,2
    add     fs:parameters_text_length,2
    ret
store_comma_one     ENDP




store_comma_cl      PROC    NEAR
; This routine stores a ",cl"
;
; Upon entry:   es:[edi] - where to store
;
; Upon exit:    It's stored
;
    mov     word ptr fs:[edi],'c,'
    mov     byte ptr fs:[edi+2],'l'
    add     edi,3
    add     fs:parameters_text_length,3
    ret
store_comma_cl      ENDP




store_colon     PROC    NEAR
; This routine stores a colon
;
; Upon entry:   es:[edi] - where to store
;
; Upon exit:    It's stored
;
    mov     byte ptr fs:[edi],':'
    inc     edi
    inc     fs:parameters_text_length
    ret
store_colon     ENDP




store_open_bracket      PROC    NEAR
; This routine stores an opening bracket
;
; Upon entry:   es:[edi] - where to store
;
; Upon exit:    It's stored
;
    mov     byte ptr fs:[edi],'['
    inc     edi
    inc     fs:parameters_text_length
    ret
store_open_bracket      ENDP




store_close_bracket     PROC    NEAR
; This routine stores a closing bracket
;
; Upon entry:   es:[edi] - where to store
;
; Upon exit:    It's stored
;
    mov     byte ptr fs:[edi],']'
    inc     edi
    inc     fs:parameters_text_length
    ret
store_close_bracket     ENDP





x86_simplify_disassembly    PROC
; This routine is used to simply the expression created above into the traditional assembly format:
;
;
; Upon entry:   es:[edi] - far ptr to string to disassembly cask generated above
;               fs:[ebx] - far ptr to string to store (can be uninitialized, this algorithm resets it to spaces)
;                    ecx - maximum width for string at fs:[ebx]
;                    eax - maximum width to devote to instruction bytes
;
; Upon exit:    fs:[ebx] - string is updated if carry? is clear
;                 carry? - SET if error in formatting, CLEAR if ok
;
    .IF (byte ptr es:[edi] == '(')
      ; It opens with a parenthesis, make sure all the |'s are there and it has a closing parenthesis
        push    gs
        pushad
      ; [esp+32] - fs
      ; [esp+28] - eax
      ; [esp+24] - ecx
      ; [esp+20] - edx
      ; [esp+16] - ebx
      ; [esp+12] - esp
      ; [esp+08] - ebp
      ; [esp+04] - esi
      ; [esp+00] - edi

        mov     gs,cs:data_segment

        mov     ebx,1
        xor     edx,edx
        .WHILE (byte ptr es:[edi+ebx] != ')' && ebx < 100)
            .IF (byte ptr es:[edi+ebx] == '|')
                inc     edx
                .IF (edx == 1)
                  ; Start of prefix bytes
                    mov     gs:prefix_bytes_start,ebx
                    inc     gs:prefix_bytes_start
                .ELSEIF (edx == 2)
                  ; End of prefix bytes
                    mov     gs:prefix_bytes_end,ebx
                  ; Start of instruction bytes
                    mov     gs:instruction_bytes_start,ebx
                    inc     gs:instruction_bytes_start
                .ELSEIF (edx == 3)
                  ; End of instruction bytes
                    mov     gs:instruction_bytes_end,ebx
                .ELSEIF (edx == 8)
                  ; Start of instruction text
                    mov     gs:instruction_text_start,ebx
                    inc     gs:instruction_text_start
                .ELSEIF (edx == 9)
                  ; End of instruction text
                    mov     gs:instruction_text_end,ebx
                  ; Start of parameters text
                    mov     gs:parameters_text_start,ebx
                    inc     gs:parameters_text_start
                .ELSEIF (edx == 10)
                  ; End of parameters text
                    mov     gs:parameters_text_end,ebx
                .ENDIF
            .ENDIF
            inc     ebx
          @@:
        .ENDW
        .IF (edx == 16)
          ; It seems to be in the right format, begin copying
            mov     ebx,dword ptr ss:[esp+16]
            .IF (eax == 0)
              ; They don't want prefix bytes, so we just copy the instruction
                jmp     copy_instruction
            .ENDIF
            mov     esi,gs:prefix_bytes_start
            .IF (byte ptr es:[edi+esi] == '|')
              ; There are no prefix bytes
                mov     esi,gs:instruction_bytes_start
            .ENDIF
            .WHILE (eax > 0 && ecx > 0)
                mov     dl,byte ptr es:[edi+esi]
                mov     byte ptr fs:[ebx],dl
                inc     ebx
                inc     esi
                dec     eax
                dec     ecx
                .IF (esi == gs:prefix_bytes_end)
                  ; We're switching over to instruction bytes
                    mov     byte ptr fs:[ebx],':'
                    inc     ebx
                    dec     eax
                    dec     ecx
                    .IF (eax == 0 || ecx == 0)
                        jmp     all_bytes_displayed
                    .ENDIF
                    mov     esi,gs:instruction_bytes_start
                .ELSEIF (esi == gs:instruction_bytes_end)
                  ; We're finished copying bytes, now we pad with spaces
                    jmp     all_bytes_displayed
                .ENDIF
            .ENDW
          ; If we're here then we have more instruction bytes then they've allocated space for
            .IF (dword ptr ss:[esp+28] != 0)
              ; There's enough room for us to add ".." or ">"
                .IF (dword ptr ss:[esp+28] >= 2)
                    mov     word ptr fs:[ebx-2],'..'
                .ELSE
                    mov     byte ptr fs:[ebx-1],'>'
                .ENDIF
                jmp     prefix_instruction_with_pad_space
            .ENDIF

          all_bytes_displayed:
          ; Now we have to stick spaces between the end of the bytes and where the instruction will go
            .WHILE (eax > 0 && ecx > 0)
                mov     byte ptr fs:[ebx],' '
                inc     ebx
                dec     eax
                dec     ecx
            .ENDW

          ; Right now we've copied over any prefix instruction bytes they want
          prefix_instruction_with_pad_space:
            .IF (dword ptr ss:[esp+28] != 0 && ecx >= 1)
              ; There were opcodes, we need to add a space
                mov     byte ptr fs:[ebx],' '
                inc     ebx
                dec     ecx
            .ENDIF

          ; Now, we're ready to copy the instruction
          copy_instruction:
            mov     esi,gs:instruction_text_start
            xor     edx,edx
            .WHILE (ecx > 0 && esi < gs:instruction_text_end)
                mov     al,byte ptr es:[edi+esi]
                mov     byte ptr fs:[ebx],al
                inc     ebx
                inc     esi
                inc     edx
                dec     ecx
            .ENDW

            .IF (edx >= 7 && ecx > 0)
              ; The instruction is the maximum length (like cmpxchg)
                mov     byte ptr fs:[ebx],' '
                inc     edx
                inc     ebx
                dec     ecx
            .ENDIF

          ; Now, put spaces out to the 8th position from the start of the instruction
            .WHILE (ecx > 0 && edx < 7)
                mov     byte ptr fs:[ebx],' '
                inc     ebx
                dec     ecx
                inc     edx
            .ENDW

          copy_parameters:
            mov     esi,gs:parameters_text_start
            .WHILE (ecx > 0 && esi < gs:parameters_text_end)
                mov     dl,byte ptr es:[edi+esi]
                mov     byte ptr fs:[ebx],dl
                inc     ebx
                inc     esi
                dec     ecx
            .ENDW

          ; Now, put spaces out to the end of whatever string length they specified
            .WHILE (ecx > 0)
                mov     byte ptr fs:[ebx],' '
                inc     ebx
                dec     ecx
            .ENDW

          ; NULL terminate it
            mov     byte ptr fs:[ebx],0

            clc
        .ELSE
            stc
        .ENDIF

        popad
        pop     gs
    .ELSE
        stc
    .ENDIF
    retf
x86_simplify_disassembly    ENDP




X86_fpu_opcode      PROC
; This routine is used to disassemble an FPU opcode
;
; Upon entry:   ebx - opcode sequence
;
; Upon exit:    ds:[esi] - far ptr to opcode string
;                    ecx - length of string
;
    pushad

    .IF (bh >= 0d8h && bh <= 0dfh)
        xor     esi,esi
        mov     ecx,4
        .IF (bh == 0d8h)
            mov     di,(lowword(offset st0_comma_sti_text))
            .IF (bl >= 0c0h && bl <= 0c7h)
              ; It's FADD st(0),st(i)
                mov     si,(lowword(offset fadd_text))
            .ELSEIF (bl >= 0c8h && bl <= 0cfh)
              ; It's FMUL st(0),st(i)
                mov     si,(lowword(offset fmul_text))
            .ELSEIF (bl >= 0d0h && bl <= 0d7h)
              ; It's FCOM st(0),st(i)
                mov     si,(lowword(offset fcom_text))
            .ELSEIF (bl >= 0d8h && bl <= 0dfh)
              ; It's FCOMP st(0),st(i)
                mov     ecx,5
                mov     si,(lowword(offset fcomp_text))
            .ELSEIF (bl >= 0e0h && bl <= 0e7h)
              ; It's FSUB st(0),st(i)
                mov     si,(lowword(offset fsub_text))
            .ELSEIF (bl >= 0e8h && bl <= 0efh)
              ; It's FSUBR st(0),st(i)
                mov     ecx,5
                mov     si,(lowword(offset fsubr_text))
            .ELSEIF (bl >= 0f0h && bl <= 0f7h)
              ; It's FDIV st(0),st(i)
                mov     si,(lowword(offset fdiv_text))
            .ELSEIF (bl >= 0f8h && bl <= 0ffh)
              ; It's FDIVR st(0),st(i)
                mov     ecx,5
                mov     si,(lowword(offset fdivr_text))
            .ELSE
                mov     di,(lowword(offset real4_text))
                shr     bl,3
                and     bl,111b
                .IF (bl == 000b)
                  ; It's FADD real4
                    mov     si,(lowword(offset fadd_text))
                .ELSEIF (bl == 001b)
                  ; It's FMUL real4
                    mov     si,(lowword(offset fmul_text))
                .ELSEIF (bl == 010b)
                  ; It's FCOM real4
                    mov     si,(lowword(offset fcom_text))
                .ELSEIF (bl == 011b)
                  ; It's FCOMP real4
                    mov     ecx,5
                    mov     si,(lowword(offset fcomp_text))
                .ELSEIF (bl == 100b)
                  ; It's FSUB real4
                    mov     si,(lowword(offset fsub_text))
                .ELSEIF (bl == 101b)
                  ; It's FSUBR real4
                    mov     ecx,5
                    mov     si,(lowword(offset fsubr_text))
                .ELSEIF (bl == 110b)
                  ; It's FDIV real4
                    mov     si,(lowword(offset fdiv_text))
                .ELSE
                  ; It's FDIVR real4
                    mov     ecx,5
                    mov     si,(lowword(offset fdivr_text))
                .ENDIF
            .ENDIF
        .ELSEIF (bh == 0d9h)
            mov     di,(lowword(offset null_text))
            .IF (bl >= 0c0h && bl <= 0c7h)
              ; It's FLD st(i)
                mov     ecx,3
                mov     si,(lowword(offset fld_text))
                mov     di,(lowword(offset sti_text))
            .ELSEIF (bl >= 0c8h && bl <= 0cfh)
              ; It's FXCH st(i)
                mov     si,(lowword(offset fxch_text))
                mov     di,(lowword(offset sti_text))
            .ELSEIF (bl == 0d0h)
              ; fnop
                mov     si,(lowword(offset fnop_text))
            .ELSEIF (bl == 0e0h)
              ; fchs
                mov     si,(lowword(offset fchs_text))
            .ELSEIF (bl == 0e1h)
              ; fabs
                mov     si,(lowword(offset fabs_text))
            .ELSEIF (bl == 0e4h)
              ; ftst
                mov     si,(lowword(offset ftst_text))
            .ELSEIF (bl == 0e5h)
              ; fxam
                mov     si,(lowword(offset fxam_text))
            .ELSEIF (bl == 0e8h)
              ; fld1
                mov     si,(lowword(offset fld1_text))
            .ELSEIF (bl == 0e9h)
              ; fldl2t
                mov     ecx,6
                mov     si,(lowword(offset fldl2t_text))
            .ELSEIF (bl == 0eah)
              ; fldl2e
                mov     ecx,6
                mov     si,(lowword(offset fldl2e_text))
            .ELSEIF (bl == 0ebh)
              ; fldpi
                mov     ecx,5
                mov     si,(lowword(offset fldpi_text))
            .ELSEIF (bl == 0ech)
              ; fldlg2
                mov     ecx,6
                mov     si,(lowword(offset fldlg2_text))
            .ELSEIF (bl == 0edh)
              ; fldln2
                mov     ecx,6
                mov     si,(lowword(offset fldln2_text))
            .ELSEIF (bl == 0eeh)
              ; fldz
                mov     si,(lowword(offset fldz_text))
            .ELSEIF (bl == 0f0h)
              ; f2xm1
                mov     ecx,5
                mov     si,(lowword(offset f2xm1_text))
            .ELSEIF (bl == 0f1h)
              ; fyl2x
                mov     ecx,5
                mov     si,(lowword(offset fyl2x_text))
            .ELSEIF (bl == 0f2h)
              ; fptan
                mov     ecx,5
                mov     si,(lowword(offset fptan_text))
            .ELSEIF (bl == 0f3h)
              ; fpatan
                mov     ecx,6
                mov     si,(lowword(offset fpatan_text))
            .ELSEIF (bl == 0f4h)
              ; fxtract
                mov     ecx,7
                mov     si,(lowword(offset fxtract_text))
            .ELSEIF (bl == 0f5h)
              ; fprem1
                mov     ecx,6
                mov     si,(lowword(offset fprem1_text))
            .ELSEIF (bl == 0f6h)
              ; fdecstp
                mov     ecx,7
                mov     si,(lowword(offset fdecstp_text))
            .ELSEIF (bl == 0f7h)
              ; fincstp
                mov     ecx,7
                mov     si,(lowword(offset fincstp_text))
            .ELSEIF (bl == 0f8h)
              ; fprem
                mov     ecx,5
                mov     si,(lowword(offset fprem_text))
            .ELSEIF (bl == 0f9h)
              ; fyl2xp1
                mov     ecx,7
                mov     si,(lowword(offset fyl2xp1_text))
            .ELSEIF (bl == 0fah)
              ; fsqrt
                mov     ecx,5
                mov     si,(lowword(offset fsqrt_text))
            .ELSEIF (bl == 0fbh)
              ; fsincos
                mov     ecx,7
                mov     si,(lowword(offset fsincos_text))
            .ELSEIF (bl == 0fch)
              ; frndint
                mov     ecx,7
                mov     si,(lowword(offset frndint_text))
            .ELSEIF (bl == 0fdh)
              ; fscale
                mov     ecx,6
                mov     si,(lowword(offset fscale_text))
            .ELSEIF (bl == 0feh)
              ; fsin
                mov     si,(lowword(offset fsin_text))
            .ELSEIF (bl == 0ffh)
              ; fcos
                mov     si,(lowword(offset fcos_text))
            .ELSE
                shr     bl,3
                and     bl,111b
                mov     di,(lowword(offset real4_text))
                .IF (bl == 000b)
                  ; It's FLD real4
                    mov     ecx,3
                    mov     si,(lowword(offset fld_text))
                .ELSEIF (bl == 010b)
                  ; It's FST real4
                    mov     ecx,3
                    mov     si,(lowword(offset fst_text))
                .ELSEIF (bl == 011b)
                  ; It's FSTP real4
                    mov     ecx,4
                    mov     si,(lowword(offset fstp_text))
                .ELSEIF (bl == 100b)
                  ; It's fldenv
                    mov     ecx,6
                    mov     si,(lowword(offset fldenv_text))
                    mov     di,(lowword(offset null_text))
                .ELSEIF (bl == 101b)
                  ; It's fldcw m16
                    mov     ecx,5
                    mov     si,(lowword(offset fldcw_text))
                    mov     di,(lowword(offset word_text))
                .ELSEIF (bl == 110b)
                  ; It's fnstenv
                    mov     ecx,7
                    mov     si,(lowword(offset fnstenv_text))
                    mov     di,(lowword(offset null_text))
                .ELSEIF (bl == 111b)
                  ; It's fnstcw m16
                    mov     ecx,6
                    mov     si,(lowword(offset fnstcw_text))
                    mov     di,(lowword(offset word_text))
                .ELSE
                    jmp     unknown_fpu_opcode
                .ENDIF
            .ENDIF
        .ELSEIF (bh == 0dah)
            mov     di,(lowword(offset st0_comma_sti_text))
            .IF (bl >= 0c0h && bl <= 0c7h)
              ; It's FCMOVB st0,sti
                mov     ecx,6
                mov     si,(lowword(offset fcmovb_text))
            .ELSEIF (bl >= 0c8h && bl <= 0cfh)
              ; It's FCMOVZ st0,sti
                mov     ecx,6
                mov     si,(lowword(offset fcmovz_text))
            .ELSEIF (bl >= 0d0h && bl <= 0d7h)
              ; It's FCMOVNG st0,sti
                mov     ecx,7
                mov     si,(lowword(offset fcmovng_text))
            .ELSEIF (bl >= 0d8h && bl <= 0dFh)
              ; It's FCMOVPO st0,sti
                mov     ecx,7
                mov     si,(lowword(offset fcmovpo_text))
            .ELSEIF (bl == 0e9h)
              ; It's FUCOMPP
                mov     ecx,7
                mov     si,(lowword(offset fucompp_text))
                mov     di,(lowword(offset null_text))
            .ELSE
                mov     di,(lowword(offset dword_text))
                mov     ecx,5
                shr     bl,3
                and     bl,111b
                .IF (bl == 000b)
                  ; It's FIADD m32_int
                    mov     si,(lowword(offset fiadd_text))
                .ELSEIF (bl == 001b)
                  ; It's FIMUL m32_int
                    mov     si,(lowword(offset fimul_text))
                .ELSEIF (bl == 010b)
                  ; It's FICOM m32_int
                    mov     si,(lowword(offset ficom_text))
                .ELSEIF (bl == 011b)
                  ; It's FICOMP m32_int
                    inc     ecx
                    mov     si,(lowword(offset ficomp_text))
                .ELSEIF (bl == 100b)
                  ; It's FISUB m32_int
                    mov     si,(lowword(offset fisub_text))
                .ELSEIF (bl == 101b)
                  ; It's FISUBR m32_int
                    inc     ecx
                    mov     si,(lowword(offset fisubr_text))
                .ELSEIF (bl == 110b)
                  ; It's FIDIV m32_int
                    mov     si,(lowword(offset fidiv_text))
                .ELSE
                  ; It's FIDIVR m32_int
                    inc     ecx
                    mov     si,(lowword(offset fidivr_text))
                .ENDIF
            .ENDIF
        .ELSEIF (bh == 0dbh)
            mov     ecx,7
            mov     di,(lowword(offset st0_comma_sti_text))
            .IF (bl >= 0c0h && bl <= 0c7h)
              ; It's FCMOVNB st0,sti
                mov     si,(lowword(offset fcmovnb_text))
            .ELSEIF (bl >= 0c8h && bl <= 0cfh)
              ; It's FCMOVNZ st0,sti
                mov     si,(lowword(offset fcmovnz_text))
            .ELSEIF (bl >= 0d0h && bl <= 0d7h)
              ; It's FCMOVG st0,sti
                dec     ecx
                mov     si,(lowword(offset fcmovg_text))
            .ELSEIF (bl >= 0d8h && bl <= 0dfh)
              ; It's FCMOVPE st0,sti
                mov     si,(lowword(offset fcmovpe_text))
            .ELSEIF (bl == 0e2h)
              ; It's fnclex
                dec     ecx
                mov     si,(lowword(offset fnclex_text))
                mov     di,(lowword(offset null_text))
            .ELSEIF (bl == 0e3h)
              ; It's fninit
                dec     ecx
                mov     si,(lowword(offset fninit_text))
                mov     di,(lowword(offset null_text))
            .ELSEIF (bl >= 0e8h && bl <= 0efh)
              ; It's FUCOMI st(0),st(i)
                dec     ecx
                mov     si,(lowword(offset fucomi_text))
            .ELSEIF (bl >= 0f0h && bl <= 0f7h)
              ; It's FCOMI st(0),st(i)
                mov     ecx,5
                mov     si,(lowword(offset fcomi_text))
            .ELSE
                mov     di,(lowword(offset dword_text))
                mov     ecx,4
                shr     bl,3
                and     bl,111b
                .IF (bl == 000b)
                  ; It's FILD m32_int
                    mov     si,(lowword(offset fild_text))
                .ELSEIF (bl == 010b)
                  ; It's FIST m32_int
                    mov     si,(lowword(offset fist_text))
                .ELSEIF (bl == 011b)
                  ; It's FISTP m32_int
                    mov     si,(lowword(offset fistp_text))
                .ELSEIF (bl == 101b)
                  ; It's FLD real10
                    dec     ecx
                    mov     si,(lowword(offset fld_text))
                    mov     di,(lowword(offset real10_text))
                .ELSEIF (bl == 111b)
                  ; It's FSTP real10
                    mov     si,(lowword(offset fstp_text))
                    mov     di,(lowword(offset real10_text))
                .ELSE
                    jmp     unknown_fpu_opcode
                .ENDIF
            .ENDIF
        .ELSEIF (bh == 0dch)
            mov     di,(lowword(offset sti_comma_st0_text))
            .IF (bl >= 0c0h && bl <= 0c7h)
              ; It's FADD st(i),st(0)
                mov     si,(lowword(offset fadd_text))
            .ELSEIF (bl >= 0c8h && bl <= 0cfh)
              ; It's FMUL st(i),st(0)
                mov     si,(lowword(offset fmul_text))
            .ELSEIF (bl >= 0e0h && bl <= 0e7h)
              ; It's FSUBR st(i),st(0)
                inc     ecx
                mov     si,(lowword(offset fsubr_text))
            .ELSEIF (bl >= 0e8h && bl <= 0efh)
              ; It's FSUB st(i),st(0)
                mov     si,(lowword(offset fsub_text))
            .ELSEIF (bl >= 0f0h && bl <= 0f7h)
              ; It's FDIVR st(i),st(0)
                inc     ecx
                mov     si,(lowword(offset fdivr_text))
            .ELSEIF (bl >= 0f8h && bl <= 0ffh)
              ; It's FDIV st(i),st(0)
                mov     si,(lowword(offset fdiv_text))
            .ELSE
                mov     di,(lowword(offset real8_text))
                shr     bl,3
                and     bl,111b
                .IF (bl == 000b)
                  ; It's FADD real8
                    mov     si,(lowword(offset fadd_text))
                .ELSEIF (bl == 001b)
                  ; It's FMUL real8
                    mov     si,(lowword(offset fmul_text))
                .ELSEIF (bl == 010b)
                  ; It's FCOM real8
                    mov     si,(lowword(offset fcom_text))
                .ELSEIF (bl == 011b)
                  ; It's FCOMP real8
                    inc     ecx
                    mov     si,(lowword(offset fcomp_text))
                .ELSEIF (bl == 100b)
                  ; It's FSUB real8
                    mov     si,(lowword(offset fsub_text))
                .ELSEIF (bl == 101b)
                  ; It's FSUBR real8
                    inc     ecx
                    mov     si,(lowword(offset fsubr_text))
                .ELSEIF (bl == 110b)
                  ; It's FDIV real8
                    mov     si,(lowword(offset fdiv_text))
                .ELSE
                  ; It's FDIVR real8
                    inc     ecx
                    mov     si,(lowword(offset fdivr_text))
                .ENDIF
            .ENDIF
        .ELSEIF (bh == 0ddh)
            mov     di,(lowword(offset sti_text))
            .IF (bl >= 0c0h && bl <= 0c7h)
              ; It's FFREE st(i)
                inc     ecx
                mov     si,(lowword(offset ffree_text))
            .ELSEIF (bl >= 0d0h && bl <= 0d7h)
              ; It's FST st(i)
                dec     ecx
                mov     si,(lowword(offset fst_text))
            .ELSEIF (bl >= 0d8h && bl <= 0dfh)
              ; It's FSTP st(i)
                mov     si,(lowword(offset fstp_text))
            .ELSEIF (bl >= 0e0h && bl <= 0e7h)
              ; It's FUCOM st(i)
                inc     ecx
                mov     si,(lowword(offset fucom_text))
            .ELSEIF (bl >= 0e8h && bl <= 0efh)
              ; It's FUCOMP st(i)
                mov     ecx,6
                mov     si,(lowword(offset fucomp_text))
            .ELSEIF (bl == 0e9h)
              ; It's FUCOMPP
                mov     ecx,7
                mov     si,(lowword(offset fucompp_text))
                mov     di,(lowword(offset null_text))
            .ELSE
                mov     di,(lowword(offset real8_text))
                shr     bl,3
                and     bl,111b
                .IF (bl == 000b)
                  ; It's FLD real8
                    dec     ecx
                    mov     si,(lowword(offset fld_text))
                .ELSEIF (bl == 010b)
                  ; It's FST real8
                    dec     ecx
                    mov     si,(lowword(offset fst_text))
                .ELSEIF (bl == 011b)
                  ; It's FSTP real8
                    mov     si,(lowword(offset fstp_text))
                .ELSEIF (bl == 100b)
                  ; It's FRSTOR m94/108
                    mov     ecx,6
                    mov     si,(lowword(offset frstor_text))
                    mov     di,(lowword(offset bytes_94_108_text))
                .ELSEIF (bl == 110b)
                  ; It's FNSAVE
                    mov     ecx,6
                    mov     si,(lowword(offset fnsave_text))
                    mov     di,(lowword(offset null_text))
                .ELSEIF (bl == 111b)
                  ; It's FNSTSW
                    mov     ecx,6
                    mov     si,(lowword(offset fnstsw_text))
                    mov     di,(lowword(offset null_text))
                .ELSE
                    jmp     unknown_fpu_opcode
                .ENDIF
            .ENDIF
        .ELSEIF (bh == 0deh)
            mov     di,(lowword(offset sti_comma_st0_text))
            mov     ecx,5
            .IF (bl >= 0c0h && bl <= 0c7h)
              ; It's FADDP st(i),st(0)
                mov     si,(lowword(offset faddp_text))
            .ELSEIF (bl >= 0c8h && bl <= 0cfh)
              ; It's FMULP st(i),st(0)
                mov     si,(lowword(offset fmulp_text))
            .ELSEIF (bl == 0d9h)
              ; It's FCOMPP
                inc     ecx
                mov     si,(lowword(offset fcompp_text))
            mov     di,(lowword(offset null_text))
            .ELSEIF (bl >= 0e0h && bl <= 0e7h)
              ; It's FSUBRP st(i),st(0)
                inc     ecx
                mov     si,(lowword(offset fsubrp_text))
            .ELSEIF (bl >= 0e8h && bl <= 0efh)
              ; It's FSUBP st(i),st(0)
                mov     si,(lowword(offset fsubp_text))
            .ELSEIF (bl >= 0f0h && bl <= 0f7h)
              ; It's FDIVRP st(i),st(0)
                inc     ecx
                mov     si,(lowword(offset fdivrp_text))
            .ELSEIF (bl >= 0f8h && bl <= 0ffh)
              ; It's FDIVP st(i),st(0)
                mov     si,(lowword(offset fdivp_text))
            .ELSE
                mov     di,(lowword(offset word_text))
                shr     bl,3
                and     bl,111b
                .IF (bl == 000b)
                  ; It's FIADD m64_int
                    mov     si,(lowword(offset fiadd_text))
                    mov     di,(lowword(offset qword_text))
                .ELSEIF (bl == 001b)
                  ; It's FIMUL m16_int
                    mov     si,(lowword(offset fimul_text))
                .ELSEIF (bl == 010b)
                  ; It's FICOM m16_int
                    mov     si,(lowword(offset ficom_text))
                .ELSEIF (bl == 011b)
                  ; It's FICOMP m16_int
                    inc     ecx
                    mov     si,(lowword(offset ficomp_text))
                .ELSEIF (bl == 100b)
                  ; It's FISUB m16_int
                    mov     si,(lowword(offset fisub_text))
                .ELSEIF (bl == 101b)
                  ; It's FISUBR m16_int
                    inc     ecx
                    mov     si,(lowword(offset fisubr_text))
                .ELSEIF (bl == 110b)
                  ; It's FIDIV m16_int
                    mov     si,(lowword(offset fidiv_text))
                .ELSE
                  ; It's FIDIVR m16_int
                    inc     ecx
                    mov     si,(lowword(offset fidivr_text))
                .ENDIF
            .ENDIF
        .ELSE
          ; 0xdf
            mov     di,(lowword(offset null_text))
            .IF (bl == 0e0h)
              ; It's FNSTSW
                mov     ecx,6
                mov     si,(lowword(offset fnstsw_text))
            .ELSEIF (bl >= 0e8h && bl <= 0efh)
              ; It's FUCOMIP
                mov     ecx,7
                mov     si,(lowword(offset fucomip_text))
            .ELSEIF (bl >= 0f0h && al <= 0f7h)
              ; It's FCOMIP
                mov     ecx,6
                mov     si,(lowword(offset fcomip_text))
            .ELSE
              ; We have to examine the REG bits
                shr     bl,3
                and     bl,111b
                .IF (bl == 000b)
                  ; It's FILD
                    mov     si,(lowword(offset fild_text))
                .ELSEIF (bl == 010b)
                  ; It's FIST
                    mov     si,(lowword(offset fist_text))
                .ELSEIF (bl == 011b)
                  ; It's FISTP
                    inc     ecx
                    mov     si,(lowword(offset fistp_text))
                .ELSEIF (bl == 100b)
                  ; It's FbhD
                    mov     si,(lowword(offset fbld_text))
                .ELSEIF (bl == 101b)
                  ; It's FILD
                    mov     si,(lowword(offset fild_text))
                .ELSEIF (bl == 111b)
                  ; It's FISTP
                    inc     ecx
                    mov     si,(lowword(offset fistp_text))
                .ELSE
                  ; Unknown
                    jmp     unknown_fpu_opcode
                .ENDIF
            .ENDIF
        .ENDIF
    .ELSE
      unknown_fpu_opcode:
        mov     ecx,sizeof unknown_text - 1
        mov     si,(lowword(offset unknown_text))
        mov     di,(lowword(offset null_text))
    .ENDIF

  ; Now, copy the data over into one output string
    mov     ds,cs:data_segment
    mov     ebx,offset temp_buffer
    .WHILE (ecx > 0)
        mov     al,byte ptr ds:[esi]
        mov     byte ptr ds:[ebx],al
        inc     esi
        inc     ebx
        dec     ecx
    .ENDW
    mov     byte ptr ds:[ebx],32
    inc     ebx

  ; Now, copy the trailing information
    .WHILE (byte ptr ds:[edi] != 0)
        mov     al,byte ptr ds:[edi]
        mov     byte ptr ds:[ebx],al
        inc     edi
        inc     ebx
    .ENDW
    mov     byte ptr ds:[ebx],0                                     ; NULL-terminate (just in case)

  ; Now, determine the length
    mov     esi,offset temp_buffer
    sub     ebx,esi
    mov     ecx,ebx

    mov     dword ptr ss:[esp+24],ecx
    mov     dword ptr ss:[esp+04],esi
    popad
    retf
X86_fpu_opcode      ENDP