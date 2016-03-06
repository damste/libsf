//////////
//
// /libsf/utils/common/cpp/console/console.cpp
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




#include "console.h"


// OS-specific code for these is found in xyz\console_xyz.h (win\console_win.h)
// _UNIT_TEST and _DLL_GENERATION are compiler-defined flags, auto-set in Debug/Release_UT and Debug/Release_DLL
#if defined(_UNIT_TEST)
	// This code is declared if we're compiling for unit tests
	console_main_function
	{
		// The unit tests are defined in xyz\console_xyz.h
		console_unit_tests;
	}

#elif defined(_DLL_GENERATION)
	// This code is for generating an output DLL
	console_dll_function
	{
		// The unit tests are defined in xyz\console_xyz.h
		console_dll_code;
	}
#endif




//////////
//
// Called to initialize the console engine
//
//////
	CONAPI uptr console_initialize(void)
	{
		// No console-specific initialization, only os-specific
		return(console_os_initialize);
	}




//////////
//
// Called to allocate a new console
//
//////
	// Note:  Console is not displayed until console_show(..., true) is first called
	uptr console_allocate(SDatum* title, s32 tnLeft, s32 tnTop, s32 tnCols, s32 tnRows, SConCallback* cb)
	{
		SConsole* console;


		// Make sure our environment is sane
		if (cb && iConsole_validateInitialization())
		{
			// Actually create the console
			console = (SConsole*)iBuilder_allocateBytes(gsConsoleRoot, sizeof(SConsole));
			if (console)
			{
				// Initialize and copy
				memset(console, 0, sizeof(*console));

				// Copy params
				iDatum_duplicate(&console->title, title);
				console->nLeft			= tnLeft;
				console->nTop			= tnTop;
				console->nWidth			= tnCols * 8;
				console->nHeight		= tnRows * 14;
				console->nCharWidth		= 8;
				console->nCharHeight	= 14;
				console->nCharFont		= _CONSOLE_FONT_8x14;		// Default to this font until they specify otherwise

				// Copy over the callback data
				memcpy(&console->cb, cb, sizeof(console->cb));
			}

			// Indicate our handle
			return((uptr)console);
		}

		// If we get here, invalid
		return(_CONSOLE_ERROR__FATAL_ERROR);
	}




//////////
//
// Called to allocate a new console
//
//////
	// Note:  Even if a visible property is specified, console is not displayed until console_show(..., true) is first called
	uptr console_allocate(SDatum* settings, SConCallback* cb)
	{
		SConsole		console_cb;
		SConsole*		console;
		SDatumCallback	dcb;


		// Make sure our environment is sane
		if (settings && cb && iConsole_validateInitialization())
		{
			// Iterate through properties
			memset(&dcb,		0, sizeof(dcb));
			memset(&console_cb,	0, sizeof(console_cb));

			// Some values that need to be set
			console_cb.nLeft		= 0;
			console_cb.nTop			= 0;
			console_cb.nWidth		= 80;
			console_cb.nHeight		= 25;
			console_cb.nCharWidth	= 8;
			console_cb.nCharHeight	= 16;
			iDatum_duplicate(&console_cb.title, "LibSF Console Window");

			// Perform the processing
			dcb.extra1 = &console_cb;
			dcb._propAndValue_func = (uptr)&iiConsole_setOptions_callback;
			iProperty_iterate(&dcb, settings);

			// Actually create the console
			console = (SConsole*)iBuilder_allocateBytes(gsConsoleRoot, sizeof(SConsole));
			if (console)
			{
				// Copy
				memcpy(console, &console_cb, sizeof(*console));		// Copy what we already setup
				memcpy(&console->cb, cb, sizeof(console->cb));		// Copy over the callback data
			}

			// Indicate our handle
			return((uptr)console);
		}

		// If we get here, invalid
		return(_CONSOLE_ERROR__FATAL_ERROR);
	}




