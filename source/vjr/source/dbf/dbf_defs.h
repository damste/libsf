//////////
//
// /libsf/source/vjr/source/dbf/dbf_defs.h
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
// Copyright (c) 2014-2017 by Rick C. Hodgin
//////
// Last update:
//     Nov.02.2014
//////
// Change log:
//     Nov.02.2014 - Initial creation
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



struct SFieldRecord1;
struct SFieldRecord2;


//////////
//
// Used in index FOR clause processing
//
//////
	const u32		_FOR_CLAUSE_OPS_EQUAL_ROW_DATA						= (1 << 0);
	const u32		_FOR_CLAUSE_OPS_LESS_THAN_ROW_DATA					= (1 << 1);
	const u32		_FOR_CLAUSE_OPS_GREATER_THAN_ROW_DATA				= (1 << 2);

	const u32		_FOR_CLAUSE_OPS_EQUAL_TEMPORARY						= (1 << 3);
	const u32		_FOR_CLAUSE_OPS_LESS_THAN_TEMPORARY					= (1 << 4);
	const u32		_FOR_CLAUSE_OPS_GREATER_THAN_TEMPORARY				= (1 << 5);

	const u32		_FOR_CLAUSE_OPS_TEMPORARY_COPY_TO					= (1 << 27);
	const u32		_FOR_CLAUSE_OPS_TEMPORARY_SWAP_ENDIAN				= (1 << 28);
	const u32		_FOR_CLAUSE_OPS_TEMPORARY_SIGN_FLIP_F32				= (1 << 29);
	const u32		_FOR_CLAUSE_OPS_TEMPORARY_SIGN_FLIP_F64				= (1 << 30);
	const u32		_FOR_CLAUSE_OPS_NOT									= (1 << 31);
	// Note:  See iCdx_isForClauseComplex() for their setup through parsing, and iiDbf_forClause_isRowIncluded() for their use in filtering rows

	const u32		_FOR_CLAUSE_SUBITEM_TYPE_ALPHANUMERIC				= 1;	// a_zA_Z0_9
	const u32		_FOR_CLAUSE_SUBITEM_TYPE_NUMERIC					= 2;	// 0_9.+-
	const u32		_FOR_CLAUSE_SUBITEM_TYPE_COMPARATOR					= 3;	// =<>!#
	const u32		_FOR_CLAUSE_SUBITEM_TYPE_QUOTE						= 4;	// " or ' at start with a mated " or ' at end
	const u32		_FOR_CLAUSE_SUBITEM_TYPE_NOT						= 5;	// !, NOT, or .NOT.
	const u32		_FOR_CLAUSE_SUBITEM_TYPE_AND						= 6;	// .AND. or AND
	const u32		_FOR_CLAUSE_SUBITEM_TYPE_OR							= 7;	// .OR. or OR
	const u32		_FOR_CLAUSE_SUBITEM_TYPE_CONSTANT					= 8;	// A constant value
	const u32		_FOR_CLAUSE_SUBITEM_TYPE_LOGICAL_CONSTANT			= 9;	// A .t. or .f.
	const u32		_FOR_CLAUSE_SUBITEM_TYPE_INVALID					= 999;	// Who knows? :-)

	const u32		_FOR_CLAUSE_SUBITEM_ALLOCATION_BLOCK_SIZE			= 20;
	const u32		_FOR_CLAUSE_OP_ALLOCATION_BLOCK_SIZE				= 20;
	const u32		_FOR_CLAUSE_TEMP_ALLOCATION_BLOCK_SIZE				= 20;

	// For index keys
	const u32		_DBF_INDEX_FIXUP_NONE								= 0;
	const u32		_DBF_INDEX_FIXUP_SWAP_ENDIAN						= 1;
	const u32		_DBF_INDEX_FIXUP_FLOAT_DOUBLE						= 2;
	const u32		_DBF_INDEX_FIXUP_DATETIME							= 3;
	const u32		_DBF_INDEX_FIXUP_DATE								= 4;
	const u32		_DBF_INDEX_FIXUP_LOGICAL							= 5;
	const u32		_DBF_INDEX_FIXUP_DELETED							= 6;
	const u32		_DBF_INDEX_FIXUP_NUMERIC							= 8;
	// Upper 4 bits are allocated for additive operations
	const u32		_DBF_INDEX_FIXUP_MASK								= 0x0fffffff;
	const u32		_DBF_INDEX_FIXUP_NULL								= 1 << 29;
	const u32		_DBF_INDEX_FIXUP_UPPER								= 1 << 30;
	const u32		_DBF_INDEX_FIXUP_LOWER								= 1 << 31;




