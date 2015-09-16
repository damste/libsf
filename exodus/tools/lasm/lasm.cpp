//////////
//
// /libsf/exodus/tools/lasm/lasm.cpp
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
// This document and all documents contained within are released as Liberty Software
// under a Repeat License, as governed by the Public Benefit License v1.0 or later
// (PBL).
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
//
// Liberty Software Foundation's lasm (LibSF Assembler).
//
//////




//////////
// Uses Visual FreePro, Jr's existing facilities to simplify our processing
//////
	#define _NONVJR_COMPILE 1				// Turns off some features in VJr that fail on compilation from here
	#define _LASM_COMPILE 1					// Turns on some features in VJr for lasm
	#define _BMP_LOCALITY 1					// Force definitions to be local
	const char cgc_appName[] = "lasm";		// Give our app a name

	// Line-level assemble status
	struct SLasmLineStatus
	{
		int			errors		: 8;					// Up to 256 errors are allowed
		int			warnings	: 8;					// Up to 256 warnings are allowed

		// Note:  Blank lines, and comments will be marked completed immediately, as will #include lines after they're included, etc.
		bool		isCompleted	: 1;					// Is the assemble process completed on this line?

		// As each pass is conducted
		bool		pass0		: 1;					// Pass-0 -- load all #include files
		bool		passN		: 1;					// Pass-N -- identifying all symbols, and all start and ending blocks
		bool		passX		: 1;					// Pass-X -- code generation
		bool		passY		: 1;					// Pass-Y -- linking
		bool		passZ		: 1;					// Pass-Z -- write out the file
	};


//////////
// Include VJr stuff, then lasm stuff
//////
	#include "\libsf\source\vjr\source\vjr.h"
	#include "lasm.h"




