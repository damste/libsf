//////////
//
// /libsf/source/vjr/source/objects/create.cpp
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
//     Dec.18.2014
//////
// Change log:
//     Dec.18.2014 - Initial creation
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
// Creates the empty object structure
//
//////
	SObject* iSubobj_createEmpty(SObject* template_empty, SObject* parent)
	{
		SObject*	emptyNew;
		SVariable*	var;


		logfunc(__FUNCTION__);
		//////////
		// Create the indicated item
		//////
			emptyNew = (SObject*)malloc(sizeof(SObject));


		//////////
		// If successful, initialize it
		//////
			if (emptyNew)
			{
				// Initialize
				memset(emptyNew, 0, sizeof(SObject));

				// Initialize properties to VJr defaults
				emptyNew->objType		= _OBJ_TYPE_EMPTY;
				emptyNew->parent		= parent;
				iiSubobj_resetToDefaultEmpty(emptyNew, true, true, &gsProps_empty[0], gnProps_emptySize, &gsEvents_empty[0], gnEvents_emptySize);

				// Initially populate
				propSetEnabled(emptyNew, _LOGICAL_TRUE);
				emptyNew->isRendered	= true;
				emptyNew->isPublished	= true;
				var = iObjProp_get_var_byIndex(emptyNew, _INDEX_NAME);			iDatum_duplicate(&var->value, cgcName_empty, -1);
				var = iObjProp_get_var_byIndex(emptyNew, _INDEX_CLASS);			iDatum_duplicate(&var->value, cgcName_empty, -1);
				var = iObjProp_get_var_byIndex(emptyNew, _INDEX_BASECLASS);		iDatum_duplicate(&var->value, cgcName_empty, -1);

				// Events
				iEvents_resetToDefault(emptyNew, &gsEvents_empty[0], gnEvents_emptySize);

				// Initialize based on template
				if (template_empty)
					iiSubobj_copyEmpty(emptyNew, template_empty);		// Copy from indicated template
			}


		//////////
		// Indicate our success or failure
		//////
			return(emptyNew);
	}




//////////
//
// Creates the form object structure
//
//////
	SObject* iSubobj_createForm(SObject* template_form, SObject* parent)
	{
		SObject*	formNew;
		SObject*	icon;
		SObject*	caption;
		SObject*	move;
		SObject*	minimize;
		SObject*	maximize;
		SObject*	close;
		SObject*	scaleUl;
		SObject*	scaleUr;
		SObject*	scaleLr;
		SObject*	scaleLl;
		SVariable*	var;


		logfunc(__FUNCTION__);
		//////////
		// Create the indicated item
		//////
			formNew = (SObject*)malloc(sizeof(SObject));


		//////////
		// If successful, initialize it
		//////
			if (formNew)
			{
				// Initialize
				memset(formNew, 0, sizeof(SObject));

				// Initialize properties to VJr defaults
				formNew->objType	= _OBJ_TYPE_FORM;
				formNew->parent		= parent;


				//////////
				// Create the default children for this object
				//////
					icon		= iObj_addChild(_OBJ_TYPE_IMAGE, formNew);
					caption		= iObj_addChild(_OBJ_TYPE_LABEL, formNew);
					move		= iObj_addChild(_OBJ_TYPE_IMAGE, formNew);
					minimize	= iObj_addChild(_OBJ_TYPE_IMAGE, formNew);
					maximize	= iObj_addChild(_OBJ_TYPE_IMAGE, formNew);
					close		= iObj_addChild(_OBJ_TYPE_IMAGE, formNew);
					scaleUl		= iObj_addChild(_OBJ_TYPE_IMAGE, formNew);
					scaleUr		= iObj_addChild(_OBJ_TYPE_IMAGE, formNew);
					scaleLr		= iObj_addChild(_OBJ_TYPE_IMAGE, formNew);
					scaleLl		= iObj_addChild(_OBJ_TYPE_IMAGE, formNew);


				//////////
				// Give them proper names
				//////
					var = iObjProp_get_var_byIndex(icon,		_INDEX_NAME);		iDatum_duplicate(&var->value,	cgcName_icon,			-1);
					var = iObjProp_get_var_byIndex(caption,	_INDEX_NAME);		iDatum_duplicate(&var->value,	cgcName_caption,		-1);
					var = iObjProp_get_var_byIndex(move,		_INDEX_NAME);		iDatum_duplicate(&var->value,	cgcName_iconMove,		-1);
					var = iObjProp_get_var_byIndex(minimize,	_INDEX_NAME);		iDatum_duplicate(&var->value,	cgcName_iconMinimize,	-1);
					var = iObjProp_get_var_byIndex(maximize,	_INDEX_NAME);		iDatum_duplicate(&var->value,	cgcName_iconMaximize,	-1);
					var = iObjProp_get_var_byIndex(close,	_INDEX_NAME);		iDatum_duplicate(&var->value,	cgcName_iconClose,		-1);
					var = iObjProp_get_var_byIndex(scaleUl,	_INDEX_NAME);		iDatum_duplicate(&var->value,	cgcName_iconScaleUl,	-1);
					var = iObjProp_get_var_byIndex(scaleUr,	_INDEX_NAME);		iDatum_duplicate(&var->value,	cgcName_iconScaleUr,	-1);
					var = iObjProp_get_var_byIndex(scaleLr,	_INDEX_NAME);		iDatum_duplicate(&var->value,	cgcName_iconScaleLr,	-1);
					var = iObjProp_get_var_byIndex(scaleLl,	_INDEX_NAME);		iDatum_duplicate(&var->value,	cgcName_iconScaleLl,	-1);


				//////////
				// Default initialization
				//////
					iiSubobj_resetToDefaultForm(formNew, true, true, &gsProps_form[0], gnProps_formSize, &gsEvents_form[0], gnEvents_formSize);


				// Initially populate
				propSetEnabled(formNew, _LOGICAL_TRUE);
				formNew->isRendered		= true;
				formNew->isPublished	= true;
				var = iObjProp_get_var_byIndex(formNew, _INDEX_NAME);			iDatum_duplicate(&var->value, cgcName_form, -1);
				var = iObjProp_get_var_byIndex(formNew, _INDEX_CLASS);			iDatum_duplicate(&var->value, cgcName_form, -1);
				var = iObjProp_get_var_byIndex(formNew, _INDEX_BASECLASS);		iDatum_duplicate(&var->value, cgcName_form, -1);
				iEvents_resetToDefault(formNew, &gsEvents_form[0], gnEvents_formSize);
				iObj_setSize(formNew, 0, 0, 375, 250);

				// Initialize based on template
				if (template_form)
					iiSubobj_copyForm(formNew, template_form);		// Copy from indicated template
			}


		//////////
		// Indicate our success or failure
		//////
			return(formNew);
	}




//////////
//
// Creates the subform object structure
//
//////
	SObject* iSubobj_createSubform(SObject* template_subform, SObject* parent)
	{
		SObject*	subformNew;
		SObject*	icon;
		SObject*	caption;
		SVariable*	var;


		logfunc(__FUNCTION__);
		//////////
		// Create the indicated item
		//////
			subformNew = (SObject*)malloc(sizeof(SObject));


		//////////
		// If successful, initialize it
		//////
			if (subformNew)
			{
				// Initialize
				memset(subformNew, 0, sizeof(SObject));

				// Initialize properties to VJr defaults
				subformNew->objType		= _OBJ_TYPE_SUBFORM;
				subformNew->parent		= parent;


				//////////
				// Create the default children for this object
				//////
					icon		= iObj_addChild(_OBJ_TYPE_IMAGE, subformNew);
					caption		= iObj_addChild(_OBJ_TYPE_LABEL, subformNew);


				//////////
				// Give them proper names
				//////
					var = iObjProp_get_var_byIndex(icon,		_INDEX_NAME);		iDatum_duplicate(&var->value,	cgcName_icon,		-1);
					var = iObjProp_get_var_byIndex(caption,	_INDEX_NAME);		iDatum_duplicate(&var->value,	cgcName_caption,	-1);


				//////////
				// Default initialization
				//////
					iiSubobj_resetToDefaultSubform(subformNew, true, true, &gsProps_subform[0], gnProps_subformSize, &gsEvents_subform[0], gnEvents_subformSize);

				// Initially populate
				propSetEnabled(subformNew, _LOGICAL_TRUE);
				subformNew->isRendered	= true;
				subformNew->isPublished	= true;
				var = iObjProp_get_var_byIndex(subformNew, _INDEX_NAME);				iDatum_duplicate(&var->value, cgcName_subform, -1);
				var = iObjProp_get_var_byIndex(subformNew, _INDEX_CLASS);			iDatum_duplicate(&var->value, cgcName_subform, -1);
				var = iObjProp_get_var_byIndex(subformNew, _INDEX_BASECLASS);		iDatum_duplicate(&var->value, cgcName_subform, -1);
				iEvents_resetToDefault(subformNew, &gsEvents_subform[0], gnEvents_subformSize);
				iObj_setSize(subformNew, 0, 0, 200, 100);

				// Initialize based on template
				if (template_subform)
					iiSubobj_copySubform(subformNew, template_subform);		// Copy from indicated template
			}


		//////////
		// Indicate our success or failure
		//////
			return(subformNew);
	}




