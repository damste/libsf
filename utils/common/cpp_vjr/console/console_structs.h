//////////
//
// /libsf/utils/common/cpp/console/console_strcts.h
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



struct SConsole;
struct SConFont_fixed;


//////////
// Callback functions for console activity
//////
	struct SConCallback
	{
		u32				uid;				// Unique ID for this instance
		union {
			uptr		_console;			// The handle (value of the pointer as a uptr)
			SConsole*	console;			// Console it relates to
		};

		// Callback info (could be different than live console info)
		s32				nX;					// Mouse X coordinate, or console X coordinate for keystroke input
		s32				nY;					// Mouse Y coordinate, or console Y coordinate for keystroke input


		//////////
		// Mouse position
		//////
			bool			lLeftButton;	// Left mouse button is down
			bool			lMiddleButton;	// Middle mouse button is down
			bool			lRightButton;	// Right mouse button is down
			bool			lAnyButton;		// If any button is down


		//////////
		// Keystroke data
		//////
			u8				cChar;			// ASCII code
			u32				nOsKey;			// OS keycode

			// Special keys
			bool			lShift;			// True if any shift key is down
			bool			lCtrl;			// True if any ctrl key is down
			bool			lAlt;			// True if any alt key is down
			bool			lCaps;			// True if caps lock is on
			bool			lNum;			// True if num lock is on
			bool			lScroll;		// True if scroll lock is on


		//////////
		// Callbacks
		//////
			union {
				// When the user creates a console
				uptr		_console_create;
				s32			(*console_create)		(uptr tnHandle, s32 tnWidth, s32 tnHeight);
			};

			union {
				// When the user closes the console with the OS close button
				uptr		_console_close;
				s32			(*console_close)		(uptr tnHandle);
			};

			union {
				// When a key is received (key could be being held down, and it will repeat here)
				uptr		_console_keyDown;
				s32			(*console_keyDown)		(SConCallback* ccb);
			};

			union {
				// When a key is received (key could be being held down, and it will repeat here)
				uptr		_console_keyUp;
				s32			(*console_keyUp)		(SConCallback* ccb);
			};

			union {
				// Mouse movement
				uptr		_console_mouseMove;
				s32			(*console_mouseMove)	(SConCallback* ccb);
			};

			union {
				// Mouse down
				uptr		_console_mouseDown;
				s32			(*console_mouseDown)	(SConCallback* ccb);
			};

			union {
				// Mouse up
				uptr		_console_mouseUp;
				s32			(*console_mouseUp)		(SConCallback* ccb);
			};

	};


// Callbacks on input
struct SConInputCallback
{
	// If true, then no local processing takes place
	bool		lOnlySignalKeystrokes;		// Signals keystrokes only
	bool		lSuppressBorder;			// Suppress the standard border

	// An inner border
	bool		lInnerBorder;				// Renders an inner-border (regardless of lSuppressBorder setting)
	SBgra		innerBorderColor;			// Color to render

	// Visual changes
	bool		lChanged;					// Has the data changed?
	bool		lVisualize_onChange;		// Should the change be visualized with the backColor_changed, charcolor_changed colors
	SBgra		backColor_changed;
	SBgra		charColor_changed;

	// Callback on each change to the field
	union {
		uptr	_onChanged;
		void	(*onChanged)	(uptr tnConsoleHandle, uptr tnInputFieldHandle);
	};

	// Callback on every keystroke after it's been processed locally
	union {
		uptr	_onKeystroke;
		void	(*onKeystroke)	(uptr tnConsoleHandle, uptr tnInputFieldHandle, s32 tnRawKey, bool tlCtrl, bool tlAlt, bool tlShift, bool tlLeft, bool tlMiddle, bool tlRight, bool tlCaps, bool tlNum, bool tlScroll, bool tlAnyButton);
	};

	// LostFocus
	union {
		uptr	_onLostFocus;
		void	(*onLostFocus)	(uptr tnConsoleHandle, uptr tnInputFieldHandle);
	};

	// GotFocus
	union {
		uptr	_onGotFocus;
		void	(*onGotFocus)	(uptr tnConsoleHandle, uptr tnInputFieldHandle);
	};
};

