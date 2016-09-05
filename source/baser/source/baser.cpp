//////////
//
// /libsf/source/baser/source/baser.cpp
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
//     Aug.31.2016
//////
// Change log:
//     Aug.31.2016 - Initial creation
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
//
// Baser is a utility for displaying file content in a base.
// By default it displays in hexadecimal.
//
//////




//////////
// Uses Visual FreePro, Jr's existing facilities to simplify our processing
//////
	#define _NONVJR_COMPILE		// Turns off some features in VJr that fail on compilation from here
	#define _BMP_LOCALITY 1		// Force definitions to be local
	#include "\libsf\source\vjr\source\vjr.h"
	#undef main

	// Supporting algorithms
	#include "baser.h"




//////////
//
// Top level entry point
//
//////
	BOOL WINAPI DllMain(HANDLE hDllHandle, DWORD dwReason, LPVOID lpReserved)
	{
		switch (dwReason)
		{
			case DLL_PROCESS_ATTACH:
				iBaser_initialize();
				break;
			
			case DLL_PROCESS_DETACH:
				break;

			case DLL_THREAD_ATTACH:
				break;

			case DLL_THREAD_DETACH:
				break;
		}

		// Indicate success
		return(TRUE);
	}




//////////
//
// DLL functions
//
//////
	// Load a file into memory
	int baser_load(s8 tcFilename)
	{
		return(-1);
	}




//////////
//
// Release a previously loaded file
//
//////
	int baser_release(int tnHandle)
	{
		return(-1);
	}




//////////
//
// Populate the indicated row in the indicated base
//
//////
	int baser_populate_row(int tnHandle, int tnOffset, int tnBase, s8* tcBufferOut, int tnBufferOut_length)
	{
		return(-1);
	}




//////////
//
// Parses the indicated block using the indicated structure to produce appropriately formatted output
//
//////
	// Note:  This processing spawns a thread which parses in the background, and notifies the tnHwnd when completed
	// Note:  It may result in a data set that is abandoned as it may spin off many threads
	int baser_parse_block_by_struct(int tnHandle, HWND tnHwnd, int tnOffset, cs8* cStruct, int nStructLength)
	{
		return(-1);
	}




//////////
//
// Called to retrieve a message that's been prepared for the display
//
//////
	int baser_retrieve_data(int nId, s8* cDataOut, int tnDataLength)
	{
		// Search for the message

		// Retrieve message

		// Indicate result
		return(-1);
	}
