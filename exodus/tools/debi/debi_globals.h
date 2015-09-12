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




// buffers.h

// Buffers used during instruction decoding
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

// Verified
u8 	cgc_add_instruction[]		= "add";
u8	cgc_adc_instruction[]		= "adc";
u8	cgc_and_instruction[]		= "and";
u8	cgc_sub_instruction[]		= "sub";
u8	cgc_sbb_instruction[]		= "sbb";
u8	cgc_xor_instruction[]		= "xor";
u8	cgc_cmp_instruction[]		= "cmp";
u8	cgc_bswap_instruction[]		= "bswap";
u8	cgc_aaa_instruction[]		= "aaa";
u8	cgc_aad_instruction[]		= "aad";
u8	cgc_aam_instruction[]		= "aam";
u8	cgc_aas_instruction[]		= "aas";
u8	cgc_cbw_instruction[]		= "cbw";
u8	cgc_clc_instruction[]		= "clc";
u8	cgc_cld_instruction[]		= "cld";
u8	cgc_cli_instruction[]		= "cli";
u8	cgc_clts_instruction[]		= "clts";
u8	cgc_cmc_instruction[]		= "cmc";
u8	cgc_cpuid_instruction[]		= "cpuid";
u8	cgc_cwd_instruction[]		= "cwd";
u8	cgc_daa_instruction[]		= "daa";
u8	cgc_emms_instruction[]		= "emms";
u8	cgc_das_instruction[]		= "das";
u8	cgc_hlt_instruction[]		= "hlt";
u8	cgc_insb_instruction[]		= "insb";
u8	cgc_insd_instruction[]		= "insd";
u8	cgc_insw_instruction[]		= "insw";
u8	cgc_int3_instruction[]		= "int3";
u8	cgc_int_instruction[]		= "int";
u8	cgc_into_instruction[]		= "into";
u8	cgc_iret_instruction[]		= "iret";
u8	cgc_lahf_instruction[]		= "lahf";
u8	cgc_leave_instruction[]		= "leave";
u8	cgc_nop_instruction[]		= "nop";
u8	cgc_outsb_instruction[]		= "outsb";
u8	cgc_outsd_instruction[]		= "outsd";
u8	cgc_outsw_instruction[]		= "outsw";
u8	cgc_pop_instruction[]		= "pop";
u8	cgc_push_instruction[]		= "push";
u8	cgc_popa_instruction[]		= "popa";
u8	cgc_popf_instruction[]		= "popf";
u8	cgc_pusha_instruction[]		= "pusha";
u8	cgc_pushf_instruction[]		= "pushf";
u8	cgc_popad_instruction[]		= "popad";
u8	cgc_popfd_instruction[]		= "popfd";
u8	cgc_pushad_instruction[]	= "pushad";
u8	cgc_pushfd_instruction[]	= "pushfd";
u8	cgc_retf_instruction[]		= "retf";
u8	cgc_retn_instruction[]		= "retn";
u8	cgc_sahf_instruction[]		= "sahf";
u8	cgc_seta_instruction[]		= "seta";
u8	cgc_setc_instruction[]		= "setc";
u8	cgc_setg_instruction[]		= "setg";
u8	cgc_setl_instruction[]		= "setl";
u8	cgc_setna_instruction[]		= "setna";
u8	cgc_setnc_instruction[]		= "setnc";
u8	cgc_setng_instruction[]		= "setng";
u8	cgc_setnl_instruction[]		= "setnl";
u8	cgc_setno_instruction[]		= "setno";
u8	cgc_setns_instruction[]		= "setns";
u8	cgc_setnz_instruction[]		= "setnz";
u8	cgc_seto_instruction[]		= "setno";
u8	cgc_setpe_instruction[]		= "setpe";
u8	cgc_setpo_instruction[]		= "setpo";
u8	cgc_sets_instruction[]		= "sets";
u8	cgc_setz_instruction[]		= "setz";
u8	cgc_stc_instruction[]		= "stc";
u8	cgc_std_instruction[]		= "std";
u8	cgc_sti_instruction[]		= "sti";
u8	cgc_wait_instruction[]		= "wait";
u8	cgc_xlat_instruction[]		= "xlat";
u8	cgc_repe_instruction[]		= "repe";
u8	cgc_repne_instruction[]		= "repne";
u8	cgc_cmpsw_instruction[]		= "cmpsw";
u8	cgc_cmpsd_instruction[]		= "cmpsd";
u8	cgc_lodsw_instruction[]		= "lodsw";
u8	cgc_lodsd_instruction[]		= "lodsd";
u8	cgc_movsw_instruction[]		= "movsw";
u8	cgc_movsd_instruction[]		= "movsd";
u8	cgc_scasw_instruction[]		= "scasw";
u8	cgc_scasd_instruction[]		= "scasd";
u8	cgc_stosw_instruction[]		= "stosw";
u8	cgc_stosd_instruction[]		= "stosd";
u8	cgc_arpl_instruction[]		= "arpl";
u8	cgc_bound_instruction[]		= "bound";
u8	cgc_bsf_instruction[]		= "bsf";
u8	cgc_bsr_instruction[]		= "bsr";
u8	cgc_bt_instruction[]		= "bt";
u8	cgc_btc_instruction[]		= "btc";
u8	cgc_btr_instruction[]		= "btr";
u8	cgc_bts_instruction[]		= "bts";
u8	cgc_call_instruction[]		= "call";
u8	cgc_cmova_instruction[]		= "cmova";
u8	cgc_cmovc_instruction[]		= "cmovc";
u8	cgc_cmovg_instruction[]		= "cmovg";
u8	cgc_cmovl_instruction[]		= "cmovl";
u8	cgc_cmovna_instruction[]	= "cmovna";
u8	cgc_cmovnc_instruction[]	= "cmovnc";
u8	cgc_cmovng_instruction[]	= "cmovng";
u8	cgc_cmovnl_instruction[]	= "cmovnl";
u8	cgc_cmovno_instruction[]	= "cmovno";
u8	cgc_cmovns_instruction[]	= "cmovns";
u8	cgc_cmovnz_instruction[]	= "cmovnz";
u8	cgc_cmovo_instruction[]		= "cmovo";
u8	cgc_cmovpe_instruction[]	= "cmovpe";
u8	cgc_cmovpo_instruction[]	= "cmovpo";
u8	cgc_cmovs_instruction[]		= "cmovs";
u8	cgc_cmovz_instruction[]		= "cmovz";
u8	cgc_cmpxchg_instruction[]	= "cmpxchg";
u8	cgc_dec_instruction[]		= "dec";
u8	cgc_inc_instruction[]		= "inc";
u8	cgc_imul_instruction[]		= "imul";
u8	cgc_icebp_instruction[]		= "icebp";
u8	cgc_sldt_instruction[]		= "sldt";
u8	cgc_lldt_instruction[]		= "lldt";
u8	cgc_str_instruction[]		= "str";
u8	cgc_verr_instruction[]		= "verr";
u8	cgc_verw_instruction[]		= "verw";
u8	cgc_ltr_instruction[]		= "ltr";
u8	cgc_unk_instruction[]		= "unk?";
u8	cgc_sgdt_instruction[]		= "sgdt";
u8	cgc_sidt_instruction[]		= "sidt";
u8	cgc_lgdt_instruction[]		= "lgdt";
u8	cgc_lidt_instruction[]		= "lidt";
u8	cgc_lmsw_instruction[]		= "lmsw";
u8	cgc_smsw_instruction[]		= "smsw";
u8	cgc_invlpg_instruction[]	= "invlpg";
u8	cgc_psraw_instruction[]		= "psraw";
u8	cgc_psrad_instruction[]		= "psrad";
u8	cgc_psrld_instruction[]		= "psrld";
u8	cgc_psrlw_instruction[]		= "psrlw";
u8	cgc_psrlq_instruction[]		= "psrlq";
u8	cgc_psubb_instruction[]		= "psubb";
u8	cgc_psubw_instruction[]		= "psubw";
u8	cgc_psubd_instruction[]		= "psubd";
u8	cgc_psubsb_instruction[]	= "psubsb";
u8	cgc_psubsw_instruction[]	= "psubsw";
u8	cgc_psubusb_instruction[]	= "psubusb";
u8	cgc_psubusw_instruction[]	= "psubusw";
u8	cgc_punpckhbw_instruction[]	= "punpckhbw";
u8	cgc_punpckhwd_instruction[]	= "punpckhwd";
u8	cgc_punpckhdq_instruction[]	= "punpckhdq";
u8	cgc_punpcklbw_instruction[]	= "punpcklbw";
u8	cgc_punpcklwd_instruction[]	= "punpcklwd";
u8	cgc_punpckldq_instruction[]	= "punpckldq";
u8	cgc_pxor_instruction[]		= "pxor";
u8	cgc_rsm_instruction[]		= "rsm";
u8	cgc_shld_instruction[]		= "shld";
u8	cgc_shrd_instruction[]		= "shrd";
u8	cgc_test_instruction[]		= "test";
u8	cgc_xchg_instruction[]		= "xchg";
u8	cgc_ud2_instruction[]		= "ud2";
u8	cgc_wrmsr_instruction[]		= "wrmsr";
u8	cgc_wbinvd_instruction[]	= "wbinvd";
u8	cgc_xadd_instruction[]		= "xadd";
u8	cgc_packssdw_instruction[]	= "packssdw";
u8	cgc_packsswb_instruction[]	= "packsswb";
u8	cgc_packuswb_instruction[]	= "packuswb";
u8	cgc_paddb_instruction[]		= "paddb";
u8	cgc_paddd_instruction[]		= "paddd";
u8	cgc_paddsb_instruction[]	= "paddsb";
u8	cgc_paddsw_instruction[]	= "paddsw";
u8	cgc_paddusb_instruction[]	= "paddusb";
u8	cgc_paddusw_instruction[]	= "paddusw";
u8	cgc_paddw_instruction[]		= "paddw";
u8	cgc_pand_instruction[]		= "pand";
u8	cgc_pandn_instruction[]		= "pandn";
u8	cgc_pcmpeqb_instruction[]	= "pcmpeqb";
u8	cgc_pcmpeqd_instruction[]	= "pcmpeqd";
u8	cgc_pcmpeqw_instruction[]	= "pcmpeqw";
u8	cgc_pcmpgtb_instruction[]	= "pcmpgtb";
u8	cgc_pcmpgtd_instruction[]	= "pcmpgtd";
u8	cgc_pcmpgtw_instruction[]	= "pcmpgtw";
u8	cgc_pmaddwd_instruction[]	= "pmaddwd";
u8	cgc_pmulhw_instruction[]	= "pmulhw";
u8	cgc_pmullw_instruction[]	= "pmullw";
u8	cgc_por_instruction[]		= "por";
u8	cgc_pslld_instruction[]		= "pslld";
u8	cgc_psllq_instruction[]		= "psllq";
u8	cgc_psllw_instruction[]		= "psllw";
u8	cgc_or_instruction[]		= "or";
u8	cgc_hcf_instruction[]		= "hcf";
u8	cgc_cmpxchg8b_instruction[]	= "cmpxchg8b";
u8	cgc_in_instruction[]		= "in";
u8	cgc_rdmsr_instruction[]		= "rdmsr";
u8	cgc_rdpmc_instruction[]		= "rdpmc";
u8	cgc_rdtsc_instruction[]		= "rdtsc";
u8	cgc_movsx_instruction[]		= "movsx";
u8	cgc_movzx_instruction[]		= "movzx";
u8	cgc_lsl_instruction[]		= "lsl";
u8	cgc_lss_instruction[]		= "lss";
u8	cgc_loopne_instruction[]	= "loopne";
u8	cgc_loope_instruction[]		= "loope";
u8	cgc_loop_instruction[]		= "loop";
u8	cgc_lgs_instruction[]		= "lgs";
u8	cgc_lfs_instruction[]		= "lfs";
u8	cgc_les_instruction[]		= "les";
u8	cgc_lea_instruction[]		= "lea";
u8	cgc_lds_instruction[]		= "lds";
u8	cgc_lar_instruction[]		= "lar";
u8	cgc_jz_instruction[]		= "jz";
u8	cgc_js_instruction[]		= "js";
u8	cgc_jpo_instruction[]		= "jpo";
u8	cgc_jpe_instruction[]		= "jpe";
u8	cgc_jo_instruction[]		= "jo";
u8	cgc_jnz_instruction[]		= "jnz";
u8	cgc_jno_instruction[]		= "jno";
u8	cgc_jnl_instruction[]		= "jnl";
u8	cgc_jng_instruction[]		= "jng";
u8	cgc_jnc_instruction[]		= "jnc";
u8	cgc_jna_instruction[]		= "jna";
u8	cgc_jmp_instruction[]		= "jmp";
u8	cgc_jl_instruction[]		= "jl";
u8	cgc_jg_instruction[]		= "jg";
u8	cgc_jcxz_instruction[]		= "jcxz";
u8	cgc_jecxz_instruction[]		= "jecxz";
u8	cgc_jc_instruction[]		= "jc";
u8	cgc_ja_instruction[]		= "ja";
u8	cgc_jns_instruction[]		= "jns";
u8	cgc_invd_instruction[]		= "invd";
u8	cgc_idiv_instruction[]		= "idiv";
u8	cgc_div_instruction[]		= "div";
u8	cgc_neg_instruction[]		= "neg";
u8	cgc_mul_instruction[]		= "mul";
u8	cgc_not_instruction[]		= "not";
u8	cgc_sar_instruction[]		= "sar";
u8	cgc_shr_instruction[]		= "shr";
u8	cgc_shl_instruction[]		= "shl";
u8	cgc_rcr_instruction[]		= "rcr";
u8	cgc_rcl_instruction[]		= "rcl";
u8	cgc_ror_instruction[]		= "ror";
u8	cgc_rol_instruction[]		= "rol";
u8	cgc_mov_instruction[]		= "mov";
u8	cgc_fnop_instruction[]		= "fnop";
u8	cgc_fchs_instruction[]		= "fchs";
u8	cgc_fabs_instruction[]		= "fabs";
u8	cgc_ftst_instruction[]		= "ftst";
u8	cgc_fxam_instruction[]		= "fxam";
u8	cgc_fld1_instruction[]		= "fld1";
u8	cgc_fld2t_instruction[]		= "fld2t";
u8	cgc_fld2e_instruction[]		= "fld2e";
u8	cgc_fldpi_instruction[]		= "fldpi";
u8	cgc_fldlg2_instruction[]	= "fldlg2";
u8	cgc_fldln2_instruction[]	= "fldln2";
u8	cgc_fldz_instruction[]		= "fldz";
u8	cgc_f2xm1_instruction[]		= "f2xm1";
u8	cgc_fyl2x_instruction[]		= "fyl2x";
u8	cgc_fptan_instruction[]		= "fptan";
u8	cgc_fpatan_instruction[]	= "fpatan";
u8	cgc_fxtract_instruction[]	= "fxtract";
u8	cgc_fprem1_instruction[]	= "fprem1";
u8	cgc_fdecstp_instruction[]	= "fdecstp";
u8	cgc_fincstp_instruction[]	= "fincstp";
u8	cgc_fprem_instruction[]		= "fprem";
u8	cgc_fyl2xp1_instruction[]	= "fyl2xp1";
u8	cgc_fsqrt_instruction[]		= "fsqrt";
u8	cgc_fsincos_instruction[]	= "fsincos";
u8	cgc_frndint_instruction[]	= "frndint";
u8	cgc_fscale_instruction[]	= "fscale";
u8	cgc_fsin_instruction[]		= "fsin";
u8	cgc_fcos_instruction[]		= "fcos";
u8	cgc_fadd_instruction[]		= "fadd";
u8	cgc_fmul_instruction[]		= "fmul";
u8	cgc_fcom_instruction[]		= "fcom";
u8	cgc_fcomp_instruction[]		= "fcomp";
u8	cgc_fsub_instruction[]		= "fsub";
u8	cgc_fsubr_instruction[]		= "fsubr";
u8	cgc_fdiv_instruction[]		= "fdiv";
u8	cgc_fdivr_instruction[]		= "fdivr";
u8	cgc_fld_instruction[]		= "fld";
u8	cgc_fst_instruction[]		= "fst";
u8	cgc_fstp_instruction[]		= "fstp";
u8	cgc_fiadd_instruction[]		= "fiadd";
u8	cgc_fimul_instruction[]		= "fimul";
u8	cgc_ficom_instruction[]		= "ficom";
u8	cgc_ficomp_instruction[]	= "ficomp";
u8	cgc_fisub_instruction[]		= "fisub";
u8	cgc_fisubr_instruction[]	= "fisubr";
u8	cgc_fidiv_instruction[]		= "fidiv";
u8	cgc_fidivr_instruction[]	= "fidivr";
u8	cgc_fist_instruction[]		= "fist";
u8	cgc_fistp_instruction[]		= "fistp";
u8	cgc_fild_instruction[]		= "fild";
u8	cgc_fbld_instruction[]		= "fbld";
u8	cgc_fbstp_instruction[]		= "fbstp";
u8	cgc_fxch_instruction[]		= "fxch";
u8	cgc_fucomp_instruction[]	= "fucomp";
u8	cgc_fucompp_instruction[]	= "fucompp";
u8	cgc_fnclex_instruction[]	= "fnclex_instruction";
u8	cgc_fninit_instruction[]	= "fninit";
u8	cgc_fnstsw_instruction[]	= "fnstsw";
u8	cgc_fldcw_instruction[]		= "fldcw";
u8	cgc_fnstcw_instruction[]	= "fnstcw";
u8	cgc_fldenv_instruction[]	= "fldenv";
u8	cgc_fnstenv_instruction[]	= "fnstenv";
u8	cgc_frstor_instruction[]	= "frstor";
u8	cgc_fnsave_instruction[]	= "fnsave";

