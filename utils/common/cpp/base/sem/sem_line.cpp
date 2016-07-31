//////////
//
// /libsf/source/vjr/source/sem/sem_line.cpp
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
// Version 0.58
// Copyright (c) 2014-2015 by Rick C. Hodgin
//////
// Last update:
//     Jul.06.2014
//////
// Change log:
//     Jul.06.2014 - Initial creation
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
//




//////////
//
// Called to make sure enough information is populated currently in the sem->ecCursorLine->sourceCode
// buffer for the new indicated line length.
//
//////
	bool iLine_ensureLineLength(SEM* sem, s32 newLineLength)
	{
		SLine* line;


		// Make sure the environment is sane
		if (sem && sem->line_cursor)
		{
			// Has this line had its data allocated?
			line = sem->line_cursor;
			if (!line->sourceCode._data)
			{
				// We need to allocate the initial data block
				iDatum_allocateSpace(&line->sourceCode, max((s32)_SEM_MINIMUM_LINE_ALLOCATION_LENGTH, newLineLength));
				line->populatedLength = 0;
			}

			// Is there room from where we are to the new line length?
			if (line->sourceCode.length > newLineLength)
				return(true);		// We're good

			// If we get here, we need to reallocate
			return(iDatum_resize(&line->sourceCode, newLineLength + _SEM_MINIMUM_LINE_ALLOCATION_LENGTH));
		}
		// If we get here, failure
		return(false);
	}




//////////
//
// Free the edit chain
//
//////
	void iLine_free(SLine** root, bool tlDeleteSelf)
	{
		SLine*		line;
		SLine*		lineNext;


		// Make sure our environment is sane
		if (root && *root)
		{
			//////////
			// Repeat throughout the entire chain
			//////
				line = *root;
				while (line)
				{
					//////////
					// Note next item in chain
					//////
						lineNext = (SLine*)line->ll.next;


					//////////
					// Delete any extra information associated with this chain entry
					//////
						iExtraInfo_removeAll(&line->extra_info);


					//////////
					// Delete this item's components and source code references
					//////
						iComps_deleteAll_byLine(line);
						iDatum_delete(&line->sourceCode, false);


					//////////
					// Free self
					//////
						if (tlDeleteSelf)
							free(line);


					//////////
					// Move to next item in the chain
					//////
						line = lineNext;
				}


			//////////
			// Free self
			//////
				if (tlDeleteSelf)
					*root = NULL;	// It would've been freed above, so we just update the pointer
		}
	}




//////////
//
// Called to create a new line
//
//////
	SLine* iLine_createNew(void)
	{
		SLine* line;


		// Allocate and initialize
		line = (SLine*)malloc(sizeof(SLine));
		if (line)
		{
			// Initialize
			memset(line, 0, sizeof(SLine));

			// Store uid
			line->uid = iiComps_getNextUid();
		}

		// Indicate our status
		return(line);
	}




//////////
//
// Called to append a new line to a chain (without regards to honoring the chain)
//
//////
	SLine* iLine_appendNew(SLine* line)
	{
		// Append the line to the chain
		line->ll.nextLine = iLine_createNew();

		// Indicate the new line
		return(line->ll.nextLine);
	}




//////////
//
// Called to insert a new line to a chain
//
//////
	SLine* iLine_insertNew(SLine* lineRef, bool tlAfter)
	{
		SLine*	lineNew;


		// Append the line to the chain
		lineNew = iLine_createNew();
		if (lineNew)
			iLl_insert__ll((SLL*)lineNew, (SLL*)lineRef, tlAfter);

		// Indicate the new line
		return(lineNew);
	}




//////////
//
// Insert the indicated line before or after the indicated line
//
//////
	bool iLine_insert(SLine* lineRef, SLine* lineNew, bool tlAfter)
	{
		// Make sure our environment is sane
		if (lineRef && lineNew)
		{
			// Indicate success or failure
			return(iLl_insert__ll((SLL*)lineNew, (SLL*)lineRef, tlAfter));
		}

		// Failure
		return(false);
	}




