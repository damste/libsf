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
	#define _WIN32_WINNT 0x0601
	#include "\libsf\source\vjr\source\vjr.h"
	#undef main

extern "C"
{
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
				DeleteCriticalSection(&cs_content_messages);
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
	s32 baser_release(s32 tnHandle)
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

		// Not found, or currently in use and cannot be released
		return(-1);
	}




//////////
//
// Populate the indicated row in the indicated base
//
//////
	s32 baser_populate_row(s32 tnHandle, s32 tnOffset, s32 tnBase, s8* tcBufferOut, s32 tnBufferOut_length)
	{
		s32				lnI, lnJ, lnOffset;
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
			if (!between(tnOffset, bsr->loadAddress, bsr->loadAddress + bsr->data.length - (tnBufferOut_length / 3)))
			{
				// Read the nearest 512-byte block into memory
				lnOffset			= tnOffset & ~0x1ff;
				bsr->data.data_s8	= &bsr->data_s8[0];
				bsr->data.length	= iDisk_read(bsr->handle, lnOffset, &bsr->data_s8, 512, &error, &errorNum);
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
			for (lnI = 0, lnOffset = 0; lnOffset < 16 && lnI < tnBufferOut_length; lnOffset++)
			{
				// Populate with data or a placeholder
				if (lnI < bsr->data.length)
				{
					// Translate into the base
					_itoa((int)bsr->data_u8[tnOffset + lnOffset], buffer, tnBase);

					// Store
					if (lnI != 0 && (lnOffset + 1) % 4 == 0)		sprintf(tcBufferOut + lnI, "%2s  ", buffer);
					else											sprintf(tcBufferOut + lnI, "%2s ", buffer);

					// Prefix with 0s as needed
					for (lnJ = lnI; lnJ < lnI + 2 && tcBufferOut[lnJ] == 32; lnJ++)
						tcBufferOut[lnJ] = '0';

					// Increase
					if (lnI != 0 && (lnOffset + 1) % 4== 0)			lnI += 4;
					else											lnI += 3;

				} else {
					// Placeholder ".. " repeatedly
					tcBufferOut[lnI+0] = '.';
					tcBufferOut[lnI+1] = '.';
					tcBufferOut[lnI+2] = ' ';
					if (lnI != 0 && lnI % 4 == 0)
					{
						tcBufferOut[lnI+3] = ' ';
						tcBufferOut[lnI+4] = 0;
						lnI += 4;

					} else {
						tcBufferOut[lnI+3] = 0;
						lnI += 3;
					}
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
	s32 baser_parse_block_by_struct(s32 tnHandle, HWND tnHwndCallback, s32 tnOffset, cs8* cStruct, s32 nStructLength)
	{
		DWORD				lnThreadId;
		SBaser*				bsr;
		union {
			s32				_bm;
			SBaserMsg*		bm;
		};


		// Make sure our environment is sane
		bm = NULL;
		if (cStruct && nStructLength > 0 && (bsr = iBaser_findBy_handle(tnHandle)))
		{
			// Allocate a message
			bm = (SBaserMsg*)malloc(sizeof(SBaserMsg));
			if (bm)
			{
				// Initialize
				memset(bm, 0, sizeof(SBaserMsg));

				// Allocate
				iDatum_duplicate(&bm->message, cStruct, nStructLength);
				if (bm->message.data_s8)
				{
					// Copy
					memcpy(&bm->data, &bsr->data, sizeof(&bm->data));
					memcpy(&bm->bsr, bsr, sizeof(bm->bsr));
					bm->hwndCallback = tnHwndCallback;

					// Spawn the thread
					CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&iiBaser_parse_block_by_struct__threadProc, bm, NULL, &lnThreadId);

				} else {
					// Failure
					free(bm);
					bm = NULL;
				}
			}
		}

		// Indicate our result
		return(_bm);
	}




//////////
//
// Called to retrieve a message that's been prepared for the display
//
//////
	s32 baser_retrieve_data(s32 nId, s8* tcDataOut, s32 tnDataOutLength)
	{
		s32			lnContentLength;
		union {
			s32				_bc_s32;
			uptr			_bc_uptr;
			SBaserContent*	bc;
		};


		//////////
		// Lock
		//////
			EnterCriticalSection(&cs_content_messages);


		//////////
		// Search for the message
		//////
			_bc_s32 = nId;
			if (iBuilder_isPointer(gsBaserMessagesRoot, _bc_uptr, (void**)&bc) && bc->isUsed && (lnContentLength = bc->content->populatedLength))
			{
				// If we have data to copy, prepare to do so
				if (tcDataOut && tnDataOutLength > 0)
				{
					// Retrieve as much of the message as will fit
					memcpy(tcDataOut, bc->content->data_s8, min(tnDataOutLength, lnContentLength));

					// Delete the message if need be
					if (tnDataOutLength >= lnContentLength)
					{
						// If it's shorter than allocated space, pad with spaces
						if (tnDataOutLength > lnContentLength)
							memset(tcDataOut + lnContentLength, 32, tnDataOutLength - lnContentLength);	// Pad with spaces

						// No longer used
						bc->isUsed = false;

						// Release the content
						iBuilder_freeAndRelease(&bc->content);
					}
				}

			} else {
				// If we get here, not found
				lnContentLength = -1;
			}


		//////////
		// Unlock
		//////
			LeaveCriticalSection(&cs_content_messages);


		//////////
		// Indicate how long it actually is
		//////
			return(lnContentLength);
	}




	//////////
	//
	// Called to render the indicated html content as html over the top of the indicated hwnd,
	// which will cause it to subclass the wndproc() function and intercept WM_PAINT messages.
	//
	// Sending to a NULL htmlContent or a zero htmlContentLength
	//
	//////
		s32 baser_render_html(HWND hwnd, s32 left, s32 top, s32 right, s32 bottom, s8* tcHtmlContent, s32 tnHtmlContentLength)
		{
			SBaserHwnd*	bwin;


			// Make sure our environment is sane
			if (hwnd && IsWindow(hwnd))
			{

				//////////
				// Lock
				//////
					EnterCriticalSection(&cs_baser_hwnd);


					//////////
					// Setup
					//////
						// Make sure we have a builder
						if (!gsBaserWindowsRoot)
							iBuilder_createAndInitialize(&gsBaserWindowsRoot, sizeof(SBaserHwnd) * 10);

						// Try to find the window
						bwin = ((hwnd) ? iBaserHwnd_findBy_hwnd(hwnd) : NULL);


					//////////
					// Disconnecting?
					//////
						if (!tcHtmlContent)
						{
							// No content, un-subclass
							if (bwin && bwin->old_wndproc)
								SetWindowLong(hwnd, GWL_WNDPROC, bwin->old_wndproc);

							// Delete this item
							iBaserHwnd_delete(bwin);

							// All done
							return(0);
						}


					//////////
					// Grab the window
					//////
						if (bwin)
						{
							// Delete the existing sem
							iSEM_delete(&bwin->sem, true);

						} else {
							// Create a new bwin
							bwin = (SBaserHwnd*)iBuilder_allocateBytes(gsBaserWindowsRoot, sizeof(SBaserHwnd));
							if (!bwin)
								return(-1);

							// Create the render object (just use a shape
							bwin->obj = iObj_create(_OBJ_TYPE_SHAPE, NULL);
							if (!bwin->obj)
								return(-1);
						}


					//////////
					// Setup
					//////
						bwin->isUsed		= true;
						bwin->hwnd			= hwnd;
						bwin->rc.left		= left;
						bwin->rc.top		= top;
						bwin->rc.right		= right;
						bwin->rc.bottom		= bottom;

						// If it hasn't yet been sub-classed, subclass it
						if (!bwin->old_wndproc)
						{
							// Save
							bwin->old_wndproc = GetWindowLong(hwnd, GWL_WNDPROC);

							// Set
							SetWindowLong(hwnd, GWL_WNDPROC, (LONG)&iBaserHwnd_wndProc);
						}

						// Set it to the target size
						iObj_setSize(bwin->obj, left, top, right - left, bottom - top);


					//////////
					// Load the html source code and render
					//////



				//////////
				// Unlock
				//////
					LeaveCriticalSection(&cs_baser_hwnd);

			}
		}




//////////
//
// Called to create a file that has a temporary lifespan, meaning it's auto-deleted upon process exit
//
//////
	s32 baser_create_htmltemp_file_content(s8* tcHtmlPathOut270, s8* tcFilenamePrefix, s8* tcContent, s32 tnContentLength)
	{
		static u32	snTempFilenameUniqueId = 1;

		s32			lnFile;
		s8			buffer[_MAX_PATH];
		bool		error;
		u32			errorNum;


		// Construct a temporary filename
		memset(tcHtmlPathOut270, 32, 270);
		GetTempFileName((GetTempPath(_MAX_PATH, buffer), buffer), tcFilenamePrefix, snTempFilenameUniqueId++, tcHtmlPathOut270);

		// Create the file
		if ((lnFile = iDisk_openExclusive(tcHtmlPathOut270, _O_RDWR | _O_BINARY | _O_CREAT | _O_TEMPORARY, true, &error, &errorNum)) > 0)
		{
			// Write out the content
			iDisk_write(lnFile, 0, tcContent, tnContentLength, &error, &errorNum);

			// Make sure it's written to disk
			iDisk_commit(lnFile, &error, &errorNum);

			// Close the file
			iDisk_close(lnFile);

			// Indicate success
			return(0);

		} else {
			// Failure
			return(-1);
		}
	}


};	// extern "C"

