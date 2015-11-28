//////////
//
// /libsf/source/vjr/commands/funcs/v.cpp
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
// Function: _VJRSYS()
// Internal function.  Not published.  Used to access VJr system variables.
//
//////
// Version 0.58
// Last update:
//     Oct.28.2015
//////
// Change log:
//     Oct.28.2015 - Initial creation by Rick C. Hodgin
//////
// Parameters:
//     varIndex			-- Index function to access the variable
//
//////
// Returns:
//     Varies			-- Based on index, returns the VJr system variable
//////
	void function__vjrsys(SReturnsParams* rpar)
	{
		SVariable* varIndex		= rpar->ip[0];

		s32			lnIndex;
		u32			errorNum;
		bool		error;


		//////////
		// Parameter 1 must be valid and numeric
		//////
			rpar->rp[0] = NULL;
			if (!iVariable_isValid(varIndex) || !iVariable_isTypeNumeric(varIndex))
			{
				iError_report_byNumber(_ERROR_P1_IS_INCORRECT, iVariable_get_relatedComp(varIndex), false);
				return;
			}

			// Grab the index value
			lnIndex = iiVariable_getAs_s32(varIndex, false, &error, &errorNum);
			if (error)
			{
				iError_report_byNumber(errorNum, iVariable_get_relatedComp(varIndex), false);
				return;
			}


		//////////
		// Dispatch based on operation
		//////
			switch (lnIndex)
			{
				case 1:
					rpar->rp[0] = iVariable_createAndPopulate_byText(_VAR_TYPE_LOGICAL, iVariable_populate_byBool(glShuttingDown), 1, false);
					break;

				default:
					iError_report_byNumber(_ERROR_FEATURE_NOT_AVAILABLE, iVariable_get_relatedComp(varIndex), false);
					break;
			}

	}




