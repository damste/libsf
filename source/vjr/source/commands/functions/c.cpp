//////////
//
// /libsf/source/vjr/commands/funcs/c.cpp
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
// Function: CDOW()
// Returns the day of the week from a given Date or DateTime expression.
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
//    CDOW() returns the name of the day of the week as a string in proper noun format.
//////
// Example:
//	  dt = datetime()	&& Apr.06.2015
//    ? CDOW(dt)		&& Displays Monday
//    ? CDOW()          && Displays current date's character day of week
//////
	SVariable* function_cdow(SThisCode* thisCode, SReturnsParams* returnsParams)
	{
		SVariable* varParam = returnsParams->params[0];
		
		u32			lnYear, lnMonth, lnDay;
		s8			lnDow;
		SYSTEMTIME	lst;
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
				if (iVariable_isTypeDatetime(varParam))			iiDateMath_extract_YyyyMmDd_from_Julian		(varParam->value.data_dt->julian,	&lnYear, &lnMonth, &lnDay);
				else /* date */									iiDateMath_extract_YyyyMmDd_from_YYYYMMDD	(varParam->value.data_u8,			&lnYear, &lnMonth, &lnDay);

			} else {
				// Use the current date
				if (_settings)		iTime_getLocalOrSystem(&lst, propGet_settings_TimeLocal(_settings));
				else				GetLocalTime(&lst);
				lnYear	= lst.wYear;
				lnMonth	= lst.wMonth;
				lnDay	= lst.wDay;
			}


		//////////
		// Compute the day of week
		//////
			lnDow	= ifunction_dow_common(lnYear, lnMonth, lnDay);


		//////////
		// Create our result
		//////
			result = iVariable_createAndPopulate_byText(thisCode, _VAR_TYPE_CHARACTER, (cs8*)cgcDayOfWeekNames[lnDow], (u32)strlen(cgcDayOfWeekNames[lnDow]), false);
			if (!result)
				iError_reportByNumber(thisCode, _ERROR_INTERNAL_ERROR, iVariable_getRelatedComp(thisCode, varParam), false);


		//////////
		// Indicate our result
		//////
			return(result);

	}

	u32	ifunction_dow_common(u32 tnYear, u32 tnMonth, u32 tnDay)
	{
		u32			lnYear, lnDow;
		static cs8	cgCdowData[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };


		//////////
		// Adjust for leap year calculation
		//////
			lnYear = tnYear;
			if (tnMonth <= 2)
				--lnYear;									// Leap year is in February


		//////////
		// Compute the day of week
		//////
			lnDow =			(lnYear +						// Base year
							(lnYear / 4)					// Leap years
						-	(lnYear / 100)					// Not centuries not evenly divisible by 100
						+	(lnYear / 400)					// And centuries evenly divisible by 400
						+	cgCdowData[tnMonth - 1]			// Plus the "magic" month number
						+	tnDay)							// Plus day of month
					/*-------------------------------*/
						%	7;								// Modulo to a day of week


		//////////
		// Result the day of week
		//////
			return(lnDow);

	}




//////////
//
// Function: CEILING()
// Returns the next highest integer that is greater than or equal to the specified numeric expression.
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
//    CEILING(n) of the value in p1
//////
// Example:
//    ? CEILING(2.2)		&& Display 3
//////
    SVariable* function_ceiling(SThisCode* thisCode, SReturnsParams* returnsParams)
    {
		SVariable* varNumber = returnsParams->params[0];


        // Return ceiling
		return(ifunction_numbers_common(thisCode, varNumber, NULL, NULL, _FP_COMMON_CEILING, _VAR_TYPE_S64, propGet_settings_ncset_ceilingFloor(_settings), false, returnsParams));
	}



