//////////
//
// /libsf/source/vjr/commands/funcs/t.cpp
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
// Version 0.56
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
// Function: TAN()
// This trigonometric function returns the tangent of an angle.
//
//////
// Version 0.56
// Last update:
//     Mar.19.2015
//////
// Change log:
//     Mar.19.2015 - Initial creation by Stefano D'Amico
//////
// Parameters:
//     p1			-- Numeric or floating point
//
//////
// Returns:
//    TAN(n) of the value in p1
//////
// Example:
//    ? TAN(0)		&& Display 0.00
//////
    SVariable* function_tan(SThisCode* thisCode, SReturnsParams* returnsParams)
    {
		SVariable* varNumber = returnsParams->params[0];


		// Return sin
		return(ifunction_numbers_common(thisCode, varNumber, NULL, NULL, _FP_COMMON_TAN, _VAR_TYPE_F64, false, false, returnsParams));
	}



//////////
// Rick's test code functionality using the _test() function
//////
	SVariable* function__test(SThisCode* thisCode, SReturnsParams* returnsParams)
	{
		SVariable*	varIndex = returnsParams->params[0];
		s32			lnIndex;
		bool		llValid;
		SVariable*	result;


		//////////
		// Parameter 1 must be valid
		//////
			if (!iVariable_isValid(varIndex) || !iVariable_isTypeNumeric(varIndex))
			{
				iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_getRelatedComp(thisCode, varIndex), false);
				return(NULL);
			}


		//////////
		// Execute the function
		//////
			llValid	= false;
			lnIndex	= iiVariable_getAs_s32(thisCode, varIndex, false, NULL, NULL);
			switch (lnIndex)
			{
				case 1:
					iTest1(thisCode, returnsParams);
					break;

				default:
					iError_reportByNumber(thisCode, _ERROR_FEATURE_NOT_AVAILABLE, iVariable_getRelatedComp(thisCode, varIndex), false);
					break;
			}


		//////////
		// Create our return variable
		/////
			result = iVariable_createAndPopulate_byText(thisCode, _VAR_TYPE_LOGICAL, (cs8*)((llValid) ? &_LOGICAL_TRUE : &_LOGICAL_FALSE), 1, true);
			return(result);
	}




//////////
//
// Function: TEXTMERGE()
// Receives an input string, and processes into it encoded variables.
//
//////
// Version 0.57
// Last update:
//     Apr.20.2015
//////
// Change log:
//     Apr.20.2015 - Initial creation
//////
// Parameters:
//     pFormat		-- Character, the format codes
//     pRecursive	-- (Optional) Logical, should it process recursively?
//     pLeftDelim	-- (Optional) Character, the left-side delimiter overriding the default <<
//     pRightDelim	-- (Optional) Character, the right-side delimiter overriding the default >>
//
//////
// Returns:
//    Character		-- The string after text merging
//////
	SVariable* function_textmerge(SThisCode* thisCode, SReturnsParams* returnsParams)
	{
		SVariable* varFormatStr		= returnsParams->params[0];
		SVariable* varRecursive		= returnsParams->params[1];
		SVariable* varLeftDelim		= returnsParams->params[2];
		SVariable* varRightDelim	= returnsParams->params[3];

		s32			lnResultLength;
		bool		llRecursive;
		SDatum		leftDelim;
		SDatum		rightDelim;
		s8*			lcResult;
		SVariable*	result;
		bool		error;
		u32			errorNum;


		//////////
		// Parameters 1 must be present and character
		//////
			if (!iVariable_isValid(varFormatStr) || !iVariable_isTypeCharacter(varFormatStr))
			{
				iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_getRelatedComp(thisCode, varFormatStr), false);
				return(NULL);
			}


		//////////
		// If present, parameter 2 must be logical
		//////
			if (varRecursive)
			{
				// Logical
				if (!iVariable_isValid(varRecursive) || !iVariable_isFundamentalTypeLogical(varRecursive))
				{
					iError_reportByNumber(thisCode, _ERROR_P2_IS_INCORRECT, iVariable_getRelatedComp(thisCode, varRecursive), false);
					return(NULL);
				}

				// Grab its value
				llRecursive = iiVariable_getAs_bool(thisCode, varRecursive, false, &error, &errorNum);
				if (error)
				{
					iError_reportByNumber(thisCode, errorNum, iVariable_getRelatedComp(thisCode, varRecursive), false);
					return(NULL);
				}

			} else {
				// Not recursive
				llRecursive = false;
			}


		//////////
		// If present, parameters 3 and 4 must be character
		//////
			if (varLeftDelim)
			{
				// Character
				if (!iVariable_isValid(varLeftDelim) || !iVariable_isTypeCharacter(varLeftDelim))
				{
					iError_reportByNumber(thisCode, _ERROR_P3_IS_INCORRECT, iVariable_getRelatedComp(thisCode, varLeftDelim), false);
					return(NULL);
				}

				// Store the delimiter
				leftDelim.data_cs8	= varLeftDelim->value.data_cs8;
				leftDelim.length	= varLeftDelim->value.length;

			} else {
				// Use the default format
				leftDelim.data_cs8	= &cgc_textmerge_leftDelim[0];
				leftDelim.length	= sizeof(cgc_textmerge_leftDelim) - 1;
			}

			if (varRightDelim)
			{
				// Character
				if (!iVariable_isValid(varRightDelim) || !iVariable_isTypeCharacter(varRightDelim))
				{
					iError_reportByNumber(thisCode, _ERROR_P3_IS_INCORRECT, iVariable_getRelatedComp(thisCode, varRightDelim), false);
					return(NULL);
				}

				// Store the delimiter
				rightDelim.data_cs8	= varRightDelim->value.data_cs8;
				rightDelim.length	= varRightDelim->value.length;

			} else {
				// Use the default format
				rightDelim.data_cs8	= &cgc_textmerge_rightDelim[0];
				rightDelim.length	= sizeof(cgc_textmerge_rightDelim) - 1;
			}


		//////////
		// Call the common function
		//////
			lcResult		= NULL;
			lnResultLength	= ifunction_dtransform_textmerge_common(thisCode, &lcResult, varFormatStr->value.data_cs8, varFormatStr->value.length, &leftDelim, &rightDelim, &returnsParams->params[1], false, true);


		//////////
		// Create our result
		//////
			if (lnResultLength != 0 && lcResult)		result = iVariable_createAndPopulate_byText(thisCode, _VAR_TYPE_CHARACTER, (cs8*)lcResult, lnResultLength, true);
			else										result = NULL;


		//////////
		// Are we good?
		//////
			if (!result)
				iError_reportByNumber(thisCode, _ERROR_INTERNAL_ERROR, iVariable_getRelatedComp(thisCode, varFormatStr), false);


		//////////
		// Indicate our result
		//////
			return(result);		

	}




