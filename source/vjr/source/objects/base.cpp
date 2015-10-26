//////////
//
// /libsf/source/vjr/source/objects/base.cpp
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
// Version 0.57
// Copyright (c) 2014 by Rick C. Hodgin
//////
// Last update:
//     Jun.14.2014
//////
// Change log:
//     Jun.14.2014 - Initial creation
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
// Creates the object structure
//
//////
	SObject* iObj_create(SThisCode* thisCode, s32 objType, SObject* objParent)
	{
		// We need to create it
		logfunc(__FUNCTION__);
		switch (objType)
		{
			case _OBJ_TYPE_EMPTY:		// Empty, used as a placeholder object that is not drawn
				return(iSubobj_createEmpty(thisCode, NULL, objParent));

			case _OBJ_TYPE_FORM:			// Form class, the main outer window the OS sees
				return(iSubobj_createForm(thisCode, NULL, objParent));

			case _OBJ_TYPE_SUBFORM:		// A new class which has its own drawing content and can be moved about using UI features
				return(iSubobj_createSubform(thisCode, NULL, objParent));

			case _OBJ_TYPE_CAROUSEL:	// A new class which is its a holder for riders, allowing multiple classes to be docked and interacted with/upon as a group
				return(iSubobj_createCarousel(thisCode, NULL, objParent));

			case _OBJ_TYPE_RIDER:		// A new class which wraps around a form or subform allowing it to be presented inside a carousel
				return(iSubobj_createRider(thisCode, NULL, objParent));

			case _OBJ_TYPE_LABEL:		// A label
				return(iSubobj_createLabel(thisCode, NULL, objParent));

			case _OBJ_TYPE_TEXTBOX:		// An input textbox
				return(iSubobj_createTextbox(thisCode, NULL, objParent));

			case _OBJ_TYPE_BUTTON:		// A push button
				return(iSubobj_createButton(thisCode, NULL, objParent));

			case _OBJ_TYPE_EDITBOX:		// An input multi-line editbox
				return(iSubobj_createEditbox(thisCode, NULL, objParent));

			case _OBJ_TYPE_IMAGE:		// A graphical image
				return(iSubobj_createImage(thisCode, NULL, objParent));

			case _OBJ_TYPE_CHECKBOX:		// A checkbox
				return(iSubobj_createCheckbox(thisCode, NULL, objParent));

			case _OBJ_TYPE_OPTION:		// A combination selection
				return(iSubobj_createOption(thisCode, NULL, objParent));

			case _OBJ_TYPE_RADIO:		// A radio dial, which can also present as a slider or spinner
				return(iSubobj_createRadio(thisCode, NULL, objParent));

			case _OBJ_TYPE_CMDGROUP:	// A command button group
				return(iSubobj_createCmdGroup(thisCode, NULL, objParent));

			case _OBJ_TYPE_OPTGROUP:	// An option group
				return(iSubobj_createOptGroup(thisCode, NULL, objParent));

			case _OBJ_TYPE_LISTBOX:		// A listbox
				return(iSubobj_createListbox(thisCode, NULL, objParent));

			case _OBJ_TYPE_COMBOBOX:	// A combobox
				return(iSubobj_createCombobox(thisCode, NULL, objParent));

			case _OBJ_TYPE_FORMSET:		// A formset
				return(iSubobj_createFormset(thisCode, NULL, objParent));

			case _OBJ_TYPE_TOOLBAR:		// A toolbar
				return(iSubobj_createToolbar(thisCode, NULL, objParent));

			case _OBJ_TYPE_SEPARATOR:	// A separator
				return(iSubobj_createSeparator(thisCode, NULL, objParent));

			case _OBJ_TYPE_LINE:		// A line
				return(iSubobj_createLine(thisCode, NULL, objParent));

			case _OBJ_TYPE_SHAPE:		// A shape
				return(iSubobj_createShape(thisCode, NULL, objParent));

			case _OBJ_TYPE_CONTAINER:	// A container
				return(iSubobj_createContainer(thisCode, NULL, objParent));

			case _OBJ_TYPE_CONTROL:		// A blocking container
				return(iSubobj_createControl(thisCode, NULL, objParent));

			case _OBJ_TYPE_GRID:		// A grid
				return(iSubobj_createGrid(thisCode, NULL, objParent));

			case _OBJ_TYPE_COLUMN:		// A grid's column object
				return(iSubobj_createColumn(thisCode, NULL, objParent));

			case _OBJ_TYPE_HEADER:		// A grid's header object
				return(iSubobj_createHeader(thisCode, NULL, objParent));

			case _OBJ_TYPE_OLEBOUND:	// A bound OLE object
				return(iSubobj_createOleBound(thisCode, NULL, objParent));

			case _OBJ_TYPE_OLECONTAIN:	// An OLE container control object
				return(iSubobj_createOleContain(thisCode, NULL, objParent));

			case _OBJ_TYPE_SPINNER:		// A spinner
				return(iSubobj_createSpinner(thisCode, NULL, objParent));

			case _OBJ_TYPE_TIMER:		// A timer
				return(iSubobj_createTimer(thisCode, NULL, objParent));

			case _OBJ_TYPE_HYPERLINK:	// A hyperlink
				return(iSubobj_createHyperlink(thisCode, NULL, objParent));

			case _OBJ_TYPE_COLLECTION:	// A collection
				return(iSubobj_createCollection(thisCode, NULL, objParent));

			case _OBJ_TYPE_PAGE:		// A page within a pageframe
				return(iSubobj_createPage(thisCode, NULL, objParent));

			case _OBJ_TYPE_PAGEFRAME:	// A pageframe
				return(iSubobj_createPageFrame(thisCode, NULL, objParent));

			case _OBJ_TYPE_SESSION:		// A session
				return(iSubobj_createSession(thisCode, NULL, objParent));

			case _OBJ_TYPE_CUSTOM:		// A custom class
				return(iSubobj_createCustom(thisCode, NULL, objParent));

			case _OBJ_TYPE_EXCEPTION:	// An exception
				return(iSubobj_createException(thisCode, NULL, objParent));

			case _OBJ_TYPE_SETTINGS:	// Settings
				return(iSubobj_createSettings(thisCode, NULL, objParent));

			default:
// TODO:  We should never get here.  If we do it's a developer error.  Check the call stack and determine the cause.
				return(NULL);
		}
	}




//////////
//
// Called to create an object and append it to the end of the
// indicated object as a child object.
//
//////
//
// Returns:
//		SObject*		-- To new object which was added
//		sub_obj_output	-- Populated with the pointer of the sub-object
//
//////
	SObject* iObj_addChild(SThisCode* thisCode, s32 objType, SObject* objParent)
	{
		SObject* objNew;


		// Make sure our environment is sane
		logfunc(__FUNCTION__);
		objNew = NULL;
		if (objParent)
		{
			// Create the new object using the default template
			objNew = iObj_create(thisCode, objType, objParent);

			// Append if valid
			if (objNew)
				iObj_appendObjToParent(thisCode, objParent, objNew);
		}

		// Indicate our status
		return(objNew);
	}




//////////
//
// Copy the indicated object.
//
//////
	SObject* iObj_copy(SThisCode* thisCode, SObject* template_obj, SObject* prevObj, SObject* nextObj, SObject* parent, bool tlCopyChildren, bool tlCopySiblings, bool tlCreateSeparateBitmapBuffers)
	{
		SObject* obj;
		SObject* objSib;
		SObject* objNew;


		// Create the object
		logfunc(__FUNCTION__);
		if (!template_obj)
			return(NULL);

		// Create the new object
		obj = (SObject*)malloc(sizeof(SObject));
		if (obj)
		{

			//////////
			// Initialize the object
			//////
				memset(obj, 0, sizeof(SObject));


			//////////
			// Copy the object's existing contents
			//////
				memcpy(&obj->p, &template_obj->p, sizeof(obj->p));		// Copy the existing object properties


			//////////
			// Copy existing events
			//////
				memcpy(&obj->ev, &template_obj->ev, sizeof(obj->ev));


			//////////
			// Update the next and parent, and clear out any bmpScaled
			//////
				obj->ll.prevObj				= prevObj;
				obj->ll.nextObj				= nextObj;
				obj->parent					= parent;

				obj->objType				= template_obj->objType;
				obj->isRendered				= template_obj->isRendered;
				obj->isPublished			= template_obj->isPublished;
				obj->isDirtyRender			= template_obj->isDirtyRender;
				obj->isDirtyPublish			= template_obj->isDirtyPublish;

				CopyRect(&obj->rc,			&template_obj->rc);
				CopyRect(&obj->rco,			&template_obj->rco);
				CopyRect(&obj->rcp,			&template_obj->rcp);
				CopyRect(&obj->rcClient,	&template_obj->rcClient);


			//////////
			// Copy all of the properties one-by-one
			//////
				iObjProp_copyAll(thisCode, obj, template_obj, true);


			//////////
			// Duplicate the bitmap buffer if need be
			//////
				if (tlCreateSeparateBitmapBuffers)
					obj->bmp = iBmp_copy(template_obj->bmp);


			//////////
			// Copy children if need be
			//////
				if (tlCopyChildren && template_obj->firstChild)
					obj->firstChild = iObj_copy(thisCode, template_obj->firstChild, NULL, NULL, obj, true, true, tlCreateSeparateBitmapBuffers);


			//////////
			// Copy siblings if need be
			//////
				if (tlCopySiblings && template_obj->ll.nextObj)
				{

					//////////
					//
					// Iterate through each sibling, appending it:
					//
					//		objSib		-- Iterates through template_obj
					//		objNew		-- Copy of each objSib created
					//		objPrev		-- The last object which needs to point forward to its next sibling
					//
					//////
						for (objSib = template_obj->ll.nextObj; objSib; objSib = objSib->ll.nextObj)
						{
							// Copy this sibling
							objNew = iObj_copy(thisCode, objSib, NULL, NULL, obj, true, false, tlCreateSeparateBitmapBuffers);
							if (objNew)
							{
								// Append it to the chain
								iLl_appendExistingNodeAtEnd((SLL**)&obj, (SLL*)objNew);

							} else {
								// Should never happen
// TODO:  For extra info, we could create the call stack
								iError_signal(thisCode, _ERROR_INTERNAL_ERROR, NULL, true, NULL, false);
							}
						}

				}

		}

		// Indicate our success or failure
		return(obj);
	}




//////////
//
// Delete the indicated object.
//
//////
	void iObj_delete(SThisCode* thisCode, SObject** objRoot, bool tlDeleteSelf, bool tlDeleteChildren, bool tlDeleteSiblings)
	{
		SObject* obj;
		SObject* objSib;
		SObject* objSibNext;


		logfunc(__FUNCTION__);
		// Make sure our environment is sane
		if (objRoot && *objRoot)
		{
			//////////
			// Grab our object, and mark it deleted
			//////
				obj			= *objRoot;
				*objRoot	= NULL;


			//////////
			// Delete children
			//////
				if (tlDeleteChildren && obj->firstChild)
					iObj_delete(thisCode, &obj->firstChild, true, true, true);


			//////////
			// Delete siblings
			//////
				if (tlDeleteSiblings && obj->ll.next)
				{
					// Iterate by looking ahead to the next entry, so we update the chain
					objSib = obj->ll.nextObj;
					while (objSib)
					{
						// Grab the next sibling
						objSibNext = objSib->ll.nextObj;

						// Delete this sibling
						iObj_delete(thisCode, &objSib, true, true, false);

						// Move to next sibling
						objSib = objSibNext;
					}
				}


			//////////
			// Delete self
			//////
				switch (obj->objType)
				{
					case _OBJ_TYPE_EMPTY:
						iSubobj_deleteEmpty(thisCode, obj, true);
						break;
					case _OBJ_TYPE_FORM:
						iSubobj_deleteForm(thisCode, obj, true);
						break;
					case _OBJ_TYPE_SUBFORM:
						iSubobj_deleteSubform(thisCode, obj, true);
						break;
					case _OBJ_TYPE_CAROUSEL:
						iSubobj_deleteCarousel(thisCode, obj, true, tlDeleteChildren, tlDeleteChildren);
						break;
					case _OBJ_TYPE_RIDER:
						iSubobj_deleteRider(thisCode, obj, true, false);
						break;
					case _OBJ_TYPE_LABEL:
						iSubobj_deleteLabel(thisCode, obj, true);
						break;
					case _OBJ_TYPE_TEXTBOX:
						iSubobj_deleteTextbox(thisCode, obj, true);
						break;
					case _OBJ_TYPE_BUTTON:
						iSubobj_deleteButton(thisCode, obj, true);
						break;
					case _OBJ_TYPE_EDITBOX:
						iSubobj_deleteEditbox(thisCode, obj, true);
						break;
					case _OBJ_TYPE_IMAGE:
						iSubobj_deleteImage(thisCode, obj, true);
						break;
					case _OBJ_TYPE_CHECKBOX:
						iSubobj_deleteCheckbox(thisCode, obj, true);
						break;
					case _OBJ_TYPE_OPTION:
						iSubobj_deleteOption(thisCode, obj, true);
						break;
					case _OBJ_TYPE_RADIO:
						iSubobj_deleteRadio(thisCode, obj, true);
						break;
					case _OBJ_TYPE_CMDGROUP:
						iSubobj_deleteCmdGroup(thisCode, obj, true);
						break;
					case _OBJ_TYPE_OPTGROUP:
						iSubobj_deleteOptGroup(thisCode, obj, true);
						break;
					case _OBJ_TYPE_LISTBOX:
						iSubobj_deleteListbox(thisCode, obj, true);
						break;
					case _OBJ_TYPE_COMBOBOX:
						iSubobj_deleteCombobox(thisCode, obj, true);
						break;
					case _OBJ_TYPE_FORMSET:
						iSubobj_deleteFormset(thisCode, obj, true);
						break;
					case _OBJ_TYPE_TOOLBAR:
						iSubobj_deleteToolbar(thisCode, obj, true);
						break;
					case _OBJ_TYPE_SEPARATOR:
						iSubobj_deleteSeparator(thisCode, obj, true);
						break;
					case _OBJ_TYPE_LINE:
						iSubobj_deleteLine(thisCode, obj, true);
						break;
					case _OBJ_TYPE_SHAPE:
						iSubobj_deleteShape(thisCode, obj, true);
						break;
					case _OBJ_TYPE_CONTAINER:
						iSubobj_deleteContainer(thisCode, obj, true);
						break;
					case _OBJ_TYPE_CONTROL:
						iSubobj_deleteControl(thisCode, obj, true);
						break;
					case _OBJ_TYPE_GRID:
						iSubobj_deleteGrid(thisCode, obj, true);
						break;
					case _OBJ_TYPE_COLUMN:
						iSubobj_deleteColumn(thisCode, obj, true);
						break;
					case _OBJ_TYPE_HEADER:
						iSubobj_deleteHeader(thisCode, obj, true);
						break;
					case _OBJ_TYPE_OLEBOUND:
						iSubobj_deleteOleBound(thisCode, obj, true);
						break;
					case _OBJ_TYPE_OLECONTAIN:
						iSubobj_deleteOleContain(thisCode, obj, true);
						break;
					case _OBJ_TYPE_SPINNER:
						iSubobj_deleteSpinner(thisCode, obj, true);
						break;
					case _OBJ_TYPE_TIMER:
						iSubobj_deleteTimer(thisCode, obj, true);
						break;
					case _OBJ_TYPE_HYPERLINK:
						iSubobj_deleteHyperlink(thisCode, obj, true);
						break;
					case _OBJ_TYPE_COLLECTION:
						iSubobj_deleteCollection(thisCode, obj, true);
						break;
					case _OBJ_TYPE_PAGE:
						iSubobj_deletePage(thisCode, obj, true);
						break;
					case _OBJ_TYPE_PAGEFRAME:
						iSubobj_deletePageFrame(thisCode, obj, true);
						break;
					case _OBJ_TYPE_SESSION:
						iSubobj_deleteSession(thisCode, obj, true);
						break;
					case _OBJ_TYPE_CUSTOM:
						iSubobj_deleteCustom(thisCode, obj, true);
						break;
					case _OBJ_TYPE_EXCEPTION:
						iSubobj_deleteException(thisCode, obj, true);
						break;
					case _OBJ_TYPE_SETTINGS:
						iSubobj_deleteSettings(thisCode, obj, true);
						break;
				}
		}
	}




