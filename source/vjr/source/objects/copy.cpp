//////////
//
// /libsf/source/vjr/source/objects/copy.cpp
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
// Called to copy the indicated empty from source to destination
//
//////
	void iiSubobj_copyEmpty(SObject* emptyDst, SObject* emptySrc)
	{
		logfunc(__FUNCTION__);
		//////////
		// Duplicate all children for this object
		//////
			iObj_duplicateChildren(emptyDst, emptySrc);
	}




//////////
//
// Called to copy the indicated form from source to destination
//
//////
	void iiSubobj_copyForm(SObject* formDst, SObject* formSrc)
	{
		logfunc(__FUNCTION__);
		//////////
		// Copy all standard properties
		//////
			memcpy(&formDst->p, &formSrc->p, sizeof(formDst->p));


		//////////
		// Copy the allocatables
		//////
			formDst->p.font	= iFont_duplicate(formSrc->p.font);
			iObjProp_set_bitmap_direct(formDst, _INDEX_ICON, iObjProp_get_bitmap(formSrc, _INDEX_ICON));
			iObjProp_copy_byIndex(formDst, _INDEX_CAPTION, formSrc, _INDEX_CAPTION);


		//////////
		// Copy the form-specific event handlers
		//////
			memcpy(&formDst->ev, &formSrc->ev, sizeof(formDst->ev));


		//////////
		// Duplicate all children for this object
		//////
			iObj_duplicateChildren(formDst, formSrc);
	}




//////////
//
// Called to copy the indicated empty subform source to destination
//
//////
	void iiSubobj_copySubform(SObject* subformDst, SObject* subformSrc)
	{
		logfunc(__FUNCTION__);
		//////////
		// Copy all standard properties
		//////
			memcpy(&subformDst->p, &subformSrc->p, sizeof(subformDst->p));


		//////////
		// Copy the allocatables
		//////
			subformDst->p.font	= iFont_duplicate(subformSrc->p.font);
			iObjProp_set_bitmap_direct(subformDst, _INDEX_ICON, iObjProp_get_bitmap(subformSrc, _INDEX_ICON));
			iObjProp_copy_byIndex(subformDst, _INDEX_CAPTION, subformSrc, _INDEX_CAPTION);

			// Picture
			iObjProp_copy_byIndex(subformDst, _INDEX_PICTURE,			subformSrc, _INDEX_PICTURE);
			iObjProp_copy_byIndex(subformDst, _INDEX_PICTUREBMP,		subformSrc, _INDEX_PICTUREBMP);
			iObjProp_copy_byIndex(subformDst, _INDEX_PICTUREBMP_DOWN,	subformSrc, _INDEX_PICTUREBMP_DOWN);
			iObjProp_copy_byIndex(subformDst, _INDEX_PICTUREBMP_OVER,	subformSrc, _INDEX_PICTUREBMP_OVER);


		//////////
		// Copy the form-specific event handlers
		//////
			memcpy(&subformDst->ev, &subformSrc->ev, sizeof(subformDst->ev));


		//////////
		// Duplicate all children for this object
		//////
			iObj_duplicateChildren(subformDst, subformSrc);
	}




//////////
//
// Called to copy the indicated carousel source to destination
//
//////
	void iiSubobj_copyCarousel(SObject* carouselDst, SObject* carouselSrc)
	{
		logfunc(__FUNCTION__);
		//////////
		// Copy all standard properties
		//////
			memcpy(&carouselDst->p, &carouselSrc->p, sizeof(carouselDst->p));


		//////////
		// Copy the form-specific event handlers
		//////
			memcpy(&carouselDst->ev, &carouselSrc->ev, sizeof(carouselDst->ev));


		//////////
		// Duplicate all children for this object
		//////
			iObj_duplicateChildren(carouselDst, carouselSrc);
	}




