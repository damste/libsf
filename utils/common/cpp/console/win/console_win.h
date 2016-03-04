//////////
//
// /libsf/utils/common/cpp/console/win/console_win.h
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
//     Jan.12.2016
//////
// Change log:
//     Jan.12.2016 - Initial creation
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
// 	   _____                      _      
// 	  / ____|                    | |     
// 	 | |     ___  _ __  ___  ___ | | ___ 
// 	 | |    / _ \| '_ \/ __|/ _ \| |/ _ \
// 	 | |___| (_) | | | \__ \ (_) | |  __/
// 	  \_____\___/|_| |_|___/\___/|_|\___|
//      LibSF -- Generic console support
//////////




#include <windows.h>


//////////
// Fixed point fonts
//////
	#include "\libsf\utils\common\cpp\include\fonts\font8x6.h"
	#include "\libsf\utils\common\cpp\include\fonts\font8x8.h"
	#include "\libsf\utils\common\cpp\include\fonts\font8x14.h"
	#include "\libsf\utils\common\cpp\include\fonts\font8x16.h"


//////////
// Required forward declarations (oh C, oh C ... may you soon be replaced with CAlive)
//////
	struct SConsole;
	struct SBuilder;
	struct SBuilderCallback;
	struct SConFont;
	struct SConRow;


//////////
// Windows-related structures used for SConFont data
//////
	struct SConFont_fixed
	{
		// ASCII-0 begins at offset 0, ASCII-N begins at (N * nHeight * nWidth), up through ASCII-255
		u8*			fontBase;				// Either (1) one of gxFontBase_* from the font*.h files in console_win.h, or (2) a custom scaled font which needs free()'d when completed
		bool		lCustomScaled;			// Indicates if fontBase is a custom scaled font or not

		// Per character for rendering
		s32			nCharWidth;				// Number of pixels columns per character
		s32			nCharHeight;			// Number of pixels rows per character

		// Original source size
		u8*			fontBase_original;		// Always one of gxFontBase_* from the font*.h files in console_win.h
		s32			nFontX;					// Width of original font that was used
		s32			nFontY;					// Height of original font that was used
	};


//////////
// Startup code
//////
	#define console_main_function									int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
	#define console_unit_tests										console_win_unit_test(hInstance, hPrevInstance, lpCmdLine, nCmdShow)
	#define console_os_validate_initialization						console_win_validateInitialization
	#define console_os_toggle_visible								console_win_toggle_visible
	#define console_os_release										console_win_release
	#define console_os_error										console_win_error
	#define console_os_font_setup									console_win_fontSetup

	#define SConsole_os_struct_variables							HWND	hwnd;	\
																	RECT	rc; \
																	HBRUSH	hbrBackground; \
																	HDC		hdc;

	#define SConFont_os_struct_variables							/* For fixed-point internal fonts: */ \
																	SConFont_fixed* fontBase_fixed; \
																	/* For system fonts: */ \
																	HFONT		hfont; \
																	TEXTMETRIC	tm; \
																	s32			_sizeUsedForCreateFont; \
																	HDC			hdc;

	#define SConChar_os_struct_variables							/* No special SConChar variables are defined in Windows */




//////////
// Global variables
//////
	HINSTANCE			ghInstance;
	cs8					cgc_consoleClass[]							= "LibSF.Console.Class";
	SBuilder*			gsFontFixedRoot								= NULL;			// SConFont_fixed holds every scaled font structure in use




//////////
// Forward declarations
//////
	int					console_win_unit_test						(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
	bool				console_win_validateInitialization			(void);
	s32					console_win_create_window					(SConsole* console);
	s32					console_win_toggle_visible					(SConsole* console);
	s32					console_win_release							(SConsole* console);
	s32					console_win_error							(SConsole* console, s32 tnErrorNum);
	bool				console_win_fontSetup						(SConsole* console, SConFont* font);
	void				iConsole_win_fontSetup_scaleAsNeeded		(SConsole* console, SConFont* font);
	SConFont_fixed*		iConsole_win_fontSetup_searchOrCreate		(s32 tnCharWidth, s32 tnCharHeight, s32 tnFontX, s32 tnFontY, bool tlCreateIfNotFound);
	void				iConsole_win_fontSetup_scalePhysically		(SConFont_fixed* fontFixed);
	ATOM				MyRegisterClass								(void);
	void				iConsole_win_render							(SConsole* console);
	void				iConsole_win_render_singleRow				(SConsole* console, RECT* rc, SConRow* row);
	LRESULT CALLBACK	console_wndProc								(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	SConsole*			iConsole_win_find_byHwnd					(HWND hwnd);
	bool				iConsole_win_find_byHwnd__callback			(SBuilderCallback* cb);
