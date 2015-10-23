//////////
//
// /libsf/source/vjr/commands/funcs/b.cpp
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
// Function: BETWEEN()
// Determines whether the value of an expression is inclusively
// between the values of two expressions of the same type.
//
//////
// Version 0.57
// Last update:
//     Mar.23.2015
//////
// Change log:
//     Mar.23.2015 - Initial creation by Stefano D'Amico
//////
// Parameters:
//     varValue		-- Specifies an expression to evaluate.
//     varLowValue	-- Specifies the lower value in the range.
//     varHighValue	-- Specifies the upper value in the range.
//
//////
// Returns:
//    Logical		-- .t. if the item is inclusively between the values of two expressions of the same type, .f. otherwise
//////
	void function_between(SThisCode* thisCode, SFunctionParams* rpar)
	{
		SVariable*	varValue		= rpar->ip[0];
		SVariable*	varLowValue		= rpar->ip[1];
		SVariable*	varHighValue	= rpar->ip[2];
		s32			lnI, lnType, lnComp;
		bool		llInRange;
		SVariable*	result;
		u32			errorNum;
        bool		error;


		//////////
		// Parameters 1, 2 and 3 must be present
		//////
			rpar->rp[0] = NULL;
			if (!iVariable_isValid(varValue))
			{
				iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_get_relatedComp(thisCode, varValue), false);
				return;
			}
			if (!iVariable_isValid(varLowValue))
			{
				iError_reportByNumber(thisCode, _ERROR_P2_IS_INCORRECT, iVariable_get_relatedComp(thisCode, varLowValue), false);
				return;
			}
			if (!iVariable_isValid(varHighValue))
			{
				iError_reportByNumber(thisCode, _ERROR_P3_IS_INCORRECT, iVariable_get_relatedComp(thisCode, varHighValue), false);
				return;
			}


		//////////
		// Each type must be fundamentally the same type
		//////
			for (lnI = 1, lnType = iVariable_get_fundamentalType(thisCode, varValue); lnI <= 3 && rpar->ip[lnI]; lnI++)
			{
				//////////
				// Make sure this variable type matches the test value
				//////
					if (iVariable_get_fundamentalType(thisCode, rpar->ip[lnI]) != lnType)
					{
						// The types do not match
						iError_reportByNumber(thisCode, _ERROR_DATA_TYPE_MISMATCH, iVariable_get_relatedComp(thisCode, rpar->ip[lnI]), false);
						return;
					}

			}


		//////////
		// Compare value and low
		//////
			lnComp = iVariable_compare(thisCode, varValue, varLowValue, false, &error, &errorNum);
			if (error)
			{
				iError_reportByNumber(thisCode, errorNum, iVariable_get_relatedComp(thisCode, varLowValue), false);
				return;
			}

			// If the value is greater than or equal to the low value, we're good
			llInRange = (lnComp == 1/*greater than*/ || lnComp == 0/*equal to*/);


		//////////
		// If we're still in range,
		// compare value and high
		//////
			if (llInRange)
			{
				// Compare value to high
				lnComp = iVariable_compare(thisCode, varValue, varHighValue, false, &error, &errorNum);
				if (error)
				{
					iError_reportByNumber(thisCode, errorNum, iVariable_get_relatedComp(thisCode, varHighValue), false);
					return;
				}

				// If value is less than or equal to high, we're good
				llInRange = (lnComp == -1/*less than*/ || lnComp == 0/*equal to*/);
			}


		//////////
		// Based on the result, create the return(result)
		//////
			result = iVariable_createAndPopulate_byText(thisCode, _VAR_TYPE_LOGICAL, ((llInRange) ? (s8*)&_LOGICAL_TRUE : (s8*)&_LOGICAL_FALSE), 1, false);
			if (!result)
				iError_reportByNumber(thisCode, _ERROR_INTERNAL_ERROR, iVariable_get_relatedComp(thisCode, varValue), false);


		//////////
		// Indicate our result
		//////
			rpar->rp[0] = result;
	}




