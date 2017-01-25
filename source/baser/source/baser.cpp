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

	#include "baser.h"

extern "C"
{
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
						else											sprintf(tcBufferOut + lnI, "%2s ",  buffer);

						// Prefix as needed
						if (bsr->data_u8[tnOffset + lnOffset] == 0)
						{
							// With dots
							for (lnJ = lnI; lnJ < lnI + 2; lnJ++)
								tcBufferOut[lnJ] = '.';

						} else {
							// with 0s
							for (lnJ = lnI; lnJ < lnI + 2 && tcBufferOut[lnJ] == 32; lnJ++)
								tcBufferOut[lnJ] = '0';
						}

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
			SObject*	goReuseForm		= NULL;
			SBitmap		bmpBaserIcon	= NULL;

			#include "graphics\bitmaps.h"

			s32 baser_render_html(s8* tcHtmlContent, s32 tnHtmlContentLength)
			{
				SDatum		html;
				SObject*	loForm;


				// Make sure our environment is sane
				if (tcHtmlContent && tnHtmlContentLength)
				{
					// Lock
					EnterCriticalSection(&cs_baser_hwnd);

					// If we're re-using an existing window
					if (goReuseForm)
					{
						// Grab the reuse form
						loForm = goReuseForm;

					} else {
						// Create a new form
						loForm = iObj_create(_OBJ_TYPE_FORM, NULL);
						if (!loForm)
							return;

						// Baser
						if (!bmpBaserIcon)
							bmpJDebiIcon = iBmp_rawLoad(cgc_baserAppIconBmp);

						// Set basic properties
						propSetPictureBmp(_jdebi, bmpBaserIcon);
						propSetBorderStyle(_jdebi, _BORDER_STYLE_FIXED);

						// Add the editbox
// TODO:  working here
					}


// TODO:  working here
					//////////
					// Create the html
					//////
						html.data	= tcHtmlContent;
						html.length	= tnHtmlContentLength;
						if (!iSEM_load_fromMemory(NULL, sem, &html, false, false))
						{
							// Allocate
							iSEM_delete(&sem, true);

							// Indicate failure
							return(-1);
						}


					// Present the window
					propSetVisible(loForm, true);

					// Unlock
					LeaveCriticalSection(&cs_baser_hwnd);
				}

				// If we get here, invalid window
				return(-1);
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




//////////
//
// Initialize baser
//
//////
	void iBaser_initialize(void)
	{
		// Initialize VJr's internal engine
		iVjr_init_minimal();

		// Create our critical sections
		InitializeCriticalSection(&cs_content_messages);
		InitializeCriticalSection(&cs_baser_hwnd);

		// Allocate our baser info
		iBuilder_createAndInitialize(&gsBaserRoot, sizeof(SBaser) * 20);
	}




//////////
//
// Allocate the indicated baser
//
//////
	SBaser* iiBaser_allocate(void)
	{
		return((SBaser*)iBuilder_allocateBytes(gsBaserRoot, sizeof(SBaser)));
	}




//////////
//
// Called to sanitize the filename, and retrieves a pointer to &full_pathname[0]
//
//////
	s8* iiBaser_getFullPathName(s8* tcFilename, s8 full_pathname[_MAX_PATH])
	{
		// Convert through Windows
		memset(full_pathname, 0, sizeof(full_pathname));
		GetFullPathName(tcFilename, _MAX_PATH, full_pathname, NULL);

		// Indicate our result
		return(&full_pathname[0]);
	}




//////////
//
// Search for the indicated filename
//
//////
	SBaser* iBaser_findBy_fullPathname(s8* tcPathname)
	{
		s32			lnLength;
		u32			lnI;
		SBaser*		bsr;


		// Search top-down
		if (gsBaserRoot && tcPathname)
		{
			// Grab the pathname length
			lnLength = strlen(tcPathname);

			// Iterate through every record
			iterate(lnI, gsBaserRoot, bsr, SBaser)
			// Begin

				// Is this it?
				if (bsr->isUsed && lnLength == bsr->filenameLength && _memicmp(tcPathname, bsr->data_s8, lnLength) == 0)
					return(bsr);	// Yes

			// End
			iterate_end;
		}

		// If we get here, not found or invalid
		return(NULL);
	}




//////////
//
// Called to locate the baser by its handle (which is its memory address)
//
//////
	SBaser* iBaser_findBy_handle(s32 tnHandle)
	{
		SBaser*		bsr;
		union {
			s32		lnHandle_s32;
			u32		lnHandle_u32;
		};


		// See if it's a valid pointer
		lnHandle_s32 = tnHandle;
		if (iBuilder_isPointer(gsBaserRoot, lnHandle_u32, (void**)&bsr) && bsr->isUsed)
			return(bsr);

		// If we get here, not valid, or valid and not used
		return(NULL);
	}




//////////
//
// Called to find the indicated SBaserHwnd by hwnd
//
//////
	// Note:  This algorithm only finds existing hwnds, if not found it does not auto-create it
	SBaserHwnd* iBaserHwnd_findActiveWindow(HWND hwnd)
	{
		u32				lnI;
		SBaserHwnd*		bwin;
		SBaserHwnd*		bwinFound;


		//////////
		// Lock
		//////
			EnterCriticalSection(&cs_baser_hwnd);


			//////////
			// Search for it
			//////
				bwinFound = NULL;
				iterate(lnI, gsBaserWindowsRoot, bwin, SBaserHwnd)
				// Begin

					// Is this our entry?
					if (bwin->isUsed && bwin->hwnd == hwnd)
					{
						// Yes
						bwinFound = bwin;
						break;
					}

				// End
				iterate_end;


		//////////
		// Unlock
		//////
			LeaveCriticalSection(&cs_baser_hwnd);


		//////////
		// Indicate the status
		//////
			return(bwinFound);

	}




//////////
//
// Called to parse and process the indicated structure, using the indicated data block
//
//////
	DWORD iiBaser_parse_block_by_struct__threadProc(LPVOID param)
	{
		bool		llPointer;
		s32			lnOffset, lnCount, lnElType, lnSize, lnFpLength, lnFpDecimals;
		u32			lnI, lnJ;
		SDatum		name, type;
		SBaserMsg*	bm;
		SComp*		comp;
		SComp*		compNext;
		SComp*		compLeftBracket;
		SComp*		compRightBracket;
		SStructDll*	dll;
		SLine*		line;
		SEM*		sem;
		SStruct*	str;
		SElement*	el;
		SBuilder*	structs;	// Parsed struct data into the various structs contained within
		SBuilder*	output;		// Generated report output


		// Retrieve our parameter rightly
		bm = (SBaserMsg*)param;

		// Parse the structure
		if (iSEM_load_fromMemory(NULL, (sem = iSEM_allocate(true)), &bm->message, true, false, &cgcBaserKeywords[0]))
		{
			// Initialize our builder
			structs = NULL;
			output	= NULL;
			iBuilder_createAndInitialize(&structs, sizeof(SStruct) * 10);
			iBuilder_createAndInitialize(&output);

			// Initialize our defaults
			lnFpLength		= -1;
			lnFpDecimals	= -1;

			// Render the data based on the structure
			for (line = sem->firstLine, str = NULL, el = NULL, lnOffset = 0, dll = NULL; line; line = line->ll.nextLine)
			{
				// Does it have any content?
				if (line->compilerInfo && (comp = line->compilerInfo->firstComp))
				{
					// We skip leading pipe signs
					while (comp && comp->iCode == _ICODE_PIPE_SIGN)
						comp = iComps_getNth(comp);

					// Reset name and type
					memset(&name, 0, sizeof(name));
					memset(&type, 0, sizeof(type));

continue_to_next_comp:
					// What type is it?
					switch (comp->iCode)
					{
						case _ICODE_S8:		{	lnElType = _BASER_ELTYPE_S8;		lnSize = 1;			goto valid_type;	}
						case _ICODE_S16:	{	lnElType = _BASER_ELTYPE_S16;		lnSize = 2;			goto valid_type;	}
						case _ICODE_S32:	{	lnElType = _BASER_ELTYPE_S32;		lnSize = 4;			goto valid_type;	}
						case _ICODE_S64:	{	lnElType = _BASER_ELTYPE_S64;		lnSize = 8;			goto valid_type;	}
						case _ICODE_F32:	{	lnElType = _BASER_ELTYPE_F32;		lnSize = 4;			goto valid_type;	}
						case _ICODE_F64:	{	lnElType = _BASER_ELTYPE_F64;		lnSize = 8;			goto valid_type;	}
						case _ICODE_U8:		{	lnElType = _BASER_ELTYPE_U8;		lnSize = 1;			goto valid_type;	}
						case _ICODE_U16:	{	lnElType = _BASER_ELTYPE_U16;		lnSize = 2;			goto valid_type;	}
						case _ICODE_U32:	{	lnElType = _BASER_ELTYPE_U32;		lnSize = 4;			goto valid_type;	}
						case _ICODE_U64:
							lnElType	= _BASER_ELTYPE_U64;
							lnSize		= 8 * lnCount;
valid_type:
//////////
//
// Syntax should be:	type name[count];
//
//		type is required
//		name is optional
//		[count] is optional
//		Use + for 64-bit pointer
//		Use * for 32-bit pointer
//		Use @ for 16-bit pointer
//
//////
							// See if it's a pointer
							compNext = iComps_getNth(comp);
							llPointer = (compNext && (compNext->iCode == _ICODE_PLUS || compNext->iCode == _ICODE_ASTERISK || compNext->iCode == _ICODE_AT_SIGN));
							if (llPointer)
							{
								// Update the size
								lnSize = ((compNext->iCode == _ICODE_ASTERISK) ? 4 : ((compNext->iCode == _ICODE_PLUS) ? 8 : 2));	// Pointer size is based on pointer type

								// Grab the real next thing
								compNext = iComps_getNth(comp);
							}

							// Initially assume no name
							name.data_s8	= NULL;
							name.length		= 0;

							// Grab the name component (if any)
							if (compNext)
								iiBaser_populateDatum_byComp(compNext, &name);		// Grab the name

							// Search for [Nn] for a repeat count
							lnCount = 1;
							if ((compLeftBracket = iComps_findNextBy_iCode(comp, _ICODE_BRACKET_LEFT)))
							{
								// We have [
								compNext = iComps_getNth(compLeftBracket, 1);
								if (compNext->iCode == _ICODE_NUMERIC && (compRightBracket = iComps_getNth(compNext, 1)) && compRightBracket->iCode == _ICODE_BRACKET_RIGHT)
									lnCount = max(iComps_getAs_s32(compNext), 1);	// We have [Nn], we have a repeat count
							}

							// Physically dispatch
							iiBaser_parse_block_by_struct__threadProc__appendElement(structs, &str, &el, &name, &type, lnElType, lnSize * lnCount, &lnOffset, dll, lnFpLength, lnFpDecimals, llPointer);
							break;

						case _ICODE_ALPHA:
						case _ICODE_ALPHANUMERIC:
							// This should be a type name which is like s32, s8, etc., but uses a custom type that decodes from within a dll function rather than internally
							iiBaser_populateDatum_byComp(comp, &type);
							lnElType	= _BASER_ELTYPE_TYPE;
							lnSize		= 0;
							goto valid_type;

						case _ICODE_NUMERIC:
							// They're specifying a hard offset
							// Syntax should be Nnn:
							compNext = iComps_getNth(comp);
							if (compNext && compNext->iCode == _ICODE_COLON)
							{
								// Set this as the offset
								lnOffset = iComps_getAs_s32(comp);

								// If there are additional components on this line, continue parsing where we are
								if (compNext->ll.nextComp)
								{
									// Grab the next and continue processing
									comp = iComps_getNth(compNext);
									goto continue_to_next_comp;
								}
							}
							break;

						case _ICODE_BASER_FP:
							// They're specifying a floating point length
							// Syntax should be fp length,decimals
							compNext = iComps_getNth(comp);
							if (compNext && compNext->iCode == _ICODE_NUMERIC)
							{
								// Set this as the length
								lnFpLength = iComps_getAs_s32(compNext);

								// If there are additional components on this line, continue parsing where we are
								if ((compNext = iComps_getNth(compNext)) && compNext->iCode == _ICODE_COMMA && (compNext = iComps_getNth(compNext)) && comp->iCode == _ICODE_NUMERIC)
								{
									// Grab the next and continue processing
									lnFpDecimals = iComps_getAs_s32(compNext);
								}
							}
							break;

						case _ICODE_BASER_STRUCT:
							// Syntax should be:	struct name
							if ((compNext = iComps_getNth(comp, 1)) && (compNext->iCode == _ICODE_ALPHA || compNext->iCode == _ICODE_ALPHANUMERIC))
							{
								// Create a new structure
								str = (SStruct*)iBuilder_allocateBytes(structs, sizeof(SStruct));
								if (!str)
									goto quit;	// Should never happen

								// Set its name
								iDatum_duplicate(&str->name, compNext->line->sourceCode->data_s8, compNext->line->sourceCode->length);
							}
							break;

						case _ICODE_BASER_DLL:
							// Syntax should be:	dll x:\path\to\whatever.dll
							// Grab the name component (if any)
							compNext = iComps_getNth(comp);
							if (compNext)
							{
								// Grab the name
								iiBaser_populateDatum_byComp(compNext, &name);

								// Create the entry
								iiBaser_parse_block_by_struct__threadProc__appendDll(structs, &str, &el, &name, &dll);
							}
							break;

						case _ICODE_BASER_FUNC:
							// Syntax should be:	func funcName type typeName
							// Grab the name component (if any)
							compNext = iComps_getNth(comp);
							if (compNext)
							{
								// Grab the name
								iiBaser_populateDatum_byComp(compNext, &name);

								// After this should be the keyword type
								compNext = iComps_getNth(compNext);
								if (compNext->iCode == _ICODE_BASER_TYPE && (compNext = iComps_getNth(compNext)))
								{
									// Grab the type
									iiBaser_populateDatum_byComp(compNext, &type);

									// Create the entry
									iiBaser_parse_block_by_struct__threadProc__appendFunc(structs, &str, &el, &name, &type, dll);
								}
							}
							break;

						default:
							// Skip the line
							break;
					}
				}
			}

			// Process the data
			lnOffset = 0;
			iterate(lnI, structs, str, SStruct)
			// Begin

				// See if the elements are known to us
				if (str->elements)
				{
					iterate(lnJ, str->elements, el, SElement)
					// Begin

						switch (el->elType)
						{
							case _BASER_ELTYPE_S8:
								iiBaser_append_s8(output, el, *(s8*)&bm->data.data_s8[lnOffset]);
								lnOffset += el->length;
								break;
							case _BASER_ELTYPE_S16:
								iiBaser_append_s16(output, el, *(s16*)&bm->data.data_s8[lnOffset]);
								lnOffset += el->length;
								break;
							case _BASER_ELTYPE_S32:
								iiBaser_append_s32(output, el, *(s32*)&bm->data.data_s8[lnOffset]);
								lnOffset += el->length;
								break;
							case _BASER_ELTYPE_S64:
								iiBaser_append_s64(output, el, *(s64*)&bm->data.data_s8[lnOffset]);
								lnOffset += el->length;
								break;
							case _BASER_ELTYPE_F32:
								iiBaser_append_f32(output, el, *(f32*)&bm->data.data_s8[lnOffset]);
								lnOffset += el->length;
								break;
							case _BASER_ELTYPE_F64:
								iiBaser_append_f64(output, el, *(f64*)&bm->data.data_s8[lnOffset]);
								lnOffset += el->length;
								break;
							case _BASER_ELTYPE_U8:
								iiBaser_append_u8(output, el, *(u8*)&bm->data.data_s8[lnOffset]);
								lnOffset += el->length;
								break;
							case _BASER_ELTYPE_U16:
								iiBaser_append_u16(output, el, *(u16*)&bm->data.data_s8[lnOffset]);
								lnOffset += el->length;
								break;
							case _BASER_ELTYPE_U32:
								iiBaser_append_u32(output, el, *(u32*)&bm->data.data_s8[lnOffset]);
								lnOffset += el->length;
								break;
							case _BASER_ELTYPE_U64:
								iiBaser_append_u64(output, el, *(u64*)&bm->data.data_s8[lnOffset]);
								lnOffset += el->length;
								break;
							case _BASER_ELTYPE_TYPE:
								lnOffset += iiBaser_append_type(output, el, structs, bm->bsr.loadAddress + lnOffset);
								break;
							// default:  ignore it
						}

					// End
					iterate_end;
				}

			// End
			iterate_end;

			// Is there a constructed message?
			if (output->populatedLength > 0)
			{
				// Send back completed message
				iiBaser_dispatch_contentMessage(bm->hwndCallback, output);
				// Note:  The output builder is moved into the dispatched content message.
				// Note:  It is later deleted on full retrieval.

			} else {
				// No message, but release the output
				iBuilder_freeAndRelease(&output);
			}
			output = NULL;

			// Clean house
			iBaser_deleteStructs(&structs);
			iSEM_delete(&sem, true);
		}

quit:
		// Release the memory blocks
		iDatum_delete(&bm->message, false);
		free(bm);

		// Complete
		TerminateThread(GetCurrentThread(), 0);
		return(0);
	}

	// Appends an element to display (or ignore if it doesn't have a name)
	void iiBaser_parse_block_by_struct__threadProc__appendElement(SBuilder* builder, SStruct** strRoot, SElement** elRoot, SDatum* name, SDatum* dllFuncType, u32 elType, s32 tnSize, s32* tnOffset, SStructDll* currentDll, s32 lnFpLength, s32 lnFpDecimals, bool tlPointer)
	{
		SElement*	el;
		SStruct*	str;


		//////////
		// Make sure we have a struct
		//////
			if (!*strRoot)
			{
				// Create a default one
				str = (SStruct*)iBuilder_allocateBytes(builder, sizeof(SStruct));
				if (!str)
					return;		// Should never happen

				// Give it a default name
				iDatum_duplicate(&str->name, cgc_baser_data, sizeof(cgc_baser_data) - 1);

				// Update the root
				*strRoot = str;

			} else {
				// Grab the struct
				str = *strRoot;
			}

			// Make sure we have an element builder
			if (!str->elements)
				iBuilder_createAndInitialize(&str->elements, sizeof(SElement) * 20);


		//////////
		// Add this element
		//////
			el = (SElement*)iBuilder_allocateBytes(str->elements, sizeof(SElement));
			if (!el)
				return;		// Should never happen

			el->elType		= elType;
			el->offset		= *tnOffset;
			el->length		= tnSize;
			el->isPointer	= tlPointer;

			// Copy the name or create a pseudo name
			if (name && name->_data && name->length > 0)		iDatum_duplicate(&el->name, name);
			else												iDatum_duplicate(&el->name, cgc_baser_data, sizeof(cgc_baser_data) - 1);

			// Copy the type if present
			if (dllFuncType && dllFuncType->_data && dllFuncType->length > 0)
				iDatum_duplicate(&el->type.dllFuncType, dllFuncType);


		//////////
		// If it's floating point, indicate the size
		//////
			if (elType == _BASER_ELTYPE_F32)
			{
				el->fpLength	= ((lnFpLength		< 2) ? 8 : lnFpLength);
				el->fpDecimals	= ((lnFpDecimals	< 0) ? 2 : lnFpDecimals);

			} else if (elType == _BASER_ELTYPE_F64) {
				el->fpLength	= ((lnFpLength		< 2) ? 15 : lnFpLength);
				el->fpDecimals	= ((lnFpDecimals	< 0) ? 4  : lnFpDecimals);
			}


		//////////
		// Update return parameters
		//////
			*tnOffset		+= tnSize;
			*elRoot			= el;
	
	}

	// Appends a dll to use from this point forward
	void iiBaser_parse_block_by_struct__threadProc__appendDll(SBuilder* builder, SStruct** strRoot, SElement** elRoot, SDatum* name, SStructDll** currentDllRoot)
	{
		s32			lnOffset;
		s8			filename[_MAX_PATH];
		SElement*	el;


		// Add the element for the dll
		lnOffset = 0;
		iiBaser_parse_block_by_struct__threadProc__appendElement(builder, strRoot, elRoot, name, NULL, _BASER_ELTYPE_DLL, 0, &lnOffset, *currentDllRoot, -1, -1, false);
		el = *elRoot;

		// Get the full pathname
		GetFullPathName(name->data_s8, sizeof(filename), filename, NULL);

		// Try to open the DLL
		if ((el->dll.handle = LoadLibrary(filename)))
		{
			// Store the name
			iDatum_duplicate(&el->dll.pathname, filename, strlen(filename));

			// Store it
			*currentDllRoot = &el->dll;
		}
	}

	// Appends a function within the current dll
	void iiBaser_parse_block_by_struct__threadProc__appendFunc(SBuilder* builder, SStruct** strRoot, SElement** elRoot, SDatum* name, SDatum* type, SStructDll* currentDll)
	{
		s32			lnOffset;
		s8			funcname[_MAX_PATH];
		SElement*	el;


		// Add the element for the dll
		lnOffset = 0;
		iiBaser_parse_block_by_struct__threadProc__appendElement(builder, strRoot, elRoot, name, NULL, _BASER_ELTYPE_DLL_FUNC, 0, &lnOffset, currentDll, -1, -1, false);
		el = *elRoot;

		// Populate the rest
		memcpy(funcname, name->data_s8, name->length);
		funcname[name->length] = 0;
		el->dllFunc._func	= (uptr)GetProcAddress(currentDll->handle, funcname);
		el->dllFunc.dll		= currentDll;
		iDatum_duplicate(&el->dllFunc.name, name);
		iDatum_duplicate(&el->dllFunc.type, type);
	}

	void iiBaser_populateDatum_byComp(SComp* comp, SDatum* datum)
	{
		// Trim quotes if need be
		if (comp->iCode == _ICODE_SINGLE_QUOTED_TEXT || comp->iCode == _ICODE_DOUBLE_QUOTED_TEXT) {
			// It's quoted text
			datum->data_s8	= comp->line->sourceCode->data_s8 + comp->start + 1;
			datum->length	= comp->length - 2;

		} else {
			// It's a name
			datum->data_s8	= comp->line->sourceCode->data_s8 + comp->start;
			datum->length	= comp->length;
		}
	}

	void iBaser_deleteStructs(SBuilder** structsRoot)
	{
		u32			lnI, lnJ;
		SStruct*	str;
		SElement*	el;


		// Make sure there is a struct
		if (structsRoot && *structsRoot)
		{
			// Iterate through each struct
			iterate(lnI, *structsRoot, str, SStruct)
			// Begin

				// If there are any active elements
				if (str->elements)
				{
					// Iterate through each element
					iterate(lnJ, str->elements, el, SElement)
					// Begin

						// Always delete the name
						iDatum_delete(&el->name);

						// And based on the type we may delete more
						switch (el->elType)
						{
							// DLLs delete their pathname
							case _BASER_ELTYPE_DLL:
								iDatum_delete(&el->dll.pathname);
								if (el->dll.handle)		FreeLibrary(el->dll.handle);
								break;

							case _BASER_ELTYPE_DLL_FUNC:
								// DLL functions delete their function name and alias type
								iDatum_delete(&el->dllFunc.name);
								iDatum_delete(&el->dllFunc.type);
								break;
						}

					// End
					iterate_end;
				}

			// End
			iterate_end;

			// Delete the builder
			iBuilder_freeAndRelease(structsRoot);
		}
	}

	void iiBaser_append_s8  (SBuilder* output, SElement* elData, s8 data)
	{
		s8 buffer[1024];


		// 8-bit integer
		sprintf(buffer, "%s = %d\n", elData->name.data_s8, (s32)data);
		iBuilder_appendData(output, buffer, -1);
	}

	void iiBaser_append_s16 (SBuilder* output, SElement* elData, s16 data)
	{
		s8 buffer[1024];


		// 16-bit integer
		sprintf(buffer, "%s = %d\n", elData->name.data_s8, (s32)data);
		iBuilder_appendData(output, buffer, -1);
	}

	void iiBaser_append_s32 (SBuilder* output, SElement* elData, s32 data)
	{
		s8 buffer[1024];


		// 32-bit integer
		sprintf(buffer, "%s = %d\n", elData->name.data_s8, data);
		iBuilder_appendData(output, buffer, -1);
	}

	void iiBaser_append_s64 (SBuilder* output, SElement* elData, s64 data)
	{
		s8 buffer[1024];


		// 64-bit integer
		sprintf(buffer, "%s = %I64d\n", elData->name.data_s8, data);
		iBuilder_appendData(output, buffer, -1);
	}

	void iiBaser_append_f32 (SBuilder* output, SElement* elData, f32 data)
	{
		return(iiBaser_append_f64(output, elData, (f64)data));
	}

	void iiBaser_append_f64 (SBuilder* output, SElement* elData, f64 data)
	{
		s8 format[16];
		s8 buffer[1024];


		// 64-bit floating point
		// Build the format flag
		if (elData->fpDecimals > 0)			sprintf(format, "%%s = %%%d.%df\n", elData->fpLength, elData->fpDecimals);
		else								sprintf(format, "%%s = %%%d.0f\n",  elData->fpLength);

		// Store
		sprintf(buffer, format, elData->name.data_s8, data);
		iBuilder_appendData(output, buffer, -1);
	}

	void iiBaser_append_u8  (SBuilder* output, SElement* elData, u8 data)
	{
		s8 buffer[1024];


		// 8-bit unsigned integer
		sprintf(buffer, "%s = %u\n", elData->name.data_s8, (u32)data);
		iBuilder_appendData(output, buffer, -1);
	}

	void iiBaser_append_u16 (SBuilder* output, SElement* elData, u16 data)
	{
		s8 buffer[1024];


		// 16-bit unsigned integer
		sprintf(buffer, "%s = %u\n", elData->name.data_s8, (u32)data);
		iBuilder_appendData(output, buffer, -1);
	}

	void iiBaser_append_u32 (SBuilder* output, SElement* elData, u32 data)
	{
		s8 buffer[1024];


		// 32-bit unsigned integer
		sprintf(buffer, "%s = %u\n", elData->name.data_s8, data);
		iBuilder_appendData(output, buffer, -1);
	}

	void iiBaser_append_u64 (SBuilder* output, SElement* elData, u64 data)
	{
		s8 buffer[1024];


		// 64-bit unsigned integer
		sprintf(buffer, "%s = %I64u\n", elData->name.data_s8, data);
		iBuilder_appendData(output, buffer, -1);
	}

	s32 iiBaser_append_type(SBuilder* output, SElement* elData, SBuilder* structs, s32 tnFileOffset)
	{
		s32			lnLength;
		s64			lnOffset;
		u32			lnI, lnJ;
		SStruct*	str;
		SElement*	el;
		s8			buffer[1024];
		


		//////////
		// Search for the indicated DLL
		//////
			iterate(lnI, structs, str, SStruct)
			// Begin

				iterate(lnJ, str->elements, el, SElement)
				// Begin

					// Is this our DLL function?
					if (el->elType == _BASER_ELTYPE_DLL_FUNC && iDatum_compare(&el->dllFunc.type, &elData->type.dllFuncType) == 0)
					{
						// Dispatch... if the function exists
						if (el->dllFunc._func)
						{
							// Save file position
							lnOffset = iDisk_getFilePosition(elData->file);

							// Dispatch
							lnLength = el->dllFunc.func(tnFileOffset, output, elData, &gsBaserCallback);

							// Restore file position
							iDisk_setFilePosition(elData->file, tnFileOffset);

							// Success
							return(lnLength);
						}
					}

				// End
				iterate_end;

			// End
			iterate_end;


		//////////
		// If we get here, not found
		//////
			sprintf(buffer, "%s = unable to find dll function related to %s\n", elData->name.data_s8, elData->type.dllFuncType.data_s8);
			iBuilder_appendData(output, buffer, -1);


		//////////
		// We did not advance
		//////
			return(0);
	
	}

	// Note:  content is inserted into the message, so if it's deleted it will cause an access violation
	void iiBaser_dispatch_contentMessage(HWND hwnd, SBuilder* content)
	{
		u32			lnI;
		union {
			uptr			_bc;
			SBaserContent*	bc;
		};


		//////////
		// Lock
		//////
			EnterCriticalSection(&cs_content_messages);


			// Make sure we have a builder
			if (!gsBaserMessagesRoot)
				iBuilder_createAndInitialize(&gsBaserMessagesRoot, sizeof(SBaserContent) * 10);


			//////////
			// Locate an unused slot
			//////
				iterate(lnI, gsBaserMessagesRoot, bc, SBaserContent)
				// Begin

					if (!bc->isUsed)
						break;

				// End
				iterate_end;


			//////////
			// Allocate a new record if need be
			//////
				if (!bc || lnI >= gsBaserMessagesRoot->populatedLength)
					bc = builder_allocate(gsBaserMessagesRoot, SBaserContent);


			//////////
			// Populate the message
			//////
				bc->isUsed	= true;
				bc->content	= content;


		//////////
		// Unlock
		//////
			LeaveCriticalSection(&cs_content_messages);


		//////////
		// Physically dispatch the message
		//////
			SendMessage(hwnd, _WMBASER_CONTENT_IS_READY, _bc, content->populatedLength);

	}




//////////
//
// Called to delete the indicated baser hwnd
//
//////
	void iBaserHwnd_delete(SBaserHwnd* bwin)
	{
		// Make sure our environment is sane
		if (bwin)
		{
			//////////
			// Lock
			//////
				EnterCriticalSection(&cs_baser_hwnd);


				//////////
				// Clean house
				//////
					// Delete the source code
					iSEM_delete(&bwin->sem, true);

					// Delete the render object
					iObj_delete(&bwin->obj, true, true, false);

					// Generally reset everything
					memcpy(bwin, 0, sizeof(SBaserHwnd));


			//////////
			// Unlock
			//////
				LeaveCriticalSection(&cs_baser_hwnd);

		}
	}




//////////
//
// Called to render the indicated overlay
//
//////
#ifndef GET_X_LPARAM
	#define GET_X_LPARAM(lp)   ((int)(short)LOWORD(lp))
#endif
#ifndef GET_Y_LPARAM
	#define GET_Y_LPARAM(lp)   ((int)(short)HIWORD(lp))
#endif

	// Note:  This wndproc is only the target of subclassed html windows
	LRESULT CALLBACK iBaserHwnd_wndProc(HWND h, UINT m, WPARAM w, LPARAM l)
	{
		bool			llInWindow;
		s32				lnX, lnY;
		HDC				lhdc;
		PAINTSTRUCT		ps;
		LRESULT			lnResult;
		SBaserHwnd*		bwin;
		SComp*			comp;


		// Search for the hwnd
		bwin = iBaserHwnd_findActiveWindow(h);
		if (bwin)
		{
			// Dispatch normally
			lnResult = CallWindowProc((WNDPROC)bwin->old_wndproc, h, m, w, l);

			// Extract mouse coordinates (just in case)
			lnX = GET_X_LPARAM(l) - bwin->rc.left;
			lnY = GET_Y_LPARAM(l) - bwin->rc.top;

			// Are we still in the window?
			llInWindow = (lnX >= 0 && lnY >= 0 && lnX < bwin->rc.right - bwin->rc.left && lnY < bwin->rc.bottom - bwin->rc.top);

			// Process certain messages
			switch (m)
			{
				case WM_PAINT:
					// Redraw
					lhdc = BeginPaint(h, &ps);

					// Populate with whatever's there
					if (bwin->obj && bwin->obj->bmp)
						BitBlt(lhdc, 0, 0, bwin->obj->bmp->bi.biWidth, bwin->obj->bmp->bi.biHeight, bwin->obj->bmp->hdc, 0, 0, SRCCOPY);

					// Done
					EndPaint(h, &ps);
					return 0;

				case WM_MOUSEMOVE:
					// Track movement over links
					bwin->mouseX = lnX;
					bwin->mouseY = lnY;

					// Iterate through all of our objects and see if any are here
					if ((comp = iBaserHwnd_findComp_byCoord(bwin)))
					{
						// We found an entry
						if (comp->html->htmlType == _HTML_TYPE_LINK)	LoadCursor(ghInstance, IDC_HAND);
						else											LoadCursor(ghInstance, IDC_ARROW);

					} else if (!llInWindow && bwin->inWindow) {
						// We're leaving the window
						LoadCursor(ghInstance, IDC_ARROW);
					}

					// Done
					return 0;

				case WM_LBUTTONUP:
					// If on a link, click
					bwin->mouseX = lnX;
					bwin->mouseY = lnY;

					// Iterate through all of our objects and see if any are here
					if ((comp = iBaserHwnd_findComp_byCoord(bwin)) && comp->html->htmlType == _HTML_TYPE_LINK)
					{
						// They clicked on a link
// TODO:  working here
						// Dispatch the url back
					}

					// Done
					return 0;
			}

			// Indicate the called function return result
			return(lnResult);
		}

		// If we get here, return the default
		return(DefWindowProc(h, m, w, l));
	}

	// Iterate through all of our objects and see if any are here
	SComp* iBaserHwnd_findComp_byCoord(SBaserHwnd* bwin)
	{
		SLine* line;
		SComp* comp;


		// Iterate through each line, then each component
		for (line = bwin->sem->firstLine; line; line = line->ll.nextLine)
		{
			// Are there components on this line?
			if (line->compilerInfo && line->compilerInfo->firstComp)
			{
				// Iterate through comps
				for (comp = line->compilerInfo->firstComp; comp; iComps_getNth(comp))
				{
					// If the mouse is over this component
// TODO:  working here
				}
			}
		}

		// If we get here, not found
		return(NULL);
	}