//////////
//
// Function: TIME()
// Returns the time in Hh:Mm:Ss or Hh:Mm:Ss:Mss format
//
//////
// Version 0.57
// Last update:
//     Apr.20.2015
//////
// Change log:
//     Apr.20.2015 - Initial creation by Hernan Cano
//////
// Parameters:
//     pDatetime	-- (optional) Datetime, any value, if they want the time from that datetime
//     pSeconds		-- (optional) Floating point, any value 0..86400, if they want the time from a SECONDS() value
//     pMillisecond	-- (optional) Logical, if we want to include milliseconds
//
//////
// Returns:
//    Character		-- Current time() as HH:MM:SS.mmm if we want milliseconds
//                                    as HH:MM:SS     if we don't want milliseconds
//
//////
	SVariable* function_time(SThisCode* thisCode, SReturnsParams* returnsParams)
	{
		return(ifunction_timex_common(thisCode, returnsParams, false));
	}

	SVariable* ifunction_timex_common(SThisCode* thisCode, SReturnsParams* returnsParams, bool tlIsTimeX)
	{
		SVariable*	varP1	= returnsParams->params[0];
		SVariable*	varP2	= returnsParams->params[1];

		s32			lnMillisecond, lnMicrosecond, lnNanosecond;
		u32			lnYear, lnMonth, lnDay, lnHour, lnMinute, lnSecond;
		f32			lfSeconds;
		f64			lfSecondsx;
		bool		llExtendedTime, llExtractDatetime, llExtractDatetimeX, llExtractSeconds;
		SVariable*	varDatetime;
		SVariable*	varDatetimeX;
		SVariable*	varSeconds;
		SVariable*	result;
		SYSTEMTIME	lst;
		s8			buffer[32];
		bool		error;
		u32			errorNum;


		// How many parameters did they give us?
		llExtendedTime		= false;
		llExtractSeconds	= false;
		llExtractDatetime	= false;
		llExtractDatetimeX	= false;
		lnMillisecond		= 0;
		lnNanosecond		= 0;
		switch (returnsParams->pcount)
		{
			case 0:
				// Grab the current time
				iTime_getLocalOrSystem(&lst, propGet_settings_TimeLocal(_settings));

				// And microsecond if need be
				if (tlIsTimeX)
					lnMicrosecond = iiDateMath_get_currentMicrosecond();
				break;

			case 1:
				// It's either logical, or a datetime/floating point
				if (!iVariable_isValid(varP1))
				{
					iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_getRelatedComp(thisCode, varP1), false);
					return(NULL);
				}

				if (iVariable_isTypeFloatingPoint(varP1))
				{
					// It's numeric, meaning they want us to convert the SECONDS() or SECONDSX() value
					varSeconds			= varP1;
					llExtractSeconds	= true;

				} else if (iVariable_isTypeDatetime(varP1)) {
					// It's datetime, meaning they want the seconds from this value
					varDatetime			= varP1;
					llExtractDatetime	= true;

				} else if (iVariable_isTypeDatetimeX(varP1)) {
					// It's datetimex, meaning they want the seconds or secondsx from this value
					varDatetimeX		= varP1;
					llExtractDatetimeX	= true;

				} else if (!tlIsTimeX && iVariable_isFundamentalTypeLogical(varP1)) {
					// It's logical, which means they're indicating if they want the milliseconds
					llExtendedTime = iiVariable_getAs_bool(thisCode, varP1, false, &error, &errorNum);
					if (error)
					{
						iError_reportByNumber(thisCode, errorNum, iVariable_getRelatedComp(thisCode, varP1), false);
						return(NULL);
					}

					// Grab the time
					iTime_getLocalOrSystem(&lst, propGet_settings_TimeLocal(_settings));

				} else {
					// Invalid
					iError_reportByNumber(thisCode, _ERROR_INVALID_ARGUMENT_TYPE_COUNT, iVariable_getRelatedComp(thisCode, varP1), false);
					return(NULL);
				}
				break;


			case 2:
				//////////
				// P1 must be datetime/datetimex/floating point
				//////
					if (iVariable_isTypeNumeric(varP1))
					{
						// It's numeric, meaning they want us to convert the SECONDS() value
						varSeconds			= varP1;
						llExtractSeconds	= true;

					} else if (iVariable_isTypeDatetime(varP1)) {
						// It's datetime, meaning they want the seconds from this value
						varDatetime			= varP1;
						llExtractDatetime	= true;

					} else if (iVariable_isTypeDatetimeX(varP1)) {
						// It's datetime, meaning they want the seconds from this value
						varDatetimeX		= varP1;
						llExtractDatetimeX	= true;

					} else {
						// Invalid
						iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_getRelatedComp(thisCode, varP1), false);
						return(NULL);
					}


				//////////
				// P2 must be logical
				//////
					if (!iVariable_isFundamentalTypeLogical(varP2))
					{
						iError_reportByNumber(thisCode, _ERROR_P2_IS_INCORRECT, iVariable_getRelatedComp(thisCode, varP2), false);
						return(NULL);
					}

					// Grab the milliseconds flag
					llExtendedTime = iiVariable_getAs_bool(thisCode, varP2, false, &error, &errorNum);
					if (error)
					{
						iError_reportByNumber(thisCode, errorNum, iVariable_getRelatedComp(thisCode, varP2), false);
						return(NULL);
					}
					break;

		}


		//////////
		// Extract the seconds if need be
		//////
			if (llExtractSeconds)
			{
				if (tlIsTimeX)
				{
					// Grab the secondsx
					lfSecondsx = iiVariable_getAs_f64(thisCode, varSeconds, false, &error, &errorNum);
					if (error)
					{
						iError_reportByNumber(thisCode, errorNum, iVariable_getRelatedComp(thisCode, varSeconds), false);
						return(NULL);
					}

					// Convert the secondsx value to a time
					iiDateMath_get_SYSTEMTIME_from_SECONDSX(&lst, lfSecondsx, &lnMicrosecond, &lnNanosecond);

				} else {
					// Grab the seconds
					lfSeconds = iiVariable_getAs_f32(thisCode, varSeconds, false, &error, &errorNum);
					if (error)
					{
						iError_reportByNumber(thisCode, errorNum, iVariable_getRelatedComp(thisCode, varSeconds), false);
						return(NULL);
					}

					// Convert the seconds value to a time
					iiDateMath_get_SYSTEMTIME_from_SECONDS(&lst, lfSeconds);
				}
			}


		//////////
		// Extract the datetime if need be
		//////
			if (llExtractDatetime)
			{
				iiDateMath_get_SYSTEMTIME_from_SECONDS(&lst, varP1->value.data_dt->seconds);

				if (tlIsTimeX)
					lnMicrosecond = (s32)lst.wMilliseconds * 1000;
			}


		//////////
		// Extract the datetimex if need be
		//////
			if (llExtractDatetimeX)
			{
				iiDateMath_get_YyyyMmDdHhMmSsMssNss_from_jseconds(varP1->value.data_dtx->jseconds, NULL, &lnYear, &lnMonth, &lnDay, &lnHour, &lnMinute, &lnSecond, &lnMillisecond, &lnMicrosecond);
				lst.wHour	= lnHour;
				lst.wMinute	= lnMinute;
				lst.wSecond	= lnSecond;
			}

			
		//////////
		// Convert lst.* into a VJr date variable
		//////
			// Time is stored as HH:MM:SS.mmm
			if (tlIsTimeX)
			{
				// TIMEX(, .t.) or TIMEX()
				if (llExtendedTime)		sprintf(buffer, "%02u:%02u:%02u.%09u\0", lst.wHour, lst.wMinute, lst.wSecond, lnNanosecond);
				else					sprintf(buffer, "%02u:%02u:%02u.%06u\0", lst.wHour, lst.wMinute, lst.wSecond, lnMicrosecond);

			} else if (llExtendedTime) {
				// TIME(, .t.)
				sprintf(buffer, "%02u:%02u:%02u.%03u\0", lst.wHour, lst.wMinute, lst.wSecond, lst.wMilliseconds);

			} else {
				// TIME()
				sprintf(buffer, "%02u:%02u:%02u\0"     , lst.wHour, lst.wMinute, lst.wSecond);
			}


		//////////
		// Create the result
		//////
			result = iVariable_createAndPopulate_byText(thisCode, _VAR_TYPE_CHARACTER, buffer, (u32)strlen(buffer), false);
			if (!result)
				iError_reportByNumber(thisCode, _ERROR_INTERNAL_ERROR, NULL, false);


		//////////
		// Return our converted result
		//////
			return(result);

	}