//////////
//
// Called to copy the indicated rider source to destination
//
//////
	void iiSubobj_copyRider(SObject* riderDst, SObject* riderSrc)
	{
		logfunc(__FUNCTION__);
		//////////
		// Copy all standard properties
		//////
			memcpy(&riderDst->p, &riderSrc->p, sizeof(riderDst->p));


		//////////
		// Copy the form-specific event handlers
		//////
			memcpy(&riderDst->ev, &riderSrc->ev, sizeof(riderDst->ev));


		//////////
		// Duplicate all children for this object
		//////
			iObj_duplicateChildren(riderDst, riderSrc);
	}




//////////
//
// Called to copy the indicated label from source to destination
//
//////
	void iiSubobj_copyLabel(SObject* labelDst, SObject* labelSrc)
	{
		logfunc(__FUNCTION__);
		//////////
		// Copy all standard properties
		//////
			memcpy(&labelDst->p, &labelSrc->p, sizeof(labelDst->p));


		//////////
		// Copy the allocatables
		//////
			labelDst->p.font = iFont_duplicate(labelSrc->p.font);

			// Caption
			iObjProp_copy_byIndex(labelDst, _INDEX_CAPTION, labelSrc, _INDEX_CAPTION);


		//////////
		// Copy the form-specific event handlers
		//////
			memcpy(&labelDst->ev, &labelSrc->ev, sizeof(labelDst->ev));


		//////////
		// Duplicate all children for this object
		//////
			iObj_duplicateChildren(labelDst, labelSrc);
	}




//////////
//
// Called to copy the indicated textbox from source to destination
//
//////
	void iiSubobj_copyTextbox(SObject* textboxDst, SObject* textboxSrc)
	{
		logfunc(__FUNCTION__);
		//////////
		// Copy all standard properties
		//////
			memcpy(&textboxDst->p, &textboxSrc->p, sizeof(textboxDst->p));


		//////////
		// Copy the allocatables
		//////
			textboxDst->p.font		= iFont_duplicate(textboxSrc->p.font);
			iObjProp_set_bitmap_direct(textboxDst, _INDEX_ICON, iObjProp_get_bitmap(textboxSrc, _INDEX_ICON));

			// Caption
			iObjProp_copy_byIndex(textboxDst, _INDEX_CAPTION,				textboxSrc, _INDEX_CAPTION);

			// Value
			iObjProp_copy_byIndex(textboxDst, _INDEX_VALUE,				textboxSrc, _INDEX_VALUE);
			iObjProp_copy_byIndex(textboxDst, _INDEX_PICTURE,				textboxSrc, _INDEX_PICTURE);
			iObjProp_copy_byIndex(textboxDst, _INDEX_PICTUREBMP,			textboxSrc, _INDEX_PICTUREBMP);
			iObjProp_copy_byIndex(textboxDst, _INDEX_PICTUREBMP_DOWN,		textboxSrc, _INDEX_PICTUREBMP_DOWN);
			iObjProp_copy_byIndex(textboxDst, _INDEX_PICTUREBMP_OVER,		textboxSrc, _INDEX_PICTUREBMP_OVER);
			iObjProp_copy_byIndex(textboxDst, _INDEX_MASK,				textboxSrc, _INDEX_MASK);
	

		//////////
		// Copy the form-specific event handlers
		//////
			memcpy(&textboxDst->ev, &textboxSrc->ev, sizeof(textboxDst->ev));


		//////////
		// Duplicate all children for this object
		//////
			iObj_duplicateChildren(textboxDst, textboxSrc);
	}