//////////
//
// Function: CHR()
// Takes a numeric input in the range 0..255, and converts it to its ASCII character.
//
//////
// Version 0.56
// Last update:
//     Jul.05.2014
//////
// Change log:
//     Jul.05.2014 - Initial creation
//////
// Parameters:
//     p1			-- Numeric, in the range 0..255
//
//////
// Returns:
//    Character		-- Input number converted to character
//////
    SVariable* function_chr(SThisCode* thisCode, SReturnsParams* returnsParams)
    {
		SVariable*	varNumber = returnsParams->params[0];
        s32			value;
		u32			errorNum;
        bool		error;
        SVariable*	result;
		u8			buffer[16];


		//////////
		// Parameter 1 must be numeric
		//////
			if (!iVariable_isValid(varNumber) || !iVariable_isTypeNumeric(varNumber))
			{
				iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_getRelatedComp(thisCode, varNumber), false);
				return(NULL);
			}


		//////////
        // It must be in the range 0..255
		//////
			value = iiVariable_getAs_s32(thisCode, varNumber, false, &error, &errorNum);
			if (error)
			{
				// The iVariable_getAs_s32() function reported an error.
				// This means the user is trying to obtain an integer value from a logical, or something similar.
				iError_reportByNumber(thisCode, errorNum, iVariable_getRelatedComp(thisCode, varNumber), false);
				return(NULL);

			} else if (value > 255 || value < 0) {
				// We report our own error
				iError_report(thisCode, (u8*)"Parameter must be in the range 0..255", false);
				return(NULL);
			}


		//////////
        // Create our return result
		//////
	        result = iVariable_create(thisCode, _VAR_TYPE_CHARACTER, NULL, true);
			if (!result)
			{
				iError_report(thisCode, (u8*)"Internal error.", false);
				return(NULL);
			}


		//////////
        // Populate the result as an ASCII character
		//////
	        buffer[0] = (u8)value;
			buffer[1] = 0;
			iDatum_duplicate(&result->value, buffer, 1);


		//////////
        // Return our converted result
		//////
	        return(result);
    }




//////////
//
// Function: CHRTRAN()
// Character transformation
//
//////
// Version 0.56
// Last update:
//     Aug.21.2014
//////
// Change log:
//     Aug.21.2014 - Initial creation
//////
// Parameters:
//     pOriginalString		-- The string being updated
//     pSearch				-- The search characters
//     pReplace             -- The characters to replace when found
//
//////
// Returns:
//    A copy of the pOriginalString with everything converted.
//
//////
	SVariable* function_chrtran(SThisCode* thisCode, SReturnsParams* returnsParams)
	{
		SVariable* varString	= returnsParams->params[0];
		SVariable* varSearch	= returnsParams->params[1];
		SVariable* varReplace	= returnsParams->params[2];


		// Return chrtran
		return(ifunction_chrtran_common(thisCode, varString, varSearch, varReplace, true, returnsParams));
	}

	SVariable* function_chrtranc(SThisCode* thisCode, SReturnsParams* returnsParams)
	{
		SVariable* varString	= returnsParams->params[0];
		SVariable* varSearch	= returnsParams->params[1];
		SVariable* varReplace	= returnsParams->params[2];


		// Return chrtranc
		return(ifunction_chrtran_common(thisCode, varString, varSearch, varReplace, false, returnsParams));
	}

	SVariable* ifunction_chrtran_common(SThisCode* thisCode, SVariable* varString, SVariable* varSearch, SVariable* varReplace, bool tlCaseSensitive, SReturnsParams* returnsParams)
	{
		s8			c1, c2;
		s32			lnSrc, lnDst, lnSearch;
		bool		llFound;
        SVariable*	result;


		//////////
		// Parameter 1 must be character
		//////
			if (!iVariable_isValid(varString) || !iVariable_isTypeCharacter(varString))
			{
				iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_getRelatedComp(thisCode, varString), false);
				return(NULL);
			}


		//////////
		// Parameter 2 must be character
		//////
			if (!iVariable_isValid(varSearch) || !iVariable_isTypeCharacter(varSearch))
			{
				iError_reportByNumber(thisCode, _ERROR_P2_IS_INCORRECT, iVariable_getRelatedComp(thisCode, varSearch), false);
				return(NULL);
			}


		//////////
		// Parameter 3 is optional, but must be character if present
		//////
			if (!iVariable_isValid(varReplace))
			{
				// They didn't provide a 3rd parameter, so we'll use a pseudo placeholder which is an empty string
				varReplace = cvarEmptyString;

			} else if (!iVariable_isTypeCharacter(varReplace)) {
				// It is invalid
				iError_reportByNumber(thisCode, _ERROR_P3_IS_INCORRECT, iVariable_getRelatedComp(thisCode, varReplace), false);
				return(NULL);
			}


		//////////
		// Allocate a copy of the original string
		//////
			result = iVariable_createAndPopulate_byText(thisCode, _VAR_TYPE_CHARACTER, varString->value.data_u8, varString->value.length, false);

			// If the original string is empty, or the characters to search for are empty, then we don't need to do anything
			if (varString->value.length == 0 || varSearch->value.length == 0)
				return(result);


		//////////
		// Iterate through the string and update as we go
		//////
			for (lnSrc = 0, lnDst = 0; lnSrc < result->value.length; lnSrc++)
			{
				// Grab this character
				c1 = result->value.data[lnSrc];

				// Adjust the case if need be
				if (!tlCaseSensitive)
				{
					if (c1 >= 'A' && c1 <= 'Z')
						c1 += 0x20;
				}

				// Search the conversion string
				llFound = false;
				for (lnSearch = 0; lnSearch < varSearch->value.length; lnSearch++)
				{
					// Grab this character
					c2 = varSearch->value.data[lnSearch];

					// Adjust the case if necessary
					if (!tlCaseSensitive)
					{
						// Case insensitive, convert if need be
						if (c2 >= 'A' && c2 <= 'Z')
							c2 += 0x20;
					}

					// Is this character a match?
					if (c1 == c2)
					{
						// Indicate we found it
						llFound = true;

						// We need to perform the replace
						if (lnSearch < varReplace->value.length)
						{
							// We replace it with the character that's there
							result->value.data[lnDst] = varReplace->value.data[lnSearch];

						} else {
							// There is no translation character, so we just delete this character
							// To do that, we decrease our lnDst because it will be increased below
							--lnDst;
						}

						// We're done with this one because we found its match
						break;
					}
				}

				// When we get here, we either found the character or not
				if (!llFound && lnSrc != lnDst)
				{
					// We need to copy this character over
					result->value.data[lnDst] = result->value.data[lnSrc];
				}

				// Move our destination forward
				++lnDst;
			}


		//////////
		// When we get here, lnDst indicates how long the output string is
		//////
			result->value.length = lnDst;


		//////////
		// Return our final string
		/////
			return(result);
	}