//////////
//
// Function: VAL()
// Returns a numeric or currency value from a expression.
//
//////
// Version 0.58
// Last update:
//     Mar.22.2015
//////
// Change log:
//     Mar.21.2015 - Initial creation by Stefano D'Amico
//////
// Parameters:
//     varExpr			-- Any, to convert
//	   varIgnoreList	-- Characters to ignore
//
//////
// Returns:
//    Numeric		--	VAL( ) returns the numbers in the character expression from left to right until a non-numeric character is encountered.
//						Leading blanks are ignored.
//						VAL( ) returns 0 if the first character of the character expression is not a number, a dollar sign ($), a plus sign (+), or minus sign (-).
//////
	void function_val(SReturnsParams* rpar)
	{
		SVariable*	varExpr			= rpar->ip[0];
		SVariable*	varIgnoreChars	= rpar->ip[1];

		s8			c, cCurrency, cPoint, cSeparator;
		s32			lnI, lnJ, lnBuffOffset;
		s64			lnValue;
		f64			lfValue;
		bool		llAsInteger, llStillGoing, llCurrency;
		SVariable*	varCurrency;
		SVariable*	varPoint;
		SVariable*	varSeparator;
		SVariable*	result;
		u32			errorNum;
        bool		error;
		s8			buffer[64];


		//////////
		// Parameter 1 must be valid
		//////
			rpar->rp[0] = NULL;
			if (!iVariable_isValid(varExpr))
			{
				iError_report_byNumber(_ERROR_P1_IS_INCORRECT, iVariable_get_relatedComp(varExpr), false);
				return;
			}


		//////////
		// If numeric, copy whatever's already there
		//////
			if (varExpr->varType >= _VAR_TYPE_NUMERIC_START && varExpr->varType <= _VAR_TYPE_NUMERIC_END)
			{
				// Copy The existing variable
				result = iVariable_copy(varExpr, false);
				if (!result)
					iError_report_byNumber(_ERROR_INTERNAL_ERROR, iVariable_get_relatedComp(varExpr), false);

				// Success or failure, return our result
				rpar->rp[0] = result;
				return;
			}



		//////////
		// Determine what we're evaluating
		//////
			switch (varExpr->varType)
			{
				case _VAR_TYPE_NULL:
					iError_report_byNumber(_ERROR_P1_IS_INCORRECT, iVariable_get_relatedComp(varExpr), false);
					return;
					break;

				case _VAR_TYPE_LOGICAL:		// 0=.F., 1=.T.
				case _VAR_TYPE_DATE:		// YYYYMMDD
					result = iVariable_create(_VAR_TYPE_S32, NULL, true);
					if (result)
					{
						// Populate the s32
						*result->value.data_s32 = iiVariable_getAs_s32(varExpr, true, &error, &errorNum);
						if (error)
							iError_report_byNumber(errorNum, iVariable_get_relatedComp(varExpr), false);
					}
					break;

				case _VAR_TYPE_DATETIME:
					// YYYYMMDDHhMmSsMss as s64
				case _VAR_TYPE_DATETIMEX:
					// YYYYMMDDHhMmSsNssssssss
					result = iVariable_create(_VAR_TYPE_S64, NULL, true);
					if (result)
					{
						// Populate the s64
						*result->value.data_s64 = iiVariable_getAs_s64(varExpr, true, &error, &errorNum);
						if (error)
							iError_report_byNumber(errorNum, iVariable_get_relatedComp(varExpr), false);
					}
					break;

				case _VAR_TYPE_CHARACTER:

					//////////
					// If present, parameter 2 must be valid
					//////
						if (varIgnoreChars)
						{
							if (!iVariable_isValid(varIgnoreChars) || !iVariable_isTypeCharacter(varIgnoreChars))
							{
								iError_report_byNumber(_ERROR_P2_IS_INCORRECT, iVariable_get_relatedComp(varIgnoreChars), false);
								return;
							}
						}


					//////////
					// Prepare our characters
					//////
						varCurrency		= propGet_settings_Currency(_settings);
						varPoint		= propGet_settings_Point(_settings);
						varSeparator	= propGet_settings_Separator(_settings);
						if (!varCurrency || !varPoint || !varSeparator)
						{
							// Should never happen
							iError_report_byNumber(_ERROR_INTERNAL_ERROR, NULL, false);
							return;
						}


					//////////
					// Create single characters
					//////
						cCurrency	= varCurrency->value.data_s8[0];
						cPoint		= varPoint->value.data_s8[0];
						cSeparator	= varSeparator->value.data_s8[0];


					//////////
					// Iterate through each character
					//////
						for (lnI = 0, lnBuffOffset = 0, llStillGoing = true, llCurrency = false; llStillGoing && lnI < (s32)varExpr->value.length && lnBuffOffset < (s32)sizeof(buffer) - 1; lnI++)
						{

							//////////
							// Grab this character
							//////
								c = varExpr->value.data[lnI];


							//////////
							// Is it a character we're including in our buffer (a number, or natural number-related symbol)?
							//////
								if ((c >= '0' && c <= '9' ) || c == '+' || c == '-' || c == cPoint)
								{
									// Yes, Copy this character
									buffer[lnBuffOffset++] = c;

								} else {
									// Are we still in a valid sequence of characters to skip?
									if (c == ' ' || c == cSeparator)
									{
										// It's a character we're skipping naturally (space, separator symbol)
										// We don't do anything here ... it's just more clear to keep this logic visible rather than inverting it. :-)

									} else if (c == cCurrency) {
										// We encountered the currency symbol, so the output will be currency
										llCurrency = true;

									} else if (varIgnoreChars) {
										// We won't continue unless we're sitting on a character in the varIgnoreChars
										for (lnJ = 0, llStillGoing = false; lnJ < varIgnoreChars->value.length; lnJ++)
										{
											// Is this one of our skip characters?
											if (c == varIgnoreChars->value.data_s8[lnJ])
											{
												llStillGoing = true;
												break;
											}
										}

									} else {
										// We're done
										break;
									}
								}

						}

						// NULL terminate
						buffer[lnBuffOffset] = 0;


					//////////
					// Convert to f64, and s64
					//////
						lfValue = atof(buffer);
#if defined(__GNUC__) || defined(__solaris__)
						lnValue = strtoll(buffer, NULL, 10);
#else
						lnValue = _strtoi64(buffer, NULL, 10);
#endif


					//////////
					// Is currency or not? If it's an integer value, store it as the same, otherwise use floating point
					//////
						if ((f64)lnValue == lfValue)
						{
							// We can return as an integer
							llAsInteger = true;
							if (llCurrency)
							{
								// Multiply by 10000 to obtain the 4 implied decimal places
								lnValue = lnValue * 10000;
								result	= iVariable_create(_VAR_TYPE_CURRENCY, NULL, true);

							} else {
								if (lnValue < (s64)_s32_max)
								{
									// We can create as an s32
									result = iVariable_create(_VAR_TYPE_S32, NULL, true);

								} else {
									// Create as an s64
									result = iVariable_create(_VAR_TYPE_S64, NULL, true);
								}
							}

						} else {
							// Must return as f64
							llAsInteger	= false;
							if (llCurrency)
							{
								// As currency
								lfValue	*= 10000.0;
								result	= iVariable_create(_VAR_TYPE_CURRENCY, NULL, true);

							} else {
								// As is
								result	= iVariable_create(_VAR_TYPE_F64, NULL, true);
							}
						}


					//////////
					// Store the result
					//////
						if (result)
						{
							if (llAsInteger)	iVariable_setNumeric_toNumericType(result, NULL, NULL, NULL, NULL, &lnValue, NULL);
							else				iVariable_setNumeric_toNumericType(result, NULL, &lfValue, NULL, NULL, NULL, NULL);
						}
						break;

				default:
					// Unrecognized type
					iError_report_byNumber(_ERROR_FEATURE_NOT_AVAILABLE, iVariable_get_relatedComp(varExpr), false);
					return;
			}


		//////////
		// Are we good?
		//////
			if (!result)
				iError_report_byNumber(_ERROR_INTERNAL_ERROR, iVariable_get_relatedComp(varExpr), false);


		//////////
        // Return our converted result
		//////
			rpar->rp[0] = result;

	}




