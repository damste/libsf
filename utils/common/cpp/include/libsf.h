//////////
//
// /libsf/utils/common/cpp/include/libsf.h
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
// Copyright (c) 2016 by Rick C. Hodgin
//////
// Last update:
//     Jun.29.2016
//////
// Change log:
//     Jun.29.2016	- Initial creation
//////
//
// This file holds all structures used by any LibSF include file.
// For now.  Once CAlive is completed ... each struct back to where it belongs.
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
//////////




#ifndef __LIBSF_H__
#define __LIBSF_H__


//////////
// datum.h
// BEGIN
//////
	#ifndef IDispatch
		struct IDispatch;
	#endif

	struct SDateTime;
	struct SDateTimeX;
	struct SDate;
	struct SVariable;
	struct SLine;
	struct SComp;
	struct SFont;
	struct SFunction;
	struct SNoteLog;
	struct SUndo;
	struct SObject;
	struct SThisCode;
	struct SExtraInfo;
	struct SDllFunc;
	struct SNode;
	struct SGraceRect;
	struct SSubInstr;

	struct SDatum
	{
		union {
			uptr		_data;				// Address of content
			s8*			data;
			s8*			data_s8;			// To access the data as s8
			u8*			data_u8;			// To access the data as u8
			u64*		data_u64;			// To access the data as u64
			s64*		data_s64;			// To access the data as s64
			u32*		data_u32;			// To access the data as u32
			s32*		data_s32;			// To access the data as s32
			u16*		data_u16;			// To access the data as u16
			s16*		data_s16;			// To access the data as s16
			f32*		data_f32;			// To access the data as f32
			f64*		data_f64;			// To access the data as f64
			cs8*		data_cs8;			// To access the data as cs8
			cu8*		data_cu8;			// To access the data as cu8
			void*		data_vp;			// To access the data as a void pointer
			IDispatch*	data_idispatch;		// To access the data as an IDispatch pointer

											// Common structures (used for displaying content during debugging)
			SDateTime*	data_dt;			// To access the data as a datetime
			SDateTimeX*	data_dtx;			// To access the data as a datetimex
			SDate*		data_date;			// To access the data as a date in the text-form YYYYMMDD
			SBgra*		data_bgra;			// To access the data as SBgra
			SBgr*		data_bgr;			// To access the data as SBgr
			#ifdef M__APM__INCLUDED
			SMapm*		data_big;			// To access the data as an arbitrary precision structure wrapped around SMapm (see 3rd_party\mapm\m_apm.h)
			#endif
		};
		s32				length;					// Content length
	};

	struct SDatumCallback
	{
		// When propAndVAlue_func() is called, these will be populated, access with cb->prop and cb->value
		SDatum		prop;
		SDatum		value;

		// General purpose values available
		void*		extra1;
		void*		extra2;
		bool		flag1;
		bool		flag2;

		// Callback, return true if it should continue iterating through more properties
		union {
			uptr	_propAndValue_func;
			bool	(*propAndValue_func)		(SDatumCallback* cb);
		};
	};

	#define _SPROPERTY_DEFINED 1
	struct SProperty
	{
		bool		name_allocated;				// Was the name datum allocated?
		bool		value_allocated;			// Was the value datum allocated?

		SDatum*		name;						// Name for this property

		bool		isValueDatum;				// If the value is stored as a datum
		SVariable*	value;						// Value for this name
		SDatum*		value_datum;				// Value for this name
	};
//////
// END
// datum.h
//////////




//////////
// builder.h
// BEGIN
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
//////
// END
// builder.h
//////////
;




//////////
// ll.h
// BEGIN
//////
	// Linked list
	struct SLL
	{
		// Next entry in linked list
		union {
			SLL*			next;
			SComp*			nextComp;
			SLine*			nextLine;
			SObject*		nextObj;
			SVariable*		nextVar;
			SThisCode*		nextThisCode;
			SExtraInfo*		nextExtraInfo;
			SFunction*		nextFunc;
			SDllFunc*		nextDllFunc;
			SNoteLog*		nextNoteLog;
		};
		
		// Previous entry in linked list
		union {
			SLL*			prev;
			SComp*			prevComp;
			SLine*			prevLine;
			SObject*		prevObj;
			SVariable*		prevVar;
			SThisCode*		prevThisCode;
			SExtraInfo*		prevExtraInfo;
			SFunction*		prevFunc;
			SDllFunc*		prevDllFunc;
			SNoteLog*		prevNoteLog;
		};
		u32					uniqueId;			// Unique id associated with this object
	};

	// Callback structure for SLL iteration
	struct SLLCallback
	{
		union
		{
			uptr	_func;
			bool	(*funcBool)	(SLLCallback* cb);
			void	(*funcVoid)	(SLLCallback* cb);
			//////
			// Uses the following format for the callback:
			//		void func(SLLCallback* cb)
			//		bool func(SLLCallback* cb)
			//////////
		};

		// For runtime
		SThisCode*	thisCode;

		// Data items for this callback
		SLL*	ll;
		union {
			uptr	extra;
			uptr	extra1;
		};
		u32		extra2;
	};
