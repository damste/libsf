//////////
//
// /libsf/source/vjr/source/vjr_init.cpp
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
//     Aug.10.2015
//////
// Change log:
//     Aug.10.2015 - Initial creation
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




//////////
//
// Startup initialization, called from WinMain() only.
//
//////
	void iVjr_init(HACCEL* hAccelTable)
	{
		SThisCode*		thisCode = NULL;
		RECT			lrc;
#if !defined(_NONVJR_COMPILE)
		u8				logBuffer[256];
		SBitmap*		bmp;
#if defined(_GRACE_COMPILE)
		SGraceParams	params;
#endif
#endif


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
		iVariable_createDefaultValues();
		iVariable_createPropsMaster();
		iVjr_init_createConstants();

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
		gsFontDefault				= iFont_create(cgcFontName_default,				10,	FW_NORMAL,	0, 0);
		gsFontDefault9				= iFont_create(cgcFontName_default,				9,	FW_NORMAL,	0, 0);
		gsFontDefaultBold			= iFont_create(cgcFontName_default,				10,	FW_BOLD,	0, 0);
		gsFontDefaultItalic8		= iFont_create(cgcFontName_default,				8,	FW_NORMAL,	1, 0);
		gsFontDefaultFixedPoint		= iFont_create(cgcFontName_defaultFixed,		10,	FW_NORMAL,	0, 0);
		gsWindowTitleBarFont		= iFont_create(cgcFontName_windowTitleBar,		11,	FW_NORMAL,	0, 0);
		gsWindowTitleBarFontSubform	= iFont_create(cgcFontName_subwindowTitleBar,	10,	FW_NORMAL,	0, 0);
		gsFontDefaultTooltip		= iFont_create(cgcFontName_defaultTooltip,		9,	FW_BOLD,	0, 0);
		gsFontCask					= iFont_create(cgcFontName_cask,				20, FW_BOLD,	0, 0);

		// Initialize the sound system
		iSound_initialize();
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


		//////////
		// Splash screen
		//////
#if !defined(_NONVJR_COMPILE)
			// Load the splash screen
			if (glShowSplashScreen)
			{
				bmpVjrSplash = iBmp_rawLoad(cgc_splashBmp);
				bmp = iiVjr_buildSplashScreen(bmpVjrSplash);
				CreateThread(0, 0, &iSplash_show, bmp, 0, 0);
			}

			// Play the startup music if any
			sprintf((s8*)logBuffer, "VJr launched %u milliseconds after system boot\0", systemStartedTickCount);
			iVjr_appendSystemLog(logBuffer);
			if (glShowSplashScreen)
				CreateThread(0, 0, &iPlay_ariaSplash, (LPVOID)cgcSoundStartupWav, 0, 0);
#endif

		// Focus window accumulator
#if !defined(_NONVJR_COMPILE)
		iVjr_appendSystemLog((u8*)"Create focus highlight buffer");
#endif
		iBuilder_createAndInitialize(&gFocusHighlights, -1);

		// Create the default reference datetimes
#if !defined(_NONVJR_COMPILE)
		iVjr_appendSystemLog((u8*)"Create default datetime variables");
#endif
		iVjr_init_createDefaultDatetimes();

		// Create our message window
#if !defined(_NONVJR_COMPILE)
		iVjr_appendSystemLog((u8*)"Create message window");
#endif
		iVjr_init_createMessageWindow();

		// Create our global variables
#if !defined(_NONVJR_COMPILE)
		iVjr_appendSystemLog((u8*)"Create global and system variables");
#endif
		iVjr_init_createGlobalSystemVariables();

		// Create our default objects
#if !defined(_NONVJR_COMPILE)
		iVjr_appendSystemLog((u8*)"Create default objects");
#endif
		iVjr_init_createDefaultObjects();

		// Create our main screen window
#if !defined(_NONVJR_COMPILE)
		iVjr_appendSystemLog((u8*)"TEMPORARY:  Manually create _jdebi");
		iVjr_init_jdebi_create();

		// Initially render each one
		iVjr_appendSystemLog((u8*)"Render _jdebi");
		iObj_render(_jdebi, true);

		// Attach them to physical windows
		iVjr_appendSystemLog((u8*)"Allocate OS Window for _jdebi");
		gWinJDebi = iWindow_allocate();
		iObj_createWindowForForm(_jdebi, gWinJDebi, IDI_JDEBI);

		// Initially populate _screen
		// Load in the history if it exists
		if (!iSEM_load_fromDisk(NULL, screenData, cgcScreenDataFilename, false, true))
		{
			// Indicate success
			sprintf((s8*)logBuffer, "Loaded: %s\0", cgcScreenDataFilename);
			iSEM_appendLine(_output_editbox->p.sem, logBuffer, (s32)strlen(logBuffer), false);
			iVjr_appendSystemLog((u8*)"Populate _screen with default data");
			iSEM_appendLine(screenData, (u8*)cgcScreenTitle, -1, false);
			iSEM_appendLine(screenData, NULL, 0, false);
			iSEM_appendLine(screenData, (u8*)"Please report any bugs:  http://www.visual-freepro.org/vjr", -1, false);
			iSEM_appendLine(screenData, (u8*)"Thank you, and may the Lord Jesus Christ bless you richly. :-)", -1, false);
			iSEM_appendLine(screenData, NULL, 0, false);
			iSEM_appendLine(screenData, (u8*)"              _____              In God's sight we've come together.", -1, false);
			iSEM_appendLine(screenData, (u8*)"             |     |             We've come together to help each other.", -1, false);
			iSEM_appendLine(screenData, (u8*)"             |     |             Let's grow this project up ... together!", -1, false);
			iSEM_appendLine(screenData, (u8*)"     ________|     |________     In service and love to The Lord, forever!", -1, false);
			iSEM_appendLine(screenData, (u8*)"    |                       |", -1, false);
			iSEM_appendLine(screenData, (u8*)"    |________       ________|    Sponsored by:", -1, false);
			iSEM_appendLine(screenData, (u8*)"             |     |                 LibSF -- Liberty Software Foundation", -1, false);
			iSEM_appendLine(screenData, (u8*)"             |     |", -1, false);
			iSEM_appendLine(screenData, (u8*)"             |     |    Contributors:", -1, false);
			iSEM_appendLine(screenData, (u8*)"             |     |        Hernan Cano, Stefano D'Amico", -1, false);
			iSEM_appendLine(screenData, (u8*)"             |     |", -1, false);
			iSEM_appendLine(screenData, (u8*)"             |     |    Lead Project Contact:  rick.c.hodgin@gmail.com", -1, false);
			iSEM_appendLine(screenData, (u8*)"             |     |", -1, false);
			iSEM_appendLine(screenData, (u8*)"             |     |    We need more coders. Please consider helping out.", -1, false);
			iSEM_appendLine(screenData, (u8*)"             |_____|    Your contribution would make a difference. :-)", -1, false);
			iSEM_appendLine(screenData, NULL, 0, false);
		}
		// Navigate to the end of the content
		iSEM_navigateToEndLine(screenData, _screen);

		// Initially populate _jdebi
		// Load in the history if it exists
		if (!iSEM_load_fromDisk(NULL, _command_editbox->p.sem, cgcCommandHistoryFilename, true, true))
		{
			// Indicate success
			sprintf((s8*)logBuffer, "Loaded: %s\0", cgcCommandHistoryFilename);
			iSEM_appendLine(_output_editbox->p.sem, logBuffer, (s32)strlen(logBuffer), false);
			iSEM_appendLine(_command_editbox->p.sem, (u8*)"*** Welcome to Visual FreePro, Junior! :-)", -1, false);
			iSEM_appendLine(_command_editbox->p.sem, (u8*)"*** For now, this can be thought of as a command window ... with a twist.", -1, false);
			iSEM_appendLine(_command_editbox->p.sem, (u8*)"*** It works like an editor window.  You can insert new lines, edit old ones, etc.", -1, false);
			iSEM_appendLine(_command_editbox->p.sem, (u8*)"*** To execute a command, press F6. If you're on the last line use F6 or Enter.", -1, false);
			iSEM_appendLine(_command_editbox->p.sem, (u8*)"*** See http://www.visual-freepro.org/wiki/index.php/VXB for supported commands.", -1, false);
			iSEM_appendLine(_command_editbox->p.sem, (u8*)"*** Remember always:  Love makes you smile. It keeps an inner peace like no other. :-)", -1, false);
		}

		// Navigate to the last line
		iSEM_navigateToEndLine(_command_editbox->p.sem, _command_editbox);

		// Make sure there's a blank line at the end
		if (_command_editbox->p.sem->line_cursor->sourceCode_populatedLength != 0)
		{
			iSEM_appendLine(_command_editbox->p.sem, NULL, 0, false);
			iSEM_navigateToEndLine(_command_editbox->p.sem, _command_editbox);
		}

		// Load some source code
		if (iSEM_load_fromDisk(_sourceCode_rider, _sourceCode_editbox->p.sem, cgcStartupPrgFilename, true, true))
		{
			// Indicate success
			sprintf((s8*)logBuffer, "Loaded: %s\0", cgcStartupPrgFilename);
			iSEM_appendLine(_output_editbox->p.sem, logBuffer, (s32)strlen(logBuffer), false);
		}

		// Redraw
		iVjr_appendSystemLog((u8*)"Final render _jdebi");
		iWindow_render(gWinJDebi, true);

		// Remove the splash screen 1/2 second later
		CreateThread(0, 0, &iSplash_delete, (LPVOID)500, 0, 0);

#if defined(_GRACE_COMPILE)
		// Create a thread to display the content in 3D
		memset(&params, 0, sizeof(params));
		params._func_mouse			= (uptr)&iGrace_mouse;
		params._func_motion			= (uptr)&iGrace_motion;
		params._func_passiveMotion	= (uptr)&iGrace_passiveMotion;
		params._func_key			= (uptr)&iGrace_key;
		params._func_special		= (uptr)&iGrace_special;
		params._func_reshape		= (uptr)&iGrace_reshape;
		params._func_display		= (uptr)&iGrace_display;
		params._func_idle			= (uptr)&iGrace_idle;
		CreateThread(0, 0, &iGrace, (LPVOID)&params, 0, 0);
#endif
#endif
	}




