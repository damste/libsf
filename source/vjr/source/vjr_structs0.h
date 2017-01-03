//////////
//
// /libsf/source/vjr/source/vjr_structs0.h
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
// Copyright (c) 2014-2017 by Rick C. Hodgin
//////
// Last update:
//     Jun.29.2014
//////
// Change log:
//     Jun.29.2014 - Initial creation
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




// Forward definition for references
struct SObject;
struct SVariable;
struct SField;
struct SEM;
struct SLine;
struct SComp;
struct SCompiler;
struct SFunction;
struct SObjPropMap;
struct SClassObj;
struct SFont;




struct SErrorInfo
{
	bool	error;				// Was there an error in processing?
	u32		errorNum;			// The error number
	SComp*	errorComp;			// The comp this error relates to (if any)
};

struct SSize
{
	union {
		s32		width;
		f32		fWidth;
	};
	union {
		s32		height;
		f32		fHeight;
	};
};

struct SRect
{
	s32			left;
	s32			top;
	s32			right;
	s32			bottom;
};

struct SXYS32
{
	s32			x;
	s32			y;
};


//////////
// Changes made here must sync up with iJDebiC_win()
// BEGIN
//////
	//////
		//
		struct SMouseData
		{
			POINT				positionInOsDesktop;					// Mouse position with regards to the entire desktop
			POINT				position;								// Mouse position in this window
			s32					wheelDeltaV;							// How far the vertical mouse wheel has scrolled
			s32					wheelDeltaH;							// How far the horizontal mouse wheel has scrolled
			bool				buttonLeft;								// Is the left mouse button down?
			bool				buttonMiddle;							// Is the middle mouse button down?
			bool				buttonRight;							// Is the right mouse button down?
			bool				buttonAnyDown;							// Is any mouse button down?
			bool				isCaps;									// Is caps lock on?
			bool				isCtrl;									// Is the control key down?
			bool				isAlt;									// Is the alt key down?
			bool				isShift;								// Is the shift key down?
		};

		struct SWindow
		{
			bool				isValid;								// When windows fall out of scope they are marked not valid

			HWND				hwnd;									// The window's hwnd
			SBitmap*			bmp;									// Accumulation buffer for drawing
			RECT				rc;										// Rectangle of window's physical position
			SObject*			obj;									// The top-level object being rendered in this window

			// Mouse data
			SMouseData			mousePrior;								// Mouse activity before the most recent mouse activity
			SMouseData			mouseCurrent;							// Current mouse activity

			// For manual movement
			bool				isMoving;								// Is this window moving?
			bool				isResizing;								// Is this window resizing?
			SMouseData			mouseMoveResizeStart;					// The mouse data within the window when the move or resize started
			RECT				rcMoveResizeStart;						// The location and size of the window when the move or resize started
			u32					resizingFrom;							// If resizing, the arrow (upper-left, upper-right, lower-left, lower-right)
			s32					movingLastDeltaX;						// When moving, this was the last delta-X for the last redraw
			s32					movingLastDeltaY;						// When moving, this was the last delta-Y for the last redraw

			// Updated as the mouse moves across the form
			POINT				mousePositionClick;						// When the mouse was last left-clicked, this is where it was clicked
			POINT				mousePositionClickScreen;				// In screen coordinates, the location where the mouse was last left-button clicked down

			CRITICAL_SECTION	cs;										// Atomic access
		};
		//
	//////
//////
// END
//////////


#if defined(_MSC_VER)
	#include "\libsf\utils\common\cpp_vjr\include\datum.h"
#elif defined(__GNUC__) || defined(__solaris__)
	#include "/libsf/utils/common/cpp_vjr/include/datum.h"
#else
	#error Unknown target for compilation (must be Windows, Linux, or Solaris (OpenIndiana))
#endif

struct STranslate
{
	void*		p1;														// Pointer 1
	void*		p2;														// Pointer 2
};

