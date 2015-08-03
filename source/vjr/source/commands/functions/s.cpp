//////////
//
// /libsf/source/vjr/commands/funcs/s.cpp
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
// Function: SEC()
// Returns the seconds portion from a DateTime expression.
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
//     varParam		-- Specifies a DateTime expression from which SEC( ) returns the seconds
//
//////
// Returns:
//    SEC( ) returns a numeric value.
//////
	void function_sec(SThisCode* thisCode, SFunctionParams* rpar)
	{
		SVariable*	varParam = rpar->ip[0];


		// Return second
		ifunction_hhmmss_common(thisCode, rpar, varParam, _HMS_COMMON_SECOND);
	}




//////////
//
// Function: SECONDS()
// Returns the number of seconds that have elapsed since midnight.
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
//     none
//
//////
// Returns:
//    Numeric. SECONDS( ) returns a numeric value in decimal format with a resolution of 1 millisecond.
//////
	void function_seconds(SThisCode* thisCode, SFunctionParams* rpar)
	{
		ifunction_xseconds_common(thisCode, rpar, _XSECONDS_FUNCTION_SECONDS);
	}

	void ifunction_xseconds_common(SThisCode* thisCode, SFunctionParams* rpar, s32 tnFunction)
	{
		f64			lfResult;
		s32			lnNanosecond;
		SYSTEMTIME	lst;
		SVariable*	result;


		//////////
		// Compute the number of seconds that have elapsed since midnight
		//////
			switch (tnFunction)
			{
				case _XSECONDS_FUNCTION_NANOSECOND:
					lfResult = (f64)iiDateMath_get_currentNanosecond();
					break;

				case _XSECONDS_FUNCTION_MICROSECOND:
					lfResult = (f64)iiDateMath_get_currentMicrosecond();
					break;

				default:
					// Grab the time
					if (_settings)		iTime_getLocalOrSystem(&lst, propGet_settings_TimeLocal(_settings));
					else				GetLocalTime(&lst);

					// Indicate time since midnight
					switch (tnFunction)
					{
						case _XSECONDS_FUNCTION_SECONDSX:
							// SECONDSX()
							lnNanosecond	= iiDateMath_get_currentNanosecond();
							lfResult		=		((f64)lst.wHour			* 3600.0		)
												+	((f64)lst.wMinute		* 60.0			)
												+	((f64)lst.wSecond						)
												+	((f64)lnNanosecond		* 0.000000001	);		// Nanosecond
							break;

						case _XSECONDS_FUNCTION_SECONDS:
							// SECONDS()
							lfResult		=		((f64)lst.wHour			* 3600.0		)
												+	((f64)lst.wMinute		* 60.0			)
												+	((f64)lst.wSecond						)
												+	((f64)lst.wMilliseconds	* 0.001			);		// Millisecond
							break;

						default:
							// Should never happen, indicates an internal programming error.
							// Check the call stack to see what was passed incorrectly into this function.
							debug_nop;
							iError_reportByNumber(thisCode, _ERROR_INTERNAL_ERROR, NULL, false);
							return;
					}

			}


		//////////
		// Create and populate output variable
		//////
			// Note:  There is a dependency in SYS(2) that this value be an f64 type:
			result = iVariable_createAndPopulate_byText(thisCode, _VAR_TYPE_F64, (s8*)&lfResult, sizeof(lfResult), false);
			if (!result)
				iError_reportByNumber(thisCode, _ERROR_INTERNAL_ERROR, NULL, false);


		//////////
        // return(result)
		//////
			rpar->rp[0] = result;

	}




//////////
//
// Function: SECONDSTOTIME()
// Converts a SECONDS() into a TIME().
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
//     p1			-- Numeric or floating point
//
//////
// Returns:
//    Character		-- Equivalent of SECONDS() as a TIME()
//////
// Example:
//    k = SECONDS()
//    ? SECONDSTOTIME(k)
//////
	void function_secondstotime(SThisCode* thisCode, SFunctionParams* rpar)
	{
		// Return secondstotime
		ifunction_timesAndDatesConversion_common(thisCode, rpar, _CONVERSION_FUNCTION_SECONDS, _CONVERSION_FUNCTION_TIME);
	}




//////////
//
// Function: SECONDSTOTIMEX()
// Converts a SECONDS() into a TIMEX().
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
//     p1			-- Numeric or floating point
//
//////
// Returns:
//    Character		-- Equivalent of SECONDS() as a TIMEX()
//////
// Example:
//    k = SECONDS()
//    ? SECONDSTOTIMEX(k)
//////
	void function_secondstotimex(SThisCode* thisCode, SFunctionParams* rpar)
	{
		// Return secondstotimex
		ifunction_timesAndDatesConversion_common(thisCode, rpar, _CONVERSION_FUNCTION_SECONDS, _CONVERSION_FUNCTION_TIMEX);
	}




//////////
//
// Function: SECONDSTOT()
// Converts a SECONDS() into a DATETIME().
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
//     p1			-- Numeric or floating point
//     p2			-- (Optional) A date, datetime, or datetimex from which to extract the year,month,day
//
//////
// Returns:
//    Datetime		-- Equivalent of SECONDS() (and optionally the year,month,day input from p2) as a DATETIME()
//////
// Example:
//    k = SECONDS()
//    d = DATE()
//    ? SECONDSTOT(k, d)
//////
	void function_secondstot(SThisCode* thisCode, SFunctionParams* rpar)
	{
		// Return secondstot
		ifunction_timesAndDatesConversion_common(thisCode, rpar, _CONVERSION_FUNCTION_SECONDS, _CONVERSION_FUNCTION_DATETIME);
	}




//////////
//
// Function: SECONDSTOX()
// Converts a SECONDS() into a DATETIMEX().
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
//     p1			-- Numeric or floating point
//     p2			-- (Optional) A date, datetime, or datetimex from which to extract the year,month,day
//
//////
// Returns:
//    Datetime		-- Equivalent of SECONDS() (and optionally the year,month,day input from p2) as a DATETIMEX()
//////
// Example:
//    k = SECONDS()
//    d = DATE()
//    ? SECONDSTOX(k, d)
//////
	void function_secondstox(SThisCode* thisCode, SFunctionParams* rpar)
	{
		// Return secondstox
		ifunction_timesAndDatesConversion_common(thisCode, rpar, _CONVERSION_FUNCTION_SECONDS, _CONVERSION_FUNCTION_DATETIMEX);
	}




//////////
//
// Function: SECONDSX()
// Returns the number of seconds that have elapsed since midnight in extended precision.
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
//     none
//
//////
// Returns:
//    Numeric. SECONDSX( ) returns a numeric value in decimal format with a resolution of 1 microsecond.
//////
	void function_secondsx(SThisCode* thisCode, SFunctionParams* rpar)
	{
		ifunction_xseconds_common(thisCode, rpar, _XSECONDS_FUNCTION_SECONDSX);
	}




