//////////
//
// /libsf/exodus/tools/lsa/pass3/pass3_c.h
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
// Assembly instructions beginning with the letter C.
//
//////




/////////
//
// CALL m16:32 -- Call far, absolute indirect address in m16:32
//
//////
	bool ilsa_pass3_call(SLine* line)
	{
		return(false);
	}




/////////
//
// CBW -- Sign-extend al to ax
//
//////
	bool ilsa_pass3_cbw(SLine* line)
	{
		return(false);
	}




/////////
//
// CWDE -- Sign-extend ax to eax
//
//////
	bool ilsa_pass3_cwde(SLine* line)
	{
		return(false);
	}




/////////
//
// CLC -- Clear carry
//
//////
	bool ilsa_pass3_clc(SLine* line)
	{
		return(false);
	}




/////////
//
// CLD -- Clear direction
//
//////
	bool ilsa_pass3_cld(SLine* line)
	{
		return(false);
	}




/////////
//
// CLI -- Clear interrupt
//
//////
	bool ilsa_pass3_cli(SLine* line)
	{
		return(false);
	}




/////////
//
// CLTS -- Clear task-switched flag in CR0
//
//////
	bool ilsa_pass3_clts(SLine* line)
	{
		return(false);
	}




/////////
//
// CMOVcc r32,rm32 -- Move if cc flag condition is true
//
//////
	bool ilsa_pass3_cmovcc(SLine* line)
	{
		switch (line->firstComp->iCode)
		{
			case iDecode_pass3_branchAddress(_ICODE_LSA_CMOVO):
				// CMOVO
				break;
			case iDecode_pass3_branchAddress(_ICODE_LSA_CMOVNO):
				// CMOVNO
				break;
			case iDecode_pass3_branchAddress(_ICODE_LSA_CMOVB):
				// CMOVB
				break;
			case iDecode_pass3_branchAddress(_ICODE_LSA_CMOVNAE):
				// CMOVNAE
				break;
			case iDecode_pass3_branchAddress(_ICODE_LSA_CMOVAE):
				// CMOVAE
				break;
			case iDecode_pass3_branchAddress(_ICODE_LSA_CMOVNB):
				// CMOVNB
				break;
			case iDecode_pass3_branchAddress(_ICODE_LSA_CMOVZ):
				// CMOVZ
				break;
			case iDecode_pass3_branchAddress(_ICODE_LSA_CMOVE):
				// CMOVE
				break;
			case iDecode_pass3_branchAddress(_ICODE_LSA_CMOVNZ):
				// CMOVNZ
				break;
			case iDecode_pass3_branchAddress(_ICODE_LSA_CMOVNE):
				// CMOVNE
				break;
			case iDecode_pass3_branchAddress(_ICODE_LSA_CMOVNA):
				// CMOVNA
				break;
			case iDecode_pass3_branchAddress(_ICODE_LSA_CMOVBE):
				// CMOVBE
				break;
			case iDecode_pass3_branchAddress(_ICODE_LSA_CMOVA):
				// CMOVA
				break;
			case iDecode_pass3_branchAddress(_ICODE_LSA_CMOVNBE):
				// CMOVNBE
				break;
			case iDecode_pass3_branchAddress(_ICODE_LSA_CMOVS):
				// CMOVS
				break;
			case iDecode_pass3_branchAddress(_ICODE_LSA_CMOVNS):
				// CMOVNS
				break;
			case iDecode_pass3_branchAddress(_ICODE_LSA_CMOVP):
				// CMOVP
				break;
			case iDecode_pass3_branchAddress(_ICODE_LSA_CMOVPE):
				// CMOVPE
				break;
			case iDecode_pass3_branchAddress(_ICODE_LSA_CMOVNP):
				// CMOVNP
				break;
			case iDecode_pass3_branchAddress(_ICODE_LSA_CMOVPO):
				// CMOVPO
				break;
			case iDecode_pass3_branchAddress(_ICODE_LSA_CMOVL):
				// CMOVL
				break;
			case iDecode_pass3_branchAddress(_ICODE_LSA_CMOVNGE):
				// CMOVNGE
				break;
			case iDecode_pass3_branchAddress(_ICODE_LSA_CMOVGE):
				// CMOVGE
				break;
			case iDecode_pass3_branchAddress(_ICODE_LSA_CMOVNL):
				// CMOVNL
				break;
			case iDecode_pass3_branchAddress(_ICODE_LSA_CMOVLE):
				// CMOVLE
				break;
			case iDecode_pass3_branchAddress(_ICODE_LSA_CMOVNG):
				// CMOVNG
				break;
			case iDecode_pass3_branchAddress(_ICODE_LSA_CMOVG):
				// CMOVG
				break;
			case iDecode_pass3_branchAddress(_ICODE_LSA_CMOVNLE):
				// CMOVNLE
				break;
		}

		return(false);
	}




/////////
//
// CMP al,imm8 -- imm8  al
//
//////
	bool ilsa_pass3_cmp(SLine* line)
	{
		return(false);
	}




/////////
//
// CMPSB -- Compare byte in ds:[esi] to es:[edi]
//
//////
	bool ilsa_pass3_cmpsb(SLine* line)
	{
		return(false);
	}




/////////
//
// CMPSW -- Compare word in ds:[esi] to es:[edi]
//
//////
	bool ilsa_pass3_cmpsw(SLine* line)
	{
		return(false);
	}




/////////
//
// CMPSD -- Compare dword in ds:[esi] to es:[edi]
//
//////
	bool ilsa_pass3_cmpsd(SLine* line)
	{
		return(false);
	}




/////////
//
// CMPXCHG r/m32,r32 -- Compare eax with r/m16, if equal set zero and load r32 into r/m32, if not equal clear zero and load r/m32 into eax
//
//////
	bool ilsa_pass3_cmpxchg(SLine* line)
	{
		return(false);
	}




/////////
//
// CMPXCHG8B m64 -- Compare edx:eax with m64, if equal set zero and load ECX:EBX into m64, if not equal clear zero and load m64 into edx:eax
//
//////
	bool ilsa_pass3_cmpxchg8b(SLine* line)
	{
		return(false);
	}




/////////
//
// CPUID -- Based on EAX, load processor information into registers
//
//////
	bool ilsa_pass3_cpuid(SLine* line)
	{
		return(false);
	}




/////////
//
// CDW -- Sign-extend ax into dx:ax
//
//////
	bool ilsa_pass3_cdw(SLine* line)
	{
		return(false);
	}




/////////
//
// CDQ -- Sign-extend eax into edx:eax
//
//////
	bool ilsa_pass3_cdq(SLine* line)
	{
		return(false);
	}
