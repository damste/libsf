//////////
//
// /libsf/source/vjr/source/vjr_structs.h
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
// Copyright (c) 2014-2015 by Rick C. Hodgin
//////
// Last update:
//     Feb.12.2014
//////
// Change log:
//     Feb.12.2014 - Initial creation
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




// Julian and seconds stored separately
struct SDateTime
{
	s32		julian;							// Julian day number
	f32		seconds;						// Seconds elapsed since midnight
};

// Julian-seconds stored as an integer
struct SDateTimeX
{
	u64		jseconds;						// Julian-seconds, formula is the sum of:	/ nanosecond  * 1    \		// Note:  Only one of these is used for input, but both are extracted for output
											//											\ millisecond * 1000 /
											//											+ second      * 1000000
											//											+ minute      * 1000000 * 60
											//											+ hour        * 1000000 * 60 * 60
											//											+ julian      * 1000000 * 60 * 60 * 24
};

// Text format of YyyyMmDd date, as in 20150404 for Apr.04.2015
struct SDate
{
	u8		yyyy[4];						// 4-digit year
	u8		mm[2];							// 2-digit month
	u8		dd[2];							// 2-digit day
};

struct SHover
{
	HWND		hwnd;						// Window for the hover
	SBitmap*	bmp;						// Bitmap for the hover text
};

// Class objects are only held for loaded classes, for templates.
// All other classes exist as base classes known to the system, or 
struct SClassObj
{
	SLL			ll;							// Link list
	SDatum		name;						// Class name

	s32			classObjType;				// See _CLASS_OBJECT_* constants
	SObject*	baseObj;					// The base class used to create instances of this class

	SEM*		sem;						// SEM this classobj was defined in
	SLine*		firstLine;					// First line in source code where the DEFINE CLASS begins
	SLine*		lastLine;					// Last line in source code where the ENDDEFINE ends
};

struct SReturnsParams
{
	// If there's an error, these are set
	SErrorInfo		ei;									// If any error info needs logged, it will be here

	// Return parameters
	SVariable*		rp[_MAX_RETURNS_COUNT];				// Return parameters
	s32				rpCount;							// Actual number of return parameters specified
	s32				rpMax;								// Maximum number allowed
	s32				rpMin;								// Minimum number required

	// Input parameters
	SVariable*		ip[_MAX_PARAMS_COUNT];			// Input parameters
	s32				ipCount;							// Number of input parameters actually passed
};


//////////
// Structures used for processing
//////
	//////////
	// Changes made here must sync up with iJDebiC_thisCode()
	// BEGIN
	//////
		//////
			//
// TODO:  These should be moved to a shared file for use with iJDebiC_thisCode()
			struct SSourceCode
			{
				SFunction*		func;					// Function source code
				SFunction*		firstAdhoc;				// First adhoc in this block

				// The first class object defined in this source code (only present in thisCode->def, never copied into thisCode->live)
				SClassObj*		firstClassObj;			// Also SET LOCALCLASSLIB definitions

				// Related to this function
				SVariable*		returns;				// The first return variable declared
				SVariable*		params;					// The function parameters
				SVariable*		privates;				// The first private variable declared
				SVariable*		locals;					// The first local variable declared
				SVariable*		scoped;					// The first scoped/temporary variable used by the function

				// Counts for populated values as this structure is fixed and reused on the stack, and to save speed it does not delete variables, but only large allocations upon exit
				s32				returnsCount;			// Number of valid returns in returns
				s32				paramsCount;			// Number of valid parameters in params
				s32				privatesCount;			// Number of valid private variables in privates
				s32				localsCount;			// Number of valid locals in locals
				s32				scopedCount;			// Number of valid scoped variables in scoped

				// Temporary returns/params level for nested functions in flight
				SReturnsParams	rp[_MAX_NESTED_FUNCTION_CALLS];
				// Note:  rp[0].rp[N] contains the return values for this function

				// Contextual references
				SObject*		_this;					// Current object
			};

			struct SThisCode
			{
				SLL				ll;

				SSourceCode*	def;					// Defined from compile time
				SSourceCode		live;					// Live state in this instance at this level
			};
			//
		//////
	//////
	// END
	//////////


