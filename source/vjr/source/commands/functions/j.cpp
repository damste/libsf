//////////
//
// /libsf/source/vjr/commands/funcs/j.cpp
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
// Copyright (c) 2014 by Rick C. Hodgin
//////
// Last update:
//     Jul.05.2014
//////
// Change log:
//     Jul.05.2014 - Initial creation
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
//
// To add a new function, see the instructions in command_defs.h.
//
//




//////////
//
// Function: JUSTDRIVE()
// Returns the drive letter from the input pathname
//
//////
// Version 0.58
// Last update:
//		Dec.25.2014
//////
// Change log:
//		Dec.25.2014 - Initial creation
//////
// Parameters:
//		varString		-- Character, the input pathname
//////
// Returns:
//		Character		-- The drive component of the pathname, or the current drive if it wasn't specified, ("c:" of "c:\path\to\sample.txt")
//////
	void function_justdrive(SReturnsParams* rpar)
	{
		SVariable*	varString = rpar->ip[0];
		u8*			ptr;
        SVariable*	result;


		//////////
		// Parameter 1 must be character
		//////
			rpar->rp[0] = NULL;
			if (!iVariable_isValid(varString) || !iVariable_isTypeCharacter(varString))
			{
				iError_report_byNumber(_ERROR_P1_IS_INCORRECT, iVariable_get_relatedComp(varString), false);
				return;
			}


		//////////
        // Based on its type, process it accordingly
		//////
			result = iVariable_create(_VAR_TYPE_CHARACTER, NULL, true);
			if (!result)
			{
				iError_report(cgcInternalError, false);
				return;
			}

			if (varString->value.length >= 2)
			{
				// If it is of the form "x:"... then we return the left two-most characters
				if (varString->value.data_s8[1] == ':')
				{
					// We have a drive
					ptr = varString->value.data_u8;
				}

			} else {
				// It's too short and cannot have a drive, so we'll initialize an empty variable
				ptr = NULL;
			}


		//////////
		// Populate if need be
		//////
			if (ptr)
				iDatum_duplicate(&result->value, ptr, 2);


		//////////
        // Return our converted result
		//////
			rpar->rp[0] = result;

	}




//////////
//
// Function: JUSTEXT()
// Returns the file extension from the input pathname
//
//////
// Version 0.58
// Last update:
//		Dec.25.2014
//////
// Change log:
//      Apr.02.2015 - Refactoring
//		Dec.25.2014 - Initial creation
//////
// Parameters:
//		varString		-- Character, the input pathname
//////
// Returns:
//		Character		-- The file extension component, or an empty string if one was not specified, ("txt" of "c:\path\to\sample.txt")
//////
	void function_justext(SReturnsParams* rpar)
	{
		SVariable*	varString = rpar->ip[0];
		s32			lnI, lnLength;
		u8*			ptr;
        SVariable*	result;


		//////////
		// Parameter 1 must be character
		//////
			rpar->rp[0] = NULL;
			if (!iVariable_isValid(varString) || !iVariable_isTypeCharacter(varString))
			{
				iError_report_byNumber(_ERROR_P1_IS_INCORRECT, iVariable_get_relatedComp(varString), false);
				return;
			}


		//////////
        // Based on its type, process it accordingly
		//////
			ptr = NULL;
			if (varString->value.length >= 1)
			{
				// Iterate backwards until we find a period.
				// If no period is found, use a blank string
				for (lnI = varString->value.length - 1, lnLength = 0; lnI > 0; lnI--, lnLength++)
				{
					if (varString->value.data_u8[lnI] == '.')
					{
						// We found a period
						ptr = varString->value.data_u8 + lnI + 1;
						break;
					}
				}
			}


		//////////
		// Populate if need be
		//////
			if (!ptr)
			{
				// Create a blank string
				result = iVariable_create(_VAR_TYPE_CHARACTER, NULL, true);

			} else {
				// Create and copy our portion
				result = iVariable_createAndPopulate_byText(_VAR_TYPE_CHARACTER, ptr, lnLength, false);
			}


		//////////
		// Are we good?
		//////
			if (!result)
				iError_report(cgcInternalError, false);


		//////////
        // Return our converted result
		//////
			rpar->rp[0] = result;

	}




