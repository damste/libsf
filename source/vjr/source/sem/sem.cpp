//////////
//
// /libsf/source/vjr/source/sem/sem.cpp
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
// Copyright (c) 2014-2017 by Rick C. Hodgin
//////
// Last update:
//     Jul.06.2014
//////
// Change log:
//     Mar.15.2015 - GitHub:4 -- Delete all does not clear the last line
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
// Called to create a new EM (Edit Manager)
//
//////
	SEM* iSEM_allocate(bool tlIsSourceCode)
	{
		SEM* sem;


		logfunc(__FUNCTION__);
		// Allocate a new structure
		sem = (SEM*)malloc(sizeof(SEM));

		// Initialize
		if (sem)
		{
			// Reset all
			memset(sem, 0, sizeof(SEM));

			// Store defaults
			sem->isSourceCode				= tlIsSourceCode;
			sem->allowMoveBeyondEndOfLine	= true;
			if (tlIsSourceCode)
				sem->showLineNumbers		= true;

			// Default to 4-character tab width
			sem->tabWidth					= 4;
			sem->areTabsEnforced			= true;

			// Default to 5% and 15% nbsp color influences
			sem->minNbspColorInfluence		= 0.05f;
			sem->maxNbspColorInfluence		= 0.15f;

			// Default colors for changed and new
			sem->newColor.color				= editNewColor.color;
			sem->changedColor.color			= editChangedColor.color;
		}

		// Indicate our status
		return(sem);
	}




//////////
//
// Called to accumulate the indicated line range into a builder buffer.
//
//////
	SBuilder* iSEM_accumulateBuilder(SEM* sem, SLine* ecHintStart, SLine* ecHintEnd)
	{
		SBuilder*	b;
		SLine*		line;


		logfunc(__FUNCTION__);
		// Make sure our environment is sane
		b = NULL;
		if (sem)
		{
			//////////
			// Create our builder
			//////
				iBuilder_createAndInitialize(&b, -1);


			//////////
			// Make sure the parameters are set.  They can pass the start or end if
			// they only want a partial file.
			//////
				if (!ecHintStart)		ecHintStart = sem->firstLine;
				if (!ecHintEnd)			ecHintEnd	= sem->lastLine;


			//////////
			// Repeat until we're at the end
			//////
				if (ecHintStart && ecHintEnd)
				{
					//////////
					// Build repeatedly
					//////
						line = ecHintStart;
						while (line)
						{
							//////////
							// If populated, append its content
							//////
								if (line->sourceCode && line->sourceCode_populatedLength > 0)
									iBuilder_appendData(b, line->sourceCode->data_u8, line->sourceCode_populatedLength);


							//////////
							// Append a carriage return + line feed
							//////
								iBuilder_appendCrLf(b);


							//////////
							// Was this the last line?
							//////
								if (line == ecHintEnd)
									break;		// Yes, sir, it was


							//////////
							// Move to next line
							//////
								line = (SLine*)line->ll.next;
						}
						// When we get here, the block is copied out
				}
		}

		// Indicate our status
		return(b);
	}




//////////
//
// Called to save the indicated EM to disk.  Saved as a raw text file.
//
//////
	bool iSEM_saveToDisk(SEM* sem, cs8* tcPathname)
	{
		return(iSEM_saveToDisk(sem, (cu8*)tcPathname));
	}
	bool iSEM_saveToDisk(SEM* sem, cu8* tcPathname)
	{
		SBuilder* content;


		logfunc(__FUNCTION__);
		// Make sure our environment is sane
		if (sem && tcPathname)
		{
			// Grab the content
			content = iSEM_accumulateBuilder(sem, NULL, NULL);
			if (content)
			{
				// Write it out
				iBuilder_asciiWriteOutFile(content, tcPathname, false);

				// Release it
				iBuilder_freeAndRelease(&content);

				// Indicate success
				return(true);
			}
		}
		// If we get here, failure
		return(false);
	}




//////////
//
// Loads in a text file into an EM beginning optionally near ecHint.
//
//////
	bool iSEM_load_fromDisk(SObject* objParent, SEM* sem, cs8* tcPathname, bool isSourceCode, bool tlLogIt, SAsciiCompSearcher* acsSecondary)
	{
		return(iSEM_load_fromDisk(objParent, sem, (cu8*)tcPathname, isSourceCode, tlLogIt, acsSecondary));
	}
	bool iSEM_load_fromDisk(SObject* objParent, SEM* sem, cu8* tcPathname, bool isSourceCode, bool tlLogIt, SAsciiCompSearcher* acsSecondary)
	{
		s32			lnPathnameLength, lnFnameLength;
		bool		llResult;
		SBuilder*	content;
		SDatum		datum;
		s8*			lcFname;
		u8			buffer[_MAX_PATH + 64];


		logfunc(__FUNCTION__);
		// Make sure our environment is sane
		if (sem && tcPathname && (lnPathnameLength = (s32)strlen((s8*)tcPathname)) < (s32)sizeof(sem->fileName) - 1 && lnPathnameLength > 0)
		{
			// Store the last loaded filename
			memset(sem->fileName, 0, sizeof(sem->fileName));
			memcpy(sem->fileName, tcPathname, lnPathnameLength);

			// Update the name on the riderTab (if need be)
			if (objParent)
			{
				// Try to extract just the pathname
				if (iFile_get_justfname((s8*)tcPathname, lnPathnameLength, &lcFname, &lnFnameLength))
				{
					// Set it to the extracted portion
					propSetRiderTab(objParent, lcFname, lnFnameLength);

				} else {
					// Fall back on "rider" text
					propSetRiderTab(objParent, cgcName_rider, sizeof(cgcName_rider) - 1);
				}
			}

			// Read it in
			content = NULL;
			if (iBuilder_asciiReadFromFile(&content, tcPathname))
			{
				// Load it
				datum.data_s8	= content->data_s8;
				datum.length	= content->populatedLength;
				llResult		= iSEM_load_fromMemory(objParent, sem, &datum, isSourceCode, false, acsSecondary);

				// Clean house
				iBuilder_freeAndRelease(&content);

				// Log if need be
				if (tlLogIt)
				{
					// Log it
					sprintf((s8*)buffer, "Load %s\0", tcPathname);
					iVjr_appendSystemLog(buffer);
				}

				// Indicate our result
				return(llResult);

			} else if (tlLogIt) {
				// Log it
				sprintf((s8*)buffer, "Load inquiry %s\0", tcPathname);
				iVjr_appendSystemLog(buffer);
			}
		}
		// If we get here, failure
		return(false);
	}




//////////
//
// Called to load a SEM from a memory block (a raw block of data)
//
//////
	bool iSEM_load_fromMemory(SObject* objParent, SEM* sem, SDatum* datum, bool isSourceCode, bool tlLogIt, SAsciiCompSearcher* acsSecondary)
	{
		s32			lnI, lnJ, lnLast;
		bool		llOtherCharacters;
		SLine*		start;
		SLine*		end;
		u8			buffer[64];


		//////////
		// Iterate through breaking out the content
		//////
			start				= NULL;
			end					= NULL;
			llOtherCharacters	= false;
			for (lnI = 0, lnLast = 0; lnI <= datum->length; )
			{
				// Are we on a CR/LF combination?
				for (lnJ = 0; lnI < datum->length && (datum->data_u8[lnI] == 13 || datum->data_u8[lnI] == 10) && lnJ < 2; lnJ++)
					++lnI;	// Increase also past this CR/LF character

				// If we found a CR/LF combination
				if (lnJ != 0 || lnI >= datum->length)
				{
					// We've entered into a CR/LF block, append a new line
					if (!llOtherCharacters)
					{
						// We only had CR+LF characters, no data
						end = iSEM_appendLine(sem, datum->data_u8 + lnLast, 0, false);

					} else {
						// We had at least some data
						end = iSEM_appendLine(sem, datum->data_u8 + lnLast, lnI - lnJ - lnLast, false);
					}
					if (!start)
						start = end;

					// Indicate where we are now
					llOtherCharacters	= false;
					lnLast				= lnI;

					// If we're done, then we're done
					if (lnI == datum->length)
						++lnI;

				} else {
					llOtherCharacters = true;
					++lnI;
				}
				// Continue on processing the next line if we have room
			}


		//////////
		// Renumber everything
		//////
			iSEM_renumber(sem, 1);


		//////////
		// Parse the content if it's flagged as source code
		//////
			if (isSourceCode)
			{
				// Parse from start to end
				for ( ; start && start->ll.prevLine != end; start = start->ll.nextLine)
					iEngine_parse_sourceCode_line(start, acsSecondary);
			}


		//////////
		// Log if need be
		//////
			if (tlLogIt)
			{
				// Log it
				sprintf((s8*)buffer, "Loaded %d from memory\0", datum->length);
				iVjr_appendSystemLog(buffer);
			}


		//////////
		// Indicate success
		//////
			return(true);

	}




//////////
//
// Duplicate the entire SEM
//
//////
	bool iSEM_duplicate(SEM** root, SEM* semSource, bool tlIncludeUndoHistory)
	{
// 		SEM*	ecmNew;
// 		SEditChain*			ecSource;
// 		SEditChain*			ecNew;
// 		SEditChain*			ecLast;
// 		SEditChain**		ecPrev;
// 		SExtraInfo*			eiSource;
// 		SExtraInfo*			eiNew;
// 		SExtraInfo**		eiPrev;
// 		SBuilder*			xlatRoot;
// 		STranslate*			xlat;


		// Create the master record
// TODO:  COMPLETELY UNTESTED.  BREAKPOINT AND EXAMINE.
debug_break;
// 		ecmNew = (SEM*)malloc(sizeof(SEM));
// 		if (ecmNew)
// 		{
// 			//////////
// 			// Initialize
// 			//////
// 				memcpy(ecmNew, ecmSource, sizeof(SEM));
//
//
// 			//////////
// 			// Remove the connection to any undo history
// 			// Note:  The undo history will be copied and translated separately if need be
// 			//////
// 				ecmNew->undoHistory = NULL;
// 				iBuilder_createAndInitialize(&xlatRoot, -1);
// 				// Note:  We create the translation regardless so we can update the ecmNew-> members which relate to cursor line, highlighted, etc.
//
//
// 			//////////
// 			// Update caller
// 			//////
// 				*root = ecmNew;
// 				// Right now:
// 				//		ecmNew		-- our new SEC
// 				//		ecmSource	-- SEC to duplicate
//
//
// 			//////////
// 			// Indicate where we'll be updating
// 			//////
// 				ecPrev	= &ecmNew->ecFirst;
// 				ecLast	= NULL;
//
//
// 			//////////
// 			// Duplicate the chain
// 			//////
// 				ecSource = ecmSource->ecFirst;
// 				while (ecSource)
// 				{
// 					//////////
// 					// Create a new entry for this one
// 					//////
// 						ecNew = (SEditChain*)malloc(sizeof(SEditChain));
// 						if (ecNew)
// 						{
// 							// Create a translation for original pointers to new pointers
// 							if (tlIncludeUndoHistory)
// 							{
// 								// Create the translation for this ecSource <--> ecNew
// 								xlat = (STranslate*)iBuilder_allocateBytes(xlatRoot, sizeof(STranslate));
// 								if (xlat)
// 								{
// 									// Create the translation
// 									xlat->p1	= ecSource;									// The old pointer in the undoHistory will point to
// 									xlat->p2	= ecNew;									// the new pointer
// 								}
// 							}
//
// 						} else {
// 							// Should not happen.
// 							return(false);
// 						}
//
//
// 					//////////
// 					// Copy source information to new
// 					//////
// 						memcpy(ecNew, ecSource, sizeof(SEditChain));
// 						*ecPrev		= ecNew;												// Update the prior record to point here
// 						ecNew->prev	= ecLast;												// Point backward to the previous entry
// 						ecNew->next	= NULL;													// Currently points forward to nothing
//
//
// 					//////////
// 					// Duplicate its data
// 					//////
// 						ecNew->sourceCode = NULL;
// 						iDatum_duplicate(ecNew->sourceCode, ecSource->sourceCode);
//
//
// 					//////////
// 					// General purpose extra data
// 					//////
// 						if (ecSource->extra_info)
// 						{
// 							// Copy any extra_info that's relevant
// 							eiPrev		= &ecNew->extra_info;
// 							eiSource	= ecSource->extra_info;
// 							while (eiSource)
// 							{
// 								//////////
// 								// Duplicate this entry
// 								//////
// 									// Are we duplicating by a function call?  Or manually?
// 									if (*(u32*)&eiSource->extra_info_duplicate != 0)
// 									{
// 										// Function call
// 										eiNew = eiSource->extra_info_duplicate(ecmSource, ecSource, ecSource->extra_info);
// 										// Right now, eiNew has either been updated or not depending on the decision making process in extra_info_duplicate().
//
// 									} else {
// 										// Manual duplication
// 										eiNew = (SExtraInfo*)malloc(sizeof(SExtraInfo));
// 										if (eiNew)
// 										{
// 											// Copy everything
// 											memcpy(eiNew, eiSource, sizeof(SExtraInfo));
//
// 											// Clear, and then duplicate the info datum
// 											memset(&eiNew->info, 0, sizeof(eiNew->info));
// 											iDatum_duplicate(&eiNew->info, &eiSource->info);
//
// 										} else {
// 											// Should not happen
// 											return(false);
// 										}
// 									}
//
//
// 								//////////
// 								// Update the back-link if need be
// 								//////
// 									if (eiNew)
// 									{
// 										*eiPrev	= eiNew;
// 										eiPrev	= &eiNew->next;
// 									}
//
//
// 								//////////
// 								// Move to next extra_info
// 								//////
// 									eiSource = eiSource->next;
// 							}
// 						}
//
//
// 					//////////
// 					// Move to next entry to duplicate
// 					//////
// 						ecLast		= ecNew;
// 						ecPrev		= &ecNew->next;
// 						ecSource	= ecSource->next;
// 				}
//
//
// 			//////////
// 			// Translate each of the ecmSource pointers for ecmNew
// 			// Note:  The rest of them use uid lookups
// 			//////
// 				ecmNew->ecFirst				= (SEditChain*)iTranslate_p1_to_p2(xlatRoot, ecmSource->ecFirst);
// 				ecmNew->ecLast				= (SEditChain*)iTranslate_p1_to_p2(xlatRoot, ecmSource->ecLast);
// 				ecmNew->ecTopLine				= (SEditChain*)iTranslate_p1_to_p2(xlatRoot, ecmSource->ecTopLine);
// 				ecmNew->ecCursorLine		= (SEditChain*)iTranslate_p1_to_p2(xlatRoot, ecmSource->ecCursorLine);
// 				ecmNew->ecCursorLineLast	= (SEditChain*)iTranslate_p1_to_p2(xlatRoot, ecmSource->ecCursorLineLast);
// 				ecmNew->ecSelectedLineStart	= (SEditChain*)iTranslate_p1_to_p2(xlatRoot, ecmSource->ecSelectedLineStart);
// 				ecmNew->ecSelectedLineEnd	= (SEditChain*)iTranslate_p1_to_p2(xlatRoot, ecmSource->ecSelectedLineEnd);
//
//
// 			//////////
// 			// Free the pointers
// 			//////
// 				iBuilder_freeAndRelease(&xlatRoot);
//
//
// 			//////////
// 			// Indicate success
// 			//////
// 				return(true);
// 		}

		// If we get here, failure
		return(false);
	}




//////////
//
// Called to duplicate the SEM as a reference (points to the original one)
//
//////
	SEM* iSEM_duplicate_asReference(SEM* sem)
	{
		SEM* semNew;


		logfunc(__FUNCTION__);
		// Make sure our environment is sane
		semNew = NULL;
		if (sem)
		{
			// Create our copy
			semNew = iSEM_allocate(sem->isSourceCode);

			// Indicate this is a reference to the original one
			if (semNew)
				semNew->indirect = sem;
		}

		// Signal our result
		return(semNew);
	}




//////////
//
// Called to free the EM content, and optionally itself
//
//////
	void iSEM_delete(SEM** root, bool tlDeleteSelf)
	{
		SEM* sem;


		logfunc(__FUNCTION__);
		// Make sure our environment is sane
		if (root && *root)
		{
			sem = *root;
			//////////
			// Are we really the thing?  Or just an indirect reference to the thing?
			//////
				if (!sem->indirect)
				{
					//////////
					// We are the thing
					// Free undo history
					//////
						if (sem->undoHistory)
							iSEM_delete(&sem->undoHistory, true);


					//////////
					// Free content
					//////
						iSEMLine_free(&sem->firstLine, true);
				}


			//////////
			// Free self
			//////
				if (tlDeleteSelf)
				{
					free(sem);
					*root = NULL;
				}
		}
	}




//////////
//
// Called to delete the entire chain explicitly
//
//////
	void iSEM_deleteChain(SEM** root, bool tlDeleteSelf)
	{
		logfunc(__FUNCTION__);

		// Delete, but with no callback
		iSEM_deleteChainWithCallback(root, tlDeleteSelf, NULL);
	}

	void iSEM_deleteChainWithCallback(SEM** root, bool tlDeleteSelf, SEM_callback* ecb)
	{
		bool			llDeleteThisLine;
		SLL*			nodeNext;
		SEM_callback	lecb;


		logfunc(__FUNCTION__);
		// Make sure our environment is sane
		if (root && *root)
		{
			//////////
			// If we don't have an ecb, make a local one
			//////
				if (!ecb)
				{
					// Initialize and setup the pointer
					memset(&lecb, 0, sizeof(lecb));
					ecb = &lecb;
				}


			//////////
			// Delete from the beginning
			//////
				ecb->sem		= *root;
				ecb->line		= ecb->sem->firstLine;


			// Iterate through deleting each entry after turning off the display
			llDeleteThisLine			= true;
			ecb->sem->isHeavyProcessing	= true;
			while (ecb->line)
			{
				//////////
				// Grab the next node
				//////
					nodeNext = ecb->line->ll.next;


				//////////
				// Perform the callback
				//////
					if (ecb && ecb->_callback)
						llDeleteThisLine = ecb->callback(ecb);


				//////////
				// Delete the node itself if we're supposed to
				//////
					ecb->sem->line_cursor = ecb->line;
					if (llDeleteThisLine)
						iSEM_deleteLine(ecb->sem);


				//////////
				// Move to next node
				//////
					ecb->line = (SLine*)nodeNext;
			}
		}
	}




//////////
//
// Renumber the source code lines
//
//////
	u32 iSEM_renumber(SEM* sem, u32 tnStartingLineNumber)
	{
		SLine* line;


		logfunc(__FUNCTION__);
		// Make sure our environment is sane
		if (sem && sem->firstLine && sem->lastLine)
		{
			// Begin at the beginning
			line = sem->firstLine;
			while (line)
			{
				//////////
				// Set the line number
				//////
					line->lineNumber = tnStartingLineNumber++;


				//////////
				// See if this line is one of the selected lines
				//////
					if (sem->selectMode != _SEM_SELECT_MODE_NONE)
					{
						// Update origin
						if (line->uid == sem->selectOrigin.uid)
						{
							sem->selectOrigin.lineNumber = line->lineNumber;
							sem->selectOrigin.line		= line;
						}

						// Update end
						if (line->uid == sem->selectEnd.uid)
						{
							sem->selectEnd.lineNumber	= line->lineNumber;
							sem->selectOrigin.line		= line;
						}
					}


				//////////
				// Are we done
				//////
					if (line == sem->lastLine)
						break;


				//////////
				// Move to next line
				//////
					line = (SLine*)line->ll.next;
			}

			// Indicate the new ending line number
			return(tnStartingLineNumber - 1);
		}

		// If we get here, no processing
		return(-1);
	}




