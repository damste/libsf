//////////
//
// /libsf/source/vjr/commands/funcs/f.cpp
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
// Copyright (c) 2014-2015 by Rick C. Hodgin
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
// Function: FLOOR()
// Returns the nearest integer that is less than or equal to the specified numeric expression.
//
//////
// Version 0.58
// Last update:
//     Mar.16.2015
//////
// Change log:
//     Mar.16.2015 - Initial creation by Stefano D'Amico
//////
// Parameters:
//     p1			-- Numeric or floating point
//
//////
// Returns:
//    FLOOR(n) of the value in p1
//////
// Example:
//    ? FLOOR(2.2)		&& Display 2
//////
    void function_floor(SReturnsParams* rpar)
    {
		SVariable* varNumber = rpar->ip[0];


        // Return floor
		ifunction_numbers_common(rpar, varNumber, NULL, NULL, _FP_COMMON_FLOOR, _VAR_TYPE_S64, propGet_settings_ncset_ceilingFloor(_settings), false);
	}




//////////
//
// Function: FORCEEXT()
// Takes a pathname and forces the file extension to the new value
//
//////
// Version 0.58
// Last update:
//     Mar.30.2015
//////
// Change log:
//     Apr.02.2015 - Refactoring by Rick C. Hodgin
//     Mar.30.2015 - Coded by Stefano D'Amico
//     Mar.12.2015 - Framed, incomplete
//////
// Parameters:
//     varPathname		-- The filename or pathname.
//     varNewExtension	-- The new file extension to force.
//////
// Returns:
//    The input pathname with the next extension.
//////
// Example:
//    ? FORCEEXT("c:\mydir\fred.txt",	"prg")		&& Displays "c:\mydir\fred.prg"
//    ? FORCEEXT("c:\mydir\fred.txt",	".prg")		&& Displays "c:\mydir\fred.prg"
//    ? FORCEEXT("c:\mydir\fred.txt ",	"prg")		&& Displays "c:\mydir\fred.prg"
//    ? FORCEEXT("c:\mydir.mydir\foo",	"prg")		&& Displays "c:\mydir.mydir\fred.prg"
//    ? FORCEEXT("c:\mydir\fred.txt",	"")			&& Displays "c:\mydir\fred"
//////
	void function_forceext(SReturnsParams* rpar)
	{
		SVariable* varPathname		= rpar->ip[0];
		SVariable* varNewExtension	= rpar->ip[1];

		s32			lnFNameOffset, lnExtOffset, lnLength;
		s8			newFilename[_MAX_PATH + 1];
		SVariable*	result;


		//////////
		// Parameter 1 must be character
		//////
			rpar->rp[0] = NULL;
			if (!iVariable_isValid(varPathname) || !iVariable_isTypeCharacter(varPathname))
			{
				iError_report_byNumber(_ERROR_P1_IS_INCORRECT, iVariable_get_relatedComp(varPathname), false);
				return;
			}


		//////////
		// Parameter 2 must be character
		//////
			if (!iVariable_isValid(varNewExtension) || !iVariable_isTypeCharacter(varNewExtension))
			{
				iError_report_byNumber(_ERROR_P2_IS_INCORRECT, iVariable_get_relatedComp(varNewExtension), false);
				return;
			}


		//////////
		// Based on its type, process it accordingly
		//////
			if (ifunction_pathname_common(rpar, varPathname, &lnFNameOffset, &lnExtOffset))
			{

				//////////
				// Initialize our target filename
				//////
					memset(newFilename, 0, sizeof(newFilename));
					memcpy(newFilename, varPathname->value.data_s8, lnExtOffset);


				//////////
				// Copy appropriately
				//////
					if (varNewExtension->value.length >= 1)
					{
						// Does it already have a point?
						if (varNewExtension->value.data_s8[0] == '.')
						{
							// Will the new filename be too big?
							lnLength = lnExtOffset + varNewExtension->value.length;			// pathname up to extension + new extension (which already has a period)
							if (lnLength >= (s32)sizeof(newFilename))
							{
								// Too big
								iError_report_byNumber(_ERROR_TOO_BIG_FOR_TARGET, iVariable_get_relatedComp(varNewExtension), false);
								return;
							}

							// Copy new extension (which already has a period)
							memcpy(newFilename + lnExtOffset, varNewExtension->value.data_s8, varNewExtension->value.length);

						} else {
							// Will the new filename be too big?
							lnLength = lnExtOffset + 1 + varNewExtension->value.length;		// pathname up to extension + new period + new extension
							if (lnLength >= (s32)sizeof(newFilename))
							{
								// Too big
								iError_report_byNumber(_ERROR_TOO_BIG_FOR_TARGET, iVariable_get_relatedComp(varNewExtension), false);
								return;
							}

							// Copy new period, and new extension (without period)
							newFilename[lnExtOffset] = '.';
							memcpy(newFilename + lnExtOffset + 1, varNewExtension->value.data_s8, varNewExtension->value.length);
						}

					} else {
						// Copy everything except the extension
						lnLength = lnExtOffset;
					}


				//////////
				// Allocate our result
				//////
					result = iVariable_createAndPopulate_byText(_VAR_TYPE_CHARACTER, newFilename, lnLength, false);


			} else {
				// Unable to parse the string properly, so return whatever they supplied
				lnLength	= varPathname->value.length;
				result		= iVariable_copy(varPathname, false);
			}


		//////////
		// Are we good?
		//////
			if (!result->value.data_s8 || result->value.length != lnLength)
			{
				// Unable to allocate our variable's contents
				iVariable_delete(result, true);
				result = NULL;
			}

			if (!result)
				iError_report(cgcInternalError, false);


		//////////
		// Return our result
		//////
			rpar->rp[0] = result;

	}