#define _MAX_DLL_HMODULES 5					// kernel32.dll, gdi32.dll, user32.dll, mpr.dll, and advapi32.dll

struct SDllLib
{
	SLL*		ll;

	SDatum			dllName;						// DLL name
	HMODULE			dllHandle[_MAX_DLL_HMODULES];	// Handle to the DLL
	s32				refCount;						// Reference count
};

struct SDllFuncParam
{
	u32				type;					// Field type, see _VAR_TYPE_DLL_* constants
	SDatum			name;					// Parameter name

	// Instance values
	SVariable*		associatedVariable;		// The variable associated with this
	u32				udfSetting;				// Either _UDFPARMS_REFERENCE or _UDFPARMS_VALUE (indicates if passed by pointer or value, from the @ in the definition)
};

// DECLARE INTEGER myFunction IN myDll.dll ALIAS myFunc INTEGER nHandle, STRING cDesc
struct SDllFunc
{
	SLL				ll;

	// DECLARE [returnType]
	SDllFuncParam	rp;						// Return parameter

	// [name] ... ALIAS [alias]
	SDatum			name;					// Function name
	SDatum			alias;					// Alias name

	// IN [library]
	SDllLib*		dlib;					// DLL load instance
	void*			funcAddress;			// GetProcAddress() of the function within the DLL
	s32				callCount;				// Number of times this DLL was referenced

	// NOPROTOTYPE and VARIADIC options
#if defined(__64_BIT_COMPILER__)
	// Only used on VJr 64-bit
	bool			noPrototype;			// Was NOPROTOTYPE specified?
	bool			isVariadic;				// Was VARIADIC specified?
#endif

	// [inputType1 inputName1], [inputType2 inputName2], ... [inputTypeN inputNameN]
	s32				ipCount;				// Number of parameters specified
	SDllFuncParam	ip[_MAX_DLL_PARAMS];	// Input parameter definitions

	// Add-ons for DLL function tracking
	SThisCode*		onAccess;				// Called whenever this DLL is accessed (used) in source code
	SThisCode*		onAssign;				// Called whenever the return result from the DLL is received
};

// Note:  See vjr_structs0.h for struct SDllVals


struct SEvent
{
	// User/class code applied to this event atop the default handler
	SFunction*	userEventCode;

	// Default handlers
	union {
		uptr	_event;

		// Based on the event type, the appropriate form is called
		bool	(*event_1)		(SWindow* win, SObject* obj);
		bool	(*event_2)		(SWindow* win, SObject* obj, SObject* obj1);
		bool	(*event_3)		(SWindow* win, SObject* obj, SVariable* var1);
		bool	(*event_4)		(SWindow* win, SObject* obj, SVariable* var1, SVariable* var2);
		bool	(*event_5)		(SWindow* win, SObject* obj, SVariable* var1, SVariable* var2, SVariable* var3);
		bool	(*event_6)		(SWindow* win, SObject* obj, SVariable* var1, SVariable* var2, SVariable* var3, SVariable* var4);
		bool	(*event_7)		(SWindow* win, SObject* obj, SVariable* var1, SVariable* var2, SVariable* var3, SVariable* var4, SVariable* var5);
		bool	(*event_8)		(SWindow* win, SObject* obj, SVariable* var1, SVariable* var2, SVariable* var3, SVariable* var4, SVariable* var5, SVariable* var6);
		bool	(*event_9)		(SWindow* win, SObject* obj, SVariable* var1, SVariable* var2, SVariable* var3, SVariable* var4, SVariable* var5, SVariable* var6, SVariable* var7);
		bool	(*event_10)		(SWindow* win, SObject* obj, SVariable* var1, SVariable* var2, SVariable* var3, SVariable* var4, SVariable* var5, SVariable* var6, SVariable* var7, SVariable* var8);
		bool	(*event_11)		(SWindow* win, SObject* obj, RECT* rc);
		bool	(*event_12)		(SWindow* win, SObject* obj, void* p);
	};
};

