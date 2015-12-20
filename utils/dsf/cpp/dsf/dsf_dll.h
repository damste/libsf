//////////
//
// /libsf/utils/dsf/msvc++/dsf/dsf/dsf.h
//
//////
//
//
//////
// Version 0.60
// Copyright (c) 2013 by Rick C. Hodgin
//////
// Last update:
//     Dec.02.2013
//////
// Change log:
//     Dec.02.2013	- Initial creation
//////
//
// Top-level program for DSF.DLL. Contains all helper algorithms for creating binary characters
// of existing font sets for translation into the DSF format.
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
//     http://www.visual-freepro.org/wiki/index.php/Repeat_License
//
// Thank you.  And may The Lord bless you richly as you lift up your life, your
// talents, your gifts, your praise, unto Him.  In Jesus' name I pray.  Amen.
//
//////




#pragma once

// Modify the following defines if you have to target a platform prior to the ones specified below.
// Refer to MSDN for the latest info on corresponding values for different platforms.
#ifndef WINVER                          // Specifies that the minimum required platform is Windows Vista.
#define WINVER 0x0600           // Change this to the appropriate value to target other versions of Windows.
#endif

#ifndef _WIN32_WINNT            // Specifies that the minimum required platform is Windows Vista.
#define _WIN32_WINNT 0x0600     // Change this to the appropriate value to target other versions of Windows.
#endif

#ifndef _WIN32_WINDOWS          // Specifies that the minimum required platform is Windows 98.
#define _WIN32_WINDOWS 0x0410 // Change this to the appropriate value to target Windows Me or later.
#endif

#ifndef _WIN32_IE                       // Specifies that the minimum required platform is Internet Explorer 7.0.
#define _WIN32_IE 0x0700        // Change this to the appropriate value to target other versions of IE.
#endif

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <Shobjidl.h>

#include "\libsf\utils\common\cpp\common_types.h"


//////////
// Source code files to include
//////
	#include "\libsf\utils\common\cpp\datum.h"
	#include "\libsf\utils\common\cpp\datum.cpp"
	#include "\libsf\utils\common\cpp\builder.h"
	#include "\libsf\utils\common\cpp\builder.cpp"
	#include "\libsf\utils\common\cpp\scale.h"
	#include "\libsf\utils\common\cpp\scale.cpp"
	#include "\libsf\utils\common\cpp\dsf.h"
	#include "\libsf\utils\common\cpp\dsf.cpp"