//////////
//
// Function: TIMETOSECONDS()
// Converts a TIME() into a SECONDS().
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
//     p1			-- Character, in the format of TIME()
//
//////
// Returns:
//    f64			-- A 64-bit floating point of the equivalent SECONDS().
//////
// Example:
//    k = TIME()
//    ? TIMETOSECONDS(k)
//////
	SVariable* function_timetoseconds(SThisCode* thisCode, SReturnsParams* returnsParams)
	{
		return(ifunction_timesAndDatesConversion_common(thisCode, returnsParams, _CONVERSION_FUNCTION_TIME, _CONVERSION_FUNCTION_SECONDS));
	}

	// Note: Functions that use this must guarantee that at least one parameter is provided
	// Note: Two parameters are only valid if the output is a datetime or datetimex, the second parameter is used to obtain the missing information
	SVariable* ifunction_timesAndDatesConversion_common(SThisCode* thisCode, SReturnsParams* returnsParams, s32 tnIn, s32 tnOut)
	{
		SVariable* varP1 = returnsParams->params[0];
		SVariable* varP2 = returnsParams->params[1];

		SAllDatetime	adt;
		f32				lfVal32;
		f64				lfVal64;
		SVariable*		result;
		s8				buffer[64];
		bool			error;
		u32				errorNum;


		//////////
		// Validate the parameter is valid
		//////
			if (!iVariable_isValid(varP1))
			{
				iError_reportByNumber(thisCode, _ERROR_INVALID_ARGUMENT_TYPE_COUNT, iVariable_getRelatedComp(thisCode, varP1), false);
				return(NULL);
			}


		//////////
		// A second parameter is allowed for time, timex, seconds, and secondsx inputs, but only if their target is a datetime or datetimex
		//////
			memset(&adt, 0, sizeof(adt));
			if (iVariable_isValid(varP2))
			{
				if (tnOut == _CONVERSION_FUNCTION_DATETIME || tnOut == _CONVERSION_FUNCTION_DATETIMEX)
				{
					// Determine the source, only time, timex, seconds, and secondx are valid if a second parameter is provided
					switch (tnIn)
					{
						// Populate the date if it is provided properly
						case _CONVERSION_FUNCTION_DATE:
						case _CONVERSION_FUNCTION_DATETIME:
						case _CONVERSION_FUNCTION_DATETIMEX:
							if (iVariable_isTypeNumeric(varP2))
							{
								// Can be seconds,secondsx
								adt.fVal64 = iiVariable_getAs_f64(thisCode, varP2, false, &error, &errorNum);
								if (error)
								{
									iError_reportByNumber(thisCode, errorNum, iVariable_getRelatedComp(thisCode, varP1), false);
									return(NULL);
								}
								iiDateMath_get_HhMmSsMss_from_seconds((f32)adt.fVal64, &adt.nHour, &adt.nMinute, &adt.nSecond, &adt.nMillisecond);

							} else if (iVariable_isTypeDatetime(varP2)) {
								// Extract the seconds
								iiDateMath_get_HhMmSsMss_from_seconds(varP2->value.data_dt->seconds, &adt.nHour, &adt.nMinute, &adt.nSecond, &adt.nMillisecond);

							} else if (iVariable_isTypeDatetimeX(varP2)) {
								// Extract the seconds
								iiDateMath_get_YyyyMmDdHhMmSsMssNss_from_jseconds(varP2->value.data_dtx->jseconds, NULL, NULL, NULL, NULL, &adt.nHour, &adt.nMinute, &adt.nSecond, &adt.nMillisecond, &adt.nMicrosecond);

							} else {
								// Invalid
								iError_reportByNumber(thisCode, _ERROR_INVALID_ARGUMENT_TYPE_COUNT, iVariable_getRelatedComp(thisCode, varP1), false);
								return(NULL);
							}
							break;

						case _CONVERSION_FUNCTION_TIME:
						case _CONVERSION_FUNCTION_TIMEX:
						case _CONVERSION_FUNCTION_SECONDS:
						case _CONVERSION_FUNCTION_SECONDSX:
							// These can receive the date parameter as well
							if (iVariable_isTypeDate(varP2))
							{
								// Date
								iiDateMath_get_YyyyMmDd_from_YYYYMMDD(varP2->value.data_u8, &adt.nYear, &adt.nMonth, &adt.nDay);

							} else if (iVariable_isTypeDatetime(varP2)) {
								// Datetime
								iiDateMath_get_YyyyMmDd_from_julian(varP2->value.data_dt->julian, &adt.nYear, &adt.nMonth, &adt.nDay);
								// Note:  The SECONDS() comes from the time, timex, seconds, or secondsx

							} else if (iVariable_isTypeDatetimeX(varP2)) {
								// DatetimeX
								iiDateMath_get_YyyyMmDdHhMmSsMssNss_from_jseconds(varP2->value.data_dtx->jseconds, NULL, &adt.nYear, &adt.nMonth, &adt.nDay, NULL, NULL, NULL, NULL, NULL);

							} else {
								// Invalid
								iError_reportByNumber(thisCode, _ERROR_INVALID_ARGUMENT_TYPE_COUNT, iVariable_getRelatedComp(thisCode, varP1), false);
								return(NULL);
							}
							break;

						default:
							// These cannot receive the date parameter
							iError_reportByNumber(thisCode, _ERROR_INVALID_ARGUMENT_TYPE_COUNT, iVariable_getRelatedComp(thisCode, varP1), false);
							return(NULL);
					}

				} else if (tnOut == _CONVERSION_FUNCTION_DATETIME || tnOut == _CONVERSION_FUNCTION_DATETIMEX) {
					// 

				} else {
					// Invalid for this type
					iError_reportByNumber(thisCode, _ERROR_INVALID_ARGUMENT_TYPE_COUNT, iVariable_getRelatedComp(thisCode, varP1), false);
					return(NULL);
				}
			}



		//////////
		// Populate input
		//////
			switch (tnIn)
			{
				case _CONVERSION_FUNCTION_TIME:
					// Hh:Mm:Ss[.Mss]
					if (!iVariable_isTypeCharacter(varP1) || varP1->value.length < 8 || varP1->value.data[2] != ':' || varP1->value.data[5] != ':')
					{
						iError_reportByNumber(thisCode, _ERROR_INVALID_ARGUMENT_TYPE_COUNT, iVariable_getRelatedComp(thisCode, varP1), false);
						return(NULL);
					}
					adt.nHour	= atoi(varP1->value.data_s8);
					adt.nMinute	= atoi(varP1->value.data_s8 + 3);
					adt.nSecond	= atoi(varP1->value.data_s8 + 6);
					if (varP1->value.data[8] == '.')
						adt.nMillisecond = atoi(varP1->value.data_s8 + 9);
					break;

				case _CONVERSION_FUNCTION_TIMEX:
					// Hh:Mm:Ss[.Mss]
					// Hh:Mm:Ss[.Micsss]
					// Hh:Mm:Ss[.Nanosssss]
					if (!iVariable_isTypeCharacter(varP1) || varP1->value.length < 12 || varP1->value.data[2] != ':' || varP1->value.data[5] != ':')
					{
						iError_reportByNumber(thisCode, _ERROR_INVALID_ARGUMENT_TYPE_COUNT, iVariable_getRelatedComp(thisCode, varP1), false);
						return(NULL);
					}
					adt.nHour	= atoi(varP1->value.data_s8);
					adt.nMinute	= atoi(varP1->value.data_s8 + 3);
					adt.nSecond	= atoi(varP1->value.data_s8 + 6);
					if (varP1->value.data[8] == '.')
					{
						if (varP1->value.length == 12)
						{
							// Hh:Mm:Ss.Mss
							adt.nMillisecond = atoi(varP1->value.data_s8 + 9);

						} else if (varP1->value.length == 15) {
							// Hh:Mm:Ss.Micsss
							adt.nMicrosecond = atoi(varP1->value.data_s8 + 9);
							adt.nMillisecond	= (adt.nMicrosecond + 500) / 1000;

						} else if (varP1->value.length == 18) {
							// Hh:Mm:Ss.Nanosssss
							adt.nNanosecond		= atoi(varP1->value.data_s8 + 9);
							adt.nMicrosecond	= (adt.nNanosecond  + 500) / 1000;
							adt.nMillisecond	= (adt.nMicrosecond + 500) / 1000;
						}
					}
					break;

				case _CONVERSION_FUNCTION_SECONDS:
					if (!iVariable_isTypeNumeric(varP1))
					{
						iError_reportByNumber(thisCode, _ERROR_INVALID_ARGUMENT_TYPE_COUNT, iVariable_getRelatedComp(thisCode, varP1), false);
						return(NULL);
					}
					adt.fVal64 = iiVariable_getAs_f64(thisCode, varP1, false, &error, &errorNum);
					if (error)
					{
						iError_reportByNumber(thisCode, errorNum, iVariable_getRelatedComp(thisCode, varP1), false);
						return(NULL);
					}
					break;

				case _CONVERSION_FUNCTION_SECONDSX:
					if (!iVariable_isTypeNumeric(varP1))
					{
						iError_reportByNumber(thisCode, _ERROR_INVALID_ARGUMENT_TYPE_COUNT, iVariable_getRelatedComp(thisCode, varP1), false);
						return(NULL);
					}
					adt.fVal64 = iiVariable_getAs_f64(thisCode, varP1, false, &error, &errorNum);
					if (error)
					{
						iError_reportByNumber(thisCode, errorNum, iVariable_getRelatedComp(thisCode, varP1), false);
						return(NULL);
					}
					break;

				case _CONVERSION_FUNCTION_DATE:
					if (!iVariable_isTypeDate(varP1))
					{
						iError_reportByNumber(thisCode, _ERROR_INVALID_ARGUMENT_TYPE_COUNT, iVariable_getRelatedComp(thisCode, varP1), false);
						return(NULL);
					}
					iiDateMath_get_YyyyMmDd_from_YYYYMMDD(varP1->value.data_u8, &adt.nYear, &adt.nMonth, &adt.nDay);
					break;

				case _CONVERSION_FUNCTION_DATETIME:
					if (!iVariable_isTypeDatetime(varP1))
					{
						iError_reportByNumber(thisCode, _ERROR_INVALID_ARGUMENT_TYPE_COUNT, iVariable_getRelatedComp(thisCode, varP1), false);
						return(NULL);
					}
					iiDateMath_get_YyyyMmDd_from_julian(varP1->value.data_dt->julian, &adt.nYear, &adt.nMonth, &adt.nDay);
					iiDateMath_get_HhMmSsMss_from_seconds(varP1->value.data_dt->seconds, &adt.nHour, &adt.nMinute, &adt.nSecond, &adt.nMillisecond);
					adt.lMillisecondValid = true;
					break;

				case _CONVERSION_FUNCTION_DATETIMEX:
					if (!iVariable_isTypeDatetimeX(varP1))
					{
						iError_reportByNumber(thisCode, _ERROR_INVALID_ARGUMENT_TYPE_COUNT, iVariable_getRelatedComp(thisCode, varP1), false);
						return(NULL);
					}
					iiDateMath_get_YyyyMmDdHhMmSsMssNss_from_jseconds(varP1->value.data_dtx->jseconds, NULL, &adt.nYear, &adt.nMonth, &adt.nDay, &adt.nHour, &adt.nMinute, &adt.nSecond, &adt.nMillisecond, &adt.nMicrosecond);
					adt.lMillisecondValid = true;
					adt.lMicrosecondValid = true;
					break;

				default:
					// Should never happen
					// Check the call stack to determine the function which sent the incorrect parameter
					debug_nop;
					iError_reportByNumber(thisCode, _ERROR_INTERNAL_ERROR, iVariable_getRelatedComp(thisCode, varP1), false);
					return(NULL);
			}


		//////////
		// Populate output
		//////
			switch (tnOut)
			{
				case _CONVERSION_FUNCTION_TIME:
					// Hh:Mm:Ss.Mss
					switch (tnIn)
					{
						case _CONVERSION_FUNCTION_SECONDS:
						case _CONVERSION_FUNCTION_SECONDSX:
							iiDateMath_get_HhMmSsMssMics_from_secondsx(adt.fVal64, &adt.nHour, &adt.nMinute, &adt.nSecond, &adt.nMillisecond, &adt.nMicrosecond);
							break;
					}

					// Convert
					sprintf(buffer, "%02u:%02u:%02u.%03u\0", adt.nHour, adt.nMinute, adt.nSecond, adt.nMillisecond);
					result = iVariable_createAndPopulate_byText(thisCode, _VAR_TYPE_CHARACTER, (cs8*)buffer, -1, false);
					break;

				case _CONVERSION_FUNCTION_TIMEX:
					// Hh:Mm:Ss.Mss
					// Hh:Mm:Ss.Micsss
					// Hh:Mm:Ss.Nanosssss
					switch (tnIn)
					{
						case _CONVERSION_FUNCTION_SECONDS:
						case _CONVERSION_FUNCTION_SECONDSX:
							iiDateMath_get_HhMmSsMssMics_from_secondsx(adt.fVal64, &adt.nHour, &adt.nMinute, &adt.nSecond, &adt.nMillisecond, &adt.nMicrosecond);
							break;
					}

					// Convert
					     if (adt.lNanosecondValid)		sprintf(buffer, "%02u:%02u:%02u.%09u\0",	adt.nHour, adt.nMinute, adt.nSecond, adt.nNanosecond);
					else if (adt.lMicrosecondValid)		sprintf(buffer, "%02u:%02u:%02u.%06u\0",	adt.nHour, adt.nMinute, adt.nSecond, adt.nMicrosecond);
					else if (adt.lMillisecondValid)		sprintf(buffer, "%02u:%02u:%02u.%03u\0",	adt.nHour, adt.nMinute, adt.nSecond, adt.nMillisecond);
					else /* Default to microsecond */	sprintf(buffer, "%02u:%02u:%02u.%06u\0",	adt.nHour, adt.nMinute, adt.nSecond, adt.nMicrosecond);

					result = iVariable_createAndPopulate_byText(thisCode, _VAR_TYPE_CHARACTER, (cs8*)buffer, -1, false);
					break;

				case _CONVERSION_FUNCTION_SECONDS:
					// SECONDS()
					lfVal32 =	(f32)((adt.nHour * 60 * 60) + (adt.nMinute * 60) + (adt.nSecond));
					lfVal32 +=	(f32)adt.nMillisecond / 1000.0f;

					result = iVariable_createAndPopulate_byText(thisCode, _VAR_TYPE_F32, (cs8*)&lfVal32, sizeof(lfVal32), false);
					break;

				case _CONVERSION_FUNCTION_SECONDSX:
					// SECONDSX()
					lfVal64 = (f64)((adt.nHour * 60 * 60) + (adt.nMinute * 60) + (adt.nSecond));

					     if (adt.lNanosecondValid)		lfVal64 += (f64)adt.nNanosecond / 1000000000.0f;
					else if (adt.lMicrosecondValid)		lfVal64 += (f64)adt.nMicrosecond / 1000000.0f;
					else if (adt.lMillisecondValid)		lfVal64 += (f64)adt.nMillisecond / 1000.0f;
					else /* Default to microseconds */	lfVal64 += (f64)adt.nMicrosecond / 1000000.0f;

					result = iVariable_createAndPopulate_byText(thisCode, _VAR_TYPE_F64, (cs8*)&lfVal64, sizeof(lfVal64), false);
					break;

				case _CONVERSION_FUNCTION_DATE:
					result = iVariable_create(thisCode, _VAR_TYPE_DATE, NULL, true);
					if (result)
						iiDateMath_get_YYYYMMDD_from_YyyyMmDd(result->value.data_s8, adt.nYear, adt.nMonth, adt.nDay);
					break;

				case _CONVERSION_FUNCTION_DATETIME:
					result = iVariable_create(thisCode, _VAR_TYPE_DATETIME, NULL, true);
					if (result)
					{
						switch (tnIn)
						{
							case _CONVERSION_FUNCTION_SECONDS:
							case _CONVERSION_FUNCTION_SECONDSX:
								iiDateMath_get_HhMmSsMssMics_from_secondsx(adt.fVal64, &adt.nHour, &adt.nMinute, &adt.nSecond, &adt.nMillisecond, &adt.nMicrosecond);
								break;
						}

						result->value.data_dt->julian	= iiDateMath_get_julian_from_YyyyMmDd(NULL, adt.nYear, adt.nMonth, adt.nDay);
						result->value.data_dt->seconds	= iiDateMath_get_seconds_from_HhMmSsMss(adt.nHour, adt.nMinute, adt.nSecond, adt.nMillisecond);
					}
					break;

				case _CONVERSION_FUNCTION_DATETIMEX:
					result = iVariable_create(thisCode, _VAR_TYPE_DATETIMEX, NULL, true);
					if (result)
					{
						switch (tnIn)
						{
							case _CONVERSION_FUNCTION_SECONDS:
							case _CONVERSION_FUNCTION_SECONDSX:
								iiDateMath_get_HhMmSsMssMics_from_secondsx(adt.fVal64, &adt.nHour, &adt.nMinute, &adt.nSecond, &adt.nMillisecond, &adt.nMicrosecond);
								break;
						}

						result->value.data_dtx->jseconds = iiDateMath_get_jseconds_from_YyyyMmDdHhMmSsMssMics(NULL, adt.nYear, adt.nMonth, adt.nDay, adt.nHour, adt.nMinute, adt.nSecond, adt.nMillisecond, adt.nMicrosecond);
					}
					break;

				default:
					// Should never happen
					// Check the call stack to determine the function which sent the incorrect parameter
					debug_nop;
					iError_reportByNumber(thisCode, _ERROR_INTERNAL_ERROR, NULL, false);
					return(NULL);
			}


		//////////
		// Are we good?
		//////
			if (!result)
				iError_reportByNumber(thisCode, _ERROR_INTERNAL_ERROR, NULL, false);


		//////////
		// Signify our result
		//////
			return(result);

	}




