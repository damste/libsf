//////////
//
// /libsf/exodus/tools/lsa/lsa_include.cpp
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
// Called to append the indicated file to the known file chain,
// and also read in its file contents
//
//////
	bool ilsa_includeFile_append(s8* tcPathname, SLsaFile** file)
	{
		bool			llFound;
		u32				lnI;
		SLsaFile		fileLoad;
		SLsaFile*		fileNew;
		SLsaInclude*	include;
		SLine*			line;
		s8*				filename_justfname;
		s8				filename[_MAX_PATH * 2];


		//////////
		// Initialize
		//////
			memset(&fileLoad,		0, sizeof(fileLoad));
			memset(filename,	0, sizeof(filename));


		//////////
		// Try to locate the #include file
		//////
			include = NULL;
			llFound = false;

			// Try to open it as is
			GetFullPathName(tcPathname, sizeof(filename), filename, &filename_justfname);
			if (iFile_readContents(tcPathname, &fileLoad.fh, &fileLoad.raw, &fileLoad.rawLength))
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
					if (iFile_readContents(filename, &fileLoad.fh, &fileLoad.raw, &fileLoad.rawLength))
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
				if (iFile_parseIntoLines(&fileLoad.firstLine, fileLoad.raw, fileLoad.rawLength, sizeof(SLine)) > 0)
				{
					// Append our entry onto the chain
					fileNew = (SLsaFile*)iBuilder_allocateBytes(includeFiles, sizeof(SLsaFile));
					if (fileNew)
					{
						// Set the filename
						iDatum_duplicate(&fileNew->filename, (cvp*)filename, strlen(filename));
						fileNew->filename_justfname = fileNew->filename.data_s8 + ((u32)filename_justfname - (u32)&filename[0]);

						// Copy over
						fileNew->filenum	= (includeFiles->populatedLength / sizeof(SLsaFile));
						fileNew->firstLine	= fileLoad.firstLine;
						fileNew->fh			= fileLoad.fh;
						fileNew->raw		= fileLoad.raw;
						fileNew->rawLength	= fileLoad.rawLength;

						// Setup the #include file level
						fileNew->include	= include;

						// Update the pointer if need be
						if (file)
							*file = fileNew;

						// Mark each line with the file it belongs to
						for (line = fileNew->firstLine; line; line = line->ll.nextLine)
							line->file = fileNew;

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