//////////
//
// DBF related
// Note:  All CDX related functions are defined in cdx_defs.h
//
/////
	// Startup and shutdown
	void 				iDbf_startup									(bool tlFirstRun);
	void 				iDbf_shutdown									(void);

	// User interaction functions
	bool				iiDbf_continueWithLockOperation					(SDiskLockCallback* dcb, s32 tnAttempts, s32 tnMillisecondsSpentThusFar);

	s32					iDbf_translateError								(s32 tnDbfErrorCode);

	// DBF functions
	uptr				iDbf_open										(SVariable* table,	SVariable* alias,	bool tlExclusive, bool tlAgain, bool tlValidate, bool tlDescending, bool tlVisualize, bool tlJournal, bool tlNoUpdate);
	uptr				iDbf_open										(cs8* table,		cs8* alias,			bool tlExclusive, bool tlAgain, bool tlValidate, bool tlDescending, bool tlVisualize, bool tlJournal, bool tlNoUpdate);
	uptr				iDbf_openRemote									(s8* connString);
	uptr				iDbf_cacheAllRowData							(SWorkArea* wa);
	uptr				iDbf_close										(SWorkArea* wa);
	uptr				iDbf_hasCdx										(SWorkArea* wa);
	bool				iDbf_hasDbc										(u32 tnWorkArea, SWorkArea** dbc = NULL, s32* tnError = NULL);
	bool				iDbf_isWorkAreaValid							(SWorkArea* wa, cu8** tcSpecialWorkAreaKeyName = NULL);
	bool				iDbf_isWorkAreaUsed								(SWorkArea* wa, bool* tlIsValidWorkArea);
	bool				iDbf_isWorkAreaLetter							(SVariable* var);
	sptr				iDbf_set_workArea_current						(u32 tnWorkArea = -1,							cu8* tcSpecialKeyName = NULL);
	sptr				iDbf_get_workArea_current						(												cu8* tcSpecialKeyName = NULL);
	SWorkArea*			iDbf_get_workArea_current_wa					(u32 tnWorkArea = -1,							cu8* tcSpecialKeyName = NULL);
	sptr				iDbf_get_workArea_lowestFree					(												cu8* tcSpecialKeyName = NULL);
	sptr				iDbf_get_workArea_highestFree					(												cu8* tcSpecialKeyName = NULL);
	sptr				iDbf_get_workArea_byTablePathname				(SVariable* varPathname,						cu8* tcSpecialKeyName = NULL);
	sptr				iDbf_get_workArea_byTablePathname				(cs8* varPathname,								cu8* tcSpecialKeyName = NULL);
	sptr				iDbf_get_workArea_byAlias_byVar					(SWorkArea** wa, SVariable* var,				cu8* tcSpecialKeyName = NULL);
	sptr				iDbf_get_workArea_byAlias_byComp				(SWorkArea** wa, SComp* comp,					cu8* tcSpecialKeyName = NULL);
	sptr				iDbf_get_workArea_byAlias_byName				(SWorkArea** wa, s8* tcName, u32 tnNameLength,	cu8* tcSpecialKeyName = NULL);
	sptr				iDbf_get_workArea_byAlias_byVar					(SVariable* var,								cu8* tcSpecialKeyName = NULL, SWorkArea** waBase = NULL);
	sptr				iDbf_get_workArea_byAlias_byComp				(SComp* comp,									cu8* tcSpecialKeyName = NULL, SWorkArea** waBase = NULL);
	sptr				iDbf_get_workArea_byAlias_byName				(s8* tcName, u32 tnNameLength,					cu8* tcSpecialKeyName = NULL, SWorkArea** waBase = NULL);
	SVariable*			iDbf_get_alias_fromPathname						(SVariable* varPathname,						cu8* tcSpecialKeyName = NULL);
	s8*					iDbf_get_tagName								(SWorkArea* wa, s8* tagName_32, s32* tnError = NULL);

	// Field marks (to indicate only certain fields should be operated on
	bool				iDbf_markFields_clearAll						(SWorkArea* wa);
	bool				iDbf_markFields_setAll							(SWorkArea* wa);
	bool				iDbf_markFields_setField						(SWorkArea* wa, cu8* fieldName, s32 fieldNameLength = -1);
	bool				iDbf_markFields_clearField						(SWorkArea* wa, cu8* fieldName, s32 fieldNameLength = -1);
	bool				iDbf_markFields_field							(SWorkArea* wa, cu8* fieldName, s32 fieldNameLength = -1, bool tlSetValue = true);

	sptr				iDbf_gotoRecord									(SWorkArea* wa, s32 recordNumber, bool tlForceDbf = false, bool* error = NULL, u32* errorNum = NULL, SBuilder* errorDetails = NULL);
	sptr				iDbf_gotoTop									(SWorkArea* wa, bool tlForceDbf = false);
	sptr				iDbf_skip										(SWorkArea* wa, s32 tnDelta, bool tlForceDbf = false, s32 tnTagIndex = -1);
	sptr				iDbf_writeChanges								(SWorkArea* wa, bool* error = NULL, u32* errorNum = NULL);
	bool				iiDbf_readMemo									(SWorkArea* wa, SFieldRecord2* fr2Ptr);
	bool				iiDbf_writeMemo									(SWorkArea* wa, SFieldRecord2* fr2Ptr);
	sptr				iiDbf_flush_anyChanges							(SWorkArea* wa, bool* error = NULL, u32* errorNum = NULL);

	uptr				iDbf_getFieldCount								(SWorkArea* wa);
	u32					iiDbf_getFieldCount								(SWorkArea* wa);
	sptr				iDbf_getReccount								(SWorkArea* wa);
	u32					iiDbf_getReccount								(SWorkArea* wa);

	uptr				iDbf_getField_name								(SWorkArea* wa, u32 fieldNumber, u8* dest, u32 destLength);
	uptr				iDbf_getField_type								(SWorkArea* wa, u32 fieldNumber, u8* dest, u32 destLength);
	uptr				iDbf_getField_type_verbose						(SWorkArea* wa, u32 fieldNumber, u8* dest, u32 destLength);
	uptr				iDbf_getField_type_extended						(SWorkArea* wa, u32 fieldNumber, u8* dest, u32 destLength);
	uptr				iDbf_getField_length							(SWorkArea* wa, u32 fieldNumber, u8* dest, u32 destLength);
	uptr				iDbf_getIndex_length							(SWorkArea* wa, u32 fieldNumber, u8* dest, u32 destLength);
	uptr				iDbf_getField_decimals							(SWorkArea* wa, u32 fieldNumber, u8* dest, u32 destLength);
	uptr				iDbf_getField_isBinary							(SWorkArea* wa, u32 fieldNumber, u8* dest, u32 destLength);
	uptr				iDbf_getField_allowNulls						(SWorkArea* wa, u32 fieldNumber, u8* dest, u32 destLength);
	uptr				iDbf_getNull_flag								(SWorkArea* wa, u32 fieldNumber, u8* dest, u32 destLength);
	bool				iDbf_getNull_offsetAndMask						(SWorkArea* wa, u32 fieldNumber, u32* nullOffset, u8* nullMask);
	uptr				iDbf_getField_autoinc_next						(SWorkArea* wa, u32 fieldNumber, u8* dest, u32 destLength);
	uptr				iDbf_getField_autoinc_step						(SWorkArea* wa, u32 fieldNumber, u8* dest, u32 destLength);
	s8*					iDbf_getField_data								(SWorkArea* wa, u32 fieldNumber, u8* dest, u32 destLength);
	SVariable*			iDbf_getField_data_asVar						(SWorkArea* wa, SFieldRecord2* fptr2, bool tlCreateAsReference);
	s8*					iiDbf_getField_data2							(SWorkArea* wa, u32 fieldNumber, u8* dest, u32 destLength, bool tlRetrieveAsIndexKey);
	uptr				iDbf_getField_dataOffset						(SWorkArea* wa, u32 fieldNumber);
	uptr				iDbf_getIndexFixupOp							(SWorkArea* wa, u32 fieldNumber);
	uptr				iDbf_setField_data								(SWorkArea* wa, s32 fieldNumber, u8* dest, u32 destLength, bool tlPartOfATransaction);
	uptr				iDbf_getField_validateContents					(SWorkArea* wa, u32 fieldNumber, u8* src, u32 srcLength);

	SDatum*				iDbf_listRecord									(SWorkArea* wa, SDbfRender* render, bool tlHonorFieldMarks = true, bool tlRenderHeaderRow = false, bool tlResetPrefixAndPostfix = false, bool tlEnquoteCharacter = false, SObject* settings = NULL, SCallback* cb = NULL, sptr _fillCharFunc = null0);

	SFieldRecord1*		iDbf_getField_byName1							(SWorkArea* wa, cu8* fieldName);
	SFieldRecord1*		iDbf_getField_byNumber1							(SWorkArea* wa, u32 fieldNumber);
	SFieldRecord2*		iDbf_getField_byName2							(SWorkArea* wa, cu8* fieldName);
	SFieldRecord2*		iDbf_getField_byNumber2							(SWorkArea* wa, u32 fieldNumber);
	SVariable*			iDbf_getField_byName2_asVariable				(SWorkArea* wa, u8* fieldName, u32 fieldNameLength, bool tlCreateAsReference);
	u8					iDbf_getField_type								(SWorkArea* wa, u8* keyExpression, bool* swapEndians, bool* needsSignBitToggled);
	uptr				iDbf_getFieldExpression_name					(u8* expression, const u8* foundFieldName);


