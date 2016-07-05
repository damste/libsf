//////////
//
// /libsf/exodus/tools/lasm/pass0.cpp
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
// Copyright (c) 2015 by Rick C. Hodgin
//////
// Last update:
//     Sep.13.2015
//////
// Change log:
//     Sep.13.2015 - Initial creation
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
// Liberty Software Foundation's lasm (LibSF Assembler).
//
//////




//////////
//
// Pass-0 -- Conducts these operations:
//
//		fundamental symbols and symbol groupings
//		removes blank lines
//		removes comment lines
//		loads #include files
//		at the end of pass-0, it re-processes #define statements for any nested macros
//
//////
	void ilasm_pass0(SLasmCmdLine* cmdLine, SLasmFile* file)
	{
		SLasmPass0 p0;


		//////////
		// Lex and parse the entire file
		//////
			p0.cmdLine	= cmdLine;
			p0.file		= file;
			for (p0.line = p0.file->firstLine; p0.line; p0.line = p0.line->ll.nextLine)
				iComps_lex_and_parse(p0.line, NULL, &cgcKeywordsLasm[0]);


		//////////
		// Iterate through each line looking for known things
		//////
			for (p0.line = p0.file->firstLine; p0.line; p0.line = p0.line->ll.nextLine)
			{
				// See what was parsed
				p0.comp = p0.line->firstComp;
				if (!p0.comp || p0.comp->iCode == _ICODE_COMMENT)
				{
					// Blank line or comment line
					ilasm_add_lineStatus(p0.line, _LASM_STATUS_COMPLETED, true);
					continue;

				} else if (p0.comp->iCode == _ICODE_LASM_INCLUDE) {
					// include
					if (!iilasm_pass0_include(&p0))
					{
						// If we need to terminate on errors
						if (p0.cmdLine->w.Wfatal_errors)
							return;		// Error was displayed by the called function

					} else {
						// Line is completed
						ilasm_add_lineStatus(p0.line, _LASM_STATUS_COMPLETED, true);
					}
				}
				// else other pragmas are ignored for this pass
			}

	}




//////////
//
// Called to load the indicated file after the indicated line.
//
// Input:
//		p0->line		-- The line p0->comp is on
//		p0->comp		-- include
//
//////
	bool iilasm_pass0_include(SLasmPass0* p0)
	{
		bool	llError;
		s32		lnLineCount;
		cs8*	lcErrorText;


		// The next component needs to be the filename
		llError			= true;
		p0->compFile	= iComps_Nth(p0->comp, 1);

		// We're looking for [include "path\file.ext"]
		do {
			// Entered for structured flow control
			if (p0->compFile && (p0->compFile->iCode == _ICODE_DOUBLE_QUOTED_TEXT || p0->compFile->iCode == _ICODE_SINGLE_QUOTED_TEXT))
			{
				// Copy the filename to a local buffer
				memcpy(p0->fileName, p0->compFile->text.data_s8 + 1, p0->compFile->text.length - 2);
				p0->fileName[p0->compFile->text.length - 2] = 0;

				// Correct the directory dividers to the standard OS form
				ilasm_fixupDirectoryDividers(p0->fileName, p0->compFile->text.length - 2);

				// Try to open it
				if (!ilasm_appendFile(p0->fileName, &p0->fileInclude))
				{
					// Error opening the file
					lcErrorText = (cs8*)"--Error(%d,%d): error opening [#include \"%s\"\n";
					break;
				}
				// File's loaded

				// If we're in verbose mode, display the loaded file
				if (p0->cmdLine->o.lVerbose)
					printf("--include \"%s\"", p0->fileName);

				// Insert its lines after this #include line
				lnLineCount = iLine_migrateLines(&p0->file->firstLine, p0->line);
				if (p0->cmdLine->o.lVerbose)	printf("%d lines\n", lnLineCount);
				else							printf("\n");

				// We're done with the include line
				ilasm_add_lineStatus(p0->line, _LASM_STATUS_COMPLETED, true);

				// We're good, no errors
				llError = false;

			} else {
				// Syntax error
				lcErrorText = "--Error(%d,%d): expected [include \"relative\\path\\to\\file.ext\"] syntax in %s\n";
			}

			// Loop for structured flow control
		} while (0);

		// Was there an error?
		if (llError)
		{
			// Syntax error
			ilasm_add_lineStatus(p0->line, _LASM_STATUS_ERROR, true);
			printf(lcErrorText, p0->line->lineNumber, p0->comp->start, p0->file->filename.data_s8);
		}

		// Indicate our status
		return(!llError);
	}
