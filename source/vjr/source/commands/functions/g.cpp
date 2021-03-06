//////////
//
// /libsf/source/vjr/commands/funcs/g.cpp
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
// Function: GOMONTH()
// Returns the date that is a specified number of months before or after a given Date or DateTime expression.
//
//////
// Version 0.57
// Last update:
//     Apr.06.2015
//////
// Change log:
//     Apr.06.2015 - Initial creation by Stefano D'Amico
//////
// Parameters:
//     p1			-- Date, Datetimex, or DateTime
//     p2			-- Specifies the number of months from the date or datetime
//
//////
// Returns:
//    Date, Datetimex, or Datetime data type.
//
//////
	static cs8 cgGoMonthData[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	VOID function_gomonth(SThisCode* thisCode, SFunctionParams* rpar)
	{
		SVariable* varParam = rpar->ip[0];
		SVariable* varMonth = rpar->ip[1];

		s32			lnNumOfMonths, lnYear, lnMonth;
		u32			lnDay, lnLastDay, lnHour, lnMinute, lnSecond;
		s32			lnMillisecond, lnNanosecond;
		f32			lfJulian;
		SVariable*	result;
		s8			buffer[16];
		u32			errorNum;
		bool		error;


		//////////
		// Parameter 1 must be date or datetime
		//////
			rpar->rp[0] = NULL;
			if (!iVariable_isValid(varParam) || !(iVariable_isTypeDate(varParam) || iVariable_isTypeDatetimeX(varParam) || iVariable_isTypeDatetime(varParam)))
			{
				iError_reportByNumber(thisCode, _ERROR_INVALID_ARGUMENT_TYPE_COUNT, iVariable_getRelatedComp(thisCode, varParam), false);
				return;
			}


		//////////
		// Grab year, month, day from datetime or date
		//////
			     if (iVariable_isTypeDatetime(varParam))		iiDateMath_get_YyyyMmDd_from_julian					(varParam->value.data_dt->julian,			(u32*)&lnYear, (u32*)&lnMonth, &lnDay);
			else if (iVariable_isTypeDatetimeX(varParam))		iiDateMath_get_YyyyMmDdHhMmSsMssNss_from_jseconds	(varParam->value.data_dtx->jseconds, NULL,	(u32*)&lnYear, (u32*)&lnMonth, &lnDay, NULL, NULL, NULL, NULL, NULL);
			else /* date */										iiDateMath_get_YyyyMmDd_from_YYYYMMDD				(varParam->value.data_u8,					(u32*)&lnYear, (u32*)&lnMonth, &lnDay);



		//////////
		// Parameter 2 must be numeric, positive or negative (GOMONTH( ) does not support dates earlier than 1753.)
		//////
			if (!iVariable_isValid(varMonth) || !iVariable_isTypeNumeric(varMonth))
			{
				// Invalid second parameter
				iError_reportByNumber(thisCode, _ERROR_INVALID_ARGUMENT_TYPE_COUNT, iVariable_getRelatedComp(thisCode, varMonth), false);
				return;
			}


		//////////
		// Grab the value
		//////
			lnNumOfMonths = iiVariable_getAs_s32(thisCode, varMonth, false, &error, &errorNum);
			if (error)
			{
				iError_reportByNumber(thisCode, errorNum, iVariable_getRelatedComp(thisCode, varMonth), false);
				return;
			}


		//////////
		// Compute new date
		//////
			if (lnNumOfMonths != 0)
			{

				//////////
				// Adjust year
				//////
					if (lnNumOfMonths > 0)
					{
						// Year may move forward
						lnYear += (lnMonth + lnNumOfMonths - 1) / 12;

					} else {	
						// Year may move backwards
						if (lnMonth + lnNumOfMonths <= 0)
							lnYear += (lnMonth + lnNumOfMonths) / 12 - 1;
					}

					// Is year in range 1600..2400
					if (lnYear < 1600 || lnYear > 2400)
					{
						iError_reportByNumber(thisCode, _ERROR_OUT_OF_RANGE, iVariable_getRelatedComp(thisCode, varParam), false);
						return;
					}


				//////////
				// Adjust month
				//////
					lnMonth = (lnMonth + lnNumOfMonths) % 12;
					if (lnMonth < 1)
						lnMonth += 12;


				//////////
				// Is day valid for the new date?
				//////
					// Day range 1..28 is always valid
					if (lnDay > 28)
					{
						// Grab last day of month
						if (lnMonth == 2 && iDateMath_isLeapYear(lnYear))
						{
							// February leap year
							lnLastDay = 29;

						} else {
							// Get the last day of the month for the indicated month
							lnLastDay = cgGoMonthData[lnMonth - 1];
						}

						// Force the new date's day number into the valid range
						lnDay = min(lnLastDay, lnDay);
					}


				//////////
				// Create our return value
				//////
					if (iVariable_isTypeDatetime(varParam))
					{
						// Datetime
						result = iVariable_create(thisCode, _VAR_TYPE_DATETIME, NULL, true);
						if (result)
						{
							// Date is stored as julian day number
							result->value.data_dt->julian	= iiDateMath_get_julian_from_YyyyMmDd(&lfJulian, lnYear, (u32)lnMonth, lnDay);
							result->value.data_dt->seconds = varParam->value.data_dt->seconds;
						}

					} else if (iVariable_isTypeDatetimeX(varParam)) {
						// DatetimeX
						result = iVariable_create(thisCode, _VAR_TYPE_DATETIMEX, NULL, true);
						if (result)
						{
							// Date is stored as julian day number
							iiDateMath_get_YyyyMmDdHhMmSsMssNss_from_jseconds(varParam->value.data_dtx->jseconds, NULL, NULL, NULL, NULL, &lnHour, &lnMinute, &lnSecond, &lnMillisecond, &lnNanosecond);
							varParam->value.data_dtx->jseconds = iiDateMath_get_jseconds_from_YyyyMmDdHhMmSsMssMics(NULL, (u32)lnYear, (u32)lnMonth, lnDay, lnHour, lnMinute, lnSecond, lnMillisecond, lnNanosecond);
						}

					} else {
						// Date is stored as YYYYMMDD
						iiDateMath_get_YYYYMMDD_from_YyyyMmDd(buffer, lnYear, (u32)lnMonth, lnDay);
						result = iVariable_createAndPopulate_byText(thisCode, _VAR_TYPE_DATE, buffer, 8, false);
					}

			} else {
				// No month movement, copy original
				result	= iVariable_copy(thisCode, varParam, false);
			}


		//////////
		// Are we good?
		//////
			if (!result)
				iError_reportByNumber(thisCode, _ERROR_INTERNAL_ERROR, iVariable_getRelatedComp(thisCode, varParam), false);


		//////////
		// Return the result
		//////
			rpar->rp[0] = result;

	}




//////////
//
// Function: GRAYSCALE()
// Grayscales a color.
//
//////
// Version 0.57
// Last update:
//     Mar.16.2015
//////
// Change log:
//     Mar.16.2015 - Initial creation
//////
// Parameters:
//     varColor			-- The color to grayscale.
//     varPercentage	-- (Optional) A percentage to grayscale (0.05 leaves almost all the color data, 0.95 is almost completely grayscaled)
//////
// Returns:
//    The input pathname with the new stem.
//////
	void function_grayscale(SThisCode* thisCode, SFunctionParams* rpar)
	{
		SVariable* varColor			= rpar->ip[0];
		SVariable* varPercentage	= rpar->ip[1];


		// Return grayscale
		ifunction_colorize_common(thisCode, rpar, varColor, NULL, varPercentage, false);
	}




//////////
//
// Function: GRN()
// Retrieves the green channel from an RGBA or BGRA color.
//
//////
// Version 0.57
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
	void function_grn(SThisCode* thisCode, SFunctionParams* rpar)
	{
		SVariable* varColor = rpar->ip[0];


		// Return grn
		ifunction_color_common(thisCode, rpar, varColor, 0x0000ff00, 8);
	}
