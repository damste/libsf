//////////
//
// /libsf/utils/common/cpp/include/comps.h
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
// Version 0.01
// Copyright (c) 2016 by Rick C. Hodgin
//////
// Last update:
//     Mar.21.2016
//////
// Change log:
//     Mar.21.2016 - Initial creation
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
//////




struct SEM;
struct SLine;
struct SFunction;
struct SNode;
struct SLL;
struct SLLCallback;
struct SComp;
struct SCompCallback;
struct SCompiler;
struct SVxbStats;
struct SNoteLog;
struct SAsciiCompSearcher;
struct SStartEnd;
struct SStartEndCallback;
struct SOp;
struct SMasterList;
struct SNoteLog;




/////////
// Globals
//////
	u32						gnComps_nextUniqueId			= 0;
	CRITICAL_SECTION		cs_compsUniqueIdAccess;




//////////
// Structures
//////
	struct SCompCallback
	{
		union {
			SComp*		comp;											// Component at start, and the component to continue processing after upon exit
			s8*			text;											// Raw text (depending on when it is being processed
		};
		u32				length;											// If raw text, the length of the thing being searched, otherwise 0.
		u32				iCode;											// The iCode being queried

		// Callback callbacks for adjustment
		union {
			uptr		_insertCompByComp;
			void		(*insertCompByComp)		(SComp* compRef, SComp* compNew, bool tlInsertAfter);
		};
		union {
			uptr		_insertCompByParams;
			void		(*insertCompByParams)	(SComp* compRef, SLine* line, u32 tniCode, u32 tnStart, s32 tnLength, bool tlInsertAfter);
		};
		union {
			uptr		_deleteComps;
			void		(*deleteComps)			(SComp* comp, SLine* line);
		};
		union {
			uptr		_cloneComps;
			SComp*		(*cloneComps)			(SComp* comp, SLine* line);
		};
		union {
			uptr		_mergeComps;
			SComp*		(*mergeComps)			(SComp* comp, SLine* line, u32 tnCount, u32 tniCodeNew);
		};
	};

	struct SStartEndCallback
	{
		union
		{
			uptr	_func;
			bool	(*funcBool)	(SStartEndCallback* cb);	// This callback should return false to continue searching, or true when the item is found
			void	(*funcVoid)	(SStartEndCallback* cb);
			//////
			// Uses the following format for the callback:
			//		bool func(SStartEndCallback* cb)
			//////////
		};

		// Data items for this callback
		// Primary pointer
		union {
			void*	ptr;
			SComp*	ptrComp;
		};

		union {
			// Extra1
			uptr		ex1;
			uptr		extra1;
			uptr		extra;
			uptr		count1;
			union {
				uptr	count1_1;
				uptr	count1_2;
			};
			void*		ex1Ptr;
		};

		union {
			// Extra2
			uptr		ex2;
			uptr		extra2;
			uptr		count2;
			union {
				uptr	count2_1;
				uptr	count2_2;
			};
			void*		ex2Ptr;
		};
	};

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


