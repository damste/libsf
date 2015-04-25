//////////
//
// /libsf/source/vjr/commands/funcs/d.cpp
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
// Function: DATE()
// Returns the current local time, or uses the input variables to create the indicated date.
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
//     pYear		-- (optional) Numeric, in the range 1600..2400
//     pMonth		-- (optional) Numeric, in the range 1..12
//     pDay			-- (optional) Numeric, in the range 1..(varies based on month+year, not more than 31)
//
//////
// Returns:
//    Date			-- Current date(), or input converted to date
//////
	SVariable* function_date(SThisCode* thisCode, SReturnsParams* returnsParams)
	{
		SVariable*	varYear			= returnsParams->params[0];
		SVariable*	varMonth		= returnsParams->params[1];
		SVariable*	varDay			= returnsParams->params[2];

		SVariable*	result;
		u32			errorNum;
		bool		error;
		SYSTEMTIME	lst;
		s8			buffer[16];


		// Have they provided us with data?
		if (!varYear)
		{
			// Nope, we are creating the current system time
			if (_settings)		iTime_getLocalOrSystem(&lst, propGet_settings_TimeLocal(_settings));
			else				GetLocalTime(&lst);

		} else {
			// They have provided us date parameters.
			// Default to 01/01/1600 for any date
			lst.wYear			= 1600;
			lst.wMonth			= 1;
			lst.wDay			= 1;


			//////////
			// pYear must be numeric, and in the range of 1600..2400
			//////
				if (iVariable_isValid(varYear))
				{
					// They gave us a pYear
					if (!iVariable_isTypeNumeric(varYear))
					{
						iError_report(thisCode, (cu8*)"Year must be numeric", false);
						return(NULL);
					}
					lst.wYear = (u16)iiVariable_getAs_s32(thisCode, varYear, false, &error, &errorNum);
					if (!error && (lst.wYear < 1600 || lst.wYear > 2400))
					{
						iError_reportByNumber(thisCode, _ERROR_OUT_OF_RANGE, iVariable_getRelatedComp(thisCode, varYear), false);
						return(NULL);
					}
				}


			//////////
			// pMonth must be numeric, and in the range of 1..12
			//////
				if (iVariable_isValid(varMonth))
				{
					// They gave us a pMonth
					if (!iVariable_isTypeNumeric(varMonth))
					{
						iError_report(thisCode, (cu8*)"Month must be numeric", false);
						return(NULL);
					}
					lst.wMonth = (u16)iiVariable_getAs_s32(thisCode, varMonth, false, &error, &errorNum);
					if (!error && (lst.wMonth < 1 || lst.wMonth > 12))
					{
						iError_reportByNumber(thisCode, _ERROR_OUT_OF_RANGE, iVariable_getRelatedComp(thisCode, varMonth), false);
						return(NULL);
					}
				}


			//////////
			// pDay must be numeric, and in a valid range for the year and month
			//////
				if (iVariable_isValid(varDay))
				{
					// They gave us a pDay
					if (!iVariable_isTypeNumeric(varDay))
					{
						iError_report(thisCode, (cu8*)"Day must be numeric", false);
						return(NULL);
					}
					lst.wDay = (u16)iiVariable_getAs_s32(thisCode, varDay, false, &error, &errorNum);
					if (!error && !iDateMath_isDayValidForDate(lst.wYear, lst.wMonth, lst.wDay))
					{
						iError_reportByNumber(thisCode, _ERROR_OUT_OF_RANGE, iVariable_getRelatedComp(thisCode, varDay), false);
						return(NULL);
					}
				}

		}


		//////////
		// Convert lst.* into a VJr date variable
		//////
			// Date is stored as YYYYMMDD
			iiDateMath_get_YYYYMMDD_from_YyyyMmDd(buffer, lst.wYear, lst.wMonth, lst.wDay);
			result = iVariable_createAndPopulate_byText(thisCode, _VAR_TYPE_DATE, buffer, 8, false);
			if (!result)
				iError_reportByNumber(thisCode, _ERROR_INTERNAL_ERROR, NULL, false);


		//////////
		// Return our converted result
		//////
			return(result);

	}




//////////
//
// Function: DATETIME()
// Returns the current local time, or uses the input variables to create the indicated datetime.
//
//////
// Version 0.56
// Last update:
//     Jul.10.2014
//////
// Change log:
//     Jul.10.2014 - Initial creation
//////
// Parameters:
//     pYear		-- (optional) Numeric, in the range 1600..2400
//     pMonth		-- (optional) Numeric, in the range 1..12
//     pDay			-- (optional) Numeric, in the range 1..(varies based on month+year, not more than 31)
//     pHour		-- (optional) Numeric, in the range 0..23
//     pMinute		-- (optional) Numeric, in the range 0..59
//     pSecond		-- (optional) Numeric, in the range 0..59
//     pMillisecond	-- (optional) Numeric, in the range 0..999
//
//////
// Returns:
//    Datetime		-- Current datetime(), or input converted to datetime
//
//////
	SVariable* function_datetime(SThisCode* thisCode, SReturnsParams* returnsParams)
	{
		// Return the datetime
		return(ifunction_datetimex_common(thisCode, returnsParams, false));
	}




