//////////
//
// /libsf/utils/common/cpp/builder.cpp
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
//     Aug.02.2014
//////
// Change log:
//     Aug.02.2014	- Initial creation
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
//     http://www.visual-freepro.org/wiki/index.php/Repeat_License
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




//////////
// The SBuilder structure.
// Initialize with iBuilder_createAndInitialize().
// Populate with iBuilder_append*().
// Release with iBuilder_freeAndRelease().
//////
// Nov.27.2014 -- See builder.h
// 	struct SBuilder
// 	{
// 		union {
// 			s8*		data;												// Pointer to a buffer allocated in blocks
// 			s8*		buffer;
// 			u32		_data;
// 		};
// 		u32			allocatedLength;									// How much of space has been allocated for the buffer
// 		u32			populatedLength;									// How much of the allocated buffer is actually populated with data
// 		union {
// 			u32		allocateBlockSize;									// Typically 16KB, the larger the size the fewer reallocs() are required
// 			u32		totSize;
// 		};
// 	};




//////////
//
// Called to ensure the indicated number of bytes can be appended onto the buffer without
// issue.  If not, reallocates the buffer.
//
//////
	void iBuilder_verifySizeForNewBytes(SBuilder* builder, u32 tnDataLength)
	{
		// Make sure our environment is sane
		if (builder && tnDataLength != 0)
		{
			// Repeatedly allocate our allocation size until we get big enough
			while (builder->data_s8)
			{
				// Are we there yet?
				if (builder->populatedLength + tnDataLength <= builder->allocatedLength)
					return;		// We're good

				// If we get here, we need to allocate more space
				// Reallocate and continue
				builder->data_s8			= (s8*)realloc(builder->data_s8, builder->allocatedLength + builder->allocateBlockSize);
				builder->allocatedLength	+= builder->allocateBlockSize;

				// Initialize the added block
				if (builder->data_s8)
					memset(builder->data_s8 + builder->allocatedLength - builder->allocateBlockSize, 0, builder->allocateBlockSize);
			}
		}
		// If we get here, there's been an error
	}




//////////
//
// Initializes a new buffer to the default allocation size.
// No content is changed.
//
// Returns:
//		Pointer to the point in the buffer where the
//////
	void iBuilder_createAndInitialize(SBuilder** builder, u32 tnAllocationBlockSize)
	{
		SBuilder*	buffNew;


		// See if they want to use the default size
		if (tnAllocationBlockSize == (u32)-1)
			tnAllocationBlockSize = 16384;		// Default to a 16KB allocation size

		// Make sure our environment is sane
		if (builder && tnAllocationBlockSize != 0)
		{
			buffNew = (SBuilder*)malloc(sizeof(SBuilder));
			if (buffNew)
			{
				// Initialize
				memset(buffNew, 0, sizeof(SBuilder));

				// Store the pointer
				*builder = buffNew;

				// Make sure our allocation block size is at least 4KB
				tnAllocationBlockSize		= max(4096, tnAllocationBlockSize);

				// Allocate the data space
				buffNew->data_s8			= (s8*)malloc(tnAllocationBlockSize);

				// If we allocated, we're good
				if (buffNew->data_s8)
				{
					buffNew->allocatedLength = tnAllocationBlockSize;
					memset(buffNew->data_s8, 0, tnAllocationBlockSize);

				} else {
					buffNew->allocatedLength = 0;
				}

				// Update the allocation size
				buffNew->allocateBlockSize	= tnAllocationBlockSize;
			}
		}
	}




//////////
//
// Called to determine if the testptr falls in the range of this builder
//
// Returns:
//		true	-- buffRoot is valid, and the testptr is in range
//		false	-- Either buffRoot is invalid, or testptr is not in range
//////
	bool iBuilder_isPointer(SBuilder* builder, uptr testptr, void** outPtr)
	{
		if (builder)
		{
			// It must fall in [range) to be considered valid
			if (testptr >= builder->_data && testptr < (builder->_data + builder->populatedLength))
			{
				// Set the pointer if specified
				if (outPtr)
					*outPtr = (void*)testptr;

				// Indicate success
				return(true);
			}
		}
		// If we get here, not a pointer of this buffRoot

		// Clear the pointer
		if (outPtr)
			*outPtr = NULL;

		// Indicate failure
		return(false);
	}