//////////
//
// Loads an array strip of icons into an SBitmap array for access through constants.
//
//////
	void iVjr_init_loadBitmapArray(void)
	{
		s32 lnIndex, lnY, lnX, lnXStart, lnStrideY, lnStrideX, lnBmpWidth, lnBmpHeight, lnMaxCount;


		//////////
		// Load the raw array content in strip form
		//////
			bmpArrayTiled		= iBmp_rawLoad(cgc_arrayBmp);
			bxmlArrayBmp		= xml_loadAs_cxml(cgc_bxmlArrayBmp, (u32)strlen(cgc_bxmlArrayBmp));
			// Note:  This XML structure comes from an embedded source (see cgc_bxmlArrayBmp[]), so its syntax will match what's indicated
			bxmlArrayBmpIcons	= bxmlArrayBmp->child(cgcTag_jdebi)->child(cgcTag_icons);


		//////////
		// Allocate memory for all of the children
		//////
			lnMaxCount	= bxmlArrayBmpIcons->childCount();
			bmpArray	= (SBitmap**)malloc(lnMaxCount * sizeof(SBitmap*));
			if (!bmpArray)
				debug_break;	// Should never happen

			// Initialize
			memset(bmpArray, 0, (lnMaxCount * sizeof(SBitmap*)));


		//////////
		// Iterate throughout extracting the icons into the actual bmps into the array
		// Each element of the array is 38x38, but the bitmap content is centered within, 36x36
		//////
			lnY			= bxmlArrayBmpIcons->attribute("uly")->data()->as_s32();
			lnXStart	= bxmlArrayBmpIcons->attribute("ulx")->data()->as_s32();
			lnStrideY	= bxmlArrayBmpIcons->attribute("stridey")->data()->as_s32();
			lnStrideX	= bxmlArrayBmpIcons->attribute("stridex")->data()->as_s32();
			lnBmpWidth	= bxmlArrayBmpIcons->attribute("width")->data()->as_s32();
			lnBmpHeight	= bxmlArrayBmpIcons->attribute("height")->data()->as_s32();

			// Iterate vertically
			for (lnIndex = 0; lnY < bmpArrayTiled->bi.biHeight; lnY += lnStrideY)
			{
				// Iterate horizontally
				for (lnX = lnXStart; lnX < bmpArrayTiled->bi.biWidth; lnIndex++, lnX += lnStrideX)
				{
					// Extract this element of the tiled strip into the sequential array
					bmpArray[lnIndex] = iBmp_createAndExtractRect(bmpArrayTiled, lnX, lnY, lnX + lnBmpWidth, lnY + lnBmpHeight);
				}
			}
	}




