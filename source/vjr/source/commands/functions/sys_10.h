//////////
//
// /libsf/source/vjr/source/commands/functions/sys_10.h
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
// Copyright (c) 2014-2017 by Rick C. Hodgin
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




	//////////
	// Parameter 1 must be numeric
	//////
		if (!iVariable_isValid(varP1) || !iVariable_isTypeNumeric(varP1))
		{
			iError_report_byNumber(_ERROR_P1_IS_INCORRECT, iVariable_get_relatedComp(varP1), false);
			return;
		}


	//////////
	// Grab julian number
	//////
		lfJulian = iiVariable_getAs_f32(varP1, false, &error, &errorNum);
		if (error)
		{
			iError_report_byNumber(errorNum, iVariable_get_relatedComp(varP1), false);
			return;
		}


	//////////
	// Must be in the range -- Sep.14.1752 to Dec.31.9999
	//////
		if (lfJulian < 2361222/*Sep.14.1752*/ || lfJulian > 5373484/*Dec.31.9999*/)
		{
			// For these values, return a blank date
			result = iVariable_create(_VAR_TYPE_DATE, NULL, true);
			if (result)
				memset(result->value.data_s8, 32, result->value.length);	// Make it all spaces

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
		varTemp = iVariable_createAndPopulate_byText(_VAR_TYPE_DATE, buffer, 8, false);
		if (!varTemp)
		{
			// Fatal error
			iError_report_byNumber(_ERROR_INTERNAL_ERROR, NULL, false);
			return;
		}


	//////////
	// Create and populate the return variable
	//////
		result = iVariable_convertForDisplay(varTemp);


	//////////
	// Clean house and exit to report any errors
	//////
		iVariable_delete(varTemp, true);
		goto clean_exit;
