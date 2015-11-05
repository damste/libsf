//////////
//
// /libsf/utils/common/cpp/builder.h
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
//  ____          _  _      _
// |  _ \        (_)| |    | |
// | |_) | _   _  _ | |  __| |  ___  _ __
// |  _ < | | | || || | / _` | / _ \| '__|
// | |_) || |_| || || || (_| ||  __/| |
// |____/  \__,_||_||_| \__,_| \___||_|
//    Builder -- Accumulator Buffer.
//////////




//#pragma once
#ifndef __BUILDER_H__
#define __BUILDER_H__

struct SDatum;




//////////
// The SBuilder structure.
// Initialize with iBuilder_createAndInitialize().
// Populate with iBuilder_append*().
// Release with iBuilder_freeAndRelease().
//////
	struct SBuilder
	{
		union {
			s8*		data_s8;												// Pointer to a buffer allocated in blocks
			u8*		data_u8;
			s8*		buffer;
			uptr	_data;
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
	bool		iBuilder_isPointer							(SBuilder* buffRoot, uptr testptr);
	cs8*		iBuilder_appendData							(SBuilder* buffRoot, SDatum* data);
	cs8*		iBuilder_appendData							(SBuilder* buffRoot, cs8* tcData, u32 tnDataLength);
	cu8*		iBuilder_appendData							(SBuilder* buffRoot, cu8* tcData, u32 tnDataLength);
	u8*			iBuilder_append_uptr						(SBuilder* buffRoot, uptr tnValue);
	u8*			iBuilder_appendCrLf							(SBuilder* buffRoot);
	void		iBuilder_delete								(SBuilder* buffRoot, u32 tnStartOffset, u32 tnDeleteLength);
	void		iBuilder_reset								(SBuilder* buffRoot);
	void		iBuilder_rewind								(SBuilder* buffRoot);
	s8*			iBuilder_allocateBytes						(SBuilder* buffRoot, u32 tnDataLength);
	void		iBuilder_backoffTrailingWhitespaces			(SBuilder* buffRoot);
	void		iBuilder_setSize							(SBuilder* buffRoot, u32 tnBufferLength);
	void		iBuilder_freeAndRelease						(SBuilder** buffRoot);
	u32			iBuilder_asciiWriteOutFile					(SBuilder* buffRoot, cu8* tcPathname, bool tlAppend = false);
	bool		iBuilder_asciiReadFromFile					(SBuilder** buffRoot, cu8* tcPathname);
	void		iBuilder_compactData						(SBuilder* buffRoot, u32 tnStart, u32 tnStride, u32 tnCompactCallbackFunction);
	s8*			iBuilder_insertBytes						(SBuilder* buffRoot, u32 tnStart, u32 tnLength);
	u32			iBuilder_binarySearch						(SBuilder* haystack, s8* tcNeedle, u32 tnNeedleLength, bool* tlFound, bool tlInsertIfNotFound);

	// Added to append "name = something" strings with a terminating CR/LF
	s32			iBuilder_append_label_uptr					(SBuilder* buffRoot, s8* tcLabelText, uptr udata);
	s32			iBuilder_append_label_sptr					(SBuilder* buffRoot, s8* tcLabelText, sptr sdata);
	s32			iBuilder_append_label_text					(SBuilder* buffRoot, s8* tcLabelText, s8* tcText);
	s32			iBuilder_append_label_datum					(SBuilder* buffRoot, s8* tcLabelText, SDatum* datum);
	s32			iBuilder_append_label_logical				(SBuilder* buffRoot, s8* tcLabelText, bool tlValue);



#endif	// __BUILDER_H__
