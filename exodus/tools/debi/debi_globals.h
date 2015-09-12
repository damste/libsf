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
u8 	operand1_buffer[32];
u8 	operand2_buffer[32];
u8 	operand3_buffer[32];
u8 	immediate_buffer[32];
u8 	sib_buffer[32];
u8 	sib2_buffer[32];
u8 	comment_buffer[256];					// General comment about the instruction
u8 	line_comment_buffer[256];			// Comment appearing on the same assembly line
u8 	prefix_op_buffer[256];
u8 	prefix_op1_buffer[256];
u8 	prefix_op2_buffer[256];
u8 	misc_buffer[256];

// Verified
u8 	_add_instruction[]		= "add";

// Still needs checked:
u8	_adc_instruction[]		= "adc";
u8	_and_instruction[]		= "and";
u8	_sub_instruction[]		= "sub";
u8	_sbb_instruction[]		= "sbb";
u8	_xor_instruction[]		= "xor";
u8	_cmp_instruction[]		= "cmp";
u8	_bswap_instruction[]	= "bswap";
u8	_aaa_instruction[]		= "aaa";
u8	_aad_instruction[]		= "aad";
u8	_aam_instruction[]		= "aam";
u8	_aas_instruction[]		= "aas";
u8	_cbw_instruction[]		= "cbw";
u8	_clc_instruction[]		= "clc";
u8	_cld_instruction[]		= "cld";
u8	_cli_instruction[]		= "cli";
u8	_clts_instruction[]		= "clts";
u8	_cmc_instruction[]		= "cmc";
u8	_cpuid_instruction[]	= "cpuid";
u8	_cwd_instruction[]		= "cwd";
u8	_daa_instruction[]		= "daa";
u8	_emms_instruction[]		= "emms";
u8	_das_instruction[]		= "das";
u8	_hlt_instruction[]		= "hlt";
u8	_insb_instruction[]		= "insb";
u8	_insd_instruction[]		= "insd";
u8	_insw_instruction[]		= "insw";
u8	_int3_instruction[]		= "int3";
u8	_int_instruction[]		= "int";
u8	_into_instruction[]		= "into";
u8	_iret_instruction[]		= "iret";
u8	_lahf_instruction[]		= "lahf";
u8	_leave_instruction[]	= "leave";
u8	_nop_instruction[]		= "nop";
u8	_outsb_instruction[]	= "outsb";
u8	_outsd_instruction[]	= "outsd";
u8	_outsw_instruction[]	= "outsw";
u8	_pop_instruction[]		= "pop";
u8	_push_instruction[]		= "push";
u8	_popa_instruction[]		= "popa";
u8	_popf_instruction[]		= "popf";
u8	_pusha_instruction[]	= "pusha";
u8	_pushf_instruction[]	= "pushf";
u8	_popad_instruction[]	= "popad";
u8	_popfd_instruction[]	= "popfd";
u8	_pushad_instruction[]	= "pushad";
u8	_pushfd_instruction[]	= "pushfd";
u8	_retf_instruction[]		= "retf";
u8	_retn_instruction[]		= "retn";
u8	_sahf_instruction[]		= "sahf";
u8	_seta_instruction[]		= "seta";
u8	_setc_instruction[]		= "setc";
u8	_setg_instruction[]		= "setg";
u8	_setl_instruction[]		= "setl";
u8	_setna_instruction[]	= "setna";
u8	_setnc_instruction[]	= "setnc";
u8	_setng_instruction[]	= "setng";
u8	_setnl_instruction[]	= "setnl";
u8	_setno_instruction[]	= "setno";
u8	_setns_instruction[]	= "setns";
u8	_setnz_instruction[]	= "setnz";
u8	_seto_instruction[]		= "setno";
u8	_setpe_instruction[]	= "setpe";
u8	_setpo_instruction[]	= "setpo";
u8	_sets_instruction[]		= "sets";
u8	_setz_instruction[]		= "setz";
u8	_stc_instruction[]		= "stc";
u8	_std_instruction[]		= "std";
u8	_sti_instruction[]		= "sti";
u8	_wait_instruction[]		= "wait";
u8	_xlat_instruction[]		= "xlat";
u8	_repe_instruction[]		= "repe";
u8	_repne_instruction[]	= "repne";
u8	_cmpsw_instruction[]	= "cmpsw";
u8	_cmpsd_instruction[]	= "cmpsd";
u8	_lodsw_instruction[]	= "lodsw";
u8	_lodsd_instruction[]	= "lodsd";
u8	_movsw_instruction[]	= "movsw";
u8	_movsd_instruction[]	= "movsd";
u8	_scasw_instruction[]	= "scasw";
u8	_scasd_instruction[]	= "scasd";
u8	_stosw_instruction[]	= "stosw";
u8	_stosd_instruction[]	= "stosd";
u8	_arpl_instruction[]		= "arpl";
u8	_bound_instruction[]	= "bound";
u8	_bsf_instruction[]		= "bsf";
u8	_bsr_instruction[]		= "bsr";
u8	_bt_instruction[]		= "bt";
u8	_btc_instruction[]		= "btc";
u8	_btr_instruction[]		= "btr";
u8	_bts_instruction[]		= "bts";
u8	_call_instruction[]		= "call";
u8	_cmova_instruction[]	= "cmova";
u8	_cmovc_instruction[]	= "cmovc";
u8	_cmovg_instruction[]	= "cmovg";
u8	_cmovl_instruction[]	= "cmovl";
u8	_cmovna_instruction[]	= "cmovna";
u8	_cmovnc_instruction[]	= "cmovnc";
u8	_cmovng_instruction[]	= "cmovng";
u8	_cmovnl_instruction[]	= "cmovnl";
u8	_cmovno_instruction[]	= "cmovno";
u8	_cmovns_instruction[]	= "cmovns";
u8	_cmovnz_instruction[]	= "cmovnz";
u8	_cmovo_instruction[]	= "cmovo";
u8	_cmovpe_instruction[]	= "cmovpe";
u8	_cmovpo_instruction[]	= "cmovpo";
u8	_cmovs_instruction[]	= "cmovs";
u8	_cmovz_instruction[]	= "cmovz";
u8	_cmpxchg_instruction[]	= "cmpxchg";
u8	_dec_instruction[]		= "dec";
u8	_inc_instruction[]		= "inc";
u8	_imul_instruction[]		= "imul";
u8	_icebp_instruction[]	= "icebp";
u8	_sldt_instruction[]		= "sldt";
u8	_lldt_instruction[]		= "lldt";
u8	_str_instruction[]		= "str";
u8	_verr_instruction[]		= "verr";
u8	_verw_instruction[]		= "verw";
u8	_ltr_instruction[]		= "ltr";
u8	_unk_instruction[]		= "unk?";
u8	_sgdt_instruction[]		= "sgdt";
u8	_sidt_instruction[]		= "sidt";
u8	_lgdt_instruction[]		= "lgdt";
u8	_lidt_instruction[]		= "lidt";
u8	_lmsw_instruction[]		= "lmsw";
u8	_smsw_instruction[]		= "smsw";
u8	_invlpg_instruction[]	= "invlpg";
u8	_psraw_instruction[]	= "psraw";
u8	_psrad_instruction[]	= "psrad";
u8	_psrld_instruction[]	= "psrld";
u8	_psrlw_instruction[]	= "psrlw";
u8	_psrlq_instruction[]	= "psrlq";
u8	_psubb_instruction[]	= "psubb";
u8	_psubw_instruction[]	= "psubw";
u8	_psubd_instruction[]	= "psubd";
u8	_psubsb_instruction[]	= "psubsb";
u8	_psubsw_instruction[]	= "psubsw";
u8	_psubusb_instruction[]	= "psubusb";
u8	_psubusw_instruction[]	= "psubusw";
u8	_punpckhbw_instruction[]= "punpckhbw";
u8	_punpckhwd_instruction[]= "punpckhwd";
u8	_punpckhdq_instruction[]= "punpckhdq";
u8	_punpcklbw_instruction[]= "punpcklbw";
u8	_punpcklwd_instruction[]= "punpcklwd";
u8	_punpckldq_instruction[]= "punpckldq";
u8	_pxor_instruction[]		= "pxor";
u8	_rsm_instruction[]		= "rsm";
u8	_shld_instruction[]		= "shld";
u8	_shrd_instruction[]		= "shrd";
u8	_test_instruction[]		= "test";
u8	_xchg_instruction[]		= "xchg";
u8	_ud2_instruction[]		= "ud2";
u8	_wrmsr_instruction[]	= "wrmsr";
u8	_wbinvd_instruction[]	= "wbinvd";
u8	_xadd_instruction[]		= "xadd";
u8	_packssdw_instruction[]	= "packssdw";
u8	_packsswb_instruction[]	= "packsswb";
u8	_packuswb_instruction[]	= "packuswb";
u8	_paddb_instruction[]	= "paddb";
u8	_paddd_instruction[]	= "paddd";
u8	_paddsb_instruction[]	= "paddsb";
u8	_paddsw_instruction[]	= "paddsw";
u8	_paddusb_instruction[]	= "paddusb";
u8	_paddusw_instruction[]	= "paddusw";
u8	_paddw_instruction[]	= "paddw";
u8	_pand_instruction[]		= "pand";
u8	_pandn_instruction[]	= "pandn";
u8	_pcmpeqb_instruction[]	= "pcmpeqb";
u8	_pcmpeqd_instruction[]	= "pcmpeqd";
u8	_pcmpeqw_instruction[]	= "pcmpeqw";
u8	_pcmpgtb_instruction[]	= "pcmpgtb";
u8	_pcmpgtd_instruction[]	= "pcmpgtd";
u8	_pcmpgtw_instruction[]	= "pcmpgtw";
u8	_pmaddwd_instruction[]	= "pmaddwd";
u8	_pmulhw_instruction[]	= "pmulhw";
u8	_pmullw_instruction[]	= "pmullw";
u8	_por_instruction[]		= "por";
u8	_pslld_instruction[]	= "pslld";
u8	_psllq_instruction[]	= "psllq";
u8	_psllw_instruction[]	= "psllw";
u8	_or_instruction[]		= "or";
u8	_hcf_instruction[]		= "hcf";
u8	_cmpxchg8b_instruction[]= "cmpxchg8b";
u8	_in_instruction[]		= "in";
u8	_rdmsr_instruction[]	= "rdmsr";
u8	_rdpmc_instruction[]	= "rdpmc";
u8	_rdtsc_instruction[]	= "rdtsc";
u8	_movsx_instruction[]	= "movsx";
u8	_movzx_instruction[]	= "movzx";
u8	_lsl_instruction[]		= "lsl";
u8	_lss_instruction[]		= "lss";
u8	_loopne_instruction[]	= "loopne";
u8	_loope_instruction[]	= "loope";
u8	_loop_instruction[]		= "loop";
u8	_lgs_instruction[]		= "lgs";
u8	_lfs_instruction[]		= "lfs";
u8	_les_instruction[]		= "les";
u8	_lea_instruction[]		= "lea";
u8	_lds_instruction[]		= "lds";
u8	_lar_instruction[]		= "lar";
u8	_jz_instruction[]		= "jz";
u8	_js_instruction[]		= "js";
u8	_jpo_instruction[]		= "jpo";
u8	_jpe_instruction[]		= "jpe";
u8	_jo_instruction[]		= "jo";
u8	_jnz_instruction[]		= "jnz";
u8	_jno_instruction[]		= "jno";
u8	_jnl_instruction[]		= "jnl";
u8	_jng_instruction[]		= "jng";
u8	_jnc_instruction[]		= "jnc";
u8	_jna_instruction[]		= "jna";
u8	_jmp_instruction[]		= "jmp";
u8	_jl_instruction[]		= "jl";
u8	_jg_instruction[]		= "jg";
u8	_jcxz_instruction[]		= "jcxz";
u8	_jecxz_instruction[]	= "jecxz";
u8	_jc_instruction[]		= "jc";
u8	_ja_instruction[]		= "ja";
u8	_jns_instruction[]		= "jns";
u8	_invd_instruction[]		= "invd";
u8	_idiv_instruction[]		= "idiv";
u8	_div_instruction[]		= "div";
u8	_neg_instruction[]		= "neg";
u8	_mul_instruction[]		= "mul";
u8	_not_instruction[]		= "not";
u8	_sar_instruction[]		= "sar";
u8	_shr_instruction[]		= "shr";
u8	_shl_instruction[]		= "shl";
u8	_rcr_instruction[]		= "rcr";
u8	_rcl_instruction[]		= "rcl";
u8	_ror_instruction[]		= "ror";
u8	_rol_instruction[]		= "rol";
u8	_mov_instruction[]		= "mov";
u8	_fnop_instruction[]		= "fnop";
u8	_fchs_instruction[]		= "fchs";
u8	_fabs_instruction[]		= "fabs";
u8	_ftst_instruction[]		= "ftst";
u8	_fxam_instruction[]		= "fxam";
u8	_fld1_instruction[]		= "fld1";
u8	_fld2t_instruction[]	= "fld2t";
u8	_fld2e_instruction[]	= "fld2e";
u8	_fldpi_instruction[]	= "fldpi";
u8	_fldlg2_instruction[]	= "fldlg2";
u8	_fldln2_instruction[]	= "fldln2";
u8	_fldz_instruction[]		= "fldz";
u8	_f2xm1_instruction[]	= "f2xm1";
u8	_fyl2x_instruction[]	= "fyl2x";
u8	_fptan_instruction[]	= "fptan";
u8	_fpatan_instruction[]	= "fpatan";
u8	_fxtract_instruction[]	= "fxtract";
u8	_fprem1_instruction[]	= "fprem1";
u8	_fdecstp_instruction[]	= "fdecstp";
u8	_fincstp_instruction[]	= "fincstp";
u8	_fprem_instruction[]	= "fprem";
u8	_fyl2xp1_instruction[]	= "fyl2xp1";
u8	_fsqrt_instruction[]	= "fsqrt";
u8	_fsincos_instruction[]	= "fsincos";
u8	_frndint_instruction[]	= "frndint";
u8	_fscale_instruction[]	= "fscale";
u8	_fsin_instruction[]		= "fsin";
u8	_fcos_instruction[]		= "fcos";
u8	_fadd_instruction[]		= "fadd";
u8	_fmul_instruction[]		= "fmul";
u8	_fcom_instruction[]		= "fcom";
u8	_fcomp_instruction[]	= "fcomp";
u8	_fsub_instruction[]		= "fsub";
u8	_fsubr_instruction[]	= "fsubr";
u8	_fdiv_instruction[]		= "fdiv";
u8	_fdivr_instruction[]	= "fdivr";
u8	_fld_instruction[]		= "fld";
u8	_fst_instruction[]		= "fst";
u8	_fstp_instruction[]		= "fstp";
u8	_fiadd_instruction[]	= "fiadd";
u8	_fimul_instruction[]	= "fimul";
u8	_ficom_instruction[]	= "ficom";
u8	_ficomp_instruction[]	= "ficomp";
u8	_fisub_instruction[]	= "fisub";
u8	_fisubr_instruction[]	= "fisubr";
u8	_fidiv_instruction[]	= "fidiv";
u8	_fidivr_instruction[]	= "fidivr";
u8	_fist_instruction[]		= "fist";
u8	_fistp_instruction[]	= "fistp";
u8	_fild_instruction[]		= "fild";
u8	_fbld_instruction[]		= "fbld";
u8	_fbstp_instruction[]	= "fbstp";
u8	_fxch_instruction[]		= "fxch";
u8	_fucomp_instruction[]	= "fucomp";
u8	_fucompp_instruction[]	= "fucompp";
u8	_fnclex_instruction[]	= "fnclex_instruction";
u8	_fninit_instruction[]	= "fninit";
u8	_fnstsw_instruction[]	= "fnstsw";
u8	_fldcw_instruction[]	= "fldcw";
u8	_fnstcw_instruction[]	= "fnstcw";
u8	_fldenv_instruction[]	= "fldenv";
u8	_fnstenv_instruction[]	= "fnstenv";
u8	_frstor_instruction[]	= "frstor";
u8	_fnsave_instruction[]	= "fnsave";