//////////
//
// Called to append a line of text to the indicated SEM.
//
//////
	SLine* iSEM_appendLine(SEM* sem, SLine* line, bool tlSetNewLineFlag)
	{
		return(iSEM_appendLine(sem, line->sourceCode->data_u8, line->sourceCode_populatedLength, tlSetNewLineFlag));
	}

	SLine* iSEM_appendLine(SEM* sem, u8* tcText, s32 tnTextLength, bool tlSetNewLineFlag)
	{
		s32		lnI, lnJ, lnPass, lnTextLength, lnCount;
		SLine*	line;


// Not logged because this function is called by the logging function. :-)
//		logfunc(__FUNCTION__);
		// Make sure our environment is sane
		// Note:  We do not test for tcText and tnTextLength because we can add blank lines
		line = NULL;
		if (sem && !sem->isReadOnly)
		{
			// Allocate our new structure
			if (sem->lastLine)
			{
				// Append after the last line
				if (sem == screenData && sem->lastLine == sem->firstLine && sem->line_cursor->sourceCode_populatedLength == 0)
				{
					// A special case for the command window, where the top line persists after a CLEAR, and must be populated before continuing
					// So, we don't do anything here ... just leave re-use the existing line
					line = sem->line_cursor;

				} else {
					line = (SLine*)iLl_appendNew__llAtEnd((SLL**)&sem->lastLine, sizeof(SLine));
				}

			} else {
				// This is the first line, add it and set the last line to the same
				line = (SLine*)iLl_appendNew__llAtEnd((SLL**)&sem->firstLine, sizeof(SLine));
				if (line)
				{
					// Update defaults
					sem->line_cursor			= line;
					sem->line_cursorLast		= line;
					sem->line_top				= line;
				}
			}

			// Update and populate if added
			if (line)
			{
				// We've added it to the end
				sem->lastLine = line;

				// Make sure the length is valid
				if (tnTextLength == -1)
				{
					if (tcText)		tnTextLength = (s32)strlen(tcText);
					else			tnTextLength = 0;
				}

				// Run two passes over the line.
				// Pass 1 -- Determine how long the line should be with tabs expanded to spaces
				// Pass 2 -- Populate the source into the destination padding tabs with spaces
				for (lnPass = 0; lnPass < 2; lnPass++)
				{
					// Determine how long the text is (expanding tabs)
					for (lnI = 0, lnTextLength = 0; lnI < tnTextLength; lnI++)
					{
						// If it's a tab, expand up to the nearest tabWidth characters
						if (tcText[lnI] == 9)
						{
							// Expand up to the next tabstop
							if (lnTextLength % sem->tabWidth == 0)	lnCount = sem->tabWidth;
							else									lnCount = sem->tabWidth - (lnTextLength % sem->tabWidth);

							// Copy if on pass 1
							if (lnPass == 1)
							{
								// Expand the difference with spaces
								for (lnJ = 0; lnJ < lnCount; lnJ++)
									line->sourceCode->data_s8[lnTextLength + lnJ] = 32;		// Fill with spaces
							}

							// Skip past our added space
							lnTextLength += lnCount;

						} else {
							// Copy one character on pass 1
							if (lnPass == 1)
								line->sourceCode->data_s8[lnTextLength] = tcText[lnI];

							// Increase by one
							++lnTextLength;
						}
					}

					// If we're on pass 0, allocate space, on the second pass we copy
					if (lnPass == 0)
					{
						// Allocate the datum
						line->sourceCode = iDatum_allocate((u8*)NULL, 0);

						// Allocate space for the copy if there's any data
						if (lnTextLength != 0)
							iDatum_allocateSpace(line->sourceCode, lnTextLength);

						// Set the populated length
						line->sourceCode_populatedLength	= lnTextLength;
					}
				}


				//////////
				// Copy the content to the original content
				//////
					line->isNewLine	= tlSetNewLineFlag;
					line->sourceCodeOriginal = iDatum_allocate(line->sourceCode->data_u8, line->sourceCode_populatedLength);


				//////////
				// Renumber if need be
				//////
// TODO:  We could do a speedup here if we are appending to the end, we only need to add one to the previous line
					if (sem->showLineNumbers)
						iSEM_renumber(sem, 1);
			}
		}

		// Indicate our status
		return(line);
	}




//////////
//
// Called to insert a line before or after the indicated line
//
//////
	SLine* iSEM_insertLine(SEM* sem, u8* tcText, s32 tnTextLength, SLine* line, bool tlInsertAfter, bool tlSetNewLineFlag)
	{
		SLine* ec;


		logfunc(__FUNCTION__);
		// Make sure our environment is sane
		// Note:  We do not test for tcText and tnTextLength because we can add blank lines
		ec = NULL;
		if (sem && line)
		{
			// Create a new entry
			ec = (SLine*)malloc(sizeof(SLine));
			if (ec)
			{
				// Initialize
				memset(ec, 0, sizeof(SLine));

				// Append a blank line
				ec->sourceCode = iDatum_allocate(tcText, tnTextLength);

				// Insert before or after the indicated line
				if (tlInsertAfter)
				{
					// Have we added one at the end?
					if (sem->lastLine == line)
						sem->lastLine = ec;

					//////////
					// [line->] [<-after]
					// becomes:
					// [line->] [<-lineNew->] [<after]
					//////
						ec->ll.next	= line->ll.next;
						ec->ll.prev	= (SLL*)line;
						line->ll.next		= (SLL*)ec;


					//////////
					// If there's one after this, have it point back
					//////
						if (ec->ll.next)
						{
							// Insert it after
							ec->ll.prev		= ec->ll.next->prev;
							ec->ll.next->prev	= (SLL*)ec;

						} else {
							// None after, so we update ecLast
							sem->lastLine = ec;
						}

				} else {
					// Have we added one before the beginning?
					if (sem->firstLine == line)
						sem->firstLine = ec;

					//////////
					// [before->] [<-line]
					// becomes:
					// [before->] [<-lineNew->] [<-line]
					//////
						ec->ll.prev		= line->ll.prev;
						ec->ll.next		= (SLL*)line;
						line->ll.prev	= (SLL*)ec;


					//////////
					// If there's one before this, have it point forward
					//////
						if (ec->ll.next)
						{
							// Insert it before
							ec->ll.next			= ec->ll.prev->next;
							ec->ll.prev->next	= (SLL*)ec;

						} else {
							// None after, so we update ecLast
							sem->firstLine = ec;
						}
				}

				// Set the new line flag
				ec->isNewLine = tlSetNewLineFlag;

				// Renumber if need be
				if (sem->showLineNumbers)
					iSEM_renumber(sem, 1);
			}
		}

		// Indicate our status
		return(ec);
	}




//////////
//
// Delete the indicated line
//
//////
	void iSEM_deleteLine(SEM* sem)
	{
		SLine* lineDeleted;
		SLine* lineNewCursorLine;


		logfunc(__FUNCTION__);
		// Make sure the environment is sane
		if (sem && !sem->isReadOnly && sem->line_cursor)
		{
			// Delete any content on this line
			if (sem->line_cursor->sourceCode && sem->firstLine != sem->lastLine)
				iDatum_delete(sem->line_cursor->sourceCode, true);

// TODO:  delete compiler info, and extra info

			// Delete the line itself if it's not the only line
			lineDeleted = sem->line_cursor;
			if (sem->firstLine != sem->lastLine)
			{
				// Delete the line
				lineNewCursorLine = (SLine*)iLl_delete__ll((SLL*)sem->line_cursor, true);

			} else {
				// Set the line to this one line
				lineNewCursorLine = sem->line_top;

				// GitHub:4 -- And set the populated length to 0
				sem->line_top->sourceCode_populatedLength = 0;
			}

			// Update anything that may have changed as a result
			if (sem->lastLine == lineDeleted)
				sem->lastLine = lineNewCursorLine;

			if (sem->firstLine == lineDeleted)
				sem->firstLine = lineNewCursorLine;

			if (sem->line_top == lineDeleted)
				sem->line_top = lineNewCursorLine;

			sem->line_cursor = lineNewCursorLine;

			// Renumber if need be
			if (sem->showLineNumbers)
				iSEM_renumber(sem, 1);
		}
	}




//////////
//
// Called to get the colors
//
//////
	void iSEM_getColors(SEM* sem, SObject* obj, SBgra& backColor, SBgra& foreColor)
	{
		logfunc(__FUNCTION__);
		// Make sure our environment is sane
		if (sem && obj)
		{
			// What is the object?
			backColor	= iObjProp_get_sbgra_direct(obj, _INDEX_BACKCOLOR);
			foreColor	= iObjProp_get_sbgra_direct(obj, _INDEX_FORECOLOR);

		} else {
			// It's insane, so we set our colors to default
			backColor	= whiteColor;
			foreColor	= blackColor;
		}
	}




//////////
//
// Obtains the rectangle we have to operate in.  If the object we relate back to is a
// form or subform, then we use the rcClient parameters created by the last render,
// otherwise we use the object's rc.
//
//////
	SFont* iSEM_getRectAndFont(SEM* sem, SObject* obj, RECT* rc)
	{
		SFont* font;


		logfunc(__FUNCTION__);
		// Make sure our environment is sane
		font = gsFontDefault;
		if (sem && obj)
		{
			// Get the client rect
			SetRect(rc, 0, 0, obj->rc.right - obj->rc.left, obj->rc.bottom - obj->rc.top);
			if (sem->font)		font = sem->font;
			else				font = obj->p.font;

		} else {
			// It's insane, so we set our rc to something that will prevent processing
			SetRect(rc, 0, 0, 0, 0);
			font = gsFontDefault;
		}

		// Return the font
		return(font);
	}




//////////
//
// Called when a keypress is made in a source code window, or when a prior keypress
// is now signaling repated keystrokes.
//
//////
	bool iSEM_onKeyDown_sourceCode(SWindow* win, SObject* obj, SVariable* varCtrl, SVariable* varAlt, SVariable* varShift, SVariable* varCaps, SVariable* varAscii, SVariable* varVKey, SVariable* varIsCAS, SVariable* varIsAscii)
	{
		s32				lnMateDirection;
		SEM*			sem;
		SObject*		subform;
		SLine*			line;
		SLine*			lineMate;
		SComp*			comp;
		bool			llCtrl, llAlt, llShift, llCaps, llIsCAS, llIsAscii;
		s16				lcAscii;
		u16				lnVKey;


		// Make sure our environment is sane
		logfunc(__FUNCTION__);
		if (!iiDefaultCallback_processKeyVariables(varCtrl, varAlt, varShift, varCaps, varAscii, varVKey, varIsCAS, varIsAscii, &llCtrl, &llAlt, &llShift, &llCaps, &llIsCAS, &llIsAscii, &lcAscii, &lnVKey))
			return(false);

		// Kick off a sourceLight thread
		CreateThread(NULL, 0, &iSourceLight_update, (void*)obj, 0, 0);

		// Make sure our environment is sane
		sem = NULL;
		if (obj && obj->objType == _OBJ_TYPE_EDITBOX)
		{
			// Grab the EM for this
			sem = obj->p.sem;

			// Send it its key
			if (!llCtrl && !llShift && !llAlt)
			{
				// Regular key without special flags
				switch (lnVKey)
				{
					case VK_F9:
						// Breakpoint toggle
						if (sem && sem->line_cursor)
						{
							// Toggle it
							iSEMLine_toggleBreakpoint(sem);

							// Force the redraw
							iObj_setDirtyRender_ascent(obj, true);

							// Re-render the window
							iWindow_render(win, false);
						}
						break;

					case VK_F6:
					case VK_F8:
						// They want to execute the cursor line of code
						if (sem && sem->line_cursor && sem->line_cursor->sourceCode_populatedLength > 0)
						{
							// Execute the command
							iEngine_engage_oneCommand(sem->line_cursor);

							// If we're still going, then update the screen
							if (!glShuttingDown)
							{
								// Move to next line and redraw
								iSEM_navigate(sem, obj, 1, 0);
								iWindow_render(win, false);
							}
							return(true);
						}
						break;

					case VK_F10:
					case VK_F11:
						// They want to execute the next line where the debugger's stopped
						break;

					case VK_RETURN:
						// Are we on the last line in the command window?
						if (sem && sem->line_cursor && !sem->line_cursor->ll.next && sem->line_cursor->sourceCode_populatedLength > 0)
						{
							subform = iObj_find_thisSubform(obj);
							if (subform && iObj_isCommandWindow(subform))
							{
								// Execute the command
								iEngine_engage_oneCommand(sem->line_cursor);

								// If we're not shutting down, update the screen
								if (!glShuttingDown)
								{
									// Draw it like normal
									iSEM_returnKey(sem, obj);
									iWindow_render(win, false);
								}
								return(true);
							}
							// If we get here, we pass the return key through for editing
						}
						break;
				}

			} else if (llCtrl && !llShift && !llAlt) {
				// CTRL+

			} else if (!llCtrl && llShift && !llAlt) {
				// SHIFT+

			} else if (!llCtrl && !llShift && llAlt) {
				// ALT+

			} else if (llCtrl && llShift && !llAlt) {
				// CTRL+SHIFT+

			} else if (llCtrl && !llShift && llAlt) {
				// CTRL+ALT+

			} else if (!llCtrl && llShift && llAlt) {
				// SHIFT+ALT

			} else if (llCtrl && llShift && llAlt) {
				// CTRL+ALT+SHIFT
				switch (lnVKey)
				{
					case 'M':
						// Mate, they're searching for this component's mate
						// If they're on the cursor line, on a flow control directive, and holding down Ctrl+Alt+Shift, then we want to show that directive's mate on the line above
						line = sem->line_cursor;
						comp = iComps_activeComp_inSEM(sem);
						if (iCat(comp->iCat) == _ICAT_FLOW && iComps_get_mateDirection(comp, &lnMateDirection))
						{
							// Search for the mated line
							lineMate = (SLine*)iSEM_findMate(sem, line, comp);

							// Was it found?
							if (lineMate)
							{
								// Display it
								if (lnMateDirection == -1)		sem->line_highlightBefore	= lineMate;
								else							sem->line_highlightAfter	= lineMate;

							} else {
								// Display mate not found
								if (lnMateDirection == -1)		iSEM_addTooltipHighlight(sem, line, obj, (s8*)cgc_noMateFound, -1, true);	// Show above
								else							iSEM_addTooltipHighlight(sem, line, obj, (s8*)cgc_noMateFound, -1, false);	// Show below
							}
						}

						// Redraw the window
						iObj_setDirtyRender_ascent(obj, true);
						iWindow_render(win, false);
						return(true);
				}
			}
		}

		// When ctrl+alt+shift changes, remove the highlighted
		if (sem && !(llCtrl && llShift && llAlt) && (sem->line_highlightBefore || sem->line_highlightAfter))
		{
			// We're done displaying the highlight
			sem->line_highlightBefore	= NULL;
			sem->line_highlightAfter	= NULL;

			// Redraw
			iObj_setDirtyRender_ascent(obj, true);
			iWindow_render(win, false);
		}

		// Indicate additional events should be processed
		return(iSEM_onKeyDown(win, obj, varCtrl, varAlt, varShift, varCaps, varAscii, varVKey, varIsCAS, varIsAscii));
	}




