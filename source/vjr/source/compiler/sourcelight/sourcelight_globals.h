//////////
//
// /libsf/source/vjr/source/compiler/sourcelight/sourcelight_globals.h
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
// Version 0.55
// Copyright (c) 2015 by Rick C. Hodgin
//////
// Last update:
//     Mar.04.2014
//////
// Change log:
//     Mar.04.2014 - Initial creation
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
//     ____                                 _      _         _      _   
//    / ___|   ___   _   _  _ __  ___  ___ | |    (_)  __ _ | |__  | |_ 
//    \___ \  / _ \ | | | || '__|/ __|/ _ \| |    | | / _` || '_ \ | __|
//     ___) || (_) || |_| || |  | (__|  __/| |___ | || (_| || | | || |_ 
//    |____/  \___/  \__,_||_|   \___|\___||_____||_| \__, ||_| |_| \__|
//                                                    |___/
//  SourceLight -- A companion utility for augmenting editors and compilers.
//
//////////





//////////
// Syntax highlight colors for SourceLight
//////
	SBgra				colorSynHi_keyword					= { rgba(0, 128, 164, 255) };			// Sky blue




//////////
// iCodes specific to SourceLight
//////
	cs32		_ICODE_SL_NAMESTATIC		= 2000000000;
	cs32		_ICODE_SL_TITLE				= 2000000001;
	cs32		_ICODE_SL_SHORT				= 2000000002;
	cs32		_ICODE_SL_CATEGORY			= 2000000003;
	cs32		_ICODE_SL_SUBCATEGORY		= 2000000004;
	cs32		_ICODE_SL_PREFACE			= 2000000005;
	cs32		_ICODE_SL_SYNTAX			= 2000000006;
	cs32		_ICODE_SL_LONG				= 2000000007;
	cs32		_ICODE_SL_NOTES				= 2000000008;
	cs32		_ICODE_SL_PRE				= 2000000009;
	cs32		_ICODE_SL_B					= 2000000010;
	cs32		_ICODE_SL_I					= 2000000011;
	cs32		_ICODE_SL_U					= 2000000012;
	cs32		_ICODE_SL_COLOR				= 2000000013;
	cs32		_ICODE_SL_COMMAND			= 2000000014;
	cs32		_ICODE_SL_FUNCTION			= 2000000015;
	cs32		_ICODE_SL_FLAGS				= 2000000016;
	cs32		_ICODE_SL_PARAMS			= 2000000017;
	cs32		_ICODE_SL_SOURCELIGHT		= 2000000018;
	cs32		_ICODE_SL_OPTIONAL			= 2000000019;
	cs32		_ICODE_SL_REQUIRED			= 2000000020;
	cs32		_ICODE_SL_RETURNS			= 2000000021;
	cs32		_ICODE_SL_DEFAULTS			= 2000000022;
	cs32		_ICODE_SL_FLOW				= 2000000023;
	cs32		_ICODE_SL_META				= 2000000024;
	cs32		_ICODE_SL_MEFA				= 2000000025;
	cs32		_ICODE_SL_MEMA				= 2000000026;
	cs32		_ICODE_SL_MEIA				= 2000000027;
	cs32		_ICODE_SL_EXAMPLE			= 2000000028;
	cs32		_ICODE_SL_MORE				= 2000000029;
	cs32		_ICODE_SL_RELATED			= 2000000030;
	cs32		_ICODE_SL_AFTER				= 2000000031;
	cs32		_ICODE_SL_FOLLOWS			= 2000000032;
	cs32		_ICODE_SL_OR				= 2000000033;
	cs32		_ICODE_SL_KEYWORD			= 2000000034;
	cs32		_ICODE_SL_VARIABLE			= 2000000035;
	cs32		_ICODE_SL_NONE				= 2000000036;

// iCats
	cs32		_ICAT_SL_KEYWORD			= 2000000000;




