//////////
//
// /libsf/source/vjr/commands/funcs/x.cpp
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
// Function: XTOD()
// Converts a DATETIMEX() into a DATE().
//
//////
// Version 0.58
// Last update:
//     Apr.26.2015
//////
// Change log:
//     Apr.26.2015 - Initial creation by Rick C. Hodgin
//////
// Parameters:
//     p1			-- DatetimeX
//
//////
// Returns:
//    Date			-- A conversion into the DATE() format.
//////
// Example:
//    k = DATETIMEX()
//    ? XTOD(k)
//////
	void function_xtod(SReturnsParams* rpar)
	{
		// Return xtod
		ifunction_timesAndDatesConversion_common(rpar, _CONVERSION_FUNCTION_DATETIMEX, _CONVERSION_FUNCTION_DATE);
	}




//////////
//
// Function: XTOSECONDS()
// Converts a DATETIMEX() into a SECONDS().
//
//////
// Version 0.58
// Last update:
//     Apr.26.2015
//////
// Change log:
//     Apr.26.2015 - Initial creation by Rick C. Hodgin
//////
// Parameters:
//     p1			-- DatetimeX
//
//////
// Returns:
//    Character		-- A conversion into the SECONDS() format.
//////
// Example:
//    k = DATETIMEX()
//    ? XTOSECONDS(k)
//////
	void function_xtoseconds(SReturnsParams* rpar)
	{
		// Return xtoseconds
		ifunction_timesAndDatesConversion_common(rpar, _CONVERSION_FUNCTION_DATETIMEX, _CONVERSION_FUNCTION_SECONDS);
	}




//////////
//
// Function: XTOSECONDSX()
// Converts a DATETIMEX() into a SECONDSX().
//
//////
// Version 0.58
// Last update:
//     Apr.26.2015
//////
// Change log:
//     Apr.26.2015 - Initial creation by Rick C. Hodgin
//////
// Parameters:
//     p1			-- DatetimeX
//
//////
// Returns:
//    Character		-- A conversion into the SECONDSX() format.
//////
// Example:
//    k = DATETIMEX()
//    ? XTOSECONDSX(k)
//////
	void function_xtosecondsx(SReturnsParams* rpar)
	{
		// Return xtosecondsx
		ifunction_timesAndDatesConversion_common(rpar, _CONVERSION_FUNCTION_DATETIMEX, _CONVERSION_FUNCTION_SECONDSX);
	}




//////////
//
// Function: XTOTIME()
// Converts a DATETIMEX() into a TIME().
//
//////
// Version 0.58
// Last update:
//     Apr.26.2015
//////
// Change log:
//     Apr.26.2015 - Initial creation by Rick C. Hodgin
//////
// Parameters:
//     p1			-- DatetimeX
//
//////
// Returns:
//    Character		-- A conversion into the TIME() format.
//////
// Example:
//    k = DATETIMEX()
//    ? XTOTIME(k)
//////
	void function_xtotime(SReturnsParams* rpar)
	{
		// Return xtotime
		ifunction_timesAndDatesConversion_common(rpar, _CONVERSION_FUNCTION_DATETIMEX, _CONVERSION_FUNCTION_TIME);
	}




//////////
//
// Function: XTOTIMEX()
// Converts a DATETIMEX() into a TIMEX().
//
//////
// Version 0.58
// Last update:
//     Apr.26.2015
//////
// Change log:
//     Apr.26.2015 - Initial creation by Rick C. Hodgin
//////
// Parameters:
//     p1			-- DatetimeX
//
//////
// Returns:
//    Character		-- A conversion into the TIMEX() format.
//////
// Example:
//    k = DATETIMEX()
//    ? XTOTIMEX(k)
//////
	void function_xtotimex(SReturnsParams* rpar)
	{
		// Return xtotimex
		ifunction_timesAndDatesConversion_common(rpar, _CONVERSION_FUNCTION_DATETIMEX, _CONVERSION_FUNCTION_TIMEX);
	}




//////////
//
// Function: XTOT()
// Converts a DATETIMEX() into a DATETIME().
//
//////
// Version 0.58
// Last update:
//     Apr.26.2015
//////
// Change log:
//     Apr.26.2015 - Initial creation by Rick C. Hodgin
//////
// Parameters:
//     p1			-- Datetime
//
//////
// Returns:
//    Datetime		-- A conversion into the DATETIME() format.
//////
// Example:
//    k = DATETIMEX()
//    ? XTOT(k)
//////
	void function_xtot(SReturnsParams* rpar)
	{
		// Return xtot
		ifunction_timesAndDatesConversion_common(rpar, _CONVERSION_FUNCTION_DATETIMEX, _CONVERSION_FUNCTION_DATETIME);
	}
