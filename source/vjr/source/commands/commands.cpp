//////////
//
// /libsf/source/vjr/commands/commands.cpp
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
// Called to signal an error in the current running program
//
//////
	void iError_signal(u32 tnErrorNum, SComp* comp, bool tlInvasive, s8* tcExtraInfo, bool tlFatal)
	{
// TODO:  This will need to potentially break the program execution
		iError_report_byNumber(tnErrorNum, comp, tlInvasive);

		if (tlInvasive)
			debug_break;
	}




//////////
//
// Reports an error
//
//////
	void iError_report(cu8* constantErrorText, bool tlInvasive)
	{
		iError_report((u8*)constantErrorText, tlInvasive);
	}

	void iError_report(u8* errorText, bool tlInvasive)
	{
		if (!tlInvasive)
		{
			// Append the error to the EM
			if (screenData)
				iSEM_appendLine(screenData, errorText, -1, false);

			// Indicate it needs a re-render
			if (_screen_editbox)
				_screen_editbox->isDirtyRender = true;

		} else {
			// Immediate need
			MessageBox(NULL, (cs8*)errorText, (cs8*)cgcVjrError, MB_OK);
		}
	}




//////////
//
// Reports an error by number
//
//////
	void iError_report_byNumber(u32 tnErrorNum, SComp* comp, bool tlInvasive)
	{
		iError_report(iError_getText_byNumber(tnErrorNum), tlInvasive);

		// Flag the component
		if (comp && comp->line && comp->line->sourceCode && comp->line->sourceCode->_data && comp->line->sourceCode_populatedLength != 0)
		{
			// Flag it for error
			comp->isError = true;
		}
	}

	cu8* iError_getText_byNumber(u32 tnErrorNum)
	{
		switch (tnErrorNum)
		{
			case _ERROR_OUT_OF_MEMORY:						return(cgcOutOfMemory);
			case _ERROR_UNEXPECTED_COMMAND:					return(cgcUnexpectedCommand);
			case _ERROR_CONTEXT_HAS_CHANGED:				return(cgcContextHasChanged);
			case _ERROR_FULL_RECOMPILE_REQUIRED:			return(cgcFullRecompileRequired);
			case _ERROR_NOT_A_VARIABLE:						return(cgcNotAVariable);
			case _ERROR_NUMERIC_OVERFLOW:					return(cgcNumericOverflow);
			case _ERROR_NOT_NUMERIC:						return(cgcNotNumeric);
			case _ERROR_EMPTY_STRING:						return(cgcEmptyString);
			case _ERROR_SYNTAX:								return(cgcSyntaxError);
			case _ERROR_UNRECOGNIZED_PARAMETER:				return(cgcUnrecognizedParameter);
			case _ERROR_OUT_OF_RANGE:						return(cgcOutOfRange);
			case _ERROR_COMMA_EXPECTED:						return(cgcCommaExpected);
			case _ERROR_TOO_MANY_PARAMETERS:				return(cgcTooManyParameters);
			case _ERROR_DATA_TYPE_MISMATCH:					return(cgcDataTypeMismatch);
			case _ERROR_FEATURE_NOT_AVAILABLE:				return(cgcFeatureNotAvailable);
			case _ERROR_P1_IS_INCORRECT:					return(cgcP1IsIncorrect);
			case _ERROR_P2_IS_INCORRECT:					return(cgcP2IsIncorrect);
			case _ERROR_P3_IS_INCORRECT:					return(cgcP3IsIncorrect);
			case _ERROR_P4_IS_INCORRECT:					return(cgcP4IsIncorrect);
			case _ERROR_P5_IS_INCORRECT:					return(cgcP5IsIncorrect);
			case _ERROR_P6_IS_INCORRECT:					return(cgcP6IsIncorrect);
			case _ERROR_P7_IS_INCORRECT:					return(cgcP7IsIncorrect);
			case _ERROR_INTERNAL_ERROR:						return(cgcInternalError);
			case _ERROR_INVALID_ARGUMENT_TYPE_COUNT:		return(cgcInvalidArgumentTypeCountError);
			case _ERROR_VARIABLE_NOT_FOUND:					return(cgcVariableNotFoundError);
			case _ERROR_ALIAS_NOT_FOUND:					return(cgcAliasNotFoundError);
			case _ERROR_INVALID_WORK_AREA:					return(cgcInvalidWorkArea);
			case _ERROR_ALIAS_ALREADY_IN_USE:				return(cgcAliasAlreadyInUse);
			case _ERROR_PARENTHESIS_EXPECTED:				return(cgcParenthesisExpected);
			case _ERROR_MISSING_PARAMETER:					return(cgcMissingParameter);

			case _ERROR_DBF_UNABLE_TO_OPEN_TABLE:			return(cgcDbfUnableToOpenTable);
			case _ERROR_DBF_WORK_AREA_ALREADY_IN_USE:		return(cgcDbfWorkAreaAlreadyInUse);
			case _ERROR_DBF_ERROR_OPENING_DBC:				return(cgcDbfErrorOpeningDbc);
			case _ERROR_DBF_WORK_AREA_NOT_IN_USE:			return(cgcDbfWorkAreaNotInUse);
			case _ERROR_DBF_ERROR_READING_HEADER1:			return(cgcDbfErrorReadingHeader1);
			case _ERROR_DBF_UNKNOWN_TABLE_TYPE:				return(cgcDbfUnknownTableType);
			case _ERROR_DBF_MEMORY_ALLOCATION:				return(cgcDbfMemoryAllocation);
			case _ERROR_DBF_ERROR_READING_HEADER2:			return(cgcDbfErrorReadingHeader2);
			case _ERROR_DBF_TABLE_NAME_TOO_LONG:			return(cgcDbfTableNameTooLong);
			case _ERROR_DBF_MEMORY_ROW:						return(cgcDbfMemoryRow);
			case _ERROR_DBF_MEMORY_ORIGINAL:				return(cgcDbfMemoryOriginal);
			case _ERROR_DBF_MEMORY_INDEX:					return(cgcDbfMemoryIndex);
			case _ERROR_DBF_INVALID_WORK_AREA:				return(cgcDbfInvalidWorkArea);
			case _ERROR_DBF_NO_MORE_WORK_AREAS:				return(cgcDbfNoMoreWorkAreas);
			case _ERROR_DBF_LOCKING:						return(cgcDbfLocking);
			case _ERROR_DBF_WRITING:						return(cgcDbfWriting);
			case _ERROR_DBF_SEEKING:						return(cgcDbfSeeking);
			case _ERROR_DBF_NO_DATA:						return(cgcDbfNoData);
			case _ERROR_DBF_UNKNOWN_MEMO_FORMAT:			return(cgcDbfUnknownMemoFormat);

			case _ERROR_CONFLICTING_PARAMETERS:				return(cgcConflictingParameters);
			case _ERROR_PARAMETER_IS_INCORRECT:				return(cgcParameterIsIncorrect);
			case _ERROR_TABLE_ALREADY_IN_USE:				return(cgcTableAlreadyInUse);
			case _ERROR_PARAMETER_TOO_LONG:					return(cgcParameterTooLong);
			case _ERROR_UNABLE_TO_OPEN_DBC:					return(cgcUnableToOpenDbc);
			case _ERROR_DIVISION_BY_ZERO:					return(cgcDivisionByZero);
			case _ERROR_CANNOT_BE_NEGATIVE:					return(cgcCannotBeNegative);
			case _ERROR_CANNOT_BE_ZERO_OR_NEGATIVE:			return(cgcCannotBeZeroOrNegative);
			case _ERROR_UNABLE_TO_AUTOVALIDATE:				return(cgcUnableToAutoValidate);
			case _ERROR_DBF_GENERAL_ERROR:					return(cgcGeneralErrorDbf);
			case _ERROR_CANNOT_BE_ZERO:						return(cgcCannotBeZero);
			case _ERROR_MUST_BE_LOGICAL:					return(cgcMustBeLogical);
			case _ERROR_PARAMETER_MUST_BE_8_16_32_64:		return(cgcParameterMustBe8_16_32_64);
			case _ERROR_TOO_BIG_FOR_TARGET:					return(cgcTooBigForTarget);
			case _ERROR_NO_INDEX_IS_LOADED:					return(cgcNoIndexIsLoaded);
			case _ERROR_INVALID_INDEX_TAG:					return(cgcInvalidIndextag);
			case _ERROR_UNABLE_TO_SAVE:						return(cgcUnableToSave);
			case _ERROR_INVALID_PARAMETERS:					return(cgcInvalidParameters);
			case _ERROR_PARAMETER_MUST_BE_1:				return(cgcParameterMustBeOne);
			case _ERROR_INVALID_CORRUPT_NEEDS_REBUILT:		return(cgcIndexCorruptNeedsRebuilt);
			case _ERROR_UNABLE_TO_LOCK_FOR_WRITE:			return(cgcUnableToLockForWrite);
			case _ERROR_UNABLE_TO_LOCK_FOR_READ:			return(cgcUnableToLockForRead);
			case _ERROR_UNABLE_TO_INITIALIZE:				return(cgcUnableToInitialize);
			case _ERROR_UNKNOWN_FUNCTION:					return(cgcUnknownFunction);
			case _ERROR_DLL_NOT_FOUND:						return(cgcDllNotFound);
			case _ERROR_FUNCTION_NOT_FOUND:					return(cgcFunctionNotFound);
			case _ERROR_VARIABLE_IS_FIXED:					return(cgcVariableIsFixed);
			case _ERROR_FEATURE_NOT_YET_CODED:				return(cgcFeatureNotYetCoded);
			case _ERROR_NESTING_ERROR:						return(cgcNestingError);
			case _ERROR_TABLE_NUMBER_INVALID:				return(cgcTableNumberInvalid);
			case _ERROR_NO_ACTIVE_INDEX:					return(cgcNoActiveIndex);
			case _ERROR_NO_TABLE_IN_CURRENT_WORKAREA:		return(cgcNoTableInCurrentWorkArea);

			default:
				return(cgcUnspecifiedError);
		}
	}




//////////
//
// An internal error track that could be used to report information in the runtime
// environment
//
//////
	void iError_track(void)
	{
		debug_nop;
	}




//////////
//
// A place where silent errors pass thru without affecting anything.
// Ultimately they could be used to signal warnings, or meta data calls.
//
//////
	// May be called through use of error_silent() macro
	void iError_silent(s8* tcFuncName)
	{
		logfunc(tcFuncName);
		debug_nop;
	}




//////////
//
// Called to signal an error if the f32 value is outside the valid range for the target type
//
//////
	f32 iErrorCandidate_signalOutOfRange_f32(SErrorInfo* ei, f32 value, s32 tnVarType, SComp* compRelated, bool tlInvasive, s8* tcExtraInfo)
	{
		bool lError, lSignal;


		// Make sure our environment is sane
		if (!ei)
			return(value);	// Can't signal

		// Based on type, signal range
		lError	= false;
		lSignal	= false;
		switch (tnVarType)
		{
			case _VAR_TYPE_S8:
				if (value <= (f32)_s8_min || value >= (f32)_s8_max)
				{
					lError = true;
					if (!ei)
						lSignal = true;
				}
				break;

			case _VAR_TYPE_U8:
				if (value >= (f32)_u8_max)
				{
					lError = true;
					if (!ei)
						lSignal = true;
				}
				break;

			case _VAR_TYPE_S16:
				if (value <= (f32)_s16_min || value >= (f32)_s16_max)
				{
					lError = true;
					if (!ei)
						lSignal = true;
				}
				break;

			case _VAR_TYPE_U16:
				if (value >= (f32)_u16_max)
				{
					lError = true;
					if (!ei)
						lSignal = true;
				}
				break;

			case _VAR_TYPE_S32:
				if (value <= (f32)_s32_min || value >= (f32)_s32_max)
				{
					lError = true;
					if (!ei)
						lSignal = true;
				}
				break;

			case _VAR_TYPE_U32:
				if (value >= (f32)_u32_max)
				{
					lError = true;
					if (!ei)
						lSignal = true;
				}
				break;

			case _VAR_TYPE_S64:
				if (value <= (f32)_s64_min || value >= (f32)_s64_max)
				{
					lError = true;
					if (!ei)
						lSignal = true;
				}
				break;

			case _VAR_TYPE_U64:
				if (value >= (f32)_u64_max)
				{
					lError = true;
					if (!ei)
						lSignal = true;
				}
				break;
		}


		//////////
		// Was there an error?
		//////
			if (lError)
			{
				// Signal
				ei->error		= true;
				ei->errorNum	= _ERROR_OUT_OF_RANGE;
				ei->errorComp	= compRelated;
			}


		//////////
		// Should the error be signaled
		//////
			if (lSignal)
				iError_signal(_ERROR_OUT_OF_RANGE, compRelated, tlInvasive, tcExtraInfo, false);


		//////////
		// Return the input value
		//////
			return(value);
	}