u8	_10byte_ptr[]	= "_10byte ptr ";
u8	_6byte_ptr[]	= "_6byte ptr ";
u8	_tbyte_ptr[]	= "tbyte ptr ";
u8	_dqword_ptr[]	= "dqword ptr ";
u8	_qword_ptr[]	= "qword ptr ";
u8	_dword_ptr[]	= "dword ptr ";
u8	_word_ptr[]		= "word ptr ";
u8	_byte_ptr[]		= "byte ptr ";
u8	_unk_ptr[]		= "unk? ptr ";		// Should never be used
u8	_illegal_ptr[]	= "!illegal! ";		// Used when illegal encoding is found
u8	_m16_16_ptr[]	= "m16:16 ptr ";
u8	_m16_32_ptr[]	= "m16:32 ptr ";
u8	_f32_ptr[]		= "f32 ptr ";
u8	_f64_ptr[]		= "f64 ptr ";
u8	_f80_ptr[]		= "f80 ptr ";
u8	_s16_ptr[]		= "s16 ptr ";
u8	_s32_ptr[]		= "s32 ptr ";
u8	_s64_ptr[]		= "s64 ptr ";
u8	_m80_ptr[]		= "m80 ptr ";
u8	_mmx_ptr[]		= "mmx ptr ";
u8	_xmmx_ptr[]		= "xmmx ptr ";
u8	_fpu_ptr[]		= "fpu ptr ";
u8	_94byte_ptr[]	= "94byte ptr ";
u8	_108byte_ptr[]	= "108byte ptr ";
u8	_14byte_ptr[]	= "14byte ptr ";
u8	_28byte_ptr[]	= "28byte ptr ";

