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
// Pass-0 -- Load content
//
//		fundamental symbols and symbol groupings
//		removes blank lines
//		removes comment lines
//		loads include files
//
//		once everything's loaded it scans in macros
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
		// Iterate through each line looking for blank lines and include files
		//////
			for (p0.line = p0.file->firstLine; p0.line; p0.line = p0.line->ll.nextLine)
			{
				// See what was parsed
				p0.comp = p0.line->firstComp;
				if (!p0.comp || p0.comp->iCode == _ICODE_COMMENT)
				{
					// Blank line or comment line
					ilasm_status_line_add(p0.line, _LASM_STATUS_COMPLETED, true);
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
						ilasm_status_line_add(p0.line, _LASM_STATUS_COMPLETED, true);
					}
				}
				// else other pragmas are ignored for this pass
			}


		//////////
		// When we get here, all include files are loaded
		// Look for define statements, macros, and conditional assembly (top-down)
		//////
			for (p0.line = p0.file->firstLine; p0.line; p0.line = p0.line->ll.nextLine)
			{
				// Is this line
				if (!ilasm_status_line_isCompleted(p0.line) && (p0.comp = p0.line->firstComp))
				{
					// Is it one we're looking for?
					switch (p0.comp->iCode)
					{
						case _ICODE_LASM_DEFINE:
							ilasm_pass0_define(&p0);
							break;

						case _ICODE_LASM_MACRO:
							ilasm_pass0_macro(&p0);
							break;

						case _ICODE_LASM_IF:
							ilasm_pass0_if(&p0);
							break;

						case _ICODE_LASM_IFDEF:
							ilasm_pass0_ifdef(&p0);
							break;

						case _ICODE_LASM_IFNDEF:
							ilasm_pass0_ifndef(&p0);
							break;

						case _ICODE_LASM_IFB:
							ilasm_pass0_ifb(&p0);
							break;

						case _ICODE_LASM_IFNB:
							ilasm_pass0_ifnb(&p0);
							break;
					}
				}
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
		bool				llError, llIsFileValid;
		s32					lnLineCount, lnFilenameLength;
		cs8*				lcErrorText;
		SLine*				line;
		SLasmIncludeIter	iiFile;


		// The next component needs to be the filename
		llError			= true;
		p0->compFile	= iComps_Nth(p0->comp, 1);

		// We're looking for [include "path\file.ext"]
		do {
			// Entered for structured flow control
			if (p0->compFile && (p0->compFile->iCode == _ICODE_DOUBLE_QUOTED_TEXT || p0->compFile->iCode == _ICODE_SINGLE_QUOTED_TEXT))
			{
				// Copy the filename to a local buffer
				memcpy(p0->filename, p0->compFile->text.data_s8 + 1, p0->compFile->text.length - 2);
				p0->filename[p0->compFile->text.length - 2] = 0;

				// Correct the directory dividers to the standard OS form
				lnFilenameLength = p0->compFile->text.length - 2;
				ilasm_fixup_directoryDividers(p0->filename, lnFilenameLength);

				// Try to open it
				if (!ilasm_includeFile_append(p0->filename, &p0->fileInclude))
				{
					// Is it an absolute path
					if (ilasm_isAbsolutePath(p0->filename, lnFilenameLength))
					{
						// Error opening the file
						lcErrorText = cgc_lasm_error_opening_include_file;
						break;
					}

					// Iterate through the known include file paths and attempt to load its
					ilasm_includePaths_iterate_start(&iiFile, p0->filename);
					while (!iiFile.wasOpened)
					{
						// Try to open it
						if (ilasm_includePaths_iterate_try(&iiFile, llIsFileValid, &p0->fileInclude))
						{
							// It was opened
							break;

						} else if (!llIsFileValid) {
							// Something was wrong with the filename (the path might be too long)
							// We ignore it... it will eventually fall through and error out if it's not found elsewhere
						}

						// Move to the next iteration
						if (!ilasm_includePaths_iterate_next(&iiFile))
						{
							// Error opening the file
							lcErrorText = cgc_lasm_error_opening_include_file;
							break;
						}
					}

					// Was the file loaded?
					if (!iiFile.wasOpened)
					{
						// Nope
						lcErrorText = cgc_lasm_error_opening_include_file;
						break;
					}
				}
				// File's loaded

				// If we're in verbose mode, display the loaded file
				if (p0->cmdLine->o.lVerbose)
					printf("--include \"%s\"", p0->filename);

				// Lex and parse the include file content
				for (line = p0->fileInclude->firstLine; line; line = line->ll.nextLine)
					iComps_lex_and_parse(line, NULL, &cgcKeywordsLasm[0]);

				// Insert its lines after this #include line
				lnLineCount = iLine_migrateLines(&p0->fileInclude->firstLine, p0->line);
				if (p0->cmdLine->o.lVerbose)
					printf(", %d lines\n", lnLineCount);

				// We're done with the include line, no errors
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
			ilasm_status_line_add(p0->line, _LASM_STATUS_ERROR, true);
			printf(lcErrorText, p0->line->lineNumber, p0->comp->start, p0->file->filename.data_s8);
		}

		// Indicate our status
		return(!llError);
	}




//////////
//
// Called to define a token and associated value
//
// Syntax:
// 		define name value
// 		define name(...) value
//
// Or:
//		define name {{ content...
//			...goes...
//		...here }}
// Or:
//		define name(...) {{ content...
//			...goes...
//		...here }}
//
//////
	bool ilasm_pass0_define(SLasmPass0* p0)
	{
		SLine*		lineMark;
		SComp*		compDefine;
		SComp*		compTokenName;
		SComp*		compThingAfterName;
		SComp*		compContentStart;
		SComp*		compContentEnd;
		SBuilder*	compParams;


		// Make sure our environment is sane
		if (p0 && p0->line && (compDefine = p0->line->firstComp))
		{
			// Is it define?
			if (compDefine->iCode == _ICODE_LASM_DEFINE)
			{
				// Grab the token name after it
				compTokenName = iComps_Nth_lineOnly(compDefine);
				if (compTokenName)
				{
					// Grab the thing after that
					compParams			= NULL;
					compThingAfterName	= iComps_Nth_lineOnly(compTokenName);
					if (compThingAfterName)
					{
						// Content assigned to the token name
						switch (compThingAfterName->iCode)
						{
							case _ICODE_DOUBLE_BRACE_LEFT:
								// It's {{ so it indicates a block
								compContentStart	= iComps_Nth(compThingAfterName);
								compContentEnd		= iComps_findNextBy_iCode(compThingAfterName, _ICODE_DOUBLE_BRACE_RIGHT);
								if (!compContentStart || !compContentEnd)
								{
									// Syntax error
									debug_error;
									return(false);
								}

								// Back up one before the right double-brace
								compContentEnd = iComps_Nth(compContentEnd, -1);

							case _ICODE_PARENTHESIS_LEFT:
								// define(...)
								iilasm_params_extract(compThingAfterName, &compParams);
								break;

							default:
								// It's everything from here to the end of line
								compContentStart	= compThingAfterName;
								compContentEnd		= iiLine_getLastComp(p0->line, compThingAfterName);
								break;
						}

					} else {
						// No content, just definition of the token name
						compContentStart	= NULL;
						compContentEnd		= NULL;
					}

					// When we get here, we have all the information we need
					iilasm_define_add(p0->file, p0->line, compTokenName, compParams, compContentStart, compContentEnd);

					// Mark everything completed
					ilasm_status_line_isCompleted(p0->line);
					if (compContentStart && compContentEnd && compContentStart->line != compContentEnd->line)
					{
						// Mark the other lines complete
						for (lineMark = p0->line->ll.nextLine; lineMark; lineMark = lineMark->ll.nextLine)
						{
							// Mark this line
							ilasm_status_line_isCompleted(lineMark);

							// Are we done?
							if (lineMark == compContentEnd->line)
								break;	// Yes
						}
					}

				} else {
					// Syntax error
					debug_error;
					return(false);
				}
			}
		}

		// If we get here, failure
		debug_error;		// Internal error, should never happen
		return(false);
	}




//////////
//
// Called to define a macro
//
// 		macro callfp
// 		|| _seg
// 		|| _offset
// 		{{
// 		// This macro:   callfp  _code_seg, _offset
// 		//
// 			u8  9ah
// 			u32 _offset
// 			u16 _seg
// 		}}
// 
//////
	bool ilasm_pass0_macro(SLasmPass0* p0)
	{
		return(false);
	}




//////////
//
// Called to see if the if expression is one of conditional assembly, or if it's of logic
//
//////
	bool ilasm_pass0_if(SLasmPass0* p0)
	{
		return(false);
	}




//////////
//
// Called to see if the token is defined
//
//////
	bool ilasm_pass0_ifdef(SLasmPass0* p0)
	{
		return(false);
	}




//////////
//
// Called to see if the token is not defined
//
//////
	bool ilasm_pass0_ifndef(SLasmPass0* p0)
	{
		return(false);
	}




//////////
//
// Called to see if the token is blank (not present)
//
//////
	bool ilasm_pass0_ifb(SLasmPass0* p0)
	{
		return(false);
	}




//////////
//
// Called to define a token is not blank (present)
//
//////
	bool ilasm_pass0_ifnb(SLasmPass0* p0)
	{
		return(false);
	}