//////////
//
// Called to copy the indicated button from source to destination
//
//////
	void iiSubobj_copyButton(SObject* buttonDst, SObject* buttonSrc)
	{
		logfunc(__FUNCTION__);
		//////////
		// Copy all standard properties
		//////
			memcpy(&buttonDst->p, &buttonSrc->p, sizeof(buttonDst->p));


		//////////
		// Copy the allocatables
		//////
			buttonDst->p.font		= iFont_duplicate(buttonSrc->p.font);

			// Caption
			iObjProp_copy_byIndex(buttonDst, _INDEX_CAPTION,			buttonSrc, _INDEX_CAPTION);

			// Picture
			iObjProp_copy_byIndex(buttonDst, _INDEX_PICTURE,			buttonSrc, _INDEX_PICTURE);
			iObjProp_copy_byIndex(buttonDst, _INDEX_PICTUREBMP,			buttonSrc, _INDEX_PICTUREBMP);
			iObjProp_copy_byIndex(buttonDst, _INDEX_PICTUREBMP_DOWN,	buttonSrc, _INDEX_PICTUREBMP_DOWN);
			iObjProp_copy_byIndex(buttonDst, _INDEX_PICTUREBMP_OVER,	buttonSrc, _INDEX_PICTUREBMP_OVER);


		//////////
		// Copy the form-specific event handlers
		//////
			memcpy(&buttonDst->ev, &buttonSrc->ev, sizeof(buttonDst->ev));


		//////////
		// Duplicate all children for this object
		//////
			iObj_duplicateChildren(buttonDst, buttonSrc);
	}




//////////
//
// Called to copy the indicated editbox from source to destination
//
//////
	void iiSubobj_copyEditbox(SObject* editboxDst, SObject* editboxSrc)
	{
		logfunc(__FUNCTION__);
		//////////
		// Copy all standard properties
		//////
			memcpy(&editboxDst->p, &editboxSrc->p, sizeof(editboxDst->p));


		//////////
		// Copy the allocatables
		//////
			editboxDst->p.font	= iFont_duplicate(editboxSrc->p.font);
			iObjProp_copy_byIndex(editboxDst, _INDEX_ICON,				editboxSrc, _INDEX_ICON);

			// Caption
			iObjProp_copy_byIndex(editboxDst, _INDEX_CAPTION,			editboxSrc, _INDEX_CAPTION);

			// Value
			iObjProp_copy_byIndex(editboxDst, _INDEX_VALUE,				editboxSrc, _INDEX_VALUE);
			iObjProp_copy_byIndex(editboxDst, _INDEX_PICTURE,			editboxSrc, _INDEX_PICTURE);
			iObjProp_copy_byIndex(editboxDst, _INDEX_PICTUREBMP,		editboxSrc, _INDEX_PICTUREBMP);
			iObjProp_copy_byIndex(editboxDst, _INDEX_PICTUREBMP_DOWN,	editboxSrc, _INDEX_PICTUREBMP_DOWN);
			iObjProp_copy_byIndex(editboxDst, _INDEX_PICTUREBMP_OVER,	editboxSrc, _INDEX_PICTUREBMP_OVER);
			iObjProp_copy_byIndex(editboxDst, _INDEX_MASK,				editboxSrc, _INDEX_MASK);


		//////////
		// Copy the form-specific event handlers
		//////
			memcpy(&editboxDst->ev, &editboxSrc->ev, sizeof(editboxDst->ev));


		//////////
		// Duplicate all children for this object
		//////
			iObj_duplicateChildren(editboxDst, editboxSrc);
	}




//////////
//
// Called to copy the indicated image from source to destination
//
//////
	void iiSubobj_copyImage(SObject* imageDst, SObject* imageSrc)
	{
		logfunc(__FUNCTION__);
		//////////
		// Copy all standard properties
		//////
			memcpy(&imageDst->p, &imageSrc->p, sizeof(imageDst->p));


		//////////
		// Copy the allocatables
		//////
			// remember


		//////////
		// Copy the form-specific event handlers
		//////
			memcpy(&imageDst->ev, &imageSrc->ev, sizeof(imageDst->ev));


		//////////
		// Duplicate all children for this object
		//////
			iObj_duplicateChildren(imageDst, imageSrc);
	}




//////////
//
// Called to copy the indicated checkbox from source to destination
//
//////
	void iiSubobj_copyCheckbox(SObject* checkboxDst, SObject* checkboxSrc)
	{
		logfunc(__FUNCTION__);
		//////////
		// Copy all standard properties
		//////
			memcpy(&checkboxDst->p, &checkboxSrc->p, sizeof(checkboxDst->p));


		//////////
		// Copy the allocatables
		//////
			// remember


		//////////
		// Copy the form-specific event handlers
		//////
			memcpy(&checkboxDst->ev, &checkboxSrc->ev, sizeof(checkboxDst->ev));


		//////////
		// Duplicate all children for this object
		//////
			iObj_duplicateChildren(checkboxDst, checkboxSrc);
	}




