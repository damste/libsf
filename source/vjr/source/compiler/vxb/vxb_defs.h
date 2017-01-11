//////////
//
// /libsf/source/vjr/source/compiler/vxb/vxb_defs.h
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
//     Jun.29.2014
//////
// Change log:
//     Jun.29.2014 - Initial creation
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
//   ___      ___   ___  ___    _______
//  |"  \    /"  | |"  \/"  |  |   _  "\
//   \   \  //  /   \   \  /   (. |_)  :)
//    \\  \/. ./     \\  \/    |:     \/
//     \.    //      /\.  \    (|  _  \\
//      \\   /      /  \   \   |: |_)  :)
//       \__/      |___/\___|  (_______/
//     Visual FreePro, Jr. XBase Compiler
//
//////////




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
struct SVariable;
struct SThisCode;
struct SClassObj;
struct SVxbContext;


//////////
// compiler.cpp
//////////
	bool					iiVerify_xDot_callback						(SAsciiCompSearcher* tacs, u8* tcStart, s32 tnLength);
	u32						iVxb_compile								(SEM* sem, SVxbContext* vxb, SVxbStats* stats);
	void					iiVxb_compile_stage1						(SVxbContext* vxb);
	void					iiVxb_compile_stage2						(SVxbContext* vxb);
	void					iiVxb_compile_stage3						(SVxbContext* vxb);

	SFunction*				iiComps_decodeSyntax_function				(SVxbContext* vxb);
	SFunction*				iiComps_decodeSyntax_adhoc					(SVxbContext* vxb);
	void					iiComps_decodeSyntax_params					(SVxbContext* vxb);
	void					iiComps_decodeSyntax_lobject				(SVxbContext* vxb);
	void					iiComps_decodeSyntax_lparameters			(SVxbContext* vxb);
	void					iiComps_decodeSyntax_returns				(SVxbContext* vxb);

	// LiveCode
	void					iiVxb_free_liveCode							(SCompiler* compiler);

	bool					iiComps_xlatToNodes							(SLine* line, SCompiler* compiler);
	SNode*					iiComps_xlatToNodes_parenthesis_left		(SNode** root, SNode* active, SComp* comp);
	SNode*					iiComps_xlatToNodes_parenthesis_right		(SNode** root, SNode* active, SComp* comp);

	SComp*					iComps_new									(SComp** compRoot, SComp* compHint, SComp* compNext, SComp* compPrev);
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
	SComp*					iComps_findNextBy_iCode						(SComp* comp, s32 tniCode, SComp** compLastScanned = NULL);
	s32						iComps_findMultipleBy_iCode					(SComp* compRoot, s32 tnCount, s32 tniCodes[], SComp** compFinds[]);
	SComp*					iComps_activeComp_inSEM						(SEM* sem);
	bool					iComps_get_mateDirection					(SComp* comp, s32* tnMateDirection, s32* tniCode = NULL);
	bool					iComps_findClosest_parensBracketsBraces		(SComp* compRelative, SComp* compStart, SComp** compPBBLeft, SComp** compPBBRight);
	bool					iComps_isParensBracketsBraces				(SComp* comp);
	bool					iComps_isMateOf								(SComp* compTest, s32 tniCodeMate);
	SComp*					iComps_findMate								(SComp* compAnchor, s32* tnCount = NULL, bool tlAllowNesting = false);
	SComp*					iComps_skipPast_iCode						(SComp* comp, s32 tniCode);
	SComp*					iComps_skipTo_iCode							(SComp* comp, s32 tniCode);
	SComp*					iComps_getNext_afterDot						(SComp* comp);
	SComp*					iComps_getNth								(SComp* comp, s32 tnCount = 1);
	u32						iComps_combineN								(SComp* comp, u32 tnCount, s32 tnNew_iCode, u32 tnNew_iCat, SBgra* newColor, SComp** compMigrateRefs = NULL);
	u32						iComps_combine_adjacent						(SComp* compLeftmost, s32 tniCode, u32 tniCat, SBgra* tnColor, s32 valid_iCodeArray[], s32 tnValid_iCodeArrayCount);
	u32						iComps_combine_adjacentAlphanumeric			(SLine* line);
	u32						iComps_combine_adjacentNumeric				(SLine* line);
	u32						iComps_combine_adjacentDotForms				(SLine* line);
	bool					iiComps_isKnown_dotForm						(SComp* comp);
	u32						iComps_combine_adjacentLeadingPipesigns		(SLine* line);
	u32						iComps_combineAll_between					(SLine* line, s32 tniCodeNeedle,		s32 tniCodeCombined,											SBgra* syntaxHighlightColor);
	u32						iComps_combineAll_betweenTwo				(SLine* line, s32 tniCodeNeedleLeft,	s32 tniCodeNeedleRight,		s32 tniCodeCombined,	u32 tniCat, SBgra* syntaxHighlightColor, bool tlUseBoldFont);
	u32						iComps_combineAll_after						(SLine* line, s32 tniCodeNeedle);
	u32						iComps_deleteAll_after						(SLine* line, s32 tniCodeNeedle);
	SComp*					iComps_migrate								(SComp** compSource, SComp** compDestination, SComp* compToMove);
	u32						iComps_remove_leadingWhitespaces			(SLine* line);
	u32						iComps_remove_whitespaces					(SLine* line);
	void					iComps_remove_startEndComments				(SLine* line);
	s32						iComps_truncate_atComments					(SLine* line);
	void					iComps_combine_casks						(SLine* line);
	void					iComps_fixup_naturalGroupings				(SLine* line);
	void					iComps_fixup_htmlGroupings					(SLine* line);
	s32						iComps_unescape_iCodes						(SComp* compStart, s32 tniCode1, s32 tniCode2, s32 tniCode3, s32 tniCodeEscape = _ICODE_BACKSLASH);
	s32						iComps_copyTo								(SLine* line, SComp* compStart, SComp* compEnd, bool tlMakeReferences);
	s32						iComps_copyTo_withCallback					(SLine* line, SComp* compStart, SCallback* cb, bool tlMakeReferences);
	bool					iiComps_areCompsAdjacent					(SComp* compLeft, SComp* compRight);
	s32						iiComps_get_charactersBetween				(SComp* compLeft, SComp* compRight);
	s32						iComps_getAs_s32							(SComp* comp);
	s64						iComps_getAs_s64							(SComp* comp);
	f64						iComps_getAs_f64							(SComp* comp);
	s32						iiComps_getAs_s32							(SComp* comp);
	s64						iiComps_getAs_s64							(SComp* comp);
	f64						iiComps_getAs_f64							(SComp* comp);
	SDatum*					iComps_getAs_datum							(SComp* comp, SDatum* useDatum = NULL, bool tlCreateACopy = true);
	SDatum*					iiComps_populateAs_datum					(SDatum* datum, SComp* comp, SVariable** varSys2015);
	s32						iComps_getContiguousLength					(SComp* comp, s32 valid_iCodeArray[], s32 tnValid_iCodeArrayCount, s32* tnCount);
	u32						iComps_count								(SComp* comp);
	bool					iiComps_validate							(SComp* comp, s32 valid_iCodeArray[], s32 tnValid_iCodeArrayCount);
	bool					iiComps_isAlphanumeric_byHardScan			(SComp* comp);
	bool					iiComps_isVxbLogicBlock_entry				(SComp* comp, bool tlIncludeAdhocs);
	bool					iiComps_isVxbLogicBlock_exit				(SComp* comp, bool tlIncludeAdhocs);
	#define					iiComps_isAlphanumeric_by_iCode(iCode)		(iCode == _ICODE_ALPHA || iCode == _ICODE_ALPHANUMERIC)
	#define					iiComps_isNumeric(iCode)					(iCode == _ICODE_NUMERIC)
	#define					iiComps_isComment(iCode)					(iCode == _ICODE_COMMENT || iCode == _ICODE_LINE_COMMENT)
	#define					iiComps_isVxbFunction(iCode)				(iCode == _ICODE_FUNCTION || iCode == _ICODE_PROCEDURE)
	s8*						iComps_visualize							(SComp* comp, s32 tnCount, s8* outputBuffer, s32 tnBufferLength, bool tlUseDefaultCompSearcher, SAsciiCompSearcher* tsComps1, SAsciiCompSearcher* tsComps2);
	s8*						iiComps_visualize_lookup_iCode				(s32 tniCode);


