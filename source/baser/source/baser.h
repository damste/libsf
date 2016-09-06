//////////
//
// /libsf/source/baser/source/baser1.cpp
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




//////////
// Global variables
//////
	bool			glBaser_isRunning							= false;
	SBuilder*		gsBaserRoot									= NULL;

	// Bitmaps
	SBitmap*		bmp512b										= NULL;
	SBitmap*		bmp1Kb										= NULL;
	SBitmap*		bmpF12Throttle								= NULL;

	SBitmap*		bmp512bOver									= NULL;
	SBitmap*		bmp1KbOver									= NULL;
	SBitmap*		bmpF12ThrottleOver							= NULL;




//////////
// Render colors
//////
	SBgra			titleColor									= { rgba(0, 92, 192, 255) };		// Dark blue
	SBgra			orangeLowColor								= { rgba(255,225,172,255) };		// Orange-ish
	SBgra			orangeHighColor								= { rgba(255,244,224,255) };
	SBgra			cyanLowColor								= { rgba(216,255,255,255) };		// Cyan-ish
	SBgra			cyanHighColor								= { rgba(237,255,255,255) };
	SBgra			greenLowColor								= { rgba(192,255,192,255) };		// Green-ish
	SBgra			greenHighColor								= { rgba(235,255,235,255) };
	SBgra			purpleLowColor								= { rgba(231,204,255,255) };		// Purple-ish
	SBgra			purpleHighColor								= { rgba(245,235,255,255) };
	SBgra			pinkLowColor								= { rgba(255,191,255,255) };		// Pinkish
	SBgra			pinkHighColor								= { rgba(255,235,255,255) };
	SBgra			disabledLowColor							= { rgba(235,235,235,255) };		// Grayish
	SBgra			disabledHighColor							= { rgba(250,250,250,255) };
	SBgra			invalidLowColor								= { rgba(255,235,235,255) };		// Reddish
	SBgra			invalidHighColor							= { rgba(255,245,245,255) };
	SBgra			memoryFillColor								= { rgba(242,247,255,255) };		// Blue-ish
	SBgra			memoryBorderColor							= { rgba(217,232,235,255) };		// Darker blue-ish
	SBgra			memoryOptionColor							= { rgba(64,140,255,255) };			// Darkest blue-ish
	SBgra			memoryOptionHighlightColor					= { rgba(255,192,128,255) };		// Striking orangish
	SBgra			registerColor								= { rgba(245,235,255,255) };		// Purple-ish
	SBgra			textColor									= { rgba(255,255,255,255) };		// White
	SBgra			redGrayColor								= { rgba(235,205,205,255) };


//////////
// Fonts in use
//////
	u8				cgcUbuntu[]									= "Ubuntu";
	u8				cgcUbuntuMono[]								= "Ubuntu Mono";
	SFont*			fontUbuntuMono8								= NULL;
	SFont*			fontUbuntuMono10							= NULL;
	SFont*			fontUbuntu14								= NULL;


//////////
// Callback messages
//////
	u32				_WMBASER_CONTENT_IS_READY					= WM_USER + 0;


//////////
// Structures
//////
	// These occupy the gsBaserRoot builder
	struct SBaser
	{
		bool		isUsed;

		// Filename used to open (retrieved with GetFullPathname())
		s8			filename[_MAX_PATH];
		s32			filenameLength;
		s32			handle;
		s32			loadAddress;

		// Number of bytes actually read (max of 512)
		SDatum		data;
		union {
			s8		data_s8[512];
			u8		data_u8[512];
		};
	};

	// For passing messages
	// Note:  Each time a message is sent with a valid bsr, the bsr->refCount is incremented
	struct SBaserMsg
	{
		bool		isUsed;
		SDatum		message;		// Message begin sent
		SBaser		bsr;			// Copy of related baser entry

		// Data loaded for this operation (may be different than bsr->data_s8[])
		SDatum		data;
	};


//////////
// Forward declarations
//////
	// Public declarations (see baser.def)
	s32				baser_load									(s8* tcFilename);
	s32				baser_release								(int tnHandle);
	s32				baser_populate_row							(int tnHandle,              int tnOffset, int tnBase, s8* tcBufferOut, int tnBufferOut_length);
	s32				baser_parse_block_by_struct					(int tnHandle, HWND tnHwnd, int tnOffset, cs8* cStruct, int nStructLength);
	s32				baser_retrieve_data							(int nId, s8* cDataOut, int tnDataLength);


	// Internal declarations
	void			iBaser_initialize							(void);
	SBaser*			iiBaser_allocate							(void);
	s8*				iiBaser_getFullPathName						(s8* tcFilename, s8 full_pathname[_MAX_PATH]);
	SBaser*			iBaser_findBy_fullPathname					(s8* tcPathname);
	SBaser*			iBaser_findBy_handle						(s32 tnHandle);
	DWORD			iiBaser_parse_block_by_struct__threadProc	(LPVOID param);





//////////
//
// Initialize baser
//
//////
	void iBaser_initialize(void)
	{
		// Initialize VJr's internal engine
		iVjr_init_minimal();

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
// Called to parse and process the indicated structure, using the indicated data block
//
//////
	DWORD iiBaser_parse_block_by_struct__threadProc(LPVOID param)
	{
		SBaserMsg*	bm;
		SEM*		sem;


		// Retrieve our parameter rightly
		bm = (SBaserMsg*)param;

		// Parse the structure
		if (iSEM_load_fromMemory(NULL, (sem = iSEM_allocate(true)), &bm->message, true, false))
		{
			// Render the data based on the structure
// TODO:  working here

			// Send back completed message

			// Delete the sem
			iSEM_delete(&sem, true);
		}

		// Release the memory blocks
		iDatum_delete(&bm->message, false);
		free(bm);

		// Complete
		TerminateThread(GetCurrentThread(), 0);
		return(0);
	}