//////////
//
// Creates the carousel object structure
//
//////
	SObject* iSubobj_createCarousel(SObject* template_carousel, SObject* parent)
	{
		SObject*	carouselNew;
		SObject*	icon;
		SObject*	caption;
		SObject*	carouselIcon;
		SObject*	close;
		SVariable*	var;


		logfunc(__FUNCTION__);
		//////////
		// Create the indicated item
		//////
			carouselNew = (SObject*)malloc(sizeof(SObject));


		//////////
		// If successful, initialize it
		//////
			if (carouselNew)
			{
				// Initialize
				memset(carouselNew, 0, sizeof(SObject));

				// Initialize properties to VJr defaults
				carouselNew->objType		= _OBJ_TYPE_CAROUSEL;
				carouselNew->parent			= parent;


				//////////
				// Create the default children for this object
				//////
					icon			= iObj_addChild(_OBJ_TYPE_IMAGE, carouselNew);
					caption			= iObj_addChild(_OBJ_TYPE_LABEL, carouselNew);
					carouselIcon	= iObj_addChild(_OBJ_TYPE_IMAGE, carouselNew);
					close			= iObj_addChild(_OBJ_TYPE_IMAGE, carouselNew);


				//////////
				// Give them proper names
				//////
					var = iObjProp_get_var_byIndex(icon,			_INDEX_NAME);		iDatum_duplicate(&var->value,	cgcName_icon,			-1);
					var = iObjProp_get_var_byIndex(caption,		_INDEX_NAME);		iDatum_duplicate(&var->value,	cgcName_caption,		-1);
					var = iObjProp_get_var_byIndex(carouselIcon,	_INDEX_NAME);		iDatum_duplicate(&var->value,	cgcName_iconCarousel,	-1);
					var = iObjProp_get_var_byIndex(close,		_INDEX_NAME);		iDatum_duplicate(&var->value,	cgcName_iconClose,		-1);


				//////////
				// Default initialization
				//////
					iiSubobj_resetToDefaultCarousel(carouselNew, true, true, &gsProps_carousel[0], gnProps_carouselSize, &gsEvents_carousel[0], gnEvents_carouselSize);


				// Initially populate
				propSetEnabled(carouselNew, _LOGICAL_TRUE);
				carouselNew->isRendered		= true;
				carouselNew->isPublished	= true;
				var = iObjProp_get_var_byIndex(carouselNew, _INDEX_NAME);			iDatum_duplicate(&var->value, cgcName_carousel, -1);
				var = iObjProp_get_var_byIndex(carouselNew, _INDEX_CLASS);			iDatum_duplicate(&var->value, cgcName_carousel, -1);
				var = iObjProp_get_var_byIndex(carouselNew, _INDEX_BASECLASS);		iDatum_duplicate(&var->value, cgcName_carousel, -1);
				iEvents_resetToDefault(carouselNew, &gsEvents_carousel[0], gnEvents_carouselSize);
				iObj_setSize(carouselNew, 0, 0, 320, 480);

				// Initialize based on template
				if (template_carousel)
					iiSubobj_copyCarousel(carouselNew, template_carousel);		// Copy from indicated template
			}


		//////////
		// Indicate our success or failure
		//////
			return(carouselNew);
	}




//////////
//
// Creates the rider object structure
//
//////
	SObject* iSubobj_createRider(SObject* template_rider, SObject* parent)
	{
		SObject*	riderNew;
		SVariable*	var;


		logfunc(__FUNCTION__);
		//////////
		// Create the indicated item
		//////
			riderNew = (SObject*)malloc(sizeof(SObject));


		//////////
		// If successful, initialize it
		//////
			if (riderNew)
			{
				// Initialize
				memset(riderNew, 0, sizeof(SObject));

				// Initialize properties to VJr defaults
				riderNew->objType		= _OBJ_TYPE_RIDER;
				riderNew->parent		= parent;
				iiSubobj_resetToDefaultRider(riderNew, true, true, &gsProps_rider[0], gnProps_riderSize, &gsEvents_rider[0], gnEvents_riderSize);

				// Initially populate
				propSetEnabled(riderNew, _LOGICAL_TRUE);
				riderNew->isRendered	= true;
				riderNew->isPublished	= true;
				var = iObjProp_get_var_byIndex(riderNew, _INDEX_NAME);			iDatum_duplicate(&var->value, cgcName_rider, -1);
				var = iObjProp_get_var_byIndex(riderNew, _INDEX_CLASS);			iDatum_duplicate(&var->value, cgcName_rider, -1);
				var = iObjProp_get_var_byIndex(riderNew, _INDEX_BASECLASS);		iDatum_duplicate(&var->value, cgcName_rider, -1);
				iEvents_resetToDefault(riderNew, &gsEvents_rider[0], gnEvents_riderSize);
				iObj_setSize(riderNew, 0, 0, 320, 480);

				// Initialize based on template
				if (template_rider)
					iiSubobj_copyRider(riderNew, template_rider);		// Copy from indicated template
			}


		//////////
		// Indicate our success or failure
		//////
			return(riderNew);
	}




//////////
//
// Creates the label object structure
//
//////
	SObject* iSubobj_createLabel(SObject* template_label, SObject* parent)
	{
		SObject*	labelNew;
		SVariable*	var;


		logfunc(__FUNCTION__);
		//////////
		// Create the indicated item
		//////
			labelNew = (SObject*)malloc(sizeof(SObject));


		//////////
		// If successful, initialize it
		//////
			if (labelNew)
			{
				// Initialize
				memset(labelNew, 0, sizeof(SObject));

				// Initialize properties to VJr defaults
				labelNew->objType		= _OBJ_TYPE_LABEL;
				labelNew->parent		= parent;
				iiSubobj_resetToDefaultLabel(labelNew, true, true, &gsProps_label[0], gnProps_labelSize, &gsEvents_label[0], gnEvents_labelSize);

				// Initially populate
				propSetEnabled(labelNew, _LOGICAL_TRUE);
				labelNew->isRendered	= true;
				labelNew->isPublished	= true;
				var = iObjProp_get_var_byIndex(labelNew, _INDEX_NAME);			iDatum_duplicate(&var->value, cgcName_label, -1);
				var = iObjProp_get_var_byIndex(labelNew, _INDEX_CLASS);			iDatum_duplicate(&var->value, cgcName_label, -1);
				var = iObjProp_get_var_byIndex(labelNew, _INDEX_BASECLASS);		iDatum_duplicate(&var->value, cgcName_label, -1);
				iEvents_resetToDefault(labelNew, &gsEvents_label[0], gnEvents_labelSize);
				iObj_setSize(labelNew, 0, 0, 40, 17);

				// Initialize based on template
				if (template_label)
					iiSubobj_copyLabel(labelNew, template_label);		// Copy from indicated template
			}


		//////////
		// Indicate our success or failure
		//////
			return(labelNew);
	}




//////////
//
// Creates the textbox object structure
//
//////
	SObject* iSubobj_createTextbox(SObject* template_textbox, SObject* parent)
	{
		SObject*	textboxNew;
		SVariable*	var;


		logfunc(__FUNCTION__);
		//////////
		// Create the indicated item
		//////
			textboxNew = (SObject*)malloc(sizeof(SObject));


		//////////
		// If successful, initialize it
		//////
			if (textboxNew)
			{
				// Initialize
				memset(textboxNew, 0, sizeof(SObject));

				// Initialize properties to VJr defaults
				textboxNew->objType		= _OBJ_TYPE_TEXTBOX;
				textboxNew->parent		= parent;
				iiSubobj_resetToDefaultTextbox(textboxNew, true, true, &gsProps_textbox[0], gnProps_textboxSize, &gsEvents_textbox[0], gnEvents_textboxSize);

				// Initially populate
				propSetEnabled(textboxNew, _LOGICAL_TRUE);
				textboxNew->isRendered	= true;
				textboxNew->isPublished	= true;
				var = iObjProp_get_var_byIndex(textboxNew, _INDEX_NAME);				iDatum_duplicate(&var->value, cgcName_textbox, -1);
				var = iObjProp_get_var_byIndex(textboxNew, _INDEX_CLASS);			iDatum_duplicate(&var->value, cgcName_textbox, -1);
				var = iObjProp_get_var_byIndex(textboxNew, _INDEX_BASECLASS);		iDatum_duplicate(&var->value, cgcName_textbox, -1);
				iEvents_resetToDefault(textboxNew, &gsEvents_textbox[0], gnEvents_textboxSize);
				iObj_setSize(textboxNew, 0, 0, 100, 23);

				// Initialize based on template
				if (template_textbox)
					iiSubobj_copyTextbox(textboxNew, template_textbox);		// Copy from indicated template
			}


		//////////
		// Indicate our success or failure
		//////
			return(textboxNew);
	}




//////////
//
// Creates the button object structure
//
//////
	SObject* iSubobj_createButton(SObject* template_button, SObject* parent)
	{
		SObject*	buttonNew;
		SVariable*	var;


		logfunc(__FUNCTION__);
		//////////
		// Create the indicated item
		//////
			buttonNew = (SObject*)malloc(sizeof(SObject));


		//////////
		// If successful, initialize it
		//////
			if (buttonNew)
			{
				// Initialize
				memset(buttonNew, 0, sizeof(SObject));

				// Initialize properties to VJr defaults
				buttonNew->objType		= _OBJ_TYPE_BUTTON;
				buttonNew->parent		= parent;
				iiSubobj_resetToDefaultButton(buttonNew, true, true, &gsProps_button[0], gnProps_buttonSize, &gsEvents_button[0], gnEvents_buttonSize);

				// Initially populate
				propSetEnabled(buttonNew, _LOGICAL_TRUE);
				buttonNew->isRendered	= true;
				buttonNew->isPublished	= true;
				var = iObjProp_get_var_byIndex(buttonNew, _INDEX_NAME);			iDatum_duplicate(&var->value, cgcName_button, -1);
				var = iObjProp_get_var_byIndex(buttonNew, _INDEX_CLASS);			iDatum_duplicate(&var->value, cgcName_button, -1);
				var = iObjProp_get_var_byIndex(buttonNew, _INDEX_BASECLASS);		iDatum_duplicate(&var->value, cgcName_button, -1);
				iEvents_resetToDefault(buttonNew, &gsEvents_button[0], gnEvents_buttonSize);
				iObj_setSize(buttonNew, 0, 0, 84, 27);

				// Initialize based on template
				if (template_button)
					iiSubobj_copyButton(buttonNew, template_button);		// Copy from indicated template
			}


		//////////
		// Indicate our success or failure
		//////
			return(buttonNew);
	}