u8	_plus_string[]	= "+";
u8	_minus_string[]	= "-";
u8	_qq_reg[]		= "??";
u8	_1_string[]		= "1";				// Used for instructions which have implicit 1 for operand

u8	_cs_reg[]	= "cs";
u8	_ds_reg[]	= "ds";
u8	_es_reg[]	= "es";
u8	_fs_reg[]	= "fs";
u8	_gs_reg[]	= "gs";
u8	_ss_reg[]	= "ss";
u8	_qqs_reg[]	= "?s";

u8 	_cs_colon[]	= "cs:";
u8 	_ds_colon[]	= "ds:";
u8 	_es_colon[]	= "es:";
u8 	_fs_colon[]	= "fs:";
u8 	_gs_colon[]	= "gs:";
u8 	_ss_colon[]	= "ss:";
u8 	_qqs_colon[]= "?s:";

u8 	_al_reg[]	= "al";
u8 	_bl_reg[]	= "bl";
u8 	_cl_reg[]	= "cl";
u8 	_dl_reg[]	= "dl";
u8 	_ah_reg[]	= "ah";
u8 	_bh_reg[]	= "bh";
u8 	_ch_reg[]	= "ch";
u8 	_dh_reg[]	= "dh";

u8 	_ax_reg[]	= "ax";
u8 	_bx_reg[]	= "bx";
u8 	_cx_reg[]	= "cx";
u8 	_dx_reg[]	= "dx";
u8 	_si_reg[]	= "si";
u8 	_di_reg[]	= "di";
u8 	_bp_reg[]	= "bp";
u8 	_sp_reg[]	= "sp";
u8 	_ip_reg[]	= "ip";

