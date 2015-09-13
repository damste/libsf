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

const s32		_ICODE__ADD_INSTRUCTION				= 1;
const s32		_ICODE__ADC_INSTRUCTION				= 2;
const s32		_ICODE__AND_INSTRUCTION				= 3;
const s32		_ICODE__SUB_INSTRUCTION				= 4;
const s32		_ICODE__SBB_INSTRUCTION				= 5;
const s32		_ICODE__XOR_INSTRUCTION				= 6;
const s32		_ICODE__CMP_INSTRUCTION				= 7;
const s32		_ICODE__BSWAP_INSTRUCTION			= 8;
const s32		_ICODE__AAA_INSTRUCTION				= 9;
const s32		_ICODE__AAD_INSTRUCTION				= 10;
const s32		_ICODE__AAM_INSTRUCTION				= 11;
const s32		_ICODE__AAS_INSTRUCTION				= 12;
const s32		_ICODE__CBW_INSTRUCTION				= 13;
const s32		_ICODE__CLC_INSTRUCTION				= 14;
const s32		_ICODE__CLD_INSTRUCTION				= 15;
const s32		_ICODE__CLI_INSTRUCTION				= 16;
const s32		_ICODE__CLTS_INSTRUCTION			= 17;
const s32		_ICODE__CMC_INSTRUCTION				= 18;
const s32		_ICODE__CPUID_INSTRUCTION			= 19;
const s32		_ICODE__CWD_INSTRUCTION				= 20;
const s32		_ICODE__DAA_INSTRUCTION				= 21;
const s32		_ICODE__EMMS_INSTRUCTION			= 22;
const s32		_ICODE__DAS_INSTRUCTION				= 23;
const s32		_ICODE__HLT_INSTRUCTION				= 24;
const s32		_ICODE__INSB_INSTRUCTION			= 25;
const s32		_ICODE__INSD_INSTRUCTION			= 26;
const s32		_ICODE__INSW_INSTRUCTION			= 27;
const s32		_ICODE__INT3_INSTRUCTION			= 28;
const s32		_ICODE__INT_INSTRUCTION				= 29;
const s32		_ICODE__INTO_INSTRUCTION			= 30;
const s32		_ICODE__IRET_INSTRUCTION			= 31;
const s32		_ICODE__LAHF_INSTRUCTION			= 32;
const s32		_ICODE__LEAVE_INSTRUCTION			= 33;
const s32		_ICODE__NOP_INSTRUCTION				= 34;
const s32		_ICODE__OUTSB_INSTRUCTION			= 35;
const s32		_ICODE__OUTSD_INSTRUCTION			= 36;
const s32		_ICODE__OUTSW_INSTRUCTION			= 37;
const s32		_ICODE__POP_INSTRUCTION				= 38;
const s32		_ICODE__PUSH_INSTRUCTION			= 39;
const s32		_ICODE__POPA_INSTRUCTION			= 40;
const s32		_ICODE__POPF_INSTRUCTION			= 41;
const s32		_ICODE__PUSHA_INSTRUCTION			= 42;
const s32		_ICODE__PUSHF_INSTRUCTION			= 43;
const s32		_ICODE__POPAD_INSTRUCTION			= 44;
const s32		_ICODE__POPFD_INSTRUCTION			= 45;
const s32		_ICODE__PUSHAD_INSTRUCTION			= 46;
const s32		_ICODE__PUSHFD_INSTRUCTION			= 47;
const s32		_ICODE__RETF_INSTRUCTION			= 48;
const s32		_ICODE__RETN_INSTRUCTION			= 49;
const s32		_ICODE__SAHF_INSTRUCTION			= 50;
const s32		_ICODE__SETA_INSTRUCTION			= 51;
const s32		_ICODE__SETC_INSTRUCTION			= 52;
const s32		_ICODE__SETG_INSTRUCTION			= 53;
const s32		_ICODE__SETL_INSTRUCTION			= 54;
const s32		_ICODE__SETNA_INSTRUCTION			= 55;
const s32		_ICODE__SETNC_INSTRUCTION			= 56;
const s32		_ICODE__SETNG_INSTRUCTION			= 57;
const s32		_ICODE__SETNL_INSTRUCTION			= 58;
const s32		_ICODE__SETNO_INSTRUCTION			= 59;
const s32		_ICODE__SETNS_INSTRUCTION			= 60;
const s32		_ICODE__SETNZ_INSTRUCTION			= 61;
const s32		_ICODE__SETO_INSTRUCTION			= 62;
const s32		_ICODE__SETPE_INSTRUCTION			= 63;
const s32		_ICODE__SETPO_INSTRUCTION			= 64;
const s32		_ICODE__SETS_INSTRUCTION			= 65;
const s32		_ICODE__SETZ_INSTRUCTION			= 66;
const s32		_ICODE__STC_INSTRUCTION				= 67;
const s32		_ICODE__STD_INSTRUCTION				= 68;
const s32		_ICODE__STI_INSTRUCTION				= 69;
const s32		_ICODE__WAIT_INSTRUCTION			= 70;
const s32		_ICODE__XLAT_INSTRUCTION			= 71;
const s32		_ICODE__REPE_INSTRUCTION			= 72;
const s32		_ICODE__REPNE_INSTRUCTION			= 73;
const s32		_ICODE__CMPSW_INSTRUCTION			= 74;
const s32		_ICODE__CMPSD_INSTRUCTION			= 75;
const s32		_ICODE__LODSW_INSTRUCTION			= 76;
const s32		_ICODE__LODSD_INSTRUCTION			= 77;
const s32		_ICODE__MOVSW_INSTRUCTION			= 78;
const s32		_ICODE__MOVSD_INSTRUCTION			= 79;
const s32		_ICODE__SCASW_INSTRUCTION			= 80;
const s32		_ICODE__SCASD_INSTRUCTION			= 81;
const s32		_ICODE__STOSW_INSTRUCTION			= 82;
const s32		_ICODE__STOSD_INSTRUCTION			= 83;
const s32		_ICODE__ARPL_INSTRUCTION			= 84;
const s32		_ICODE__BOUND_INSTRUCTION			= 85;
const s32		_ICODE__BSF_INSTRUCTION				= 86;
const s32		_ICODE__BSR_INSTRUCTION				= 87;
const s32		_ICODE__BT_INSTRUCTION				= 88;
const s32		_ICODE__BTC_INSTRUCTION				= 89;
const s32		_ICODE__BTR_INSTRUCTION				= 90;
const s32		_ICODE__BTS_INSTRUCTION				= 91;
const s32		_ICODE__CALL_INSTRUCTION			= 92;
const s32		_ICODE__CMOVA_INSTRUCTION			= 93;
const s32		_ICODE__CMOVC_INSTRUCTION			= 94;
const s32		_ICODE__CMOVG_INSTRUCTION			= 95;
const s32		_ICODE__CMOVL_INSTRUCTION			= 96;
const s32		_ICODE__CMOVNA_INSTRUCTION			= 97;
const s32		_ICODE__CMOVNC_INSTRUCTION			= 98;
const s32		_ICODE__CMOVNG_INSTRUCTION			= 99;
const s32		_ICODE__CMOVNL_INSTRUCTION			= 100;
const s32		_ICODE__CMOVNO_INSTRUCTION			= 101;
const s32		_ICODE__CMOVNS_INSTRUCTION			= 102;
const s32		_ICODE__CMOVNZ_INSTRUCTION			= 103;
const s32		_ICODE__CMOVO_INSTRUCTION			= 104;
const s32		_ICODE__CMOVPE_INSTRUCTION			= 105;
const s32		_ICODE__CMOVPO_INSTRUCTION			= 106;
const s32		_ICODE__CMOVS_INSTRUCTION			= 107;
const s32		_ICODE__CMOVZ_INSTRUCTION			= 108;
const s32		_ICODE__CMPXCHG_INSTRUCTION			= 109;
const s32		_ICODE__DEC_INSTRUCTION				= 110;
const s32		_ICODE__INC_INSTRUCTION				= 111;
const s32		_ICODE__IMUL_INSTRUCTION			= 112;
const s32		_ICODE__ICEBP_INSTRUCTION			= 113;
const s32		_ICODE__SLDT_INSTRUCTION			= 114;
const s32		_ICODE__LLDT_INSTRUCTION			= 115;
const s32		_ICODE__STR_INSTRUCTION				= 116;
const s32		_ICODE__VERR_INSTRUCTION			= 117;
const s32		_ICODE__VERW_INSTRUCTION			= 118;
const s32		_ICODE__LTR_INSTRUCTION				= 119;
const s32		_ICODE__UNK_INSTRUCTION				= 120;
const s32		_ICODE__SGDT_INSTRUCTION			= 121;
const s32		_ICODE__SIDT_INSTRUCTION			= 122;
const s32		_ICODE__LGDT_INSTRUCTION			= 123;
const s32		_ICODE__LIDT_INSTRUCTION			= 124;
const s32		_ICODE__LMSW_INSTRUCTION			= 125;
const s32		_ICODE__SMSW_INSTRUCTION			= 126;
const s32		_ICODE__INVLPG_INSTRUCTION			= 127;
const s32		_ICODE__PSRAW_INSTRUCTION			= 128;
const s32		_ICODE__PSRAD_INSTRUCTION			= 129;
const s32		_ICODE__PSRLD_INSTRUCTION			= 130;
const s32		_ICODE__PSRLW_INSTRUCTION			= 131;
const s32		_ICODE__PSRLQ_INSTRUCTION			= 132;
const s32		_ICODE__PSUBB_INSTRUCTION			= 133;
const s32		_ICODE__PSUBW_INSTRUCTION			= 134;
const s32		_ICODE__PSUBD_INSTRUCTION			= 135;
const s32		_ICODE__PSUBSB_INSTRUCTION			= 136;
const s32		_ICODE__PSUBSW_INSTRUCTION			= 137;
const s32		_ICODE__PSUBUSB_INSTRUCTION			= 138;
const s32		_ICODE__PSUBUSW_INSTRUCTION			= 139;
const s32		_ICODE__PUNPCKHBW_INSTRUCTION		= 140;
const s32		_ICODE__PUNPCKHWD_INSTRUCTION		= 141;
const s32		_ICODE__PUNPCKHDQ_INSTRUCTION		= 142;
const s32		_ICODE__PUNPCKLBW_INSTRUCTION		= 143;
const s32		_ICODE__PUNPCKLWD_INSTRUCTION		= 144;
const s32		_ICODE__PUNPCKLDQ_INSTRUCTION		= 145;
const s32		_ICODE__PXOR_INSTRUCTION			= 146;
const s32		_ICODE__RSM_INSTRUCTION				= 147;
const s32		_ICODE__SHLD_INSTRUCTION			= 148;
const s32		_ICODE__SHRD_INSTRUCTION			= 149;
const s32		_ICODE__TEST_INSTRUCTION			= 150;
const s32		_ICODE__XCHG_INSTRUCTION			= 151;
const s32		_ICODE__UD2_INSTRUCTION				= 152;
const s32		_ICODE__WRMSR_INSTRUCTION			= 153;
const s32		_ICODE__WBINVD_INSTRUCTION			= 154;
const s32		_ICODE__XADD_INSTRUCTION			= 155;
const s32		_ICODE__PACKSSDW_INSTRUCTION		= 156;
const s32		_ICODE__PACKSSWB_INSTRUCTION		= 157;
const s32		_ICODE__PACKUSWB_INSTRUCTION		= 158;
const s32		_ICODE__PADDB_INSTRUCTION			= 159;
const s32		_ICODE__PADDD_INSTRUCTION			= 160;
const s32		_ICODE__PADDSB_INSTRUCTION			= 161;
const s32		_ICODE__PADDSW_INSTRUCTION			= 162;
const s32		_ICODE__PADDUSB_INSTRUCTION			= 163;
const s32		_ICODE__PADDUSW_INSTRUCTION			= 164;
const s32		_ICODE__PADDW_INSTRUCTION			= 165;
const s32		_ICODE__PAND_INSTRUCTION			= 166;
const s32		_ICODE__PANDN_INSTRUCTION			= 167;
const s32		_ICODE__PCMPEQB_INSTRUCTION			= 168;
const s32		_ICODE__PCMPEQD_INSTRUCTION			= 169;
const s32		_ICODE__PCMPEQW_INSTRUCTION			= 170;
const s32		_ICODE__PCMPGTB_INSTRUCTION			= 171;
const s32		_ICODE__PCMPGTD_INSTRUCTION			= 172;
const s32		_ICODE__PCMPGTW_INSTRUCTION			= 173;
const s32		_ICODE__PMADDWD_INSTRUCTION			= 174;
const s32		_ICODE__PMULHW_INSTRUCTION			= 175;
const s32		_ICODE__PMULLW_INSTRUCTION			= 176;
const s32		_ICODE__POR_INSTRUCTION				= 177;
const s32		_ICODE__PSLLD_INSTRUCTION			= 178;
const s32		_ICODE__PSLLQ_INSTRUCTION			= 179;
const s32		_ICODE__PSLLW_INSTRUCTION			= 180;
const s32		_ICODE__OR_INSTRUCTION				= 181;
const s32		_ICODE__HCF_INSTRUCTION				= 182;
const s32		_ICODE__CMPXCHG8B_INSTRUCTION		= 183;
const s32		_ICODE__IN_INSTRUCTION				= 184;
const s32		_ICODE__RDMSR_INSTRUCTION			= 185;
const s32		_ICODE__RDPMC_INSTRUCTION			= 186;
const s32		_ICODE__RDTSC_INSTRUCTION			= 187;
const s32		_ICODE__MOVSX_INSTRUCTION			= 188;
const s32		_ICODE__MOVZX_INSTRUCTION			= 189;
const s32		_ICODE__LSL_INSTRUCTION				= 190;
const s32		_ICODE__LSS_INSTRUCTION				= 191;
const s32		_ICODE__LOOPNE_INSTRUCTION			= 192;
const s32		_ICODE__LOOPE_INSTRUCTION			= 193;
const s32		_ICODE__LOOP_INSTRUCTION			= 194;
const s32		_ICODE__LGS_INSTRUCTION				= 195;
const s32		_ICODE__LFS_INSTRUCTION				= 196;
const s32		_ICODE__LES_INSTRUCTION				= 197;
const s32		_ICODE__LEA_INSTRUCTION				= 198;
const s32		_ICODE__LDS_INSTRUCTION				= 199;
const s32		_ICODE__LAR_INSTRUCTION				= 200;
const s32		_ICODE__JZ_INSTRUCTION				= 201;
const s32		_ICODE__JS_INSTRUCTION				= 202;
const s32		_ICODE__JPO_INSTRUCTION				= 203;
const s32		_ICODE__JPE_INSTRUCTION				= 204;
const s32		_ICODE__JO_INSTRUCTION				= 205;
const s32		_ICODE__JNZ_INSTRUCTION				= 206;
const s32		_ICODE__JNO_INSTRUCTION				= 207;
const s32		_ICODE__JNL_INSTRUCTION				= 208;
const s32		_ICODE__JNG_INSTRUCTION				= 209;
const s32		_ICODE__JNC_INSTRUCTION				= 210;
const s32		_ICODE__JNA_INSTRUCTION				= 211;
const s32		_ICODE__JMP_INSTRUCTION				= 212;
const s32		_ICODE__JL_INSTRUCTION				= 213;
const s32		_ICODE__JG_INSTRUCTION				= 214;
const s32		_ICODE__JCXZ_INSTRUCTION			= 215;
const s32		_ICODE__JECXZ_INSTRUCTION			= 216;
const s32		_ICODE__JC_INSTRUCTION				= 217;
const s32		_ICODE__JA_INSTRUCTION				= 218;
const s32		_ICODE__JNS_INSTRUCTION				= 219;
const s32		_ICODE__INVD_INSTRUCTION			= 220;
const s32		_ICODE__IDIV_INSTRUCTION			= 221;
const s32		_ICODE__DIV_INSTRUCTION				= 222;
const s32		_ICODE__NEG_INSTRUCTION				= 223;
const s32		_ICODE__MUL_INSTRUCTION				= 224;
const s32		_ICODE__NOT_INSTRUCTION				= 225;
const s32		_ICODE__SAR_INSTRUCTION				= 226;
const s32		_ICODE__SHR_INSTRUCTION				= 227;
const s32		_ICODE__SHL_INSTRUCTION				= 228;
const s32		_ICODE__RCR_INSTRUCTION				= 229;
const s32		_ICODE__RCL_INSTRUCTION				= 230;
const s32		_ICODE__ROR_INSTRUCTION				= 231;
const s32		_ICODE__ROL_INSTRUCTION				= 232;
const s32		_ICODE__MOV_INSTRUCTION				= 233;
const s32		_ICODE__FNOP_INSTRUCTION			= 234;
const s32		_ICODE__FCHS_INSTRUCTION			= 235;
const s32		_ICODE__FABS_INSTRUCTION			= 236;
const s32		_ICODE__FTST_INSTRUCTION			= 237;
const s32		_ICODE__FXAM_INSTRUCTION			= 238;
const s32		_ICODE__FLD1_INSTRUCTION			= 239;
const s32		_ICODE__FLD2T_INSTRUCTION			= 240;
const s32		_ICODE__FLD2E_INSTRUCTION			= 241;
const s32		_ICODE__FLDPI_INSTRUCTION			= 242;
const s32		_ICODE__FLDLG2_INSTRUCTION			= 243;
const s32		_ICODE__FLDLN2_INSTRUCTION			= 244;
const s32		_ICODE__FLDZ_INSTRUCTION			= 245;
const s32		_ICODE__F2XM1_INSTRUCTION			= 246;
const s32		_ICODE__FYL2X_INSTRUCTION			= 247;
const s32		_ICODE__FPTAN_INSTRUCTION			= 248;
const s32		_ICODE__FPATAN_INSTRUCTION			= 249;
const s32		_ICODE__FXTRACT_INSTRUCTION			= 250;
const s32		_ICODE__FPREM1_INSTRUCTION			= 251;
const s32		_ICODE__FDECSTP_INSTRUCTION			= 252;
const s32		_ICODE__FINCSTP_INSTRUCTION			= 253;
const s32		_ICODE__FPREM_INSTRUCTION			= 254;
const s32		_ICODE__FYL2XP1_INSTRUCTION			= 255;
const s32		_ICODE__FSQRT_INSTRUCTION			= 256;
const s32		_ICODE__FSINCOS_INSTRUCTION			= 257;
const s32		_ICODE__FRNDINT_INSTRUCTION			= 258;
const s32		_ICODE__FSCALE_INSTRUCTION			= 259;
const s32		_ICODE__FSIN_INSTRUCTION			= 260;
const s32		_ICODE__FCOS_INSTRUCTION			= 261;
const s32		_ICODE__FADD_INSTRUCTION			= 262;
const s32		_ICODE__FMUL_INSTRUCTION			= 263;
const s32		_ICODE__FCOM_INSTRUCTION			= 264;
const s32		_ICODE__FCOMP_INSTRUCTION			= 265;
const s32		_ICODE__FSUB_INSTRUCTION			= 266;
const s32		_ICODE__FSUBR_INSTRUCTION			= 267;
const s32		_ICODE__FDIV_INSTRUCTION			= 268;
const s32		_ICODE__FDIVR_INSTRUCTION			= 269;
const s32		_ICODE__FLD_INSTRUCTION				= 270;
const s32		_ICODE__FST_INSTRUCTION				= 271;
const s32		_ICODE__FSTP_INSTRUCTION			= 272;
const s32		_ICODE__FIADD_INSTRUCTION			= 273;
const s32		_ICODE__FIMUL_INSTRUCTION			= 274;
const s32		_ICODE__FICOM_INSTRUCTION			= 275;
const s32		_ICODE__FICOMP_INSTRUCTION			= 276;
const s32		_ICODE__FISUB_INSTRUCTION			= 277;
const s32		_ICODE__FISUBR_INSTRUCTION			= 278;
const s32		_ICODE__FIDIV_INSTRUCTION			= 279;
const s32		_ICODE__FIDIVR_INSTRUCTION			= 280;
const s32		_ICODE__FIST_INSTRUCTION			= 281;
const s32		_ICODE__FISTP_INSTRUCTION			= 282;
const s32		_ICODE__FILD_INSTRUCTION			= 283;
const s32		_ICODE__FBLD_INSTRUCTION			= 284;
const s32		_ICODE__FBSTP_INSTRUCTION			= 285;
const s32		_ICODE__FXCH_INSTRUCTION			= 286;
const s32		_ICODE__FUCOMP_INSTRUCTION			= 287;
const s32		_ICODE__FUCOMPP_INSTRUCTION			= 288;
const s32		_ICODE__FNCLEX_INSTRUCTION			= 289;
const s32		_ICODE__FNINIT_INSTRUCTION			= 290;
const s32		_ICODE__FNSTSW_INSTRUCTION			= 291;
const s32		_ICODE__FLDCW_INSTRUCTION			= 292;
const s32		_ICODE__FNSTCW_INSTRUCTION			= 293;
const s32		_ICODE__FLDENV_INSTRUCTION			= 294;
const s32		_ICODE__FNSTENV_INSTRUCTION			= 295;
const s32		_ICODE__FRSTOR_INSTRUCTION			= 296;
const s32		_ICODE__FNSAVE_INSTRUCTION			= 297;

