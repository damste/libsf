//////////
//
// /libsf/exodus/tools/common/debi_globals.h
//
//////
// Version 0.80
// Copyright (c) 2014-2015 by Rick C. Hodgin
//////
// Last update:
//     Mar.17.2016
//////
// Change log:
//     Mar.17.2016 - Initial creation
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
// Assembly opcodes
//////
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

	u8	cgc_6byte_ptr[]				= "m6byte ptr ";
	u8	cgc_10byte_ptr[]			= "m10byte ptr ";
	u8	cgc_14byte_ptr[]			= "m14byte ptr ";
	u8	cgc_28byte_ptr[]			= "m28byte ptr ";
	u8	cgc_94byte_ptr[]			= "m94byte ptr ";
	u8	cgc_108byte_ptr[]			= "m108byte ptr ";

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