u8	cgc_10byte_ptr[]			= "byte10 ptr ";
u8	cgc_6byte_ptr[]				= "byte6 ptr ";
u8	cgc_tbyte_ptr[]				= "tbyte ptr ";
u8	cgc_dqword_ptr[]			= "dqword ptr ";
u8	cgc_qword_ptr[]				= "qword ptr ";
u8	cgc_dword_ptr[]				= "dword ptr ";
u8	cgc_word_ptr[]				= "word ptr ";
u8	cgc_byte_ptr[]				= "byte ptr ";
u8	cgc_unk_ptr[]				= "unk? ptr ";		// Should never be used
u8	cgc_illegal_ptr[]			= "!illegal! ";		// Used when illegal encoding is found
u8	cgc_m16_16_ptr[]			= "m16_16 ptr ";
u8	cgc_m16_32_ptr[]			= "m16_32 ptr ";
u8	cgc_f32_ptr[]				= "f32 ptr ";
u8	cgc_f64_ptr[]				= "f64 ptr ";
u8	cgc_f80_ptr[]				= "f80 ptr ";
u8	cgc_s16_ptr[]				= "s16 ptr ";
u8	cgc_s32_ptr[]				= "s32 ptr ";
u8	cgc_s64_ptr[]				= "s64 ptr ";
u8	cgc_m80_ptr[]				= "m80 ptr ";
u8	cgc_mmx_ptr[]				= "mmx ptr ";
u8	cgc_xmmx_ptr[]				= "xmmx ptr ";
u8	cgc_fpu_ptr[]				= "fpu ptr ";
u8	cgc_94byte_ptr[]			= "byte94 ptr ";
u8	cgc_108byte_ptr[]			= "byte108 ptr ";
u8	cgc_14byte_ptr[]			= "byte14 ptr ";
u8	cgc_28byte_ptr[]			= "byte28 ptr ";