//////
// END
// ll.h
//////////




//////////
// sem.h
// BEGIN
//////
	struct SEMPoint
	{
		SLine*			line;											// The actual line here
		u32				uid;											// The UID of the line
		u32				lineNumber;										// The line number
		s32				column;											// The column on this line where the selection is currently
	};


	//////////
	// SEM is short for "SEditManager"
	// Note:  This is also a reference to Sammy Edward Mitchell, the author of
	//        The SEMware Editor, TSE, without whom I would not have been as
	//        prolific in my software development.
	//////
	struct SEM
	{
		SLine*		firstLine;										// First in the chain (first->prev is NULL)
		SLine*		lastLine;										// Last in the chain (last->next is NULL)
		bool		isStale;										// A general purpose flag indicating if the source code within this SEM is stale
		bool		isReadOnly;										// If read-only no changes are allowed, only navigation
		bool		stopNavigationOnNbsp;							// Do ctrl+left/right operations stop at every part of nbsp names (by default, no)?

																	// If populated, this SEM is only a placeholder for this instance, and the this->reference points to the real SEM we should use
		SEM*		indirect;										// If not NULL, this SEM points to another SEM which is the real code block


																	//////////
																	// NOTE:  Everything below is used ONLY IF INDIRECT IS NULL (except for cases of context usage)
																	//////////


																	//////////
																	// For display
																	//////
		SLine*		line_top;										// Top item in the current view
		SLine*		line_cursor;									// Line where the cursor is
		SLine*		line_cursorLast;								// The last location before movement was made
		bool		isOverwrite;									// Are we in overwrite mode?
		bool		showLineNumbers;								// Should we render line numbers?
		bool		showCursorLine;									// Should we render the cursor line?
		bool		showEndLine;									// Should we render the end line in a different color?
		bool		isHeavyProcessing;								// When large amounts of processing will be conducted, the display can be disabled
		bool		isSourceCode;									// Is this source code?
		bool		allowMoveBeyondEndOfLine;						// Do we allow them to move beyond the end of the line?
		RECT		rcLineNumberLastRender;							// Used for mouse clicking, to determine how much we adjust

																	// Loaded filename (if any)
		s8			fileName[_MAX_PATH];

		// Editing cues
		bool		hideEditCues;									// If true, will not show the changedColor or newColor
		SBgra		changedColor;									// The color when data has changed
		SBgra		newColor;										// The color when data is new

																	// Percentages (values are typically 0.05f and 0.15f for 5% to 15%)
		f32			minNbspColorInfluence;							// How much minimum influence should the Nbsp color have for highlighting
		f32			maxNbspColorInfluence;							// How much maximum?

		s32			columnEdit;										// Column we're currently inputting
		s32			columnLeft;										// The column we're displaying at the left-most position (of horizontally scrolled, this will be greater than 0)
		s32			tabWidth;										// How many characters does a tab expand to?
		bool		areTabsEnforced;								// If tabs are enforced, then navigation across whitespaces lands on tab boundaries
		SFont*		font;											// Optional, if not NULL then it overrides the object's font
		u32			renderId;										// Each time it's rendered, the count is incremented.  This allows lines to be tested to see if they are actively rendered, or were previously rendered.


																	//////////
																	// Overlay highlight information to display near the cursor line
																	//////
		SLine*		line_highlightBefore;							// Something to highlight before the cursor line
		SLine*		line_highlightAfter;							// Something to highlight after the cursor line


																	//////////
																	// Note:  If isSelectingLine, then full line select mode.
																	//        If isSelectingColumn, then column select mode.
																	//        If isSelectingAnchor, then anchor select mode.
																	//////
		u32			selectMode;										// See _SEM_SELECT_MODE_* constants
		SEMPoint	selectOrigin;									// Where the selection started
		SEMPoint	selectEnd;										// Where the selection has ended


																	//////////
																	// For compiled programs
																	//////
		SFunction*	firstFunction;									// By default, we always create a function head for any code blocks that don't have an explicit "FUNCTION" at the top.
		SNoteLog*	firstNote;										// Notes during load or parsing


																	//////////
																	// The undo history operates in two levels:
																	// (1) When going through ecm-> it is undoHistory.
																	// (2) If accessing ecm->undoHistory-> then it is theUndo, which holds the undo information for that operation.
																	//////
		union {
			// If referenced through ecm-> then undoHistory is the undo history for this sec
			SEM*	undoHistory;									// The lines affected by the undo

																	// If referenced through ecm->undoHistory, then theUndo is the one in use here
			SUndo*	theUndo;										// If referenced through ecm->undoHistory-> then it only uses theUndo
		};
	};

	struct SEM_callback
	{
		SEM*		sem;											// The manager
		SLine*		line;											// This line

																	// Values used for miscellaneous purposes
		uptr		extra1;
		uptr		extra2;

		// Callback to delete any extra information.
		// Based on the return value, both line->sourceCode and line will be deleted automatically.
		union {
			uptr			_callback;
			bool			(*callback)		(SEM_callback* ecb);
		};

	};

	struct SEM_postParseCallback
	{
		union {
			uptr	_postParseFunc;
			void	(*postParseFunc)	(SLine* line);
		};
	};