//////////
//
// Called when a keypress is made, or when a prior keypress is now signaling repated keystrokes.
//
//////
	bool iSEM_onKeyDown(SWindow* win, SObject* obj, SVariable* varCtrl, SVariable* varAlt, SVariable* varShift, SVariable* varCaps, SVariable* varAscii, SVariable* varVKey, SVariable* varIsCAS, SVariable* varIsAscii)
	{
		s32		lnDeltaX;
		bool	llProcessed;
		SEM*	sem;
		bool	llCtrl, llAlt, llShift, llCaps, llIsCAS, llIsAscii;
		s16		lcAscii;
		u16		lnVKey;


		// Make sure our environment is sane
		if (!iiDefaultCallback_processKeyVariables(varCtrl, varAlt, varShift, varCaps, varAscii, varVKey, varIsCAS, varIsAscii, &llCtrl, &llAlt, &llShift, &llCaps, &llIsCAS, &llIsAscii, &lcAscii, &lnVKey))
			return(false);


		logfunc(__FUNCTION__);
		// Make sure our environment is sane
		llProcessed = false;
		if (obj && obj->objType == _OBJ_TYPE_EDITBOX && obj->p.sem)
		{
			// Grab the EM for this
			sem = obj->p.sem;

			// Send it its key
			if (!llCtrl && !llShift && !llAlt)
			{
				// Regular key without special flags
				switch (lnVKey)
				{
					case VK_UP:
						if (iSEM_isSelecting(sem))
						{
							// They want to navigate from the selection, so we go to the top
							iSEM_navigateToSelectStart(sem, obj, false);
							iSEM_selectStop(sem);
						}

						// Navigate up one
						iSEM_navigate(sem, obj, -1, 0);

						// Indicate our key was processed
						llProcessed = true;
						break;

					case VK_DOWN:
						if (iSEM_isSelecting(sem))
						{
							// They want to navigate from the selection, so we go to the top
							iSEM_navigateToSelectEnd(sem, obj, false);
							iSEM_selectStop(sem);
						}

						// Navigate down one
						iSEM_navigate(sem, obj, 1, 0);

						// Indicate our key was processed
						llProcessed = true;
						break;

					case VK_PRIOR:		// Page up
						iSEM_selectStop(sem);
						iSEM_navigatePages(sem, obj, -1);

						// Indicate our key was processed
						llProcessed = true;
						break;

					case VK_NEXT:		// Page down
						iSEM_selectStop(sem);
						iSEM_navigatePages(sem, obj, 1);

						// Indicate our key was processed
						llProcessed = true;
						break;

					case VK_ESCAPE:		// They hit escape, and are cancelling the input
						iSEM_clearLine(sem, obj);

						// Indicate our key was processed
						llProcessed = true;
						break;

					case VK_TAB:
						iSEM_tabIn(sem, obj);

						// Indicate our key was processed
						llProcessed = true;
						break;

					case VK_RETURN:
						// Draw it like normal
						iSEM_returnKey(sem, obj);

						// Indicate our key was processed
						llProcessed = true;
						break;

					case VK_LEFT:
						if (iSEM_isSelecting(sem))
						{
							// They want to navigate from the selection, so we go to the top
							iSEM_navigateToSelectStart(sem, obj, false);
							iSEM_selectStop(sem);
						}

						// Navigate left one
						iSEM_navigate(sem, obj, 0, -1);

						// Indicate our key was processed
						llProcessed = true;
						break;

					case VK_RIGHT:
						if (iSEM_isSelecting(sem))
						{
							// They want to navigate from the selection, so we go to the top
							iSEM_navigateToSelectEnd(sem, obj, false);
							iSEM_selectStop(sem);
						}

						// Navigate right one
						iSEM_navigate(sem, obj, 0, 1);

						// Indicate our key was processed
						llProcessed = true;
						break;

					case VK_HOME:
						if (iSEM_isSelecting(sem))
						{
							// They want to navigate from the selection, so we go to the top
							iSEM_navigateToSelectStart(sem, obj, false);
							iSEM_selectStop(sem);
						}

						// Navigate to the start of the line
						// If there are components, we will first try to navigate to the start of the first non-whitespace component
						if (sem->line_cursor && sem->line_cursor->compilerInfo && sem->line_cursor->compilerInfo->firstComp)
						{
							// Are we already on the first non-whitespace character?
							if (sem->columnEdit == sem->line_cursor->compilerInfo->firstComp->start)
							{
								// Yes, so navigate to the start of the line
								lnDeltaX = -(sem->columnEdit);

							} else {
								// Navigate to the start of the line
								if (sem->columnEdit == 0)
								{
									// Navigate to the first non-whitespace component
									lnDeltaX = sem->line_cursor->compilerInfo->firstComp->start;

								} else {
									// Navigate from where we are to the position of the first non-whitespace component
									lnDeltaX = sem->columnEdit - sem->line_cursor->compilerInfo->firstComp->start;
									if (sem->columnEdit >= sem->line_cursor->compilerInfo->firstComp->start)
										lnDeltaX *= -1;
								}
							}

						} else {
							// Navigate to the start of the line
							lnDeltaX = -(sem->columnEdit);
						}

						// Navigate
						if (lnDeltaX != 0)
							iSEM_navigate(sem, obj, 0, lnDeltaX);

						// Indicate our key was processed
						llProcessed = true;
						break;

					case VK_END:
						if (iSEM_isSelecting(sem))
						{
							// They want to navigate from the selection, so we go to the top
							iSEM_navigateToSelectEnd(sem, obj, false);
							iSEM_selectStop(sem);
						}

						// Navigate to the end of the line
						if (sem->columnEdit != sem->line_cursor->sourceCode_populatedLength)
							iSEM_navigate(sem, obj, 0, sem->line_cursor->sourceCode_populatedLength - sem->columnEdit);

						// Indicate our key was processed
						llProcessed = true;
						break;

					case VK_INSERT:
						iSEM_toggleInsert(sem, obj);

						// Indicate our key was processed
						llProcessed = true;
						break;

					case VK_BACK:
						iSEM_deleteLeft(sem, obj);
						iSEM_selectStop(sem);

						// Indicate our key was processed
						llProcessed = true;
						break;

					case VK_DELETE:
						iSEM_deleteRight(sem, obj);
						iSEM_selectStop(sem);

						// Indicate our key was processed
						llProcessed = true;
						break;

					case VK_CLEAR:
						iSEM_centerCursorLine(sem, obj);

						// Indicate our key was processed
						llProcessed = true;
						break;
				}

			} else if (llCtrl && !llShift && !llAlt) {
				// CTRL+
				switch (lnVKey)
				{
					case VK_ADD:
						if (sem->font)			sem->font = iFont_bigger(sem->font,		true);
						else					sem->font = iFont_bigger(obj->p.font,	false);
						iSEM_verifyCursorIsVisible(sem, obj);
						iObj_setDirtyRender_ascent(obj, true);
						llProcessed = true;
						break;

					case VK_SUBTRACT:
						if (sem->font)			sem->font = iFont_smaller(sem->font,		true);
						else					sem->font = iFont_smaller(obj->p.font,	false);
						iSEM_verifyCursorIsVisible(sem, obj);
						iObj_setDirtyRender_ascent(obj, true);
						llProcessed = true;
						break;

					case 'A':		// Select all
						iSEM_selectAll(sem, obj);

						// Indicate our key was processed
						llProcessed = true;
						break;

					case 'X':		// Cut
						iSEM_cut(sem, obj);

						// Indicate our key was processed
						llProcessed = true;
						break;

					case 'C':		// Copy
						iSEM_copy(sem, obj);

						// Indicate our key was processed
						llProcessed = true;
						break;

					case 'V':		// Paste
						iSEM_paste(sem, obj);

						// Indicate our key was processed
						llProcessed = true;
						break;

					case 'W':		// Save and close
						break;

					case 'Q':		// Quit
						break;

					case VK_UP:		// Up
						iSEM_rollUp(sem, obj);

						// Indicate our key was processed
						llProcessed = true;
						break;

					case VK_DOWN:	// Down
						iSEM_rollDown(sem, obj);

						// Indicate our key was processed
						llProcessed = true;
						break;

					case VK_LEFT:	// Word left
						iSEM_navigateWordLeft(sem, obj, true);

						// Indicate our key was processed
						llProcessed = true;
						break;

					case VK_RIGHT:	// Word right
						iSEM_navigateWordRight(sem, obj, true);

						// Indicate our key was processed
						llProcessed = true;
						break;

					case VK_HOME:	// Home (go to top of content)
						iSEM_navigateToTopLine(sem, obj);

						// Indicate our key was processed
						llProcessed = true;
						break;

					case VK_END:	// Page down (go to end of content)
						iSEM_navigateToEndLine(sem, obj);

						// Indicate our key was processed
						llProcessed = true;
						break;

					case VK_BACK:
						iSEM_deleteWordLeft(sem, obj);

						// Indicate our key was processed
						llProcessed = true;
						break;

					case VK_DELETE:
						iSEM_deleteWordRight(sem, obj);

						// Indicate our key was processed
						llProcessed = true;
						break;
				}

			} else if (!llCtrl && llShift && !llAlt) {
				// SHIFT+
				switch (lnVKey)
				{
					case VK_LEFT:	// Select left
						iSEM_selectLeft(sem, obj);

						// Indicate our key was processed
						llProcessed = true;
						break;

					case VK_RIGHT:	// Select right
						iSEM_selectRight(sem, obj);

						// Indicate our key was processed
						llProcessed = true;
						break;

					case VK_UP:		// Select line up
						iSEM_selectLineUp(sem, obj);

						// Indicate our key was processed
						llProcessed = true;
						break;

					case VK_DOWN:	// Select line down
						iSEM_selectLineDown(sem, obj);

						// Indicate our key was processed
						llProcessed = true;
						break;

					case VK_END:	// Select to end
						iSEM_selectToEndOfLine(sem, obj);

						// Indicate our key was processed
						llProcessed = true;
						break;

					case VK_HOME:	// Select to start
						iSEM_selectToBeginOfLine(sem, obj);

						// Indicate our key was processed
						llProcessed = true;
						break;

					case VK_TAB:	// Shift tab
						iSEM_tabOut(sem, obj);

						// Indicate our key was processed
						llProcessed = true;
						break;

					case VK_PRIOR:		// Page up
						iSEM_navigatePages(sem, obj, -1);

						// Indicate our key was processed
						llProcessed = true;
						break;

					case VK_NEXT:		// Page down
						iSEM_navigatePages(sem, obj, 1);

						// Indicate our key was processed
						llProcessed = true;
						break;

					case VK_SPACE:		// Shift+space is a way to input a space into a token name
						lcAscii		= 255;
						llIsAscii	= true;
						break;
				}

			} else if (!llCtrl && !llShift && llAlt) {
				// ALT+
				switch (lnVKey)
				{
					case 'K':		// Select column mode
						iSEM_selectColumnToggle(sem, obj);

						// Indicate our key was processed
						llProcessed = true;
						break;

					case 'L':		// Select full line mode
						iSEM_selectLineToggle(sem, obj);

						// Indicate our key was processed
						llProcessed = true;
						break;
				}

			} else if (llCtrl && llShift && !llAlt) {
				// CTRL+SHIFT+
				switch (lnVKey)
				{
					case VK_END:	// Select to end
						iSEM_selectToEndLine(sem, obj);

						// Indicate our key was processed
						llProcessed = true;
						break;

					case VK_HOME:	// Select to start
						iSEM_selectToTopLine(sem, obj);

						// Indicate our key was processed
						llProcessed = true;
						break;

					case VK_UP:		// Select line up
						iSEM_selectStart(sem, _SEM_SELECT_MODE_ANCHOR);
						iSEM_rollUp(sem, obj);

						// Indicate our key was processed
						llProcessed = true;
						break;

					case VK_DOWN:	// Select line down
						iSEM_selectStart(sem, _SEM_SELECT_MODE_ANCHOR);
						iSEM_rollDown(sem, obj);

						// Indicate our key was processed
						llProcessed = true;
						break;

					case VK_LEFT:	// Select word left
						iSEM_selectWordLeft(sem, obj);

						// Indicate our key was processed
						llProcessed = true;
						break;

					case VK_RIGHT:	// Select word right
						iSEM_selectWordRight(sem, obj);

						// Indicate our key was processed
						llProcessed = true;
						break;
				}

			} else if (llCtrl && !llShift && llAlt) {
				// CTRL+ALT+

			} else if (!llCtrl && llShift && llAlt) {
				// SHIFT+ALT

			} else if (llCtrl && llShift && llAlt) {
				// CTRL+ALT+SHIFT+

			}

			// If we get here, it wasn't processed above.  Try to stick it in the buffer
			if (!llProcessed && llIsAscii)
				iSEM_keystroke(sem, obj, (u8)lcAscii);		// It's a regular input key
		}

		// Re-render the window if need be
		iWindow_render(win, false);

		// Indicate additional events should be processed
		return(true);
	}




//////////
//
// Moves through source code to find the mated component to the line indicated
//
//////
	void* iSEM_findMate(SEM* sem, SLine* line, SComp* comp)
	{
		s32		lnMateDirection, lnLevel;
		SComp*	compRunner;


		logfunc(__FUNCTION__);
		// Make sure our environment is sane
		if (sem && line && comp && iComps_get_mateDirection(comp, &lnMateDirection))
		{
			// Based on the directive, search backward or forward to find the mate
			lnLevel = 0;
			if (iCat(comp->iCat) == _ICAT_FLOW)
			{
				// Searching by lines
				do {
					// Move to next position
					if (lnMateDirection == -1)		line = (SLine*)line->ll.prev;
					else							line = (SLine*)line->ll.next;

					// Is this us?
					if (line && line->compilerInfo && line->compilerInfo->firstComp)
					{
						if (line->compilerInfo->firstComp->iCode == comp->iCode)
						{
							// We're going a level deeper
							--lnLevel;

						} else if (iComps_isMateOf(line->compilerInfo->firstComp, comp->iCode)) {
							if (lnLevel == 0)
								return(line);

							// Going shallow
							++lnLevel;
						}
					}
				} while (line);
				// If we get here, not found

			} else {
				// Searching by components
				compRunner = comp;
				do {
					// Move to next position
					if (lnMateDirection == -1)		compRunner = compRunner->ll.prevComp;
					else							compRunner = compRunner->ll.nextComp;

					// Is this us?
					if (compRunner)
					{
						if (compRunner->iCode == comp->iCode)
						{
							// We're going a level deeper
							--lnLevel;

						} else if (iComps_isMateOf(compRunner, comp->iCode)) {
							if (lnLevel == 0)
								return(comp);

							// Going shallow
							++lnLevel;
						}
					}
				} while (comp);
				// If we get here, not found
			}
		}

		// if we get here, not found
		return(NULL);
	}




//////////
//
// Called to create a tooltip above the highlighted line
//
//////
	void iSEM_addTooltipHighlight(SEM* sem, SLine* line, SObject* obj, s8* tcText, s32 tnTextLength, bool tlShowAbove)
	{
		RECT		lrc, lrcObjInScreenCoords, lrcTooltip;
		SBitmap*	bmp;
		SFont*		font;
		STooltip*	tooltip;


		logfunc(__FUNCTION__);
		// Make sure our environment is sane
		if (sem && line && line->sourceCode && line->sourceCode->_data && line->sourceCode_populatedLength > 0 && obj && tcText && sem->renderId == line->renderId)
		{
			// Make sure our length is valid
			if (tnTextLength < 0)
				tnTextLength = (s32)strlen(tcText);

			// Determine where it will go
			if (iObj_find_screenRect(obj, &lrcObjInScreenCoords))
			{
				// This is the rectangle of the em in screen coordinates

				//////////
				// Adjust for the location of the line within
				//////
					if (tlShowAbove)
					{
						// Adjust the rectangle to the space above
						SetRect(&lrcTooltip,	lrcObjInScreenCoords.left + line->rcLastRender.left,
												lrcObjInScreenCoords.top  + line->rcLastRender.top - (line->rcLastRender.bottom - line->rcLastRender.top),
												lrcObjInScreenCoords.left + line->rcLastRender.right,
												lrcObjInScreenCoords.top  + line->rcLastRender.top);

					} else {
						// Adjust the rectangle to the space below
						SetRect(&lrcTooltip,	lrcObjInScreenCoords.left + line->rcLastRender.left,
												lrcObjInScreenCoords.top  + line->rcLastRender.bottom,
												lrcObjInScreenCoords.left + line->rcLastRender.right,
												lrcObjInScreenCoords.top + line->rcLastRender.bottom + (line->rcLastRender.bottom - line->rcLastRender.top));
					}


				//////////
				// Construct the bitmap
				//////
					bmp = iBmp_allocate();
					SetRect(&lrc, 0, 0, lrcTooltip.right - lrcTooltip.left, lrcTooltip.bottom - lrcTooltip.top);
					iBmp_createBySize(bmp, lrc.right, lrc.bottom, 24);
					iBmp_colorizeAsCommonTooltipBackground(bmp);


				//////////
				// Overlay the text
				//////
					font = iSEM_getRectAndFont(sem, obj, NULL);
					SelectObject(bmp->hdc, ((font) ? font->hfont : gsFontDefaultTooltip->hfont));
					SetBkMode(bmp->hdc, TRANSPARENT);
					SetTextColor(bmp->hdc, RGB(tooltipForecolor.red, tooltipForecolor.grn, tooltipForecolor.blu));
					InflateRect(&lrc, -4, 0);
					DrawText(bmp->hdc, tcText, tnTextLength, &lrc, DT_SINGLELINE | DT_END_ELLIPSIS | DT_LEFT | DT_NOPREFIX);


				//////////
				// Create the tooltip window
				//////
					tooltip = iTooltip_allocate(&lrcTooltip, bmp, _TOOLTIP_TIMER_DEFAULT_TIMEOUT, true, true);
					iTooltip_show(tooltip);
			}
		}
	}