//////////
//
// Called to set focus on the indicated control.
//
//////
	bool iObj_setFocus(SThisCode* thisCode, SWindow* win, SObject* obj, bool tlClearOtherControlsWithFocus)
	{
		logfunc(__FUNCTION__);
		// Clear the focus if we should
		if (tlClearOtherControlsWithFocus)
			iObj_clearFocus(thisCode, win, iObj_find_rootmostObject(thisCode, obj), true, true);

		// Set the focus
		if (!obj->p.hasFocus)
		{
			// Set focus
			obj->p.hasFocus = true;

			// Mark the object dirty
			iObj_setDirtyRender_ascent(thisCode, obj, true);

			// Signal the change
			iEngine_raise_event(thisCode, _EVENT_ONGOTFOCUS, win, obj);

			// Indicate we set focus
			return(true);
		}

		// Indicate focus was not changed
		return(false);
	}




//////////
//
// Clear the focus.
//
//////
	void iObj_clearFocus(SThisCode* thisCode, SWindow* win, SObject* obj, bool tlClearChildren, bool tlClearSiblings)
	{
		SObject*			objSib;
		SFocusHighlight*	focus;


		// Clear children
		logfunc(__FUNCTION__);
		if (tlClearChildren && obj->firstChild)
			iObj_clearFocus(thisCode, win, obj->firstChild, true, true);

		// Clear self
		if (obj->p.hasFocus)
		{
			// Clear focus
			obj->p.hasFocus = false;

			// Mark the object dirty
			iObj_setDirtyRender_ascent(thisCode, obj, true);

			// Remove the focus highlight window around the control (if any)
			focus = iFocusHighlight_findByObj(obj);
			if (focus)
				iFocusHighlight_delete(focus);

			// If it was a checkbox that lost focus, then we need to release the parent as well
			if (obj->parent && obj->parent->objType == _OBJ_TYPE_CHECKBOX)
			{
				// The control was part of a checkbox, make sure the parent is released as well
				focus = iFocusHighlight_findByObj(obj->parent);
				if (focus)
					iFocusHighlight_delete(focus);
			}

			// Signal the change
			iEngine_raise_event(thisCode, _EVENT_ONLOSTFOCUS, win, obj);
		}

		// Clear siblings
		if (tlClearSiblings && obj->ll.next)
		{
			// Begin at the next sibling
			objSib = obj->ll.nextObj;
			while (objSib)
			{
				// Clear this sibling
				iObj_clearFocus(thisCode, win, objSib, true, false);

				// Move to the next sibling
				objSib = objSib->ll.nextObj;
			}
		}
	}




//////////
//
// Finds the root parent and returns that value
//
//////
	SObject* iObj_find_rootmostObject(SThisCode* thisCode, SObject* obj)
	{
		// If there's a parent, continue up the chain
		logfunc(__FUNCTION__);
		if (obj->parent)		return(iObj_find_rootmostObject(thisCode, obj->parent));
		else					return(obj);		// This is the parent-most object
	}




//////////
//
// Called to find the RECT of the indicated object in screen coordinates
//
//////
	bool iObj_find_screenRect(SThisCode* thisCode, SObject* obj, RECT* rc)
	{
		SObject*	objRoot;
		SWindow*	win;
		RECT		lrcWin, lrcObj;


		// Make sure our environment is sane
		logfunc(__FUNCTION__);
		if (obj && rc)
		{
			// Grab the parent-most object
			objRoot = iObj_find_rootmostObject(thisCode, obj);

			// It must be a form, so we look for the form on the window
			win = iWindow_findByObj(thisCode, objRoot);
			if (win)
			{
				// Get the coordinates
				CopyRect(&lrcWin, &win->rc);
				SetRect(&lrcObj, 0, 0, objRoot->bmp->bi.biWidth, objRoot->bmp->bi.biHeight);

				// Adjust for the child object's location within
				if (iObj_find_relativeRect(thisCode, objRoot, obj, 0, 0, &lrcObj, true, true))
				{
					// Calculate the adjustment
					SetRect(rc, lrcWin.left + lrcObj.left, lrcWin.top + lrcObj.top, lrcWin.left + lrcObj.right, lrcWin.top + lrcObj.bottom);

					// Indicate success
					return(true);
				}
			}
		}
		// If we get here, we could not obtain that information
		return(false);
	}




//////////
//
// Called to find the relative rectangle of the indicated
//
//////
	bool iObj_find_relativeRect(SThisCode* thisCode, SObject* objThis, SObject* objTarget, s32 x, s32 y, RECT* rc, bool tlProcessChildren, bool tlProcessSiblings)
	{
		s32			lnX, lnY;
		SObject*	objSib;


		// Make sure our environment is sane
		logfunc(__FUNCTION__);
		if (objThis && objTarget)
		{
			// Copy the variables
			lnX = x + objThis->rc.left;
			lnY = y + objThis->rc.top;

			// Add in the client coordinates for forms and sub-forms
			if (objThis->objType == _OBJ_TYPE_FORM || objThis->objType == _OBJ_TYPE_SUBFORM)
			{
				lnX += objThis->rcClient.left;
				lnY += objThis->rcClient.top;
			}


			//////////
			// Is this the control?
			//////
				if (objThis == objTarget)
				{
					// Build the rectangle
					SetRect(rc,	lnX - ((objTarget->objType == _OBJ_TYPE_FORM || objTarget->objType == _OBJ_TYPE_SUBFORM) ? objTarget->rcClient.left : 0),
								lnY - ((objTarget->objType == _OBJ_TYPE_FORM || objTarget->objType == _OBJ_TYPE_SUBFORM) ? objTarget->rcClient.top  : 0),
								lnX - ((objTarget->objType == _OBJ_TYPE_FORM || objTarget->objType == _OBJ_TYPE_SUBFORM) ? objTarget->rcClient.left : 0) + objTarget->rc.right  - objTarget->rc.left,
								lnY - ((objTarget->objType == _OBJ_TYPE_FORM || objTarget->objType == _OBJ_TYPE_SUBFORM) ? objTarget->rcClient.top  : 0) + objTarget->rc.bottom - objTarget->rc.top);

					// Indicate success
					return(true);
				}


			//////////
			// Scan through children
			//////
				if (objThis->firstChild && tlProcessChildren)
				{
					if (iObj_find_relativeRect(thisCode, objThis->firstChild, objTarget, lnX, lnY, rc, true, true))
						return(true);
				}


			//////////
			// Check siblings
			//////
				if (tlProcessSiblings)
				{
					// Begin at the first sibling
					objSib = objThis->ll.nextObj;
					while (objSib)
					{
						// Process this sibling
						if (iObj_find_relativeRect(thisCode, objSib, objTarget, x, y, rc, true, false))
							return(true);

						// Move to the next sibling
						objSib = objSib->ll.nextObj;
					}
				}
			}

		// Invalid
		return(false);
	}




//////////
//
// Called to find the thisForm
//
//////
	SObject* iObj_find_thisForm(SThisCode* thisCode, SObject* obj)
	{
		logfunc(__FUNCTION__);
		return(iiObj_findParentObject_byType(thisCode, obj, _OBJ_TYPE_FORM, true));
	}




//////////
//
// Called to find the thisSubform object
//
//////
	SObject* iObj_find_thisSubform(SThisCode* thisCode, SObject* obj)
	{
		logfunc(__FUNCTION__);
		return(iiObj_findParentObject_byType(thisCode, obj, _OBJ_TYPE_SUBFORM, true));
	}




//////////
//
// Called to find the thisRider object
//
//////
	SObject* iObj_find_thisRider(SThisCode* thisCode, SObject* obj)
	{
		logfunc(__FUNCTION__);
		return(iiObj_findParentObject_byType(thisCode, obj, _OBJ_TYPE_RIDER, true));
	}




/////////
//
// Called to search for the indicated object
//
//////
	SObject* iiObj_findParentObject_byType(SThisCode* thisCode, SObject* objStart, s32 objType, bool tlSearchSelf)
	{
		logfunc(__FUNCTION__);

		if (tlSearchSelf && objStart->objType == objType)
		{
			// This is the subform
			return(objStart);

		} else {
			// If we can traverse higher, go higher, if not we're done
			if (objStart->parent)		return(iiObj_findParentObject_byType(thisCode, objStart->parent, objType, true));
			else						return(NULL);
		}
	}




//////////
//
// Called to find the indicated child object by name
//
//////
	SObject* iiObj_findChildObject_byName(SThisCode* thisCode, SObject* objStart, SDatum* name, bool tlSearchSelf, bool tlSearchChildren, bool tlSearchSiblings)
	{
		SObject*	objFound;
		SObject*	objSib;


		logfunc(__FUNCTION__);

		//////////
		// See if this is the name
		//////
			if (tlSearchSelf && propIsName_byDatum(objStart, name))
				return(objStart);


		//////////
		// See if they are searching grandchildren
		//////
			if (tlSearchChildren && objStart->firstChild)
			{
				if ((objFound = iiObj_findChildObject_byName(thisCode, objStart->firstChild, name, true, tlSearchSiblings, tlSearchChildren)))
					return(objFound);
			}


		//////////
		// Search siblings
		//////
			if (tlSearchSiblings)
			{
				for (objSib = objStart->ll.nextObj; objSib; objSib = objSib->ll.nextObj)
				{
					// Search this sibling
					if ((objFound = iiObj_findChildObject_byName(thisCode, objSib, name, true, tlSearchChildren, false)))
						return(objFound);
				}
			}


		//////////
		// If we get here, not found
		//////
			return(NULL);
	}




//////////
//
// Called to determine if the indicated object is the command window
//
//////
	bool iObj_isCommandWindow(SThisCode* thisCode, SObject* obj)
	{
		logfunc(__FUNCTION__);
		return(obj == _cmd);
	}




//////////
//
// Called to set the focus highlights (blue borders around the focused control)
//
//////
	void iObj_setFocusHighlights(SThisCode* thisCode, SWindow* win, SObject* obj, s32 x, s32 y, bool tlProcessChildren, bool tlProcessSiblings)
	{
		u32					lnI;
		s32					lnX, lnY, lnFocusHighlightPixels, lnFocusHighlightBorderPixels;
		bool				llFound, llChildHasFocus;
		RECT				lrc;
		SObject*			objSib;
		SFocusHighlight*	focus;
		SFocusHighlight*	focusUnused;


		// Make sure our environment is sane
		logfunc(__FUNCTION__);
		focus = NULL;
		if (win && obj && GetActiveWindow() == win->hwnd)
		{
			// Copy the variables
			lnX = x + obj->rc.left;
			lnY = y + obj->rc.top;

			// Add in the client coordinates for forms and sub-forms
			if (obj->objType == _OBJ_TYPE_FORM || obj->objType == _OBJ_TYPE_SUBFORM)
			{
				lnX += obj->rcClient.left;
				lnY += obj->rcClient.top;
			}


			//////////
			// Scan through children
			//////
				if (obj->firstChild && tlProcessChildren)
					iObj_setFocusHighlights(thisCode, win, obj->firstChild, lnX, lnY, true, true);


			//////////
			// Is this a focus window?
			//////
				// Search for an existing focus window for this control
				llFound		= false;
				focusUnused	= 0;
				for (lnI = 0; !llFound && lnI < gFocusHighlights->populatedLength; lnI += sizeof(SFocusHighlight))
				{
					// Grab this pointer
					focus = (SFocusHighlight*)(gFocusHighlights->data_u8 + lnI);

					// Is this it?
					     if (focus->isValid && focus->obj == obj)		llFound		= true;
					else if (focusUnused == NULL)						focusUnused	= focus;
				}


			//////////
			// Check the checkbox
			//////
				llChildHasFocus = false;
				if (obj->objType == _OBJ_TYPE_CHECKBOX)
				{
					// Does the image have focus?
					llChildHasFocus  = (obj->firstChild && obj->firstChild->p.hasFocus);
					llChildHasFocus |= (obj->firstChild && obj->firstChild->ll.next && ((SObject*)obj->firstChild->ll.next)->p.hasFocus);
				}


			//////////
			// Should this control have focus?
			//////
				if ((obj->p.hasFocus || llChildHasFocus) && obj->objType != _OBJ_TYPE_CAROUSEL && obj->objType != _OBJ_TYPE_RIDER && !(obj->parent && obj->parent->objType == _OBJ_TYPE_CHECKBOX))
				{
					// This needs to be a focus window
					if (!llFound)
					{
						// We need to add it
						if (!focusUnused)
						{
							// Append a new record
							focus = (SFocusHighlight*)iBuilder_allocateBytes(gFocusHighlights, sizeof(SFocusHighlight));

						} else {
							// Use the first unused record we found
							focus = focusUnused;
						}

						// If the item was created okay, process it
						if (focus)
						{
							// Populate the new entry
							focus->obj	= obj;
							focus->win	= win;
							lnFocusHighlightPixels			= propGet_settings_FocusHighlightPixels(_settings);
							lnFocusHighlightBorderPixels	= propGet_settings_FocusHighlightBorderPixels(_settings);
							SetRect(&lrc,	lnX - ((obj->objType == _OBJ_TYPE_FORM || obj->objType == _OBJ_TYPE_SUBFORM) ? obj->rcClient.left : 0) - lnFocusHighlightPixels - lnFocusHighlightBorderPixels,
											lnY - ((obj->objType == _OBJ_TYPE_FORM || obj->objType == _OBJ_TYPE_SUBFORM) ? obj->rcClient.top  : 0) - lnFocusHighlightPixels - lnFocusHighlightBorderPixels,
											lnX - ((obj->objType == _OBJ_TYPE_FORM || obj->objType == _OBJ_TYPE_SUBFORM) ? obj->rcClient.left : 0) + lnFocusHighlightPixels + lnFocusHighlightBorderPixels + obj->rc.right  - obj->rc.left,
											lnY - ((obj->objType == _OBJ_TYPE_FORM || obj->objType == _OBJ_TYPE_SUBFORM) ? obj->rcClient.top  : 0) + lnFocusHighlightPixels + lnFocusHighlightBorderPixels + obj->rc.bottom - obj->rc.top);

							// Physically create the window
							iFocusHighlight_create(focus, &lrc);
						}
					}

				} else if (focus) {
					// This needs to NOT be a focus window
					if (llFound)
						iFocusHighlight_delete(focus);
				}


			//////////
			// Check siblings
			//////
				if (tlProcessSiblings)
				{
					// Begin at the first sibling
					objSib = obj->ll.nextObj;
					while (objSib)
					{
						// Process this sibling
						iObj_setFocusHighlights(thisCode, win, objSib, x, y, true, false);

						// Move to the next sibling
						objSib = objSib->ll.nextObj;
					}
				}
		}
	}




