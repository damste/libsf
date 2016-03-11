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




//////////
// Processing data
//////
	SLasmFile*		gsFirstFile							= NULL;					// First file that's being assembled
	SLasmDefine*	gsLasmDefines						= NULL;					// List of #defines found, in the order found
	SLasmBlock*		firstAdhoc							= NULL;					// All adhoc definitions are scoped within functions or flowofs, but are part of a single list
	SLasmBlock*		firstFunction						= NULL;					// All function definitions
	SLasmBlock*		firstFlowof							= NULL;					// All flowof definitions
	SLasmClass*		firstClass							= NULL;					// All class definitions
	SLasmStruct*	firstStruct							= NULL;					// All struct definitions
	SLasmEnum*		firstEnum							= NULL;					// All enum definitions


//////////
// Command line options
//////
	cs8			cgc_wno[]							= "-Wno-";
	cs8			cgc_wmissing_type_ptr[]				= "missing-type-ptr";
	cs8			cgc_wall[]							= "all";
	cs8			cgc_wfatal_errors[]					= "fatal-errors";
	cs8			cgc_werror[]						= "error";
	cs8			cgc_fsyntax_only[]					= "-fsyntax-only";


//////////
// Pointer types
//////
	u8			cgc_ptr_tbyte[]						= "tbyte";
	u8			cgc_ptr_dqword[]					= "dqword";
	u8			cgc_ptr_qword[]						= "qword";
	u8			cgc_ptr_dword[]						= "dword";
	u8			cgc_ptr_word[]						= "word";
	u8			cgc_ptr_byte[]						= "byte";
	u8			cgc_ptr_m16_16[]					= "m16_16";
	u8			cgc_ptr_m16_32[]					= "m16_32";
	u8			cgc_ptr_f32[]						= "f32";
	u8			cgc_ptr_f64[]						= "f64";
	u8			cgc_ptr_f80[]						= "f80";
	u8			cgc_ptr_s16[]						= "s16";
	u8			cgc_ptr_s32[]						= "s32";
	u8			cgc_ptr_s64[]						= "s64";
	u8			cgc_ptr_m80[]						= "m80";
	u8			cgc_ptr_mmx[]						= "mmx";
	u8			cgc_ptr_xmmx[]						= "xmmx";
	u8			cgc_ptr_fpu[]						= "fpu";
	u8			cgc_ptr_6byte[]						= "m6byte";
	u8			cgc_ptr_10byte[]					= "m10byte";
	u8			cgc_ptr_14byte[]					= "m14byte";
	u8			cgc_ptr_28byte[]					= "m28byte";
	u8			cgc_ptr_94byte[]					= "m94byte";
	u8			cgc_ptr_108byte[]					= "m108byte";

	u8			cgc_lasm_include[]					= "include";
	u8			cgc_lasm_define[]					= "define";
	u8			cgc_lasm_function[]					= "function";
	u8			cgc_lasm_struct[]					= "struct";




//////////
// Colors
//////
	SBgra		colorDefault						= { rgba(0, 0, 0, 255) };		// Black




