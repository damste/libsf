//////////
//
// /libsf/utils/common/cpp/builder.h
//
//////
//
//
//////
// Version 0.10
// Copyright (c) 2014 by Rick C. Hodgin
//////
// Last update:
//     Nov.02.2014
//////
// Change log:
//     Nov.02.2014	- Initial creation
//////
//
// This file is self-contained and handles all builder algorithms.  It can be used as an include
// file for other stand-alone projects.  It was extracted from the Visual FreePro Virtual Machine.
//
//////////
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
//     http://www.visual-freepro.org
//     http://www.visual-freepro.org/blog/
//     http://www.visual-freepro.org/forum/
//     http://www.visual-freepro.org/wiki/
//     http://www.visual-freepro.org/wiki/index.php/PBL
//
// Thank you.  And may The Lord bless you richly as you lift up your life, your
// talents, your gifts, your praise, unto Him.  In Jesus' name I pray.  Amen.
//
//////




//////////
// The SBuilder structure.
// Initialize with iBuilder_createAndInitialize().
// Populate with iBuilder_append*().
// Release with iBuilder_freeAndRelease().
//////
	struct SBuilder
	{
		union {
			s8*		data;												// Pointer to a buffer allocated in blocks
			s8*		buffer;
			u32		_data;
		};
		u32			allocatedLength;									// How much of space has been allocated for the buffer
		u32			populatedLength;									// How much of the allocated buffer is actually populated with data
		union {
			u32		allocateBlockSize;									// Typically 16KB, the larger the size the fewer reallocs() are required
			u32		totSize;
		};
	};




//////////
//
// Forward declarations
//
//////
	void		iBuilder_verifySizeForNewBytes				(SBuilder* buffRoot, u32 tnDataLength);
	void		iBuilder_createAndInitialize				(SBuilder** buffRoot, u32 tnAllocationBlockSize);
	s8*			iBuilder_appendData							(SBuilder* buffRoot, s8* tcData, u32 tnDataLength);
	s8*			iBuilder_append_u32							(SBuilder* buffRoot, u32 tnValue);
	s8*			iBuilder_appendCrLf							(SBuilder* buffRoot);
	void		iBuilder_reset								(SBuilder* dst);
	s8*			iBuilder_allocateBytes						(SBuilder* buffRoot, u32 tnDataLength);
	void		iBuilder_backoffTrailingWhitespaces			(SBuilder* dst);
	void		iBuilder_setSize							(SBuilder* buffRoot, u32 tnBufferLength);
	void		iBuilder_freeAndRelease						(SBuilder** buffRoot);
	u32			iBuilder_asciiWriteOutFile					(SBuilder* buffRoot, s8* tcPathname);
	bool		iBuilder_asciiReadFromFile					(SBuilder** buffRoot, s8* tcPathname);
	void		iBuilder_compactData						(SBuilder* buffRoot, u32 tnStart, u32 tnStride, u32 tnCompactCallbackFunction);
	s8*			iBuilder_insertBytes						(SBuilder* buffRoot, u32 tnStart, u32 tnLength);
	u32			iBuilder_binarySearch						(SBuilder* haystack, s8* tcNeedle, u32 tnNeedleLength, bool* tlFound, bool tlInsertIfNotFound);