u8	cgc_plus_string[]			= "+";
u8	cgc_minus_string[]			= "-";
u8	cgc_qq_reg[]				= "??";
u8	cgc_1_string[]				= "1";				// Used for instructions which have implicit 1 for operand

u8	cgc_cs_reg[]				= "cs";
u8	cgc_ds_reg[]				= "ds";
u8	cgc_es_reg[]				= "es";
u8	cgc_fs_reg[]				= "fs";
u8	cgc_gs_reg[]				= "gs";
u8	cgc_ss_reg[]				= "ss";
u8	cgc_qqs_reg[]				= "?s";

u8 	cgc_cs_colon[]				= "cs:";
u8 	cgc_ds_colon[]				= "ds:";
u8 	cgc_es_colon[]				= "es:";
u8 	cgc_fs_colon[]				= "fs:";
u8 	cgc_gs_colon[]				= "gs:";
u8 	cgc_ss_colon[]				= "ss:";
u8 	cgc_qqs_colon[]				= "?s:";

u8 	cgc_al_reg[]				= "al";
u8 	cgc_bl_reg[]				= "bl";
u8 	cgc_cl_reg[]				= "cl";
u8 	cgc_dl_reg[]				= "dl";
u8 	cgc_ah_reg[]				= "ah";
u8 	cgc_bh_reg[]				= "bh";
u8 	cgc_ch_reg[]				= "ch";
u8 	cgc_dh_reg[]				= "dh";