struct SEvents
{
	// Array of events for the class
	SEvent		methods[_EVENT_MAX_COUNT];							// Pointer to the the array for every built-in event/method handler

	// Object's render function (or custom render function)
	union {
		uptr	_renderFunc;
		u32		(*renderFunc)(SObject* obj);						// By default, for the object type, calls iSubobj_render*(), but allows for custom rendering algorithms
	};

	// Holds status for changes
	u32			_lastClick;											// When the last mouseClickEx was called, what was the tnClick value?
	u32			thisClick;											// The tnClick parameter passed below, it is the _MOUSE_*_BUTTON amalgam based on the current mouse button state
	bool		isMouseDown;										// Is the mouse down over this item?
	bool		isMouseOver;										// Used for signaling enter/leave events

	u32			startHoverTickCount;								// At each last mouseMove the startHoverTickCount is set, if the interval elapses the hover event is triggered
	SHover		hover;												// If there's an active hover, this value is not NULL
	bool		hasHoverSignaled;									// If the hover has signaled already on this control

	// onMouseMove
	SVariable*	varX_onMouseMove;
	SVariable*	varY_onMouseMove;
	SVariable*	varCtrl_onMouseMove;
	SVariable*	varAlt_onMouseMove;
	SVariable*	varShift_onMouseMove;
	SVariable*	varClick_onMouseMove;

	// onMouseDown
	SVariable*	varX_onMouseDown;
	SVariable*	varY_onMouseDown;
	SVariable*	varCtrl_onMouseDown;
	SVariable*	varAlt_onMouseDown;
	SVariable*	varShift_onMouseDown;
	SVariable*	varClick_onMouseDown;

	// onMouseClickEx
	SVariable*	varX_onMouseClickEx;
	SVariable*	varY_onMouseClickEx;
	SVariable*	varCtrl_onMouseClickEx;
	SVariable*	varAlt_onMouseClickEx;
	SVariable*	varShift_onMouseClickEx;
	SVariable*	varClick_onMouseClickEx;

	// onMouseUp
	SVariable*	varX_onMouseUp;
	SVariable*	varY_onMouseUp;
	SVariable*	varCtrl_onMouseUp;
	SVariable*	varAlt_onMouseUp;
	SVariable*	varShift_onMouseUp;
	SVariable*	varClick_onMouseUp;

	// onMouseWheel
	SVariable*	varX_onMouseWheel;
	SVariable*	varY_onMouseWheel;
	SVariable*	varCtrl_onMouseWheel;
	SVariable*	varAlt_onMouseWheel;
	SVariable*	varShift_onMouseWheel;
	SVariable*	varClick_onMouseWheel;
	SVariable*	varDeltaY_onMouseWheel;

	// onKeyDown
	SVariable*	varCtrl_onKeyDown;
	SVariable*	varAlt_onKeyDown;
	SVariable*	varShift_onKeyDown;
	SVariable*	varCaps_onKeyDown;
	SVariable*	varAsciiChar_onKeyDown;
	SVariable*	varVKey_onKeyDown;
	SVariable*	varIsCAS_onKeyDown;
	SVariable*	varIsAscii_onKeyDown;

	// onKeyUp
	SVariable*	varCtrl_onKeyUp;
	SVariable*	varAlt_onKeyUp;
	SVariable*	varShift_onKeyUp;
	SVariable*	varCaps_onKeyUp;
	SVariable*	varAsciiChar_onKeyUp;
	SVariable*	varVKey_onKeyUp;
	SVariable*	varIsCAS_onKeyUp;
	SVariable*	varIsAscii_onKeyUp;

};

struct SProperties
{
	RECT		rcMax;												// The maximum rectangle for the form
	RECT		rcMin;												// The minimum rectangle for the form
	SFont*		font;												// Default font for the control

