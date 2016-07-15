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
	#define ilsa_is_warning(a)						(a & _LSA_STATUS_WARNING)
	#define ilsa_is_error(a)						(a & _LSA_STATUS_ERROR)
	#define ilsa_is_completed(a)					(a & _LSA_STATUS_COMPLETED)
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

	cs32		_ICODE_ADD_INSTRUCTION						= 1000001;
	cs32		_ICODE_ADC_INSTRUCTION						= 1000002;
	cs32		_ICODE_AND_INSTRUCTION						= 1000003;
	cs32		_ICODE_SUB_INSTRUCTION						= 1000004;
	cs32		_ICODE_SBB_INSTRUCTION						= 1000005;
	cs32		_ICODE_XOR_INSTRUCTION						= 1000006;
	cs32		_ICODE_CMP_INSTRUCTION						= 1000007;
	cs32		_ICODE_BSWAP_INSTRUCTION					= 1000008;
	cs32		_ICODE_AAA_INSTRUCTION						= 1000009;
	cs32		_ICODE_AAD_INSTRUCTION						= 1000010;
	cs32		_ICODE_AAM_INSTRUCTION						= 1000011;
	cs32		_ICODE_AAS_INSTRUCTION						= 1000012;
	cs32		_ICODE_CBW_INSTRUCTION						= 1000013;
	cs32		_ICODE_CLC_INSTRUCTION						= 1000014;
	cs32		_ICODE_CLD_INSTRUCTION						= 1000015;
	cs32		_ICODE_CLI_INSTRUCTION						= 1000016;
	cs32		_ICODE_CLTS_INSTRUCTION						= 1000017;
	cs32		_ICODE_CMC_INSTRUCTION						= 1000018;
	cs32		_ICODE_CPUID_INSTRUCTION					= 1000019;
	cs32		_ICODE_CWD_INSTRUCTION						= 1000020;
	cs32		_ICODE_DAA_INSTRUCTION						= 1000021;
	cs32		_ICODE_EMMS_INSTRUCTION						= 1000022;
	cs32		_ICODE_DAS_INSTRUCTION						= 1000023;
	cs32		_ICODE_HLT_INSTRUCTION						= 1000024;
	cs32		_ICODE_INSB_INSTRUCTION						= 1000025;
	cs32		_ICODE_INSD_INSTRUCTION						= 1000026;
	cs32		_ICODE_INSW_INSTRUCTION						= 1000027;
	cs32		_ICODE_INT3_INSTRUCTION						= 1000028;
	cs32		_ICODE_INT_INSTRUCTION						= 1000029;
	cs32		_ICODE_INTO_INSTRUCTION						= 1000030;
	cs32		_ICODE_IRET_INSTRUCTION						= 1000031;
	cs32		_ICODE_LAHF_INSTRUCTION						= 1000032;
	cs32		_ICODE_LEAVE_INSTRUCTION					= 1000033;
	cs32		_ICODE_NOP_INSTRUCTION						= 1000034;
	cs32		_ICODE_OUTSB_INSTRUCTION					= 1000035;
	cs32		_ICODE_OUTSD_INSTRUCTION					= 1000036;
	cs32		_ICODE_OUTSW_INSTRUCTION					= 1000037;
	cs32		_ICODE_POP_INSTRUCTION						= 1000038;
	cs32		_ICODE_PUSH_INSTRUCTION						= 1000039;
	cs32		_ICODE_POPA_INSTRUCTION						= 1000040;
	cs32		_ICODE_POPF_INSTRUCTION						= 1000041;
	cs32		_ICODE_PUSHA_INSTRUCTION					= 1000042;
	cs32		_ICODE_PUSHF_INSTRUCTION					= 1000043;
	cs32		_ICODE_POPAD_INSTRUCTION					= 1000044;
	cs32		_ICODE_POPFD_INSTRUCTION					= 1000045;
	cs32		_ICODE_PUSHAD_INSTRUCTION					= 1000046;
	cs32		_ICODE_PUSHFD_INSTRUCTION					= 1000047;
	cs32		_ICODE_RETF_INSTRUCTION						= 1000048;
	cs32		_ICODE_RETN_INSTRUCTION						= 1000049;
	cs32		_ICODE_SAHF_INSTRUCTION						= 1000050;
	cs32		_ICODE_SETA_INSTRUCTION						= 1000051;
	cs32		_ICODE_SETC_INSTRUCTION						= 1000052;
	cs32		_ICODE_SETG_INSTRUCTION						= 1000053;
	cs32		_ICODE_SETL_INSTRUCTION						= 1000054;
	cs32		_ICODE_SETNA_INSTRUCTION					= 1000055;
	cs32		_ICODE_SETNC_INSTRUCTION					= 1000056;
	cs32		_ICODE_SETNG_INSTRUCTION					= 1000057;
	cs32		_ICODE_SETNL_INSTRUCTION					= 1000058;
	cs32		_ICODE_SETNO_INSTRUCTION					= 1000059;
	cs32		_ICODE_SETNS_INSTRUCTION					= 1000060;
	cs32		_ICODE_SETNZ_INSTRUCTION					= 1000061;
	cs32		_ICODE_SETO_INSTRUCTION						= 1000062;
	cs32		_ICODE_SETPE_INSTRUCTION					= 1000063;
	cs32		_ICODE_SETPO_INSTRUCTION					= 1000064;
	cs32		_ICODE_SETS_INSTRUCTION						= 1000065;
	cs32		_ICODE_SETZ_INSTRUCTION						= 1000066;
	cs32		_ICODE_STC_INSTRUCTION						= 1000067;
	cs32		_ICODE_STD_INSTRUCTION						= 1000068;
	cs32		_ICODE_STI_INSTRUCTION						= 1000069;
	cs32		_ICODE_WAIT_INSTRUCTION						= 1000070;
	cs32		_ICODE_XLAT_INSTRUCTION						= 1000071;
	cs32		_ICODE_REPE_INSTRUCTION						= 1000072;
	cs32		_ICODE_REPNE_INSTRUCTION					= 1000073;
	cs32		_ICODE_CMPSW_INSTRUCTION					= 1000074;
	cs32		_ICODE_CMPSD_INSTRUCTION					= 1000075;
	cs32		_ICODE_LODSW_INSTRUCTION					= 1000076;
	cs32		_ICODE_LODSD_INSTRUCTION					= 1000077;
	cs32		_ICODE_MOVSW_INSTRUCTION					= 1000078;
	cs32		_ICODE_MOVSD_INSTRUCTION					= 1000079;
	cs32		_ICODE_SCASW_INSTRUCTION					= 1000080;
	cs32		_ICODE_SCASD_INSTRUCTION					= 1000081;
	cs32		_ICODE_STOSW_INSTRUCTION					= 1000082;
	cs32		_ICODE_STOSD_INSTRUCTION					= 1000083;
	cs32		_ICODE_ARPL_INSTRUCTION						= 1000084;
	cs32		_ICODE_BOUND_INSTRUCTION					= 1000085;
	cs32		_ICODE_BSF_INSTRUCTION						= 1000086;
	cs32		_ICODE_BSR_INSTRUCTION						= 1000087;
	cs32		_ICODE_BT_INSTRUCTION						= 1000088;
	cs32		_ICODE_BTC_INSTRUCTION						= 1000089;
	cs32		_ICODE_BTR_INSTRUCTION						= 1000090;
	cs32		_ICODE_BTS_INSTRUCTION						= 1000091;
	cs32		_ICODE_CALL_INSTRUCTION						= 1000092;
	cs32		_ICODE_CMOVA_INSTRUCTION					= 1000093;
	cs32		_ICODE_CMOVC_INSTRUCTION					= 1000094;
	cs32		_ICODE_CMOVG_INSTRUCTION					= 1000095;
	cs32		_ICODE_CMOVL_INSTRUCTION					= 1000096;
	cs32		_ICODE_CMOVNA_INSTRUCTION					= 1000097;
	cs32		_ICODE_CMOVNC_INSTRUCTION					= 1000098;
	cs32		_ICODE_CMOVNG_INSTRUCTION					= 1000099;
	cs32		_ICODE_CMOVNL_INSTRUCTION					= 1000100;
	cs32		_ICODE_CMOVNO_INSTRUCTION					= 1000101;
	cs32		_ICODE_CMOVNS_INSTRUCTION					= 1000102;
	cs32		_ICODE_CMOVNZ_INSTRUCTION					= 1000103;
	cs32		_ICODE_CMOVO_INSTRUCTION					= 1000104;
	cs32		_ICODE_CMOVPE_INSTRUCTION					= 1000105;
	cs32		_ICODE_CMOVPO_INSTRUCTION					= 1000106;
	cs32		_ICODE_CMOVS_INSTRUCTION					= 1000107;
	cs32		_ICODE_CMOVZ_INSTRUCTION					= 1000108;
	cs32		_ICODE_CMPXCHG_INSTRUCTION					= 1000109;
	cs32		_ICODE_DEC_INSTRUCTION						= 1000110;
	cs32		_ICODE_INC_INSTRUCTION						= 1000111;
	cs32		_ICODE_IMUL_INSTRUCTION						= 1000112;
	cs32		_ICODE_ICEBP_INSTRUCTION					= 1000113;
	cs32		_ICODE_SLDT_INSTRUCTION						= 1000114;
	cs32		_ICODE_LLDT_INSTRUCTION						= 1000115;
	cs32		_ICODE_STR_INSTRUCTION						= 1000116;
	cs32		_ICODE_VERR_INSTRUCTION						= 1000117;
	cs32		_ICODE_VERW_INSTRUCTION						= 1000118;
	cs32		_ICODE_LTR_INSTRUCTION						= 1000119;
	cs32		_ICODE_UNK_INSTRUCTION						= 1000120;
	cs32		_ICODE_SGDT_INSTRUCTION						= 1000121;
	cs32		_ICODE_SIDT_INSTRUCTION						= 1000122;
	cs32		_ICODE_LGDT_INSTRUCTION						= 1000123;
	cs32		_ICODE_LIDT_INSTRUCTION						= 1000124;
	cs32		_ICODE_LMSW_INSTRUCTION						= 1000125;
	cs32		_ICODE_SMSW_INSTRUCTION						= 1000126;
	cs32		_ICODE_INVLPG_INSTRUCTION					= 1000127;
	cs32		_ICODE_PSRAW_INSTRUCTION					= 1000128;
	cs32		_ICODE_PSRAD_INSTRUCTION					= 1000129;
	cs32		_ICODE_PSRLD_INSTRUCTION					= 1000130;
	cs32		_ICODE_PSRLW_INSTRUCTION					= 1000131;
	cs32		_ICODE_PSRLQ_INSTRUCTION					= 1000132;
	cs32		_ICODE_PSUBB_INSTRUCTION					= 1000133;
	cs32		_ICODE_PSUBW_INSTRUCTION					= 1000134;
	cs32		_ICODE_PSUBD_INSTRUCTION					= 1000135;
	cs32		_ICODE_PSUBSB_INSTRUCTION					= 1000136;
	cs32		_ICODE_PSUBSW_INSTRUCTION					= 1000137;
	cs32		_ICODE_PSUBUSB_INSTRUCTION					= 1000138;
	cs32		_ICODE_PSUBUSW_INSTRUCTION					= 1000139;
	cs32		_ICODE_PUNPCKHBW_INSTRUCTION				= 1000140;
	cs32		_ICODE_PUNPCKHWD_INSTRUCTION				= 1000141;
	cs32		_ICODE_PUNPCKHDQ_INSTRUCTION				= 1000142;
	cs32		_ICODE_PUNPCKLBW_INSTRUCTION				= 1000143;
	cs32		_ICODE_PUNPCKLWD_INSTRUCTION				= 1000144;
	cs32		_ICODE_PUNPCKLDQ_INSTRUCTION				= 1000145;
	cs32		_ICODE_PXOR_INSTRUCTION						= 1000146;
	cs32		_ICODE_RSM_INSTRUCTION						= 1000147;
	cs32		_ICODE_SHLD_INSTRUCTION						= 1000148;
	cs32		_ICODE_SHRD_INSTRUCTION						= 1000149;
	cs32		_ICODE_TEST_INSTRUCTION						= 1000150;
	cs32		_ICODE_XCHG_INSTRUCTION						= 1000151;
	cs32		_ICODE_UD2_INSTRUCTION						= 1000152;
	cs32		_ICODE_WRMSR_INSTRUCTION					= 1000153;
	cs32		_ICODE_WBINVD_INSTRUCTION					= 1000154;
	cs32		_ICODE_XADD_INSTRUCTION						= 1000155;
	cs32		_ICODE_PACKSSDW_INSTRUCTION					= 1000156;
	cs32		_ICODE_PACKSSWB_INSTRUCTION					= 1000157;
	cs32		_ICODE_PACKUSWB_INSTRUCTION					= 1000158;
	cs32		_ICODE_PADDB_INSTRUCTION					= 1000159;
	cs32		_ICODE_PADDD_INSTRUCTION					= 1000160;
	cs32		_ICODE_PADDSB_INSTRUCTION					= 1000161;
	cs32		_ICODE_PADDSW_INSTRUCTION					= 1000162;
	cs32		_ICODE_PADDUSB_INSTRUCTION					= 1000163;
	cs32		_ICODE_PADDUSW_INSTRUCTION					= 1000164;
	cs32		_ICODE_PADDW_INSTRUCTION					= 1000165;
	cs32		_ICODE_PAND_INSTRUCTION						= 1000166;
	cs32		_ICODE_PANDN_INSTRUCTION					= 1000167;
	cs32		_ICODE_PCMPEQB_INSTRUCTION					= 1000168;
	cs32		_ICODE_PCMPEQD_INSTRUCTION					= 1000169;
	cs32		_ICODE_PCMPEQW_INSTRUCTION					= 1000170;
	cs32		_ICODE_PCMPGTB_INSTRUCTION					= 1000171;
	cs32		_ICODE_PCMPGTD_INSTRUCTION					= 1000172;
	cs32		_ICODE_PCMPGTW_INSTRUCTION					= 1000173;
	cs32		_ICODE_PMADDWD_INSTRUCTION					= 1000174;
	cs32		_ICODE_PMULHW_INSTRUCTION					= 1000175;
	cs32		_ICODE_PMULLW_INSTRUCTION					= 1000176;
	cs32		_ICODE_POR_INSTRUCTION						= 1000177;
	cs32		_ICODE_PSLLD_INSTRUCTION					= 1000178;
	cs32		_ICODE_PSLLQ_INSTRUCTION					= 1000179;
	cs32		_ICODE_PSLLW_INSTRUCTION					= 1000180;
	cs32		_ICODE_OR_INSTRUCTION						= 1000181;
	cs32		_ICODE_HCF_INSTRUCTION						= 1000182;
	cs32		_ICODE_CMPXCHG8B_INSTRUCTION				= 1000183;
	cs32		_ICODE_IN_INSTRUCTION						= 1000184;
	cs32		_ICODE_RDMSR_INSTRUCTION					= 1000185;
	cs32		_ICODE_RDPMC_INSTRUCTION					= 1000186;
	cs32		_ICODE_RDTSC_INSTRUCTION					= 1000187;
	cs32		_ICODE_MOVSX_INSTRUCTION					= 1000188;
	cs32		_ICODE_MOVZX_INSTRUCTION					= 1000189;
	cs32		_ICODE_LSL_INSTRUCTION						= 1000190;
	cs32		_ICODE_LSS_INSTRUCTION						= 1000191;
	cs32		_ICODE_LOOPNE_INSTRUCTION					= 1000192;
	cs32		_ICODE_LOOPE_INSTRUCTION					= 1000193;
	cs32		_ICODE_LOOP_INSTRUCTION						= 1000194;
	cs32		_ICODE_LGS_INSTRUCTION						= 1000195;
	cs32		_ICODE_LFS_INSTRUCTION						= 1000196;
	cs32		_ICODE_LES_INSTRUCTION						= 1000197;
	cs32		_ICODE_LEA_INSTRUCTION						= 1000198;
	cs32		_ICODE_LDS_INSTRUCTION						= 1000199;
	cs32		_ICODE_LAR_INSTRUCTION						= 1000200;
	cs32		_ICODE_JZ_INSTRUCTION						= 1000201;
	cs32		_ICODE_JS_INSTRUCTION						= 1000202;
	cs32		_ICODE_JPO_INSTRUCTION						= 1000203;
	cs32		_ICODE_JPE_INSTRUCTION						= 1000204;
	cs32		_ICODE_JO_INSTRUCTION						= 1000205;
	cs32		_ICODE_JNZ_INSTRUCTION						= 1000206;
	cs32		_ICODE_JNO_INSTRUCTION						= 1000207;
	cs32		_ICODE_JNL_INSTRUCTION						= 1000208;
	cs32		_ICODE_JNG_INSTRUCTION						= 1000209;
	cs32		_ICODE_JNC_INSTRUCTION						= 1000210;
	cs32		_ICODE_JNA_INSTRUCTION						= 1000211;
	cs32		_ICODE_JMP_INSTRUCTION						= 1000212;
	cs32		_ICODE_JL_INSTRUCTION						= 1000213;
	cs32		_ICODE_JG_INSTRUCTION						= 1000214;
	cs32		_ICODE_JCXZ_INSTRUCTION						= 1000215;
	cs32		_ICODE_JECXZ_INSTRUCTION					= 1000216;
	cs32		_ICODE_JC_INSTRUCTION						= 1000217;
	cs32		_ICODE_JA_INSTRUCTION						= 1000218;
	cs32		_ICODE_JNS_INSTRUCTION						= 1000219;
	cs32		_ICODE_INVD_INSTRUCTION						= 1000220;
	cs32		_ICODE_IDIV_INSTRUCTION						= 1000221;
	cs32		_ICODE_DIV_INSTRUCTION						= 1000222;
	cs32		_ICODE_NEG_INSTRUCTION						= 1000223;
	cs32		_ICODE_MUL_INSTRUCTION						= 1000224;
	cs32		_ICODE_NOT_INSTRUCTION						= 1000225;
	cs32		_ICODE_SAR_INSTRUCTION						= 1000226;
	cs32		_ICODE_SHR_INSTRUCTION						= 1000227;
	cs32		_ICODE_SHL_INSTRUCTION						= 1000228;
	cs32		_ICODE_RCR_INSTRUCTION						= 1000229;
	cs32		_ICODE_RCL_INSTRUCTION						= 1000230;
	cs32		_ICODE_ROR_INSTRUCTION						= 1000231;
	cs32		_ICODE_ROL_INSTRUCTION						= 1000232;
	cs32		_ICODE_MOV_INSTRUCTION						= 1000233;
	cs32		_ICODE_FNOP_INSTRUCTION						= 1000234;
	cs32		_ICODE_FCHS_INSTRUCTION						= 1000235;
	cs32		_ICODE_FABS_INSTRUCTION						= 1000236;
	cs32		_ICODE_FTST_INSTRUCTION						= 1000237;
	cs32		_ICODE_FXAM_INSTRUCTION						= 1000238;
	cs32		_ICODE_FLD1_INSTRUCTION						= 1000239;
	cs32		_ICODE_FLD2T_INSTRUCTION					= 1000240;
	cs32		_ICODE_FLD2E_INSTRUCTION					= 1000241;
	cs32		_ICODE_FLDPI_INSTRUCTION					= 1000242;
	cs32		_ICODE_FLDLG2_INSTRUCTION					= 1000243;
	cs32		_ICODE_FLDLN2_INSTRUCTION					= 1000244;
	cs32		_ICODE_FLDZ_INSTRUCTION						= 1000245;
	cs32		_ICODE_F2XM1_INSTRUCTION					= 1000246;
	cs32		_ICODE_FYL2X_INSTRUCTION					= 1000247;
	cs32		_ICODE_FPTAN_INSTRUCTION					= 1000248;
	cs32		_ICODE_FPATAN_INSTRUCTION					= 1000249;
	cs32		_ICODE_FXTRACT_INSTRUCTION					= 1000250;
	cs32		_ICODE_FPREM1_INSTRUCTION					= 1000251;
	cs32		_ICODE_FDECSTP_INSTRUCTION					= 1000252;
	cs32		_ICODE_FINCSTP_INSTRUCTION					= 1000253;
	cs32		_ICODE_FPREM_INSTRUCTION					= 1000254;
	cs32		_ICODE_FYL2XP1_INSTRUCTION					= 1000255;
	cs32		_ICODE_FSQRT_INSTRUCTION					= 1000256;
	cs32		_ICODE_FSINCOS_INSTRUCTION					= 1000257;
	cs32		_ICODE_FRNDINT_INSTRUCTION					= 1000258;
	cs32		_ICODE_FSCALE_INSTRUCTION					= 1000259;
	cs32		_ICODE_FSIN_INSTRUCTION						= 1000260;
	cs32		_ICODE_FCOS_INSTRUCTION						= 1000261;
	cs32		_ICODE_FADD_INSTRUCTION						= 1000262;
	cs32		_ICODE_FMUL_INSTRUCTION						= 1000263;
	cs32		_ICODE_FCOM_INSTRUCTION						= 1000264;
	cs32		_ICODE_FCOMP_INSTRUCTION					= 1000265;
	cs32		_ICODE_FSUB_INSTRUCTION						= 1000266;
	cs32		_ICODE_FSUBR_INSTRUCTION					= 1000267;
	cs32		_ICODE_FDIV_INSTRUCTION						= 1000268;
	cs32		_ICODE_FDIVR_INSTRUCTION					= 1000269;
	cs32		_ICODE_FLD_INSTRUCTION						= 1000270;
	cs32		_ICODE_FST_INSTRUCTION						= 1000271;
	cs32		_ICODE_FSTP_INSTRUCTION						= 1000272;
	cs32		_ICODE_FIADD_INSTRUCTION					= 1000273;
	cs32		_ICODE_FIMUL_INSTRUCTION					= 1000274;
	cs32		_ICODE_FICOM_INSTRUCTION					= 1000275;
	cs32		_ICODE_FICOMP_INSTRUCTION					= 1000276;
	cs32		_ICODE_FISUB_INSTRUCTION					= 1000277;
	cs32		_ICODE_FISUBR_INSTRUCTION					= 1000278;
	cs32		_ICODE_FIDIV_INSTRUCTION					= 1000279;
	cs32		_ICODE_FIDIVR_INSTRUCTION					= 1000280;
	cs32		_ICODE_FIST_INSTRUCTION						= 1000281;
	cs32		_ICODE_FISTP_INSTRUCTION					= 1000282;
	cs32		_ICODE_FILD_INSTRUCTION						= 1000283;
	cs32		_ICODE_FBLD_INSTRUCTION						= 1000284;
	cs32		_ICODE_FBSTP_INSTRUCTION					= 1000285;
	cs32		_ICODE_FXCH_INSTRUCTION						= 1000286;
	cs32		_ICODE_FUCOMP_INSTRUCTION					= 1000287;
	cs32		_ICODE_FUCOMPP_INSTRUCTION					= 1000288;
	cs32		_ICODE_FNCLEX_INSTRUCTION					= 1000289;
	cs32		_ICODE_FNINIT_INSTRUCTION					= 1000290;
	cs32		_ICODE_FNSTSW_INSTRUCTION					= 1000291;
	cs32		_ICODE_FLDCW_INSTRUCTION					= 1000292;
	cs32		_ICODE_FNSTCW_INSTRUCTION					= 1000293;
	cs32		_ICODE_FLDENV_INSTRUCTION					= 1000294;
	cs32		_ICODE_FNSTENV_INSTRUCTION					= 1000295;
	cs32		_ICODE_FRSTOR_INSTRUCTION					= 1000296;
	cs32		_ICODE_FNSAVE_INSTRUCTION					= 1000297;

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

	cs32		_ICODE_LSA_INCLUDE							= 3000001;
	cs32		_ICODE_LSA_DEFINE							= 3000002;
	cs32		_ICODE_LSA_FUNCTION							= 3000003;
	cs32		_ICODE_LSA_STRUCT							= 3000004;
	cs32		_ICODE_LSA_ENUM								= 3000005;
	cs32		_ICODE_LSA_MACRO							= 3000006;
	cs32		_ICODE_LSA_IF								= 3000007;
	cs32		_ICODE_LSA_ELSE								= 3000008;
	cs32		_ICODE_LSA_IFDEF							= 3000009;
	cs32		_ICODE_LSA_IFNDEF							= 3000010;
	cs32		_ICODE_LSA_IFB								= 3000011;
	cs32		_ICODE_LSA_IFNB								= 3000012;


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

	cs8			cgc_lsa_include[]							= "include";
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

//////////
// Error messages
//////
	cs8			cgc_unable_to_open_file[]					= "--Error: unable to open file: %s\n";
	cs8			cgc_lsa_error_opening_include_file[]		= "--Error[%d,%d]: error opening file [include \"%s\"]\n";
	cs8			cgc_lsa_error_token_name_already_exists[]	= "token name already exists";
	cs8			cgc_lsa_error_unknown_error[]				= "unspecified error";
