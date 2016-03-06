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
		s32				lnI, lnJ, lnAscii;
		uptr			lnCon1;
		SDatum			title;
		SConCallback	ccb;
		SDatum			props, test;
		s8				buffer[_MAX_FNAME];


		//////////
		// Store instance
		//////
			ghInstance = hInstance;


		//////////
		// Allocate three consoles
		//////
			title.data_cs8	= "Console 80x43";
			title.length	= strlen(title.data_cs8);
			sprintf(buffer, "backColor=0\nforeColor=%d", rgb(0,255,0));
			props.data_cs8	= &buffer[0];
			props.length	= strlen(buffer);
			lnCon1 = console_allocate(&title, -1, -1, 20, 20, &ccb);
			console_setProperties(lnCon1, &props);
			console_show(lnCon1, true);


		//////////
		// Draw some text
		//////
			sprintf(buffer, "backColor=%d\nforeColor=%d", rgb(0,255,0), rgb(0,0,0));
			props.length	= strlen(buffer);
			console_setProperties(lnCon1, &props);
			test.data_cs8	= "Test1";
			test.length		= strlen(test.data_cs8);
			console_goto_xy(lnCon1, 2, 5);
			console_print(lnCon1, &test);

			sprintf(buffer, "backColor=%d\nforeColor=%d", rgb(255,255,255), rgb(0,0,0));
			props.length	= strlen(buffer);
			console_setProperties(lnCon1, &props);
			test.data_cs8	= "Test2";
			test.length		= strlen(test.data_cs8);
			console_goto_xy(lnCon1, 2, 10);
			console_print(lnCon1, &test);


		// Read messages
		iConsole_win_readMessages();

		// Indicate success
		return(_CONSOLE_ERROR__NO_ERROR);
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
			console->nX			= 0;												// Cursor position @ col = 0
			console->nY			= 0;												// Cursor position @ row = 0


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
		SetRect(&lrc,	console->nX * console->nCharWidth,
						console->nY * console->nCharHeight,
						((console->nX + 1) * console->nCharWidth)  - 1,
						((console->nY + 1) * console->nCharHeight) - 1);
		
		// Signal the rectangle needs redrawn
		InvalidateRect(console->hwnd, &lrc, false);
	}




