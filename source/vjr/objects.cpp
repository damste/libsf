//////////
//
// /libsf/source/vjr/objects.cpp
//
//////
// Version 0.31
// Copyright (c) 2014 by Rick C. Hodgin
//////
// Last update:
//     Jun.14.2014
//////
// Change log:
//     Jun.14.2014 - Initial creation
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
//     http://www.visual-freepro.org/wiki/index.php/Repeat_License
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
	SObject* iObj_create(u32 objType, void* obj_data, SObject* objParent)
	{
		SObject* obj;


		//////////
		// Create the indicated item
		//////
			obj = (SObject*)malloc(sizeof(SObject));


		//////////
		// If successful, initialize it
		//////
			if (obj)
			{
				// Initialize
				memset(obj, 0, sizeof(SObject));

				// Initially populate
				obj->objType	= objType;
				obj->objParent	= objParent;

				// If they gave us a child, we'll use that
				if (obj_data)
				{
					// Whatever they handed off to us we assume
					obj->sub_obj = obj_data;

				} else {
					// We need to create it
					switch (objType)
					{
						case _OBJ_TYPE_EMPTY:		// Empty, used as a placeholder object that is not drawn
							iDatum_duplicate(&obj->name,		cgcName_empty, -1);
							iDatum_duplicate(&obj->className,	cgcName_empty, -1);
							obj->sub_obj = (void*)iSubobj_createEmpty(NULL, obj);
							break;

						case _OBJ_TYPE_FORM:			// Form class, the main outer window the OS sees
							iDatum_duplicate(&obj->name,		cgcName_form, -1);
							iDatum_duplicate(&obj->className,	cgcName_form, -1);
							obj->sub_obj = (void*)iSubobj_createForm(NULL, obj);
							break;

						case _OBJ_TYPE_SUBFORM:		// A new class which has its own drawing content and can be moved about using UI features
							iDatum_duplicate(&obj->name,		cgcName_subform, -1);
							iDatum_duplicate(&obj->className,	cgcName_subform, -1);
							obj->sub_obj = (void*)iSubobj_createSubform(NULL, obj);
							break;

						case _OBJ_TYPE_LABEL:		// A label
							iDatum_duplicate(&obj->name,		cgcName_label, -1);
							iDatum_duplicate(&obj->className,	cgcName_label, -1);
							obj->sub_obj = (void*)iSubobj_createLabel(NULL, obj);
							break;

						case _OBJ_TYPE_TEXTBOX:		// An input textbox
							iDatum_duplicate(&obj->name,		cgcName_textbox, -1);
							iDatum_duplicate(&obj->className,	cgcName_textbox, -1);
							obj->sub_obj = (void*)iSubobj_createTextbox(NULL, obj);
							break;

						case _OBJ_TYPE_BUTTON:		// A push button
							iDatum_duplicate(&obj->name,		cgcName_button, -1);
							iDatum_duplicate(&obj->className,	cgcName_button, -1);
							obj->sub_obj = (void*)iSubobj_createButton(NULL, obj);
							break;

						case _OBJ_TYPE_EDITBOX:		// An input multi-line editbox
							iDatum_duplicate(&obj->name,		cgcName_editbox, -1);
							iDatum_duplicate(&obj->className,	cgcName_editbox, -1);
							obj->sub_obj = (void*)iSubobj_createEditbox(NULL, obj);
							break;

						case _OBJ_TYPE_IMAGE:		// A graphical image
							iDatum_duplicate(&obj->name,		cgcName_image, -1);
							iDatum_duplicate(&obj->className,	cgcName_image, -1);
							obj->sub_obj = (void*)iSubobj_createImage(NULL, obj);
							break;

						case _OBJ_TYPE_CHECKBOX:		// A checkbox
							iDatum_duplicate(&obj->name,		cgcName_checkbox, -1);
							iDatum_duplicate(&obj->className,	cgcName_checkbox, -1);
							obj->sub_obj = (void*)iSubobj_createCheckbox(NULL, obj);
							break;

						case _OBJ_TYPE_OPTION:		// A combination selection
							iDatum_duplicate(&obj->name,		cgcName_option, -1);
							iDatum_duplicate(&obj->className,	cgcName_option, -1);
							obj->sub_obj = (void*)iSubobj_createOption(NULL, obj);
							break;

						case _OBJ_TYPE_RADIO:		// A radio dial, which can also present as a slider or spinner
							iDatum_duplicate(&obj->name,		cgcName_radio, -1);
							iDatum_duplicate(&obj->className,	cgcName_radio, -1);
							obj->sub_obj = (void*)iSubobj_createRadio(NULL, obj);
							break;

						default:
// TODO:  We should never get here... we should fire off an internal consistency error
							break;
					}

				}
			}


		//////////
		// Indicate our success or failure
		//////
			return(obj);
	}




//////////
//
// Called to create an object and append it to the
// indicated object as a child.
//
//////
//
// Returns:
//		SObject*		-- To new object which was added
//		sub_obj_output	-- Populated with the pointer of the sub-object
//
//////
	SObject* iObj_addChild(SObject* objParent, u32 objType, void** sub_obj_output)
	{
		SObject* objNew;


		// Make sure our environment is sane
		objNew = NULL;
		if (objParent)
		{
			// Create the new object using the default template
			objNew = iObj_create(objType, NULL, objParent);
			if (objNew)
			{
				// Append it to the child chain of the parent object
				iLl_appendExistingNodeAtBeginning((SLL**)&objParent->firstChild, (SLL*)objNew);
			}
		}

		// When we get here, it's there
		if (sub_obj_output)
			*sub_obj_output = ((objNew) ? objNew->sub_obj : NULL);

		// Indicate our status
		return(objNew);
	}




