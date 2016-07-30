//////////
//
// /libsf/utils/common/cpp/base/compsearcher.cpp
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
// Version 0.10
// Copyright (c) 2016 by Rick C. Hodgin
//////
// Last update:
//     Jun.23.2016
//////
// Change log:
//     Jun.23.2016	- Initial creation
//////
//
// This file is handles all file/line/comp related algorithms.
//
//////////
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
//     http://www.visual-freepro.org
//     http://www.visual-freepro.org/blog/
//     http://www.visual-freepro.org/forum/
//     http://www.visual-freepro.org/wiki/
//     http://www.visual-freepro.org/wiki/index.php/PBL
//
// Thank you.  And may The Lord bless you richly as you lift up your life, your
// talents, your gifts, your praise, unto Him.  In Jesus' name I pray.  Amen.
//
//////////




//////////
//
// Called to delete the previous allocated compiler data
//
//////
	void iLiveCode_delete(SLiveCode* livecodeRoot)
	{
		// Make sure our environment is sane
		if (livecodeRoot)
		{
			// Delete the items here
			iNoteLog_removeAll(&livecodeRoot->firstWarning);
			iNoteLog_removeAll(&livecodeRoot->firstInquiry);
			iNoteLog_removeAll(&livecodeRoot->firstNote);
		}
	}




//////////
//
// Called to create a new note.
//
//////
	// Note:  tcMessage should be NULL terminated
	SNoteLog* iNoteLog_create(SNoteLog** noteRoot, SLine* line, SComp* comp, cu8* tcMessage, u32 tnNumber, s32 tnStart, s32 tnEnd)
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
			note->comp		= comp;
			note->start		= tnStart;
			note->end		= tnEnd;
			note->number	= tnNumber;
			iDatum_duplicate(&note->note, (cvp*)tcMessage, -1);
		}

		// Indicate our status
		return(note);
	}

	// Creates a note associated with the indicated line
	SNoteLog* iNoteLog_create_byLine(SLine* line, cu8* tcMessage, u32 tnNumber, u32 tnStart, u32 tnEnd, SNoteLog** noteRoot)
	{
		if (line)
		{
			// Append to the indicated noteRoot, or to the line
			return(iNoteLog_create(((noteRoot) ? noteRoot : &line->firstNote), line, NULL, tcMessage, tnNumber, tnStart, tnEnd));

		} else {
			// Invalid
			return(NULL);
		}
	}

	SNoteLog* iNoteLog_create_byComp(SComp* comp, cu8* tcMessage, u32 tnNumber, u32 tnStart, u32 tnEnd, SNoteLog** noteRoot)
	{
		if (comp)
		{
			// Append to the indicated noteRoot, or to the line
			return(iNoteLog_create(((noteRoot) ? noteRoot : &comp->firstNote), NULL, comp, tcMessage, tnNumber, tnStart, tnEnd));

		} else {
			// Invalid
			return(NULL);
		}
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




//////////
//
// Called to duplicate the entire NoteLog chain
//
//////
	void iNoteLog_duplicateChain(SNoteLog** noteDstRoot, SNoteLog* noteSrc)
	{
		SLLCallback cb;


		// Initialize and duplicate
		memset(&cb, 0, sizeof(cb));
		cb._func = (uptr)&iNoteLog_duplicateChain__callback;
		*noteDstRoot = (SNoteLog*)iLl_duplicateChain__llWithCallback((SLL*)noteSrc, &cb, sizeof(SNoteLog));
	}

	bool iNoteLog_duplicateChain__callback(SLLCallback* cb)
	{
		SNoteLog* nl;
		SNoteLog* nlNew;


		// Should always be valid, but... :-)
		if ((nl = (SNoteLog*)cb->ll))
		{
			// Duplicate
			nlNew = (SNoteLog*)iLl_duplicate(cb->ll, sizeof(SNoteLog), true);
			if (nlNew)
			{
				// Copy the note
				iDatum_duplicate(&nlNew->note, &nl->note);

				// Indicate success
				cb->llNew					= (SLL*)nlNew;
				cb->llNewEntryIsOkayToUse	= true;
			}
		}

		// Continue iterating
		return(true);
	}
