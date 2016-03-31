//////////
//
// /libsf/source/vjr/source/compiler/vxb/vxb_compiler.cpp
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
//     Mar.21.2016
//////
// Change log:
//     Mar.21.2016 - Initial creation
//////
//
// This document is released as Liberty Software under a Repeat License, as governed
// by the Public Benefit License v1.0 or later (PBL).
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









//////////
// Basic compile
//////
	void iComps_lex_and_parse(SLine* line, SAsciiCompSearcher* acs0, SAsciiCompSearcher* acs1, SAsciiCompSearcher* acs2, SAsciiCompSearcher* acs3)
	{
		if (line->compilerInfo)
			iiVxb_free_liveCode(line->compilerInfo);

		if (!line->compilerInfo)
			line->compilerInfo = iCompiler_allocate(line);

		// Convert raw source code to known character sequences
		iComps_translate_sourceLineTo(acs0, line);

		// Standard fixups
		iComps_remove_startEndComments(line);			// Remove /* comments */ and /+ comments +/
		iComps_fixup_naturalGroupings(line);			// Fixup natural groupings [_][aaa][999] becomes [_aaa999], [999][.][99] becomes [999.99], etc.
		iComps_remove_whitespaces(line);				// Remove whitespaces [xyz][whitespace][fred] becomes [xyz][fred]

		// Further translation
		if (acs1)		iComps_translate_toOthers(acs1, line->compilerInfo->firstComp, true);
		if (acs2)		iComps_translate_toOthers(acs2, line->compilerInfo->firstComp, true);
		if (acs3)		iComps_translate_toOthers(acs3, line->compilerInfo->firstComp, true);

		// Generate warnings for ignored components if any appear after
// 		iComp_appendError(comp, tnErrorNum, tcMessage);
// 		iComp_appendWarning(comp, tnWarningNum, tcMessage);
// 		iComp_reportWarningsOnRemainder(comp, tnWarningNum, tcMessage);
	}




//////////
//
// Release the compiler info contained here
//
//////
	void iiVxb_free_liveCode(SCompiler* compiler)
	{

		//////////
		// Free this copy of the original source code line (if need be)
		/////
			if (compiler->sourceCode)
				iDatum_delete(&compiler->sourceCode);


		//////////
		// Free the components
		//////
			iComps_deleteAll(&compiler->firstComp);


		//////////
		// Free the previous parse, optimize, and engage nodes
		//////
			if (compiler->first_nodeParse)
			{
				// Release the array
				free(compiler->first_nodeParse);
				compiler->count_nodeParse = 0;
			}

			if (compiler->first_nodeOptimize)
			{
				// Release the array
				free(compiler->first_nodeOptimize);
				compiler->count_nodeOptimize = 0;
			}

			if (compiler->first_nodeEngage)
			{
				// Release the array
				free(compiler->first_nodeEngage);
				compiler->count_nodeArray = 0;
			}


		//////////
		// Delete any errors, warnings, or notes
		//////
			iNoteLog_removeAll(&compiler->firstInquiry);
			iNoteLog_removeAll(&compiler->firstWarning);
			iNoteLog_removeAll(&compiler->firstNote);


		//////////
		// Delete any extra info that's stored
		//////
			iExtraInfo_removeAll(NULL, NULL, &compiler->first_extraInfo, true);

	}




//////////
//
// Appends a new comp to the end of the component chain
//
//////
	SComp* iComps_new(SComp** compRoot, SComp* compHint, SComp* compNext, SComp* compPrev)
	{
		SComp* compNew;


		// Append the new component
		compNew = (SComp*)iLl_appendNew__ll((SLL**)compRoot, (SLL*)compHint, (SLL*)compNext, (SLL*)compPrev, iGetNextUid(), sizeof(SComp));

		// If it was created properly, append a node
		if (compNew)
			iNode_create(&compNew->node, compNew);

		// Indicate our result
		return(compNew);
	}




//////////
//
// Get the next comps Unique ID
//
//////
	u32 iiComps_getNextUid()
	{
		u32 lnValue;


		// Synchronized access
		EnterCriticalSection(&cs_compsUniqueIdAccess);

		// Get our value and increment
		lnValue = gnComps_nextUniqueId++;

		// All done
		LeaveCriticalSection(&cs_compsUniqueIdAccess);

		// Return that value
		return(lnValue);
	}




//////////
//
// Deletes all of the comps in the chain
//
//////
	void iComps_deleteAll(SComp** compRoot)
	{
		SComp* comp;
		SComp* compNext;


		// Make sure our environment is sane
		if (compRoot && *compRoot)
		{
			// Iterate while there's something to delete
			comp = *compRoot;
			while (comp)
			{
				// Grab the next comp
				compNext = comp->ll.nextComp;

				// Delete this one
				iComps_delete(comp, true);

				// Move to the next one
				comp = compNext;
			}

			// Reset the root
			*compRoot = NULL;
		}
	}




//////////
//
// Called to remove all components for this line
//
//////
	void iComps_deleteAll_byLine(SLine* line)
	{
		// Make sure our environment is sane
		if (line && line->compilerInfo)
		{
			// Delete all components
			iComps_deleteAll(&line->compilerInfo->firstComp);

			// Clear the compilerInfo
			iCompiler_delete(&line->compilerInfo, true);
		}
	}




//////////
//
// Deletes everything from this first component
//
//////
	void iComps_deleteAll_byFirstComp(SComp** firstComp)
	{
		SComp* comp;
		SComp* compNext;


		// Make sure the environment is sane
		if (firstComp && *firstComp)
		{
			// Delete all the components
			for (comp = *firstComp; comp; comp = compNext)
			{
				// Delete this component
				compNext = comp->ll.nextComp;		// Grab the next comp
				iComps_delete(comp, true);			// Delete this one
			}

			// Reset the pointer
			*firstComp = NULL;
		}
	}




//////////
//
// Called to duplicate a component
//
//////
// TODO:  We could add a tlDeepCopy here, which would also copy the firstCombined records, the bitmap cache, etc.
	SComp* iComps_duplicate(SComp* comp)
	{
		SComp* compNew;
		SComp* compRoot;


		// Make sure our environment is sane
		compNew = NULL;
		if (comp)
		{
			// Create a copy
			compRoot	= NULL;
			compNew		= iComps_new(&compRoot, NULL, NULL, NULL);
			if (compNew)
				iComps_copyMembers(compNew, comp, true, false, 0);		// Copy the normal members
		}

		// Indicate our copy
		return(compNew);
	}




//////////
//
// Called to delete the indicated comp
//
//////
	SComp* iComps_delete(SComp** compRoot)
	{
		SComp* comp;


		// Make sure our environment is sane
		comp = NULL;
		if (compRoot && *compRoot)
		{
			// Delete the component chain
			comp = iComps_delete(*compRoot, true);

			// Reset the variable
			*compRoot = NULL;
		}

		// Indicate our status
		return(comp);
	}

	SComp* iComps_delete(SComp* comp, bool tlDeleteSelf)
	{
		SComp* compNext;


		// If there is a bitmap cache, delete it
		if (comp->bc)
			iBmp_deleteCache(&comp->bc);

		// If it has combined comps, delete them
		if (comp->firstCombined)		iComps_delete(&comp->firstCombined);
		if (comp->firstWhitespace)		iComps_delete(&comp->firstWhitespace);
		if (comp->firstComment)			iComps_delete(&comp->firstComment);

		// If it has a node, delete it
		if (comp->node)
			iNode_delete(&comp->node);			// Delete it

		// Delete this node from the chain
		compNext = comp->ll.nextComp;
		iLl_delete__ll((SLL*)comp, tlDeleteSelf);

		// Indicate our new value
		return(compNext);
	}




//////////
//
// Called to create nodes across the components, hooking each into each
//
//////
	SNode* iComps_chainLinkNodes(SComp* compLeftMost)
	{
		SComp* comp;
		SComp* compPrev;
		SComp* compNext;


		// Iterate through every comp
		for (comp = compLeftMost; comp; comp = comp->ll.nextComp)
		{
			//////////
			// Make sure it has a node
			//////
				if (!comp->node)
					comp->node = iNode_create(&comp->node, comp);


			//////////
			// Hook it up
			//////
				if (comp->node)
				{
					// If there's a component before, hook up its node
					if ((compPrev = comp->ll.prevComp) && compPrev->node && !compPrev->node->n[_NODE_E])
					{
						comp->node->n[_NODE_W]		= compPrev->node;			// New points west to previous node
						compPrev->node->n[_NODE_E]	= comp->node;				// Previous points east to new
					}

					// If there's a component after, hook up its node
					if ((compNext = comp->ll.nextComp) && compNext->node && !compNext->node->n[_NODE_W])
					{
						comp->node->n[_NODE_E]		= compNext->node;			// New points east to next node
						compNext->node->n[_NODE_W]	= comp->node;				// Next node points points west to new
					}
				}

		}

		// Return self
		return(compLeftMost->node);
	}




//////////
//
// Called to copy the inner contents of a component
//
//////
	void iComps_copyMembers(SComp* compTo, SComp* compFrom, bool tlAllocated, bool tlCopyLl, s32 tnBackoff)
	{
		if (tlCopyLl)
			memcpy(&compTo->ll, &compFrom->ll, sizeof(compFrom->ll));

		// Copy the component's attributes
		compTo->llAllocated						= tlAllocated;

		compTo->line							= compFrom->line;
		compTo->start							= compFrom->start - tnBackoff;
		compTo->length							= compFrom->length;

		compTo->isError							= compFrom->isError;
		compTo->isWarning						= compFrom->isWarning;

		compTo->iCode							= compFrom->iCode;
		compTo->iCat							= compFrom->iCat;

		compTo->color							= compFrom->color;
		compTo->nbspCount						= compFrom->nbspCount;
		compTo->useBoldFont						= compFrom->useBoldFont;

		compTo->overrideSelectionBackColor		= compFrom->overrideSelectionBackColor;
		compTo->overrideSelectionForeColor		= compFrom->overrideSelectionForeColor;
		compTo->overrideMatchingBackColor		= compFrom->overrideMatchingBackColor;
		compTo->overrideMatchingForeColor		= compFrom->overrideMatchingForeColor;

		// Note:  bc (bmpCache) is not copied because each cache is a distinct instance, and it will be rendered the next time it's needed
	}




//////////
//
// Called to search the SAsciiCompSearcher format list of text item keywords.
//
// Note:  If the length column of the SAsciiCompSearcher entry is negative, it is a case-sensitive search.
//
// Returns:
//		The first component created (if any)
//
//////
	SComp* iComps_translate_sourceLineTo(SAsciiCompSearcher* tsComps, SLine* line)
	{
		s32						lnI, lnMaxLength, lnStart, lnLength, lnLacsLength;
		SComp*					compFirst;
		SComp*					compLast;
		SComp*					comp;
		u8*						lcData;
		SAsciiCompSearcher*		lacs;


		// Make sure the environment's sane
		compFirst = NULL;
		if (tsComps && line)
		{
			// Scan starting at the beginning of the line
			lcData = line->sourceCode->data._u8;

			// Iterate through every byte identifying every component we can
			compLast	= line->compilerInfo->firstComp;
			lnMaxLength	= line->sourceCode_populatedLength;
			for (lnI = 0; lnI < lnMaxLength; )
			{
				// Search through the tsComps list one by one
				for (	lacs = tsComps;
						lacs->length != 0;
						lacs++)
				{
					// Find out our signed status and get normalized length
//					llSigned		= (lacs->length < 0);
					lnLacsLength	= abs(lacs->length);

					// Process through this entry
					if ((!lacs->firstOnLine || lnI == 0 || iComps_areAllPrecedingCompsWhitespaces(compLast)) && lnLacsLength <= lnMaxLength - lnI)
					{
						// There is enough room for this component to be examined
						// See if it matches
						if (		iComps_xlatToComps_withTest(lacs->keyword_cu8, lcData + lnI, lacs->length) == 0
								&&	(!lacs->_onCandidateMatch || lacs->onCandidateMatch(lacs, lcData + lnI, lacs->length))		)
						{
							// It matches
							// mark its current condition
							lnStart		= lnI;
							lnLength	= lnLacsLength;
							// See if it's allowed to repeat
							if (lacs->repeats)
							{
								while (	lnStart + lnLength + lnLacsLength <= lnMaxLength
										&& iComps_xlatToComps_withTest(lacs->keyword_cu8, lcData + lnStart + lnLength, lacs->length) == 0)
								{
									// We found another repeated entry
									lnLength += lnLacsLength;
								}
								// When we get here, every repeated entry has been found (if any)
							}
							// When we get here, we have the starting point and the full length (including any repeats)


							//////////
							// Allocate this entry
							///////
								comp = iComps_new(&line->compilerInfo->firstComp, compLast, NULL, compLast);


							//////////
							// Populate the component with specified information
							//////
								//
								//////
									if (comp)
									{
										// Update the back links
										if (compLast)
											compLast->ll.next = (SLL*)comp;			// Previous one points to this one

										// This one points back to previous one
										comp->ll.prev		= (SLL*)compLast;

										// Update the component's information
										comp->line			= line;
										comp->start			= lnStart;
										comp->length		= lnLength;
										comp->iCode			= lacs->iCode;
										comp->iCat			= lacs->iCat;
										comp->color			= lacs->syntaxHighlightColor;
										comp->useBoldFont	= lacs->useBoldFont;

										// Update our first component (if it's not updated already)
										if (!compFirst)
											compFirst = comp;

										// All done
									}

									// Make sure we're setup for the next go-round
									compLast = comp;
								//////
								//
							//////
							// END
							//////////


							//////////
							// Execute
							//////
								if (lacs->_onFind)
									lacs->onFind(lacs, comp);


							//////////
							// Move beyond this entry, and continue on search again afterward
							//////
								lnI += lnLength;
								break;		// leaves lnJ loop, continues with lnI loop
						}
					}
				}
				// When we get here, we've processed through everything here
				if (lacs->length == 0)
					lnI++;			// We didn't find anything at that character, continue on to the next
			}
			// When we get here, lnI has been updated to its new location,
			// and any indicated components have been added
		}
		// Return the count
		return(compFirst);
	}