//////////
//
// Function: SECONDSXTOTIME()
// Converts a SECONDSX() into a TIME().
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
//     p1			-- Numeric or floating point
//
//////
// Returns:
//    Character		-- Equivalent of SECONDSX() as a TIME()
//////
// Example:
//    k = SECONDSX()
//    ? SECONDSXTOTIME(k)
//////
	void function_secondsxtotime(SThisCode* thisCode, SFunctionParams* rpar)
	{
		// Return secondsxtotime
		ifunction_timesAndDatesConversion_common(thisCode, rpar, _CONVERSION_FUNCTION_SECONDSX, _CONVERSION_FUNCTION_TIME);
	}




//////////
//
// Function: SECONDSXTOTIMEX()
// Converts a SECONDSX() into a TIMEX().
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
//     p1			-- Numeric or floating point
//
//////
// Returns:
//    Character		-- Equivalent of SECONDSX() as a TIMEX()
//////
// Example:
//    k = SECONDSX()
//    ? SECONDSXTOTIMEX(k)
//////
	void function_secondsxtotimex(SThisCode* thisCode, SFunctionParams* rpar)
	{
		// Return secondsxtotimex
		ifunction_timesAndDatesConversion_common(thisCode, rpar, _CONVERSION_FUNCTION_SECONDSX, _CONVERSION_FUNCTION_TIMEX);
	}




//////////
//
// Function: SECONDSXTOT()
// Converts a SECONDSX() into a DATETIMEX().
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
//     p1			-- Numeric or floating point
//     p2			-- (Optional) A date, datetime, or datetimex from which to extract the year,month,day
//
//////
// Returns:
//    Datetime		-- Equivalent of SECONDSX() (and optionally the year,month,day input from p2) as a DATETIME()
//////
// Example:
//    k = SECONDSX()
//    d = DATE()
//    ? SECONDSXTOT(k, d)
//////
	void function_secondsxtot(SThisCode* thisCode, SFunctionParams* rpar)
	{
		// Return secondsxtot
		ifunction_timesAndDatesConversion_common(thisCode, rpar, _CONVERSION_FUNCTION_SECONDSX, _CONVERSION_FUNCTION_DATETIME);
	}




//////////
//
// Function: SECONDSXTOX()
// Converts a SECONDSX() into a DATETIMEX().
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
//     p1			-- Numeric or floating point
//     p2			-- (Optional) A date, datetime, or datetimex from which to extract the year,month,day
//
//////
// Returns:
//    Datetime		-- Equivalent of SECONDSX() (and optionally the year,month,day input from p2) as a DATETIMEX()
//////
// Example:
//    k = SECONDS()
//    d = DATE()
//    ? SECONDSXTOX(k, d)
//////
	void function_secondsxtox(SThisCode* thisCode, SFunctionParams* rpar)
	{
		// Returns secondsxtox
		ifunction_timesAndDatesConversion_common(thisCode, rpar, _CONVERSION_FUNCTION_SECONDSX, _CONVERSION_FUNCTION_DATETIMEX);
	}




//////////
//
// Function: SET()
// Retrieves current settings
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
//     pString		-- Character, the string to trim
//
//////
// Returns:
//    Character		-- The string with any trailing spaces removed
//////
	void function_set(SThisCode* thisCode, SFunctionParams* rpar)
	{
		SVariable*		varIdentifier	= rpar->ip[0];
		SVariable*		varExtraInfo	= rpar->ip[1];

		s32				lnIndex, lnValue;
		bool			llProcessed;
		SBasePropMap*	baseProp;
		SObjPropMap*	objProp;
		SVariable*		var;
		bool			error;
		u32				errorNum;


		//////////
		// Parameter 1 must be character
		//////
			rpar->rp[0] = NULL;
			if (!iVariable_isValid(varIdentifier) || !iVariable_isTypeCharacter(varIdentifier))
			{
				iError_reportByNumber(thisCode, _ERROR_PARAMETER_IS_INCORRECT, iVariable_getRelatedComp(thisCode, varIdentifier), false);
				return;
			}


		//////////
		// Parameter 2 is ignored for now
		//////



		//////////
		// Locate the indicated setting
		//////
			for (lnIndex = _INDEX_SET_FIRST_ITEM; gsProps_master[lnIndex].index != 0; lnIndex++)
			{
				// Does this setting name match?
				if ((s32)gsProps_master[lnIndex].propNameLength == varIdentifier->value.length && _memicmp(gsProps_master[lnIndex].propName_s8, varIdentifier->value.data_s8, varIdentifier->value.length) == 0)
				{

					//////////
					// This is the setting
					//////
						var = iObjProp_get_variable_byIndex(thisCode, _settings, gsProps_master[lnIndex].index, &baseProp, &objProp);
						if (!var || !baseProp || !objProp)
						{
							// Should never happen, if it does it means something's not setup properly in the properties, or there's a memory corruption
							iError_signal(thisCode, _ERROR_INTERNAL_ERROR, iVariable_getRelatedComp(thisCode, varIdentifier), false, NULL, false);
							return;
						}
						// Note:  var is the actual _settings variable, so a copy must be made if returning this value.


					//////////
					// If they specified a second parameter, it can extract different information
					//////
						llProcessed = false;
						if (iVariable_isValid(varExtraInfo))
						{
							if (iVariable_isTypeNumeric(varExtraInfo))
							{
								// Grab the value
								lnValue = iiVariable_getAs_s32(thisCode, varExtraInfo, false, &error, &errorNum);
								if (error)
								{
									iError_reportByNumber(thisCode, errorNum, iVariable_getRelatedComp(thisCode, varExtraInfo), false);
									return;
								}

								// Find out what they're searching for
								switch (lnValue)
								{
									case 1:
										if (objProp->index == _INDEX_SET_DEVICE)
										{
											// SET("device", 1) ... they want to know the filename if it's SET DEVICE TO FILE
											if (iiVariable_getAs_s32(thisCode, var, false, &error, &errorNum) == _SET_DEVICE_FILE)
											{
												// We have processed into this option
												llProcessed = true;

												// Grab the _INDEX_SET_DEVICE2 entry for its filename
												var = iObjProp_get_variable_byIndex(thisCode, _settings, _INDEX_SET_DEVICE2, &baseProp, &objProp);
												if (!var || !baseProp || !objProp)
												{
													// Should never happen, if it does it means something's not setup properly in the properties, or there's a memory corruption
													iError_signal(thisCode, _ERROR_INTERNAL_ERROR, iVariable_getRelatedComp(thisCode, varIdentifier), false, NULL, false);
													return;
												}
												// Note:  var is the actual _settings variable, so a copy must be made if returning this value.
												rpar->rp[0] = iVariable_copy(thisCode, var, false);
											}
										}
										break;

									case 2:
										// Not currently used, but it is defined
										iError_reportByNumber(thisCode, _ERROR_FEATURE_NOT_AVAILABLE, iVariable_getRelatedComp(thisCode, varExtraInfo), false);
										break;

									case 3:
										// Not currently used, but it is defined
										iError_reportByNumber(thisCode, _ERROR_FEATURE_NOT_AVAILABLE, iVariable_getRelatedComp(thisCode, varExtraInfo), false);
										break;

									case 4:
										// Not currently used, but it is defined
										iError_reportByNumber(thisCode, _ERROR_FEATURE_NOT_AVAILABLE, iVariable_getRelatedComp(thisCode, varExtraInfo), false);
										break;
								}

							} else if (iVariable_isTypeCharacter(varExtraInfo)) {
								// SET("abc", cExpression)
								// Not currently used, but it is defined
								iError_reportByNumber(thisCode, _ERROR_FEATURE_NOT_AVAILABLE, iVariable_getRelatedComp(thisCode, varExtraInfo), false);

							} else {
								iError_reportByNumber(thisCode, _ERROR_SYNTAX, iVariable_getRelatedComp(thisCode, varExtraInfo), false);
								return;
							}
						}


					//////////
					// If there's a getter, translate the actual variable into its displayable form
					//////
						if (!llProcessed)
						{
							if (objProp->_getterObject_get)
							{
								// Get the displayable form
								rpar->rp[0] = objProp->getterObject_get(thisCode, var, iVariable_getRelatedComp(thisCode, varIdentifier), false);

							} else {
								// If we get here, return a copy of the value
								rpar->rp[0] = iVariable_copy(thisCode, var, false);
							}
						}


					//////////
					// Are we good?
					//////
						if (!rpar->rp[0])
							iError_reportByNumber(thisCode, _ERROR_INTERNAL_ERROR, iVariable_getRelatedComp(thisCode, varIdentifier), false);


					//////////
					// Indicate the result
					//////
						return;

				}
			}


		//////////
		// If we get here, we didn't find that setting
		//////
			iError_reportByNumber(thisCode, _ERROR_FEATURE_NOT_AVAILABLE, NULL, false);
	}




