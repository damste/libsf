//////////
//
// /libsf/source/vjr/commands/funcs/n.cpp
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
// Function: NANOSECOND()
// The current nanosecond (1/1000000000 one billionth of a second) as a floating point in the range 0..999999999
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
//    f64		-- A floating point value containing the number of one billionths of a second which have gone by this second
//////
	void function_nanosecond(SReturnsParams* rpar)
	{
		ifunction_xseconds_common(rpar, _XSECONDS_FUNCTION_NANOSECOND);
	}




//////////
//
// Function: NCSET()
// Nuance compatibility settings. Used to enable or disable enhancements
// in VXB which may not be present in other xbase languages.
//
//////
// Version 0.57
// Last update:
//     Mar.15.2015
//////
// Change log:
//     Mar.15.2015 -- Initial creation
//////
// Parameters:
//    varIndex		-- The index to set
//    varP1..varP6	-- Various, depends on the indexed function's requirements
//
//////
// Returns:
//    s32			-- The number of times
//////
	void function_ncset(SReturnsParams* rpar)
	{
		SVariable*	varIndex	= rpar->ip[0];
		SVariable*	varP1		= rpar->ip[1];

		s32					lnIndex, lnIndexProp;
		bool				llEnabled, llNewValue, llFound;
		SBasePropMap*		baseProp;
		SAsciiCompSearcher*	asciiComp;
		SVariable*			result;
		bool				error;
		u32					errorNum;


		//////////
		// nIndex must be numeric
		//////
			rpar->rp[0] = NULL;
			if (!iVariable_isValid(varIndex))
			{
				iError_report_byNumber(_ERROR_P1_IS_INCORRECT, iVariable_get_relatedComp(varIndex), false);
				return;
			}
			if (iVariable_isTypeNumeric(varIndex))
			{
				// They have specified an index
				// We'll receive whatever they give, as it will be reported in error below
				lnIndex = iiVariable_getAs_s32(varIndex, false, &error, &errorNum);
				if (error)
				{
					iError_report_byNumber(errorNum, iVariable_get_relatedComp(varIndex), false);
					return;
				}


			//////////
			// What function are they requesting?
			//////
				// Based on the index, set the value
				switch (lnIndex)
				{
					case _NCSET_CEILING_FLOOR:
						lnIndexProp = _INDEX_SET_NCSET_CEILING_FLOOR;
						break;

					case _NCSET_DATETIME_MILLISECONDS:
						lnIndexProp = _INDEX_SET_NCSET_DATETIME_MILLISECONDS;
						break;

					case _NCSET_OPTIMIZE_TABLE_WRITES:
						lnIndexProp = _INDEX_SET_NCSET_OPTIMIZE_TABLE_WRITES;
						break;

					case _NCSET_OPTIMIZE_VARIABLES:
						lnIndexProp = _INDEX_SET_NCSET_OPTIMIZE_VARIABLES;
						break;

					case _NCSET_RGBA_ALPHA_IS_OPAQUE:
						lnIndexProp = _INDEX_SET_NCSET_ALPHA_IS_OPAQUE;
						break;

					case _NCSET_SIGN_SIGN2:
						lnIndexProp = _INDEX_SET_NCSET_SIGN_SIGN2;
						break;

					case _NCSET_DIRECT_NATIVE_MEMBERS:
						lnIndexProp = _INDEX_SET_NCSET_DIRECT_NATIVE_MEMBERS;
						break;

					default:
						// Unrecognized option
						iError_report_byNumber(_ERROR_FEATURE_NOT_AVAILABLE, iVariable_get_relatedComp(varIndex), false);
						return;
				}


			} else if (iVariable_isTypeCharacter(varIndex)) {
				// They have specified a character string, so we can lookup the identifying tag
				for (lnIndex = (s32)_INDEX_SET_NCSET_START, baseProp = &gsProps_master[_INDEX_SET_NCSET_START - 1], llFound = false; !llFound && lnIndex <= (s32)_INDEX_SET_NCSET_END; lnIndex++, baseProp++)
				{
					// Translate the property _INDEX to its related iCode
					for (asciiComp = &cgcVxbKeywords[0]; asciiComp->iCode != 0; asciiComp++)
					{
						// If this is the component which relates to the indicated iCode...
						if (asciiComp->iCode == baseProp->associated_iCode)
						{
							// It's the right iCode, see if the text they've provided matches up
							if (varIndex->value.length == asciiComp->length && iDatum_compare(&varIndex->value, asciiComp->keyword_cs8, asciiComp->length) == 0)
							{
								lnIndexProp	= lnIndex;
								llFound		= true;
								break;
							}
						}
					}
				}

				if (!llFound)
				{
					// They've specified something we don't have
					iError_report_byNumber(_ERROR_FEATURE_NOT_AVAILABLE, iVariable_get_relatedComp(varIndex), false);
					return;
				}
				// When we get here, lnIndexProp is set

			} else {
				// Invalid
				iError_report_byNumber(_ERROR_INVALID_ARGUMENT_TYPE_COUNT, iVariable_get_relatedComp(varIndex), false);
				return;
			}


		//////////
		// Update
		//////
			// Get the existing value
			llEnabled = propGet_settings_ncset(_settings, lnIndexProp);
			if (varP1)
			{
				// They are setting the value
				if (iVariable_isFundamentalTypeLogical(varP1))
				{
					// Obtain its value as a logical
					llNewValue = iiVariable_getAs_bool(varP1, false, &error, &errorNum);
					if (error)
					{
						iError_report_byNumber(errorNum, iVariable_get_relatedComp(varIndex), false);
						return;
					}

					// Set the new value
					propSet_settings_ncset_fromBool(_settings, lnIndexProp, llNewValue);

				} else {
					// The variable is not a type that can be processed as logical
					iError_report_byNumber(_ERROR_P1_IS_INCORRECT, iVariable_get_relatedComp(varP1), false);
					return;
				}
			}


		//////////
		// Create the return variable
		//////
			result = iVariable_createAndPopulate_byText(_VAR_TYPE_LOGICAL, iVariable_populate_byBool(llEnabled), 1, false);
			if (!result)
				iError_report_byNumber(_ERROR_INTERNAL_ERROR, iVariable_get_relatedComp(varIndex), false);


		//////////
		// Signify our result
		//////
			rpar->rp[0] = result;

	}




