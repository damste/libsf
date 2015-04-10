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
// Version 0.56
// Copyright (c) 2014 by Rick C. Hodgin
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




struct SDateTime
{
	u32		julian;														// Julian day number
	f32		seconds;													// Seconds elapsed since midnight
};

// Text format of YyyyMmDd date, as in 20150404 for Apr.04.2015
struct SDate
{
	u8		yyyy[4];						// 4-digit year
	u8		mm[4];							// 2-digit month
	u8		dd[4];							// 2-digit day
};

struct SFont
{
	bool		isUsed;						// Is this font slot used?
	HDC			hdc;						// Device context used for its creation

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
	s32			_sizeUsedForCreateFont;
	u32			_size;
	u32			_weight;
	u32			_italics;
	u32			_underline;
	TEXTMETRIC	tm;
};

struct SHover
{
	HWND		hwnd;						// Window for the hover
	SBitmap*	bmp;						// Bitmap for the hover text
};

// struct SEventsGeneral
// {
// 	union {
// 		uptr	_onLoad;					// Called to load anything needed by the init() event (holds a template/skeleton object)
// 		bool	(*onLoad)					(SThisCode* thisCode, SWindow* win, SObject* obj);
// 	};
// 	union {
// 		uptr	_onInit;					// Called to initialize anything
// 		bool	(*onInit)					(SThisCode* thisCode, SWindow* win, SObject* obj);
// 	};
// 	union {
// 		uptr	_onCreated;					// Called after initialization, before the object is sized
// 		bool	(*onCreated)				(SThisCode* thisCode, SWindow* win, SObject* obj);
// 	};
// 	union {
// 		uptr	_onResize;					// Called to size or resize the object
// 		bool	(*onResize)					(SThisCode* thisCode, SWindow* win, SObject* obj, SVariable* widthRequired_out, SVariable* heightRequired_out);
// 	};
// 	union {
// 		uptr	_onMoved;					// Called when the object has been moved
// 		bool	(*onMoved)					(SThisCode* thisCode, SWindow* win, SObject* obj, SVariable* xOverride_out, SVariable* yOverride_out);
// 	};
// 	union {
// 		uptr	_onRender;					// Called to render to bmp (returns if anything was drawn)
// 		bool	(*onRender)					(SThisCode* thisCode, SWindow* win, SObject* obj);
// 	};
// 	union {
// 		uptr	_onPublish;					// Called to publish the control onto the parent (which will populate bmpScale if need be)
// 		bool	(*onPublish)				(SThisCode* thisCode, SWindow* win, SObject* obj);
// 	};
// 	union {
// 		uptr	_onQueryUnload;				// Called before onDestroy, determines if the form should actually be destroyed
// 		bool	(*onQueryUnload)			(SThisCode* thisCode, SWindow* win, SObject* obj);
// 	};
// 	union {
// 		uptr	_onDestroy;					// Called when the object will be destroyed
// 		bool	(*onDestroy)				(SThisCode* thisCode, SWindow* win, SObject* obj);
// 	};
// 	union {
// 		uptr	_onUnload;					// Called after the object has been destroyed, to unload anything (holds a template/skeleton object)
// 		bool	(*onUnload)					(SThisCode* thisCode, SWindow* win, SObject* obj);
// 	};
// 	union {
// 		uptr	_onGotFocus;				// Called when the object receives focus (note multiple items can have simultaneous focus)
// 		bool	(*onGotFocus)				(SThisCode* thisCode, SWindow* win, SObject* obj);
// 	};
// 	union {
// 		uptr	_onLostFocus;				// Called when the object loses focus
// 		bool	(*onLostFocus)				(SThisCode* thisCode, SWindow* win, SObject* obj);
// 	};
// 	union {
// 		uptr	_onAddObject;				// Called when an object is added
// 		bool	(*onAddObject)				(SThisCode* thisCode, SWindow* win, SObject* obj);
// 	};
// 	union {
// 		uptr	_onAddProperty;				// Called when a property is added
// 		bool	(*onAddProperty)			(SThisCode* thisCode, SWindow* win, SObject* obj);
// 	};
// 	union {
// 		uptr	_onError;					// Called when an error is triggered in code on an object
// 		bool	(*onError)					(SThisCode* thisCode, SWindow* win, SObject* obj);
// 	};
// 	union {
// 		uptr	_onScrolled;				// Called when an object has been scrolled
// 		bool	(*onScrolled)				(SThisCode* thisCode, SWindow* win, SObject* obj);
// 	};
// 	union {
// 		uptr	_activate;					// Called when activated
// 		bool	(*activate)					(SThisCode* thisCode, SWindow* win, SObject* obj);
// 	};
// 	union {
// 		uptr	_deactivate;				// Called when deactivated
// 		bool	(*deactivate)				(SThisCode* thisCode, SWindow* win, SObject* obj);
// 	};
// 	union {
// 		uptr	_onSelect;					// When an option is selected
// 		bool	(*onSelect)					(SThisCode* thisCode, SWindow* win, SObject* obj, SObject* objItem);
// 	};
// 	union {
// 		uptr	_onDeselect;				// When an option is deselected
// 		bool	(*onDeselect)				(SThisCode* thisCode, SWindow* win, SObject* obj, SVariable* objItem);
// 	};
// 	union {
// 		uptr	_onInteractiveChange;		// Called when the data changes
// 		bool	(*onInteractiveChange)		(SThisCode* thisCode, SWindow* win, SObject* obj);
// 	};
// 	union {
// 		uptr	_onProgrammaticChange;		// Called when the data changes
// 		bool	(*onProgrammaticChange)		(SThisCode* thisCode, SWindow* win, SObject* obj);
// 	};
// 
// 
//////////
// Added for carousels and riders
//////
// 	union {
// 		uptr	_onSetActiveControl;		// Fired programmatically, specifies the object to make active
// 		bool	(*onSetActiveControl)		(SThisCode* thisCode, SWindow* win, SObject* obj, SVariable* objActive);
// 	};
// 	union {
// 		uptr	_onSpin;					// Fired programmatically, specifies the object to make active
// 		bool	(*onSpin)					(SThisCode* thisCode, SWindow* win, SObject* obj, SVariable* tnDelta, SVariable* tnDirection, SVariable* tnType);
// 	};
// };
// 
// struct SEventsMouse
// {
// 	// Holds status for changes
// 	u32			_lastClick;													// When the last mouseClickEx was called, what was the tnClick value?
// 	u32			thisClick;													// The tnClick parameter passed below, it is the _MOUSE_*_BUTTON amalgam based on the current mouse button state
// 	bool		isMouseDown;												// Is the mouse down over this item?
// 	bool		isMouseOver;												// Used for signaling enter/leave events
// 	u32			startHoverTickCount;										// At each last mouseMove the startHoverTickCount is set, if the interval elapses the hover event is triggered
// 	SHover*		hover;														// If there's an active hover, this value is not NULL
// 	bool		hasHoverSignaled;											// If the hover has signaled already on this control
//
// 	// Mouse callbacks issued by VJr to the internal object controller.
// 	// These will be translated by the internal object controller into executable VJr VXB code.
// 	// Return value indicates if the event should be sent to its parent instead (if NODEFAULT was issued during execution).
// 	union {
// 		uptr	_onMouseClickEx;
// 		bool	(*onMouseClickEx)		(SThisCode* thisCode, SWindow* win, SObject* obj, SVariable* varX, SVariable* varY, SVariable* varCtrl, SVariable* varAlt, SVariable* varShift, SVariable* varClick);	// varClick is 1=left, 2=middle, 4=right, 2^n bit positions indicate which buttons are clicked
// 	};
// 	union {
// 		uptr	_onMouseDblClickEx;
// 		bool	(*onMouseDblClickEx)	(SThisCode* thisCode, SWindow* win, SObject* obj, SVariable* varX, SVariable* varY, SVariable* varCtrl, SVariable* varAlt, SVariable* varShift, SVariable* varClick);
// 	};
// 	union {
// 		uptr	_onMouseWheel;
// 		bool	(*onMouseWheel)			(SThisCode* thisCode, SWindow* win, SObject* obj, SVariable* varX, SVariable* varY, SVariable* varCtrl, SVariable* varAlt, SVariable* varShift, SVariable* varClick, SVariable* varUnits);	// Signed units indicating direction and velocity
// 	};
// 	union {
// 		uptr	_onMouseMove;
// 		bool	(*onMouseMove)			(SThisCode* thisCode, SWindow* win, SObject* obj, SVariable* varX, SVariable* varY, SVariable* varCtrl, SVariable* varAlt, SVariable* varShift, SVariable* varClick);
// 	};
// 	union {
// 		uptr	_onMouseDown;
// 		bool	(*onMouseDown)			(SThisCode* thisCode, SWindow* win, SObject* obj, SVariable* varX, SVariable* varY, SVariable* varCtrl, SVariable* varAlt, SVariable* varShift, SVariable* varClick);
// 	};
// 	union {
// 		uptr	_onMouseUp;
// 		bool	(*onMouseUp)			(SThisCode* thisCode, SWindow* win, SObject* obj, SVariable* varX, SVariable* varY, SVariable* varCtrl, SVariable* varAlt, SVariable* varShift, SVariable* varClick);
// 	};
// 	union {
// 		uptr	_onMouseEnter;
// 		bool	(*onMouseEnter)			(SThisCode* thisCode, SWindow* win, SObject* obj);
// 	};
// 	union {
// 		uptr	_onMouseLeave;
// 		bool	(*onMouseLeave)			(SThisCode* thisCode, SWindow* win, SObject* obj);
// 	};
// 	union {
// 		uptr	_onMouseHover;
// 		bool	(*onMouseHover)			(SThisCode* thisCode, SWindow* win, SObject* obj, SVariable* varX, SVariable* varY, SVariable* varCtrl, SVariable* varAlt, SVariable* varShift, SVariable* varClick);
// 	};
// };
// 
// struct SEventsKeyboard
// {
// 	// Keyboard callbacks
// 	// Bool indicates if the event should be sent to its parent instead
// 	union {
// 		uptr	_onKeyDown;
// 		bool	(*onKeyDown)		(SThisCode* thisCode, SWindow* win, SObject* obj, SVariable* varCtrl, SVariable* varAlt, SVariable* varShift, SVariable* varCaps, SVariable* varAscii, SVariable* varVKey, SVariable* varIsCAS, SVariable* varIsAscii);
// 	};
// 	union {
// 		uptr	_onKeyUp;
// 		bool	(*onKeyUp)			(SThisCode* thisCode, SWindow* win, SObject* obj, SVariable* varCtrl, SVariable* varAlt, SVariable* varShift, SVariable* varCaps, SVariable* varAscii, SVariable* varVKey, SVariable* varIsCAS, SVariable* varIsAscii);
// 	};
//};