//////////
// Assembly opcodes
//////
	SAsciiCompSearcher	cgcKeywordsLasm[] =
	{
		// 																																first								syntax highlight	syntax highlight
		//	keyword								length									repeats?	extra (type)						on line?	category				color				bold			onFind()	compilerDictionaryLookup()
		{	(cs8*)cgc_add_instruction,			sizeof(cgc_add_instruction) - 1,		false,		_ICODE_ADD_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_adc_instruction,			sizeof(cgc_adc_instruction) - 1,		false,		_ICODE_ADC_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_and_instruction,			sizeof(cgc_and_instruction) - 1,		false,		_ICODE_AND_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_sub_instruction,			sizeof(cgc_sub_instruction) - 1,		false,		_ICODE_SUB_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_sbb_instruction,			sizeof(cgc_sbb_instruction) - 1,		false,		_ICODE_SBB_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_xor_instruction,			sizeof(cgc_xor_instruction) - 1,		false,		_ICODE_XOR_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_cmp_instruction,			sizeof(cgc_cmp_instruction) - 1,		false,		_ICODE_CMP_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_bswap_instruction,		sizeof(cgc_bswap_instruction) - 1,		false,		_ICODE_BSWAP_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_aaa_instruction,			sizeof(cgc_aaa_instruction) - 1,		false,		_ICODE_AAA_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_aad_instruction,			sizeof(cgc_aad_instruction) - 1,		false,		_ICODE_AAD_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_aam_instruction,			sizeof(cgc_aam_instruction) - 1,		false,		_ICODE_AAM_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_aas_instruction,			sizeof(cgc_aas_instruction) - 1,		false,		_ICODE_AAS_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_cbw_instruction,			sizeof(cgc_cbw_instruction) - 1,		false,		_ICODE_CBW_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_clc_instruction,			sizeof(cgc_clc_instruction) - 1,		false,		_ICODE_CLC_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_cld_instruction,			sizeof(cgc_cld_instruction) - 1,		false,		_ICODE_CLD_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_cli_instruction,			sizeof(cgc_cli_instruction) - 1,		false,		_ICODE_CLI_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_clts_instruction,			sizeof(cgc_clts_instruction) - 1,		false,		_ICODE_CLTS_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_cmc_instruction,			sizeof(cgc_cmc_instruction) - 1,		false,		_ICODE_CMC_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_cpuid_instruction,		sizeof(cgc_cpuid_instruction) - 1,		false,		_ICODE_CPUID_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_cwd_instruction,			sizeof(cgc_cwd_instruction) - 1,		false,		_ICODE_CWD_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_daa_instruction,			sizeof(cgc_daa_instruction) - 1,		false,		_ICODE_DAA_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_emms_instruction,			sizeof(cgc_emms_instruction) - 1,		false,		_ICODE_EMMS_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_das_instruction,			sizeof(cgc_das_instruction) - 1,		false,		_ICODE_DAS_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_hlt_instruction,			sizeof(cgc_hlt_instruction) - 1,		false,		_ICODE_HLT_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_insb_instruction,			sizeof(cgc_insb_instruction) - 1,		false,		_ICODE_INSB_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_insd_instruction,			sizeof(cgc_insd_instruction) - 1,		false,		_ICODE_INSD_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_insw_instruction,			sizeof(cgc_insw_instruction) - 1,		false,		_ICODE_INSW_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_int3_instruction,			sizeof(cgc_int3_instruction) - 1,		false,		_ICODE_INT3_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_int_instruction,			sizeof(cgc_int_instruction) - 1,		false,		_ICODE_INT_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_into_instruction,			sizeof(cgc_into_instruction) - 1,		false,		_ICODE_INTO_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_iret_instruction,			sizeof(cgc_iret_instruction) - 1,		false,		_ICODE_IRET_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_lahf_instruction,			sizeof(cgc_lahf_instruction) - 1,		false,		_ICODE_LAHF_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_leave_instruction,		sizeof(cgc_leave_instruction) - 1,		false,		_ICODE_LEAVE_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_nop_instruction,			sizeof(cgc_nop_instruction) - 1,		false,		_ICODE_NOP_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_outsb_instruction,		sizeof(cgc_outsb_instruction) - 1,		false,		_ICODE_OUTSB_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_outsd_instruction,		sizeof(cgc_outsd_instruction) - 1,		false,		_ICODE_OUTSD_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_outsw_instruction,		sizeof(cgc_outsw_instruction) - 1,		false,		_ICODE_OUTSW_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_pop_instruction,			sizeof(cgc_pop_instruction) - 1,		false,		_ICODE_POP_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_push_instruction,			sizeof(cgc_push_instruction) - 1,		false,		_ICODE_PUSH_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_popa_instruction,			sizeof(cgc_popa_instruction) - 1,		false,		_ICODE_POPA_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_popf_instruction,			sizeof(cgc_popf_instruction) - 1,		false,		_ICODE_POPF_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_pusha_instruction,		sizeof(cgc_pusha_instruction) - 1,		false,		_ICODE_PUSHA_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_pushf_instruction,		sizeof(cgc_pushf_instruction) - 1,		false,		_ICODE_PUSHF_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_popad_instruction,		sizeof(cgc_popad_instruction) - 1,		false,		_ICODE_POPAD_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_popfd_instruction,		sizeof(cgc_popfd_instruction) - 1,		false,		_ICODE_POPFD_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_pushad_instruction,		sizeof(cgc_pushad_instruction) - 1,		false,		_ICODE_PUSHAD_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_pushfd_instruction,		sizeof(cgc_pushfd_instruction) - 1,		false,		_ICODE_PUSHFD_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_retf_instruction,			sizeof(cgc_retf_instruction) - 1,		false,		_ICODE_RETF_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_retn_instruction,			sizeof(cgc_retn_instruction) - 1,		false,		_ICODE_RETN_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_sahf_instruction,			sizeof(cgc_sahf_instruction) - 1,		false,		_ICODE_SAHF_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_seta_instruction,			sizeof(cgc_seta_instruction) - 1,		false,		_ICODE_SETA_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_setc_instruction,			sizeof(cgc_setc_instruction) - 1,		false,		_ICODE_SETC_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_setg_instruction,			sizeof(cgc_setg_instruction) - 1,		false,		_ICODE_SETG_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_setl_instruction,			sizeof(cgc_setl_instruction) - 1,		false,		_ICODE_SETL_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_setna_instruction,		sizeof(cgc_setna_instruction) - 1,		false,		_ICODE_SETNA_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_setnc_instruction,		sizeof(cgc_setnc_instruction) - 1,		false,		_ICODE_SETNC_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_setng_instruction,		sizeof(cgc_setng_instruction) - 1,		false,		_ICODE_SETNG_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_setnl_instruction,		sizeof(cgc_setnl_instruction) - 1,		false,		_ICODE_SETNL_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_setno_instruction,		sizeof(cgc_setno_instruction) - 1,		false,		_ICODE_SETNO_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_setns_instruction,		sizeof(cgc_setns_instruction) - 1,		false,		_ICODE_SETNS_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_setnz_instruction,		sizeof(cgc_setnz_instruction) - 1,		false,		_ICODE_SETNZ_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_seto_instruction,			sizeof(cgc_seto_instruction) - 1,		false,		_ICODE_SETO_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_setpe_instruction,		sizeof(cgc_setpe_instruction) - 1,		false,		_ICODE_SETPE_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_setpo_instruction,		sizeof(cgc_setpo_instruction) - 1,		false,		_ICODE_SETPO_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_sets_instruction,			sizeof(cgc_sets_instruction) - 1,		false,		_ICODE_SETS_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_setz_instruction,			sizeof(cgc_setz_instruction) - 1,		false,		_ICODE_SETZ_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_stc_instruction,			sizeof(cgc_stc_instruction) - 1,		false,		_ICODE_STC_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_std_instruction,			sizeof(cgc_std_instruction) - 1,		false,		_ICODE_STD_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_sti_instruction,			sizeof(cgc_sti_instruction) - 1,		false,		_ICODE_STI_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_wait_instruction,			sizeof(cgc_wait_instruction) - 1,		false,		_ICODE_WAIT_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_xlat_instruction,			sizeof(cgc_xlat_instruction) - 1,		false,		_ICODE_XLAT_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_repe_instruction,			sizeof(cgc_repe_instruction) - 1,		false,		_ICODE_REPE_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_repne_instruction,		sizeof(cgc_repne_instruction) - 1,		false,		_ICODE_REPNE_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_cmpsw_instruction,		sizeof(cgc_cmpsw_instruction) - 1,		false,		_ICODE_CMPSW_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_cmpsd_instruction,		sizeof(cgc_cmpsd_instruction) - 1,		false,		_ICODE_CMPSD_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_lodsw_instruction,		sizeof(cgc_lodsw_instruction) - 1,		false,		_ICODE_LODSW_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_lodsd_instruction,		sizeof(cgc_lodsd_instruction) - 1,		false,		_ICODE_LODSD_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_movsw_instruction,		sizeof(cgc_movsw_instruction) - 1,		false,		_ICODE_MOVSW_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_movsd_instruction,		sizeof(cgc_movsd_instruction) - 1,		false,		_ICODE_MOVSD_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_scasw_instruction,		sizeof(cgc_scasw_instruction) - 1,		false,		_ICODE_SCASW_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_scasd_instruction,		sizeof(cgc_scasd_instruction) - 1,		false,		_ICODE_SCASD_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_stosw_instruction,		sizeof(cgc_stosw_instruction) - 1,		false,		_ICODE_STOSW_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_stosd_instruction,		sizeof(cgc_stosd_instruction) - 1,		false,		_ICODE_STOSD_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_arpl_instruction,			sizeof(cgc_arpl_instruction) - 1,		false,		_ICODE_ARPL_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_bound_instruction,		sizeof(cgc_bound_instruction) - 1,		false,		_ICODE_BOUND_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_bsf_instruction,			sizeof(cgc_bsf_instruction) - 1,		false,		_ICODE_BSF_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_bsr_instruction,			sizeof(cgc_bsr_instruction) - 1,		false,		_ICODE_BSR_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_bt_instruction,			sizeof(cgc_bt_instruction) - 1,			false,		_ICODE_BT_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_btc_instruction,			sizeof(cgc_btc_instruction) - 1,		false,		_ICODE_BTC_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_btr_instruction,			sizeof(cgc_btr_instruction) - 1,		false,		_ICODE_BTR_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_bts_instruction,			sizeof(cgc_bts_instruction) - 1,		false,		_ICODE_BTS_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_call_instruction,			sizeof(cgc_call_instruction) - 1,		false,		_ICODE_CALL_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_cmova_instruction,		sizeof(cgc_cmova_instruction) - 1,		false,		_ICODE_CMOVA_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_cmovc_instruction,		sizeof(cgc_cmovc_instruction) - 1,		false,		_ICODE_CMOVC_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_cmovg_instruction,		sizeof(cgc_cmovg_instruction) - 1,		false,		_ICODE_CMOVG_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_cmovl_instruction,		sizeof(cgc_cmovl_instruction) - 1,		false,		_ICODE_CMOVL_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_cmovna_instruction,		sizeof(cgc_cmovna_instruction) - 1,		false,		_ICODE_CMOVNA_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_cmovnc_instruction,		sizeof(cgc_cmovnc_instruction) - 1,		false,		_ICODE_CMOVNC_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_cmovng_instruction,		sizeof(cgc_cmovng_instruction) - 1,		false,		_ICODE_CMOVNG_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_cmovnl_instruction,		sizeof(cgc_cmovnl_instruction) - 1,		false,		_ICODE_CMOVNL_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_cmovno_instruction,		sizeof(cgc_cmovno_instruction) - 1,		false,		_ICODE_CMOVNO_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_cmovns_instruction,		sizeof(cgc_cmovns_instruction) - 1,		false,		_ICODE_CMOVNS_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_cmovnz_instruction,		sizeof(cgc_cmovnz_instruction) - 1,		false,		_ICODE_CMOVNZ_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_cmovo_instruction,		sizeof(cgc_cmovo_instruction) - 1,		false,		_ICODE_CMOVO_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_cmovpe_instruction,		sizeof(cgc_cmovpe_instruction) - 1,		false,		_ICODE_CMOVPE_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_cmovpo_instruction,		sizeof(cgc_cmovpo_instruction) - 1,		false,		_ICODE_CMOVPO_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_cmovs_instruction,		sizeof(cgc_cmovs_instruction) - 1,		false,		_ICODE_CMOVS_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_cmovz_instruction,		sizeof(cgc_cmovz_instruction) - 1,		false,		_ICODE_CMOVZ_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_cmpxchg_instruction,		sizeof(cgc_cmpxchg_instruction) - 1,	false,		_ICODE_CMPXCHG_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_dec_instruction,			sizeof(cgc_dec_instruction) - 1,		false,		_ICODE_DEC_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_inc_instruction,			sizeof(cgc_inc_instruction) - 1,		false,		_ICODE_INC_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_imul_instruction,			sizeof(cgc_imul_instruction) - 1,		false,		_ICODE_IMUL_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_icebp_instruction,		sizeof(cgc_icebp_instruction) - 1,		false,		_ICODE_ICEBP_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_sldt_instruction,			sizeof(cgc_sldt_instruction) - 1,		false,		_ICODE_SLDT_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_lldt_instruction,			sizeof(cgc_lldt_instruction) - 1,		false,		_ICODE_LLDT_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_str_instruction,			sizeof(cgc_str_instruction) - 1,		false,		_ICODE_STR_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_verr_instruction,			sizeof(cgc_verr_instruction) - 1,		false,		_ICODE_VERR_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_verw_instruction,			sizeof(cgc_verw_instruction) - 1,		false,		_ICODE_VERW_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_ltr_instruction,			sizeof(cgc_ltr_instruction) - 1,		false,		_ICODE_LTR_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_unk_instruction,			sizeof(cgc_unk_instruction) - 1,		false,		_ICODE_UNK_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_sgdt_instruction,			sizeof(cgc_sgdt_instruction) - 1,		false,		_ICODE_SGDT_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_sidt_instruction,			sizeof(cgc_sidt_instruction) - 1,		false,		_ICODE_SIDT_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_lgdt_instruction,			sizeof(cgc_lgdt_instruction) - 1,		false,		_ICODE_LGDT_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_lidt_instruction,			sizeof(cgc_lidt_instruction) - 1,		false,		_ICODE_LIDT_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_lmsw_instruction,			sizeof(cgc_lmsw_instruction) - 1,		false,		_ICODE_LMSW_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_smsw_instruction,			sizeof(cgc_smsw_instruction) - 1,		false,		_ICODE_SMSW_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_invlpg_instruction,		sizeof(cgc_invlpg_instruction) - 1,		false,		_ICODE_INVLPG_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_psraw_instruction,		sizeof(cgc_psraw_instruction) - 1,		false,		_ICODE_PSRAW_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_psrad_instruction,		sizeof(cgc_psrad_instruction) - 1,		false,		_ICODE_PSRAD_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_psrld_instruction,		sizeof(cgc_psrld_instruction) - 1,		false,		_ICODE_PSRLD_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_psrlw_instruction,		sizeof(cgc_psrlw_instruction) - 1,		false,		_ICODE_PSRLW_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_psrlq_instruction,		sizeof(cgc_psrlq_instruction) - 1,		false,		_ICODE_PSRLQ_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_psubb_instruction,		sizeof(cgc_psubb_instruction) - 1,		false,		_ICODE_PSUBB_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_psubw_instruction,		sizeof(cgc_psubw_instruction) - 1,		false,		_ICODE_PSUBW_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_psubd_instruction,		sizeof(cgc_psubd_instruction) - 1,		false,		_ICODE_PSUBD_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_psubsb_instruction,		sizeof(cgc_psubsb_instruction) - 1,		false,		_ICODE_PSUBSB_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_psubsw_instruction,		sizeof(cgc_psubsw_instruction) - 1,		false,		_ICODE_PSUBSW_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_psubusb_instruction,		sizeof(cgc_psubusb_instruction) - 1,	false,		_ICODE_PSUBUSB_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_psubusw_instruction,		sizeof(cgc_psubusw_instruction) - 1,	false,		_ICODE_PSUBUSW_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_punpckhbw_instruction,	sizeof(cgc_punpckhbw_instruction) - 1,	false,		_ICODE_PUNPCKHBW_INSTRUCTION,		true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_punpckhwd_instruction,	sizeof(cgc_punpckhwd_instruction) - 1,	false,		_ICODE_PUNPCKHWD_INSTRUCTION,		true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_punpckhdq_instruction,	sizeof(cgc_punpckhdq_instruction) - 1,	false,		_ICODE_PUNPCKHDQ_INSTRUCTION,		true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_punpcklbw_instruction,	sizeof(cgc_punpcklbw_instruction) - 1,	false,		_ICODE_PUNPCKLBW_INSTRUCTION,		true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_punpcklwd_instruction,	sizeof(cgc_punpcklwd_instruction) - 1,	false,		_ICODE_PUNPCKLWD_INSTRUCTION,		true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_punpckldq_instruction,	sizeof(cgc_punpckldq_instruction) - 1,	false,		_ICODE_PUNPCKLDQ_INSTRUCTION,		true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_pxor_instruction,			sizeof(cgc_pxor_instruction) - 1,		false,		_ICODE_PXOR_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_rsm_instruction,			sizeof(cgc_rsm_instruction) - 1,		false,		_ICODE_RSM_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_shld_instruction,			sizeof(cgc_shld_instruction) - 1,		false,		_ICODE_SHLD_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_shrd_instruction,			sizeof(cgc_shrd_instruction) - 1,		false,		_ICODE_SHRD_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_test_instruction,			sizeof(cgc_test_instruction) - 1,		false,		_ICODE_TEST_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_xchg_instruction,			sizeof(cgc_xchg_instruction) - 1,		false,		_ICODE_XCHG_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_ud2_instruction,			sizeof(cgc_ud2_instruction) - 1,		false,		_ICODE_UD2_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_wrmsr_instruction,		sizeof(cgc_wrmsr_instruction) - 1,		false,		_ICODE_WRMSR_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_wbinvd_instruction,		sizeof(cgc_wbinvd_instruction) - 1,		false,		_ICODE_WBINVD_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_xadd_instruction,			sizeof(cgc_xadd_instruction) - 1,		false,		_ICODE_XADD_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_packssdw_instruction,		sizeof(cgc_packssdw_instruction) - 1,	false,		_ICODE_PACKSSDW_INSTRUCTION,		true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_packsswb_instruction,		sizeof(cgc_packsswb_instruction) - 1,	false,		_ICODE_PACKSSWB_INSTRUCTION,		true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_packuswb_instruction,		sizeof(cgc_packuswb_instruction) - 1,	false,		_ICODE_PACKUSWB_INSTRUCTION,		true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_paddb_instruction,		sizeof(cgc_paddb_instruction) - 1,		false,		_ICODE_PADDB_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_paddd_instruction,		sizeof(cgc_paddd_instruction) - 1,		false,		_ICODE_PADDD_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_paddsb_instruction,		sizeof(cgc_paddsb_instruction) - 1,		false,		_ICODE_PADDSB_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_paddsw_instruction,		sizeof(cgc_paddsw_instruction) - 1,		false,		_ICODE_PADDSW_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_paddusb_instruction,		sizeof(cgc_paddusb_instruction) - 1,	false,		_ICODE_PADDUSB_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_paddusw_instruction,		sizeof(cgc_paddusw_instruction) - 1,	false,		_ICODE_PADDUSW_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_paddw_instruction,		sizeof(cgc_paddw_instruction) - 1,		false,		_ICODE_PADDW_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_pand_instruction,			sizeof(cgc_pand_instruction) - 1,		false,		_ICODE_PAND_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_pandn_instruction,		sizeof(cgc_pandn_instruction) - 1,		false,		_ICODE_PANDN_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_pcmpeqb_instruction,		sizeof(cgc_pcmpeqb_instruction) - 1,	false,		_ICODE_PCMPEQB_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_pcmpeqd_instruction,		sizeof(cgc_pcmpeqd_instruction) - 1,	false,		_ICODE_PCMPEQD_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_pcmpeqw_instruction,		sizeof(cgc_pcmpeqw_instruction) - 1,	false,		_ICODE_PCMPEQW_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_pcmpgtb_instruction,		sizeof(cgc_pcmpgtb_instruction) - 1,	false,		_ICODE_PCMPGTB_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_pcmpgtd_instruction,		sizeof(cgc_pcmpgtd_instruction) - 1,	false,		_ICODE_PCMPGTD_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_pcmpgtw_instruction,		sizeof(cgc_pcmpgtw_instruction) - 1,	false,		_ICODE_PCMPGTW_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_pmaddwd_instruction,		sizeof(cgc_pmaddwd_instruction) - 1,	false,		_ICODE_PMADDWD_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_pmulhw_instruction,		sizeof(cgc_pmulhw_instruction) - 1,		false,		_ICODE_PMULHW_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_pmullw_instruction,		sizeof(cgc_pmullw_instruction) - 1,		false,		_ICODE_PMULLW_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_por_instruction,			sizeof(cgc_por_instruction) - 1,		false,		_ICODE_POR_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_pslld_instruction,		sizeof(cgc_pslld_instruction) - 1,		false,		_ICODE_PSLLD_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_psllq_instruction,		sizeof(cgc_psllq_instruction) - 1,		false,		_ICODE_PSLLQ_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_psllw_instruction,		sizeof(cgc_psllw_instruction) - 1,		false,		_ICODE_PSLLW_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_or_instruction,			sizeof(cgc_or_instruction) - 1,			false,		_ICODE_OR_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_hcf_instruction,			sizeof(cgc_hcf_instruction) - 1,		false,		_ICODE_HCF_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_cmpxchg8b_instruction,	sizeof(cgc_cmpxchg8b_instruction) - 1,	false,		_ICODE_CMPXCHG8B_INSTRUCTION,		true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_in_instruction,			sizeof(cgc_in_instruction) - 1,			false,		_ICODE_IN_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_rdmsr_instruction,		sizeof(cgc_rdmsr_instruction) - 1,		false,		_ICODE_RDMSR_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_rdpmc_instruction,		sizeof(cgc_rdpmc_instruction) - 1,		false,		_ICODE_RDPMC_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_rdtsc_instruction,		sizeof(cgc_rdtsc_instruction) - 1,		false,		_ICODE_RDTSC_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_movsx_instruction,		sizeof(cgc_movsx_instruction) - 1,		false,		_ICODE_MOVSX_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_movzx_instruction,		sizeof(cgc_movzx_instruction) - 1,		false,		_ICODE_MOVZX_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_lsl_instruction,			sizeof(cgc_lsl_instruction) - 1,		false,		_ICODE_LSL_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_lss_instruction,			sizeof(cgc_lss_instruction) - 1,		false,		_ICODE_LSS_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_loopne_instruction,		sizeof(cgc_loopne_instruction) - 1,		false,		_ICODE_LOOPNE_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_loope_instruction,		sizeof(cgc_loope_instruction) - 1,		false,		_ICODE_LOOPE_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_loop_instruction,			sizeof(cgc_loop_instruction) - 1,		false,		_ICODE_LOOP_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_lgs_instruction,			sizeof(cgc_lgs_instruction) - 1,		false,		_ICODE_LGS_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_lfs_instruction,			sizeof(cgc_lfs_instruction) - 1,		false,		_ICODE_LFS_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_les_instruction,			sizeof(cgc_les_instruction) - 1,		false,		_ICODE_LES_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_lea_instruction,			sizeof(cgc_lea_instruction) - 1,		false,		_ICODE_LEA_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_lds_instruction,			sizeof(cgc_lds_instruction) - 1,		false,		_ICODE_LDS_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_lar_instruction,			sizeof(cgc_lar_instruction) - 1,		false,		_ICODE_LAR_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_jz_instruction,			sizeof(cgc_jz_instruction) - 1,			false,		_ICODE_JZ_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_js_instruction,			sizeof(cgc_js_instruction) - 1,			false,		_ICODE_JS_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_jpo_instruction,			sizeof(cgc_jpo_instruction) - 1,		false,		_ICODE_JPO_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_jpe_instruction,			sizeof(cgc_jpe_instruction) - 1,		false,		_ICODE_JPE_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_jo_instruction,			sizeof(cgc_jo_instruction) - 1,			false,		_ICODE_JO_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_jnz_instruction,			sizeof(cgc_jnz_instruction) - 1,		false,		_ICODE_JNZ_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_jno_instruction,			sizeof(cgc_jno_instruction) - 1,		false,		_ICODE_JNO_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_jnl_instruction,			sizeof(cgc_jnl_instruction) - 1,		false,		_ICODE_JNL_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_jng_instruction,			sizeof(cgc_jng_instruction) - 1,		false,		_ICODE_JNG_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_jnc_instruction,			sizeof(cgc_jnc_instruction) - 1,		false,		_ICODE_JNC_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_jna_instruction,			sizeof(cgc_jna_instruction) - 1,		false,		_ICODE_JNA_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_jmp_instruction,			sizeof(cgc_jmp_instruction) - 1,		false,		_ICODE_JMP_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_jl_instruction,			sizeof(cgc_jl_instruction) - 1,			false,		_ICODE_JL_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_jg_instruction,			sizeof(cgc_jg_instruction) - 1,			false,		_ICODE_JG_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_jcxz_instruction,			sizeof(cgc_jcxz_instruction) - 1,		false,		_ICODE_JCXZ_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_jecxz_instruction,		sizeof(cgc_jecxz_instruction) - 1,		false,		_ICODE_JECXZ_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_jc_instruction,			sizeof(cgc_jc_instruction) - 1,			false,		_ICODE_JC_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_ja_instruction,			sizeof(cgc_ja_instruction) - 1,			false,		_ICODE_JA_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_jns_instruction,			sizeof(cgc_jns_instruction) - 1,		false,		_ICODE_JNS_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_invd_instruction,			sizeof(cgc_invd_instruction) - 1,		false,		_ICODE_INVD_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_idiv_instruction,			sizeof(cgc_idiv_instruction) - 1,		false,		_ICODE_IDIV_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_div_instruction,			sizeof(cgc_div_instruction) - 1,		false,		_ICODE_DIV_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_neg_instruction,			sizeof(cgc_neg_instruction) - 1,		false,		_ICODE_NEG_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_mul_instruction,			sizeof(cgc_mul_instruction) - 1,		false,		_ICODE_MUL_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_not_instruction,			sizeof(cgc_not_instruction) - 1,		false,		_ICODE_NOT_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_sar_instruction,			sizeof(cgc_sar_instruction) - 1,		false,		_ICODE_SAR_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_shr_instruction,			sizeof(cgc_shr_instruction) - 1,		false,		_ICODE_SHR_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_shl_instruction,			sizeof(cgc_shl_instruction) - 1,		false,		_ICODE_SHL_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_rcr_instruction,			sizeof(cgc_rcr_instruction) - 1,		false,		_ICODE_RCR_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_rcl_instruction,			sizeof(cgc_rcl_instruction) - 1,		false,		_ICODE_RCL_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_ror_instruction,			sizeof(cgc_ror_instruction) - 1,		false,		_ICODE_ROR_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_rol_instruction,			sizeof(cgc_rol_instruction) - 1,		false,		_ICODE_ROL_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_mov_instruction,			sizeof(cgc_mov_instruction) - 1,		false,		_ICODE_MOV_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_fnop_instruction,			sizeof(cgc_fnop_instruction) - 1,		false,		_ICODE_FNOP_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_fchs_instruction,			sizeof(cgc_fchs_instruction) - 1,		false,		_ICODE_FCHS_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_fabs_instruction,			sizeof(cgc_fabs_instruction) - 1,		false,		_ICODE_FABS_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_ftst_instruction,			sizeof(cgc_ftst_instruction) - 1,		false,		_ICODE_FTST_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_fxam_instruction,			sizeof(cgc_fxam_instruction) - 1,		false,		_ICODE_FXAM_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_fld1_instruction,			sizeof(cgc_fld1_instruction) - 1,		false,		_ICODE_FLD1_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_fld2t_instruction,		sizeof(cgc_fld2t_instruction) - 1,		false,		_ICODE_FLD2T_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_fld2e_instruction,		sizeof(cgc_fld2e_instruction) - 1,		false,		_ICODE_FLD2E_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_fldpi_instruction,		sizeof(cgc_fldpi_instruction) - 1,		false,		_ICODE_FLDPI_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_fldlg2_instruction,		sizeof(cgc_fldlg2_instruction) - 1,		false,		_ICODE_FLDLG2_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_fldln2_instruction,		sizeof(cgc_fldln2_instruction) - 1,		false,		_ICODE_FLDLN2_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_fldz_instruction,			sizeof(cgc_fldz_instruction) - 1,		false,		_ICODE_FLDZ_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_f2xm1_instruction,		sizeof(cgc_f2xm1_instruction) - 1,		false,		_ICODE_F2XM1_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_fyl2x_instruction,		sizeof(cgc_fyl2x_instruction) - 1,		false,		_ICODE_FYL2X_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_fptan_instruction,		sizeof(cgc_fptan_instruction) - 1,		false,		_ICODE_FPTAN_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_fpatan_instruction,		sizeof(cgc_fpatan_instruction) - 1,		false,		_ICODE_FPATAN_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_fxtract_instruction,		sizeof(cgc_fxtract_instruction) - 1,	false,		_ICODE_FXTRACT_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_fprem1_instruction,		sizeof(cgc_fprem1_instruction) - 1,		false,		_ICODE_FPREM1_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_fdecstp_instruction,		sizeof(cgc_fdecstp_instruction) - 1,	false,		_ICODE_FDECSTP_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_fincstp_instruction,		sizeof(cgc_fincstp_instruction) - 1,	false,		_ICODE_FINCSTP_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_fprem_instruction,		sizeof(cgc_fprem_instruction) - 1,		false,		_ICODE_FPREM_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_fyl2xp1_instruction,		sizeof(cgc_fyl2xp1_instruction) - 1,	false,		_ICODE_FYL2XP1_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_fsqrt_instruction,		sizeof(cgc_fsqrt_instruction) - 1,		false,		_ICODE_FSQRT_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_fsincos_instruction,		sizeof(cgc_fsincos_instruction) - 1,	false,		_ICODE_FSINCOS_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_frndint_instruction,		sizeof(cgc_frndint_instruction) - 1,	false,		_ICODE_FRNDINT_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_fscale_instruction,		sizeof(cgc_fscale_instruction) - 1,		false,		_ICODE_FSCALE_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_fsin_instruction,			sizeof(cgc_fsin_instruction) - 1,		false,		_ICODE_FSIN_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_fcos_instruction,			sizeof(cgc_fcos_instruction) - 1,		false,		_ICODE_FCOS_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_fadd_instruction,			sizeof(cgc_fadd_instruction) - 1,		false,		_ICODE_FADD_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_fmul_instruction,			sizeof(cgc_fmul_instruction) - 1,		false,		_ICODE_FMUL_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_fcom_instruction,			sizeof(cgc_fcom_instruction) - 1,		false,		_ICODE_FCOM_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_fcomp_instruction,		sizeof(cgc_fcomp_instruction) - 1,		false,		_ICODE_FCOMP_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_fsub_instruction,			sizeof(cgc_fsub_instruction) - 1,		false,		_ICODE_FSUB_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_fsubr_instruction,		sizeof(cgc_fsubr_instruction) - 1,		false,		_ICODE_FSUBR_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_fdiv_instruction,			sizeof(cgc_fdiv_instruction) - 1,		false,		_ICODE_FDIV_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_fdivr_instruction,		sizeof(cgc_fdivr_instruction) - 1,		false,		_ICODE_FDIVR_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_fld_instruction,			sizeof(cgc_fld_instruction) - 1,		false,		_ICODE_FLD_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_fst_instruction,			sizeof(cgc_fst_instruction) - 1,		false,		_ICODE_FST_INSTRUCTION,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_fstp_instruction,			sizeof(cgc_fstp_instruction) - 1,		false,		_ICODE_FSTP_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_fiadd_instruction,		sizeof(cgc_fiadd_instruction) - 1,		false,		_ICODE_FIADD_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_fimul_instruction,		sizeof(cgc_fimul_instruction) - 1,		false,		_ICODE_FIMUL_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_ficom_instruction,		sizeof(cgc_ficom_instruction) - 1,		false,		_ICODE_FICOM_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_ficomp_instruction,		sizeof(cgc_ficomp_instruction) - 1,		false,		_ICODE_FICOMP_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_fisub_instruction,		sizeof(cgc_fisub_instruction) - 1,		false,		_ICODE_FISUB_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_fisubr_instruction,		sizeof(cgc_fisubr_instruction) - 1,		false,		_ICODE_FISUBR_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_fidiv_instruction,		sizeof(cgc_fidiv_instruction) - 1,		false,		_ICODE_FIDIV_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_fidivr_instruction,		sizeof(cgc_fidivr_instruction) - 1,		false,		_ICODE_FIDIVR_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_fist_instruction,			sizeof(cgc_fist_instruction) - 1,		false,		_ICODE_FIST_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_fistp_instruction,		sizeof(cgc_fistp_instruction) - 1,		false,		_ICODE_FISTP_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_fild_instruction,			sizeof(cgc_fild_instruction) - 1,		false,		_ICODE_FILD_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_fbld_instruction,			sizeof(cgc_fbld_instruction) - 1,		false,		_ICODE_FBLD_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_fbstp_instruction,		sizeof(cgc_fbstp_instruction) - 1,		false,		_ICODE_FBSTP_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_fxch_instruction,			sizeof(cgc_fxch_instruction) - 1,		false,		_ICODE_FXCH_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_fucomp_instruction,		sizeof(cgc_fucomp_instruction) - 1,		false,		_ICODE_FUCOMP_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_fucompp_instruction,		sizeof(cgc_fucompp_instruction) - 1,	false,		_ICODE_FUCOMPP_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_fnclex_instruction,		sizeof(cgc_fnclex_instruction) - 1,		false,		_ICODE_FNCLEX_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_fninit_instruction,		sizeof(cgc_fninit_instruction) - 1,		false,		_ICODE_FNINIT_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_fnstsw_instruction,		sizeof(cgc_fnstsw_instruction) - 1,		false,		_ICODE_FNSTSW_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_fldcw_instruction,		sizeof(cgc_fldcw_instruction) - 1,		false,		_ICODE_FLDCW_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_fnstcw_instruction,		sizeof(cgc_fnstcw_instruction) - 1,		false,		_ICODE_FNSTCW_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_fldenv_instruction,		sizeof(cgc_fldenv_instruction) - 1,		false,		_ICODE_FLDENV_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_fnstenv_instruction,		sizeof(cgc_fnstenv_instruction) - 1,	false,		_ICODE_FNSTENV_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_frstor_instruction,		sizeof(cgc_frstor_instruction) - 1,		false,		_ICODE_FRSTOR_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_fnsave_instruction,		sizeof(cgc_fnsave_instruction) - 1,		false,		_ICODE_FNSAVE_INSTRUCTION,			true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,		null0	},
																																																									  
		{	(cs8*)cgc_ptr_tbyte,				sizeof(cgc_ptr_tbyte) - 1,				false,		_ICODE_PTR_TBYTE,					false,		_ICAT_POINTER_SIZE,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_ptr_dqword,				sizeof(cgc_ptr_dqword) - 1,				false,		_ICODE_PTR_DQWORD,					false,		_ICAT_POINTER_SIZE,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_ptr_qword,				sizeof(cgc_ptr_qword) - 1,				false,		_ICODE_PTR_QWORD,					false,		_ICAT_POINTER_SIZE,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_ptr_dword,				sizeof(cgc_ptr_dword) - 1,				false,		_ICODE_PTR_DWORD,					false,		_ICAT_POINTER_SIZE,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_ptr_word,					sizeof(cgc_ptr_word) - 1,				false,		_ICODE_PTR_WORD,					false,		_ICAT_POINTER_SIZE,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_ptr_byte,					sizeof(cgc_ptr_byte) - 1,				false,		_ICODE_PTR_BYTE,					false,		_ICAT_POINTER_SIZE,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_ptr_m16_16,				sizeof(cgc_ptr_m16_16) - 1,				false,		_ICODE_PTR_M16_16,					false,		_ICAT_POINTER_SIZE,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_ptr_m16_32,				sizeof(cgc_ptr_m16_32) - 1,				false,		_ICODE_PTR_M16_32,					false,		_ICAT_POINTER_SIZE,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_ptr_f32,					sizeof(cgc_ptr_f32) - 1,				false,		_ICODE_PTR_F32,						false,		_ICAT_POINTER_SIZE,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_ptr_f64,					sizeof(cgc_ptr_f64) - 1,				false,		_ICODE_PTR_F64,						false,		_ICAT_POINTER_SIZE,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_ptr_f80,					sizeof(cgc_ptr_f80) - 1,				false,		_ICODE_PTR_F80,						false,		_ICAT_POINTER_SIZE,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_ptr_s16,					sizeof(cgc_ptr_s16) - 1,				false,		_ICODE_PTR_S16,						false,		_ICAT_POINTER_SIZE,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_ptr_s32,					sizeof(cgc_ptr_s32) - 1,				false,		_ICODE_PTR_S32,						false,		_ICAT_POINTER_SIZE,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_ptr_s64,					sizeof(cgc_ptr_s64) - 1,				false,		_ICODE_PTR_S64,						false,		_ICAT_POINTER_SIZE,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_ptr_m80,					sizeof(cgc_ptr_m80) - 1,				false,		_ICODE_PTR_M80,						false,		_ICAT_POINTER_SIZE,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_ptr_mmx,					sizeof(cgc_ptr_mmx) - 1,				false,		_ICODE_PTR_MMX,						false,		_ICAT_POINTER_SIZE,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_ptr_xmmx,					sizeof(cgc_ptr_xmmx) - 1,				false,		_ICODE_PTR_XMMX,					false,		_ICAT_POINTER_SIZE,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_ptr_fpu,					sizeof(cgc_ptr_fpu) - 1,				false,		_ICODE_PTR_FPU,						false,		_ICAT_POINTER_SIZE,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_ptr_6byte,				sizeof(cgc_ptr_6byte) - 1,				false,		_ICODE_PTR_6BYTE,					false,		_ICAT_POINTER_SIZE,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_ptr_10byte,				sizeof(cgc_ptr_10byte) - 1,				false,		_ICODE_PTR_10BYTE,					false,		_ICAT_POINTER_SIZE,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_ptr_14byte,				sizeof(cgc_ptr_14byte) - 1,				false,		_ICODE_PTR_14BYTE,					false,		_ICAT_POINTER_SIZE,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_ptr_28byte,				sizeof(cgc_ptr_28byte) - 1,				false,		_ICODE_PTR_28BYTE,					false,		_ICAT_POINTER_SIZE,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_ptr_94byte,				sizeof(cgc_ptr_94byte) - 1,				false,		_ICODE_PTR_94BYTE,					false,		_ICAT_POINTER_SIZE,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_ptr_108byte,				sizeof(cgc_ptr_108byte) - 1,			false,		_ICODE_PTR_108BYTE,					false,		_ICAT_POINTER_SIZE,		&colorDefault,		false,			null0,		null0	},
																																																									  
		{	(cs8*)cgc_cs_reg,					sizeof(cgc_cs_reg) - 1,					false,		_ICODE_CS,							false,		_ICAT_SEGMENT_REGISTER,	&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_ds_reg,					sizeof(cgc_ds_reg) - 1,					false,		_ICODE_DS,							false,		_ICAT_SEGMENT_REGISTER,	&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_es_reg,					sizeof(cgc_es_reg) - 1,					false,		_ICODE_ES,							false,		_ICAT_SEGMENT_REGISTER,	&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_fs_reg,					sizeof(cgc_fs_reg) - 1,					false,		_ICODE_FS,							false,		_ICAT_SEGMENT_REGISTER,	&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_gs_reg,					sizeof(cgc_gs_reg) - 1,					false,		_ICODE_GS,							false,		_ICAT_SEGMENT_REGISTER,	&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_ss_reg,					sizeof(cgc_ss_reg) - 1,					false,		_ICODE_SS,							false,		_ICAT_SEGMENT_REGISTER,	&colorDefault,		false,			null0,		null0	},
																																																									  
		{	(cs8*)cgc_al_reg,					sizeof(cgc_al_reg) - 1,					false,		_ICODE_AL,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_bl_reg,					sizeof(cgc_bl_reg) - 1,					false,		_ICODE_BL,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_cl_reg,					sizeof(cgc_cl_reg) - 1,					false,		_ICODE_CL,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_dl_reg,					sizeof(cgc_dl_reg) - 1,					false,		_ICODE_DL,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_ah_reg,					sizeof(cgc_ah_reg) - 1,					false,		_ICODE_AH,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_bh_reg,					sizeof(cgc_bh_reg) - 1,					false,		_ICODE_BH,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_ch_reg,					sizeof(cgc_ch_reg) - 1,					false,		_ICODE_CH,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_dh_reg,					sizeof(cgc_dh_reg) - 1,					false,		_ICODE_DH,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,		null0	},
																																																									  
		{	(cs8*)cgc_ax_reg,					sizeof(cgc_ax_reg) - 1,					false,		_ICODE_AX,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_bx_reg,					sizeof(cgc_bx_reg) - 1,					false,		_ICODE_BX,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_cx_reg,					sizeof(cgc_cx_reg) - 1,					false,		_ICODE_CX,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_dx_reg,					sizeof(cgc_dx_reg) - 1,					false,		_ICODE_DX,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_si_reg,					sizeof(cgc_si_reg) - 1,					false,		_ICODE_SI,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_di_reg,					sizeof(cgc_di_reg) - 1,					false,		_ICODE_DI,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_bp_reg,					sizeof(cgc_bp_reg) - 1,					false,		_ICODE_BP,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_sp_reg,					sizeof(cgc_sp_reg) - 1,					false,		_ICODE_SP,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_ip_reg,					sizeof(cgc_ip_reg) - 1,					false,		_ICODE_IP,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,		null0	},
																																																									  
		{	(cs8*)cgc_eax_reg,					sizeof(cgc_eax_reg) - 1,				false,		_ICODE_EAX,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_ebx_reg,					sizeof(cgc_ebx_reg) - 1,				false,		_ICODE_EBX,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_ecx_reg,					sizeof(cgc_ecx_reg) - 1,				false,		_ICODE_ECX,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_edx_reg,					sizeof(cgc_edx_reg) - 1,				false,		_ICODE_EDX,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_esi_reg,					sizeof(cgc_esi_reg) - 1,				false,		_ICODE_ESI,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_edi_reg,					sizeof(cgc_edi_reg) - 1,				false,		_ICODE_EDI,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_ebp_reg,					sizeof(cgc_ebp_reg) - 1,				false,		_ICODE_EBP,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_esp_reg,					sizeof(cgc_esp_reg) - 1,				false,		_ICODE_ESP,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_eip_reg,					sizeof(cgc_eip_reg) - 1,				false,		_ICODE_EIP,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,		null0	},
																																																									  
		{	(cs8*)cgc_cr0_reg,					sizeof(cgc_cr0_reg) - 1,				false,		_ICODE_CR0,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_cr1_reg,					sizeof(cgc_cr1_reg) - 1,				false,		_ICODE_CR1,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_cr2_reg,					sizeof(cgc_cr2_reg) - 1,				false,		_ICODE_CR2,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_cr3_reg,					sizeof(cgc_cr3_reg) - 1,				false,		_ICODE_CR3,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_cr4_reg,					sizeof(cgc_cr4_reg) - 1,				false,		_ICODE_CR4,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_cr5_reg,					sizeof(cgc_cr5_reg) - 1,				false,		_ICODE_CR5,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_cr6_reg,					sizeof(cgc_cr6_reg) - 1,				false,		_ICODE_CR6,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_cr7_reg,					sizeof(cgc_cr7_reg) - 1,				false,		_ICODE_CR7,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,		null0	},
																																																									  
		{	(cs8*)cgc_dr0_reg,					sizeof(cgc_dr0_reg) - 1,				false,		_ICODE_DR0,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_dr1_reg,					sizeof(cgc_dr1_reg) - 1,				false,		_ICODE_DR1,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_dr2_reg,					sizeof(cgc_dr2_reg) - 1,				false,		_ICODE_DR2,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_dr3_reg,					sizeof(cgc_dr3_reg) - 1,				false,		_ICODE_DR3,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_dr4_reg,					sizeof(cgc_dr4_reg) - 1,				false,		_ICODE_DR4,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_dr5_reg,					sizeof(cgc_dr5_reg) - 1,				false,		_ICODE_DR5,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_dr6_reg,					sizeof(cgc_dr6_reg) - 1,				false,		_ICODE_DR6,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_dr7_reg,					sizeof(cgc_dr7_reg) - 1,				false,		_ICODE_DR7,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,		null0	},
																																																									  
		{	(cs8*)cgc_tr0_reg,					sizeof(cgc_tr0_reg) - 1,				false,		_ICODE_TR0,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_tr1_reg,					sizeof(cgc_tr1_reg) - 1,				false,		_ICODE_TR1,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_tr2_reg,					sizeof(cgc_tr2_reg) - 1,				false,		_ICODE_TR2,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_tr3_reg,					sizeof(cgc_tr3_reg) - 1,				false,		_ICODE_TR3,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_tr4_reg,					sizeof(cgc_tr4_reg) - 1,				false,		_ICODE_TR4,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_tr5_reg,					sizeof(cgc_tr5_reg) - 1,				false,		_ICODE_TR5,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_tr6_reg,					sizeof(cgc_tr6_reg) - 1,				false,		_ICODE_TR6,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_tr7_reg,					sizeof(cgc_tr7_reg) - 1,				false,		_ICODE_TR7,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,		null0	},
																																																									  
		{	(cs8*)cgc_st0_reg,					sizeof(cgc_st0_reg) - 1,				false,		_ICODE_ST0,							false,		_ICAT_FPU_REGISTER,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_st1_reg,					sizeof(cgc_st1_reg) - 1,				false,		_ICODE_ST1,							false,		_ICAT_FPU_REGISTER,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_st2_reg,					sizeof(cgc_st2_reg) - 1,				false,		_ICODE_ST2,							false,		_ICAT_FPU_REGISTER,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_st3_reg,					sizeof(cgc_st3_reg) - 1,				false,		_ICODE_ST3,							false,		_ICAT_FPU_REGISTER,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_st4_reg,					sizeof(cgc_st4_reg) - 1,				false,		_ICODE_ST4,							false,		_ICAT_FPU_REGISTER,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_st5_reg,					sizeof(cgc_st5_reg) - 1,				false,		_ICODE_ST5,							false,		_ICAT_FPU_REGISTER,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_st6_reg,					sizeof(cgc_st6_reg) - 1,				false,		_ICODE_ST6,							false,		_ICAT_FPU_REGISTER,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_st7_reg,					sizeof(cgc_st7_reg) - 1,				false,		_ICODE_ST7,							false,		_ICAT_FPU_REGISTER,		&colorDefault,		false,			null0,		null0	},
																																																									  
		{	(cs8*)cgc_mm0_reg,					sizeof(cgc_mm0_reg) - 1,				false,		_ICODE_MM0,							false,		_ICAT_MMX_REGISTER,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_mm1_reg,					sizeof(cgc_mm1_reg) - 1,				false,		_ICODE_MM1,							false,		_ICAT_MMX_REGISTER,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_mm2_reg,					sizeof(cgc_mm2_reg) - 1,				false,		_ICODE_MM2,							false,		_ICAT_MMX_REGISTER,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_mm3_reg,					sizeof(cgc_mm3_reg) - 1,				false,		_ICODE_MM3,							false,		_ICAT_MMX_REGISTER,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_mm4_reg,					sizeof(cgc_mm4_reg) - 1,				false,		_ICODE_MM4,							false,		_ICAT_MMX_REGISTER,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_mm5_reg,					sizeof(cgc_mm5_reg) - 1,				false,		_ICODE_MM5,							false,		_ICAT_MMX_REGISTER,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_mm6_reg,					sizeof(cgc_mm6_reg) - 1,				false,		_ICODE_MM6,							false,		_ICAT_MMX_REGISTER,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_mm7_reg,					sizeof(cgc_mm7_reg) - 1,				false,		_ICODE_MM7,							false,		_ICAT_MMX_REGISTER,		&colorDefault,		false,			null0,		null0	},
																																																									  
		{	(cs8*)cgc_xmm0_reg,					sizeof(cgc_xmm0_reg) - 1,				false,		_ICODE_XMM0,						false,		_ICAT_XMM_REGISTER,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_xmm1_reg,					sizeof(cgc_xmm1_reg) - 1,				false,		_ICODE_XMM1,						false,		_ICAT_XMM_REGISTER,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_xmm2_reg,					sizeof(cgc_xmm2_reg) - 1,				false,		_ICODE_XMM2,						false,		_ICAT_XMM_REGISTER,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_xmm3_reg,					sizeof(cgc_xmm3_reg) - 1,				false,		_ICODE_XMM3,						false,		_ICAT_XMM_REGISTER,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_xmm4_reg,					sizeof(cgc_xmm4_reg) - 1,				false,		_ICODE_XMM4,						false,		_ICAT_XMM_REGISTER,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_xmm5_reg,					sizeof(cgc_xmm5_reg) - 1,				false,		_ICODE_XMM5,						false,		_ICAT_XMM_REGISTER,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_xmm6_reg,					sizeof(cgc_xmm6_reg) - 1,				false,		_ICODE_XMM6,						false,		_ICAT_XMM_REGISTER,		&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_xmm7_reg,					sizeof(cgc_xmm7_reg) - 1,				false,		_ICODE_XMM7,						false,		_ICAT_XMM_REGISTER,		&colorDefault,		false,			null0,		null0	},
																																																									  
		{	(cs8*)cgc_lasm_function,			sizeof(cgc_lasm_function) - 1,			false,		_ICODE_LASM_FUNCTION,				true,		_ICAT_FLOW,				&colorDefault,		false,			null0,		null0	},
		{	(cs8*)cgc_lasm_struct,				sizeof(cgc_lasm_struct) - 1,			false,		_ICODE_LASM_STRUCT,					true,		_ICAT_DEFINITION,		&colorDefault,		false,			null0,		null0	},
		
		{	0,									0,										0,			0,									0,			0,						0,					0,				0,			0		}
	};
