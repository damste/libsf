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


		//////////
		// Identify
		//////
			printf("ES/2 LibSF Assembler | LASM v0.01\n");


		//////////
		// Initialize
		//////
			memset(&cmdLine,	0, sizeof(cmdLine));		// Initialize all options off
			memset(&cmdLine.w,	1, sizeof(cmdLine.w));		// Initialize all warnings on
			memset(fileName,	0, sizeof(fileName));
			iBuilder_createAndInitialize(&includePaths, sizeof(SLasmInclude) * 50);
			iBuilder_createAndInitialize(&includeFiles, sizeof(SLasmFile) * 50);

			// Grab the current directory (as our starting point)
			lnPathnameLength	= GetCurrentDirectory(sizeof(fileName) - 1, fileName);
			include				= ilasm_includePath_append(fileName, lnPathnameLength, false);


		//////////
		// Grab options
		//////
			ilasm_parse_commandLine(&cmdLine, argc, argv);


		//////////
		// Compile
		//////
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
		bool	llSetValue;
		s32		lnI, lnLength;
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
						if (lasm_is_cmdLineOption(cgc_wmissing_type_ptr))
						{
							// -Wmissing-type-ptr		-- Using "mov eax,[esi]" rather than "mov eax,u32 ptr [esi]"
							// -Wno-missing-type-ptr
							cmdLine->w.Wmissing_type_ptr = llSetValue;
							break;

						} else if (lasm_is_cmdLineOption(cgc_wall)) {
							// -Wall					-- Show all warnings
							// -Wno-all
							cmdLine->w.Wall = llSetValue;
							break;

						} else if (lasm_is_cmdLineOption(cgc_wfatal_errors)) {
							// -Wfatal-errors			-- Should compilation stop immediately on first error?
							// -Wno-fatal-errors
							cmdLine->w.Wfatal_errors = llSetValue;
							break;

						} else if (lasm_is_cmdLineOption(cgc_werror)) {
							// -Werror					-- Should warnings be treated as errors?
							// -Wno-error
							cmdLine->w.Werror = llSetValue;
							break;
						}
					
					
					//////////
					// Which options?
					//////
						if (lasm_is_cmdLineOption(cgc_syntax_only))
						{
							// -fsyntax-only			-- Syntax check only
							cmdLine->o.lSyntax_only = llSetValue;
							break;

						} else if (lasm_is_cmdLineOption(cgc_verbose)) {
							// -verbose					-- Show extra compilation information
							cmdLine->o.lVerbose = llSetValue;
							break;

						} else {
							// Unrecognized option
							printf("--Error: unrecognized command line option: %s", lcOption);
							exit(-1);
						}

				// Loop to allow structured exit
				} while (0);


			} else {
				// Based on our command line option syntax, since it doesn't begin with a hyphen, it can only be a file to assemble
				// Try to load it
				if (!ilasm_includeFile_append(argv[lnI], NULL))
				{
					// Unable to load
					printf(cgc_unable_to_open_file, argv[lnI]);
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
		u32			lnI;
		SLasmFile*	file;


		// Iterate through every file, through every pass
		iterate (lnI, includeFiles, file, SLasmFile)
		//

			// Begin passes through each file
			for (lnPass = 0; lnPass < 6 && !lasm_is_completed(file->status); lnPass++)
			{
				// Identify the file on the first pass
				if (lnPass == 0)
					printf("--%s\n", file->filename.data_s8);

				// Dispatch the pass on this file
				switch (lnPass)
				{
					case 0:
						ilasm_pass0(cmdLine, file);

//////////
// // For debugging, write a temporary output of our contiguous file now
// SLine*		line;
// SBuilder*	b;
// b = NULL;
// iBuilder_createAndInitialize(&b);
// for (line = file->firstLine; line; line = line->ll.nextLine)
// {
// 	if (!ilasm_status_line_isCompleted(line))
// 	{
// 		iBuilder_appendData(b, line->sourceCode.data_u8, line->sourceCode.length);
// 		iBuilder_appendCrLf(b);
// 	}
// }
// iBuilder_asciiWriteOutFile(b, (cu8*)"c:\\temp\\out.txt");
// iBuilder_freeAndRelease(&b);
//////
						break;

					case 1:
						ilasm_pass1(cmdLine, file);
						break;

// 					case 2:		{	ilasm_pass2(cmdLine, file);		break;	}
// 					case 3:		{	ilasm_pass2(cmdLine, file);		break;	}
// 					case 4:		{	ilasm_passX(cmdLine, file);		break;	}
// 					case 5:		{	ilasm_passY(cmdLine, file);		break;	}
// 					case 6:		{	ilasm_passZ(cmdLine, file);		break;	}
				}
			}

		//
		iterate_end;
	}




//////////
//
// Called to append the indicated file to the known file chain,
// and also read in its file contents
//
//////
	bool ilasm_includeFile_append(s8* tcPathname, SLasmFile** file)
	{
		bool			llFound;
		u32				lnI;
		SLasmFile		fLoad;
		SLasmFile*		fNew;
		SLasmInclude*	include;
		s8*				filename_justfname;
		s8				filename[_MAX_PATH * 2];


		//////////
		// Initialize
		//////
			memset(&fLoad,		0, sizeof(fLoad));
			memset(filename,	0, sizeof(filename));


		//////////
		// Try to locate the #include file
		//////
			include = NULL;
			llFound = false;
			if ((u16)tcPathname[0] == '\\.')
			{
				// Relative path
				iterate(lnI, includePaths, include, SLasmInclude)
				//
					// Store the root path, then filename
					sprintf(filename,								include->filename.data_s8);
					sprintf(filename + include->filename.length,	tcPathname + 2);

					// Try to read the file contents
					if (iFile_readContents(tcPathname, &fLoad.fh, &fLoad.raw, &fLoad.rawLength))
					{
						llFound = true;
						break;
					}
				//
				iterate_end;

			} else {
				// It is a hard path, use it as is
				GetFullPathName(tcPathname, sizeof(filename), filename, &filename_justfname);
				if (iFile_readContents(tcPathname, &fLoad.fh, &fLoad.raw, &fLoad.rawLength))
					llFound = true;
			}


		//////////
		// Was it loaded?
		//////
			if (llFound)
			{
				// Parse into lines
				if (iFile_parseIntoLines(&fLoad.firstLine, fLoad.raw, fLoad.rawLength, sizeof(SLine)) > 0)
				{
					// Append our entry onto the chain
					fNew = (SLasmFile*)iBuilder_allocateBytes(includeFiles, sizeof(SLasmFile));
					if (fNew)
					{
						// Set the filename
						iDatum_duplicate(&fNew->filename, filename, strlen(filename));
						fNew->filename_justfname = fNew->filename.data_s8 + ((u32)filename_justfname - (u32)&filename[0]);

						// Copy over
						fNew->filenum		= (includeFiles->populatedLength / sizeof(SLasmFile));
						fNew->firstLine		= fLoad.firstLine;
						fNew->fh			= fLoad.fh;
						fNew->raw			= fLoad.raw;
						fNew->rawLength		= fLoad.rawLength;

						// Setup the #include file level
						fNew->include	= include;

						// Update the pointer if need be
						if (file)
							*file = fNew;

						// Add it as a possible include path
						ilasm_includePath_append(filename, strlen(filename), true);

						// Indicate success
						return(true);
					}
				}

			}
		
		
		//////////
		// Failure
		//////
			return(false);

	}




//////////
//
// Store the include file to a list of directories for later traversal should we
//
//////
	SLasmInclude* ilasm_includePath_append(s8* tcPathname, s32 tnPathnameLength, bool tlIsFilename)
	{
		u32				lnI, lnError;
		SLasmInclude*	include;
		s8*				fileNamePortion;


		// See if it already exists
		for (lnI = 0; lnI < includePaths->populatedLength; lnI += sizeof(SLasmInclude))
		{
			// Grab our pointer
			include = (SLasmInclude*)(includePaths->buffer + lnI);

			// Is it our filename?
			if (include->filename.length == tnPathnameLength && iDatum_compare(&include->filename, tcPathname, tnPathnameLength) == 0)
				return(include);
		}

		// If we get here, not found
		include = (SLasmInclude*)iBuilder_allocateBytes(includePaths, sizeof(SLasmInclude));
		if (include)
		{
			// Allocate enough space
			include->lIsFilename = false;
			iDatum_allocateSpace(&include->filename, _MAX_PATH + 32);

			// Expand to its full form
			fileNamePortion = NULL;
			if (!GetFullPathName(tcPathname, include->filename.length, include->filename.data_s8, &fileNamePortion))
				lnError = GetLastError();

			// Store the permanent length of whatever we're now using
			include->filename.length = strlen(tcPathname);

			// NULL-terminate
			if (tlIsFilename)
			{
				// Include the filename
				*fileNamePortion			= 0;						// Remove the path portion
				include->filenamePortion	= (s32)((uptr)fileNamePortion - (uptr)include->filename.data_s8);

			} else {
				// No filename portion
				include->filenamePortion = 0;

				// Validate that it has a trailing backslash
				ilasm_validate_trailingBackspace(include);
			}
		}

		// Indicate our result
		return(include);
	}




//////////
//
// For searching for files in the include path iteratively
//
//////
	void ilasm_includePaths_iterate_start(SLasmIncludeIter* iiFile, s8* filename)
	{
		s32 lnLength;


		// make sure our environment is sane
		if (iiFile)
		{
			// Initialize
			memset(iiFile, 0, sizeof(*iiFile));

			// Copy over the filename they indicate
			lnLength = strlen(filename);
			if (lnLength < sizeof(iiFile->filename) - 1)
			{
				// Copy and set the length
				memcpy(iiFile->filename, filename, lnLength);
				iiFile->filenameLength = lnLength;
			}
		}
	}

	bool ilasm_includePaths_iterate_try(SLasmIncludeIter* iiFile, bool& tlIsFileValid, SLasmFile** fileInclude)
	{
		s32				lnLength;
		SLasmInclude*	include;


		// Based on the current offset
		if (iiFile && iiFile->offset < includePaths->populatedLength)
		{
			//////////
			// Create the merged pathname
			//////
				iiFile->wasOpened	= false;
				include				= (SLasmInclude*)(includePaths->buffer + iiFile->offset);		// Copy the path from includePaths
				if (include->lIsFilename)
					return(false);		// This include file is not a pathname, but a filename, we can't use it

				// Copy the path
				memset(&iiFile->pathname, 0, sizeof(iiFile->pathname));
				memcpy(&iiFile->pathname, include->filename.data_s8, include->filename.length + 1);


			//////////
			// Append the file portion
			//////
				lnLength = strlen(iiFile->pathname);
				if (lnLength + iiFile->filenameLength < sizeof(iiFile->pathname) - 1)
				{
					// There's room to copy
					tlIsFileValid = true;
					memcpy(iiFile->pathname + lnLength, iiFile->filename, iiFile->filenameLength);

				} else {
					// Concatenated filename would be too big
					tlIsFileValid = false;
				}


			//////////
			// Try to open
			//////
				if (tlIsFileValid)
				{
					// Can we append the file?
					if (ilasm_includeFile_append(iiFile->pathname, fileInclude))
					{
						// It was opened successfully
						iiFile->wasOpened = true;

						// Indicate success
						return(true);
					}
				}

		}

		// Unsuccessful if we get here
		return(false);
	}

	bool ilasm_includePaths_iterate_next(SLasmIncludeIter* iiFile)
	{
		// Make sure our environment is sane
		if (iiFile)
		{
			// Is there enough room for another attempt?
			if (iiFile->offset + sizeof(SLasmInclude) < includePaths->populatedLength)
			{
				// Yes
				iiFile->offset += sizeof(SLasmInclude);
				return(true);
			}
		}

		// If we get here, we're done
		return(false);
	}




//////////
//
// For include files, makes sure that they have the trailing backspace
//
//////
	// Note:  include files also always allocate _MAX_PATH + 32 bytes for their filename size, so there's always room for the extra backslash
	SLasmInclude* ilasm_validate_trailingBackspace(SLasmInclude* include)
	{
		// Make sure the last character's a backspace
		if (include->filename.data_s8[include->filename.length - 1] != '\\')
		{
			// Make it a backslash
			include->filename.data_s8[include->filename.length] = '\\';

			// Increase its length
			++include->filename.length;
		}

		// Pass-thru our parameter
		return(include);
	}




//////////
//
// Called to adjust the slashes
//
//////
	void ilasm_fixup_directoryDividers(s8* tcPathname, s32 tnPathnameLength)
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




//////////
//
// Called to see if it's a file like "c:\path\to\file.txt" or if it's
// something like "relative\path\to\file.txt"
//
//////
	bool ilasm_isAbsolutePath(s8* tcPathname, s32 tnPathnameLength)
	{
		// Is it long enough to be an absolute path?
		if (tnPathnameLength >= 2)
		{
			// Test drive letter
			if (isAlpha(tcPathname[0]) && tcPathname[1] == ':')
			{
				// It's something like x:
				return(true);
			}

			// Test unc
			if (tcPathname[0] == '\\' && tcPathname[1] == '\\')
			{
				// It's something like \\server\...
				return(true);
			}

			// Test \path\to\file.txt
			if (tcPathname[0] == '\\')
				return(true);

			// If we get here, we assume it's a relative path
		}

		// It's too short to be an absolute path
		return(false);
	}




//////////
//
// Used for internal debugging, places where errors are not actively reported, but
// should never occur, but are occurring, are routed through here for debugging.
//
//////
	void ilasm_route_through_silentError_for_debugging(void)
	{
		// For debugging, errors that should not occur route through this function
		debug_nop;
	}




//////////
//
// Applies the status to the indicated component
//
//////
	void ilasm_status_comp_add(SComp* comp, u32 tnStatus)
	{
		// Make sure our environment is sane
		if (comp)
			comp->compStatus |= tnStatus;
	}




//////////
//
// Called to add the indicated status to the line, and optionally all of the line comps
//
//////
	void ilasm_status_line_add(SLine* line, u32 tnStatus, bool tlProcessComps)
	{
		SComp* comp;


		// Make sure our environment is sane
		if (line)
		{
			// Set the status
			line->lineStatus |= tnStatus;

			// Optionally process comps
			if (tlProcessComps)
			{
				// Iterate and set the status of each component
				for (comp = line->firstComp; comp; comp = comp->ll.nextComp)
					comp->compStatus |= tnStatus;
			}
		}
	}




//////////
//
// Called to see if the status is completed
//
//////
	bool ilasm_status_line_isCompleted(SLine* line)
	{
		// If there's no line, it's obviously done :-)
		if (!line)
			return(true);

		// If it's marked completed, it's done
		if ((line->lineStatus & _LASM_STATUS_COMPLETED) != 0)
			return(true);

		// If we get here, not done
		return(false);
	}




//////////
//
// Called to add the indicated status to the file, and optionally all of the lines and more optionally all the comps
//
//////
	void ilasm_status_file_add(SLasmFile* file, u32 tnStatus, bool tlProcessLines, bool tlProcessComps)
	{
		SLine* line;


		// Make sure our environment is sane
		if (file)
		{
			// Set the status
			file->status |= tnStatus;

			// Optionally process lines
			if (tlProcessLines)
			{
				// Iterate through each line
				for (line = file->firstLine; line; line = line->ll.nextLine)
					ilasm_status_line_add(line, tnStatus, tlProcessComps);
			}
		}
	}




//////////
//
// Called to extract parameters between two parenthesis
//
//////
	s32 iilasm_params_extract(SComp* compLeftParam, SBuilder** compParamsRoot, bool tlMoveBeyondLineIfNeeded)
	{
		s32				lnLevel;
		SComp*			comp;
		SComp*			compStart;
		SComp*			compEnd;
		SComp*			compLast;
		SLasmParam*		lp;
		SBuilder*		compParams;


		// We know we're sitting on a left parenthesis ( character
		*compParamsRoot = NULL;
		iBuilder_createAndInitialize(compParamsRoot);
		compParams = *compParamsRoot;

		// Scan forward looking for commas and right-parenthesis
		for (comp = iComps_Nth(compLeftParam, 1, tlMoveBeyondLineIfNeeded), lnLevel = 0, compStart = comp, compEnd = NULL, compLast = NULL; comp; comp = iComps_Nth(compLeftParam, 1, tlMoveBeyondLineIfNeeded))
		{
			// What are we sitting on?
			switch (comp->iCode)
			{
				case _ICODE_COMMA:
				case _ICODE_PARENTHESIS_RIGHT:
					if (lnLevel == 0)
					{
						// Everything up to the component before this is part of the parameter
						compEnd = compLast;

// TODO:  working here

						// If it's a right parenthesis, we're done
						if (comp->iCode == _ICODE_PARENTHESIS_RIGHT)
							break;
					}
					// else we just skip past
					break;

				default:
					// No code, just keep going
					break;
			}

			// Store this component as the last component we hit/touched
			compLast = comp;
		}

		// Indicate how many parameters were extracted
		return(compParams->populatedLength / sizeof(SLasmParam));
	}




//////////
//
// Called to create a token
//
//////
	bool iilasm_define_add(SLasmFile* file, SLine* line, SComp* compName, SBuilder* params, SComp* compStart, SComp* compEnd, SLasmDefine** defineOut)
	{
		u32				lnI;
		SLasmDefine*	define;
		s8				buffer[_MAX_PATH * 2];


		// Clear out the prior defineOut if any
		if (defineOut)
			*defineOut = NULL;

		// Search existing
		iterate(lnI, gsLasmDefinesRoot, define, SLasmDefine)
		//
			
			// Does the name already exist?
			if (define->name->text.length == compName->text.length && iDatum_compare(&define->name->text, &compName->text) == 0)
			{
				// Generate the error
				sprintf(buffer, "Error %%d (%d,%d): %%s at (%d,%d) in %s", 
								_LASM_ERROR_TOKEN_NAME_ALREADY_EXISTS,
								line->lineNumber, compName->start,
								define->name->line->lineNumber, define->name->start, file->filename.data_s8);

				// Report the error
				ilasm_error(_LASM_ERROR_TOKEN_NAME_ALREADY_EXISTS, buffer, line);
				debug_error;

				// Indicate failure
				return(false);
			}

		//
		iterate_end;

		// Allocate a new define record
		define = (SLasmDefine*)iBuilder_allocateBytes(gsLasmDefinesRoot, sizeof(SLasmDefine));
		if (define)
		{
			// Store
			define->name		= compName;
			define->params		= params;
			define->first		= compStart;
			define->last		= compEnd;
			define->firstLine	= compStart->line;

			// Update the point
			if (defineOut)
				*defineOut = define;
	
			// If we get here, success
			return(true);
		}

		// If we get here, failure
		return(false);
	}




//////////
//
// Called to add something to the indicated file, line, or component
//
//////
	void ilasm_append_extraInfo(s32 tnValueCode, s8* valueTextTemplate, SLine* line, SComp* comp, SLasmFile* file, s32 tnValueBaseAddto, s32 tn_eiType)
	{
		s32				lnLength;
		cs8*			lcErrorText;
		s8				buffer[1024];
		SExtraInfo*		ei;


		//////////
		// Grab the error message
		//////
			switch (tnValueCode)
			{
				case _LASM_ERROR_TOKEN_NAME_ALREADY_EXISTS:
					lcErrorText = cgc_lasm_error_token_name_already_exists;
					break;

				default:
					// Internal error (should never happen)
					ilasm_route_through_silentError_for_debugging();
					lcErrorText = cgc_lasm_error_unknown_error;
					break;
			}


		//////////
		// Generate the error
		//////
			sprintf(buffer, valueTextTemplate, tnValueCode + tnValueBaseAddto, lcErrorText);
			lnLength = strlen(buffer);


		//////////
		// Store the error
		//////
			     if (line)		ei = iExtraInfo_allocate(&line->extra_info, tn_eiType);
			else if (comp)		ei = iExtraInfo_allocate(&comp->extra_info, tn_eiType);
			else if (file)		ei = iExtraInfo_allocate(&file->extra_info, tn_eiType);


		//////////
		// Store the related error message
		//////
			if (ei)
				iDatum_duplicate(&ei->info, buffer);


		//////////
		// Print it
		//////
			printf(buffer);

			// Append a trailing CR if it doesn't already have one
			if (*(u16*)&buffer[lnLength - 2] != 'n\\' && *(u16*)&buffer[lnLength - 4] != 'n\\')
				printf("\n");

	}

	void ilasm_note(s32 tnNoteCode, s8* noteTextTemplate, SLine* line, SComp* comp, SLasmFile* file)
	{
		// Append the note
		ilasm_append_extraInfo(tnNoteCode, noteTextTemplate, line, comp, file, _LASM_NOTE_BASE, _EXTRA_INFO_NOTE);
	}

	void ilasm_warning(s32 tnWarningCode, s8* warningTextTemplate, SLine* line, SComp* comp, SLasmFile* file)
	{
		// Append the warning
		ilasm_append_extraInfo(tnWarningCode, warningTextTemplate, line, comp, file, _LASM_WARNING_BASE, _EXTRA_INFO_WARNING);
	}

	void ilasm_error(s32 tnErrorCode, s8* errorTextTemplate, SLine* line, SComp* comp, SLasmFile* file)
	{
		// Append the error
		ilasm_append_extraInfo(tnErrorCode, errorTextTemplate, line, comp, file, _LASM_ERROR_BASE, _EXTRA_INFO_ERROR);
	}
