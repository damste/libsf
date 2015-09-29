//////////
//
// /libsf/source/vjr/source/datum/datum.cpp
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
// Version 0.57
// Copyright (c) 2014 by Rick C. Hodgin
//////
// Last update:
//     Nov.27.2014
//////
// Change log:
//     Nov.27.2014 - Initial creation
//////
//
// This document is released as Liberty Software under a Repeat License, as governed
// by the Public Benefit License v1.0 or later (PBL).
//
// The PBL is a public domain license with a caveat:  self accountability unto God.
// You are free to use, copy, modify and share this software for any purpose, however,
// it is the desire of those working on this project that the software remain open.
// It is our request that you maintain it that way.  This is not a legal request unto
// our court systems, but rather a personal matter between you and God.  Our talents
// were received from God, and given to you through this forum.  And it is our wish
// that those talents reach out to as many as possible in a form allowing them to wield
// this content for their own betterment, as you are now considering doing.  And whereas
// we could've forced the issue through something like a copyleft-protected release, the
// truth is we are all giving an account of our lives unto God continually by the daily
// choices we make.  And here again is another case where you get to demonstrate your
// character unto God, and unto your fellow man.
//
// Jesus came to this Earth to set the captives free, to save men's eternal souls from
// the punishment demanded by our sin.  Each one of us is given the opportunity to
// receive Him in this world and be saved.  Whether we choose to receive Him, and follow
// Him, and purpose our lives on the goals He has for each of us (all of which are
// beneficial for all involved), is one way we reveal our character continually.  God
// sees straight through to the heart, bypassing all of the words, all of the facades.
// He is our Creator, and He knows who we are truly.
//
// Jesus is called "Christ" because He saves men from the eternal flames of Hell, the
// just punishment of rebellion against God (rebellion against truth) by eternal beings,
// which each of us are.
//
// Do not let His free gift escape you because of some desire to shortcut what is right
// in your life. Instead, do what is right, and do it because He is who He is, and what
// He has done to save us from such a fate.  Demonstrate to Him, to me, and to all of
// mankind, and to all of the Heavenly hosts, exactly who you are on the inside.  Receive
// Jesus Christ into your heart, learn of Him, of how He came here to guide us into that
// which is of His Kingdom and will be forever hereafter we leave this world.  Do this,
// and live.
//
// Every project released by Liberty Software Foundation will include a copy of the
// pbl.txt document, which can be found at http://www.libsf.org/licenses/.
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
//  _____          _
// |  __ \        | |
// | |  | |  __ _ | |_  _   _  _ __ ___
// | |  | | / _` || __|| | | || '_ ` _ \
// | |__| || (_| || |_ | |_| || | | | | |
// |_____/  \__,_| \__| \__,_||_| |_| |_|
// Datum --- Data w/allocation and length
//
//////////




