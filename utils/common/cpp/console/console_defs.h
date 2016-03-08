//////////
//
// /libsf/utils/common/cpp/console/console_defs.h
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




//////////
// console.cpp
//////
	CONAPI uptr		console_initialize					(void);
	CONAPI uptr		console_allocate					(SDatum* title, s32 tnLeft, s32 tnTop, s32 tnCols, s32 tnRows, SConCallback* cb);
	CONAPI uptr		console_allocate					(SDatum* settings, SConCallback* cb);
	CONAPI uptr		console_reregister					(uptr tnHandle, SConCallback* cb);
	CONAPI s32		console_show						(uptr tnHandle, bool tlVisible);
	CONAPI s32		console_release						(uptr tnHandle);

	// Sets title, width, height, charWidth, charHeight, and visible
	CONAPI s32		console_setProperties				(uptr tnHandle, SDatum* properties);
	CONAPI s32		console_setBorder					(uptr tnHandle, bool tlShowBorder, SBgra* color);

	// Set the active font (to use for the console_push() operations until changed again)
	CONAPI s32		console_setFont						(uptr tnHandle, SDatum* fontName, s32 tnPointSize, bool tlBold, bool tlItalic, bool tlUnderline);
	CONAPI s32		console_setFont						(uptr tnHandle, SDatum* fontData);
	CONAPI s32		console_getFont						(uptr tnHandle, s32 tnX, s32 tnY, SDatum* fontName, s32* tnPointSize, bool* tlBold, bool* tlItalic, bool* tlUnderline);
	CONAPI s32		console_getFont						(uptr tnHandle, s32 tnX, s32 tnY, SDatum* fontData);

	// General write algorithm, processes CR/LF, and auto-scrolls
	CONAPI s32		console_print						(uptr tnHandle, SDatum* textOut);
	CONAPI s32		console_print						(uptr tnHandle, s8* text, s32 tnTextLength = -1);
	CONAPI s32		console_print_crlf					(uptr tnHandle);
	CONAPI s32		console_gotoXY						(uptr tnHandle, s32 tnX, s32 tnY);
	CONAPI s32		console_getXY						(uptr tnHandle, s32* tnX, s32* tnY);
	CONAPI s32		console_scroll						(uptr tnHandle, s32 tnRows, bool tlMoveCursor = true);
	CONAPI s32		console_repaint						(uptr tnHandle);
	CONAPI s32		console_box_single					(uptr tnHandle, s32 tnXul, s32 tnYul, s32 tnXlr, s32 tnYlr, SBgra* backColor, SBgra* charColor);
	CONAPI s32		console_box_double					(uptr tnHandle, s32 tnXul, s32 tnYul, s32 tnXlr, s32 tnYlr, SBgra* backColor, SBgra* charColor);
	CONAPI s32		console_box_custom					(uptr tnHandle, s32 tnXul, s32 tnYul, s32 tnXlr, s32 tnYlr, SBgra* backColor, SBgra* charColor, u8 ul, u8 top, u8 ur, u8 r, u8 lr, u8 b, u8 ll, u8 l);

	// For input blocks
	CONAPI s32		console_input_fields_clear_all		(uptr tnHandle);
	CONAPI uptr		console_input_field_add				(uptr tnHandle, s32 tnX, s32 tnY, s32 tnLength, SBgra* backColor, SBgra* charColor, SDatum* liveValue, SConInputCallback* cicb = NULL);
	CONAPI s32		console_input_field_delete			(uptr tnHandle, uptr tnInputFieldHandle);

	// Explicitly push large quantities of raw content to the screen, or pull raw content from the screen
	CONAPI s32		console_raw_push					(uptr tnHandle, s32 tnX, s32 tnY, SBgra color, SDatum* textIn, bool tlWrap);
	CONAPI s32		console_raw_pullN					(uptr tnHandle, s32 tnX, s32 tnY, s32 tnCount, SDatum* textOut);

	// Obtain more information about each character
	CONAPI s32		console_raw_pull1					(uptr tnHandle, s32 tnX, s32 tnY, u8* c, SBgra* color, bool* tlBold, bool* tlItalic, bool* tlUnderline);

	// Explicitly push embedded/formatted content to the screen
	CONAPI s32		console_vt100_push					(uptr tnHandle, SDatum* vt100Text);


//////////
// Internal functions
//////
	bool			iiConsole_setOptions_callback		(SDatumCallback* cb);
	bool			iConsole_validateInitialization		(void);
	bool			iConsole_validateScrollBuffer		(SConsole* console);
	SConsole*		iConsole_find_byHandle				(uptr tnHandle);
	void			iConsole_silentError_passThru		(void);
	void			iiConsole_storeCharacter			(SConsole* console, char c, bool tlAtCursorXY = false);
	void			iiConsole_validateXYRange			(SConsole* console);
	void			iiConsole_selectFont				(SConsole* console, s32 fontIndex);
	void			iiConsole_scroll					(SConsole* console);
	bool			iConsole_scroll__callback			(SBuilderCallback* bcb);
	bool			iConsole_anyValidConsoles			(void);
	bool			iConsole_anyValidConsoles__callback	(SBuilderCallback* bcb);
	u32				iGetNextUid							(void);
	SConInput*		iConsole_input_addNew				(void);
	bool			iConsole_input_addNew__callback		(SBuilderCallback* bcb);
	SConInput*		iConsole_input_find_byHandle		(uptr tnInputFieldHandle);
	bool			iConsole_input_find_byHandle__callback(SBuilderCallback* bcb);