//////////
//
// Creates the editbox object structure
//
//////
	SObject* iSubobj_createEditbox(SObject* template_editbox, SObject* parent)
	{
		SObject*	editboxNew;
		SVariable*	var;


		logfunc(__FUNCTION__);
		//////////
		// Create the indicated item
		//////
			editboxNew = (SObject*)malloc(sizeof(SObject));


		//////////
		// If successful, initialize it
		//////
			if (editboxNew)
			{
				// Initialize
				memset(editboxNew, 0, sizeof(SObject));

				// Initialize properties to VJr defaults
				editboxNew->objType		= _OBJ_TYPE_EDITBOX;
				editboxNew->parent		= parent;
				iiSubobj_resetToDefaultEditbox(editboxNew, true, true, &gsProps_editbox[0], gnProps_editboxSize, &gsEvents_editbox[0], gnEvents_editboxSize);

				// Initially populate
				propSetEnabled(editboxNew, _LOGICAL_TRUE);
				editboxNew->isRendered	= true;
				editboxNew->isPublished	= true;
				var = iObjProp_get_var_byIndex(editboxNew, _INDEX_NAME);				iDatum_duplicate(&var->value, cgcName_editbox, -1);
				var = iObjProp_get_var_byIndex(editboxNew, _INDEX_CLASS);			iDatum_duplicate(&var->value, cgcName_editbox, -1);
				var = iObjProp_get_var_byIndex(editboxNew, _INDEX_BASECLASS);		iDatum_duplicate(&var->value, cgcName_editbox, -1);
				iEvents_resetToDefault(editboxNew, &gsEvents_editbox[0], gnEvents_editboxSize);
				iObj_setSize(editboxNew, 0, 0, 100, 53);

				// Initialize based on template
				if (template_editbox)
					iiSubobj_copyEditbox(editboxNew, template_editbox);		// Copy from indicated template
			}


		//////////
		// Indicate our success or failure
		//////
			return(editboxNew);
	}




//////////
//
// Creates the image object structure
//
//////
	SObject* iSubobj_createImage(SObject* template_image, SObject* parent)
	{
		SObject*	imageNew;
		SVariable*	var;


		logfunc(__FUNCTION__);
		//////////
		// Create the indicated item
		//////
			imageNew = (SObject*)malloc(sizeof(SObject));


		//////////
		// If successful, initialize it
		//////
			if (imageNew)
			{
				// Initialize
				memset(imageNew, 0, sizeof(SObject));

				// Initialize properties to VJr defaults
				imageNew->objType		= _OBJ_TYPE_IMAGE;
				imageNew->parent		= parent;
				iiSubobj_resetToDefaultImage(imageNew, true, true, &gsProps_image[0], gnProps_imageSize, &gsEvents_image[0], gnEvents_imageSize);

				// Initially populate
				propSetEnabled(imageNew, _LOGICAL_TRUE);
				imageNew->isRendered	= true;
				imageNew->isPublished	= true;
				var = iObjProp_get_var_byIndex(imageNew, _INDEX_NAME);			iDatum_duplicate(&var->value, cgcName_image, -1);
				var = iObjProp_get_var_byIndex(imageNew, _INDEX_CLASS);			iDatum_duplicate(&var->value, cgcName_image, -1);
				var = iObjProp_get_var_byIndex(imageNew, _INDEX_BASECLASS);		iDatum_duplicate(&var->value, cgcName_image, -1);
				iEvents_resetToDefault(imageNew, &gsEvents_image[0], gnEvents_imageSize);
				iObj_setSize(imageNew, 0, 0, 100, 36);

				// Initialize based on template
				if (template_image)
					iiSubobj_copyImage(imageNew, template_image);		// Copy from indicated template
			}


		//////////
		// Indicate our success or failure
		//////
			return(imageNew);
	}




//////////
//
// Creates the checkbox object structure
//
//////
	SObject* iSubobj_createCheckbox(SObject* template_checkbox, SObject* parent)
	{
		SObject*	checkboxNew;
		SObject*	image;
		SObject*	label;
		SVariable*	var;


		logfunc(__FUNCTION__);
		//////////
		// Create the indicated item
		//////
			checkboxNew = (SObject*)malloc(sizeof(SObject));


		//////////
		// If successful, initialize it
		//////
			if (checkboxNew)
			{
				// Initialize
				memset(checkboxNew, 0, sizeof(SObject));

				// Initialize properties to VJr defaults
				checkboxNew->objType		= _OBJ_TYPE_CHECKBOX;
				checkboxNew->parent			= parent;


				//////////
				// Create the default children for this object
				//////
					image	= iObj_addChild(_OBJ_TYPE_IMAGE, checkboxNew);
					label	= iObj_addChild(_OBJ_TYPE_LABEL, checkboxNew);


				//////////
				// Give them proper names
				//////
					var = iObjProp_get_var_byIndex(image,	_INDEX_NAME);			iDatum_duplicate(&var->value,	cgcName_checkboxImage,	-1);
					var = iObjProp_get_var_byIndex(label,	_INDEX_NAME);			iDatum_duplicate(&var->value,	cgcName_checkboxLabel,	-1);


				//////////
				// Default initialization
				//////
					iiSubobj_resetToDefaultCheckbox(checkboxNew, true, true, &gsProps_checkbox[0], gnProps_checkboxSize, &gsEvents_checkbox[0], gnEvents_checkboxSize);


				// Initially populate
				propSetEnabled(checkboxNew, _LOGICAL_TRUE);
				checkboxNew->isRendered		= true;
				checkboxNew->isPublished	= true;
				var = iObjProp_get_var_byIndex(checkboxNew, _INDEX_NAME);			iDatum_duplicate(&var->value, cgcName_checkbox, -1);
				var = iObjProp_get_var_byIndex(checkboxNew, _INDEX_CLASS);			iDatum_duplicate(&var->value, cgcName_checkbox, -1);
				var = iObjProp_get_var_byIndex(checkboxNew, _INDEX_BASECLASS);		iDatum_duplicate(&var->value, cgcName_checkbox, -1);
				iEvents_resetToDefault(checkboxNew, &gsEvents_checkbox[0], gnEvents_checkboxSize);
				iObj_setSize(checkboxNew, 0, 0, 60, 17);

				// Initialize based on template
				if (template_checkbox)
					iiSubobj_copyCheckbox(checkboxNew, template_checkbox);		// Copy from indicated template
			}


		//////////
		// Indicate our success or failure
		//////
			return(checkboxNew);
	}




//////////
//
// Creates the combo object structure
//
//////
	SObject* iSubobj_createOption(SObject* template_option, SObject* parent)
	{
		SObject*	optionNew;
		SVariable*	var;


		logfunc(__FUNCTION__);
		//////////
		// Create the indicated item
		//////
			optionNew = (SObject*)malloc(sizeof(SObject));


		//////////
		// If successful, initialize it
		//////
			if (optionNew)
			{
				// Initialize
				memset(optionNew, 0, sizeof(SObject));

				// Initialize properties to VJr defaults
				optionNew->objType		= _OBJ_TYPE_OPTION;
				optionNew->parent		= parent;
				iiSubobj_resetToDefaultOption(optionNew, true, true, &gsProps_option[0], gnProps_optionSize, &gsEvents_option[0], gnEvents_optionSize);

				// Initially populate
				propSetEnabled(optionNew, _LOGICAL_TRUE);
				optionNew->isRendered	= true;
				optionNew->isPublished	= true;
				var = iObjProp_get_var_byIndex(optionNew, _INDEX_NAME);			iDatum_duplicate(&var->value, cgcName_option, -1);
				var = iObjProp_get_var_byIndex(optionNew, _INDEX_CLASS);			iDatum_duplicate(&var->value, cgcName_option, -1);
				var = iObjProp_get_var_byIndex(optionNew, _INDEX_BASECLASS);		iDatum_duplicate(&var->value, cgcName_option, -1);
				iEvents_resetToDefault(optionNew, &gsEvents_option[0], gnEvents_optionSize);
				iObj_setSize(optionNew, 0, 0, 60, 40);

				// Initialize based on template
				if (template_option)
					iiSubobj_copyOption(optionNew, template_option);		// Copy from indicated template
			}


		//////////
		// Indicate our success or failure
		//////
			return(optionNew);
	}




//////////
//
// Creates the radio object structure
//
//////
	SObject* iSubobj_createRadio(SObject* template_radio, SObject* parent)
	{
		SObject*	radioNew;
		SVariable*	var;


		logfunc(__FUNCTION__);
		//////////
		// Create the indicated item
		//////
			radioNew = (SObject*)malloc(sizeof(SObject));


		//////////
		// If successful, initialize it
		//////
			if (radioNew)
			{
				// Initialize
				memset(radioNew, 0, sizeof(SObject));

				// Initialize properties to VJr defaults
				radioNew->objType		= _OBJ_TYPE_RADIO;
				radioNew->parent		= parent;
				iiSubobj_resetToDefaultRadio(radioNew, true, true, &gsProps_radio[0], gnProps_radioSize, &gsEvents_radio[0], gnEvents_radioSize);

				// Initially populate
				propSetEnabled(radioNew, _LOGICAL_TRUE);
				radioNew->isRendered	= true;
				radioNew->isPublished	= true;
				var = iObjProp_get_var_byIndex(radioNew, _INDEX_NAME);			iDatum_duplicate(&var->value, cgcName_radio, -1);
				var = iObjProp_get_var_byIndex(radioNew, _INDEX_CLASS);			iDatum_duplicate(&var->value, cgcName_radio, -1);
				var = iObjProp_get_var_byIndex(radioNew, _INDEX_BASECLASS);		iDatum_duplicate(&var->value, cgcName_radio, -1);
				iEvents_resetToDefault(radioNew, &gsEvents_radio[0], gnEvents_radioSize);
				iObj_setSize(radioNew, 0, 0, 100, 100);

				// Initialize based on template
				if (template_radio)
					iiSubobj_copyRadio(radioNew, template_radio);		// Copy from indicated template
			}


		//////////
		// Indicate our success or failure
		//////
			return(radioNew);
	}