//////////
//
// Called to get a list of controls which have focus
//
//////
	void iObj_findFocusControls(SThisCode* thisCode, SObject* obj, SBuilder* objFocusControls, bool tlProcessSiblings)
	{
		SObject* objSib;


		logfunc(__FUNCTION__);
		//////////
		// Process any children first
		//////
			if (obj->firstChild)
				iObj_findFocusControls(thisCode, obj->firstChild, objFocusControls, true);


		//////////
		// Process self
		//////
			if (obj->p.hasFocus)
				iBuilder_append_uptr(objFocusControls, (uptr)obj);


		//////////
		// Process any siblings
		//////
			if (tlProcessSiblings)
			{
				// Iterate through every sibling and process it, but don't process its siblings
				objSib = obj->ll.nextObj;
				while (objSib)
				{
					// Process this sibling
					iObj_findFocusControls(thisCode, objSib, objFocusControls, false);

					// Move to next sibling
					objSib = objSib->ll.nextObj;
				}
			}
	}




//////////
//
// Called to move to set focus on the previous control
//
//////
	bool iObj_setFocusObjectPrev(SThisCode* thisCode, SWindow* win, SObject* obj)
	{
		// Attempt the focus
		logfunc(__FUNCTION__);
		if (obj->ll.prev)
			return(iObj_setFocus(thisCode, win, (SObject*)obj->ll.prev, true));

		// Nothing before
		return(false);
	}




/////////
//
// Called to move to set focus on the next control
//
//////
	bool iObj_setFocusObjectNext(SThisCode* thisCode, SWindow* win, SObject* obj)
	{
		// Attempt the focus
		logfunc(__FUNCTION__);
		if (obj->ll.next)
			return(iObj_setFocus(thisCode, win, obj->ll.nextObj, true));

		// Nothing after
		return(false);
	}




//////////
//
// Called to check to see if any object at or below the indicated object has focus
//
//////
	bool iObj_focus_descentCheck(SThisCode* thisCode, SObject* obj, bool tlCheckChildren, bool tlCheckSiblings)
	{
		return((iObj_focus_descentCheckObj(thisCode, obj, tlCheckChildren, tlCheckSiblings) != NULL));
	}




//////////
//
// Called to return which control (if any) has focus
//
//////
	SObject* iObj_focus_descentCheckObj(SThisCode* thisCode, SObject* obj, bool tlCheckChildren, bool tlCheckSiblings)
	{
		SObject* objSib;
		SObject* objFocus;


		//////////
		// If it has focus we're done (because we're only looking to see IF any have focus)
		//////
			if (obj->p.hasFocus)
				return(obj);


		//////////
		// Check the children
		//////
			if (tlCheckChildren && obj->firstChild && (objFocus = iObj_focus_descentCheckObj(thisCode, obj->firstChild, true, true)))
				return(objFocus);


		//////////
		// Check the siblings
		//////
			if (tlCheckSiblings && obj->ll.next)
			{
				// Skip to the sibling
				objSib = obj->ll.nextObj;
				while (objSib)
				{
					// See if this one has focus
					if ((objFocus = iObj_focus_descentCheckObj(thisCode, objSib, true, false)))
						return(objFocus);

					// Move to next sibling
					objSib = objSib->ll.nextObj;
				}
			}


		//////////
		// If we get here, this object and its children do not have focus
		//////
			return(NULL);
	}




//////////
//
// Called to mark the object dirty for rendering.
//
//////
	void iObj_setDirtyRender_ascent(SThisCode* thisCode, SObject* obj, bool tlMarkParents)
	{
		logfunc(__FUNCTION__);
		if (obj)
		{
			// Mark the object dirty
			obj->isDirtyRender	= true;
// TODO:  Consider if this should mark something dirty for publishing as well...
			obj->isDirtyPublish	= true;

			// Mark the parent
// TODO:  This can be made into an iterative loop rather than a recursive function
			if (tlMarkParents && obj->parent)
				iObj_setDirtyRender_ascent(thisCode, obj->parent, true);
		}
	}




//////////
//
// Called to mark the object and optionally all its children and siblings
//
//////
	void iObj_setDirtyRender_descent(SThisCode* thisCode, SObject* obj, bool tlProcessChildren, bool tlProcessSiblings)
	{
		SObject* objSib;


		logfunc(__FUNCTION__);
		if (obj)
		{
			//////////
			// Mark the object dirty
			//////
				obj->isDirtyRender	= true;
				obj->isDirtyPublish	= true;


			//////////
			// Process children?
			//////
				if (tlProcessChildren && obj->firstChild)
					iObj_setDirtyRender_descent(thisCode, obj, true, true);


			//////////
			// Process siblings
			//////
				if (tlProcessSiblings && obj->ll.next)
				{
					// Grab the first sibling
					objSib = obj->ll.nextObj;
					while (objSib)
					{
						// Process this sibling
						iObj_setDirtyRender_descent(thisCode, objSib, true, false);

						// Move to next sibling
						objSib = objSib->ll.nextObj;
					}
				}
		}
	}




//////////
//
// Called to mark the object dirty for publishing.
//
//////
	void iObj_setDirtyPublish_ascent(SThisCode* thisCode, SObject* obj, bool tlMarkParents)
	{
		logfunc(__FUNCTION__);
		if (obj)
		{
			// Mark the object dirty
			obj->isDirtyPublish = true;

			// Mark the parent
// TODO:  This can be made into an iterative loop rather than a recursive function
			if (tlMarkParents && obj->parent)
				iObj_setDirtyPublish_ascent(thisCode, obj->parent, true);
		}
	}




//////////
//
// Called to mark the object and optionally all its children and siblings
//
//////
	void iObj_setDirtyPublish_descent(SThisCode* thisCode, SObject* obj, bool tlProcessChildren, bool tlProcessSiblings)
	{
		SObject* objSib;


		logfunc(__FUNCTION__);
		if (obj)
		{
			//////////
			// Mark the object dirty for publishing
			//////
				obj->isDirtyPublish	= true;


			//////////
			// Process children?
			//////
				if ((tlProcessChildren || obj->objType == _OBJ_TYPE_CAROUSEL || obj->objType == _OBJ_TYPE_RIDER) && obj->firstChild)
					iObj_setDirtyPublish_descent(thisCode, obj, true, true);


			//////////
			// Process siblings
			//////
				if ((tlProcessSiblings || obj->objType == _OBJ_TYPE_CAROUSEL || obj->objType == _OBJ_TYPE_RIDER) && obj->ll.next)
				{
					// Grab the first sibling
					objSib = obj->ll.nextObj;
					while (objSib)
					{
						// Process this sibling
						iObj_setDirtyPublish_descent(thisCode, objSib, true, false);

						// Move to next sibling
						objSib = objSib->ll.nextObj;
					}
				}
		}
	}




//////////
//
// Called to render the indicated object
//
//////
	u32 iObj_render(SThisCode* thisCode, SObject* obj, bool tlForceRender)
	{
		u32			lnPixelsRendered;
		SObject*	objRoot;
		SWindow*	win;


		// Make sure our environment is sane
		logfunc(__FUNCTION__);
		lnPixelsRendered = 0;
		if (obj && obj->isRendered)
		{
			//////////
			// If they're forcing a render, set it up
			//////
				obj->isDirtyRender							|= tlForceRender;
				obj->ogl.quad.updateTextureWithNewBitmap	= obj->isDirtyRender;


			//////////
			// Make sure there is a bit bucket
			//////
				if (!obj->bmp)
				{
					// Initially allocate
					obj->isDirtyRender	= true;
					obj->bmp			= iBmp_allocate();
					iBmp_createBySize(obj->bmp,		obj->rc.right - obj->rc.left,
													obj->rc.bottom - obj->rc.top,
													24);

				} else if (obj->bmp->bi.biWidth != obj->rc.right - obj->rc.left || obj->bmp->bi.biHeight != obj->rc.bottom - obj->rc.top) {
					// Resize
					obj->isDirtyRender = true;
					obj->bmp			= iBmp_verifySizeOrResize(obj->bmp,		obj->rc.right - obj->rc.left,
																				obj->rc.bottom - obj->rc.top,
																				obj->bmp->bi.biBitCount);
				}


			//////////
			// See if there is any onRender() algorithm associated with this object
			//////
				// Find the root object
				objRoot = iObj_find_rootmostObject(thisCode, obj);
				if (objRoot)
				{
					// Locate the associated window (if any)
					win = iWindow_findByObj(thisCode, objRoot);
					iEngine_raise_event(thisCode, _EVENT_ONRENDER, win, obj);
				}


			//////////
			// Which object are they rendering?
			//////
				switch (obj->objType)
				{
					case _OBJ_TYPE_EMPTY:		// Empty, used as a placeholder object that is not drawn
						lnPixelsRendered += iSubobj_renderEmpty(thisCode, obj);
						break;
					case _OBJ_TYPE_FORM:			// Form class, the main outer window the OS sees
						lnPixelsRendered += iSubobj_renderForm(thisCode, obj);
						break;
					case _OBJ_TYPE_SUBFORM:		// A new class which has its own drawing content and can be moved about using UI features
						lnPixelsRendered += iSubobj_renderSubform(thisCode, obj);
						break;
					case _OBJ_TYPE_CAROUSEL:	// A new class which holds riders, and allows multiple contents drawn in a new way
						lnPixelsRendered += iSubobj_renderCarousel(thisCode, obj);
						break;
					case _OBJ_TYPE_RIDER:		// A new class which holds other objects, and allows its content to be drawn in a new way
						lnPixelsRendered += iSubobj_renderRider(thisCode, obj);
						break;
					case _OBJ_TYPE_LABEL:		// A label
						lnPixelsRendered += iSubobj_renderLabel(thisCode, obj);
						break;
					case _OBJ_TYPE_TEXTBOX:		// An input textbox
						lnPixelsRendered += iSubobj_renderTextbox(thisCode, obj);
						break;
					case _OBJ_TYPE_BUTTON:		// A push button
						lnPixelsRendered += iSubobj_renderButton(thisCode, obj);
						break;
					case _OBJ_TYPE_EDITBOX:		// An input multi-line editbox
						lnPixelsRendered += iSubobj_renderEditbox(thisCode, obj);
						break;
					case _OBJ_TYPE_IMAGE:		// A graphical image
						lnPixelsRendered += iSubobj_renderImage(thisCode, obj);
						break;
					case _OBJ_TYPE_CHECKBOX:		// A checkbox
						lnPixelsRendered += iSubobj_renderCheckbox(thisCode, obj);
						break;
					case _OBJ_TYPE_OPTION:		// A combination selection
						lnPixelsRendered += iSubobj_renderOption(thisCode, obj);
						break;
					case _OBJ_TYPE_RADIO:		// A radio dial, which can also present as a slider or spinner
						lnPixelsRendered += iSubobj_renderRadio(thisCode, obj);
						break;
					case _OBJ_TYPE_CMDGROUP:
						lnPixelsRendered += iSubobj_renderCmdGroup(thisCode, obj);
						break;
					case _OBJ_TYPE_OPTGROUP:
						lnPixelsRendered += iSubobj_renderOptGroup(thisCode, obj);
						break;
					case _OBJ_TYPE_LISTBOX:
						lnPixelsRendered += iSubobj_renderListbox(thisCode, obj);
						break;
					case _OBJ_TYPE_COMBOBOX:
						lnPixelsRendered += iSubobj_renderCombobox(thisCode, obj);
						break;
					case _OBJ_TYPE_FORMSET:
						lnPixelsRendered += iSubobj_renderFormset(thisCode, obj);
						break;
					case _OBJ_TYPE_TOOLBAR:
						lnPixelsRendered += iSubobj_renderToolbar(thisCode, obj);
						break;
					case _OBJ_TYPE_SEPARATOR:
						lnPixelsRendered += iSubobj_renderSeparator(thisCode, obj);
						break;
					case _OBJ_TYPE_LINE:
						lnPixelsRendered += iSubobj_renderLine(thisCode, obj);
						break;
					case _OBJ_TYPE_SHAPE:
						lnPixelsRendered += iSubobj_renderShape(thisCode, obj);
						break;
					case _OBJ_TYPE_CONTAINER:
						lnPixelsRendered += iSubobj_renderContainer(thisCode, obj);
						break;
					case _OBJ_TYPE_CONTROL:
						lnPixelsRendered += iSubobj_renderControl(thisCode, obj);
						break;
					case _OBJ_TYPE_GRID:
						lnPixelsRendered += iSubobj_renderGrid(thisCode, obj);
						break;
					case _OBJ_TYPE_COLUMN:
						lnPixelsRendered += iSubobj_renderColumn(thisCode, obj);
						break;
					case _OBJ_TYPE_HEADER:
						lnPixelsRendered += iSubobj_renderHeader(thisCode, obj);
						break;
					case _OBJ_TYPE_OLEBOUND:
						lnPixelsRendered += iSubobj_renderOleBound(thisCode, obj);
						break;
					case _OBJ_TYPE_OLECONTAIN:
						lnPixelsRendered += iSubobj_renderOleContain(thisCode, obj);
						break;
					case _OBJ_TYPE_SPINNER:
						lnPixelsRendered += iSubobj_renderSpinner(thisCode, obj);
						break;
					case _OBJ_TYPE_TIMER:
						lnPixelsRendered += iSubobj_renderTimer(thisCode, obj);
						break;
					case _OBJ_TYPE_HYPERLINK:
						lnPixelsRendered += iSubobj_renderHyperlink(thisCode, obj);
						break;
					case _OBJ_TYPE_COLLECTION:
						lnPixelsRendered += iSubobj_renderCollection(thisCode, obj);
						break;
					case _OBJ_TYPE_PAGE:
						lnPixelsRendered += iSubobj_renderPage(thisCode, obj);
						break;
					case _OBJ_TYPE_PAGEFRAME:
						lnPixelsRendered += iSubobj_renderPageFrame(thisCode, obj);
						break;
					case _OBJ_TYPE_SESSION:
						lnPixelsRendered += iSubobj_renderSession(thisCode, obj);
						break;
					case _OBJ_TYPE_CUSTOM:
						lnPixelsRendered += iSubobj_renderCustom(thisCode, obj);
						break;
					case _OBJ_TYPE_EXCEPTION:
						lnPixelsRendered += iSubobj_renderException(thisCode, obj);
						break;
					case _OBJ_TYPE_SETTINGS:
						lnPixelsRendered += iSubobj_renderSettings(thisCode, obj);
						break;

					default:
// TODO:  We should never get here... we should fire off an internal consistency error ... or a signal flare.  Something to draw attention.
						break;
				}
		}

		// Indicate how many pixels were rendered
		return(lnPixelsRendered);
	}




