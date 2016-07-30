//////////
//
// /libsf/exodus/tools/lsa/pass3.cpp
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
// Copyright (c) 2016 by Rick C. Hodgin
//////
// Last update:
//     Mar.14.2016
//////
// Change log:
//     Mar.14.2016 - Initial creation
//////
//
// This document and all documents contained within are released as Liberty Software
// under a Repeat License, as governed by the Public Benefit License v1.0 or later
// (PBL).
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
//////
//
// Liberty Software Foundation's lsa (LibSF Assembler).
//
//////




//////////
//
// Pass-3 -- Mnemonic parsing
//
//////
	struct SPass3Func
	{
		union {
			uptr	_func;
			bool	(*func)		(SLine* line);
		};
	};

	#define _LSA_PASS3_ICODE_BIT	23
	#define	iEncodeBranch(i)		(((u32)i << 24) + (1 << _LSA_PASS3_ICODE_BIT))
	#define	iCodeBranch(i)			(((u32)i & 0xff00000) >> 24)
	#define	iAddress(a)				(uptr)&ilsa_pass3_##a

	#define _LSA_PASS3_CODE_BRANCH_MIN 1
	cs32	_ICODE_LSA_AAA							= iEncodeBranch(1);
	cs32	_ICODE_LSA_AAD							= iEncodeBranch(2);
	cs32	_ICODE_LSA_AAD2							= iEncodeBranch(3);
	cs32	_ICODE_LSA_AAM							= iEncodeBranch(4);
	cs32	_ICODE_LSA_AAM2							= iEncodeBranch(5);
	cs32	_ICODE_LSA_AAS							= iEncodeBranch(6);
	cs32	_ICODE_LSA_ADC							= iEncodeBranch(7);
	cs32	_ICODE_LSA_ADD							= iEncodeBranch(8);
	cs32	_ICODE_LSA_AND							= iEncodeBranch(9);
	cs32	_ICODE_LSA_APRL							= iEncodeBranch(10);
	cs32	_ICODE_LSA_BOUND						= iEncodeBranch(11);
	cs32	_ICODE_LSA_BSF							= iEncodeBranch(12);
	cs32	_ICODE_LSA_BSR							= iEncodeBranch(13);
	cs32	_ICODE_LSA_BSWAP						= iEncodeBranch(14);
	cs32	_ICODE_LSA_BT							= iEncodeBranch(15);
	cs32	_ICODE_LSA_BTC							= iEncodeBranch(16);
	cs32	_ICODE_LSA_BTR							= iEncodeBranch(17);
	cs32	_ICODE_LSA_BTS							= iEncodeBranch(18);
	cs32	_ICODE_LSA_CALL							= iEncodeBranch(19);
	cs32	_ICODE_LSA_CBW							= iEncodeBranch(20);
	cs32	_ICODE_LSA_CWDE							= iEncodeBranch(21);
	cs32	_ICODE_LSA_CLC							= iEncodeBranch(22);
	cs32	_ICODE_LSA_CLD							= iEncodeBranch(23);
	cs32	_ICODE_LSA_CLI							= iEncodeBranch(24);
	cs32	_ICODE_LSA_CLTS							= iEncodeBranch(25);
	cs32	_ICODE_LSA_CMOVCC						= iEncodeBranch(26);
	cs32	_ICODE_LSA_CMP							= iEncodeBranch(27);
	cs32	_ICODE_LSA_CMPSB						= iEncodeBranch(28);
	cs32	_ICODE_LSA_CMPSW						= iEncodeBranch(29);
	cs32	_ICODE_LSA_CMPSD						= iEncodeBranch(30);
	cs32	_ICODE_LSA_CMPXCHG						= iEncodeBranch(31);
	cs32	_ICODE_LSA_CMPXCHG8B					= iEncodeBranch(32);
	cs32	_ICODE_LSA_CPUID						= iEncodeBranch(33);
	cs32	_ICODE_LSA_CDW							= iEncodeBranch(34);
	cs32	_ICODE_LSA_CDQ							= iEncodeBranch(35);
	cs32	_ICODE_LSA_DAA							= iEncodeBranch(36);
	cs32	_ICODE_LSA_DAS							= iEncodeBranch(37);
	cs32	_ICODE_LSA_DEC							= iEncodeBranch(38);
	cs32	_ICODE_LSA_DIV							= iEncodeBranch(39);
	cs32	_ICODE_LSA_EMMS							= iEncodeBranch(40);
	cs32	_ICODE_LSA_ENTER						= iEncodeBranch(41);
	cs32	_ICODE_LSA_F2XM1						= iEncodeBranch(42);
	cs32	_ICODE_LSA_FABS							= iEncodeBranch(43);
	cs32	_ICODE_LSA_FADD							= iEncodeBranch(44);
	cs32	_ICODE_LSA_FADDP						= iEncodeBranch(45);
	cs32	_ICODE_LSA_FIADD						= iEncodeBranch(46);
	cs32	_ICODE_LSA_FBLD							= iEncodeBranch(47);
	cs32	_ICODE_LSA_FBSTP						= iEncodeBranch(48);
	cs32	_ICODE_LSA_FCHS							= iEncodeBranch(49);
	cs32	_ICODE_LSA_FCLEX						= iEncodeBranch(50);
	cs32	_ICODE_LSA_FNCLEX						= iEncodeBranch(51);
	cs32	_ICODE_LSA_FCMOVB						= iEncodeBranch(52);
	cs32	_ICODE_LSA_FCMOVE						= iEncodeBranch(53);
	cs32	_ICODE_LSA_FCMOVBE						= iEncodeBranch(54);
	cs32	_ICODE_LSA_FCMOVU						= iEncodeBranch(55);
	cs32	_ICODE_LSA_FCMOVNB						= iEncodeBranch(56);
	cs32	_ICODE_LSA_FCMOVNE						= iEncodeBranch(57);
	cs32	_ICODE_LSA_FCMOVNBE						= iEncodeBranch(58);
	cs32	_ICODE_LSA_FCMOVNU						= iEncodeBranch(59);
	cs32	_ICODE_LSA_FCOM							= iEncodeBranch(60);
	cs32	_ICODE_LSA_FCOMP						= iEncodeBranch(61);
	cs32	_ICODE_LSA_FCOMPP						= iEncodeBranch(62);
	cs32	_ICODE_LSA_FCOMI						= iEncodeBranch(63);
	cs32	_ICODE_LSA_FCOMIP						= iEncodeBranch(64);
	cs32	_ICODE_LSA_FUCOMI						= iEncodeBranch(65);
	cs32	_ICODE_LSA_FUCOMIP						= iEncodeBranch(66);
	cs32	_ICODE_LSA_FCOS							= iEncodeBranch(67);
	cs32	_ICODE_LSA_FDECSTP						= iEncodeBranch(68);
	cs32	_ICODE_LSA_FDIV							= iEncodeBranch(69);
	cs32	_ICODE_LSA_FDIVP						= iEncodeBranch(70);
	cs32	_ICODE_LSA_FIDIV						= iEncodeBranch(71);
	cs32	_ICODE_LSA_FDIVR						= iEncodeBranch(72);
	cs32	_ICODE_LSA_FDIVRP						= iEncodeBranch(73);
	cs32	_ICODE_LSA_FIDIVR						= iEncodeBranch(74);
	cs32	_ICODE_LSA_FFREE						= iEncodeBranch(75);
	cs32	_ICODE_LSA_FICOM						= iEncodeBranch(76);
	cs32	_ICODE_LSA_FICOMP						= iEncodeBranch(77);
	cs32	_ICODE_LSA_FILD							= iEncodeBranch(78);
	cs32	_ICODE_LSA_FINCSTP						= iEncodeBranch(79);
	cs32	_ICODE_LSA_FINIT						= iEncodeBranch(80);
	cs32	_ICODE_LSA_FIST							= iEncodeBranch(81);
	cs32	_ICODE_LSA_FISTP						= iEncodeBranch(82);
	cs32	_ICODE_LSA_FLD							= iEncodeBranch(83);
	cs32	_ICODE_LSA_FLD1							= iEncodeBranch(84);
	cs32	_ICODE_LSA_FLD2T						= iEncodeBranch(85);
	cs32	_ICODE_LSA_FLD2E						= iEncodeBranch(86);
	cs32	_ICODE_LSA_FLDPI						= iEncodeBranch(87);
	cs32	_ICODE_LSA_FLDLG2						= iEncodeBranch(88);
	cs32	_ICODE_LSA_FLDN2						= iEncodeBranch(89);
	cs32	_ICODE_LSA_FLDZ							= iEncodeBranch(90);
	cs32	_ICODE_LSA_FLDCW						= iEncodeBranch(91);
	cs32	_ICODE_LSA_FLDENV						= iEncodeBranch(92);
	cs32	_ICODE_LSA_FMUL							= iEncodeBranch(93);
	cs32	_ICODE_LSA_FMULP						= iEncodeBranch(94);
	cs32	_ICODE_LSA_FIMUL						= iEncodeBranch(95);
	cs32	_ICODE_LSA_FNOP							= iEncodeBranch(96);
	cs32	_ICODE_LSA_FPATAN						= iEncodeBranch(97);
	cs32	_ICODE_LSA_FPREM						= iEncodeBranch(98);
	cs32	_ICODE_LSA_FPREM1						= iEncodeBranch(99);
	cs32	_ICODE_LSA_FPTAN						= iEncodeBranch(100);
	cs32	_ICODE_LSA_FRNDINT						= iEncodeBranch(101);
	cs32	_ICODE_LSA_FRSTOR						= iEncodeBranch(102);
	cs32	_ICODE_LSA_FSAVE						= iEncodeBranch(103);
	cs32	_ICODE_LSA_FSCALE						= iEncodeBranch(104);
	cs32	_ICODE_LSA_FSIN							= iEncodeBranch(105);
	cs32	_ICODE_LSA_FSINCOS						= iEncodeBranch(106);
	cs32	_ICODE_LSA_FSQRT						= iEncodeBranch(107);
	cs32	_ICODE_LSA_FST							= iEncodeBranch(108);
	cs32	_ICODE_LSA_FSTCW						= iEncodeBranch(109);
	cs32	_ICODE_LSA_FSTENV						= iEncodeBranch(110);
	cs32	_ICODE_LSA_FSTSW						= iEncodeBranch(111);
	cs32	_ICODE_LSA_FSUB							= iEncodeBranch(112);
	cs32	_ICODE_LSA_FSUBP						= iEncodeBranch(113);
	cs32	_ICODE_LSA_FISUB						= iEncodeBranch(114);
	cs32	_ICODE_LSA_FSUBR						= iEncodeBranch(115);
	cs32	_ICODE_LSA_FSUBRP						= iEncodeBranch(116);
	cs32	_ICODE_LSA_FISUBR						= iEncodeBranch(117);
	cs32	_ICODE_LSA_FTST							= iEncodeBranch(118);
	cs32	_ICODE_LSA_FUCOM						= iEncodeBranch(119);
	cs32	_ICODE_LSA_FUCOMP						= iEncodeBranch(120);
	cs32	_ICODE_LSA_FUCOMPP						= iEncodeBranch(121);
	cs32	_ICODE_LSA_FXAM							= iEncodeBranch(122);
	cs32	_ICODE_LSA_FXCH							= iEncodeBranch(123);
	cs32	_ICODE_LSA_FXTRACT						= iEncodeBranch(124);
	cs32	_ICODE_LSA_FYL2X						= iEncodeBranch(125);
	cs32	_ICODE_LSA_FYL2XP1						= iEncodeBranch(126);
	cs32	_ICODE_LSA_HLT							= iEncodeBranch(127);
	cs32	_ICODE_LSA_IDIV							= iEncodeBranch(128);
	cs32	_ICODE_LSA_IMUL							= iEncodeBranch(129);
	cs32	_ICODE_LSA_IN							= iEncodeBranch(130);
	cs32	_ICODE_LSA_INC							= iEncodeBranch(131);
	cs32	_ICODE_LSA_INS							= iEncodeBranch(132);
	cs32	_ICODE_LSA_INSB							= iEncodeBranch(133);
	cs32	_ICODE_LSA_INSW							= iEncodeBranch(134);
	cs32	_ICODE_LSA_INSD							= iEncodeBranch(135);
	cs32	_ICODE_LSA_INT3							= iEncodeBranch(136);
	cs32	_ICODE_LSA_INT							= iEncodeBranch(137);
	cs32	_ICODE_LSA_INTO							= iEncodeBranch(138);
	cs32	_ICODE_LSA_INVD							= iEncodeBranch(139);
	cs32	_ICODE_LSA_INVLPG						= iEncodeBranch(140);
	cs32	_ICODE_LSA_IRET							= iEncodeBranch(141);
	cs32	_ICODE_LSA_IRETD						= iEncodeBranch(142);
	cs32	_ICODE_LSA_JCC							= iEncodeBranch(143);
	cs32	_ICODE_LSA_JMP							= iEncodeBranch(144);
	cs32	_ICODE_LSA_LAHF							= iEncodeBranch(145);
	cs32	_ICODE_LSA_LAR							= iEncodeBranch(146);
	cs32	_ICODE_LSA_LDS							= iEncodeBranch(147);
	cs32	_ICODE_LSA_LSS							= iEncodeBranch(148);
	cs32	_ICODE_LSA_LES							= iEncodeBranch(149);
	cs32	_ICODE_LSA_LFS							= iEncodeBranch(150);
	cs32	_ICODE_LSA_LGS							= iEncodeBranch(151);
	cs32	_ICODE_LSA_LEA							= iEncodeBranch(152);
	cs32	_ICODE_LSA_LEAVE						= iEncodeBranch(153);
	cs32	_ICODE_LSA_LGDT							= iEncodeBranch(154);
	cs32	_ICODE_LSA_LIDT							= iEncodeBranch(155);
	cs32	_ICODE_LSA_LLDT							= iEncodeBranch(156);
	cs32	_ICODE_LSA_LMSW							= iEncodeBranch(157);
	cs32	_ICODE_LSA_LOCK							= iEncodeBranch(158);
	cs32	_ICODE_LSA_LODS							= iEncodeBranch(159);
	cs32	_ICODE_LSA_LODSB						= iEncodeBranch(160);
	cs32	_ICODE_LSA_LODSW						= iEncodeBranch(161);
	cs32	_ICODE_LSA_LODSD						= iEncodeBranch(162);
	cs32	_ICODE_LSA_LOOP							= iEncodeBranch(163);
	cs32	_ICODE_LSA_LOOPE						= iEncodeBranch(164);
	cs32	_ICODE_LSA_LOOPZ						= iEncodeBranch(165);
	cs32	_ICODE_LSA_LOOPNE						= iEncodeBranch(166);
	cs32	_ICODE_LSA_LOOPNZ						= iEncodeBranch(167);
	cs32	_ICODE_LSA_LSL							= iEncodeBranch(168);
	cs32	_ICODE_LSA_LTR							= iEncodeBranch(169);
	cs32	_ICODE_LSA_MOV							= iEncodeBranch(170);
	cs32	_ICODE_LSA_MOVS							= iEncodeBranch(171);
	cs32	_ICODE_LSA_MOVSB						= iEncodeBranch(172);
	cs32	_ICODE_LSA_MOVSW						= iEncodeBranch(173);
	cs32	_ICODE_LSA_MOVSD						= iEncodeBranch(174);
	cs32	_ICODE_LSA_MOVSX						= iEncodeBranch(175);
	cs32	_ICODE_LSA_MOVZX						= iEncodeBranch(176);
	cs32	_ICODE_LSA_MUL							= iEncodeBranch(177);
	cs32	_ICODE_LSA_NEG							= iEncodeBranch(178);
	cs32	_ICODE_LSA_NOP							= iEncodeBranch(179);
	cs32	_ICODE_LSA_NOT							= iEncodeBranch(180);
	cs32	_ICODE_LSA_OR							= iEncodeBranch(181);
	cs32	_ICODE_LSA_OUT							= iEncodeBranch(182);
	cs32	_ICODE_LSA_OUTS							= iEncodeBranch(183);
	cs32	_ICODE_LSA_OUTSB						= iEncodeBranch(184);
	cs32	_ICODE_LSA_OUTSW						= iEncodeBranch(185);
	cs32	_ICODE_LSA_OUTSD						= iEncodeBranch(186);
	cs32	_ICODE_LSA_POP							= iEncodeBranch(187);
	cs32	_ICODE_LSA_POPA							= iEncodeBranch(188);
	cs32	_ICODE_LSA_POPAD						= iEncodeBranch(189);
	cs32	_ICODE_LSA_POPF							= iEncodeBranch(190);
	cs32	_ICODE_LSA_POPFD						= iEncodeBranch(191);
	cs32	_ICODE_LSA_PREFETCH0					= iEncodeBranch(192);
	cs32	_ICODE_LSA_PREFETCH1					= iEncodeBranch(193);
	cs32	_ICODE_LSA_PREFETCH2					= iEncodeBranch(194);
	cs32	_ICODE_LSA_PREFETCHNTA					= iEncodeBranch(195);
	cs32	_ICODE_LSA_PUSH							= iEncodeBranch(196);
	cs32	_ICODE_LSA_PUSHA						= iEncodeBranch(197);
	cs32	_ICODE_LSA_PUSHAD						= iEncodeBranch(198);
	cs32	_ICODE_LSA_PUSHF						= iEncodeBranch(199);
	cs32	_ICODE_LSA_PUSHFD						= iEncodeBranch(200);
	cs32	_ICODE_LSA_RCL							= iEncodeBranch(201);
	cs32	_ICODE_LSA_RCR							= iEncodeBranch(202);
	cs32	_ICODE_LSA_REPNE						= iEncodeBranch(203);
	cs32	_ICODE_LSA_REPNZ						= iEncodeBranch(204);
	cs32	_ICODE_LSA_REPE							= iEncodeBranch(205);
	cs32	_ICODE_LSA_REPZ							= iEncodeBranch(206);
	cs32	_ICODE_LSA_ROL							= iEncodeBranch(207);
	cs32	_ICODE_LSA_ROR							= iEncodeBranch(208);
	cs32	_ICODE_LSA_RDMSR						= iEncodeBranch(209);
	cs32	_ICODE_LSA_RDPMC						= iEncodeBranch(210);
	cs32	_ICODE_LSA_RDTSC						= iEncodeBranch(211);
	cs32	_ICODE_LSA_RET							= iEncodeBranch(212);
	cs32	_ICODE_LSA_SAHF							= iEncodeBranch(213);
	cs32	_ICODE_LSA_SAR							= iEncodeBranch(214);
	cs32	_ICODE_LSA_SHL							= iEncodeBranch(215);
	cs32	_ICODE_LSA_SHR							= iEncodeBranch(216);
	cs32	_ICODE_LSA_SBB							= iEncodeBranch(217);
	cs32	_ICODE_LSA_SCAS							= iEncodeBranch(218);
	cs32	_ICODE_LSA_SCASB						= iEncodeBranch(219);
	cs32	_ICODE_LSA_SCASW						= iEncodeBranch(220);
	cs32	_ICODE_LSA_SCASD						= iEncodeBranch(221);
	cs32	_ICODE_LSA_SETCC						= iEncodeBranch(222);
	cs32	_ICODE_LSA_SGDT							= iEncodeBranch(223);
	cs32	_ICODE_LSA_SIDT							= iEncodeBranch(224);
	cs32	_ICODE_LSA_SLDT							= iEncodeBranch(225);
	cs32	_ICODE_LSA_SHLD							= iEncodeBranch(226);
	cs32	_ICODE_LSA_SHRD							= iEncodeBranch(227);
	cs32	_ICODE_LSA_SMSW							= iEncodeBranch(228);
	cs32	_ICODE_LSA_STC							= iEncodeBranch(229);
	cs32	_ICODE_LSA_STD							= iEncodeBranch(230);
	cs32	_ICODE_LSA_STI							= iEncodeBranch(231);
	cs32	_ICODE_LSA_STOS							= iEncodeBranch(232);
	cs32	_ICODE_LSA_STOSB						= iEncodeBranch(233);
	cs32	_ICODE_LSA_STOSW						= iEncodeBranch(234);
	cs32	_ICODE_LSA_STOSD						= iEncodeBranch(235);
	cs32	_ICODE_LSA_STR							= iEncodeBranch(236);
	cs32	_ICODE_LSA_SUB							= iEncodeBranch(237);
	cs32	_ICODE_LSA_SYSENTER						= iEncodeBranch(238);
	cs32	_ICODE_LSA_SYSEXIT						= iEncodeBranch(239);
	cs32	_ICODE_LSA_TEST							= iEncodeBranch(240);
	cs32	_ICODE_LSA_UD2							= iEncodeBranch(241);
	cs32	_ICODE_LSA_VERR							= iEncodeBranch(242);
	cs32	_ICODE_LSA_VERW							= iEncodeBranch(243);
	cs32	_ICODE_LSA_FWAIT						= iEncodeBranch(244);
	cs32	_ICODE_LSA_WBINVD						= iEncodeBranch(245);
	cs32	_ICODE_LSA_WRMSR						= iEncodeBranch(246);
	cs32	_ICODE_LSA_XADD							= iEncodeBranch(247);
	cs32	_ICODE_LSA_XCHG							= iEncodeBranch(248);
	cs32	_ICODE_LSA_XLAT							= iEncodeBranch(249);
	cs32	_ICODE_LSA_XLATB						= iEncodeBranch(250);
	cs32	_ICODE_LSA_XOR							= iEncodeBranch(251);
	#define _LSA_PASS3_CODE_BRANCH_MAX 251

	SPass3Func gsPass3_functions[_LSA_PASS3_CODE_BRANCH_MAX];


	// AAA -- ASCII adjust al after addition
	bool ilsa_pass3_aaa(SLine* line)
	{
		return(false);
	}

	// AAD -- ASCII adjust ax before division
	bool ilsa_pass3_aad(SLine* line)
	{
		return(false);
	}

	// AAD2 -- ASCII adjust ax before division to base imm8
	bool ilsa_pass3_aad2(SLine* line)
	{
		return(false);
	}

	// AAM -- ASCII adjust ax after multiply
	bool ilsa_pass3_aam(SLine* line)
	{
		return(false);
	}

	// AAM2 -- ASCII adjust ax after multiply to base imm8
	bool ilsa_pass3_aam2(SLine* line)
	{
		return(false);
	}

	// AAS -- ASCII adjust al after subtraction
	bool ilsa_pass3_aas(SLine* line)
	{
		return(false);
	}

	// ADC -- Add with carry r/m32 to r32
	bool ilsa_pass3_adc(SLine* line)
	{
		return(false);
	}

	// ADD al,imm8 -- Add imm8 to al
	bool ilsa_pass3_add(SLine* line)
	{
		return(false);
	}

	// AND al,imm8 -- imm8  al
	bool ilsa_pass3_and(SLine* line)
	{
		return(false);
	}

	// APRL r/m16,r16 -- Adjust RPL of r/m16 to not less than RPL of r16
	bool ilsa_pass3_aprl(SLine* line)
	{
		return(false);
	}

	// BOUND r16,m16&16 -- Check if r16 (array index) is within bounds specified by m16&16
	bool ilsa_pass3_bound(SLine* line)
	{
		return(false);
	}

	// BSF r16,r/m16 -- Bit scan forward on r/m16
	bool ilsa_pass3_bsf(SLine* line)
	{
		return(false);
	}

	// BSR r16,r/m16 -- Bit scan reverse on r/m16
	bool ilsa_pass3_bsr(SLine* line)
	{
		return(false);
	}

	// BSWAP r32 -- Swap endian on 32-bit register
	bool ilsa_pass3_bswap(SLine* line)
	{
		return(false);
	}

	// BT r/m32,imm8 -- Store selected bit in carry
	bool ilsa_pass3_bt(SLine* line)
	{
		return(false);
	}

	// BTC r/m16,r16 -- Store selected bit in carry, and complement
	bool ilsa_pass3_btc(SLine* line)
	{
		return(false);
	}

	// BTR r/m32,imm8 -- Store selected bit in carry, and clear
	bool ilsa_pass3_btr(SLine* line)
	{
		return(false);
	}

	// BTS r/m32,imm8 -- Store selected bit in carry, and set
	bool ilsa_pass3_bts(SLine* line)
	{
		return(false);
	}

	// CALL m16:32 -- Call far, absolute indirect address in m16:32
	bool ilsa_pass3_call(SLine* line)
	{
		return(false);
	}

	// CBW -- Sign-extend al to ax
	bool ilsa_pass3_cbw(SLine* line)
	{
		return(false);
	}

	// CWDE -- Sign-extend ax to eax
	bool ilsa_pass3_cwde(SLine* line)
	{
		return(false);
	}

	// CLC -- Clear carry
	bool ilsa_pass3_clc(SLine* line)
	{
		return(false);
	}

	// CLD -- Clear direction
	bool ilsa_pass3_cld(SLine* line)
	{
		return(false);
	}

	// CLI -- Clear interrupt
	bool ilsa_pass3_cli(SLine* line)
	{
		return(false);
	}

	// CLTS -- Clear task-switched flag in CR0
	bool ilsa_pass3_clts(SLine* line)
	{
		return(false);
	}

	// CMOVcc r32,rm32 -- Move if cc flag condition is true
	bool ilsa_pass3_cmovcc(SLine* line)
	{
		return(false);
	}

	// CMP al,imm8 -- imm8  al
	bool ilsa_pass3_cmp(SLine* line)
	{
		return(false);
	}

	// CMPSB -- Compare byte in ds:[esi] to es:[edi]
	bool ilsa_pass3_cmpsb(SLine* line)
	{
		return(false);
	}

	// CMPSW -- Compare word in ds:[esi] to es:[edi]
	bool ilsa_pass3_cmpsw(SLine* line)
	{
		return(false);
	}

	// CMPSD -- Compare dword in ds:[esi] to es:[edi]
	bool ilsa_pass3_cmpsd(SLine* line)
	{
		return(false);
	}

	// CMPXCHG r/m32,r32 -- Compare eax with r/m16, if equal set zero and load r32 into r/m32, if not equal clear zero and load r/m32 into eax
	bool ilsa_pass3_cmpxchg(SLine* line)
	{
		return(false);
	}

	// CMPXCHG8B m64 -- Compare edx:eax with m64, if equal set zero and load ECX:EBX into m64, if not equal clear zero and load m64 into edx:eax
	bool ilsa_pass3_cmpxchg8b(SLine* line)
	{
		return(false);
	}

	// CPUID -- Based on EAX, load processor information into registers
	bool ilsa_pass3_cpuid(SLine* line)
	{
		return(false);
	}

	// CDW -- Sign-extend ax into dx:ax
	bool ilsa_pass3_cdw(SLine* line)
	{
		return(false);
	}

	// CDQ -- Sign-extend eax into edx:eax
	bool ilsa_pass3_cdq(SLine* line)
	{
		return(false);
	}

	// DAA -- Decimal adjust al after addition
	bool ilsa_pass3_daa(SLine* line)
	{
		return(false);
	}

	// DAS -- Decimal adjust al after subtraction
	bool ilsa_pass3_das(SLine* line)
	{
		return(false);
	}

	// DEC r32 -- Decrement r32 by 1
	bool ilsa_pass3_dec(SLine* line)
	{
		return(false);
	}

	// DIV r/m32 -- Unsigned divide edx:eax by r/m32, quotient in eax, remainder in edx
	bool ilsa_pass3_div(SLine* line)
	{
		return(false);
	}

	// EMMS -- Empty the MMX state
	bool ilsa_pass3_emms(SLine* line)
	{
		return(false);
	}

	// ENTER imm16,imm8 -- Create a stack frame, or nested stack frame
	bool ilsa_pass3_enter(SLine* line)
	{
		return(false);
	}

	// F2XM1 -- st0 = 2^(st0 - 1) into st0
	bool ilsa_pass3_f2xm1(SLine* line)
	{
		return(false);
	}

	// FABS -- st0 = fabs(st0)
	bool ilsa_pass3_fabs(SLine* line)
	{
		return(false);
	}

	// FADD f32 -- st0 = st0 + f32
	bool ilsa_pass3_fadd(SLine* line)
	{
		return(false);
	}

	// FADDP stN,st0 -- stN = stN + st0, then pop
	bool ilsa_pass3_faddp(SLine* line)
	{
		return(false);
	}

	// FIADD s32 -- st0 = st0 + s32
	bool ilsa_pass3_fiadd(SLine* line)
	{
		return(false);
	}

	// FBLD m80 -- push m80 loaded as binary coded decimal into st0
	bool ilsa_pass3_fbld(SLine* line)
	{
		return(false);
	}

	// FBSTP m80 -- Store st0 as binary coded decimal into m80, then pop
	bool ilsa_pass3_fbstp(SLine* line)
	{
		return(false);
	}

	// FCHS -- Complement st0's sign
	bool ilsa_pass3_fchs(SLine* line)
	{
		return(false);
	}

	// FCLEX -- Clear floating point exceptions after checking for pending unmasked exceptions
	bool ilsa_pass3_fclex(SLine* line)
	{
		return(false);
	}

	// FNCLEX -- No-wait version of FCLEX
	bool ilsa_pass3_fnclex(SLine* line)
	{
		return(false);
	}

	// FCMOVB st0,stN -- Move if carry
	bool ilsa_pass3_fcmovb(SLine* line)
	{
		return(false);
	}

	// FCMOVE st0,stN -- Move if zero
	bool ilsa_pass3_fcmove(SLine* line)
	{
		return(false);
	}

	// FCMOVBE st0,stN -- Move if carry or zero
	bool ilsa_pass3_fcmovbe(SLine* line)
	{
		return(false);
	}

	// FCMOVU st0,stN -- Move if parity
	bool ilsa_pass3_fcmovu(SLine* line)
	{
		return(false);
	}

	// FCMOVNB st0,stN -- Move if not carry
	bool ilsa_pass3_fcmovnb(SLine* line)
	{
		return(false);
	}

	// FCMOVNE st0,stN -- Move if not zero
	bool ilsa_pass3_fcmovne(SLine* line)
	{
		return(false);
	}

	// FCMOVNBE st0,stN -- Move if not carry and not zero
	bool ilsa_pass3_fcmovnbe(SLine* line)
	{
		return(false);
	}

	// FCMOVNU st0,stN -- Move if not parity
	bool ilsa_pass3_fcmovnu(SLine* line)
	{
		return(false);
	}

	// FCOM f32 -- Compare st0 with f32
	bool ilsa_pass3_fcom(SLine* line)
	{
		return(false);
	}

	// FCOMP stN -- Compare st0 with stN, then pop
	bool ilsa_pass3_fcomp(SLine* line)
	{
		return(false);
	}

	// FCOMPP -- Compare st0 with st1, then pop, then pop again
	bool ilsa_pass3_fcompp(SLine* line)
	{
		return(false);
	}

	// FCOMI stN -- Compare st0 with stN, and set eflags
	bool ilsa_pass3_fcomi(SLine* line)
	{
		return(false);
	}

	// FCOMIP stN -- Compare st0 with stN, and set eflags, then pop
	bool ilsa_pass3_fcomip(SLine* line)
	{
		return(false);
	}

	// FUCOMI stN -- Compare st0 with stN, check for ordered values, and set eflags
	bool ilsa_pass3_fucomi(SLine* line)
	{
		return(false);
	}

	// FUCOMIP stN -- Compare st0 with stN, check for ordered values, and set eflags, then pop
	bool ilsa_pass3_fucomip(SLine* line)
	{
		return(false);
	}

	// FCOS -- st0 = cos(st0)
	bool ilsa_pass3_fcos(SLine* line)
	{
		return(false);
	}

	// FDECSTP -- Decrement the TOP field in the FPU status word
	bool ilsa_pass3_fdecstp(SLine* line)
	{
		return(false);
	}

	// FDIV f32 -- st0 = st0 / f32
	bool ilsa_pass3_fdiv(SLine* line)
	{
		return(false);
	}

	// FDIVP stN,st0 -- stN = stN / st0, then pop
	bool ilsa_pass3_fdivp(SLine* line)
	{
		return(false);
	}

	// FIDIV s32 -- st0 = st0 / s32
	bool ilsa_pass3_fidiv(SLine* line)
	{
		return(false);
	}

	// FDIVR f64 -- st0 = f64 / st0
	bool ilsa_pass3_fdivr(SLine* line)
	{
		return(false);
	}

	// FDIVRP stN,st0 -- stN = st0 / stN, then pop
	bool ilsa_pass3_fdivrp(SLine* line)
	{
		return(false);
	}

	// FIDIVR s32 -- st0 = s32 / st0
	bool ilsa_pass3_fidivr(SLine* line)
	{
		return(false);
	}

	// FFREE stN -- Set the tag for stN to empty
	bool ilsa_pass3_ffree(SLine* line)
	{
		return(false);
	}

	// FICOM s32 -- Compare st0 to s32
	bool ilsa_pass3_ficom(SLine* line)
	{
		return(false);
	}

	// FICOMP s32 -- Compare st0 to s32, then pop
	bool ilsa_pass3_ficomp(SLine* line)
	{
		return(false);
	}

	// FILD s16 -- Push s16 into st0
	bool ilsa_pass3_fild(SLine* line)
	{
		return(false);
	}

	// FINCSTP -- Increment the TOP field in the FPU status word
	bool ilsa_pass3_fincstp(SLine* line)
	{
		return(false);
	}

	// FINIT -- Initialize the FPU
	bool ilsa_pass3_finit(SLine* line)
	{
		return(false);
	}

	// FIST m32int -- Store st0 to memory as s32
	bool ilsa_pass3_fist(SLine* line)
	{
		return(false);
	}

	// FISTP m64int -- Store st0 to memory as s64, then pop
	bool ilsa_pass3_fistp(SLine* line)
	{
		return(false);
	}

	// FLD stN -- Push stN into st0
	bool ilsa_pass3_fld(SLine* line)
	{
		return(false);
	}

	// FLD1 -- Push +1.0 into st0
	bool ilsa_pass3_fld1(SLine* line)
	{
		return(false);
	}

	// FLDL2T -- Push log2(10) into st0
	bool ilsa_pass3_fld2t(SLine* line)
	{
		return(false);
	}

	// FLDL2E -- Push log2(e) into st0
	bool ilsa_pass3_fldl2e(SLine* line)
	{
		return(false);
	}

	// FLDPI -- Push pi into st0
	bool ilsa_pass3_fldpi(SLine* line)
	{
		return(false);
	}

	// FLDLG2 -- Push log10(2) into st0
	bool ilsa_pass3_fldlg2(SLine* line)
	{
		return(false);
	}

	// FLDLN2 -- Push loge(2) into st0
	bool ilsa_pass3_fldn2(SLine* line)
	{
		return(false);
	}

	// FLDZ -- Push +0.0 into st0
	bool ilsa_pass3_fldz(SLine* line)
	{
		return(false);
	}

	// FLDCW u16 -- Load u16 into FPU control word
	bool ilsa_pass3_fldcw(SLine* line)
	{
		return(false);
	}

	// FLDENV m14/m28 -- Load 14-byte or 28-byte into environment
	bool ilsa_pass3_fldenv(SLine* line)
	{
		return(false);
	}

	// FMUL stN,st0 -- stN = stN * st0
	bool ilsa_pass3_fmul(SLine* line)
	{
		return(false);
	}

	// FMULP stN,st0 -- stN = stN * st0, then pop
	bool ilsa_pass3_fmulp(SLine* line)
	{
		return(false);
	}

	// FIMUL m32int -- st0 = st0 * s32
	bool ilsa_pass3_fimul(SLine* line)
	{
		return(false);
	}

	// FNOP -- No operation
	bool ilsa_pass3_fnop(SLine* line)
	{
		return(false);
	}

	// FPATAN -- st1 = arctan(st1 / st0), then pop
	bool ilsa_pass3_fpatan(SLine* line)
	{
		return(false);
	}

	// FPREM -- st0 = st0 % st1
	bool ilsa_pass3_fprem(SLine* line)
	{
		return(false);
	}

	// FPREM1 -- st0 = IEEE st0 % st1
	bool ilsa_pass3_fprem1(SLine* line)
	{
		return(false);
	}

	// FPTAN -- st0 = tan(st0), then push 1 into st0
	bool ilsa_pass3_fptan(SLine* line)
	{
		return(false);
	}

	// FRNDINT -- st0 = int(st0)
	bool ilsa_pass3_frndint(SLine* line)
	{
		return(false);
	}

	// FRSTOR m94/m108 -- Load FPU state from a 94 or 108 byte block
	bool ilsa_pass3_frstor(SLine* line)
	{
		return(false);
	}

	// FSAVE m94/m108 -- Store the FPU state to a 94 or 108 byte block
	bool ilsa_pass3_fsave(SLine* line)
	{
		return(false);
	}

	// FSCALE -- st0 = 2^stN
	bool ilsa_pass3_fscale(SLine* line)
	{
		return(false);
	}

	// FSIN -- st0 = sin(st0)
	bool ilsa_pass3_fsin(SLine* line)
	{
		return(false);
	}

	// FSINCOS -- t = cos(st0), st0 = sin(st0), then push t into st0
	bool ilsa_pass3_fsincos(SLine* line)
	{
		return(false);
	}

	// FSQRT -- st0 = sqrt(st0)
	bool ilsa_pass3_fsqrt(SLine* line)
	{
		return(false);
	}

	// FST stN -- Copy st0 to stN, then pop
	bool ilsa_pass3_fst(SLine* line)
	{
		return(false);
	}

	// FSTCW m16 -- Copy FPU status word to m16
	bool ilsa_pass3_fstcw(SLine* line)
	{
		return(false);
	}

	// FSTENV m14/m28 -- Copy FPU environment to 14-byte or 28-byte block
	bool ilsa_pass3_fstenv(SLine* line)
	{
		return(false);
	}

	// FSTSW ax -- Copy FPU status word to ax
	bool ilsa_pass3_fstsw(SLine* line)
	{
		return(false);
	}

	// FSUB stN,st0 -- stN = stN - st0
	bool ilsa_pass3_fsub(SLine* line)
	{
		return(false);
	}

	// FSUBP stN,st0 -- stN = stN - st0, then pop
	bool ilsa_pass3_fsubp(SLine* line)
	{
		return(false);
	}

	// FISUB s16 -- st0 = st0 - s16
	bool ilsa_pass3_fisub(SLine* line)
	{
		return(false);
	}

	// FSUBR stN,st0 -- stN = st0 - stN
	bool ilsa_pass3_fsubr(SLine* line)
	{
		return(false);
	}

	// FSUBRP stN,st0 -- stN = st0 - stN, then pop
	bool ilsa_pass3_fsubrp(SLine* line)
	{
		return(false);
	}

	// FISUBR s16 -- st0 = s16 - st0
	bool ilsa_pass3_fisubr(SLine* line)
	{
		return(false);
	}

	// FTST -- Compare st0 to +0.0
	bool ilsa_pass3_ftst(SLine* line)
	{
		return(false);
	}

	// FUCOM stN -- Compare st0 to stN
	bool ilsa_pass3_fucom(SLine* line)
	{
		return(false);
	}

	// FUCOMP stN -- Compare st0 to stN, then pop
	bool ilsa_pass3_fucomp(SLine* line)
	{
		return(false);
	}

	// FUCOMPP -- Compare st0 to st1, then pop
	bool ilsa_pass3_fucompp(SLine* line)
	{
		return(false);
	}

	// FXAM -- Classify st0
	bool ilsa_pass3_fxam(SLine* line)
	{
		return(false);
	}

	// FXCH stN -- Exchange st0 and stN
	bool ilsa_pass3_fxch(SLine* line)
	{
		return(false);
	}

	// FXTRACT -- t = st0's exponent, st0 = st0's significand, then push t into st0
	bool ilsa_pass3_fxtract(SLine* line)
	{
		return(false);
	}

	// FYL2X -- st1 = st1 * log2(st0), then pop
	bool ilsa_pass3_fyl2x(SLine* line)
	{
		return(false);
	}

	// FYL2XP1 -- st1 = st1 * log2(st0 + 1.0), then pop
	bool ilsa_pass3_fyl2xp1(SLine* line)
	{
		return(false);
	}

	// HLT -- Halt until interrupt
	bool ilsa_pass3_hlt(SLine* line)
	{
		return(false);
	}

	// IDIV r/m32 -- Integer divide edx:eax, eax=quotient, edx=remainder
	bool ilsa_pass3_idiv(SLine* line)
	{
		return(false);
	}

	// IMUL r32,r/m32,imm32 -- r32 = r32 * r/m32 * imm32
	bool ilsa_pass3_imul(SLine* line)
	{
		return(false);
	}

	// IN eax,dx -- Read dword from I/o port in dx
	bool ilsa_pass3_in(SLine* line)
	{
		return(false);
	}

	// INC r32 -- Increment r32 by 1
	bool ilsa_pass3_inc(SLine* line)
	{
		return(false);
	}

	// INS m32,dx -- Input a dword from I/O port in dx, store to es:[e/di]
	bool ilsa_pass3_ins(SLine* line)
	{
		return(false);
	}

	// INSB -- Shorthand for INS m8,dx
	bool ilsa_pass3_insb(SLine* line)
	{
		return(false);
	}

	// INSW -- Shorthand for INS m16,dx
	bool ilsa_pass3_insw(SLine* line)
	{
		return(false);
	}

	// INSD -- Shorthand for INS m32,dx
	bool ilsa_pass3_insd(SLine* line)
	{
		return(false);
	}

	// INT3 -- Trap to debugger, one byte
	bool ilsa_pass3_int3(SLine* line)
	{
		return(false);
	}

	// INT imm8 -- Interrupt vector imm8
	bool ilsa_pass3_int(SLine* line)
	{
		return(false);
	}

	// INTO -- Interrupt on overflow
	bool ilsa_pass3_into(SLine* line)
	{
		return(false);
	}

	// INVD -- Invalidate internal caches
	bool ilsa_pass3_invd(SLine* line)
	{
		return(false);
	}

	// INVLPG m -- Invalidate TLB entry for page that contains m
	bool ilsa_pass3_invlpg(SLine* line)
	{
		return(false);
	}

	// IRET -- Interrupt return 16-bit
	bool ilsa_pass3_iret(SLine* line)
	{
		return(false);
	}

	// IRETD -- Interrupt return 32-bit
	bool ilsa_pass3_iretd(SLine* line)
	{
		return(false);
	}

	// Jcc imm32 -- Conditional jump relative by imm32 offset
	bool ilsa_pass3_jcc(SLine* line)
	{
		return(false);
	}

	// JMP m16:32 -- Jump far, absolute indirect, address in m16:32
	bool ilsa_pass3_jmp(SLine* line)
	{
		return(false);
	}

	// LAHF -- ah = eflags.sf:zf:0:af:0:pf:1:cf
	bool ilsa_pass3_lahf(SLine* line)
	{
		return(false);
	}

	// LAR r32,r/m32 -- r32 = r/m32 & 00fxff00h
	bool ilsa_pass3_lar(SLine* line)
	{
		return(false);
	}

	// LDS r32,m16:32 -- Load DS:r32 indirect from far pointer
	bool ilsa_pass3_lds(SLine* line)
	{
		return(false);
	}

	// LSS r32,m16:32 -- Load SS:r32 indirect from far pointer
	bool ilsa_pass3_lss(SLine* line)
	{
		return(false);
	}

	// LES r32,m16:32 -- Load ES:r32 indirect from far pointer
	bool ilsa_pass3_les(SLine* line)
	{
		return(false);
	}

	// LFS r32,m16:32 -- Load FS:r32 indirect from far pointer
	bool ilsa_pass3_lfs(SLine* line)
	{
		return(false);
	}

	// LGS r32,m16:32 -- Load GS:r32 indirect from far pointer
	bool ilsa_pass3_lgs(SLine* line)
	{
		return(false);
	}

	// LEA r32,m -- Store effective address for m in r32
	bool ilsa_pass3_lea(SLine* line)
	{
		return(false);
	}

	// LEAVE -- esp = ebp, then pop ebp
	bool ilsa_pass3_leave(SLine* line)
	{
		return(false);
	}

	// LGDT m16&32 -- Load m into GDTR
	bool ilsa_pass3_lgdt(SLine* line)
	{
		return(false);
	}

	// LIDT m16&32 -- Load m into IDTR
	bool ilsa_pass3_lidt(SLine* line)
	{
		return(false);
	}

	// LLDT r/m16 -- Load selector into LDTR
	bool ilsa_pass3_lldt(SLine* line)
	{
		return(false);
	}

	// LMSW r/m16 -- Loads r/m16 into bits cr0
	bool ilsa_pass3_lmsw(SLine* line)
	{
		return(false);
	}

	// LOCK -- Prefix for other instructions, locks system bus
	bool ilsa_pass3_lock(SLine* line)
	{
		return(false);
	}

	// LODS m32 -- Load dword from ds:[e/si] into eax
	bool ilsa_pass3_lods(SLine* line)
	{
		return(false);
	}

	// LODSB -- Shorthand for LODS m8
	bool ilsa_pass3_lodsb(SLine* line)
	{
		return(false);
	}

	// LODSW -- Shorthand for LODS m16
	bool ilsa_pass3_lodsw(SLine* line)
	{
		return(false);
	}

	// LODSD -- Shorthand for LODS m32
	bool ilsa_pass3_lodsd(SLine* line)
	{
		return(false);
	}

	// LOOP imm8 -- Decrement count, jump short if count != 0
	bool ilsa_pass3_loop(SLine* line)
	{
		return(false);
	}

	// LOOPE imm8 -- Decrement count, jump short if count != 0 and zero
	bool ilsa_pass3_loope(SLine* line)
	{
		return(false);
	}

	// LOOPZ imm8 -- Synonym for LOOPE
	bool ilsa_pass3_loopz(SLine* line)
	{
		return(false);
	}

	// LOOPNE imm8 -- Decrement count, jump short if count != 0 and !zero
	bool ilsa_pass3_loopne(SLine* line)
	{
		return(false);
	}

	// LOOPNZ imm8 -- Synonym for LOOPNE
	bool ilsa_pass3_loopnz(SLine* line)
	{
		return(false);
	}

	// LSL r32,r/m32 -- r32 = segment_limit(r/m32)
	bool ilsa_pass3_lsl(SLine* line)
	{
		return(false);
	}

	// LTR r/m16 -- Load r/m16 into TR
	bool ilsa_pass3_ltr(SLine* line)
	{
		return(false);
	}

	// MOV mm/m64,mmN -- Move mmN to mmN/m64
	bool ilsa_pass3_mov(SLine* line)
	{
		return(false);
	}

	// MOVS m32,m32 -- Move dword from ds:[e/si] to es:[e/di]
	bool ilsa_pass3_movs(SLine* line)
	{
		return(false);
	}

	// MOVSB -- Shorthand for MOVS m8,m8
	bool ilsa_pass3_movsb(SLine* line)
	{
		return(false);
	}

	// MOVSW -- Shorthand for MOVS m16,m16
	bool ilsa_pass3_movsw(SLine* line)
	{
		return(false);
	}

	// MOVSD -- Shorthand for MOVS m32,m32
	bool ilsa_pass3_movsd(SLine* line)
	{
		return(false);
	}

	// MOVSX r32,r/m16 -- Sign-extend word to dword
	bool ilsa_pass3_movsx(SLine* line)
	{
		return(false);
	}

	// MOVZX r32,r/m16 -- Zero-extend word to dword
	bool ilsa_pass3_movzx(SLine* line)
	{
		return(false);
	}

	// MUL r/m32 -- edx:eax = eax * r/m32
	bool ilsa_pass3_mul(SLine* line)
	{
		return(false);
	}

	// NEG r/m32 -- Two's complement r/m32
	bool ilsa_pass3_neg(SLine* line)
	{
		return(false);
	}

	// NOP -- No operation
	bool ilsa_pass3_nop(SLine* line)
	{
		return(false);
	}

	// NOT r/m32 -- Logical NOT of r/m32
	bool ilsa_pass3_not(SLine* line)
	{
		return(false);
	}

	// OR r32,r/m32 -- r/m32 to r32
	bool ilsa_pass3_or(SLine* line)
	{
		return(false);
	}

	// OUT dx,eax -- Output eax to I/O port dx
	bool ilsa_pass3_out(SLine* line)
	{
		return(false);
	}

	// OUTS dx,m32 -- Output dword at ds:[e/si] to I/O port dx
	bool ilsa_pass3_outs(SLine* line)
	{
		return(false);
	}

	// OUTSB -- Shorthand for OUTS dx,m8
	bool ilsa_pass3_outsb(SLine* line)
	{
		return(false);
	}

	// OUTSW -- Shorthand for OUTS dx,m16
	bool ilsa_pass3_outsw(SLine* line)
	{
		return(false);
	}

	// OUTSD -- Shorthand for OUTS dx,m32
	bool ilsa_pass3_outsd(SLine* line)
	{
		return(false);
	}

	// POP GS -- Pop stack into GS
	bool ilsa_pass3_pop(SLine* line)
	{
		return(false);
	}

	// POPA -- Pop all r16 registers
	bool ilsa_pass3_popa(SLine* line)
	{
		return(false);
	}

	// POPAD -- Pop all r32 registers
	bool ilsa_pass3_popad(SLine* line)
	{
		return(false);
	}

	// POPF -- Pop 16-bit flags
	bool ilsa_pass3_popf(SLine* line)
	{
		return(false);
	}

	// POPFD -- Pop 32-bit eflags
	bool ilsa_pass3_popfd(SLine* line)
	{
		return(false);
	}

	// PREFETCHT0 m8 -- Prefetch block around m8 into all caches
	bool ilsa_pass3_prefetch0(SLine* line)
	{
		return(false);
	}

	// PREFETCHT1 m8 -- Prefetch block around m8 into l1 and above
	bool ilsa_pass3_prefetch1(SLine* line)
	{
		return(false);
	}

	// PREFETCHT2 m8 -- Prefetch block around m8 into l2 and above
	bool ilsa_pass3_prefetch2(SLine* line)
	{
		return(false);
	}

	// PREFETCHNTA m8 -- Prefetch block around m8 into non-temporal caches
	bool ilsa_pass3_prefetchnta(SLine* line)
	{
		return(false);
	}

	// PUSH gs -- Push GS
	bool ilsa_pass3_push(SLine* line)
	{
		return(false);
	}

	// PUSHA -- Push all 16-bit registers
	bool ilsa_pass3_pusha(SLine* line)
	{
		return(false);
	}

	// PUSHAD -- Push all 32-bit registers
	bool ilsa_pass3_pushad(SLine* line)
	{
		return(false);
	}

	// PUSHF -- Push 16-bit flags
	bool ilsa_pass3_pushf(SLine* line)
	{
		return(false);
	}

	// PUSHFD -- Push 32-bit eflags
	bool ilsa_pass3_pushfd(SLine* line)
	{
		return(false);
	}

	// RCL r/m32,imm8 -- Rotate r/m32 through carry by imm8 bits left
	bool ilsa_pass3_rcl(SLine* line)
	{
		return(false);
	}

	// RCR r/m32,imm8 -- Rotate r/m32 through carry by imm8 bits right
	bool ilsa_pass3_rcr(SLine* line)
	{
		return(false);
	}

	// REPne/z prefix
	bool ilsa_pass3_repne(SLine* line)
	{
		return(false);
	}

	// REP/e/z prefix
	bool ilsa_pass3_repe(SLine* line)
	{
		return(false);
	}

	// ROL r/m32,imm8 -- Rotate r/m32 by imm8 bits left
	bool ilsa_pass3_rol(SLine* line)
	{
		return(false);
	}

	// ROR r/m32,imm8 -- Rotate r/m32 by imm8 bits right
	bool ilsa_pass3_ror(SLine* line)
	{
		return(false);
	}

	// RDMSR -- Load MSR specified by ecx into edx:eax
	bool ilsa_pass3_rdmsr(SLine* line)
	{
		return(false);
	}

	// RDPMC -- Read performance monitoring counter specified by ecx into edx:eax
	bool ilsa_pass3_rdpmc(SLine* line)
	{
		return(false);
	}

	// RDTSC -- Read time-stamp counter into edx:eax
	bool ilsa_pass3_rdtsc(SLine* line)
	{
		return(false);
	}

	// RET imm16 -- Far return, and pop imm16 bytes from stack
	bool ilsa_pass3_ret(SLine* line)
	{
		return(false);
	}

	// SAHF -- Store ah into flags
	bool ilsa_pass3_sahf(SLine* line)
	{
		return(false);
	}

	// SAR r/m32,imm8 -- Signed divide r/m32 by imm8 times
	bool ilsa_pass3_sar(SLine* line)
	{
		return(false);
	}

	// SHL r/m32,imm8 -- Shift left r/m32 imm8 times
	bool ilsa_pass3_shl(SLine* line)
	{
		return(false);
	}

	// SHR r/m32,imm8 -- Shift right r/m32 imm8 times
	bool ilsa_pass3_shr(SLine* line)
	{
		return(false);
	}

	// SBB r32,r/m32 -- r/m32 from r32
	bool ilsa_pass3_sbb(SLine* line)
	{
		return(false);
	}

	// SCAS m32 -- Compare eax with dword in es:[e/di]
	bool ilsa_pass3_scas(SLine* line)
	{
		return(false);
	}

	// SCASB -- Shorthand for SCAS m8
	bool ilsa_pass3_scasb(SLine* line)
	{
		return(false);
	}

	// SCASW -- Shorthand for SCAS m16
	bool ilsa_pass3_scasw(SLine* line)
	{
		return(false);
	}

	// SCASD -- Shorthand for SCAS m32
	bool ilsa_pass3_scasd(SLine* line)
	{
		return(false);
	}

	// SETcc r/m8 -- Set byte if cc condition is met
	bool ilsa_pass3_setcc(SLine* line)
	{
		return(false);
	}

	// SGDT m48 -- Store GDTR to m48
	bool ilsa_pass3_sgdt(SLine* line)
	{
		return(false);
	}

	// SIDT m48 -- Store IDTR to m48
	bool ilsa_pass3_sidt(SLine* line)
	{
		return(false);
	}

	// SLDT r/m16 -- Store LDTR to r/m16
	bool ilsa_pass3_sldt(SLine* line)
	{
		return(false);
	}

	// SHLD r/m32,r32,cl -- Shift r/m32 left cl places, shiting in bits from r32
	bool ilsa_pass3_shld(SLine* line)
	{
		return(false);
	}

	// SHRD r/m32,r32,cl -- Shift r/m32 right cl places, shiting in bits from r32
	bool ilsa_pass3_shrd(SLine* line)
	{
		return(false);
	}

	// SMSW r32/m16 -- Store machine status word to r32/m16
	bool ilsa_pass3_smsw(SLine* line)
	{
		return(false);
	}

	// STC -- Set carry
	bool ilsa_pass3_stc(SLine* line)
	{
		return(false);
	}

	// STD -- Set direction
	bool ilsa_pass3_std(SLine* line)
	{
		return(false);
	}

	// STI -- Set interrupt
	bool ilsa_pass3_sti(SLine* line)
	{
		return(false);
	}

	// STOS m32 -- Store eax into es:[e/di]
	bool ilsa_pass3_stos(SLine* line)
	{
		return(false);
	}

	// STOSB -- Shorthand for STOS m8
	bool ilsa_pass3_stosb(SLine* line)
	{
		return(false);
	}

	// STOSW -- Shorthand for STOS m16
	bool ilsa_pass3_stosw(SLine* line)
	{
		return(false);
	}

	// STOSD -- Shorthand for STOS m32
	bool ilsa_pass3_stosd(SLine* line)
	{
		return(false);
	}

	// STR r/m16 -- Stores segment selector from TR in r/m16
	bool ilsa_pass3_str(SLine* line)
	{
		return(false);
	}

	// SUB r32,r/m32 -- r/m32 from r32
	bool ilsa_pass3_sub(SLine* line)
	{
		return(false);
	}

	// SYSENTER -- Fast system entry
	bool ilsa_pass3_sysenter(SLine* line)
	{
		return(false);
	}

	// SYSEXIT -- Fast system exit
	bool ilsa_pass3_sysexit(SLine* line)
	{
		return(false);
	}

	// TEST r/m32,r32 -- r32 and r/m32
	bool ilsa_pass3_test(SLine* line)
	{
		return(false);
	}

	// UD2 -- Raises invalid opcode exception
	bool ilsa_pass3_ud2(SLine* line)
	{
		return(false);
	}

	// VERR r/m16 -- Verify segment r/m16 can be read
	bool ilsa_pass3_verr(SLine* line)
	{
		return(false);
	}

	// VERW r/m16 -- Verify segment r/m16 can be written to
	bool ilsa_pass3_verw(SLine* line)
	{
		return(false);
	}

	// FWAIT -- Check pending unmasked floating-point exceptions
	bool ilsa_pass3_fwait(SLine* line)
	{
		return(false);
	}

	// WBINVD -- Write back and flush internal caches
	bool ilsa_pass3_wbinvd(SLine* line)
	{
		return(false);
	}

	// WRMSR -- Write the value in edx:eax to MSR specified by ecx
	bool ilsa_pass3_wrmsr(SLine* line)
	{
		return(false);
	}

	// XADD r/m32,r32 -- Exchange r32 and r/m32, and load sum into r/m32
	bool ilsa_pass3_xadd(SLine* line)
	{
		return(false);
	}

	// XCHG r/m32,r32 -- Exchange r32 and r/m32
	bool ilsa_pass3_xchg(SLine* line)
	{
		return(false);
	}

	// XLAT m8 -- Set al to ds:[e/bx + al]
	bool ilsa_pass3_xlat(SLine* line)
	{
		return(false);
	}

	// XLATB -- Shorthand for XLAT m8
	bool ilsa_pass3_xlatb(SLine* line)
	{
		return(false);
	}

	// XOR r32,r/m32 -- r/m32 and r32
	bool ilsa_pass3_xor(SLine* line)
	{
		return(false);
	}

	void ilsa_pass3(void)
	{
		u32		lniCodeBranch;
		SLine*	line;


		// Populate
		gsPass3_functions[iCodeBranch(_ICODE_LSA_AAA)]._func			= iAddress(aaa);			// AAA					-- ASCII adjust al after addition
		gsPass3_functions[iCodeBranch(_ICODE_LSA_AAD)]._func			= iAddress(aad);			// AAD					-- ASCII adjust ax before division
		gsPass3_functions[iCodeBranch(_ICODE_LSA_AAD2)]._func			= iAddress(aad2);			// AAD2					-- ASCII adjust ax before division to base imm8
		gsPass3_functions[iCodeBranch(_ICODE_LSA_AAM)]._func			= iAddress(aam);			// AAM					-- ASCII adjust ax after multiply
		gsPass3_functions[iCodeBranch(_ICODE_LSA_AAM2)]._func			= iAddress(aam2);			// AAM2					-- ASCII adjust ax after multiply to base imm8
		gsPass3_functions[iCodeBranch(_ICODE_LSA_AAS)]._func			= iAddress(aas);			// AAS					-- ASCII adjust al after subtraction
		gsPass3_functions[iCodeBranch(_ICODE_LSA_ADC)]._func			= iAddress(adc);			// ADC					-- Add with carry r/m32 to r32
		gsPass3_functions[iCodeBranch(_ICODE_LSA_ADD)]._func			= iAddress(add);			// ADD al,imm8			-- Add imm8 to al
		gsPass3_functions[iCodeBranch(_ICODE_LSA_AND)]._func			= iAddress(and);			// AND al,imm8			-- imm8  al
		gsPass3_functions[iCodeBranch(_ICODE_LSA_APRL)]._func			= iAddress(aprl);			// APRL r/m16,r16		-- Adjust RPL of r/m16 to not less than RPL of r16
		gsPass3_functions[iCodeBranch(_ICODE_LSA_BOUND)]._func			= iAddress(bound);			// BOUND r16,m16&16		-- Check if r16 (array index) is within bounds specified by m16&16
		gsPass3_functions[iCodeBranch(_ICODE_LSA_BSF)]._func			= iAddress(bsf);			// BSF r16,r/m16		-- Bit scan forward on r/m16
		gsPass3_functions[iCodeBranch(_ICODE_LSA_BSR)]._func			= iAddress(bsr);			// BSR r16,r/m16		-- Bit scan reverse on r/m16
		gsPass3_functions[iCodeBranch(_ICODE_LSA_BSWAP)]._func			= iAddress(bswap);			// BSWAP r32			-- Swap endian on 32-bit register
		gsPass3_functions[iCodeBranch(_ICODE_LSA_BT)]._func				= iAddress(bt);				// BT r/m32,imm8		-- Store selected bit in carry
		gsPass3_functions[iCodeBranch(_ICODE_LSA_BTC)]._func			= iAddress(btc);			// BTC r/m16,r16		-- Store selected bit in carry, and complement
		gsPass3_functions[iCodeBranch(_ICODE_LSA_BTR)]._func			= iAddress(btr);			// BTR r/m32,imm8		-- Store selected bit in carry, and clear
		gsPass3_functions[iCodeBranch(_ICODE_LSA_BTS)]._func			= iAddress(bts);			// BTS r/m32,imm8		-- Store selected bit in carry, and set
		gsPass3_functions[iCodeBranch(_ICODE_LSA_CALL)]._func			= iAddress(call);			// CALL m16:32			-- Call far, absolute indirect address in m16:32
		gsPass3_functions[iCodeBranch(_ICODE_LSA_CBW)]._func			= iAddress(cbw);			// CBW					-- Sign-extend al to ax
		gsPass3_functions[iCodeBranch(_ICODE_LSA_CWDE)]._func			= iAddress(cwde);			// CWDE					-- Sign-extend ax to eax
		gsPass3_functions[iCodeBranch(_ICODE_LSA_CLC)]._func			= iAddress(clc);			// CLC					-- Clear carry
		gsPass3_functions[iCodeBranch(_ICODE_LSA_CLD)]._func			= iAddress(cld);			// CLD					-- Clear direction
		gsPass3_functions[iCodeBranch(_ICODE_LSA_CLI)]._func			= iAddress(cli);			// CLI					-- Clear interrupt
		gsPass3_functions[iCodeBranch(_ICODE_LSA_CLTS)]._func			= iAddress(clts);			// CLTS					-- Clear task-switched flag in CR0
		gsPass3_functions[iCodeBranch(_ICODE_LSA_CMOVCC)]._func			= iAddress(cmovcc);			// CMOVcc r32,rm32		-- Move if cc flag condition is true
		gsPass3_functions[iCodeBranch(_ICODE_LSA_CMP)]._func			= iAddress(cmp);			// CMP al,imm8			-- imm8  al
		gsPass3_functions[iCodeBranch(_ICODE_LSA_CMPSB)]._func			= iAddress(cmpsb);			// CMPSB				-- Compare byte in ds:[esi] to es:[edi]
		gsPass3_functions[iCodeBranch(_ICODE_LSA_CMPSW)]._func			= iAddress(cmpsw);			// CMPSW				-- Compare word in ds:[esi] to es:[edi]
		gsPass3_functions[iCodeBranch(_ICODE_LSA_CMPSD)]._func			= iAddress(cmpsd);			// CMPSD				-- Compare dword in ds:[esi] to es:[edi]
		gsPass3_functions[iCodeBranch(_ICODE_LSA_CMPXCHG)]._func		= iAddress(cmpxchg);		// CMPXCHG r/m32,r32	-- Compare eax with r/m16, if equal set zero and load r32 into r/m32, if not equal clear zero and load r/m32 into eax
		gsPass3_functions[iCodeBranch(_ICODE_LSA_CMPXCHG8B)]._func		= iAddress(cmpxchg8b);		// CMPXCHG8B m64		-- Compare edx:eax with m64, if equal set zero and load ECX:EBX into m64, if not equal clear zero and load m64 into edx:eax
		gsPass3_functions[iCodeBranch(_ICODE_LSA_CPUID)]._func			= iAddress(cpuid);			// CPUID				-- Based on EAX, load processor information into registers
		gsPass3_functions[iCodeBranch(_ICODE_LSA_CDW)]._func			= iAddress(cdw);			// CDW					-- Sign-extend ax into dx:ax
		gsPass3_functions[iCodeBranch(_ICODE_LSA_CDQ)]._func			= iAddress(cdq);			// CDQ					-- Sign-extend eax into edx:eax
		gsPass3_functions[iCodeBranch(_ICODE_LSA_DAA)]._func			= iAddress(daa);			// DAA					-- Decimal adjust al after addition
		gsPass3_functions[iCodeBranch(_ICODE_LSA_DAS)]._func			= iAddress(das);			// DAS					-- Decimal adjust al after subtraction
		gsPass3_functions[iCodeBranch(_ICODE_LSA_DEC)]._func			= iAddress(dec);			// DEC r32				-- Decrement r32 by 1
		gsPass3_functions[iCodeBranch(_ICODE_LSA_DIV)]._func			= iAddress(div);			// DIV r/m32			-- Unsigned divide edx:eax by r/m32, quotient in eax, remainder in edx
		gsPass3_functions[iCodeBranch(_ICODE_LSA_EMMS)]._func			= iAddress(emms);			// EMMS					-- Empty the MMX state
		gsPass3_functions[iCodeBranch(_ICODE_LSA_ENTER)]._func			= iAddress(enter);			// ENTER imm16,imm8		-- Create a stack frame, or nested stack frame
		gsPass3_functions[iCodeBranch(_ICODE_LSA_F2XM1)]._func			= iAddress(f2xm1);			// F2XM1				-- st0 = 2^(st0 - 1) into st0
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FABS)]._func			= iAddress(fabs);			// FABS					-- st0 = fabs(st0)
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FADD)]._func			= iAddress(fadd);			// FADD f32				-- st0 = st0 + f32
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FADDP)]._func			= iAddress(faddp);			// FADDP stN,st0		-- stN = stN + st0, then pop
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FIADD)]._func			= iAddress(fiadd);			// FIADD s32			-- st0 = st0 + s32
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FBLD)]._func			= iAddress(fbld);			// FBLD m80				-- push m80 loaded as binary coded decimal into st0
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FBSTP)]._func			= iAddress(fbstp);			// FBSTP m80			-- Store st0 as binary coded decimal into m80, then pop
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FCHS)]._func			= iAddress(fchs);			// FCHS					-- Complement st0's sign
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FCLEX)]._func			= iAddress(fclex);			// FCLEX				-- Clear floating point exceptions after checking for pending unmasked exceptions
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FNCLEX)]._func			= iAddress(fnclex);			// FNCLEX				-- No-wait version of FCLEX
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FCMOVB)]._func			= iAddress(fcmovb);			// FCMOVB st0,stN		-- Move if carry
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FCMOVE)]._func			= iAddress(fcmove);			// FCMOVE st0,stN		-- Move if zero
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FCMOVBE)]._func		= iAddress(fcmovbe);		// FCMOVBE st0,stN		-- Move if carry or zero
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FCMOVU)]._func			= iAddress(fcmovu);			// FCMOVU st0,stN		-- Move if parity
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FCMOVNB)]._func		= iAddress(fcmovnb);		// FCMOVNB st0,stN		-- Move if not carry
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FCMOVNE)]._func		= iAddress(fcmovne);		// FCMOVNE st0,stN		-- Move if not zero
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FCMOVNBE)]._func		= iAddress(fcmovnbe);		// FCMOVNBE st0,stN		-- Move if not carry and not zero
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FCMOVNU)]._func		= iAddress(fcmovnu);		// FCMOVNU st0,stN		-- Move if not parity
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FCOM)]._func			= iAddress(fcom);			// FCOM f32				-- Compare st0 with f32
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FCOMP)]._func			= iAddress(fcomp);			// FCOMP stN			-- Compare st0 with stN, then pop
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FCOMPP)]._func			= iAddress(fcompp);			// FCOMPP				-- Compare st0 with st1, then pop, then pop again
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FCOMI)]._func			= iAddress(fcomi);			// FCOMI stN			-- Compare st0 with stN, and set eflags
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FCOMIP)]._func			= iAddress(fcomip);			// FCOMIP stN			-- Compare st0 with stN, and set eflags, then pop
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FUCOMI)]._func			= iAddress(fucomi);			// FUCOMI stN			-- Compare st0 with stN, check for ordered values, and set eflags
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FUCOMIP)]._func		= iAddress(fucomip);		// FUCOMIP stN			-- Compare st0 with stN, check for ordered values, and set eflags, then pop
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FCOS)]._func			= iAddress(fcos);			// FCOS					-- st0 = cos(st0)
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FDECSTP)]._func		= iAddress(fdecstp);		// FDECSTP				-- Decrement the TOP field in the FPU status word
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FDIV)]._func			= iAddress(fdiv);			// FDIV f32				-- st0 = st0 / f32
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FDIVP)]._func			= iAddress(fdivp);			// FDIVP stN,st0		-- stN = stN / st0, then pop
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FIDIV)]._func			= iAddress(fidiv);			// FIDIV s32			-- st0 = st0 / s32
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FDIVR)]._func			= iAddress(fdivr);			// FDIVR f64			-- st0 = f64 / st0
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FDIVRP)]._func			= iAddress(fdivrp);			// FDIVRP stN,st0		-- stN = st0 / stN, then pop
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FIDIVR)]._func			= iAddress(fidivr);			// FIDIVR s32			-- st0 = s32 / st0
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FFREE)]._func			= iAddress(ffree);			// FFREE stN			-- Set the tag for stN to empty
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FICOM)]._func			= iAddress(ficom);			// FICOM s32			-- Compare st0 to s32
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FICOMP)]._func			= iAddress(ficomp);			// FICOMP s32			-- Compare st0 to s32, then pop
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FILD)]._func			= iAddress(fild);			// FILD s16				-- Push s16 into st0
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FINCSTP)]._func		= iAddress(fincstp);		// FINCSTP				-- Increment the TOP field in the FPU status word
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FINIT)]._func			= iAddress(finit);			// FINIT				-- Initialize the FPU
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FIST)]._func			= iAddress(fist);			// FIST m32int			-- Store st0 to memory as s32
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FISTP)]._func			= iAddress(fistp);			// FISTP m64int			-- Store st0 to memory as s64, then pop
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FLD)]._func			= iAddress(fld);			// FLD stN				-- Push stN into st0
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FLD1)]._func			= iAddress(fld1);			// FLD1					-- Push +1.0 into st0
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FLD2T)]._func			= iAddress(fld2t);			// FLDL2T				-- Push log2(10) into st0
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FLD2E)]._func			= iAddress(fldl2e);			// FLDL2E				-- Push log2(e) into st0
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FLDPI)]._func			= iAddress(fldpi);			// FLDPI				-- Push pi into st0
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FLDLG2)]._func			= iAddress(fldlg2);			// FLDLG2				-- Push log10(2) into st0
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FLDN2)]._func			= iAddress(fldn2);			// FLDLN2				-- Push loge(2) into st0
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FLDZ)]._func			= iAddress(fldz);			// FLDZ					-- Push +0.0 into st0
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FLDCW)]._func			= iAddress(fldcw);			// FLDCW u16			-- Load u16 into FPU control word
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FLDENV)]._func			= iAddress(fldenv);			// FLDENV m14/m28		-- Load 14-byte or 28-byte into environment
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FMUL)]._func			= iAddress(fmul);			// FMUL stN,st0			-- stN = stN * st0
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FMULP)]._func			= iAddress(fmulp);			// FMULP stN,st0		-- stN = stN * st0, then pop
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FIMUL)]._func			= iAddress(fimul);			// FIMUL m32int			-- st0 = st0 * s32
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FNOP)]._func			= iAddress(fnop);			// FNOP					-- No operation
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FPATAN)]._func			= iAddress(fpatan);			// FPATAN				-- st1 = arctan(st1 / st0), then pop
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FPREM)]._func			= iAddress(fprem);			// FPREM				-- st0 = st0 % st1
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FPREM1)]._func			= iAddress(fprem1);			// FPREM1				-- st0 = IEEE st0 % st1
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FPTAN)]._func			= iAddress(fptan);			// FPTAN				-- st0 = tan(st0), then push 1 into st0
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FRNDINT)]._func		= iAddress(frndint);		// FRNDINT				-- st0 = int(st0)
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FRSTOR)]._func			= iAddress(frstor);			// FRSTOR m94/m108		-- Load FPU state from a 94 or 108 byte block
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FSAVE)]._func			= iAddress(fsave);			// FSAVE m94/m108		-- Store the FPU state to a 94 or 108 byte block
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FSCALE)]._func			= iAddress(fscale);			// FSCALE				-- st0 = 2^stN
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FSIN)]._func			= iAddress(fsin);			// FSIN					-- st0 = sin(st0)
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FSINCOS)]._func		= iAddress(fsincos);		// FSINCOS				-- t = cos(st0), st0 = sin(st0), then push t into st0
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FSQRT)]._func			= iAddress(fsqrt);			// FSQRT				-- st0 = sqrt(st0)
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FST)]._func			= iAddress(fst);			// FST stN				-- Copy st0 to stN, then pop
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FSTCW)]._func			= iAddress(fstcw);			// FSTCW m16			-- Copy FPU status word to m16
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FSTENV)]._func			= iAddress(fstenv);			// FSTENV m14/m28		-- Copy FPU environment to 14-byte or 28-byte block
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FSTSW)]._func			= iAddress(fstsw);			// FSTSW ax				-- Copy FPU status word to ax
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FSUB)]._func			= iAddress(fsub);			// FSUB stN,st0			-- stN = stN - st0
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FSUBP)]._func			= iAddress(fsubp);			// FSUBP stN,st0		-- stN = stN - st0, then pop
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FISUB)]._func			= iAddress(fisub);			// FISUB s16			-- st0 = st0 - s16
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FSUBR)]._func			= iAddress(fsubr);			// FSUBR stN,st0		-- stN = st0 - stN
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FSUBRP)]._func			= iAddress(fsubrp);			// FSUBRP stN,st0		-- stN = st0 - stN, then pop
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FISUBR)]._func			= iAddress(fisubr);			// FISUBR s16			-- st0 = s16 - st0
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FTST)]._func			= iAddress(ftst);			// FTST					-- Compare st0 to +0.0
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FUCOM)]._func			= iAddress(fucom);			// FUCOM stN			-- Compare st0 to stN
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FUCOMP)]._func			= iAddress(fucomp);			// FUCOMP stN			-- Compare st0 to stN, then pop
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FUCOMPP)]._func		= iAddress(fucompp);		// FUCOMPP				-- Compare st0 to st1, then pop
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FXAM)]._func			= iAddress(fxam);			// FXAM					-- Classify st0
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FXCH)]._func			= iAddress(fxch);			// FXCH stN				-- Exchange st0 and stN
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FXTRACT)]._func		= iAddress(fxtract);		// FXTRACT				-- t = st0's exponent, st0 = st0's significand, then push t into st0
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FYL2X)]._func			= iAddress(fyl2x);			// FYL2X				-- st1 = st1 * log2(st0), then pop
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FYL2XP1)]._func		= iAddress(fyl2xp1);		// FYL2XP1				-- st1 = st1 * log2(st0 + 1.0), then pop
		gsPass3_functions[iCodeBranch(_ICODE_LSA_HLT)]._func			= iAddress(hlt);			// HLT					-- Halt until interrupt
		gsPass3_functions[iCodeBranch(_ICODE_LSA_IDIV)]._func			= iAddress(idiv);			// IDIV r/m32			-- Integer divide edx:eax, eax=quotient, edx=remainder
		gsPass3_functions[iCodeBranch(_ICODE_LSA_IMUL)]._func			= iAddress(imul);			// IMUL r32,r/m32,imm32	-- r32 = r32 * r/m32 * imm32
		gsPass3_functions[iCodeBranch(_ICODE_LSA_IN)]._func				= iAddress(in);				// IN eax,dx			-- Read dword from I/o port in dx
		gsPass3_functions[iCodeBranch(_ICODE_LSA_INC)]._func			= iAddress(inc);			// INC r32				-- Increment r32 by 1
		gsPass3_functions[iCodeBranch(_ICODE_LSA_INS)]._func			= iAddress(ins);			// INS m32,dx			-- Input a dword from I/O port in dx, store to es:[e/di]
		gsPass3_functions[iCodeBranch(_ICODE_LSA_INSB)]._func			= iAddress(insb);			// INSB					-- Shorthand for INS m8,dx
		gsPass3_functions[iCodeBranch(_ICODE_LSA_INSW)]._func			= iAddress(insw);			// INSW					-- Shorthand for INS m16,dx
		gsPass3_functions[iCodeBranch(_ICODE_LSA_INSD)]._func			= iAddress(insd);			// INSD					-- Shorthand for INS m32,dx
		gsPass3_functions[iCodeBranch(_ICODE_LSA_INT3)]._func			= iAddress(int3);			// INT3					-- Trap to debugger, one byte
		gsPass3_functions[iCodeBranch(_ICODE_LSA_INT)]._func			= iAddress(int);			// INT imm8				-- Interrupt vector imm8
		gsPass3_functions[iCodeBranch(_ICODE_LSA_INTO)]._func			= iAddress(into);			// INTO					-- Interrupt on overflow
		gsPass3_functions[iCodeBranch(_ICODE_LSA_INVD)]._func			= iAddress(invd);			// INVD					-- Invalidate internal caches
		gsPass3_functions[iCodeBranch(_ICODE_LSA_INVLPG)]._func			= iAddress(invlpg);			// INVLPG m				-- Invalidate TLB entry for page that contains m
		gsPass3_functions[iCodeBranch(_ICODE_LSA_IRET)]._func			= iAddress(iret);			// IRET					-- Interrupt return 16-bit
		gsPass3_functions[iCodeBranch(_ICODE_LSA_IRETD)]._func			= iAddress(iretd);			// IRETD				-- Interrupt return 32-bit
		gsPass3_functions[iCodeBranch(_ICODE_LSA_JCC)]._func			= iAddress(jcc);			// Jcc imm32			-- Conditional jump relative by imm32 offset
		gsPass3_functions[iCodeBranch(_ICODE_LSA_JMP)]._func			= iAddress(jmp);			// JMP m16:32			-- Jump far, absolute indirect, address in m16:32
		gsPass3_functions[iCodeBranch(_ICODE_LSA_LAHF)]._func			= iAddress(lahf);			// LAHF					-- ah = eflags.sf:zf:0:af:0:pf:1:cf
		gsPass3_functions[iCodeBranch(_ICODE_LSA_LAR)]._func			= iAddress(lar);			// LAR r32,r/m32		-- r32 = r/m32 & 00fxff00h
		gsPass3_functions[iCodeBranch(_ICODE_LSA_LDS)]._func			= iAddress(lds);			// LDS r32,m16:32		-- Load DS:r32 indirect from far pointer
		gsPass3_functions[iCodeBranch(_ICODE_LSA_LSS)]._func			= iAddress(lss);			// LSS r32,m16:32		-- Load SS:r32 indirect from far pointer
		gsPass3_functions[iCodeBranch(_ICODE_LSA_LES)]._func			= iAddress(les);			// LES r32,m16:32		-- Load ES:r32 indirect from far pointer
		gsPass3_functions[iCodeBranch(_ICODE_LSA_LFS)]._func			= iAddress(lfs);			// LFS r32,m16:32		-- Load FS:r32 indirect from far pointer
		gsPass3_functions[iCodeBranch(_ICODE_LSA_LGS)]._func			= iAddress(lgs);			// LGS r32,m16:32		-- Load GS:r32 indirect from far pointer
		gsPass3_functions[iCodeBranch(_ICODE_LSA_LEA)]._func			= iAddress(lea);			// LEA r32,m			-- Store effective address for m in r32
		gsPass3_functions[iCodeBranch(_ICODE_LSA_LEAVE)]._func			= iAddress(leave);			// LEAVE				-- esp = ebp, then pop ebp
		gsPass3_functions[iCodeBranch(_ICODE_LSA_LGDT)]._func			= iAddress(lgdt);			// LGDT m16&32			-- Load m into GDTR
		gsPass3_functions[iCodeBranch(_ICODE_LSA_LIDT)]._func			= iAddress(lidt);			// LIDT m16&32			-- Load m into IDTR
		gsPass3_functions[iCodeBranch(_ICODE_LSA_LLDT)]._func			= iAddress(lldt);			// LLDT r/m16			-- Load selector into LDTR
		gsPass3_functions[iCodeBranch(_ICODE_LSA_LMSW)]._func			= iAddress(lmsw);			// LMSW r/m16			-- Loads r/m16 into bits cr0
		gsPass3_functions[iCodeBranch(_ICODE_LSA_LOCK)]._func			= iAddress(lock);			// LOCK					-- Prefix for other instructions, locks system bus
		gsPass3_functions[iCodeBranch(_ICODE_LSA_LODS)]._func			= iAddress(lods);			// LODS m32				-- Load dword from ds:[e/si] into eax
		gsPass3_functions[iCodeBranch(_ICODE_LSA_LODSB)]._func			= iAddress(lodsb);			// LODSB				-- Shorthand for LODS m8
		gsPass3_functions[iCodeBranch(_ICODE_LSA_LODSW)]._func			= iAddress(lodsw);			// LODSW				-- Shorthand for LODS m16
		gsPass3_functions[iCodeBranch(_ICODE_LSA_LODSD)]._func			= iAddress(lodsd);			// LODSD				-- Shorthand for LODS m32
		gsPass3_functions[iCodeBranch(_ICODE_LSA_LOOP)]._func			= iAddress(loop);			// LOOP imm8			-- Decrement count, jump short if count != 0
		gsPass3_functions[iCodeBranch(_ICODE_LSA_LOOPE)]._func			= iAddress(loope);			// LOOPE imm8			-- Decrement count, jump short if count != 0 and zero
		gsPass3_functions[iCodeBranch(_ICODE_LSA_LOOPZ)]._func			= iAddress(loopz);			// LOOPZ imm8			-- Synonym for LOOPE
		gsPass3_functions[iCodeBranch(_ICODE_LSA_LOOPNE)]._func			= iAddress(loopne);			// LOOPNE imm8			-- Decrement count, jump short if count != 0 and !zero
		gsPass3_functions[iCodeBranch(_ICODE_LSA_LOOPNZ)]._func			= iAddress(loopnz);			// LOOPNZ imm8			-- Synonym for LOOPNE
		gsPass3_functions[iCodeBranch(_ICODE_LSA_LSL)]._func			= iAddress(lsl);			// LSL r32,r/m32		-- r32 = segment_limit(r/m32)
		gsPass3_functions[iCodeBranch(_ICODE_LSA_LTR)]._func			= iAddress(ltr);			// LTR r/m16			-- Load r/m16 into TR
		gsPass3_functions[iCodeBranch(_ICODE_LSA_MOV)]._func			= iAddress(mov);			// MOV mm/m64,mmN		-- Move mmN to mmN/m64
		gsPass3_functions[iCodeBranch(_ICODE_LSA_MOVS)]._func			= iAddress(movs);			// MOVS m32,m32			-- Move dword from ds:[e/si] to es:[e/di] 
		gsPass3_functions[iCodeBranch(_ICODE_LSA_MOVSB)]._func			= iAddress(movsb);			// MOVSB				-- Shorthand for MOVS m8,m8
		gsPass3_functions[iCodeBranch(_ICODE_LSA_MOVSW)]._func			= iAddress(movsw);			// MOVSW				-- Shorthand for MOVS m16,m16
		gsPass3_functions[iCodeBranch(_ICODE_LSA_MOVSD)]._func			= iAddress(movsd);			// MOVSD				-- Shorthand for MOVS m32,m32
		gsPass3_functions[iCodeBranch(_ICODE_LSA_MOVSX)]._func			= iAddress(movsx);			// MOVSX r32,r/m16		-- Sign-extend word to dword
		gsPass3_functions[iCodeBranch(_ICODE_LSA_MOVZX)]._func			= iAddress(movzx);			// MOVZX r32,r/m16		-- Zero-extend word to dword
		gsPass3_functions[iCodeBranch(_ICODE_LSA_MUL)]._func			= iAddress(mul);			// MUL r/m32			-- edx:eax = eax * r/m32
		gsPass3_functions[iCodeBranch(_ICODE_LSA_NEG)]._func			= iAddress(neg);			// NEG r/m32			-- Two's complement r/m32
		gsPass3_functions[iCodeBranch(_ICODE_LSA_NOP)]._func			= iAddress(nop);			// NOP					-- No operation
		gsPass3_functions[iCodeBranch(_ICODE_LSA_NOT)]._func			= iAddress(not);			// NOT r/m32			-- Logical NOT of r/m32
		gsPass3_functions[iCodeBranch(_ICODE_LSA_OR)]._func				= iAddress(or);				// OR r32,r/m32			-- r/m32 to r32
		gsPass3_functions[iCodeBranch(_ICODE_LSA_OUT)]._func			= iAddress(out);			// OUT dx,eax			-- Output eax to I/O port dx
		gsPass3_functions[iCodeBranch(_ICODE_LSA_OUTS)]._func			= iAddress(outs);			// OUTS dx,m32			-- Output dword at ds:[e/si] to I/O port dx
		gsPass3_functions[iCodeBranch(_ICODE_LSA_OUTSB)]._func			= iAddress(outsb);			// OUTSB				-- Shorthand for OUTS dx,m8
		gsPass3_functions[iCodeBranch(_ICODE_LSA_OUTSW)]._func			= iAddress(outsw);			// OUTSW				-- Shorthand for OUTS dx,m16
		gsPass3_functions[iCodeBranch(_ICODE_LSA_OUTSD)]._func			= iAddress(outsd);			// OUTSD				-- Shorthand for OUTS dx,m32
		gsPass3_functions[iCodeBranch(_ICODE_LSA_POP)]._func			= iAddress(pop);			// POP GS				-- Pop stack into GS
		gsPass3_functions[iCodeBranch(_ICODE_LSA_POPA)]._func			= iAddress(popa);			// POPA					-- Pop all r16 registers
		gsPass3_functions[iCodeBranch(_ICODE_LSA_POPAD)]._func			= iAddress(popad);			// POPAD				-- Pop all r32 registers
		gsPass3_functions[iCodeBranch(_ICODE_LSA_POPF)]._func			= iAddress(popf);			// POPF					-- Pop 16-bit flags
		gsPass3_functions[iCodeBranch(_ICODE_LSA_POPFD)]._func			= iAddress(popfd);			// POPFD				-- Pop 32-bit eflags
		gsPass3_functions[iCodeBranch(_ICODE_LSA_PREFETCH0)]._func		= iAddress(prefetch0);		// PREFETCHT0 m8		-- Prefetch block around m8 into all caches
		gsPass3_functions[iCodeBranch(_ICODE_LSA_PREFETCH1)]._func		= iAddress(prefetch1);		// PREFETCHT1 m8		-- Prefetch block around m8 into l1 and above
		gsPass3_functions[iCodeBranch(_ICODE_LSA_PREFETCH2)]._func		= iAddress(prefetch2);		// PREFETCHT2 m8		-- Prefetch block around m8 into l2 and above
		gsPass3_functions[iCodeBranch(_ICODE_LSA_PREFETCHNTA)]._func	= iAddress(prefetchnta);	// PREFETCHNTA m8		-- Prefetch block around m8 into non-temporal caches
		gsPass3_functions[iCodeBranch(_ICODE_LSA_PUSH)]._func			= iAddress(push);			// PUSH gs				-- Push GS
		gsPass3_functions[iCodeBranch(_ICODE_LSA_PUSHA)]._func			= iAddress(pusha);			// PUSHA				-- Push all 16-bit registers
		gsPass3_functions[iCodeBranch(_ICODE_LSA_PUSHAD)]._func			= iAddress(pushad);			// PUSHAD				-- Push all 32-bit registers
		gsPass3_functions[iCodeBranch(_ICODE_LSA_PUSHF)]._func			= iAddress(pushf);			// PUSHF				-- Push 16-bit flags
		gsPass3_functions[iCodeBranch(_ICODE_LSA_PUSHFD)]._func			= iAddress(pushfd);			// PUSHFD				-- Push 32-bit eflags
		gsPass3_functions[iCodeBranch(_ICODE_LSA_RCL)]._func			= iAddress(rcl);			// RCL r/m32,imm8		-- Rotate r/m32 through carry by imm8 bits left
		gsPass3_functions[iCodeBranch(_ICODE_LSA_RCR)]._func			= iAddress(rcr);			// RCR r/m32,imm8		-- Rotate r/m32 through carry by imm8 bits right
		gsPass3_functions[iCodeBranch(_ICODE_LSA_REPNE)]._func			= iAddress(repne);			// REPne/z prefix
		gsPass3_functions[iCodeBranch(_ICODE_LSA_REPNZ)]._func			= iAddress(repne);			// REPne/z prefix
		gsPass3_functions[iCodeBranch(_ICODE_LSA_REPE)]._func			= iAddress(repe);			// REP/e/z prefix
		gsPass3_functions[iCodeBranch(_ICODE_LSA_REPZ)]._func			= iAddress(repe);			// REP/e/z prefix
		gsPass3_functions[iCodeBranch(_ICODE_LSA_ROL)]._func			= iAddress(rol);			// ROL r/m32,imm8		-- Rotate r/m32 by imm8 bits left
		gsPass3_functions[iCodeBranch(_ICODE_LSA_ROR)]._func			= iAddress(ror);			// ROR r/m32,imm8		-- Rotate r/m32 by imm8 bits right
		gsPass3_functions[iCodeBranch(_ICODE_LSA_RDMSR)]._func			= iAddress(rdmsr);			// RDMSR				-- Load MSR specified by ecx into edx:eax
		gsPass3_functions[iCodeBranch(_ICODE_LSA_RDPMC)]._func			= iAddress(rdpmc);			// RDPMC				-- Read performance monitoring counter specified by ecx into edx:eax
		gsPass3_functions[iCodeBranch(_ICODE_LSA_RDTSC)]._func			= iAddress(rdtsc);			// RDTSC				-- Read time-stamp counter into edx:eax
		gsPass3_functions[iCodeBranch(_ICODE_LSA_RET)]._func			= iAddress(ret);			// RET imm16			-- Far return, and pop imm16 bytes from stack
		gsPass3_functions[iCodeBranch(_ICODE_LSA_SAHF)]._func			= iAddress(sahf);			// SAHF					-- Store ah into flags
		gsPass3_functions[iCodeBranch(_ICODE_LSA_SAR)]._func			= iAddress(sar);			// SAR r/m32,imm8		-- Signed divide r/m32 by imm8 times
		gsPass3_functions[iCodeBranch(_ICODE_LSA_SHL)]._func			= iAddress(shl);			// SHL r/m32,imm8		-- Shift left r/m32 imm8 times
		gsPass3_functions[iCodeBranch(_ICODE_LSA_SHR)]._func			= iAddress(shr);			// SHR r/m32,imm8		-- Shift right r/m32 imm8 times
		gsPass3_functions[iCodeBranch(_ICODE_LSA_SBB)]._func			= iAddress(sbb);			// SBB r32,r/m32		-- r/m32 from r32
		gsPass3_functions[iCodeBranch(_ICODE_LSA_SCAS)]._func			= iAddress(scas);			// SCAS m32				-- Compare eax with dword in es:[e/di]
		gsPass3_functions[iCodeBranch(_ICODE_LSA_SCASB)]._func			= iAddress(scasb);			// SCASB				-- Shorthand for SCAS m8
		gsPass3_functions[iCodeBranch(_ICODE_LSA_SCASW)]._func			= iAddress(scasw);			// SCASW				-- Shorthand for SCAS m16
		gsPass3_functions[iCodeBranch(_ICODE_LSA_SCASD)]._func			= iAddress(scasd);			// SCASD				-- Shorthand for SCAS m32
		gsPass3_functions[iCodeBranch(_ICODE_LSA_SETCC)]._func			= iAddress(setcc);			// SETcc r/m8			-- Set byte if cc condition is met
		gsPass3_functions[iCodeBranch(_ICODE_LSA_SGDT)]._func			= iAddress(sgdt);			// SGDT m48				-- Store GDTR to m48
		gsPass3_functions[iCodeBranch(_ICODE_LSA_SIDT)]._func			= iAddress(sidt);			// SIDT m48				-- Store IDTR to m48
		gsPass3_functions[iCodeBranch(_ICODE_LSA_SLDT)]._func			= iAddress(sldt);			// SLDT r/m16			-- Store LDTR to r/m16
		gsPass3_functions[iCodeBranch(_ICODE_LSA_SHLD)]._func			= iAddress(shld);			// SHLD r/m32,r32,cl	-- Shift r/m32 left cl places, shiting in bits from r32
		gsPass3_functions[iCodeBranch(_ICODE_LSA_SHRD)]._func			= iAddress(shrd);			// SHRD r/m32,r32,cl	-- Shift r/m32 right cl places, shiting in bits from r32
		gsPass3_functions[iCodeBranch(_ICODE_LSA_SMSW)]._func			= iAddress(smsw);			// SMSW r32/m16			-- Store machine status word to r32/m16
		gsPass3_functions[iCodeBranch(_ICODE_LSA_STC)]._func			= iAddress(stc);			// STC					-- Set carry
		gsPass3_functions[iCodeBranch(_ICODE_LSA_STD)]._func			= iAddress(std);			// STD					-- Set direction
		gsPass3_functions[iCodeBranch(_ICODE_LSA_STI)]._func			= iAddress(sti);			// STI					-- Set interrupt
		gsPass3_functions[iCodeBranch(_ICODE_LSA_STOS)]._func			= iAddress(stos);			// STOS m32				-- Store eax into es:[e/di]
		gsPass3_functions[iCodeBranch(_ICODE_LSA_STOSB)]._func			= iAddress(stosb);			// STOSB				-- Shorthand for STOS m8
		gsPass3_functions[iCodeBranch(_ICODE_LSA_STOSW)]._func			= iAddress(stosw);			// STOSW				-- Shorthand for STOS m16
		gsPass3_functions[iCodeBranch(_ICODE_LSA_STOSD)]._func			= iAddress(stosd);			// STOSD				-- Shorthand for STOS m32
		gsPass3_functions[iCodeBranch(_ICODE_LSA_STR)]._func			= iAddress(str);			// STR r/m16			-- Stores segment selector from TR in r/m16
		gsPass3_functions[iCodeBranch(_ICODE_LSA_SUB)]._func			= iAddress(sub);			// SUB r32,r/m32		-- r/m32 from r32
		gsPass3_functions[iCodeBranch(_ICODE_LSA_SYSENTER)]._func		= iAddress(sysenter);		// SYSENTER				-- Fast system entry
		gsPass3_functions[iCodeBranch(_ICODE_LSA_SYSEXIT)]._func		= iAddress(sysexit);		// SYSEXIT				-- Fast system exit
		gsPass3_functions[iCodeBranch(_ICODE_LSA_TEST)]._func			= iAddress(test);			// TEST r/m32,r32		-- r32 and r/m32
		gsPass3_functions[iCodeBranch(_ICODE_LSA_UD2)]._func			= iAddress(ud2);			// UD2					-- Raises invalid opcode exception
		gsPass3_functions[iCodeBranch(_ICODE_LSA_VERR)]._func			= iAddress(verr);			// VERR r/m16			-- Verify segment r/m16 can be read
		gsPass3_functions[iCodeBranch(_ICODE_LSA_VERW)]._func			= iAddress(verw);			// VERW r/m16			-- Verify segment r/m16 can be written to
		gsPass3_functions[iCodeBranch(_ICODE_LSA_FWAIT)]._func			= iAddress(fwait);			// FWAIT				-- Check pending unmasked floating-point exceptions
		gsPass3_functions[iCodeBranch(_ICODE_LSA_WBINVD)]._func			= iAddress(wbinvd);			// WBINVD				-- Write back and flush internal caches
		gsPass3_functions[iCodeBranch(_ICODE_LSA_WRMSR)]._func			= iAddress(wrmsr);			// WRMSR				-- Write the value in edx:eax to MSR specified by ecx
		gsPass3_functions[iCodeBranch(_ICODE_LSA_XADD)]._func			= iAddress(xadd);			// XADD r/m32,r32		-- Exchange r32 and r/m32, and load sum into r/m32
		gsPass3_functions[iCodeBranch(_ICODE_LSA_XCHG)]._func			= iAddress(xchg);			// XCHG r/m32,r32		-- Exchange r32 and r/m32
		gsPass3_functions[iCodeBranch(_ICODE_LSA_XLAT)]._func			= iAddress(xlat);			// XLAT m8				-- Set al to ds:[e/bx + al]
		gsPass3_functions[iCodeBranch(_ICODE_LSA_XLATB)]._func			= iAddress(xlatb);			// XLATB				-- Shorthand for XLAT m8
		gsPass3_functions[iCodeBranch(_ICODE_LSA_XOR)]._func			= iAddress(xor);			// XOR r32,r/m32		-- r/m32 and r32

		// Iterate through every line
		for (line = cmdLine.file->firstLine; line; line = line->ll.nextLine)
		{
			// Only applying to uncompleted lines
			if (!ilsa_status_line_isCompleted(line) && line->firstComp && !ilsa_status_comp_isCompleted(line->firstComp))
			{
				lniCodeBranch = iCodeBranch(line->firstComp->iCode);
				if (lniCodeBranch >= _LSA_PASS3_CODE_BRANCH_MIN && lniCodeBranch <= _LSA_PASS3_CODE_BRANCH_MAX)
				{
					if (!gsPass3_functions[lniCodeBranch].func(line))
					{
						// Error

					} else {
						// We're good
					}
				}
				//else Not a line for us to decode
			}
		}
	}