//////////
//
// Called to render the SEM in the indicated rectangle on the object's bitmap
//
//////
	u32 iSEM_render(SEM* sem, SObject* obj, bool tlRenderCursorline)
	{
		u32			lnPixelsRendered;
		s32			lnI, lnJ, lnTop, lnSkip, lnDeltaX, lnLevel, lnBufferLength;
		bool		llIsValid, llOverrideCaskColors;
		SFont*		font;
		SLine*		line;
		SBitmap*	bmp;
		SBitmap*	bmpCask;
		SBitmap*	bmpNbsp;
		SBitmap*	bmpBreakpoint;
		SBitmap*	bmpBreakpointScaled;
		SVariable*	varStyle;
		SComp*		comp;
		SComp*		compHighlight;
		SComp*		comp2;
		SComp*		compPBBLeft;
		SComp*		compPBBRight;
		HGDIOBJ		hfontOld;
		SBgra		defaultForeColor, defaultBackColor, fillColor, backColorLast, foreColorLast, compForeColor, compBackColor, compFillColor, nbspBackColor, tempColor1, tempColor2;
		RECT		rc, lrc, lrc2, lrc3, lrcComp, lrcText, lrcText2, lrcCompCalcStart, lrcCompCalcDwell;
		s8*			textptr;
		s8			buffer[1024];


		logfunc(__FUNCTION__);
		// Make sure our environment is sane
		lnPixelsRendered = 1;
		if (sem && obj)
		{
			// Support for simple html
			if (sem->isSimpleHtml || ((varStyle = iObjProp_get(obj, _INDEX_STYLE)) && iiVariable_getAs_s32(varStyle) == _STYLE_HTML))
				return(iSEM_renderAs_simpleHtml(sem, obj, tlRenderCursorline));

			// Get the top line and continue down as far as we can
			line	= sem->line_top;
			bmp		= obj->bmp;
			lnTop	= 0;

			// Indicate the current render ID number
			++sem->renderId;


			//////////
			// Grab font, coordinates, and colors
			//////
				font = iSEM_getRectAndFont(sem, obj, &rc);
				iSEM_getColors(sem, obj, defaultBackColor, defaultForeColor);
				backColorLast.color			= defaultBackColor.color;
				foreColorLast.color			= defaultForeColor.color;
				iMisc_adjustColorBrightness(backColorLast, -5.0f);
				iMisc_adjustColorBrightness(foreColorLast, 5.0f);
				hfontOld = SelectObject(bmp->hdc, font->hfont);		// Save the original font, and set our current font


			//////////
			// Determine what component they're currently on, and highlight any same-named references on-screen
			//////
				compHighlight = iComps_activeComp_inSEM(sem);
				if (compHighlight && (!compHighlight->line || !compHighlight->line->sourceCode || !compHighlight->line->sourceCode->_data))
					compHighlight = NULL;	// Invalid, ignore it


			//////////
			// Prepare for rendering
			//////
				CopyRect(&lrc, &rc);
				if (sem->showLineNumbers)
				{
					// Adjust lrc over for room for line numbers
					CopyRect(&sem->rcLineNumberLastRender, &rc);
					DrawText(bmp->hdc, "  9999 ", 7, &sem->rcLineNumberLastRender, DT_SINGLELINE | DT_LEFT | DT_NOPREFIX | DT_CALCRECT);
					SetRect(&sem->rcLineNumberLastRender, rc.left, rc.top, rc.left + (sem->rcLineNumberLastRender.right - sem->rcLineNumberLastRender.left), rc.bottom);
					lrc.left	= sem->rcLineNumberLastRender.right;
					rc.left		= sem->rcLineNumberLastRender.right;
				}


			// Iterate for every visible line
			while (line && lrc.top + font->tm.tmHeight < rc.bottom)
			{
				// Store the render ID
				line->renderId = sem->renderId;

				// If there is compiler information, clear out any prior highlighting
				if (line->compilerInfo && line->compilerInfo->firstComp)
				{
					//////////
					// Clear off any former highlights, and highlight the current
					//////
						comp = line->compilerInfo->firstComp;
						while (comp)
						{
							// Clear this entry
							comp->overrideMatchingBackColor = NULL;
							comp->overrideMatchingForeColor = NULL;

							// Move to next component
							comp = comp->ll.nextComp;
						}


					//////////
					// Highlight the closest parenthesis, bracket, or brace
					//////
						if (line == sem->line_cursor)
						{
							//////////
							// Locate the closest match
							//////
								comp = line->compilerInfo->firstComp;
								while (comp)
								{
									// Are they on this component?
									if (sem->columnEdit >= comp->start && sem->columnEdit <= comp->start + comp->length)
									{
										// This is the current component we're highlighting
										if (iComps_findClosest_parensBracketsBraces(comp, comp, &compPBBLeft, &compPBBRight))
										{
											// We found something
											if (iComps_isParensBracketsBraces(comp))
											{
												// Mark all commas between as highlighted
												comp2	= compPBBLeft->ll.nextComp;
												lnLevel	= 0;
												while (comp2 != compPBBRight)
												{
													if (lnLevel == 0 && comp2->iCode == _ICODE_COMMA)
													{
														// Mark this component
														comp2->overrideMatchingBackColor	= &overrideMatchingBackColorMultiple;
														comp2->overrideMatchingForeColor	= &overrideMatchingForeColorMultiple;

														comp2->overrideMatchingBackColor	= &overrideMatchingBackColorMultiple;
														comp2->overrideMatchingForeColor	= &overrideMatchingForeColorMultiple;

													} else if (iComps_isMateOf(comp2, compPBBLeft->iCode)) {
														// If the left-most is (, then this is a ), going shallow
														++lnLevel;

													} else if (comp2->iCode == compPBBLeft->iCode) {
														// We're going deep
														--lnLevel;
													}

													// Move to next component
													comp2 = comp2->ll.nextComp;
												}

											}
											// Mark the two
											compPBBLeft->overrideMatchingBackColor	= &overrideMatchingBackColor;
											compPBBLeft->overrideMatchingForeColor	= &overrideMatchingForeColor;

											compPBBRight->overrideMatchingBackColor	= &overrideMatchingBackColor;
											compPBBRight->overrideMatchingForeColor	= &overrideMatchingForeColor;
										}
										break;
									}

									// Move to next component
									comp = comp->ll.nextComp;
								}
						}
				}


				//////////
				// Determine the position
				//////
					SetRect(&lrc2, rc.left, rc.top + lnTop, rc.right, rc.top + lnTop + (font->tm.tmHeight * 2));
					DrawText(bmp->hdc, cvarSpace2000->value.data_s8, 1, &lrc2, DT_CALCRECT);
					SetRect(&lrc, rc.left, rc.top + lnTop, rc.right, rc.top + lnTop + (lrc2.bottom - lrc2.top));
					if (lrc.bottom > rc.bottom)
						lrc.bottom = rc.bottom;


				//////////
				// Determine the color
				//////
					SetBkMode(bmp->hdc, OPAQUE);
					if (sem->line_cursor == line && sem->showCursorLine && tlRenderCursorline)
					{
						// Display in the cursor color line
						SetBkColor(bmp->hdc, RGB(currentStatementBackColor.red, currentStatementBackColor.grn, currentStatementBackColor.blu));
						SetTextColor(bmp->hdc, RGB(currentStatementForeColor.red, currentStatementForeColor.grn, currentStatementForeColor.blu));
						fillColor.color	= currentStatementBackColor.color;

					} else if (line->ll.next || ((!sem->showCursorLine || !tlRenderCursorline) && !sem->showEndLine)) {
						// Display in normal background color
						SetBkColor(bmp->hdc, RGB(defaultBackColor.red, defaultBackColor.grn, defaultBackColor.blu));
						SetTextColor(bmp->hdc, RGB(defaultForeColor.red, defaultForeColor.grn, defaultForeColor.blu));
						hfontOld		= SelectObject(bmp->hdc, font->hfont);
						fillColor.color	= defaultBackColor.color;

					} else {
						// This is the last line, display in the last line color
						SetBkColor(bmp->hdc, RGB(backColorLast.red, backColorLast.grn, backColorLast.blu));
						SetTextColor(bmp->hdc, RGB(foreColorLast.red, foreColorLast.grn, foreColorLast.blu));
						hfontOld		= SelectObject(bmp->hdc, font->hfont);
						fillColor.color	= backColorLast.color;
					}


				//////////
				// Determine the render rectangles (populated area on left, area to clear on right)
				//////
					CopyRect(&lrc2, &lrc);
					CopyRect(&line->rcLastRender, &lrc);	// Store the rect for highlight messages

					// Will we fit?
					if (line->sourceCode->_data && line->sourceCode_populatedLength > 0 && sem->columnLeft < line->sourceCode_populatedLength)
					{
						// Draw the portion that will fit
						DrawText(bmp->hdc, line->sourceCode->data_s8 + sem->columnLeft, line->sourceCode_populatedLength - sem->columnLeft, &lrc2, DT_VCENTER | DT_LEFT | DT_SINGLELINE | DT_NOPREFIX | DT_CALCRECT);
						lrc2.right	= min(rc.right,  lrc2.right);
						lrc2.bottom	= min(rc.bottom, lrc2.bottom);
						// Set the clear border
						SetRect(&lrc3, lrc2.right, lrc2.top, rc.right, lrc2.bottom);

					} else {
						// We're scrolled past this line, so the entire area must be filled in
						// Set the clear border
						CopyRect(&lrc3, &lrc);
					}


				//////////
				// Fill the line with the appropriate background color
				//////
					iBmp_fillRect(bmp, &lrc3, fillColor, fillColor, fillColor, fillColor, false, NULL, false);


					// Do we need to draw anything?
					if (line->sourceCode->_data && line->sourceCode_populatedLength != 0 && line->sourceCode_populatedLength >= sem->columnLeft)
					{
						// Draw the text
						DrawText(bmp->hdc, line->sourceCode->data_s8 + sem->columnLeft, line->sourceCode_populatedLength - sem->columnLeft, &lrc2, DT_VCENTER | DT_LEFT | DT_SINGLELINE | DT_NOPREFIX);

						// If they're selecting, highlight the selected portion
						if (line->compilerInfo && line->compilerInfo->firstComp)
						{
							// Highlight both components and whitespaces
							iSEM_render_highlightSelectedComps(sem, line->compilerInfo->firstComp);
							iSEM_render_highlightSelectedComps(sem, line->compilerInfo->firstComp->firstWhitespace);
						}


						// For source code, we perform syntax highlighting
						if (sem->isSourceCode && line->compilerInfo && line->compilerInfo->firstComp && sem->columnLeft < line->sourceCode_populatedLength)
						{
							// Source code, syntax highlight
							if (sem->isSourceCode && line->compilerInfo && line->compilerInfo->firstComp)
							{
								// Redraw items that are to be colorized in their color
								for (lnI = 1; lnI < 3; lnI++)
								{
									// Determine if we're rendering components or whitespaces
									if (lnI == 1)		comp = line->compilerInfo->firstComp;
									else				comp = line->compilerInfo->firstComp->firstWhitespace;

									// For all of these, render them one by one
									while (comp)
									{
										//////////
										// Remove any nbsp characters
										//////
											if (comp->nbspCount != 0)
											{
												// Copy to a temporary buffer
												lnBufferLength = min(comp->length, (s32)sizeof(buffer));
												memcpy(buffer, comp->line->sourceCode->data_s8 + comp->start, lnBufferLength);

												// Remove nbsp characters
												for (lnJ = 0; lnJ < lnBufferLength; lnJ++)
												{
													// If it's a nbsp, replace with a normal space for rendering
													if ((u8)buffer[lnJ] == 255)
														buffer[lnJ] = 32;
												}

												// Setup the pointer
												textptr = (s8*)&buffer[0];

											} else {
												// No nbsp characters, so just draw whatever's there
												textptr = comp->line->sourceCode->data_s8 + comp->start;
											}

										// Fore color
										llOverrideCaskColors = true;
										if (comp->overrideSelectionBackColor)
										{
											// Use the selection color
											SetBkMode(bmp->hdc, OPAQUE);
											SetBkColor(bmp->hdc, RGB(comp->overrideSelectionBackColor->red, comp->overrideSelectionBackColor->grn, comp->overrideSelectionBackColor->blu));
											compBackColor.color		= comp->overrideSelectionBackColor->color;
											compFillColor.color		= comp->overrideSelectionBackColor->color;
											llOverrideCaskColors	= false;

											// Update our component color during selections
											     if (comp->overrideSelectionForeColor)		compForeColor.color = comp->overrideSelectionForeColor->color;
											else if (comp->color)							compForeColor.color = comp->color->color;
											else											compForeColor.color = defaultForeColor.color;

										} else if (comp->overrideMatchingForeColor) {
											// Use the matching color
											SetBkMode(bmp->hdc, OPAQUE);
											SetBkColor(bmp->hdc, RGB(comp->overrideMatchingBackColor->red, comp->overrideMatchingBackColor->grn, comp->overrideMatchingBackColor->blu));
											compBackColor.color		= comp->overrideMatchingBackColor->color;
											compFillColor.color		= comp->overrideMatchingBackColor->color;
											compForeColor.color		= comp->overrideMatchingForeColor->color;
											llOverrideCaskColors	= false;

										} else if (comp->color) {
											// Use the component override color
											SetBkMode(bmp->hdc, TRANSPARENT);
											SetBkColor(bmp->hdc, RGB(fillColor.red, fillColor.grn, fillColor.blu));
											compBackColor.color	= fillColor.color;
											compFillColor.color	= fillColor.color;
											compForeColor.color	= comp->color->color;

										} else {
											// Use the standard display color
											SetBkMode(bmp->hdc, TRANSPARENT);
											SetBkColor(bmp->hdc, RGB(fillColor.red, fillColor.grn, fillColor.blu));
											compBackColor.color	= fillColor.color;
											compFillColor.color	= fillColor.color;
											compForeColor.color	= defaultForeColor.color;
										}

										// Find out where it starts
										SetRect(&lrcCompCalcStart, 0, 0, 200000, lrc.bottom);
										if (comp->start != 0)		DrawText(bmp->hdc, cvarSpace2000->value.data_s8, comp->start, &lrcCompCalcStart, DT_VCENTER | DT_LEFT | DT_SINGLELINE | DT_NOPREFIX | DT_CALCRECT);
										else						SetRect(&lrcCompCalcStart, 0, 0, 0, lrc.bottom);

										// Find out how long it dwells
										SetRect(&lrcCompCalcDwell, lrcCompCalcStart.right, 0, 200000, lrc.bottom);
										DrawText(bmp->hdc, cvarSpace2000->value.data_s8, comp->length, &lrcCompCalcDwell, DT_VCENTER | DT_LEFT | DT_SINGLELINE | DT_NOPREFIX | DT_CALCRECT);
										SetRect(&lrcComp, rc.left + lrcCompCalcDwell.left, lrc2.top, rc.left + lrcCompCalcDwell.right, lrc2.bottom);

										// Do we need to adjust it back for scrolling?
										if (sem->columnLeft != 0)
										{
											// Adjust it for the sem->leftColumn
											lnDeltaX		= sem->columnLeft * ((lrcComp.right - lrcComp.left) / comp->length);
											lrcComp.left	-= lnDeltaX;
											lrcComp.right	-= lnDeltaX;
										}

										// Is this a component that should be highlighted?
										if (compHighlight && comp != compHighlight && comp->length == compHighlight->length && _memicmp(comp->line->sourceCode->data_s8 + comp->start, compHighlight->line->sourceCode->data_s8 + compHighlight->start, comp->length) == 0)
										{
											SetBkMode(bmp->hdc, OPAQUE);
											SetBkColor(bmp->hdc, RGB(highlightSymbolBackColor.red, highlightSymbolBackColor.grn, highlightSymbolBackColor.blu));
											compBackColor.color		= highlightSymbolBackColor.color;
											llOverrideCaskColors	= false;
										}

										// Is it a cask or text?
										if (comp->iCode >= _ICODE_CASK_MINIMUM && comp->iCode <= _ICODE_CASK_MAXIMUM)
										{
											// Is there a cask cache from a previous screen render?
											if (!comp->bc || !iBmp_isValidCache(&comp->bc, defaultBackColor.color, defaultForeColor.color, fillColor.color, (lrcComp.right - lrcComp.left), (lrcComp.bottom - lrcComp.top), comp->iCode, lrcComp.left, compFillColor.color, compBackColor.color, 0, 0, 0, 0, 0))
											{
												// The bitmap cache is no longer valid
												iBmp_deleteCache(&obj->bc);

												// It's a cask, build it
												bmpCask = iBmp_cask_createAndPopulate(comp->iCode,
																						lrcComp.right  - lrcComp.left,
																						lrcComp.bottom - lrcComp.top,
																						&lnSkip,
																						comp->length,
																						&compBackColor,
																						compForeColor,
																						compFillColor,
																						llOverrideCaskColors);

												// If we decide to display it with an alpha, this also may need to be brought outside of the if block
												// Overlay the text
												SetBkMode(bmpCask->hdc, TRANSPARENT);
												SelectObject(bmpCask->hdc, font->hfont);
												SetTextColor(bmpCask->hdc, RGB(compForeColor.red, compForeColor.grn, compForeColor.blu));
												SetRect(&lrcText, 0, -1, bmpCask->bi.biWidth, bmpCask->bi.biHeight);
												DrawText(bmpCask->hdc, textptr + lnSkip, comp->length - (2 * lnSkip), &lrcText, DT_VCENTER | DT_CENTER | DT_SINGLELINE | DT_NOPREFIX | DT_END_ELLIPSIS);
												SetBkMode(bmpCask->hdc, OPAQUE);

												// Add the visual cue if need be
												if (comp->nbspCount != 0)
												{
													// Add in the underline for where it should be
													tempColor1 = iBmp_colorCombine(blueColor, compBackColor, sem->minNbspColorInfluence + 0.1f);
													tempColor2 = iBmp_colorCombine(blueColor, compBackColor, sem->maxNbspColorInfluence + 0.1f);
													CopyRect(&lrcText2, &lrcText);
													InflateRect(&lrcText2, -(lnSkip * font->tm.tmAveCharWidth), 0);
													lrcText2.top = lrcText2.top + ((lrcText2.bottom - lrcText2.top) * 3 / 4);
													iBmp_colorizeRect(bmpCask, &lrcText2, tempColor1, tempColor1, tempColor2, tempColor2, true, NULL, false, 1.0f);
												}

												// Save the cache
												iBmp_createCache(&comp->bc, bmpCask, defaultBackColor.color, defaultForeColor.color, fillColor.color, (lrcComp.right - lrcComp.left), (lrcComp.bottom - lrcComp.top), comp->iCode, lrcComp.left, compFillColor.color, compBackColor.color, 0, 0, 0, 0, 0, false);

											} else {
												// Use the bitmap cache
												bmpCask = comp->bc->bmpCached;
											}

											// Publish it
											if (line == sem->line_cursor && sem->columnEdit >= comp->start && sem->columnEdit <= comp->start + comp->length)
											{
//////////
// Aug.16.2014 -- I originally had the idea of drawing a partially translucent cask over the top of the text... but the text seems to draw it properly, so I removed it.
// 												// The cursor is currently on this item, draw with a 15% transparency
//												iBmp_bitBltAlpha(bmp, &lrcComp, bmpCask, 0.15f);
//////
												// For now, just render it in the standard color in case it's selected
												goto renderAsText;

											} else {
												// Draw completely opaque
												iBmp_bitBlt(bmp, &lrcComp, bmpCask);
											}

										} else {
renderAsText:
											// We either draw it directly as text as it is, or if it has a non-breaking-space, we need to alter its appearance for the purposes of allowing spaces in variable names.
											if (comp->nbspCount)
											{
												// It's a name with a non-breaking-space, so we need to render it as a special graphic.
												// For these we will take a name like "my variable" and render a half-space between "my" and "variable", and take the pixels which were removed and prefix and postfix the name with it.
												// This will be drawn on a background that is a slightly altered background for its current color so it visually stands out, but the background will fade away from the edges sort of like the way the splash screen does along the left-side list.

												// Is there a cask cache from a previous screen render?
												if (!comp->bc || !iBmp_isValidCache(&comp->bc, defaultBackColor.color, defaultForeColor.color, fillColor.color, (lrcComp.right - lrcComp.left), (lrcComp.bottom - lrcComp.top), comp->iCode, lrcComp.left, compFillColor.color, compBackColor.color, 0, 0, 0, 0, 0))
												{
													// The bitmap cache is no longer valid
													iBmp_deleteCache(&obj->bc);

													// An explicit background color?
													nbspBackColor = compBackColor;
													if (comp->overrideMatchingBackColor)
														nbspBackColor = *comp->overrideMatchingBackColor;

													// Is this a component that should be highlighted?
													if (compHighlight && comp != compHighlight && comp->length == compHighlight->length && _memicmp(comp->line->sourceCode->data_s8 + comp->start, compHighlight->line->sourceCode->data_s8 + compHighlight->start, comp->length) == 0)
														nbspBackColor = highlightSymbolBackColor;

													// Build it
													bmpNbsp = iBmp_nbsp_createAndPopulate(	comp, font, sem->minNbspColorInfluence, sem->maxNbspColorInfluence,
																							lrcComp.right  - lrcComp.left,
																							lrcComp.bottom - lrcComp.top,
																							nbspBackColor,
																							compForeColor);

													// Save the cache
													iBmp_createCache(&comp->bc, bmpNbsp, defaultBackColor.color, defaultForeColor.color, fillColor.color, (lrcComp.right - lrcComp.left), (lrcComp.bottom - lrcComp.top), comp->iCode, lrcComp.left, compFillColor.color, compBackColor.color, 0, 0, 0, 0, 0, false);

												} else {
													// Use the bitmap cache
													bmpNbsp = comp->bc->bmpCached;
												}

												// If the cursor's on the thing, then render it normally
												if (line == sem->line_cursor && sem->columnEdit >= comp->start && sem->columnEdit <= comp->start + comp->length)
													goto renderAsOnlyText;

												// Draw completely opaque
												iBmp_bitBlt(bmp, &lrcComp, bmpNbsp);

											} else {
												// Draw the text
renderAsOnlyText:
												// Set the color
												SetTextColor(bmp->hdc, RGB(compForeColor.red, compForeColor.grn, compForeColor.blu));

												// An explicit background color?
												if (comp->overrideMatchingBackColor)
													SetBkColor(bmp->hdc, RGB(comp->overrideMatchingBackColor->red, comp->overrideMatchingBackColor->grn, comp->overrideMatchingBackColor->blu));

												// Is this a component that should be highlighted?
												if (compHighlight && comp != compHighlight && comp->length == compHighlight->length && _memicmp(comp->line->sourceCode->data_s8 + comp->start, compHighlight->line->sourceCode->data_s8 + compHighlight->start, comp->length) == 0)
													SetBkColor(bmp->hdc, RGB(highlightSymbolBackColor.red, highlightSymbolBackColor.grn, highlightSymbolBackColor.blu));

												// Draw this component
												SetBkMode(bmp->hdc, OPAQUE);
												DrawText(bmp->hdc, textptr, comp->length, &lrcComp, DT_VCENTER | DT_LEFT | DT_SINGLELINE | DT_NOPREFIX);

												// If we should bold, bold it
												if (comp->useBoldFont)
												{
													// Set transparent mode, render, then back to opaque
													SetBkMode(bmp->hdc, TRANSPARENT);
													DrawText(bmp->hdc, textptr, comp->length, &lrcComp, DT_VCENTER | DT_LEFT | DT_SINGLELINE | DT_NOPREFIX);
													SetBkMode(bmp->hdc, OPAQUE);
												}

												// Any nbps?  If so, colorize the underlined portion
												if (comp->nbspCount)
												{
													tempColor1 = iBmp_colorCombine(blueColor, compBackColor, sem->minNbspColorInfluence);
													tempColor2 = iBmp_colorCombine(blueColor, compBackColor, sem->maxNbspColorInfluence);
													CopyRect(&lrcText2, &lrcComp);
													lrcText2.top = lrcText2.top + ((lrcText2.bottom - lrcText2.top) * 3 / 4);
													iBmp_colorizeRect(bmp, &lrcText2, tempColor1, tempColor1, tempColor2, tempColor2, true, NULL, false, 1.0f);
												}

												// If it's a comp that we're highlighting, highlight it
//////////
// Aug.16.2014 -- This is an optional way to highlight the component.  It draws a gradient over the component to signal its being highlighted.  Far too overt in my opinion.
//												if (compHighlight && comp != compHighlight && comp->length == compHighlight->length && _memicmp(comp->line->sourceCode->data_s8 + comp->start, compHighlight->line->sourceCode->data_s8 + compHighlight->start, comp->length) == 0)
// 													iBmp_colorizeHighlightGradient(bmp, &lrcComp, overrideMatchingBackColor, 0.5f, 0.25f);
//////
											}
										}


										//////////
										// Check errors and warnings
										//////
											if (line != sem->line_cursor && (comp->isError || comp->isWarning))
											{
												// Adjust the top down to the lower 1/4th
												lrcComp.top += ((lrcComp.bottom - lrcComp.top) * 3) / 4;

												// Is it a warning?
												if (comp->isWarning && !comp->isError)
													iBmp_wavyLine(bmp, &lrcComp, orangeColor);		// Overlay an amber wavy line on the lower 1/3rd of the component

												// Is it an error? (if there is an error and a warning, errors take precedence)
												if (comp->isError)
													iBmp_wavyLine(bmp, &lrcComp, redColor);			// Overlay a red wavy line on the lower 1/3rd of the component
											}


										// Move to next component
										comp = comp->ll.nextComp;
									}
								}
							}
						}
					}


				//////////
				// Draw the cursor if on the cursor line
				//////
					if (sem->line_cursor == line && sem->showCursorLine && tlRenderCursorline)
					{
						SetRect(&lrcCompCalcStart, 0, 0, lrc.right, lrc.bottom);
						if (sem->columnEdit != 0)
						{
							// It's somewhere on the line
							DrawText(bmp->hdc, cvarSpace2000->value.data_s8, sem->columnEdit - sem->columnLeft, &lrcCompCalcStart, DT_VCENTER | DT_LEFT | DT_SINGLELINE | DT_NOPREFIX | DT_CALCRECT);
							SetRect(&lrcCompCalcDwell, lrcCompCalcStart.right, 0, lrc.right, lrc.bottom);
							DrawText(bmp->hdc, cvarSpace2000->value.data_s8, 1, &lrcCompCalcDwell, DT_VCENTER | DT_LEFT | DT_SINGLELINE | DT_NOPREFIX | DT_CALCRECT);
							SetRect(&lrcComp, rc.left + lrcCompCalcDwell.left, lrc2.top, rc.left + lrcCompCalcDwell.right, lrc2.bottom);

						} else {
							// It's all the way to the left
							DrawText(bmp->hdc, cvarSpace2000->value.data_s8, 1, &lrcCompCalcStart, DT_VCENTER | DT_LEFT | DT_SINGLELINE | DT_NOPREFIX | DT_CALCRECT);
							SetRect(&lrcComp, rc.left + ((sem->isOverwrite) ? 0 : 1), lrc.top, rc.left + lrcCompCalcStart.right, lrc.bottom);
						}

						iBmp_invert(bmp, lrcComp.left - ((sem->isOverwrite) ? 0 : 1), ((sem->isOverwrite) ? lrc.bottom - 2 : lrc.top), ((sem->isOverwrite) ? lrcComp.right : lrcComp.left + ((sem->isOverwrite) ? 0 : 1)), lrc.bottom);
					}


				//////////
				// Overlay the line number
				//////
					if (sem->showLineNumbers)
					{
						// Left-side overlay
						SetRect(&lrc3, sem->rcLineNumberLastRender.left, lrc2.top, sem->rcLineNumberLastRender.right, lrc2.bottom);
						iBmp_fillRect(bmp, &lrc3, lineNumberFillColor, lineNumberFillColor, lineNumberFillColor, lineNumberFillColor, false, NULL, false);
						iBmp_drawVerticalLine(bmp, lrc3.top, lrc3.bottom, lrc3.right - 1, lineNumberBackColor);

						// Get our line number
						sprintf(buffer, "%u\0", line->lineNumber);

						// Back off one character, and render the line number right-justified
						lrc3.right -= (sem->rcLineNumberLastRender.right - sem->rcLineNumberLastRender.left) / 7;
						SetBkMode(bmp->hdc, TRANSPARENT);
						SetTextColor(bmp->hdc, RGB(lineNumberForeColor.red, lineNumberForeColor.grn, lineNumberForeColor.blu));
						DrawText(bmp->hdc, buffer, (int)strlen(buffer), &lrc3, DT_SINGLELINE | DT_RIGHT | DT_NOPREFIX);


						//////////
						// If we're on the cursor line, extend its color influence to the left line number area
						//////
							if (line == sem->line_cursor && !line->breakpoint && tlRenderCursorline)
							{
								SetRect(&lrc3, sem->rcLineNumberLastRender.left, lrc2.top, sem->rcLineNumberLastRender.right, lrc2.bottom);
								iBmp_colorize(bmp, &lrc3, currentStatementBackColor, false, 0.0f);
							}


						//////////
						// Show the breakpoint
						//////
							if (line->breakpoint && line->breakpoint->isUsed)
							{
								// Determine the breakpoint parameters
								llIsValid = true;
								switch (line->breakpoint->type)
								{
									case _BREAKPOINT_ALWAYS:
										if (line->breakpoint->countdownResetValue == 0)			bmpBreakpoint = bmpBreakpointAlways;
										else													bmpBreakpoint = bmpBreakpointAlwaysCountdown;
										break;

									case _BREAKPOINT_CONDITIONAL_TRUE:
										bmpBreakpoint = bmpConditionalTrue;
										break;

									case _BREAKPOINT_CONDITIONAL_FALSE:
										bmpBreakpoint = bmpConditionalFalse;
										break;

									case _BREAKPOINT_CONDITIONAL_TRUE_COUNTDOWN:
										bmpBreakpoint = bmpConditionalTrueCountdown;
										break;

									case _BREAKPOINT_CONDITIONAL_FALSE_COUNTDOWN:
										bmpBreakpoint = bmpConditionalFalseCountdown;
										break;

									default:
										// Unknown type, ignore it
										llIsValid = false;
										break;
								}

								// Render the breakpoint if it's valid
								if (llIsValid)
								{
									//////////
									// Draw the icon
									//////
										bmpBreakpointScaled = iBmp_allocate();
										iBmp_createBySize(bmpBreakpointScaled, (lrc3.bottom - lrc3.top), (lrc3.bottom - lrc3.top), bmpBreakpoint->bi.biBitCount);
										iBmp_scale(bmpBreakpointScaled, bmpBreakpoint);
										iBmp_bitBlt(bmp, &lrc3, bmpBreakpointScaled);
										iBmp_delete(&bmpBreakpointScaled, true, true);


									//////////
									// Give the source code line some breakpoint color love :-)
									//////
										if (line == sem->line_cursor)
										{
											// Just do the sem->rcLineNumberLastRender portion
											SetRect(&lrc3, sem->rcLineNumberLastRender.left, lrc2.top, sem->rcLineNumberLastRender.right, lrc2.bottom);

										} else {
											// Do the entire line
											SetRect(&lrc3, 0, lrc.top, rc.right, lrc.bottom);
										}

										// Colorize it
										iBmp_alphaColorizeMask(bmp, &lrc3, breakpointBackColor, 0.25f);
								}
						}


					//////////
					// Overlay an indicator if the line has changed, or is a new line (since last save)
					//////
						SetRect(&lrc3, sem->rcLineNumberLastRender.right - 4, lrc2.top, sem->rcLineNumberLastRender.right - 1, lrc2.bottom);
						if (!sem->hideEditCues)
						{
							if (iSEMLine_hasChanged(line))
							{
								// The content has changed
								iBmp_fillRect(bmp, &lrc3, sem->changedColor, sem->changedColor, sem->changedColor, sem->changedColor, false, NULL, false);

							} else if (line->isNewLine) {
								// The line is new
								iBmp_fillRect(bmp, &lrc3, sem->newColor, sem->newColor, sem->newColor, sem->newColor, false, NULL, false);
							}
						}


					//////////
					// Show any breadcrumbs
					//////
// TODO:  Once the program execution engine is coded, breadcrumbs will need to overlay here
					}


				//////////
				// Move down to the next row
				//////
					lnTop	+= (lrc.bottom - lrc.top);
					line	= (SLine*)line->ll.next;
			}

			// Fill in the remainder of the display
			SetRect(&lrc, rc.left, rc.top + lnTop, rc.right, rc.bottom);
			iBmp_fillRect(bmp, &lrc, defaultBackColor, defaultBackColor, defaultBackColor, defaultBackColor, false, NULL, false);

			// Line number portion
			SetRect(&lrc3, sem->rcLineNumberLastRender.left, rc.top + lnTop, sem->rcLineNumberLastRender.right, rc.bottom);
			iBmp_fillRect(bmp, &lrc3, lineNumberFillColor, lineNumberFillColor, lineNumberFillColor, lineNumberFillColor, false, NULL, false);
			iBmp_drawVerticalLine(bmp, lrc3.top, lrc3.bottom, lrc3.right - 1, lineNumberBackColor);


			//////////
			// If there are any highlights, overlay them
			//////
				if (sem->line_cursor && sem->line_cursor->renderId == sem->renderId)
				{
					// Grab the coordinates of the cursor line
					CopyRect(&lrc3, &sem->line_cursor->rcLastRender);

					// If there are any highlight overlays, display them
					if (sem->line_highlightBefore)
					{
						// Will appear before
						line = sem->line_highlightBefore;

						// Move up one line
						OffsetRect(&lrc3, 0, -(lrc3.bottom - lrc3.top));

						// Colorize that entire section
						iBmp_fillRect(bmp, &lrc3, tooltipNwBackColor, tooltipNeBackColor, tooltipSwBackColor, tooltipSeBackColor, true, NULL, false);
						iBmp_frameRect(bmp, &lrc3, tooltipForecolor, tooltipForecolor, tooltipForecolor, tooltipForecolor, false, NULL, false);

						// Overlay the text
						if (line->sourceCode->_data && line->sourceCode_populatedLength != 0 && line->sourceCode_populatedLength >= sem->columnLeft)
						{
							//////////
							// Remove any nbsp characters
							//////
								if (iIsCharacterInHaystack(line->sourceCode->data_s8, line->sourceCode_populatedLength, -1, NULL))
								{
									// Copy to a temporary buffer
									lnBufferLength = min(line->sourceCode_populatedLength - sem->columnLeft, (s32)sizeof(buffer));
									memcpy(buffer, line->sourceCode->data_s8 + sem->columnLeft, lnBufferLength);

									// Remove nbsp characters
									for (lnJ = 0; lnJ <= lnBufferLength; lnJ++)
									{
										// If it's a nbsp, replace with a normal space for rendering
										if ((u8)buffer[lnJ] == 255)
											buffer[lnJ] = 32;
									}

									// Setup the pointer
									textptr = (s8*)&buffer[0];

								} else {
									// No nbsp characters, so just draw whatever's there
									textptr			= line->sourceCode->data_s8 + sem->columnLeft;
									lnBufferLength	= line->sourceCode_populatedLength - sem->columnLeft;
								}


							//////////
							// Draw the line
							//////
								SetTextColor(bmp->hdc, RGB(tooltipForecolor.red, tooltipForecolor.grn, tooltipForecolor.blu));
								DrawText(bmp->hdc, textptr, lnBufferLength, &lrc3, DT_VCENTER | DT_LEFT | DT_SINGLELINE | DT_NOPREFIX);


							//////////
							// Add in the line numbers
							//////
								if (sem->showLineNumbers)
								{
									// Adjust for the line number area
									SetRect(&lrc3, 0, lrc3.top, lrc3.left, lrc3.bottom);

									// Colorize that entire section
									iBmp_fillRect(bmp, &lrc3, tooltipNwBackColor, tooltipNeBackColor, tooltipSwBackColor, tooltipSeBackColor, true, NULL, false);
									iBmp_frameRect(bmp, &lrc3, tooltipForecolor, tooltipForecolor, tooltipForecolor, tooltipForecolor, false, NULL, false);

									// Compute the line number
									sprintf(buffer, "%u\0", line->lineNumber);
									DrawText(bmp->hdc, buffer, (int)strlen(buffer), &lrc3, DT_VCENTER | DT_CENTER | DT_SINGLELINE | DT_NOPREFIX);
								}
						}
					}

					// If there are any highlight overlays after, display them
					if (sem->line_highlightAfter)
					{
						// Will appear after
						line = sem->line_highlightAfter;

						// Move down one line
						OffsetRect(&lrc3, 0, (lrc3.bottom - lrc3.top));

						// Colorize that entire section
						iBmp_fillRect(bmp, &lrc3, tooltipNwBackColor, tooltipNeBackColor, tooltipSwBackColor, tooltipSeBackColor, true, NULL, false);
						iBmp_frameRect(bmp, &lrc3, tooltipForecolor, tooltipForecolor, tooltipForecolor, tooltipForecolor, false, NULL, false);

						// Overlay the text
						if (line->sourceCode->_data && line->sourceCode_populatedLength != 0 && line->sourceCode_populatedLength >= sem->columnLeft)
						{
							SetTextColor(bmp->hdc, RGB(tooltipForecolor.red, tooltipForecolor.grn, tooltipForecolor.blu));
							DrawText(bmp->hdc, line->sourceCode->data_s8 + sem->columnLeft, line->sourceCode_populatedLength - sem->columnLeft, &lrc3, DT_VCENTER | DT_LEFT | DT_SINGLELINE | DT_NOPREFIX);

							// Add in the line numbers
							if (sem->showLineNumbers)
							{
								// Adjust for the line number area
								SetRect(&lrc3, 0, lrc3.top, lrc3.left, lrc3.bottom);

								// Colorize that entire section
								iBmp_fillRect(bmp, &lrc3, tooltipNwBackColor, tooltipNeBackColor, tooltipSwBackColor, tooltipSeBackColor, true, NULL, false);
								iBmp_frameRect(bmp, &lrc3, tooltipForecolor, tooltipForecolor, tooltipForecolor, tooltipForecolor, false, NULL, false);

								// Compute the line number
								sprintf(buffer, "%u\0", line->lineNumber);
								DrawText(bmp->hdc, buffer, (int)strlen(buffer), &lrc3, DT_VCENTER | DT_CENTER | DT_SINGLELINE | DT_NOPREFIX);
							}
						}
					}
				}


// s8 buffer[256];
// if (obj->parent && obj->parent->objType == _OBJ_TYPE_SUBFORM && iDatum_compare(&obj->parent->p.caption, cgcSourceCodeTitle, sizeof(cgcSourceCodeTitle) - 1) == 0)
// {
// 	sprintf(buffer, "c:\\temp\\ems\\%u.bmp\0", (u32)em);
// 	iBmp_saveToDisk(bmp, buffer);
// 	iBmp_saveToDisk(bmp, "c:\\temp\\em.bmp");
// }

			// Reset the font
			SelectObject(bmp->hdc, hfontOld);

//////////
// This is a nice appearance effect, but it is slow.
// If the background rendering algorithm was drawn, and the bitmap cached, it would be okay.
// 			// Apply a dappling
// 			iBmp_dapple(bmp, bmpDapple1, bmpDapple1Tmp, 215.0f, 10);
//////
		}

		// Indicate the object is now dirty
		iObj_setDirtyRender_ascent(obj, true);
		iObj_setDirtyPublish_ascent(obj, true);

		// Indicate how many pixels were rendered
		return(lnPixelsRendered);
	}