	// For form/subform object processing
	bool		hasFocus;											// Does this object have focus?
 	bool		processKeyPreviewEvents;							// Do keystrokes for controls on the form go through the form's Key* events as well?
	bool		initializationComplete;								// Set only after the object has been initially set

	// For any SEM related to this control (typically only used on editbox classes)
	SEM*		sem;												// (SEM)		-- The content being edited

	// For Carousel
	SBitmap*	bmpTabs;											// (Carousel)	-- Bitmap holding the rendered tabs
	s32			bmpTabsScrolled;									// (Carousel)	-- How many pixels are the tabs scrolled (if the bmpTabs->bi.biWidth is bigger than the carousel's width, and one of the tabs beyond the width is active and displayed)
	SBuilder*	rcTabs;												// (Carousel)	-- An array of SObjCarouselTabData items, one for each rider's tab
};

struct SObjNodeData
{
	SObject*	obj;												// If the node was created so that A was linked to B, A is primary
	SBgra		color;												// Color for the node ball
	SDatum		label;												// An optional bit of text for the node hookup
};

// Nodes run from something to something else...
struct SObjNode
{
	// Link lists along from and to chains
	SLL				from_ll;										// Node link in the from chain
	SLL				to_ll;											// Node link in the to chain

	// From configuration
	SObjNodeData	from;											// The data for this node
	bool			from_isEast;									// Does the from node originate easterly?
	s32				from_slotNum;									// The node slot number for the from
	s32				from_maxTextLength;								// Maximum text length along this from_ll chain

	// To configuration
	SObjNodeData	to;												// ...and this is the to. :-)
	bool			to_isWest;										// Does the to terminate from the west?
	s32				to_slotNum;										// The node slot number for the to
	s32				to_maxTextLength;								// Maximum text length along this to_ll chain
};

struct SObjCarouselTabData
{
	SObject*	rider;												// The rider this tab relates to
	RECT		rc;													// Rectangle within carousel->p.bmpTabs

	bool		isMouseOver;										// Is the mouse currently over this item?
	bool		isMouseOverClose;									// Is the mouse currently over the close button?

	bool		isCloseable;										// Is this tab closable?
	RECT		rcClose;											// Closing 'x' if shown
};

struct SField
{
	SWorkArea*		wa;												// Pointer to the work area

	SFieldRecord1*	fr1;											// Pointer to the associated field record 1
	SFieldRecord2*	fr2;											// Pointer to the associated field record 2
};