//////////
//
// Called to copy the indicated option from source to destination
//
//////
	void iiSubobj_copyOption(SObject* optionDst, SObject* optionSrc)
	{
		logfunc(__FUNCTION__);
		//////////
		// Copy all standard properties
		//////
			memcpy(&optionDst->p, &optionSrc->p, sizeof(optionDst->p));


		//////////
		// Copy the allocatables
		//////
			// remember


		//////////
		// Copy the form-specific event handlers
		//////
			memcpy(&optionDst->ev, &optionSrc->ev, sizeof(optionDst->ev));


		//////////
		// Duplicate all children for this object
		//////
			iObj_duplicateChildren(optionDst, optionSrc);
	}




//////////
//
// Called to copy the indicated radio from source to destination
//
//////
	void iiSubobj_copyRadio(SObject* radioDst, SObject* radioSrc)
	{
		logfunc(__FUNCTION__);
		//////////
		// Copy all standard properties
		//////
			memcpy(&radioDst->p, &radioSrc->p, sizeof(radioDst->p));


		//////////
		// Copy the allocatables
		//////
			// remember


		//////////
		// Copy the form-specific event handlers
		//////
			memcpy(&radioDst->ev, &radioSrc->ev, sizeof(radioDst->ev));


		//////////
		// Duplicate all children for this object
		//////
			iObj_duplicateChildren(radioDst, radioSrc);
	}




//////////
//
// Called to copy the indicated cmdGroup from source to destination
//
//////
	void iiSubobj_copyCmdGroup(SObject* cmdGroupDst, SObject* cmdGroupSrc)
	{
		logfunc(__FUNCTION__);
		//////////
		// Copy all standard properties
		//////
			memcpy(&cmdGroupDst->p, &cmdGroupSrc->p, sizeof(cmdGroupDst->p));


		//////////
		// Copy the allocatables
		//////
			// remember


		//////////
		// Copy the form-specific event handlers
		//////
			memcpy(&cmdGroupDst->ev, &cmdGroupSrc->ev, sizeof(cmdGroupDst->ev));


		//////////
		// Duplicate all children for this object
		//////
			iObj_duplicateChildren(cmdGroupDst, cmdGroupSrc);
	}




//////////
//
// Called to copy the indicated optGroup from source to destination
//
//////
	void iiSubobj_copyOptGroup(SObject* optGroupDst, SObject* optGroupSrc)
	{
		logfunc(__FUNCTION__);
		//////////
		// Copy all standard properties
		//////
			memcpy(&optGroupDst->p, &optGroupSrc->p, sizeof(optGroupDst->p));


		//////////
		// Copy the allocatables
		//////
			// remember


		//////////
		// Copy the form-specific event handlers
		//////
			memcpy(&optGroupDst->ev, &optGroupSrc->ev, sizeof(optGroupDst->ev));


		//////////
		// Duplicate all children for this object
		//////
			iObj_duplicateChildren(optGroupDst, optGroupSrc);
	}




//////////
//
// Called to copy the indicated listbox from source to destination
//
//////
	void iiSubobj_copyListbox(SObject* listboxDst, SObject* listboxSrc)
	{
		logfunc(__FUNCTION__);
		//////////
		// Copy all standard properties
		//////
			memcpy(&listboxDst->p, &listboxSrc->p, sizeof(listboxDst->p));


		//////////
		// Copy the allocatables
		//////
			// remember


		//////////
		// Copy the form-specific event handlers
		//////
			memcpy(&listboxDst->ev, &listboxSrc->ev, sizeof(listboxDst->ev));


		//////////
		// Duplicate all children for this object
		//////
			iObj_duplicateChildren(listboxDst, listboxSrc);
	}




