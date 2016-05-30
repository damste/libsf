//////////
//
// /libsf/source/vjr/source/debugger/jdebic/jdebic.cpp
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
// Copyright (c) 2015 by Rick C. Hodgin
//////
// Last update:
//     Apr.10.2015
//////
// Change log:
//     Apr.10.2015 - Initial creation
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
//	       _  _____         _      _   _____
//	      | ||  __ \       | |    (_) / ____|
//	      | || |  | |  ___ | |__   _ | |
//	  _   | || |  | | / _ \| '_ \ | || |
//	 | |__| || |__| ||  __/| |_) || || |____
//	  \____/ |_____/  \___||_.__/ |_| \_____|
//				JDebi Companion
//			A Remote Debug Assist Tool
//




//////////
//
// Called to send over debugging information for the current context
//
//////
	void JDebiC_debug(SWindow* win, SObject* obj)
	{
		SDatum		data;
		SBuilder*	builder;
		SBuilder*	items;


// Temporarily disabled
return;
		// Are we connected?
		if (iJDebiC_connect() && (win || obj))
		{

			//////////
			// Initialize
			//////
				iBuilder_createAndInitialize(&builder, -1);
				data.data_s8 = builder->buffer;


			//////////
			// thisCode
			//////
				iJDebiC_thisCode(builder, items, &gsThisCode[gnThisCode]);
				data.length = builder->populatedLength;
				iJDebiC_transmit_viaPipe(&data, NULL, _WMJDEBIC_DATA_TYPE_THISCODE);
				iBuilder_rewind(builder);


			//////////
			// win
			//////
				if (win)
				{
					iJDebiC_win(builder, items, win);
					data.length = builder->populatedLength;
					iJDebiC_transmit_viaPipe(&data, NULL, _WMJDEBIC_DATA_TYPE_WIN);
					iBuilder_rewind(builder);
				}


			//////////
			// obj
			//////
				if (obj)
				{
					iJDebiC_obj(builder, items, obj);
					data.length = builder->populatedLength;
					iJDebiC_transmit_viaPipe(&data, NULL, _WMJDEBIC_DATA_TYPE_OBJ);
					iBuilder_rewind(builder);
				}


			//////////
			// Clean house
			//////
				iBuilder_freeAndRelease(&builder);

		}
	}




//////////
//
// Called to send over some text
//
//////
	void JDebiC_text(s8* tcText)
	{
		SDatum data;


		data.data_s8	= tcText;
		data.length		= (s32)strlen(tcText);
		iJDebiC_transmit_viaPipe(&data, NULL, _WMJDEBIC_DATA_TYPE_TEXT);
	}




//////////
//
// Called to send over some data
//
//////
	void JDebiC_data(s8* tcData, s32 tnDataLength)
	{
		SDatum data;


		data.data_s8	= tcData;
		data.length		= tnDataLength;
		iJDebiC_transmit_viaPipe(&data, NULL, _WMJDEBIC_DATA_TYPE_DATA);
	}




//////////
//
// Called to transmit a bitmap.
//
// Note:  Bitmaps must always transmitted without interruption in the order header, info, data.
// Note:  Use an external tnControlId to refresh the presentation as images change over time.
// Note:  This system should be sufficient for sending well over 30 fps transfer rates of full-screen images.
//
//////
	void JDebiC_bmp(SBitmap* bmp, bool tlShowImmediately, u32 tnControlId_ifControlled, bool tlDeleteAfterSend, bool tlDeleteSelf)
	{
		u32		lnId;
		SDatum	data;


		//////////
		// Id control tag
		//////
			lnId		= ((tnControlId_ifControlled == -1) ? iGetNextUid() : tnControlId_ifControlled);
			data.length = lnId;
			iJDebiC_transmit_viaPipe(&data, NULL, _WMJDEBIC_ID_TAG);


		//////////
		// Header
		//////
			data.data_vp	= &bmp->bh;
			data.length		= sizeof(bmp->bh);
			iJDebiC_transmit_viaPipe(&data, NULL, _WMJDEBIC_DATA_TYPE_BITMAP_BH);


		//////////
		// Info
		//////
			data.data_vp	= &bmp->bi;
			data.length		= sizeof(bmp->bi);
			iJDebiC_transmit_viaPipe(&data, NULL, _WMJDEBIC_DATA_TYPE_BITMAP_BI);


		//////////
		// Data
		//////
			data.data_vp	= &bmp->bd;
			data.length		= (bmp->bi.biHeight * bmp->bi.biWidth * bmp->rowWidth);
			iJDebiC_transmit_viaPipe(&data, NULL, _WMJDEBIC_DATA_TYPE_BITMAP_BD);


		//////////
		// Show if need be
		//////
			if (tlShowImmediately)
			{
				data.length = lnId;
				iJDebiC_transmit_viaPipe(&data, NULL, _WMJDEBIC_ID_TAG_PRESENT);
			}


		//////////
		// Delete if need be
		//////
			if (tlDeleteAfterSend)
				iBmp_delete(&bmp, true, tlDeleteAfterSend);

	}