//////////
//
// Creates the message window used for communicating actions
//
//////
	void iVjr_init_createMessageWindow(void)
	{
		ATOM			atom;
		WNDCLASSEXA		classa;


		//////////
		// Register the classes if need be
		//////
			while (1)
			{
				if (!GetClassInfoExA(ghInstance, (cs8*)cgcMessageWindowClass, &classa))
				{
					// Initialize
					memset(&classa, 0, sizeof(classa));

					// Populate
					classa.cbSize				= sizeof(WNDCLASSEXA);
					classa.hInstance			= ghInstance;
					classa.lpszClassName		= (cs8*)cgcMessageWindowClass;
					classa.lpfnWndProc			= &iWindow_wndProcMessage;

					// Register
					atom = RegisterClassExA(&classa);
					if (!atom)
						break;
				}



			//////////
			// Create the message window
			//////
				ghwndMsg = CreateWindowA((cs8*)cgcMessageWindowClass, (cs8*)cgcMessageWindowClass, 0, 0, 0, 0, 0, HWND_MESSAGE, null0, ghInstance, 0);
				if (ghwndMsg)
				{
					// Create a timer for the message window firing 20x per second
					SetTimer(ghwndMsg, 0, 50, null0);

					// Read events
					CreateThread(NULL, 0, &iReadEvents_messageWindow, 0, 0, 0);
					return;
				}
				break;
			}
			// We should never get here
			MessageBoxA(null0, "Error creating Visual FreePro Jr's message window.", "VJr - Fatal Error", MB_OK);
	}




//////////
//
// In order for a window pointer to be valid, it must be in the range gWindows->data to
// gWindows->data + gWindows->populatedLength.
//
//////
	bool iVjr_isValid_window(uptr tnWindowPtr)
	{
// TODO:  We may need to add a module test here to make sure the ((tnWindowPtr - gsWindows) % sizeof(SWindow)) == 0
		return(tnWindowPtr >= gWindows->_data && tnWindowPtr < (gWindows->_data + gWindows->populatedLength));
	}