//////////
//
// Function: VARTYPE()
// Returns the variable type, parsing NULL values.
//
//////
// Version 0.58
// Last update:
//     Apr.06.2015
//////
// Change log:
//     Apr.06.2015 - Initial creation
//////
// Parameters:
//     P1			-- The variable to examine
//     P2			-- (Optional) If provided, .t. or .f. indicating if NULL values should return the type (default to .f.)
//
//////
// Returns:
//    Character		-- A one-digit value indicating the type
//////
	void function_vartype(SReturnsParams* rpar)
	{
		SVariable* var		= rpar->ip[0];
		SVariable* varNull	= rpar->ip[1];

		bool	llNullIsType;
		bool	error;
		u32		errorNum;


		//////////
		// varLookup must exist
		//////
			rpar->rp[0] = NULL;
			if (!iVariable_isValidType(var))
			{
				iError_report_byNumber(_ERROR_P1_IS_INCORRECT, iVariable_get_relatedComp(var), false);
				return;
			}


		//////////
		// If varNull is specified, must be logical
		//////
			if (varNull)
			{

				//////////
				// Must be logical
				//////
					if (!iVariable_isValid(varNull) || !iVariable_isTypeLogical(varNull))
					{
						iError_report_byNumber(_ERROR_P2_IS_INCORRECT, iVariable_get_relatedComp(varNull), false);
						return;
					}


				//////////
				// Grab the value
				//////
					llNullIsType = iiVariable_getAs_bool(varNull, false, &error, &errorNum);
					if (error)
					{
						iError_report_byNumber(errorNum, iVariable_get_relatedComp(varNull), false);
						return;
					}


			} else {
				// Do not report on NULL types
				llNullIsType = false;
			}


		//////////
		// Compute our result
		//////
			ifunction_type_common(rpar, var, false, true, llNullIsType);

	}




//////////
//
// Function: VEC()
// Creates a vector.
//
//////
// Version 0.58
// Last update:
//     Mar.21.2015
//////
// Change log:
//     Mar.21.2015 - Initial creation
//////
// Parameters (example: vec(5,8,9) has three vectors, v1, v2, and v3 are the 5, 8, and 9 portions):
//     varV1		- Vector 1
//     varV2		- Vector 2
//     ...
//     varV10		- Vector 10
//
//////
// Returns:
//    Vector		-- The concatenated value, assumes the current SET VECSEPARATOR symbol
//////
	void function_vec(SReturnsParams* rpar)
	{
		SVariable* varV1 = rpar->ip[0];


		// Not yet completed
		iError_report_byNumber(_ERROR_FEATURE_NOT_AVAILABLE, iVariable_get_relatedComp(varV1), false);
		rpar->rp[0] = NULL;
	}