u8 	cgc_ax_reg[]				= "ax";
u8 	cgc_bx_reg[]				= "bx";
u8 	cgc_cx_reg[]				= "cx";
u8 	cgc_dx_reg[]				= "dx";
u8 	cgc_si_reg[]				= "si";
u8 	cgc_di_reg[]				= "di";
u8 	cgc_bp_reg[]				= "bp";
u8 	cgc_sp_reg[]				= "sp";
u8 	cgc_ip_reg[]				= "ip";

u8 	cgc_eax_reg[]				= "eax";
u8 	cgc_ebx_reg[]				= "ebx";
u8 	cgc_ecx_reg[]				= "ecx";
u8 	cgc_edx_reg[]				= "edx";
u8 	cgc_esi_reg[]				= "esi";
u8 	cgc_edi_reg[]				= "edi";
u8 	cgc_ebp_reg[]				= "ebp";
u8 	cgc_esp_reg[]				= "esp";
u8 	cgc_eip_reg[]				= "eip";

u8 	cgc_rax_reg[]				= "rax";
u8 	cgc_rbx_reg[]				= "rbx";
u8 	cgc_rcx_reg[]				= "rcx";
u8 	cgc_rdx_reg[]				= "rdx";
u8 	cgc_rsi_reg[]				= "rsi";
u8 	cgc_rdi_reg[]				= "rdi";
u8 	cgc_rbp_reg[]				= "rbp";
u8 	cgc_rsp_reg[]				= "rsp";
u8 	cgc_rip_reg[]				= "rip";

