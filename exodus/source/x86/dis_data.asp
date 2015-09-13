; dis_data.asp
;
; Data for the x86 Disassembly algorithms
;




;; Macros
@instr_bytes    MACRO   bytes:REQ
    mov     fs:instruction_bytes,bytes
    IF bytes EQ 1
        inc     esi
    ELSE
        add     esi,bytes
    ENDIF
ENDM

@instr_text     MACRO   instr:REQ, len:REQ
    mov     fs:instruction_text_offset,offset instr
    mov     fs:instruction_text_length,len
ENDM

_NO_SPECIAL     EQU 0
_CONTROL_REGS   EQU 1
_DEBUG_REGS     EQU 2
_TEST_REGS      EQU 3
_SEG_REGS       EQU 4
_STx_REGS       EQU 5
_MMX_REGS       EQU 6
_XMM_REGS       EQU 7


;; Data
  ; Used by debi_disassemble_instruction()
    cpu_mode                dd  0                                   ; 0-32 bit pmode, 1-16-bit pmode, 2-real, 3-v86
    prefix_bytes            dd  0
    sreg_override           dd  0
    sign_extend             dd  0
    reverse_regs            dd  0
    special_reg             dd  0
    sib_byte                dd  0
    byte_word_size          dd  0
    seg_override            dd  0
    op_size_override        dd  0
    adr_size_override       dd  0
    reverse_mod_reg_rm      dd  0
    scale_factor            dd  0
    movxx_register          dd  0
    first_gp_register       dd  0
    second_gp_register      dd  0
    display_second_register dd  0
    gp_reg_count            dd  0
    special_control         dd  0

    instruction_offset      dd  0                                   ; Ptr to start of instruction
    instruction_bytes       dd  0                                   ; number of bytes there
    instruction_text_length dd  0                                   ; Ptr to start of instruction text (like "adc")
    instruction_text_offset dd  0                                   ; number of bytes there
    parameters_text_length  dd  0                                   ; Ptr to start of parameters in local memory
    parameters_text_offset  dd  0                                   ; number of bytes there
    displacement_offset     dd  0                                   ; Ptr to start of displacement text (if any) in parameters
    displacement_bytes      dd  0                                   ; number of bytes there (the [esi] part of "ds:[esi],ebx")
    displacement_data       dd  0                                   ; dword value indicating the actual displacement part
                                                                    ; (such as the 1234 value in "ds:[esi+1234]")
    mod_reg_rm_offset       dd  0                                   ; Ptr to start of mod_reg_rm byte in instruction
    mod_reg_rm_bytes        dd  0                                   ; Number of instruction bytes used by mod_reg_rm requirements
    sib_offset              dd  0                                   ; Ptr to start of SIB byte in instruction
    sib_bytes               dd  0                                   ; Number of instruction bytes used by SIB requirements
    immediate_offset        dd  0                                   ; Ptr to start of immediate data in instruction
    immediate_bytes         dd  0                                   ; Number of bytes used in immediate
    immediate_data          dd  0                                   ; The immediate value
    operand_size            dd  0

  ; Used by debi_simplify_disassembly()
    prefix_bytes_start      dd  0                                   ; Start and end of the prefix bytes (if any)
    prefix_bytes_end        dd  0
    instruction_bytes_start dd  0
    instruction_bytes_end   dd  0
    instruction_text_start  dd  0
    instruction_text_end    dd  0
    parameters_text_start   dd  0
    parameters_text_end     dd  0


  opcode_map:
                            dw  lowword(offset _add)                    ; 00
                            dw  lowword(offset _add)                    ; 01
                            dw  lowword(offset _add)                    ; 02
                            dw  lowword(offset _add)                    ; 03
                            dw  lowword(offset _add_immed8)             ; 04
                            dw  lowword(offset _add_immed16_32)         ; 05
                            dw  lowword(offset _push_es)                ; 06
                            dw  lowword(offset _pop_es)                 ; 07
                            dw  lowword(offset _or_rm)                  ; 08
                            dw  lowword(offset _or_rm)                  ; 09
                            dw  lowword(offset _or_rm)                  ; 0a
                            dw  lowword(offset _or_rm)                  ; 0b
                            dw  lowword(offset _or_accum)               ; 0c
                            dw  lowword(offset _or_accum)               ; 0d
                            dw  lowword(offset _push_cs)                ; 0e
                            dw  lowword(offset _two_byte_instruction)   ; 0f
                            dw  lowword(offset _adc)                    ; 10
                            dw  lowword(offset _adc)                    ; 11
                            dw  lowword(offset _adc)                    ; 12
                            dw  lowword(offset _adc)                    ; 13
                            dw  lowword(offset _adc_immed8)             ; 14
                            dw  lowword(offset _adc_immed16_32)         ; 15
                            dw  lowword(offset _push_ss)                ; 16
                            dw  lowword(offset _pop_ss)                 ; 17
                            dw  lowword(offset _sbb_rm_reg8)            ; 18
                            dw  lowword(offset _sbb_rm_reg16_32)        ; 19
                            dw  lowword(offset _sbb_reg8_rm)            ; 1a
                            dw  lowword(offset _sbb_reg16_32_rm)        ; 1b
                            dw  lowword(offset _sbb_accum_immed8)       ; 1c
                            dw  lowword(offset _sbb_accum_immed16_32)   ; 1d
                            dw  lowword(offset _push_ds)                ; 1e
                            dw  lowword(offset _pop_ds)                 ; 1f
                            dw  lowword(offset _and)                    ; 20
                            dw  lowword(offset _and)                    ; 21
                            dw  lowword(offset _and)                    ; 22
                            dw  lowword(offset _and)                    ; 23
                            dw  lowword(offset _and_immed8)             ; 24
                            dw  lowword(offset _and_immed16_32)         ; 25
                            dw  lowword(offset _es_override)            ; 26
                            dw  lowword(offset _daa)                    ; 27
                            dw  lowword(offset _sub_rm_reg8)            ; 28
                            dw  lowword(offset _sub_rm_reg16_32)        ; 29
                            dw  lowword(offset _sub_reg8_rm)            ; 2a
                            dw  lowword(offset _sub_reg16_32_rm)        ; 2b
                            dw  lowword(offset _sub_accum_immed8)       ; 2c
                            dw  lowword(offset _sub_accum_immed16_32)   ; 2d
                            dw  lowword(offset _cs_override)            ; 2e
                            dw  lowword(offset _das)                    ; 2f
                            dw  lowword(offset _xor_rm_reg8)            ; 30
                            dw  lowword(offset _xor_rm_reg16_32)        ; 31
                            dw  lowword(offset _xor_reg8_rm)            ; 32
                            dw  lowword(offset _xor_reg16_32_rm)        ; 33
                            dw  lowword(offset _xor_accum_immed8)       ; 34
                            dw  lowword(offset _xor_accum_immed16_32)   ; 35
                            dw  lowword(offset _ss_override)            ; 36
                            dw  lowword(offset _aaa)                    ; 37
                            dw  lowword(offset _cmp_rm8_r8)             ; 38
                            dw  lowword(offset _cmp_rm16_r16)           ; 39
                            dw  lowword(offset _cmp_r8_rm8)             ; 3a
                            dw  lowword(offset _cmp_r16_rm16)           ; 3b
                            dw  lowword(offset _cmp_immed8)             ; 3c
                            dw  lowword(offset _cmp_immed16_32)         ; 3d
                            dw  lowword(offset _ds_override)            ; 3e
                            dw  lowword(offset _aas)                    ; 3f
                            dw  lowword(offset _inc_xax)                ; 40
                            dw  lowword(offset _inc_xcx)                ; 41
                            dw  lowword(offset _inc_xdx)                ; 42
                            dw  lowword(offset _inc_xbx)                ; 43
                            dw  lowword(offset _inc_xsp)                ; 44
                            dw  lowword(offset _inc_xbp)                ; 45
                            dw  lowword(offset _inc_xsi)                ; 46
                            dw  lowword(offset _inc_xdi)                ; 47
                            dw  lowword(offset _dec_xax)                ; 48
                            dw  lowword(offset _dec_xcx)                ; 49
                            dw  lowword(offset _dec_xdx)                ; 4a
                            dw  lowword(offset _dec_xbx)                ; 4b
                            dw  lowword(offset _dec_xsp)                ; 4c
                            dw  lowword(offset _dec_xbp)                ; 4d
                            dw  lowword(offset _dec_xsi)                ; 4e
                            dw  lowword(offset _dec_xdi)                ; 4f
                            dw  lowword(offset _push_xax)               ; 50
                            dw  lowword(offset _push_xcx)               ; 51
                            dw  lowword(offset _push_xdx)               ; 52
                            dw  lowword(offset _push_xbx)               ; 53
                            dw  lowword(offset _push_xsp)               ; 54
                            dw  lowword(offset _push_xbp)               ; 55
                            dw  lowword(offset _push_xsi)               ; 56
                            dw  lowword(offset _push_xdi)               ; 57
                            dw  lowword(offset _pop_xax)                ; 58
                            dw  lowword(offset _pop_xcx)                ; 59
                            dw  lowword(offset _pop_xdx)                ; 5a
                            dw  lowword(offset _pop_xbx)                ; 5b
                            dw  lowword(offset _pop_xsp)                ; 5c
                            dw  lowword(offset _pop_xbp)                ; 5d
                            dw  lowword(offset _pop_xsi)                ; 5e
                            dw  lowword(offset _pop_xdi)                ; 5f
                            dw  lowword(offset _pusha)                  ; 60
                            dw  lowword(offset _popa)                   ; 61
                            dw  lowword(offset _bound)                  ; 62
                            dw  lowword(offset _arpl)                   ; 63
                            dw  lowword(offset _fs_override)            ; 64
                            dw  lowword(offset _gs_override)            ; 65
                            dw  lowword(offset _op_size_override)       ; 66
                            dw  lowword(offset _adr_size_override)      ; 67
                            dw  lowword(offset _push_immed16_32)        ; 68
                            dw  lowword(offset _imul_3_parms_immed16_32); 69
                            dw  lowword(offset _push_immed8)            ; 6a
                            dw  lowword(offset _imul_3_parms_immed8)    ; 6b
                            dw  lowword(offset _insb)                   ; 6c
                            dw  lowword(offset _insw)                   ; 6d
                            dw  lowword(offset _outsb)                  ; 6e
                            dw  lowword(offset _outsw)                  ; 6f
                            dw  lowword(offset _jo)                     ; 70
                            dw  lowword(offset _jno)                    ; 71
                            dw  lowword(offset _jc)                     ; 72
                            dw  lowword(offset _jnc)                    ; 73
                            dw  lowword(offset _jz)                     ; 74
                            dw  lowword(offset _jnz)                    ; 75
                            dw  lowword(offset _jna)                    ; 76
                            dw  lowword(offset _ja)                     ; 77
                            dw  lowword(offset _js)                     ; 78
                            dw  lowword(offset _jns)                    ; 79
                            dw  lowword(offset _jpe)                    ; 7a
                            dw  lowword(offset _jpo)                    ; 7b
                            dw  lowword(offset _jl)                     ; 7c
                            dw  lowword(offset _jnl)                    ; 7d
                            dw  lowword(offset _jng)                    ; 7e
                            dw  lowword(offset _jg)                     ; 7f
                            dw  lowword(offset _check_reg_80)           ; 80
                            dw  lowword(offset _check_reg_81)           ; 81
                            dw  lowword(offset _check_reg_82)           ; 82
                            dw  lowword(offset _check_reg_83)           ; 83
                            dw  lowword(offset _test_rm_reg_8)          ; 84
                            dw  lowword(offset _test_rm_reg16_32)       ; 85
                            dw  lowword(offset _xchg_byte)              ; 86
                            dw  lowword(offset _xchg)                   ; 87
                            dw  lowword(offset _mov_rm_reg_8)           ; 88
                            dw  lowword(offset _mov_rm_reg_16_32)       ; 89
                            dw  lowword(offset _mov_reg_rm_8)           ; 8a
                            dw  lowword(offset _mov_reg_rm_16_32)       ; 8b
                            dw  lowword(offset _mov_reg16_32_sreg)      ; 8c
                            dw  lowword(offset _lea)                    ; 8d
                            dw  lowword(offset _mov_sreg_reg16_32)      ; 8e
                            dw  lowword(offset _check_reg_8f)           ; 8f
                            dw  lowword(offset _nop)                    ; 90
                            dw  lowword(offset _xchg_xcx)               ; 91
                            dw  lowword(offset _xchg_xdx)               ; 92
                            dw  lowword(offset _xchg_xbx)               ; 93
                            dw  lowword(offset _xchg_xsp)               ; 94
                            dw  lowword(offset _xchg_xbp)               ; 95
                            dw  lowword(offset _xchg_xsi)               ; 96
                            dw  lowword(offset _xchg_xdi)               ; 97
                            dw  lowword(offset _cbw)                    ; 98
                            dw  lowword(offset _cwd)                    ; 99
                            dw  lowword(offset _call_far_operand)       ; 9a
                            dw  lowword(offset _wait)                   ; 9b
                            dw  lowword(offset _pushf)                  ; 9c
                            dw  lowword(offset _popf)                   ; 9d
                            dw  lowword(offset _sahf)                   ; 9e
                            dw  lowword(offset _lahf)                   ; 9f
                            dw  lowword(offset _mov_accum_mem_8)        ; a0
                            dw  lowword(offset _mov_accum_mem_16_32)    ; a1
                            dw  lowword(offset _mov_mem_accum_8)        ; a2
                            dw  lowword(offset _mov_mem_accum_16_32)    ; a3
                            dw  lowword(offset _movsb)                  ; a4
                            dw  lowword(offset _movsw)                  ; a5
                            dw  lowword(offset _cmpsb)                  ; a6
                            dw  lowword(offset _cmpsw)                  ; a7
                            dw  lowword(offset _test_accum_imm8)        ; a8
                            dw  lowword(offset _test_accum_imm16_32)    ; a9
                            dw  lowword(offset _stosb)                  ; aa
                            dw  lowword(offset _stosw)                  ; ab
                            dw  lowword(offset _lodsb)                  ; ac
                            dw  lowword(offset _lodsw)                  ; ad
                            dw  lowword(offset _scasb)                  ; ae
                            dw  lowword(offset _scasw)                  ; af
                            dw  lowword(offset _mov_reg_immed8)         ; b0
                            dw  lowword(offset _mov_reg_immed8)         ; b1
                            dw  lowword(offset _mov_reg_immed8)         ; b2
                            dw  lowword(offset _mov_reg_immed8)         ; b3
                            dw  lowword(offset _mov_reg_immed8)         ; b4
                            dw  lowword(offset _mov_reg_immed8)         ; b5
                            dw  lowword(offset _mov_reg_immed8)         ; b6
                            dw  lowword(offset _mov_reg_immed8)         ; b7
                            dw  lowword(offset _mov_reg_immed16_32)     ; b8
                            dw  lowword(offset _mov_reg_immed16_32)     ; b9
                            dw  lowword(offset _mov_reg_immed16_32)     ; ba
                            dw  lowword(offset _mov_reg_immed16_32)     ; bb
                            dw  lowword(offset _mov_reg_immed16_32)     ; bc
                            dw  lowword(offset _mov_reg_immed16_32)     ; bd
                            dw  lowword(offset _mov_reg_immed16_32)     ; be
                            dw  lowword(offset _mov_reg_immed16_32)     ; bf
                            dw  lowword(offset _check_reg_c0)           ; c0
                            dw  lowword(offset _check_reg_c1)           ; c1
                            dw  lowword(offset _retn_immed)             ; c2
                            dw  lowword(offset _retn)                   ; c3
                            dw  lowword(offset _les)                    ; c4
                            dw  lowword(offset _lds)                    ; c5
                            dw  lowword(offset _check_reg_c6)           ; c6
                            dw  lowword(offset _check_reg_c7)           ; c7
                            dw  lowword(offset _enter)                  ; c8
                            dw  lowword(offset _leave)                  ; c9
                            dw  lowword(offset _retf_immed)             ; ca
                            dw  lowword(offset _retf)                   ; cb
                            dw  lowword(offset _int3)                   ; cc
                            dw  lowword(offset _intx)                   ; cd
                            dw  lowword(offset _into)                   ; ce
                            dw  lowword(offset _iret)                   ; cf
                            dw  lowword(offset _check_reg_d0)           ; d0
                            dw  lowword(offset _check_reg_d1)           ; d1
                            dw  lowword(offset _check_reg_d2)           ; d2
                            dw  lowword(offset _check_reg_d3)           ; d3
                            dw  lowword(offset _aam)                    ; d4
                            dw  lowword(offset _aad)                    ; d5
                            dw  lowword(offset _unused)                 ; d6
                            dw  lowword(offset _xlat)                   ; d7
                            dw  lowword(offset _fpu_d8)                 ; d8
                            dw  lowword(offset _fpu_d9)                 ; d9
                            dw  lowword(offset _fpu_da)                 ; da
                            dw  lowword(offset _fpu_db)                 ; db
                            dw  lowword(offset _fpu_dc)                 ; dc
                            dw  lowword(offset _fpu_dd)                 ; dd
                            dw  lowword(offset _fpu_de)                 ; de
                            dw  lowword(offset _fpu_df)                 ; df
                            dw  lowword(offset _loopne)                 ; e0
                            dw  lowword(offset _loope)                  ; e1
                            dw  lowword(offset _loop)                   ; e2
                            dw  lowword(offset _jcxz)                   ; e3
                            dw  lowword(offset _in8_immed8)             ; e4
                            dw  lowword(offset _in16_32_immed8)         ; e5
                            dw  lowword(offset _out)                    ; e6
                            dw  lowword(offset _out)                    ; e7
                            dw  lowword(offset _call_near_relative)     ; e8
                            dw  lowword(offset _jmp16_32)               ; e9
                            dw  lowword(offset _jmp_far)                ; ea
                            dw  lowword(offset _jmp8)                   ; eb
                            dw  lowword(offset _in_byte)                ; ec
                            dw  lowword(offset _in)                     ; ed
                            dw  lowword(offset _out_byte)               ; ee
                            dw  lowword(offset _out)                    ; ef
                            dw  lowword(offset _lock_prefix)            ; f0
                            dw  lowword(offset _unused)                 ; f1
                            dw  lowword(offset _repne_prefix)           ; f2
                            dw  lowword(offset _repe_prefix)            ; f3
                            dw  lowword(offset _hlt)                    ; f4
                            dw  lowword(offset _cmc)                    ; f5
                            dw  lowword(offset _check_reg_f6)           ; f6
                            dw  lowword(offset _check_reg_f7)           ; f7
                            dw  lowword(offset _clc)                    ; f8
                            dw  lowword(offset _stc)                    ; f9
                            dw  lowword(offset _cli)                    ; fa
                            dw  lowword(offset _sti)                    ; fb
                            dw  lowword(offset _cld)                    ; fc
                            dw  lowword(offset _std)                    ; fd
                            dw  lowword(offset _check_reg_fe)           ; fe
                            dw  lowword(offset _check_reg_ff)           ; ff


