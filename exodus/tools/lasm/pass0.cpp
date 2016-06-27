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
//		stores #define statements
//		at the end of pass-0, it re-processes #define statements for any nested macros
//
//////
	void ilasm_pass0(SLasmCmdLine* cmdLine, SLasmFile* file)
	{
		SLasmPass0 p0;


		// Iterate through the entire file
		p0.cmdLine	= cmdLine;
		p0.file		= file;
		for (p0.comp = iLine_Nth_comp(p0.file->firstLine); p0.comp; p0.comp = iComps_Nth(p0.comp))
		{

			//////////
			// See what was parsed
			//////
				if (p0.comp->iCode == _ICODE_COMMENT || !(iilasm_pass0_parse(&p0), p0.comp))
				{
					// Blank line or comment line
					continue;

				} else if (p0.comp->iCode != _ICODE_POUND_SIGN) {
					// It's not a pragma
					continue;

				} else if (!(p0.compNext = iComps_Nth(p0.comp))) {
					// Syntax error
					++p0.comp->line->status.errors;
					printf("--Error(%d,%d): Missing identifier after #\n", p0.comp->line->lineNumber, p0.compNext->start);
				}


			///////////
			// Pass-0 only supports #include, #define
			//////
				if (p0.compNext->iCode == _ICODE_LASM_INCLUDE)
				{
					// #include
					iilasm_pass0_include(&p0);

				} else if (p0.compNext->iCode == _ICODE_LASM_DEFINE) {
					// #define
					if (!iilasm_pass0_define(&p0))
					{
						// If we need to terminate on errors
						if (p0.cmdLine->w.Wfatal_errors)
							return;		// Error was displayed by the called function
					}

					// This line is completed, but the file itself is not
					p0.comp->line->status.isCompleted = true;
				}

		}
	}

	// p0->comp		-- #include
	// p0->compNext	-- Pointing to the thing after the #include statement
	void iilasm_pass0_include(SLasmPass0* p0)
	{
		// The next component needs to be the filename
		if ((p0->compFile = iComps_Nth(p0->compNext)) && (p0->compFile->iCode == _ICODE_DOUBLE_QUOTED_TEXT || p0->compFile->iCode == _ICODE_SINGLE_QUOTED_TEXT))
		{
			// Copy the filename to a local buffer
			memcpy(p0->fileName, p0->compFile->line->sourceCode->data._s8 + p0->compFile->start + 1, p0->compFile->length - 2);
			p0->fileName[p0->compFile->length - 2] = 0;

			// Correct the directory dividers to the standard OS form
			ilasm_fixupDirectories(p0->fileName, p0->compFile->length - 2);

			// Try to open it
			if (!ilasm_appendFile(p0->fileName, &p0->fileInclude))
			{
				// Error opening the file
				++p0->compFile->line->status.errors;
				printf("--Error(%d,%d): error opening [#include \"%s\"\n", p0->compFile->line->lineNumber, p0->compNext->start, p0->fileName);
				return;
			}
			// File's loaded

			// If we're in verbose mode, display the loaded file
			if (p0->cmdLine->o.lVerbose)
				printf("--#include \"%s\"\n", p0->fileName);

			// Insert its lines after this #include line
			iLine_migrateLines(&p0->file->firstLine, p0->compNext->line);

			// We're done with the #include line
			p0->fileInclude->status.isCompleted		= true;
			p0->compFile->line->status.isCompleted	= true;
			// Note:  line->ll.nextLine is now pointing to the #include file source code


		} else {
			// Syntax error
			++p0->compNext->line->status.errors;
			printf("--Error(%d,%d): expected [#include \"relative\\path\\to\\file.ext\"] syntax in %s\n", p0->compNext->line->lineNumber, p0->compNext->start, p0->file->fileName.data._s8);
			return;
		}
	}