//////////
//
// Called to signal an error if the f64 value is outside the valid range for the target type
//
//////
	f64 iErrorCandidate_signalOutOfRange_f64(SErrorInfo* ei, f64 value, s32 tnVarType, SComp* compRelated, bool tlInvasive, s8* tcExtraInfo)
	{
		bool lError, lSignal;


		// Make sure our environment is sane
		if (!ei)
			return(value);	// Can't signal

		// Based on type, signal range
		lError	= false;
		lSignal	= false;
		switch (tnVarType)
		{
			case _VAR_TYPE_S8:
				if (value <= (f64)_s8_min || value >= (f64)_s8_max)
				{
					lError = true;
					if (!ei)
						lSignal = true;
				}
				break;

			case _VAR_TYPE_U8:
				if (value >= (f64)_u8_max)
				{
					lError = true;
					if (!ei)
						lSignal = true;
				}
				break;

			case _VAR_TYPE_S16:
				if (value <= (f64)_s16_min || value >= (f64)_s16_max)
				{
					lError = true;
					if (!ei)
						lSignal = true;
				}
				break;

			case _VAR_TYPE_U16:
				if (value >= (f64)_u16_max)
				{
					lError = true;
					if (!ei)
						lSignal = true;
				}
				break;

			case _VAR_TYPE_S32:
				if (value <= (f64)_s32_min || value >= (f64)_s32_max)
				{
					lError = true;
					if (!ei)
						lSignal = true;
				}
				break;

			case _VAR_TYPE_U32:
				if (value >= (f64)_u32_max)
				{
					lError = true;
					if (!ei)
						lSignal = true;
				}
				break;

			case _VAR_TYPE_S64:
				if (value <= (f64)_s64_min || value >= (f64)_s64_max)
				{
					lError = true;
					if (!ei)
						lSignal = true;
				}
				break;

			case _VAR_TYPE_U64:
				if (value >= (f64)_u64_max)
				{
					lError = true;
					if (!ei)
						lSignal = true;
				}
				break;
		}


		//////////
		// Was there an error?
		//////
			if (lError)
			{
				// Signal
				ei->error		= true;
				ei->errorNum	= _ERROR_OUT_OF_RANGE;
				ei->errorComp	= compRelated;
			}


		//////////
		// Should the error be signaled
		//////
			if (lSignal)
				iError_signal(_ERROR_OUT_OF_RANGE, compRelated, tlInvasive, tcExtraInfo, false);


		//////////
		// Return the input value
		//////
			return(value);

	}




//////////
//
// Called to signal an error if the u16 value is outside the valid range for the target type
//
//////
	u8 iErrorCandidate_signalOutOfRange_u8(SErrorInfo* ei, u8 value, s32 tnVarType, SComp* compRelated, bool tlInvasive, s8* tcExtraInfo)
	{
		bool lError, lSignal;


		// Make sure our environment is sane
		if (!ei)
			return(value);	// Can't signal

		// Based on type, signal range
		lError	= false;
		lSignal	= false;
		switch (tnVarType)
		{
			case _VAR_TYPE_S8:
				if (value >= (u8)_s8_max)
				{
					lError = true;
					if (!ei)
						lSignal = true;
				}
				break;
		}


		//////////
		// Was there an error?
		//////
			if (lError)
			{
				// Signal
				ei->error		= true;
				ei->errorNum	= _ERROR_OUT_OF_RANGE;
				ei->errorComp	= compRelated;
			}


		//////////
		// Should the error be signaled
		//////
			if (lSignal)
				iError_signal(_ERROR_OUT_OF_RANGE, compRelated, tlInvasive, tcExtraInfo, false);


		//////////
		// Return the input value
		//////
			return(value);

	}




//////////
//
// Called to signal an error if the s16 value is outside the valid range for the target type
//
//////
	s16 iErrorCandidate_signalOutOfRange_s16(SErrorInfo* ei, s16 value, s32 tnVarType, SComp* compRelated, bool tlInvasive, s8* tcExtraInfo)
	{
		bool lError, lSignal;


		// Make sure our environment is sane
		if (!ei)
			return(value);	// Can't signal

		// Based on type, signal range
		lError	= false;
		lSignal	= false;
		switch (tnVarType)
		{
			case _VAR_TYPE_S8:
				if (value <= (s16)_s8_min || value >= (s16)_s8_max)
				{
					lError = true;
					if (!ei)
						lSignal = true;
				}
				break;

			case _VAR_TYPE_U8:
				if (value >= (s16)_u8_max)
				{
					lError = true;
					if (!ei)
						lSignal = true;
				}
				break;
		}


		//////////
		// Was there an error?
		//////
			if (lError)
			{
				// Signal
				ei->error		= true;
				ei->errorNum	= _ERROR_OUT_OF_RANGE;
				ei->errorComp	= compRelated;
			}


		//////////
		// Should the error be signaled
		//////
			if (lSignal)
				iError_signal(_ERROR_OUT_OF_RANGE, compRelated, tlInvasive, tcExtraInfo, false);


		//////////
		// Return the input value
		//////
			return(value);

	}




//////////
//
// Called to signal an error if the u16 value is outside the valid range for the target type
//
//////
	u16 iErrorCandidate_signalOutOfRange_u16(SErrorInfo* ei, u16 value, s32 tnVarType, SComp* compRelated, bool tlInvasive, s8* tcExtraInfo)
	{
		bool lError, lSignal;


		// Make sure our environment is sane
		if (!ei)
			return(value);	// Can't signal

		// Based on type, signal range
		lError	= false;
		lSignal	= false;
		switch (tnVarType)
		{
			case _VAR_TYPE_S8:
				if (value >= (u16)_s8_max)
				{
					lError = true;
					if (!ei)
						lSignal = true;
				}
				break;

			case _VAR_TYPE_U8:
				if (value >= (u16)_u8_max)
				{
					lError = true;
					if (!ei)
						lSignal = true;
				}
				break;

			case _VAR_TYPE_S16:
				if (value >= (u16)_s16_max)
				{
					lError = true;
					if (!ei)
						lSignal = true;
				}
				break;
		}


		//////////
		// Was there an error?
		//////
			if (lError)
			{
				// Signal
				ei->error		= true;
				ei->errorNum	= _ERROR_OUT_OF_RANGE;
				ei->errorComp	= compRelated;
			}


		//////////
		// Should the error be signaled
		//////
			if (lSignal)
				iError_signal(_ERROR_OUT_OF_RANGE, compRelated, tlInvasive, tcExtraInfo, false);


		//////////
		// Return the input value
		//////
			return(value);

	}




//////////
//
// Called to signal an error if the s32 value is outside the valid range for the target type
//
//////
	s32 iErrorCandidate_signalOutOfRange_s32(SErrorInfo* ei, s32 value, s32 tnVarType, SComp* compRelated, bool tlInvasive, s8* tcExtraInfo)
	{
		bool lError, lSignal;


		// Make sure our environment is sane
		if (!ei)
			return(value);	// Can't signal

		// Based on type, signal range
		lError	= false;
		lSignal	= false;
		switch (tnVarType)
		{
			case _VAR_TYPE_S8:
				if (value <= (s32)_s8_min || value >= (s32)_s8_max)
				{
					lError = true;
					if (!ei)
						lSignal = true;
				}
				break;

			case _VAR_TYPE_U8:
				if (value >= (s32)_u8_max)
				{
					lError = true;
					if (!ei)
						lSignal = true;
				}
				break;

			case _VAR_TYPE_S16:
				if (value <= (s32)_s16_min || value >= (s32)_s16_max)
				{
					lError = true;
					if (!ei)
						lSignal = true;
				}
				break;

			case _VAR_TYPE_U16:
				if (value >= (s32)_u16_max)
				{
					lError = true;
					if (!ei)
						lSignal = true;
				}
				break;
		}


		//////////
		// Was there an error?
		//////
			if (lError)
			{
				// Signal
				ei->error		= true;
				ei->errorNum	= _ERROR_OUT_OF_RANGE;
				ei->errorComp	= compRelated;
			}


		//////////
		// Should the error be signaled
		//////
			if (lSignal)
				iError_signal(_ERROR_OUT_OF_RANGE, compRelated, tlInvasive, tcExtraInfo, false);


		//////////
		// Return the input value
		//////
			return(value);

	}




//////////
//
// Called to signal an error if the s32 value is outside the valid range for the target type
//
//////
	u32 iErrorCandidate_signalOutOfRange_u32(SErrorInfo* ei, u32 value, s32 tnVarType, SComp* compRelated, bool tlInvasive, s8* tcExtraInfo)
	{
		bool lError, lSignal;


		// Make sure our environment is sane
		if (!ei)
			return(value);	// Can't signal

		// Based on type, signal range
		lError	= false;
		lSignal	= false;
		switch (tnVarType)
		{
			case _VAR_TYPE_S8:
				if (value >= (u32)_s8_max)
				{
					lError = true;
					if (!ei)
						lSignal = true;
				}
				break;

			case _VAR_TYPE_U8:
				if (value >= (u32)_u8_max)
				{
					lError = true;
					if (!ei)
						lSignal = true;
				}
				break;

			case _VAR_TYPE_S16:
				if (value >= (u32)_s16_max)
				{
					lError = true;
					if (!ei)
						lSignal = true;
				}
				break;

			case _VAR_TYPE_U16:
				if (value >= (u32)_u16_max)
				{
					lError = true;
					if (!ei)
						lSignal = true;
				}
				break;
		}


		//////////
		// Was there an error?
		//////
			if (lError)
			{
				// Signal
				ei->error		= true;
				ei->errorNum	= _ERROR_OUT_OF_RANGE;
				ei->errorComp	= compRelated;
			}


		//////////
		// Should the error be signaled
		//////
			if (lSignal)
				iError_signal(_ERROR_OUT_OF_RANGE, compRelated, tlInvasive, tcExtraInfo, false);


		//////////
		// Return the input value
		//////
			return(value);

	}




//////////
//
// Called to signal an error if the s64 value is outside the valid range for the target type
//
//////
	s64 iErrorCandidate_signalOutOfRange_s64(SErrorInfo* ei, s64 value, s32 tnVarType, SComp* compRelated, bool tlInvasive, s8* tcExtraInfo)
	{
		bool lError, lSignal;


		// Make sure our environment is sane
		if (!ei)
			return(value);	// Can't signal

		// Based on type, signal range
		lError	= false;
		lSignal	= false;
		switch (tnVarType)
		{
			case _VAR_TYPE_S8:
				if (value <= (s64)_s8_min || value >= (s64)_s8_max)
				{
					lError = true;
					if (!ei)
						lSignal = true;
				}
				break;

			case _VAR_TYPE_U8:
				if (value >= (s64)_u8_max)
				{
					lError = true;
					if (!ei)
						lSignal = true;
				}
				break;

			case _VAR_TYPE_S16:
				if (value <= (s64)_s16_min || value >= (s64)_s16_max)
				{
					lError = true;
					if (!ei)
						lSignal = true;
				}
				break;

			case _VAR_TYPE_U16:
				if (value >= (s64)_u16_max)
				{
					lError = true;
					if (!ei)
						lSignal = true;
				}
				break;

			case _VAR_TYPE_S32:
				if (value <= (s64)_s32_min || value >= (s64)_s32_max)
				{
					lError = true;
					if (!ei)
						lSignal = true;
				}
				break;

			case _VAR_TYPE_U32:
				if (value >= (s64)_u32_max)
				{
					lError = true;
					if (!ei)
						lSignal = true;
				}
				break;
		}


		//////////
		// Was there an error?
		//////
			if (lError)
			{
				// Signal
				ei->error		= true;
				ei->errorNum	= _ERROR_OUT_OF_RANGE;
				ei->errorComp	= compRelated;
			}


		//////////
		// Should the error be signaled
		//////
			if (lSignal)
				iError_signal(_ERROR_OUT_OF_RANGE, compRelated, tlInvasive, tcExtraInfo, false);


		//////////
		// Return the input value
		//////
			return(value);

	}




//////////
//
// Called to signal an error if the s64 value is outside the valid range for the target type
//
//////
	u64 iErrorCandidate_signalOutOfRange_u64(SErrorInfo* ei, u64 value, s32 tnVarType, SComp* compRelated, bool tlInvasive, s8* tcExtraInfo)
	{
		bool lError, lSignal;


		// Make sure our environment is sane
		if (!ei)
			return(value);	// Can't signal

		// Based on type, signal range
		lError	= false;
		lSignal	= false;
		switch (tnVarType)
		{
			case _VAR_TYPE_S8:
				if (value >= (u64)_s8_max)
				{
					lError = true;
					if (!ei)
						lSignal = true;
				}
				break;

			case _VAR_TYPE_U8:
				if (value >= (u64)_u8_max)
				{
					lError = true;
					if (!ei)
						lSignal = true;
				}
				break;

			case _VAR_TYPE_S16:
				if (value >= (u64)_s16_max)
				{
					lError = true;
					if (!ei)
						lSignal = true;
				}
				break;

			case _VAR_TYPE_U16:
				if (value >= (u64)_u16_max)
				{
					lError = true;
					if (!ei)
						lSignal = true;
				}
				break;

			case _VAR_TYPE_S32:
				if (value >= (u64)_s32_max)
				{
					lError = true;
					if (!ei)
						lSignal = true;
				}
				break;

			case _VAR_TYPE_U32:
				if (value >= (u64)_u32_max)
				{
					lError = true;
					if (!ei)
						lSignal = true;
				}
				break;

			case _VAR_TYPE_S64:
				if (value >= (u64)_s64_max)
				{
					lError = true;
					if (!ei)
						lSignal = true;
				}
				break;
		}


		//////////
		// Was there an error?
		//////
			if (lError)
			{
				// Signal
				ei->error		= true;
				ei->errorNum	= _ERROR_OUT_OF_RANGE;
				ei->errorComp	= compRelated;
			}


		//////////
		// Should the error be signaled
		//////
			if (lSignal)
				iError_signal(_ERROR_OUT_OF_RANGE, compRelated, tlInvasive, tcExtraInfo, false);


		//////////
		// Return the input value
		//////
			return(value);

	}




