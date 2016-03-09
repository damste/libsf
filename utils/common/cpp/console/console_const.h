//////////
//
// /libsf/utils/common/cpp/console/console_const.h
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
// Version 0.01
// Copyright (c) 2016 by Rick C. Hodgin
//////
// Last update:
//     Jan.12.2016
//////
// Change log:
//     Jan.12.2016 - Initial creation
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
// 	   _____                      _      
// 	  / ____|                    | |     
// 	 | |     ___  _ __  ___  ___ | | ___ 
// 	 | |    / _ \| '_ \/ __|/ _ \| |/ _ \
// 	 | |___| (_) | | | \__ \ (_) | |  __/
// 	  \_____\___/|_| |_|___/\___/|_|\___|
//      LibSF -- Generic console support
//////////




//////////
// Helper macro to make searching for properties easier
// Use as:  if (console_check_prop(width))
//			if (console_check_value(yes))
//////
	#define console_check_prop(x)		(cb->prop.length  == sizeof(cgc_##x) - 1 && _memicmp(cb->prop.data_cs8,  cgc_##x, cb->prop.length)  == 0)
	#define console_check_value(x)		(cb->value.length == sizeof(cgc_##x) - 1 && _memicmp(cb->value.data_cs8, cgc_##x, cb->value.length) == 0)

	#define _ROUND_CASK_LEFT_SOLID		"\120"
	#define _ROUND_CASK_LEFT_UP			"\121"
	#define _ROUND_CASK_LEFT_DOWN		"\122"
	#define _ROUND_CASK_LEFT_BOTH		"\123"
	#define _ROUND_CASK_RIGHT_SOLID		"\124"
	#define _ROUND_CASK_RIGHT_UP		"\125"
	#define _ROUND_CASK_RIGHT_DOWN		"\126"
	#define _ROUND_CASK_RIGHT_BOTH		"\127"

	#define _TRIANGLE_CASK_LEFT_SOLID	"\130"
	#define _TRIANGLE_CASK_LEFT_UP		"\131"
	#define _TRIANGLE_CASK_LEFT_DOWN	"\132"
	#define _TRIANGLE_CASK_LEFT_BOTH	"\133"
	#define _TRIANGLE_CASK_RIGHT_SOLID	"\134"
	#define _TRIANGLE_CASK_RIGHT_UP		"\135"
	#define _TRIANGLE_CASK_RIGHT_DOWN	"\136"
	#define _TRIANGLE_CASK_RIGHT_BOTH	"\137"

	#define _SQUARE_CASK_LEFT_SOLID		"\140"
	#define _SQUARE_CASK_LEFT_UP		"\141"
	#define _SQUARE_CASK_LEFT_DOWN		"\142"
	#define _SQUARE_CASK_LEFT_BOTH		"\143"
	#define _SQUARE_CASK_RIGHT_SOLID	"\144"
	#define _SQUARE_CASK_RIGHT_UP		"\145"
	#define _SQUARE_CASK_RIGHT_DOWN		"\146"
	#define _SQUARE_CASK_RIGHT_BOTH		"\147"

	#define _UTILITY_CASK_LEFT_SOLID	"\150"
	#define _UTILITY_CASK_LEFT_UP		"\151"
	#define _UTILITY_CASK_LEFT_DOWN		"\152"
	#define _UTILITY_CASK_LEFT_BOTH		"\153"
	#define _UTILITY_CASK_RIGHT_SOLID	"\154"
	#define _UTILITY_CASK_RIGHT_UP		"\155"
	#define _UTILITY_CASK_RIGHT_DOWN	"\156"
	#define _UTILITY_CASK_RIGHT_BOTH	"\157"


