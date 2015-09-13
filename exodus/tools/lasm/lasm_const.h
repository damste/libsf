//////////
//
// /libsf/exodus/tools/lasm/lasm_const.h
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




const s32		_ICAT_INSTRUCTION					= 1;
const s32		_ICAT_DATA_TYPE						= 2;
const s32		_ICAT_POINTER_SIZE					= 3;
const s32		_ICAT_PLUS_MINUS					= 4;
const s32		_ICAT_SEGMENT_REGISTER				= 5;
const s32		_ICAT_REGISTER						= 6;
const s32		_ICAT_FPU_REGISTER					= 7;
const s32		_ICAT_MM_REGISTER					= 8;
const s32		_ICAT_XMM_REGISTER					= 9;

const s32		_ICODE_ADD_INSTRUCTION				= 1;
const s32		_ICODE_ADC_INSTRUCTION				= 2;
const s32		_ICODE_AND_INSTRUCTION				= 3;
const s32		_ICODE_SUB_INSTRUCTION				= 4;
const s32		_ICODE_SBB_INSTRUCTION				= 5;
const s32		_ICODE_XOR_INSTRUCTION				= 6;
const s32		_ICODE_CMP_INSTRUCTION				= 7;
const s32		_ICODE_BSWAP_INSTRUCTION			= 8;
const s32		_ICODE_AAA_INSTRUCTION				= 9;
const s32		_ICODE_AAD_INSTRUCTION				= 10;
const s32		_ICODE_AAM_INSTRUCTION				= 11;
const s32		_ICODE_AAS_INSTRUCTION				= 12;
const s32		_ICODE_CBW_INSTRUCTION				= 13;
const s32		_ICODE_CLC_INSTRUCTION				= 14;
const s32		_ICODE_CLD_INSTRUCTION				= 15;
const s32		_ICODE_CLI_INSTRUCTION				= 16;
const s32		_ICODE_CLTS_INSTRUCTION				= 17;
const s32		_ICODE_CMC_INSTRUCTION				= 18;
const s32		_ICODE_CPUID_INSTRUCTION			= 19;
const s32		_ICODE_CWD_INSTRUCTION				= 20;
const s32		_ICODE_DAA_INSTRUCTION				= 21;
const s32		_ICODE_EMMS_INSTRUCTION				= 22;
const s32		_ICODE_DAS_INSTRUCTION				= 23;
const s32		_ICODE_HLT_INSTRUCTION				= 24;
const s32		_ICODE_INSB_INSTRUCTION				= 25;
const s32		_ICODE_INSD_INSTRUCTION				= 26;
const s32		_ICODE_INSW_INSTRUCTION				= 27;
const s32		_ICODE_INT3_INSTRUCTION				= 28;
const s32		_ICODE_INT_INSTRUCTION				= 29;
const s32		_ICODE_INTO_INSTRUCTION				= 30;
const s32		_ICODE_IRET_INSTRUCTION				= 31;
const s32		_ICODE_LAHF_INSTRUCTION				= 32;
const s32		_ICODE_LEAVE_INSTRUCTION			= 33;
const s32		_ICODE_NOP_INSTRUCTION				= 34;
const s32		_ICODE_OUTSB_INSTRUCTION			= 35;
const s32		_ICODE_OUTSD_INSTRUCTION			= 36;
const s32		_ICODE_OUTSW_INSTRUCTION			= 37;
const s32		_ICODE_POP_INSTRUCTION				= 38;
const s32		_ICODE_PUSH_INSTRUCTION				= 39;
const s32		_ICODE_POPA_INSTRUCTION				= 40;
const s32		_ICODE_POPF_INSTRUCTION				= 41;
const s32		_ICODE_PUSHA_INSTRUCTION			= 42;
const s32		_ICODE_PUSHF_INSTRUCTION			= 43;
const s32		_ICODE_POPAD_INSTRUCTION			= 44;
const s32		_ICODE_POPFD_INSTRUCTION			= 45;
const s32		_ICODE_PUSHAD_INSTRUCTION			= 46;
const s32		_ICODE_PUSHFD_INSTRUCTION			= 47;
const s32		_ICODE_RETF_INSTRUCTION				= 48;
const s32		_ICODE_RETN_INSTRUCTION				= 49;
const s32		_ICODE_SAHF_INSTRUCTION				= 50;
const s32		_ICODE_SETA_INSTRUCTION				= 51;
const s32		_ICODE_SETC_INSTRUCTION				= 52;
const s32		_ICODE_SETG_INSTRUCTION				= 53;
const s32		_ICODE_SETL_INSTRUCTION				= 54;
const s32		_ICODE_SETNA_INSTRUCTION			= 55;
const s32		_ICODE_SETNC_INSTRUCTION			= 56;
const s32		_ICODE_SETNG_INSTRUCTION			= 57;
const s32		_ICODE_SETNL_INSTRUCTION			= 58;
const s32		_ICODE_SETNO_INSTRUCTION			= 59;
const s32		_ICODE_SETNS_INSTRUCTION			= 60;
const s32		_ICODE_SETNZ_INSTRUCTION			= 61;
const s32		_ICODE_SETO_INSTRUCTION				= 62;
const s32		_ICODE_SETPE_INSTRUCTION			= 63;
const s32		_ICODE_SETPO_INSTRUCTION			= 64;
const s32		_ICODE_SETS_INSTRUCTION				= 65;
const s32		_ICODE_SETZ_INSTRUCTION				= 66;
const s32		_ICODE_STC_INSTRUCTION				= 67;
const s32		_ICODE_STD_INSTRUCTION				= 68;
const s32		_ICODE_STI_INSTRUCTION				= 69;
const s32		_ICODE_WAIT_INSTRUCTION				= 70;
const s32		_ICODE_XLAT_INSTRUCTION				= 71;
const s32		_ICODE_REPE_INSTRUCTION				= 72;
const s32		_ICODE_REPNE_INSTRUCTION			= 73;
const s32		_ICODE_CMPSW_INSTRUCTION			= 74;
const s32		_ICODE_CMPSD_INSTRUCTION			= 75;
const s32		_ICODE_LODSW_INSTRUCTION			= 76;
const s32		_ICODE_LODSD_INSTRUCTION			= 77;
const s32		_ICODE_MOVSW_INSTRUCTION			= 78;
const s32		_ICODE_MOVSD_INSTRUCTION			= 79;
const s32		_ICODE_SCASW_INSTRUCTION			= 80;
const s32		_ICODE_SCASD_INSTRUCTION			= 81;
const s32		_ICODE_STOSW_INSTRUCTION			= 82;
const s32		_ICODE_STOSD_INSTRUCTION			= 83;
const s32		_ICODE_ARPL_INSTRUCTION				= 84;
const s32		_ICODE_BOUND_INSTRUCTION			= 85;
const s32		_ICODE_BSF_INSTRUCTION				= 86;
const s32		_ICODE_BSR_INSTRUCTION				= 87;
const s32		_ICODE_BT_INSTRUCTION				= 88;
const s32		_ICODE_BTC_INSTRUCTION				= 89;
const s32		_ICODE_BTR_INSTRUCTION				= 90;
const s32		_ICODE_BTS_INSTRUCTION				= 91;
const s32		_ICODE_CALL_INSTRUCTION				= 92;
const s32		_ICODE_CMOVA_INSTRUCTION			= 93;
const s32		_ICODE_CMOVC_INSTRUCTION			= 94;
const s32		_ICODE_CMOVG_INSTRUCTION			= 95;
const s32		_ICODE_CMOVL_INSTRUCTION			= 96;
const s32		_ICODE_CMOVNA_INSTRUCTION			= 97;
const s32		_ICODE_CMOVNC_INSTRUCTION			= 98;
const s32		_ICODE_CMOVNG_INSTRUCTION			= 99;
const s32		_ICODE_CMOVNL_INSTRUCTION			= 100;
const s32		_ICODE_CMOVNO_INSTRUCTION			= 101;
const s32		_ICODE_CMOVNS_INSTRUCTION			= 102;
const s32		_ICODE_CMOVNZ_INSTRUCTION			= 103;
const s32		_ICODE_CMOVO_INSTRUCTION			= 104;
const s32		_ICODE_CMOVPE_INSTRUCTION			= 105;
const s32		_ICODE_CMOVPO_INSTRUCTION			= 106;
const s32		_ICODE_CMOVS_INSTRUCTION			= 107;
const s32		_ICODE_CMOVZ_INSTRUCTION			= 108;
const s32		_ICODE_CMPXCHG_INSTRUCTION			= 109;
const s32		_ICODE_DEC_INSTRUCTION				= 110;
const s32		_ICODE_INC_INSTRUCTION				= 111;
const s32		_ICODE_IMUL_INSTRUCTION				= 112;
const s32		_ICODE_ICEBP_INSTRUCTION			= 113;
const s32		_ICODE_SLDT_INSTRUCTION				= 114;
const s32		_ICODE_LLDT_INSTRUCTION				= 115;
const s32		_ICODE_STR_INSTRUCTION				= 116;
const s32		_ICODE_VERR_INSTRUCTION				= 117;
const s32		_ICODE_VERW_INSTRUCTION				= 118;
const s32		_ICODE_LTR_INSTRUCTION				= 119;
const s32		_ICODE_UNK_INSTRUCTION				= 120;
const s32		_ICODE_SGDT_INSTRUCTION				= 121;
const s32		_ICODE_SIDT_INSTRUCTION				= 122;
const s32		_ICODE_LGDT_INSTRUCTION				= 123;
const s32		_ICODE_LIDT_INSTRUCTION				= 124;
const s32		_ICODE_LMSW_INSTRUCTION				= 125;
const s32		_ICODE_SMSW_INSTRUCTION				= 126;
const s32		_ICODE_INVLPG_INSTRUCTION			= 127;
const s32		_ICODE_PSRAW_INSTRUCTION			= 128;
const s32		_ICODE_PSRAD_INSTRUCTION			= 129;
const s32		_ICODE_PSRLD_INSTRUCTION			= 130;
const s32		_ICODE_PSRLW_INSTRUCTION			= 131;
const s32		_ICODE_PSRLQ_INSTRUCTION			= 132;
const s32		_ICODE_PSUBB_INSTRUCTION			= 133;
const s32		_ICODE_PSUBW_INSTRUCTION			= 134;
const s32		_ICODE_PSUBD_INSTRUCTION			= 135;
const s32		_ICODE_PSUBSB_INSTRUCTION			= 136;
const s32		_ICODE_PSUBSW_INSTRUCTION			= 137;
const s32		_ICODE_PSUBUSB_INSTRUCTION			= 138;
const s32		_ICODE_PSUBUSW_INSTRUCTION			= 139;
const s32		_ICODE_PUNPCKHBW_INSTRUCTION		= 140;
const s32		_ICODE_PUNPCKHWD_INSTRUCTION		= 141;
const s32		_ICODE_PUNPCKHDQ_INSTRUCTION		= 142;
const s32		_ICODE_PUNPCKLBW_INSTRUCTION		= 143;
const s32		_ICODE_PUNPCKLWD_INSTRUCTION		= 144;
const s32		_ICODE_PUNPCKLDQ_INSTRUCTION		= 145;
const s32		_ICODE_PXOR_INSTRUCTION				= 146;
const s32		_ICODE_RSM_INSTRUCTION				= 147;
const s32		_ICODE_SHLD_INSTRUCTION				= 148;
const s32		_ICODE_SHRD_INSTRUCTION				= 149;
const s32		_ICODE_TEST_INSTRUCTION				= 150;
const s32		_ICODE_XCHG_INSTRUCTION				= 151;
const s32		_ICODE_UD2_INSTRUCTION				= 152;
const s32		_ICODE_WRMSR_INSTRUCTION			= 153;
const s32		_ICODE_WBINVD_INSTRUCTION			= 154;
const s32		_ICODE_XADD_INSTRUCTION				= 155;
const s32		_ICODE_PACKSSDW_INSTRUCTION			= 156;
const s32		_ICODE_PACKSSWB_INSTRUCTION			= 157;
const s32		_ICODE_PACKUSWB_INSTRUCTION			= 158;
const s32		_ICODE_PADDB_INSTRUCTION			= 159;
const s32		_ICODE_PADDD_INSTRUCTION			= 160;
const s32		_ICODE_PADDSB_INSTRUCTION			= 161;
const s32		_ICODE_PADDSW_INSTRUCTION			= 162;
const s32		_ICODE_PADDUSB_INSTRUCTION			= 163;
const s32		_ICODE_PADDUSW_INSTRUCTION			= 164;
const s32		_ICODE_PADDW_INSTRUCTION			= 165;
const s32		_ICODE_PAND_INSTRUCTION				= 166;
const s32		_ICODE_PANDN_INSTRUCTION			= 167;
const s32		_ICODE_PCMPEQB_INSTRUCTION			= 168;
const s32		_ICODE_PCMPEQD_INSTRUCTION			= 169;
const s32		_ICODE_PCMPEQW_INSTRUCTION			= 170;
const s32		_ICODE_PCMPGTB_INSTRUCTION			= 171;
const s32		_ICODE_PCMPGTD_INSTRUCTION			= 172;
const s32		_ICODE_PCMPGTW_INSTRUCTION			= 173;
const s32		_ICODE_PMADDWD_INSTRUCTION			= 174;
const s32		_ICODE_PMULHW_INSTRUCTION			= 175;
const s32		_ICODE_PMULLW_INSTRUCTION			= 176;
const s32		_ICODE_POR_INSTRUCTION				= 177;
const s32		_ICODE_PSLLD_INSTRUCTION			= 178;
const s32		_ICODE_PSLLQ_INSTRUCTION			= 179;
const s32		_ICODE_PSLLW_INSTRUCTION			= 180;
const s32		_ICODE_OR_INSTRUCTION				= 181;
const s32		_ICODE_HCF_INSTRUCTION				= 182;
const s32		_ICODE_CMPXCHG8B_INSTRUCTION		= 183;
const s32		_ICODE_IN_INSTRUCTION				= 184;
const s32		_ICODE_RDMSR_INSTRUCTION			= 185;
const s32		_ICODE_RDPMC_INSTRUCTION			= 186;
const s32		_ICODE_RDTSC_INSTRUCTION			= 187;
const s32		_ICODE_MOVSX_INSTRUCTION			= 188;
const s32		_ICODE_MOVZX_INSTRUCTION			= 189;
const s32		_ICODE_LSL_INSTRUCTION				= 190;
const s32		_ICODE_LSS_INSTRUCTION				= 191;
const s32		_ICODE_LOOPNE_INSTRUCTION			= 192;
const s32		_ICODE_LOOPE_INSTRUCTION			= 193;
const s32		_ICODE_LOOP_INSTRUCTION				= 194;
const s32		_ICODE_LGS_INSTRUCTION				= 195;
const s32		_ICODE_LFS_INSTRUCTION				= 196;
const s32		_ICODE_LES_INSTRUCTION				= 197;
const s32		_ICODE_LEA_INSTRUCTION				= 198;
const s32		_ICODE_LDS_INSTRUCTION				= 199;
const s32		_ICODE_LAR_INSTRUCTION				= 200;
const s32		_ICODE_JZ_INSTRUCTION				= 201;
const s32		_ICODE_JS_INSTRUCTION				= 202;
const s32		_ICODE_JPO_INSTRUCTION				= 203;
const s32		_ICODE_JPE_INSTRUCTION				= 204;
const s32		_ICODE_JO_INSTRUCTION				= 205;
const s32		_ICODE_JNZ_INSTRUCTION				= 206;
const s32		_ICODE_JNO_INSTRUCTION				= 207;
const s32		_ICODE_JNL_INSTRUCTION				= 208;
const s32		_ICODE_JNG_INSTRUCTION				= 209;
const s32		_ICODE_JNC_INSTRUCTION				= 210;
const s32		_ICODE_JNA_INSTRUCTION				= 211;
const s32		_ICODE_JMP_INSTRUCTION				= 212;
const s32		_ICODE_JL_INSTRUCTION				= 213;
const s32		_ICODE_JG_INSTRUCTION				= 214;
const s32		_ICODE_JCXZ_INSTRUCTION				= 215;
const s32		_ICODE_JECXZ_INSTRUCTION			= 216;
const s32		_ICODE_JC_INSTRUCTION				= 217;
const s32		_ICODE_JA_INSTRUCTION				= 218;
const s32		_ICODE_JNS_INSTRUCTION				= 219;
const s32		_ICODE_INVD_INSTRUCTION				= 220;
const s32		_ICODE_IDIV_INSTRUCTION				= 221;
const s32		_ICODE_DIV_INSTRUCTION				= 222;
const s32		_ICODE_NEG_INSTRUCTION				= 223;
const s32		_ICODE_MUL_INSTRUCTION				= 224;
const s32		_ICODE_NOT_INSTRUCTION				= 225;
const s32		_ICODE_SAR_INSTRUCTION				= 226;
const s32		_ICODE_SHR_INSTRUCTION				= 227;
const s32		_ICODE_SHL_INSTRUCTION				= 228;
const s32		_ICODE_RCR_INSTRUCTION				= 229;
const s32		_ICODE_RCL_INSTRUCTION				= 230;
const s32		_ICODE_ROR_INSTRUCTION				= 231;
const s32		_ICODE_ROL_INSTRUCTION				= 232;
const s32		_ICODE_MOV_INSTRUCTION				= 233;
const s32		_ICODE_FNOP_INSTRUCTION				= 234;
const s32		_ICODE_FCHS_INSTRUCTION				= 235;
const s32		_ICODE_FABS_INSTRUCTION				= 236;
const s32		_ICODE_FTST_INSTRUCTION				= 237;
const s32		_ICODE_FXAM_INSTRUCTION				= 238;
const s32		_ICODE_FLD1_INSTRUCTION				= 239;
const s32		_ICODE_FLD2T_INSTRUCTION			= 240;
const s32		_ICODE_FLD2E_INSTRUCTION			= 241;
const s32		_ICODE_FLDPI_INSTRUCTION			= 242;
const s32		_ICODE_FLDLG2_INSTRUCTION			= 243;
const s32		_ICODE_FLDLN2_INSTRUCTION			= 244;
const s32		_ICODE_FLDZ_INSTRUCTION				= 245;
const s32		_ICODE_F2XM1_INSTRUCTION			= 246;
const s32		_ICODE_FYL2X_INSTRUCTION			= 247;
const s32		_ICODE_FPTAN_INSTRUCTION			= 248;
const s32		_ICODE_FPATAN_INSTRUCTION			= 249;
const s32		_ICODE_FXTRACT_INSTRUCTION			= 250;
const s32		_ICODE_FPREM1_INSTRUCTION			= 251;
const s32		_ICODE_FDECSTP_INSTRUCTION			= 252;
const s32		_ICODE_FINCSTP_INSTRUCTION			= 253;
const s32		_ICODE_FPREM_INSTRUCTION			= 254;
const s32		_ICODE_FYL2XP1_INSTRUCTION			= 255;
const s32		_ICODE_FSQRT_INSTRUCTION			= 256;
const s32		_ICODE_FSINCOS_INSTRUCTION			= 257;
const s32		_ICODE_FRNDINT_INSTRUCTION			= 258;
const s32		_ICODE_FSCALE_INSTRUCTION			= 259;
const s32		_ICODE_FSIN_INSTRUCTION				= 260;
const s32		_ICODE_FCOS_INSTRUCTION				= 261;
const s32		_ICODE_FADD_INSTRUCTION				= 262;
const s32		_ICODE_FMUL_INSTRUCTION				= 263;
const s32		_ICODE_FCOM_INSTRUCTION				= 264;
const s32		_ICODE_FCOMP_INSTRUCTION			= 265;
const s32		_ICODE_FSUB_INSTRUCTION				= 266;
const s32		_ICODE_FSUBR_INSTRUCTION			= 267;
const s32		_ICODE_FDIV_INSTRUCTION				= 268;
const s32		_ICODE_FDIVR_INSTRUCTION			= 269;
const s32		_ICODE_FLD_INSTRUCTION				= 270;
const s32		_ICODE_FST_INSTRUCTION				= 271;
const s32		_ICODE_FSTP_INSTRUCTION				= 272;
const s32		_ICODE_FIADD_INSTRUCTION			= 273;
const s32		_ICODE_FIMUL_INSTRUCTION			= 274;
const s32		_ICODE_FICOM_INSTRUCTION			= 275;
const s32		_ICODE_FICOMP_INSTRUCTION			= 276;
const s32		_ICODE_FISUB_INSTRUCTION			= 277;
const s32		_ICODE_FISUBR_INSTRUCTION			= 278;
const s32		_ICODE_FIDIV_INSTRUCTION			= 279;
const s32		_ICODE_FIDIVR_INSTRUCTION			= 280;
const s32		_ICODE_FIST_INSTRUCTION				= 281;
const s32		_ICODE_FISTP_INSTRUCTION			= 282;
const s32		_ICODE_FILD_INSTRUCTION				= 283;
const s32		_ICODE_FBLD_INSTRUCTION				= 284;
const s32		_ICODE_FBSTP_INSTRUCTION			= 285;
const s32		_ICODE_FXCH_INSTRUCTION				= 286;
const s32		_ICODE_FUCOMP_INSTRUCTION			= 287;
const s32		_ICODE_FUCOMPP_INSTRUCTION			= 288;
const s32		_ICODE_FNCLEX_INSTRUCTION			= 289;
const s32		_ICODE_FNINIT_INSTRUCTION			= 290;
const s32		_ICODE_FNSTSW_INSTRUCTION			= 291;
const s32		_ICODE_FLDCW_INSTRUCTION			= 292;
const s32		_ICODE_FNSTCW_INSTRUCTION			= 293;
const s32		_ICODE_FLDENV_INSTRUCTION			= 294;
const s32		_ICODE_FNSTENV_INSTRUCTION			= 295;
const s32		_ICODE_FRSTOR_INSTRUCTION			= 296;
const s32		_ICODE_FNSAVE_INSTRUCTION			= 297;

