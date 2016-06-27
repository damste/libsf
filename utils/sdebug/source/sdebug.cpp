//////////
//
// /libsf/utils/sdebug/source/sdebug.cpp
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
//     May.17.2016
//////
// Change log:
//     May.17.2016 - Initial creation
//////
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
//     http://www.visual-freepro.org/vjr/indexmain.html
//     http://www.visual-freepro.org/wiki/index.php/PBL
//
// Thank you.  And may The Lord bless you richly as you lift up your life, your
// talents, your gifts, your praise, unto Him.  In Jesus' name I pray.  Amen.
//
//////
//
// SDebug is short for "Sanitizing Debugger".  It was designed to help find memory bugs.
//
// SDebug allows explicit memory ranges to be checked, along with explicit references
// to pointers being tracked.  Once the range(s) is(are) set, it allows runtime modes:
//
//		1 - Single-step through code looking for any access outside of tracked memory.
//
//		2 - Specify a function to examine, within which it looks at all memory references
//			to see if any reference is outside the tracked range.
//
//		3 - Specify a parameter or local pointer to track, which then only explicitly looks
//			at things which reference that pointer, ignoring all other memory references.
//
// Once set on a pointer or function, SDebug disassembles the function body and determines
// where each memory reference is made, and where each pointer is used.  It then sets
// breakpoints on all of those instructions.  When those breakpoints are hit, it internally
// decodes the instruction on-the-fly to determine if references are being made inside or
// outside of tracked memory ranges.
//
// Memory blocks are tracked in the general form:
//
//		preBufferCount		-- Number of bytes to examine before buffer (typically up to 64)
//		bufferStart			-- Where the buffer starts
//		bufferLength		-- Length of normal data within the buffer
//		postBufferCount		-- Number of bytes to examine after the buffer (typically up to 64)
//
//////


//////////
// Uses Visual FreePro, Jr's existing facilities to simplify our processing
//////
	#define _NONVJR_COMPILE		// Turns off some features in VJr that fail on compilation from here
	#define _BMP_LOCALITY 1		// Force definitions to be local
	#include "\libsf\source\vjr\source\vjr.h"
	#undef main

	#include "sdebug.h"




//////////
//
// The main loop
//
//////
	int CALLBACK WinMain(	HINSTANCE	hInstance,
							HINSTANCE	hPrevInstance,
							LPSTR		lpCmdLine,
							int			nCmdShow	)
{
	SThisCode*		thisCode = NULL;
	MSG				msg;
	HACCEL			hAccelTable;
	SVxbContext		vxbParams;
	SVxbStats		stats;
	bool			error;
	u32				errorNum;



	//////////
	// Initialize
	//////
		ghInstance = hInstance;
		iVjr_init(&hAccelTable);
		iSDeb_init();
		iVjr_appendSystemLog((u8*)"Initialization complete");


	//////////
	// Read events
	//////
		iVjr_appendSystemLog((u8*)"Engage main loop");
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
			iVjr_shutdown();


	//////////
	// Return our exit code
	//////
		return((int)msg.wParam);
}

SWindow*			gsWinSD								= NULL;
SObject*			_sd_screen							= NULL;
SObject*			_sd_command							= NULL;
SObject*			_sd_sourceCode						= NULL;
SObject*			_sd_sourceCode_rider				= NULL;
SObject*			_sd_sourceCode_editbox				= NULL;
SObject*			_sd_locals							= NULL;
SObject*			_sd_watch							= NULL;
SObject*			_sd_cmd								= NULL;
SObject*			_sd_output							= NULL;
SObject*			_sd_locals_editbox					= NULL;
SObject*			_sd_watch_editbox					= NULL;
SObject*			_sd_command_editbox					= NULL;
SObject*			_sd_output_editbox					= NULL;
void iSDeb_init(void)
{
	// Create our main screen window
	iSD_init__create_screen();
	iObj_render(_sd_screen, true);

	// Attach them to physical windows
	gsWinSD = iWindow_allocate();
	iObj_createWindowForForm(_sd_screen, gsWinSD, -1);

	// Tell them who we are
	iSEM_appendLine(_sd_command_editbox->p.sem, (u8*)"Sanitizing Debugger by Liberty Software Foundation", -1, false);
	iSEM_appendLine(_sd_command_editbox->p.sem, (u8*)"To execute a command, press F6.  If you're on the last line use F6 or Enter.", -1, false);
	iSEM_appendLine(_sd_command_editbox->p.sem, (u8*)"See http://www.libsf.org/sdebug/ for supported commands.", -1, false);
	iSEM_appendLine(_sd_command_editbox->p.sem, (u8*)"Remember always:  Love makes you smile.  It keeps an inner peace like no other. :-)", -1, false);
	iSEM_navigateToEndLine(_sd_command_editbox->p.sem, _sd_command_editbox);

	// Load some source code
//	iSEM_load_fromDisk(_sd_sourceCode_rider, _sd_sourceCode_editbox->p.sem, sourceCode->data_s8, true, true);

	// Redraw
	iWindow_render(gsWinSD, true);
}

void iSD_init__create_screen(void)
{

}
