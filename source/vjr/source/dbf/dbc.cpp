//////////
//
// /libsf/source/vjr/source/dbf/dbc.cpp
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
// Version 0.58
// Copyright (c) 2014 by Rick C. Hodgin
//////
// Last update:
//     Nov.02.2014
//////
// Change log:
//     Nov.02.2014 - Initial creation
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
//




//////////
// Binary property memo field related structures
/////
	struct SVfpPropertyMemo
	{									///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
										// Offset	Length		Description
										// ------	------		-------------------------------------------------------------------------------------------
		u16			length;				//   0		  2			Length of this entry
		u32			_32bit_value;		//   2		  4			32-bit value which is always the value "00000001"
		u8			dataItem;			//   6		  1			An 8-bit identifier for the data item the value is assigned to
		u8			value;				//   7		  1			An 8-bit quantity set by the data item
										// Total:  8 bytes
										//
										// Note:  Beyond this structure exists variable-length data.  Each data item
										//        has its length determined by the length of this entire sub-structure,
										//        less the sizeof(SVfpPropertyMemo), less 1 more (for trailing NULL).
										///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	};

	// Used to store a linked-list to 
	struct SEntry
	{
		SEntry*		next;				// Pointer to the next entry, NULL if last in chain
		u8			dataItem;			// The data item identifier
		u8*			data;				// The physical data for the dataItem itself
		u32			dataLength;			// Length of data
	};




//////////
// Globally used variable for DBC
/////
	SEntry*	gsRootDbc = NULL;				// Root of the memo field's numerous entries









//////////
//
// The following functions load and parse the DBC's "property" binary memo field.
// The structure within the binary memo field is comprised of a fixed minimal structure
// form, with longer-than-one-byte data items extending beyond that fixed structure,
// making lengthy items a variable data structure.
//
// Note:  This is the "property" memo field from the DBC itself.  It can be loaded for
//        anything, with some known values being identified in the Word document:
//				ViewsTablesIndexesFields.docx
//
/////

	// Reset any previously loaded data
	u32 iDbc_resetPropertyMemo(void)
	{
		u32			lnCount;
		SEntry*		se;
		SEntry*		seNext;

		// Reset 
		se		= gsRootDbc;
		lnCount	= 0;
		while (se)
		{
			// Increase our counter for each item we process
			++lnCount;

			// Grab the next item and reset it
			seNext		= se->next;
			se->next	= NULL;

			// Free this item's entries (if any) and reset it
			if (se->data)
			{
				free(se->data);
				se->data = NULL;
			}

			// Reset its components
			se->dataLength	= 0;
			se->dataItem	= 0;

			// Move to next item (if any)
			se = seNext;
		}
		// When we get here, everything's been reset
		gsRootDbc = NULL;

		// Indicate how many were reset
		return(lnCount);
	}

	// Parse the memo field structure, storing SEntry items to gsRoot for each one found
	u32 iDbc_parsePropertyMemo(s8* memo, u32 lengthMax)
	{
		u8					lcDataItem/*, lcValue*/;
		u16					lnLength;
		u32					lnOffset, lnOtherDataLength, lnCount;
		u8*					lpOtherData;
		SVfpPropertyMemo*	svp;
		SEntry**			seLast;
		SEntry*				seNew;


		// Make sure we have data to process
		if (memo == NULL || lengthMax == 0)
			return(-1);

		// Reset anything that may not have been reset previously
		iDbc_resetPropertyMemo();

		// Grab a pointer to the structure in its proper form
		svp = (SVfpPropertyMemo*)memo;

		// Iterate through every sub-structure entry until we find a null-terminated entry, or reach the max length
		lnOffset	= 0;
		lnCount		= 0;
		seLast		= &gsRootDbc;
		while (*(u8*)svp != 0 && lnOffset < lengthMax)
		{
			++lnCount;
			lnLength		= svp->length;
			lcDataItem		= svp->dataItem;
//			lcValue			= svp->value;

			if (lnOffset + lnLength < lengthMax)
			{	// We can process this one
				// Create the new entry
				seNew = (SEntry*)malloc(sizeof(SEntry));
				if (seNew)
				{	// We're good
					memset(seNew, 0, sizeof(SEntry));
					if (seLast)
					{	// Update the chain
						*seLast = seNew;

						// The chain will now proceed from here
						seLast = &seNew->next;
					}

					// Set its options
					seNew->next			= NULL;
					seNew->dataItem		= lcDataItem;

					// Grab pointers to the sub-structure's data
					lpOtherData			= (u8*)svp + sizeof(SVfpPropertyMemo) - 1;
					lnOtherDataLength	= lnLength - sizeof(SVfpPropertyMemo) + 1;

					// Allocate the variable data portion
					seNew->data			= (u8*)malloc(lnOtherDataLength);
					if (seNew->data)
					{	// Set the length and copy the item 
						seNew->dataLength	= lnOtherDataLength;
						memcpy(seNew->data, lpOtherData, lnOtherDataLength);
					}
				}
			}

			// Move to the next sub-structure entry
			lnOffset	+= lnLength;
			svp			=  (SVfpPropertyMemo*)((u8*)svp + lnLength);
		}
		return(lnCount);
	}

	// Returns the entries one by one (stored into buffer, return value is length of item)
	// Note:  Index value of 1 is first item.
	// Note:  asInt returns two values, the value of the data with the endian as big-endian, then as little-endian.
	// Note:  FoxPro uses big-endian often for some reason.
	u32 iDbc_getPropertyMemo_byIndex(u32 index, s8* code4, s8* raw, u32 rawLength, s8* asInt, u32 asIntLength)
	{
		u32			lnCount, lnLength, lnValue;
		SEntry*		se;
		s8			buffer[32];

		// Iterate through our linked list until we find the index they specify
		lnCount	= 0;
		se		= gsRootDbc;
		while (se)
		{
			++lnCount;
			if (lnCount == index)
			{	// This is our man


				// Store the dataItem code as (0x04) for example
				if (code4)
				{
					sprintf(buffer, "0x%02x\000", (u32)se->dataItem);
					memcpy(code4, buffer, 4);
				}


				// Copy the raw contents
				if (raw)
				{
					// Initialize the destination
					memset(raw, 32, rawLength);

					// Copy it (or as much of it as we can)
					memcpy(raw, se->data, (rawLength >= se->dataLength) ? se->dataLength : rawLength);
				}


				// Copy it converted to an integer (if possible)
				if (asInt)
				{
					// Initialize the destination
					memset(asInt, 32, asIntLength);

					// Based on the dataLength, we can either convert it as an integer, or not
					if (se->dataLength <= 4)
					{	// Convert the value to int (if it's 4-bytes or less) and store it

						if (se->dataLength == 1)
							lnValue	= (u32) *((u8*)se->data);				// It's 8-bits (1 byte)
						else if (se->dataLength == 2)
							lnValue	= (u32)*((u16*)se->data);				// It's 16-bits (2 bytes)
						else if (se->dataLength == 3)
							lnValue	= (*((u32*)se->data) & 0xffffff);		// It's 24-bits (3 bytes)
						else
							lnValue	= iiSwapEndian32(*((u32*)se->data));	// It's 32-bits (4 bytes, stored as big-endian)

						sprintf(buffer, "%u\000", lnValue);
						lnLength = (u32)strlen(buffer);

						// Copy it (or as much of it as we can)
						memcpy(asInt, buffer, (asIntLength >= lnLength) ? lnLength : asIntLength);
					}
				}

				return(se->dataLength);
			}

			// Move to next item
			se = se->next;
		}
		// If we get here, the index specified wasn't found
		return(0);
	}




//////////
//
// Called to validate the datbase.  If sem is provided, output from validate is
// routed to that buffer.  If win is provided, that win is redrawn as the
// validation continues.
//
// Returns:
//		Number of changes made (if tlRecover), or would've been made (if !tlRecover).
//
//////
	s32 iDbc_validate(SWorkArea* wa, bool tlRecover, SEM* sem, SWindow* win)
	{
// TODO:  Write the DBC validation algorithm.  A small task I assure you. :-)
		return(-1);
	}