; Used by _two_byte_instruction
  two_byte_opcode_map:
                            dw  lowword(offset _check_reg_0f00)         ; 00
                            dw  lowword(offset _check_reg_0f01)         ; 01
                            dw  lowword(offset _lar)                    ; 02
                            dw  lowword(offset _lsl)                    ; 03
                            dw  lowword(offset _two_byte_unused)        ; 04
                            dw  lowword(offset _two_byte_unused)        ; 05
                            dw  lowword(offset _clts)                   ; 06
                            dw  lowword(offset _two_byte_unused)        ; 07
                            dw  lowword(offset _invd)                   ; 08
                            dw  lowword(offset _wbinvd)                 ; 09
                            dw  lowword(offset _two_byte_unused)        ; 0a
                            dw  lowword(offset _ud2_f0b)                ; 0b
                            dw  lowword(offset _two_byte_unused)        ; 0c
                            dw  lowword(offset _two_byte_unused)        ; 0d
                            dw  lowword(offset _two_byte_unused)        ; 0e
                            dw  lowword(offset _two_byte_unused)        ; 0f
                            dw  lowword(offset _two_byte_unused)        ; 10
                            dw  lowword(offset _two_byte_unused)        ; 11
                            dw  lowword(offset _two_byte_unused)        ; 12
                            dw  lowword(offset _two_byte_unused)        ; 13
                            dw  lowword(offset _two_byte_unused)        ; 14
                            dw  lowword(offset _two_byte_unused)        ; 15
                            dw  lowword(offset _two_byte_unused)        ; 16
                            dw  lowword(offset _two_byte_unused)        ; 17
                            dw  lowword(offset _two_byte_unused)        ; 18
                            dw  lowword(offset _two_byte_unused)        ; 19
                            dw  lowword(offset _two_byte_unused)        ; 1a
                            dw  lowword(offset _two_byte_unused)        ; 1b
                            dw  lowword(offset _two_byte_unused)        ; 1c
                            dw  lowword(offset _two_byte_unused)        ; 1d
                            dw  lowword(offset _two_byte_unused)        ; 1e
                            dw  lowword(offset _two_byte_unused)        ; 1f
                            dw  lowword(offset _mov_gp_control)         ; 20
                            dw  lowword(offset _mov_gp_debug)           ; 21
                            dw  lowword(offset _mov_gp_control)         ; 22
                            dw  lowword(offset _mov_gp_debug)           ; 23
                            dw  lowword(offset _mov_gp_test)            ; 24
                            dw  lowword(offset _two_byte_unused)        ; 25
                            dw  lowword(offset _mov_gp_test)            ; 26
                            dw  lowword(offset _two_byte_unused)        ; 27
                            dw  lowword(offset _two_byte_unused)        ; 28
                            dw  lowword(offset _two_byte_unused)        ; 29
                            dw  lowword(offset _two_byte_unused)        ; 2a
                            dw  lowword(offset _two_byte_unused)        ; 2b
                            dw  lowword(offset _two_byte_unused)        ; 2c
                            dw  lowword(offset _two_byte_unused)        ; 2d
                            dw  lowword(offset _two_byte_unused)        ; 2e
                            dw  lowword(offset _two_byte_unused)        ; 2f
                            dw  lowword(offset _wrmsr)                  ; 30
                            dw  lowword(offset _rdtsc)                  ; 31
                            dw  lowword(offset _rdmsr)                  ; 32
                            dw  lowword(offset _rdpmc)                  ; 33
                            dw  lowword(offset _two_byte_unused)        ; 34
                            dw  lowword(offset _two_byte_unused)        ; 35
                            dw  lowword(offset _two_byte_unused)        ; 36
                            dw  lowword(offset _two_byte_unused)        ; 37
                            dw  lowword(offset _two_byte_unused)        ; 38
                            dw  lowword(offset _two_byte_unused)        ; 39
                            dw  lowword(offset _two_byte_unused)        ; 3a
                            dw  lowword(offset _two_byte_unused)        ; 3b
                            dw  lowword(offset _two_byte_unused)        ; 3c
                            dw  lowword(offset _two_byte_unused)        ; 3d
                            dw  lowword(offset _two_byte_unused)        ; 3e
                            dw  lowword(offset _two_byte_unused)        ; 3f
                            dw  lowword(offset _cmovo)                  ; 40
                            dw  lowword(offset _cmovno)                 ; 41
                            dw  lowword(offset _cmovc)                  ; 42
                            dw  lowword(offset _cmovnc)                 ; 43
                            dw  lowword(offset _cmovz)                  ; 44
                            dw  lowword(offset _cmovnz)                 ; 45
                            dw  lowword(offset _cmovna)                 ; 46
                            dw  lowword(offset _cmova)                  ; 47
                            dw  lowword(offset _cmovs)                  ; 48
                            dw  lowword(offset _cmovns)                 ; 49
                            dw  lowword(offset _cmovpe)                 ; 4a
                            dw  lowword(offset _cmovpo)                 ; 4b
                            dw  lowword(offset _cmovl)                  ; 4c
                            dw  lowword(offset _cmovnl)                 ; 4d
                            dw  lowword(offset _cmovng)                 ; 4e
                            dw  lowword(offset _cmovg)                  ; 4f
                            dw  lowword(offset _two_byte_unused)        ; 50
                            dw  lowword(offset _two_byte_unused)        ; 51
                            dw  lowword(offset _two_byte_unused)        ; 52
                            dw  lowword(offset _two_byte_unused)        ; 53
                            dw  lowword(offset _two_byte_unused)        ; 54
                            dw  lowword(offset _two_byte_unused)        ; 55
                            dw  lowword(offset _two_byte_unused)        ; 56
                            dw  lowword(offset _two_byte_unused)        ; 57
                            dw  lowword(offset _two_byte_unused)        ; 58
                            dw  lowword(offset _two_byte_unused)        ; 59
                            dw  lowword(offset _two_byte_unused)        ; 5a
                            dw  lowword(offset _two_byte_unused)        ; 5b
                            dw  lowword(offset _two_byte_unused)        ; 5c
                            dw  lowword(offset _two_byte_unused)        ; 5d
                            dw  lowword(offset _two_byte_unused)        ; 5e
                            dw  lowword(offset _two_byte_unused)        ; 5f
                            dw  lowword(offset _punpcklbw)              ; 60
                            dw  lowword(offset _punpcklwd)              ; 61
                            dw  lowword(offset _punpckldq)              ; 62
                            dw  lowword(offset _packsswb)               ; 63
                            dw  lowword(offset _pcmpgtb)                ; 64
                            dw  lowword(offset _pcmpgtw)                ; 65
                            dw  lowword(offset _pcmpgtd)                ; 66
                            dw  lowword(offset _packuswb)               ; 67
                            dw  lowword(offset _punpckhbw)              ; 68
                            dw  lowword(offset _punpckhwd)              ; 69
                            dw  lowword(offset _punpckhdq)              ; 6a
                            dw  lowword(offset _packssdw)               ; 6b
                            dw  lowword(offset _two_byte_unused)        ; 6c
                            dw  lowword(offset _two_byte_unused)        ; 6d
                            dw  lowword(offset _movd_mmx_gp)            ; 6e
                            dw  lowword(offset _movq_mmx_mm_mmx)        ; 6f
                            dw  lowword(offset _two_byte_unused)        ; 70
                            dw  lowword(offset _check_reg_0f71)         ; 71
                            dw  lowword(offset _check_reg_0f72)         ; 72
                            dw  lowword(offset _two_byte_unused)        ; 73
                            dw  lowword(offset _pcmpeqb)                ; 74
                            dw  lowword(offset _pcmpeqw)                ; 75
                            dw  lowword(offset _pcmpeqd)                ; 76
                            dw  lowword(offset _emms)                   ; 77
                            dw  lowword(offset _two_byte_unused)        ; 78
                            dw  lowword(offset _two_byte_unused)        ; 79
                            dw  lowword(offset _two_byte_unused)        ; 7a
                            dw  lowword(offset _two_byte_unused)        ; 7b
                            dw  lowword(offset _two_byte_unused)        ; 7c
                            dw  lowword(offset _two_byte_unused)        ; 7d
                            dw  lowword(offset _movd_gp_mmx)            ; 7e
                            dw  lowword(offset _movq_mm_mmx_mmx)        ; 7f
                            dw  lowword(offset _jo_l)                   ; 80
                            dw  lowword(offset _jno_l)                  ; 81
                            dw  lowword(offset _jc_l)                   ; 82
                            dw  lowword(offset _jnc_l)                  ; 83
                            dw  lowword(offset _jz_l)                   ; 84
                            dw  lowword(offset _jnz_l)                  ; 85
                            dw  lowword(offset _jna_l)                  ; 86
                            dw  lowword(offset _ja_l)                   ; 87
                            dw  lowword(offset _js_l)                   ; 88
                            dw  lowword(offset _jns_l)                  ; 89
                            dw  lowword(offset _jpe_l)                  ; 8a
                            dw  lowword(offset _jpo_l)                  ; 8b
                            dw  lowword(offset _jl_l)                   ; 8c
                            dw  lowword(offset _jnl_l)                  ; 8d
                            dw  lowword(offset _jng_l)                  ; 8e
                            dw  lowword(offset _jg_l)                   ; 8f
                            dw  lowword(offset _seto)                   ; 90
                            dw  lowword(offset _setno)                  ; 91
                            dw  lowword(offset _setc)                   ; 92
                            dw  lowword(offset _setnc)                  ; 93
                            dw  lowword(offset _setz)                   ; 94
                            dw  lowword(offset _setnz)                  ; 95
                            dw  lowword(offset _setna)                  ; 96
                            dw  lowword(offset _seta)                   ; 97
                            dw  lowword(offset _sets)                   ; 98
                            dw  lowword(offset _setns)                  ; 99
                            dw  lowword(offset _setpe)                  ; 9a
                            dw  lowword(offset _setpo)                  ; 9b
                            dw  lowword(offset _setl)                   ; 9c
                            dw  lowword(offset _setnl)                  ; 9d
                            dw  lowword(offset _setng)                  ; 9e
                            dw  lowword(offset _setg)                   ; 9f
                            dw  lowword(offset _push_fs)                ; a0
                            dw  lowword(offset _pop_fs)                 ; a1
                            dw  lowword(offset _cpuid)                  ; a2
                            dw  lowword(offset _bt)                     ; a3
                            dw  lowword(offset _shld_immed)             ; a4
                            dw  lowword(offset _shld_cl)                ; a5
                            dw  lowword(offset _two_byte_unused)        ; a6
                            dw  lowword(offset _two_byte_unused)        ; a7
                            dw  lowword(offset _push_gs)                ; a8
                            dw  lowword(offset _pop_gs)                 ; a9
                            dw  lowword(offset _rsm)                    ; aa
                            dw  lowword(offset _bts)                    ; ab
                            dw  lowword(offset _shrd_immed)             ; ac
                            dw  lowword(offset _shrd_cl)                ; ad
                            dw  lowword(offset _two_byte_unused)        ; ae
                            dw  lowword(offset _imul_2_params)          ; af
                            dw  lowword(offset _cmpxchg_byte)           ; b0
                            dw  lowword(offset _cmpxchg)                ; b1
                            dw  lowword(offset _lss)                    ; b2
                            dw  lowword(offset _btr)                    ; b3
                            dw  lowword(offset _lfs)                    ; b4
                            dw  lowword(offset _lgs)                    ; b5
                            dw  lowword(offset _movzx_byte)             ; b6
                            dw  lowword(offset _movzx_word)             ; b7
                            dw  lowword(offset _two_byte_unused)        ; b8
                            dw  lowword(offset _ud2_fb9)                ; b9
                            dw  lowword(offset _check_reg_0fba)         ; ba
                            dw  lowword(offset _btc)                    ; bb
                            dw  lowword(offset _bsf)                    ; bc
                            dw  lowword(offset _bsr)                    ; bd
                            dw  lowword(offset _movsx_byte)             ; be
                            dw  lowword(offset _movsx_word)             ; bf
                            dw  lowword(offset _xadd_byte)              ; c0
                            dw  lowword(offset _xadd)                   ; c1
                            dw  lowword(offset _two_byte_unused)        ; c2
                            dw  lowword(offset _two_byte_unused)        ; c3
                            dw  lowword(offset _two_byte_unused)        ; c4
                            dw  lowword(offset _two_byte_unused)        ; c5
                            dw  lowword(offset _two_byte_unused)        ; c6
                            dw  lowword(offset _check_reg_0fc7)         ; c7
                            dw  lowword(offset _bswap_eax)              ; c8
                            dw  lowword(offset _bswap_ecx)              ; c9
                            dw  lowword(offset _bswap_edx)              ; ca
                            dw  lowword(offset _bswap_ebx)              ; cb
                            dw  lowword(offset _bswap_esp)              ; cc
                            dw  lowword(offset _bswap_ebp)              ; cd
                            dw  lowword(offset _bswap_esi)              ; ce
                            dw  lowword(offset _bswap_edi)              ; cf
                            dw  lowword(offset _two_byte_unused)        ; d0
                            dw  lowword(offset _psrlw)                  ; d1
                            dw  lowword(offset _psrld)                  ; d2
                            dw  lowword(offset _psrlq)                  ; d3
                            dw  lowword(offset _two_byte_unused)        ; d4
                            dw  lowword(offset _pmullw)                 ; d5
                            dw  lowword(offset _two_byte_unused)        ; d6
                            dw  lowword(offset _two_byte_unused)        ; d7
                            dw  lowword(offset _psubusb)                ; d8
                            dw  lowword(offset _psubusw)                ; d9
                            dw  lowword(offset _two_byte_unused)        ; da
                            dw  lowword(offset _pand)                   ; db
                            dw  lowword(offset _paddusb)                ; dc
                            dw  lowword(offset _paddusw)                ; dd
                            dw  lowword(offset _two_byte_unused)        ; de
                            dw  lowword(offset _pandn)                  ; df
                            dw  lowword(offset _two_byte_unused)        ; e0
                            dw  lowword(offset _psraw)                  ; e1
                            dw  lowword(offset _psrad)                  ; e2
                            dw  lowword(offset _two_byte_unused)        ; e3
                            dw  lowword(offset _pmulhw)                 ; e4
                            dw  lowword(offset _two_byte_unused)        ; e5
                            dw  lowword(offset _two_byte_unused)        ; e6
                            dw  lowword(offset _two_byte_unused)        ; e7
                            dw  lowword(offset _psubsb)                 ; e8
                            dw  lowword(offset _psubsw)                 ; e9
                            dw  lowword(offset _two_byte_unused)        ; ea
                            dw  lowword(offset _por)                    ; eb
                            dw  lowword(offset _paddsb)                 ; ec
                            dw  lowword(offset _paddsw)                 ; ed
                            dw  lowword(offset _two_byte_unused)        ; ee
                            dw  lowword(offset _pxor)                   ; ef
                            dw  lowword(offset _two_byte_unused)        ; f0
                            dw  lowword(offset _psllw)                  ; f1
                            dw  lowword(offset _pslld)                  ; f2
                            dw  lowword(offset _psllq)                  ; f3
                            dw  lowword(offset _two_byte_unused)        ; f4
                            dw  lowword(offset _pmaddwd)                ; f5
                            dw  lowword(offset _two_byte_unused)        ; f6
                            dw  lowword(offset _two_byte_unused)        ; f7
                            dw  lowword(offset _psubb)                  ; f8
                            dw  lowword(offset _psubw)                  ; f9
                            dw  lowword(offset _psubd)                  ; fa
                            dw  lowword(offset _two_byte_unused)        ; fb
                            dw  lowword(offset _paddb)                  ; fc
                            dw  lowword(offset _paddw)                  ; fd
                            dw  lowword(offset _paddd)                  ; fe
                            dw  lowword(offset _two_byte_unused)        ; ff