//////////
// varPathname		-- Something like "c:\my\dir\file.ext" or "file.ext"
// tnFNameOffset	-- offset to start of file name
// tnExtOffset		-- offset to start of file extension
//////
	bool ifunction_pathname_common(SReturnsParams* rpar, SVariable* varPathname, s32* tnFNameOffset, s32* tnExtOffset)
	{
		s8		lc;
		s32		lnI, lnLookingFor;
		cs32	_PERIOD		= 1;
		cs32	_BACKSLASH	= 2;


		//////////
		// Make sure our environment is sane
		//////
			rpar->rp[0] = NULL;
			if (varPathname->value.length >= 1)
			{

				//////////
				// Initialize to the beginning for filename, and end for period
				//////
					*tnFNameOffset	= 0;
					*tnExtOffset	= varPathname->value.length;


				//////////
				// We need to find "\" and period.
				//////
					for (lnI = varPathname->value.length - 1, lnLookingFor = _PERIOD; lnI >= 0; lnI--)
					{

						//////////
						// Grab the character
						//////
							lc = varPathname->value.data_u8[lnI];


						//////////
						// What are we looking for?
						//////
							if (lnLookingFor == _PERIOD)
							{
								// Searching for the file extension
								if (lc == '.')
								{
									// Found the period
									*tnExtOffset	= lnI;
									lnLookingFor	= _BACKSLASH;	// Now looking for backslash

								} else if (lc == '\\') {
									// We've found the backslash before the period
									*tnFNameOffset = lnI + 1;
									return(true);
								}

							} else if (lnLookingFor == _BACKSLASH) {
								// Looking for the backslash
								if (lc == '\\')
								{
									*tnFNameOffset = lnI + 1;
									return(true);
								}
							}

					}
					// If we get here, we didn't find
			}


		//////////
		// varPathname is empty
		//////
			return(false);
	}




