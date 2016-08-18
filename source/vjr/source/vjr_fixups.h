#pragma once

struct SComp;
struct SLine;
struct SObject;
struct SVariable;
struct SThisCode;
struct SExtraInfo;
struct SFunction;
struct SDllFunc;
struct SNoteLog;
struct SSubInstr;
struct SFont;
struct SBitmap;
struct SGraceRect;
struct SDatum;
struct SDateTime;
struct SDateTimeX;
struct SDate;
struct SBgra;
struct SBgr;
struct SCompiler;
struct SBreakpoint;

#define _EXCLUDE_iBmp_nbsp_createAndPopulate 1

// Linked list
struct SLL
{
	// Next entry in linked list
	union
	{
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
	union
	{
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
	union
	{
		uptr	extra;
		uptr	extra1;
	};
	u32		extra2;

	// For duplicated entries
	bool	llNewEntryIsOkayToUse;
	SLL*	llNew;
};

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
	u32				uid;											// Unique ID for this node
	SNode*			n[_NODE_COUNT];									// Offshoot nodes

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


struct SBuilder
{
	union {
		s8*		data;
		s8*		data_s8;								// Pointer to a buffer allocated in blocks
		u8*		data_u8;
		cvp		data_cvp;
		SDatum*	data_datum;
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

struct SDatum
{
	union
	{
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
		const void*	data_cvp;			// To access the data as a const void pointer
		IDispatch*	data_idispatch;		// To access the data as an IDispatch pointer

										// Common structures (used for displaying content during debugging)
		SDateTime*	data_dt;			// To access the data as a datetime
		SDateTimeX*	data_dtx;			// To access the data as a datetimex
		SDate*		data_date;			// To access the data as a date in the text-form YYYYMMDD
		SBgra*		data_bgra;			// To access the data as SBgra
		SBgr*		data_bgr;			// To access the data as SBgr
		SDatum*		data_datum;			// To access the data as another level of datum
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
	union
	{
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
	bool		widen;						// Is the font widened?
	s32			widenSpaces;				// How many pixels between characters is it widened?

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

struct SLine
{
	SLL				ll;												// Link list throughout
	u32				uid;											// Unique id for this line, used for undos and identifying individual lines which may move about (note this value must be isolated and separate from ll.uniqueId)
	void*			parent;											// A parent this relates to, which could be a controlling structure (like an SEM*)

	// Line information
	u32				lineNumber;										// This line's number
	bool			isNewLine;										// If the line's been added during normal editing
	SDatum*			sourceCodeOriginal;								// The original sourceCode when the line was first created, or last saved (note the length here is the total length as this value does not change, but is setup exactly when it is updated)
	SDatum*			sourceCode;										// The text on this line is LEFT(sourceCode.data, sourceCodePopulated)
	s32				sourceCode_populatedLength;						// The actual populated length of sourceCode, which may differ from sourceCode.length (which is the allocated length fo sourceCode.data)

//////////
// Some of these compilation steps are specific to Visual FreePro, Jr., though they will also work for other non-RDC/VXB compile steps
// START
//////
	// Each render, these are updated
	u32				renderId;										// Each time it's rendered, this value is set
	RECT			rcLastRender;									// The rectangle within the parent of the last render

	// Compiler information (see compiler.cpp)
	bool			forceRecompile;									// A flag that if set forces a recompile of this line
	SCompiler*		compilerInfo;									// Information about the last time this line was compiled

