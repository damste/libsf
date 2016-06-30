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


struct SEM;
struct SBreakpoint;
struct SComp;
struct SFont;
struct SFunction;
struct SVariable;
struct SSourceCode;
struct SExtraInfo;
struct SWindow;
struct SObject;
struct SVariable;


#include "sem_extra_info.h"
#include "sem_line.h"


//////////
// Constants
//////
	const u32		_SEM_MINIMUM_LINE_ALLOCATION_LENGTH			= 96;		// Allocate data in 96 byte blocks


//////////
// Structs
//////
	// When line-selecting, indicates the type
	const u32		_SEM_SELECT_MODE_NONE						= 0;
	const u32		_SEM_SELECT_MODE_LINE						= 1;
	const u32		_SEM_SELECT_MODE_COLUMN						= 2;
	const u32		_SEM_SELECT_MODE_ANCHOR						= 3;

	struct SUndo
	{
		u32			uidBefore;												// The item before
		u32			uidAfter;												// The item after

		SLine*	first;													// The first SEditChain that would've gone between them
		// If multiple lines were deleted, the chain is moved here.
		// If the line was changed, the old value is here
	};



//////////
// Forward declarations
//////
	SEM*					iSEM_allocate						(bool tlIsSourceCode);
	SBuilder*				iSEM_accumulateBuilder				(SEM* sem, SLine* ecHintStart, SLine* ecHintEnd);
	bool					iSEM_saveToDisk						(                    SEM* sem, cs8* tcPathname);
	bool					iSEM_saveToDisk						(                    SEM* sem, cu8* tcPathname);
	bool					iSEM_load_fromDisk					(SObject* objParent, SEM* sem, cs8* tcPathname, bool isSourceCode, bool tlLogIt);
	bool					iSEM_load_fromDisk					(SObject* objParent, SEM* sem, cu8* tcPathname, bool isSourceCode, bool tlLogIt);
	bool					iSEM_load_fromMemory				(SObject* objParent, SEM* sem, SDatum* datum,   bool isSourceCode, bool tlLogIt);
	bool					iSEM_duplicate						(SEM** root, SEM* chain, bool tlIncludeUndoHistory);
	SEM*					iSEM_duplicate_asReference			(SEM* sem);
	void					iSEM_delete							(SEM** root, bool tlDeleteSelf);
	void					iSEM_deleteChain					(SEM** root, bool tlDeleteSelf);
	void					iSEM_deleteChainWithCallback		(SEM** root, bool tlDeleteSelf, SEM_callback* ecb);
	u32						iSEM_renumber						(SEM* sem, u32 tnStartingLineNumber);
	SLine*					iSEM_appendLine						(SEM* sem, SLine* line, bool tlSetNewLineFlag);
	SLine*					iSEM_appendLine						(SEM* sem, u8* tcText, s32 tnTextLength, bool tlSetNewLineFlag);
	SLine*					iSEM_insertLine						(SEM* sem, u8* tcText, s32 tnTextLength, SLine* line, bool tlInsertAfter, bool tlSetNewLineFlag);
	void					iSEM_deleteLine						(SEM* sem);
	SFont*					iSEM_getRectAndFont					(SEM* sem, SObject* obj, RECT* rc);
	void					iSEM_getColors						(SEM* sem, SObject* obj, SBgra& backColor, SBgra& foreColor);
#ifdef _VJR_COMPILE
	void*					iSEM_findMate						(SEM* sem, SLine* lineStart, SComp* comp);
	void					iSEM_addTooltipHighlight			(SEM* sem, SLine* line, SObject* obj, s8* tcText, s32 tnTextLength, bool tlShowAbove);
	u32						iSEM_render							(SEM* sem, SObject* obj, bool tlRenderCursorline);
	void					iSEM_render_highlightSelectedComps	(SEM* sem, SComp* firstComp);
	bool					iSEM_onKeyDown_sourceCode			(SWindow* win, SObject* obj, SVariable* varCtrl, SVariable* varAlt, SVariable* varShift, SVariable* varCaps, SVariable* varAscii, SVariable* varVKey, SVariable* varIsCAS, SVariable* varIsAscii);
	bool					iSEM_onKeyDown						(SWindow* win, SObject* obj, SVariable* varCtrl, SVariable* varAlt, SVariable* varShift, SVariable* varCaps, SVariable* varAscii, SVariable* varVKey, SVariable* varIsCAS, SVariable* varIsAscii);