//////////
//
// Function: CMONTH()
// Returns the name of the month from a given date or DateTime expression.
//
//////
// Version 0.57
// Last update:
//     Apr.05.2015
//////
// Change log:
//     Apr.05.2015 - Initial creation by Stefano D'Amico
//////
// Parameters:
//     p1			-- Date or DateTime
//
//////
// Returns:
//    CMONTH( ) returns the name of the month as a string in proper noun format.
//////
// Example:
//	  dt = datetime()	&& Apr.06.2015
//    ? CMONTH(dt)		&& Displays April
//    ? CMONTH()        && Displays current date's character month
//////
	SVariable* function_cmonth(SThisCode* thisCode, SReturnsParams* returnsParams)
	{
		SVariable* varParam = returnsParams->params[0];

		u32			lnYear, lnMonth, lnDay;
		s8			lnMonthIdx;
		SYSTEMTIME	lst;
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
					if (iVariable_isTypeDatetime(varParam))			iiDateMath_extract_YyyyMmDd_from_Julian		(varParam->value.data_dt->julian,	&lnYear, &lnMonth, &lnDay);
					else /* date */									iiDateMath_extract_YyyyMmDd_from_YYYYMMDD		(varParam->value.data_u8,			&lnYear, &lnMonth, &lnDay);


			} else {
				// Use the current date
				if (_settings)		iTime_getLocalOrSystem(&lst, propGet_settings_TimeLocal(_settings));
				else				GetLocalTime(&lst);
				lnYear	= lst.wYear;
				lnMonth	= lst.wMonth;
				lnDay	= lst.wDay;
			}


		//////////
		// Compute index
		//////
			lnMonthIdx = max(min(lnMonth, 12), 1) - 1;		// Force into range 1..12, then backoff one for base-0 array reference


		//////////
		// Create our result
		//////
			result = iVariable_createAndPopulate_byText(thisCode, _VAR_TYPE_CHARACTER, (cs8*)cgcMonthNames[lnMonthIdx], (u32)strlen(cgcMonthNames[lnMonthIdx]), false);
			if (!result)
				iError_reportByNumber(thisCode, _ERROR_INTERNAL_ERROR, iVariable_getRelatedComp(thisCode, varParam), false);


		//////////
		// Indicate our result
		//////
			return(result);

	}




