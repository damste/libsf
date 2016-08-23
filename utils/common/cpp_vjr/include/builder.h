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
			s8*		data;
			s8*		data_s8;								// Pointer to a buffer allocated in blocks
			u8*		data_u8;
			s8*		buffer;
			uptr	_data;
		};
		u32			allocatedLength;						// How much of space has been allocated for the buffer
		u32			populatedLength;						// How much of the allocated buffer is actually populated with data
		union {
			u32		allocateBlockSize;						// Typically 16KB, the larger the size the fewer reallocs() are required
			u32		totSize;
		};
	};

	struct SBuilderCallback
	{
		SBuilder*	b;										// The builder being iterated through
		u32			stepSize;								// Step size for each element in b->buffer (must be an even multiple of b->populatedLength to be valid)
		u32			offset;									// Offset into b->buffer

		// For each iteration:
		void*		iter_ptr;								// Cast as (target*) to get this iteration's pointer in the data type
		s32			iter_count;								// Increments each time (starts at 0)

		// Available for user general purpose use
		union {
			uptr	_extra1;
			void*	extra1;
		};
		union {
			uptr	_extra2;
			void*	extra2;
		};
		bool		flag1;
		bool		flag2;
		s32			value1;
		s32			value2;

		// Iterate function (return true to continue iteration, false to stop)
		union {
			uptr	_iterateFunc;
			bool	(*iterateFunc)		(SBuilderCallback* bcb);
		};
	};

	struct SBuilderCallback2
	{
		SBuilder*	b1;										// The builder being iterated through
		SBuilder*	b2;										// The builder being iterated through
		u32			stepSize1;								// Step size for each element in b1->buffer (must be an even multiple of b1->populatedLength to be valid)
		u32			offset1;								// Offset into b1->buffer
		u32			stepSize2;								// Step size for each element in b2->buffer (must be an even multiple of b2->populatedLength to be valid)
		u32			offset2;								// Offset into b2->buffer

		// For each iteration:
		void*		iter1_ptr;								// Cast as (target*) to get this iteration's pointer in the data type
		void*		iter2_ptr;								// Cast as (target*) to get this iteration's pointer in the data type
		s32			iter_count;								// Increments each time (starts at 0)

		// Available for user general purpose use
		union {
			uptr	_extra1;
			void*	extra1;
		};
		union {
			uptr	_extra2;
			void*	extra2;
		};
		bool		flag1;
		bool		flag2;
		s32			value1;
		s32			value2;

		// Iterate function (return true to continue iteration, false to stop)
		union {
			uptr	_iterate2Func;
			bool	(*iterate2Func)		(SBuilderCallback2* bcb2);
		};
	};




//////////
//
// Forward declarations
//
//////
	void		iBuilder_verifySizeForNewBytes				(SBuilder* builder, u32 tnDataLength);
	void		iBuilder_createAndInitialize				(SBuilder** builder, u32 tnAllocationBlockSize = -1);
	bool		iBuilder_isPointer							(SBuilder* builder, uptr testptr, void** outPtr = NULL);
	cs8*		iBuilder_appendData							(SBuilder* builder, SDatum* data);
	cs8*		iBuilder_appendData							(SBuilder* builder, cs8* tcData, u32 tnDataLength);
	cu8*		iBuilder_appendData							(SBuilder* builder, cu8* tcData, u32 tnDataLength);
	u8*			iBuilder_append_uptr						(SBuilder* builder, uptr tnValue);
	u8*			iBuilder_appendCrLf							(SBuilder* builder);
	void		iBuilder_delete								(SBuilder* builder, u32 tnStartOffset, u32 tnDeleteLength);
	void		iBuilder_reset								(SBuilder* builder);
	void		iBuilder_rewind								(SBuilder* builder);
	s8*			iBuilder_allocateBytes						(SBuilder* builder, u32 tnDataLength);
	void		iBuilder_backoffTrailingWhitespaces			(SBuilder* builder);
	void		iBuilder_setSize							(SBuilder* builder, u32 tnBufferLength);
	void		iBuilder_freeAndRelease						(SBuilder** builder);
	u32			iBuilder_asciiWriteOutFile					(SBuilder* builder, cu8* tcPathname, bool tlAppend = false);
	bool		iBuilder_asciiReadFromFile					(SBuilder** builder, cu8* tcPathname);
	void		iBuilder_compactData						(SBuilder* builder, u32 tnStart, u32 tnStride, u32 tnCompactCallbackFunction);
	s8*			iBuilder_insertBytes						(SBuilder* builder, u32 tnStart, u32 tnLength);
	u32			iBuilder_binarySearch						(SBuilder* builderHaystack, s8* textNeedle, u32 needleLength, bool* tlFound, bool tlInsertIfNotFound);
	s32			iBuilder_iterate							(SBuilder* builder, u32 tnStepSize, SBuilderCallback* cb, uptr _iterateFunc = NULL);
	s32			iBuilder_iterate_N_to_N						(SBuilder* builder, u32 tnStepSize, u32 tnStartRecord, u32 tnStopRecord, SBuilderCallback* cb, uptr _iterateFunc = NULL);
	s32			iBuilder_iterate2							(SBuilder* builder1, SBuilder* builder2, u32 tnStepSize1, u32 tnStepSize2, SBuilderCallback2* cb2, uptr _iterate2Func = NULL);
	s32			iBuilder_iterate2_N_to_N					(SBuilder* builder1, SBuilder* builder2, u32 tnStepSize1, u32 tnStepSize2, u32 tnStartRecord, u32 tnStopRecord, SBuilderCallback2* cb2, uptr _iterate2Func = NULL);
	s8*			iBuilder_retrieveRecord						(SBuilder* builder, u32 tnStepSize, u32 tnN);

	// Added to append "name = something" strings with a terminating CR/LF
	s32			iBuilder_append_label_uptr					(SBuilder* builder, s8* tcLabelText, uptr udata);
	s32			iBuilder_append_label_sptr					(SBuilder* builder, s8* tcLabelText, sptr sdata);
	s32			iBuilder_append_label_text					(SBuilder* builder, s8* tcLabelText, s8* tcText);
	s32			iBuilder_append_label_datum					(SBuilder* builder, s8* tcLabelText, SDatum* datum);
	s32			iBuilder_append_label_logical				(SBuilder* builder, s8* tcLabelText, bool tlValue);



#endif	// __BUILDER_H__