//////////
//
// Called to re-register a previously registered callback
//
//////
	uptr console_reregister(uptr tnHandle, SConCallback* cb)
	{
		SConsole* console;


		// Make sure our environment is sane
		if (cb && iConsole_validateInitialization() && (console = iConsole_find_byHandle(tnHandle)))
		{
			// Copy the new information over
			memcpy(&console->cb, cb, sizeof(console->cb));

			// Indicate success
			return(_CONSOLE_ERROR__NO_ERROR);
		}

		// Indicate failure
		return(_CONSOLE_ERROR__HANDLE_NOT_FOUND);
	}




//////////
//
// Called to  show or hide a console
//
//////
	s32 console_show(uptr tnHandle, bool tlVisible)
	{
		s32			lnResult;
		SConsole*	console;


		// Make sure our environment is sane
		if (iConsole_validateInitialization() && (console = iConsole_find_byHandle(tnHandle)))
		{
			// If it's changed, set it
			if (console->lVisible != tlVisible)
			{
				// Try to toggle the visible status
				if ((lnResult = console_os_toggle_visible) != _CONSOLE_ERROR__NO_ERROR)
					console_os_error;

				// Indicate success
				return(lnResult);
			}

			// We're good
			return(_CONSOLE_ERROR__NO_ERROR);

		} else {
			// Failure
			return(_CONSOLE_ERROR__HANDLE_NOT_FOUND);
		}
	}




//////////
//
// Called to release a previously allocated console
//
//////
	s32 console_release(uptr tnHandle)
	{
		s32			lnResult;
		SConsole*	console;


		// Make sure our environment is sane
		if (iConsole_validateInitialization() && (console = iConsole_find_byHandle(tnHandle)))
		{
			// If it's changed, set it
			if ((lnResult = console_os_release) != _CONSOLE_ERROR__NO_ERROR)
				console_os_error;

			// We're good
			return(lnResult);

		} else {
			// Failure
			return(_CONSOLE_ERROR__HANDLE_NOT_FOUND);
		}
	}




//////////
//
// Called to set an option or options for a console
//
//////
	s32 console_setProperties(uptr tnHandle, SDatum* properties)
	{
		SConsole*			console;
		SDatumCallback		cb;


		// Make sure our environment is sane
		if (iConsole_validateInitialization() && (console = iConsole_find_byHandle(tnHandle)))
		{
			// Iterate through all of the properties one-by-one
			memset(&cb, 0, sizeof(cb));
			cb.extra1				= console;
			cb._propAndValue_func	= (uptr)&iiConsole_setOptions_callback;
			return(iProperty_iterate(&cb, properties));
		}

		// If we get here, error
		return(_CONSOLE_ERROR__HANDLE_NOT_FOUND);
	}




//////////
//
// Called to set the font to use from this point forward (until changed in the future)
//
//////
	s32 console_setFont(uptr tnHandle, SDatum* tcFontName, s32 tnPointSize, bool tlBold, bool tlItalic, bool tlUnderline)
	{
		s32			lnI;
		SConsole*	console;
		SConFont*	font;


		// See if we have a console
		if (iConsole_validateInitialization() && (console = iConsole_find_byHandle(tnHandle)))
		{
			// Make sure we have a font builder
			if (!gsConsoleFontRoot)
				iBuilder_createAndInitialize(&gsConsoleFontRoot, 64 * sizeof(SConFont));

			// Search for a matching font
			for (lnI = 0; lnI < (s32)gsConsoleFontRoot->populatedLength; lnI += sizeof(SConFont))
			{
				// Grab the font
				font = (SConFont*)(gsConsoleFontRoot->buffer + lnI);

				// Check each thing
				if (font->nPointSize == tnPointSize && font->lBold == tlBold && font->lItalic == tlItalic && font->lUnderline == tlUnderline)
				{
					// They're the same size, bold, italic, and underline
					if (font->cFontName.length == tcFontName->length && iDatum_compare(tcFontName, &font->cFontName) == 0)
						return(lnI / sizeof(SConFont));		// Same font
				}
			}
			// If we get here, not found

			// Add new
			font = (SConFont*)iBuilder_allocateBytes(gsConsoleFontRoot, sizeof(SConFont));
			if (font)
			{
				// Copy the info
				if (tcFontName)			iDatum_duplicate(&font->cFontName, tcFontName);
				else					font->lFixed = true;

				// Copy font size info
				font->nPointSize	= tnPointSize;
				font->lBold			= tlBold;
				font->lItalic		= tlItalic;
				font->lUnderline	= tlUnderline;

				// If they specify "$fixed" for the font name, then we use 
				if (!tcFontName || iDatum_compare(tcFontName, cgc_internal_fontName, -1) == 0)
				{
					// Extract out X,Y font sizes in pixels (lower two bytes in 32-bit tnPointSize)
					font->nUseX		= max(((u32)tnPointSize & 0xff00) >> 8, 8);
					font->nUseY		= max((u32)tnPointSize & 0xff, 6);
					font->nActualX	= font->nUseX;
					font->nActualY	= font->nUseY;
					// Note:  The OS will choose from its own internal list of fixed point fonts which one to scale into the targeted console's current character size (width,height)
					// Note:  Later on the character size can be changed, at which case the fonts in use will be re-scaled
				}

				// Call OS-specific code
				if (!console_os_font_setup)
				{
					// The OS does not support the font request
					return(_CONSOLE_ERROR__FONT_NOT_SUPPORTED_ERROR);
				}

				// Indicate success
				return((gsConsoleFontRoot->populatedLength - sizeof(SConFont)) / sizeof(SConFont));
			}

			// Indicate failure
			return(_CONSOLE_ERROR__FONT_ALLOCATION_ERROR);
		}

		// Indicate failure
		return(_CONSOLE_ERROR__HANDLE_NOT_FOUND);
	}