//////////
//
// Appends the indicated data to the end of the buffer.  If the buffer is NULL, the
// data is initialized to all 0s.  This differs from iBuilder_appendBytes() which
// does not do any initialization.
//
// Returns:
//		Pointer to the point in the buffer where the text was inserted, can be used
//		for a furthering or continuance of this function embedded in a higher call.
//////
	cs8* iBuilder_appendData(SBuilder* builder, SDatum* data)
	{
		// Make sure there's something to update
		if (builder && data && data->_data && data->length > 0)
			return((cs8*)iBuilder_appendData(builder, data->data_cu8, data->length));

		// Return our original input
		return(NULL);
	}

	cs8* iBuilder_appendData(SBuilder* builder, cs8* tcData, u32 tnDataLength)
	{
		return((cs8*)iBuilder_appendData(builder, (cu8*)tcData, tnDataLength));
	}

	cu8* iBuilder_appendData(SBuilder* builder, cu8* tcData, u32 tnDataLength)
	{
		// Make sure our environment is sane
		if (builder)
		{
			// If they want us to populate the length, do so
			if (tnDataLength == (u32)-1)
				tnDataLength = (u32)strlen((s8*)tcData);

			// If there's anything to do, do it
			if (tnDataLength != 0)
			{
				// Make sure this much data will fit there in the buffer
				iBuilder_verifySizeForNewBytes(builder, tnDataLength);

				// If we're still valid, proceed with the copy
				if (builder->data_s8)
				{
					// Copy the original content
					if (tcData)			memcpy(builder->data_s8 + builder->populatedLength, (s8*)tcData, tnDataLength);
					else				memset(builder->data_s8 + builder->populatedLength, 0, tnDataLength);

					// Increase the size
					builder->populatedLength += tnDataLength;
				}
			}
			// Indicate where the start of that buffer is
			return(builder->data_u8 + builder->populatedLength - tnDataLength);
		}
		// If we get here, things are bad
		return(NULL);
	}




//////////
//
// Appends the indicated 32-bit value.
//
//////
	u8* iBuilder_append_uptr(SBuilder* builder, uptr tnValue)
	{
		// Make sure our environment is sane
		if (builder)
		{
			// Make sure this much data will fit there in the buffer
			iBuilder_verifySizeForNewBytes(builder, sizeof(uptr));

			// Copy the data
			if (builder->data_s8)
			{
				*(uptr*)(builder->data_s8 + builder->populatedLength) = tnValue;
				builder->populatedLength += sizeof(uptr);
			}

			// Indicate where the start of that buffer is
			return(builder->data_u8 + builder->populatedLength - sizeof(uptr));
		}
		// If we get here, things are bad
		return(NULL);
	}




//////////
//
// Called to append a CR+LF to the builder
//
//////
	u8* iBuilder_appendCrLf(SBuilder* builder)
	{
		return((u8*)iBuilder_appendData(builder, (cu8*)"\r\n", 2));
	}




//////////
//
// Called to delete the indicated bytes
//
//////
	void iBuilder_delete(SBuilder* builder, u32 tnStartOffset, u32 tnDeleteLength)
	{
		if (builder && tnStartOffset <= builder->populatedLength)
		{
			// Move any data that was after the deleted block forward in the block
			if (tnStartOffset + tnDeleteLength < builder->populatedLength)
			{
				memmove(builder->buffer + tnStartOffset,
						builder->buffer + tnStartOffset + tnDeleteLength,
						builder->populatedLength - tnStartOffset - tnDeleteLength);
			}

			// Indicate the new size
			builder->populatedLength -= tnDeleteLength;
		}
	}




//////////
//
// Called to reset the buffer to 0 bytes
//
//////
	void iBuilder_reset(SBuilder* builder)
	{
		if (builder && builder->populatedLength != 0)
		{
			memset(builder->buffer, 0, builder->totSize);
			builder->populatedLength = 0;
		}
	}




//////////
//
// Called to reset the buffer to 0 bytes
//
//////
	void iBuilder_rewind(SBuilder* builder)
	{
		if (builder)
			builder->populatedLength = 0;
	}