//////////
//
// Called to search the already parsed SAsciiCompSearcher list of components, looking for
// combinations which relate to other component types.  The primary translations here are
// alpha/alphanumeric/numeric forms to other forms.
//
//////
	bool iComps_translate_toOthers(SAsciiCompSearcher* tacsRoot, SComp* comp, bool tlDescendIntoFirstCombineds)
	{
		bool					llResult;
		s32						lnTacsLength;
		SAsciiCompSearcher*		tacs;


		// Make sure the environment is sane
		llResult = false;
		if (tacsRoot && comp && comp->line && comp->line->sourceCode)
		{
			// Grab our pointers into recognizable thingamajigs
			while (comp)
			{
				// Parse those things which were combined if need be
				if (tlDescendIntoFirstCombineds && comp->firstCombined)
					iComps_translate_toOthers(tacsRoot, comp->firstCombined, true);

				// Iterate through this item to see if any match
				tacs = tacsRoot;
				for (/* tacs is initialize above */; tacs->length != 0; tacs++)
				{
					// Grab the normalized length
					lnTacsLength = abs(tacs->length);

					// We only test if they're the same length
					if (lnTacsLength == comp->length || (tacs->repeats && lnTacsLength <= comp->length))
					{
						// We only test if this item is not the first item on line, or if must be the first
						// item on the line, then this component must be the first component on the line.  Simple, yes? :-)
						if (!tacs->firstOnLine || !comp->ll.prev || iComps_areAllPrecedingCompsWhitespaces(comp))
						{
							// Physically conduct the exact comparison
							if (iComps_translateToOthers_testIfMatch(tacs->keyword_cu8, comp->line->sourceCode->data._cu8 + comp->start, tacs->length) == 0)
							{
								// This is a match
								llResult			= true;

								// Convert it, translate it, whatever you want to call it, just make it be the new code, per the user's request, got it? :-)
								comp->iCode			= tacs->iCode;
								comp->iCat			= tacs->iCat;
								comp->color			= tacs->syntaxHighlightColor;
								comp->useBoldFont	= tacs->useBoldFont;


								//////////
								// Execute
								//////
									if (tacs->_onFind)
										tacs->onFind(tacs, comp);


								// All done with this component
								break;
							}
						}
					}
				}

				// Move to next component
				comp = comp->ll.nextComp;
			}
		}

		// Indicate our status
		return(llResult);
	}




//////////
//
// If every component from here on back is a whitespace, this is then the first
// component on the line.
//
//////
	bool iComps_areAllPrecedingCompsWhitespaces(SComp* comp)
	{
		while (comp)
		{
			// If this isn't a whitespace, the test fails
			if (comp->iCode != _ICODE_WHITESPACE)
				return(false);

			// Move to previous component
			comp = comp->ll.prevComp;
		}
		// If we get here, true
		return(true);
	}




//////////
//
// Search the haystack for the needle, the haystack can be tupels, as in "_az" meaning
// (is it between "a" and "z" inclusive?)  To set this condition, use a length of 1,
// a leading "_" in tcHaystack, and two characters (one of which must NOT be NULL) after.
//
// Examples:
//		_az		= lower-case a to z inclusive
//		_AZ		= upper-case a to z inclusive
//		_09		= numeric 0 to 9 inclusive
//
// Note:  If length is negative, it is a signed compare.
//
// Returns:
//		0		= matches
//		!0		= does not tmach
//
//////
	s32 iComps_translateToOthers_testIfMatch(cu8* tcHaystack, cu8* tcNeedle, s32 tnLength)
	{
		u32		lnI;
		bool	llSigned;


		// Make sure our environment is sane
		if (tnLength != 0)
		{
			// See if we're a signed or unsigned compare
			if (tnLength < 0)
			{
				// Case sensitive compare
				tnLength	= -tnLength;
				llSigned	= true;

			} else {
				// Case insensitive compare
				llSigned = false;
			}

			// See if we're looking for a tuple, or a regular compare
			if (tcHaystack[0] == '_' && tnLength == 1)
			{
				// It's an explicit match of a range (this is ALWAYS subject to case as it is an explicit range)
				for (lnI = 1; tcHaystack[lnI] != 0 || tcHaystack[lnI + 1] != 0; lnI += 2)
				{
					//		within the range low			.........			up to the range high
					if (tcNeedle[0] >= tcHaystack[lnI]			&&		tcNeedle[0] <= tcHaystack[lnI + 1])
						return(0);		// It's a match, needle is in the range
				}
				// Not a match, will fall through to below

			} else {
				// Just a regular compare
				if (llSigned)	return(  memcmp(tcHaystack, tcNeedle, tnLength));
				else			return(_memicmp(tcHaystack, tcNeedle, tnLength));
			}
		}
		// If we get here, no match
		return(-1);
	}




//////////
//
// Searches forward to find the indicated component by the indicated type.
//
// Returns:
//		The matching component
//		If NULL, the compLastScanned indicates the last component that was searched where it wasn't found
//
//////
	SComp* iComps_findNextBy_iCode(SComp* comp, s32 tniCode, SComp** compLastScanned)
	{
		// Initially indicate failure
		if (compLastScanned)
			*compLastScanned = comp;

		// Continue while the environment is sane
		while (comp)
		{
			// Store the component we're scanning
			if (compLastScanned)
				*compLastScanned = comp;

			// See if this is it
			if (comp->iCode == tniCode)
				break;		// It is, we're done

			// Move to the next component
			comp = comp->ll.nextComp;
		}
		// When we get here, we either found it or not
		// Store our results
		return(comp);
	}




//////////
//
// Returns which component the cursor is currently on
//
//////
	SComp* iComps_activeComp_inSEM(SEM* sem)
	{
		SComp* comp;


		// Make sure our environment is sane
		if (sem && sem->isSourceCode && sem->line_cursor && sem->line_cursor->compilerInfo && sem->line_cursor->compilerInfo->firstComp)
		{
			// Begin at the beginning
			comp = sem->line_cursor->compilerInfo->firstComp;
			while (comp)
			{
				// Is this the active component?
				if (sem->columnEdit >= comp->start && sem->columnEdit <= comp->start + comp->length)
					return(comp);

				// Move to next component
				comp = comp->ll.nextComp;
			}
		}

		// If we get here, invalid or not found
		return(NULL);
	}




//////////
//
// If this is something that has a mate, indicate the mate's direction (forward
// or backward in source code).
//
//////
	bool iComps_get_mateDirection(SComp* comp, s32* tnMateDirection)
	{
		if (comp && tnMateDirection)
		{
			switch (comp->iCode)
			{
				case _ICODE_PARENTHESIS_LEFT:
					// Is (, so what is the direction to )?
					*tnMateDirection = 1;
					return(true);

				case _ICODE_PARENTHESIS_RIGHT:
					// Is ), so what is the direction to (?
					*tnMateDirection = -1;
					return(true);

				case _ICODE_BRACKET_LEFT:
					*tnMateDirection = 1;
					return(true);
				case _ICODE_BRACKET_RIGHT:
					*tnMateDirection = -1;
					return(true);

				case _ICODE_DOUBLE_BRACE_LEFT:
				case _ICODE_BRACE_LEFT:
					*tnMateDirection = 1;
					return(true);
				case _ICODE_DOUBLE_BRACE_RIGHT:
				case _ICODE_BRACE_RIGHT:
					*tnMateDirection = -1;
					return(true);
			}
		}

		// If we get here, no mate
		*tnMateDirection = 0;
		return(false);
	}




//////////
//
// Called to search the comp and forward for a parenthesis, bracket, or brace, and then to
// search the appropriate direction and find the matching one, and return those components.
//
//////
	bool iComps_findClosest_parensBracketsBraces(SComp* compRelative, SComp* compStart, SComp** compPBBLeft, SComp** compPBBRight)
	{
		s32 lnDirection, lniCodeNeedle, lniCodeNeedleMate, lnLevel;


		// Make sure our environment is sane
		if (compStart && compPBBLeft && compPBBRight)
		{
			// Reset our receivers
			*compPBBLeft	= NULL;
			*compPBBRight	= NULL;

			// Are we already on a target?
			if (compStart->iCode == _ICODE_PARENTHESIS_LEFT)
			{
				// We're on (
				lnDirection			= 1;
				*compPBBLeft		= compStart;
				lniCodeNeedle		= _ICODE_PARENTHESIS_RIGHT;
				lniCodeNeedleMate	= _ICODE_PARENTHESIS_LEFT;

			} else if (compStart->iCode == _ICODE_PARENTHESIS_RIGHT) {
				// We're on )
				lnDirection			= -1;
				*compPBBRight		= compStart;
				lniCodeNeedle		= _ICODE_PARENTHESIS_LEFT;
				lniCodeNeedleMate	= _ICODE_PARENTHESIS_RIGHT;

			} else if (compStart->iCode == _ICODE_BRACKET_LEFT) {
				// We're on [
				lnDirection			= 1;
				*compPBBLeft		= compStart;
				lniCodeNeedle		= _ICODE_BRACKET_RIGHT;
				lniCodeNeedleMate	= _ICODE_BRACKET_LEFT;

			} else if (compStart->iCode == _ICODE_BRACKET_RIGHT) {
				// We're on ]
				lnDirection			= -1;
				*compPBBRight		= compStart;
				lniCodeNeedle		= _ICODE_BRACKET_LEFT;
				lniCodeNeedleMate	= _ICODE_BRACKET_RIGHT;

			} else if (compStart->iCode == _ICODE_DOUBLE_BRACE_LEFT) {
				// We're on {{
				lnDirection			= 1;
				*compPBBLeft		= compStart;
				lniCodeNeedle		= _ICODE_DOUBLE_BRACE_RIGHT;
				lniCodeNeedleMate	= _ICODE_DOUBLE_BRACE_LEFT;

			} else if (compStart->iCode == _ICODE_DOUBLE_BRACE_RIGHT) {
				// We're on }}
				lnDirection			= -1;
				*compPBBRight		= compStart;
				lniCodeNeedle		= _ICODE_DOUBLE_BRACE_LEFT;
				lniCodeNeedleMate	= _ICODE_DOUBLE_BRACE_RIGHT;

			} else if (compStart->iCode == _ICODE_BRACE_LEFT) {
				// We're on {
				lnDirection			= 1;
				*compPBBLeft		= compStart;
				lniCodeNeedle		= _ICODE_BRACE_RIGHT;
				lniCodeNeedleMate	= _ICODE_BRACE_LEFT;

			} else if (compStart->iCode == _ICODE_BRACE_RIGHT) {
				// We're on }
				lnDirection			= -1;
				*compPBBRight		= compStart;
				lniCodeNeedle		= _ICODE_BRACE_LEFT;
				lniCodeNeedleMate	= _ICODE_BRACE_RIGHT;

			} else {
				// We need to search forward to find the closest one
				do
				{
					// Move to next comp
					compStart = compStart->ll.nextComp;

					// Is this a target?
					if (compStart)
					{
						switch (compStart->iCode)
						{
							case _ICODE_PARENTHESIS_RIGHT:
							case _ICODE_BRACKET_RIGHT:
							case _ICODE_BRACE_RIGHT:
								if (!iComps_findClosest_parensBracketsBraces(compRelative, compStart, compPBBLeft, compPBBRight))
									return(false);

								// If the left component begins before our reference component we're good, otherwise we're still looking
								if ((*compPBBLeft)->start < compRelative->start)
									return(true);

								// If we get here, still looking
								break;
						}
					}

				} while (compStart);

				// If we get here, no find
				return(false);
			}

			// When we get here we are processing for the indicated form
			lnLevel = 0;
			do {
				// Move to next comp
				if (lnDirection == -1)			compStart = compStart->ll.prevComp;
				else							compStart = compStart->ll.nextComp;

				// Is this our match?
				if (compStart)
				{
					if (compStart->iCode == lniCodeNeedle)
					{
						if (lnLevel == 0)
						{
							// We're there, note our findings
							if (lnDirection == -1)		*compPBBLeft	= compStart;
							else						*compPBBRight	= compStart;

							// Report success
							return(true);
						}

						// Going deeper, decrease our level
						--lnLevel;

					} else if (compStart->iCode == lniCodeNeedleMate) {
						// It's the mate of what we're searching for, increase our level another level deep for nesting, going shallow
						++lnLevel;
					}
				}

			} while (compStart);

			// When we get here, no find
			return(false);
		}
		// If we get here, invalid
		return(false);
	}




//////////
//
// Called to see if a component is a parenthesis, bracket, or brace
//
//////
	bool iComps_isParensBracketsBraces(SComp* comp)
	{
		// Make sure our environment is sane
		if (comp)
		{
			switch (comp->iCode)
			{
				case _ICODE_PARENTHESIS_LEFT:
				case _ICODE_PARENTHESIS_RIGHT:
				case _ICODE_BRACKET_LEFT:
				case _ICODE_BRACKET_RIGHT:
				case _ICODE_DOUBLE_BRACE_LEFT:
				case _ICODE_DOUBLE_BRACE_RIGHT:
				case _ICODE_BRACE_LEFT:
				case _ICODE_BRACE_RIGHT:
					return(true);
			}
			// If we get here, no match
		}

		// If we get here, invalid
		return(false);
	}




//////////
//
// Is the reference the mate of iCodeMate
//
//////
	bool iComps_isMateOf(SComp* compTest, s32 tniCodeMate)
	{
		switch (tniCodeMate)
		{
			case _ICODE_PARENTHESIS_LEFT:				return(compTest->iCode == _ICODE_PARENTHESIS_RIGHT);
			case _ICODE_PARENTHESIS_RIGHT:				return(compTest->iCode == _ICODE_PARENTHESIS_LEFT);
			case _ICODE_BRACKET_LEFT:					return(compTest->iCode == _ICODE_BRACKET_RIGHT);
			case _ICODE_BRACKET_RIGHT:					return(compTest->iCode == _ICODE_BRACKET_LEFT);
			case _ICODE_DOUBLE_BRACE_LEFT:				return(compTest->iCode == _ICODE_DOUBLE_BRACE_RIGHT);
			case _ICODE_DOUBLE_BRACE_RIGHT:				return(compTest->iCode == _ICODE_DOUBLE_BRACE_LEFT);
			case _ICODE_BRACE_LEFT:						return(compTest->iCode == _ICODE_BRACE_RIGHT);
			case _ICODE_BRACE_RIGHT:					return(compTest->iCode == _ICODE_BRACE_LEFT);
		}

		// If we get here, not a mate
		return(false);
	}