//////////
//
// Function: TIMETOSECONDSX()
// Converts a TIME() into a SECONDSX().
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
//     p1			-- Character, in the format of TIME()
//
//////
// Returns:
//    f64			-- A 64-bit floating point of the equivalent SECONDSX().
//////
// Example:
//    k = TIME()
//    ? TIMETOSECONDSX(k)
//////
	SVariable* function_timetosecondsx(SThisCode* thisCode, SReturnsParams* returnsParams)
	{
		return(ifunction_timesAndDatesConversion_common(thisCode, returnsParams, _CONVERSION_FUNCTION_TIME, _CONVERSION_FUNCTION_SECONDSX));
	}




//////////
//
// Function: TIMETOT()
// Converts a TIME() into a DATETIME().
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
//     p1			-- Character, in the format of TIME()
//     p2			-- (Optional) DATE(), DATETIME(), or DATETIMEX()
//
//////
// Returns:
//    Datetime		-- The equivalent in a datetime with today's date
//////
// Example:
//    k = TIME()
//    t = DATE()
//    ? TIMETOT(k, t)
//////
	SVariable* function_timetot(SThisCode* thisCode, SReturnsParams* returnsParams)
	{
		return(ifunction_timesAndDatesConversion_common(thisCode, returnsParams, _CONVERSION_FUNCTION_TIME, _CONVERSION_FUNCTION_DATETIME));
	}




