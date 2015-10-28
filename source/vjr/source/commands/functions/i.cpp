//////////
//
// /libsf/source/vjr/commands/funcs/i.cpp
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
// Function: IIF()
// Immediate if.
//
//////
// Version 0.57
// Last update:
//     Mar.22.2015
//////
// Change log:
//     Mar.22.2015 - Initial creation
//////
// Parameters:
//     varTest		-- The logical test result
//     varTrue		-- The value to use if true
//     varFalse		-- The value to use if false
//
//////
// Returns:
//    A copy of either varTrue or varFalse.
//////
	void function_iif(SFunctionParams* rpar)
	{
		SVariable*	varTest		= rpar->ip[0];
		SVariable*	varTrue		= rpar->ip[1];
		SVariable*	varFalse	= rpar->ip[2];
		bool		llTest;
		SVariable*	result;
		u32			errorNum;
        bool		error;


		//////////
		// Parameter 1 must be logical
		//////
			rpar->rp[0] = NULL;
			if (!iVariable_isValid(varTest) || !iVariable_isFundamentalTypeLogical(varTest))
			{
				iError_reportByNumber(_ERROR_MUST_BE_LOGICAL, iVariable_get_relatedComp(varTest), false);
				return;
			}


		//////////
        // Grab the test result
		//////
			llTest = iiVariable_getAs_bool(varTest, false, &error, &errorNum);
			if (error)
			{
				iError_reportByNumber(errorNum, iVariable_get_relatedComp(varTest), false);
				return;
			}


		//////////
		// Based on the test, copy either varTrue or varFalse
		//////
			if (llTest)
			{
				// Copy true
				result = iVariable_copy(varTrue, false);

			} else {
				// Copy false
				result = iVariable_copy(varFalse, false);
			}


		//////////
		// Are we good?
		//////
			if (!result)
				iError_reportByNumber(_ERROR_INTERNAL_ERROR, iVariable_get_relatedComp(((llTest) ? varTrue : varFalse)), false);


		//////////
        // Return our converted result
		//////
			rpar->rp[0] = result;

	}




//////////
//
// Function: INLIST()
// A test if the value is in the list.
//
//////
// Version 0.57
// Last update:
//     Mar.22.2015
//////
// Change log:
//     Mar.22.2015 - Initial creation
//////
// Parameters:
//     varValue		-- The value to compare
//     varList1		-- A value in the list
//     varList2		-- A value in the list
//     ..
//     varList9		-- A value in the list
//
//////
// Returns:
//    Logical		-- .t. if the item is found in the list, .f. otherwise
//////
	void function_inlist(SFunctionParams* rpar)
	{
		SVariable*	varValue = rpar->ip[0];
		SVariable*	varList1 = rpar->ip[1];
		bool		llResult;
		s32			lnI, lnType;
		SVariable*	result;
		u32			errorNum;
        bool		error;


		//////////
		// Parameters 1 and 2 must be present, and of equal types
		//////
			rpar->rp[0] = NULL;
			if (!iVariable_isValid(varValue))
			{
				iError_reportByNumber(_ERROR_MISSING_PARAMETER, iVariable_get_relatedComp(varValue), false);
				return;
			}
			if (!iVariable_isValid(varList1))
			{
				iError_reportByNumber(_ERROR_MISSING_PARAMETER, iVariable_get_relatedComp(varList1), false);
				return;
			}


		//////////
		// Each type must be fundamentally the same type
		//////
			for (lnI = 1, lnType = iVariable_get_fundamentalType(varValue); lnI < (s32)_MAX_PARAMS_COUNT && rpar->ip[lnI]; lnI++)
			{

				//////////
				// Make sure this variable type matches the test value
				//////
					if (iVariable_get_fundamentalType(rpar->ip[lnI]) != lnType)
					{
						// The types do not match
						iError_reportByNumber(_ERROR_DATA_TYPE_MISMATCH, iVariable_get_relatedComp(rpar->ip[lnI]), false);
						return;
					}

			}


		//////////
		// Iterate through to see if the parameters are equal
		//////
			for (lnI = 1, llResult = false; lnI < (s32)_MAX_PARAMS_COUNT && rpar->ip[lnI]; lnI++)
			{

				//////////
				// Compare the value with each list item
				//////
					if (iVariable_compare(varValue, rpar->ip[lnI], false, &error, &errorNum) == 0 && !error)
					{
						// We found a match
						llResult = true;
						break;
					}


				//////////
				// Report on errors
				//////
					if (error)
					{
						iError_reportByNumber(errorNum, iVariable_get_relatedComp(rpar->ip[lnI]), false);
						return;
					}

			}


		//////////
		// Based on the result, create the return(result)
		//////
			result = iVariable_createAndPopulate_byText(_VAR_TYPE_LOGICAL, ((llResult) ? (s8*)&_LOGICAL_TRUE : (s8*)&_LOGICAL_FALSE), 1, false);
			if (!result)
				iError_reportByNumber(_ERROR_INTERNAL_ERROR, iVariable_get_relatedComp(varValue), false);


		//////////
		// Indicate our result
		//////
			rpar->rp[0] = result;

	}