//////////
//
// Called to render the highlighted components at their indicated locations (for syntax highlighting)
//
//////
	void iSEM_render_highlightSelectedComps(SEM* sem, SComp* firstComp)
	{
		bool	llSetSelectedColor;
		SComp*	comp;


		// Make sure the environment is sane
		if (sem && firstComp)
		{
			// Set the starting values
			llSetSelectedColor	= false;
			comp				= firstComp;

			// Repeat through every component for this line
			while (comp)
			{
				//////////
				// Is anything selected?
				//////
					if (sem->selectMode != _SEM_SELECT_MODE_NONE)
					{
// if (sem->selectOrigin.column != sem->selectEnd.column)
// 	debug_break;
						// Are they selecting up or down
						if (sem->selectOrigin.lineNumber < sem->selectEnd.lineNumber)
						{
							// The selection began closer to the start of the file, and continued on toward the end
							if (comp->line->lineNumber >= sem->selectOrigin.lineNumber && comp->line->lineNumber <= sem->selectEnd.lineNumber)
							{
								// This line is within range, and may need to be displayed with selected coloring
								if (comp->line->lineNumber == sem->selectOrigin.lineNumber)
								{
									// It is on the line closer to the beginning of the file, so it must appear at or after the selection start
									if (sem->selectOrigin.column <= comp->start + comp->length)
										llSetSelectedColor = true;

								} else if (comp->line->lineNumber == sem->selectEnd.lineNumber) {
									// It is on the line closer to the end of the file
									if (comp->start <= sem->selectEnd.column)
										llSetSelectedColor = true;

								} else {
									// It's in the middle, always selected
									llSetSelectedColor = true;
								}
							}

						} else if (sem->selectOrigin.lineNumber > sem->selectEnd.lineNumber) {
							// The selection began closer to the end of a the file, and continued up to the top
							if (comp->line->lineNumber <= sem->selectOrigin.lineNumber && comp->line->lineNumber >= sem->selectEnd.lineNumber)
							{
								// This line should be displayed with selected coloring
								if (comp->line->lineNumber == sem->selectOrigin.lineNumber)
								{
									// It is on the line closer to the end of the file
									if (comp->start <= sem->selectOrigin.column)
										llSetSelectedColor = true;

								} else if (comp->line->lineNumber == sem->selectEnd.lineNumber) {
									// It is on the line closer to the beginning of the file
									if (comp->start + comp->length >= sem->selectEnd.column)
										llSetSelectedColor = true;

								} else {
									// It's in the middle, always selected
									llSetSelectedColor = true;
								}
							}

						} else if (sem->selectOrigin.lineNumber == sem->selectEnd.lineNumber && sem->selectOrigin.column <= sem->selectEnd.column) {
							// The selection began on a particular line closer to column 0, and continued on to something closer to the end
							if (comp->line->lineNumber == sem->selectOrigin.lineNumber)
							{
								// This line should be displayed with selected coloring
								if (iMath_between(comp->start,					sem->selectOrigin.column, sem->selectEnd.column) ||
									iMath_between(comp->start + comp->length,	sem->selectOrigin.column, sem->selectEnd.column) ||
									iMath_between(sem->selectOrigin.column,		comp->start, comp->start + comp->length) ||
									iMath_between(sem->selectEnd.column,			comp->start, comp->start + comp->length))
								{
									llSetSelectedColor = true;
								}
							}

						} else if (sem->selectOrigin.lineNumber == sem->selectEnd.lineNumber && sem->selectOrigin.column > sem->selectEnd.column) {
							// The selection began on a particular line closer to column 0, and continued on to something closer to the end
							if (comp->line->lineNumber == sem->selectOrigin.lineNumber)
							{
								// This line should be displayed with selected coloring
								if (iMath_between(comp->start,					sem->selectOrigin.column, sem->selectEnd.column) ||
									iMath_between(comp->start + comp->length,	sem->selectOrigin.column, sem->selectEnd.column) ||
									iMath_between(sem->selectOrigin.column,		comp->start, comp->start + comp->length) ||
									iMath_between(sem->selectEnd.column,			comp->start, comp->start + comp->length))
								{
									llSetSelectedColor = true;
								}
							}
						}
					}


				//////////
				// Set or reset the color
				//////
					if (llSetSelectedColor)
					{
						// Set the color
						comp->overrideSelectionBackColor = &selectedBackColor;
//////////
// Aug.16.2014 -- Removed.  I think I like having the syntax highlighting colors still visible when in selection mode
//						comp->overrideSelectionForeColor = &selectedForeColor;
//////
						comp->overrideSelectionForeColor = NULL;
						llSetSelectedColor = false;

					} else {
						// Reset the color
						comp->overrideSelectionBackColor = NULL;
						comp->overrideSelectionForeColor = NULL;
					}


				//////////
				// Move to next component
				//////
					comp = comp->ll.nextComp;
			}
		}
	}




//////////
//
// Called to verify the cursor is visible by adjusting sem->leftColumn
//
//////
	bool iSEM_verifyCursorIsVisible(SEM* sem, SObject* obj)
	{
		s32		lnI, lnUp, lnDn, lnNewLeftColumn, lnCols, lnRows, lnWidth, lnHeight, lnExtra;
		bool	llChanged;
		SLine*	lineUp;
		SLine*	lineDn;
		SFont*	font;
		RECT	lrc;


		logfunc(__FUNCTION__);
		llChanged = false;
		if (!sem->isHeavyProcessing)
		{
			//////////
			// Indicate initially that no changes were made that require a re-render
			//////
				font = iSEM_getRectAndFont(sem, obj, &lrc);


			//////////
			// Make sure our environment is sane
			//////
				llChanged = false;
				if (sem)
				{
					//////////
					// Compute our maximum rows and cols based on visible display area
					//////
// TODO:  There must be a more elegant way to do this.
						lnWidth		= (lrc.right - lrc.left) - ((sem->showLineNumbers) ? (7 * font->tm.tmAveCharWidth) : 0);
						lnHeight	= (lrc.bottom - lrc.top);
						lnExtra		= font->tm.tmMaxCharWidth - (font->tm.tmAveCharWidth * 2);			// Added to fix the bug mentioned below
						if (lnExtra < 0)
							lnExtra = 0;
						lnCols		= max((lnWidth  / (font->tm.tmAveCharWidth + lnExtra)),	2);			// There is some kind of bug in the font->tm.tmAveCharWidth which prevents this from always being able to be an exact calculation, so we back off 10 characters
						lnRows		= max((lnHeight / font->tm.tmHeight),					2);			// And for the height, we back off one

						// Adjust to 90% of extents
						lnCols		= lnCols - (lnCols / 10);
						lnRows		= lnRows - (lnRows / 10);


					//////////
					// Make sure we're not beyond the end of the line when we're not allowed to
					//////
						if (!sem->allowMoveBeyondEndOfLine && sem->columnEdit > sem->line_cursor->sourceCode_populatedLength)
							sem->columnEdit = sem->line_cursor->sourceCode_populatedLength;


					//////////
					// Make sure we're not before it to the left
					//////
						if (sem->columnEdit < sem->columnLeft)
						{
							sem->columnLeft	= sem->columnEdit;
							llChanged		= true;
						}


					//////////
					// Make sure we're not beyond it to the right1
					//////
						lnNewLeftColumn = sem->columnEdit - lnCols;
						if (sem->columnLeft - lnNewLeftColumn < 0)
						{
							sem->columnLeft	= lnNewLeftColumn;
							llChanged		= true;
						}


					//////////
					// Make sure we're on-screen vertically
					//////
						if (!sem->line_cursor)
						{
							// No cursor line has been set
							if (!sem->line_top)
							{
								// Set the top line
								sem->line_top		= sem->firstLine;
								sem->line_cursor	= sem->firstLine;

							} else {
								// Position it at the top line
								sem->line_cursor = sem->line_top;
							}
							llChanged = true;

						} else {
							// Find out how many rows away the cursor line is from the top line by scanning up and down
							lineUp	= sem->line_top;
							lineDn	= sem->line_top;
							for (lnUp = 0, lnDn = 0; (lineUp || lineDn) && lineUp != sem->line_cursor && lineDn != sem->line_cursor; )
							{
								//////////
								// Can we go up?
								//////
									if (lineUp)
									{
										lineUp = (SLine*)lineUp->ll.prev;
										++lnUp;
									}


								//////////
								// Can we go down?
								//////
									if (lineDn)
									{
										lineDn = (SLine*)lineDn->ll.next;
										++lnDn;
									}
							}
							// When we get here, either lineUp or lineDn found the cursor line

							if (lineUp == sem->line_cursor)
							{
								// We went up, so set the top line to this location
								sem->line_top = sem->line_cursor;
								llChanged = true;

							} else if (lineDn == sem->line_cursor) {
								// We went down to find it
								if (lnDn >= lnRows)
								{
									// And the position is too far down
									for (lnI = 0; lnI <= lnDn - lnRows; lnI++)
										sem->line_top = (SLine*)sem->line_top->ll.next;

									// Indicate the change
									llChanged = true;
								}

							} else {
								// If we get here, it wasn't found
								sem->line_top = sem->line_cursor;
								llChanged = true;
							}
						}
				}
		}

		// Signal the arrival on this line
		iExtraInfo_arrival(sem, sem->line_cursor);

		// If something has changed, we need to re-render
		iObj_setDirtyRender_ascent(obj, true);
		iSEM_selectUpdateExtents(sem);

		// Indicate our status
		return(llChanged);
	}