// struct STranslateExtra
// {
// 	void*		p1;														// Pointer 1
// 	void*		p2;														// Pointer 2
//
// 	// Extra information
// 	union {
// 		struct {
// 			u8		u8Data1;
// 			u8		u8Data2;
// 			u8		u8Data3;
// 			u8		u8Data4;
// 		};
// 		struct {
// 			s8		s8Data1;
// 			s8		s8Data2;
// 			s8		s8Data3;
// 			s8		s8Data4;
// 		};
// 		struct {
// 			u16		u16Data1;
// 			u16		u16Data2;
// 		};
// 		struct {
// 			s16		s16Data1;
// 			s16		s16Data2;
// 		};
// 		u32		u32Data;
// 		s32		s32Data;
// 		bool	used;
// 		void*	extra;
// 	};
// };

struct SAllDatetime
{
	u32			nYear;
	u32			nMonth;
	u32			nDay;
	u32			nHour;
	u32			nMinute;
	u32			nSecond;

	bool		lMillisecondValid;
	s32			nMillisecond;

	bool		lMicrosecondValid;
	s32			nMicrosecond;

	bool		lNanosecondValid;
	s32			nNanosecond;

	f64			fVal64;
};

#define _SVARIABLE_DEFINED 1
struct SVariable
{
	SLL			ll;
	SVariable*	indirect;												// If non-NULL, and not an object or this variable is an indirect reference to an underlying variable.
	bool		isVarAllocated;											// If true, this variable structure was allocated, and needs to be released upon delete.
	bool		isSysVar;												// If true, it's a system variable and cannot be deleted
	bool		isProtected;											// If true, the variable has been specifically protected and cannot be deleted until un-protected

	// User-defined data (not automatically maintained by VJr's variable-handling algorithms)
	union {
		sptr	_meta;													// Accessible as an integer for testing values
		void*	meta;													// Any meta data for this variable.  Not explicitly maintained by VJr, but is up to whatever uses it to maintain the data set/linked here
	};

	// If this variable is related to a component, indicate it here
	SComp*		compRelated;											// Can vary regularly, but when available at compile time and in immediate scope, relates to a component

	// Variable data
	SDatum		name;													// Name of this variable (alway allocated)
	u32			arrayRows;												// If created as an array, how many rows
	union {
		u32		arrayCols;												// If created as an array, how many columns
		u32		vectorElements;											// If created as a vector, how many elements?
	};

	// Variable content based on type
	u32			varType;												// Variable type (see _VAR_TYPE_* constants)
	bool		isVarTypeFixed;											// If true, the variable type is  fixed and cannot be altered, only populated into (used for dbf fields)
	bool		isValueAllocated;										// If true, the data pointed to by this->value.data_s8, or this->obj, or this->bmp, or this->thisCode was allocated
	union {
		SObject*		obj;											// The object this item relates to.  If isValueAllocated is set, this variable owns the object.
		SFunction*		thisCode;										// Pointer to the code block this relates to
		SBitmap*		bmp;											// The bitmap this item points to
		SField*			field;											// Pointer to a table/cursor field
		union {
			// The actual value
			SDatum		value;
			SDatum		current;
		};
		// Note:  If it's an array, then this->value is populated with a repeating structure of SVariable pointers, one for every array element (arrayRows * arrayCols)
		// Note:  If it's a vector, then this->value is populated with a repeating structure of SVariable pointers, one for every vector element (vectorCols)
	};

	// If assign or access
	SEM*		firstAccess;											// Source code executed whenever this variable is accessed
	SEM*		firstAssign;											// Source code executed whenever this variable is assigned
};

struct SVarTypeXlat
{
	s32		varType;													// _VAR_TYPE_* constants

	cs8*	keyword;													// Keyword for each type, such as "s8" or "numeric"
	u32		keywordLength;												// Length of the keyword
};

struct SBaseClassMap
{
	s32				objType;											// Translation between objType...

	// Class name
	cu8*			baseclassName;										// ...and the text-based name of the base class
	s32				baseclassNameLength;

	union {
		uptr			_objProps;
		SObjPropMap*	objProps;										// Root property map for this object
	};

	s32				objPropsCount;										// Number of object properties as defined
};

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

struct SCompiler;
struct SBreakpoint;
struct SExtraInfo;

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

// Structure of parsed components on a line, tokens by another name
#define _SCOMP_DEFINED