//////
// END
// sem.h
//////////




//////////
// sem_line.h
// BEGIN
//////
	struct SLine
	{
		SLL				ll;												// 2-way link list
		u32				uid;											// Unique id for this line, used for undos and identifying individual lines which may move about (note this value must be isolated and separate from ll.uniqueId)
		union
		{
			void*		parent;											// A parent this relates to, which could be a controlling structure (like an SEM*)
			SEM*		sem;											// Parent SEM this belongs to
		};

		// Line information
		u32				lineNumber;										// This line's number
		s32				lineStatus;										// See _LINESTATUS_* constants
		SDatum			sourceCodeOriginal;								// The original sourceCode when the line was first created, or last saved (note the length here is the total length as this value does not change, but is setup exactly when it is updated)
		SDatum			sourceCode;										// The text on this line is LEFT(sourceCode.data, sourceCodePopulated)
		s32				populatedLength;								// The actual populated length of sourceCode, which may differ from sourceCode.length (which is the allocated length of sourceCode.data)

		// Optional related components associated with this line
		SComp*			firstComp;

		// Information related to this line
		SBuilder*		extra_info;										// (SExtraInfo) extra information about this line

																		// Each render, these are updated
		u32				renderId;										// Each time it's rendered, this value is set
		RECT			rcLastRender;									// The rectangle within the parent of the last render
	};
//////
// END
// sem_line.h
//////////




//////////
// bitmaps.h
// BEGIN
//////