//////////
//
// Function: SIGN()
// Returns a numeric value of 1, -1, or 0 if varNumber is positive,
// negative, or 0 value.
//
//////
//
// Function: SIGN2()
// Returns a numeric value of 1 if varNumber >= 0, and -1 otherwise.
//
//////
// Version 0.57
// Last update:
//     Mar.14.2015
//////
// Change log:
//     Mar.15.2015 - Added common() and sign2() functions
//     Mar.14.2015 - Merge into main by Rick C. Hodgin, refactor result to match varNumber varType
//     Mar.14.2015 - Initial creation by Stefano D'Amico
//////
// Parameters:
//     p1			-- Numeric or floating point
//
//////
// Returns:
//    SIGN(n) of the value in p1
//////
// Example:
//    ? sign(2)				&& Displays 1
//    ? sign(-2)			&& Displays -1
//    ? sign(0)				&& Displays 0
//    ? sign(-0.0)			&& Displays 0
//    ? sign(-0.3333)		&& Displays -1
//    ? sign(2.65656)		&& Displays 1
//    ? sign(-2.65656)		&& Displays -1
//////
    void function_sign(SThisCode* thisCode, SFunctionParams* rpar)
    {
		SVariable* varNumber = rpar->ip[0];


		// Return sign -- returns -1, 0, or 1
		ifunction_sign_common(thisCode, rpar, varNumber, false);
	}

	void function_sign2(SThisCode* thisCode, SFunctionParams* rpar)
	{
		SVariable* varNumber = rpar->ip[0];


		// Return sign2 -- returns -1 if non-zero negative, 1 otherwise
		ifunction_sign_common(thisCode, rpar, varNumber, true);
	}

	void ifunction_sign_common(SThisCode* thisCode, SFunctionParams* rpar, SVariable* varNumber, bool tlIncrementZero)
	{
		f64			lfValue;
		bool		error;
		u32			errorNum;
        SVariable*	result;


		//////////
		// Parameter 1 must be numeric
		//////
			rpar->rp[0] = NULL;
			if (!iVariable_isValid(varNumber) || !iVariable_isTypeNumeric(varNumber))
			{
				iError_reportByNumber(thisCode, _ERROR_PARAMETER_IS_INCORRECT, iVariable_getRelatedComp(thisCode, varNumber), false);
				return;
			}


		//////////
		// Parameter 1, Convert to f64
		//////
			lfValue = iiVariable_getAs_f64(thisCode, varNumber, false, &error, &errorNum);
			if (error)
			{
				iError_reportByNumber(thisCode, errorNum, iVariable_getRelatedComp(thisCode, varNumber), false);
				return;
			}


		//////////
		// Create output variable
		//////
			if (propGet_settings_ncset_signSign2(_settings))
			{
				// They want it to be the input type if possible
				result = iVariable_create(thisCode, varNumber->varType, NULL, true);

			} else {
				// Always an integer return value
				result = iVariable_create(thisCode, _VAR_TYPE_S32, NULL, true);
			}
			if (!result)
			{
				iError_reportByNumber(thisCode, errorNum, iVariable_getRelatedComp(thisCode, varNumber), false);
				return;
			}


		//////////
		// Compute sign
		//////
			if (lfValue != 0.0)
			{
				// Converting of lfValue to 1 or -1
				lfValue = lfValue / abs(lfValue);

			} else if (tlIncrementZero) {
				// Should we increment a 0 value (so it will be returned as 1 instead of 0)?
				++lfValue;
			}


		//////////
		// Set the value
		//////
			if (!iVariable_setNumeric_toNumericType(thisCode, result, NULL, &lfValue, NULL, NULL, NULL, NULL))
				iError_reportByNumber(thisCode, errorNum, iVariable_getRelatedComp(thisCode, varNumber), false);


		//////////
        // Return sign
		//////
			rpar->rp[0] = result;

    }




//////////
//
// Function: SIN()
// Returns the sine of an angle.
//
//////
// Version 0.57
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
//    SIN(n) of the value in p1
//////
// Example:
//    ? SIN(0)		&& Display 0.00
//////
    void function_sin(SThisCode* thisCode, SFunctionParams* rpar)
    {
		SVariable* varNumber = rpar->ip[0];


		// Return sin
		ifunction_numbers_common(thisCode, rpar, varNumber, NULL, NULL, _FP_COMMON_SIN, _VAR_TYPE_F64, false, false);
	}




//////////
//
// Function: SLICE()
// Extracts a portion of a string.
//
//////
// Version 0.57
// Last update:
//     Mar.22.2015
//////
// Change log:
//     Mar.22.2015 - Initial creation, proposed by Stefano D'Amico.
//////
// Parameters:
//     varString	-- The string to slice into.
//     varStart		-- The offset to start the slice.  If negative, then backs off from LEN(varString).
//     varEnd		-- The offset to end at.  If negative, then backs off from LEN(varString).
//
//////
// Returns:
//    Character		-- The string which was extracted.
//////
	void function_slice(SThisCode* thisCode, SFunctionParams* rpar)
	{
//		SVariable* varString	= rpar->params[0];
//		SVariable* varStart		= rpar->params[1];
//		SVariable* varEnd		= rpar->params[2];


		// Not yet completed
		iError_reportByNumber(thisCode, _ERROR_FEATURE_NOT_AVAILABLE, NULL, false);
		rpar->rp[0] = NULL;
	}