//////////
//
// Function: VECCOUNT()
// The vector element count.
//
//////
// Version 0.58
// Last update:
//     Mar.21.2015
//////
// Change log:
//     Mar.21.2015 - Initial creation
//////
// Parameters:
//     varVec		- Vector
//
//////
// Returns:
//     Numeric, the number of elements in the vector.
//////
	void function_veccount(SReturnsParams* rpar)
	{
		SVariable* varVec = rpar->ip[0];


		// Not yet completed
		iError_report_byNumber(_ERROR_FEATURE_NOT_AVAILABLE, iVariable_get_relatedComp(varVec), false);
		rpar->rp[0] = NULL;
	}




//////////
//
// Function: VECEL()
// Accesses or updates a vector element.
//
//////
// Version 0.58
// Last update:
//     Mar.21.2015
//////
// Change log:
//     Mar.21.2015 - Initial creation
//////
// Parameters:
//     varVec		- Vector
//     varEl		- Element number within (1-based)
//     varNewValue	- (Optional) Sets the new value. If the new value is a vector, it replaces other vectors which are there.
//
//////
// Returns:
//    if varNewValue was specified, returns the new vector
//    else                          returns the value of that element
//////
	void function_vecel(SReturnsParams* rpar)
	{
		SVariable* varVec		= rpar->ip[0];
//		SVariable* varEl		= rpar->params[1];
//		SVariable* varNewValue	= rpar->params[2];


		// Not yet completed
		iError_report_byNumber(_ERROR_FEATURE_NOT_AVAILABLE, iVariable_get_relatedComp(varVec), false);
		rpar->rp[0] = NULL;
	}




//////////
//
// Function: VECSLICE()
// Extracts elements from a vector.
//
//////
// Version 0.58
// Last update:
//     Mar.22.2015
//////
// Change log:
//     Mar.22.2015 - Initial creation
//////
// Parameters:
//     varVec			- Vector
//     varStartEl		- Element to start the operation at.
//     varEndEl			- The number of elements to remove
//
//////
// Returns:
//     The extracted element or elements as a vector.
//////
	void function_vecslice(SReturnsParams* rpar)
	{
//		SVariable* varVec		= rpar->params[0];
//		SVariable* varStartEl	= rpar->params[1];
//		SVariable* varEndEl		= rpar->params[2];


		// Not yet completed
		iError_report_byNumber(_ERROR_FEATURE_NOT_AVAILABLE, NULL, false);
		rpar->rp[0] = NULL;
	}




//////////
//
// Function: VECSTR()
// Generates a character string containing the vectors.
//
//////
// Version 0.58
// Last update:
//     Mar.21.2015
//////
// Change log:
//     Mar.21.2015 - Initial creation
//////
// Parameters:
//     varVec				- Vector
//     varSymbolOverride	- A symbol to use between vectors
//
//////
// Returns:
//     A character string containing the vector values interspersed with symbol space, or the varSymbolOverride
//////
	void function_vecstr(SReturnsParams* rpar)
	{
//		SVariable* varVec				= rpar->params[0];
//		SVariable* varSymbolOverride	= rpar->params[1];


		// Not yet completed
		iError_report_byNumber(_ERROR_FEATURE_NOT_AVAILABLE, NULL, false);
		rpar->rp[0] = NULL;
	}




//////////
//
// Function: VECSTUFF()
// Updates or resizes a vector element. Works like STUFF().
//
//////
// Version 0.58
// Last update:
//     Mar.21.2015
//////
// Change log:
//     Mar.21.2015 - Initial creation
//////
// Parameters:
//     varVec			- Vector
//     varStartEl		- Element to start the operation at.
//     varRemoveCount	- The number of elements to remove
//     varVecStuff		- (Optional) The new vector to stuff in there after varStartEl
//
//////
// Returns:
//    if varNewValue was specified, returns the new vector
//    else                          returns the value of that element
//////
	void function_vecstuff(SReturnsParams* rpar)
	{
		SVariable* varVec			= rpar->ip[0];
//		SVariable* varStartEl		= rpar->params[1];
//		SVariable* varRemoveCount	= rpar->params[2];
//		SVariable* varVecStuff		= rpar->params[3];


		// Not yet completed
		iError_report_byNumber(_ERROR_FEATURE_NOT_AVAILABLE, iVariable_get_relatedComp(varVec), false);
		rpar->rp[0] = NULL;
	}