struct SEvent
{
	union {
		uptr	_event;

		// Based on the event type, the appropriate form is called
		bool	(*event_1)		(SThisCode* thisCode, SWindow* win, SObject* obj);
		bool	(*event_2)		(SThisCode* thisCode, SWindow* win, SObject* obj, SObject* obj1);
		bool	(*event_3)		(SThisCode* thisCode, SWindow* win, SObject* obj, SVariable* var1);
		bool	(*event_4)		(SThisCode* thisCode, SWindow* win, SObject* obj, SVariable* var1, SVariable* var2);
		bool	(*event_5)		(SThisCode* thisCode, SWindow* win, SObject* obj, SVariable* var1, SVariable* var2, SVariable* var3);
		bool	(*event_6)		(SThisCode* thisCode, SWindow* win, SObject* obj, SVariable* var1, SVariable* var2, SVariable* var3, SVariable* var4);
		bool	(*event_7)		(SThisCode* thisCode, SWindow* win, SObject* obj, SVariable* var1, SVariable* var2, SVariable* var3, SVariable* var4, SVariable* var5);
		bool	(*event_8)		(SThisCode* thisCode, SWindow* win, SObject* obj, SVariable* var1, SVariable* var2, SVariable* var3, SVariable* var4, SVariable* var5, SVariable* var6);
		bool	(*event_9)		(SThisCode* thisCode, SWindow* win, SObject* obj, SVariable* var1, SVariable* var2, SVariable* var3, SVariable* var4, SVariable* var5, SVariable* var6, SVariable* var7);
		bool	(*event_10)		(SThisCode* thisCode, SWindow* win, SObject* obj, SVariable* var1, SVariable* var2, SVariable* var3, SVariable* var4, SVariable* var5, SVariable* var6, SVariable* var7, SVariable* var8);
		bool	(*event_11)		(SThisCode* thisCode, SWindow* win, SObject* obj, RECT* rc);
		bool	(*event_12)		(SThisCode* thisCode, SWindow* win, SObject* obj, void* p);
	};
};

struct SEvents
{
	// Array of events for the class
	SEvent		methods[_EVENT_MAX_COUNT];							// Pointer to the the array for every built-in event/method handler

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

#ifdef _EXTRA_DEBUGGING_DATA
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
				SEM*		firstMethod;									// User-defined methods (design time and runtime)

				// Related access and assign methods
				bool		anyPropertyHasAccessOrAssignMethods;
				SEM*		firstAccess;									// User-defined property access methods (design time and runtime)
				SEM*		firstAssign;									// User-defined property assignment methods (design time and runtime)

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
