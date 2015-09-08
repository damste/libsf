//////////
//
// /libsf/source/vjr/source/dbf/cdx_defs.h
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
// Version 0.55
// Copyright (c) 2014 by Rick C. Hodgin
//////
// Last update:
//     Dec.22.2014
//////
// Change log:
//     Dec.22.2014 - Initial creation
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




struct SThisCode;




//////////
//
// CDX related
// Note:  Many of the functions referred to in these functions are defined in dbf_defs.h.
//
//////
	u32					cdx_open										(SThisCode* thisCode, SWorkArea* wa, s8* tcCdxFilename, u32 tnCdxFilenameLength, u32 tnExplicitIndexType, bool tlValidate, bool tlDescending);
	u32					cdx_close										(SThisCode* thisCode, SWorkArea* wa);
	u32					cdx_get_tag										(SThisCode* thisCode, SWorkArea* wa,
																			u32 tnTagIndex,
																			s8* tcTagName,		u32 tnTagNameLength,
																			s8* tcExpression,	u32 tnExpressionLength,
																			s8* tcForClause,	u32 tnForClauseLength,
																			s8* tcKeyLength4,
																			s8* tcUnique1,
																			s8* tcCompact1,
																			s8* tcCompound1,
																			s8* tcOrder1);

	u32					cdx_find_key									(SThisCode* thisCode, u32 tnWorkArea, s32 tnTagIndex, u8* tcKey, u32 tnKeyLength);
	u32					cdx_build_and_find_key							(SThisCode* thisCode, u32 tnWorkArea, s32 tnTagIndex, u32 tnKeyLength);
	u32					cdx_skip_n										(SThisCode* thisCode, u32 tnWorkArea, s32 tnTagIndex, s32 tnDelta);
	u32					cdx_top											(SThisCode* thisCode, u32 tnWorkArea, s32 tnTagIndex);
	u32					cdx_bottom										(SThisCode* thisCode, u32 tnWorkArea, s32 tnTagIndex);

	u32					cdx_validate_tag								(SThisCode* thisCode,
																			u32 tnWorkArea,		s32 tnTagIndex,
																			s8* tcMetaData,		u32 tnMetaDataLength,
																			s8* tcErrorsFound,	u32 tnErrorsFoundLength);

	u32					cdx_validate_keys								(SThisCode* thisCode,
																			u32 tnWorkArea,			s32 tnTagIndex,
																			s8* tcMetaData,			u32 tnMetaDataLength,
																			s8* tcErrorsFound,		u32 tnErrorsFoundLength);

	u32					cdx_get_all_keys								(SThisCode* thisCode,
																			u32 tnWorkArea,				s32 tnTagIndex,
																			u8* tcKeySpace,				u32 tnKeySpaceLength,
																			u8* tcDecodeExpression,		u32 tnDecodeExpressionLength,
																			s8* tcKeyLength4);

	bool				iCdx_validateIdx								(SThisCode* thisCode, SWorkArea* wa, s8* tcMetaData, u32 tnMetaDataLength, s8* tcErrorsFound, u32 tnErrorsFoundLength);
	bool				iCdx_validateIdx_compact						(SThisCode* thisCode, SWorkArea* wa, s8* tcMetaData, u32 tnMetaDataLength, s8* tcErrorsFound, u32 tnErrorsFoundLength);
	bool				iCdx_validateIdx_standard						(SThisCode* thisCode, SWorkArea* wa, s8* tcMetaData, u32 tnMetaDataLength, s8* tcErrorsFound, u32 tnErrorsFoundLength);
	s32					iCdx_validateCdx								(SThisCode* thisCode, SWorkArea* wa, s32 tnTagIndex, s8* tcMetaData, u32 tnMetaDataLength, s8* tcErrorData, u32 tnErrorDataLength);
	s32					iCdx_validateCdxKeys							(SThisCode* thisCode, SWorkArea* wa, u32 tnWorkArea, s32 tnTagIndex, s8* tcMetaData, u32 tnMetaDataLength, s8* tcErrorsFound, u32 tnErrorsFoundLength);
	int					iiKeys_qsortDescending_callback					(const void* l, const void* r);
	int					iiKeys_qsortAscending_callback					(const void* l, const void* r);
	s32					iCdx_validateIdxKeys							(SThisCode* thisCode, SWorkArea* wa, s8* tcMetaData, u32 tnMetaDataLength, s8* tcErrorsFound, u32 tnErrorsFoundLength);