//////////
//
// Called to copy the indicated combobox from source to destination
//
//////
	void iiSubobj_copyCombobox(SObject* comboboxDst, SObject* comboboxSrc)
	{
		logfunc(__FUNCTION__);
		//////////
		// Copy all standard properties
		//////
			memcpy(&comboboxDst->p, &comboboxSrc->p, sizeof(comboboxDst->p));


		//////////
		// Copy the allocatables
		//////
			// remember


		//////////
		// Copy the form-specific event handlers
		//////
			memcpy(&comboboxDst->ev, &comboboxSrc->ev, sizeof(comboboxDst->ev));


		//////////
		// Duplicate all children for this object
		//////
			iObj_duplicateChildren(comboboxDst, comboboxSrc);
	}




//////////
//
// Called to copy the indicated formset from source to destination
//
//////
	void iiSubobj_copyFormset(SObject* formsetDst, SObject* formsetSrc)
	{
		logfunc(__FUNCTION__);
		//////////
		// Copy all standard properties
		//////
			memcpy(&formsetDst->p, &formsetSrc->p, sizeof(formsetDst->p));


		//////////
		// Copy the allocatables
		//////
			// remember


		//////////
		// Copy the form-specific event handlers
		//////
			memcpy(&formsetDst->ev, &formsetSrc->ev, sizeof(formsetDst->ev));


		//////////
		// Duplicate all children for this object
		//////
			iObj_duplicateChildren(formsetDst, formsetSrc);
	}




//////////
//
// Called to copy the indicated toolbar from source to destination
//
//////
	void iiSubobj_copyToolbar(SObject* toolbarDst, SObject* toolbarSrc)
	{
		logfunc(__FUNCTION__);
		//////////
		// Copy all standard properties
		//////
			memcpy(&toolbarDst->p, &toolbarSrc->p, sizeof(toolbarDst->p));


		//////////
		// Copy the allocatables
		//////
			// remember


		//////////
		// Copy the form-specific event handlers
		//////
			memcpy(&toolbarDst->ev, &toolbarSrc->ev, sizeof(toolbarDst->ev));


		//////////
		// Duplicate all children for this object
		//////
			iObj_duplicateChildren(toolbarDst, toolbarSrc);
	}




//////////
//
// Called to copy the indicated separator from source to destination
//
//////
	void iiSubobj_copySeparator(SObject* separatorDst, SObject* separatorSrc)
	{
		logfunc(__FUNCTION__);
		//////////
		// Copy all standard properties
		//////
			memcpy(&separatorDst->p, &separatorSrc->p, sizeof(separatorDst->p));


		//////////
		// Copy the allocatables
		//////
			// remember


		//////////
		// Copy the form-specific event handlers
		//////
			memcpy(&separatorDst->ev, &separatorSrc->ev, sizeof(separatorDst->ev));


		//////////
		// Duplicate all children for this object
		//////
			iObj_duplicateChildren(separatorDst, separatorSrc);
	}




//////////
//
// Called to copy the indicated line from source to destination
//
//////
	void iiSubobj_copyLine(SObject* lineDst, SObject* lineSrc)
	{
		logfunc(__FUNCTION__);
		//////////
		// Copy all standard properties
		//////
			memcpy(&lineDst->p, &lineSrc->p, sizeof(lineDst->p));


		//////////
		// Copy the allocatables
		//////
			// remember


		//////////
		// Copy the form-specific event handlers
		//////
			memcpy(&lineDst->ev, &lineSrc->ev, sizeof(lineDst->ev));


		//////////
		// Duplicate all children for this object
		//////
			iObj_duplicateChildren(lineDst, lineSrc);
	}