//////////
//
// Function: DATETIMEX()
// Returns the current local time, or uses the input variables to create the indicated datetimex.
//
//////
// Version 0.56
// Last update:
//     Apr.25.2015
//////
// Change log:
//     Apr.25.2015 - Initial creation
//////
// Parameters:
//     pYear		-- (optional) Numeric, in the range 1600..2400
//     pMonth		-- (optional) Numeric, in the range 1..12
//     pDay			-- (optional) Numeric, in the range 1..(varies based on month+year, not more than 31)
//     pHour		-- (optional) Numeric, in the range 0..23
//     pMinute		-- (optional) Numeric, in the range 0..59
//     pSecond		-- (optional) Numeric, in the range 0..59
//     pMillisecond	-- (optional) Numeric, in the range 0..999
//     pNanosecond	-- (optional) Numeric, in the range 0..999999999
//
//////
// Returns:
//    Datetimex		-- Current datetimex(), or input converted to datetimex
//
//////
	SVariable* function_datetimex(SThisCode* thisCode, SReturnsParams* returnsParams)
	{
		// Return the datetimex
		return(ifunction_datetimex_common(thisCode, returnsParams, true));
	}

	SVariable* ifunction_datetimex_common(SThisCode* thisCode, SReturnsParams* returnsParams, bool tlIsDatetimeX)
	{
		SVariable*	varYear			= returnsParams->params[0];
		SVariable*	varMonth		= returnsParams->params[1];
		SVariable*	varDay			= returnsParams->params[2];
		SVariable*	varHour			= returnsParams->params[3];
		SVariable*	varMinute		= returnsParams->params[4];
		SVariable*	varSecond		= returnsParams->params[5];
		SVariable*	varMillisecond	= returnsParams->params[6];
		SVariable*	varNanosecond	= returnsParams->params[7];		// Only if tlIsDatetimeX

		s32				lnMicrosecond;
		SVariable*		result;
		f32				lfJulian;
		u32				errorNum;
		bool			error;
		SYSTEMTIME		lst;


		// Have they provided us with data?
		if (!varYear)
		{
			// Nope, we are creating the current system time
			if (_settings)		iTime_getLocalOrSystem(&lst, propGet_settings_TimeLocal(_settings));
			else				GetLocalTime(&lst);

			if (tlIsDatetimeX)
			{
				lst.wMilliseconds	= 0;
				lnMicrosecond		= iiDateMath_get_currentMicrosecond();
			}

		} else {
			// They have provided us datetime/x parameters.
			// Default to 01/01/1600 00:00:00.000 for any
			lst.wYear			= 1600;
			lst.wMonth			= 1;
			lst.wDay			= 1;
			lst.wHour			= 0;
			lst.wMinute			= 0;
			lst.wSecond			= 0;
			lst.wMilliseconds	= 0;


			//////////
			// pYear must be numeric, and in the range of 1600..2400
			//////
				if (iVariable_isValid(varYear))
				{
					// They gave us a pYear
					if (!iVariable_isTypeNumeric(varYear))
					{
						iError_report(thisCode, (cu8*)"Year must be numeric", false);
						return(NULL);
					}
					lst.wYear = (u16)iiVariable_getAs_s32(thisCode, varYear, false, &error, &errorNum);
					if (!error && (lst.wYear < 1600 || lst.wYear > 2400))
					{
						iError_reportByNumber(thisCode, _ERROR_OUT_OF_RANGE, iVariable_getRelatedComp(thisCode, varYear), false);
						return(NULL);
					}
				}


			//////////
			// pMonth must be numeric, and in the range of 1..12
			//////
				if (iVariable_isValid(varMonth))
				{
					// They gave us a pMonth
					if (!iVariable_isTypeNumeric(varMonth))
					{
						iError_report(thisCode, (cu8*)"Month must be numeric", false);
						return(NULL);
					}
					lst.wMonth = (u16)iiVariable_getAs_s32(thisCode, varMonth, false, &error, &errorNum);
					if (!error && (lst.wMonth < 1 || lst.wMonth > 12))
					{
						iError_reportByNumber(thisCode, _ERROR_OUT_OF_RANGE, iVariable_getRelatedComp(thisCode, varMonth), false);
						return(NULL);
					}
				}


			//////////
			// pDay must be numeric, and in a valid range for the year and month
			//////
				if (iVariable_isValid(varDay))
				{
					// They gave us a pDay
					if (!iVariable_isTypeNumeric(varDay))
					{
						iError_report(thisCode, (cu8*)"Day must be numeric", false);
						return(NULL);
					}
					lst.wDay = (u16)iiVariable_getAs_s32(thisCode, varDay, false, &error, &errorNum);
					if (!error && !iDateMath_isDayValidForDate(lst.wYear, lst.wMonth, lst.wDay))
					{
						iError_reportByNumber(thisCode, _ERROR_OUT_OF_RANGE, iVariable_getRelatedComp(thisCode, varDay), false);
						return(NULL);
					}
				}


			//////////
			// pHour must be numeric, and in the range of 0..23
			//////
				if (iVariable_isValid(varHour))
				{
					// They gave us a pHour
					if (!iVariable_isTypeNumeric(varHour))
					{
						iError_report(thisCode, (cu8*)"Hours must be numeric", false);
						return(NULL);
					}
					lst.wHour = (u16)iiVariable_getAs_s32(thisCode, varHour, false, &error, &errorNum);
					if (!error && (lst.wHour < 0 || lst.wHour > 23))
					{
						iError_reportByNumber(thisCode, _ERROR_OUT_OF_RANGE, iVariable_getRelatedComp(thisCode, varHour), false);
						return(NULL);
					}
				}


			//////////
			// pMinute must be numeric, and in the range of 0..59
			//////
				if (iVariable_isValid(varMinute))
				{
					// They gave us a pMinute
					if (!iVariable_isTypeNumeric(varMinute))
					{
						iError_report(thisCode, (cu8*)"Minutes must be numeric", false);
						return(NULL);
					}
					lst.wMinute = (u16)iiVariable_getAs_s32(thisCode, varMinute, false, &error, &errorNum);
					if (!error && (lst.wMinute < 0 || lst.wMinute > 59))
					{
						iError_reportByNumber(thisCode, _ERROR_OUT_OF_RANGE, iVariable_getRelatedComp(thisCode, varMinute), false);
						return(NULL);
					}
				}


			//////////
			// pSecond must be numeric, and in the range of 0..59
			//////
				if (iVariable_isValid(varSecond))
				{
					// They gave us a pSecond
					if (!iVariable_isTypeNumeric(varSecond))
					{
						iError_report(thisCode, (cu8*)"Seconds must be numeric", false);
						return(NULL);
					}
					lst.wSecond = (u16)iiVariable_getAs_s32(thisCode, varSecond, false, &error, &errorNum);
					if (!error && (lst.wSecond < 0 || lst.wSecond > 59))
					{
						iError_reportByNumber(thisCode, _ERROR_OUT_OF_RANGE, iVariable_getRelatedComp(thisCode, varSecond), false);
						return(NULL);
					}
				}


			//////////
			// pMillisecond must be numeric, and in the range of 0..999
			//////
				if (iVariable_isValid(varMillisecond))
				{
					// They gave us a pMillisecond
					if (!iVariable_isTypeNumeric(varMillisecond))
					{
						iError_report(thisCode, (cu8*)"Milliseconds must be numeric", false);
						return(NULL);
					}
					lst.wMilliseconds = (u16)iiVariable_getAs_s32(thisCode, varMillisecond, false, &error, &errorNum);
					if (!error && (lst.wMilliseconds < 0 || lst.wMilliseconds > 999))
					{
						iError_reportByNumber(thisCode, _ERROR_OUT_OF_RANGE, iVariable_getRelatedComp(thisCode, varMillisecond), false);
						return(NULL);
					}
				}


			//////////
			// pNanosecond must be numeric, and in the range of 0..999999999
			//////
				if (tlIsDatetimeX)
				{
					// DatetimeX nanosecond is allowed
					if (iVariable_isValid(varNanosecond))
					{
						// They gave us a pNanosecond
						if (!iVariable_isTypeNumeric(varNanosecond))
						{
							iError_report(thisCode, (cu8*)"Nanoseconds must be numeric", false);
							return(NULL);
						}
						lnMicrosecond = iiVariable_getAs_s32(thisCode, varNanosecond, false, &error, &errorNum);
						if (!error && (lnMicrosecond < 0 || lnMicrosecond > 999999999))
						{
							iError_reportByNumber(thisCode, _ERROR_OUT_OF_RANGE, iVariable_getRelatedComp(thisCode, varNanosecond), false);
							return(NULL);
						}

					} else {
						// Get the current tick count
						lnMicrosecond = iiDateMath_get_currentMicrosecond();
					}

				} else {
					// DatetimeX nanosecond is NOT allowed
					if (iVariable_isValid(varNanosecond))
					{
						iError_reportByNumber(thisCode, _ERROR_TOO_MANY_PARAMETERS, iVariable_getRelatedComp(thisCode, varNanosecond), false);
						return(NULL);
					}
				}
		}


		//////////
		// Convert lst.* into a VJr datetime variable
		//////
			result = iVariable_create(thisCode, ((tlIsDatetimeX) ? _VAR_TYPE_DATETIMEX : _VAR_TYPE_DATETIME), NULL, true);
			if (!result)
			{
				iError_reportByNumber(thisCode, _ERROR_INTERNAL_ERROR, iVariable_getRelatedComp(thisCode, varYear), false);
				return(NULL);
			}

			if (tlIsDatetimeX)
			{
				// DatetimeX
				result->value.data_dtx->jseconds = iiDateMath_get_jseconds_from_YyyyMmDdHhMmSsMssMics(NULL, lst.wYear, lst.wMonth, lst.wDay, lst.wHour, lst.wMinute, lst.wSecond, lst.wMilliseconds, lnMicrosecond);

			} else {
				// Datetime
				result->value.data_dt->julian	= iiDateMath_get_julian_from_YyyyMmDd(&lfJulian, lst.wYear, lst.wMonth, lst.wDay);
				result->value.data_dt->seconds	= iiDateMath_get_seconds_from_HhMmSsMss(lst.wHour, lst.wMinute, lst.wSecond, lst.wMilliseconds);
			}


		//////////
        // Return our converted result
		//////
	        return(result);
	}