;; Miscellaneous text
    sx_to_word_text         db  "  {as_16_bits}",0
    sx_to_dword_text        db  "  {as_32_bits}",0

;; CPU instructions
    int3_phrase             db  "int3"
    aaa_text                db  "aaa"
    xadd_text               db  "x"
    add_text                db  "add"
    aas_text                db  "aas"
    cbw_text                db  "cbw"
  cwde_text:
    cwd_text                db  "cwd"
                            db  "e"
    cdq_text                db  "cdq"
    clc_text                db  "clc"
    cld_text                db  "cld"
    cli_text                db  "cli"
    cmc_text                db  "cmc"
    daa_text                db  "daa"
    das_text                db  "das"
    hlt_text                db  "hlt"
    into_text               db  "into"
  iretd_text:
    iret_text               db  "iret"
                            db  "d"
    lahf_text               db  "lahf"
    leave_text              db  "leave"
    lock_text               db  "lock"
    nop_text                db  "nop"
  popad_text:
    popa_text               db  "popa"
                            db  "d"
  popfd_text:
    popf_text               db  "popf"
                            db  "d"
  pushad_text:
    pusha_text              db  "pusha"
                            db  "d"
  pushfd_text:
    pushf_text              db  "pushf"
                            db  "d"
    ret_text                db  "ret"
    retf_text               db  "retf"
    sahf_text               db  "sahf"
    stc_text                db  "stc"
    std_text                db  "std"
    sti_text                db  "sti"
    wait_text               db  "wait"
    xlat_text               db  "xlat"
    aad_text                db  "aad"
    aam_text                db  "aam"
    clts_text               db  "clts"
    wbinvd_text             db  "wb"
    invd_text               db  "invd"
    arpl_text               db  "arpl"
    bound_text              db  "bound"
    bswap_text              db  "bswap"
  call_far_text:
    call_text               db  "call"
                            db  "f"
  cmpxchg8b_text:
    cmpxchg_text            db  "cmpxchg"
                            db  "8b"
    enter_text              db  "enter"
    int_text                db  "int"
    ja_text                 db  "ja"
    jc_text                 db  "jc"
    jcxz_text               db  "jcxz"
    jecxz_text              db  "jecxz"
    jg_text                 db  "jg"
    jl_text                 db  "jl"
    jna_text                db  "jna"
    jnc_text                db  "jnc"
    jng_text                db  "jng"
    jnl_text                db  "jnl"
    jno_text                db  "jno"
    jns_text                db  "jns"
    jnz_text                db  "jnz"
    jo_text                 db  "jo"
    jpe_text                db  "jpe"
    jpo_text                db  "jpo"
    js_text                 db  "js"
    jz_text                 db  "jz"
    cmovo_text              db  "cmovo"
    cmovno_text             db  "cmovno"
    cmovc_text              db  "cmovc"
    cmovnc_text             db  "cmovnc"
    cmovz_text              db  "cmovz"
    cmovnz_text             db  "cmovnz"
    cmovna_text             db  "cmovna"
    cmova_text              db  "cmova"
    cmovs_text              db  "cmovs"
    cmovns_text             db  "cmovns"
    cmovpe_text             db  "cmovpe"
    cmovpo_text             db  "cmovpo"
    cmovl_text              db  "cmovl"
    cmovnl_text             db  "cmovnl"
    cmovng_text             db  "cmovng"
    cmovg_text              db  "cmovg"
    seto_text               db  "seto"
    setno_text              db  "setno"
    setc_text               db  "setc"
    setnc_text              db  "setnc"
    setz_text               db  "setz"
    setnz_text              db  "setnz"
    setna_text              db  "setna"
    seta_text               db  "seta"
    sets_text               db  "sets"
    setns_text              db  "setns"
    setpe_text              db  "setpe"
    setpo_text              db  "setpo"
    setl_text               db  "setl"
    setnl_text              db  "setnl"
    setng_text              db  "setng"
    setg_text               db  "setg"

  jmp_far_text:
    jmp_text                db  "jmp"
                            db  "f"
    movd_text               db  "movd"
    movq_text               db  "movq"
  movsx_text:
    mov_text                db  "mov"
                            db  "sx"
    movzx_text              db  "movzx"
    lds_text                db  "lds"
    les_text                db  "les"
    lea_text                db  "lea"
  loopne_text:
    loop_text               db  "loop"
                            db  "ne"
  looped_text:
    loope_text              db  "loope"
    pop_text                db  "pop"
  pushd_text:
    push_text               db  "push"
                            db  "d"
  repne_text:
    rep_text                db  "rep"
                            db  "ne"
    movsb_text              db  "movsb"
    movsw_text              db  "movsw"
    movsd_text              db  "movsd"
    stosb_text              db  "stosb"
    stosw_text              db  "stosw"
    stosd_text              db  "stosd"
    lodsb_text              db  "lodsb"
    lodsw_text              db  "lodsw"
    lodsd_text              db  "lodsd"
    insb_text               db  "insb"
    insw_text               db  "insw"
    insd_text               db  "insd"
    outsb_text              db  "outsb"
    outsw_text              db  "outsw"
    outsd_text              db  "outsd"
    cmpsb_text              db  "cmpsb"
    cmpsw_text              db  "cmpsw"
    cmpsd_text              db  "cmpsd"
    scasb_text              db  "scasb"
    scasw_text              db  "scasw"
    scasd_text              db  "scasd"
    setccc_text             db  "setccc"
    bsf_text                db  "bsf"
    bsr_text                db  "bsr"
  btc_text:
    bt_text                 db  "bt"
                            db  "c"
    bts_text                db  "bts"
    btr_text                db  "btr"
    invlpg_text             db  "invlpg"
    lar_text                db  "lar"
    lfs_text                db  "lfs"
    lgs_text                db  "lgs"
    lss_text                db  "lss"
    lgdt_text               db  "lgdt"
    lidt_text               db  "lidt"
    lldt_text               db  "lldt"
    lmsw_text               db  "lmsw"
    lsl_text                db  "lsl"
    ltr_text                db  "ltr"
    sldt_text               db  "sldt"
    str_text                db  "str"
    verr_text               db  "verr"
    verw_text               db  "verw"
    sgdt_text               db  "sgdt"
    sidt_text               db  "sidt"
    smsw_text               db  "smsw"
  shld_text:
    shl_text                db  "shl"
                            db  "d"
    sal_text                db  "sal"
  shrd_text:
    shr_text                db  "shr"
                            db  "d"
    sar_text                db  "sar"
    imul_text               db  "i"
    mul_text                db  "mul"
    test_text               db  "test"
    not_text                db  "not"
    neg_text                db  "neg"
    idiv_text               db  "i"
    div_text                db  "div"
  inc_text:
    in_text                 db  "in"
                            db  "c"
    dec_text                db  "dec"
    rol_text                db  "rol"
    rcl_text                db  "rcl"
    ror_text                db  "ror"
    rcr_text                db  "rcr"
    xchg_text               db  "xchg"
    or_text                 db  "or"
    adc_text                db  "adc"
    xxx_text                db  "??? "
    and_text                db  "and"
    xor_text                db  "xor"
    cmp_text                db  "cmp"

