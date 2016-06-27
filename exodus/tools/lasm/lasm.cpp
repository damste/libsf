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
	#include "lasm.h"




//////////
//
// Main program entry point
//
//////
	#undef main

	s32 main(s32 argc, s8* argv[])
	{
		u32				lnPathnameLength;
		SLasmInclude*	include;
		SLasmCmdLine	cmdLine;
		s8				fileName[_MAX_PATH];


		// Initialize our engine
		memset(&cmdLine,		0, sizeof(cmdLine));		// Initialize all options off
		memset(&cmdLine.w,		1, sizeof(cmdLine.w));		// Initialize all warnings on
		memset(&includeFiles,	0, sizeof(includeFiles));	// Initialize the include file

		// Grab the current directory as our starting point
		memset(&fileName[0], 0, sizeof(fileName));
		lnPathnameLength	= GetCurrentDirectory(sizeof(fileName) - 1, fileName);
		include				= ilasm_includeFile_append(&fileName[0], lnPathnameLength);
		include->fileName[include->fileNameLength] = 0;
		ilasm_ensure_trailingBackspace(&include[0]);

		// Compile
		printf("LASM v0.01 -- LibSF Assembler -- for ExoduS/2\n");
		ilasm_parse_commandLine(&cmdLine, argc, argv);
		ilasm_compile(&cmdLine);

		// If we get here, success
		return(0);
	}




//////////
//
// Called to parse the command line and load its various parameters
//
//////
	void ilasm_parse_commandLine(SLasmCmdLine* cmdLine, s32 argc, s8* argv[])
	{
		s32		lnI, lnLength;
		bool	llSetToValue;
		s8*		lcOption;


		// Iterate through every parameter
		for (lnI = 1; lnI < argc; lnI++)
		{
			// Is it an option?
			if (argv[lnI][0] == '-')
			{
				// Yes
				lnLength = strlen(argv[lnI]);


				//////////
				// -Wno-?
				//////
					lcOption = argv[lnI];
					if (lnLength > sizeof(cgc_wno) - 1 && _memicmp(argv[lnI], cgc_wno, sizeof(cgc_wno) - 1) == 0)
					{
						// Yes, which means the option will be turned off
						llSetToValue	= false;
						argv[lnI]		+= sizeof(cgc_wno) - 1;

					} else {
						// The option will be turned on
						llSetToValue = true;

						// Skip past the leading -W (if need be)
						if (lnLength > sizeof(cgc_w) - 1 && _memicmp(argv[lnI], cgc_w, sizeof(cgc_w) - 1) == 0)
							argv[lnI] += sizeof(cgc_w) - 1;
					}


				//////////
				// Which warnings?
				//////
					if (lasm_is_cmdLineOption(cgc_wmissing_type_ptr))
					{
						// -Wmissing-type-ptr		-- Using "mov eax,[esi]" rather than "mov eax,dword ptr [esi]"
						// -Wno-missing-type-ptr
						cmdLine->w.Wmissing_type_ptr = llSetToValue;

					} else if (lasm_is_cmdLineOption(cgc_wall)) {
						// -Wall					-- Show all warnings
						// -Wno-all
						cmdLine->w.Wall = llSetToValue;

					} else if (lasm_is_cmdLineOption(cgc_wfatal_errors)) {
						// -Wfatal-errors			-- Should compilation stop immediately on first error?
						// -Wno-fatal-errors
						cmdLine->w.Wfatal_errors = llSetToValue;

					} else if (lasm_is_cmdLineOption(cgc_werror)) {
						// -Werror					-- Should warnings be treated as errors?
						// -Wno-error
						cmdLine->w.Werror = llSetToValue;
					}
				
				
				//////////
				// Which options?
				//////
					if (lasm_is_cmdLineOption(cgc_syntax_only))
					{
						// -fsyntax-only			-- Syntax check only
						cmdLine->o.lSyntax_only = llSetToValue;

					} else if (lasm_is_cmdLineOption(cgc_verbose)) {
						// -verbose					-- Show extra compilation information
						cmdLine->o.lVerbose = llSetToValue;

					} else {
						// Unrecognized option
						printf("--Error: unrecognized command line option: %s", lcOption);
						exit(-1);
					}


			} else {
				// Based on our command line options, it can only be a file to assemble
				// Try to load it
				if (!ilasm_appendFile(argv[lnI], NULL))
				{
					printf("--Error: unable to open file: %s\n", argv[lnI]);
					exit(-2);
				}
			}
		}
	}