//////////
//
// Searches for the next component that is not of type tniIcode, including itself
//
//////
	SComp* iComps_skipPast_iCode(SComp* comp, s32 tniCode)
	{
		while (comp && comp->iCode == tniCode)
		{
			// Move to next component
			comp = comp->ll.nextComp;
		}
		// When we get here, we're sitting on either no valid component, or the one which does not match the specified type
		return(comp);
	}




//////////
//
// Searches beyond this component until we find the indicated component
//
//////
	SComp* iComps_skipTo_iCode(SComp* comp, s32 tniCode)
	{
		// Skip to next comp
		comp = comp->ll.nextComp;

		// Repeat until we find our match
		while (comp && comp->iCode != tniCode)
			comp = comp->ll.nextComp;	// Move to next component

		// When we get here, we're sitting on the iCode, or we've exhausted our comps and it's NULL
		return(comp);
	}




//////////
//
// Called to retrieve the next component after the dot.  The dot should be 
// either this component, or the one after it.  The next component will be
// the one after that.
//
//////
	SComp* iComps_getNext_afterDot(SComp* comp)
	{
		if (comp)
		{
			if (comp->iCode == _ICODE_DOT)
			{
				// Return the next one, whether it's right, wrong, or indifferent
				return(comp->ll.nextComp);

			} else if (comp->ll.nextComp && comp->ll.nextComp->iCode == _ICODE_DOT) {
				// Return the 2nd one, whether it's right, wrong, or indifferent
				return(comp->ll.nextComp->ll.nextComp);
			}
		}

		// If we get here, failure
		return(NULL);
	}

	// A newer version which goes to the next line if need be
	SComp* iComps_prev(SComp* comp, bool tlMoveBeyondLineIfNeeded)
	{
		return(iComps_Nth(comp, -1, tlMoveBeyondLineIfNeeded));
	}

	// A newer version which goes to the next line if need be
	SComp* iComps_next(SComp* comp, bool tlMoveBeyondLineIfNeeded)
	{
		return(iComps_Nth(comp, 1, tlMoveBeyondLineIfNeeded));
	}

	// A newer version which goes to the next line if need be
	SComp* iComps_Nth(SComp* comp, s32 tnCount, bool tlMoveBeyondLineIfNeeded)
	{
		s32		lnI;
		SLine*	line;


		// Based on direction
		if (comp)
		{
			if (tnCount > 0)
			{
				// Going forward
				for (lnI = 0; comp && lnI < tnCount; lnI++)
				{
					// Is there room on the line?
					if (comp->ll.nextComp)
					{
						// Move to next component
						comp = comp->ll.nextComp;

					} else {
						// No more components on this line, switch to next line
						if (tlMoveBeyondLineIfNeeded && comp->line && (line = comp->line->ll.nextLine))
						{
							// Room to move forward
							while (line && (!line->compilerInfo || !line->compilerInfo->firstComp) && line->ll.nextLine)
								line = line->ll.nextLine;

							// Store the component
							if (line->compilerInfo && line->compilerInfo->firstComp)
							{
								// Use this component for the next one
								comp = line->compilerInfo->firstComp;

							} else {
								// We're done
								comp = NULL;
							}

						} else {
							// We're done
							comp = NULL;
						}
					}
				}

			} else if (tnCount < 0) {
				// Going backwards
				for (lnI = 0; comp && lnI < tnCount; lnI++)
				{
					// Is there room on the line?
					if (comp->ll.prevComp)
					{
						// Move to next component
						comp = comp->ll.prevComp;

					} else {
						// No more components on this line, switch to next line
						if (tlMoveBeyondLineIfNeeded && comp->line && (line = comp->line->ll.prevLine))
						{
							// Room to move forward
							while (line && (!line->compilerInfo || !line->compilerInfo->firstComp) && line->ll.prevLine)
								line = line->ll.prevLine;

							// Store the last component on the line
							if (line->compilerInfo && line->compilerInfo->firstComp)
							{
								// Use this component
								comp = line->compilerInfo->firstComp;

								// Move to the last one of the line
								while (comp->ll.nextComp)
									comp = comp->ll.nextComp;

								// When we get here, we're on the last component on the line

							} else {
								// We're done
								comp = NULL;
							}

						} else {
							// We're done
							comp = NULL;
						}
					}
				}
			}
		}

		// Indicate success or failure
		return(comp);
	}




//////////
//
// Returns the Nth component beyond the current one
//
//////
	SComp* iComps_Nth_fromLine(SComp* comp, s32 tnCount)
	{
		s32 lnI;


		// Iterate until we find it
		for (lnI = 0; comp && lnI < tnCount; lnI++)
			comp = comp->ll.nextComp;

		// Indicate success or failure
		return(comp);
	}




//////////
//
// Called to combine two components into one.  If tnNewICode is > 0 then the
// iCode is updated as well.  If compMigrateRefs is populated, then the node
// that's combined isn't deleted, but rather is migrated to that chain.
// Otherwise, the node that was merged in is deleted.
//
//////
	u32 iComps_combineN(SComp* comp, u32 tnCount, s32 tnNew_iCode, u32 tnNew_iCat, SBgra* newColor, SComp** compMigrateRefs)
	{
		u32		lnCount;
		SComp*	compNext;


		// Make sure our environment is sane
		lnCount = 0;
		if (comp)
		{
			//////////
			// Combine the next N-1 items
			//////
				for (lnCount = 1; lnCount < tnCount; lnCount++)
				{
					// Grab the next component
					compNext = comp->ll.nextComp;

					// Combine it into this one
					if (compNext)
					{
						// If we have a migrate buffer, and it's the first one, we need to duplicate it so it shows up in the migrate buffer properly
						if (lnCount == 1 && compMigrateRefs)
							iLl_appendExisting__llAtEnd((SLL**)compMigrateRefs, (SLL*)iComps_duplicate(comp));

						// Add in the length of the next component, plus any spaces between them
						comp->length	+= (compNext->length + iiComps_get_charactersBetween(comp, compNext));
						comp->nbspCount	+= compNext->nbspCount;

						// Migrate or delete the next component
						if (compMigrateRefs)
						{
							// Combine it if it's part of a chain
							if (comp->line && comp->line->compilerInfo && comp->line->compilerInfo->firstComp)
								iLl_migrate__llToOther((SLL**)&comp->line->compilerInfo->firstComp, (SLL**)compMigrateRefs, (SLL*)compNext, true);

						} else {
							// Delete it
							iLl_delete__ll((SLL*)compNext, true);
						}

					} else {
						// We're done, perhaps prematurely, but there are no more components
						break;
					}
				}


			//////////
			// Mark it as the new iCode
			//////
				if (tnNew_iCode > 0)
				{
					comp->iCode = tnNew_iCode;
					comp->iCat	= tnNew_iCat;
					comp->color	= newColor;
				}
		}


		//////////
		// Indicate how many we merged
		//////
			return(lnCount - 1);
	}




//////////
//
// Called to combine all immediately adjacent components into a single one.
// This is typically done to aggegate things that should be something like
// a filename, such as [c][:][\][some][\][dir][\][file][.][txt], into one
// component of [c:\some\dir\file.txt].
//
//////
	u32 iComps_combine_adjacent(SComp* compLeftmost, s32 tniCode, u32 tniCat, SBgra* tnColor, s32 valid_iCodeArray[], s32 tnValid_iCodeArrayCount)
	{
		u32 lnCombined;


		// Make sure the environment is sane
		lnCombined = 0;
		if (compLeftmost)
		{
			// Repeat so long as there is a component to the right
			for ( ; compLeftmost->ll.next; lnCombined++)
			{
				// And continue so long as they are immediately adjacent
				if (iiComps_get_charactersBetween(compLeftmost, compLeftmost->ll.nextComp) != 0)
					return(lnCombined);	// All done

				// Validate if need be
				if (tnValid_iCodeArrayCount > 0 && valid_iCodeArray)
				{
					// If it's valid, add it
					if (!iiComps_validate(compLeftmost->ll.nextComp, valid_iCodeArray, tnValid_iCodeArrayCount))
						return(lnCombined);		// Invalid

					// If we get here, it is still valid
				}
				// else no validation is required

				// Combine these two...
				iComps_combineN(compLeftmost, 2, tniCode, tniCat, tnColor);
				// ...and continue on to the next component after
			}
		}

		// Indicate how many were combined
		return(lnCombined);
	}




//////////
//
// Called to combine adjacent combinations of underscore, alpha, numeric, or alphanumeric,
// which begin with an underscore, alpha, or alphanumeric, into one component that is then
// branded as alphanumeric.
//
//////
	u32 iComps_combine_adjacentAlphanumeric(SLine* line)
	{
		u32		lnCombined;
		SComp*	comp;
		SComp*	compNext;


		// Make sure our environment is sane
		lnCombined = 0;
		if (line && line->compilerInfo)
		{
			// Begin at the beginning and check across all components
			comp = line->compilerInfo->firstComp;
			while (comp)
			{
				// Grab the next component
				compNext = comp->ll.nextComp;
				if (compNext)
				{
					// Is this an underscore, alpha, or alphanumeric?
					if (comp->iCode == _ICODE_UNDERSCORE || comp->iCode == _ICODE_ALPHA || comp->iCode == _ICODE_ALPHANUMERIC)
					{
						// Combine so long as the following are immediately adjacent, and are one of underscore, alpha, numeric, alphanumeric
						while (	(compNext = comp->ll.nextComp)
								&& iiComps_get_charactersBetween(comp, compNext) == 0
								&& (	compNext->iCode == _ICODE_UNDERSCORE
									||	compNext->iCode == _ICODE_ALPHA
									||	compNext->iCode == _ICODE_NUMERIC
									||	compNext->iCode == _ICODE_ALPHANUMERIC
								)
							)
						{
							// Combine this comp and the next one into one
							iComps_combineN(comp, 2, _ICODE_ALPHANUMERIC, comp->iCat, comp->color);
							++lnCombined;
						}
					}
				}


				// Move to the next component
				comp = comp->ll.nextComp;
			}
		}

		// Indicate how many we combined
		return(lnCombined);
	}




//////////
//
// Called to combine numeric combinations, such as [999][.][99] into [999.99] as
// a single numeric.  In addition, if a leading plus or negative is immediately
// adjacent, it is included as well.
//
//////
	u32 iComps_combine_adjacentNumeric(SLine* line)
	{
		u32		lnCombined;
		SComp*	comp;
		SComp*	compNext1;
		SComp*	compNext2;
		SComp*	compNext3;


		// Make sure our environment is sane
		lnCombined = 0;
		if (line && line->compilerInfo)
		{
			// Begin at the beginning and check across all components
			comp = line->compilerInfo->firstComp;
			while (comp)
			{
				// Grab the next component
				if ((compNext1 = comp->ll.nextComp) && iiComps_get_charactersBetween(comp, compNext1) == 0)
				{
					// Is this an underscore, alpha, or alphanumeric?
					if ((comp->iCode == _ICODE_PLUS || comp->iCode == _ICODE_HYPHEN) && compNext1->iCode == _ICODE_NUMERIC)
					{
						// We have +-999
						if ((compNext2 = compNext1->ll.nextComp) && compNext2->iCode == _ICODE_DOT)
						{
							// We have +-999.
							if ((compNext3 = compNext2->ll.nextComp) && compNext3->iCode == _ICODE_NUMERIC)
							{
								// We have +-999.99
								iComps_combineN(comp, 4, _ICODE_NUMERIC, comp->iCat, comp->color);
								lnCombined += 3;

							} else {
								// Combine the +- with the 999 and the .
								iComps_combineN(comp, 3, _ICODE_NUMERIC, comp->iCat, comp->color);
								lnCombined += 2;
							}

						} else {
							// Combine the +- with the 999 into one
							iComps_combineN(comp, 2, _ICODE_NUMERIC, comp->iCat, comp->color);
							++lnCombined;
						}

					} else if (comp->iCode == _ICODE_NUMERIC) {
						// We have 999
						if ((compNext1 = comp->ll.nextComp) && compNext1->iCode == _ICODE_DOT)
						{
							// We have 999.
							if ((compNext2 = compNext1->ll.nextComp) && compNext2->iCode == _ICODE_NUMERIC)
							{
								// We have 999.99
								iComps_combineN(comp, 3, _ICODE_NUMERIC, comp->iCat, comp->color);
								lnCombined += 2;

							} else {
								// We just have 999.
								iComps_combineN(comp, 2, _ICODE_NUMERIC, comp->iCat, comp->color);
								++lnCombined;
							}
						}
					}
				}


				// Move to the next component
				comp = comp->ll.nextComp;
			}
		}

		// Indicate how many we combined
		return(lnCombined);
	}




