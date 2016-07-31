//////////
//
// /libsf/exodus/tools/lsa/lasm_const.h
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
// Macros
//////
	#define ilsa_is_cmdLineOption(a)				lnLength == sizeof(a) - 1 && (_memicmp(argv[lnI], a, sizeof(a) - 1) == 0)
	#define ilsa_is_cmdLineOption_beginsWith(a)		lnLength > sizeof(a) - 1 && (_memicmp(argv[lnI], a, sizeof(a) - 1) == 0)
	#define ilsa_is_warning(a)						(a & _LSA_STATUS_WARNING)
	#define ilsa_is_error(a)						(a & _LSA_STATUS_ERROR)
	#define ilsa_is_completed(a)					(a & _LSA_STATUS_COMPLETED)
	#define ilsa_markCompCompleted(c)				ilsa_status_comp_add(c, _LSA_STATUS_COMPLETED)
	#define ilsa_markLineCompleted(l)				ilsa_status_line_add(l, _LSA_STATUS_COMPLETED, true)



//////////
// Constants
//////
	cu32		_LSA_STATUS_WARNING							= 1 << 29;				// At least one warning attached
	cu32		_LSA_STATUS_ERROR							= 1 << 30;				// At lease one error attached
	cu32		_LSA_STATUS_COMPLETED						= 1 << 31;				// Completed flag

	cs32		_LSA_MAX_DEFINE_PARAMS						= 26;					// Up to 26 #define macro(a,b,c,...,z)
	cs32		_LSA_MAX_RETURN_PARAMS						= 10;					// Up to 10 return parameters are allowed
	cs32		_LSA_MAX_INPUT_PARAMS						= 26;					// Up to 26 input parameters are allowed

	cs32		_LSA_BLOCK_TYPE_ADHOC						= 1;
	cs32		_LSA_BLOCK_TYPE_FUNCTION					= 2;
	cs32		_LSA_BLOCK_TYPE_FLOWOF						= 3;

	cs32		_ICAT_INSTRUCTION							= 1;
	cs32		_ICAT_DATA_TYPE								= 2;
	cs32		_ICAT_POINTER_SIZE							= 3;
	cs32		_ICAT_PLUS_MINUS							= 4;
	cs32		_ICAT_SEGMENT_REGISTER						= 5;
	cs32		_ICAT_REGISTER								= 6;
	cs32		_ICAT_FPU_REGISTER							= 7;
	cs32		_ICAT_MMX_REGISTER							= 8;
	cs32		_ICAT_XMM_REGISTER							= 9;

	// Note:  The instruction iCodes were moved to lsa_pass3.h

	cs32		_ICODE_PTR_TBYTE							= 1000000;
	cs32		_ICODE_PTR_DQWORD							= 1000001;
	cs32		_ICODE_PTR_QWORD							= 1000002;
	cs32		_ICODE_PTR_DWORD							= 1000003;
	cs32		_ICODE_PTR_WORD								= 1000004;
	cs32		_ICODE_PTR_BYTE								= 1000005;
	cs32		_ICODE_PTR_M16_16							= 1000006;
	cs32		_ICODE_PTR_M16_32							= 1000007;
	cs32		_ICODE_PTR_F32								= 1000008;
	cs32		_ICODE_PTR_F64								= 1000009;
	cs32		_ICODE_PTR_F80								= 1000010;
	cs32		_ICODE_PTR_S16								= 1000011;
	cs32		_ICODE_PTR_S32								= 1000012;
	cs32		_ICODE_PTR_S64								= 1000013;
	cs32		_ICODE_PTR_M80								= 1000014;
	cs32		_ICODE_PTR_MMX								= 1000015;
	cs32		_ICODE_PTR_XMMX								= 1000016;
	cs32		_ICODE_PTR_FPU								= 1000017;
	cs32		_ICODE_PTR_6BYTE							= 1000018;
	cs32		_ICODE_PTR_10BYTE							= 1000019;
	cs32		_ICODE_PTR_14BYTE							= 1000020;
	cs32		_ICODE_PTR_28BYTE							= 1000021;
	cs32		_ICODE_PTR_94BYTE							= 1000022;
	cs32		_ICODE_PTR_108BYTE							= 1000023;

	// Note:  The 10001nn series are nuserved (not used, and reserved for future use)

	cs32		_ICODE_CS									= 1000200;
	cs32		_ICODE_DS									= 1000200;
	cs32		_ICODE_ES									= 1000200;
	cs32		_ICODE_FS									= 1000200;
	cs32		_ICODE_GS									= 1000200;
	cs32		_ICODE_SS									= 1000200;

	cs32		_ICODE_AL									= 1000300;
	cs32		_ICODE_BL									= 1000301;
	cs32		_ICODE_CL									= 1000302;
	cs32		_ICODE_DL									= 1000303;
	cs32		_ICODE_AH									= 1000304;
	cs32		_ICODE_BH									= 1000305;
	cs32		_ICODE_CH									= 1000306;
	cs32		_ICODE_DH									= 1000307;

	cs32		_ICODE_AX									= 1000400;
	cs32		_ICODE_BX									= 1000401;
	cs32		_ICODE_CX									= 1000402;
	cs32		_ICODE_DX									= 1000403;
	cs32		_ICODE_SI									= 1000404;
	cs32		_ICODE_DI									= 1000405;
	cs32		_ICODE_BP									= 1000406;
	cs32		_ICODE_SP									= 1000407;
	cs32		_ICODE_IP									= 1000408;

	cs32		_ICODE_EAX									= 1000500;
	cs32		_ICODE_EBX									= 1000501;
	cs32		_ICODE_ECX									= 1000502;
	cs32		_ICODE_EDX									= 1000503;
	cs32		_ICODE_ESI									= 1000504;
	cs32		_ICODE_EDI									= 1000505;
	cs32		_ICODE_EBP									= 1000506;
	cs32		_ICODE_ESP									= 1000507;
	cs32		_ICODE_EIP									= 1000508;

	cs32		_ICODE_CR0									= 1000600;
	cs32		_ICODE_CR1									= 1000601;
	cs32		_ICODE_CR2									= 1000602;
	cs32		_ICODE_CR3									= 1000603;
	cs32		_ICODE_CR4									= 1000604;
	cs32		_ICODE_CR5									= 1000605;
	cs32		_ICODE_CR6									= 1000606;
	cs32		_ICODE_CR7									= 1000607;

	cs32		_ICODE_DR0									= 1000700;
	cs32		_ICODE_DR1									= 1000701;
	cs32		_ICODE_DR2									= 1000702;
	cs32		_ICODE_DR3									= 1000703;
	cs32		_ICODE_DR4									= 1000704;
	cs32		_ICODE_DR5									= 1000705;
	cs32		_ICODE_DR6									= 1000706;
	cs32		_ICODE_DR7									= 1000707;

	cs32		_ICODE_TR0									= 1000800;
	cs32		_ICODE_TR1									= 1000801;
	cs32		_ICODE_TR2									= 1000802;
	cs32		_ICODE_TR3									= 1000803;
	cs32		_ICODE_TR4									= 1000804;
	cs32		_ICODE_TR5									= 1000805;
	cs32		_ICODE_TR6									= 1000806;
	cs32		_ICODE_TR7									= 1000807;

	cs32		_ICODE_ST0									= 1000900;
	cs32		_ICODE_ST1									= 1000901;
	cs32		_ICODE_ST2									= 1000902;
	cs32		_ICODE_ST3									= 1000903;
	cs32		_ICODE_ST4									= 1000904;
	cs32		_ICODE_ST5									= 1000905;
	cs32		_ICODE_ST6									= 1000906;
	cs32		_ICODE_ST7									= 1000907;

	cs32		_ICODE_MM0									= 2000000;
	cs32		_ICODE_MM1									= 2000001;
	cs32		_ICODE_MM2									= 2000002;
	cs32		_ICODE_MM3									= 2000003;
	cs32		_ICODE_MM4									= 2000004;
	cs32		_ICODE_MM5									= 2000005;
	cs32		_ICODE_MM6									= 2000006;
	cs32		_ICODE_MM7									= 2000007;

	cs32		_ICODE_XMM0									= 2000100;
	cs32		_ICODE_XMM1									= 2000101;
	cs32		_ICODE_XMM2									= 2000102;
	cs32		_ICODE_XMM3									= 2000103;
	cs32		_ICODE_XMM4									= 2000104;
	cs32		_ICODE_XMM5									= 2000105;
	cs32		_ICODE_XMM6									= 2000106;
	cs32		_ICODE_XMM7									= 2000107;

	cs32		_ICODE_LSA_EQU								= 3000001;
	cs32		_ICODE_LSA_ORG								= 3000002;

	cs32		_ICODE_LSA_INCLUDE							= 3000101;
	cs32		_ICODE_LSA_CODE								= 3000102;
	cs32		_ICODE_LSA_DEFINE							= 3000103;
	cs32		_ICODE_LSA_FUNCTION							= 3000104;
	cs32		_ICODE_LSA_STRUCT							= 3000105;
	cs32		_ICODE_LSA_ENUM								= 3000106;
	cs32		_ICODE_LSA_MACRO							= 3000107;

	cs32		_ICODE_LSA_IF								= 3000501;
	cs32		_ICODE_LSA_ELSE								= 3000502;
	cs32		_ICODE_LSA_IFDEF							= 3000503;
	cs32		_ICODE_LSA_IFNDEF							= 3000504;
	cs32		_ICODE_LSA_IFB								= 3000505;
	cs32		_ICODE_LSA_IFNB								= 3000506;


