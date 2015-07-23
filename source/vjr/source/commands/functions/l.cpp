//////////
//
// /libsf/source/vjr/commands/funcs/l.cpp
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
// Version 0.57
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
// Function: LEFT()
// Returns the left N characters of a string.
//
//////
// Version 0.57
// Last update:
//     Jul.12.2014
//////
// Change log:
//     Jul.12.2014 - Initial creation
//////
// Parameters:
//     pString		-- Character, the string to trim
//     pCount		-- Numeric, the number of characters to copy
//
//////
// Returns:
//    Character		-- The string of the left N characters
//////
	void function_left(SThisCode* thisCode, SFunctionParams* rpar)
	{
		SVariable*	varString	= rpar->params[0];
		SVariable*	varCount	= rpar->params[1];
		s32			lnLength;
		u32			errorNum;
		bool		error;
        SVariable*	result;


		//////////
		// Parameter 1 must be character
		//////
			rpar->returns[0] = NULL;
			if (!iVariable_isValid(varString) || iVariable_getType(varString) != _VAR_TYPE_CHARACTER)
			{
				iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_getRelatedComp(thisCode, varString), false);
				return;
			}


		//////////
		// Parameter 2 must be numeric
		//////
			if (!iVariable_isValid(varCount) || !iVariable_isTypeNumeric(varCount))
			{
				iError_reportByNumber(thisCode, _ERROR_P2_IS_INCORRECT, iVariable_getRelatedComp(thisCode, varCount), false);
				return;
			}


		//////////
        // Find out how long they want our string to be
		//////
			lnLength = iiVariable_getAs_s32(thisCode, varCount, false, &error, &errorNum);
			if (error)
			{
				iError_reportByNumber(thisCode, errorNum, iVariable_getRelatedComp(thisCode, varCount), false);
				return;
			}


		//////////
        // Create our return result
		//////
	        result = iVariable_create(thisCode, _VAR_TYPE_CHARACTER, NULL, true);
			if (!result)
			{
				iError_report(thisCode, cgcInternalError, false);
				return;
			}


		//////////
        // Copy as much of the source string as will fit
		//////
			if (lnLength > 0)
				iDatum_duplicate(&result->value, varString->value.data_u8, min(varString->value.length, lnLength));


		//////////
        // Return our converted result
		//////
			rpar->returns[0] = result;

	}




//////////
//
// Function: LEN()
// Returns the length of the string.
//
//////
// Version 0.57
// Last update:
//     Jul.12.2014
//////
// Change log:
//     Jul.12.2014 - Initial creation
//////
// Parameters:
//     pString		-- Character, the string to return the length from
//
//////
// Returns:
//    Numeric		-- The length of the string
//////
	void function_len(SThisCode* thisCode, SFunctionParams* rpar)
	{
		SVariable* varString = rpar->params[0];
        SVariable* result;


		//////////
		// Parameter 1 must be character
		//////
			rpar->returns[0] = NULL;
			if (!iVariable_isValid(varString) || iVariable_getType(varString) != _VAR_TYPE_CHARACTER)
			{
				iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_getRelatedComp(thisCode, varString), false);
				return;
			}


		//////////
        // Create our return result
		//////
	        result = iVariable_create(thisCode, _VAR_TYPE_S32, NULL, true);
			if (!result)
			{
				iError_report(thisCode, cgcInternalError, false);
				return;
			}


		//////////
		// Populate based on the length
		//////
			*(s32*)result->value.data = varString->value.length;


		//////////
        // Return our converted result
		//////
			rpar->returns[0] = result;

	}


//////////
//
// Function: LOG()
// Returns the natural logarithm (base e) of the specified numeric expression.
//
//////
// Version 0.57
// Last update:
//     Mar.15.2015
//////
// Change log:
//     Mar.15.2015 - Initial creation by Stefano D'Amico
//////
// Parameters:
//     p1			-- Numeric or floating point
//
//////
// Returns:
//    LOG(n) of the value in p1
//////
// Example:
//    ? LOG(2)		&& Display 0.69
//////
    void function_log(SThisCode* thisCode, SFunctionParams* rpar)
    {
		SVariable* varNumber = rpar->params[0];


        // Return log
		ifunction_numbers_common(thisCode, rpar, varNumber, NULL, NULL, _FP_COMMON_LOG, _VAR_TYPE_F64, false, false);
	}




//////////
//
// Function: LOG10()
// Returns the common logarithm (base 10) of the specified numeric expression.
//
//////
// Version 0.57
// Last update:
//     Mar.15.2015
//////
// Change log:
//     Mar.15.2015 - Initial creation by Stefano D'Amico
//////
// Parameters:
//     p1			-- Numeric or floating point
//
//////
// Returns:
//    LOG10(n) of the value in p1
//////
// Example:
//    ? LOG10(2)		&& Display 0.30
//////
    void function_log10(SThisCode* thisCode, SFunctionParams* rpar)
    {
		SVariable* varNumber = rpar->params[0];


        // Return log10
		ifunction_numbers_common(thisCode, rpar, varNumber, NULL, NULL, _FP_COMMON_LOG10, _VAR_TYPE_F64, false, false);
	}




//////////
//
// Function: LOWER()
// Converts every character in the string to lowercase.
//
//////
// Version 0.57
// Last update:
//     Jul.12.2014
//////
// Change log:
//     Jul.12.2014 - Initial creation
//////
// Parameters:
//     pString		-- Character, the string to lower
//
//////
// Returns:
//    Character		-- The string with all lowercase characters converted to lowercase
//////
	void function_lower(SThisCode* thisCode, SFunctionParams* rpar)
	{
		SVariable*	varString = rpar->params[0];
		s32			lnI;
        SVariable*	result;


		//////////
		// Parameter 1 must be character
		//////
			rpar->returns[0] = NULL;
			if (!iVariable_isValid(varString) || iVariable_getType(varString) != _VAR_TYPE_CHARACTER)
			{
				iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_getRelatedComp(thisCode, varString), false);
				return;
			}


		//////////
        // Create our return result
		//////
	        result = iVariable_create(thisCode, _VAR_TYPE_CHARACTER, NULL, true);
			if (!result)
			{
				iError_report(thisCode, cgcInternalError, false);
				return;
			}


		//////////
        // Copy the source string
		//////
	        iDatum_duplicate(&result->value, &varString->value);


		//////////
		// Lower every character
		//////
			for (lnI = 0; lnI < result->value.length; lnI++)
			{
				if (result->value.data[lnI] >= 'A' && result->value.data[lnI] <= 'Z')
					result->value.data[lnI] += 0x20;
			}


		//////////
        // Return our converted result
		//////
			rpar->returns[0] = result;

	}




//////////
//
// Function: LTRIM()
// Trims spaces off the start of the string.
//
//////
// Version 0.57
// Last update:
//     Jul.12.2014
//////
// Change log:
//     Jul.12.2014 - Initial creation
//////
// Parameters:
//     pString		-- Character, the string to trim
//
//////
// Returns:
//    Character		-- The string with any leading spaces removed
//////
	void function_ltrim(SThisCode* thisCode, SFunctionParams* rpar)
	{
		SVariable* varString			= rpar->params[0];
		SVariable* varCaseInsensitive	= rpar->params[1];
		SVariable* varTrimChars1		= rpar->params[2];
		SVariable* varTrimChars2		= rpar->params[3];


		// Return ltrim
		ifunction_trim_common(thisCode, rpar, varString, varCaseInsensitive, varTrimChars1, varTrimChars2, true, false);
	}
