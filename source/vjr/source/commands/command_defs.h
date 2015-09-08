//////////
//
// /libsf/source/vjr/commands/command_defs.h
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
// Steps to add a new function:
//		(1a) STEP1A:  Add the function definition to the "Functions" section below (search for "STEP1A:").
//		(1b) STEP1B:  Add the command definition to the "Commands" section below (search for "STEP1B:").
//		(2)  STEP2:  Add the function information to the "Translation" gsKnownFunctions data by inserting it where it should go (search for "STEP2:").
//		(3)  STEP3:  Add the function to commands.cpp (search for "STEP3").
//		(4)  Code, debug, and test the function thoroughly.
//		(5)  Email your changes to Rick C. Hodgin at the address on the www.visual-freepro.org/vjr/indexmain.html web page.
//		(6)  Happy coding!
//
//




struct SVariable;
struct SThisCode;
struct SFunctionParams;

#define get_s64(a)		(*a->value.data_s64)
#define get_u64(a)		(*a->value.data_u64)
#define get_s32(a)		(*a->value.data_s32)
#define get_u32(a)		(*a->value.data_u32)
#define get_s16(a)		(*a->value.data_s16)
#define get_u16(a)		(*a->value.data_u16)
#define get_s8(a)		(*a->value.data_s8)
#define get_u8(a)		(*a->value.data_u8)
#define get_f32(a)		(*a->value.data_f32)
#define get_f64(a)		(*a->value.data_f64)
#define get_bool(a)		(*a->value.data_u8 != _LOGICAL_FALSE)
#define get_bgra(a)		(*a->value.data_bgra)
#define get_bgr(a)		(*a->value.data_bgr)




//////////
// commands.cpp
// Note:  This source file contains both commands and functions.  Each will be
//        given by its name, such as "function_chr()" being a function.
//////
	// Temporary error reporting until the proper engine is constructed.
	void				iError_signal								(SThisCode* thisCode, u32 tnErrorNum, SComp* comp, bool tlInvasive, s8* tcExtraInfo, bool tlFatal);
	void				iError_report								(SThisCode* thisCode, cu8* constantErrorText, bool tlInvasive);
	void				iError_report								(SThisCode* thisCode, u8* errorText, bool tlInvasive);
	void				iError_reportByNumber						(SThisCode* thisCode, u32 tnErrorNum, SComp* comp, bool tlInvasive);
	void				iError_track								(void);

	// Called to check if potential errors exist
	f32					iErrorCandidate_signalOutOfRange_f32		(SThisCode* thisCode, SErrorInfo* ei, f32 value, s32 tnVarType, SComp* compRelated, bool tlInvasive, s8* tcExtraInfo);
	f64					iErrorCandidate_signalOutOfRange_f64		(SThisCode* thisCode, SErrorInfo* ei, f64 value, s32 tnVarType, SComp* compRelated, bool tlInvasive, s8* tcExtraInfo);
	u8					iErrorCandidate_signalOutOfRange_u8			(SThisCode* thisCode, SErrorInfo* ei, u8  value, s32 tnVarType, SComp* compRelated, bool tlInvasive, s8* tcExtraInfo);
	s16					iErrorCandidate_signalOutOfRange_s16		(SThisCode* thisCode, SErrorInfo* ei, s16 value, s32 tnVarType, SComp* compRelated, bool tlInvasive, s8* tcExtraInfo);
	u16					iErrorCandidate_signalOutOfRange_u16		(SThisCode* thisCode, SErrorInfo* ei, u16 value, s32 tnVarType, SComp* compRelated, bool tlInvasive, s8* tcExtraInfo);
	s32					iErrorCandidate_signalOutOfRange_s32		(SThisCode* thisCode, SErrorInfo* ei, s32 value, s32 tnVarType, SComp* compRelated, bool tlInvasive, s8* tcExtraInfo);
	u32					iErrorCandidate_signalOutOfRange_u32		(SThisCode* thisCode, SErrorInfo* ei, u32 value, s32 tnVarType, SComp* compRelated, bool tlInvasive, s8* tcExtraInfo);
	s64					iErrorCandidate_signalOutOfRange_s64		(SThisCode* thisCode, SErrorInfo* ei, s64 value, s32 tnVarType, SComp* compRelated, bool tlInvasive, s8* tcExtraInfo);
	u64					iErrorCandidate_signalOutOfRange_u64		(SThisCode* thisCode, SErrorInfo* ei, u64 value, s32 tnVarType, SComp* compRelated, bool tlInvasive, s8* tcExtraInfo);
	f64					iErrorCandidate_signalOutOfRange_numeric	(SThisCode* thisCode, SErrorInfo* ei, SDatum* value, s32 tnVarType, SComp* compRelated, bool tlInvasive, s8* tcExtraInfo);




//////////
//
// SourceLight
//
//////
	struct SSourceLightData
	{
		u32			key;									// Refer to _SOURCELIGHT_* constants

		// Data, varies based on _SOURCELIGHT_* constants
		uptr		data1;
		uptr		data2;
		uptr		data3;
		uptr		data4;
		uptr		data5;
	};

	#include "command_sourcelight.h"