//////////
// Command line options
//////
	cs8			cgc_w[]										= "-W";
	cs8			cgc_wno[]									= "-Wno-";
	cs8			cgc_wmissing_type_ptr[]						= "missing-type-ptr";
	cs8			cgc_wall[]									= "all";
	cs8			cgc_wfatal_errors[]							= "fatal-errors";
	cs8			cgc_werror[]								= "error";
	cs8			cgc_syntax_only[]							= "fsyntax-only";
	cs8			cgc_verbose[]								= "verbose";
	cs8			cgc_includePath[]							= "includepath=";


//////////
// Pointer types
//////
	cs8			cgc_ptr_tbyte[]								= "tbyte";
	cs8			cgc_ptr_dqword[]							= "dqword";
	cs8			cgc_ptr_qword[]								= "qword";
	cs8			cgc_ptr_dword[]								= "dword";
	cs8			cgc_ptr_word[]								= "word";
	cs8			cgc_ptr_byte[]								= "byte";
	cs8			cgc_ptr_m16_16[]							= "m16_16";
	cs8			cgc_ptr_m16_32[]							= "m16_32";
	cs8			cgc_ptr_f32[]								= "f32";
	cs8			cgc_ptr_f64[]								= "f64";
	cs8			cgc_ptr_f80[]								= "f80";
	cs8			cgc_ptr_s16[]								= "s16";
	cs8			cgc_ptr_s32[]								= "s32";
	cs8			cgc_ptr_s64[]								= "s64";
	cs8			cgc_ptr_m80[]								= "m80";
	cs8			cgc_ptr_mmx[]								= "mmx";
	cs8			cgc_ptr_xmmx[]								= "xmmx";
	cs8			cgc_ptr_fpu[]								= "fpu";
	cs8			cgc_ptr_6byte[]								= "m6byte";
	cs8			cgc_ptr_10byte[]							= "m10byte";
	cs8			cgc_ptr_14byte[]							= "m14byte";
	cs8			cgc_ptr_28byte[]							= "m28byte";
	cs8			cgc_ptr_94byte[]							= "m94byte";
	cs8			cgc_ptr_108byte[]							= "m108byte";

	cs8			cgc_lsa_equ[]								= "equ";
	cs8			cgc_lsa_org[]								= "org";

	cs8			cgc_lsa_include[]							= "include";
	cs8			cgc_lsa_code[]								= "code";
	cs8			cgc_lsa_define[]							= "define";
	cs8			cgc_lsa_function[]							= "function";
	cs8			cgc_lsa_struct[]							= "struct";
	cs8			cgc_lsa_enum[]								= "enum";
	cs8			cgc_lsa_macro[]								= "macro";

	cs8			cgc_lsa_if[]								= "if";
	cs8			cgc_lsa_else[]								= "else";
	cs8			cgc_lsa_ifdef[]								= "ifdef";
	cs8			cgc_lsa_ifndef[]							= "ifndef";
	cs8			cgc_lsa_ifb[]								= "ifb";
	cs8			cgc_lsa_ifnb[]								= "ifnb";


