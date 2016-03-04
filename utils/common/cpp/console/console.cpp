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


// The _UNIT_TEST setting is determined by a compiler-defined flag
#ifdef _UNIT_TEST
	// This code is declared if we're compiling for unit tests
	// This command-line startup function is defined in xyz\console_xyz.h
	console_main_function
	{
		// The unit tests are defined in xyz\console_xyz.h
		console_unit_tests;
	}
#endif




//////////
//
// Called to allocate a new console
//
//////
	uptr console_allocate(SDatum* title, s32 tnLeft, s32 tnTop, s32 tnWidth, s32 tnHeight, s32 tnCharWidth, s32 tnCharHeight, SConCallback* cb)
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
				console->nLeft			= tnLeft;
				console->nTop			= tnTop;
				console->nWidth			= tnWidth;
				console->nHeight			= tnHeight;
				console->nCharWidth		= tnCharWidth;
				console->nCharHeight	= tnCharHeight;
				iDatum_duplicate(&console->title, title);

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
			console_cb.nLeft			= 0;
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
		if (cb && (console = iConsole_find_byHandle(tnHandle)))
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
		if ((console = iConsole_find_byHandle(tnHandle)))
		{
			// If it's changed, set it
			if (console->lVisible != tlVisible)
			{
				// Try to toggle the visible status
				if ((lnResult = console_os_toggle_visible(console)) != _CONSOLE_ERROR__NO_ERROR)
					console_os_error(console, lnResult);

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
		if ((console = iConsole_find_byHandle(tnHandle)))
		{
			// If it's changed, set it
			if ((lnResult = console_os_release(console)) != _CONSOLE_ERROR__NO_ERROR)
				console_os_error(console, lnResult);

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
		if ((console = iConsole_find_byHandle(tnHandle)))
		{
			// Iterate through all of the properties one-by-one
			memset(&cb, 0, sizeof(cb));
			cb._propAndValue_func = (uptr)&iiConsole_setOptions_callback;
			return(iProperty_iterate(&cb, properties));
		}

		// If we get here, error
		return(_CONSOLE_ERROR__HANDLE_NOT_FOUND);
	}

	// Callback iterated through every option from iProperty_iterate() in console_setOptions()
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
// Called to set the font to use from this point forward (until changed in the future)
//
//////
	s32 console_setFont(uptr tnHandle, SDatum* tcFontName, s32 tnPointSize, bool tlBold, bool tlItalic, bool tlUnderline)
	{
		s32			lnI;
		SConsole*	console;
		SConFont*	font;


		// See if we have a console
		if ((console = iConsole_find_byHandle(tnHandle)))
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
				iDatum_duplicate(&font->cFontName, tcFontName);
				font->nPointSize	= tnPointSize;
				font->lBold			= tlBold;
				font->lItalic		= tlItalic;
				font->lUnderline	= tlUnderline;

				// Call OS-specific code
				console_os_font_setup(console, font);

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
		if ((console = iConsole_find_byHandle(tnHandle)))
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
							iiConsole_moveToNextRow(console);

						} else if (c == 9) {
							// Tab
							for (lnJ = console->nX + 1; lnJ % 4 != 0; )
								++lnJ;

							// Make sure it's in range
							console->nX = min(console->nX, console->nWidth);

						} else {
							// Display the output
							iiConsole_storeCharacter(console, c);
						}
					}

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
// Called to scroll the console window up or down N-rows
//
//////
	s32 console_scroll(uptr tnHandle, s32 tnRows, bool tlMoveCursor)
	{
		return(0);
	}




//////////
//
// Called to write some text to the console
//
//////
	s32 console_raw_push(uptr tnHandle, s32 tnX, s32 tnY, SBgra color, SDatum* textIn, bool tlWrap)
	{
		return(-1);
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
// Validate that we have gsRootConsole allocated,
// and any OS-specific initialization completed
//
//////
	bool iConsole_validateInitialization(void)
	{
		bool llResult;


		// Make sure we have a root console buffer
		if (!gsConsoleRoot)
		{
			// Allocate
			iBuilder_createAndInitialize(&gsConsoleRoot, sizeof(SConsole) * 40);
			llResult = (gsConsoleRoot != NULL);

		} else {
			// We're good
			llResult = true;
		}

		// Conclude with any OS initialization
		return(llResult |= console_os_validate_initialization());
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
// Move to the next row, which may signal a scroll
//
//////
	void iiConsole_moveToNextRow(SConsole* console)
	{
		s32			lnX;
		SConRow*	conrow;


		// If we're keeping an unlimited buffer, we can always append even if we're at the end
		if (console->nScrollRowsToKeep == -1)
		{
			// Move down to the next row
			if ((console->nTopRow + console->nY + 1) * sizeof(SConRow) < console->scrollBuffer->populatedLength)
			{
				// There's room to move down one
				++console->nY;

			} else {
				// We need to add a new line
				conrow = (SConRow*)iBuilder_allocateBytes(console->scrollBuffer, sizeof(SConRow));
				if (conrow)
				{
					// Iterate through 
					for (lnX = 0; lnX < console->nWidth; lnX++)
					{
// TODO:  working here
					}
				}
			}

		} else if (console->nY < console->nHeight) {
			// There's room to move down one

		} else {
			// Everything must scroll up once
			++console->nTopRow;
		}
	}




//////////
//
// Store a character, which may require scrolling to the next line
//
//////
	void iiConsole_storeCharacter(SConsole* console, char c)
	{
	}




//////////
//
// Selects the indicated font into the console's dc
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
			SelectObject(console->hdc, font->hfont);
		}
	}