//////////
//
// Function: BFP()
// Creates an arbitrary precision big floating point value.
//
//////
// Version 0.57
// Last update:
//     Apr.27.2015
//////
// Change log:
//     Apr.27.2015 - Initial creation
//////
// Parameters:
// Note:  Uses SET PRECISIONBFP bits
//     varP1		-- (Optional) An initialization value
//     varP2		-- (Optional) The number of bits to initialize
//
//////
// Returns:
//    Numeric		-- The input is populated into the big floating point
//////
	void function_bfp(SThisCode* thisCode, SFunctionParams* rpar)
	{
		SVariable* varP1	= rpar->ip[0];
		SVariable* varP2	= rpar->ip[1];

		s32			lnBits;
		s64			lnVal64;
		f64			lfVal64;
		SVariable*	result;
		s8			buffer[64];
		bool		error;
		u32			errorNum;


		//////////
		// Determine our size and initialization value
		//////
			rpar->rp[0] = NULL;
			switch (rpar->ipCount)
			{
				case 0:
					lnBits = propGet_settings_PrecisionBFP(_settings);
					break;

				case 1:
					//////////
					// Initialization value only
					//////
						if (!iVariable_isValid(varP1) || (!iVariable_isTypeNumeric(varP1) && !iVariable_isTypeCharacter(varP1)))
						{
							iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_get_relatedComp(thisCode, varP1), false);
							return;
						}


					//////////
					// Default precision
					//////
						lnBits = propGet_settings_PrecisionBFP(_settings);
						break;

				case 2:
					//////////
					// Initialization value, and bits override
					//////
						if (!iVariable_isValid(varP1) || (!iVariable_isTypeNumeric(varP1) && !iVariable_isTypeCharacter(varP1)))
						{
							iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_get_relatedComp(thisCode, varP1), false);
							return;
						}
						if (!iVariable_isValid(varP2) || !iVariable_isTypeNumeric(varP2))
						{
							iError_reportByNumber(thisCode, _ERROR_P2_IS_INCORRECT, iVariable_get_relatedComp(thisCode, varP2), false);
							return;
						}


					//////////
					// Grab the bits
					//////
						lnBits = iiVariable_getAs_s32(thisCode, varP2, false, &error, &errorNum);
						if (error)
						{
							iError_reportByNumber(thisCode, errorNum, iVariable_get_relatedComp(thisCode, varP2), false);
							return;
						}
						break;

			}


		//////////
		// Construct the appropriate variable
		//////
			result = iVariable_create(thisCode, _VAR_TYPE_BFP, NULL, true, lnBits);
			if (result && rpar->ipCount >= 1)
			{
				// Initialize
				if (iVariable_isTypeCharacter(varP1))
				{
					// Initializing from the string
					m_apm_set_string(result->value.data_big, varP1->value.data_s8);

				} else if (iVariable_isTypeBig(varP1)) {
					// bfp or bi
					m_apm_copy(result->value.data_big, varP1->value.data_big);

				} else if (iVariable_isTypeInteger(varP1)) {
					// Integer
					lnVal64 = iiVariable_getAs_s64(thisCode, varP1, false, &error, &errorNum);
					if (error)
					{
						// Should never happen
						iError_reportByNumber(thisCode, _ERROR_UNABLE_TO_INITIALIZE, iVariable_get_relatedComp(thisCode, varP2), false);

					} else {
						// We're good
						if (lnVal64 >= (s64)_s32_min && lnVal64 <= (s64)_s32_max)
						{
							// We can set it directly as a long
							m_apm_set_long(result->value.data_big, (s32)lnVal64);

						} else {
							// Convert it to a string first, then set it
							sprintf((s8*)buffer, "%I64d\0", lnVal64);
							m_apm_set_string(result->value.data_big, buffer);
						}
					}

				} else {
					// Floating point
					lfVal64 = iiVariable_getAs_f64(thisCode, varP1, false, &error, &errorNum);
					if (error)
					{
						// Should never happen
						iError_reportByNumber(thisCode, _ERROR_UNABLE_TO_INITIALIZE, iVariable_get_relatedComp(thisCode, varP2), false);

					} else {
						// We're good
						m_apm_set_double(result->value.data_big, lfVal64);
					}
				}
			}


		//////////
		// Are we good?
		//////
			if (!result)
				iError_reportByNumber(thisCode, _ERROR_INTERNAL_ERROR, iVariable_get_relatedComp(thisCode, varP1), false);


		//////////
		// Indicate our result
		//////
			rpar->rp[0] = result;

	}