//////////
//
// Compile through the multiple passes
//
//////
	void ilasm_compile(SLasmCmdLine* cmdLine)
	{
		s32			lnPass;
		SLasmFile*	file;


		// Iterate through every file, through every pass
		for (file = gsFirstFile; file; file = (SLasmFile*)file->ll.next)
		{
			// Begin passes through each file
			for (lnPass = 0; lnPass < 6 && !file->status.isCompleted; lnPass++)
			{
				// Identify the file on the first pass
				if (lnPass == 0)
					printf("--Assembling %s\n", file->fileName.data._s8);

				// Dispatch the pass on this file
				switch (lnPass)
				{
					case 0:		{	ilasm_pass0(cmdLine, file);		break;	}
// 					case 1:		{	ilasm_pass1(cmdLine, file);		break;	}
// 					case 2:		{	ilasm_pass2(cmdLine, file);		break;	}
// 					case 3:		{	ilasm_pass2(cmdLine, file);		break;	}
// 					case 4:		{	ilasm_passX(cmdLine, file);		break;	}
// 					case 5:		{	ilasm_passY(cmdLine, file);		break;	}
// 					case 6:		{	ilasm_passZ(cmdLine, file);		break;	}
				}
			}
		}
	}




//////////
//
// Called to append the indicated file to the chain, and read in its file contents
//
//////
	bool ilasm_appendFile(s8* tcPathname, SLasmFile** file)
	{
		s32				lnI;
		SLasmFile		f;
		SLasmFile*		fNew;
		SLasmInclude*	include;
		s8				fileName[_MAX_PATH * 2];
// 		s8				fullFileName[_MAX_PATH];


		//////////
		// Initialize
		//////
			memset(&f, 0, sizeof(f));


		//////////
		// Try to locate the #include file
		//////
			if (tcPathname[0] == '.')
			{
				// It is a relative path
				for (lnI = gnMaxIncludePaths - 1; lnI >= 0; lnI--)
				{
					// Grab the include directory reference
					include = &includeFiles[lnI];

					// Store the root path

					// Append the relative filename
					memset(fileName, 0, sizeof(fileName));
					memcpy(fileName, tcPathname, min(_MAX_PATH - 1, strlen(tcPathname)));

					// Try to read the file contents
					if (iFile_readContents(tcPathname, &f.fh, &f.raw, &f.rawLength))
						break;
				}

			} else {
				// It is a hard path, use it as is
			}


		//////////
		// Was it loaded?
		//////
			if (lnI >= 0)
			{
				// Parse into lines
				if (iFile_parseIntoLines(&f.firstLine, f.raw, f.rawLength) > 0)
				{
					// Append our entry onto the chain
					fNew = (SLasmFile*)iLl_appendNew__llAtEnd((SLL**)&gsFirstFile, sizeof(f));
					if (fNew)
					{
						// Copy over
						fNew->firstLine	= f.firstLine;
						fNew->fh		= f.fh;
						fNew->raw		= f.raw;
						fNew->rawLength	= f.rawLength;
						fNew->fileName	= f.fileName;
						iDatum_duplicate(&f.fileName, tcPathname, -1);

						// Setup the #include file level
						fNew->include	= &includeFiles[gnMaxIncludePaths - 1];

						// Update the pointer if need be
						if (file)
							*file = fNew;

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
// Store the include file to a list of directories for later traversal should we
//
//////
	SLasmInclude* ilasm_includeFile_append(s8* tcPathname, s32 tnPathnameLength)
	{
		SLasmInclude* include;


		// Get the appropriate entry
		if (gnMaxIncludePaths < _LASM_MAX_INCLUDE_FILES)
		{
			// Grab the slot
			include = &includeFiles[gnMaxIncludePaths++];

			// Expand to its full form
			GetFullPathName(tcPathname, tnPathnameLength, &include->fileName[0], &include->fileNamePortion);

			// NULL-terminate
			*include->fileNamePortion = 0;

			// Validate that it ends in a backslash
			ilasm_ensure_trailingBackspace(include);

			// Store the new length
			include->fileNameLength	 = strlen(include->fileName);

		} else {
			// We're reached our limit
			printf("--Error: too many #include files (%d)\n", _LASM_MAX_INCLUDE_FILES + 1);
			exit(-1);
		}

		// Indicate our result
		return(include);
	}




//////////
//
// For include files, makes sure that they have the trailing backspace
//
//////
	SLasmInclude* ilasm_ensure_trailingBackspace(SLasmInclude* include)
	{
		// Make sure the last character's a backspace
		if (include->fileName[include->fileNameLength - 1] != '\\')
		{
			// Make it a backslash
			include->fileName[include->fileNameLength] = '\\';

			// Increase its length
			++include->fileNameLength;
		}

		// Pass-thru our parameter
		return(include);
	}




//////////
//
// Called to adjust the slashes
//
//////
	void ilasm_fixupDirectories(s8* tcPathname, s32 tnPathnameLength)
	{
		s32 lnI;


		// Iterate through the pathname and switch all '/' to '\' characters
		for (lnI = 0; lnI < tnPathnameLength; lnI++)
		{
			// If it's a slash, change it to a backslash
			if (tcPathname[lnI] == '/')
				tcPathname[lnI] = '\\';
		}
	}
