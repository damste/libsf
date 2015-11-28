//////////
//
// /libsf/source/vjr/source/objects/events.cpp
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
//     Jul.04.2014
//////
// Change log:
//     Jul.04.2014 - Initial creation
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
//
// Called to reset an object's events to its default
//
//////
	void iEvents_resetToDefault(SObject* obj, SObjEventMap* oemap, s32 tnOemapCount)
	{
		s32 lnI;


		// Make sure our environment is sane
		if (obj)
		{

			//////////
			// onMouseMove
			//////
				if (!obj->ev.varX_onMouseMove)				obj->ev.varX_onMouseMove		= iVariable_create(_VAR_TYPE_S32,		NULL, true);
				if (!obj->ev.varY_onMouseMove)				obj->ev.varY_onMouseMove		= iVariable_create(_VAR_TYPE_S32,		NULL, true);
				if (!obj->ev.varCtrl_onMouseMove)			obj->ev.varCtrl_onMouseMove		= iVariable_create(_VAR_TYPE_LOGICAL,	NULL, true);
				if (!obj->ev.varAlt_onMouseMove)			obj->ev.varAlt_onMouseMove		= iVariable_create(_VAR_TYPE_LOGICAL,	NULL, true);
				if (!obj->ev.varShift_onMouseMove)			obj->ev.varShift_onMouseMove	= iVariable_create(_VAR_TYPE_LOGICAL,	NULL, true);
				if (!obj->ev.varClick_onMouseMove)			obj->ev.varClick_onMouseMove	= iVariable_create(_VAR_TYPE_S32,		NULL, true);


			//////////
			// onMouseDown
			//////
				if (!obj->ev.varX_onMouseDown)				obj->ev.varX_onMouseDown		= iVariable_create(_VAR_TYPE_S32,		NULL, true);
				if (!obj->ev.varY_onMouseDown)				obj->ev.varY_onMouseDown		= iVariable_create(_VAR_TYPE_S32,		NULL, true);
				if (!obj->ev.varCtrl_onMouseDown)			obj->ev.varCtrl_onMouseDown		= iVariable_create(_VAR_TYPE_LOGICAL,	NULL, true);
				if (!obj->ev.varAlt_onMouseDown)			obj->ev.varAlt_onMouseDown		= iVariable_create(_VAR_TYPE_LOGICAL,	NULL, true);
				if (!obj->ev.varShift_onMouseDown)			obj->ev.varShift_onMouseDown	= iVariable_create(_VAR_TYPE_LOGICAL,	NULL, true);
				if (!obj->ev.varClick_onMouseDown)			obj->ev.varClick_onMouseDown	= iVariable_create(_VAR_TYPE_S32,		NULL, true);


			//////////
			// onMouseClickEx
			//////
				if (!obj->ev.varX_onMouseClickEx)			obj->ev.varX_onMouseClickEx		= iVariable_create(_VAR_TYPE_S32,		NULL, true);
				if (!obj->ev.varY_onMouseClickEx)			obj->ev.varY_onMouseClickEx		= iVariable_create(_VAR_TYPE_S32,		NULL, true);
				if (!obj->ev.varCtrl_onMouseClickEx)		obj->ev.varCtrl_onMouseClickEx	= iVariable_create(_VAR_TYPE_LOGICAL,	NULL, true);
				if (!obj->ev.varAlt_onMouseClickEx)			obj->ev.varAlt_onMouseClickEx	= iVariable_create(_VAR_TYPE_LOGICAL,	NULL, true);
				if (!obj->ev.varShift_onMouseClickEx)		obj->ev.varShift_onMouseClickEx	= iVariable_create(_VAR_TYPE_LOGICAL,	NULL, true);
				if (!obj->ev.varClick_onMouseClickEx)		obj->ev.varClick_onMouseClickEx	= iVariable_create(_VAR_TYPE_S32,		NULL, true);


			//////////
			// onMouseUp
			//////
				if (!obj->ev.varX_onMouseUp)				obj->ev.varX_onMouseUp			= iVariable_create(_VAR_TYPE_S32,		NULL, true);
				if (!obj->ev.varY_onMouseUp)				obj->ev.varY_onMouseUp			= iVariable_create(_VAR_TYPE_S32,		NULL, true);
				if (!obj->ev.varCtrl_onMouseUp)				obj->ev.varCtrl_onMouseUp		= iVariable_create(_VAR_TYPE_LOGICAL,	NULL, true);
				if (!obj->ev.varAlt_onMouseUp)				obj->ev.varAlt_onMouseUp		= iVariable_create(_VAR_TYPE_LOGICAL,	NULL, true);
				if (!obj->ev.varShift_onMouseUp)			obj->ev.varShift_onMouseUp		= iVariable_create(_VAR_TYPE_LOGICAL,	NULL, true);
				if (!obj->ev.varClick_onMouseUp)			obj->ev.varClick_onMouseUp		= iVariable_create(_VAR_TYPE_S32,		NULL, true);


			//////////
			// onMouseWheel
			//////
				if (!obj->ev.varX_onMouseWheel)				obj->ev.varX_onMouseWheel		= iVariable_create(_VAR_TYPE_S32,		NULL, true);
				if (!obj->ev.varY_onMouseWheel)				obj->ev.varY_onMouseWheel		= iVariable_create(_VAR_TYPE_S32,		NULL, true);
				if (!obj->ev.varCtrl_onMouseWheel)			obj->ev.varCtrl_onMouseWheel	= iVariable_create(_VAR_TYPE_LOGICAL,	NULL, true);
				if (!obj->ev.varAlt_onMouseWheel)			obj->ev.varAlt_onMouseWheel		= iVariable_create(_VAR_TYPE_LOGICAL,	NULL, true);
				if (!obj->ev.varShift_onMouseWheel)			obj->ev.varShift_onMouseWheel	= iVariable_create(_VAR_TYPE_LOGICAL,	NULL, true);
				if (!obj->ev.varClick_onMouseWheel)			obj->ev.varClick_onMouseWheel	= iVariable_create(_VAR_TYPE_S32,		NULL, true);
				if (!obj->ev.varDeltaY_onMouseWheel)		obj->ev.varDeltaY_onMouseWheel	= iVariable_create(_VAR_TYPE_S32,		NULL, true);


			//////////
			// onKeyDown
			//////
				if (!obj->ev.varCtrl_onKeyDown)				obj->ev.varCtrl_onKeyDown		= iVariable_create(_VAR_TYPE_LOGICAL,	NULL, true);
				if (!obj->ev.varAlt_onKeyDown)				obj->ev.varAlt_onKeyDown		= iVariable_create(_VAR_TYPE_LOGICAL,	NULL, true);
				if (!obj->ev.varShift_onKeyDown)			obj->ev.varShift_onKeyDown		= iVariable_create(_VAR_TYPE_LOGICAL,	NULL, true);
				if (!obj->ev.varCaps_onKeyDown)				obj->ev.varCaps_onKeyDown		= iVariable_create(_VAR_TYPE_LOGICAL,	NULL, true);
				if (!obj->ev.varAsciiChar_onKeyDown)		obj->ev.varAsciiChar_onKeyDown	= iVariable_create(_VAR_TYPE_U16,		NULL, true);
				if (!obj->ev.varVKey_onKeyDown)				obj->ev.varVKey_onKeyDown		= iVariable_create(_VAR_TYPE_S16,		NULL, true);
				if (!obj->ev.varIsCAS_onKeyDown)			obj->ev.varIsCAS_onKeyDown		= iVariable_create(_VAR_TYPE_LOGICAL,	NULL, true);
				if (!obj->ev.varIsAscii_onKeyDown)			obj->ev.varIsAscii_onKeyDown	= iVariable_create(_VAR_TYPE_LOGICAL,	NULL, true);


			//////////
			// onKeyUp
			//////
				if (!obj->ev.varCtrl_onKeyUp)				obj->ev.varCtrl_onKeyUp			= iVariable_create(_VAR_TYPE_LOGICAL,	NULL, true);
				if (!obj->ev.varAlt_onKeyUp)				obj->ev.varAlt_onKeyUp			= iVariable_create(_VAR_TYPE_LOGICAL,	NULL, true);
				if (!obj->ev.varShift_onKeyUp)				obj->ev.varShift_onKeyUp		= iVariable_create(_VAR_TYPE_LOGICAL,	NULL, true);
				if (!obj->ev.varCaps_onKeyUp)				obj->ev.varCaps_onKeyUp			= iVariable_create(_VAR_TYPE_LOGICAL,	NULL, true);
				if (!obj->ev.varAsciiChar_onKeyUp)			obj->ev.varAsciiChar_onKeyUp	= iVariable_create(_VAR_TYPE_U16,		NULL, true);
				if (!obj->ev.varVKey_onKeyUp)				obj->ev.varVKey_onKeyUp			= iVariable_create(_VAR_TYPE_S16,		NULL, true);
				if (!obj->ev.varIsCAS_onKeyUp)				obj->ev.varIsCAS_onKeyUp		= iVariable_create(_VAR_TYPE_LOGICAL,	NULL, true);
				if (!obj->ev.varIsAscii_onKeyUp)			obj->ev.varIsAscii_onKeyUp		= iVariable_create(_VAR_TYPE_LOGICAL,	NULL, true);


			//////////
			// Reset general events
			//////
				// Reset all to 0
				memset(&obj->ev.methods[0], 0, sizeof(obj->ev.methods));

				// Set default handlers for valid events
				for (lnI = 0; lnI < tnOemapCount; lnI++)
					obj->ev.methods[oemap[lnI].index]._event	= oemap[lnI]._defaultHandler;

		}
	}