//////////
//
// Function: VECSYMBOL()
// Access or updates the symbol used after a vector element.
//
//////
// Version 0.58
// Last update:
//     Mar.21.2015
//////
// Change log:
//     Mar.21.2015 - Initial creation
//////
// Parameters:
//     varVec		- Vector
//     varEl		- Element to access or update.
//     varNewSymbol	- (Optional) The new symbol to put there.
//
//////
// Returns:
//    if varNewSymbol was specified, returns the old symbol
//    else                           returns the current symbol
//////
	void function_vecsymbol(SReturnsParams* rpar)
	{
		SVariable* varVec		= rpar->ip[0];
//		SVariable* varEl		= rpar->params[1];
//		SVariable* varNewSymbol	= rpar->params[2];


		// Not yet completed
		iError_report_byNumber(_ERROR_FEATURE_NOT_AVAILABLE, iVariable_get_relatedComp(varVec), false);
		rpar->rp[0] = NULL;
	}




//////////
//
// Function: VERSION()
// Based on input, retrieves various version information.
//
//////
// Version 0.58
// Last update:
//     Jul.13.2014
//////
// Change log:
//     Jul.13.2014 - Initial creation
//////
// Parameters:
//     pIndex		-- (Optional) If present, Numeric, in the range 1..5
//
//////
// Returns:
//    Numeric or Character	-- Depending on index, various values are returned
//////
    void function_version(SReturnsParams* rpar)
    {
		SVariable*	varIndex = rpar->ip[0];
        s32			index;
		u32			errorNum;
        bool		error;
		u8*			lptr;
        SVariable*	result;


		//////////
		// Parameter 1 must be numeric
		//////
			rpar->rp[0]	= NULL;
			lptr				= NULL;
			if (!iVariable_isValid(varIndex))
			{
				// They are requesting the default information
				lptr = (u8*)cgcVersionText;

			} else if (!iVariable_isTypeNumeric(varIndex)) {
				// The parameter is not numeric
				iError_report_byNumber(_ERROR_P1_IS_INCORRECT, iVariable_get_relatedComp(varIndex), false);
				return;

			} else {
				// It must be in the range 1..5
				index = iiVariable_getAs_s32(varIndex, false, &error, &errorNum);
				if (error)
				{
					iError_report_byNumber(errorNum, iVariable_get_relatedComp(varIndex), false);
					return;

				} else if (index < 1 || index > 5) {
					// We report our own error
					iError_report((cu8*)"Parameter must be in the range 1..5", false);
					return;
				}
			}


		//////////
        // Create our return result
		//////
			if (lptr || index == 1 || index == 4)
			{
				// Character return
				result = iVariable_create(_VAR_TYPE_CHARACTER, NULL, true);
				if (lptr)
				{
					// Copy the version info
					iDatum_duplicate(&result->value, lptr, -1);

				} else if (index == 1) {
					// Copy the version1 info
					iDatum_duplicate(&result->value, cgcVersion1Text, -1);

				} else {
					// Copy the version4 info
					iDatum_duplicate(&result->value, cgcVersion4Text, -1);
				}

			} else {
				result = iVariable_create(_VAR_TYPE_S32, NULL, true);
				if (index == 2)
				{
					// 0=runtime, 1=standard, 2=professional
					*(s32*)result->value.data = gnVersion2;	// Oh yeah!

				} else if (index == 3) {
					// Localized version
					*(s32*)result->value.data = gnVersion3;	// English

				} else {
					// Version in a form like Major.Minor as M.mm, or 123 for version 1.23
					*(s32*)result->value.data = gnVersion5;
				}
			}
			if (!result)
			{
				iError_report(cgcInternalError, false);
				return;
			}


		//////////
        // Return our converted result
		//////
			rpar->rp[0] = result;

    }