//////////
//
// Called to allocate bytes in the builder, but not yet populate them with anything,
// nor initializing them.  If you would like to allocate a block that is initialized
// to something, or to all 0s, then use iBuilder_appendData().
//
//////
	s8* iBuilder_allocateBytes(SBuilder* builder, u32 tnDataLength)
	{
		// Make sure our environment is sane
		if (builder)
		{
			// Make sure this much data will fit there in the buffer
			if (tnDataLength != 0)
			{
				iBuilder_verifySizeForNewBytes(builder, tnDataLength);
				builder->populatedLength += tnDataLength;
			}

			// Indicate where the start of that buffer is
			return(builder->data_s8 + builder->populatedLength - tnDataLength);
		}
		// If we get here, things are bad
		return(NULL);
	}




//////////
//
// Called to back off and remove any trailing spaces from the builder, so
// that the last data is not a whitespace.
//
//////
	void iBuilder_backoffTrailingWhitespaces(SBuilder* builder)
	{
		if (builder && builder->data_s8)
		{
			// Back off so long as there are whitespaces
			while ((s32)builder->populatedLength > 0 && (builder->data_s8[builder->populatedLength - 1] == 32 || builder->data_s8[builder->populatedLength - 1] == 9))
			{
				// Reset the data there to the expected NULLs
				builder->data_s8[builder->populatedLength - 1] = 0;

				// Backup one
				--builder->populatedLength;
			}
		}
	}




//////////
//
// Specifies the size the buffer should be.  Either allocates up or down. No content
// is changed, however the buffer pointer value could be changed from oss_realloc().
// In addition, this function should not be used for resizing in general.  Simply call
// the builder_AppendData() function and it will automatically resize if needed, as
// per the allocated block size.
//
//////
	void iBuilder_setSize(SBuilder* builder, u32 tnBufferLength)
	{
		s8* lcNew;


		// Make sure our environment is sane
		if (builder)
		{
			//////////
			// See if they want to make it whatever the populated size is
			//////
				if (tnBufferLength == (u32)-1)
					tnBufferLength = builder->populatedLength;


			//////////
			// See if they're releasing everything
			//////
				if (tnBufferLength == 0)
				{
					//////////
					// They are freeing everything
					//////
						free(builder->data_s8);
						builder->data_s8			= NULL;
						builder->populatedLength	= 0;
						builder->allocatedLength	= 0;


				} else if (tnBufferLength != builder->allocatedLength) {
					//////////
					// They are resizing
					//////
						lcNew = (s8*)realloc(builder->data_s8, tnBufferLength);
						if (lcNew)
						{
							//////////
							// Set the allocated length
							//////
								builder->data_s8			= lcNew;
								builder->allocatedLength	= tnBufferLength;


							//////////
							// If our populated length no longer fits into the new allocated space, then adjust it down
							//////
								if (builder->populatedLength > builder->allocatedLength)
									builder->populatedLength = builder->allocatedLength;		// Bring the populated area down to the new size

						} else {
							// Failure on resize -- should not happen
#ifdef debug_break
							debug_break;
#endif
						}
				}
		}
	}




//////////
//
// Releases the buffer allocated for the SBuilder structure
//
//////
	void iBuilder_freeAndRelease(SBuilder** builder)
	{
		SBuilder* buffDelete;


		// Make sure our environment is sane
		if (builder && *builder)
		{
			// Copy our *buffRoot pointer to local space so we can "appear" to kill it before it's actually killed
			buffDelete	= *builder;
			*builder	= NULL;

			// Release the data buffer
			if (buffDelete->data_s8)
			{
				// Trim our sizes down to 0
				buffDelete->allocatedLength = 0;
				buffDelete->populatedLength = 0;

				// Release our buffer
				free(buffDelete->data_s8);

				// Mark it as no longer valid
				buffDelete->data_s8 = NULL;
			}

			// Release the SBuilder structure
			free(buffDelete);
		}
	}




//////////
//
// Called to write out the indicated builder file as an 8-bit ASCII file
//
//////
	u32 iBuilder_asciiWriteOutFile(SBuilder* builder, cu8* tcPathname, bool tlAppend)
	{
		FILE* lfh;


		// Make sure there's something to write
		if (builder && tcPathname)
		{
			// Try to create the file
			lfh = fopen((s8*)tcPathname, ((tlAppend) ? "ab+" : "wb+"));
			if (lfh)
			{
				// Write out the data if need be
				if (builder->data_s8 && builder->populatedLength != 0)
				{
					fwrite(builder->data_s8, 1, builder->populatedLength, lfh);
					fclose(lfh);
					return(builder->populatedLength);
				}
				// If we get here, nothing to write
				fclose(lfh);
				return(0);
			}
		}
		// If we get here, failure
		return(-1);
	}




