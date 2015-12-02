//////////
//
// /libsf/source/vjr/commands/funcs/w.cpp
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
// Function: WEEK()
// Returns a number representing the week of the year from a Date or DateTime expression.
//
//////
// Version 0.58
// Last update:
//     May.01.2015
//////
// Change log:
//     May.01.2015 - Initial creation by Stefano D'Amico
//////
// Parameters:
//     p1			-- Date or DateTime
//     p2			-- Numeric [nMinDaysOfWeek] Minimum number of days in first week of year (1..7)
//     p3			-- Numeric [nFirstDayOfWeek] 
//
//////
// Returns:
//    WEEK() returns a number representing the week of the year.
//////
// Example:
//	  dt = datetime()	&& May.01.2015
//    ? WEEK(dt)		&& Displays 18
//////
	void function_week(SReturnsParams* rpar)
	{
		SVariable*	varParam			= rpar->ip[0];
		SVariable*	varFirstWeek		= rpar->ip[1];
		SVariable*	varFirstDayOfWeek	= rpar->ip[2];

		u32			lnYear, lnMonth, lnDay;
		s32			lnWeek, lnMinDaysInWeek, lnFirstDayOfWeek;
		SYSTEMTIME	lst;
		bool		error;
		u32			errorNum;
		SVariable*	result;


		//////////
		// If provided, parameter 1 must be date or datetime
		//////
			rpar->rp[0] = NULL;
			if (varParam)
			{
				if (!iVariable_isValid(varParam) || !(iVariable_isTypeDate(varParam) || iVariable_isTypeDatetime(varParam) || iVariable_isTypeDatetimeX(varParam)))
				{
					iError_report_byNumber(_ERROR_INVALID_ARGUMENT_TYPE_COUNT, iVariable_get_relatedComp(varParam), false);
					return;
				}

			//////////
			// Grab year, month, day from datetime or date
			//////
				     if (iVariable_isTypeDatetime(varParam))		iiDateMath_get_YyyyMmDd_from_julian					(varParam->value.data_dt->julian,			&lnYear, &lnMonth, &lnDay);
				else if (iVariable_isTypeDatetimeX(varParam))		iiDateMath_get_YyyyMmDdHhMmSsMssNss_from_jseconds	(varParam->value.data_dtx->jseconds, NULL,	&lnYear, &lnMonth, &lnDay, NULL, NULL, NULL, NULL, NULL);
				else /* date */										iiDateMath_get_YyyyMmDd_from_YYYYMMDD				(varParam->value.data_u8,					&lnYear, &lnMonth, &lnDay);

			} else {
				// Use the current date
				if (_settings)		iTime_getLocalOrSystem(&lst, propGet_settings_TimeLocal(_settings));
				else				GetLocalTime(&lst);

				lnYear	= lst.wYear;
				lnMonth	= lst.wMonth;
				lnDay	= lst.wDay;
			}


		//////////
		// Parameter 2 must be numeric
		//////
			if (varFirstWeek)
			{
				if (!iVariable_isValid(varFirstWeek) || !iVariable_isTypeNumeric(varFirstWeek))
				{
					iError_report_byNumber(_ERROR_P2_IS_INCORRECT, iVariable_get_relatedComp(varFirstWeek), false);
					return;
				}

				// Grab the minimum number of days in week
				lnMinDaysInWeek = iiVariable_getAs_s32(varFirstWeek, false, &error, &errorNum);
				if (error)
				{
					// An error extracting the value (should never happen)
					iError_report_byNumber(errorNum, iVariable_get_relatedComp(varFirstWeek), false);
					return;
				}

				if (lnMinDaysInWeek < 1 || 7 < lnMinDaysInWeek)
				{
					iError_report_byNumber(_ERROR_OUT_OF_RANGE, iVariable_get_relatedComp(varFirstWeek), false);
					return;				
				}

			} else {
				// First week contains January 1st.
				lnMinDaysInWeek = 1;
			}


		//////////
		// Parameter 3 must be numeric
		//////
			if (varFirstDayOfWeek)
			{
				if (!iVariable_isValid(varFirstDayOfWeek) || !iVariable_isTypeNumeric(varFirstDayOfWeek))
				{
					iError_report_byNumber(_ERROR_P3_IS_INCORRECT, iVariable_get_relatedComp(varFirstDayOfWeek), false);
					return;
				}

				// Grab the first day of week
				lnFirstDayOfWeek = iiVariable_getAs_s32(varFirstDayOfWeek, false, &error, &errorNum);
				if (error)
				{
					// An error extracting the value (should never happen)
					iError_report_byNumber(errorNum, iVariable_get_relatedComp(varFirstDayOfWeek), false);
					return;
				}

				if (lnFirstDayOfWeek < 0 || 6 < lnFirstDayOfWeek)
				{
					iError_report_byNumber(_ERROR_OUT_OF_RANGE, iVariable_get_relatedComp(varFirstWeek), false);
					return;				
				}

			} else {
				// Sunday
				lnFirstDayOfWeek = 0;
			}


		/////////
		// Grab week
		//////
			lnWeek = ifunction_week_common(rpar, lnYear, lnMonth, lnDay, lnMinDaysInWeek, lnFirstDayOfWeek);


		//////////
		// Create and populate our output variable
		//////
			result = iVariable_createAndPopulate_byText(_VAR_TYPE_S32, (cs8*)&lnWeek, 4, false);
			if (!result)
				iError_report_byNumber(_ERROR_INTERNAL_ERROR, iVariable_get_relatedComp(varParam), false);


		//////////
		// Indicate our result
		//////
			rpar->rp[0] = result;

	}

	s32	ifunction_week_common(SReturnsParams* rpar, u32 tnYear, u32 tnMonth, u32 tnDay, s32 tnMinDaysInWeek, s32 tnFirstDayOfWeek)
	{
		s32	lnWeek, ln1WDay, lnDayOfYear, lnDaysInYear, lnDaysNextYear;
		s32 lnTempDays;


		// Day of week January 1 
		ln1WDay		= ifunction_dow_common(rpar, tnYear, 1, 1);

		// Day of year 
		lnDayOfYear	= iiDateMath_get_dayNumberIntoYear(tnYear, tnMonth, tnDay) - 1/*-1 because weekdays start at 0*/;

		// Account for first day of week
		ln1WDay		= (ln1WDay + (7 - tnFirstDayOfWeek)) % 7;


		//////////
		// Compute week
		//////
			switch(tnMinDaysInWeek)
			{
				case 1:
					//////////
					// First week contains January 1st
					//////
						lnWeek = ((ln1WDay + lnDayOfYear) / 7) + 1;


					//////////
					// Set to 53rd week only if we're not in the first week of the new year
					//////
						if (lnWeek == 54)
						{
							lnWeek = 1;

						} else if (lnWeek == 53) {
							lnDaysInYear	= iiDateMath_isLeapYear(tnYear) ? 366 : 365;
							lnDaysNextYear	= ifunction_dow_common(rpar, tnYear + 1, 1, 1);
							lnDaysNextYear	= (lnDaysNextYear + (7 - tnFirstDayOfWeek)) % 7;

							if (lnDayOfYear > (lnDaysInYear-lnDaysNextYear-1))
								lnWeek = 1;
						}
						break;

				case 7:
					//////////
					// First week has seven days
					//////
						lnWeek = ((ln1WDay + lnDayOfYear) / 7);


					//////////
					// First week of a year is equal to the last week of the previous year
					//////
						if (lnWeek == 0)
							lnWeek = ifunction_week_common(rpar, tnYear - 1, 12, 31, tnMinDaysInWeek, tnFirstDayOfWeek);

						break;

				default:
					//////////
					// Example: The larger half (four days) of the first week is in the current year 
					//////
						if (ln1WDay < tnMinDaysInWeek)
						{
							// Monday to Thursday
							lnWeek = 1;

						} else if (ln1WDay == tnMinDaysInWeek) {
							// Friday
							lnWeek = 53;

						} else if (ln1WDay == tnMinDaysInWeek + 1) {
							// Saturday
							// Year after leapyear
							if (iiDateMath_isLeapYear(tnYear - 1))		lnWeek = 53;
							else										lnWeek = 52;

						} else {
							// Sunday
							lnWeek = 52;
						}

						if ((lnWeek == 1) || (lnDayOfYear + ln1WDay > 6))
						{
							if (lnWeek == 1)		lnWeek += (lnDayOfYear + ln1WDay) / 7;
							else					lnWeek =  (lnDayOfYear + ln1WDay) / 7;
							
							if (lnWeek == 53)
							{ 
								// next Sunday is equal to first Sunday in the new year
								lnTempDays	= iiDateMath_get_julian_from_YyyyMmDd(NULL, tnYear, tnMonth, tnDay);
								lnTempDays	+=  6 - (ifunction_dow_common(rpar, tnYear, tnMonth, tnDay) + (7 - tnFirstDayOfWeek)) % 7;
								iiDateMath_get_YyyyMmDd_from_julian(lnTempDays, &tnYear, &tnMonth, &tnDay);

								lnWeek		= ifunction_week_common(rpar, tnYear, tnMonth, tnDay, tnMinDaysInWeek, tnFirstDayOfWeek);
							}
						}

			}


		/////////
		// return week
		//////
			return lnWeek;

	}