//////////
//
// Function: TIMETOX()
// Converts a TIME() into a DATETIMEX().
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
//     p1			-- Character, in the format of TIME()
//     p2			-- (Optional) DATE(), DATETIME(), or DATETIMEX()
//
//////
// Returns:
//    DatetimeX		-- The equivalent in a datetimex with today's date
//////
// Example:
//    k = TIME()
//    t = DATE()
//    ? TIMETOX(k, t)
//////
	SVariable* function_timetox(SThisCode* thisCode, SReturnsParams* returnsParams)
	{
		return(ifunction_timesAndDatesConversion_common(thisCode, returnsParams, _CONVERSION_FUNCTION_TIME, _CONVERSION_FUNCTION_DATETIMEX));
	}




//////////
//
// Function: TIMEX()
// Returns the timex in Hh:Mm:Ss:Micsss format
//
//////
// Version 0.57
// Last update:
//     Apr.25.2015
//////
// Change log:
//     Apr.25.2015 - Initial creation by Rick C. Hodgin
//////
// Parameters:
//     pDatetimex	-- (optional) Datetimex, any value, if they want the time from that datetimex
//     pSecondsx	-- (optional) Floating point, any value 0..86400, if they want the time from a SECONDSX() value
//
//////
// Returns:
//    Character		-- Current time() as HH:MM:SS.Micsss
//
//////
	SVariable* function_timex(SThisCode* thisCode, SReturnsParams* returnsParams)
	{
		return(ifunction_timex_common(thisCode, returnsParams, true));
	}




//////////
//
// Function: TIMEXTOSECONDS()
// Converts a TIMEX() into a SECONDS().
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
//     p1			-- Character, in the format of TIMEX()
//
//////
// Returns:
//    f64			-- A 64-bit floating point of the equivalent SECONDS().
//////
// Example:
//    k = TIMEX()
//    ? TIMEXTOSECONDS(k)
//////
	SVariable* function_timextoseconds(SThisCode* thisCode, SReturnsParams* returnsParams)
	{
		return(ifunction_timesAndDatesConversion_common(thisCode, returnsParams, _CONVERSION_FUNCTION_TIMEX, _CONVERSION_FUNCTION_SECONDS));
	}