//////////
//
// Called to combine adjacent | characters into either
// a || whitespace if two, or a ||| comment if greater
//
//////
	u32 iComps_combine_adjacentLeadingPipesigns(SLine* line)
	{
		s32		lniCat, lniCode;
		u32		lnCombined;
		SComp*	comp;
		SComp*	compPipesign2;
		SComp*	compPipesign3;


		// Make sure our environment is sane
		lnCombined = 0;
		if (line && line->compilerInfo && (comp = line->compilerInfo->firstComp) && comp->iCode == _ICODE_PIPE_SIGN)
		{
			// Is it followed by a pipe sign?
			if ((compPipesign2 = comp->ll.nextComp) && iiComps_get_charactersBetween(comp, compPipesign2) == 0 && compPipesign2->iCode == _ICODE_PIPE_SIGN)
			{

				//////////
				// It has at least one following, so an extra test is required:
				//
				//		Whitespace	-- double-pipe-sign
				//		Comment		-- triple-pipe-sign or more
				//////
					if ((compPipesign3 = compPipesign2->ll.nextComp) && iiComps_get_charactersBetween(compPipesign2, compPipesign3) == 0 && compPipesign3->iCode == _ICODE_PIPE_SIGN)
					{
						// Translate to comment
						// Find out how many there are
						lniCode	= _ICODE_COMMENT;
						for (lnCombined = 2; compPipesign3->iCode == _ICODE_PIPE_SIGN; lnCombined++)
							compPipesign3 = compPipesign3->ll.nextComp;

					} else {
						// Translate to whitespace
						lniCode		= _ICODE_PIPE_SIGN;
						lnCombined	= 2;
					}


				//////////
				// Combine
				//////
					lniCat	= comp->iCat;
					iComps_combineN(comp, lnCombined, lniCode, lniCat, comp->color);

			}
		}

		// Indicate how many we combined
		return(lnCombined);
	}




//////////
//
// Called to combine everything between two components
//
// Source:		u8 name[] = "foo"
// Example:		[u8][whitespace][name][left bracket][right bracket][whitespace][equal][whitespace][double quote][foo][double quote]
// Search:		[double quote], replace with [double quoted text]
// After:		[u8][whitespace][name][left bracket][right bracket][whitespace][equal][whitespace][double quote text]
//
//////
	u32 iComps_combineAll_between(SLine* line, s32 tniCodeNeedle, s32 tniCodeCombined, SBgra* syntaxHighlightColor)
	{
		u32		lnCount;
		SComp*	compNext;
		SComp*	comp;
		SComp*	compSearcher;


		// Make sure our environment is sane
		lnCount = 0;
		if (line && line->compilerInfo && line->compilerInfo->firstComp)
		{
			// Grab the first component
			comp = line->compilerInfo->firstComp;

			// Continue until we get ... to ... the ... end ... (imagine you were reading that like in a baseball stadium with lots of loud echoes)
			while (comp)
			{
				// Grab the next component sequentially
				compNext = comp->ll.nextComp;

				// Make sure there's something to do
				if (!compNext)
					return(lnCount);	// We're done

				// Is this our intended?
				if (comp->iCode == tniCodeNeedle)
				{
					// Search forward to see if there is a matching entry
					compSearcher = compNext;
					while (compSearcher)
					{
						if (compSearcher->iCode == tniCodeNeedle)
						{
							// This is the match, combine everything between
							comp->length	= (compSearcher->start + compSearcher->length) - comp->start;
							comp->iCode		= tniCodeCombined;
							comp->color		= syntaxHighlightColor;
							comp->nbspCount	+= compSearcher->nbspCount;

							// Iterate and merge in
							while (compNext)
							{
								// Increase our count
								++lnCount;

								// Migrate this one to the combined node (as it was technically merged above with the comp->length = line)
								iLl_migrate__llToOther((SLL**)&line->compilerInfo->firstComp, (SLL**)&comp->firstCombined, (SLL*)compNext, true);

								// See if we're done
								if (compNext == compSearcher)
									break;		// This was the last one, we're done

								// Move to the next component (which is the comp->ll.next component again, because we just migrated the previous compNext
								compNext = comp->ll.nextComp;
							}
							// When we get here, everything's migrated

							// Grab the new next, which is the one after the matched entry
							compNext = comp->ll.nextComp;

							// Continue looking for more combinations on this line
							break;
						}

						// Move to the next component
						compSearcher = compSearcher->ll.nextComp;
					}
				}
				// Move to the next component
				comp = compNext;
			}
			// When we get here, we're good
		}
		// Indicate the success rate at which we operated hitherto
		return(lnCount);
	}




//////////
//
// Called to search for unmatched codes, a left and right, and combines everything between
//
//////
	u32 iComps_combineAll_betweenTwo(SLine* line, s32 tniCodeNeedleLeft, s32 tniCodeNeedleRight, s32 tniCodeCombined, u32 tniCat, SBgra* syntaxHighlightColor, bool tlUseBoldFont)
	{
		u32		lnCount;
		SComp*	compNext;
		SComp*	comp;
		SComp*	compSearcher;


		// Make sure our environment is sane
		lnCount = 0;
		if (line && line->compilerInfo && line->compilerInfo->firstComp)
		{
			// Grab the first component
			comp = line->compilerInfo->firstComp;

			// Continue until we get ... to ... the ... end ... (imagine you were reading that like in a baseball stadium with lots of loud echoes)
			while (comp)
			{
				// Grab the next component sequentially
				compNext = comp->ll.nextComp;

				// Make sure there's something to do
				if (!compNext)
					return(lnCount);	// We're done

				// Is this our intended?
				if (comp->iCode == tniCodeNeedleLeft)
				{
					// Search forward to see if there is a matching entry
					compSearcher = compNext;
					while (compSearcher)
					{
						if (compSearcher->iCode == tniCodeNeedleRight)
						{
							// This is the match, combine everything between
							comp->length		= (compSearcher->start + compSearcher->length) - comp->start;
							comp->iCode			= tniCodeCombined;
							comp->iCat			= tniCat;
							comp->color			= syntaxHighlightColor;
							comp->useBoldFont	= tlUseBoldFont;

							// Iterate and merge in
							while (compNext)
							{
								// Increase our count
								++lnCount;

								// Add in our count
								comp->nbspCount += compNext->nbspCount;

								// Migrate this one to the combined node (as it was technically merged above with the comp->length = line)
								iLl_migrate__llToOther((SLL**)&line->compilerInfo->firstComp, (SLL**)&comp->firstCombined, (SLL*)compNext, true);

								// See if we're done
								if (compNext == compSearcher)
									break;		// This was the last one, we're done

								// Move to the next component (which is the comp->ll.next component again, because we just migrated the previous compNext
								compNext = comp->ll.nextComp;
							}
							// When we get here, everything's migrated

							// Grab the new next, which is the one after the matched entry
							compNext = comp->ll.nextComp;

							// Continue looking for more combinations on this line
							break;
						}

						// Move to the next component
						compSearcher = compSearcher->ll.nextComp;
					}
				}
				// Move to the next component
				comp = compNext;
			}
			// When we get here, we're good
		}
		// Indicate the success rate at which we operated hitherto
		return(lnCount);
	}




//////////
//
// Called to combine everything after the indicated component into that one component.
//
//////
	u32 iComps_combineAll_after(SLine* line, s32 tniCodeNeedle)
	{
		u32		lnCombined;
		SComp*	comp;


		// Make sure our environment is sane
		lnCombined = 0;
		if (line && line->compilerInfo && line->compilerInfo->firstComp)
		{
			// Grab the first component
			comp = line->compilerInfo->firstComp;

			// Iterate forward through all components
			while (comp)
			{
				// Is this our intended?
				if (comp->iCode == tniCodeNeedle)
				{
					// Combine from here on out
					while (comp->ll.next)
					{
						// Combine
						iComps_combineN(comp, 2, tniCodeNeedle, comp->iCat, comp->color);

						// Indicate the number combined
						++lnCombined;
					}
				}

				// Move to the next component
				comp = comp->ll.nextComp;
			}
			// When we get here, we're good
		}
		// Indicate the success rate at which we operated hitherto
		return(lnCombined);
	}




//////////
//
// Called to delete everything after the indicated component
//
//////
	u32 iComps_deleteAll_after(SLine* line, s32 tniCodeNeedle)
	{
		u32		lnDeleted;
		SComp*	comp;
		SComp**	compLast;


		// Make sure our environment is sane
		lnDeleted = 0;
		if (line && line->compilerInfo && line->compilerInfo->firstComp)
		{
			// Grab the first component
			comp		= line->compilerInfo->firstComp;
			compLast	= (SComp**)&line->compilerInfo->firstComp;

			// Iterate forward through all components
			while (comp)
			{
				// Is this our intended?
				if (comp->iCode == tniCodeNeedle)
				{
					// Combine from here on out
					while (comp)
					{
						// Indicate the number combined
						++lnDeleted;

						// Move to the next component
						comp = comp->ll.nextComp;
					}

					// Delete from here on out
					iComps_deleteAll_byFirstComp(compLast);
					break;
				}

				// Move to the next component
				compLast	= (SComp**)&comp->ll.next;
				comp		= comp->ll.nextComp;
			}
			// When we get here, we're good
		}
		// Indicate the success rate at which we operated hitherto
		return(lnDeleted);
	}




//////////
//
// Called to remove leading whitespaces
// Note:  This function can be called at any time.
//
//////
	SComp* iComps_migrate(SComp** compSource, SComp** compDestination, SComp* compToMove)
	{
		return((SComp*)iLl_migrate__llToOther((SLL**)compSource, (SLL**)compDestination, (SLL*)compToMove, true));
	}

	u32 iComps_remove_leadingWhitespaces(SLine* line)
	{
		u32		lnRemoved;
		SComp*	comp;


		// Make sure our environment is sane
		lnRemoved = 0;
		if (line && line->compilerInfo)
		{
			// Iterate through all looking for _ICODE_COMMENT_START
			comp = line->compilerInfo->firstComp;
			while (comp && comp->iCode == _ICODE_WHITESPACE)
			{
				// Migrate this whitespace from firstComp to firstWhitespace
				comp = iComps_migrate(&line->compilerInfo->firstComp, &line->compilerInfo->firstComp->firstWhitespace, comp);
				++lnRemoved;

				// comp is now pointing to what would've been comp->ll.next
				line->compilerInfo->firstComp = comp;
			}
		}

		// Indicate how many we removed
		return(lnRemoved);
	}




//////////
//
// Called to remove whitespaces.
// Note:  By the time this function is called, natural groupings should've already been
//        processed, such that all quoted text items are already combined into a single icode.
//
//////
	u32 iComps_remove_whitespaces(SLine* line)
	{
		u32		lnRemoved;
		SComp*	comp;


		// Make sure our environment is sane
		lnRemoved = 0;
		if (line && line->compilerInfo)
		{
			// Iterate through all looking for _ICODE_COMMENT_START
			comp = line->compilerInfo->firstComp;
			while (comp)
			{
				//////////
				// Is this a whitespace?
				//////
					while (comp && comp->iCode == _ICODE_WHITESPACE)
					{
						// Is it at the head of the class?
						if (line->compilerInfo->firstComp == comp)
							line->compilerInfo->firstComp = comp->ll.nextComp;

						// Migrate this whitespace to the whitespace area
						comp = iComps_migrate(&line->compilerInfo->firstComp, &line->compilerInfo->firstComp->firstWhitespace, comp);

						// Increase our counter
						++lnRemoved;
					}


				//////////
				// Continue on to next component
				//////
					if (comp)
						comp = comp->ll.nextComp;
			}
		}

		// Indicate how many we removed
		return(lnRemoved);
	}




//////////
//
// Called to remove any /* comments */ from the current chain of comps.
//
//////
	void iComps_remove_startEndComments(SLine* line)
	{
		SComp*	comp;
		SComp*	compNext;


		// Make sure our environment is sane
		if (line && line->compilerInfo)
		{
			// Iterate through all looking for _ICODE_COMMENT_START
			comp = line->compilerInfo->firstComp;
			while (comp)
			{
				//////////
				// Is this a start?
				//////
					if (comp->iCode == _ICODE_COMMENT_START)
					{
						// Delete everything forward until we reach _ICODE_COMMENT_END or the last comp
						while ((compNext = comp->ll.nextComp) && compNext->iCode != _ICODE_COMMENT_END)
							iComps_combineN(comp, 2, comp->iCode, comp->iCat, comp->color);

						// When we get here, we're sitting on the _ICODE_COMMENT_END
						if ((compNext = comp->ll.nextComp) && compNext->iCode == _ICODE_COMMENT_END)
							iComps_combineN(comp, 2, comp->iCode, comp->iCat, comp->color);

						// Migrate the (now single) comment
						comp = iComps_migrate(&line->compilerInfo->firstComp, &line->compilerInfo->firstComp->firstComment, comp);

						// Done
						return;
					}


				//////////
				// Continue on to next component
				//////
					if (comp)
						comp = comp->ll.nextComp;
			}
		}
	}




//////////
//
// Truncates the components at the first comment, leaving only things up to that point in place
//
//////
	s32 iComps_truncate_atComments(SLine* line)
	{
		u32		lnMigrated;
		SComp*	comp;


		// Make sure our environment is sane
		lnMigrated = 0;
		if (line && line->compilerInfo)
		{
			// Iterate through all looking for _ICODE_COMMENT
			for (comp = line->compilerInfo->firstComp; comp; comp = comp->ll.nextComp)
			{
				// Is this a comment?
				if (comp->iCode == _ICODE_COMMENT)
				{
					// Migrate to the components after into the leading comment
					while (comp->ll.nextComp)
					{
						// Combine these
						iComps_combineN(comp, 2, comp->iCode, comp->iCat, comp->color);

						// Increase our count
						++lnMigrated;
					}

					// Migrate the (now single) comment
					comp = iComps_migrate(&line->compilerInfo->firstComp, &line->compilerInfo->firstComp->firstComment, comp);

					// All done
					break;
				}
			}
		}

		// Indicate how many we migrated
		return(lnMigrated);
	}