//////////
//
// Function: INT()
// Takes a value and returns the INT(n) of that value.
//
//////
// Version 0.57
// Last update:
//     Apr.02.2015
//////
// Change log:
//     Apr.02.2015 - Refactoring
//     Jul.13.2014 - Initial creation
//////
// Parameters:
//     p1			-- Numeric or floating point
//
//////
// Returns:
//    INT(n) of the value in p1
//////
    void function_int(SFunctionParams* rpar)
    {
		SVariable*	varNumber = rpar->ip[0];
		f64			fValue;
		u32			errorNum;
        bool		error;
        SVariable*	result;


		//////////
		// Parameter 1 must be numeric
		//////
			rpar->rp[0] = NULL;
			if (!iVariable_isValid(varNumber) || !iVariable_isTypeNumeric(varNumber))
			{
				iError_reportByNumber(_ERROR_PARAMETER_IS_INCORRECT, iVariable_get_relatedComp(varNumber), false);
				return;
			}


		//////////
        // Based on its type, process it accordingly
		//////
			if (iVariable_isTypeFloatingPoint(varNumber))
			{
				fValue = iiVariable_getAs_f64(varNumber, false, &error, &errorNum);
				if (error)
				{
					iError_reportByNumber(errorNum, iVariable_get_relatedComp(varNumber), false);
					return;
				}

				// Convert to S64
				result = iVariable_create(_VAR_TYPE_S64, NULL, true);
				if (result)
					*(s64*)result->value.data = (s64)fValue;

			} else {
				// Copy whatever it already is
				result = iVariable_copy(varNumber, false);
			}


		//////////
		// Are we good?
		//////
			if (!result)
			{
				iError_report(cgcInternalError, false);
				return;
			}


		//////////
        // Return our converted result
		//////
			rpar->rp[0] = result;

    }




//////////
//
// Function: ISALPHA()
// Determines whether the leftmost character in a character expression is alphabetic.
//
//////
// Version 0.58
// Last update:
//     Sep.15.2015
//////
// Change log:
//     Sep.15.2015 - Initial creation by Stefano D'Amico
//////
// Parameters:
//     p1	-- Specifies the character expression that ISALPHA( ) evaluates.
//     p2	-- Optional, if true evaluates all string
//
//////
// Returns:
//    Logical    -- If the leftmost character* is an alphabetic character;
//                  * Note:  If p2 is .T., then it tests all characters and not just left-most
//////
// Example:
//    ? ISALPHA("A2")		&& Display .T.
//    ? ISALPHA("A2")		&& Display .T.
//    ? ISALPHA("A2", .T.) 	&& Display .F.
//    ? ISALPHA("AA", .T.)	&& Display .T.
//////
	void function_isalpha(SFunctionParams* rpar)
	{
		SVariable*	varStr				= rpar->ip[0];
		SVariable*	varTestWholeString	= rpar->ip[1];

		bool		llTestWholeString, llIsAlpha;
		bool		error;
		u32			errorNum;


		//////////
		// Parameters 1 must be present and character
		//////
			rpar->rp[0] = NULL;
			if (!iVariable_isValid(varStr) || !iVariable_isTypeCharacter(varStr))
			{
				iError_reportByNumber(_ERROR_P1_IS_INCORRECT, iVariable_get_relatedComp(varStr), false);
				return;
			}


		//////////
		// If present, parameter 2 must be bool
		//////
			if (varTestWholeString)
			{
				if (!iVariable_isFundamentalTypeLogical(varTestWholeString))
				{
					iError_reportByNumber(_ERROR_P2_IS_INCORRECT, iVariable_get_relatedComp(varTestWholeString), false);
					return;
				}

				// Grab the value
				llTestWholeString = iiVariable_getAs_bool(varTestWholeString, false, &error, &errorNum);
				if (error)
				{
					iError_reportByNumber(errorNum, iVariable_get_relatedComp(varTestWholeString), false);
					return;
				}

			} else {
				// Just testing the first character
				llTestWholeString = false;
			}


		//////////
		// Create and populate the return variable
		//////
			llIsAlpha	= ifunction_iscommon(varStr, llTestWholeString, _isAlpha);
			rpar->rp[0]	= iVariable_createAndPopulate_byText(_VAR_TYPE_LOGICAL, (cs8*)((llIsAlpha) ? &_LOGICAL_TRUE : &_LOGICAL_FALSE), 1, true);
			if (!rpar->rp[0])
				iError_reportByNumber(_ERROR_INTERNAL_ERROR, iVariable_get_relatedComp(varStr), false);

	}

	// Common for isalpha(), isdigit(), islower(), isupper()
	bool ifunction_iscommon(SVariable* varStr, bool tlWhole, u32 tnIsCommonOp)
	{
		s32		lnI, lnMaxLength;
		s8		c;
		bool	llResult;
		

		//////////
		// Iterate through our string for each test
		//////
			lnMaxLength = min(((tlWhole) ? varStr->value.length : 1), varStr->value.length);
			llResult	= (lnMaxLength>0);

			// What is the common operation we're testing?
			switch (tnIsCommonOp)
			{
				case _isAlpha:
					for (lnI = 0; llResult && lnI < lnMaxLength; lnI++)
					{
						// Grab and test each character
						c			= varStr->value.data_cs8[lnI];
						llResult	= ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
					}
					break;

				case _isDigit:
					for (lnI = 0; llResult && lnI < lnMaxLength; lnI++)
					{
						// Grab and test each character
						c			= varStr->value.data_cs8[lnI];
						llResult	= (c >= '0' && c <= '9');
					}
					break;

				case _isLower:
					for (lnI = 0; llResult && lnI < lnMaxLength; lnI++)
					{
						// Grab and test each character
						c			= varStr->value.data_cs8[lnI];
						llResult	= (c >= 'a' && c <= 'z');
					}
					break;

				case _isUpper:
					for (lnI = 0; llResult && lnI < lnMaxLength; lnI++)
					{
						// Grab and test each character
						c			= varStr->value.data_cs8[lnI];
						llResult	= (c >= 'A' && c <= 'Z');
					}
					break;
			}


		//////////
        // return result
		//////
			return(llResult);
	}




