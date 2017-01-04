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
	SBuilder*		gsBaserRoot									= NULL;			// SBaser
	SBuilder*		gsBaserMessagesRoot							= NULL;			// SBaserContent
	SBuilder*		gsBaserWindowsRoot							= NULL;			// SBaserHwnd

	// For synchronized access
	CRITICAL_SECTION cs_content_messages;
	CRITICAL_SECTION cs_baser_hwnd;

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
// General named tokens
//////
	cs8				cgc_baser_data[]							= "data";


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
	#include "baser_structs.h"

	// Global callback to standard functions
	SStructDllCallbacks gsBaserCallback = {
		(uptr)&iDisk_getFilePosition,
		(uptr)&iDisk_setFilePosition, 
		(uptr)&iDisk_read,
		(uptr)&iDisk_write
	};


//////////
// Keywords for Baser
//////
	cs8		cgc_baser_struct[]		= "struct";
	cs8		cgc_baser_dll[]			= "dll";
	cs8		cgc_baser_func[]		= "func";
	cs8		cgc_baser_type[]		= "type";
	cs8		cgc_baser_alias[]		= "alias";
	cs8		cgc_baser_fp[]			= "fp";
	cs8		cgc_baser_int[]			= "int";
	cs8		cgc_baser_uint[]		= "uint";

	cu32	_ICODE_BASER_STRUCT		= 5000000;
	cu32	_ICODE_BASER_DLL		= 5000001;
	cu32	_ICODE_BASER_FUNC		= 5000002;
	cu32	_ICODE_BASER_TYPE		= 5000003;
	cu32	_ICODE_BASER_FP			= 5000004;

	SAsciiCompSearcher cgcBaserKeywords[] =
	{
		// keyword					length		repeats?	extra (type)							first on line?		category				syntax highlight color		syntax highlight bold		onCandidateMatch()		onFind()	compilerDictionaryLookup()
		{ cgc_baser_struct,			6,			false,		_ICODE_BASER_STRUCT,					false,				_ICAT_DEFINITION,		&colorSynHi_keyword,		false,						null0,					null0,		null0 },
		{ cgc_baser_dll,			3,			false,		_ICODE_BASER_DLL,						false,				_ICAT_DEFINITION,		&colorSynHi_keyword,		false,						null0,					null0,		null0 },
		{ cgc_baser_func,			4,			false,		_ICODE_BASER_FUNC,						false,				_ICAT_DEFINITION,		&colorSynHi_keyword,		false,						null0,					null0,		null0 },
		{ cgc_baser_type,			4,			false,		_ICODE_BASER_TYPE,						false,				_ICAT_DEFINITION,		&colorSynHi_keyword,		false,						null0,					null0,		null0 },
		{ cgc_baser_alias,			5,			false,		_ICODE_BASER_TYPE,						false,				_ICAT_DEFINITION,		&colorSynHi_keyword,		false,						null0,					null0,		null0 },
		{ cgc_baser_fp,				2,			false,		_ICODE_BASER_FP,						false,				_ICAT_DEFINITION,		&colorSynHi_keyword,		false,						null0,					null0,		null0 },

		// Data types
		{ cgc_u8,					2,			false,		_ICODE_U8,								false,				_ICAT_DEFINITION,		null0,						false,						null0,					null0,		null0 },
		{ cgc_u16,					3,			false,		_ICODE_U16,								false,				_ICAT_DEFINITION,		null0,						false,						null0,					null0,		null0 },
		{ cgc_u32,					3,			false,		_ICODE_U32,								false,				_ICAT_DEFINITION,		null0,						false,						null0,					null0,		null0 },
		{ cgc_baser_uint,			4,			false,		_ICODE_U32,								false,				_ICAT_DEFINITION,		null0,						false,						null0,					null0,		null0 },
		{ cgc_u64,					3,			false,		_ICODE_U64,								false,				_ICAT_DEFINITION,		null0,						false,						null0,					null0,		null0 },

		{ cgc_f32,					3,			false,		_ICODE_F32,								false,				_ICAT_DEFINITION,		null0,						false,						null0,					null0,		null0 },
		{ cgc_f64,					3,			false,		_ICODE_F64,								false,				_ICAT_DEFINITION,		null0,						false,						null0,					null0,		null0 },

		{ cgc_s8,					2,			false,		_ICODE_S8,								false,				_ICAT_DEFINITION,		null0,						false,						null0,					null0,		null0 },
		{ cgc_s16,					3,			false,		_ICODE_S16,								false,				_ICAT_DEFINITION,		null0,						false,						null0,					null0,		null0 },
		{ cgc_s32,					3,			false,		_ICODE_S32,								false,				_ICAT_DEFINITION,		null0,						false,						null0,					null0,		null0 },
		{ cgc_baser_int,			3,			false,		_ICODE_S32,								false,				_ICAT_DEFINITION,		null0,						false,						null0,					null0,		null0 },
		{ cgc_s64,					3,			false,		_ICODE_S64,								false,				_ICAT_DEFINITION,		null0,						false,						null0,					null0,		null0 },

		{ 0,						0,			0,			0,										0,					0,					0,							0,							0,						0,			0 }
	};


