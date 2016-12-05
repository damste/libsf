//////////
//
// /libsf/arxoda/oppie/oppie1/cpp_simulation/oppie/oppie1.cpp
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
// Copyright (c) 2014 by Rick C. Hodgin
//////
// Last update:
//     Nov.26.2014
//////
// Change log:
//     Nov.24.2014 - Initial creation
//////
//
// This software is released as Liberty Software under a Repeat License, as governed
// by the Public Benefit License v1.0 or later (PBL).
//
// You are free to use, copy, modify and share this software.  However, it can only
// be released under the PBL version indicated, and every project must include a copy
// of the pbl.txt document for its version as is at http://www.libsf.org/licenses/.
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


//////////
// Opcode bit encodings
//////
	cu32		B000						= 0x0;		// Binary 000
	cu32		B001						= 0x1;		// Binary 001
	cu32		B100						= 0x4;		// Binary 100
	cu32		B101						= 0x5;		// Binary 101
	cu32		B0100						= 0x4;		// Binary 0100
	cu32		B0101						= 0x5;		// Binary 0101
	cu32		B0110						= 0x6;		// Binary 0110
	cu32		B0111						= 0x7;		// Binary 0111
	cu32		B11000						= 0x18;		// Binary 11000
	cu32		B11001						= 0x19;		// Binary 11001
	cu32		B11010						= 0x1a;		// Binary 11010
	cu32		B11011						= 0x1b;		// Binary 11011
	cu32		B11100						= 0x1c;		// Binary 11100
	cu32		B11111						= 0x1f;		// Binary 11111

	cu32		_OPCODE_THREE_BITS			= 0x30000000;
	cu32		_OPCODE_FOUR_BITS			= 0x40000000;
	cu32		_OPCODE_FIVE_BITS			= 0x50000000;
	cu32		_OPCODE_MASK				= B11111;		// Mask for the actual opcode bits

	cu32		_OPCODE_MOV_R8_ADDR			= _OPCODE_THREE_BITS	| B000;		//		mov   reg8,[address]	2			000.00.000:00000000
	cu32		_OPCODE_MOV_R8_R8			= _OPCODE_THREE_BITS	| B001;		//		mov   reg8,reg8			1			001.x.00.00	(dest,src)
	cu32		_OPCODE_ADC_R8_R8			= _OPCODE_FOUR_BITS		| B0110;	//		adc   reg8,reg8			1			0110.00.00
	cu32		_OPCODE_SBB_R8_R8			= _OPCODE_FOUR_BITS		| B0111;	//		sbb   reg8,reg8			1			0111.00.00
	cu32		_OPCODE_ADD_R8_R8			= _OPCODE_FOUR_BITS		| B0100;	//		add   reg8,reg8			1			0100.00.00
	cu32		_OPCODE_SUB_R8_R8			= _OPCODE_FOUR_BITS		| B0101;	//		sub   reg8,reg8			1			0101.00.00
	cu32		_OPCODE_MOV_ADDR_R8			= _OPCODE_THREE_BITS	| B100;		//		mov   [address],reg8	2			100.00.000:00000000
	cu32		_OPCODE_CMP_R8_R8			= _OPCODE_THREE_BITS	| B101;		//		cmp   reg8,reg8			1			101.x.00.00	(left,right)
	cu32		_OPCODE_JNC_REL_ADDR		= _OPCODE_FIVE_BITS		| B11000;	//		jnc   +/- 1KB			2			11000.s.00:00000000
	cu32		_OPCODE_JC_REL_ADDR			= _OPCODE_FIVE_BITS		| B11001;	//		jc    +/- 1KB			2			11001.s.00:00000000
	cu32		_OPCODE_JNZ_REL_ADDR		= _OPCODE_FIVE_BITS		| B11010;	//		jnz   +/- 1KB			2			11010.s.00:00000000
	cu32		_OPCODE_JZ_REL_ADDR			= _OPCODE_FIVE_BITS		| B11011;	//		jz    +/- 1KB			2			11011.s.00:00000000
	cu32		_OPCODE_JMP_REL_ADDR		= _OPCODE_FIVE_BITS		| B11100;	//		jmp   +/- 1KB			2			11100.s.00:00000000

	cu32		_SIGN_NEGATIVE				= 1;
	cu32		_SIGN_POSITIVE				= 0;

	cu32		_R1							= 0;		// 00b
	cu32		_R2							= 1;		// 01b
	cu32		_R3							= 2;		// 10b
	cu32		_R4							= 3;		// 11b


//////////
// Template instructions
//////
	struct SOra	// Ora = Operation, register, address
	{
		// ooo.rr.aaa:aaaaaaaa
		union {
			struct {
				u8		i_data1;			// Opcode byte 1
				u8		i_data2;			// Opcode byte 2
			};
			struct {
				u8		aaaaaaaa	: 8;
				u8		aaa			: 3;
				u8		rd			: 2;
				u8		ooo			: 3;
			};
		};
	};

	struct SOrr // Orr = Operation, register, register
	{
		// ooo.x.rd.rs		-- 3-bit form
		// oooo.rd.rs		-- 4-bit form
		union {
			struct {
				u8		i_data1;			// Opcode byte 1
				u8		i_data2;			// Unused opcode byte 2 to align everything
			};
			struct {
				u8		rs			: 2;
				u8		rd			: 2;
				u8		ignore		: 4;
			};
			struct {
				u8		rs1			: 2;
				u8		rd1			: 2;
				u8		x			: 1;
				u8		ooo			: 3;
			};
			struct {
				u8		rs2			: 2;
				u8		rd2			: 2;
				u8		oooo		: 4;
			};
		};
	};

	struct SBsa	// Bsa = Branch, sign, address
	{
		// ooooo.s.aa:aaaaaaaa
		union {
			struct {
				u8		i_data1;			// Opcode byte 1
				u8		i_data2;			// Opcode byte 2
			};
			struct {
				u8		aaaaaaaa	: 8;
				u8		aa			: 2;
				u8		s			: 1;
				u8		ooooo		: 5;
			};
		};
	};

	struct SOppie1Instruction
	{
		SLL		ll;							// Link list

		s32		org;						// The offset into memory for this item
		s32		size;						// Number of bytes for this item, either 0, or greater

		// Flags for certain operations
		bool	isOrg;						// For .org statements, the org is populated with its new org
		bool	isLabel;					// For label: statements, indicates this one is a label
		s32		labelComponentNumber;		// Which component within the line is the label component?

		// For data we do not store in instructions
		bool	isData;						// If true uses data, if false uses the instruction below
		u8*		data;						// If isData, then this is the data related to it

		// Instructions are at most 2-bytes in Oppie-1
		bool	isInstruction;				// Added late in the development of this project so as to bypass blank lines
		union {
			SOra	ora;
			SOrr	orr;
			SBsa	bsa;
		};
	};
