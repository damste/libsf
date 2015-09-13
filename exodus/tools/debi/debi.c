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

// Indicate Debi itself is being compiled, as this disassembler is tightly coupled to lasm, which uses some of debi's data structs
#define _DEBI_COMPILE 1

#include "debi_const.h"
#include "debi_typedefs.h"
#include "debi_structs.h"
#include "debi_defs.h"
#include "debi_globals.h"
#include "disasm_opcodes.h"

// Default to 32-bit instruction encoding
EMode _cpu_mode = _32bit_mode;




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




//////////
// Disassembly code
//////
	#include "disasm.c"