//////////
// Forward declarations
//////
extern "C" {
	// Public declarations (see baser.def)
	s32					baser_load													(s8* tcFilename);
	s32					baser_release												(s32 tnHandle);
	s32					baser_populate_row											(s32 tnHandle,                      s32 tnOffset, s32 tnBase, s8* tcBufferOut, s32 tnBufferOut_length);
	s32					baser_parse_block_by_struct									(s32 tnHandle, HWND tnHwndCallback, s32 tnOffset, cs8* cStruct, s32 nStructLength);
	s32					baser_retrieve_data											(s32 nId, s8* tcDataOut, s32 tnDataOutLength);
	s32					baser_render_html											(HWND hwnd, s32 left, s32 top, s32 right, s32 bottom, s8* tcHtmlContent, s32 tnHtmlContentLength);
	s32					baser_create_htmltemp_file_content							(s8* tcFileOut260, s8* tcFilenamePrefix, s8* tcContent, s32 tnContentLength);
};


	// Internal declarations
	void				iBaser_initialize											(void);
	SBaser*				iiBaser_allocate											(void);
	s8*					iiBaser_getFullPathName										(s8* tcFilename, s8 full_pathname[_MAX_PATH]);
	SBaser*				iBaser_findBy_fullPathname									(s8* tcPathname);
	SBaser*				iBaser_findBy_handle										(s32 tnHandle);
	SBaserHwnd*			iBaserHwnd_findBy_hwnd										(HWND hwnd);
	DWORD				iiBaser_parse_block_by_struct__threadProc					(LPVOID param);
	void				iiBaser_parse_block_by_struct__threadProc__appendElement	(SBuilder* builder, SStruct** strRoot, SElement** elRoot, SDatum* name, SDatum* dllFuncType, u32 elType, s32 tnSize, s32* tnOffset, SStructDll* currentDll, s32 lnFpLength, s32 lnFpDecimals, bool tlPointer);
	void				iiBaser_parse_block_by_struct__threadProc__appendDll		(SBuilder* builder, SStruct** strRoot, SElement** elRoot, SDatum* name, SStructDll** currentDllRoot);
	void				iiBaser_parse_block_by_struct__threadProc__appendFunc		(SBuilder* builder, SStruct** strRoot, SElement** elRoot, SDatum* name, SDatum* type, SStructDll* currentDll);
	void				iiBaser_populateDatum_byComp								(SComp* comp, SDatum* datum);
	void				iBaser_deleteStructs										(SBuilder** structsRoot);
	void				iiBaser_append_s8											(SBuilder* output, SElement* elData, s8 data);
	void				iiBaser_append_s16											(SBuilder* output, SElement* elData, s16 data);
	void				iiBaser_append_s32											(SBuilder* output, SElement* elData, s32 data);
	void				iiBaser_append_s64											(SBuilder* output, SElement* elData, s64 data);
	void				iiBaser_append_f32											(SBuilder* output, SElement* elData, f32 data);
	void				iiBaser_append_f64											(SBuilder* output, SElement* elData, f64 data);
	void				iiBaser_append_u8											(SBuilder* output, SElement* elData, u8 data);
	void				iiBaser_append_u16											(SBuilder* output, SElement* elData, u16 data);
	void				iiBaser_append_u32											(SBuilder* output, SElement* elData, u32 data);
	void				iiBaser_append_u64											(SBuilder* output, SElement* elData, u64 data);
	s32					iiBaser_append_type											(SBuilder* output, SElement* elData, SBuilder* structs, s32 tnFileOffset);
	void				iiBaser_dispatch_contentMessage								(HWND hwnd, SBuilder* content);
	void				iBaserHwnd_delete											(SBaserHwnd* bwin);
	LRESULT CALLBACK	iBaserHwnd_wndProc											(HWND h, UINT m, WPARAM w, LPARAM l);
	SComp*				iBaserHwnd_findComp_byCoord									(SBaserHwnd* bwin);