//////////
//
// Called to store the indicated character into the console buffer
//
//////
	void console_win_store_character(SConsole* console, char c)
	{
		SConRow*			conRow;
		SConChar*			conChar;
		SBuilderCallback	bcb;


		// Grab the row
		conChar	= NULL;
		conRow	= (SConRow*)iBuilder_retrieveRecord(console->scrollBuffer, sizeof(SConRow), console->nY);
		if (conRow)
		{
			// Grab the character
			conChar = (SConChar*)iBuilder_retrieveRecord(conRow->chars, sizeof(SConChar), console->nX);
			if (conChar)
			{

				//////////
				// Store character and attributes
				//////
					conChar->c					= c;
					conChar->backColor.color	= console->backColor.color;
					conChar->charColor.color	= console->charColor.color;
					conChar->nFont				= console->nCharFont;


				//////////
				// Redraw
				//////
					// Create a simulated builder callback
					memset(&bcb, 0, sizeof(bcb));
					bcb.extra1		= console;
					bcb.iter_ptr	= conChar;

					// Render the one character
					iConsole_win_render__callbackCol(&bcb);

			}
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
				font_fixed = (SConFont_fixed*)iBuilder_allocateBytes(gsFontFixedRoot, sizeof(SConFont_fixed) * (_CONSOLE_FONT_16x32 + 1));
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
		s32			lnI, lnX, lnY, lnRow, lnCol, lnWidthIn, lnHeightIn, lnWidthOut, lnHeightOut, lnPixelNum;
		SBitmap*	bmpIn;
		SBitmap*	bmpOut;
		RECT		lrc;
		SBgr*		lrgb;


		// Make sure our parameters are in a sane range
		font_fixed->nFontX		= 8;
		font_fixed->nFontY		= ((font_fixed->nFontY == 6 || font_fixed->nFontY == 8 || font_fixed->nFontY == 14 || font_fixed->nFontY == 16) ? font_fixed->nFontY : 16);
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
				for (lnI = 0, lnRow = font_fixed->nFontY, lcThisCharacter = 0; lnI < 256; lnI++, lcThisCharacter++, lnRow = (((lnI / 16) + 1) * font_fixed->nFontY))
				{
					// Offset for this character into font_fixed->fontBase_original[]
					lnPixelNum = lnI * font_fixed->nFontY;

					// Draw the character
					for (lnY = 0; lnY < font_fixed->nFontY; lnY++, lnPixelNum++)
					{
						// Prepare for drawing bits across this row
						lrgb = (SBgr*)(bmpIn->bd + ((bmpIn->bi.biHeight - lnRow - lnY) * bmpIn->rowWidth) + (((lnI % 16) + 1) * font_fixed->nFontX * 3));

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
//iBmp_saveToDisk(bmpIn,  "c:\\temp\\in.bmp");
				iBmp_scale(bmpOut, bmpIn);
//iBmp_saveToDisk(bmpOut, "c:\\temp\\out.bmp");

				// Delete the input
				iBmp_delete(&bmpIn, true, true);


			//////////
			// Extract the scaled bits back out
			//////
				// Iterate character-by-character
				for (lnI = 0, lnPixelNum = 0; lnI < 256; lnI++)
				{
					// Iterate for every vertical pixel
					for (lnY = 0, lnRow = ((lnI / 16) + 1) * font_fixed->nCharHeight, lnCol = (lnI % 16); lnY < font_fixed->nCharHeight; lnY++)
					{
						// Grab pointer to the start of this row
						lrgb = (SBgr*)(bmpOut->bd + ((bmpOut->bi.biHeight - lnRow - lnY) * bmpOut->rowWidth) + ((lnCol + 1) * font_fixed->nCharWidth * 3));

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
	void iConsole_win_render(SConsole* console)
	{
		SBuilderCallback bcb;


		// Full color background
		iBmp_fillRect(console->bmp, &console->rc, console->backColor);

		// Iterate through every row
		memset(&bcb, 0, sizeof(bcb));
		bcb.extra1 = console;
		iBuilder_iterate_N_to_N(console->scrollBuffer, sizeof(SConRow), console->nTopRow, console->nTopRow + console->nRows, &bcb, (uptr)&iConsole_win_render__callbackRow);

		// All done, force a full repaint by Windows
		InvalidateRect(console->hwnd, NULL, false);
	}

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
	bool iConsole_win_render__callbackCol(SBuilderCallback* bcb)
	{
		s32					lnY, lnX, lnRow;
		f32					lfAlp, lfMalp, lfRed, lfGrn, lfBlu, lfBRed, lfBGrn, lfBBlu, lfFRed, lfFGrn, lfFBlu;
		f32*				pixelRow;
		SConsole*			console;
		SConChar*			conChar;
		SBgr*				lbgr;
		SConFont_fixed*		font_fixed;
		RECT				lrc;


		// Grab the pointers
		console	= (SConsole*)bcb->extra1;
		conChar	= (SConChar*)bcb->iter_ptr;

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
			for (lnY = 0, lnRow = (console->nY * console->nCharHeight); lnY < console->nCharHeight; lnY++, lnRow++)
			{
				// Compute the offset into the pixel buffers
				lbgr = (SBgr*)(console->bmp->bd + ((console->bmp->bi.biHeight - lnRow - 1) * console->bmp->rowWidth) + (console->nX * console->nCharWidth * 3));

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
			SetRect(&lrc,	console->nX * console->nCharWidth,
							console->nY * console->nCharHeight,
							((console->nX + 1) * console->nCharWidth)  - 1,
							((console->nY + 1) * console->nCharHeight) - 1);

			// Draw this character
			DrawText(console->bmp->hdc, (s8*)&conChar->c, 1, &lrc, DT_LEFT | DT_SINGLELINE);
		}

		// Continue with the other characters
		return(true);
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
// Windows callback, delivering messages
//
//////
	LRESULT CALLBACK iConsole_wndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		PAINTSTRUCT		ps;
		HDC				hdc;
		RECT			lrc;
		SConsole*		console;


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
						console->lCursorOn = !console->lCursorOn;

						// Repaint the cursor area
						SetRect(&lrc,	console->nX * console->nCharWidth,
										console->nY * console->nCharHeight - 2,
										((console->nX + 1) * console->nCharWidth),
										((console->nY + 1) * console->nCharHeight) + 2);

						// Invalidate that rectangle to update the cursor
						InvalidateRect(hwnd, &lrc, false);
						break;
					}
					break;

				case WM_ERASEBKGND:
					// Ignore it
					return 1;
					break;

				case WM_PAINT:
					// Internally we maintain the drawn state of the window in a separate buffer,
					// and simply BitBlt it back out to the main window as is needed by the OS
					hdc = BeginPaint(hwnd, &ps);
					BitBlt(hdc, 0, 0, console->nWidth, console->nHeight, console->bmp->hdc, 0, 0,SRCCOPY);
					if (glCursorOn && GetForegroundWindow() == hwnd && console->lCursorOn)
					{
						// Highlight the cursor
						SetRect(&lrc,	console->nX * console->nCharWidth,
										console->nY * console->nCharHeight - 2,
										((console->nX + 1) * console->nCharWidth),
										((console->nY + 1) * console->nCharHeight) + 2);

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