//////////
//
// Function: ISDIGIT()
// Determines whether the leftmost character of the specified character expression is a digit (0 through 9).
//
//////
// Version 0.58
// Last update:
//     Sep.15.2015
//////
// Change log:
//     Sep.15.2015 - Initial creation by Stefano D'Amico
//////
// Parameters:
//     p1	-- Specifies the character expression that ISDIGIT( ) evaluates.
//     p2	-- Optional, if true evaluates all string
//
//////
// Returns:
//    ISDIGIT( ) returns true (.T.) if the leftmost character of the specified character expression is a digit (0 through 9);
//    otherwise, ISDIGIT( ) returns false (.F.).
//////
// Example:
//    ? ISDIGIT("22")		&& Display .T.
//    ? ISDIGIT("2a")		&& Display .T.
//    ? ISDIGIT("2a", .T.)  && Display .F.
//    ? ISDIGIT("22", .T.)	&& Display .T.
//////
	void function_isdigit(SFunctionParams* rpar)
	{
		SVariable*	varStr				= rpar->ip[0];
		SVariable*	varTestWholeString	= rpar->ip[1];

		bool		llTestWholeString, llIsDigit;
		bool		error;
		u32			errorNum;


		//////////
		// Parameters 1 must be present and character
		//////
			rpar->rp[0] = NULL;
			if (!iVariable_isValid(varStr) || !iVariable_isTypeCharacter(varStr))
			{
				iError_reportByNumber(_ERROR_P1_IS_INCORRECT, iVariable_get_relatedComp(varStr), false);
				return;
			}


		//////////
		// If present, parameter 2 must be bool
		//////
			if (varTestWholeString)
			{
				if (!iVariable_isFundamentalTypeLogical(varTestWholeString))
				{
					iError_reportByNumber(_ERROR_P2_IS_INCORRECT, iVariable_get_relatedComp(varTestWholeString), false);
					return;
				}

				// Grab the value
				llTestWholeString = iiVariable_getAs_bool(varTestWholeString, false, &error, &errorNum);
				if (error)
				{
					iError_reportByNumber(errorNum, iVariable_get_relatedComp(varTestWholeString), false);
					return;
				}

			} else {
				// Just testing the first character
				llTestWholeString = false;
			}


		//////////
		// Create and populate the return variable
		//////
			llIsDigit	= ifunction_iscommon(varStr, llTestWholeString, _isDigit);
			rpar->rp[0]	= iVariable_createAndPopulate_byText(_VAR_TYPE_LOGICAL, (cs8*)((llIsDigit) ? &_LOGICAL_TRUE : &_LOGICAL_FALSE), 1, true);
			if (!rpar->rp[0])
				iError_reportByNumber(_ERROR_INTERNAL_ERROR, iVariable_get_relatedComp(varStr), false);

	}