//////////
//
// Called to set the font to use from this point forward (until changed in the future)
//
//////
	s32 console_setFont(uptr tnHandle, SDatum* fontData)
	{
		return(-1);
	}




//////////
//
// Called to get the current font
//
//////
	s32 console_getFont(uptr tnHandle, s32 tnX, s32 tnY, SDatum* fontName, s32* tnPointSize, bool* tlBold, bool* tlItalic, bool* tlUnderline)
	{
		return(-1);
	}




//////////
//
// Called to get the current font
//
//////
	s32 console_getFont(uptr tnHandle, s32 tnX, s32 tnY, SDatum* fontData)
	{
		return(-1);
	}




//////////
//
// Called to output text to the console window, only processes CR/LF and TAB characters,
// the rest are pass-thru displayed.
//
//////
	s32 console_print(uptr tnHandle, SDatum* textOut)
	{
		s8			c;
		s32			lnI, lnJ;
		SConsole*	console;


		// See if we have a console
		if (iConsole_validateInitialization() && (console = iConsole_find_byHandle(tnHandle)))
		{
			// Make sure we have a scroll buffer
			if (iConsole_validateScrollBuffer(console))
			{
				// Make sure they're printing something valid
				if (textOut && textOut->_data)
				{
					// Begin processing
					for (lnI = 0; lnI < textOut->length; lnI++)
					{
						// Parse out the character
					    if ((c = textOut->data_cs8[lnI]) == 13)
						{
							// Carriage return
							 console->nX = 0;

						} else if (c == 10) {
							// Line feed
							if (console->nY >= console->nRows)
							{
								// We need to scroll up one
								iiConsole_scroll(console);
								
							} else {
								// Enough room to move down one row
								++console->nY;
							}

							// Move to the start
							console->nX = 0;

						} else if (c == 9) {
							// Tab
							for (lnJ = console->nX + 1; lnJ % 4 != 0; )
								++lnJ;

							// Make sure it's in range
							console->nX = min(console->nX, console->nWidth);

						} else {
							// Store it
							if (c == '\\')
							{
								// If we're at the end, we can't continue
								if (lnI >= textOut->length - 1)
									break;

								// Grab the next character
								c = textOut->data_cs8[++lnI];
							}

							// Store the character
							iiConsole_storeCharacter(console, c);
						}
					}
					// When we get here, the data was pushed
					return(_CONSOLE_ERROR__NO_ERROR);

				} else {
					// Something's awry
					return(_CONSOLE_ERROR__INVALID_PARAMETERS);
				}

			} else {
				// Something's awry
				return(_CONSOLE_ERROR__CANNOT_ALLOCATE_BUFFER);
			}
		}

		// Failure
		return(_CONSOLE_ERROR__HANDLE_NOT_FOUND);
	}