//////////
//
// Function: TIMEXTOSECONDSX()
// Converts a TIMEX() into a SECONDSX().
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
//     p1			-- Character, in the format of TIMEX()
//
//////
// Returns:
//    f64			-- A 64-bit floating point of the equivalent SECONDSX().
//////
// Example:
//    k = TIMEX()
//    ? TIMEXTOSECONDSX(k)
//////
	SVariable* function_timextosecondsx(SThisCode* thisCode, SReturnsParams* returnsParams)
	{
		return(ifunction_timesAndDatesConversion_common(thisCode, returnsParams, _CONVERSION_FUNCTION_TIMEX, _CONVERSION_FUNCTION_SECONDSX));
	}




//////////
//
// Function: TIMEXTOT()
// Converts a TIMEX() into a DATETIME().
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
//     p1			-- Character, in the format of TIMEX()
//     p2			-- (Optional) DATE(), DATETIME(), or DATETIMEX()
//
//////
// Returns:
//    Datetime		-- The equivalent in a datetime with today's date
//////
// Example:
//    k = TIMEX()
//    t = DATE()
//    ? TIMEXTOT(k, t)
//////
	SVariable* function_timextot(SThisCode* thisCode, SReturnsParams* returnsParams)
	{
		return(ifunction_timesAndDatesConversion_common(thisCode, returnsParams, _CONVERSION_FUNCTION_TIMEX, _CONVERSION_FUNCTION_DATETIME));
	}




//////////
//
// Function: TIMEXTOX()
// Converts a TIMEX() into a DATETIMEX().
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
//     p1			-- Character, in the format of TIMEX()
//     p2			-- (Optional) DATE(), DATETIME(), or DATETIMEX()
//
//////
// Returns:
//    DatetimeX		-- The equivalent in a datetimex with today's date
//////
// Example:
//    k = TIMEX()
//    t = DATE()
//    ? TIMEXTOX(k, t)
//////
	SVariable* function_timextox(SThisCode* thisCode, SReturnsParams* returnsParams)
	{
		return(ifunction_timesAndDatesConversion_common(thisCode, returnsParams, _CONVERSION_FUNCTION_TIMEX, _CONVERSION_FUNCTION_DATETIMEX));
	}




//////////
//
// Function: TRANSFORM()
// Converts any variable input to a character form, and applies formatting based on codes.
//
//////
// Version 0.56
// Last update:
//     Aug.03.2014
//////
// Change log:
//     Aug.03.2014 - Initial creation
//////
// Parameters:
//     pString		-- Character, the variable to transform
//     pformat		-- Character, the format codes
//
//////
// Returns:
//    Character		-- The string after the variable was converted and formatted
//////
	SVariable* function_transform(SThisCode* thisCode, SReturnsParams* returnsParams)
	{
		SVariable* varVariable	= returnsParams->params[0];
		SVariable* varFormat	= returnsParams->params[1];
		SVariable* result;


		//////////
		// Parameter 1 must be valid
		//////
			if (!iVariable_isValid(varVariable))
			{
				iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_getRelatedComp(thisCode, varVariable), false);
				return(NULL);
			}


		//////////
		// Parameter 2 is optional, but if present...
		//////
			if (iVariable_isValid(varFormat))
			{
				// ...it must be character
				if (!iVariable_isTypeCharacter(varFormat))
				{
					iError_reportByNumber(thisCode, _ERROR_P2_IS_INCORRECT, iVariable_getRelatedComp(thisCode, varFormat), false);
					return(NULL);
				}
			}


		//////////
		// Create the return variable
		//////
			result = iVariable_convertForDisplay(thisCode, varVariable);


		//////////
		// Formatters:
		//		@D		date,		convert using SET DATE
		//		@E		date,		convert using BRITISH
		//		@YL		date,		convert using LONG
		//		@YS		date,		convert using SHORT
		//		Y		logical,	use Y and N
		//		@T		character,	ALLTRIM() input before conversion
		//		@!		character,	UPPER() input
		//		!		character,	UPPER() on the character in this position
		//		.		Use decimal point
		//		,		Use 1000s separator
		//		X		Specifies output width by character count
		//
		// Output formats:
		//		@B		numeric,	left-justify
		//		@$		numeric,	append based on SET CURRENCY symbol
		//		@C		numeric,	append "CR" after if zero or positive
		//		@X		numeric,	appends "DB" after if negative
		//		@L		numeric,	prefix with leading 0s
		//		@Z		numeric,	if zero display CHR(32) instead of "0"
		//		@(		numeric,	surround with () if negative
		//		@^		numeric,	scientific notation
		//		@0		numeric,	convert to hexadecimal equivalent
		//		@R		format around other characters encountered using 9,#,! for source data
		//////


		//////////
		// Indicate our status
		//////
			return(result);
	}