//////////
//
// Called to signal an error if the numeric value is outside the valid range for the target type
//
//////
	f64 iErrorCandidate_signalOutOfRange_numeric(SErrorInfo* ei, SDatum* value, s32 tnVarType, SComp* compRelated, bool tlInvasive, s8* tcExtraInfo)
	{
		f64	lfValue;
		s8	buffer[64];
		bool lError, lSignal;


		// Based on the test type, make sure it's in range
		lError	= false;
		lSignal	= false;
		lfValue = 0.0f;
		if (value && value->length >= 1 && (u32)value->length <= sizeof(buffer) - 1)
		{
			// Copy text to null-terminate
			memcpy(buffer, value->data_s8, value->length);
			buffer[value->length] = 0;

			// Convert to f64
			lfValue = atof(value->data_s8);

			// Make sure our environment is sane
			if (!ei)
				return(lfValue);	// Can't signal

			// Based on the type, check its range
			switch (tnVarType)
			{
				case _VAR_TYPE_S8:
					if (lfValue <= (f64)_s8_min || lfValue >= (f64)_s8_max)
					{
						lError = true;
						if (!ei)
							lSignal = true;
					}
					break;

				case _VAR_TYPE_U8:
					if (lfValue >= (f64)_u8_max)
					{
						lError = true;
						if (!ei)
							lSignal = true;
					}
					break;

				case _VAR_TYPE_S16:
					if (lfValue <= (f64)_s16_min || lfValue >= (f64)_s16_max)
					{
						lError = true;
						if (!ei)
							lSignal = true;
					}
					break;

				case _VAR_TYPE_U16:
					if (lfValue >= (f64)_u16_max)
					{
						lError = true;
						if (!ei)
							lSignal = true;
					}
					break;

				case _VAR_TYPE_S32:
					if (lfValue <= (f64) _s32_min || lfValue >= (f64)_s32_max)
					{
						lError = true;
						if (!ei)
							lSignal = true;
					}
					break;

				case _VAR_TYPE_U32:
					if (lfValue >= (f64)_u32_max)
					{
						lError = true;
						if (!ei)
							lSignal = true;
					}
					break;

				case _VAR_TYPE_S64:
					if (lfValue <= (f64)_s64_min || lfValue >= (f64)_s64_max)
					{
						lError = true;
						if (!ei)
							lSignal = true;
					}
					break;

				case _VAR_TYPE_U64:
					if (lfValue >= (f64)_u64_max)
					{
						lError = true;
						if (!ei)
							lSignal = true;
					}
					break;

				case _VAR_TYPE_F32:
					if (lfValue <= (f64)_s32_min || lfValue >= (f64)_s32_max)
					{
						lError = true;
						if (!ei)
							lSignal = true;
					}
					break;
			}

		} else {
			// Signal the lowest possible value
			lfValue = (f64)_f64_min;
		}


		//////////
		// Was there an error?
		//////
			if (lError)
			{
				// Signal
				ei->error		= true;
				ei->errorNum	= _ERROR_OUT_OF_RANGE;
				ei->errorComp	= compRelated;
			}


		//////////
		// Should the error be signaled
		//////
			if (lSignal)
				iError_signal(_ERROR_OUT_OF_RANGE, compRelated, tlInvasive, tcExtraInfo, false);


		//////////
		// Return the value
		//////
			return(lfValue);

	}




//////////
// The following are broken out to make source files shorter
//////
#if defined(__linux__) || defined(__solaris__)
	#include "/libsf/source/vjr/source/commands/functions/a.cpp"
	#include "/libsf/source/vjr/source/commands/functions/b.cpp"
	#include "/libsf/source/vjr/source/commands/functions/c.cpp"
	#include "/libsf/source/vjr/source/commands/functions/d.cpp"
	#include "/libsf/source/vjr/source/commands/functions/e.cpp"
	#include "/libsf/source/vjr/source/commands/functions/f.cpp"
	#include "/libsf/source/vjr/source/commands/functions/g.cpp"
	#include "/libsf/source/vjr/source/commands/functions/h.cpp"
	#include "/libsf/source/vjr/source/commands/functions/i.cpp"
	#include "/libsf/source/vjr/source/commands/functions/j.cpp"
	#include "/libsf/source/vjr/source/commands/functions/k.cpp"
	#include "/libsf/source/vjr/source/commands/functions/l.cpp"
	#include "/libsf/source/vjr/source/commands/functions/m.cpp"
	#include "/libsf/source/vjr/source/commands/functions/n.cpp"
	#include "/libsf/source/vjr/source/commands/functions/o.cpp"
	#include "/libsf/source/vjr/source/commands/functions/p.cpp"
	#include "/libsf/source/vjr/source/commands/functions/q.cpp"
	#include "/libsf/source/vjr/source/commands/functions/r.cpp"
	#include "/libsf/source/vjr/source/commands/functions/s.cpp"
	#include "/libsf/source/vjr/source/commands/functions/t.cpp"
	#include "/libsf/source/vjr/source/commands/functions/u.cpp"
	#include "/libsf/source/vjr/source/commands/functions/v.cpp"
	#include "/libsf/source/vjr/source/commands/functions/w.cpp"
	#include "/libsf/source/vjr/source/commands/functions/x.cpp"
	#include "/libsf/source/vjr/source/commands/functions/y.cpp"
	#include "/libsf/source/vjr/source/commands/functions/z.cpp"

	// Apr.26.2015 -- Temporarily isolated into one area:
	#include "/libsf/source/vjr/source/commands/functions/rick_in_progress.cpp"

#else
	#include "\libsf\source\vjr\source\commands\functions\a.cpp"
	#include "\libsf\source\vjr\source\commands\functions\b.cpp"
	#include "\libsf\source\vjr\source\commands\functions\c.cpp"
	#include "\libsf\source\vjr\source\commands\functions\d.cpp"
	#include "\libsf\source\vjr\source\commands\functions\e.cpp"
	#include "\libsf\source\vjr\source\commands\functions\f.cpp"
	#include "\libsf\source\vjr\source\commands\functions\g.cpp"
	#include "\libsf\source\vjr\source\commands\functions\h.cpp"
	#include "\libsf\source\vjr\source\commands\functions\i.cpp"
	#include "\libsf\source\vjr\source\commands\functions\j.cpp"
	#include "\libsf\source\vjr\source\commands\functions\k.cpp"
	#include "\libsf\source\vjr\source\commands\functions\l.cpp"
	#include "\libsf\source\vjr\source\commands\functions\m.cpp"
	#include "\libsf\source\vjr\source\commands\functions\n.cpp"
	#include "\libsf\source\vjr\source\commands\functions\o.cpp"
	#include "\libsf\source\vjr\source\commands\functions\p.cpp"
	#include "\libsf\source\vjr\source\commands\functions\q.cpp"
	#include "\libsf\source\vjr\source\commands\functions\r.cpp"
	#include "\libsf\source\vjr\source\commands\functions\s.cpp"
	#include "\libsf\source\vjr\source\commands\functions\t.cpp"
	#include "\libsf\source\vjr\source\commands\functions\u.cpp"
	#include "\libsf\source\vjr\source\commands\functions\v.cpp"
	#include "\libsf\source\vjr\source\commands\functions\w.cpp"
	#include "\libsf\source\vjr\source\commands\functions\x.cpp"
	#include "\libsf\source\vjr\source\commands\functions\y.cpp"
	#include "\libsf\source\vjr\source\commands\functions\z.cpp"

	// Apr.26.2015 -- Temporarily isolated into one area:
	#include "\libsf\source\vjr\source\commands\functions\rick_in_progress.cpp"
#endif




//////////
//
// Function: CONCATENATE()
// Note:  This is a temporary function until the main compiler engine is coded.
// Concatenates two strings together.
//
//////
// Version 0.58   (Determine the current version from the header in vjr.cpp)
// Last update:
//     Jul.13.2014
//////
// Change log:
//     Jul.13.2014 - Initial creation
//////
// Parameters:
//     p1		-- String1
//     p2		-- String2
//
//////
// Returns:
//    The sum of p1 + p2
//
//////
	void function_concatenate(SReturnsParams* rpar)
	{
		SVariable*	varString1	= rpar->ip[0];
		SVariable*	varString2	= rpar->ip[1];
		SVariable*	result;


		//////////
		// Parameter 1 must be character
		//////
			rpar->rp[0] = NULL;
			if (!iVariable_isValid(varString1) || !iVariable_isTypeCharacter(varString1))
			{
				iError_report_byNumber(_ERROR_P1_IS_INCORRECT, iVariable_get_relatedComp(varString1), false);
				return;
			}


		//////////
		// Parameter 2 must be character
		//////
			if (!iVariable_isValid(varString2) || !iVariable_isTypeCharacter(varString2))
			{
				iError_report_byNumber(_ERROR_P2_IS_INCORRECT, iVariable_get_relatedComp(varString2), false);
				return;
			}


		//////////
		// Allocate enough space for the assemblage
		//////
			result = iVariable_create(_VAR_TYPE_CHARACTER, NULL, true);
			if (!result)
			{
				iError_report(cgcInternalError, false);
				return;
			}

			// Populate
			iDatum_allocateSpace(&result->value, varString1->value.length + varString2->value.length);

			// Create the concatenated string
			memcpy(result->value.data_s8,								varString1->value.data_s8,		varString1->value.length);
			memcpy(result->value.data_s8 + varString1->value.length,	varString2->value.data_s8,		varString2->value.length);


		//////////
		// Indicate our result
		//////
			rpar->rp[0] = result;

	}




//////////
//
// Function: ADD()
// Note:  This is a temporary function until the main compiler engine is coded.
// Adds two values and returns the result.
//
//////
// Version 0.58   (Determine the current version from the header in vjr.cpp)
// Last update:
//     Jul.13.2014
//////
// Change log:
//     Jul.13.2014 - Initial creation
//////
// Parameters:
//     p1		-- Value1 to add
//     p2		-- Value2 to add
//
//////
// Returns:
//    The sum of p1 + p2
//
//////
	void function_add(SReturnsParams* rpar)
	{
		SVariable*	varNum1	= rpar->ip[0];
		SVariable*	varNum2	= rpar->ip[1];
		s64			lnValue1, lnValue2;
		f64			lfValue1, lfValue2;
		bool		error;
		u32			errorNum;
		SVariable*	result;


		//////////
		// Parameter 1 must be numeric
		//////
			rpar->rp[0] = NULL;
			if (!iVariable_isValid(varNum1) || !iVariable_isTypeNumeric(varNum1))
			{
				iError_report_byNumber(_ERROR_P1_IS_INCORRECT, iVariable_get_relatedComp(varNum1), false);
				return;
			}


		//////////
		// Parameter 2 must be numeric
		//////
			if (!iVariable_isValid(varNum2) || !iVariable_isTypeNumeric(varNum2))
			{
				iError_report_byNumber(_ERROR_P2_IS_INCORRECT, iVariable_get_relatedComp(varNum2), false);
				return;
			}


		//////////
		// Determine what we're comparing
		//////
			if (iVariable_isTypeFloatingPoint(varNum1))
			{
				// p1 is floating point, meaning the result will be too
				lfValue1 = iiVariable_getAs_f64(varNum1, false, &error, &errorNum);
				if (error)
				{
					iError_report_byNumber(errorNum, iVariable_get_relatedComp(varNum1), false);
					return;
				}

				// Create our floating point result
				result = iVariable_create(_VAR_TYPE_F64, NULL, true);
				if (result)
				{
					// Grab p2
					if (iVariable_isTypeFloatingPoint(varNum2))
					{
						// p2 is floating point
						lfValue2 = iiVariable_getAs_f64(varNum2, false, &error, &errorNum);
						if (error)
						{
							iError_report_byNumber(errorNum, iVariable_get_relatedComp(varNum2), false);
							return;
						}

						// Store the result
						*(f64*)result->value.data_s8 = lfValue1 + lfValue2;

					} else  {
						// p2 is not floating point, so we'll get it as an integer
						lnValue2 = iiVariable_getAs_s64(varNum2, false, &error, &errorNum);
						if (error)
						{
							iError_report_byNumber(errorNum, iVariable_get_relatedComp(varNum2), false);
							return;
						}

						// Store the result
						*(f64*)result->value.data_s8 = lfValue1 + (f64)lnValue2;
					}
				}

			} else {
				// p1 is integer, result is determined by what p2 is, either integer or floating point
				lnValue1 = iiVariable_getAs_s64(varNum1, false, &error, &errorNum);
				if (error)
				{
					iError_report_byNumber(errorNum, iVariable_get_relatedComp(varNum1), false);
					return;
				}

				// Grab p2
				if (iVariable_isTypeFloatingPoint(varNum2))
				{
					// p2 is floating point
					lfValue2 = iiVariable_getAs_f64(varNum2, false, &error, &errorNum);
					if (error)
					{
						iError_report_byNumber(errorNum, iVariable_get_relatedComp(varNum2), false);
						return;
					}

					// Create our floating point result
					result = iVariable_create(_VAR_TYPE_F64, NULL, true);
					if (result)
						*(f64*)result->value.data_s8 = (f64)lnValue1 + lfValue2;

				} else  {
					// p2 is not floating point, so we'll get it as an integer
					lnValue2 = iiVariable_getAs_s64(varNum2, false, &error, &errorNum);
					if (error)
					{
						iError_report_byNumber(errorNum, iVariable_get_relatedComp(varNum2), false);
						return;
					}

					// Create our floating point result
					result = iVariable_create(_VAR_TYPE_S64, NULL, true);
					if (result)
						*(s64*)result->value.data_s8 = lnValue1 + lnValue2;
				}
			}


		//////////
		// Are we good?
		//////
			if (!result)
				iError_report(cgcInternalError, false);


		//////////
		// Indicate our result
		//////
			rpar->rp[0] = result;

	}




