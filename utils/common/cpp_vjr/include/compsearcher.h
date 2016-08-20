//////////
//
// /libsf/utils/common/cpp/include/callbacks.h
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
//     Mar.17.2016
//////
// Change log:
//     Mar.17.2016	- Initial creation
//////
//
// This file is self-contained and handles all builder algorithms.  It can be used as an include
// file for other stand-alone projects.  It was extracted from the Visual FreePro Virtual Machine.
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

struct SBmpCache;


// For the lower 64K values of flag-mapped comp->iCat codes
#define iCat(x)										(x & 0xffff)
#define iCatBits(x)									(x & _ICAT_MASK);


// Structure of parsed components on a line, tokens by another name
#define _SCOMP_DEFINED 1
struct SComp
{
	SLL				ll;												// 2-way link list

	// Information about the component
	SNode*			node;											// The node this component relates to
	SLine*			line;											// The line this component relates to
	s32				iCode;											// Refer to _ICODE_* constants
	u32				iCat;											// Refer to _ICAT_* constants, and use iCat() macro for accessing the lower portion without bit flags influencing its value
	SBgra*			color;											// Syntax highlight color
	s32				start;											// Start into the indicates line's source code
	s32				length;											// Length of the component
	s32				nbspCount;										// Number of non-breaking-spaces in this component

	// Combined components into this one
	SComp*			firstCombined;									// Combined components, like [a].[b] combined into [a.b] dot variable, keeps [.] and [b] in this
	SComp*			firstWhitespace;								// Whitespaces are removed for ease of compilation, but they persist here for rendering and reference
	SComp*			firstComment;									// Comments within a line are removed, these include "/*comments*/" and "// comments"

	// Should the syntax highlighting for this component be bold?
	bool			useBoldFont;									// Syntax highlight font should be bold?

	// For each compilation pass, components can be marked in error or warning or both
	bool			isError;										// Is this component part of an error?
	bool			isWarning;										// Is this component part of a warning?

	// Was this component allocated?
	bool			llAllocated;									// If true, it should be deleted

	// For selected components
	SBgra*			overrideSelectionBackColor;
	SBgra*			overrideSelectionForeColor;

	// If this is a character that matches something (the closest parenthesis, bracket, or brace) then this color will be populated
	SBgra*			overrideMatchingForeColor;
	SBgra*			overrideMatchingBackColor;

	// For faster rendering in source code windows
	SBmpCache*		bc;												// Holds drawn things (casks for example)
};

#define _SCOMPPARAMS_DEFINED 1
struct SCompParams
{
	s32				cpType;											// See _CP_TYPE constants

	// Based on _CP_TYPE, one of these will be populated
	union {
		SComp*		comp;
		SVariable*	var;
	};
};

// Extra info contains information about a line of source code
#define _SEXTRAINFO_DEFINED 1
struct SExtraInfo
{
	SLL			ll;

	u32			identifier;						// A registered identifier with the system for this extra info block
	u32			identifier_type;				// Application defined type, identifies what's stored in this.info.data
	SDatum		info;							// The extra info block stored for this entry


	//////////
	// Functions to called when the associated line is processed in some way
	//////
		union {
			sptr	_onAccess;					// When the line is accessed
			void	(*onAccess)					(SEM* sem, SLine* line, SExtraInfo* extra_info);
		};

		union {
			sptr	_onArrival;					// When the target implementation is sitting on this line
			void	(*onArrival)				(SEM* sem, SLine* line, SExtraInfo* extra_info);
		};

		union {
			sptr	_onUpdate;					// When the line is updated
			void	(*onUpdate)					(SEM* sem, SLine* line, SExtraInfo* extra_info);
		};


	//////////
	// Function to call before freeing an entry
	//////
		union {
			sptr		_freeInternal;			// Called to free any data in this.info
			SExtraInfo*	(*freeInternal)			(SEM* sem, SLine* line, SExtraInfo* extra_info);
		};
};

