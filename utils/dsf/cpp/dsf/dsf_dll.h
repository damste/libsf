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
// Windows used for rendering previews atop VFP forms
//////
	struct SDsf_hwnd
	{
		union {
			HWND	hwndParent;						// The parent HWND to which this hwnd is a child
			u32		_hwndParent;					// Accessible value of the parent window
		};
		bool		isValid;						// When a window is no longer a window, it is marked isValid=false

		// The last settings
		u32			markup;							// The last setting passed for the markup condition for rendering
		u32			bold;							// The last bold setting
		u32			italic;							// The last italic setting
		u32			underline;						// The last underline setting
		u32			strikethrough;					// The last strikethrough setting

		// Coordinates
		s32			x;								// X position on the parent hwnd's client area
		s32			y;								// Y position on the parent hwnd's client area
		s32			w;								// Window width
		s32			h;								// Window height

		// Data used expressly for the generated bitmap, and rendering it locally on windows
		union {
			HWND			hwnd;					// The HWND handle of the render window
			u32				_hwnd;					// u32 form
		};
		WNDPROC				oldWndProcAddress;		// Used for re-directing window handling through our DLL
		WNDPROC				oldWndParentProcAddress;// Used for re-directing window handling through our DLL
		BITMAPFILEHEADER	bh;						// Bitmap header if this bitmap is written to disk
		BITMAPINFOHEADER	bi;						// Bitmap info
		RECT				rc;						// Same as SetRect(&rc, 0, 0, w, h)
		s32					rowWidth;				// How wide is each row (rounded up to nearest 32-bit boundary)
		HDC					hdc;					// Device context when window was created
		HBITMAP				hbmp;					// Handle to DIBSection
		SBgr*				bd;						// Pointer to literal bit data for the active window buffer
		HBRUSH				backDarkGrayBrush;		// Color used for dark gray background brush
		HFONT				fontXY;					// Font for rendering X,Y coordiantes in the lower-right

		// Copied out each time something is rendered
		HDC					hdc2;					// Device context when window was created
		HBITMAP				hbmp2;					// Handle to DIBSection
		SBgr*				bd2;					// Copy of bd used for rendering real-time mouse data

		// For editing the markup
		u32					tool;					// The current tool in use

		// Used for the contextual control window display / input on markup windows
		BITMAPFILEHEADER	bhControl;				// Bitmap header if this bitmap is written to disk
		BITMAPINFOHEADER	biControl;				// Bitmap info
		RECT				rcControl;
		union {
			HWND			hwndControl;			// The HWND handle of the control window
			u32				_hwndControl;			// u32 form
		};
		HDC					hdcControl;				// Device context when window was created
		HBITMAP				hbmpControl;			// Handle to DIBSection
		SBgr*				bdControl;				// Pointer to literal bit data for the active window buffer

	};




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


	// Support functions
	int					iDsf_get_character_bitmap				(int tnAscii, s8* tcBitmapFilename, s8* tcFloanFilename, s8* tcFontName, int tnHeight, int tnWidth);
	int					iDsf_scale_and_clip_bitmap				(s8* tcBitmapFilenameIn, s8* tcBitmapFilenameOut, f64 tfWidth, f64 tfHeight, int tnClipLeft, int tnClipTop, int tnNewWidth, int tnNewHeight);
	int					iDsf_create_new_instance				(void);
	int					iDsf_load_font							(u32 tnInstance,	f64 tfAscent,	f64 tfUpper,	f64 tfLower,		f64 tfLeft,			f64 tfRight,
																	f64 tfBase,		f64 tfDescent,	f64 tfWidth,
																	f64 tfItalics,	f64 tfBold,		f64 tfUnderTop,	f64 tfUnderBot,		f64 tfStrikeTop,	f64 tfStrikeBot);
	
	int					iDsf_load_character						(u32 tnInstance,	u32 tnType, u32 tiid, u32 tiOrder, s8* tcDesc10, u32 tlNewStroke, u32 tlSelected,
																	f64 tfOx, f64 tfOy, f64 tfOt, f64 tfLr, f64 tfLt, f64 tfRr, f64 tfRt, 
																	u32 tiSubdivs, u32 tiLnkId, u32 tiLnkOrder);
	
	int					iDsf_load_reference						(u32 tnInstance,	u32 tnType, s8* tcDesc40,
																	f64 tfRef1X, f64 tfRef1Y,
																	f64 tfRef2X, f64 tfRef2Y,
																	f64 tfRef3X, f64 tfRef3Y,
																	f64 tfRef4X, f64 tfRef4Y,
																	f64 tfRef5X, f64 tfRef5Y,
																	bool tlVisible, s8* tcChars1_128, s8* tcChars2_128);
	
	int					iDsf_load_template						(u32 tnInstance, u32 tipid, f64 tfX, f64 tfY, u32 tnRecno);
	void				iDsf_initial_load_complete				(u32 tnInstance, u32 tnWidth, u32 tnHeight);
	int					iDsf_get_changed_template				(u32 tnInstance, u32 tipid, s8* tcY12, s8* tcX12, s8* tcRecno12, u32 tnNextNewRecno);
	int					iDsf_get_deleted_template				(u32 tnInstance, u32 tipid, s8* tcRecno12);
	
	int					iDsf_user_cues							(u32 tnInstance,	u32 tnAscent,			u32 tnTrackAscent, 
																	u32 tnUpper,			u32 tnTrackUpper, 
																	u32 tnLower,			u32 tnTrackLower, 
																	u32 tnBase,				u32 tnTrackBase, 
																	u32 tnDescent,			u32 tnTrackDescent, 
																	u32 tnStrikethrough,	u32 tnTrackStrike, 
																	u32 tnUnderline,		u32 tnTrackUnderline, 
																	u32 tnRefs,				u32 tnTrackRefs);
	
	int					iDsf_user_cues2							(u32 tnInstance,	u32 tlLeft,		u32 tnTrackLeft, 
																	u32 tlRight,	u32 tnTrackRight, 
																	u32 tlWidth,	u32 tnTrackWidth, 
																	u32 tlTems,		u32 tnTrackTems,
																	u32 tlGrid,		u32 tnTrackGrid);
	
	int					iDsf_user_settings						(u32 tnInstance,
																	u32 tnDisposition, u32 tnMode, u32 tnMethod, u32 tnRange,
																	u32 tlShowSplines, u32 tnSplinesType,
																	u32 tlHighlighSelection, u32 tlShowPenDowns,
																	u32 tlMouseCrosshairX, u32 tlMouseCrosshairY,
																	u32 tlInvert,
																	u32 tlZoomLens,
																	u32 tlCuesUnder, 
																	u32 tnSelectArea);
	
	int					iDsf_set_active_character				(u32 tnInstance, u32 tiid);
	int					iDsf_set_active_tool					(u32 tnInstance, u32 tnToolNumber);
	int					iDsf_get_hwnd_contents					(u32 tnHwnd, s8* tcBitmapFilename);
	int					iDsf_scaled_interface_to_hwnd			(u32 tnHwnd, s8* tcIdentifer, f32 tfInitialScale);
	int					iDsf_window_on_taskbar					(u32 tnHwnd, u32 tnShow);
	int					iDsf_render_markup						(u32 tnInstance, s32 tnWidth, s32 tnHeight, u32 tlBold, u32 tlItalic, u32 tlUnderline, u32 tlStrikethrough, s8* tcBitmapPathname, u32 tnHwnd, s32 tnX, s32 tnY, s32 tnControlX, s32 tnControlY, s32 tnControlWidth, s32 tnControlHeight);
	int					iDsf_render_final						(u32 tnInstance, s32 tnWidth, s32 tnHeight, u32 tlBold, u32 tlItalic, u32 tlUnderline, u32 tlStrikethrough, s8* tcBitmapPathname, u32 tnHwnd, s32 tnX, s32 tnY);
	int					iDsf_re_render							(u32 tnInstance, u32 tnHwnd);

	// Bitmaps
	int					iGetCharacterBitmap						(int tnAscii, s8* tcBitmapFilename, s8* tcFontName, int tnHeight, int tnWidth);
	int					iSaveBitmapByParams						(BITMAPFILEHEADER* tbh, BITMAPINFOHEADER* tbi, SBgr* tbd, s8* tcBitmapFilename);
	int					iSaveBitmap								(SBgr* tbd, int tnWidth, int tnHeight, int tnLeft, s8* tcBitmapFilename, int tnMakeWidth);
	int					iComputeRowWidth						(int tnWidth);
	HBITMAP				iCreateBitmap							(HDC thdc, int tnWidth, int tnHeight, int tnPlanes, int tnBits, void** tbd, BITMAPFILEHEADER* tbh, BITMAPINFOHEADER* tbi);

	// Floans
	int					iGetFloanFromBitmap						(u32 tnAscii, s8* tcBitmapFilename, s8* tcFloanFilename);
	int					iiGetFloanFromBitmap_qsortCallback		(const void* l, const void* r);

	// Windows
	u32					iDsf_createWindow						(SDsf_hwnd* h);
	u32					iDsf_createControlWindow				(SDsf_hwnd* h, u32 tnX, u32 tnY, u32 tnW, u32 tnH);
	LRESULT CALLBACK	iDsf_control_wndProc_callback			(HWND hwnd, UINT m, WPARAM w, LPARAM l);
	LRESULT CALLBACK	iDsf_wndProc_callback					(HWND hwnd, UINT m, WPARAM w, LPARAM l);


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