//////////
//
// Function: TTOC()
// Converts a DateTime expression to a Character value with the specified format.
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
//     p1			-- Datetime
//	   p2			-- Numeric: 
//						1 -- yyyymmddhhmmss[.mss]
//						2 -- only the time portion of p1
//						3 -- yyyy-mm-ddThh:mm:ss[.mss]
//////
// Returns:
//    Character. TTOC( ) returns a DateTime expression as a character string.
//////
	SVariable* function_ttoc(SThisCode* thisCode, SReturnsParams* returnsParams)
	{
		SVariable* varParam = returnsParams->params[0];
		SVariable* varFlag	= returnsParams->params[1];

		s32			lnMillisecond;
		u32			lnYear, lnMonth, lnDay, lnFlag;
		u32			lnHour, lnHourAdjusted, lnMinute, lnSecond;
		bool		llHour24;
		cs8*		lcAmPmText;
		s8			buffer[64];
		u32			errorNum;
		bool		error;

		SVariable*	result;


		//////////
		// Parameter 1 must be datetime
		//////
// TODO:  Must also support DATETIMEX at some point
			if (!iVariable_isValid(varParam) || !iVariable_isTypeDatetime(varParam))
			{
				iError_reportByNumber(thisCode, _ERROR_INVALID_ARGUMENT_TYPE_COUNT, iVariable_getRelatedComp(thisCode, varParam), false);
				return(NULL);
			}

		//////////
		// If Parameter 2 is provided, must be numeric
		//////
			if (varFlag)
			{

				//////////
				// Numeric?
				//////
					if (!iVariable_isValid(varFlag) || !iVariable_isTypeNumeric(varFlag))
					{
						iError_reportByNumber(thisCode, _ERROR_INVALID_ARGUMENT_TYPE_COUNT, iVariable_getRelatedComp(thisCode, varFlag), false);
						return(NULL);
					}


				//////////
				// Grab the flag value
				//////
					lnFlag = iiVariable_getAs_s32(thisCode, varFlag, false, &error, &errorNum);
					if (error)
					{
						// An error extracting the value (should never happen)
						iError_reportByNumber(thisCode, errorNum, iVariable_getRelatedComp(thisCode, varFlag), false);
						return(NULL);
					}	


				//////////
				// Grab the value
				//////
					iiDateMath_get_YyyyMmDd_from_julian(varParam->value.data_dt->julian, &lnYear, &lnMonth, &lnDay);
					iiDateMath_get_HhMmSsMss_from_seconds(varParam->value.data_dt->seconds, &lnHour, &lnMinute, &lnSecond, &lnMillisecond);


				//////////
				// Generate the output
				//////
					switch(lnFlag)
					{
						// YYYYMMDDHhMmSs[Mss]
						case 1:
							if (_settings && propGet_settings_ncset_datetimeMilliseconds(_settings))
							{
								// Include milliseconds
								sprintf(buffer, "%04u%02u%02u%02u%02u%02u%03u\0", lnYear, lnMonth, lnDay, lnHour, lnMinute, lnSecond, lnMillisecond);

							} else {
								// No milliseconds
								sprintf(buffer, "%04u%02u%02u%02u%02u%02u\0", lnYear, lnMonth, lnDay, lnHour, lnMinute, lnSecond);
							}
							break;


						// Hh:Mm:Ss[.Mss]
						case 2:
							// Adjust for our 24-hour settings
							llHour24		= propGet_settings_Hours24(_settings);
							lnHourAdjusted	= iTime_adjustHour_toAMPM(lnHour, !llHour24);
							lcAmPmText		= (cs8*)((llHour24) ? "" : (cs8*)iTime_amOrPm(lnHour, cgc_space_am_uppercase, cgc_space_pm_lowercase));

							if (propGet_settings_ncset_datetimeMilliseconds(_settings))
							{
								// Include milliseconds
								sprintf(buffer, "%02u:%02u:%02u.%03u%s\0", lnHourAdjusted, lnMinute, lnSecond, lnMillisecond, lcAmPmText);

							} else {
								// No milliseconds
								sprintf(buffer, "%02u:%02u:%02u%s\0", lnHourAdjusted, lnMinute, lnSecond, lcAmPmText);
							}
							break;


						// YYYY-MM-DDThh:mm:ss[.Mss]
						case 3:
							if (_settings && propGet_settings_ncset_datetimeMilliseconds(_settings))
							{
								// Include milliseconds
								sprintf(buffer, "%04u-%02u-%02uT%02u:%02u:%02u.%03u\0", lnYear, lnMonth, lnDay, lnHour, lnMinute, lnSecond, lnMillisecond);

							} else {
								// No milliseconds (XML DateTime format)
								sprintf(buffer, "%04u-%02u-%02uT%02u:%02u:%02u\0", lnYear, lnMonth, lnDay, lnHour, lnMinute, lnSecond);
							}
							break;

						default:
							// If we get here, invalid parameter specified
							iError_reportByNumber(thisCode, _ERROR_INVALID_ARGUMENT_TYPE_COUNT, iVariable_getRelatedComp(thisCode, varFlag), false);
							return(NULL);
					}


				//////////
				// Create and populate the return variable
				//////
					result = iVariable_createAndPopulate_byText(thisCode, _VAR_TYPE_CHARACTER, (cs8*)buffer, (u32)strlen(buffer), false);

			} else {

				//////////
				// Create and populate the return variable from the standard / default ttoc() algorithm
				//////
					result = iVariable_convertForDisplay(thisCode, varParam);
			}


		//////////
		// Are we good?
		//////
			if (!result)
				iError_reportByNumber(thisCode, _ERROR_INTERNAL_ERROR, NULL, false);


		//////////
		// Return our converted result
		//////
			return(result);

	}




//////////
//
// Function: TTOD()
// Returns a Date value from a Datetime expression.
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
//     p1			-- Datetime
//
//////
// Returns:
//    Datetime	-- DTOT( ) adds a default time of 12:00:00 AM (if SET HOURS is 12) or 00:00:00 (if SET HOURS is 24) to the date to produce a valid DateTime value.
//////
	SVariable* function_ttod(SThisCode* thisCode, SReturnsParams* returnsParams)
	{
		return(ifunction_timesAndDatesConversion_common(thisCode, returnsParams, _CONVERSION_FUNCTION_DATETIME, _CONVERSION_FUNCTION_DATE));
	}




//////////
//
// Function: TTOSECONDS()
// Converts a DATETIME() into a SECONDS().
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
//     p1			-- Datetime or DatetimeX
//
//////
// Returns:
//    f64			-- A 64-bit floating point number equivalent to the SECONDS() component
//////
// Example:
//    k = DATETIME()
//    ? TTOSECONDS(k)
//////
	SVariable* function_ttoseconds(SThisCode* thisCode, SReturnsParams* returnsParams)
	{
		return(ifunction_timesAndDatesConversion_common(thisCode, returnsParams, _CONVERSION_FUNCTION_DATETIME, _CONVERSION_FUNCTION_SECONDS));
	}




//////////
//
// Function: TTOSECONDSX()
// Converts a DATETIME() into a SECONDSX().
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
//     p1			-- Datetime or DatetimeX
//
//////
// Returns:
//    f64			-- A 64-bit floating point number equivalent to the SECONDSX() component
//////
// Example:
//    k = DATETIME()
//    ? TTOSECONDSX(k)
//////
	SVariable* function_ttosecondsx(SThisCode* thisCode, SReturnsParams* returnsParams)
	{
		return(ifunction_timesAndDatesConversion_common(thisCode, returnsParams, _CONVERSION_FUNCTION_DATETIME, _CONVERSION_FUNCTION_SECONDSX));
	}




//////////
//
// Function: TTOTIME()
// Converts a DATETIME() into a TIME().
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
//     p1			-- Datetime or DatetimeX
//
//////
// Returns:
//    Character		-- A conversion into the TIME() format.
//////
// Example:
//    k = DATETIME()
//    ? TTOTIME(k)
//////
	SVariable* function_ttotime(SThisCode* thisCode, SReturnsParams* returnsParams)
	{
		return(ifunction_timesAndDatesConversion_common(thisCode, returnsParams, _CONVERSION_FUNCTION_DATETIME, _CONVERSION_FUNCTION_TIME));
	}




//////////
//
// Function: TTOTIMEX()
// Converts a DATETIME() into a TIMEX().
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
//     p1			-- Datetime or DatetimeX
//
//////
// Returns:
//    Character		-- A conversion into the TIMEX() format.
//////
// Example:
//    k = DATETIME()
//    ? TTOTIMEX(k)
//////
	SVariable* function_ttotimex(SThisCode* thisCode, SReturnsParams* returnsParams)
	{
		return(ifunction_timesAndDatesConversion_common(thisCode, returnsParams, _CONVERSION_FUNCTION_DATETIME, _CONVERSION_FUNCTION_TIMEX));
	}




//////////
//
// Function: TTOX()
// Converts a DATETIME() into a DATETIMEX().
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
//     p1			-- Datetime
//
//////
// Returns:
//    DatetimeX		-- A conversion into the DATETIMEX() format.
//////
// Example:
//    k = DATETIME()
//    ? TTOX(k)
//////
	SVariable* function_ttox(SThisCode* thisCode, SReturnsParams* returnsParams)
	{
		return(ifunction_timesAndDatesConversion_common(thisCode, returnsParams, _CONVERSION_FUNCTION_DATETIME, _CONVERSION_FUNCTION_DATETIMEX));
	}