//////////
//
// Datum storage
//
//////
	void iDatum_allocateSpace(SDatum* datum, s32 dataLength)
	{
		// Make sure our environment is sane
		if (datum)
		{
			if (datum->data && datum->length != dataLength)
			{
				// Release anything that's already there
				iiDatum_delete(datum);
			}

			// Allocate the space
			datum->data = (s8*)malloc(max(dataLength, 1) + 1);

			// Set the length
			datum->length = dataLength;

			// Initialize
			if (datum->data && dataLength)
				memset(datum->data, 0, dataLength);

			// NULL-terminate
			datum->data_s8[max(dataLength, 1)] = 0;
		}
	}

	SDatum* iDatum_allocate(cu8* data, s32 dataLength)
	{
		return(iDatum_allocate((u8*)data, dataLength));
	}

	SDatum* iDatum_allocate(u8* data, s32 dataLength)
	{
		SDatum* datumNew;


		// Allocate our new datum
		datumNew = (SDatum*)malloc(sizeof(SDatum));
		if (datumNew)
		{
			// Initialize
			memset(datumNew, 0, sizeof(SDatum));

			// Copy over the content
			if (data)
			{
				// We may need to set the length
				if (dataLength < 0)
					dataLength = (s32)strlen((s8*)data);

				// Initialize
				memset(datumNew, 0, sizeof(SDatum));

				// Populate
				iDatum_duplicate(datumNew, data, dataLength);
			}
		}

		// Indicate our status
		return(datumNew);
	}

	void iDatum_duplicate(SDatum* datum, u8* data, s32 dataLength)
	{
		// Make sure our environment is sane
		if (datum && data)
		{
			// We may need to set the length
			if (dataLength < 0)
				dataLength = (s32)strlen((s8*)data);

			// Release anything that's already there
			iiDatum_delete(datum);

			// Store the new data
			// Allocate one extra byte for a trailing NULL
			datum->data = (s8*)malloc(max(dataLength, 1) + 1);

			// Copy over if we were successful
			if (datum->data && dataLength > 0)
				memcpy(datum->data, data, dataLength);

			// Store the new length
			datum->length = dataLength;
			datum->data[max(dataLength, 1)] = 0;
		}
	}

	void iDatum_duplicate(SDatum* datum, s8* data, s32 dataLength)
	{
		iDatum_duplicate(datum, (u8*)data, dataLength);
	}

	void iDatum_duplicate(SDatum* datum, cu8* data, s32 dataLength)
	{
		iDatum_duplicate(datum, (u8*)data, dataLength);
	}

	void iDatum_duplicate(SDatum* datum, cs8* data, s32 dataLength)
	{
		iDatum_duplicate(datum, (u8*)data, dataLength);
	}

	void iDatum_duplicate(SDatum* datumDst, SDatum* datumSrc)
	{
		// Make sure our environment is sane
		if (datumDst && datumSrc && datumSrc->data)
			iDatum_duplicate(datumDst, datumSrc->data_u8, datumSrc->length);
	}

	void iDatum_duplicate_fromComp(SDatum* datum, SComp* comp)
	{
		// Make sure our environment is sane
		if (datum && comp && comp->line && comp->line->sourceCode && comp->line->sourceCode->data_cs8 && comp->length != 0)
			iDatum_duplicate(datum, comp->line->sourceCode->data_cs8 + comp->start, comp->length);
	}

	void iiDatum_duplicate_fromComp(SDatum* datum, SComp* comp)
	{
		iDatum_duplicate(datum, comp->line->sourceCode->data_cs8 + comp->start, comp->length);
	}

	bool iDatum_resize(SDatum* datum, s32 newDataLength)
	{
		s8* ptr;


		// Make sure our environment is sane
		if (datum && newDataLength != 0)
		{
			if (datum->length == newDataLength)
				return(true);		// It's already the same length

			// Allocate our new block
			ptr = (s8*)malloc(newDataLength + 1);
			if (ptr)
			{
				// Copy everything that will fit
				memcpy(ptr, datum->data, min(newDataLength, datum->length));

				// Fill the remainder with NULLs if any
				if (newDataLength > datum->length)
					memset(ptr + datum->length, 0, newDataLength - datum->length);

				// Null-terminate
				ptr[newDataLength] = 0;

				// Delete the old data
				if (datum->data)
					free(datum->data);

				// And populate with the new data
				datum->data		= ptr;
				datum->length	= newDataLength;

				// All done
				return(true);

			} else {
				// Failure
				return(false);
			}

		} else {
			// No data to work with
			return(false);
		}
	}

	// Returns -1, 0, or 1 (indicating left is less than, equal to, or greater than right)
	s32 iDatum_compare(SDatum* datumLeft, SDatum* datumRight)
	{
		s32 lnResult;


		// Default to invalid data
		lnResult = -2;

		// Make sure our environment is sane
		if (datumLeft && datumLeft->data && datumLeft->length != 0 && datumRight && datumRight->data && datumRight->length > 0)
		{
			// Do a standard compare
			lnResult = _memicmp(datumLeft->data, datumRight->data, min(datumLeft->length, datumRight->length));
		}

		// Indicate our result
		return(lnResult);
	}

	s32 iDatum_compare(SDatum* datumLeft, s8* data, s32 dataLength)
	{
		s32 lnResult;


		// Default to invalid data
		lnResult = -2;

		// Make sure our environment is sane
		if (datumLeft && datumLeft->data && datumLeft->length != 0 && data)
		{
			// Make sure our length is set
			if (dataLength < 0)
				dataLength = (s32)strlen(data);

			// Do a standard compare
			lnResult = _memicmp(datumLeft->data, data, min(datumLeft->length, dataLength));
		}

		// Indicate our result
		return(lnResult);
	}

	s32 iDatum_compare(SDatum* datumLeft, cs8* data, s32 dataLength)
	{
		return(iDatum_compare(datumLeft, (s8*)data, dataLength));
	}

	s32 iDatum_compare(SDatum* datumLeft, u8*  data, s32 dataLength)
	{
		return(iDatum_compare(datumLeft, (s8*)data, dataLength));
	}

	s32 iDatum_compare(SDatum* datumLeft, cu8* data, s32 dataLength)
	{
		return(iDatum_compare(datumLeft, (s8*)data, dataLength));
	}

	void iDatum_delete(SDatum* datum, bool tlDeleteSelf)
	{
		// Make sure our environment is sane
		if (datum)
		{
			// Delete the content
			iiDatum_delete(datum);

			// Delete self if need be
			if (tlDeleteSelf)
				free(datum);
		}
	}

	void iiDatum_delete(SDatum* datum)
	{
		// Make sure our environment is sane
		if (datum->data)
		{
			free(datum->data);
			datum->data = NULL;
		}

		// Reset the length to zero
		datum->length = 0;
	}