//////////
// Structures
//////
	struct SFont
	{
		HDC			hdc;						// Device context used for its creation
		bool		isUsed;						// Is this font slot used?

		// Current font instance flags
		SDatum		name;						// Name of this font
		s32			charset;					// Font charset
		bool		isBold;						// Is the font bold? (Note: This is independent of the font name itself having bold in it, such as "Ubuntu Bold"
		bool		isItalic;					// Is the font italic?
		bool		isUnderline;				// Is the font underline?
		bool		isStrikethrough;			// Is the font strikethrough?
		bool		isCondensed;				// Is the font condensed?
		bool		isExtended;					// Is the font extended?
		bool		isOutline;					// Is the font outlined?
		bool		isShadow;					// Is the font shadowed?

		// OS font handle
		HFONT		hfont;

		// Internal Windows settings
		s32			_sizeUsedForCreateFont;		// Computed value based on passed font size
		u32			_size;						// Actual point size
		u32			_weight;					// Actual weight
		u32			_italics;					// Actual italics setting
		u32			_underline;					// Actual underline setting
		TEXTMETRIC	tm;							// Text metrics computed at the time of creation
	};

	struct SBitmap
	{
		// Device context and bitmap handle to this data
		HDC					hdc;
		HBITMAP				hbmp;
		RECT				rc;
		u32					iter;					// For graphics ops, holds a rendering iteration count
		SFont*				font;					// If a font is associated with this context, it is set here

		// Raw bitmap data (suitable for writing to disk)
		BITMAPFILEHEADER	bh;
		BITMAPINFOHEADER	bi;

		union {
			s8*				bd;						// Legacy access
			s8*				bds;					// Signed char access
			u8*				bdu;					// Unsigned char access
			SBgr*			bdrgb;					// Access as 24-bit rgb
			SBgra*			bdrgba;					// Access as 32-bit rgba
		};
		u32					rowWidth;				// See: iBmp_computeRowWidth()
	};

	struct SBmpCache
	{
		SBitmap*		bmpCached;

		u32				data1;
		u32				data2;
		u32				data3;
		u32				data4;
		u32				data5;
		u32				data6;
		u32				data7;
		u32				data8;
		u32				data9;
		u32				data10;
		u32				data11;
		u32				data12;
		u32				data13;
		u32				data14;
	};


	// For processing the scaling of bitmaps
	struct SBitmapProcess
	{
		// Holds the source canvas
		SBitmap*			src;

		// Holds storage data for single spanned pixels
		u32					red;
		u32					grn;
		u32					blu;
		u32					alp;

		// tpoints is a buffer created to store the conversion pixel data during accumulation.
		// Use formula:
		//		tpoints	= (SRGBAF*)malloc(		((u32)(1.0/ratioV) + 3)   *
		//										((u32)(1.0/ratioH) + 3))
		//
		f32					ratioV;				// (f32)bio->biHeight	/ (f32)bii->biHeight;
		f32					ratioH;				// (f32)bio->biWidth	/ (f32)bii->biWidth;
		u32					count;				// Number of valid points in tpoints
		SBgraf*				pixels;				// Accumulation buffer for point data needed to feed into destination

		// Temporary variables used for processing
		union {
			SBgra*			optra;				// (For 32-bit bitmaps) Output pointer to the upper-left pixel for this x,y
			SBgr*			optr;				// (For 24-bit bitmaps) Output pointer to the upper-left pixel for this x,y
		};
		union {
			SBgra*			iptrAnchora;		// (For 32-bit bitmaps) Input pointer to the left-most pixel of the first row (the anchor)
			SBgr*			iptrAnchor;			// (For 24-bit bitmaps) Input pointer to the left-most pixel of the first row (the anchor)
		};
		union {
			SBgra*			iptra;				// (For 32-bit bitmaps) Input pointer to the left-most pixel for this y row
			SBgr*			iptr;				// (For 24-bit bitmaps) Input pointer to the left-most pixel for this y row
		};
		f32					ulx;				// Upper-left X
		f32					uly;				// Upper-left Y
		f32					lrx;				// Lower-right X
		f32					lry;				// Lower-right Y
		f32					widthLeft;			// Width for each left-most pixel
		f32					widthRight;			// Width for each right-most pixel
		f32					height;				// Height for a particular pixel portion (upper, lower)
		f32					area;				// Temporary computed area for various pixels
		s32					left;				// Left-side pixel offset into line
		s32					right;				// Number of pixels to reach the right-most pixel
		s32					middleStartH;		// Starting pixel offset for middle span
		s32					middleFinishH;		// Ending pixel offset for middle span
		s32					middleStartV;		// Middle starting pixel
		s32					middleFinishV;		// Middle ending pixel

		// Indicates the span from upper-left corner
		bool				spans2H;			// Spans at least 2 pixels horizontally, meaning it begins somewhere in 1.x, for example, and ends somewhere beyond 2.x
		bool				spans3H;			// Spans at least 3 pixels horizontally, meaning it begins somewhere in 1.x, for example, and ends somewhere beyond 3.x
		bool				spans2V;			// Spans at least 2 pixels vertically, meaning it begins somewhere in 1.x, for example, and ends somewhere beyond 2.x
		bool				spans3V;			// Spans at least 3 pixels vertically, meaning it begins somewhere in 1.x, for example, and ends somewhere beyond 3.x
	};
//////
// END
// bitmaps.h
//////////




//////////
// comps.h
// BEGIN
//////