//////////
//
// Function: JUSTFNAME()
// Returns the file name from the input pathname
//
//////
// Version 0.58
// Last update:
//		Dec.25.2014
//////
// Change log:
//		Dec.25.2014 - Initial creation
//////
// Parameters:
//		varString		-- Character, the input pathname
//////
// Returns:
//		Character		-- The file name portion of the pathname ("sample.txt" of "c:\path\to\sample.txt")
//////
	void function_justfname(SReturnsParams* rpar)
	{
		SVariable*	varString = rpar->ip[0];
		s32			lnI, lnLength;
		u8*			ptr;
        SVariable*	result;


		//////////
		// Parameter 1 must be character
		//////
			if (!iVariable_isValid(varString) || !iVariable_isTypeCharacter(varString))
			{
				iError_report_byNumber(_ERROR_P1_IS_INCORRECT, iVariable_get_relatedComp(varString), false);
				return;
			}


		//////////
        // Based on its type, process it accordingly
		//////
			ptr = NULL;
			if (varString->value.length >= 1)
			{
				// Iterate backwards until we find a period.
				// If no period is found, use a blank string
				for (lnI = varString->value.length - 1, lnLength = 0; lnI > 0; lnI--, lnLength++)
				{
					if (varString->value.data_u8[lnI] == '\\')
					{
						// We found a backslash
						break;
					}
				}

				// Set our pointer to the filename
				ptr			= varString->value.data_u8 + lnI + ((lnI > 0) ? 1 : 0);
				lnLength	+= ((lnI > 0) ? 0 : 1);
			}


		//////////
		// Populate if need be
		//////
			if (!ptr)
			{
				// Create a blank string
				result = iVariable_create(_VAR_TYPE_CHARACTER, NULL, true);

			} else {
				// Create and copy our portion
				result = iVariable_createAndPopulate_byText(_VAR_TYPE_CHARACTER, ptr, lnLength, false);
			}


		//////////
		// Are we good?
		//////
			if (!result)
				iError_report(cgcInternalError, false);


		//////////
        // Return our converted result
		//////
			rpar->rp[0] = result;

	}




//////////
//
// Function: JUSTPATH()
// Returns the path from the input pathname
//
//////
// Version 0.58
// Last update:
//		Apr.02.2015
//////
// Change log:
//      Apr.02.2015 - Refactoring
//		Dec.25.2014 - Initial creation
//////
// Parameters:
//		varString		-- Character, the input pathname
//////
// Returns:
//		Character		-- The file path of the pathname ("c:\path\to" of "c:\path\to\sample.txt")
//////
	void function_justpath(SReturnsParams* rpar)
	{
		SVariable*	varString = rpar->ip[0];
		s32			lnLength;
		u8*			ptr;
        SVariable*	result;


		//////////
		// Parameter 1 must be character
		//////
			rpar->rp[0] = NULL;
			if (!iVariable_isValid(varString) || !iVariable_isTypeCharacter(varString))
			{
				iError_report_byNumber(_ERROR_P1_IS_INCORRECT, iVariable_get_relatedComp(varString), false);
				return;
			}


		//////////
        // Based on its type, process it accordingly
		//////
			ptr = NULL;
			if (varString->value.length >= 1)
			{
				// Iterate backwards until we find a period.
				// If no period is found, use a blank string
				for (lnLength = varString->value.length - 1; lnLength >= 0; lnLength--)
				{
					if (varString->value.data_u8[lnLength] == '\\')
					{
						// We found a backslash
						ptr = varString->value.data_u8;
						if (lnLength == 0)
							++lnLength;
						break;
					}
				}
			}


		//////////
		// Populate if need be
		//////
			if (!ptr)
			{
				// Create a blank string
				result = iVariable_create(_VAR_TYPE_CHARACTER, NULL, true);

			} else {
				// Create and copy our portion
				result = iVariable_createAndPopulate_byText(_VAR_TYPE_CHARACTER, ptr, lnLength, false);
			}


		//////////
		// Are we good?
		//////
			if (!result)
				iError_report(cgcInternalError, false);


		//////////
        // Return our converted result
		//////
			rpar->rp[0] = result;

	}