//////////
//
// Creates the cmdGroup structure
//
//////
	SObject* iSubobj_createCmdGroup(SObject* template_cmdGroup, SObject* parent)
	{
		SObject*	cmdGroupNew;
		SVariable*	var;


		logfunc(__FUNCTION__);
		//////////
		// Create the indicated item
		//////
			cmdGroupNew = (SObject*)malloc(sizeof(SObject));


		//////////
		// If successful, initialize it
		//////
			if (cmdGroupNew)
			{
				// Initialize
				memset(cmdGroupNew, 0, sizeof(SObject));

				// Initialize properties to VJr defaults
				cmdGroupNew->objType	= _OBJ_TYPE_CMDGROUP;
				cmdGroupNew->parent		= parent;
				iiSubobj_resetToDefaultCmdGroup(cmdGroupNew, true, true, &gsProps_cmdgroup[0], gnProps_cmdgroupSize, &gsEvents_cmdgroup[0], gnEvents_cmdgroupSize);

				// Initially populate
				propSetEnabled(cmdGroupNew, _LOGICAL_TRUE);
				cmdGroupNew->isRendered		= true;
				cmdGroupNew->isPublished	= true;
				var = iObjProp_get_var_byIndex(cmdGroupNew, _INDEX_NAME);			iDatum_duplicate(&var->value, cgcName_cmdgroup, -1);
				var = iObjProp_get_var_byIndex(cmdGroupNew, _INDEX_CLASS);			iDatum_duplicate(&var->value, cgcName_cmdgroup, -1);
				var = iObjProp_get_var_byIndex(cmdGroupNew, _INDEX_BASECLASS);		iDatum_duplicate(&var->value, cgcName_cmdgroup, -1);
				iEvents_resetToDefault(cmdGroupNew, &gsEvents_cmdgroup[0], gnEvents_cmdgroupSize);
				iObj_setSize(cmdGroupNew, 0, 0, 100, 100);

				// Initialize based on template
				if (template_cmdGroup)
					iiSubobj_copyCmdGroup(cmdGroupNew, template_cmdGroup);		// Copy from indicated template
			}


		//////////
		// Indicate our success or failure
		//////
			return(cmdGroupNew);
	}




//////////
//
// Creates the optGroup structure
//
//////
	SObject* iSubobj_createOptGroup(SObject* template_optGroup, SObject* parent)
	{
		SObject*	optGroupNew;
		SVariable*	var;


		logfunc(__FUNCTION__);
		//////////
		// Create the indicated item
		//////
			optGroupNew = (SObject*)malloc(sizeof(SObject));


		//////////
		// If successful, initialize it
		//////
			if (optGroupNew)
			{
				// Initialize
				memset(optGroupNew, 0, sizeof(SObject));

				// Initialize properties to VJr defaults
				optGroupNew->objType	= _OBJ_TYPE_OPTGROUP;
				optGroupNew->parent		= parent;
				iiSubobj_resetToDefaultOptGroup(optGroupNew, true, true, &gsProps_optgroup[0], gnProps_optgroupSize, &gsEvents_optgroup[0], gnEvents_optgroupSize);

				// Initially populate
				propSetEnabled(optGroupNew, _LOGICAL_TRUE);
				optGroupNew->isRendered		= true;
				optGroupNew->isPublished	= true;
				var = iObjProp_get_var_byIndex(optGroupNew, _INDEX_NAME);			iDatum_duplicate(&var->value, cgcName_optgroup, -1);
				var = iObjProp_get_var_byIndex(optGroupNew, _INDEX_CLASS);			iDatum_duplicate(&var->value, cgcName_optgroup, -1);
				var = iObjProp_get_var_byIndex(optGroupNew, _INDEX_BASECLASS);		iDatum_duplicate(&var->value, cgcName_optgroup, -1);
				iEvents_resetToDefault(optGroupNew, &gsEvents_optgroup[0], gnEvents_optgroupSize);
				iObj_setSize(optGroupNew, 0, 0, 100, 100);

				// Initialize based on template
				if (template_optGroup)
					iiSubobj_copyOptGroup(optGroupNew, template_optGroup);		// Copy from indicated template
			}


		//////////
		// Indicate our success or failure
		//////
			return(optGroupNew);
	}




//////////
//
// Creates the listbox structure
//
//////
	SObject* iSubobj_createListbox(SObject* template_listbox, SObject* parent)
	{
		SObject*	listboxNew;
		SVariable*	var;


		logfunc(__FUNCTION__);
		//////////
		// Create the indicated item
		//////
			listboxNew = (SObject*)malloc(sizeof(SObject));


		//////////
		// If successful, initialize it
		//////
			if (listboxNew)
			{
				// Initialize
				memset(listboxNew, 0, sizeof(SObject));

				// Initialize properties to VJr defaults
				listboxNew->objType	= _OBJ_TYPE_LISTBOX;
				listboxNew->parent		= parent;
				iiSubobj_resetToDefaultListbox(listboxNew, true, true, &gsProps_listbox[0], gnProps_listboxSize, &gsEvents_listbox[0], gnEvents_listboxSize);

				// Initially populate
				propSetEnabled(listboxNew, _LOGICAL_TRUE);
				listboxNew->isRendered		= true;
				listboxNew->isPublished		= true;
				var = iObjProp_get_var_byIndex(listboxNew, _INDEX_NAME);			iDatum_duplicate(&var->value, cgcName_listbox, -1);
				var = iObjProp_get_var_byIndex(listboxNew, _INDEX_CLASS);		iDatum_duplicate(&var->value, cgcName_listbox, -1);
				var = iObjProp_get_var_byIndex(listboxNew, _INDEX_BASECLASS);	iDatum_duplicate(&var->value, cgcName_listbox, -1);
				iEvents_resetToDefault(listboxNew, &gsEvents_listbox[0], gnEvents_listboxSize);
				iObj_setSize(listboxNew, 0, 0, 100, 100);

				// Initialize based on template
				if (template_listbox)
					iiSubobj_copyListbox(listboxNew, template_listbox);		// Copy from indicated template
			}


		//////////
		// Indicate our success or failure
		//////
			return(listboxNew);
	}




//////////
//
// Creates the combobox structure
//
//////
	SObject* iSubobj_createCombobox(SObject* template_combobox, SObject* parent)
	{
		SObject*	comboboxNew;
		SVariable*	var;


		logfunc(__FUNCTION__);
		//////////
		// Create the indicated item
		//////
			comboboxNew = (SObject*)malloc(sizeof(SObject));


		//////////
		// If successful, initialize it
		//////
			if (comboboxNew)
			{
				// Initialize
				memset(comboboxNew, 0, sizeof(SObject));

				// Initialize properties to VJr defaults
				comboboxNew->objType	= _OBJ_TYPE_COMBOBOX;
				comboboxNew->parent		= parent;
				iiSubobj_resetToDefaultCombobox(comboboxNew, true, true, &gsProps_combobox[0], gnProps_comboboxSize, &gsEvents_combobox[0], gnEvents_comboboxSize);

				// Initially populate
				propSetEnabled(comboboxNew, _LOGICAL_TRUE);
				comboboxNew->isRendered		= true;
				comboboxNew->isPublished	= true;
				var = iObjProp_get_var_byIndex(comboboxNew, _INDEX_NAME);			iDatum_duplicate(&var->value, cgcName_combobox, -1);
				var = iObjProp_get_var_byIndex(comboboxNew, _INDEX_CLASS);			iDatum_duplicate(&var->value, cgcName_combobox, -1);
				var = iObjProp_get_var_byIndex(comboboxNew, _INDEX_BASECLASS);		iDatum_duplicate(&var->value, cgcName_combobox, -1);
				iEvents_resetToDefault(comboboxNew, &gsEvents_combobox[0], gnEvents_comboboxSize);
				iObj_setSize(comboboxNew, 0, 0, 100, 100);

				// Initialize based on template
				if (template_combobox)
					iiSubobj_copyCombobox(comboboxNew, template_combobox);		// Copy from indicated template
			}


		//////////
		// Indicate our success or failure
		//////
			return(comboboxNew);
	}




//////////
//
// Creates the formset structure
//
//////
	SObject* iSubobj_createFormset(SObject* template_formset, SObject* parent)
	{
		SObject*	formsetNew;
		SVariable*	var;


		logfunc(__FUNCTION__);
		//////////
		// Create the indicated item
		//////
			formsetNew = (SObject*)malloc(sizeof(SObject));


		//////////
		// If successful, initialize it
		//////
			if (formsetNew)
			{
				// Initialize
				memset(formsetNew, 0, sizeof(SObject));

				// Initialize properties to VJr defaults
				formsetNew->objType	= _OBJ_TYPE_FORMSET;
				formsetNew->parent		= parent;
				iiSubobj_resetToDefaultFormset(formsetNew, true, true, &gsProps_formset[0], gnProps_formsetSize, &gsEvents_formset[0], gnEvents_formsetSize);

				// Initially populate
				propSetEnabled(formsetNew, _LOGICAL_TRUE);
				formsetNew->isRendered		= true;
				formsetNew->isPublished		= true;
				var = iObjProp_get_var_byIndex(formsetNew, _INDEX_NAME);			iDatum_duplicate(&var->value, cgcName_formset, -1);
				var = iObjProp_get_var_byIndex(formsetNew, _INDEX_CLASS);		iDatum_duplicate(&var->value, cgcName_formset, -1);
				var = iObjProp_get_var_byIndex(formsetNew, _INDEX_BASECLASS);	iDatum_duplicate(&var->value, cgcName_formset, -1);
				iEvents_resetToDefault(formsetNew, &gsEvents_formset[0], gnEvents_formsetSize);
				iObj_setSize(formsetNew, 0, 0, 100, 100);

				// Initialize based on template
				if (template_formset)
					iiSubobj_copyFormset(formsetNew, template_formset);		// Copy from indicated template
			}


		//////////
		// Indicate our success or failure
		//////
			return(formsetNew);
	}