//////////
//
// Function: SPACE()
// Creates a character variable initialized with spaces.
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
//     pCount		-- The number of spaces to populate
//
//////
// Returns:
//    Character		-- The string with any leading and trailing spaces removed
//////
	void function_space(SThisCode* thisCode, SFunctionParams* rpar)
	{
		SVariable*	varCount = rpar->ip[0];
		s32			lnLength;
		u32			errorNum;
		bool		error;
        SVariable*	result;


		//////////
		// Parameter 1 must be numeric
		//////
			rpar->rp[0] = NULL;
			if (!iVariable_isValid(varCount) || !iVariable_isTypeNumeric(varCount))
			{
				iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_getRelatedComp(thisCode, varCount), false);
				return;
			}


		//////////
        // Find out how long they want our string to be
		//////
			lnLength = iiVariable_getAs_s32(thisCode, varCount, false, &error, &errorNum);
			if (error)
			{
				iError_reportByNumber(thisCode, errorNum, iVariable_getRelatedComp(thisCode, varCount), false);
				return;
			}


		//////////
        // Create our return result
		//////
			result = iVariable_create(thisCode, _VAR_TYPE_CHARACTER, NULL, true);
			if (!result)
			{
				iError_report(thisCode, cgcInternalError, false);
				return;
			}


		//////////
        // Create the source string and initialize to spaces
		//////
	        iDatum_allocateSpace(&result->value, lnLength);
			memset(result->value.data, 32, lnLength);


		//////////
        // Return our converted result
		//////
			rpar->rp[0] = result;

	}




//////////
//
// Function: SQRT()
// Returns the square root of the specified numeric expression.
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
//     varNumber	-- Numeric or floating point
//
//////
// Returns:
//    SQRT(n) of the value in p1
//////
// Example:
//    ? SQRT(2)		&& Display 1.41
//    ? SQRT(2.0)	&& Display 1.41
//    ? SQRT(-2)	&& Error: argument cannot be negative
//////
    void function_sqrt(SThisCode* thisCode, SFunctionParams* rpar)
	{
		SVariable* varNumber = rpar->ip[0];


		// Return sqrt
		ifunction_numbers_common(thisCode, rpar, varNumber, NULL, NULL, _FP_COMMON_SQRT, _VAR_TYPE_F64, false, false);
	}




//////////
//
// Function: STARTSWITH()
// Determines if the character string starts with the search string.
//
//////
// Version 0.57   (Determine the current version from the header in vjr.cpp)
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
//
//////
// Returns:
//    Logical		-- .t. if the search string is found in the string, .f. otherwise
//
//////
	void function_startswith(SThisCode* thisCode, SFunctionParams* rpar)
	{
		SVariable* varString	= rpar->ip[0];
//		SVariable* varSearch	= rpar->params[1];
//		SVariable* varStart		= rpar->params[2];


		// Not yet completed
		iError_reportByNumber(thisCode, _ERROR_FEATURE_NOT_AVAILABLE, iVariable_getRelatedComp(thisCode, varString), false);
		rpar->rp[0] = NULL;
	}




//////////
//
// Function: STARTSWITHC()
// Case-insensitive version of STARTSWITH().
//
//////
	void function_startswithc(SThisCode* thisCode, SFunctionParams* rpar)
	{
		SVariable* varString	= rpar->ip[0];
//		SVariable* varSearch	= rpar->params[1];
//		SVariable* varStart		= rpar->params[2];


		// Not yet completed
		iError_reportByNumber(thisCode, _ERROR_FEATURE_NOT_AVAILABLE, iVariable_getRelatedComp(thisCode, varString), false);
		rpar->rp[0] = NULL;
	}