//////////
// Container functions
//////
	void				iiDbc_lookupTableField							(SWorkArea* wa, bool* tlIsValid, bool tlExcusive);
	void				iiDbf_getRelativeDbc							(SWorkArea* wa, s8* dbcName);
	s32					iDbc_validate									(SWorkArea* wa, bool tlRecover, SEM* sem, SWindow* win);


//////////
// FOR clauses used to test row data for inclusion in various operations
//////
	SForClause*			iDbf_forClause_allocate							(SForClause** tsFor);
	void				iDbf_forClause_delete							(SForClause** tsFor);
	bool				iiDbf_forClause_isRowIncluded					(SWorkArea* wa, SForClause* tsFor);
	bool				iiDbf_forClause_subitems_parse					(SCdxHeader* head, SForClause* tsFor);
	SForSubItem* 		iiDbf_forClause_subitems_appendItem				(SForClause* tsFor);
	SForOp* 			iiDbf_forClause_ops_appendItem					(SForClause* tsFor);
	uptr				iiDbf_forClause_temp_appendConstant				(SForClause* tsFor, s8* tcData, u32 tnDataLength);


//////////
// Structure tests from iDbf_open() for specific file types
//////
	SFieldRecord2*		iDbf_validate_fieldExists						(SWorkArea* wa, cu8* tcFieldName, cs8* tcFieldType, s32 length, s32 decimals);
	bool				iDbf_validate_isDbc								(SWorkArea* wa);
	bool				iDbf_validate_isScx								(SWorkArea* wa);
	bool				iDbf_validate_isVcx								(SWorkArea* wa);
	bool				iDbf_validate_isFrx								(SWorkArea* wa);
	bool				iDbf_validate_isMnx								(SWorkArea* wa);


