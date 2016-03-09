//////////
//
// /libsf/utils/common/cpp/console/win/console_win.cpp
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
//     Jan.13.2016
//////
// Change log:
//     Jan.13.2016 - Initial creation
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





//////////
//
// Called for unit testing
//
//////
// #define _ASCII_CHART 0
	int console_win_unit_test(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
	{
		uptr				lnCon1;
		SDatum				title;
		SConCallback		ccb;
		SConInputCallback	cibc;
		SDatum				props, datum_eax, datum_ebx, datum_ecx, datum_edx, datum_esi, datum_edi, datum_ebp, datum_esp, datum_cs, datum_ds, datum_es, datum_fs, datum_gs;
		s8					buffer[1024];
		s8					buf_eax[8];
		s8					buf_ebx[8];
		s8					buf_ecx[8];
		s8					buf_edx[8];
		s8					buf_esi[8];
		s8					buf_edi[8];
		s8					buf_ebp[8];
		s8					buf_esp[8];
		s8					buf_cs[4];
		s8					buf_ds[4];
		s8					buf_es[4];
		s8					buf_fs[4];
		s8					buf_gs[4];


		//////////
		// Store instance
		//////
			ghInstance = hInstance;


		//////////
		// Allocate three consoles
		//////
			title.data_cs8	= "Regs";
			title.length	= strlen(title.data_cs8);
			sprintf(buffer, "backColor=0\nforeColor=%d", rgb(0,255,0));
			props.data_cs8	= &buffer[0];
			props.length	= strlen(buffer);
			memset(&ccb, 0, sizeof(ccb));
			ccb._console_keyDown	= (uptr)&iiConsole_win_unit_test__callback_keyDown;
			ccb._console_mouseDown	= (uptr)&iiConsole_win_unit_test__callback_mouseDown;
// 			lnCon1 = console_allocate(&title, -1, -1, 14, 15, &ccb);
			lnCon1 = console_allocate(&title, -1, -1, 20, 20, &ccb);
			console_setProperties(lnCon1, &props);
			console_show(lnCon1, true);


		//////////
		// Draw some text
		//////
			sprintf(buffer, "foreColor=%d\nbackColor=%d", rgb(0,255,0), rgb(0,0,0));
			props.length	= strlen(buffer);
			console_setProperties(lnCon1, &props);
#if !defined(_ASCII_CHART)
			console_gotoXY(lnCon1, 0, 1);
			console_print(lnCon1, " eax\263\n\r ebx\263\n\r ecx\263\n\r edx\263\n\r esi\263\n\r edi\263\n\r ebp\263\n\r esp\263\n\r  cs\263\n\r  ds\263\n\r  es\263\n\r  fs\263\n\r  gs\263");
#endif


		//////////
		// Draw an ASCII chart
		//////
#if defined(_ASCII_CHART)
			u8					lnC;
			s32					lnI, lnX, lnY;
			memset(buffer, 0, sizeof(buffer));
			for (lnI = 0, lnC = 0, lnY = 0; lnY < 16; lnY++)
			{
				// Iterate for every row
				for (lnX = 0; lnX < 16; lnX++)
				{
					// Store escape if need be
					buffer[lnI++] = '\\';

					// Store character
					buffer[lnI++] = lnC++;
				}

				// Move to start of next line
				buffer[lnI++] = ' ';
				buffer[lnI++] = ((lnY <= 9) ? lnY + '0' : lnY + 'a' - 10);
				buffer[lnI++] = '\n';
				buffer[lnI++] = '\r';
			}
			sprintf(buffer + lnI - 1, "0123456789abcdef");
			console_print(lnCon1, buffer, lnI + 15);
#endif


		//////////
		// Set the border color5
		//////
			console_setBorder(lnCon1, true, (SBgra*)&whiteColor);


		//////////
		// Some input areas
		//////
#if !defined(_ASCII_CHART)
			memset(&cibc, 0, sizeof(cibc));
			cibc.lSuppressBorder			= true;
			cibc.lInnerBorder				= true;
			cibc.innerBorderColor.color		= blackColor.color;
			cibc.lVisualize_onChange		= true;
			cibc.backColor_changed.color	= yellowColor.color;
			cibc.charColor_changed.color	= blackColor.color;
			cibc._onChanged		= (uptr)&iiConsole_win_unit_test__onChanged;
			cibc._onKeystroke	= (uptr)&iiConsole_win_unit_test__onKeystroke;
			cibc._onLostFocus	= (uptr)&iiConsole_win_unit_test__onLostFocus;
			cibc._onGotFocus	= (uptr)&iiConsole_win_unit_test__onGotFocus;

			datum_eax.data		= &buf_eax[0];
			datum_eax.length	= 8;
			memset(&buf_eax, 32, sizeof(buf_eax));
			console_input_field_add(lnCon1, 5, 1, datum_eax.length, (SBgra*)&greenColor, (SBgra*)&blackColor, &datum_eax, &cibc);

			datum_ebx.data		= &buf_ebx[0];
			datum_ebx.length	= 8;
			memset(&buf_ebx, 32, sizeof(buf_ebx));
			console_input_field_add(lnCon1, 5, 2, datum_ebx.length, (SBgra*)&greenColor, (SBgra*)&blackColor, &datum_ebx, &cibc);

			datum_ecx.data		= &buf_ecx[0];
			datum_ecx.length	= 8;
			memset(&buf_ecx, 32, sizeof(buf_ecx));
			console_input_field_add(lnCon1, 5, 3, datum_ecx.length, (SBgra*)&greenColor, (SBgra*)&blackColor, &datum_ecx, &cibc);

			datum_edx.data		= &buf_edx[0];
			datum_edx.length	= 8;
			memset(&buf_edx, 32, sizeof(buf_edx));
			console_input_field_add(lnCon1, 5, 4, datum_edx.length, (SBgra*)&greenColor, (SBgra*)&blackColor, &datum_edx, &cibc);

			datum_esi.data		= &buf_esi[0];
			datum_esi.length	= 8;
			memset(&buf_esi, 32, sizeof(buf_esi));
			console_input_field_add(lnCon1, 5, 5, datum_esi.length, (SBgra*)&greenColor, (SBgra*)&blackColor, &datum_esi, &cibc);

			datum_edi.data		= &buf_edi[0];
			datum_edi.length	= 8;
			memset(&buf_edi, 32, sizeof(buf_edi));
			console_input_field_add(lnCon1, 5, 6, datum_edi.length, (SBgra*)&greenColor, (SBgra*)&blackColor, &datum_edi, &cibc);

			datum_ebp.data		= &buf_ebp[0];
			datum_ebp.length	= 8;
			memset(&buf_ebp, 32, sizeof(buf_ebp));
			console_input_field_add(lnCon1, 5, 7, datum_ebp.length, (SBgra*)&greenColor, (SBgra*)&blackColor, &datum_ebp, &cibc);

			datum_esp.data		= &buf_esp[0];
			datum_esp.length	= 8;
			memset(&buf_esp, 32, sizeof(buf_esp));
			console_input_field_add(lnCon1, 5, 8, datum_esp.length, (SBgra*)&greenColor, (SBgra*)&blackColor, &datum_esp, &cibc);

			datum_cs.data	= &buf_cs[0];
			datum_cs.length	= 4;
			memset(&buf_cs, 32, sizeof(buf_cs));
			console_input_field_add(lnCon1, 5, 9, datum_cs.length, (SBgra*)&greenColor, (SBgra*)&blackColor, &datum_cs, &cibc);

			datum_ds.data	= &buf_ds[0];
			datum_ds.length	= 4;
			memset(&buf_ds, 32, sizeof(buf_ds));
			console_input_field_add(lnCon1, 5, 10, datum_ds.length, (SBgra*)&greenColor, (SBgra*)&blackColor, &datum_ds, &cibc);

			datum_es.data	= &buf_es[0];
			datum_es.length	= 4;
			memset(&buf_es, 32, sizeof(buf_es));
			console_input_field_add(lnCon1, 5, 11, datum_es.length, (SBgra*)&greenColor, (SBgra*)&blackColor, &datum_es, &cibc);

			datum_fs.data	= &buf_fs[0];
			datum_fs.length	= 4;
			memset(&buf_fs, 32, sizeof(buf_fs));
			console_input_field_add(lnCon1, 5, 12, datum_fs.length, (SBgra*)&greenColor, (SBgra*)&blackColor, &datum_fs, &cibc);

			datum_gs.data	= &buf_gs[0];
			datum_gs.length	= 4;
			memset(&buf_gs, 32, sizeof(buf_gs));
			console_input_field_add(lnCon1, 5, 13, datum_gs.length, (SBgra*)&greenColor, (SBgra*)&blackColor, &datum_gs, &cibc);
#endif


		//////////
		// Draw a box around it
		//////
#if !defined(_ASCII_CHART)
// 			console_box_single(lnCon1, 0, 0, 14, 14, (SBgra*)&blackColor, (SBgra*)&greenColor);
			console_box_double(lnCon1, 0, 0, 14, 14, (SBgra*)&blackColor, (SBgra*)&greenColor);
#endif


		//////////
		// Read messages
		//////
			iConsole_win_readMessages();


		//////////
		// Indicate success
		//////
			return(_CONSOLE_ERROR__NO_ERROR);

	}

	void iiConsole_win_unit_test__onChanged(uptr tnConsoleHandle, uptr tnConInputHandle)
	{
	}

	void iiConsole_win_unit_test__onKeystroke(uptr tnConsoleHandle, uptr tnConInputHandle, s32 tnRawKey, bool tlCtrl, bool tlAlt, bool tlShift, bool tlLeft, bool tlMiddle, bool tlRight, bool tlCaps, bool tlNum, bool tlScroll, bool tlAnyButton)
	{
	}

	void iiConsole_win_unit_test__onLostFocus(uptr tnConsoleHandle, uptr tnConInputHandle)
	{
		((SConInput*)tnConInputHandle)->cicb.lChanged = false;
	}

	void iiConsole_win_unit_test__onGotFocus(uptr tnConsoleHandle, uptr tnConInputHandle)
	{
	}

	s32 iiConsole_win_unit_test__callback_keyDown(SConCallback* ccb)
	{
		// Indicate success
		return(0);
	}

	s32 iiConsole_win_unit_test__callback_mouseDown(SConCallback* ccb)
	{
		SBgra color;


		// Shift the colors over one
		color.red = ccb->console->borderColor.grn;
		color.grn = ccb->console->borderColor.blu;
		color.blu = ccb->console->borderColor.red;
		console_setBorder(ccb->_console, true, &color);

		// Indicate success
		return(0);
	}




//////////
//
// Called to make sure our Windows prerequisites have been setup
//
//////
	bool console_win_validateInitialization(void)
	{
		// Register our class
		iConsole_win_registerWndClass();

		// Make sure we have at least one font
		iConsole_win_fontSetup_init();

		// Success
		return(true);
	}




//////////
//
// Called to create a window
//
//////
	s32 console_win_create_window(SConsole* console)
	{
		s32					lnLength, lnSize;
		DWORD				err;
		RECT				lrc;
		SBuilderCallback	bcb;
		s8					buffer[_MAX_FNAME];


		//////////
		// If there's already a window, delete the current window before creating the new one
		//////
			if (console->hwnd)
			{
				// If it's valid, destroy it
				if (IsWindow(console->hwnd))
					DestroyWindow(console->hwnd);

				// Reset
				console->hwnd = NULL;
			}


		//////////
		// Prepare a window of at least 1x1
		//////
			console->nWidth		= max(console->nCharWidth,  console->nWidth);
			console->nHeight	= max(console->nCharHeight, console->nHeight);


		//////////
		// Center the window if need be
		//////
			GetWindowRect(GetDesktopWindow(), &lrc);
			if (console->nLeft < 0)			console->nLeft	= ((lrc.right - lrc.left) - console->nWidth)	/ 2;
			if (console->nTop  < 0)			console->nTop	= ((lrc.bottom - lrc.top) - console->nHeight)	/ 2;


			// Assemble the title
			lnLength = min(_MAX_FNAME - 1, console->title.length);
			memcpy(buffer, console->title.data_cs8, lnLength);
			buffer[lnLength] = 0;

			// Create the window
			SetRect(&lrc, console->nLeft, console->nTop, console->nLeft + console->nWidth, console->nTop + console->nHeight);
			AdjustWindowRect(&lrc, WS_OVERLAPPEDWINDOW, FALSE);
			console->hwnd = CreateWindow(cgc_consoleClass,	buffer, WS_OVERLAPPEDWINDOW, 
															lrc.left,
															lrc.top,
															lrc.right  - lrc.left,
															lrc.bottom - lrc.top,
															NULL, NULL, ghInstance, NULL);

			// If it failed, we're done
			err = GetLastError();
			if (!console->hwnd)
				return(_CONSOLE_ERROR__CANNOT_CREATE_WINDOW);


		//////////
		// Create the background bitmap for off-screen rendering
		//////
			console->bmp = iBmp_allocate();
			if (!console->bmp)
				return(_CONSOLE_ERROR__WINDOW_SETUP_NOT_COMPLETED);

			// Size it
			iBmp_createBySize(console->bmp, console->nWidth, console->nHeight, 24);
			SetRect(&lrc, 0, 0, console->nWidth, console->nHeight);

			// Initially set the background color
			iBmp_fillRect(console->bmp, &lrc, console->backColor);


		//////////
		// Create a timer for the cursor
		//////
			console->cursorTimerId = iGetNextWmApp();
			SetTimer(console->hwnd, console->cursorTimerId, 333, NULL);


		//////////
		// Determine row buffer geometry
		//////
			console->nCols		= (console->nWidth  / console->nCharWidth);			// Columns
			console->nRows		= (console->nHeight / console->nCharHeight);		// Rows
			console->nTopRow	= 0;												// Top row at the start of the buffer
			console->nXText		= 0;												// Text cursor position @ col = 0
			console->nYText		= 0;												// Text cursor position @ row = 0
			console->nXCursor	= -1;												// Keyboard cursor position not in use
			console->nYCursor	= -1;												// Keyboard cursor position not in use


		//////////
		// Create the console's character buffer
		//////
			lnSize = sizeof(SConRow) * console->nRows;
			iBuilder_createAndInitialize(&console->scrollBuffer, lnSize);
			if (!console->scrollBuffer)
				return(_CONSOLE_ERROR__WINDOW_SETUP_NOT_COMPLETED);

			// Initialize every row
			iBuilder_allocateBytes(console->scrollBuffer, lnSize);
			memset(&bcb, 0, sizeof(bcb));
			bcb.extra1 = console;
			iBuilder_iterate(console->scrollBuffer, sizeof(SConRow), &bcb, (uptr)&iConsole_win_create_window__callbackRow);


		//////////
		// Indicate success
		//////
			return(_CONSOLE_ERROR__NO_ERROR);

	}




/////////
//
// Called to toggle the visible state, which either shows or hides
//
//////
	s32 console_win_toggle_visible(SConsole* console)
	{
		// Make sure the 
		if (console)
		{
			// Toggle
			console->lVisible = !console->lVisible;

			// If it's visible, make sure it exists
			if (console->lVisible && (!console->hwnd || !IsWindow(console->hwnd)))
				console_win_create_window(console);

			// If there's a window, adjust it
			if (console->hwnd && IsWindow(console->hwnd))
			{
				// Show or hide the window
				ShowWindow(console->hwnd, ((console->lVisible) ? SW_SHOW : SW_HIDE));

				// Redraw everything
				InvalidateRect(console->hwnd, NULL, false);

				// We're good
				return(_CONSOLE_ERROR__NO_ERROR);

			} else {
				// Invalid window
				return(_CONSOLE_ERROR__INVALID_WINDOW);
			}

		} else {
			// Invalid console
			return(_CONSOLE_ERROR__HANDLE_NOT_FOUND);
		}
	}




//////////
//
// Called to release a console, and its associated window
//
//////
	s32 console_win_release(SConsole* console)
	{
		// Make sure the environment is sane
		if (console)
		{
			// Is it a valid window?
			if (console->hwnd && IsWindow(console->hwnd))
			{
				// Release the window
				DestroyWindow(console->hwnd);

				// Reset the handle
				console->hwnd = NULL;

				// Success
				return(_CONSOLE_ERROR__NO_ERROR);

			} else {
				// Invalid window
				return(_CONSOLE_ERROR__INVALID_WINDOW);
			}

		} else {
			// Invalid handle
			return(_CONSOLE_ERROR__HANDLE_NOT_FOUND);
		}
	}




//////////
//
// Receives errors related to the console
//
//////
	s32 console_win_error(SConsole* console, s32 tnErrorNum)
	{
		// Just pass-thru unless a breakpoint is set here
		_asm nop;
	}




//////////
//
// Called to handle Windows-specific font setup
//
//////
	bool console_win_fontSetup(SConsole* console, SConFont* font)
	{
		// Font creation for either fixed-point or system fonts
		if (font->lFixed)
		{
			// Internal fixed-point font
			iConsole_win_fontSetup_scaleAsNeeded(console, font);

		} else {
			// System font
			// Create a DC for the font
			font->hdc = CreateCompatibleDC(GetDC(GetDesktopWindow()));

			// Create the font
			font->_sizeUsedForCreateFont	= -MulDiv(font->nPointSize, GetDeviceCaps(font->hdc, LOGPIXELSY), 72);
			font->hfont						= CreateFont(font->_sizeUsedForCreateFont, 0, 0, 0, ((font->lBold) ? FW_BOLD : FW_NORMAL), ((font->lItalic) ? 1 : 0), ((font->lUnderline) ? 1 : 0), false, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_NATURAL_QUALITY, FF_DONTCARE, font->cFontName.data);

			// Select into the dc
			SelectObject(font->hdc, font->hfont);

			// Find out the text metrics
			GetTextMetricsA(font->hdc, &font->tm);
		}

		// If we get here, we're good
		return(true);
	}




//////////
//
// Called to handle Windows-specific initialization
//
//////
	uptr console_win_initialize(void)
	{
		// Nothing to do
		// Initialization is handled automatically on every function
		// Indicate success
		return(_CONSOLE_ERROR__NO_ERROR);
	}




//////////
//
// Called when the screen needs repainted
//
//////
	void console_win_xy_needs_repainted(SConsole* console)
	{
		RECT lrc;


		// Repaint the current character
		SetRect(&lrc,	console->nXText * console->nCharWidth,
						console->nYText * console->nCharHeight,
						((console->nXText + 1) * console->nCharWidth),
						((console->nYText + 1) * console->nCharHeight));
		
		// Signal the rectangle needs redrawn
		InvalidateRect(console->hwnd, &lrc, false);
	}




//////////
//
// Called when a character needs repainted
//
//////
	void console_win_xy_needs_repainted_atxy(SConsole* console, s32 tnX, s32 tnY)
	{
		RECT lrc;


		// Repaint the current character (and the border around it up to four pixels out)
		SetRect(&lrc,	(tnX * console->nCharWidth)  - 4,
						(tnY * console->nCharHeight) - 4,
						((tnX + 1) * console->nCharWidth) + 4,
						((tnY + 1) * console->nCharHeight) + 4);
		
		// Signal the rectangle needs redrawn
		InvalidateRect(console->hwnd, &lrc, false);
	}




//////////
//
// Called to set the border color
//
//////
	s32 console_win_set_border(SConsole* console, bool tlShowBorder, SBgra* color)
	{
		DWMNCRENDERINGPOLICY policy;


		// Store the new values
		console->lShowBorder		= tlShowBorder;
		console->borderColor.color	= color->color;

		// Turn off aero glass so the border renders properly
		if (tlShowBorder)		policy = DWMNCRP_DISABLED;
		else					policy = DWMNCRP_ENABLED;
		DwmSetWindowAttribute(console->hwnd, DWMWA_NCRENDERING_POLICY, (void*)&policy, sizeof(policy));

		// Signal the non-client repaint
		SendMessage(console->hwnd, WM_NCPAINT, 0, 0);
		
		// Indicate success
		return(_CONSOLE_ERROR__NO_ERROR);
	}




//////////
//
// Called to store the indicated character into the console buffer
//
//////
	void console_win_store_character(SConsole* console, u8 c, bool tlAtCursorXY, SBgra* backColor, SBgra* charColor)
	{
		// Pass-thru to the common function
		console_win_store_character_atxy(	console, c,		((tlAtCursorXY) ? console->nXCursor : console->nXText),
															((tlAtCursorXY) ? console->nYCursor : console->nYText),
											backColor, charColor);
	}

	void console_win_store_character_atxy(SConsole* console, u8 c, s32 tnX, s32 tnY, SBgra* backColor, SBgra* charColor)
	{
		SConChar* conChar;


		// Make sure the environment is sane
		if (iConsole_find_conChar_byXY(console, tnX, tnY, NULL, &conChar))
		{
			// Store character and attributes
			conChar->c					= c;
			conChar->backColor.color	= backColor->color;
			conChar->charColor.color	= charColor->color;
			conChar->nFont				= console->nCharFont;

			// Redraw the one character
			iConsole_win_renderSingleChar(console, tnX, tnY, conChar);
		}
	}




//////////
//
// Support functions
//
//////
	// Initialize SConRows one by one
	bool iConsole_win_create_window__callbackRow(SBuilderCallback* bcb)
	{
		s32					lnSize;
		SConsole*			console;
		SConRow*			conRow;
		SBuilderCallback	bcb2;


		// Grab our pointers
		console	= (SConsole*)bcb->extra1;
		conRow	= (SConRow*)bcb->iter_ptr;

		// Prepare the characters
		conRow->nWidth	= console->nCols;
		lnSize			= sizeof(SConChar) * conRow->nWidth;
		iBuilder_createAndInitialize(&conRow->chars, lnSize);
		if (conRow->chars)
		{
			// Allocate the characters
			iBuilder_allocateBytes(conRow->chars, lnSize);

			// Initialize every character to its default value
			memset(&bcb2, 0, sizeof(bcb2));
			bcb2.extra1 = console;
			iBuilder_iterate(conRow->chars, sizeof(SConRow), &bcb2, (uptr)&iConsole_win_create_window__callbackCol);
		}

		// Continue iterating
		return(true);
	}

	// Initialize SConChars one by one
	bool iConsole_win_create_window__callbackCol(SBuilderCallback* bcb)
	{
		SConsole*	console;
		SConChar*	conChar;


		// Grab our pointers
		console	= (SConsole*)bcb->extra1;
		conChar	= (SConChar*)bcb->iter_ptr;

		// Populate
		conChar->c					= 32;		// Space
		conChar->nFont				= console->nCharFont;
		conChar->backColor.color	= console->backColor.color;
		conChar->charColor.color	= console->charColor.color;

		// Continue iterating
		return(true);
	}




//////////
//
// Called to setup the font by setting up the first four fixed point fonts
//
//////
	void iConsole_win_fontSetup_init(void)
	{
		SConFont_fixed* font_fixed;


		// If we haven't yet setup our fonts, do so now
		if (!gsFontFixedRoot)
		{

			//////////
			// Initialize the block
			//////
				iBuilder_createAndInitialize(&gsFontFixedRoot, sizeof(SConFont_fixed) * 16);
				if (!gsFontFixedRoot)
					return;		// Should never happen


			//////////
			// Create the fixed entries
			//////
				font_fixed = (SConFont_fixed*)iBuilder_allocateBytes(gsFontFixedRoot, sizeof(SConFont_fixed) * (_CONSOLE_FONT__MAX_FIXED + 1));
				if (!font_fixed)
					return;		// Should never happen


			//////////
			// 8x6
			//////
				font_fixed->fontBase			= &gxFontBase_8x6[0];
				font_fixed->fontBase_original	= font_fixed->fontBase;
				font_fixed->lCustomScaled		= false;
				font_fixed->nCharWidth			= 8;			font_fixed->nCharHeight	= 6;
				font_fixed->nFontX				= 8;			font_fixed->nFontY		= 6;
				iConsole_win_fontSetup_scalePhysically(font_fixed);


			//////////
			// 8x8
			//////
				++font_fixed;
				font_fixed->fontBase			= &gxFontBase_8x8[0];
				font_fixed->fontBase_original	= font_fixed->fontBase;
				font_fixed->lCustomScaled		= false;
				font_fixed->nCharWidth			= 8;			font_fixed->nCharHeight	= 8;
				font_fixed->nFontX				= 8;			font_fixed->nFontY		= 8;
				iConsole_win_fontSetup_scalePhysically(font_fixed);


			//////////
			// 8x14
			//////
				++font_fixed;
				font_fixed->fontBase			= &gxFontBase_8x14[0];
				font_fixed->fontBase_original	= font_fixed->fontBase;
				font_fixed->lCustomScaled		= false;
				font_fixed->nCharWidth			= 8;			font_fixed->nCharHeight	= 14;
				font_fixed->nFontX				= 8;			font_fixed->nFontY		= 14;
				iConsole_win_fontSetup_scalePhysically(font_fixed);


			//////////
			// 8x16
			//////
				++font_fixed;
				font_fixed->fontBase			= &gxFontBase_8x16[0];
				font_fixed->fontBase_original	= font_fixed->fontBase;
				font_fixed->lCustomScaled		= false;
				font_fixed->nCharWidth			= 8;			font_fixed->nCharHeight	= 16;
				font_fixed->nFontX				= 8;			font_fixed->nFontY		= 16;
				iConsole_win_fontSetup_scalePhysically(font_fixed);


			//////////
			// 16x32
			//////
				++font_fixed;
				font_fixed->fontBase			= &gxFontBase_8x16[0];
				font_fixed->fontBase_original	= font_fixed->fontBase;
				font_fixed->lCustomScaled		= false;
				font_fixed->nCharWidth			= 16;			font_fixed->nCharHeight	= 32;
				font_fixed->nFontX				= 8;			font_fixed->nFontY		= 16;
				iConsole_win_fontSetup_scalePhysically(font_fixed);


			//////////
			// 8x12
			//////
				++font_fixed;
				font_fixed->fontBase			= &gxFontBase_8x6[0];
				font_fixed->fontBase_original	= font_fixed->fontBase;
				font_fixed->lCustomScaled		= false;
				font_fixed->nCharWidth			= 8;			font_fixed->nCharHeight	= 12;
				font_fixed->nFontX				= 8;			font_fixed->nFontY		= 6;
				font_fixed->nAdjustmentY		= -1;
				iConsole_win_fontSetup_scalePhysically(font_fixed);


			//////////
			// 8x16 using 8x8 font
			//////
				++font_fixed;
				font_fixed->fontBase			= &gxFontBase_8x8[0];
				font_fixed->fontBase_original	= font_fixed->fontBase;
				font_fixed->lCustomScaled		= false;
				font_fixed->nCharWidth			= 8;			font_fixed->nCharHeight	= 16;
				font_fixed->nFontX				= 8;			font_fixed->nFontY		= 8;
				font_fixed->nAdjustmentY		= -1;
				iConsole_win_fontSetup_scalePhysically(font_fixed);

		}
	}




//////////
//
// Called to scale the font, or look for one that's already been scaled
//
//////
	void iConsole_win_fontSetup_scaleAsNeeded(SConsole* console, SConFont* font)
	{
		s32					lnX, lnY;
		bool				llFontChosen;
		u8*					fontBase;
		SConFont_fixed*		font_fixed;


		//////////
		// Determine which font is needed
		//////
			llFontChosen = false;
			if (font->nActualX == 8)
			{
				// 8-pixels wide
				lnX = 8;

				// See how high
				switch (font->nActualY)
				{
					case 6:
						// 8x6 font
						lnY				= 6;
						fontBase		= &gxFontBase_8x6[0];
						llFontChosen	= true;
						break;

					case 8:
						// 8x8 font
						lnY				= 8;
						fontBase		= &gxFontBase_8x8[0];
						llFontChosen	= true;
						break;

					case 14:
						// 8x14 font
						lnY				= 14;
						fontBase		= &gxFontBase_8x14[0];
						llFontChosen	= true;
						break;

					case 16:
						// 8x16 font
						lnY				= 16;
						fontBase		= &gxFontBase_8x16[0];
						llFontChosen	= true;
						break;
				}
			}


		//////////
		// If it's not a standard size, then we are into assumption and/or scaling
		//////
			if (!llFontChosen)
			{
				// No matching font, we'll need to assume one
				if (console->nCharWidth == 8)
				{
					// 8-pixels wide
					lnX	= 8;

					// See how high
					switch (console->nCharHeight)
					{
						case 6:
							// 8x6 font
							lnY				= 6;
							fontBase		= &gxFontBase_8x6[0];
							llFontChosen	= true;
							break;

						case 8:
							// 8x8 font
							lnY				= 8;
							fontBase		= &gxFontBase_8x8[0];
							llFontChosen	= true;
							break;

						case 14:
							// 8x14 font
							lnY				= 14;
							fontBase		= &gxFontBase_8x14[0];
							llFontChosen	= true;
							break;

						default:
						case 16:
							// 8x16 font
							lnY				= 16;
							fontBase		= &gxFontBase_8x16[0];
							llFontChosen	= true;
							break;
					}

				} else {
					// Assume 8x16 and then scale up to what's needed
					lnX				= 8;
					lnY				= 16;
					fontBase		= &gxFontBase_8x16[0];
					llFontChosen	= true;
				}
			}


		//////////
		// Determine what size it should be
		//////
			if (lnX != console->nCharWidth || lnY != console->nCharHeight)
			{
				// It needs to be scaled
				font_fixed = iConsole_win_fontSetup_searchOrCreate(console->nWidth, console->nHeight, lnX, lnY, true);

			} else {
				// It's the correct width
				font_fixed = iConsole_win_fontSetup_searchOrCreate(console->nWidth, console->nHeight, lnX, lnY, false);
			}

	}




//////////
//
// Searches for the exact match, and creates a scaled font if need be
//
//////
	SConFont_fixed* iConsole_win_fontSetup_searchOrCreate(s32 tnCharWidth, s32 tnCharHeight, s32 tnFontX, s32 tnFontY, bool tlCreateIfNotFound)
	{
		s32					lnI;
		SConFont_fixed*		font_fixed;


		//////////
		// Make sure our font selection is sane
		//////
			// X must be 8
			if (tnFontX != 8)
				tnFontX = 8;

			// Y must be 6,8,14,16
			switch (tnFontY)
			{
				case 6:
				case 8:
				case 14:
				case 16:
					// These are all good
					break;

				default:
					// Out of bounds, find to the closest
					     if (tnCharHeight <= 6)		tnFontY = 6;
					else if (tnCharHeight <= 8)		tnFontY = 8;
					else if (tnCharHeight <= 14)	tnFontY = 14;
					else							tnFontY = 16;
			}
			// Right now, X is 8, and Y is one of 6,8,14,16


		//////////
		// Search for the font
		//////
			for (lnI = 0; lnI < (s32)gsFontFixedRoot->populatedLength; lnI += sizeof(SConFont_fixed))
			{
				// Grab this font
				font_fixed = (SConFont_fixed*)(gsFontFixedRoot->buffer + lnI);

				// Does it match?
				if (font_fixed->nCharWidth == tnCharWidth && font_fixed->nCharHeight == tnCharHeight && font_fixed->nFontX == tnFontX && font_fixed->nFontY == tnFontY)
					return(font_fixed);		// We found a match to this existing font
			}


		//////////
		// If we get here, not found
		//////
			if (tlCreateIfNotFound)
			{
				// Go ahead and create it
				font_fixed = (SConFont_fixed*)iBuilder_allocateBytes(gsFontFixedRoot, sizeof(SConFont_fixed));
				if (font_fixed)
				{

					//////////
					// Create the base entry
					//////
						font_fixed->lCustomScaled	= false;
						font_fixed->nCharWidth		= tnCharWidth;
						font_fixed->nCharHeight		= tnCharHeight;
						font_fixed->nFontX			= tnFontX;
						font_fixed->nFontY			= tnFontY;


					//////////
					// Perform the physical scaling for the font characters
					//////
						font_fixed->fontBase = NULL;
						switch (tnFontY)
						{
							case 6:
								font_fixed->fontBase_original	= &gxFontBase_8x6[0];
								break;

							case 8:
								font_fixed->fontBase_original	= &gxFontBase_8x8[0];
								break;

							case 14:
								font_fixed->fontBase_original	= &gxFontBase_8x14[0];
								break;

							case 16:
								font_fixed->fontBase_original	= &gxFontBase_8x16[0];
								break;
						}

						// Physically scale
						iConsole_win_fontSetup_scalePhysically(font_fixed);

				}

			} else {
				// We're done, not found
				font_fixed = NULL;
			}


		//////////
		// Indicate our status
		//////
			return(font_fixed);

	}




//////////
//
// Called to scale the font set to the indicated size.
// It does this by:
//
//		(1)  Creating an 18x18 character array
//		(2)  Populating it with the base font in black text on white background
//		(3)  Scaling it to the appropriate size
//		(4)  Allocating the output byte-level pixel buffer for the scaled fonts (holding 256 shades of gray for each pixel)
//
//////
	// Smallest output font allowed is 3x3
	void iConsole_win_fontSetup_scalePhysically(SConFont_fixed* font_fixed)
	{
		u8			lcThisCharacter, lnCharBits, lcMask;
		s32			lnC, lnX, lnY, lnRow, lnCol, lnWidthIn, lnHeightIn, lnWidthOut, lnHeightOut, lnPixelNum;
		SBitmap*	bmpIn;
		SBitmap*	bmpOut;
		RECT		lrc;
		SBgr*		lrgb;


		// Make sure our parameters are in a sane range
		font_fixed->nCharWidth	= max(3, font_fixed->nCharWidth);
		font_fixed->nCharHeight	= max(3, font_fixed->nCharHeight);

		// Create the basic bitmap
		lnWidthIn	= (font_fixed->nFontX		* 18);
		lnHeightIn	= (font_fixed->nFontY		* 18);
		lnWidthOut	= (font_fixed->nCharWidth	* 18);
		lnHeightOut	= (font_fixed->nCharHeight	* 18);

		// Allocate bitmaps
		bmpIn	= iBmp_allocate();
		bmpOut	= iBmp_allocate();

		// Allocate enough space for every ASCII pixel
		font_fixed->fontBase = (u8*)malloc(256 * font_fixed->nCharWidth * font_fixed->nCharHeight * sizeof(f32));

		// Was everything allocated correctly?
		if (bmpIn && bmpOut && font_fixed->fontBase)
		{

			//////////
			// Create input and output bitmaps
			///////
				iBmp_createBySize(bmpIn,	lnWidthIn,		lnHeightIn,		24);
				iBmp_createBySize(bmpOut,	lnWidthOut,		lnHeightOut,	24);


			//////////
			// Initialize it to white
			//////
				SetRect(&lrc, 0, 0, lnWidthIn, lnHeightIn);
				iBmp_fillRect(bmpIn, &lrc, whiteColor);
//iBmp_saveToDisk(bmpIn,  "c:\\temp\\in_before.bmp");


			//////////
			// Redraw all 256 characters (0x00 .. 0xff)
			//////
				for (lnC = 0, lnRow = font_fixed->nFontY, lcThisCharacter = 0; lnC < 256; lnC++, lcThisCharacter++, lnRow = ((s32)((lnC / 16) + 1) * font_fixed->nFontY))
				{
					// Offset for this character into font_fixed->fontBase_original[]
					lnPixelNum = lnC * font_fixed->nFontY;

					// Draw the character
					for (lnY = 0; lnY < font_fixed->nFontY; lnY++, lnPixelNum++)
					{
						// Prepare for drawing bits across this row
						lrgb = (SBgr*)(bmpIn->bd + ((bmpIn->bi.biHeight - lnRow - lnY) * bmpIn->rowWidth) + ((s32)((lnC % 16) + 1) * font_fixed->nFontX * 3));

						// Grab the bits pattern for this row of the character
						lnCharBits = font_fixed->fontBase_original[lnPixelNum];

						// Iterate through all of the bits setting pixels for bits which are 1
						for (lnX = 0, lcMask = 0x80; lnX < font_fixed->nFontX; lnX++, lrgb++, lcMask >>= 1)
						{
							// If it's on, set the pixel
							if ((lnCharBits & lcMask) != 0)
							{
								// Foreground bits are black
								lrgb->red = blackColor.red;
								lrgb->grn = blackColor.grn;
								lrgb->blu = blackColor.blu;
							}
						}
					}
				}


			//////////
			// Scale the bitmap to its new size
			//////
// iBmp_saveToDisk(bmpIn,  "c:\\temp\\in.bmp");
				iBmp_scale(bmpOut, bmpIn);
// iBmp_saveToDisk(bmpOut, "c:\\temp\\out.bmp");

				// Delete the input
				iBmp_delete(&bmpIn, true, true);


			//////////
			// Extract the scaled bits back out
			//////
				// Iterate character-by-character
				for (lnC = 0, lnPixelNum = 0; lnC < 256; lnC++)
				{
					// Iterate for every vertical pixel
					for (lnY = 0, lnRow = (s32)((lnC / 16) + 1) * font_fixed->nCharHeight, lnCol = (s32)(lnC % 16); lnY < font_fixed->nCharHeight; lnY++)
					{
						// Grab pointer to the start of this row
						lrgb = (SBgr*)(bmpOut->bd + ((bmpOut->bi.biHeight - lnRow - lnY - font_fixed->nAdjustmentY) * bmpOut->rowWidth) + ((((s32)(lnCol + 1) * font_fixed->nCharWidth) + font_fixed->nAdjustmentX) * 3));

						// Extract each pixel into the output buffer
						for (lnX = 0; lnX < font_fixed->nCharWidth; lnX++, lnPixelNum++, lrgb++)
						{
							font_fixed->fontBase_f32[lnPixelNum] = (f32)(255 - lrgb->red) / 255.0f;
// Invert this section (for debugging purposes)
// lrgb->red = 255 - lrgb->red;
// lrgb->grn = 128;
// lrgb->blu = 128;
						}
					}
// Output after each character to make sure it's "swiping" the correct 
// iBmp_saveToDisk(bmpOut, "c:\\temp\\out2.bmp");
// if (font_fixed->nCharHeight == 12)
// 	_asm nop;
				}
				// When we get here, we have our scaled fonts
				iBmp_delete(&bmpOut, true, true);

				// We're good, font was custom scaled
				font_fixed->lCustomScaled = true;

		} else {
			// If we get here, failure allocating something
			if (font_fixed->fontBase)		free(font_fixed->fontBase);
			if (bmpIn)						iBmp_delete(&bmpIn,  true, true);
			if (bmpOut)						iBmp_delete(&bmpOut, true, true);

			// Set it to the original and update the values
			font_fixed->fontBase		= font_fixed->fontBase_original;
			font_fixed->lCustomScaled	= false;
			font_fixed->nCharWidth		= font_fixed->nFontX;
			font_fixed->nCharHeight		= font_fixed->nFontY;
		}
	}




//////////
//
// Register the console window class with Windows
//
//////
	void iConsole_win_registerWndClass(void)
	{
		WNDCLASSEX wcex;


		// See if it's already been registered
		if (!GetClassInfoExA(ghInstance, (cs8*)cgc_consoleClass, &wcex))
		{
			// Not yet
			memset(&wcex, 0, sizeof(wcex));
			wcex.cbSize			= sizeof(WNDCLASSEX);
			wcex.style			= CS_HREDRAW | CS_VREDRAW;
			wcex.lpfnWndProc	= iConsole_wndProc;
			wcex.hInstance		= ghInstance;
			wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
			wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
			wcex.lpszClassName	= cgc_consoleClass;
			RegisterClassEx(&wcex);
		}
	}




//////////
//
// Render the console
//
//////
	s32 iConsole_win_render(SConsole* console)
	{
		SBuilderCallback bcb;


		// Full color background
		iBmp_fillRect(console->bmp, &console->rc, console->backColor);

		// Iterate through every row
		memset(&bcb, 0, sizeof(bcb));
		bcb.extra1	= console;
		iBuilder_iterate_N_to_N(console->scrollBuffer, sizeof(SConRow), console->nTopRow, console->nTopRow + console->nRows, &bcb, (uptr)&iConsole_win_render__callbackRow);

		// All done, force a full repaint by Windows
		InvalidateRect(console->hwnd, NULL, false);

		// Indicate how many rows were rendered
		return(console->nRows);
	}

	// Uses bcb->extra1 for console, bcb->iter_ptr as conRow
	bool iConsole_win_render__callbackRow(SBuilderCallback* bcb)
	{
		SConsole*			console;
		SConRow*			conRow;
		SBuilderCallback	bcb2;


		// Grab our pointers
		console	= (SConsole*)bcb->extra1;
		conRow	= (SConRow*)bcb->iter_ptr;

		// Iterate through every character
		memset(&bcb2, 0, sizeof(bcb2));
		bcb2.extra1 = console;
		bcb2.value1	= bcb->value1;
		bcb2.value2	= bcb->value2 + bcb->iter_count;
		iBuilder_iterate_N_to_N(conRow->chars, sizeof(SConChar), 0, console->nCols, &bcb2, (uptr)&iConsole_win_render__callbackCol);
		// Note:  If horizontal scrolling is ever added, the "0" and "console->nCols" can be adjusted here by console->nScrollX value

		// Continue iterating for every row
		return(true);
	}




//////////
//
// Called to render a single row onto the console->hdc at the indicated rect
//
//////
	// Uses bcb->extra1 for console, bcb->iter_ptr for conChar, bcb->value1 for x, bcb->value2 for y, and iterates using bcb->iter_count
	bool iConsole_win_render__callbackCol(SBuilderCallback* bcb)
	{
		SConsole*	console;
		SConChar*	conChar;


		// Grab the pointers
		console	= (SConsole*)bcb->extra1;
		conChar	= (SConChar*)bcb->iter_ptr;

		// Redraw the indicated character
		iConsole_win_renderSingleChar(console, bcb->value1 + bcb->iter_count, bcb->value2, conChar);
		console_os_xy_needs_repainted_atxy(console->nXText, console->nYText);

		// Continue iterating
		return(true);
	}




//////////
//
// Called to render a single character at the indicated coordinates
//
//////
	void iConsole_win_renderSingleChar(SConsole* console, s32 tnX, s32 tnY, SConChar* conChar)
	{
		s32					lnY, lnX, lnRow;
		f32					lfAlp, lfMalp, lfRed, lfGrn, lfBlu, lfBRed, lfBGrn, lfBBlu, lfFRed, lfFGrn, lfFBlu;
		f32*				pixelRow;
		SBgr*				lbgr;
		SConFont_fixed*		font_fixed;
		RECT				lrc;


		// Based on the font type, render appropriately
		if (conChar->nFont <= _CONSOLE_FONT__MAX_FIXED)
		{
			// A fixed-point font, copied pixel by pixel
			lfBRed	= (f32)conChar->backColor.red;
			lfBGrn	= (f32)conChar->backColor.grn;
			lfBBlu	= (f32)conChar->backColor.blu;
			lfFRed	= (f32)conChar->charColor.red;
			lfFGrn	= (f32)conChar->charColor.grn;
			lfFBlu	= (f32)conChar->charColor.blu;

			// Grab the font base
			font_fixed = (SConFont_fixed*)iBuilder_retrieveRecord(gsFontFixedRoot, sizeof(SConFont_fixed), conChar->nFont);

			// Iterate through every row of the character
			pixelRow = &font_fixed->fontBase_f32[(s32)conChar->c * console->nCharHeight * console->nCharWidth];
			for (lnY = 0, lnRow = (tnY * console->nCharHeight); lnY < console->nCharHeight; lnY++, lnRow++)
			{
				// Compute the offset into the pixel buffers
				lbgr = (SBgr*)(console->bmp->bd + ((console->bmp->bi.biHeight - lnRow - 1) * console->bmp->rowWidth) + (tnX * console->nCharWidth * 3));

				// Iterate through every column
				for (lnX = 0; lnX < console->nCharWidth; lnX++, pixelRow++, lbgr++)
				{
					// Compute the pixel
					lfAlp	= *pixelRow;
					lfMalp	= 1.0f - lfAlp;

					// Compute the color mixture
					lfRed	= (lfBRed * lfMalp) + (lfFRed * lfAlp);
					lfGrn	= (lfBGrn * lfMalp) + (lfFGrn * lfAlp);
					lfBlu	= (lfBBlu * lfMalp) + (lfFBlu * lfAlp);

					// Store the pixel
					// Range:       0  <=  color  <=   255
					lbgr->red = max(0, min((u32)lfRed, 255));
					lbgr->grn = max(0, min((u32)lfGrn, 255));
					lbgr->blu = max(0, min((u32)lfBlu, 255));
				}
			}

		} else {
			// System font
			iiConsole_selectFont(console, conChar->nFont);

			// Background color
			SetBkColor(console->bmp->hdc,	RGB(conChar->backColor.red, conChar->backColor.grn, conChar->backColor.blu));
			SetTextColor(console->bmp->hdc,	RGB(conChar->backColor.red, conChar->backColor.grn, conChar->backColor.blu));
			SetBkMode(console->bmp->hdc, OPAQUE);

			// Construct the rect
			SetRect(&lrc,	tnX * console->nCharWidth,
							tnY * console->nCharHeight,
							((tnX + 1) * console->nCharWidth)  - 1,
							((tnY + 1) * console->nCharHeight) - 1);

			// Draw this character
			DrawText(console->bmp->hdc, (s8*)&conChar->c, 1, &lrc, DT_LEFT | DT_SINGLELINE);
		}
	}




//////////
//
// Searches for the indicated console
//
//////
	SConsole* iConsole_win_find_byHwnd(HWND hwnd)
	{
		SBuilderCallback cb;


		// Prepare for iterative callback
		memset(&cb, 0, sizeof(cb));
		cb._iterateFunc	= (uptr)&iConsole_win_find_byHwnd__callback;
		cb.extra1 = hwnd;

		// Find it
		iBuilder_iterate(gsConsoleRoot, sizeof(SConsole), &cb);
		if (cb.extra2)
			return((SConsole*)cb.extra2);	// It's a valid pointer

		// Invalid
		return(NULL);
	}

	bool iConsole_win_find_byHwnd__callback(SBuilderCallback* cb)
	{
		SConsole* console;


		// Test the value
		console = (SConsole*)cb->iter_ptr;
		if (console->hwnd == (HWND)cb->extra1)
		{
			// Store the console
			cb->extra2 = console;
			return(false);		// Stop iterating
		}

		// Continue iterating
		return(true);
	}
;




//////////
//
// Called to obtain the status of the various keys
//
//////
	void iiConsole_win_getFlags_async(bool* tlCtrl, bool* tlAlt, bool* tlShift, bool* tlLeft, bool* tlMiddle, bool* tlRight, bool* tlCaps, bool* tlNum, bool* tlScroll, bool* tlAnyButton)
	{
		//////////
		// Grab each one asynchronously
		//////
			*tlCtrl			= ((GetAsyncKeyState(VK_CONTROL)	& 0x8000)	!= 0);
			*tlAlt			= (GetKeyState(VK_MENU)							< 0);
			*tlShift		= ((GetAsyncKeyState(VK_SHIFT)		& 0x8000)	!= 0);
			*tlLeft			= ((GetAsyncKeyState(VK_LBUTTON)	& 0x8000)	!= 0);
			*tlMiddle		= ((GetAsyncKeyState(VK_MBUTTON)	& 0x8000)	!= 0);
			*tlRight		= ((GetAsyncKeyState(VK_RBUTTON)	& 0x8000)	!= 0);
			*tlCaps			= (GetAsyncKeyState(VK_CAPITAL)		& 0x8000)	!= 0;
			*tlNum			= (GetAsyncKeyState(VK_NUMLOCK)		& 0x8000)	!= 0;
			*tlScroll		= (GetAsyncKeyState(VK_SCROLL)		& 0x8000)	!= 0;
			*tlAnyButton	= (*tlLeft || *tlMiddle || *tlRight);
	}




//////////
//
// Called to get the mouse settings before a callback
//
//////
	void iiConsole_get_mouseSettings(SConsole* console)
	{
		DWORD lnXY;


		// Set the parameters
		console->cb.console = console;
		iiConsole_win_getFlags_async(	&console->cb.lCtrl,			&console->cb.lAlt,				&console->cb.lShift,
										&console->cb.lLeftButton,	&console->cb.lMiddleButton,		&console->cb.lRightButton,
										&console->cb.lCaps,			&console->cb.lNum,				&console->cb.lScroll,
										&console->cb.lAnyButton);

		// If we're moving or resizing, also read the screen coordinate mouse data, and then return
		lnXY = GetMessagePos();
		console->cb.nX = lnXY & 0xffff;		// Low-order word
		console->cb.nY = lnXY >> 16;		// High-order word
	}




//////////
//
// Called to get the keyboard settings before a callback
//
//////
	void iiConsole_get_keyboardSettings(SConsole* console, WPARAM wParam, LPARAM lParam)
	{
		// Set the parameters
		console->cb.console = console;
		iiConsole_win_getFlags_async(	&console->cb.lCtrl,			&console->cb.lAlt,				&console->cb.lShift,
										&console->cb.lLeftButton,	&console->cb.lMiddleButton,		&console->cb.lRightButton,
										&console->cb.lCaps,			&console->cb.lNum,				&console->cb.lScroll,
										&console->cb.lAnyButton);

		// If we're moving or resizing, also read the screen coordinate mouse data, and then return
		console->cb.nX = console->nXText;		// Current X position
		console->cb.nY = console->nYText;		// Current Y position

		// Process the key
		console->cb.cChar	= (u8)MapVirtualKey(wParam, MAPVK_VK_TO_CHAR);
		console->cb.nOsKey	= wParam;
	}




//////////
//
// Called to handle GUI feedback
//
//////
	void iConsole_win_buttonup(SConsole* console, WPARAM wParam, LPARAM lParam)
	{
		// Grab the mouse settings
		iiConsole_get_mouseSettings(console);

		// Signal the callback
		if (console->cb._console_mouseUp)
			console->cb.console_mouseUp(&console->cb);
	}

	void iConsole_win_buttondown(SConsole* console, WPARAM wParam, LPARAM lParam)
	{
		// Grab the mouse settings
		iiConsole_get_mouseSettings(console);

		// Signal the callback
		if (console->cb._console_mouseDown)
			console->cb.console_mouseDown(&console->cb);
	}

	void iConsole_win_mousemove(SConsole* console, WPARAM wParam, LPARAM lParam)
	{
		// Grab the mouse settings
		iiConsole_get_mouseSettings(console);

		// Signal the callback
		if (console->cb._console_mouseMove)
			console->cb.console_mouseMove(&console->cb);
	}

	void iConsole_win_keyup(SConsole* console, WPARAM wParam, LPARAM lParam)
	{
		// Grab the keyboard settings
		iiConsole_get_keyboardSettings(console, wParam, lParam);

		// Signal the callback
		if (console->cb._console_keyUp)
			console->cb.console_keyUp(&console->cb);
	}

	void iConsole_win_keydown(SConsole* console, WPARAM wParam, LPARAM lParam)
	{
		s8			c;
		s32			lnI, lnCol;
		bool		llCtrl, llAlt, llShift, llLeft, llMiddle, llRight, llCaps, llNum, llScroll, llAnyButton, llNavigateKey;
		SConChar*	conChar;
		SConChar*	conCharLast;
		SConInput*	conInput;


		// If there is no cursor position yet, use the text position
		if (console->nXCursor < 0)
		{
			console->nXCursor = console->nXText;
			console->nYCursor = console->nYText;
		}

		// Grab the keyboard settings
		iiConsole_get_keyboardSettings(console, wParam, lParam);

		// Grab the keyboard and mouse flags
		iiConsole_win_getFlags_async(&llCtrl, &llAlt, &llShift, &llLeft, &llMiddle, &llRight, &llCaps, &llNum, &llScroll, &llAnyButton);

		// Signal the callback
		if (console->cb._console_keyDown)
			console->cb.console_keyDown(&console->cb);

		// Try and get the input
		conInput = iConsole_find_conInput_byCursorXY(console);
		if (conInput && conInput->cicb._onKeystroke)
		{
			// Signal keystroke
			conInput->cicb.onKeystroke((uptr)console, (uptr)conInput, wParam, llCtrl, llAlt, llShift, llLeft, llMiddle, llRight, llCaps, llNum, llScroll, llAnyButton);

			// If that's all they want, we're done
			if (conInput->cicb.lOnlySignalKeystrokes)
				return;
		}

		// Adjust the cursor position
		llNavigateKey = false;
		switch (wParam)
		{
			case VK_UP:
			case VK_DOWN:
			case VK_RIGHT:
			case VK_LEFT:
			case VK_HOME:
			case VK_END:
			case VK_PRIOR:
			case VK_NEXT:
			case VK_BACK:
			case VK_DELETE:
				llNavigateKey = true;
				break;

			case VK_TAB:
				// This is a navigate key if there's some input field to navigate to
				llNavigateKey = true;
				break;
		}
		// If we have a navigate key, continue
		if (llNavigateKey)
		{
			// Position the cursor where the text cursor is if need be
			// Make Y valid
			if (console->nYCursor < 0)
				console->nYCursor = console->nYText;

			// Make X valid
			if (console->nXCursor < 0)
				console->nXCursor = console->nXText;

			// Move based on the keystroke
			switch (wParam)
			{
				case VK_UP:
					if (console->nYCursor > 0)							--console->nYCursor;
					else												console->nYCursor = console->nRows - 1;
					break;
				case VK_DOWN:
					if (console->nYCursor < console->nRows - 1)			++console->nYCursor;
					else												console->nYCursor = 0;
					break;
				case VK_RIGHT:
					if (console->nXCursor < console->nCols - 1)			++console->nXCursor;
					else												console->nXCursor = 0;
					break;
				case VK_LEFT:
					if (console->nXCursor > 0)							--console->nXCursor;
					else												console->nXCursor = console->nCols - 1;
					break;
				case VK_HOME:
					// If in an input, move to the beginning of the input
					if (conInput)		iConsole_win_input_home(console, conInput);
					else				console->nXCursor = 0;
					break;
				case VK_END:
					// If in an input, move to the end of the input
					if (conInput)		iConsole_win_input_end(console, conInput);
					else				console->nXCursor = console->nCols - 1;		// Move to right-side of the screen
					break;
				case VK_PRIOR:
					console->nYCursor = 0;
					break;
				case VK_NEXT:
					console->nYCursor = console->nRows - 1;
					break;

				case VK_BACK:
					// If we're on an input field, backspace unless it's CTRL+Backspace, then delete all and move to leftmost X
					if (llCtrl)			iConsole_win_input_backspaceToStart(console, conInput);
					else				iConsole_win_input_backspace(console, conInput);
					break;

				case VK_DELETE:
					// If we're on an input field, delete right unless it's CTRL+Delete, then delete rest of the input
					if (llCtrl)			iConsole_win_input_deleteToEnd(console, conInput);
					else				iConsole_win_input_delete(console, conInput);
					break;

				case VK_TAB:
					if (llShift)		iConsole_win_input_prevField(console, conInput);		// Shift+tab (previous field)
					else				iConsole_win_input_nextField(console, conInput);		// Tab (next field)
					break;
			}

			// Turn the cursor on for the movement
			console->lCursorOn = true;

			// Redraw the input if it's valid
			if (conInput)
				iConsole_win_input_render(console, NULL, conInput, false);

		} else if ((c = (s8)MapVirtualKey(wParam, MAPVK_VK_TO_CHAR)) != 0) {
			// If they're in input mode, and they're in an input area, receive the keystroke
			if (console->nXCursor >= 0 && conInput && console->nXCursor < conInput->nX + conInput->nLength)
			{
				// We're on an input, determine where we are in it
				lnCol = console->nXCursor - conInput->nX;

				// Update it
				if (conInput->liveValue && conInput->liveValue->_data)
				{
					// Update the liveValue
					for (lnI = conInput->nLength - 1; lnI > lnCol; lnI--)
						conInput->liveValue->data_s8[lnI] = conInput->liveValue->data_s8[lnI - 1];
					
					// Store the new character
					if (lnCol < conInput->nLength)
						conInput->liveValue->data_s8[lnCol] = c;

				} else {
					// Update the screen only
					for (lnI = conInput->nLength - 1, conCharLast = NULL, conChar = NULL; lnI >= lnCol; lnI--)
					{
						// If we get it, continue
						if (iConsole_find_conChar_byXY(console, conInput->nX + lnI, conInput->nY, NULL, &conChar))
						{
							// Copy over
							if (conCharLast)
								conCharLast->c	= conChar->c;

							// Prepare for next iteration
							conCharLast = conChar;
						}
					}

					// Store the final character
					if (conChar)
						conChar->c = c;
				}

				// Signal the change
				conInput->cicb.lChanged = true;
				if (conInput && conInput->cicb._onChanged)
					conInput->cicb.onChanged((uptr)console, (uptr)conInput);

				// Simulate a right keystroke
				iConsole_win_keydown(console, VK_RIGHT, lParam);
			}
		}

		// Redraw the screen
		InvalidateRect(console->hwnd, NULL, FALSE);
	}




//////////
//
// Distributes unique WM_APP ids for various internal uses
//
//////
	u32 iGetNextWmApp(void)
	{
		return(gnNextWmAppNum++);
	}




//////////
//
// Called to read messages
//
//////
	void iConsole_win_readMessages(void)
	{
		MSG msg;


		// Iterate until there aren't any more console windows
		while (iConsole_anyValidConsoles())
		{
			// Process messages
			while (GetMessage(&msg, NULL, NULL, NULL))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			// When a window closes, it exits the loop
		}
	}




//////////
//
// Keystroke movement in the window
//
//////
	bool iConsole_win_input_home(SConsole* console, SConInput* conInput)
	{
		// Make sure our environment is sane
		if (conInput)
		{
			// Move to the start of the input
			console->nXCursor = conInput->nX;

			// Indicate success
			return(true);
		}

		// If we get here, not on an input
		return(false);
	}




//////////
//
// Moves to the end of the input
//
//////
	bool iConsole_win_input_end(SConsole* console, SConInput* conInput)
	{
		s32			lnI;
		SConChar*	conChar;


		// Make sure our environment is sane
		if (conInput)
		{
			// Move to the last populated value in the input
			if (conInput->liveValue && conInput->liveValue->_data)
			{
				// There's a datum, scan it
				for (lnI = conInput->liveValue->length - 1; lnI >= 0; lnI--)
				{
					// Is this a non-space?
					if (conInput->liveValue->data[lnI] != 32)
					{
						// We've found the first non-space
						console->nXCursor = min(conInput->nX + lnI + 1, console->nCols - 1);
						// Note:  If we're on the last position, this will place us beyond the max

						// Success
						break;
					}
				}

				// If we get here, we're all the way at the beginning
				if (lnI < 0)
					console->nXCursor = conInput->nX;

			} else {
				// Just read the screen
				for (lnI = conInput->nLength - 1; lnI > 0; lnI--)
				{
					// Is this a non-space?
					if (iConsole_find_conChar_byXY(console, conInput->nX + lnI, conInput->nY, NULL, &conChar))
					{
						if (conChar->c != 32)
						{
							// We've found the first non-space
							console->nXCursor = min(conInput->nX + lnI + 1, console->nCols - 1);
							// Note:  If we're on the last position, this will place us beyond the max

							// Success
							break;
						}
					}
				}

				// If we get here, we're all the way at the beginning
				if (lnI < 0)
				{
					// Grab the character
					if (conChar->c != 32)		console->nXCursor = conInput->nX;
					else						console->nXCursor = conInput->nX + 1;
				}

			}

			// Indicate success
			return(true);
		}

		// If we get here, not on an input
		return(false);
	}




//////////
//
// Backspace once on the input
//
//////
	bool iConsole_win_input_backspace(SConsole* console, SConInput* conInput)
	{
		s32			lnCol;
		SConChar*	conChar;
		SConChar*	conCharLast;


		// See if we're on an input
		if (conInput)
		{
			// We're on an input
			lnCol = console->nXCursor - conInput->nX;
			if (lnCol > 0)
			{
				// We have room to backspace
				if (conInput->liveValue && conInput->liveValue->_data)
				{
					// They have a datum to update
					for ( ; lnCol < conInput->nLength; lnCol++)
						conInput->liveValue->data[lnCol - 1] = conInput->liveValue->data[lnCol];

					// Insert a space at the end
					conInput->liveValue->data[lnCol - 1] = 32;

				} else if (lnCol > 0 && lnCol < conInput->nLength) {
					// Just update the screen
					for (conCharLast = NULL, conChar = NULL; lnCol <= conInput->nLength; lnCol++)
					{
						// If we get it, continue
						if (iConsole_find_conChar_byXY(console, conInput->nX + lnCol - 1, conInput->nY, NULL, &conChar))
						{
							// Copy over
							if (conCharLast)
								conCharLast->c	= conChar->c;

							// Prepare for next iteration
							conCharLast = conChar;
						}
					}

					// The last character should be a space
					conChar->c = 32;

				} else {
					// We're on the last character
					if (iConsole_find_conChar_byXY(console, conInput->nX + conInput->nLength - 1, conInput->nY, NULL, &conChar))
						conChar->c = 32;
				}
			}

			// Signal the change
			conInput->cicb.lChanged = true;
			if (conInput && conInput->cicb._onChanged)
				conInput->cicb.onChanged((uptr)console, (uptr)conInput);

			// Move left one unless we're at the beginning of the input
			if (console->nXCursor > 0 && console->nXCursor > conInput->nX)
				iConsole_win_keydown(console, VK_LEFT, 0);

			// If we get here, we had an input at this point
			return(true);

		} else {
			// They're outside of an input
			iConsole_win_keydown(console, VK_LEFT, 0);
		}

		// If we get here, not on an input
		return(false);
	}




//////////
//
// Backspaces to the beginning of the field
//
//////
	bool iConsole_win_input_backspaceToStart(SConsole* console, SConInput* conInput)
	{
		s32			lnCol;
		SConChar*	conChar;


		// See if we're on an input
		if (conInput)
		{
			// We're on an input
			if (conInput->liveValue && conInput->liveValue->_data)
			{
				// They have a datum to update
				iDatum_setAll(conInput->liveValue, 32);

			} else {
				// Just update the screen
				for (lnCol = conInput->nX; lnCol < conInput->nX + conInput->nLength; lnCol++)
				{
					// If we get the input, reset it
					if (iConsole_find_conChar_byXY(console, lnCol, conInput->nY, NULL, &conChar))
						conChar->c = 32;
				}
			}

			// Backup to the beginning
			console->nXCursor = conInput->nX;

			// Signal the change
			conInput->cicb.lChanged = true;
			if (conInput && conInput->cicb._onChanged)
				conInput->cicb.onChanged((uptr)console, (uptr)conInput);

			// If we get here, we had an input at this point
			return(true);
		}
		// If we get here, not on an input
		return(false);
	}




//////////
//
// Deletes the character at the cursor
//
//////
	bool iConsole_win_input_delete(SConsole* console, SConInput* conInput)
	{
		s32			lnCol;
		SConChar*	conChar;
		SConChar*	conCharLast;


		// See if we're on an input
		if (conInput)
		{
			// We're on an input
			lnCol = console->nXCursor - conInput->nX;
			if (conInput->liveValue && conInput->liveValue->_data)
			{
				// They have a datum to update
				for ( ; lnCol < conInput->nLength - 1; lnCol++)
					conInput->liveValue->data[lnCol] = conInput->liveValue->data[lnCol + 1];

				// Insert a space at the end
				conInput->liveValue->data[lnCol] = 32;

			} else if (lnCol < conInput->nLength) {
				// Just update the screen
				for (conCharLast = NULL, conChar = NULL; lnCol < conInput->nLength; lnCol++)
				{
					// If we get it, continue
					if (iConsole_find_conChar_byXY(console, conInput->nX + lnCol, conInput->nY, NULL, &conChar))
					{
						// Copy over
						if (conCharLast)
							conCharLast->c	= conChar->c;

						// Prepare for next iteration
						conCharLast = conChar;
					}
				}

				// The last character should be a space
				conChar->c = 32;

			} else {
				// We're on the last character
				if (iConsole_find_conChar_byXY(console, conInput->nX + conInput->nLength - 1, conInput->nY, NULL, &conChar))
					conChar->c = 32;
			}

			// Signal the change
			conInput->cicb.lChanged = true;
			if (conInput && conInput->cicb._onChanged)
				conInput->cicb.onChanged((uptr)console, (uptr)conInput);

			// If we get here, we had an input at this point
			return(true);

		} else {
			// They're outside of an input
			iConsole_win_keydown(console, VK_LEFT, 0);
		}

		// If we get here, not on an input
		return(false);
	}




//////////
//
// Delete everything to the end of the line
//
//////
	bool iConsole_win_input_deleteToEnd(SConsole* console, SConInput* conInput)
	{
		s32			lnCol;
		SConChar*	conChar;


		// See if we're on an input
		if (conInput)
		{
			// We're on an input
			lnCol = console->nXCursor - conInput->nX;
			if (conInput->liveValue && conInput->liveValue->_data)
			{
				// They have a datum to update
				for ( ; lnCol < conInput->nLength; lnCol++)
					conInput->liveValue->data[lnCol] = 32;

			} else if (lnCol < conInput->nLength) {
				// Just update the screen
				for ( ; lnCol < conInput->nLength; lnCol++)
				{
					// If we get it, continue
					if (iConsole_find_conChar_byXY(console, conInput->nX + lnCol, conInput->nY, NULL, &conChar))
						conChar->c = 32;	// Set
				}

			} else {
				// We're on the last character
				if (iConsole_find_conChar_byXY(console, conInput->nX + conInput->nLength - 1, conInput->nY, NULL, &conChar))
					conChar->c = 32;
			}

			// Signal the change
			conInput->cicb.lChanged = true;
			if (conInput && conInput->cicb._onChanged)
				conInput->cicb.onChanged((uptr)console, (uptr)conInput);

			// If we get here, we had an input at this point
			return(true);

		} else {
			// They're outside of an input
			iConsole_win_keydown(console, VK_LEFT, 0);
		}

		// If we get here, not on an input
		return(false);
	}




//////////
//
// Called to 
//
//////
	bool iConsole_win_input_prevField(SConsole* console, SConInput* conInput)
	{
		s32			lnY, lnX, lnYStart, lnXStart, lnYStop, lnPass;
		SConInput*	conInputCandidate;


		// Iterate from where we are down, and then begin again at the top if need be
		if (conInput)
		{
			lnYStart	= conInput->nY;
			lnYStop		= 0;
			lnXStart	= conInput->nX;

		} else {
			// Not on a field, so we're searching for the first one
			lnYStart	= console->nYCursor;
			lnYStop		= 0;
			lnXStart	= console->nXCursor;
		}

		// Iterate down
		for (lnPass = 0; lnPass < 2; lnPass++)
		{
			//////////
			// Search every row down
			//////
				for (lnY = lnYStart; lnY >= lnYStop; lnY--, lnXStart = console->nCols - 1)
				{
					// Iterate across every row
					for (lnX = lnXStart; lnX >= 0; lnX--)
					{
						// Search for an input at these coordinates
						conInputCandidate = iConsole_find_conInput_byXY(console, lnX, lnY);
						if (conInputCandidate && conInputCandidate != conInput)
						{
							// We found it
							console->nXCursor	= conInputCandidate->nX;
							console->nYCursor	= conInputCandidate->nY;

							// Signal the onLostFocus
							if (conInput && conInput->cicb._onLostFocus)
								conInput->cicb.onLostFocus((uptr)console, (uptr)conInput);

							// Signal the onGotFocus
							if (conInputCandidate->cicb._onGotFocus)
								conInputCandidate->cicb.onGotFocus((uptr)console, (uptr)conInputCandidate);

							// Go ahead and keyboard an end key as well
							iConsole_win_keydown(console, VK_END, NULL);

							// Indicate success
							return(true);
						}
					}
				}


			//////////
			// If we didn't find it on this pass
			//////
				if (lnPass == 0)
				{
					// We didn't find it from where we were to the end of the screen, so start over at the top
					lnYStart = console->nRows - 1;
					if (conInput)		lnYStop = conInput->nY - 1;
					else				lnYStop = console->nYCursor - 1;

				} else {
					// It wasn't found anywhere, so just move to the start of the original input
					if (conInput)
					{
						console->nXCursor	= conInput->nX;
						console->nYCursor	= conInput->nY;

						// Indicate success
						return(true);
					}
				}

		}

		// If we get here, nothing found
		return(false);
	}

	bool iConsole_win_input_nextField(SConsole* console, SConInput* conInput)
	{
		s32			lnY, lnX, lnYStart, lnXStart, lnYStop, lnPass;
		SConInput*	conInputCandidate;


		// Iterate from where we are down, and then begin again at the top if need be
		if (conInput)
		{
			lnYStart	= conInput->nY;
			lnYStop		= console->nRows;
			lnXStart	= conInput->nX + conInput->nLength;

		} else {
			// Not on a field, so we're searching for the first one
			lnYStart	= console->nYCursor;
			lnYStop		= console->nRows;
			lnXStart	= console->nXCursor;
		}

		// Iterate down
		for (lnPass = 0; lnPass < 2; lnPass++)
		{
			//////////
			// Search every row down
			//////
				for (lnY = lnYStart; lnY < lnYStop; lnY++, lnXStart = 0)
				{
					// Iterate across every row
					for (lnX = lnXStart; lnX < console->nCols; lnX++)
					{
						// Search for an input at these coordinates
						conInputCandidate = iConsole_find_conInput_byXY(console, lnX, lnY);
						if (conInputCandidate && conInputCandidate != conInput)
						{
							// We found it
							console->nXCursor	= conInputCandidate->nX;
							console->nYCursor	= conInputCandidate->nY;

							// Signal the onLostFocus
							if (conInput && conInput->cicb._onLostFocus)
								conInput->cicb.onLostFocus((uptr)console, (uptr)conInput);

							// Signal the onGotFocus
							if (conInputCandidate->cicb._onGotFocus)
								conInputCandidate->cicb.onGotFocus((uptr)console, (uptr)conInputCandidate);

							// Go ahead and keyboard an end key as well
							iConsole_win_keydown(console, VK_END, NULL);

							// Indicate success
							return(true);
						}
					}
				}


			//////////
			// If we didn't find it on this pass
			//////
				if (lnPass == 0)
				{
					// We didn't find it from where we were to the end of the screen, so start over at the top
					lnYStart = 0;
					if (conInput)		lnYStop = conInput->nY + 1;
					else				lnYStop = console->nYCursor + 1;

				} else {
					// It wasn't found anywhere, so just move to the start of the original input
					if (conInput)
					{
						console->nXCursor	= conInput->nX;
						console->nYCursor	= conInput->nY;

						// Indicate success
						return(true);
					}
				}

		}

		// If we get here, nothing found
		return(false);
	}




//////////
//
// Render the indicated input area
//
//////
	bool iConsole_win_input_render(SConsole* console, HDC hdcBorder, SConInput* conInput, bool tlDrawBorder)
	{
		s32				lnI;
		bool			llHighlighted;
		RECT			lrc;
		SConRow*		conRow;
		SConChar*		conChar;
		HBRUSH			hbrBackColor, hbrTextColor, hbrBrightBlue;


		// Rectangle area
		SetRect(&lrc,	conInput->nX * console->nCharWidth  - 1,
						conInput->nY * console->nCharHeight - 1,
						(conInput->nX + conInput->nLength)	* console->nCharWidth  + 1,
						(conInput->nY + 1)					* console->nCharHeight + 1);

		// Frame it if we're in the input area
		llHighlighted = (console->nYCursor == conInput->nY && between(console->nXCursor, conInput->nX, conInput->nX + conInput->nLength - 1));

		// bcb->flag1 is set if they only want to invalidate the rect, otherwise it redraws everything
		if (tlDrawBorder && (!conInput->cicb.lSuppressBorder || conInput->cicb.lInnerBorder))
		{
			// Redraw everything
			hbrTextColor	= CreateSolidBrush(RGB(conInput->charColor.red, conInput->charColor.grn, conInput->charColor.blu));
			hbrBrightBlue	= CreateSolidBrush(RGB(112,164,255));

			// Single in the back color
			if (conInput->cicb.lInnerBorder)
			{
				// Inner border
				hbrBackColor = CreateSolidBrush(RGB(conInput->cicb.innerBorderColor.red, conInput->cicb.innerBorderColor.grn, conInput->cicb.innerBorderColor.blu));
				--lrc.bottom;
				FrameRect(hdcBorder, &lrc, hbrBackColor);
				++lrc.bottom;

			} else {
				// Outer border
				hbrBackColor = CreateSolidBrush(RGB(conInput->backColor.red, conInput->backColor.grn, conInput->backColor.blu));
				FrameRect(hdcBorder, &lrc, hbrBackColor);
			}

			if (!conInput->cicb.lSuppressBorder)
			{
				// Single in the text color
				InflateRect(&lrc, 1, 1);
				FrameRect(hdcBorder, &lrc, hbrTextColor);

				// If they're on this field, continue another three in brighter blue
				if (llHighlighted)
				{
					InflateRect(&lrc, 1, 1);
					for (lnI = 0; lnI < 3; lnI++, InflateRect(&lrc, 1, 1))
						FrameRect(hdcBorder, &lrc, hbrBrightBlue);
				}
			}

			// Clean house
			DeleteObject((HGDIOBJ)hbrBackColor);
			DeleteObject((HGDIOBJ)hbrBrightBlue);
			DeleteObject((HGDIOBJ)hbrTextColor);
		}

		// Make sure the colors are correct
		for (lnI = 0; lnI < conInput->nLength; lnI++)
		{
			// Store the character from the liveValue (if present) and the background color info
			if (iConsole_find_conChar_byXY(console, conInput->nX + lnI, conInput->nY, &conRow, &conChar))
			{
				// Store the character
				if (conInput->liveValue && conInput->liveValue->_data)
					conChar->c = conInput->liveValue->data[lnI];

				// Store the coloring
				conChar->nFont				= conInput->nFont;
				if (conInput->cicb.lChanged && conInput->cicb.lVisualize_onChange)
				{
					// Colorize on change
					conChar->charColor.color	= conInput->cicb.charColor_changed.color;
					conChar->backColor.color	= conInput->cicb.backColor_changed.color;

				} else {
					// Standard coloring
					conChar->charColor.color	= conInput->charColor.color;
					conChar->backColor.color	= conInput->backColor.color;
				}

				// Redraw the character
				iConsole_win_renderSingleChar(console, conInput->nX + lnI, conInput->nY, conChar);
			}
		}

		// Invalidate
		InvalidateRect(console->hwnd, &lrc, FALSE);

		// Continue iterating
		return(true);
	}




//////////
//
// Windows callback, delivering messages
//
//////
	LRESULT CALLBACK iConsole_wndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		s32					lnI, lnResult;
		PAINTSTRUCT			ps;
		union {
			void*			_hdc;
			HDC				hdc;
		};
		HBRUSH				hbr;
		RECT				lrc;
		SConsole*			console;
		SBuilderCallback	bcb;


		// Locate the associated console
		if ((console = iConsole_win_find_byHwnd(hwnd)))
		{
			// Based on the message
			switch (message)
			{
				case WM_TIMER:
					// Toggle 
					if (wParam == console->cursorTimerId)
					{
						// Toggle the console's local cursor
						console->lCursorOn = !console->lCursorOn;

						// Repaint the cursor area
						if (console->nXCursor >= 0)
						{
							// Use the cursor X,Y
							SetRect(&lrc,	console->nXCursor * console->nCharWidth,
											console->nYCursor * console->nCharHeight,
											((console->nXCursor + 1) * console->nCharWidth),
											((console->nYCursor + 1) * console->nCharHeight));

						} else {
							// Use the text X,Y
							SetRect(&lrc,	console->nXText * console->nCharWidth,
											console->nYText * console->nCharHeight,
											((console->nXText + 1) * console->nCharWidth),
											((console->nYText + 1) * console->nCharHeight));
						}

						// Invalidate that rectangle to update the cursor
						InvalidateRect(hwnd, &lrc, false);

						// Invalidate any input fields
						if (gsInputRoot && gsInputRoot->buffer && gsInputRoot->populatedLength)
						{
							memset(&bcb, 0, sizeof(bcb));
							bcb.extra1	= console;
							bcb.flag1	= true;		// Invalidate only
							iBuilder_iterate(gsInputRoot, sizeof(SConInput), &bcb, (uptr)&iConsole_wndProc__inputBoxes__callback);
						}
						break;
					}
					break;

				case WM_LBUTTONDOWN:
					// Left button down
					iConsole_win_buttondown(console, wParam, lParam);
					break;

				case WM_LBUTTONUP:
					// Left button up
					iConsole_win_buttonup(console, wParam, lParam);
					break;

				case WM_MOUSEMOVE:
					// Move
					iConsole_win_mousemove(console, wParam, lParam);
					break;

				case WM_KEYDOWN:
					// Key depressed
					iConsole_win_keydown(console, wParam, lParam);
					break;

				case WM_KEYUP:
					// Key released
					iConsole_win_keyup(console, wParam, lParam);
					break;

				case WM_ERASEBKGND:
					// Ignore it
					return 1;
					break;

				case WM_NCPAINT:
					// Draw normally
					lnResult = DefWindowProc(hwnd, message, wParam, lParam);

					// Overlay with a white border
					if (console->lShowBorder)
					{
						hdc = GetWindowDC(hwnd);
						GetWindowRect(hwnd, &lrc);
						lrc.right	-= lrc.left;
						lrc.bottom	-= lrc.top;
						lrc.left	= 0;
						lrc.top		= 0;
						hbr			= CreateSolidBrush(RGB(console->borderColor.red, console->borderColor.grn, console->borderColor.blu));
						for (lnI = 0; lnI < 4; lnI++, InflateRect(&lrc, -1, -1))
							FrameRect(hdc, &lrc, hbr);

						DeleteObject((HGDIOBJ)hbr);
						ReleaseDC(hwnd, hdc);
					}
					return(lnResult);

				case WM_PAINT:
					// Internally we maintain the drawn state of the window in a separate buffer,
					// and simply BitBlt it back out to the main window as is needed by the OS
					hdc = BeginPaint(hwnd, &ps);

					// Copy over the base image
					BitBlt(hdc, 0, 0, console->nWidth, console->nHeight, console->bmp->hdc, 0, 0,SRCCOPY);

					// Highlight any input fields
					if (gsInputRoot && gsInputRoot->buffer && gsInputRoot->populatedLength)
					{
						memset(&bcb, 0, sizeof(bcb));
						bcb.extra1 = console;
						bcb.extra2 = _hdc;
						iBuilder_iterate(gsInputRoot, sizeof(SConInput), &bcb, (uptr)&iConsole_wndProc__inputBoxes__callback);
					}

					// Overlay the cursor if need be
					if (glCursorOn && GetForegroundWindow() == hwnd && console->lCursorOn)
					{
						// Highlight the cursor
						if (console->nXCursor >= 0)
						{
							// Use the cursor X,Y
							SetRect(&lrc,	console->nXCursor * console->nCharWidth,
											console->nYCursor * console->nCharHeight,
											((console->nXCursor + 1) * console->nCharWidth),
											((console->nYCursor + 1) * console->nCharHeight));

						} else {
							// Use the text X,Y
							SetRect(&lrc,	console->nXText * console->nCharWidth,
											console->nYText * console->nCharHeight,
											((console->nXText + 1) * console->nCharWidth),
											((console->nYText + 1) * console->nCharHeight));
						}

						// Just draw a cursor there
						InvertRect(hdc, &lrc);
					}
					EndPaint(hwnd, &ps);
					break;

				case WM_DESTROY:
					PostQuitMessage(0);
					break;

				default:
					return DefWindowProc(hwnd, message, wParam, lParam);
			}
		}

		// Indicate the message was not processed
		return DefWindowProc(hwnd, message, wParam, lParam);
	}

	bool iConsole_wndProc__inputBoxes__callback(SBuilderCallback* bcb)
	{
		SConsole*		console;
		SConInput*		conInput;
		union {
			void*		_hdc;
			HDC			hdc;
		};


		// Grab our pointers
		console		= (SConsole*)bcb->extra1;
		_hdc		= bcb->extra2;
		conInput	= (SConInput*)bcb->iter_ptr;

		// Redraw characters and overlay border
		return(iConsole_win_input_render(console, hdc, conInput, true));
	}
