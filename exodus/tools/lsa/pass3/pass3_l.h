//////////
//
// /libsf/exodus/tools/lsa/pass3/pass3_l.h
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
// Assembly instructions beginning with the letter L.
//
//////




/////////
//
// LAHF -- ah = eflags.sf:zf:0:af:0:pf:1:cf
//
//////
	bool ilsa_pass3_lahf(SLine* line, SComp* comp)
	{
		// Simple opcode
		return(ilsa_pass3_common_addOpcodeByte(line, comp, 0x9f));
	}




/////////
//
// LAR r32,r/m32 -- r32 = r/m32 & 00fxff00h
//
//////
	bool ilsa_pass3_lar(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// LDS r32,m16:32 -- Load DS:r32 indirect from far pointer
//
//////
	bool ilsa_pass3_lds(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// LSS r32,m16:32 -- Load SS:r32 indirect from far pointer
//
//////
	bool ilsa_pass3_lss(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// LES r32,m16:32 -- Load ES:r32 indirect from far pointer
//
//////
	bool ilsa_pass3_les(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// LFS r32,m16:32 -- Load FS:r32 indirect from far pointer
//
//////
	bool ilsa_pass3_lfs(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// LGS r32,m16:32 -- Load GS:r32 indirect from far pointer
//
//////
	bool ilsa_pass3_lgs(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// LEA r32,m -- Store effective address for m in r32
//
//////
	bool ilsa_pass3_lea(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// LEAVE -- esp = ebp, then pop ebp
//
//////
	bool ilsa_pass3_leave(SLine* line, SComp* comp)
	{
		// Simple opcode
		return(ilsa_pass3_common_addOpcodeByte(line, comp, 0xc9));
	}




/////////
//
// LGDT m16&32 -- Load m into GDTR
//
//////
	bool ilsa_pass3_lgdt(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// LIDT m16&32 -- Load m into IDTR
//
//////
	bool ilsa_pass3_lidt(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// LLDT r/m16 -- Load selector into LDTR
//
//////
	bool ilsa_pass3_lldt(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// LMSW r/m16 -- Loads r/m16 into bits cr0
//
//////
	bool ilsa_pass3_lmsw(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// LOCK -- Prefix for other instructions, locks system bus
//
//////
	bool ilsa_pass3_lock(SLine* line, SComp* comp)
	{
		// Store the lock prefix
		if (!iilsa_lineData_lock(line))
			return(false);

		// Mark the component complete
		ilsa_markCompCompleted(comp);

		// If there's a component after lock, we parse from that point on as well
		if ((comp = iComps_Nth_lineOnly(comp)))
			return(iilsa_pass3_decode_line(line, comp));

		// Indicate success
		return(true);
	}




/////////
//
// LODS m32 -- Load dword from ds:[e/si] into eax
//
//////
	bool ilsa_pass3_lods(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// LODSB -- Shorthand for LODS m8
//
//////
	bool ilsa_pass3_lodsb(SLine* line, SComp* comp)
	{
		// Simple opcode
		return(ilsa_pass3_common_addOpcodeByte(line, comp, 0xac));
	}




/////////
//
// LODSW -- Shorthand for LODS m16
//
//////
	bool ilsa_pass3_lodsw(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// LODSD -- Shorthand for LODS m32
//
//////
	bool ilsa_pass3_lodsd(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// LOOP imm8 -- Decrement count, jump short if count != 0
//
//////
	bool ilsa_pass3_loop(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// LOOPE imm8 -- Decrement count, jump short if count != 0 and zero
//
//////
	bool ilsa_pass3_loope(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// LOOPZ imm8 -- Synonym for LOOPE
//
//////
	bool ilsa_pass3_loopz(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// LOOPNE imm8 -- Decrement count, jump short if count != 0 and !zero
//
//////
	bool ilsa_pass3_loopne(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// LOOPNZ imm8 -- Synonym for LOOPNE
//
//////
	bool ilsa_pass3_loopnz(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// LSL r32,r/m32 -- r32 = segment_limit(r/m32)
//
//////
	bool ilsa_pass3_lsl(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// LTR r/m16 -- Load r/m16 into TR
//
//////
	bool ilsa_pass3_ltr(SLine* line, SComp* comp)
	{
		return(false);
	}
