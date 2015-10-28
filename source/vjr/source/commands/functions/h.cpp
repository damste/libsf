//////////
//
// /libsf/source/vjr/commands/funcs/h.cpp
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
// Function: HOUR()
// Returns the hour portion from a DateTime expression.
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
//     varParam		-- Specifies a DateTime expression from which HOUR( ) returns the hour
//
//////
// Returns:
//    HOUR( ) returns a numeric value based on a 24 hour format.
//////
	void function_hour(SFunctionParams* rpar)
	{
		SVariable*	varParam	= rpar->ip[0];


		// Return hour
		ifunction_hhmmss_common(rpar, varParam, _HMS_COMMON_HOUR);
	}

	void ifunction_hhmmss_common(SFunctionParams* rpar, SVariable* varParam, u32 tnFunctionType)
	{

		s32			lnMillisecond, lnMicrosecond;
		u32			lnResult, lnHour, lnMinute, lnSecond;
		SYSTEMTIME	lst;
		SVariable*	result;


		//////////
		// If Parameter 1 is provided, it must be datetime or datetimex
		//////
			rpar->rp[0] = NULL;
			if (varParam)
			{
				if (!iVariable_isValid(varParam))
				{
					iError_reportByNumber(_ERROR_INVALID_ARGUMENT_TYPE_COUNT, iVariable_get_relatedComp(varParam), false);
					return;

				} else if (!iVariable_isTypeDatetime(varParam)) {
					// Grab hour, minute, second, millisecond from datetime
					iiDateMath_get_HhMmSsMss_from_seconds(varParam->value.data_dt->seconds, &lnHour, &lnMinute, &lnSecond, &lnMillisecond);
					lnMicrosecond = lnMillisecond * 1000;

				} else if (!iVariable_isTypeDatetimeX(varParam)) {
					// Grab hour, minute, second, millisecond from datetime
					iiDateMath_get_julian_and_YyyyMmDdHhMmSsMssNss_from_jseconds(varParam->value.data_dtx->jseconds, NULL, NULL, NULL, NULL, NULL, &lnHour, &lnMinute, &lnSecond, &lnMillisecond, &lnMicrosecond);

				} else {
					iError_reportByNumber(_ERROR_INVALID_ARGUMENT_TYPE_COUNT, iVariable_get_relatedComp(varParam), false);
					return;
				}

			} else {
				// Use the current datetimex
				if (_settings)		iTime_getLocalOrSystem(&lst, propGet_settings_TimeLocal(_settings));
				else				GetLocalTime(&lst);

				lnHour			= lst.wHour;
				lnMinute		= lst.wMinute;
				lnSecond		= lst.wSecond;
				lnMillisecond	= lst.wMilliseconds;
				lnMicrosecond	= iiDateMath_get_currentMicrosecond();
			}


		//////////
		// Create output variable
		//////
			switch (tnFunctionType)
			{
				case _HMS_COMMON_HOUR:			lnResult = lnHour;			break;
				case _HMS_COMMON_MINUTE:		lnResult = lnMinute;		break;
				case _HMS_COMMON_SECOND:		lnResult = lnSecond;		break;
				case _HMS_COMMON_MILLISECOND:	lnResult = lnMillisecond;	break;
				case _HMS_COMMON_MICROSECOND:	lnResult = lnMicrosecond;	break;

				// Should never happen
				default:
					iError_reportByNumber(_ERROR_INTERNAL_ERROR, iVariable_get_relatedComp(varParam), false);
					return;
			}


		//////////
		// Create the value
		//////
			result = iVariable_createAndPopulate_byText(_VAR_TYPE_U32, (cs8*)&lnResult, sizeof(lnResult), false);
			if (!result)
				iError_reportByNumber(_ERROR_INTERNAL_ERROR, iVariable_get_relatedComp(varParam), false);


		//////////
		// Return the result
		//////
			rpar->rp[0] = result;

	}