//////////
//
// Called with strongly typed variables to dispatch the same event using weakly typed
// SVariable variables, so as to align with conventional source code processing.
//
//////
	bool iiEventDispatch_onMouseMove(SWindow* win, SObject* obj, s32 x, s32 y, bool tlCtrl, bool tlAlt, bool tlShift, u32 tnClicks)
	{
		//////////
		// Prepare for dispatch
		//////
			iVariable_set_s32		(obj->ev.varX_onMouseMove,		x);
			iVariable_set_s32		(obj->ev.varY_onMouseMove,		y);
			iVariable_set_logical	(obj->ev.varCtrl_onMouseMove,		((tlCtrl)	? _LOGICAL_TRUE : _LOGICAL_FALSE));
			iVariable_set_logical	(obj->ev.varAlt_onMouseMove,		((tlAlt)	? _LOGICAL_TRUE : _LOGICAL_FALSE));
			iVariable_set_logical	(obj->ev.varShift_onMouseMove,	((tlShift)	? _LOGICAL_TRUE : _LOGICAL_FALSE));
			iVariable_set_s32		(obj->ev.varClick_onMouseMove,	tnClicks);


		//////////
		// Dispatch
		//////
			return(iEngine_raise_event(_EVENT_ONMOUSEMOVE, win, obj));
	}