//////////
//
// Called to position
//
//////
	CONAPI s32 console_goto_xy(uptr tnHandle, s32 tnX, s32 tnY)
	{
		SConsole*	console;


		// See if we have a console
		if (iConsole_validateInitialization() && (console = iConsole_find_byHandle(tnHandle)))
		{
			// Un-paint the current position
			console_os_xy_needs_repainted;

			// Store the position
			console->nX = max(0, min(tnX, console->nCols - 1));
			console->nY = max(0, min(tnY, console->nRows - 1));

			// Paint the new one
			console_os_xy_needs_repainted;

			// Indicate success
			return(_CONSOLE_ERROR__NO_ERROR);
		}

		// Failure
		return(_CONSOLE_ERROR__HANDLE_NOT_FOUND);
	}




//////////
//
// Called to get the current X,Y position on the console
//
//////
	CONAPI s32 console_get_xy(uptr tnHandle, s32* tnX, s32* tnY)
	{
		SConsole*	console;


		// See if we have a console
		if (iConsole_validateInitialization() && (console = iConsole_find_byHandle(tnHandle)))
		{
			// Store the position
			if (tnX)	*tnX = console->nX;
			if (tnY)	*tnY = console->nY;

			// Indicate success
			return(_CONSOLE_ERROR__NO_ERROR);
		}

		// Failure
		return(_CONSOLE_ERROR__HANDLE_NOT_FOUND);
	}




//////////
//
// Called to scroll the console window up or down N-rows
//
//////
	s32 console_scroll(uptr tnHandle, s32 tnRows, bool tlMoveCursor)
	{
		return(0);
	}




//////////
//
// Reset all the input fields embedded within the console
//
//////
	s32 console_input_fields_clear_all(uptr tnHandle)
	{
		SConsole*	console;


		// See if we have a console
		if (iConsole_validateInitialization() && (console = iConsole_find_byHandle(tnHandle)))
		{
			// Reset
			gsInputRoot->populatedLength = 0;

			// Redraw everything
			InvalidateRect(console->hwnd, NULL, FALSE);

			// Indicate success
			return(_CONSOLE_ERROR__NO_ERROR);
		}

		// Failure
		return(_CONSOLE_ERROR__HANDLE_NOT_FOUND);
	}




//////////
//
// Add a new input field to the console
//
//////
	s32 console_input_field_add(uptr tnHandle, s32 tnX, s32 tnY, s32 tnLength, SBgra* backColor, SBgra* charColor, SDatum* liveValue)
	{
		SConsole*	console;
		union {
			s32			_conInput;
			SConInput*	conInput;
		};


		// See if we have a console
		if (iConsole_validateInitialization() && (console = iConsole_find_byHandle(tnHandle)))
		{
			// Get a new entry
			conInput = iConsole_input_addNew();
			if (conInput)
			{
				// Set the parameters
				conInput->nX			= tnX;
				conInput->nY			= tnY;
				conInput->nLength		= tnLength;
				conInput->liveValue		= liveValue;

				// Indicate success
				return(_CONSOLE_ERROR__NO_ERROR);
			}
		}

		// Failure
		return(_CONSOLE_ERROR__HANDLE_NOT_FOUND);
	}




//////////
//
// Delete an input field on the console
//
//////
	s32 console_input_field_delete(uptr tnHandle, s32 tnInputFieldHandle)
	{
		SConsole*	console;
		SConInput*	conInput;


		// See if we have a console
		if (iConsole_validateInitialization() && (console = iConsole_find_byHandle(tnHandle)))
		{
			// Get a new entry
			conInput = iConsole_input_find_byHandle(tnInputFieldHandle);
			if (conInput)
			{
				// Delete it
				memset(conInput, 0, sizeof(*conInput));

				// Indicate success
				return(_CONSOLE_ERROR__NO_ERROR);
			}
		}

		// Failure
		return(_CONSOLE_ERROR__HANDLE_NOT_FOUND);
	}