;; Newer instructions
    cpuid_text              db  "cpuid"
    rdmsr_text              db  "rdmsr"
    rdpmc_text              db  "rdpmc"
    rdtsc_text              db  "rdtsc"
    rsm_text                db  "rsm"
    ud2_0f0b_text           db  "ud2_0f0b"
    ud2_0fb9_text           db  "ud2_0fb9"
    wrmsr_text              db  "wrmsr"

;; FPU instructions
    fcmovb_text             db  "fcmovb"
    fcmovz_text             db  "fcmovz"
    fcmovng_text            db  "fcmovng"
    fcmovpo_text            db  "fcmovpo"
    fcmovnb_text            db  "fcmovnb"
    fcmovnz_text            db  "fcmovnz"
    fcmovg_text             db  "fcmovg"
    fcmovpe_text            db  "fcmovpe"
  fcomi_text:
    fcomip_text             db  "fcomip"
  fucomi_text:
    fucomip_text            db  "fucomip"
    fpu_text                db  "fpu"
  faddp_text:
    fadd_text               db  "fadd"
                            db  "p"
  fmulp_text:
    fmul_text               db  "fmul"
                            db  "p"
  fcompp_text:
  fcomp_text:
    fcom_text               db  "fcom"
                            db  "p"
                            db  "p"
  fsubrp_text:
  fsubr_text:
    fsub_text               db  "fsub"
                            db  "r"
                            db  "p"
    fsubp_text              db  "fsubp"
  fdivr_text:
    fdiv_text               db  "fdiv"
                            db  "r"
    fdivp_text              db  "fdivp"
    fdivrp_text             db  "fdivrp"
  fldcw_text:
    fld_text                db  "fld"
                            db  "cw"
  fstp_text:
    fst_text                db  "fst"
                            db  "p"
    fxch_text               db  "fxch"
    fnop_text               db  "fnop"
    fchs_text               db  "fchs"
    fabs_text               db  "fabs"
    ftst_text               db  "ftst"
    fxam_text               db  "fxam"
    fld1_text               db  "fld1"
    fldl2t_text             db  "fldl2t"
    fldl2e_text             db  "fldl2e"
    fldpi_text              db  "fldpi"
    fldlg2_text             db  "fldlg2"
    fldln2_text             db  "fldln2"
    fldz_text               db  "fldz"
    f2xm1_text              db  "f2xm1"
    fyl2x_text              db  "fyl2x"
    fptan_text              db  "fptan"
    fpatan_text             db  "fpatan"
    fxtract_text            db  "fxtract"
  fprem_text:
    fprem1_text             db  "fprem1"
    fdecstp_text            db  "fdecstp"
    fincstp_text            db  "fincstp"
    fyl2xp1_text            db  "fyl2xp1"
    fsqrt_text              db  "fsqrt"
    fsincos_text            db  "fsincos"
    frndint_text            db  "frndint"
    fscale_text             db  "fscale"
    fsin_text               db  "fsin"
    fcos_text               db  "fcos"
    fldenv_text             db  "fldenv"
    fnstenv_text            db  "fnstenv"
    fnstcw_text             db  "fnstcw"
  fucom_text:
  fucomp_text:
    fucompp_text            db  "fucompp"
    fiadd_text              db  "fiadd"
    fimul_text              db  "fimul"
  ficomp_text:
    ficom_text              db  "ficom"
                            db  "p"
  fisubr_text:
    fisub_text              db  "fisub"
                            db  "r"
  fidivr_text:
    fidiv_text              db  "fidiv"
                            db  "r"
    fnclex_text             db  "fnclex"
    fninit_text             db  "fninit"
    fild_text               db  "fild"
  fistp_text:
    fist_text               db  "fist"
                            db  "p"
    ffree_text              db  "ffree"
    frstor_text             db  "frstor"
    fnstsw_text             db  "fnstsw"
    fbld_text               db  "fbld"
    fbstp_text              db  "fbstp"
    fnsave_text             db  "fnsave"