//////////
//
// Called with strongly typed variables to dispatch the same event using weakly typed
// SVariable variables, so as to align with conventional source code processing.
//
//////
	bool iiEventDispatch_onMouseDown(SWindow* win, SObject* obj, s32 x, s32 y, bool tlCtrl, bool tlAlt, bool tlShift, u32 tnClicks)
	{
		//////////
		// Prepare for dispatch
		//////
			iVariable_set_s32		(obj->ev.varX_onMouseDown,			x);
			iVariable_set_s32		(obj->ev.varY_onMouseDown,			y);
			iVariable_set_logical	(obj->ev.varCtrl_onMouseDown,			((tlCtrl)	? _LOGICAL_TRUE : _LOGICAL_FALSE));
			iVariable_set_logical	(obj->ev.varAlt_onMouseDown,			((tlAlt)	? _LOGICAL_TRUE : _LOGICAL_FALSE));
			iVariable_set_logical	(obj->ev.varShift_onMouseDown,		((tlShift)	? _LOGICAL_TRUE : _LOGICAL_FALSE));
			iVariable_set_s32		(obj->ev.varClick_onMouseDown,		tnClicks);


		//////////
		// Dispatch
		//////
			return(iEngine_raise_event(_EVENT_ONMOUSEDOWN, win, obj));
	}