//////////
// Forward declarations
//////
	// Functions visible in the DLL (see dsf.def)
	int					dsf_get_character_bitmap				(int tnAscii, s8* tcBitmapFilename, s8* tcFloanFilename, s8* tcFontName, int tnHeight, int tnWidth);
	int					dsf_scale_and_clip_bitmap				(s8* tcBitmapFilenameIn, s8* tcBitmapFilenameOut, f64 tfWidth, f64 tfHeight, int tnClipLeft, int tnClipTop, int tnNewWidth, int tnNewHeight);
	int					dsf_create_new_instance					(void);
	int					dsf_load_font							(u32 tnInstance,	f64 tfAscent,	f64 tfUpper,	f64 tfLower,		f64 tfLeft,			f64 tfRight,
																					f64 tfBase,		f64 tfDescent,	f64 tfWidth,
																					f64 tfItalics,	f64 tfBold,		f64 tfUnderTop,		f64 tfUnderBot,		f64 tfStrikeTop,	f64 tfStrikeBot);
	int					dsf_load_character						(u32 tnInstance,	u32 tnType, u32 tiid, u32 tiOrder, s8* tcDesc10, u32 tlNewStroke, u32 tlSelected,
																					f64 tfOx, f64 tfOy, f64 tfOt, f64 tfLr, f64 tfLt, f64 tfRr, f64 tfRt, 
																					u32 tiSubdivs, u32 tiLnkId, u32 tiLnkOrder);
	int					dsf_load_reference						(u32 tnInstance,	u32 tnType, s8* tcDesc40,
																					f64 tfRef1X, f64 tfRef1Y,
																					f64 tfRef2X, f64 tfRef2Y,
																					f64 tfRef3X, f64 tfRef3Y,
																					f64 tfRef4X, f64 tfRef4Y,
																					f64 tfRef5X, f64 tfRef5Y,
																					bool tlVisible, s8* tcChars1_128, s8* tcChars2_128);
	int					dsf_load_template						(u32 tnInstance, u32 tipid, f64 tfX, f64 tfY, u32 tnRecno);
	void				dsf_initial_load_complete				(u32 tnInstance, u32 tnWidth, u32 tnHeight);
	int					dsf_get_changed_template				(u32 tnInstance, u32 tipid, s8* tcY12, s8* tcX12, s8* tcRecno12, u32 tnNextNewRecno);
	int					dsf_get_deleted_template				(u32 tnInstance, u32 tipid, s8* tcRecno12);
	int					dsf_user_cues							(u32 tnInstance,	u32 tnAscent,			u32 tnTrackAscent, 
																					u32 tnUpper,			u32 tnTrackUpper, 
																					u32 tnLower,			u32 tnTrackLower, 
																					u32 tnBase,				u32 tnTrackBase, 
																					u32 tnDescent,			u32 tnTrackDescent, 
																					u32 tnStrikethrough,	u32 tnTrackStrike, 
																					u32 tnUnderline,		u32 tnTrackUnderline, 
																					u32 tnRefs,				u32 tnTrackRefs);
	int					dsf_user_cues2							(u32 tnInstance,	u32 tlLeft,		u32 tnTrackLeft, 
																					u32 tlRight,	u32 tnTrackRight, 
																					u32 tlWidth,	u32 tnTrackWidth, 
																					u32 tlTems,		u32 tnTrackTems,
																					u32 tlGrid,		u32 tnTrackGrid);
	int					dsf_user_settings						(u32 tnInstance,	u32 tnDisposition, u32 tnMode, u32 tnMethod, u32 tnRange,
																					u32 tlShowSplines, u32 tnSplinesType,
																					u32 tlHighlighSelection, u32 tlShowPenDowns,
																					u32 tlMouseCrosshairX, u32 tlMouseCrosshairY,
																					u32 tlInvert,
																					u32 tlZoomLens,
																					u32 tlCuesUnder, 
																					u32 tnSelectArea);
	int					dsf_set_active_character				(u32 tnInstance, u32 tiid);
	int					dsf_set_active_tool						(u32 tnInstance, u32 tnToolNumber);
	int					dsf_get_hwnd_contents					(u32 tnHwnd, s8* tcBitmapFilename);
	int					dsf_scaled_interface_to_hwnd			(u32 tnHwnd, s8* tcIdentifer, f32 tfInitialScale);
	int					dsf_window_on_taskbar					(u32 tnHwnd, u32 tnShow);
	int					dsf_render_markup						(u32 tnInstance, s32 tnWidth, s32 tnHeight, u32 tlBold, u32 tlItalic, u32 tlUnderline, u32 tlStrikethrough, s8* tcBitmapPathname, u32 tnHwnd, s32 tnX, s32 tnY, s32 tnControlX, s32 tnControlY, s32 tnControlWidth, s32 tnControlHeight);
	int					dsf_render_final						(u32 tnInstance, s32 tnWidth, s32 tnHeight, u32 tlBold, u32 tlItalic, u32 tlUnderline, u32 tlStrikethrough, s8* tcBitmapPathname, u32 tnHwnd, s32 tnX, s32 tnY);
	int					dsf_re_render							(u32 tnInstance, u32 tnHwnd);


	// From DllMain
	void				iSetPoint								(SXYF64* p, f64 x, f64 y);
	void				iCopyPoint								(SXYF64* pDst, SXYF64* pSrc);
	void				initialize								(void);
	SSpline* 			iAddSplineFromToLR						(SBuilder* b, bool tlPenDown, f64 tfXL, f64 tfYL, f64 tfXR, f64 tfYR);
	SSpline* 			iAddSplineCenterThetaRadiusLR			(SBuilder* b, bool tlPenDown, f64 tfX, f64 tfY, f64 tfRadius, f64 tfThetaL, f64 tfThetaR);

	// Bitmaps
	int					iGetCharacterBitmap						(int tnAscii, s8* tcBitmapFilename, s8* tcFontName, int tnHeight, int tnWidth);
	int					iSaveBitmapByParams						(BITMAPFILEHEADER* tbh, BITMAPINFOHEADER* tbi, SBGR* tbd, s8* tcBitmapFilename);
	int					iSaveBitmap								(SBGR* tbd, int tnWidth, int tnHeight, int tnLeft, s8* tcBitmapFilename, int tnMakeWidth);
	int					iComputeRowWidth						(int tnWidth);
	HBITMAP				iCreateBitmap							(HDC thdc, int tnWidth, int tnHeight, int tnPlanes, int tnBits, void** tbd, BITMAPFILEHEADER* tbh, BITMAPINFOHEADER* tbi);


	// Floans
	int					iGetFloanFromBitmap						(u32 tnAscii, s8* tcBitmapFilename, s8* tcFloanFilename);
	int					iiGetFloanFromBitmap_qsortCallback		(const void* l, const void* r);

	// General purpose
	SInstance*			iGetDsfInstance							(u32 tnHandle, bool* tlValid);
	SSpline*			iFindSplineInstance						(SBuilder* charsBuilder, u32 tnIid, u8 tcType, u32 tiOrder, u32 tiLnkId, u32 tiLnkOrder);
	SChars*				iiFindOrCreateThisChars					(SBuilder* charsBuilder, u32 tnIid);
	SChars*				iiFindOnlyThisChars						(SBuilder* charsBuilder, u32 tnIid);
	SSpline*			iFindSplineInstance_SD					(SBuilder* thisSplineBuilder, u32 tnIid, u32 tiOrder, bool tlAddIfNotFound);
	SSpline*			iFindSplineInstance_R					(SBuilder* thisSplineBuilder, u32 tnIid, u32 tiOrder, u32 tiLnkId, bool tlAddIfNotFound);
	SSpline*			iFindSplineInstance_L					(SBuilder* thisSplineBuilder, u32 tnIid, u32 tiOrder, u32 tiLnkId, u32 tiLnkOrder, bool tlAddIfNotFound);
	SRefs*				iFindRefsInstance						(SBuilder* refs, u8 tcType, s8* tcDesc40);
	STems*				iCreateNewTemsEntry						(SBuilder* charsBuilder, u32 tipid);
	SBuilder*			iGetTemsRawBuilder						(SBuilder* charsBuilder, u32 tipid);

	int					iRender									(SInstance* p, SHwnd* h, SChars* c, s32 tnWidth, s32 tnHeight, u32 tnHwndParent, s32 tnX, s32 tnY);
	void				iRenderMouseCoordinates					(SInstance* p, SHwnd* h);
	void				iRenderCues								(SInstance* p, SHwnd* h, SChars* c);
	void				iRenderCueLineH							(SInstance* p, SHwnd* h, SChars* c, f64 tfPosition, SBGR color);
	void				iRenderCueLineV							(SInstance* p, SHwnd* h, SChars* c, f64 tfPosition, SBGR color);
	void				iRenderQuadH							(SInstance* p, SHwnd* h, SChars* c, f64 tfTop, f64 tfBottom, SBGR color);
	void				iRenderRefs								(SInstance* p, SHwnd* h, SChars* c);
	void				iRenderGrid								(SInstance* p, SHwnd* h);
	void				iRenderSplines							(SInstance* p, SHwnd* h, SChars* c, u32 tlMarkup, u32 tlBold, u32 tlItalic, u32 tlUnderline, u32 tlStrikethrough);
	SBGR				iSetLineColor							(SInstance* p);
	void				iDrawPenDown							(SHwnd* h, SLineF64* line);
	void				iDrawPenUp								(SHwnd* h, SLineF64* line);
	void				iRenderHint								(SHwnd* h, SLineF64* line, SXYF64* pt);
	void				iComputeLOR								(SSpline* s, SXYF64* pl, SXYF64* po, SXYF64* pr);
	void				iComputeQuadColorsR						(SSpline* s, SSpline* sLast, SBGR quadNormal, SBGR quadSelected, SBGR* p1ColorR, SBGR* p2ColorR, SBGR* p3ColorR, SBGR* p4ColorR);
	void				iComputeQuadColorsL						(SSpline* s, SSpline* sLast, SBGR quadNormal, SBGR quadSelected, SBGR* p1ColorL, SBGR* p2ColorL, SBGR* p3ColorL, SBGR* p4ColorL);
	void				iDrawPoints								(SInstance* p, SHwnd* h, SXYF64* pr, SXYF64* po, SXYF64* pl, SSpline* s, SBGR colorSelected, SBGR colorR, SBGR colorO, SBGR colorL, SBGR colorRSelected, SBGR colorOSelected, SBGR colorLSelected, SBGR colorLine);
	void				iDrawLine								(SHwnd* h, SXYF64* p1, SXYF64* p2, SBGR colorStart, SBGR colorEnd, f64 tfPower);
	void				iDrawLineAlpha							(SHwnd* h, SXYF64* p1, SXYF64* p2, SBGR_AF64* colorStart, SBGR_AF64* colorEnd, SBuilder* pointsDrawn, bool tlNoDuplicates, f64 tfPower);
	void				iDrawPoint								(SHwnd* h, SXYF64* p1, SBGR color);
	void				iDrawPointSmall							(SHwnd* h, SXYF64* p1, SBGR color);
	void				iDrawPointLarge							(SHwnd* h, SXYF64* p1, SBGR color);
	void				iDrawMouse								(SHwnd* h, SXYS32* p);
	void				iDrawHorizontalLineByPixels				(SHwnd* h, s32 x1, s32 x2, s32 y, SBGR color);
	void				iFillQuadAlpha							(SHwnd* h, SXYF64* p1, SXYF64* p2, SXYF64* p3, SXYF64* p4, SBGR p1Color, SBGR p2Color, SBGR p3Color, SBGR p4Color, f64 tfP1Alp, f64 tfP2Alp, f64 tfP3Alp, f64 tfP4Alp, f64 tfPower);
	void				iRenderMouseOverlay						(SInstance* p, SHwnd* h, SChars* c);
	bool				iComputeClosestMouseLine				(SLineF64* line);
	void				iColorizeAndProcessHorizontalLineByPixels(SInstance* p, SHwnd* h, SChars* c, s32 x1, s32 x2, s32 y, SBGR color);
	void				iColorizeHorizontalLineByPixels			(SInstance* p, SHwnd* h, SChars* c, s32 x1, s32 x2, s32 y, SBGR color);
	void				iColorizeAndProcessVerticalLineByPixels	(SInstance* p, SHwnd* h, SChars* c, s32 y1, s32 y2, s32 x, SBGR color);
	void				iColorizeVerticalLineByPixels			(SInstance* p, SHwnd* h, SChars* c, s32 y1, s32 y2, s32 x, SBGR color);
	void				iRenderTems								(SInstance* p, SHwnd* h, SChars* c);
	void				iInvertImage							(SHwnd* h);
	void				iRenderZoomLens							(SHwnd* h);
	u32					iScaleIntoRange							(s32 tnValue, s32 tnValueMax, s32 tnMinRange, s32 tnMaxRange);
	u32					iValidateRange							(s32 tnValue, s32 tnValueMin, s32 tnValueMax, s32 tnDefaultValue);
	void				iMakeSureLowToHighU32					(u32* p1, u32* p2);
	void				iMakeSureLowToHighS32					(s32* p1, s32* p2);
	void				iMakeSureLowToHighF64					(f64* p1, f64* p2);
	int					iiTems_qsortCallback					(const void* l, const void* r);
	int					iiSXyS32_qsortCallback					(const void* l, const void* r);
	int					iiSPointsDrawn_qsortCallback			(const void* l, const void* r);
	u32					iiRenderMarkup_getNextLineSegment		(u32 tnIndex, u32 tnMaxCount, SHwnd* h, STems* root, STems** p1, STems** p2);
	s32					iiGetPoint								(f64 tfValue01, s32 tnMultiplier);
	SHwnd*				iFindOnlyHwndByHwnd						(SBuilder* hwnds, u32 tnHwndParent, u32 tnHwnd);
	SHwnd*				iFindOnlyHwndByHwndControl				(SBuilder* hwnds, u32 tnHwndParent, u32 tnHwndControl);
	SHwnd*				iFindOnlyHwndByHwndParent				(SBuilder* hwnds, u32 tnHwndParent);
	SHwnd*				iFindOnlyHwnd							(SBuilder* hwnds, u32 tnHwndParent, s32 tnX, s32 tnY, s32 tnWidth, s32 tnHeight);
	SHwnd*				iFindOrCreateHwnd						(SBuilder* hwnds, u32 tnHwndParent, s32 tnX, s32 tnY, s32 tnWidth, s32 tnHeight, u32 tlMarkup);
	u32					iCreateWindow							(SHwnd* h);
	u32					iCreateControlWindow					(SHwnd* h, u32 tnX, u32 tnY, u32 tnW, u32 tnH);
	void				iComputeLine							(SLineF64* line);
	void				iComputeLineFromTwoPoints				(SLineF64* line, SXYF64* p1, SXYF64* p2);
	void				iConstrainQuadAroundLine				(SLineF64* lineRef, SXYF64* p1, SXYF64* p2, SXYF64* p3, SXYF64* p4, f64 tfp1Max, f64 tfp2Max, f64 tfp3Max, f64 tfp4Max, bool tlForceSize);
	void				iConstrainLineLength					(SXYF64* po, SXYF64* pToConstrain, f64 tfMaxLength, bool tlForceToLength);
	f64					iAdjustTheta							(f64 tfTheta);
	s32					iComputeQuad							(SXYF64* p);
	void				iSelectRange							(SInstance* p, SHwnd* h, SChars* c, SXYF64* p1, SXYF64* p2);
	void				iSelectPoint							(SInstance* p, SSpline* spline, bool* tlSelected);
	void				iSelectSpline							(SInstance* p, SSpline* spline);
	void				iSelectStroke							(SInstance* p, SSpline* splineStrokeStart);
	void				iSelectStrokeBefore						(SInstance* p, SSpline* splineStrokeStart, SSpline* splineStrokeEnd);
	void				iSelectStrokeAfter						(SInstance* p, SSpline* splineStrokeStart);
	void				iSplineCompute							(SSpline* spline, SXYF64* pl, SXYF64* po, SXYF64* pr);
	bool				iIsPointInRange							(SXYF64* pTest, SXYF64* ul, SXYF64* lr);
	void				iReadMousePosition						(SInstance* p, SHwnd* h);
	LRESULT CALLBACK	iControlWindowProcCallback				(HWND hwnd, UINT m, WPARAM w, LPARAM l);
	LRESULT CALLBACK	iWindowProcCallback						(HWND hwnd, UINT m, WPARAM w, LPARAM l);