//////////
// Jun.25.2014 -- This block of code was originally created before I began working on
// iiTranslateSOpsToSubInstr() above.  As such, it is stale and will probably be
// refactored or deleted.
// BEGIN
//////
	void					iiComps_xlatToSubInstr						(SLine* line);
	SComp*					iiComps_xlatToSubInstr_findInmostExpression	(SNode* si, SLine* line);
	void					iiComps_xlatToSubInstr_findStartOfComponent	(SComp* compRoot, SOp* op);
	void					iiComps_xlatToSubInstr_findFullComponent	(SComp* compRoot, SOp* op);
	bool					iiComps_xlatToSubInstr_isEqualAssignment	(SLine* line);
//////
// END
//////////


	u32						iBreakoutAsciiTextDataIntoLines_ScanLine	(s8* tcData, u32 tnMaxLength, u32* tnLength, u32* tnWhitespaces);
	bool					iFindFirstOccurrenceOfAsciiCharacter		(s8* tcHaystack, u32 tnHaystackLength, s8 tcNeedle, u32* tnPosition);
	u32						iGetNextUid									();

	// Start end chains
	void*					iSEChain_prepend							(SStartEnd* ptrSE, u32 tnUniqueId, u32 tnUniqueIdExtra, u32 tnSize, u32 tnBlockSizeIfNewBlockNeeded, bool* tlResult);
	void*					iSEChain_append								(SStartEnd* ptrSE, u32 tnUniqueId, u32 tnUniqueIdExtra, u32 tnSize, u32 tnBlockSizeIfNewBlockNeeded, bool* tlResult);
	void*					iSEChain_appendOrPrepend					(SStartEnd* ptrSE, u32 tnUniqueId, u32 tnUniqueIdExtra, u32 tnSize, u32 tnBlockSizeIfNewBlockNeeded, bool tlPrepend, bool* tlResult);
	u32						iSkip_whitespaces							(s8* tcData, u32 tnMaxLength);
	u32						iSkip_toCrLf								(s8* tcData, u32 tnMaxLength, u32* tnCRLF_Length);
	void					iSEChain_appendMasterList					(SStartEnd* ptrSE, SMasterList* ptrNew, u32 tnHint, u32 tnBlockSizeIfNewBlockNeeded);
	bool					iSEChain_allocateAdditionalMasterSlots		(SStartEnd* ptrSE, u32 tnBlockSize);
	void*					iSEChain_searchByCallback					(SStartEnd* ptrSE, SStartEndCallback* cb);
	void*					iSEChain_searchByUniqueId					(SStartEnd* ptrSE, u64 tnUniqueId);
	void					iSEChain_iterateThroughForCallback			(SStartEnd* ptrSE, SStartEndCallback* cb);
	void					iSEChain_deleteFrom							(SStartEnd* ptrSE, void* ptrCaller, bool tlDeletePointers);
	SLL*					iSEChain_completelyMigrateSLLByPtr			(SStartEnd* ptrSEDst, SStartEnd* ptrSESrc, SLL* ptr, u32 tnHint, u32 tnBlockSize);
	SLL*					iSEChain_completelyMigrateSLLByNum			(SStartEnd* ptrSEDst, SStartEnd* ptrSESrc, u32 lnSrcNum, u32 tnHint, u32 tnBlockSize);
	SMasterList*			iSEChain_migrateByNum						(SStartEnd* ptrSEDst, SStartEnd* ptrSESrc, u32 lnSrcNum, u32 tnHint, u32 tnBlockSize);

	s32						iComps_xlatToComps_withTest					(cu8* tcHaystack, cu8* tcNeedle, s32 tnLength);
	bool					iiComps_xlatToOthers_callback				(SStartEndCallback* cb);
	void					iiComps_xlatToOthers_callback__insertCompByCompCallback		(SComp* compRef, SComp* compNew, bool tlInsertAfter);
	void					iiComps_xlatToOthers_callback__insertCompByParamsCallback	(SComp* compRef, SLine* line, u32 tniCode, u32 tnStart, s32 tnLength, bool tlInsertAfter);
	void					iiComps_xlatToOthers_callback__deleteCompsCallback			(SComp* comp, SLine* line);
	SComp*					iiComps_xlatToOthers_callback__cloneCompsCallback			(SComp* comp, SLine* line);
	SComp*					iiComps_xlatToOthers_callback__mergeCompsCallback			(SComp* comp, SLine* line, u32 tnCount, u32 tniCodeNew);

	// Function functions (LOL)
	SFunction*				iFunction_allocate							(SComp* compName);
	SFunction*				iFunction_allocate							(SDatum* datumName);
	SFunction*				iFunction_allocate							(u8* tcFuncName);
	SVariable*				iFunction_addVariable_scoped				(SFunction* func);
	void					iFunction_politelyDeleteCompiledInfo		(SFunction* func, bool tlDeleteSelf);
	void					iFunction_politelyDelete					(SFunction* func, bool tlDeleteSelf);
	void					iFunction_politelyDelete_chain				(SFunction** rootFunc, bool tlDeleteSelf);

	// ClassObj
	SClassObj*				iClassObj_allocate							(SDatum* datumName);

	// Variable functions
	SVariable*				iiVariable_terminateIndirect				(SVariable* var);
	SVariable*				iVariable_create							(s32 tnVarType, SVariable* varIndirect, bool tlAllocateDefaultValue, s32 tnBitsFor_bfp_bi = -1);
	SVariable*				iVariable_createAndPopulate_byDatum			(s32 tnVarType, SDatum* datum, bool tlCreateReference);