//////////
//
// Parses out the raw source code bytes into SComp items with an iCode
//
//////
	void iilasm_pass0_parse(SLasmPass0* p0)
	{
		SLine* line;


		//////////
		// If we have existing compiler data, get rid of it
		//////
			line = p0->comp->line;
			if (line->compilerInfo)		iCompiler_delete(&line->compilerInfo, false);
			else						line->compilerInfo = iCompiler_allocate(line);		// Allocate a new one


		// Loop added only for structured exit
		do {

			// Parse out the line fundamentally
			iComps_translate_sourceLineTo(&cgcFundamentalSymbols[0], line);
			if (!line->compilerInfo->firstComp)
				break;		// Nothing to compile on this line


			// If it's a line comment, we don't need to process it
			iComps_remove_leadingWhitespaces(line);
			iComps_remove_startEndComments(line);					// Removes /*comments*/ and /+comments+/
			if (!line->compilerInfo->firstComp)
				break;


			// If it's a line comment, we're done
			if (line->compilerInfo->firstComp->iCode == _ICODE_COMMENT || line->compilerInfo->firstComp->iCode == _ICODE_LINE_COMMENT)
			{
				// Combine every item after this to a single comment
				iComps_combineN(line->compilerInfo->firstComp, 99999, _ICODE_COMMENT, line->compilerInfo->firstComp->iCat, line->compilerInfo->firstComp->color);
				break;
			}


			// Perform natural source code fixups
			iComps_fixup_naturalGroupings(line);				// Fixup natural groupings [_][aaa][999] becomes [_aaa999], [999][.][99] becomes [999.99], etc.
			iComps_remove_whitespaces(line);					// Remove all whitespaces after everything else was parsed [use][whitespace][foo] becomes [use][foo]
			if (!line->compilerInfo->firstComp)
				break;


			// Remove or replace ||| and |||| portions
			iComps_combine_adjacentLeadingPipesigns(line);		// Combines each leading ||| to whitespace, and |||| (or longer) to a line comment

			// We may have re-introduced a || whitespace, which would've been removed above
			if (line->compilerInfo->firstComp->iCode == _ICODE_WHITESPACE)
			{
				iComps_remove_whitespaces(line);
				if (!line->compilerInfo->firstComp)
					break;
			}

			// We may have re-introduced line comments (by converting ||| (or longer) to a line comment)
			if (iiComps_isComment(line->compilerInfo->firstComp->iCode))
			{
				iComps_truncate_atComments(line);
				if (!line->compilerInfo->firstComp)
					break;
			}


			// Translate remaining sequences to known lasm keywords
			iComps_translate_toOthers((SAsciiCompSearcher*)&cgcKeywordsLasm[0], line->compilerInfo->firstComp);

		} while (0);
	}