//////////
//
// Function: DAY()
// Returns the numeric day of the month for a given Date or DateTime expression.
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
//    DAY( ) returns a number from 1 through 31.
//////
// Example:
//	  dt = datetime()	&& Apr.06.2015
//    ? DAY(dt)		&& Displays 6
//    ? DAY()       && Displays current date's day of month
//////
	SVariable* function_day(SThisCode* thisCode, SReturnsParams* returnsParams)
	{
		SVariable* varParam = returnsParams->params[0];

		// Return day
		return(ifunction_day_month_year_common(thisCode, varParam, _DMY_COMMON_DAY));
	}
	
	// Common date functions used for DAY(), MONTH(), YEAR()
	SVariable* ifunction_day_month_year_common(SThisCode* thisCode, SVariable* varParam, u32 tnFunctionType)
	{
		u32			lnResult, lnYear, lnMonth, lnDay;
		SYSTEMTIME	lst;
		SVariable*	result;


		//////////
		// If Parameter 1 is provided, it must be date or datetime
		//////
// TODO:  Must also support DATETIMEX at some point
			if (varParam)
			{
				if (!iVariable_isValid(varParam) || !(iVariable_isTypeDate(varParam) || iVariable_isTypeDatetime(varParam)))
				{
					iError_reportByNumber(thisCode, _ERROR_INVALID_ARGUMENT_TYPE_COUNT, iVariable_getRelatedComp(thisCode, varParam), false);
					return(NULL);
				}


				//////////
				// Grab year, month, day from datetime or date
				//////
					if (iVariable_isTypeDatetime(varParam))			iiDateMath_get_YyyyMmDd_from_Julian		(varParam->value.data_dt->julian,	&lnYear, &lnMonth, &lnDay);
					else /* date */									iiDateMath_get_YyyyMmDd_from_YYYYMMDD		(varParam->value.data_u8,			&lnYear, &lnMonth, &lnDay);


			} else {
				// Use the current date
				if (_settings)		iTime_getLocalOrSystem(&lst, propGet_settings_TimeLocal(_settings));
				else				GetLocalTime(&lst);
				lnYear	= lst.wYear;
				lnMonth	= lst.wMonth;
				lnDay	= lst.wDay;
			}


		//////////
		// Create output variable
		//////
			switch (tnFunctionType)
			{
				case _DMY_COMMON_DAY:		lnResult = lnDay;		break;
				case _DMY_COMMON_MONTH:		lnResult = lnMonth;		break;
				case _DMY_COMMON_YEAR:		lnResult = lnYear;		break;

				// Should never happen
				default:
					iError_reportByNumber(thisCode, _ERROR_INTERNAL_ERROR, iVariable_getRelatedComp(thisCode, varParam), false);
					return(NULL);
			}


		//////////
		// Create the value
		//////
			result = iVariable_createAndPopulate_byText(thisCode, _VAR_TYPE_U32, (cs8*)&lnResult, sizeof(lnResult), false);
			if (!result)
				iError_reportByNumber(thisCode, _ERROR_INTERNAL_ERROR, iVariable_getRelatedComp(thisCode, varParam), false);


		//////////
		// Return the result
		//////
			return(result);

	}




//////////
//
// Function: DMY()
// Returns a character expression in day-month-year format (for example, 31 May 1998).
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
//    Character - If SET CENTURY is OFF, DMY( ) returns a character string in a dd-Month-yy format (for example, 16 February 98). 
//////
	SVariable* function_dmy(SThisCode* thisCode, SReturnsParams* returnsParams)
	{
		SVariable* varParam = returnsParams->params[0];

		return(ifunction_dtoc_common(thisCode, varParam, _DMY_COMMON_DMY));
	}

	SVariable* ifunction_dtoc_common(SThisCode* thisCode, SVariable* varParam, u32 tnFunctionType)
	{
		u32			lnYear, lnMonth, lnDay;
		s8			lnMonthIdx;
		SYSTEMTIME	lst;
		s8			buffer[64];
		SVariable*	result;


		//////////
		// If provided, parameter 1 must be date or datetime
		//////
			if (varParam)
			{
// TODO:  Must also support DATETIMEX at some point
				if (!iVariable_isValid(varParam) || !(iVariable_isTypeDate(varParam) || iVariable_isTypeDatetime(varParam)))
				{
					iError_reportByNumber(thisCode, _ERROR_INVALID_ARGUMENT_TYPE_COUNT, iVariable_getRelatedComp(thisCode, varParam), false);
					return(NULL);
				}


				//////////
				// Grab year, month, day from datetime or date
				//////
					if (iVariable_isTypeDatetime(varParam))			iiDateMath_get_YyyyMmDd_from_Julian		(varParam->value.data_dt->julian,	&lnYear, &lnMonth, &lnDay);
					else /* date */									iiDateMath_get_YyyyMmDd_from_YYYYMMDD		(varParam->value.data_u8,			&lnYear, &lnMonth, &lnDay);


			} else {
				// Use the current date
				if (_settings)		iTime_getLocalOrSystem(&lst, propGet_settings_TimeLocal(_settings));
				else				GetLocalTime(&lst);
				lnYear	= lst.wYear;
				lnMonth	= lst.wMonth;
				lnDay	= lst.wDay;
			}


		//////////
		// Concatenate string
		//////
			switch(tnFunctionType)
			{
				case _DMY_COMMON_DMY:
				case _DMY_COMMON_MDY:
					lnMonthIdx = max(min(lnMonth, 12), 1) - 1;		// Force into range 1..12, then backoff one for base-0 array reference
					if (_settings && !propGet_settings_Century(_settings))
						// YY
						if (tnFunctionType == _DMY_COMMON_DMY)	sprintf(buffer, "%02u %s %02u\0", lnDay, cgcMonthNames[lnMonthIdx], lnYear % 100);
						else /*MDY*/							sprintf(buffer, "%s %02u, %02u\0", cgcMonthNames[lnMonthIdx], lnDay, lnYear % 100);
					else
						// YYYY
						if (tnFunctionType == _DMY_COMMON_DMY)	sprintf(buffer, "%02u %s %04u\0", lnDay, cgcMonthNames[lnMonthIdx], lnYear);
						else /*MDY*/							sprintf(buffer, "%s %02u, %04u\0", cgcMonthNames[lnMonthIdx], lnDay, lnYear);
				
					break;

				case _DMY_COMMON_DTOS:
					// Date is stored as YYYYMMDD
					iiDateMath_get_YYYYMMDD_from_YyyyMmDd(buffer, lnYear, lnMonth, lnDay);
					break;

				// Should never happen
				default:
					iError_reportByNumber(thisCode, _ERROR_INTERNAL_ERROR, iVariable_getRelatedComp(thisCode, varParam), false);
					return(NULL);
			}
			
		//////////
		// Create our result
		//////
			result = iVariable_createAndPopulate_byText(thisCode, _VAR_TYPE_CHARACTER, (cs8*)buffer, (u32)strlen(buffer), false);
			if (!result)
				iError_reportByNumber(thisCode, _ERROR_INTERNAL_ERROR, NULL, false);


		//////////
		// Indicate our result
		//////
			return(result);

	}

	

