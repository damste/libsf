//////////
//
// /libsf/source/vjr/commands/funcs/p.cpp
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
// Function: PADC(), PADL(), and PADR()
//
// and lowercases everything else.
//
//////
// Version 0.57
// Last update:
//     Aug.03.2014
//////
// Change log:
//     Aug.03.2014 - Initial creation
//////
// Parameters:
//     pExpression		-- The input, converted to character, and then aligned
//     pResultSize		-- The size of the result
//     pPadCharacter	-- Optional, the character to use, if unspecified then uses SPACE(1)
//
//////
// Returns:
//    Character         -- The string is converted from whatever it was to character, and
//                         then padded to its destination size. If the string is larger than
//                         the destination, then it remains as it is.
//////
	void function_padc(SReturnsParams* rpar)
	{
		SVariable* varExpr			= rpar->ip[0];
		SVariable* varResultSize	= rpar->ip[1];
		SVariable* varPadCharacter	= rpar->ip[2];


		// Return padc
		ifunction_pad_common(rpar, varExpr, varResultSize, varPadCharacter, true, true);
	}

	void function_padl(SReturnsParams* rpar)
	{
		SVariable* varExpr			= rpar->ip[0];
		SVariable* varResultSize	= rpar->ip[1];
		SVariable* varPadCharacter	= rpar->ip[2];


		// Return padl
		ifunction_pad_common(rpar, varExpr, varResultSize, varPadCharacter, true, false);
	}

	void function_padr(SReturnsParams* rpar)
	{
		SVariable* varExpr			= rpar->ip[0];
		SVariable* varResultSize	= rpar->ip[1];
		SVariable* varPadCharacter	= rpar->ip[2];


		// Return padr
		ifunction_pad_common(rpar, varExpr, varResultSize, varPadCharacter, false, true);
	}

	void ifunction_pad_common(SReturnsParams* rpar, SVariable* varExpr, SVariable* varResultSize, SVariable* varPadCharacter, bool tlPadLeft, bool tlPadRight)
	{
		u32			errorNum;
		s32			lnI, lnResultSize, lnCopyStart, lnPadLeftStopper, lnPadRightStart, lnPadRightStopper;
		bool		error;
		SVariable*	tempVar;
		SVariable*	result;


		//////////
        // Make sure our parameters are correct
		//////
			rpar->rp[0] = NULL;
			if (!tlPadLeft && !tlPadRight)
			{
				iError_reportByNumber(_ERROR_INTERNAL_ERROR, NULL, false);
				return;
			}


		//////////
		// Parameter 1 must be valid
		//////
			if (!iVariable_isValid(varExpr))
			{
				iError_reportByNumber(_ERROR_P1_IS_INCORRECT, NULL, false);
				return;
			}


		//////////
		// Parameter 2 must be numeric
		//////
			if (!iVariable_isValid(varResultSize) || !iVariable_isTypeNumeric(varResultSize))
			{
				iError_reportByNumber(_ERROR_P2_IS_INCORRECT, iVariable_get_relatedComp(varResultSize), false);
				return;
			}
			lnResultSize = iiVariable_getAs_s32(varResultSize, false, &error, &errorNum);
			if (error)
			{
				iError_reportByNumber(errorNum, iVariable_get_relatedComp(varResultSize), false);
				return;
			}


		//////////
		// Parameter 3 is optional, but if present...
		//////
			if (iVariable_isValid(varPadCharacter))
			{
				// ...it must be character
				if (!iVariable_isTypeCharacter(varPadCharacter))
				{
					iError_reportByNumber(_ERROR_P3_IS_INCORRECT, iVariable_get_relatedComp(varPadCharacter), false);
					return;
				}

				// Validate the pad character is at least one character long
				if (varPadCharacter->value.length == 0)
				{
					iError_report((cu8*)"Parameter 3 must be at least one character", false);
					return;
				}

			} else {
				// The first occurrence is what we're after
				varPadCharacter = cvarSpace1;
			}


		//////////
		// Create the return variable
		//////
			tempVar = iVariable_convertForDisplay(varExpr);

			// If it wasn't created, or it's already as long or longer than its target, return it
			if (!tempVar || tempVar->value.length >= lnResultSize)
			{
				rpar->rp[0] = tempVar;
				return;
			}

			// If we get here, the result will be needed
			result = iVariable_create(_VAR_TYPE_CHARACTER, NULL, true);
			if (!result)
			{
				iError_report(cgcInternalError, false);
				return;
			}

			// Populate
			iDatum_allocateSpace(&result->value, lnResultSize);


		//////////
		// Determine where the string should go
		//////
			if (tlPadLeft && tlPadRight)
			{
				// Pad both
				lnCopyStart			= (lnResultSize - tempVar->value.length) / 2;
				lnPadLeftStopper	= lnCopyStart;
				lnPadRightStart		= lnCopyStart + tempVar->value.length;
				lnPadRightStopper	= lnResultSize;

			} else if (tlPadLeft) {
				// Pad left
				lnCopyStart			= lnResultSize - tempVar->value.length;
				lnPadLeftStopper	= lnCopyStart;
				lnPadRightStart		= -1;
				lnPadRightStopper	= -1;

			} else {
				// Pad right
				lnCopyStart			= 0;
				lnPadLeftStopper	= -1;
				lnPadRightStart		= tempVar->value.length;
				lnPadRightStopper	= lnResultSize;
			}


		//////////
		// Pad left
		//////
			if (lnPadLeftStopper >= 1)
			{
				// Iterate through every cycle required to populate the left side
				for (lnI = 0; lnI < lnPadLeftStopper; lnI += varPadCharacter->value.length)
				{
					// Copy this string, or as much of it will fit
					memcpy(result->value.data + lnI, varPadCharacter->value.data, min(lnPadLeftStopper - lnI, varPadCharacter->value.length));
				}
			}


		//////////
		// Pad right
		//////
			if (lnPadRightStopper >= 1)
			{
				// Iterate through every cycle required to populate the right side
				for (lnI = lnPadRightStart; lnI < lnPadRightStopper; lnI += varPadCharacter->value.length)
				{
					// Copy this string, or as much of it will fit
					memcpy(result->value.data + lnI, varPadCharacter->value.data, min(lnPadRightStopper - lnI, varPadCharacter->value.length));
				}
			}


		//////////
		// Copy the source string and delete the source string variable
		//////
			// Copy the string
			memcpy(result->value.data + lnCopyStart, tempVar->value.data, tempVar->value.length);


		//////////
		// Delete our temporary variable
		//////
			iVariable_delete(tempVar, true);


		//////////
		// Indicate our status
		//////
			rpar->rp[0] = result;

	}




