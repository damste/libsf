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
	#include "logician.h"
	#undef main


//////////
// Global variables
//////
	SObject*		goLogicianForm						= NULL;


//////////
// Forward declarations
//////
	void			iLogician_init_createMainForm			(void);
	void			iLogician_init_spawn3dThread			(void);


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
		MSG msg;


		//////////
		// Initialize
		//////
			// Initialize main engine
			iVjr_init(NULL);

			// Initialize Logician
			iLogician_init_createMainForm();
			iLogician_init_spawn3dThread();


		//////////
		// Read events
		//////
			while (!glShuttingDown && GetMessage(&msg, null0, 0, 0))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			// When the WM_QUIT message is received, we exit

			// Do allocated resource shutdown
			if (!glShuttingDown)
				iVjr_shutdown(NULL);


		//////////
		// Return our exit code
		//////
			return((int)msg.wParam);

	}




//////////
//
// Main form
//
//////
	void iLogician_init_createMainForm(void)
	{
		RECT		lrc;
		s32			lnLeft, lnTop, lnWidth, lnHeight;
		SThisCode*	thisCode;


		// Initialize
		thisCode = NULL;

		// Create the main form
		goLogicianForm = iObj_create(thisCode, _OBJ_TYPE_FORM, NULL);

		// Give it a fixed point font
		goLogicianForm->p.font = iFont_create(cgcFontName_defaultFixed, 10, FW_MEDIUM, false, false);

		// Get the desktop size
		GetWindowRect(GetDesktopWindow(), &lrc);
		lnWidth		= (lrc.right - lrc.left);
		lnHeight	= (lrc.bottom - lrc.top);

		// Size and position it
		lnLeft		= (lrc.right  - lrc.left) / 32;
		lnTop		= (lrc.bottom - lrc.top)  / 32;
		lnWidth		-= (2 * lnLeft);
		lnHeight	-= (2 * lnTop);
		iObj_setSize(NULL, goLogicianForm, lnLeft, lnTop, lnWidth, lnHeight);

		// Set the app icon and enable the border
		propSetPictureBmp	(goLogicianForm,	bmpJDebiIcon);
		propSetBorderStyle	(goLogicianForm,	_BORDER_STYLE_FIXED);
		propSetName			(goLogicianForm,	cgcName_jdebi,		sizeof(cgcName_jdebi) - 1);
		propSetIcon			(goLogicianForm,	bmpJDebiIcon);
		propSetCaption		(goLogicianForm,	cgcJDebiTitle);
		propSetVisible		(goLogicianForm,	_LOGICAL_TRUE);

		// Render
		iObj_render(NULL, goLogicianForm, true);
	}




//////////
//
// Create our 3D thread
//
//////
	void iLogician_init_spawn3dThread(void)
	{
		SGraceParams* params;


		// Create a thread to display the content in 3D
		params = (SGraceParams*)malloc(sizeof(SGraceParams));
		if (params)
		{
			// Initialize
			memset(params, 0, sizeof(params));

			// Populate
			params->_func_mouse			= (uptr)&iGrace_mouse;
			params->_func_motion		= (uptr)&iGrace_motion;
			params->_func_passiveMotion	= (uptr)&iGrace_passiveMotion;
			params->_func_key			= (uptr)&iGrace_key;
			params->_func_special		= (uptr)&iGrace_special;
			params->_func_reshape		= (uptr)&iGrace_reshape;
			params->_func_display		= (uptr)&iGrace_display;
			params->_func_idle			= (uptr)&iGrace_idle;

			// Create the associated VJr window
			params->win					= iWindow_allocate();
			iObj_createWindowForForm(NULL, goLogicianForm, params->win, NULL);

			// Launch the 3D render thread
			CreateThread(0, 0, &iGrace, (LPVOID)params, 0, 0);
		}
	}
