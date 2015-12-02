//////////
//
// /libsf/source/vjr/bitmaps.h
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
//     Nov.27.2014
//////
// Change log:
//     Nov.27.2014 - Initial creation
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



class CXml;


//////////
// Constants
//////
	#define					_FILL_RECT_OP_AND						1
	#define					_FILL_RECT_OP_OR						2
	#define					_FILL_RECT_OP_XOR						3


//////////
// Function prototypes
//////
	SBitmap*				iBmp_allocate							(void);
	SBitmap*				iBmp_copy								(SBitmap* bmpSrc);
	SBitmap*				iBmp_arrayBmp_copy						(CXml* baseArrayBmp, SBitmap* baseBmp[], s8* tcName, u32 tnNameLength);
	SBitmap*				iBmp_arrayBmp_getRef						(CXml* baseArrayBmp, SBitmap* baseBmp[], s8* tcName, u32 tnNameLength);
	SBitmap*				iBmp_verifyCopyIsSameSize				(SBitmap* bmpCopy, SBitmap* bmp);
	SBitmap*				iBmp_verifySizeOrResize					(SBitmap* bmp, u32 tnWidth, u32 tnHeight, u32 tnBitCount);
	SBitmap*				iBmp_rawLoad							(cu8* bmpRawFileData);
	SBitmap*				iBmp_isValidCache						(SBmpCache** bmpCache,               u32 data1, u32 data2, u32 data3, u32 data4, u32 data5, u32 data6, u32 data7, u32 data8, u32 data9, u32 data10, u32 data11, u32 data12, u32 data13, u32 data14);
	SBitmap*				iBmp_createCache						(SBmpCache** bmpCache, SBitmap* bmp, u32 data1, u32 data2, u32 data3, u32 data4, u32 data5, u32 data6, u32 data7, u32 data8, u32 data9, u32 data10, u32 data11, u32 data12, u32 data13, u32 data14, bool tlCopyBitmap);
	SBitmap*				iBmp_deleteCache						(SBmpCache** bmpCache);
	void					iBmp_saveToDisk							(SBitmap* bmp, s8* tcPathname);
	void					iBmp_convertTo32Bits					(SBitmap* bmp);
	void					iBmp_convertTo24Bits					(SBitmap* bmp);
	void					iBmp_copy24To32							(SBitmap* bmp32, SBitmap* bmp24);
	bool					iBmp_validate							(SBitmap* bmp);
	s32						iBmp_computeRowWidth					(SBitmap* bmp);
	void					iBmp_createBySize						(SBitmap* bmp, u32 width, u32 height, u32 tnBitCount);
	void					iBmp_populateBitmapStructure			(SBitmap* bmp, u32 tnWidth, u32 tnHeight, u32 tnBitCount);
	void					iBmp_delete								(SBitmap** bmp, bool tlFreeBits, bool tlDeleteSelf, bool tlDeleteFont = true);
	void					iBmp_invert								(SBitmap* bmp, s32 tnUlX, s32 tnUlY, s32 tnLrX, s32 tnLrY);
	void					iBmp_bitBltObject						(SBitmap* bmpDst, SObject* obj, SBitmap* bmpSrc);
	void					iBmp_bitBltObjectMask					(SBitmap* bmpDst, SObject* obj, SBitmap* bmpSrc);
	u32						iBmp_bitBlt								(SBitmap* bmpDst, RECT* trc, SBitmap* bmpSrc);
	u32						iBmp_bitBlt_rotated						(SBitmap* bmpDst, RECT* trc, SBitmap* bmpSrc, s32 tnDegrees_90_180_270);
	u32						iBmp_bitBltAlpha						(SBitmap* bmpDst, RECT* trc, SBitmap* bmpSrc, f32 alpha);
	u32						iBmp_grayscale							(SBitmap* bmp, RECT* trc);
	u32						iBmp_colorize							(SBitmap* bmp, RECT* trc, SBgra colorTemplate, bool clampColor, f32 minColor);
	u32						iBmp_colorizeMask						(SBitmap* bmp, RECT* trc, SBgra colorTemplate, bool clampColor, f32 minColor);
	u32						iBmp_swapColors							(SBitmap* bmp, SBgra colorOld, SBgra colorNew);
	u32						iBmp_alphaColorizeMask					(SBitmap* bmp, RECT* trc, SBgra colorAlpha, f32 alpha);
	u32						iBmp_bitBltMask							(SBitmap* bmpDst, RECT* trc, SBitmap* bmpSrc);
	u32						iBmp_bitBlt_byGraymask					(SBitmap* bmpDst, RECT* trc, SBitmap* bmpSrc, SBgra color);
	SBitmap*				iBmp_createAndExtractRect				(SBitmap* bmpSrc, s32 tnUlX, s32 tnUlY, s32 tnLrX, s32 tnLrY);
	HRGN					iBmp_extractRgnByMask					(SBitmap* bmp, RECT* trc);
	u32						iBmp_wavyLine							(SBitmap* bmp, RECT* trc, SBgra color);
	u32						iBmp_roundCorners						(SBitmap* bmp, s32 tnType, SBgra color);
	SBgra					iBmp_extractColorAtPoint				(SBitmap* bmp, s32 tnX, s32 tnY);
	SBgra					iBmp_colorCombine						(SBgra color1, SBgra color2, f32 tfAlp);
	bool					iBmp_locateMarker						(SBitmap* bmp, u8 red, u8 grn, u8 blu, u32* tnX, u32* tnY, bool tlOverwriteMarker);
	SBitmap*				iBmp_cask_createAndPopulate				(s32 iCode, s32 tnWidth, s32 tnHeight, s32* tnSkipChars, u32 tnTextLength, SBgra* backColor, SBgra textColor, SBgra backgroundColor, bool tlOverrideColors);
	SBitmap*				iBmp_nbsp_createAndPopulate				(SComp* comp, SFont* font, f32 tfMinColor, f32 tfMaxColor, s32 tnWidth, s32 tnHeight, SBgra backColor, SBgra textColor);
	void					iBmp_colorizeAsCommonTooltipBackground	(SBitmap* bmp);
	void					iBmp_colorizeHighlightGradient			(SBitmap* bmp, RECT* rc, SBgra color, f32 tfLeftOpaque, f32 tfRightOpaque);
	void					iBmp_dapple								(SBitmap* bmp, SBitmap* bmpDapple, SBitmap* bmpDappleTmp, f32 tfBias, f32 tfInfluence);
