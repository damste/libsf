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




//////////
//
// Main program entry point
//
//////
	#undef main

	s32 main(s32 argc, s8* argv[])
	{
		u32				lnPathnameLength;
		SLsaInclude*	include;
		SLsaCmdLine	cmdLine;
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
			iBuilder_createAndInitialize(&includePaths, sizeof(SLsaInclude) * 50);
			iBuilder_createAndInitialize(&includeFiles, sizeof(SLsaFile) * 50);

			// Grab the current directory (as our starting point)
			lnPathnameLength	= GetCurrentDirectory(sizeof(fileName) - 1, fileName);
			include				= ilsa_includePath_append(fileName, lnPathnameLength, false);


		//////////
		// Grab options
		//////
			ilsa_parse_commandLine(&cmdLine, argc, argv);


		//////////
		// Compile
		//////
			ilsa_compile(&cmdLine);


		// If we get here, success
		return(0);
	}




//////////
//
// Called to parse the command line and load its various parameters
//
//////
	void ilsa_parse_commandLine(SLsaCmdLine* cmdLine, s32 argc, s8* argv[])
	{
		bool	llSetValue;
		s32		lnI, lnLength;
		s8*		lcThisOption;
		s8*		lcIncludePath;


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
							cmdLine->w.Wmissing_type_ptr = llSetValue;
							break;

						} else if (ilsa_is_cmdLineOption(cgc_wall)) {
							// -Wall					-- Show all warnings
							// -Wno-all
							cmdLine->w.Wall = llSetValue;
							break;

						} else if (ilsa_is_cmdLineOption(cgc_wfatal_errors)) {
							// -Wfatal-errors			-- Should compilation stop immediately on first error?
							// -Wno-fatal-errors
							cmdLine->w.Wfatal_errors = llSetValue;
							break;

						} else if (ilsa_is_cmdLineOption(cgc_werror)) {
							// -Werror					-- Should warnings be treated as errors?
							// -Wno-error
							cmdLine->w.Werror = llSetValue;
							break;
						}
					
					
					//////////
					// Which options?
					//////
						if (ilsa_is_cmdLineOption(cgc_syntax_only))
						{
							// -fsyntax-only			-- Syntax check only
							cmdLine->o.lSyntax_only = llSetValue;
							break;

						} else if (ilsa_is_cmdLineOption(cgc_verbose)) {
							// -verbose					-- Show extra compilation information
							cmdLine->o.lVerbose = llSetValue;
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
				if (!ilsa_includeFile_append(argv[lnI], NULL))
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
	void ilsa_compile(SLsaCmdLine* cmdLine)
	{
		s32			lnPass;
		u32			lnI;
		SLsaFile*	file;


		// Iterate through every file, through every pass
		iterate(lnI, includeFiles, file, SLsaFile)
		//

			// Begin passes through each file
			for (lnPass = 0; lnPass < 6 && !ilsa_is_completed(file->status); lnPass++)
			{
				// Identify the file on the first pass
				if (lnPass == 0)
					printf("--%s\n", file->filename.data_s8);

				// Dispatch the pass on this file
				switch (lnPass)
				{
					case 0:
						ilsa_pass0(cmdLine, file);
						break;

					case 1:
						ilsa_pass1(cmdLine, file);
						break;

					case 2:
						ilsa_pass2(cmdLine, file);
						break;

// 					case 3:		{	ilsa_pass2(cmdLine, file);		break;	}
// 					case 4:		{	ilsa_passX(cmdLine, file);		break;	}
// 					case 5:		{	ilsa_passY(cmdLine, file);		break;	}
// 					case 6:		{	ilsa_passZ(cmdLine, file);		break;	}
				}

//////////
// For debugging, write a temporary output of our contiguous file now
//////
	SLine*		line;
	SBuilder*	b;
	b = NULL;
	iBuilder_createAndInitialize(&b);
	file = (SLsaFile*)includeFiles->buffer;
	for (line = file->firstLine; line; line = line->ll.nextLine)
	{
		// Uncompleted lines
		if (!ilsa_status_line_isCompleted(line))
		{
			iBuilder_appendData(b, line->sourceCode.data_u8, line->sourceCode.length);
			iBuilder_appendCrLf(b);
		}
	}
	iBuilder_asciiWriteOutFile(b, (cu8*)"c:\\temp\\out_undone.txt");

	// Do the completed lines
	b->populatedLength = 0;
	for (line = file->firstLine; line; line = line->ll.nextLine)
	{
		// Completed lines
		if (ilsa_status_line_isCompleted(line))
		{
			iBuilder_appendData(b, line->sourceCode.data_u8, line->sourceCode.length);
			iBuilder_appendCrLf(b);
		}
	}
	iBuilder_asciiWriteOutFile(b, (cu8*)"c:\\temp\\out_done.txt");
	iBuilder_freeAndRelease(&b);
//////
// END
//////////
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
	bool ilsa_includeFile_append(s8* tcPathname, SLsaFile** file)
	{
		bool			llFound;
		u32				lnI;
		SLsaFile		fLoad;
		SLsaFile*		fNew;
		SLsaInclude*	include;
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

			// Try to open it as is
			GetFullPathName(tcPathname, sizeof(filename), filename, &filename_justfname);
			if (iFile_readContents(tcPathname, &fLoad.fh, &fLoad.raw, &fLoad.rawLength))
			{
				// Good! :-)
				llFound = true;

			} else {
				// Search relative to the paths we've encountered thus far
				iterate(lnI, includePaths, include, SLsaInclude)
				//

					// Store the path, then filename
					sprintf(filename,								include->filename.data_s8);
					sprintf(filename + include->filename.length,	"%s", tcPathname);

					// Try to read the file contents
					if (iFile_readContents(filename, &fLoad.fh, &fLoad.raw, &fLoad.rawLength))
					{
						llFound = true;
						break;
					}

				//
				iterate_end;
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
					fNew = (SLsaFile*)iBuilder_allocateBytes(includeFiles, sizeof(SLsaFile));
					if (fNew)
					{
						// Set the filename
						iDatum_duplicate(&fNew->filename, (cvp*)filename, strlen(filename));
						fNew->filename_justfname = fNew->filename.data_s8 + ((u32)filename_justfname - (u32)&filename[0]);

						// Copy over
						fNew->filenum		= (includeFiles->populatedLength / sizeof(SLsaFile));
						fNew->firstLine		= fLoad.firstLine;
						fNew->fh			= fLoad.fh;
						fNew->raw			= fLoad.raw;
						fNew->rawLength		= fLoad.rawLength;

						// Setup the #include file level
						fNew->include		= include;

						// Update the pointer if need be
						if (file)
							*file = fNew;

						// Add it as a possible include path
						ilsa_includePath_append(filename, strlen(filename), true);

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
	SLsaInclude* ilsa_includePath_append(s8* tcPathname, s32 tnPathnameLength, bool tlIsFilename)
	{
		u32				lnI, lnError, lnLength;
		SLsaInclude*	include;
		s8*				fileNamePortion;
		s8				buffer[_MAX_PATH];


		// Expand to its full form
		fileNamePortion = NULL;
		if (!GetFullPathName(tcPathname, sizeof(buffer), buffer, &fileNamePortion))
			lnError = GetLastError();

		// NULL-terminate to remove the filename
		if (tlIsFilename && fileNamePortion)
			*fileNamePortion = 0;

		// Grab the length given by GetFullPathName(), and adjusted by removing the path
		lnLength = strlen(buffer);

		// Validate it has a trailing backslash
		lnLength += ilsa_validate_trailingBackspace(buffer, lnLength);
		buffer[lnLength] = 0;

		// See if it already exists
		for (lnI = 0; lnI < includePaths->populatedLength; lnI += sizeof(SLsaInclude))
		{
			// Grab our pointer
			include = (SLsaInclude*)(includePaths->buffer + lnI);

			// Is it our filename?
			if (include->filename.length == lnLength && iDatum_compare(&include->filename, buffer, lnLength) == 0)
				return(include);
		}

		// If we get here, not found
		include = (SLsaInclude*)iBuilder_allocateBytes(includePaths, sizeof(SLsaInclude));
		if (include)
			iDatum_duplicate(&include->filename, buffer, lnLength);

		// Indicate our result
		return(include);
	}




//////////
//
// For searching for files in the include path iteratively
//
//////
	void ilsa_includePaths_iterate_start(SLsaIncludeIter* iiFile, s8* filename)
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

	bool ilsa_includePaths_iterate_try(SLsaIncludeIter* iiFile, bool& tlIsFileValid, SLsaFile** fileInclude)
	{
		s32				lnLength;
		SLsaInclude*	include;


		// Based on the current offset
		if (iiFile && iiFile->offset < includePaths->populatedLength)
		{
			//////////
			// Create the merged pathname
			//////
				iiFile->wasOpened	= false;
				include				= (SLsaInclude*)(includePaths->buffer + iiFile->offset);		// Copy the path from includePaths

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
					if (ilsa_includeFile_append(iiFile->pathname, fileInclude))
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

	bool ilsa_includePaths_iterate_next(SLsaIncludeIter* iiFile)
	{
		// Make sure our environment is sane
		if (iiFile)
		{
			// Is there enough room for another attempt?
			if (iiFile->offset + sizeof(SLsaInclude) < includePaths->populatedLength)
			{
				// Yes
				iiFile->offset += sizeof(SLsaInclude);
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
	s32 ilsa_validate_trailingBackspace(s8* tcPathname, s32 tnPathnameLength)
	{
		// Make sure the last character's a backspace
		if (tcPathname[tnPathnameLength - 1] != '\\')
		{
			// Make it a backslash
			tcPathname[tnPathnameLength] = '\\';

			// Increase its length
			return(1);
		}

		// Nothing was added
		return(0);
	}




//////////
//
// Called to adjust the slashes
//
//////
	void ilsa_fixup_directoryDividers(s8* tcPathname, s32 tnPathnameLength)
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
	bool ilsa_isAbsolutePath(s8* tcPathname, s32 tnPathnameLength)
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
	void ilsa_route_through_silentError_for_debugging(void)
	{
		// For debugging, errors that should not occur route through this function
		debug_nop;
	}




//////////
//
// Applies the status to the indicated component
//
//////
	void ilsa_status_comp_add(SComp* comp, u32 tnStatus)
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
	void ilsa_status_line_add(SLine* line, u32 tnStatus, bool tlProcessComps)
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
	bool ilsa_status_comp_isCompleted(SComp* comp)
	{
		// If there's no comp, it's obviously done :-)
		if (!comp)
			return(true);

		// If it's marked completed, it's done
		if ((comp->compStatus & _LSA_STATUS_COMPLETED) != 0)
			return(true);

		// If we get here, not done
		return(false);
	}




//////////
//
// Called to see if the status is completed
//
//////
	bool ilsa_status_line_isCompleted(SLine* line)
	{
		// If there's no line, it's obviously done :-)
		if (!line)
			return(true);

		// If it's marked completed, it's done
		if ((line->lineStatus & _LSA_STATUS_COMPLETED) != 0)
			return(true);

		// If we get here, not done
		return(false);
	}




//////////
//
// Called to add the indicated status to the file, and optionally all of the lines and more optionally all the comps
//
//////
	void ilsa_status_file_add(SLsaFile* file, u32 tnStatus, bool tlProcessLines, bool tlProcessComps)
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
					ilsa_status_line_add(line, tnStatus, tlProcessComps);
			}
		}
	}




//////////
//
// Called to extract parameters...
//
//////
	// Note:  This function generates the *paramsRoot builder (if there were any parameters) ... it will have to be deleted manually by caller
	// ...beginning at the parameter after the parenthesis, and then between the two parenthesis
	s32 iilsa_params_parentheticalExtract(SComp* compLeftParam, SBuilder** paramsRoot, bool tlMoveBeyondLineIfNeeded)
	{
		return(iilsa_params_extract_common(iComps_Nth(compLeftParam, 1, tlMoveBeyondLineIfNeeded), paramsRoot, tlMoveBeyondLineIfNeeded, _ICODE_PARENTHESIS_RIGHT));
	}

	// ...beginning where we are to the end of the line
	s32 iilsa_params_commaDelimitedExtract(SComp* compFirstParam, SBuilder** paramsRoot, bool tlVerifySingleParams, bool* tlIsSingleParam)
	{
		s32				lnResult;
		u32				lnI;
		SLsaParam*		param;


		// Get our parameters
		lnResult = iilsa_params_extract_common(compFirstParam, paramsRoot, false, _ICODE_NU);
		if (lnResult > 0 && *paramsRoot && tlVerifySingleParams && tlIsSingleParam)
		{
			// Make sure each parameter is single
			*tlIsSingleParam = true;	// Assume success
			iterate(lnI, (*paramsRoot), param, SLsaParam)
			//

				// Is this parameter single?
				if (param->start != param->end)
				{
					// No
					*tlIsSingleParam = false;
					break;
				}
			//
			iterate_end;
		}

		// Indicate our result
		return(lnResult);
	}




//////////
//
// Common comma-delimited parameter extraction algorithm
//
//////
	s32 iilsa_params_extract_common(SComp* compFirstParam, SBuilder** paramsRoot, bool tlMoveBeyondLineIfNeeded, s32 tniStopCode)
	{
		bool			llStoreStart;
		s32				lnLevel;
		SComp*			comp;
		SComp*			compStart;
		SComp*			compEnd;
		SComp*			compLast;
		SLsaParam*		param;
		SBuilder*		params;


		// We know we're sitting on a left parenthesis ( character
		if (*paramsRoot == NULL)
			iBuilder_createAndInitialize(paramsRoot);
		
		if (!*paramsRoot)
			return(0);

		// Grab our param in a more manageable form
		params = *paramsRoot;

		// Scan forward looking for commas and right-parenthesis
		for (lnLevel = 0, comp = compFirstParam, compEnd = NULL, compLast = NULL, llStoreStart = true; comp; comp = iComps_Nth(comp, 1, tlMoveBeyondLineIfNeeded))
		{
			// Store the starting component (if we need to)
			if (llStoreStart)
			{
				llStoreStart	= false;
				compStart		= comp;
			}

			// Are we at the terminating code?
			if (comp->iCode == tniStopCode || (!tlMoveBeyondLineIfNeeded && !comp->ll.nextComp))
			{
				// Make sure we can populate the end
				if (!compLast)
					compLast = compStart;

				// Process
				goto end_of_parameter;
			}

			// What are we sitting on?
			switch (comp->iCode)
			{
				case _ICODE_COMMA:
end_of_parameter:
					if (lnLevel == 0)
					{
						// Everything up to the component before this is part of the parameter
						compEnd = compLast;

						// Add a new record
						param = (SLsaParam*)iBuilder_allocateBytes(params, sizeof(SLsaParam));
						if (param)
						{
							// Populate this record
							param->start	= compStart;
							param->end		= compEnd;

							// Create the name parameter
							if (param->start == param->end)		iDatum_duplicate(&param->name, &param->start->text);
							else								iDatum_duplicate(&param->name, cgc_lsa_group);
						}

						// Reset the end and prepare for next iteration
						llStoreStart	= true;
						compEnd			= NULL;
					}
					// else we just skip past
					break;

				default:
					// No code, just keep going
					break;
			}

			// If it's the terminating code, we're done
			if (comp->iCode == tniStopCode || (!tlMoveBeyondLineIfNeeded && !comp->ll.nextComp))
				break;

			// Store this component as the last component we hit/touched
			compLast = comp;
		}

		// Indicate how many parameters were extracted
		if (params->populatedLength == 0)
		{
			// Nothing was selected, reset the params array
			iBuilder_freeAndRelease(paramsRoot);

			// No parameters
			return(0);

		} else {
			// Indicate the count
			return(params->populatedLength / sizeof(SLsaParam));
		}
	}




//////////
//
// Called to create a token
//
//////
	bool iilsa_dmac_add(SLsaFile* file, SLine* line, SComp* compName, SBuilder* params, SComp* compStart, SComp* compEnd, bool tlIsDefine, SLsaDMac** dmOut)
	{
		u32			lnI;
		SLsaDMac*	dm;
		s8			buffer[_MAX_PATH * 2];


		// Clear out the prior defineOut if any
		if (dmOut)
			*dmOut = NULL;

		// Make sure we have at least one define
		if (!gsLsaDMacRoot)
			iBuilder_createAndInitialize(&gsLsaDMacRoot);

		// Search existing
		iterate(lnI, gsLsaDMacRoot, dm, SLsaDMac)
		//
			
			// Does the name already exist?
			if (dm->name->text.length == compName->text.length && iDatum_compare(&dm->name->text, &compName->text) == 0)
			{
				// Generate the error
				sprintf(buffer, "Error %%d [%d,%d]: '%s' %%s, see [%d,%d] of %s", 
								line->lineNumber, compName->start,
								compName->text.data_s8,
								dm->name->line->lineNumber, dm->name->start, file->filename.data_s8);

				// Report the error
				ilsa_error(_LSA_ERROR_TOKEN_NAME_ALREADY_EXISTS, buffer, line);

				// Indicate failure
				return(false);
			}

		//
		iterate_end;

		// Allocate a new define record
		dm = (SLsaDMac*)iBuilder_allocateBytes(gsLsaDMacRoot, sizeof(SLsaDMac));
		if (dm)
		{
			// Store
			dm->file	= file;				// The associated file
			dm->line	= line;				// The line related
			dm->name	= compName;			// Token name
			dm->params	= params;			// Parameters (if any)
			dm->first	= compStart;		// First component related to the token (if any)
			dm->last	= compEnd;			// Last component related to the token (if any)

			// Update the point
			if (dmOut)
				*dmOut = dm;
	
			// If we get here, success
			return(true);
		}

		// If we get here, failure
		return(false);
	}




//////////
//
// Called to parse through the define/macro structures to unfurl their coding
// requirements into little segments which are either raw texts to copy, or
// parameters
//
//////
	void ilsa_dmac_unfurl(SLsaDMac* dm)
	{
		bool			llHasParams, llPrefixCrLf;
		s32				lnWhitespaces, lnParamNumber;
		u32				lnI;
		SComp*			comp;
		SComp*			compLast;
		SBuilder*		tbuilder;
		SLsaParam*		param;
		s8				buffer[1024];


		// Make sure our environment is sane
		if (dm)
		{
			// Create a builder
			tbuilder = NULL;
			iBuilder_createAndInitialize(&tbuilder);

			// If no parameters, store all as text
			llHasParams = (dm->params && dm->params->populatedLength > 0);
			
			// Iterate through every component one by one
			for (comp = dm->first, compLast = NULL; comp; comp = iComps_Nth(comp))
			{
				// Are we still on the same line?
				llPrefixCrLf = (compLast && compLast->line != comp->line);

				// Whitespaces or inter-component spacing
				     if (llPrefixCrLf)		lnWhitespaces = comp->start;
				else if (compLast)			lnWhitespaces = ((llPrefixCrLf) ? comp->start : comp->start - (compLast->start + compLast->text.length));
				else						lnWhitespaces = 0;

				// Search this component for a param name
				if (llHasParams && iiComps_isAlphanumeric_by_iCode(comp->iCode) && dm->params && iilsa_dmac_searchParams(dm->params, &comp->text, lnParamNumber, &param))
				{
					// A single name, which means we use this parameter
					++param->nRefCount;
					iilsa_dmac_unfurl_addParameter(&dm->expansion_steps, lnParamNumber, &param->name, lnWhitespaces, llPrefixCrLf, tbuilder);

				} else {
					// Append it as is as text
					iilsa_dmac_unfurl_addText(&dm->expansion_steps, &comp->text, lnWhitespaces, llPrefixCrLf, tbuilder);
				}

				// Was this component the last one for the blocK?
				if (comp == dm->last)
					break;	// Yes

				// Prepare for the next component
				compLast = comp;
			}

			// Iterate through the params and make sure all were referenced
			if (llHasParams)
			{
				// Check ref counts
				iterate(lnI, dm->params, param, SLsaParam)
				//

					// Generate a warning if it's an unreferenced parameter
					if (param->name._data && param->name.length > 0 && param->nRefCount == 0)
					{
						// Display unreferenced parameter
						sprintf(buffer, "Warning %%d [%d,%d]: '%s' %%s, see [%d,%d] define/macro '%s' of %s", 
										param->start->line->lineNumber, param->start->start,
										param->name.data_s8,
										dm->name->line->lineNumber, dm->name->start,
										dm->name->text.data_s8,
										dm->file->filename.data_s8);

						// Report the warning
						ilsa_warning(_LSA_WARNING_UNREFERENCED_PARAMETER, buffer, param->start->line, param->start, dm->file);
					}

				//
				iterate_end;

			}

			// Release the builder
			iBuilder_freeAndRelease(&tbuilder);
		}
	}

	// Search for the indicated name
	bool iilsa_dmac_searchParams(SBuilder* params, SDatum* text, s32& tnParamNumber, SLsaParam** paramOut)
	{
		s32			lnParamNumber;
		u32			lnI;
		SLsaParam*	param;


		// Iterate through the parameters looking for this name
		lnParamNumber = 0;
		iterate_with_count(lnI, params, param, SLsaParam, lnParamNumber)
		//

			// Right size?
			if (param->start == param->end && param->start->text.length == text->length)
			{
				// Text match?
				if (param->start->text.length == text->length && iDatum_compare(&param->start->text, text) == 0)
				{
					// This is it
					if (paramOut)
						*paramOut = param;

					// Indicate the number
					tnParamNumber = lnParamNumber;

					// And success
					return(true);
				}
			}

		//
		iterate_end;

		// If we get here, not found
		return(false);
	}

	// Make sure we have a builder
	SBuilder* iilsa_dmac_unfurl_validateBuilder(SBuilder** expansion_stepsRoot)
	{
		// Make sure we have a pointer to builder
		if (expansion_stepsRoot)
		{
			// Default to 20 entries
			if (!*expansion_stepsRoot)
				iBuilder_createAndInitialize(expansion_stepsRoot, sizeof(SLsaExpansion) * 20);

			// Indicate status
			return(*expansion_stepsRoot);
		}

		// If we get here, failure
		return(NULL);
	}

	// Called to add the parameter
	SLsaExpansion* iilsa_dmac_unfurl_addParameter(SBuilder** expansion_stepsRoot, s32 tnParamNum, SDatum* name, s32 tnWhitespaces, bool tlPrefixCrLf, SBuilder* tbuilder)
	{
		SBuilder*		expansion_stepsBuilder;
		SLsaExpansion*	exp;


		// Store text to prefix before the parameter
		if (tnWhitespaces != 0 || tlPrefixCrLf)
			iilsa_dmac_unfurl_addText(expansion_stepsRoot, NULL, tnWhitespaces, tlPrefixCrLf, tbuilder);

		// Make sure we have a builder
		exp = NULL;
		if ((expansion_stepsBuilder = iilsa_dmac_unfurl_validateBuilder(expansion_stepsRoot)))
		{
			// Create a new entry
			exp = (SLsaExpansion*)iBuilder_allocateBytes(*expansion_stepsRoot, sizeof(SLsaExpansion));
			if (exp)
			{
				iDatum_duplicate(&exp->name, name);
				exp->nParamNum = tnParamNum + 1;	// Store the parameter
			}
		}

		// Indicate the expansion record
		return(exp);
	}

	// Called to add text from a sequence of components
	SLsaExpansion* iilsa_dmac_unfurl_addText(SBuilder** expansion_stepsRoot, SDatum* text, s32 tnWhitespaces, bool tlPrefixCrLf, SBuilder* tbuilder)
	{
		SBuilder*		expansion_stepsBuilder;
		SLsaExpansion*	exp;


		// Make sure we have a builder
		exp = NULL;
		if ((expansion_stepsBuilder = iilsa_dmac_unfurl_validateBuilder(expansion_stepsRoot)))
		{
			// Create a new entry
			exp = (SLsaExpansion*)iBuilder_allocateBytes(expansion_stepsBuilder, sizeof(SLsaExpansion));
			if (exp)
			{
				// Reset the builder
				tbuilder->populatedLength = 0;

				// Prefix with anything?
				if (tlPrefixCrLf)			iBuilder_appendCrLf(tbuilder);
				if (tnWhitespaces > 0)		iBuilder_appendWhitespaces(tbuilder, tnWhitespaces);

				// Append the text
				if (text)
					iBuilder_appendData(tbuilder, text);

				// Copy to the expansion entry
				iDatum_duplicate(&exp->text, tbuilder->data_cvp, (s32)tbuilder->populatedLength);
			}
		}

		// Indicate the expansion record
		return(exp);
	}




//////////
//
// Performs a search for the indicated macro
//
//////
	bool ilsa_dmac_find_byComp(SComp* comp, SLsaDMac** dmOut)
	{
		u32			lnI;
		SLsaDMac*	dm;


		// Iterate through the global define/macro entries
		iterate(lnI, gsLsaDMacRoot, dm, SLsaDMac)
		//

			// Is it the same length name?
			if (dm->name->text.length == comp->text.length)
			{
				// Is it the token name?
				if (iDatum_compare(&dm->name->text, &comp->text) == 0)
				{
					// This is the token
					if (dmOut)
						*dmOut = dm;

					// Indicate success
					return(true);
				}
			}

		//
		iterate_end;

		// If we get here, not found
		return(false);
	}




//////////
//
// Called to add something to the indicated file, line, or component
//
//////
	// Note:  valueTextTemplate is expected to include a %d parameter for tnValueCode, and a %s parameter for the associated text
	void ilsa_append_extraInfo(s32			tnValueCode,
								cs8*		valueTextTemplate,
								cs8*		tcValueText,
								SLine*		line,
								SComp*		comp,
								SLsaFile*	file,
								s32			tnValueBaseAddto,
								s32			tn_eiType)
	{
		s32				lnLength;
		s8				buffer[1024];
		SExtraInfo*		ei;


		//////////
		// Generate the error
		//////
			sprintf(buffer, valueTextTemplate, tnValueCode + tnValueBaseAddto, tcValueText);
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
				iDatum_duplicate(&ei->info, (cvp*)buffer);


		//////////
		// Print it
		//////
			printf(buffer);

			// Append a trailing CR if it doesn't already have one
			if (*(u16*)&buffer[lnLength - 2] != 'n\\' && *(u16*)&buffer[lnLength - 4] != 'n\\')
				printf("\n");

	}

	// Note:  noteTextTemplate is expected to include a %d parameter for tnErrorCode, and a %s parameter for the associated error text
	void ilsa_note(s32 tnNoteCode, cs8* noteTextTemplate, SLine* line, SComp* comp, SLsaFile* file)
	{
		cs8* lcNoteText;


		//////////
		// Grab the error message
		//////
			switch (tnNoteCode)
			{
				default:
					// Internal error (should never happen)
					ilsa_route_through_silentError_for_debugging();
					lcNoteText = cgc_lsa_note_unknown_note;
					break;
			}


		//////////
		// Append the warning
		//////
			ilsa_append_extraInfo(tnNoteCode, noteTextTemplate, lcNoteText, line, comp, file, _LSA_NOTE_BASE, _EXTRA_INFO_NOTE);

	}

	// Note:  warningTextTemplate is expected to include a %d parameter for tnErrorCode, and a %s parameter for the associated error text
	void ilsa_warning(s32 tnWarningCode, cs8* warningTextTemplate, SLine* line, SComp* comp, SLsaFile* file)
	{
		cs8* lcWarningText;


		//////////
		// Grab the error message
		//////
			switch (tnWarningCode)
			{
				case _LSA_WARNING_UNREFERENCED_PARAMETER:
					lcWarningText = cgc_lsa_warning_unreferenced_parameter;
					break;

				default:
					// Internal error (should never happen)
					ilsa_route_through_silentError_for_debugging();
					lcWarningText = cgc_lsa_warning_unknown_warning;
					break;
			}


		//////////
		// Append the warning
		//////
			ilsa_append_extraInfo(tnWarningCode, warningTextTemplate, lcWarningText, line, comp, file, _LSA_WARNING_BASE, _EXTRA_INFO_WARNING);

	}

	// Note:  errorTextTemplate is expected to include a %d parameter for tnErrorCode, and a %s parameter for the associated error text
	void ilsa_error(s32 tnErrorCode, cs8* errorTextTemplate, SLine* line, SComp* comp, SLsaFile* file)
	{
		cs8* lcErrorText;


		//////////
		// Grab the error message
		//////
			switch (tnErrorCode)
			{
				case _LSA_ERROR_TOKEN_NAME_ALREADY_EXISTS:
					lcErrorText = cgc_lsa_error_token_name_already_exists;
					break;

				default:
					// Internal error (should never happen)
					ilsa_route_through_silentError_for_debugging();
					lcErrorText = cgc_lsa_error_unknown_error;
					break;
			}


		//////////
		// Append the error
		//////
			ilsa_append_extraInfo(tnErrorCode, errorTextTemplate, lcErrorText, line, comp, file, _LSA_ERROR_BASE, _EXTRA_INFO_ERROR);

	}
