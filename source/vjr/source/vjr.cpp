//////////
//
// /libsf/source/vjr/source/vjr.cpp
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
//     Feb.12.2014
//////
// Change log:
//     Feb.12.2014 - Initial creation
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
//
//   __      __   _
//   \ \    / /  | |
//    \ \  / /   | | _ __
//     \ \/ /_   | || '__|
//      \  /| |__| || |
//       \/  \____/ |_|
//     Visual FreePro, Jr.
//
//////////




//////////
// Only include vjr.h in this one source file
//////
	#include "vjr.h"




#if defined(__linux__)
	int main(int argc, char* argv[])
#else
	int CALLBACK WinMain(	HINSTANCE	hInstance,
							HINSTANCE	hPrevInstance,
							LPSTR		lpCmdLine,
							int			nCmdShow	)
#endif
{
	SThisCode*	thisCode = NULL;
	MSG			msg;
	HACCEL		hAccelTable;
#if defined(__linux__)
	HINSTANCE	hInstance = 0;
#endif



	//////////
	// Initialize
	//////
		ghInstance = hInstance;
		iVjr_init(&hAccelTable);
		iVjr_appendSystemLog(thisCode, (u8*)"Initialization complete");


	//////////
	// Read events
	//////
		iVjr_appendSystemLog(thisCode, (u8*)"Engage main loop");
		while (!glShuttingDown && GetMessage(&msg, null0, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		// When the WM_QUIT message is received, we exit


	//////////
	// Do allocated resource shutdown
	//////
		if (!glShuttingDown)
			iVjr_shutdown(thisCode);


	//////////
	// Return our exit code
	//////
		return((int)msg.wParam);
}




//////////
//
// Startup initialization, called from WinMain() only.
//
//////
	void iVjr_init(HACCEL* hAccelTable)
	{
		SThisCode*		thisCode = NULL;
		RECT			lrc;
		u8				logBuffer[256];
		SBitmap*		bmp;
//		SGraceParams	params;


		// Get startup time
		systemStartedTickCount	= GetTickCount();
		systemStartedMs			= iTime_getLocalMs();

		// Fixup values that can't be properly encoded at compile-time
		iObjProp_init_fixup();

		// Initialize basic data engine
		iDbf_startup(true);

		// Create a 1x1 no image bitmap placeholder
		bmpNoImage = iBmp_allocate();
		iBmp_createBySize(bmpNoImage, 1, 1, 24);

		// Initialize primitive variables
		iVariable_createDefaultValues(NULL);
		iVariable_createPropsMaster(NULL);
		iInit_createConstants();

		// Initialize our critical sections
		InitializeCriticalSection(&cs_uniqueIdAccess);
		InitializeCriticalSection(&cs_logData);

		// These arrows are used as a standard throughout the system for the size of an icon.
		// They must be loaded first.
		bmpArrowUl		= iBmp_rawLoad(cgc_arrowUlBmp);
		bmpArrowUr		= iBmp_rawLoad(cgc_arrowUrBmp);
		bmpArrowLl		= iBmp_rawLoad(cgc_arrowLlBmp);
		bmpArrowLr		= iBmp_rawLoad(cgc_arrowLrBmp);

		// Initialize our builders
		iBuilder_createAndInitialize(&gWindows,	-1);
		iBuilder_createAndInitialize(&gFonts,	-1);

		// Default font
		gsFontDefault				= iFont_create(cgcFontName_default,			10,	FW_NORMAL,	0, 0);
		gsFontDefault9				= iFont_create(cgcFontName_default,			9,	FW_NORMAL,	0, 0);
		gsFontDefaultBold			= iFont_create(cgcFontName_default,			10,	FW_BOLD,	0, 0);
		gsFontDefaultItalic8		= iFont_create(cgcFontName_default,			8,	FW_NORMAL,	1, 0);
		gsFontDefaultFixedPoint		= iFont_create(cgcFontName_defaultFixed,	10,	FW_NORMAL,	0, 0);
		gsWindowTitleBarFont		= iFont_create(cgcFontName_windowTitleBar,	12,	FW_NORMAL,	0, 0);
		gsWindowTitleBarFontSubform	= iFont_create(cgcFontName_windowTitleBar,	10,	FW_NORMAL,	0, 0);
		gsFontDefaultTooltip		= iFont_create(cgcFontName_defaultTooltip,	9,	FW_BOLD,	0, 0);
		gsFontCask					= iFont_create(cgcFontName_cask,			20, FW_BOLD,	0, 0);

		// Initialize the sound system
		isound_initialize();
		memset(&gseRootSounds, 0, sizeof(gseRootSounds));	// Initialize our root sounds array

//////////
// Jul.29.2014
// Removed due to limitations in the Shobjidl.h in MinGW.  Can be manually re-added with copy-and-paste... enjoy doing that! :-)
//		// Taskbar interface
//		HRESULT		hRes;
//		hRes = OleInitialize(NULL);
//		CoCreateInstance(CLSID_TaskbarList, 0, CLSCTX_INPROC_SERVER, IID_ITaskbarList, (void**)&giTaskbar);
//////////


		//////////
		// Allocate a sourceLight area
		//////
			bmpSourceLight = iBmp_allocate();
			iBmp_createBySize(bmpSourceLight, 800, 1024, 24);
			iSourceLight_reset();


		//////////
		// Load our icons and images
		//////
			bmpVjrIcon						= iBmp_rawLoad(cgc_appIconBmp);
			bmpJDebiIcon					= iBmp_rawLoad(cgc_jdebiAppIconBmp);
			bmpSourceCodeIcon				= iBmp_rawLoad(cgc_sourcecodeIconBmp);
			bmpLocalsIcon					= iBmp_rawLoad(cgc_localsIconBmp);
			bmpWatchIcon					= iBmp_rawLoad(cgc_watchIconBmp);
			bmpCommandIcon					= iBmp_rawLoad(cgc_commandIconBmp);
			bmpDebugIcon					= iBmp_rawLoad(cgc_debugIconBmp);
			bmpOutputIcon					= iBmp_rawLoad(cgc_outputIconBmp);
			bmpSourceLightIcon				= iBmp_rawLoad(cgc_sourcelightIconBmp);

			// Carousels
			bmpCarouselCarouselIcon			= iBmp_rawLoad(cgc_carouselCarouselBmp);
			bmpCarouselTabsIcon				= iBmp_rawLoad(cgc_carouselTabsBmp);
			bmpCarouselPad					= iBmp_rawLoad(cgc_carouselPadBmp);
			bmpCarouselIcon					= iBmp_rawLoad(cgc_carouselIconBmp);
			bmpCarouselRiderTabClose		= iBmp_rawLoad(cgc_carouselRiderTabCloseBmp);

			bmpClose						= iBmp_rawLoad(cgc_closeBmp);
			bmpMaximize						= iBmp_rawLoad(cgc_maximizeBmp);
			bmpMinimize						= iBmp_rawLoad(cgc_minimizeBmp);
			bmpMove							= iBmp_rawLoad(cgc_moveBmp);

			bmpCheckboxOn					= iBmp_rawLoad(cgc_checkboxOnBmp);
			bmpCheckboxOff					= iBmp_rawLoad(cgc_checkboxOffBmp);

			bmpButton						= iBmp_rawLoad(cgc_buttonBmp);
			bmpTextbox						= iBmp_rawLoad(cgc_textboxBmp);

			bmpStoplightRed					= iBmp_rawLoad(cgc_stoplightRedBmp);
			bmpStoplightAmber				= iBmp_rawLoad(cgc_stoplightAmberBmp);
			bmpStoplightGreen				= iBmp_rawLoad(cgc_stoplightGreenBmp);
			bmpStoplightBlue				= iBmp_rawLoad(cgc_stoplightBlueBmp);

			bmpBreakpointAlways				= iBmp_rawLoad(cgc_breakpointAlways);
			bmpBreakpointAlwaysCountdown	= iBmp_rawLoad(cgc_breakpointAlwaysCountdown);
			bmpConditionalTrue				= iBmp_rawLoad(cgc_breakpointConditionalTrue);
			bmpConditionalFalse				= iBmp_rawLoad(cgc_breakpointConditionalFalse);
			bmpConditionalTrueCountdown		= iBmp_rawLoad(cgc_breakpointConditionalTrueCountdown);
			bmpConditionalFalseCountdown	= iBmp_rawLoad(cgc_breakpointConditionalFalseCountdown);

			bmpDapple1						= iBmp_rawLoad(cgc_dappleBmp);
			bmpDapple1Tmp					= iBmp_rawLoad(cgc_dappleBmp);
			bmpDapple2						= iBmp_rawLoad(cgc_dapple2Bmp);
			bmpDapple2Tmp					= iBmp_rawLoad(cgc_dapple2Bmp);


		//////////
		// Casks
		//////
			iVjr_init_loadCaskIcons();


		//////////
		// Bitmap array
		//////
			iVjr_init_loadBitmapArray();


		//////////
		// The radio image has a 44x44 dot in the upper-left.
		//////
			bmpRadio	= iBmp_rawLoad(cgc_radioBmp);											// Load the raw bmpRadio
			bmpRadioDot = iBmp_createAndExtractRect(bmpRadio, 0, 0, 44, 44);					// Extract the 44x44 rectangle
			SetRect(&lrc, 0, 0, 44, 44);
			iBmp_fillRect(bmpRadio, &lrc, whiteColor, whiteColor, whiteColor, whiteColor, false, NULL, false);		// And cover it up with white


		if (glShowSplashScreen)
		{
			// Load the splash screen
			bmpVjrSplash = iBmp_rawLoad(cgc_splashBmp);
			bmp = iiVjr_buildSplashScreen(bmpVjrSplash);
			CreateThread(0, 0, &iSplash_show, bmp, 0, 0);
		}

		// Play the startup music if any
		sprintf((s8*)logBuffer, "VJr launched %u milliseconds after system boot\0", systemStartedTickCount);
		iVjr_appendSystemLog(thisCode, logBuffer);
		if (glShowSplashScreen)
			CreateThread(0, 0, &iPlay_ariaSplash, (LPVOID)cgcSoundStartupWav, 0, 0);

		// Focus window accumulator
		iVjr_appendSystemLog(thisCode, (u8*)"Create focus highlight buffer");
		iBuilder_createAndInitialize(&gFocusHighlights, -1);

		// Create the default reference datetimes
		iVjr_appendSystemLog(thisCode, (u8*)"Create default datetime variables");
		iInit_createDefaultDatetimes();

		// Create our message window
		iVjr_appendSystemLog(thisCode, (u8*)"Create message window");
		iInit_createMessageWindow();

		// Create our global variables
		iVjr_appendSystemLog(thisCode, (u8*)"Create global and system variables");
		iInit_createGlobalSystemVariables();

		// Create our default objects
		iVjr_appendSystemLog(thisCode, (u8*)"Create default objects");
		iInit_createDefaultObjects();

		// Create our main screen window
		iVjr_appendSystemLog(thisCode, (u8*)"TEMPORARY:  Manually create _jdebi");
		iInit_jdebi_create();

		// Initially render each one
		iVjr_appendSystemLog(thisCode, (u8*)"Render _jdebi");
		iObj_render(NULL, _jdebi, true);

		// Attach them to physical windows
		iVjr_appendSystemLog(thisCode, (u8*)"Allocate OS Window for _jdebi");
		gWinJDebi = iWindow_allocate();
		iObj_createWindowForForm(NULL, _jdebi, gWinJDebi, IDI_JDEBI);

		// Initially populate _screen
		// Load in the history if it exists
		if (!iSEM_loadFromDisk(thisCode, NULL, screenData, cgcScreenDataFilename, false, true))
		{
			// Indicate success
			sprintf((s8*)logBuffer, "Loaded: %s\0", cgcScreenDataFilename);
			iSEM_appendLine(thisCode, _output_editbox->p.sem, logBuffer, (s32)strlen(logBuffer), false);
			iVjr_appendSystemLog(thisCode, (u8*)"Populate _screen with default data");
			iSEM_appendLine(thisCode, screenData, (u8*)cgcScreenTitle, -1, false);
			iSEM_appendLine(thisCode, screenData, NULL, 0, false);
			iSEM_appendLine(thisCode, screenData, (u8*)"Please report any bugs:  http://www.visual-freepro.org/vjr", -1, false);
			iSEM_appendLine(thisCode, screenData, (u8*)"Thank you, and may the Lord Jesus Christ bless you richly. :-)", -1, false);
			iSEM_appendLine(thisCode, screenData, NULL, 0, false);
			iSEM_appendLine(thisCode, screenData, (u8*)"              _____              In God's sight we've come together.", -1, false);
			iSEM_appendLine(thisCode, screenData, (u8*)"             |     |             We've come together to help each other.", -1, false);
			iSEM_appendLine(thisCode, screenData, (u8*)"             |     |             Let's grow this project up ... together!", -1, false);
			iSEM_appendLine(thisCode, screenData, (u8*)"     ________|     |________     In service and love to The Lord, forever!", -1, false);
			iSEM_appendLine(thisCode, screenData, (u8*)"    |                       |", -1, false);
			iSEM_appendLine(thisCode, screenData, (u8*)"    |________       ________|    Sponsored by:", -1, false);
			iSEM_appendLine(thisCode, screenData, (u8*)"             |     |                 LibSF -- Liberty Software Foundation", -1, false);
			iSEM_appendLine(thisCode, screenData, (u8*)"             |     |", -1, false);
			iSEM_appendLine(thisCode, screenData, (u8*)"             |     |    Contributors:", -1, false);
			iSEM_appendLine(thisCode, screenData, (u8*)"             |     |        Hernan Cano, Stefano D'Amico", -1, false);
			iSEM_appendLine(thisCode, screenData, (u8*)"             |     |", -1, false);
			iSEM_appendLine(thisCode, screenData, (u8*)"             |     |    Lead Project Contact:  rick.c.hodgin@gmail.com", -1, false);
			iSEM_appendLine(thisCode, screenData, (u8*)"             |     |", -1, false);
			iSEM_appendLine(thisCode, screenData, (u8*)"             |     |    We need more coders. Please consider helping out.", -1, false);
			iSEM_appendLine(thisCode, screenData, (u8*)"             |_____|    Your contribution would make a difference. :-)", -1, false);
			iSEM_appendLine(thisCode, screenData, NULL, 0, false);
		}
		// Navigate to the end of the content
		iSEM_navigateToEndLine(thisCode, screenData, _screen);

		// Initially populate _jdebi
		// Load in the history if it exists
		if (!iSEM_loadFromDisk(thisCode, NULL, _command_editbox->p.sem, cgcCommandHistoryFilename, true, true))
		{
			// Indicate success
			sprintf((s8*)logBuffer, "Loaded: %s\0", cgcCommandHistoryFilename);
			iSEM_appendLine(thisCode, _output_editbox->p.sem, logBuffer, (s32)strlen(logBuffer), false);
			iSEM_appendLine(thisCode, _command_editbox->p.sem, (u8*)"*** Welcome to Visual FreePro, Junior! :-)", -1, false);
			iSEM_appendLine(thisCode, _command_editbox->p.sem, (u8*)"*** For now, this can be thought of as a command window ... with a twist.", -1, false);
			iSEM_appendLine(thisCode, _command_editbox->p.sem, (u8*)"*** It works like an editor window.  You can insert new lines, edit old ones, etc.", -1, false);
			iSEM_appendLine(thisCode, _command_editbox->p.sem, (u8*)"*** To execute a command, press F6. If you're on the last line use F6 or Enter.", -1, false);
			iSEM_appendLine(thisCode, _command_editbox->p.sem, (u8*)"*** See http://www.visual-freepro.org/wiki/index.php/VXB for supported commands.", -1, false);
			iSEM_appendLine(thisCode, _command_editbox->p.sem, (u8*)"*** Remember always:  Love makes you smile. It keeps an inner peace like no other. :-)", -1, false);
		}

		// Navigate to the last line
		iSEM_navigateToEndLine(thisCode, _command_editbox->p.sem, _command_editbox);

		// Make sure there's a blank line at the end
		if (_command_editbox->p.sem->line_cursor->sourceCode_populatedLength != 0)
		{
			iSEM_appendLine(thisCode, _command_editbox->p.sem, NULL, 0, false);
			iSEM_navigateToEndLine(thisCode, _command_editbox->p.sem, _command_editbox);
		}

		// Load some source code
		if (iSEM_loadFromDisk(thisCode, _sourceCode_rider, _sourceCode_editbox->p.sem, cgcStartupPrgFilename, true, true))
		{
			// Indicate success
			sprintf((s8*)logBuffer, "Loaded: %s\0", cgcStartupPrgFilename);
			iSEM_appendLine(thisCode, _output_editbox->p.sem, logBuffer, (s32)strlen(logBuffer), false);
		}

		// Redraw
		iVjr_appendSystemLog(thisCode, (u8*)"Final render _jdebi");
		iWindow_render(NULL, gWinJDebi, true);

		// Remove the splash screen 1/2 second later
		CreateThread(0, 0, &iSplash_delete, (LPVOID)500, 0, 0);

// 		// Create a thread to display the content in 3D
//		memset(&params, 0, sizeof(params));
//		params._func_mouse			= (uptr)&iGrace_mouse;
//		params._func_motion			= (uptr)&iGrace_motion;
//		params._func_passiveMotion	= (uptr)&iGrace_passiveMotion;
//		params._func_key			= (uptr)&iGrace_key;
//		params._func_special		= (uptr)&iGrace_special;
//		params._func_reshape		= (uptr)&iGrace_reshape;
//		params._func_display		= (uptr)&iGrace_display;
//		params._func_idle			= (uptr)&iGrace_idle;
//		CreateThread(0, 0, &iGrace, (LPVOID)&params, 0, 0);
	}