//////////
//
// Function: TYPE()
// Returns the TYPE() for the indicated variable
//
//////
// Version 0.57
// Last update:
//     Apr.05.2015
//////
// Change log:
//     Apr.05.2015 - Initial creation
//////
// Parameters:
//     p1			-- The variable to examine
//     p2			-- (Optional) If present, must be 1, indicating extended TYPE() information
//
//////
// Returns:
//    Character		-- A one-digit code indicating the type
//////
	SVariable* function_type(SThisCode* thisCode, SReturnsParams* returnsParams)
	{
		SVariable* varLookup	= returnsParams->params[0];
		SVariable* varExtraInfo	= returnsParams->params[1];

		s32				lnExtraInfo;
		bool			llExtraInfo, llManufactured;
		SComp*			compVarLookup;
		SVariable*		var;
		SVariable*		result;
		bool			error;
		u32				errorNum;


		//////////
		// varLookup must be character
		//////
			if (!iVariable_isValid(varLookup) || !iVariable_isTypeCharacter(varLookup))
			{
				iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_getRelatedComp(thisCode, varLookup), false);
				return(NULL);
			}
		

		//////////
		// If varExtraInfo is specified, must be numeric, and 1
		//////
			if (varExtraInfo)
			{

				//////////
				// Must be numeric
				//////
					if (!iVariable_isValid(varExtraInfo) || !iVariable_isTypeNumeric(varExtraInfo))
					{
						iError_reportByNumber(thisCode, _ERROR_P2_IS_INCORRECT, iVariable_getRelatedComp(thisCode, varExtraInfo), false);
						return(NULL);
					}


				//////////
				// Grab the value
				//////
					lnExtraInfo = iiVariable_getAs_s32(thisCode, varExtraInfo, false, &error, &errorNum);
					if (error)
					{
						iError_reportByNumber(thisCode, errorNum, iVariable_getRelatedComp(thisCode, varExtraInfo), false);
						return(NULL);
					}


				//////////
				// Must be 1
				//////
					if (lnExtraInfo != 1)
					{
						iError_reportByNumber(thisCode, _ERROR_PARAMETER_MUST_BE_1, iVariable_getRelatedComp(thisCode, varExtraInfo), false);
						return(NULL);
					}


				//////////
				// If we get here, we're good
				//////
					llExtraInfo = true;


			} else {
				// No extra info
				llExtraInfo = false;
			}


		//////////
		// The varLookup points to something that needs to be looked up indirectly
		//////
			compVarLookup			= iVariable_getRelatedComp(thisCode, varLookup);
			compVarLookup->iCode	= _ICODE_ALPHANUMERIC;
			compVarLookup->start	+= 1;		// Skip leading quote for start
			compVarLookup->length	-= 2;		// Back off for both quotes for length
			var = iEngine_get_variableName_fromComponent(thisCode, compVarLookup, &llManufactured, false);
			if (!var)
			{
				iError_reportByNumber(thisCode, _ERROR_VARIABLE_NOT_FOUND, iVariable_getRelatedComp(thisCode, varLookup), false);
				return(NULL);
			}


		//////////
		// Compute our result
		//////
			result = ifunction_type_common(thisCode, var, llExtraInfo, false, false);


		//////////
		// Clean house
		//////
			if (llManufactured)
				iVariable_delete(thisCode, var, true);


		//////////
		// Return our result
		//////
			return(result);

	}

	// Handles type() and vartype()
	SVariable* ifunction_type_common(SThisCode* thisCode, SVariable* var, bool tlExtraInfo, bool tlIsVartype, bool tlNullIsType)
	{
		s8				c;
		SBaseClassMap*	baseClassMap;
		SVariable*		result;


		//////////
		// var holds the actual type we're testing
		//////
			if (tlExtraInfo)
			{
				// Returning extra information
				if (var->varType == _VAR_TYPE_OBJECT)
				{
					// It is a collection class?
					baseClassMap = iiObj_getBaseclass_byType(thisCode, var->obj->objType);
					if (baseClassMap && baseClassMap->objProps == &gsProps_collection[0])
					{
						// It is a collection
						c = 'C';

					} else {
						// Unknown
						c = 'U';
					}

				} else if (var->varType == _VAR_TYPE_ARRAY) {
					// It's an array
					c = 'A';

				} else {
					// Unknown
					c = 'U';
				}

			} else {
				// Standard
				if ((!var->value.data || var->value.length == 0) && tlIsVartype)
				{
					// NULL
					c = 'X';

				} else {
					switch (var->varType)
					{
						case _VAR_TYPE_NULL:
							c = ((tlIsVartype) ? 'X' : 'L');
							break;

						case _VAR_TYPE_CHARACTER:
							c = 'C';
							break;

						case _VAR_TYPE_LOGICAL:
							c = 'L';
							break;

						case _VAR_TYPE_DATE:
							c = 'D';
							break;

						case _VAR_TYPE_DATETIME:
							c = 'T';
							break;

						case _VAR_TYPE_DATETIMEX:
							c = 't';
							break;

						case _VAR_TYPE_FIELD:
							// Based on the associated field type
							switch(var->field->fr2->type)
							{
								case 'D':	// Date
								case 'T':	// Datetime
								case 'L':	// Logical
								case 'N':	// Numeric
								case 'Y':	// currency, which is technically an 8-byte integer (s64)
								case 'C':	// Character
									c = var->field->fr2->type;
									break;

								case 'X':	// DatetimeX
									c = 't';
									break;

								case 'I':	// 4-byte integer (s32)
								case 'F':	// Float
								case 'B':	// Double (f64)
									c = 'N';
									break;

								case 'M':	// Memo
									c = 'C';
									break;

// Unsupported in VJr:
// 								case 'W':	// Blob
// 								case 'G':	// General
// 								case 'Q':	// Varbinary
// 								case 'V':	// Varchar
								default:
									c = 'U';
									break;
							}
							break;

						case _VAR_TYPE_OBJECT:
							c = 'O';
							break;

						default:
							if (var->varType == _VAR_TYPE_CURRENCY)
							{
								// Currency
								c = 'Y';

							} else if (var->varType >= _VAR_TYPE_NUMERIC_START && var->varType <= _VAR_TYPE_NUMERIC_END) {
								// Numeric
								c = 'N';

							} else {
								// Unknown
								c = 'U';
							}
							break;
					}
				}
			}


		//////////
		// For vartype(), if nulls are to return x then we need to possibly adjust it
		//////
			if (tlIsVartype && !tlNullIsType && (var->varType == _VAR_TYPE_NULL || !var->value.data || var->value.length == 0))
				c = 'X';	// It is NULL


		//////////
		// Create our return result
		//////
			result = iVariable_createAndPopulate_byText(thisCode, _VAR_TYPE_CHARACTER, &c, 1, false);
			if (!result)
				iError_reportByNumber(thisCode, _ERROR_INTERNAL_ERROR, NULL, false);


		//////////
		// Indicate our result
		//////
			return(result);

	}




//////////
//
// Function: TYPEDETAIL()
// Returns the detailed TYPE() information.
//
//////
// Version 0.57
// Last update:
//     Apr.05.2015
//////
// Change log:
//     Apr.05.2015 - Initial creation
//////
// Parameters:
//     p1			-- The variable to examine
//
//////
// Returns:
//    Character		-- The expanded detail type string
//////
	SVariable* function_typedetail(SThisCode* thisCode, SReturnsParams* returnsParams)
	{
		SVariable* var = returnsParams->params[0];


		// Return the typedetail
		return(iVariable_get_typeDetail(thisCode, var));
	}