u8 	_eax_reg[]	= "eax";
u8 	_ebx_reg[]	= "ebx";
u8 	_ecx_reg[]	= "ecx";
u8 	_edx_reg[]	= "edx";
u8 	_esi_reg[]	= "esi";
u8 	_edi_reg[]	= "edi";
u8 	_ebp_reg[]	= "ebp";
u8 	_esp_reg[]	= "esp";
u8 	_eip_reg[]	= "eip";

u8 	_rax_reg[]	= "rax";
u8 	_rbx_reg[]	= "rbx";
u8 	_rcx_reg[]	= "rcx";
u8 	_rdx_reg[]	= "rdx";
u8 	_rsi_reg[]	= "rsi";
u8 	_rdi_reg[]	= "rdi";
u8 	_rbp_reg[]	= "rbp";
u8 	_rsp_reg[]	= "rsp";
u8 	_rip_reg[]	= "rip";

u8 	_cr0_reg[]	= "cr0";
u8 	_cr1_reg[]	= "cr1";
u8 	_cr2_reg[]	= "cr2";
u8 	_cr3_reg[]	= "cr3";
u8 	_cr4_reg[]	= "cr4";
u8 	_cr5_reg[]	= "cr5";
u8 	_cr6_reg[]	= "cr6";
u8 	_cr7_reg[]	= "cr7";