//////////
//
// Function: SUB()
// Note:  This is a temporary function until the main compiler engine is coded.
// Subtracts two values and returns the result.
//
//////
// Version 0.58   (Determine the current version from the header in vjr.cpp)
// Last update:
//     Jul.13.2014
//////
// Change log:
//     Jul.13.2014 - Initial creation
//////
// Parameters:
//     p1		-- Value1 to subtract value2 from
//     p2		-- Value2
//
//////
// Returns:
//    The sum of p1 - p2
//
//////
	void function_sub(SReturnsParams* rpar)
	{
		SVariable*	varNum1	= rpar->ip[0];
		SVariable*	varNum2	= rpar->ip[1];
		s64			lnValue1, lnValue2;
		f64			lfValue1, lfValue2;
		bool		error;
		u32			errorNum;
		SVariable*	result;


		//////////
		// Parameter 1 must be numeric
		//////
			rpar->rp[0] = NULL;
			if (!iVariable_isValid(varNum1) || !iVariable_isTypeNumeric(varNum1))
			{
				iError_report_byNumber(_ERROR_P1_IS_INCORRECT, iVariable_get_relatedComp(varNum1), false);
				return;
			}


		//////////
		// Parameter 2 must be numeric
		//////
			if (!iVariable_isValid(varNum2) || !iVariable_isTypeNumeric(varNum2))
			{
				iError_report_byNumber(_ERROR_P2_IS_INCORRECT, iVariable_get_relatedComp(varNum2), false);
				return;
			}


		//////////
		// Determine what we're comparing
		//////
			if (iVariable_isTypeFloatingPoint(varNum1))
			{
				// p1 is floating point, meaning the result will be too
				lfValue1 = iiVariable_getAs_f64(varNum1, false, &error, &errorNum);
				if (error)
				{
					iError_report_byNumber(errorNum, iVariable_get_relatedComp(varNum1), false);
					return;
				}

				// Create our floating point result
				result = iVariable_create(_VAR_TYPE_F64, NULL, true);
				if (result)
				{
					// Grab p2
					if (iVariable_isTypeFloatingPoint(varNum2))
					{
						// p2 is floating point
						lfValue2 = iiVariable_getAs_f64(varNum2, false, &error, &errorNum);
						if (error)
						{
							iError_report_byNumber(errorNum, iVariable_get_relatedComp(varNum2), false);
							return;
						}

						// Store the result
						*(f64*)result->value.data_s8 = lfValue1 - lfValue2;

					} else  {
						// p2 is not floating point, so we'll get it as an integer
						lnValue2 = iiVariable_getAs_s64(varNum2, false, &error, &errorNum);
						if (error)
						{
							iError_report_byNumber(errorNum, iVariable_get_relatedComp(varNum2), false);
							return;
						}

						// Store the result
						*(f64*)result->value.data_s8 = lfValue1 - (f64)lnValue2;
					}
				}

			} else {
				// p1 is integer, result is determined by what p2 is, either integer or floating point
				lnValue1 = iiVariable_getAs_s64(varNum1, false, &error, &errorNum);
				if (error)
				{
					iError_report_byNumber(errorNum, iVariable_get_relatedComp(varNum1), false);
					return;
				}

				// Grab p2
				if (iVariable_isTypeFloatingPoint(varNum2))
				{
					// p2 is floating point
					lfValue2 = iiVariable_getAs_f64(varNum2, false, &error, &errorNum);
					if (error)
					{
						iError_report_byNumber(errorNum, iVariable_get_relatedComp(varNum2), false);
						return;
					}

					// Create our floating point result
					result = iVariable_create(_VAR_TYPE_F64, NULL, true);
					if (result)
						*(f64*)result->value.data_s8 = (f64)lnValue1 - lfValue2;

				} else  {
					// p2 is not floating point, so we'll get it as an integer
					lnValue2 = iiVariable_getAs_s64(varNum2, false, &error, &errorNum);
					if (error)
					{
						iError_report_byNumber(errorNum, iVariable_get_relatedComp(varNum2), false);
						return;
					}

					// Create our floating point result
					result = iVariable_create(_VAR_TYPE_S64, NULL, true);
					if (result)
						*(s64*)result->value.data_s8 = lnValue1 - lnValue2;
				}
			}


		//////////
		// Are we good?
		//////
			if (!result)
				iError_report(cgcInternalError, false);


		//////////
		// Indicate our result
		//////
			rpar->rp[0] = result;

	}




//////////
//
// Function: MUL()
// Note:  This is a temporary function until the main compiler engine is coded.
// Multiplies two values and returns the result.
//
//////
// Version 0.58   (Determine the current version from the header in vjr.cpp)
// Last update:
//     Jul.13.2014
//////
// Change log:
//     Jul.13.2014 - Initial creation
//////
// Parameters:
//     p1		-- Value1 to multiply
//     p2		-- Value2 to multiply
//
//////
// Returns:
//    The sum of p1 * p2
//
//////
	void function_mul(SReturnsParams* rpar)
	{
		SVariable*	varNum1	= rpar->ip[0];
		SVariable*	varNum2	= rpar->ip[1];
		s64			lnValue1, lnValue2;
		f64			lfValue1, lfValue2;
		bool		error;
		u32			errorNum;
		SVariable*	result;


		//////////
		// Parameter 1 must be numeric
		//////
			rpar->rp[0] = NULL;
			if (!iVariable_isValid(varNum1) || !iVariable_isTypeNumeric(varNum1))
			{
				iError_report_byNumber(_ERROR_P1_IS_INCORRECT, iVariable_get_relatedComp(varNum1), false);
				return;
			}


		//////////
		// Parameter 2 must be numeric
		//////
			if (!iVariable_isValid(varNum2) || !iVariable_isTypeNumeric(varNum2))
			{
				iError_report_byNumber(_ERROR_P2_IS_INCORRECT, iVariable_get_relatedComp(varNum2), false);
				return;
			}


		//////////
		// Determine what we're comparing
		//////
			if (iVariable_isTypeFloatingPoint(varNum1))
			{
				// p1 is floating point, meaning the result will be too
				lfValue1 = iiVariable_getAs_f64(varNum1, false, &error, &errorNum);
				if (error)
				{
					iError_report_byNumber(errorNum, iVariable_get_relatedComp(varNum1), false);
					return;
				}

				// Create our floating point result
				result = iVariable_create(_VAR_TYPE_F64, NULL, true);
				if (result)
				{
					// Grab p2
					if (iVariable_isTypeFloatingPoint(varNum2))
					{
						// p2 is floating point
						lfValue2 = iiVariable_getAs_f64(varNum2, false, &error, &errorNum);
						if (error)
						{
							iError_report_byNumber(errorNum, iVariable_get_relatedComp(varNum2), false);
							return;
						}

						// Store the result
						*(f64*)result->value.data_s8 = lfValue1 * lfValue2;

					} else  {
						// p2 is not floating point, so we'll get it as an integer
						lnValue2 = iiVariable_getAs_s64(varNum2, false, &error, &errorNum);
						if (error)
						{
							iError_report_byNumber(errorNum, iVariable_get_relatedComp(varNum2), false);
							return;
						}

						// Store the result
						*(f64*)result->value.data_s8 = lfValue1 * (f64)lnValue2;
					}
				}

			} else {
				// p1 is integer, result is determined by what p2 is, either integer or floating point
				lnValue1 = iiVariable_getAs_s64(varNum1, false, &error, &errorNum);
				if (error)
				{
					iError_report_byNumber(errorNum, iVariable_get_relatedComp(varNum1), false);
					return;
				}

				// Grab p2
				if (iVariable_isTypeFloatingPoint(varNum2))
				{
					// p2 is floating point
					lfValue2 = iiVariable_getAs_f64(varNum2, false, &error, &errorNum);
					if (error)
					{
						iError_report_byNumber(errorNum, iVariable_get_relatedComp(varNum2), false);
						return;
					}

					// Create our floating point result
					result = iVariable_create(_VAR_TYPE_F64, NULL, true);
					if (result)
						*(f64*)result->value.data_s8 = (f64)lnValue1 * lfValue2;

				} else  {
					// p2 is not floating point, so we'll get it as an integer
					lnValue2 = iiVariable_getAs_s64(varNum2, false, &error, &errorNum);
					if (error)
					{
						iError_report_byNumber(errorNum, iVariable_get_relatedComp(varNum2), false);
						return;
					}

					// Create our floating point result
					result = iVariable_create(_VAR_TYPE_S64, NULL, true);
					if (result)
						*(s64*)result->value.data_s8 = lnValue1 * lnValue2;
				}
			}


		//////////
		// Are we good?
		//////
			if (!result)
				iError_report(cgcInternalError, false);


		//////////
		// Indicate our result
		//////
			rpar->rp[0] = result;

	}




//////////
//
// Function: DIV()
// Note:  This is a temporary function until the main compiler engine is coded.
// Divides two values and returns the result.
//
//////
// Version 0.58   (Determine the current version from the header in vjr.cpp)
// Last update:
//     Jul.13.2014
//////
// Change log:
//     Jul.13.2014 - Initial creation
//////
// Parameters:
//     p1		-- Value1 to divide by value2
//     p2		-- Value2
//
//////
// Returns:
//    The sum of p1 / p2
//
//////
	void function_div(SReturnsParams* rpar)
	{
		SVariable*	varNum1	= rpar->ip[0];
		SVariable*	varNum2	= rpar->ip[1];
		s64			lnValue1, lnValue2;
		f64			lfValue1, lfValue2;
		bool		error;
		u32			errorNum;
		SVariable*	result;


		//////////
		// Parameter 1 must be numeric
		//////
			rpar->rp[0] = NULL;
			if (!iVariable_isValid(varNum1) || !iVariable_isTypeNumeric(varNum1))
			{
				iError_report_byNumber(_ERROR_P1_IS_INCORRECT, iVariable_get_relatedComp(varNum1), false);
				return;
			}


		//////////
		// Parameter 2 must be numeric
		//////
			if (!iVariable_isValid(varNum2) || !iVariable_isTypeNumeric(varNum2))
			{
				iError_report_byNumber(_ERROR_P2_IS_INCORRECT, iVariable_get_relatedComp(varNum2), false);
				return;
			}


		//////////
		// Parameter 2 cannot be 0
		//////
			lfValue1 = iiVariable_getAs_f64(varNum2, false, &error, &errorNum);
			if (lfValue1 == 0.0 || error)
			{
				iError_report_byNumber(_ERROR_P2_IS_INCORRECT, iVariable_get_relatedComp(varNum2), false);
				return;
			}


		//////////
		// Determine what we're comparing
		//////
			if (iVariable_isTypeFloatingPoint(varNum1))
			{
				// p1 is floating point, meaning the result will be too
				lfValue1 = iiVariable_getAs_f64(varNum1, false, &error, &errorNum);
				if (error)
				{
					iError_report_byNumber(errorNum, iVariable_get_relatedComp(varNum1), false);
					return;
				}

				// Create our floating point result
				result = iVariable_create(_VAR_TYPE_F64, NULL, true);
				if (result)
				{
					// Grab p2
					if (iVariable_isTypeFloatingPoint(varNum2))
					{
						// p2 is floating point
						lfValue2 = iiVariable_getAs_f64(varNum2, false, &error, &errorNum);
						if (error)
						{
							iError_report_byNumber(errorNum, iVariable_get_relatedComp(varNum2), false);
							return;
						}

						// Store the result
						*(f64*)result->value.data_s8 = lfValue1 / lfValue2;

					} else  {
						// p2 is not floating point, so we'll get it as an integer
						lnValue2 = iiVariable_getAs_s64(varNum2, false, &error, &errorNum);
						if (error)
						{
							iError_report_byNumber(errorNum, iVariable_get_relatedComp(varNum2), false);
							return;
						}

						// Store the result
						*(f64*)result->value.data_s8 = lfValue1 / (f64)lnValue2;
					}
				}

			} else {
				// p1 is integer, result is determined by what p2 is, either integer or floating point
				lnValue1 = iiVariable_getAs_s64(varNum1, false, &error, &errorNum);
				if (error)
				{
					iError_report_byNumber(errorNum, iVariable_get_relatedComp(varNum1), false);
					return;
				}

				// Create our floating point result
				result = iVariable_create(_VAR_TYPE_F64, NULL, true);
				if (result)
				{
					// Grab p2
					if (iVariable_isTypeFloatingPoint(varNum2))
					{
						// p2 is floating point
						lfValue2 = iiVariable_getAs_f64(varNum2, false, &error, &errorNum);
						if (error)
						{
							iError_report_byNumber(errorNum, iVariable_get_relatedComp(varNum2), false);
							return;
						}

						// Store the result
						*(f64*)result->value.data_s8 = (f64)lnValue1 / lfValue2;

					} else  {
						// p2 is not floating point, so we'll get it as an integer
						lnValue2 = iiVariable_getAs_s64(varNum2, false, &error, &errorNum);
						if (error)
						{
							iError_report_byNumber(errorNum, iVariable_get_relatedComp(varNum2), false);
							return;
						}

						// Store the result
						*(f64*)result->value.data_s8 = (f64)lnValue1 / (f64)lnValue2;
					}
				}
			}


		//////////
		// Are we good?
		//////
			if (!result)
				iError_report(cgcInternalError, false);


		//////////
		// Indicate our result
		//////
			rpar->rp[0] = result;

	}