//////////
//
// Called to write some text to the console
//
//////
	s32 console_raw_push(uptr tnHandle, s32 tnX, s32 tnY, SBgra color, SDatum* textIn, bool tlWrap)
	{
		SConsole*	console;


		// See if we have a console
		if ((console = iConsole_find_byHandle(tnHandle)))
		{
		}

		// Failure
		return(_CONSOLE_ERROR__HANDLE_NOT_FOUND);
	}




//////////
//
// Called to read some text from the console
//
//////
	s32 console_raw_pullN(uptr tnHandle, s32 tnX, s32 tnY, s32 tnCount, SDatum* textOut)
	{
		return(-1);
	}




//////////
//
// Called to get the attributes of a specific character
//
//////
	s32 console_raw_pull1(uptr tnHandle, s32 tnX, s32 tnY, u8* c, SBgra* color, bool* tlBold, bool* tlItalic, bool* tlUnderline)
	{
		return(-1);
	}




//////////
//
// Called to write some VT100 text to the console
//
//////
	s32 console_vt100_push(uptr tnHandle, SDatum* vt100Text)
	{
		return(-1);
	}




//////////
//
// Callback, iterated through every option from iProperty_iterate() in console_setOptions()
//
//////
	bool iiConsole_setOptions_callback(SDatumCallback* cb)
	{
		SConsole* console;


		// Make sure our environment is sane
		console = (SConsole*)cb->extra1;

		// See what option they checked
		     if (console_check_prop(x))				{	console->nX					= iDatum_getAs_s32(&cb->value);			cb->flag1 = true;	}
		else if (console_check_prop(y))				{	console->nY					= iDatum_getAs_s32(&cb->value);			cb->flag1 = true;	}
		else if (console_check_prop(left))			{	console->nLeft				= iDatum_getAs_s32(&cb->value);			cb->flag1 = true;	}
		else if (console_check_prop(top))			{	console->nHeight			= iDatum_getAs_s32(&cb->value);			cb->flag1 = true;	}
		else if (console_check_prop(width))			{	console->nWidth				= iDatum_getAs_s32(&cb->value);			cb->flag1 = true;	}
		else if (console_check_prop(height))		{	console->nHeight			= iDatum_getAs_s32(&cb->value);			cb->flag1 = true;	}
		else if (console_check_prop(charWidth))		{	console->nCharWidth			= iDatum_getAs_s32(&cb->value);			cb->flag1 = true;	}
		else if (console_check_prop(charHeight))	{	console->nCharHeight		= iDatum_getAs_s32(&cb->value);			cb->flag1 = true;	}
		else if (console_check_prop(scrollRows))	{	console->nScrollRowsToKeep	= iDatum_getAs_s32(&cb->value);			cb->flag1 = true;	}
		else if (console_check_prop(backColor))		{	console->backColor.color	= iDatum_getAs_s32(&cb->value);			cb->flag1 = true;	}
		else if (console_check_prop(foreColor))		{	console->charColor.color	= iDatum_getAs_s32(&cb->value);			cb->flag1 = true;	}
		else if (console_check_prop(charColor))		{	console->charColor.color	= iDatum_getAs_s32(&cb->value);			cb->flag1 = true;	}
		else if (console_check_prop(title))			{	iDatum_duplicate(&console->title, &cb->value);						cb->flag1 = true;	}
		else if (console_check_prop(visible))
		{
			// Visible accepts Yes, yes, True, true, .T., .t., 1
			console->lVisible	= (console_check_value(yes) || console_check_value(true) || console_check_value(dot_t_dot) || iDatum_getAs_s32(&cb->value) != 0);
			cb->flag1			= true;

		} else {
			// Unknown, so just ignore it
			iConsole_silentError_passThru();
		}
		
		// Indicate more properties should be sent
		return(true);
	}