//////////
// Keywords for SourceLight's definition language
//////
	SAsciiCompSearcher	cgcKeywordsSourceLight[] =
	{
		// keyword				length		repeats?	extra (type)							first on line?		category				syntax highlight color		syntax highlight bold		onCandidateMatch()		onFind()	compilerDictionaryLookup()
		{ "namestatic",			10,			false,		_ICODE_SL_NAMESTATIC,					true,				_ICAT_SL_KEYWORD,		&colorSynHi_keyword,		false,						null0,					null0,		null0 },
		{ "title",				5,			false,		_ICODE_SL_TITLE,						true,				_ICAT_SL_KEYWORD,		&colorSynHi_keyword,		false,						null0,					null0,		null0 },
		{ "short",				5,			false,		_ICODE_SL_SHORT,						true,				_ICAT_SL_KEYWORD,		&colorSynHi_keyword,		false,						null0,					null0,		null0 },
		{ "category",			8,			false,		_ICODE_SL_CATEGORY,						true,				_ICAT_SL_KEYWORD,		&colorSynHi_keyword,		false,						null0,					null0,		null0 },
		{ "subcategory",		11,			false,		_ICODE_SL_SUBCATEGORY,					true,				_ICAT_SL_KEYWORD,		&colorSynHi_keyword,		false,						null0,					null0,		null0 },
		{ "preface",			7,			false,		_ICODE_SL_PREFACE,						true,				_ICAT_SL_KEYWORD,		&colorSynHi_keyword,		false,						null0,					null0,		null0 },
		{ "syntax",				6,			false,		_ICODE_SL_SYNTAX,						true,				_ICAT_SL_KEYWORD,		&colorSynHi_keyword,		false,						null0,					null0,		null0 },
		{ "long",				4,			false,		_ICODE_SL_LONG,							true,				_ICAT_SL_KEYWORD,		&colorSynHi_keyword,		false,						null0,					null0,		null0 },
		{ "notes",				5,			false,		_ICODE_SL_NOTES,						true,				_ICAT_SL_KEYWORD,		&colorSynHi_keyword,		false,						null0,					null0,		null0 },
		{ "pre",				3,			false,		_ICODE_SL_PRE,							false,				_ICAT_SL_KEYWORD,		&colorSynHi_keyword,		false,						null0,					null0,		null0 },
		{ "b",					1,			false,		_ICODE_SL_B,							false,				_ICAT_SL_KEYWORD,		&colorSynHi_keyword,		false,						null0,					null0,		null0 },
		{ "i",					1,			false,		_ICODE_SL_I,							false,				_ICAT_SL_KEYWORD,		&colorSynHi_keyword,		false,						null0,					null0,		null0 },
		{ "u",					1,			false,		_ICODE_SL_U,							false,				_ICAT_SL_KEYWORD,		&colorSynHi_keyword,		false,						null0,					null0,		null0 },
		{ "color",				5,			false,		_ICODE_SL_COLOR,						false,				_ICAT_SL_KEYWORD,		&colorSynHi_keyword,		false,						null0,					null0,		null0 },
		{ "command",			7,			false,		_ICODE_SL_COMMAND,						true,				_ICAT_SL_KEYWORD,		&colorSynHi_keyword,		false,						null0,					null0,		null0 },
		{ "function",			8,			false,		_ICODE_SL_FUNCTION,						true,				_ICAT_SL_KEYWORD,		&colorSynHi_keyword,		false,						null0,					null0,		null0 },
		{ "flags",				5,			false,		_ICODE_SL_FLAGS,						true,				_ICAT_SL_KEYWORD,		&colorSynHi_keyword,		false,						null0,					null0,		null0 },
		{ "params",				6,			false,		_ICODE_SL_PARAMS,						true,				_ICAT_SL_KEYWORD,		&colorSynHi_keyword,		false,						null0,					null0,		null0 },
		{ "sourcelight",		11,			false,		_ICODE_SL_SOURCELIGHT,					false,				_ICAT_SL_KEYWORD,		&colorSynHi_keyword,		false,						null0,					null0,		null0 },
		{ "optional",			8,			false,		_ICODE_SL_OPTIONAL,						false,				_ICAT_SL_KEYWORD,		&colorSynHi_keyword,		false,						null0,					null0,		null0 },
		{ "required",			8,			false,		_ICODE_SL_REQUIRED,						false,				_ICAT_SL_KEYWORD,		&colorSynHi_keyword,		false,						null0,					null0,		null0 },
		{ "returns",			7,			false,		_ICODE_SL_RETURNS,						true,				_ICAT_SL_KEYWORD,		&colorSynHi_keyword,		false,						null0,					null0,		null0 },
		{ "defaults",			8,			false,		_ICODE_SL_DEFAULTS,						true,				_ICAT_SL_KEYWORD,		&colorSynHi_keyword,		false,						null0,					null0,		null0 },
		{ "flow",				4,			false,		_ICODE_SL_FLOW,							true,				_ICAT_SL_KEYWORD,		&colorSynHi_keyword,		false,						null0,					null0,		null0 },
		{ "meta",				4,			false,		_ICODE_SL_META,							true,				_ICAT_SL_KEYWORD,		&colorSynHi_keyword,		false,						null0,					null0,		null0 },
		{ "mefa",				4,			false,		_ICODE_SL_MEFA,							true,				_ICAT_SL_KEYWORD,		&colorSynHi_keyword,		false,						null0,					null0,		null0 },
		{ "meia",				4,			false,		_ICODE_SL_MEIA,							true,				_ICAT_SL_KEYWORD,		&colorSynHi_keyword,		false,						null0,					null0,		null0 },
		{ "mema",				4,			false,		_ICODE_SL_MEMA,							true,				_ICAT_SL_KEYWORD,		&colorSynHi_keyword,		false,						null0,					null0,		null0 },
		{ "example",			7,			false,		_ICODE_SL_EXAMPLE,						true,				_ICAT_SL_KEYWORD,		&colorSynHi_keyword,		false,						null0,					null0,		null0 },
		{ "more",				4,			false,		_ICODE_SL_MORE,							true,				_ICAT_SL_KEYWORD,		&colorSynHi_keyword,		false,						null0,					null0,		null0 },
		{ "related",			7,			false,		_ICODE_SL_RELATED,						true,				_ICAT_SL_KEYWORD,		&colorSynHi_keyword,		false,						null0,					null0,		null0 },
		{ "after",				5,			false,		_ICODE_SL_AFTER,						false,				_ICAT_SL_KEYWORD,		&colorSynHi_keyword,		false,						null0,					null0,		null0 },
		{ "follows",			7,			false,		_ICODE_SL_FOLLOWS,						false,				_ICAT_SL_KEYWORD,		&colorSynHi_keyword,		false,						null0,					null0,		null0 },
		{ "or",					2,			false,		_ICODE_SL_OR,							false,				_ICAT_SL_KEYWORD,		&colorSynHi_keyword,		false,						null0,					null0,		null0 },
		{ "keyword",			7,			false,		_ICODE_SL_KEYWORD,						false,				_ICAT_SL_KEYWORD,		&colorSynHi_keyword,		false,						null0,					null0,		null0 },
		{ "variable",			8,			false,		_ICODE_SL_VARIABLE,						false,				_ICAT_SL_KEYWORD,		&colorSynHi_keyword,		false,						null0,					null0,		null0 },
		{ "none",				4,			false,		_ICODE_SL_NONE,							false,				_ICAT_SL_KEYWORD,		&colorSynHi_keyword,		false,						null0,					null0,		null0 },

		// Terminates the list
		{ 0,					0,			0,			0,										0,					0,						0,							0,							0,						0,			0 }
	};
