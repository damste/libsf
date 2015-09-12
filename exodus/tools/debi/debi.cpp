//////////
//
// /libsf/exodus/tools/debi/debi.cpp
//
//////
// Version 0.80
// Copyright (c) 2014-2015 by Rick C. Hodgin
//////
// Last update:
//     Sep.12.2015
//////
// Change log:
//     Sep.12.2015 - Refactoring for Exodus OS tool support
//     Feb.13.2014 - Initial creation
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
//     http://www.visual-freepro.org/wiki/index.php/Repeat_License
//
// Thank you.  And may The Lord bless you richly as you lift up your life, your
// talents, your gifts, your praise, unto Him.  In Jesus' name I pray.  Amen.
//
//




#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include "debi_const.h"
#include "debi_structs.h"
#include "debi_defs.h"
#include "debi_globals.h"
#include "disasm_opcodes.h"

// Default to 32-bit instruction encoding
MODE _cpu_mode = _32bit_mode;




//////////
// Note:	Eventually this will fold into one component of a user-level debugger, but for now it is just a disassembler.
//////
	int main(int argc, char **argv)
	{
		u32		length, lnOffset, lnLength, numread;
		u8*		data;
		FILE*	lfh;


		//////////
		// 
		//////
			if (argc < 2)
			{
				printf("Usage: debi [-header] [-no-codebytes] -i=input -o=offset -l=length\n");
				exit(-1);
			}
		

		//////////
		// Open the file specified
		//////
			lfh = fopen(argv[1], "rb+");
			if (!lfh)
			{
				printf("Unable to open %s.\n", argv[1]);
				exit(-2);
			}


		//////////
		// Read the file
		//////
			// File size
			fseek(lfh, 0, SEEK_END);
			length = ftell(lfh);
			fseek(lfh, 0, SEEK_SET);

			// Memory
			data = (u8*)malloc(length);
			if (!data)
			{
				printf("Unable to allocate %u bytes.\n", (int)length);
				exit(-3);
			}

			// Read file contents
			numread = fread(data, 1, length, lfh);
			if (numread != length)
			{
				printf("Could only read %u bytes from %u length file %s.\n", (int)numread, (int)length, argv[1]);
				exit(-4);
			}

			// Close
			fclose(lfh);


		//////////
		// We have our file loaded, now disassemble it
		//////
			lnOffset	= ((argc >= 3) ? lnOffset = atoi(argv[2]) : 0);
			lnLength	= ((argc >= 4) ? lnLength = atoi(argv[3]) : length);


		//////////
		// Disassemble
		//////
			// Identify
			printf("LibSF Debi 0.80 -- Liberty Software Foundation\n");
			printf("Disassembling %s.\n", argv[1]);
			printf("--> Begin at %u, length of %u bytes.\n\n", (int)lnOffset, (int)lnLength);

			// Physically disassemble (writes to stdout)
			debi_disassemble(data + lnOffset, lnLength, 0);


		// Success
		return 0;
	}




;
//////////
//
// 
//
//////
	void debi_disassemble(u8* data, u32 length, u32 address)
	{
		u32				lnCount, lnIterator, lnOffset;		// Offset into the data block of assembly opcodes
		u8*				dd_data_root;
		u8*				op;
		u8*				lcb;
		SDisasmData		dd;									// Disassemble info data structure
		u8				tbuffer1[512];


		// Process through every block until we reach the end
		lnCount			= 0;
		lnOffset		= 0;
		memset(&dd, 0, sizeof(dd));
		dd.data			= data;
		dd.data_root	= data;
		while (lnOffset < length)
		{
			// Update the structure with decoded instruction information
			first_byte_functions[data[lnOffset + dd.opcode_bytes]]
				(data + lnOffset + dd.opcode_bytes, &dd);

			if (dd.opcode_bytes == 0)
				_asm int 3;

			// If there is information, display it
			if (dd.mnemonic)
			{
				// Move to the next position
				lnOffset += dd.opcode_bytes;
				
				// Show address and opcode bytes
				printf("%08X : %02X : ", (int)(address + lnOffset), (int)dd.opcode_bytes);
				for (lnIterator = 0; lnIterator < dd.opcode_bytes; lnIterator++)
					printf("%02x ", (int)dd.data[lnIterator]);
				
				// Update the operand pointer
				if (dd.destination_source_type == Memory)
				{
					switch (dd.operand_size)
					{
						case Byte:
							op = _byte_ptr;
							break;
						case Word:
							op = _word_ptr;
							break;
						case Dword:
							op = _dword_ptr;
							break;
						case Qword:
							op = _qword_ptr;
							break;
						case DQword:
							op = _dqword_ptr;
							break;
						case Tbyte:
							op = _tbyte_ptr;
							break;
						default:
							op = _null_string;
							break;
					}

				} else {
					op = _null_string;
				}
				
				// Upgrade the line_comment buffer
				sprintf((s8*)&tbuffer1[0], "\t\t\t%s", dd.line_comment);
				lcb = dd.line_comment ? &tbuffer1[0] : _null_string;
				
				// Show the instruction
				if (dd.operand1 && dd.operand2 && dd.operand3 && !dd.immediate)
					printf("\n\t%s\t%s,%s,%s%s\n", dd.mnemonic, dd.operand1, dd.operand2, dd.operand3, lcb);
					
				else if (dd.operand1 && dd.operand2 && !dd.immediate)
					printf("\n\t%s\t%s,%s%s\n", dd.mnemonic, dd.operand1, dd.operand2, lcb);
					
				else if (dd.operand1 && !dd.immediate)
					printf("\n\t%s\t%s%s\n", dd.mnemonic, dd.operand1, lcb);
					
				else if (dd.operand1 && dd.operand2 && dd.operand3 && dd.immediate)
					printf("\n\t%s\t%s%s,%s,%s,%s%s\n", dd.mnemonic, op, dd.operand1, dd.operand2, dd.operand3, dd.immediate, lcb);
					
				else if (dd.operand1 && dd.operand2 && dd.immediate)
					printf("\n\t%s\t%s%s,%s,%s%s\n", dd.mnemonic, op, dd.operand1, dd.operand2, dd.immediate, lcb);
					
				else if (dd.operand1 && dd.immediate)
					printf("\n\t%s\t%s%s,%s%s\n", dd.mnemonic, op, dd.operand1, dd.immediate, lcb);
					
				else if (dd.immediate)
					printf("\n\t%s\t%s%s%s\n", dd.mnemonic, op, dd.immediate, lcb);
					
				else
					printf("\n\t%s%s\n", dd.mnemonic, lcb);
					

				// Reset the structure
				dd_data_root	= dd.data_root + dd.opcode_bytes;
 				memset(&dd, 0, sizeof(dd));
				dd.data			= data + lnOffset;
				dd.data_root	= dd_data_root;

				if (dd.data_root != dd.data)
					_asm int 3;	// Oops, these should ALWAYS be in sync

				++lnCount;

			} else {
				_asm nop;
			}
		}
		printf("\nDecoded %u instructions\n", (int)lnCount);
	}




//////////
// 
//////
	#include "disasm.cpp"