//////////
//
// Called to descend through the children to see if anything needs to be rendered.
//
//////
	bool iObj_render_descentCheck(SThisCode* thisCode, SObject* obj, bool tlCheckChildren, bool tlCheckSiblings)
	{
		SObject* objSib;


		//////////
		// If it's dirty, we need to render
		//////
			if (obj->isDirtyRender)
				return(true);


		//////////
		// Check the children
		//////
			if (tlCheckChildren && obj->firstChild && iObj_render_descentCheck(thisCode, obj->firstChild, true, true))
				return(true);


		//////////
		// Check the siblings
		//////
			if (tlCheckSiblings && obj->ll.next)
			{
				// Skip to the sibling
				objSib = obj->ll.nextObj;
				while (objSib)
				{
					// See if this one needs rendering
					if (iObj_render_descentCheck(thisCode, objSib, true, false))
						return(true);

					// Move to next sibling
					objSib = objSib->ll.nextObj;
				}
			}


		//////////
		// If we get here, this object and its children do not need to be rendered
		//////
			return(false);
	}




//////////
//
// Called from subobjects to render any object children and sibling they may have based on flags
//
//////
	u32 iObj_renderChildrenAndSiblings(SThisCode* thisCode, SObject* obj, bool tlRenderChildren, bool tlRenderSiblings, bool tlForceRender)
	{
		u32			lnPixelsRendered;
		SObject*	objSib;


		logfunc(__FUNCTION__);
		//////////
		// Render any children
		//////
			lnPixelsRendered = 0;
			if (tlRenderChildren && obj->firstChild)
				lnPixelsRendered += iObj_renderChildrenAndSiblings(thisCode, obj->firstChild, true, true, tlForceRender);


		//////////
		// Render self
		//////
			obj->isDirtyRender |= tlForceRender;
			lnPixelsRendered += iObj_render(thisCode, obj, tlForceRender);


		//////////
		// Render any siblings
		//////
			if (tlRenderSiblings && obj->ll.next)
			{
				objSib = obj->ll.nextObj;
				while (objSib)
				{
					// Render this sibling
					lnPixelsRendered += iObj_renderChildrenAndSiblings(thisCode, objSib, true, false, tlForceRender);

					// Move to next sibling
					objSib = objSib->ll.nextObj;
				}
			}


		//////////
		// Indicate how much was rendered
		//////
			return(lnPixelsRendered);
	}




//////////
//
// Called to publish the indicated object, which takes the rendered bitmaps of all child objects
// and overlays them where they should be.
//
//////
	u32 iObj_publish(SThisCode* thisCode, SObject* obj, RECT* rc, SBitmap* bmpDst, bool tlPublishChildren, bool tlPublishSiblings, bool tlForcePublish, s32 tnLevel)
	{
		s32			lnWidth, lnHeight, lnBackStyle;
		u32			lnPixelsRendered;
		bool		llPublishChildren, llIsVisible, llIsEnabled;
		RECT		lrc, lrcChild, lrc2;
		SWindow*	win;
		SObject*	objRoot;
		SObject*	objSib;


		// Make sure our environment is sane
		logfunc(__FUNCTION__);
		lnPixelsRendered = 0;
		if (obj && obj->bmp)
		{
			//////////
			// Set the force publish flag if need be
			//////
				obj->isDirtyPublish |= (tlForcePublish || tnLevel == 1);


			//////////
			// Determine the position within the parent's rectangle where this object will go
			//////
				// Adjust this item within the parent's rectangle
				SetRect(&lrc,	rc->left	+ obj->rc.left,
								rc->top		+ obj->rc.top,
								rc->left	+ obj->rc.right,
								rc->top		+ obj->rc.bottom);

				// Default the parent's rectangle for any subsequent drawing within by children
				SetRect(&lrcChild, 0, 0, obj->bmp->bi.biWidth, obj->bmp->bi.biHeight);

				// This is a top-level entry, so adjust everything to rcClient, or to 0
				llPublishChildren = true;
				switch (obj->objType)
				{
					case _OBJ_TYPE_FORM:
						// Bypass the frame area
						CopyRect(&lrcChild, &obj->rcClient);
						break;

					case _OBJ_TYPE_SUBFORM:
						// Bypass the frame area
						CopyRect(&lrcChild, &obj->rcClient);

						// Validate if anything has changed on this subform's children, if not then we don't need to publish anything below
						if (!obj->isDirtyPublish && obj->firstChild)
							llPublishChildren = iObj_publish_descentCheck(thisCode, obj->firstChild, true, true);
						break;
				}


			//////////
			// Clip the publication to the target rectangle
			//////
				if (!obj->parent || obj->parent->objType != _OBJ_TYPE_FORM)
				{
					lrc.right	= min(rc->right, lrc.right);
					lrc.bottom	= min(rc->bottom, lrc.bottom);
				}


			//////////
			// Publish any children
			//////
				llIsVisible = propIsVisible(obj);
				llIsEnabled = propIsEnabled(obj);
				lnBackStyle	= propBackStyle(obj);
				if (llPublishChildren && llIsVisible && tlPublishChildren && obj->firstChild)
					lnPixelsRendered += iObj_publish(thisCode, obj->firstChild, &lrcChild, obj->bmp, true, true, tlForcePublish, tnLevel + 1);


			//////////
			// Publish this item
			//////
				if (llIsVisible)
				{
					//////////
					// See if there is any onPublish() algorithm associated with this object
					//////
						// Find the root object
						objRoot = iObj_find_rootmostObject(thisCode, obj);
						if (objRoot)
						{
							// Locate the associated window (if any)
							win = iWindow_findByObj(thisCode, objRoot);
							iEngine_raise_event(thisCode, _EVENT_ONPUBLISH, win, obj);
						}


					// The size of the bitmap should equal the size of the rectangle on the parent.
					lnWidth		= obj->rc.right - obj->rc.left;
					lnHeight	= obj->rc.bottom - obj->rc.top;
					// If it's different, then we need to scale the content
					if (lnWidth != obj->bmp->bi.biWidth || lnHeight != obj->bmp->bi.biHeight)
					{
						// Need to scale, but do we need to create or alter our scaled target bitmap?
						if (!obj->bmpScaled || lnWidth != obj->bmpScaled->bi.biWidth || lnHeight != obj->bmpScaled->bi.biHeight)
						{
							// Delete any existing bitmap
							iBmp_delete(&obj->bmpScaled, true, true);

							// Create the new one
							obj->bmpScaled = iBmp_allocate();
							iBmp_createBySize(obj->bmpScaled, lnWidth, lnHeight, 24);
							// Now when we scale into it, it will be the right size
						}

						// Perform the scale
						iBmp_scale(obj->bmpScaled, obj->bmp);

						// Perform the bitblt
						if (bmpDst && obj->isPublished && obj->isDirtyPublish)
						{
							// If it's not enabled, grayscale it
							if (!llIsEnabled)
							{
								SetRect(&lrc2, 0, 0, obj->bmpScaled->bi.biWidth, obj->bmpScaled->bi.biHeight);
								iBmp_grayscale(obj->bmpScaled, &lrc2);
							}


							//////////
							// Copy
							//////
								switch (obj->objType)
								{
									case _OBJ_TYPE_IMAGE:
									case _OBJ_TYPE_LABEL:
										if (lnBackStyle == _BACK_STYLE_OPAQUE)		lnPixelsRendered += iBmp_bitBlt(bmpDst,		&lrc, obj->bmpScaled);
										else										lnPixelsRendered += iBmp_bitBltMask(bmpDst,	&lrc, obj->bmpScaled);
										break;

									default:
										lnPixelsRendered += iBmp_bitBlt(bmpDst, &lrc, obj->bmpScaled);
										break;
								}
						}

					} else {
						// We can just copy
						if (bmpDst && obj->isPublished && obj->isDirtyPublish && tnLevel != 0)
						{
							// If it's not enabled, grayscale it
							if (!llIsEnabled)
							{
								SetRect(&lrc2, 0, 0, obj->bmp->bi.biWidth, obj->bmp->bi.biHeight);
								iBmp_grayscale(obj->bmp, &lrc2);
							}


							//////////
							// Copy
							//////
								switch (obj->objType)
								{
									case _OBJ_TYPE_IMAGE:
										if (lnBackStyle == _BACK_STYLE_OPAQUE)		lnPixelsRendered += iBmp_bitBlt(bmpDst, &lrc, obj->bmp);
										else										lnPixelsRendered += iBmp_bitBltMask(bmpDst, &lrc, obj->bmp);
										break;

									case _OBJ_TYPE_LABEL:
										// Non-opaque labels are rendered as black on white, with that grayscale being used to influence the forecolor
										if (lnBackStyle == _BACK_STYLE_OPAQUE)		lnPixelsRendered += iBmp_bitBlt(bmpDst, &lrc, obj->bmp);
										else										lnPixelsRendered += iBmp_bitBlt_byGraymask(bmpDst, &lrc, obj->bmp, iObjProp_get_sbgra_direct(thisCode, obj, _INDEX_FORECOLOR));
										break;

									default:
										lnPixelsRendered += iBmp_bitBlt(bmpDst, &lrc, obj->bmp);
										break;
								}
						}
					}
				}


			//////////
			// Lower the flag at this level
			//////
				obj->isDirtyPublish = false;


// s8 buffer[256];
// if (tnLevel >= 0)
// {
// 	sprintf(buffer, "c:\\temp\\publish\\%u_%u_%d.bmp\0", ++gnNextUniqueId, (u32)obj, tnLevel);
// 	iBmp_saveToDisk(bmpDst, buffer);
// }

			//////////
			// Publish any siblings
			//////
				if (tlPublishSiblings)
				{
					// Begin at the next sibling
					objSib = obj->ll.nextObj;
					while (objSib)
					{
						// Publish this sibling
						lnPixelsRendered += iObj_publish(thisCode, objSib, rc, bmpDst, true, false, tlForcePublish, tnLevel);

						// Move to next sibling
						objSib = objSib->ll.nextObj;
					}
				}
		}


		//////////
		// Indicate how many pixels were painted
		//////
			return(lnPixelsRendered);
	}




//////////
//
// Called to descend through the children to see if anything needs to be published.
//
//////
	bool iObj_publish_descentCheck(SThisCode* thisCode, SObject * obj, bool tlCheckChildren, bool tlCheckSiblings)
	{
		SObject* objSib;


		//////////
		// If it's dirty, we need to publish
		//////
			if (obj->isDirtyPublish)
				return(true);


		//////////
		// Check the children
		//////
			if (tlCheckChildren && obj->firstChild && iObj_publish_descentCheck(thisCode, obj->firstChild, true, true))
				return(true);


		//////////
		// Check the siblings
		//////
			if (tlCheckSiblings && obj->ll.next)
			{
				// Skip to the sibling
				objSib = obj->ll.nextObj;
				while (objSib)
				{
					// See if this one needs to be published
					if (iObj_publish_descentCheck(thisCode, objSib, true, false))
						return(true);

					// Move to next sibling
					objSib = objSib->ll.nextObj;
				}
			}


		//////////
		// If we get here, this object and its children do not need to be published
		//////
			return(false);
	}




//////////
//
// Saves the object layout from the current object
//
//////
	CXml* iObj_saveLayoutAs_bxml(SThisCode* thisCode, SObject* obj, cu8* tcFilename, bool tlFullProperties, bool tlSaveChildren, bool tlSaveSiblings, bool* error, u32* errorNum)
	{
		uptr		lnResult;
		union {
			uptr	_bxml;
			CXmlp	bxml;
		};
//		CXmlp		bxmlJDebi, bxmlLayout;


		//////////
		// Make sure the environment is sane
		//////
			if (!(obj && tcFilename && error && errorNum))
			{
				*error		= true;
				*errorNum	= _ERROR_INVALID_PARAMETERS;
				return(NULL);
			}


		//////////
		// Create the root node (which is one level above jdebi in this content)
		//////
			_bxml = xml_load("<jdebi><layout></layout></jdebi>", -1);
			if (!bxml)
			{
				*error		= true;
				*errorNum	= _ERROR_INTERNAL_ERROR;
				return(NULL);
			}


		//////////
		// Access the jdebi and layout tags
		//////
//			bxmlJDebi	= bxml->child(cgcTag_jdebi);
//			bxmlLayout	= bxmlJDebi->child(cgcTag_layout);


		//////////
		// Iterate through each object, appending its content
		//////
			iiObj_saveLayoutAs_bxml_saveObject(thisCode, bxml, obj, tlFullProperties, tlSaveChildren, tlSaveSiblings);


		//////////
		// Save the result
		//////
			lnResult = xml_write_file(_bxml, tcFilename);
			if (lnResult == 0)
			{
				// Success
				*error		= false;
				*errorNum	= 0;

			} else {
				// An error writing the output
				*error		= true;
				*errorNum	= _ERROR_UNABLE_TO_SAVE;
			}
			return(bxml);
	}