//////////
//
// Function: COLORIZE()
// Colorizes an existing color by blending two colors.
//
//////
// Version 0.56
// Last update:
//     Mar.16.2015
//////
// Change log:
//     Mar.16.2015 - Initial creation
//////
// Parameters:
//     varColor			-- The original color
//     varColorTarget	-- The color to blend in
//     varPercentage	-- (Optional) How much to blend
//
//////
// Returns:
//    Numeric			-- The resulting colorized color
//
//////
	SVariable* function_colorize(SThisCode* thisCode, SReturnsParams* returnsParams)
	{
		SVariable* varColor			= returnsParams->params[0];
		SVariable* varColorTarget	= returnsParams->params[1];
		SVariable* varPercentage	= returnsParams->params[2];


		// Return colorize
		return(ifunction_colorize_common(thisCode, varColor, varColorTarget, varPercentage, true, returnsParams));
	}

	SVariable* ifunction_colorize_common(SThisCode* thisCode, SVariable* varColor, SVariable* varColorTarget, SVariable* varPercentage, bool tlApplyColorTarget, SReturnsParams* returnsParams)
	{
		u32			lnColor, lnColorTarget, lnColorNew;
		f32			lfRedC, lfGrnC, lfBluC, lfAlpC;		// varColor
		f32			lfRedT, lfGrnT, lfBluT, lfAlpT;		// varColorTarget
		f32			lfAlp, lfMalp, lfGray, lfRedNew, lfGrnNew, lfBluNew, lfAlpNew;
		bool		error;
		u32			errorNum;
		SVariable*	result;


		//////////
		// Color must be numeric
		//////
			if (!iVariable_isValid(varColor) || !iVariable_isTypeNumeric(varColor))
			{
				iError_reportByNumber(thisCode, _ERROR_PARAMETER_IS_INCORRECT, iVariable_getRelatedComp(thisCode, varColor), false);
				return(NULL);
			}


		//////////
		// If present, varColorTarget must be numeric
		//////
			if (tlApplyColorTarget)
			{
				if (!iVariable_isValid(varColorTarget) || !iVariable_isTypeNumeric(varColorTarget))
				{
					iError_reportByNumber(thisCode, _ERROR_PARAMETER_IS_INCORRECT, iVariable_getRelatedComp(thisCode, varColorTarget), false);
					return(NULL);
				}
			}


		//////////
		// Grab the percentage
		//////
			if (varPercentage)
			{
				// Must be floating point
				if (!iVariable_isValid(varPercentage) || !iVariable_isTypeFloatingPoint(varPercentage))
				{
					iError_reportByNumber(thisCode, _ERROR_PARAMETER_IS_INCORRECT, iVariable_getRelatedComp(thisCode, varPercentage), false);
					return(NULL);
				}

				// Grab the value
				lfAlp = iiVariable_getAs_f32(thisCode, varPercentage, false, &error, &errorNum);
				if (error)	{	iError_reportByNumber(thisCode, errorNum, iVariable_getRelatedComp(thisCode, varPercentage), false);	return(NULL);	}

				// Must be in the range 0.0 to 1.0
				if (lfAlp < 0.0f || lfAlp > 1.0f)
				{
					iError_reportByNumber(thisCode, _ERROR_OUT_OF_RANGE, iVariable_getRelatedComp(thisCode, varPercentage), false);
					return(NULL);
				}
				// If we get here, we're good

			} else {
				// They didn't specify a percentage, use default values
				if (tlApplyColorTarget)		lfAlp = 0.5f;		// colorize() 50% / 50%
				else						lfAlp = 1.0f;		// grayscale() 100%
			}

			// Compute our malp
			lfMalp = 1.0f - lfAlp;


		//////////
		// Grab the color
		//////
			// Extract the color
			lnColor = iiVariable_getAs_u32(thisCode, varColor, false, &error, &errorNum);
			if (error)	{	iError_reportByNumber(thisCode, errorNum, iVariable_getRelatedComp(thisCode, varColor), false);	return(NULL);	}

			// Extract channels
			lfRedC = (f32)red(lnColor);
			lfGrnC = (f32)grn(lnColor);
			lfBluC = (f32)blu(lnColor);
			lfAlpC = (f32)alp(lnColor);


		//////////
		// Grab the color target
		//////
			if (tlApplyColorTarget)
			{
				// Extract the color target
				lnColorTarget = iiVariable_getAs_u32(thisCode, varColorTarget, false, &error, &errorNum);
				if (error)	{	iError_reportByNumber(thisCode, errorNum, iVariable_getRelatedComp(thisCode, varColor), false);	return(NULL);	}

				// Extract channels
				lfRedT = (f32)red(lnColorTarget);
				lfGrnT = (f32)grn(lnColorTarget);
				lfBluT = (f32)blu(lnColorTarget);
				lfAlpT = (f32)alp(lnColorTarget);


				//////////
				// Generate the combined color (original color * malp) + (color target * alp)
				//////
					lfRedNew	= (lfRedC * lfMalp) + (lfRedT * lfAlp);
					lfGrnNew	= (lfGrnC * lfMalp) + (lfGrnT * lfAlp);
					lfBluNew	= (lfBluC * lfMalp) + (lfBluT * lfAlp);
					lfAlpNew	= (lfAlpC * lfMalp) + (lfAlpT * lfAlp);


			} else {
				// We are grayscaling
				lfGray		= max(min((lfRedC * 0.35f) + (lfGrnC * 0.54f) + (lfBluC * 0.11f), 1.0f), 0.0f);

				// Generate the new grayscaled color (original color * malp) + (grayscale * alp)
				lfRedNew	= (lfRedC * lfMalp) + (lfGray * lfAlp);
				lfGrnNew	= (lfGrnC * lfMalp) + (lfGray * lfAlp);
				lfBluNew	= (lfBluC * lfMalp) + (lfGray * lfAlp);
				lfAlpNew	= (lfAlpC * lfMalp) + (lfGray * lfAlp);
			}


		//////////
		// Construct the new color into an integer
		//////
			lnColorNew = rgba((u32)lfRedNew, (u32)lfGrnNew, (u32)lfBluNew, (u32)lfAlpNew);


		//////////
		// Construct our result
		//////
			result = iVariable_create(thisCode, _VAR_TYPE_U32, NULL, true);
			if (!result)
			{
				iError_reportByNumber(thisCode, _ERROR_INTERNAL_ERROR, NULL, false);
				return(NULL);
			}


		//////////
		// Populate and return our result
		//////
			*result->value.data_u32 = lnColorNew;
			return(result);
	}