//////////
//
// Function: STRTRAN()
// Converts the matching portions of the string from one form to another.
//
//////
// Version 0.57   (Determine the current version from the header in vjr.cpp)
// Last update:
//     Aug.21.2014
//////
// Change log:
//     Aug.21.2014 - Initial creation
//////
// Parameters:
//     pString			-- Original string
//     pSearch			-- Search string to replace
//     pReplace			-- String to replace with
//     pRecursiveCount	-- How many times should we recursively parse this string?
//
//////
// Returns:
//    Character		-- The original string with all components replaced
//
//////
	void function_strtran(SThisCode* thisCode, SFunctionParams* rpar)
	{
		SVariable* varString			= rpar->ip[0];
		SVariable* varSearch			= rpar->ip[1];
		SVariable* varReplace			= rpar->ip[2];
		SVariable* varRecursiveCount	= rpar->ip[3];


		// Return strtran
		ifunction_strtran_common(thisCode, rpar, varString, varSearch, varReplace, varRecursiveCount, true);
	}

	void function_strtranc(SThisCode* thisCode, SFunctionParams* rpar)
	{
		SVariable* varString			= rpar->ip[0];
		SVariable* varSearch			= rpar->ip[1];
		SVariable* varReplace			= rpar->ip[2];
		SVariable* varRecursiveCount	= rpar->ip[3];


		// Return strtranc
		ifunction_strtran_common(thisCode, rpar, varString, varSearch, varReplace, varRecursiveCount, false);
	}

	void ifunction_strtran_common(SThisCode* thisCode, SFunctionParams* rpar, SVariable* varString, SVariable* varSearch, SVariable* varReplace, SVariable* varRecursiveCount, bool tlCaseSensitive)
	{
		s32			lnI, lnIteration, lnSrc, lnDst, lnLength, lnRecursiveCount, lnFoundCount;
		bool		error;
		u32			errorNum;
        SVariable*	result;
		SVariable*	resultNew;


		//////////
		// Parameter 1 must be character
		//////
			rpar->rp[0] = NULL;
			if (!iVariable_isValid(varString) || !iVariable_isTypeCharacter(varString))
			{
				iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_getRelatedComp(thisCode, varString), false);
				return;
			}


		//////////
		// Parameter 2 must be character
		//////
			if (!iVariable_isValid(varSearch) || !iVariable_isTypeCharacter(varSearch))
			{
				iError_reportByNumber(thisCode, _ERROR_P2_IS_INCORRECT, iVariable_getRelatedComp(thisCode, varSearch), false);
				return;
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
				return;
			}


		//////////
		// Parameter 4 is optional, but must be numeric if present
		//////
			if (!iVariable_isValid(varRecursiveCount))
			{
				// They didn't provide a 3rd parameter, so we'll use a pseudo placeholder which is an empty string
				lnRecursiveCount = 1;

			} else if (!iVariable_isTypeNumeric(varRecursiveCount)) {
				// It is invalid
				iError_reportByNumber(thisCode, _ERROR_P4_IS_INCORRECT, iVariable_getRelatedComp(thisCode, varRecursiveCount), false);
				return;

			} else {
				// Grab the actual value
				lnRecursiveCount = iiVariable_getAs_s32(thisCode, varRecursiveCount, false, &error, &errorNum);
				if (error)
				{
					iError_reportByNumber(thisCode, errorNum, iVariable_getRelatedComp(thisCode, varRecursiveCount), false);
					return;
				}

				if (lnRecursiveCount < 0)
				{
					// It is invalid
					iError_reportByNumber(thisCode, _ERROR_P4_IS_INCORRECT, iVariable_getRelatedComp(thisCode, varRecursiveCount), false);
					return;
				}
			}


		//////////
		// If we aren't searching for anything, we don't need to go through the rigmarole
		//////
			// If the original string is empty, or the characters to search for are empty, then we don't need to do anything
			if (varSearch->value.length == 0 || varSearch->value.length > varString->value.length)
			{
				// Allocate a full copy of the original string
				rpar->rp[0] = iVariable_createAndPopulate_byText(thisCode, _VAR_TYPE_CHARACTER, varString->value.data_u8, varString->value.length, false);
				return;
			}


		//////////
		// Iterate through the string twice, the first to determine how long the destination will be, the second to copy
		//////
			for (lnIteration = 1, result = varString; lnRecursiveCount == 0 || lnIteration <= lnRecursiveCount; lnIteration++)
			{
				// Search for any matches, and determine the overall length
				for (lnI = 0, lnFoundCount = 0; lnI < result->value.length - varSearch->value.length; )
				{
					// See if this matches the source string
					if (tlCaseSensitive)
					{
						// Case-sensitive compare
						if (memcmp(result->value.data + lnI, varSearch->value.data, varSearch->value.length) == 0)
						{
							// We found a match
							++lnFoundCount;
							lnI += varSearch->value.length;

						} else {
							// Skip to the next character
							++lnI;
						}

					} else {
						// Case-insensitive compare
						if (_memicmp(result->value.data + lnI, varSearch->value.data, varSearch->value.length) == 0)
						{
							// We found a match
							++lnFoundCount;
							lnI += varSearch->value.length;

						} else {
							// Skip to the next character
							++lnI;
						}
					}
				}

				// If we didn't find any, we're done
				if (lnFoundCount == 0)
				{
					// If we haven't made an official copy yet, we need to do so now
					if (result == varString)
						result = iVariable_createAndPopulate_byText(thisCode, _VAR_TYPE_CHARACTER, varString->value.data_u8, varString->value.length, false);

					// Return our result
					rpar->rp[0] = result;
					return;
				}

				// When we get here, we have a new length for our copy
				lnLength = result->value.length - (lnFoundCount * varSearch->value.length) + (lnFoundCount * varReplace->value.length);

				// Allocate a new string of that length
				resultNew = iVariable_create(thisCode, _VAR_TYPE_CHARACTER, NULL, true);
				iDatum_allocateSpace(&resultNew->value, lnLength);

				// Copy the content
				for (lnSrc = 0, lnDst = 0; lnSrc < result->value.length; )
				{
					// See if this matches the source string
					if (tlCaseSensitive)
					{
						// Case-sensitive compare
						if (memcmp(result->value.data + lnSrc, varSearch->value.data, varSearch->value.length) == 0)
						{
							// We found a match
							memcpy(resultNew->value.data + lnDst, varReplace->value.data, varReplace->value.length);
							lnSrc += varSearch->value.length;
							lnDst += varReplace->value.length;

						} else {
							// Skip to the next character
							resultNew->value.data[lnDst] = result->value.data[lnSrc];
							++lnDst;
							++lnSrc;
						}

					} else {
						// Case-insensitive compare
						if (_memicmp(result->value.data + lnSrc, varSearch->value.data, varSearch->value.length) == 0)
						{
							// We found a match
							memcpy(resultNew->value.data + lnDst, varReplace->value.data, varReplace->value.length);
							lnSrc += varSearch->value.length;
							lnDst += varReplace->value.length;

						} else {
							// Skip to the next character
							resultNew->value.data[lnDst] = result->value.data[lnSrc];
							++lnDst;
							++lnSrc;
						}
					}
				}

				// Delete our original (if it wasn't pointing to our source string)
				if (result != varString)
					iVariable_delete(thisCode, result, true);

				// Set the new to our result
				result = resultNew;
				// Continue on for the next iteration
			}


		//////////
		// Return our final string
		/////
			rpar->rp[0] = result;

	}




//////////
//
// Function: STUFF()
// Returns a string which has been modified, having optionally some characters optionally removed, some optionally inserted.
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
//     pOriginalString		-- Input string
//     pStartPos			-- Starting position
//     pNumToRemove			-- Number of characters to remove
//     pStuffString			-- String to insert there
//
//////
// Returns:
//    Character		-- String has been modified as per the STUFF() function.
//
//////
	void function_stuff(SThisCode* thisCode, SFunctionParams* rpar)
	{
		SVariable*	varOriginalString	= rpar->ip[0];
		SVariable*	varStartPos			= rpar->ip[1];
		SVariable*	varNumToRemove		= rpar->ip[2];
		SVariable*	varStuffString		= rpar->ip[3];
		s32			lnStartPosition, lnRemoveCount, lnBufferLength;
		bool		error;
		u32			errorNum;
		u8*			lcBuffer;
		SVariable*	result;


		//////////
		// Parameter 1 must be character
		//////
			rpar->rp[0] = NULL;
			if (!iVariable_isValid(varOriginalString) || !iVariable_isTypeCharacter(varOriginalString))
			{
				iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_getRelatedComp(thisCode, varOriginalString), false);
				return;
			}


		//////////
		// Parameter 2 must be numeric
		//////
			if (!iVariable_isValid(varStartPos) || !iVariable_isTypeNumeric(varStartPos))
			{
				iError_reportByNumber(thisCode, _ERROR_P2_IS_INCORRECT, iVariable_getRelatedComp(thisCode, varStartPos), false);
				return;
			}


		//////////
		// Parameter 3 must be numeric
		//////
			if (!iVariable_isValid(varNumToRemove) || !iVariable_isTypeNumeric(varNumToRemove))
			{
				iError_reportByNumber(thisCode, _ERROR_P3_IS_INCORRECT, iVariable_getRelatedComp(thisCode, varNumToRemove), false);
				return;
			}


		//////////
		// Parameter 4 must be character
		//////
			if (!iVariable_isValid(varStuffString) || !iVariable_isTypeCharacter(varStuffString))
			{
				iError_reportByNumber(thisCode, _ERROR_P4_IS_INCORRECT, iVariable_getRelatedComp(thisCode, varStuffString), false);
				return;
			}


		//////////
		// Grab the parameters as usable values
		//////
			// Your algorithm code goes here
			lnStartPosition	= iiVariable_getAs_s32(thisCode, varStartPos, false, &error, &errorNum);
			lnRemoveCount	= iiVariable_getAs_s32(thisCode, varNumToRemove, false, &error, &errorNum);


		//////////
		// If they are trying to do negative things, report it
		//////
			if (lnStartPosition < 1)		lnStartPosition		= 1;
			if (lnRemoveCount   < 0)		lnRemoveCount		= 0;


		//////////
		// Adjust them based on real-world observations from the string
		//////
			// Are they trying to start beyond the end of the string?  If so, reduce to the end.
			if (lnStartPosition > varOriginalString->value.length)
				lnStartPosition = varOriginalString->value.length + 1;

			// Are they trying to remove more than can be extracted?
			if (lnStartPosition - 1 + lnRemoveCount > varOriginalString->value.length)
				lnRemoveCount = varOriginalString->value.length - lnStartPosition + 1;


		//////////
		// Construct our destination
		//////
			lnBufferLength	= varOriginalString->value.length - lnRemoveCount + varStuffString->value.length;
			lcBuffer = (u8*)malloc(lnBufferLength);
			if (!lcBuffer)
			{
				iError_reportByNumber(thisCode, _ERROR_OUT_OF_MEMORY, NULL, false);
				return;
			}

			// Copy the first part of the original string, plus the stuffed in part, plus the end of the last part of the original string
			--lnStartPosition;

			// We only copy the first part if there is something to copy
			if (lnStartPosition > 0)
				memcpy((s8*)lcBuffer, varOriginalString->value.data, lnStartPosition);

			// We only insert our stuff string if there is something to put there
			if (varStuffString->value.length > 0)
				memcpy((s8*)lcBuffer + lnStartPosition, varStuffString->value.data, varStuffString->value.length);

			// We only copy over the last part if there's something there
			if (varOriginalString->value.length - lnStartPosition - lnRemoveCount > 0)
				memcpy((s8*)lcBuffer + lnStartPosition + varStuffString->value.length, varOriginalString->value.data + lnStartPosition + lnRemoveCount, varOriginalString->value.length - lnStartPosition - lnRemoveCount);


		//////////
        // Create the return(result)
		//////
	        result = iVariable_create(thisCode, _VAR_TYPE_CHARACTER, NULL, true);
			if (!result)
			{
				iError_report(thisCode, (u8*)"Internal error.", false);
				return;
			}


		//////////
        // Populate the return value
		//////
			iDatum_duplicate(&result->value, lcBuffer, lnBufferLength);


		//////////
		// Release the temporary buffer
		//////
			free(lcBuffer);


		//////////
        // Return our converted result
		//////
			rpar->rp[0] = result;

	}




