//////////
//
// /libsf/exodus/tools/lsa/lsa.cpp
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
	#define _LSA_COMPILE 1					// Turns on some features in VJr for lasm
	#define _BMP_LOCALITY 1					// Force definitions to be local
	const char cgc_appName[] = "lsa";		// Give our app a name
	



//////////
// Include VJr stuff, then lsa stuff
//////
	#include "lsa.h"

	// Algorithms
	#include "lsa_cmdline.cpp"		// Command line algorithms
	#include "lsa_dmac.cpp"			// Define/Macro token algorithms
	#include "lsa_ei.cpp"			// extra_info algorithms
	#include "lsa_include.cpp"		// Process include file algorithms
	#include "lsa_params.cpp"		// Process parameter algorithms
	#include "lsa_status.cpp"		// File, line, component status algorithms




//////////
//
// Main program entry point
//
//////
	#undef main

	s32 main(s32 argc, s8* argv[])
	{
		u32				lnI;
		SLsaFile*		file;
		SLsaInclude*	include;


		//////////
		// Initialize
		//////
			include = ilsa_init();


		//////////
		// Grab options
		//////
			ilsa_parse_commandLine(argc, argv);


		//////////
		// Compile
		//////
			// Dispatch each pass
			iterate(lnI, (cmdLine.filesToCompile), file, SLsaFile)
			//
				// Grab the current file
				cmdLine.file	= file;
				cmdLine.fileOut	= NULL;

				// Dispatch each pass
				ilsa_pass0();
				ilsa_pass1();
				ilsa_pass2();
				ilsa_pass3();
				ilsa_passX();
				ilsa_passY();
				ilsa_passZ();

				// Indicate we're completed at this point
				if (!cmdLine.o.lVerbose && cmdLine.fileOut)
					printf("--%s, %\n", cmdLine.fileOut->filename.data_cs8, cmdLine.fileOut->rawLength);
			//
			iterate_end;


		// If we get here, success
		return(0);
	}




//////////
//
// 
//
//////
	SLsaInclude* ilsa_init(void)
	{
		u32	lnPathnameLength;
		s8	fileName[_MAX_PATH];


		// Identify
		printf("ES/2 LibSF Assembler | LSA v0.01\n");

		// Initialize
		memset(&cmdLine,	0, sizeof(cmdLine));		// Initialize all options to off
		memset(&cmdLine.w,	1, sizeof(cmdLine.w));		// Initialize all warnings to on
		memset(fileName,	0, sizeof(fileName));
		iBuilder_createAndInitialize(&includePaths, sizeof(SLsaInclude)	* 50);
		iBuilder_createAndInitialize(&includeFiles, sizeof(SLsaFile)	* 50);

		// Grab the current directory (as our starting point)
		lnPathnameLength	= GetCurrentDirectory(sizeof(fileName) - 1, fileName);
		return(ilsa_includePath_append(fileName, lnPathnameLength, false));
	}




//////////
//
// Used for internal debugging, places where errors are not actively reported, but
// should never occur, but are occurring, are routed through here for debugging.
//
//////
	void ilsa_routeThrough_silentError_forDebugging(void)
	{
		// For debugging, errors that should not occur route through this function
		debug_nop;
	}
