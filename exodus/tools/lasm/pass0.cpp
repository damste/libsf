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
// Pass-0 -- Parse each line and conduct these operations:
//
//		blank lines
//		comment lines
//		#include files
//		#define statements
//		labels
//		function starts and stops
//		flow control starts and stops
//
//////
	void ilasm_pass0(SLasmFile* file)
	{
		SLine*		line;
		SComp*		comp;
		SComp*		compNext;
		SComp*		compFile;
		SLasmFile*	fileInclude;
		s8			fileName[_MAX_PATH];


		// Iterate through the entire file
		for (line = file->firstLine; line; line = line->ll.nextLine)
		{
			// Parse it
			comp = ilasm_pass0_parse(line);
			if (!comp)
			{
				// Blank line
				line->status.isCompleted = true;

			} else {
				// See if we're done
				if (comp->iCode == _ICODE_COMMENT)
				{
					// Comment, we're done
					line->status.isCompleted = true;

				} else if (compNext = iComps_getNth(NULL, comp, 1)) {
					// # prefix
					if (comp->iCode == _ICODE_POUND_SIGN)
					{
						// #include
						if (compNext->iCode == _ICODE_LASM_INCLUDE)
						{
							// The next component needs to be the filename
							if ((compFile = iComps_getNth(NULL, compNext, 1)) && (compFile->iCode == _ICODE_DOUBLE_QUOTED_TEXT || compFile->iCode == _ICODE_SINGLE_QUOTED_TEXT))
							{
								// Copy the filename to a local buffer
								memcpy(fileName, line->sourceCode->data_s8 + compFile->start, compFile->length);
								fileName[compFile->length] = 0;

								// Try to open it
								if (!ilasm_appendFile(fileName, &fileInclude))
								{
									// Error opening the file
									++line->status.errors;
									printf("--Error(%d,%d): error opening [#include \"%s\"\n", line->lineNumber, compNext->start, fileName);
									return;
								}
								// We have the file loaded

								// Insert its lines after this #include line
								iLine_migrateLines(NULL, &file->firstLine, line);

								// We're done
								fileInclude->status.isCompleted	= true;
								line->status.isCompleted		= true;

							} else {
								// Syntax error
								++line->status.errors;
								printf("--Error(%d,%d): expected [#include \"path\to\file.ext\"] syntax in %s\n", line->lineNumber, compNext->start, file->fileName.data_s8);
								return;
							}

						} else if (compNext->iCode == _ICODE_LASM_DEFINE) {
							// #define
							if (!ilasm_pass0_define(file, &line, compNext, iComps_getNth(NULL, compNext, 1)))
								return;		// Error is displayed by the called function

							// This line is completed, but the file itself is not
							line->status.isCompleted = true;
						}

					} else if (compNext->iCode == _ICODE_LASM_FUNCTION) {
						// function
// TODO:  Working here

					} else if (compNext->iCode == _ICODE_LASM_FLOWOF) {
						// flowof
// TODO:  Working here

					} 
				}
			}
		}
	}