//////////
//
// Called to copy the indicated shape from source to destination
//
//////
	void iiSubobj_copyShape(SObject* shapeDst, SObject* shapeSrc)
	{
		logfunc(__FUNCTION__);
		//////////
		// Copy all standard properties
		//////
			memcpy(&shapeDst->p, &shapeSrc->p, sizeof(shapeDst->p));


		//////////
		// Copy the allocatables
		//////
			// remember


		//////////
		// Copy the form-specific event handlers
		//////
			memcpy(&shapeDst->ev, &shapeSrc->ev, sizeof(shapeDst->ev));


		//////////
		// Duplicate all children for this object
		//////
			iObj_duplicateChildren(shapeDst, shapeSrc);
	}




//////////
//
// Called to copy the indicated container from source to destination
//
//////
	void iiSubobj_copyContainer(SObject* containerDst, SObject* containerSrc)
	{
		logfunc(__FUNCTION__);
		//////////
		// Copy all standard properties
		//////
			memcpy(&containerDst->p, &containerSrc->p, sizeof(containerDst->p));


		//////////
		// Copy the allocatables
		//////
			// remember


		//////////
		// Copy the form-specific event handlers
		//////
			memcpy(&containerDst->ev, &containerSrc->ev, sizeof(containerDst->ev));


		//////////
		// Duplicate all children for this object
		//////
			iObj_duplicateChildren(containerDst, containerSrc);
	}




//////////
//
// Called to copy the indicated control from source to destination
//
//////
	void iiSubobj_copyControl(SObject* controlDst, SObject* controlSrc)
	{
		logfunc(__FUNCTION__);
		//////////
		// Copy all standard properties
		//////
			memcpy(&controlDst->p, &controlSrc->p, sizeof(controlDst->p));


		//////////
		// Copy the allocatables
		//////
			// remember


		//////////
		// Copy the form-specific event handlers
		//////
			memcpy(&controlDst->ev, &controlSrc->ev, sizeof(controlDst->ev));


		//////////
		// Duplicate all children for this object
		//////
			iObj_duplicateChildren(controlDst, controlSrc);
	}




//////////
//
// Called to copy the indicated grid from source to destination
//
//////
	void iiSubobj_copyGrid(SObject* gridDst, SObject* gridSrc)
	{
		logfunc(__FUNCTION__);
		//////////
		// Copy all standard properties
		//////
			memcpy(&gridDst->p, &gridSrc->p, sizeof(gridDst->p));


		//////////
		// Copy the allocatables
		//////
			// remember


		//////////
		// Copy the form-specific event handlers
		//////
			memcpy(&gridDst->ev, &gridSrc->ev, sizeof(gridDst->ev));


		//////////
		// Duplicate all children for this object
		//////
			iObj_duplicateChildren(gridDst, gridSrc);
	}




//////////
//
// Called to copy the indicated column from source to destination
//
//////
	void iiSubobj_copyColumn(SObject* columnDst, SObject* columnSrc)
	{
		logfunc(__FUNCTION__);
		//////////
		// Copy all standard properties
		//////
			memcpy(&columnDst->p, &columnSrc->p, sizeof(columnDst->p));


		//////////
		// Copy the allocatables
		//////
			// remember


		//////////
		// Copy the form-specific event handlers
		//////
			memcpy(&columnDst->ev, &columnSrc->ev, sizeof(columnDst->ev));


		//////////
		// Duplicate all children for this object
		//////
			iObj_duplicateChildren(columnDst, columnSrc);
	}




//////////
//
// Called to copy the indicated header from source to destination
//
//////
	void iiSubobj_copyHeader(SObject* headerDst, SObject* headerSrc)
	{
		logfunc(__FUNCTION__);
		//////////
		// Copy all standard properties
		//////
			memcpy(&headerDst->p, &headerSrc->p, sizeof(headerDst->p));


		//////////
		// Copy the allocatables
		//////
			// remember


		//////////
		// Copy the form-specific event handlers
		//////
			memcpy(&headerDst->ev, &headerSrc->ev, sizeof(headerDst->ev));


		//////////
		// Duplicate all children for this object
		//////
			iObj_duplicateChildren(headerDst, headerSrc);
	}




