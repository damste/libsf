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
	int console_win_unit_test(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
	{
		MSG msg;


		// Initialize
		ghInstance = hInstance;
		MyRegisterClass();

		// Main message loop:
		while (GetMessage(&msg, NULL, 0, 0))
			DispatchMessage(&msg);

		return (int) msg.wParam;
	}




//////////
//
// Called to make sure our Windows prerequisites have been setup
//
//////
	bool console_win_validateInitialization(void)
	{
		return(false);
	}




//////////
//
// Called to create a window
//
//////
	s32 console_win_create_window(SConsole* console)
	{
		s32		lnLength;
		s8		buffer[_MAX_FNAME];


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
		// Prepare a window
		//////
			console->nWidth	= max(320, console->nWidth);
			console->nHeight	= max(200, console->nHeight);

			// Assemble the title
			lnLength = min(_MAX_FNAME - 1, console->title.length);
			memcpy(buffer, console->title.data_cs8, lnLength);
			buffer[lnLength] = 0;

			// Create the window
			console->hwnd = CreateWindow(cgc_consoleClass,	buffer, WS_OVERLAPPEDWINDOW, 
															console->nLeft, console->nTop, 
															console->nWidth, console->nHeight, 
															NULL, NULL, ghInstance, NULL);

		// If it failed, we're done
		if (!console->hwnd)
			return(_CONSOLE_ERROR__CANNOT_CREATE_WINDOW);

		// Display if need be
		if (console->lVisible)
		{
			ShowWindow(console->hwnd, SW_SHOW);
			UpdateWindow(console->hwnd);
		}

		// Indicate success
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
	void console_win_fontSetup(SConsole* console, SConFont* font)
	{
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




//////////
//
// Register the console window class with Windows
//
//////
	ATOM MyRegisterClass(void)
	{
		WNDCLASSEX wcex;

		wcex.cbSize			= sizeof(WNDCLASSEX);
		wcex.style			= CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc	= console_wndProc;
		wcex.cbClsExtra		= 0;
		wcex.cbWndExtra		= 0;
		wcex.hInstance		= ghInstance;
		wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
		wcex.lpszClassName	= cgc_consoleClass;

		return RegisterClassEx(&wcex);
	}




//////////
//
// Render the console
//
//////
	void iConsole_win_render(SConsole* console)
	{
		s32			lnI, lnRow;
		SConRow*	row;
		RECT		lrc;


		// Create the background brush if need be
		if (!console->hbrBackground)
			console->hbrBackground = CreateSolidBrush(RGB(console->backColor.red, console->backColor.grn, console->backColor.blu));

		// Full color background
		FillRect(console->hdc, &console->rc, console->hbrBackground);

		// Redraw any lines which are visible
		SetRect(&lrc, 0, 0, console->rc.right, console->nCharHeight);
		for (lnI = console->nTopRow, lnRow = 0; lnRow < console->nHeight && lnI < (s32)console->scrollBuffer->populatedLength; lnI += sizeof(SConRow), lnRow++)
		{
			// Grab the row data
			row = (SConRow*)console->scrollBuffer->buffer + (lnI * sizeof(SConRow));

			// Draw the row
			iConsole_win_render_singleRow(console, &lrc, row);
		}


		// All done
		InvalidateRect(console->hwnd, NULL, false);
	}




//////////
//
// Called to render a single row onto the console->hdc at the indicated rect
//
//////
	void iConsole_win_render_singleRow(SConsole* console, RECT* rc, SConRow* row)
	{
		s32			lnCol, lnLastFont;
		SConChar*	thisChar;
		SBgra		lastBackColor, lastForeColor;
		RECT		lrc;


		// Note:  These are set on the first iteration, but are also set here to remove compiler warning
		lastBackColor.color = 0;
		lastForeColor.color = 0;

		// Iterate drawing it character-by-character
		CopyRect(&lrc, rc);
		for (lnCol = 0, lnLastFont = 0; lnCol < console->nWidth; lnCol++, OffsetRect(&lrc, console->nCharWidth, 0), thisChar++)
		{

			//////////
			// Grab this character
			//////
				thisChar = (SConChar*)row->chars->buffer + (lnCol * sizeof(SConChar));


			//////////
			// Update font
			//////
				if (lnLastFont != thisChar->nFont)
				{
					// Set the font
					lnLastFont = thisChar->nFont;
					iiConsole_selectFont(console, thisChar->nFont);
				}


			//////////
			// Update colors
			//////
				if (lastBackColor.color != thisChar->backColor.color || lnCol == 0)
				{
					// Background color
					SetBkColor(console->hdc, RGB(thisChar->backColor.red, thisChar->backColor.grn, thisChar->backColor.blu));
					lastBackColor.color = thisChar->backColor.color;
				}

				if (lastForeColor.color != thisChar->foreColor.color || lnCol == 0)
				{
					// Text color
					SetTextColor(console->hdc, RGB(thisChar->foreColor.red, thisChar->foreColor.grn, thisChar->foreColor.blu));
					lastForeColor.color = thisChar->foreColor.color;
				}


			//////////
			// Draw this character
			//////
				DrawText(console->hdc, (s8*)&thisChar->c, 1, &lrc, DT_LEFT | DT_SINGLELINE);

		}
	}




//////////
//
// Windows callback, delivering messages
//
//////
	LRESULT CALLBACK console_wndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		int				wmId, wmEvent;
		PAINTSTRUCT		ps;
		HDC				hdc;
		SConsole*		console;


		// Locate the associated console
		if ((console = iConsole_win_find_byHwnd(hwnd)))
		{
			// Based on the message
			switch (message)
			{
				case WM_COMMAND:
					wmId    = LOWORD(wParam);
					wmEvent = HIWORD(wParam);
					break;

				case WM_ERASEBKGND:
					// Ignore it
					return 1;
					break;

				case WM_PAINT:
					hdc = BeginPaint(hwnd, &ps);

					// Internally we maintain the drawn state of the window in a separate buffer, and simply BitBlt it back out to the main window as is needed by the OS
					BitBlt(	hdc, 0, 0,	console->rc.right - console->rc.left,	/* width */
										console->rc.bottom - console->rc.top,	/* height */
							console->hdc, 0, 0,
							SRCCOPY	);

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
		return 0;
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
		console = (SConsole*)cb->buffer_ptr;
		if (console->hwnd == (HWND)cb->extra1)
		{
			// Store the console
			cb->extra2 = console;

			// Indicate we've found it
			return(false);
		}

		// Continue sending more to test
		return(true);
	}
