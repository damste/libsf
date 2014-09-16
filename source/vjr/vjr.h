//////////
//
// /libsf/source/vjr/vjr.h
//
//////
// Version 0.53
// Copyright (c) 2014 by Rick C. Hodgin
//////
// Last update:
//     Feb.12.2014
//////
// Change log:
//     Feb.12.2014 - Initial creation
//////
//
// This software is released as Liberty Software under a Repeat License, as governed
// by the Public Benefit License v1.0 or later (PBL).
//
// You are free to use, copy, modify and share this software.  However, it can only
// be released under the PBL version indicated, and every project must include a copy
// of the pbl.txt document for its version as is at http://www.libsf.org/licenses/.
//
// For additional information about this project, or to view the license, see:
//
//     http://www.libsf.org/
//     http://www.libsf.org/licenses/
//     http://www.visual-freepro.org/vjr/indexmain.html
//     http://www.visual-freepro.org/wiki/index.php/PBL
//     http://www.visual-freepro.org/wiki/index.php/Repeat_License
//
// Thank you.  And may The Lord bless you richly as you lift up your life, your
// talents, your gifts, your praise, unto Him.  In Jesus' name I pray.  Amen.
//
//

#ifndef WINVER                  // Specifies that the minimum required platform is Windows Vista.
#define WINVER 0x0600           // Change this to the appropriate value to target other versions of Windows.
#endif

#ifndef _WIN32_WINNT            // Specifies that the minimum required platform is Windows Vista.
#define _WIN32_WINNT 0x0600     // Change this to the appropriate value to target other versions of Windows.
#endif

#ifndef _WIN32_WINDOWS          // Specifies that the minimum required platform is Windows 98.
#define _WIN32_WINDOWS 0x0410   // Change this to the appropriate value to target Windows Me or later.
#endif

#ifndef _WIN32_IE               // Specifies that the minimum required platform is Internet Explorer 7.0.
#define _WIN32_IE 0x0700        // Change this to the appropriate value to target other versions of IE.
#endif


//////////
// Aug.11.2014 -- Added to track down functions that were slowing down the system
//#define _VJR_LOG_ALL
//////
	#ifdef _VJR_LOG_ALL
		#define logfunc(x)		iVjr_appendSystemLog((s8*)x)
	#else
		#define logfunc(x)
	#endif

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
//#include <Shobjidl.h>
#include "resource.h"


//////////
// See: https://vld.codeplex.com/
// Install to:  c:\program files\visual leak detector\
// Un-comment this line to find memory leaks
// BEGIN
//////
	//#include "vld.h"	// Visual (memory) Leak Detector
//////
// END
//////////


//////////
// For debugging, the splash screen gets in the way if you're doing debugging
// on a single monitor machine (like a notebook) during the initial startup.
// You can set this property to false and prevent the splash screen from appearing.
//////
	bool glShowSplash = false;


#define _USE_MATH_DEFINES
#include <math.h>
#include "sound\SDL-1.2.15\include\sdl\SDL.h"
#include "sound\SDL-1.2.15\include\sdl\SDL_audio.h"

#include "vjr_const.h"
#include "\libsf\utils\common\cpp\builder.cpp"
#include "\libsf\utils\common\cpp\ll.cpp"
#include "vjr_structs0.h"

#include "compiler_const.h"
#include "compiler_structs.h"
#include "compiler_defs.h"
#include "compiler_globals.h"

#include "vjr_structs.h"
#include "vjr_defs.h"
#include "vjr_globals.h"

#include "command_defs.h"
#include "sound\sound.h"
#include "edit_chain_manager.h"
#include "edit_chain.h"
#include "engine.h"
#include "object_accessors.h"
#include "graphics\bitmaps.h"

#include "vjr_sup.cpp"
#include "objects.cpp"
#include "object_accessors.cpp"
#include "callbacks.cpp"
#include "events.cpp"
#include "bitmaps.cpp"
#include "compiler.cpp"
#include "commands.cpp"
#include "engine.cpp"
#include "edit_chain_manager.cpp"
#include "edit_chain.cpp"
#include "sound\sound.cpp"
