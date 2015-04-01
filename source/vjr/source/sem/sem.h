//////////
//
// /libsf/source/vjr/source/sem/sem.h
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
// Version 0.56
// Copyright (c) 2014 by Rick C. Hodgin
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
// Constants
//////
	const u32				_ECM_MINIMUM_LINE_ALLOCATION_LENGTH		= 96;		// Allocate data in 96 byte blocks


//////////
// Structs
//////
	struct SFont;
	struct SFunction;
	struct SVariable;
	struct SSourceCode;

	// When line-selecting, indicates the type
	const u32		_SEM_SELECT_MODE_NONE						= 0;
	const u32		_SEM_SELECT_MODE_LINE						= 1;
	const u32		_SEM_SELECT_MODE_COLUMN						= 2;
	const u32		_SEM_SELECT_MODE_ANCHOR						= 3;

	// Breakpoint types
	const u32		_BREAKPOINT_NONE							= 0;	// No breakpoint
	const u32		_BREAKPOINT_ALWAYS							= 1;	// Always stops
	const u32		_BREAKPOINT_CONDITIONAL_TRUE				= 2;	// Breaks when the condition is true
	const u32		_BREAKPOINT_CONDITIONAL_FALSE				= 3;	// Breaks when the condition is false
	const u32		_BREAKPOINT_CONDITIONAL_TRUE_COUNTDOWN		= 4;	// Breaks when the condition is true, and the countdown reaches zero
	const u32		_BREAKPOINT_CONDITIONAL_FALSE_COUNTDOWN		= 5;	// Breaks when the condition is false, and the countdown reaches zero

	struct SUndo
	{
		u32			uidBefore;												// The item before
		u32			uidAfter;												// The item after

		SLine*	first;													// The first SEditChain that would've gone between them
		// If multiple lines were deleted, the chain is moved here.
		// If the line was changed, the old value is here
	};

	struct SBreakpoint
	{
		// See _BREAKPOINT_* constants
		u32				type;
		bool			isUsed;											// Allocated in gBreakpoints as a bulk structure

		// If there's a countdown
		u32				countdownResetValue;							// The value the countdown will reset to once it fires, if 0 always fires
		u32				countdown;										// Countdown to 0 when it fires

		// A test condition
		SSourceCode*	conditionalCode;								// What is the conditional test expression for this breakpoint firing?

		// Code to execute when the conditionalCode returns true
		SSourceCode*	executeCode;									// Arbitrary code to execute when the breakpoint fires
																		// Explicitly:  breakpoint_always(), breakpoint_true(), breakpoint_false()
	};

	struct SEMPoint
	{
		SLine*			line;											// The actual line here
		u32				uid;											// The UID of the line
		u32				lineNumber;										// The line number
		s32				column;											// The column on this line where the selection is currently
	};


	//////////
	// SEM is short for "SEditManager"
	// Note:  This is also a reference to Sammy Edward Mitchell, the author of
	//        The SEMware Editor, TSE, without whom I would not have been as
	//        prolific in my software development.
	//////
		struct SEM
		{
			SLine*		firstLine;										// First in the chain (first->prev is NULL)
			SLine*		lastLine;										// Last in the chain (last->next is NULL)
			bool		isReadOnly;										// If read-only no changes are allowed, only navigation
			bool		stopNavigationOnNbsp;							// Do ctrl+left/right operations stop at every part of nbsp names (by default, no)?

			// If populated, this SEM is only a placeholder for this instance, and the this->reference points to the real SEM we should use
			SEM*		indirect;										// If not NULL, this SEM points to another SEM which is the real code block
			// NOTE:  Everything below is used ONLY IF INDIRECT IS NULL


		//////////
		// For display
		//////
			SLine*		line_top;										// Top item in the current view
			SLine*		line_cursor;									// Line where the cursor is
			SLine*		line_cursorLast;								// The last location before movement was made
			bool		isOverwrite;									// Are we in overwrite mode?
			bool		showLineNumbers;								// Should we render line numbers?
			bool		showCursorLine;									// Should we render the cursor line?
			bool		showEndLine;									// Should we render the end line in a different color?
			bool		isHeavyProcessing;								// When large amounts of processing will be conducted, the display can be disabled
			bool		isSourceCode;									// Is this source code?
			bool		allowMoveBeyondEndOfLine;						// Do we allow them to move beyond the end of the line?
			RECT		rcLineNumberLastRender;							// Used for mouse clicking, to determine how much we adjust

			// Loaded filename (if any)
			s8			fileName[_MAX_PATH];

			// Editing cues
			bool		hideEditCues;									// If true, will not show the changedColor or newColor
			SBgra		changedColor;									// The color when data has changed
			SBgra		newColor;										// The color when data is new

			// Percentages (values are typically 0.05f and 0.15f for 5% to 15%)
			f32			minNbspColorInfluence;							// How much minimum influence should the Nbsp color have for highlighting
			f32			maxNbspColorInfluence;							// How much maximum?

			s32			columnEdit;										// Column we're currently inputting
			s32			columnLeft;										// The column we're displaying at the left-most position (of horizontally scrolled, this will be greater than 0)
			s32			tabWidth;										// How many characters does a tab expand to?
			bool		areTabsEnforced;								// If tabs are enforced, then navigation across whitespaces lands on tab boundaries
			SFont*		font;											// Optional, if not NULL then it overrides the object's font
			u32			renderId;										// Each time it's rendered, the count is incremented.  This allows lines to be tested to see if they are actively rendered, or were previously rendered.

		
		//////////
		// Overlay highlight information to display near the cursor line
		//////
			SLine*		line_highlightBefore;							// Something to highlight before the cursor line
			SLine*		line_highlightAfter;							// Something to highlight after the cursor line


		//////////
		// Note:  If isSelectingLine, then full line select mode.
		//        If isSelectingColumn, then column select mode.
		//        If isSelectingAnchor, then anchor select mode.
		//////
			u32			selectMode;										// See _SEM_SELECT_MODE_* constants
			SEMPoint	selectOrigin;									// Where the selection started
			SEMPoint	selectEnd;										// Where the selection has ended


		//////////
		// For compiled programs
		//////
			SFunction	firstFunction;									// By default, we always create a function head for any code blocks that don't have an explicit "FUNCTION" at the top.


		//////////
		// The undo history operates in two levels:
		// (1) When going through ecm-> it is undoHistory.
		// (2) If accessing ecm->undoHistory-> then it is theUndo, which holds the undo information for that operation.
		//////
			union {
				// If referenced through ecm-> then undoHistory is the undo history for this sec
				SEM*	undoHistory;									// The lines affected by the undo

				// If referenced through ecm->undoHistory, then theUndo is the one in use here
				SUndo*	theUndo;										// If referenced through ecm->undoHistory-> then it only uses theUndo
			};
		};

	struct SEM_callback
	{
		SEM*		sem;											// The manager
		SLine*		line;											// This line

		// Values used for miscellaneous purposes
		uptr		extra1;
		uptr		extra2;

		// Callback to delete any extra information.
		// Based on the return value, both line->sourceCode and line will be deleted automatically.
		union {
			uptr			_callback;
			bool			(*callback)		(SEM_callback* ecb);
		};

	};