//////////
//
// Function: PAYMENT()
// Returns the amount of each periodic payment on a fixed-interest loan.
//
//////
// Version 0.57
// Last update:
//     Mar.19.2015
//////
// Change log:
//     Mar.19.2015 - Initial creation by Stefano D'Amico
//////
// Parameters:
//     p1			-- Specifies the periodic payment amount.
//     p2			-- Specifies the periodic interest rate.
//     p3			-- Specifies the total number of payments.
//
//////
// Returns:
//    PAYMENT( ) assumes a constant periodic interest rate and assumes that payments are made at the end of each period.
//////
// Example:
//   ? PAYMENT(500, 0.006, 48)	&& Displays 12.02
//////
	void function_payment(SReturnsParams* rpar)
	{
		SVariable* varPayment		= rpar->ip[0];
		SVariable* varInterestRate	= rpar->ip[1];
		SVariable* varPeriods		= rpar->ip[2];


		// Return payment
		ifunction_numbers_common(rpar, varPayment, varInterestRate, varPeriods, _FP_COMMON_PAYMENT, _VAR_TYPE_F64, false, true);
	}




//////////
//
// Function: PI()
// Returns the numeric constant pi.
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
//     none
//////
// Returns:
//    Numeric		-- Returns the numeric constant pi
//////
// Example:
//    ? pi()				&& Displays 3.14
//////
	void function_pi(SReturnsParams* rpar)
	{
		// Return pi
		ifunction_numbers_common(rpar, NULL, NULL, NULL, _FP_COMMON_PI, _VAR_TYPE_F64, false, false);
	}