//////////
//
// Called with strongly typed variables to dispatch the same event using weakly typed
// SVariable variables, so as to align with conventional source code processing.
//
//////
	bool iiEventDispatch_onMouseClickEx(SWindow* win, SObject* obj, s32 x, s32 y, bool tlCtrl, bool tlAlt, bool tlShift, u32 tnClicks)
	{
		//////////
		// Prepare for dispatch
		//////
			iVariable_set_s32		(obj->ev.varX_onMouseClickEx,			x);
			iVariable_set_s32		(obj->ev.varY_onMouseClickEx,			y);
			iVariable_set_logical	(obj->ev.varCtrl_onMouseClickEx,		((tlCtrl)	? _LOGICAL_TRUE : _LOGICAL_FALSE));
			iVariable_set_logical	(obj->ev.varAlt_onMouseClickEx,		((tlAlt)	? _LOGICAL_TRUE : _LOGICAL_FALSE));
			iVariable_set_logical	(obj->ev.varShift_onMouseClickEx,		((tlShift)	? _LOGICAL_TRUE : _LOGICAL_FALSE));
			iVariable_set_s32		(obj->ev.varClick_onMouseClickEx,		tnClicks);


		//////////
		// Dispatch
		//////
			return(iEngine_raise_event(_EVENT_ONMOUSECLICKEX, win, obj));
	}




//////////
//
// Called with strongly typed variables to dispatch the same event using weakly typed
// SVariable variables, so as to align with conventional source code processing.
//
//////
	bool iiEventDispatch_onMouseUp(SWindow* win, SObject* obj, s32 x, s32 y, bool tlCtrl, bool tlAlt, bool tlShift, u32 tnClicks)
	{
		//////////
		// Prepare for dispatch
		//////
			iVariable_set_s32		(obj->ev.varX_onMouseUp,			x);
			iVariable_set_s32		(obj->ev.varY_onMouseUp,			y);
			iVariable_set_logical	(obj->ev.varCtrl_onMouseUp,		((tlCtrl)	? _LOGICAL_TRUE : _LOGICAL_FALSE));
			iVariable_set_logical	(obj->ev.varAlt_onMouseUp,		((tlAlt)	? _LOGICAL_TRUE : _LOGICAL_FALSE));
			iVariable_set_logical	(obj->ev.varShift_onMouseUp,		((tlShift)	? _LOGICAL_TRUE : _LOGICAL_FALSE));
			iVariable_set_s32		(obj->ev.varClick_onMouseUp,		tnClicks);


		//////////
		// Dispatch
		//////
			return(iEngine_raise_event(_EVENT_ONMOUSEUP, win, obj));
	}




//////////
//
// Called with strongly typed variables to dispatch the same event using weakly typed
// SVariable variables, so as to align with conventional source code processing.
//
//////
	bool iiEventDispatch_onMouseWheel(SWindow* win, SObject* obj, s32 x, s32 y, bool tlCtrl, bool tlAlt, bool tlShift, u32 tnClicks, s32 tnDeltaY)
	{
		//////////
		// Prepare for dispatch
		//////
			iVariable_set_s32		(obj->ev.varX_onMouseWheel,			x);
			iVariable_set_s32		(obj->ev.varY_onMouseWheel,			y);
			iVariable_set_logical	(obj->ev.varCtrl_onMouseWheel,		((tlCtrl)	? _LOGICAL_TRUE : _LOGICAL_FALSE));
			iVariable_set_logical	(obj->ev.varAlt_onMouseWheel,			((tlAlt)	? _LOGICAL_TRUE : _LOGICAL_FALSE));
			iVariable_set_logical	(obj->ev.varShift_onMouseWheel,		((tlShift)	? _LOGICAL_TRUE : _LOGICAL_FALSE));
			iVariable_set_s32		(obj->ev.varClick_onMouseWheel,		tnClicks);
			iVariable_set_s32		(obj->ev.varDeltaY_onMouseWheel,		tnDeltaY);


		//////////
		// Dispatch
		//////
			return(iEngine_raise_event(_EVENT_ONMOUSEWHEEL, win, obj));
	}




