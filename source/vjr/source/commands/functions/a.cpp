//////////
//
// /libsf/source/vjr/commands/funcs/a.cpp
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
// Function: ABS()
// Returns the absolute value of the specified numeric expression.
//
//////
// Version 0.58
// Last update:
//     Mar.18.2015
//////
// Change log:
//     Mar.18.2015 - Initial creation by Stefano D'Amico
//////
// Parameters:
//     p1			-- Numeric or floating point
//
//////
// Returns:
//    ABS(n) of the value in p1
//////
// Example:
//    ? ABS(-10)		&& Display 10
//////
    void function_abs(SReturnsParams* rpar)
    {
		SVariable* varNumber = rpar->ip[0];


		// Return abs
		ifunction_numbers_common(rpar, varNumber, NULL, NULL, _FP_COMMON_ABS, _VAR_TYPE_F64, true, false);
	}




//////////
//
// Function: ACOS()
// Returns the arc cosine of a specified numeric expression.
//
//////
// Version 0.58
// Last update:
//     Mar.18.2015
//////
// Change log:
//     Mar.18.2015 - Initial creation by Stefano D'Amico
//////
// Parameters:
//     p1			-- Numeric or floating point
//
//////
// Returns:
//    ACOS(n) of the value in p1
//////
// Example:
//    ? ACOS(0)		&& Display 1.57
//////
    void function_acos(SReturnsParams* rpar)
    {
		SVariable* varNumber = rpar->ip[0];


		// Return acos
		ifunction_numbers_common(rpar, varNumber, NULL, NULL, _FP_COMMON_ACOS, _VAR_TYPE_F64, false, false);
	}




//////////
//
// Function: ADDBS()
// Adds a backslash to a path if it needs one
//
//////
// Version 0.58
// Last update:
//	   Dec.26.2014
//////
// Change log:
//     Dec.26.2014 - Initial creation
//////
// Parameters:
//     varString		-- Character, the string that needs to end with a backspace
//////
// Returns:
//     Character		-- The string with a trailing backspace added if need be
//////
	void function_addbs(SReturnsParams* rpar)
	{
		SVariable*	varString = rpar->ip[0];
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

			if (varString->value.length >= 1)
			{
				// If the last character is not a backslash, add one
				if (varString->value.data_u8[varString->value.length - 1] != '\\')
				{
					// We need to append the string plus a backslash
					iDatum_allocateSpace(&result->value, varString->value.length + 1);
					memcpy(result->value.data_s8, varString->value.data_s8, varString->value.length);
					result->value.data_u8[result->value.length - 1] = '\\';

				} else {
					// We can copy the string as is
					iDatum_duplicate(&result->value, &varString->value);
				}

			} else {
				// Append a trailing backslash
				iDatum_duplicate(&result->value, (u8*)cgcBackslash, 1);
			}


		//////////
        // Return our converted result
		//////
	        rpar->rp[0] = result;
	}




//////////
//
// Function: ALLTRIM()
// Trims spaces off the start and end of the string.
//
//////
// Version 0.58
// Last update:
//     Jul.12.2014
//////
// Change log:
//     Jul.12.2014 - Initial creation
//////
// Parameters:
//     pString			-- Character, the string to trim
//     pCaseInsensitive	-- (Optional) Logical,		are the trim characters case insensitive?  Default = .T.
//     pTrimChars1		-- (Optional) Character,	characters to trim
//     pTrimChars2		-- (Optional) Character,	characters to trim
//
//////
// Returns:
//    Character		-- The string with any leading and trailing spaces removed
//////
	void function_alltrim(SReturnsParams* rpar)
	{
		SVariable* varString			= rpar->ip[0];
		SVariable* varCaseInsensitive	= rpar->ip[1];
		SVariable* varTrimChars1		= rpar->ip[2];
		SVariable* varTrimChars2		= rpar->ip[3];


		// Return alltrim
		ifunction_trim_common(rpar, varString, varCaseInsensitive, varTrimChars1, varTrimChars2, true, true);
	}




