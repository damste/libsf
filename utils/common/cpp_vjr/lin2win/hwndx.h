//////////
//
// /libsf/utils/common/cpp/linux/hwndx.h
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
// Copyright (c) 2015 by Rick C. Hodgin
//////
// Last update:
//     Jan.17.2014
//////
// Change log:
//     Jan.17.2014 - Initial creation
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
//  _       _         ___             _
// | |     (_)       |__ \           (_)
// | |      _  _ __     ) |__      __ _  _ __
// | |     | || '_ \   / / \ \ /\ / /| || '_ \
// | |____ | || | | | / /_  \ V  V / | || | | |
// |______||_||_| |_||____|  \_/\_/  |_||_| |_|
//     Linux to Windows -- Emulation Layer
//
//////////




#include "/libsf/utils/common/cpp/builder.h"
#include "/libsf/utils/common/cpp/datum.h"


#define _X11_OK					0
#define _X11_NO_DISPLAY			-1
#define _X11_UNSUPPORTED		-2
#define _X11_NO_WINDOW			-3
#define _X11_NO_VIRTUAL_SCREEN	-4
#define _X11_NO_PIXEL_BUFFER	-5
#define _X11_VIRTALLOC			-6
#define _X11_GENERAL_FAILURE	-99

struct SBitmap;
struct SFont;
struct SClassX;
struct SHwndX;
struct SHdcX;
struct STimerX;
struct SRegionRectX;
struct SRegionX;




//////////
// Windows Hwnd -to- X-Windows translation
//////
	struct SXWindow
	{
		Display*		display;
		Window			window;
		Screen*			screenptr;
		s32				drawable;
		Visual*			visual;
		GC				gc;

		XImage*			ximage;
		SBgra*			virtualscreen;
		s32				screensize;

		XImage*			ximage2;
		SBgra*			virtualscreen2;
		s32				screensize2;

		s32				width;
		s32				height;
		s32				depth;
		s32				pixelsize;

	} __attribute__((packed));


	struct SClassX
	{
		bool			isValid;
		WNDCLASSEX		wcx;
		SDatum			cClass;

	} __attribute__((packed));

	struct SHwndX
	{
		// For Windows
		uptr			hwnd;
		bool			isValid;
		bool			isVisible;
		bool			isEnabled;
		bool			isActive;
		pthread_t		nThreadId;
		RECT			rc;
		RECT			rcClient;
		SBuilder*		msgQueue;

		// Note:  Both of these contain the trailing NULL in their length ... this is done because some callbacks require ASCIIZ strings
		SDatum			cClass;
		SDatum			cTitle;

		// Current mouse and keyboard flags
		uptr			mouseKbdFlags;
		POINT			mousePt;

		// Structure used for callbacks
		CREATESTRUCT	data;
		SClassX*		clsx;
		SHdcX*			hdcx;

		// For X-windows
		SXWindow*		x11;

		// For region
		SRegionX*		regionx;
		Pixmap			regionPixmap;		// Built from the SRegionX structure at the time of SetWindowRgn() as it sizes to the window

	} __attribute__((packed));

	struct SMessageX
	{
		MSG				msg;

	} __attribute__((packed));

	struct STimerX
	{
		bool		isValid;
		s32			timerId;		// Linux id from timer_create()
		itimerspec	its;			// Linux-based interval data

		// User parameters
		sptr		nIDEvent;		// User-supplied id
		s32			interval;		// User-supplied millisecond interval

		// Windows callback if winAssociated != NULL, and _timerFunc != 0
		SHwndX*		winAssociated;
		union {
			sptr			_timerFunc;
			void CALLBACK	(*timerFunc)(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime);
		};

	} __attribute__((packed));

	struct SHdcX
	{
		bool		isValid;
		HDC			hdc;

		// Current settings for the device context
		SFont*		font;
		bool		isOpaque;
		SBgra		colorFore;
		SBgra		colorBack;

		// Bitmaps take on the size of the thing they belong to, so they may be constantly resized
		SBitmap*	bmp;

	} __attribute__((packed));

	struct SDesktopX
	{
		Display*	display;

		s32			screen;
		s32			depth;
		s32			connection;
		Window		windowDesktop;

	} __attribute__((packed));

	struct SFontX
	{
		bool		isValid;

		int			nHeight;
		int			nWidth;
		int			nEscapement;
		int			nOrientation;
		int			nWeight;
		DWORD		lItalic;
		DWORD		lUnderline;
		DWORD		lStrikeOut;
		DWORD		nCharSet;
		DWORD		nOutPrecision;
		DWORD		nClipPrecision;
		DWORD		nQuality;
		DWORD		nPitchAndFamily;
		SDatum		faceName;
		TEXTMETRIC	tm;

		Font			font;
		XFontStruct*	fontData;

	} __attribute__((packed));

	struct SBrushX
	{
		bool		isValid;
		bool		isSolidBrush;

		SBgra		color;

	} __attribute__((packed));

