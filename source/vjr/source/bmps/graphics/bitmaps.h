//////////
//
// /libsf/source/vjr/bmps/graphics/bitmaps.h
//
//////
// Version 0.54
// Copyright (c) 2014 by Rick C. Hodgin
//////
// Last update:
//     Nov.13.2014 - Moved to bmps\
//////
// Change log:
//     Aug.01.2014 - Initial creation
//////
// Note:  To re-generate the bitmap files for compilation, run build_h_files.bat
//        after changing the bmp images.  This will re-generate all of the .h
//        files for compilation.
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




#if defined(_MSC_VER)
	#include "h\app_icon.h"
	#include "h\move.h"
	#include "h\minimize.h"
	#include "h\maximize.h"
	#include "h\close.h"
	#include "h\arrow_ul.h"
	#include "h\arrow_ur.h"
	#include "h\arrow_lr.h"
	#include "h\arrow_ll.h"

	#include "h\checkbox_off.h"
	#include "h\checkbox_on.h"

	#include "h\button.h"

	#include "h\textbox.h"

	#include "h\textbox_2d.h"
	#include "h\textbox_3d.h"

	#include "h\radio.h"

	#include "h\jdebi_app_icon.h"

	#include "h\sourcelight_icon.h"
	#include "h\output_icon.h"
	#include "h\debug_icon.h"
	#include "h\command_icon.h"
	#include "h\watch_icon.h"
	#include "h\locals_icon.h"
	#include "h\sourcecode_icon.h"

	#include "h\vjr_splash.h"

	#include "h\stoplight_red.h"
	#include "h\stoplight_amber.h"
	#include "h\stoplight_green.h"
	#include "h\stoplight_blue.h"

	#include "h\breakpoint_always.h"
	#include "h\breakpoint_always_countdown.h"
	#include "h\breakpoint_conditional_true.h"
	#include "h\breakpoint_conditional_false.h"
	#include "h\breakpoint_conditional_true_countdown.h"
	#include "h\breakpoint_conditional_false_countdown.h"

	#include "h\dapple.h"
	#include "h\dapple2.h"

	#include "h\carousel_carousel_icon.h"
	#include "h\carousel_tabs_icon.h"
	#include "h\carousel_pad.h"
	#include "h\carousel_icon.h"

	#include "h\grace\node_pad_blue.h"
	#include "h\grace\node_pad_green.h"
	#include "h\grace\node_pad_orange.h"
	#include "h\grace\node_pad_purple.h"
	#include "h\grace\node_pad_red.h"
	#include "h\grace\node_pad_yellow.h"

	#include "h\grace\node_port_ball_blue.h"
	#include "h\grace\node_port_ball_green.h"
	#include "h\grace\node_port_ball_orange.h"
	#include "h\grace\node_port_ball_purple.h"
	#include "h\grace\node_port_ball_red.h"
	#include "h\grace\node_port_ball_yellow.h"

	#include "h\cask_icons.h"
	#include "h\array_bmp.h"

#elif defined(__GNUC__)
	#include "h/app_icon.h"
	#include "h/move.h"
	#include "h/minimize.h"
	#include "h/maximize.h"
	#include "h/close.h"
	#include "h/arrow_ul.h"
	#include "h/arrow_ur.h"
	#include "h/arrow_lr.h"
	#include "h/arrow_ll.h"

	#include "h/checkbox_off.h"
	#include "h/checkbox_on.h"

	#include "h/button.h"

	#include "h/textbox.h"

	#include "h/textbox_2d.h"
	#include "h/textbox_3d.h"

	#include "h/radio.h"

	#include "h/jdebi_app_icon.h"

	#include "h/sourcelight_icon.h"
	#include "h/output_icon.h"
	#include "h/debug_icon.h"
	#include "h/command_icon.h"
	#include "h/watch_icon.h"
	#include "h/locals_icon.h"
	#include "h/sourcecode_icon.h"

	#include "h/vjr_splash.h"

	#include "h/stoplight_red.h"
	#include "h/stoplight_amber.h"
	#include "h/stoplight_green.h"
	#include "h/stoplight_blue.h"

	#include "h/breakpoint_always.h"
	#include "h/breakpoint_always_countdown.h"
	#include "h/breakpoint_conditional_true.h"
	#include "h/breakpoint_conditional_false.h"
	#include "h/breakpoint_conditional_true_countdown.h"
	#include "h/breakpoint_conditional_false_countdown.h"

	#include "h/dapple.h"
	#include "h/dapple2.h"

	#include "h/carousel_carousel_icon.h"
	#include "h/carousel_tabs_icon.h"
	#include "h/carousel_pad.h"
	#include "h/carousel_icon.h"

	#include "h/grace/node_pad_blue.h"
	#include "h/grace/node_pad_green.h"
	#include "h/grace/node_pad_orange.h"
	#include "h/grace/node_pad_purple.h"
	#include "h/grace/node_pad_red.h"
	#include "h/grace/node_pad_yellow.h"

	#include "h/grace/node_port_ball_blue.h"
	#include "h/grace/node_port_ball_green.h"
	#include "h/grace/node_port_ball_orange.h"
	#include "h/grace/node_port_ball_purple.h"
	#include "h/grace/node_port_ball_red.h"
	#include "h/grace/node_port_ball_yellow.h"

	#include "h/cask_icons.h"
	#include "h/array_bmp.h"

#else
	#error Unknown target for compilation (must be Windows or Linux)
#endif
