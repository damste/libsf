//////////
//
// /libsf/exodus/tools/lsa/pass3/pass3_s.h
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
// Assembly instructions beginning with the letter S.
//
//////




/////////
//
// SAHF -- Store ah into flags
//
//////
	bool ilsa_pass3_sahf(SLine* line, SComp* comp)
	{
		// Simple opcode
		return(ilsa_pass3_common_addOpcodeByte(line, comp, 0x9e));
	}




/////////
//
// SAR r/m32,imm8 -- Signed divide r/m32 by imm8 times
//
//////
	bool ilsa_pass3_sar(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// SHL r/m32,imm8 -- Shift left r/m32 imm8 times
//
//////
	bool ilsa_pass3_shl(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// SHR r/m32,imm8 -- Shift right r/m32 imm8 times
//
//////
	bool ilsa_pass3_shr(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// SBB r32,r/m32 -- r/m32 from r32
//
//////
	bool ilsa_pass3_sbb(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// SCAS m32 -- Compare eax with dword in es:[e/di]
//
//////
	bool ilsa_pass3_scas(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// SCASB -- Shorthand for SCAS m8
//
//////
	bool ilsa_pass3_scasb(SLine* line, SComp* comp)
	{
		// Simple opcode
		return(ilsa_pass3_common_addOpcodeByte(line, comp, 0xae));
	}




/////////
//
// SCASW -- Shorthand for SCAS m16
//
//////
	bool ilsa_pass3_scasw(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// SCASD -- Shorthand for SCAS m32
//
//////
	bool ilsa_pass3_scasd(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// SETcc r/m8 -- Set byte if cc condition is met
//
//////
	bool ilsa_pass3_setcc(SLine* line, SComp* comp)
	{
		switch (line->firstComp->iCode)
		{
			case iDecode_pass3_branchAddress(_ICODE_LSA_SETO):
			// SETO
				break;
			case iDecode_pass3_branchAddress(_ICODE_LSA_SETNO):
			// SETNO
				break;
			case iDecode_pass3_branchAddress(_ICODE_LSA_SETB):
			// SETB
				break;
			case iDecode_pass3_branchAddress(_ICODE_LSA_SETNAE):
			// SETNAE
				break;
			case iDecode_pass3_branchAddress(_ICODE_LSA_SETAE):
			// SETAE
				break;
			case iDecode_pass3_branchAddress(_ICODE_LSA_SETNB):
			// SETNB
				break;
			case iDecode_pass3_branchAddress(_ICODE_LSA_SETZ):
			// SETZ
				break;
			case iDecode_pass3_branchAddress(_ICODE_LSA_SETE):
			// SETE
				break;
			case iDecode_pass3_branchAddress(_ICODE_LSA_SETNZ):
			// SETNZ
				break;
			case iDecode_pass3_branchAddress(_ICODE_LSA_SETNE):
			// SETNE
				break;
			case iDecode_pass3_branchAddress(_ICODE_LSA_SETNA):
			// SETNA
				break;
			case iDecode_pass3_branchAddress(_ICODE_LSA_SETBE):
			// SETBE
				break;
			case iDecode_pass3_branchAddress(_ICODE_LSA_SETA):
			// SETA
				break;
			case iDecode_pass3_branchAddress(_ICODE_LSA_SETNBE):
			// SETNBE
				break;
			case iDecode_pass3_branchAddress(_ICODE_LSA_SETS):
			// SETS
				break;
			case iDecode_pass3_branchAddress(_ICODE_LSA_SETNS):
			// SETNS
				break;
			case iDecode_pass3_branchAddress(_ICODE_LSA_SETP):
			// SETP
				break;
			case iDecode_pass3_branchAddress(_ICODE_LSA_SETPE):
			// SETPE
				break;
			case iDecode_pass3_branchAddress(_ICODE_LSA_SETNP):
			// SETNP
				break;
			case iDecode_pass3_branchAddress(_ICODE_LSA_SETPO):
			// SETPO
				break;
			case iDecode_pass3_branchAddress(_ICODE_LSA_SETL):
			// SETL
				break;
			case iDecode_pass3_branchAddress(_ICODE_LSA_SETNGE):
			// SETNGE
				break;
			case iDecode_pass3_branchAddress(_ICODE_LSA_SETGE):
			// SETGE
				break;
			case iDecode_pass3_branchAddress(_ICODE_LSA_SETNL):
			// SETNL
				break;
			case iDecode_pass3_branchAddress(_ICODE_LSA_SETLE):
			// SETLE
				break;
			case iDecode_pass3_branchAddress(_ICODE_LSA_SETNG):
			// SETNG
				break;
			case iDecode_pass3_branchAddress(_ICODE_LSA_SETG):
			// SETG
				break;
			case iDecode_pass3_branchAddress(_ICODE_LSA_SETNLE):
			// SETNLE
				break;
		}

		return(false);
	}




/////////
//
// SGDT m48 -- Store GDTR to m48
//
//////
	bool ilsa_pass3_sgdt(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// SIDT m48 -- Store IDTR to m48
//
//////
	bool ilsa_pass3_sidt(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// SLDT r/m16 -- Store LDTR to r/m16
//
//////
	bool ilsa_pass3_sldt(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// SHLD r/m32,r32,cl -- Shift r/m32 left cl places, shifting in bits from r32
//
//////
	bool ilsa_pass3_shld(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// SHRD r/m32,r32,cl -- Shift r/m32 right cl places, shifting in bits from r32
//
//////
	bool ilsa_pass3_shrd(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// SMSW r32/m16 -- Store machine status word to r32/m16
//
//////
	bool ilsa_pass3_smsw(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// STC -- Set carry
//
//////
	bool ilsa_pass3_stc(SLine* line, SComp* comp)
	{
		// Simple opcode
		return(ilsa_pass3_common_addOpcodeByte(line, comp, 0xf9));
	}




/////////
//
// STD -- Set direction
//
//////
	bool ilsa_pass3_std(SLine* line, SComp* comp)
	{
		// Simple opcode
		return(ilsa_pass3_common_addOpcodeByte(line, comp, 0xfd));
	}




/////////
//
// STI -- Set interrupt
//
//////
	bool ilsa_pass3_sti(SLine* line, SComp* comp)
	{
		// Simple opcode
		return(ilsa_pass3_common_addOpcodeByte(line, comp, 0xfb));
	}




/////////
//
// STOS m32 -- Store eax into es:[e/di]
//
//////
	bool ilsa_pass3_stos(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// STOSB -- Shorthand for STOS m8
//
//////
	bool ilsa_pass3_stosb(SLine* line, SComp* comp)
	{
		// Simple opcode
		return(ilsa_pass3_common_addOpcodeByte(line, comp, 0xaa));
	}




/////////
//
// STOSW -- Shorthand for STOS m16
//
//////
	bool ilsa_pass3_stosw(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// STOSD -- Shorthand for STOS m32
//
//////
	bool ilsa_pass3_stosd(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// STR r/m16 -- Stores segment selector from TR in r/m16
//
//////
	bool ilsa_pass3_str(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// SUB r32,r/m32 -- r/m32 from r32
//
//////
	bool ilsa_pass3_sub(SLine* line, SComp* comp)
	{
		return(false);
	}




/////////
//
// SYSENTER -- Fast system entry
//
//////
	bool ilsa_pass3_sysenter(SLine* line, SComp* comp)
	{
		// Two-byte opcode
		return(ilsa_pass3_common_addOpcodeTwoByte(line, line->firstComp, 0x0f, 0x34));
	}




/////////
//
// SYSEXIT -- Fast system exit
//
//////
	bool ilsa_pass3_sysexit(SLine* line, SComp* comp)
	{
		// Two-byte opcode
		return(ilsa_pass3_common_addOpcodeTwoByte(line, line->firstComp, 0x0f, 0x35));
	}