const s32		_ICODE_PTR_TBYTE					= 1000;
const s32		_ICODE_PTR_DQWORD					= 1001;
const s32		_ICODE_PTR_QWORD					= 1002;
const s32		_ICODE_PTR_DWORD					= 1003;
const s32		_ICODE_PTR_WORD						= 1004;
const s32		_ICODE_PTR_BYTE						= 1005;
const s32		_ICODE_PTR_M16_16					= 1006;
const s32		_ICODE_PTR_M16_32					= 1007;
const s32		_ICODE_PTR_F32						= 1008;
const s32		_ICODE_PTR_F64						= 1009;
const s32		_ICODE_PTR_F80						= 1010;
const s32		_ICODE_PTR_S16						= 1011;
const s32		_ICODE_PTR_S32						= 1012;
const s32		_ICODE_PTR_S64						= 1013;
const s32		_ICODE_PTR_M80						= 1014;
const s32		_ICODE_PTR_MMX						= 1015;
const s32		_ICODE_PTR_XMMX						= 1016;
const s32		_ICODE_PTR_FPU						= 1017;
const s32		_ICODE_PTR_6BYTE					= 1018;
const s32		_ICODE_PTR_10BYTE					= 1019;
const s32		_ICODE_PTR_14BYTE					= 1020;
const s32		_ICODE_PTR_28BYTE					= 1021;
const s32		_ICODE_PTR_94BYTE					= 1022;
const s32		_ICODE_PTR_108BYTE					= 1023;