//////////
//
// Creates the toolbar structure
//
//////
	SObject* iSubobj_createToolbar(SObject* template_toolbar, SObject* parent)
	{
		SObject*	toolbarNew;
		SVariable*	var;


		logfunc(__FUNCTION__);
		//////////
		// Create the indicated item
		//////
			toolbarNew = (SObject*)malloc(sizeof(SObject));


		//////////
		// If successful, initialize it
		//////
			if (toolbarNew)
			{
				// Initialize
				memset(toolbarNew, 0, sizeof(SObject));

				// Initialize properties to VJr defaults
				toolbarNew->objType		= _OBJ_TYPE_TOOLBAR;
				toolbarNew->parent		= parent;
				iiSubobj_resetToDefaultToolbar(toolbarNew, true, true, &gsProps_toolbar[0], gnProps_toolbarSize, &gsEvents_toolbar[0], gnEvents_toolbarSize);

				// Initially populate
				propSetEnabled(toolbarNew, _LOGICAL_TRUE);
				toolbarNew->isRendered		= true;
				toolbarNew->isPublished		= true;
				var = iObjProp_get_var_byIndex(toolbarNew, _INDEX_NAME);			iDatum_duplicate(&var->value, cgcName_toolbar, -1);
				var = iObjProp_get_var_byIndex(toolbarNew, _INDEX_CLASS);		iDatum_duplicate(&var->value, cgcName_toolbar, -1);
				var = iObjProp_get_var_byIndex(toolbarNew, _INDEX_BASECLASS);	iDatum_duplicate(&var->value, cgcName_toolbar, -1);
				iEvents_resetToDefault(toolbarNew, &gsEvents_toolbar[0], gnEvents_toolbarSize);
				iObj_setSize(toolbarNew, 0, 0, 100, 100);

				// Initialize based on template
				if (template_toolbar)
					iiSubobj_copyToolbar(toolbarNew, template_toolbar);		// Copy from indicated template
			}


		//////////
		// Indicate our success or failure
		//////
			return(toolbarNew);
	}




//////////
//
// Creates the separator structure
//
//////
	SObject* iSubobj_createSeparator(SObject* template_separator, SObject* parent)
	{
		SObject*	separatorNew;
		SVariable*	var;


		logfunc(__FUNCTION__);
		//////////
		// Create the indicated item
		//////
			separatorNew = (SObject*)malloc(sizeof(SObject));


		//////////
		// If successful, initialize it
		//////
			if (separatorNew)
			{
				// Initialize
				memset(separatorNew, 0, sizeof(SObject));

				// Initialize properties to VJr defaults
				separatorNew->objType	= _OBJ_TYPE_SEPARATOR;
				separatorNew->parent	= parent;
				iiSubobj_resetToDefaultSeparator(separatorNew, true, true, &gsProps_separator[0], gnProps_separatorSize, &gsEvents_separator[0], gnEvents_separatorSize);

				// Initially populate
				propSetEnabled(separatorNew, _LOGICAL_TRUE);
				separatorNew->isRendered	= true;
				separatorNew->isPublished	= true;
				var = iObjProp_get_var_byIndex(separatorNew, _INDEX_NAME);			iDatum_duplicate(&var->value, cgcName_separator, -1);
				var = iObjProp_get_var_byIndex(separatorNew, _INDEX_CLASS);			iDatum_duplicate(&var->value, cgcName_separator, -1);
				var = iObjProp_get_var_byIndex(separatorNew, _INDEX_BASECLASS);		iDatum_duplicate(&var->value, cgcName_separator, -1);
				iEvents_resetToDefault(separatorNew, &gsEvents_separator[0], gnEvents_separatorSize);
				iObj_setSize(separatorNew, 0, 0, 100, 100);

				// Initialize based on template
				if (template_separator)
					iiSubobj_copySeparator(separatorNew, template_separator);		// Copy from indicated template
			}


		//////////
		// Indicate our success or failure
		//////
			return(separatorNew);
	}




//////////
//
// Creates the line structure
//
//////
	SObject* iSubobj_createLine(SObject* template_line, SObject* parent)
	{
		SObject*	lineNew;
		SVariable*	var;


		logfunc(__FUNCTION__);
		//////////
		// Create the indicated item
		//////
			lineNew = (SObject*)malloc(sizeof(SObject));


		//////////
		// If successful, initialize it
		//////
			if (lineNew)
			{
				// Initialize
				memset(lineNew, 0, sizeof(SObject));

				// Initialize properties to VJr defaults
				lineNew->objType	= _OBJ_TYPE_LINE;
				lineNew->parent		= parent;
				iiSubobj_resetToDefaultLine(lineNew, true, true, &gsProps_line[0], gnProps_lineSize, &gsEvents_line[0], gnEvents_lineSize);

				// Initially populate
				propSetEnabled(lineNew, _LOGICAL_TRUE);
				lineNew->isRendered		= true;
				lineNew->isPublished	= true;
				var = iObjProp_get_var_byIndex(lineNew, _INDEX_NAME);			iDatum_duplicate(&var->value, cgcName_line, -1);
				var = iObjProp_get_var_byIndex(lineNew, _INDEX_CLASS);			iDatum_duplicate(&var->value, cgcName_line, -1);
				var = iObjProp_get_var_byIndex(lineNew, _INDEX_BASECLASS);		iDatum_duplicate(&var->value, cgcName_line, -1);
				iEvents_resetToDefault(lineNew, &gsEvents_line[0], gnEvents_lineSize);
				iObj_setSize(lineNew, 0, 0, 100, 100);

				// Initialize based on template
				if (template_line)
					iiSubobj_copyLine(lineNew, template_line);		// Copy from indicated template
			}


		//////////
		// Indicate our success or failure
		//////
			return(lineNew);
	}




//////////
//
// Creates the shape structure
//
//////
	SObject* iSubobj_createShape(SObject* template_shape, SObject* parent)
	{
		SObject*	shapeNew;
		SVariable*	var;


		logfunc(__FUNCTION__);
		//////////
		// Create the indicated item
		//////
			shapeNew = (SObject*)malloc(sizeof(SObject));


		//////////
		// If successful, initialize it
		//////
			if (shapeNew)
			{
				// Initialize
				memset(shapeNew, 0, sizeof(SObject));

				// Initialize properties to VJr defaults
				shapeNew->objType	= _OBJ_TYPE_SHAPE;
				shapeNew->parent	= parent;
				iiSubobj_resetToDefaultShape(shapeNew, true, true, &gsProps_shape[0], gnProps_shapeSize, &gsEvents_shape[0], gnEvents_shapeSize);

				// Initially populate
				propSetEnabled(shapeNew, _LOGICAL_TRUE);
				shapeNew->isRendered	= true;
				shapeNew->isPublished	= true;
				var = iObjProp_get_var_byIndex(shapeNew, _INDEX_NAME);			iDatum_duplicate(&var->value, cgcName_shape, -1);
				var = iObjProp_get_var_byIndex(shapeNew, _INDEX_CLASS);			iDatum_duplicate(&var->value, cgcName_shape, -1);
				var = iObjProp_get_var_byIndex(shapeNew, _INDEX_BASECLASS);		iDatum_duplicate(&var->value, cgcName_shape, -1);
				iEvents_resetToDefault(shapeNew, &gsEvents_shape[0], gnEvents_shapeSize);
				iObj_setSize(shapeNew, 0, 0, 100, 100);

				// Initialize based on template
				if (template_shape)
					iiSubobj_copyShape(shapeNew, template_shape);		// Copy from indicated template
			}


		//////////
		// Indicate our success or failure
		//////
			return(shapeNew);
	}




//////////
//
// Creates the container structure
//
//////
	SObject* iSubobj_createContainer(SObject* template_container, SObject* parent)
	{
		SObject*	containerNew;
		SVariable*	var;


		logfunc(__FUNCTION__);
		//////////
		// Create the indicated item
		//////
			containerNew = (SObject*)malloc(sizeof(SObject));


		//////////
		// If successful, initialize it
		//////
			if (containerNew)
			{
				// Initialize
				memset(containerNew, 0, sizeof(SObject));

				// Initialize properties to VJr defaults
				containerNew->objType	= _OBJ_TYPE_CONTAINER;
				containerNew->parent	= parent;
				iiSubobj_resetToDefaultContainer(containerNew, true, true, &gsProps_container[0], gnProps_containerSize, &gsEvents_container[0], gnEvents_containerSize);

				// Initially populate
				propSetEnabled(containerNew, _LOGICAL_TRUE);
				containerNew->isRendered	= true;
				containerNew->isPublished	= true;
				var = iObjProp_get_var_byIndex(containerNew, _INDEX_NAME);		iDatum_duplicate(&var->value, cgcName_container, -1);
				var = iObjProp_get_var_byIndex(containerNew, _INDEX_CLASS);		iDatum_duplicate(&var->value, cgcName_container, -1);
				var = iObjProp_get_var_byIndex(containerNew, _INDEX_BASECLASS);	iDatum_duplicate(&var->value, cgcName_container, -1);
				iEvents_resetToDefault(containerNew, &gsEvents_container[0], gnEvents_containerSize);
				iObj_setSize(containerNew, 0, 0, 100, 100);

				// Initialize based on template
				if (template_container)
					iiSubobj_copyContainer(containerNew, template_container);		// Copy from indicated template
			}


		//////////
		// Indicate our success or failure
		//////
			return(containerNew);
	}