//////////
//
// Validate that we have gsRootConsole allocated,
// and any OS-specific initialization completed
//
//////
	bool iConsole_validateInitialization(void)
	{
		bool llResult;


		//////////
		// Make sure we have a root console buffer
		//////
			llResult = true;
			if (!gsConsoleRoot)
			{
				// Allocate
				iBuilder_createAndInitialize(&gsConsoleRoot, sizeof(SConsole) * 40);
				llResult &= (gsConsoleRoot != NULL);
			}


		//////////
		// Make sure we have a root input buffer
		//////
			if (!gsInputRoot)
			{
				// Allocate
				iBuilder_createAndInitialize(&gsInputRoot, sizeof(SConInput) * 40);
				llResult &= (gsInputRoot != NULL);
			}


		// Conclude with any OS initialization
		return(llResult |= console_os_validate_initialization);
	}




//////////
//
// Called to make sure the scroll buffer has been allocated,
// and to allocate it if not.
//
//////
	bool iConsole_validateScrollBuffer(SConsole* console)
	{
		// Make sure our environment is sane
		if (console)
		{
			// Do we already have a buffer?
			if (console->scrollBuffer)
				return(true);

			// Try to create one
			iBuilder_createAndInitialize(&console->scrollBuffer, sizeof(SConRow) * max(1000, console->nScrollRowsToKeep));

			// Indicate success or failure
			return((console->scrollBuffer != NULL));
		}

		// If we get here, invalid
		return(false);
	}




//////////
//
// Searches for the indicated console
//
//////
	SConsole* iConsole_find_byHandle(uptr tnHandle)
	{
		SConsole* console;


		// See if we're good
		if ((SConsole*)iBuilder_isPointer(gsConsoleRoot, tnHandle, (void**)&console))
		{
			// It's a valid pointer
			return(console);

		} else {
			// Invalid
			return(NULL);
		}
	}




//////////
//
// Called various places where something unexpected happened.
// Used during development only, intended to help find bugs.
//
//////
	void iConsole_silentError_passThru(void)
	{
		// Does nothing except trap the condition
		// Un-comment this code to put a breakpoint here
		// _asm nop;
	}




//////////
//
// Store a character, which may require scrolling to the next line
//
//////
	void iiConsole_storeCharacter(SConsole* console, char c)
	{
		// Store the character into the buffer, and re-render if necessary
		console_os_store_character;

		// Indicate the current X,Y needs to be repainted
		console_os_xy_needs_repainted;

		// Move to the next character
		++console->nX;
		iiConsole_validateXYRange(console);
	}




//////////
//
// Called to validate the X,Y are in range
//
//////
	void iiConsole_validateXYRange(SConsole* console)
	{
		//////////
		// Y
		//////
			if (console->nY < 0)
				console->nY = 0;

			if (console->nY > console->nRows)
				console->nY = console->nRows;


		//////////
		// X
		//////
			if (console->nX >= console->nCols)
			{
				// Need to move to the next row
				if (console->nY < console->nRows)
				{
					// Enough room to move down
					console->nX = 0;
					++console->nY;

				} else {
					// We need to scroll
					console->nX = 0;
					iiConsole_scroll(console);
				}
			}
	}




//////////
//
// Selects the indicated font into the console's DC
//
//////
	void iiConsole_selectFont(SConsole* console, s32 fontIndex)
	{
		SConFont* font;


		// Make sure the font's in range
		if (fontIndex < (s32)(gsConsoleFontRoot->populatedLength / sizeof(SConFont)))
		{
			// We're in range
			font = (SConFont*)gsConsoleFontRoot->buffer + (fontIndex * sizeof(SConFont));
			SelectObject(console->bmp->hdc, font->hfont);
		}
	}




//////////
//
// Called to scroll the console up one row
//
//////
	void iiConsole_scroll(SConsole* console)
	{
		SBuilderCallback bcb;


		// Copy each row forward
		memset(&bcb, 0, sizeof(bcb));
		bcb.extra1 = console;
		iBuilder_iterate(console->scrollBuffer, sizeof(SConRow), &bcb, (uptr)iConsole_scroll__callback);
	}

	// Uses bcb->extra1 for console, bcb->extra2 for the destination row, and bcb->iter_ptr for the source row
	bool iConsole_scroll__callback(SBuilderCallback* bcb)
	{
		SConsole*	console;
		SConRow*	rowDst;
		SConRow*	rowSrc;

		
		// Grab the row
		if (!bcb->extra2)
		{
			// First row
			bcb->extra2 = bcb->iter_ptr;

		} else {
			// Grab the pointers
			console	= (SConsole*)bcb->extra1;
			rowDst	= (SConRow*)bcb->extra2;
			rowSrc	= (SConRow*)bcb->iter_ptr;

			// Copy the row
			memcpy(rowDst->chars, rowSrc->chars, console->nCols * sizeof(SConChar));
// TODO:  We should actually iterate through each char and add an OS callback to handle any special OS structures

			// Prepare for the next iteration
			bcb->extra2 = bcb->iter_ptr;
		}

		// Continue processing each row
		return(true);
	}