//////////
// These are for extracting and re-generating keys in a node, and for adding and deleting nodes
// BEGIN
//////
	SCdxNodeCache*		iCdx_cacheNode									(SThisCode* thisCode, SWorkArea* wa, SCdxHeader* tagHeader, s32 tnNodeNum, SCdxNode** nodeDst);
	SCdxNodeCache*		iiCdx_cacheNode_allocate						(SThisCode* thisCode, SWorkArea* wa, SCdxHeader* tagHeader, s32 tnNodeNum, bool tlAutoPopulate);
	void				iiCdx_cacheNode_populate						(SThisCode* thisCode, SWorkArea* wa, SCdxHeader* tagHeader, SCdxNodeCache* nodeKeys, bool tlAllocateLiberally);
	void				iiCdx_cacheNode_depopulate						(SThisCode* thisCode, SWorkArea* wa, SCdxHeader* tagHeader, SCdxNodeCache* nodeKeys);
	void				iiCdx_cacheNode_delete							(SThisCode* thisCode, SWorkArea* wa, SCdxHeader* tagHeader, SCdxNodeCache* nodeKeys, bool tlImmediateReuse);
//////
// END
//////////


//////////
// These are for generating new keys from DBF data, or from manual data loaded for index finds
// BEGIN
//////
	SCdxKeyOp*			iiCdx_generateKey_buildOps						(SThisCode* thisCode, SWorkArea* wa, u8* keyExpression, s32* tnKeyOpCount);
	bool				iiCdx_generateKey_buildOps_markClosingParenthesis(SThisCode* thisCode, u8* leftParenthesis, u8 fixupAscii);
	u32					iiCdx_generateKey								(SThisCode* thisCode, SWorkArea* wa, SCdxHeader* head, u8* keyOut);
	void				iiCdx_generateKey_byOps							(SThisCode* thisCode, SWorkArea* wa, SCdxKeyOp* keyOps, s32 tnKeyOpCount, u8* keyOut, bool tlBuildFromIndexData);
	void				iiCdx_generateKey_byOps_fixup_swapEndian		(SThisCode* thisCode, SCdxKeyOp* lko, u8* keyPart);
	void				iiCdx_generateKey_byOps_fixup_date				(SThisCode* thisCode, SCdxKeyOp* lko, u8* keyPart);
	void				iiCdx_generateKey_byOps_fixup_double			(SThisCode* thisCode, SCdxKeyOp* lko, u8* keyPart);
	void				iiCdx_generateKey_byOps_fixup_numeric			(SThisCode* thisCode, SCdxKeyOp* lko, u8* keyPart, SWorkArea* wa);
	bool				iiCdx_generateKey_byOps_fixup					(SThisCode* thisCode, SWorkArea* wa, SCdxKeyOp* keyOps, s32 tnKeyOpCount, u8* keyOut, bool tlIsCdxKey);
	bool				iiCdx_get_buildOps								(SThisCode* thisCode, SWorkArea* wa, s32 tnTagIndex, SCdxHeader* tagHeader, SForClause** tsFor, SCdxKeyOp** tsKeyOp, u32* tnKeyOpCount, u32* tnResult);
//////
// END
//////////


//////////
// Index navigation
// BEGIN
//////
	s32					iCdx_findKey									(SThisCode* thisCode, SWorkArea* wa, STagRoot* tagRoot, u8* keyBuffer, u32 tnKeyLength);

	s32					iCdx_gotoTop									(SThisCode* thisCode, SWorkArea* wa);
	s32					iCdx_skip										(SThisCode* thisCode, SWorkArea* wa, s32 tnDelta);
	s32					iCdx_gotoBottom									(SThisCode* thisCode, SWorkArea* wa);

	s32					iIdx_gotoTop									(SThisCode* thisCode, SWorkArea* wa);
	s32					iIdx_skip										(SThisCode* thisCode, SWorkArea* wa, s32 tnDelta);
	s32					iIdx_gotoBottom									(SThisCode* thisCode, SWorkArea* wa);