//////////
//
// Creates the control structure
//
//////
	SObject* iSubobj_createControl(SObject* template_control, SObject* parent)
	{
		SObject*	controlNew;
		SVariable*	var;


		logfunc(__FUNCTION__);
		//////////
		// Create the indicated item
		//////
			controlNew = (SObject*)malloc(sizeof(SObject));


		//////////
		// If successful, initialize it
		//////
			if (controlNew)
			{
				// Initialize
				memset(controlNew, 0, sizeof(SObject));

				// Initialize properties to VJr defaults
				controlNew->objType		= _OBJ_TYPE_CONTROL;
				controlNew->parent		= parent;
				iiSubobj_resetToDefaultControl(controlNew, true, true, &gsProps_control[0], gnProps_controlSize, &gsEvents_control[0], gnEvents_controlSize);

				// Initially populate
				propSetEnabled(controlNew, _LOGICAL_TRUE);
				controlNew->isRendered		= true;
				controlNew->isPublished		= true;
				var = iObjProp_get_var_byIndex(controlNew, _INDEX_NAME);			iDatum_duplicate(&var->value, cgcName_control, -1);
				var = iObjProp_get_var_byIndex(controlNew, _INDEX_CLASS);		iDatum_duplicate(&var->value, cgcName_control, -1);
				var = iObjProp_get_var_byIndex(controlNew, _INDEX_BASECLASS);	iDatum_duplicate(&var->value, cgcName_control, -1);
				iEvents_resetToDefault(controlNew, &gsEvents_control[0], gnEvents_controlSize);
				iObj_setSize(controlNew, 0, 0, 100, 100);

				// Initialize based on template
				if (template_control)
					iiSubobj_copyControl(controlNew, template_control);		// Copy from indicated template
			}


		//////////
		// Indicate our success or failure
		//////
			return(controlNew);
	}




//////////
//
// Creates the grid structure
//
//////
	SObject* iSubobj_createGrid(SObject* template_grid, SObject* parent)
	{
		SObject*	gridNew;
		SVariable*	var;


		logfunc(__FUNCTION__);
		//////////
		// Create the indicated item
		//////
			gridNew = (SObject*)malloc(sizeof(SObject));


		//////////
		// If successful, initialize it
		//////
			if (gridNew)
			{
				// Initialize
				memset(gridNew, 0, sizeof(SObject));

				// Initialize properties to VJr defaults
				gridNew->objType	= _OBJ_TYPE_GRID;
				gridNew->parent		= parent;
				iiSubobj_resetToDefaultGrid(gridNew, true, true, &gsProps_grid[0], gnProps_gridSize, &gsEvents_grid[0], gnEvents_gridSize);

				// Initially populate
				propSetEnabled(gridNew, _LOGICAL_TRUE);
				gridNew->isRendered		= true;
				gridNew->isPublished	= true;
				var = iObjProp_get_var_byIndex(gridNew, _INDEX_NAME);			iDatum_duplicate(&var->value, cgcName_grid, -1);
				var = iObjProp_get_var_byIndex(gridNew, _INDEX_CLASS);			iDatum_duplicate(&var->value, cgcName_grid, -1);
				var = iObjProp_get_var_byIndex(gridNew, _INDEX_BASECLASS);		iDatum_duplicate(&var->value, cgcName_grid, -1);
				iEvents_resetToDefault(gridNew, &gsEvents_grid[0], gnEvents_gridSize);
				iObj_setSize(gridNew, 0, 0, 100, 100);

				// Initialize based on template
				if (template_grid)
					iiSubobj_copyGrid(gridNew, template_grid);		// Copy from indicated template
			}


		//////////
		// Indicate our success or failure
		//////
			return(gridNew);
	}




//////////
//
// Creates the column structure
//
//////
	SObject* iSubobj_createColumn(SObject* template_column, SObject* parent)
	{
		SObject*	columnNew;
		SVariable*	var;


		logfunc(__FUNCTION__);
		//////////
		// Create the indicated item
		//////
			columnNew = (SObject*)malloc(sizeof(SObject));


		//////////
		// If successful, initialize it
		//////
			if (columnNew)
			{
				// Initialize
				memset(columnNew, 0, sizeof(SObject));

				// Initialize properties to VJr defaults
				columnNew->objType	= _OBJ_TYPE_COLUMN;
				columnNew->parent	= parent;
				iiSubobj_resetToDefaultColumn(columnNew, true, true, &gsProps_column[0], gnProps_columnSize, &gsEvents_column[0], gnEvents_columnSize);

				// Initially populate
				propSetEnabled(columnNew, _LOGICAL_TRUE);
				columnNew->isRendered	= true;
				columnNew->isPublished	= true;
				var = iObjProp_get_var_byIndex(columnNew, _INDEX_NAME);			iDatum_duplicate(&var->value, cgcName_column, -1);
				var = iObjProp_get_var_byIndex(columnNew, _INDEX_CLASS);			iDatum_duplicate(&var->value, cgcName_column, -1);
				var = iObjProp_get_var_byIndex(columnNew, _INDEX_BASECLASS);		iDatum_duplicate(&var->value, cgcName_column, -1);
				iEvents_resetToDefault(columnNew, &gsEvents_column[0], gnEvents_columnSize);
				iObj_setSize(columnNew, 0, 0, 100, 100);

				// Initialize based on template
				if (template_column)
					iiSubobj_copyColumn(columnNew, template_column);		// Copy from indicated template
			}


		//////////
		// Indicate our success or failure
		//////
			return(columnNew);
	}




//////////
//
// Creates the header structure
//
//////
	SObject* iSubobj_createHeader(SObject* template_header, SObject* parent)
	{
		SObject*	headerNew;
		SVariable*	var;


		logfunc(__FUNCTION__);
		//////////
		// Create the indicated item
		//////
			headerNew = (SObject*)malloc(sizeof(SObject));


		//////////
		// If successful, initialize it
		//////
			if (headerNew)
			{
				// Initialize
				memset(headerNew, 0, sizeof(SObject));

				// Initialize properties to VJr defaults
				headerNew->objType	= _OBJ_TYPE_HEADER;
				headerNew->parent	= parent;
				iiSubobj_resetToDefaultHeader(headerNew, true, true, &gsProps_header[0], gnProps_headerSize, &gsEvents_header[0], gnEvents_headerSize);

				// Initially populate
				propSetEnabled(headerNew, _LOGICAL_TRUE);
				headerNew->isRendered	= true;
				headerNew->isPublished	= true;
				var = iObjProp_get_var_byIndex(headerNew, _INDEX_NAME);			iDatum_duplicate(&var->value, cgcName_header, -1);
				var = iObjProp_get_var_byIndex(headerNew, _INDEX_CLASS);			iDatum_duplicate(&var->value, cgcName_header, -1);
				var = iObjProp_get_var_byIndex(headerNew, _INDEX_BASECLASS);		iDatum_duplicate(&var->value, cgcName_header, -1);
				iEvents_resetToDefault(headerNew, &gsEvents_header[0], gnEvents_headerSize);
				iObj_setSize(headerNew, 0, 0, 100, 100);

				// Initialize based on template
				if (template_header)
					iiSubobj_copyHeader(headerNew, template_header);		// Copy from indicated template
			}


		//////////
		// Indicate our success or failure
		//////
			return(headerNew);
	}




//////////
//
// Creates the olebound structure
//
//////
	SObject* iSubobj_createOleBound(SObject* template_oleBound, SObject* parent)
	{
		SObject*	oleBoundNew;
		SVariable*	var;


		logfunc(__FUNCTION__);
		//////////
		// Create the indicated item
		//////
			oleBoundNew = (SObject*)malloc(sizeof(SObject));


		//////////
		// If successful, initialize it
		//////
			if (oleBoundNew)
			{
				// Initialize
				memset(oleBoundNew, 0, sizeof(SObject));

				// Initialize properties to VJr defaults
				oleBoundNew->objType	= _OBJ_TYPE_OLEBOUND;
				oleBoundNew->parent		= parent;
				iiSubobj_resetToDefaultOleBound(oleBoundNew, true, true, &gsProps_olebound[0], gnProps_oleboundSize, &gsEvents_olebound[0], gnEvents_oleboundSize);

				// Initially populate
				propSetEnabled(oleBoundNew, _LOGICAL_TRUE);
				oleBoundNew->isRendered		= true;
				oleBoundNew->isPublished	= true;
				var = iObjProp_get_var_byIndex(oleBoundNew, _INDEX_NAME);			iDatum_duplicate(&var->value, cgcName_olebound, -1);
				var = iObjProp_get_var_byIndex(oleBoundNew, _INDEX_CLASS);			iDatum_duplicate(&var->value, cgcName_olebound, -1);
				var = iObjProp_get_var_byIndex(oleBoundNew, _INDEX_BASECLASS);		iDatum_duplicate(&var->value, cgcName_olebound, -1);
				iEvents_resetToDefault(oleBoundNew, &gsEvents_olebound[0], gnEvents_oleboundSize);
				iObj_setSize(oleBoundNew, 0, 0, 100, 100);

				// Initialize based on template
				if (template_oleBound)
					iiSubobj_copyOleBound(oleBoundNew, template_oleBound);		// Copy from indicated template
			}


		//////////
		// Indicate our success or failure
		//////
			return(oleBoundNew);
	}




//////////
//
// Creates the contain structure
//
//////
	SObject* iSubobj_createOleContain(SObject* template_oleContain, SObject* parent)
	{
		SObject*	oleContainNew;
		SVariable*	var;


		logfunc(__FUNCTION__);
		//////////
		// Create the indicated item
		//////
			oleContainNew = (SObject*)malloc(sizeof(SObject));


		//////////
		// If successful, initialize it
		//////
			if (oleContainNew)
			{
				// Initialize
				memset(oleContainNew, 0, sizeof(SObject));

				// Initialize properties to VJr defaults
				oleContainNew->objType	= _OBJ_TYPE_CONTAINER;
				oleContainNew->parent	= parent;
				iiSubobj_resetToDefaultContainer(oleContainNew, true, true, &gsProps_olecontain[0], gnProps_olecontainSize, &gsEvents_olecontain[0], gnEvents_olecontainSize);

				// Initially populate
				propSetEnabled(oleContainNew, _LOGICAL_TRUE);
				oleContainNew->isRendered	= true;
				oleContainNew->isPublished	= true;
				var = iObjProp_get_var_byIndex(oleContainNew, _INDEX_NAME);			iDatum_duplicate(&var->value, cgcName_olecontain, -1);
				var = iObjProp_get_var_byIndex(oleContainNew, _INDEX_CLASS);			iDatum_duplicate(&var->value, cgcName_olecontain, -1);
				var = iObjProp_get_var_byIndex(oleContainNew, _INDEX_BASECLASS);		iDatum_duplicate(&var->value, cgcName_olecontain, -1);
				iEvents_resetToDefault(oleContainNew, &gsEvents_olecontain[0], gnEvents_olecontainSize);
				iObj_setSize(oleContainNew, 0, 0, 100, 100);

				// Initialize based on template
				if (template_oleContain)
					iiSubobj_copyContainer(oleContainNew, template_oleContain);		// Copy from indicated template
			}


		//////////
		// Indicate our success or failure
		//////
			return(oleContainNew);
	}