u8 	cgc_cr0_reg[]				= "cr0";
u8 	cgc_cr1_reg[]				= "cr1";
u8 	cgc_cr2_reg[]				= "cr2";
u8 	cgc_cr3_reg[]				= "cr3";
u8 	cgc_cr4_reg[]				= "cr4";
u8 	cgc_cr5_reg[]				= "cr5";
u8 	cgc_cr6_reg[]				= "cr6";
u8 	cgc_cr7_reg[]				= "cr7";

u8 	cgc_dr0_reg[]				= "dr0";
u8 	cgc_dr1_reg[]				= "dr1";
u8 	cgc_dr2_reg[]				= "dr2";
u8 	cgc_dr3_reg[]				= "dr3";
u8 	cgc_dr4_reg[]				= "dr4";
u8 	cgc_dr5_reg[]				= "dr5";
u8 	cgc_dr6_reg[]				= "dr6";
u8 	cgc_dr7_reg[]				= "dr7";

u8 	cgc_tr0_reg[]				= "tr0";
u8 	cgc_tr1_reg[]				= "tr1";
u8 	cgc_tr2_reg[]				= "tr2";
u8 	cgc_tr3_reg[]				= "tr3";
u8 	cgc_tr4_reg[]				= "tr4";
u8 	cgc_tr5_reg[]				= "tr5";
u8 	cgc_tr6_reg[]				= "tr6";
u8 	cgc_tr7_reg[]				= "tr7";