//////////
//
// Logic used for ALLTRIM(), LTRIM(), RTRIM()
//
//////
// Syntax forms supported:
//	    (1)  *TRIM(cString[, cTrimString])
//	    (2)  *TRIM(cString[, nCaseSensitive|lCaseSensitive[, cTrimChar1[, cTrimChar2]]])
//
//////
	void ifunction_trim_common(SReturnsParams* rpar, SVariable* varString, SVariable* varCaseInsensitive, SVariable* varTrimChars1, SVariable* varTrimChars2, bool tlTrimTheStart, bool tlTrimTheEnd)
	{
		s32			lnI, lnClipStartPos, lnClipEndPos;
		s8			lc;
		bool		llCaseInsensitive, llSyntaxForm1, llFound;
		s8*			trim1ptr;
		s8*			trim2ptr;
		s32			trim1Length, trim2Length;
        SVariable*	result;


// TODO:  Incomplete function.  Breakpoint, debug, and finish development
//_asm_int3;
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
		// Initialize
		//////
			llSyntaxForm1		= false;		// Two syntax forms are available
			llCaseInsensitive	= false;		// By default case-sensitive compare
			trim1ptr		= (s8*)cgc_spaceText;
			trim1Length		= 1;
			trim2ptr		= NULL;
			trim2Length		= 0;


		//////////
        // If pCaseInsensitive is present, indicates case-insensitive
		//////
			if (varCaseInsensitive)
			{
				// See what the parameter is
				if (!iVariable_isValid(varCaseInsensitive))
				{
					iError_report_byNumber(_ERROR_P2_IS_INCORRECT, iVariable_get_relatedComp(varCaseInsensitive), false);
					return;

				} else if (iVariable_isTypeNumeric(varCaseInsensitive)) {
					// They are indicating case sensitivity by an integer, should be 1 for case-insensitive, otherwise case-sensitive
					// If 1, case-insensitive
					if (*(s32*)varCaseInsensitive->value.data_s8 == 1)
						llCaseInsensitive = true;

				} else if (iVariable_isTypeLogical(varCaseInsensitive)) {
					// They are indicating case sensitivity by a logical flag, should be .t. for case-insensitive, otherwise case-sensitive
					if (varCaseInsensitive->value.data_s8[0] != 0)
						llCaseInsensitive = true;

				} else if (iVariable_isTypeCharacter(varCaseInsensitive)) {
					// They're using the syntax form:
					//		ALLTRIM(cString[, cTrimString])
					trim1ptr		= varCaseInsensitive->value.data_s8;
					trim1Length		= varCaseInsensitive->value.length;
					trim2ptr		= NULL;
					trim2Length		= 0;
					llSyntaxForm1	= true;

				} else {
					iError_report_byNumber(_ERROR_P2_IS_INCORRECT, iVariable_get_relatedComp(varCaseInsensitive), false);
					return;
				}
			}


		//////////
		// If they specified trimCharss
		//////
			if (varTrimChars1)
			{
				// If they're using syntax form1, then the presence of this parameter is a syntax error
				if (llSyntaxForm1)
				{
					iError_report_byNumber(_ERROR_TOO_MANY_PARAMETERS, iVariable_get_relatedComp(varTrimChars1), false);
					return;

				} else if (iVariable_isTypeCharacter(varTrimChars1)) {
					// They specified characters to scan
					trim1ptr	= varTrimChars1->value.data_s8;
					trim1Length	= varTrimChars1->value.length;

				} else {
					iError_report_byNumber(_ERROR_P3_IS_INCORRECT, iVariable_get_relatedComp(varTrimChars1), false);
					return;
				}
			}


		//////////
		// If they specified trimCharss
		//////
			if (varTrimChars2)
			{
				if (iVariable_isTypeCharacter(varTrimChars2))
				{
					// They specified characters to scan
					trim2ptr	= varTrimChars2->value.data_s8;
					trim2Length	= varTrimChars2->value.length;
					if (trim1ptr == (s8*)cgc_spaceText)
					{
						// They gave us the second trim characters, so we'll use it
						trim1ptr		= NULL;
						trim1Length		= 0;
					}

				} else {
					iError_report_byNumber(_ERROR_P4_IS_INCORRECT, iVariable_get_relatedComp(varTrimChars2), false);
					return;
				}
			}


		//////////
        // Create our return result
		//////
	        result = iVariable_create(_VAR_TYPE_CHARACTER, NULL, true);
			if (!result)
			{
				iError_report(cgcInternalError, false);
				return;
			}


		//////////
        // It must be at least one character long to be adjusted
		//////
			if (varString->value.length >= 1)
			{
				//////////
				// START
				//////
					lnClipStartPos = 0;
					if (tlTrimTheStart)
					{
						// Based on the comparison, we either compare character-by-character, or convert case and compare character-by-character
						if (llCaseInsensitive)
						{
							// Compare character by character exactly as they are
							for ( ; lnClipStartPos < varString->value.length; ++lnClipStartPos)
							{
								// Grab the character
								lc = varString->value.data_s8[lnClipStartPos];

								// Scan the trim1 characters
								// If we're not on a character that we know, we're done
								llFound = false;
								if (trim1ptr)
								{
									for (lnI = 0; lnI < trim1Length; lnI++)
									{
										// If this character matches, we've found a match, which means we're still trimming characters
										if (lc == trim1ptr[lnI])
										{
											llFound = true;
											break;
										}
									}
								}


								// Scan the trim2 characters
								// We still need to search through the trim2 characters list
								if (!llFound && trim2ptr)
								{
									for (lnI = 0; lnI < trim2Length; lnI++)
									{
										// If this character matches, we've found a match, which means we're still trimming characters
										if (lc == trim2ptr[lnI])
										{
											llFound = true;
											break;
										}
									}
								}

								// If we didn't find a trim character, we've reached the end
								if (!llFound)
									break;
							}

						} else {
							// Compare character by character accounting for case
							// Compare character by character exactly as they are
							for ( ; lnClipStartPos < varString->value.length; ++lnClipStartPos)
							{
								// Grab the character
								lc = iLowerCase(varString->value.data_s8[lnClipStartPos]);

								// Scan the trim1 characters
								// If we're not on a character that we know, we're done
								llFound = false;
								if (trim1ptr)
								{
									for (lnI = 0; lnI < trim1Length; lnI++)
									{
										// If this character matches, we've found a match, which means we're still trimming characters
										if (lc == iLowerCase(trim1ptr[lnI]))
										{
											llFound = true;
											break;
										}
									}
								}


								// Scan the trim2 characters
								// We still need to search through the trim2 characters list
								if (!llFound && trim2ptr)
								{
									for (lnI = 0; lnI < trim2Length; lnI++)
									{
										// If this character matches, we've found a match, which means we're still trimming characters
										if (lc == iLowerCase(trim2ptr[lnI]))
										{
											llFound = true;
											break;
										}
									}
								}

								// If we didn't find a trim character, we've reached the end
								if (!llFound)
									break;
							}
						}

						// When we get here, we have determined the number of characters on the left
						if (lnClipStartPos >= varString->value.length)
						{
							// The entire character string is empty, so we just return the blank string
							rpar->rp[0] = result;
							return;
						}
					}


				//////////
				// END
				//////
					lnClipEndPos = varString->value.length - 1;
					if (tlTrimTheEnd)
					{
						// Based on the comparison, we either compare character-by-character, or convert case and compare character-by-character
						if (llCaseInsensitive)
						{
							// Compare character by character exactly as they are
							for ( ; lnClipEndPos > 0; lnClipEndPos--)
							{
								// Grab the character
								lc = varString->value.data_s8[lnClipEndPos];

								// Scan the trim1 characters
								// If we're not on a character that we know, we're done
								llFound = false;
								if (trim1ptr)
								{
									for (lnI = 0; lnI < trim1Length; lnI++)
									{
										// If this character matches, we've found a match, which means we're still trimming characters
										if (lc == trim1ptr[lnI])
										{
											llFound = true;
											break;
										}
									}
								}


								// Scan the trim2 characters
								// We still need to search through the trim2 characters list
								if (!llFound && trim2ptr)
								{
									for (lnI = 0; lnI < trim2Length; lnI++)
									{
										// If this character matches, we've found a match, which means we're still trimming characters
										if (lc == trim2ptr[lnI])
										{
											llFound = true;
											break;
										}
									}
								}

								// If we didn't find a trim character, we've reached the end
								if (!llFound)
									break;
							}

						} else {
							// Compare character by character accounting for case
							// Compare character by character exactly as they are
							for ( ; lnClipEndPos > 0; lnClipEndPos--)
							{
								// Grab the character
								lc = iLowerCase(varString->value.data_s8[lnClipEndPos]);

								// Scan the trim1 characters
								// If we're not on a character that we know, we're done
								llFound = false;
								if (trim1ptr)
								{
									for (lnI = 0; lnI < trim1Length; lnI++)
									{
										// If this character matches, we've found a match, which means we're still trimming characters
										if (lc == iLowerCase(trim1ptr[lnI]))
										{
											llFound = true;
											break;
										}
									}
								}


								// Scan the trim2 characters
								// We still need to search through the trim2 characters list
								if (!llFound && trim2ptr)
								{
									for (lnI = 0; lnI < trim2Length; lnI++)
									{
										// If this character matches, we've found a match, which means we're still trimming characters
										if (lc == iLowerCase(trim2ptr[lnI]))
										{
											llFound = true;
											break;
										}
									}
								}

								// If we didn't find a trim character, we've reached the end
								if (!llFound)
									break;
							}
						}
					}


				//////////
				// Copy the portion of the string
				//////
					iDatum_duplicate(&result->value, varString->value.data_u8 + lnClipStartPos, lnClipEndPos - lnClipStartPos + 1);
			}


		//////////
        // Return our converted result
		//////
	        rpar->rp[0] = result;
	}




