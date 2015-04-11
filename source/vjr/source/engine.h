//////////
//
// /libsf/source/vjr/source/engine.h
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
//     Jul.05.2014
//////
// Change log:
//     Jul.05.2014 - Initial creation
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
	const u32	_MAX_PARAMETER_COUNT			= 26;
	const u32	_MAX_RETURN_COUNT				= 10;


//////////
// Constants for .T. and .F. settings using LOGICALX()
//
//////
	const u32	_LOGICAL_TF						= 1;
	const u32	_LOGICAL_UD						= 2;
	const u32	_LOGICAL_YN						= 3;


//////////
// Constants for date formats
//////
	const u32	_SET_DATE_AMERICAN				= 1;			// mm/dd/yy
	const u32	_SET_DATE_ANSI					= 2;			// yy.mm.dd
	const u32	_SET_DATE_BRITISH				= 3;			// dd/mm/yy
	const u32	_SET_DATE_FRENCH				= 4;			// dd/mm/yy
	const u32	_SET_DATE_GERMAN				= 5;			// dd.mm.yy
	const u32	_SET_DATE_ITALIAN				= 6;			// dd-mm-yy
	const u32	_SET_DATE_JAPAN					= 7;			// yy/mm/dd
	const u32	_SET_DATE_TAIWAN				= 8;			// yy/mm/dd
	const u32	_SET_DATE_LONG					= 9;			// Dayofweek, Month dd, yyyy
	const u32	_SET_DATE_SHORT					= 10;			// m/d/yy
	const u32	_SET_DATE_USA					= 11;			// mm-dd-yy
	const u32	_SET_DATE_DMY					= 12;			// dd/mm/yy
	const u32	_SET_DATE_MDY					= 13;			// mm/dd/yy
	const u32	_SET_DATE_YMD					= 14;			// yy/mm/dd

	// First entry
	SObject*	settings									= NULL;
	SObject*	settingsDefaults							= NULL;


//////////
// Structures used for processing
//////

	//////////
	// Changes made here must sync up with iJDebiC_thisCode()
	// BEGIN
	//////
		//////
			//
			struct SSourceCode
			{
				SFunction*		firstFunction;			// First function in the program

				SVariable*		params;					// The first parameter in the function
				SVariable*		returns;				// The first return variable declared
				SVariable*		privates;				// The first private variable declared
				SVariable*		locals;					// The first local variable declared
				SVariable*		scoped;					// The first scoped/temporary variable used by the function

				SEM*			sourceCode;				// The source code for this program
			};

			struct SThisCode
			{
				SLL				ll;

				SWindow*		win;					// Current window
				SSourceCode*	definition;				// As defined at compile time
				SSourceCode*	live;					// As exists live in this instance at this level
			};
			//
		//////
	//////
	// END
	//////////


	struct SReturnsParams
	{
		SVariable*		returns[_MAX_RETURN_COUNT];			// Return parameters
		SVariable*		params[_MAX_PARAMETER_COUNT];		// Input parameters
	};


//////////
// Forward declarations
//////
	bool					iEngine_executeStandaloneCommand		(SThisCode* thisCode, SLine* line);
	SComp*					iEngine_parseSourceCodeLine				(SThisCode* thisCode, SLine* line);
	SVariable*				iEngine_get_variableName_fromComponent	(SThisCode* thisCode, SComp* comp, bool* tlManufactured);
	SVariable*				iEngine_get_contiguousComponents		(SThisCode* thisCode, SComp* comp, bool* tlManufactured, s32 valid_iCodeArray[], s32 tnValid_iCodeArrayCount);
	SVariable*				iEngine_get_functionResult				(SThisCode* thisCode, SComp* comp);
	void					iEngine_executeSetter					(SThisCode* thisCode, cs8* name, SVariable* varOld, SVariable* varNew);
	void					iEngine_executeSetter					(SThisCode* thisCode, s8*  name, SVariable* varOld, SVariable* varNew);
	void					iEngine_error							(SThisCode* thisCode, u32 tnErrorNumber, SVariable* varRelated);

	bool					iEngine_signal_onValidate				(SThisCode* thisCode, SVariable* varTableName, SVariable* varAlias, SVariable* varCdxName, SVariable* varTag, SVariable* varcMessage, SVariable* varIsError, SVariable* varRebuildIndexRequired);
	bool					iEngine_raise_event						(SThisCode* thisCode, s32 tnEventId, SWindow* win, SObject* obj, void* p = NULL);
	bool					iEngine_set_event						(SThisCode* thisCode, s32 tnEventId, SWindow* win, SObject* obj, uptr tnEventAddress);

	s64						iEngine_update_tally					(SThisCode* thisCode, s64 tnValue);
	s64						iEngine_update_meta1					(SThisCode* thisCode, s64 tnValue);
	s64						iEngine_update_meta2					(SThisCode* thisCode, s64 tnValue);
	s64						iEngine_update_meta3					(SThisCode* thisCode, s64 tnValue);
	s64						iEngine_update_meta4					(SThisCode* thisCode, s64 tnValue);
	void					iEngine_update_meta5					(SThisCode* thisCode, SDatum* data);
	void					iEngine_update_meta6					(SThisCode* thisCode, SDatum* data);
	void					iEngine_update_meta7					(SThisCode* thisCode, SVariable* varSrc);
	void					iEngine_update_meta8					(SThisCode* thisCode, SVariable* varSrc);
	void					iEngine_update_meta9					(SThisCode* thisCode, SVariable* varSrc);

	bool					iiEngine_getParametersBetween			(SThisCode* thisCode, SComp* compLeftParen, u32* paramsFound, u32 requiredCount, u32 maxCount, SVariable* params[]);

	void					iBreakpoint_delete						(SThisCode* thisCode, SBreakpoint** breakpoint);
	SBreakpoint* 			iBreakpoint_add							(SThisCode* thisCode, SBreakpoint** breakpoint, u32 tnType);

	void					iSourceCode_delete						(SThisCode* thisCode, SSourceCode** sourceCode);