//////////
//
// Called to send over some data for a hex dump
//
//////
	void JDebiC_hexdump(s8* tcData, s32 tnDataLength)
	{
		SDatum data;


		data.data_s8	= tcData;
		data.length		= tnDataLength;
		iJDebiC_transmit_viaPipe(&data, NULL, _WMJDEBIC_DATA_TYPE_HEXDUMP);
	}




//////////
//
// Called to verify we're online, and if not then try to connect
//
//////
	HANDLE iJDebiC_createPipeHandle(cs8* lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile)
	{
//		s32		lnError1, lnError2;
		HANDLE	hPipe;


		//////////
		// Create the indicated pipe
		//////
			hPipe		= CreateFile(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
//			lnError1	= GetLastError();
			if (hPipe != INVALID_HANDLE_VALUE)
			{
				ConnectNamedPipe(hPipe, NULL);
//				lnError2 = GetLastError();
			}


		//////////
		// Indicate our status
		//////
			return(hPipe);

	}




//////////
//
// Called to see if the indicated pointer has already been processed in this iteration
//
//////
	bool iJDebiC_alreadyProcessedItem(SBuilder* items, void* item)
	{
		u32 lnI;


		// Iterate through every item
		for (lnI = 0; lnI < items->populatedLength; lnI += sizeof(item))
		{
			// Is this item already recorded?
			if (*((void**)(items->buffer + lnI)) == item)
				return(true);
		}

		// If we get here, not processed
		return(false);
	}




//////////
//
// Append the indicated item to the list of processed items
//
//////
	void iJDebiC_recordNewItem(SBuilder* items, void* item)
	{
		iBuilder_appendData(items, (cs8*)&item, sizeof(item));
	}




//////////
//
// Validates we're still connected to JDebiC, or tries to connect to it
//
//////
	bool iJDebiC_connect(void)
	{
		bool	llNeedHandles;
		s8		pipeNameOut[_MAX_PATH];


		//////////
		// Locate the existing JDebiC window
		//////
			// Is the window (still) known and viable?
			if (!hwndJDebiC || !IsWindow(hwndJDebiC))
			{
				// Our reference needs updated ... try to find it
				hwndJDebiC		= FindWindow(cgcJDebiCClassName, NULL);
				llNeedHandles	= true;		// If it was found, our handles are now invalid and must be re-requested

			} else {
				// It is known ... see if we have the handles
				llNeedHandles = (handleJDebiCOut == null0);
			}


		//////////
		// Are we still viable?
		//////
			if (!hwndJDebiC)
				return(false);	// Nope


		//////////
		// We are viable, but do we need handles?
		//////
			if (llNeedHandles)
			{
				// Request our number to use for our named pipes
				gnJDebiCOutPipeNumber = SendMessage(hwndJDebiC, _WMJDEBIC_PIPE_REQUEST, 0, 0);

				// Create the pipe names
				sprintf(pipeNameOut, "\\\\.\\pipe\\JDebiC_pipe_%08x\0", gnJDebiCOutPipeNumber);

				// Non-owners connect to an existing pipe
				handleJDebiCOut = (u32)iJDebiC_createPipeHandle(pipeNameOut, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			}


		//////////
		// Check values
		//////
			if (handleJDebiCOut == (u32)INVALID_HANDLE_VALUE)
				handleJDebiCOut = null0;


		//////////
		// Write the output data
		//////
			return((handleJDebiCOut != null0));
	}




//////////
//
// Called to transmit the data to the remote
//
//////
	s32 iJDebiC_transmit_viaPipe(SDatum* data1, SDatum* data2, u32 tnDataType)
	{
		DWORD lnNumwritten1, lnNumwritten2;


		//////////
		// Make sure we're connected
		//////
			lnNumwritten1 = 0;
			lnNumwritten2 = 0;
			if (iJDebiC_connect())
			{
				if (!between(tnDataType, _WMJDEBIC_ID_TAG__MIN, _WMJDEBIC_ID_TAG__MAX))
				{
					// Transmit and signal the transmission
					if (data1)		WriteFile((HANDLE)handleJDebiCOut, data1->data_s8, data1->length, &lnNumwritten1, NULL);
					if (data2)		WriteFile((HANDLE)handleJDebiCOut, data2->data_s8, data2->length, &lnNumwritten2, NULL);

				} else {
					// Simulate successful writes
					lnNumwritten1 = data1->length;
					lnNumwritten2 = 0;
				}

				// Did we write anything?
				if (lnNumwritten1 + lnNumwritten2 > 0)
					SendMessage(hwndJDebiC, tnDataType, lnNumwritten1 + lnNumwritten2, gnJDebiCOutPipeNumber);
			}


		//////////
		// Clean house
		//////
			if (data1)		data1->length = 0;
			if (data2)		data2->length = 0;


		//////////
		// Indicate how many bytes were transmitted
		//////
			return((s32)(lnNumwritten1 + lnNumwritten2));

	}




//////////
//
// Called to process a thisCode object into its call stack hierarchy
//
// Note:  Must sync up with the SThisCode structure
//
//////
	void iJDebiC_thisCode(SBuilder* data, SBuilder* items, SThisCode* thisCode)
	{
		s8 buffer[64];


		// Make sure our environment is sane
		if (thisCode && data && !iJDebiC_alreadyProcessedItem(items, thisCode))
		{
			//////////
			// Record our processing this thisCode
			//////
				iJDebiC_recordNewItem(items, thisCode);


			//////////
			// Ids
			//////
				iBuilder_appendData(data, "thisCode = { ", -1);
				sprintf(buffer, "id = %08x, \0", (u32)(uptr)thisCode);
				iBuilder_appendData(data, buffer, -1);

				iBuilder_append_label_uptr(data, (s8*)"prev",		(uptr)thisCode->ll.prev);
				iBuilder_append_label_uptr(data, (s8*)"next",		(uptr)thisCode->ll.next);
				iBuilder_append_label_uptr(data, (s8*)"window",		(uptr)iObj_find_thisForm_window(thisCode->live._this));
				iBuilder_append_label_uptr(data, (s8*)"definition",	(uptr)thisCode->def);
				iBuilder_append_label_uptr(data, (s8*)"live",		(uptr)&thisCode->live);

				iBuilder_appendData(data, " }", -1);


			//////////
			// definition
			//////
				if (thisCode->def)
					iJDebiC_sourceCode(data, items, thisCode->def);


			//////////
			// live
			//////
				iJDebiC_sourceCode(data, items, &thisCode->live);
		}
	}




//////////
//
// Called to append information about a sourceCode member
//
// Note:  Must sync up with the SSourceCode structure
//
//////
	void iJDebiC_sourceCode(SBuilder* data, SBuilder* items, SSourceCode* sourceCode)
	{
		s8 buffer[64];


		// Make sure our environment is sane
		if (sourceCode && data && !iJDebiC_alreadyProcessedItem(items, sourceCode))
		{
			//////////
			// Record our processing this sourceCode
			//////
				iJDebiC_recordNewItem(items, sourceCode);


			//////////
			// Ids
			//////
				iBuilder_appendData(data, "sourceCode = { ", -1);
				sprintf(buffer, "id = %08x, \0", (u32)(uptr)sourceCode);
				iBuilder_appendData(data, buffer, -1);
				if (sourceCode->func)			iBuilder_append_label_uptr(data, (s8*)"firstFunction",	(uptr)sourceCode->func);
				if (sourceCode->params)			iBuilder_append_label_uptr(data, (s8*)"params",			(uptr)sourceCode->params);
				if (sourceCode->returns)		iBuilder_append_label_uptr(data, (s8*)"returns",		(uptr)sourceCode->returns);
				if (sourceCode->privates)		iBuilder_append_label_uptr(data, (s8*)"privates",		(uptr)sourceCode->privates);
				if (sourceCode->locals)			iBuilder_append_label_uptr(data, (s8*)"locals",			(uptr)sourceCode->locals);
				if (sourceCode->scoped)			iBuilder_append_label_uptr(data, (s8*)"scoped",			(uptr)sourceCode->scoped);
				if (sourceCode->func)			iBuilder_append_label_uptr(data, (s8*)"sourceCode",		(uptr)sourceCode->func);
				iBuilder_appendData(data, " }", -1);


			//////////
			// Append related items
			//////
				if (sourceCode->func)			iJDebiC_function(data, items, sourceCode->func);
				if (sourceCode->params)			iJDebiC_variable(data, items, sourceCode->params);
				if (sourceCode->returns)		iJDebiC_variable(data, items, sourceCode->returns);
				if (sourceCode->privates)		iJDebiC_variable(data, items, sourceCode->privates);
				if (sourceCode->locals)			iJDebiC_variable(data, items, sourceCode->locals);
				if (sourceCode->scoped)			iJDebiC_variable(data, items, sourceCode->scoped);
				if (sourceCode->func)			iJDebiC_sem(data, items, sourceCode->func->sem);

		}
	}




//////////
//
// Called to append information about a function member
//
// Note:  Must sync up with the SFunction structure
//
//////
	void iJDebiC_function(SBuilder* data, SBuilder* items, SFunction* func)
	{
		s8 buffer[64];


		// Make sure our environment is sane
		if (func && data && !iJDebiC_alreadyProcessedItem(items, func))
		{
			//////////
			// Record our processing this function
			//////
				iJDebiC_recordNewItem(items, func);


			//////////
			// Ids
			//////
				iBuilder_appendData(data, "function = { ", -1);
				sprintf(buffer, "id = %08x, \0", (u32)(uptr)func);
				iBuilder_appendData(data, buffer, -1);

				if (func->ll.nextFunc)			iBuilder_append_label_uptr(data,	(s8*)"firstFunction",	(uptr)func->ll.nextFunc);
				if (func->name._data)		iBuilder_append_label_datum(data,	(s8*)"name",			&func->name);

				if (func->params)				iBuilder_append_label_uptr(data,	(s8*)"params",			(uptr)func->params);
				if (func->locals)				iBuilder_append_label_uptr(data,	(s8*)"locals",			(uptr)func->locals);
				if (func->returns)				iBuilder_append_label_uptr(data,	(s8*)"returns",			(uptr)func->returns);
				if (func->scoped)				iBuilder_append_label_uptr(data,	(s8*)"scoped",			(uptr)func->scoped);

				if (func->firstAdhoc)			iBuilder_append_label_uptr(data,	(s8*)"firstAdhoc",		(uptr)func->firstAdhoc);

//////////
// Oct.24.2015 -- removed in favor of creating a SEM* reference for each block, which is func->sourceCode
// 				if (func->firstLine)			iBuilder_append_label_uptr(data,	(s8*)"firstLine",		(uptr)func->firstLine);
// 				if (func->lastLine)				iBuilder_append_label_uptr(data,	(s8*)"lastLine",		(uptr)func->lastLine);
//////
				iBuilder_appendData(data, " }", -1);


			//////////
			// Append related items
			//////
				if (func->ll.nextFunc)			iJDebiC_function(data, items, func->ll.nextFunc);

				if (func->params)				iJDebiC_variable(data, items, func->params);
				if (func->locals)				iJDebiC_variable(data, items, func->locals);
				if (func->returns)				iJDebiC_variable(data, items, func->returns);
				if (func->scoped)				iJDebiC_variable(data, items, func->scoped);

				if (func->firstAdhoc)			iJDebiC_function(data, items, func->firstAdhoc);
		}
	}




//////////
//
// Called to append information about a variable member
//
// Note:  Must sync up with the SVariable structure
//
//////
	void iJDebiC_variable(SBuilder* data, SBuilder* items, SVariable* var)
	{
		s8 buffer[64];


		// Make sure our environment is sane
		if (var && data && !iJDebiC_alreadyProcessedItem(items, var))
		{
			//////////
			// Record our processing this variable
			//////
				iJDebiC_recordNewItem(items, var);


			//////////
			// Ids
			//////
				iBuilder_appendData(data, "variable = { ", -1);
				sprintf(buffer, "id = %08x, \0", (u32)(uptr)var);
				iBuilder_appendData(data, buffer, -1);

				if (var->name._data)		iBuilder_append_label_datum(data,	(s8*)"name",			&var->name);
				if (var->ll.prev)				iBuilder_append_label_uptr(data,	(s8*)"prev",			(uptr)var->ll.prev);
				if (var->ll.next)				iBuilder_append_label_uptr(data,	(s8*)"next",			(uptr)var->ll.next);
				if (var->firstAccess)			iBuilder_append_label_uptr(data,	(s8*)"firstAccess",		(uptr)var->firstAccess);
				if (var->firstAssign)			iBuilder_append_label_uptr(data,	(s8*)"firstAssign",		(uptr)var->firstAssign);

				iBuilder_append_label_logical(data,	(s8*)"varAllocated", var->isVarAllocated);


			//////////
			// Actual variable, or indirect?
			//////
				if (var->indirect)
				{
					// This variable points to another variable
					iBuilder_append_label_uptr(data,	(s8*)"indirect",		(uptr)var->indirect);
					iBuilder_appendData(data, " }", -1);

					if (var->firstAccess)		iJDebiC_sem(data, items, var->firstAccess);
					if (var->firstAssign)		iJDebiC_sem(data, items, var->firstAssign);

					iJDebiC_variable(data, items, var->indirect);

				} else {
					// The variable is not a reference, but points to itself
					iBuilder_append_label_logical(data,	(s8*)"valueAllocated", var->isValueAllocated);
					iBuilder_appendData(data, " }", -1);

					if (var->firstAccess)		iJDebiC_sem(data, items, var->firstAccess);
					if (var->firstAssign)		iJDebiC_sem(data, items, var->firstAssign);
// TODO:  Working here...
				}

		}

// 		// If this variable is related to a component, indicate it here
// 		SComp*		compRelated;											// Can vary regularly, but when available at compile time and in immediate scope, relates to a component
//
// 		// Variable data
// 		SDatum		name;													// Name of this variable (alway allocated)
// 		u32			arrayRows;												// If created as an array, how many rows
// 		u32			arrayCols;												// If created as an array, how many columns
//
// 		// Variable content based on type
// 		u32			varType;												// Variable type (see _VAR_TYPE_* constants)
// 		bool		isValueAllocated;										// If true, the data pointed to by this->value.data_s8, or this->obj, or this->bmp, or this->thisCode was allocated
// 		union {
// 			SObject*		obj;											// The object this item relates to.  If isValueAllocated is set, this variable owns the object.
// 			SFunction*		thisCode;										// Pointer to the code block this relates to
// 			SBitmap*		bmp;											// The bitmap this item points to
// 			SField*			field;											// Pointer to a table/cursor field
// 			SDatum			value;											// The actual value
// 		};
//
// 		// If assign or access
// 		SEM*		firstAccess;											// Source code executed whenever this variable is accessed
// 		SEM*		firstAssign;											// Source code executed whenever this variable is assigned
	}




//////////
//
// Called to append information about a sem (edit manager) member
//
// Note:  Must sync up with the SEM structure
//
//////
	void iJDebiC_sem(SBuilder* data, SBuilder* items, SEM* sem)
	{
		s8 buffer[64];


		// Make sure our environment is sane
		if (sem && data && !iJDebiC_alreadyProcessedItem(items, sem))
		{
			//////////
			// Record our processing this edit manager
			//////
				iJDebiC_recordNewItem(items, sem);


			//////////
			// Ids and values
			//////
				iBuilder_appendData(data, "sem = { ", -1);
				sprintf(buffer, "id = %08x, \0", (u32)(uptr)sem);
				iBuilder_appendData(data, buffer, -1);

				iBuilder_appendData(data, " }", -1);

		}
	}




//////////
//
// Called to process a windows object into text.
//
//		window = { id = 083829983, ... }
//
//////
	void iJDebiC_win(SBuilder* data, SBuilder* items, SWindow* win)
	{
		s8 buffer[4096];


		// Make sure our environment is sane
		if (win && data && !iJDebiC_alreadyProcessedItem(items, win))
		{
			//////////
			// Record our processing this window
			//////
				iJDebiC_recordNewItem(items, win);


			//////////
			// Ids and values
			//////
				iBuilder_appendData(data, "window = { ", -1);
				sprintf(buffer, "id = %08x, \0", (u32)(uptr)win);
				iBuilder_appendData(data, buffer, -1);

// Must sync up with the SWindow structure
				iBuilder_append_label_logical(data, (s8*)"isValid", win->isValid);
				iBuilder_append_label_uptr(data, (s8*)"hwnd", (uptr)win->hwnd);
				iBuilder_append_label_uptr(data, (s8*)"bmp", (uptr)win->bmp);

				iiJDebiC_decode_Rect(buffer, &win->rc);
				iBuilder_append_label_text(data, (s8*)"rc", buffer);

				iBuilder_append_label_uptr(data, (s8*)"obj", (uptr)win->obj);

				iiJDebiC_decode_SMouseData(buffer, &win->mousePrior);
				iBuilder_append_label_text(data, (s8*)"mousePrior", buffer);

				iiJDebiC_decode_SMouseData(buffer, &win->mouseCurrent);
				iBuilder_append_label_text(data, (s8*)"mousePrior", buffer);

				iBuilder_append_label_logical(data, (s8*)"isMoving", win->isMoving);
				iBuilder_append_label_logical(data, (s8*)"isResizing", win->isResizing);

				iiJDebiC_decode_SMouseData(buffer, &win->mouseMoveResizeStart);
				iBuilder_append_label_text(data, (s8*)"mouseMoveResizeStart", buffer);

				iiJDebiC_decode_Rect(buffer, &win->rcMoveResizeStart);
				iBuilder_append_label_text(data, (s8*)"rcMoveResizeStart", buffer);

				iBuilder_append_label_sptr(data, (s8*)"movingLastDeltaX", (uptr)win->movingLastDeltaX);
				iBuilder_append_label_sptr(data, (s8*)"movingLastDeltaY", (uptr)win->movingLastDeltaY);

				iiJDebiC_decode_POINT(buffer, win->mousePositionClick);
				iBuilder_append_label_text(data, (s8*)"mousePositionClick", buffer);

				iiJDebiC_decode_POINT(buffer, win->mousePositionClickScreen);
				iBuilder_append_label_text(data, (s8*)"mousePositionClickScreen", buffer);

				iBuilder_appendData(data, (s8*)" }", -1);
		}
	}




//////////
//
// Called to process an object, and all its poems, into text
//
//////
	void iJDebiC_obj(SBuilder* data, SBuilder* items, SObject* obj)
	{
		s8 buffer[4096];


		// Make sure our environment is sane
		if (obj && data && !iJDebiC_alreadyProcessedItem(items, obj))
		{
			//////////
			// Record our processing this object
			//////
				iJDebiC_recordNewItem(items, obj);


			//////////
			// Ids and values
			//////
				iBuilder_appendData(data, "object = { ", -1);
				sprintf(buffer, "id = %08x, \0", (u32)(uptr)obj);
				iBuilder_appendData(data, buffer, -1);

		}
// 			SLL			ll;													// Linked list
// 			SObject*	parent;												// Pointer to parent object for this instance
// 			SObject*	firstChild;											// Pointer to child objects (all objects are containers)
//
// 	#ifdef _EXTRA_DEBUGGING_DATA
// 			SDatum		dbgClass;
// 			SDatum		dbgName;
// 	#endif
//
// 			// Defined class, class information
// 			s32			objType;											// Object base type/class (see _OBJECT_TYPE_* constants)
//
// 			// Object flags
// 			bool		isRendered;											// Is it rendered (can be rendered even if it's not visible)?
// 			bool		isPublished;										// Should this control be published?  Every object has a .lockScreen property which allows it to not be published while changes are made.
// 			bool		isDirtyRender;										// Is set if this or any child object needs re-rendered
// 			bool		isDirtyPublish;										// Is set if this or any child object needs re-published
//
//
// 			//////////
// 			// Object size in pixels, per the .Left, .Top, .Width, and .Height properties
// 			//////
// 				RECT		rc;												// Object's current position in its parent
// 				RECT		rco;											// Object's original position in its parent
// 				RECT		rcp;											// Original size of parent at creation
// 				RECT		rcClient;										// Client portion within the size of the object
// 				RECT		rcExtra;										// An extra portion used for object-specific components, such as rider tab location on carousels
//
//
// 			//////////
// 			// Common properties that are literal(p) and allocated(pa) values
// 			//////
// 				SProperties		p;											// Common object properties
// 				SVariable**		props;										// An allocated array of properties (varies in size by object)
// 				s32				propsCount;									// The number of property variables allocated
//
// 				// Related position in the member hierarchy
// 				SVariable*	firstProperty;									// User-defined property (design time and runtime)
// 				SEM*		firstMethod;									// User-defined methods (design time and runtime)
//
// 				// Related access and assign methods
// 				bool		anyPropertyHasAccessOrAssignMethods;
// 				SEM*		firstAccess;									// User-defined property access methods (design time and runtime)
// 				SEM*		firstAssign;									// User-defined property assignment methods (design time and runtime)
//
// 				// Events
// 				SEvents		ev;												// Events for this object
//
//
// 			//////////
// 			// Base drawing canvas
// 			//////
// 				SBitmap*	bmp;											// If exists, canvas for the content
// 				SBitmap*	bmpPriorRendered;								// Used for speedups when not isDirty
// 				SBmpCache*	bc;												// For certain compute intensive operations (color gradient controls), the bitmap is only drawn/computed once and then copied thereafter, unless any of eight data points change
// 				// If not scaled:
// 				s32			scrollOffsetX;									// If the bmp->bi coordinates are larger than its display area, the upper-left X coordinate
// 				s32			scrollOffsetY;									// ...the upper-left Y coordinate
// 				// If scaled, updated only during publish():
// 				bool		isScaled;										// If the bmp->bi coordinates are larger than its display area, should it be scaled?
// 				SBitmap*	bmpScaled;										// The bmp scaled into RC's size

	}




//////////
//
// Helper functions for decoding sub-variables
//
//////
	void iiJDebiC_decode_Rect(s8* buffer, RECT* rc)
	{
		sprintf(buffer, "{ left = %d, top = %d, right = %d, bottom = %d }\0", (s32)rc->left, (s32)rc->top, (s32)rc->right, (s32)rc->bottom);
	}

	void iiJDebiC_decode_POINT(s8* buffer, POINT pt)
	{
		sprintf(buffer, "{ x = %d, y = %d }\0", (s32)pt.x, (s32)pt.y);
	}

	cs8* iiYesNo(bool tlTest)
	{
		return((tlTest) ? "yes" : "no");
	}

	void iiJDebiC_decode_SMouseData(s8* buffer, SMouseData* md)
	{
		sprintf(buffer,   "{ positionInOsDesktop = { x = %d, y = %d }, "
							"position = { x = %d, y = %d }, "
							"whelDeltaV = %d, wheelDeltaH = %d, "

							"buttonLeft = %u, buttonMiddle = %u, buttonRight = %u, buttonAnyDown = %u, "
							"isCaps = %s, isCtrl = %s, isAlt = %s, isShift = %s }\0",

							(s32)md->positionInOsDesktop.x,	(s32)md->positionInOsDesktop.y,
							(s32)md->position.x,			(s32)md->position.y,
							md->wheelDeltaV,				md->wheelDeltaH,

							md->buttonLeft,			md->buttonMiddle,		md->buttonRight,	md->buttonAnyDown,
							iiYesNo(md->isCaps),	iiYesNo(md->isCtrl),	iiYesNo(md->isAlt),	iiYesNo(md->isShift));
	}