//////////
// Structures
//////
	// Components parsed on a line
	struct SComp
	{
		SLL				ll;							// 2-way link list
		bool			isAllocated;				// When deleted, should it be free'd?
		bool			isError;					// Is the component in error?  Stored in extra_info.
		bool			isWarning;					// Is the component in warning?  Stored in extra_info.

		// Information about the component
		s32				iCode;						// Refer to _ICODE_* constants
		u32				iCat;						// Refer to _ICAT_* constants, and use iCat() macro for accessing the lower portion without bit flags influencing its value

		// Storage data
		bool			lTextAllocated;				// When deleted, should the text be free'd?
		SDatum			text;						// The text this component relates to

		// References to other related items
		SLine*			line;						// Source line
		s32				start;						// Offset into the line where it was found (used for warning/error reporting)
		SNode*			node;						// The node this component relates to
		SBuilder*		extra_info;					// (SExtraInfo) extra information about this component

		// For rendering and syntax highlighting
		s32				nbspCount;					// Number of non-breaking-spaces in this component (ASCII-255)
		SBmpCache*		bc;							// For faster rendering of drawn things (casks, for example) in SEM windows
		SBgra*			color;						// Syntax highlight color
		bool			useBoldFont;				// Syntax highlight font should be bold?
		// For selected components
		SBgra*			overrideSelectionBackColor;
		SBgra*			overrideSelectionForeColor;
		// For matches (the closest parenthesis, bracket, brace, etc)
		SBgra*			overrideMatchingForeColor;
		SBgra*			overrideMatchingBackColor;
	};

	struct SCompCallback
	{
		union {
			SComp*		comp;											// Component at start, and the component to continue processing after upon exit
			s8*			text;											// Raw text (depending on when it is being processed
		};
		u32				length;											// If raw text, the length of the thing being searched, otherwise 0.
		u32				iCode;											// The iCode being queried

		// Callback callbacks for adjustment
		union {
			uptr		_insertCompByComp;
			void		(*insertCompByComp)		(SComp* compRef, SComp* compNew, bool tlInsertAfter);
		};
		union {
			uptr		_insertCompByParams;
			void		(*insertCompByParams)	(SComp* compRef, SLine* line, u32 tniCode, u32 tnStart, s32 tnLength, bool tlInsertAfter);
		};
		union {
			uptr		_deleteComps;
			void		(*deleteComps)			(SComp* comp, SLine* line);
		};
		union {
			uptr		_cloneComps;
			SComp*		(*cloneComps)			(SComp* comp, SLine* line);
		};
		union {
			uptr		_mergeComps;
			SComp*		(*mergeComps)			(SComp* comp, SLine* line, u32 tnCount, u32 tniCodeNew);
		};
	};

	struct SStartEndCallback
	{
		union
		{
			uptr	_func;
			bool	(*funcBool)	(SStartEndCallback* cb);	// This callback should return false to continue searching, or true when the item is found
			void	(*funcVoid)	(SStartEndCallback* cb);
			//////
			// Uses the following format for the callback:
			//		bool func(SStartEndCallback* cb)
			//////////
		};

		// Data items for this callback
		// Primary pointer
		union {
			void*	ptr;
			SComp*	ptrComp;
		};

		union {
			// Extra1
			uptr		ex1;
			uptr		extra1;
			uptr		extra;
			uptr		count1;
			union {
				uptr	count1_1;
				uptr	count1_2;
			};
			void*		ex1Ptr;
		};

		union {
			// Extra2
			uptr		ex2;
			uptr		extra2;
			uptr		count2;
			union {
				uptr	count2_1;
				uptr	count2_2;
			};
			void*		ex2Ptr;
		};
	};
//////
// END
// comps.h
//////////
;




