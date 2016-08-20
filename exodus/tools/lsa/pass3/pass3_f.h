//////////
//
// /libsf/exodus/tools/lsa/pass3/pass3_f.h
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
// Assembly instructions beginning with the letter F.
//
//////




/////////
//
// F2XM1 -- st0 = 2^(st0 - 1) into st0
//
//////
	bool ilsa_pass3_f2xm1(SLine* line, SComp* comp)
	{
		// Two-byte opcode
		return(ilsa_pass3_common_addOpcodeTwoByte(line, line->firstComp, 0xd9, 0xf0));
	}




/////////
//
// FABS -- st0 = fabs(st0)
//
//////
	bool ilsa_pass3_fabs(SLine* line, SComp* comp)
	{
		// Two-byte opcode
		return(ilsa_pass3_common_addOpcodeTwoByte(line, line->firstComp, 0xd9, 0xe1));
	}




/////////
//
// FADD f32 -- st0 = st0 + f32
//
//////
	bool ilsa_pass3_fadd(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// FADDP stN,st0 -- stN = stN + st0, then pop
//
//////
	bool ilsa_pass3_faddp(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// FIADD s32 -- st0 = st0 + s32
//
//////
	bool ilsa_pass3_fiadd(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// FBLD m80 -- push m80 loaded as binary coded decimal into st0
//
//////
	bool ilsa_pass3_fbld(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// FBSTP m80 -- Store st0 as binary coded decimal into m80, then pop
//
//////
	bool ilsa_pass3_fbstp(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// FCHS -- Complement st0's sign
//
//////
	bool ilsa_pass3_fchs(SLine* line, SComp* comp)
	{
		// Two-byte opcode
		return(ilsa_pass3_common_addOpcodeTwoByte(line, line->firstComp, 0xd9, 0xe0));
	}




/////////
//
// FCLEX -- Clear floating point exceptions after checking for pending unmasked exceptions
//
//////
	bool ilsa_pass3_fclex(SLine* line, SComp* comp)
	{
		// Three-byte opcode
		return(ilsa_pass3_common_addOpcodeThreeByte(line, line->firstComp, 0x9b, 0xdb, 0xe2));
	}




/////////
//
// FNCLEX -- No-wait version of FCLEX
//
//////
	bool ilsa_pass3_fnclex(SLine* line, SComp* comp)
	{
		// Two-byte opcode
		return(ilsa_pass3_common_addOpcodeTwoByte(line, line->firstComp, 0xdb, 0xe2));
	}




/////////
//
// FCMOVB st0,stN -- Move if carry
//
//////
	bool ilsa_pass3_fcmovb(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// FCMOVE st0,stN -- Move if zero
//
//////
	bool ilsa_pass3_fcmove(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// FCMOVBE st0,stN -- Move if carry or zero
//
//////
	bool ilsa_pass3_fcmovbe(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// FCMOVU st0,stN -- Move if parity
//
//////
	bool ilsa_pass3_fcmovu(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// FCMOVNB st0,stN -- Move if not carry
//
//////
	bool ilsa_pass3_fcmovnb(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// FCMOVNE st0,stN -- Move if not zero
//
//////
	bool ilsa_pass3_fcmovne(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// FCMOVNBE st0,stN -- Move if not carry and not zero
//
//////
	bool ilsa_pass3_fcmovnbe(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// FCMOVNU st0,stN -- Move if not parity
//
//////
	bool ilsa_pass3_fcmovnu(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// FCOM f32 -- Compare st0 with f32
//
//////
	bool ilsa_pass3_fcom(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// FCOMP stN -- Compare st0 with stN, then pop
//
//////
	bool ilsa_pass3_fcomp(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// FCOMPP -- Compare st0 with st1, then pop, then pop again
//
//////
	bool ilsa_pass3_fcompp(SLine* line, SComp* comp)
	{
		// Two-byte opcode
		return(ilsa_pass3_common_addOpcodeTwoByte(line, line->firstComp, 0xde, 0xd9));
	}




/////////
//
// FCOMI stN -- Compare st0 with stN, and set eflags
//
//////
	bool ilsa_pass3_fcomi(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// FCOMIP stN -- Compare st0 with stN, and set eflags, then pop
//
//////
	bool ilsa_pass3_fcomip(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// FUCOMI stN -- Compare st0 with stN, check for ordered values, and set eflags
//
//////
	bool ilsa_pass3_fucomi(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// FUCOMIP stN -- Compare st0 with stN, check for ordered values, and set eflags, then pop
//
//////
	bool ilsa_pass3_fucomip(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// FCOS -- st0 = cos(st0)
//
//////
	bool ilsa_pass3_fcos(SLine* line, SComp* comp)
	{
		// Two-byte opcode
		return(ilsa_pass3_common_addOpcodeTwoByte(line, line->firstComp, 0xd9, 0xff));
	}




/////////
//
// FDECSTP -- Decrement the TOP field in the FPU status word
//
//////
	bool ilsa_pass3_fdecstp(SLine* line, SComp* comp)
	{
		// Two-byte opcode
		return(ilsa_pass3_common_addOpcodeTwoByte(line, line->firstComp, 0xd9, 0xf6));
	}




/////////
//
// FDIV f32 -- st0 = st0 / f32
//
//////
	bool ilsa_pass3_fdiv(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// FDIVP stN,st0 -- stN = stN / st0, then pop
//
//////
	bool ilsa_pass3_fdivp(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// FIDIV s32 -- st0 = st0 / s32
//
//////
	bool ilsa_pass3_fidiv(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// FDIVR f64 -- st0 = f64 / st0
//
//////
	bool ilsa_pass3_fdivr(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// FDIVRP stN,st0 -- stN = st0 / stN, then pop
//
//////
	bool ilsa_pass3_fdivrp(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// FIDIVR s32 -- st0 = s32 / st0
//
//////
	bool ilsa_pass3_fidivr(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// FFREE stN -- Set the tag for stN to empty
//
//////
	bool ilsa_pass3_ffree(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// FICOM s32 -- Compare st0 to s32
//
//////
	bool ilsa_pass3_ficom(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// FICOMP s32 -- Compare st0 to s32, then pop
//
//////
	bool ilsa_pass3_ficomp(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// FILD s16 -- Push s16 into st0
//
//////
	bool ilsa_pass3_fild(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// FINCSTP -- Increment the TOP field in the FPU status word
//
//////
	bool ilsa_pass3_fincstp(SLine* line, SComp* comp)
	{
		// Two-byte opcode
		return(ilsa_pass3_common_addOpcodeTwoByte(line, line->firstComp, 0xd9, 0xf7));
	}




/////////
//
// FINIT -- Initialize the FPU
//
//////
	bool ilsa_pass3_finit(SLine* line, SComp* comp)
	{
		// Three-byte opcode
		return(ilsa_pass3_common_addOpcodeThreeByte(line, line->firstComp, 0x9b, 0xdb, 0xe3));
	}




/////////
//
// FIST m32int -- Store st0 to memory as s32
//
//////
	bool ilsa_pass3_fist(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// FISTP m64int -- Store st0 to memory as s64, then pop
//
//////
	bool ilsa_pass3_fistp(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// FLD stN -- Push stN into st0
//
//////
	bool ilsa_pass3_fld(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// FLD1 -- Push +1.0 into st0
//
//////
	bool ilsa_pass3_fld1(SLine* line, SComp* comp)
	{
		// Two-byte opcode
		return(ilsa_pass3_common_addOpcodeTwoByte(line, line->firstComp, 0xd9, 0xe8));
	}




/////////
//
// FLDL2T -- Push log2(10) into st0
//
//////
	bool ilsa_pass3_fld2t(SLine* line, SComp* comp)
	{
		// Two-byte opcode
		return(ilsa_pass3_common_addOpcodeTwoByte(line, line->firstComp, 0xd9, 0xe9));
	}




/////////
//
// FLDL2E -- Push log2(e) into st0
//
//////
	bool ilsa_pass3_fldl2e(SLine* line, SComp* comp)
	{
		// Two-byte opcode
		return(ilsa_pass3_common_addOpcodeTwoByte(line, line->firstComp, 0xd9, 0xea));
	}




/////////
//
// FLDPI -- Push pi into st0
//
//////
	bool ilsa_pass3_fldpi(SLine* line, SComp* comp)
	{
		// Two-byte opcode
		return(ilsa_pass3_common_addOpcodeTwoByte(line, line->firstComp, 0xd9, 0xeb));
	}




/////////
//
// FLDLG2 -- Push log10(2) into st0
//
//////
	bool ilsa_pass3_fldlg2(SLine* line, SComp* comp)
	{
		// Two-byte opcode
		return(ilsa_pass3_common_addOpcodeTwoByte(line, line->firstComp, 0xd9, 0xec));
	}




/////////
//
// FLDLN2 -- Push loge(2) into st0
//
//////
	bool ilsa_pass3_fldn2(SLine* line, SComp* comp)
	{
		// Two-byte opcode
		return(ilsa_pass3_common_addOpcodeTwoByte(line, line->firstComp, 0xd9, 0xed));
	}




/////////
//
// FLDZ -- Push +0.0 into st0
//
//////
	bool ilsa_pass3_fldz(SLine* line, SComp* comp)
	{
		// Two-byte opcode
		return(ilsa_pass3_common_addOpcodeTwoByte(line, line->firstComp, 0xd9, 0xee));
	}




/////////
//
// FLDCW u16 -- Load u16 into FPU control word
//
//////
	bool ilsa_pass3_fldcw(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// FLDENV m14/m28 -- Load 14-byte or 28-byte into environment
//
//////
	bool ilsa_pass3_fldenv(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// FMUL stN,st0 -- stN = stN * st0
//
//////
	bool ilsa_pass3_fmul(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// FMULP stN,st0 -- stN = stN * st0, then pop
//
//////
	bool ilsa_pass3_fmulp(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// FIMUL m32int -- st0 = st0 * s32
//
//////
	bool ilsa_pass3_fimul(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// FNOP -- No operation
//
//////
	bool ilsa_pass3_fnop(SLine* line, SComp* comp)
	{
		// Two-byte opcode
		return(ilsa_pass3_common_addOpcodeTwoByte(line, line->firstComp, 0xd9, 0xd0));
	}




/////////
//
// FPATAN -- st1 = arctan(st1 / st0), then pop
//
//////
	bool ilsa_pass3_fpatan(SLine* line, SComp* comp)
	{
		// Two-byte opcode
		return(ilsa_pass3_common_addOpcodeTwoByte(line, line->firstComp, 0xd9, 0xf3));
	}




/////////
//
// FPREM -- st0 = st0 % st1
//
//////
	bool ilsa_pass3_fprem(SLine* line, SComp* comp)
	{
		// Two-byte opcode
		return(ilsa_pass3_common_addOpcodeTwoByte(line, line->firstComp, 0xd9, 0xf8));
	}




/////////
//
// FPREM1 -- st0 = IEEE st0 % st1
//
//////
	bool ilsa_pass3_fprem1(SLine* line, SComp* comp)
	{
		// Two-byte opcode
		return(ilsa_pass3_common_addOpcodeTwoByte(line, line->firstComp, 0xd9, 0xf5));
	}




/////////
//
// FPTAN -- st0 = tan(st0), then push 1 into st0
//
//////
	bool ilsa_pass3_fptan(SLine* line, SComp* comp)
	{
		// Two-byte opcode
		return(ilsa_pass3_common_addOpcodeTwoByte(line, line->firstComp, 0xd9, 0xf2));
	}




/////////
//
// FRNDINT -- st0 = int(st0)
//
//////
	bool ilsa_pass3_frndint(SLine* line, SComp* comp)
	{
		// Two-byte opcode
		return(ilsa_pass3_common_addOpcodeTwoByte(line, line->firstComp, 0xd9, 0xfc));
	}




/////////
//
// FRSTOR m94/m108 -- Load FPU state from a 94 or 108 byte block
//
//////
	bool ilsa_pass3_frstor(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// FSAVE m94/m108 -- Store the FPU state to a 94 or 108 byte block
//
//////
	bool ilsa_pass3_fsave(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// FSCALE -- st0 = 2^stN
//
//////
	bool ilsa_pass3_fscale(SLine* line, SComp* comp)
	{
		// Two-byte opcode
		return(ilsa_pass3_common_addOpcodeTwoByte(line, line->firstComp, 0xd9, 0xfd));
	}




/////////
//
// FSIN -- st0 = sin(st0)
//
//////
	bool ilsa_pass3_fsin(SLine* line, SComp* comp)
	{
		// Two-byte opcode
		return(ilsa_pass3_common_addOpcodeTwoByte(line, line->firstComp, 0xd9, 0xfe));
	}




/////////
//
// FSINCOS -- t = cos(st0), st0 = sin(st0), then push t into st0
//
//////
	bool ilsa_pass3_fsincos(SLine* line, SComp* comp)
	{
		// Two-byte opcode
		return(ilsa_pass3_common_addOpcodeTwoByte(line, line->firstComp, 0xd9, 0xfb));
	}




/////////
//
// FSQRT -- st0 = sqrt(st0)
//
//////
	bool ilsa_pass3_fsqrt(SLine* line, SComp* comp)
	{
		// Two-byte opcode
		return(ilsa_pass3_common_addOpcodeTwoByte(line, line->firstComp, 0xd9, 0xfa));
	}




/////////
//
// FST stN -- Copy st0 to stN, then pop
//
//////
	bool ilsa_pass3_fst(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// FSTCW m16 -- Copy FPU status word to m16
//
//////
	bool ilsa_pass3_fstcw(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// FSTENV m14/m28 -- Copy FPU environment to 14-byte or 28-byte block
//
//////
	bool ilsa_pass3_fstenv(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// FSTSW ax -- Copy FPU status word to ax
//
//////
	bool ilsa_pass3_fstsw(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// FSUB stN,st0 -- stN = stN - st0
//
//////
	bool ilsa_pass3_fsub(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// FSUBP stN,st0 -- stN = stN - st0, then pop
//
//////
	bool ilsa_pass3_fsubp(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// FISUB s16 -- st0 = st0 - s16
//
//////
	bool ilsa_pass3_fisub(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// FSUBR stN,st0 -- stN = st0 - stN
//
//////
	bool ilsa_pass3_fsubr(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// FSUBRP stN,st0 -- stN = st0 - stN, then pop
//
//////
	bool ilsa_pass3_fsubrp(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// FISUBR s16 -- st0 = s16 - st0
//
//////
	bool ilsa_pass3_fisubr(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// FTST -- Compare st0 to +0.0
//
//////
	bool ilsa_pass3_ftst(SLine* line, SComp* comp)
	{
		// Two-byte opcode
		return(ilsa_pass3_common_addOpcodeTwoByte(line, line->firstComp, 0xd9, 0xe4));
	}




/////////
//
// FUCOM stN -- Compare st0 to stN
//
//////
	bool ilsa_pass3_fucom(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// FUCOMP stN -- Compare st0 to stN, then pop
//
//////
	bool ilsa_pass3_fucomp(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// FUCOMPP -- Compare st0 to st1, then pop
//
//////
	bool ilsa_pass3_fucompp(SLine* line, SComp* comp)
	{
		// Two-byte opcode
		return(ilsa_pass3_common_addOpcodeTwoByte(line, line->firstComp, 0xd9, 0xe9));
	}




//////////
//
// FWAIT -- Check pending unmasked floating-point exceptions
//
//////
	bool ilsa_pass3_fwait(SLine* line, SComp* comp)
	{
		// Simple opcode
		return(ilsa_pass3_common_addOpcodeByte(line, comp, 0x9b));
	}




/////////
//
// FXAM -- Classify st0
//
//////
	bool ilsa_pass3_fxam(SLine* line, SComp* comp)
	{
		// Two-byte opcode
		return(ilsa_pass3_common_addOpcodeTwoByte(line, line->firstComp, 0xd9, 0xe5));
	}




/////////
//
// FXCH stN -- Exchange st0 and stN
//
//////
	bool ilsa_pass3_fxch(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// FXTRACT -- t = st0's exponent, st0 = st0's significand, then push t into st0
//
//////
	bool ilsa_pass3_fxtract(SLine* line, SComp* comp)
	{
		// Two-byte opcode
		return(ilsa_pass3_common_addOpcodeTwoByte(line, line->firstComp, 0xd9, 0xf4));
	}




/////////
//
// FYL2X -- st1 = st1 * log2(st0), then pop
//
//////
	bool ilsa_pass3_fyl2x(SLine* line, SComp* comp)
	{
		// Two-byte opcode
		return(ilsa_pass3_common_addOpcodeTwoByte(line, line->firstComp, 0xd9, 0xf1));
	}




/////////
//
// FYL2XP1 -- st1 = st1 * log2(st0 + 1.0), then pop
//
//////
	bool ilsa_pass3_fyl2xp1(SLine* line, SComp* comp)
	{
		// Two-byte opcode
		return(ilsa_pass3_common_addOpcodeTwoByte(line, line->firstComp, 0xd9, 0xf9));
	}