//////////
//
// Parses out #define syntax, creating a new SLasmDefine structure if valid.
//
//////
//
// Syntax must be:
//
//		"#define"
//		name
//
//		optional "("
//			:repeat until matching ")"
//				name
//					optional ,
//						loop
//					else
//						exit
//			:end
//
//		optional {
//			all content to matching }, with every intermediate \} escaped
//		optional {{
//			all content to matching }}, with every intermediate \} escaped
//		else
//			:repeat
//				all content to end of line
//				optional "\"
//					next line
//					loop
//				else
//					exit
//			:end
//
//////
	// Note:  It is known that when this function is called, the first component is _ICODE_LASM_DEFINE
	bool iilasm_pass0_define(SLasmPass0* p0)
	{
// 		SComp*			compDefine;
// 		SComp*			compName;
// 		SCallback		cb;
// 		s8				buffer1[_MAX_FNAME];
// 		s8				buffer2[_MAX_FNAME];
// 		
// 		
// 		//////////
// 		// Is there a valid component?
// 		//////
// 			compDefine	= p0->compNext;
// 			compName	= iComps_Nth(compDefine);
// 			if (!compName)
// 			{
// 				// It's a #define but nothing comes after
// 				++compDefine->line->status.errors;
// 				printf("--Error(%d,%d): token was expected in %s\n", compDefine->line->lineNumber, compDefine->start + compDefine->length, p0->file->fileName.data._s8);
// 				goto politely_fail;
// 			}
// 
// 
// 		//////////
// 		// Validate that it's alphanumeric
// 		//////
// 			if (!iiComps_isAlphanumeric_byContent(compName))
// 			{
// 				++compName->line->status.errors;
// 				printf("--Error(%d,%d): alphanumeric was expected in %s\n", compName->line->lineNumber, compName->start, p0->file->fileName.data._s8);
// 				goto politely_fail;
// 			}
// 
// 
// 		//////////
// 		// Validate it's a unique symbol
// 		//////
// 			if ((p0->define = iilasm_pass0_lookup_define_byName(compName, gsLasmDefines)))
// 			{
// 				// It was already found
// 				memcpy(buffer1, p0->define->compName->line->sourceCode->data._s8 + p0->define->compName->start, p0->define->compName->length);
// 				memcpy(buffer2, p0->file->fileName.data._s8, p0->file->fileName.length);
// 				buffer1[p0->define->compName->length]	= 0;
// 				buffer2[p0->file->fileName.length]	= 0;
// 				printf("--Error(%d,%d): token '%s' already defined in %s on (%d,%d)\n", compName->line->lineNumber, compName->start, buffer1, buffer2, p0->define->compName->line->lineNumber, p0->define->compName->start);
// 			}
// 
// 
// 		//////////
// 		// Grab it
// 		//////
// 			p0->define = newAlloc(SLasmDefine, gsLasmDefines);
// 			if (!p0->define)
// 			{
// 				// Internal error
// 				++compName->line->status.errors;
// 				printf("--Error(%d): an unexpected internal error occurred processing a #define in %s\n", compName->line->lineNumber, p0->file->fileName.data._s8);
// 				goto politely_fail;
// 			}
// 
// 			// Copy the name
// 			p0->define->compName = compName;
// 
// 
// 		//////////
// 		// Load any optional parameters
// 		//////
// 			if ((p0->compNext = iComps_Nth(compName, 1, false)))
// 			{
// 				// Does it have parameters?
// 				if (p0->compNext->iCode == _ICODE_PARENTHESIS_LEFT)
// 				{
// 					// It begins with an open parenthesis
// 					if (!iilasm_pass0_define__getParameters(p0))
// 					{
// 						++p0->compNext->line->status.errors;
// 						printf("--Error(%d,%d): unable to parse parameters in %s\n", p0->compNext->line->lineNumber, p0->compNext->start, p0->file->fileName.data._s8);
// 						goto politely_fail;
// 					}
// 					// When we get here, line and compNext are pointing to the closing )
// 
// 					// Skip past the closing )
// 					if (!(p0->compNext = iComps_Nth(p0->compNext)))
// 					{
// 						++p0->comp->line->status.errors;
// 						printf("--Error: unexpected end of file in %s\n", p0->file->fileName.data._s8);
// 						goto politely_fail;
// 					}
// 					// When we get here, we're on the first component after
// 				}
// 
// 				// Is it brace content
// 				if (p0->compNext->iCode == _ICODE_BRACE_LEFT || p0->compNext->iCode == _ICODE_DOUBLE_BRACE_LEFT)
// 				{
// 					// Begins with {/{{, we need to find the closing }}/}
// 					memset(&cb, 0, sizeof(cb));
// 					if (!iComps_scanForward_withCallback(p0->compNext, &cb, true, (uptr)&iilasm_pass0_define__callback_bypassEscapedBraces))
// 					{
// 						// Not found
// 						++p0->compNext->line->status.errors;
// 						printf("--Error(%d,%d): unable to locate matching } %s\n", p0->compNext->line->lineNumber, p0->compNext->start + p0->compNext->length, p0->file->fileName.data._s8);
// 						goto politely_fail;
// 					}
// 
// 					// Move to post-{/{{ and pre-}/}}
// 					p0->comp	= iComps_Nth(p0->comp);
// 					cb.comp		= iComps_Nth(cb.comp, -1);
// 
// 					// Copy inner content (between the { and }, and excluding those two characters)
// 					p0->define->firstLine = iComps_copyComps_toNewLines(p0->comp, cb.comp, true, true);
// 
// 				} else {
// 					// Copy everything, including multiple lines ending in '\'
// 					p0->define->firstLine = iLine_copyComps_toNewLines_untilTerminating(p0->line, compNext, _ICODE_BACKSLASH, true, true, &cb);
// 				}
// 				// If we get here, success
// 
// 				// Unescape \{, \}, \{{, \}}, and \\ within the block
// 				iLines_unescape_iCodes(p0->define->firstLine,	_ICODE_BRACE_LEFT,			_ICODE_BRACE_RIGHT,			_ICODE_BACKSLASH);
// 				iLines_unescape_iCodes(p0->define->firstLine,	_ICODE_DOUBLE_BRACE_LEFT,	_ICODE_DOUBLE_BRACE_RIGHT,	-1);
// 			}
// 
// 
// 		//////////
// 		// Position our line to the last location, which completes the #define
// 		//////
// 			p0->line = cb.line;
// 
// 
// 
// politely_fail:
// 		// If we get here, error
		return(false);
	}

	// Uses cb->value for iCode
	bool iilasm_pass0_define__callback_bypassEscapedBraces(SCallback* cb)
	{
		SComp* compNext;


		//////////
		// Is it a \{ or \} ?
		//////
			if (cb->comp->iCode == _ICODE_BACKSLASH)
			{
				// Grab the next component
				compNext = cb->comp->ll.nextComp;

				// Is it { or } ?
				if (compNext && (compNext->iCode == _ICODE_BRACE_LEFT || compNext->iCode == _ICODE_DOUBLE_BRACE_LEFT || compNext->iCode == _ICODE_BRACE_RIGHT || compNext->iCode == _ICODE_DOUBLE_BRACE_RIGHT))
				{
					// Yes, but are they directly adjacent?
					if (iiComps_areCompsAdjacent(cb->comp, compNext))
					{
						// Yes, so skip this one because it's escaped
						cb->comp = compNext;

						// Go ahead and keep looking after these two components are skipped
						return(true);
					}
				}
			}
		

		//////////
		// Is it our target }?
		//////
			if (cb->comp->iCode == cb->iCode)
			{
				cb->flag = true;	// Found it
				return(false);		// Yes, so indicate there should be no more searching
			}


		//////////
		// If we get here, not found, so continue on searching
		//////
			return(true);

	}