//////////
// Forward declarations
//////
	SEM*					iSEM_allocate						(SThisCode* thisCode, bool tlIsSourceCode);
	SBuilder*				iSEM_accumulateBuilder				(SThisCode* thisCode, SEM* sem, SLine* ecHintStart, SLine* ecHintEnd);
	bool					iSEM_saveToDisk						(SThisCode* thisCode,                     SEM* sem, cu8* tcPathname);
	bool					iSEM_loadFromDisk					(SThisCode* thisCode, SObject* objParent, SEM* sem, cu8* tcPathname, bool isSourceCode, bool tlLogIt);
	bool					iSEM_duplicate						(SThisCode* thisCode, SEM** root, SEM* chain, bool tlIncludeUndoHistory);
	void					iSEM_delete							(SThisCode* thisCode, SEM** root, bool tlDeleteSelf);
	void					iSEM_deleteChain					(SThisCode* thisCode, SEM** root, bool tlDeleteSelf);
	void					iSEM_deleteChainWithCallback		(SThisCode* thisCode, SEM** root, bool tlDeleteSelf, SEM_callback* ecb);
	u32						iSEM_renumber						(SThisCode* thisCode, SEM* sem, u32 tnStartingLineNumber);
	SLine*					iSEM_appendLine						(SThisCode* thisCode, SEM* sem, u8* tcText, s32 tnTextLength, bool tlSetNewLineFlag);
	SLine*					iSEM_insertLine						(SThisCode* thisCode, SEM* sem, u8* tcText, s32 tnTextLength, SLine* line, bool tlInsertAfter, bool tlSetNewLineFlag);
	void					iSEM_deleteLine						(SThisCode* thisCode, SEM* sem);
	SFont*					iSEM_getRectAndFont					(SThisCode* thisCode, SEM* sem, SObject* obj, RECT* rc);
	void					iSEM_getColors						(SThisCode* thisCode, SEM* sem, SObject* obj, SBgra& backColor, SBgra& foreColor);
	u32						iSEM_render							(SThisCode* thisCode, SEM* sem, SObject* obj, bool tlRenderCursorline);
	void					iSEM_render_highlightSelectedComps	(SThisCode* thisCode, SEM* sem, SComp* firstComp);
	bool					iSEM_verifyCursorIsVisible			(SThisCode* thisCode, SEM* sem, SObject* obj);
	bool					iSEM_onKeyDown_sourceCode			(SThisCode* thisCode, SWindow* win, SObject* obj, SVariable* varCtrl, SVariable* varAlt, SVariable* varShift, SVariable* varCaps, SVariable* varAscii, SVariable* varVKey, SVariable* varIsCAS, SVariable* varIsAscii);
	bool					iSEM_onKeyDown						(SThisCode* thisCode, SWindow* win, SObject* obj, SVariable* varCtrl, SVariable* varAlt, SVariable* varShift, SVariable* varCaps, SVariable* varAscii, SVariable* varVKey, SVariable* varIsCAS, SVariable* varIsAscii);
	void*					iSEM_findMate						(SThisCode* thisCode, SEM* sem, SLine* lineStart, SComp* comp);
	void					iSEM_addTooltipHighlight			(SThisCode* thisCode, SEM* sem, SLine* line, SObject* obj, s8* tcText, s32 tnTextLength, bool tlShowAbove);


	// Editor movements
	bool					iSEM_keystroke						(SThisCode* thisCode, SEM* sem, SObject* obj, u8 asciiChar);
	bool					iSEM_scroll							(SThisCode* thisCode, SEM* sem, SObject* obj, s32 deltaY, s32 deltaX);
	bool					iSEM_navigate						(SThisCode* thisCode, SEM* sem, SObject* obj, s32 deltaY, s32 deltaX);
	bool					iSEM_navigatePages					(SThisCode* thisCode, SEM* sem, SObject* obj, s32 deltaY);
	bool					iSEM_clearLine						(SThisCode* thisCode, SEM* sem, SObject* obj);
	bool					iSEM_clearToEndOfLine				(SThisCode* thisCode, SEM* sem, SObject* obj);
	bool					iSEM_clearToBeginningOfLine			(SThisCode* thisCode, SEM* sem, SObject* obj);
	bool					iSEM_toggleInsert					(SThisCode* thisCode, SEM* sem, SObject* obj);
	bool					iSEM_tabIn							(SThisCode* thisCode, SEM* sem, SObject* obj);
	bool					iSEM_tabOut							(SThisCode* thisCode, SEM* sem, SObject* obj);
	bool					iSEM_returnKey						(SThisCode* thisCode, SEM* sem, SObject* obj);
	bool					iSEM_selectAll						(SThisCode* thisCode, SEM* sem, SObject* obj);
	bool					iSEM_cut							(SThisCode* thisCode, SEM* sem, SObject* obj);
	bool					iSEM_copy							(SThisCode* thisCode, SEM* sem, SObject* obj);
	bool					iSEM_paste							(SThisCode* thisCode, SEM* sem, SObject* obj);
	bool					iSEM_navigateWordLeft				(SThisCode* thisCode, SEM* sem, SObject* obj, bool tlVerifyCursorIsVisible);
	bool					iSEM_navigateWordRight				(SThisCode* thisCode, SEM* sem, SObject* obj, bool tlVerifyCursorIsVisible);
	bool					iSEM_navigateToTopLine				(SThisCode* thisCode, SEM* sem, SObject* obj);
	bool					iSEM_navigateToEndLine				(SThisCode* thisCode, SEM* sem, SObject* obj);
	bool					iSEM_navigateToSelectStart			(SThisCode* thisCode, SEM* sem, SObject* obj, bool tlMoveByOrigin);
	bool					iSEM_navigateToSelectEnd			(SThisCode* thisCode, SEM* sem, SObject* obj, bool tlMoveByOrigin);
	bool					iSEM_rollUp							(SThisCode* thisCode, SEM* sem, SObject* obj);
	bool					iSEM_rollDown						(SThisCode* thisCode, SEM* sem, SObject* obj);
	bool					iSEM_centerCursorLine				(SThisCode* thisCode, SEM* sem, SObject* obj);
	bool					iSEM_selectLineUp					(SThisCode* thisCode, SEM* sem, SObject* obj);
	bool					iSEM_selectLineDown					(SThisCode* thisCode, SEM* sem, SObject* obj);
	bool					iSEM_selectLeft						(SThisCode* thisCode, SEM* sem, SObject* obj);
	bool					iSEM_selectRight					(SThisCode* thisCode, SEM* sem, SObject* obj);
	bool					iSEM_selectToEndOfLine				(SThisCode* thisCode, SEM* sem, SObject* obj);
	bool					iSEM_selectToBeginOfLine			(SThisCode* thisCode, SEM* sem, SObject* obj);
	bool					iSEM_selectColumnToggle				(SThisCode* thisCode, SEM* sem, SObject* obj);
	bool					iSEM_selectLineToggle				(SThisCode* thisCode, SEM* sem, SObject* obj);
	bool					iSEM_selectAnchorToggle				(SThisCode* thisCode, SEM* sem, SObject* obj);
	bool					iSEM_selectWordLeft					(SThisCode* thisCode, SEM* sem, SObject* obj);
	bool					iSEM_selectWordRight				(SThisCode* thisCode, SEM* sem, SObject* obj);
	bool					iSEM_selectToTopLine				(SThisCode* thisCode, SEM* sem, SObject* obj);
	bool					iSEM_selectToEndLine				(SThisCode* thisCode, SEM* sem, SObject* obj);
	bool					iSEM_deleteLeft						(SThisCode* thisCode, SEM* sem, SObject* obj);
	bool					iSEM_deleteRight					(SThisCode* thisCode, SEM* sem, SObject* obj);
	bool					iSEM_deleteWordLeft					(SThisCode* thisCode, SEM* sem, SObject* obj);
	bool					iSEM_deleteWordRight				(SThisCode* thisCode, SEM* sem, SObject* obj);
	bool					iSEM_navigateTo_pixelXY				(SThisCode* thisCode, SEM* sem, SObject* obj, s32 x, s32 y);
	bool					iiSEM_isBreakingCharacter			(SThisCode* thisCode, SEM* sem, SLine* line, s32 tnDeltaTest);
	void					iSEM_selectStart					(SThisCode* thisCode, SEM* sem, u32 tnSelectMode);
	bool					iSEM_isSelecting					(SThisCode* thisCode, SEM* sem);
	void					iSEM_selectStop						(SThisCode* thisCode, SEM* sem);
	void					iSEM_selectUpdateExtents			(SThisCode* thisCode, SEM* sem);
