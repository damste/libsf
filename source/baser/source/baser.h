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
	SBuilder*		gsBaserMessagesRoot							= NULL;
	CRITICAL_SECTION cs_content_messages;

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
		(uptr)&iDisk_read
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
	// Public declarations (see baser.def)
	s32				baser_load													(s8* tcFilename);
	s32				baser_release												(s32 tnHandle);
	s32				baser_populate_row											(s32 tnHandle,                      s32 tnOffset, s32 tnBase, s8* tcBufferOut, s32 tnBufferOut_length);
	s32				baser_parse_block_by_struct									(s32 tnHandle, HWND tnHwndCallback, s32 tnOffset, cs8* cStruct, s32 nStructLength);
	s32				baser_retrieve_data											(s32 nId, s8* tcDataOut, s32 tnDataOutLength);
	s32				baser_create_htmltemp_file_content							(s8* tcFileOut260, s8* tcFilenamePrefix, s8* tcContent, s32 tnContentLength);


	// Internal declarations
	void			iBaser_initialize											(void);
	SBaser*			iiBaser_allocate											(void);
	s8*				iiBaser_getFullPathName										(s8* tcFilename, s8 full_pathname[_MAX_PATH]);
	SBaser*			iBaser_findBy_fullPathname									(s8* tcPathname);
	SBaser*			iBaser_findBy_handle										(s32 tnHandle);
	DWORD			iiBaser_parse_block_by_struct__threadProc					(LPVOID param);
	void			iiBaser_parse_block_by_struct__threadProc__appendElement	(SBuilder* builder, SStruct** strRoot, SElement** elRoot, SDatum* name, u32 elType, s32 tnSize, s32* tnOffset, SStructDll* currentDll, s32 lnFpLength, s32 lnFpDecimals);
	void			iiBaser_parse_block_by_struct__threadProc__appendDll		(SBuilder* builder, SStruct** strRoot, SElement** elRoot, SDatum* name, SStructDll** currentDllRoot);
	void			iiBaser_parse_block_by_struct__threadProc__appendFunc		(SBuilder* builder, SStruct** strRoot, SElement** elRoot, SDatum* name, SDatum* type, SStructDll* currentDll);
	void			iiBaser_populateDatum_byComp								(SComp* comp, SDatum* datum);
	void			iiBaser_deleteStructs										(SBuilder** structsRoot);
	void			iiBaser_append_s8											(SBuilder* output, SElement* elData, s8 data);
	void			iiBaser_append_s16											(SBuilder* output, SElement* elData, s16 data);
	void			iiBaser_append_s32											(SBuilder* output, SElement* elData, s32 data);
	void			iiBaser_append_s64											(SBuilder* output, SElement* elData, s64 data);
	void			iiBaser_append_f32											(SBuilder* output, SElement* elData, f32 data);
	void			iiBaser_append_f64											(SBuilder* output, SElement* elData, f64 data);
	void			iiBaser_append_u8											(SBuilder* output, SElement* elData, u8 data);
	void			iiBaser_append_u16											(SBuilder* output, SElement* elData, u16 data);
	void			iiBaser_append_u32											(SBuilder* output, SElement* elData, u32 data);
	void			iiBaser_append_u64											(SBuilder* output, SElement* elData, u64 data);
	s32				iiBaser_append_type											(SBuilder* output, SElement* elData, SBuilder* structs, s32 tnOffset);
	void			iiBaser_dispatch_contentMessage								(HWND hwnd, SBuilder* content);




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
//
//////
							// Initially assume no name
							name.data_s8	= NULL;
							name.length		= 0;

							// Grab the name component (if any)
							compNext = iComps_getNth(comp);
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
							iiBaser_parse_block_by_struct__threadProc__appendElement(structs, &str, &el, &name, lnElType, lnSize * lnCount, &lnOffset, dll, lnFpLength, lnFpDecimals);
							break;

						case _ICODE_ALPHA:
						case _ICODE_ALPHANUMERIC:
							// This should be a type name which is like s32, s8, etc., but uses a custom type that decodes from within a dll function rather than internally
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
									// Grab the type alias
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

				iterate(lnJ, str->elements, el, SElement)
				// Begin

					switch (el->elType)
					{
						case _BASER_ELTYPE_S8:
							iiBaser_append_s8(output, el, *(s8*)bm->data.data_s8[lnOffset]);
							lnOffset += el->length;
							break;
						case _BASER_ELTYPE_S16:
							iiBaser_append_s16(output, el, *(s16*)bm->data.data_s8[lnOffset]);
							lnOffset += el->length;
							break;
						case _BASER_ELTYPE_S32:
							iiBaser_append_s32(output, el, *(s32*)bm->data.data_s8[lnOffset]);
							lnOffset += el->length;
							break;
						case _BASER_ELTYPE_S64:
							iiBaser_append_s64(output, el, *(s64*)bm->data.data_s8[lnOffset]);
							lnOffset += el->length;
							break;
						case _BASER_ELTYPE_F32:
							iiBaser_append_f32(output, el, *(f32*)bm->data.data_s8[lnOffset]);
							lnOffset += el->length;
							break;
						case _BASER_ELTYPE_F64:
							iiBaser_append_f64(output, el, *(f64*)bm->data.data_s8[lnOffset]);
							lnOffset += el->length;
							break;
						case _BASER_ELTYPE_U8:
							iiBaser_append_u8(output, el, *(u8*)bm->data.data_s8[lnOffset]);
							lnOffset += el->length;
							break;
						case _BASER_ELTYPE_U16:
							iiBaser_append_u16(output, el, *(u16*)bm->data.data_s8[lnOffset]);
							lnOffset += el->length;
							break;
						case _BASER_ELTYPE_U32:
							iiBaser_append_u32(output, el, *(u32*)bm->data.data_s8[lnOffset]);
							lnOffset += el->length;
							break;
						case _BASER_ELTYPE_U64:
							iiBaser_append_u64(output, el, *(u64*)bm->data.data_s8[lnOffset]);
							lnOffset += el->length;
							break;
						case _BASER_ELTYPE_TYPE:
							lnOffset += iiBaser_append_type(output, el, structs, lnOffset);
							break;

					}

				// End
				iterate_end;

			// End
			iterate_end;

			// Send back completed message
			iiBaser_dispatch_contentMessage(bm->hwndCallback, output);
			output = NULL;
			// Note:  The output builder is moved into the dispatched content message.  It is deleted on full retrieval.

			// Clean house
			iiBaser_deleteStructs(&structs);
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
	void iiBaser_parse_block_by_struct__threadProc__appendElement(SBuilder* builder, SStruct** strRoot, SElement** elRoot, SDatum* name, u32 elType, s32 tnSize, s32* tnOffset, SStructDll* currentDll, s32 lnFpLength, s32 lnFpDecimals)
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
		iiBaser_parse_block_by_struct__threadProc__appendElement(builder, strRoot, elRoot, name, _BASER_ELTYPE_DLL, 0, &lnOffset, *currentDllRoot, -1, -1);
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
		iiBaser_parse_block_by_struct__threadProc__appendElement(builder, strRoot, elRoot, name, _BASER_ELTYPE_DLL_FUNC, 0, &lnOffset, currentDll, -1, -1);
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

	void iiBaser_deleteStructs(SBuilder** structsRoot)
	{
		u32			lnI, lnJ;
		SStruct*	str;
		SElement*	el;


		// Iterate through each struct
		iterate(lnI, *structsRoot, str, SStruct)
		// Begin

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

		// End
		iterate_end;

		// Delete the builder
		iBuilder_freeAndRelease(structsRoot);
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

	s32 iiBaser_append_type(SBuilder* output, SElement* elData, SBuilder* structs, s32 tnOffset)
	{
		s32			lnLength;
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
						// Dispatch
						lnLength = el->dllFunc.func(tnOffset, elData, &gsBaserCallback);

						// Success
						return(lnLength);
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
			// Physically dispatch the message
			//////
				SendMessage(hwnd, _WMBASER_CONTENT_IS_READY, _bc, content->populatedLength);

quit:
		//////////
		// Unlock
		//////
			LeaveCriticalSection(&cs_content_messages);

	}
