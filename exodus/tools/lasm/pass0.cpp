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
// Pass-0 -- Parse each line and load #include files
//
//////
	void ilasm_pass0(SLasmFile* file)
	{
		SLine*	line;
		SComp*	comp;
		SComp*	compNext;


		// Iterate through the entire file
		for (line = file->firstLine; line; line = line->ll.nextLine)
		{
			// Parse it
			comp = ilasm_pass0_parse(line);
			if (comp)
			{
				// See if we're done
				if (comp->iCode == _ICODE_COMMENT)
				{
					// Comment, we're done
					line->status.isCompleted = true;

				} else if (comp->iCode == _ICODE_POUND_SIGN && ((compNext = iComps_getNth(NULL, comp, 1)) && compNext->iCode == _ICODE_LASM_INCLUDE)) {
					// #include 

// TODO: Load the include file
// TODO:  Working here

					// We're done
					line->status.isCompleted = true;

				} else {
					// Pass-0 is completed
					line->status.pass0 = true;
				}

			} else {
				// No data on this line
				line->status.isCompleted = true;
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