//////////
//
// Called to copy the indicated oleBound from source to destination
//
//////
	void iiSubobj_copyOleBound(SObject* oleBoundDst, SObject* oleBoundSrc)
	{
		logfunc(__FUNCTION__);
		//////////
		// Copy all standard properties
		//////
			memcpy(&oleBoundDst->p, &oleBoundSrc->p, sizeof(oleBoundDst->p));


		//////////
		// Copy the allocatables
		//////
			// remember


		//////////
		// Copy the form-specific event handlers
		//////
			memcpy(&oleBoundDst->ev, &oleBoundSrc->ev, sizeof(oleBoundDst->ev));


		//////////
		// Duplicate all children for this object
		//////
			iObj_duplicateChildren(oleBoundDst, oleBoundSrc);
	}




//////////
//
// Called to copy the indicated oleContain from source to destination
//
//////
	void iiSubobj_copyOleContain(SObject* oleContainDst, SObject* oleContainSrc)
	{
		logfunc(__FUNCTION__);
		//////////
		// Copy all standard properties
		//////
			memcpy(&oleContainDst->p, &oleContainSrc->p, sizeof(oleContainDst->p));


		//////////
		// Copy the allocatables
		//////
			// remember


		//////////
		// Copy the form-specific event handlers
		//////
			memcpy(&oleContainDst->ev, &oleContainSrc->ev, sizeof(oleContainDst->ev));


		//////////
		// Duplicate all children for this object
		//////
			iObj_duplicateChildren(oleContainDst, oleContainSrc);
	}




//////////
//
// Called to copy the indicated spinner from source to destination
//
//////
	void iiSubobj_copySpinner(SObject* spinnerDst, SObject* spinnerSrc)
	{
		logfunc(__FUNCTION__);
		//////////
		// Copy all standard properties
		//////
			memcpy(&spinnerDst->p, &spinnerSrc->p, sizeof(spinnerDst->p));


		//////////
		// Copy the allocatables
		//////
			// remember


		//////////
		// Copy the form-specific event handlers
		//////
			memcpy(&spinnerDst->ev, &spinnerSrc->ev, sizeof(spinnerDst->ev));


		//////////
		// Duplicate all children for this object
		//////
			iObj_duplicateChildren(spinnerDst, spinnerSrc);
	}




//////////
//
// Called to copy the indicated timer from source to destination
//
//////
	void iiSubobj_copyTimer(SObject* timerDst, SObject* timerSrc)
	{
		logfunc(__FUNCTION__);
		//////////
		// Copy all standard properties
		//////
			memcpy(&timerDst->p, &timerSrc->p, sizeof(timerDst->p));


		//////////
		// Copy the allocatables
		//////
			// remember


		//////////
		// Copy the form-specific event handlers
		//////
			memcpy(&timerDst->ev, &timerSrc->ev, sizeof(timerDst->ev));


		//////////
		// Duplicate all children for this object
		//////
			iObj_duplicateChildren(timerDst, timerSrc);
	}




//////////
//
// Called to copy the indicated hyperlink from source to destination
//
//////
	void iiSubobj_copyHyperlink(SObject* hyperlinkDst, SObject* hyperlinkSrc)
	{
		logfunc(__FUNCTION__);
		//////////
		// Copy all standard properties
		//////
			memcpy(&hyperlinkDst->p, &hyperlinkSrc->p, sizeof(hyperlinkDst->p));


		//////////
		// Copy the allocatables
		//////
			// remember


		//////////
		// Copy the form-specific event handlers
		//////
			memcpy(&hyperlinkDst->ev, &hyperlinkSrc->ev, sizeof(hyperlinkDst->ev));


		//////////
		// Duplicate all children for this object
		//////
			iObj_duplicateChildren(hyperlinkDst, hyperlinkSrc);
	}