//////////
//
// Called to combine casks
//
//////
	void iComps_combine_casks(SLine* line)
	{
		SComp* comp;


		// Make sure our environment is sane
		if (line && line->compilerInfo && line->compilerInfo->firstComp)
		{
			// See if there are any cask components on this line
			for (comp = line->compilerInfo->firstComp; comp; comp = comp->ll.nextComp)
			{
				// Is it a cask?
				if (between(comp->iCode, _ICODE_CASK_SIDE_MINIMUM, _ICODE_CASK_SIDE_MAXIMUM))
				{
					// WITH parameters
					iComps_combineAll_betweenTwo(line,		_ICODE_CASK_ROUND_OPEN_PARAMS,		_ICODE_CASK_ROUND_CLOSE_PARAMS,		_ICODE_CASK_ROUND_PARAMS,		_ICAT_CASK,		(SBgra*)&blackColor, false);
					iComps_combineAll_betweenTwo(line,		_ICODE_CASK_SQUARE_OPEN_PARAMS,		_ICODE_CASK_SQUARE_CLOSE_PARAMS,	_ICODE_CASK_SQUARE_PARAMS,		_ICAT_CASK,		(SBgra*)&blackColor, false);
					iComps_combineAll_betweenTwo(line,		_ICODE_CASK_TRIANGLE_OPEN_PARAMS,	_ICODE_CASK_TRIANGLE_CLOSE_PARAMS,	_ICODE_CASK_TRIANGLE_PARAMS,	_ICAT_CASK,		(SBgra*)&blackColor, false);
					iComps_combineAll_betweenTwo(line,		_ICODE_CASK_UTILITY_OPEN_PARAMS,	_ICODE_CASK_UTILITY_CLOSE_PARAMS,	_ICODE_CASK_TILDE_PARAMS,		_ICAT_CASK,		(SBgra*)&blackColor, false);
					iComps_combineAll_betweenTwo(line,		_ICODE_CASK_CODE_OPEN_PARAMS,		_ICODE_CASK_CODE_CLOSE_PARAMS,		_ICODE_CASK_CODE_PARAMS,		_ICAT_CASK,		(SBgra*)&blackColor, false);
					iComps_combineAll_betweenTwo(line,		_ICODE_CASK_AUTO_OPEN_PARAMS,		_ICODE_CASK_AUTO_CLOSE_PARAMS,		_ICODE_CASK_AUTO_PARAMS,		_ICAT_CASK,		(SBgra*)&blackColor, false);

					// NO parameters
					iComps_combineAll_betweenTwo(line,		_ICODE_CASK_ROUND_OPEN,				_ICODE_CASK_ROUND_CLOSE,			_ICODE_CASK_ROUND,				_ICAT_CASK,		(SBgra*)&blackColor, false);
					iComps_combineAll_betweenTwo(line,		_ICODE_CASK_SQUARE_OPEN,			_ICODE_CASK_SQUARE_CLOSE,			_ICODE_CASK_SQUARE,				_ICAT_CASK,		(SBgra*)&blackColor, false);
					iComps_combineAll_betweenTwo(line,		_ICODE_CASK_TRIANGLE_OPEN,			_ICODE_CASK_TRIANGLE_CLOSE,			_ICODE_CASK_TRIANGLE,			_ICAT_CASK,		(SBgra*)&blackColor, false);
					iComps_combineAll_betweenTwo(line,		_ICODE_CASK_UTILITY_OPEN,			_ICODE_CASK_UTILITY_CLOSE,			_ICODE_CASK_TILDE,				_ICAT_CASK,		(SBgra*)&blackColor, false);
					iComps_combineAll_betweenTwo(line,		_ICODE_CASK_CODE_OPEN,				_ICODE_CASK_CODE_CLOSE,				_ICODE_CASK_CODE,				_ICAT_CASK,		(SBgra*)&blackColor, false);
					iComps_combineAll_betweenTwo(line,		_ICODE_CASK_AUTO_OPEN,				_ICODE_CASK_AUTO_CLOSE,				_ICODE_CASK_AUTO,				_ICAT_CASK,		(SBgra*)&blackColor, false);

					// Done
					return;
				}
			}
		}
	}




//////////
//
// Fixes up common things found in VXB source code.
//
//////
	void iComps_fixup_naturalGroupings(SLine* line)
	{
		if (line && line->compilerInfo && line->compilerInfo->firstComp)
		{
			//////////
			// Fixup quotes, comments
			//////
				iComps_combineAll_between(line, _ICODE_SINGLE_QUOTE,	_ICODE_SINGLE_QUOTED_TEXT,	&colorSynHi_quotedText);
				iComps_combineAll_between(line, _ICODE_DOUBLE_QUOTE,	_ICODE_DOUBLE_QUOTED_TEXT,	&colorSynHi_quotedText);
				iComps_combineAll_after(line, _ICODE_LINE_COMMENT);


			//////////
			// Search for combinations which are adjacent sequences beginning with an underscore or alpha,
			// which then alternate in some form of alpha, numeric, underscore, etc., and translate to
			// alphanumeric.  For numeric it looks for +-999.99 completely adjacent, and combines into one.
			//////
				iComps_combine_adjacentAlphanumeric(line);
				iComps_combine_adjacentNumeric(line);
		}
	}




//////////
//
// Takes sequences like \{, \}, and \\ and replaces them solely with {, }, and \
//
//////
	s32 iComps_unescape_iCodes(SComp* compStart, s32 tniCode1, s32 tniCode2, s32 tniCode3, s32 tniCodeEscape)
	{
		s32		lnCount;
		SComp*	comp;
		SComp*	compNext;


		// Make sure our environment is sane
		lnCount = 0;
		if (compStart)
		{
			// Iterate through the line components
			for (comp = compStart; comp; comp = comp->ll.nextComp)
			{
				// Is it an escape?
				if (comp->iCode == tniCodeEscape)
				{
					// Is there a component after?
					if ((compNext = iComps_getNth(comp, 1)))
					{
						// Is it iCode1, iCode2, or iCode3
						if ((compNext->iCode == tniCode1 || compNext->iCode == tniCode2 || compNext->iCode == tniCode3))
						{
							// Are they directly adjacent?
							if (iiComps_areCompsAdjacent(comp, compNext))
							{
								// Remove the escape
								++lnCount;
								comp = iComps_delete(comp, true);
							}
						}
					}
				}
			}
		}

		// Indicate our count
		return(lnCount);
	}




//////////
//
// Called to copy the components to the indicated ending component, or the end of the line, whichever comes first
// Note:  If compEnd is NULL, it continues to the end of the line
//
//////
	// If tlMakeReferences, content is not physically copied to lineNew->sourceCode, but only references to the compStart->line->sourceCode content are made
	s32 iComps_copyTo(SLine* line, SComp* compStart, SComp* compEnd, bool tlMakeReferences)
	{
		s32		lnPass, lnCount, lnStart, lnEnd, lnLength;
		SComp*	comp;
		SComp*	compNew;


		// Make sure our environment is sane
		lnCount = 0;
		if (compStart->line && compStart->line->sourceCode)
		{
			// Pass 1 -- Count line length
			// Pass 2 -- Copy
			for (lnPass = 1; lnPass <= 2; lnPass++)
			{
				// Which pass?
				if (lnPass == 1)
				{

					//////////
					// Compute extents
					//////
						for (comp = compStart, lnStart = comp->line->sourceCode->length, lnEnd = 0; comp; comp = comp->ll.nextComp, ++lnCount)
						{

							// Update
							lnStart	= min(lnStart, comp->start);
							lnEnd	= max(lnEnd, comp->start + comp->length);

							// Are we done?
							if (compEnd && comp == compEnd)
								break;	// Yup

						}


					//////////
					// Allocate
					//////
						if (!tlMakeReferences)
						{
							// Length and allocation
							lnLength = lnEnd - lnStart;
							iDatum_allocateSpace(line->sourceCode, lnLength + 1);
							memset(line->sourceCode->data._s8, 32, lnLength);
						}


				} else {

					//////////
					// Copy
					// Note: There may be large gaps of whitespaces if comments were removed
					//////
						for (comp = compStart; comp; comp = comp->ll.nextComp, lnCount++)
						{

							//////////
							// Copy if need be
							//////
								if (!tlMakeReferences)
									memcpy(line->sourceCode->data._s8 + comp->start - lnStart, comp->line->sourceCode->data._cs8 + comp->start, comp->length);


							//////////
							// Append the component
							//////
								compNew = newAlloc(SComp, line->compilerInfo->firstComp);

							
							//////////
							// Copy
							//////
								if (compNew)
								{
									// Copy members
									iComps_copyMembers(compNew, comp, true/*isAllocated*/, false/*copyLl*/, ((tlMakeReferences) ? 0 : lnStart)/*backoff*/);

									// Update the new line if need be
									if (!tlMakeReferences)
										compNew->line = line;
								}


							//////////
							// Are we done?
							//////
								if (!compNew || (compEnd && comp == compEnd))
									break;	// Yup

						}

				}
			}
			// All done!
		}

		// Indicate our count
		return(lnCount);
	}




//////////
//
// Called to copy components based on feedback or guidance from a callback function
//
//////
	s32 iComps_copyTo_withCallback(SLine* line, SComp* compStart, SCallback* cb, bool tlMakeReferences)
	{
		s32		lnCount, lnPass, lnStart, lnEnd, lnLength;
		bool	llContinue;
		SComp*	comp;
		SComp*	compNew;


		// Make sure our environment is sane
		lnCount = 0;
		if (line && compStart && cb && cb->_func)
		{
			// Pass 1 -- Count line length
			// Pass 2 -- Copy
			for (lnPass = 1; lnPass <= 2; lnPass++)
			{
				// Which pass?
				if (lnPass == 1)
				{

					//////////
					// Compute extents
					//////
						lnStart		= compStart->line->sourceCode->length;
						lnEnd		= 0;
						cb->line	= line;
						for (comp = compStart, llContinue = true; llContinue && comp; comp= comp->ll.nextComp)
						{

							//////////
							// See if the next component should be included as well
							//////
								cb->comp	= comp;
								llContinue	= cb->func(cb);


							//////////
							// Update extents for this component
							//////
								lnStart	= min(lnStart, comp->start);
								lnEnd	= max(lnEnd, comp->start + comp->length);

						}

						// Prepare for copy if need be
						if (!tlMakeReferences)
						{
							// Length and allocation
							lnLength = lnEnd - lnStart;
							iDatum_allocateSpace(line->sourceCode, lnLength + 1);
							memset(line->sourceCode->data._s8, 32, lnLength);
						}


				} else {

					//////////
					// Copy
					// Note: There may be large gaps of whitespaces if comments were removed
					//////
						for (llContinue = true, comp = compStart; llContinue && comp; comp= comp->ll.nextComp, lnCount++)
						{

							//////////
							// See if the next component should be included as well
							//////
								cb->comp	= comp;
								llContinue	= cb->func(cb);


							//////////
							// Copy if need be
							//////
								if (!tlMakeReferences)
									memcpy(line->sourceCode->data._s8 + comp->start - lnStart, comp->line->sourceCode->data._cs8 + comp->start, comp->length);


							//////////
							// Append the component
							//////
								compNew = newAlloc(SComp, line->compilerInfo->firstComp);

							
							//////////
							// Copy
							//////
								if (compNew)
								{
									// Copy members
									iComps_copyMembers(compNew, comp, true/*isAllocated*/, false/*copyLl*/, ((tlMakeReferences) ? 0 : lnStart)/*backoff*/);

									// Update the new line if need be
									if (!tlMakeReferences)
										compNew->line = line;

								} else {
									// We're done
									break;
								}

						}

				}
			}
		}

		// Indicate our count
		return(lnCount);
	}




//////////
//
// Returns true of false if two components are directly adjacent (no whitespace between)
//
//////
	bool iiComps_areCompsAdjacent(SComp* compLeft, SComp* compRight)
	{
		// If [start+length] equals [start] of the next, they're adjacent
		return(compLeft->start + compLeft->length == compRight->start);
	}




//////////
//
// Returns the number of characters between two components.
//
//////
	s32 iiComps_get_charactersBetween(SComp* compLeft, SComp* compRight)
	{
		// Start of right component and end of left component
		return(compRight->start - (compLeft->start + compLeft->length));
	}




//////////
//
// Called to convert the value in this component to an s32 or s64 integer, or f64 floating point
//
//////
	s32 iComps_getAs_s32(SComp* comp)
	{
		s8 buffer[32];


		if (comp && comp->line && comp->line->sourceCode && comp->line->sourceCode->data._s8 && comp->line->sourceCode_populatedLength > 0)
		{
			// Copy to a buffer
			memcpy(buffer, comp->line->sourceCode->data._s8 + comp->start, min(comp->length, (s32)sizeof(buffer) - 1));
			buffer[comp->length] = 0;
			return(atoi(buffer));
		}
		
		// Component is not valid
		return(0);
	}

	s64 iComps_getAs_s64(SComp* comp)
	{
		s8 buffer[32];


		if (comp && comp->line && comp->line->sourceCode && comp->line->sourceCode->data._s8 && comp->line->sourceCode_populatedLength > 0)
		{
			// Copy to a buffer
			memcpy(buffer, comp->line->sourceCode->data._s8 + comp->start, min(comp->length, (s32)sizeof(buffer) - 1));
			buffer[comp->length] = 0;
			return(_atoi64(buffer));
		}

		// Component is not valid
		return(0);
	}

	f64 iComps_getAs_f64(SComp* comp)
	{
		s8 buffer[32];


		if (comp && comp->line && comp->line->sourceCode && comp->line->sourceCode->data._s8 && comp->line->sourceCode_populatedLength > 0)
		{
			// Copy to a buffer
			memcpy(buffer, comp->line->sourceCode->data._s8 + comp->start, min(comp->length, (s32)sizeof(buffer) - 1));
			buffer[comp->length] = 0;
			return(atof(buffer));
		}

		// Component is not valid
		return(0);
	}