//////////
//
// Function: COS()
// Returns the cosine of a numeric expression.
//
//////
// Version 0.56
// Last update:
//     Mar.17.2015
//////
// Change log:
//     Mar.17.2015 - Initial creation by Stefano D'Amico
//////
// Parameters:
//     p1			-- Numeric or floating point
//
//////
// Returns:
//    COS(n) of the value in p1
//////
// Example:
//    ? COS(0)		&& Display 1.00
//////
    SVariable* function_cos(SThisCode* thisCode, SReturnsParams* returnsParams)
    {
		SVariable* varNumber = returnsParams->params[0];


		// Return cos
		return(ifunction_numbers_common(thisCode, varNumber, NULL, NULL, _FP_COMMON_COS, _VAR_TYPE_F64, false, false, returnsParams));
	}




//////////
//
// Function: CREATEOBJECT()
// Instantiates and instance of the indicated class.
//
//////
// Version 0.56
// Last update:
//     Jul.12.2014
//////
// Change log:
//     Jul.12.2014 - Initial creation
//////
// Parameters:
//     pClassname	-- The name of the class
//     Note:  A future extension will allow parameters passed to the class's init() event
//
//////
// Returns:
//    Object		-- The class instance object is returned
//
//////
	SVariable* function_createobject(SThisCode* thisCode, SReturnsParams* returnsParams)
	{
		SVariable*	varClass = returnsParams->params[0];
		s32			lnObjType;
		SObject*	obj;
        SVariable*	result;


		//////////
		// Parameter 1 must be character
		//////
			if (!iVariable_isValid(varClass) || !iVariable_isTypeCharacter(varClass))
			{
				iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_getRelatedComp(thisCode, varClass), false);
				return(NULL);
			}


		//////////
        // It must be at least one character long
		//////
			if (varClass->value.length == 0)
				iError_reportByNumber(thisCode, _ERROR_EMPTY_STRING, iVariable_getRelatedComp(thisCode, varClass), false);


		//////////
		// See if we know the class
		//////
			lnObjType = iiObj_getBaseclassType_byName(thisCode, varClass->value.data, varClass->value.length);
			if (lnObjType <= 0)
			{
				iError_report(thisCode, (cu8*)"Unknown class", false);
				return(NULL);
			}

			// Create our object
			obj = iObj_create(thisCode, lnObjType, NULL);
			if (!obj)
			{
				iError_report(thisCode, (cu8*)"Internal error on create object.", false);
				return(NULL);
			}


		//////////
        // Create our return result variable, which is a reference to the new object
		//////
	        result = iVariable_create(thisCode, _VAR_TYPE_OBJECT, NULL, true);
			if (!result)
			{
				iObj_delete(thisCode, &obj, true, true, true);
				iError_report(thisCode, (cu8*)"Internal error on create variable.", false);
				return(NULL);
			}

			// Store the object reference
			result->obj = obj;


		//////////
        // Return our converted result
		//////
	        return(result);
	}