const s32		_ICODE_CGC_TBYTE					= 1000;
const s32		_ICODE_CGC_DQWORD					= 1001;
const s32		_ICODE_CGC_QWORD					= 1002;
const s32		_ICODE_CGC_DWORD					= 1003;
const s32		_ICODE_CGC_WORD						= 1004;
const s32		_ICODE_CGC_BYTE						= 1005;
const s32		_ICODE_CGC_M16_16					= 1006;
const s32		_ICODE_CGC_M16_32					= 1007;
const s32		_ICODE_CGC_F32						= 1008;
const s32		_ICODE_CGC_F64						= 1009;
const s32		_ICODE_CGC_F80						= 1010;
const s32		_ICODE_CGC_S16						= 1011;
const s32		_ICODE_CGC_S32						= 1012;
const s32		_ICODE_CGC_S64						= 1013;
const s32		_ICODE_CGC_M80						= 1014;
const s32		_ICODE_CGC_MMX						= 1015;
const s32		_ICODE_CGC_XMMX						= 1016;
const s32		_ICODE_CGC_FPU						= 1017;
const s32		_ICODE_CGC_6BYTE					= 1018;
const s32		_ICODE_CGC_10BYTE					= 1019;
const s32		_ICODE_CGC_14BYTE					= 1020;
const s32		_ICODE_CGC_28BYTE					= 1021;
const s32		_ICODE_CGC_94BYTE					= 1022;
const s32		_ICODE_CGC_108BYTE					= 1023;