// TODO:  The following void functions need to be changed to u32 and indicate how many pixels were rendered
	void					iBmp_drawPoint							(SBitmap* bmp, s32 tnX, s32 tnY, SBgra color);
	void					iBmp_drawBullet							(SBitmap* bmp, s32 tnX, s32 tnY, SBgra color);
	void					iBmp_fillRect							(SBitmap* bmp, RECT* rc, SBgra colorNW, SBgra colorNE = whiteColor, SBgra colorSW = whiteColor, SBgra colorSE = whiteColor, bool tlUseGradient = false, RECT* rcClip = NULL, bool tluseClip = false);
	void					iBmp_fillRect_op						(SBitmap* bmp, RECT* rc, SBgra colorOn, SBgra colorOff, u32 tnOp);
	void					iBmp_frameRect							(SBitmap* bmp, RECT* rc, SBgra colorNW, SBgra colorNE = whiteColor, SBgra colorSW = whiteColor, SBgra colorSE = whiteColor, bool tlUseGradient = false, RECT* rcClip = NULL, bool tluseClip = false);
	void					iBmp_colorizeRect						(SBitmap* bmp, RECT* rc, SBgra colorNW, SBgra colorNE = whiteColor, SBgra colorSW = whiteColor, SBgra colorSE = whiteColor, bool tlUseGradient = false, RECT* rcClip = NULL, bool tluseClip = false, f32 alpha = 1.0f);
	void					iiBmp_frameInNineParts					(SBitmap* bmpDst, RECT* trc, SBitmap* bmpFrame);
	void					iiBmp_bitBltPortion						(SBitmap* bmpDst, s32 tnX, s32 tnY, s32 tnWidth, s32 tnHeight, SBitmap* bmpSrc, s32 tnXStart, s32 tnYStart);
	void					iBmp_drawArbitraryLine					(SBitmap* bmp, s32 tnX1, s32 tnY1, s32 tnX2, s32 tnY2, SBgra color);
	void					iBmp_drawArbitraryQuad					(SBitmap* bmp, s32 tnX1, s32 tnY1, s32 tnX2, s32 tnY2, s32 tnWidth, bool tlDrawEnds, SBgra color);
	void					iBmp_drawHorizontalLine					(SBitmap* bmp, s32 tnX1, s32 tnX2, s32 tnY, SBgra color);
	void					iBmp_drawVerticalLine					(SBitmap* bmp, s32 tnY1, s32 tnY2, s32 tnX, SBgra color);
	void					iBmp_drawHorizontalLineGradient			(SBitmap* bmp, s32 tnX1, s32 tnX2, s32 tnY, f32 tfRed, f32 tfGrn, f32 tfBlu, f32 tfRedInc, f32 tfGrnInc, f32 tfBluInc, RECT* rcClip, bool tluseClip);
	void					iBmp_drawVerticalLineGradient			(SBitmap* bmp, s32 tnY1, s32 tnY2, s32 tnX, f32 tfRed, f32 tfGrn, f32 tfBlu, f32 tfRedInc, f32 tfGrnInc, f32 tfBluInc, RECT* rcClip, bool tluseClip);
	void					iBmp_colorizeHorizontalLine				(SBitmap* bmp, s32 tnX1, s32 tnX2, s32 tnY, SBgra color, f32 alpha);
	void					iBmp_colorizeVerticalLine				(SBitmap* bmp, s32 tnY1, s32 tnY2, s32 tnX, SBgra color, f32 alpha);
	void					iBmp_colorizeHorizontalLineGradient		(SBitmap* bmp, s32 tnX1, s32 tnX2, s32 tnY, f32 tfRed, f32 tfGrn, f32 tfBlu, f32 tfRedInc, f32 tfGrnInc, f32 tfBluInc, RECT* rcClip, bool tluseClip, f32 alpha);
	void					iBmp_colorizeVerticalLineGradient		(SBitmap* bmp, s32 tnY1, s32 tnY2, s32 tnX, f32 tfRed, f32 tfGrn, f32 tfBlu, f32 tfRedInc, f32 tfGrnInc, f32 tfBluInc, RECT* rcClip, bool tluseClip, f32 alpha);
	f32						iiBmp_squeezeColorChannel				(f32 color, f32 minColor);
	u32						iiBmp_setPixel							(SBitmap* bmp, s32 tnX, s32 tnY, SBgra color);

	// For nodes
	void					iBmp_node_renderComp					(SNode* node, s32 tnMaxTokenLength, s32 tnMaxOverallLength, SNodeProps props[], s32 tnPropsCount, u32 tnIter_uid);

	//////////
	// For scaling
	//////
		u32					iBmp_scale								(SBitmap* bmpScaled, SBitmap* bmp);
		u32					iiBmp_scale_Process						(SBitmap* bmpDst, SBitmap* bmpSrc, f32 tfVerticalScaler, f32 tfHorizontalScaler);
		void				iiBmp_scale_processPixels				(SBitmapProcess* bp);
		void				iiBmp_scale_processSpannedPixel1		(SBitmapProcess* bp);
		void				iiBmp_scale_processSpannedPixel2		(SBitmapProcess* bp);
		void				iiBmp_scale_processSpannedPixel3		(SBitmapProcess* bp);
		void				iiBmp_scale_processSpannedPixel4		(SBitmapProcess* bp);
		void				iiBmp_scale_processSpannedPixel5		(SBitmapProcess* bp);
		void				iiBmp_scale_processSpannedPixel6		(SBitmapProcess* bp);
		void				iiBmp_scale_processSpannedPixel7		(SBitmapProcess* bp);
		void				iiBmp_scale_processSpannedPixel8		(SBitmapProcess* bp);
		void				iiBmp_scale_processSpannedPixel9		(SBitmapProcess* bp);
		u32					iiBmp_scale_processGetIntegersBetween	(f32 p1, f32 p2);
	//////
	// End
	//////////