cu32 _HTML_TYPE_TEXT		= 1;
cu32 _HTML_TYPE_LINE		= 2;
cu32 _HTML_TYPE_LINK		= 3;

struct SCompHtml
{
	// What type of html element is it?
	s32				htmlType;										// See _HTML_TYPE_* constants

	// For line and text
	SBgra			backColor;										// Background color
	SBgra			foreColor;										// Foreground color

	// Text
	union {
		SDatum*		text;											// Text content to render
		SBitmap*	bmp;
	};

	// Link
	SDatum*			targetUrl;
};

struct SComp
{
	SLL				ll;												// 2-way link list

	// Information about the component
	SNode*			node;											// The node this component relates to
	SLine*			line;											// The line this component relates to
	s32				iCode;											// Refer to _ICODE_* constants
	u32				iCat;											// Refer to _ICAT_* constants, and use iCat() macro for accessing the lower portion without bit flags influencing its value
	SBgra*			color;											// Syntax highlight color
	s32				start;											// Start into the indicates line's source code
	s32				length;											// Length of the component
	s32				nbspCount;										// Number of non-breaking-spaces in this component

	// Combined components into this one
	SComp*			firstCombined;									// Combined components, like [a].[b] combined into [a.b] dot variable, keeps [.] and [b] in this
	SComp*			firstWhitespace;								// Whitespaces are removed for ease of compilation, but they persist here for rendering and reference
	SComp*			firstComment;									// Comments within a line are removed, these include "/*comments*/" and "// comments"

	// Should the syntax highlighting for this component be bold?
	bool			useBoldFont;									// Syntax highlight font should be bold?

	// For each compilation pass, components can be marked in error or warning or both
	bool			isError;										// Is this component part of an error?
	bool			isWarning;										// Is this component part of a warning?

	// Was this component allocated?
	bool			llAllocated;									// If true, it should be deleted

	// For selected components
	SBgra*			overrideSelectionBackColor;
	SBgra*			overrideSelectionForeColor;

	// If this is a character that matches something (the closest parenthesis, bracket, or brace) then this color will be populated
	SBgra*			overrideMatchingForeColor;
	SBgra*			overrideMatchingBackColor;

	// If it's an html
	SCompHtml*		html;											// An html

	// For faster rendering in source code windows
	SBmpCache*		bc;												// Holds drawn things (casks for example)
};

struct SCompParams
{
	s32				cpType;											// See _CP_TYPE constants

	// Based on _CP_TYPE, one of these will be populated
	union {
		SComp*		comp;
		SVariable*	var;
	};
};

// Generic callback support
struct SCallback
{

	//////////
	// Callback function
	//////
		union {
			uptr	_func;
			bool	(*func)		(SCallback* cb);
		};


	//////////
	// Various data items available
	//////
		union {
			void*		data1;
			SLine*		line;
			SLine*		line1;
			SComp*		comp;
			SComp*		comp1;
			SObject*	obj1;
		};

		union {
			void*		data2;
			SLine*		line2;
			SComp*		comp2;
			SObject*	obj2;
		};

		union
		{
			void*		data3;
			SLine*		line3;
			SComp*		comp3;
			SObject*	obj3;
		};


	//////////
	// Extra information
	//////
		bool		flag;
		void*		x;
		s32			value1;
		s32			value2;
		s32			value3;

};

// Used for pushing values onto the stack for the physical DLL dispatch from VJr into the DLL code
struct SDllVals
{
	union {
		s16			_s16;			// Signed integer
		s32			_s32;
		s64			_s64;

		f32			_f32;			// Floating point
		f64			_f64;

		s16			_u16;			// Unsigned integer
		s32			_u32;
		s64			_u64;

		s8*			_s8p;			// Pointer to character data
		void*		_vp;			// General pointer to data (byRef values)
		IDispatch*	_idispatch;		// An IDispatch Windows object

		SDatum		_datum;			// Used for creating a copy of character data when it's passed by value (so any changes made are made to the copy)
	};
};

struct SEngineLoad
{
	SFunction*	firstFunc;					// First new function that was loaded in parsing the source code
	SDllFunc*	firstDllFunc;				// First new DLL function that was loaded in parsing the source code
	SClassObj*	firstClassObj;				// First new class that was loaded
};
