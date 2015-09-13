//////////
//
// /libsf/exodus/tools/lasm/lasm_globals.h
//
//////
//    _     _ _     _____ _____
//   | |   (_) |__ / ____|  ___|
//   | |   | | '_ \\___ \|  __|
//   | |___| | |_) |___) | |
//   |_____|_|_.__/_____/|_|
//
//   Liberty Software Foundation
// and the Village Freedom Project
//   __     _______     ____
//   \ \   / /  ___| __|  _ \
//    \ \ / /| |_ | '__| |_) |
//     \ V / |  _|| |  |  __/
//      \_/  |_|  |_|  |_|
//
//////
// Version 0.01
// Copyright (c) 2015 by Rick C. Hodgin
//////
// Last update:
//     Sep.12.2015
//////
// Change log:
//     Sep.12.2015 - Initial creation
//////
//
// This document is released as Liberty Software under a Repeat License, as governed
// by the Public Benefit License v1.0 or later (PBL).
//
// The PBL is a public domain license with a caveat:  self accountability unto God.
// You are free to use, copy, modify and share this software for any purpose, however,
// it is the desire of those working on this project that the software remain open.
// It is our request that you maintain it that way.  This is not a legal request unto
// our court systems, but rather a personal matter between you and God.  Our talents
// were received from God, and given to you through this forum.  And it is our wish
// that those talents reach out to as many as possible in a form allowing them to wield
// this content for their own betterment, as you are now considering doing.  And whereas
// we could've forced the issue through something like a copyleft-protected release, the
// truth is we are all giving an account of our lives unto God continually by the daily
// choices we make.  And here again is another case where you get to demonstrate your
// character unto God, and unto your fellow man.
//
// Jesus came to this Earth to set the captives free, to save men's eternal souls from
// the punishment demanded by our sin.  Each one of us is given the opportunity to
// receive Him in this world and be saved.  Whether we choose to receive Him, and follow
// Him, and purpose our lives on the goals He has for each of us (all of which are
// beneficial for all involved), is one way we reveal our character continually.  God
// sees straight through to the heart, bypassing all of the words, all of the facades.
// He is our Creator, and He knows who we are truly.
//
// Jesus is called "Christ" because He saves men from the eternal flames of Hell, the
// just punishment of rebellion against God (rebellion against truth) by eternal beings,
// which each of us are.
//
// Do not let His free gift escape you because of some desire to shortcut what is right
// in your life. Instead, do what is right, and do it because He is who He is, and what
// He has done to save us from such a fate.  Demonstrate to Him, to me, and to all of
// mankind, and to all of the Heavenly hosts, exactly who you are on the inside.  Receive
// Jesus Christ into your heart, learn of Him, of how He came here to guide us into that
// which is of His Kingdom and will be forever hereafter we leave this world.  Do this,
// and live.
//
// Every project released by Liberty Software Foundation will include a copy of the
// pbl.txt document, which can be found at http://www.libsf.org/licenses/.
//
// For additional information about this project, or to view the license, see:
//
//     http://www.libsf.org/
//     http://www.libsf.org/licenses/
//     http://www.visual-freepro.org/vjr/indexmain.html
//     http://www.visual-freepro.org/wiki/index.php/PBL
//
// Thank you.  And may The Lord bless you richly as you lift up your life, your
// talents, your gifts, your praise, unto Him.  In Jesus' name I pray.  Amen.
//
//




u8		cgc_tbyte[]				= "tbyte";
u8		cgc_dqword[]			= "dqword";
u8		cgc_qword[]				= "qword";
u8		cgc_dword[]				= "dword";
u8		cgc_word[]				= "word";
u8		cgc_byte[]				= "byte";
u8		cgc_m16_16[]			= "m16_16";
u8		cgc_m16_32[]			= "m16_32";
//u8	cgc_f32[]				= "f32";
//u8	cgc_f64[]				= "f64";
u8		cgc_f80[]				= "f80";
//u8	cgc_s16[]				= "s16";
//u8	cgc_s32[]				= "s32";
//u8	cgc_s64[]				= "s64";
u8		cgc_m80[]				= "m80";
u8		cgc_mmx[]				= "mmx";
u8		cgc_xmmx[]				= "xmmx";
u8		cgc_fpu[]				= "fpu";

u8		cgc_6byte[]				= "m6byte";
u8		cgc_10byte[]			= "m10byte";
u8		cgc_14byte[]			= "m14byte";
u8		cgc_28byte[]			= "m28byte";
u8		cgc_94byte[]			= "m94byte";
u8		cgc_108byte[]			= "m108byte";

// Black
SBgra	colorDefault			= { rgba(0, 0, 0, 255) };