// Breakpoint types
const u32		_BREAKPOINT_NONE							= 0;	// No breakpoint
const u32		_BREAKPOINT_ALWAYS							= 1;	// Always stops
const u32		_BREAKPOINT_CONDITIONAL_TRUE				= 2;	// Breaks when the condition is true
const u32		_BREAKPOINT_CONDITIONAL_FALSE				= 3;	// Breaks when the condition is false
const u32		_BREAKPOINT_CONDITIONAL_TRUE_COUNTDOWN		= 4;	// Breaks when the condition is true, and the countdown reaches zero
const u32		_BREAKPOINT_CONDITIONAL_FALSE_COUNTDOWN		= 5;	// Breaks when the condition is false, and the countdown reaches zero
//const u32		_BREAKPOINT_CODEPOINT						= 6;	// Executes code when encountered

// Breakpoints during execution
#define _SBREAKPOINT_DEFINED 1
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

// Holds compiler data
#define _SCOMPILER_DEFINED 1
struct SCompiler
{
	// EC was designed with source code in mind, and that means a tight compiler relationship
	SLine*			parent;								// SEMLine this compiler data belongs to (parent->compilerInfo points back to here)

	// The last source code line
	SDatum*			sourceCode;							// Copy at last compile of LEFT(parent->sourceCode.data, parent->sourceCodePopulated)
	// Note:  If the source code line ended in a semicolon, the following sourceCode line(s) will be appended here on top of the semicolon until there are no more semicolon lines

	// Components compiled in prior compiler passes
	SComp*			firstComp;							// Pointer to the first component identified on this line

	// Results of compilation
	SNoteLog*		firstInquiry;						// Noted inquiry(s) on this source code line
	SNoteLog*		firstWarning;						// Noted warning(s) on this source code line
	SNoteLog*		firstNote;							// Noted note(s) on this source code line

	// Extra information
	SExtraInfo*		first_extraInfo;					// Specific to the application, also may contain triggers on errors, warnings, and notes


	//////////
	// During compilation, three steps:
	//		(1) parse		-- Parse out the components into sequenced steps
	//		(2) optimize	-- Optimize
	//		(3) generate	-- Write the sequenced engagement code for the target
	//////
	SNode*			first_nodeParse;					// (1)  Component sequencing prior to optimization
	SNode*			first_nodeOptimize;					// (2)  Component sequencing after optimization
	SNode*			first_nodeEngage;					// (3)  Final generation of engagement code steps

	u32				count_nodeParse;					// (1)  How many nodes after parsing
	u32				count_nodeOptimize;					// (2)  How many nodes after optimization
	u32				count_nodeArray;					// (3)  How many nodes in engagement code
};

#define _SLINE_DEFINED 1
struct SLine
{
	SLL				ll;												// Link list throughout
	u32				uid;											// Unique id for this line, used for undos and identifying individual lines which may move about (note this value must be isolated and separate from ll.uniqueId)
	void*			parent;											// A parent this relates to, which could be a controlling structure (like an SEM*)

	// Line information
	u32				lineNumber;										// This line's number
	bool			isNewLine;										// If the line's been added during normal editing
	SDatum*			sourceCodeOriginal;								// The original sourceCode when the line was first created, or last saved (note the length here is the total length as this value does not change, but is setup exactly when it is updated)
	SDatum*			sourceCode;										// The text on this line is LEFT(sourceCode.data, sourceCodePopulated)
	s32				sourceCode_populatedLength;						// The actual populated length of sourceCode, which may differ from sourceCode.length (which is the allocated length fo sourceCode.data)

	// Compiler information (see compiler.cpp)
	bool			forceRecompile;									// A flag that if set forces a recompile of this line
	SCompiler*		compilerInfo;									// Information about the last time this line was compiled

	// General purpose extra data
	SBreakpoint*	breakpoint;										// If there's a breakpoint here, what kind?
	SExtraInfo*		extra_info;										// Extra information about this item in the chain

	// Each render, these are updated
	u32				renderId;										// Each time it's rendered, this value is set
	RECT			rcLastRender;									// The rectangle within the parent of the last render

#if defined(_LASM_COMPILE)
	// Other usages defined by app, see /libsf/exodus/tools/lasm/lasm.cpp for an example
	SLasmLineStatus		status;
	SDatum*				fileName;
#endif
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
