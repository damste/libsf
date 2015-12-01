//////////
//
// /libsf/source/vjr/source/vjr_compile_time_settings.h
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
//     Nov.05.2014
//////
// Change log:
//     Nov.05.2014 - Initial creation
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
// For debugging, the splash screen gets in the way if you're doing debugging
// on a single monitor machine (like a notebook) during the initial startup.
// You can set this property to false and prevent the splash screen from appearing.
// Also the focus border can sometimes be annoying if it's not rendered in blue
// and is merely a defined window consuming screen real-estate, but not re-rendering
// itself because the process is suspended in the debugger.  Oh, the humanity! :-)
//////

	//////////
	// Splash
	//////
 		bool glShowSplashScreen = true;
 		//bool glShowSplashScreen = false;


	//////////
	// Focus highlight border
	//////
		bool glShowFocusHighlightBorder = true;
		//bool glShowFocusHighlightBorder = false;


//////////
// Compiler-specific settings
//////
	#ifdef __GNUC__
		// gcc
		#define debug_break			asm("int $3")
		#define debug_nop			asm("nop")
		#ifndef __amd64
			#define __32_BIT_COMPILER__
		#else
			#define __64_BIT_COMPILER__
		#endif

	#elif defined(__unix)
                // Solaris compiler
		#define debug_break			asm("int $3")
		#define debug_nop			asm("nop")
                #ifndef __solaris
                    #define __solaris__
                #endif
        #ifdef __i386
            #define __32_BIT_COMPILER__
        #else
			#define __64_BIT_COMPILER__
        #endif

	#else
		// visual studio
		#ifndef _M_X64
			// 32-bit
			#define debug_break		_asm int 3
			#define debug_nop		_asm nop
			#define __32_BIT_COMPILER__
		#else
			// 64-bit
			void debugBreak(void)	{	int i = 4;	}
			void debugNop(void)		{	int i = 4;	}
			#define debug_break		debugBreak();
			#define debug_nop		debugNop();
			#define __64_BIT_COMPILER__
		#endif
	#endif


//////////
// Aug.11.2014 -- Added to track down functions that were slowing down the system.
//                Note:  This should be normally OFF as it is resource intensive.
//                Note:  It could also be refactored into a function to examine variables.
//#define _VJR_LOG_ALL
//////
	#ifdef _VJR_LOG_ALL
		#define logfunc(x)		iVjr_appendSystemLog((s8*)x)
	#else
		#define logfunc(x)
	#endif


//////////
// Added to track down silent errors, ones that don't really affect anything, but still shouldn't exist
//////
	#define error_silent		iError_silent((char*)__FUNCTION__)


//////////
// Force the bitmaps to be declared external for assignment through linking the bmps project
//////
	#ifndef _BMP_LOCALITY
		#define _BMP_LOCALITY 0
	#endif
	#ifndef _BXML_LOCALITY
		#define _BXML_LOCALITY 0
	#endif


///////////
// Should extra debugging information be included?
//////
	#define _EXTRA_DEBUGGING_DATA 1


//////////
// Should Grace 3D support be instantiated at startup?
//////
// 	#define _GRACE_COMPILE


//////////
// The language to compile for:
//		EN - English
//		IT - Italian
//		ES - Spanish
//////
	#define _LANG_EN
// 	#define _LANG_IT
// 	#define _LANG_ES
