//////////
//
// /libsf/source/vjr/commands/funcs/r.cpp
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
// Function: RANGER()
// Force Into Range.  The function is the equivalent of xResult = MIN(MAX(xVar, xMin), xMax)).
//
//////
// Version 0.58   (Determine the current version from the header in vjr.cpp)
// Last update:
//     Mar.14.2015
//////
// Change log:
//     Mar.14.2015 - GitHub commit by Rick C. Hodgin, refactoring into varExpr type
//     Mar.13.2015 - Initial creation by Stefano D'Amico
//////
// Parameters:
//    varExpr	-- Specifies the expression to valuate
//    varMin		-- Specifies the min range
//    varMin		-- Specifies the max range
//
//////
// Returns:
//   Returns the value forced into the range xMin..xMax
//////
// Example:
//  x = 10
//	? x                            && Displays 10
//	? RANGER(x, 20, 80)            && Displays 20
//	x = RANGER(x, 20, 80)          && Can be used as assignment
//	? x							   && Displays 20
//////
	void function_ranger(SReturnsParams* rpar)
	{
		SVariable* varExpr	= rpar->ip[0];
		SVariable* varMin	= rpar->ip[1];
		SVariable* varMax	= rpar->ip[2];


		// Return ranger
		ifunction_ranger_common(rpar, varExpr, varMin, varMax, NULL);
	}

	void function_ranger2(SReturnsParams* rpar)
	{
		SVariable*	varExpr	= rpar->ip[0];
		SVariable*	varMin	= rpar->ip[1];
		SVariable*	varMax	= rpar->ip[2];
		bool		llRanged;
		SVariable*	result;


		//////////
		// Range the result
		//////
			ifunction_ranger_common(rpar, varExpr, varMin, varMax, &llRanged);
			result = rpar->rp[0];


		//////////
		// If ranged, update varExpr to the new range
		//////
			if (llRanged && result && iVariable_isValid(varExpr))
				iVariable_set(varExpr, result);
	}

	void ifunction_ranger_common(SReturnsParams* rpar, SVariable* varExpr, SVariable* varMin, SVariable* varMax, bool* tlRanged)
	{
		SVariable*		tempMin;
		SVariable*		tempMax;
		SVariable*		tempResult1;
		SVariable*		tempResult2;
		SVariable*		result;
		SReturnsParams	lsrpar;



		//////////
		// Test Parameter 1
		//////
			rpar->rp[0] = NULL;
			if (!iVariable_isValid(varExpr))
			{
				iError_report_byNumber(_ERROR_P1_IS_INCORRECT, iVariable_get_relatedComp(varExpr), false);
				return;
			}


		//////////
		// Test Parameter 2
		//////
			if (!iVariable_isValid(varMin))
			{
				iError_report_byNumber(_ERROR_P2_IS_INCORRECT, iVariable_get_relatedComp(varMin), false);
				return;
			}


		//////////
		// Test Parameter 3
		//////
			if (!iVariable_isValid(varMax))
			{
				iError_report_byNumber(_ERROR_P2_IS_INCORRECT, iVariable_get_relatedComp(varMax), false);
				return;
			}


		//////////
		// They must be the same type
		//////
			if (iVariable_get_fundamentalType(varExpr) != iVariable_get_fundamentalType(varMin))
			{
				// Operand mismatch
				iError_report_byNumber(_ERROR_DATA_TYPE_MISMATCH, iVariable_get_relatedComp(varMin), false);
				return;
			}
			if (iVariable_get_fundamentalType(varExpr) != iVariable_get_fundamentalType(varMax))
			{
				// Operand mismatch
				iError_report_byNumber(_ERROR_DATA_TYPE_MISMATCH, iVariable_get_relatedComp(varMax), false);
				return;
			}


		//////////
		// Initialize
		//////
			tempMin			= NULL;
			tempMax			= NULL;
			tempResult1		= NULL;
			tempResult2		= NULL;


		//////////
		// Verify we are working with properly ordered min/max
		//////
			do {
				// Loop entered for structured programming
				memcpy(&lsrpar, rpar, sizeof(lsrpar));
				lsrpar.ip[0] = varMin;
				lsrpar.ip[1] = varMax;
				function_min(&lsrpar);
				if ((tempMin = lsrpar.rp[0]) == NULL)
				{
					iError_report_byNumber(_ERROR_INTERNAL_ERROR, iVariable_get_relatedComp(varMax), false);
					return;
				}
				function_max(&lsrpar);
				if ((tempMax = lsrpar.rp[0]) == NULL)
				{
					iError_report_byNumber(_ERROR_INTERNAL_ERROR, iVariable_get_relatedComp(varMax), false);
					break;
				}


			//////////
			// RANGER() executed as "result = MIN(MAX(xVar, xMin), xMax))"
			//////
				// Compute first part of result
				lsrpar.ip[0] = varExpr;
				lsrpar.ip[1] = tempMin;
				function_max(&lsrpar);
				if ((tempResult1 = lsrpar.rp[0]) == NULL)
				{
					iError_report_byNumber(_ERROR_INTERNAL_ERROR, iVariable_get_relatedComp(varMax), false);
					break;
				}

				// Compute the final result
				lsrpar.ip[0]	= tempResult1;
				lsrpar.ip[1]	= tempMax;
				function_min(&lsrpar);
				tempResult2			= lsrpar.rp[0];

				// Force the result into the same form as varExpr originally was
				if (tempResult2)
				{
					// Create one of the same type, and populate
					result = iVariable_create(varExpr->varType, NULL, true);
					if (result)
					{
						// Convert to the target type for propagation through the expression
						if (!iVariable_setNumeric_toDestinationType(result, tempResult2))
							iError_report_byNumber(_ERROR_INTERNAL_ERROR, iVariable_get_relatedComp(varExpr), false);
					}

				} else {
					iError_report_byNumber(_ERROR_INTERNAL_ERROR, iVariable_get_relatedComp(varMax), false);
				}

				// All done
				break;

			} while (1);


		//////////
		// Delete our temporary variables
		/////
			if (tempMin)		iVariable_delete(tempMin,		true);
			if (tempMax)		iVariable_delete(tempMax,		true);
			if (tempResult1)	iVariable_delete(tempResult1,	true);
			if (tempResult2)	iVariable_delete(tempResult2,	true);


		//////////
		// Indicate our true result
		//////
			rpar->rp[0] = result;

	}