//////////
//
// Function: NVL()
// Returns a non-null value from two expressions.
//
//////
// Version 0.57
// Last update:
//     2015.04.09
//////
// Change log:
//     2015.04.09 - Initial creation by Hernan Cano M
//////
// Parameters:
//     p1	-- Specifies the expression that NVL() evaluates.
//     p2	-- Specifies the expression to return if p1 is null.
//
//////
// Returns:
//    NVL() returns p1 if it does not evaluate to an null value; otherwise, it returns p2.
//////
// Examples:
//    ? NVL("FirstNoNull", .null.)	&& Display "FirstNoNull"
//    FirstIsNull = .null.
//    M.dSecondNoNull=date()
//    ? NVL(FirstIsNull, M.dSecondNoNull)	&& Display value of M.dSecondNoNull
//////
	void function_nvl(SReturnsParams* rpar)
	{
		SVariable*	varExpr1 = rpar->ip[0];
		SVariable*	varExpr2 = rpar->ip[1];

		bool		llIsNull;


		//////////
		// Verify p1 is correct
		//////
			rpar->rp[0] = NULL;
			if (!iVariable_isValidType(varExpr1))
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
			llIsNull	= ifunction_isnull_common(varExpr1);
			rpar->rp[0]	= iVariable_copy(((llIsNull) ? varExpr2 : varExpr1), false);
			if (!rpar->rp[0])
				iError_report_byNumber(_ERROR_INTERNAL_ERROR, iVariable_get_relatedComp(((llIsNull) ? varExpr2 : varExpr1)), false);

	}