//////////
//
// Creates the spinner structure
//
//////
	SObject* iSubobj_createSpinner(SObject* template_spinner, SObject* parent)
	{
		SObject*	spinnerNew;
		SVariable*	var;


		logfunc(__FUNCTION__);
		//////////
		// Create the indicated item
		//////
			spinnerNew = (SObject*)malloc(sizeof(SObject));


		//////////
		// If successful, initialize it
		//////
			if (spinnerNew)
			{
				// Initialize
				memset(spinnerNew, 0, sizeof(SObject));

				// Initialize properties to VJr defaults
				spinnerNew->objType		= _OBJ_TYPE_SPINNER;
				spinnerNew->parent		= parent;
				iiSubobj_resetToDefaultSpinner(spinnerNew, true, true, &gsProps_spinner[0], gnProps_spinnerSize, &gsEvents_spinner[0], gnEvents_spinnerSize);

				// Initially populate
				propSetEnabled(spinnerNew, _LOGICAL_TRUE);
				spinnerNew->isRendered		= true;
				spinnerNew->isPublished		= true;
				var = iObjProp_get_var_byIndex(spinnerNew, _INDEX_NAME);				iDatum_duplicate(&var->value, cgcName_spinner, -1);
				var = iObjProp_get_var_byIndex(spinnerNew, _INDEX_CLASS);			iDatum_duplicate(&var->value, cgcName_spinner, -1);
				var = iObjProp_get_var_byIndex(spinnerNew, _INDEX_BASECLASS);		iDatum_duplicate(&var->value, cgcName_spinner, -1);
				iEvents_resetToDefault(spinnerNew, &gsEvents_spinner[0], gnEvents_spinnerSize);
				iObj_setSize(spinnerNew, 0, 0, 100, 100);

				// Initialize based on template
				if (template_spinner)
					iiSubobj_copySpinner(spinnerNew, template_spinner);		// Copy from indicated template
			}


		//////////
		// Indicate our success or failure
		//////
			return(spinnerNew);
	}




//////////
//
// Creates the timer structure
//
//////
	SObject* iSubobj_createTimer(SObject* template_timer, SObject* parent)
	{
		SObject*	timerNew;
		SVariable*	var;


		logfunc(__FUNCTION__);
		//////////
		// Create the indicated item
		//////
			timerNew = (SObject*)malloc(sizeof(SObject));


		//////////
		// If successful, initialize it
		//////
			if (timerNew)
			{
				// Initialize
				memset(timerNew, 0, sizeof(SObject));

				// Initialize properties to VJr defaults
				timerNew->objType	= _OBJ_TYPE_TIMER;
				timerNew->parent	= parent;
				iiSubobj_resetToDefaultTimer(timerNew, true, true, &gsProps_timer[0], gnProps_timerSize, &gsEvents_timer[0], gnEvents_timerSize);

				// Initially populate
				propSetEnabled(timerNew, _LOGICAL_TRUE);
				timerNew->isRendered	= true;
				timerNew->isPublished	= true;
				var = iObjProp_get_var_byIndex(timerNew, _INDEX_NAME);			iDatum_duplicate(&var->value, cgcName_timer, -1);
				var = iObjProp_get_var_byIndex(timerNew, _INDEX_CLASS);			iDatum_duplicate(&var->value, cgcName_timer, -1);
				var = iObjProp_get_var_byIndex(timerNew, _INDEX_BASECLASS);		iDatum_duplicate(&var->value, cgcName_timer, -1);
				iEvents_resetToDefault(timerNew, &gsEvents_timer[0], gnEvents_timerSize);
				iObj_setSize(timerNew, 0, 0, 100, 100);

				// Initialize based on template
				if (template_timer)
					iiSubobj_copyTimer(timerNew, template_timer);		// Copy from indicated template
			}


		//////////
		// Indicate our success or failure
		//////
			return(timerNew);
	}




//////////
//
// Creates the hyperlink structure
//
//////
	SObject* iSubobj_createHyperlink(SObject* template_hyperlink, SObject* parent)
	{
		SObject*	hyperlinkNew;
		SVariable*	var;


		logfunc(__FUNCTION__);
		//////////
		// Create the indicated item
		//////
			hyperlinkNew = (SObject*)malloc(sizeof(SObject));


		//////////
		// If successful, initialize it
		//////
			if (hyperlinkNew)
			{
				// Initialize
				memset(hyperlinkNew, 0, sizeof(SObject));

				// Initialize properties to VJr defaults
				hyperlinkNew->objType	= _OBJ_TYPE_HYPERLINK;
				hyperlinkNew->parent	= parent;
				iiSubobj_resetToDefaultHyperlink(hyperlinkNew, true, true, &gsProps_hyperlink[0], gnProps_hyperlinkSize, &gsEvents_hyperlink[0], gnEvents_hyperlinkSize);

				// Initially populate
				propSetEnabled(hyperlinkNew, _LOGICAL_TRUE);
				hyperlinkNew->isRendered	= true;
				hyperlinkNew->isPublished	= true;
				var = iObjProp_get_var_byIndex(hyperlinkNew, _INDEX_NAME);			iDatum_duplicate(&var->value, cgcName_hyperlink, -1);
				var = iObjProp_get_var_byIndex(hyperlinkNew, _INDEX_CLASS);			iDatum_duplicate(&var->value, cgcName_hyperlink, -1);
				var = iObjProp_get_var_byIndex(hyperlinkNew, _INDEX_BASECLASS);		iDatum_duplicate(&var->value, cgcName_hyperlink, -1);
				iEvents_resetToDefault(hyperlinkNew, &gsEvents_hyperlink[0], gnEvents_hyperlinkSize);
				iObj_setSize(hyperlinkNew, 0, 0, 100, 100);

				// Initialize based on template
				if (template_hyperlink)
					iiSubobj_copyHyperlink(hyperlinkNew, template_hyperlink);		// Copy from indicated template
			}


		//////////
		// Indicate our success or failure
		//////
			return(hyperlinkNew);
	}




//////////
//
// Creates the collection structure
//
//////
	SObject* iSubobj_createCollection(SObject* template_collection, SObject* parent)
	{
		SObject*	collectionNew;
		SVariable*	var;


		logfunc(__FUNCTION__);
		//////////
		// Create the indicated item
		//////
			collectionNew = (SObject*)malloc(sizeof(SObject));


		//////////
		// If successful, initialize it
		//////
			if (collectionNew)
			{
				// Initialize
				memset(collectionNew, 0, sizeof(SObject));

				// Initialize properties to VJr defaults
				collectionNew->objType	= _OBJ_TYPE_COLLECTION;
				collectionNew->parent	= parent;
				iiSubobj_resetToDefaultCollection(collectionNew, true, true, &gsProps_collection[0], gnProps_collectionSize, &gsEvents_collection[0], gnEvents_collectionSize);

				// Initially populate
				propSetEnabled(collectionNew, _LOGICAL_TRUE);
				collectionNew->isRendered		= true;
				collectionNew->isPublished		= true;
				var = iObjProp_get_var_byIndex(collectionNew, _INDEX_NAME);			iDatum_duplicate(&var->value, cgcName_collection, -1);
				var = iObjProp_get_var_byIndex(collectionNew, _INDEX_CLASS);			iDatum_duplicate(&var->value, cgcName_collection, -1);
				var = iObjProp_get_var_byIndex(collectionNew, _INDEX_BASECLASS);		iDatum_duplicate(&var->value, cgcName_collection, -1);
				iEvents_resetToDefault(collectionNew, &gsEvents_collection[0], gnEvents_collectionSize);
				iObj_setSize(collectionNew, 0, 0, 100, 100);

				// Initialize based on template
				if (template_collection)
					iiSubobj_copyCollection(collectionNew, template_collection);		// Copy from indicated template
			}


		//////////
		// Indicate our success or failure
		//////
			return(collectionNew);
	}




//////////
//
// Creates the cmdGroup structure
//
//////
	SObject* iSubobj_createPage(SObject* template_page, SObject* parent)
	{
		SObject*	pageNew;
		SVariable*	var;


		logfunc(__FUNCTION__);
		//////////
		// Create the indicated item
		//////
			pageNew = (SObject*)malloc(sizeof(SObject));


		//////////
		// If successful, initialize it
		//////
			if (pageNew)
			{
				// Initialize
				memset(pageNew, 0, sizeof(SObject));

				// Initialize properties to VJr defaults
				pageNew->objType	= _OBJ_TYPE_PAGE;
				pageNew->parent		= parent;
				iiSubobj_resetToDefaultPage(pageNew, true, true, &gsProps_page[0], gnProps_pageSize, &gsEvents_page[0], gnEvents_pageSize);

				// Initially populate
				propSetEnabled(pageNew, _LOGICAL_TRUE);
				pageNew->isRendered		= true;
				pageNew->isPublished	= true;
				var = iObjProp_get_var_byIndex(pageNew, _INDEX_NAME);			iDatum_duplicate(&var->value, cgcName_page, -1);
				var = iObjProp_get_var_byIndex(pageNew, _INDEX_CLASS);			iDatum_duplicate(&var->value, cgcName_page, -1);
				var = iObjProp_get_var_byIndex(pageNew, _INDEX_BASECLASS);		iDatum_duplicate(&var->value, cgcName_page, -1);
				iEvents_resetToDefault(pageNew, &gsEvents_page[0], gnEvents_pageSize);
				iObj_setSize(pageNew, 0, 0, 100, 100);

				// Initialize based on template
				if (template_page)
					iiSubobj_copyPage(pageNew, template_page);		// Copy from indicated template
			}


		//////////
		// Indicate our success or failure
		//////
			return(pageNew);
	}