//////////
//
// Save the indicated object to the indicated bxml
//
//////
	CXml* iiObj_saveLayoutAs_bxml_saveObject(SThisCode* thisCode, CXml* bxml, SObject* obj, bool tlFullProperties, bool tlSaveChildren, bool tlSaveSiblings)
	{
		s32				lnI;
		SBaseClassMap*	baseClassMap;
		SBasePropMap*	basePropMap;
		SObjPropMap*	thisObjProp;
		CXmlp			bxmlObj, bxmlP, bxmlProps, bxmlProp;
		SVariable*		varData;
		SVariable*		varTypeDetail;
		s8				buffer[64];


		// Make sure there's an object
		if (obj)
		{

			//////////
			// Create the child for this object
			//	<object name="whatever">
			//////
				varData		= propName(obj);
				bxmlObj	= bxml->append_child(new CXml((s8*)cgcTag_object, -1, NULL, 0, (s8*)cgcTag_name, varData->value.data, varData->value.length));


			//////////
			// Append the standard properties
			//////
				bxmlP	= bxmlObj->append_child(new CXml((s8*)cgcTag_p));
				// X
				sprintf(buffer, "%d\0", (s32)propX(obj));
				bxmlP->append_attribute(new CXml((s8*)cgcTag_x, -1, buffer, -1, NULL, NULL, 0));

				// Y
				sprintf(buffer, "%d\0", (s32)propY(obj));
				bxmlP->append_attribute(new CXml((s8*)cgcTag_y, -1, buffer, -1, NULL, NULL, 0));

				// Width
				sprintf(buffer, "%d\0", (s32)propWidth(obj));
				bxmlP->append_attribute(new CXml((s8*)cgcTag_w, -1, buffer, -1, NULL, NULL, 0));

				// Height
				sprintf(buffer, "%d\0", (s32)propHeight(obj));
				bxmlP->append_attribute(new CXml((s8*)cgcTag_h, -1, buffer, -1, NULL, NULL, 0));

				// Class
				varData = propClass(obj);
				bxmlP->append_attribute(new CXml((s8*)cgcTag_class, -1, varData->value.data, varData->value.length, NULL, NULL, 0));

				// Baseclass
				varData = propBaseclass(obj);
				bxmlP->append_attribute(new CXml((s8*)cgcTag_baseclass, -1, varData->value.data, varData->value.length, NULL, NULL, 0));

				// ClassLibrary
				varData = propClassLibrary(obj);
				bxmlP->append_attribute(new CXml((s8*)cgcTag_classLibrary, -1, varData->value.data, varData->value.length, NULL, NULL, 0));


			//////////
			// Append object properties if specified
			//////
				if (tlFullProperties)
				{
					// Locate the base class
// TODO:  We could add a speedup here by storing the baseClassMap location in the object itself at the time of creation
					baseClassMap = iiObj_getBaseclass_byType(thisCode, obj->objType);
					if (baseClassMap)
					{
						// Create the props tag
						bxmlProps = bxmlObj->append_child(new CXml((s8*)cgcTag_props));

						// Locate the property within the object's properties
						thisObjProp = baseClassMap->objProps;
						for (lnI = 0; lnI < baseClassMap->objPropsCount; lnI++)
						{
							switch (lnI)
							{
								case _INDEX_BASECLASS:
								case _INDEX_CLASS:
								case _INDEX_CLASSLIBRARY:
								case _INDEX_NAME:
									// Already recorded above
									break;

								default:
									//////////
									//	<props>
									//		<prop>
									//////
										bxmlProp = bxmlProps->append_child(new CXml((s8*)cgcTag_prop));


									//////////
									// Grab a pointer to the master prop
									//////
										basePropMap	= &gsProps_master[thisObjProp[lnI].index - 1];


									//////////
									// Get the current property in a display-as-text form
									//////
										varData	= iVariable_convertForDisplay(thisCode, iObjProp_get(thisCode, obj, lnI));
										varTypeDetail = iVariable_get_typeDetail(thisCode, varData);


									//////////
									//	<prop name="..." td="..." val="..."/>
									//////
										bxmlProp->append_attribute((s8*)cgcTag_name,			sizeof(cgcTag_name) - 1,			(s8*)basePropMap->propName_s8,		basePropMap->propNameLength);
										bxmlProp->append_attribute((s8*)cgcTag_typeDetail,		sizeof(cgcTag_typeDetail) - 1,		varTypeDetail->value.data,			varTypeDetail->value.length);
										bxmlProp->append_attribute((s8*)cgcTag_value,			sizeof(cgcTag_value) - 1,			varData->value.data,				varData->value.length);


									//////////
									// Delete the variables
									//////
										iVariable_delete(thisCode, varData,			true);
										iVariable_delete(thisCode, varTypeDetail,	true);
										break;
							}

// TODO:  Working here
//							&thisObjProp[lnI];
						}
						// If we get here, not found
					}

// This should never happen.
// If it does it's a design-time error.  Search the call stack to determine which _INDEX_* variable was referenced.
debug_break;
					// Invalid
					return(NULL);
				}
		}

		// Return our input
		return(bxml);
	}




//////////
//
// Duplicate the chain of ObjectLabels, so the destination has a copy of each.
//
//////
	void iObj_duplicateChain(SThisCode* thisCode, SObject** root, SObject* chain)
	{
		SObject*	obj;
		SObject**	oPrevPtr;


		// Create the master record
		logfunc(__FUNCTION__);
		if (root)
		{
			// Repeat adding as many entries as there are
			oPrevPtr = root;
			while (chain)
			{
				// Create this object
				obj = iObj_copy(thisCode, chain, NULL, NULL, chain, true, false, true);
				if (obj)
				{
					// Update the duplicate object's forward pointer in the chain
					*oPrevPtr = obj;

					// Setup the next forward pointer
					oPrevPtr = (SObject**)&obj->ll.next;
				}

				// Move to next item in the chain
				chain = (SObject*)chain->ll.next;
			}
		}
	}




//////////
//
// Called to append the indicated object to the parent
//
//////
	void iObj_appendObjToParent(SThisCode* thisCode, SObject* parent, SObject* obj)
	{
		// Make sure our environment is sane
		logfunc(__FUNCTION__);
		if (parent && obj)
			iLl_appendExistingNodeAtEnd((SLL**)&parent->firstChild, (SLL*)obj);
	}




//////////
//
// Called to duplicate the child objects to this object
//
//////
	void iObj_duplicateChildren(SThisCode* thisCode, SObject* objDst, SObject* objSrc)
	{
		SObject*	objChild;
		SObject*	objCopy;


		// Make sure our environment is sane
		logfunc(__FUNCTION__);
		if (objDst && objSrc && objSrc->firstChild)
		{
			// Duplicate this entry
			objChild = objSrc->firstChild;
			while (objChild)
			{
				// Create the copy (note that all children are automatically copied by using the reference as a template)
				switch (objChild->objType)
				{
					case _OBJ_TYPE_EMPTY:
						objCopy = iSubobj_createForm(thisCode, objChild, objDst);
						break;
					case _OBJ_TYPE_FORM:
						objCopy = iSubobj_createForm(thisCode, objChild, objDst);
						break;
					case _OBJ_TYPE_SUBFORM:
						objCopy = iSubobj_createSubform(thisCode, objChild, objDst);
						break;
					case _OBJ_TYPE_LABEL:
						objCopy = iSubobj_createLabel(thisCode, objChild, objDst);
						break;
					case _OBJ_TYPE_TEXTBOX:
						objCopy = iSubobj_createTextbox(thisCode, objChild, objDst);
						break;
					case _OBJ_TYPE_BUTTON:
						objCopy = iSubobj_createButton(thisCode, objChild, objDst);
						break;
					case _OBJ_TYPE_EDITBOX:
						objCopy = iSubobj_createEditbox(thisCode, objChild, objDst);
						break;
					case _OBJ_TYPE_IMAGE:
						objCopy = iSubobj_createImage(thisCode, objChild, objDst);
						break;
					case _OBJ_TYPE_CHECKBOX:
						objCopy = iSubobj_createCheckbox(thisCode, objChild, objDst);
						break;
					case _OBJ_TYPE_OPTION:
						objCopy = iSubobj_createOption(thisCode, objChild, objDst);
						break;
					case _OBJ_TYPE_RADIO:
						objCopy = iSubobj_createRadio(thisCode, objChild, objDst);
						break;
					case _OBJ_TYPE_CMDGROUP:
						objCopy = iSubobj_createCmdGroup(thisCode, objChild, objDst);
						break;
					case _OBJ_TYPE_OPTGROUP:
						objCopy = iSubobj_createOptGroup(thisCode, objChild, objDst);
						break;
					case _OBJ_TYPE_LISTBOX:
						objCopy = iSubobj_createListbox(thisCode, objChild, objDst);
						break;
					case _OBJ_TYPE_COMBOBOX:
						objCopy = iSubobj_createCombobox(thisCode, objChild, objDst);
						break;
					case _OBJ_TYPE_FORMSET:
						objCopy = iSubobj_createFormset(thisCode, objChild, objDst);
						break;
					case _OBJ_TYPE_TOOLBAR:
						objCopy = iSubobj_createToolbar(thisCode, objChild, objDst);
						break;
					case _OBJ_TYPE_SEPARATOR:
						objCopy = iSubobj_createSeparator(thisCode, objChild, objDst);
						break;
					case _OBJ_TYPE_LINE:
						objCopy = iSubobj_createLine(thisCode, objChild, objDst);
						break;
					case _OBJ_TYPE_SHAPE:
						objCopy = iSubobj_createShape(thisCode, objChild, objDst);
						break;
					case _OBJ_TYPE_CONTAINER:
						objCopy = iSubobj_createContainer(thisCode, objChild, objDst);
						break;
					case _OBJ_TYPE_CONTROL:
						objCopy = iSubobj_createControl(thisCode, objChild, objDst);
						break;
					case _OBJ_TYPE_GRID:
						objCopy = iSubobj_createGrid(thisCode, objChild, objDst);
						break;
					case _OBJ_TYPE_COLUMN:
						objCopy = iSubobj_createColumn(thisCode, objChild, objDst);
						break;
					case _OBJ_TYPE_HEADER:
						objCopy = iSubobj_createHeader(thisCode, objChild, objDst);
						break;
					case _OBJ_TYPE_OLEBOUND:
						objCopy = iSubobj_createOleBound(thisCode, objChild, objDst);
						break;
					case _OBJ_TYPE_OLECONTAIN:
						objCopy = iSubobj_createOleContain(thisCode, objChild, objDst);
						break;
					case _OBJ_TYPE_SPINNER:
						objCopy = iSubobj_createSpinner(thisCode, objChild, objDst);
						break;
					case _OBJ_TYPE_TIMER:
						objCopy = iSubobj_createTimer(thisCode, objChild, objDst);
						break;
					case _OBJ_TYPE_HYPERLINK:
						objCopy = iSubobj_createHyperlink(thisCode, objChild, objDst);
						break;
					case _OBJ_TYPE_COLLECTION:
						objCopy = iSubobj_createCollection(thisCode, objChild, objDst);
						break;
					case _OBJ_TYPE_PAGE:
						objCopy = iSubobj_createPage(thisCode, objChild, objDst);
						break;
					case _OBJ_TYPE_PAGEFRAME:
						objCopy = iSubobj_createPageFrame(thisCode, objChild, objDst);
						break;
					case _OBJ_TYPE_SESSION:
						objCopy = iSubobj_createSession(thisCode, objChild, objDst);
						break;
					case _OBJ_TYPE_CUSTOM:
						objCopy = iSubobj_createCustom(thisCode, objChild, objDst);
						break;
					case _OBJ_TYPE_EXCEPTION:
						objCopy = iSubobj_createException(thisCode, objChild, objDst);
						break;
					case _OBJ_TYPE_SETTINGS:
						objCopy = iSubobj_createSettings(thisCode, objChild, objDst);
						break;

					default:
						objCopy = NULL;
						break;
				}

				// Append the copy if valid
				if (objCopy)
					iObj_appendObjToParent(thisCode, objDst, objChild);

				// Move to next
				objChild = objChild->ll.nextObj;
			}
		}
	}




//////////
//
// Called to set the position for this item.
//
// Note:  This is an internal call, and not the user-code setting thisObj.left = 5, for example.  It sets all values at once, signling only onMoved().
// Note:  For normal event signaling, use iObjProp_set...() with the _INDEX_LEFT, _INDEX_TOP, _INDEX_WIDTH, and/or _INDEX_HEIGHT
//        This will signal the onMoved() event if it actually moved.
//
//////
	void iObj_setPosition(SThisCode* thisCode, SObject* obj, s32 tnLeft, s32 tnTop)
	{
		RECT lrco;


		// Reposition
		logfunc(__FUNCTION__);
		if (!obj)
			return;

		// Note the original locations
		CopyRect(&lrco, &obj->rc);

		// Set the new position
		obj->rc.left	= tnLeft;
		obj->rc.top		= tnTop;


		//////////
		// Signal onMoved() if it moved
		//////
			if (memcmp(&lrco, &obj->rc, sizeof(lrco)) != 0)
			{
				// Has the position changed?
				if (lrco.left != obj->rc.left || lrco.top != obj->rc.top)
					iEngine_raise_event(thisCode, _EVENT_ONMOVED, ((thisCode) ? thisCode->win : NULL), obj, &obj->rc);
			}


// TODO:  We need to see if there are any left_assign() or top_assign() custom methods defined
	}