//////////
//
// Command:  CLEAR
// Clears various things.
//
//////
// Version 0.58
// Last update:
//     Mar.15.2015
//////
// Change log:
//     Mar.15.2015
//////
// Parameters:
//		compClear -- The [CLEAR] component
//////
// Returns:
//		Nothing, but whatever it is that's being modified may be open for modifying.
//////
	void command_clear(SComp* compCommand, SReturnsParams* rpar)
	{
		SComp*			compClear = compCommand;
		s32				lnClearLines, lnSaveLines;
		bool			llManufactured;
		SEM_callback	ecb;
		SVariable*		var;
		bool			error;
		u32				errorNum;


// 		SComp*	compAll				= iComps_findNextBy_iCode(compModify, _ICODE_ALL,			NULL);
// 		SComp*	compClass			= iComps_findNextBy_iCode(compModify, _ICODE_CLASS,		NULL);
// 		SComp*	compClassName		= iComps_getNth(compClass, 1);
// 		SComp*	compClassLib		= iComps_findNextBy_iCode(compModify, _ICODE_CLASSLIB,	NULL);
// 		SComp*	compClassLibName	= iComps_getNth(compClassLib, 1);
		SComp*	compKeep			= iComps_findNextBy_iCode(compClear, _ICODE_KEEP,			NULL);
		SComp*	compKeepCount		= iComps_getNth(compKeep, 1);
		SComp*	compLast			= iComps_findNextBy_iCode(compClear, _ICODE_LAST,			NULL);
		SComp*	compLastCount		= iComps_getNth(compLast, 1);
// 		SComp*	compDebug			= iComps_findNextBy_iCode(compModify, _ICODE_DEBUG,		NULL);
// 		SComp*	compDlls			= iComps_findNextBy_iCode(compModify, _ICODE_DLLS,		NULL);
// 		SComp*	compDllAlias		= iComps_getNth(compDlls, 1);
// 		SComp*	compEvents			= iComps_findNextBy_iCode(compModify, _ICODE_EVENTS,		NULL);
// 		SComp*	compError			= iComps_findNextBy_iCode(compModify, _ICODE_ERROR,		NULL);
// 		SComp*	compFields			= iComps_findNextBy_iCode(compModify, _ICODE_FIELDS,		NULL);
// 		SComp*	compGets			= iComps_findNextBy_iCode(compModify, _ICODE_GETS,		NULL);
// 		SComp*	compMacros			= iComps_findNextBy_iCode(compModify, _ICODE_MACROS,		NULL);
// 		SComp*	compMemory			= iComps_findNextBy_iCode(compModify, _ICODE_MEMORY,		NULL);
// 		SComp*	compMenus			= iComps_findNextBy_iCode(compModify, _ICODE_MENUS,		NULL);
// 		SComp*	compPopups			= iComps_findNextBy_iCode(compModify, _ICODE_POPUPS,		NULL);
// 		SComp*	compProgram			= iComps_findNextBy_iCode(compModify, _ICODE_PROGRAM,		NULL);
// 		SComp*	compPrompt			= iComps_findNextBy_iCode(compModify, _ICODE_PROMPT,		NULL);
// 		SComp*	compRead			= iComps_findNextBy_iCode(compModify, _ICODE_READ,		NULL);
// 		SComp*	compResources		= iComps_findNextBy_iCode(compModify, _ICODE_RESOURCES,	NULL);
// 		SComp*	compTypeahead		= iComps_findNextBy_iCode(compModify, _ICODE_TYPEAHEAD,	NULL);
// 		SComp*	compWindows			= iComps_findNextBy_iCode(compModify, _ICODE_WINDOWS,		NULL);
// 		SComp*	compFilename		= iComps_getNth(compWindows, 1);

		if (compLast)
		{
			// CLEAR LAST -- Clears the last few lines at the end of a buffer
			if (compLastCount)
			{
				//////////
				// CLEAR LAST nCount
				//////
					var = iEngine_get_variableName_fromComponent(compLastCount, &llManufactured, false);
					if (!var)
					{
						// Unknown parameter
						iError_report_byNumber(_ERROR_UNRECOGNIZED_PARAMETER, compLastCount, false);
						return;
					}


				//////////
				// Find out how many lines
				//////
					lnClearLines = iiVariable_getAs_s32(var, false, &error, &errorNum);
					if (error)
					{
						iError_report_byNumber(errorNum, compLastCount, false);
						return;
					}


				//////////
				// Clean house
				//////
					if (llManufactured)
						iVariable_delete(var, true);


				//////////
				// Validate the number is in range
				//////
					if (lnClearLines < 0)
					{
						iError_report_byNumber(_ERROR_CANNOT_BE_NEGATIVE, compLastCount, false);
						return;
					}

			} else {
				// Clear them all
				lnClearLines = 0;
			}


			//////////
			// Prepare for the clear
			//////
				memset(&ecb, 0, sizeof(ecb));
				ecb._callback = (uptr)&iiCommand_clear_last_callback;
				ecb.extra1 = (uptr)lnClearLines;
				ecb.extra2 = (uptr)iSEM_renumber(screenData, 1);


			//////////
			// Clear
			//////
				iSEM_deleteChainWithCallback(&screenData, false, &ecb);


			//////////
			// Count what remains, and set _tally
			//////
				iEngine_update_tally(iSEM_renumber(screenData, 1));


			//////////
			// Redraw what remains
			//////
				iSEM_navigateToEndLine(screenData, _screen);
				_screen_editbox->isDirtyRender = true;
				iWindow_render(gWinJDebi, false);

			//////////
			// All done
			//////
				return;


		} else if (compKeep) {
			// CLEAR KEEP -- Keeps a certain number of lines at the end of the buffer, and clears the rest
			if (compKeepCount)
			{
				//////////
				// CLEAR KEEP nCount
				//////
					var = iEngine_get_variableName_fromComponent(compKeepCount, &llManufactured, false);
					if (!var)
					{
						// Unknown parameter
						iError_report_byNumber(_ERROR_UNRECOGNIZED_PARAMETER, compKeepCount, false);
						return;
					}


				//////////
				// Find out how many lines
				//////
					lnSaveLines = iiVariable_getAs_s32(var, false, &error, &errorNum);
					if (error)
					{
						iError_report_byNumber(errorNum, compKeepCount, false);
						return;
					}


				//////////
				// Clean house
				//////
					if (llManufactured)
						iVariable_delete(var, true);


				//////////
				// Validate the number is in range
				//////
					if (lnSaveLines < 0)
					{
						iError_report_byNumber(_ERROR_CANNOT_BE_NEGATIVE, compKeepCount, false);
						return;
					}

			} else {
				// Clear them all
				lnSaveLines = 0;
			}

		} else {
			// Clear them all
			lnSaveLines = 0;
		}


		//////////
		// Prepare for the clear
		//////
			memset(&ecb, 0, sizeof(ecb));
			ecb._callback = (uptr)&iiCommand_clear_keep_callback;
			ecb.extra1 = (uptr)lnSaveLines;
			ecb.extra2 = (uptr)iSEM_renumber(screenData, 1);


		//////////
		// Clear
		//////
			iSEM_deleteChainWithCallback(&screenData, false, &ecb);


		//////////
		// Count what remains, and set _tally
		//////
			iEngine_update_tally(iSEM_renumber(screenData, 1));


		//////////
		// Redraw what remains
		//////
			iSEM_navigateToEndLine(screenData, _screen);
			_screen_editbox->isDirtyRender = true;
			iWindow_render(gWinJDebi, false);
			// All done
	}

	// Tests the line number, only deletes the tail
	bool iiCommand_clear_last_callback(SEM_callback* ecb)
	{
		// If lineNum >= (endNum - clearCount) ... delete it
		return(ecb->line->lineNumber > ecb->sem->lastLine->lineNumber - ecb->extra1);
	}

	// Tests the line number, only saves the tail
	bool iiCommand_clear_keep_callback(SEM_callback* ecb)
	{
		// If (endNum - saveCount) > lineNum ... delete it
		return(ecb->sem->lastLine->lineNumber - ecb->extra1 >= ecb->line->lineNumber);
	}




