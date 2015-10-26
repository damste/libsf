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
// Version 0.57
// Copyright (c) 2014 by Rick C. Hodgin
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
struct SCompileStats;
struct SCompileNote;
struct SAsciiCompSearcher;
struct SStartEnd;
struct SStartEndCallback;
struct SOp;
struct SMasterList;
struct SVariable;
struct SThisCode;


//////////
// compiler.cpp
//////////
	u32						compile_vxb									(SThisCode* thisCode, SEM* codeBlock, SCompileVxbContext* vxbParam, SCompileStats* stats);
	bool					iValidate_xDot								(SAsciiCompSearcher* tacs, u8* tcStart, s32 tnLength);
	void					iiCompile_vxb_precompile_forLiveCode		(SThisCode* thisCode, SCompileVxbContext* vxb);
	void					iiCompile_vxb_compile_forLiveCode			(SThisCode* thisCode, SCompileVxbContext* vxb);
	void					iiCompile_vxb_postcompile_forLiveCode		(SThisCode* thisCode, SCompileVxbContext* vxb);

	SFunction*				iiComps_decodeSyntax_function				(SThisCode* thisCode, SCompileVxbContext* vxb);
	SFunction*				iiComps_decodeSyntax_adhoc					(SThisCode* thisCode, SCompileVxbContext* vxb);
	void					iiComps_decodeSyntax_params					(SThisCode* thisCode, SCompileVxbContext* vxb);
	void					iiComps_decodeSyntax_lobject				(SThisCode* thisCode, SCompileVxbContext* vxb);
	void					iiComps_decodeSyntax_lparameters			(SThisCode* thisCode, SCompileVxbContext* vxb);
	void					iiComps_decodeSyntax_returns				(SThisCode* thisCode, SCompileVxbContext* vxb);

	// LiveCode
	void					iiCompile_LiveCode_free						(SThisCode* thisCode, SCompiler* compiler);

	bool					iiComps_xlatToNodes							(SThisCode* thisCode, SLine* line, SCompiler* compiler);
	SNode*					iiComps_xlatToNodes_parenthesis_left		(SThisCode* thisCode, SNode** root, SNode* active, SComp* comp);
	SNode*					iiComps_xlatToNodes_parenthesis_right		(SThisCode* thisCode, SNode** root, SNode* active, SComp* comp);

	void					iComps_deleteAll							(SThisCode* thisCode, SComp* comp);
	void					iComps_deleteAll_byLine						(SThisCode* thisCode, SLine* line);
	void					iComps_deleteAll_byFirstComp				(SThisCode* thisCode, SComp** firstComp);
	SComp*					iComps_duplicate							(SThisCode* thisCode, SComp* comp);
	SComp*					iComps_delete								(SThisCode* thisCode, SComp* comp, bool tlDeleteSelf);
	void					iComps_copyMembers							(SThisCode* thisCode, SComp* compTo, SComp* compFrom, bool tlAllocated, bool tlCopyLl, s32 tnBackoff);
 	SComp*					iComps_translateSourceLineTo				(SThisCode* thisCode, SAsciiCompSearcher* tsComps, SLine* line);
 	bool					iComps_translateToOthers					(SThisCode* thisCode, SAsciiCompSearcher* tsComps, SLine* line);
	bool					iComps_areAllPrecedingCompsWhitespaces		(SThisCode* thisCode, SComp* comp);
	s32						iComps_translateToOthers_testIfMatch		(SThisCode* thisCode, cu8* tcHaystack, cu8* tcNeedle, s32 tnLength);
	SComp*					iComps_findNextBy_iCode						(SThisCode* thisCode, SComp* comp, s32 tniCode, SComp** compLastScanned);
	SComp*					iComps_activeComp_inSEM						(SThisCode* thisCode, SEM* sem);
	bool					iComps_getMateDirection						(SThisCode* thisCode, SComp* comp, s32* tnMateDirection);
	bool					iComps_findClosest_parensBracketsBraces		(SThisCode* thisCode, SComp* compRelative, SComp* compStart, SComp** compPBBLeft, SComp** compPBBRight);
	bool					iComps_isParensBracketsBraces				(SThisCode* thisCode, SComp* comp);
	bool					iComps_isMateOf								(SThisCode* thisCode, SComp* compTest, s32 tniCodeMate);
	SComp*					iComps_skipPast_iCode						(SThisCode* thisCode, SComp* comp, s32 tniCode);
	SComp*					iComps_skipTo_iCode							(SThisCode* thisCode, SComp* comp, s32 tniCode);
	SComp*					iComps_getNext_afterDot						(SThisCode* thisCode, SComp* comp);
	SComp*					iComps_getNth								(SThisCode* thisCode, SComp* comp, s32 tnCount);
	u32						iComps_combineN								(SThisCode* thisCode, SComp* comp, u32 tnCount, s32 tnNew_iCode, u32 tnNew_iCat, SBgra* newColor, SComp** compMigrateRefs = NULL);
	u32						iComps_combineAdjacent						(SThisCode* thisCode, SComp* compLeftmost, s32 tniCode, u32 tniCat, SBgra* tnColor, s32 valid_iCodeArray[], s32 tnValid_iCodeArrayCount);
	u32						iComps_combineAdjacentAlphanumeric			(SThisCode* thisCode, SLine* line);
	u32						iComps_combineAdjacentNumeric				(SThisCode* thisCode, SLine* line);
	u32						iComps_combineAdjacentDotForms				(SThisCode* thisCode, SLine* line);
	bool					iiComps_isKnownDotForm						(SComp* comp);
	u32						iComps_combineAdjacentLeadingPipesigns		(SThisCode* thisCode, SLine* line);
	u32						iComps_combineAllBetween					(SThisCode* thisCode, SLine* line, s32 tniCodeNeedle,		s32 tniCodeCombined,											SBgra* syntaxHighlightColor);
	u32						iComps_combineAllBetween2					(SThisCode* thisCode, SLine* line, s32 tniCodeNeedleLeft,	s32 tniCodeNeedleRight,		s32 tniCodeCombined,	u32 tniCat, SBgra* syntaxHighlightColor, bool tlUseBoldFont);
	u32						iComps_combineAllAfter						(SThisCode* thisCode, SLine* line, s32 tniCodeNeedle);
	u32						iComps_deleteAllAfter						(SThisCode* thisCode, SLine* line, s32 tniCodeNeedle);
	u32						iComps_removeLeadingWhitespaces				(SThisCode* thisCode, SLine* line);
	u32						iComps_removeWhitespaces					(SThisCode* thisCode, SLine* line);
	void					iComps_removeStartEndComments				(SThisCode* thisCode, SLine* line);
	s32						iComps_truncateAtComments					(SThisCode* thisCode, SLine* line);
	void					iComps_combineCasks							(SThisCode* thisCode, SLine* line);
	void					iComps_fixupNaturalGroupings				(SThisCode* thisCode, SLine* line);
	s32						iComps_unescape_iCodes						(SThisCode* thisCode, SComp* compStart, s32 tniCode1, s32 tniCode2, s32 tniCode3, s32 tniCodeEscape = _ICODE_BACKSLASH);
	s32						iComps_copyTo								(SThisCode* thisCode, SLine* line, SComp* compStart, SComp* compEnd, bool tlMakeReferences);
	s32						iComps_copyTo_withCallback					(SThisCode* thisCode, SLine* line, SComp* compStart, SCallback* cb, bool tlMakeReferences);
	bool					iiComps_areCompsAdjacent					(SThisCode* thisCode, SComp* compLeft, SComp* compRight);
	s32						iiComps_get_charactersBetween				(SThisCode* thisCode, SComp* compLeft, SComp* compRight);
	s32						iComps_getAs_s32							(SThisCode* thisCode, SComp* comp);
	s64						iComps_getAs_s64							(SThisCode* thisCode, SComp* comp);
	f64						iComps_getAs_f64							(SThisCode* thisCode, SComp* comp);
	s32						iiComps_getAs_s32							(SComp* comp);
	s64						iiComps_getAs_s64							(SComp* comp);
	f64						iiComps_getAs_f64							(SComp* comp);
	s32						iComps_getContiguousLength					(SThisCode* thisCode, SComp* comp, s32 valid_iCodeArray[], s32 tnValid_iCodeArrayCount, s32* tnCount);
	u32						iComps_count								(SThisCode* thisCode, SComp* comp);
	bool					iiComps_validate							(SThisCode* thisCode, SComp* comp, s32 valid_iCodeArray[], s32 tnValid_iCodeArrayCount);
	bool					iiComps_isAlphanumeric						(SThisCode* thisCode, SComp* comp);
	#define					iiComps_isComment(tniCode)					(tniCode == _ICODE_COMMENT || tniCode == _ICODE_LINE_COMMENT)
	s8*						iComps_visualize							(SThisCode* thisCode, SComp* comp, s32 tnCount, s8* outputBuffer, s32 tnBufferLength, bool tlUseDefaultCompSearcher, SAsciiCompSearcher* tsComps1, SAsciiCompSearcher* tsComps2);
	s8*						iiComps_visualize_lookup_iCode				(s32 tniCode);


