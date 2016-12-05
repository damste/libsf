//////////
//
// /libsf/arxoda/oppie/oppie1/cpp_simulation/oppie1/debo1_disasm.cpp
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
// Version 0.02
// Copyright (c) 2014 by Rick C. Hodgin
//////
// Last update:
//     Dec.04.2014
//////
// Change log:
//     Dec.04.2014 - Initial creation
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
//////
//
//		mov   reg8,[address]	2			000.00.000:00000000
//		mov   reg8,reg8			1			0010.00.00	(dest,src)
//		add   reg8,reg8			1			0100.00.00
//		adc   reg8,reg8			1			0110.00.00
//		sub   reg8,reg8			1			0101.00.00
//		sbb   reg8,reg8			1			0111.00.00
//		mov   [address],reg8	2			100.00.000:00000000
//		cmp   reg8,reg8			1			1010.00.00	(left,right)
//		jnc   +/- 1KB			2			11000.s.00:00000000
//		jc    +/- 1KB			2			11001.s.00:00000000
//		jnz   +/- 1KB			2			11010.s.00:00000000
//		jz    +/- 1KB			2			11011.s.00:00000000
//		jmp   +/- 1KB			2			11100.s.00:00000000 
//
//




#include "debo1_disasm.h"


//////////
//
// Disassemble the instruction into text form
//
//////
	s32 iiDebo1_decodeAssembly(s8* tcText, s32 ip_address, bool tlIncludeIpAddress, bool tlIncludeOpcodeBytes, u8* ram)
	{
		s32		lnOpcodeCount;
		SOra	iora;		// ooo.xx.aaa.aaaaaaaa
		SOrr	iorr;		// ooo.x.rd.rs, oooo.rd.rs
		SBsa	ibsa;		// ooooo.s.aa.aaaaaaaa


		//////////
		// Fill the instruction patterns for testing
		//////
			iora.i_data1 = ram[ip_address + 0];
			iora.i_data2 = ram[ip_address + 1];
			iorr.i_data1 = ram[ip_address + 0];
			iorr.i_data2 = ram[ip_address + 1];
			ibsa.i_data1 = ram[ip_address + 0];
			ibsa.i_data2 = ram[ip_address + 1];

			// Include the ip address
			if (tlIncludeIpAddress)		sprintf(tcText, "%03x: \0", ip_address);
			else						sprintf(tcText, "\0");

			// Decode the bits
			if (iorr.oooo == (_OPCODE_ADD_R8_R8 & _OPCODE_MASK))
			{
				// add   reg8,reg8			1			0100.00.00
				lnOpcodeCount = 1;

				// Opcode byte
				if (tlIncludeOpcodeBytes)
					sprintf(tcText + strlen(tcText), "%02x      \0", ram[ip_address]);

				// Disassembly
				sprintf(tcText + strlen(tcText), "add r%u,r%u\0", (u32)iorr.rd + 1, (u32)iorr.rs + 1);

			} else if (iorr.oooo == (_OPCODE_ADC_R8_R8 & _OPCODE_MASK)) {
				// adc   reg8,reg8			1			0110.00.00
				lnOpcodeCount = 1;

				// Opcode byte
				if (tlIncludeOpcodeBytes)
					sprintf(tcText + strlen(tcText), "%02x      \0", ram[ip_address]);

				// Disassembly
				sprintf(tcText + strlen(tcText), "adc r%u,r%u\0", (u32)iorr.rd + 1, (u32)iorr.rs + 1);

			} else if (iorr.oooo == (_OPCODE_SUB_R8_R8 & _OPCODE_MASK)) {
				// sub   reg8,reg8			1			0101.00.00
				lnOpcodeCount = 1;

				// Opcode byte
				if (tlIncludeOpcodeBytes)
					sprintf(tcText + strlen(tcText), "%02x      \0", ram[ip_address]);

				// Disassembly
				sprintf(tcText + strlen(tcText), "sub r%u,r%u\0", (u32)iorr.rd + 1, (u32)iorr.rs + 1);

			} else if (iorr.oooo == (_OPCODE_SBB_R8_R8 & _OPCODE_MASK)) {
				// sbb   reg8,reg8			1			0111.00.00
				lnOpcodeCount = 1;

				// Opcode byte
				if (tlIncludeOpcodeBytes)
					sprintf(tcText + strlen(tcText), "%02x      \0", ram[ip_address]);

				// Disassembly
				sprintf(tcText + strlen(tcText), "sbb r%u,r%u\0", (u32)iorr.rd + 1, (u32)iorr.rs + 1);

			} else if (iorr.ooo == (_OPCODE_CMP_R8_R8 & _OPCODE_MASK)) {
				// cmp   reg8,reg8			1			101.x.00.00	(left,right)
				lnOpcodeCount = 1;

				// Opcode byte
				if (tlIncludeOpcodeBytes)
					sprintf(tcText + strlen(tcText), "%02x      \0", ram[ip_address]);

				// Disassembly
				sprintf(tcText + strlen(tcText), "cmp r%u,r%u\0", (u32)iorr.rd + 1, (u32)iorr.rs + 1);

			} else if (iora.ooo == (_OPCODE_MOV_R8_ADDR & _OPCODE_MASK)) {
				// mov   reg8,[address]		2			000.00.000:00000000
				lnOpcodeCount = 2;

				// Opcode bytes
				if (tlIncludeOpcodeBytes)
					sprintf(tcText + strlen(tcText), "%02x %02x   \0", ram[ip_address], ram[ip_address+1]);

				// Disassembly
				sprintf(tcText + strlen(tcText), "mov r%u,[%03x]\0", (u32)iora.rd + 1, ((u16)iora.aaa << 8) | (u16)iora.aaaaaaaa);

			} else if (iora.ooo == (_OPCODE_MOV_ADDR_R8 & _OPCODE_MASK)) {
				// mov   [address],reg8		2			100.00.000:00000000
				lnOpcodeCount = 2;

				// Opcode bytes
				if (tlIncludeOpcodeBytes)
					sprintf(tcText + strlen(tcText), "%02x %02x   \0", ram[ip_address], ram[ip_address+1]);

				// Disassembly
				sprintf(tcText + strlen(tcText), "mov [%03x],r%u\0", ((u16)iora.aaa << 8) | (u16)iora.aaaaaaaa, (u32)iora.rd + 1);

			} else if (iorr.ooo == (_OPCODE_MOV_R8_R8 & _OPCODE_MASK)) {
				// mov   reg8,reg8			1			001.x.00.00	(dest,src)
				lnOpcodeCount = 1;

				// Opcode byte
				if (tlIncludeOpcodeBytes)
					sprintf(tcText + strlen(tcText), "%02x      \0", ram[ip_address]);

				// Disassembly
				sprintf(tcText + strlen(tcText), "mov r%u,r%u\0", (u32)iorr.rd + 1, (u32)iorr.rs + 1);

			} else if (ibsa.ooooo == (_OPCODE_JNC_REL_ADDR & _OPCODE_MASK)) {
				// jnc    +/- 1KB
				lnOpcodeCount = 2;

				// Opcode bytes
				if (tlIncludeOpcodeBytes)
					sprintf(tcText + strlen(tcText), "%02x %02x   \0", ram[ip_address], ram[ip_address+1]);

				// Disassembly
				if (ibsa.s)
				{
					// Jumping negative
					sprintf(tcText + strlen(tcText), "jnc  -%03x   (%03x:)\0", ((u16)ibsa.aa << 8) | (u16)ibsa.aaaaaaaa, ip_address + 2 - (((u16)ibsa.aa << 8) | (u16)ibsa.aaaaaaaa));

				} else {
					// Jumping positive
					sprintf(tcText + strlen(tcText), "jnc  +%03x   (%03x:)\0", ((u16)ibsa.aa << 8) | (u16)ibsa.aaaaaaaa, ip_address + 2 + (((u16)ibsa.aa << 8) | (u16)ibsa.aaaaaaaa));
				}

			} else if (ibsa.ooooo == (_OPCODE_JC_REL_ADDR & _OPCODE_MASK)) {
				// jc    +/- 1KB
				lnOpcodeCount = 2;

				// Opcode bytes
				if (tlIncludeOpcodeBytes)
					sprintf(tcText + strlen(tcText), "%02x %02x   \0", ram[ip_address], ram[ip_address+1]);

				// Disassembly
				if (ibsa.s)
				{
					// Jumping negative
					sprintf(tcText + strlen(tcText), "jc  -%03x   (%03x:)\0", ((u16)ibsa.aa << 8) | (u16)ibsa.aaaaaaaa, ip_address + 2 - (((u16)ibsa.aa << 8) | (u16)ibsa.aaaaaaaa));

				} else {
					// Jumping positive
					sprintf(tcText + strlen(tcText), "jc  +%03x   (%03x:)\0", ((u16)ibsa.aa << 8) | (u16)ibsa.aaaaaaaa, ip_address + 2 + (((u16)ibsa.aa << 8) | (u16)ibsa.aaaaaaaa));
				}

			} else if (ibsa.ooooo == (_OPCODE_JNZ_REL_ADDR & _OPCODE_MASK)) {
				// jnz    +/- 1KB
				lnOpcodeCount = 2;

				// Opcode bytes
				if (tlIncludeOpcodeBytes)
					sprintf(tcText + strlen(tcText), "%02x %02x   \0", ram[ip_address], ram[ip_address+1]);

				// Disassembly
				if (ibsa.s)
				{
					// Jumping negative
					sprintf(tcText + strlen(tcText), "jnz  -%03x   (%03x:)\0", ((u16)ibsa.aa << 8) | (u16)ibsa.aaaaaaaa, ip_address + 2 - (((u16)ibsa.aa << 8) | (u16)ibsa.aaaaaaaa));

				} else {
					// Jumping positive
					sprintf(tcText + strlen(tcText), "jnz  +%03x   (%03x:)\0", ((u16)ibsa.aa << 8) | (u16)ibsa.aaaaaaaa, ip_address + 2 + (((u16)ibsa.aa << 8) | (u16)ibsa.aaaaaaaa));
				}

			} else if (ibsa.ooooo == (_OPCODE_JZ_REL_ADDR & _OPCODE_MASK)) {
				// jz    +/- 1KB
				lnOpcodeCount = 2;

				// Opcode bytes
				if (tlIncludeOpcodeBytes)
					sprintf(tcText + strlen(tcText), "%02x %02x   \0", ram[ip_address], ram[ip_address+1]);

				// Disassembly
				if (ibsa.s)
				{
					// Jumping negative
					sprintf(tcText + strlen(tcText), "jz  -%03x   (%03x:)\0", ((u16)ibsa.aa << 8) | (u16)ibsa.aaaaaaaa, ip_address + 2 - (((u16)ibsa.aa << 8) | (u16)ibsa.aaaaaaaa));

				} else {
					// Jumping positive
					sprintf(tcText + strlen(tcText), "jz  +%03x   (%03x:)\0", ((u16)ibsa.aa << 8) | (u16)ibsa.aaaaaaaa, ip_address + 2 + (((u16)ibsa.aa << 8) | (u16)ibsa.aaaaaaaa));
				}

			} else if (ibsa.ooooo == (_OPCODE_JMP_REL_ADDR & _OPCODE_MASK)) {
				// jmp   +/- 1KB
				lnOpcodeCount = 2;

				// Opcode bytes
				if (tlIncludeOpcodeBytes)
					sprintf(tcText + strlen(tcText), "%02x %02x   \0", ram[ip_address], ram[ip_address+1]);

				// Disassembly
				if (ibsa.s)
				{
					// Jumping negative
					sprintf(tcText + strlen(tcText), "jmp -%03x   (%03x:)\0", ((u16)ibsa.aa << 8) | (u16)ibsa.aaaaaaaa, ip_address + 2 - (((u16)ibsa.aa << 8) | (u16)ibsa.aaaaaaaa));

				} else {
					// Jumping positive
					sprintf(tcText + strlen(tcText), "jmp +%03x   (%03x:)\0", ((u16)ibsa.aa << 8) | (u16)ibsa.aaaaaaaa, ip_address + 2 + (((u16)ibsa.aa << 8) | (u16)ibsa.aaaaaaaa));
				}

			} else {
				// Invalid opcode
				lnOpcodeCount = 1;
				sprintf(tcText + strlen(tcText), "%02x unknown opcode\0", ram[ip_address]);
			}


		//////////
		// Indicate how many bytes were used in the opcode
		//////
			return(lnOpcodeCount);
	}