//////////
//
// Called with strongly typed variables to dispatch the same event using weakly typed
// SVariable variables, so as to align with conventional source code processing.
//
//////
	bool iiEventDispatch_onKeyDown(SWindow* win, SObject* obj, bool tlCtrl, bool tlAlt, bool tlShift, bool tlCaps, u16 tnAsciiChar, u16 tvKey, bool tlIsCAS, bool tlIsAscii)
	{
		//////////
		// Prepare for dispatch
		//////
			iVariable_set_logical	(obj->ev.varCtrl_onKeyDown,			((tlCtrl)		? _LOGICAL_TRUE : _LOGICAL_FALSE));
			iVariable_set_logical	(obj->ev.varAlt_onKeyDown,			((tlAlt)		? _LOGICAL_TRUE : _LOGICAL_FALSE));
			iVariable_set_logical	(obj->ev.varShift_onKeyDown,			((tlShift)		? _LOGICAL_TRUE : _LOGICAL_FALSE));
			iVariable_set_logical	(obj->ev.varCaps_onKeyDown,			((tlCaps)		? _LOGICAL_TRUE : _LOGICAL_FALSE));
			iVariable_set_u16		(obj->ev.varAsciiChar_onKeyDown,		tnAsciiChar);
			iVariable_set_s16		(obj->ev.varVKey_onKeyDown,			tvKey);
			iVariable_set_logical	(obj->ev.varIsCAS_onKeyDown,			((tlIsCAS)		? _LOGICAL_TRUE : _LOGICAL_FALSE));
			iVariable_set_logical	(obj->ev.varIsAscii_onKeyDown,		((tlIsAscii)	? _LOGICAL_TRUE : _LOGICAL_FALSE));


		//////////
		// Dispatch
		//////
			return(iEngine_raise_event(_EVENT_ONKEYDOWN, win, obj));
	}




//////////
//
// Called with strongly typed variables to dispatch the same event using weakly typed
// SVariable variables, so as to align with conventional source code processing.
//
//////
	bool iiEventDispatch_onKeyUp(SWindow* win, SObject* obj, bool tlCtrl, bool tlAlt, bool tlShift, bool tlCaps, u16 tnAsciiChar, u16 tvKey, bool tlIsCAS, bool tlIsAscii)
	{
		//////////
		// Prepare for dispatch
		//////
			iVariable_set_logical	(obj->ev.varCtrl_onKeyUp,			((tlCtrl)		? _LOGICAL_TRUE : _LOGICAL_FALSE));
			iVariable_set_logical	(obj->ev.varAlt_onKeyUp,			((tlAlt)		? _LOGICAL_TRUE : _LOGICAL_FALSE));
			iVariable_set_logical	(obj->ev.varShift_onKeyUp,		((tlShift)		? _LOGICAL_TRUE : _LOGICAL_FALSE));
			iVariable_set_logical	(obj->ev.varCaps_onKeyUp,			((tlCaps)		? _LOGICAL_TRUE : _LOGICAL_FALSE));
			iVariable_set_u16		(obj->ev.varAsciiChar_onKeyUp,	tnAsciiChar);
			iVariable_set_s16		(obj->ev.varVKey_onKeyUp,			tvKey);
			iVariable_set_logical	(obj->ev.varIsCAS_onKeyUp,		((tlIsCAS)		? _LOGICAL_TRUE : _LOGICAL_FALSE));
			iVariable_set_logical	(obj->ev.varIsAscii_onKeyUp,		((tlIsAscii)	? _LOGICAL_TRUE : _LOGICAL_FALSE));


		//////////
		// Dispatch
		//////
			return(iEngine_raise_event(_EVENT_ONKEYUP, win, obj));
	}




//////////
//
// Called when the user mouse-wheels on a carousel somewhere outside of the client area
//
//////
	bool iEvents_carouselMouseWheel(SWindow* win, SObject* obj, s32 lnX, s32 lnY, bool llCtrl, bool llAlt, bool llShift, u32 lnClick)
	{
		u32						lnTarget;
		bool					llFocusChanged, llResult;
		SObjCarouselTabData*	octd;


		// Make sure our environment is sane
		llResult = true;
		if (obj)
		{
			// Find the associated carousel sub-object
			lnTarget = iiEvents_carousel_findTarget(win, obj, lnX, lnY, &octd, &llFocusChanged);
			switch (lnTarget)
			{
				case _EVENT_CAROUSEL_TAB:
				case _EVENT_CAROUSEL_TAB_CLOSE:
				case _EVENT_CAROUSEL_TAB_RECTANGLE:
					// It's a tab event
					iEngine_raise_event(_EVENT_CAROUSEL_ONTABMOUSEWHEEL, win, obj, (void*)lnClick);
					llResult = false;	// Do not propagate further
			}
		}

		// If something changed, we need to re-render
		if (llFocusChanged)
		{
			iObj_setDirtyRender_ascent(obj, true);
			iWindow_render(iWindow_findRoot_byObj(obj), false);
		}

		// Signal if the message should continue propagating
		return(llResult);
	}




