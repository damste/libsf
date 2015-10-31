//////////
//
// /libsf/source/vjr/commands/funcs/m.cpp
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
// Function: MALP()
// Returns the 1.0 - ((255 - ALP()) / 255) calculation.
//
//////
// Version 0.57   (Determine the current version from the header in vjr.cpp)
// Last update:
//     Mar.16.2015
//////
// Change log:
//     Mar.16.2015 - Initial creation
//////
// Parameters:
//     varColor		-- Color to extract alpha channel from
//
//////
// Returns:
//    Integer in the range 0..255, or floating point in the range 0.0 to 1.0
//
//////
// Usage:
//   ? malp(lnColor)          && Returns floating point
//   ? malp(lnColor, .t.)     && Returns integer
//   ? malp(lnColor, .f.)     && Returns floating point
//////
	void function_malp(SReturnsParams* rpar)
	{
		SVariable*	varColor		= rpar->ip[0];
		SVariable*	varAsInteger	= rpar->ip[1];
		u32			lnColor;
		f32			lfMalp;
		bool		llAsInteger;
		bool		error;
		u32			errorNum;
		SVariable*	result;


		//////////
		// Color must be numeric
		//////
			rpar->rp[0] = NULL;
			if (!iVariable_isValid(varColor) || !iVariable_isTypeNumeric(varColor))
			{
				iError_report_byNumber(_ERROR_P1_IS_INCORRECT, iVariable_get_relatedComp(varColor), false);
				return;
			}


		//////////
		// If varAsInteger exists, it must be logical
		//////
			if (varAsInteger)
			{
				if (!iVariable_isFundamentalTypeLogical(varAsInteger))
				{
					iError_report_byNumber(_ERROR_P1_IS_INCORRECT, iVariable_get_relatedComp(varColor), false);
					return;
				}

				// Grab the value
				llAsInteger = iiVariable_getAs_bool(varAsInteger, false, &error, &errorNum);
				if (error)
				{
					iError_report_byNumber(errorNum, iVariable_get_relatedComp(varColor), false);
					return;
				}

			} else {
				// Set it to false
				llAsInteger = false;
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
			lnColor &= 0xff0000000;
			lnColor >>= 24;
			if (llAsInteger)
			{
				// Unsigned 32-bit integer
				lnColor	= 255 - lnColor;
				result	= iVariable_create(_VAR_TYPE_U32, NULL, true);

			} else {
				// Floating point
				lfMalp	= 1.0f - ((255.0f - (f32)lnColor) / 255.0f);
				result	= iVariable_create(_VAR_TYPE_F32, NULL, true);
			}


		//////////
		// Construct our result
		//////
			if (!result)
			{
				iError_report_byNumber(_ERROR_INTERNAL_ERROR, NULL, false);

			} else {
				//////////
				// Populate our result
				//////
					if (llAsInteger)		*result->value.data_u32 = lnColor;
					else					*result->value.data_f32 = lfMalp;
			}


		//////////
		// Signify our result
		//////
			rpar->rp[0] = result;

	}




//////////
//
// Function: MAX()
// Returns the maximum value of the two inputs.
//
//////
// Version 0.57   (Determine the current version from the header in vjr.cpp)
// Last update:
//     Jul.12.2014
//////
// Change log:
//     Jul.12.2014 - Initial creation
//////
// Parameters:
//     pLeft		-- Left-side value, first parameter
//     pRight		-- Right-side value, second parameter
//
//////
// Returns:
//    Either pLeft or pRight copied, depending on which is greater.
//    If they're equal, a copy of pLeft is returned.
//
//////
	void function_max(SReturnsParams* rpar)
	{
		SVariable*	varLeft		= rpar->ip[0];
		SVariable*	varRight	= rpar->ip[1];
		bool		llLeft;
		s32			lnLeft32, lnRight32;
		s64			lnLeft64, lnRight64;
		f64			lfLeft64, lfRight64;
		bool		error;
		u32			errorNum;
		SDateTime*	dtLeft;
		SDateTime*	dtRight;
		SVariable*	result;


		//////////
		// Parameter 1 must be numeric
		//////
			rpar->rp[0] = NULL;
			if (!iVariable_isValid(varLeft))
			{
				iError_report_byNumber(_ERROR_P1_IS_INCORRECT, iVariable_get_relatedComp(varLeft), false);
				return;
			}


		//////////
		// Parameter 2 must be numeric
		//////
			if (!iVariable_isValid(varRight))
			{
				iError_report_byNumber(_ERROR_P2_IS_INCORRECT, iVariable_get_relatedComp(varRight), false);
				return;
			}


		//////////
		// They must be the same type
		//////
			if (iVariable_get_fundamentalType(varLeft) != iVariable_get_fundamentalType(varRight))
			{
				// Operand mismatch
				iError_report_byNumber(_ERROR_DATA_TYPE_MISMATCH, iVariable_get_relatedComp(varRight), false);
				return;
			}


		//////////
		// Determine what we're comparing
		//////
			llLeft = false;
			switch (varLeft->varType)
			{
				case _VAR_TYPE_DATE:			// Note:  Dates are stored internally as YYYYMMDD, so they can be directly compared
				case _VAR_TYPE_CHARACTER:
					if (varLeft->value.length == 0 || varRight->value.length == 0)
					{
						// At least one of them is null, return the left
						llLeft = true;

					} else {
						// They both have a non-zero length
						switch (_memicmp(varLeft->value.data, varRight->value.data, min(varLeft->value.length, varRight->value.length)))
						{
							case -1:
							case 0:
								// Left is less than or equal to right
								llLeft = true;
								break;

							default:
								// Right is less
								break;
						}
					}
					break;

				// Note: _VAR_TYPE_DATETIMEX is handled below as a 64-bit number
				case _VAR_TYPE_DATETIME:
					dtLeft	= varLeft->value.data_dt;
					dtRight	= varRight->value.data_dt;
					if (dtLeft->julian < dtRight->julian)
					{
						// Left is less
						llLeft = true;

					} else if (dtLeft->julian > dtRight->julian) {
						// Right is less

					} else {
						// They are equal, compare the time
						if (dtLeft->seconds <= dtRight->seconds)
						{
							// Left is less or equal
							llLeft = true;

						} else {
							// Right is less
						}
					}
					break;

				default:
					if (iVariable_isTypeBig(varLeft) || iVariable_isTypeBig(varRight))
					{
						// It's a character compared to a character
						iError_report_byNumber(_ERROR_FEATURE_NOT_AVAILABLE, NULL, false);
						return;

					} else if (iVariable_isTypeFloatingPoint(varLeft) || iVariable_isTypeFloatingPoint(varRight)) {
						// Comparing floating point values
						lfLeft64	= iiVariable_getAs_f64(varLeft, false, &error, &errorNum);
						if (error)
						{
							iError_report_byNumber(errorNum, iVariable_get_relatedComp(varLeft), false);
							return;
						}

						lfRight64	= iiVariable_getAs_f64(varRight, false, &error, &errorNum);
						if (error)
						{
							iError_report_byNumber(errorNum, iVariable_get_relatedComp(varRight), false);
							return;
						}

						// Perform the test
						if (lfLeft64 <= lfRight64)
						{
							// Left is less
							llLeft = true;

						} else {
							// Right is less
						}

					} else if (iVariable_isTypeNumeric(varLeft) || iVariable_isTypeNumeric(varRight) || iVariable_isTypeDatetimeX(varLeft) || iVariable_isTypeDatetimeX(varRight)) {
						// Comparing numerics
						if (iVariable_isNumeric64Bit(varLeft) || iVariable_isNumeric64Bit(varRight))
						{
							// It requires a 64-bit signed compare
							lnLeft64	= iiVariable_getAs_s64(varLeft, false, &error, &errorNum);
							if (error)
							{
								iError_report_byNumber(errorNum, iVariable_get_relatedComp(varLeft), false);
								return;
							}

							lnRight64	= iiVariable_getAs_s64(varRight, false, &error, &errorNum);
							if (error)
							{
								iError_report_byNumber(errorNum, iVariable_get_relatedComp(varRight), false);
								return;
							}

							// Perform the test
							if (lnLeft64 <= lnRight64)
							{
								// Left is less
								llLeft = true;

							} else {
								// Right is less
							}

						} else {
							// It can be done in a 32-bit signed compare
							lnLeft32	= iiVariable_getAs_s32(varLeft, false, &error, &errorNum);
							if (error)
							{
								iError_report_byNumber(errorNum, iVariable_get_relatedComp(varLeft), false);
								return;
							}

							lnRight32	= iiVariable_getAs_s32(varRight, false, &error, &errorNum);
							if (error)
							{
								iError_report_byNumber(errorNum, iVariable_get_relatedComp(varRight), false);
								return;
							}

							// Perform the test
							if (lnLeft32 <= lnRight32)
							{
								// Left is less
								llLeft = true;

							} else {
								// Right is less
							}
						}

					} else {
						// We cannot compare these types
						iError_report_byNumber(_ERROR_FEATURE_NOT_AVAILABLE, iVariable_get_relatedComp(varLeft), false);
						return;
					}
			}
			// When we get here, llLeft is populated with our intent
			if (llLeft)
			{
				// Left is less, so duplicate right
				result = iVariable_copy(varRight, false);

			} else {
				// Right is less, so duplicate left
				result = iVariable_copy(varLeft, false);
			}


		//////////
		// Are we good?
		//////
			if (!result)
				iError_report_byNumber(_ERROR_INTERNAL_ERROR, iVariable_get_relatedComp(varLeft), false);


		//////////
		// Indicate our result
		//////
			rpar->rp[0] = result;

	}




//////////
//
// Function: MDY()
// Returns the specified date or datetime expression in month-day-year format with the name of the month spelled out.
//
//////
// Version 0.57
// Last update:
//     Apr.07.2015
//////
// Change log:
//     Apr.07.2015 - Initial creation by Stefano D'Amico
//////
// Parameters:
//     p1			-- Date or DateTime
//
//////
// Returns:
//    Character - If SET CENTURY is OFF, the character expression is returned in a month dd, yy format. 
//	  If SET CENTURY is ON, the format is month dd, yyyy.
//////
	void function_mdy(SReturnsParams* rpar)
	{
		SVariable* varParam = rpar->ip[0];


		// Return mdy
		ifunction_dtoc_common(rpar, varParam, _DMY_COMMON_MDY);
	}




//////////
//
// Function: MICROSECOND()
// The current microsecond (1/1000000 one millionth of a second) as a floating point in the range 0..999999.
//
//////
// Version 0.57
// Last update:
//     Apr.26.2015
//////
// Change log:
//     Apr.26.2015 - Initial creation by Rick C. Hodgin
//////
// Parameters:
//     none
//
//////
// Returns:
//    f64		-- A floating point value containing the number of one millionths of a second which have gone by this second
//////
	void function_microsecond(SReturnsParams* rpar)
	{
		ifunction_xseconds_common(rpar, _XSECONDS_FUNCTION_MICROSECOND);
	}




//////////
//
// Function: MIN()
// Returns the minimum value of the two inputs.
//
//////
// Version 0.57   (Determine the current version from the header in vjr.cpp)
// Last update:
//     Jul.12.2014
//////
// Change log:
//     Jul.12.2014 - Initial creation
//////
// Parameters:
//     pLeft		-- Left-side value, first parameter
//     pRight		-- Right-side value, second parameter
//
//////
// Returns:
//    Either pLeft or pRight copied, depending on which is less.
//    If they're equal, a copy of pLeft is returned.
//
//////
	void function_min(SReturnsParams* rpar)
	{
		SVariable*	varLeft		= rpar->ip[0];
		SVariable*	varRight	= rpar->ip[1];
		bool		llLeft;
		s32			lnLeft32, lnRight32;
		s64			lnLeft64, lnRight64;
		f64			lfLeft64, lfRight64;
		bool		error;
		u32			errorNum;
		SDateTime*	dtLeft;
		SDateTime*	dtRight;
		SVariable*	result;


		//////////
		// Parameter 1 must be numeric
		//////
			rpar->rp[0] = NULL;
			if (!iVariable_isValid(varLeft))
			{
				iError_report_byNumber(_ERROR_P1_IS_INCORRECT, iVariable_get_relatedComp(varLeft), false);
				return;
			}


		//////////
		// Parameter 2 must be numeric
		//////
			if (!iVariable_isValid(varRight))
			{
				iError_report_byNumber(_ERROR_P2_IS_INCORRECT, iVariable_get_relatedComp(varRight), false);
				return;
			}


		//////////
		// They must be the same type
		//////
			if (iVariable_get_fundamentalType(varLeft) != iVariable_get_fundamentalType(varRight))
			{
				// Operand mismatch
				iError_report_byNumber(_ERROR_DATA_TYPE_MISMATCH, iVariable_get_relatedComp(varRight), false);
				return;
			}


		//////////
		// Determine what we're comparing
		//////
			llLeft = false;
			switch (varLeft->varType)
			{
				case _VAR_TYPE_DATE:			// Note:  Dates are stored internally as YYYYMMDD, so they can be directly compared
				case _VAR_TYPE_CHARACTER:
					if (varLeft->value.length == 0 || varRight->value.length == 0)
					{
						// At least one of them is null, return the left
						llLeft = true;

					} else {
						// They both have a non-zero length
						switch (_memicmp(varLeft->value.data, varRight->value.data, min(varLeft->value.length, varRight->value.length)))
						{
							case -1:
							case 0:
								// Left is less than or equal to right
								llLeft = true;
								break;

							default:
								// Right is less
								break;
						}
					}
					break;

				// Note: _VAR_TYPE_DATETIMEX is handled below as a 64-bit number
				case _VAR_TYPE_DATETIME:
					dtLeft	= (SDateTime*)varLeft->value.data;
					dtRight	= (SDateTime*)varRight->value.data;
					if (dtLeft->julian < dtRight->julian)
					{
						// Left is less
						llLeft = true;

					} else if (dtLeft->julian > dtRight->julian) {
						// Right is less

					} else {
						// They are equal, compare the time
						if (dtLeft->seconds <= dtRight->seconds)
						{
							// Left is less or equal
							llLeft = true;

						} else {
							// Right is less
						}
					}
					break;

				default:
					if (iVariable_isTypeBig(varLeft) || iVariable_isTypeBig(varRight))
					{
						// It's a character compared to a character
						iError_report_byNumber(_ERROR_FEATURE_NOT_AVAILABLE, NULL, false);
						return;

					} else if (iVariable_isTypeFloatingPoint(varLeft) || iVariable_isTypeFloatingPoint(varRight)) {
						// Comparing floating point values
						lfLeft64	= iiVariable_getAs_f64(varLeft, false, &error, &errorNum);
						if (error)
						{
							iError_report_byNumber(errorNum, iVariable_get_relatedComp(varLeft), false);
							return;
						}

						lfRight64	= iiVariable_getAs_f64(varRight, false, &error, &errorNum);
						if (error)
						{
							iError_report_byNumber(errorNum, iVariable_get_relatedComp(varRight), false);
							return;
						}

						// Perform the test
						if (lfLeft64 <= lfRight64)
						{
							// Left is less
							llLeft = true;

						} else {
							// Right is less
						}

					} else if (iVariable_isTypeNumeric(varLeft)) {
						// Comparing numerics
						if (iVariable_isNumeric64Bit(varLeft) || iVariable_isNumeric64Bit(varRight) || iVariable_isTypeDatetimeX(varLeft) || iVariable_isTypeDatetimeX(varRight))
						{
							// It requires a 64-bit signed compare
							lnLeft64	= iiVariable_getAs_s64(varLeft, false, &error, &errorNum);
							if (error)
							{
								iError_report_byNumber(errorNum, iVariable_get_relatedComp(varLeft), false);
								return;
							}

							lnRight64	= iiVariable_getAs_s64(varRight, false, &error, &errorNum);
							if (error)
							{
								iError_report_byNumber(errorNum, iVariable_get_relatedComp(varRight), false);
								return;
							}

							// Perform the test
							if (lnLeft64 <= lnRight64)
							{
								// Left is less
								llLeft = true;

							} else {
								// Right is less
							}

						} else {
							// It can be done in a 32-bit signed compare
							lnLeft32	= iiVariable_getAs_s32(varLeft, false, &error, &errorNum);
							if (error)
							{
								iError_report_byNumber(errorNum, iVariable_get_relatedComp(varLeft), false);
								return;
							}

							lnRight32	= iiVariable_getAs_s32(varRight, false, &error, &errorNum);
							if (error)
							{
								iError_report_byNumber(errorNum, iVariable_get_relatedComp(varRight), false);
								return;
							}

							// Perform the test
							if (lnLeft32 <= lnRight32)
							{
								// Left is less
								llLeft = true;

							} else {
								// Right is less
							}
						}

					} else {
						// We cannot compare these types
						iError_report_byNumber(_ERROR_FEATURE_NOT_AVAILABLE, iVariable_get_relatedComp(varLeft), false);
						return;
					}
			}
			// When we get here, llLeft is populated with our intent
			if (llLeft)
			{
				// Left is less, so copy left
				result = iVariable_copy(varLeft, false);

			} else {
				// Right is less, so copy right
				result = iVariable_copy(varRight, false);
			}

			// Are we good?
			if (!result)
				iError_report_byNumber(_ERROR_INTERNAL_ERROR, iVariable_get_relatedComp(varLeft), false);

			// Indicate our result
			rpar->rp[0] = result;

	}




//////////
//
// Function: MINUTE()
// Returns the minute portion from a DateTime expression.
//
//////
// Version 0.57
// Last update:
//     Apr.07.2015
//////
// Change log:
//     Apr.07.2015 - Initial creation by Stefano D'Amico
//////
// Parameters:
//     varParam		-- Specifies a DateTime expression from which MINUTE( ) returns the minute
//
//////
// Returns:
//    MINUTE( ) returns a numeric value.
//////
	void function_minute(SReturnsParams* rpar)
	{
		SVariable*	varParam = rpar->ip[0];


		// Return minute
		ifunction_hhmmss_common(rpar, varParam, _HMS_COMMON_MINUTE);
	}




//////////
//
// Function: MOD()
// Divides one numeric expression by another numeric expression and returns the remainder.
//
//////
// Version 0.57   (Determine the current version from the header in vjr.cpp)
// Last update:
//     Mar.19.2015
//////
// Change log:
//     Mar.19.2015 - Refactoring by Stefano D'Amico
//     Mar.14.2015 - Fix bug when lfMod = 0 by Stefano D'Amico			// https://github.com/RickCHodgin/libsf/issues/2
//     Mar.08.2015 - Merge into main by Rick C. Hodgin, reformatting
//     Feb.28.2015 - Initial creation by Stefano D'Amico
//////
// Parameters:
//    nDividend		-- Specifies the dividend
//    nDivisor		-- Specifies the divisor
//
//////
// Returns:
//    Numeric		-- Returns the remainder
//////
// Example:
//    ? MOD(5, 2)      && 1
//    ? MOD(5, -2)     && -1
//    ? MOD(5.3, 2)    && 1.3
//    ? MOD(5.3, -2)   && -0.7
//////
	void function_mod(SReturnsParams* rpar)
	{
		SVariable*	varDividend	= rpar->ip[0];
		SVariable*	varDivisor	= rpar->ip[1];


		// Return mod
		ifunction_numbers_common(rpar, varDividend, varDivisor, NULL, _FP_COMMON_MOD, _VAR_TYPE_F64, true, false);
	}




//////////
//
// Function: MONTH()
// Returns the number of the month for a given Date or DateTime expression.
//
//////
// Version 0.57
// Last update:
//     Apr.04.2015
//////
// Change log:
//     Apr.04.2015 - Initial creation by Stefano D'Amico
//////
// Parameters:
//     p1			-- Date or DateTime
//
//////
// Returns:
//    MONTH( ) returns a number from 1 through 12. January is month 1, and December is month 12.
//////
// Example:
//	  dt = datetime()	&& Apr.06.2015
//    ? MONTH(dt)		&& Displays 4
//    ? MONTH()			&& Displays current date's month number
//////
	void function_month(SReturnsParams* rpar)
	{
		SVariable* varParam = rpar->ip[0];


		// Return month
		ifunction_day_month_year_common(rpar, varParam, _DMY_COMMON_MONTH);
	}