u8 	_dr0_reg[]	= "dr0";
u8 	_dr1_reg[]	= "dr1";
u8 	_dr2_reg[]	= "dr2";
u8 	_dr3_reg[]	= "dr3";
u8 	_dr4_reg[]	= "dr4";
u8 	_dr5_reg[]	= "dr5";
u8 	_dr6_reg[]	= "dr6";
u8 	_dr7_reg[]	= "dr7";

u8 	_tr0_reg[]	= "tr0";
u8 	_tr1_reg[]	= "tr1";
u8 	_tr2_reg[]	= "tr2";
u8 	_tr3_reg[]	= "tr3";
u8 	_tr4_reg[]	= "tr4";
u8 	_tr5_reg[]	= "tr5";
u8 	_tr6_reg[]	= "tr6";
u8 	_tr7_reg[]	= "tr7";

u8 	_st0_reg[]	= "st0";
u8 	_st1_reg[]	= "st1";
u8 	_st2_reg[]	= "st2";
u8 	_st3_reg[]	= "st3";
u8 	_st4_reg[]	= "st4";
u8 	_st5_reg[]	= "st5";
u8 	_st6_reg[]	= "st6";
u8 	_st7_reg[]	= "st7";

u8 	_mm0_reg[]	= "mm0";
u8 	_mm1_reg[]	= "mm1";
u8 	_mm2_reg[]	= "mm2";
u8 	_mm3_reg[]	= "mm3";
u8 	_mm4_reg[]	= "mm4";
u8 	_mm5_reg[]	= "mm5";
u8 	_mm6_reg[]	= "mm6";
u8 	_mm7_reg[]	= "mm7";

