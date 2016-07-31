//////////
//
// /libsf/exodus/tools/lsa/pass3/pass3_p.h
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
// Assembly instructions beginning with the letter P.
//
//////




/////////
//
// POP GS -- Pop stack into GS
//
//////
	bool ilsa_pass3_pop(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// POPA -- Pop all r16 registers
//
//////
	bool ilsa_pass3_popa(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// POPAD -- Pop all r32 registers
//
//////
	bool ilsa_pass3_popad(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// POPF -- Pop 16-bit flags
//
//////
	bool ilsa_pass3_popf(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// POPFD -- Pop 32-bit eflags
//
//////
	bool ilsa_pass3_popfd(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// PREFETCHT0 m8 -- Prefetch block around m8 into all caches
//
//////
	bool ilsa_pass3_prefetch0(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// PREFETCHT1 m8 -- Prefetch block around m8 into l1 and above
//
//////
	bool ilsa_pass3_prefetch1(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// PREFETCHT2 m8 -- Prefetch block around m8 into l2 and above
//
//////
	bool ilsa_pass3_prefetch2(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// PREFETCHNT m8 -- Prefetch block around m8 into non-temporal caches
//
//////
	bool ilsa_pass3_prefetchnt(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// PUSH gs -- Push GS
//
//////
	bool ilsa_pass3_push(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// PUSHA -- Push all 16-bit registers
//
//////
	bool ilsa_pass3_pusha(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// PUSHAD -- Push all 32-bit registers
//
//////
	bool ilsa_pass3_pushad(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// PUSHF -- Push 16-bit flags
//
//////
	bool ilsa_pass3_pushf(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// PUSHFD -- Push 32-bit eflags
//
//////
	bool ilsa_pass3_pushfd(SLine* line, SComp* comp)
	{
		return(false);
	}