//////////
//
// Function: POW()
// Return x to the power y, if z is present, return x to the power y, modulo z.
//
//////
// Version 0.57
// Last update:
//     Apr.26.2015
//////
// Change log:
//     Apr.26.2015 - Initial creation by Stefano D'Amico
//////
// Parameters:
//     varP1		-- Numeric
//     varP2		-- Numeric
//	   varP3		-- [Optional] Numeric 
//////
// Returns:
//    Numeric		--	Returns varP1 to the power varP2; if varP3 is present, return varP1 to the power varP2, modulo varP3.
//						If varP1, varP2, and varP3 are all integer, then Euler's algorithm can be used, which is faster.
//////
// Example:
//    ? pow(10, 3456789, 3)				&& Displays 1
//    ? pow(10.0, 3456789.0, 3.0)		&& Displays 1.00
//////
	void function_pow(SReturnsParams* rpar)
	{
		SVariable*	varP1 = rpar->ip[0];
		SVariable*	varP2 = rpar->ip[1];
		SVariable*	varP3 = rpar->ip[2];

		f64			lfVal1, lfVal2, lfVal3, lfResult;
		s64			lnPower, lnResult, lnExp, lnMod;
		bool		llIsP1Valid, llIsP2Valid, llIsP3Valid, llIsP1Integer, llIsP2Integer, llIsP3Integer;
		bool		error, error1, error2, error3;
		u32			errorNum;
		SVariable*	result;


		//////////
		// Determine parameter input formats
		//////
			rpar->rp[0] = NULL;
			llIsP1Valid = (iVariable_isValid(varP1) && iVariable_isTypeNumeric(varP1));
			llIsP2Valid = (iVariable_isValid(varP2) && iVariable_isTypeNumeric(varP2));
			if (llIsP1Valid && llIsP2Valid)
			{
				// If three parameters, we perform a power/mod
				if (rpar->ipCount == 3)
				{
					// POW(p1, p2, p3)
					llIsP1Integer	= iVariable_isTypeInteger(varP1);
					llIsP2Integer	= iVariable_isTypeInteger(varP2);

					llIsP3Valid		= (iVariable_isValid(varP3) && iVariable_isTypeNumeric(varP3));
					if (llIsP3Valid)
						llIsP3Integer = iVariable_isTypeInteger(varP3);

				} else {
					// POW(p1, p2)
					llIsP1Integer	= false;	// Default to floating point algorithm
					llIsP2Integer	= false;	// Default to floating point algorithm
					llIsP3Valid		= true;
				}
			}


		/////////
		// Validate parameters
		//////
			if (!llIsP1Valid || !llIsP2Valid || !llIsP3Valid)
			{
				iError_reportByNumber(_ERROR_INVALID_ARGUMENT_TYPE_COUNT, iVariable_get_relatedComp(((!llIsP1Valid) ? varP1 : ((!llIsP2Valid) ? varP2 : varP3))), false);
				return;
			}


		//////////
		// Can we use Euler's algorithm?
		// To do so, all three parameters must be integer.
		//////
			if (rpar->ipCount == 3 && llIsP1Integer && llIsP2Integer && llIsP3Integer)
			{
				//////////
				// Grab varP1
				//////
					lnPower = iiVariable_getAs_s64(varP1, false, &error, &errorNum);
					if (error)
					{
						iError_reportByNumber(errorNum, iVariable_get_relatedComp(varP1), false);
						return;
					}


				//////////
				// Grab varP2, and validate it's non-negative
				//////
					lnExp = iiVariable_getAs_s64(varP2, false, &error, &errorNum);
					if (error || (lnExp < 0 && (errorNum = _ERROR_PARAMETER_IS_INCORRECT)))
					{
						iError_reportByNumber(errorNum, iVariable_get_relatedComp(varP2), false);
						return;
					}


				//////////
				// Grab varP3 and validate it's not zero
				//////
					lnMod = iiVariable_getAs_s64(varP3, false, &error, &errorNum);
					if (error || (lnMod == 0 && (errorNum = _ERROR_CANNOT_BE_ZERO)))
					{
						// Error, or 0
						iError_reportByNumber(errorNum, iVariable_get_relatedComp(varP3), false);
						return;
					}


				//////////
				// Compute x^y % z using Euler's theorem
				//////
					lnResult = 1;
					for (lnResult = 1; lnExp; lnPower = (lnPower * lnPower) % lnMod, lnExp >>= 1)
					{
						// Every other iteration...
						if (lnExp & 1)
							lnResult = (lnResult * lnPower) % lnMod;
					}


				//////////
				// Create the value
				//////
					result = iVariable_createAndPopulate_byText(_VAR_TYPE_S64, (cs8*)&lnResult, sizeof(lnResult), false);


			} else {
				// Fall-back on the slower algorithm

				//////////
				// Grab as f64
				//////
					lfVal1 = iiVariable_getAs_f64(varP1, false, &error1, &errorNum);
					lfVal2 = iiVariable_getAs_f64(varP2, false, &error2, &errorNum);

					// Grab P3 if need be
					error3 = false;
					if (rpar->ipCount == 3)		lfVal3 = iiVariable_getAs_f64(varP3, false, &error3, &errorNum);
					else						lfVal3 = 1.0;

					// Make sure we don't have an error in conversion, and that lfValue3 is > 0.0
					if (error1 || error2 || error3 || (lfVal3 <= 0.0 && (error3 = true) && (errorNum = _ERROR_INVALID_ARGUMENT_TYPE_COUNT)))
					{
						iError_reportByNumber(errorNum, iVariable_get_relatedComp(((error1) ? varP1 : ((error2) ? varP2 : varP3))), false);
						return;
					}


				//////////
				// Compute power
				//////
					lfResult = pow(lfVal1, lfVal2);


				//////////
				// Mod if need be
				//////
					if (rpar->ipCount == 3)
						lfResult = fmod(lfResult, lfVal3);


				//////////
				// Create output variable
				//////
					result = iVariable_createAndPopulate_byText(_VAR_TYPE_F64, (cs8*)&lfResult, sizeof(lfResult), false);

			}


		//////////
		// Are we good?
		//////
			if (!result)
				iError_reportByNumber(_ERROR_INTERNAL_ERROR, iVariable_get_relatedComp(varP1), false);


		//////////
        // Signify the result
		//////
			rpar->rp[0] = result;

	}