//////////
//
// Called when the user moves the mouse on a carousel somewhere outside of the client area
//
//////
	bool iEvents_carouselMouseMove(SWindow* win, SObject* obj, s32 lnX, s32 lnY, bool llCtrl, bool llAlt, bool llShift, u32 lnClick)
	{
		u32						lnTarget;
		bool					llFocusChanged, llResult;
		SObjCarouselTabData*	octd;


		// Make sure our environment is sane
		llResult = true;
		if (obj)
		{
			// Find the associated carousel sub-object
			lnTarget = iiEvents_carousel_findTarget(win, obj, lnX, lnY, &octd, &llFocusChanged);
			switch (lnTarget)
			{
				case _EVENT_CAROUSEL_TAB:
					// Moving on the tab
					iEngine_raise_event(_EVENT_CAROUSEL_ONTABMOUSEMOVE, win, obj, (void*)false);
					llResult = false;
					break;

				case _EVENT_CAROUSEL_TAB_CLOSE:
					// Moving over the close button, but still on the tab
					iEngine_raise_event(_EVENT_CAROUSEL_ONTABMOUSEMOVE, win, obj, (void*)true);
					llResult = false;
					break;
			}
		}

		// If something changed, we need to re-render
		if (llFocusChanged)
		{
			iObj_setDirtyRender_ascent(obj, true);
			iWindow_render(iWindow_findRoot_byObj(obj), false);
		}

		// Signal if the message should continue propagating
		return(llResult);
	}




//////////
//
// Called when the user mouse downs (presses down a mouse button) on a carousel somewhere outside of the client area
//
//////
	bool iEvents_carouselMouseDown(SWindow* win, SObject* obj, s32 lnX, s32 lnY, bool llCtrl, bool llAlt, bool llShift, u32 lnClick)
	{
		u32						lnTarget;
		bool					llFocusChanged, llResult;
		SObjCarouselTabData*	octd;


		// Make sure our environment is sane
		llResult = true;
		if (obj)
		{
			// Find the associated carousel sub-object
			lnTarget = iiEvents_carousel_findTarget(win, obj, lnX, lnY, &octd, &llFocusChanged);
			switch (lnTarget)
			{
				case _EVENT_CAROUSEL_TAB:
					// Clicking on a tab
					iEngine_raise_event(_EVENT_CAROUSEL_ONTABMOUSEDOWN, win, obj, (void*)false);
					iEngine_raise_event(_EVENT_CAROUSEL_ONTABCLICK, win, obj, NULL);
					llResult = false;
					break;

				case _EVENT_CAROUSEL_TAB_CLOSE:
					// Clicking close on a tab
					iEngine_raise_event(_EVENT_CAROUSEL_ONTABCLOSE, win, obj, (void*)true);
					llResult = false;
					break;
			}
		}

		// If something changed, we need to re-render
		if (llFocusChanged)
		{
			iObj_setDirtyRender_ascent(obj, true);
			iWindow_render(iWindow_findRoot_byObj(obj), false);
		}

		// Signal if the message should continue propagating
		return(llResult);
	}




//////////
//
// Called when the user mouse ups (releases the mouse button) on a carousel somewhere outside of the client area
//
//////
	bool iEvents_carouselMouseUp(SWindow* win, SObject* obj, s32 lnX, s32 lnY, bool llCtrl, bool llAlt, bool llShift, u32 lnClick)
	{
		u32						lnTarget;
		bool					llFocusChanged, llResult;
		SObjCarouselTabData*	octd;


		// Make sure our environment is sane
		llResult = true;
		if (obj)
		{
			// Find the associated carousel sub-object
			lnTarget = iiEvents_carousel_findTarget(win, obj, lnX, lnY, &octd, &llFocusChanged);
			switch (lnTarget)
			{
				case _EVENT_CAROUSEL_TAB:
					// Releasing the mouse on a tab
					iEngine_raise_event(_EVENT_CAROUSEL_ONTABMOUSEUP, win, obj, (void*)false);
					llResult = false;
					break;
			}
		}

		// If something changed, we need to re-render
		if (llFocusChanged)
		{
			iObj_setDirtyRender_ascent(obj, true);
			iWindow_render(iWindow_findRoot_byObj(obj), false);
		}

		// Signal if the message should continue propagating
		return(llResult);
	}