//////////
//
// Function: ISLOWER()
// Determines whether the leftmost character of the specified character expression is a lowercase alphabetic character.
//
//////
// Version 0.58
// Last update:
//     Sep.15.2015
//////
// Change log:
//     Sep.15.2015 - Initial creation by Stefano D'Amico
//////
// Parameters:
//     p1	-- Specifies the character expression that ISLOWER( ) evaluates.
//     p2	-- Optional, if true evaluates all string
//
//////
// Returns:
//    ISLOWER( ) returns true (.T.) if the leftmost character in the specified character expression is a lowercase alphabetic character;
//    otherwise, ISLOWER( ) returns false (.F.).
//////
// Example:
//    ? ISLOWER("aA")		&& Display .T.
//    ? ISLOWER("aA")		&& Display .T.
//    ? ISLOWER("aA", .T.) 	&& Display .F.
//    ? ISLOWER("aa", .T.)	&& Display .T.
//////
	void function_islower(SFunctionParams* rpar)
	{
		SVariable*	varStr				= rpar->ip[0];
		SVariable*	varTestWholeString	= rpar->ip[1];

		bool		llTestWholeString, llIsLower;
		bool		error;
		u32			errorNum;


		//////////
		// Parameters 1 must be present and character
		//////
			rpar->rp[0] = NULL;
			if (!iVariable_isValid(varStr) || !iVariable_isTypeCharacter(varStr))
			{
				iError_reportByNumber(_ERROR_P1_IS_INCORRECT, iVariable_get_relatedComp(varStr), false);
				return;
			}


		//////////
		// If present, parameter 2 must be bool
		//////
			if (varTestWholeString)
			{
				if (!iVariable_isFundamentalTypeLogical(varTestWholeString))
				{
					iError_reportByNumber(_ERROR_P2_IS_INCORRECT, iVariable_get_relatedComp(varTestWholeString), false);
					return;
				}

				// Grab the value
				llTestWholeString = iiVariable_getAs_bool(varTestWholeString, false, &error, &errorNum);
				if (error)
				{
					iError_reportByNumber(errorNum, iVariable_get_relatedComp(varTestWholeString), false);
					return;
				}

			} else {
				// Just testing the first character
				llTestWholeString = false;
			}


		//////////
		// Create and populate the return variable
		//////
			llIsLower	= ifunction_iscommon(varStr, llTestWholeString, _isLower);
			rpar->rp[0]	= iVariable_createAndPopulate_byText(_VAR_TYPE_LOGICAL, (cs8*)((llIsLower) ? &_LOGICAL_TRUE : &_LOGICAL_FALSE), 1, true);
			if (!rpar->rp[0])
				iError_reportByNumber(_ERROR_INTERNAL_ERROR, iVariable_get_relatedComp(varStr), false);

	}