//////////
//
// Function: BI()
// Creates an arbitrary precision big integer value.
//
//////
// Version 0.57
// Last update:
//     Apr.27.2015
//////
// Change log:
//     Apr.27.2015 - Initial creation
//////
// Parameters:
// Note:  Uses SET PRECISIONBFP bits
//     varP1		-- (Optional) An initialization value
//     varP2		-- (Optional) The number of bits to initialize
//
//////
// Returns:
//    Numeric		-- The input is populated into the big integer
//////
	void function_bi(SThisCode* thisCode, SFunctionParams* rpar)
	{
		SVariable* varP1	= rpar->ip[0];
		SVariable* varP2	= rpar->ip[1];

		s32			lnBits;
		s64			lnVal64;
		f64			lfVal64;
		SVariable*	result;
		s8			buffer[64];
		bool		error;
		u32			errorNum;


		//////////
		// Determine our size and initialization value
		//////
			rpar->rp[0] = NULL;
			switch (rpar->ipCount)
			{
				case 0:
					lnBits = propGet_settings_PrecisionBI(_settings);
					break;

				case 1:
					//////////
					// Initialization value only
					//////
						if (!iVariable_isValid(varP1) || (!iVariable_isTypeNumeric(varP1) && !iVariable_isTypeCharacter(varP1)))
						{
							iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_get_relatedComp(thisCode, varP1), false);
							return;
						}


					//////////
					// Default precision
					//////
						lnBits = propGet_settings_PrecisionBI(_settings);
						break;

				case 2:
					//////////
					// Initialization value, and bits override
					//////
						if (!iVariable_isValid(varP1) || (!iVariable_isTypeNumeric(varP1) && !iVariable_isTypeCharacter(varP1)))
						{
							iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_get_relatedComp(thisCode, varP1), false);
							return;
						}
						if (!iVariable_isValid(varP2) || !iVariable_isTypeNumeric(varP2))
						{
							iError_reportByNumber(thisCode, _ERROR_P2_IS_INCORRECT, iVariable_get_relatedComp(thisCode, varP2), false);
							return;
						}


					//////////
					// Grab the bits
					//////
						lnBits = iiVariable_getAs_s32(thisCode, varP2, false, &error, &errorNum);
						if (error)
						{
							iError_reportByNumber(thisCode, errorNum, iVariable_get_relatedComp(thisCode, varP2), false);
							return;
						}
						break;

			}


		//////////
		// Construct the appropriate variable
		//////
			result = iVariable_create(thisCode, _VAR_TYPE_BI, NULL, true, lnBits);
			if (result && rpar->ipCount >= 1)
			{
				// Initialize
				if (iVariable_isTypeCharacter(varP1))
				{
					// Initializing from the string
					m_apm_set_string(result->value.data_big, varP1->value.data_s8);

				} else if (iVariable_isTypeBig(varP1)) {
					// bfp or bi
					m_apm_copy(result->value.data_big, varP1->value.data_big);

				} else if (iVariable_isTypeInteger(varP1)) {
					// Integer
					lnVal64 = iiVariable_getAs_s64(thisCode, varP1, false, &error, &errorNum);
					if (error)
					{
						// Should never happen
						iError_reportByNumber(thisCode, _ERROR_UNABLE_TO_INITIALIZE, iVariable_get_relatedComp(thisCode, varP2), false);

					} else {
						// We're good
						if (lnVal64 >= (s64)_s32_min && lnVal64 <= (s64)_s32_max)
						{
							// We can set it directly as a long
							m_apm_set_long(result->value.data_big, (s32)lnVal64);

						} else {
							// Convert it to a string first, then set it
							sprintf((s8*)buffer, "%I64d\0", lnVal64);
							m_apm_set_string(result->value.data_big, buffer);
						}
					}

				} else {
					// Floating point
					lfVal64 = iiVariable_getAs_f64(thisCode, varP1, false, &error, &errorNum);
					if (error)
					{
						// Should never happen
						iError_reportByNumber(thisCode, _ERROR_UNABLE_TO_INITIALIZE, iVariable_get_relatedComp(thisCode, varP2), false);

					} else {
						// We're good
						m_apm_set_double(result->value.data_big, lfVal64);
					}
				}
			}


		//////////
		// Are we good?
		//////
			if (!result)
				iError_reportByNumber(thisCode, _ERROR_INTERNAL_ERROR, iVariable_get_relatedComp(thisCode, varP1), false);


		//////////
		// Indicate our result
		//////
			rpar->rp[0] = result;

	}