// Moved to vjr_defs0.h
// 	SVariable*				iVariable_createAndPopulate_byText			(s32 tnVarType, u8*  tcData, s32 tnDataLength, bool tlCreateReference);
// 	SVariable*				iVariable_createAndPopulate_byText			(s32 tnVarType, s8*  tcData, s32 tnDataLength, bool tlCreateReference);
// 	SVariable*				iVariable_createAndPopulate_byText			(s32 tnVarType, cu8* tcData, s32 tnDataLength, bool tlCreateReference);
// 	SVariable*				iVariable_createAndPopulate_byText			(s32 tnVarType, cs8* tcData, s32 tnDataLength, bool tlCreateReference);
	SVariable*				iVariable_createByRadix						(u64 tnValue, u64 tnBase, u32 tnPrefixChars, u32 tnPostfixChars);
	bool					iVariable_searchRoot_forDotName_andSet_byVar(              SComp* compDotName, SVariable* varNewValue, bool* tlError, u32* tnErrorNum);
	bool					iVariable_searchObj_forDotName_andSet_byVar	(SObject* obj, SComp* compDotName, SVariable* varNewValue, bool* tlError, u32* tnErrorNum);
	SVariable*				iVariable_searchForName						(cs8* tcVarName, u32 tnVarNameLength, SComp* comp, bool tlCreateAsReference);
	SVariable*				iiVariable_searchForName_variables			(SVariable* varRoot, cs8* tcVarName, u32 tnVarNameLength, SComp* comp, bool tlCreateAsReference, s32 tnMaxVarDepth = 9999999);
	SVariable*				iiVariable_searchForName_fields				(cs8* tcVarName, u32 tnVarNameLength, SComp* comp, bool tlCreateAsReference);
	SComp*					iVariable_get_relatedComp					(SVariable* var);
	s32						iVariable_get_fundamentalType				(SVariable* var);
	bool					iVariable_isFundamentalType					(SVariable* var);
	void					iVariable_createDefaultValues				(void);
	void					iVariable_createPropsMaster					(void);
	bool					iVariable_isVarTypeValid					(s32 tnVarType, SVariable** varDefaultValue);
	bool					iVariable_areTypesCompatible				(SVariable* var1, SVariable* var2);
	bool					iVariable_copy								(SVariable* varDst, SVariable* varSrc);
	SVariable*				iVariable_copy								(SVariable* varSrc, bool tlMakeReference);
	bool					iVariable_set								(SVariable* varDst, SVariable* varSrc);
	void					iVariable_setVarType						(SVariable* var, u32 tnVarTypeNew);
	bool					iVariable_setNumeric_toNumericType			(SVariable* varDst, f32* val_f32, f64* val_f64, s32* val_s32, u32* val_u32, s64* val_s64, u64* val_u64);
	bool					iVariable_setNumeric_toDestinationType		(SVariable* varDst, SVariable* varSrc);
	bool					iVariable_set_s32_toExistingType			(SErrorInfo* ei, SVariable* var, s32 value);
	bool					iVariable_set_s64_toExistingType			(SErrorInfo* ei, SVariable* var, s64 value);
	bool					iVariable_set_f32_toExistingType			(SErrorInfo* ei, SVariable* var, f32 value);
	bool					iVariable_set_f64_toExistingType			(SErrorInfo* ei, SVariable* var, f64 value);
	bool					iVariable_set_u32_toExistingType			(SErrorInfo* ei, SVariable* var, u32 value);
	bool					iVariable_set_u64_toExistingType			(SErrorInfo* ei, SVariable* var, u64 value);
	SDatum*					iVariable_setName							(SVariable* var, cu8* tcName, s32 tnNameLength);
	bool					iVariable_set_s16							(SVariable* var, s16 value);
	bool					iVariable_set_s32							(SVariable* var, s32 value);
	bool					iVariable_set_u16							(SVariable* var, u16 value);
	bool					iVariable_set_u32							(SVariable* var, u32 value);
	bool					iVariable_set_f32							(SVariable* var, f32 value);
	bool					iVariable_set_f64							(SVariable* var, f64 value);
	bool					iVariable_set_logical						(SVariable* var, bool tlValue);
	bool					iVariable_set_logical						(SVariable* var, s32 value);
	bool					iVariable_set_bitmap						(SVariable* var, SBitmap* bmp);
	bool					iVariable_set_character						(SVariable* var, u8* tcData, u32 tnDataLength);
	bool					iVariable_set_character						(SVariable* var, SDatum* datum);
	void					iVariable_reset								(SVariable* var, bool tlTerminateIndirect);
	SVariable*				iVariable_convertForDisplay					(SVariable* var);
	SVariable*				iVariable_get_typeDetail					(SVariable* var);