#endif
	bool					iSEM_verifyCursorIsVisible			(SEM* sem, SObject* obj);


	// Editor movements
	bool					iSEM_keystroke						(SEM* sem, SObject* obj, u8 asciiChar, uptr _postParseFunc_ifNeeded);
	bool					iSEM_scroll							(SEM* sem, SObject* obj, s32 deltaY, s32 deltaX);
	bool					iSEM_navigate						(SEM* sem, SObject* obj, s32 deltaY, s32 deltaX);
	bool					iSEM_navigatePages					(SEM* sem, SObject* obj, s32 deltaY);
	bool					iSEM_clearLine						(SEM* sem, SObject* obj);
	bool					iSEM_clearToEndOfLine				(SEM* sem, SObject* obj);
	bool					iSEM_clearToBeginningOfLine			(SEM* sem, SObject* obj);
	bool					iSEM_toggleInsert					(SEM* sem, SObject* obj);
	bool					iSEM_tabIn							(SEM* sem, SObject* obj);
	bool					iSEM_tabOut							(SEM* sem, SObject* obj);
	bool					iSEM_returnKey						(SEM* sem, SObject* obj);
	bool					iSEM_selectAll						(SEM* sem, SObject* obj);
	bool					iSEM_cut							(SEM* sem, SObject* obj);
	bool					iSEM_copy							(SEM* sem, SObject* obj);
	bool					iSEM_paste							(SEM* sem, SObject* obj);
	bool					iSEM_navigateWordLeft				(SEM* sem, SObject* obj, bool tlVerifyCursorIsVisible);
	bool					iSEM_navigateWordRight				(SEM* sem, SObject* obj, bool tlVerifyCursorIsVisible);
	bool					iSEM_navigateToTopLine				(SEM* sem, SObject* obj);
	bool					iSEM_navigateToEndLine				(SEM* sem, SObject* obj);
	bool					iSEM_navigateToSelectStart			(SEM* sem, SObject* obj, bool tlMoveByOrigin);
	bool					iSEM_navigateToSelectEnd			(SEM* sem, SObject* obj, bool tlMoveByOrigin);
	bool					iSEM_rollUp							(SEM* sem, SObject* obj);
	bool					iSEM_rollDown						(SEM* sem, SObject* obj);
	bool					iSEM_centerCursorLine				(SEM* sem, SObject* obj);
	bool					iSEM_selectLineUp					(SEM* sem, SObject* obj);
	bool					iSEM_selectLineDown					(SEM* sem, SObject* obj);
	bool					iSEM_selectLeft						(SEM* sem, SObject* obj);
	bool					iSEM_selectRight					(SEM* sem, SObject* obj);
	bool					iSEM_selectToEndOfLine				(SEM* sem, SObject* obj);
	bool					iSEM_selectToBeginOfLine			(SEM* sem, SObject* obj);
	bool					iSEM_selectColumnToggle				(SEM* sem, SObject* obj);
	bool					iSEM_selectLineToggle				(SEM* sem, SObject* obj);
	bool					iSEM_selectAnchorToggle				(SEM* sem, SObject* obj);
	bool					iSEM_selectWordLeft					(SEM* sem, SObject* obj);
	bool					iSEM_selectWordRight				(SEM* sem, SObject* obj);
	bool					iSEM_selectToTopLine				(SEM* sem, SObject* obj);
	bool					iSEM_selectToEndLine				(SEM* sem, SObject* obj);
	bool					iSEM_deleteLeft						(SEM* sem, SObject* obj, uptr _postParseFunc_ifNeeded);
	bool					iSEM_deleteRight					(SEM* sem, SObject* obj, uptr _postParseFunc_ifNeeded);
	bool					iSEM_deleteWordLeft					(SEM* sem, SObject* obj, uptr _postParseFunc_ifNeeded);
	bool					iSEM_deleteWordRight				(SEM* sem, SObject* obj, uptr _postParseFunc_ifNeeded);
	bool					iSEM_navigateTo_pixelXY				(SEM* sem, SObject* obj, s32 x, s32 y);
	bool					iiSEM_isBreakingCharacter			(SEM* sem, SLine* line, s32 tnDeltaTest);
	void					iSEM_selectStart					(SEM* sem, u32 tnSelectMode);
	bool					iSEM_isSelecting					(SEM* sem);
	void					iSEM_selectStop						(SEM* sem);
	void					iSEM_selectUpdateExtents			(SEM* sem);