//////////
//
// Function: CTOD()
// Converts a character expression to a date expression.
//
//////
// Version 0.57
// Last update:
//     Apr.10.2015
//////
// Change log:
//     Apr.10.2015 - Initial creation by Stefano D'Amico
//////
// Parameters:
//     p1			-- Character
//
//////
// Returns:
//    Date data type. CTOD( ) returns a Date value
// 
//////
// Example:
//    SET DATE MDY
//    ?CTOD("12/25/15") &&Displays 12-25-2015
//    ?CTOD("12/25/2015") &&Displays 12-25-2015
//    ?CTOD("12-25-15") &&Displays 12-25-2015
//    ?CTOD("12-25-15 12:33:44 AM") &&Displays 12-25-2015
//    ?CTOD("12-25-15 12:33:44.555") &&Displays 12-25-2015
//
//////
	SVariable* function_ctod(SThisCode* thisCode, SReturnsParams* returnsParams)
	{
		SVariable* varString = returnsParams->params[0];

		//Return date
		return(ifunction_ctox_common(thisCode, varString, true));
	}

	SVariable* ifunction_ctox_common(SThisCode* thisCode, SVariable* varCtoxString, bool tlIncludeTime)
	{
		s8			c1, c2, cx, cMark;
		s32			lnI, lnSkip, lnStop, lnDate, lnAmPm;
		u32			lnYYYY, lnMM, lnDD, lnHh, lnMm, lnSs, lnMss;
		bool		llValidate, llYear, llTimeValid;
		s8*			lcYYYY		= NULL;
		s8*			lcMM		= NULL;
		s8*			lcDD		= NULL;
		s8*			lcHh		= NULL;
		s8*			lcMm		= NULL;
		s8*			lcSs		= NULL;
		s8*			lcMss		= NULL;
		s8*			data;
		SVariable*	varMark;
		SVariable*	varDate;
		SVariable*	result;


// Untested code, breakpoint and examine
debug_break;
		//////////
		// varCtoxString must be character
		//////
			if (!iVariable_isValid(varCtoxString) || !iVariable_isTypeCharacter(varCtoxString))
			{
				iError_reportByNumber(thisCode, _ERROR_INVALID_ARGUMENT_TYPE_COUNT, iVariable_getRelatedComp(thisCode, varCtoxString),false);
				return(NULL);
			}


		//////////
		// Get the expected general date format
		//////
			lnDate	= propGet_settings_Date(_settings);
			data	= varCtoxString->value.data;
			if (data[1] == '^')
			{
				// Can be:
				// ^YYYY-MM-DD
				// ^YYYY-MM-DD, 2:13p
				// ^YYYY-MM-DD Hh:Mm
				// ^YYYY-MM-DD Hh:Mm:Ss
// TODO:  General purpose ^... date parser (for compile-time and runtime)

			} else if (varCtoxString->value.length == 23 && data[4] == '-' && data[7] == '-' && (data[10] == 32 || data[10] == 'T') && data[13] == ':' && data[16] == ':' && data[19] == '.') {
				// YYYY-MM-DDTHh:Mm:Ss.Mss
				varDate = varSetDateYyyyMmDdTHhMmSsMss;

			} else if (varCtoxString->value.length == 19 && data[4] == '-' && data[7] == '-' && (data[10] == 32 || data[10] == 'T') && data[13] == ':' && data[16] == ':') {
				// YYYY-MM-DDTHh:Mm:Ss
				varDate = varSetDateYyyyMmDdTHhMmSs;

			} else {
				// Use the current system date format
				// Note:  varDate is a reference to the constant
				varDate = iiDateMath_get_dateTemplate(lnDate);
			}


		//////////
		// Grab the SET("MARK") character
		//////
			// Note:  varMark is a reference to the actual _settings.mark value
			varMark = propGet_settings_Mark(_settings);
			if (!varMark || !iVariable_isTypeCharacter(varMark) || !varMark->value.data || varMark->value.length <= 0)
			{
				// Fall back on current date type
				switch (lnDate)
				{
					case _SET_DATE_USA:			// mm-dd-yy
					case _SET_DATE_ITALIAN:		// dd-mm-yy
						cMark = '-';
						break;

					case _SET_DATE_GERMAN:		// dd.mm.yy
					case _SET_DATE_ANSI:		// yy.mm.dd
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


		//////////
		// Iterate through every character
		//////
			for (lnI = 0, lnAmPm = -1; lnI < varDate->value.length && !lcYYYY || !lcMM || !lcDD; )
			{
				llYear		= false;
				llValidate	= true;
				lnSkip		= 2;
				c1			= varDate->value.data[lnI + 0];
				c2			= varDate->value.data[lnI + 1];
				switch (c1)
				{
					case '1':
						// Either 11 or 12, for MM or Hh
						if (c2 == '1')		/* Is MM */		lcMM = varCtoxString->value.data + lnI;
						else				/* Is Hh */		lcHh = varCtoxString->value.data + lnI;
						break;

					case '2':
						// Dd
						lcDD = varCtoxString->value.data + lnI;
						break;

					case '3':
						// Either 33/3333 or 34, for YY/YYYY or Mm
						if (c2 == '3')
						{
							// YY/YYYY
							llYear	= true;
							lcYYYY	= varCtoxString->value.data + lnI;

							if (propGet_settings_Century(_settings))
								lnSkip = 4;

						} else {
							// Mm
							lcMm = varCtoxString->value.data + lnI;
						}
						break;

					default:
						lnSkip		= 1;
						llValidate	= false;
						cx			= varCtoxString->value.data[lnI];
						if (cx == '/' || cx == '-' || cx == '.' || cx == cMark)
						{
							// Input syntax formatting error, and we know the offset where it occurred
							iEngine_update_meta1(thisCode, _ERROR_INVALID_ARGUMENT_TYPE_COUNT);
							iEngine_update_meta2(thisCode, lnI);

							// Return a blank datetime or date
							if (tlIncludeTime)		return(iVariable_create(thisCode, _VAR_TYPE_DATETIME,	NULL, true));
							else					return(iVariable_create(thisCode, _VAR_TYPE_DATE,		NULL, true));
						}

				}

				// Validate these data positions between lnI and lnI+lnSkip
				if (llValidate)
				{
					// Iterate through the source string to verify it's the same
// TODO:  Parsing here needs developed
					for (lnStop = lnI + lnSkip; lnI < lnStop; lnI++)
					{
						if (varCtoxString->value.data[lnI] < '0' || varCtoxString->value.data[lnI] > '9')
						{
							// Input syntax formatting error, and we know the offset where it occurred
						}
					}
				}
			}


		//////////
		// When we get here, we have each of them extracted, and we can obtain their integers
		//////
			if (lcYYYY)		lnYYYY = atoi(lcYYYY);
			else			lnYYYY = 1600;

			if (lcMM)		lnMM = atoi(lcMM);
			else			lnMm = 1;

			if (lcDD)		lnDD = atoi(lcDD);
			else			lnDD = 1;

			// Are we including time in our output variable?
			if (tlIncludeTime)
			{
				// Grab Hh:Mm:Ss:Mss
				if (lcHh)		lnHh = atoi(lcHh);
				else			lnHh = 0;

				if (lcMm)		lnMm = atoi(lcMm);
				else			lnMm = 0;

				if (lcSs)		lnSs = atoi(lcSs);
				else			lnSs = 0;

				if (lcMss)		lnMss = atoi(lcMss);
				else			lnMss = 0;

				// Validate the time is valid
// TODO:  Test for presence of AM or PM
				llTimeValid = (lnHh >= 0 && lnHh <= 23);
				llTimeValid = (llTimeValid && (lnMm >= 0 && lnMm <= 59) && (lnSs >= 0 && lnSs <= 59) && (lnMss >= 0 && lnMss <= 999));

			} else {
				// Indicate the time is valid for logic below
				llTimeValid = true;
			}


		//////////
		// Validate the date is valid
		//////
			result = iVariable_create(thisCode, ((tlIncludeTime) ? _VAR_TYPE_DATETIME : _VAR_TYPE_DATE), NULL, false);
			if (result)
			{
				if (!llTimeValid || lnYYYY < 1600 || lnYYYY > 9999 || lnMM < 1 || lnMM > 12 || !iDateMath_isDayValidForDate(lnYYYY, lnMM, lnDD))
				{
					// Invalid, so make it blank
					result->value.data_dt->julian	= _DATETIME_BLANK_DATETIME_JULIAN;
					result->value.data_dt->seconds	= _DATETIME_BLANK_DATETIME_SECONDS;

				} else {
					// It's valid, populate it
					if (tlIncludeTime)
					{
						// Datetime
						result->value.data_dt->julian	= iiDateMath_extract_Julian_from_YyyyMmDd(NULL, lnYYYY, lnMM, lnDD);
						result->value.data_dt->seconds	= iiDateMath_extract_seconds_from_HhMmSsMss(lnHh, lnMm, lnSs, lnMss);

					} else {
						// Just a date
						iiDateMath_convertTo_YYYYMMDD_from_YyyyMmDd(result->value.data, lnYYYY, lnMM, lnDD);
					}
				}

			} else {
				// Should never happen
				iError_reportByNumber(thisCode, _ERROR_INTERNAL_ERROR, iVariable_getRelatedComp(thisCode, varCtoxString), false);
			}


		//////////
		// Signify our result
		//////
			return(result);

	}




//////////
//
// Function: CTOT()
// Converts a character expression to a datetime expression.
//
//////
// Version 0.57
// Last update:
//     Apr.11.2015
//////
// Change log:
//     Apr.11.2015 - Initial creation by Stefano D'Amico
//////
// Parameters:
//     p1			-- Character
//
//////
// Returns:
//    Datetime data type. CTOT( ) returns a Datetime value
//////
// Example:
//    SET DATE MDY
//    ?CTOD("12/25/15") &&Displays 12-25-2015 00:00:00
//    ?CTOD("12/25/2015") &&Displays 12-25-2015 00:00:00
//    ?CTOD("12-25-15") &&Displays 12-25-2015 00:00:00
//    ?CTOD("12-25-15 12:33:44 AM") &&Displays 12-25-2015 00:33:44
//    ?CTOD("12-25-15 12:33:44.555") &&Displays 12-25-2015 12:33:44
//
//////
	SVariable* function_ctot(SThisCode* thisCode, SReturnsParams* returnsParams)
	{
		SVariable* varString = returnsParams->params[0];

		//Return datetime
		return(ifunction_ctox_common(thisCode, varString, false));
	}




//////////
//
// Function: CURDIR()
// Returns the current directory
//
//////
// Version 0.56
// Last Update:
//		Dec.25.2014
//////
// Change log:
//		Dec.25.2014 - Initial creation
//////
// Parameters:
//		none
//////
// Returns:
//		Character		-- Current directory
//////
	SVariable* function_curdir(SThisCode* thisCode, SReturnsParams* returnsParams)
	{
		u8			curdir[_MAX_PATH];
		SVariable*	result;


		// Get the current directory
		memset(curdir, 0, sizeof(curdir));
		GetCurrentDirectory(_MAX_PATH, (s8*)curdir);
		memcpy(curdir + strlen(curdir), "\\\0", 2);

		// Create the output variable
		result = iVariable_createAndPopulate_byText(thisCode, _VAR_TYPE_CHARACTER, curdir + 2, (u32)strlen(curdir + 2), false);
		if (!result)
			iError_reportByNumber(thisCode, _ERROR_INTERNAL_ERROR, NULL, false);

		// Indicate our result
		return(result);
	}