//////////
//
// Copy the indicated object
//
//////
	SObject* iObj_copy(SObject* template_obj, SObject* next, SObject* parent, bool tlCopyChildren, bool tlCopySubobjects, bool tlCreateSeparateBitmapBuffers)
	{
		SObject* obj;


		// Create the object
		obj = (SObject*)malloc(sizeof(SObject));
		if (obj)
		{
			//////////
			// Initialize the object
			//////
				memset(obj, 0, sizeof(SObject));


			//////////
			// Populate the object
			//////
				if (template_obj)
					memcpy(obj, template_obj, sizeof(SObject));		// Copy the existing object contents


			//////////
			// Update the next and parent, and clear out any bmpScaled
			//////
				obj->ll.next	= (SLL*)next;
				obj->objParent		= parent;
				obj->bmpScaled	= NULL;


			//////////
			// Copy the bitmap, subojects, and/or children (if need be)
			//////
				if (template_obj)
				{
					// Duplicate the bitmap buffer if need be
					if (tlCreateSeparateBitmapBuffers)
						obj->bmp = iBmp_copy(template_obj->bmp);

					// Copy subobject data
					if (tlCopySubobjects)
						obj->sub_obj = iObj_copySubobj(template_obj);

					// Copy children if need be
					if (tlCopyChildren && template_obj->firstChild)
						obj->firstChild = iObj_copy(template_obj->firstChild, NULL, obj, true, true, tlCreateSeparateBitmapBuffers);
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
	void iObj_delete(SObject** objRoot, bool tlDeleteSelf)
	{
		SObject* obj;


		// Make sure our environment is sane
		if (objRoot && *objRoot)
		{
			obj = *objRoot;
// TODO:  write this code
		}
	}




//////////
//
// Called to render the indicated object
//
//////
	u32 iObj_render(SObject* obj, bool tlRenderChildren, bool tlRenderSiblings)
	{
		u32 lnPixelsRendered;


		// Make sure our environment is sane
		lnPixelsRendered = 0;
		if (obj)
		{
			switch (obj->objType)
			{
				case _OBJ_TYPE_EMPTY:		// Empty, used as a placeholder object that is not drawn
					lnPixelsRendered += iSubobj_renderEmpty(obj, (SSubObjEmpty*)obj->sub_obj, tlRenderChildren, tlRenderSiblings);
					break;

				case _OBJ_TYPE_FORM:			// Form class, the main outer window the OS sees
					lnPixelsRendered += iSubobj_renderForm(obj, (SSubObjForm*)obj->sub_obj, tlRenderChildren, tlRenderSiblings);
					break;

				case _OBJ_TYPE_SUBFORM:		// A new class which has its own drawing content and can be moved about using UI features
					lnPixelsRendered += iSubobj_renderSubform(obj, (SSubObjSubform*)obj->sub_obj, tlRenderChildren, tlRenderSiblings);
					break;

				case _OBJ_TYPE_LABEL:		// A label
					lnPixelsRendered += iSubobj_renderLabel(obj, (SSubObjLabel*)obj->sub_obj, tlRenderChildren, tlRenderSiblings);
					break;

				case _OBJ_TYPE_TEXTBOX:		// An input textbox
					lnPixelsRendered += iSubobj_renderTextbox(obj, (SSubObjTextbox*)obj->sub_obj, tlRenderChildren, tlRenderSiblings);
					break;

				case _OBJ_TYPE_BUTTON:		// A push button
					lnPixelsRendered += iSubobj_renderButton(obj, (SSubObjButton*)obj->sub_obj, tlRenderChildren, tlRenderSiblings);
					break;

				case _OBJ_TYPE_EDITBOX:		// An input multi-line editbox
					lnPixelsRendered += iSubobj_renderEditbox(obj, (SSubObjEditbox*)obj->sub_obj, tlRenderChildren, tlRenderSiblings);
					break;

				case _OBJ_TYPE_IMAGE:		// A graphical image
					lnPixelsRendered += iSubobj_renderImage(obj, (SSubObjImage*)obj->sub_obj, tlRenderChildren, tlRenderSiblings);
					break;

				case _OBJ_TYPE_CHECKBOX:		// A checkbox
					lnPixelsRendered += iSubobj_renderCheckbox(obj, (SSubObjCheckbox*)obj->sub_obj, tlRenderChildren, tlRenderSiblings);
					break;

				case _OBJ_TYPE_OPTION:		// A combination selection
					lnPixelsRendered += iSubobj_renderOption(obj, (SSubObjOption*)obj->sub_obj, tlRenderChildren, tlRenderSiblings);
					break;

				case _OBJ_TYPE_RADIO:		// A radio dial, which can also present as a slider or spinner
					lnPixelsRendered += iSubobj_renderRadio(obj, (SSubObjRadio*)obj->sub_obj, tlRenderChildren, tlRenderSiblings);
					break;

				default:
// TODO:  We should never get here... we should fire off an internal consistency error
					break;
			}
		}

		// Indicate how many pixels were rendered
		return(lnPixelsRendered);
	}




//////////
//
// Called from subobjects to render any object children and sibling they may have based on flags
//
//////
	void iObj_renderChildrenAndSiblings(SObject* obj, bool tlRenderChildren, bool tlRenderSiblings)
	{
		SObject* objSib;


		//////////
		// Render any children
		//////
			if (tlRenderChildren && obj->firstChild)
				iObj_render(obj->firstChild, true, true);


		//////////
		// Render any siblings
		//////
			if (tlRenderSiblings && obj->ll.next)
			{
				objSib = (SObject*)obj->ll.next;
				while (objSib)
				{
					// Render this sibling
					iObj_render(objSib, true, true);

					// Move to next sibling
					objSib = (SObject*)objSib->ll.next;
				}
			}
	}





//////////
//
// Called to publish the indicated object, which takes the rendered bitmaps of all child objects
// and overlays them where they should be.
//
//////
	u32 iObj_publish(SBitmap* bmpDst, RECT* rc, SObject* obj, bool tlPublishChildren, bool tlPublishSiblings)
	{
		u32					lnWidth, lnHeight, lnPixelsRendered;
		RECT				lrc;
		SObject*			objSib;
		union {
			SSubObjForm*	form;
			SSubObjSubform*	subform;
		};


		// Make sure our environment is sane
		lnPixelsRendered = 0;
		if (obj && obj->bmp)
		{
			//////////
			// Determine the position within the parent's rectangle where this object will go
			//////
				if (obj->objParent)
				{
					// Adjust this item within the parent's rectangle
					SetRect(&lrc,	rc->left	+ obj->rc.left,
									rc->top		+ obj->rc.top,
									rc->left	+ obj->rc.right,
									rc->top		+ obj->rc.bottom);

				} else {
					// This is a top-level entry, so adjust everything to rcClient, or to 0
					switch (obj->objType)
					{
						case _OBJ_TYPE_FORM:
							// Bypass the frame
							form = (SSubObjForm*)obj->sub_obj;
							CopyRect(&lrc, &form->rcClient);
							break;

						case _OBJ_TYPE_SUBFORM:
							// Bypass the frame
							subform = (SSubObjSubform*)obj->sub_obj;
							CopyRect(&lrc, &subform->rcClient);
							break;

						default:
							// The object occupies its entire space
							SetRect(&lrc,	0,
											0,
											obj->rc.right - obj->rc.left,
											obj->rc.bottom -obj->rc.top);
					}
				}


			//////////
			// Publish any children
			//////
				if (tlPublishChildren && obj->firstChild)
					lnPixelsRendered += iObj_publish(obj->bmp, &lrc, obj->firstChild, true, true);


			//////////
			// Publish this item
			//////
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
					if (bmpDst)
						lnPixelsRendered += iBmp_bitBlt(bmpDst, &lrc, obj->bmpScaled);

				} else {
					// We can just copy
// s8 buffer[256];
// sprintf(buffer, "c:\\temp\\publish_obj%u.bmp\0", (u32)obj);
// iBmp_saveToDisk(obj->bmp, buffer);
					if (bmpDst)
						lnPixelsRendered += iBmp_bitBlt(bmpDst, &lrc, obj->bmp);
				}


			//////////
			// Publish any siblings
			//////
				if (tlPublishSiblings)
				{
					// Begin at the next sibling
					objSib = (SObject*)obj->ll.next;
					while (objSib)
					{
						// Render this sibling
						lnPixelsRendered += iObj_publish(bmpDst, rc, objSib, true, false);

						// Move to next sibling
						objSib = (SObject*)objSib->ll.next;
					}
				}
		}
// s8 buffer[256];
// sprintf(buffer, "c:\\temp\\publish_%u.bmp\0", (u32)obj);
// iBmp_saveToDisk(bmpDst, buffer);



		//////////
		// Indicate how many pixels were painted
		//////
			return(lnPixelsRendered);
	}




//////////
//
// Duplicate the chain of ObjectLabels, so the destination has a copy of each.
//
//////
	void iObj_duplicateChain(SObject** root, SObject* chain)
	{
		SObject*		obj;
		SObject**		oPrevPtr;
		void**			objDataPtr;


		// Create the master record
		if (root)
		{
			// Repeat adding as many entries as there are
			oPrevPtr = root;
			while (chain)
			{
				// Create this object
				obj = iObj_copy(chain, NULL, chain, true, true, true);
				if (obj)
				{
					// Update the duplicate object's forward pointer in the chain
					*oPrevPtr = obj;

					// Setup the next forward pointer
					oPrevPtr = (SObject**)&obj->ll.next;

					// Get the location of our sub-object update pointer
					objDataPtr = &obj->sub_obj;

					// Copy the sub-object
					obj->sub_obj = iObj_copySubobj(chain);
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
	void iObj_appendObjToParent(SObject* parent, SObject* obj)
	{
		// Make sure our environment is sane
		if (parent && obj)
			iLl_appendExistingNodeAtEnd((SLL**)&parent->firstChild, (SLL*)obj);
	}




//////////
//
// Called to duplicate the child objects to this object
//
//////
	void iObj_duplicateChildren(SObject* objDst, SObject* objSrc)
	{
		SObject*	objChild;
//		SObject*	objCopy;


		// Make sure our environment is sane
		if (objSrc && objSrc->firstChild)
		{
//_asm int 3;
			// Duplicate this entry
			objChild = objSrc->firstChild;
			while (objChild)
			{
				// Copy this item

				// Append any children here

				// Move to next
// TODO:  working here
				objChild = (SObject*)objChild->ll.next;
			}
		}
	}




//////////
//
// Called to set the object size
//
//////
	void iObj_setSize(SObject* obj, s32 tnLeft, s32 tnTop, s32 tnWidth, s32 tnHeight)
	{
		union {
			SSubObjForm*		form;
			SSubObjSubform*		subform;
		};

		// Resize if need be
		obj->bmp = iBmp_verifySizeOrResize(obj->bmp, tnWidth, tnHeight);

		// Position and size its rectangle
		SetRect(&obj->rc, tnLeft, tnTop, tnLeft + tnWidth, tnTop + tnHeight);

		// Update the client area
		switch (obj->objType)
		{
			case _OBJ_TYPE_EMPTY:
				break;

			case _OBJ_TYPE_FORM:
				form = (SSubObjForm*)obj->sub_obj;
				SetRect(&form->rcClient, 8, form->bmpFormIcon->bi.biHeight + 2, tnWidth - form->bmpFormIcon->bi.biHeight - 2, tnHeight - form->bmpFormIcon->bi.biHeight - 1);
				break;

			case _OBJ_TYPE_SUBFORM:
				subform = (SSubObjSubform*)obj->sub_obj;
				SetRect(&subform->rcClient, 0, subform->bmpSubformIcon->bi.biHeight, tnWidth - 8, tnHeight);
				break;

			case _OBJ_TYPE_LABEL:
				break;

			case _OBJ_TYPE_TEXTBOX:
				break;

			case _OBJ_TYPE_BUTTON:
				break;

			case _OBJ_TYPE_EDITBOX:
				break;

			case _OBJ_TYPE_IMAGE:
				break;

			case _OBJ_TYPE_CHECKBOX:
				break;

			case _OBJ_TYPE_OPTION:
				break;

			case _OBJ_TYPE_RADIO:
				break;
		}

		// Mark it dirty for a full re-render
		obj->isDirty = true;
	}




//////////
//
// Called to create the Windows-side window for the form.  The normal bit buffer is
// rendered regardless of whether or not the form is presented outwardly.  It can be
// used as an off-screen buffer in that way.
//
//////
	SWindow* iObj_createWindowForForm(SObject* obj_form, SWindow* win, s32 icon)
	{
		SWindow* winNew;


		// Make sure our environment is sane
		winNew = NULL;
		if (obj_form)
			winNew = iWindow_createForObject(obj_form, win, icon);

		// Indicate our status
		return(winNew);
	}




//////////
//
// Called to set the visible status of the indicated object.
// Returns the previous visible status.
//
//////
	bool iObj_setVisible(SObject* obj, bool tlNewVisible)
	{
		bool llOldVisible;


		// Make sure our environment is sane
		llOldVisible = false;
		if (obj)
		{
			llOldVisible	= obj->isVisible;
			obj->isVisible	= tlNewVisible;
		}

		// Indicate prior visible
		return(llOldVisible);
	}




//////////
//
// Called to copy the sub-object based on type
//
//////
	void* iObj_copySubobj(SObject* template_obj)
	{
		void* ptr;


		ptr = NULL;
		if (template_obj)
		{
			// Update the sub-object data
			switch (template_obj->objType)
			{
				case _OBJ_TYPE_EMPTY:		// Empty, used as a placeholder object that is not drawn
					ptr = (void*)iSubobj_createEmpty((SSubObjEmpty*)template_obj->sub_obj, template_obj);
					break;

				case _OBJ_TYPE_FORM:			// Form class, the main outer window the OS sees
					ptr = (void*)iSubobj_createForm((SSubObjForm*)template_obj->sub_obj, template_obj);
					break;

				case _OBJ_TYPE_SUBFORM:		// A new class which has its own drawing content and can be moved about using UI features
					ptr = (void*)iSubobj_createSubform((SSubObjSubform*)template_obj->sub_obj, template_obj);
					break;

				case _OBJ_TYPE_LABEL:		// A label
					ptr = (void*)iSubobj_createLabel((SSubObjLabel*)template_obj->sub_obj, template_obj);
					break;

				case _OBJ_TYPE_TEXTBOX:		// An input textbox
					ptr = (void*)iSubobj_createTextbox((SSubObjTextbox*)template_obj->sub_obj, template_obj);
					break;

				case _OBJ_TYPE_BUTTON:		// A push button
					ptr = (void*)iSubobj_createButton((SSubObjButton*)template_obj->sub_obj, template_obj);
					break;

				case _OBJ_TYPE_EDITBOX:		// An input multi-line editbox
					ptr = (void*)iSubobj_createEditbox((SSubObjEditbox*)template_obj->sub_obj, template_obj);
					break;

				case _OBJ_TYPE_IMAGE:		// A graphical image
					ptr = (void*)iSubobj_createImage((SSubObjImage*)template_obj->sub_obj, template_obj);
					break;

				case _OBJ_TYPE_CHECKBOX:		// A checkbox
					ptr = (void*)iSubobj_createCheckbox((SSubObjCheckbox*)template_obj->sub_obj, template_obj);
					break;

				case _OBJ_TYPE_OPTION:		// A combination selection
					ptr = (void*)iSubobj_createOption((SSubObjOption*)template_obj->sub_obj, template_obj);
					break;

				case _OBJ_TYPE_RADIO:		// A radio dial, which can also present as a slider or spinner
					ptr = (void*)iSubobj_createRadio((SSubObjRadio*)template_obj->sub_obj, template_obj);
					break;

				default:
// TODO:  We should never get here... we should fire off an internal consistency error
					break;
			}
		}

		// Indicate our success or failure
		return(ptr);
	}




//////////
//
// Searches the indicated object for the indicated property
//
//////
	SVariable* iObj_getPropertyAsVariable(SObject* obj, s8* tcPropertyName, u32 tnPropertyNameLength, SComp* comp)
	{
		SBaseclassList* lbcl;
		SPropertyList*	lpl;


		// Make sure our environment is sane
		if (obj)
		{
			// Find out our property interface
			lbcl = iiObj_getBaseclass_byType(obj->objType);
			if (lbcl)
			{
				// Search through the properties
				lpl = lbcl->objProps;
				while (lpl && lpl->textName)
				{
					// Is this the name?
					if (lpl->textNameLength == tnPropertyNameLength && _memicmp(tcPropertyName, lpl->textName, tnPropertyNameLength) == 0)
					{
						// This is the property, retrieve its value
						return(lpl->get(obj));
					}

					// Move to next property
					++lpl;
				}
				// If we get here, we didn't find it on the object

				// Search the sub-object
				lpl = lbcl->subobjProps;
				while (lpl && lpl->textName)
				{
					// Is this the name?
					if (lpl->textNameLength == tnPropertyNameLength && _memicmp(tcPropertyName, lpl->textName, tnPropertyNameLength) == 0)
					{
						// This is the property, retrieve its value
						return(lpl->get(obj));
					}

					// Move to next property
					++lpl;
				}
				// If we get here, it wasn't found
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
	void iiObj_resetToDefault(SObject* obj, bool tlResetProperties, bool tlResetMethods)
	{
		// Make sure our environment is sane
		if (obj)
		{
			// Update the sub-object data
			switch (obj->objType)
			{
				case _OBJ_TYPE_EMPTY:		// Empty, used as a placeholder object that is not drawn
					iiSubobj_resetToDefaultEmpty((SSubObjEmpty*)obj->sub_obj, true, tlResetProperties, tlResetMethods);
					break;

				case _OBJ_TYPE_FORM:			// Form class, the main outer window the OS sees
					iiSubobj_resetToDefaultForm((SSubObjForm*)obj->sub_obj, true, tlResetProperties, tlResetMethods);
					break;

				case _OBJ_TYPE_SUBFORM:		// A new class which has its own drawing content and can be moved about using UI features
					iiSubobj_resetToDefaultSubform((SSubObjSubform*)obj->sub_obj, true, tlResetProperties, tlResetMethods);
					break;

				case _OBJ_TYPE_LABEL:		// A label
					iiSubobj_resetToDefaultLabel((SSubObjLabel*)obj->sub_obj, true, tlResetProperties, tlResetMethods);
					break;

				case _OBJ_TYPE_TEXTBOX:		// An input textbox
					iiSubobj_resetToDefaultTextbox((SSubObjTextbox*)obj->sub_obj, true, tlResetProperties, tlResetMethods);
					break;

				case _OBJ_TYPE_BUTTON:		// A push button
					iiSubobj_resetToDefaultButton((SSubObjButton*)obj->sub_obj, true, tlResetProperties, tlResetMethods);
					break;

				case _OBJ_TYPE_EDITBOX:		// An input multi-line editbox
					iiSubobj_resetToDefaultEditbox((SSubObjEditbox*)obj->sub_obj, true, tlResetProperties, tlResetMethods);
					break;

				case _OBJ_TYPE_IMAGE:		// A graphical image
					iiSubobj_resetToDefaultImage((SSubObjImage*)obj->sub_obj, true, tlResetProperties, tlResetMethods);
					break;

				case _OBJ_TYPE_CHECKBOX:		// A checkbox
					iiSubobj_resetToDefaultCheckbox((SSubObjCheckbox*)obj->sub_obj, true, tlResetProperties, tlResetMethods);
					break;

				case _OBJ_TYPE_OPTION:		// A combination selection
					iiSubobj_resetToDefaultOption((SSubObjOption*)obj->sub_obj, true, tlResetProperties, tlResetMethods);
					break;

				case _OBJ_TYPE_RADIO:		// A radio dial, which can also present as a slider or spinner
					iiSubobj_resetToDefaultRadio((SSubObjRadio*)obj->sub_obj, true, tlResetProperties, tlResetMethods);
					break;

				default:
// TODO:  We should never get here... we should fire off an internal consistency error
					break;
			}
		}
	}




//////////
//
// Resets common object properties to their defaults
//
//////
	void iiObj_resetToDefaultCommon(SObject* obj, bool tlResetProperties, bool tlResetMethods)
	{
		/////////
		// Information about the object itself
		//////
			obj->tabIndex					= 0;
			obj->tabStop					= true;
			obj->helpContextId				= -1;
			obj->hasWhatsThisButton			= false;
			obj->hasWhatsThisHelp			= false;
			obj->whatsThisHelpId			= -1;


		//////////
		// Clear out the comment and tag
		//////
			iDatum_delete(&obj->tag, false);


		//////////
		// Clear out the mouse information
		//////
			iBmp_delete(&obj->mouseIcon, true, true);
			obj->mousePointer				= _MOUSE_POINTER_DEFAULT;


		//////////
		// Object flags
		//////
			obj->isEnabled					= true;
			obj->hasFocus					= false;
			obj->isMovable					= true;
			obj->isRendered					= true;
			obj->isPublished				= true;
			obj->isVisible					= false;
			obj->isDirty					= true;


		//////////
		// Any properties within
		//////
			if (tlResetProperties)
				iVariable_politelyDeleteChain(&obj->firstProperty, true);


		//////////
		// Any methods defined
		//////
			if (tlResetMethods)
				iEditChainManager_deleteChain(&obj->firstMethod, true);


		//////////
		// Events
		//////
			iEvents_resetToDefault(&obj->ev);


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
	s32 iiObj_getBaseclass_byName(s8* tcTextname, s32 tnTextnameLength)
	{
		SBaseclassList* lbcl;
		
		
		// Iterate through each function for matches
		lbcl = &gsKnownBaseclasses[0];
		while (lbcl && lbcl->baseclassName != NULL)
		{
			// Is this the named function?
			if (lbcl->baseclassNameLength == tnTextnameLength && _memicmp(tcTextname, (s8*)lbcl->baseclassName, tnTextnameLength) == 0)
				return(lbcl->objType);

			// Move to next function
			++lbcl;
		}
		// If we get here, not found
		return(-1);
	}




//////////
//
// Called to translate the class object type to its text-base name
//
//////
	SBaseclassList* iiObj_getBaseclass_byType(u32 tnObjType)
	{
		SBaseclassList* lbcl;
		
		
		// Iterate through each function for matches
		lbcl = &gsKnownBaseclasses[0];
		while (lbcl && lbcl->baseclassName != NULL)
		{
			// Is this the named function?
			if (lbcl->objType == tnObjType)
				return(lbcl);

			// Move to next function
			++lbcl;
		}
		// If we get here, not found
		return(NULL);
	}




//////////
//
// Creates the empty object structure
//
//////
	SSubObjEmpty* iSubobj_createEmpty(SSubObjEmpty* template_subobj, SObject* parent)
	{
		SSubObjEmpty* subobj;


		//////////
		// Create the indicated item
		//////
			subobj = (SSubObjEmpty*)malloc(sizeof(SSubObjEmpty));


		//////////
		// If successful, initialize it
		//////
			if (subobj)
			{
				// Initialize
				memset(subobj, 0, sizeof(SSubObjEmpty));

				// Initially populate
				subobj->objParent	= parent;

				// Initialize based on template
				if (template_subobj)
				{
					// Copy from indicated template
					iiSubobj_copyEmpty(subobj, template_subobj);

				} else {
					// Use VJr defaults
					iiSubobj_resetToDefaultEmpty(subobj, true, true, true);
				}

			}


		//////////
		// Indicate our success or failure
		//////
			return(subobj);
	}




//////////
//
// Creates the form object structure
//
//////
	SSubObjForm* iSubobj_createForm(SSubObjForm* template_subobj, SObject* objParent)
	{
		SSubObjForm*	subobj;
		SObject*		icon;
		SObject*		caption;
		SObject*		move;
		SObject*		minimize;
		SObject*		maximize;
		SObject*		close;


		//////////
		// Create the indicated item
		//////
			subobj = (SSubObjForm*)malloc(sizeof(SSubObjForm));


		//////////
		// If successful, initialize it
		//////
			if (subobj)
			{
				// Initialize
				memset(subobj, 0, sizeof(SSubObjForm));

				// Initially populate
				subobj->objParent = objParent;

				// Initialize based on template
				if (template_subobj)
				{
					// Copy from indicated template
					iiSubobj_copyForm(subobj, template_subobj);

				} else {
					// Use VJr defaults
					iiSubobj_resetToDefaultForm(subobj, true, true, true);


					//////////
					// Create the default children for this object
					//////
						icon		= iObj_create(_OBJ_TYPE_IMAGE, NULL, objParent);
						caption		= iObj_create(_OBJ_TYPE_LABEL, NULL, objParent);
						move		= iObj_create(_OBJ_TYPE_IMAGE, NULL, objParent);
						minimize	= iObj_create(_OBJ_TYPE_IMAGE, NULL, objParent);
						maximize	= iObj_create(_OBJ_TYPE_IMAGE, NULL, objParent);
						close		= iObj_create(_OBJ_TYPE_IMAGE, NULL, objParent);


					//////////
					// Give them proper names
					//////
						iDatum_duplicate(&icon->name,		cgcName_icon,			-1);
						iDatum_duplicate(&caption->name,	cgcCaption_icon,		-1);
						iDatum_duplicate(&move->name,		cgcName_iconMove,		-1);
						iDatum_duplicate(&minimize->name,	cgcName_iconMinimize,	-1);
						iDatum_duplicate(&maximize->name,	cgcName_iconMaximize,	-1);
						iDatum_duplicate(&close->name,		cgcName_iconClose,		-1);


					//////////
					// Append to the parent
					//////
						iObj_appendObjToParent(objParent, icon);
						iObj_appendObjToParent(objParent, caption);
						iObj_appendObjToParent(objParent, move);
						iObj_appendObjToParent(objParent, minimize);
						iObj_appendObjToParent(objParent, maximize);
						iObj_appendObjToParent(objParent, close);
				}
			}


		//////////
		// Indicate our success or failure
		//////
			return(subobj);
	}




//////////
//
// Creates the subform object structure
//
//////
	SSubObjSubform* iSubobj_createSubform(SSubObjSubform* template_subobj, SObject* parent)
	{
		SSubObjSubform* subobj;


		//////////
		// Create the indicated item
		//////
			subobj = (SSubObjSubform*)malloc(sizeof(SSubObjSubform));


		//////////
		// If successful, initialize it
		//////
			if (subobj)
			{
				// Initialize
				memset(subobj, 0, sizeof(SSubObjSubform));

				// Initially populate
				subobj->objParent = parent;

				// Initialize based on template
				if (template_subobj)
				{
					// Copy from indicated template
					iiSubobj_copySubform(subobj, template_subobj);

				} else {
					// Use VJr defaults
					iiSubobj_resetToDefaultSubform(subobj, true, true, true);
				}
			}


		//////////
		// Indicate our success or failure
		//////
			return(subobj);
	}




//////////
//
// Creates the label object structure
//
//////
	SSubObjLabel* iSubobj_createLabel(SSubObjLabel* template_subobj, SObject* parent)
	{
		SSubObjLabel* subobj;


		//////////
		// Create the indicated item
		//////
			subobj = (SSubObjLabel*)malloc(sizeof(SSubObjLabel));


		//////////
		// If successful, initialize it
		//////
			if (subobj)
			{
				// Initialize
				memset(subobj, 0, sizeof(SSubObjLabel));

				// Initially populate
				subobj->parent = parent;

				// Initialize based on template
				if (template_subobj)
				{
					// Copy from indicated template
					iiSubobj_copyLabel(subobj, template_subobj);

				} else {
					// Use VJr defaults
					iiSubobj_resetToDefaultLabel(subobj, true, true, true);
				}
			}


		//////////
		// Indicate our success or failure
		//////
			return(subobj);
	}




//////////
//
// Creates the textbox object structure
//
//////
	SSubObjTextbox* iSubobj_createTextbox(SSubObjTextbox* template_subobj, SObject* parent)
	{
		SSubObjTextbox* subobj;


		//////////
		// Create the indicated item
		//////
			subobj = (SSubObjTextbox*)malloc(sizeof(SSubObjTextbox));


		//////////
		// If successful, initialize it
		//////
			if (subobj)
			{
				// Initialize
				memset(subobj, 0, sizeof(SSubObjTextbox));

				// Initially populate
				subobj->objParent = parent;

				// Initialize based on template
				if (template_subobj)
				{
					// Copy from indicated template
					iiSubobj_copyTextbox(subobj, template_subobj);

				} else {
					// Use VJr defaults
					iiSubobj_resetToDefaultTextbox(subobj, true, true, true);
				}
			}


		//////////
		// Indicate our success or failure
		//////
			return(subobj);
	}




//////////
//
// Creates the button object structure
//
//////
	SSubObjButton* iSubobj_createButton(SSubObjButton* template_subobj, SObject* parent)
	{
		SSubObjButton* subobj;


		//////////
		// Create the indicated item
		//////
			subobj = (SSubObjButton*)malloc(sizeof(SSubObjButton));


		//////////
		// If successful, initialize it
		//////
			if (subobj)
			{
				// Initialize
				memset(subobj, 0, sizeof(SSubObjButton));

				// Initially populate
				subobj->parent = parent;

				// Initialize based on template
				if (template_subobj)
				{
					// Copy from indicated template
					iiSubobj_copyButton(subobj, template_subobj);

				} else {
					// Use VJr defaults
					iiSubobj_resetToDefaultButton(subobj, true, true, true);
				}
			}


		//////////
		// Indicate our success or failure
		//////
			return(subobj);
	}




//////////
//
// Creates the editbox object structure
//
//////
	SSubObjEditbox* iSubobj_createEditbox(SSubObjEditbox* template_subobj, SObject* parent)
	{
		SSubObjEditbox* subobj;


		//////////
		// Create the indicated item
		//////
			subobj = (SSubObjEditbox*)malloc(sizeof(SSubObjEditbox));


		//////////
		// If successful, initialize it
		//////
			if (subobj)
			{
				// Initialize
				memset(subobj, 0, sizeof(SSubObjEditbox));

				// Initially populate
				subobj->objParent = parent;

				// Initialize based on template
				if (template_subobj)
				{
					// Copy from indicated template
					iiSubobj_copyEditbox(subobj, template_subobj);

				} else {
					// Use VJr defaults
					iiSubobj_resetToDefaultEditbox(subobj, true, true, true);
				}
			}


		//////////
		// Indicate our success or failure
		//////
			return(subobj);
	}




//////////
//
// Creates the image object structure
//
//////
	SSubObjImage* iSubobj_createImage(SSubObjImage* template_subobj, SObject* parent)
	{
		SSubObjImage* subobj;


		//////////
		// Create the indicated item
		//////
			subobj = (SSubObjImage*)malloc(sizeof(SSubObjImage));


		//////////
		// If successful, initialize it
		//////
			if (subobj)
			{
				// Initialize
				memset(subobj, 0, sizeof(SSubObjImage));

				// Initially populate
				subobj->objParent = parent;

				// Initialize based on template
				if (template_subobj)
				{
					// Copy from indicated template
					iiSubobj_copyImage(subobj, template_subobj);

				} else {
					// Use VJr defaults
					iiSubobj_resetToDefaultImage(subobj, true, true, true);
				}
			}


		//////////
		// Indicate our success or failure
		//////
			return(subobj);
	}




//////////
//
// Creates the checkbox object structure
//
//////
	SSubObjCheckbox* iSubobj_createCheckbox(SSubObjCheckbox* template_subobj, SObject* parent)
	{
		SSubObjCheckbox* subobj;


		//////////
		// Create the indicated item
		//////
			subobj = (SSubObjCheckbox*)malloc(sizeof(SSubObjCheckbox));


		//////////
		// If successful, initialize it
		//////
			if (subobj)
			{
				// Initialize
				memset(subobj, 0, sizeof(SSubObjCheckbox));

				// Initially populate
				subobj->objParent = parent;

				// Initialize based on template
				if (template_subobj)
				{
					// Copy from indicated template
					iiSubobj_copyCheckbox(subobj, template_subobj);

				} else {
					// Use VJr defaults
					iiSubobj_resetToDefaultCheckbox(subobj, true, true, true);
				}
			}


		//////////
		// Indicate our success or failure
		//////
			return(subobj);
	}




//////////
//
// Creates the combo object structure
//
//////
	SSubObjOption* iSubobj_createOption(SSubObjOption* template_subobj, SObject* parent)
	{
		SSubObjOption* subobj;


		//////////
		// Create the indicated item
		//////
			subobj = (SSubObjOption*)malloc(sizeof(SSubObjOption));


		//////////
		// If successful, initialize it
		//////
			if (subobj)
			{
				// Initialize
				memset(subobj, 0, sizeof(SSubObjOption));

				// Initially populate
				subobj->objParent = parent;

				// Initialize based on template
				if (template_subobj)
				{
					// Copy from indicated template
					iiSubobj_copyOption(subobj, template_subobj);

				} else {
					// Use VJr defaults
					iiSubobj_resetToDefaultOption(subobj, true, true, true);
				}
			}


		//////////
		// Indicate our success or failure
		//////
			return(subobj);
	}




//////////
//
// Creates the radio object structure
//
//////
	SSubObjRadio* iSubobj_createRadio(SSubObjRadio* template_subobj, SObject* parent)
	{
		SSubObjRadio* subobj;


		//////////
		// Create the indicated item
		//////
			subobj = (SSubObjRadio*)malloc(sizeof(SSubObjRadio));


		//////////
		// If successful, initialize it
		//////
			if (subobj)
			{
				// Initialize
				memset(subobj, 0, sizeof(SSubObjRadio));

				// Initially populate
				subobj->objParent = parent;

				// Initialize based on template
				if (template_subobj)
				{
					// Copy from indicated template
					iiSubobj_copyRadio(subobj, template_subobj);

				} else {
					// Use VJr defaults
					iiSubobj_resetToDefaultRadio(subobj, true, true, true);
				}
			}


		//////////
		// Indicate our success or failure
		//////
			return(subobj);
	}




//////////
//
// Called to copy the indicated empty from source to destination
//
//////
	void iiSubobj_copyEmpty(SSubObjEmpty* subobjDst, SSubObjEmpty* subobjSrc)
	{
		//////////
		// Duplicate all children for this object
		//////
			iObj_duplicateChildren(subobjDst->objParent, subobjSrc->objParent);
	}




//////////
//
// Called to copy the indicated form from source to destination
//
//////
	void iiSubobj_copyForm(SSubObjForm* subobjDst, SSubObjForm* subobjSrc)
	{
		//////////
		// Copy our min/max
		//////
			CopyRect(&subobjDst->rcMax, &subobjSrc->rcMax);
			CopyRect(&subobjDst->rcMin, &subobjSrc->rcMin);


		//////////
		// Copy the font
		//////
			subobjDst->font						= iFont_duplicate(subobjSrc->font);


		//////////
		// Copy the colors
		//////
			subobjDst->nwRgba.color				= subobjSrc->nwRgba.color;
			subobjDst->neRgba.color				= subobjSrc->neRgba.color;
			subobjDst->swRgba.color				= subobjSrc->swRgba.color;
			subobjDst->seRgba.color				= subobjSrc->seRgba.color;
			subobjDst->backColor.color			= subobjSrc->backColor.color;
			subobjDst->foreColor.color			= subobjSrc->foreColor.color;
			subobjDst->captionColor.color		= subobjSrc->captionColor.color;


		//////////
		// Copy the form icon
		//////
			subobjDst->bmpFormIcon				= iBmp_copy(subobjSrc->bmpFormIcon);
			iDatum_duplicate(&subobjDst->caption, &subobjSrc->caption);


		//////////
		// Copy the caption
		//////
			iDatum_duplicate(&subobjDst->caption, &subobjSrc->caption);


		//////////
		// Copy the picture
		//////
			iBmp_delete(&subobjDst->bmpPicture, true, true);
			subobjDst->bmpPicture = iBmp_copy(subobjSrc->bmpPicture);
			iDatum_duplicate(&subobjDst->pictureName, &subobjSrc->pictureName);


		//////////
		// General flags and settings
		//////
			subobjDst->allowOutput				= subobjSrc->allowOutput;
			subobjDst->alwaysOnBottom			= subobjSrc->alwaysOnBottom;
			subobjDst->alwaysOnTop				= subobjSrc->alwaysOnTop;
			subobjDst->autoCenter				= subobjSrc->autoCenter;
			subobjDst->borderStyle				= subobjSrc->borderStyle;
			subobjDst->isClosable				= subobjSrc->isClosable;
			subobjDst->processKeyPreviewEvents	= subobjSrc->processKeyPreviewEvents;
			subobjDst->hasControlBox			= subobjSrc->hasControlBox;
			subobjDst->hasMinButton				= subobjSrc->hasMinButton;
			subobjDst->hasMaxButton				= subobjSrc->hasMaxButton;
			subobjDst->hasCloseButton			= subobjSrc->hasCloseButton;
			subobjDst->scaleMode				= subobjSrc->scaleMode;
			subobjDst->showInTaskBar			= subobjSrc->showInTaskBar;
			subobjDst->windowState				= subobjSrc->windowState;

			// The following are ignored, maintained only for backward compatibility
			subobjDst->bindControls				= subobjSrc->bindControls;
			subobjDst->bufferMode				= subobjSrc->bufferMode;
			subobjDst->clipControls				= subobjSrc->clipControls;
			subobjDst->colorSource				= subobjSrc->colorSource;
			subobjDst->continuousScroll			= subobjSrc->continuousScroll;
			iObj_delete(&subobjDst->dataSession, true);
			subobjDst->dataSessionId			= subobjSrc->dataSessionId;
			iDatum_duplicate(&subobjDst->declass,			&subobjSrc->declass);
			iDatum_duplicate(&subobjDst->declasslibrary,	&subobjSrc->declasslibrary);
			subobjDst->defolecid				= subobjSrc->defolecid;
			subobjDst->desktop					= subobjSrc->desktop;
			subobjDst->isDockable				= subobjSrc->isDockable;
			subobjDst->isDocked					= subobjSrc->isDocked;
			subobjDst->dockPosition				= subobjSrc->dockPosition;
			subobjDst->drawmode					= subobjSrc->drawmode;
			subobjDst->drawstyle				= subobjSrc->drawstyle;
			subobjDst->drawwidth				= subobjSrc->drawwidth;
			subobjDst->fillColor.color			= subobjSrc->fillColor.color;
			subobjDst->fillStyle				= subobjSrc->fillStyle;
			subobjDst->halfHeightCaption		= subobjSrc->halfHeightCaption;
			subobjDst->hScrollSmallChange		= subobjSrc->hScrollSmallChange;
			subobjDst->vScrollSmallChange		= subobjSrc->vScrollSmallChange;
			subobjDst->macDesktop				= subobjSrc->macDesktop;
			subobjDst->mdiForm					= subobjSrc->mdiForm;
			subobjDst->oleDragMode				= subobjSrc->oleDragMode;
			iBmp_delete(&subobjDst->oleDragPicture, true, true);
			subobjDst->oleDragPicture			= iBmp_copy(subobjSrc->oleDragPicture);
			subobjDst->oleDropEffects			= subobjSrc->oleDropEffects;
			subobjDst->oleDropHasData			= subobjSrc->oleDropHasData;
			subobjDst->oleDropMode				= subobjSrc->oleDropMode;
			subobjDst->releaseType				= subobjSrc->releaseType;
			subobjDst->rightToLeft				= subobjSrc->rightToLeft;
			subobjDst->scrollbars				= subobjSrc->scrollbars;
			subobjDst->showTips					= subobjSrc->showTips;
			subobjDst->showWindow				= subobjSrc->showWindow;
			subobjDst->sizeBox					= subobjSrc->sizeBox;
			subobjDst->themes					= subobjSrc->themes;
			subobjDst->titleBar					= subobjSrc->titleBar;
			subobjDst->windowType				= subobjSrc->windowType;
			subobjDst->zoomBox					= subobjSrc->zoomBox;


		//////////
		// Copy the form-specific event handlers
		//////
			*(u32*)&subobjDst->activate			= (u32)&subobjSrc->activate;
			*(u32*)&subobjDst->deactivate		= (u32)&subobjSrc->deactivate;


		//////////
		// Duplicate all children for this object
		//////
			iObj_duplicateChildren(subobjDst->objParent, subobjSrc->objParent);
	}




//////////
//
// Called to copy the indicated empty subfrom source to destination
//
//////
	void iiSubobj_copySubform(SSubObjSubform* subobjDst, SSubObjSubform* subobjSrc)
	{
		//////////
		// Copy our min/max
		//////
			CopyRect(&subobjDst->rcMax, &subobjSrc->rcMax);
			CopyRect(&subobjDst->rcMin, &subobjSrc->rcMin);


		//////////
		// Copy the font
		//////
			subobjDst->font						= iFont_duplicate(subobjSrc->font);


		//////////
		// Copy the colors
		//////
			subobjDst->nwRgba.color				= subobjSrc->nwRgba.color;
			subobjDst->neRgba.color				= subobjSrc->neRgba.color;
			subobjDst->swRgba.color				= subobjSrc->swRgba.color;
			subobjDst->seRgba.color				= subobjSrc->seRgba.color;
			subobjDst->backColor.color			= subobjSrc->backColor.color;
			subobjDst->foreColor.color			= subobjSrc->foreColor.color;
			subobjDst->captionColor.color		= subobjSrc->captionColor.color;


		//////////
		// Copy the form icon
		//////
			subobjDst->bmpSubformIcon				= iBmp_copy(subobjSrc->bmpSubformIcon);
			iDatum_duplicate(&subobjDst->caption, &subobjSrc->caption);


		//////////
		// Copy the caption
		//////
			iDatum_duplicate(&subobjDst->caption, &subobjSrc->caption);


		//////////
		// Copy the picture
		//////
			iBmp_delete(&subobjDst->bmpPicture, true, true);
			subobjDst->bmpPicture = iBmp_copy(subobjSrc->bmpPicture);
			iDatum_duplicate(&subobjDst->pictureName, &subobjSrc->pictureName);


		//////////
		// General flags and settings
		//////
			subobjDst->allowOutput				= subobjSrc->allowOutput;
			subobjDst->borderStyle				= subobjSrc->borderStyle;
			subobjDst->processKeyPreviewEvents	= subobjSrc->processKeyPreviewEvents;
			subobjDst->scaleMode				= subobjSrc->scaleMode;
			subobjDst->windowState				= subobjSrc->windowState;


		//////////
		// Copy the subform-specific event handlers
		//////
			*(u32*)&subobjDst->activate			= (u32)&subobjSrc->activate;
			*(u32*)&subobjDst->deactivate		= (u32)&subobjSrc->deactivate;


		//////////
		// Duplicate all children for this object
		//////
			iObj_duplicateChildren(subobjDst->objParent, subobjSrc->objParent);
	}




//////////
//
// Called to copy the indicated label from source to destination
//
//////
	void iiSubobj_copyLabel(SSubObjLabel* subobjDst, SSubObjLabel* subobjSrc)
	{
		//////////
		// Copy the font
		//////
			subobjDst->font						= iFont_duplicate(subobjSrc->font);


		//////////
		// Copy the colors
		//////
			subobjDst->backColor.color			= subobjSrc->backColor.color;
			subobjDst->foreColor.color			= subobjSrc->foreColor.color;


		//////////
		// Copy the caption
		//////
			iDatum_duplicate(&subobjDst->caption, &subobjSrc->caption);


		//////////
		// General settings
		//////
			subobjDst->alignment					= subobjSrc->alignment;
			subobjDst->isOpaque						= subobjSrc->isOpaque;
			subobjDst->isBorder						= subobjSrc->isBorder;
			subobjDst->borderColor.color			= subobjSrc->borderColor.color;
			subobjDst->disabledBackColor.color		= subobjSrc->disabledBackColor.color;
			subobjDst->disabledForeColor.color		= subobjSrc->disabledForeColor.color;


		//////////
		// Duplicate all children for this object
		//////
			iObj_duplicateChildren(subobjDst->parent, subobjSrc->parent);
	}




//////////
//
// Called to copy the indicated textbox from source to destination
//
//////
	void iiSubobj_copyTextbox(SSubObjTextbox* subobjDst, SSubObjTextbox* subobjSrc)
	{
		//////////
		// Copy the font
		//////
			subobjDst->font						= iFont_duplicate(subobjSrc->font);


		//////////
		// Copy the colors
		//////
			subobjDst->backColor.color			= subobjSrc->backColor.color;
			subobjDst->foreColor.color			= subobjSrc->foreColor.color;


		//////////
		// General settings
		//////
			subobjDst->style						= subobjSrc->style;
			subobjDst->alignment					= subobjSrc->alignment;
			iDatum_duplicate(&subobjDst->value,		&subobjSrc->value);
			subobjDst->valueLength					= subobjSrc->valueLength;
			iDatum_duplicate(&subobjDst->picture,	&subobjSrc->picture);
			iDatum_duplicate(&subobjDst->mask,		&subobjSrc->mask);
			subobjDst->isOpaque						= subobjSrc->isOpaque;
			subobjDst->isBorder						= subobjSrc->isBorder;
			subobjDst->borderColor.color			= subobjSrc->borderColor.color;
			subobjDst->selectedBackColor.color		= subobjSrc->selectedBackColor.color;
			subobjDst->selectedForeColor.color		= subobjSrc->selectedForeColor.color;
			subobjDst->disabledBackColor.color		= subobjSrc->disabledBackColor.color;
			subobjDst->disabledForeColor.color		= subobjSrc->disabledForeColor.color;


		//////////
		// Editor settings
		//////
			subobjDst->cursor						= subobjSrc->cursor;
			subobjDst->selectStart					= subobjSrc->selectStart;
			subobjDst->selectEnd					= subobjSrc->selectEnd;


		//////////
		// Copy the textbox-specific event handlers
		//////
			*(u32*)&subobjDst->interactiveChange	= *(u32*)&subobjSrc->interactiveChange;
			*(u32*)&subobjDst->programmaticChange	= *(u32*)&subobjSrc->programmaticChange;


		//////////
		// Duplicate all children for this object
		//////
			iObj_duplicateChildren(subobjDst->objParent, subobjSrc->objParent);
	}




//////////
//
// Called to copy the indicated button from source to destination
//
//////
	void iiSubobj_copyButton(SSubObjButton* subobjDst, SSubObjButton* subobjSrc)
	{
		//////////
		// Copy the font
		//////
			subobjDst->font						= iFont_duplicate(subobjSrc->font);


		//////////
		// Copy the colors
		//////
			subobjDst->backColor.color			= subobjSrc->backColor.color;
			subobjDst->foreColor.color			= subobjSrc->foreColor.color;


		//////////
		// General settings
		//////
			subobjDst->style						= subobjSrc->style;
			subobjDst->alignment					= subobjSrc->alignment;
			iDatum_duplicate(&subobjDst->caption,	&subobjSrc->caption);
			subobjDst->disabledBackColor.color		= subobjSrc->disabledBackColor.color;
			subobjDst->disabledForeColor.color		= subobjSrc->disabledForeColor.color;


		//////////
		// Copy the button-specific event handlers
		//////
			*(u32*)&subobjDst->interactiveChange	= *(u32*)&subobjSrc->interactiveChange;
			*(u32*)&subobjDst->programmaticChange	= *(u32*)&subobjSrc->programmaticChange;


		//////////
		// Duplicate all children for this object
		//////
			iObj_duplicateChildren(subobjDst->parent, subobjSrc->parent);
	}




//////////
//
// Called to copy the indicated editbox from source to destination
//
//////
	void iiSubobj_copyEditbox(SSubObjEditbox* subobjDst, SSubObjEditbox* subobjSrc)
	{
		//////////
		// Copy the font
		//////
			subobjDst->font						= iFont_duplicate(subobjSrc->font);


		//////////
		// Copy the colors
		//////
			subobjDst->backColor.color			= subobjSrc->backColor.color;
			subobjDst->foreColor.color			= subobjSrc->foreColor.color;


		//////////
		// General settings
		//////
			subobjDst->style						= subobjSrc->style;
			subobjDst->alignment					= subobjSrc->alignment;
			iEditChainManager_duplicate(&subobjDst->ecm, subobjSrc->ecm, true);
			subobjDst->isOpaque						= subobjSrc->isOpaque;
			subobjDst->isBorder						= subobjSrc->isBorder;
			subobjDst->borderColor.color			= subobjSrc->borderColor.color;
			subobjDst->selectedBackColor.color		= subobjSrc->selectedBackColor.color;
			subobjDst->selectedForeColor.color		= subobjSrc->selectedForeColor.color;
			subobjDst->disabledBackColor.color		= subobjSrc->disabledBackColor.color;
			subobjDst->disabledForeColor.color		= subobjSrc->disabledForeColor.color;


		//////////
		// Editor settings
		//////
			subobjDst->cursor						= subobjSrc->cursor;
			subobjDst->selectStart					= subobjSrc->selectStart;
			subobjDst->selectEnd					= subobjSrc->selectEnd;


		//////////
		// Copy the editbox-specific event handlers
		//////
			*(u32*)&subobjDst->interactiveChange	= *(u32*)&subobjSrc->interactiveChange;
			*(u32*)&subobjDst->programmaticChange	= *(u32*)&subobjSrc->programmaticChange;


		//////////
		// Duplicate all children for this object
		//////
			iObj_duplicateChildren(subobjDst->objParent, subobjSrc->objParent);
	}




//////////
//
// Called to copy the indicated image from source to destination
//
//////
	void iiSubobj_copyImage(SSubObjImage* subobjDst, SSubObjImage* subobjSrc)
	{
		//////////
		// General settings
		//////
			subobjDst->style						= subobjSrc->style;
			subobjDst->image						= iBmp_copy(subobjSrc->image);
			subobjDst->imageOver					= iBmp_copy(subobjSrc->imageOver);


		//////////
		// Copy the editbox-specific event handlers
		//////
			*(u32*)&subobjDst->programmaticChange	= *(u32*)&subobjSrc->programmaticChange;


		//////////
		// Duplicate all children for this object
		//////
			iObj_duplicateChildren(subobjDst->objParent, subobjSrc->objParent);
	}




//////////
//
// Called to copy the indicated checkbox from source to destination
//
//////
	void iiSubobj_copyCheckbox(SSubObjCheckbox* subobjDst, SSubObjCheckbox* subobjSrc)
	{
		//////////
		// Copy the font
		//////
			subobjDst->font						= iFont_duplicate(subobjSrc->font);


		//////////
		// Copy the colors
		//////
			subobjDst->backColor.color			= subobjSrc->backColor.color;
			subobjDst->foreColor.color			= subobjSrc->foreColor.color;


		//////////
		// General settings
		//////
			subobjDst->alignment					= subobjSrc->alignment;
			subobjDst->style						= subobjSrc->style;
			subobjDst->value						= subobjSrc->value;
			iDatum_duplicate(&subobjDst->caption,	&subobjSrc->caption);
			subobjDst->isOpaque						= subobjSrc->isOpaque;
			subobjDst->isBorder						= subobjSrc->isBorder;
			subobjDst->borderColor.color			= subobjSrc->borderColor.color;
			subobjDst->disabledBackColor.color		= subobjSrc->disabledBackColor.color;
			subobjDst->disabledForeColor.color		= subobjSrc->disabledForeColor.color;


		//////////
		// Copy the checkbox-specific event handlers
		//////
			*(u32*)&subobjDst->interactiveChange	= *(u32*)&subobjSrc->interactiveChange;
			*(u32*)&subobjDst->programmaticChange	= *(u32*)&subobjSrc->programmaticChange;


		//////////
		// Duplicate all children for this object
		//////
			iObj_duplicateChildren(subobjDst->objParent, subobjSrc->objParent);
	}




//////////
//
// Called to copy the indicated option from source to destination
//
//////
	void iiSubobj_copyOption(SSubObjOption* subobjDst, SSubObjOption* subobjSrc)
	{
		//////////
		// Copy the colors
		//////
			subobjDst->backColor.color			= subobjSrc->backColor.color;
			subobjDst->foreColor.color			= subobjSrc->foreColor.color;


		//////////
		// General settings
		//////
			subobjDst->alignment					= subobjSrc->alignment;
			subobjDst->style						= subobjSrc->style;
			subobjDst->optionCount					= subobjSrc->optionCount;		// How many options are there?
			subobjDst->multiSelect					= subobjSrc->multiSelect;		// Can multiple items be selected?


		//////////
		// Copy the label objects
		//////
			iObj_duplicateChain(&subobjDst->firstOption, subobjSrc->firstOption);	// Each option has its own set of properties, and each is of _OBJECT_TYPE_LABEL


		//////////
		// Copy the option-specific event handlers
		//////
			*(u32*)&subobjDst->onSelect				= *(u32*)&subobjSrc->onSelect;
			*(u32*)&subobjDst->onDeselect			= *(u32*)&subobjSrc->onDeselect;
			*(u32*)&subobjDst->interactiveChange	= *(u32*)&subobjSrc->interactiveChange;
			*(u32*)&subobjDst->programmaticChange	= *(u32*)&subobjSrc->programmaticChange;


		//////////
		// Duplicate all children for this object
		//////
			iObj_duplicateChildren(subobjDst->objParent, subobjSrc->objParent);
	}




//////////
//
// Called to copy the indicated radio from source to destination
//
//////
	void iiSubobj_copyRadio(SSubObjRadio* subobjDst, SSubObjRadio* subobjSrc)
	{
		//////////
		// Copy the font
		//////
			subobjDst->font						= iFont_duplicate(subobjSrc->font);


		//////////
		// Copy the colors
		//////
			subobjDst->backColor.color			= subobjSrc->backColor.color;
			subobjDst->foreColor.color			= subobjSrc->foreColor.color;


		//////////
		// General settings
		//////
			subobjDst->alignment					= subobjSrc->alignment;
			subobjDst->style						= subobjSrc->style;
			subobjDst->value						= subobjSrc->value;
			subobjDst->minValue						= subobjSrc->minValue;
			subobjDst->maxValue						= subobjSrc->maxValue;
			subobjDst->roundTo						= subobjSrc->roundTo;
			subobjDst->isOpaque						= subobjSrc->isOpaque;
			subobjDst->isBorder						= subobjSrc->isBorder;
			subobjDst->borderColor.color			= subobjSrc->borderColor.color;
			subobjDst->disabledBackColor.color		= subobjSrc->disabledBackColor.color;
			subobjDst->disabledForeColor.color		= subobjSrc->disabledForeColor.color;


		//////////
		// Copy the option-specific event handlers
		//////
			*(u32*)&subobjDst->interactiveChange	= *(u32*)&subobjSrc->interactiveChange;
			*(u32*)&subobjDst->programmaticChange	= *(u32*)&subobjSrc->programmaticChange;


		//////////
		// Duplicate all children for this object
		//////
			iObj_duplicateChildren(subobjDst->objParent, subobjSrc->objParent);
	}




//////////
//
// Called to reset the object to its hard defaults.
//
//////
	void iiSubobj_resetToDefaultEmpty(SSubObjEmpty* empty, bool tlResetObject, bool tlResetProperties, bool tlResetMethods)
	{
		SObject* obj;


		// Do we need to reset the object as well (Note that subobj->parent is the obj here)
		obj = empty->objParent;
		if (obj && tlResetObject)
		{
			//////////
			// Reset the common settings
			//////
				iiObj_resetToDefaultCommon(obj, true, true);
		}

		// No object-specific initialization because empty objects do nothing except exist as placeholders
	}

	void iiSubobj_resetToDefaultForm(SSubObjForm* form, bool tlResetObject, bool tlResetProperties, bool tlResetMethods)
	{
		SObject* obj;


		// Do we need to reset the object as well (Note that subobj->parent is the obj here)
		obj = form->objParent;
		if (obj && tlResetObject)
		{
			//////////
			// Reset the common settings
			//////
				iiObj_resetToDefaultCommon(obj, true, true);


			//////////
			// Set default size and position
			//////
				SetRect(&obj->rc, 0, 0, 375, 250);
				SetRect(&obj->rco, 0, 0, 375, 250);
				SetRect(&obj->rcp, 0, 0, 375, 250);


			//////////
			// Set default anchor to fixed in all positions, no resize
			//////
				obj->anchor = _ANCHOR_FIXED_NORESIZE;
		}

		//////////
		// Set the default font
		//////
			iFont_delete(&form->font, true);
			form->font					= iFont_duplicate(gsFont);


		//////////
		// Set the default colors
		//////
			form->nwRgba.color			= NwColor.color;
			form->neRgba.color			= NeColor.color;
			form->swRgba.color			= SwColor.color;
			form->seRgba.color			= SeColor.color;
			form->backColor.color		= white.color;
			form->foreColor.color		= black.color;
			form->captionColor.color	= dark_blue.color;


		//////////
		// Set the default form icon
		//////
			iBmp_delete(&form->bmpFormIcon, true, true);
			form->bmpFormIcon			= iBmp_copy(bmpVjrIcon);


		//////////
		// Set the default caption
		//////
			iDatum_duplicate(&form->caption, cgcName_form, -1);


		//////////
		// Set the default form-specific events
		//////
			*(u32*)&form->activate		= (u32)&iDefaultCallback_onActivate;
			*(u32*)&form->deactivate	= (u32)&iDefaultCallback_onDeactivate;


		//////////
		// Reset our min/max
		//////
			SetRect(&form->rcMax, -1, -1, -1, -1);
			SetRect(&form->rcMin, -1, -1, -1, -1);


		//////////
		// Clear the picture
		//////
			iBmp_delete(&form->bmpPicture, true, true);


		//////////
		// General flags and settings
		//////
			form->allowOutput						= true;
			form->alwaysOnBottom					= false;
			form->alwaysOnTop						= false;
			form->autoCenter						= false;
			form->borderStyle						= _BORDER_STYLE_SIZABLE;
			form->isClosable						= true;
			form->processKeyPreviewEvents			= false;
			form->hasControlBox						= true;
			form->hasMinButton						= true;
			form->hasMaxButton						= true;
			form->hasCloseButton					= true;
			form->scaleMode							= _SCALE_MODE_PIXELS;
			form->showInTaskBar						= true;
			form->windowState						= _WINDOW_STATE_NORMAL;

			// The following are ignored, maintained only for backward compatibility
			form->bindControls						= true;
			form->bufferMode						= 2;
			form->clipControls						= false;
			form->colorSource						= 4;
			form->continuousScroll					= true;
			iObj_delete(&form->dataSession, true);
			form->dataSessionId						= -1;
			iDatum_delete(&form->declass, false);
			iDatum_delete(&form->declasslibrary, false);
			form->defolecid							= -1;
			form->desktop							= false;
			form->isDockable						= false;
			form->isDocked							= false;
			form->dockPosition						= -1;
			form->drawmode							= -1;
			form->drawstyle							= 13;
			form->drawwidth							= 1;
			form->fillColor.color					= rgba(255,255,255,255);
			form->fillStyle							= 0;
			form->halfHeightCaption					= false;
			form->hScrollSmallChange				= 10;
			form->vScrollSmallChange				= 10;
			form->macDesktop						= false;
			form->mdiForm							= false;
			form->oleDragMode						= 0;
			iBmp_delete(&form->oleDragPicture, true, true);
			form->oleDropEffects					= 3;
			form->oleDropHasData					= -1;
			form->oleDropMode						= 0;
			form->releaseType						= 0;
			form->rightToLeft						= false;
			form->scrollbars						= 3;
			form->showTips							= true;
			form->showWindow						= 2;
			form->sizeBox							= false;
			form->themes							= true;
			form->titleBar							= 1;
			form->windowType						= 0;
			form->zoomBox							= false;
	}

	void iiSubobj_resetToDefaultSubform(SSubObjSubform* subform, bool tlResetObject, bool tlResetProperties, bool tlResetMethods)
	{
		SObject* obj;


		// Do we need to reset the object as well (Note that subobj->parent is the obj here)
		obj = subform->objParent;
		if (tlResetObject)
		{
			//////////
			// Reset the common settings
			//////
				iiObj_resetToDefaultCommon(obj, true, true);


			//////////
			// Set default size and position
			//////
				SetRect(&obj->rc, 0, 0, 275, 150);
				SetRect(&obj->rco, 0, 0, 275, 150);
				SetRect(&obj->rcp, 0, 0, 275, 150);


			//////////
			// Set default anchor to fixed in all positions, no resize
			//////
				obj->anchor = _ANCHOR_FIXED_NORESIZE;
		}


		//////////
		// Set the default font
		//////
			iFont_delete(&subform->font, true);
			subform->font					= iFont_duplicate(gsFont);


		//////////
		// Set the default colors
		//////
			subform->nwRgba.color			= NwColor.color;
			subform->neRgba.color			= NeColor.color;
			subform->swRgba.color			= SwColor.color;
			subform->seRgba.color			= SeColor.color;
			subform->backColor.color		= white.color;
			subform->foreColor.color		= black.color;
			subform->captionColor.color		= dark_blue.color;


		//////////
		// Set the default form icon
		//////
			iBmp_delete(&subform->bmpSubformIcon, true, true);
			subform->bmpSubformIcon			= iBmp_copy(bmpVjrIcon);


		//////////
		// Set the default caption
		//////
			iDatum_duplicate(&subform->caption, cgcName_subform, -1);


		//////////
		// Set the default form-specific events
		//////
			*(u32*)&subform->activate		= (u32)&iDefaultCallback_onActivate;
			*(u32*)&subform->deactivate		= (u32)&iDefaultCallback_onDeactivate;
	}

	void iiSubobj_resetToDefaultLabel(SSubObjLabel* label, bool tlResetObject, bool tlResetProperties, bool tlResetMethods)
	{
		u32			lnHeight;
		SObject*	obj;


		// Do we need to reset the object as well (Note that subobj->parent is the obj here)
		obj = label->parent;
		if (tlResetObject)
		{
			//////////
			// Reset the common settings
			//////
				iiObj_resetToDefaultCommon(obj, true, true);


			//////////
			// Set default size and position
			//////
				lnHeight = max(gsFont->tm.tmHeight + 2, 10);
				SetRect(&obj->rc, 0, 0, 275, lnHeight);
				SetRect(&obj->rco, 0, 0, 275, lnHeight);
				SetRect(&obj->rcp, 0, 0, 275, lnHeight);


			//////////
			// Set default anchor to fixed in all positions, no resize
			//////
				obj->anchor = _ANCHOR_FIXED_NORESIZE;
		}


		//////////
		// Set the default font
		//////
			iFont_delete(&label->font, true);
			label->font							= iFont_duplicate(gsFont);


		//////////
		// Set the default colors
		//////
			label->backColor.color				= white.color;
			label->foreColor.color				= black.color;


		//////////
		// Set the characteristics
		//////
			label->alignment					= _ALIGNMENT_LEFT;
			iDatum_duplicate(&label->caption, cgcName_label, 5);
			label->isOpaque						= true;
			label->isBorder						= false;
			label->borderColor.color			= black.color;
			label->disabledBackColor.color		= disabledBackColor.color;
			label->disabledForeColor.color		= disabledForeColor.color;
	}

	void iiSubobj_resetToDefaultTextbox(SSubObjTextbox* textbox, bool tlResetObject, bool tlResetProperties, bool tlResetMethods)
	{
		SObject* obj;


		// Do we need to reset the object as well (Note that subobj->parent is the obj here)
		obj = textbox->objParent;
		if (tlResetObject)
		{
			//////////
			// Reset the common settings
			//////
				iiObj_resetToDefaultCommon(obj, true, true);


			//////////
			// Set default size and position
			//////
				SetRect(&obj->rc, 0, 0, 100, 75);
				SetRect(&obj->rco, 0, 0, 100, 75);
				SetRect(&obj->rcp, 0, 0, 100, 75);


			//////////
			// Set default anchor to fixed in all positions, no resize
			//////
				obj->anchor = _ANCHOR_FIXED_NORESIZE;
		}


		//////////
		// Set the default font
		//////
			iFont_delete(&textbox->font, true);
			textbox->font						= iFont_duplicate(gsFont);


		//////////
		// Set the default colors
		//////
			textbox->backColor.color			= white.color;
			textbox->foreColor.color			= black.color;


		//////////
		// Set the characteristics
		//////
			textbox->style						= _STYLE_3D;
			textbox->alignment					= _ALIGNMENT_LEFT;
			textbox->valueLength				= 0;

			textbox->cursor						= 0;
			textbox->selectStart				= -1;
			textbox->selectEnd					= -1;

			textbox->isOpaque					= true;
			textbox->isBorder					= false;
			textbox->borderColor.color			= black.color;
			textbox->selectedBackColor.color	= selectedBackColor.color;
			textbox->selectedForeColor.color	= selectedForeColor.color;
			textbox->disabledBackColor.color	= disabledBackColor.color;
			textbox->disabledForeColor.color	= disabledForeColor.color;


		//////////
		// Indicate the callback handler
		//////
			*(u32*)&textbox->interactiveChange	= *(u32*)&iDefaultCallback_onInteractiveChange;
			*(u32*)&textbox->programmaticChange	= *(u32*)&iDefaultCallback_onProgrammaticChange;
	}

	void iiSubobj_resetToDefaultButton(SSubObjButton* button, bool tlResetObject, bool tlResetProperties, bool tlResetMethods)
	{
		SObject* obj;


		// Do we need to reset the object as well (Note that subobj->parent is the obj here)
		obj = button->parent;
		if (tlResetObject)
		{
			button->font						= iFont_duplicate(gsFont);
			button->backColor.color				= white.color;
			button->foreColor.color				= black.color;

			button->style						= _STYLE_3D;
			button->alignment					= _ALIGNMENT_LEFT;
			iDatum_duplicate(&button->caption,	"Button", 6);

			button->disabledBackColor.color		= disabledBackColor.color;
			button->disabledForeColor.color		= disabledForeColor.color;

			*(u32*)&button->interactiveChange	= *(u32*)&iDefaultCallback_onInteractiveChange;
			*(u32*)&button->programmaticChange	= *(u32*)&iDefaultCallback_onProgrammaticChange;
		}
	}

	void iiSubobj_resetToDefaultEditbox(SSubObjEditbox* editbox, bool tlResetObject, bool tlResetProperties, bool tlResetMethods)
	{
		SObject* obj;


		// Do we need to reset the object as well (Note that subobj->parent is the obj here)
		obj = editbox->objParent;
		if (tlResetObject)
		{
			editbox->font							= iFont_duplicate(gsFont);
			editbox->backColor.color				= white.color;
			editbox->foreColor.color				= black.color;

			editbox->style							= _STYLE_3D;
			editbox->alignment						= _ALIGNMENT_LEFT;

			editbox->cursor							= 0;
			editbox->selectStart					= -1;
			editbox->selectEnd						= -1;

			editbox->isOpaque						= true;
			editbox->isBorder						= false;
			editbox->borderColor.color				= black.color;
			editbox->selectedBackColor.color		= selectedBackColor.color;
			editbox->selectedForeColor.color		= selectedForeColor.color;
			editbox->disabledBackColor.color		= disabledBackColor.color;
			editbox->disabledForeColor.color		= disabledForeColor.color;

			*(u32*)&editbox->interactiveChange		= *(u32*)&iDefaultCallback_onInteractiveChange;
			*(u32*)&editbox->programmaticChange		= *(u32*)&iDefaultCallback_onProgrammaticChange;
		}
	}

	void iiSubobj_resetToDefaultImage(SSubObjImage* image, bool tlResetObject, bool tlResetProperties, bool tlResetMethods)
	{
		SObject* obj;


		// Do we need to reset the object as well (Note that subobj->parent is the obj here)
		obj = image->objParent;
		if (tlResetObject)
		{
			image->style						= _IMAGE_STYLE_OPAQUE;
			image->image						= iBmp_copy(bmpNoImage);

			*(u32*)&image->programmaticChange	= *(u32*)&iDefaultCallback_onProgrammaticChange;
		}
	}

	void iiSubobj_resetToDefaultCheckbox(SSubObjCheckbox* checkbox, bool tlResetObject, bool tlResetProperties, bool tlResetMethods)
	{
		SObject* obj;


		// Do we need to reset the object as well (Note that subobj->parent is the obj here)
		obj = checkbox->objParent;
		if (tlResetObject)
		{
			checkbox->font							= iFont_duplicate(gsFont);
			checkbox->backColor.color				= white.color;
			checkbox->foreColor.color				= black.color;

			checkbox->alignment						= _ALIGNMENT_LEFT;
			checkbox->style							= _STYLE_3D;
			checkbox->value							= 0;
			iDatum_duplicate(&checkbox->caption, cgcName_checkbox, 8);

			checkbox->isOpaque						= true;
			checkbox->isBorder						= false;
			checkbox->borderColor.color				= black.color;
			checkbox->disabledBackColor.color		= disabledBackColor.color;
			checkbox->disabledForeColor.color		= disabledForeColor.color;

			*(u32*)&checkbox->interactiveChange		= *(u32*)&iDefaultCallback_onInteractiveChange;
			*(u32*)&checkbox->programmaticChange	= *(u32*)&iDefaultCallback_onProgrammaticChange;
		}
	}

	void iiSubobj_resetToDefaultOption(SSubObjOption* option, bool tlResetObject, bool tlResetProperties, bool tlResetMethods)
	{
		SObject* obj;


		// Do we need to reset the object as well (Note that subobj->parent is the obj here)
		obj = option->objParent;
		if (tlResetObject)
		{
			option->backColor.color				= white.color;
			option->foreColor.color				= black.color;

			option->alignment					= _ALIGNMENT_LEFT;
			option->style						= _STYLE_3D;

			option->optionCount					= 2;
			option->multiSelect					= false;

			// Create the two objects
			option->firstOption					= iObj_create(_OBJ_TYPE_LABEL, NULL, obj);
			if (option->firstOption)
				option->firstOption->ll.next	= (SLL*)iObj_create(_OBJ_TYPE_LABEL, NULL, obj);

			// Copy the events
			*(u32*)&option->onSelect			= *(u32*)&iDefaultCallback_onSelect;
			*(u32*)&option->onDeselect			= *(u32*)&iDefaultCallback_onDeselect;
			*(u32*)&option->interactiveChange	= *(u32*)&iDefaultCallback_onInteractiveChange;
			*(u32*)&option->programmaticChange	= *(u32*)&iDefaultCallback_onProgrammaticChange;
		}
	}

	void iiSubobj_resetToDefaultRadio(SSubObjRadio* radio, bool tlResetObject, bool tlResetProperties, bool tlResetMethods)
	{
		SObject* obj;


		// Do we need to reset the object as well (Note that subobj->parent is the obj here)
		obj = radio->objParent;
		if (tlResetObject)
		{
			radio->font							= iFont_duplicate(gsFont);
			radio->backColor.color				= white.color;
			radio->foreColor.color				= black.color;

			radio->alignment					= _ALIGNMENT_LEFT;
			radio->style						= _STYLE_3D;
			radio->value						= 0;
			radio->minValue						= 0;
			radio->maxValue						= 100;
			radio->roundTo						= 1.0f;

			radio->isOpaque						= true;
			radio->isBorder						= false;
			radio->borderColor.color			= black.color;
			radio->disabledBackColor.color		= disabledBackColor.color;
			radio->disabledForeColor.color		= disabledForeColor.color;

			*(u32*)&radio->interactiveChange	= *(u32*)&iDefaultCallback_onInteractiveChange;
			*(u32*)&radio->programmaticChange	= *(u32*)&iDefaultCallback_onProgrammaticChange;
		}
	}




//////////
//
// Called to set the form's icon
//
//////
	void iiSubobj_form_setIcon(SObject* obj, SBitmap* bmp)
	{
		SSubObjForm* form;


		// Make sure our environment is sane
		if (obj && bmp && obj->objType == _OBJ_TYPE_FORM)
		{
			// Grab the form data
			form = (SSubObjForm*)obj->sub_obj;

			// Delete the old icon if any
			if (form->bmpFormIcon)
				iBmp_delete(&form->bmpFormIcon, true, true);

			// Create a new icon that is 24x24
			form->bmpFormIcon = iBmp_allocate();
			iBmp_createBySize(form->bmpFormIcon, 24, 24, 24);

			// Scale the indicated icon into this one
			iBmp_scale(form->bmpFormIcon, bmp);
		}
	}




//////////
//
// Called to delete the empty.
//
//////
	void iSubobj_deleteEmpty(SSubObjEmpty* empty, bool tlDeleteSelf)
	{
		//////////
		// Free self
		//////
			if (tlDeleteSelf)
				free(empty);
	}




//////////
//
// Called to delete the form.
//
//////
	void iSubobj_deleteForm(SSubObjForm* form, bool tlDeleteSelf)
	{
		//////////
		// Free subobject components
		//////
			iFont_delete(&form->font, true);
			iBmp_delete(&form->bmpFormIcon, true, true);
			iDatum_delete(&form->caption, false);


		//////////
		// Free self
		//////
			if (tlDeleteSelf)
				free(form);
	}




//////////
//
// Called to delete the subform.
//
//////
	void iSubobj_deleteSubform(SSubObjSubform* subform, bool tlDeleteSelf)
	{
		//////////
		// Free subobject components
		//////
			iFont_delete(&subform->font, true);
			iBmp_delete(&subform->bmpSubformIcon, true, true);
			iDatum_delete(&subform->caption, false);


		//////////
		// Free self
		//////
			if (tlDeleteSelf)
				free(subform);
	}




//////////
//
// Called to delete the label.
//
//////
	void iSubobj_deleteLabel(SSubObjLabel* label, bool tlDeleteSelf)
	{
		//////////
		// Free subobject components
		//////
			iFont_delete(&label->font, true);
			iDatum_delete(&label->caption, false);


		//////////
		// Free self
		//////
			if (tlDeleteSelf)
				free(label);
	}




//////////
//
// Called to delete the textbox.
//
//////
	void iSubobj_deleteTextbox(SSubObjTextbox* textbox, bool tlDeleteSelf)
	{
		//////////
		// Free subobject components
		//////
			iFont_delete(&textbox->font, true);
			iDatum_delete(&textbox->value, false);
			iDatum_delete(&textbox->picture, false);
			iDatum_delete(&textbox->mask, false);


		//////////
		// Free self
		//////
			if (tlDeleteSelf)
				free(textbox);
	}




//////////
//
// Called to delete the button.
//
//////
	void iSubobj_deleteButton(SSubObjButton* button, bool tlDeleteSelf)
	{
		//////////
		// Free subobject components
		//////
			iFont_delete(&button->font, true);
			iDatum_delete(&button->caption, false);


		//////////
		// Free self
		//////
			if (tlDeleteSelf)
				free(button);
	}




//////////
//
// Called to delete the editbox.
//
//////
	void iSubobj_deleteEditbox(SSubObjEditbox* editbox, bool tlDeleteSelf)
	{
		//////////
		// Free subobject components
		//////
			iFont_delete(&editbox->font, true);
			iEditChainManager_delete(&editbox->ecm, true);


		//////////
		// Free self
		//////
			if (tlDeleteSelf)
				free(editbox);
	}




//////////
//
// Called to delete the image.
//
//////
	void iSubobj_deleteImage(SSubObjImage* image, bool tlDeleteSelf)
	{
		//////////
		// Free subobject components
		//////


		//////////
		// Free self
		//////
			if (tlDeleteSelf)
				free(image);
	}




//////////
//
// Called to delete the checkbox.
//
//////
	void iSubobj_deleteCheckbox(SSubObjCheckbox* checkbox, bool tlDeleteSelf)
	{
		//////////
		// Free subobject components
		//////


		//////////
		// Free self
		//////
			if (tlDeleteSelf)
				free(checkbox);
	}




//////////
//
// Called to delete the option.
//
//////
	void iSubobj_deleteOption(SSubObjOption* option, bool tlDeleteSelf)
	{
		//////////
		// Free subobject components
		//////


		//////////
		// Free self
		//////
			if (tlDeleteSelf)
				free(option);
	}




//////////
//
// Called to delete the radio.
//
//////
	void iSubobj_deleteRadio(SSubObjRadio* radio, bool tlDeleteSelf)
	{
		//////////
		// Free subobject components
		//////


		//////////
		// Free self
		//////
			if (tlDeleteSelf)
				free(radio);
	}




//////////
//
// Renders an empty.  Note, empty objects are not rendered.  This control, however,
// can have controls within which are rendered to off-screen buffers, used for whatever
// non-visual purposes exist.  As such, render calls are still made to it.
//
//////
	u32 iSubobj_renderEmpty(SObject* obj, SSubObjEmpty* empty, bool tlRenderChildren, bool tlRenderSiblings)
	{
		//////////
		// Do any requisite processing
		//////
			iObj_renderChildrenAndSiblings(obj, tlRenderChildren, tlRenderSiblings);


		//////////
		// Success!
		//////
			obj->isDirty = false;
			return(0);		// Indicate that nothing was rendered which will affect the screen
	}




//////////
//
// Renders the form, which traverses through all child objects and renders to the
// furthest extent before rendering itself.
//
// Note:  The object rendering is independent of the publication of the constructed
//        bitmap.  The render operation only populates the bit buffer.  It will be
//        published at a later time, if indeed it is visible, however, it can after
//        rendering be re-directed to some other source, a disk file, or over a
//        network resource.
//
//////
	u32 iSubobj_renderForm(SObject* obj, SSubObjForm* form, bool tlRenderChildren, bool tlRenderSiblings)
	{
		u32				lnPixelsRendered;
		SObject*		objSib;
		RECT			lrc, lrc2, lrc3, lrc4;
		HFONT			lhfontOld;


		// Make sure our environment is sane
		lnPixelsRendered = 0;
		if (obj && form)
		{
			//////////
			// Make sure there is a bit bucket
			//////
				if (!obj->bmp)
				{
					obj->bmp = iBmp_allocate();
					iBmp_createBySize(obj->bmp, obj->rc.right - obj->rc.left, obj->rc.bottom - obj->rc.top, 24);
				}


			//////////
			// Traverse and render any children
			//////
				if (tlRenderChildren && obj->firstChild)
					lnPixelsRendered += iObj_render(obj->firstChild, true, true);


			//////////
			// If we need re-rendering, re-render
			//////
				// The entire bmp
				SetRect(&lrc, 0, 0, obj->bmp->bi.biWidth, obj->bmp->bi.biHeight);

				// Do we need to redraw?  Or can we just copy?
				if (obj->isDirty || lnPixelsRendered != 0)
				{
					//////////
					// Frame it
					//////
						// Draw the window border
						iBmp_fillRect(obj->bmp, &lrc, form->nwRgba, form->neRgba, form->swRgba, form->seRgba, true);

						// Frame it
						iBmp_frameRect(obj->bmp, &lrc, black, black, black, black, false);

						// Draw the client area
						SetRect(&lrc2, 8, form->bmpFormIcon->bi.biHeight + 2, lrc.right - form->bmpFormIcon->bi.biHeight - 2, lrc.bottom - form->bmpFormIcon->bi.biHeight - 1);
						iBmp_fillRect(obj->bmp, &lrc2, white, white, white, white, false);
// These rc* copies were added temporarily until the full object structure is coded and working
//CopyRect(&form->rcClient, &lrc2);

						// Put a border around the client area
						InflateRect(&lrc2, 1, 1);
						iBmp_frameRect(obj->bmp, &lrc2, black, black, black, black, false);


					//////////
					// Form icon and standard controls
					//////
						// Form icon
						SetRect(&lrc3,	bmpArrowUl->bi.biWidth + 8, 1, bmpArrowUl->bi.biWidth + 8 + form->bmpFormIcon->bi.biWidth, 1 + form->bmpFormIcon->bi.biHeight);
						iBmp_bitBltMask(obj->bmp, &lrc3, form->bmpFormIcon);
CopyRect(&form->rcIcon, &lrc3);

						// Close
						SetRect(&lrc2,	lrc.right - bmpArrowUr->bi.biWidth - 8 - bmpClose->bi.biWidth, lrc.top + 1, lrc.right - bmpArrowUr->bi.biWidth - 8, lrc.bottom - 1);
						iBmp_bitBltMask(obj->bmp, &lrc2, bmpClose);
CopyRect(&form->rcClose, &lrc2);

						// Maximize
						SetRect(&lrc2,	lrc2.left - bmpMaximize->bi.biWidth - 1, lrc2.top, lrc2.left - 1, lrc2.bottom);
						iBmp_bitBltMask(obj->bmp, &lrc2, bmpMaximize);
CopyRect(&form->rcMaximize, &lrc2);

						// Minimize
						SetRect(&lrc2,	lrc2.left - bmpMinimize->bi.biWidth - 1, lrc2.top, lrc2.left - 1, lrc2.bottom);
						iBmp_bitBltMask(obj->bmp, &lrc2, bmpMinimize);
CopyRect(&form->rcMinimize, &lrc2);

						// Move
						SetRect(&lrc4,	lrc2.left - bmpMove->bi.biWidth - 1, lrc2.top, lrc2.left - 1, lrc2.bottom);
						iBmp_bitBltMask(obj->bmp, &lrc4, bmpMove);
CopyRect(&form->rcMove, &lrc4);


					//////////
					// Resizing arrows
					//////
						// Upper left arrow
						SetRect(&lrc2, lrc.left, lrc.top, lrc.left + bmpArrowUl->bi.biWidth, lrc.top + bmpArrowUl->bi.biHeight);
						iBmp_bitBltMask(obj->bmp, &lrc2, bmpArrowUl);
CopyRect(&form->rcArrowUl, &lrc2);

						// Upper right arrow
						SetRect(&lrc2, lrc.right - bmpArrowUr->bi.biWidth, lrc.top, lrc.right, lrc.top + bmpArrowUr->bi.biHeight);
						iBmp_bitBltMask(obj->bmp, &lrc2, bmpArrowUr);
CopyRect(&form->rcArrowUr, &lrc2);

						// Lower left arrow
						SetRect(&lrc2, lrc.right - bmpArrowLr->bi.biWidth, lrc.bottom - bmpArrowLr->bi.biHeight, lrc.right, lrc.bottom);
						iBmp_bitBltMask(obj->bmp, &lrc2, bmpArrowLr);
CopyRect(&form->rcArrowLl, &lrc2);

						// Lower right arrow
						SetRect(&lrc2, lrc.left, lrc.bottom - bmpArrowLl->bi.biHeight, lrc.left + bmpArrowLl->bi.biWidth, lrc.bottom);
						iBmp_bitBltMask(obj->bmp, &lrc2, bmpArrowLl);
CopyRect(&form->rcArrowLr, &lrc2);


					//////////
					// Form caption
					//////
						SetRect(&lrc2, lrc3.right + 8, lrc3.top + 1, lrc4.right - 8, lrc3.bottom + 1);
CopyRect(&form->rcCaption, &lrc2);
						lhfontOld = (HFONT)SelectObject(obj->bmp->hdc, gsWindowTitleBarFont->hfont);
						SetBkMode(obj->bmp->hdc, TRANSPARENT);
						SetTextColor(obj->bmp->hdc, (COLORREF)RGB(form->captionColor.red, form->captionColor.grn, form->captionColor.blu));
						DrawTextA(obj->bmp->hdc, form->caption.data, form->caption.length, &lrc2, DT_VCENTER);
						SelectObject(obj->bmp->hdc, lhfontOld);


					//////////
					// Copy to prior rendered bitmap
					//////
						// Make sure our bmpPriorRendered exists
						obj->bmpPriorRendered = iBmp_verifyCopyIsSameSize(obj->bmpPriorRendered, obj->bmp);

						// Copy to the prior rendered version
						lnPixelsRendered += iBmp_bitBlt(obj->bmpPriorRendered, &lrc, obj->bmp);
						// Right now, we can use the bmpPriorRendered for a fast copy rather than 

// 				} else {
// 					// Render from its prior rendered version
// 					lnPixelsRendered += iBmp_bitBlt(obj->bmp, &lrc, obj->bmpPriorRendered);
				}


//////////
// For temporary, we are adding additional renderings for _screen
//////
	if (obj == gobj_screen)
	{
		iEditChainManager_render(screenData, gobj_screen);
		if (gWinScreen)
			InvalidateRect(gWinScreen->hwnd, 0, FALSE);
	}


			//////////
			// Indicate we're no longer dirty, that we have everything
			//////
				obj->isDirty = false;
// s8 buffer[256];
// sprintf(buffer, "c:\\temp\\form_%u.bmp\0", (u32)obj);
// iBmp_saveToDisk(obj->bmp, buffer);


			//////////
			// Render any siblings
			//////
				if (tlRenderSiblings && obj->ll.next)
				{
					objSib = (SObject*)obj->ll.next;
					while (objSib)
					{
						// Render this sibling
						lnPixelsRendered += iObj_render(objSib, true, true);

						// Move to next sibling
						objSib = (SObject*)objSib->ll.next;
					}
				}
		}


		// Indicate how many pixels were drawn
		return(lnPixelsRendered);
	}




//////////
//
// Renders the subform, which traverses through all child objects and renders to the
// furthest extent before rendering itself.
//
// Note:  See "Note" on iRenderForm().
//
//////
	u32 iSubobj_renderSubform(SObject* obj, SSubObjSubform* subform, bool tlRenderChildren, bool tlRenderSiblings)
	{
		u32				lnPixelsRendered;
		SObject*		objSib;
		RECT			lrc, lrc2, lrc3;
		HFONT			lhfontOld;


		// Make sure our environment is sane
		lnPixelsRendered = 0;
		if (obj && subform && obj->rc.right > 0 && obj->rc.bottom > 0 && obj->rc.right >= obj->rc.left && obj->rc.bottom >= obj->rc.bottom && obj->rc.right - obj->rc.left < 4400 && obj->rc.bottom - obj->rc.top < 4400)
		{
			//////////
			// Make sure there is a bit bucket
			//////
				if (!obj->bmp)
				{
					// Initially allocate
					obj->bmp = iBmp_allocate();
					iBmp_createBySize(obj->bmp, obj->rc.right - obj->rc.left, obj->rc.bottom - obj->rc.top, 24);

				} else if (obj->bmp->bi.biWidth != obj->rc.right - obj->rc.left || obj->bmp->bi.biHeight != obj->rc.bottom - obj->rc.top) {
					// Resize
					obj->bmp = iBmp_verifySizeOrResize(obj->bmp, obj->rc.right - obj->rc.left, obj->rc.bottom - obj->rc.top);
				}


			//////////
			// Traverse and render any children
			//////
				if (tlRenderChildren && obj->firstChild)
					lnPixelsRendered += iObj_render(obj->firstChild, true, true);


			//////////
			// If we need re-rendering, re-render
			//////
				// The entire bmp
				SetRect(&lrc, 0, 0, obj->bmp->bi.biWidth, obj->bmp->bi.biHeight);

				// Do we need to redraw?  Or can we just copy?
				if (obj->isDirty || lnPixelsRendered != 0)
				{
					//////////
					// Frame it
					//////
						// Draw the window border
						iBmp_fillRect(obj->bmp, &lrc, subform->nwRgba, subform->neRgba, subform->swRgba, subform->seRgba, true);

						// Frame it
						CopyRect(&lrc2, &lrc);
						SetRect(&lrc2, lrc2.left - 1, lrc2.top - 1, lrc2.right + 1, lrc2.bottom + 1);
						iBmp_frameRect(obj->bmp, &lrc2, black, black, black, black, false);

						// Draw the client area
						SetRect(&lrc2, 0, subform->bmpSubformIcon->bi.biHeight - 1, lrc.right - 8, lrc.bottom);
						// Make everything white
						iBmp_fillRect(obj->bmp, &lrc2, white, white, white, white, false);
// These rc* copies were added temporarily until the full object structure is coded and working
//CopyRect(&subform->rcClient, &lrc2);
						// Put a border around the client area
						SetRect(&lrc2, -1, lrc2.top, lrc2.right, lrc2.bottom + 1);
//						iBmp_frameRect(obj->bmp, &lrc2, black, black, black, black, false);



					//////////
					// Subform icon and standard controls
					//////
						// Subform icon
						SetRect(&lrc3, 0, 0, subform->bmpSubformIcon->bi.biWidth + 8 + subform->bmpSubformIcon->bi.biWidth, subform->bmpSubformIcon->bi.biHeight);
						iBmp_bitBltMask(obj->bmp, &lrc3, subform->bmpSubformIcon);
CopyRect(&subform->rcIcon, &lrc3);

//////////
// Subforms don't currently have automatic close, maximize, minimize, or move buttons, but they can be added programmatically.
// I may change that in the future.  It will depend on how well they integrated into the JDebi Debugger.
// 						// Close
// 						SetRect(&lrc2,	lrc.right - bmpArrowUr->bi.biWidth - 8 - bmpClose->bi.biWidth, lrc.top + 1, lrc.right - bmpArrowUr->bi.biWidth - 8, lrc.bottom - 1);
// 						iBmp_bitBltMask(obj->bmp, &lrc2, bmpClose);
// CopyRect(&subform->rcClose, &lrc2);
// 
// 						// Maximize
// 						SetRect(&lrc2,	lrc2.left - bmpMaximize->bi.biWidth - 1, lrc2.top, lrc2.left - 1, lrc2.bottom);
// 						iBmp_bitBltMask(obj->bmp, &lrc2, bmpMaximize);
// CopyRect(&subform->rcMaximize, &lrc2);
// 
// 						// Minimize
// 						SetRect(&lrc2,	lrc2.left - bmpMinimize->bi.biWidth - 1, lrc2.top, lrc2.left - 1, lrc2.bottom);
// 						iBmp_bitBltMask(obj->bmp, &lrc2, bmpMinimize);
// CopyRect(&subform->rcMinimize, &lrc2);
// 
// 						// Move
// 						SetRect(&lrc4,	lrc2.left - bmpMove->bi.biWidth - 1, lrc2.top, lrc2.left - 1, lrc2.bottom);
// 						iBmp_bitBltMask(obj->bmp, &lrc4, bmpMove);
// CopyRect(&subform->rcMove, &lrc4);
//////


					//////////
					// Subform caption
					//////
						SetRect(&lrc2, subform->bmpSubformIcon->bi.biWidth + 8, lrc3.top + 2, obj->bmp->bi.biWidth - 8, lrc3.bottom);
CopyRect(&subform->rcCaption, &lrc2);
						lhfontOld = (HFONT)SelectObject(obj->bmp->hdc, gsWindowTitleBarFontSubform->hfont);
						SetBkMode(obj->bmp->hdc, TRANSPARENT);
						SetTextColor(obj->bmp->hdc, (COLORREF)RGB(subform->captionColor.red, subform->captionColor.grn, subform->captionColor.blu));
						DrawTextA(obj->bmp->hdc, subform->caption.data, subform->caption.length, &lrc2, DT_VCENTER);
						SelectObject(obj->bmp->hdc, lhfontOld);


//////////
// For temporary, we are adding additional renderings for the command subform
//////
if (iDatum_compare(&subform->caption, (s8*)cgcCommandTitle, -1) == 0)
{
	gobj_jdebi_command = obj;
	iEditChainManager_render(commandHistory, obj);
}


					//////////
					// Copy to prior rendered bitmap
					//////
						// Make sure our bmpPriorRendered exists
						obj->bmpPriorRendered = iBmp_verifyCopyIsSameSize(obj->bmpPriorRendered, obj->bmp);

						// Copy to the prior rendered version
						lnPixelsRendered += iBmp_bitBlt(obj->bmpPriorRendered, &lrc, obj->bmp);
						// Right now, we can use the bmpPriorRendered for a fast copy rather than 

// 				} else {
// 					// Render from its prior rendered version
// 					lnPixelsRendered += iBmp_bitBlt(obj->bmp, &lrc, obj->bmpPriorRendered);
				}


			//////////
			// Indicate we're no longer dirty, that we have everything
			//////
				obj->isDirty = false;
// s8 buffer[256];
// sprintf(buffer, "c:\\temp\\subform_%u.bmp\0", (u32)obj);
// iBmp_saveToDisk(obj->bmp, buffer);


			//////////
			// Render any siblings
			//////
				if (tlRenderSiblings && obj->ll.next)
				{
					objSib = (SObject*)obj->ll.next;
					while (objSib)
					{
						// Render this sibling
						lnPixelsRendered += iObj_render(objSib, true, true);

						// Move to next sibling
						objSib = (SObject*)objSib->ll.next;
					}
				}
		}

		// Indicate how many pixels were drawn
		return(lnPixelsRendered);
	}




//////////
//
// Renders the label, and traverses any child objects contained within to render them.
//
// Note:  See "Note" on iRenderForm().
//
//////
	u32 iSubobj_renderLabel(SObject* obj, SSubObjLabel* label, bool tlRenderChildren, bool tlRenderSiblings)
	{


			//////////
			// Indicate we're no longer dirty, that we have everything
			//////
				obj->isDirty = false;
		return(0);
	}




//////////
//
// Renders the textbox, and traverses any child objects contained within to render them.
//
// Note:  See "Note" on iRenderForm().
//
//////
	u32 iSubobj_renderTextbox(SObject* obj, SSubObjTextbox* textbox, bool tlRenderChildren, bool tlRenderSiblings)
	{


			//////////
			// Indicate we're no longer dirty, that we have everything
			//////
				obj->isDirty = false;
		return(0);
	}




//////////
//
// Renders the button, and traverses any child objects contained within to render them.
//
// Note:  See "Note" on iRenderForm().
//
//////
	u32 iSubobj_renderButton(SObject* obj, SSubObjButton* button, bool tlRenderChildren, bool tlRenderSiblings)
	{


			//////////
			// Indicate we're no longer dirty, that we have everything
			//////
				obj->isDirty = false;
		return(0);
	}




//////////
//
// Renders the editbox, and traverses any child objects contained within to render them.
//
// Note:  See "Note" on iRenderForm().
//
//////
	u32 iSubobj_renderEditbox(SObject* obj, SSubObjEditbox* editbox, bool tlRenderChildren, bool tlRenderSiblings)
	{


			//////////
			// Indicate we're no longer dirty, that we have everything
			//////
				obj->isDirty = false;
		return(0);
	}




//////////
//
// Renders the image, and traverses any child objects contained within to render them.
//
// Note:  See "Note" on iRenderForm().
//
//////
	u32 iSubobj_renderImage(SObject* obj, SSubObjImage* image, bool tlRenderChildren, bool tlRenderSiblings)
	{


			//////////
			// Indicate we're no longer dirty, that we have everything
			//////
				obj->isDirty = false;
		return(0);
	}




//////////
//
// Renders the checkbox, and traverses any child objects contained within to render them.
//
// Note:  See "Note" on iRenderForm().
//
//////
	u32 iSubobj_renderCheckbox(SObject* obj, SSubObjCheckbox* checkbox, bool tlRenderChildren, bool tlRenderSiblings)
	{


			//////////
			// Indicate we're no longer dirty, that we have everything
			//////
				obj->isDirty = false;
		return(0);
	}




//////////
//
// Renders the option, and traverses any child objects contained within to render them.
//
// Note:  See "Note" on iRenderForm().
//
//////
	u32 iSubobj_renderOption(SObject* obj, SSubObjOption* option, bool tlRenderChildren, bool tlRenderSiblings)
	{


			//////////
			// Indicate we're no longer dirty, that we have everything
			//////
				obj->isDirty = false;
		return(0);
	}




//////////
//
// Renders the radio, and traverses any child objects contained within to render them.
//
// Note:  See "Note" on iRenderForm().
//
//////
	u32 iSubobj_renderRadio(SObject* obj, SSubObjRadio* radio, bool tlRenderChildren, bool tlRenderSiblings)
	{


			//////////
			// Indicate we're no longer dirty, that we have everything
			//////
				obj->isDirty = false;
		return(0);
	}