//////////
//
// Called to set the object size and position.
//
// Note:  This is an internal call, and not the user-code setting thisObj.left = 5, for example.
//        This will signal the onMoved() event if it actually moved.
//
//////
	void iObj_setSize(SThisCode* thisCode, SObject* obj, s32 tnLeft, s32 tnTop, s32 tnWidth, s32 tnHeight)
	{
		s32			lnAlignment, lnBorderStyle, lnLeft, lnTop;
		bool		llTitleBar, llBorder;
		SObject*	objChild;
		SBitmap*	bmp;
		RECT		lrc, lrco, lrcDeltas;


		// Resize if need be (32-bit bitmap for labels, 24-bit for everything else)
		logfunc(__FUNCTION__);
		if (!obj)
			return;

		// If it's a toolbar, the size they dictate may not be the final size
		if (obj->objType == _OBJ_TYPE_TOOLBAR)
			iiObj_setSize_snapForToolbar(thisCode, obj, &tnWidth, &tnHeight);	// Determine the real size requirement for the toolbar given this "proposed" width

		// Note the original locations
		CopyRect(&lrco, &obj->rc);

		// Delete the current buffer if the size has changed
		if (obj->bmp && (obj->bmp->bi.biWidth != tnWidth || obj->bmp->bi.biHeight != tnHeight))
			iBmp_delete(&obj->bmp, true, true);

		// Delete any prior rendered buffers, and any scaled buffers
		if (obj->bmpPriorRendered)			iBmp_delete(&obj->bmpPriorRendered,		true, true);
		if (obj->bmpScaled)					iBmp_delete(&obj->bmpScaled,			true, true);

		// Position and size its rectangle
		SetRect(&obj->rc,			tnLeft, tnTop, tnLeft + tnWidth, tnTop + tnHeight);
		CopyRect(&obj->rcClient,	&obj->rc);

		// Update the client area
		switch (obj->objType)
		{
			case _OBJ_TYPE_EMPTY:
				// Just use the default rcClient settings above
				break;



			case _OBJ_TYPE_FORM:
				// The client portion of a form is inset so as to allow for the border
				llTitleBar		= propTitleBar(obj);
				lnBorderStyle	= propBorderStyle(obj);
				if (llTitleBar)
				{
					// It has a title bar
					SetRect(&obj->rcClient,
								8,
								bmpArrowUl->bi.biHeight + 2,
								tnWidth - bmpArrowUl->bi.biHeight - 2,
								tnHeight - bmpArrowUl->bi.biHeight - 1);

				} else {
					// No title bar
					switch (lnBorderStyle)
					{
						case _BORDER_STYLE_NONE:
							SetRect(&obj->rcClient,
										0,
										0,
										tnWidth,
										tnHeight);
							break;

						case _BORDER_STYLE_OUTLINE:
							SetRect(&obj->rcClient,
										2,
										2,
										tnWidth - 2,
										tnHeight - 2);
							break;

						case _BORDER_STYLE_FIXED:
							SetRect(&obj->rcClient,
										8,
										8,
										tnWidth - 8,
										tnHeight - 8);
							break;

						case _BORDER_STYLE_SIZABLE:
						default:
							SetRect(&obj->rcClient,
										8,
										bmpArrowUl->bi.biHeight + 2,
										tnWidth - bmpArrowUl->bi.biHeight - 2,
										tnHeight - bmpArrowUl->bi.biHeight - 1);
					}
				}


				//////////
				// Default child settings:
				// [icon][caption                     ][move][minimize][maximize][close]
				//////
					objChild = obj->firstChild;
					while (objChild)
					{
						// See which object this is
						if (objChild->objType == _OBJ_TYPE_IMAGE && propIsName_byText(objChild, cgcName_icon))
						{
							logfunc("form icon");
							// Form icon
							SetRect(&objChild->rc,
										bmpArrowUl->bi.biWidth + 4 - obj->rcClient.left,
										1 - obj->rcClient.top,
										bmpArrowUl->bi.biWidth + 4 - obj->rcClient.left + bmpArrowUl->bi.biWidth,
										1 + bmpArrowUl->bi.biHeight - obj->rcClient.top);

							// Update the size
							iObj_setSize(thisCode, objChild, objChild->rc.left, objChild->rc.top, objChild->rc.right - objChild->rc.left, objChild->rc.bottom - objChild->rc.top);


						} else if (objChild->objType == _OBJ_TYPE_LABEL && propIsName_byText(objChild, cgcName_caption)) {
							// Caption
							logfunc("form caption");
							SetRect(&objChild->rc,
										bmpArrowUl->bi.biWidth + 4 + bmpArrowUl->bi.biWidth + 8 - obj->rcClient.left,
										2 - obj->rcClient.top,
										tnWidth - (5 * (bmpArrowUl->bi.biWidth + 2)) - obj->rcClient.left - 4,
										1 + bmpArrowUl->bi.biHeight - obj->rcClient.top);

							// Update the size
							iObj_setSize(thisCode, objChild, objChild->rc.left, objChild->rc.top, objChild->rc.right - objChild->rc.left, objChild->rc.bottom - objChild->rc.top);


						} else if (objChild->objType == _OBJ_TYPE_IMAGE && propIsName_byText(objChild, cgcName_iconMove)) {
							// Move icon
							logfunc("form move icon");
							SetRect(&objChild->rc,
										tnWidth - (5 * (bmpArrowUl->bi.biWidth + 2)) - obj->rcClient.left,
										1 - obj->rcClient.top,
										tnWidth - (5 * (bmpArrowUl->bi.biWidth + 2)) - obj->rcClient.left + bmpArrowUl->bi.biWidth,
										1 + bmpArrowUl->bi.biHeight - obj->rcClient.top);

							// Update the size
							iObj_setSize(thisCode, objChild, objChild->rc.left, objChild->rc.top, objChild->rc.right - objChild->rc.left, objChild->rc.bottom - objChild->rc.top);


						} else if (objChild->objType == _OBJ_TYPE_IMAGE && propIsName_byText(objChild, cgcName_iconMinimize)) {
							// Minimize icon
							logfunc("form minimize icon");
							SetRect(&objChild->rc,
										tnWidth - (4 * (bmpArrowUl->bi.biWidth + 2)) - obj->rcClient.left,
										1 - obj->rcClient.top,
										tnWidth - (4 * (bmpArrowUl->bi.biWidth + 2)) - obj->rcClient.left + bmpArrowUl->bi.biWidth,
										1 + bmpArrowUl->bi.biHeight - obj->rcClient.top);

							// Update the size
							iObj_setSize(thisCode, objChild, objChild->rc.left, objChild->rc.top, objChild->rc.right - objChild->rc.left, objChild->rc.bottom - objChild->rc.top);


						} else if (objChild->objType == _OBJ_TYPE_IMAGE && propIsName_byText(objChild, cgcName_iconMaximize)) {
							// Maximize icon
							logfunc("form maximize icon");
							SetRect(&objChild->rc,
										tnWidth - (3 * (bmpArrowUl->bi.biWidth + 2)) - obj->rcClient.left,
										1 - obj->rcClient.top,
										tnWidth - (3 * (bmpArrowUl->bi.biWidth + 2)) - obj->rcClient.left + bmpArrowUl->bi.biWidth,
										1 + bmpArrowUl->bi.biHeight - obj->rcClient.top);

							// Update the size
							iObj_setSize(thisCode, objChild, objChild->rc.left, objChild->rc.top, objChild->rc.right - objChild->rc.left, objChild->rc.bottom - objChild->rc.top);


						} else if (objChild->objType == _OBJ_TYPE_IMAGE && propIsName_byText(objChild, cgcName_iconClose)) {
							// Close icon
							logfunc("form close icon");
							SetRect(&objChild->rc,
										tnWidth - (2 * (bmpArrowUl->bi.biWidth + 2)) - obj->rcClient.left,
										1 - obj->rcClient.top,
										tnWidth - (2 * (bmpArrowUl->bi.biWidth + 2)) - obj->rcClient.left + bmpArrowUl->bi.biWidth,
										1 + bmpArrowUl->bi.biHeight - obj->rcClient.top);

							// Update the size
							iObj_setSize(thisCode, objChild, objChild->rc.left, objChild->rc.top, objChild->rc.right - objChild->rc.left, objChild->rc.bottom - objChild->rc.top);


						} else if (objChild->objType == _OBJ_TYPE_IMAGE && propIsName_byText(objChild, cgcName_iconScaleUl)) {
							// Upper left arrow
							logfunc("form ul scale");
							SetRect(&objChild->rc,
											1 - obj->rcClient.left,
											1 - obj->rcClient.top,
											1 + bmpArrowUl->bi.biWidth - obj->rcClient.left,
											1 + bmpArrowUl->bi.biHeight - obj->rcClient.top);

							// Update the size
							iObj_setSize(thisCode, objChild, objChild->rc.left, objChild->rc.top, objChild->rc.right - objChild->rc.left, objChild->rc.bottom - objChild->rc.top);


						} else if (objChild->objType == _OBJ_TYPE_IMAGE && propIsName_byText(objChild, cgcName_iconScaleUr)) {
							// Upper right arrow
							logfunc("form ur scale");
							SetRect(&objChild->rc,
											tnWidth - bmpArrowUr->bi.biWidth - obj->rcClient.left - 1,
											1 - obj->rcClient.top,
											tnWidth - obj->rcClient.left - 1,
											1 - obj->rcClient.top + bmpArrowUr->bi.biHeight);

							// Update the size
							iObj_setSize(thisCode, objChild, objChild->rc.left, objChild->rc.top, objChild->rc.right - objChild->rc.left, objChild->rc.bottom - objChild->rc.top);


						} else if (objChild->objType == _OBJ_TYPE_IMAGE && propIsName_byText(objChild, cgcName_iconScaleLr)) {
							// Lower right arrow
							logfunc("form lr scale");
							SetRect(&objChild->rc,
											tnWidth  - bmpArrowLr->bi.biWidth  - obj->rcClient.left - 1,
											tnHeight - bmpArrowLr->bi.biHeight - obj->rcClient.top - 1,
											tnWidth  - obj->rcClient.left - 1,
											tnHeight - obj->rcClient.top - 1);

							// Update the size
							iObj_setSize(thisCode, objChild, objChild->rc.left, objChild->rc.top, objChild->rc.right - objChild->rc.left, objChild->rc.bottom - objChild->rc.top);


						} else if (objChild->objType == _OBJ_TYPE_IMAGE && propIsName_byText(objChild, cgcName_iconScaleLl)) {
							// Lower left arrow
							logfunc("form ll scale");
							SetRect(&objChild->rc,
											1 - obj->rcClient.left,
											tnHeight - bmpArrowLl->bi.biHeight - obj->rcClient.top - 1,
											1 + bmpArrowUl->bi.biWidth - obj->rcClient.left,
											tnHeight - obj->rcClient.top - 1);

							// Update the size
							iObj_setSize(thisCode, objChild, objChild->rc.left, objChild->rc.top, objChild->rc.right - objChild->rc.left, objChild->rc.bottom - objChild->rc.top);
						}

						// Move to next object
						objChild = objChild->ll.nextObj;
					}
				break;



			case _OBJ_TYPE_SUBFORM:
				if (propBorderStyle(obj) != _BORDER_STYLE_NONE)		SetRect(&obj->rcClient, 1, bmpArrowUl->bi.biHeight + 1, tnWidth - 8 - 1, tnHeight - 1);
				else												SetRect(&obj->rcClient, 0, bmpArrowUl->bi.biHeight,     tnWidth - 8,     tnHeight);


				/////////
				// If it's _screen, we need to also setup _asciirows and _asciicols
				//////
					if (propIsName_byText(obj, cgcName_screen))
					{
						*varAsciiRows->value.data_s32	= (obj->rcClient.bottom - obj->rcClient.top) / obj->p.font->tm.tmHeight;
						*varAsciiCols->value.data_s32	= (obj->rcClient.right - obj->rcClient.left) / obj->p.font->tm.tmAveCharWidth;
					}


				//////////
				// Default child settings:
				// [icon][caption                     ]
				//////
					objChild = obj->firstChild;
					while (objChild)
					{
						// See which object this is
						if (objChild->objType == _OBJ_TYPE_IMAGE && propIsName_byText(objChild, cgcName_icon))
						{
							// Subform icon
							logfunc("subform icon");
							SetRect(&objChild->rc,
										1,
										1 - obj->rcClient.top,
										1 + bmpArrowUl->bi.biWidth,
										1 + bmpArrowUl->bi.biHeight - obj->rcClient.top);

							// Update the size
							iObj_setSize(thisCode, objChild, objChild->rc.left, objChild->rc.top, objChild->rc.right - objChild->rc.left, objChild->rc.bottom - objChild->rc.top);


						} else if (objChild->objType == _OBJ_TYPE_LABEL && propIsName_byText(objChild, cgcName_caption)) {
							// Caption
							logfunc("subform caption");
							SetRect(&objChild->rc,
										1 + bmpArrowUl->bi.biWidth + 4,
										2 - obj->rcClient.top,
										tnWidth - 4,
										2 - obj->rcClient.top + objChild->p.font->tm.tmHeight + 2);

							// Update the size
							iObj_setSize(thisCode,	objChild,
													objChild->rc.left,
													objChild->rc.top,
													objChild->rc.right  - objChild->rc.left,
													objChild->rc.bottom - objChild->rc.top);
						}

						// Move to next object
						objChild = objChild->ll.nextObj;
					}
				break;



			case _OBJ_TYPE_CAROUSEL:
				//////////
				// Adjust for the border if need be
				//////
					llBorder = (propBorderStyle(obj) != _BORDER_STYLE_NONE);
					if (llBorder)		SetRect(&obj->rcClient, 2, 2, tnWidth - 2, tnHeight - 2);
					else				SetRect(&obj->rcClient, 0, 0, tnWidth,     tnHeight);


				//////////
				// Adjust for title bar area
				//////
					llTitleBar = propTitleBar(obj);
					if (llTitleBar)
						obj->rcClient.top += bmpArrowUl->bi.biHeight;		// Adjusts down for the caption


				//////////
				// Adjust for the tabs placement
				//////
					lnLeft		= 0;
					lnTop		= 0;
					lnAlignment	= propAlignment(obj);
					switch (lnAlignment)
					{
						case _ALIGNMENT_LEFT:		// Tabs are at the left
							obj->rcClient.left		+= bmpArrowUl->bi.biWidth;
							lnLeft					= bmpArrowUl->bi.biWidth;
							break;

						case _ALIGNMENT_RIGHT:		// Tabs are at the right
							obj->rcClient.right		-= bmpArrowUl->bi.biWidth;
							break;

						case _ALIGNMENT_TOP:		// Tabs are at the top
							obj->rcClient.top		+= bmpArrowUl->bi.biWidth;
							lnTop					= bmpArrowUl->bi.biWidth;
							break;

						default:
						case _ALIGNMENT_BOTTOM:		// Tabs are at the bottom
							obj->rcClient.bottom	-= bmpArrowUl->bi.biWidth;
							break;
					}


				//////////
				// Make sure the coordinates remain valid
				//////
					obj->rcClient.bottom	= max(obj->rcClient.bottom,	obj->rcClient.top  + 1);
					obj->rcClient.right		= max(obj->rcClient.right,	obj->rcClient.left + 1);


				//////////
				// Default child settings:
				// [icon][caption                     ]
				//////
					objChild = obj->firstChild;
					while (objChild)
					{
						// See which object this is
						if (objChild->objType == _OBJ_TYPE_IMAGE && propIsName_byText(objChild, cgcName_icon))
						{
							// Carousel icon
							logfunc("carousel icon");
							if (llTitleBar)
							{
								// Make the content visible
								if (!propIsVisible(objChild))
									propSetVisible_fromBool(objChild, true);

								// Set the appropriate size
								SetRect(&objChild->rc,	obj->rcClient.left - lnLeft,
														obj->rcClient.top - bmpArrowUl->bi.biHeight - lnTop,
														obj->rcClient.left + bmpArrowUl->bi.biWidth - lnLeft,
														obj->rcClient.top - lnTop);

								// Update the size
								iObj_setSize(thisCode, objChild, objChild->rc.left, objChild->rc.top, objChild->rc.right - objChild->rc.left, objChild->rc.bottom - objChild->rc.top);

							} else {
								// Make this content invisible
								if (propIsVisible(objChild))
									propSetVisible_fromBool(objChild, false);
							}


						} else if (objChild->objType == _OBJ_TYPE_LABEL && propIsName_byText(objChild, cgcName_caption)) {
							// Caption
							logfunc("carousel caption");
							if (llTitleBar)
							{
								// Make the content visible
								if (!propIsVisible(objChild))
									propSetVisible_fromBool(objChild, true);

								// Set the appropriate size
								SetRect(&objChild->rc,	obj->rcClient.left + bmpArrowUl->bi.biWidth + 4 - lnLeft,
														obj->rcClient.top - bmpArrowUl->bi.biHeight - lnTop,
														obj->rcClient.right - 4 - (2 * bmpArrowUl->bi.biWidth) - lnLeft,
														obj->rcClient.top - lnTop);

								// Update the size
								iObj_setSize(thisCode, objChild, objChild->rc.left, objChild->rc.top, objChild->rc.right - objChild->rc.left, objChild->rc.bottom - objChild->rc.top);

							} else {
								// Make this content invisible
								if (propIsVisible(objChild))
									propSetVisible_fromBool(objChild, false);
							}


						} else if (objChild->objType == _OBJ_TYPE_IMAGE && propIsName_byText(objChild, cgcName_iconCarousel)) {
							// Tabs/carousel icon
							logfunc("carousel icon button");
							if (llTitleBar)
							{
								// Make the content visible
								if (!propIsVisible(objChild))
									propSetVisible_fromBool(objChild, true);

								// Set the appropriate size
								SetRect(&objChild->rc,	obj->rcClient.right - bmpArrowUl->bi.biWidth - bmpArrowUl->bi.biWidth,
														obj->rcClient.top - bmpArrowUl->bi.biHeight - lnTop,
														obj->rcClient.right - bmpArrowUl->bi.biWidth,
														obj->rcClient.top - lnTop);

								// Update the size
								iObj_setSize(thisCode, objChild, objChild->rc.left, objChild->rc.top, objChild->rc.right - objChild->rc.left, objChild->rc.bottom - objChild->rc.top);

							} else {
								// Make this content invisible
								if (propIsVisible(objChild))
									propSetVisible_fromBool(objChild, false);
							}


						} else if (objChild->objType == _OBJ_TYPE_IMAGE && propIsName_byText(objChild, cgcName_iconClose)) {
							// Close carousel image
							logfunc("carousel close");
							if (llTitleBar)
							{
								// Make the content visible
								if (!propIsVisible(objChild))
									propSetVisible_fromBool(objChild, true);

								// Set the appropriate size
								SetRect(&objChild->rc,	obj->rcClient.right - bmpArrowUl->bi.biWidth,
														obj->rcClient.top - bmpArrowUl->bi.biHeight - lnTop,
														obj->rcClient.right,
														obj->rcClient.top - lnTop);

								// Update the size
								iObj_setSize(thisCode, objChild, objChild->rc.left, objChild->rc.top, objChild->rc.right - objChild->rc.left, objChild->rc.bottom - objChild->rc.top);

							} else {
								// Make this content invisible
								if (propIsVisible(objChild))
									propSetVisible_fromBool(objChild, false);
							}


						} else if (objChild->objType == _OBJ_TYPE_RIDER) {
							// Set the rider size
							CopyRect(&objChild->rc,	&obj->rcClient);

							// Update the size
							iObj_setSize(thisCode, objChild, objChild->rc.left, objChild->rc.top, objChild->rc.right - objChild->rc.left, objChild->rc.bottom - objChild->rc.top);
						}

						// Move to next object
						objChild = objChild->ll.nextObj;
					}
				break;

				break;

			case _OBJ_TYPE_RIDER:
				// Just use the default rcClient settings above
				break;

			case _OBJ_TYPE_LABEL:
			case _OBJ_TYPE_EDITBOX:
			case _OBJ_TYPE_IMAGE:
			case _OBJ_TYPE_BUTTON:
				// Just use the default rcClient settings above
				break;

			case _OBJ_TYPE_TEXTBOX:
				// Just use the default rcClient settings above
				break;

			case _OBJ_TYPE_CHECKBOX:
				//////////
				// Default child settings
				// [check][label]
				//////
					SetRect(&lrc, 0, 0, tnHeight, tnHeight);
					lnAlignment	= propAlignment(obj);
					objChild	= obj->firstChild;
					while (objChild)
					{
						// See which object this is
						if (objChild->objType == _OBJ_TYPE_IMAGE && propIsName_byText(objChild, cgcName_checkboxImage))
						{
							// Adjust the size and position
							logfunc("checkbox image");
							switch (lnAlignment)
							{
								default:
								case _ALIGNMENT_LEFT:
									iObj_setSize(thisCode, objChild, 0, 0, tnHeight, tnHeight);
									break;

								case _ALIGNMENT_RIGHT:
									iObj_setSize(thisCode, objChild, obj->rc.right - tnHeight, 0, obj->rc.right - obj->rc.left - tnHeight, tnHeight);
									break;
							}

							// Checkbox image
							bmp = iBmp_allocate();
							iBmp_createBySize(bmp, tnHeight, tnHeight, 24);

							// Based on type, populate the image
							if (iObjProp_get_s32_direct(thisCode, obj, _INDEX_VALUE) == 0)
							{
								// Off
								iBmp_scale(bmp, bmpCheckboxOff);		// Set the new

							} else {
								// On
								iBmp_scale(bmp, bmpCheckboxOn);			// Set the new
							}

							// Populate the standard image
							iObjProp_set_bitmap_direct(thisCode, obj, _INDEX_PICTUREBMP,		bmp);
							iObjProp_set_bitmap_direct(thisCode, obj, _INDEX_PICTUREBMP_DOWN,	bmp);
							iObjProp_set_bitmap_direct(thisCode, obj, _INDEX_PICTUREBMP_OVER,	bmp);

							// Delete our template
							iBmp_delete(&bmp, true, true);

							// Add highlighting for the over and down
							bmp = iObjProp_get_bitmap(thisCode, obj, _INDEX_PICTUREBMP_OVER);			iBmp_colorize(bmp, &lrc, colorMouseOver, false, 0.5f);
							bmp = iObjProp_get_bitmap(thisCode, obj, _INDEX_PICTUREBMP_DOWN);			iBmp_colorize(bmp, &lrc, colorMouseDown, false, 0.5f);

							// Mark it for re-render
							objChild->isDirtyRender = true;

						} else if (objChild->objType == _OBJ_TYPE_LABEL && propIsName_byText(objChild, cgcName_checkboxLabel)) {
							// Adjust the size
							logfunc("checkbox label");
							switch (propAlignment(obj))
							{
								default:
								case _ALIGNMENT_LEFT:
									iObj_setSize(thisCode, objChild, tnHeight, 0, obj->rc.right - obj->rc.left - tnHeight, tnHeight);
									break;

								case _ALIGNMENT_RIGHT:
									iObj_setSize(thisCode, objChild, 0, 0, obj->rc.right - obj->rc.left - tnHeight, tnHeight);
									break;
							}

							// Mark it for re-render
							objChild->isDirtyRender = true;
						}

						// Move to next object
						objChild = objChild->ll.nextObj;
					}
				break;

			case _OBJ_TYPE_OPTION:
				// Just use the default rcClient settings above
				break;

			case _OBJ_TYPE_RADIO:
				// Just use the default rcClient settings above
				break;

			case _OBJ_TYPE_TOOLBAR:
				// Arrange all items within so they fit horizontally until the width is reached, then begin down below
				break;
		}


		//////////
		// Signal any needed events for this change
		//////
			if (memcmp(&lrco, &obj->rc, sizeof(lrco)) != 0)
			{

				//////////
				// Something has changed
				//////
					// Position?
					if (lrco.left != obj->rc.left || lrco.top != obj->rc.top)
						iEngine_raise_event(thisCode, _EVENT_ONMOVED, ((thisCode) ? thisCode->win : NULL), obj, &obj->rc);

					// Size?
					if (lrco.right - lrco.left != obj->rc.right - obj->rc.left || lrco.bottom - lrco.top != obj->rc.bottom - obj->rc.top)
						iEngine_raise_event(thisCode, _EVENT_ONRESIZE, ((thisCode) ? thisCode->win : NULL), obj, iiMath_computeRectDeltas(&lrcDeltas, &lrco, &obj->rc));
			}


// TODO:  We need to see if there are any left_assign(), top_assign(), width_assign(), or height_assign() custom methods defined


		//////////
		// Mark it dirty for a full re-render
		//////
			obj->isDirtyRender = true;
	}