#define _REGION_RECT_OP_DRAW	1

	struct SRegionRectX
	{
		RECT		rc;					// Logical rectangle
		s32			op;					// How is this rectangle applied to the region stack, see RGN_* constants

	} __attribute__((packed));

	struct SRegionX
	{
		bool		isValid;

		SBuilder*	regionArray;		// SRegionRectX structures

	} __attribute__((packed));




//////////
// Prototype definitions
//////
	bool			iHwndX_postMessage_byWin				(SHwndX* win,	uptr message, uptr wParam, uptr lParam);
	bool			iHwndX_postMessage_byHwnd				(HWND hWnd,		uptr message, uptr wParam, uptr lParam);
	SHwndX*			iHwndX_declareDesktopHwnd				(void);
	DWORD			iHwndX_getTime							(void);
	SHwndX*			iHwndX_findWindow_byHwnd				(HWND hWnd);
	SHwndX*			iHwndX_findWindow_byHdcx				(SHdcX* hdcx);
	SHdcX*			iHwndX_findHdc_byHdc					(HDC hdc);
	SClassX*		iHwndX_findClass_byName					(cs8* lpClassName);
	void			iHwndX_createWindow						(SHwndX* win);
	SXWindow*		iHwndX_createXWindow					(SHwndX* win);
	void			iHwndX_deleteXWindow					(SHwndX* win);
	SHdcX*			iHwndX_createHdc						(s32 tnWidth, s32 tnHeight, SBitmap* bmp);
	s32				iHwndX_initializeXWindow				(SXWindow* win, s32 width, s32 height, s8* title);
	bool			iHwndX_addTimer							(SHwndX* win, sptr nIDEvent, UINT uElapse, sptr lpTimerFunc);
	void			iHwndX_deleteTimer						(SHwndX* win, sptr nIDEvent);
	SFontX*			iHwndX_getNextFont						(void);
	SBrushX*		iHwndX_createBrush						(bool isSolidBrush, uptr data);
	SBrushX*		iHwndX_deleteBrush						(HBRUSH hbr);
	SBrushX*		iHwndX_findBrush_byBrush				(HBRUSH hbr);
	SRegionX*		iHwndX_createRegion						(void);
	void			iHwndX_deleteRegion						(SHwndX* win);


//////////
// Global variables
//////
	SBuilder*		gsWindows								= NULL;
	SBuilder*		gsClasses								= NULL;
	SBuilder*		gsHdcs									= NULL;
	SBuilder*		gsTimers								= NULL;
	SBuilder*		gsHfonts								= NULL;
	SBuilder*		gsBrushes								= NULL;
	SBuilder*		gsRegions								= NULL;

	// Holds mouse position relative to the desktop
	POINT			gnMouseDesktop							= { 0, 0 };

	// "Desktop" window related
	SHwndX*			gsDesktopWindow							= iHwndX_declareDesktopHwnd();
	SDesktopX		gsDesktop;
	HWND			ghWndDesktop							= null0;

	cs8				cgcDesktop[]							= "_desktop";