//////////
// Assembly opcodes
//////
	SAsciiCompSearcher	cgcKeywordsLasm[] =
	{
		// 																														first								syntax highlight	syntax highlight
		// keyword								length									repeats?	extra (type)						on line?	category				color				bold			onFind()	compilerDictionaryLookup()
		{ (cs8*)cgc_add_instruction,			sizeof(cgc_add_instruction) - 1,		false,		_ICODE__ADD_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_adc_instruction,			sizeof(cgc_adc_instruction) - 1,		false,		_ICODE__ADC_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_and_instruction,			sizeof(cgc_and_instruction) - 1,		false,		_ICODE__AND_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_sub_instruction,			sizeof(cgc_sub_instruction) - 1,		false,		_ICODE__SUB_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_sbb_instruction,			sizeof(cgc_sbb_instruction) - 1,		false,		_ICODE__SBB_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_xor_instruction,			sizeof(cgc_xor_instruction) - 1,		false,		_ICODE__XOR_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_cmp_instruction,			sizeof(cgc_cmp_instruction) - 1,		false,		_ICODE__CMP_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_bswap_instruction,			sizeof(cgc_bswap_instruction) - 1,		false,		_ICODE__BSWAP_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_aaa_instruction,			sizeof(cgc_aaa_instruction) - 1,		false,		_ICODE__AAA_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_aad_instruction,			sizeof(cgc_aad_instruction) - 1,		false,		_ICODE__AAD_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_aam_instruction,			sizeof(cgc_aam_instruction) - 1,		false,		_ICODE__AAM_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_aas_instruction,			sizeof(cgc_aas_instruction) - 1,		false,		_ICODE__AAS_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_cbw_instruction,			sizeof(cgc_cbw_instruction) - 1,		false,		_ICODE__CBW_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_clc_instruction,			sizeof(cgc_clc_instruction) - 1,		false,		_ICODE__CLC_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_cld_instruction,			sizeof(cgc_cld_instruction) - 1,		false,		_ICODE__CLD_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_cli_instruction,			sizeof(cgc_cli_instruction) - 1,		false,		_ICODE__CLI_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_clts_instruction,			sizeof(cgc_clts_instruction) - 1,		false,		_ICODE__CLTS_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_cmc_instruction,			sizeof(cgc_cmc_instruction) - 1,		false,		_ICODE__CMC_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_cpuid_instruction,			sizeof(cgc_cpuid_instruction) - 1,		false,		_ICODE__CPUID_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_cwd_instruction,			sizeof(cgc_cwd_instruction) - 1,		false,		_ICODE__CWD_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_daa_instruction,			sizeof(cgc_daa_instruction) - 1,		false,		_ICODE__DAA_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_emms_instruction,			sizeof(cgc_emms_instruction) - 1,		false,		_ICODE__EMMS_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_das_instruction,			sizeof(cgc_das_instruction) - 1,		false,		_ICODE__DAS_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_hlt_instruction,			sizeof(cgc_hlt_instruction) - 1,		false,		_ICODE__HLT_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_insb_instruction,			sizeof(cgc_insb_instruction) - 1,		false,		_ICODE__INSB_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_insd_instruction,			sizeof(cgc_insd_instruction) - 1,		false,		_ICODE__INSD_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_insw_instruction,			sizeof(cgc_insw_instruction) - 1,		false,		_ICODE__INSW_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_int3_instruction,			sizeof(cgc_int3_instruction) - 1,		false,		_ICODE__INT3_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_int_instruction,			sizeof(cgc_int_instruction) - 1,		false,		_ICODE__INT_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_into_instruction,			sizeof(cgc_into_instruction) - 1,		false,		_ICODE__INTO_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_iret_instruction,			sizeof(cgc_iret_instruction) - 1,		false,		_ICODE__IRET_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_lahf_instruction,			sizeof(cgc_lahf_instruction) - 1,		false,		_ICODE__LAHF_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_leave_instruction,			sizeof(cgc_leave_instruction) - 1,		false,		_ICODE__LEAVE_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_nop_instruction,			sizeof(cgc_nop_instruction) - 1,		false,		_ICODE__NOP_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_outsb_instruction,			sizeof(cgc_outsb_instruction) - 1,		false,		_ICODE__OUTSB_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_outsd_instruction,			sizeof(cgc_outsd_instruction) - 1,		false,		_ICODE__OUTSD_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_outsw_instruction,			sizeof(cgc_outsw_instruction) - 1,		false,		_ICODE__OUTSW_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_pop_instruction,			sizeof(cgc_pop_instruction) - 1,		false,		_ICODE__POP_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_push_instruction,			sizeof(cgc_push_instruction) - 1,		false,		_ICODE__PUSH_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_popa_instruction,			sizeof(cgc_popa_instruction) - 1,		false,		_ICODE__POPA_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_popf_instruction,			sizeof(cgc_popf_instruction) - 1,		false,		_ICODE__POPF_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_pusha_instruction,			sizeof(cgc_pusha_instruction) - 1,		false,		_ICODE__PUSHA_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_pushf_instruction,			sizeof(cgc_pushf_instruction) - 1,		false,		_ICODE__PUSHF_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_popad_instruction,			sizeof(cgc_popad_instruction) - 1,		false,		_ICODE__POPAD_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_popfd_instruction,			sizeof(cgc_popfd_instruction) - 1,		false,		_ICODE__POPFD_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_pushad_instruction,			sizeof(cgc_pushad_instruction) - 1,		false,		_ICODE__PUSHAD_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_pushfd_instruction,			sizeof(cgc_pushfd_instruction) - 1,		false,		_ICODE__PUSHFD_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_retf_instruction,			sizeof(cgc_retf_instruction) - 1,		false,		_ICODE__RETF_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_retn_instruction,			sizeof(cgc_retn_instruction) - 1,		false,		_ICODE__RETN_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_sahf_instruction,			sizeof(cgc_sahf_instruction) - 1,		false,		_ICODE__SAHF_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_seta_instruction,			sizeof(cgc_seta_instruction) - 1,		false,		_ICODE__SETA_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_setc_instruction,			sizeof(cgc_setc_instruction) - 1,		false,		_ICODE__SETC_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_setg_instruction,			sizeof(cgc_setg_instruction) - 1,		false,		_ICODE__SETG_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_setl_instruction,			sizeof(cgc_setl_instruction) - 1,		false,		_ICODE__SETL_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_setna_instruction,			sizeof(cgc_setna_instruction) - 1,		false,		_ICODE__SETNA_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_setnc_instruction,			sizeof(cgc_setnc_instruction) - 1,		false,		_ICODE__SETNC_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_setng_instruction,			sizeof(cgc_setng_instruction) - 1,		false,		_ICODE__SETNG_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_setnl_instruction,			sizeof(cgc_setnl_instruction) - 1,		false,		_ICODE__SETNL_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_setno_instruction,			sizeof(cgc_setno_instruction) - 1,		false,		_ICODE__SETNO_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_setns_instruction,			sizeof(cgc_setns_instruction) - 1,		false,		_ICODE__SETNS_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_setnz_instruction,			sizeof(cgc_setnz_instruction) - 1,		false,		_ICODE__SETNZ_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_seto_instruction,			sizeof(cgc_seto_instruction) - 1,		false,		_ICODE__SETO_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_setpe_instruction,			sizeof(cgc_setpe_instruction) - 1,		false,		_ICODE__SETPE_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_setpo_instruction,			sizeof(cgc_setpo_instruction) - 1,		false,		_ICODE__SETPO_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_sets_instruction,			sizeof(cgc_sets_instruction) - 1,		false,		_ICODE__SETS_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_setz_instruction,			sizeof(cgc_setz_instruction) - 1,		false,		_ICODE__SETZ_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_stc_instruction,			sizeof(cgc_stc_instruction) - 1,		false,		_ICODE__STC_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_std_instruction,			sizeof(cgc_std_instruction) - 1,		false,		_ICODE__STD_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_sti_instruction,			sizeof(cgc_sti_instruction) - 1,		false,		_ICODE__STI_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_wait_instruction,			sizeof(cgc_wait_instruction) - 1,		false,		_ICODE__WAIT_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_xlat_instruction,			sizeof(cgc_xlat_instruction) - 1,		false,		_ICODE__XLAT_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_repe_instruction,			sizeof(cgc_repe_instruction) - 1,		false,		_ICODE__REPE_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_repne_instruction,			sizeof(cgc_repne_instruction) - 1,		false,		_ICODE__REPNE_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_cmpsw_instruction,			sizeof(cgc_cmpsw_instruction) - 1,		false,		_ICODE__CMPSW_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_cmpsd_instruction,			sizeof(cgc_cmpsd_instruction) - 1,		false,		_ICODE__CMPSD_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_lodsw_instruction,			sizeof(cgc_lodsw_instruction) - 1,		false,		_ICODE__LODSW_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_lodsd_instruction,			sizeof(cgc_lodsd_instruction) - 1,		false,		_ICODE__LODSD_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_movsw_instruction,			sizeof(cgc_movsw_instruction) - 1,		false,		_ICODE__MOVSW_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_movsd_instruction,			sizeof(cgc_movsd_instruction) - 1,		false,		_ICODE__MOVSD_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_scasw_instruction,			sizeof(cgc_scasw_instruction) - 1,		false,		_ICODE__SCASW_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_scasd_instruction,			sizeof(cgc_scasd_instruction) - 1,		false,		_ICODE__SCASD_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_stosw_instruction,			sizeof(cgc_stosw_instruction) - 1,		false,		_ICODE__STOSW_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_stosd_instruction,			sizeof(cgc_stosd_instruction) - 1,		false,		_ICODE__STOSD_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_arpl_instruction,			sizeof(cgc_arpl_instruction) - 1,		false,		_ICODE__ARPL_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_bound_instruction,			sizeof(cgc_bound_instruction) - 1,		false,		_ICODE__BOUND_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_bsf_instruction,			sizeof(cgc_bsf_instruction) - 1,		false,		_ICODE__BSF_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_bsr_instruction,			sizeof(cgc_bsr_instruction) - 1,		false,		_ICODE__BSR_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_bt_instruction,				sizeof(cgc_bt_instruction) - 1,			false,		_ICODE__BT_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_btc_instruction,			sizeof(cgc_btc_instruction) - 1,		false,		_ICODE__BTC_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_btr_instruction,			sizeof(cgc_btr_instruction) - 1,		false,		_ICODE__BTR_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_bts_instruction,			sizeof(cgc_bts_instruction) - 1,		false,		_ICODE__BTS_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_call_instruction,			sizeof(cgc_call_instruction) - 1,		false,		_ICODE__CALL_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_cmova_instruction,			sizeof(cgc_cmova_instruction) - 1,		false,		_ICODE__CMOVA_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_cmovc_instruction,			sizeof(cgc_cmovc_instruction) - 1,		false,		_ICODE__CMOVC_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_cmovg_instruction,			sizeof(cgc_cmovg_instruction) - 1,		false,		_ICODE__CMOVG_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_cmovl_instruction,			sizeof(cgc_cmovl_instruction) - 1,		false,		_ICODE__CMOVL_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_cmovna_instruction,			sizeof(cgc_cmovna_instruction) - 1,		false,		_ICODE__CMOVNA_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_cmovnc_instruction,			sizeof(cgc_cmovnc_instruction) - 1,		false,		_ICODE__CMOVNC_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_cmovng_instruction,			sizeof(cgc_cmovng_instruction) - 1,		false,		_ICODE__CMOVNG_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_cmovnl_instruction,			sizeof(cgc_cmovnl_instruction) - 1,		false,		_ICODE__CMOVNL_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_cmovno_instruction,			sizeof(cgc_cmovno_instruction) - 1,		false,		_ICODE__CMOVNO_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_cmovns_instruction,			sizeof(cgc_cmovns_instruction) - 1,		false,		_ICODE__CMOVNS_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_cmovnz_instruction,			sizeof(cgc_cmovnz_instruction) - 1,		false,		_ICODE__CMOVNZ_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_cmovo_instruction,			sizeof(cgc_cmovo_instruction) - 1,		false,		_ICODE__CMOVO_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_cmovpe_instruction,			sizeof(cgc_cmovpe_instruction) - 1,		false,		_ICODE__CMOVPE_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_cmovpo_instruction,			sizeof(cgc_cmovpo_instruction) - 1,		false,		_ICODE__CMOVPO_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_cmovs_instruction,			sizeof(cgc_cmovs_instruction) - 1,		false,		_ICODE__CMOVS_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_cmovz_instruction,			sizeof(cgc_cmovz_instruction) - 1,		false,		_ICODE__CMOVZ_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_cmpxchg_instruction,		sizeof(cgc_cmpxchg_instruction) - 1,	false,		_ICODE__CMPXCHG_INSTRUCTION,		true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_dec_instruction,			sizeof(cgc_dec_instruction) - 1,		false,		_ICODE__DEC_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_inc_instruction,			sizeof(cgc_inc_instruction) - 1,		false,		_ICODE__INC_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_imul_instruction,			sizeof(cgc_imul_instruction) - 1,		false,		_ICODE__IMUL_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_icebp_instruction,			sizeof(cgc_icebp_instruction) - 1,		false,		_ICODE__ICEBP_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_sldt_instruction,			sizeof(cgc_sldt_instruction) - 1,		false,		_ICODE__SLDT_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_lldt_instruction,			sizeof(cgc_lldt_instruction) - 1,		false,		_ICODE__LLDT_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_str_instruction,			sizeof(cgc_str_instruction) - 1,		false,		_ICODE__STR_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_verr_instruction,			sizeof(cgc_verr_instruction) - 1,		false,		_ICODE__VERR_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_verw_instruction,			sizeof(cgc_verw_instruction) - 1,		false,		_ICODE__VERW_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_ltr_instruction,			sizeof(cgc_ltr_instruction) - 1,		false,		_ICODE__LTR_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_unk_instruction,			sizeof(cgc_unk_instruction) - 1,		false,		_ICODE__UNK_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_sgdt_instruction,			sizeof(cgc_sgdt_instruction) - 1,		false,		_ICODE__SGDT_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_sidt_instruction,			sizeof(cgc_sidt_instruction) - 1,		false,		_ICODE__SIDT_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_lgdt_instruction,			sizeof(cgc_lgdt_instruction) - 1,		false,		_ICODE__LGDT_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_lidt_instruction,			sizeof(cgc_lidt_instruction) - 1,		false,		_ICODE__LIDT_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_lmsw_instruction,			sizeof(cgc_lmsw_instruction) - 1,		false,		_ICODE__LMSW_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_smsw_instruction,			sizeof(cgc_smsw_instruction) - 1,		false,		_ICODE__SMSW_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_invlpg_instruction,			sizeof(cgc_invlpg_instruction) - 1,		false,		_ICODE__INVLPG_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_psraw_instruction,			sizeof(cgc_psraw_instruction) - 1,		false,		_ICODE__PSRAW_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_psrad_instruction,			sizeof(cgc_psrad_instruction) - 1,		false,		_ICODE__PSRAD_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_psrld_instruction,			sizeof(cgc_psrld_instruction) - 1,		false,		_ICODE__PSRLD_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_psrlw_instruction,			sizeof(cgc_psrlw_instruction) - 1,		false,		_ICODE__PSRLW_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_psrlq_instruction,			sizeof(cgc_psrlq_instruction) - 1,		false,		_ICODE__PSRLQ_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_psubb_instruction,			sizeof(cgc_psubb_instruction) - 1,		false,		_ICODE__PSUBB_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_psubw_instruction,			sizeof(cgc_psubw_instruction) - 1,		false,		_ICODE__PSUBW_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_psubd_instruction,			sizeof(cgc_psubd_instruction) - 1,		false,		_ICODE__PSUBD_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_psubsb_instruction,			sizeof(cgc_psubsb_instruction) - 1,		false,		_ICODE__PSUBSB_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_psubsw_instruction,			sizeof(cgc_psubsw_instruction) - 1,		false,		_ICODE__PSUBSW_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_psubusb_instruction,		sizeof(cgc_psubusb_instruction) - 1,	false,		_ICODE__PSUBUSB_INSTRUCTION,		true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_psubusw_instruction,		sizeof(cgc_psubusw_instruction) - 1,	false,		_ICODE__PSUBUSW_INSTRUCTION,		true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_punpckhbw_instruction,		sizeof(cgc_punpckhbw_instruction) - 1,	false,		_ICODE__PUNPCKHBW_INSTRUCTION,		true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_punpckhwd_instruction,		sizeof(cgc_punpckhwd_instruction) - 1,	false,		_ICODE__PUNPCKHWD_INSTRUCTION,		true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_punpckhdq_instruction,		sizeof(cgc_punpckhdq_instruction) - 1,	false,		_ICODE__PUNPCKHDQ_INSTRUCTION,		true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_punpcklbw_instruction,		sizeof(cgc_punpcklbw_instruction) - 1,	false,		_ICODE__PUNPCKLBW_INSTRUCTION,		true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_punpcklwd_instruction,		sizeof(cgc_punpcklwd_instruction) - 1,	false,		_ICODE__PUNPCKLWD_INSTRUCTION,		true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_punpckldq_instruction,		sizeof(cgc_punpckldq_instruction) - 1,	false,		_ICODE__PUNPCKLDQ_INSTRUCTION,		true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_pxor_instruction,			sizeof(cgc_pxor_instruction) - 1,		false,		_ICODE__PXOR_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_rsm_instruction,			sizeof(cgc_rsm_instruction) - 1,		false,		_ICODE__RSM_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_shld_instruction,			sizeof(cgc_shld_instruction) - 1,		false,		_ICODE__SHLD_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_shrd_instruction,			sizeof(cgc_shrd_instruction) - 1,		false,		_ICODE__SHRD_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_test_instruction,			sizeof(cgc_test_instruction) - 1,		false,		_ICODE__TEST_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_xchg_instruction,			sizeof(cgc_xchg_instruction) - 1,		false,		_ICODE__XCHG_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_ud2_instruction,			sizeof(cgc_ud2_instruction) - 1,		false,		_ICODE__UD2_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_wrmsr_instruction,			sizeof(cgc_wrmsr_instruction) - 1,		false,		_ICODE__WRMSR_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_wbinvd_instruction,			sizeof(cgc_wbinvd_instruction) - 1,		false,		_ICODE__WBINVD_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_xadd_instruction,			sizeof(cgc_xadd_instruction) - 1,		false,		_ICODE__XADD_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_packssdw_instruction,		sizeof(cgc_packssdw_instruction) - 1,	false,		_ICODE__PACKSSDW_INSTRUCTION,		true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_packsswb_instruction,		sizeof(cgc_packsswb_instruction) - 1,	false,		_ICODE__PACKSSWB_INSTRUCTION,		true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_packuswb_instruction,		sizeof(cgc_packuswb_instruction) - 1,	false,		_ICODE__PACKUSWB_INSTRUCTION,		true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_paddb_instruction,			sizeof(cgc_paddb_instruction) - 1,		false,		_ICODE__PADDB_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_paddd_instruction,			sizeof(cgc_paddd_instruction) - 1,		false,		_ICODE__PADDD_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_paddsb_instruction,			sizeof(cgc_paddsb_instruction) - 1,		false,		_ICODE__PADDSB_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_paddsw_instruction,			sizeof(cgc_paddsw_instruction) - 1,		false,		_ICODE__PADDSW_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_paddusb_instruction,		sizeof(cgc_paddusb_instruction) - 1,	false,		_ICODE__PADDUSB_INSTRUCTION,		true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_paddusw_instruction,		sizeof(cgc_paddusw_instruction) - 1,	false,		_ICODE__PADDUSW_INSTRUCTION,		true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_paddw_instruction,			sizeof(cgc_paddw_instruction) - 1,		false,		_ICODE__PADDW_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_pand_instruction,			sizeof(cgc_pand_instruction) - 1,		false,		_ICODE__PAND_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_pandn_instruction,			sizeof(cgc_pandn_instruction) - 1,		false,		_ICODE__PANDN_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_pcmpeqb_instruction,		sizeof(cgc_pcmpeqb_instruction) - 1,	false,		_ICODE__PCMPEQB_INSTRUCTION,		true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_pcmpeqd_instruction,		sizeof(cgc_pcmpeqd_instruction) - 1,	false,		_ICODE__PCMPEQD_INSTRUCTION,		true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_pcmpeqw_instruction,		sizeof(cgc_pcmpeqw_instruction) - 1,	false,		_ICODE__PCMPEQW_INSTRUCTION,		true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_pcmpgtb_instruction,		sizeof(cgc_pcmpgtb_instruction) - 1,	false,		_ICODE__PCMPGTB_INSTRUCTION,		true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_pcmpgtd_instruction,		sizeof(cgc_pcmpgtd_instruction) - 1,	false,		_ICODE__PCMPGTD_INSTRUCTION,		true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_pcmpgtw_instruction,		sizeof(cgc_pcmpgtw_instruction) - 1,	false,		_ICODE__PCMPGTW_INSTRUCTION,		true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_pmaddwd_instruction,		sizeof(cgc_pmaddwd_instruction) - 1,	false,		_ICODE__PMADDWD_INSTRUCTION,		true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_pmulhw_instruction,			sizeof(cgc_pmulhw_instruction) - 1,		false,		_ICODE__PMULHW_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_pmullw_instruction,			sizeof(cgc_pmullw_instruction) - 1,		false,		_ICODE__PMULLW_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_por_instruction,			sizeof(cgc_por_instruction) - 1,		false,		_ICODE__POR_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_pslld_instruction,			sizeof(cgc_pslld_instruction) - 1,		false,		_ICODE__PSLLD_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_psllq_instruction,			sizeof(cgc_psllq_instruction) - 1,		false,		_ICODE__PSLLQ_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_psllw_instruction,			sizeof(cgc_psllw_instruction) - 1,		false,		_ICODE__PSLLW_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_or_instruction,				sizeof(cgc_or_instruction) - 1,			false,		_ICODE__OR_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_hcf_instruction,			sizeof(cgc_hcf_instruction) - 1,		false,		_ICODE__HCF_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_cmpxchg8b_instruction,		sizeof(cgc_cmpxchg8b_instruction) - 1,	false,		_ICODE__CMPXCHG8B_INSTRUCTION,		true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_in_instruction,				sizeof(cgc_in_instruction) - 1,			false,		_ICODE__IN_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_rdmsr_instruction,			sizeof(cgc_rdmsr_instruction) - 1,		false,		_ICODE__RDMSR_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_rdpmc_instruction,			sizeof(cgc_rdpmc_instruction) - 1,		false,		_ICODE__RDPMC_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_rdtsc_instruction,			sizeof(cgc_rdtsc_instruction) - 1,		false,		_ICODE__RDTSC_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_movsx_instruction,			sizeof(cgc_movsx_instruction) - 1,		false,		_ICODE__MOVSX_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_movzx_instruction,			sizeof(cgc_movzx_instruction) - 1,		false,		_ICODE__MOVZX_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_lsl_instruction,			sizeof(cgc_lsl_instruction) - 1,		false,		_ICODE__LSL_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_lss_instruction,			sizeof(cgc_lss_instruction) - 1,		false,		_ICODE__LSS_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_loopne_instruction,			sizeof(cgc_loopne_instruction) - 1,		false,		_ICODE__LOOPNE_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_loope_instruction,			sizeof(cgc_loope_instruction) - 1,		false,		_ICODE__LOOPE_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_loop_instruction,			sizeof(cgc_loop_instruction) - 1,		false,		_ICODE__LOOP_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_lgs_instruction,			sizeof(cgc_lgs_instruction) - 1,		false,		_ICODE__LGS_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_lfs_instruction,			sizeof(cgc_lfs_instruction) - 1,		false,		_ICODE__LFS_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_les_instruction,			sizeof(cgc_les_instruction) - 1,		false,		_ICODE__LES_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_lea_instruction,			sizeof(cgc_lea_instruction) - 1,		false,		_ICODE__LEA_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_lds_instruction,			sizeof(cgc_lds_instruction) - 1,		false,		_ICODE__LDS_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_lar_instruction,			sizeof(cgc_lar_instruction) - 1,		false,		_ICODE__LAR_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_jz_instruction,				sizeof(cgc_jz_instruction) - 1,			false,		_ICODE__JZ_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_js_instruction,				sizeof(cgc_js_instruction) - 1,			false,		_ICODE__JS_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_jpo_instruction,			sizeof(cgc_jpo_instruction) - 1,		false,		_ICODE__JPO_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_jpe_instruction,			sizeof(cgc_jpe_instruction) - 1,		false,		_ICODE__JPE_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_jo_instruction,				sizeof(cgc_jo_instruction) - 1,			false,		_ICODE__JO_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_jnz_instruction,			sizeof(cgc_jnz_instruction) - 1,		false,		_ICODE__JNZ_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_jno_instruction,			sizeof(cgc_jno_instruction) - 1,		false,		_ICODE__JNO_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_jnl_instruction,			sizeof(cgc_jnl_instruction) - 1,		false,		_ICODE__JNL_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_jng_instruction,			sizeof(cgc_jng_instruction) - 1,		false,		_ICODE__JNG_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_jnc_instruction,			sizeof(cgc_jnc_instruction) - 1,		false,		_ICODE__JNC_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_jna_instruction,			sizeof(cgc_jna_instruction) - 1,		false,		_ICODE__JNA_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_jmp_instruction,			sizeof(cgc_jmp_instruction) - 1,		false,		_ICODE__JMP_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_jl_instruction,				sizeof(cgc_jl_instruction) - 1,			false,		_ICODE__JL_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_jg_instruction,				sizeof(cgc_jg_instruction) - 1,			false,		_ICODE__JG_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_jcxz_instruction,			sizeof(cgc_jcxz_instruction) - 1,		false,		_ICODE__JCXZ_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_jecxz_instruction,			sizeof(cgc_jecxz_instruction) - 1,		false,		_ICODE__JECXZ_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_jc_instruction,				sizeof(cgc_jc_instruction) - 1,			false,		_ICODE__JC_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_ja_instruction,				sizeof(cgc_ja_instruction) - 1,			false,		_ICODE__JA_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_jns_instruction,			sizeof(cgc_jns_instruction) - 1,		false,		_ICODE__JNS_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_invd_instruction,			sizeof(cgc_invd_instruction) - 1,		false,		_ICODE__INVD_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_idiv_instruction,			sizeof(cgc_idiv_instruction) - 1,		false,		_ICODE__IDIV_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_div_instruction,			sizeof(cgc_div_instruction) - 1,		false,		_ICODE__DIV_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_neg_instruction,			sizeof(cgc_neg_instruction) - 1,		false,		_ICODE__NEG_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_mul_instruction,			sizeof(cgc_mul_instruction) - 1,		false,		_ICODE__MUL_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_not_instruction,			sizeof(cgc_not_instruction) - 1,		false,		_ICODE__NOT_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_sar_instruction,			sizeof(cgc_sar_instruction) - 1,		false,		_ICODE__SAR_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_shr_instruction,			sizeof(cgc_shr_instruction) - 1,		false,		_ICODE__SHR_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_shl_instruction,			sizeof(cgc_shl_instruction) - 1,		false,		_ICODE__SHL_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_rcr_instruction,			sizeof(cgc_rcr_instruction) - 1,		false,		_ICODE__RCR_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_rcl_instruction,			sizeof(cgc_rcl_instruction) - 1,		false,		_ICODE__RCL_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_ror_instruction,			sizeof(cgc_ror_instruction) - 1,		false,		_ICODE__ROR_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_rol_instruction,			sizeof(cgc_rol_instruction) - 1,		false,		_ICODE__ROL_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_mov_instruction,			sizeof(cgc_mov_instruction) - 1,		false,		_ICODE__MOV_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_fnop_instruction,			sizeof(cgc_fnop_instruction) - 1,		false,		_ICODE__FNOP_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_fchs_instruction,			sizeof(cgc_fchs_instruction) - 1,		false,		_ICODE__FCHS_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_fabs_instruction,			sizeof(cgc_fabs_instruction) - 1,		false,		_ICODE__FABS_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_ftst_instruction,			sizeof(cgc_ftst_instruction) - 1,		false,		_ICODE__FTST_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_fxam_instruction,			sizeof(cgc_fxam_instruction) - 1,		false,		_ICODE__FXAM_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_fld1_instruction,			sizeof(cgc_fld1_instruction) - 1,		false,		_ICODE__FLD1_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_fld2t_instruction,			sizeof(cgc_fld2t_instruction) - 1,		false,		_ICODE__FLD2T_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_fld2e_instruction,			sizeof(cgc_fld2e_instruction) - 1,		false,		_ICODE__FLD2E_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_fldpi_instruction,			sizeof(cgc_fldpi_instruction) - 1,		false,		_ICODE__FLDPI_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_fldlg2_instruction,			sizeof(cgc_fldlg2_instruction) - 1,		false,		_ICODE__FLDLG2_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_fldln2_instruction,			sizeof(cgc_fldln2_instruction) - 1,		false,		_ICODE__FLDLN2_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_fldz_instruction,			sizeof(cgc_fldz_instruction) - 1,		false,		_ICODE__FLDZ_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_f2xm1_instruction,			sizeof(cgc_f2xm1_instruction) - 1,		false,		_ICODE__F2XM1_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_fyl2x_instruction,			sizeof(cgc_fyl2x_instruction) - 1,		false,		_ICODE__FYL2X_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_fptan_instruction,			sizeof(cgc_fptan_instruction) - 1,		false,		_ICODE__FPTAN_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_fpatan_instruction,			sizeof(cgc_fpatan_instruction) - 1,		false,		_ICODE__FPATAN_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_fxtract_instruction,		sizeof(cgc_fxtract_instruction) - 1,	false,		_ICODE__FXTRACT_INSTRUCTION,		true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_fprem1_instruction,			sizeof(cgc_fprem1_instruction) - 1,		false,		_ICODE__FPREM1_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_fdecstp_instruction,		sizeof(cgc_fdecstp_instruction) - 1,	false,		_ICODE__FDECSTP_INSTRUCTION,		true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_fincstp_instruction,		sizeof(cgc_fincstp_instruction) - 1,	false,		_ICODE__FINCSTP_INSTRUCTION,		true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_fprem_instruction,			sizeof(cgc_fprem_instruction) - 1,		false,		_ICODE__FPREM_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_fyl2xp1_instruction,		sizeof(cgc_fyl2xp1_instruction) - 1,	false,		_ICODE__FYL2XP1_INSTRUCTION,		true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_fsqrt_instruction,			sizeof(cgc_fsqrt_instruction) - 1,		false,		_ICODE__FSQRT_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_fsincos_instruction,		sizeof(cgc_fsincos_instruction) - 1,	false,		_ICODE__FSINCOS_INSTRUCTION,		true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_frndint_instruction,		sizeof(cgc_frndint_instruction) - 1,	false,		_ICODE__FRNDINT_INSTRUCTION,		true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_fscale_instruction,			sizeof(cgc_fscale_instruction) - 1,		false,		_ICODE__FSCALE_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_fsin_instruction,			sizeof(cgc_fsin_instruction) - 1,		false,		_ICODE__FSIN_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_fcos_instruction,			sizeof(cgc_fcos_instruction) - 1,		false,		_ICODE__FCOS_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_fadd_instruction,			sizeof(cgc_fadd_instruction) - 1,		false,		_ICODE__FADD_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_fmul_instruction,			sizeof(cgc_fmul_instruction) - 1,		false,		_ICODE__FMUL_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_fcom_instruction,			sizeof(cgc_fcom_instruction) - 1,		false,		_ICODE__FCOM_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_fcomp_instruction,			sizeof(cgc_fcomp_instruction) - 1,		false,		_ICODE__FCOMP_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_fsub_instruction,			sizeof(cgc_fsub_instruction) - 1,		false,		_ICODE__FSUB_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_fsubr_instruction,			sizeof(cgc_fsubr_instruction) - 1,		false,		_ICODE__FSUBR_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_fdiv_instruction,			sizeof(cgc_fdiv_instruction) - 1,		false,		_ICODE__FDIV_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_fdivr_instruction,			sizeof(cgc_fdivr_instruction) - 1,		false,		_ICODE__FDIVR_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_fld_instruction,			sizeof(cgc_fld_instruction) - 1,		false,		_ICODE__FLD_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_fst_instruction,			sizeof(cgc_fst_instruction) - 1,		false,		_ICODE__FST_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_fstp_instruction,			sizeof(cgc_fstp_instruction) - 1,		false,		_ICODE__FSTP_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_fiadd_instruction,			sizeof(cgc_fiadd_instruction) - 1,		false,		_ICODE__FIADD_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_fimul_instruction,			sizeof(cgc_fimul_instruction) - 1,		false,		_ICODE__FIMUL_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_ficom_instruction,			sizeof(cgc_ficom_instruction) - 1,		false,		_ICODE__FICOM_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_ficomp_instruction,			sizeof(cgc_ficomp_instruction) - 1,		false,		_ICODE__FICOMP_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_fisub_instruction,			sizeof(cgc_fisub_instruction) - 1,		false,		_ICODE__FISUB_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_fisubr_instruction,			sizeof(cgc_fisubr_instruction) - 1,		false,		_ICODE__FISUBR_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_fidiv_instruction,			sizeof(cgc_fidiv_instruction) - 1,		false,		_ICODE__FIDIV_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_fidivr_instruction,			sizeof(cgc_fidivr_instruction) - 1,		false,		_ICODE__FIDIVR_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_fist_instruction,			sizeof(cgc_fist_instruction) - 1,		false,		_ICODE__FIST_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_fistp_instruction,			sizeof(cgc_fistp_instruction) - 1,		false,		_ICODE__FISTP_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_fild_instruction,			sizeof(cgc_fild_instruction) - 1,		false,		_ICODE__FILD_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_fbld_instruction,			sizeof(cgc_fbld_instruction) - 1,		false,		_ICODE__FBLD_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_fbstp_instruction,			sizeof(cgc_fbstp_instruction) - 1,		false,		_ICODE__FBSTP_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_fxch_instruction,			sizeof(cgc_fxch_instruction) - 1,		false,		_ICODE__FXCH_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_fucomp_instruction,			sizeof(cgc_fucomp_instruction) - 1,		false,		_ICODE__FUCOMP_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_fucompp_instruction,		sizeof(cgc_fucompp_instruction) - 1,	false,		_ICODE__FUCOMPP_INSTRUCTION,		true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_fnclex_instruction,			sizeof(cgc_fnclex_instruction) - 1,		false,		_ICODE__FNCLEX_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_fninit_instruction,			sizeof(cgc_fninit_instruction) - 1,		false,		_ICODE__FNINIT_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_fnstsw_instruction,			sizeof(cgc_fnstsw_instruction) - 1,		false,		_ICODE__FNSTSW_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_fldcw_instruction,			sizeof(cgc_fldcw_instruction) - 1,		false,		_ICODE__FLDCW_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_fnstcw_instruction,			sizeof(cgc_fnstcw_instruction) - 1,		false,		_ICODE__FNSTCW_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_fldenv_instruction,			sizeof(cgc_fldenv_instruction) - 1,		false,		_ICODE__FLDENV_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_fnstenv_instruction,		sizeof(cgc_fnstenv_instruction) - 1,	false,		_ICODE__FNSTENV_INSTRUCTION,		true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_frstor_instruction,			sizeof(cgc_frstor_instruction) - 1,		false,		_ICODE__FRSTOR_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_fnsave_instruction,			sizeof(cgc_fnsave_instruction) - 1,		false,		_ICODE__FNSAVE_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},

		{ (cs8*)cgc_tbyte,						sizeof(cgc_tbyte) - 1,					false,		_ICODE_CGC_TBYTE,					true,		_ICAT_DATA_TYPE,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_dqword,						sizeof(cgc_dqword) - 1,					false,		_ICODE_CGC_DQWORD,					true,		_ICAT_DATA_TYPE,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_qword,						sizeof(cgc_qword) - 1,					false,		_ICODE_CGC_QWORD,					true,		_ICAT_DATA_TYPE,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_dword,						sizeof(cgc_dword) - 1,					false,		_ICODE_CGC_DWORD,					true,		_ICAT_DATA_TYPE,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_word,						sizeof(cgc_word) - 1,					false,		_ICODE_CGC_WORD,					true,		_ICAT_DATA_TYPE,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_byte,						sizeof(cgc_byte) - 1,					false,		_ICODE_CGC_BYTE,					true,		_ICAT_DATA_TYPE,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_m16_16,						sizeof(cgc_m16_16) - 1,					false,		_ICODE_CGC_M16_16,					true,		_ICAT_DATA_TYPE,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_m16_32,						sizeof(cgc_m16_32) - 1,					false,		_ICODE_CGC_M16_32,					true,		_ICAT_DATA_TYPE,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_f32,						sizeof(cgc_f32) - 1,					false,		_ICODE_CGC_F32,						true,		_ICAT_DATA_TYPE,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_f64,						sizeof(cgc_f64) - 1,					false,		_ICODE_CGC_F64,						true,		_ICAT_DATA_TYPE,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_f80,						sizeof(cgc_f80) - 1,					false,		_ICODE_CGC_F80,						true,		_ICAT_DATA_TYPE,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_s16,						sizeof(cgc_s16) - 1,					false,		_ICODE_CGC_S16,						true,		_ICAT_DATA_TYPE,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_s32,						sizeof(cgc_s32) - 1,					false,		_ICODE_CGC_S32,						true,		_ICAT_DATA_TYPE,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_s64,						sizeof(cgc_s64) - 1,					false,		_ICODE_CGC_S64,						true,		_ICAT_DATA_TYPE,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_m80,						sizeof(cgc_m80) - 1,					false,		_ICODE_CGC_M80,						true,		_ICAT_DATA_TYPE,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_mmx,						sizeof(cgc_mmx) - 1,					false,		_ICODE_CGC_MMX,						true,		_ICAT_DATA_TYPE,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_xmmx,						sizeof(cgc_xmmx) - 1,					false,		_ICODE_CGC_XMMX,					true,		_ICAT_DATA_TYPE,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_fpu,						sizeof(cgc_fpu) - 1,					false,		_ICODE_CGC_FPU,						true,		_ICAT_DATA_TYPE,		&colorDefault,		false,			null0,		null0	},

		{ (cs8*)cgc_6byte,						sizeof(cgc_6byte) - 1,					false,		_ICODE_CGC_6BYTE,					true,		_ICAT_DATA_TYPE,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_10byte,						sizeof(cgc_10byte) - 1,					false,		_ICODE_CGC_10BYTE,					true,		_ICAT_DATA_TYPE,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_14byte,						sizeof(cgc_14byte) - 1,					false,		_ICODE_CGC_14BYTE,					true,		_ICAT_DATA_TYPE,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_28byte,						sizeof(cgc_28byte) - 1,					false,		_ICODE_CGC_28BYTE,					true,		_ICAT_DATA_TYPE,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_94byte,						sizeof(cgc_94byte) - 1,					false,		_ICODE_CGC_94BYTE,					true,		_ICAT_DATA_TYPE,		&colorDefault,		false,			null0,		null0	},
		{ (cs8*)cgc_108byte,					sizeof(cgc_108byte) - 1,				false,		_ICODE_CGC_108BYTE,					true,		_ICAT_DATA_TYPE,		&colorDefault,		false,			null0,		null0	},

/*
		{ cgc_plus_string			= "+";
		{ cgc_minus_string			= "-";

		{ cgc_cs_reg				= "cs";
		{ cgc_ds_reg				= "ds";
		{ cgc_es_reg				= "es";
		{ cgc_fs_reg				= "fs";
		{ cgc_gs_reg				= "gs";
		{ cgc_ss_reg				= "ss";

		{ cgc_al_reg				= "al";
		{ cgc_bl_reg				= "bl";
		{ cgc_cl_reg				= "cl";
		{ cgc_dl_reg				= "dl";
		{ cgc_ah_reg				= "ah";
		{ cgc_bh_reg				= "bh";
		{ cgc_ch_reg				= "ch";
		{ cgc_dh_reg				= "dh";

		{ cgc_ax_reg				= "ax";
		{ cgc_bx_reg				= "bx";
		{ cgc_cx_reg				= "cx";
		{ cgc_dx_reg				= "dx";
		{ cgc_si_reg				= "si";
		{ cgc_di_reg				= "di";
		{ cgc_bp_reg				= "bp";
		{ cgc_sp_reg				= "sp";
		{ cgc_ip_reg				= "ip";

		{ cgc_eax_reg				= "eax";
		{ cgc_ebx_reg				= "ebx";
		{ cgc_ecx_reg				= "ecx";
		{ cgc_edx_reg				= "edx";
		{ cgc_esi_reg				= "esi";
		{ cgc_edi_reg				= "edi";
		{ cgc_ebp_reg				= "ebp";
		{ cgc_esp_reg				= "esp";
		{ cgc_eip_reg				= "eip";

		{ cgc_cr0_reg				= "cr0";
		{ cgc_cr1_reg				= "cr1";
		{ cgc_cr2_reg				= "cr2";
		{ cgc_cr3_reg				= "cr3";
		{ cgc_cr4_reg				= "cr4";
		{ cgc_cr5_reg				= "cr5";
		{ cgc_cr6_reg				= "cr6";
		{ cgc_cr7_reg				= "cr7";

		{ cgc_dr0_reg				= "dr0";
		{ cgc_dr1_reg				= "dr1";
		{ cgc_dr2_reg				= "dr2";
		{ cgc_dr3_reg				= "dr3";
		{ cgc_dr4_reg				= "dr4";
		{ cgc_dr5_reg				= "dr5";
		{ cgc_dr6_reg				= "dr6";
		{ cgc_dr7_reg				= "dr7";

		{ cgc_tr0_reg				= "tr0";
		{ cgc_tr1_reg				= "tr1";
		{ cgc_tr2_reg				= "tr2";
		{ cgc_tr3_reg				= "tr3";
		{ cgc_tr4_reg				= "tr4";
		{ cgc_tr5_reg				= "tr5";
		{ cgc_tr6_reg				= "tr6";
		{ cgc_tr7_reg				= "tr7";

		{ cgc_st0_reg				= "st0";
		{ cgc_st1_reg				= "st1";
		{ cgc_st2_reg				= "st2";
		{ cgc_st3_reg				= "st3";
		{ cgc_st4_reg				= "st4";
		{ cgc_st5_reg				= "st5";
		{ cgc_st6_reg				= "st6";
		{ cgc_st7_reg				= "st7";

		{ cgc_mm0_reg				= "mm0";
		{ cgc_mm1_reg				= "mm1";
		{ cgc_mm2_reg				= "mm2";
		{ cgc_mm3_reg				= "mm3";
		{ cgc_mm4_reg				= "mm4";
		{ cgc_mm5_reg				= "mm5";
		{ cgc_mm6_reg				= "mm6";
		{ cgc_mm7_reg				= "mm7";

		{ cgc_xmm0_reg				= "xmm0";
		{ cgc_xmm1_reg				= "xmm1";
		{ cgc_xmm2_reg				= "xmm2";
		{ cgc_xmm3_reg				= "xmm3";
		{ cgc_xmm4_reg				= "xmm4";
		{ cgc_xmm5_reg				= "xmm5";
		{ cgc_xmm6_reg				= "xmm6";
		{ cgc_xmm7_reg				= "xmm7";
*/

		{ 0,						0,			0,			0,										0,					0,					0,							0,							0,			0		}
	};