//////////
//
// Function: SYS()
// SYS function support (Dec.27.2014 incomplete)
//
///////
// Version 0.57
// Last update:
//     Apr.08.2015
//////
// Change log:
//	   Apr.08.2015 - SYS(10) added by Stefano D'Amico
//	   Apr.08.2015 - SYS(2) added by Stefano D'Amico
//	   Apr.08.2015 - SYS(1) added by Stefano D'Amico
//     Dec.27.2014 - Initial creation
//////
// Parameters:
//		1				-- none
//		2				-- none
//		10				-- Numeric, julian day number
//		2015			-- none
//////
// Returns:
//		1				-- Character, returns the current system date as a Julian day number character string
//		2				-- Numeric, returns the number of seconds elapsed since midnight
//		10				-- Character, returns a Character-type date from a Julian day number
//		2015			-- Character, unique procedure name
//////
	void function_sys(SThisCode* thisCode, SFunctionParams* rpar)
	{
		SVariable*	varIndex	= rpar->ip[0];
		SVariable*	varP1		= rpar->ip[1];
		SVariable*	varP2		= rpar->ip[2];
		s32			lnIndex;
		f32			lfJulian;
		u32			lnYear, lnMonth, lnDay;
		s8			buffer[64];
		s8			curdir[_MAX_PATH];
		u32			lnExtraPrefixWidth, lnExtraPostfixWidth;
		s64			ln2015;
		u32			errorNum;
        bool		error;
		SYSTEMTIME	lst;
		SVariable*	varTemp;
		SVariable*	result;


// TODO:  Untested function, breakpoint and examine
// debug_break;
		//////////
		// Parameter 1 must be numeric
		//////
			rpar->rp[0] = NULL;
			if (!iVariable_isValid(varIndex) || !iVariable_isTypeNumeric(varIndex))
			{
				iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_getRelatedComp(thisCode, varIndex), false);
				return;
			}

			// Grab the index
			lnIndex = iiVariable_getAs_s32(thisCode, varIndex, false, &error, &errorNum);
			if (error)
			{
				// An error extracting the value (should never happen)
				iError_reportByNumber(thisCode, errorNum, iVariable_getRelatedComp(thisCode, varIndex), false);
				return;
			}


		//////////
		// Based on the function...
		//////
			switch (lnIndex)
			{
				// SYS(1) -- Current system date as a Julian day number character string
				case 1:
					//////////
					// Get the current time
					//////
						if (_settings)		iTime_getLocalOrSystem(&lst, propGet_settings_TimeLocal(_settings));
						else				GetLocalTime(&lst);


					//////////
					// Convert to julian
					//////
						iiDateMath_get_julian_from_YyyyMmDd(&lfJulian, lst.wYear, lst.wMonth, lst.wDay);
						sprintf(buffer, "%d\0", (s32)lfJulian);


					//////////
					// Create our result and exit to report any errors
					//////
						result = iVariable_createAndPopulate_byText(thisCode, _VAR_TYPE_CHARACTER, (cs8*)buffer, (u32)strlen(buffer), false);
						goto clean_exit;


				// SYS(2) -- Number of seconds elapsed since midnight
				case 2:
					//////////
					// Grab seconds()
					//////
						function_seconds(thisCode, rpar);
						result = rpar->rp[0];
						if (result)
						{
							// Validation (should not be needed, but just to be safe)
							if (result->varType == _VAR_TYPE_F64)
							{
								// Convert f64 to s64
								*result->value.data_s64	= (s64)*result->value.data_f64;
								result->varType			= _VAR_TYPE_S64;

								// Report any errors
								goto clean_exit;

							} else {
								// This should never happen
								// It indicates refactoring was done on function_seconds() to change the size of the return value from f64 to something else
								debug_break;
							}
						}


				//////////
				// SYS(3) -- Legal filename
				// case 3: -- In VJr, is same as SYS(2015), so please see SYS(2015) below, or search for "case 3:" and find the next instance
				//////////


				// SYS(5) -- Equivalent of JUSTDRIVE(CURDIR())
				case 5:
					//////////
					// Get the current directory and populate
					//////
						memset(curdir, 0, sizeof(curdir));
						GetCurrentDirectory(_MAX_PATH, curdir);
						result = iVariable_createAndPopulate_byText(thisCode, _VAR_TYPE_CHARACTER, curdir, 2, false);
						goto clean_exit;


				// SYS(10) -- Julian string from day number
				case 10:
					//////////
					// Parameter 1 must be numeric
					//////
						if (!iVariable_isValid(varP1) || !iVariable_isTypeNumeric(varP1))
						{
							iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_getRelatedComp(thisCode, varP1), false);
							return;
						}


					//////////
					// Grab julian number
					//////
						lfJulian = iiVariable_getAs_f32(thisCode, varP1, false, &error, &errorNum);
						if (error)
						{
							iError_reportByNumber(thisCode, errorNum, iVariable_getRelatedComp(thisCode, varP1), false);
							return;
						}


					//////////
					// Must be in the range -- Sep.14.1752 to Dec.31.9999
					//////
						if (lfJulian < 2361222/*Sep.14.1752*/ || lfJulian > 5373484/*Dec.31.9999*/)
						{
							// For these values, return a blank date
							result = iVariable_create(thisCode, _VAR_TYPE_DATE, NULL, true);
							if (result)
								memset(result->value.data, 32, result->value.length);	// Make it all spaces

							// Check our result
							goto clean_exit;
						}


					//////////
					// Translate into standard year, month, day
					//////
						iiDateMath_get_YyyyMmDd_from_julian((u32)lfJulian, &lnYear, &lnMonth, &lnDay);


					//////////
					// Convert julian date into a VJr date variable
					//////
						// Date is stored as YYYYMMDD
						iiDateMath_get_YYYYMMDD_from_YyyyMmDd(buffer, lnYear, lnMonth, lnDay);
						varTemp = iVariable_createAndPopulate_byText(thisCode, _VAR_TYPE_DATE, buffer, 8, false);
						if (!varTemp)
						{
							// Fatal error
							iError_reportByNumber(thisCode, _ERROR_INTERNAL_ERROR, NULL, false);
							return;
						}


					//////////
					// Create and populate the return variable
					//////
						result = iVariable_convertForDisplay(thisCode, varTemp);


					//////////
					// Clean house and exit to report any errors
					//////
						iVariable_delete(thisCode, varTemp, true);
						goto clean_exit;


				// SYS(2003) -- Equivalent of SUBSTR(CURDIR(), 3, LEN(CURDIR()) - 3) (supresses the drive and backslash final)
				case 2003:
					//////////
					// Get the current directory and populate
					// Note:  GetCurrentDirectory() does not include the trailing backslash
					//////
						memset(curdir, 0, sizeof(curdir));
						GetCurrentDirectory(_MAX_PATH, curdir);
						result = iVariable_createAndPopulate_byText(thisCode, _VAR_TYPE_CHARACTER, curdir + 2, (s32)strlen(curdir + 2), false);
						goto clean_exit;


				// SYS(3)		-- Legal filename
				// SYS(2015)	-- Unique procedure name
				case 3:
				case 2015:
					// Unique procedure names take on the form YYYYMMDDHHMMSSmmm converted to base-36, prefixed with an underscore
					if (_settings)		iTime_getLocalOrSystem(&lst, propGet_settings_TimeLocal(_settings));
					else				GetLocalTime(&lst);

					// Create a single large integer
					ln2015 =	((s64)lst.wYear		* 10000000000000) +
								((s64)lst.wMonth	* 100000000000) +
								((s64)lst.wDay		* 1000000000) +
								((s64)lst.wHour		* 10000000) +
								((s64)lst.wMinute	* 100000) +
								((s64)lst.wSecond	* 1000) +
								 (s64)lst.wMilliseconds;

					// Optional 2nd and 3rd parameter indicate how many extra prefix and postfix characters to insert
					if (iVariable_isValid(varP1))
					{
						//////////
						// Since P1 was provided, it must be numeric
						//////
							if (!iVariable_isTypeNumeric(varP1))
							{
								iError_reportByNumber(thisCode, _ERROR_P2_IS_INCORRECT, iVariable_getRelatedComp(thisCode, varP1), false);
								goto clean_exit;
							}


						//////////
						// Get the prefix width
						//////
							lnExtraPrefixWidth = iiVariable_getAs_s32(thisCode, varP1, false, &error, &errorNum);
							if (error)
							{
								iError_reportByNumber(thisCode, errorNum, iVariable_getRelatedComp(thisCode, varP1), false);
								goto clean_exit;
							}
							// Right now, we have lnExtraPrefixWidth


						/////////
						// Did they also provide a 3rd parameter?
						//////
							if (iVariable_isValid(varP2))
							{
								//////////
								// Since P2 was provided, it must be numeric
								//////
									if (!iVariable_isTypeNumeric(varP2))
									{
										iError_reportByNumber(thisCode, _ERROR_P2_IS_INCORRECT, iVariable_getRelatedComp(thisCode, varP2), false);
										goto clean_exit;
									}


								//////////
								// Get the postfix width
								//////
									lnExtraPostfixWidth = iiVariable_getAs_s32(thisCode, varP2, false, &error, &errorNum);
									if (error)
									{
										iError_reportByNumber(thisCode, errorNum, iVariable_getRelatedComp(thisCode, varP2), false);
										goto clean_exit;
									}
									// Right now, we have lnExtraPostfixWidth

							} else {
								// Nope, just assign it to 0
								lnExtraPostfixWidth = 0;
							}

					} else {
						lnExtraPrefixWidth	= 0;
						lnExtraPostfixWidth	= 0;
					}

					// Create a variable in base-36 (uses 0..9, A..Z)
					result = iVariable_createByRadix(thisCode, ln2015, 36, 1 + lnExtraPrefixWidth, lnExtraPostfixWidth);

					// Prefix with an underscore
					if (result)
						result->value.data_u8[lnExtraPrefixWidth] = '_';

					// Right now, the variable looks something like:  _19B2L483
					break;


				// SYS(2023) -- Temporary path
				case 2023:
					//////////
					// Get the temporary path
					//////
						memset(curdir, 0, sizeof(curdir));
						GetTempPath(sizeof(curdir), curdir);
						result = iVariable_createAndPopulate_byText(thisCode, _VAR_TYPE_CHARACTER, curdir, (s32)strlen(curdir), false);
						goto clean_exit;


				// Unknown
				default:
					// Not currently supported
					iError_reportByNumber(thisCode, _ERROR_FEATURE_NOT_AVAILABLE, iVariable_getRelatedComp(thisCode, varIndex), false);
					return;
			}