//////////
//
// Called to append an error the indicated source code line
//
//////
	void iLine_appendError(SLine* line, u32 tnErrorNum, cu8* tcMessage, u32 tnStartColumn, u32 tnLength)
	{
#ifdef _SHOW_REFACTOR_ERRORS
		if (line && line->compilerInfo)
			iNoteLog_create(&line->compilerInfo->firstInquiry, line, tnStartColumn, tnStartColumn + tnLength, tnErrorNum, tcMessage);
#endif
	}




//////////
//
// Called to append a warning to the indicated source code line
//
//////
	void iLine_appendWarning(SLine* line, u32 tnWarningNum, cu8* tcMessage, u32 tnStartColumn, u32 tnLength)
	{
#ifdef _SHOW_REFACTOR_ERRORS
		if (line && line->compilerInfo)
			iNoteLog_create(&line->compilerInfo->firstInquiry, line, tnStartColumn, tnStartColumn + tnLength, tnWarningNum, tcMessage);
#endif
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
#ifdef _SHOW_REFACTOR_ERRORS
							if (!cb->line->ll.nextLine || !cb->line->ll.nextLine->compilerInfo)
								break;	// We've reached the end
#endif

							// Next line
							cb->line = cb->line->ll.nextLine;
#ifdef _SHOW_REFACTOR_ERRORS
							cb->comp = cb->line->compilerInfo->firstComp;
#endif

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
#ifdef _SHOW_REFACTOR_ERRORS
			if (line->compilerInfo && line->compilerInfo->firstComp)
				lnUnescapeCount += iComps_unescape_iCodes(line->compilerInfo->firstComp, tniCode1, tniCode2, tniCode3);
#endif
		}

		// Indicate how many were unescaped
		return(lnUnescapeCount);
	}




//////////
//
// Moves all lines from one file to another, after the target line
//
//////
	s32 iLine_migrateLines(SLine** linesFrom, SLine* lineTarget)
	{
		s32		lnLineCount;
		SLine*	lineAfter;
		SLine*	line;
		SLine*	lineFrom;


		// Make sure our environment is sane
		lnLineCount	= 0;
		if (linesFrom && (lineFrom = *linesFrom) && lineTarget)
		{

			//////////
			// Point lineTarget to the start of the linesFrom block
			//////
				lineAfter					= lineTarget->ll.nextLine;
				lineTarget->ll.nextLine		= lineFrom;
				lineFrom->ll.prevLine		= lineTarget;


			//////////
			// Point the last line of the *linesFrom chain to the temp
			//////
				for (line = lineFrom, lnLineCount = 1; line->ll.nextLine; line = line->ll.nextLine)
					++lnLineCount;

				// Update the 
				line->ll.nextLine = lineAfter;				// Last line points to the original line after where we inserted
				if (lineAfter)
					lineAfter->ll.prevLine	= line;			// The original line after where we inserted points back to the new line

		}

		// Indicate our count
		return(lnLineCount);
	}