//////////
//
// Function: DOW()
// Returns the number day of the week from a given Date or DateTime expression.
// ToDo: receive a second parameter for the first day of the week (from 0 to 7); currently assumes 1 for Sunday.
//
//////
// Version 0.57????????????????????????????????
// Last update:
//     Apr.20.2015
//////
// Change log:
//     Apr.20.2015 - Initial creation by Hernan Cano
//////
// Parameters:
//     p1			-- (optional) Date or DateTime
//     p2 ---TODO-- -- (optional) nFirstDayOfWeek, Numeric from 0 to 7
//
//////
// Returns:
//    DOW() returns the day of the week as a number.
//////
// Example:
//	  dt = datetime()	&& Apr.06.2015
//    ? DOW(dt)		    && Displays 1 (for Monday)
//    ? DOW()           && Displays current date's number day of week
//
//////
	SVariable* function_dow(SThisCode* thisCode, SReturnsParams* returnsParams)
	{
		SVariable* varDateOrDatetime	= returnsParams->params[0];
		SVariable* varFirstDow			= returnsParams->params[1];
		
		u32			lnYear, lnMonth, lnDay;
		s32			lnDow, lnFirstDow;
		SYSTEMTIME	lst;
		SVariable*	result;
		bool		error;
		u32			errorNum;


		//////////
		// If provided, parameter 1 must be date or datetime
		//////
			if (varDateOrDatetime)
			{
// TODO:  Must also support DATETIMEX at some point
				if (!iVariable_isValid(varDateOrDatetime) || !(iVariable_isTypeDate(varDateOrDatetime) || iVariable_isTypeDatetime(varDateOrDatetime)))
				{
					iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_getRelatedComp(thisCode, varDateOrDatetime), false);
					return(NULL);
				}

			//////////
			// Grab year, month, day from datetime or date
			//////
				if iVariable_isTypeDatetime(varDateOrDatetime)		iiDateMath_get_YyyyMmDd_from_Julian  (varDateOrDatetime->value.data_dt->julian, &lnYear, &lnMonth, &lnDay);
				else /* date */										iiDateMath_get_YyyyMmDd_from_YYYYMMDD(varDateOrDatetime->value.data_u8,         &lnYear, &lnMonth, &lnDay);

			} else {
				// Use the current date
				GetLocalTime(&lst);
				lnYear	= lst.wYear;
				lnMonth	= lst.wMonth;
				lnDay	= lst.wDay;
			}


		//////////
		// Grab day of week
		//////
			lnDow = (s32)ifunction_dow_common(lnYear, lnMonth, lnDay);


		//////////
		// Adjust for starting day of week
		//////
			if (varFirstDow)
			{

				//////////
				// We may need to adjust the starting day
				//////
					if (!iVariable_isValid(varFirstDow) || !iVariable_isTypeNumeric(varFirstDow))
					{
						iError_reportByNumber(thisCode, _ERROR_P2_IS_INCORRECT, iVariable_getRelatedComp(thisCode, varFirstDow), false);
						return(NULL);
					}


				//////////
				// Grab the value
				//////
					lnFirstDow = iiVariable_getAs_s32(thisCode, varFirstDow, false, &error, &errorNum);
					if (error)
					{
						iError_reportByNumber(thisCode, errorNum, iVariable_getRelatedComp(thisCode, varFirstDow), false);
						return(NULL);
					}
					if (lnFirstDow < 0 || lnFirstDow > 7)
					{
						iError_reportByNumber(thisCode, _ERROR_P2_IS_INCORRECT, iVariable_getRelatedComp(thisCode, varFirstDow), false);
						return(NULL);
					}


				//////////
				// Adjust by setting
				//////
					if (lnFirstDow == 0)
					{
						// Use regional settings
// TODO:  Regional settings, for now we'll just use the default
						lnFirstDow = 1;
					}

					// Adjust forward, and wrap around if need be
					if (lnFirstDow != 1)
					{
						// Subtract off the starting day of week
						lnDow -= (lnFirstDow - 1);

						// If we're negative, bring positive again
						if (lnDow < 0)
							lnDow += 7;
					}

			}


		//////////
		// Adjust base-0 to base-1
		//////
			++lnDow;


		//////////
		// Create and populate our output variable
		//////
			result = iVariable_createAndPopulate_byText(thisCode, _VAR_TYPE_U32, (cs8*)&lnDow, 4, false);
			if (!result)
				iError_reportByNumber(thisCode, _ERROR_INTERNAL_ERROR, iVariable_getRelatedComp(thisCode, varDateOrDatetime), false);


		//////////
		// Indicate our result
		//////
			return(result);

	}




//////////
//
// Function: DTOC()
// Returns a Character-type date from a Date or DateTime expression.
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
//	   p2			-- If 1 returns the date in a format suitable for indexing
//
//////
// Returns:
//    DTOC( ) returns a character string corresponding to a Date or DateTime expression.
//	  The date format is determined by SET CENTURY and SET DATE. 
//
//////
	SVariable* function_dtoc(SThisCode* thisCode, SReturnsParams* returnsParams)
	{
		SVariable* varParam	= returnsParams->params[0];
		SVariable* varFlag	= returnsParams->params[1];

		s32			lnFlag;
		u32			lnYear, lnMonth, lnDay;
		SYSTEMTIME	lst;
		s8			buffer[16];
		SVariable*	varTempDate;
		SVariable*	result;
		bool		error;
		u32			errorNum;


		//////////
		// Parameter 2 must be numeric
		//////
			if (varFlag)
			{
				if (!iVariable_isValid(varFlag) || !iVariable_isTypeNumeric(varFlag))
				{
					iError_reportByNumber(thisCode, _ERROR_P2_IS_INCORRECT, iVariable_getRelatedComp(thisCode, varFlag), false);
					return(NULL);
				}

				// Grab the flag
				lnFlag = iiVariable_getAs_s32(thisCode, varFlag, false, &error, &errorNum);
				if (error)
				{
					// An error extracting the value (should never happen)
					iError_reportByNumber(thisCode, errorNum, iVariable_getRelatedComp(thisCode, varFlag), false);
					return(NULL);
				}		

				// DTOC(--, 1) is DTOS(--)
				if (lnFlag == 1)
					return(ifunction_dtoc_common(thisCode, varParam, _DMY_COMMON_DTOS));

				// If we get here, invalid parameter specified
				iError_reportByNumber(thisCode, _ERROR_INVALID_ARGUMENT_TYPE_COUNT, iVariable_getRelatedComp(thisCode, varFlag), false);
				return(NULL);
			}


		//////////
		// Parameter 1 must be date or datetime
		//////			
			if (varParam)
			{
// TODO:  Must also support DATETIMEX at some point
				if (!iVariable_isValid(varParam) || !(iVariable_isTypeDate(varParam) || iVariable_isTypeDatetime(varParam)))
				{
					iError_reportByNumber(thisCode, _ERROR_INVALID_ARGUMENT_TYPE_COUNT, iVariable_getRelatedComp(thisCode, varParam), false);
					return(NULL);
				}

				// If date we finished
				if (iVariable_isTypeDate(varParam))
					return(iVariable_convertForDisplay(thisCode, varParam));
				

				//////////
				// Grab year, month, day from datetime
				//////
					iiDateMath_get_YyyyMmDd_from_Julian (varParam->value.data_dt->julian,	&lnYear, &lnMonth, &lnDay);


			} else {
				// Use the current date
				if (_settings)		iTime_getLocalOrSystem(&lst, propGet_settings_TimeLocal(_settings));
				else				GetLocalTime(&lst);
				lnYear	= lst.wYear;
				lnMonth	= lst.wMonth;
				lnDay	= lst.wDay;
			}
		

		//////////
		// Convert datetime or lst.* into a VJr date variable
		//////
			// Date is stored as YYYYMMDD
			iiDateMath_get_YYYYMMDD_from_YyyyMmDd(buffer, lnYear, lnMonth, lnDay);
			varTempDate = iVariable_createAndPopulate_byText(thisCode, _VAR_TYPE_DATE, buffer, 8, false);
			if (!varTempDate)
			{
				// Fatal error
				iError_reportByNumber(thisCode, _ERROR_INTERNAL_ERROR, NULL, false);
				return(NULL);
			}


		//////////
		// Create and populate the return variable
		//////
			result = iVariable_convertForDisplay(thisCode, varTempDate);
			if (!result)
				iError_reportByNumber(thisCode, _ERROR_INTERNAL_ERROR, iVariable_getRelatedComp(thisCode, varParam), false);


		//////////
		// Clean house
		//////
			iVariable_delete(thisCode, varTempDate, true);


		//////////
		// Signify our result
		//////
			return(result);

	}