//////////
//
// Function: FORCEFNAME()
// Takes a pathname and forces the filename to the new value
//
//////
// Version 0.58
// Last update:
//     Mar.30.2015
//////
// Change log:
//     Apr.02.2015 - Refactoring by Rick C. Hodgin
//     Mar.30.2015 - Coded by Stefano D'Amico
//     Mar.12.2015 - Framed, incomplete
//////
// Parameters:
//     varPathname		-- The filename or pathname.
//     varNewFilename	-- The new filename to force.
//////
// Returns:
//    The input pathname with the filename.
//////
	void function_forcefname(SReturnsParams* rpar)
	{
		SVariable* varPathname		= rpar->ip[0];
		SVariable* varNewFilename	= rpar->ip[1];

		s32			lnFNameOffset, lnExtOffset, lnLength;
		s8			newFilename[_MAX_PATH + 1];
		SVariable*	result;


		//////////
		// Parameter 1 must be character
		//////
			rpar->rp[0] = NULL;
			if (!iVariable_isValid(varPathname) || !iVariable_isTypeCharacter(varPathname))
			{
				iError_report_byNumber(_ERROR_P1_IS_INCORRECT, iVariable_get_relatedComp(varPathname), false);
				return;
			}


		//////////
		// Parameter 2 must be character
		//////
			if (!iVariable_isValid(varNewFilename) || !iVariable_isTypeCharacter(varNewFilename))
			{
				iError_report_byNumber(_ERROR_P2_IS_INCORRECT, iVariable_get_relatedComp(varNewFilename), false);
				return;
			}


		//////////
		// Based on its type, process it accordingly
		//////
			if (ifunction_pathname_common(rpar, varPathname, &lnFNameOffset, &lnExtOffset))
			{

				//////////
				// Initialize our target filename
				//////
					memset(newFilename, 0, sizeof(newFilename));
					memcpy(newFilename, varPathname->value.data_s8, lnFNameOffset);


				//////////
				// Copy appropriately
				//////
					if (varNewFilename->value.length >= 1)
					{
						// Will the new filename be too big?
						lnLength = lnFNameOffset + varNewFilename->value.length;
						if (lnLength >= (s32)sizeof(newFilename))
						{
							// Too big
							iError_report_byNumber(_ERROR_TOO_BIG_FOR_TARGET, iVariable_get_relatedComp(varNewFilename), false);
							return;
						}

						// Copy new filename
						memcpy(newFilename + lnFNameOffset, varNewFilename->value.data_s8, varNewFilename->value.length);

					} else {
						// If varNewFilename is empty, we remove filename
						lnLength = lnFNameOffset;
					}


				//////////
				// Allocate our result
				//////
					result = iVariable_createAndPopulate_byText(_VAR_TYPE_CHARACTER, newFilename, lnLength, false);


			} else {
				// Unable to parse the string properly, so return whatever they supplied
				lnLength	= varPathname->value.length;
				result		= iVariable_copy(varPathname, false);
			}


		//////////
		// Are we good?
		//////
			if (!result->value.data_s8 || result->value.length != lnLength)
			{
				// Unable to allocate our variable's contents
				iVariable_delete(result, true);
				result = NULL;
			}

			if (!result)
				iError_report(cgcInternalError, false);


		//////////
		// Return our result
		//////
			rpar->rp[0] = result;

	}