//////////
//
// Called to render (or re-render) the content as simple HTML.
//
// Supported commands:
//				<html>		-- Indicates html block,	bgcolor, color, width, height, name [implied font name], size
//				<hr>		-- Horizontal line,			bgcolor, height
//				<br>		-- Break
//				<font>		-- Change font,				bgcolor, color, name, size
//				<tt>		-- Typewriter type (fixed point)
//				<table>		-- Table definition,	bgcolor, color, align, valign, width
//				<tr>		-- Table row,			bgcolor, color, align, valign, height
//				<td>		-- Table column,		bgcolor, color, align, valign, colspan, width, height
//				<b>			-- Bold
//				<i>			-- Italics
//				<u>			-- Underline
//				<wNnn>		-- Specify a hard width, like <w1024>
//				<hNnn>		-- Specify a hard height, like <h768>
//				<xNnn>		-- Move to hard X pixel, like <x50>
//				<yNnn>		-- Move to hard Y pixel, like <y20>
//				&..;		-- nbsp, quo, lt, gt, Nn for ASCII characters
//
// Note:  Other attributes and tags are ignored.
//
//////
	// Returns number of pixels rendered
	u32 iSEM_renderAs_simpleHtml(SEM* sem, SObject* obj, bool tlRenderCursorline)
	{
		bool		llZoomed, llNumeric, llAlpha, llFontChange, llFallThru;
		u32			lnPixelsRendered;
		s32			lnX, lnY, lnLastHeight, lnWidth, lnHeight, lnScrollX, lnScrollY, lnStartHeight, lnStartWidth;
		s32			lnFontSize, lnFontWeight, lnFontItalics, lnFontUnderline, lnFontStack, lnFontsCreated;
		f64			lfZoom;
		SBgra		color, bgcolor, defaultBackColor, defaultForeColor;
		RECT		rc, lrc, lrc2;
		u8*			lcFontName;
		SBitmap*	bmp;
		SDatum*		fontName;
		SComp*		comp;
		SComp*		comp2;
		SComp*		compNext;
		SComp*		compNext2;
		SFont*		font;
		SFont*		fontStack[64];		// Up to 64 font changes on the stack
		SFont*		fontsCreated[128];	// Fonts created during this process
		SLine*		line;


		// Make sure the environment is sane
		lnPixelsRendered = 0;
		if (sem && obj && obj->bmp)
		{
			// Fill the rectangle with an empty background
			font = iSEM_getRectAndFont(sem, obj, &rc);
			iSEM_getColors(sem, obj, defaultBackColor, defaultForeColor);
			iBmp_fillRect(obj->bmp, &rc, defaultBackColor, defaultBackColor, defaultBackColor, defaultBackColor, false, NULL, false);

			// Draw any content
			if (sem->firstLine && sem->lastLine && obj)
			{
				//////////
				// We always re-parse when this function it's called
				//////
					for (line = sem->firstLine; line; line = line->ll.nextLine)
					{
						// Recompile everything and parse out tags
						iEngine_parse_sourceCode_line(line, cgcSEMHtmlKeywords);
						iComps_fixup_semHtmlGroupings(line);
					}


				//////////
				// Grab the render bitmap
				//////
					lnWidth  = obj->bmp->bi.biWidth;
					lnHeight = obj->bmp->bi.biHeight;

					// Apply any zoom
					llZoomed = iiSEM_renderAs_simpleHtml__applyZoom(obj, &lnWidth, &lnHeight);

					// If it's the same size as the bitmap, use it, otherwise build a temporary one
					if (!iiSEM_renderAs_simpleHtml__createBmp(&bmp, obj->bmp, lnWidth, lnHeight))
						return(-1);


				//////////
				// Default font
				//////
					lnFontSize		= 12;
					lnFontWeight	= FW_NORMAL;
					lnFontItalics	= 0;
					lnFontUnderline	= 0;
					lcFontName		= (u8*)"Ubuntu";
					font			= iSEM_renderAs_simpleHtml__addFont(&fontsCreated[0], &lnFontsCreated, lcFontName, lnFontSize, lnFontWeight, lnFontItalics, lnFontUnderline);


				//////////
				// Font stack
				//////
					memset(fontStack, 0, sizeof(fontStack));
					lnFontStack = 0;
					iiSEM_renderAs_simpleHtml__pushFontStack(&fontStack[0], font, &lnFontStack, sizeof(fontStack) / sizeof(fontStack[0]));


				//////////
				// Render through each line
				//////
					lnLastHeight	= 0;
					fontName		= NULL;
					for (line = sem->line_top, lnX = 0, lnY = 0; line; line = line->ll.nextLine)
					{
						// Iterate through each line
						lnStartHeight	= lnHeight;
						lnStartWidth	= lnWidth;
						llFontChange	= false;
						for (comp = line->compilerInfo->firstComp; comp; comp = comp->ll.nextComp)
						{
							// Is it an html tag?
							comp2 = comp->firstCombined;
							switch (comp->iCode)
							{
								case _ICODE_SEM_HTML_HTML:
									if (comp->iCat == _ICAT_SEM_HTML_ATTRIBUTES)
									{
										// Has attributes
										for (llFontChange = false; comp; comp = comp->ll.nextComp)
										{
											// Make sure the pattern needed exists
											compNext	= iComps_getNth(comp);
											compNext2	= iComps_getNth(compNext);
											llNumeric	= (compNext && compNext->iCode == _ICODE_EQUAL_SIGN && compNext2 && compNext2->iCode == _ICODE_NUMERIC);
											llAlpha		= (compNext && compNext->iCode == _ICODE_EQUAL_SIGN && compNext2 && (compNext2->iCode == _ICODE_DOUBLE_QUOTED_TEXT || compNext2->iCode == _ICODE_SINGLE_QUOTED_TEXT));

											// html only allows certain attributes
											llFallThru = false;
											switch (comp->iCode)
											{
												case _ICODE_SEM_HTML_BGCOLOR:
													iiSEM_renderAs_simpleHtml__getColor(compNext2, llNumeric, llAlpha, &bgcolor);
													break;

												case _ICODE_SEM_HTML_COLOR:
													iiSEM_renderAs_simpleHtml__getColor(compNext2, llNumeric, llAlpha, &color);
													break;

												case _ICODE_SEM_HTML_HEIGHT:
													lnHeight = iComps_getAs_s32(comp);
													break;

												case _ICODE_SEM_HTML_WIDTH:
													lnWidth = iComps_getAs_s32(comp);
													break;

												case _ICODE_SEM_HTML_NAME:
// TODO:  working here ... not quite sure how I want to handle this:
													if ((fontName = iComps_getAs_datum(comp, fontName)))
														lcFontName	= fontName->data_u8;
													break;

												case _ICODE_SEM_HTML_SIZE:
													lnFontSize = iComps_getAs_s32(comp);
													break;

												default:
													llFallThru = true;
													break;
											}
											llFontChange |= (!llFallThru);
										}

									} else {
										// Ignore this tag
										// No code
									}
									break;

								case _ICODE_SEM_HTML_HR:
									// Moving to the next row, drawing a horizontal line, and then moving to the next row
									break;
								case _ICODE_SEM_HTML_BR:
									// Moving to the next row
									lnY += lnLastHeight;
									lnX = 0;
									break;
								case _ICODE_SEM_HTML_FONT:
									// Setting font parameters
									break;
								case _ICODE_SEM_HTML_TT:
									// Switching to a monochrome font in the current size
									break;

//								case _ICODE_SEM_HTML_TABLE:
//								case _ICODE_SEM_HTML_TR:
//								case _ICODE_SEM_HTML_TD:
//									// Need to spawn off a secondary processor for this one, to determine its size in the first step, to render in the second step, and then redraw here in the third step
//									break;

								case _ICODE_SEM_HTML_B:
									// Turning on bold
									break;
								case _ICODE_SEM_HTML_I:
									// Turning on italic
									break;
								case _ICODE_SEM_HTML_U:
									// Turning on underline
									break;
								case _ICODE_SEM_HTML_W:
									// Setting a hard new width for the HTML render
									break;
								case _ICODE_SEM_HTML_H:
									// Setting a hard new height for the HTML render
									break;
								case _ICODE_SEM_HTML_X:
									// Repositioning to a hard X coordinate
									break;
								case _ICODE_SEM_HTML_Y:
									// Repositioning to a hard Y coordinate
									break;
								case _ICODE_SEM_HTML_BGCOLOR:
									// Setting a hard background color
									break;
								case _ICODE_SEM_HTML_COLOR:
									// Setting a hard foreground color
									break;
								case _ICODE_SEM_HTML_ALIGN:
									// Setting a hard horizontal alignment mode
									break;
								case _ICODE_SEM_HTML_VALIGN:
									// Setting a hard vertical alignment mode
									break;
								case _ICODE_SEM_HTML_HEIGHT:
									// Setting a hard new height for the HTML render
									break;
								case _ICODE_SEM_HTML_WIDTH:
									// Setting a hard new width for the HTML render
									break;
								case _ICODE_SEM_HTML_NAME:
									// Setting a hard new font name
									break;
								case _ICODE_SEM_HTML_SIZE:
									// Setting a hard new font size
									break;

								default:
									// It's something to render
									SelectObject(bmp->hdc, font->hfont);
									SetTextColor(bmp->hdc, RGB(color.red, color.grn, color.blu));
									SetBkColor(bmp->hdc, RGB(bgcolor.red, bgcolor.grn, bgcolor.blu));
									SetBkMode(bmp->hdc, OPAQUE);

									// Calculate rectangle
									SetRect(&lrc, 0, 0, 0, 0);
									DrawText(bmp->hdc, comp->line->sourceCode->data + comp->start, comp->length, &lrc, DT_LEFT | DT_CALCRECT);

									// Render
									SetRect(&lrc2, lnX, lnY, lnX + lrc.right - lrc.left, lnY + lrc.bottom - lrc.top);
									DrawText(bmp->hdc, comp->line->sourceCode->data + comp->start, comp->length, &lrc2, DT_LEFT);

									// Adjust the position by the size
									lnX				+= lrc.right - lrc.left;
									lnLastHeight	= lrc.bottom - lrc.top;
									break;
							}

							// Adjust the width and height if specified to do so
							if (lnHeight != lnStartHeight && lnWidth != lnStartWidth)
							{
								// Adjust to the new height
								llZoomed = iiSEM_renderAs_simpleHtml__applyZoom(obj, &lnWidth, &lnHeight);
								if (!iiSEM_renderAs_simpleHtml__createBmp(&bmp, obj->bmp, lnWidth, lnHeight))
								{
									// Memory error
									lnPixelsRendered = _ERROR_OUT_OF_MEMORY;
									goto error_exit;
								}

								// Reset our variables
								lnStartHeight	= lnHeight;
								lnStartWidth	= lnWidth;
							}

							// Get the new default font if we need
							if (llFontChange)
							{
								// Create the font
								font = iFont_create(lcFontName, lnFontSize, lnFontWeight, lnFontItalics, lnFontUnderline);

								// Add it to the stack
								if (lnFontStack == 1)
									fontStack[0] = font;	// Replace the first/main entry created above

								// Indicate our font has not yet again changed
								llFontChange = false;
							}
						}

						// Are we done?
						if (line == sem->lastLine)
							break;
					}

			}
		}

error_exit:

		// Indicate how many pixels were rendered
		return(lnPixelsRendered);
	}

	// Upon entry, comp is either numeric or alpha
	void iiSEM_renderAs_simpleHtml__getColor(SComp* comp, bool tlNumeric, bool tlAlpha, SBgra* color)
	{
		u8 lnBlu, lnGrn, lnRed;


		// Extract as indicated
		if (tlAlpha)
		{
			// It's color=".."
			if (comp->line->sourceCode->data_s8[1] == '#')
			{
				// It's #color
				if (comp->length == 9)
				{
					// It's "#rrggbb"
					if (iMath_getAs_rrggbb(comp->line->sourceCode->data_u8 + 2, &lnBlu, &lnGrn, &lnRed))
						color->color = bgr(lnBlu, lnGrn, lnRed);

				} else if (comp->length == 6) {
					// It's "#rgb"
					if (iMath_getAs_rgb(comp->line->sourceCode->data_u8 + 2, &lnBlu, &lnGrn, &lnRed))
						color->color = bgr(lnBlu, lnGrn, lnRed);
				}
				//else We don't know what it is, so ignore it

			} else {
				// It's color
				if (comp->length == 8)
				{
					// It's "rrggbb"
					if (iMath_getAs_rrggbb(comp->line->sourceCode->data_u8 + 1, &lnBlu, &lnGrn, &lnRed))
						color->color = bgr(lnBlu, lnGrn, lnRed);

				} else if (comp->length == 5) {
					// It's "rgb"
					if (iMath_getAs_rgb(comp->line->sourceCode->data_u8 + 1, &lnBlu, &lnGrn, &lnRed))
						color->color = bgr(lnBlu, lnGrn, lnRed);
				}
			}

		} else if (tlNumeric) {
			// It's color=Nnn
			color->color = (u32)iComps_getAs_s64(comp);
		}
	}




//////////
//
// Applies a zoom factor to the indicated values
//
//////
	bool iiSEM_renderAs_simpleHtml__applyZoom(SObject* obj, s32* tnWidth, s32* tnHeight)
	{
		bool		llZoomed;
		f64			lfZoom;
		SVariable*	varZoom;


		// Extract the zoom member (if present)
		varZoom = iObjProp_get(obj, _INDEX_HTML_ZOOM);
		if (varZoom && between((lfZoom = iiVariable_getAs_f64(varZoom)), _HTML_ZOOM_MIN, _HTML_ZOOM_MAX) && iiVariable_getAs_f64(varZoom) != 1.0)
		{
			// Force it into range
			llZoomed	= true;
			lfZoom		= min(max(lfZoom, _HTML_ZOOM_MIN), _HTML_ZOOM_MAX);

			// Determine the bitmap size we can render
			*tnWidth	= (s32)((f64)*tnWidth  / lfZoom);
			*tnHeight	= (s32)((f64)*tnHeight / lfZoom);

		} else {
			// Not zoomed
			llZoomed	= false;
		}

		// Indicate if it's zoomed
		return(llZoomed);
	}




//////////
//
// Creates the bitmap based on the size
//
//////
	bool iiSEM_renderAs_simpleHtml__createBmp(SBitmap** bmpOld, SBitmap* bmpObj, s32 tnWidth, s32 tnHeight)
	{
		SBitmap* bmp;


		// If there's already a bitmap and the sizes are different
		bmp = *bmpOld;
		if (bmp && (bmp != bmpObj) && (bmp->bi.biWidth != tnWidth || bmp->bi.biHeight != tnHeight))
			iBmp_delete(bmpOld, true, true);

		// Create the bitmap
		if (bmpObj->bi.biWidth == tnWidth && bmpObj->bi.biHeight == tnHeight)
		{
			// Use the default bitmap
			bmp = bmpObj;

		} else {
			// Create a temporary one to render into
			if ((bmp = iBmp_allocate()))
				iBmp_createBySize(bmp, tnWidth, tnHeight, bmpObj->bi.biBitCount);
			
		}

		// Make sure we have a valid bitmap
		if (!bmp || bmp->bi.biWidth != tnWidth || bmp->bi.biHeight)
		{
			// Delete the bitmap (if it was partially created)
			if (bmp != bmpObj)
				iBmp_delete(&bmp, true, true);

			// Indicate failure
			*bmpOld = NULL;
			return(false);

		} else {
			// Indicate success
			*bmpOld = bmp;
			return(true);
		}
	}




//////////
//
// Create a font and add it to the list of fonts we've created for this render
//
//////
	SFont* iSEM_renderAs_simpleHtml__addFont(SFont* fontsCreated[], s32* tnFontsCreated, u8* tcFontName, s32 tnFontSize, s32 tnFontWeight, s32 tnFontItalics, s32 tnFontUnderline)
	{
		s32		lnI;
		SFont*	font;


		// Search to see if the font already exists
		for (lnI = 0; lnI < *tnFontsCreated; lnI++)
		{
			// Grab the font as a pointer
			font = fontsCreated[lnI];

			// Is this a duplicate?
			if (iDatum_compare(&font->name, tcFontName, -1) && font->_size == tnFontSize && font->_weight == tnFontWeight && font->_italics == tnFontItalics && font->_underline == tnFontUnderline)
				return(font);		// This is a match
		}

		// Create the font
		font = iFont_create(tcFontName, tnFontSize, tnFontWeight, tnFontItalics, tnFontUnderline);
		if (font)
		{
			// Add it to the list of fonts we've used
			fontsCreated[*tnFontsCreated] = font;
			++*tnFontsCreated;
		}

		// Indicate success or failure
		return(font);
	}




//////////
//
// Push the font onto stack
//
//////
	void iiSEM_renderAs_simpleHtml__pushFontStack(SFont* fontStack[], SFont* font, s32* tnFontStack, s32 tnFontStackSize)
	{
		// Are we still within the valid space?
		if (*tnFontStack < tnFontStackSize)
			fontStack[*tnFontStack] = font;		// Push

		// Point to the next slot
		++*tnFontStack;							// Note:  This stack may grow well beyond its physical size.  In such a case it will use the maximum entry repeatedly.
	}




//////////
//
// Pop the font onto stack
//
//////
	SFont* iiSEM_renderAs_simpleHtml__popFontStack(SFont* fontStack[], SFont* font, s32* tnFontStack, s32 tnFontStackSize)
	{
		// Decrease the stack pointer
		if (tnFontStack > 0)
			--*tnFontStack;

		// Grab the font (or the maximum font if we're too deep
		return(fontStack[min(*tnFontStack, tnFontStackSize - 1)]);
	}




//////////
//
// Called to process the ASCII character into the input buffer.
//
//////
	bool iSEM_keystroke(SEM* sem, SObject* obj, u8 asciiChar)
	{
		bool	llChanged;


		logfunc(__FUNCTION__);
		//////////
		// Indicate initially that no changes were made that require a re-render
		//////
			llChanged = false;


		// Make sure our environment is sane
// TODO:  Added the extra test on ecm->column because of a bug when scrolling... will fix. :-)
		if (sem && !sem->isReadOnly)
		{
			//////////
			// Are we on a line?
			//////
				if (!sem->firstLine)
					iSEM_appendLine(sem, NULL, 0, true);		// Append a blank line to receive this keystroke


			//////////
			// Is a line currently selected?
			//////
				if (!sem->line_cursor)
					iSEM_navigateToTopLine(sem, obj);


			//////////
			// Are we in insert mode?
			//////
				if (!sem->isOverwrite)
				{
					// We are inserting
					if (sem->selectMode != _SEM_SELECT_MODE_NONE)
					{
						// There is a selection, which means we are replacing everything that's selected with this new keystroke
// TODO:  write this code

					} else {
						// We are just overwriting whatever's there
						llChanged = iSEMLine_characterInsert(sem, asciiChar);
					}

				} else {
					// We are overwriting
					if (sem->selectMode != _SEM_SELECT_MODE_NONE)
					{
						// There is a selection, which means we are replacing everything that's selected with this new keystroke
// TODO:  write this code

					} else {
						// We are just overwriting whatever's there
						llChanged = iSEMLine_characterOverwrite(sem, asciiChar);
					}
				}
		}

		// If we updated something, mark the object dirty
		if (llChanged)
		{
			// Indicate the object needs re-rendered
			iObj_setDirtyRender_ascent(obj, true);

			// Reprocess the source code on the line
			iEngine_parse_sourceCode_line(sem->line_cursor);

			// Verify our cursor is visible
			iSEM_verifyCursorIsVisible(sem, obj);
		}

		// Indicate our status
		return(llChanged);
	}