//////////
//
// Called to copy the indicated collection from source to destination
//
//////
	void iiSubobj_copyCollection(SObject* collectionDst, SObject* collectionSrc)
	{
		logfunc(__FUNCTION__);
		//////////
		// Copy all standard properties
		//////
			memcpy(&collectionDst->p, &collectionSrc->p, sizeof(collectionDst->p));


		//////////
		// Copy the allocatables
		//////
			// remember


		//////////
		// Copy the form-specific event handlers
		//////
			memcpy(&collectionDst->ev, &collectionSrc->ev, sizeof(collectionDst->ev));


		//////////
		// Duplicate all children for this object
		//////
			iObj_duplicateChildren(collectionDst, collectionSrc);
	}




//////////
//
// Called to copy the indicated page from source to destination
//
//////
	void iiSubobj_copyPage(SObject* pageDst, SObject* pageSrc)
	{
		logfunc(__FUNCTION__);
		//////////
		// Copy all standard properties
		//////
			memcpy(&pageDst->p, &pageSrc->p, sizeof(pageDst->p));


		//////////
		// Copy the allocatables
		//////
			// remember


		//////////
		// Copy the form-specific event handlers
		//////
			memcpy(&pageDst->ev, &pageSrc->ev, sizeof(pageDst->ev));


		//////////
		// Duplicate all children for this object
		//////
			iObj_duplicateChildren(pageDst, pageSrc);
	}




//////////
//
// Called to copy the indicated pageframe from source to destination
//
//////
	void iiSubobj_copyPageframe(SObject* pageframeDst, SObject* pageframeSrc)
	{
		logfunc(__FUNCTION__);
		//////////
		// Copy all standard properties
		//////
			memcpy(&pageframeDst->p, &pageframeSrc->p, sizeof(pageframeDst->p));


		//////////
		// Copy the allocatables
		//////
			// remember


		//////////
		// Copy the form-specific event handlers
		//////
			memcpy(&pageframeDst->ev, &pageframeSrc->ev, sizeof(pageframeDst->ev));


		//////////
		// Duplicate all children for this object
		//////
			iObj_duplicateChildren(pageframeDst, pageframeSrc);
	}




//////////
//
// Called to copy the indicated session from source to destination
//
//////
	void iiSubobj_copySession(SObject* sessionDst, SObject* sessionSrc)
	{
		logfunc(__FUNCTION__);
		//////////
		// Copy all standard properties
		//////
			memcpy(&sessionDst->p, &sessionSrc->p, sizeof(sessionDst->p));


		//////////
		// Copy the allocatables
		//////
			// remember


		//////////
		// Copy the form-specific event handlers
		//////
			memcpy(&sessionDst->ev, &sessionSrc->ev, sizeof(sessionDst->ev));


		//////////
		// Duplicate all children for this object
		//////
			iObj_duplicateChildren(sessionDst, sessionSrc);
	}




//////////
//
// Called to copy the indicated custom from source to destination
//
//////
	void iiSubobj_copyCustom(SObject* customDst, SObject* customSrc)
	{
		logfunc(__FUNCTION__);
		//////////
		// Copy all standard properties
		//////
			memcpy(&customDst->p, &customSrc->p, sizeof(customDst->p));


		//////////
		// Copy the allocatables
		//////
			// remember


		//////////
		// Copy the form-specific event handlers
		//////
			memcpy(&customDst->ev, &customSrc->ev, sizeof(customDst->ev));


		//////////
		// Duplicate all children for this object
		//////
			iObj_duplicateChildren(customDst, customSrc);
	}




//////////
//
// Called to copy the indicated exception from source to destination
//
//////
	void iiSubobj_copyException(SObject* exceptionDst, SObject* exceptionSrc)
	{
		logfunc(__FUNCTION__);
		//////////
		// Copy all standard properties
		//////
			memcpy(&exceptionDst->p, &exceptionSrc->p, sizeof(exceptionDst->p));


		//////////
		// Copy the allocatables
		//////
			// remember


		//////////
		// Copy the form-specific event handlers
		//////
			memcpy(&exceptionDst->ev, &exceptionSrc->ev, sizeof(exceptionDst->ev));


		//////////
		// Duplicate all children for this object
		//////
			iObj_duplicateChildren(exceptionDst, exceptionSrc);
	}