const s32		_ICODE_PLUS_SIGN					= 1100;
const s32		_ICODE_MINUS_SIGN					= 1101;

const s32		_ICODE_CS							= 1200;
const s32		_ICODE_DS							= 1200;
const s32		_ICODE_ES							= 1200;
const s32		_ICODE_FS							= 1200;
const s32		_ICODE_GS							= 1200;
const s32		_ICODE_SS							= 1200;

const s32		_ICODE_AL							= 1300;
const s32		_ICODE_BL							= 1301;
const s32		_ICODE_CL							= 1302;
const s32		_ICODE_DL							= 1303;
const s32		_ICODE_AH							= 1304;
const s32		_ICODE_BH							= 1305;
const s32		_ICODE_CH							= 1306;
const s32		_ICODE_DH							= 1307;

const s32		_ICODE_AX							= 1400;
const s32		_ICODE_BX							= 1401;
const s32		_ICODE_CX							= 1402;
const s32		_ICODE_DX							= 1403;
const s32		_ICODE_SI							= 1404;
const s32		_ICODE_DI							= 1405;
const s32		_ICODE_BP							= 1406;
const s32		_ICODE_SP							= 1407;
const s32		_ICODE_IP							= 1408;

const s32		_ICODE_EAX							= 1500;
const s32		_ICODE_EBX							= 1501;
const s32		_ICODE_ECX							= 1502;
const s32		_ICODE_EDX							= 1503;
const s32		_ICODE_ESI							= 1504;
const s32		_ICODE_EDI							= 1505;
const s32		_ICODE_EBP							= 1506;
const s32		_ICODE_ESP							= 1507;
const s32		_ICODE_EIP							= 1508;

