//////////
//
// /libsf/source/vjr/source/vjr_const_version.h
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
// Copyright (c) 2015-2017 by Rick C. Hodgin
//////
// Last update:
//     Nov.28.2015
//////
// Change log:
//     Nov.28.2015 - Initial creation
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
// Version information
//////
	const u8			cgcVersionShort[]					= "Version 0.58";
#if !defined(_NONVJR_COMPILE)
	const u8			cgc_appName[]						= "Visual FreePro, Jr.";				// Used for Grace 3D's OpenGL window (each app that uss the VJr engine can have its own name)
#endif
#ifdef __GNUC__
	#ifndef __amd64
		const u8		cgcScreenTitle[]					= "Visual FreePro, Jr. Version 0.58 | Nov.30.2015 | GCC 32-bit";
		const u8		cgcJDebiTitle[]						= "JDebi Debugger Version 0.58 | Nov.30.2015 | GCC 32-bit";
		const u8		cgcVersionText[]					= "Visual FreePro, Jr. 32-bit 00.58.0001.9999 for Windows";
		const u8		cgcVersion1Text[]					= "Visual FreePro, Jr. 32-bit 00.58.0001.9999 for Windows [Nov.30.2015 00:00:00] Product ID 31415-926-5358979-32384";
		const u8		cgcVersion4Text[]					= "00.58.3201.9999";
	#else
		const u8		cgcScreenTitle[]					= "Visual FreePro, Jr. Version 0.58 | Nov.30.2015   | GCC 64-bit";
		const u8		cgcJDebiTitle[]						= "JDebi Debugger Version 0.58 | Nov.30.2015 | GCC 64-bit";
		const u8		cgcVersionText[]					= "Visual FreePro, Jr. 64-bit 00.58.0001.9999 for Windows";
		const u8		cgcVersion1Text[]					= "Visual FreePro, Jr. 64-bit 00.58.0001.9999 for Windows [Nov.30.2015 00:00:00] Product ID 31415-926-5358979-32384";
		const u8		cgcVersion4Text[]					= "00.58.6401.9999";
	#endif
#else
	#if !defined(__64_BIT_COMPILER__)
		const u8		cgcScreenTitle[]					= "Visual FreePro, Jr. Version 0.58 | Nov.30.2015 | MSVC 32-bit";
		const u8		cgcJDebiTitle[]						= "JDebi Debugger Version 0.58 | Nov.30.2015 | MSVC 32-bit";
		const u8		cgcVersionText[]					= "Visual FreePro, Jr. 32-bit 00.58.0001.9999 for Windows";
		const u8		cgcVersion1Text[]					= "Visual FreePro, Jr. 32-bit 00.58.0001.9999 for Windows [Nov.30.2015 00:00:00] Product ID 31415-926-5358979-32384";
		const u8		cgcVersion4Text[]					= "00.58.3201.9999";
	#else
		const u8		cgcScreenTitle[]					= "Visual FreePro, Jr. Version 0.58 | Nov.30.2015 | MSVC 64-bit";
		const u8		cgcJDebiTitle[]						= "JDebi Debugger Version 0.58 | Nov.30.2015 | MSVC 64-bit";
		// VERSION() support
		const u8		cgcVersionText[]					= "Visual FreePro, Jr. 64-bit 00.58.0001.9999 for Windows";
		const u8		cgcVersion1Text[]					= "Visual FreePro, Jr. 64-bit 00.58.0001.9999 for Windows [Nov.30.2015 00:00:00] Product ID 31415-926-5358979-32384";
		const u8		cgcVersion4Text[]					= "00.58.6401.9999";
	#endif
#endif
	const s32			gnVersion5							= (s32)(0.58 * 100.0);		// Version 0.58	(Nov.28.2015 RCH -- stored as (cs32)58, but shown here as 0.58 so it's auto-updated in find-and-replace operations)
	const s32			gnVersion2							= 2;						// Professional
	const s32			gnVersion3							= 0;						// English