//////////
//
// Function: FORCEPATH()
// Takes a pathname and forces the path to the new value
//
//////
// Version 0.58
// Last update:
//     Mar.30.2015
//////
// Change log:
//     Apr.02.2015 - Refactoring by Rick C. Hodgin
//     Mar.30.2015 - Coded by Stefano D'Amico
//     Mar.12.2015 - Framed, incomplete
//////
// Parameters:
//     varPathname		-- The filename or pathname.
//     varNewPathname	-- The new pathname to force.
//////
// Returns:
//    The input pathname with the new path.
//////
	void function_forcepath(SReturnsParams* rpar)
	{
		SVariable* varPathname		= rpar->ip[0];
		SVariable* varNewPathname	= rpar->ip[1];

		s32			lnFNameOffset, lnExtOffset, lnFNameLength, lnLength;
		s8			newFilename[_MAX_PATH + 1];
		SVariable*	result;



		//////////
		// Parameter 1 must be character
		//////
			rpar->rp[0] = NULL;
			if (!iVariable_isValid(varPathname) || !iVariable_isTypeCharacter(varPathname))
			{
				iError_report_byNumber(_ERROR_P1_IS_INCORRECT, iVariable_get_relatedComp(varPathname), false);
				return;
			}


		//////////
		// Parameter 2 must be character
		//////
		if (!iVariable_isValid(varNewPathname) || !iVariable_isTypeCharacter(varNewPathname))
		{
			iError_report_byNumber(_ERROR_P2_IS_INCORRECT, iVariable_get_relatedComp(varNewPathname), false);
			return;
		}

		//////////
		// Based on its type, process it accordingly
		//////
			lnLength = 0;
			if (ifunction_pathname_common(rpar, varPathname, &lnFNameOffset, &lnExtOffset))
			{

				//////////
				// Initialize our target filename
				//////
					memset(newFilename, 0, sizeof(newFilename));


				//////////
				// Compute the length of the non-path portion
				//////
					lnFNameLength = varPathname->value.length - lnFNameOffset;


				//////////
				// Copy appropriately
				//////
					if (varNewPathname->value.length >= 1)
					{
						// Do we need to add a backslash?
						if (varNewPathname->value.data_s8[varNewPathname->value.length - 1] != '\\')
						{
							// Will the new filename be too big?
							lnLength = varNewPathname->value.length + 1 + lnFNameLength;
							if (lnLength >= (s32)sizeof(newFilename))
							{
								// Too big
								iError_report_byNumber(_ERROR_TOO_BIG_FOR_TARGET, iVariable_get_relatedComp(varNewPathname), false);
								return;
							}

							// Copy new path, plus trailing backslash, plus whatever was there before
							memcpy(newFilename, varNewPathname->value.data_s8, varNewPathname->value.length);
							newFilename[varNewPathname->value.length] = '\\';
							memcpy(newFilename + varNewPathname->value.length + 1, varPathname->value.data_s8 + lnFNameOffset, lnFNameLength);

						} else {
							// Will the new filename be too big?
							lnLength = varNewPathname->value.length + lnFNameLength;
							if (lnLength >= (s32)sizeof(newFilename))
							{
								// Too big
								iError_report_byNumber(_ERROR_TOO_BIG_FOR_TARGET, iVariable_get_relatedComp(varNewPathname), false);
								return;
							}

							// Copy new path, plus whatever was there before
							memcpy(newFilename, varNewPathname->value.data_s8, varNewPathname->value.length);
							memcpy(newFilename + varNewPathname->value.length, varPathname->value.data_s8 + lnFNameOffset, lnFNameLength);
						}

					} else {
						// Remove path
						lnLength = lnFNameLength;
						memcpy(newFilename, varPathname->value.data_s8 + lnFNameOffset, lnFNameLength);
					}


				//////////
				// Allocate our result
				//////
					result = iVariable_createAndPopulate_byText(_VAR_TYPE_CHARACTER, newFilename, lnLength, false);


			} else {
				// Unable to parse the string properly, so return whatever they supplied
				lnFNameLength	= varPathname->value.length;
				result			= iVariable_copy(varPathname, false);
			}


		//////////
		// Are we good?
		//////
			if (!result->value.data_s8 || result->value.length != lnLength || lnLength == 0)
			{
				// Unable to allocate our variable's contents
				iVariable_delete(result, true);
				result = NULL;
			}

			if (!result)
				iError_report(cgcInternalError, false);


		//////////
		// Return our result
		//////
			rpar->rp[0] = result;

	}




