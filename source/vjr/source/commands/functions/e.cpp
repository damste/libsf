//////////
//
// /libsf/source/vjr/commands/funcs/e.cpp
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
// Function: EMPTY()
// Determines whether an expression evaluates to empty.
//
//////
// Version 0.58
// Last update:
//     Mar.20.2015
//////
// Change log:
//     Mar.20.2015 - Refactoring by Stefano D'Amico
//     Mar.19.2015 - Refactoring by Rick C. Hodgin
//     Mar.19.2015 - Initial creation by Stefano D'Amico
//////
// Parameters:
//     p1	-- Specifies the expression that EMPTY( ) evaluates.
//
//////
// Returns:
//    EMPTY( ) returns True (.T.) if the expression eExpression evaluates to empty;
//    otherwise, EMPTY( ) returns False (.F.)
//////
// Example:
//    ? EMPTY("AA")	&& Display .F.
//    ? EMPTY("  ")	&& Display .T.
//    ? EMPTY(0.0)	&& Display .T.
//////
	void function_empty(SReturnsParams* rpar)
	{
		SVariable*	varExpr = rpar->ip[0];
		bool		llEmpty;
		SVariable*	result;


		//////////
		// Verify the expression is correct
		//////
			rpar->rp[0] = NULL;
			if (!iVariable_isValid(varExpr))
			{
				iError_report_byNumber(_ERROR_PARAMETER_IS_INCORRECT, iVariable_get_relatedComp(varExpr), false);
				return;
			}


		//////////
		// Create and populate the return variable
		//////
			llEmpty	= function_isempty_common(rpar, varExpr);
			result	= iVariable_createAndPopulate_byText(_VAR_TYPE_LOGICAL, iVariable_populate_byBool(llEmpty), 1, false);
			if (!result)
				iError_report_byNumber(_ERROR_INTERNAL_ERROR, iVariable_get_relatedComp(varExpr), false);


		//////////
		// Signify our result
		//////
			rpar->rp[0] = result;

	}

	bool function_isempty_common(SReturnsParams* rpar, SVariable* varExpr)
	{
		s8			c, cPointChar;
		u32			lnI;
		bool		llEmpty;
		SVariable*	varPoint;


		//////////
		// Determine what we're evaluating
		//////
			llEmpty = true;
			switch (varExpr->varType)
			{
				case _VAR_TYPE_NULL:
					// NULL values are considered "not empty" even though they really are.
					llEmpty = false;
					break;

				case _VAR_TYPE_DATE:	// Note:  Dates are stored internally as YYYYMMDD, so they can be directly compared
				case _VAR_TYPE_CHARACTER:
					// Character expressions must have no length, or be completely blank to be considered empty

					//////////
					// Iterate through each character
					//////
						for (lnI = 0; lnI < (u32)varExpr->value.length; lnI++)
						{
							// If we encounter anything other than spaces, not empty
							if (varExpr->value.data[lnI] != 32)
							{
								llEmpty = false;
								break;
							}
						}
						break;


				case _VAR_TYPE_NUMERIC:
					// Numerics are stored as numbers, possibly with a minus sign and the point separator

					//////////
					// Grab the point character
					//////
						if ((varPoint = propGet_settings_Point(_settings)))
						{
							// Extract it
							cPointChar	= varPoint->value.data_s8[0];
							iVariable_delete(varPoint, true);

						} else {
							// Default to the standard period
							cPointChar	= cgcPointChar[0];
						}


					//////////
					// Iterate through
					//////
						for (lnI = 0; lnI < (u32)varExpr->value.length; lnI++)
						{
							// If we encounter a non-space, non-zero, or a non-point character, it's then not empty
							c = varExpr->value.data[lnI];
							if (c != 32 && c != '0' && c != cPointChar)
							{
								llEmpty = false;
								break;
							}
						}
						break;


				case _VAR_TYPE_DATETIMEX:
					llEmpty = (varExpr->value.data_dtx->jseconds < 0);
					break;

				case _VAR_TYPE_DATETIME:
					llEmpty = ((varExpr->value.data_dt->julian == _DATETIME_BLANK_DATETIME_JULIAN) && (varExpr->value.data_dt->seconds == _DATETIME_BLANK_DATETIME_SECONDS));
					break;

				case _VAR_TYPE_LOGICAL:
					llEmpty = !(varExpr->value.data_s8[0] == _LOGICAL_TRUE);
					break;

				case _VAR_TYPE_S8:
				case _VAR_TYPE_U8:
					llEmpty = (*varExpr->value.data_u8 == 0);
					break;

				case _VAR_TYPE_S16:
				case _VAR_TYPE_U16:
					llEmpty = (*varExpr->value.data_u16 == 0);
					break;

				case _VAR_TYPE_S32:
				case _VAR_TYPE_U32:
					llEmpty = (*varExpr->value.data_u32 == 0);
					break;

				case _VAR_TYPE_S64:
				case _VAR_TYPE_U64:
				case _VAR_TYPE_CURRENCY:
					llEmpty = (*varExpr->value.data_u64 == 0);
					break;

				case _VAR_TYPE_F32:
					llEmpty = (*varExpr->value.data_f32 == 0.0f);
					break;

				case _VAR_TYPE_F64:
					llEmpty = (*varExpr->value.data_f64 == 0.0);
					break;

//				case _VAR_TYPE_BI:
//					// Big integer
//					break;

//				case _VAR_TYPE_BFP:
//					// Big floating point
//					break;

				default:
					iError_report_byNumber(_ERROR_FEATURE_NOT_AVAILABLE, NULL, false);
					return(NULL);
			}


		//////////
		// Signify our result
		//////
			return(llEmpty);

	}