// Moved to vjr_defs.0.h
// 	void					iVariable_delete							(SVariable** var);
// 	void					iVariable_delete							(SVariable* var, bool tlDeleteSelf, bool tlOverrideDelete = false);
	void					iVariable_politelyDelete_chain				(SVariable** root, bool tlDeleteSelf);
	void					iVariable_politelyDelete_chain_callback		(SLLCallback* cb);
	SVariable*				iiVariable_getAs_datetime					(SVariable* var, bool tlForceConvert = false, bool* tlError = NULL, u32* tnErrorNum = NULL);
	bool					iiVariable_getAs_bool						(SVariable* var, bool tlForceConvert = false, bool* tlError = NULL, u32* tnErrorNum = NULL);
	s8						iiVariable_getAs_s8							(SVariable* var, bool tlForceConvert = false, bool* tlError = NULL, u32* tnErrorNum = NULL);
	s16						iiVariable_getAs_s16						(SVariable* var, bool tlForceConvert = false, bool* tlError = NULL, u32* tnErrorNum = NULL);
	s32						iiVariable_getAs_s32						(SVariable* var, bool tlForceConvert = false, bool* tlError = NULL, u32* tnErrorNum = NULL);
	u16						iiVariable_getAs_u16						(SVariable* var, bool tlForceConvert = false, bool* tlError = NULL, u32* tnErrorNum = NULL);
	u32						iiVariable_getAs_u32						(SVariable* var, bool tlForceConvert = false, bool* tlError = NULL, u32* tnErrorNum = NULL);
	s64						iiVariable_getAs_s64						(SVariable* var, bool tlForceConvert = false, bool* tlError = NULL, u32* tnErrorNum = NULL);
	u64						iiVariable_getAs_u64						(SVariable* var, bool tlForceConvert = false, bool* tlError = NULL, u32* tnErrorNum = NULL);
	f32						iiVariable_getAs_f32						(SVariable* var, bool tlForceConvert = false, bool* tlError = NULL, u32* tnErrorNum = NULL);
	f64						iiVariable_getAs_f64						(SVariable* var, bool tlForceConvert = false, bool* tlError = NULL, u32* tnErrorNum = NULL);
	s8						iiVariable_getAs_s8_andDispose				(SVariable* var, bool tlForceConvert = false, bool* tlError = NULL, u32* tnErrorNum = NULL, bool tlDeleteSelf = true);
	s16						iiVariable_getAs_s16_andDispose				(SVariable* var, bool tlForceConvert = false, bool* tlError = NULL, u32* tnErrorNum = NULL, bool tlDeleteSelf = true);
	s32						iiVariable_getAs_s32_andDispose				(SVariable* var, bool tlForceConvert = false, bool* tlError = NULL, u32* tnErrorNum = NULL, bool tlDeleteSelf = true);
	u16						iiVariable_getAs_u16_andDispose				(SVariable* var, bool tlForceConvert = false, bool* tlError = NULL, u32* tnErrorNum = NULL, bool tlDeleteSelf = true);
	u32						iiVariable_getAs_u32_andDispose				(SVariable* var, bool tlForceConvert = false, bool* tlError = NULL, u32* tnErrorNum = NULL, bool tlDeleteSelf = true);
	s64						iiVariable_getAs_s64_andDispose				(SVariable* var, bool tlForceConvert = false, bool* tlError = NULL, u32* tnErrorNum = NULL, bool tlDeleteSelf = true);
	u64						iiVariable_getAs_u64_andDispose				(SVariable* var, bool tlForceConvert = false, bool* tlError = NULL, u32* tnErrorNum = NULL, bool tlDeleteSelf = true);
	f32						iiVariable_getAs_f32_andDispose				(SVariable* var, bool tlForceConvert = false, bool* tlError = NULL, u32* tnErrorNum = NULL, bool tlDeleteSelf = true);
	f64						iiVariable_getAs_f64_andDispose				(SVariable* var, bool tlForceConvert = false, bool* tlError = NULL, u32* tnErrorNum = NULL, bool tlDeleteSelf = true);
	s32						iVariable_compare							(SVariable* varLeft, SVariable* varRight, bool tlForceConvert = false, bool* tlError = NULL, u32* tnErrorNum = NULL);
	s32						iiVariable_compareNonmatchingTypesAs_f64	(SVariable* varLeft, SVariable* varRight, bool tlForceConvert = false, bool* tlError = NULL, u32* tnErrorNum = NULL);
	s32						iiVariable_compareNonmatchingTypesAs_s64	(SVariable* varLeft, SVariable* varRight, bool tlForceConvert = false, bool* tlError = NULL, u32* tnErrorNum = NULL);
	s32						iiVariable_compareNonmatchingTypesAs_u64	(SVariable* varLeft, SVariable* varRight, bool tlForceConvert = false, bool* tlError = NULL, u32* tnErrorNum = NULL);
	s32						iiVariable_compareMatchingTypes				(SVariable* varLeft, SVariable* varRight, bool* tlError = NULL, u32* tnErrorNum = NULL);
	s64						iiVariable_compute_DatetimeDifference_getAs_s64(SVariable* dtVar1, SVariable* dtVar2);
	f64						iiVariable_compute_DatetimeDifference_getAs_f64(SVariable* dtVar1, SVariable* dtVar2);
	// Helper functions