//////////
//
// Function: ALP()
// Retrieves the alpha channel from an RGBA or BGRA color.
//
//////
// Version 0.58
// Last update:
//     Mar.16.2015
//////
// Change log:
//     Mar.16.2015 - Initial creation
//////
// Parameters:
//     varColor		-- Numeric, a color (0..(2^32)-1)
//
//////
// Returns:
//    Numeric	-- Input number converted to ASCII value number
//////
	void function_alp(SReturnsParams* rpar)
	{
		SVariable* varColor = rpar->ip[0];


		// Return alp
		ifunction_color_common(rpar, varColor, 0xff000000, 24);
	}




//////////
//
// Function: ASC()
// Takes a character input and converts it to its ASCII value.
//
//////
// Version 0.58
// Last update:
//     Jul.05.2014
//////
// Change log:
//     Jul.05.2014 - Initial creation
//////
// Parameters:
//     p1		-- Character, must be at least one character long
//
//////
// Returns:
//    Numeric	-- Input number converted to ASCII value number
//////
    void function_asc(SReturnsParams* rpar)
    {
		SVariable*	varString = rpar->ip[0];
        u8 			value;
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
        // It must be at least one character long
		//////
			if (varString->value.length == 0)
				iError_report_byNumber(_ERROR_EMPTY_STRING, iVariable_get_relatedComp(varString), false);


		//////////
		// Extract the first character, and convert it to a number
		//////
			value = varString->value.data_u8[0];


		//////////
        // Create our return result
		//////
	        result = iVariable_create(_VAR_TYPE_S32, NULL, true);
			if (!result)
			{
				iError_report(cgcInternalError, false);
				return;
			}


		//////////
        // Populate the result as an ASCII character
		//////
	        *result->value.data_s32 = (s32)value;


		//////////
        // Return our converted result
		//////
	        rpar->rp[0] = result;
    }