//////////
// Changes made here must sync up with iJDebiC_obj()
// BEGIN
//////
	//////
		//
		struct SObject
		{
			SLL			ll;													// Linked list
			SObject*	parent;												// Pointer to parent object for this instance
			SObject*	firstChild;											// Pointer to child objects (all objects are containers)
			SObject*	firstControlPoint;									// Added for riders and carousels, indicates points within which allow rider movement and navigation

#ifdef _EXTRA_DEBUGGING_DATA
			SDatum		dbgBaseclass;
			SDatum		dbgClass;
			SDatum		dbgName;
#endif

			// Defined class, class information
			s32			objType;											// Object base type/class (see _OBJECT_TYPE_* constants)

			// Object flags
			bool		isRendered;											// Is it rendered (can be rendered even if it's not visible)?
			bool		isPublished;										// Should this control be published?  Every object has a .lockScreen property which allows it to not be published while changes are made.
			bool		isDirtyRender;										// Is set if this or any child object needs re-rendered
			bool		isDirtyPublish;										// Is set if this or any child object needs re-published


			//////////
			// Object size in pixels, per the .Left, .Top, .Width, and .Height properties
			//////
				RECT		rc;												// Object's current position in its parent
				RECT		rco;											// Object's original position in its parent
				RECT		rcp;											// Original size of parent at creation
				RECT		rcClient;										// Client portion within the size of the object
				RECT		rcExtra;										// An extra portion used for object-specific components, such as rider tab location on carousels


			//////////
			// Common properties that are literal(p) and allocated(pa) values
			//////
				SProperties		p;											// Common object properties
				SVariable**		props;										// An allocated array of properties (varies in size by object)
				s32				propsCount;									// The number of property variables allocated

				// Related position in the member hierarchy
				SVariable*	firstProperty;									// User-defined property (design time and runtime)
				SFunction*	firstMethod;									// User-defined methods (design time and runtime)

				// Related access and assign methods
				bool		anyPropertyHasAccessOrAssignMethods;
				SFunction*	firstAccess;									// User-defined property access methods (design time and runtime)
				SFunction*	firstAssign;									// User-defined property assignment methods (design time and runtime)

				// Events
				SEvents		ev;												// Events for this object


			//////////
			// Base drawing canvas
			//////
				SBitmap*	bmp;											// If exists, canvas for the content
				SBitmap*	bmpPriorRendered;								// Used for speedups when not isDirty
				SBmpCache*	bc;												// For certain compute intensive operations (color gradient controls), the bitmap is only drawn/computed once and then copied thereafter, unless any of eight data points change
				// If not scaled:
				s32			scrollOffsetX;									// If the bmp->bi coordinates are larger than its display area, the upper-left X coordinate
				s32			scrollOffsetY;									// ...the upper-left Y coordinate
				// If scaled, updated only during publish():
				bool		isScaled;										// If the bmp->bi coordinates are larger than its display area, should it be scaled?
				SBitmap*	bmpScaled;										// The bmp scaled into RC's size


#ifdef _GRACE_OGL
			//////////
			// OpenGL
			//////
				// Visualization
				SGraceOgl	ogl;											// Open GL coordinates

				// Nodes connect to this object on the left or top
				SObjNode*	toLeft;											// First node in the west direction
				SObjNode*	toTop;											// First node in the east direction

				// This node connects to other things from the right or bottom
				SObjNode*	fromRight;										// First node in the north direction
				SObjNode*	fromBottom;										// First node in the south direction
#endif
		};
		typedef SObject* SObjectp;
		//
	//////
//////
// END
//////////


struct SFocusHighlight
{
	bool		isValid;											// Is this item valid?

	SWindow*	win;												// The window this focus highlight entry relates to
	SObject*	obj;												// The object being focused

	HWND		hwnd;												// The HWND for this window
	HRGN		hrgn;												// Handle to the clip region
	HBRUSH		readWriteBrush;										// Read-write color, bluish
	HBRUSH		readOnlyBrush;										// Read-only color, reddish

	RECT		rc;													// In screen coordinates
};

struct STooltip
{
	bool		isValid;											// Is this item valid?

	SObject*	obj;												// The object owning the tip
	s32			timeoutMs;											// Tooltips have a lifetime... in milliseconds

	bool		allowMove;											// Can the tooltip be moved?
	bool		allowSticky;										// Can they pin the tooltip so it doesn't expire?

	HWND		hwnd;												// The HWND for this window
	RECT		rc;													// In screen coordinates
	SBitmap*	bmp;												// The rendered bitmap for the tooltip
};

struct SSplash
{
	bool		isVisible;											// Is the splash screen still visible?
	bool		isEnabled;											// Is the splash screen active, able to have content displayed?

	HWND		hwnd;												// The HWND to the splash screen
	RECT		rc;													// In screen coordinates
	SBitmap*	bmp;												// The rendered bitmap
};

// For warnings, errors, and notes
struct SNoteLog
{
	SLL				ll;
	SDateTimeX		datetimex;										// When did the note get logged?

	SLine*			line;											// Associated line (if not already on a line)
	u32				start;											// Column the note begins on
	u32				end;											// Column the note ends on

	u32				number;											// A related number
	SDatum*			note;											// The message
};

struct SVjrDevice
{
	bool		lScreen;
	bool		lPrinter;
	bool		lFile;

	bool		lConsole;						// Echo on console?
	bool		lPrinterPrompt;					// Prompt for printer?
	s8			filenameBuffer[_MAX_PATH];		// Output filename (always append to it), it is reset with SET DEVICE TO FILE name
};