//////////
//
// Called when a user begins dragging on a carousel tab.
//
//////
	bool iEvents_carousel_dragStart_tab(SWindow* win, SObject* obj, SBitmap* bmp)
	{
		return(true);
	}




//////////
//
// Called when a user begins dragging on a carousel titlebar.
//
//////
	bool iEvents_carousel_dragStart_titlebar(SWindow* win, SObject* obj, SBitmap* bmp)
	{
		return(true);
	}




//////////
//
// Called to find out what the target is for the indicated coordinate within the carousel (header, or a tab)
//
//////
	u32 iiEvents_carousel_findTarget(SWindow* win, SObject* obj, s32 tnX, s32 tnY, SObjCarouselTabData** toctd, bool* tlHighlightChanged)
	{
		s32						lnResult, lnAlignment;
		u32						lnI;
		RECT					lrc;
		POINT					pt;
		SObjCarouselTabData*	octd;


		//////////
		// Create a point at the actual coordinates
		/////
			pt.x = tnX - obj->rcExtra.left;		// Back off for the tab location's X coordinate
			pt.y = tnY - obj->rcExtra.top;		// Back off for the tab location's Y coordinate


		//////////
		// Adjust for alignment
		//////
			lnAlignment = propAlignment(obj);
			switch (lnAlignment)
			{
				case _ALIGNMENT_LEFT:
					pt.y = obj->rcClient.bottom - pt.y;
					break;
			}


		//////////
		// Is it on a tab?
		//////
			*tlHighlightChanged = false;
			if (obj->p.rcTabs && obj->p.rcTabs->buffer)
			{
				// Iterate through all the tabs to update the isMouseOver* flags
				for (lnResult = -1, lnI = 0, octd = (SObjCarouselTabData*)obj->p.rcTabs->buffer; lnI < obj->p.rcTabs->populatedLength; lnI += sizeof(SObjCarouselTabData), octd++)
				{

					//////////
					// Is it on the close button?
					//////
						SetRect(&lrc, octd->rcClose.left + obj->p.bmpTabsScrolled, octd->rcClose.top, octd->rcClose.right + obj->p.bmpTabsScrolled, octd->rcClose.bottom);
						if (PtInRect(&lrc, pt))
						{
							// Yes
							*toctd					= octd;
							lnResult				= _EVENT_CAROUSEL_TAB_CLOSE;

							if (!octd->isMouseOverClose || octd->isMouseOver)
							{
								*tlHighlightChanged	= true;

								// Are we entering the tab?
								if (!octd->isMouseOverClose && !octd->isMouseOver)
									iEngine_raise_event(_EVENT_CAROUSEL_ONTABMOUSEENTER, win, obj, (void*)true);
							}

							octd->isMouseOverClose	= true;
							octd->isMouseOver		= false;

						} else {
							// Nope
							if (octd->isMouseOverClose)
							{
								*tlHighlightChanged	= true;
								iEngine_raise_event(_EVENT_CAROUSEL_ONTABMOUSELEAVE, win, obj, (void*)true);
							}

							octd->isMouseOverClose	= false;

							//////////
							// Is it on this tab at all?
							//////
								SetRect(&lrc, octd->rc.left + obj->p.bmpTabsScrolled, octd->rc.top, octd->rc.right + obj->p.bmpTabsScrolled, octd->rc.bottom);
								if (PtInRect(&lrc, pt))
								{
									// Yes
									*toctd				= octd;
									lnResult			= _EVENT_CAROUSEL_TAB;

									if (!octd->isMouseOver)
									{
										*tlHighlightChanged	= true;

										// Entering the tab
										iEngine_raise_event(_EVENT_CAROUSEL_ONTABMOUSEENTER, win, obj, (void*)false);
									}

									octd->isMouseOver	= true;

								} else {
									// Nope
									if (octd->isMouseOver)
									{
										*tlHighlightChanged	= true;

										// Leaving the tab
										iEngine_raise_event(_EVENT_CAROUSEL_ONTABMOUSELEAVE, win, obj, (void*)false);
									}

									octd->isMouseOver	= false;
								}
						}

				}

				// When we get here, lnResult is >= 0 if we encountered something
				if (lnResult >= 0)
					return(lnResult);
			}


		//////////
		// If we get here, it's away from the header or a tab
		//////
			return(_EVENT_CAROUSEL_AWAY);

	}