//////////
//
// Called to extract parameters from a (a,b,...,z) sequence
// Note:  Upon entry the *compProcessing should be pointing to _ICODE_PARENTHESIS_LEFT
//
//////
	bool iilasm_pass0_define__getParameters(SLasmPass0* p0)
	{
// 		s32		lnI;
// 		bool	llSkipTest;
// 		SComp*	comp;
// 
// 
// 		//////////
// 		// Should be on opening parenthesis
// 		//////
// 			if (comp->iCode != _ICODE_PARENTHESIS_LEFT)
// 			{
// 				++p0->line->status.errors;
// 				printf("--Error(%d,%d): unexpected internal error processing #define parameters %s\n", p0->line->lineNumber, comp->start, p0->file->fileName.data._s8);
// 				return(false);
// 			}
// 
// 
// 		//////////
// 		// Iterate loading each one
// 		//////
// 			for (lnI = 0, llSkipTest = false; lnI < _LASM_MAX_DEFINE_PARAMS && comp->iCode != _ICODE_PARENTHESIS_RIGHT; lnI++)
// 			{
// 
// 				//////////
// 				// Validate it's a token
// 				//////
// 					if (!llSkipTest && !iiComps_isAlphanumeric_by_iCode(comp))
// 					{
// 						++p0->line->status.errors;
// 						printf("--Error(%d,%d): expected token in %s\n", p0->line->lineNumber, comp->start, p0->file->fileName.data._s8);
// 						goto politely_fail;
// 					}
// 					llSkipTest = false;
// 
// 
// 				//////////
// 				// Increase count, grab the name
// 				//////
// 					++p0->define->paramCount;
// 					iiDatum_duplicate_fromComp(&p0->define->params[lnI], comp);
// 
// 
// 				//////////
// 				// Skip to next parameter
// 				//////
// 					if (iiLine_skipTo_nextComp(&p0->line, &comp) < 0)
// 					{
// 						// Unexpected end of file
// 						printf("--Error: unexpected end of file in %s\n", p0->file->fileName.data._s8);
// 						goto politely_fail;
// 					}
// 
// 
// 				//////////
// 				// Skip past comma
// 				//////
// 					if (comp->iCode == _ICODE_COMMA)
// 					{
// 
// 						//////////
// 						// Skip past it
// 						//////
// 							if (iiLine_skipTo_nextComp(&p0->line, &comp) < 0)
// 							{
// 								// Unexpected end of file
// 								printf("--Error: unexpected end of file in %s\n", p0->file->fileName.data._s8);
// 								goto politely_fail;
// 							}
// 
// 
// 						//////////
// 						// Next component must be right parenthesis or alphanumeric
// 						//////
// 							if (comp->iCode != _ICODE_PARENTHESIS_RIGHT && !iiComps_isAlphanumeric_by_iCode(comp))
// 							{
// 								++p0->line->status.errors;
// 								printf("--Error(%d,%d): expected token or right parenthesis in %s\n", p0->line->lineNumber, comp->start, p0->file->fileName.data._s8);
// 								goto politely_fail;
// 							}
// 
// 							// We don't need to double-check alphanumeric above
// 							llSkipTest = true;
// 
// 					}
// 					// When we get here, we're on either ) or the next token name
// 
// 			}
// 			// When we get here, comp is sitting on )
// 
// 
// 		//////////
// 		// Success!
// 		//////
// 			*compProcessing = comp;
// 			return(true);
// 
// 
// politely_fail:
// 		//////////
// 		// Set current parameters, and then return false
// 		//////
// 			*compProcessing = comp;
			return(false);
	}




//////////
//
// Lookup the #define by name
//
//////
	SLasmDefine* iilasm_pass0_lookup_define_byName(SComp* compName, SLasmDefine* defineRoot)
	{
		SLasmDefine* define;


		// Iterate through the defines
		for (define = defineRoot; define; define = (SLasmDefine*)define->ll.next)
		{
			// Is it the same length?
			if (define->compName->length == compName->length)
			{
				// Is it the same name?
				if (_memicmp(	define->compName->line->sourceCode->data._s8 +  define->compName->start,
										compName->line->sourceCode->data._s8 +			compName->start,
										compName->length)
						== 0)
				{
					// Yes, this is the symbol
					return(define);
				}
			}
		}

		// If we get here, not found
		return(NULL);
	}