//////////
// Miscellaneous messages
//////
	cs8			cgc_lsa_group[]								= "{group}";


//////////
// Note numbers
//////
	cs32		_LSA_NOTE_BASE								= 2000;


//////////
// Warning numbers
//////
	cs32		_LSA_WARNING_BASE							= 4000;
	cs32		_LSA_WARNING_UNREFERENCED_PARAMETER			= 1;
	cs32		_LSA_WARNING_TOO_MANY_PARAMETERS__IGNORED	= 2;


//////////
// Error numbers
//////
	cs32		_LSA_ERROR_BASE								= 5000;
	cs32		_LSA_ERROR_TOKEN_NAME_ALREADY_EXISTS		= 1;


//////////
// Note messages
//////
	cs8			cgc_lsa_note_unknown_note[]					= "unspecified note";


//////////
// Warning messages
//////
	cs8			cgc_lsa_warning_unknown_warning[]			= "unspecified warning";
	cs8			cgc_lsa_warning_unreferenced_parameter[]	= "unreferenced parameter";
	cs8			cgc_lsa_warning_too_many_parameters__ignored[] = "too many parameters (extra parameters ignored)";

//////////
// Error messages
//////
	cs8			cgc_lsa_internal_compiler_error[]			= "Internal compiler error.  Terminating.\n";
	cs8			cgc_unable_to_open_file[]					= "--Error: unable to open file: %s\n";
	cs8			cgc_lsa_error_opening_include_file[]		= "--Error[%d,%d]: error opening file [include \"%s\"]\n";
	cs8			cgc_lsa_error_token_name_already_exists[]	= "token name already exists";
	cs8			cgc_lsa_error_unknown_error[]				= "unspecified error";