//////////
// Rendering algorithms for individual fields
//////
	void				iiDbf_populateRender							(SObject* settings, SDbfRender* render, SWorkArea* wa);
	void				iiDbf_render_headerName							(SFieldRecord2* field2Ptr);
	s32					iiDbf_render_i									(SDatum* row, SFieldRecord2* field2Ptr, SDbfRender* render);
	s32					iiDbf_render_y									(SDatum* row, SFieldRecord2* field2Ptr, SDbfRender* render);
	s32					iiDbf_render_b									(SDatum* row, SFieldRecord2* field2Ptr, SDbfRender* render);
	s32					iiDbf_render_d									(SDatum* row, SFieldRecord2* field2Ptr, SDbfRender* render);
	s32					iiDbf_render_t									(SDatum* row, SFieldRecord2* field2Ptr, SDbfRender* render);
	s32					iiDbf_render_l									(SDatum* row, SFieldRecord2* field2Ptr, SDbfRender* render);
	s32					iiDbf_render_f									(SDatum* row, SFieldRecord2* field2Ptr, SDbfRender* render);
	s32					iiDbf_render_n									(SDatum* row, SFieldRecord2* field2Ptr, SDbfRender* render);
	s32					iiDbf_render_m									(SDatum* row, SFieldRecord2* field2Ptr, SDbfRender* render);
	s32					iiDbf_render_w									(SDatum* row, SFieldRecord2* field2Ptr, SDbfRender* render);
	s32					iiDbf_render_g									(SDatum* row, SFieldRecord2* field2Ptr, SDbfRender* render);
	s32					iiDbf_render_q									(SDatum* row, SFieldRecord2* field2Ptr, SDbfRender* render);
	s32					iiDbf_render_v									(SDatum* row, SFieldRecord2* field2Ptr, SDbfRender* render);
	s32					iiDbf_render_c									(SDatum* row, SFieldRecord2* field2Ptr, SDbfRender* render);
	s32					iiDbf_render_unk								(SDatum* row, SFieldRecord2* field2Ptr, SDbfRender* render);



