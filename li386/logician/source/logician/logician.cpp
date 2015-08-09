//////////
//
// /libsf/li386/logician/source/logician/logician.cpp
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
// Copyright (c) 2015 by Rick C. Hodgin
//////
// Last update:
//     Aug.08.2015
//////
// Change log:
//     Aug.08.2015 - Initial creation
//////
//
// This document and all documents contained within are released as Liberty Software
// under a Repeat License, as governed by the Public Benefit License v1.0 or later
// (PBL).
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
// Logician is a logic layout tool designed to use a 3D interface for positioning
// and coding logic circuits.  It intends to be a type of "graphical verilog,"
// with similar definition abilities to verilog, able to export its content as
// verilog source code.
//
//////


//////////
// Uses Visual FreePro, Jr's existing facilities to simplify our processing
//////
	#define _NONVJR_COMPILE		// Turns off some features in VJr that fail on compilation from here
	#define _BMP_LOCALITY 1		// Force definitions to be local
	const char cgc_appName[] = "Logician";
	#include "\libsf\source\vjr\source\vjr.h"
	#undef main


//////////
// Global variables
//////
	SObject*		goLogicianForm				= NULL;


//////////
// Forward declarations
//////
	// None currently defined


//////////
// other.cpp
//////
	//#include "other.cpp"




//////////
//
// The main Logician execution loop
//
//////
#if defined(__linux__)
	int main(int argc, char* argv[])
#else
	int CALLBACK WinMain(	HINSTANCE	hInstance,
							HINSTANCE	hPrevInstance,
							LPSTR		lpCmdLine,
							int			nCmdShow	)
#endif
	{
		SGraceParams params;


		//////////
		// Initialize VJr
		//////
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


			iBuilder_createAndInitialize(&gFocusHighlights, -1);
			iInit_createDefaultDatetimes();
			iInit_createMessageWindow();
			iInit_createGlobalSystemVariables();
			iInit_createDefaultObjects();


		//////////
		// Create the default form
		//////
			goLogicianForm = iObj_create(NULL, _OBJ_TYPE_FORM, NULL);
			iObj_render(NULL, goLogicianForm, true);


		//////////
		// Create a thread to display the content in 3D
		//////
			memset(&params, 0, sizeof(params));
			params._func_mouse			= (uptr)&iGrace_mouse;
			params._func_motion			= (uptr)&iGrace_motion;
			params._func_passiveMotion	= (uptr)&iGrace_passiveMotion;
			params._func_key			= (uptr)&iGrace_key;
			params._func_special		= (uptr)&iGrace_special;
			params._func_reshape		= (uptr)&iGrace_reshape;
			params._func_display		= (uptr)&iGrace_display;
			params._func_idle			= (uptr)&iGrace_idle;
			params.win					= iWindow_allocate();
			iObj_createWindowForForm(NULL, goLogicianForm, params.win, NULL);
			CreateThread(0, 0, &iGrace, (LPVOID)&params, 0, 0);


		//////////
		// Enter a loop until we're done
		//////
			while (!glShuttingDown)
			{
				// Wait 1/3 second
				Sleep(333);
			}


		//////////
		// We're done
		//////
			return 0;

	}