///////////
//
// Command:  DECLARE
// Declares an array or DLL.
//
//////
// Version 0.58
// Last update:
//     Jul.23.2015
//////
// Change log:
//     Jul.23.2015
//////
// Parameters:
//		compDeclare	-- The [DECLARE] component
//////
// Returns:
//		Nothing. The thing being declared has been declared, or there is an error.
//////
	void command_declare(SComp* compCommand, SReturnsParams* rpar)
	{
		SComp*			compDeclare = compCommand;

		u32				lnI;
		SComp*			compVar;
		SComp*			compLBracket;
		SComp*			compIn;
		SComp*			compAlias;
		SComp*			compWin32Api;
		SComp*			compNext;
		SComp*			compFunctionName;
		SComp*			compDllName;
		SComp*			compAliasName;
		SComp*			compParam;
		SComp*			compNoPrototype;
		SComp*			compVariadic;
		SDllFuncParam	returnParam;
		SDllFuncParam	inputParams[_MAX_DLL_PARAMS];
		char			buffer[16];


		//////////
		// See if we're working with an array definition. The syntax will be: DECLARE laName[quantity] or DECLARE laName(quantity)
		//////
			if ((compVar = iComps_getNth(compDeclare, 1)) && (compLBracket = iComps_getNth(compVar, 1)) && (compLBracket->iCode == _ICODE_BRACKET_LEFT || compLBracket->iCode == _ICODE_PARENTHESIS_LEFT))
			{
				// It is of the array structure
				iError_report_byNumber(_ERROR_FEATURE_NOT_AVAILABLE, compVar, false);
				return;

			}


		//////////
		// It might be a DECLARE DLL form
		//////
			// DECLARE [return_type] functionName IN WIN32API|dllpathname.dll [ALIAS cName] [type [@]name][,type [@]name][,...][,type [@]name]
			compAlias		= iComps_findNextBy_iCode(compDeclare, _ICODE_ALIAS,			NULL);
			compIn			= iComps_findNextBy_iCode(compDeclare, _ICODE_IN,				NULL);
			compWin32Api	= iComps_findNextBy_iCode(compDeclare, _ICODE_WIN32API,		NULL);
			compNoPrototype	= iComps_findNextBy_iCode(compDeclare, _ICODE_NOPROTOTYPE,	NULL);
			compVariadic	= iComps_findNextBy_iCode(compDeclare, _ICODE_VARIADIC,		NULL);
			

		//////////
		// Initialize the parameters
		//////
			memset(&returnParam, 0, sizeof(returnParam));		// Return parameter
			memset(&inputParams, 0, sizeof(inputParams));		// Input parameters

			compFunctionName	= NULL;
			compDllName			= NULL;
			compAliasName		= NULL;


		//////////
		// There should be something after declare
		//////
			if (!(compNext = iComps_getNth(compDeclare, 1)) || !compIn)
			{
				// Syntax error
				iError_report_byNumber(_ERROR_SYNTAX, compDeclare, false);
				return;
			}


		//////////
		// Is it a return type?
		//////
			iDatum_duplicate(&returnParam.name, cgc_ret1, sizeof(cgc_ret1) - 1);
			if (iiComps_validate(compNext, &gsCompList_dllTypes[0], gnCompList_dllTypes_length))
			{
				// It is a valid return type
				compFunctionName = iiCommand_declare_storeParameterType(&returnParam, compNext);

			} else {
				// The function name is next
				returnParam.type = _DLL_TYPE_VOID;
				compFunctionName = compNext;
			}


		//////////
		// Is the name valid?
		//////
			if (!iiComps_isAlphanumeric(compFunctionName))
			{
				// Syntax error
				iError_report_byNumber(_ERROR_SYNTAX, compFunctionName, false);
				return;
			}


		//////////
		// IN win32api | pathname.dll
		//////
			compDllName = iComps_getNth(compIn, 1);
			iComps_combine_adjacent(compDllName, _ICODE_ALPHA, _ICAT_GENERIC, &colorSynHi_operator, gsCompList_filenameTypes, gnCompList_filenameTypes_length);


		//////////
		// ALIAS cName
		//////
			if (compAlias)
			{
				// Get the name after
				if (!(compAliasName = iComps_getNth(compAlias, 1)) || !iiComps_validate(compAliasName, gsCompList_alphanumericTypes, gnCompList_alphanumericTypes_length))
				{
					// Syntax error
					iError_report_byNumber(_ERROR_SYNTAX, compAlias, false);
					return;
				}

				// First parameter begins after compAliasName
				compParam = iComps_getNth(compAliasName, 1);

			} else {
				// First parameter begins after compDllName
				compParam = iComps_getNth(compDllName, 1);
			}


		//////////
		// Skip NOPROTOTYPE and VARIADIC flags
		//////
#if defined(__64_BIT_COMPILER__)
			while (compParam->iCode == _ICODE_NOPROTOTYPE || compParam->iCode == _ICODE_VARIADIC)
				compParam = iComps_getNth(compParam, 1);
#endif


		//////////
		// Parameters
		//////
			if (compParam)
			{
				// Load in the parameters
				for (lnI = 0; compParam && lnI < _MAX_DLL_PARAMS; lnI++)
				{
					// The format for each must be:  type [@] [name] [comma]
					if (iiComps_validate(compParam, gsCompList_dllTypes, gnCompList_dllTypes_length))
					{
						// Grab type
						compParam = iiCommand_declare_storeParameterType(&inputParams[lnI], compParam);
						if (compParam)
						{
							// Is there an at sign?
							if (compParam->iCode == _ICODE_AT_SIGN)
							{
								// by-ref
								inputParams[lnI].udfSetting	= _UDFPARMS_REFERENCE;
								compParam					= iComps_getNth(compParam, 1);

							} else {
								// by-val
								inputParams[lnI].udfSetting	= _UDFPARMS_VALUE;
							}

							// Is there a name?
							if (compParam->iCode != _ICODE_COMMA && iiComps_isAlphanumeric(compParam))
							{
								// Grab the name (for debugging)
								compParam = iiCommand_declare_storeParameterName(&inputParams[lnI], compParam, lnI + 1);

							} else {
								// Use a default name
								sprintf(buffer, "var%d", lnI + 1);
								iDatum_duplicate(&inputParams[lnI].name, buffer, (s32)strlen(buffer));
							}

							// Is there a comma?
							if (compParam)
							{
								if (compParam->iCode == _ICODE_COMMA)
								{
									// We're good, continue on past the comma
									compParam = iComps_getNth(compParam, 1);

								} else {
									// Syntax error
									iError_report_byNumber(_ERROR_SYNTAX, compParam, false);
									return;
								}
							}
						}
						

					} else {
						// Syntax error
						iError_report_byNumber(_ERROR_SYNTAX, compParam, false);
						return;
					}
				}
				// When we get here, all of the parameters have been parsed
				// If there are more waiting, then it's a too many parameters error
				if (compParam)
				{
					// Too many parameters
					iError_report_byNumber(_ERROR_TOO_MANY_PARAMETERS, compParam, false);
					return;
				}

			} else {
				// No parameters
				lnI = 0;
			}


		//////////
		// Create the DLL reference
		//////
#if defined(__64_BIT_COMPILER__)
			// 64-bit, noprototype and variadic are based on components flags
			iDllFunc_add(rpar, &returnParam, inputParams, lnI, compFunctionName, compAliasName, compDllName, NULL, NULL, (compNoPrototype != NULL), (compVariadic != NULL));
#else
			// 32-bit and therefore not noprototype or variadic
			iDllFunc_add(rpar, &returnParam, inputParams, lnI, compFunctionName, compAliasName, compDllName, NULL, NULL, false, false);
#endif

	}

	SComp* iiCommand_declare_storeParameterType(SDllFuncParam* dp, SComp* comp)
	{
		// Based on the type, set the parameter
		switch (comp->iCode)
		{
			case _ICODE_VOID:			// No return type
				dp->type = _DLL_TYPE_VOID;
				break;

			case _ICODE_SHORT:			// 16-bit integer
			case _ICODE_S16:			// 16-bit integer
				dp->type = _DLL_TYPE_S16;
				break;

			case _ICODE_U16:			// 16-bit unsigned integer
				dp->type = _DLL_TYPE_U16;
				break;

			case _ICODE_INTEGER:		// 32-bit integer
			case _ICODE_S32:			// 32-bit integer
			case _ICODE_LONG:			// 32-bit integer
				dp->type = _DLL_TYPE_S32;
				break;

			case _ICODE_U32:			// 32-bit unsigned integer
				dp->type = _DLL_TYPE_U32;
				break;

			case _ICODE_SINGLE:			// 32-bit floating point
			case _ICODE_FLOAT:			// 32-bit floating point
			case _ICODE_F32:			// 32-bit floating point
				dp->type = _DLL_TYPE_F32;
				break;

			case _ICODE_DOUBLE:			// 64-bit floating point
			case _ICODE_F64:			// 64-bit floating point
				dp->type = _DLL_TYPE_F64;
				break;

			case _ICODE_S64:			// 64-bit integer
				dp->type = _DLL_TYPE_S64;
				break;

			case _ICODE_U64:			// 64-bit unsigned integer
				dp->type = _DLL_TYPE_U64;
				break;

			case _ICODE_STRING:			// Character string
				dp->type = _DLL_TYPE_STRING;
				break;

			case _ICODE_OBJECT:			// IDispatch object
				dp->type = _DLL_TYPE_IDISPATCH;
				break;
		}

		// Return the component after this one
		return(iComps_getNth(comp, 1));
	}

	SComp* iiCommand_declare_storeParameterName(SDllFuncParam* dp, SComp* comp/*name or at sign*/, s32 tnParamNum)
	{

		//////////
		// by-ref or by-value?
		//////
			if (comp->iCode == _ICODE_AT_SIGN)
			{
				// By-ref as it is prefixed with an @ sign
				dp->udfSetting		= _UDFPARMS_REFERENCE;
				comp	= iComps_getNth(comp, 1);

			} else {
				// By-value
				dp->udfSetting		= _UDFPARMS_VALUE;
			}


		//////////
		// Copy the name if present (for debugging reference)
		//////
			// Use the name as given
			iDatum_duplicate(&dp->name, comp->line->sourceCode->data_cs8 + comp->start, comp->length);
			comp = iComps_getNth(comp, 1);


		//////////
		// Indicate the next component (which is now the one we're sitting on)
		//////
			return(comp);
	}




//////////
//
// Command: GOTO
// Moves to an explicit recno(), or to top or bottom in a table
//
//////
// Version 0.59   (Determine the current version from the header in vjr.cpp)
// Last update:
//     Aug.20.2016
//////
// Change log:
//     Aug.20.2016 - Initial creation
//////
// Parameters:
//     comp		-- The [GOTO] component
//////
// Returns:
//    Nothing, but the environment may be changed.
//    Can generate an error.
//////
	void command_goto(SComp* compCommand, SReturnsParams* rpar)
	{
		SComp*		compGoto = compCommand;
	}




//////////
//
// Command: LIST
// Lists various items to the indicated outputs
//
//////
// Version 0.59   (Determine the current version from the header in vjr.cpp)
// Last update:
//     Aug.23.2016
//////
// Change log:
//     Aug.23.2016 - Initial creation
//////
// Parameters:
//     comp		-- The [LIST] component
//////
// Returns:
//    Nothing, but the environment may be changed.
//    Can generate an error.
//////
	void command_list(SComp* compCommand, SReturnsParams* rpar)
	{
		SComp*		compList = compCommand;

		u32			lnRecno;
		SDatum*		listRow;
		SWorkArea*	wa;


// TODO:  We have no FOR clause expression parsing here, so only LIST works presently

		//////////
		// See what they're listing
		/////
			if (!compList->ll.nextComp)
			{
				// Just LIST by itself, so list the current table if any
				if ((wa = iDbf_get_workArea_current_wa()))
				{
					// Is a table open?
					if (!wa->isUsed)
						wa = iDialog_openTable();

					// Do we have a file?
					if (wa && wa->isUsed)
					{
						// List contents
						for (lnRecno = 1; lnRecno <= wa->header.records; lnRecno++)
						{
							// Position on this record
							iDbf_gotoRecord(wa, lnRecno);
							if (wa->currentRecord <= wa->header.records)
							{
								// List this entry
								listRow = iDbf_listRecord(wa);
							}
						}

					} else {
						// No table open in current work area
						iError_report_byNumber(_ERROR_NO_TABLE_IN_CURRENT_WORKAREA, compList->ll.nextComp, false);
					}

				} else {
					// Should never happen
					iError_report_byNumber(_DBF_ERROR__INTERNAL_PROGRAMMER, compList->ll.nextComp, false);
				}

			} else {
				// Not yet coded
				iError_report_byNumber(_ERROR_FEATURE_NOT_YET_CODED, compList->ll.nextComp, false);
			}
	}




//////////
//
// Command:  MODIFY
// Modifies various things.
//
//////
// Version 0.58
// Last update:
//     Jan.09.2015
//////
// Change log:
//     Jan.09.2015
//////
// Parameters:
//		compModify	-- The [MODIFY] component
//////
// Returns:
//		Nothing, but whatever it is that's being modified may be open for modifying.
//////
	void command_modify(SComp* compCommand, SReturnsParams* rpar)
	{
		SComp*	compModify = compCommand;
		SComp*	compType;
//		SComp*	compTarget;


		//////////
		// Make sure there's something after the modify command
		//////
			if (!(compType = iComps_getNth(compModify, 1)))
			{
				// There was nothing after, which means syntax error
				iError_report_byNumber(_ERROR_MISSING_PARAMETER, compModify, false);
				return;
			}


		//////////
		// Based on what's after, validate the syntaxes
		//////
// TODO:  Working on here ... the thing after MODIFY should be a fully qualified thing as per the compiler engine
//			compTarget = iComps_getNth(compType, 1);
			switch (compType->iCode)
			{
				case _ICODE_CLASS:
					// MODIFY CLASS
					break;

				case _ICODE_COMMAND:
					// MODIFY COMMAND
					break;

				case _ICODE_CONNECTION:
					// MODIFY CONNECTION
					break;

				case _ICODE_DATABASE:
					// MODIFY DATABASE
					break;

				case _ICODE_FILE:
					// MODIFY FILE
					break;

				case _ICODE_FORM:
					// MODIFY FORM
					break;

				case _ICODE_GENERAL:
					// MODIFY GENERAL
					break;

				case _ICODE_LABEL:
					// MODIFY LABEL
					break;

				case _ICODE_MEMO:
					// MODIFY MEMO
					break;

				case _ICODE_MENU:
					// MODIFY MENU
					break;

				case _ICODE_PROCEDURE:
					// MODIFY PROCEDURE
					break;

				case _ICODE_PROJECT:
					// MODIFY PROJECT
					break;

				case _ICODE_QUERY:
					// MODIFY QUERY
					break;

				case _ICODE_REPORT:
					// MODIFY REPORT
					break;

				case _ICODE_STRUCTURE:
					// MODIFY STRUCTURE
					break;

				case _ICODE_VIEW:
					// MODIFY VIEW
					break;

				case _ICODE_WINDOW:
					// MODIFY WINDOW
					break;
			}


		//////////
		// If we get here, syntax error
		//////
			iError_report_byNumber(_ERROR_SYNTAX, compType, false);
	}




//////////
//
// Command:  OPEN
// Multiple forms.  Opens a database container.
//
//////
// Version 0.58
// Last update:
//     Jan.06.2015
//////
// Change log:
//     Jan.06.2015 - Initial creation
//////
// Parameters:
//		compOpen		-- The [OPEN] component
//////
// Returns:
//		Nothing, but the environment may be changed.
//////
	void command_open(SComp* compCommand, SReturnsParams* rpar)
	{
		SComp*	compOpen = compCommand;
		s32		lnLength;
		sptr	lnDbcArea;
		bool	llIsExclusive, llIsNoUpdate;
		SComp*	compPathname;
		SComp*	compDatabase;
		SComp*	compExclusive;
		SComp*	compShared;
		SComp*	compValidate;
		SComp*	compRecover;
		SComp*	compNoUpdate;
		s8		dbcNameBuffer[_MAX_PATH];


		//////////
		// Access the options which are available for this command
		//////
			compDatabase	= iComps_findNextBy_iCode(compOpen, _ICODE_DATABASE,	NULL);
			compExclusive	= iComps_findNextBy_iCode(compOpen, _ICODE_EXCLUSIVE,	NULL);
			compShared		= iComps_findNextBy_iCode(compOpen, _ICODE_SHARED,	NULL);
			compValidate	= iComps_findNextBy_iCode(compOpen, _ICODE_VALIDATE,	NULL);
			compRecover		= iComps_findNextBy_iCode(compOpen, _ICODE_RECOVER,	NULL);
			compNoUpdate	= iComps_findNextBy_iCode(compOpen, _ICODE_NOUPDATE,	NULL);


		//////////
		// Make sure the syntax was OPEN DATABASE
		//////
			if (!compDatabase)
			{
				// Syntax error
				iError_report_byNumber(_ERROR_SYNTAX, compOpen, false);
				return;
			}
			if (!compDatabase->ll.next)
			{
				// Syntax error
				iError_report_byNumber(_ERROR_SYNTAX, compDatabase, false);
				return;
			}
			// Grab the component after [database]
			compPathname = iComps_getNth(compDatabase, 1);


		//////////
		// Extract the DBC name
		//////
			lnLength = iComps_getContiguousLength(compPathname, NULL, 0, NULL);
			if (lnLength >= (s32)sizeof(dbcNameBuffer))
			{
				// Parameter is too long
				iError_report_byNumber(_ERROR_PARAMETER_TOO_LONG, compPathname, false);
				return;
			}
			memset(dbcNameBuffer, 0, sizeof(dbcNameBuffer));
			memcpy(dbcNameBuffer, compPathname->line->sourceCode->data_s8 + compPathname->start, lnLength);


		//////////
		// Cannot have both SHARED and EXCLUSIVE
		//////
			if (compShared && compExclusive)
			{
				iError_report_byNumber(_ERROR_CONFLICTING_PARAMETERS, ((compShared->ll.uniqueId < compExclusive->ll.uniqueId) ? compExclusive : compShared), false);
				return;
			}

			// Determine shared or exclusive status
			if (compShared)
			{
				// Explicitly shared
				llIsExclusive	= false;

			} else if (compExclusive) {
				// Explicitly exclusive
				llIsExclusive	= true;

			} else {
				// Use the current SET default
				llIsExclusive	= propGet_settings_Exclusive(_settings);
			}


		//////////
		// Read-only?
		//////
			llIsNoUpdate = (compNoUpdate != NULL);


		//////////
		// Try to open it
		//////
			lnDbcArea = iDbf_open((cs8*)dbcNameBuffer, (cs8*)cgcDbcKeyName, llIsExclusive, false, false, false, false, false, llIsNoUpdate);
			if (lnDbcArea < 0)
			{
				// Unable to open
				iError_report_byNumber(_ERROR_UNABLE_TO_OPEN_DBC, compPathname, false);
				return;
			}


		//////////
		// If we need to validate, do so
		//////
			// Pass it our output screen
			if (compValidate)
				iDbc_validate(&gsDbcArea[lnDbcArea], (compRecover != NULL), ((propGet_settings_Talk(_settings)) ? _screen_editbox->p.sem : NULL), gWinJDebi);
	}