//////////
//
// Called to get the value stored in the component as an s64.
//
// Note:  We simply process the component's content here.  No type checking.
// Note:  We expect that the component has been identified appropriately as a numeric type, and that
//        there is some character after which will cease its conversion, and thereby make it convert
//        without forcing a NULL in there at the end before converting.
//
//////
	s32 iiComps_getAs_s32(SComp* comp)
	{
		s8 buffer[32];

		memcpy(buffer, comp->line->sourceCode->data._s8 + comp->start, min(comp->length, (s32)sizeof(buffer) - 1));
		buffer[comp->length] = 0;
		return(atoi(buffer));
	}

	s64 iiComps_getAs_s64(SComp* comp)
	{
		s8 buffer[32];

		memcpy(buffer, comp->line->sourceCode->data._s8 + comp->start, min(comp->length, (s32)sizeof(buffer) - 1));
		buffer[comp->length] = 0;
		return(_atoi64(buffer));
	}

	f64 iiComps_getAs_f64(SComp* comp)
	{
		s8 buffer[32];

		memcpy(buffer, comp->line->sourceCode->data._s8 + comp->start, min(comp->length, (s32)sizeof(buffer) - 1));
		buffer[comp->length] = 0;
		return(atof(buffer));
	}

	// Note:  The name is only in scope so long as either comp exists (if valid), or *varSys2015 exists if comp was not valid
	// Note:  If comp was not valid, and varSys2015 was provided, *varSys2015 must be explicitly deleted at some point
	SDatum* iiComps_populateAs_datum(SDatum* datum, SComp* comp)
	{
		// Populate if possible
		if (datum && comp && comp->line && comp->line->sourceCode)
		{
			// Store the component's name
			datum->data._cs8	= comp->line->sourceCode->data._cs8 + comp->start;
			datum->length		= comp->length;
		}

		// Pass-thru
		return(datum);
	}




//////////
//
// Called to get the length of the contiguous components
//
//////
	s32 iComps_getContiguousLength(SComp* comp, s32 valid_iCodeArray[], s32 tnValid_iCodeArrayCount, s32* tnCount)
	{
		s32		lnCount, lnLength, lnThisSpacing;
		bool	llAtLeastOne, llIsValid;


		// Make sure our environment is sane
		lnCount		= 0;
		lnLength	= 0;
		if (comp)
		{
			//////////
			// Iterate so long as there are components after it
			//////
				lnThisSpacing	= -1;
				llIsValid		= true;
				llAtLeastOne	= false;
				while (comp->ll.next)
				{
					//////////
					// See if it's contiguously adjoined
					//////
						if ((lnThisSpacing = iiComps_get_charactersBetween(comp, comp->ll.nextComp)) != 0)
							break;		// We're done


					//////////
					// Validate if need be
					//////
						if (tnValid_iCodeArrayCount > 0 && valid_iCodeArray)
						{
							// We do need to validate
							if (!iiComps_validate(comp, valid_iCodeArray, tnValid_iCodeArrayCount))
							{
								// If we get here, it did not pass validation
								llIsValid = false;
								break;
							}
						}


					//////////
					// Increase our length
					//////
						lnLength += comp->length;


					//////////
					// Raise our flag and increase our count
					//////
						llAtLeastOne = true;
						++lnCount;


					//////////
					// Move to next comp
					//////
						comp = comp->ll.nextComp;
				}


			//////////
			// Do we need to add in the last component?
			//////
				if (!comp->ll.next && llAtLeastOne && llIsValid && lnThisSpacing == 0)
				{
					// Validate if need be
					if (tnValid_iCodeArrayCount > 0 && valid_iCodeArray)
					{
						// If it's valid, add it
						if (iiComps_validate(comp, valid_iCodeArray, tnValid_iCodeArrayCount))
						{
							lnLength += comp->length;	// It's valid
							++lnCount;
						}

					} else {
						// No validation, just add it in
						lnLength += comp->length;
						++lnCount;
					}
				}

		}

		// Store the count if need be
		if (tnCount)
			*tnCount = lnCount;

		// Indicate where we are
		return(lnLength);
	}




//////////
//
// Counts the number of components from here to the end of the chain
//
//////
	u32 iComps_count(SComp* comp)
	{
		return(iLl_count__llsToEnd((SLL*)comp));
	}




//////////
//
// Called to validate the indicated component against a valid array list
//
//////
	bool iiComps_validate(SComp* comp, s32 valid_iCodeArray[], s32 tnValid_iCodeArrayCount)
	{
		s32 lnI;


		// Iterate through the valid list
		for (lnI = 0; lnI < tnValid_iCodeArrayCount; lnI++)
		{
			// Does it match this one?
			if (comp->iCode == valid_iCodeArray[lnI])
				return(true);	// It matches
		}

		// If we get here, no match
		return(false);
	}




//////////
//
// Called to validate the contents of the component are comprised of only alphanumeric characters.
// This differs from the test of iCode == _ICODE_ALPH or iCode == _ICODE_ALPHANUMERIC, and is
// done on things which may have already been translated to others forms, but their fundamental
// data content may be alphanumeric, such as using the variable "text" for example, which is a
// known keyword, but can also be used as a variable name.
//
//////
	bool iiComps_isAlphanumeric_byContent(SComp* comp)
	{
		s32		lnI;
		char	c;


		// First character must be alpha
		if (isAlpha(comp->line->sourceCode->data._s8[comp->start]))
		{
			for (lnI = 1; lnI < comp->length; lnI++)
			{
				// Test this character
				c = comp->line->sourceCode->data._s8[comp->start + lnI];
				if (!isAlpha(c) && !isNumeric(c))
					return(false);
			}
			// If we get here, we're good
			return(true);
		}
		// If we get here, not alphanumeric
		return(false);
	}




//////////
//
// Visualizes the components in text form.
// Format:  [raw_text iCode,start,length]
//
//////
	s8* iComps_visualize(SComp* comp, s32 tnCount, s8* outputBuffer, s32 tnBufferLength, bool tlUseDefaultCompSearcher, SAsciiCompSearcher* tsComps1, SAsciiCompSearcher* tsComps2)
	{
		s32						lnI, lnJ, lnLength, lnOffset;
		bool					llFound;
		SAsciiCompSearcher*		lacs;
		s8*						lciCodeName;
		s8						accumBuffer[2048];


		//////////
		// Iterate through the comps one-by-one
		//////
			if (comp && outputBuffer && tnBufferLength > 0 && (tlUseDefaultCompSearcher || tsComps1 || tsComps2))
			{
				// Reset the display buffer
				memset(outputBuffer, 0, tnBufferLength);

				// Iterate through the comps
				for (lnI = 0, lnOffset = 0; lnI < tnCount && comp && lnOffset < tnBufferLength; comp = comp->ll.nextComp)
				{
					//////////
					// Lookup this comp
					//////
						for (lnJ = 0, llFound = false; lnJ < 3 && !llFound; lnJ++)
						{
							if (lnJ == 0 && tlUseDefaultCompSearcher)
							{
								// Search the standard complement
								lacs = &cgcFundamentalSymbols[0];

							} else if (lnJ == 1 && tsComps1) {
								// Search the primary components
								lacs = tsComps1;

							} else if (lnJ == 2 && tsComps2) {
								// Search the second custom components
								lacs = tsComps2;

							} else {
								// This one is not valid
								lacs = NULL;
							}


							//////////
							// Search for a match
							//////
								for ( ; lacs && lacs->iCode != 0 && lacs->length != 0; lacs++)
								{
									// Is this a match?
									if (comp->iCode == lacs->iCode && comp->iCat == lacs->iCat)
									{
										// This is a match, visualize it as:  [text]
										memset(accumBuffer, 0, sizeof(accumBuffer));
										sprintf(accumBuffer, "[");
										memcpy(accumBuffer + strlen(accumBuffer), comp->line->sourceCode->data._s8 + comp->start, min(comp->length, (s32)sizeof(accumBuffer) - 20));

										if ((lciCodeName = iiComps_visualize_lookup_iCode(comp->iCode)))	sprintf(accumBuffer + strlen(accumBuffer), " %s,", lciCodeName);
										else																sprintf(accumBuffer + strlen(accumBuffer), " %d,", comp->iCode);

										sprintf(accumBuffer + strlen(accumBuffer), "%u,%u]", comp->start, comp->length);

										// Copy to our output
										lnLength = min(tnBufferLength - lnOffset, (s32)strlen(accumBuffer));
										memcpy(outputBuffer + lnOffset, accumBuffer, lnLength);
										lnOffset += lnLength;

										// Are there combined references at this point?
										if (comp->firstCombined)
										{
											// Include any previously combined references for what they are
											sprintf(outputBuffer + lnOffset, "<!--");
											iComps_visualize(comp->firstCombined, iComps_count(comp->firstCombined), outputBuffer + lnOffset + 4, tnBufferLength - lnOffset - 4, tlUseDefaultCompSearcher, tsComps1, tsComps2);
											lnOffset = (s32)strlen(outputBuffer);
											sprintf(outputBuffer + lnOffset, "-->");
											lnOffset += 3;
										}

										// All done
										llFound = true;
										break;
									}
								}

						}


						//////////
						// If it wasn't found, we need to visualize it like this:  [iCode:text:length], like [5:hi:2]
						//////
							if (!llFound)
							{
								// Visualize the raw text as an unknown form
								memset(accumBuffer, 0, sizeof(accumBuffer));
								sprintf(accumBuffer, "[");
								memcpy(accumBuffer+ strlen(accumBuffer), comp->line->sourceCode->data._s8 + comp->start, min(comp->length, (s32)sizeof(accumBuffer) - 20));

								if ((lciCodeName = iiComps_visualize_lookup_iCode(comp->iCode)))	sprintf(accumBuffer + strlen(accumBuffer), " %s,", lciCodeName);
								else																sprintf(accumBuffer + strlen(accumBuffer), " %d,", comp->iCode);

								sprintf(accumBuffer + strlen(accumBuffer), "%u,%u]", comp->start, comp->length);

								// Copy to our output
								lnLength = min(tnBufferLength - lnOffset, (s32)strlen(accumBuffer));
								memcpy(outputBuffer + lnOffset, accumBuffer, lnLength);
								lnOffset += lnLength;

								// Are there combined references at this point?
								if (comp->firstCombined)
								{
									// Include any previously combined references for what they are
									sprintf(outputBuffer + lnOffset, "<!--");
									iComps_visualize(comp->firstCombined, iComps_count(comp->firstCombined), outputBuffer + lnOffset + 4, tnBufferLength - lnOffset - 4, tlUseDefaultCompSearcher, tsComps1, tsComps2);
									lnOffset = (s32)strlen(outputBuffer);
									sprintf(outputBuffer + lnOffset, "-->");
									lnOffset += 3;
								}
							}

				}
			}


		//////////
		// Return the pointer
		//////
			return(outputBuffer);
	}

	s8* iiComps_visualize_lookup_iCode(s32 tniCode)
	{
		switch (tniCode)
		{
			case _ICODE_ALPHA:						return("alp");
			case _ICODE_ALPHANUMERIC:				return("anu");
			case _ICODE_NUMERIC:					return("num");
			case _ICODE_DOUBLE_QUOTED_TEXT:
			case _ICODE_SINGLE_QUOTED_TEXT:			return("quote");
			default:								return(NULL);
		}
	}




//////////
//
// Scans from the indicated location forward until finding CR/LF or any combination thereof,
// nothing whitespaces, content, and total line length (including cr/lf combinations at the end)
//
//////
	u32 iBreakoutAsciiTextDataIntoLines_ScanLine(s8* tcData, u32 tnMaxLength, u32* tnLength, u32* tnWhitespaces)
	{
		u32 lnLength, lnWhitespaces, lnCRLF_Length;


		// Make sure we have something to do
		lnLength		= 0;
		lnWhitespaces	= 0;
		lnCRLF_Length	= 0;
		if (tcData && tnMaxLength > 0)
		{
			// Skip past any whitespaces
			lnWhitespaces = iSkip_whitespaces(tcData, tnMaxLength);
			if (tnWhitespaces)
				*tnWhitespaces = lnWhitespaces;


			// Skip to the ending carriage return / line feed
			lnLength = iSkip_toCrLf(tcData + lnWhitespaces, tnMaxLength - lnWhitespaces, &lnCRLF_Length);
			if (tnLength)
				*tnLength = lnLength;
		}
		// Return the total length
		return(lnWhitespaces + lnLength + lnCRLF_Length);
	}




//////////
//
// Searches the haystack for the indicated needle, and reports the position if found
//
// Returns:
//		true	- found, tnPosition is updated
//		false	- not found, tnPosition unchanged
//
//////
	bool iFindFirstOccurrenceOfAsciiCharacter(s8* tcHaystack, u32 tnHaystackLength, s8 tcNeedle, u32* tnPosition)
	{
		u32		lnI;
		bool	llFound;


		// Make sure our environment is sane
		llFound = false;
		if (tcHaystack && tnHaystackLength != 0)
		{
			// Repeat for the length of the string
			for (lnI = 0; lnI < tnHaystackLength; lnI++)
			{
				// See if this is the character we're after
				if (tcHaystack[lnI] == tcNeedle)
				{
					// We found it
					llFound = true;

					// Update caller's pointer if need be
					if (tnPosition)
						*tnPosition = lnI;

					// All done
					break;
				}
			}
			// When we get here, either found or not
		}
		// Indicate our found condition
		return(llFound);
	}




//////////
//
// Scans from the indicated location forward until finding a non-whitespace character
//
//////
	u32 iSkip_whitespaces(s8* tcData, u32 tnMaxLength)
	{
		u32 lnLength;


		// Make sure our environment's sane
		lnLength = 0;		// Initially indicate no whitespaces
		if (tcData && tnMaxLength > 0)
		{
			// While we encounter spaces or tabs, count them
			while (lnLength < tnMaxLength && (tcData[lnLength] == 32 || tcData[lnLength] == 9))
				++lnLength;
			// When we get here, lnLength is the number of whitespaces (if any)
		}
		// Indicate the total length encountered
		return(lnLength);
	}