clean_exit:
		//////////
		// Are we good?
		//////
			if (!result)
				iError_reportByNumber(thisCode, _ERROR_INTERNAL_ERROR, NULL, false);


		//////////
		// Indicate our result
		//////
			rpar->rp[0] = result;

	}

	// Note:  Helper function.  iFunction_sys2015() is a shortcut function for accessing the oft-used get-unique-procedure-name feature
	SVariable* iFunction_sys2015(SThisCode* thisCode, u32 tnPrefixWidth, u32 tnPostfixWidth)
	{
		s32				ln2015;
		SVariable*		varSys2015;
		SFunctionParams	lsrpar;


// TODO:  Untested function, breakpoint and examine
debug_break;
		//////////
		// Setup the function call variables
		//////
			memset(&lsrpar, 0, sizeof(lsrpar));
			ln2015 = 2015;
			lsrpar.ip[0/*2015*/]		= iVariable_createAndPopulate_byText(thisCode, _VAR_TYPE_S32,	(cu8*)&ln2015,			sizeof(ln2015),			false);
			lsrpar.ip[1/*prefix*/]	= iVariable_createAndPopulate_byText(thisCode, _VAR_TYPE_S32,	(cu8*)&tnPrefixWidth,	sizeof(tnPrefixWidth),	false);
			lsrpar.ip[2/*postfix*/]	= iVariable_createAndPopulate_byText(thisCode, _VAR_TYPE_S32,	(cu8*)&tnPostfixWidth,	sizeof(tnPostfixWidth), false);


		//////////
		// Call the function
		//////
			function_sys(thisCode, &lsrpar);
			varSys2015 = lsrpar.rp[0];


		//////////
		// Clean house
		//////
			iVariable_delete(thisCode, lsrpar.ip[0], true);
			iVariable_delete(thisCode, lsrpar.ip[1], true);
			iVariable_delete(thisCode, lsrpar.ip[2], true);


		//////////
		// Return our value
		//////
			return(varSys2015);
	}




