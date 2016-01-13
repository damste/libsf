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
	void iBuilder_verifySizeForNewBytes(SBuilder* buffRoot, u32 tnDataLength)
	{
		// Make sure our environment is sane
		if (buffRoot && tnDataLength != 0)
		{
			// Repeatedly allocate our allocation size until we get big enough
			while (buffRoot->data_s8)
			{
				// Are we there yet?
				if (buffRoot->populatedLength + tnDataLength <= buffRoot->allocatedLength)
					return;		// We're good

				// If we get here, we need to allocate more space
				// Reallocate and continue
				buffRoot->data_s8			= (s8*)realloc(buffRoot->data_s8, buffRoot->allocatedLength + buffRoot->allocateBlockSize);
				buffRoot->allocatedLength	+= buffRoot->allocateBlockSize;

				// Initialize the added block
				if (buffRoot->data_s8)
					memset(buffRoot->data_s8 + buffRoot->allocatedLength - buffRoot->allocateBlockSize, 0, buffRoot->allocateBlockSize);
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
	void iBuilder_createAndInitialize(SBuilder** buffRoot, u32 tnAllocationBlockSize)
	{
		SBuilder*	buffNew;


		// See if they want to use the default size
		if (tnAllocationBlockSize == (u32)-1)
			tnAllocationBlockSize = 16384;		// Default to a 16KB allocation size

		// Make sure our environment is sane
		if (buffRoot && tnAllocationBlockSize != 0)
		{
			buffNew = (SBuilder*)malloc(sizeof(SBuilder));
			if (buffNew)
			{
				// Initialize
				memset(buffNew, 0, sizeof(SBuilder));

				// Store the pointer
				*buffRoot = buffNew;

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
	bool iBuilder_isPointer(SBuilder* buffRoot, uptr testptr, void** outPtr)
	{
		if (buffRoot)
		{
			// It must fall in [range) to be considered valid
			if (testptr >= buffRoot->_data && testptr < (buffRoot->_data + buffRoot->populatedLength))
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
	cs8* iBuilder_appendData(SBuilder* buffRoot, SDatum* data)
	{
		// Make sure there's something to update
		if (buffRoot && data && data->data && data->length > 0)
			return((cs8*)iBuilder_appendData(buffRoot, data->data_cu8, data->length));

		// Return our original input
		return(NULL);
	}

	cs8* iBuilder_appendData(SBuilder* buffRoot, cs8* tcData, u32 tnDataLength)
	{
		return((cs8*)iBuilder_appendData(buffRoot, (cu8*)tcData, tnDataLength));
	}

	cu8* iBuilder_appendData(SBuilder* buffRoot, cu8* tcData, u32 tnDataLength)
	{
		// Make sure our environment is sane
		if (buffRoot)
		{
			// If they want us to populate the length, do so
			if (tnDataLength == (u32)-1)
				tnDataLength = (u32)strlen((s8*)tcData);

			// If there's anything to do, do it
			if (tnDataLength != 0)
			{
				// Make sure this much data will fit there in the buffer
				iBuilder_verifySizeForNewBytes(buffRoot, tnDataLength);

				// If we're still valid, proceed with the copy
				if (buffRoot->data_s8)
				{
					// Copy the original content
					if (tcData)			memcpy(buffRoot->data_s8 + buffRoot->populatedLength, (s8*)tcData, tnDataLength);
					else				memset(buffRoot->data_s8 + buffRoot->populatedLength, 0, tnDataLength);

					// Increase the size
					buffRoot->populatedLength += tnDataLength;
				}
			}
			// Indicate where the start of that buffer is
			return(buffRoot->data_u8 + buffRoot->populatedLength - tnDataLength);
		}
		// If we get here, things are bad
		return(NULL);
	}




//////////
//
// Appends the indicated 32-bit value.
//
//////
	u8* iBuilder_append_uptr(SBuilder* buffRoot, uptr tnValue)
	{
		// Make sure our environment is sane
		if (buffRoot)
		{
			// Make sure this much data will fit there in the buffer
			iBuilder_verifySizeForNewBytes(buffRoot, sizeof(uptr));

			// Copy the data
			if (buffRoot->data_s8)
			{
				*(uptr*)(buffRoot->data_s8 + buffRoot->populatedLength) = tnValue;
				buffRoot->populatedLength += sizeof(uptr);
			}

			// Indicate where the start of that buffer is
			return(buffRoot->data_u8 + buffRoot->populatedLength - sizeof(uptr));
		}
		// If we get here, things are bad
		return(NULL);
	}




//////////
//
// Called to append a CR+LF to the builder
//
//////
	u8* iBuilder_appendCrLf(SBuilder* buffRoot)
	{
		return((u8*)iBuilder_appendData(buffRoot, (cu8*)"\r\n", 2));
	}




//////////
//
// Called to delete the indicated bytes
//
//////
	void iBuilder_delete(SBuilder* buffRoot, u32 tnStartOffset, u32 tnDeleteLength)
	{
		if (buffRoot && tnStartOffset <= buffRoot->populatedLength)
		{
			// Move any data that was after the deleted block forward in the block
			if (tnStartOffset + tnDeleteLength < buffRoot->populatedLength)
			{
				memmove(buffRoot->buffer + tnStartOffset,
						buffRoot->buffer + tnStartOffset + tnDeleteLength,
						buffRoot->populatedLength - tnStartOffset - tnDeleteLength);
			}

			// Indicate the new size
			buffRoot->populatedLength -= tnDeleteLength;
		}
	}




//////////
//
// Called to reset the buffer to 0 bytes
//
//////
	void iBuilder_reset(SBuilder* buffRoot)
	{
		if (buffRoot && buffRoot->populatedLength != 0)
		{
			memset(buffRoot->buffer, 0, buffRoot->totSize);
			buffRoot->populatedLength = 0;
		}
	}




//////////
//
// Called to reset the buffer to 0 bytes
//
//////
	void iBuilder_rewind(SBuilder* buffRoot)
	{
		if (buffRoot)
			buffRoot->populatedLength = 0;
	}




//////////
//
// Called to allocate bytes in the builder, but not yet populate them with anything,
// nor initializing them.  If you would like to allocate a block that is initialized
// to something, or to all 0s, then use iBuilder_appendData().
//
//////
	s8* iBuilder_allocateBytes(SBuilder* buffRoot, u32 tnDataLength)
	{
		// Make sure our environment is sane
		if (buffRoot)
		{
			// Make sure this much data will fit there in the buffer
			if (tnDataLength != 0)
			{
				iBuilder_verifySizeForNewBytes(buffRoot, tnDataLength);
				buffRoot->populatedLength += tnDataLength;
			}

			// Indicate where the start of that buffer is
			return(buffRoot->data_s8 + buffRoot->populatedLength - tnDataLength);
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
	void iBuilder_backoffTrailingWhitespaces(SBuilder* buffRoot)
	{
		if (buffRoot && buffRoot->data_s8)
		{
			// Back off so long as there are whitespaces
			while ((s32)buffRoot->populatedLength > 0 && (buffRoot->data_s8[buffRoot->populatedLength - 1] == 32 || buffRoot->data_s8[buffRoot->populatedLength - 1] == 9))
			{
				// Reset the data there to the expected NULLs
				buffRoot->data_s8[buffRoot->populatedLength - 1] = 0;

				// Backup one
				--buffRoot->populatedLength;
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
	void iBuilder_setSize(SBuilder* buffRoot, u32 tnBufferLength)
	{
		s8* lcNew;


		// Make sure our environment is sane
		if (buffRoot)
		{
			//////////
			// See if they want to make it whatever the populated size is
			//////
				if (tnBufferLength == (u32)-1)
					tnBufferLength = buffRoot->populatedLength;


			//////////
			// See if they're releasing everything
			//////
				if (tnBufferLength == 0)
				{
					//////////
					// They are freeing everything
					//////
						free(buffRoot->data_s8);
						buffRoot->data_s8			= NULL;
						buffRoot->populatedLength	= 0;
						buffRoot->allocatedLength	= 0;


				} else if (tnBufferLength != buffRoot->allocatedLength) {
					//////////
					// They are resizing
					//////
						lcNew = (s8*)realloc(buffRoot->data_s8, tnBufferLength);
						if (lcNew)
						{
							//////////
							// Set the allocated length
							//////
								buffRoot->data_s8			= lcNew;
								buffRoot->allocatedLength	= tnBufferLength;


							//////////
							// If our populated length no longer fits into the new allocated space, then adjust it down
							//////
								if (buffRoot->populatedLength > buffRoot->allocatedLength)
									buffRoot->populatedLength = buffRoot->allocatedLength;		// Bring the populated area down to the new size

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
	void iBuilder_freeAndRelease(SBuilder** buffRoot)
	{
		SBuilder* buffDelete;


		// Make sure our environment is sane
		if (buffRoot && *buffRoot)
		{
			// Copy our *buffRoot pointer to local space so we can "appear" to kill it before it's actually killed
			buffDelete	= *buffRoot;
			*buffRoot	= NULL;

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
	u32 iBuilder_asciiWriteOutFile(SBuilder* buffRoot, cu8* tcPathname, bool tlAppend)
	{
		FILE* lfh;


		// Make sure there's something to write
		if (buffRoot && tcPathname)
		{
			// Try to create the file
			lfh = fopen((s8*)tcPathname, ((tlAppend) ? "ab+" : "wb+"));
			if (lfh)
			{
				// Write out the data if need be
				if (buffRoot->data_s8 && buffRoot->populatedLength != 0)
				{
					fwrite(buffRoot->data_s8, 1, buffRoot->populatedLength, lfh);
					fclose(lfh);
					return(buffRoot->populatedLength);
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
	bool iBuilder_asciiReadFromFile(SBuilder** buffRoot, cu8* tcPathname)
	{
		u32		lnSize, lnNumread;
		FILE*	lfh;


		// Make sure our environment is sane
		if (buffRoot && tcPathname)
		{
			//////////
			// If we don't have a buffer, create one
			//////
				if (!*buffRoot)
					iBuilder_createAndInitialize(buffRoot, -1);


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
					iBuilder_verifySizeForNewBytes(*buffRoot, lnSize);


				//////////
				// Read in the content
				//////
					lnNumread						= (u32)fread((*buffRoot)->data_s8 + (*buffRoot)->populatedLength, 1, lnSize, lfh);
					(*buffRoot)->populatedLength	+= min(lnNumread, lnSize);


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
	void iBuilder_compactData(SBuilder* buffRoot, u32 tnStart, u32 tnStride, u32 tnCompactCallbackFunction)
	{
		u32 lnI, lnCopyTo;
		union
		{
			// This callback is used to execute a test determining if each entry can be compacted
			u32		_compactCallbackFunction;
			bool	(*compactCallbackFunction)	(void* ptr);
		};


		// Make sure our environment is sane
		if (buffRoot && buffRoot->data_s8 && buffRoot->populatedLength >= tnStart)
		{
			// Setup our callback function
			_compactCallbackFunction = tnCompactCallbackFunction;

			// Iterate through each pointer
			lnCopyTo = tnStart;
			for (lnI = tnStart; lnI < buffRoot->populatedLength; lnI += tnStride)
			{
				if (!compactCallbackFunction(buffRoot->data_s8 + lnI))
				{
					// We are keeping this one
					if (lnCopyTo != lnI)
						memcpy(buffRoot->data_s8 + lnCopyTo, buffRoot->data_s8 + lnI, tnStride);

					// Move to next one
					lnCopyTo += tnStride;
				}
			}
			// When we get here, everything's been compacted
			if (lnCopyTo < buffRoot->populatedLength)
				iBuilder_setSize(buffRoot, lnCopyTo);
		}
	}




//////////
//
// Called to insert bytes at the indicated location.
//
//////
	s8* iBuilder_insertBytes(SBuilder* buffRoot, u32 tnStart, u32 tnLength)
	{
		u32		lnI, lnStop;
		s8*		buffNew;
		s8*		lcSrc;
		s8*		lcDst;


		//////////
		// Make sure our environment is sane
		//////
			buffNew = NULL;
			if (buffRoot && buffRoot->data_s8)
			{
				//////////
				// Are we adding to the end?
				//////
					if (buffRoot->populatedLength == tnStart)
						return(iBuilder_allocateBytes(buffRoot, tnLength));		// We're appending to the end


				//////////
				// If we get here, we're inserting in the middle
				// We go ahead and allocate the new bytes
				//////
					buffNew = iBuilder_allocateBytes(buffRoot, tnLength);
					if (buffNew)
					{
						//////////
						// Now, we have to copy everything backwards so we don't propagate a portion repeatedly
						//////
							lcSrc	= buffRoot->data_s8 + buffRoot->populatedLength - tnLength - 1;
							lcDst	= buffRoot->data_s8 + buffRoot->populatedLength - 1;
							lnStop	= buffRoot->populatedLength - tnStart - tnLength;


						//////////
						// Copy until we're done
						//////
							for (lnI = 0; lnI < lnStop; lnI++, lcDst--, lcSrc--)
								*lcDst = *lcSrc;


						//////////
						// Indicate where our new record is
						//////
							buffNew = buffRoot->data_s8 + tnStart;
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
	u32 iBuilder_binarySearch(SBuilder* haystack, s8* tcNeedle, u32 tnNeedleLength, bool* tlFound, bool tlInsertIfNotFound)
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
			if (haystack && haystack->data_s8 && haystack->populatedLength % tnNeedleLength == 0)
			{
				//////////
				// Perform a binary search
				//////
					lnTop = 0;
					lnBot = (haystack->populatedLength / tnNeedleLength) - 1;
					lnMid = max((lnTop + lnBot) / 2, lnTop);
					while (lnTop <= lnBot)
					{
						// Position our search pointer
						lnMid = (lnTop + lnBot) / 2;

						// See if it's above or below this position
						lnResult = memcmp(haystack->data_s8 + (lnMid * tnNeedleLength), tcNeedle, tnNeedleLength);
						if (lnResult == 0)
						{
							// Found, but this may not be the first one, we need to creep backwards to find the first
							if (lnMid == lnBot)
							{
								// Success!
								if (tlFound)
									*tlFound = true;

								// Indicate our entry
								return(lnMid * tnNeedleLength);
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
						buffNew = iBuilder_insertBytes(haystack, lnMid * tnNeedleLength, tnNeedleLength);
						if (buffNew)
						{
							// We can copy over and insert it
							memcpy(buffNew, tcNeedle, tnNeedleLength);

							// Indicate where it exists in the list
							return(lnMid * tnNeedleLength);

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
// Called to append a label and an unsigned value, followed by CR/LF
// "name = 12345[cr/lf]"
//
//////
	s32 iBuilder_append_label_uptr(SBuilder* buffRoot, s8* tcLabelText, uptr udata)
	{
		s32	lnStart;
		s8	buffer[32];


		// Make sure our environment's sane
		if (buffRoot && tcLabelText)
		{
			// Note our size at the stat
			lnStart = buffRoot->populatedLength;

			// Label
			iBuilder_appendData(buffRoot, tcLabelText, (s32)strlen(tcLabelText));

			// Equals
			iBuilder_appendData(buffRoot, " = ", 3);

			// Value
			sprintf(buffer, "%u\0", udata);
			iBuilder_appendData(buffRoot, buffer, (s32)strlen(buffer));

			// CR/LF
			iBuilder_appendCrLf(buffRoot);

			// Indicate how many bytes were written
			return(buffRoot->populatedLength - lnStart);

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
	s32 iBuilder_append_label_sptr(SBuilder* buffRoot, s8* tcLabelText, sptr sdata)
	{
		s32	lnStart;
		s8	buffer[32];


		// Make sure our environment's sane
		if (buffRoot && tcLabelText)
		{
			// Note our size at the stat
			lnStart = buffRoot->populatedLength;

			// Label
			iBuilder_appendData(buffRoot, tcLabelText, (s32)strlen(tcLabelText));

			// Equals
			iBuilder_appendData(buffRoot, " = ", 3);

			// Value
			sprintf(buffer, "%d\0", sdata);
			iBuilder_appendData(buffRoot, buffer, (s32)strlen(buffer));

			// CR/LF
			iBuilder_appendCrLf(buffRoot);

			// Indicate how many bytes were written
			return(buffRoot->populatedLength - lnStart);

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
	s32 iBuilder_append_label_text(SBuilder* buffRoot, s8* tcLabelText, s8* tcText)
	{
		s32	lnStart;


		// Make sure our environment's sane
		if (buffRoot && tcLabelText)
		{
			// Note our size at the stat
			lnStart = buffRoot->populatedLength;

			// Label
			iBuilder_appendData(buffRoot, tcLabelText, (s32)strlen(tcLabelText));

			// Equals
			iBuilder_appendData(buffRoot, " = ", 3);

			// Text
			iBuilder_appendData(buffRoot, tcText, (s32)strlen(tcText));

			// CR/LF
			iBuilder_appendCrLf(buffRoot);

			// Indicate how many bytes were written
			return(buffRoot->populatedLength - lnStart);

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
	s32 iBuilder_append_label_datum(SBuilder* buffRoot, s8* tcLabelText, SDatum* datum)
	{
		s32	lnStart;


		// Make sure our environment's sane
		if (buffRoot && tcLabelText && datum && datum->data && datum->length > 0)
		{
			// Note our size at the stat
			lnStart = buffRoot->populatedLength;

			// Label
			iBuilder_appendData(buffRoot, tcLabelText, (s32)strlen(tcLabelText));

			// Equals
			iBuilder_appendData(buffRoot, " = ", 3);

			// Text
			iBuilder_appendData(buffRoot, datum->data, datum->length);

			// CR/LF
			iBuilder_appendCrLf(buffRoot);

			// Indicate how many bytes were written
			return(buffRoot->populatedLength - lnStart);

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
	s32 iBuilder_append_label_logical(SBuilder* buffRoot, s8* tcLabelText, bool tlValue)
	{
		s32	lnStart;


		// Make sure our environment's sane
		if (buffRoot && tcLabelText)
		{
			// Note our size at the stat
			lnStart = buffRoot->populatedLength;

			// Label
			iBuilder_appendData(buffRoot, tcLabelText, (s32)strlen(tcLabelText));

			// Equals
			iBuilder_appendData(buffRoot, " = ", 3);

			// True/false
			iBuilder_appendData(buffRoot, ((tlValue) ? "true" : "false"), ((tlValue) ? 4 : 5));

			// CR/LF
			iBuilder_appendCrLf(buffRoot);

			// Indicate how many bytes were written
			return(buffRoot->populatedLength - lnStart);

		} else {
			// Failure
			return(0);
		}
	}