	// General purpose extra data
	SBreakpoint*	breakpoint;										// If there's a breakpoint here, what kind?
	SExtraInfo*		extra_info;										// Extra information about this item in the chain
//////
// END
///////////


#if defined(_LASM_COMPILE)
	// Other usages defined by app, see /libsf/exodus/tools/lasm/lasm.cpp for an example
	SLasmLineStatus		status;
	SDatum*				fileName;
#endif
};

void					iNode_init								(void);
SNode*					iNode_create							(SNode** root, SComp* comp = NULL, SNode* n_defaults[27/*_NODE_COUNT*/] = NULL);
u32						iiNode_getNextUid						(void);
SNode*					iNode_extrude							(SNode** root, s32 tnExtrudeDirection);
SNode*					iNode_bump								(SNode** root, s32 tnBump/*BumpDirection*/, s32 tnAnchor/*AnchorDirection*/);
SNode*					iNode_insert							(SNode** root, s32 tnDirection);
void					iNode_delete							(SNode** root, bool tlDeleteSelf = true);
void					iNode_orphanize							(SNode** root);
void					iNode_deleteAll_politely				(SNode** root, SNode* nodeStopper, SNode* nodeStopper2, bool tlDeleteSelf, SNodeFlags* nodeFlags);

// Bitmap
SBitmap*				iNode_renderBitmap						(SNode* node, s32 tnMaxTokenLength = 6, s32 tnMaxOverallLength = 12, f64 tfRodLength = 8.0, s32 tnMarginWidth = 2, s32 tnBorderWidth = 1, bool tlIncludeExtraInfo = false, bool tlGoDeeper = true, SNodeFlags* nodeFlags = &gsfNodeFlags_all, bool tlDeeperNodesExtendInAllDirections = true);
void					iiNode_renderBitmap						(SNode* node, SNode* nodeStopper1, SNode* nodeStopper2, s32 tnMaxTokenLength, s32 tnMaxOverallLength, SNodeProps props[], s32 tnPropsCount, u32 tnIter_uid, bool tlIncludeExtraInfo, bool tlGoDeeper = true, SNodeFlags* nodeFlags = &gsfNodeFlags_all, bool tlDeeperNodesExtendInAllDirections = true);
void					iiNode_get_bitmapExtents				(SNode* node, SNode* nodeStopper1, SNode* nodeStopper2, s32 tnArrivalDirection, SBitmap* bmp, RECT* rc, POINTS p_anchor, POINTS p_arrival, f64 tfRodLength, u32 tnIter_uid, SNodeProps* props, bool tlGoDeeper = true, SNodeFlags* nodeFlags = &gsfNodeFlags_all, bool tlDeeperNodesExtendInAllDirections = true);

// 	// OpenGL
// 	void					iiNode_renderGrace						(SNode* node, SNode* nodeStopper1, SNode* nodeStopper2, s32 tnMaxTokenLength, s32 tnMaxOverallLength, SNodeProps props[], s32 tnPropsCount, u32 tnIter_uid,								bool tlGoDeeper = true, SNodeFlags* nodeFlags = &gsfNodeFlags_all, bool tlDeeperNodesExtendInAllDirections = true);
// 	void					iiNode_get_graceExtents					(SNode* node, SNode* nodeStopper1, SNode* nodeStopper2, s32 tnArrivalDirection, SBitmap* bmp, SGraceLine* line, POINTS p_arrival, f64 tfRodLength, u32 tnIter_uid, SNodeProps* props,	bool tlGoDeeper = true, SNodeFlags* nodeFlags = &gsfNodeFlags_all, bool tlDeeperNodesExtendInAllDirections = true);


// Datum functions
void*					iDatum_allocateSpace					(SDatum* datum,	s32 dataLength, s8 fillChar = 0);
SDatum*					iDatum_allocate							(const void* data, s32 dataLength = -1);
bool					iDatum_appendData						(SDatum* datum, s8* data, s32 tnAppendLength);

void					iDatum_duplicate						(SDatum* datum, cvp data, s32 dataLength = -1);
void					iDatum_duplicate						(SDatum* datumDst, SDatum* datumSrc);
void					iDatum_duplicate_byRef					(SDatum* datumDst, SDatum* datumSrc);
SDatum*					iDatum_duplicate						(SDatum* datum);
void					iDatum_duplicate_fromComp				(SDatum* datum, SComp* comp);
void					iiDatum_duplicate_fromComp				(SDatum* datum, SComp* comp);
SDatum*					iDatum_populate_fromComp				(SDatum* datum, SComp* comp);
bool					iDatum_append_comp						(SDatum* datum, SComp* comp);

s32						iDatum_getAs_s32						(SDatum* datum);
s64						iDatum_getAs_s64						(SDatum* datum);

s32						iDatum_setAll							(SDatum* datum, u8 c);
bool					iDatum_resize							(SDatum* datum, s32 newDataLength);
s32						iDatum_compare							(SDatum* datumLeft, SDatum* datumRight);
s32						iDatum_compare							(SDatum* datumLeft, void*  data, s32 dataLength);
s32						iDatum_compare							(SDatum* datumLeft, void*  data, u32 dataLength);
s32						iDatum_contains							(SDatum* haystack, SDatum* needle, bool tlCaseCompare = false, s32 tnOccurrence = 1);
s32						iDatum_contains							(SDatum* haystack, s8* needle, s32 needleLength = -1, bool tlCaseCompare = false, s32 tnOccurrence = 1);
void					iDatum_delete							(SDatum** datum);
void					iDatum_delete							(SDatum* datum, bool tlDeleteSelf);
void					iiDatum_delete							(SDatum* datum);

SProperty*				iProperty_allocateAs_character_fromComp	(SComp* name, SComp* value, s32 tnOverrideNameLength = -1, s32 tnOverrideValueLength = -1);
SProperty*				iProperty_allocateAs_character			(cu8* tcName, s32 tnNameLength, cu8* tcValue, s32 tnValueLength);
SProperty*				iProperty_allocateAs_s32				(cu8* tcName, s32 tnNameLength, s32 tnValue);
SProperty*				iProperty_allocateAs_s32				(SDatum* name, s32 tnValue);
SProperty*				iiProperty_allocate						(SDatum* name, SVariable* value, SDatum* value_datum = NULL);
void					iProperty_delete						(SProperty** p);
SProperty*				iProperty_delete						(SProperty* p, bool tlDeleteSelf);
s32						iProperty_iterate						(SDatumCallback* cb, SDatum* properties);

void					iBuilder_verifySizeForNewBytes			(SBuilder* builder, u32 tnDataLength);
void					iBuilder_createAndInitialize			(SBuilder** builder, u32 tnAllocationBlockSize = 4096);
bool					iBuilder_isPointer						(SBuilder* builder, uptr testptr, void** outPtr = NULL);
cs8*					iBuilder_appendData						(SBuilder* builder, SDatum* data);
void*					iBuilder_appendData						(SBuilder* builder, void* tcData, u32 tnDataLength = (u32)-1);
u8*						iBuilder_append_uptr					(SBuilder* builder, uptr tnValue);
u8*						iBuilder_appendCrLf						(SBuilder* builder);
u8*						iBuilder_appendWhitespaces				(SBuilder* builder, s32 tnCount, u8 cWhitespaceChar = 32);
void					iBuilder_delete							(SBuilder* builder, u32 tnStartOffset, u32 tnDeleteLength);
void					iBuilder_reset							(SBuilder* builder);
void					iBuilder_rewind							(SBuilder* builder);
s8*						iBuilder_allocateBytes					(SBuilder* builder, u32 tnDataLength);
void					iBuilder_backoffTrailingWhitespaces		(SBuilder* builder);
void					iBuilder_setSize						(SBuilder* builder, u32 tnBufferLength);
void					iBuilder_freeAndRelease					(SBuilder** builder);
u32						iBuilder_asciiWriteOutFile				(SBuilder* builder, cu8* tcPathname, bool tlAppend = false);
bool					iBuilder_asciiReadFromFile				(SBuilder** builder, cu8* tcPathname);
void					iBuilder_compactData					(SBuilder* builder, u32 tnStart, u32 tnStride, u32 tnCompactCallbackFunction);
s8*						iBuilder_insertBytes					(SBuilder* builder, u32 tnStart, u32 tnLength);
u32						iBuilder_binarySearch					(SBuilder* builderHaystack, s8* textNeedle, u32 needleLength, bool* tlFound, bool tlInsertIfNotFound);
s32						iBuilder_iterate						(SBuilder* builder, u32 tnStepSize, SBuilderCallback* cb, uptr _iterateFunc = NULL);
s32						iBuilder_iterate_N_to_N					(SBuilder* builder, u32 tnStepSize, u32 tnStartRecord, u32 tnStopRecord, SBuilderCallback* cb, uptr _iterateFunc = NULL);
s32						iBuilder_iterate2						(SBuilder* builder1, SBuilder* builder2, u32 tnStepSize1, u32 tnStepSize2, SBuilderCallback2* cb2, uptr _iterate2Func = NULL);
s32						iBuilder_iterate2_N_to_N				(SBuilder* builder1, SBuilder* builder2, u32 tnStepSize1, u32 tnStepSize2, u32 tnStartRecord, u32 tnStopRecord, SBuilderCallback2* cb2, uptr _iterate2Func = NULL);
void*					iBuilder_retrieveRecord					(SBuilder* builder, u32 tnStepSize, u32 tnN);

// Added to append "name = something" strings with a terminating CR/LF
s32						iBuilder_append_label_uptr				(SBuilder* builder, s8* tcLabelText, uptr udata);
s32						iBuilder_append_label_sptr				(SBuilder* builder, s8* tcLabelText, sptr sdata);
s32						iBuilder_append_label_text				(SBuilder* builder, s8* tcLabelText, s8* tcText);
s32						iBuilder_append_label_datum				(SBuilder* builder, s8* tcLabelText, SDatum* datum);
s32						iBuilder_append_label_logical			(SBuilder* builder, s8* tcLabelText, bool tlValue);

//////////
//
// Get the next comps Unique ID
//
//////
	bool				lInitialized_cs_compsUniqueIdAccess;
	u32					gnComps_nextUniqueId = 0;
	CRITICAL_SECTION	cs_compsUniqueIdAccess;
	u32 iiComps_getNextUid()
	{
		u32 lnValue;


		// Make sure it's initialized
		if (!lInitialized_cs_compsUniqueIdAccess)
		{
			InitializeCriticalSection(&cs_compsUniqueIdAccess);
			lInitialized_cs_compsUniqueIdAccess = true;
		}

		// Synchronized access
		EnterCriticalSection(&cs_compsUniqueIdAccess);

		// Get our value and increment
		lnValue = gnComps_nextUniqueId++;

		// All done
		LeaveCriticalSection(&cs_compsUniqueIdAccess);

		// Return that value
		return(lnValue);
	}