//////////
//
// Called to scroll rows (deltaY) or columns (deltaX) or both.
//
//////
	bool iSEM_scroll(SEM* sem, SObject* obj, s32 deltaY, s32 deltaX)
	{
		s32 lnI;


		logfunc(__FUNCTION__);
		//////////
		// Make sure we're valid
		//////
			if (sem && sem->line_cursor && sem->line_cursor->sourceCode)
			{
				//////////
				// Scroll by count
				//////
					if (deltaY != 0)
					{
						if (deltaY > 0)
						{
							// Going forward
							for (lnI = 0; sem->line_cursor->ll.next && lnI != deltaY; lnI++)
							{
								sem->line_top		= (SLine*)sem->line_top->ll.next;
								sem->line_cursor	= (SLine*)sem->line_cursor->ll.next;
							}

						} else {
							// Going backward
							for (lnI = 0; sem->line_top->ll.prev && lnI != deltaY; lnI--)
							{
								sem->line_top		= (SLine*)sem->line_top->ll.prev;
								sem->line_cursor	= (SLine*)sem->line_cursor->ll.prev;
							}
						}
					}


				//////////
				// Move columns
				//////
					if (deltaX != 0)
					{
						if (deltaX < 0)
						{
							// Moving left
							sem->columnEdit		= max(sem->columnEdit     + deltaX, 0);
							sem->columnLeft	= max(sem->columnLeft + deltaX, 0);

						} else {
							// Moving right
							sem->columnEdit		+= deltaX;
							sem->columnLeft	+= deltaX;
						}
					}


				//////////
				// Verify we're visible
				//////
					iSEM_verifyCursorIsVisible(sem, obj);


				// Indicate success
				return(true);
			}


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to navigate rows (deltaY) or columns (deltaX) or both.
//
//////
	bool iSEM_navigate(SEM* sem, SObject* obj, s32 deltaY, s32 deltaX)
	{
		s32			lnI, lnTop, lnBottom;
		bool		llResetTopLine;
		SFont*		font;
		SLine*		line;
		SLine*		lineRunner;
		SLine*		lineTest;
		RECT		lrc;


		logfunc(__FUNCTION__);
		//////////
		// Grab the rectangle we're working in
		//////
			font = iSEM_getRectAndFont(sem, obj, &lrc);


		//////////
		// Make sure we're valid
		//////
			if (sem && sem->line_cursor && sem->line_cursor->sourceCode)
			{
				//////////
				// Grab the line and form
				//////
					line = sem->line_cursor;


				//////////
				// Navigate by lines
				//////
					if (deltaY != 0)
					{
						if (deltaY > 0)
						{
							// Going forward
							for (lnI = 0; line->ll.next && lnI != deltaY; lnI++)
								line = (SLine*)line->ll.next;

							// We need to scan forward from ecTopLine to see if we'd be off screen.
							// If so, we drag ecTopLine forward until we reach the visible portion
							lnTop		= lrc.top;
							lnBottom	= lrc.bottom - font->tm.tmHeight;
							lineRunner	= sem->line_top;
							while (sem->line_top->ll.next && lineRunner != line)
							{
								//////////
								// Are we still on screen?
								//////
									if (lnTop > lnBottom)
									{
										// We're off screen, so we're dragging the top forward
										sem->line_top = (SLine*)sem->line_top->ll.next;

									} else {
										// Still on the same page
										lnTop += font->tm.tmHeight;
									}


								//////////
								// Move to next line
								//////
									lineRunner = (SLine*)lineRunner->ll.next;
							}

						} else {
							// Going backward
							llResetTopLine = false;
							for (lnI = 0; line->ll.prev && lnI != deltaY; lnI--)
							{
								// Are we dragging the top line with us yet?
								if (sem->line_top == line)
									llResetTopLine = true;

								// Move back one line
								line = (SLine*)line->ll.prev;
							}

							if (llResetTopLine)
								sem->line_top = line;
						}

					//////////
					// Update the pointers
					//////
						sem->line_cursor = line;
				}


				//////////
				// Move columns
				//////
					if (deltaX != 0)
					{
						if (deltaX < 0)
						{
							// Moving left
							if (sem->columnEdit == 0)
							{
								// Need to move to the end of the line above
								lineTest = sem->line_cursor;
								iSEM_navigate(sem, obj, -1, 0);
								if (sem->line_cursor != lineTest)
									return(iSEM_navigate(sem, obj, 0, sem->line_cursor->sourceCode_populatedLength));

							} else {
								// Just moving over
								sem->columnEdit = max(sem->columnEdit + deltaX, 0);
							}

						} else {
							// Moving right
							if (sem->columnEdit < sem->line_cursor->sourceCode_populatedLength || sem->allowMoveBeyondEndOfLine)
							{
								// We allow them to move out as far right as they want
								sem->columnEdit += deltaX;

							} else {
								// Once they get to the end, move to the start of the next line
								return(iSEM_navigate(sem, obj, 1, -sem->columnEdit));
							}
						}
					}


				//////////
				// Verify we're visible
				//////
					iSEM_verifyCursorIsVisible(sem, obj);


				// Indicate success
				return(true);
			}


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to navigate pages (deltaY) forward or backward)
//
//////
	bool iSEM_navigatePages(SEM* sem, SObject* obj, s32 deltaY)
	{
		s32		lnI;
		bool	llMoveForward;
		SFont*	font;
		RECT	lrc;
		SLine*	line;


		logfunc(__FUNCTION__);
		//////////
		// Grab the rectangle we're working in
		//////
			font = iSEM_getRectAndFont(sem, obj, &lrc);


		//////////
		// Make sure we're valid
		//////
			if (sem && sem->line_cursor && sem->line_cursor->sourceCode && deltaY != 0)
			{
				//////////
				// Determine how many visible lines there are and move that far
				//////
					deltaY = deltaY * ((lrc.bottom - lrc.top) / font->tm.tmHeight);
					if (deltaY > 0)
					{
						// See how many lines there are left on the page
						llMoveForward = true;
						if (sem->line_cursor != sem->lastLine)
						{
							// We're not on the last line, so we first see if we can navigate a partial page down without moving the top line
							// before we reach the end of the file
							line = sem->line_cursor;
							for (lnI = 0; line->ll.next && lnI != deltaY; lnI++)
							{
								// Move the cursor line to the next line
								line = (SLine*)line->ll.next;
							}

							// If we've reached the end before reaching our delta...then...
							if (lnI != deltaY)
							{
								// We can do the partial page
								sem->line_cursor	= line;
								llMoveForward		= false;
							}
						}

						// Going forward
						if (llMoveForward)
						{
							if (!sem->line_cursor->ll.next && sem->line_cursor != sem->line_top)
							{
								// We're already at the bottom, so just move down a line
								sem->line_top = (SLine*)sem->line_top->ll.next;

							} else {
								// Scroll the whole page
								for (lnI = 0; sem->line_cursor->ll.next && lnI != deltaY; lnI++)
								{
									// Move the top line to the next line
									sem->line_top		= (SLine*)sem->line_top->ll.next;
									sem->line_cursor	= (SLine*)sem->line_cursor->ll.next;
								}
							}
						}

					} else {
						// Going backward
						for (lnI = 0; sem->line_cursor->ll.prev && lnI != deltaY; lnI--)
						{
							// Move the top line up (if we can)
							if (sem->line_top->ll.prev)
								sem->line_top	= (SLine*)sem->line_top->ll.prev;

							// Move the cursor line up
							sem->line_cursor	= (SLine*)sem->line_cursor->ll.prev;
						}

					}


				//////////
				// Verify we're visible
				//////
					iSEM_verifyCursorIsVisible(sem, obj);


				// Indicate success
				return(true);
			}


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to clear the entire line.
//
//////
	bool iSEM_clearLine(SEM* sem, SObject* obj)
	{
		logfunc(__FUNCTION__);
		if (sem && !sem->isReadOnly && sem->line_cursor && obj)
		{
			// Clear off everything on the line
			sem->line_cursor->sourceCode_populatedLength = 0;

			// Indicate success
			return(true);
		}

		// Indicate failure
		return(false);
	}




//////////
//
// Called to clear from where we are to the end of the line
//
//////
	bool iSEM_clearToEndOfLine(SEM* sem, SObject* obj)
	{
		logfunc(__FUNCTION__);
		if (sem && !sem->isReadOnly && sem->line_cursor && obj)
		{
			// Clear off everything on the line
			if (sem->line_cursor->sourceCode_populatedLength > sem->columnEdit)
				sem->line_cursor->sourceCode_populatedLength = sem->columnEdit;

			// Indicate success
			return(true);
		}

		// Indicate failure
		return(false);
	}




//////////
//
// Called to clear from one character left of where we are to the beginning of the line
//
//////
	bool iSEM_clearToBeginningOfLine(SEM* sem, SObject* obj)
	{
		s32 lnI;


		logfunc(__FUNCTION__);
		if (sem && !sem->isReadOnly && sem->line_cursor && obj)
		{
			for (lnI = 0; lnI < sem->columnEdit && lnI < sem->line_cursor->sourceCode_populatedLength; lnI++)
			{
				// If it's not already a whitespace, replace it
				if (!(sem->line_cursor->sourceCode->data_s8[lnI] == 32 || sem->line_cursor->sourceCode->data_s8[lnI] == 9))
					sem->line_cursor->sourceCode->data_s8[lnI] = 32;
			}
		}

		// Indicate failure
		return(false);
	}




//////////
//
// Called to toggle insert mode
//
//////
	bool iSEM_toggleInsert(SEM* sem, SObject* obj)
	{
		logfunc(__FUNCTION__);
		if (sem)
		{
			// Toggle the flag
			sem->isOverwrite = !sem->isOverwrite;

			// Something has changed, we need to re-render
			iObj_setDirtyRender_ascent(obj, true);

			// Toggling insert changes the shape of the cursor, so we always redraw
			return(true);
		}

		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called when the users press TAB
//
//////
	bool iSEM_tabIn(SEM* sem, SObject* obj)
	{
		logfunc(__FUNCTION__);
		return(false);
	}




//////////
//
// Called when the users presses SHIFT+TAB
//
//////
	bool iSEM_tabOut(SEM* sem, SObject* obj)
	{
		logfunc(__FUNCTION__);
		return(false);
	}




//////////
//
//
//
//////
	bool iSEM_returnKey(SEM* sem, SObject* obj)
	{
		logfunc(__FUNCTION__);
		// Make sure the environment is sane
		if (sem && !sem->isReadOnly && sem->line_cursor && obj)
		{
			// If we're in insert mode, we split the line
			if (!sem->isOverwrite)
			{
				// Insert mode
				iSEM_insertLine(sem, NULL, 0, sem->line_cursor, true, true);	// Append a new line after the cursor line

			} else {
				// Overwrite mode
				if (!sem->line_cursor->ll.next)
					iSEM_appendLine(sem, NULL, 0, true);		// Append a new line at the end
			}

			// Move to the new line, and to the start of that line
			iSEM_navigate(sem, obj, 1, -sem->columnEdit);

			// Indicate success
			return(true);
		}


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to select everything
//
//////
	bool iSEM_selectAll(SEM* sem, SObject* obj)
	{
		logfunc(__FUNCTION__);

		return(false);
	}




//////////
//
// Called to cut to the clipboard
//
//////
	bool iSEM_cut(SEM* sem, SObject* obj)
	{
		logfunc(__FUNCTION__);
		return(false);
	}




//////////
//
// Called to copy to the clipboard
//
//////
	bool iSEM_copy(SEM* sem, SObject* obj)
	{
		logfunc(__FUNCTION__);
		return(false);
	}




//////////
//
// Called to paste from the clipboard
//
//////
	bool iSEM_paste(SEM* sem, SObject* obj)
	{
		logfunc(__FUNCTION__);
		return(false);
	}




//////////
//
// Called to navigate one word left
//
//////
	bool iSEM_navigateWordLeft(SEM* sem, SObject* obj, bool tlVerifyCursorIsVisible)
	{
		SLine* line;


		logfunc(__FUNCTION__);
		//////////
		// Make sure we're valid
		//////
			if (sem && sem->line_cursor && sem->line_cursor->sourceCode)
			{
				//////////
				// Grab the line and form
				//////
					line = sem->line_cursor;


				//////////
				// Iterate until we find a space
				//////
					if (sem->columnEdit == 0 || line->sourceCode_populatedLength == 0)
					{
						// We have to go to the previous line (if we can)
						if (sem->firstLine != line)
						{
							// Go up one line
							iSEM_navigate(sem, obj, -1, 0);

							// Go to the end of this line
							iSEM_navigate(sem, obj, 0, sem->line_cursor->sourceCode_populatedLength);

							// Continue looking word left on this line
							return(iSEM_navigateWordLeft(sem, obj, true));
						}

					} else if (line->sourceCode_populatedLength < sem->columnEdit) {
						// We're beyond end of line, move to the end of line
						iSEM_navigate(sem, obj, 0, sem->line_cursor->sourceCode_populatedLength - sem->columnEdit);

						// Then continue looking word left on this line
						return(iSEM_navigateWordLeft(sem, obj, true));

					} else {
						//////////
						// We're somewhere on the line, move one column left first
						//////
							--sem->columnEdit;


						//////////
						// If we're on a whitespace character, scan left until we reach a non-whitespace character
						//////
							// When we get to the first non-whitespace, we break
							for ( ; sem->columnEdit > 0 && iiSEM_isBreakingCharacter(sem, line, 0); )
								--sem->columnEdit;


						//////////
						// If we're not at the beginning of the line, then we look for the first whitespace character
						//////
							if (sem->columnEdit != 0)
							{
								// Search left for the first whitespace or comma
								for ( ; sem->columnEdit > 0; sem->columnEdit--)
								{
									// Did we find a whitespace to our left?
									if (iiSEM_isBreakingCharacter(sem, line, -1))
										break;	// Yes
								}
							}
					}


				//////////
				// Verify we're visible
				//////
					if (tlVerifyCursorIsVisible)
						iSEM_verifyCursorIsVisible(sem, obj);


				// Indicate success
				return(true);
			}


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to navigate one word right
//
//////
	bool iSEM_navigateWordRight(SEM* sem, SObject* obj, bool tlVerifyCursorIsVisible)
	{
		SLine* line;


		logfunc(__FUNCTION__);
		//////////
		// Make sure we're valid
		//////
			if (sem && sem->line_cursor && sem->line_cursor->sourceCode)
			{
				//////////
				// Grab the line and form
				//////
					line = sem->line_cursor;


				//////////
				// Iterate until we find a space
				//////
					if (sem->columnEdit >= line->sourceCode_populatedLength)
					{
						// We have to go to the next line (if we can)
						if (sem->lastLine != line)
						{
							// Go down one line
							iSEM_navigate(sem, obj, 1, 0);

							// Go to the start of the line
							if (sem->columnEdit > 0)
								iSEM_navigate(sem, obj, 0, -sem->columnEdit);

							// Continue looking word left on this line
							return(iSEM_navigateWordRight(sem, obj, true));
						}

					} else {
						//////////
						// We're somewhere on the line, move one column right first
						//////
							++sem->columnEdit;
							if (sem->columnEdit == 1 && line->sourceCode_populatedLength == 1)
								return(true);


						//////////
						// If we're on a whitespace character, scan left until we reach a non-whitespace character
						//////
							if (!iiSEM_isBreakingCharacter(sem, line, 0))
							{
								// Continue until we find a whitespace
								for ( ; sem->columnEdit < line->sourceCode_populatedLength && !iiSEM_isBreakingCharacter(sem, line, 0); )
									++sem->columnEdit;
							}

							if (iiSEM_isBreakingCharacter(sem, line, 0))
							{
								// When we get to the first non-whitespace, we break
								for ( ; sem->columnEdit < line->sourceCode_populatedLength && iiSEM_isBreakingCharacter(sem, line, 0); )
									++sem->columnEdit;
							}


						//////////
						// If we're not at the end of the line, then we look for the first whitespace character
						//////
							if (sem->columnEdit >= line->sourceCode_populatedLength)
							{
								// We have to go to the next line (if we can)
								if (sem->lastLine != line)
								{
									// Go down one line
									iSEM_navigate(sem, obj, 1, 0);

									// Go to the start of the line
									if (sem->columnEdit > 0)
										iSEM_navigate(sem, obj, 0, -sem->columnEdit);

									// Continue looking word left on this line
									return(iSEM_navigateWordRight(sem, obj, true));
								}
							}
					}


				//////////
				// Verify we're visible
				//////
					if (tlVerifyCursorIsVisible)
						iSEM_verifyCursorIsVisible(sem, obj);


				// Indicate success
				return(true);
			}


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to navigate to the top of the chain
//
//////
	bool iSEM_navigateToTopLine(SEM* sem, SObject* obj)
	{
		logfunc(__FUNCTION__);
		// Make sure the environment is sane
		if (sem && sem->firstLine)
		{
			//////////
			// Save previous position
			//////
				sem->line_cursorLast	= sem->line_cursor;


			//////////
			// Move to top of the document
			//////
				sem->line_top			= sem->firstLine;
				sem->line_cursor		= sem->firstLine;


			//////////
			// Verify we're visible
			//////
				iSEM_verifyCursorIsVisible(sem, obj);


			// Indicate we did something
			return(true);
		}


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to navigate to the end of the chain
//
//////
	bool iSEM_navigateToEndLine(SEM* sem, SObject* obj)
	{
		s32			lnTop, lnBottom;
		SFont*		font;
		SLine*		line;
		RECT		lrc;


		logfunc(__FUNCTION__);
		//////////
		// Grab the rectangle we're working in
		//////
			font = iSEM_getRectAndFont(sem, obj, &lrc);


		//////////
		// Make sure we're valid
		//////
			if (sem && sem->line_cursor)
			{
				//////////
				// Grab the line and form
				//////
					line = sem->line_cursor;


				//////////
				// Navigate to the end
				//////
					// We need to scan forward from ecTopLine to see if we'd be off screen.
					// If so, we drag ecTopLine forward until we reach the visible portion
					lnTop		= lrc.top;
					lnBottom	= lrc.bottom - font->tm.tmHeight;
					while (sem->line_top->ll.next && line->ll.next)
					{
						//////////
						// Are we still on screen?
						//////
							if (lnTop > lnBottom)
							{
								// We're off screen, so we're dragging the top forward
								sem->line_top = (SLine*)sem->line_top->ll.next;

							} else {
								// Still on the same page
								lnTop += font->tm.tmHeight;
							}


						//////////
						// Move to next line
						//////
							line = (SLine*)line->ll.next;
					}


				//////////
				// Update the cursor line
				//////
					sem->line_cursor = line;


				//////////
				// Verify we're visible
				//////
					iSEM_verifyCursorIsVisible(sem, obj);


				// Indicate success
				return(true);
			}


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to navigate to the start of the selected block
//
//////
	bool iSEM_navigateToSelectStart(SEM* sem, SObject* obj, bool tlMoveByOrigin)
	{
		logfunc(__FUNCTION__);
		//////////
		// Make sure we're valid
		//////
			if (sem && iSEM_isSelecting(sem))
			{
				//////////
				// Move to the start
				//////
					if (tlMoveByOrigin)
					{
						// We are moving by the origin start
						sem->line_cursor = sem->selectOrigin.line;

					} else {
						// We are moving by whatever's closest to the top of the file
						if (sem->selectOrigin.lineNumber < sem->selectEnd.lineNumber)			sem->line_cursor = sem->selectOrigin.line;
						else																sem->line_cursor = sem->selectEnd.line;
					}


				//////////
				// Verify we're visible
				//////
					iSEM_verifyCursorIsVisible(sem, obj);


				// Indicate success
				return(true);
			}


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to navigate to the end of the selected block
//
//////
	bool iSEM_navigateToSelectEnd(SEM* sem, SObject* obj, bool tlMoveByOrigin)
	{
		logfunc(__FUNCTION__);
		//////////
		// Make sure we're valid
		//////
			if (sem && iSEM_isSelecting(sem))
			{
				//////////
				// Move to the start
				//////
					if (tlMoveByOrigin)
					{
						// We are moving by the origin start
						sem->line_cursor = sem->selectEnd.line;

					} else {
						// We are moving by whatever's closest to the end of the file
						if (sem->selectOrigin.lineNumber < sem->selectEnd.lineNumber)			sem->line_cursor = sem->selectEnd.line;
						else																sem->line_cursor = sem->selectOrigin.line;
					}


				//////////
				// Verify we're visible
				//////
					iSEM_verifyCursorIsVisible(sem, obj);


				// Indicate success
				return(true);
			}


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to roll the screen up one line
//
//////
	bool iSEM_rollUp(SEM* sem, SObject* obj)
	{
		bool llChanged;


		logfunc(__FUNCTION__);
		// Make sure our environment is sane
		llChanged = false;
		if (sem)
		{
			// Move the top line up one
			if (sem->line_top && sem->line_top->ll.prev)
			{
				llChanged		= true;
				sem->line_top	= (SLine*)sem->line_top->ll.prev;
			}

			// Move the cursor line up one
			if (sem->line_cursor && sem->line_cursor->ll.prev)
			{
				llChanged			= true;
				sem->line_cursor	= (SLine*)sem->line_cursor->ll.prev;
			}

			// If we moved anything...
			if (llChanged)
				iSEM_verifyCursorIsVisible(sem, obj);
		}

		// Indicate our status
		return(llChanged);
	}




//////////
//
// Called to roll the screen down one line
//
//////
	bool iSEM_rollDown(SEM* sem, SObject* obj)
	{
		bool llChanged;


		logfunc(__FUNCTION__);
		// Make sure our environment is sane
		llChanged = false;
		if (sem)
		{
			// Move the top line down one
			if (sem->line_top && sem->line_top->ll.next)
			{
				llChanged		= true;
				sem->line_top	= (SLine*)sem->line_top->ll.next;
			}

			// Move the cursor line down
			if (sem->line_cursor && sem->line_cursor->ll.next)
			{
				llChanged			= true;
				sem->line_cursor	= (SLine*)sem->line_cursor->ll.next;
			}

			// If we moved anything...
			if (llChanged)
				iSEM_verifyCursorIsVisible(sem, obj);
		}

		// Indicate our status
		return(llChanged);
	}




//////////
//
// Moves the cursor line to the middle of the visible screen
//
//////
	bool iSEM_centerCursorLine(SEM* sem, SObject* obj)
	{
		s32			lnI, lnRows;
		SFont*		font;
		SLine*		line;
		RECT		lrc;


		logfunc(__FUNCTION__);
		//////////
		// Grab the rectangle we're working in
		//////
			font = iSEM_getRectAndFont(sem, obj, &lrc);


		//////////
		// Make sure we're valid
		//////
			if (sem && sem->line_cursor)
			{

				//////////
				// Determine how many rows there are on screen
				//////
					lnRows = ((lrc.bottom - lrc.top) / font->tm.tmHeight) / 2;


				//////////
				// Move to that location
				//////`
					line = sem->line_cursor;
					for (lnI = 0; line && line->ll.prev && lnI < lnRows; lnI++)
						line = (SLine*)line->ll.prev;


				///////////
				// At this point, edit is what should be the cursor line
				//////
					sem->line_top = line;


				//////////
				// Verify we're visible
				//////
					iSEM_verifyCursorIsVisible(sem, obj);


				//////////
				// Indicate success
				//////
					return(true);

			} else {
				// Failure
				return(false);
			}
	}




//////////
//
// Called to select from where we are up one line.
// Note:  If we are not already selecting, then we assume an anchor mode select,
//        which begins at an arbitrary column, and ends at an arbitrary column.
//
//////
	bool iSEM_selectLineUp(SEM* sem, SObject* obj)
	{
		logfunc(__FUNCTION__);
		iSEM_selectStart(sem, _SEM_SELECT_MODE_ANCHOR);
		return(iSEM_navigate(sem, obj, -1, 0));
	}




//////////
//
// Called to select from where we are down one line.
// Note:  If we are not already selecting, then we assume an anchor mode select,
//        which begins at an arbitrary column, and ends at an arbitrary column.
//
//////
	bool iSEM_selectLineDown(SEM* sem, SObject* obj)
	{
		logfunc(__FUNCTION__);
		iSEM_selectStart(sem, _SEM_SELECT_MODE_ANCHOR);
		return(iSEM_navigate(sem, obj, 1, 0));
	}




//////////
//
// Called to select left one character.
// Note:  If we are in line select mode, this command has no effect unless we are at
//        the end of the line, at which time we will navigate to the next line.
//
//////
	bool iSEM_selectLeft(SEM* sem, SObject* obj)
	{
		logfunc(__FUNCTION__);
		iSEM_selectStart(sem, _SEM_SELECT_MODE_ANCHOR);
		return(iSEM_navigate(sem, obj, 0, -1));
	}




//////////
//
// Called to select right one character.
//
//////
	bool iSEM_selectRight(SEM* sem, SObject* obj)
	{
		logfunc(__FUNCTION__);
		iSEM_selectStart(sem, _SEM_SELECT_MODE_ANCHOR);
		return(iSEM_navigate(sem, obj, 0, 1));
	}




//////////
//
// Called to select from where we are to the end of line
//
//////
	bool iSEM_selectToEndOfLine(SEM* sem, SObject* obj)
	{
		bool llResult;


		logfunc(__FUNCTION__);
		if (sem->columnEdit >= sem->line_cursor->sourceCode_populatedLength)
		{
			// We're past the end of the line
			llResult = iSEM_navigate(sem, obj, 0, -(sem->columnEdit - sem->line_cursor->sourceCode_populatedLength));
			iSEM_selectStart(sem, _SEM_SELECT_MODE_ANCHOR);

		} else {
			// We're before the end of the line
			iSEM_selectStart(sem, _SEM_SELECT_MODE_ANCHOR);
			llResult = iSEM_navigate(sem, obj, 0, sem->line_cursor->sourceCode_populatedLength - sem->columnEdit);
		}

		// Indicate our result
		return(llResult);
	}




//////////
//
// Called to left one character of where we are to the beginning of line
//
//////
	bool iSEM_selectToBeginOfLine(SEM* sem, SObject* obj)
	{
		logfunc(__FUNCTION__);
		iSEM_selectStart(sem, _SEM_SELECT_MODE_ANCHOR);
		if (sem->columnEdit > 0)		return(iSEM_navigate(sem, obj, 0, -sem->columnEdit));
		else					return(true);
	}




//////////
//
// Called to toggle selection by column mode
//
//////
	bool iSEM_selectColumnToggle(SEM* sem, SObject* obj)
	{
		logfunc(__FUNCTION__);
		if (sem->selectMode != _SEM_SELECT_MODE_NONE)
		{
			// Turn off selecting mode
			sem->selectMode = _SEM_SELECT_MODE_NONE;
			iSEM_selectStop(sem);

		} else {
			// Turn on column select mode
			iSEM_selectStart(sem, _SEM_SELECT_MODE_COLUMN);
		}
		return(true);
	}




//////////
//
// Called to toggle selection by line mode
//
//////
	bool iSEM_selectLineToggle(SEM* sem, SObject* obj)
	{
		logfunc(__FUNCTION__);
		if (sem->selectMode != _SEM_SELECT_MODE_NONE)
		{
			// Turn off selecting mode
			sem->selectMode = _SEM_SELECT_MODE_NONE;
			iSEM_selectStop(sem);

		} else {
			// Turn on line select mode
			iSEM_selectStart(sem, _SEM_SELECT_MODE_LINE);
		}
		return(true);
	}




//////////
//
// Called to toggle selection by line mode
//
//////
	bool iSEM_selectAnchorToggle(SEM* sem, SObject* obj)
	{
		logfunc(__FUNCTION__);
		if (sem->selectMode != _SEM_SELECT_MODE_NONE)
		{
			// Turn off selecting mode
			sem->selectMode = _SEM_SELECT_MODE_NONE;
			iSEM_selectStop(sem);

		} else {
			// Turn on anchor select mode
			iSEM_selectStart(sem, _SEM_SELECT_MODE_ANCHOR);
		}
		return(true);
	}




//////////
//
// Called to select one word left
// Note:  If we are in line select mode, this command has no effect unless we are at
//        the beginning of the line, at which time we will navigate to the previous line
//        and all of the previous line will be selected.
//
//////
	bool iSEM_selectWordLeft(SEM* sem, SObject* obj)
	{
		logfunc(__FUNCTION__);
		iSEM_selectStart(sem, _SEM_SELECT_MODE_ANCHOR);
		return(iSEM_navigateWordLeft(sem, obj, true));
	}




//////////
//
// Called to select one word right
// Note:  If we are in line select mode, this command has no effect unless we are at
//        the end of the line, at which time we will navigate to the next line and all
//        of the next line will be selected.
//
//////
	bool iSEM_selectWordRight(SEM* sem, SObject* obj)
	{
		logfunc(__FUNCTION__);
		iSEM_selectStart(sem, _SEM_SELECT_MODE_ANCHOR);
		return(iSEM_navigateWordRight(sem, obj, true));
	}




//////////
//
// Select from where we are to the top of the file
//
//////
	bool iSEM_selectToTopLine(SEM* sem, SObject* obj)
	{
		logfunc(__FUNCTION__);
		iSEM_selectStart(sem, _SEM_SELECT_MODE_ANCHOR);
		return(iSEM_navigateToTopLine(sem, obj));
	}




//////////
//
// Select from where we are to the top of the file
//
//////
	bool iSEM_selectToEndLine(SEM* sem, SObject* obj)
	{
		logfunc(__FUNCTION__);
		iSEM_selectStart(sem, _SEM_SELECT_MODE_ANCHOR);
		return(iSEM_navigateToEndLine(sem, obj));
	}




//////////
//
// Called to delete one character left (backspace)
//
//////
	bool iSEM_deleteLeft(SEM* sem, SObject* obj)
	{
		SLine*	line;
		SLine*	lineLast;


		logfunc(__FUNCTION__);
		//////////
		// Make sure we're valid
		//////
			if (sem && !sem->isReadOnly && sem->line_cursor)
			{
				// Grab the line
				line		= sem->line_cursor;
				lineLast	= sem->lastLine;

				// If there's nothing on this line, delete it
				if (sem->line_cursor->sourceCode_populatedLength == 0)
				{
					if (sem->firstLine != sem->lastLine)
					{
						// Delete the current line
						iSEM_deleteLine(sem);

						if (lineLast != line)
						{
							// Navigate up one line
							iSEM_navigate(sem, obj, -1, 0);
						}

						// Navigate to the end of the current line
						iSEM_navigate(sem, obj, 0, sem->line_cursor->sourceCode_populatedLength - sem->columnEdit);
					}

				} else {
					// Do we need to do anything?
					if (sem->columnEdit == 0)
					{
						if (sem->firstLine != sem->lastLine)
						{
							// Delete the current line
							iSEM_deleteLine(sem);

							if (lineLast != line)
							{
								// Navigate up one line
								iSEM_navigate(sem, obj, -1, 0);
							}

							// Navigate to the end of the current line
							iSEM_navigate(sem, obj, 0, sem->line_cursor->sourceCode_populatedLength - sem->columnEdit);
						}

					} else if (sem->columnEdit > 0 && sem->columnEdit <= line->sourceCode_populatedLength) {
						// Reduce our column position
						--sem->columnEdit;

						// Based on insert, handle it different
						if (!sem->isOverwrite)
						{
							// We're in insert mode, so we drag everything with us
							iSEMLine_characterDelete(sem);

						} else {
							// We're in overwrite mode, so we just insert a space
							iSEMLine_characterOverwrite(sem, ' ');

							// The overwrite moves us back right again, so we reduce our column position
							--sem->columnEdit;
						}
					}
				}

				// Reprocess the source code on the line
				iEngine_parse_sourceCode_line(sem->line_cursor);


				//////////
				// Verify we're visible
				//////
					iSEM_verifyCursorIsVisible(sem, obj);


				// Indicate success
				return(true);
			}


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to select one character right (delete key)
//
//////
	bool iSEM_deleteRight(SEM* sem, SObject* obj)
	{
		logfunc(__FUNCTION__);
		//////////
		// Make sure we're valid
		//////
			if (sem && !sem->isReadOnly && sem->line_cursor)
			{
				if (sem->line_cursor->sourceCode_populatedLength == 0)
				{
					// There's no data on this line, if we're in insert mode delete the line
					if (!sem->isOverwrite && sem->firstLine != sem->lastLine)
						iSEM_deleteLine(sem);

				} else {
					// Delete everything to the right
					iSEMLine_characterDelete(sem);
				}

				// Reprocess the source code on the line
				iEngine_parse_sourceCode_line(sem->line_cursor);


				//////////
				// Verify we're visible
				//////
					iSEM_verifyCursorIsVisible(sem, obj);


				// Indicate success
				return(true);
			}


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to delete one word left (ctrl+backspace)
//
//////
	bool iSEM_deleteWordLeft(SEM* sem, SObject* obj)
	{
		s32		lnI, lnColumnStart, lnColumnEnd;
		SLine*	line;


		logfunc(__FUNCTION__);
		//////////
		// Make sure we're valid
		//////
			if (sem && !sem->isReadOnly && sem->line_cursor)
			{
				// Store where we are now
				lnColumnStart	= sem->columnEdit;
				line			= sem->line_cursor;

				// See if we can navigate right
				if (iSEM_navigateWordLeft(sem, obj, false))
				{
					// Are we still on the same line?
					if (sem->line_cursor == line && sem->columnEdit < lnColumnStart)
					{
						// Delete the indicated number of characters
						lnColumnEnd = lnColumnStart - sem->columnEdit;
						for (lnI = 0; lnI < lnColumnEnd; lnI++)
							iSEMLine_characterDelete(sem);

					} else if (sem->line_cursor == line && sem->columnEdit == 0 && line->sourceCode_populatedLength > 0) {
						// Delete to the start of line
						lnColumnEnd = line->sourceCode_populatedLength;
						for (lnI = 0; lnI < lnColumnEnd; lnI++)
							iSEMLine_characterDelete(sem);

					} else if (sem->line_cursor != line && sem->columnEdit < sem->line_cursor->sourceCode_populatedLength) {
						// Navigate to the end so the next delete will work
						iSEM_navigate(sem, obj, 0, sem->line_cursor->sourceCode_populatedLength - sem->columnEdit);
					}

					// Reprocess the source code on the line if need be
					if (sem->isSourceCode)
						iEngine_parse_sourceCode_line(sem->line_cursor);

					// Indicate success
					return(true);
				}
			}


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to delete one word right (ctrl+delete)
//
//////
	bool iSEM_deleteWordRight(SEM* sem, SObject* obj)
	{
		s32		lnI, lnColumnStart, lnColumnEnd;
		SLine*	line;


		logfunc(__FUNCTION__);
		//////////
		// Make sure we're valid
		//////
			if (sem && !sem->isReadOnly && sem->line_cursor)
			{
				// Store where we are now
				lnColumnStart	= sem->columnEdit;
				line			= sem->line_cursor;

				// See if we can navigate right
				if (iSEM_navigateWordRight(sem, obj, false))
				{
					// Are we still on the same line?
					if (sem->line_cursor == line || line->sourceCode_populatedLength > lnColumnStart)
					{
						// We weren't done with the line yet
						if (sem->line_cursor != line && line->sourceCode_populatedLength > lnColumnStart)
						{
							sem->line_cursor	= line;
							sem->columnEdit			= lnColumnStart;
						}

						// See how we can delete here
						if (sem->columnEdit > lnColumnStart)
						{
							// Delete sem->column - columnStart from where we were
							lnColumnEnd			= sem->columnEdit;
							sem->line_cursor	= line;
							sem->columnEdit			= lnColumnStart;

							// Delete the indicated number of characters
							lnColumnEnd = lnColumnEnd - lnColumnStart;
							for (lnI = 0; lnI < lnColumnEnd; lnI++)
								iSEMLine_characterDelete(sem);

							// Reprocess the source code on the line if need be
							if (sem->isSourceCode)
								iEngine_parse_sourceCode_line(sem->line_cursor);

							// Indicate success
							return(true);

						} else if (sem->columnEdit != 0 && sem->columnEdit < line->sourceCode_populatedLength) {
							// Delete sem->column - columnStart from where we were
							sem->line_cursor	= line;
							sem->columnEdit			= lnColumnStart;

							// Delete to the end of line
							lnColumnEnd = line->sourceCode_populatedLength - sem->columnEdit;
							for (lnI = 0; lnI < lnColumnEnd; lnI++)
								iSEMLine_characterDelete(sem);

							// Reprocess the source code on the line if need be
							if (sem->isSourceCode)
								iEngine_parse_sourceCode_line(sem->line_cursor);

							// Indicate success
							return(true);
						}
					}
				}
			}


		// If we get here, indicate failure
		return(false);
	}




//////////
//
// Called to navigate to the indicated position on the screen
//
//////
	bool iSEM_navigateTo_pixelXY(SEM* sem, SObject* obj, s32 x, s32 y)
	{
		s32			lnI, lnRow, lnExtra, lnCandidateCol;
		bool		llResult;
		RECT		lrc;
		SLine*		line;
		SFont*		font;


		logfunc(__FUNCTION__);
		// Make sure our environment is sane
		llResult = false;
		if (sem && sem->line_top && obj)
		{
			//////////
			// Grab the rectangle we're working in
			//////
				font = iSEM_getRectAndFont(sem, obj, &lrc);


			//////////
			// Back off if we're showing line numbers
			//////
				if (sem->showLineNumbers)
					x -= sem->rcLineNumberLastRender.right;


			//////////
			// See which row and column the click would be on
			//////
				lnRow		= y / font->tm.tmHeight;
				lnExtra		= font->tm.tmMaxCharWidth - (font->tm.tmAveCharWidth * 2);			// Added to fix the bug mentioned below
				if (lnExtra < 0)
					lnExtra = 0;

				// We only go to the column if it's valid, otherwise we just move to the row
				lnCandidateCol = sem->columnLeft + (x / (font->tm.tmAveCharWidth + lnExtra));
				if (lnCandidateCol > 0 && x >= lrc.left)
					sem->columnEdit = lnCandidateCol;


			//////////
			// Move to that location
			//////`
				line = sem->line_top;
				for (lnI = 0; line && line->ll.next && lnI < lnRow; lnI++)
					line = (SLine*)line->ll.next;


			//////////
			// Validate that this column is allowable
			//////
				if (!sem->allowMoveBeyondEndOfLine && sem->columnEdit > line->sourceCode_populatedLength)
					sem->columnEdit = line->sourceCode_populatedLength;


			///////////
			// At this point, edit is what should be the cursor line
			//////
				sem->line_cursorLast	= sem->line_cursor;
				sem->line_cursor		= line;


			//////////
			// Verify we're visible
			//////
				iSEM_verifyCursorIsVisible(sem, obj);


			// Indicate success
			llResult = true;
		}

		// Indicate our status
		return(llResult);
	}




//////////
//
// Indicates if the character under the cursor is a breaking character
//
//////
	bool iiSEM_isBreakingCharacter(SEM* sem, SLine* line, s32 tnDeltaTest)
	{
		u8 c;


		// Testing if we have data
		if (line->sourceCode && line->sourceCode->_data)
		{
// TODO:  Need to add code here to test a new member sem->isBreakOnCamelCase, and a new parameter indicating movement direction

			// If we're at the beginning of the line, or beyond the end, we're at a breaking character
			if (sem->columnEdit + tnDeltaTest <= 0 || sem->columnEdit + tnDeltaTest >= line->sourceCode_populatedLength)
				return(true);

			// If this is a breaking character, return true
			c = line->sourceCode->data_u8[sem->columnEdit + tnDeltaTest];
			switch (c)
			{
				case 32:	// Space
				case 9:		// Tab
				case '.':
				case '(':
				case ')':
				case ',':
					return(true);

				default:
					if (sem->stopNavigationOnNbsp && c == 255)
						return(true);
			}
		}

		// Indicate failure
		return(false);
	}




//////////
//
// Selecting begins at the current coordinates if it's not already selected.
//
//////
	void iSEM_selectStart(SEM* sem, u32 tnSelectMode)
	{
		if (sem && sem->selectMode == _SEM_SELECT_MODE_NONE && sem->line_cursor)
		{
			// We're starting a new selection
			switch (tnSelectMode)
			{
				case _SEM_SELECT_MODE_LINE:
				case _SEM_SELECT_MODE_COLUMN:
				case _SEM_SELECT_MODE_ANCHOR:
					iSEM_renumber(sem, 1);
					sem->selectMode = tnSelectMode;

					// Note where we start
					sem->selectOrigin.lineNumber		= sem->line_cursor->lineNumber;
					sem->selectOrigin.uid			= sem->line_cursor->uid;
					sem->selectOrigin.column			= sem->columnEdit;
					sem->selectOrigin.line			= sem->line_cursor;

					// Update the extents
					iSEM_selectUpdateExtents(sem);
					break;
			}
		}
	}




//////////
//
// Are we selecting?
//
//////
	bool iSEM_isSelecting(SEM* sem)
	{
		return(sem && sem->selectMode != _SEM_SELECT_MODE_NONE);
	}




//////////
//
// Selecting has stopped
//
//////
	void iSEM_selectStop(SEM* sem)
	{
		if (sem && sem->selectMode != _SEM_SELECT_MODE_NONE)
			sem->selectMode = _SEM_SELECT_MODE_NONE;
	}




//////////
//
// Selecting to the current location
//
//////
	void iSEM_selectUpdateExtents(SEM* sem)
	{
		if (sem && sem->selectMode != _SEM_SELECT_MODE_NONE && sem->line_cursor)
		{
			// Store where they are now
			sem->selectEnd.lineNumber	= sem->line_cursor->lineNumber;
			sem->selectEnd.uid			= sem->line_cursor->uid;
			sem->selectEnd.column		= sem->columnEdit;
			sem->selectEnd.line			= sem->line_cursor;
		}
	}