//////////
//
// Scans from the indicated location forward until finding CR/LF or any combination thereof
//
//////
	u32 iSkip_toCrLf(s8* tcData, u32 tnMaxLength, u32* tnCRLF_Length)
	{
		u32 lnLength, lnCRLF_Length;


		// Make sure our environment's sane
		lnLength		= 0;		// Initially indicate a line length of 0
		lnCRLF_Length	= 0;		// Same for CR/LF length
		if (tcData && tnMaxLength > 0)
		{
			// While we do not counter a CR or LF, continue
			while (lnLength < tnMaxLength && tcData[lnLength] != 13 && tcData[lnLength] != 10)
				++lnLength;

			// See if we are done
			if (lnLength < tnMaxLength)
			{
				// We did not reach the end of the entire data available to us to search
				// So, when we get here, we're sitting on a CR or LF, which is the end of line
				if (tcData[lnLength] == 13)
				{
					// We're sitting on a carriage return
					// If the next character is a line feed, we count it
					if (tcData[lnLength + 1] == 10)		lnCRLF_Length = 2;		// We have a pair
					else								lnCRLF_Length = 1;		// Just the one

				} else {
					// We know we're sitting on a line feed
					// If the next character is a carriage return, we count it
					if (tcData[lnLength + 1] == 13)		lnCRLF_Length = 2;		// We have a pair
					else								lnCRLF_Length = 1;		// Just the one
				}

			} else {
				// We reached the end
				// We don't do anything here, but just return the length
			}
		}
		// When we get here, return the lengths
		// The CR/LF length
		if (tnCRLF_Length)
			*tnCRLF_Length = lnCRLF_Length;

		// The stuff before length :-)
		return(lnLength);
	}




//////////
//
// Search the haystack for the needle, the haystack can be tupels, as in "_az" meaning
// (is it between "a" and "z" inclusive?)  To set this condition, use a length of 1,
// a leading "_" in tcHaystack, and two characters (one of which must NOT be NULL) after.
//
// Examples:
//		_az			= lower-case a to z inclusive
//		_AZ			= upper-case a to z inclusive
//		_09			= numeric 0 to 9 inclusive
//		_azAZ09		= any of the above in a single succession
//		_azAZ09__	= any of the above plus an underscore character (it must be done twice because of the from/to pattern
//
// Returns:
//		0		= matches
//		!0		= does not tmach
//
//////
	s32 iComps_xlatToComps_withTest(cu8* tcHaystack, cu8* tcNeedle, s32 tnLength)
	{
		u32		lnI;
		bool	llCase;


		// Make sure our environment is sane
		if (tnLength != 0)
		{
			// See if we're a signed or unsigned compare
			if (tnLength < 0)
			{
				// Case-sensitive compare
				tnLength	= -tnLength;
				llCase		= true;

			} else {
				// Case-insensitive compare
				llCase		= false;
			}

			// See if we're looking for a tuple, or a regular compare
			if (tcHaystack[0] == '_' && tnLength == 1)
			{
				// It's an explicit match of a range (this is ALWAYS subject to case as it is an explicit range)
				for (lnI = 1; tcHaystack[lnI] != 0 && tcHaystack[lnI + 1] != 0; lnI += 2)
				{
					//		within the range low			.........			up to the range high
					if (tcNeedle[0] >= tcHaystack[lnI]			&&		tcNeedle[0] <= tcHaystack[lnI + 1])
						return(0);		// It's a match, needle is in the range
				}
				// Not a match, will fall through to below

			} else {
				// Just a regular compare
				if (llCase)		return(  memcmp((s8*)tcHaystack, (s8*)tcNeedle, tnLength));
				else			return(_memicmp((s8*)tcHaystack, (s8*)tcNeedle, tnLength));
			}
		}
		// If we get here, no match
		return(-1);
	}




//////////
//
// Callback, used to translate existing components into other components
// Note:  Always returns false, so it will continue being fed every component
//
//////
	bool iiComps_xlatToOthers_callback(SStartEndCallback* cb)
	{
		s32						lnLacsLength;
		SComp*					comp;
		SAsciiCompSearcher*		lacs;


		// Make sure the environment is sane
		if (cb && cb->ptr)
		{
			// Grab our pointers into recognizable thingamajigs
			comp	= cb->ptrComp;
			lacs	= (SAsciiCompSearcher*)cb->extra;

			// Iterate through this item to see if any match
			for (	/* lacs is initialize above */;
					lacs->length != 0;
					lacs++		)
			{
				// Grab the normalized length
				lnLacsLength = abs(lacs->length);

				// We only test if they're the same length
				if (lnLacsLength == comp->length || (lacs->repeats && lnLacsLength <= comp->length))
				{
					// We only test if this item is not the first item on line, or if must be the first
					// item on the line, then this component must be the first component on the line.  Simple, yes? :-)
					if (!lacs->firstOnLine || !comp->ll.prev)
					{
						// Physically conduct the exact comparison
						if (iComps_xlatToComps_withTest(lacs->keyword_cu8,
														comp->line->sourceCode->data._u8 + comp->start,
														lacs->length) == 0)
						{
							// This is a match
							// Convert it, translate it, whatever you want to call it, just make it be the new code, per the user's request, got it? :-)
							comp->iCode = lacs->iCode;
							// All done with this component
							break;
						}
					}
				}
			}

		}
		// We always simulate a false condition so we'll keep receiving each item
		return(false);
	}




//////////
//
// Called as a callback from the custom handler callback function, to do some manual insertion.
// Note:  If a rogue component is inserted here, one not already defined in the ref's SOssLine parent,
//        then it will need to be either manually added to the line->comps, or manually tended to.
//
//////
	void iiComps_xlatToOthers_callback__insertCompByCompCallback(SComp* compRef, SComp* compNew, bool tlInsertAfter)
	{
// TODO:  untested code, breakpoint and examine
debug_break;
		// Make sure our environment is sane
		if (compRef && compNew)
		{
			// Before or after?
			if (tlInsertAfter)
			{
				// Add the new comp after the reference comp
				if (compRef->ll.next)
					compRef->ll.next->prev	= (SLL*)compNew;	// One originally after ref points back to new

				compNew->ll.next	= compRef->ll.next;			// New points forward to the one originally after ref
				compNew->ll.prev	= (SLL*)compRef;			// New points back to ref
				compRef->ll.next	= (SLL*)compNew;			// Ref points forward to new

			} else {
				// Add the new comp before the reference comp
				if (compRef->ll.prev)
					compRef->ll.prev->next	= (SLL*)compNew;	// One originally before ref points forward to new

				compNew->ll.next	= (SLL*)compRef;			// New points forward to ref
				compNew->ll.prev	= compRef->ll.prev;			// New points back to the one originally before ref
				compRef->ll.prev	= (SLL*)compNew;			// Ref points back to new
			}
		}
	}




//////////
//
// Called as a callback from the custom handler callback function, to do some manual insertion.
//
//////
	void iiComps_xlatToOthers_callback__insertCompByParamsCallback(SComp* compRef, SLine* line, u32 tniCode, u32 tnStart, s32 tnLength, bool tlInsertAfter)
	{
		SComp* compNew;
		SComp* compRoot;


// TODO:  untested code, breakpoint and examine
debug_break;
		// Make sure our environment is sane
		if (compRef && line && line->compilerInfo)
		{
			// Create a copy
			compRoot	= NULL;
			compNew		= iComps_new(&compRoot, NULL, NULL, NULL);
			if (compNew)
			{
				// Copy the normal members
				iComps_copyMembers(compNew, compRef, true, false, 0);

				// Populate it
				compNew->line		= line;
				compNew->iCode		= tniCode;
				compNew->start		= tnStart;
				compNew->length		= tnLength;

				// Add the new component as a component
				iiComps_xlatToOthers_callback__insertCompByCompCallback(compRef, compNew, tlInsertAfter);
			}
		}
	}




//////////
//
// Called as a callback from the custom handler callback function, to do delete the
// indicated component.
//
//////
	void iiComps_xlatToOthers_callback__deleteCompsCallback(SComp* comp, SLine* line)
	{
// TODO:  untested code, breakpoint and examine
debug_break;
		//////////
		// Disconnect the component from its siblings
		//////
			// Make the one before point forward to one after
			if (comp->ll.prev)
				comp->ll.prev->next = comp->ll.next;

			// Make the one after point back to the one before
			if (comp->ll.next)
				comp->ll.next->prev = comp->ll.prev;


		//////////
		// Delete it from the list of known components.
		// Component go bye bye. :-)
		//////
			if (line)
			{
				// Delete the entry from line->comps
				iLl_delete__ll((SLL*)comp, true);

			} else {
				// Free the rogue entry
				free(comp);
			}
	}




//////////
//
// Called as a callback from the custom handler callback function, to clone the indicated
// component.  If line is not NULL, the component is automatically added to line->comps;
//
//////
	SComp* iiComps_xlatToOthers_callback__cloneCompsCallback(SComp* comp, SLine* line)
	{
		SComp* compNew;
		SComp* compRoot;


// TODO:  untested code, breakpoint and examine
debug_break;
		// Make sure our environment is sane
		compNew = NULL;
		if (comp)
		{
			// Are we adding to to a line?
			if (line && line->compilerInfo)
			{
				// Add the new component to line->comps
				compNew = iComps_new(&line->compilerInfo->firstComp, NULL, NULL, NULL);

			} else {
				// Just create a rogue one
				compRoot = NULL;
				compNew = iComps_new(&compRoot, NULL, NULL, NULL);
			}

			// Was it valid?
			if (compNew)
			{
				// Populate it
				compNew->line		= line;
				compNew->iCode		= comp->iCode;
				compNew->start		= comp->start;
				compNew->length		= comp->length;
				// All done!
			}
		}

		// Return our new one, no matter if it was a success or not
		return(compNew);
	}




//////////
//
// Called as a callback from the custom handler callback function, to do merge components into
// a new one, and delete the one(s) which were merged.
//
// NOTE:  It's theoretically possible that there could be a gap here, such as a component next to
//        another component where there used to be a whitespace inbetween (or anything else), so
//        the components are no longer right by each other.  The caller will have to manually
//        handle that condition.
//
//////
	SComp* iiComps_xlatToOthers_callback__mergeCompsCallback(SComp* comp, SLine* line, u32 tnCount, u32 tniCodeNew)
	{
		u32			lnI;
		SComp*	compThis;


// TODO:  untested code, breakpoint and examine
debug_break;
		// Make sure our environment is sane
		if (comp)
		{
			// Iterate for each merging
			for (lnI = 1, compThis = comp->ll.nextComp; compThis && lnI < tnCount; lnI++, compThis = comp->ll.nextComp)
			{
				// Absorb compThis's length into comp's "collective"
				comp->length += compThis->length;

				// Delete this component
				iiComps_xlatToOthers_callback__deleteCompsCallback(compThis, comp->line);

				// Note:  compThis is always assigned comp->ll.next, because its next component keeps being updated after the delete
			}
			// When we get here, everything's merged
		}
		// Return the original component as a pass through (in case this is used as an intermediate function)
		return(comp);
	}




//////////
//
// Called to append an error to the indicated component
//
//////
	void iComp_appendError(SComp* comp, u32 tnErrorNum, cu8* tcMessage)
	{
		if (comp && comp->line)
			iLine_appendError(comp->line, tnErrorNum, tcMessage, comp->start, comp->length);
	}




//////////
//
// Called to append a warning to the indicated component
//
//////
	void iComp_appendWarning(SComp* comp, u32 tnWarningNum, cu8* tcMessage)
	{
		if (comp && comp->line)
			iLine_appendWarning(comp->line, tnWarningNum, tcMessage, comp->start, comp->length);
	}




//////////
//
// Called to report the indicated message
//
//////
	void iComp_reportWarningsOnRemainder(SComp* comp, u32 tnWarningNum, cu8* tcMessage)
	{
		while (comp)
		{
			// Append the warning
			iComp_appendWarning(comp, tnWarningNum, ((tcMessage) ? tcMessage : (u8*)"unspecified warning"));

			// Move to next component
			comp = comp->ll.nextComp;
		}
	}




//////////
//
// Called to create a new line
//
//////
	SLine* iLine_createNew(bool tlAllocCompilerInfo)
	{
		SLine* line;


		// Allocate and initialize
		line = (SLine*)malloc(sizeof(SLine));
		if (line)
		{

			// Reset
			memset(line, 0, sizeof(SLine));

			// Add SCompiler if need be
			if (tlAllocCompilerInfo)
				line->compilerInfo = iCompiler_allocate(line);

		}

		// Indicate our status
		return(line);
	}




//////////
//
// Called to append a new line to a chain (without regards to honoring the chain)
//
//////
	SLine* iLine_appendNew(SLine* line, bool tlAllocCompilerInfo)
	{
		// Append the line to the chain
		line->ll.nextLine = iLine_createNew(tlAllocCompilerInfo);

		// Indicate the new line
		return(line->ll.nextLine);
	}




//////////
//
// Called to insert a new line to a chain
//
//////
	SLine* iLine_insertNew(SLine* lineRef, bool tlAllocCompilerInfo, bool tlAfter)
	{
		SLine*	lineNew;


		// Append the line to the chain
		lineNew = iLine_createNew(tlAllocCompilerInfo);
		if (lineNew)
			iLl_insert__ll((SLL*)lineNew, (SLL*)lineRef, tlAfter);

		// Indicate the new line
		return(lineNew);
	}




//////////
//
// Called to append an error the indicated source code line
//
//////
	void iLine_appendError(SLine* line, u32 tnErrorNum, cu8* tcMessage, u32 tnStartColumn, u32 tnLength)
	{
		if (line && line->compilerInfo)
			iNoteLog_create(&line->compilerInfo->firstInquiry, line, tnStartColumn, tnStartColumn + tnLength, tnErrorNum, tcMessage);
	}




//////////
//
// Called to append a warning to the indicated source code line
//
//////
	void iLine_appendWarning(SLine* line, u32 tnWarningNum, cu8* tcMessage, u32 tnStartColumn, u32 tnLength)
	{
		if (line && line->compilerInfo)
			iNoteLog_create(&line->compilerInfo->firstInquiry, line, tnStartColumn, tnStartColumn + tnLength, tnWarningNum, tcMessage);
	}




