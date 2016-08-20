//////////
//
// /libsf/utils/common/cpp/include/errors.h
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
//     May.07.2016
//////
// Change log:
//     May.07.2016 - Initial creation
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
//
//////////




// #pragma once
#ifndef __ERRORS_H__
#define __ERRORS_H__


//////////
// Errors
//////
	cu32			_ERROR_OKAY								= 0;
	cu32			_ERROR_OUT_OF_MEMORY					= 1;
	cu32			_ERROR_UNEXPECTED_COMMAND				= 2;
	cu32			_ERROR_CONTEXT_HAS_CHANGED				= 3;
	cu32			_ERROR_FULL_RECOMPILE_REQUIRED			= 4;
	cu32			_ERROR_NOT_A_VARIABLE					= 5;
	cu32			_ERROR_NUMERIC_OVERFLOW					= 6;
	cu32			_ERROR_NOT_NUMERIC						= 7;
	cu32			_ERROR_EMPTY_STRING						= 8;
	cu32			_ERROR_SYNTAX							= 9;
	cu32			_ERROR_UNRECOGNIZED_PARAMETER			= 10;
	cu32			_ERROR_OUT_OF_RANGE						= 11;
	cu32			_ERROR_COMMA_EXPECTED					= 12;
	cu32			_ERROR_TOO_MANY_PARAMETERS				= 13;
	cu32			_ERROR_DATA_TYPE_MISMATCH				= 14;
	cu32			_ERROR_FEATURE_NOT_AVAILABLE			= 15;
	cu32			_ERROR_P1_IS_INCORRECT					= 16;
	cu32			_ERROR_P2_IS_INCORRECT					= 17;
	cu32			_ERROR_P3_IS_INCORRECT					= 18;
	cu32			_ERROR_P4_IS_INCORRECT					= 19;
	cu32			_ERROR_P5_IS_INCORRECT					= 20;
	cu32			_ERROR_P6_IS_INCORRECT					= 21;
	cu32			_ERROR_P7_IS_INCORRECT					= 22;
	cu32			_ERROR_INTERNAL_ERROR					= 23;
	cu32			_ERROR_INVALID_ARGUMENT_TYPE_COUNT		= 24;
	cu32			_ERROR_VARIABLE_NOT_FOUND				= 25;
	cu32			_ERROR_ALIAS_NOT_FOUND					= 26;
	cu32			_ERROR_INVALID_WORK_AREA				= 27;
	cu32			_ERROR_ALIAS_ALREADY_IN_USE				= 28;
	cu32			_ERROR_PARENTHESIS_EXPECTED				= 29;
	cu32			_ERROR_MISSING_PARAMETER				= 30;

	// These relate in a 1:1 ratio with the _DBF_ERROR_* and _CDX_ERROR_* constants of the same name, that are defined internally in dbf.cpp, and cdx.cpp
	cu32			_ERROR_DBF_UNABLE_TO_OPEN_TABLE			= 31;
	cu32			_ERROR_DBF_WORK_AREA_ALREADY_IN_USE		= 32;
	cu32			_ERROR_DBF_ERROR_OPENING_DBC			= 33;
	cu32			_ERROR_DBF_WORK_AREA_NOT_IN_USE			= 34;
	cu32			_ERROR_DBF_ERROR_READING_HEADER1		= 35;
	cu32			_ERROR_DBF_UNKNOWN_TABLE_TYPE			= 36;
	cu32			_ERROR_DBF_MEMORY_ALLOCATION			= 37;
	cu32			_ERROR_DBF_ERROR_READING_HEADER2		= 38;
	cu32			_ERROR_DBF_TABLE_NAME_TOO_LONG			= 39;
	cu32			_ERROR_DBF_MEMORY_ROW					= 40;
	cu32			_ERROR_DBF_MEMORY_ORIGINAL				= 41;
	cu32			_ERROR_DBF_MEMORY_INDEX					= 42;
	cu32			_ERROR_DBF_INVALID_WORK_AREA			= 43;
	cu32			_ERROR_DBF_NO_MORE_WORK_AREAS			= 44;
	cu32			_ERROR_DBF_LOCKING						= 45;
	cu32			_ERROR_DBF_WRITING						= 46;
	cu32			_ERROR_DBF_SEEKING						= 47;
	cu32			_ERROR_DBF_NO_DATA						= 48;
	cu32			_ERROR_DBF_UNKNOWN_MEMO_FORMAT			= 49;

	cu32			_ERROR_CONFLICTING_PARAMETERS			= 80;
	cu32			_ERROR_PARAMETER_IS_INCORRECT			= 81;
	cu32			_ERROR_TABLE_ALREADY_IN_USE				= 82;
	cu32			_ERROR_PARAMETER_TOO_LONG				= 83;
	cu32			_ERROR_UNABLE_TO_OPEN_DBC				= 84;
	cu32			_ERROR_DIVISION_BY_ZERO					= 85;
	cu32			_ERROR_CANNOT_BE_NEGATIVE				= 86;
	cu32			_ERROR_CANNOT_BE_ZERO_OR_NEGATIVE		= 87;
	cu32			_ERROR_UNABLE_TO_AUTOVALIDATE			= 88;
	cu32			_ERROR_DBF_GENERAL_ERROR				= 89;
	cu32			_ERROR_CANNOT_BE_ZERO					= 90;
	cu32			_ERROR_MUST_BE_LOGICAL					= 91;
	cu32			_ERROR_PARAMETER_MUST_BE_8_16_32_64		= 92;
	cu32			_ERROR_TOO_BIG_FOR_TARGET				= 93;
	cu32			_ERROR_NO_INDEX_IS_LOADED				= 94;
	cu32			_ERROR_INVALID_INDEX_TAG				= 95;
	cu32			_ERROR_UNABLE_TO_SAVE					= 96;
	cu32			_ERROR_INVALID_PARAMETERS				= 97;
	cu32			_ERROR_PARAMETER_MUST_BE_1				= 98;
	cu32			_ERROR_INVALID_CORRUPT_NEEDS_REBUILT	= 99;
	cu32			_ERROR_UNABLE_TO_LOCK_FOR_WRITE			= 100;
	cu32			_ERROR_UNABLE_TO_LOCK_FOR_READ			= 101;
	cu32			_ERROR_UNABLE_TO_INITIALIZE				= 102;
	cu32			_ERROR_UNKNOWN_FUNCTION					= 103;
	cu32			_ERROR_DLL_NOT_FOUND					= 104;
	cu32			_ERROR_FUNCTION_NOT_FOUND				= 105;
	cu32			_ERROR_VARIABLE_IS_FIXED				= 106;
	cu32			_ERROR_FEATURE_NOT_YET_CODED			= 107;
	cu32			_ERROR_NESTING_ERROR					= 108;
	cu32			_ERROR_TABLE_NUMBER_INVALID				= 109;

#endif	// __ERRORS_H__