//////////
// comps.cpp
//////////
	void					iComps_lex_and_parse						(SLine* line);
	void					iiVxb_free_liveCode							(SCompiler* compiler);

	SComp*					iComps_new									(SComp** compRoot, SComp* compHint, SComp* compNext, SComp* compPrev);
	u32						iiComps_getNextUid							(void);
	void					iComps_deleteAll							(SComp** compRoot);
	void					iComps_deleteAll_byLine						(SLine* line);
	void					iComps_deleteAll_byFirstComp				(SComp** firstComp);
	SComp*					iComps_duplicate							(SComp* comp);
	SComp*					iComps_delete								(SComp** compRoot);
	SComp*					iComps_delete								(SComp* comp, bool tlDeleteSelf);
	SNode*					iComps_chainLinkNodes						(SComp* compLeftMost);
	void					iComps_copyMembers							(SComp* compTo, SComp* compFrom, bool tlAllocated, bool tlCopyLl, s32 tnBackoff);
 	SComp*					iComps_translate_sourceLineTo				(SAsciiCompSearcher* tsComps, SLine* line);
 	bool					iComps_translate_toOthers					(SAsciiCompSearcher* tsComps, SComp* comp, bool tlDescendIntoFirstCombineds = true);
	bool					iComps_areAllPrecedingCompsWhitespaces		(SComp* comp);
	s32						iComps_translateToOthers_testIfMatch		(cu8* tcHaystack, cu8* tcNeedle, s32 tnLength);
	SComp*					iComps_findNextBy_iCode						(SComp* comp, s32 tniCode, SComp** compLastScanned);
	SComp*					iComps_activeComp_inSEM						(SEM* sem);
	bool					iComps_get_mateDirection						(SComp* comp, s32* tnMateDirection);
	bool					iComps_findClosest_parensBracketsBraces		(SComp* compRelative, SComp* compStart, SComp** compPBBLeft, SComp** compPBBRight);
	bool					iComps_isParensBracketsBraces				(SComp* comp);
	bool					iComps_isMateOf								(SComp* compTest, s32 tniCodeMate);
	SComp*					iComps_skipPast_iCode						(SComp* comp, s32 tniCode);
	SComp*					iComps_skipTo_iCode							(SComp* comp, s32 tniCode);
	SComp*					iComps_getNext_afterDot						(SComp* comp);
	SComp*					iComps_Nth									(SComp* comp, s32 tnCount = 1, bool tlMoveBeyondLineIfNeeded = true);
	SComp*					iComps_Nth_lineOnly							(SComp* comp, s32 tnCount = 1);
	bool					iComps_scanForward_withCallback				(SComp* comp, SCallback* cb, bool tlSkipFirst = false, bool tlMoveBeyondLineIfNeeded = true, uptr _func = NULL);
	u32						iComps_combineN								(SComp* comp, u32 tnCount, s32 tnNew_iCode, u32 tnNew_iCat, SBgra* newColor, SComp** compMigrateRefs = NULL);
	u32						iComps_combine_adjacent						(SComp* compLeftmost, s32 tniCode, u32 tniCat, SBgra* tnColor, s32 valid_iCodeArray[], s32 tnValid_iCodeArrayCount);
	u32						iComps_combine_adjacentAlphanumeric			(SLine* line);
	u32						iComps_combine_adjacentNumeric				(SLine* line);
	u32						iComps_combine_adjacentLeadingPipesigns		(SLine* line);
	u32						iComps_combineAll_between					(SLine* line, s32 tniCodeNeedle,		s32 tniCodeCombined,											SBgra* syntaxHighlightColor);
	u32						iComps_combineAll_betweenTwo				(SLine* line, s32 tniCodeNeedleLeft,	s32 tniCodeNeedleRight,		s32 tniCodeCombined,	u32 tniCat, SBgra* syntaxHighlightColor, bool tlUseBoldFont);
	u32						iComps_combineAll_after						(SLine* line, s32 tniCodeNeedle);
	u32						iComps_deleteAll_after						(SLine* line, s32 tniCodeNeedle);
	SComp*					iComps_migrate								(SComp** compSource, SComp** compDestination, SComp* compToMove);
	SLine*					iComps_copyComps_toNewLines					(SComp* compStart, SComp* compEnd, bool tlLeftJustifyStart, bool tlSkipBlankLines, SLine** lineLast);
	u32						iComps_remove_leadingWhitespaces			(SLine* line);
	u32						iComps_remove_whitespaces					(SLine* line);
	void					iComps_remove_startEndComments				(SLine* line);
	s32						iComps_truncate_atComments					(SLine* line);
	void					iComps_combine_casks						(SLine* line);
	void					iComps_fixup_naturalGroupings				(SLine* line);
	s32						iComps_unescape_iCodes						(SComp* compStart, s32 tniCode1, s32 tniCode2, s32 tniCode3, s32 tniCodeEscape = _ICODE_BACKSLASH);
	s32						iComps_copyToLine_untilEndOfLine			(SLine* line, SComp* compStart, SComp* compEnd, bool tlMakeReferences);
	s32						iComps_copyTo_withCallback					(SLine* line, SComp* compStart, SCallback* cb, bool tlMakeReferences);
	bool					iiComps_areCompsAdjacent					(SComp* compLeft, SComp* compRight);
	s32						iiComps_get_charactersBetween				(SComp* compLeft, SComp* compRight);
	s32						iComps_getAs_s32							(SComp* comp);
	s64						iComps_getAs_s64							(SComp* comp);
	f64						iComps_getAs_f64							(SComp* comp);
	s32						iiComps_getAs_s32							(SComp* comp);
	s64						iiComps_getAs_s64							(SComp* comp);
	f64						iiComps_getAs_f64							(SComp* comp);
	SDatum*					iiComps_populateAs_datum					(SDatum* datum, SComp* comp, SVariable** varSys2015);
	s32						iComps_getContiguousLength					(SComp* comp, s32 valid_iCodeArray[], s32 tnValid_iCodeArrayCount, s32* tnCount);
	u32						iComps_count								(SComp* comp);
	bool					iiComps_validate							(SComp* comp, s32 valid_iCodeArray[], s32 tnValid_iCodeArrayCount);
	bool					iiComps_isAlphanumeric_byContent			(SComp* comp);
	#define					iiComps_isAlphanumeric_by_iCode(iCode)		(iCode == _ICODE_ALPHA || iCode == _ICODE_ALPHANUMERIC)
	#define					iiComps_isNumeric(iCode)					(iCode == _ICODE_NUMERIC)
	#define					iiComps_isComment(iCode)					(iCode == _ICODE_COMMENT || iCode == _ICODE_LINE_COMMENT)
	s8*						iComps_visualize							(SComp* comp, s32 tnCount, s8* outputBuffer, s32 tnBufferLength, bool tlUseDefaultCompSearcher, SAsciiCompSearcher* tsComps1, SAsciiCompSearcher* tsComps2);
	s8*						iiComps_visualize_lookup_iCode				(s32 tniCode);

	u32						iBreakoutAsciiTextDataIntoLines_ScanLine	(s8* tcData, u32 tnMaxLength, u32* tnLength, u32* tnWhitespaces);
	bool					iFindFirstOccurrenceOfAsciiCharacter		(s8* tcHaystack, u32 tnHaystackLength, s8 tcNeedle, u32* tnPosition);
	u32						iSkip_whitespaces							(s8* tcData, u32 tnMaxLength);
	u32						iSkip_toCrLf								(s8* tcData, u32 tnMaxLength, u32* tnCRLF_Length);

	s32						iComps_xlatToComps_withTest					(cu8* tcHaystack, cu8* tcNeedle, s32 tnLength);
	bool					iiComps_xlatToOthers_callback				(SStartEndCallback* cb);
	void					iiComps_xlatToOthers_callback__insertCompByCompCallback		(SComp* compRef, SComp* compNew, bool tlInsertAfter);
	void					iiComps_xlatToOthers_callback__insertCompByParamsCallback	(SComp* compRef, SLine* line, u32 tniCode, u32 tnStart, s32 tnLength, bool tlInsertAfter);
	void					iiComps_xlatToOthers_callback__deleteCompsCallback			(SComp* comp, SLine* line);
	SComp*					iiComps_xlatToOthers_callback__cloneCompsCallback			(SComp* comp, SLine* line);
	SComp*					iiComps_xlatToOthers_callback__mergeCompsCallback			(SComp* comp, SLine* line, u32 tnCount, u32 tniCodeNew);

	// Error and warning functions
	void					iComp_appendError							(SComp* comp, u32 tnErrorNum,   cu8* tcMessage);
	void					iComp_appendWarning							(SComp* comp, u32 tnWarningNum, cu8* tcMessage);
	void					iComp_reportWarningsOnRemainder				(SComp* comp, u32 tnWarningNum, cu8* tcMessage);

	// Line functions
	SLine*					iLine_createNew								(bool tlAllocCompilerInfo);
	SLine*					iLine_appendNew								(SLine* line, bool tlAllocCompilerInfo);
	SLine*					iLine_insertNew								(SLine* lineRef, bool tlAllocCompilerInfo, bool tlAfter);
	void					iLine_appendError							(SLine* line, u32 tnErrorNum,   cu8* tcMessage, u32 tnStartColumn, u32 tnLength);
	void					iLine_appendWarning							(SLine* line, u32 tnWarningNum, cu8* tcMessage, u32 tnStartColumn, u32 tnLength);
	bool					iLine_scanComps_forward_withCallback		(SLine* line, SComp* comp, SCallback* cb, bool tlSkipFirst);
	s32						iLines_unescape_iCodes						(SLine* lineStart, s32 tniCode1, s32 tniCode2, s32 tniCode3, s32 tniCodeEscape = _ICODE_BACKSLASH);

	s32						iLine_migrateLines							(SLine** linesFrom, SLine* lineTarget);

	SComp*					iLine_Nth_comp								(SLine* line, s32 tnCount = 1, bool tlMoveBeyondLineIfNeeded = true);
	//
	SLine*					iLine_copyComps_toNewLines_untilTerminating					(SLine* lineStart, SComp* compStart, s32 tniCodeContinuation, bool tlLeftJustifyStart, bool tlSkipBlankLines, SCallback* cb);
	bool					iiLine_copyComps_toNewLines_untilTerminating__callback		(SCallback* cb);
	//
	s32						iiLine_skipTo_nextComp						(SLine** lineProcessing, SComp** compProcessing);
	s32						iiLine_skipTo_prevComp						(SLine** lineProcessing, SComp** compProcessing);

	// Compiler functions
	SCompiler*				iCompiler_allocate							(SLine* parent);
	void					iCompiler_delete							(SCompiler** compilerInfoRoot, bool tlDeleteSelf);

	// Compile note functions
	SNoteLog*				iNoteLog_create								(SNoteLog** noteRoot, SLine* line, u32 tnStart,	u32 tnEnd,	u32 tnNumber, cu8* tcMessage);
	SNoteLog*				iNoteLog_create								(SNoteLog** noteRoot, SComp* comp, u32 tnNumber, cu8* tcMessage);
	void					iNoteLog_removeAll							(SNoteLog** noteRoot);