//////////
//
// Function: REPLICATE()
// Returns the indicated string replicated N times.
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
//     pString		-- Character, the string to replicate
//     pCount		-- Numeric, the number of copies to generate
//
//////
// Returns:
//    Character		-- The string of the input replicated N times
//////
	void function_replicate(SReturnsParams* rpar)
	{
		SVariable*	varString	= rpar->ip[0];
		SVariable*	varCount	= rpar->ip[1];
		s32			lnI, lnCopies;
		u32			errorNum;
		bool		error;
        SVariable*	result;


		//////////
		// Parameter 1 must be character
		//////
			rpar->rp[0] = NULL;
			if (!iVariable_isValid(varString) || iVariable_getType(varString) != _VAR_TYPE_CHARACTER)
			{
				iError_report_byNumber(_ERROR_P1_IS_INCORRECT, iVariable_get_relatedComp(varString), false);
				return;
			}


		//////////
		// Parameter 2 must be nmumeric
		//////
			if (!iVariable_isValid(varCount) || !iVariable_isTypeNumeric(varCount))
			{
				iError_report_byNumber(_ERROR_P2_IS_INCORRECT, iVariable_get_relatedComp(varCount), false);
				return;
			}


		//////////
        // Find out how long they want our string to be
		//////
			lnCopies = iiVariable_getAs_s32(varCount, false, &error, &errorNum);
			if (error)
			{
				iError_report_byNumber(errorNum, iVariable_get_relatedComp(varCount), false);
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

			if (lnCopies > 0 && varString->value.length > 0)
			{
				// Repeat the string as many as are indicated
				iDatum_allocateSpace(&result->value, lnCopies * varString->value.length);
				for (lnI = 0; lnI < lnCopies; lnI++)
					memcpy(result->value.data + (lnI * varString->value.length), varString->value.data, varString->value.length);
			}


		//////////
        // Return our converted result
		//////
			rpar->rp[0] = result;

	}




//////////
//
// Function: RGB()
// Returns the RGB() of the three input values.
//
//////
// Version 0.58   (Determine the current version from the header in vjr.cpp)
// Last update:
//     Jul.13.2014
//////
// Change log:
//     Jul.13.2014 - Initial creation
//////
// Parameters:
//     pRed			-- Red, in the range 0..255, or 0.0..1.0
//     pGrn			-- Green, in the range 0..255, or 0.0..1.0
//     pBlu			-- Blue, in the range 0..255, or 0.0..1.0
//
//////
// Returns:
//    Numeric		-- Constructed RGB() integer
//
//////
	void function_rgb(SReturnsParams* rpar)
	{
		SVariable* varRed	= rpar->ip[0];
		SVariable* varGrn	= rpar->ip[1];
		SVariable* varBlu	= rpar->ip[2];


		// Return rgb
		ifunction_rgba_common(rpar, varRed, varGrn, varBlu, NULL);
	}

	void ifunction_rgba_common(SReturnsParams* rpar, SVariable* varRed, SVariable* varGrn, SVariable* varBlu, SVariable* varAlp)
	{
		f32			lfRed, lfGrn, lfBlu, lfAlp;
		s32			lnRed, lnGrn, lnBlu, lnAlp;
		bool		error;
		u32			errorNum;
		SVariable*	result;


		//////////
		// Parameter 1 must be numeric
		//////
			rpar->rp[0] = NULL;
			if (!iVariable_isValid(varRed) || !iVariable_isTypeNumeric(varRed))
			{
				iError_report_byNumber(_ERROR_PARAMETER_IS_INCORRECT, iVariable_get_relatedComp(varRed), false);
				return;
			}


		//////////
		// Parameter 2 must be numeric
		//////
			if (!iVariable_isValid(varGrn) || !iVariable_isTypeNumeric(varGrn))
			{
				iError_report_byNumber(_ERROR_PARAMETER_IS_INCORRECT, iVariable_get_relatedComp(varGrn), false);
				return;
			}


		//////////
		// Parameter 3 must be numeric
		//////
			if (!iVariable_isValid(varBlu) || !iVariable_isTypeNumeric(varBlu))
			{
				iError_report_byNumber(_ERROR_PARAMETER_IS_INCORRECT, iVariable_get_relatedComp(varBlu), false);
				return;
			}


		//////////
		// Parameter 4 must be numeric
		//////
			if (varAlp)
			{
				if (!iVariable_isValid(varAlp) || !iVariable_isTypeNumeric(varAlp))
				{
					iError_report_byNumber(_ERROR_PARAMETER_IS_INCORRECT, iVariable_get_relatedComp(varAlp), false);
					return;
				}

			} else {
				// Default to fully transparent or fully opaque based on its ncset()
				if (propGet_settings_ncset_alphaIsOpaque(_settings))	varAlp = cvarTwoFiftyFive;
				else													varAlp = cvarZero;
			}


		//////////
		// Red
		//////
			if (iVariable_isTypeFloatingPoint(varRed))
			{
				// It is a floating point, which means it must be in the range 0..1
				lfRed = iiVariable_getAs_f32(varRed, false, &error, &errorNum);
				if (error)
				{
					iError_report_byNumber(errorNum, iVariable_get_relatedComp(varRed), false);
					return;
				}
				lnRed = (s32)(255.0f * min(max(lfRed, 0.0f), 1.0f));

			} else {
				// It is an integer, which means it must be in the range 0..255
				lnRed = iiVariable_getAs_s32(varRed, false, &error, &errorNum);
				if (error)
				{
					iError_report_byNumber(errorNum, iVariable_get_relatedComp(varRed), false);
					return;
				}
			}
			if (lnRed < 0 || lnRed > 255)
			{
				iError_report_byNumber(_ERROR_OUT_OF_RANGE, iVariable_get_relatedComp(varRed), false);
				return;
			}


		//////////
		// Green
		//////
			if (iVariable_isTypeFloatingPoint(varGrn))
			{
				// It is a floating point, which means it must be in the range 0..1
				lfGrn = iiVariable_getAs_f32(varGrn, false, &error, &errorNum);
				if (error)
				{
					iError_report_byNumber(errorNum, iVariable_get_relatedComp(varGrn), false);
					return;
				}
				lnGrn = (s32)(255.0f * min(max(lfGrn, 0.0f), 1.0f));

			} else {
				// It is an integer, which means it must be in the range 0..255
				lnGrn = iiVariable_getAs_s32(varGrn, false, &error, &errorNum);
				if (error)
				{
					iError_report_byNumber(errorNum, iVariable_get_relatedComp(varGrn), false);
					return;
				}
			}
			if (lnGrn < 0 || lnGrn > 255)
			{
				iError_report_byNumber(_ERROR_OUT_OF_RANGE, iVariable_get_relatedComp(varGrn), false);
				return;
			}


		//////////
		// Blue
		//////
			if (iVariable_isTypeFloatingPoint(varBlu))
			{
				// It is a floating point, which means it must be in the range 0..1
				lfBlu = iiVariable_getAs_f32(varBlu, false, &error, &errorNum);
				if (error)
				{
					iError_report_byNumber(errorNum, iVariable_get_relatedComp(varBlu), false);
					return;
				}
				lnBlu = (s32)(255.0f * min(max(lfBlu, 0.0f), 1.0f));

			} else {
				// It is an integer, which means it must be in the range 0..255
				lnBlu	= iiVariable_getAs_s32(varBlu, false, &error, &errorNum);
				if (error)
				{
					iError_report_byNumber(errorNum, iVariable_get_relatedComp(varBlu), false);
					return;
				}
			}
			if (lnBlu < 0 || lnBlu > 255)
			{
				iError_report_byNumber(_ERROR_OUT_OF_RANGE, iVariable_get_relatedComp(varBlu), false);
				return;
			}


		//////////
		// Alpha
		//////
			if (iVariable_isTypeFloatingPoint(varAlp))
			{
				// It is a floating point, which means it must be in the range 0..1
				lfAlp = iiVariable_getAs_f32(varAlp, false, &error, &errorNum);
				if (error)
				{
					iError_report_byNumber(errorNum, iVariable_get_relatedComp(varAlp), false);
					return;
				}
				lnAlp = (s32)(255.0f * min(max(lfAlp, 0.0f), 1.0f));

			} else {
				// It is an integer, which means it must be in the range 0..255
				lnAlp	= iiVariable_getAs_s32(varAlp, false, &error, &errorNum);
				if (error)
				{
					iError_report_byNumber(errorNum, iVariable_get_relatedComp(varAlp), false);
					return;
				}
			}
			if (lnAlp < 0 || lnAlp > 255)
			{
				iError_report_byNumber(_ERROR_OUT_OF_RANGE, iVariable_get_relatedComp(varAlp), false);
				return;
			}


		//////////
        // Create the return(result)
		//////
	        result = iVariable_create(_VAR_TYPE_U32, NULL, true);
			if (!result)
			{
				iError_report(cgcInternalError, false);
				return;
			}


		//////////
        // Populate the return value
		//////
			*(u32*)result->value.data = bgra((u32)lnBlu, (u32)lnGrn, (u32)lnRed, (u32)lnAlp);


		//////////
        // Return our converted result
		//////
	        rpar->rp[0] = result;
	}




//////////
//
// Function: RGBA()
// Returns the RGBA() of the four input values.
//
//////
// Version 0.58   (Determine the current version from the header in vjr.cpp)
// Last update:
//     Jul.13.2014
//////
// Change log:
//     Jul.13.2014 - Initial creation
//////
// Parameters:
//     pRed			-- Red, in the range 0..255, or 0.0..1.0
//     pGrn			-- Green, in the range 0..255, or 0.0..1.0
//     pBlu			-- Blue, in the range 0..255, or 0.0..1.0
//     pAlp			-- Blue, in the range 0..255, or 0.0..1.0
//
//////
// Returns:
//    Numeric		-- Constructed RGBA() integer
//
//////
	void function_rgba(SReturnsParams* rpar)
	{
		SVariable* varRed	= rpar->ip[0];
		SVariable* varGrn	= rpar->ip[1];
		SVariable* varBlu	= rpar->ip[2];
		SVariable* varAlp	= rpar->ip[3];


		// Return rgba
		ifunction_rgba_common(rpar, varRed, varGrn, varBlu, varAlp);
	}




//////////
//
// Function: RED()
// Retrieves the red channel from an RGBA or BGRA color.
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
	void function_red(SReturnsParams* rpar)
	{
		SVariable* varColor = rpar->ip[0];


		// Return red
		ifunction_color_common(rpar, varColor, 0x000000ff, 0);
	}

	void ifunction_color_common(SReturnsParams* rpar, SVariable* varColor, u32 tnMask, u32 tnShift)
	{
		u32			lnColor;
		bool		error;
		u32			errorNum;
		SVariable*	result;


		//////////
		// Color must be numeric
		//////
			rpar->rp[0] = NULL;
			if (!iVariable_isValid(varColor) || !iVariable_isTypeNumeric(varColor))
			{
				iError_report_byNumber(_ERROR_PARAMETER_IS_INCORRECT, iVariable_get_relatedComp(varColor), false);
				return;
			}


		//////////
		// Grab the value
		//////
			lnColor = iiVariable_getAs_u32(varColor, false, &error, &errorNum);
			if (error)
			{
				iError_report_byNumber(errorNum, iVariable_get_relatedComp(varColor), false);
				return;
			}


		//////////
		// Apply the mask and shift
		//////
			lnColor &= tnMask;
			if (tnShift != 0)
				lnColor >>= tnShift;


		//////////
		// Construct our result
		//////
			result = iVariable_create(_VAR_TYPE_U32, NULL, true);
			if (!result)
			{
				iError_report_byNumber(_ERROR_INTERNAL_ERROR, NULL, false);
				return;
			}


		//////////
		// Populate and return our result
		//////
			*result->value.data_u32 = lnColor;
			rpar->rp[0] = result;
	}




//////////
//
// Function: RIGHT()
// Returns the right N characters of a string.
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
//     pString		-- Character, the string to trim
//     pCount		-- Numeric, the number of characters to copy
//
//////
// Returns:
//    Character		-- The string of the right N characters
//////
	void function_right(SReturnsParams* rpar)
	{
		SVariable*	varString	= rpar->ip[0];
		SVariable*	varCount	= rpar->ip[1];
		s32			lnStart, lnLength;
		u32			errorNum;
		bool		error;
        SVariable*	result;


		//////////
		// Parameter 1 must be character
		//////
			rpar->rp[0] = NULL;
			if (!iVariable_isValid(varString) || iVariable_getType(varString) != _VAR_TYPE_CHARACTER)
			{
				iError_report_byNumber(_ERROR_P1_IS_INCORRECT, iVariable_get_relatedComp(varString), false);
				return;
			}


		//////////
		// Parameter 2 must be nmumeric
		//////
			if (!iVariable_isValid(varCount) || !iVariable_isTypeNumeric(varCount))
			{
				iError_report_byNumber(_ERROR_P2_IS_INCORRECT, iVariable_get_relatedComp(varCount), false);
				return;
			}


		//////////
        // Find out how long they want our string to be
		//////
			lnLength = iiVariable_getAs_s32(varCount, false, &error, &errorNum);
			if (error)
			{
				iError_report_byNumber(errorNum, iVariable_get_relatedComp(varCount), false);
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
        // Copy as much of the source string as will fit
		//////
			if (lnLength >= varString->value.length)
			{
				// Copy only the length of the current string
				iDatum_duplicate(&result->value, &varString->value);

			} else if (lnLength > 0) {
				// We can do an extraction
				lnStart = varString->value.length - lnLength;
				iDatum_duplicate(&result->value, varString->value.data_u8 + lnStart, lnLength);
			}


		//////////
        // Return our converted result
		//////
			rpar->rp[0] = result;

	}




//////////
//
// Function: ROUND()
// Returns a numeric expression rounded to a specified number of decimal places.
//
//////
// Version 0.58   (Determine the current version from the header in vjr.cpp)
// Last update:
//     Mar.17.2015
//////
// Change log:
//     Mar.17.2015 - Initial creation by Stefano D'Amico
//////
// Parameters:
//    varNumber			-- Specifies the numeric expression whose value is to be rounded.
//    varDecimalPlaces	-- Specifies the number of decimal places nExpression is rounded to.
//
//////
// Returns:
//    Numeric		-- ROUND( ) returns a value rounded to the nearest decimal position as specified by nDecimalPlaces.
//////
// Example:
//    ? ROUND(53.213, 2)   && 53.21
//    ? ROUND(532, -2)     && 500
//////
	void function_round(SReturnsParams* rpar)
	{
		SVariable*	varNumber			= rpar->ip[0];
		SVariable*	varDecimalPlaces	= rpar->ip[1];
		f64			lfValue, lfRounded;
		s32			lnDecimalPlaces;
		bool		error;
		u32			errorNum;
		SVariable*	result;


//TODO: more speed by type checking :-)

		//////////
		// Parameter 1 must be numeric
		//////
			rpar->rp[0] = NULL;
			if (!iVariable_isValid(varNumber) || !iVariable_isTypeNumeric(varNumber))
			{
				iError_report_byNumber(_ERROR_P1_IS_INCORRECT, iVariable_get_relatedComp(varNumber), false);
				return;
			}


		//////////
		// Parameter 2 must be numeric
		//////
			if (!iVariable_isValid(varDecimalPlaces) || !iVariable_isTypeNumeric(varDecimalPlaces))
			{
				iError_report_byNumber(_ERROR_P2_IS_INCORRECT, iVariable_get_relatedComp(varDecimalPlaces), false);
				return;
			}


		//////////
		// Grab the p1, convert to f64
		//////
			lfValue = iiVariable_getAs_f64(varNumber, false, &error, &errorNum);
			if (error)
			{
				iError_report_byNumber(errorNum, iVariable_get_relatedComp(varNumber), false);
				return;
			}


		//////////
		// Grab the p2, convert to s32
		//////
			lnDecimalPlaces = iiVariable_getAs_s32(varDecimalPlaces, false, &error, &errorNum);
			if (error)
			{
				iError_report_byNumber(errorNum, iVariable_get_relatedComp(varDecimalPlaces), false);
				return;
			}


		//////////
		// Check -18<=lnDecimalPlaces<=16,  max 16 :-(
		//////
			if (lnDecimalPlaces < -18 || lnDecimalPlaces > 16)
			{
				iError_report_byNumber(_ERROR_OUT_OF_RANGE, iVariable_get_relatedComp(varDecimalPlaces), false);
				return;
			}

		//////////
		// Compute round
		//////
			lfRounded = ((s64)(lfValue * pow(10.0, lnDecimalPlaces) + .5) / pow(10.0, lnDecimalPlaces));


		//////////
        // Create the return(result)
		//////
	        result = iVariable_create(varNumber->varType, NULL, true);
			if (!result)
			{
				iError_report(cgcInternalError, false);
				return;
			}


		//////////
        // Populate the return value
		//////
			if (!iVariable_setNumeric_toNumericType(result, NULL, &lfRounded, NULL, NULL, NULL, NULL))
				iError_report_byNumber(errorNum, iVariable_get_relatedComp(varNumber), false);


		//////////
        // Return our result
		//////
			rpar->rp[0] = result;

	}





//////////
//
// Function: RTOD()
// Converts radians to its equivalent in degrees.
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
//    RTOD(n) of the value in p1
//////
// Example:
//    ? RTOD(PI())		&& Display 180.00
//////
    void function_rtod(SReturnsParams* rpar)
    {
		SVariable* varNumber = rpar->ip[0];


        // Return rtod
		ifunction_numbers_common(rpar, varNumber, NULL, NULL, _FP_COMMON_RTOD, _VAR_TYPE_F64, false, false);
	}




//////////
//
// Function: RTRIM()
// Trims spaces off the end of the string.
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
//     pString		-- Character, the string to trim
//
//////
// Returns:
//    Character		-- The string with any trailing spaces removed
//////
	void function_rtrim(SReturnsParams* rpar)
	{
		SVariable* varString			= rpar->ip[0];
		SVariable* varCaseInsensitive	= rpar->ip[1];
		SVariable* varTrimChars1		= rpar->ip[2];
		SVariable* varTrimChars2		= rpar->ip[3];


		// Return rtrim
		ifunction_trim_common(rpar, varString, varCaseInsensitive, varTrimChars1, varTrimChars2, false, true);
	}