//////////
//
// Called to load a file into the indicated buffer.
//
//////
	bool iBuilder_asciiReadFromFile(SBuilder** builder, cu8* tcPathname)
	{
		u32		lnSize, lnNumread;
		FILE*	lfh;


		// Make sure our environment is sane
		if (builder && tcPathname)
		{
			//////////
			// If we don't have a buffer, create one
			//////
				if (!*builder)
					iBuilder_createAndInitialize(builder, -1);


			// Try to open the indicated file
			lfh = fopen((s8*)tcPathname, "rb");
			if (lfh)
			{
				//////////
				// Find out how big the file is
				//////
					fseek(lfh, 0, SEEK_END);
					lnSize = ftell(lfh);
					fseek(lfh, 0, SEEK_SET);


				//////////
				// Allocate that buffer
				//////
					iBuilder_verifySizeForNewBytes(*builder, lnSize);


				//////////
				// Read in the content
				//////
					lnNumread						= (u32)fread((*builder)->data_s8 + (*builder)->populatedLength, 1, lnSize, lfh);
					(*builder)->populatedLength	+= min(lnNumread, lnSize);


				//////////
				// Close the file
				//////
					fclose(lfh);


				//////////
				// Were we successful?
				//////
					if (lnNumread == lnSize)
						return(true);	// We're good

			} else {
				// We could not open the file
				// We don't do anything here, but just trap the condition and note it here in the comments
			}
		}
		// If we get here, failure
		return(false);
	}




//////////
//
// Called to compact data
//
//////
	void iBuilder_compactData(SBuilder* builder, u32 tnStart, u32 tnStride, u32 tnCompactCallbackFunction)
	{
		u32 lnI, lnCopyTo;
		union
		{
			// This callback is used to execute a test determining if each entry can be compacted
			u32		_compactCallbackFunction;
			bool	(*compactCallbackFunction)	(void* ptr);
		};


		// Make sure our environment is sane
		if (builder && builder->data_s8 && builder->populatedLength >= tnStart)
		{
			// Setup our callback function
			_compactCallbackFunction = tnCompactCallbackFunction;

			// Iterate through each pointer
			lnCopyTo = tnStart;
			for (lnI = tnStart; lnI < builder->populatedLength; lnI += tnStride)
			{
				if (!compactCallbackFunction(builder->data_s8 + lnI))
				{
					// We are keeping this one
					if (lnCopyTo != lnI)
						memcpy(builder->data_s8 + lnCopyTo, builder->data_s8 + lnI, tnStride);

					// Move to next one
					lnCopyTo += tnStride;
				}
			}
			// When we get here, everything's been compacted
			if (lnCopyTo < builder->populatedLength)
				iBuilder_setSize(builder, lnCopyTo);
		}
	}




//////////
//
// Called to insert bytes at the indicated location.
//
//////
	s8* iBuilder_insertBytes(SBuilder* builder, u32 tnStart, u32 tnLength)
	{
		u32		lnI, lnStop;
		s8*		buffNew;
		s8*		lcSrc;
		s8*		lcDst;


		//////////
		// Make sure our environment is sane
		//////
			buffNew = NULL;
			if (builder && builder->data_s8)
			{
				//////////
				// Are we adding to the end?
				//////
					if (builder->populatedLength == tnStart)
						return(iBuilder_allocateBytes(builder, tnLength));		// We're appending to the end


				//////////
				// If we get here, we're inserting in the middle
				// We go ahead and allocate the new bytes
				//////
					buffNew = iBuilder_allocateBytes(builder, tnLength);
					if (buffNew)
					{
						//////////
						// Now, we have to copy everything backwards so we don't propagate a portion repeatedly
						//////
							lcSrc	= builder->data_s8 + builder->populatedLength - tnLength - 1;
							lcDst	= builder->data_s8 + builder->populatedLength - 1;
							lnStop	= builder->populatedLength - tnStart - tnLength;


						//////////
						// Copy until we're done
						//////
							for (lnI = 0; lnI < lnStop; lnI++, lcDst--, lcSrc--)
								*lcDst = *lcSrc;


						//////////
						// Indicate where our new record is
						//////
							buffNew = builder->data_s8 + tnStart;
					}
			}
			// Indicate our status
			return(buffNew);
	}