//////////
//
// Called to see if there are any active console windows
//
//////
	bool iConsole_anyValidConsoles(void)
	{
		SBuilderCallback bcb;


		// See if there are any
		memset(&bcb, 0, sizeof(bcb));
		bcb._iterateFunc = (uptr)&iConsole_anyValidConsoles__callback;
		iBuilder_iterate(gsConsoleRoot, sizeof(SConsole), &bcb);

		// Indicate our status
		return(bcb.flag1);
	}

	bool iConsole_anyValidConsoles__callback(SBuilderCallback* bcb)
	{
		SConsole* console;


		// Grab the console
		console = (SConsole*)bcb->iter_ptr;
		if (console->hwnd && IsWindow(console->hwnd))
		{
			// We found one
			bcb->flag1 = true;

			// Stop iterating
			return(false);
		}

		// Continue iterating
		return(true);
	}




//////////
//
// Provides a system-wide unique id
//
//////
	u32 iGetNextUid(void)
	{
		// Simply return the next value
		return(gnNextUid++);
	}




//////////
//
// Called to add a new SConInput
//
//////
	SConInput* iConsole_input_addNew(void)
	{
		SConInput*			conInput;
		SBuilderCallback	bcb;


		// Iterate to find an empty slot
		memset(&bcb, 0, sizeof(bcb));
		iBuilder_iterate(gsInputRoot, sizeof(SConInput), &bcb, (uptr)&iConsole_input_addNew__callback);

		// Was it found?
		if (bcb.extra1)		conInput = (SConInput*)bcb.extra1;													// Found an empty slot
		else				conInput = (SConInput*)iBuilder_allocateBytes(gsInputRoot, sizeof(SConInput));		// Add a new entry

		// Reset and mark it valid
		if (conInput)
		{
			memset(conInput, 0, sizeof(SConInput));
			conInput->lValid = true;
		}

		// Indicate our success
		return(conInput);
	}

	bool iConsole_input_addNew__callback(SBuilderCallback* bcb)
	{
		SConInput* conInput;


		// Grab the pointer
		conInput = (SConInput*)bcb->iter_ptr;
		if (!conInput->lValid)
		{
			// We found an empty slot
			bcb->extra1 = conInput;

			// Stop iterating
			return(false);
		}

		// Continue iterating
		return(true);
	}




//////////
//
// Called to search for the input entry
//
//////
	SConInput* iConsole_input_find_byHandle(uptr tnInputFieldHandle)
	{
		SBuilderCallback bcb;


		// Iterate to find an empty slot
		memset(&bcb, 0, sizeof(bcb));
		bcb._extra1 = tnInputFieldHandle;
		iBuilder_iterate(gsInputRoot, sizeof(SConInput), &bcb, (uptr)&iConsole_input_find_byHandle__callback);

		// Was it found?
		if (bcb.extra2)
			return((SConInput*)bcb.extra2);		// Yes

		// If we get here, wasn't found
		return(NULL);
	}

	// Uses bcb->extra1 for the handle we're searching for, and bcb->extra2 for the found conInput
	bool iConsole_input_find_byHandle__callback(SBuilderCallback* bcb)
	{
		SConInput* conInput;


		// Grab the pointer
		conInput = (SConInput*)bcb->iter_ptr;
		if (conInput == (SConInput*)bcb->extra1)
		{
			// We found it
			bcb->extra2 = conInput;

			// Stop iterating
			return(false);
		}

		// Continue iterating
		return(true);
	}