//////////
//
// Function: SYSMETRIC()
// Based on the index, returns a wide array of information.
//
//////
// Version 0.57
// Last update:
//     Jul.13.2014
//////
// Change log:
//     Jul.13.2014 - Initial creation
//////
// Parameters:
//     pIndex		-- Numeric, in the range 1..34
//
//////
// Returns:
//    Numeric		-- Depending on index, various value ranges are returned
//////
    void function_sysmetric(SThisCode* thisCode, SFunctionParams* rpar)
    {
		SVariable*	varIndex = rpar->ip[0];
        s32			index;
		RECT		lrc;
		u32			errorNum;
        bool		error;
        SVariable*	result;


		//////////
		// Parameter 1 must be numeric
		//////
			rpar->rp[0] = NULL;
			if (!iVariable_isValid(varIndex) || !iVariable_isTypeNumeric(varIndex))
			{
				iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_getRelatedComp(thisCode, varIndex), false);
				return;
			}


		//////////
        // It must be in the range 1..34
		//////
			index = iiVariable_getAs_s32(thisCode, varIndex, false, &error, &errorNum);
			if (error)
			{
				iError_reportByNumber(thisCode, errorNum, iVariable_getRelatedComp(thisCode, varIndex), false);
				return;

			} else if (index > 34 || index < 1) {
				// We report our own error
				iError_report(thisCode, (cu8*)"Parameter must be in the range 1..34", false);
				return;
			}


		//////////
        // Create our return result
		//////
	        result = iVariable_create(thisCode, _VAR_TYPE_S32, NULL, true);
			if (!result)
			{
				iError_report(thisCode, cgcInternalError, false);
				return;
			}


		//////////
        // Populate the result with its sysmetric()
		//////
			GetWindowRect(GetDesktopWindow(), &lrc);
			switch (index)
			{
				case 1:
					// Screen width
					*(s32*)result->value.data = (lrc.right - lrc.left);
					break;

				case 2:
					// Screen height
					*(s32*)result->value.data = (lrc.bottom - lrc.top);
					break;

				case 3:
					// Width of a sizable window frame
					*(s32*)result->value.data = bmpVjrIcon->bi.biWidth;
					break;

				case 4:
					// Height of a sizable window frame
					*(s32*)result->value.data = bmpVjrIcon->bi.biHeight;
					break;

				case 5:
					// Width of scroll arrows on a vertical scroll bar
					*(s32*)result->value.data = 0;
					break;

				case 6:
					// Height of scroll arrows on a vertical scroll bar
					*(s32*)result->value.data = 0;
					break;

				case 7:
					// Width of scroll arrows on a horizontal scroll bar
					*(s32*)result->value.data = 0;
					break;

				case 8:
					// Height of scroll arrows on a horizontal scroll bar
					*(s32*)result->value.data = 0;
					break;

				case 9:
					// Height of form caption
					*(s32*)result->value.data = bmpVjrIcon->bi.biHeight;
					break;

				case 10:
					// Width of non-sizable window frame
					*(s32*)result->value.data = bmpVjrIcon->bi.biWidth;
					break;

				case 11:
					// Height of a non-sizable window frame
					*(s32*)result->value.data = bmpVjrIcon->bi.biHeight;
					break;

				case 12:
					// Width of a double or panel window frame
					*(s32*)result->value.data = bmpVjrIcon->bi.biWidth;
					break;

				case 13:
					// Height of a double or panel window frame
					*(s32*)result->value.data = bmpVjrIcon->bi.biHeight;
					break;

				case 14:
					// Scroll box width on horizontal scroll bars in text editing windows
					*(s32*)result->value.data = 0;
					break;

				case 15:
					// Scroll box height on horizontal scroll bars in text editing windows
					*(s32*)result->value.data = 0;
					break;

				case 16:
					// Minimized window icon width
					*(s32*)result->value.data = bmpVjrIcon->bi.biWidth;
					break;

				case 17:
					// Minimized window icon height
					*(s32*)result->value.data = bmpVjrIcon->bi.biHeight;
					break;

				case 18:
					// Maximum insertion point width
					*(s32*)result->value.data = 0;
					break;

				case 19:
					// Maximum insertion point height
					*(s32*)result->value.data = 0;
					break;

				case 20:
					// Single-line menu bar height
					*(s32*)result->value.data = _MENU_BAR_HEIGHT;
					break;

				case 21:
					// Maximized window width
					*(s32*)result->value.data = (lrc.right - lrc.left);
					break;

				case 22:
					// Maximized window height
					*(s32*)result->value.data = (lrc.bottom - lrc.top);
					break;

				case 23:
					// Kanji window height
					*(s32*)result->value.data = ((GetSystemMetrics(SM_CYKANJIWINDOW) != 0) ? 1 : 0);
					break;

				case 24:
					// Minimum sizable window width
					*(s32*)result->value.data = 2 * bmpVjrIcon->bi.biWidth;
					break;

				case 25:
					// Minimum sizable window height
					*(s32*)result->value.data = 2 * bmpVjrIcon->bi.biHeight;
					break;

				case 26:
					// Minimum window width
					*(s32*)result->value.data = 2 * bmpVjrIcon->bi.biWidth;
					break;

				case 27:
					// Minimum window height
					*(s32*)result->value.data = 2 * bmpVjrIcon->bi.biHeight;
					break;

				case 28:
					// Window controls width
					*(s32*)result->value.data = 2 * bmpClose->bi.biWidth;
					break;

				case 29:
					// Window controls height
					*(s32*)result->value.data = 2 * bmpClose->bi.biHeight;
					break;

				case 30:
					// 1 if mouse hardware present, 0 otherwise
					*(s32*)result->value.data = ((GetSystemMetrics(SM_MOUSEPRESENT) != 0) ? 1 : 0);
					break;

				case 31:
					// 1 for Microsoft Windows debugging version, 0 otherwise
					*(s32*)result->value.data = ((GetSystemMetrics(SM_DEBUG) != 0) ? 1 : 0);
					break;

				case 32:
					// 1 if mouse buttons are swapped, 0 otherwise
					*(s32*)result->value.data = ((GetSystemMetrics(SM_SWAPBUTTON) != 0) ? 1 : 0);
					break;

				case 33:
					// width of a button in a half-height title bar
					*(s32*)result->value.data = bmpClose->bi.biWidth;
					break;

				case 34:
					// Height of half-height caption area
					*(s32*)result->value.data = bmpClose->bi.biHeight;
					break;

			}


		//////////
        // Return our converted result
		//////
			rpar->rp[0] = result;

    }
