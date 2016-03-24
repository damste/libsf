//////////
//
// /libsf/exodus/tools/debi/debi_globals.h
//
//////
// Version 0.80
// Copyright (c) 2014-2015 by Rick C. Hodgin
//////
// Last update:
//     Sep.12.2015
//////
// Change log:
//     Sep.12.2015 - Refactoring for Exodus OS tool support
//     Feb.13.2014 - Initial creation
//////
//
// This software is released as Liberty Software under a Repeat License, as governed
// by the Public Benefit License v1.0 or later (PBL).
//
// You are free to use, copy, modify and share this software.  However, it can only
// be released under the PBL version indicated, and every project must include a copy
// of the pbl.txt document for its version as is at http://www.libsf.org/licenses/.
//
// For additional information about this project, or to view the license, see:
//
//     http://www.libsf.org/
//     http://www.libsf.org/licenses/
//     http://www.visual-freepro.org/vjr/indexmain.html
//     http://www.visual-freepro.org/wiki/index.php/PBL
//     http://www.visual-freepro.org/wiki/index.php/Repeat_License
//
// Thank you.  And may The Lord bless you richly as you lift up your life, your
// talents, your gifts, your praise, unto Him.  In Jesus' name I pray.  Amen.
//
//




//////////
// Shared assembly codes used by lasm
//////
	#include "../common/debi_globals.h"


//////////
// Buffers used during instruction decoding
//////
	u8 	operand1_buffer			[32];
	u8 	operand2_buffer			[32];
	u8 	operand3_buffer			[32];
	u8 	immediate_buffer		[32];
	u8 	sib_buffer				[32];
	u8 	sib2_buffer				[32];
	u8 	comment_buffer			[256];					// General comment about the instruction
	u8 	line_comment_buffer		[256];			// Comment appearing on the same assembly line
	u8 	prefix_op_buffer		[256];
	u8 	prefix_op1_buffer		[256];
	u8 	prefix_op2_buffer		[256];
	u8 	misc_buffer				[256];