//////////
//
// Function: JUSTSTEM()
// Returns the stem (filename left of dot-extension) from the input pathname
//
//////
// Version 0.58
// Last update:
//		Dec.25.2014
//////
// Change log:
//		Dec.25.2014 - Initial creation
//////
// Parameters:
//		varString		-- Character, the input pathname
//		varPostfixWidth	-- (optional) Numeric, the number of extra spaces to postfix pad the juststem() result with
//////
// Returns:
//		Character		-- The file name portion of the pathname ("sample" of "c:\path\to\sample.txt")
//////
	void function_juststem(SReturnsParams* rpar)
	{
		SVariable*	varString		= rpar->ip[0];
		SVariable*	varPostfixWidth	= rpar->ip[1];
		s32			lnI, lnLength, lnPostfixWidth;
		u8*			ptr;
		bool		error;
		u32			errorNum;
        SVariable*	result;


		//////////
		// Parameter 1 must be character
		//////
			rpar->rp[0] = NULL;
			if (!iVariable_isValid(varString) || !iVariable_isTypeCharacter(varString))
			{
				iError_report_byNumber(_ERROR_P1_IS_INCORRECT, iVariable_get_relatedComp(varString), false);
				return;
			}


		//////////
		// If parameter 2 was specified, it must be numeric
		//////
			if (varPostfixWidth)
			{
				if (!iVariable_isValid(varPostfixWidth) || !iVariable_isTypeNumeric(varPostfixWidth))
				{
					iError_report_byNumber(_ERROR_P2_IS_INCORRECT, iVariable_get_relatedComp(varPostfixWidth), false);
					return;
				}
				// Grab the postfix width
				lnPostfixWidth = iiVariable_getAs_s32(varPostfixWidth, false, &error, &errorNum);

			} else {
				// No postfix
				lnPostfixWidth = 0;
			}


		//////////
        // Based on its type, process it accordingly
		//////
			ptr		= NULL;
			result	= iVariable_create(_VAR_TYPE_CHARACTER, NULL, true);
			if (!result)
			{
				iError_report(cgcInternalError, false);
				return;
			}

			if (varString->value.length >= 1)
			{
				// Iterate backwards until we find a period.
				// If no period is found, use a blank string
				for (lnI = varString->value.length - 1, lnLength = 0; lnI > 0; lnI--)
				{
					if (varString->value.data_u8[lnI] == '\\')
					{
						// We found a period
						break;
					}
				}

				// Set our pointer to the filename
				ptr = varString->value.data_u8 + lnI + ((lnI > 0) ? 1 : 0);
			}


		//////////
		// Populate if need be
		//////
			if (ptr)
			{
				// Search forward until we find a period, or the end
				for (lnLength = ((lnI == 0) ? 0 : -1); lnI < varString->value.length; lnI++, lnLength++)
				{
					if (varString->value.data_u8[lnI] == '.')
						break;
				}

				// Copy the stem portion
				iDatum_allocateSpace(&result->value, lnLength + lnPostfixWidth);
				if (result->value.data && result->value.length == lnLength + lnPostfixWidth)
				{
					// Copy the ptr content
					memcpy(result->value.data_s8, ptr, lnLength);

					// Postfix width is populated with spaces
					if (lnPostfixWidth != 0)
						memset(result->value.data_s8 + lnLength, 32, lnPostfixWidth);
				}
			}


		//////////
        // Return our converted result
		//////
			rpar->rp[0] = result;

	}