//////////
//
// Called to obtain the Nth parameter from the start of the line, or from a line that follows if allowed
//
//////
	SComp* iLine_Nth_comp(SLine* line, s32 tnCount, bool tlMoveBeyondLineIfNeeded)
	{
		// Make sure our environment is sane
		if (line)
		{
#ifdef _SHOW_REFACTOR_ERRORS
			// Locate the line that has compiler info
			if (tlMoveBeyondLineIfNeeded)
			{
				// Iterate until we find a line with a first component
				for ( ; line && (!line->compilerInfo || !line->compilerInfo->firstComp); )
					line = line->ll.nextLine;
			}

			// If we're on a line with compiler info and a first comp, locate it
			if (line->compilerInfo && line->compilerInfo->firstComp)
				return(iComps_Nth(line->compilerInfo->firstComp, tnCount, tlMoveBeyondLineIfNeeded));
#endif
		}

		// If we get here, failure
		return(NULL);
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

	SLine* iLine_duplicate_withComps(SLine* line, bool tlCopyNotes, bool tlCopyExtraInfo)
	{
		SComp*			comp;
		SComp*			compNew;
		SLine*			lineDup;


		// Make sure our environment is sane
		lineDup = NULL;
		if (line)
		{
			// Iterate through each comp
			lineDup = iLine_createNew();
			if (lineDup)
			{

				//////////
				// Copy generally
				//////
					lineDup->file				= line->file;
					lineDup->func				= line->func;
					lineDup->data				= line->data;
					lineDup->parent				= line->parent;
					lineDup->lineNumber			= line->lineNumber;
					lineDup->lineSubnumber		= line->lineSubnumber;
					lineDup->lineStatus			= line->lineStatus;

					// Copy source code
					iDatum_duplicate(&lineDup->sourceCode,			&line->sourceCode);
					iDatum_duplicate(&lineDup->sourceCodeOriginal,	&line->sourceCode);
					lineDup->populatedLength	= line->populatedLength;


				//////////
				// Copy components
				//////
					for (comp = line->firstComp; comp; comp = comp->ll.nextComp)
					{
						// Duplicate
						compNew = iComps_duplicate(comp);

						// Append to the new line
						iLl_appendExisting__llAtEnd((SLL**)&lineDup->firstComp, (SLL*)compNew);
					}


				//////////
				// Copy notes
				//////
					if (tlCopyNotes)
						iNoteLog_duplicateChain(&lineDup->firstNote, line->firstNote);


				//////////
				// Copy extra_info
				//////
					if (tlCopyExtraInfo)
						iExtraInfo_duplicateChain(&lineDup->extra_info, line->extra_info);

			}
		}

		// Indicate our status
		return(lineDup);
	}

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
				if (!(lineNew = iLine_createNew()))
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
					if (!tlSkipBlankLines || lineCopy->firstComp->iCode != _ICODE_BACKSLASH)
					{
						// New line
						lineNew = iLine_appendNew(lineNew);

						// Copy all line components up to the end
						iComps_copyTo_withCallback(lineNew, lineCopy->firstComp, cb, false);
					}
				}


		} else {
			// Invalid content, just create a blank line
			lineNew = iLine_createNew();
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
#ifdef _SHOW_REFACTOR_ERRORS
					if (line->compilerInfo && line->compilerInfo->firstComp)
					{
						// Set the component
						*compProcessing = line->compilerInfo->firstComp;

						// Indicate how far we traversed
						return(lnCount);
					}
#endif


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
#ifdef _SHOW_REFACTOR_ERRORS
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
#endif


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
// Called to get the first or last component on the line
//
//////
	SComp* iiLine_getLastComp(SLine* line, SComp* compInLine)
	{
		// Scan forward to the end
		for (compInLine = ((compInLine) ? compInLine : line->firstComp); compInLine->ll.nextComp && compInLine->ll.nextComp->line == line; )
			compInLine = compInLine->ll.nextComp;

		// Indicate our status
		return(compInLine);
	}




//////////
//
// Renumber forward beginning at the indicated number.
// Returns the next line number.
//
//////
	s32 iLine_renumber(SLine* firstLine, s32 tnStartingNumber)
	{
		s32		lnLine;
		SLine*	line;


		// Iterate forward
		for (line = firstLine, lnLine = tnStartingNumber; line; line = line->ll.nextLine, lnLine++)
			line->lineNumber = lnLine;

		// Indicate the next line
		return(lnLine);
	}

	f32 iLine_renumber2(SLine* firstLine, f32 tfStartingNumber)
	{
		f32		lfLine;
		SLine*	line;


		// Iterate forward
		for (line = firstLine, lfLine = tfStartingNumber; line; line = line->ll.nextLine, lfLine++)
			line->lineSubnumber = lfLine;

		// Indicate the next line
		return(lfLine);
	}




//////////
//
// Reconstitute the source code on the line based on the components
//
//////
	SDatum* iLine_reconstitute_byComps(SLine* line)
	{
		s32		lnLength, lnWhitespaces, lnEndLast;
		SComp*	comp;
		SComp*	compLast;


		// Make sure our environment is sane
// TODO:  Untested code.  Breakpoint and examine.
debug_break;
		if (line)
		{

			//////////
			// Find out how long the line needs to be
			//////
				for (comp = line->firstComp, compLast = NULL, lnLength = 0; comp; compLast = comp, comp = iComps_Nth_lineOnly(comp))
				{
					// Whitespaces
					if (comp->start >= 0 && compLast && compLast->text._data)
						lnLength += comp->start - (compLast->start + compLast->text.length);

					// Content
					if (comp->text._data)
						lnLength += comp->text.length;
				}


			//////////
			// Create the line
			//////
				if (line->sourceCode._data)
					iDatum_delete(&line->sourceCode, false);

				// Allocate space for the copy
				iDatum_allocateSpace(&line->sourceCode, lnLength, 32);


			//////////
			// Populate the component content
			//////
				for (comp = line->firstComp, lnEndLast = 0, lnLength = 0; comp; comp = iComps_Nth_lineOnly(comp))
				{
					// Whitespaces
					if (comp->start >= 0 && lnEndLast != 0)
					{
						// Physical space between
						lnWhitespaces = comp->start - lnEndLast;

					} else {
						// No whitespaces
						lnWhitespaces = 0;
					}

					// Copy content
					if (comp->text._data)
						memcpy(line->sourceCode.data_s8 + lnLength + lnWhitespaces, comp->text.data_s8, comp->text.length);

					// Indicate where the previous one ended
					lnEndLast = lnLength + lnWhitespaces + comp->text.length;

					// Update the component
					comp->start = lnLength;

					// Update the length
					lnLength += (lnWhitespaces + comp->text.length);
				}

		}
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
	SComp* iLine_lex(SAsciiCompSearcher* tacs, SLine* line)
	{
		s32						lnI, lnMaxLength, lnStart, lnLength, lnLacsLength, lnSearchLen;
		SComp*					compFirst;
		SComp*					compLast;
		SComp*					comp;
		u8*						lcData;
		cu8*					lcSearchPtr;
		SAsciiCompSearcher*		lacs;


		// Make sure the environment's sane
		compFirst = NULL;
		if (tacs && line)
		{
			// Scan starting at the beginning of the line
			lcData = line->sourceCode.data_u8;

			// Iterate through every byte identifying every component we can
			compLast	= line->firstComp;
			lnMaxLength	= line->populatedLength;
			for (lnI = 0; lnI < lnMaxLength; )
			{
				// Search through the tsComps list one by one
				for (	lacs = tacs;
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
								// Are we searching for a literal repeat of the entire string, or something alternate
								if (lacs->repeats == 1)
								{
									// Entire string
									lcSearchPtr = lacs->keyword_cu8;
									lnSearchLen = lacs->length;

								} else {
									// Something alternate
									lcSearchPtr = lacs->partialRepeatContent;
									lnSearchLen = strlen((cs8*)lcSearchPtr);
								}

								// Iterate forward looking for the repeating sequence(s)
								while (lnStart + lnLength + lnLacsLength <= lnMaxLength && iComps_xlatToComps_withTest(lcSearchPtr, lcData + lnStart + lnLength, lnSearchLen) == 0)
								{
									// We found another repeated entry
									lnLength += lnSearchLen;
								}
								// When we get here, every repeated entry has been found (if any)
							}
							// When we get here, we have the starting point and the full length (including any repeats)


							//////////
							// Allocate this entry
							///////
								comp = iComps_new(&line->firstComp, compLast, NULL, compLast);


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

										// Copy the text for the component to the text SDatum
										iDatum_duplicate(&comp->text, (cvp*)(line->sourceCode.data_s8 + lnStart), lnLength);

										// Update the component's information
										comp->line			= line;
										comp->start			= lnStart;
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
// Called to insert a character
//
//////
	bool iLine_characterInsert(SEM* sem, u8 asciiChar)
	{
		s32			lnI;
		SLine*		line;


		// Make sure our environment is sane
		if (sem && !sem->isReadOnly && sem->line_cursor)
		{
			// Make sure there's room enough for the keystroke
			line = sem->line_cursor;
			if (iLine_ensureLineLength(sem, sem->line_cursor->populatedLength + 1))
			{
				// They could've been beyond the end of line, and if so then we need to insert spaces between the end and here
				if (sem->columnEdit > line->populatedLength)
				{
					// Fill with spaces
					for (lnI = line->populatedLength; lnI < sem->columnEdit; lnI++)
						line->sourceCode.data_s8[lnI] = ' ';
				}

				// Move everything from the end of the line to where we are right one character
				for (lnI = line->populatedLength + 1; lnI > sem->columnEdit && lnI > 0; lnI--)
					line->sourceCode.data_s8[lnI] = line->sourceCode.data_s8[lnI - 1];

				// Insert the character
				line->sourceCode.data_s8[sem->columnEdit] = asciiChar;

				// Move to the next column
				++sem->columnEdit;

				// Increase the populated length
				++line->populatedLength;

				// If we're past the end, we need to indicate our populated line length
				if (sem->columnEdit > line->populatedLength)
					line->populatedLength = sem->columnEdit;

				// Indicate success
				return(true);
			}
		}

		// If we get here, we could not insert it
		return(false);
	}




//////////
//
// Called to overwrite the existing character wherever we are
//
//////
	bool iLine_characterOverwrite(SEM* sem, u8 asciiChar)
	{
		s32			lnI;
		SLine*		line;


		// Make sure our environment is sane
		if (sem && !sem->isReadOnly && sem->line_cursor)
		{
			// Is there room to inject it?
			line = sem->line_cursor;
			if (iLine_ensureLineLength(sem, sem->line_cursor->populatedLength + 1))
			{
				if (sem->columnEdit > line->populatedLength)
				{
					// We need to insert it because we're at the end of the populated length
					return(iLine_characterInsert(sem, asciiChar));

				} else {
					// We can overwrite it

					// They could've been beyond the end of line, and if so then we need to insert spaces between the end and here
					if (sem->columnEdit > line->populatedLength)
					{
						// Fill with spaces
						for (lnI = line->populatedLength; lnI < sem->columnEdit; lnI++)
							line->sourceCode.data_s8[lnI] = ' ';
					}

					// Overwrite the character
					line->sourceCode.data_s8[sem->columnEdit] = asciiChar;

					// Move to the next column
					++sem->columnEdit;

					// If we're past the end, we need to indicate our populated line length
					if (sem->columnEdit > line->populatedLength)
						line->populatedLength = sem->columnEdit;

					// Indicate success
					return(true);
				}
			}
		}

		// If we get here, we could not overwrite
		return(false);
	}




//////////
//
// Called to delete the character where we are, which, depending on insert mode,
// will affect the line in different ways.
//
//////
	bool iLine_characterDelete(SEM* sem)
	{
		s32		lnI;
		SLine*	line;


		// Make sure our environment is sane
		if (sem && !sem->isReadOnly && sem->line_cursor)
		{
			// Grab the line
			line = sem->line_cursor;

			// If we're in the populated area
			if (sem->columnEdit < line->populatedLength)
			{
				// Move everything left one character
				for (lnI = sem->columnEdit; lnI < line->populatedLength; lnI++)
					line->sourceCode.data_s8[lnI] = line->sourceCode.data_s8[lnI + 1];

				// Reduce the length of the populated portion of the line by one
				--line->populatedLength;

				// Put a space there
				line->sourceCode.data_s8[line->populatedLength] = 32;

				// Indicate success
				return(true);
			}
		}

		// If we get here, we could not overwrite
		return(false);
	}




//////////
//
// Called to toggle the breakpoint on the current line
//
//////
	SBreakpoint* iLine_toggleBreakpoint(SEM* sem)
	{
		SBreakpoint* bp;


		// Make sure our environment is sane
		if (sem && sem->line_cursor)
		{
			// Grab the line
			if (iBreakpoint_exists(sem->line_cursor->extra_info))
			{
				// Delete the existing breakpoint
				iBreakpoint_delete(&sem->line_cursor->extra_info);
				bp = NULL;

			} else {
				// Adding a new always-stop breakpoint
				bp = iBreakpoint_add(&sem->line_cursor->extra_info, _BREAKPOINT_ALWAYS);
			}

			// Indicate our status
			return(bp);
		}

		// If we get here, invalid
		return(NULL);
	}




//////////
//
// Called to see if a line has changed
//
//////
	bool iLine_hasChanged(SLine* ec)
	{
		// Make sure our environment is sane
		if (ec)
		{
			// Test lengths
			if (ec->populatedLength != ec->sourceCodeOriginal.length)
				return(true);		// They are different lengths

			// Test content
			if (memcmp(ec->sourceCode.data_s8, ec->sourceCodeOriginal.data_s8, ec->populatedLength) != 0)
				return(true);		// The content is different
		}
		// If we get here, not changed
		return(false);
	}