//////////
//
// Function: DTOR()
// Converts degrees to radians.
//
//////
// Version 0.56
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
//    DTOR(n) of the value in p1
//////
// Example:
//    ? DTOR(180)		&& Display 3.14
//////
    SVariable* function_dtor(SThisCode* thisCode, SReturnsParams* returnsParams)
    {
		SVariable* varNumber = returnsParams->params[0];


		// Return dtor
		return(ifunction_numbers_common(thisCode, varNumber, NULL, NULL, _FP_COMMON_DTOR, _VAR_TYPE_F64, false, false, returnsParams));
	}




//////////
//
// Function: DTOS()
// Returns a character-string date in a yyyymmdd format from a specified Date or DateTime expression.
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
//    Character - This function is useful for indexing tables on a Date or DateTime field.
//	  It is equivalent to DTOC( ) when its optional 1 argument is included. 
//
//////
	SVariable* function_dtos(SThisCode* thisCode, SReturnsParams* returnsParams)
	{
		SVariable* varParam = returnsParams->params[0];


		// Return dtos
		return(ifunction_dtoc_common(thisCode, varParam, _DMY_COMMON_DTOS));
	}




//////////
//
// Function: DTOT()
// Returns a DateTime value from a Date expression.
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
//     p1			-- Date
//     p2			-- (Optional) Fractional number of seconds to use for the time (0.0 to 86400.0)
//
//////
// Returns:
//    Datetime	-- DTOT( ) adds a default time of 12:00:00 AM (if SET HOURS is 12) or 00:00:00 (if SET HOURS is 24) to the date to produce a valid DateTime value.
//                 If the second parameter is provided and is valid, it will override the default midnight time.
//////
	SVariable* function_dtot(SThisCode* thisCode, SReturnsParams* returnsParams)
	{
		SVariable* varParam	= returnsParams->params[0];
		SVariable* varFlag	= returnsParams->params[1];

		u32			lnYear, lnMonth, lnDay;
		f32			lfJulian, lfSeconds;
		SVariable*	result;
		bool		error;
		u32			errorNum;


		//////////
		// Parameter 1 must be date
		//////
			if (!iVariable_isValid(varParam) || !iVariable_isTypeDate(varParam))
			{
				iError_reportByNumber(thisCode, _ERROR_INVALID_ARGUMENT_TYPE_COUNT, iVariable_getRelatedComp(thisCode, varParam), false);
				return(NULL);
			}


		//////////
		// If Parameter 2 provided, it must be numeric
		//////
			if (varFlag)
			{
				// Is it numeric?
				if (!iVariable_isValid(varFlag) || !iVariable_isTypeNumeric(varFlag))
				{
					iError_reportByNumber(thisCode, _ERROR_P2_IS_INCORRECT, iVariable_getRelatedComp(thisCode, varFlag), false);
					return(NULL);
				}

				// Grab it as a float
				lfSeconds = iiVariable_getAs_f32(thisCode, varFlag, false, &error, &errorNum);
				if (error)
				{
					iError_reportByNumber(thisCode, errorNum, iVariable_getRelatedComp(thisCode, varFlag), false);
					return(NULL);
				}

				// Is it in range?
				if (lfSeconds < 0.0f || lfSeconds > 24*60*60)
				{
					iError_reportByNumber(thisCode, _ERROR_OUT_OF_RANGE, iVariable_getRelatedComp(thisCode, varFlag), false);
					return(NULL);
				}
				// Right now, lfSeconds is the seconds to inject


			} else {
				// Initialize to 0.0f, which is midnight
				lfSeconds = 0.0f;
			}


		//////////
		// Grab year, month, day from date
		//////
			iiDateMath_get_YyyyMmDd_from_YYYYMMDD(varParam->value.data_u8, &lnYear, &lnMonth, &lnDay);


		//////////
		// Convert date into a VJr datetime variable
		//////
			result = iVariable_create(thisCode, _VAR_TYPE_DATETIME, NULL, true);
			if (!result)
			{
				// Unable to create the variable
				iError_report(thisCode, cgcInternalError, false);

			} else {
				result->value.data_dt->julian	= iiDateMath_get_julian_from_YyyyMmDd(&lfJulian, lnYear, lnMonth, lnDay);
				result->value.data_dt->seconds	= lfSeconds;
			}


		//////////
        // Return our converted result
		//////
	        return(result);

	}