//////////
//
// Parses out the raw source code bytes into SComp items with an iCode
//
//////
	SComp* ilasm_pass0_parse(SLine* line)
	{

		//////////
		// If we have existing compiler data, get rid of it
		//////
			if (line->compilerInfo)		iCompiler_delete(NULL, &line->compilerInfo, false);
			else						line->compilerInfo = iCompiler_allocate(NULL, line);		// Allocate a new one


		// Loop added only for structured exit
		while (1)
		{

			//////////
			// Parse out the line fundamentally
			//////
				iComps_translateSourceLineTo(NULL, &cgcFundamentalSymbols[0], line);
				if (!line->compilerInfo->firstComp)
					break;		// Nothing to compile on this line


			//////////
			// If it's a line comment, we don't need to process it
			//////
				iComps_removeLeadingWhitespaces(NULL, line);
				iComps_removeStartEndComments(NULL, line);				// Removes /* comments */
				if (!line->compilerInfo->firstComp)
					break;

				// If it's a line comment, we're done
				if (line->compilerInfo->firstComp->iCode == _ICODE_COMMENT || line->compilerInfo->firstComp->iCode == _ICODE_LINE_COMMENT)
				{
					// Combine every item after this to a single comment
					iComps_combineN(NULL, line->compilerInfo->firstComp, 99999, _ICODE_COMMENT, line->compilerInfo->firstComp->iCat, line->compilerInfo->firstComp->color);
					break;
				}


			//////////
			// Perform natural source code fixups
			//////
				iComps_fixupNaturalGroupings(NULL, line);				// Fixup natural groupings [_][aaa][999] becomes [_aaa999], [999][.][99] becomes [999.99], etc.
				iComps_removeWhitespaces(NULL, line);					// Remove all whitespaces after everything else was parsed [use][whitespace][foo] becomes [use][foo]
				if (!line->compilerInfo->firstComp)
					break;


			//////////
			// Remove or replace || and ||| portions
			//////
				iComps_combineAdjacentLeadingPipesigns(NULL, line);		// Combines each leading || to whitespace, and ||| (or longer) to a line comment

				// We may have re-introduced a || whitespace, which would've been removed above
				if (line->compilerInfo->firstComp->iCode == _ICODE_WHITESPACE)
				{
					iComps_removeWhitespaces(NULL, line);
					if (!line->compilerInfo->firstComp)
						break;
				}

				// We may have re-introduced line comments (by converting ||| (or longer) to a line comment)
				if (iiComps_isComment(line->compilerInfo->firstComp->iCode))
				{
					iComps_truncateAtComments(NULL, line);
					if (!line->compilerInfo->firstComp)
						break;
				}


			//////////
			// Translate remaining sequences to known lasm keywords
			//////
				iComps_translateToOthers(NULL, (SAsciiCompSearcher*)&cgcKeywordsLasm[0], line);


			// Exit for structured programming
			break;
		}

		// Return the first component
		return(line->compilerInfo->firstComp);
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
	bool ilasm_pass0_define(SLasmFile* file, SLine** lineProcessing, SComp* compDefine, SComp* compName)
	{
		SLine*			line;
		SComp*			compNext;
		SLasmDefine*	define;
		SCallback		cb;


		// Make sure our environment is sane
		if (lineProcessing && (line = *lineProcessing))
		{
			// Is there a valid component?
			if (compName)
			{

				//////////
				// Validate it's alphanumeric
				//////
					if (!iiComps_isAlphanumeric(NULL, compName))
					{
						++line->status.errors;
						printf("--Error(%d,%d): alphanumeric was expected in %s\n", line->lineNumber, compName->start, file->fileName.data_s8);
						goto politely_fail;
					}


				//////////
				// Grab it
				//////
					define = newAlloc(SLasmDefine, gsLasmDefines);
					if (!define)
					{
						// Internal error
						++line->status.errors;
						printf("--Error(%d): an unexpected internal error occurred processing a #define in %s\n", line->lineNumber, file->fileName.data_s8);
						goto politely_fail;
					}

					// Copy the name
					iiDatum_duplicate_fromComp(&define->name, compName);


				//////////
				// Load any optional parameters
				//////
					compNext = iComps_getNth(NULL, compName, 1);
					if (compNext->iCode == _ICODE_PARENTHESIS_LEFT)
					{
						// It begins with an open parenthesis
						if (!iilasm_pass0_define__getParameters(file, define, &line, &compNext))
						{
							++line->status.errors;
							printf("--Error(%d,%d): unable to parse parameters in %s\n", line->lineNumber, compNext->start, file->fileName.data_s8);
							goto politely_fail;
						}
						// When we get here, line and compNext are pointing to the closing )

						// Skip past the closing )
						if (!iiLine_skipTo_nextComp(NULL, &line, &compNext))
						{
							++line->status.errors;
							printf("--Error: unexpected end of file in %s\n", file->fileName.data_s8);
							goto politely_fail;
						}
						// When we get here, we're on the first component after
					}


				//////////
				// Is it brace content
				//////
					if (compNext->iCode == _ICODE_BRACE_LEFT)
					{

						//////////
						// Begins with {
						//////
							// Find closing }
							memset(&cb, 0, sizeof(cb));
							cb._func = (sptr)&iilasm_pass0_define__callback_bypassEscapedBraces;
							if (!iLine_scanComps_forward_withCallback(NULL, line, compNext, &cb, true))
							{
								// Not found
								++line->status.errors;
								printf("--Error(%d,%d): unable to locate matching } %s\n", line->lineNumber, compNext->start + compNext->length, file->fileName.data_s8);
								goto politely_fail;
							}
							// Found closing }


						///////////
						// Move to post-{ and pre-}
						//////
							iiLine_skipTo_nextComp(NULL,	&line,		&compNext);
							iiLine_skipTo_prevComp(NULL,	&cb.line,	&cb.comp);


						//////////
						// Copy
						//////
							define->firstLine = iLine_copyComps_toNewLines(NULL, line, compNext, cb.line, cb.comp, true, true);


						//////////
						// Unescape \{, \}, and \\
						//////
							iLines_unescape_iCodes(NULL, define->firstLine, _ICODE_BRACE_LEFT,	_ICODE_BRACE_RIGHT, _ICODE_BACKSLASH);


					} else {
						// Copy everything, including any continued lines (lines ending with \)
						define->firstLine = iLine_copyComps_toNewLines_untilTerminating(NULL, line, compNext, _ICODE_BACKSLASH, true, true);

					}
					// If we get here, success

					// Position our line and component to the last location, ready for our next skip
					line		= cb.line;
					compNext	= cb.comp;

			} else {
				// It's a #define but nothing comes after
				++line->status.errors;
				printf("--Error(%d,%d): token was expected in %s\n", line->lineNumber, compDefine->start + compDefine->length, file->fileName.data_s8);
				goto politely_fail;
			}

		} else {
			printf("--Error: an unexpected internal error occurred processing a #define in %s\n", file->fileName.data_s8);
			goto politely_fail;
		}


politely_fail:
		// If we get here, error
		*lineProcessing = line;
		return(false);
	}

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
				if (compNext && (compNext->iCode == _ICODE_BRACE_LEFT || compNext->iCode == _ICODE_BRACE_RIGHT))
				{
					// Yes, but are they directly adjacent?
					if (iiComps_areCompsAdjacent(NULL, cb->comp, compNext))
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
			if (cb->comp->iCode == _ICODE_BRACE_RIGHT)
				return(false);	// Yes, so indicate there should be no more searching


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
	bool iilasm_pass0_define__getParameters(SLasmFile* file, SLasmDefine* define, SLine** lineProcessing, SComp** compProcessing)
	{
		s32		lnI;
		bool	llSkipTest;
		SComp*	comp;
		SLine*	line;


		//////////
		// Grab our real parameters
		//////
			comp = *compProcessing;
			line = *lineProcessing;


		//////////
		// Should be on opening parenthesis
		//////
			if (comp->iCode != _ICODE_PARENTHESIS_LEFT)
			{
				++line->status.errors;
				printf("--Error(%d,%d): unexpected internal error processing #define parameters %s\n", line->lineNumber, comp->start, file->fileName.data_s8);
				return(false);
			}


		//////////
		// Iterate loading each one
		//////
			for (lnI = 0, llSkipTest = false; lnI < _MAX_LASM_DEFINE_PARAMS && comp->iCode != _ICODE_PARENTHESIS_RIGHT; lnI++)
			{

				//////////
				// Validate it's a token
				//////
					if (!llSkipTest && !iiComps_isAlphanumeric(NULL, comp))
					{
						++line->status.errors;
						printf("--Error(%d,%d): expected token in %s\n", line->lineNumber, comp->start, file->fileName.data_s8);
						goto politely_fail;
					}
					llSkipTest = false;


				//////////
				// Increase count, grab the name
				//////
					++define->paramCount;
					iiDatum_duplicate_fromComp(&define->params[lnI], comp);


				//////////
				// Skip to next parameter
				//////
					if (iiLine_skipTo_nextComp(NULL, &line, &comp) < 0)
					{
						// Unexpected end of file
						printf("--Error: unexpected end of file in %s\n", file->fileName.data_s8);
						goto politely_fail;
					}


				//////////
				// Skip past comma
				//////
					if (comp->iCode == _ICODE_COMMA)
					{

						//////////
						// Skip past it
						//////
							if (iiLine_skipTo_nextComp(NULL, &line, &comp) < 0)
							{
								// Unexpected end of file
								printf("--Error: unexpected end of file in %s\n", file->fileName.data_s8);
								goto politely_fail;
							}


						//////////
						// Next component must be right parenthesis or alphanumeric
						//////
							if (comp->iCode != _ICODE_PARENTHESIS_RIGHT && !iiComps_isAlphanumeric(NULL, comp))
							{
								++line->status.errors;
								printf("--Error(%d,%d): expected token or right parenthesis in %s\n", line->lineNumber, comp->start, file->fileName.data_s8);
								goto politely_fail;
							}

							// We don't need to double-check alphanumeric above
							llSkipTest = true;

					}
					// When we get here, we're on either ) or the next token name

			}
			// When we get here, comp is sitting on )


		//////////
		// Success!
		//////
			*lineProcessing = line;
			*compProcessing = comp;
			return(true);


politely_fail:
		//////////
		// Set current parameters, and then return false
		//////
			*lineProcessing = line;
			*compProcessing = comp;
			return(false);
	}
