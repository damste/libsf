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
	#include "pass3\pass3_a.h"
	#include "pass3\pass3_b.h"
	#include "pass3\pass3_c.h"
	#include "pass3\pass3_d_e.h"
	#include "pass3\pass3_f.h"
	#include "pass3\pass3_h_i.h"
	#include "pass3\pass3_j.h"
	#include "pass3\pass3_l.h"
	#include "pass3\pass3_m.h"
	#include "pass3\pass3_n_o.h"
	#include "pass3\pass3_p.h"
	#include "pass3\pass3_r.h"
	#include "pass3\pass3_s.h"
	#include "pass3\pass3_t_u_v_w.h"
	#include "pass3\pass3_x.h"




//////////
//
// pass3.cpp -- Mnemonic parsing
//
//////
	void ilsa_pass3(void)
	{
		SLine* line;


		// Populate and validate the gsPass3_functions for rapid dispatch to handlers
		iilsa_pass3_init();

		// Iterate through every line
		for (line = cmdLine.file->firstLine; line; line = line->ll.nextLine)
			iilsa_pass3_decode_line(line);
	}




//////////
//
// Called to decode the indicated line beginning at the indicated component (or line->firstComp if not provided)
//
//////
	bool iilsa_pass3_decode_line(SLine* line, SComp* comp)
	{
		// Make sure our environment is sane
		if (line && (comp || (comp = line->firstComp)))
		{
			// Only applying to uncompleted lines
			if (!ilsa_status_line_isCompleted(line) && comp && !ilsa_status_comp_isCompleted(comp))
				return(iilsa_pass3_decode_compsRight(line, comp));
		}

		// If we get here, did not process
		return(ilsa_status_line_isCompleted(line));
	}




//////////
//
// Called to decode from the indicated component right on the indicated line
//
//////
	bool iilsa_pass3_decode_compsRight(SLine* line, SComp* comp)
	{
		u32 lniCodeBranch;


		// Grab the branch address
		lniCodeBranch = iDecode_pass3_branchAddress(comp->iCode);

		// If it's valid for this pass, parse it
		if (lniCodeBranch >= _LSA_PASS3_CODE_BRANCH_MIN && lniCodeBranch <= _LSA_PASS3_CODE_BRANCH_MAX)
		{
			// If we're successful, check the line and mark it completed
			if (gsPass3_functions[lniCodeBranch].func(line, comp))
			{
				// Processed
				ilsa_status_markLineStatus_ifAllCompsHave(line);

				// Indicate success
				return(true);
			}
		}
		//else Not a line for us to decode
		return(false);
	}




//////////
//
// Common function for simple single-opcode instructions
//
//////
	bool ilsa_pass3_common_addOpcodeByte(SLine* line, SComp* comp, u8 opcodeByte)
	{
		// Store the opcode
		if (!iilsa_lineData_addOpcodeByte(line, opcodeByte))
			return(false);

		// Mark the component complete
		ilsa_markCompCompleted(comp);

		// Indicate success
		return(true);
	}




//////////
//
// Common function for simple two-opcode instructions
//
//////
	bool ilsa_pass3_common_addOpcodeTwoByte(SLine* line, SComp* comp, u8 opcodeByte1, u8 opcodeByte2)
	{
		// Store opcode 1
		if (iilsa_lineData_addOpcodeByte(line, opcodeByte1))
		{
			// Store opcode 2
			if (iilsa_lineData_addOpcodeByte(line, opcodeByte2))
			{
				// Mark the component complete
				ilsa_markCompCompleted(comp);

				// Indicate success
				return(true);
			}
		}

		// Indicate failure
		return(false);
	}




//////////
//
// Called to extract an imm8 parameter.
// Note:  By this point in the calculation, all symbols will have been swapped out with their equivalent fundamental values
//
//////
	bool ilsa_pass3_extract_imm8(SComp* comp, u8* imm8)
	{
		bool		llValid;
		s8			buffer[64];
		SNode*		node;
		SCallback*	cb;
		union {
			u32		lnValue;
			u8		_imm8;
		};


		// Make sure our environment is sane
		if (comp && comp->line)
		{
			// Entered to allow structured exit
			switch (comp->iCode)
			{
				case _ICODE_NUMERIC:
					// Grab the value
					lnValue = iComps_getAs_s32(comp);
					break;

				case _ICODE_NUMERICALPHA:
					// It's likely 0xfedcba9876543210, 0o76543210, 0g3210, 0y10
					lnValue = iComps_getAs_u32_byBase(comp, &llValid);
					if (!llValid)
					{
						// Generate and report the error
imm8_error:
						sprintf(buffer, "Error %%d [%d,%d]: '%s' %%s",  comp->line->lineNumber, comp->start);
						iilsa_error(_LSA_ERROR_IMMEDIATE_VALUE_ERROR, buffer, comp->line);
						return(false);
					}
					break;

				default:
					// It's likely an expression
					memset(&cb, 0, sizeof(cb));
					cb->_func = (uptr)&iilsa_pass3_extract_imm8__callback;
					node = iComps_parseExpression(comp, NULL, 1, cb);
					if (!node)
						goto imm8_error;

					// Compute the result
					lnValue = iComps_computeExpressionAs_u32(node, true, &llValid);
					if (!llValid)
					{
						sprintf(buffer, "Error %%d [%d,%d]: '%s' %%s",  comp->line->lineNumber, comp->start);
						iilsa_error(_LSA_ERROR_IMMEDIATE_VALUE_NOT_CONSTANT, buffer, comp->line);
						return(false);
					}
					break;
			}

			// Make sure our value is correct
			if (lnValue <= 255 || lnValue >= -128)
			{
				// Store the value
				*imm8 = _imm8;

				// Indicate success
				return(true);

			}

			// If we get here, the value is out of range
			// Generate and report the error
			sprintf(buffer, "Error %%d [%d,%d]: '%s' %%s",  comp->line->lineNumber, comp->start);
			iilsa_error(_LSA_ERROR_IMMEDIATE_VALUE_OUT_OF_RANGE, buffer, comp->line);
			return(false);
		}

		// If we get here, failure
		return(false);
	}

	bool iilsa_pass3_extract_imm8__callback(SCallback* cb)
	{
		SExprOps* eopLevel;


		// Block entered for structured exit
		eopLevel = (SExprOps*)cb->data;
		do {

			// For level 4, we add these items
			if (cb->value == 4)
			{
				// Append operands
				if (!iieops_appendEop(eopLevel, (uptr)&ieops_lsa_offset, 0,		_ICODE_LSA_OFFSET))			break;
				if (!iieops_appendEop(eopLevel, (uptr)&ieops_lsa_sizeof, 0,		_ICODE_LSA_SIZEOF))			break;
				if (!iieops_appendEop(eopLevel, (uptr)&ieops_lsa_alignof, 0,	_ICODE_LSA_ALIGNOF))		break;
			}

		} while (0);

		// Indicate success
		return(true);
	}