//////////
//
// Called to scan forward across multiple lines for a component.
//
// Note:	Incoming comp need not be a component of incoming line, but once
//			comp->ll.nextComp is NULL, line->ll.nextLine will be used
//////
	// Note:  cb->lFound also indicates if something was found
	bool iLine_scanComps_forward_withCallback(SLine* line, SComp* comp, SCallback* cb, bool tlSkipFirst)
	{
		// Make sure our environment is sane
		if (line && comp && cb && cb->_func)
		{

			//////////
			// Skip to next component if need be
			//////
				if (tlSkipFirst)
					goto goto_next_component;


			//////////
			// Iterate until found
			//////
				cb->line	= line;
				cb->comp	= comp;
				cb->flag	= false;
				while (cb->line && cb->comp)
				{

					//////////
					// Callback returns true if we should continue searching
					//////
						if ((cb->flag = !cb->func(cb)))
							break;


					//////////
					// Skip to next component, which could move us on to the next line
					//////
goto_next_component:
						if (!cb->comp->ll.nextComp)
						{
							// Move to next line
							if (!cb->line->ll.nextLine || !cb->line->ll.nextLine->compilerInfo)
								break;	// We've reached the end

							// Next line
							cb->line = cb->line->ll.nextLine;
							cb->comp = cb->line->compilerInfo->firstComp;

						} else {
							// Move to the next component
							cb->comp = cb->comp->ll.nextComp;
						}

				}

		} else {
			// Something's invalid in our parameters
			if (cb)
			{
				cb->line	= NULL;
				cb->comp	= NULL;
				cb->flag	= false;
			}
		}

		// Indicate our return value
		return(cb->flag);
	}




//////////
//
// Called to convert all \{ and \} (for example) to just { and }
//
//////
	s32 iLines_unescape_iCodes(SLine* lineStart, s32 tniCode1, s32 tniCode2, s32 tniCode3, s32 tniCodeEscape)
	{
		s32		lnUnescapeCount;
		SLine*	line;


		// Iterate through each line removing all escaped components
		for (line = lineStart, lnUnescapeCount = 0; line; line = line->ll.nextLine)
		{
			// Remove escapes from this line
			if (line->compilerInfo && line->compilerInfo->firstComp)
				lnUnescapeCount += iComps_unescape_iCodes(line->compilerInfo->firstComp, tniCode1, tniCode2, tniCode3);
		}

		// Indicate how many were unescaped
		return(lnUnescapeCount);
	}




//////////
//
// Moves all lines from one file to another, before or after the target line
//
//////
	s32 iLine_migrateLines(SLine** linesFrom, SLine* lineTarget)
	{
		s32		lnLineCount;
		SLine*	temp;
		SLine*	line;


		// Make sure our environment is sane
		lnLineCount	= 0;
		if (linesFrom && *linesFrom && lineTarget)
		{
// TODO:  Untested.  Breakpoint and examine.
debug_break;
			//////////
			// Point lineTarget to the start of the line block
			//////
				temp						= lineTarget->ll.nextLine;
				lineTarget->ll.nextLine		= *linesFrom;
				(*linesFrom)->ll.prevLine	= lineTarget;


			//////////
			// Point the last line of the *linesFrom chain to the temp
			//////
				line		= *linesFrom;
				lnLineCount	= 1;

				// Iterate through until we reach the last line
				while (line->ll.nextLine)
				{
					// Increase our line count
					++lnLineCount;

					// Move to the next line
					line = line->ll.nextLine;
				}

				line->ll.nextLine	= temp;		// Last line points to the original line after where we inserted
				temp->ll.prevLine	= line;		// The original line after where we inserted points back to the new line

		}

		// Indicate our count
		return(lnLineCount);
	}




//////////
//
// Called to copy everything from the starting component on the starting line, to the ending component on the ending line.
// Note:  It will left-justify the starting component if specified, otherwise it will prefix with spaces
//
//////
	SLine* iLine_copyComps_toNewLines(SLine* lineStart, SComp* compStart, SLine* lineEnd, SComp* compEnd, bool tlLeftJustifyStart, bool tlSkipBlankLines)
	{
		SLine*	lineNew;
		SLine*	lineCopy;


		// Make sure our environment is sane
		if (lineStart && compStart && lineEnd && compEnd && !(lineStart == lineEnd && compStart == compEnd))
		{

			//////////
			// First line
			//////
				// New line
				if (!(lineNew = iLine_createNew(true)))
					return(NULL);

				// Copy components
				iComps_copyTo(lineNew, compStart, compEnd, false);

				// If we're only doing one line, we're done
				if (lineStart == lineEnd)
					return(lineNew);


			//////////
			// Middle lines
			//////
				for (lineCopy = lineStart->ll.nextLine; lineCopy && lineCopy != lineEnd; lineCopy = lineCopy->ll.nextLine)
				{
					// Skip blank lines if need be
					if (!tlSkipBlankLines || !lineCopy->compilerInfo->firstComp)
					{
						// New line
						lineNew = iLine_appendNew(lineNew, true);

						// Copy all line components up to the end
						iComps_copyTo(lineNew, lineCopy->compilerInfo->firstComp, compEnd, false);
					}
				}


			//////////
			// Last line
			//////
				// Create the new last line
				if (lineCopy != lineEnd)
				{
					// New line
					lineNew = iLine_appendNew(lineNew, true);

					// Copy all line components up to the end
					iComps_copyTo(lineNew, lineCopy->compilerInfo->firstComp, compEnd, false);
				}
				

		} else {
			// Invalid content, just create a blank line
			lineNew = iLine_createNew(true);
			// Note: We don't reposition the component here because nothing moved
		}


		//////////
		// Indicate our status
		//////
			// Note:  Right now the next component should be the next one from lineEnd and compEnd
			return(lineNew);

	}




//////////
//
// Called to copy lines until the continuation character is no longer found
//
//////
	struct S_iLine_copyComps_toNewLines_untilTerminating
	{
		bool	lContinuationFound;
	};

	SLine* iLine_copyComps_toNewLines_untilTerminating(SLine* lineStart, SComp* compStart, s32 tniCodeContinuation, bool tlLeftJustifyStart, bool tlSkipBlankLines, SCallback* cb)
	{
		SLine*		lineNew;
		SLine*		lineCopy;
		S_iLine_copyComps_toNewLines_untilTerminating x;


		// Make sure our environment is sane
		if (lineStart && compStart && cb)
		{

			//////////
			// First line
			//////
				// New line
				if (!(lineNew = iLine_createNew(true)))
					return(NULL);

				// Copy components smartly
				memset(cb, 0, sizeof(*cb));
				memset(&x, 0, sizeof(x));
				cb->_func	= (sptr)&iiLine_copyComps_toNewLines_untilTerminating__callback;
				cb->x		= (void*)&x;
				iComps_copyTo_withCallback(lineNew, compStart, cb, false);

				// If the last component was not a continuation character, we're done
				if (!x.lContinuationFound)
					return(lineNew);


			//////////
			// Following lines
			//////
				for (lineCopy = lineStart->ll.nextLine; x.lContinuationFound && lineCopy; lineCopy = lineCopy->ll.nextLine)
				{
					// Skip blank lines if need be
					if (!tlSkipBlankLines || lineCopy->compilerInfo->firstComp->iCode != _ICODE_BACKSLASH)
					{
						// New line
						lineNew = iLine_appendNew(lineNew, true);

						// Copy all line components up to the end
						iComps_copyTo_withCallback(lineNew, lineCopy->compilerInfo->firstComp, cb, false);
					}
				}
				

		} else {
			// Invalid content, just create a blank line
			lineNew = iLine_createNew(true);
			// Note: We don't reposition the component here because nothing moved
		}


		//////////
		// Indicate our status
		//////
			// Note:  Right now the next component should be the next one from lineEnd and compEnd
			return(lineNew);

	}

	// Return indicates if copying should continue
	bool iiLine_copyComps_toNewLines_untilTerminating__callback(SCallback* cb)
	{
		S_iLine_copyComps_toNewLines_untilTerminating* x;
		SComp* compNext;


		//////////
		// Get our x and next component
		//////
			x			= (S_iLine_copyComps_toNewLines_untilTerminating*)cb->x;
			compNext	= cb->comp->ll.nextComp;


		//////////
		// Get the components
		//////
			if (!compNext)
			{
				// No continuation was found
				x->lContinuationFound = false;

				// And we're stopping after this component
				return(false);
			}


		//////////
		// If it's a backslash, and the component after doesn't exist, then it's a continuation character
		//////
			x->lContinuationFound = (compNext->iCode == _ICODE_BACKSLASH && !compNext->ll.nextComp);


		//////////
		// We continue so long as there are more components to copy (until we reach the continuation character \)
		//////
			return(!x->lContinuationFound);

	}




//////////
//
// Called to skip to the next component
//
//////
	s32 iiLine_skipTo_nextComp(SLine** lineProcessing, SComp** compProcessing)
	{
		s32		lnCount;
		SComp*	comp;
		SLine*	line;


		//////////
		// Grab our real parameters
		//////
			comp = *compProcessing;
			line = *lineProcessing;


		//////////
		// Is there another component
		//////
			if (comp->ll.nextComp)
			{
				// Another component on the line
				*compProcessing = comp->ll.nextComp;
				return(1);
			}


		//////////
		// Need to move to next line
		//////
			if (!line->ll.nextLine)
				return(-1);	// Nowhere to move


		//////////
		// Iterate down and right until we find another component
		//////
			lnCount = 0;
			while (line && line->ll.nextLine)
			{

				//////////
				// Increase our movement count
				//////
					++lnCount;


				//////////
				// Move to the next line
				//////
					line			= line->ll.nextLine;
					*lineProcessing	= line;


				//////////
				// Is there a component here?
				//////
					if (line->compilerInfo && line->compilerInfo->firstComp)
					{
						// Set the component
						*compProcessing = line->compilerInfo->firstComp;

						// Indicate how far we traversed
						return(lnCount);
					}


				//////////
				// No component yet
				//////
					*compProcessing	= NULL;

			}


		//////////
		// If we get here, end of file, line is pointing to the last line
		//////
			return(-1);

	}




//////////
//
// Called to skip to the previous component
//
//////
	s32 iiLine_skipTo_prevComp(SLine** lineProcessing, SComp** compProcessing)
	{
		s32		lnCount;
		SComp*	comp;
		SLine*	line;


		//////////
		// Grab our real parameters
		//////
			comp = *compProcessing;
			line = *lineProcessing;


		//////////
		// Is there another component
		//////
			if (comp->ll.prevComp)
			{
				// Is there a previous component on the line
				*compProcessing = comp->ll.prevComp;
				return(1);
			}


		//////////
		// Need to move to previous line
		//////
			if (!line->ll.prevLine)
				return(-1);	// Nowhere to move


		//////////
		// Iterate down and right until we find another component
		//////
			lnCount = 0;
			while (line && line->ll.prevLine)
			{

				//////////
				// Increase our movement count
				//////
					++lnCount;


				//////////
				// Move to the previous line
				//////
					line			= line->ll.prevLine;
					*lineProcessing	= line;


				//////////
				// Is there a component here?
				//////
					if (line->compilerInfo && line->compilerInfo->firstComp)
					{

						//////////
						// Move to the last component on the line
						//////
							comp = line->compilerInfo->firstComp;
							while (comp->ll.nextComp)
								comp = comp->ll.nextComp;


						//////////
						// Set the component and indicate how far we traversed
						//////
							*compProcessing = comp;
							return(lnCount);

					}


				//////////
				// No component yet
				//////
					*compProcessing	= NULL;

			}


		//////////
		// If we get here, beginning of file, line is pointing to the first line
		//////
			return(-1);

	}




//////////
//
// Allocates an SCompiler structure.  Initializes it to all NULLs.
//
//////
	SCompiler* iCompiler_allocate(SLine* parent)
	{
		SCompiler* compilerNew;


		// Allocate and initialize
		compilerNew = (SCompiler*)malloc(sizeof(SCompiler));
		if (compilerNew)
		{
			// Initialize
			memset(compilerNew, 0, sizeof(SCompiler));
			compilerNew->parent = parent;
		}

		// Indicate our status
		return(compilerNew);
	}




//////////
//
// Called to delete the previous allocated compiler data
//
//////
	void iCompiler_delete(SCompiler** compilerInfoRoot, bool tlDeleteSelf)
	{
		SCompiler* compilerInfo;


		// Make sure our environment is sane
		if (compilerInfoRoot && (compilerInfo = *compilerInfoRoot))
		{
			// Delete the source code
			iDatum_delete(&compilerInfo->sourceCode);

			// Delete the items here
			iNoteLog_removeAll(&compilerInfo->firstWarning);
			iNoteLog_removeAll(&compilerInfo->firstInquiry);
			iNoteLog_removeAll(&compilerInfo->firstNote);

			// Delete regular components
			iComps_deleteAll_byFirstComp(&compilerInfo->firstComp);

			// Delete self if need be
			if (tlDeleteSelf)
			{
				*compilerInfoRoot = NULL;
				free(compilerInfo);
			}
		}
	}




//////////
//
// Called to create a new note
//
//////
	SNoteLog* iNoteLog_create(SNoteLog** noteRoot, SLine* line, u32 tnStart, u32 tnEnd, u32 tnNumber, cu8* tcMessage)
	{
		SNoteLog* note;


		// Create the new note
		note = (SNoteLog*)iLl_appendNew__llAtEnd((SLL**)noteRoot, sizeof(SNoteLog));
		if (note)
		{
			// Initialize it
			memset(note, 0, sizeof(SNoteLog));

			// Populate it
			GetLocalTime(&note->time);
			note->line		= line;
			note->start		= tnStart;
			note->end		= tnEnd;
			note->number	= tnNumber;
			note->note		= iDatum_allocate(tcMessage, -1);
		}

		// Indicate our status
		return(note);
	}

	SNoteLog* iNoteLog_create(SNoteLog** noteRoot, SComp* comp, u32 tnNumber, cu8* tcMessage)
	{
		if (comp)		return(iNoteLog_create(noteRoot, comp->line, comp->start, comp->start + comp->length - 1, tnNumber, tcMessage));
		else			return(NULL);
	}




//////////
//
// Called to remove all compile notes in the chain
//
//////
	void iNoteLog_removeAll(SNoteLog** noteRoot)
	{
		// Make sure our environment is sane
		if (noteRoot && *noteRoot)
			iLl_delete__llChain((SLL**)noteRoot);
	}