//////////
//
// Main program entry point
//
//////
	#undef main

	s32 main(s32 argc, s8* argv[])
	{
		s32				lnI, lnLength, lnPass;
		bool			llSetValue;
		s8*				lcOption;
		SLasmFile*		file;
		SLasmCmdLine	cmdLine;


		//////////
		// Initialize
		//////
			// Initialize main engine
			iVjr_init(NULL);


		//////////
		// Initialize our engine
		//////
			memset(&cmdLine,	0, sizeof(cmdLine));		// Initialize all options off
			memset(&cmdLine.w,	1, sizeof(cmdLine.w));		// Initialize all warnings on


		//////////
		// Identify self
		//////
			printf("LibSF Assembler for Exodus v0.01\n");


		//////////
		// Process command line parameters
		//////
			for (lnI = 1; lnI < argc; lnI++)
			{

				// Is it an option or a file?
				if (argv[lnI][0] == '-')
				{
					// It's an option
					lnLength = strlen(argv[lnI]);


					//////////
					// See if it's a -Wno- option
					//////
						lcOption = argv[lnI];
						if (lnLength > sizeof(cgc_wno) - 1 && _memicmp(argv[lnI], cgc_wno, sizeof(cgc_wno) - 1) == 0)
						{
							// It's -Wno-, so the set value will be false
							llSetValue = false;
							argv[lnI] += sizeof(cgc_wno) - 1;

						} else {
							// The value to set will be true
							llSetValue = true;

							// Skip past -W if need be
							if (lnLength > sizeof(cgc_wno) - 1 && _memicmp(argv[lnI], cgc_wno, 2) == 0)
								argv[lnI] += 2;
						}


					//////////
					// Find out which option
					//////
						if (lnLength == sizeof(cgc_wmissing_type_ptr) - 1 && _memicmp(argv[lnI], cgc_wmissing_type_ptr, sizeof(cgc_wmissing_type_ptr) - 1) == 0)
						{
							// -Wmissing-type-ptr
							// -Wno-missing-type-ptr
							cmdLine.w.missing_type_ptr = llSetValue;

						} else if (lnLength == sizeof(cgc_wall) - 1 && _memicmp(argv[lnI], cgc_wall, sizeof(cgc_wall) - 1) == 0) {
							// -Wall				-- Show all warnings
							// -Wno-all
							cmdLine.Wall = llSetValue;

						} else if (lnLength == sizeof(cgc_wfatal_errors) - 1 && _memicmp(argv[lnI], cgc_wfatal_errors, sizeof(cgc_wfatal_errors) - 1) == 0) {
							// -Wfatal-errors		-- Should compilation stop immediately on first error?
							// -Wno-fatal-errors
							cmdLine.Wfatal_errors = llSetValue;

						} else if (lnLength == sizeof(cgc_werror) - 1 && _memicmp(argv[lnI], cgc_werror, sizeof(cgc_werror) - 1) == 0) {
							// -Werror				-- Should warnings be treated as errors?
							// -Wno-error
							cmdLine.WError = llSetValue;

						} else if (lnLength == sizeof(cgc_fsyntax_only) - 1 && _memicmp(argv[lnI], cgc_fsyntax_only, sizeof(cgc_fsyntax_only) - 1) == 0) {
							// -fsyntax-only		-- Syntax check only
							cmdLine.fsyntax_only = llSetValue;

						} else {
							// Unrecognized option
							printf("--Error: unrecognized command line option: %s", lcOption);
							return(-1);
						}

				} else {
					// It can only be a file to assemble

					// Try to load it
					if (!ilasm_appendFile(argv[lnI]))
					{
						printf("--Error: unable to open file: %s\n", argv[lnI]);
						return(-2);
					}
				}
			}


		//////////
		// Iterate through each file on this pass
		//////
			for (file = gsFirstFile; file; file = (SLasmFile*)file->ll.next)
			{

				// Begin passes through each file
				for (lnPass = 0; lnPass < 26 && !file->status.isCompleted; lnPass++)
				{

					//////////
					// Identify the file on the first pass
					//////
						if (lnPass == 0)
							printf("Assembling %s\n", file->fileName.data_s8);


					//////////
					// Dispatch the pass
					//////
						switch (lnPass)
						{
							case 0:
								// Pass-0
								ilasm_pass0(file);
								break;

							case 24:
								// Pass-X
								ilasm_passX(file);
								break;

							case 25:
								// Pass-Y
								ilasm_passY(file);
								break;

							case 26:
								// Pass-Z
								ilasm_passZ(file);
								break;

							default:
								// Pass-N
								ilasm_passN(file);
								break;
						}

				}

			}


		//////////
		// Return our exit code
		//////
			return(0);

	}




//////////
//
// Called to append the indicated file to the chain, and read in its file contents
//
//////
	bool ilasm_appendFile(s8* tcPathname)
	{
		SLasmFile	f;
		SLasmFile*	fNew;


		//////////
		// Initialize
		//////
			memset(&f, 0, sizeof(f));


		//////////
		// Try to read the file
		//////
			if (iFile_readContents(tcPathname, &f.fh, &f.raw, &f.rawLength))
			{

				// Parse into lines
				if (iFile_parseIntoLines(&f.firstLine, f.raw, f.rawLength) > 0)
				{

					// Append our entry onto the chain
					fNew = (SLasmFile*)iLl_appendNewNodeAtEnd((SLL**)&gsFirstFile, sizeof(f));
					if (fNew)
					{
						// Copy over
						fNew->firstLine		= f.firstLine;
						fNew->fh			= f.fh;
						fNew->raw			= f.raw;
						fNew->rawLength		= f.rawLength;
						fNew->fileName		= f.fileName;
						iDatum_duplicate(&f.fileName, tcPathname, -1);

						// Indicate success
						return(true);
					}
				}
			}


		//////////
		// If we get here, failure
		//////
			return(false);

	}




//////////
//
// Pass-N -- General expansion and parsing
//
//////
	void ilasm_passN(SLasmFile* file)
	{
	}




//////////
//
// Pass-X -- Binary code generation
//
//////
	void ilasm_passX(SLasmFile* file)
	{
	}




//////////
//
// Pass-Y -- Linking
//
//////
	void ilasm_passY(SLasmFile* file)
	{
	}




//////////
//
// Pass-Z -- Writing output
//
//////
	void ilasm_passZ(SLasmFile* file)
	{
	}