//////////
//
// Searching for a needle in a haystack.
// Called to perform a binary search on the data in a builder.  This is typically used for a fixed
// structure that is repeatedly stored.  The optional parameter allows the item to be inserted
// where it should go if it was not found.
//
//////
// TODO:  A speedup for this algorithm would be to test tnDataLength and if it's 32-bit or 64-bit, then do integer searches rather than string compare searches
	u32 iBuilder_binarySearch(SBuilder* builderHaystack, s8* textNeedle, u32 needleLength, bool* tlFound, bool tlInsertIfNotFound)
	{
		s32		lnResult;
		s32		lnTop, lnMid, lnBot;
		s8*		buffNew;


// TODO:  untested, breakpoint and examine
#ifdef debug_break
		debug_break;
#endif
		//////////
		// Make sure our environment is sane
		//////
			if (builderHaystack && builderHaystack->data_s8 && builderHaystack->populatedLength % needleLength == 0)
			{
				//////////
				// Perform a binary search
				//////
					lnTop = 0;
					lnBot = (builderHaystack->populatedLength / needleLength) - 1;
					lnMid = max((lnTop + lnBot) / 2, lnTop);
					while (lnTop <= lnBot)
					{
						// Position our search pointer
						lnMid = (lnTop + lnBot) / 2;

						// See if it's above or below this position
						lnResult = memcmp(builderHaystack->data_s8 + (lnMid * needleLength), textNeedle, needleLength);
						if (lnResult == 0)
						{
							// Found, but this may not be the first one, we need to creep backwards to find the first
							if (lnMid == lnBot)
							{
								// Success!
								if (tlFound)
									*tlFound = true;

								// Indicate our entry
								return(lnMid * needleLength);
							}
							// Continue looking in the top half
							lnBot = lnMid;

						} else if (lnResult < 0) {
							// Our haystack entry is less than our needle, it's after this in the list
							lnTop = lnMid + 1;

						} else {
							// Our haystack entry is greater than our need, it's before this in the list
							lnBot = lnMid - 1;
						}
					}
					// When we get here, it was not found
					if (tlFound)
						*tlFound = false;


				//////////
				// See if they want us to add it
				//////
					if (tlInsertIfNotFound)
					{
						// We will insert it where lnMid is
						buffNew = iBuilder_insertBytes(builderHaystack, lnMid * needleLength, needleLength);
						if (buffNew)
						{
							// We can copy over and insert it
							memcpy(buffNew, textNeedle, needleLength);

							// Indicate where it exists in the list
							return(lnMid * needleLength);

						} else {
							// Failure adding
							return(-3);
						}

					} else {
						// Indicate no find
						return(-1);
					}
			}


		//////////
		// Was not found, is invalid configuration
		//////
			if (tlFound)	*tlFound = false;
			return(-2);		// Is invalid configuration
	}




//////////
//
// Called to iterate through a builder
//
//////
	s32 iBuilder_iterate(SBuilder* builder, u32 tnStepSize, SBuilderCallback* cb, uptr _iterateFunc)
	{
		// Iterate from 0 all the way through to the end
		return(iBuilder_iterate_N_to_N(builder, tnStepSize, 0, (builder->populatedLength / tnStepSize) - 1, cb, _iterateFunc));
	}

	// Note:  Stop record is inclusive
	s32 iBuilder_iterate_N_to_N(SBuilder* builder, u32 tnStepSize, u32 tnStartRecord, u32 tnStopRecord, SBuilderCallback* cb, uptr _iterateFunc)
	{
		s32 lnCount;


		// Make sure our environment is sane
		lnCount = 0;
		if (builder && builder->populatedLength % tnStepSize == 0 && cb && (cb->_iterateFunc || _iterateFunc) && tnStopRecord >= tnStartRecord)
		{
			// Use the passed parameter if it was provided
			if (_iterateFunc)
				cb->_iterateFunc = _iterateFunc;

			// Setup
			cb->b			= builder;
			cb->stepSize	= tnStepSize;

			// Iterate through
			// Note:  The values of cb->offset, cb->stepSize, and cb->_iterateFunc can be updated live as it's being iterated through
			for (cb->offset = (tnStartRecord * tnStepSize), cb->iter_count = 0; cb->offset < builder->populatedLength && cb->offset <= (tnStopRecord * tnStepSize); cb->offset += cb->stepSize, ++lnCount, ++cb->iter_count)
			{
				// Setup for the iteration
				cb->iter_ptr = builder->buffer + cb->offset;
				if (!cb->iterateFunc(cb))
					break;
			}
		}

		// Indicate failure
		return(lnCount);
	}




