//////////
//
// /libsf/source/vjr/source/objects/callbacks.cpp
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
//     Jun.15.2014
//////
// Change log:
//     Jun.15.2014 - Initial creation
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
// Default callbacks are found below.
//
//////
//
// Note:  The return value indicates if this event should continue to be propagated to other objects.
// Note:  If the event is consumed here, the return value should be false.
//
//////
	bool iDefaultCallback_resize(SThisCode* thisCode, SWindow* win, SObject* obj, RECT* rc)
	{
		// Assume the resize was okay
		if (obj && rc)
		{
			// Resize
			iObj_setSize(thisCode, obj, rc->left, rc->top, rc->right - rc->left, rc->bottom - rc->top);

			// Indicate success
			return(false);
		}

		// If we get here, error, continue propagating
		return(true);
	}

	bool iDefaultCallback_onLoad(SThisCode* thisCode, SWindow* win, SObject* obj)
	{
		// Do not continue to propagate this message to other objects
		return(false);
	}

	bool iDefaultCallback_onInit(SThisCode* thisCode, SWindow* win, SObject* obj)
	{
		// Do not continue to propagate this message to other objects
		return(false);
	}

	bool iDefaultCallback_onCreated(SThisCode* thisCode, SWindow* win, SObject* obj)
	{
		// Do not continue to propagate this message to other objects
		return(false);
	}

	bool iDefaultCallback_onResize(SThisCode* thisCode, SWindow* win, SObject* obj, SVariable* widthRequired_out, SVariable* heightRequired_out)
	{
		// Do not continue to propagate this message to other objects
		return(false);
	}

	bool iDefaultCallback_onRender(SThisCode* thisCode, SWindow* win, SObject* obj)
	{

//////////
// Debug trap:  Rendered objects signal this event by default ... to find when a particular object is being rendered, trap here
//////
// 	if (obj->objType == _OBJ_TYPE_CAROUSEL)
// 		debug_break;
// 	if (obj->objType == _OBJ_TYPE_RIDER)
// 		debug_break;


		// Do not continue to propagate this message to other objects
		return(false);
	}

	bool iDefaultCallback_onPublish(SThisCode* thisCode, SWindow* win, SObject* obj)
	{
		// Do not continue to propagate this message to other objects
		return(false);
	}

	bool iDefaultCallback_onDestroy(SThisCode* thisCode, SWindow* win, SObject* obj)
	{
		// Do not continue to propagate this message to other objects
		return(false);
	}

	bool iDefaultCallback_onUnload(SThisCode* thisCode, SWindow* win, SObject* obj)
	{
		// Do not continue to propagate this message to other objects
		return(false);
	}

	bool iDefaultCallback_onGotFocus(SThisCode* thisCode, SWindow* win, SObject* obj)
	{
		// Do not continue to propagate this message to other objects
		return(false);
	}

	bool iDefaultCallback_onLostFocus(SThisCode* thisCode, SWindow* win, SObject* obj)
	{
		// Do not continue to propagate this message to other objects
		return(false);
	}

	bool iiDefaultCallback_processMouseVariables(	SThisCode* thisCode, 
													SVariable* varX, SVariable* varY, SVariable* varCtrl, SVariable* varAlt, SVariable* varShift, SVariable* varClick,
													s32* lnX, s32* lnY, bool* tlCtrl, bool* tlAlt, bool* tlShift, u32* lnClick)
	{
		//////////
		// Validate the variables are appropriate
		//////
			if (!iVariable_isValid(varX) || !iVariable_isValid(varY) || !iVariable_isValid(varCtrl) || !iVariable_isValid(varAlt) || !iVariable_isValid(varShift) || !iVariable_isValid(varClick))
			{
				// Something is invalid, ignore it
				return(false);
			}
			if (!iVariable_isTypeNumeric(varX) || !iVariable_isTypeNumeric(varY) || !iVariable_isTypeLogical(varCtrl) || !iVariable_isTypeLogical(varAlt) || !iVariable_isTypeLogical(varShift) || !iVariable_isTypeNumeric(varClick))
			{
				// Something is not a proper variable, ignore it
				return(false);
			}
			*lnX		= (s16)iiVariable_getAs_s32(thisCode,	varX,		false, NULL, NULL);
			*lnY		= (u16)iiVariable_getAs_s32(thisCode,	varY,		false, NULL, NULL);
			*tlCtrl		= iiVariable_getAs_bool(thisCode,		varCtrl,	false, NULL, NULL);
			*tlAlt		= iiVariable_getAs_bool(thisCode,		varAlt,		false, NULL, NULL);
			*tlShift	= iiVariable_getAs_bool(thisCode,		varShift,	false, NULL, NULL);
			*lnClick	= iiVariable_getAs_u32(thisCode,		varClick,	false, NULL, NULL);


		//////////
		// Indicate we successfully parsed the variables
		//////
			return(true);
	}

	bool iDefaultCallback_onMouseClickEx(SThisCode* thisCode, SWindow* win, SObject* obj, SVariable* varX, SVariable* varY, SVariable* varCtrl, SVariable* varAlt, SVariable* varShift, SVariable* varClick)
	{
		s32		lnX, lnY;
		u32		lnClick;
		bool	llCtrl, llAlt, llShift;


		// Make sure our environment is sane
		if (!iiDefaultCallback_processMouseVariables(thisCode, varX, varY, varCtrl, varAlt, varShift, varClick, &lnX, &lnY, &llCtrl, &llAlt, &llShift, &lnClick))
			return(false);


		// Do not continue to propagate this message to other objects
		return(false);
	}

	bool iDefaultCallback_onMouseDblClickEx(SThisCode* thisCode, SWindow* win, SObject* obj, SVariable* varX, SVariable* varY, SVariable* varCtrl, SVariable* varAlt, SVariable* varShift, SVariable* varClick)
	{
		s32		lnX, lnY;
		u32		lnClick;
		bool	llCtrl, llAlt, llShift;


		// Make sure our environment is sane
		if (!iiDefaultCallback_processMouseVariables(thisCode, varX, varY, varCtrl, varAlt, varShift, varClick, &lnX, &lnY, &llCtrl, &llAlt, &llShift, &lnClick))
			return(false);


		// Do not continue to propagate this message to other objects
		return(false);
	}

	bool iDefaultCallback_onMouseWheel(SThisCode* thisCode, SWindow* win, SObject* obj, SVariable* varX, SVariable* varY, SVariable* varCtrl, SVariable* varAlt, SVariable* varShift, SVariable* varClick, SVariable* varUnits)
	{
		s32		lnX, lnY, lnUnits;
		u32		lnClick;
		bool	llCtrl, llAlt, llShift;
		POINT	pt;


		// Make sure our environment is sane
		if (!iiDefaultCallback_processMouseVariables(thisCode, varX, varY, varCtrl, varAlt, varShift, varClick, &lnX, &lnY, &llCtrl, &llAlt, &llShift, &lnClick) || !iVariable_isValid(varUnits) || !iVariable_isTypeNumeric(varUnits))
			return(false);	// Do not continue consuming

		// Grab the units
		lnUnits = iiVariable_getAs_s32(thisCode, varUnits, false, NULL, NULL);


		// Assume we consumed the mouse wheel, and that the parent doesn't need to receive it
		if (obj->objType == _OBJ_TYPE_EDITBOX)
		{
			// Ctrl+MouseWheel is a normal navigate
			if (llCtrl)
			{
				// They are just moving the cursor line
				iSEM_navigate(thisCode, obj->p.sem, obj, lnUnits * ((llShift) ? -1 : -3), 0);

			// MouseWheel is a scroll
			} else {
				// They want to scroll the entire window, including the cursor line
				iSEM_scroll(thisCode, obj->p.sem, obj, lnUnits * ((llShift) ? -1 : -3), 0);
			}
			iObj_setDirtyRender_ascent(thisCode, obj, true);
			iWindow_render(thisCode, win, false);

		} else if (obj->objType == _OBJ_TYPE_CAROUSEL) {
			// Create a point
			pt.x = lnX;
			pt.y = lnY;

			// They are they outside of the client area?
			if (!PtInRect(&obj->rcClient, pt))
				return(iEvents_carouselMouseWheel(thisCode, win, obj, lnX, lnY, llCtrl, llAlt, llShift, lnClick));
		}

		// Do not continue to propagate this message to other objects
		return(false);
	}

	bool iDefaultCallback_onMouseMove(SThisCode* thisCode, SWindow* win, SObject* obj, SVariable* varX, SVariable* varY, SVariable* varCtrl, SVariable* varAlt, SVariable* varShift, SVariable* varClick)
	{
		f64			lfPercent, lfX, lfY, lfWidth, lfHeight;
		s32			lnX, lnY;
		u32			lnClick;
		bool		llCtrl, llAlt, llShift;
		SVariable*	valueMin;


		// Make sure our environment is sane
		if (!iiDefaultCallback_processMouseVariables(thisCode, varX, varY, varCtrl, varAlt, varShift, varClick, &lnX, &lnY, &llCtrl, &llAlt, &llShift, &lnClick))
			return(false);	// Do not continue consuming


		// If we're clicking on a radio button, adjust the dial
		if (lnClick != 0 && obj->objType == _OBJ_TYPE_RADIO)
		{
			// The mouse indicates the position
			// Determine theta
			lfWidth		= (f64)(obj->rc.right  - obj->rc.left);
			lfHeight	= (f64)(obj->rc.bottom - obj->rc.top);
			lfX			= (f64)lnX - (lfWidth / 2.0);
			lfY			= (lfHeight - (f64)lnY) - (lfHeight / 2.0);

			lfPercent	= atan2(lfY, lfX) / (M_PI * 2.0);
			if (lfPercent < 0.0)
				lfPercent += 1.0;

			valueMin = iObjProp_get_variable_byIndex(thisCode, obj, _INDEX_VALUE_MINIMUM);
			iObjProp_set_f64_direct(thisCode, obj, _INDEX_VALUE, get_f64(valueMin) + (lfPercent * (iObjProp_get_f64_direct(thisCode, obj, _INDEX_VALUE_MAXIMUM) - get_f64(valueMin))));
			iObj_setDirtyRender_ascent(thisCode, obj, true);
			iWindow_render(thisCode, win, false);

		} else if (obj->objType == _OBJ_TYPE_EDITBOX) {
			if ((lnClick & _MOUSE_LEFT_BUTTON) != 0)
			{
				// They are clicking and dragging

				// Need to navigate to the indicated x,y coordinate
				iSEM_navigateTo_pixelXY(thisCode, obj->p.sem, obj, lnX, lnY);

				// Mark the mouse activity
				iSEM_selectStart(thisCode, obj->p.sem, _SEM_SELECT_MODE_ANCHOR);

				// Redraw our changes
				iObj_setDirtyRender_ascent(thisCode, obj, true);
				iWindow_render(thisCode, win, false);
			}

		} else if (obj->objType == _OBJ_TYPE_CAROUSEL) {
			// We always track mouse movements to hightlight and un-hightlight tabs
			return(iEvents_carouselMouseMove(thisCode, win, obj, lnX, lnY, llCtrl, llAlt, llShift, lnClick));
		}

		// Mouse moves continue to propagate all the way through, so as to signal appropriate enter and leave events
		return(true);
	}

	bool iDefaultCallback_onMouseDown(SThisCode* thisCode, SWindow* win, SObject* obj, SVariable* varX, SVariable* varY, SVariable* varCtrl, SVariable* varAlt, SVariable* varShift, SVariable* varClick)
	{
		bool		llMouseDown;
		f64			lfPercent, lfX, lfY, lfWidth, lfHeight, lfValue;
		s32			lnX, lnY;
		u32			lnClick;
		bool		llCtrl, llAlt, llShift;
		POINT		pt;
		SVariable*	valueMin;
		SObject*	objRoot;


		// Make sure our environment is sane
		if (!iiDefaultCallback_processMouseVariables(thisCode, varX, varY, varCtrl, varAlt, varShift, varClick, &lnX, &lnY, &llCtrl, &llAlt, &llShift, &lnClick))
			return(false);	// Do not continue consuming


		// Set the flag
		llMouseDown = true;

		// If focus isn't already set on this control, set focus on this control
		if (!obj->p.hasFocus)
		{
			objRoot = iObj_find_rootmostObject(thisCode, obj);
			if (objRoot)
				iObj_clearFocus(thisCode, win, objRoot, true, true);

			iObj_setFocus(thisCode, win, obj, true);
			iObj_setDirtyRender_ascent(thisCode, objRoot, true);
		}

		// For forms, they can be clicking down on special things for various operations
		if (obj->parent && obj->parent->objType == _OBJ_TYPE_FORM && win->obj == obj->parent)
		{
			// Left button only?
			if (win->mouseCurrent.buttonLeft && !win->mouseCurrent.buttonMiddle && !win->mouseCurrent.buttonRight)
			{
				// We're on the top-level form for the window
				if (propIsName_byText(obj, cgcName_iconMove) || propIsName_byText(obj, cgcName_caption))
				{
					// We're on the _move icon or the caption, which means they want to move the window
					win->isMoving = true;
					memcpy(&win->rcMoveResizeStart,		&win->rc,			sizeof(win->rcMoveResizeStart));
					memcpy(&win->mouseMoveResizeStart,	&win->mouseCurrent,	sizeof(win->mouseMoveResizeStart));

//				} else if (iDatum_compare(&varName->value, cgcName_iconScaleUl, sizeof(cgcName_iconScaleUl) - 1) == 0) {
//					// We're on the upper-left scaling arrow
//				} else if (iDatum_compare(&varName->value, cgcName_iconScaleUr, sizeof(cgcName_iconScaleUr) - 1) == 0) {
//					// We're on the upper-right scaling arrow
//				} else if (iDatum_compare(&varName->value, cgcName_iconScaleLr, sizeof(cgcName_iconScaleLr) - 1) == 0) {
//					// We're on the lower-right scaling arrow
//				} else if (iDatum_compare(&varName->value, cgcName_iconScaleLl, sizeof(cgcName_iconScaleLl) - 1) == 0) {
//					// We're on the lower-left scaling arrow
				}
			}
		}

		if (obj->parent && obj->parent->objType == _OBJ_TYPE_CHECKBOX)
		{
			// For checkboxes, we toggle
			// They're clicking on a checkbox, toggle the value and re-render
			iObjProp_set_s32_direct(thisCode, obj, _INDEX_VALUE, ((iObjProp_get_s32_direct(thisCode, obj, _INDEX_VALUE) != 0) ? 0 : 1));

			// Calling the size with its current size forces the refresh
			iObj_setSize(thisCode, obj->parent,
									obj->parent->rc.left,
									obj->parent->rc.top,
									obj->parent->rc.right  - obj->parent->rc.left,
									obj->parent->rc.bottom - obj->parent->rc.top);

		} else if (obj->objType == _OBJ_TYPE_EDITBOX) {
			// Need to navigate to the indicated x,y coordinate
			iSEM_navigateTo_pixelXY(thisCode, obj->p.sem, obj, lnX, lnY);

			// Mark the mouse activity
			if (!llShift)		iSEM_selectStop(thisCode, obj->p.sem);
			else				iSEM_selectStart(thisCode, obj->p.sem, _SEM_SELECT_MODE_ANCHOR);

		} else if (obj->objType == _OBJ_TYPE_RADIO) {
			// The mouse indicates the position
			// Determine theta
			lfWidth		= (f64)(obj->rc.right  - obj->rc.left);
			lfHeight	= (f64)(obj->rc.bottom - obj->rc.top);
			lfX			= (f64)lnX - (lfWidth / 2.0);
			lfY			= (lfHeight - (f64)lnY) - (lfHeight / 2.0);
			lfPercent	= atan2(lfY, lfX) / (M_PI * 2.0);
			if (lfPercent < 0.0)
				lfPercent += 1.0;

			valueMin	= iObjProp_get_variable_byIndex(thisCode, obj, _INDEX_VALUE_MINIMUM);
			lfValue		= get_f64(valueMin) + (lfPercent * (iObjProp_get_f64_direct(thisCode, obj, _INDEX_VALUE_MAXIMUM) - get_f64(valueMin)));
			iObjProp_set_f64_direct(thisCode, obj, _INDEX_VALUE, lfValue);

		} else if (obj->objType == _OBJ_TYPE_CAROUSEL) {
			// Create a point
			pt.x = lnX;
			pt.y = lnY;

			// They are they outside of the client area?
			if (!PtInRect(&obj->rcClient, pt))
				return(iEvents_carouselMouseDown(thisCode, win, obj, lnX, lnY, llCtrl, llAlt, llShift, lnClick));

		} else {
			// Assume we consumed the mouse down event, and that the parent doesn't need to receive it
			switch (obj->objType)
			{
				case _OBJ_TYPE_IMAGE:
					if (propIsName_byText(obj, cgcName_iconClose)) {
						// Close
						iVjr_shutdown(thisCode);	// They clicked quit
						return(false);				// When we get here, the object no longer exists

					} else if (propIsName_byText(obj, cgcName_iconMove)) {
						// Move
						llMouseDown			= false;
						obj->ev.isMouseOver	= false;
						iWindow_move(win);

					} else if (propIsName_byText(obj, cgcName_iconMinimize)) {
						// Minimize
						llMouseDown			= false;
						obj->ev.isMouseOver	= false;
						iWindow_minimize(win);

					} else if (propIsName_byText(obj, cgcName_iconMaximize)) {
						// Maximize
						llMouseDown			= false;
						obj->ev.isMouseOver	= false;
						iWindow_maximize(win);
					}
					break;
			}
		}

		// Update our condition
		obj->ev.isMouseDown = llMouseDown;
		iObj_setDirtyRender_ascent(thisCode, obj, true);
		iWindow_render(thisCode, win, false);

		// Do not continue to propagate this message to other objects
		return(false);
	}

	bool iDefaultCallback_onMouseUp(SThisCode* thisCode, SWindow* win, SObject* obj, SVariable* varX, SVariable* varY, SVariable* varCtrl, SVariable* varAlt, SVariable* varShift, SVariable* varClick)
	{
		s32		lnX, lnY;
		u32		lnClick;
		bool	llCtrl, llAlt, llShift;
		POINT	pt;


		// Make sure our environment is sane
		if (!iiDefaultCallback_processMouseVariables(thisCode, varX, varY, varCtrl, varAlt, varShift, varClick, &lnX, &lnY, &llCtrl, &llAlt, &llShift, &lnClick))
			return(false);	// Do not continue consuming


		if (obj->objType == _OBJ_TYPE_CAROUSEL)
		{
			// Create a point
			pt.x = lnX;
			pt.y = lnY;

			// They are they outside of the client area?
			if (!PtInRect(&obj->rcClient, pt))
				return(iEvents_carouselMouseUp(thisCode, win, obj, lnX, lnY, llCtrl, llAlt, llShift, lnClick));
		}

		// We are leaving this object, lower the flag
		obj->ev.isMouseDown = (obj->ev.thisClick != 0);	// Indicate if the mouse is down here
		obj->ev.isMouseDown = false;
		iObj_setDirtyRender_ascent(thisCode, obj, true);
		iWindow_render(thisCode, win, false);

		// Do not continue to propagate this message to other objects
		return(false);
	}

	bool iDefaultCallback_onMouseEnter(SThisCode* thisCode, SWindow* win, SObject* obj)
	{
		// We are newly over this object, raise the flag
		obj->ev.isMouseDown = (obj->ev.thisClick != 0);	// Indicate if the mouse is down here
		if (!obj->ev.isMouseOver)
		{
			obj->ev.isMouseOver = true;
			iObj_setDirtyRender_ascent(thisCode, obj, true);
			iWindow_render(thisCode, win, false);
		}

		// Do not continue to propagate this message to other objects
		return(false);
	}

	bool iDefaultCallback_onMouseLeave(SThisCode* thisCode, SWindow* win, SObject* obj)
	{
		// Assume we consumed the leave, and that the parent doesn't need to receive it
		if (obj->ev.isMouseOver)
		{
			obj->ev.isMouseOver = false;
			iObj_setDirtyRender_ascent(thisCode, obj, true);
			iWindow_render(thisCode, win, false);
		}

		// Do not continue to propagate this message to other objects
		return(false);
	}

	bool iDefaultCallback_onMouseHover(SThisCode* thisCode, SWindow* win, SObject* obj, SVariable* varX, SVariable* varY, SVariable* varCtrl, SVariable* varAlt, SVariable* varShift, SVariable* varClick)
	{
		s32		lnX, lnY;
		u32		lnClick;
		bool	llCtrl, llAlt, llShift;


		// Make sure our environment is sane
		if (!iiDefaultCallback_processMouseVariables(thisCode, varX, varY, varCtrl, varAlt, varShift, varClick, &lnX, &lnY, &llCtrl, &llAlt, &llShift, &lnClick))
			return(false);	// Do not continue consuming

		// Do not continue to propagate this message to other objects
		return(false);
	}

	bool iiDefaultCallback_processKeyVariables(	SThisCode* thisCode, 
												SVariable* varCtrl, SVariable* varAlt, SVariable* varShift, SVariable* varCaps, SVariable* varAscii, SVariable* varVKey, SVariable* varIsCAS, SVariable* varIsAscii,
												bool* tlCtrl, bool* tlAlt, bool* tlShift, bool* tlCaps, bool* tlIsCAS, bool* tlIsAscii,
												s16* lcAscii, u16* lnVKey)
	{
		//////////
		// Validate the variables are appropriate
		//////
			if (!iVariable_isValid(varCtrl) || !iVariable_isValid(varAlt) || !iVariable_isValid(varShift) || !iVariable_isValid(varCaps) || !iVariable_isValid(varIsAscii) || !iVariable_isValid(varAscii)	|| !iVariable_isValid(varVKey))
			{
				// Something is invalid
				return(false);	// Do not continue consuming
			}
			if (!iVariable_isTypeLogical(varCtrl) || !iVariable_isTypeLogical(varAlt) || !iVariable_isTypeLogical(varShift) || !iVariable_isTypeLogical(varCaps) || !iVariable_isTypeLogical(varIsAscii) || !iVariable_isTypeNumeric(varAscii)	|| !iVariable_isTypeNumeric(varVKey))
			{
				// Something is not a proper variable
				return(false);	// Do not continue consuming
			}
			*tlCtrl		= iiVariable_getAs_bool(thisCode, varCtrl,		false, NULL, NULL);
			*tlAlt		= iiVariable_getAs_bool(thisCode, varAlt,		false, NULL, NULL);
			*tlShift	= iiVariable_getAs_bool(thisCode, varShift,		false, NULL, NULL);
			*tlCaps		= iiVariable_getAs_bool(thisCode, varCaps,		false, NULL, NULL);
			*tlIsCAS	= iiVariable_getAs_bool(thisCode, varIsCAS,		false, NULL, NULL);
			*tlIsAscii	= iiVariable_getAs_bool(thisCode, varIsAscii,	false, NULL, NULL);
			*lcAscii	= iiVariable_getAs_s16(thisCode, varAscii,		false, NULL, NULL);
			*lnVKey		= iiVariable_getAs_u16(thisCode, varVKey,		false, NULL, NULL);


		//////////
		// Indicate we successfully parsed the keyboard variables
		//////
			return(true);
	}

	bool iDefaultCallback_onKeyDown(SThisCode* thisCode, SWindow* win, SObject* obj, SVariable* varCtrl, SVariable* varAlt, SVariable* varShift, SVariable* varCaps, SVariable* varAscii, SVariable* varVKey, SVariable* varIsCAS, SVariable* varIsAscii)
	{
		bool		llRender;
		SObject*	objCheckbox;
		SObject*	objRender2;
		bool		llCtrl, llAlt, llShift, llCaps, llIsCAS, llIsAscii;
		s16			lcAscii;
		u16			lnVKey;


		// Make sure our environment is sane
		if (!iiDefaultCallback_processKeyVariables(thisCode, varCtrl, varAlt, varShift, varCaps, varAscii, varVKey, varIsCAS, varIsAscii, &llCtrl, &llAlt, &llShift, &llCaps, &llIsCAS, &llIsAscii, &lcAscii, &lnVKey))
			return(false);	// Do not continue consuming


		//////////
		// See if we're on a checkbox
		//////
			llRender	= false;
			objCheckbox	= NULL;
			if (obj->objType == _OBJ_TYPE_CHECKBOX)
			{
				// The object itself is a checkbox
				objCheckbox = obj;
				objRender2	= obj;

			} else if (obj->parent && obj->parent->objType == _OBJ_TYPE_CHECKBOX) {
				// The parent is a checkbox
				objCheckbox = obj->parent;
				objRender2	= obj;
			}

			if (objCheckbox)
			{
				if (lnVKey == VK_SPACE || lnVKey == VK_RETURN)
				{
					// Toggle the value and redraw
					llRender = true;
					iObjProp_set_s32_direct(thisCode, objCheckbox, _INDEX_VALUE, ((iObjProp_get_s32_direct(thisCode, objCheckbox, _INDEX_VALUE) == 0) ? 1 : 0));
					iObj_setDirtyRender_ascent(thisCode, objCheckbox, false);
					if (objRender2 != objCheckbox)
						iObj_setDirtyRender_ascent(thisCode, objRender2, false);


				} else if (llShift && lnVKey == VK_TAB) {
					// Move to previous object
					llRender = iObj_setFocusObjectPrev(thisCode, win, objCheckbox);


				} else if (lnVKey == VK_TAB) {
					// Move to next object
					llRender = iObj_setFocusObjectNext(thisCode, win, objCheckbox);


				} else if (llIsAscii) {
					if ((u8)lcAscii == 't' || (u8)lcAscii == 'T' || (u8)lcAscii == 'y' || (u8)lcAscii == 'Y' || (u8)lcAscii == '1')
					{
						// Set it to on
						llRender = true;
						iObjProp_set_s32_direct(thisCode, obj, _INDEX_VALUE, 1);
						iObj_setDirtyRender_ascent(thisCode, objCheckbox, false);
						if (objRender2 != objCheckbox)
							iObj_setDirtyRender_ascent(thisCode, objRender2, false);

					} else if ((u8)lcAscii == 'f' || (u8)lcAscii == 'F' || (u8)lcAscii == 'n' || (u8)lcAscii == 'N' || (u8)lcAscii == '0') {
						// Set it to off
						llRender = true;
						iObjProp_set_s32_direct(thisCode, obj, _INDEX_VALUE, 0);
						iObj_setDirtyRender_ascent(thisCode, objCheckbox, false);
						if (objRender2 != objCheckbox)
							iObj_setDirtyRender_ascent(thisCode, objRender2, false);
					}
				}

			} else {
				// Not a checkbox
				if (llShift && lnVKey == VK_TAB)
				{
					// Move to previous object
					llRender = iObj_setFocusObjectPrev(thisCode, win, obj);

				} else if (lnVKey == VK_TAB) {
					// Move to next object
					llRender = iObj_setFocusObjectNext(thisCode, win, obj);
				}
			}


		// Redraw if need be
		if (llRender)
		{
			// Redraw the checkbox if needed
			if (objCheckbox)
				iObj_setSize(thisCode, objCheckbox, objCheckbox->rc.left, objCheckbox->rc.top, objCheckbox->rc.right - objCheckbox->rc.left, objCheckbox->rc.bottom - objCheckbox->rc.top);

			// Redraw the window
			iWindow_render(thisCode, win, false);
		}
		
		// Do not continue to propagate this message to other objects
		return(false);
	}

	bool iDefaultCallback_onKeyUp(SThisCode* thisCode, SWindow* win, SObject* obj, SVariable* varCtrl, SVariable* varAlt, SVariable* varShift, SVariable* varCaps, SVariable* varAscii, SVariable* varVKey, SVariable* varIsCAS, SVariable* varIsAscii)
	{
		bool		llCtrl, llAlt, llShift, llCaps, llIsCAS, llIsAscii;
		s16			lcAscii;
		u16			lnVKey;


		// Make sure our environment is sane
		if (!iiDefaultCallback_processKeyVariables(thisCode, varCtrl, varAlt, varShift, varCaps, varAscii, varVKey, varIsCAS, varIsAscii, &llCtrl, &llAlt, &llShift, &llCaps, &llIsCAS, &llIsAscii, &lcAscii, &lnVKey))
			return(false);	// Do not continue consuming


		// Do not continue to propagate this message to other objects
		return(false);
	}

	bool iDefaultCallback_onActivate(SThisCode* thisCode, SWindow* win, SObject* obj)
	{
		// Do not continue to propagate this message to other objects
		return(false);
	}

	bool iDefaultCallback_onDeactivate(SThisCode* thisCode, SWindow* win, SObject* obj)
	{
		// Do not continue to propagate this message to other objects
		return(false);
	}

	bool iDefaultCallback_onInteractiveChange(SThisCode* thisCode, SWindow* win, SObject* obj)
	{
		// Do not continue to propagate this message to other objects
		return(false);
	}

	bool iDefaultCallback_onProgrammaticChange(SThisCode* thisCode, SWindow* win, SObject* obj)
	{
		// Do not continue to propagate this message to other objects
		return(false);
	}

	bool iDefaultCallback_onSelect(SThisCode* thisCode, SWindow* win, SObject* obj)
	{
		// Do not continue to propagate this message to other objects
		return(false);
	}

	bool iDefaultCallback_onDeselect(SThisCode* thisCode, SWindow* win, SObject* obj)
	{
		// Do not continue to propagate this message to other objects
		return(false);
	}

	bool iDefaultCallback_onMoved(SThisCode* thisCode, SWindow* win, SObject* obj, SVariable* xOverride_out, SVariable* yOverride_out)
	{
		// Do not continue to propagate this message to other objects
		return(false);
	}

	bool iDefaultCallback_onQueryUnload(SThisCode* thisCode, SWindow* win, SObject* obj)
	{
		// Do not continue to propagate this message to other objects
		return(false);
	}

	bool iDefaultCallback_onAddObject(SThisCode* thisCode, SWindow* win, SObject* obj)
	{
		// Do not continue to propagate this message to other objects
		return(false);
	}

	bool iDefaultCallback_onAddProperty(SThisCode* thisCode, SWindow* win, SObject* obj)
	{
		// Do not continue to propagate this message to other objects
		return(false);
	}

	bool iDefaultCallback_onError(SThisCode* thisCode, SWindow* win, SObject* obj)
	{
		// Do not continue to propagate this message to other objects
		return(false);
	}

	bool iDefaultCallback_onScrolled(SThisCode* thisCode, SWindow* win, SObject* obj)
	{
		// Do not continue to propagate this message to other objects
		return(false);
	}

	// For carousels and riders, sets the left-most object of carousel, or the object to present for a rider
	bool iDefaultCallback_onSetActiveControl(SThisCode* thisCode, SWindow* win, SObject* obj, SVariable* toActive)
	{
// TODO:  relates to accessors.h gsProps_carousel, gsProps_rider, base.cpp, create.cpp, render.cpp, etc.
		// Verify object exists within this.controls[]
		// Set the activeControl
		// Mark dirty
		// If on rider, mark parent carousel dirty
		// Trigger refresh

		// Do not continue to propagate this message to other objects
		return(false);
	}

	bool iDefaultCallback_onSpin(SThisCode* thisCode, SWindow* win, SObject* obj, SVariable* tnDelta, SVariable* tnDirection, SVariable* tnType)
	{
// TODO:  same as onSetActiveControl()
		// tnDelta		= units (in riders, or pixels based on tnType), defaults to riders
		// tnDirection	= negative=left, positive=right, defaults to right
		// tnType		= 0=riders/toolbars, 1=pixels, defaults to riders

		// Do not continue to propagate this message to other objects
		return(false);
	}

	bool iDefaultCallback_onTabClose(SThisCode* thisCode, SWindow* win, SObject* obj)
	{
		// Do not continue to propagate this message to other objects
		return(false);
	}

	bool iDefaultCallback_onTabClick(SThisCode* thisCode, SWindow* win, SObject* obj)
	{
		// Do not continue to propagate this message to other objects
		return(false);
	}

	bool iDefaultCallback_onTabMouseWheel(SThisCode* thisCode, SWindow* win, SObject* obj)
	{
		// Do not continue to propagate this message to other objects
		return(false);
	}

	bool iDefaultCallback_onTabMouseMove(SThisCode* thisCode, SWindow* win, SObject* obj)
	{
		// Do not continue to propagate this message to other objects
		return(false);
	}

	bool iDefaultCallback_onTabMouseDown(SThisCode* thisCode, SWindow* win, SObject* obj)
	{
		// Do not continue to propagate this message to other objects
		return(false);
	}

	bool iDefaultCallback_onTabMouseUp(SThisCode* thisCode, SWindow* win, SObject* obj)
	{
		// Do not continue to propagate this message to other objects
		return(false);
	}

	bool iDefaultCallback_onTabMouseEnter(SThisCode* thisCode, SWindow* win, SObject* obj)
	{
		// Do not continue to propagate this message to other objects
		return(false);
	}

	bool iDefaultCallback_onTabMouseLeave(SThisCode* thisCode, SWindow* win, SObject* obj)
	{
		// Do not continue to propagate this message to other objects
		return(false);
	}
