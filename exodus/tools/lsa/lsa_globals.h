//////////
//
// /libsf/exodus/tools/lsa/lasm_globals.h
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
	SBuilder*		includePaths					= NULL;				// (SLsaInclude) Include files
	SBuilder*		includeFiles					= NULL;				// (SLsaFile) Files that are included in the assembly
	SBuilder*		gsLsaDMacRoot					= NULL;				// (SLsaDefineMacro) List of define and macro statements found, in the order found
	SLsaBlock*		firstFunction					= NULL;				// All function definitions
	SLsaStruct*		firstStruct						= NULL;				// All struct definitions
	SLsaEnum*		firstEnum						= NULL;				// All enum definitions
	SLsaCmdLine		cmdLine;											// Command line options


//////////
// Colors
//////
	SBgra			colorDefault					= { rgba(0, 0, 0, 255) };		// Black


//////////
// Assembly opcodes
//////
	SAsciiCompSearcher cgcKeywordsLsa[] =
	{
		// 																																first								syntax highlight	syntax highlight
		//	keyword								length									repeats?	extra (type)						on line?	category				color				bold			onFind()	compilerDictionaryLookup()
		// Fixups
		{	";;",								2,							(u32)((cu8*)&";"),		_ICODE_COMMENT,						false,		_ICAT_COMMENT,			NULL,				false,			null0,	null0,	null0	},

		// x86 instructions
		{	(cs8*)cgc_aaa_instruction,			sizeof(cgc_aaa_instruction) - 1,		false,		_ICODE_LSA_AAA,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_aad2_instruction,			sizeof(cgc_aad2_instruction) - 1,		false,		_ICODE_LSA_AAD2,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_aad_instruction,			sizeof(cgc_aad_instruction) - 1,		false,		_ICODE_LSA_AAD,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_aam2_instruction,			sizeof(cgc_aam2_instruction) - 1,		false,		_ICODE_LSA_AAM2,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_aam_instruction,			sizeof(cgc_aam_instruction) - 1,		false,		_ICODE_LSA_AAM,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_aas_instruction,			sizeof(cgc_aas_instruction) - 1,		false,		_ICODE_LSA_AAS,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_adc_instruction,			sizeof(cgc_adc_instruction) - 1,		false,		_ICODE_LSA_ADC,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_add_instruction,			sizeof(cgc_add_instruction) - 1,		false,		_ICODE_LSA_ADD,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_and_instruction,			sizeof(cgc_and_instruction) - 1,		false,		_ICODE_LSA_AND,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_aprl_instruction,			sizeof(cgc_aprl_instruction) - 1,		false,		_ICODE_LSA_APRL,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_bound_instruction,		sizeof(cgc_bound_instruction) - 1,		false,		_ICODE_LSA_BOUND,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_bsf_instruction,			sizeof(cgc_bsf_instruction) - 1,		false,		_ICODE_LSA_BSF,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_bsr_instruction,			sizeof(cgc_bsr_instruction) - 1,		false,		_ICODE_LSA_BSR,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_bswap_instruction,		sizeof(cgc_bswap_instruction) - 1,		false,		_ICODE_LSA_BSWAP,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_bt_instruction,			sizeof(cgc_bt_instruction) - 1,			false,		_ICODE_LSA_BT,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_btc_instruction,			sizeof(cgc_btc_instruction) - 1,		false,		_ICODE_LSA_BTC,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_btr_instruction,			sizeof(cgc_btr_instruction) - 1,		false,		_ICODE_LSA_BTR,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_bts_instruction,			sizeof(cgc_bts_instruction) - 1,		false,		_ICODE_LSA_BTS,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_call_instruction,			sizeof(cgc_call_instruction) - 1,		false,		_ICODE_LSA_CALL,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_cbw_instruction,			sizeof(cgc_cbw_instruction) - 1,		false,		_ICODE_LSA_CBW,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_cdq_instruction,			sizeof(cgc_cdq_instruction) - 1,		false,		_ICODE_LSA_CDQ,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_cdw_instruction,			sizeof(cgc_cdw_instruction) - 1,		false,		_ICODE_LSA_CDW,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_clc_instruction,			sizeof(cgc_clc_instruction) - 1,		false,		_ICODE_LSA_CLC,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_cld_instruction,			sizeof(cgc_cld_instruction) - 1,		false,		_ICODE_LSA_CLD,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_cli_instruction,			sizeof(cgc_cli_instruction) - 1,		false,		_ICODE_LSA_CLI,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_clts_instruction,			sizeof(cgc_clts_instruction) - 1,		false,		_ICODE_LSA_CLTS,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_cmova_instruction,		sizeof(cgc_cmova_instruction) - 1,		false,		_ICODE_LSA_CMOVA,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_cmovae_instruction,		sizeof(cgc_cmovae_instruction) - 1,		false,		_ICODE_LSA_CMOVAE,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_cmovb_instruction,		sizeof(cgc_cmovb_instruction) - 1,		false,		_ICODE_LSA_CMOVB,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_cmovbe_instruction,		sizeof(cgc_cmovbe_instruction) - 1,		false,		_ICODE_LSA_CMOVBE,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_cmove_instruction,		sizeof(cgc_cmove_instruction) - 1,		false,		_ICODE_LSA_CMOVE,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_cmovg_instruction,		sizeof(cgc_cmovg_instruction) - 1,		false,		_ICODE_LSA_CMOVG,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_cmovge_instruction,		sizeof(cgc_cmovge_instruction) - 1,		false,		_ICODE_LSA_CMOVGE,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_cmovl_instruction,		sizeof(cgc_cmovl_instruction) - 1,		false,		_ICODE_LSA_CMOVL,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_cmovle_instruction,		sizeof(cgc_cmovle_instruction) - 1,		false,		_ICODE_LSA_CMOVLE,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_cmovna_instruction,		sizeof(cgc_cmovna_instruction) - 1,		false,		_ICODE_LSA_CMOVNA,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_cmovnae_instruction,		sizeof(cgc_cmovnae_instruction) - 1,	false,		_ICODE_LSA_CMOVNAE,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_cmovnb_instruction,		sizeof(cgc_cmovnb_instruction) - 1,		false,		_ICODE_LSA_CMOVNB,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_cmovnbe_instruction,		sizeof(cgc_cmovnbe_instruction) - 1,	false,		_ICODE_LSA_CMOVNBE,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_cmovne_instruction,		sizeof(cgc_cmovne_instruction) - 1,		false,		_ICODE_LSA_CMOVNE,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_cmovng_instruction,		sizeof(cgc_cmovng_instruction) - 1,		false,		_ICODE_LSA_CMOVNG,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_cmovnge_instruction,		sizeof(cgc_cmovnge_instruction) - 1,	false,		_ICODE_LSA_CMOVNGE,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_cmovnl_instruction,		sizeof(cgc_cmovnl_instruction) - 1,		false,		_ICODE_LSA_CMOVNL,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_cmovnle_instruction,		sizeof(cgc_cmovnle_instruction) - 1,	false,		_ICODE_LSA_CMOVNLE,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_cmovno_instruction,		sizeof(cgc_cmovno_instruction) - 1,		false,		_ICODE_LSA_CMOVNO,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_cmovnp_instruction,		sizeof(cgc_cmovnp_instruction) - 1,		false,		_ICODE_LSA_CMOVNP,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_cmovns_instruction,		sizeof(cgc_cmovns_instruction) - 1,		false,		_ICODE_LSA_CMOVNS,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_cmovnz_instruction,		sizeof(cgc_cmovnz_instruction) - 1,		false,		_ICODE_LSA_CMOVNZ,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_cmovo_instruction,		sizeof(cgc_cmovo_instruction) - 1,		false,		_ICODE_LSA_CMOVO,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_cmovp_instruction,		sizeof(cgc_cmovp_instruction) - 1,		false,		_ICODE_LSA_CMOVP,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_cmovpe_instruction,		sizeof(cgc_cmovpe_instruction) - 1,		false,		_ICODE_LSA_CMOVPE,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_cmovpo_instruction,		sizeof(cgc_cmovpo_instruction) - 1,		false,		_ICODE_LSA_CMOVPO,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_cmovs_instruction,		sizeof(cgc_cmovs_instruction) - 1,		false,		_ICODE_LSA_CMOVS,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_cmovz_instruction,		sizeof(cgc_cmovz_instruction) - 1,		false,		_ICODE_LSA_CMOVZ,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_cmp_instruction,			sizeof(cgc_cmp_instruction) - 1,		false,		_ICODE_LSA_CMP,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_cmpsb_instruction,		sizeof(cgc_cmpsb_instruction) - 1,		false,		_ICODE_LSA_CMPSB,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_cmpsd_instruction,		sizeof(cgc_cmpsd_instruction) - 1,		false,		_ICODE_LSA_CMPSD,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_cmpsw_instruction,		sizeof(cgc_cmpsw_instruction) - 1,		false,		_ICODE_LSA_CMPSW,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_cmpxchg8b_instruction,	sizeof(cgc_cmpxchg8b_instruction) - 1,	false,		_ICODE_LSA_CMPXCHG8B,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_cmpxchg_instruction,		sizeof(cgc_cmpxchg_instruction) - 1,	false,		_ICODE_LSA_CMPXCHG,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_cpuid_instruction,		sizeof(cgc_cpuid_instruction) - 1,		false,		_ICODE_LSA_CPUID,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_cwde_instruction,			sizeof(cgc_cwde_instruction) - 1,		false,		_ICODE_LSA_CWDE,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_daa_instruction,			sizeof(cgc_daa_instruction) - 1,		false,		_ICODE_LSA_DAA,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_das_instruction,			sizeof(cgc_das_instruction) - 1,		false,		_ICODE_LSA_DAS,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_dec_instruction,			sizeof(cgc_dec_instruction) - 1,		false,		_ICODE_LSA_DEC,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_div_instruction,			sizeof(cgc_div_instruction) - 1,		false,		_ICODE_LSA_DIV,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_emms_instruction,			sizeof(cgc_emms_instruction) - 1,		false,		_ICODE_LSA_EMMS,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_enter_instruction,		sizeof(cgc_enter_instruction) - 1,		false,		_ICODE_LSA_ENTER,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_f2xm1_instruction,		sizeof(cgc_f2xm1_instruction) - 1,		false,		_ICODE_LSA_F2XM1,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fabs_instruction,			sizeof(cgc_fabs_instruction) - 1,		false,		_ICODE_LSA_FABS,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fadd_instruction,			sizeof(cgc_fadd_instruction) - 1,		false,		_ICODE_LSA_FADD,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_faddp_instruction,		sizeof(cgc_faddp_instruction) - 1,		false,		_ICODE_LSA_FADDP,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fbld_instruction,			sizeof(cgc_fbld_instruction) - 1,		false,		_ICODE_LSA_FBLD,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fbstp_instruction,		sizeof(cgc_fbstp_instruction) - 1,		false,		_ICODE_LSA_FBSTP,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fchs_instruction,			sizeof(cgc_fchs_instruction) - 1,		false,		_ICODE_LSA_FCHS,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fclex_instruction,		sizeof(cgc_fclex_instruction) - 1,		false,		_ICODE_LSA_FCLEX,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fcmovb_instruction,		sizeof(cgc_fcmovb_instruction) - 1,		false,		_ICODE_LSA_FCMOVB,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fcmovbe_instruction,		sizeof(cgc_fcmovbe_instruction) - 1,	false,		_ICODE_LSA_FCMOVBE,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fcmove_instruction,		sizeof(cgc_fcmove_instruction) - 1,		false,		_ICODE_LSA_FCMOVE,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fcmovnb_instruction,		sizeof(cgc_fcmovnb_instruction) - 1,	false,		_ICODE_LSA_FCMOVNB,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fcmovnbe_instruction,		sizeof(cgc_fcmovnbe_instruction) - 1,	false,		_ICODE_LSA_FCMOVNBE,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fcmovne_instruction,		sizeof(cgc_fcmovne_instruction) - 1,	false,		_ICODE_LSA_FCMOVNE,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fcmovnu_instruction,		sizeof(cgc_fcmovnu_instruction) - 1,	false,		_ICODE_LSA_FCMOVNU,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fcmovu_instruction,		sizeof(cgc_fcmovu_instruction) - 1,		false,		_ICODE_LSA_FCMOVU,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fcom_instruction,			sizeof(cgc_fcom_instruction) - 1,		false,		_ICODE_LSA_FCOM,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fcomi_instruction,		sizeof(cgc_fcomi_instruction) - 1,		false,		_ICODE_LSA_FCOMI,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fcomip_instruction,		sizeof(cgc_fcomip_instruction) - 1,		false,		_ICODE_LSA_FCOMIP,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fcomp_instruction,		sizeof(cgc_fcomp_instruction) - 1,		false,		_ICODE_LSA_FCOMP,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fcompp_instruction,		sizeof(cgc_fcompp_instruction) - 1,		false,		_ICODE_LSA_FCOMPP,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fcos_instruction,			sizeof(cgc_fcos_instruction) - 1,		false,		_ICODE_LSA_FCOS,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fdecstp_instruction,		sizeof(cgc_fdecstp_instruction) - 1,	false,		_ICODE_LSA_FDECSTP,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fdiv_instruction,			sizeof(cgc_fdiv_instruction) - 1,		false,		_ICODE_LSA_FDIV,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fdivp_instruction,		sizeof(cgc_fdivp_instruction) - 1,		false,		_ICODE_LSA_FDIVP,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fdivr_instruction,		sizeof(cgc_fdivr_instruction) - 1,		false,		_ICODE_LSA_FDIVR,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fdivrp_instruction,		sizeof(cgc_fdivrp_instruction) - 1,		false,		_ICODE_LSA_FDIVRP,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_ffree_instruction,		sizeof(cgc_ffree_instruction) - 1,		false,		_ICODE_LSA_FFREE,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fiadd_instruction,		sizeof(cgc_fiadd_instruction) - 1,		false,		_ICODE_LSA_FIADD,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_ficom_instruction,		sizeof(cgc_ficom_instruction) - 1,		false,		_ICODE_LSA_FICOM,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_ficomp_instruction,		sizeof(cgc_ficomp_instruction) - 1,		false,		_ICODE_LSA_FICOMP,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fidiv_instruction,		sizeof(cgc_fidiv_instruction) - 1,		false,		_ICODE_LSA_FIDIV,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fidivr_instruction,		sizeof(cgc_fidivr_instruction) - 1,		false,		_ICODE_LSA_FIDIVR,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fild_instruction,			sizeof(cgc_fild_instruction) - 1,		false,		_ICODE_LSA_FILD,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fimul_instruction,		sizeof(cgc_fimul_instruction) - 1,		false,		_ICODE_LSA_FIMUL,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fincstp_instruction,		sizeof(cgc_fincstp_instruction) - 1,	false,		_ICODE_LSA_FINCSTP,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_finit_instruction,		sizeof(cgc_finit_instruction) - 1,		false,		_ICODE_LSA_FINIT,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fist_instruction,			sizeof(cgc_fist_instruction) - 1,		false,		_ICODE_LSA_FIST,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fistp_instruction,		sizeof(cgc_fistp_instruction) - 1,		false,		_ICODE_LSA_FISTP,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fisub_instruction,		sizeof(cgc_fisub_instruction) - 1,		false,		_ICODE_LSA_FISUB,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fisubr_instruction,		sizeof(cgc_fisubr_instruction) - 1,		false,		_ICODE_LSA_FISUBR,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fld1_instruction,			sizeof(cgc_fld1_instruction) - 1,		false,		_ICODE_LSA_FLD1,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fld2e_instruction,		sizeof(cgc_fld2e_instruction) - 1,		false,		_ICODE_LSA_FLD2E,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fld2t_instruction,		sizeof(cgc_fld2t_instruction) - 1,		false,		_ICODE_LSA_FLD2T,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fld_instruction,			sizeof(cgc_fld_instruction) - 1,		false,		_ICODE_LSA_FLD,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fldcw_instruction,		sizeof(cgc_fldcw_instruction) - 1,		false,		_ICODE_LSA_FLDCW,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fldenv_instruction,		sizeof(cgc_fldenv_instruction) - 1,		false,		_ICODE_LSA_FLDENV,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fldlg2_instruction,		sizeof(cgc_fldlg2_instruction) - 1,		false,		_ICODE_LSA_FLDLG2,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fldn2_instruction,		sizeof(cgc_fldn2_instruction) - 1,		false,		_ICODE_LSA_FLDN2,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fldpi_instruction,		sizeof(cgc_fldpi_instruction) - 1,		false,		_ICODE_LSA_FLDPI,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fldz_instruction,			sizeof(cgc_fldz_instruction) - 1,		false,		_ICODE_LSA_FLDZ,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fmul_instruction,			sizeof(cgc_fmul_instruction) - 1,		false,		_ICODE_LSA_FMUL,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fmulp_instruction,		sizeof(cgc_fmulp_instruction) - 1,		false,		_ICODE_LSA_FMULP,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fnclex_instruction,		sizeof(cgc_fnclex_instruction) - 1,		false,		_ICODE_LSA_FNCLEX,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fnop_instruction,			sizeof(cgc_fnop_instruction) - 1,		false,		_ICODE_LSA_FNOP,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fpatan_instruction,		sizeof(cgc_fpatan_instruction) - 1,		false,		_ICODE_LSA_FPATAN,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fprem1_instruction,		sizeof(cgc_fprem1_instruction) - 1,		false,		_ICODE_LSA_FPREM1,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fprem_instruction,		sizeof(cgc_fprem_instruction) - 1,		false,		_ICODE_LSA_FPREM,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fptan_instruction,		sizeof(cgc_fptan_instruction) - 1,		false,		_ICODE_LSA_FPTAN,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_frndint_instruction,		sizeof(cgc_frndint_instruction) - 1,	false,		_ICODE_LSA_FRNDINT,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_frstor_instruction,		sizeof(cgc_frstor_instruction) - 1,		false,		_ICODE_LSA_FRSTOR,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fsave_instruction,		sizeof(cgc_fsave_instruction) - 1,		false,		_ICODE_LSA_FSAVE,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fscale_instruction,		sizeof(cgc_fscale_instruction) - 1,		false,		_ICODE_LSA_FSCALE,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fsin_instruction,			sizeof(cgc_fsin_instruction) - 1,		false,		_ICODE_LSA_FSIN,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fsincos_instruction,		sizeof(cgc_fsincos_instruction) - 1,	false,		_ICODE_LSA_FSINCOS,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fsqrt_instruction,		sizeof(cgc_fsqrt_instruction) - 1,		false,		_ICODE_LSA_FSQRT,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fst_instruction,			sizeof(cgc_fst_instruction) - 1,		false,		_ICODE_LSA_FST,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fstcw_instruction,		sizeof(cgc_fstcw_instruction) - 1,		false,		_ICODE_LSA_FSTCW,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fstenv_instruction,		sizeof(cgc_fstenv_instruction) - 1,		false,		_ICODE_LSA_FSTENV,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fstsw_instruction,		sizeof(cgc_fstsw_instruction) - 1,		false,		_ICODE_LSA_FSTSW,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fsub_instruction,			sizeof(cgc_fsub_instruction) - 1,		false,		_ICODE_LSA_FSUB,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fsubp_instruction,		sizeof(cgc_fsubp_instruction) - 1,		false,		_ICODE_LSA_FSUBP,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fsubr_instruction,		sizeof(cgc_fsubr_instruction) - 1,		false,		_ICODE_LSA_FSUBR,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fsubrp_instruction,		sizeof(cgc_fsubrp_instruction) - 1,		false,		_ICODE_LSA_FSUBRP,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_ftst_instruction,			sizeof(cgc_ftst_instruction) - 1,		false,		_ICODE_LSA_FTST,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fucom_instruction,		sizeof(cgc_fucom_instruction) - 1,		false,		_ICODE_LSA_FUCOM,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fucomi_instruction,		sizeof(cgc_fucomi_instruction) - 1,		false,		_ICODE_LSA_FUCOMI,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fucomip_instruction,		sizeof(cgc_fucomip_instruction) - 1,	false,		_ICODE_LSA_FUCOMIP,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fucomp_instruction,		sizeof(cgc_fucomp_instruction) - 1,		false,		_ICODE_LSA_FUCOMP,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fucompp_instruction,		sizeof(cgc_fucompp_instruction) - 1,	false,		_ICODE_LSA_FUCOMPP,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fwait_instruction,		sizeof(cgc_fwait_instruction) - 1,		false,		_ICODE_LSA_FWAIT,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fxam_instruction,			sizeof(cgc_fxam_instruction) - 1,		false,		_ICODE_LSA_FXAM,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fxch_instruction,			sizeof(cgc_fxch_instruction) - 1,		false,		_ICODE_LSA_FXCH,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fxtract_instruction,		sizeof(cgc_fxtract_instruction) - 1,	false,		_ICODE_LSA_FXTRACT,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fyl2x_instruction,		sizeof(cgc_fyl2x_instruction) - 1,		false,		_ICODE_LSA_FYL2X,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fyl2xp1_instruction,		sizeof(cgc_fyl2xp1_instruction) - 1,	false,		_ICODE_LSA_FYL2XP1,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_hlt_instruction,			sizeof(cgc_hlt_instruction) - 1,		false,		_ICODE_LSA_HLT,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_idiv_instruction,			sizeof(cgc_idiv_instruction) - 1,		false,		_ICODE_LSA_IDIV,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_imul_instruction,			sizeof(cgc_imul_instruction) - 1,		false,		_ICODE_LSA_IMUL,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_in_instruction,			sizeof(cgc_in_instruction) - 1,			false,		_ICODE_LSA_IN,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_inc_instruction,			sizeof(cgc_inc_instruction) - 1,		false,		_ICODE_LSA_INC,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_ins_instruction,			sizeof(cgc_ins_instruction) - 1,		false,		_ICODE_LSA_INS,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_insb_instruction,			sizeof(cgc_insb_instruction) - 1,		false,		_ICODE_LSA_INSB,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_insd_instruction,			sizeof(cgc_insd_instruction) - 1,		false,		_ICODE_LSA_INSD,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_insw_instruction,			sizeof(cgc_insw_instruction) - 1,		false,		_ICODE_LSA_INSW,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_int3_instruction,			sizeof(cgc_int3_instruction) - 1,		false,		_ICODE_LSA_INT3,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_int_instruction,			sizeof(cgc_int_instruction) - 1,		false,		_ICODE_LSA_INT,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_into_instruction,			sizeof(cgc_into_instruction) - 1,		false,		_ICODE_LSA_INTO,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_invd_instruction,			sizeof(cgc_invd_instruction) - 1,		false,		_ICODE_LSA_INVD,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_invlpg_instruction,		sizeof(cgc_invlpg_instruction) - 1,		false,		_ICODE_LSA_INVLPG,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_iret_instruction,			sizeof(cgc_iret_instruction) - 1,		false,		_ICODE_LSA_IRET,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_iretd_instruction,		sizeof(cgc_iretd_instruction) - 1,		false,		_ICODE_LSA_IRETD,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_ja_instruction,			sizeof(cgc_ja_instruction) - 1,			false,		_ICODE_LSA_JA,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_jae_instruction,			sizeof(cgc_jae_instruction) - 1,		false,		_ICODE_LSA_JAE,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_jb_instruction,			sizeof(cgc_jb_instruction) - 1,			false,		_ICODE_LSA_JB,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_jbe_instruction,			sizeof(cgc_jbe_instruction) - 1,		false,		_ICODE_LSA_JBE,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_je_instruction,			sizeof(cgc_je_instruction) - 1,			false,		_ICODE_LSA_JE,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_jg_instruction,			sizeof(cgc_jg_instruction) - 1,			false,		_ICODE_LSA_JG,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_jge_instruction,			sizeof(cgc_jge_instruction) - 1,		false,		_ICODE_LSA_JGE,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_jl_instruction,			sizeof(cgc_jl_instruction) - 1,			false,		_ICODE_LSA_JL,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_jle_instruction,			sizeof(cgc_jle_instruction) - 1,		false,		_ICODE_LSA_JLE,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_jmp_instruction,			sizeof(cgc_jmp_instruction) - 1,		false,		_ICODE_LSA_JMP,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_jna_instruction,			sizeof(cgc_jna_instruction) - 1,		false,		_ICODE_LSA_JNA,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_jnae_instruction,			sizeof(cgc_jnae_instruction) - 1,		false,		_ICODE_LSA_JNAE,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_jnb_instruction,			sizeof(cgc_jnb_instruction) - 1,		false,		_ICODE_LSA_JNB,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_jnbe_instruction,			sizeof(cgc_jnbe_instruction) - 1,		false,		_ICODE_LSA_JNBE,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_jne_instruction,			sizeof(cgc_jne_instruction) - 1,		false,		_ICODE_LSA_JNE,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_jng_instruction,			sizeof(cgc_jng_instruction) - 1,		false,		_ICODE_LSA_JNG,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_jnge_instruction,			sizeof(cgc_jnge_instruction) - 1,		false,		_ICODE_LSA_JNGE,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_jnl_instruction,			sizeof(cgc_jnl_instruction) - 1,		false,		_ICODE_LSA_JNL,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_jnle_instruction,			sizeof(cgc_jnle_instruction) - 1,		false,		_ICODE_LSA_JNLE,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_jno_instruction,			sizeof(cgc_jno_instruction) - 1,		false,		_ICODE_LSA_JNO,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_jnp_instruction,			sizeof(cgc_jnp_instruction) - 1,		false,		_ICODE_LSA_JNP,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_jns_instruction,			sizeof(cgc_jns_instruction) - 1,		false,		_ICODE_LSA_JNS,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_jnz_instruction,			sizeof(cgc_jnz_instruction) - 1,		false,		_ICODE_LSA_JNZ,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_jo_instruction,			sizeof(cgc_jo_instruction) - 1,			false,		_ICODE_LSA_JO,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_jp_instruction,			sizeof(cgc_jp_instruction) - 1,			false,		_ICODE_LSA_JP,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_jpe_instruction,			sizeof(cgc_jpe_instruction) - 1,		false,		_ICODE_LSA_JPE,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_jpo_instruction,			sizeof(cgc_jpo_instruction) - 1,		false,		_ICODE_LSA_JPO,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_js_instruction,			sizeof(cgc_js_instruction) - 1,			false,		_ICODE_LSA_JS,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_jz_instruction,			sizeof(cgc_jz_instruction) - 1,			false,		_ICODE_LSA_JZ,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_lahf_instruction,			sizeof(cgc_lahf_instruction) - 1,		false,		_ICODE_LSA_LAHF,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_lar_instruction,			sizeof(cgc_lar_instruction) - 1,		false,		_ICODE_LSA_LAR,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_lds_instruction,			sizeof(cgc_lds_instruction) - 1,		false,		_ICODE_LSA_LDS,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_lea_instruction,			sizeof(cgc_lea_instruction) - 1,		false,		_ICODE_LSA_LEA,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_leave_instruction,		sizeof(cgc_leave_instruction) - 1,		false,		_ICODE_LSA_LEAVE,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_les_instruction,			sizeof(cgc_les_instruction) - 1,		false,		_ICODE_LSA_LES,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_lfs_instruction,			sizeof(cgc_lfs_instruction) - 1,		false,		_ICODE_LSA_LFS,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_lgdt_instruction,			sizeof(cgc_lgdt_instruction) - 1,		false,		_ICODE_LSA_LGDT,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_lgs_instruction,			sizeof(cgc_lgs_instruction) - 1,		false,		_ICODE_LSA_LGS,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_lidt_instruction,			sizeof(cgc_lidt_instruction) - 1,		false,		_ICODE_LSA_LIDT,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_lldt_instruction,			sizeof(cgc_lldt_instruction) - 1,		false,		_ICODE_LSA_LLDT,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_lmsw_instruction,			sizeof(cgc_lmsw_instruction) - 1,		false,		_ICODE_LSA_LMSW,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_lock_instruction,			sizeof(cgc_lock_instruction) - 1,		false,		_ICODE_LSA_LOCK,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_lods_instruction,			sizeof(cgc_lods_instruction) - 1,		false,		_ICODE_LSA_LODS,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_lodsb_instruction,		sizeof(cgc_lodsb_instruction) - 1,		false,		_ICODE_LSA_LODSB,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_lodsd_instruction,		sizeof(cgc_lodsd_instruction) - 1,		false,		_ICODE_LSA_LODSD,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_lodsw_instruction,		sizeof(cgc_lodsw_instruction) - 1,		false,		_ICODE_LSA_LODSW,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_loop_instruction,			sizeof(cgc_loop_instruction) - 1,		false,		_ICODE_LSA_LOOP,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_loope_instruction,		sizeof(cgc_loope_instruction) - 1,		false,		_ICODE_LSA_LOOPE,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_loopne_instruction,		sizeof(cgc_loopne_instruction) - 1,		false,		_ICODE_LSA_LOOPNE,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_loopnz_instruction,		sizeof(cgc_loopnz_instruction) - 1,		false,		_ICODE_LSA_LOOPNZ,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_loopz_instruction,		sizeof(cgc_loopz_instruction) - 1,		false,		_ICODE_LSA_LOOPZ,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_lsl_instruction,			sizeof(cgc_lsl_instruction) - 1,		false,		_ICODE_LSA_LSL,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_lss_instruction,			sizeof(cgc_lss_instruction) - 1,		false,		_ICODE_LSA_LSS,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_ltr_instruction,			sizeof(cgc_ltr_instruction) - 1,		false,		_ICODE_LSA_LTR,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_mov_instruction,			sizeof(cgc_mov_instruction) - 1,		false,		_ICODE_LSA_MOV,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_movs_instruction,			sizeof(cgc_movs_instruction) - 1,		false,		_ICODE_LSA_MOVS,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_movsb_instruction,		sizeof(cgc_movsb_instruction) - 1,		false,		_ICODE_LSA_MOVSB,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_movsd_instruction,		sizeof(cgc_movsd_instruction) - 1,		false,		_ICODE_LSA_MOVSD,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_movsw_instruction,		sizeof(cgc_movsw_instruction) - 1,		false,		_ICODE_LSA_MOVSW,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_movsx_instruction,		sizeof(cgc_movsx_instruction) - 1,		false,		_ICODE_LSA_MOVSX,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_movzx_instruction,		sizeof(cgc_movzx_instruction) - 1,		false,		_ICODE_LSA_MOVZX,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_mul_instruction,			sizeof(cgc_mul_instruction) - 1,		false,		_ICODE_LSA_MUL,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_neg_instruction,			sizeof(cgc_neg_instruction) - 1,		false,		_ICODE_LSA_NEG,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_nop_instruction,			sizeof(cgc_nop_instruction) - 1,		false,		_ICODE_LSA_NOP,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_not_instruction,			sizeof(cgc_not_instruction) - 1,		false,		_ICODE_LSA_NOT,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_or_instruction,			sizeof(cgc_or_instruction) - 1,			false,		_ICODE_LSA_OR,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_out_instruction,			sizeof(cgc_out_instruction) - 1,		false,		_ICODE_LSA_OUT,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_outs_instruction,			sizeof(cgc_outs_instruction) - 1,		false,		_ICODE_LSA_OUTS,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_outsb_instruction,		sizeof(cgc_outsb_instruction) - 1,		false,		_ICODE_LSA_OUTSB,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_outsd_instruction,		sizeof(cgc_outsd_instruction) - 1,		false,		_ICODE_LSA_OUTSD,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_outsw_instruction,		sizeof(cgc_outsw_instruction) - 1,		false,		_ICODE_LSA_OUTSW,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_pop_instruction,			sizeof(cgc_pop_instruction) - 1,		false,		_ICODE_LSA_POP,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_popa_instruction,			sizeof(cgc_popa_instruction) - 1,		false,		_ICODE_LSA_POPA,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_popad_instruction,		sizeof(cgc_popad_instruction) - 1,		false,		_ICODE_LSA_POPAD,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_popf_instruction,			sizeof(cgc_popf_instruction) - 1,		false,		_ICODE_LSA_POPF,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_popfd_instruction,		sizeof(cgc_popfd_instruction) - 1,		false,		_ICODE_LSA_POPFD,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_prefetch0_instruction,	sizeof(cgc_prefetch0_instruction) - 1,	false,		_ICODE_LSA_PREFETCH0,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_prefetch1_instruction,	sizeof(cgc_prefetch1_instruction) - 1,	false,		_ICODE_LSA_PREFETCH1,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_prefetch2_instruction,	sizeof(cgc_prefetch2_instruction) - 1,	false,		_ICODE_LSA_PREFETCH2,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_prefetchnt_instruction,	sizeof(cgc_prefetchnt_instruction) - 1, false,		_ICODE_LSA_PREFETCHNT,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_push_instruction,			sizeof(cgc_push_instruction) - 1,		false,		_ICODE_LSA_PUSH,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_pusha_instruction,		sizeof(cgc_pusha_instruction) - 1,		false,		_ICODE_LSA_PUSHA,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_pushad_instruction,		sizeof(cgc_pushad_instruction) - 1,		false,		_ICODE_LSA_PUSHAD,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_pushf_instruction,		sizeof(cgc_pushf_instruction) - 1,		false,		_ICODE_LSA_PUSHF,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_pushfd_instruction,		sizeof(cgc_pushfd_instruction) - 1,		false,		_ICODE_LSA_PUSHFD,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_rcl_instruction,			sizeof(cgc_rcl_instruction) - 1,		false,		_ICODE_LSA_RCL,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_rcr_instruction,			sizeof(cgc_rcr_instruction) - 1,		false,		_ICODE_LSA_RCR,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_rdmsr_instruction,		sizeof(cgc_rdmsr_instruction) - 1,		false,		_ICODE_LSA_RDMSR,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_rdpmc_instruction,		sizeof(cgc_rdpmc_instruction) - 1,		false,		_ICODE_LSA_RDPMC,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_rdtsc_instruction,		sizeof(cgc_rdtsc_instruction) - 1,		false,		_ICODE_LSA_RDTSC,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_repe_instruction,			sizeof(cgc_repe_instruction) - 1,		false,		_ICODE_LSA_REPE,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_repne_instruction,		sizeof(cgc_repne_instruction) - 1,		false,		_ICODE_LSA_REPNE,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_repnz_instruction,		sizeof(cgc_repnz_instruction) - 1,		false,		_ICODE_LSA_REPNZ,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_repz_instruction,			sizeof(cgc_repz_instruction) - 1,		false,		_ICODE_LSA_REPZ,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_ret_instruction,			sizeof(cgc_ret_instruction) - 1,		false,		_ICODE_LSA_RET,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_rol_instruction,			sizeof(cgc_rol_instruction) - 1,		false,		_ICODE_LSA_ROL,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_ror_instruction,			sizeof(cgc_ror_instruction) - 1,		false,		_ICODE_LSA_ROR,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_sahf_instruction,			sizeof(cgc_sahf_instruction) - 1,		false,		_ICODE_LSA_SAHF,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_sar_instruction,			sizeof(cgc_sar_instruction) - 1,		false,		_ICODE_LSA_SAR,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_sbb_instruction,			sizeof(cgc_sbb_instruction) - 1,		false,		_ICODE_LSA_SBB,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_scas_instruction,			sizeof(cgc_scas_instruction) - 1,		false,		_ICODE_LSA_SCAS,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_scasb_instruction,		sizeof(cgc_scasb_instruction) - 1,		false,		_ICODE_LSA_SCASB,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_scasd_instruction,		sizeof(cgc_scasd_instruction) - 1,		false,		_ICODE_LSA_SCASD,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_scasw_instruction,		sizeof(cgc_scasw_instruction) - 1,		false,		_ICODE_LSA_SCASW,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_seta_instruction,			sizeof(cgc_seta_instruction) - 1,		false,		_ICODE_LSA_SETA,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_setae_instruction,		sizeof(cgc_setae_instruction) - 1,		false,		_ICODE_LSA_SETAE,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_setb_instruction,			sizeof(cgc_setb_instruction) - 1,		false,		_ICODE_LSA_SETB,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_setbe_instruction,		sizeof(cgc_setbe_instruction) - 1,		false,		_ICODE_LSA_SETBE,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_sete_instruction,			sizeof(cgc_sete_instruction) - 1,		false,		_ICODE_LSA_SETE,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_setg_instruction,			sizeof(cgc_setg_instruction) - 1,		false,		_ICODE_LSA_SETG,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_setge_instruction,		sizeof(cgc_setge_instruction) - 1,		false,		_ICODE_LSA_SETGE,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_setl_instruction,			sizeof(cgc_setl_instruction) - 1,		false,		_ICODE_LSA_SETL,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_setle_instruction,		sizeof(cgc_setle_instruction) - 1,		false,		_ICODE_LSA_SETLE,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_setna_instruction,		sizeof(cgc_setna_instruction) - 1,		false,		_ICODE_LSA_SETNA,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_setnae_instruction,		sizeof(cgc_setnae_instruction) - 1,		false,		_ICODE_LSA_SETNAE,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_setnb_instruction,		sizeof(cgc_setnb_instruction) - 1,		false,		_ICODE_LSA_SETNB,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_setnbe_instruction,		sizeof(cgc_setnbe_instruction) - 1,		false,		_ICODE_LSA_SETNBE,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_setne_instruction,		sizeof(cgc_setne_instruction) - 1,		false,		_ICODE_LSA_SETNE,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_setng_instruction,		sizeof(cgc_setng_instruction) - 1,		false,		_ICODE_LSA_SETNG,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_setnge_instruction,		sizeof(cgc_setnge_instruction) - 1,		false,		_ICODE_LSA_SETNGE,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_setnl_instruction,		sizeof(cgc_setnl_instruction) - 1,		false,		_ICODE_LSA_SETNL,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_setnle_instruction,		sizeof(cgc_setnle_instruction) - 1,		false,		_ICODE_LSA_SETNLE,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_setno_instruction,		sizeof(cgc_setno_instruction) - 1,		false,		_ICODE_LSA_SETNO,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_setnp_instruction,		sizeof(cgc_setnp_instruction) - 1,		false,		_ICODE_LSA_SETNP,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_setns_instruction,		sizeof(cgc_setns_instruction) - 1,		false,		_ICODE_LSA_SETNS,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_setnz_instruction,		sizeof(cgc_setnz_instruction) - 1,		false,		_ICODE_LSA_SETNZ,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_seto_instruction,			sizeof(cgc_seto_instruction) - 1,		false,		_ICODE_LSA_SETO,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_setp_instruction,			sizeof(cgc_setp_instruction) - 1,		false,		_ICODE_LSA_SETP,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_setpe_instruction,		sizeof(cgc_setpe_instruction) - 1,		false,		_ICODE_LSA_SETPE,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_setpo_instruction,		sizeof(cgc_setpo_instruction) - 1,		false,		_ICODE_LSA_SETPO,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_sets_instruction,			sizeof(cgc_sets_instruction) - 1,		false,		_ICODE_LSA_SETS,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_setz_instruction,			sizeof(cgc_setz_instruction) - 1,		false,		_ICODE_LSA_SETZ,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_sgdt_instruction,			sizeof(cgc_sgdt_instruction) - 1,		false,		_ICODE_LSA_SGDT,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_shl_instruction,			sizeof(cgc_shl_instruction) - 1,		false,		_ICODE_LSA_SHL,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_shld_instruction,			sizeof(cgc_shld_instruction) - 1,		false,		_ICODE_LSA_SHLD,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_shr_instruction,			sizeof(cgc_shr_instruction) - 1,		false,		_ICODE_LSA_SHR,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_shrd_instruction,			sizeof(cgc_shrd_instruction) - 1,		false,		_ICODE_LSA_SHRD,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_sidt_instruction,			sizeof(cgc_sidt_instruction) - 1,		false,		_ICODE_LSA_SIDT,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_sldt_instruction,			sizeof(cgc_sldt_instruction) - 1,		false,		_ICODE_LSA_SLDT,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_smsw_instruction,			sizeof(cgc_smsw_instruction) - 1,		false,		_ICODE_LSA_SMSW,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_stc_instruction,			sizeof(cgc_stc_instruction) - 1,		false,		_ICODE_LSA_STC,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_std_instruction,			sizeof(cgc_std_instruction) - 1,		false,		_ICODE_LSA_STD,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_sti_instruction,			sizeof(cgc_sti_instruction) - 1,		false,		_ICODE_LSA_STI,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_stos_instruction,			sizeof(cgc_stos_instruction) - 1,		false,		_ICODE_LSA_STOS,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_stosb_instruction,		sizeof(cgc_stosb_instruction) - 1,		false,		_ICODE_LSA_STOSB,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_stosd_instruction,		sizeof(cgc_stosd_instruction) - 1,		false,		_ICODE_LSA_STOSD,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_stosw_instruction,		sizeof(cgc_stosw_instruction) - 1,		false,		_ICODE_LSA_STOSW,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_str_instruction,			sizeof(cgc_str_instruction) - 1,		false,		_ICODE_LSA_STR,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_sub_instruction,			sizeof(cgc_sub_instruction) - 1,		false,		_ICODE_LSA_SUB,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_sysenter_instruction,		sizeof(cgc_sysenter_instruction) - 1,	false,		_ICODE_LSA_SYSENTER,				true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_sysexit_instruction,		sizeof(cgc_sysexit_instruction) - 1,	false,		_ICODE_LSA_SYSEXIT,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_test_instruction,			sizeof(cgc_test_instruction) - 1,		false,		_ICODE_LSA_TEST,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_ud2_instruction,			sizeof(cgc_ud2_instruction) - 1,		false,		_ICODE_LSA_UD2,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_verr_instruction,			sizeof(cgc_verr_instruction) - 1,		false,		_ICODE_LSA_VERR,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_verw_instruction,			sizeof(cgc_verw_instruction) - 1,		false,		_ICODE_LSA_VERW,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_wbinvd_instruction,		sizeof(cgc_wbinvd_instruction) - 1,		false,		_ICODE_LSA_WBINVD,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_wrmsr_instruction,		sizeof(cgc_wrmsr_instruction) - 1,		false,		_ICODE_LSA_WRMSR,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_xadd_instruction,			sizeof(cgc_xadd_instruction) - 1,		false,		_ICODE_LSA_XADD,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_xchg_instruction,			sizeof(cgc_xchg_instruction) - 1,		false,		_ICODE_LSA_XCHG,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_xlat_instruction,			sizeof(cgc_xlat_instruction) - 1,		false,		_ICODE_LSA_XLAT,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_xlatb_instruction,		sizeof(cgc_xlatb_instruction) - 1,		false,		_ICODE_LSA_XLATB,					true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_xor_instruction,			sizeof(cgc_xor_instruction) - 1,		false,		_ICODE_LSA_XOR,						true,		_ICAT_INSTRUCTION,		&colorDefault,		false,			null0,	null0,	null0	},

		{	(cs8*)cgc_ptr_tbyte,				sizeof(cgc_ptr_tbyte) - 1,				false,		_ICODE_PTR_TBYTE,					false,		_ICAT_POINTER_SIZE,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_ptr_dqword,				sizeof(cgc_ptr_dqword) - 1,				false,		_ICODE_PTR_DQWORD,					false,		_ICAT_POINTER_SIZE,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_ptr_qword,				sizeof(cgc_ptr_qword) - 1,				false,		_ICODE_PTR_QWORD,					false,		_ICAT_POINTER_SIZE,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_ptr_dword,				sizeof(cgc_ptr_dword) - 1,				false,		_ICODE_PTR_DWORD,					false,		_ICAT_POINTER_SIZE,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_ptr_word,					sizeof(cgc_ptr_word) - 1,				false,		_ICODE_PTR_WORD,					false,		_ICAT_POINTER_SIZE,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_ptr_byte,					sizeof(cgc_ptr_byte) - 1,				false,		_ICODE_PTR_BYTE,					false,		_ICAT_POINTER_SIZE,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_ptr_m16_16,				sizeof(cgc_ptr_m16_16) - 1,				false,		_ICODE_PTR_M16_16,					false,		_ICAT_POINTER_SIZE,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_ptr_m16_32,				sizeof(cgc_ptr_m16_32) - 1,				false,		_ICODE_PTR_M16_32,					false,		_ICAT_POINTER_SIZE,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_ptr_f32,					sizeof(cgc_ptr_f32) - 1,				false,		_ICODE_PTR_F32,						false,		_ICAT_POINTER_SIZE,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_ptr_f64,					sizeof(cgc_ptr_f64) - 1,				false,		_ICODE_PTR_F64,						false,		_ICAT_POINTER_SIZE,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_ptr_f80,					sizeof(cgc_ptr_f80) - 1,				false,		_ICODE_PTR_F80,						false,		_ICAT_POINTER_SIZE,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_ptr_s16,					sizeof(cgc_ptr_s16) - 1,				false,		_ICODE_PTR_S16,						false,		_ICAT_POINTER_SIZE,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_ptr_s32,					sizeof(cgc_ptr_s32) - 1,				false,		_ICODE_PTR_S32,						false,		_ICAT_POINTER_SIZE,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_ptr_s64,					sizeof(cgc_ptr_s64) - 1,				false,		_ICODE_PTR_S64,						false,		_ICAT_POINTER_SIZE,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_ptr_m80,					sizeof(cgc_ptr_m80) - 1,				false,		_ICODE_PTR_M80,						false,		_ICAT_POINTER_SIZE,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_ptr_mmx,					sizeof(cgc_ptr_mmx) - 1,				false,		_ICODE_PTR_MMX,						false,		_ICAT_POINTER_SIZE,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_ptr_xmmx,					sizeof(cgc_ptr_xmmx) - 1,				false,		_ICODE_PTR_XMMX,					false,		_ICAT_POINTER_SIZE,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_ptr_fpu,					sizeof(cgc_ptr_fpu) - 1,				false,		_ICODE_PTR_FPU,						false,		_ICAT_POINTER_SIZE,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_ptr_6byte,				sizeof(cgc_ptr_6byte) - 1,				false,		_ICODE_PTR_6BYTE,					false,		_ICAT_POINTER_SIZE,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_ptr_10byte,				sizeof(cgc_ptr_10byte) - 1,				false,		_ICODE_PTR_10BYTE,					false,		_ICAT_POINTER_SIZE,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_ptr_14byte,				sizeof(cgc_ptr_14byte) - 1,				false,		_ICODE_PTR_14BYTE,					false,		_ICAT_POINTER_SIZE,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_ptr_28byte,				sizeof(cgc_ptr_28byte) - 1,				false,		_ICODE_PTR_28BYTE,					false,		_ICAT_POINTER_SIZE,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_ptr_94byte,				sizeof(cgc_ptr_94byte) - 1,				false,		_ICODE_PTR_94BYTE,					false,		_ICAT_POINTER_SIZE,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_ptr_108byte,				sizeof(cgc_ptr_108byte) - 1,			false,		_ICODE_PTR_108BYTE,					false,		_ICAT_POINTER_SIZE,		&colorDefault,		false,			null0,	null0,	null0	},
																																																									  
		{	(cs8*)cgc_cs_reg,					sizeof(cgc_cs_reg) - 1,					false,		_ICODE_CS,							false,		_ICAT_SEGMENT_REGISTER,	&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_ds_reg,					sizeof(cgc_ds_reg) - 1,					false,		_ICODE_DS,							false,		_ICAT_SEGMENT_REGISTER,	&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_es_reg,					sizeof(cgc_es_reg) - 1,					false,		_ICODE_ES,							false,		_ICAT_SEGMENT_REGISTER,	&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_fs_reg,					sizeof(cgc_fs_reg) - 1,					false,		_ICODE_FS,							false,		_ICAT_SEGMENT_REGISTER,	&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_gs_reg,					sizeof(cgc_gs_reg) - 1,					false,		_ICODE_GS,							false,		_ICAT_SEGMENT_REGISTER,	&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_ss_reg,					sizeof(cgc_ss_reg) - 1,					false,		_ICODE_SS,							false,		_ICAT_SEGMENT_REGISTER,	&colorDefault,		false,			null0,	null0,	null0	},
																																																									  
		{	(cs8*)cgc_al_reg,					sizeof(cgc_al_reg) - 1,					false,		_ICODE_AL,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_bl_reg,					sizeof(cgc_bl_reg) - 1,					false,		_ICODE_BL,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_cl_reg,					sizeof(cgc_cl_reg) - 1,					false,		_ICODE_CL,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_dl_reg,					sizeof(cgc_dl_reg) - 1,					false,		_ICODE_DL,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_ah_reg,					sizeof(cgc_ah_reg) - 1,					false,		_ICODE_AH,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_bh_reg,					sizeof(cgc_bh_reg) - 1,					false,		_ICODE_BH,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_ch_reg,					sizeof(cgc_ch_reg) - 1,					false,		_ICODE_CH,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_dh_reg,					sizeof(cgc_dh_reg) - 1,					false,		_ICODE_DH,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,	null0,	null0	},
																																																									  
		{	(cs8*)cgc_ax_reg,					sizeof(cgc_ax_reg) - 1,					false,		_ICODE_AX,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_bx_reg,					sizeof(cgc_bx_reg) - 1,					false,		_ICODE_BX,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_cx_reg,					sizeof(cgc_cx_reg) - 1,					false,		_ICODE_CX,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_dx_reg,					sizeof(cgc_dx_reg) - 1,					false,		_ICODE_DX,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_si_reg,					sizeof(cgc_si_reg) - 1,					false,		_ICODE_SI,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_di_reg,					sizeof(cgc_di_reg) - 1,					false,		_ICODE_DI,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_bp_reg,					sizeof(cgc_bp_reg) - 1,					false,		_ICODE_BP,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_sp_reg,					sizeof(cgc_sp_reg) - 1,					false,		_ICODE_SP,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_ip_reg,					sizeof(cgc_ip_reg) - 1,					false,		_ICODE_IP,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,	null0,	null0	},
																																																									  
		{	(cs8*)cgc_eax_reg,					sizeof(cgc_eax_reg) - 1,				false,		_ICODE_EAX,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_ebx_reg,					sizeof(cgc_ebx_reg) - 1,				false,		_ICODE_EBX,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_ecx_reg,					sizeof(cgc_ecx_reg) - 1,				false,		_ICODE_ECX,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_edx_reg,					sizeof(cgc_edx_reg) - 1,				false,		_ICODE_EDX,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_esi_reg,					sizeof(cgc_esi_reg) - 1,				false,		_ICODE_ESI,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_edi_reg,					sizeof(cgc_edi_reg) - 1,				false,		_ICODE_EDI,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_ebp_reg,					sizeof(cgc_ebp_reg) - 1,				false,		_ICODE_EBP,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_esp_reg,					sizeof(cgc_esp_reg) - 1,				false,		_ICODE_ESP,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_eip_reg,					sizeof(cgc_eip_reg) - 1,				false,		_ICODE_EIP,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,	null0,	null0	},
																																																									  
		{	(cs8*)cgc_cr0_reg,					sizeof(cgc_cr0_reg) - 1,				false,		_ICODE_CR0,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_cr1_reg,					sizeof(cgc_cr1_reg) - 1,				false,		_ICODE_CR1,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_cr2_reg,					sizeof(cgc_cr2_reg) - 1,				false,		_ICODE_CR2,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_cr3_reg,					sizeof(cgc_cr3_reg) - 1,				false,		_ICODE_CR3,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_cr4_reg,					sizeof(cgc_cr4_reg) - 1,				false,		_ICODE_CR4,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_cr5_reg,					sizeof(cgc_cr5_reg) - 1,				false,		_ICODE_CR5,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_cr6_reg,					sizeof(cgc_cr6_reg) - 1,				false,		_ICODE_CR6,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_cr7_reg,					sizeof(cgc_cr7_reg) - 1,				false,		_ICODE_CR7,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,	null0,	null0	},
																																																									  
		{	(cs8*)cgc_dr0_reg,					sizeof(cgc_dr0_reg) - 1,				false,		_ICODE_DR0,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_dr1_reg,					sizeof(cgc_dr1_reg) - 1,				false,		_ICODE_DR1,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_dr2_reg,					sizeof(cgc_dr2_reg) - 1,				false,		_ICODE_DR2,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_dr3_reg,					sizeof(cgc_dr3_reg) - 1,				false,		_ICODE_DR3,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_dr4_reg,					sizeof(cgc_dr4_reg) - 1,				false,		_ICODE_DR4,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_dr5_reg,					sizeof(cgc_dr5_reg) - 1,				false,		_ICODE_DR5,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_dr6_reg,					sizeof(cgc_dr6_reg) - 1,				false,		_ICODE_DR6,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_dr7_reg,					sizeof(cgc_dr7_reg) - 1,				false,		_ICODE_DR7,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,	null0,	null0	},
																																																									  
		{	(cs8*)cgc_tr0_reg,					sizeof(cgc_tr0_reg) - 1,				false,		_ICODE_TR0,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_tr1_reg,					sizeof(cgc_tr1_reg) - 1,				false,		_ICODE_TR1,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_tr2_reg,					sizeof(cgc_tr2_reg) - 1,				false,		_ICODE_TR2,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_tr3_reg,					sizeof(cgc_tr3_reg) - 1,				false,		_ICODE_TR3,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_tr4_reg,					sizeof(cgc_tr4_reg) - 1,				false,		_ICODE_TR4,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_tr5_reg,					sizeof(cgc_tr5_reg) - 1,				false,		_ICODE_TR5,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_tr6_reg,					sizeof(cgc_tr6_reg) - 1,				false,		_ICODE_TR6,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_tr7_reg,					sizeof(cgc_tr7_reg) - 1,				false,		_ICODE_TR7,							false,		_ICAT_REGISTER,			&colorDefault,		false,			null0,	null0,	null0	},
																																																									  
		{	(cs8*)cgc_st0_reg,					sizeof(cgc_st0_reg) - 1,				false,		_ICODE_ST0,							false,		_ICAT_FPU_REGISTER,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_st1_reg,					sizeof(cgc_st1_reg) - 1,				false,		_ICODE_ST1,							false,		_ICAT_FPU_REGISTER,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_st2_reg,					sizeof(cgc_st2_reg) - 1,				false,		_ICODE_ST2,							false,		_ICAT_FPU_REGISTER,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_st3_reg,					sizeof(cgc_st3_reg) - 1,				false,		_ICODE_ST3,							false,		_ICAT_FPU_REGISTER,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_st4_reg,					sizeof(cgc_st4_reg) - 1,				false,		_ICODE_ST4,							false,		_ICAT_FPU_REGISTER,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_st5_reg,					sizeof(cgc_st5_reg) - 1,				false,		_ICODE_ST5,							false,		_ICAT_FPU_REGISTER,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_st6_reg,					sizeof(cgc_st6_reg) - 1,				false,		_ICODE_ST6,							false,		_ICAT_FPU_REGISTER,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_st7_reg,					sizeof(cgc_st7_reg) - 1,				false,		_ICODE_ST7,							false,		_ICAT_FPU_REGISTER,		&colorDefault,		false,			null0,	null0,	null0	},
																																																									  
		{	(cs8*)cgc_mm0_reg,					sizeof(cgc_mm0_reg) - 1,				false,		_ICODE_MM0,							false,		_ICAT_MMX_REGISTER,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_mm1_reg,					sizeof(cgc_mm1_reg) - 1,				false,		_ICODE_MM1,							false,		_ICAT_MMX_REGISTER,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_mm2_reg,					sizeof(cgc_mm2_reg) - 1,				false,		_ICODE_MM2,							false,		_ICAT_MMX_REGISTER,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_mm3_reg,					sizeof(cgc_mm3_reg) - 1,				false,		_ICODE_MM3,							false,		_ICAT_MMX_REGISTER,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_mm4_reg,					sizeof(cgc_mm4_reg) - 1,				false,		_ICODE_MM4,							false,		_ICAT_MMX_REGISTER,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_mm5_reg,					sizeof(cgc_mm5_reg) - 1,				false,		_ICODE_MM5,							false,		_ICAT_MMX_REGISTER,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_mm6_reg,					sizeof(cgc_mm6_reg) - 1,				false,		_ICODE_MM6,							false,		_ICAT_MMX_REGISTER,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_mm7_reg,					sizeof(cgc_mm7_reg) - 1,				false,		_ICODE_MM7,							false,		_ICAT_MMX_REGISTER,		&colorDefault,		false,			null0,	null0,	null0	},
																																																									  
		{	(cs8*)cgc_xmm0_reg,					sizeof(cgc_xmm0_reg) - 1,				false,		_ICODE_XMM0,						false,		_ICAT_XMM_REGISTER,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_xmm1_reg,					sizeof(cgc_xmm1_reg) - 1,				false,		_ICODE_XMM1,						false,		_ICAT_XMM_REGISTER,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_xmm2_reg,					sizeof(cgc_xmm2_reg) - 1,				false,		_ICODE_XMM2,						false,		_ICAT_XMM_REGISTER,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_xmm3_reg,					sizeof(cgc_xmm3_reg) - 1,				false,		_ICODE_XMM3,						false,		_ICAT_XMM_REGISTER,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_xmm4_reg,					sizeof(cgc_xmm4_reg) - 1,				false,		_ICODE_XMM4,						false,		_ICAT_XMM_REGISTER,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_xmm5_reg,					sizeof(cgc_xmm5_reg) - 1,				false,		_ICODE_XMM5,						false,		_ICAT_XMM_REGISTER,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_xmm6_reg,					sizeof(cgc_xmm6_reg) - 1,				false,		_ICODE_XMM6,						false,		_ICAT_XMM_REGISTER,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_xmm7_reg,					sizeof(cgc_xmm7_reg) - 1,				false,		_ICODE_XMM7,						false,		_ICAT_XMM_REGISTER,		&colorDefault,		false,			null0,	null0,	null0	},

		// lsa-specific
		{	(cs8*)cgc_lsa_equ,					sizeof(cgc_lsa_equ) - 1,				false,		_ICODE_LSA_EQU,						true,		_ICAT_DEFINITION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_lsa_org,					sizeof(cgc_lsa_org) - 1,				false,		_ICODE_LSA_ORG,						false,		_ICAT_DEFINITION,		&colorDefault,		false,			null0,	null0,	null0	},

		{	(cs8*)cgc_lsa_include,				sizeof(cgc_lsa_include) - 1,			false,		_ICODE_LSA_INCLUDE,					true,		_ICAT_DEFINITION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_lsa_code,					sizeof(cgc_lsa_code) - 1,				false,		_ICODE_LSA_CODE,					true,		_ICAT_DEFINITION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_lsa_define,				sizeof(cgc_lsa_define) - 1,				false,		_ICODE_LSA_DEFINE,					true,		_ICAT_DEFINITION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_lsa_function,				sizeof(cgc_lsa_function) - 1,			false,		_ICODE_LSA_FUNCTION,				true,		_ICAT_DEFINITION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_lsa_struct,				sizeof(cgc_lsa_struct) - 1,				false,		_ICODE_LSA_STRUCT,					true,		_ICAT_DEFINITION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_lsa_enum,					sizeof(cgc_lsa_enum) - 1,				false,		_ICODE_LSA_ENUM,					true,		_ICAT_DEFINITION,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_lsa_macro,				sizeof(cgc_lsa_macro) - 1,				false,		_ICODE_LSA_MACRO,					true,		_ICAT_DEFINITION,		&colorDefault,		false,			null0,	null0,	null0	},

		{	(cs8*)cgc_lsa_if,					sizeof(cgc_lsa_if) - 1,					false,		_ICODE_LSA_IF,						false,		_ICAT_FLOW,				&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_lsa_else,					sizeof(cgc_lsa_else) - 1,				false,		_ICODE_LSA_ELSE,					false,		_ICAT_FLOW,				&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_lsa_ifdef,				sizeof(cgc_lsa_ifdef) - 1,				false,		_ICODE_LSA_IFDEF,					false,		_ICAT_FLOW,				&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_lsa_ifndef,				sizeof(cgc_lsa_ifndef) - 1,				false,		_ICODE_LSA_IFNDEF,					false,		_ICAT_FLOW,				&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_lsa_ifb,					sizeof(cgc_lsa_ifb) - 1,				false,		_ICODE_LSA_IFB,						false,		_ICAT_FLOW,				&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_lsa_ifnb,					sizeof(cgc_lsa_ifnb) - 1,				false,		_ICODE_LSA_IFNB,					false,		_ICAT_FLOW,				&colorDefault,		false,			null0,	null0,	null0	},

		{	(cs8*)cgc_lsa_offset,				sizeof(cgc_lsa_offset) - 1,				false,		_ICODE_LSA_OFFSET,					false,		_ICAT_REFERENCE,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_lsa_sizeof,				sizeof(cgc_lsa_sizeof) - 1,				false,		_ICODE_LSA_SIZEOF,					false,		_ICAT_REFERENCE,		&colorDefault,		false,			null0,	null0,	null0	},
		{	(cs8*)cgc_lsa_alignof,				sizeof(cgc_lsa_alignof) - 1,			false,		_ICODE_LSA_ALIGNOF,					false,		_ICAT_REFERENCE,		&colorDefault,		false,			null0,	null0,	null0	},

		{	0,									0,										0,			0,									0,			0,						0,					0,				0,		0,		0		}
	};
