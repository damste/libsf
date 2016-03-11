//////////
//
// /libsf/utils/common/cpp/fifo.cpp
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
// Copyright (c) 2014-2015 by Rick C. Hodgin
//////
// Last update:
//     Dec.28.2015
//////
// Change log:
//     Dec.28.2015 - Initial creation
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
// 	  ______  _____  ______  ____  
// 	 |  ____||_   _||  ____|/ __ \ 
// 	 | |__     | |  | |__  | |  | |
// 	 |  __|    | |  |  __| | |  | |
// 	 | |      _| |_ | |    | |__| |
// 	 |_|     |_____||_|     \____/
// FIFO -- First In, First Out storage
//////////

#ifndef __FIFO_H_
#include "fifo.h"
#endif




//////////
//
// Called to push an item onto the FIFO stack
//
//////
	SFIFO* iFifo_push(SDatum* datum, bool tlMakeReference)
	{
		SFIFO* fifo;


		// Make sure our environment is sane
		fifo = NULL;
		if (datum && datum->data._data && datum->length > 0)
		{
			// Make sure we have a root
			if (!gsRootFifo)
				iBuilder_createAndInitialize(&gsRootFifo, sizeof(SDatum) * 64);

			// Make sure our root is valid
			if (gsRootFifo)
			{
				// Append a new record
				fifo = (SFIFO*)iBuilder_allocateBytes(gsRootFifo, sizeof(SDatum));
				if (fifo)
				{
					// Set our reference flag
					fifo->isReference = tlMakeReference;

					// Refer or copy
					if (tlMakeReference)		iDatum_duplicate_byRef(&fifo->datum, datum);		// Make a reference to the data
					else						iDatum_duplicate(&fifo->datum, datum);				// Copy the data
				}
			}
		}

		// Indicate our result
		return(fifo);
	}




//////////
//
// Called to pop an item off the FIFO stack
//
//////
	s32 iFifo_peek(SDatum& datum, bool& tlIsReference)
	{
		// Do we have any data?
		if (gsRootFifo && gsRootFifo->buffer && gsRootFifo->populatedLength >= sizeof(SDatum))
		{
			// Set our flag
			tlIsReference = ((SFIFO*)(gsRootFifo->buffer))->isReference;

			// Copy our output
			memcpy(&datum, gsRootFifo->buffer, sizeof(SDatum));
		}

		// Indicate how many remain
		return(((gsRootFifo) ? gsRootFifo->populatedLength / sizeof(SDatum) : 0));
	}

	s32 iFifo_pop(SDatum& datum, bool& tlIsReference)
	{
		// Do we have any data?
		if (gsRootFifo && gsRootFifo->buffer && gsRootFifo->populatedLength >= sizeof(SDatum))
		{
			// Set our flag
			tlIsReference = ((SFIFO*)(gsRootFifo->buffer))->isReference;

			// Copy our output
			memcpy(&datum, gsRootFifo->buffer, sizeof(SDatum));

			// Remove from the stack
			iBuilder_delete(gsRootFifo, 0, sizeof(SDatum));
		}

		// Indicate how many remain
		return(((gsRootFifo) ? gsRootFifo->populatedLength / sizeof(SDatum) : 0));
	}