u8 	_xmm0_reg[]	= "xmm0";
u8 	_xmm1_reg[]	= "xmm1";
u8 	_xmm2_reg[]	= "xmm2";
u8 	_xmm3_reg[]	= "xmm3";
u8 	_xmm4_reg[]	= "xmm4";
u8 	_xmm5_reg[]	= "xmm5";
u8 	_xmm6_reg[]	= "xmm6";
u8 	_xmm7_reg[]	= "xmm7";

u8 	_q0_reg[]	= "q0";
u8 	_q1_reg[]	= "q1";
u8 	_q2_reg[]	= "q2";
u8 	_q3_reg[]	= "q3";
u8 	_q4_reg[]	= "q4";
u8 	_q5_reg[]	= "q5";
u8 	_q6_reg[]	= "q6";
u8 	_q7_reg[]	= "q7";

u8 	_bx_plus_si[]	= "[bx+si]";
u8 	_bx_plus_di[]	= "[bx+di]";
u8 	_bp_plus_si[]	= "[bp+si]";
u8 	_bp_plus_di[]	= "[bp+di]";
u8 	_si_indirect[]	= "[si]";
u8 	_di_indirect[]	= "[di]";
u8 	_bx_indirect[]	= "[bx]";

u8 	_eax_indirect[]	= "[eax]";
u8 	_ebx_indirect[]	= "[ebx]";
u8 	_ecx_indirect[]	= "[ecx]";
u8 	_edx_indirect[]	= "[edx]";
u8 	_esi_indirect[]	= "[esi]";
u8 	_edi_indirect[]	= "[edi]";
u8 	_ebp_indirect[]	= "[ebp]";
u8 	_esp_indirect[]	= "[esp]";

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