//////////
//
// Command: SET
// Sets various components within the current _settings object.
//
//////
// Version 0.58   (Determine the current version from the header in vjr.cpp)
// Last update:
//     Mar.15.2015
//////
// Change log:
//     Mar.15.2015 - Initial creation
//////
// Parameters:
//     comp		-- The [SET] component
//////
// Returns:
//    Nothing, but the environment may be changed.
//////
	void command_set(SComp* compCommand, SReturnsParams* rpar)
	{
		SComp*			compSet = compCommand;
		s32				lnIndex;
		bool			llManufactured;
		SComp*			compSetTarget;
		SComp*			compSetValue;
		SObjPropMap*	objProp;
		SBasePropMap*	baseProp;
		SVariable*		varSet;
		SVariable*		varSetNewValue;

// iError_reportByNumber(_ERROR_FEATURE_NOT_AVAILABLE, compSet, false);
// return;

		//////////
		// Get the next component
		//////
			compSetTarget = iComps_getNth(compSet, 1);
			if (compSetTarget)
			{
				// SET SOMETHING


				//////////
				// The thing after should be the value, or the keyword TO
				//////
					compSetValue = iComps_getNth(compSetTarget, 1);

					// TO is superfluous, so if it exists, skip it
					if (compSetValue && compSetValue->iCode == _ICODE_TO)
						compSetValue = iComps_getNth(compSetValue, 1);


				//////////
				// Is there anything there?
				//////
					if (!compSetValue)
					{
						// Syntax error
						iError_report_byNumber(_ERROR_SYNTAX, compSetTarget, false);
						return;
					}


				//////////
				// Translate the xyz part of the SET xyz TO abcc into the actual _INDEX_SET_* value
				/////
					lnIndex = iObjProp_settingsTranslate(compSetTarget->iCode);
					if (lnIndex <= 0)
					{
						iError_report_byNumber(_ERROR_FEATURE_NOT_AVAILABLE, compSetTarget, false);
						return;
					}


				//////////
				// Find out what the xyz is for SET xyz TO ...
				//////
					varSet = iObjProp_get_var_byIndex(_settings, lnIndex, &baseProp, &objProp);
					if (varSet && objProp && baseProp)
					{
						// We found the setting and the default variable type
						varSetNewValue = iEngine_get_variableName_fromComponent(compSetValue, &llManufactured, false);
//////////
// Note:
//		Settings are handled a little differently compared to other objects.
//		They are only ever referenced as a settings object, so their values are
//		only ever set through the setter settings, which use the setterObject_set()
//		function instead of the standard setterObject() function.
//////////

						// Try to set the value using our special set values
						if (objProp->_setterObject_set)
						{
							// We have our own value, use it
							if (objProp->setterObject_set(varSet, compSetValue, varSetNewValue, llManufactured))
								return;		// If we get here, we're good

							// If we get here, it couldn't be set
							iError_report_byNumber(_ERROR_SYNTAX, compSetValue, false);
							return;
						}

						// If we get here, try the standard method
						if (!iObjProp_set(_settings, compSetTarget->iCode, varSetNewValue))
						{
							iError_report_byNumber(_ERROR_PARAMETER_IS_INCORRECT, compSetTarget, false);
							return;
						}
					}
					// If we get here, invalid setting
					// Fall through
			}


		//////////
		// If we get here, syntax error
		//////
			iError_report_byNumber(_ERROR_SYNTAX, compSet, false);
	}




//////////
//
// Command: SKIP
// Skips forward or backward in a table by index or not
//
//////
// Version 0.59   (Determine the current version from the header in vjr.cpp)
// Last update:
//     Aug.20.2016
//////
// Change log:
//     Aug.20.2016 - Initial creation
//////
// Parameters:
//     comp		-- The [SKIP] component
//////
// Returns:
//    Nothing, but the environment may be changed.
//    Can generate an error.
//////
	void command_skip(SComp* compCommand, SReturnsParams* rpar)
	{
		SComp*		compSkip = compCommand;

		bool		llInCdx, llInDbf;
		s32			lnSkip, lnWorkArea, lnTagIndex, tnErrorNum;
		SComp*		comp;
		SComp*		compNext;
		SComp*		compCdx;
		SWorkArea*	dbf;
		s8			bufferCdx[64];


		//////////
		// Locate the other parameters
		//////
			llInCdx	= false;
			llInDbf	= false;
			if ((comp = compSkip->ll.nextComp))
			{
				// There are parameters
				for ( ; comp; comp = comp->ll.nextComp)
				{
					// Is the component the IN keyword?
					if (comp->iCode == _ICODE_IN)
					{
						// Skipping in something
						if ((compNext = comp->ll.nextComp))
						{
							// What are we skipping in?
							if (compNext->iCode == _ICODE_CDX)
							{
								// IN CDX
								memset(bufferCdx, 0, sizeof(bufferCdx));
								llInCdx = true;
								if ((compCdx = compNext->ll.nextComp))
								{
									// They've specified an explicit tag name
									if (compCdx->iCode == _ICODE_ALPHA || compCdx->iCode == _ICODE_ALPHANUMERIC)
									{
										// Valid tag name
										if (compCdx->length > sizeof(bufferCdx) - 1)
										{
											iError_report_byNumber(_ERROR_INVALID_INDEX_TAG, compCdx, false);
											return;
										}

										// Copy the tag name
										memcpy(bufferCdx, comp->line->sourceCode->data_s8 + comp->start, comp->length);

									} else {
										// Syntax error
										iError_report_byNumber(_ERROR_SYNTAX, compNext, false);
										return;
									}

								} else {
									// Just in CDX
									// Grab the current CDX tag name
									if (!iDbf_get_tagName(iDbf_get_workArea_current_wa(), bufferCdx, &tnErrorNum) || tnErrorNum != 0)
									{
										iError_report_byNumber(_ERROR_NO_ACTIVE_INDEX, compNext, false);
										return;
									}
									// We have the index
								}

							} else if (compNext->iCode == _ICODE_DBF) {
								// IN DBF
								llInDbf = true;

							} else if (compNext->iCode == _ICODE_ALPHA || _ICODE_ALPHANUMERIC) {
								// IN an alias
								lnWorkArea = iDbf_get_workArea_byAlias_byName(&dbf, compNext->line->sourceCode->data_s8 + compNext->start, compNext->length);
								if (lnWorkArea < 0 || !dbf || !dbf->isUsed)
								{
									iError_report_byNumber(_ERROR_INVALID_WORK_AREA, compNext, false);
									return;
								}

							} else if (compNext->iCode == _ICODE_NUMERIC) {
								// IN a work area
								lnWorkArea = iComps_getAs_s32(compNext);
								if (lnWorkArea < 0 || !(dbf = iDbf_get_workArea_current_wa(lnWorkArea)) || !dbf->isUsed)
								{
									iError_report_byNumber(_ERROR_INVALID_WORK_AREA, compNext, false);
									return;
								}

							} else {
								// Syntax error
								iError_report_byNumber(_ERROR_SYNTAX, compNext, false);
								return;
							}
						}
					}
				}

			} else {
				// Skipping forward 1 record in the current area
				lnSkip		= 1;
				lnWorkArea	= iDbf_get_workArea_current();
				dbf			= iDbf_get_workArea_current_wa(lnWorkArea);
				if (!dbf || !dbf->isUsed)
				{
					iError_report_byNumber(_ERROR_INVALID_WORK_AREA, compSkip, false);
					return;
				}
			}


		//////////
		// Are they trying to move in dbf and cdx?
		//////
			if (llInDbf && llInCdx)
			{
				iError_report_byNumber(_ERROR_CONFLICTING_PARAMETERS, compCdx, false);
				return;
			}


		//////////
		// Skip as indicated
		//////
			if (llInCdx)
			{
				// Skipping in a CDX
				if ((lnTagIndex = iCdx_isTagValid_byTagName(dbf, bufferCdx)))
				{
					// Skip forward within the indicated tag
					iCdx_skip(dbf, lnSkip, lnTagIndex);

				} else {
					// Invalid tag name
					iError_report_byNumber(_ERROR_INVALID_INDEX_TAG, compCdx, false);
					return;
				}

			} else if (llInDbf) {
				// Skipping in the DBF
				iDbf_skip(dbf, lnSkip, true);

			} else {
				// Skipping naturally
				iDbf_skip(dbf, lnSkip, false);
			}
	}




