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


#define _SFILE_DEFINED 1
struct SFile
{
	SLL				ll;							// 2-way link list

	// File info
	SDatum			pathname;					// The fully qualified pathname
	s32				os_handle;					// The handle

	// Information related to this file
	SBuilder*		related_info;				// (SRelatedInfo) items related to this file
	SBuilder*		extra_info;					// (SExtraInfo) extra information about this file
	void*			parent;						// An optional parent this relates to
};

#define _SRELATEDINFO_DEFINED 1
struct SRelatedInfo
{
	bool			isUsed;						// Is this slot in use?

	// Related data, discriminated by relType
	s32				relType;					// The type of relation (see _RELTYPE_* constants)
	union
	{
		void*		data;						// The related data
		void*		data1;
	};
};

// Structure of parsed components on a line, tokens by another name
#define _SCOMP_DEFINED 1
struct SComp
{
	SLL				ll;							// 2-way link list

	// Information about the component
	s32				iCode;						// Refer to _ICODE_* constants
	u32				iCat;						// Refer to _ICAT_* constants, and use iCat() macro for accessing the lower portion without bit flags influencing its value
	bool			llAllocated;				// When deleted, should it be free'd?
	SDatum			text;						// The text this component relates to
	s32				nbspCount;					// Number of non-breaking-spaces in this component (ASCII-255)

	// References to other related items
	SNode*			node;						// The node this component relates to
	SFile*			file;						// Source file
	SEM*			sem;						// SEM instance
	SLine*			line;						// Source line
	s32				start;						// Offset into line
	s32				length;						// Length of component

	// Information related to this component
	SBuilder*		related_info;				// (SRelatedInfo) items related to this component
	SBuilder*		extra_info;					// (SExtraInfo) extra information about this component

	// For rendering and syntax highlighting
	SBmpCache*		bc;							// For faster rendering of drawn things (casks, for example) in SEM windows
	SBgra*			color;						// Syntax highlight color
	bool			useBoldFont;				// Syntax highlight font should be bold?
	// For selected components
	SBgra*			overrideSelectionBackColor;
	SBgra*			overrideSelectionForeColor;
	// For matches (the closest parenthesis, bracket, brace, etc)
	SBgra*			overrideMatchingForeColor;
	SBgra*			overrideMatchingBackColor;
};

// Extra info contains information about a line of source code
#define _SEXTRAINFO_DEFINED 1
struct SExtraInfo
{
	bool		isUsed;							// Is this item currently in use?
	s32			eiType;							// A registered identifier with the system for this extra info block
	u32			app_eiType;						// An application defined type
	void*		data;							// Associated data
	SDatum		info;							// The extra info block stored for this entry


	//////////
	// Functions to called when the associated line is processed in some way
	//////
		union {
			uptr	_onAccess;					// When the line is accessed
			void	(*onAccess)					(SEM* sem, SLine* line, SExtraInfo* extra_info);
		};

		union {
			uptr	_onArrival;					// When the SEM's cursor line is sitting on this line
			void	(*onArrival)				(SEM* sem, SLine* line, SExtraInfo* extra_info);
		};

		union {
			uptr	_onUpdate;					// When the line is updated/changed
			void	(*onUpdate)					(SEM* sem, SLine* line, SExtraInfo* extra_info);
		};


	//////////
	// Function to call before freeing an entry
	//////
		union {
			uptr		_freeInternal;			// Called to free any data in this.info
			SExtraInfo*	(*freeInternal)			(SEM* sem, SLine* line, SExtraInfo* extra_info);
		};
};

// Breakpoints during execution
#define _SBREAKPOINT_DEFINED 1
// Breakpoint types
cu32	_BREAKPOINT_NONE								= 0;	// No breakpoint
cu32	_BREAKPOINT_ALWAYS								= 1;	// Always stops
cu32	_BREAKPOINT_CONDITIONAL_TRUE					= 2;	// Breaks when the condition is true
cu32	_BREAKPOINT_CONDITIONAL_FALSE					= 3;	// Breaks when the condition is false
cu32	_BREAKPOINT_CONDITIONAL_TRUE_COUNTDOWN			= 4;	// Breaks when the condition is true, and the countdown reaches zero
cu32	_BREAKPOINT_CONDITIONAL_FALSE_COUNTDOWN			= 5;	// Breaks when the condition is false, and the countdown reaches zero
cu32	_BREAKPOINT_CODEPOINT							= 6;	// Executes code when encountered
struct SBreakpoint
{
	// See _BREAKPOINT_* constants
	u32				type;
	bool			isUsed;								// Allocated in gBreakpoints as a bulk structure
	s32				soundChannel;						// Sound channel to engage when the breakpoint is encountered
	SBitmap*		bmpImage;							// Image to display when encountered
	u32				osKey;								// Keystroke to use to continue (allows certain breakpoints to not continue on normal RESUME command)

	// If there's a countdown
	u32				countdownResetValue;				// The value the countdown will reset to once it fires, if 0 always fires
	u32				countdown;							// Countdown to 0 when it fires

	// A test condition
	SSourceCode*	conditionalCode;					// What is the conditional test expression for this breakpoint firing?

	// Code to execute when the conditionalCode returns true
	SSourceCode*	executeCode;						// Arbitrary code to execute when the breakpoint fires
	// Explicitly:  breakpoint_always(), breakpoint_true(), breakpoint_false()
};

// Holds compiler data (added as a related item or extra item)
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
	SBuilder*		related_info;						// (SRelatedInfo) items related to this compiler
	SBuilder*		extra_info;							// (SExtraInfo) extra information about this compiler
};

#define _SLINE_DEFINED 1
// #if defined(_LASM_COMPILE)
// 	// Other usages defined by app, see /libsf/exodus/tools/lasm/lasm.cpp for an example
// 	SLasmLineStatus		status;
// 	SDatum*				fileName;
// #endif

struct SLine
{
	SLL				ll;												// 2-way link list
	u32				uid;											// Unique id for this line, used for undos and identifying individual lines which may move about (note this value must be isolated and separate from ll.uniqueId)

	// Line information
	u32				lineNumber;										// This line's number
	s32				lineStatus;										// See _LINESTATUS_* constants
	SDatum			sourceCodeOriginal;								// The original sourceCode when the line was first created, or last saved (note the length here is the total length as this value does not change, but is setup exactly when it is updated)
	SDatum			sourceCode;										// The text on this line is LEFT(sourceCode.data, sourceCodePopulated)
	s32				populatedLength;								// The actual populated length of sourceCode, which may differ from sourceCode.length (which is the allocated length of sourceCode.data)

	// Optional related components associated with this line
	SComp*			firstComp;

	// Information related to this line
	SBuilder*		related_info;									// (SRelatedInfo) items related to this line
	SBuilder*		extra_info;										// (SExtraInfo) extra information about this line
	void*			parent;											// A parent this relates to, which could be a controlling structure (like an SEM*)

	// Each render, these are updated
	u32				renderId;										// Each time it's rendered, this value is set
	RECT			rcLastRender;									// The rectangle within the parent of the last render
};

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

#endif 	// __COMPSEARCHER_H__