//////////
//
// Function: PROPER()
// Converts the first character after every space to upper-case,
// and lowercases everything else.
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
//     pString		-- Character, the string to proper
//
//////
// Returns:
//    Character		-- The string with all words proper'd (if I can use that as a verb)
//////
	void function_proper(SReturnsParams* rpar)
	{
		SVariable*	varString = rpar->ip[0];
		s32			lnI;
		bool		llUpperNext;
        SVariable*	result;


		//////////
		// Parameter 1 must be character
		//////
			rpar->rp[0] = NULL;
			if (!iVariable_isValid(varString) || iVariable_getType(varString) != _VAR_TYPE_CHARACTER)
			{
				iError_reportByNumber(_ERROR_P1_IS_INCORRECT, iVariable_get_relatedComp(varString), false);
				return;
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
        // Copy the source string
		//////
	        iDatum_duplicate(&result->value, &varString->value);


		//////////
		// Upper every first character after a space, and lower every character
		//////
			llUpperNext = true;
			for (lnI = 0; lnI < result->value.length; lnI++)
			{
				// Spaces are treated differently
				if (result->value.data[lnI] == 32)
				{
					// We've found a space, the next one will be upper-case
					llUpperNext = true;

				} else {
					// We're on data
					if (llUpperNext)
					{
						// Make this one uppercase if it's lower
						llUpperNext = false;
						if (result->value.data[lnI] >= 'a' && result->value.data[lnI] <= 'z')
							result->value.data[lnI] -= 0x20;

					} else {
						// Make this one lowercase if it's upper
						if (result->value.data[lnI] >= 'A' && result->value.data[lnI] <= 'Z')
							result->value.data[lnI] += 0x20;
					}
				}
			}


		//////////
        // Return our converted result
		//////
			rpar->rp[0] = result;

	}




//////////
//
// Function: PV()
// Returns the present value of an investment.
//
//////
// Version 0.57
// Last update:
//     Mar.19.2015
//////
// Change log:
//     Mar.19.2015 - Refactoring by Stefano D'Amico
//     Mar.18.2015 - Initial creation by Stefano D'Amico
//////
// Parameters:
//     p1			-- Specifies the periodic payment amount.
//     p2			-- Specifies the periodic interest rate.
//     p3			-- Specifies the total number of payments.
//
//////
// Returns:
//    PV( ) computes the present value of an investment based on a series of equal periodic payments at a constant periodic interest rate.
//////
// Example:
//   ? PV(500, 0.006, 48)	&& Displays 20799.41
//////
	void function_pv(SReturnsParams* rpar)
	{
		SVariable* varPayment		= rpar->ip[0];
		SVariable* varInterestRate	= rpar->ip[1];
		SVariable* varPeriods		= rpar->ip[2];


		// Return pv
		ifunction_numbers_common(rpar, varPayment, varInterestRate, varPeriods, _FP_COMMON_PV, _VAR_TYPE_F64, false, true);
	}
