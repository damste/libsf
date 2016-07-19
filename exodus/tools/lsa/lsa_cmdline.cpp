//////////
//
// /libsf/exodus/tools/lsa/lsa_cmdline.cpp
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
//     Jul.19.2016
//////
// Change log:
//     Jul.19.2016 - Initial creation
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
//
// Called to parse the command line and load its various parameters
//
//////
	void ilsa_parse_commandLine(s32 argc, s8* argv[])
	{
		bool		llSetValue;
		s32			lnI, lnLength;
		s8*			lcThisOption;
		s8*			lcIncludePath;
		SLsaFile*	file;


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
					lcThisOption = argv[lnI];
					if (lnLength > sizeof(cgc_wno) - 1 && _memicmp(argv[lnI], cgc_wno, sizeof(cgc_wno) - 1) == 0)
					{
						// Yes, which means the option will be turned off
						llSetValue	= false;
						argv[lnI]	+= sizeof(cgc_wno) - 1;
						lnLength	-= sizeof(cgc_wno) - 1;

					} else {
						// The option will be turned on
						llSetValue	= true;

						// Skip past the leading -W (if need be)
						if (lnLength > sizeof(cgc_w) - 1 && _memicmp(argv[lnI], cgc_w, sizeof(cgc_w) - 1) == 0)
						{
							argv[lnI] += sizeof(cgc_w) - 1;
							lnLength -= sizeof(cgc_w) - 1;
						}
					}


				//////////
				// If we're still on a hyphen, skip past it
				//////
					if (argv[lnI][0] == '-')
					{
						++argv[lnI];
						--lnLength;
					}


				// Entered to allow structured exit
				do {
					//////////
					// Which warnings?
					//////
						if (ilsa_is_cmdLineOption(cgc_wmissing_type_ptr))
						{
							// -Wmissing-type-ptr		-- Using "mov eax,[esi]" rather than "mov eax,u32 ptr [esi]"
							// -Wno-missing-type-ptr
							cmdLine.w.Wmissing_type_ptr = llSetValue;
							break;

						} else if (ilsa_is_cmdLineOption(cgc_wall)) {
							// -Wall					-- Show all warnings
							// -Wno-all
							cmdLine.w.Wall = llSetValue;
							break;

						} else if (ilsa_is_cmdLineOption(cgc_wfatal_errors)) {
							// -Wfatal-errors			-- Should compilation stop immediately on first error?
							// -Wno-fatal-errors
							cmdLine.w.Wfatal_errors = llSetValue;
							break;

						} else if (ilsa_is_cmdLineOption(cgc_werror)) {
							// -Werror					-- Should warnings be treated as errors?
							// -Wno-error
							cmdLine.w.Werror = llSetValue;
							break;
						}
					
					
					//////////
					// Which options?
					//////
						if (ilsa_is_cmdLineOption(cgc_syntax_only))
						{
							// -fsyntax-only			-- Syntax check only
							cmdLine.o.lSyntax_only = llSetValue;
							break;

						} else if (ilsa_is_cmdLineOption(cgc_verbose)) {
							// -verbose					-- Show extra compilation information
							cmdLine.o.lVerbose = llSetValue;
							break;

						} else if (ilsa_is_cmdLineOption_beginsWith(cgc_includePath)) {
							// -includepath=
							lcIncludePath = lcThisOption + 1 + sizeof(cgc_includePath) - 1;
							ilsa_includePath_append(lcIncludePath, strlen(lcIncludePath), false);

						} else {
							// Unrecognized option
							printf("--Error: unrecognized command line option: %s", lcThisOption);
							exit(-1);
						}

				// Loop to allow structured exit
				} while (0);


			} else {
				// Based on our command line option syntax, since it doesn't begin with a hyphen, it can only be a file to assemble
				// Try to load it
				if (!ilsa_includeFile_append(argv[lnI], (file = NULL, &file)))
				{
					// Unable to load
					printf(cgc_unable_to_open_file, argv[lnI]);
					exit(-2);
				}

				// Initialize the file buffer
				if (!cmdLine.filesToCompile)
					iBuilder_createAndInitialize(&cmdLine.filesToCompile);

				// Add the file
				if (cmdLine.filesToCompile)
					iBuilder_append_uptr(cmdLine.filesToCompile, (uptr)file);
			}
		}
	}