//////////
//
// Snap to the smallest width encountered which accommodates the child items contained within,
// and auto-adjust the height to the appropriate height.
//
//////
	void iiObj_setSize_snapForToolbar(SThisCode* thisCode, SObject* obj, s32* tnWidth, s32* tnHeight)
	{
		s32			lnI, lnMargin, lnMaxWidth, lnMaxHeight, lnWidth, lnHeight, lnNewX, lnNewY, lnRowWidth, lnRowHeight;
		bool		llAtLeastOne;
		SObject*	objChild;


		//////////
		// Initialize
		//////
			lnMaxWidth	= 0;		// Overall maximum width encountered
			lnMaxHeight	= 0;		// Overall maximum height encountered
			lnRowWidth	= 0;		// Building row width
			lnRowHeight	= 0;		// Building row height


		//////////
		// Iterate through every child, fitting them where they will fit
		//////
			lnMargin = propMargin(obj);		// Spacing between toolbar items
			for (objChild = obj->firstChild, llAtLeastOne = false, lnI = 0; objChild; objChild = objChild->ll.nextObj, llAtLeastOne = true, lnI++)
			{
				//////////
				// Grab our size for this one
				//////
					lnWidth		= objChild->rc.right - objChild->rc.left;
					lnHeight	= objChild->rc.bottom - objChild->rc.top;
					lnRowHeight	= max(lnHeight,	lnRowHeight);


				//////////
				// Coordinate for the new object (if we're not over width)
				//////
					lnNewX	= lnRowWidth + ((lnRowWidth != 0) ? lnMargin : 0);
					lnNewY	= lnMaxHeight;


				//////////
				// Are we off the reservation?
				//////
					if (lnNewX + lnWidth > *tnWidth)
					{
						// This will be too big for our width
						// Move down for the start of the next row
						lnMaxHeight += lnRowHeight + ((lnMaxHeight != 0) ? lnMargin : 0);

						// No, so we need to move to this item to the start of the next row
						lnNewX		= 0;
						lnNewY		= lnMaxHeight;
						lnRowWidth	= lnWidth;
						lnRowHeight = lnHeight;

					} else {
						// We're continuing across this row
						lnRowWidth += lnWidth;
					}


				//////////
				// Observe our width extent thus far
				//////
					lnMaxWidth	= max(max(lnNewX, lnMaxWidth), lnRowWidth);
					lnMaxHeight	= max(lnNewY, lnMaxHeight);


				//////////
				// Position this child object at its new location
				//////
					iObj_setSize(thisCode, objChild, obj->rc.left + lnNewX, obj->rc.top + lnNewY, lnWidth, lnHeight);
			}


		//////////
		// Store our extents as the snap values
		//////
			if (llAtLeastOne)
			{
				*tnWidth	= lnMaxWidth;
				*tnHeight	= lnMaxHeight + lnRowHeight;
			}
	}




//////////
//
// Called to create the Windows-side window for the form.  The normal bit buffer is
// rendered regardless of whether or not the form is presented outwardly.  It can be
// used as an off-screen buffer in that way.
//
//////
	SWindow* iObj_createWindowForForm(SThisCode* thisCode, SObject* obj_form, SWindow* winReuse, s32 icon)
	{
		SWindow* winNew;


		// Make sure our environment is sane
		logfunc(__FUNCTION__);
		winNew = NULL;
		if (obj_form)
			winNew = iWindow_createForObject(thisCode, obj_form, winReuse, icon);

		// Indicate our status
		return(winNew);
	}




//////////
//
// Searches the indicated object for the indicated property
//
//////
	SVariable* iObj_getPropertyAsVariable(SThisCode* thisCode, SObject* obj, s8* tcPropertyName, u32 tnPropertyNameLength, SComp* comp, bool tlCreateAsReference)
	{
		SBaseClassMap*	lbcl;
		SObjPropMap*	lpm;


		// Make sure our environment is sane
		logfunc(__FUNCTION__);
		if (obj)
		{
			// Find out our property interface
			lbcl = iiObj_getBaseclass_byType(thisCode, obj->objType);
			if (lbcl)
			{
				// Search through the properties
				lpm = lbcl->objProps;
				while (lpm && gsProps_master[lpm->index].propName_u8)
				{
					// Is this the name?
					if (gsProps_master[lpm->index].propNameLength == tnPropertyNameLength && _memicmp(tcPropertyName, gsProps_master[lpm->index].propName_u8, tnPropertyNameLength) == 0)
						return(iVariable_copy(thisCode, obj->props[lpm->index], tlCreateAsReference));

					// Move to next property
					++lpm;
				}
				// If we get here, we didn't find it on the object
			}
		}
		// If we get here, wasn't found
		return(NULL);
	}