//////////
//
// Function: ASIN()
// Returns in radians the arc sine of a numeric expression.
//
//////
// Version 0.58
// Last update:
//     Mar.18.2015
//////
// Change log:
//     Mar.18.2015 - Initial creation by Stefano D'Amico
//////
// Parameters:
//     p1			-- Numeric or floating point
//
//////
// Returns:
//    ASIN(n) of the value in p1
//////
// Example:
//    ? ASIN(1)		&& Display 1.57
//////
    void function_asin(SReturnsParams* rpar)
    {
		SVariable* varNumber = rpar->ip[0];


		// Return asin
		ifunction_numbers_common(rpar, varNumber, NULL, NULL, _FP_COMMON_ASIN, _VAR_TYPE_F64, false, false);
	}




//////////
//
// Function: ATAN()
// Returns in radians the arc tangent of a numeric expression.
//
//////
// Version 0.58
// Last update:
//     Mar.18.2015
//////
// Change log:
//     Mar.18.2015 - Initial creation by Stefano D'Amico
//////
// Parameters:
//     p1			-- Numeric or floating point
//
//////
// Returns:
//    ATAN(n) of the value in p1
//////
// Example:
//    ? ATAN(1.57)		&& Display 1.00
//////
    void function_atan(SReturnsParams* rpar)
    {
		SVariable* varNumber = rpar->ip[0];


		// Return atan
		ifunction_numbers_common(rpar, varNumber, NULL, NULL, _FP_COMMON_ATAN, _VAR_TYPE_F64, false, false);
	}