//////////
//
// Functions
// STEP1A: Define your function
//
//////
	void				function_abs		/* Stefano D'Amico */	(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_acos		/* Stefano D'Amico */	(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_addbs								(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_alltrim							(SThisCode* thisCode, SFunctionParams* rpar);
	void				ifunction_trim_common						(SThisCode* thisCode, SFunctionParams* rpar, SVariable* varString, SVariable* varCaseInsensitive, SVariable* varTrimChars1, SVariable* varTrimChars2, bool trimStart, bool trimEnd);
	void				function_alp								(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_asc								(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_asin		/* Stefano D'Amico */	(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_at									(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_atan		/* Stefano D'Amico */	(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_atc								(SThisCode* thisCode, SFunctionParams* rpar);
	void				ifunction_at_occurs_common					(SThisCode* thisCode, SFunctionParams* rpar, SVariable* varNeedle, SVariable* varHaystack, SVariable* varOccurrence, bool tlCaseSensitive, bool tlScanBackward, u32* tnFoundCount);
	void				function_atn2								(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_between	/* Stefano D'Amico */	(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_bfp								(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_bi									(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_bits								(SThisCode* thisCode, SFunctionParams* rpar);
	void				ifunction_bits_common						(SThisCode* thisCode, SFunctionParams* rpar, SVariable* varBits, SVariable* varBitWidth);
	void				function_bits8								(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_bits16								(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_bits32								(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_bits64								(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_bitslice							(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_bitstr								(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_blu								(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_bgr								(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_bgra								(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_cdow		/* Stefano D'Amico */	(SThisCode* thisCode, SFunctionParams* rpar);
	u32					ifunction_dow_common						(SThisCode* thisCode, SFunctionParams* rpar, u32 tnYear, u32 tnMonth, u32 tnDay);
	void				function_ceiling	/* Stefano D'Amico */	(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_chr								(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_chrtran							(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_chrtranc							(SThisCode* thisCode, SFunctionParams* rpar);
	void				ifunction_chrtran_common					(SThisCode* thisCode, SFunctionParams* rpar, SVariable* varString, SVariable* varSearch, SVariable* varReplace, bool tlCaseSensitive);
	void				function_cmonth		/* Stefano D'Amico */	(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_colorize							(SThisCode* thisCode, SFunctionParams* rpar);
	void				ifunction_colorize_common					(SThisCode* thisCode, SFunctionParams* rpar, SVariable* varColor, SVariable* varColorTarget, SVariable* varPercentage, bool tlApplyColorTarget);
	void				function_cos		/* Stefano D'Amico */	(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_createobject						(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_ctod								(SThisCode* thisCode, SFunctionParams* rpar);
	void				ifunction_ctox_common						(SThisCode* thisCode, SFunctionParams* rpar, SVariable* varString, bool tlIncludeTime);
	void				function_ctot								(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_curdir								(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_date		/* Stefano D'Amico */	(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_datetime							(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_datetimex							(SThisCode* thisCode, SFunctionParams* rpar);
	void				ifunction_datetimex_common					(SThisCode* thisCode, SFunctionParams* rpar, bool tlIsDatetimeX);
	void				function_day		/* Stefano D'Amico */	(SThisCode* thisCode, SFunctionParams* rpar);
	void				ifunction_day_month_year_common				(SThisCode* thisCode, SFunctionParams* rpar, SVariable* varParam, u32 tnFunctionType);
	void				function_dmy		/* Stefano D'Amico */	(SThisCode* thisCode, SFunctionParams* rpar);
	void				ifunction_dtoc_common						(SThisCode* thisCode, SFunctionParams* rpar, SVariable* varParam, u32 tnFunctionType);
	void				function_dow		/* Hernan Cano */		(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_dtoc		/* Stefano D'Amico */	(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_dtor		/* Stefano D'Amico */	(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_dtos		/* Stefano D'Amico */	(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_dtot		/* Stefano D'Amico */	(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_dtox								(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_dtransform	/* Stefano D'Amico */	(SThisCode* thisCode, SFunctionParams* rpar);
	s32					iifunction_append_text						(s8* tcDst, s8* tcSrc, s32 tnLength);
	u32					ifunction_dtransform_textmerge_common		(SThisCode* thisCode, SFunctionParams* rpar, s8** tcResult, cs8* tcFormatStr, s32 tnFormatStrLength, SDatum* leftTextmergeDelim, SDatum* rightTextmergeDelim, SVariable* varDatesOrDatetimes[9], bool tlDateCodes, bool tlTextMerge);
	void				function_empty		/* Stefano D'Amico */	(SThisCode* thisCode, SFunctionParams* rpar);
	bool				function_isempty_common						(SThisCode* thisCode, SFunctionParams* rpar, SVariable* varExpr);
	void				function_endswith							(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_endswithc							(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_evl		/* Stefano D'Amico */	(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_exp		/* Stefano D'Amico */	(SThisCode* thisCode, SFunctionParams* rpar);
	void				ifunction_numbers_common					(SThisCode* thisCode, SFunctionParams* rpar, SVariable* varNumber1, SVariable* varNumber2, SVariable* varNumber3, u32 tnFunctionType, const u32 tnResultType, bool tlSameInputType, bool tlNoEmptyParam);
	void				function_floor		/* Stefano D'Amico */	(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_forceext	/* Stefano D'Amico */	(SThisCode* thisCode, SFunctionParams* rpar);
	bool				ifunction_pathname_common					(SThisCode* thisCode, SFunctionParams* rpar, SVariable* varPathname, s32* tnFNamePos, s32* tnExtPos);
	void				function_forcefname	/* Stefano D'Amico */	(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_forcepath	/* Stefano D'Amico */	(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_forcestem	/* Stefano D'Amico */	(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_fv			/* Stefano D'Amico */	(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_gomonth	/* Stefano D'Amico */	(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_grayscale							(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_grn								(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_hour		/* Stefano D'Amico */	(SThisCode* thisCode, SFunctionParams* rpar);
	void				ifunction_hhmmss_common						(SThisCode* thisCode, SFunctionParams* rpar, SVariable* varParam, u32 tnFunctionType);
	void				function_iif								(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_inlist								(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_int								(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_isnull		/* Hernan Cano */		(SThisCode* thisCode, SFunctionParams* rpar);
	bool				ifunction_isnull_common						(SThisCode* thisCode, SFunctionParams* rpar, SVariable* varExpr);
	void				function_justdrive							(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_justext							(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_justfname							(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_justpath							(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_juststem							(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_left								(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_len								(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_log		/* Stefano D'Amico */	(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_log10		/* Stefano D'Amico */	(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_lower								(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_ltrim								(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_malp								(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_max								(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_mdy		/* Stefano D'Amico */	(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_microsecond						(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_min								(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_minute		/* Stefano D'Amico */	(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_mod		/* Stefano D'Amico */	(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_month		/* Stefano D'Amico */	(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_nanosecond							(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_ncset								(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_nvl		/* Hernan Cano */		(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_occurs								(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_occursc							(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_outside	/* Stefano D'Amico */	(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_padc								(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_padl								(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_padr								(SThisCode* thisCode, SFunctionParams* rpar);
	void				ifunction_pad_common						(SThisCode* thisCode, SFunctionParams* rpar, SVariable* varExpr, SVariable* varResultSize, SVariable* varPadCharacter, bool tlPadLeft, bool tlPadRight);
	void				function_payment	/* Stefano D'Amico */	(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_pi			/* Stefano D'Amico */	(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_pow		/* Stefano D'Amico */	(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_proper								(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_pv			/* Stefano D'Amico */	(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_quarter	/* Stefano D'Amico */	(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_ranger		/* Stefano D'Amico */	(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_ranger2							(SThisCode* thisCode, SFunctionParams* rpar);
	void				ifunction_ranger_common						(SThisCode* thisCode, SFunctionParams* rpar, SVariable* varExpr, SVariable* varMin, SVariable* varMax, bool* tlRanged);
	void				function_rat								(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_ratc								(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_replicate							(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_rgb								(SThisCode* thisCode, SFunctionParams* rpar);
	void				ifunction_rgba_common						(SThisCode* thisCode, SFunctionParams* rpar, SVariable* varRed, SVariable* varGrn, SVariable* varBlu, SVariable* varAlp);
	void				function_rgba								(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_red								(SThisCode* thisCode, SFunctionParams* rpar);
	void				ifunction_color_common						(SThisCode* thisCode, SFunctionParams* rpar, SVariable* varColor, u32 tnMask, u32 tnShift);
	void				function_right								(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_round		/* Stefano D'Amico */	(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_rtod		/* Stefano D'Amico */	(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_rtrim								(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_sec		/* Stefano D'Amico */	(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_seconds	/* Stefano D'Amico */	(SThisCode* thisCode, SFunctionParams* rpar);
	void				ifunction_xseconds_common					(SThisCode* thisCode, SFunctionParams* rpar, s32 tnFunction);
	void				function_secondstotime						(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_secondstotimex						(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_secondstot							(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_secondstox							(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_secondsx							(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_secondsxtotime						(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_secondsxtotimex					(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_secondsxtot						(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_secondsxtox						(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_set								(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_sign		/* Stefano D'Amico */	(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_sign2								(SThisCode* thisCode, SFunctionParams* rpar);
	void				ifunction_sign_common						(SThisCode* thisCode, SFunctionParams* rpar, SVariable* varNumber, bool tlIncrementZero);
	void				function_sin		/* Stefano D'Amico */	(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_slice								(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_space								(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_sqrt		/* Stefano D'Amico */	(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_startswith							(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_startswithc						(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_strtran							(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_strtranc							(SThisCode* thisCode, SFunctionParams* rpar);
	void				ifunction_strtran_common					(SThisCode* thisCode, SFunctionParams* rpar, SVariable* varString, SVariable* varSearch, SVariable* varReplace, SVariable* varRecursiveCount, bool tlCaseSensitive);
	void				function_stuff								(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_sys								(SThisCode* thisCode, SFunctionParams* rpar);
	SVariable*			iFunction_sys2015							(SThisCode* thisCode, u32 tnPrefixWidth, u32 tnPostfixWidth, SFunctionParams* rpar);
	void				function_sysmetric							(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_tan		/* Stefano D'Amico */	(SThisCode* thisCode, SFunctionParams* rpar);
	void				function__test								(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_textmerge							(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_time		/* Hernan Cano */		(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_timetoseconds						(SThisCode* thisCode, SFunctionParams* rpar);
	void				ifunction_timesAndDatesConversion_common	(SThisCode* thisCode, SFunctionParams* rpar, s32 tnIn, s32 tnOut);
	void				function_timetosecondsx						(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_timetot							(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_timetox							(SThisCode* thisCode, SFunctionParams* rpar);
	void				ifunction_timex_common						(SThisCode* thisCode, SFunctionParams* rpar, bool tlIsTimeX);
	void				function_timex								(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_timextoseconds						(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_timextosecondsx					(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_timextot							(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_timextox							(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_transform							(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_ttoc		/* Stefano D'Amico */	(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_ttod		/* Stefano D'Amico */	(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_ttoseconds							(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_ttosecondsx						(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_ttotime							(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_ttotimex							(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_ttox								(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_type								(SThisCode* thisCode, SFunctionParams* rpar);
	void				ifunction_type_common						(SThisCode* thisCode, SFunctionParams* rpar, SVariable* var, bool tlExtraInfo, bool tlIsVartype, bool tlNullIsType);
	void				function_typedetail							(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_upper								(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_val		/* Stefano D'Amico */	(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_vartype							(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_vec								(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_veccount							(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_vecel								(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_vecslice							(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_vecstr								(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_vecstuff							(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_vecsymbol							(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_version							(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_week		/* Stefano D'Amico */	(SThisCode* thisCode, SFunctionParams* rpar);
	s32					ifunction_week_common						(SThisCode* thisCode, SFunctionParams* rpar, u32 tnYear, u32 tnMonth, u32 tnDay, s32 tnMinDaysInWeek, s32 tnFirstDayOfWeek);
	void				function_xtod								(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_xtoseconds							(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_xtosecondsx						(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_xtot								(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_xtotime							(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_xtotimex							(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_year		/* Stefano D'Amico */	(SThisCode* thisCode, SFunctionParams* rpar);


	// Apr.25.2015 -- Functions Rick is currently working on, see rick_in_progress.cpp
	void				function_cxlatd								(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_cxlatt								(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_cxlatx								(SThisCode* thisCode, SFunctionParams* rpar);

	void				function_dbundle							(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_dunbundle							(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_tbundle							(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_tunbundle							(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_xbundle							(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_xunbundle							(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_timebundle							(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_timeunbundle						(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_timexbundle						(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_timexunbundle						(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_secondsbundle						(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_secondsunbundle					(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_secondsxbundle						(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_secondsxunbundle					(SThisCode* thisCode, SFunctionParams* rpar);

	// May.17.2015 -- Functions Rick is currently working on, see rick_in_progress.cpp
	void				function_pdjobstart							(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_pdaddpage							(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_pdaddpanel							(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_pdtext								(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_pdtexteval							(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_pdimage							(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_pdpanel							(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_pdhline							(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_pdvline							(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_pdrect								(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_pdpagedelete						(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_pdpagereorder						(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_pdwidth							(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_pdheight							(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_pdpmetrics							(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_pdtextmetrics						(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_pdjobdelete						(SThisCode* thisCode, SFunctionParams* rpar);



// Added temporarily until the processing engine is coded
	void				function_concatenate						(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_add								(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_sub								(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_mul								(SThisCode* thisCode, SFunctionParams* rpar);
	void				function_div								(SThisCode* thisCode, SFunctionParams* rpar);
	// transform (partial support, only converts to character, does not do any formatting ... yet)
//////
// STEP3: Copy the code above near one of the other functions in commands.cpp.
//        You may be able to right-click on one of the functions and choose "go to definition".
//////////




//////////
//
// Commands
// STEP1B: Define your command
//
//////
	void				command_clear								(SThisCode* thisCode, SComp* compCommand, SFunctionParams* rpar);
	bool				iiCommand_clear_last_callback				(SEM_callback* ecb);
	bool				iiCommand_clear_keep_callback				(SEM_callback* ecb);
	void				command_declare								(SThisCode* thisCode, SComp* compCommand, SFunctionParams* rpar);
	SComp*				iiCommand_declare_storeParameterType		(SThisCode* thisCode, SDllFuncParam* dp, SComp* comp);
	SComp*				iiCommand_declare_storeParameterName		(SThisCode* thisCode, SDllFuncParam* dp, SComp* comp, s32 tnParamNum);
	void				command_modify								(SThisCode* thisCode, SComp* compCommand, SFunctionParams* rpar);
	void				command_open								(SThisCode* thisCode, SComp* compCommand, SFunctionParams* rpar);
	void				command_set									(SThisCode* thisCode, SComp* compCommand, SFunctionParams* rpar);
	void				command_use									(SThisCode* thisCode, SComp* compCommand, SFunctionParams* rpar);

	// May.17.2015 -- Functions Rick is currently working on, see rick_in_progress.cpp
	void				command_report								(SThisCode* thisCode, SComp* compCommand, SFunctionParams* rpar);




//////////
// Translation between iCodes and function definitions.
//////
	struct SFunctionData
	{
		//////////
		// iCode relates to the keyword identified in source code, tranlated to a usable number.
		// See cgcKeywordsVxb in vxb_globals.h.
		// There are also other areas, so a generic "cgcKeywords" search might yield additional locations.
		//////
			s32		iCode;


		//////////
		// Number of return variables this function generates
		//////
			s32		req_rcount;			// How many return values are required
			s32		max_rcount;			// How many return values are there maximum?
			bool	lExplicitEqual;		// Is an explicit equal required to assume (a) return variable(s)?


		//////////
		// Function to call to conduct the work
		//////
			union {
				uptr		_func;
				void		(*func)		(SThisCode* thisCode, SFunctionParams* rpar);
			};


		//////////
		// Input parameters the function handles
		//////
			s32		req_pcount;			// How many parameters are required
			s32		max_pcount;			// How many parameters are there maximum?
			s8*		map_byValOrByRef;	// Pointer to structure indicating the indirect map
					// byVal='0'		// Refer to the _UDFPARMS_VALUE constant
					// byRef='1'		// Refer to the _UDFPARMS_REFERENCE constant


		//////////
		// SourceLight information for syntax highlighting during input
		//////
			SSourceLightData*	data;
	};

// TODO:  Need to add a compile-time test to verify that the maximum parameter count is representative of the function definition's actual parameters because the function is referenced through the union struct above in SFunctionData
	SFunctionData gsKnownFunctions[] = {
		//							Return		Return			Explicit									Parameters		Parameter		byRef(1)
		//	iCode					Required	Maximum Count	Equal?		Function Algorithm				Required		Maximum Count	byVal(0) Map	SourceLight data
		//  ------------------		--------	-------------	--------	--------------------------		----------		-------------	------------	----------------------------------
		{	_ICODE_ABS,				1,			1,				false,		(uptr)&function_abs,			1,				1,				NULL,			&gsSourceLight_abs[0]			},	// ABS() by Stefano D'Amico, VJr 0.56, Mar.18.2015
		{	_ICODE_ACOS,			1,			1,				false,		(uptr)&function_acos,			1,				1,				NULL,			&gsSourceLight_acos[0]			},	// ACOS() by Stefano D'Amico, VJr 0.56, Mar.18.2015
		{	_ICODE_ADDBS,			1,			1,				false,		(uptr)&function_addbs,			1,				4,				NULL,			&gsSourceLight_addbs[0]			},
		{	_ICODE_ALLTRIM,			1,			1,				false,		(uptr)&function_alltrim,		1,				4,				NULL,			&gsSourceLight_alltrim[0]		},
		{	_ICODE_ALP,				1,			1,				false,		(uptr)&function_alp,			1,				1,				NULL,			&gsSourceLight_alp[0]			},
		{	_ICODE_ASC,				1,			1,				false,		(uptr)&function_asc,			1,				1,				NULL,			&gsSourceLight_asc[0]			},
		{	_ICODE_ASIN,			1,			1,				false,		(uptr)&function_asin,			1,				1,				NULL,			&gsSourceLight_asin[0]			},	// ASIN() by Stefano D'Amico, VJr 0.56, Mar.18.2015
		{	_ICODE_AT,				1,			1,				false,		(uptr)&function_at,				2,				3,				NULL,			&gsSourceLight_at[0]			},
		{	_ICODE_ATAN,			1,			1,				false,		(uptr)&function_atan,			1,				1,				NULL,			&gsSourceLight_atan[0]			},	// ATAN() by Stefano D'Amico, VJr 0.56, Mar.18.2015
		{	_ICODE_ATC,				1,			1,				false,		(uptr)&function_atc,			2,				3,				NULL,			&gsSourceLight_atc[0]			},
		{	_ICODE_ATN2,			1,			1,				false,		(uptr)&function_atn2,			2,				2,				NULL,			&gsSourceLight_atn2[0]			},
		{	_ICODE_BETWEEN,			1,			1,				false,		(uptr)&function_between,		3,				3,				NULL,			&gsSourceLight_between[0]		},	// BETWEEN() by Stefano D'Amico, VJr 0.57, Mar.23.2015
		{	_ICODE_BFP,				1,			1,				false,		(uptr)&function_bfp,			0,				2,				NULL,			&gsSourceLight_bfp[0]			},
		{	_ICODE_BI,				1,			1,				false,		(uptr)&function_bi,				0,				2,				NULL,			&gsSourceLight_bi[0]			},
		{	_ICODE_BITS,			1,			1,				false,		(uptr)&function_bits,			1,				2,				NULL,			&gsSourceLight_bits[0]			},
		{	_ICODE_BITS8,			1,			1,				false,		(uptr)&function_bits8,			1,				1,				NULL,			&gsSourceLight_bits8[0]			},
		{	_ICODE_BITS16,			1,			1,				false,		(uptr)&function_bits16,			1,				1,				NULL,			&gsSourceLight_bits16[0]		},
		{	_ICODE_BITS32,			1,			1,				false,		(uptr)&function_bits32,			1,				1,				NULL,			&gsSourceLight_bits32[0]		},
		{	_ICODE_BITS64,			1,			1,				false,		(uptr)&function_bits64,			1,				1,				NULL,			&gsSourceLight_bits64[0]		},
		{	_ICODE_BITSLICE,		1,			1,				false,		(uptr)&function_bitslice,		2,				3,				NULL,			&gsSourceLight_bitslice[0]		},
		{	_ICODE_BITSTR,			1,			1,				false,		(uptr)&function_bitstr,			1,				2,				NULL,			&gsSourceLight_bitstr[0]		},
		{	_ICODE_BGR,				1,			1,				false,		(uptr)&function_bgr,			3,				3,				NULL,			&gsSourceLight_bgr[0]			},
		{	_ICODE_BGRA,			1,			1,				false,		(uptr)&function_bgra,			4,				4,				NULL,			&gsSourceLight_bgra[0]			},
		{	_ICODE_BLU,				1,			1,				false,		(uptr)&function_blu,			1,				1,				NULL,			&gsSourceLight_blu[0]			},
		{	_ICODE_CDOW,			1,			1,				false,		(uptr)&function_cdow,			0,				1,				NULL,			&gsSourceLight_cdow[0]			},	// CDOW() by Stefano D'Amico, VJr 0.57, Apr.04.2015
		{	_ICODE_CEILING,			1,			1,				false,		(uptr)&function_ceiling,		1,				1,				NULL,			&gsSourceLight_ceiling[0]		},	// CEILING() by Stefano D'Amico, VJr 0.56, Mar.15.2015
		{	_ICODE_CHR,				1,			1,				false,		(uptr)&function_chr,			1,				1,				NULL,			&gsSourceLight_chr[0]			},
		{	_ICODE_CHRTRAN,			1,			1,				false,		(uptr)&function_chrtran,		2,				3,				NULL,			&gsSourceLight_chrtran[0]		},
		{	_ICODE_CHRTRANC,		1,			1,				false,		(uptr)&function_chrtranc,		2,				3,				NULL,			&gsSourceLight_chrtranc[0]		},
		{	_ICODE_CMONTH,			1,			1,				false,		(uptr)&function_cmonth,			0,				1,				NULL,			&gsSourceLight_cmonth[0]		},	// CMONTH() by Stefano D'Amico, VJr 0.57, Apr.05.2015
		{	_ICODE_COLORIZE,		1,			1,				false,		(uptr)&function_colorize,		2,				3,				NULL,			&gsSourceLight_colorize[0]		},
		{	_ICODE_COS,				1,			1,				false,		(uptr)&function_cos,			1,				1,				NULL,			&gsSourceLight_cos[0]			},	// COS() by Stefano D'Amico, VJr 0.56, Mar.17.2015
		{	_ICODE_CREATEOBJECT,	1,			1,				false,		(uptr)&function_createobject,	1,				1,				NULL,			&gsSourceLight_createobject[0]	},
		{	_ICODE_CTOD,			1,			1,				false,		(uptr)&function_ctod,			1,				1,				NULL,			&gsSourceLight_ctod[0]			},	// CTOD() by Stefano D'Amico, VJr 0.57, Apr.11.2015
		{	_ICODE_CTOT,			1,			1,				false,		(uptr)&function_ctot,			1,				1,				NULL,			&gsSourceLight_ctot[0]			},	// CTOT() by Stefano D'Amico, VJr 0.57, Apr.11.2015
		{	_ICODE_CURDIR,			1,			1,				false,		(uptr)&function_curdir,			0,				0,				NULL,			&gsSourceLight_curdir[0]		},
		{	_ICODE_DATE,			1,			1,				false,		(uptr)&function_date,			0,				3,				NULL,			&gsSourceLight_date[0]			},	// DATE() by Stefano D'Amico, VJr 0.57, Apr.04.2015
		{	_ICODE_DATETIME,		1,			1,				false,		(uptr)&function_datetime,		0,				7,				NULL,			&gsSourceLight_datetime[0]		},
		{	_ICODE_DATETIMEX,		1,			1,				false,		(uptr)&function_datetimex,		0,				8,				NULL,			&gsSourceLight_datetimex[0]		},
		{	_ICODE_DAY,				1,			1,				false,		(uptr)&function_day,			0,				1,				NULL,			&gsSourceLight_day[0]			},	// DAY() by Stefano D'Amico, VJr 0.57, Apr.04.2015
		{	_ICODE_DBUNDLE,			0,			1,				false,		(uptr)&function_dbundle,		1,				4,				(char*)"1000",	&gsSourceLight_dbundle[0]		},
		{	_ICODE_DMY,				1,			1,				false,		(uptr)&function_dmy,			0,				1,				NULL,			&gsSourceLight_dmy[0]			},	// DMY() by Stefano D'Amico, VJr 0.57, Apr.07.2015
		{	_ICODE_DOW,				1,			1,				false,		(uptr)&function_dow,			0,				2,				NULL,			&gsSourceLight_dow[0]			},	// DOW() by Hernan Cano, VJr 0.75, Apr.20.2015
		{	_ICODE_DTOC,			1,			1,				false,		(uptr)&function_dtoc,			0,				2,				NULL,			&gsSourceLight_dtoc[0]			},	// DTOC() by Stefano D'Amico, VJr 0.57, Apr.07.2015
		{	_ICODE_DTOR,			1,			1,				false,		(uptr)&function_dtor,			1,				1,				NULL,			&gsSourceLight_dtor[0]			},	// DTOR() by Stefano D'Amico, VJr 0.56, Mar.16.2015
		{	_ICODE_DTOS,			1,			1,				false,		(uptr)&function_dtos,			0,				1,				NULL,			&gsSourceLight_dtos[0]			},	// DTOS() by Stefano D'Amico, VJr 0.57, Apr.07.2015
		{	_ICODE_DTOT,			1,			1,				false,		(uptr)&function_dtot,			1,				2,				NULL,			&gsSourceLight_dtot[0]			},	// DTOT() by Stefano D'Amico, VJr 0.57, Apr.07.2015
		{	_ICODE_DTOX,			1,			1,				false,		(uptr)&function_dtox,			1,				2,				NULL,			&gsSourceLight_dtox[0]			},
		{	_ICODE_DTRANSFORM,		1,			1,				false,		(uptr)&function_dtransform,		1,				10,				NULL,			&gsSourceLight_dtransform[0]	},	// DTRANSFORM() by Stefano D'Amico, VJr 0.57, Apr.16.2015
		{	_ICODE_DUNBUNDLE,		0,			3,				false,		(uptr)&function_dunbundle,		1,				4,				(char*)"0111",	&gsSourceLight_dunbundle[0]		},
		{	_ICODE_EMPTY,			1,			1,				false,		(uptr)&function_empty,			1,				1,				NULL,			&gsSourceLight_empty[0]			},	// EMPTY() by Stefano D'Amico, VJr 0.56, Mar.19.2015
		{	_ICODE_ENDSWITH,		1,			1,				false,		(uptr)&function_endswith,		2,				4,				NULL,			&gsSourceLight_endswith[0]		},
		{	_ICODE_ENDSWITHC,		1,			1,				false,		(uptr)&function_endswith,		2,				4,				NULL,			&gsSourceLight_endswithc[0]		},
		{	_ICODE_EVL,				1,			1,				false,		(uptr)&function_evl,			2,				2,				NULL,			&gsSourceLight_evl[0]			},	// EVL() by Stefano D'Amico, VJr 0.56, Mar.20.2015
		{	_ICODE_EXP,				1,			1,				false,		(uptr)&function_exp,			1,				1,				NULL,			&gsSourceLight_exp[0]			},	// EXP() by Stefano D'Amico, VJr 0.56, Mar.15.2015
		{	_ICODE_FLOOR,			1,			1,				false,		(uptr)&function_floor,			1,				1,				NULL,			&gsSourceLight_floor[0]			},	// FLOOR() by Stefano D'Amico, VJr 0.56, Mar.15.2015
		{	_ICODE_FORCEEXT,		1,			1,				false,		(uptr)&function_forceext,		2,				2,				NULL,			&gsSourceLight_forceext[0]		},
		{	_ICODE_FORCEFNAME,		1,			1,				false,		(uptr)&function_forcefname,		2,				2,				NULL,			&gsSourceLight_forcefname[0]	},
		{	_ICODE_FORCEPATH,		1,			1,				false,		(uptr)&function_forcepath,		2,				2,				NULL,			&gsSourceLight_forcepath[0]		},
		{	_ICODE_FORCESTEM,		1,			1,				false,		(uptr)&function_forcestem,		2,				2,				NULL,			&gsSourceLight_forcestem[0]		},
		{	_ICODE_FV,				1,			1,				false,		(uptr)&function_fv,				3,				3,				NULL,			&gsSourceLight_fv[0]			},	// FV() by Stefano D'Amico, VJr 0.56, Mar.18.2015
		{	_ICODE_GOMONTH,			1,			1,				false,		(uptr)&function_gomonth,		2,				2,				NULL,			&gsSourceLight_gomonth[0]		},	// GOMONTH() by Stefano D'Amico, VJr 0.57, Apr.06.2015
		{	_ICODE_GRAYSCALE,		1,			1,				false,		(uptr)&function_grayscale,		1,				2,				NULL,			&gsSourceLight_grayscale[0]		},
		{	_ICODE_GRN,				1,			1,				false,		(uptr)&function_grn,			1,				1,				NULL,			&gsSourceLight_grn[0]			},
		{	_ICODE_HOUR,			1,			1,				false,		(uptr)&function_hour,			0,				1,				NULL,			&gsSourceLight_hour[0]			},	// HOUR() by Stefano D'Amico, VJr 0.57, Apr.07.2015
		{	_ICODE_IIF,				1,			1,				false,		(uptr)&function_iif,			2,				3,				NULL,			&gsSourceLight_iif[0]			},
		{	_ICODE_INLIST,			1,			1,				false,		(uptr)&function_inlist,			2,				26,				NULL,			&gsSourceLight_inlist[0]		},
		{	_ICODE_INT,				1,			1,				false,		(uptr)&function_int,			1,				1,				NULL,			&gsSourceLight_int[0]			},
		{	_ICODE_ISNULL,			1,			1,				false,		(uptr)&function_isnull,			1,				1,				NULL,			&gsSourceLight_isnull[0]		},	// ISNULL() by Hernan Cano, VJr 0.57, Apr.22.2015
		{	_ICODE_JUSTDRIVE,		1,			1,				false,		(uptr)&function_justdrive,		1,				1,				NULL,			&gsSourceLight_justdrive[0]		},
		{	_ICODE_JUSTEXT,			1,			1,				false,		(uptr)&function_justext,		1,				1,				NULL,			&gsSourceLight_justext[0]		},
		{	_ICODE_JUSTFNAME,		1,			1,				false,		(uptr)&function_justfname,		1,				1,				NULL,			&gsSourceLight_justfname[0]		},
		{	_ICODE_JUSTPATH,		1,			1,				false,		(uptr)&function_justpath,		1,				1,				NULL,			&gsSourceLight_justpath[0]		},
		{	_ICODE_JUSTSTEM,		1,			1,				false,		(uptr)&function_juststem,		1,				2,				NULL,			&gsSourceLight_juststem[0]		},
		{	_ICODE_LEFT,			1,			1,				false,		(uptr)&function_left,			2,				2,				NULL,			&gsSourceLight_left[0]			},
		{	_ICODE_LEN,				1,			1,				false,		(uptr)&function_len,			1,				1,				NULL,			&gsSourceLight_len[0]			},
		{	_ICODE_LOG,				1,			1,				false,		(uptr)&function_log,			1,				1,				NULL,			&gsSourceLight_log[0]			},	// LOG() by Stefano D'Amico, VJr 0.56, Mar.15.2015
		{	_ICODE_LOG10,			1,			1,				false,		(uptr)&function_log10,			1,				1,				NULL,			&gsSourceLight_log10[0]			},	// LOG10() by Stefano D'Amico, VJr 0.56, Mar.15.2015
		{	_ICODE_LOWER,			1,			1,				false,		(uptr)&function_lower,			1,				1,				NULL,			&gsSourceLight_lower[0]			},
		{	_ICODE_LTRIM,			1,			1,				false,		(uptr)&function_ltrim,			1,				1,				NULL,			&gsSourceLight_ltrim[0]			},
		{	_ICODE_MALP,			1,			1,				false,		(uptr)&function_malp,			1,				2,				NULL,			&gsSourceLight_malp[0]			},
		{	_ICODE_MAX,				1,			1,				false,		(uptr)&function_max,			2,				2,				NULL,			&gsSourceLight_max[0]			},
		{	_ICODE_MDY,				1,			1,				false,		(uptr)&function_mdy,			0,				1,				NULL,			&gsSourceLight_mdy[0]			},	// MDY() by Stefano D'Amico, VJr 0.57, Apr.07.2015
		{	_ICODE_MICROSECOND,		1,			1,				false,		(uptr)&function_microsecond,	0,				0,				NULL,			&gsSourceLight_microsecond[0]	},
		{	_ICODE_MIN,				1,			1,				false,		(uptr)&function_min,			2,				2,				NULL,			&gsSourceLight_min[0]			},
		{	_ICODE_MINUTE,			1,			1,				false,		(uptr)&function_minute,			0,				1,				NULL,			&gsSourceLight_minute[0]		},	// MINUTE() by Stefano D'Amico, VJr 0.57, Apr.07.2015
		{	_ICODE_MOD,				1,			1,				false,		(uptr)&function_mod,			2,				2,				NULL,			&gsSourceLight_mod[0]			},	// MOD() by Stefano D'Amico, VJr 0.56, Mar.08.2015
		{	_ICODE_MONTH,			1,			1,				false,		(uptr)&function_month,			0,				1,				NULL,			&gsSourceLight_month[0]			},	// MONTH() by Stefano D'Amico, VJr 0.57, Apr.04.2015
		{	_ICODE_NANOSECOND,		1,			1,				false,		(uptr)&function_nanosecond,		0,				0,				NULL,			&gsSourceLight_nanosecond[0]	},
		{	_ICODE_NCSET,			1,			1,				false,		(uptr)&function_ncset,			1,				7,				NULL,			&gsSourceLight_ncset[0]			},
		{	_ICODE_NVL,				1,			1,				false,		(uptr)&function_nvl,			1,				2,				NULL,			&gsSourceLight_nvl[0]			},	// NVL() by Hernan Can, VJr 0.57, Apr.22.2015
		{	_ICODE_OCCURS,			1,			1,				false,		(uptr)&function_occurs,			2,				2,				NULL,			&gsSourceLight_occurs[0]		},
		{	_ICODE_OCCURSC,			1,			1,				false,		(uptr)&function_occursc,		2,				2,				NULL,			&gsSourceLight_occursc[0]		},
		{	_ICODE_OUTSIDE,			1,			1,				false,		(uptr)&function_outside,		3,				3,				NULL,			&gsSourceLight_outside[0]		},	// OUTSIDE() by Stefano D'Amico, VJr 0.57, Mar.23.2015
		{	_ICODE_PADC,			1,			1,				false,		(uptr)&function_padc,			2,				3,				NULL,			&gsSourceLight_padc[0]			},
		{	_ICODE_PADL,			1,			1,				false,		(uptr)&function_padl,			2,				3,				NULL,			&gsSourceLight_padl[0]			},
		{	_ICODE_PADR,			1,			1,				false,		(uptr)&function_padr,			2,				3,				NULL,			&gsSourceLight_padr[0]			},
		{	_ICODE_PAYMENT,			1,			1,				false,		(uptr)&function_payment,		3,				3,				NULL,			&gsSourceLight_payment[0]		},	// PAYMENT() by Stefano D'Amico, VJr 0.56, Mar.19.2015
		{	_ICODE_PI,				1,			1,				false,		(uptr)&function_pi,				0,				0,				NULL,			&gsSourceLight_pi[0]			},	// PI() by Stefano D'Amico, VJr 0.56, Mar.15.2015
		{	_ICODE_POW,				1,			1,				false,		(uptr)&function_pow,			2,				3,				NULL,			&gsSourceLight_pow[0]			},	// POW() by Stefano D'Amico, VJr 0.57, Apr.26.2015
		{	_ICODE_PROPER,			1,			1,				false,		(uptr)&function_proper,			1,				1,				NULL,			&gsSourceLight_proper[0]		},
		{	_ICODE_PV,				1,			1,				false,		(uptr)&function_pv,				3,				3,				NULL,			&gsSourceLight_pv[0]			},	// PV() by Stefano D'Amico, VJr 0.56, Mar.18.2015
		{	_ICODE_QUARTER,			1,			1,				false,		(uptr)&function_quarter,		0,				2,				NULL,			&gsSourceLight_quarter[0]		},	// QUARTER() by Stefano D'Amico, VJr 0.57, Apr.05.2015
		{	_ICODE_RANGER,			1,			1,				false,		(uptr)&function_ranger,			3,				3,				NULL,			&gsSourceLight_ranger[0]		},	// RANGER() by Stefano D'Amico, VJr 0.56, Mar.14.2015
		{	_ICODE_RANGER2,			1,			1,				false,		(uptr)&function_ranger2,		3,				3,				NULL,			&gsSourceLight_ranger2[0]		},
		{	_ICODE_RAT,				1,			1,				false,		(uptr)&function_rat,			2,				3,				NULL,			&gsSourceLight_rat[0]			},
		{	_ICODE_RATC,			1,			1,				false,		(uptr)&function_ratc,			2,				3,				NULL,			&gsSourceLight_ratc[0]			},
		{	_ICODE_RED,				1,			1,				false,		(uptr)&function_red,			1,				1,				NULL,			&gsSourceLight_red[0]			},
		{	_ICODE_REPLICATE,		1,			1,				false,		(uptr)&function_replicate,		2,				2,				NULL,			&gsSourceLight_replicate[0]		},
		{	_ICODE_RGB,				1,			1,				false,		(uptr)&function_rgb,			3,				3,				NULL,			&gsSourceLight_rgb[0]			},
		{	_ICODE_RGBA,			1,			1,				false,		(uptr)&function_rgba,			4,				4,				NULL,			&gsSourceLight_rgba[0]			},
		{	_ICODE_RIGHT,			1,			1,				false,		(uptr)&function_right,			2,				2,				NULL,			&gsSourceLight_right[0]			},
		{	_ICODE_ROUND,			1,			1,				false,		(uptr)&function_round,			2,				2,				NULL,			&gsSourceLight_round[0]			},	// ROUND() by Stefano D'Amico, VJr 0.56, Mar.16.2015
		{	_ICODE_RTOD,			1,			1,				false,		(uptr)&function_rtod,			1,				1,				NULL,			&gsSourceLight_rtod[0]			},	// RTOD() by Stefano D'Amico, VJr 0.56, Mar.16.2015
		{	_ICODE_RTRIM,			1,			1,				false,		(uptr)&function_rtrim,			1,				4,				NULL,			&gsSourceLight_rtrim[0]			},
		{	_ICODE_TRIM,			1,			1,				false,		(uptr)&function_rtrim,			1,				4,				NULL,			&gsSourceLight_rtrim[0]			},
		{	_ICODE_SEC,				1,			1,				false,		(uptr)&function_sec,			0,				1,				NULL,			&gsSourceLight_sec[0]			},	// SEC() by Stefano D'Amico, VJr 0.57, Apr.07.2015
		{	_ICODE_SECONDS,			1,			1,				false,		(uptr)&function_seconds,		0,				0,				NULL,			&gsSourceLight_seconds[0]		},	// SECONDS() by Stefano D'Amico, VJr 0.57, Apr.07.2015
		{	_ICODE_SECONDSTOTIME,	1,			1,				false,		(uptr)&function_secondstotime,	1,				1,				NULL,			&gsSourceLight_secondstotime[0]	},
		{	_ICODE_SECONDSTOTIMEX,	1,			1,				false,		(uptr)&function_secondstotimex,	1,				1,				NULL,			&gsSourceLight_secondstotimex[0] },
		{	_ICODE_SECONDSX,		1,			1,				false,		(uptr)&function_secondsx,		0,				0,				NULL,			&gsSourceLight_secondsx[0]		},	// SECONDS() by Stefano D'Amico, VJr 0.57, Apr.07.2015
		{	_ICODE_SECONDSXTOTIME,	1,			1,				false,		(uptr)&function_secondsxtotime, 1,				1,				NULL,			&gsSourceLight_secondsxtotime[0] },
		{	_ICODE_SECONDSXTOTIMEX,	1,			1,				false,		(uptr)&function_secondsxtotimex, 1,				1,				NULL,			&gsSourceLight_secondsxtotimex[0] },
		{	_ICODE_SECONDSTOT,		1,			1,				false,		(uptr)&function_secondstot,		1,				2,				NULL,			&gsSourceLight_secondstot[0]	},
		{	_ICODE_SECONDSTOX,		1,			1,				false,		(uptr)&function_secondstox,		1,				2,				NULL,			&gsSourceLight_secondstox[0]	},
		{	_ICODE_SECONDSXTOT,		1,			1,				false,		(uptr)&function_secondsxtot,	1,				2,				NULL,			&gsSourceLight_secondsxtot[0]	},
		{	_ICODE_SECONDSXTOX,		1,			1,				false,		(uptr)&function_secondsxtox,	1,				2,				NULL,			&gsSourceLight_secondsxtox[0]	},
		{	_ICODE_SET,				1,			1,				false,		(uptr)&function_set,			1,				2,				NULL,			&gsSourceLight_set[0]			},
		{	_ICODE_SIGN,			1,			1,				false,		(uptr)&function_sign,			1,				1,				NULL,			&gsSourceLight_sign[0]			},	// SIGN() by Stefano D'Amico, VJr 0.56, Mar.14.2015
		{	_ICODE_SIN,				1,			1,				false,		(uptr)&function_sin,			1,				1,				NULL,			&gsSourceLight_sin[0]			},	// SIN() by Stefano D'Amico, VJr 0.56, Mar.17.2015
		{	_ICODE_SLICE,			1,			1,				false,		(uptr)&function_slice,			2,				3,				NULL,			&gsSourceLight_slice[0]			},
		{	_ICODE_SPACE,			1,			1,				false,		(uptr)&function_space,			1,				1,				NULL,			&gsSourceLight_space[0]			},
		{	_ICODE_SQRT,			1,			1,				false,		(uptr)&function_sqrt,			1,				1,				NULL,			&gsSourceLight_sqrt[0]			},	// SQRT() by Stefano D'Amico, VJr 0.56, Mar.15.2015
		{	_ICODE_STARTSWITH,		1,			1,				false,		(uptr)&function_startswith,		2,				4,				NULL,			&gsSourceLight_startswith[0]	},
		{	_ICODE_STARTSWITHC,		1,			1,				false,		(uptr)&function_startswithc,	2,				4,				NULL,			&gsSourceLight_startswithc[0]	},
		{	_ICODE_STRTRAN,			1,			1,				false,		(uptr)&function_strtran,		2,				4,				NULL,			&gsSourceLight_strtran[0]		},
		{	_ICODE_STRTRANC,		1,			1,				false,		(uptr)&function_strtranc,		2,				4,				NULL,			&gsSourceLight_strtranc[0]		},
		{	_ICODE_STUFF,			1,			1,				false,		(uptr)&function_stuff,			3,				4,				NULL,			&gsSourceLight_stuff[0]			},
		{	_ICODE_SYS,				1,			1,				false,		(uptr)&function_sys,			1,				7,				NULL,			&gsSourceLight_sys[0]			},
		{	_ICODE_SYSMETRIC,		1,			1,				false,		(uptr)&function_sysmetric,		1,				1,				NULL,			&gsSourceLight_sysmetric[0]		},
		{	_ICODE_TAN,				1,			1,				false,		(uptr)&function_tan,			1,				1,				NULL,			&gsSourceLight_tan[0]			},	// TAN() by Stefano D'Amico, VJr 0.56, Mar.19.2015
		{	_ICODE__TEST,			1,			1,				false,		(uptr)&function__test,			1,				1,				NULL,			NULL							},
		{	_ICODE_TEXTMERGE,		1,			1,				false,		(uptr)&function_textmerge,		1,				4,				NULL,			&gsSourceLight_textmerge[0]		},
		{	_ICODE_TIME,			1,			1,				false,		(uptr)&function_time,			0,				2,				NULL,			&gsSourceLight_time[0]			},	// TIME() by Hernan Cano, VJr 0.57, Apr.20.2015
		{	_ICODE_TIMETOSECONDS,	1,			1,				false,		(uptr)&function_timetoseconds,	1,				1,				NULL,			&gsSourceLight_timetoseconds[0] },
		{	_ICODE_TIMETOSECONDSX,	1,			1,				false,		(uptr)&function_timetosecondsx,	1,				1,				NULL,			&gsSourceLight_timetosecondsx[0] },
		{	_ICODE_TIMETOT,			1,			1,				false,		(uptr)&function_timetot,		1,				2,				NULL,			&gsSourceLight_timetot[0]		},
		{	_ICODE_TIMETOX,			1,			1,				false,		(uptr)&function_timetox,		1,				2,				NULL,			&gsSourceLight_timetox[0]		},
		{	_ICODE_TIMEX,			1,			1,				false,		(uptr)&function_timex,			0,				2,				NULL,			&gsSourceLight_timex[0]			},	// TIME() by Hernan Cano, VJr 0.57, Apr.20.2015
		{	_ICODE_TIMEXTOSECONDS,	1,			1,				false,		(uptr)&function_timextoseconds,	1,				1,				NULL,			&gsSourceLight_timextoseconds[0] },
		{	_ICODE_TIMEXTOSECONDSX,	1,			1,				false,		(uptr)&function_timextosecondsx, 1,				1,				NULL,			&gsSourceLight_timextosecondsx[0] },
		{	_ICODE_TIMEXTOT,		1,			1,				false,		(uptr)&function_timextot,		1,				2,				NULL,			&gsSourceLight_timextot[0]		},
		{	_ICODE_TIMEXTOX,		1,			1,				false,		(uptr)&function_timextox,		1,				2,				NULL,			&gsSourceLight_timextox[0]		},
		{	_ICODE_TRANSFORM,		1,			1,				false,		(uptr)&function_transform,		1,				2,				NULL,			&gsSourceLight_transform[0]		},
		{	_ICODE_TTOC,			1,			1,				false,		(uptr)&function_ttoc,			1,				2,				NULL,			&gsSourceLight_ttoc[0]			},	// TTOC() by Stefano D'Amico, VJr 0.57, Apr.07.2015
		{	_ICODE_TTOD,			1,			1,				false,		(uptr)&function_ttod,			1,				1,				NULL,			&gsSourceLight_ttod[0]			},	// TTOD() by Stefano D'Amico, VJr 0.57, Apr.07.2015
		{	_ICODE_TTOSECONDS,		1,			1,				false,		(uptr)&function_ttoseconds,		1,				1,				NULL,			&gsSourceLight_ttoseconds[0]	},
		{	_ICODE_TTOSECONDSX,		1,			1,				false,		(uptr)&function_ttosecondsx,	1,				1,				NULL,			&gsSourceLight_ttosecondsx[0]	},
		{	_ICODE_TTOTIME,			1,			1,				false,		(uptr)&function_ttotime,		1,				1,				NULL,			&gsSourceLight_ttotime[0]		},
		{	_ICODE_TTOTIMEX,		1,			1,				false,		(uptr)&function_ttotimex,		1,				1,				NULL,			&gsSourceLight_ttotimex[0]		},
		{	_ICODE_TTOX,			1,			1,				false,		(uptr)&function_ttox,			1,				2,				NULL,			&gsSourceLight_ttod[0]			},
		{	_ICODE_TYPE,			1,			1,				false,		(uptr)&function_type,			1,				2,				NULL,			&gsSourceLight_type[0]	},
		{	_ICODE_TYPEDETAIL,		1,			1,				false,		(uptr)&function_typedetail,		1,				1,				NULL,			&gsSourceLight_typedetail[0]	},
		{	_ICODE_UPPER,			1,			1,				false,		(uptr)&function_upper,			1,				1,				NULL,			&gsSourceLight_upper[0]			},
		{	_ICODE_VAL,				1,			1,				false,		(uptr)&function_val,			1,				2,				NULL,			&gsSourceLight_val[0]			}, 	// VAL() by Stefano D'Amico, VJr 0.56, Mar.22.2015
		{	_ICODE_VARTYPE,			1,			1,				false,		(uptr)&function_vartype,		1,				2,				NULL,			&gsSourceLight_vartype[0]		},
		{	_ICODE_VEC,				1,			1,				false,		(uptr)&function_vec,			1,				10,				NULL,			&gsSourceLight_vec[0]			},
		{	_ICODE_VECCOUNT,		1,			1,				false,		(uptr)&function_veccount,		1,				1,				NULL,			&gsSourceLight_veccount[0]		},
		{	_ICODE_VECEL,			1,			1,				false,		(uptr)&function_vecel,			1,				3,				NULL,			&gsSourceLight_vecel[0]			},
		{	_ICODE_VECSLICE,		1,			1,				false,		(uptr)&function_vecslice,		2,				3,				NULL,			&gsSourceLight_vecslice[0]		},
		{	_ICODE_VECSTR,			1,			1,				false,		(uptr)&function_vecstr,			1,				2,				NULL,			&gsSourceLight_vecstr[0]		},
		{	_ICODE_VECSTUFF,		1,			1,				false,		(uptr)&function_vecstuff,		3,				4,				NULL,			&gsSourceLight_vecstuff[0]		},
		{	_ICODE_VECSYMBOL,		1,			1,				false,		(uptr)&function_vecsymbol,		1,				3,				NULL,			&gsSourceLight_vecsymbol[0]		},
		{	_ICODE_VERSION,			1,			1,				false,		(uptr)&function_version,		0,				1,				NULL,			&gsSourceLight_version[0]		},
		{	_ICODE_WEEK,			1,			1,				false,		(uptr)&function_week,			0,				3,				NULL,			&gsSourceLight_week[0]			},	// WEEK() by Stefano D'Amico, VJr 0.57, May.01.2015
		{	_ICODE_XTOD,			1,			1,				false,		(uptr)&function_xtod,			1,				1,				NULL,			&gsSourceLight_xtod[0]			},
		{	_ICODE_XTOSECONDS,		1,			1,				false,		(uptr)&function_xtoseconds,		1,				1,				NULL,			&gsSourceLight_xtoseconds[0]	},
		{	_ICODE_XTOSECONDSX,		1,			1,				false,		(uptr)&function_xtosecondsx,	1,				1,				NULL,			&gsSourceLight_xtosecondsx[0]	},
		{	_ICODE_XTOT,			1,			1,				false,		(uptr)&function_xtot,			1,				1,				NULL,			&gsSourceLight_xtot[0]			},
		{	_ICODE_XTOTIME,			1,			1,				false,		(uptr)&function_xtotime,		1,				1,				NULL,			&gsSourceLight_xtotime[0]		},
		{	_ICODE_XTOTIMEX,		1,			1,				false,		(uptr)&function_xtotimex,		1,				1,				NULL,			&gsSourceLight_xtotimex[0]		},
		{	_ICODE_YEAR,			1,			1,				false,		(uptr)&function_year,			0,				1,				NULL,			&gsSourceLight_year[0]			},	// YEAR() by Stefano D'Amico, VJr 0.57, Apr.04.2015
		{	_ICODE_CONCATENATE,		1,			1,				false,		(uptr)&function_concatenate,	2,				2,				NULL,			&gsSourceLight_concatenate[0]	},
		{	_ICODE_ADD,				1,			1,				false,		(uptr)&function_add,			2,				2,				NULL,			&gsSourceLight_add[0]			},
		{	_ICODE_SUB,				1,			1,				false,		(uptr)&function_sub,			2,				2,				NULL,			&gsSourceLight_sub[0]			},
		{	_ICODE_MUL,				1,			1,				false,		(uptr)&function_mul,			2,				2,				NULL,			&gsSourceLight_mul[0]			},
		{	_ICODE_DIV,				1,			1,				false,		(uptr)&function_div,			2,				2,				NULL,			&gsSourceLight_div[0]			},
	//////
	// Insert above this step somewhere in the list of functions.
	// STEP2:
	//////////
		// Note:  Do not delete this line, it is used to terminate the function list
		{	0,						0,			0,				0,			0,								0,				0,				NULL,			NULL							}
	};




//////////
// Translation between iCodes and Command definitions.
//////
	struct SCommandData
	{
		//////////
		// The iCode relates to the known commands.
		// See cgcFundamentalSymbols and cgcKeywordKeywords in compiler_globals.h
		//////
			s32		iCode;


		//////////
		// Command prototype to call internally
		//////
			union {
				uptr		_command;
				void		(*command)		(SThisCode* thisCode, SComp* comp, SFunctionParams* rpar);
			};


		//////////
		// SourceLight information
		//////
			SSourceLightData*	data;
	};

	SCommandData gsKnownCommands[] = {
		//	iCode					Command Algorithm
		//  ------------------		--------------------------
		{	_ICODE_CLEAR,			(uptr)&command_clear		},
		{	_ICODE_DECLARE,			(uptr)&command_declare		},
		{	_ICODE_MODIFY,			(uptr)&command_modify		},
		{	_ICODE_OPEN,			(uptr)&command_open			},
		{	_ICODE_SET,				(uptr)&command_set			},
		{	_ICODE_USE,				(uptr)&command_use			},

		// Note:  Do not delete this line, it is used to terminate the command list
		{	0,						0							}
	};