//////////
//
// Function: BITS()
// Creates the closest larger 2^n numeric value than the size indicated by bits.
//
//////
// Version 0.57
// Last update:
//     Mar.22.2015
//////
// Change log:
//     Mar.22.2015 - Initial creation
//////
// Parameters:
//     varBits		-- A sequence of binary bits
//
//////
// Returns:
//    Numeric		-- Input bits converted to an unsigned integer of the appropriate size (up to 64-bits)
//////
	void function_bits(SThisCode* thisCode, SFunctionParams* rpar)
	{
		SVariable* varBits		= rpar->ip[0];
		SVariable* varBitWidth	= rpar->ip[1];


		// Return bits
		ifunction_bits_common(thisCode, rpar, varBits, varBitWidth);
	}

	void ifunction_bits_common(SThisCode* thisCode, SFunctionParams* rpar, SVariable* varBits, SVariable* varBitWidth)
	{
		s8			c;
		u8			lnOrValue;
		s32			lnWidth, lnBit;
		SVariable*	result;
		bool		error;
		u32			errorNum;


		//////////
		// varBits must be character
		//////
			rpar->rp[0] = NULL;
			if (!iVariable_isValid(varBits) || !iVariable_isTypeCharacter(varBits) || varBits->value.length > 64)
			{
				iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_get_relatedComp(thisCode, varBits), false);
				return;
			}


		//////////
		// If present, varBitWidth must be numeric
		//////
			if (varBitWidth)
			{
				if (!iVariable_isValid(varBitWidth) || !iVariable_isTypeNumeric(varBitWidth))
				{
					iError_reportByNumber(thisCode, _ERROR_P2_IS_INCORRECT, iVariable_get_relatedComp(thisCode, varBitWidth), false);
					return;
				}

				// Grab the width
				lnWidth = iiVariable_getAs_s32(thisCode, varBitWidth, false, &error, &errorNum);
				if (error)
				{
					iError_reportByNumber(thisCode, errorNum, iVariable_get_relatedComp(thisCode, varBitWidth), false);
					return;
				}

				// Must be 8, 16, 32, or 64
				if (lnWidth != 8 && lnWidth != 16 && lnWidth != 32 && lnWidth != 64)
				{
					iError_reportByNumber(thisCode, _ERROR_PARAMETER_MUST_BE_8_16_32_64, iVariable_get_relatedComp(thisCode, varBitWidth), false);
					return;
				}

			} else {
				// It will be sized based on what is required for the value it contains
				lnWidth = -1;
			}


		//////////
		// Make sure every digit in the character string is either a '1' or '0', and the total is
		//////
			for (lnBit = 0; lnBit < varBits->value.length; lnBit++)
			{
				// Grab the character
				c = varBits->value.data_s8[lnBit];

				// Is it anything other than binary digits
				if (c != '0' && c != '1')
				{
					iError_reportByNumber(thisCode, _ERROR_P1_IS_INCORRECT, iVariable_get_relatedComp(thisCode, varBits), false);
					return;
				}
			}
			// When we get here, we know how wide it is maximum
			if (lnWidth == -1)
			{
				// Always default to 64-bit or 32-bit
				if (lnBit > 32)		lnWidth = 64;
				else				lnWidth = 32;
			}


		//////////
		// Make sure our result will fit
		//////
			if (lnBit > lnWidth)
			{
				iError_reportByNumber(thisCode, _ERROR_TOO_BIG_FOR_TARGET, iVariable_get_relatedComp(thisCode, varBits), false);
				return;
			}


		//////////
		// Create our result
		//////
			switch (lnWidth)
			{
				case 8:
					result = iVariable_create(thisCode, _VAR_TYPE_U8, NULL, true);
					break;
				case 16:
					result = iVariable_create(thisCode, _VAR_TYPE_U16, NULL, true);
					break;
				case 32:
					result = iVariable_create(thisCode, _VAR_TYPE_U32, NULL, true);
					break;
				case 64:
					result = iVariable_create(thisCode, _VAR_TYPE_U64, NULL, true);
					break;
				default:
					iError_reportByNumber(thisCode, _ERROR_INTERNAL_ERROR, iVariable_get_relatedComp(thisCode, varBits), false);
					return;
			}


		//////////
		// Are we good?
		//////
			if (!result)
				iError_reportByNumber(thisCode, _ERROR_INTERNAL_ERROR, iVariable_get_relatedComp(thisCode, varBits), false);


		//////////
		// Populate
		//////
			if (result)
			{
				// Iterate through each bit loading in its value
				for (lnBit = 0; lnBit < varBits->value.length; lnBit++)
				{

					//////////
					// Grab our OR value
					//////
						lnOrValue = varBits->value.data_u8[lnBit] - (u8)'0';


					//////////
					// Shift our destination
					//////
						switch (result->varType)
						{
							case _VAR_TYPE_U8:
								result->value.data_u8[0] <<= 1;
								result->value.data_u8[0] |= lnOrValue;
								break;

							case _VAR_TYPE_U16:
								result->value.data_u16[0] <<= 1;
								result->value.data_u16[0] |= lnOrValue;
								break;

							case _VAR_TYPE_U32:
								result->value.data_u32[0] <<= 1;
								result->value.data_u32[0] |= lnOrValue;
								break;

							case _VAR_TYPE_U64:
								result->value.data_u64[0] <<= 1;
								result->value.data_u64[0] |= lnOrValue;
								break;
						}

				}
			}


		//////////
		// Return our result
		//////
			rpar->rp[0] = result;
	}




