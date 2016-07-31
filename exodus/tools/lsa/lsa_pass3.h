//////////
//
// /libsf/exodus/tools/lsa/lsa_pass3.h
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
//     Jul.30.2016
//////
// Change log:
//     Jul.30.2016 - Initial creation
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
// Pass 3-specific information.
//
//////




struct SPass3Func
{
	union
	{
		uptr	_func;
		bool	(*func)		(SLine* line, SComp* comp);
	};
};

#define _LSA_PASS3_ICODE_BIT				21
#define	iEncode_pass3_branchAddress(i)		((((u32)i << (_LSA_PASS3_ICODE_BIT + 1))) + (1 << _LSA_PASS3_ICODE_BIT))
#define	iDecode_pass3_branchAddress(i)		(((u32)i & 0xffc00000) >> 22)
#define	iGenerate_pass3_functionName(a)		(uptr)&ilsa_pass3_##a

#define _LSA_PASS3_CODE_BRANCH_MIN 1

cs32	_ICODE_LSA_AAA							= iEncode_pass3_branchAddress(1);
cs32	_ICODE_LSA_AAD							= iEncode_pass3_branchAddress(2);
cs32	_ICODE_LSA_AAD2							= iEncode_pass3_branchAddress(3);
cs32	_ICODE_LSA_AAM							= iEncode_pass3_branchAddress(4);
cs32	_ICODE_LSA_AAM2							= iEncode_pass3_branchAddress(5);
cs32	_ICODE_LSA_AAS							= iEncode_pass3_branchAddress(6);
cs32	_ICODE_LSA_ADC							= iEncode_pass3_branchAddress(7);
cs32	_ICODE_LSA_ADD							= iEncode_pass3_branchAddress(8);
cs32	_ICODE_LSA_AND							= iEncode_pass3_branchAddress(9);
cs32	_ICODE_LSA_APRL							= iEncode_pass3_branchAddress(10);
cs32	_ICODE_LSA_BOUND						= iEncode_pass3_branchAddress(11);
cs32	_ICODE_LSA_BSF							= iEncode_pass3_branchAddress(12);
cs32	_ICODE_LSA_BSR							= iEncode_pass3_branchAddress(13);
cs32	_ICODE_LSA_BSWAP						= iEncode_pass3_branchAddress(14);
cs32	_ICODE_LSA_BT							= iEncode_pass3_branchAddress(15);
cs32	_ICODE_LSA_BTC							= iEncode_pass3_branchAddress(16);
cs32	_ICODE_LSA_BTR							= iEncode_pass3_branchAddress(17);
cs32	_ICODE_LSA_BTS							= iEncode_pass3_branchAddress(18);
cs32	_ICODE_LSA_CALL							= iEncode_pass3_branchAddress(19);
cs32	_ICODE_LSA_CBW							= iEncode_pass3_branchAddress(20);
cs32	_ICODE_LSA_CWDE							= iEncode_pass3_branchAddress(21);
cs32	_ICODE_LSA_CLC							= iEncode_pass3_branchAddress(22);
cs32	_ICODE_LSA_CLD							= iEncode_pass3_branchAddress(23);
cs32	_ICODE_LSA_CLI							= iEncode_pass3_branchAddress(24);
cs32	_ICODE_LSA_CLTS							= iEncode_pass3_branchAddress(25);
cs32	_ICODE_LSA_CMOVO						= iEncode_pass3_branchAddress(26);
cs32	_ICODE_LSA_CMOVNO						= iEncode_pass3_branchAddress(27);
cs32	_ICODE_LSA_CMOVB						= iEncode_pass3_branchAddress(28);
cs32	_ICODE_LSA_CMOVNAE						= iEncode_pass3_branchAddress(29);
cs32	_ICODE_LSA_CMOVAE						= iEncode_pass3_branchAddress(30);
cs32	_ICODE_LSA_CMOVNB						= iEncode_pass3_branchAddress(31);
cs32	_ICODE_LSA_CMOVZ						= iEncode_pass3_branchAddress(32);
cs32	_ICODE_LSA_CMOVE						= iEncode_pass3_branchAddress(33);
cs32	_ICODE_LSA_CMOVNZ						= iEncode_pass3_branchAddress(34);
cs32	_ICODE_LSA_CMOVNE						= iEncode_pass3_branchAddress(35);
cs32	_ICODE_LSA_CMOVNA						= iEncode_pass3_branchAddress(36);
cs32	_ICODE_LSA_CMOVBE						= iEncode_pass3_branchAddress(37);
cs32	_ICODE_LSA_CMOVA						= iEncode_pass3_branchAddress(38);
cs32	_ICODE_LSA_CMOVNBE						= iEncode_pass3_branchAddress(39);
cs32	_ICODE_LSA_CMOVS						= iEncode_pass3_branchAddress(40);
cs32	_ICODE_LSA_CMOVNS						= iEncode_pass3_branchAddress(41);
cs32	_ICODE_LSA_CMOVP						= iEncode_pass3_branchAddress(42);
cs32	_ICODE_LSA_CMOVPE						= iEncode_pass3_branchAddress(43);
cs32	_ICODE_LSA_CMOVNP						= iEncode_pass3_branchAddress(44);
cs32	_ICODE_LSA_CMOVPO						= iEncode_pass3_branchAddress(45);
cs32	_ICODE_LSA_CMOVL						= iEncode_pass3_branchAddress(46);
cs32	_ICODE_LSA_CMOVNGE						= iEncode_pass3_branchAddress(47);
cs32	_ICODE_LSA_CMOVGE						= iEncode_pass3_branchAddress(48);
cs32	_ICODE_LSA_CMOVNL						= iEncode_pass3_branchAddress(49);
cs32	_ICODE_LSA_CMOVLE						= iEncode_pass3_branchAddress(50);
cs32	_ICODE_LSA_CMOVNG						= iEncode_pass3_branchAddress(51);
cs32	_ICODE_LSA_CMOVG						= iEncode_pass3_branchAddress(52);
cs32	_ICODE_LSA_CMOVNLE						= iEncode_pass3_branchAddress(53);
cs32	_ICODE_LSA_CMP							= iEncode_pass3_branchAddress(54);
cs32	_ICODE_LSA_CMPSB						= iEncode_pass3_branchAddress(55);
cs32	_ICODE_LSA_CMPSW						= iEncode_pass3_branchAddress(56);
cs32	_ICODE_LSA_CMPSD						= iEncode_pass3_branchAddress(57);
cs32	_ICODE_LSA_CMPXCHG						= iEncode_pass3_branchAddress(58);
cs32	_ICODE_LSA_CMPXCHG8B					= iEncode_pass3_branchAddress(59);
cs32	_ICODE_LSA_CPUID						= iEncode_pass3_branchAddress(60);
cs32	_ICODE_LSA_CDW							= iEncode_pass3_branchAddress(61);
cs32	_ICODE_LSA_CDQ							= iEncode_pass3_branchAddress(62);
cs32	_ICODE_LSA_DAA							= iEncode_pass3_branchAddress(63);
cs32	_ICODE_LSA_DAS							= iEncode_pass3_branchAddress(64);
cs32	_ICODE_LSA_DEC							= iEncode_pass3_branchAddress(65);
cs32	_ICODE_LSA_DIV							= iEncode_pass3_branchAddress(66);
cs32	_ICODE_LSA_EMMS							= iEncode_pass3_branchAddress(67);
cs32	_ICODE_LSA_ENTER						= iEncode_pass3_branchAddress(68);
cs32	_ICODE_LSA_F2XM1						= iEncode_pass3_branchAddress(69);
cs32	_ICODE_LSA_FABS							= iEncode_pass3_branchAddress(70);
cs32	_ICODE_LSA_FADD							= iEncode_pass3_branchAddress(71);
cs32	_ICODE_LSA_FADDP						= iEncode_pass3_branchAddress(72);
cs32	_ICODE_LSA_FIADD						= iEncode_pass3_branchAddress(73);
cs32	_ICODE_LSA_FBLD							= iEncode_pass3_branchAddress(74);
cs32	_ICODE_LSA_FBSTP						= iEncode_pass3_branchAddress(75);
cs32	_ICODE_LSA_FCHS							= iEncode_pass3_branchAddress(76);
cs32	_ICODE_LSA_FCLEX						= iEncode_pass3_branchAddress(77);
cs32	_ICODE_LSA_FNCLEX						= iEncode_pass3_branchAddress(78);
cs32	_ICODE_LSA_FCMOVB						= iEncode_pass3_branchAddress(79);
cs32	_ICODE_LSA_FCMOVE						= iEncode_pass3_branchAddress(80);
cs32	_ICODE_LSA_FCMOVBE						= iEncode_pass3_branchAddress(81);
cs32	_ICODE_LSA_FCMOVU						= iEncode_pass3_branchAddress(82);
cs32	_ICODE_LSA_FCMOVNB						= iEncode_pass3_branchAddress(83);
cs32	_ICODE_LSA_FCMOVNE						= iEncode_pass3_branchAddress(84);
cs32	_ICODE_LSA_FCMOVNBE						= iEncode_pass3_branchAddress(85);
cs32	_ICODE_LSA_FCMOVNU						= iEncode_pass3_branchAddress(86);
cs32	_ICODE_LSA_FCOM							= iEncode_pass3_branchAddress(87);
cs32	_ICODE_LSA_FCOMP						= iEncode_pass3_branchAddress(88);
cs32	_ICODE_LSA_FCOMPP						= iEncode_pass3_branchAddress(89);
cs32	_ICODE_LSA_FCOMI						= iEncode_pass3_branchAddress(90);
cs32	_ICODE_LSA_FCOMIP						= iEncode_pass3_branchAddress(91);
cs32	_ICODE_LSA_FUCOMI						= iEncode_pass3_branchAddress(92);
cs32	_ICODE_LSA_FUCOMIP						= iEncode_pass3_branchAddress(93);
cs32	_ICODE_LSA_FCOS							= iEncode_pass3_branchAddress(94);
cs32	_ICODE_LSA_FDECSTP						= iEncode_pass3_branchAddress(95);
cs32	_ICODE_LSA_FDIV							= iEncode_pass3_branchAddress(96);
cs32	_ICODE_LSA_FDIVP						= iEncode_pass3_branchAddress(97);
cs32	_ICODE_LSA_FIDIV						= iEncode_pass3_branchAddress(98);
cs32	_ICODE_LSA_FDIVR						= iEncode_pass3_branchAddress(99);
cs32	_ICODE_LSA_FDIVRP						= iEncode_pass3_branchAddress(100);
cs32	_ICODE_LSA_FIDIVR						= iEncode_pass3_branchAddress(101);
cs32	_ICODE_LSA_FFREE						= iEncode_pass3_branchAddress(102);
cs32	_ICODE_LSA_FICOM						= iEncode_pass3_branchAddress(103);
cs32	_ICODE_LSA_FICOMP						= iEncode_pass3_branchAddress(104);
cs32	_ICODE_LSA_FILD							= iEncode_pass3_branchAddress(105);
cs32	_ICODE_LSA_FINCSTP						= iEncode_pass3_branchAddress(106);
cs32	_ICODE_LSA_FINIT						= iEncode_pass3_branchAddress(107);
cs32	_ICODE_LSA_FIST							= iEncode_pass3_branchAddress(108);
cs32	_ICODE_LSA_FISTP						= iEncode_pass3_branchAddress(109);
cs32	_ICODE_LSA_FLD							= iEncode_pass3_branchAddress(110);
cs32	_ICODE_LSA_FLD1							= iEncode_pass3_branchAddress(111);
cs32	_ICODE_LSA_FLD2T						= iEncode_pass3_branchAddress(112);
cs32	_ICODE_LSA_FLD2E						= iEncode_pass3_branchAddress(113);
cs32	_ICODE_LSA_FLDPI						= iEncode_pass3_branchAddress(114);
cs32	_ICODE_LSA_FLDLG2						= iEncode_pass3_branchAddress(115);
cs32	_ICODE_LSA_FLDN2						= iEncode_pass3_branchAddress(116);
cs32	_ICODE_LSA_FLDZ							= iEncode_pass3_branchAddress(117);
cs32	_ICODE_LSA_FLDCW						= iEncode_pass3_branchAddress(118);
cs32	_ICODE_LSA_FLDENV						= iEncode_pass3_branchAddress(119);
cs32	_ICODE_LSA_FMUL							= iEncode_pass3_branchAddress(120);
cs32	_ICODE_LSA_FMULP						= iEncode_pass3_branchAddress(121);
cs32	_ICODE_LSA_FIMUL						= iEncode_pass3_branchAddress(122);
cs32	_ICODE_LSA_FNOP							= iEncode_pass3_branchAddress(123);
cs32	_ICODE_LSA_FPATAN						= iEncode_pass3_branchAddress(124);
cs32	_ICODE_LSA_FPREM						= iEncode_pass3_branchAddress(125);
cs32	_ICODE_LSA_FPREM1						= iEncode_pass3_branchAddress(126);
cs32	_ICODE_LSA_FPTAN						= iEncode_pass3_branchAddress(127);
cs32	_ICODE_LSA_FRNDINT						= iEncode_pass3_branchAddress(128);
cs32	_ICODE_LSA_FRSTOR						= iEncode_pass3_branchAddress(129);
cs32	_ICODE_LSA_FSAVE						= iEncode_pass3_branchAddress(130);
cs32	_ICODE_LSA_FSCALE						= iEncode_pass3_branchAddress(131);
cs32	_ICODE_LSA_FSIN							= iEncode_pass3_branchAddress(132);
cs32	_ICODE_LSA_FSINCOS						= iEncode_pass3_branchAddress(133);
cs32	_ICODE_LSA_FSQRT						= iEncode_pass3_branchAddress(134);
cs32	_ICODE_LSA_FST							= iEncode_pass3_branchAddress(135);
cs32	_ICODE_LSA_FSTCW						= iEncode_pass3_branchAddress(136);
cs32	_ICODE_LSA_FSTENV						= iEncode_pass3_branchAddress(137);
cs32	_ICODE_LSA_FSTSW						= iEncode_pass3_branchAddress(138);
cs32	_ICODE_LSA_FSUB							= iEncode_pass3_branchAddress(139);
cs32	_ICODE_LSA_FSUBP						= iEncode_pass3_branchAddress(140);
cs32	_ICODE_LSA_FISUB						= iEncode_pass3_branchAddress(141);
cs32	_ICODE_LSA_FSUBR						= iEncode_pass3_branchAddress(142);
cs32	_ICODE_LSA_FSUBRP						= iEncode_pass3_branchAddress(143);
cs32	_ICODE_LSA_FISUBR						= iEncode_pass3_branchAddress(144);
cs32	_ICODE_LSA_FTST							= iEncode_pass3_branchAddress(145);
cs32	_ICODE_LSA_FUCOM						= iEncode_pass3_branchAddress(146);
cs32	_ICODE_LSA_FUCOMP						= iEncode_pass3_branchAddress(147);
cs32	_ICODE_LSA_FUCOMPP						= iEncode_pass3_branchAddress(148);
cs32	_ICODE_LSA_FXAM							= iEncode_pass3_branchAddress(149);
cs32	_ICODE_LSA_FXCH							= iEncode_pass3_branchAddress(150);
cs32	_ICODE_LSA_FXTRACT						= iEncode_pass3_branchAddress(151);
cs32	_ICODE_LSA_FYL2X						= iEncode_pass3_branchAddress(152);
cs32	_ICODE_LSA_FYL2XP1						= iEncode_pass3_branchAddress(153);
cs32	_ICODE_LSA_HLT							= iEncode_pass3_branchAddress(154);
cs32	_ICODE_LSA_IDIV							= iEncode_pass3_branchAddress(155);
cs32	_ICODE_LSA_IMUL							= iEncode_pass3_branchAddress(156);
cs32	_ICODE_LSA_IN							= iEncode_pass3_branchAddress(157);
cs32	_ICODE_LSA_INC							= iEncode_pass3_branchAddress(158);
cs32	_ICODE_LSA_INS							= iEncode_pass3_branchAddress(159);
cs32	_ICODE_LSA_INSB							= iEncode_pass3_branchAddress(160);
cs32	_ICODE_LSA_INSW							= iEncode_pass3_branchAddress(161);
cs32	_ICODE_LSA_INSD							= iEncode_pass3_branchAddress(162);
cs32	_ICODE_LSA_INT3							= iEncode_pass3_branchAddress(163);
cs32	_ICODE_LSA_INT							= iEncode_pass3_branchAddress(164);
cs32	_ICODE_LSA_INTO							= iEncode_pass3_branchAddress(165);
cs32	_ICODE_LSA_INVD							= iEncode_pass3_branchAddress(166);
cs32	_ICODE_LSA_INVLPG						= iEncode_pass3_branchAddress(167);
cs32	_ICODE_LSA_IRET							= iEncode_pass3_branchAddress(168);
cs32	_ICODE_LSA_IRETD						= iEncode_pass3_branchAddress(169);
cs32	_ICODE_LSA_JO							= iEncode_pass3_branchAddress(170);
cs32	_ICODE_LSA_JNO							= iEncode_pass3_branchAddress(171);
cs32	_ICODE_LSA_JB							= iEncode_pass3_branchAddress(172);
cs32	_ICODE_LSA_JNAE							= iEncode_pass3_branchAddress(173);
cs32	_ICODE_LSA_JAE							= iEncode_pass3_branchAddress(174);
cs32	_ICODE_LSA_JNB							= iEncode_pass3_branchAddress(175);
cs32	_ICODE_LSA_JZ							= iEncode_pass3_branchAddress(176);
cs32	_ICODE_LSA_JE							= iEncode_pass3_branchAddress(177);
cs32	_ICODE_LSA_JNZ							= iEncode_pass3_branchAddress(178);
cs32	_ICODE_LSA_JNE							= iEncode_pass3_branchAddress(179);
cs32	_ICODE_LSA_JNA							= iEncode_pass3_branchAddress(180);
cs32	_ICODE_LSA_JBE							= iEncode_pass3_branchAddress(181);
cs32	_ICODE_LSA_JA							= iEncode_pass3_branchAddress(182);
cs32	_ICODE_LSA_JNBE							= iEncode_pass3_branchAddress(183);
cs32	_ICODE_LSA_JS							= iEncode_pass3_branchAddress(184);
cs32	_ICODE_LSA_JNS							= iEncode_pass3_branchAddress(185);
cs32	_ICODE_LSA_JP							= iEncode_pass3_branchAddress(186);
cs32	_ICODE_LSA_JPE							= iEncode_pass3_branchAddress(187);
cs32	_ICODE_LSA_JNP							= iEncode_pass3_branchAddress(188);
cs32	_ICODE_LSA_JPO							= iEncode_pass3_branchAddress(189);
cs32	_ICODE_LSA_JL							= iEncode_pass3_branchAddress(190);
cs32	_ICODE_LSA_JNGE							= iEncode_pass3_branchAddress(191);
cs32	_ICODE_LSA_JGE							= iEncode_pass3_branchAddress(192);
cs32	_ICODE_LSA_JNL							= iEncode_pass3_branchAddress(193);
cs32	_ICODE_LSA_JLE							= iEncode_pass3_branchAddress(194);
cs32	_ICODE_LSA_JNG							= iEncode_pass3_branchAddress(195);
cs32	_ICODE_LSA_JG							= iEncode_pass3_branchAddress(196);
cs32	_ICODE_LSA_JNLE							= iEncode_pass3_branchAddress(197);
cs32	_ICODE_LSA_JMP							= iEncode_pass3_branchAddress(198);
cs32	_ICODE_LSA_LAHF							= iEncode_pass3_branchAddress(199);
cs32	_ICODE_LSA_LAR							= iEncode_pass3_branchAddress(200);
cs32	_ICODE_LSA_LDS							= iEncode_pass3_branchAddress(201);
cs32	_ICODE_LSA_LSS							= iEncode_pass3_branchAddress(202);
cs32	_ICODE_LSA_LES							= iEncode_pass3_branchAddress(203);
cs32	_ICODE_LSA_LFS							= iEncode_pass3_branchAddress(204);
cs32	_ICODE_LSA_LGS							= iEncode_pass3_branchAddress(205);
cs32	_ICODE_LSA_LEA							= iEncode_pass3_branchAddress(206);
cs32	_ICODE_LSA_LEAVE						= iEncode_pass3_branchAddress(207);
cs32	_ICODE_LSA_LGDT							= iEncode_pass3_branchAddress(208);
cs32	_ICODE_LSA_LIDT							= iEncode_pass3_branchAddress(209);
cs32	_ICODE_LSA_LLDT							= iEncode_pass3_branchAddress(210);
cs32	_ICODE_LSA_LMSW							= iEncode_pass3_branchAddress(211);
cs32	_ICODE_LSA_LOCK							= iEncode_pass3_branchAddress(212);
cs32	_ICODE_LSA_LODS							= iEncode_pass3_branchAddress(213);
cs32	_ICODE_LSA_LODSB						= iEncode_pass3_branchAddress(214);
cs32	_ICODE_LSA_LODSW						= iEncode_pass3_branchAddress(215);
cs32	_ICODE_LSA_LODSD						= iEncode_pass3_branchAddress(216);
cs32	_ICODE_LSA_LOOP							= iEncode_pass3_branchAddress(217);
cs32	_ICODE_LSA_LOOPE						= iEncode_pass3_branchAddress(218);
cs32	_ICODE_LSA_LOOPZ						= iEncode_pass3_branchAddress(219);
cs32	_ICODE_LSA_LOOPNE						= iEncode_pass3_branchAddress(220);
cs32	_ICODE_LSA_LOOPNZ						= iEncode_pass3_branchAddress(221);
cs32	_ICODE_LSA_LSL							= iEncode_pass3_branchAddress(222);
cs32	_ICODE_LSA_LTR							= iEncode_pass3_branchAddress(223);
cs32	_ICODE_LSA_MOV							= iEncode_pass3_branchAddress(224);
cs32	_ICODE_LSA_MOVS							= iEncode_pass3_branchAddress(225);
cs32	_ICODE_LSA_MOVSB						= iEncode_pass3_branchAddress(226);
cs32	_ICODE_LSA_MOVSW						= iEncode_pass3_branchAddress(227);
cs32	_ICODE_LSA_MOVSD						= iEncode_pass3_branchAddress(228);
cs32	_ICODE_LSA_MOVSX						= iEncode_pass3_branchAddress(229);
cs32	_ICODE_LSA_MOVZX						= iEncode_pass3_branchAddress(230);
cs32	_ICODE_LSA_MUL							= iEncode_pass3_branchAddress(231);
cs32	_ICODE_LSA_NEG							= iEncode_pass3_branchAddress(232);
cs32	_ICODE_LSA_NOP							= iEncode_pass3_branchAddress(233);
cs32	_ICODE_LSA_NOT							= iEncode_pass3_branchAddress(234);
cs32	_ICODE_LSA_OR							= iEncode_pass3_branchAddress(235);
cs32	_ICODE_LSA_OUT							= iEncode_pass3_branchAddress(236);
cs32	_ICODE_LSA_OUTS							= iEncode_pass3_branchAddress(237);
cs32	_ICODE_LSA_OUTSB						= iEncode_pass3_branchAddress(238);
cs32	_ICODE_LSA_OUTSW						= iEncode_pass3_branchAddress(239);
cs32	_ICODE_LSA_OUTSD						= iEncode_pass3_branchAddress(240);
cs32	_ICODE_LSA_POP							= iEncode_pass3_branchAddress(241);
cs32	_ICODE_LSA_POPA							= iEncode_pass3_branchAddress(242);
cs32	_ICODE_LSA_POPAD						= iEncode_pass3_branchAddress(243);
cs32	_ICODE_LSA_POPF							= iEncode_pass3_branchAddress(244);
cs32	_ICODE_LSA_POPFD						= iEncode_pass3_branchAddress(245);
cs32	_ICODE_LSA_PREFETCH0					= iEncode_pass3_branchAddress(246);
cs32	_ICODE_LSA_PREFETCH1					= iEncode_pass3_branchAddress(247);
cs32	_ICODE_LSA_PREFETCH2					= iEncode_pass3_branchAddress(248);
cs32	_ICODE_LSA_PREFETCHNT					= iEncode_pass3_branchAddress(249);
cs32	_ICODE_LSA_PUSH							= iEncode_pass3_branchAddress(250);
cs32	_ICODE_LSA_PUSHA						= iEncode_pass3_branchAddress(251);
cs32	_ICODE_LSA_PUSHAD						= iEncode_pass3_branchAddress(252);
cs32	_ICODE_LSA_PUSHF						= iEncode_pass3_branchAddress(253);
cs32	_ICODE_LSA_PUSHFD						= iEncode_pass3_branchAddress(254);
cs32	_ICODE_LSA_RCL							= iEncode_pass3_branchAddress(255);
cs32	_ICODE_LSA_RCR							= iEncode_pass3_branchAddress(256);
cs32	_ICODE_LSA_REPNE						= iEncode_pass3_branchAddress(257);
cs32	_ICODE_LSA_REPNZ						= iEncode_pass3_branchAddress(258);
cs32	_ICODE_LSA_REPE							= iEncode_pass3_branchAddress(259);
cs32	_ICODE_LSA_REPZ							= iEncode_pass3_branchAddress(260);
cs32	_ICODE_LSA_ROL							= iEncode_pass3_branchAddress(261);
cs32	_ICODE_LSA_ROR							= iEncode_pass3_branchAddress(262);
cs32	_ICODE_LSA_RDMSR						= iEncode_pass3_branchAddress(263);
cs32	_ICODE_LSA_RDPMC						= iEncode_pass3_branchAddress(264);
cs32	_ICODE_LSA_RDTSC						= iEncode_pass3_branchAddress(265);
cs32	_ICODE_LSA_RET							= iEncode_pass3_branchAddress(266);
cs32	_ICODE_LSA_SAHF							= iEncode_pass3_branchAddress(267);
cs32	_ICODE_LSA_SAR							= iEncode_pass3_branchAddress(268);
cs32	_ICODE_LSA_SHL							= iEncode_pass3_branchAddress(269);
cs32	_ICODE_LSA_SHR							= iEncode_pass3_branchAddress(270);
cs32	_ICODE_LSA_SBB							= iEncode_pass3_branchAddress(271);
cs32	_ICODE_LSA_SCAS							= iEncode_pass3_branchAddress(272);
cs32	_ICODE_LSA_SCASB						= iEncode_pass3_branchAddress(273);
cs32	_ICODE_LSA_SCASW						= iEncode_pass3_branchAddress(274);
cs32	_ICODE_LSA_SCASD						= iEncode_pass3_branchAddress(275);
cs32	_ICODE_LSA_SETO							= iEncode_pass3_branchAddress(276);
cs32	_ICODE_LSA_SETNO						= iEncode_pass3_branchAddress(277);
cs32	_ICODE_LSA_SETB							= iEncode_pass3_branchAddress(278);
cs32	_ICODE_LSA_SETNAE						= iEncode_pass3_branchAddress(279);
cs32	_ICODE_LSA_SETAE						= iEncode_pass3_branchAddress(280);
cs32	_ICODE_LSA_SETNB						= iEncode_pass3_branchAddress(281);
cs32	_ICODE_LSA_SETZ							= iEncode_pass3_branchAddress(282);
cs32	_ICODE_LSA_SETE							= iEncode_pass3_branchAddress(283);
cs32	_ICODE_LSA_SETNZ						= iEncode_pass3_branchAddress(284);
cs32	_ICODE_LSA_SETNE						= iEncode_pass3_branchAddress(285);
cs32	_ICODE_LSA_SETNA						= iEncode_pass3_branchAddress(286);
cs32	_ICODE_LSA_SETBE						= iEncode_pass3_branchAddress(287);
cs32	_ICODE_LSA_SETA							= iEncode_pass3_branchAddress(288);
cs32	_ICODE_LSA_SETNBE						= iEncode_pass3_branchAddress(289);
cs32	_ICODE_LSA_SETS							= iEncode_pass3_branchAddress(290);
cs32	_ICODE_LSA_SETNS						= iEncode_pass3_branchAddress(291);
cs32	_ICODE_LSA_SETP							= iEncode_pass3_branchAddress(292);
cs32	_ICODE_LSA_SETPE						= iEncode_pass3_branchAddress(293);
cs32	_ICODE_LSA_SETNP						= iEncode_pass3_branchAddress(294);
cs32	_ICODE_LSA_SETPO						= iEncode_pass3_branchAddress(295);
cs32	_ICODE_LSA_SETL							= iEncode_pass3_branchAddress(296);
cs32	_ICODE_LSA_SETNGE						= iEncode_pass3_branchAddress(297);
cs32	_ICODE_LSA_SETGE						= iEncode_pass3_branchAddress(298);
cs32	_ICODE_LSA_SETNL						= iEncode_pass3_branchAddress(299);
cs32	_ICODE_LSA_SETLE						= iEncode_pass3_branchAddress(300);
cs32	_ICODE_LSA_SETNG						= iEncode_pass3_branchAddress(301);
cs32	_ICODE_LSA_SETG							= iEncode_pass3_branchAddress(302);
cs32	_ICODE_LSA_SETNLE						= iEncode_pass3_branchAddress(303);
cs32	_ICODE_LSA_SGDT							= iEncode_pass3_branchAddress(304);
cs32	_ICODE_LSA_SIDT							= iEncode_pass3_branchAddress(305);
cs32	_ICODE_LSA_SLDT							= iEncode_pass3_branchAddress(306);
cs32	_ICODE_LSA_SHLD							= iEncode_pass3_branchAddress(307);
cs32	_ICODE_LSA_SHRD							= iEncode_pass3_branchAddress(308);
cs32	_ICODE_LSA_SMSW							= iEncode_pass3_branchAddress(309);
cs32	_ICODE_LSA_STC							= iEncode_pass3_branchAddress(310);
cs32	_ICODE_LSA_STD							= iEncode_pass3_branchAddress(311);
cs32	_ICODE_LSA_STI							= iEncode_pass3_branchAddress(312);
cs32	_ICODE_LSA_STOS							= iEncode_pass3_branchAddress(313);
cs32	_ICODE_LSA_STOSB						= iEncode_pass3_branchAddress(314);
cs32	_ICODE_LSA_STOSW						= iEncode_pass3_branchAddress(315);
cs32	_ICODE_LSA_STOSD						= iEncode_pass3_branchAddress(316);
cs32	_ICODE_LSA_STR							= iEncode_pass3_branchAddress(317);
cs32	_ICODE_LSA_SUB							= iEncode_pass3_branchAddress(318);
cs32	_ICODE_LSA_SYSENTER						= iEncode_pass3_branchAddress(319);
cs32	_ICODE_LSA_SYSEXIT						= iEncode_pass3_branchAddress(320);
cs32	_ICODE_LSA_TEST							= iEncode_pass3_branchAddress(321);
cs32	_ICODE_LSA_UD2							= iEncode_pass3_branchAddress(322);
cs32	_ICODE_LSA_VERR							= iEncode_pass3_branchAddress(323);
cs32	_ICODE_LSA_VERW							= iEncode_pass3_branchAddress(324);
cs32	_ICODE_LSA_FWAIT						= iEncode_pass3_branchAddress(325);
cs32	_ICODE_LSA_WBINVD						= iEncode_pass3_branchAddress(326);
cs32	_ICODE_LSA_WRMSR						= iEncode_pass3_branchAddress(327);
cs32	_ICODE_LSA_XADD							= iEncode_pass3_branchAddress(328);
cs32	_ICODE_LSA_XCHG							= iEncode_pass3_branchAddress(329);
cs32	_ICODE_LSA_XLAT							= iEncode_pass3_branchAddress(330);
cs32	_ICODE_LSA_XLATB						= iEncode_pass3_branchAddress(331);
cs32	_ICODE_LSA_XOR							= iEncode_pass3_branchAddress(332);

#define _LSA_PASS3_CODE_BRANCH_MAX 332

SPass3Func gsPass3_functions[_LSA_PASS3_CODE_BRANCH_MAX];