//////
// END
//////////


	s32					iiCdx_translateActualResultThroughIndexOrder	(STagRoot* tagRoot, u8* keyLeft, u8* keyRight, u32 tnKeyLength);
	u32					iCdx_getAllKeysCdx								(SThisCode* thisCode, SWorkArea* wa, s32 tnTagIndex, u8* tcKeySpace, u32 tnKeySpaceLength, u8* tcDecodeExpression, u32 tnDecodeExpressionLength, s8* tcKeyLength4);
	u32					iCdx_getAllKeysIdx								(SThisCode* thisCode, SWorkArea* wa,                 u8* tcKeySpace, u32 tnKeySpaceLength, u8* tcDecodeExpression, u32 tnDecodeExpressionLength, s8* tcKeyLength4);
	bool				iCdx_setActiveTag								(SThisCode* thisCode, SWorkArea* wa, s32 tnTagIndex, STagRoot* tagRoot, bool* tlError, u32* tnErrorNum);
	bool				iCdx_getRootmostCompoundTag_byTagnum			(SThisCode* thisCode, SWorkArea* wa, SCdxHeader* head, SCdxNode* node, s32 lnTagNum, STagRoot* tagRoot);
	bool				iCdx_getCompactRootNode							(SThisCode* thisCode, SWorkArea* wa, SCdxHeader* head, SCdxNode* node,               STagRoot* tagRoot);
	bool				iCdx_getStandardRootNode						(SThisCode* thisCode, SWorkArea* wa, SIdxHeader* head, SIdxNode* node,               STagRoot* tagRoot);
	bool				iiCdx_isCompact									(SThisCode* thisCode, SCdxHeader* head);
	bool				iiCdx_isCompound								(SThisCode* thisCode, SCdxHeader* head);
	bool				iiCdx_isUnique									(SThisCode* thisCode, SCdxHeader* head);
	bool				iiCdx_isDescending								(SThisCode* thisCode, SCdxHeader* head);
	bool				iiCdx_isPrimaryKeySet							(SThisCode* thisCode, SWorkArea* wa);
	bool				iCdx_isForClauseComplex							(SThisCode* thisCode, SWorkArea* wa, SCdxHeader* head, SForClause** tsFor);
	SIdxNode*			iCdx_getStandardIdxNode_byNumber				(SThisCode* thisCode,                SIdxHeader* head, u32 tnNodeNumber);
	SIdxNode*			iCdx_getStandardIdxNode_byOffset				(SThisCode* thisCode,                SIdxHeader* head, u32 tnOffset);
	bool				iCdx_getStandardIdxKey_byNumber					(SThisCode* thisCode,                SIdxHeader* head, u8 tcFillChar, u32 tnNumber, SIdxNode* node, SIdxKey* key, STagRoot* tagRoot, bool tlFixupEndian, bool tlFixupSignBit);
	SCdxNode*			iCdx_getCompactIdxNode_byNumber					(SThisCode* thisCode,                SCdxHeader* head, u32 tnNodeNumber);
	SCdxNode*			iCdx_getCompactIdxNode_byOffset					(SThisCode* thisCode,                SCdxHeader* head, u32 tnOffset);
	bool				iCdx_getCompactIdxKey_byNumber					(SThisCode* thisCode,                SCdxHeader* head, u32 keyLength, u8 tcFillChar, u32 tnKeyNumber, u32 tnKeyNumberThis, SCdxNode* node, SCdxKeyLeafRaw* key, STagRoot* tagRoot, bool tlFixupEndian, bool tlFixupSignBit);
	u32					iCdx_descendToLeftmostNode						(SThisCode* thisCode,                SCdxHeader* head, u32 keyLength, SCdxNode* node, STagRoot* tagRoot);
	// Internal functions that do not have special testing
	void				iiCdx_extractExteriorNode_nodeKeyAccessData		(SThisCode* thisCode, SCdxNode* node, u32 tnNumber, SCdxKeyTrail* keyTrail);


//////////
// These are for non-exclusive use indexes
// BEGIN
//////
	uptr				iiCdx_lock_file									(SThisCode* thisCode, SWorkArea* wa, STagRoot* tagRoot);
	uptr				iiCdx_lock_node									(SThisCode* thisCode, SWorkArea* wa, STagRoot* tagRoot, s32 tnNode);
	uptr				iiCdx_lock_range								(SThisCode* thisCode, SWorkArea* wa, STagRoot* tagRoot, s32 tnOffset, s32 tnLength);
	bool				iiCdx_unlock									(SThisCode* thisCode, SWorkArea* wa, SDiskLock* dl);
//////
// END
//////////