//////////
//
// Function: ENDSWITH()
// Determines if the character string ends with the search string.
//
//////
// Version 0.58   (Determine the current version from the header in vjr.cpp)
// Last update:
//     Mar.22.2015
//////
// Change log:
//     Mar.22.2015 - Initial creation (originally proposed by Stefano D'Amico)
//////
// Parameters:
//     varString	-- Original string
//     varSearch	-- Search string to replace
//     varStart		-- Starting location within the string
//     varEnd		-- Ending location within the string
//
//////
// Returns:
//    Logical		-- .t. if the search string is found in the string, .f. otherwise
//
//////
	void function_endswith(SReturnsParams* rpar)
	{
		SVariable* varString	= rpar->ip[0];
//		SVariable* varSearch	= rpar->params[1];
//		SVariable* varStart		= rpar->params[2];
//		SVariable* varEnd		= rpar->params[3];


		// Not yet completed
		iError_report_byNumber(_ERROR_FEATURE_NOT_AVAILABLE, iVariable_get_relatedComp(varString), false);
	}




//////////
//
// Function: ENDSWITHC()
// Case-insensitive version of ENDSWITH()
//
//////
	void function_endswithc(SReturnsParams* rpar)
	{
		SVariable* varString	= rpar->ip[0];
//		SVariable* varSearch	= rpar->params[1];
//		SVariable* varStart		= rpar->params[2];
//		SVariable* varEnd		= rpar->params[3];


		// Not yet completed
		iError_report_byNumber(_ERROR_FEATURE_NOT_AVAILABLE, iVariable_get_relatedComp(varString), false);
	}




//////////
//
// Function: EVL()
// Returns a non-empty value from two expressions.
//
//////
// Version 0.58
// Last update:
//     Mar.20.2015
//////
// Change log:
//     Mar.20.2015 - Some refactoring by Rick C. Hodgin
//     Mar.20.2015 - Initial creation by Stefano D'Amico
//////
// Parameters:
//     p1	-- Specifies the expression that EMPTY( ) evaluates.
//     p2	-- Specifies the expression to return if p1 is empty.
//
//////
// Returns:
//    EVL( ) returns p1 if it does not evaluate to an empty value; otherwise, it returns p2.
//////
// Example:
//    ? EVL("  ", "None")	&& Display "None"
//////
	void function_evl(SReturnsParams* rpar)
	{
		SVariable*	varExpr1 = rpar->ip[0];
		SVariable*	varExpr2 = rpar->ip[1];
		bool		llEmpty;
		SVariable*	result;


		//////////
		// Verify p1 is correct
		//////
			rpar->rp[0] = NULL;
			if (!iVariable_isValid(varExpr1))
			{
				iError_report_byNumber(_ERROR_P1_IS_INCORRECT, iVariable_get_relatedComp(varExpr1), false);
				return;
			}


		//////////
		// Verify p2 is correct
		//////
			if (!iVariable_isValid(varExpr2))
			{
				iError_report_byNumber(_ERROR_P2_IS_INCORRECT, iVariable_get_relatedComp(varExpr2), false);
				return;
			}


		//////////
		// Create our result
		//////
			llEmpty	= function_isempty_common(rpar, varExpr1);
			result	= iVariable_copy(((llEmpty) ? varExpr2 : varExpr1), false);
			if (!result)
				iError_report_byNumber(_ERROR_INTERNAL_ERROR, iVariable_get_relatedComp(((llEmpty) ? varExpr2 : varExpr1)), false);


		//////////
		// Signify our result
		//////
			rpar->rp[0] = result;

	}




