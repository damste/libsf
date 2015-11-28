//////////
//
// /libsf/source/vjr/source/debugger/jdebic/jdebic.h
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
// Version 0.58
// Copyright (c) 2015 by Rick C. Hodgin
//////
// Last update:
//     Apr.10.2015
//////
// Change log:
//     Apr.10.2015 - Initial creation
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
//	       _  _____         _      _   _____ 
//	      | ||  __ \       | |    (_) / ____|
//	      | || |  | |  ___ | |__   _ | |     
//	  _   | || |  | | / _ \| '_ \ | || |     
//	 | |__| || |__| ||  __/| |_) || || |____ 
//	  \____/ |_____/  \___||_.__/ |_| \_____|
//				JDebi Companion
//			A Remote Debug Assist Tool
//




//////////
//
// Data preparation functions:
//		JDebiC_debug		-- Prepare and transmit win, obj data to the remote
//		JDebiC_text			-- Prepare and transmit text to display in the text window
//		JDebiC_data			-- Prepare and transmit data to parse remotely and have available for display
//
// Communication functions:
//		iJDebiC_connect		-- Connects to remote process
//		iJDebiC_transmit	-- Transmits data from this process to the other
//
// Serialization functions:
//		iJDebiC_thisCode	-- Converts a thisCode object into its call stack for examination
//		iJDebiC_win			-- Converts information about a window into text
//		iJDebiC_obj			-- Converts an object into its text form
//
//////////




//////////
// Forward declarations
//////
	void		JDebiC_debug					(SWindow* win, SObject* obj);
	void		JDebiC_text						(s8* tcText);
	void		JDebiC_data						(s8* tcData, s32 tnDataLength, u32 tnDataType);

	// Helper functions
	bool		iJDebiC_connect					(void);
	s32			iJDebiC_transmit_viaPipe		(SDatum* data1, SDatum* data2, u32 tnDataType);
	HANDLE		iJDebiC_createPipeHandle		(cs8* lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);
	bool		iJDebiC_alreadyProcessedItem	(SBuilder* items, void* item);
	void		iJDebiC_recordNewItem			(SBuilder* items, void* item);

	// Processes each structure into text
	void		iJDebiC_thisCode				(SBuilder* data, SBuilder* items,	SThisCode* thisCode);
	void		iJDebiC_sourceCode				(SBuilder* data, SBuilder* items,	SSourceCode* sourceCode);
	void		iJDebiC_function				(SBuilder* data, SBuilder* items,	SFunction* func);
	void		iJDebiC_variable				(SBuilder* data, SBuilder* items,	SVariable* var);
	void		iJDebiC_sem						(SBuilder* data, SBuilder* items,	SEM* sem);
	void		iJDebiC_win						(SBuilder* data, SBuilder* items,	SWindow* win);
	void		iJDebiC_obj						(SBuilder* data, SBuilder* items,	SObject* obj);

	// Process sub-components
	void		iiJDebiC_decode_Rect			(s8* buffer, RECT* rc);
	void		iiJDebiC_decode_POINT			(s8* buffer, POINT pt);
	void		iiJDebiC_decode_SMouseData		(s8* buffer, SMouseData* md);


//////////
// JDebiC
//////
	HWND		hwndJDebiC;						// The HWND to the remote
	uptr		handleJDebiCOut;				// The pipe handle to write data
	uptr		gnJDebiCOutPipeNumber;			// The pipe number we were allocated from the remote


//////////
// Transmission types
//////
	cu32		_WMJDEBIC_PIPE_REQUEST			= WM_USER + 0;
	cu32		_WMJDEBIC_DATA_TYPE_DATA		= WM_USER + 1;
	cu32		_WMJDEBIC_DATA_TYPE_BITMAP		= WM_USER + 2;
	cu32		_WMJDEBIC_DATA_TYPE_HEXDUMP		= WM_USER + 3;
	cu32		_WMJDEBIC_DATA_TYPE_TEXT		= WM_USER + 4;
	cu32		_WMJDEBIC_DATA_TYPE_THISCODE	= WM_USER + 5;
	cu32		_WMJDEBIC_DATA_TYPE_WIN			= WM_USER + 6;
	cu32		_WMJDEBIC_DATA_TYPE_OBJ			= WM_USER + 7;


//////////
// Constants
//////
	cs8			cgcJDebiCClassName[]			= "JDebiC_RemoteApp_PipeMessageReceptor";