//////////
//
// Called to iterate through two builders in parallel
//
//////
	s32 iBuilder_iterate2(SBuilder* builder1, SBuilder* builder2, u32 tnStepSize1, u32 tnStepSize2, SBuilderCallback2* cb2, uptr _iterate2Func)
	{
		// Iterate from 0 all the way through to the end of whichever one is shorter
		return(iBuilder_iterate2_N_to_N(builder1, builder2, tnStepSize1, tnStepSize2, 0, min((builder1->populatedLength / tnStepSize1) - 1, (builder2->populatedLength / tnStepSize2) - 1), cb2, _iterate2Func));
	}

	// TODO:  It might be worthwhile here to continue on so long as either of the two builders are still within range, and pass NULL for the other parameter
	// Note:  Stop record is inclusive
	s32 iBuilder_iterate2_N_to_N(SBuilder* builder1, SBuilder* builder2, u32 tnStepSize1, u32 tnStepSize2, u32 tnStartRecord, u32 tnStopRecord, SBuilderCallback2* cb2, uptr _iterate2Func)
	{
		s32 lnCount;


		// Make sure our environment is sane
		lnCount = 0;
		if (builder1 && builder1->populatedLength % tnStepSize1 == 0 && builder2 && builder2->populatedLength % tnStepSize2 == 0 && cb2 && (cb2->_iterate2Func || _iterate2Func) && tnStopRecord >= tnStartRecord)
		{
			// Use the passed parameter if it was provided
			if (_iterate2Func)
				cb2->_iterate2Func = _iterate2Func;

			// Setup
			cb2->b1			= builder1;
			cb2->stepSize1	= tnStepSize1;
			cb2->b2			= builder2;
			cb2->stepSize2	= tnStepSize2;

			// Iterate through
			// Note:  The values of cb->offset, cb->stepSize, and cb->_iterateFunc can be updated live as it's being iterated through
			cb2->offset1	= (tnStartRecord * tnStepSize1);
			cb2->offset2	= (tnStartRecord * tnStepSize2);
			for (cb2->iter_count = 0; cb2->offset1 < builder1->populatedLength && cb2->offset2 < builder2->populatedLength && cb2->offset1 <= (tnStopRecord * tnStepSize1) && cb2->offset2 <= (tnStopRecord * tnStepSize2); ++cb2->iter_count, ++lnCount)
			{
				// Setup for the iteration
				cb2->iter1_ptr = builder1->buffer + cb2->offset1;
				cb2->iter2_ptr = builder2->buffer + cb2->offset2;
				if (!cb2->iterate2Func(cb2))
					break;

				// Continue for next loop
				cb2->offset1 += cb2->stepSize1;
				cb2->offset2 += cb2->stepSize2;
			}
		}

		// Indicate failure
		return(lnCount);
	}




//////////
//
// Called to retrieve the indicated record
//
//////
	s8* iBuilder_retrieveRecord(SBuilder* builder, u32 tnStepSize, u32 tnN)
	{
		// Make sure it ranges
		if (builder && builder->buffer && (tnStepSize * tnN) <= (builder->populatedLength - tnStepSize))
			return(builder->buffer + (tnStepSize * tnN));	// It does

		// Not in range
		return(NULL);
	}