//////////
//
// Function: EXP()
// Returns the value of e^x where x is a specified numeric expression.
//
//////
// Version 0.58
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
//    EXP(n) of the value in p1
//////
// Example:
//    ? EXP(2)		&& Display 7.39
//////
    void function_exp(SReturnsParams* rpar)
    {
		SVariable* varNumber = rpar->ip[0];


		// Return exp
		ifunction_numbers_common(rpar, varNumber, NULL, NULL, _FP_COMMON_EXP, _VAR_TYPE_F64, false, false);
	}

	// Common numeric functions used for EXP(), LOG(), LOG10(), PI(), SQRT(), CEILING(), FLOOR(), DTOR(), RTOD(), ...
    void ifunction_numbers_common(SReturnsParams* rpar, SVariable* varNumber1, SVariable* varNumber2, SVariable* varNumber3, u32 tnFunctionType, const u32 tnResultType, bool tlSameInputType, bool tlNoEmptyParam)
    {
		f64			lfResult, lfValue1, lfValue2, lfValue3;
		u32			errorNum;
        bool		error;
        SVariable*	result;


		//////////
		// If varNumber1 is provided, must also be numeric
		//////
			rpar->rp[0] = NULL;
			if (varNumber1)
			{
				//////////
				// Must be numeric
				//////
					if (!iVariable_isValid(varNumber1) || !iVariable_isTypeNumeric(varNumber1))
					{
						iError_report_byNumber(_ERROR_PARAMETER_IS_INCORRECT, iVariable_get_relatedComp(varNumber1), false);
						return;
					}


				//////////
				// Convert to f64
				//////
					lfValue1 = iiVariable_getAs_f64(varNumber1, false, &error, &errorNum);
					if (error)
					{
						iError_report_byNumber(errorNum, iVariable_get_relatedComp(varNumber1), false);
						return;
					}

				//////////
				// Check empty param
				//////
					if (tlNoEmptyParam && lfValue1 == 0.0)
					{
						iError_report_byNumber(_ERROR_CANNOT_BE_ZERO, iVariable_get_relatedComp(varNumber1), false);
						return;
					}

			} else {
				lfValue1 = 0.0;
			}


		//////////
		// If varNumber2 is provided, must also be numeric
		//////
			if (varNumber2)
			{
				//////////
				// Must be numeric
				//////
					if (!iVariable_isValid(varNumber2) || !iVariable_isTypeNumeric(varNumber2))
					{
						iError_report_byNumber(_ERROR_PARAMETER_IS_INCORRECT, iVariable_get_relatedComp(varNumber2), false);
						return;
					}


				//////////
				// Convert to f64
				//////
					lfValue2 = iiVariable_getAs_f64(varNumber2, false, &error, &errorNum);
					if (error)
					{
						iError_report_byNumber(errorNum, iVariable_get_relatedComp(varNumber2), false);
						return;
					}

				//////////
				// Check empty param
				//////
					if (tlNoEmptyParam && lfValue2 == 0.0)
					{
						iError_report_byNumber(_ERROR_CANNOT_BE_ZERO, iVariable_get_relatedComp(varNumber2), false);
						return;
					}

			} else {
				lfValue2 = 0.0;
			}


		//////////
		// If varNumber3 is provided, must also be numeric
		//////
			if (varNumber3)
			{
				//////////
				// Must be numeric
				//////
					if (!iVariable_isValid(varNumber3) || !iVariable_isTypeNumeric(varNumber3))
					{
						iError_report_byNumber(_ERROR_PARAMETER_IS_INCORRECT, iVariable_get_relatedComp(varNumber3), false);
						return;
					}


				//////////
				// Convert to f64
				//////
					lfValue3 = iiVariable_getAs_f64(varNumber3, false, &error, &errorNum);
					if (error)
					{
						iError_report_byNumber(errorNum, iVariable_get_relatedComp(varNumber3), false);
						return;
					}

				//////////
				// Check empty param
				//////
					if (tlNoEmptyParam && lfValue3 == 0.0)
					{
						iError_report_byNumber(_ERROR_CANNOT_BE_ZERO, iVariable_get_relatedComp(varNumber3), false);
						return;
					}

			} else {
				lfValue3 = 0.0;
			}


		//////////
		// Compute numeric function
		//////
			switch (tnFunctionType)
			{

// SQRT()
				case _FP_COMMON_SQRT:

					//////////
					// Verify p1 >= 0
					//////
						if (lfValue1 < 0.0)
						{
							// Oops!
							iError_report_byNumber(_ERROR_CANNOT_BE_NEGATIVE, iVariable_get_relatedComp(varNumber1), false);
							return;
						}


					//////////
					// Compute sqrt
					//////
						lfResult = sqrt(lfValue1);
						break;

// EXP()
				case _FP_COMMON_EXP:
					lfResult = exp(lfValue1);
					break;

// PI()
				case _FP_COMMON_PI:
					lfResult = _MATH_PI;
					break;

// LOG()
// LOG10()
				case _FP_COMMON_LOG:
				case _FP_COMMON_LOG10:

					//////////
					// Verify p1 > 0
					//////
						if (lfValue1 <= 0.0)
						{
							// Oops!
							iError_report_byNumber(_ERROR_CANNOT_BE_ZERO_OR_NEGATIVE, iVariable_get_relatedComp(varNumber1), false);
							return;
						}


					//////////
					// Compute
					//////
						if (tnFunctionType == _FP_COMMON_LOG)		lfResult = log(lfValue1);
						else										lfResult = log10(lfValue1);
						break;

// CEILING()
				case _FP_COMMON_CEILING:
					lfResult = ceil(lfValue1);
					break;

// FLOOR()
				case _FP_COMMON_FLOOR:
					lfResult = floor(lfValue1);
					break;

// DTOR()
				case _FP_COMMON_DTOR:
					lfResult = lfValue1 * _MATH_PI180;
					break;

// RTOD()
				case _FP_COMMON_RTOD:
					lfResult = lfValue1 * _MATH_180PI;
					break;

// COS()
				case _FP_COMMON_COS:
					lfResult = cos(lfValue1);
					break;

// SIN()
				case _FP_COMMON_SIN:
					lfResult = sin(lfValue1);
					break;

// ABS()
				case _FP_COMMON_ABS:
					lfResult = abs(lfValue1);
					break;

// ACOS()
// ASIN()
				case _FP_COMMON_ACOS:
				case _FP_COMMON_ASIN:

					//////////
					// Verify p1 > 0
					//////
						if (lfValue1 < -1 || lfValue1 > 1)
						{
							// Oops!
							iError_report_byNumber(_ERROR_OUT_OF_RANGE, iVariable_get_relatedComp(varNumber1), false);
							return;
						}

					//////////
					// Compute
					//////
						if (tnFunctionType == _FP_COMMON_ACOS)		lfResult = acos(lfValue1);
						else										lfResult = asin(lfValue1);
						break;

// ATAN()
				case _FP_COMMON_ATAN:

					//////////
					// Verify p1 > 0
					//////
						if (lfValue1 < -_MATH_PI2 || lfValue1 > _MATH_PI2)
						{
							// Oops!
							iError_report_byNumber(_ERROR_OUT_OF_RANGE, iVariable_get_relatedComp(varNumber1), false);
							return;
						}

					//////////
					// Compute
					//////
						lfResult = atan(lfValue1);
						break;

// ATN2()
				case _FP_COMMON_ATN2:
					lfResult = atan2(lfValue1, lfValue2);
					break;
// TAN()
				case _FP_COMMON_TAN:
					lfResult = tan(lfValue1);
					break;
// MOD()
				case _FP_COMMON_MOD:

					//////////
					// Verify divisor not 0
					//////
						if (lfValue2 == 0.0)
						{
							// Oops!
							iError_report_byNumber(_ERROR_DIVISION_BY_ZERO, iVariable_get_relatedComp(varNumber2), false);
							return;
						}


					//////////
					// Compute
					//////
						lfResult = fmod(lfValue1, abs(lfValue2));
						if (lfValue2 < 0 && lfResult != 0.0)			// Mar.14.2015
							lfResult += lfValue2;

					break;

// FV()
				case _FP_COMMON_FV:

					//////////
					// Future value
					//////
						lfResult = (pow((1 + lfValue2), lfValue3) - 1) / lfValue2 * lfValue1;
						break;

// PV()
				case _FP_COMMON_PV:

					//////////
					// Present value
					//////
						lfResult = lfValue1 * ((1 - pow((1 + lfValue2), -lfValue3)) / lfValue2);
						break;

// PAYMENT()
				case _FP_COMMON_PAYMENT:

					//////////
					// Payment
					//////
						lfValue1 = (lfValue1 * pow(lfValue2 + 1, lfValue3) * lfValue2) / (pow(lfValue2 + 1, lfValue3) - 1);
						break;

				default:
					// Programmer error... this is an internal function and we should never get here
					iError_report_byNumber(_ERROR_INTERNAL_ERROR, iVariable_get_relatedComp(varNumber1), false);
					return;
			}


		//////////
		// Create output variable
		//////
			if (tlSameInputType)	result = iVariable_create(varNumber1->varType, NULL, true);
			else					result = iVariable_create(tnResultType, NULL, true);

			if (!result)
			{
				iError_report_byNumber(errorNum, iVariable_get_relatedComp(varNumber1), false);
				return;
			}


		//////////
		// Set the value
		//////
			if (!iVariable_setNumeric_toNumericType(result, NULL, &lfResult, NULL, NULL, NULL, NULL))
				iError_report_byNumber(errorNum, iVariable_get_relatedComp(varNumber1), false);


		//////////
        // return(result)
		//////
			rpar->rp[0] = result;
	}