//////////
//
// Command: USE
// Multiple forms.  Opens or close a table or view in the current or another area.
//
//////
// Version 0.58   (Determine the current version from the header in vjr.cpp)
// Last update:
//     Nov.02.2014
//////
// Change log:
//     Nov.02.2014 - Initial creation
//////
// Parameters:
//     comp		-- The [USE] component
//////
// Returns:
//    Nothing, but the environment may be changed.
//////
	void command_use(SComp* compCommand, SReturnsParams* rpar)
	{
		SComp*		compUse = compCommand;
		sptr		lnWorkArea, lnWorkAreaAlias;
		bool		llIsInUse, llIsValidWorkArea, llManufacturedTableName, llManufacturedAliasName, llIsExclusive;
		SComp*		comp2;
		SComp*		comp3;
		SComp*		comp4;
		SVariable*	varInWorkArea;
		SVariable*	varTableName;
		SVariable*	varAliasName;
		u32			errorNum;
		bool		error;


		//////////
		// Initialize
		//////
			varInWorkArea					= NULL;
			varTableName				= 0;
			varAliasName				= 0;
			llManufacturedTableName		= false;
			llManufacturedAliasName		= false;
			llIsExclusive				= false;


		//////////
		// Access the options which are available for this command
		//////
			SComp*	compAgain				= iComps_findNextBy_iCode(compUse, _ICODE_AGAIN,				NULL);
//			SComp*	compNoRequery			= iComps_findNextBy_iCode(compUse, _ICODE_NOREQUERY,			NULL);
//			SComp*	compNoData				= iComps_findNextBy_iCode(compUse, _ICODE_NODATA,				NULL);
//			SComp*	compNoUpdate			= iComps_findNextBy_iCode(compUse, _ICODE_NOUPDATE,				NULL);
//			SComp*	compExclamationPoint	= iComps_findNextBy_iCode(compUse, _ICODE_EXCLAMATION_POINT,	NULL);
			SComp*	compIn					= iComps_findNextBy_iCode(compUse, _ICODE_IN,					NULL);
//			SComp*	compIndex				= iComps_findNextBy_iCode(compUse, _ICODE_INDEX,				NULL);
//			SComp*	compOrder				= iComps_findNextBy_iCode(compUse, _ICODE_ORDER,				NULL);
//			SComp*	compTag					= iComps_findNextBy_iCode(compUse, _ICODE_TAG,					NULL);
			SComp*	compAscending			= iComps_findNextBy_iCode(compUse, _ICODE_ASCENDING,			NULL);
			SComp*	compDescending			= iComps_findNextBy_iCode(compUse, _ICODE_DESCENDING,			NULL);
			SComp*	compAlias				= iComps_findNextBy_iCode(compUse, _ICODE_ALIAS,				NULL);
			SComp*	compExclusive			= iComps_findNextBy_iCode(compUse, _ICODE_EXCLUSIVE,			NULL);
			SComp*	compShared				= iComps_findNextBy_iCode(compUse, _ICODE_SHARED,				NULL);
			SComp*	compNoUpdate			= iComps_findNextBy_iCode(compUse, _ICODE_NOUPDATE,				NULL);
//			SComp*	compConnString			= iComps_findNextBy_iCode(compUse, _ICODE_CONNSTRING,			NULL);
			SComp*	compValidate			= iComps_findNextBy_iCode(compUse, _ICODE_VALIDATE,				NULL);
			SComp*	compVisualize			= iComps_findNextBy_iCode(compUse, _ICODE_VISUALIZE,			NULL);		// USE fred.dbf VISUALIZE	&& Creates disk-defrag-like display of table and index
			SComp*	compJournal				= iComps_findNextBy_iCode(compUse, _ICODE_JOURNAL,				NULL);		// USE fred.dbf JOURNAL		&& Creates fred.jrn with every write change made to table or index


		//////////
		// Report any conflicts
		//////
			//////////
			// Cannot have both ASCENDING and DESCENDING
			//////
				if (compAscending && compDescending)
				{
					iError_report_byNumber(_ERROR_CONFLICTING_PARAMETERS, ((compAscending->ll.uniqueId < compDescending->ll.uniqueId) ? compDescending : compAscending), false);
					goto clean_exit;
				}


			//////////
			// Cannot have both SHARED and EXCLUSIVE
			//////
				if (compShared && compExclusive)
				{
					iError_report_byNumber(_ERROR_CONFLICTING_PARAMETERS, ((compShared->ll.uniqueId < compExclusive->ll.uniqueId) ? compExclusive : compShared), false);
					goto clean_exit;
				}

				// Determine shared or exclusive status
				if (compShared)
				{
					// Explicitly shared
					llIsExclusive	= false;

				} else if (compExclusive) {
					// Explicitly exclusive
					llIsExclusive	= true;

				} else {
					// Use the current SET default
					llIsExclusive	= propGet_settings_Exclusive(_settings);
				}


			//////////
			// If they specify IN, they must specify something after it
			//////
// TODO:  Untested function, breakpoint and examine
// debug_break;
				if (compIn && !compIn->ll.next)
				{
					iError_report_byNumber(_ERROR_SYNTAX, compIn, false);
					goto clean_exit;
				}

				// Go ahead and point to what's after it
				if (compIn)
					compIn = compIn->ll.nextComp;


			//////////
			// If they specified an alias, they must specify something after it
			//////
				if (compAlias && !compAlias->ll.next)
				{
					iError_report_byNumber(_ERROR_SYNTAX, compAlias, false);
					goto clean_exit;
				}

				// Go ahead and point to what's after it
				if (compAlias)
					compAlias = compAlias->ll.nextComp;


			//////////
			// What type of USE are we pursuing?
			//////
				if (compUse && !compUse->ll.next)
				{
					// USE ... They have specified USE by itself, closing the current work area
					if ((lnWorkArea = iDbf_get_workArea_current(cgcDbfKeyName)) >= 0)
					{
						// Close it
						iDbf_close(&gsWorkArea[lnWorkArea]);

					} else {
						// The current work area is invalid
						// Hmmm... this shouldn't ever happen. Ever. :-)
						iError_report_byNumber(_ERROR_INTERNAL_ERROR, compUse, false);
					}

					// We're good
					goto clean_exit;
				}

				// Go ahead and point to what's after it
				compUse = compUse->ll.nextComp;


		//////////
		// Find out if they specified a workarea
		//////
			// Note:  Right now, compIn is already pointing to the thing after "IN"
			if (compIn)
			{
				// Get what comes after the IN
				comp3 = NULL;
				comp4 = NULL;
				if ((comp2 = iComps_getNth(compIn, 1)) && (comp3 = iComps_getNth(comp2, 1)) && (comp4 = iComps_getNth(comp3, 1)))
				{
					// Placeholder to allow engagement through the if expression as far as it will go
				}

				// Find out what they're selecting
				if (compIn->iCode == _ICODE_SELECT)
				{
					// They've specified USE IN SELECT something
					// Perform tests on what comes after SELECT()
					if (!comp2) {
						// Syntax error
						iError_report_byNumber(_ERROR_SYNTAX, compIn, false);
						goto clean_exit;

					} else if (comp2->iCode != _ICODE_PARENTHESIS_LEFT) {
						// Syntax error missing parenthesis
						iError_report_byNumber(_ERROR_SYNTAX, comp2, false);
						goto clean_exit;

					} else if (!comp3) {
						// Syntax error missing parameter
						iError_report_byNumber(_ERROR_MISSING_PARAMETER, comp2, false);
						goto clean_exit;

					} else if (!(comp4 = iComps_getNth(comp3, 1))) {
						// Syntax error
						iError_report_byNumber(_ERROR_SYNTAX, comp3, false);
						goto clean_exit;

					} else if (comp4->iCode != _ICODE_PARENTHESIS_RIGHT) {
						// Syntax error parenthesis expected
						iError_report_byNumber(_ERROR_PARENTHESIS_EXPECTED, comp4, false);
						goto clean_exit;
					}
					// Once we get here, we know we have SELECT(...something

					// They've specified USE IN SELECT(something)
					varInWorkArea = iEngine_get_variableName_fromComponent(comp3, &llManufacturedAliasName, false);

				} else {
					// They must've specified a number or alias name
					varInWorkArea = iEngine_get_variableName_fromComponent(compIn, &llManufacturedAliasName, false);
				}
			}


		//////////
		// See if they specified an integer or character for the SELECT()
		//////
			if (varInWorkArea)
			{
				//////////
				// See what they specified
				//////
					if (iVariable_isTypeNumeric(varInWorkArea))
					{
						// They're are specifying a number
						lnWorkArea = iiVariable_getAs_s32(varInWorkArea, false, &error, &errorNum);
						if (error)	{ iError_report_byNumber(errorNum, compIn, false); return; }

					} else if (iVariable_isTypeCharacter(varInWorkArea)) {
						// They specified something character (could be a work area letter, or alias)
						if (iDbf_isWorkAreaLetter(varInWorkArea))
						{
							// Work area letter
							lnWorkArea = iUpperCase(varInWorkArea->value.data_s8[0]) - (s32)'A' + 1;

						} else {
							// Alias name
							lnWorkArea = iDbf_get_workArea_byAlias_byVar(varInWorkArea, NULL, NULL);
						}

						// Did we get a valid work area?
						if (lnWorkArea < 0)
						{
							iError_report_byNumber(_ERROR_ALIAS_NOT_FOUND, iVariable_get_relatedComp(varInWorkArea), false);
							goto clean_exit;
						}
						// If we get here, we have our work area number

					} else {
						// Unrecognized syntax
						iError_report_byNumber(_ERROR_SYNTAX, compIn->ll.nextComp, false);
						goto clean_exit;
					}

			} else {
				// Just grab the current work area
				lnWorkArea = (s32)iDbf_get_workArea_current(cgcDbfKeyName);
			}


		//////////
		// Was "USE IN..." specified?
		//////
			// Note:  Right now, compUse is already pointing to the thing after "USE"
			if (compUse->iCode == _ICODE_IN)
			{
				// Yes, close that work area and we're done
				iDbf_close(&gsWorkArea[lnWorkArea]);
				goto clean_exit;
			}


		//////////
		// Get the table name
		//////
			// Note:  compUse is actually pointing to whatever was after USE by this point
			if ((varTableName = iEngine_get_variableName_fromComponent(compUse, &llManufacturedTableName, false))) {
				// Placeholder, we were able to obtain a variable name
				// Note:  The variable is checked for sanity below

			} else if ((varTableName = iEngine_get_contiguousComponents(compUse, &llManufacturedTableName, NULL, 0))) {
					// Placeholder, we were able to obtain a contiguous stream of characters
//////////
// TODO:	Enhancement consideration.  May not ever be needed.
//
//			For the contiguous components grab, it may be desirable to pass an array through to obtain only
//			those components that are known to be part of a valid pathname for the target OS.  This could
//			also be setup to be specified by a SET VALID_PATHNAME_CHARS TO cString to allow that string to
//			be parsed out and the components derived obtained therein.  Such a creature would generally look
//			like this:
//
// 				#define _VALID_PATHNAME_ICODE_ARRAY_COUNT 7
// 				s32 gnValidPathname_iCodeArray[_VALID_PATHNAME_ICODE_ARRAY_COUNT];
//
// 				gnValidPathname_iCodeArray[0] = _ICODE_ALPHA;
// 				gnValidPathname_iCodeArray[1] = _ICODE_NUMERIC;
// 				gnValidPathname_iCodeArray[2] = _ICODE_ALPHANUMERIC;
// 				gnValidPathname_iCodeArray[3] = _ICODE_COLON;
// 				gnValidPathname_iCodeArray[4] = _ICODE_BACKSLASH;
// 				gnValidPathname_iCodeArray[5] = _ICODE_DOT;
// 				gnValidPathname_iCodeArray[6] = _ICODE_UNDERSCORE;
// 				// Plus any other characters to add
//
//			And in use:
//				iEngine_get_contiguousComponents(compUse, &llManufacturedTableName, &gnValidPathname_iCodeArray[0], _VALID_PATHNAME_ICODE_ARRAY_COUNT)
//////
			}

			// Is it valid?
			if (!varTableName || !iVariable_isTypeCharacter(varTableName))
			{
				// We didn't get what we needed
				iError_report_byNumber(_ERROR_UNRECOGNIZED_PARAMETER, compUse, false);
				goto clean_exit;
			}
			// Note:	The parameter, while character, may still be incorrect.
			//			It may be an invalid filename.  That will be sorted out on the open.


		//////////
		// If they didn't specify AGAIN, make sure it's not already open
		//////
			if (!compAgain)
			{
				// No AGAIN clause was specified, so make sure it isn't already found as being in use
// TODO:  Need FULLPATH() here
				if (iDbf_get_workArea_byTablePathname(varTableName, null) >= 0)
				{
					// It was found, which means it's already in use
					iError_report_byNumber(_ERROR_TABLE_ALREADY_IN_USE, compUse, false);
					goto clean_exit;
				}
			}


		//////////
		// Get the alias name, making sure it's unique amongst the other alias name
		//////
			if (compAlias)
			{
				// They've specified an alias
				varAliasName	= iEngine_get_variableName_fromComponent(compAlias->ll.nextComp, &llManufacturedTableName, false);
				lnWorkAreaAlias	= iDbf_get_workArea_byAlias_byVar(varAliasName, NULL, NULL);
				if (lnWorkAreaAlias > 0)
				{
					// They've specified an alias name
					// If it's the current work area, or the one they specified with the "IN xyz" clause, then we're okay
					if (lnWorkArea != lnWorkAreaAlias)
					{
						// Nope, they're trying to re-use an alias already in use
						iError_report_byNumber(_ERROR_ALIAS_ALREADY_IN_USE, compAlias, false);
						goto clean_exit;
					}
					// If we get here, the work area is okay

				} else {
					// Unknown alias
					iError_report_byNumber(_ERROR_ALIAS_NOT_FOUND, compAlias, false);
					goto clean_exit;
				}

			} else {
				// We need to construct the alias from the table name
				varAliasName = iDbf_get_alias_fromPathname(varTableName, null);
			}
			if (!varAliasName)
			{
				iError_report_byNumber(_ERROR_INTERNAL_ERROR, compUse, false);
				goto clean_exit;
			}


		//////////
		// See if the current work area already has a table open
		//////
			llIsInUse = iDbf_isWorkAreaUsed(&gsWorkArea[lnWorkArea], &llIsValidWorkArea);
			if (!llIsValidWorkArea)
			{
				// They specified an invalid work area number
				iError_report_byNumber(_ERROR_INVALID_WORK_AREA, compIn, false);
				goto clean_exit;

			} else if (llIsInUse) {
				// If it's already open, close it
				iDbf_close(&gsWorkArea[lnWorkArea]);
			}


		//////////
		// Get the alias
		//////
			iDbf_set_workArea_current((u32)lnWorkArea, null);
			lnWorkArea = iDbf_open(varTableName, varAliasName, llIsExclusive, (compAgain != NULL), (compValidate != NULL), (compDescending != NULL), (compVisualize != NULL), (compJournal != NULL), (compNoUpdate != NULL));
			if (lnWorkArea < 0)
			{
				// The negative work area number indicates the error
				iError_signal(iDbf_translateError((s32)lnWorkArea), compUse, false, NULL, false);

			} else {
				// Set any meta data about the table
//				SComp*	compAgain				= iComps_findNextBy_iCode(compUse, _ICODE_AGAIN,				NULL);
//				SComp*	compNoRequery			= iComps_findNextBy_iCode(compUse, _ICODE_NOREQUERY,			NULL);
//				SComp*	compNoData				= iComps_findNextBy_iCode(compUse, _ICODE_NODATA,				NULL);
//				SComp*	compNoUpdate			= iComps_findNextBy_iCode(compUse, _ICODE_NOUPDATE,				NULL);
//				SComp*	compExclamationPoint	= iComps_findNextBy_iCode(compUse, _ICODE_EXCLAMATION_POINT,	NULL);
//				SComp*	compIn					= iComps_findNextBy_iCode(compUse, _ICODE_IN,					NULL);
//				SComp*	compIndex				= iComps_findNextBy_iCode(compUse, _ICODE_INDEX,				NULL);
//				SComp*	compOrder				= iComps_findNextBy_iCode(compUse, _ICODE_ORDER,				NULL);
//				SComp*	compTag					= iComps_findNextBy_iCode(compUse, _ICODE_TAG,					NULL);
//				SComp*	compAscending			= iComps_findNextBy_iCode(compUse, _ICODE_ASCENDING,			NULL);
//				SComp*	compDescending			= iComps_findNextBy_iCode(compUse, _ICODE_DESCENDING,			NULL);
//				SComp*	compAlias				= iComps_findNextBy_iCode(compUse, _ICODE_ALIAS,				NULL);
//				SComp*	compExclusive			= iComps_findNextBy_iCode(compUse, _ICODE_EXCLUSIVE,			NULL);
//				SComp*	compShared				= iComps_findNextBy_iCode(compUse, _ICODE_SHARED,				NULL);
//				SComp*	compConnString			= iComps_findNextBy_iCode(compUse, _ICODE_CONNSTRING,			NULL);
			}

clean_exit:
			// Release variables
			if (varInWorkArea)		iVariable_delete(varInWorkArea,	true);
			if (varTableName)		iVariable_delete(varTableName,	true);
			if (varAliasName)		iVariable_delete(varAliasName,	true);
	}