//////////
// Jun.25.2014 -- This block of code was originally created before I began working on
// iiTranslateSOpsToSubInstr() above.  As such, it is stale and will probably be
// refactored or deleted.
// BEGIN
//////
	void					iiComps_xlatToSubInstr						(SThisCode* thisCode, SLine* line);
	SComp*					iiComps_xlatToSubInstr_findInmostExpression	(SThisCode* thisCode, SNode* si, SLine* line);
	void					iiComps_xlatToSubInstr_findStartOfComponent	(SThisCode* thisCode, SComp* compRoot, SOp* op);
	void					iiComps_xlatToSubInstr_findFullComponent	(SThisCode* thisCode, SComp* compRoot, SOp* op);
	bool					iiComps_xlatToSubInstr_isEqualAssignment	(SThisCode* thisCode, SLine* line);
//////
// END
//////////


	u32						iBreakoutAsciiTextDataIntoLines_ScanLine	(SThisCode* thisCode, s8* tcData, u32 tnMaxLength, u32* tnLength, u32* tnWhitespaces);
	bool					iFindFirstOccurrenceOfAsciiCharacter		(SThisCode* thisCode, s8* tcHaystack, u32 tnHaystackLength, s8 tcNeedle, u32* tnPosition);
	u32						iGetNextUid									(SThisCode* thisCode);

	// Start end chains
	void*					iSEChain_prepend							(SThisCode* thisCode, SStartEnd* ptrSE, u32 tnUniqueId, u32 tnUniqueIdExtra, u32 tnSize, u32 tnBlockSizeIfNewBlockNeeded, bool* tlResult);
	void*					iSEChain_append								(SThisCode* thisCode, SStartEnd* ptrSE, u32 tnUniqueId, u32 tnUniqueIdExtra, u32 tnSize, u32 tnBlockSizeIfNewBlockNeeded, bool* tlResult);
	void*					iSEChain_appendOrPrepend					(SThisCode* thisCode, SStartEnd* ptrSE, u32 tnUniqueId, u32 tnUniqueIdExtra, u32 tnSize, u32 tnBlockSizeIfNewBlockNeeded, bool tlPrepend, bool* tlResult);
	u32						iSkip_whitespaces							(SThisCode* thisCode, s8* tcData, u32 tnMaxLength);
	u32						iSkip_toCrLf								(SThisCode* thisCode, s8* tcData, u32 tnMaxLength, u32* tnCRLF_Length);
	void					iSEChain_appendMasterList					(SThisCode* thisCode, SStartEnd* ptrSE, SMasterList* ptrNew, u32 tnHint, u32 tnBlockSizeIfNewBlockNeeded);
	bool					iSEChain_allocateAdditionalMasterSlots		(SThisCode* thisCode, SStartEnd* ptrSE, u32 tnBlockSize);
	void*					iSEChain_searchByCallback					(SThisCode* thisCode, SStartEnd* ptrSE, SStartEndCallback* cb);
	void*					iSEChain_searchByUniqueId					(SThisCode* thisCode, SStartEnd* ptrSE, u64 tnUniqueId);
	void					iSEChain_iterateThroughForCallback			(SThisCode* thisCode, SStartEnd* ptrSE, SStartEndCallback* cb);
	void					iSEChain_deleteFrom							(SThisCode* thisCode, SStartEnd* ptrSE, void* ptrCaller, bool tlDeletePointers);
	SLL*					iSEChain_completelyMigrateSLLByPtr			(SThisCode* thisCode, SStartEnd* ptrSEDst, SStartEnd* ptrSESrc, SLL* ptr, u32 tnHint, u32 tnBlockSize);
	SLL*					iSEChain_completelyMigrateSLLByNum			(SThisCode* thisCode, SStartEnd* ptrSEDst, SStartEnd* ptrSESrc, u32 lnSrcNum, u32 tnHint, u32 tnBlockSize);
	SMasterList*			iSEChain_migrateByNum						(SThisCode* thisCode, SStartEnd* ptrSEDst, SStartEnd* ptrSESrc, u32 lnSrcNum, u32 tnHint, u32 tnBlockSize);

	s32						iComps_xlatToComps_withTest					(SThisCode* thisCode, cu8* tcHaystack, cu8* tcNeedle, s32 tnLength);
	bool					iiComps_xlatToOthers_callback				(SThisCode* thisCode, SStartEndCallback* cb);
	void					iiComps_xlatToOthers_callback__insertCompByCompCallback		(SThisCode* thisCode, SComp* compRef, SComp* compNew, bool tlInsertAfter);
	void					iiComps_xlatToOthers_callback__insertCompByParamsCallback	(SThisCode* thisCode, SComp* compRef, SLine* line, u32 tniCode, u32 tnStart, s32 tnLength, bool tlInsertAfter);
	void					iiComps_xlatToOthers_callback__deleteCompsCallback			(SThisCode* thisCode, SComp* comp, SLine* line);
	SComp*					iiComps_xlatToOthers_callback__cloneCompsCallback			(SThisCode* thisCode, SComp* comp, SLine* line);
	SComp*					iiComps_xlatToOthers_callback__mergeCompsCallback			(SThisCode* thisCode, SComp* comp, SLine* line, u32 tnCount, u32 tniCodeNew);

	// Node functions
	SNode*					iNode_create								(SThisCode* thisCode, SNode** root, SNode* hint, u32 tnDirection, SNode* parent, SNode* prev, SNode* next, SNode* left, SNode* right);
	SNode*					iNode_insertBetween							(SThisCode* thisCode, SNode** root, SNode* node1, SNode* node2, u32 tnNode1Direction, u32 tnNode2Direction);
	void					iNode_politelyDeleteAll						(SThisCode* thisCode, SNode** root, bool tlDeleteSelf, bool tlTraverseParent, bool tlTraversePrev, bool tlTraverseNext, bool tlTraverseLeft, bool tlTraverseRight);

	// Function functions (LOL)
	SFunction*				iFunction_allocate							(SThisCode* thisCode, SComp* compName);
	SFunction*				iFunction_allocate							(SThisCode* thisCode, SDatum* datumName);
	SFunction*				iFunction_allocate							(SThisCode* thisCode, u8* tcFuncName);
	SVariable*				iFunction_addVariable_scoped				(SThisCode* thisCode, SFunction* func);
	void					iFunction_politelyDeleteCompiledInfo		(SThisCode* thisCode, SFunction* func, bool tlDeleteSelf);
	void					iFunction_politelyDeleteChain				(SThisCode* thisCode, SFunction** rootFunc);

	// Variable functions
	SVariable*				iiVariable_terminateIndirect				(SThisCode* thisCode, SVariable* var);
	SVariable*				iVariable_create							(SThisCode* thisCode, s32 tnVarType, SVariable* varIndirect, bool tlAllocateDefaultValue, s32 tnBitsFor_bfp_bi = -1);
	SVariable*				iVariable_createAndPopulate_byDatum			(SThisCode* thisCode, s32 tnVarType, SDatum* datum, bool tlCreateReference);
	SVariable*				iVariable_createAndPopulate_byText			(SThisCode* thisCode, s32 tnVarType, u8*  tcData, s32 tnDataLength, bool tlCreateReference);
	SVariable*				iVariable_createAndPopulate_byText			(SThisCode* thisCode, s32 tnVarType, s8*  tcData, s32 tnDataLength, bool tlCreateReference);
	SVariable*				iVariable_createAndPopulate_byText			(SThisCode* thisCode, s32 tnVarType, cu8* tcData, s32 tnDataLength, bool tlCreateReference);
	SVariable*				iVariable_createAndPopulate_byText			(SThisCode* thisCode, s32 tnVarType, cs8* tcData, s32 tnDataLength, bool tlCreateReference);
	SVariable*				iVariable_createByRadix						(SThisCode* thisCode, u64 tnValue, u64 tnBase, u32 tnPrefixChars, u32 tnPostfixChars);
	bool					iVariable_searchRoot_forDotName_andSet_byVar	(SThisCode* thisCode, SComp* compDotName, SVariable* varNewValue, bool* tlError, u32* tnErrorNum);
	bool					iVariable_searchObj_forDotName_andSet_byVar		(SThisCode* thisCode, SObject* obj, SComp* comp, SVariable* varNewValue, bool* tlError, u32* tnErrorNum);
	SVariable*				iVariable_searchForName						(SThisCode* thisCode, cs8* tcVarName, u32 tnVarNameLength, SComp* comp, bool tlCreateAsReference);
	SVariable*				iiVariable_searchForName_variables			(SThisCode* thisCode, SVariable* varRoot, cs8* tcVarName, u32 tnVarNameLength, SComp* comp, bool tlCreateAsReference);
	SVariable*				iiVariable_searchForName_fields				(SThisCode* thisCode, cs8* tcVarName, u32 tnVarNameLength, SComp* comp, bool tlCreateAsReference);
	SComp*					iVariable_get_relatedComp					(SThisCode* thisCode, SVariable* var);
	s32						iVariable_get_fundamentalType				(SThisCode* thisCode, SVariable* var);
	bool					iVariable_isFundamentalType					(SThisCode* thisCode, SVariable* var);
	void					iVariable_createDefaultValues				(SThisCode* thisCode);
	void					iVariable_createPropsMaster					(SThisCode* thisCode);
	bool					iVariable_isVarTypeValid					(SThisCode* thisCode, s32 tnVarType, SVariable** varDefaultValue);
	bool					iVariable_areTypesCompatible				(SThisCode* thisCode, SVariable* var1, SVariable* var2);
	bool					iVariable_copy								(SThisCode* thisCode, SVariable* varDst, SVariable* varSrc);
	SVariable*				iVariable_copy								(SThisCode* thisCode, SVariable* varSrc, bool tlMakeReference);
	bool					iVariable_set								(SThisCode* thisCode, SVariable* varDst, SVariable* varSrc);
	void					iVariable_setVarType						(SThisCode* thisCode, SVariable* var, u32 tnVarTypeNew);
	bool					iVariable_setNumeric_toNumericType			(SThisCode* thisCode, SVariable* varDst, f32* val_f32, f64* val_f64, s32* val_s32, u32* val_u32, s64* val_s64, u64* val_u64);
	bool					iVariable_setNumeric_toDestinationType		(SThisCode* thisCode, SVariable* varDst, SVariable* varSrc);
	bool					iVariable_set_s32_toExistingType			(SThisCode* thisCode, SErrorInfo* ei, SVariable* var, s32 value);
	bool					iVariable_set_s64_toExistingType			(SThisCode* thisCode, SErrorInfo* ei, SVariable* var, s64 value);
	bool					iVariable_set_f32_toExistingType			(SThisCode* thisCode, SErrorInfo* ei, SVariable* var, f32 value);
	bool					iVariable_set_f64_toExistingType			(SThisCode* thisCode, SErrorInfo* ei, SVariable* var, f64 value);
	bool					iVariable_set_u32_toExistingType			(SThisCode* thisCode, SErrorInfo* ei, SVariable* var, u32 value);
	bool					iVariable_set_u64_toExistingType			(SThisCode* thisCode, SErrorInfo* ei, SVariable* var, u64 value);
	SDatum*					iVariable_setName							(SThisCode* thisCode, SVariable* var, cu8* tcName, s32 tnNameLength);
	bool					iVariable_set_s16							(SThisCode* thisCode, SVariable* var, s16 value);
	bool					iVariable_set_s32							(SThisCode* thisCode, SVariable* var, s32 value);
	bool					iVariable_set_u16							(SThisCode* thisCode, SVariable* var, u16 value);
	bool					iVariable_set_u32							(SThisCode* thisCode, SVariable* var, u32 value);
	bool					iVariable_set_f32							(SThisCode* thisCode, SVariable* var, f32 value);
	bool					iVariable_set_f64							(SThisCode* thisCode, SVariable* var, f64 value);
	bool					iVariable_set_logical						(SThisCode* thisCode, SVariable* var, bool tlValue);
	bool					iVariable_set_logical						(SThisCode* thisCode, SVariable* var, s32 value);
	bool					iVariable_set_bitmap						(SThisCode* thisCode, SVariable* var, SBitmap* bmp);
	bool					iVariable_set_character						(SThisCode* thisCode, SVariable* var, u8* tcData, u32 tnDataLength);
	bool					iVariable_set_character						(SThisCode* thisCode, SVariable* var, SDatum* datum);
	void					iVariable_reset								(SThisCode* thisCode, SVariable* var, bool tlTerminateIndirect);
	SVariable*				iVariable_convertForDisplay					(SThisCode* thisCode, SVariable* var);
	SVariable*				iVariable_get_typeDetail					(SThisCode* thisCode, SVariable* var);
	void					iVariable_delete							(SThisCode* thisCode, SVariable* var, bool tlDeleteSelf, bool tlOverrideDelete = false);
	void					iVariable_politelyDeleteChain				(SThisCode* thisCode, SVariable** root, bool tlDeleteSelf);
	void					iVariable_politelyDeleteChain_callback		(SLLCallback* cb);
	SVariable*				iiVariable_getAs_datetime					(SThisCode* thisCode, SVariable* var, bool tlForceConvert, bool* tlError, u32* tnErrorNum);
	bool					iiVariable_getAs_bool						(SThisCode* thisCode, SVariable* var, bool tlForceConvert, bool* tlError, u32* tnErrorNum);
	s8						iiVariable_getAs_s8							(SThisCode* thisCode, SVariable* var, bool tlForceConvert, bool* tlError, u32* tnErrorNum);
	s16						iiVariable_getAs_s16						(SThisCode* thisCode, SVariable* var, bool tlForceConvert, bool* tlError, u32* tnErrorNum);
	s32						iiVariable_getAs_s32						(SThisCode* thisCode, SVariable* var, bool tlForceConvert, bool* tlError, u32* tnErrorNum);
	u16						iiVariable_getAs_u16						(SThisCode* thisCode, SVariable* var, bool tlForceConvert, bool* tlError, u32* tnErrorNum);
	u32						iiVariable_getAs_u32						(SThisCode* thisCode, SVariable* var, bool tlForceConvert, bool* tlError, u32* tnErrorNum);
	s64						iiVariable_getAs_s64						(SThisCode* thisCode, SVariable* var, bool tlForceConvert, bool* tlError, u32* tnErrorNum);
	u64						iiVariable_getAs_u64						(SThisCode* thisCode, SVariable* var, bool tlForceConvert, bool* tlError, u32* tnErrorNum);
	f32						iiVariable_getAs_f32						(SThisCode* thisCode, SVariable* var, bool tlForceConvert, bool* tlError, u32* tnErrorNum);
	f64						iiVariable_getAs_f64						(SThisCode* thisCode, SVariable* var, bool tlForceConvert, bool* tlError, u32* tnErrorNum);
	s32						iVariable_compare							(SThisCode* thisCode, SVariable* varLeft, SVariable* varRight, bool tlForceConvert, bool* tlError, u32* tnErrorNum);
	s32						iiVariable_compareNonmatchingTypesAs_f64	(SThisCode* thisCode, SVariable* varLeft, SVariable* varRight, bool tlForceConvert, bool* tlError, u32* tnErrorNum);
	s32						iiVariable_compareNonmatchingTypesAs_s64	(SThisCode* thisCode, SVariable* varLeft, SVariable* varRight, bool tlForceConvert, bool* tlError, u32* tnErrorNum);
	s32						iiVariable_compareNonmatchingTypesAs_u64	(SThisCode* thisCode, SVariable* varLeft, SVariable* varRight, bool tlForceConvert, bool* tlError, u32* tnErrorNum);
	s32						iiVariable_compareMatchingTypes				(SThisCode* thisCode, SVariable* varLeft, SVariable* varRight, bool* tlError, u32* tnErrorNum);
	s64						iiVariable_compute_DatetimeDifference_getAs_s64(SThisCode* thisCode, SVariable* dtVar1, SVariable* dtVar2);
	f64						iiVariable_compute_DatetimeDifference_getAs_f64(SThisCode* thisCode, SVariable* dtVar1, SVariable* dtVar2);

	// Support functions
	SVariable*				iiDateMath_get_dateTemplate										(s32 tnDateFormat);
	void					iiDateMath_get_YyyyMmDdHhMmSsMssNss_from_jseconds				(u64  tnDtx, f64* tfDtx,              u32* year, u32* month, u32* day, u32* hour, u32* minute, u32* second, s32* millisecond, s32* microsecond);
	void					iiDateMath_get_julian_and_YyyyMmDdHhMmSsMssNss_from_jseconds	(u64  tnDtx, f64* tfDtx, u32* julian, u32* year, u32* month, u32* day, u32* hour, u32* minute, u32* second, s32* millisecond, s32* microsecond);
	u64						iiDateMath_get_jseconds_from_YyyyMmDdHhMmSsMssMics				(f64* tfDtx,                          u32  year, u32  month, u32  day, u32  hour, u32  minute, u32  second, s32  millisecond, s32  microsecond);
	u64						iiDateMath_get_jseconds_from_julian_and_HhMmSsMssMics			(f64* tfDtx,             u32  julian,                                  u32  hour, u32  minute, u32  second, s32  millisecond, s32  microsecond);
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
	bool					iDateMath_isValidDate											(u32 year, u32 month, u32 day);
	bool					iDateMath_isLeapYear											(u32 year);
	u32						iDateMath_getDayNumberIntoYear									(u32 tnYear, u32 tnMonth, u32 tnDay);

	// Big floating point
	s32						iiBfp_calc_significantDigits_bySize			(SVariable* varVal);
	void					iiBfp_convertForDisplay						(SThisCode* thisCode, SVariable* varDisp,	SVariable* varVal);
	void					iiBfp_convertFrom_scientificNotation		(SThisCode* thisCode, SDatum* datum,		SVariable* varVal);
	// Big integer
	s32						iiBi_calc_significantDigits_bySize			(SVariable* varVal);
	void					iiBi_convertForDisplay						(SThisCode* thisCode, SVariable* varDisp,	SVariable* varVal);
	void					iiBi_convertFrom_scientificNotation			(SThisCode* thisCode, SDatum* datum,		SVariable* varVal);


	// Op functions
	bool					iOp_setNull									(SOp* op);
	bool					iOp_setVariable_param						(SThisCode* thisCode, SOp* op, SVariable* var, bool isOpAllocated);
	bool					iOp_setVariable_local						(SThisCode* thisCode, SOp* op, SVariable* var, bool isOpAllocated);
	bool					iOp_setVariable_scoped						(SThisCode* thisCode, SOp* op, SVariable* var, bool isOpAllocated);
	bool					iOp_setVariable_return						(SThisCode* thisCode, SOp* op, SVariable* var, bool isOpAllocated);
	void					iOp_politelyDelete							(SThisCode* thisCode, SOp* op, bool tlDeleteSelf);

	// Error and warning functions
	void					iComp_appendError							(SThisCode* thisCode, SComp* comp, u32 tnErrorNum,   cu8* tcMessage);
	void					iComp_appendWarning							(SThisCode* thisCode, SComp* comp, u32 tnWarningNum, cu8* tcMessage);
	void					iComp_reportWarningsOnRemainder				(SThisCode* thisCode, SComp* comp, u32 tnWarningNum, cu8* tcMessage);


	// Line functions
	SLine*					iLine_createNew								(SThisCode* thisCode, bool tlAllocCompilerInfo);
	SLine*					iLine_appendNew								(SThisCode* thisCode, SLine* line, bool tlAllocCompilerInfo);
	SLine*					iLine_insertNew								(SThisCode* thisCode, SLine* lineRef, bool tlAllocCompilerInfo, bool tlAfter);
	void					iLine_appendError							(SThisCode* thisCode, SLine* line, u32 tnErrorNum,   cu8* tcMessage, u32 tnStartColumn, u32 tnLength);
	void					iLine_appendWarning							(SThisCode* thisCode, SLine* line, u32 tnWarningNum, cu8* tcMessage, u32 tnStartColumn, u32 tnLength);
	bool					iLine_scanComps_forward_withCallback		(SThisCode* thisCode, SLine* line, SComp* comp, SCallback* cb, bool tlSkipFirst);
	s32						iLines_unescape_iCodes						(SThisCode* thisCode, SLine* lineStart, s32 tniCode1, s32 tniCode2, s32 tniCode3, s32 tniCodeEscape = _ICODE_BACKSLASH);

	s32						iLine_migrateLines							(SThisCode* thisCode, SLine** linesFrom, SLine* lineTarget);
	SLine*					iLine_copyComps_toNewLines					(SThisCode* thisCode, SLine* lineStart, SComp* compStart, SLine* lineEnd, SComp* compEnd, bool tlLeftJustifyStart, bool tlSkipBlankLines);
	//
	SLine*					iLine_copyComps_toNewLines_untilTerminating					(SThisCode* thisCode, SLine* lineStart, SComp* compStart, s32 tniCodeContinuation, bool tlLeftJustifyStart, bool tlSkipBlankLines, SCallback* cb);
	bool					iiLine_copyComps_toNewLines_untilTerminating__callback		(SCallback* cb);
	//
	s32						iiLine_skipTo_nextComp						(SThisCode* thisCode, SLine** lineProcessing, SComp** compProcessing);
	s32						iiLine_skipTo_prevComp						(SThisCode* thiscode, SLine** lineProcessing, SComp** compProcessing);

	// Compiler functions
	SCompiler*				iCompiler_allocate							(SThisCode* thisCode, SLine* parent);
	void					iCompiler_delete							(SThisCode* thisCode, SCompiler** root, bool tlDeleteSelf);

	// Compile note functions
	SCompileNote*			iCompileNote_create							(SThisCode* thisCode, SCompileNote** noteRoot, u32 tnStart,			u32 tnEnd,			u32 tnNumber, cu8* tcMessage);
	SCompileNote*			iCompileNote_appendMessage					(SThisCode* thisCode, SCompileNote** noteRoot, u32 tnStartColumn,	u32 tnEndColumn,	u32 tnNumber, cu8* tcMessage);
	void					iCompileNote_removeAll						(SThisCode* thisCode, SCompileNote** noteRoot);