//////////
//
// Function: DTRANSFROM()
//  It takes an input formatting string and one or more dates or datetimes and 
//	creates an output character string which prepares date information as indicated, 
//	interspersed with other text.
//
//		**********
//		* Long forms
//		*****
//			%D  Day                   02
//			%B  Month                 04
//			%Y  Year                  2015
//			%H  Hour                  14      02 If %P is in string
//			%M  Minute                05
//			%S  Second                55
//			%N  Milliseconds          020
//			%P  AM/PM                 PM
//			%J  Julian                2457115
//			%A  Day of week           Thursday
//			%O  Month                 April
//			%T  Timestamp			  20150402140555
//
//			%-	Date mark			  SET("MARK")
//			%%						  %
//
//		**********
//		* Short forms
//		*****
//			%d  day                   2
//			%b  month                 4
//			%y  year                  15
//			%h  hour                  14      2 If %P is in string
//			%m  minute                5
//			%s  second                55
//			%p  am/pm                 pm
//			%j  Day of year           92
//			%a  Day of week           Thu
//			%o  Month                 Apr
//			%t  Timestamp			  20150402
//////
// Version 0.57
// Last update:
//     Apr.16.2015
//////
// Change log:
//     Apr.16.2015 - Initial creation by Stefano D'Amico
//////
// Parameters:
//     p1	-- Specifies the formatting string.
//     p2	-- Specifies the first date/datetime.
//	   ..
//     p26	-- Specifies the last date/datetime.
//
//////
// Returns:
//    Formatted string.
//////
	SVariable* function_dtransform(SThisCode* thisCode, SReturnsParams* returnsParams)
	{
		SVariable* varFormatStr = returnsParams->params[0];

		s32			lnI, lnResultLength;
		s8*			lcResult;
		SVariable*	param;
		SVariable*	result;


		//////////
		// Parameters 1 must be present and character
		//////
			if (!iVariable_isValid(varFormatStr) || !iVariable_isTypeCharacter(varFormatStr))
			{
				iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_getRelatedComp(thisCode, varFormatStr), false);
				return(NULL);
			}


		//////////
		// All parameter 2 and later must be date/datetime type, and are translated locally into datetime types
		//////
			for (lnI = 1; lnI < returnsParams->pcount; lnI++)
			{

				//////////
				// Make sure this variable type matches the test value
				//////
					param = returnsParams->params[lnI];
					if (!iVariable_isValid(param) || !(iVariable_isTypeDate(param) || iVariable_isTypeDatetime(param)))
					{
						// The types do not match
						iError_reportByNumber(thisCode, _ERROR_DATA_TYPE_MISMATCH, iVariable_getRelatedComp(thisCode, param), false);
						return(NULL);
					}

			}


		//////////
		// Call the common function
		//////
			lcResult		= NULL;
			lnResultLength	= ifunction_dtransform_textmerge_common(thisCode, &lcResult, varFormatStr->value.data_cs8, varFormatStr->value.length, NULL, NULL, &returnsParams->params[1], true, true);


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

	s32 iifunction_append_text(s8* tcDst, s8* tcSrc, s32 tnLength)
	{
		// Fixup length (if need be)
		if (tnLength < 0)
			tnLength = strlen(tcSrc);

		// Copy
		memcpy(tcDst, tcSrc, tnLength);

		// Indicate our length
		return(tnLength);
	}

	// Valid types are %-DdBbYyIiHhMmSsNTtJjPpAaOoL
	//
	// %%	-- % symbol
	// %<	-- < symbol (allows overriding textmerge)
	// %-	-- Current SET("MARK") symbol, typically one of [.-/].
	// %D	-- Day of month 02
	// %d	-- Day of month 2
	// %B	-- Month of year 02
	// %b	-- Month of year 2
	// %Y	-- Year 2015
	// %y	-- Year 15
	// %I	-- Hour 02
	// %H	-- Hour 14
	// %i	-- Hour 2
	// %h	-- Hour 14
	// %M	-- Minute 02
	// %m	-- Minute 2
	// %S	-- Seconds 02
	// %s	-- Seconds 2
	// %N	-- Milliseconds 002
	// %T	-- YYYYMMDDHhMmSs
	// %t	-- YYYYMMDD
	// %J	-- Julian day number
	// %j	-- Day number into year
	// %P	-- AM or PM
	// %p	-- am or pm
	// %A	-- Day of week Monday, Tuesday, etc...
	// %a	-- Day of week Mon, Tue, etc...
	// %O	-- Day of month January, February, etc...
	// %o	-- Day of month Jan, Feb, etc...
	// %L	-- Local or System time based on SET("TIME") setting
	//
	u32 ifunction_dtransform_textmerge_common(SThisCode* thisCode, s8** tcResult, cs8* tcFormatStr, s32 tnFormatStrLength, SDatum* leftTextmergeDelim, SDatum* rightTextmergeDelim, SVariable* varDatesOrDatetimes[9], bool tlDateCodes, bool tlTextMerge)
	{
		s8				c, cMark;
		s32				lnI, lnJ, lnPass, lnAllocationLength, lnOffset, lnMillisecond, lnNanosecond;
		u32				lnYear, lnMonth, lnDay, lnHour, lnMinute, lnSecond, lnJulian;
		f32				lfJulian;
		bool			llLocalTime, llManufactured, llProcessed;
		s8*				lcPtr;
		s8*				lcResult;
		SDatum			leftDelim;
		SDatum			rightDelim;
		SVariable*		varTextmerge;
		SVariable*		varDisplay;
		SVariable*		varMark;
		SVariable*		var;
		SYSTEMTIME*		dt;
		SYSTEMTIME		dtInfo[9];
		SYSTEMTIME		dtFill;
		s8				buffer[64];


		//////////
		// Prepare datetime info for dtransform()
		//////
			if (tlDateCodes)
			{
				for (lnI = 0; varDatesOrDatetimes[lnI] && lnI < 9; lnI++)
				{

					//////////
					// Grab year, month, day, time from date/datetime
					//////
						var = varDatesOrDatetimes[lnI];
						if (!iVariable_isValid(var))
						{
							// Invalid variable type

						} else if (iVariable_isTypeDatetime(var)) {
							// Datetime
							iiDateMath_get_YyyyMmDd_from_Julian	(var->value.data_dt->julian,	&lnYear, &lnMonth,  &lnDay);
							iiDateMath_get_HhMmSsMss_from_seconds(var->value.data_dt->seconds,  &lnHour, &lnMinute, &lnSecond, &lnMillisecond);

						} else if (iVariable_isTypeDatetimeX(var)) {
							// Date
							iiDateMath_get_YyyyMmDdHhMmSsMssNss_from_DatetimeX(var->value.data_dtx->jseconds, NULL, &lnYear, &lnMonth, &lnDay, &lnHour, &lnMinute, &lnSecond, &lnMillisecond, &lnNanosecond);

							// 00:00:00.000
							lnHour = lnMinute = lnSecond = lnMillisecond = 0;

						} else if (iVariable_isTypeDate(var)) {
							// Date
							iiDateMath_get_YyyyMmDd_from_YYYYMMDD (var->value.data_u8, &lnYear, &lnMonth, &lnDay);

							// 00:00:00.000
							lnHour = lnMinute = lnSecond = lnMillisecond = 0;

						} else {
							// Something else
							iError_reportByNumber(thisCode, _ERROR_DATA_TYPE_MISMATCH, iVariable_getRelatedComp(thisCode, var), false);
							return(NULL);
						}


					//////////
					// Store formally
					//////
						dtInfo[lnI].wYear			= lnYear;
						dtInfo[lnI].wMonth			= lnMonth;
						dtInfo[lnI].wDay			= lnDay;
						dtInfo[lnI].wHour			= lnHour;
						dtInfo[lnI].wMinute			= lnMinute;
						dtInfo[lnI].wSecond			= lnSecond;
						dtInfo[lnI].wMilliseconds	= lnMillisecond;
						dtInfo[lnI].wDayOfWeek		= ifunction_dow_common(lnYear, lnMonth, lnDay);
				}


			//////////
			// Fill out the rest of the parameters with the current date and time
			//////
				llLocalTime = propGet_settings_TimeLocal(_settings);
				if (llLocalTime)		GetLocalTime(&dtFill);
				else					GetSystemTime(&dtFill);

				// Every other date detaults to current date and time
				for ( ; lnI < 9; lnI++)
					memcpy(&dtInfo[lnI], &dtFill, sizeof(dtFill));

			}


		//////////
		// Fill in missing delimiters
		//////
			if (!leftTextmergeDelim)
			{
				leftDelim.data_cs8		= &cgc_textmerge_leftDelim[0];
				leftDelim.length		= sizeof(cgc_textmerge_leftDelim) - 1;
				leftTextmergeDelim		= &leftDelim;
			}

			if (!rightTextmergeDelim)
			{
				rightDelim.data_cs8		= &cgc_textmerge_rightDelim[0];
				rightDelim.length		= sizeof(cgc_textmerge_rightDelim) - 1;
				rightTextmergeDelim		= &rightDelim;
			}


		//////////
		// Grab the SET("MARK") character
		//////
			// Note:  varMark is a reference to the actual _settings.mark value
			varMark = propGet_settings_Mark(_settings);
			if (!varMark || !iVariable_isTypeCharacter(varMark) || !varMark->value.data || varMark->value.length <= 0)
			{
				// Fall back on current date type
				switch (propGet_settings_Date(_settings))
				{
					case _SET_DATE_USA:			// mm-dd-yy
					case _SET_DATE_ITALIAN:		// dd-mm-yy
						// Hyphen
						cMark = '-';
						break;

					case _SET_DATE_GERMAN:		// dd.mm.yy
					case _SET_DATE_ANSI:		// yy.mm.dd
						// Period
						cMark = '.';
						break;

					default:
// 					case _SET_DATE_AMERICAN:	// mm/dd/yy
// 					case _SET_DATE_BRITISH:		// dd/mm/yy
// 					case _SET_DATE_FRENCH:		// dd/mm/yy
// 					case _SET_DATE_JAPAN:		// yy/mm/dd
// 					case _SET_DATE_TAIWAN:		// yy/mm/dd
// 					case _SET_DATE_SHORT:		// m/d/yy
// 					case _SET_DATE_DMY:			// dd/mm/yy
// 					case _SET_DATE_MDY:			// mm/dd/yy
// 					case _SET_DATE_YMD:			// yy/mm/dd
						cMark = '/';
						break;
				}

		} else {
			// Grab the character they've set
			cMark = varMark->value.data[0];
		}


		/////////
		// Parser format string twice
		//////
			for (lnPass = 1; lnPass < 3; lnPass++)
			{

				//////////
				// Initialize this pass
				//////
					if (lnPass == 1)
					{
						// Compute allocation length
						lnAllocationLength = 0;

					} else {
						// Physically store the data
						lcResult = (s8*)malloc(lnAllocationLength + 1);
						if (!lcResult)
						{
							iError_reportByNumber(thisCode, _ERROR_INTERNAL_ERROR, NULL, false);
							*tcResult = NULL;
							return(NULL);
						}

						// Store the allocated pointer
						*tcResult = lcResult;

						// Prepare for storage
						lcResult[lnAllocationLength]	= 0;
						lnOffset						= 0;
					}


				//////////
				// Iterate through our format string, and expand out based on length
				//////
					for (lnI = 0; tcFormatStr[lnI] && lnI < tnFormatStrLength; )
					{

						//////////
						// Grab char
						//////
							c = tcFormatStr[lnI];


						/////////
						// Examine the character:
						//////
							if (tlDateCodes && c == '%')
							{
								/////////
								// Examine the character after %:
								//////
									c = tcFormatStr[lnI + 1];
									if (c >= '0' && c <= '9')
									{
										// %#
										dt	= &dtInfo[(s32)(c - '0') - 1];
										c	= tcFormatStr[lnI++];
										lnI	+= 2;

									} else {
										// %x
										dt	= &dtInfo[0];
										++lnI;
									}


									/////////
									// Examine the character encoded
									//////
										switch (c)
										{
											case '<':
											case '%':
												// %
												if (lnPass == 1)
												{
													// Increase our length
													++lnAllocationLength;

												} else {
													lcResult[lnOffset] = c;
													++lnOffset;
												}
												break;

											case '-':
												// Set Mark
												if (lnPass == 1)
												{
													// Increase our length
													++lnAllocationLength;

												} else {
													// Store
													lcResult[lnOffset] = cMark;
													++lnOffset;
												}
												break;

											case 'D':
												// Day 02
												if (lnPass == 1)
												{
													// Increase our length
													lnAllocationLength += 2;

												} else {
													// Compute and store
													sprintf(buffer, "%02u", dt->wDay);
													lnOffset += iifunction_append_text(lcResult + lnOffset, buffer, 2);
												}
												break;

											case 'd':
												// Day 2
												sprintf(buffer, "%u\0", dt->wDay);
												if (lnPass == 1)		lnAllocationLength	+= strlen(buffer);
												else					lnOffset			+= iifunction_append_text(lcResult + lnOffset, buffer, -1);
												break;

											case 'B':	// Month 04
												if (lnPass == 1)
												{
													// Increase our length
													lnAllocationLength += 2;

												} else {
													// Compute and store
													sprintf(buffer, "%02u", dt->wMonth);
													lnOffset += iifunction_append_text(lcResult + lnOffset, buffer, 2);
												}
												break;

											case 'b':	// Month 4
												sprintf(buffer, "%u\0", dt->wMonth);
												if (lnPass == 1)		lnAllocationLength	+= strlen(buffer);
												else					lnOffset			+= iifunction_append_text(lcResult + lnOffset, buffer, -1);
												break;

											case 'Y':	// Year 2015
												if (lnPass == 1)
												{
													// Increase our length
													lnAllocationLength += 4;

												} else {
													// Compute and store
													sprintf(buffer, "%04u", dt->wYear);
													lnOffset += iifunction_append_text(lcResult + lnOffset, buffer, 4);
												}
												break;

											case 'y':	// Year 15
												if (lnPass == 1)
												{
													// Increase our length
													lnAllocationLength += 2;

												} else {
													// Compute and store
													sprintf(buffer, "%02u", (dt->wYear % 100));
													lnOffset += iifunction_append_text(lcResult + lnOffset, buffer, 2);
												}
												break;

											case 'I':	// Hour 02
											case 'H':	// Hour 14
												sprintf(buffer, "%02u\0", iTime_adjustHour_toAMPM(dt->wHour, (c == 'I')));
												if (lnPass == 1)		lnAllocationLength	+= strlen(buffer);
												else					lnOffset			+= iifunction_append_text(lcResult + lnOffset, buffer, -1);
												break;

											case 'i':	// Hour 2
											case 'h':	// Hour 14
												sprintf(buffer, "%u\0", iTime_adjustHour_toAMPM(dt->wHour, (c == 'i')));
												if (lnPass == 1)		lnAllocationLength	+= strlen(buffer);
												else					lnOffset			+= iifunction_append_text(lcResult + lnOffset, buffer, -1);
												break;

											case 'M':
												// Minute 05
												if (lnPass == 1)
												{
													// Increase our length
													lnAllocationLength += 2;

												} else {
													// Compute and store
													sprintf(buffer, "%02u", dt->wMinute);
													lnOffset += iifunction_append_text(lcResult + lnOffset, buffer, 2);
												}
												break;

											case 'm':
												// Minute 5
												sprintf(buffer, "%u\0", dt->wMinute);
												if (lnPass == 1)		lnAllocationLength	+= strlen(buffer);
												else					lnOffset			+= iifunction_append_text(lcResult + lnOffset, buffer, -1);
												break;

											case 'S':
												// Seconds 09
												if (lnPass == 1)
												{
													// Increase our length
													lnAllocationLength += 2;

												} else {
													// Compute and store
													sprintf(buffer, "%02u", dt->wSecond);
													lnOffset += iifunction_append_text(lcResult + lnOffset, buffer, 2);
												}
												break;

											case 's':
												// Seconds 9
												sprintf(buffer, "%u\0", dt->wSecond);
												if (lnPass == 1)		lnAllocationLength	+= strlen(buffer);
												else					lnOffset			+= iifunction_append_text(lcResult + lnOffset, buffer, -1);
												break;

											case 'N':
												// Milliseconds 025
												if (lnPass == 1)
												{
													// Increase our length
													lnAllocationLength += 3;

												} else {
													// Compute and store
													sprintf(buffer, "%03u", dt->wMilliseconds);
													lnOffset += iifunction_append_text(lcResult + lnOffset, buffer, 3);
												}
												break;

											case 'T':
												// YYYYMMDDHhMmSs
												if (lnPass == 1)
												{
													// Increase our length
													lnAllocationLength += 14;

												} else {
													// Compute and store
													sprintf(buffer, "%04u%02u%02u%02u%02u%02u", dt->wYear, dt->wMonth, dt->wDay, dt->wHour, dt->wMinute, dt->wSecond);
													lnOffset += iifunction_append_text(lcResult + lnOffset, buffer, 14);
												}
												break;

											case 't':
												// YYYYMMDD
												if (lnPass == 1)
												{
													// Increase our length
													lnAllocationLength += 8;

												} else {
													// Compute and store
													sprintf(buffer, "%04u%02u%02u", dt->wYear, dt->wMonth, dt->wDay);
													lnOffset += iifunction_append_text(lcResult + lnOffset, buffer, 8);
												}
												break;

											case 'J':
												// Julian day number
												lnJulian = (u32)iiDateMath_get_julian_from_YyyyMmDd(&lfJulian, dt->wYear, dt->wMonth, dt->wDay);
												sprintf(buffer, "%u", lnJulian);
												if (lnPass == 1)		lnAllocationLength	+= strlen(buffer);
												else					lnOffset			+= iifunction_append_text(lcResult + lnOffset, buffer, -1);
												break;

											case 'j':
												// Day number into year
												sprintf(buffer, "%u\0", iDateMath_getDayNumberIntoYear(dt->wYear, dt->wMonth, dt->wDay));
												if (lnPass == 1)		lnAllocationLength	+= strlen(buffer);
												else					lnOffset			+= iifunction_append_text(lcResult + lnOffset, buffer, -1);
												break;

											case 'P':
												// AM-PM
												if (lnPass == 1)
												{
													// Increase our length
													lnAllocationLength	+= 2;

												} else {
													// Compute and store
													lcPtr		= (s8*)iTime_amOrPm(dt->wHour, cgc_am_uppercase, cgc_pm_uppercase);
													lnOffset	+= iifunction_append_text(lcResult + lnOffset, lcPtr, 2);
												}
												break;

											case 'p':
												// am-pm
												if (lnPass == 1)
												{
													// Increase our length
													lnAllocationLength	+= 2;

												} else {
													// Compute and store
													lcPtr		= (s8*)iTime_amOrPm(dt->wHour, cgc_am_lowercase, cgc_pm_lowercase);
													lnOffset	+= iifunction_append_text(lcResult + lnOffset, lcPtr, 2);
												}
												break;

											case 'A':	// Day of week
												if (lnPass == 1)		lnAllocationLength	+= strlen(cgcDayOfWeekNames[dt->wDayOfWeek]);
												else					lnOffset			+= iifunction_append_text(lcResult + lnOffset, cgcDayOfWeekNames[dt->wDayOfWeek], -1);
												break;

											case 'a':	// Day of week short
												if (lnPass == 1)		lnAllocationLength	+= 3;
												else					lnOffset			+= iifunction_append_text(lcResult + lnOffset, cgcDayOfWeekNamesShort[dt->wDayOfWeek], 3);
												break;

											case 'O':	// Cmonth
												if (lnPass == 1)		lnAllocationLength	+= strlen(cgcMonthNames[dt->wMonth - 1]);
												else					lnOffset			+= iifunction_append_text(lcResult + lnOffset, cgcMonthNames[dt->wMonth - 1], -1);
												break;

											case 'o':	// Cmonth short
												if (lnPass == 1)		lnAllocationLength	+= 3;
												else					lnOffset			+= iifunction_append_text(lcResult + lnOffset, cgcMonthNamesShort[dt->wMonth - 1], 3);
												break;

											case 'L':
												// Local-System (current SET("TIME") setting)
												if (lnPass == 1)
												{
													// Increase our length
													lnAllocationLength	+= ((llLocalTime) ? sizeof(cgc_local) - 1 : sizeof(cgc_system) - 1);

												} else {
													// Compute and store
													lcPtr		= (s8*)((llLocalTime) ? cgc_local : cgc_system);
													lnOffset	+= iifunction_append_text(lcResult + lnOffset, lcPtr, -1);
												}
												break;

											default:	// Copy a question mark
												if (lnPass == 1)
												{
													// Increase our length
													++lnAllocationLength;

												} else {
													// Store
													lcResult[lnOffset] = '?';
													++lnOffset;
												}
										}

							} else if (tlTextMerge && lnI + leftTextmergeDelim->length <= tnFormatStrLength && iDatum_compare(leftTextmergeDelim, tcFormatStr + lnI, leftTextmergeDelim->length) == 0) {
								// It's the start of a text merge
								// Search forward for the closing tag and extract the content out between
								for (lnJ = lnI + leftTextmergeDelim->length, varTextmerge = NULL; lnJ <= tnFormatStrLength - rightTextmergeDelim->length; lnJ++)
								{
									// Is it the right delimiter?
									if (iDatum_compare(rightTextmergeDelim, tcFormatStr + lnJ, rightTextmergeDelim->length) == 0)
									{
										// We've found the range
										varTextmerge = iEngine_get_variableName_fromText(thisCode, tcFormatStr + lnI + leftTextmergeDelim->length, lnJ - lnI - rightTextmergeDelim->length, NULL, &llManufactured);
										break;
									}
								}

								// Did we find it?
								llProcessed = false;
								if (varTextmerge)
								{
									// Yes
									lnI = lnJ + rightTextmergeDelim->length;

									// Convert it for display
									varDisplay = iVariable_convertForDisplay(thisCode, varTextmerge);

									// Clean house
									if (llManufactured)
										iVariable_delete(thisCode, varTextmerge, true);

									if (varDisplay)
									{
										// Perform the operation
										llProcessed = true;
										if (lnPass == 1)
										{
											// Increase our length
											lnAllocationLength += varDisplay->value.length;

										} else {
											// Store
											lnOffset += iifunction_append_text(lcResult + lnOffset, varDisplay->value.data, varDisplay->value.length);
										}

										// Delete the variable
										iVariable_delete(thisCode, varDisplay, true);
									}
								}

								// If we haven't processed it yet, just copy it over
								if (!llProcessed)
								{
									// Copy over directly
									if (lnPass == 1)
									{
										// Increase our length
										++lnAllocationLength;

									} else {
										// Store
										lcResult[lnOffset] = c;
										++lnOffset;
									}

									// Move past this character
									++lnI;
								}

							} else {
								// Copy over directly
								if (lnPass == 1)
								{
									// Increase our length
									++lnAllocationLength;

								} else {
									// Store
									lcResult[lnOffset] = c;
									++lnOffset;
								}

								// Move past this character
								++lnI;
							}

					}

			}


		///////////
		// Return length buffer
		/////
			return(lnAllocationLength);

	}