//////////
// nodes.h
// BEGIN
//////
	//////////
	//
	// Nodes provide a multi-ported way to hook things up.  They are intended
	// to be used with components (SComp), which provide their context and all
	// information they'll display.  As such, nodes is dependent upon the
	// iBmp_node_renderComp() function, which renders the graphical portion of
	// the node.  If you do not want to use the default rendering algorithm,
	// then you can replace it with whatever you need.
	//
	// General 27-way node cube.  Picture a square.  At all cardinal and
	// ordinal points, there are node extending out, plus one in the middle.
	// Repeat this for three cross-sections of the cube, one at the front,
	// one at the back, and one directly in the middle:
	//
	//                   parent
	//                     n
	//             nw      |      ne
	//               \     |     /
	//                +----+----+
	//                |         |
	//         w ---- +    o    + ---- e
	//                |  center |
	//      prev      +----+----+      next
	//               /     |     \
	//             sw      |      se
	//           left      s      right
	//                    down
	//
	// Now picture that plane placed into a three-way system.  Imagine
	// looking at the image above from the e side, looking toward w:
	//
	//                                              Perspective view:
	//                                            2          1            0
	//            Side-on-view:          nw2----  +          + nw         +  ----nw0
	//            2    1    0                     |\         |\           |\
	//            +    +    +             w2----  + +        + + n        + +  ----n0
	//            |    |    |                     |  \       |  \         |  \
	//            o    o    o            sw2----  + o +      + o + ne     + o +  ----ne0
	//            |    |    |                      \  |       \  |         \  |
	//            +    +    +               s2----  + +        + + e        + +  ----e0
	//                                               \|         \|           \|
	//                                       se2----  +          + se         +  ----se0
	//
	// This yields a node array configuration that has 9 nodes per plane,
	// with a three-way configuration constructing a perfect cube, resulting
	// in 27-separate nodes.  These are called:
	//
	//		C0, N0, NE0, E0, SE0, S0, SW0, W0, NW0
	//		C1, N1, NE1, E1, SE1, S1, SW1, W1, NW1		// Aliased to:  C, N, NE, E, SE, S, SW, W, NW
	//		C2, N2, NE2, E2, SE2, S2, SW2, W2, NW2
	//
	//////
		cu32	_NODE2_MAX			= 27;
		cu32	_NODE_MAX			= 27;
		cu32	_NODE_COUNT			= 27;
		cu32	_NODE0_COUNT		= 9;
		cu32	_NODE1_COUNT		= 9;
		cu32	_NODE2_COUNT		= 9;

		// Go and map directions (from the current node)
		// Note:  The + origin is at the logical center of the screen
		struct SNodeRodMaps
		{
			// Relates to screen coordinates with a z-axis added in:
			f64		x;			//  o-y					// y is negative going up, positive going down
			f64		y;			//  |   .o+z			// z is positive going away, negative coming toward
			f64		z;			//  | .' 
		};						//  +'----o+x			// x is positive going right, negative going left
		///////
		// Holds the default rod directions for each connection based on a cube centered at C1 being at (0,0,0) and oriented normally (C0 away, C2 toward)
		//////////
				// Constant rod map values multipliers
				SNodeRodMaps gsfNodeRodMaps[_NODE_COUNT] =
				{	//	  x		  y		  z
					//	-----	-----	-----
					{	0.0,	-1.0,	1.0		},		// _NODE_N0		// Away
					{	1.0,	0.0,	1.0		},		// _NODE_E0
					{	0.0,	1.0,	1.0		},		// _NODE_S0
					{	-1.0,	0.0,	1.0		},		// _NODE_W0
					{	1.0,	-1.0,	1.0		},		// _NODE_NE0
					{	1.0,	1.0,	1.0		},		// _NODE_SE0
					{	-1.0,	1.0,	1.0		},		// _NODE_SW0
					{	-1.0,	-1.0,	1.0		},		// _NODE_NW0
					{	0.0,	0.0,	1.0		},		// _NODE_C0

					{	0.0,	-1.0,	0.0		},		// _NODE_N		// Same as _NODE_N1
					{	1.0,	0.0,	0.0		},		// _NODE_E		// Same as _NODE_E1
					{	0.0,	1.0,	0.0		},		// _NODE_S		// Same as _NODE_S1
					{	-1.0,	0.0,	0.0		},		// _NODE_W		// Same as _NODE_W1
					{	1.0,	-1.0,	0.0		},		// _NODE_NE		// Same as _NODE_NE1
					{	1.0,	1.0,	0.0		},		// _NODE_SE		// Same as _NODE_SE1
					{	-1.0,	1.0,	0.0		},		// _NODE_SW		// Same as _NODE_SW1
					{	-1.0,	-1.0,	0.0		},		// _NODE_NW		// Same as _NODE_NW1
					{	0.0,	0.0,	0.0		},		// _NODE_C		// Same as _NODE_C1

					{	0.0,	-1.0,	-1.0	},		// _NODE_N2		// Toward
					{	1.0,	0.0,	-1.0	},		// _NODE_E2
					{	0.0,	1.0,	-1.0	},		// _NODE_S2
					{	-1.0,	0.0,	-1.0	},		// _NODE_W2
					{	1.0,	-1.0,	-1.0	},		// _NODE_NE2
					{	1.0,	1.0,	-1.0	},		// _NODE_SE2
					{	-1.0,	1.0,	-1.0	},		// _NODE_SW2
					{	-1.0,	-1.0,	-1.0	},		// _NODE_NW2
					{	0.0,	0.0,	-1.0	}		// _NODE_C2
				};


		struct SNodeFlags
		{
			bool			n[_NODE_COUNT];									// A flag relates to each node direction, whether or not it should be traversed / processed / whatever
		};
		//////
		// Holds the default flag set that allows traversal in all directions
		//////////
				// Allow full traversal
				SNodeFlags gsfNodeFlags_all =
				{
					true,	// _NODE_N0
					true,	// _NODE_E0
					true,	// _NODE_S0
					true,	// _NODE_W0
					true,	// _NODE_NE0
					true,	// _NODE_SE0
					true,	// _NODE_SW0
					true,	// _NODE_NW0
					true,	// _NODE_C0

					true,	// _NODE_N		// Same as _NODE_N1
					true,	// _NODE_E		// Same as _NODE_E1
					true,	// _NODE_S		// Same as _NODE_S1
					true,	// _NODE_W		// Same as _NODE_W1
					true,	// _NODE_NE		// Same as _NODE_NE1
					true,	// _NODE_SE		// Same as _NODE_SE1
					true,	// _NODE_SW		// Same as _NODE_SW1
					true,	// _NODE_NW		// Same as _NODE_NW1
					true,	// _NODE_C		// Same as _NODE_C1

					true,	// _NODE_N2
					true,	// _NODE_E2
					true,	// _NODE_S2
					true,	// _NODE_W2
					true,	// _NODE_NE2
					true,	// _NODE_SE2
					true,	// _NODE_SW2
					true,	// _NODE_NW2
					true	// _NODE_C2
				};


		struct SNodeProps
		{
			SBgra			backColor;										// Text back color, 
			SBgra			foreColor;										// Text fore color, typically black
			s32				marginWidth;									// Width between text and the inner border
			SBgra			fillColor;										// Fill color, typically white
			s32				borderWidth;									// Width of the border in pixels
			SBgra			borderColor;									// Color of the border, typically black
			SBgra			rodColor;										// Connecting rods

			bool			colorize;										// Should the node be colorized (and not just black-and-white)?
			SBgra			colorizeColor;									// Color to colorize

			// Font settings
			SFont*			font;											// If non-NULL, font override to use, otherwise uses default font
		};

		// Holds render information for the node
		struct SNodeRender
		{
			SBitmap*	bmp;											// An image for this node's content
			RECT		rc;												// Render rc as of last computation
			u32			iter_uid;										// The last iteration this item was updated
			s32			propsIndex;										// An index into the properties for how this node is configured

																		// For 3D rendering using iGrace()
			SGraceRect*	grace;											// An array of vectors outlining everything to render the node centered around (0,0,0)
			s32			graceCount;										// The number of elements in grace
		};

		struct SNode
		{
			SNode*			n[_NODE_COUNT];									// Offshoot nodes
			u32				uid;											// Unique ID for this node

																			// Related info
			SComp*			comp;											// The component this node relates to
			SSubInstr*		opData;											// When used as for processing ops

																			// Extra/associated data
			void*			extraData;										// General purpose data
			union {
				uptr		_extraData_deleteFunc;							// Function to call when deleting
				void		(*extraData_deleteFunc)(SNode* node);
			};

			// For graphics rendering
			SNodeRender		render;
			SNodeProps*		render_override;								// Use these properties instead of those indicated by render (used for highlighting explicit nodes)
		};

