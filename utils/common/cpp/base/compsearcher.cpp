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