u8 	cgc_st0_reg[]				= "st0";
u8 	cgc_st1_reg[]				= "st1";
u8 	cgc_st2_reg[]				= "st2";
u8 	cgc_st3_reg[]				= "st3";
u8 	cgc_st4_reg[]				= "st4";
u8 	cgc_st5_reg[]				= "st5";
u8 	cgc_st6_reg[]				= "st6";
u8 	cgc_st7_reg[]				= "st7";

u8 	cgc_mm0_reg[]				= "mm0";
u8 	cgc_mm1_reg[]				= "mm1";
u8 	cgc_mm2_reg[]				= "mm2";
u8 	cgc_mm3_reg[]				= "mm3";
u8 	cgc_mm4_reg[]				= "mm4";
u8 	cgc_mm5_reg[]				= "mm5";
u8 	cgc_mm6_reg[]				= "mm6";
u8 	cgc_mm7_reg[]				= "mm7";

u8 	cgc_xmm0_reg[]				= "xmm0";
u8 	cgc_xmm1_reg[]				= "xmm1";
u8 	cgc_xmm2_reg[]				= "xmm2";
u8 	cgc_xmm3_reg[]				= "xmm3";
u8 	cgc_xmm4_reg[]				= "xmm4";
u8 	cgc_xmm5_reg[]				= "xmm5";
u8 	cgc_xmm6_reg[]				= "xmm6";
u8 	cgc_xmm7_reg[]				= "xmm7";