//////
// END
// nodes.h
//////////




//////////
// compsearcher.h
// BEGIN
//////
	//////////
	// Extra info
	//////
		#define _SEXTRAINFO_DEFINED 1
		struct SExtraInfo
		{
			bool		isUsed;							// Is this item currently in use?
			s32			eiType;							// A registered identifier with the system for this extra info block
			u32			appType;						// An application defined type
			void*		data;							// Associated data
			SDatum		info;							// The extra info block stored for this entry

			// Functions to called when this item is processed in some way
			union
			{
				uptr	_onAccess;					// When the extra info item is accessed
				void	(*onAccess)					(SEM* sem, SLine* line, SExtraInfo* extra_info);
			};

			union
			{
				uptr	_onUpdate;					// When the parent signals that it's been updated/changed
				void	(*onUpdate)					(SEM* sem, SLine* line, SExtraInfo* extra_info);
			};

			union
			{
				uptr		_freeInternal;			// Called on a forced free operation when the parent is deleted
				SExtraInfo*	(*freeInternal)			(SEM* sem, SLine* line, SExtraInfo* extra_info);
			};
		};


	//////////
	// Compiler data
	//////
		#define _SNOTELOG_DEFINED 1
		// For warnings, errors, and notes
		struct SNoteLog
		{
			SLL				ll;
			SYSTEMTIME		time;											// When did the note get logged?

			SLine*			line;											// Associated line (if not already on a line)
			u32				start;											// Column the note begins on
			u32				end;											// Column the note ends on

			u32				number;											// A related number
			SDatum*			note;											// The message
		};

		#define _SCOMPILER_DEFINED 1
		struct SCompiler
		{
			// The last source code line
			SDatum*			sourceCode;										// Copy at last compile of LEFT(parent->sourceCode.data, parent->sourceCodePopulated)
			SLine*			line;											// SLine this compiler data belongs to (parent->compilerInfo points back to here)

			// Results of compilation
			SNoteLog*		firstInquiry;									// Noted inquiry(s) on this source code line
			SNoteLog*		firstWarning;									// Noted warning(s) on this source code line
			SNoteLog*		firstNote;										// Noted note(s) on this source code line

			// Information related to this compiler
			SBuilder*		extra_info;										// (SExtraInfo) extra information about this compiler
		};


	//////////
	// Known keywords to the system
	// ASCII Component Searcher
	//////
		#define _SASCIICOMPSEARCHER_DEFINED 1
		struct SAsciiCompSearcher
		{
			union {
				cs8*	keyword_cs8;
				cu8*	keyword_cu8;											// Text keyword being searched
			};
			s32			length;													// Length of the keyword (negative for case sensitive, positive case insensitive, 0 for termination entry)
			bool		repeats;												// Can this item repeat?  Or is this a one-shot keyword?
			s32			iCode;													// An associated code to store when this entry is found
			bool		firstOnLine;											// Should this item ONLY be the first on line?
			u32			iCat;													// This entry's general category (function, operator, keyword, flow)

			// For syntax highlighting
			SBgra*		syntaxHighlightColor;									// Color to display this component in
			bool		useBoldFont;											// Should this be bolded?

			// An optional extra callback to consider further if a candidate match is a valid match before committing
			union {
				uptr	_onCandidateMatch;
				bool	(*onCandidateMatch)(SAsciiCompSearcher* tacs, u8* tcStart, s32 tnLength);
			};

			// An optional extra callback to parse on finds
			union {
				uptr	_onFind;
				void	(*onFind)(SAsciiCompSearcher* tacs, SComp* comp);
			};

			// A callback function for the syntax parsing phase of compilation, to determine if the parameters are correct at compile-time, rather than run-time
			union {
				uptr	_compilerDictionaryLookup;
				s32		(*compilerDictionaryLookup)(SAsciiCompSearcher* tacs, SComp* comp, SComp* paramOrder[], s32* paramCount);
				// Returns an index into the internal function/command dictionary if a match is found, -1 if not
			};
		};