//////////
//
// Called to append a label and an unsigned value, followed by CR/LF
// "name = 12345[cr/lf]"
//
//////
	s32 iBuilder_append_label_uptr(SBuilder* builder, s8* tcLabelText, uptr udata)
	{
		s32	lnStart;
		s8	buffer[32];


		// Make sure our environment's sane
		if (builder && tcLabelText)
		{
			// Note our size at the stat
			lnStart = builder->populatedLength;

			// Label
			iBuilder_appendData(builder, tcLabelText, (s32)strlen(tcLabelText));

			// Equals
			iBuilder_appendData(builder, " = ", 3);

			// Value
			sprintf(buffer, "%u\0", (u32)udata);
			iBuilder_appendData(builder, buffer, (s32)strlen(buffer));

			// CR/LF
			iBuilder_appendCrLf(builder);

			// Indicate how many bytes were written
			return(builder->populatedLength - lnStart);

		} else {
			// Failure
			return(0);
		}
	}




//////////
//
// Called to append a label and a signed value, followed by CR/LF
// "name = 12345[cr/lf]"
//
//////
	s32 iBuilder_append_label_sptr(SBuilder* builder, s8* tcLabelText, sptr sdata)
	{
		s32	lnStart;
		s8	buffer[32];


		// Make sure our environment's sane
		if (builder && tcLabelText)
		{
			// Note our size at the stat
			lnStart = builder->populatedLength;

			// Label
			iBuilder_appendData(builder, tcLabelText, (s32)strlen(tcLabelText));

			// Equals
			iBuilder_appendData(builder, " = ", 3);

			// Value
			sprintf(buffer, "%d\0", (s32)sdata);
			iBuilder_appendData(builder, buffer, (s32)strlen(buffer));

			// CR/LF
			iBuilder_appendCrLf(builder);

			// Indicate how many bytes were written
			return(builder->populatedLength - lnStart);

		} else {
			// Failure
			return(0);
		}
	}




//////////
//
// Called to append a label and some text, followed by CR/LF
// "name = text[cr/lf]"
//
//////
	s32 iBuilder_append_label_text(SBuilder* builder, s8* tcLabelText, s8* tcText)
	{
		s32	lnStart;


		// Make sure our environment's sane
		if (builder && tcLabelText)
		{
			// Note our size at the stat
			lnStart = builder->populatedLength;

			// Label
			iBuilder_appendData(builder, tcLabelText, (s32)strlen(tcLabelText));

			// Equals
			iBuilder_appendData(builder, " = ", 3);

			// Text
			iBuilder_appendData(builder, tcText, (s32)strlen(tcText));

			// CR/LF
			iBuilder_appendCrLf(builder);

			// Indicate how many bytes were written
			return(builder->populatedLength - lnStart);

		} else {
			// Failure
			return(0);
		}
	}




//////////
//
// Called to append the datum
//
//////
	s32 iBuilder_append_label_datum(SBuilder* builder, s8* tcLabelText, SDatum* datum)
	{
		s32	lnStart;


		// Make sure our environment's sane
		if (builder && tcLabelText && datum && datum->_data && datum->length > 0)
		{
			// Note our size at the stat
			lnStart = builder->populatedLength;

			// Label
			iBuilder_appendData(builder, tcLabelText, (s32)strlen(tcLabelText));

			// Equals
			iBuilder_appendData(builder, " = ", 3);

			// Text
			iBuilder_appendData(builder, datum->data_s8, datum->length);

			// CR/LF
			iBuilder_appendCrLf(builder);

			// Indicate how many bytes were written
			return(builder->populatedLength - lnStart);

		} else {
			// Failure
			return(0);
		}
	}




//////////
//
// Called to append a label and a logical value as "true" or "false", followed by CR/LF
// "name = true[cr/lf]"
//
//////
	s32 iBuilder_append_label_logical(SBuilder* builder, s8* tcLabelText, bool tlValue)
	{
		s32	lnStart;


		// Make sure our environment's sane
		if (builder && tcLabelText)
		{
			// Note our size at the stat
			lnStart = builder->populatedLength;

			// Label
			iBuilder_appendData(builder, tcLabelText, (s32)strlen(tcLabelText));

			// Equals
			iBuilder_appendData(builder, " = ", 3);

			// True/false
			iBuilder_appendData(builder, ((tlValue) ? "true" : "false"), ((tlValue) ? 4 : 5));

			// CR/LF
			iBuilder_appendCrLf(builder);

			// Indicate how many bytes were written
			return(builder->populatedLength - lnStart);

		} else {
			// Failure
			return(0);
		}
	}
