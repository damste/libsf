//////////
//
// /libsf/exodus/tools/lasm/lasm_structs.h
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
//     Sep.12.2015
//////
// Change log:
//     Sep.12.2015 - Initial creation
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
//




//////////
// lasm structs
//////

	// Assembler warnings, all enabled by default
	struct SWarnings
	{
		bool		missing_type_ptr;					// -Wmissing-type-ptr	-- Uses "mov [ebp-4],eax" rather than "mov dword ptr [ebp-4],eax", missing type ptr "dword ptr"
	};

	// Options specified on the command line
	struct SLasmCmdLine
	{
		SWarnings	w;									// Which warnings are enabled?

		bool		Wall;								// -Wall				-- Show all warnings
		bool		Wfatal_errors;						// -Wfatal-errors		-- Should compilation stop immediately on first error?
		bool		WError;								// -WError				-- Should warnings be treated as errors?
		bool		fsyntax_only;						// -fsyntax-only		-- Syntax check only
	};

	// File-level assemble status
	struct SLasmFileStatus
	{
		s32			errors		: 8;					// Up to 256 errors are allowed
		s32			warnings	: 8;					// Up to 256 warnings are allowed

		// Note:  Based on every line within the file being line->status->isCompleted = true;
		bool		isCompleted	: 1;					// Is the assemble process completed on this line?
	};

	// Linked list of files to be assembled
	struct SLasmFile
	{
		SLL					ll;							// Link list through multiple files

		// File and status
		SDatum				fileName;					// Source file
		SLasmFileStatus		status;						// Processing through the assemble process

		// Raw disk file contents
		FILE*				fh;							// File handle
		s8*					raw;						// Raw data
		u32					rawLength;					// Raw data length

		// Parsed into line structures
		SLine*				firstLine;					// Source file content for this file (including any include files)
	};

	// #define statements
	struct SLasmDefine
	{
		SLL					ll;										// Link list through multiple defines

		// Required parameters
		SDatum				name;									// The "xyz" in #define xyz
		SLine*				firstLine;								// Potentially multiple lines

		// Optional parameters (the a, b,..., z in #define xyz(a,b,...,z))
		s32					paramCount;								// Actual parameter count
		SDatum				params[_MAX_LASM_DEFINE_PARAMS];		// Parameter names and lengths
	};