//////////
//
// Creates the pageframe structure
//
//////
	SObject* iSubobj_createPageFrame(SObject* template_pageframe, SObject* parent)
	{
		SObject*	pageframeNew;
		SVariable*	var;


		logfunc(__FUNCTION__);
		//////////
		// Create the indicated item
		//////
			pageframeNew = (SObject*)malloc(sizeof(SObject));


		//////////
		// If successful, initialize it
		//////
			if (pageframeNew)
			{
				// Initialize
				memset(pageframeNew, 0, sizeof(SObject));

				// Initialize properties to VJr defaults
				pageframeNew->objType	= _OBJ_TYPE_PAGEFRAME;
				pageframeNew->parent	= parent;
				iiSubobj_resetToDefaultPageframe(pageframeNew, true, true, &gsProps_pageframe[0], gnProps_pageframeSize, &gsEvents_pageframe[0], gnEvents_pageframeSize);

				// Initially populate
				propSetEnabled(pageframeNew, _LOGICAL_TRUE);
				pageframeNew->isRendered	= true;
				pageframeNew->isPublished	= true;
				var = iObjProp_get_var_byIndex(pageframeNew, _INDEX_NAME);			iDatum_duplicate(&var->value, cgcName_pageframe, -1);
				var = iObjProp_get_var_byIndex(pageframeNew, _INDEX_CLASS);			iDatum_duplicate(&var->value, cgcName_pageframe, -1);
				var = iObjProp_get_var_byIndex(pageframeNew, _INDEX_BASECLASS);		iDatum_duplicate(&var->value, cgcName_pageframe, -1);
				iEvents_resetToDefault(pageframeNew, &gsEvents_pageframe[0], gnEvents_pageframeSize);
				iObj_setSize(pageframeNew, 0, 0, 100, 100);

				// Initialize based on template
				if (template_pageframe)
					iiSubobj_copyPageframe(pageframeNew, template_pageframe);		// Copy from indicated template
			}


		//////////
		// Indicate our success or failure
		//////
			return(pageframeNew);
	}




//////////
//
// Creates the session structure
//
//////
	SObject* iSubobj_createSession(SObject* template_session, SObject* parent)
	{
		SObject*	sessionNew;
		SVariable*	var;


		logfunc(__FUNCTION__);
		//////////
		// Create the indicated item
		//////
			sessionNew = (SObject*)malloc(sizeof(SObject));


		//////////
		// If successful, initialize it
		//////
			if (sessionNew)
			{
				// Initialize
				memset(sessionNew, 0, sizeof(SObject));

				// Initialize properties to VJr defaults
				sessionNew->objType		= _OBJ_TYPE_SESSION;
				sessionNew->parent		= parent;
				iiSubobj_resetToDefaultSession(sessionNew, true, true, &gsProps_session[0], gnProps_sessionSize, &gsEvents_session[0], gnEvents_sessionSize);

				// Initially populate
				propSetEnabled(sessionNew, _LOGICAL_TRUE);
				sessionNew->isRendered		= true;
				sessionNew->isPublished		= true;
				var = iObjProp_get_var_byIndex(sessionNew, _INDEX_NAME);			iDatum_duplicate(&var->value, cgcName_session, -1);
				var = iObjProp_get_var_byIndex(sessionNew, _INDEX_CLASS);		iDatum_duplicate(&var->value, cgcName_session, -1);
				var = iObjProp_get_var_byIndex(sessionNew, _INDEX_BASECLASS);	iDatum_duplicate(&var->value, cgcName_session, -1);
				iEvents_resetToDefault(sessionNew, &gsEvents_session[0], gnEvents_sessionSize);
				iObj_setSize(sessionNew, 0, 0, 100, 100);

				// Initialize based on template
				if (template_session)
					iiSubobj_copySession(sessionNew, template_session);		// Copy from indicated template
			}


		//////////
		// Indicate our success or failure
		//////
			return(sessionNew);
	}




//////////
//
// Creates the custom structure
//
//////
	SObject* iSubobj_createCustom(SObject* template_custom, SObject* parent)
	{
		SObject*	customNew;
		SVariable*	var;


		logfunc(__FUNCTION__);
		//////////
		// Create the indicated item
		//////
			customNew = (SObject*)malloc(sizeof(SObject));


		//////////
		// If successful, initialize it
		//////
			if (customNew)
			{
				// Initialize
				memset(customNew, 0, sizeof(SObject));

				// Initialize properties to VJr defaults
				customNew->objType		= _OBJ_TYPE_CUSTOM;
				customNew->parent		= parent;
				iiSubobj_resetToDefaultCustom(customNew, true, true, &gsProps_custom[0], gnProps_customSize, &gsEvents_custom[0], gnEvents_customSize);

				// Initially populate
				propSetEnabled(customNew, _LOGICAL_TRUE);
				customNew->isRendered		= true;
				customNew->isPublished		= true;
				var = iObjProp_get_var_byIndex(customNew, _INDEX_NAME);			iDatum_duplicate(&var->value, cgcName_custom, -1);
				var = iObjProp_get_var_byIndex(customNew, _INDEX_CLASS);			iDatum_duplicate(&var->value, cgcName_custom, -1);
				var = iObjProp_get_var_byIndex(customNew, _INDEX_BASECLASS);		iDatum_duplicate(&var->value, cgcName_custom, -1);
				iEvents_resetToDefault(customNew, &gsEvents_custom[0], gnEvents_customSize);
				iObj_setSize(customNew, 0, 0, 100, 100);

				// Initialize based on template
				if (template_custom)
					iiSubobj_copyCustom(customNew, template_custom);		// Copy from indicated template
			}


		//////////
		// Indicate our success or failure
		//////
			return(customNew);
	}




//////////
//
// Creates the exception structure
//
//////
	SObject* iSubobj_createException(SObject* template_exception, SObject* parent)
	{
		SObject*	exceptionNew;
		SVariable*	var;


		logfunc(__FUNCTION__);
		//////////
		// Create the indicated item
		//////
			exceptionNew = (SObject*)malloc(sizeof(SObject));


		//////////
		// If successful, initialize it
		//////
			if (exceptionNew)
			{
				// Initialize
				memset(exceptionNew, 0, sizeof(SObject));

				// Initialize properties to VJr defaults
				exceptionNew->objType		= _OBJ_TYPE_EXCEPTION;
				exceptionNew->parent		= parent;
				iiSubobj_resetToDefaultException(exceptionNew, true, true, &gsProps_exception[0], gnProps_exceptionSize, &gsEvents_exception[0], gnEvents_exceptionSize);

				// Initially populate
				propSetEnabled(exceptionNew, _LOGICAL_TRUE);
				exceptionNew->isRendered		= true;
				exceptionNew->isPublished		= true;
				var = iObjProp_get_var_byIndex(exceptionNew, _INDEX_NAME);			iDatum_duplicate(&var->value, cgcName_exception, -1);
				var = iObjProp_get_var_byIndex(exceptionNew, _INDEX_CLASS);			iDatum_duplicate(&var->value, cgcName_exception, -1);
				var = iObjProp_get_var_byIndex(exceptionNew, _INDEX_BASECLASS);		iDatum_duplicate(&var->value, cgcName_exception, -1);
				iEvents_resetToDefault(exceptionNew, &gsEvents_exception[0], gnEvents_exceptionSize);
				iObj_setSize(exceptionNew, 0, 0, 100, 100);

				// Initialize based on template
				if (template_exception)
					iiSubobj_copyException(exceptionNew, template_exception);		// Copy from indicated template
			}


		//////////
		// Indicate our success or failure
		//////
			return(exceptionNew);
	}




//////////
//
// Create the settings structure
//
//////
	SObject* iSubobj_createSettings(SObject* template_Settings, SObject* parent)
	{
		SObject*	settingsNew;
		SVariable*	var;


		logfunc(__FUNCTION__);
		//////////
		// Create the indicated item
		//////
			settingsNew = (SObject*)malloc(sizeof(SObject));


		//////////
		// If successful, initialize it
		//////
			if (settingsNew)
			{
				// Initialize
				memset(settingsNew, 0, sizeof(SObject));

				// Initialize properties to VJr defaults
				settingsNew->objType	= _OBJ_TYPE_SETTINGS;
				settingsNew->parent		= parent;
				iiSubobj_resetToDefaultSettings(settingsNew, true, true, &gsProps_settings[0], gnProps_settingsSize, &gsEvents_settings[0], gnEvents_settingsSize);

				// Initially populate
				settingsNew->isRendered		= false;
				settingsNew->isPublished	= false;
				var = iObjProp_get_var_byIndex(settingsNew, _INDEX_NAME);			iDatum_duplicate(&var->value, cgcName_settings, -1);
				var = iObjProp_get_var_byIndex(settingsNew, _INDEX_CLASS);			iDatum_duplicate(&var->value, cgcName_settings, -1);
				var = iObjProp_get_var_byIndex(settingsNew, _INDEX_BASECLASS);		iDatum_duplicate(&var->value, cgcName_settings, -1);
				iEvents_resetToDefault(settingsNew, &gsEvents_settings[0], gnEvents_settingsSize);

				// Initialize based on template
				if (template_Settings)
					iiSubobj_copyException(settingsNew, template_Settings);		// Copy from indicated template
			}


		//////////
		// Indicate our success or failure
		//////
			return(settingsNew);
	}