// Input fields
struct SConInput
{
	bool				lValid;			// Is this entry valid?
	s32					nX;				// X coordinate
	s32					nY;				// Y coordinate
	s32					nLength;		// Length of the input

	s32					nFont;			// Font at time of creation
	SBgra				charColor;		// Text color at time of creation
	SBgra				backColor;		// Background color at time of creation

	SConInputCallback	cicb;			// An optional callback on keystrokes

	SDatum*				liveValue;		// Where to store the live value based on input
};

// Font data
struct SConFont
{
	// For internal fixed-point fonts
	bool			lFixed;				// Uses the internal fixed point font
	s32				nUseX;				// Width in pixels of the fixed point font to use
	s32				nUseY;				// Height in pixels of the fixed point font to use
	s32				nActualX;			// The actual width of the fixed point font when created (may have been scaled)
	s32				nActualY;			// The actual height of the fixed point font when created (may have been scaled)

	// For system-wide fonts
	s32				nPointSize;			// Font point size
	bool			lBold;				// Is it bold?
	bool			lItalic;			// Italics?
	bool			lUnderline;			// Underline?
	SDatum			cFontName;			// Font name

	// OS-specific info
	SConFont_os_struct_variables;		// Extra structure members specific to the OS's needs
};

// Console characters
struct SConChar
{
	u8				c;					// Character to display there
	SBgra			backColor;			// Background color
	SBgra			charColor;			// Foreground color (character color)
	s32				nFont;				// The font set to use

	// OS-specific info
	SConChar_os_struct_variables;		// Extra structure members specific to the OS's needs
};

struct SConRow
{
	s32				nWidth;				// Number of characters stored in this row (can be longer than the display allows)
	SBuilder*		chars;				// SConChar one for each character for nWidth

	// OS-specific info
	SConRow_os_struct_variables;		// Extra structure members specific to the OS's needs
};

// Main consoles
struct SConsole
{
	SConCallback	cb;					// Callback info

	// Position and size
	s32				nRows;				// Number of rows in the window based on the current font
	s32				nCols;				// Number of cols in the window based on the current font
	s32				nLeft;				// Upper-left X coordinate of window
	s32				nTop;				// Upper-left Y coordinate of window
	s32				nWidth;				// Width of window in characters (multiply by char_width to get pixel width)
	s32				nHeight;			// Height of window in characters (multiply by char_height to get pixel height)
	s32				nCharWidth;			// Width of character
	s32				nCharHeight;		// Height of character

	// Window title
	SDatum			title;				// Title of the console window

	// Character settings
	s32				nXText;				// Current X location in the buffer
	s32				nYText;				// Current Y location in the buffer
	s32				nXCursor;			// X coordinate for the cursor (negative if not in use (they haven't used the arrows to navigate around))
	s32				nYCursor;			// Y coordinate for the cursor (negative if not in use (they haven't used the arrows to navigate around))
	SBgra			charColor;			// Color to output in
	s32				nCharFont;			// Font handle to use in gsConsoleFontRoot
	bool			lWordWrap;			// If word wrap is on, then only as many characters as will fit horizontally are stored, then it moves to the next row, otherwise the row can contain more data than will fit in the current window

	// Row buffer
	bool			lInhibitScroll;		// Should scrolling be inhibited?
	SBuilder*		scrollBuffer;		// Holds one SConRow record per row, including scrolled data
	s32				nTopRow;			// The row to display at the top of the scroll buffer
	s32				nScrollRowsToKeep;	// Number of rows to keep in the scroll buffer, negative=unlimited

	// Display, input, and output
	bool			lShowBorder;		// Should the border highlight be shown?
	SBgra			borderColor;		// Set a border color to highlight the window
	SBgra			backColor;			// General color of the background
	bool			lVisible;			// Display
	bool			lAllowInput;		// Should input be returned?
	bool			lAllowOutput;		// Should output be returned?

	// OS-specific info
	SConsole_os_struct_variables;		// Extra structure members specific to the OS's needs
};