//////////
//
// Called to populate the gsPass3_functions[] array with addresses for known target instructions.
// It uses the encoding in bits 22..31
//
// Note:  See the iEncode_pass3_branchAddress() and iDecode_pass3_branchAddress()
//
//////
	void iilsa_pass3_init(void)
	{
		u32	lnI;


		//////////
		// Populate
		//////
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_AAA)]._func			= iGenerate_pass3_functionName(aaa);			// AAA					-- ASCII adjust al after addition
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_AAD)]._func			= iGenerate_pass3_functionName(aad);			// AAD					-- ASCII adjust ax before division
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_AAD2)]._func			= iGenerate_pass3_functionName(aad2);			// AAD2					-- ASCII adjust ax before division to base imm8
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_AAM)]._func			= iGenerate_pass3_functionName(aam);			// AAM					-- ASCII adjust ax after multiply
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_AAM2)]._func			= iGenerate_pass3_functionName(aam2);			// AAM2					-- ASCII adjust ax after multiply to base imm8
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_AAS)]._func			= iGenerate_pass3_functionName(aas);			// AAS					-- ASCII adjust al after subtraction
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_ADC)]._func			= iGenerate_pass3_functionName(adc);			// ADC					-- Add with carry r/m32 to r32
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_ADD)]._func			= iGenerate_pass3_functionName(add);			// ADD al,imm8			-- Add imm8 to al
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_AND)]._func			= iGenerate_pass3_functionName(and);			// AND al,imm8			-- imm8  al
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_APRL)]._func			= iGenerate_pass3_functionName(aprl);			// APRL r/m16,r16		-- Adjust RPL of r/m16 to not less than RPL of r16
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_BOUND)]._func			= iGenerate_pass3_functionName(bound);			// BOUND r16,m16&16		-- Check if r16 (array index) is within bounds specified by m16&16
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_BSF)]._func			= iGenerate_pass3_functionName(bsf);			// BSF r16,r/m16		-- Bit scan forward on r/m16
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_BSR)]._func			= iGenerate_pass3_functionName(bsr);			// BSR r16,r/m16		-- Bit scan reverse on r/m16
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_BSWAP)]._func			= iGenerate_pass3_functionName(bswap);			// BSWAP r32			-- Swap endian on 32-bit register
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_BT)]._func				= iGenerate_pass3_functionName(bt);				// BT r/m32,imm8		-- Store selected bit in carry
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_BTC)]._func			= iGenerate_pass3_functionName(btc);			// BTC r/m16,r16		-- Store selected bit in carry, and complement
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_BTR)]._func			= iGenerate_pass3_functionName(btr);			// BTR r/m32,imm8		-- Store selected bit in carry, and clear
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_BTS)]._func			= iGenerate_pass3_functionName(bts);			// BTS r/m32,imm8		-- Store selected bit in carry, and set
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_CALL)]._func			= iGenerate_pass3_functionName(call);			// CALL m16:32			-- Call far, absolute indirect address in m16:32
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_CBW)]._func			= iGenerate_pass3_functionName(cbw);			// CBW					-- Sign-extend al to ax
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_CWDE)]._func			= iGenerate_pass3_functionName(cwde);			// CWDE					-- Sign-extend ax to eax
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_CLC)]._func			= iGenerate_pass3_functionName(clc);			// CLC					-- Clear carry
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_CLD)]._func			= iGenerate_pass3_functionName(cld);			// CLD					-- Clear direction
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_CLI)]._func			= iGenerate_pass3_functionName(cli);			// CLI					-- Clear interrupt
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_CLTS)]._func			= iGenerate_pass3_functionName(clts);			// CLTS					-- Clear task-switched flag in CR0
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_CMOVO)]._func			= iGenerate_pass3_functionName(cmovcc);			// CMOVO				-- Move if o   flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_CMOVNO)]._func			= iGenerate_pass3_functionName(cmovcc);			// CMOVNO				-- Move if no  flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_CMOVB)]._func			= iGenerate_pass3_functionName(cmovcc);			// CMOVB				-- Move if b   flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_CMOVNAE)]._func		= iGenerate_pass3_functionName(cmovcc);			// CMOVNAE				-- Move if nae flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_CMOVAE)]._func			= iGenerate_pass3_functionName(cmovcc);			// CMOVAE				-- Move if ae  flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_CMOVNB)]._func			= iGenerate_pass3_functionName(cmovcc);			// CMOVNB				-- Move if nb  flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_CMOVZ)]._func			= iGenerate_pass3_functionName(cmovcc);			// CMOVZ				-- Move if z   flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_CMOVE)]._func			= iGenerate_pass3_functionName(cmovcc);			// CMOVE				-- Move if e   flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_CMOVNZ)]._func			= iGenerate_pass3_functionName(cmovcc);			// CMOVNZ				-- Move if nz  flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_CMOVNE)]._func			= iGenerate_pass3_functionName(cmovcc);			// CMOVNE				-- Move if ne  flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_CMOVNA)]._func			= iGenerate_pass3_functionName(cmovcc);			// CMOVNA				-- Move if na  flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_CMOVBE)]._func			= iGenerate_pass3_functionName(cmovcc);			// CMOVBE				-- Move if be  flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_CMOVA)]._func			= iGenerate_pass3_functionName(cmovcc);			// CMOVA				-- Move if a   flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_CMOVNBE)]._func		= iGenerate_pass3_functionName(cmovcc);			// CMOVNBE				-- Move if nbe flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_CMOVS)]._func			= iGenerate_pass3_functionName(cmovcc);			// CMOVS				-- Move if s   flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_CMOVNS)]._func			= iGenerate_pass3_functionName(cmovcc);			// CMOVNS				-- Move if ns  flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_CMOVP)]._func			= iGenerate_pass3_functionName(cmovcc);			// CMOVP				-- Move if p   flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_CMOVPE)]._func			= iGenerate_pass3_functionName(cmovcc);			// CMOVPE				-- Move if pe  flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_CMOVNP)]._func			= iGenerate_pass3_functionName(cmovcc);			// CMOVNP				-- Move if np  flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_CMOVPO)]._func			= iGenerate_pass3_functionName(cmovcc);			// CMOVPO				-- Move if po  flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_CMOVL)]._func			= iGenerate_pass3_functionName(cmovcc);			// CMOVL				-- Move if l   flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_CMOVNGE)]._func		= iGenerate_pass3_functionName(cmovcc);			// CMOVNGE				-- Move if nge flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_CMOVGE)]._func			= iGenerate_pass3_functionName(cmovcc);			// CMOVGE				-- Move if ge  flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_CMOVNL)]._func			= iGenerate_pass3_functionName(cmovcc);			// CMOVNL				-- Move if nl  flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_CMOVLE)]._func			= iGenerate_pass3_functionName(cmovcc);			// CMOVLE				-- Move if le  flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_CMOVNG)]._func			= iGenerate_pass3_functionName(cmovcc);			// CMOVNG				-- Move if ng  flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_CMOVG)]._func			= iGenerate_pass3_functionName(cmovcc);			// CMOVG				-- Move if g   flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_CMOVNLE)]._func		= iGenerate_pass3_functionName(cmovcc);			// CMOVNLE				-- Move if nle flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_CMP)]._func			= iGenerate_pass3_functionName(cmp);			// CMP al,imm8			-- imm8  al
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_CMPSB)]._func			= iGenerate_pass3_functionName(cmpsb);			// CMPSB				-- Compare byte in ds:[esi] to es:[edi]
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_CMPSW)]._func			= iGenerate_pass3_functionName(cmpsw);			// CMPSW				-- Compare word in ds:[esi] to es:[edi]
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_CMPSD)]._func			= iGenerate_pass3_functionName(cmpsd);			// CMPSD				-- Compare dword in ds:[esi] to es:[edi]
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_CMPXCHG)]._func		= iGenerate_pass3_functionName(cmpxchg);		// CMPXCHG r/m32,r32	-- Compare eax with r/m16, if equal set zero and load r32 into r/m32, if not equal clear zero and load r/m32 into eax
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_CMPXCHG8B)]._func		= iGenerate_pass3_functionName(cmpxchg8b);		// CMPXCHG8B m64		-- Compare edx:eax with m64, if equal set zero and load ECX:EBX into m64, if not equal clear zero and load m64 into edx:eax
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_CPUID)]._func			= iGenerate_pass3_functionName(cpuid);			// CPUID				-- Based on EAX, load processor information into registers
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_CDW)]._func			= iGenerate_pass3_functionName(cdw);			// CDW					-- Sign-extend ax into dx:ax
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_CDQ)]._func			= iGenerate_pass3_functionName(cdq);			// CDQ					-- Sign-extend eax into edx:eax
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_DAA)]._func			= iGenerate_pass3_functionName(daa);			// DAA					-- Decimal adjust al after addition
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_DAS)]._func			= iGenerate_pass3_functionName(das);			// DAS					-- Decimal adjust al after subtraction
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_DEC)]._func			= iGenerate_pass3_functionName(dec);			// DEC r32				-- Decrement r32 by 1
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_DIV)]._func			= iGenerate_pass3_functionName(div);			// DIV r/m32			-- Unsigned divide edx:eax by r/m32, quotient in eax, remainder in edx
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_EMMS)]._func			= iGenerate_pass3_functionName(emms);			// EMMS					-- Empty the MMX state
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_ENTER)]._func			= iGenerate_pass3_functionName(enter);			// ENTER imm16,imm8		-- Create a stack frame, or nested stack frame
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_F2XM1)]._func			= iGenerate_pass3_functionName(f2xm1);			// F2XM1				-- st0 = 2^(st0 - 1) into st0
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FABS)]._func			= iGenerate_pass3_functionName(fabs);			// FABS					-- st0 = fabs(st0)
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FADD)]._func			= iGenerate_pass3_functionName(fadd);			// FADD f32				-- st0 = st0 + f32
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FADDP)]._func			= iGenerate_pass3_functionName(faddp);			// FADDP stN,st0		-- stN = stN + st0, then pop
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FIADD)]._func			= iGenerate_pass3_functionName(fiadd);			// FIADD s32			-- st0 = st0 + s32
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FBLD)]._func			= iGenerate_pass3_functionName(fbld);			// FBLD m80				-- push m80 loaded as binary coded decimal into st0
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FBSTP)]._func			= iGenerate_pass3_functionName(fbstp);			// FBSTP m80			-- Store st0 as binary coded decimal into m80, then pop
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FCHS)]._func			= iGenerate_pass3_functionName(fchs);			// FCHS					-- Complement st0's sign
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FCLEX)]._func			= iGenerate_pass3_functionName(fclex);			// FCLEX				-- Clear floating point exceptions after checking for pending unmasked exceptions
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FNCLEX)]._func			= iGenerate_pass3_functionName(fnclex);			// FNCLEX				-- No-wait version of FCLEX
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FCMOVB)]._func			= iGenerate_pass3_functionName(fcmovb);			// FCMOVB st0,stN		-- Move if carry
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FCMOVE)]._func			= iGenerate_pass3_functionName(fcmove);			// FCMOVE st0,stN		-- Move if zero
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FCMOVBE)]._func		= iGenerate_pass3_functionName(fcmovbe);		// FCMOVBE st0,stN		-- Move if carry or zero
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FCMOVU)]._func			= iGenerate_pass3_functionName(fcmovu);			// FCMOVU st0,stN		-- Move if parity
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FCMOVNB)]._func		= iGenerate_pass3_functionName(fcmovnb);		// FCMOVNB st0,stN		-- Move if not carry
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FCMOVNE)]._func		= iGenerate_pass3_functionName(fcmovne);		// FCMOVNE st0,stN		-- Move if not zero
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FCMOVNBE)]._func		= iGenerate_pass3_functionName(fcmovnbe);		// FCMOVNBE st0,stN		-- Move if not carry and not zero
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FCMOVNU)]._func		= iGenerate_pass3_functionName(fcmovnu);		// FCMOVNU st0,stN		-- Move if not parity
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FCOM)]._func			= iGenerate_pass3_functionName(fcom);			// FCOM f32				-- Compare st0 with f32
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FCOMP)]._func			= iGenerate_pass3_functionName(fcomp);			// FCOMP stN			-- Compare st0 with stN, then pop
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FCOMPP)]._func			= iGenerate_pass3_functionName(fcompp);			// FCOMPP				-- Compare st0 with st1, then pop, then pop again
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FCOMI)]._func			= iGenerate_pass3_functionName(fcomi);			// FCOMI stN			-- Compare st0 with stN, and set eflags
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FCOMIP)]._func			= iGenerate_pass3_functionName(fcomip);			// FCOMIP stN			-- Compare st0 with stN, and set eflags, then pop
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FUCOMI)]._func			= iGenerate_pass3_functionName(fucomi);			// FUCOMI stN			-- Compare st0 with stN, check for ordered values, and set eflags
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FUCOMIP)]._func		= iGenerate_pass3_functionName(fucomip);		// FUCOMIP stN			-- Compare st0 with stN, check for ordered values, and set eflags, then pop
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FCOS)]._func			= iGenerate_pass3_functionName(fcos);			// FCOS					-- st0 = cos(st0)
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FDECSTP)]._func		= iGenerate_pass3_functionName(fdecstp);		// FDECSTP				-- Decrement the TOP field in the FPU status word
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FDIV)]._func			= iGenerate_pass3_functionName(fdiv);			// FDIV f32				-- st0 = st0 / f32
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FDIVP)]._func			= iGenerate_pass3_functionName(fdivp);			// FDIVP stN,st0		-- stN = stN / st0, then pop
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FIDIV)]._func			= iGenerate_pass3_functionName(fidiv);			// FIDIV s32			-- st0 = st0 / s32
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FDIVR)]._func			= iGenerate_pass3_functionName(fdivr);			// FDIVR f64			-- st0 = f64 / st0
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FDIVRP)]._func			= iGenerate_pass3_functionName(fdivrp);			// FDIVRP stN,st0		-- stN = st0 / stN, then pop
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FIDIVR)]._func			= iGenerate_pass3_functionName(fidivr);			// FIDIVR s32			-- st0 = s32 / st0
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FFREE)]._func			= iGenerate_pass3_functionName(ffree);			// FFREE stN			-- Set the tag for stN to empty
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FICOM)]._func			= iGenerate_pass3_functionName(ficom);			// FICOM s32			-- Compare st0 to s32
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FICOMP)]._func			= iGenerate_pass3_functionName(ficomp);			// FICOMP s32			-- Compare st0 to s32, then pop
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FILD)]._func			= iGenerate_pass3_functionName(fild);			// FILD s16				-- Push s16 into st0
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FINCSTP)]._func		= iGenerate_pass3_functionName(fincstp);		// FINCSTP				-- Increment the TOP field in the FPU status word
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FINIT)]._func			= iGenerate_pass3_functionName(finit);			// FINIT				-- Initialize the FPU
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FIST)]._func			= iGenerate_pass3_functionName(fist);			// FIST m32int			-- Store st0 to memory as s32
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FISTP)]._func			= iGenerate_pass3_functionName(fistp);			// FISTP m64int			-- Store st0 to memory as s64, then pop
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FLD)]._func			= iGenerate_pass3_functionName(fld);			// FLD stN				-- Push stN into st0
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FLD1)]._func			= iGenerate_pass3_functionName(fld1);			// FLD1					-- Push +1.0 into st0
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FLD2T)]._func			= iGenerate_pass3_functionName(fld2t);			// FLDL2T				-- Push log2(10) into st0
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FLD2E)]._func			= iGenerate_pass3_functionName(fldl2e);			// FLDL2E				-- Push log2(e) into st0
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FLDPI)]._func			= iGenerate_pass3_functionName(fldpi);			// FLDPI				-- Push pi into st0
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FLDLG2)]._func			= iGenerate_pass3_functionName(fldlg2);			// FLDLG2				-- Push log10(2) into st0
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FLDN2)]._func			= iGenerate_pass3_functionName(fldn2);			// FLDLN2				-- Push loge(2) into st0
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FLDZ)]._func			= iGenerate_pass3_functionName(fldz);			// FLDZ					-- Push +0.0 into st0
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FLDCW)]._func			= iGenerate_pass3_functionName(fldcw);			// FLDCW u16			-- Load u16 into FPU control word
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FLDENV)]._func			= iGenerate_pass3_functionName(fldenv);			// FLDENV m14/m28		-- Load 14-byte or 28-byte into environment
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FMUL)]._func			= iGenerate_pass3_functionName(fmul);			// FMUL stN,st0			-- stN = stN * st0
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FMULP)]._func			= iGenerate_pass3_functionName(fmulp);			// FMULP stN,st0		-- stN = stN * st0, then pop
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FIMUL)]._func			= iGenerate_pass3_functionName(fimul);			// FIMUL m32int			-- st0 = st0 * s32
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FNOP)]._func			= iGenerate_pass3_functionName(fnop);			// FNOP					-- No operation
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FPATAN)]._func			= iGenerate_pass3_functionName(fpatan);			// FPATAN				-- st1 = arctan(st1 / st0), then pop
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FPREM)]._func			= iGenerate_pass3_functionName(fprem);			// FPREM				-- st0 = st0 % st1
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FPREM1)]._func			= iGenerate_pass3_functionName(fprem1);			// FPREM1				-- st0 = IEEE st0 % st1
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FPTAN)]._func			= iGenerate_pass3_functionName(fptan);			// FPTAN				-- st0 = tan(st0), then push 1 into st0
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FRNDINT)]._func		= iGenerate_pass3_functionName(frndint);		// FRNDINT				-- st0 = int(st0)
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FRSTOR)]._func			= iGenerate_pass3_functionName(frstor);			// FRSTOR m94/m108		-- Load FPU state from a 94 or 108 byte block
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FSAVE)]._func			= iGenerate_pass3_functionName(fsave);			// FSAVE m94/m108		-- Store the FPU state to a 94 or 108 byte block
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FSCALE)]._func			= iGenerate_pass3_functionName(fscale);			// FSCALE				-- st0 = 2^stN
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FSIN)]._func			= iGenerate_pass3_functionName(fsin);			// FSIN					-- st0 = sin(st0)
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FSINCOS)]._func		= iGenerate_pass3_functionName(fsincos);		// FSINCOS				-- t = cos(st0), st0 = sin(st0), then push t into st0
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FSQRT)]._func			= iGenerate_pass3_functionName(fsqrt);			// FSQRT				-- st0 = sqrt(st0)
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FST)]._func			= iGenerate_pass3_functionName(fst);			// FST stN				-- Copy st0 to stN, then pop
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FSTCW)]._func			= iGenerate_pass3_functionName(fstcw);			// FSTCW m16			-- Copy FPU status word to m16
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FSTENV)]._func			= iGenerate_pass3_functionName(fstenv);			// FSTENV m14/m28		-- Copy FPU environment to 14-byte or 28-byte block
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FSTSW)]._func			= iGenerate_pass3_functionName(fstsw);			// FSTSW ax				-- Copy FPU status word to ax
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FSUB)]._func			= iGenerate_pass3_functionName(fsub);			// FSUB stN,st0			-- stN = stN - st0
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FSUBP)]._func			= iGenerate_pass3_functionName(fsubp);			// FSUBP stN,st0		-- stN = stN - st0, then pop
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FISUB)]._func			= iGenerate_pass3_functionName(fisub);			// FISUB s16			-- st0 = st0 - s16
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FSUBR)]._func			= iGenerate_pass3_functionName(fsubr);			// FSUBR stN,st0		-- stN = st0 - stN
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FSUBRP)]._func			= iGenerate_pass3_functionName(fsubrp);			// FSUBRP stN,st0		-- stN = st0 - stN, then pop
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FISUBR)]._func			= iGenerate_pass3_functionName(fisubr);			// FISUBR s16			-- st0 = s16 - st0
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FTST)]._func			= iGenerate_pass3_functionName(ftst);			// FTST					-- Compare st0 to +0.0
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FUCOM)]._func			= iGenerate_pass3_functionName(fucom);			// FUCOM stN			-- Compare st0 to stN
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FUCOMP)]._func			= iGenerate_pass3_functionName(fucomp);			// FUCOMP stN			-- Compare st0 to stN, then pop
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FUCOMPP)]._func		= iGenerate_pass3_functionName(fucompp);		// FUCOMPP				-- Compare st0 to st1, then pop
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FXAM)]._func			= iGenerate_pass3_functionName(fxam);			// FXAM					-- Classify st0
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FXCH)]._func			= iGenerate_pass3_functionName(fxch);			// FXCH stN				-- Exchange st0 and stN
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FXTRACT)]._func		= iGenerate_pass3_functionName(fxtract);		// FXTRACT				-- t = st0's exponent, st0 = st0's significand, then push t into st0
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FYL2X)]._func			= iGenerate_pass3_functionName(fyl2x);			// FYL2X				-- st1 = st1 * log2(st0), then pop
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FYL2XP1)]._func		= iGenerate_pass3_functionName(fyl2xp1);		// FYL2XP1				-- st1 = st1 * log2(st0 + 1.0), then pop
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_HLT)]._func			= iGenerate_pass3_functionName(hlt);			// HLT					-- Halt until interrupt
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_IDIV)]._func			= iGenerate_pass3_functionName(idiv);			// IDIV r/m32			-- Integer divide edx:eax, eax=quotient, edx=remainder
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_IMUL)]._func			= iGenerate_pass3_functionName(imul);			// IMUL r32,r/m32,imm32	-- r32 = r32 * r/m32 * imm32
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_IN)]._func				= iGenerate_pass3_functionName(in);				// IN eax,dx			-- Read dword from I/o port in dx
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_INC)]._func			= iGenerate_pass3_functionName(inc);			// INC r32				-- Increment r32 by 1
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_INS)]._func			= iGenerate_pass3_functionName(ins);			// INS m32,dx			-- Input a dword from I/O port in dx, store to es:[e/di]
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_INSB)]._func			= iGenerate_pass3_functionName(insb);			// INSB					-- Shorthand for INS m8,dx
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_INSW)]._func			= iGenerate_pass3_functionName(insw);			// INSW					-- Shorthand for INS m16,dx
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_INSD)]._func			= iGenerate_pass3_functionName(insd);			// INSD					-- Shorthand for INS m32,dx
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_INT3)]._func			= iGenerate_pass3_functionName(int3);			// INT3					-- Trap to debugger, one byte
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_INT)]._func			= iGenerate_pass3_functionName(int);			// INT imm8				-- Interrupt vector imm8
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_INTO)]._func			= iGenerate_pass3_functionName(into);			// INTO					-- Interrupt on overflow
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_INVD)]._func			= iGenerate_pass3_functionName(invd);			// INVD					-- Invalidate internal caches
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_INVLPG)]._func			= iGenerate_pass3_functionName(invlpg);			// INVLPG m				-- Invalidate TLB entry for page that contains m
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_IRET)]._func			= iGenerate_pass3_functionName(iret);			// IRET					-- Interrupt return 16-bit
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_IRETD)]._func			= iGenerate_pass3_functionName(iretd);			// IRETD				-- Interrupt return 32-bit
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_JO)]._func				= iGenerate_pass3_functionName(jcc);			// JO					-- Conditional jump relative by imm32 offset if o   flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_JNO)]._func			= iGenerate_pass3_functionName(jcc);			// JNO					-- Conditional jump relative by imm32 offset if no  flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_JB)]._func				= iGenerate_pass3_functionName(jcc);			// JB					-- Conditional jump relative by imm32 offset if b   flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_JNAE)]._func			= iGenerate_pass3_functionName(jcc);			// JNAE					-- Conditional jump relative by imm32 offset if nae flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_JAE)]._func			= iGenerate_pass3_functionName(jcc);			// JAE					-- Conditional jump relative by imm32 offset if ae  flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_JNB)]._func			= iGenerate_pass3_functionName(jcc);			// JNB					-- Conditional jump relative by imm32 offset if nb  flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_JZ)]._func				= iGenerate_pass3_functionName(jcc);			// JZ					-- Conditional jump relative by imm32 offset if z   flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_JE)]._func				= iGenerate_pass3_functionName(jcc);			// JE					-- Conditional jump relative by imm32 offset if e   flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_JNZ)]._func			= iGenerate_pass3_functionName(jcc);			// JNZ					-- Conditional jump relative by imm32 offset if nz  flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_JNE)]._func			= iGenerate_pass3_functionName(jcc);			// JNE					-- Conditional jump relative by imm32 offset if ne  flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_JNA)]._func			= iGenerate_pass3_functionName(jcc);			// JNA					-- Conditional jump relative by imm32 offset if na  flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_JBE)]._func			= iGenerate_pass3_functionName(jcc);			// JBE					-- Conditional jump relative by imm32 offset if be  flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_JA)]._func				= iGenerate_pass3_functionName(jcc);			// JA					-- Conditional jump relative by imm32 offset if a   flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_JNBE)]._func			= iGenerate_pass3_functionName(jcc);			// JNBE					-- Conditional jump relative by imm32 offset if nbe flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_JS)]._func				= iGenerate_pass3_functionName(jcc);			// JS					-- Conditional jump relative by imm32 offset if s   flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_JNS)]._func			= iGenerate_pass3_functionName(jcc);			// JNS					-- Conditional jump relative by imm32 offset if ns  flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_JP)]._func				= iGenerate_pass3_functionName(jcc);			// JP					-- Conditional jump relative by imm32 offset if p   flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_JPE)]._func			= iGenerate_pass3_functionName(jcc);			// JPE					-- Conditional jump relative by imm32 offset if pe  flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_JNP)]._func			= iGenerate_pass3_functionName(jcc);			// JNP					-- Conditional jump relative by imm32 offset if np  flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_JPO)]._func			= iGenerate_pass3_functionName(jcc);			// JPO					-- Conditional jump relative by imm32 offset if po  flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_JL)]._func				= iGenerate_pass3_functionName(jcc);			// JL					-- Conditional jump relative by imm32 offset if l   flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_JNGE)]._func			= iGenerate_pass3_functionName(jcc);			// JNGE					-- Conditional jump relative by imm32 offset if nge flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_JGE)]._func			= iGenerate_pass3_functionName(jcc);			// JGE					-- Conditional jump relative by imm32 offset if ge  flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_JNL)]._func			= iGenerate_pass3_functionName(jcc);			// JNL					-- Conditional jump relative by imm32 offset if nl  flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_JLE)]._func			= iGenerate_pass3_functionName(jcc);			// JLE					-- Conditional jump relative by imm32 offset if le  flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_JNG)]._func			= iGenerate_pass3_functionName(jcc);			// JNG					-- Conditional jump relative by imm32 offset if ng  flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_JG)]._func				= iGenerate_pass3_functionName(jcc);			// JG					-- Conditional jump relative by imm32 offset if g   flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_JNLE)]._func			= iGenerate_pass3_functionName(jcc);			// JNLE					-- Conditional jump relative by imm32 offset if nle flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_JMP)]._func			= iGenerate_pass3_functionName(jmp);			// JMP					-- Jump far, absolute indirect, address in m16:32
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_LAHF)]._func			= iGenerate_pass3_functionName(lahf);			// LAHF					-- ah = eflags.sf:zf:0:af:0:pf:1:cf
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_LAR)]._func			= iGenerate_pass3_functionName(lar);			// LAR					-- r32 = r/m32 & 00fxff00h
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_LDS)]._func			= iGenerate_pass3_functionName(lds);			// LDS				 	-- Load DS:r32 indirect from far pointer
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_LSS)]._func			= iGenerate_pass3_functionName(lss);			// LSS				 	-- Load SS:r32 indirect from far pointer
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_LES)]._func			= iGenerate_pass3_functionName(les);			// LES				 	-- Load ES:r32 indirect from far pointer
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_LFS)]._func			= iGenerate_pass3_functionName(lfs);			// LFS				 	-- Load FS:r32 indirect from far pointer
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_LGS)]._func			= iGenerate_pass3_functionName(lgs);			// LGS					-- Load GS:r32 indirect from far pointer
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_LEA)]._func			= iGenerate_pass3_functionName(lea);			// LEA					-- Store effective address for m in r32
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_LEAVE)]._func			= iGenerate_pass3_functionName(leave);			// LEAVE				-- esp = ebp, then pop ebp
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_LGDT)]._func			= iGenerate_pass3_functionName(lgdt);			// LGDT m16&32			-- Load m into GDTR
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_LIDT)]._func			= iGenerate_pass3_functionName(lidt);			// LIDT m16&32			-- Load m into IDTR
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_LLDT)]._func			= iGenerate_pass3_functionName(lldt);			// LLDT r/m16			-- Load selector into LDTR
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_LMSW)]._func			= iGenerate_pass3_functionName(lmsw);			// LMSW r/m16			-- Loads r/m16 into bits cr0
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_LOCK)]._func			= iGenerate_pass3_functionName(lock);			// LOCK					-- Prefix for other instructions, locks system bus
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_LODS)]._func			= iGenerate_pass3_functionName(lods);			// LODS m32				-- Load dword from ds:[e/si] into eax
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_LODSB)]._func			= iGenerate_pass3_functionName(lodsb);			// LODSB				-- Shorthand for LODS m8
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_LODSW)]._func			= iGenerate_pass3_functionName(lodsw);			// LODSW				-- Shorthand for LODS m16
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_LODSD)]._func			= iGenerate_pass3_functionName(lodsd);			// LODSD				-- Shorthand for LODS m32
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_LOOP)]._func			= iGenerate_pass3_functionName(loop);			// LOOP imm8			-- Decrement count, jump short if count != 0
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_LOOPE)]._func			= iGenerate_pass3_functionName(loope);			// LOOPE imm8			-- Decrement count, jump short if count != 0 and zero
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_LOOPZ)]._func			= iGenerate_pass3_functionName(loopz);			// LOOPZ imm8			-- Synonym for LOOPE
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_LOOPNE)]._func			= iGenerate_pass3_functionName(loopne);			// LOOPNE imm8			-- Decrement count, jump short if count != 0 and !zero
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_LOOPNZ)]._func			= iGenerate_pass3_functionName(loopnz);			// LOOPNZ imm8			-- Synonym for LOOPNE
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_LSL)]._func			= iGenerate_pass3_functionName(lsl);			// LSL r32,r/m32		-- r32 = segment_limit(r/m32)
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_LTR)]._func			= iGenerate_pass3_functionName(ltr);			// LTR r/m16			-- Load r/m16 into TR
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_MOV)]._func			= iGenerate_pass3_functionName(mov);			// MOV mm/m64,mmN		-- Move mmN to mmN/m64
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_MOVS)]._func			= iGenerate_pass3_functionName(movs);			// MOVS m32,m32			-- Move dword from ds:[e/si] to es:[e/di] 
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_MOVSB)]._func			= iGenerate_pass3_functionName(movsb);			// MOVSB				-- Shorthand for MOVS m8,m8
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_MOVSW)]._func			= iGenerate_pass3_functionName(movsw);			// MOVSW				-- Shorthand for MOVS m16,m16
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_MOVSD)]._func			= iGenerate_pass3_functionName(movsd);			// MOVSD				-- Shorthand for MOVS m32,m32
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_MOVSX)]._func			= iGenerate_pass3_functionName(movsx);			// MOVSX r32,r/m16		-- Sign-extend word to dword
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_MOVZX)]._func			= iGenerate_pass3_functionName(movzx);			// MOVZX r32,r/m16		-- Zero-extend word to dword
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_MUL)]._func			= iGenerate_pass3_functionName(mul);			// MUL r/m32			-- edx:eax = eax * r/m32
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_NEG)]._func			= iGenerate_pass3_functionName(neg);			// NEG r/m32			-- Two's complement r/m32
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_NOP)]._func			= iGenerate_pass3_functionName(nop);			// NOP					-- No operation
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_NOT)]._func			= iGenerate_pass3_functionName(not);			// NOT r/m32			-- Logical NOT of r/m32
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_OR)]._func				= iGenerate_pass3_functionName(or);				// OR r32,r/m32			-- r/m32 to r32
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_OUT)]._func			= iGenerate_pass3_functionName(out);			// OUT dx,eax			-- Output eax to I/O port dx
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_OUTS)]._func			= iGenerate_pass3_functionName(outs);			// OUTS dx,m32			-- Output dword at ds:[e/si] to I/O port dx
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_OUTSB)]._func			= iGenerate_pass3_functionName(outsb);			// OUTSB				-- Shorthand for OUTS dx,m8
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_OUTSW)]._func			= iGenerate_pass3_functionName(outsw);			// OUTSW				-- Shorthand for OUTS dx,m16
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_OUTSD)]._func			= iGenerate_pass3_functionName(outsd);			// OUTSD				-- Shorthand for OUTS dx,m32
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_POP)]._func			= iGenerate_pass3_functionName(pop);			// POP GS				-- Pop stack into GS
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_POPA)]._func			= iGenerate_pass3_functionName(popa);			// POPA					-- Pop all r16 registers
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_POPAD)]._func			= iGenerate_pass3_functionName(popad);			// POPAD				-- Pop all r32 registers
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_POPF)]._func			= iGenerate_pass3_functionName(popf);			// POPF					-- Pop 16-bit flags
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_POPFD)]._func			= iGenerate_pass3_functionName(popfd);			// POPFD				-- Pop 32-bit eflags
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_PREFETCH0)]._func		= iGenerate_pass3_functionName(prefetch0);		// PREFETCHT0 m8		-- Prefetch block around m8 into all caches
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_PREFETCH1)]._func		= iGenerate_pass3_functionName(prefetch1);		// PREFETCHT1 m8		-- Prefetch block around m8 into l1 and above
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_PREFETCH2)]._func		= iGenerate_pass3_functionName(prefetch2);		// PREFETCHT2 m8		-- Prefetch block around m8 into l2 and above
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_PREFETCHNT)]._func		= iGenerate_pass3_functionName(prefetchnt);		// PREFETCHNT m8		-- Prefetch block around m8 into non-temporal caches
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_PUSH)]._func			= iGenerate_pass3_functionName(push);			// PUSH gs				-- Push GS
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_PUSHA)]._func			= iGenerate_pass3_functionName(pusha);			// PUSHA				-- Push all 16-bit registers
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_PUSHAD)]._func			= iGenerate_pass3_functionName(pushad);			// PUSHAD				-- Push all 32-bit registers
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_PUSHF)]._func			= iGenerate_pass3_functionName(pushf);			// PUSHF				-- Push 16-bit flags
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_PUSHFD)]._func			= iGenerate_pass3_functionName(pushfd);			// PUSHFD				-- Push 32-bit eflags
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_RCL)]._func			= iGenerate_pass3_functionName(rcl);			// RCL r/m32,imm8		-- Rotate r/m32 through carry by imm8 bits left
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_RCR)]._func			= iGenerate_pass3_functionName(rcr);			// RCR r/m32,imm8		-- Rotate r/m32 through carry by imm8 bits right
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_REPNE)]._func			= iGenerate_pass3_functionName(repne);			// REPne/z prefix
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_REPNZ)]._func			= iGenerate_pass3_functionName(repne);			// REPne/z prefix
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_REPE)]._func			= iGenerate_pass3_functionName(repe);			// REP/e/z prefix
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_REPZ)]._func			= iGenerate_pass3_functionName(repe);			// REP/e/z prefix
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_ROL)]._func			= iGenerate_pass3_functionName(rol);			// ROL r/m32,imm8		-- Rotate r/m32 by imm8 bits left
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_ROR)]._func			= iGenerate_pass3_functionName(ror);			// ROR r/m32,imm8		-- Rotate r/m32 by imm8 bits right
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_RDMSR)]._func			= iGenerate_pass3_functionName(rdmsr);			// RDMSR				-- Load MSR specified by ecx into edx:eax
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_RDPMC)]._func			= iGenerate_pass3_functionName(rdpmc);			// RDPMC				-- Read performance monitoring counter specified by ecx into edx:eax
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_RDTSC)]._func			= iGenerate_pass3_functionName(rdtsc);			// RDTSC				-- Read time-stamp counter into edx:eax
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_RET)]._func			= iGenerate_pass3_functionName(ret);			// RET imm16			-- Far return, and pop imm16 bytes from stack
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_SAHF)]._func			= iGenerate_pass3_functionName(sahf);			// SAHF					-- Store ah into flags
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_SAR)]._func			= iGenerate_pass3_functionName(sar);			// SAR r/m32,imm8		-- Signed divide r/m32 by imm8 times
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_SHL)]._func			= iGenerate_pass3_functionName(shl);			// SHL r/m32,imm8		-- Shift left r/m32 imm8 times
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_SHR)]._func			= iGenerate_pass3_functionName(shr);			// SHR r/m32,imm8		-- Shift right r/m32 imm8 times
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_SBB)]._func			= iGenerate_pass3_functionName(sbb);			// SBB r32,r/m32		-- r/m32 from r32
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_SCAS)]._func			= iGenerate_pass3_functionName(scas);			// SCAS m32				-- Compare eax with dword in es:[e/di]
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_SCASB)]._func			= iGenerate_pass3_functionName(scasb);			// SCASB				-- Shorthand for SCAS m8
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_SCASW)]._func			= iGenerate_pass3_functionName(scasw);			// SCASW				-- Shorthand for SCAS m16
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_SCASD)]._func			= iGenerate_pass3_functionName(scasd);			// SCASD				-- Shorthand for SCAS m32
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_SETO)]._func			= iGenerate_pass3_functionName(setcc);			// SETO					-- Set byte if o   flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_SETNO)]._func			= iGenerate_pass3_functionName(setcc);			// SETNO				-- Set byte if no  flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_SETB)]._func			= iGenerate_pass3_functionName(setcc);			// SETB					-- Set byte if b   flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_SETNAE)]._func			= iGenerate_pass3_functionName(setcc);			// SETNAE				-- Set byte if nae flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_SETAE)]._func			= iGenerate_pass3_functionName(setcc);			// SETAE				-- Set byte if ae  flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_SETNB)]._func			= iGenerate_pass3_functionName(setcc);			// SETNB				-- Set byte if nb  flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_SETZ)]._func			= iGenerate_pass3_functionName(setcc);			// SETZ					-- Set byte if z   flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_SETE)]._func			= iGenerate_pass3_functionName(setcc);			// SETE					-- Set byte if e   flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_SETNZ)]._func			= iGenerate_pass3_functionName(setcc);			// SETNZ				-- Set byte if nz  flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_SETNE)]._func			= iGenerate_pass3_functionName(setcc);			// SETNE				-- Set byte if ne  flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_SETNA)]._func			= iGenerate_pass3_functionName(setcc);			// SETNA				-- Set byte if na  flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_SETBE)]._func			= iGenerate_pass3_functionName(setcc);			// SETBE				-- Set byte if be  flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_SETA)]._func			= iGenerate_pass3_functionName(setcc);			// SETA					-- Set byte if a   flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_SETNBE)]._func			= iGenerate_pass3_functionName(setcc);			// SETNBE				-- Set byte if nbe flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_SETS)]._func			= iGenerate_pass3_functionName(setcc);			// SETS					-- Set byte if s   flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_SETNS)]._func			= iGenerate_pass3_functionName(setcc);			// SETNS				-- Set byte if ns  flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_SETP)]._func			= iGenerate_pass3_functionName(setcc);			// SETP					-- Set byte if p   flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_SETPE)]._func			= iGenerate_pass3_functionName(setcc);			// SETPE				-- Set byte if pe  flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_SETNP)]._func			= iGenerate_pass3_functionName(setcc);			// SETNP				-- Set byte if np  flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_SETPO)]._func			= iGenerate_pass3_functionName(setcc);			// SETPO				-- Set byte if po  flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_SETL)]._func			= iGenerate_pass3_functionName(setcc);			// SETL					-- Set byte if l   flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_SETNGE)]._func			= iGenerate_pass3_functionName(setcc);			// SETNGE				-- Set byte if nge flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_SETGE)]._func			= iGenerate_pass3_functionName(setcc);			// SETGE				-- Set byte if ge  flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_SETNL)]._func			= iGenerate_pass3_functionName(setcc);			// SETNL				-- Set byte if nl  flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_SETLE)]._func			= iGenerate_pass3_functionName(setcc);			// SETLE				-- Set byte if le  flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_SETNG)]._func			= iGenerate_pass3_functionName(setcc);			// SETNG				-- Set byte if ng  flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_SETG)]._func			= iGenerate_pass3_functionName(setcc);			// SETG					-- Set byte if g   flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_SETNLE)]._func			= iGenerate_pass3_functionName(setcc);			// SETNLE				-- Set byte if nle flag condition is true
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_SGDT)]._func			= iGenerate_pass3_functionName(sgdt);			// SGDT m48				-- Store GDTR to m48
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_SIDT)]._func			= iGenerate_pass3_functionName(sidt);			// SIDT m48				-- Store IDTR to m48
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_SLDT)]._func			= iGenerate_pass3_functionName(sldt);			// SLDT r/m16			-- Store LDTR to r/m16
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_SHLD)]._func			= iGenerate_pass3_functionName(shld);			// SHLD r/m32,r32,cl	-- Shift r/m32 left cl places, shifting in bits from r32
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_SHRD)]._func			= iGenerate_pass3_functionName(shrd);			// SHRD r/m32,r32,cl	-- Shift r/m32 right cl places, shifting in bits from r32
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_SMSW)]._func			= iGenerate_pass3_functionName(smsw);			// SMSW r32/m16			-- Store machine status word to r32/m16
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_STC)]._func			= iGenerate_pass3_functionName(stc);			// STC					-- Set carry
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_STD)]._func			= iGenerate_pass3_functionName(std);			// STD					-- Set direction
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_STI)]._func			= iGenerate_pass3_functionName(sti);			// STI					-- Set interrupt
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_STOS)]._func			= iGenerate_pass3_functionName(stos);			// STOS m32				-- Store eax into es:[e/di]
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_STOSB)]._func			= iGenerate_pass3_functionName(stosb);			// STOSB				-- Shorthand for STOS m8
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_STOSW)]._func			= iGenerate_pass3_functionName(stosw);			// STOSW				-- Shorthand for STOS m16
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_STOSD)]._func			= iGenerate_pass3_functionName(stosd);			// STOSD				-- Shorthand for STOS m32
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_STR)]._func			= iGenerate_pass3_functionName(str);			// STR r/m16			-- Stores segment selector from TR in r/m16
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_SUB)]._func			= iGenerate_pass3_functionName(sub);			// SUB r32,r/m32		-- r/m32 from r32
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_SYSENTER)]._func		= iGenerate_pass3_functionName(sysenter);		// SYSENTER				-- Fast system entry
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_SYSEXIT)]._func		= iGenerate_pass3_functionName(sysexit);		// SYSEXIT				-- Fast system exit
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_TEST)]._func			= iGenerate_pass3_functionName(test);			// TEST r/m32,r32		-- r32 and r/m32
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_UD2)]._func			= iGenerate_pass3_functionName(ud2);			// UD2					-- Raises invalid opcode exception
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_VERR)]._func			= iGenerate_pass3_functionName(verr);			// VERR r/m16			-- Verify segment r/m16 can be read
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_VERW)]._func			= iGenerate_pass3_functionName(verw);			// VERW r/m16			-- Verify segment r/m16 can be written to
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_FWAIT)]._func			= iGenerate_pass3_functionName(fwait);			// FWAIT				-- Check pending unmasked floating-point exceptions
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_WBINVD)]._func			= iGenerate_pass3_functionName(wbinvd);			// WBINVD				-- Write back and flush internal caches
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_WRMSR)]._func			= iGenerate_pass3_functionName(wrmsr);			// WRMSR				-- Write the value in edx:eax to MSR specified by ecx
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_XADD)]._func			= iGenerate_pass3_functionName(xadd);			// XADD r/m32,r32		-- Exchange r32 and r/m32, and load sum into r/m32
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_XCHG)]._func			= iGenerate_pass3_functionName(xchg);			// XCHG r/m32,r32		-- Exchange r32 and r/m32
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_XLAT)]._func			= iGenerate_pass3_functionName(xlat);			// XLAT m8				-- Set al to ds:[e/bx + al]
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_XLATB)]._func			= iGenerate_pass3_functionName(xlatb);			// XLATB				-- Shorthand for XLAT m8
			gsPass3_functions[iDecode_pass3_branchAddress(_ICODE_LSA_XOR)]._func			= iGenerate_pass3_functionName(xor);			// XOR r32,r/m32		-- r/m32 and r32


		//////////
		// Validate
		//////
			// Iterate, every item should be populated
				for (lnI = _LSA_PASS3_CODE_BRANCH_MIN; lnI <= _LSA_PASS3_CODE_BRANCH_MAX; lnI++)
				{
					// Should never happen
					if (gsPass3_functions[lnI]._func)
					{
						// Note:  If we get here, one of the _ICODE_LSA_* items above is not contiguous
						// Note:  The value of lnI should indicate which one it is, or the item near where it is
						ilsa_internal_compiler_error();
					}
				}
	}