//////////
//
// Function: BITS8()
// Creates an 8-bit integer populated with the indicated bits.
//
//////
// Version 0.57
// Last update:
//     Mar.22.2015
//////
// Change log:
//     Mar.22.2015 - Initial creation
//////
// Parameters:
//     varBits		-- A sequence of binary bits
//
//////
// Returns:
//    Numeric		-- Input bits converted to an 8-bit unsigned integer
//////
	void function_bits8(SThisCode* thisCode, SFunctionParams* rpar)
	{
		SVariable* varBits = rpar->ip[0];


		// Return bits8()
		ifunction_bits_common(thisCode, rpar, varBits, cvarEight);
	}




//////////
//
// Function: BITS16()
// Creates a 16-bit integer populated with the indicated bits.
//
//////
// Version 0.57
// Last update:
//     Mar.22.2015
//////
// Change log:
//     Mar.22.2015 - Initial creation
//////
// Parameters:
//     varBits		-- A sequence of binary bits
//
//////
// Returns:
//    Numeric		-- Input bits converted to an 16-bit unsigned integer
//////
	void function_bits16(SThisCode* thisCode, SFunctionParams* rpar)
	{
		SVariable* varBits = rpar->ip[0];


		// Return bits16()
		ifunction_bits_common(thisCode, rpar, varBits, cvarSixteen);
	}




//////////
//
// Function: BITS32()
// Creates a 32-bit integer populated with the indicated bits.
//
//////
// Version 0.57
// Last update:
//     Mar.22.2015
//////
// Change log:
//     Mar.22.2015 - Initial creation
//////
// Parameters:
//     varBits		-- A sequence of binary bits
//
//////
// Returns:
//    Numeric		-- Input bits converted to an 32-bit unsigned integer
//////
	void function_bits32(SThisCode* thisCode, SFunctionParams* rpar)
	{
		SVariable* varBits = rpar->ip[0];


		// Return bits32()
		ifunction_bits_common(thisCode, rpar, varBits, cvarThirtyTwo);
	}




//////////
//
// Function: BITS64()
// Creates a 64-bit integer populated with the indicated bits.
//
//////
// Version 0.57
// Last update:
//     Mar.22.2015
//////
// Change log:
//     Mar.22.2015 - Initial creation
//////
// Parameters:
//     varBits		-- A sequence of binary bits
//
//////
// Returns:
//    Numeric		-- Input bits converted to an 64-bit unsigned integer
//////
	void function_bits64(SThisCode* thisCode, SFunctionParams* rpar)
	{
		SVariable* varBits = rpar->ip[0];


		// Return bits64()
		ifunction_bits_common(thisCode, rpar, varBits, cvarSixtyFour);
	}