//////////
//
// Miscellaneous DBF/CDX support functions
//
/////
	void				iiFreeAndSetToNull								(void** ptr);
	void				iiGetTemporaryFilename							(s8 *temp_file, s8 *prefix);
	void				iiLowerCaseString								(s8 *string, u32 length);
	void				iiJuststem										(SWorkArea* wa, s8* alias);
	void				iiUpperCase										(u8* cptr);
	void				iiLowerCase										(u8* cptr);
	u8					iiLowerCase_char								(u8 c);
	u32					iiSwapEndian32									(u32 tnEndianIn);		// Swap endian
	u64					iiSwapEndian64									(u64 tnEndianIn);		// Swap endian
	void				iiShiftBlockRight								(u8* data, u32 tnBytes, s32 tnBits);
	void				iiPtrSwap										(void** p1, void** p2);
	u8*					iResetThenCopyString							(u8* tcDest, s32 tnDestLength, u8* tcSource, s32 tnSourceLength);
	u8*					iResetThenCopyString							(u8* tcDest, s32 tnDestLength, u8 lcResetChar, u8* tcSource, s32 tnSourceLength);
	cs8*				iiTwoChoice										(s8* tcDest, bool tlTestValue, cs8* tcIfTrue, cs8* tcIfFalse);


	// Julian date support
	u32					iiJulianDayNumber_fromYyyyMmDd_s8				(u8* year4,  u8* month2,  u8* day2);
	u32					iiJulianDayNumber_fromYyyyMmDd_u32				(u32 year,  u32  month,  u32  day);
	void				iiYyyyMmDd_fromJulianDayNumber					(u32  tnJulianDayNumber, u8* year4, u8* month2, u8* day2);
	void				iiHhMmSsMss_fromf32								(f32 tfSeconds, u32* hour, u32* minute, u32* second, u32* millisecond);

	// Character tests
	bool				isDotExpression									(s8 c);
	bool				isComparator									(s8 c);
	bool				isQuote											(s8 c);
	bool				isNotSymbol										(s8 c);
	bool				isParenthesis									(s8 c);
	bool				isBracket										(s8 c);
	bool				isBrace											(s8 c);
	bool				isWhitespace									(s8 c);