//////////
//
// Functions:  AT(), ATC(), RAT(), RATC()
// Takes a character input to search for, an expression to search, and an optional occurrence
// to find, with and optionally with regard to case (trailing "C").
//
// Functions:  OCCURS(), OCCURSC()
// Takes a character input to search for, an expression to search, and determines how many
// times the search string is found, and optionally with regard to case (trailing "C").
//
//////
// Version 0.58
// Last update:
//     Aug.03.2014
//////
// Change log:
//     Aug.03.2014 - Initial creation
//////
// Parameters:
//     pNeedle		-- What we're looking for
//     pHaystack	-- Where we're looking
//     pOccurrence	-- An optional instance count within the expression
//
//////
// Returns:
//    u32			-- Location of the find, or 0 if not found
//////
	void function_at(SReturnsParams* rpar)
	{
		SVariable* varNeedle		= rpar->ip[0];
		SVariable* varHaystack		= rpar->ip[1];
		SVariable* varOccurrence	= rpar->ip[2];


		// Return at
		ifunction_at_occurs_common(rpar, varNeedle, varHaystack, varOccurrence, true, false, NULL);
	}

	void function_atc(SReturnsParams* rpar)
	{
		SVariable* varNeedle		= rpar->ip[0];
		SVariable* varHaystack		= rpar->ip[1];
		SVariable* varOccurrence	= rpar->ip[2];


		// Return atc
		ifunction_at_occurs_common(rpar, varNeedle, varHaystack, varOccurrence, false, false, NULL);
	}

	void function_rat(SReturnsParams* rpar)
	{
		SVariable* varNeedle		= rpar->ip[0];
		SVariable* varHaystack		= rpar->ip[1];
		SVariable* varOccurrence	= rpar->ip[2];


		// Return rat
		ifunction_at_occurs_common(rpar, varNeedle, varHaystack, varOccurrence, true, true, NULL);
	}

	void function_ratc(SReturnsParams* rpar)
	{
		SVariable* varNeedle		= rpar->ip[0];
		SVariable* varHaystack		= rpar->ip[1];
		SVariable* varOccurrence	= rpar->ip[2];


		// Return ratc
		ifunction_at_occurs_common(rpar, varNeedle, varHaystack, varOccurrence, false, true, NULL);
	}

	void ifunction_at_occurs_common(SReturnsParams* rpar, SVariable* varNeedle, SVariable* varHaystack, SVariable* varOccurrence, bool tlCaseSensitive, bool tlScanBackward, u32* tnFoundCount)
	{
		u32			errorNum;
		s32			lnI, lnStart, lnInc, lnStopper, lnFoundCount, lnOccurrence;
		bool		error;
		SVariable*	result;


		//////////
		// Parameter 1 must be character
		//////
			rpar->rp[0] = NULL;
			if (!iVariable_isValid(varNeedle) || !iVariable_isTypeCharacter(varNeedle))
			{
				iError_report_byNumber(_ERROR_P1_IS_INCORRECT, iVariable_get_relatedComp(varNeedle), false);
				return;
			}


		//////////
		// Parameter 2 must be character
		//////
			if (!iVariable_isValid(varHaystack) || !iVariable_isTypeCharacter(varHaystack))
			{
				iError_report_byNumber(_ERROR_P2_IS_INCORRECT, iVariable_get_relatedComp(varHaystack), false);
				return;
			}


		//////////
		// Parameter 3 is optional, but if present...
		//////
			if (iVariable_isValid(varOccurrence))
			{
				// ...it must be numeric
				if (!iVariable_isTypeNumeric(varOccurrence))
				{
					iError_report_byNumber(_ERROR_P3_IS_INCORRECT, iVariable_get_relatedComp(varOccurrence), false);
					return;
				}

				// Grab the occurrence
				lnOccurrence = iiVariable_getAs_s32(varOccurrence, false, &error, &errorNum);
				if (error)
				{
					iError_report_byNumber(errorNum, iVariable_get_relatedComp(varOccurrence), false);
					return;
				}

				// Validate that the occurrence is
				if (lnOccurrence <= 0)
				{
					iError_report((cu8*)"Parameter 3 must be 1 or greater", false);
					return;
				}

			} else {
				// The first occurrence is what we're after
				lnOccurrence = 1;
			}


		//////////
		// Create the return variable
		//////
			result = iVariable_create(_VAR_TYPE_S32, NULL, true);
			if (!result)
			{
				iError_report(cgcInternalError, false);
				return;
			}


		//////////
		// If either string has a zero length, or the needle is bigger than the haystack, we cannot find it
		//////
			if (varNeedle->value.length == 0 || varHaystack->value.length == 0 || varNeedle->value.length > varHaystack->value.length)
			{
				rpar->rp[0] = result;
				return;
			}


		//////////
		// Determine where
		//////
			if (tnFoundCount)
			{
				// They want to find all of the occurrences
				lnStart			= 0;
				lnInc			= 1;
				lnStopper		= varHaystack->value.length - varNeedle->value.length + 1;
				lnOccurrence	= varHaystack->value.length;

			} else if (tlScanBackward) {
				// Scan from the back of the string to the start
				lnStart		= varHaystack->value.length - varNeedle->value.length;
				lnInc		= -1;
				lnStopper	= -1;

			} else {
				// Scan from the front of the string to the end
				lnStart		= 0;
				lnInc		= 1;
				lnStopper	= varHaystack->value.length - varNeedle->value.length + 1;
			}


		//////////
		// Scan through the text
		//////
			for (lnI = lnStart, lnFoundCount = 0; lnI != lnStopper; lnI += lnInc)
			{
				//////////
				// Compare this portion
				//////
					if (tlCaseSensitive)
					{
						// Case-sensitive
						if (memcmp(varNeedle->value.data_s8, varHaystack->value.data_s8 + lnI, varNeedle->value.length) == 0)
							++lnFoundCount;		// Here's a match

					} else {
						// Case-insensitive
						if (_memicmp(varNeedle->value.data_s8, varHaystack->value.data_s8 + lnI, varNeedle->value.length) == 0)
							++lnFoundCount;		// Here's a match
					}


				//////////
				// See if we're done
				//////
					if (lnFoundCount == lnOccurrence)
					{
						// Store the found location
						*(s32*)result->value.data_s32 = lnI + 1;

						// We're done, exit
						break;
					}
			}


		//////////
		// Update the found count if it was requested
		//////
			if (tnFoundCount)
				*tnFoundCount = lnFoundCount;


		//////////
		// Indicate our status
		//////
			rpar->rp[0] = result;

	}




//////////
//
// Function: ATN2()
// Returns in radians the arc tangent of the x,y numeric expression
//
//////
// Version 0.58
// Last update:
//     Mar.18.2015
//////
// Change log:
//     Mar.18.2015 - Initial creation
//////
// Parameters:
//     p1			-- Numeric or floating point
//     p2			-- Numeric or floating point
//
//////
// Returns:
//    ATN2(y,x)
//////
// Example:
//    ? ATN2(5,3)		&& Display 1.03
//////
	void function_atn2(SReturnsParams* rpar)
	{
		SVariable* varY = rpar->ip[0];
		SVariable* varX = rpar->ip[1];


		// Return atn2
		ifunction_numbers_common(rpar, varY, varX, NULL, _FP_COMMON_ATN2, _VAR_TYPE_F64, false, false);
	}
