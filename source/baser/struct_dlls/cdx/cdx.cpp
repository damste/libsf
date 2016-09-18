//////////
//
// /libsf/source/baser/dll_structs/cdx/cdx.cpp
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
//     Sep.10.2016
//////
// Change log:
//     Sep.10.2016 - Initial creation
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
//
// Thank you.  And may The Lord bless you richly as you lift up your life, your
// talents, your gifts, your praise, unto Him.  In Jesus' name I pray.  Amen.
//
//////




#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

// Use VJr processing engine
#define _NONVJR_COMPILE		// Turns off some features in VJr that fail on compilation from here
#define _BMP_LOCALITY 1		// Force definitions to be local
#include "\libsf\source\vjr\source\vjr.h"

// Baser includes
#include "\libsf\source\baser\source\baser_structs.h"




//////////
//
// DLL entry point
//
//////
	BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
	{
		switch (ul_reason_for_call)
		{
			case DLL_PROCESS_ATTACH:
			case DLL_THREAD_ATTACH:
			case DLL_THREAD_DETACH:
				break;
			case DLL_PROCESS_DETACH:
				// Initialize VJr's internal engine
				iVjr_init_minimal();
				break;
		}
		return TRUE;
	}




//////////
//
// Decode the indicated data block
//
//////
	s32 cdx_decode_keyfor(s32 tnFileOffset, SBuilder* output, SElement* el, SStructDllCallbacks* cb)
	{
		// Read the required block from disk

		// Translate

		iBuilder_appendData(output, "cdx_decode_keyfor() was reached\n", -1);

		// Indicate how many bytes were processed
		return(512);
	}
