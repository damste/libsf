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
	HWND		hwndCallback;	// Callback when completed processing this message

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
	// Disk get file position offset
	union {
		uptr		_iDisk_getFilePosition;
		s64			(*iDisk_getFilePosition)(s32 tnFile, bool* tlError, u32* tnErrorNum);
	};

	// Disk set file position offset
	union {
		uptr		_iDisk_setFilePosition;
		s64			(*iDisk_setFilePosition)(s32 tnFile, s64 tnSeekOffset, bool* tlError, u32* tnErrorNum);
	};

	// Disk read
	union {
		uptr		_iDisk_read;
		s32			(*iDisk_read)		(s32 tnFile, s64 tnSeekOffset, void* tcData, s32 tnReadCount, bool* tlError, u32* tnErrorNum);
	};

	// Disk write
	union
	{
		uptr		_iDisk_write;
		s32			(*iDisk_write)		(s32 tnFile, s64 tnSeekOffset, void* tcData, s32 tnWriteCount, bool* tlError, u32* tnErrorNum);
	};
};

struct SStructType
{
	SDatum			dllFuncType;	// The DLL type name to use for this data
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
		s32			(*func)		(s32 tnFileOffset, SBuilder* output, SElement* el, SStructDllCallbacks* cb);	// Returns the length consumed from tnFileOffset
	};
};

struct SElement
{
	// Element type
	u32				elType;
	bool			isPointer;		// If it's a pointer to this type, then here it is
	SDatum			name;			// Data element name

	// File handle to retrieve from
	s32				file;

	// Offset and length of this data
	s32				offset;
	s32				length;

	// If it's a floating point form, optional fpLength and fpDecimals, such as 6, 2 for "123.45"
	s32				fpLength;		// By default, f32=8 f64=15, override with a declaration of something like "fp 14,4" in the struct
	s32				fpDecimals;		// By default, f32=2 f64=4

	// Content related to _BASER_ELTYPE_*
	union {
		SStructType		type;		// _BASER_ELTYPE_TYPE
		SStructDll		dll;		// _BASER_ELTYPE_DLL
		SStructDllFunc	dllFunc;	// _BASER_ELTYPE_DLLFUNC
	};
};

struct SStruct
{
	SDatum			name;			// Structure name

	SBuilder*		elements;		// The SElements within each one
};

// For constructed messages with content, dispatched by hwnd callback, they are retrieved here
struct SBaserContent
{
	bool			isUsed;			// Is this a valid message?
	SBuilder*		content;		// The message content
};

// For rendering HTML atop another hwnd
struct SBaserHwnd
{
	bool			isUsed;			// Is this entry used?
	bool			inWindow;		// Is the mouse currently in the window?

	// Window and relative window info
	HWND			hwnd;			// Handle
	RECT			rc;				// Rectangle for the display
	s32				mouseX;			// Mouse X coordinate
	s32				mouseY;			// Mouse Y coordinate

	// Old address before we sub-classed it
	LONG			old_wndproc;

	// The associated 
	SEM*			sem;			// The html source code
	SObject*		obj;			// The object the html source code is graphically into
};