//////////
//
// Thread to handle message window events
//
//////
	DWORD WINAPI iReadEvents_messageWindow(LPVOID lpParameter)
	{
		MSG msg;


		// Read until the message window goes bye bye
		while (GetMessage(&msg, ghwndMsg, 0, 0) > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// When we get here, we're shutting down
		return 0;
	}




//////////
//
// Processes internal messages to process things internally.
//
//////
	LRESULT CALLBACK iWindow_wndProcMessage(HWND hwnd, UINT msg, WPARAM w, LPARAM l)
	{
		u32			lnI;
		MSG			msgPeek;
		SWindow*	win;


		// Call Windows' default procedure handler
		switch (msg)
		{
			case WM_TIMER:
				// See if any windows need to receive this message
				for (lnI = 0; lnI < gWindows->populatedLength; lnI += sizeof(SWindow))
				{
					// Grab this one
					win = (SWindow*)(gWindows->data_u8 + lnI);

					// If it's in use, and it's moving or resizing, send it this message
					if (win->isValid && (win->isMoving || win->isResizing))
					{
						// Send the message if there isn't already one of these messages in the queue
						if (!PeekMessage(&msgPeek, win->hwnd, WM_TIMER, WM_TIMER, PM_NOREMOVE))
							PostMessage(win->hwnd, WM_TIMER, 0, 0);		// Not in queue, send it
					}
				}
				// Indicate we processed it
				return 0;
				break;
		}
		return(DefWindowProc(hwnd, msg, w, l));
	}




//////////
//
// 
//
//////
	void iVjr_init_createConstants(void)
	{
		s32 lnValue;
		f32 lfValue;


		// System constants used internally
		cvarSpace1				= iVariable_createAndPopulate_byText(_VAR_TYPE_CHARACTER, cgc_spaceText, 1,	false);
		cvarEmptyString			= iVariable_createAndPopulate_byText(_VAR_TYPE_CHARACTER, (cu8*)NULL, 0,		false);
		cvarSpace2000			= iVariable_create(_VAR_TYPE_CHARACTER, NULL, true);
		cvarTrue				= iVariable_createAndPopulate_byText(_VAR_TYPE_LOGICAL, iVariable_populate_byBool(true),	0,	false);
		cvarFalse				= iVariable_createAndPopulate_byText(_VAR_TYPE_LOGICAL, iVariable_populate_byBool(false),	0,	false);
		cvarZero				= iVariable_create(_VAR_TYPE_S64, NULL, true);

		lnValue	= 6;
		cvarSix					= iVariable_createAndPopulate_byText(_VAR_TYPE_S32, (cu8*)&lnValue, 4, false);
		lnValue	= 8;
		cvarEight				= iVariable_createAndPopulate_byText(_VAR_TYPE_S32, (cu8*)&lnValue, 4, false);
		lnValue	= 16;
		cvarSixteen				= iVariable_createAndPopulate_byText(_VAR_TYPE_S32, (cu8*)&lnValue, 4, false);
		lnValue	= 32;
		cvarThirtyTwo			= iVariable_createAndPopulate_byText(_VAR_TYPE_S32, (cu8*)&lnValue, 4, false);
		lnValue	= 64;
		cvarSixtyFour			= iVariable_createAndPopulate_byText(_VAR_TYPE_S32, (cu8*)&lnValue, 4, false);
		lnValue	= 255;
		cvarTwoFiftyFive		= iVariable_createAndPopulate_byText(_VAR_TYPE_S32, (cu8*)&lnValue, 4, false);

		lfValue	= 0.5f;
		cvarFiftyPercent		= iVariable_createAndPopulate_byText(_VAR_TYPE_F32, (cu8*)&lfValue, 4, false);
		lfValue	= 0.5f;
		cvarOneHundredPercent	= iVariable_createAndPopulate_byText(_VAR_TYPE_F32, (cu8*)&lfValue, 4, false);

		// 2000 blank spaces
		iDatum_allocateSpace(&cvarSpace2000->value, 2000);
		memset(cvarSpace2000->value.data, 32, 2000);

		// Datetime constants for parsing
		cvarSetDateAmerican	= iVariable_createAndPopulate_byText(_VAR_TYPE_CHARACTER, "11/22/3333 12:34:56.000 AP", -1, true);
		cvarSetDateAnsi		= iVariable_createAndPopulate_byText(_VAR_TYPE_CHARACTER, "3333.22.11 12:34:56.000 AP", -1, true);
		cvarSetDateBritish	= iVariable_createAndPopulate_byText(_VAR_TYPE_CHARACTER, "22/11/3333 12:34:56.000 AP", -1, true);
		cvarSetDateFrench	= cvarSetDateBritish;
		cvarSetDateGerman	= iVariable_createAndPopulate_byText(_VAR_TYPE_CHARACTER, "22.11.3333 12:34:56.000 AP", -1, true);
		cvarSetDateItalian	= iVariable_createAndPopulate_byText(_VAR_TYPE_CHARACTER, "22-11-3333 12:34:56.000 AP", -1, true);
		cvarSetDateJapan		= iVariable_createAndPopulate_byText(_VAR_TYPE_CHARACTER, "3333/11/22 12:34:56.000 AP", -1, true);
		cvarSetDateTaiwan	= cvarSetDateJapan;
		cvarSetDateLong		= iVariable_createAndPopulate_byText(_VAR_TYPE_CHARACTER, "Dow, Mon 22, 3333 12:34:56.000 AP", -1, true);
		cvarSetDateShort		= cvarSetDateAmerican;
		cvarSetDateUsa		= iVariable_createAndPopulate_byText(_VAR_TYPE_CHARACTER, "11-22-33333 12:34:56.000 AP", -1, true);
		cvarSetDateDmy		= cvarSetDateBritish;
		cvarSetDateMdy		= cvarSetDateAmerican;
		cvarSetDateYmd		= cvarSetDateJapan;

		// Other datetime constants for fixed date types
		varSetDateYyyyMmDdTHhMmSsMss	= iVariable_createAndPopulate_byText(_VAR_TYPE_CHARACTER, "3333-11-22 12:34:56.000 AP", -1, true);
		varSetDateYyyyMmDdTHhMmSs		= iVariable_createAndPopulate_byText(_VAR_TYPE_CHARACTER, "3333-11-22 12:34:56 AP", -1, true);
	}




//////////
//
// Called to create the global system variables
//
//////
	void iVjr_init_createGlobalSystemVariables(void)
	{
		s8				lnVal_s8;
		s32				lnVal_s32;
		f32				lfVal_f32;
		SReturnsParams	lsrpar;


		//////////
		// _startupTime
		//////
			memset(&lsrpar, 0, sizeof(lsrpar));
			function_datetime(&lsrpar);
			varStartupTime = lsrpar.rp[0];
			iDatum_duplicate(&varStartupTime->name, cgcName_startupTime, -1);
			iLl_appendExistingNodeAtBeginning((SLL**)&varGlobals, (SLL*)varStartupTime);


		//////////
		// The rest...
		//////
			iiVjr_init_createGlobalSystemVariable(&varAlignment,		_VAR_TYPE_CHARACTER,	cgcName_alignment,		(cs8*)&cgc_left[0], sizeof(cgc_left) - 1);
			iiVjr_init_createGlobalSystemVariable(&varAsciiCols,		_VAR_TYPE_S32,			cgcName_asciicols);
			iiVjr_init_createGlobalSystemVariable(&varAsciiRows,		_VAR_TYPE_S32,			cgcName_asciirows);
			iiVjr_init_createGlobalSystemVariable(&varAssist,			_VAR_TYPE_CHARACTER,	cgcName_assist);
			lnVal_s8 = _LOGICAL_TRUE;
			iiVjr_init_createGlobalSystemVariable(&varBox,				_VAR_TYPE_LOGICAL,		cgcName_box,			(cs8*)&lnVal_s8,	1);
			iiVjr_init_createGlobalSystemVariable(&varBeautify,			_VAR_TYPE_CHARACTER,	cgcName_beautify);
			iiVjr_init_createGlobalSystemVariable(&varBrowser,			_VAR_TYPE_CHARACTER,	cgcName_browser);
			iiVjr_init_createGlobalSystemVariable(&varBuilder,			_VAR_TYPE_CHARACTER,	cgcName_builder);
			iiVjr_init_createGlobalSystemVariable(&varCalcMem,			_VAR_TYPE_F64,			cgcName_calcmem);
			iiVjr_init_createGlobalSystemVariable(&varCalcValue,		_VAR_TYPE_F64,			cgcName_calcvalue);
			iiVjr_init_createGlobalSystemVariable(&varCliptext,			_VAR_TYPE_CHARACTER,	cgcName_cliptext);
			iiVjr_init_createGlobalSystemVariable(&varCodesense,		_VAR_TYPE_CHARACTER,	cgcName_codesense);
			iiVjr_init_createGlobalSystemVariable(&varConverter,		_VAR_TYPE_CHARACTER,	cgcName_converter);
			iiVjr_init_createGlobalSystemVariable(&varCoverage,			_VAR_TYPE_CHARACTER,	cgcName_coverage);
			lnVal_s32 = -1;
			iiVjr_init_createGlobalSystemVariable(&varCurobj,			_VAR_TYPE_S32,			cgcName_curobj,			(cs8*)&lnVal_s32,	4);
			lnVal_s32 = GetDoubleClickTime();
			iiVjr_init_createGlobalSystemVariable(&varDblclick,			_VAR_TYPE_S32,			cgcName_dblclick,		(cs8*)&lnVal_s32,	4);
			iiVjr_init_createGlobalSystemVariable(&varDiaryDate,		_VAR_TYPE_DATE,			cgcName_diarydate);
			iiVjr_init_createGlobalSystemVariable(&varDos,				_VAR_TYPE_LOGICAL,		cgcName_dos);
			iiVjr_init_createGlobalSystemVariable(&varFoxcode,			_VAR_TYPE_CHARACTER,	cgcName_foxcode);
			iiVjr_init_createGlobalSystemVariable(&varFoxdoc,			_VAR_TYPE_CHARACTER,	cgcName_foxdoc);
			iiVjr_init_createGlobalSystemVariable(&varFoxgraph,			_VAR_TYPE_CHARACTER,	cgcName_foxgraph,		(cs8*)&cgcFoxgraphFilename,		sizeof(cgcFoxgraphFilename) - 1);
			iiVjr_init_createGlobalSystemVariable(&varFoxref,			_VAR_TYPE_CHARACTER,	cgcName_foxref,			(cs8*)&cgcFoxrefFilename,		sizeof(cgcFoxrefFilename) - 1);
			iiVjr_init_createGlobalSystemVariable(&varFoxtask,			_VAR_TYPE_CHARACTER,	cgcName_foxtask,		(cs8*)&cgcFoxrefFilename,		sizeof(cgcFoxrefFilename) - 1);
			iiVjr_init_createGlobalSystemVariable(&varGallery,			_VAR_TYPE_CHARACTER,	cgcName_gallery,		(cs8*)&cgcFoxgalleryFilename,	sizeof(cgcFoxgalleryFilename) - 1);
			iiVjr_init_createGlobalSystemVariable(&varGengraph,			_VAR_TYPE_CHARACTER,	cgcName_gengraph,		(cs8*)&cgcGengraphFilename,		sizeof(cgcGengraphFilename) - 1);
			iiVjr_init_createGlobalSystemVariable(&varGenhtml,			_VAR_TYPE_CHARACTER,	cgcName_genhtml,		(cs8*)&cgcGenhtmlFilename,		sizeof(cgcGenhtmlFilename) - 1);
			iiVjr_init_createGlobalSystemVariable(&varGenmenu,			_VAR_TYPE_CHARACTER,	cgcName_genmenu,		(cs8*)&cgcGenmenuFilename,		sizeof(cgcGenmenuFilename) - 1);
			iiVjr_init_createGlobalSystemVariable(&varGenpd,			_VAR_TYPE_CHARACTER,	cgcName_genpd);
			iiVjr_init_createGlobalSystemVariable(&varFoxref,			_VAR_TYPE_CHARACTER,	cgcName_foxref);
			iiVjr_init_createGlobalSystemVariable(&varFoxtask,			_VAR_TYPE_CHARACTER,	cgcName_foxtask);
			iiVjr_init_createGlobalSystemVariable(&varGallery,			_VAR_TYPE_CHARACTER,	cgcName_gallery);
			iiVjr_init_createGlobalSystemVariable(&varGenhtml,			_VAR_TYPE_CHARACTER,	cgcName_genhtml);
			iiVjr_init_createGlobalSystemVariable(&varGenmenu,			_VAR_TYPE_CHARACTER,	cgcName_genmenu);
			iiVjr_init_createGlobalSystemVariable(&varGetexpr,			_VAR_TYPE_CHARACTER,	cgcName_getexpr);
			iiVjr_init_createGlobalSystemVariable(&varGenscrn,			_VAR_TYPE_CHARACTER,	cgcName_genscrn,		(cs8*)&cgcGenscrnFilename,		sizeof(cgcGenscrnFilename) - 1);
			iiVjr_init_createGlobalSystemVariable(&varGenxtab,			_VAR_TYPE_CHARACTER,	cgcName_genxtab);
			iiVjr_init_createGlobalSystemVariable(&varGetexpr,			_VAR_TYPE_CHARACTER,	cgcName_getexpr);
			lfVal_f32 = 0.5;
			iiVjr_init_createGlobalSystemVariable(&varIncseek,			_VAR_TYPE_S32,			cgcName_incseek,		(cs8*)&lfVal_f32,	4);
			iiVjr_init_createGlobalSystemVariable(&varInclude,			_VAR_TYPE_CHARACTER,	cgcName_include);
			iiVjr_init_createGlobalSystemVariable(&varIndent,			_VAR_TYPE_S32,			cgcName_indent);		// Defaults to 0
			iiVjr_init_createGlobalSystemVariable(&varLmargin,			_VAR_TYPE_S32,			cgcName_lmargin);		// Defaults to 0
			iiVjr_init_createGlobalSystemVariable(&varMac,				_VAR_TYPE_LOGICAL,		cgcName_mac);			// Defaults to .f.
			iiVjr_init_createGlobalSystemVariable(&varMeta1,			_VAR_TYPE_S64,			cgcName_meta1);
			iiVjr_init_createGlobalSystemVariable(&varMeta2,			_VAR_TYPE_S64,			cgcName_meta2);
			iiVjr_init_createGlobalSystemVariable(&varMeta3,			_VAR_TYPE_S64,			cgcName_meta3);
			iiVjr_init_createGlobalSystemVariable(&varMeta4,			_VAR_TYPE_S64,			cgcName_meta4);
			iiVjr_init_createGlobalSystemVariable(&varMeta5,			_VAR_TYPE_CHARACTER,	cgcName_meta5);
			iiVjr_init_createGlobalSystemVariable(&varMeta6,			_VAR_TYPE_CHARACTER,	cgcName_meta6);
			iiVjr_init_createGlobalSystemVariable(&varMeta7,			_VAR_TYPE_LOGICAL,		cgcName_meta7);
			iiVjr_init_createGlobalSystemVariable(&varMeta8,			_VAR_TYPE_LOGICAL,		cgcName_meta8);
			iiVjr_init_createGlobalSystemVariable(&varMeta9,			_VAR_TYPE_LOGICAL,		cgcName_meta9);
			iiVjr_init_createGlobalSystemVariable(&varMenudesigner,		_VAR_TYPE_CHARACTER,	cgcName_menudesigner);
			iiVjr_init_createGlobalSystemVariable(&varMline,			_VAR_TYPE_S32,			cgcName_mline);
			iiVjr_init_createGlobalSystemVariable(&varObjectBrowser,	_VAR_TYPE_CHARACTER,	cgcName_objectbrowser);
			iiVjr_init_createGlobalSystemVariable(&varPadvance,			_VAR_TYPE_CHARACTER,	cgcName_padvance,		(cs8*)&cgcFormfeed[0], sizeof(cgcFormfeed) - 1);
			iiVjr_init_createGlobalSystemVariable(&varPageno,			_VAR_TYPE_S32,			cgcName_pageno);
			iiVjr_init_createGlobalSystemVariable(&varPagetotal,		_VAR_TYPE_S32,			cgcName_pagetotal);
			iiVjr_init_createGlobalSystemVariable(&varPretext,			_VAR_TYPE_CHARACTER,	cgcName_pretext);
			lnVal_s32 = 1;
			iiVjr_init_createGlobalSystemVariable(&varPbpage,			_VAR_TYPE_S32,			cgcName_pbpage,			(cs8*)&lnVal_s32,	4);
			iiVjr_init_createGlobalSystemVariable(&varPcolno,			_VAR_TYPE_S32,			cgcName_pcolno);
			iiVjr_init_createGlobalSystemVariable(&varPcopies,			_VAR_TYPE_S32,			cgcName_pcopies,		(cs8*)&lnVal_s32,	4);
			iiVjr_init_createGlobalSystemVariable(&varPdriver,			_VAR_TYPE_CHARACTER,	cgcName_pdriver);
			iiVjr_init_createGlobalSystemVariable(&varPdsetup,			_VAR_TYPE_CHARACTER,	cgcName_pdsetup);
			iiVjr_init_createGlobalSystemVariable(&varPecode,			_VAR_TYPE_CHARACTER,	cgcName_pecode);
			iiVjr_init_createGlobalSystemVariable(&varPeject,			_VAR_TYPE_CHARACTER,	cgcName_peject,			(cs8*)&cgcNone[0], sizeof(cgcNone) - 1);
			lnVal_s32 = 32767;
			iiVjr_init_createGlobalSystemVariable(&varPepage,			_VAR_TYPE_S32,			cgcName_pepage,			(cs8*)&lnVal_s32,	4);
			lnVal_s32 = 66;
			iiVjr_init_createGlobalSystemVariable(&varPlength,			_VAR_TYPE_S32,			cgcName_plength,		(cs8*)&lnVal_s32,	4);
			iiVjr_init_createGlobalSystemVariable(&varPlineno,			_VAR_TYPE_S32,			cgcName_plineno);
			iiVjr_init_createGlobalSystemVariable(&varPloffset,			_VAR_TYPE_S32,			cgcName_ploffset);
			iiVjr_init_createGlobalSystemVariable(&varPpitch,			_VAR_TYPE_CHARACTER,	cgcName_ppitch,			(cs8*)&cgcDefault[0], sizeof(cgcDefault) - 1);
			iiVjr_init_createGlobalSystemVariable(&varPquality,			_VAR_TYPE_LOGICAL,		cgcName_pquality);
			iiVjr_init_createGlobalSystemVariable(&varPretext,			_VAR_TYPE_CHARACTER,	cgcName_pretext);
			iiVjr_init_createGlobalSystemVariable(&varPscode,			_VAR_TYPE_CHARACTER,	cgcName_pscode);
			iiVjr_init_createGlobalSystemVariable(&varPspacing,			_VAR_TYPE_S32,			cgcName_pspacing,		(cs8*)&lnVal_s32,	4);
			iiVjr_init_createGlobalSystemVariable(&varPwait,			_VAR_TYPE_LOGICAL,		cgcName_pwait);
			iiVjr_init_createGlobalSystemVariable(&varReportBuilder,	_VAR_TYPE_CHARACTER,	cgcName_reportbuilder,	(cs8*)&cgcReportBuilderFilename[0],	sizeof(cgcReportBuilderFilename) - 1);
			iiVjr_init_createGlobalSystemVariable(&varReportOutput,		_VAR_TYPE_CHARACTER,	cgcName_reportoutput,	(cs8*)&cgcReportOutputFilename[0],	sizeof(cgcReportOutputFilename) - 1);
			iiVjr_init_createGlobalSystemVariable(&varReportpreview,	_VAR_TYPE_CHARACTER,	cgcName_reportpreview,	(cs8*)&cgcReportPreviewFilename[0],	sizeof(cgcReportPreviewFilename) - 1);
			lnVal_s32 = 80;
			iiVjr_init_createGlobalSystemVariable(&varRmargin,			_VAR_TYPE_S32,			cgcName_rmargin,		(cs8*)&lnVal_s32,	4);
			iiVjr_init_createGlobalSystemVariable(&varRunactivedoc,		_VAR_TYPE_CHARACTER,	cgcName_runactivedoc,	(cs8*)&cgcRunActiveDocFilename[0],	sizeof(cgcRunActiveDocFilename) - 1);

			iiVjr_init_createGlobalSystemVariable(&varSamples,			_VAR_TYPE_CHARACTER,	cgcName_samples,		(cs8*)&cgcSamples[0],				sizeof(cgcSamples) - 1);
			iiVjr_init_createGlobalSystemVariable(&varScctext,			_VAR_TYPE_CHARACTER,	cgcName_scctext,		(cs8*)&cgcScctextFilename[0],		sizeof(cgcScctextFilename) - 1);
			// varScreen is initialized as _screen system-wide
			iiVjr_init_createGlobalSystemVariable(&varShell,			_VAR_TYPE_CHARACTER,	cgcName_shell);
			iiVjr_init_createGlobalSystemVariable(&varSpellchk,			_VAR_TYPE_CHARACTER,	cgcName_spellchk,		(cs8*)&cgcSpellchkFilename[0],		sizeof(cgcSpellchkFilename) - 1);
			iiVjr_init_createGlobalSystemVariable(&varStartup,			_VAR_TYPE_CHARACTER,	cgcName_startup,		(cs8*)&cgcStartupPrgFilename[0],	sizeof(cgcStartupPrgFilename) - 1);
			// varStartupTime is set above
			iiVjr_init_createGlobalSystemVariable(&varTabs,				_VAR_TYPE_CHARACTER,	cgcName_tabs);
			iiVjr_init_createGlobalSystemVariable(&varTasklist,			_VAR_TYPE_CHARACTER,	cgcName_tasklist,		(cs8*)&cgcTasklistFilename[0],		sizeof(cgcTasklistFilename) - 1);
			iiVjr_init_createGlobalSystemVariable(&varTaskpane,			_VAR_TYPE_CHARACTER,	cgcName_taskpane,		(cs8*)&cgcTaskpaneFilename[0],		sizeof(cgcTaskpaneFilename) - 1);
			iiVjr_init_createGlobalSystemVariable(&varTally,			_VAR_TYPE_S64,			cgcName_tally);
			lnVal_s32 = -1;
			iiVjr_init_createGlobalSystemVariable(&varText,				_VAR_TYPE_CHARACTER,	cgcName_text,			(cs8*)&lnVal_s32,	4);
			lnVal_s32 = 1;
			iiVjr_init_createGlobalSystemVariable(&varThrottle,			_VAR_TYPE_S32,			cgcName_throttle,		(cs8*)&lnVal_s32,	4);
			iiVjr_init_createGlobalSystemVariable(&varToolbox,			_VAR_TYPE_CHARACTER,	cgcName_toolbox,		(cs8*)&cgcToolboxFilename[0],		sizeof(cgcToolboxFilename) - 1);
			lnVal_s32 = -1;
			iiVjr_init_createGlobalSystemVariable(&varTooltiptimeout,	_VAR_TYPE_S32,			cgcName_tooltiptimeout, (cs8*)&lnVal_s32,	4);
			iiVjr_init_createGlobalSystemVariable(&varTransport,		_VAR_TYPE_CHARACTER,	cgcName_transport);
			iiVjr_init_createGlobalSystemVariable(&varTriggerlevel,		_VAR_TYPE_S32,			cgcName_triggerlevel);
			iiVjr_init_createGlobalSystemVariable(&varUnix,				_VAR_TYPE_LOGICAL,		cgcName_unix);
			// varVfp is initialized as _vjr system-wide
			lnVal_s8 = _LOGICAL_TRUE;
			iiVjr_init_createGlobalSystemVariable(&varWindows,			_VAR_TYPE_LOGICAL,		cgcName_windows,		(cs8*)&lnVal_s8,	1);
			iiVjr_init_createGlobalSystemVariable(&varWizard,			_VAR_TYPE_CHARACTER,	cgcName_wizard,			(cs8*)&cgcWizardFilename[0],		sizeof(cgcWizardFilename) - 1);
			iiVjr_init_createGlobalSystemVariable(&varWrap,				_VAR_TYPE_LOGICAL,		cgcName_wrap,			".F." );

	}

	void iiVjr_init_createGlobalSystemVariable(SVariable** var, s32 tnType, cu8* tcName, cs8* tcInitValue, u32 tnInitValueLength)
	{
		// Create it
		if (!tcInitValue)		*var = iVariable_create(tnType, NULL, true);
		else					*var = iVariable_createAndPopulate_byText(tnType, tcInitValue, tnInitValueLength, false);

		// Name it
		iDatum_duplicate(&(*var)->name, tcName, -1);

		// Mark it as a system variable
		(*var)->isSysVar = true;

		// Append it to global variables
		iLl_appendExistingNodeAtEnd((SLL**)&varGlobals, (SLL*)*var);
	}




//////////
//
// Loads the default settings for each object, populating them in turn.
//
//////
	void iVjr_init_createDefaultObjects(void)
	{

		//////////
		// Create base objects
		//////
			_settings				= iObj_create(_OBJ_TYPE_SETTINGS, NULL);


		//////////
		// Create each default object
		//////
			gobj_defaultEmpty		= iObj_create(_OBJ_TYPE_EMPTY,		NULL);
			gobj_defaultLabel		= iObj_create(_OBJ_TYPE_LABEL,		NULL);
			gobj_defaultTextbox		= iObj_create(_OBJ_TYPE_TEXTBOX,	NULL);
			gobj_defaultButton		= iObj_create(_OBJ_TYPE_BUTTON,		NULL);
			gobj_defaultImage		= iObj_create(_OBJ_TYPE_IMAGE,		NULL);
			gobj_defaultCheckbox	= iObj_create(_OBJ_TYPE_CHECKBOX,	NULL);
			gobj_defaultCmdGroup	= iObj_create(_OBJ_TYPE_CMDGROUP,	NULL);
			gobj_defaultOptGroup	= iObj_create(_OBJ_TYPE_OPTGROUP,	NULL);
			gobj_defaultListbox		= iObj_create(_OBJ_TYPE_LISTBOX,	NULL);
			gobj_defaultCombobox	= iObj_create(_OBJ_TYPE_COMBOBOX,	NULL);
			gobj_defaultFormset		= iObj_create(_OBJ_TYPE_FORMSET,	NULL);
			gobj_defaultToolbar		= iObj_create(_OBJ_TYPE_TOOLBAR,	NULL);
			gobj_defaultSeparator	= iObj_create(_OBJ_TYPE_SEPARATOR,	NULL);
			gobj_defaultLine		= iObj_create(_OBJ_TYPE_LINE,		NULL);
			gobj_defaultShape		= iObj_create(_OBJ_TYPE_SHAPE,		NULL);
			gobj_defaultContainer	= iObj_create(_OBJ_TYPE_CONTAINER,	NULL);
			gobj_defaultControl		= iObj_create(_OBJ_TYPE_CONTROL,	NULL);
			gobj_defaultGrid		= iObj_create(_OBJ_TYPE_GRID,		NULL);
			gobj_defaultColumn		= iObj_create(_OBJ_TYPE_COLUMN,		NULL);
			gobj_defaultHeader		= iObj_create(_OBJ_TYPE_HEADER,		NULL);
			gobj_defaultOleBound	= iObj_create(_OBJ_TYPE_OLEBOUND,	NULL);
			gobj_defaultOleContain	= iObj_create(_OBJ_TYPE_OLECONTAIN,	NULL);
			gobj_defaultSpinner		= iObj_create(_OBJ_TYPE_SPINNER,	NULL);
			gobj_defaultTimer		= iObj_create(_OBJ_TYPE_TIMER,		NULL);
			gobj_defaultHyperlink	= iObj_create(_OBJ_TYPE_HYPERLINK,	NULL);
			gobj_defaultCollection	= iObj_create(_OBJ_TYPE_COLLECTION,	NULL);
			gobj_defaultPage		= iObj_create(_OBJ_TYPE_PAGE,		NULL);
			gobj_defaultPageFrame	= iObj_create(_OBJ_TYPE_PAGEFRAME,	NULL);
			gobj_defaultSession		= iObj_create(_OBJ_TYPE_SESSION,	NULL);
			gobj_defaultCustom		= iObj_create(_OBJ_TYPE_CUSTOM,		NULL);
			gobj_defaultException	= iObj_create(_OBJ_TYPE_EXCEPTION,	NULL);
			gobj_defaultSettings	= iObj_create(_OBJ_TYPE_SETTINGS,	NULL);

			// Option and radio both have label controls within
			gobj_defaultOption		= iObj_create(_OBJ_TYPE_OPTION,		NULL);
			gobj_defaultRadio		= iObj_create(_OBJ_TYPE_RADIO,		NULL);
			// Forms and subforms are created last because they have internal child objects references to classes which must be created before
			gobj_defaultForm		= iObj_create(_OBJ_TYPE_FORM,		NULL);
			gobj_defaultSubform		= iObj_create(_OBJ_TYPE_SUBFORM,	NULL);
	}




//////////
//
// Called to load the cask icons from the icon tile image
//
//////
	void iVjr_init_loadCaskIcons(void)
	{
		RECT lrc;


// TODO:  There's a BXML file with this information (cask_icons.bxml).
//        BXML support should be added to VJr and then that information used to do this, rather than by hard-coding.
#ifndef _NONVJR_COMPILE
		// Casks are only used in VJr
		bmpCaskIconsTiled			= iBmp_rawLoad(cgc_caskIconsBmp);
#endif
		bmpCaskRoundLeft			= iBmp_createAndExtractRect(bmpCaskIconsTiled, 12, 2, 31, 38);
		bmpCaskRoundRight			= iBmp_createAndExtractRect(bmpCaskIconsTiled, 33, 2, 52, 38);
		bmpCaskSquareLeft			= iBmp_createAndExtractRect(bmpCaskIconsTiled, 12, 44, 31, 80);
		bmpCaskSquareRight			= iBmp_createAndExtractRect(bmpCaskIconsTiled, 33, 44, 52, 80);
		bmpCaskTriangleLeft			= iBmp_createAndExtractRect(bmpCaskIconsTiled, 12, 86, 30, 122);
		bmpCaskTriangleRight		= iBmp_createAndExtractRect(bmpCaskIconsTiled, 34, 86, 52, 122);
		bmpCaskTildeLeft			= iBmp_createAndExtractRect(bmpCaskIconsTiled, 115, 86, 132, 122);
		bmpCaskTildeRight			= iBmp_createAndExtractRect(bmpCaskIconsTiled, 134, 86, 151, 122);
		bmpCaskCodeLeft				= iBmp_createAndExtractRect(bmpCaskIconsTiled, 156, 86, 174, 122);
		bmpCaskCodeRight			= iBmp_createAndExtractRect(bmpCaskIconsTiled, 177, 86, 195, 122);

		// /|auto|\ casks are inverted code casks
		bmpCaskAutoLeft				= iBmp_copy(bmpCaskCodeLeft);
		bmpCaskAutoRight			= iBmp_copy(bmpCaskCodeRight);
		CopyRect(&lrc, &bmpCaskAutoLeft->rc);
		iBmp_bitBlt_rotated(bmpCaskAutoLeft, &lrc, bmpCaskCodeRight, 180);
		CopyRect(&lrc, &bmpCaskAutoRight->rc);
		iBmp_bitBlt_rotated(bmpCaskAutoRight, &lrc, bmpCaskCodeLeft, 180);

		bmpCaskPips1				= iBmp_createAndExtractRect(bmpCaskIconsTiled, 54, 7, 65, 33);
		bmpCaskPips2				= iBmp_createAndExtractRect(bmpCaskIconsTiled, 67, 7, 78, 33);
		bmpCaskPips3				= iBmp_createAndExtractRect(bmpCaskIconsTiled, 80, 7, 91, 33);
		bmpCaskSideExtender			= iBmp_createAndExtractRect(bmpCaskIconsTiled, 72, 44, 76, 79);
		bmpCaskSideExtenderLeft		= iBmp_createAndExtractRect(bmpCaskIconsTiled, 54, 44, 58, 79);
		bmpCaskSideExtenderMiddle	= iBmp_createAndExtractRect(bmpCaskIconsTiled, 60, 44, 64, 79);
		bmpCaskSideExtenderRight	= iBmp_createAndExtractRect(bmpCaskIconsTiled, 66, 44, 70, 79);
		bmpCaskExtenderMiddle		= iBmp_createAndExtractRect(bmpCaskIconsTiled, 70, 86, 74, 122);
		bmpCaskExtenderLeft1		= iBmp_createAndExtractRect(bmpCaskIconsTiled, 64, 86, 68, 122);
		bmpCaskExtenderLeft2		= iBmp_createAndExtractRect(bmpCaskIconsTiled, 76, 86, 87, 122);
		bmpCaskExtenderRight2		= iBmp_createAndExtractRect(bmpCaskIconsTiled, 89, 86, 100, 122);
		bmpCaskExtenderRight1		= iBmp_createAndExtractRect(bmpCaskIconsTiled, 102, 86, 106, 122);

		// Grab the cask color masks
		caskOrange1					= iBmp_extractColorAtPoint(bmpCaskIconsTiled, 160, 18);
		caskOrange2					= iBmp_extractColorAtPoint(bmpCaskIconsTiled, 154, 18);
		caskOrange3					= iBmp_extractColorAtPoint(bmpCaskIconsTiled, 148, 18);
		caskRed1					= iBmp_extractColorAtPoint(bmpCaskIconsTiled, 160, 23);
		caskRed2					= iBmp_extractColorAtPoint(bmpCaskIconsTiled, 154, 23);
		caskRed3					= iBmp_extractColorAtPoint(bmpCaskIconsTiled, 148, 23);
		caskBlue1					= iBmp_extractColorAtPoint(bmpCaskIconsTiled, 160, 28);
		caskBlue2					= iBmp_extractColorAtPoint(bmpCaskIconsTiled, 154, 28);
		caskBlue3					= iBmp_extractColorAtPoint(bmpCaskIconsTiled, 148, 28);
		caskPurple1					= iBmp_extractColorAtPoint(bmpCaskIconsTiled, 160, 33);
		caskPurple2					= iBmp_extractColorAtPoint(bmpCaskIconsTiled, 154, 33);
		caskPurple3					= iBmp_extractColorAtPoint(bmpCaskIconsTiled, 148, 33);
		caskCyan1					= iBmp_extractColorAtPoint(bmpCaskIconsTiled, 160, 38);
		caskCyan2					= iBmp_extractColorAtPoint(bmpCaskIconsTiled, 154, 38);
		caskCyan3					= iBmp_extractColorAtPoint(bmpCaskIconsTiled, 148, 38);
		caskGreen1					= iBmp_extractColorAtPoint(bmpCaskIconsTiled, 160, 43);
		caskGreen2					= iBmp_extractColorAtPoint(bmpCaskIconsTiled, 154, 43);
		caskGreen3					= iBmp_extractColorAtPoint(bmpCaskIconsTiled, 148, 43);
		caskYellow1					= iBmp_extractColorAtPoint(bmpCaskIconsTiled, 160, 48);
		caskYellow2					= iBmp_extractColorAtPoint(bmpCaskIconsTiled, 154, 48);
		caskYellow3					= iBmp_extractColorAtPoint(bmpCaskIconsTiled, 148, 48);
		caskGray1					= iBmp_extractColorAtPoint(bmpCaskIconsTiled, 160, 53);
		caskGray2					= iBmp_extractColorAtPoint(bmpCaskIconsTiled, 154, 53);
		caskGray3					= iBmp_extractColorAtPoint(bmpCaskIconsTiled, 148, 53);
		caskWhite1					= iBmp_extractColorAtPoint(bmpCaskIconsTiled, 160, 58);
		caskWhite2					= iBmp_extractColorAtPoint(bmpCaskIconsTiled, 154, 58);
		caskWhite3					= iBmp_extractColorAtPoint(bmpCaskIconsTiled, 148, 58);
		caskBlack1					= iBmp_extractColorAtPoint(bmpCaskIconsTiled, 160, 63);
		caskBlack2					= iBmp_extractColorAtPoint(bmpCaskIconsTiled, 154, 63);
		caskBlack3					= iBmp_extractColorAtPoint(bmpCaskIconsTiled, 148, 63);
	}