u8 	cgc_q0_reg[]				= "q0";
u8 	cgc_q1_reg[]				= "q1";
u8 	cgc_q2_reg[]				= "q2";
u8 	cgc_q3_reg[]				= "q3";
u8 	cgc_q4_reg[]				= "q4";
u8 	cgc_q5_reg[]				= "q5";
u8 	cgc_q6_reg[]				= "q6";
u8 	cgc_q7_reg[]				= "q7";

u8 	cgc_bx_plus_si[]			= "[bx+si]";
u8 	cgc_bx_plus_di[]			= "[bx+di]";
u8 	cgc_bp_plus_si[]			= "[bp+si]";
u8 	cgc_bp_plus_di[]			= "[bp+di]";
u8 	cgc_si_indirect[]			= "[si]";
u8 	cgc_di_indirect[]			= "[di]";
u8 	cgc_bx_indirect[]			= "[bx]";

u8 	cgc_eax_indirect[]			= "[eax]";
u8 	cgc_ebx_indirect[]			= "[ebx]";
u8 	cgc_ecx_indirect[]			= "[ecx]";
u8 	cgc_edx_indirect[]			= "[edx]";
u8 	cgc_esi_indirect[]			= "[esi]";
u8 	cgc_edi_indirect[]			= "[edi]";
u8 	cgc_ebp_indirect[]			= "[ebp]";
u8 	cgc_esp_indirect[]			= "[esp]";

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
