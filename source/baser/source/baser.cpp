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
	s32 baser_load(s8* tcFilename)
	{
		s8*				lcPathname;
		s8				pathname[_MAX_PATH];
		union {
			int			_bsr;
			SBaser*		bsr;
		};


		// Make sure the environment is sane
		if (tcFilename)
		{
			// Sanitize the name
			lcPathname = iiBaser_getFullPathName(tcFilename, pathname);

			// Is the file already open?s
			if ((bsr = iBaser_findBy_fullPathname(lcPathname)))
				return(_bsr);	// Already found

			// Try to open the file shared
			bsr = iiBaser_allocate();
			if (bsr)
			{
				// Copy the pathname
				bsr->isUsed			= true;
				bsr->filenameLength	= strlen(pathname);
				memcpy(bsr->filename, pathname, sizeof(pathname));

				// Initialize
				bsr->handle			= iDisk_openShared(lcPathname, _O_RDWR | _O_BINARY, false);
				bsr->loadAddress	= -1;
				// Success
			}

			// Return the handle
			return(_bsr);

		} else {
			// Invalid parameters
			return(-1);
		}
	}




//////////
//
// Release a previously loaded file
//
//////
	// 0=success
	s32 baser_release(int tnHandle)
	{
		union {
			int			_bsr;
			SBaser*		bsr;
		};


		// Locate 
		if ((bsr = iBaser_findBy_handle(tnHandle)))
		{
			// Close
			bsr->isUsed = false;
			memset(bsr->filename, 0, sizeof(bsr->filename));
			memset(bsr->data_u8, 0, sizeof(bsr->data_u8));
			iDisk_close(bsr->handle);

			// Indicate success
			return(0);
		}

		// Not found
		return(-1);
	}




//////////
//
// Populate the indicated row in the indicated base
//
//////
	s32 baser_populate_row(int tnHandle, int tnOffset, int tnBase, s8* tcBufferOut, int tnBufferOut_length)
	{
		s32				lnI;
		u32				lnOffset;
		s8				buffer[64];
		union {
			int			_bsr;
			SBaser*		bsr;
		};
		bool			error;
		u32				errorNum;


		// Locate 
		if ((bsr = iBaser_findBy_handle(tnHandle)))
		{
			// Make sure our base is valid
			tnBase = min(max(tnBase, 2), 36);

			// Are we within our block range?
			if (!between(tnOffset, bsr->loadAddress, bsr->loadAddress + bsr->length - (tnBufferOut_length / 3)))
			{
				// Read the nearest 512-byte block into memory
				lnOffset	= tnOffset & ~0x1ff;
				bsr->length	= iDisk_read(bsr->handle, lnOffset, &bsr->data_s8, 512, &error, &errorNum);
				if (error)
				{
					// Failure reading disk
					for (lnI = 0; lnI < tnBufferOut_length; lnI += 3)
					{
						// Populate with "?? " repeatedly
						tcBufferOut[lnI+0] = '?';
						tcBufferOut[lnI+1] = '?';
						tcBufferOut[lnI+2] = ' ';
					}

					// Indicate nothing was processed
					return(0);
				}
			}

			// Populate the line
			for (lnI = 0, lnOffset = 0; lnI < tnBufferOut_length; lnI += 3, lnOffset++)
			{
				// Populate with data or a placeholder
				if (lnI < bsr->length)
				{
					// Data
					_itoa((int)bsr->data_u8[lnI], buffer, tnBase);
					sprintf(bsr->data_s8 + lnOffset, "%2s ", buffer);

				} else {
					// Placeholder ".. " repeatedly
					bsr->data_s8[lnI+0] = '.';
					bsr->data_s8[lnI+1] = '.';
					bsr->data_s8[lnI+2] = ' ';
					bsr->data_s8[lnI+4] = 0;
				}
			}

			// Indicate how many were written
			return(lnOffset);

		} else {
			// Failure
			return(-1);
		}
	}




//////////
//
// Parses the indicated block using the indicated structure to produce appropriately formatted output
//
//////
	// Note:  This processing spawns a thread which parses in the background, and notifies the tnHwnd when completed
	// Note:  It may result in a data set that is abandoned as it may spin off many threads
	s32 baser_parse_block_by_struct(int tnHandle, HWND tnHwnd, int tnOffset, cs8* cStruct, int nStructLength)
	{
		// Copy the content

		// Spawn the thread
	}




//////////
//
// Called to retrieve a message that's been prepared for the display
//
//////
	s32 baser_retrieve_data(int nId, s8* cDataOut, int tnDataLength)
	{
		// Search for the message

		// Retrieve message

		// Indicate result
		return(-1);
	}