;; MMX and SSE/SSE2 instructions
    emms_text               db  "emms"
    packssdw_text           db  "packssdw"
    packsswb_text           db  "packsswb"
    packuswb_text           db  "packuswb"
    paddb_text              db  "paddb"
    paddsb_text             db  "paddsb"
    paddsw_text             db  "paddsw"
    paddusb_text            db  "paddusb"
    paddusw_text            db  "paddusw"
    paddw_text              db  "paddw"
    paddd_text              db  "paddd"
    pand_text               db  "pand"
    pandn_text              db  "pandn"
    pcmpeqb_text            db  "pcmpeqb"
    pcmpeqd_text            db  "pcmpeqd"
    pcmpeqw_text            db  "pcmpeqw"
    pcmpgtb_text            db  "pcmpgtb"
    pcmpgtd_text            db  "pcmpgtd"
    pcmpgtw_text            db  "pcmpgtw"
    pmaddwd_text            db  "pmaddwd"
    pmulhw_text             db  "pmulhw"
    pmullw_text             db  "pmullw"
    por_text                db  "por"
    pslld_text              db  "pslld"
    psllq_text              db  "psllq"
    psllw_text              db  "psllw"
    psrad_text              db  "psrad"
    psraw_text              db  "psraw"
    psrld_text              db  "psrld"
    psrlq_text              db  "psrlq"
    psrlw_text              db  "psrlw"
    psubb_text              db  "psubb"
    psubd_text              db  "psubd"
    psubsb_text             db  "psubsb"
    psubsw_text             db  "psubsw"
    psubusb_text            db  "psubusb"
    psubusw_text            db  "psubusw"
    psubw_text              db  "psubw"
    punpckhbw_text          db  "punpckhbw"
    punpckhwd_text          db  "punpckhwd"
    punpckhdq_text          db  "punpckhdq"
    punpcklbw_text          db  "punpcklbw"
    punpcklwd_text          db  "punpcklwd"
    punpckldq_text          db  "punpckldq"
    pxor_text               db  "pxor"

    null_text               db  0
    bytes_94_108_text       db  "{94 or 108 bytes}",0
  dword_text                db  "d"
    word_text               db  "word",0
    qword_text              db  "qword",0
    real4_text              db  "real32",0
    real8_text              db  "real64",0
    real10_text             db  "real80",0
    st0_comma_sti_text      db  "st0,sti",0
    sti_comma_st0_text      db  "sti,st0",0

    fpu_unknown_opcode      db  "fpu opcode xx xx"
    unknown_opcode          db  "opcode xx"
  illegal_register:
    unknown_text            db  "???",0

    temp_buffer             db  100 dup(0)
    temp_buffer2            db  100 dup(0)