//////////
//
// Function: FORCESTEM()
// Takes a pathname and forces the stem to the new value
//
//////
// Version 0.58
// Last update:
//     Mar.30.2015
//////
// Change log:
//     Apr.02.2015 - Refactoring by Rick C. Hodgin
//     Mar.30.2015 - Coded by Stefano D'Amico
//     Mar.12.2015 - Framed, incomplete
//////
// Parameters:
//     varPathname		-- The filename or pathname.
//     varNewStem		-- The new stem to force.
//////
// Returns:
//    The input pathname with the new stem.
//////
	void function_forcestem(SReturnsParams* rpar)
	{
		SVariable* varPathname	= rpar->ip[0];
		SVariable* varNewStem	= rpar->ip[1];

		s32			lnFNameOffset, lnExtOffset, lnLengthExt, lnLength;
		s8			newFilename[_MAX_PATH + 1];
		SVariable*	result;


		//////////
		// Parameter 1 must be character
		//////
			rpar->rp[0] = NULL;
			if (!iVariable_isValid(varPathname) || !iVariable_isTypeCharacter(varPathname))
			{
				iError_report_byNumber(_ERROR_P1_IS_INCORRECT, iVariable_get_relatedComp(varPathname), false);
				return;
			}


		//////////
		// Parameter 2 must be character
		//////
			if (!iVariable_isValid(varNewStem) || !iVariable_isTypeCharacter(varNewStem))
			{
				iError_report_byNumber(_ERROR_P2_IS_INCORRECT, iVariable_get_relatedComp(varNewStem), false);
				return;
			}


		//////////
		// Based on its type, process it accordingly
		//////
			lnLength = 0;
			if (ifunction_pathname_common(rpar, varPathname, &lnFNameOffset, &lnExtOffset))
			{

				//////////
				// Initialize our target filename
				//////
					memset(newFilename, 0, sizeof(newFilename));


				//////////
				// Compute the length of the non-path portion
				//////
//					lnLengthStem	= varPathname->value.length - lnFNameOffset - lnExtOffset;
					lnLengthExt		= varPathname->value.length - lnExtOffset;


				//////////
				// Copy appropriately
				//////
					if (varNewStem->value.length >= 1)
					{
						// Will the new filename be too big?
						lnLength = lnFNameOffset + varNewStem->value.length + lnLengthExt;
						if (lnLength >= (s32)sizeof(newFilename))
						{
							// Too big
							iError_report_byNumber(_ERROR_TOO_BIG_FOR_TARGET, iVariable_get_relatedComp(varNewStem), false);
							return;
						}

						// Copy path, plus new stem, plus original extension
						memcpy(newFilename, varPathname->value.data_s8, lnFNameOffset);
						memcpy(newFilename + lnFNameOffset, varNewStem->value.data_s8, varNewStem->value.length);
						memcpy(newFilename + lnFNameOffset + varNewStem->value.length, varPathname->value.data_s8 + lnExtOffset, lnLengthExt);

					} else {
						// Copy original path, plus original extension
						lnLength = lnFNameOffset + lnLengthExt;
						memcpy(newFilename, varPathname->value.data_s8, lnFNameOffset);
						memcpy(newFilename + lnFNameOffset, varPathname->value.data_s8 + lnExtOffset, lnLengthExt);
					}


				//////////
				// Allocate our result
				//////
					result = iVariable_createAndPopulate_byText(_VAR_TYPE_CHARACTER, newFilename, lnLength, false);


			} else {
				// Unable to parse the string properly, so return whatever they supplied
				result = iVariable_copy(varPathname, false);
			}


		//////////
		// Are we good?
		//////
			if (!result->value.data_s8 || result->value.length != lnLength)
			{
				// Unable to allocate our variable's contents
				iVariable_delete(result, true);
				result = NULL;
			}

			if (!result)
				iError_report(cgcInternalError, false);


		//////////
		// Return our result
		//////
			rpar->rp[0] = result;

	}




//////////
//
// Function: FV()
// Returns the future value of a financial investment.
//
//////
// Version 0.58
// Last update:
//     Mar.19.2015
//////
// Change log:
//     Mar.19.2015 - Refactoring by Stefano D'Amico
//     Mar.18.2015 - Initial creation by Stefano D'Amico
//////
// Parameters:
//     p1			-- Numeric or floating point
//
//////
// Returns:
//    FV(n) of the value in p1
//////
// Example:
//   ? FV(500, 0.006, 48)	&& Displays 27717.50
//////
	void function_fv(SReturnsParams* rpar)
	{
		SVariable* varPayment		= rpar->ip[0];
		SVariable* varInterestRate	= rpar->ip[1];
		SVariable* varPeriods		= rpar->ip[2];


		// Return fv
		ifunction_numbers_common(rpar, varPayment, varInterestRate, varPeriods, _FP_COMMON_FV, _VAR_TYPE_F64, false, true);
	}