const s32		_ICODE_CR0							= 1600;
const s32		_ICODE_CR1							= 1601;
const s32		_ICODE_CR2							= 1602;
const s32		_ICODE_CR3							= 1603;
const s32		_ICODE_CR4							= 1604;
const s32		_ICODE_CR5							= 1605;
const s32		_ICODE_CR6							= 1606;
const s32		_ICODE_CR7							= 1607;

const s32		_ICODE_DR0							= 1700;
const s32		_ICODE_DR1							= 1701;
const s32		_ICODE_DR2							= 1702;
const s32		_ICODE_DR3							= 1703;
const s32		_ICODE_DR4							= 1704;
const s32		_ICODE_DR5							= 1705;
const s32		_ICODE_DR6							= 1706;
const s32		_ICODE_DR7							= 1707;

const s32		_ICODE_TR0							= 1800;
const s32		_ICODE_TR1							= 1801;
const s32		_ICODE_TR2							= 1802;
const s32		_ICODE_TR3							= 1803;
const s32		_ICODE_TR4							= 1804;
const s32		_ICODE_TR5							= 1805;
const s32		_ICODE_TR6							= 1806;
const s32		_ICODE_TR7							= 1807;

const s32		_ICODE_ST0							= 1900;
const s32		_ICODE_ST1							= 1901;
const s32		_ICODE_ST2							= 1902;
const s32		_ICODE_ST3							= 1903;
const s32		_ICODE_ST4							= 1904;
const s32		_ICODE_ST5							= 1905;
const s32		_ICODE_ST6							= 1906;
const s32		_ICODE_ST7							= 1907;

const s32		_ICODE_MM0							= 2000;
const s32		_ICODE_MM1							= 2001;
const s32		_ICODE_MM2							= 2002;
const s32		_ICODE_MM3							= 2003;
const s32		_ICODE_MM4							= 2004;
const s32		_ICODE_MM5							= 2005;
const s32		_ICODE_MM6							= 2006;
const s32		_ICODE_MM7							= 2007;

const s32		_ICODE_XMM0							= 2100;
const s32		_ICODE_XMM1							= 2101;
const s32		_ICODE_XMM2							= 2102;
const s32		_ICODE_XMM3							= 2103;
const s32		_ICODE_XMM4							= 2104;
const s32		_ICODE_XMM5							= 2105;
const s32		_ICODE_XMM6							= 2106;
const s32		_ICODE_XMM7							= 2107;