//////////
//
// Function: ISUPPER()
// Determines whether the first character in a character expression is an uppercase alphabetic character.
//
//////
// Version 0.58
// Last update:
//     Sep.15.2015
//////
// Change log:
//     Sep.15.2015 - Initial creation by Stefano D'Amico
//////
// Parameters:
//     p1	-- Specifies the character expression that ISUPPER( ) evaluates.
//     p2	-- Optional, if true evaluates all string
//
//////
// Returns:
//    ISUPPER( ) returns true (.T.) if the first character in a character expression is an uppercase alphabetic character;
//    otherwise, ISUPPER( ) returns false (.F.).
//////
// Example:
//    ? ISUPPER("Aa")		&& Display .T.
//    ? ISUPPER("Aa")		&& Display .T.
//    ? ISUPPER("Aa", .T.) 	&& Display .F.
//    ? ISUPPER("AA", .T.)	&& Display .T.
//////
	void function_isupper(SFunctionParams* rpar)
	{
		SVariable*	varStr				= rpar->ip[0];
		SVariable*	varTestWholeString	= rpar->ip[1];

		bool		llTestWholeString, llIsUpper;
		bool		error;
		u32			errorNum;


		//////////
		// Parameters 1 must be present and character
		//////
			rpar->rp[0] = NULL;
			if (!iVariable_isValid(varStr) || !iVariable_isTypeCharacter(varStr))
			{
				iError_reportByNumber(_ERROR_P1_IS_INCORRECT, iVariable_get_relatedComp(varStr), false);
				return;
			}


		//////////
		// If present, parameter 2 must be bool
		//////
			if (varTestWholeString)
			{
				if (!iVariable_isFundamentalTypeLogical(varTestWholeString))
				{
					iError_reportByNumber(_ERROR_P2_IS_INCORRECT, iVariable_get_relatedComp(varTestWholeString), false);
					return;
				}

				// Grab the value
				llTestWholeString = iiVariable_getAs_bool(varTestWholeString, false, &error, &errorNum);
				if (error)
				{
					iError_reportByNumber(errorNum, iVariable_get_relatedComp(varTestWholeString), false);
					return;
				}

			} else {
				// Just testing the first character
				llTestWholeString = false;
			}


		//////////
		// Create and populate the return variable
		//////
			llIsUpper	= ifunction_iscommon(varStr, llTestWholeString, _isUpper);
			rpar->rp[0]	= iVariable_createAndPopulate_byText(_VAR_TYPE_LOGICAL, (cs8*)((llIsUpper) ? &_LOGICAL_TRUE : &_LOGICAL_FALSE), 1, true);
			if (!rpar->rp[0])
				iError_reportByNumber(_ERROR_INTERNAL_ERROR, iVariable_get_relatedComp(varStr), false);

	}




//////////
//
// Function: ISNULL()
// Determines whether an expression evaluates to null.
//
//////
// Version 0.57
// Last update:
//     Apr.22.2015
//////
// Change log:
//     Apr.06.2015 - Initial creation by Hernan Cano M
//////
// Parameters:
//     p1	-- Specifies the expression that ISNULL() evaluates.
//
//////
// Returns:
//    ISNULL() returns True (.T.) if the expression eExpression evaluates to null;
//    otherwise, ISNULL() returns False (.F.)
//////
// Example:
//    ? ISNULL("AA")	&& Display .F.
//    ? ISNULL("  ")	&& Display .F.
//    ? ISNULL(0.0)  	&& Display .F.
//    ? ISNULL(.null.)  && Display .T.
//////
	void function_isnull(SFunctionParams* rpar)
	{
		SVariable*	varExpr = rpar->ip[0];

		bool		llIsNull;


		//////////
		// Verify the variable is of a valid format
		//////
			rpar->rp[0] = NULL;
			if (!iVariable_isValidType(varExpr))
			{
				iError_reportByNumber(_ERROR_PARAMETER_IS_INCORRECT, iVariable_get_relatedComp(varExpr), false);
				return;
			}


		//////////
		// Create and populate the return variable
		//////
			llIsNull	= ifunction_isnull_common(varExpr);
			rpar->rp[0]	= iVariable_createAndPopulate_byText(_VAR_TYPE_LOGICAL, (cs8*)((llIsNull) ? &_LOGICAL_TRUE : &_LOGICAL_FALSE), 1, true);
			if (!rpar->rp[0])
				iError_reportByNumber(_ERROR_INTERNAL_ERROR, iVariable_get_relatedComp(varExpr), false);

	}

	bool ifunction_isnull_common(SVariable* varExpr)
	{
		bool llIsNull;


		//////////
		// Determine what we're evaluating
		//////
			llIsNull = true;
			switch (varExpr->varType)
			{
				case _VAR_TYPE_NULL:
				case _VAR_TYPE_DATE:
				case _VAR_TYPE_CHARACTER:
				case _VAR_TYPE_NUMERIC:
				case _VAR_TYPE_DATETIMEX:
				case _VAR_TYPE_DATETIME:
				case _VAR_TYPE_LOGICAL:
				case _VAR_TYPE_S8:
				case _VAR_TYPE_U8:
				case _VAR_TYPE_S16:
				case _VAR_TYPE_U16:
				case _VAR_TYPE_S32:
				case _VAR_TYPE_U32:
				case _VAR_TYPE_S64:
				case _VAR_TYPE_U64:
				case _VAR_TYPE_CURRENCY:
				case _VAR_TYPE_F32:
				case _VAR_TYPE_F64:
				case _VAR_TYPE_BI:  // Big integer
				case _VAR_TYPE_BFP: // Big floating point
					llIsNull = iVariable_isNull(varExpr);
					break;

				// We cannot (yet??) test NULL on the other types
				default:
					iError_reportByNumber(_ERROR_FEATURE_NOT_AVAILABLE, NULL, false);
					return(false);
			}


		//////////
		// Signify our result
		//////
			return(llIsNull);

	}