// Moved to vjr_defs0.h
// 	s32						iiVariable_getType_character				(void);
// 	s32						iiVariable_getType_s32						(void);

	// Support functions
	SVariable*				iiDateMath_get_dateTemplate										(s32 tnDateFormat);
	bool					iiDateMath_get_YyyyMmDdHhMmSsMss_from_datetime					(SDateTime*  dt,  u32* year, u32* month, u32* day, u32* hour = NULL, u32* minute = NULL, u32* second = NULL, s32* ms = NULL);
	bool					iiDateMath_get_YyyyMmDdHhMmSsMssNss_from_datetimex				(SDateTimeX* dtx, u32* year, u32* month, u32* day, u32* hour = NULL, u32* minute = NULL, u32* second = NULL, s32* ms = NULL, s32* ns = NULL);
	void					iiDateMath_get_YyyyMmDdHhMmSsMssNss_from_jseconds				(u64  tnDtx, f64* tfDtx,              u32* year, u32* month, u32* day, u32* hour, u32* minute, u32* second, s32* millisecond, s32* microsecond);
	void					iiDateMath_get_julian_and_YyyyMmDdHhMmSsMssNss_from_jseconds	(u64  tnDtx, f64* tfDtx, u32* julian, u32* year, u32* month, u32* day, u32* hour, u32* minute, u32* second, s32* millisecond, s32* microsecond);
	u64						iiDateMath_get_jseconds_from_YyyyMmDdHhMmSsMssMics				(u64* tnDtx,                          u32  year, u32  month, u32  day, u32  hour, u32  minute, u32  second, s32  millisecond, s32  microsecond);
	u64						iiDateMath_get_jseconds_from_julian_and_HhMmSsMssMics			(u64* tnDtx,             u32  julian,                                  u32  hour, u32  minute, u32  second, s32  millisecond, s32  microsecond);
	s32						iiDateMath_get_julian_from_YyyyMmDd								(f32* tnJulianDayNumber, u32  year, u32  month, u32  day);
	void					iiDateMath_get_YyyyMmDd_from_julian								(u32  tnJulianDayNumber, u32* year, u32* month, u32* day);
	void					iiDateMath_get_YyyyMmDd_from_YYYYMMDD							(u8* YYYYMMDD,           u32* year, u32* month, u32* day);
	void					iiDateMath_get_HhMmSsMss_from_seconds							(f32 tfSeconds, u32* hour, u32* minute, u32* second, s32* millisecond);
	void					iiDateMath_get_HhMmSsMssMics_from_secondsx						(f64 tfSeconds, u32* hour, u32* minute, u32* second, s32* millisecond, s32* microsecond);
	f32						iiDateMath_get_seconds_from_HhMmSsMss							(               u32  hour, u32  minute, u32  second, s32  millisecond);
	s32						iiDateMath_get_currentMicrosecond								(void);
	s32						iiDateMath_get_currentNanosecond								(void);
	void					iiDateMath_get_YYYYMMDD_from_YyyyMmDd							(u8* YYYYMMDD, u32  year, u32  month, u32  day);
	void					iiDateMath_get_YYYYMMDD_from_YyyyMmDd							(s8* YYYYMMDD, u32  year, u32  month, u32  day);
	void					iiDateMath_get_SYSTEMTIME_from_SECONDS							(SYSTEMTIME* st, f32 tfSeconds);
	void					iiDateMath_get_SYSTEMTIME_from_SECONDSX							(SYSTEMTIME* st, f64 tfSecondsx, s32* tnMicroseconds, s32* tnNanosecond);
	bool					iiDateMath_isValidDate											(u32 year, u32 month, u32 day);
	bool					iiDateMath_isLeapYear											(u32 year);
	s32						iiDateMath_derive_century										(u32 year);
	u32						iiDateMath_get_dayNumberIntoYear								(u32 year, u32 month, u32 day);
	void					iiDateMath_get_datetimeX										(SDateTimeX* dtx, bool tlUseLocalTime = true);
	s32						iiDateMath_get_date_inSystemFormat								(SDatum* dateOut, s8* YyyyMmDd,		s32 tnDateFormat = -1, bool* tlCentury = NULL);
	s32						iiDateMath_get_datetime_inSystemFormat							(SDatum* dateOut, SDateTime*  dt,	s32 tnDateFormat = -1, bool* tlCentury = NULL, s32* tnHour = NULL);
	s32						iiDateMath_get_datetimex_inSystemFormat							(SDatum* dateOut, SDateTimeX* dtx,	s32 tnDateFormat = -1, bool* tlCentury = NULL, s32* tnHour = NULL);

	// Big floating point
	s32						iiBfp_calc_significantDigits_bySize			(SVariable* varVal);
	void					iiBfp_convertForDisplay						(SVariable* varDisp,	SVariable* varVal);
	void					iiBfp_convertFrom_scientificNotation		(SDatum* datum,			SVariable* varVal);
	// Big integer
	s32						iiBi_calc_significantDigits_bySize			(SVariable* varVal);
	void					iiBi_convertForDisplay						(SVariable* varDisp,	SVariable* varVal);
	void					iiBi_convertFrom_scientificNotation			(SDatum* datum,			SVariable* varVal);


	// Op functions
	bool					iOp_setNull									(SOp* op);
	bool					iOp_setVariable_param						(SOp* op, SVariable* var, bool isOpAllocated);
	bool					iOp_setVariable_local						(SOp* op, SVariable* var, bool isOpAllocated);
	bool					iOp_setVariable_scoped						(SOp* op, SVariable* var, bool isOpAllocated);
	bool					iOp_setVariable_return						(SOp* op, SVariable* var, bool isOpAllocated);
	void					iOp_politelyDelete							(SOp** opRoot, bool tlDeleteSelf);
	void					iOp_politelyDelete							(SOp* op, bool tlDeleteSelf);

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
	SLine*					iLine_copyComps_toNewLines					(SLine* lineStart, SComp* compStart, SLine* lineEnd, SComp* compEnd, bool tlLeftJustifyStart, bool tlSkipBlankLines);
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
	SNoteLog*				iNoteLog_create_byErrorNumber				(SNoteLog** noteRoot, SComp* comp, u32 tnErrorNumber);
	void					iNoteLog_removeAll							(SNoteLog** noteRoot);