//////
// END
// compsearcher.h
//////////




//////////
// debug.h
// BEGIN
//////
	// Breakpoints during execution
	#define _SBREAKPOINT_DEFINED 1
	// Breakpoint types
	cu32	_BREAKPOINT_NONE								= 0;	// No breakpoint
	cu32	_BREAKPOINT_ALWAYS								= 1;	// Always stops
	cu32	_BREAKPOINT_CONDITIONAL_TRUE					= 2;	// Breaks when the condition is true
	cu32	_BREAKPOINT_CONDITIONAL_FALSE					= 3;	// Breaks when the condition is false
	cu32	_BREAKPOINT_CONDITIONAL_TRUE_COUNTDOWN			= 4;	// Breaks when the condition is true, and the countdown reaches zero
	cu32	_BREAKPOINT_CONDITIONAL_FALSE_COUNTDOWN			= 5;	// Breaks when the condition is false, and the countdown reaches zero
	cu32	_BREAKPOINT_CODEPOINT							= 6;	// Executes code when encountered
	cu32	_BREAKPOINT_SOUND_ON_BREAK						= 7;	// Plays a sound when the break is encountered

	struct SBreakpoint
	{
		// See _BREAKPOINT_* constants
		u32				type;
		bool			isUsed;								// Allocated in gBreakpoints as a bulk structure
		s32				soundChannel;						// Sound channel to engage when the breakpoint is encountered
		SBitmap*		bmpImage;							// Image to display when encountered
		u32				osKey;								// Keystroke to use to continue (allows certain breakpoints to not continue on normal RESUME command)

		// If there's a countdown
		u32				countdownResetValue;				// The value the countdown will reset to once it fires, if 0 always fires
		u32				countdown;							// Countdown to 0 when it fires

		// Information related to this breakpoint
		SBuilder*		extra_info;							// (SExtraInfo) extra information about this breakpoint
	};
//////
// END
// debug.h
//////////


#endif // __LIBSF_H__
