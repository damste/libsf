//////////
//
// /libsf/utils/common/cpp/include/compsearcher.h
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
//     Jun.22.2016
//////
// Change log:
//     Mar.17.2016	- Initial creation
//     Jun.22.2016  - Significant refactoring
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




//#pragma once
#ifndef __COMPSEARCHER_H__
#define __COMPSEARCHER_H__


// For the lower 64K values of flag-mapped comp->iCat codes
#define iCat(x)										(x & 0xffff)
#define iCatBits(x)									(x & _ICAT_MASK);


//////////
// Extra info
//////
	#define _SEXTRAINFO_DEFINED 1
	struct SExtraInfo
	{
		bool		isUsed;							// Is this item currently in use?
		s32			eiType;							// A registered identifier with the system for this extra info block
		u32			appType;						// An application defined type
		void*		data;							// Associated data
		SDatum		info;							// The extra info block stored for this entry

		// Functions to called when this item is processed in some way
		union
		{
			uptr	_onAccess;					// When the extra info item is accessed
			void	(*onAccess)					(SEM* sem, SLine* line, SExtraInfo* extra_info);
		};

		union
		{
			uptr	_onUpdate;					// When the parent signals that it's been updated/changed
			void	(*onUpdate)					(SEM* sem, SLine* line, SExtraInfo* extra_info);
		};

		union
		{
			uptr		_freeInternal;			// Called on a forced free operation when the parent is deleted
			SExtraInfo*	(*freeInternal)			(SEM* sem, SLine* line, SExtraInfo* extra_info);
		};
	};


//////////
// Compiler data
//////
	#define _SNOTELOG_DEFINED 1
	// For warnings, errors, and notes
	struct SNoteLog
	{
		SLL				ll;
		SYSTEMTIME		time;											// When did the note get logged?

		SLine*			line;											// Associated line (if not already on a line)
		u32				start;											// Column the note begins on
		u32				end;											// Column the note ends on

		u32				number;											// A related number
		SDatum*			note;											// The message
	};

	#define _SCOMPILER_DEFINED 1
	struct SCompiler
	{
		SLine*			parent;								// SLine this compiler data belongs to (parent->compilerInfo points back to here)

															// The last source code line
		SDatum*			sourceCode;							// Copy at last compile of LEFT(parent->sourceCode.data, parent->sourceCodePopulated)
															// Note:  If the source code line ended in a semicolon, the following sourceCode line(s) will be appended here on top of the semicolon until there are no more semicolon lines

															// Results of compilation
		SNoteLog*		firstInquiry;						// Noted inquiry(s) on this source code line
		SNoteLog*		firstWarning;						// Noted warning(s) on this source code line
		SNoteLog*		firstNote;							// Noted note(s) on this source code line

															// Information related to this compiler
		SBuilder*		extra_info;							// (SExtraInfo) extra information about this compiler
	};


//////////
// Known keywords to the system
// ASCII Component Searcher
//////
	#define _SASCIICOMPSEARCHER_DEFINED 1
	struct SAsciiCompSearcher
	{
		union {
			cs8*	keyword_cs8;
			cu8*	keyword_cu8;											// Text keyword being searched
		};
		s32			length;													// Length of the keyword (negative for case sensitive, positive case insensitive, 0 for termination entry)
		bool		repeats;												// Can this item repeat?  Or is this a one-shot keyword?
		s32			iCode;													// An associated code to store when this entry is found
		bool		firstOnLine;											// Should this item ONLY be the first on line?
		u32			iCat;													// This entry's general category (function, operator, keyword, flow)

		// For syntax highlighting
		SBgra*		syntaxHighlightColor;									// Color to display this component in
		bool		useBoldFont;											// Should this be bolded?

		// An optional extra callback to consider further if a candidate match is a valid match before committing
		union {
			uptr	_onCandidateMatch;
			bool	(*onCandidateMatch)(SAsciiCompSearcher* tacs, u8* tcStart, s32 tnLength);
		};

		// An optional extra callback to parse on finds
		union {
			uptr	_onFind;
			void	(*onFind)(SAsciiCompSearcher* tacs, SComp* comp);
		};

		// A callback function for the syntax parsing phase of compilation, to determine if the parameters are correct at compile-time, rather than run-time
		union {
			uptr	_compilerDictionaryLookup;
			s32		(*compilerDictionaryLookup)(SAsciiCompSearcher* tacs, SComp* comp, SComp* paramOrder[], s32* paramCount);
			// Returns an index into the internal function/command dictionary if a match is found, -1 if not
		};
	};


	// Compiler functions
	SCompiler*				iCompiler_allocate							(SLine* parent);
	void					iCompiler_delete							(SCompiler** compilerInfoRoot, bool tlDeleteSelf);

	// Compile note functions
	SNoteLog*				iNoteLog_create								(SNoteLog** noteRoot, SLine* line, u32 tnStart, u32 tnEnd, u32 tnNumber, cu8* tcMessage);
	SNoteLog*				iNoteLog_create								(SNoteLog** noteRoot, SComp* comp, u32 tnNumber, cu8* tcMessage);
	void					iNoteLog_removeAll							(SNoteLog** noteRoot);

#endif 	// __COMPSEARCHER_H__