//////////
//
// Called to reset the object's properties to their default values.
// Only an internal function, and only used during initialization.
// After that the main gobj_default* objects are used for creating
// all default base class objects thereafter.
//
//////
	void iiObj_resetToDefault(SThisCode* thisCode, SObject* obj, bool tlResetProperties, bool tlResetMethods)
	{
		// Make sure our environment is sane
		logfunc(__FUNCTION__);
		if (obj)
		{
			// Update the sub-object data
			switch (obj->objType)
			{
				case _OBJ_TYPE_EMPTY:		// Empty, used as a placeholder object that is not drawn
					iiSubobj_resetToDefaultEmpty(thisCode, obj, tlResetProperties, tlResetMethods, &gsProps_empty[0], gnProps_emptySize, &gsEvents_empty[0], gnEvents_emptySize);
					break;

				case _OBJ_TYPE_FORM:			// Form class, the main outer window the OS sees
					iiSubobj_resetToDefaultForm(thisCode, obj, tlResetProperties, tlResetMethods, &gsProps_form[0], gnProps_formSize, &gsEvents_form[0], gnEvents_formSize);
					break;

				case _OBJ_TYPE_SUBFORM:		// A new class which has its own drawing content and can be moved about using UI features
					iiSubobj_resetToDefaultSubform(thisCode, obj, tlResetProperties, tlResetMethods, &gsProps_subform[0], gnProps_subformSize, &gsEvents_subform[0], gnEvents_subformSize);
					break;

				case _OBJ_TYPE_LABEL:		// A label
					iiSubobj_resetToDefaultLabel(thisCode, obj, tlResetProperties, tlResetMethods, &gsProps_label[0], gnProps_labelSize, &gsEvents_label[0], gnEvents_labelSize);
					break;

				case _OBJ_TYPE_TEXTBOX:		// An input textbox
					iiSubobj_resetToDefaultTextbox(thisCode, obj, tlResetProperties, tlResetMethods, &gsProps_textbox[0], gnProps_textboxSize, &gsEvents_textbox[0], gnEvents_textboxSize);
					break;

				case _OBJ_TYPE_BUTTON:		// A push button
					iiSubobj_resetToDefaultButton(thisCode, obj, tlResetProperties, tlResetMethods, &gsProps_button[0], gnProps_buttonSize, &gsEvents_button[0], gnEvents_buttonSize);
					break;

				case _OBJ_TYPE_EDITBOX:		// An input multi-line editbox
					iiSubobj_resetToDefaultEditbox(thisCode, obj, tlResetProperties, tlResetMethods, &gsProps_editbox[0], gnProps_editboxSize, &gsEvents_editbox[0], gnEvents_editboxSize);
					break;

				case _OBJ_TYPE_IMAGE:		// A graphical image
					iiSubobj_resetToDefaultImage(thisCode, obj, tlResetProperties, tlResetMethods, &gsProps_image[0], gnProps_imageSize, &gsEvents_image[0], gnEvents_imageSize);
					break;

				case _OBJ_TYPE_CHECKBOX:		// A checkbox
					iiSubobj_resetToDefaultCheckbox(thisCode, obj, tlResetProperties, tlResetMethods, &gsProps_checkbox[0], gnProps_checkboxSize, &gsEvents_checkbox[0], gnEvents_checkboxSize);
					break;

				case _OBJ_TYPE_OPTION:		// A combination selection
					iiSubobj_resetToDefaultOption(thisCode, obj, tlResetProperties, tlResetMethods, &gsProps_option[0], gnProps_optionSize, &gsEvents_option[0], gnEvents_optionSize);
					break;

				case _OBJ_TYPE_RADIO:		// A radio dial, which can also present as a slider or spinner
					iiSubobj_resetToDefaultRadio(thisCode, obj, tlResetProperties, tlResetMethods, &gsProps_radio[0], gnProps_radioSize, &gsEvents_radio[0], gnEvents_radioSize);
					break;

				case _OBJ_TYPE_CMDGROUP:	// A command button group
					iiSubobj_resetToDefaultCmdGroup(thisCode, obj, tlResetProperties, tlResetMethods, &gsProps_cmdgroup[0], gnProps_cmdgroupSize, &gsEvents_cmdgroup[0], gnEvents_cmdgroupSize);
					break;

				case _OBJ_TYPE_OPTGROUP:	// An option group
					iiSubobj_resetToDefaultOptGroup(thisCode, obj, tlResetProperties, tlResetMethods, &gsProps_optgroup[0], gnProps_optgroupSize, &gsEvents_optgroup[0], gnEvents_optgroupSize);
					break;

				case _OBJ_TYPE_LISTBOX:		// A listbox
					iiSubobj_resetToDefaultListbox(thisCode, obj, tlResetProperties, tlResetMethods, &gsProps_listbox[0], gnProps_listboxSize, &gsEvents_listbox[0], gnEvents_listboxSize);
					break;

				case _OBJ_TYPE_COMBOBOX:	// A combobox
					iiSubobj_resetToDefaultCombobox(thisCode, obj, tlResetProperties, tlResetMethods, &gsProps_combobox[0], gnProps_comboboxSize, &gsEvents_combobox[0], gnEvents_comboboxSize);
					break;

				case _OBJ_TYPE_FORMSET:		// A formset
					iiSubobj_resetToDefaultFormset(thisCode, obj, tlResetProperties, tlResetMethods, &gsProps_formset[0], gnProps_formsetSize, &gsEvents_formset[0], gnEvents_formsetSize);
					break;

				case _OBJ_TYPE_TOOLBAR:		// A toolbar
					iiSubobj_resetToDefaultToolbar(thisCode, obj, tlResetProperties, tlResetMethods, &gsProps_toolbar[0], gnProps_toolbarSize, &gsEvents_toolbar[0], gnEvents_toolbarSize);
					break;

				case _OBJ_TYPE_SEPARATOR:	// A separator
					iiSubobj_resetToDefaultSeparator(thisCode, obj, tlResetProperties, tlResetMethods, &gsProps_separator[0], gnProps_separatorSize, &gsEvents_separator[0], gnEvents_separatorSize);
					break;

				case _OBJ_TYPE_LINE:		// A line
					iiSubobj_resetToDefaultLine(thisCode, obj, tlResetProperties, tlResetMethods, &gsProps_line[0], gnProps_lineSize, &gsEvents_line[0], gnEvents_lineSize);
					break;

				case _OBJ_TYPE_SHAPE:		// A shape
					iiSubobj_resetToDefaultShape(thisCode, obj, tlResetProperties, tlResetMethods, &gsProps_shape[0], gnProps_shapeSize, &gsEvents_shape[0], gnEvents_shapeSize);
					break;

				case _OBJ_TYPE_CONTAINER:	// A container
					iiSubobj_resetToDefaultContainer(thisCode, obj, tlResetProperties, tlResetMethods, &gsProps_container[0], gnProps_containerSize, &gsEvents_container[0], gnEvents_containerSize);
					break;

				case _OBJ_TYPE_CONTROL:		// A blocking container
					iiSubobj_resetToDefaultControl(thisCode, obj, tlResetProperties, tlResetMethods, &gsProps_control[0], gnProps_controlSize, &gsEvents_control[0], gnEvents_controlSize);
					break;

				case _OBJ_TYPE_GRID:		// A grid
					iiSubobj_resetToDefaultGrid(thisCode, obj, tlResetProperties, tlResetMethods, &gsProps_grid[0], gnProps_gridSize, &gsEvents_grid[0], gnEvents_gridSize);
					break;

				case _OBJ_TYPE_COLUMN:		// A grid's column object
					iiSubobj_resetToDefaultColumn(thisCode, obj, tlResetProperties, tlResetMethods, &gsProps_column[0], gnProps_columnSize, &gsEvents_column[0], gnEvents_columnSize);
					break;

				case _OBJ_TYPE_HEADER:		// A grid's header object
					iiSubobj_resetToDefaultHeader(thisCode, obj, tlResetProperties, tlResetMethods, &gsProps_header[0], gnProps_headerSize, &gsEvents_header[0], gnEvents_headerSize);
					break;

				case _OBJ_TYPE_OLEBOUND:	// A bound OLE object
					iiSubobj_resetToDefaultOleBound(thisCode, obj, tlResetProperties, tlResetMethods, &gsProps_olebound[0], gnProps_oleboundSize, &gsEvents_olebound[0], gnEvents_oleboundSize);
					break;

				case _OBJ_TYPE_OLECONTAIN:	// An OLE container control object
					iiSubobj_resetToDefaultOleContain(thisCode, obj, tlResetProperties, tlResetMethods, &gsProps_olecontain[0], gnProps_olecontainSize, &gsEvents_olecontain[0], gnEvents_olecontainSize);
					break;

				case _OBJ_TYPE_SPINNER:		// A spinner
					iiSubobj_resetToDefaultOleContain(thisCode, obj, tlResetProperties, tlResetMethods, &gsProps_olecontain[0], gnProps_olecontainSize, &gsEvents_olecontain[0], gnEvents_olecontainSize);
					break;

				case _OBJ_TYPE_TIMER:		// A timer
					iiSubobj_resetToDefaultTimer(thisCode, obj, tlResetProperties, tlResetMethods, &gsProps_timer[0], gnProps_timerSize, &gsEvents_timer[0], gnEvents_timerSize);
					break;

				case _OBJ_TYPE_HYPERLINK:	// A hyperlink
					iiSubobj_resetToDefaultHyperlink(thisCode, obj, tlResetProperties, tlResetMethods, &gsProps_hyperlink[0], gnProps_hyperlinkSize, &gsEvents_hyperlink[0], gnEvents_hyperlinkSize);
					break;

				case _OBJ_TYPE_COLLECTION:	// A collection
					iiSubobj_resetToDefaultCollection(thisCode, obj, tlResetProperties, tlResetMethods, &gsProps_collection[0], gnProps_collectionSize, &gsEvents_collection[0], gnEvents_collectionSize);
					break;

				case _OBJ_TYPE_PAGE:		// A page within a pageframe
					iiSubobj_resetToDefaultPage(thisCode, obj, tlResetProperties, tlResetMethods, &gsProps_page[0], gnProps_pageSize, &gsEvents_page[0], gnEvents_pageSize);
					break;

				case _OBJ_TYPE_PAGEFRAME:	// A pageframe
					iiSubobj_resetToDefaultPageframe(thisCode, obj, tlResetProperties, tlResetMethods, &gsProps_pageframe[0], gnProps_pageframeSize, &gsEvents_pageframe[0], gnEvents_pageframeSize);
					break;

				case _OBJ_TYPE_SESSION:		// A session
					iiSubobj_resetToDefaultSession(thisCode, obj, tlResetProperties, tlResetMethods, &gsProps_session[0], gnProps_sessionSize, &gsEvents_session[0], gnEvents_sessionSize);
					break;

				case _OBJ_TYPE_CUSTOM:		// A custom class
					iiSubobj_resetToDefaultCustom(thisCode, obj, tlResetProperties, tlResetMethods, &gsProps_custom[0], gnProps_customSize, &gsEvents_custom[0], gnEvents_customSize);
					break;

				case _OBJ_TYPE_EXCEPTION:	// An exception
					iiSubobj_resetToDefaultException(thisCode, obj, tlResetProperties, tlResetMethods, &gsProps_exception[0], gnProps_exceptionSize, &gsEvents_exception[0], gnEvents_exceptionSize);
					break;

				case _OBJ_TYPE_SETTINGS:	// Settings (SET TALK ON, etc.)
					iiSubobj_resetToDefaultSettings(thisCode, obj, tlResetProperties, tlResetMethods, &gsProps_settings[0], gnProps_settingsSize, &gsEvents_settings[0], gnEvents_settingsSize);
					break;

				default:
// TODO:  We should never get here... we should fire off an internal consistency error
					break;
			}
		}
	}




//////////
//
// Resets common object properties to their defaults.
//
//////
	void iiObj_resetToDefaultCommon(SThisCode* thisCode, SObject* obj, bool tlResetProperties, bool tlResetMethods, SObjPropMap* propMap, s32 tnPropCount, SObjEventMap* eventList, u32 tnEventCount)
	{
		s32 lnI, lnIndex, lnAllocationSize;


		logfunc(__FUNCTION__);

		//////////
		// Make sure the properties are allocated
		//////
			if (!obj->props)
			{

				// Allocate
				lnAllocationSize	= tnPropCount * sizeof(SVariable*);
				obj->props			= (SVariable**)malloc(lnAllocationSize);
				if (!obj->props)
				{
					// Out of memory
					debug_break;
					return;
				}

				// Initialize
				memset(obj->props, 0, lnAllocationSize);
				obj->propsCount = tnPropCount;

			}


		//////////
		// Set properties
		//////
			for (lnI = 0; lnI < tnPropCount; lnI++)
			{

				//////////
				// Grab the index of this entry in the master list
				//////
					lnIndex = propMap[lnI].index;


				//////////
				// Delete the old variable
				//////
					if (obj->props[lnI])
					{
						iVariable_delete(thisCode, obj->props[lnI], true);
						obj->props[lnI] = NULL;
					}


				//////////
				// Create the base variable based on the master init variable created at startup and set its property name
				//////
// if (lnIndex == 235 || lnIndex == 234 || lnIndex == 233)
// 	debug_break;
					obj->props[lnI] = iVariable_copy(thisCode, gsProps_master[lnIndex - 1].varInit, false);

// Should never happen
// This usually means a property was added to a gsProps_class, but not to the full gsProps_master
// See accessors.h for this lnIndex property number
if (!obj->props[lnI])
	debug_break;
					// Set its name
					iVariable_setName(thisCode, obj->props[lnI], gsProps_master[lnIndex - 1].propName_u8, gsProps_master[lnIndex - 1].propNameLength);


				//////////
				// Perform any base class initialization
				//////
					if (gsProps_master[lnIndex - 1]._initterBase)
						gsProps_master[lnIndex - 1].initterBase(thisCode, obj, lnIndex);


				//////////
				// Finalize the initialization with any additional steps specific to the object
				//////
					if (propMap[lnI]._initterObject)
						propMap[lnI].initterObject(thisCode, obj, lnIndex);

			}


		//////////
		// Related to rendering
		//////
			obj->isRendered		= true;
			obj->isPublished	= true;
			obj->isDirtyRender	= true;
			obj->isDirtyPublish	= true;


		//////////
		// Any dynamic properties within
		//////
			if (tlResetProperties)
				iVariable_politelyDelete_chain(thisCode, &obj->firstProperty, true);


		//////////
		// Any methods defined
		//////
			if (tlResetMethods)
				iFunction_politelyDelete_chain(thisCode, &obj->firstMethod, true);


		//////////
		// Events
		//////
			iEvents_resetToDefault(thisCode, obj, eventList, tnEventCount);


		//////////
		// Remove any prior renderings, and reset render parameters
		//////
			iBmp_delete(&obj->bmp, true, true);
			iBmp_delete(&obj->bmpPriorRendered, true, true);
			iBmp_delete(&obj->bmpScaled, true, true);

			obj->scrollOffsetX	= 0;
			obj->scrollOffsetY	= 0;
			obj->isScaled		= false;
	}




//////////
//
// Called to translate the text-based class name to its internal object type.
//
//////
	s32 iiObj_getBaseclassType_byName(SThisCode* thisCode, s8* tcTextname, s32 tnTextnameLength)
	{
		s32 lnI;


		// Iterate through each function for matches
		logfunc(__FUNCTION__);
		for (lnI = 0; gsKnownBaseclasses[lnI].objType != 0; lnI++)
		{
			// Is this the named function?
			if (gsKnownBaseclasses[lnI].baseclassNameLength == tnTextnameLength && _memicmp(tcTextname, (s8*)gsKnownBaseclasses[lnI].baseclassName, tnTextnameLength) == 0)
				return(gsKnownBaseclasses[lnI].objType);
		}
		// If we get here, not found
		return(0);
	}




//////////
//
// Called to translate the text-based class name to its internal object reference
//
//////
	SBaseClassMap* iiObj_getBaseclass_byName(SThisCode* thisCode, s8* tcTextname, s32 tnTextnameLength)
	{
		s32 lnI;


		// Iterate through each function for matches
		logfunc(__FUNCTION__);
		for (lnI = 0; gsKnownBaseclasses[lnI].objType != 0; lnI++)
		{
			// Is this the named function?
			if (gsKnownBaseclasses[lnI].baseclassNameLength == tnTextnameLength && _memicmp(tcTextname, (s8*)gsKnownBaseclasses[lnI].baseclassName, tnTextnameLength) == 0)
				return(&gsKnownBaseclasses[lnI]);
		}
		// If we get here, not found
		return(NULL);
	}





//////////
//
// Called to translate the class object type to its text-base name
//
//////
	SBaseClassMap* iiObj_getBaseclass_byType(SThisCode* thisCode, s32 tnObjType)
	{
		// Iterate through each function for matches
		logfunc(__FUNCTION__);
		if (tnObjType <= gnKnownBaseclasses_size)
			return(&gsKnownBaseclasses[tnObjType - 1]);

		// If we get here, invalid
		return(NULL);
	}