//////////
// Returned error codes
//////
	cs32		_CONSOLE_ERROR__NO_ERROR					= 0;
	cs32		_CONSOLE_ERROR__HANDLE_NOT_FOUND			= -1;
	cs32		_CONSOLE_ERROR__CANNOT_ALLOCATE_BUFFER		= -2;
	cs32		_CONSOLE_ERROR__INVALID_PARAMETERS			= -3;
	cs32		_CONSOLE_ERROR__INVALID_WINDOW				= -4;
	cs32		_CONSOLE_ERROR__CANNOT_CREATE_WINDOW		= -5;
	cs32		_CONSOLE_ERROR__FATAL_ERROR					= -6;
	cs32		_CONSOLE_ERROR__FONT_ALLOCATION_ERROR		= -7;
	cs32		_CONSOLE_ERROR__FONT_NOT_SUPPORTED_ERROR	= -8;
	cs32		_CONSOLE_ERROR__WINDOW_SETUP_NOT_COMPLETED	= -9;


//////////
// Miscellaneous constants
//////
	cs32		_CONSOLE_CURSOR_TIMER						= 0x12345678;


//////////
// Fixed point font indices (always the first four, every other custom-allocated font is after that)
//////
	cs32		_CONSOLE_FONT_8x6							= 0;
	cs32		_CONSOLE_FONT_8x8							= 1;
	cs32		_CONSOLE_FONT_8x14							= 2;
	cs32		_CONSOLE_FONT_8x16							= 3;
	cs32		_CONSOLE_FONT_16x32							= 4;
	cs32		_CONSOLE_FONT_8x12							= 5;
	cs32		_CONSOLE_FONT_8x16_8						= 6;	// 8x16 font, using 8x8 font doubled
	cs32		_CONSOLE_FONT__MAX_FIXED				= 6;


//////////
// Properties
//////
	cs8			cgc_console_x[]								= "x";
	cs8			cgc_console_y[]								= "y";
	cs8			cgc_console_left[]							= "left";
	cs8			cgc_console_top[]							= "top";
	cs8			cgc_console_width[]							= "width";
	cs8			cgc_console_height[]						= "height";
	cs8			cgc_console_charWidth[]						= "charwidth";
	cs8			cgc_console_charHeight[]					= "charheight";
	cs8			cgc_console_scrollRows[]					= "scrollrows";
	cs8			cgc_console_backColor[]						= "backcolor";
	cs8			cgc_console_foreColor[]						= "forecolor";
	cs8			cgc_console_charColor[]						= "charcolor";
	cs8			cgc_console_title[]							= "title";
	cs8			cgc_console_visible[]						= "visible";
	cs8			cgc_console_yes[]							= "yes";
	cs8			cgc_console_true[]							= "true";
	cs8			cgc_console_dot_t_dot[]						= ".t.";


//////////
// 8-bit color patterns seen on the VGA (with some modern adjustments)
//////
	const SBgra colors_vga[] =
	{
		{	bgra(0, 0, 0, 255)			},		// 0	- black
		{	bgra(192, 0, 0, 255)		},		// 1	- blue
		{	bgra(0, 192, 0, 255)		},		// 2	- green
		{	bgra(192, 192, 0, 255)		},		// 3	- cyan
		{	bgra(0, 0, 192, 255)		},		// 4	- red
		{	bgra(164, 64, 164, 255)		},		// 5	- purple
		{	bgra(64, 192, 192, 255)		},		// 6	- tan
		{	bgra(164, 164, 164, 255)	},		// 7	- gray
		{	bgra(64, 64, 64, 255)		},		// 8	- charcoal
		{	bgra(255, 32, 32, 255)		},		// 9	- bright blue
		{	bgra(32, 255, 32, 255)		},		// 10	- bright green
		{	bgra(255, 255, 32, 255)		},		// 11	- bright cyan
		{	bgra(32, 32, 255, 255)		},		// 12	- bright red
		{	bgra(255, 92, 255, 255)		},		// 13	- bright purple
		{	bgra(255, 255, 164, 255)	},		// 14	- bright yellow
		{	bgra(255, 255, 255, 255)	}		// 15	- bright white
	};


//////////
// Internal constants
//////
	cs8			cgc_internal_fontName[]					= "$fixed";