//////////
// Opcode map into to handler functions
//////
#ifdef _DEBI_COMPILE
	DISASM_FUNC first_byte_functions[] =
	{
		(DISASM_FUNC)&opcode_add00,					/* 00 */
		(DISASM_FUNC)&opcode_add01,                 /* 01 */
		(DISASM_FUNC)&opcode_add02,                 /* 02 */
		(DISASM_FUNC)&opcode_add03,                 /* 03 */
		(DISASM_FUNC)&opcode_add_rm8_immed8,        /* 04 */
		(DISASM_FUNC)&opcode_add_rm16_32_immed16_32,/* 05 */
		(DISASM_FUNC)&opcode_push_es,               /* 06 */
		(DISASM_FUNC)&opcode_pop_es,                /* 07 */
		(DISASM_FUNC)&opcode_or_rm08,               /* 08 */
		(DISASM_FUNC)&opcode_or_rm09,               /* 09 */
		(DISASM_FUNC)&opcode_or_rm0a,               /* 0a */
		(DISASM_FUNC)&opcode_or_rm0b,               /* 0b */
		(DISASM_FUNC)&opcode_or_accum0c,            /* 0c */
		(DISASM_FUNC)&opcode_or_accum0d,            /* 0d */
		(DISASM_FUNC)&opcode_push_cs,               /* 0e */
		(DISASM_FUNC)&opcode_two_byte_instruction,  /* 0f */
		(DISASM_FUNC)&opcode_adc10,                 /* 10 */
		(DISASM_FUNC)&opcode_adc11,                 /* 11 */
		(DISASM_FUNC)&opcode_adc12,                 /* 12 */
		(DISASM_FUNC)&opcode_adc13,                 /* 13 */
		(DISASM_FUNC)&opcode_adc_rm8_immed8,        /* 14 */
		(DISASM_FUNC)&opcode_adc_rm16_32_immed16_32,/* 15 */
		(DISASM_FUNC)&opcode_push_ss,               /* 16 */
		(DISASM_FUNC)&opcode_pop_ss,                /* 17 */
		(DISASM_FUNC)&opcode_sbb18,                 /* 18 */
		(DISASM_FUNC)&opcode_sbb19,                 /* 19 */
		(DISASM_FUNC)&opcode_sbb1a,                 /* 1a */
		(DISASM_FUNC)&opcode_sbb1b,                 /* 1b */
		(DISASM_FUNC)&opcode_sbb_accum_immed8,      /* 1c */
		(DISASM_FUNC)&opcode_sbb_accum_immed16_32,  /* 1d */
		(DISASM_FUNC)&opcode_push_ds,               /* 1e */
		(DISASM_FUNC)&opcode_pop_ds,                /* 1f */
		(DISASM_FUNC)&opcode_and20,                 /* 20 */
		(DISASM_FUNC)&opcode_and21,                 /* 21 */
		(DISASM_FUNC)&opcode_and22,                 /* 22 */
		(DISASM_FUNC)&opcode_and23,                 /* 23 */
		(DISASM_FUNC)&opcode_and_rm8_immed8,        /* 24 */
		(DISASM_FUNC)&opcode_and_rm16_32_immed16_32,/* 25 */
		(DISASM_FUNC)&opcode_es_override,           /* 26 */
		(DISASM_FUNC)&opcode_daa,                   /* 27 */
		(DISASM_FUNC)&opcode_sub28,                 /* 28 */
		(DISASM_FUNC)&opcode_sub29,                 /* 29 */
		(DISASM_FUNC)&opcode_sub2a,                 /* 2a */
		(DISASM_FUNC)&opcode_sub2b,                 /* 2b */
		(DISASM_FUNC)&opcode_sub_accum_immed8,      /* 2c */
		(DISASM_FUNC)&opcode_sub_accum_immed16_32,  /* 2d */
		(DISASM_FUNC)&opcode_cs_override,           /* 2e */
		(DISASM_FUNC)&opcode_das,                   /* 2f */
		(DISASM_FUNC)&opcode_xor30,                 /* 30 */
		(DISASM_FUNC)&opcode_xor31,                 /* 31 */
		(DISASM_FUNC)&opcode_xor32,                 /* 32 */
		(DISASM_FUNC)&opcode_xor33,                 /* 33 */
		(DISASM_FUNC)&opcode_xor_accum_immed8,      /* 34 */
		(DISASM_FUNC)&opcode_xor_accum_immed16_32,  /* 35 */
		(DISASM_FUNC)&opcode_ss_override,           /* 36 */
		(DISASM_FUNC)&opcode_aaa,                   /* 37 */
		(DISASM_FUNC)&opcode_cmp38,                 /* 38 */
		(DISASM_FUNC)&opcode_cmp39,                 /* 39 */
		(DISASM_FUNC)&opcode_cmp3a,                 /* 3a */
		(DISASM_FUNC)&opcode_cmp3b,                 /* 3b */
		(DISASM_FUNC)&opcode_cmp3c,                 /* 3c */
		(DISASM_FUNC)&opcode_cmp3d,                 /* 3d */
		(DISASM_FUNC)&opcode_ds_override,           /* 3e */
		(DISASM_FUNC)&opcode_aas,                   /* 3f */
		(DISASM_FUNC)&opcode_inc_xxx,               /* 40 */
		(DISASM_FUNC)&opcode_inc_xxx,               /* 41 */
		(DISASM_FUNC)&opcode_inc_xxx,               /* 42 */
		(DISASM_FUNC)&opcode_inc_xxx,               /* 43 */
		(DISASM_FUNC)&opcode_inc_xxx,               /* 44 */
		(DISASM_FUNC)&opcode_inc_xxx,               /* 45 */
		(DISASM_FUNC)&opcode_inc_xxx,               /* 46 */
		(DISASM_FUNC)&opcode_inc_xxx,               /* 47 */
		(DISASM_FUNC)&opcode_dec_xxx,               /* 48 */
		(DISASM_FUNC)&opcode_dec_xxx,               /* 49 */
		(DISASM_FUNC)&opcode_dec_xxx,               /* 4a */
		(DISASM_FUNC)&opcode_dec_xxx,               /* 4b */
		(DISASM_FUNC)&opcode_dec_xxx,               /* 4c */
		(DISASM_FUNC)&opcode_dec_xxx,               /* 4d */
		(DISASM_FUNC)&opcode_dec_xxx,               /* 4e */
		(DISASM_FUNC)&opcode_dec_xxx,               /* 4f */
		(DISASM_FUNC)&opcode_push_xreg,             /* 50 */
		(DISASM_FUNC)&opcode_push_xreg,             /* 51 */
		(DISASM_FUNC)&opcode_push_xreg,             /* 52 */
		(DISASM_FUNC)&opcode_push_xreg,             /* 53 */
		(DISASM_FUNC)&opcode_push_xreg,             /* 54 */
		(DISASM_FUNC)&opcode_push_xreg,             /* 55 */
		(DISASM_FUNC)&opcode_push_xreg,             /* 56 */
		(DISASM_FUNC)&opcode_push_xreg,             /* 57 */
		(DISASM_FUNC)&opcode_pop_xreg,              /* 58 */
		(DISASM_FUNC)&opcode_pop_xreg,              /* 59 */
		(DISASM_FUNC)&opcode_pop_xreg,              /* 5a */
		(DISASM_FUNC)&opcode_pop_xreg,              /* 5b */
		(DISASM_FUNC)&opcode_pop_xreg,              /* 5c */
		(DISASM_FUNC)&opcode_pop_xreg,              /* 5d */
		(DISASM_FUNC)&opcode_pop_xreg,              /* 5e */
		(DISASM_FUNC)&opcode_pop_xreg,              /* 5f */
		(DISASM_FUNC)&opcode_pusha,                 /* 60 */
		(DISASM_FUNC)&opcode_popa,                  /* 61 */
		(DISASM_FUNC)&opcode_bound,                 /* 62 */
		(DISASM_FUNC)&opcode_arpl,                  /* 63 */
		(DISASM_FUNC)&opcode_fs_override,           /* 64 */
		(DISASM_FUNC)&opcode_gs_override,           /* 65 */
		(DISASM_FUNC)&opcode_op_size_override,      /* 66 */
		(DISASM_FUNC)&opcode_adr_size_override,     /* 67 */
		(DISASM_FUNC)&opcode_push_immed16_32,       /* 68 */
		(DISASM_FUNC)&opcode_imul_3_parms_immed16_32,/* 69 */
		(DISASM_FUNC)&opcode_push_immed8,           /* 6a */
		(DISASM_FUNC)&opcode_imul_3_parms_immed8,   /* 6b */
		(DISASM_FUNC)&opcode_insb,                  /* 6c */
		(DISASM_FUNC)&opcode_insw,                  /* 6d */
		(DISASM_FUNC)&opcode_outsb,                 /* 6e */
		(DISASM_FUNC)&opcode_outsw,                 /* 6f */
		(DISASM_FUNC)&opcode_jo,                    /* 70 */
		(DISASM_FUNC)&opcode_jno,                   /* 71 */
		(DISASM_FUNC)&opcode_jc,                    /* 72 */
		(DISASM_FUNC)&opcode_jnc,                   /* 73 */
		(DISASM_FUNC)&opcode_jz,                    /* 74 */
		(DISASM_FUNC)&opcode_jnz,                   /* 75 */
		(DISASM_FUNC)&opcode_jna,                   /* 76 */
		(DISASM_FUNC)&opcode_ja,                    /* 77 */
		(DISASM_FUNC)&opcode_js,                    /* 78 */
		(DISASM_FUNC)&opcode_jns,                   /* 79 */
		(DISASM_FUNC)&opcode_jpe,                   /* 7a */
		(DISASM_FUNC)&opcode_jpo,                   /* 7b */
		(DISASM_FUNC)&opcode_jl,                    /* 7c */
		(DISASM_FUNC)&opcode_jnl,                   /* 7d */
		(DISASM_FUNC)&opcode_jng,                   /* 7e */
		(DISASM_FUNC)&opcode_jg,                    /* 7f */
		(DISASM_FUNC)&opcode_check_reg_80,          /* 80 */
		(DISASM_FUNC)&opcode_check_reg_81,          /* 81 */
		(DISASM_FUNC)&opcode_check_reg_82,          /* 82 */
		(DISASM_FUNC)&opcode_check_reg_83,          /* 83 */
		(DISASM_FUNC)&opcode_test_rm_reg_8,         /* 84 */
		(DISASM_FUNC)&opcode_test_rm_reg16_32,      /* 85 */
		(DISASM_FUNC)&opcode_xchg_byte,             /* 86 */
		(DISASM_FUNC)&opcode_xchg,                  /* 87 */
		(DISASM_FUNC)&opcode_mov_rm_reg_8,          /* 88 */
		(DISASM_FUNC)&opcode_mov_rm_reg_16_32,      /* 89 */
		(DISASM_FUNC)&opcode_mov_reg_rm_8,          /* 8a */
		(DISASM_FUNC)&opcode_mov_reg_rm_16_32,      /* 8b */
		(DISASM_FUNC)&opcode_mov_reg16_32_sreg,     /* 8c */
		(DISASM_FUNC)&opcode_lea,                   /* 8d */
		(DISASM_FUNC)&opcode_mov_sreg_reg16_32,     /* 8e */
		(DISASM_FUNC)&opcode_check_reg_8f,          /* 8f */
		(DISASM_FUNC)&opcode_nop,                   /* 90 */
		(DISASM_FUNC)&opcode_xchg_xxx,              /* 91 */
		(DISASM_FUNC)&opcode_xchg_xxx,              /* 92 */
		(DISASM_FUNC)&opcode_xchg_xxx,              /* 93 */
		(DISASM_FUNC)&opcode_xchg_xxx,              /* 94 */
		(DISASM_FUNC)&opcode_xchg_xxx,              /* 95 */
		(DISASM_FUNC)&opcode_xchg_xxx,              /* 96 */
		(DISASM_FUNC)&opcode_xchg_xxx,              /* 97 */
		(DISASM_FUNC)&opcode_cbw,                   /* 98 */
		(DISASM_FUNC)&opcode_cwd,                   /* 99 */
		(DISASM_FUNC)&opcode_call_far_operand,      /* 9a */
		(DISASM_FUNC)&opcode_wait,                  /* 9b */
		(DISASM_FUNC)&opcode_pushf,                 /* 9c */
		(DISASM_FUNC)&opcode_popf,                  /* 9d */
		(DISASM_FUNC)&opcode_sahf,                  /* 9e */
		(DISASM_FUNC)&opcode_lahf,                  /* 9f */
		(DISASM_FUNC)&opcode_mov_accum_mem_8,       /* a0 */
		(DISASM_FUNC)&opcode_mov_accum_mem_16_32,   /* a1 */
		(DISASM_FUNC)&opcode_mov_mem_accum_8,       /* a2 */
		(DISASM_FUNC)&opcode_mov_mem_accum_16_32,   /* a3 */
		(DISASM_FUNC)&opcode_movsb,                 /* a4 */
		(DISASM_FUNC)&opcode_movsw,                 /* a5 */
		(DISASM_FUNC)&opcode_cmpsb,                 /* a6 */
		(DISASM_FUNC)&opcode_cmpsw,                 /* a7 */
		(DISASM_FUNC)&opcode_test_accum_imm8,       /* a8 */
		(DISASM_FUNC)&opcode_test_accum_imm16_32,   /* a9 */
		(DISASM_FUNC)&opcode_stosb,                 /* aa */
		(DISASM_FUNC)&opcode_stosw,                 /* ab */
		(DISASM_FUNC)&opcode_lodsb,                 /* ac */
		(DISASM_FUNC)&opcode_lodsw,                 /* ad */
		(DISASM_FUNC)&opcode_scasb,                 /* ae */
		(DISASM_FUNC)&opcode_scasw,                 /* af */
		(DISASM_FUNC)&opcode_mov_reg_immed8,        /* b0 */
		(DISASM_FUNC)&opcode_mov_reg_immed8,        /* b1 */
		(DISASM_FUNC)&opcode_mov_reg_immed8,        /* b2 */
		(DISASM_FUNC)&opcode_mov_reg_immed8,        /* b3 */
		(DISASM_FUNC)&opcode_mov_reg_immed8,        /* b4 */
		(DISASM_FUNC)&opcode_mov_reg_immed8,        /* b5 */
		(DISASM_FUNC)&opcode_mov_reg_immed8,        /* b6 */
		(DISASM_FUNC)&opcode_mov_reg_immed8,        /* b7 */
		(DISASM_FUNC)&opcode_mov_reg_immed16_32,    /* b8 */
		(DISASM_FUNC)&opcode_mov_reg_immed16_32,    /* b9 */
		(DISASM_FUNC)&opcode_mov_reg_immed16_32,    /* ba */
		(DISASM_FUNC)&opcode_mov_reg_immed16_32,    /* bb */
		(DISASM_FUNC)&opcode_mov_reg_immed16_32,    /* bc */
		(DISASM_FUNC)&opcode_mov_reg_immed16_32,    /* bd */
		(DISASM_FUNC)&opcode_mov_reg_immed16_32,    /* be */
		(DISASM_FUNC)&opcode_mov_reg_immed16_32,    /* bf */
		(DISASM_FUNC)&opcode_check_reg_c0,          /* c0 */
		(DISASM_FUNC)&opcode_check_reg_c1,          /* c1 */
		(DISASM_FUNC)&opcode_retn_immed,            /* c2 */
		(DISASM_FUNC)&opcode_retn,                  /* c3 */
		(DISASM_FUNC)&opcode_les,                   /* c4 */
		(DISASM_FUNC)&opcode_lds,                   /* c5 */
		(DISASM_FUNC)&opcode_check_reg_c6,          /* c6 */
		(DISASM_FUNC)&opcode_check_reg_c7,          /* c7 */
		(DISASM_FUNC)&opcode_enter,                 /* c8 */
		(DISASM_FUNC)&opcode_leave,                 /* c9 */
		(DISASM_FUNC)&opcode_retf_immed,            /* ca */
		(DISASM_FUNC)&opcode_retf,                  /* cb */
		(DISASM_FUNC)&opcode_int3,                  /* cc */
		(DISASM_FUNC)&opcode_intx,                  /* cd */
		(DISASM_FUNC)&opcode_into,                  /* ce */
		(DISASM_FUNC)&opcode_iret,                  /* cf */
		(DISASM_FUNC)&opcode_check_reg_d0,          /* d0 */
		(DISASM_FUNC)&opcode_check_reg_d1,          /* d1 */
		(DISASM_FUNC)&opcode_check_reg_d2,          /* d2 */
		(DISASM_FUNC)&opcode_check_reg_d3,          /* d3 */
		(DISASM_FUNC)&opcode_aam,                   /* d4 */
		(DISASM_FUNC)&opcode_aad,                   /* d5 */
		(DISASM_FUNC)&opcode_unused,                /* d6 */
		(DISASM_FUNC)&opcode_xlat,                  /* d7 */
		(DISASM_FUNC)&opcode_fpu_d8,                /* d8 */
		(DISASM_FUNC)&opcode_fpu_d9,                /* d9 */
		(DISASM_FUNC)&opcode_fpu_da,                /* da */
		(DISASM_FUNC)&opcode_fpu_db,                /* db */
		(DISASM_FUNC)&opcode_fpu_dc,                /* dc */
		(DISASM_FUNC)&opcode_fpu_dd,                /* dd */
		(DISASM_FUNC)&opcode_fpu_de,                /* de */
		(DISASM_FUNC)&opcode_fpu_df,                /* df */
		(DISASM_FUNC)&opcode_loopne,                /* e0 */
		(DISASM_FUNC)&opcode_loope,                 /* e1 */
		(DISASM_FUNC)&opcode_loop,                  /* e2 */
		(DISASM_FUNC)&opcode_jcxz,                  /* e3 */
		(DISASM_FUNC)&opcode_in8_immed8,            /* e4 */
		(DISASM_FUNC)&opcode_in16_32_immed8,        /* e5 */
		(DISASM_FUNC)&opcode_oute6,                 /* e6 */
		(DISASM_FUNC)&opcode_oute7,                 /* e7 */
		(DISASM_FUNC)&opcode_call_near_relative,    /* e8 */
		(DISASM_FUNC)&opcode_jmp16_32,              /* e9 */
		(DISASM_FUNC)&opcode_jmp_far,               /* ea */
		(DISASM_FUNC)&opcode_jmp8,                  /* eb */
		(DISASM_FUNC)&opcode_in_byte,               /* ec */
		(DISASM_FUNC)&opcode_in,                    /* ed */
		(DISASM_FUNC)&opcode_outee,                 /* ee */
		(DISASM_FUNC)&opcode_outef,                 /* ef */
		(DISASM_FUNC)&opcode_lock_prefix,           /* f0 */
		(DISASM_FUNC)&opcode_icebp,                 /* f1 */
		(DISASM_FUNC)&opcode_repne_prefix,          /* f2 */
		(DISASM_FUNC)&opcode_repe_prefix,           /* f3 */
		(DISASM_FUNC)&opcode_hlt,                   /* f4 */
		(DISASM_FUNC)&opcode_cmc,                   /* f5 */
		(DISASM_FUNC)&opcode_check_reg_f6,          /* f6 */
		(DISASM_FUNC)&opcode_check_reg_f7,          /* f7 */
		(DISASM_FUNC)&opcode_clc,                   /* f8 */
		(DISASM_FUNC)&opcode_stc,                   /* f9 */
		(DISASM_FUNC)&opcode_cli,                   /* fa */
		(DISASM_FUNC)&opcode_sti,                   /* fb */
		(DISASM_FUNC)&opcode_cld,                   /* fc */
		(DISASM_FUNC)&opcode_std,                   /* fd */
		(DISASM_FUNC)&opcode_check_reg_fe,          /* fe */
		(DISASM_FUNC)&opcode_check_reg_ff           /* ff */
	};


	DISASM_FUNC second_byte_functions[] =
	{
		(DISASM_FUNC)&opcode_check_reg_0f00,        /* 00 */
		(DISASM_FUNC)&opcode_check_reg_0f01,        /* 01 */
		(DISASM_FUNC)&opcode_lar,                   /* 02 */
		(DISASM_FUNC)&opcode_lsl,                   /* 03 */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 04 */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 05 */
		(DISASM_FUNC)&opcode_clts,                  /* 06 */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 07 */
		(DISASM_FUNC)&opcode_invd,                  /* 08 */
		(DISASM_FUNC)&opcode_wbinvd,                /* 09 */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 0a */
		(DISASM_FUNC)&opcode_ud2_0f0b,              /* 0b */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 0c */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 0d */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 0e */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 0f */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 10 */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 11 */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 12 */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 13 */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 14 */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 15 */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 16 */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 17 */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 18 */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 19 */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 1a */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 1b */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 1c */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 1d */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 1e */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 1f */
		(DISASM_FUNC)&opcode_mov_gp_control,        /* 20 */
		(DISASM_FUNC)&opcode_mov_gp_debug,          /* 21 */
		(DISASM_FUNC)&opcode_mov_control_gp,        /* 22 */
		(DISASM_FUNC)&opcode_mov_debug_gp,          /* 23 */
		(DISASM_FUNC)&opcode_mov_gp_test,           /* 24 */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 25 */
		(DISASM_FUNC)&opcode_mov_test_gp,           /* 26 */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 27 */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 28 */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 29 */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 2a */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 2b */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 2c */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 2d */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 2e */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 2f */
		(DISASM_FUNC)&opcode_wrmsr,                 /* 30 */
		(DISASM_FUNC)&opcode_rdtsc,                 /* 31 */
		(DISASM_FUNC)&opcode_rdmsr,                 /* 32 */
		(DISASM_FUNC)&opcode_rdpmc,                 /* 33 */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 34 */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 35 */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 36 */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 37 */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 38 */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 39 */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 3a */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 3b */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 3c */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 3d */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 3e */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 3f */
		(DISASM_FUNC)&opcode_cmovo,                 /* 40 */
		(DISASM_FUNC)&opcode_cmovno,                /* 41 */
		(DISASM_FUNC)&opcode_cmovc,                 /* 42 */
		(DISASM_FUNC)&opcode_cmovnc,                /* 43 */
		(DISASM_FUNC)&opcode_cmovz,                 /* 44 */
		(DISASM_FUNC)&opcode_cmovnz,                /* 45 */
		(DISASM_FUNC)&opcode_cmovna,                /* 46 */
		(DISASM_FUNC)&opcode_cmova,                 /* 47 */
		(DISASM_FUNC)&opcode_cmovs,                 /* 48 */
		(DISASM_FUNC)&opcode_cmovns,                /* 49 */
		(DISASM_FUNC)&opcode_cmovpe,                /* 4a */
		(DISASM_FUNC)&opcode_cmovpo,                /* 4b */
		(DISASM_FUNC)&opcode_cmovl,                 /* 4c */
		(DISASM_FUNC)&opcode_cmovnl,                /* 4d */
		(DISASM_FUNC)&opcode_cmovng,                /* 4e */
		(DISASM_FUNC)&opcode_cmovg,                 /* 4f */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 50 */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 51 */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 52 */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 53 */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 54 */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 55 */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 56 */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 57 */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 58 */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 59 */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 5a */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 5b */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 5c */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 5d */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 5e */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 5f */
		(DISASM_FUNC)&opcode_punpcklbw,             /* 60 */
		(DISASM_FUNC)&opcode_punpcklwd,             /* 61 */
		(DISASM_FUNC)&opcode_punpckldq,             /* 62 */
		(DISASM_FUNC)&opcode_packsswb,              /* 63 */
		(DISASM_FUNC)&opcode_pcmpgtb,               /* 64 */
		(DISASM_FUNC)&opcode_pcmpgtw,               /* 65 */
		(DISASM_FUNC)&opcode_pcmpgtd,               /* 66 */
		(DISASM_FUNC)&opcode_packuswb,              /* 67 */
		(DISASM_FUNC)&opcode_punpckhbw,             /* 68 */
		(DISASM_FUNC)&opcode_punpckhwd,             /* 69 */
		(DISASM_FUNC)&opcode_punpckhdq,             /* 6a */
		(DISASM_FUNC)&opcode_packssdw,              /* 6b */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 6c */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 6d */
		(DISASM_FUNC)&opcode_movd_mmx_gp,           /* 6e */
		(DISASM_FUNC)&opcode_movq_mmx_mm_mmx,       /* 6f */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 70 */
		(DISASM_FUNC)&opcode_check_reg_0f71,        /* 71 */
		(DISASM_FUNC)&opcode_check_reg_0f72,        /* 72 */
		(DISASM_FUNC)&opcode_check_reg_0f73,        /* 73 */
		(DISASM_FUNC)&opcode_pcmpeqb,               /* 74 */
		(DISASM_FUNC)&opcode_pcmpeqw,               /* 75 */
		(DISASM_FUNC)&opcode_pcmpeqd,               /* 76 */
		(DISASM_FUNC)&opcode_emms,                  /* 77 */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 78 */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 79 */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 7a */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 7b */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 7c */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* 7d */
		(DISASM_FUNC)&opcode_movd_gp_mmx,           /* 7e */
		(DISASM_FUNC)&opcode_movq_mm_mmx_mmx,       /* 7f */
		(DISASM_FUNC)&opcode_jo_l,                  /* 80 */
		(DISASM_FUNC)&opcode_jno_l,                 /* 81 */
		(DISASM_FUNC)&opcode_jc_l,                  /* 82 */
		(DISASM_FUNC)&opcode_jnc_l,                 /* 83 */
		(DISASM_FUNC)&opcode_jz_l,                  /* 84 */
		(DISASM_FUNC)&opcode_jnz_l,                 /* 85 */
		(DISASM_FUNC)&opcode_jna_l,                 /* 86 */
		(DISASM_FUNC)&opcode_ja_l,                  /* 87 */
		(DISASM_FUNC)&opcode_js_l,                  /* 88 */
		(DISASM_FUNC)&opcode_jns_l,                 /* 89 */
		(DISASM_FUNC)&opcode_jpe_l,                 /* 8a */
		(DISASM_FUNC)&opcode_jpo_l,                 /* 8b */
		(DISASM_FUNC)&opcode_jl_l,                  /* 8c */
		(DISASM_FUNC)&opcode_jnl_l,                 /* 8d */
		(DISASM_FUNC)&opcode_jng_l,                 /* 8e */
		(DISASM_FUNC)&opcode_jg_l,                  /* 8f */
		(DISASM_FUNC)&opcode_seto,                  /* 90 */
		(DISASM_FUNC)&opcode_setno,                 /* 91 */
		(DISASM_FUNC)&opcode_setc,                  /* 92 */
		(DISASM_FUNC)&opcode_setnc,                 /* 93 */
		(DISASM_FUNC)&opcode_setz,                  /* 94 */
		(DISASM_FUNC)&opcode_setnz,                 /* 95 */
		(DISASM_FUNC)&opcode_setna,                 /* 96 */
		(DISASM_FUNC)&opcode_seta,                  /* 97 */
		(DISASM_FUNC)&opcode_sets,                  /* 98 */
		(DISASM_FUNC)&opcode_setns,                 /* 99 */
		(DISASM_FUNC)&opcode_setpe,                 /* 9a */
		(DISASM_FUNC)&opcode_setpo,                 /* 9b */
		(DISASM_FUNC)&opcode_setl,                  /* 9c */
		(DISASM_FUNC)&opcode_setnl,                 /* 9d */
		(DISASM_FUNC)&opcode_setng,                 /* 9e */
		(DISASM_FUNC)&opcode_setg,                  /* 9f */
		(DISASM_FUNC)&opcode_push_fs,               /* a0 */
		(DISASM_FUNC)&opcode_pop_fs,                /* a1 */
		(DISASM_FUNC)&opcode_cpuid,                 /* a2 */
		(DISASM_FUNC)&opcode_bt,                    /* a3 */
		(DISASM_FUNC)&opcode_shld_immed,            /* a4 */
		(DISASM_FUNC)&opcode_shld_cl,               /* a5 */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* a6 */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* a7 */
		(DISASM_FUNC)&opcode_push_gs,               /* a8 */
		(DISASM_FUNC)&opcode_pop_gs,                /* a9 */
		(DISASM_FUNC)&opcode_rsm,                   /* aa */
		(DISASM_FUNC)&opcode_bts,                   /* ab */
		(DISASM_FUNC)&opcode_shrd_immed,            /* ac */
		(DISASM_FUNC)&opcode_shrd_cl,               /* ad */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* ae */
		(DISASM_FUNC)&opcode_imulaf,                /* af */
		(DISASM_FUNC)&opcode_cmpxchg_byte,          /* b0 */
		(DISASM_FUNC)&opcode_cmpxchg,               /* b1 */
		(DISASM_FUNC)&opcode_lss,                   /* b2 */
		(DISASM_FUNC)&opcode_btr,                   /* b3 */
		(DISASM_FUNC)&opcode_lfs,                   /* b4 */
		(DISASM_FUNC)&opcode_lgs,                   /* b5 */
		(DISASM_FUNC)&opcode_movzx_byte,            /* b6 */
		(DISASM_FUNC)&opcode_movzx_word,            /* b7 */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* b8 */
		(DISASM_FUNC)&opcode_ud2_0fb9,              /* b9 */
		(DISASM_FUNC)&opcode_check_reg_0fba,        /* ba */
		(DISASM_FUNC)&opcode_btc,                   /* bb */
		(DISASM_FUNC)&opcode_bsf,                   /* bc */
		(DISASM_FUNC)&opcode_bsr,                   /* bd */
		(DISASM_FUNC)&opcode_movsx_byte,            /* be */
		(DISASM_FUNC)&opcode_movsx_word,            /* bf */
		(DISASM_FUNC)&opcode_xadd_byte,             /* c0 */
		(DISASM_FUNC)&opcode_xadd,                  /* c1 */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* c2 */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* c3 */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* c4 */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* c5 */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* c6 */
		(DISASM_FUNC)&opcode_check_reg_0fc7,        /* c7 */
		(DISASM_FUNC)&opcode_bswap_xxx,             /* c8 */
		(DISASM_FUNC)&opcode_bswap_xxx,             /* c9 */
		(DISASM_FUNC)&opcode_bswap_xxx,             /* ca */
		(DISASM_FUNC)&opcode_bswap_xxx,             /* cb */
		(DISASM_FUNC)&opcode_bswap_xxx,             /* cc */
		(DISASM_FUNC)&opcode_bswap_xxx,             /* cd */
		(DISASM_FUNC)&opcode_bswap_xxx,             /* ce */
		(DISASM_FUNC)&opcode_bswap_xxx,             /* cf */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* d0 */
		(DISASM_FUNC)&opcode_psrlw,                 /* d1 */
		(DISASM_FUNC)&opcode_psrld,                 /* d2 */
		(DISASM_FUNC)&opcode_psrlq,                 /* d3 */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* d4 */
		(DISASM_FUNC)&opcode_pmullw,                /* d5 */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* d6 */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* d7 */
		(DISASM_FUNC)&opcode_psubusb,               /* d8 */
		(DISASM_FUNC)&opcode_psubusw,               /* d9 */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* da */
		(DISASM_FUNC)&opcode_pand,                  /* db */
		(DISASM_FUNC)&opcode_paddusb,               /* dc */
		(DISASM_FUNC)&opcode_paddusw,               /* dd */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* de */
		(DISASM_FUNC)&opcode_pandn,                 /* df */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* e0 */
		(DISASM_FUNC)&opcode_psraw,                 /* e1 */
		(DISASM_FUNC)&opcode_psrad,                 /* e2 */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* e3 */
		(DISASM_FUNC)&opcode_pmulhw,                /* e4 */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* e5 */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* e6 */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* e7 */
		(DISASM_FUNC)&opcode_psubsb,                /* e8 */
		(DISASM_FUNC)&opcode_psubsw,                /* e9 */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* ea */
		(DISASM_FUNC)&opcode_por,                   /* eb */
		(DISASM_FUNC)&opcode_paddsb,                /* ec */
		(DISASM_FUNC)&opcode_paddsw,                /* ed */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* ee */
		(DISASM_FUNC)&opcode_pxor,                  /* ef */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* f0 */
		(DISASM_FUNC)&opcode_psllw,                 /* f1 */
		(DISASM_FUNC)&opcode_pslld,                 /* f2 */
		(DISASM_FUNC)&opcode_psllq,                 /* f3 */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* f4 */
		(DISASM_FUNC)&opcode_pmaddwd,               /* f5 */
		(DISASM_FUNC)&opcode_imul_rm8,              /* f6 */
		(DISASM_FUNC)&opcode_imul_rm1632,           /* f7 */
		(DISASM_FUNC)&opcode_psubb,                 /* f8 */
		(DISASM_FUNC)&opcode_psubw,                 /* f9 */
		(DISASM_FUNC)&opcode_psubd,                 /* fa */
		(DISASM_FUNC)&opcode_two_byte_unused,       /* fb */
		(DISASM_FUNC)&opcode_paddb,                 /* fc */
		(DISASM_FUNC)&opcode_paddw,                 /* fd */
		(DISASM_FUNC)&opcode_paddd,                 /* fe */
		(DISASM_FUNC)&opcode_two_byte_unused        /* ff */
	};
#endif
