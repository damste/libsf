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
	bool iSEMLine_ensureLineLength(SEM* sem, s32 newLineLength)
	{
		SLine* line;


		// Make sure the environment is sane
		if (sem && sem->line_cursor)
		{
			// Has this line had its data allocated?
			line = sem->line_cursor;
			if (!line->sourceCode)
			{
				// We need to allocate the initial data block
				iDatum_allocateSpace(line->sourceCode, max((s32)_ECM_MINIMUM_LINE_ALLOCATION_LENGTH, newLineLength));
				line->sourceCode_populatedLength	= 0;
			}

			// Is there room from where we are to the new line length?
			if (line->sourceCode->length > newLineLength)
				return(true);		// We're good

			// If we get here, we need to reallocate
			return(iDatum_resize(line->sourceCode, newLineLength + _ECM_MINIMUM_LINE_ALLOCATION_LENGTH));
		}
		// If we get here, failure
		return(false);
	}




//////////
//
// Free the edit chain
//
//////
	void iSEMLine_free(SLine** root, bool tlDeleteSelf)
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
						iExtraInfo_removeAll(NULL, line, &line->extra_info, true);


					//////////
					// Delete this item's components and source code references
					//////
						iComps_deleteAll_byLine(line);
						iDatum_delete(line->sourceCode, true);


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
// Called to insert a character
//
//////
	bool iSEMLine_characterInsert(SEM* sem, u8 asciiChar)
	{
		s32			lnI;
		SLine*		line;


		// Make sure our environment is sane
		if (sem && !sem->isReadOnly && sem->line_cursor && sem->line_cursor->sourceCode)
		{
			// Make sure there's room enough for the keystroke
			line = sem->line_cursor;
			if (iSEMLine_ensureLineLength(sem, sem->line_cursor->sourceCode_populatedLength + 1))
			{
				// They could've been beyond the end of line, and if so then we need to insert spaces between the end and here
				if (sem->columnEdit > line->sourceCode_populatedLength)
				{
					// Fill with spaces
					for (lnI = line->sourceCode_populatedLength; lnI < sem->columnEdit; lnI++)
						line->sourceCode->data._s8[lnI] = ' ';
				}

				// Move everything from the end of the line to where we are right one character
				for (lnI = line->sourceCode_populatedLength + 1; lnI > sem->columnEdit && lnI > 0; lnI--)
					line->sourceCode->data._s8[lnI] = line->sourceCode->data._s8[lnI - 1];

				// Signal the update
				iExtraInfo_update(sem, sem->line_cursor);

				// Insert the character
				line->sourceCode->data._s8[sem->columnEdit] = asciiChar;

				// Move to the next column
				++sem->columnEdit;

				// Increase the populated length
				++line->sourceCode_populatedLength;

				// If we're past the end, we need to indicate our populated line length
				if (sem->columnEdit > line->sourceCode_populatedLength)
					line->sourceCode_populatedLength = sem->columnEdit;

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
	bool iSEMLine_characterOverwrite(SEM* sem, u8 asciiChar)
	{
		s32			lnI;
		SLine*		line;


		// Make sure our environment is sane
		if (sem && !sem->isReadOnly && sem->line_cursor && sem->line_cursor->sourceCode)
		{
			// Is there room to inject it?
			line = sem->line_cursor;
			if (iSEMLine_ensureLineLength(sem, sem->line_cursor->sourceCode_populatedLength + 1))
			{
				if (sem->columnEdit > line->sourceCode_populatedLength)
				{
					// We need to insert it because we're at the end of the populated length
					return(iSEMLine_characterInsert(sem, asciiChar));

				} else {
					// We can overwrite it

					// They could've been beyond the end of line, and if so then we need to insert spaces between the end and here
					if (sem->columnEdit > line->sourceCode_populatedLength)
					{
						// Fill with spaces
						for (lnI = line->sourceCode_populatedLength; lnI < sem->columnEdit; lnI++)
							line->sourceCode->data._s8[lnI] = ' ';
					}

					// Signal the update
					iExtraInfo_update(sem, sem->line_cursor);

					// Overwrite the character
					line->sourceCode->data._s8[sem->columnEdit] = asciiChar;

					// Move to the next column
					++sem->columnEdit;

					// If we're past the end, we need to indicate our populated line length
					if (sem->columnEdit > line->sourceCode_populatedLength)
						line->sourceCode_populatedLength = sem->columnEdit;

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
	bool iSEMLine_characterDelete(SEM* sem)
	{
		s32		lnI;
		SLine*	line;


		// Make sure our environment is sane
		if (sem && !sem->isReadOnly && sem->line_cursor && sem->line_cursor->sourceCode)
		{
			// Grab the line
			line = sem->line_cursor;

			// If we're in the populated area
			if (sem->columnEdit < line->sourceCode_populatedLength)
			{
				// Move everything left one character
				for (lnI = sem->columnEdit; lnI < line->sourceCode_populatedLength; lnI++)
					line->sourceCode->data._s8[lnI] = line->sourceCode->data._s8[lnI + 1];

				// Signal the update
				iExtraInfo_update(sem, sem->line_cursor);

				// Reduce the length of the populated portion of the line by one
				--line->sourceCode_populatedLength;

				// Put a space there
				line->sourceCode->data._s8[line->sourceCode_populatedLength] = 32;

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
	SBreakpoint* iSEMLine_toggleBreakpoint(SEM* sem)
	{
		SBreakpoint* bp;


		// Make sure our environment is sane
		if (sem && sem->line_cursor)
		{
			// Grab the line
			if (sem->line_cursor->breakpoint)
			{
				// Delete the existing breakpoint
				iBreakpoint_delete(&sem->line_cursor->breakpoint);
				bp = NULL;

			} else {
				// Adding a new always-stop breakpoint
				bp = iBreakpoint_add(&sem->line_cursor->breakpoint, _BREAKPOINT_ALWAYS);
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
	bool iSEMLine_hasChanged(SLine* ec)
	{
		// Make sure our environment is sane
		if (ec && ec->sourceCode && ec->sourceCodeOriginal)
		{
			// Test lengths
			if (ec->sourceCode_populatedLength != ec->sourceCodeOriginal->length)
				return(true);		// They are different lengths

			// Test content
			if (memcmp(ec->sourceCode->data._s8, ec->sourceCodeOriginal->data._s8, ec->sourceCode_populatedLength) != 0)
				return(true);		// The content is different
		}
		// If we get here, not changed
		return(false);
	}
