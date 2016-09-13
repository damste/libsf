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



struct SStruct;
struct SElement;
struct SStructDllFunc;
struct SStructDllCallbacks;


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

cu32	_BASER_ELTYPE_S8			= 1;
cu32	_BASER_ELTYPE_S16			= 2;
cu32	_BASER_ELTYPE_S32			= 3;
cu32	_BASER_ELTYPE_S64			= 4;

cu32	_BASER_ELTYPE_F32			= 5;
cu32	_BASER_ELTYPE_F64			= 6;

cu32	_BASER_ELTYPE_U8			= 7;
cu32	_BASER_ELTYPE_U16			= 8;
cu32	_BASER_ELTYPE_U32			= 9;
cu32	_BASER_ELTYPE_U64			= 10;

cu32	_BASER_ELTYPE_TYPE			= 11;		// When a dll function is used, the type is given after, like "func abc_decode type abc" ... so this would indicate "abc"

cu32	_BASER_ELTYPE_DLL			= 12;
cu32	_BASER_ELTYPE_DLL_FUNC		= 13;

struct SStructDllCallbacks
{
	// Disk read
	union {
		uptr		_iDisk_read;
		s32			(*iDisk_read)		(s32 tnFile, s64 tnSeekOffset, void* tcData, s32 tnReadCount, bool* tlError, u32* tnErrorNum);
	};

};

struct SStructType
{
	SDatum			type;			// The type name to use for this
};

struct SStructDll
{
	SDatum			pathname;		// Full disk path to the DLL
	HMODULE			handle;			// From LoadLibrary(pathname)
};

struct SStructDllFunc
{
	SStructDll*		dll;			// The dll this function relates to
	SDatum			name;			// Function name
	SDatum			type;			// Type name

									// Function to call within
	union {
		uptr		_func;
		void		(*func)		(SElement* el, SStructDllCallbacks* cb);
	};
};

struct SElement
{
	// Element type
	u32				elType;
	SDatum			name;			// Data element name

									// File handle to retrieve from
	s32				file;

	// Offset and length of this data
	s32				offset;
	s32				length;

	union {
		SStructType		type;
		SStructDll		dll;
		SStructDllFunc	dllFunc;
	};
};

struct SStruct
{
	SDatum			name;			// Structure name
	SBuilder*		data;			// The SElements within each one
};