//////////
//
// Function: BITSLICE()
// Extracts a bit portion from a value.
//
//////
// Version 0.57
// Last update:
//     Mar.22.2015
//////
// Change log:
//     Mar.22.2015 - Initial creation
//////
// Parameters:
//     varValue		-- Numeric value from which to extract.
//     varBitStart	-- Starting bit position (little-endian, so starting position will be greatest bit value)
//     varBitEnd    -- Ending bit position (little-endian, so ending position will be lowest bit value)
//
//////
// Returns:
//    Numeric		-- The extracted bits as a numeric unsigned integer of the same size as the original.
//////
	void function_bitslice(SThisCode* thisCode, SFunctionParams* rpar)
	{
//		SVariable* varValue		= rpar->params[0];
//		SVariable* varBitStart	= rpar->params[1];
//		SVariable* varBitEnd	= rpar->params[2];


		// Not yet completed
		iError_reportByNumber(thisCode, _ERROR_FEATURE_NOT_AVAILABLE, NULL, false);
	}




//////////
//
// Function: BITSTR()
// Converts a value into its bit pattern.
//
//////
// Version 0.57
// Last update:
//     Mar.22.2015
//////
// Change log:
//     Mar.22.2015 - Initial creation
//////
// Parameters:
//     varValue		-- Numeric value from which to extract.
//     varLength	-- Number of bits to extract, including leading 0s
//
//////
// Returns:
//    Character		-- The extracted bits as a character string
//////
	void function_bitstr(SThisCode* thisCode, SFunctionParams* rpar)
	{
//		SVariable* varValue		= rpar->params[0];
//		SVariable* varLength	= rpar->params[1];


		// Not yet completed
		iError_reportByNumber(thisCode, _ERROR_FEATURE_NOT_AVAILABLE, NULL, false);
	}




//////////
//
// Function: BLU()
// Retrieves the blue channel from an RGBA or BGRA color.
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
	void function_blu(SThisCode* thisCode, SFunctionParams* rpar)
	{
		SVariable* varColor = rpar->ip[0];


		// Return blu
		ifunction_color_common(thisCode, rpar, varColor, 0x00ff0000, 16);
	}




//////////
//
// Function: BGR()
// Returns the BGR() of the three input values.
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
//     pBlu			-- Blue, in the range 0..255, or 0.0..1.0
//     pGrn			-- Green, in the range 0..255, or 0.0..1.0
//     pRed			-- Red, in the range 0..255, or 0.0..1.0
//
//////
// Returns:
//    Numeric		-- Constructed system-wide RGBA() integer
//
//////
	void function_bgr(SThisCode* thisCode, SFunctionParams* rpar)
	{
		SVariable* varBlu = rpar->ip[0];
		SVariable* varGrn = rpar->ip[1];
		SVariable* varRed = rpar->ip[2];


		// Return bgr
		ifunction_rgba_common(thisCode, rpar, varRed, varGrn, varBlu, NULL);
	}




//////////
//
// Function: BGRA()
// Returns the BGRA() of the four input values.
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
//     pBlu			-- Blue, in the range 0..255, or 0.0..1.0
//     pGrn			-- Green, in the range 0..255, or 0.0..1.0
//     pRed			-- Red, in the range 0..255, or 0.0..1.0
//     pAlp			-- Alpha, in the range 0..255, or 0.0..1.0
//
//////
// Returns:
//    Numeric		-- Constructed system-wide RGBA() integer
//
//////
	void function_bgra(SThisCode* thisCode, SFunctionParams* rpar)
	{
		SVariable* varBlu = rpar->ip[0];
		SVariable* varGrn = rpar->ip[1];
		SVariable* varRed = rpar->ip[2];
		SVariable* varAlp = rpar->ip[3];


		// Return bgra
		ifunction_rgba_common(thisCode, rpar, varRed, varGrn, varBlu, varAlp);
	}
