//////////
//
// /libsf/source/vjr/source/objects/delete.cpp
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
// Called to delete the common properties
//
//////
	void iObj_deleteCommon(SObject* obj)
	{
		SWindow* win;


		//////////
		// See if this object is the top-level object to any windows, and if so disconnect it
		//////
			win = iWindow_findByObj(obj);
			if (win)
				iWindow_disconnectObj(win, obj);

// TODO:  iterate through obj->props and delete all
	}




//////////
//
// Called to delete the empty.
//
//////
	void iSubobj_deleteEmpty(SObject* empty, bool tlDeleteSelf)
	{
		logfunc(__FUNCTION__);
		//////////
		// Free common components
		//////
			iObj_deleteCommon(empty);


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
	void iSubobj_deleteForm(SObject* form, bool tlDeleteSelf)
	{
		logfunc(__FUNCTION__);
		//////////
		// Free common components
		//////
			iObj_deleteCommon(form);


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
	void iSubobj_deleteSubform(SObject* subform, bool tlDeleteSelf)
	{
		logfunc(__FUNCTION__);
		//////////
		// Free common components
		//////
			iObj_deleteCommon(subform);


		//////////
		// Free self
		//////
			if (tlDeleteSelf)
				free(subform);
	}




//////////
//
// Called to delete the carousel
//
//////
	void iSubobj_deleteCarousel(SObject* carousel, bool tlDeleteSelf, bool tlLeaveRiders, bool tlLeaveObjects)
	{
		SObject* rider;
		SObject* riderNext;


		logfunc(__FUNCTION__);
		//////////
		// Free common components
		//////
			iObj_deleteCommon(carousel);


		//////////
		// Act on riders
		//////
			if (tlLeaveRiders)
			{
				// We just need to orphanize each one
//////////
// Note:  Orphanizing riders is a potentially precarious thing.  They must be known as they are
//        not maintained in a buffer somewhere.  Typically this only occurs when migrating the
//        last rider from one carousel to another.  But regardless, care must be taken to prevent
//        the orphaned rider from hanging around unused and forgotten.
//////
				// Get the first
				rider = carousel->firstChild;

				// Mark the parent as now being free from children
				carousel->firstChild = NULL;

				// Iterate for every rider
				while (rider)
				{
					// Determine the next rider
					riderNext = (SObject*)rider->ll.next;

					// Orphanize this rider
					iLl_orphanize__ll((SLL*)rider);

					// Move to next rider
					rider = riderNext;
				}

			} else {
				// They are being deleted
				iObj_delete(&carousel->firstChild, true, true, true);
			}


		//////////
		// Free self
		//////
			if (tlDeleteSelf)
				free(carousel);
	}




//////////
//
// Called to delete the rider
//
//////
	void iSubobj_deleteRider(SObject* rider, bool tlDeleteSelf, bool tlLeaveObjects)
	{
		logfunc(__FUNCTION__);
		//////////
		// Free common components
		//////
			iObj_deleteCommon(rider);


		//////////
		// Act on objects
		//////
			if (!tlLeaveObjects)
				iObj_delete(&rider->firstChild, true, true, true);		// They are being deleted


		//////////
		// Free self
		//////
			if (tlDeleteSelf)
				free(rider);
	}




//////////
//
// Called to delete the label.
//
//////
	void iSubobj_deleteLabel(SObject* label, bool tlDeleteSelf)
	{
		logfunc(__FUNCTION__);
		//////////
		// Free common components
		//////
			iObj_deleteCommon(label);


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
	void iSubobj_deleteTextbox(SObject* textbox, bool tlDeleteSelf)
	{
		logfunc(__FUNCTION__);
		//////////
		// Free common components
		//////
			iObj_deleteCommon(textbox);


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
	void iSubobj_deleteButton(SObject* button, bool tlDeleteSelf)
	{
		logfunc(__FUNCTION__);
		//////////
		// Free common components
		//////
			iObj_deleteCommon(button);


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
	void iSubobj_deleteEditbox(SObject* editbox, bool tlDeleteSelf)
	{
		logfunc(__FUNCTION__);
		//////////
		// Free common components
		//////
			iObj_deleteCommon(editbox);


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
	void iSubobj_deleteImage(SObject* image, bool tlDeleteSelf)
	{
		logfunc(__FUNCTION__);
		//////////
		// Free common components
		//////
			iObj_deleteCommon(image);


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
	void iSubobj_deleteCheckbox(SObject* checkbox, bool tlDeleteSelf)
	{
		logfunc(__FUNCTION__);
		//////////
		// Free common components
		//////
			iObj_deleteCommon(checkbox);


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
	void iSubobj_deleteOption(SObject* option, bool tlDeleteSelf)
	{
		logfunc(__FUNCTION__);
		//////////
		// Free common components
		//////
			iObj_deleteCommon(option);


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
	void iSubobj_deleteRadio(SObject* radio, bool tlDeleteSelf)
	{
		logfunc(__FUNCTION__);
		//////////
		// Free common components
		//////
			iObj_deleteCommon(radio);


		//////////
		// Free self
		//////
			if (tlDeleteSelf)
				free(radio);
	}




//////////
//
// Called to delete the cmdGroup.
//
//////
	void iSubobj_deleteCmdGroup(SObject* cmdGroup, bool tlDeleteSelf)
	{
		logfunc(__FUNCTION__);
		//////////
		// Free common components
		//////
			iObj_deleteCommon(cmdGroup);


		//////////
		// Free self
		//////
			if (tlDeleteSelf)
				free(cmdGroup);
	}




//////////
//
// Called to delete the optGroup.
//
//////
	void iSubobj_deleteOptGroup(SObject* optGroup, bool tlDeleteSelf)
	{
		logfunc(__FUNCTION__);
		//////////
		// Free common components
		//////
			iObj_deleteCommon(optGroup);


		//////////
		// Free self
		//////
			if (tlDeleteSelf)
				free(optGroup);
	}




//////////
//
// Called to delete the listbox.
//
//////
	void iSubobj_deleteListbox(SObject* listbox, bool tlDeleteSelf)
	{
		logfunc(__FUNCTION__);
		//////////
		// Free common components
		//////
			iObj_deleteCommon(listbox);


		//////////
		// Free self
		//////
			if (tlDeleteSelf)
				free(listbox);
	}




//////////
//
// Called to delete the combobox.
//
//////
	void iSubobj_deleteCombobox(SObject* combobox, bool tlDeleteSelf)
	{
		logfunc(__FUNCTION__);
		//////////
		// Free common components
		//////
			iObj_deleteCommon(combobox);


		//////////
		// Free self
		//////
			if (tlDeleteSelf)
				free(combobox);
	}




//////////
//
// Called to delete the formset.
//
//////
	void iSubobj_deleteFormset(SObject* formset, bool tlDeleteSelf)
	{
		logfunc(__FUNCTION__);
		//////////
		// Free common components
		//////
			iObj_deleteCommon(formset);


		//////////
		// Free self
		//////
			if (tlDeleteSelf)
				free(formset);
	}




//////////
//
// Called to delete the toolbar.
//
//////
	void iSubobj_deleteToolbar(SObject* toolbar, bool tlDeleteSelf)
	{
		logfunc(__FUNCTION__);
		//////////
		// Free common components
		//////
			iObj_deleteCommon(toolbar);


		//////////
		// Free self
		//////
			if (tlDeleteSelf)
				free(toolbar);
	}




//////////
//
// Called to delete the separator.
//
//////
	void iSubobj_deleteSeparator(SObject* separator, bool tlDeleteSelf)
	{
		logfunc(__FUNCTION__);
		//////////
		// Free common components
		//////
			iObj_deleteCommon(separator);


		//////////
		// Free self
		//////
			if (tlDeleteSelf)
				free(separator);
	}




//////////
//
// Called to delete the line.
//
//////
	void iSubobj_deleteLine(SObject* line, bool tlDeleteSelf)
	{
		logfunc(__FUNCTION__);
		//////////
		// Free common components
		//////
			iObj_deleteCommon(line);


		//////////
		// Free self
		//////
			if (tlDeleteSelf)
				free(line);
	}




//////////
//
// Called to delete the shape.
//
//////
	void iSubobj_deleteShape(SObject* shape, bool tlDeleteSelf)
	{
		logfunc(__FUNCTION__);
		//////////
		// Free common components
		//////
			iObj_deleteCommon(shape);


		//////////
		// Free self
		//////
			if (tlDeleteSelf)
				free(shape);
	}




//////////
//
// Called to delete the container.
//
//////
	void iSubobj_deleteContainer(SObject* container, bool tlDeleteSelf)
	{
		logfunc(__FUNCTION__);
		//////////
		// Free common components
		//////
			iObj_deleteCommon(container);


		//////////
		// Free self
		//////
			if (tlDeleteSelf)
				free(container);
	}




//////////
//
// Called to delete the control.
//
//////
	void iSubobj_deleteControl(SObject* control, bool tlDeleteSelf)
	{
		logfunc(__FUNCTION__);
		//////////
		// Free common components
		//////
			iObj_deleteCommon(control);


		//////////
		// Free self
		//////
			if (tlDeleteSelf)
				free(control);
	}




//////////
//
// Called to delete the grid.
//
//////
	void iSubobj_deleteGrid(SObject* grid, bool tlDeleteSelf)
	{
		logfunc(__FUNCTION__);
		//////////
		// Free common components
		//////
			iObj_deleteCommon(grid);


		//////////
		// Free self
		//////
			if (tlDeleteSelf)
				free(grid);
	}




//////////
//
// Called to delete the column.
//
//////
	void iSubobj_deleteColumn(SObject* column, bool tlDeleteSelf)
	{
		logfunc(__FUNCTION__);
		//////////
		// Free common components
		//////
			iObj_deleteCommon(column);


		//////////
		// Free self
		//////
			if (tlDeleteSelf)
				free(column);
	}




//////////
//
// Called to delete the header.
//
//////
	void iSubobj_deleteHeader(SObject* header, bool tlDeleteSelf)
	{
		logfunc(__FUNCTION__);
		//////////
		// Free common components
		//////
			iObj_deleteCommon(header);


		//////////
		// Free self
		//////
			if (tlDeleteSelf)
				free(header);
	}




//////////
//
// Called to delete the oleBound.
//
//////
	void iSubobj_deleteOleBound(SObject* oleBound, bool tlDeleteSelf)
	{
		logfunc(__FUNCTION__);
		//////////
		// Free common components
		//////
			iObj_deleteCommon(oleBound);


		//////////
		// Free self
		//////
			if (tlDeleteSelf)
				free(oleBound);
	}




//////////
//
// Called to delete the oleContain.
//
//////
	void iSubobj_deleteOleContain(SObject* oleContain, bool tlDeleteSelf)
	{
		logfunc(__FUNCTION__);
		//////////
		// Free common components
		//////
			iObj_deleteCommon(oleContain);


		//////////
		// Free self
		//////
			if (tlDeleteSelf)
				free(oleContain);
	}




//////////
//
// Called to delete the spinner.
//
//////
	void iSubobj_deleteSpinner(SObject* spinner, bool tlDeleteSelf)
	{
		logfunc(__FUNCTION__);
		//////////
		// Free common components
		//////
			iObj_deleteCommon(spinner);


		//////////
		// Free self
		//////
			if (tlDeleteSelf)
				free(spinner);
	}




//////////
//
// Called to delete the timer.
//
//////
	void iSubobj_deleteTimer(SObject* timer, bool tlDeleteSelf)
	{
		logfunc(__FUNCTION__);
		//////////
		// Free common components
		//////
			iObj_deleteCommon(timer);


		//////////
		// Free self
		//////
			if (tlDeleteSelf)
				free(timer);
	}




//////////
//
// Called to delete the hyperlink.
//
//////
	void iSubobj_deleteHyperlink(SObject* hyperlink, bool tlDeleteSelf)
	{
		logfunc(__FUNCTION__);
		//////////
		// Free common components
		//////
			iObj_deleteCommon(hyperlink);


		//////////
		// Free self
		//////
			if (tlDeleteSelf)
				free(hyperlink);
	}




//////////
//
// Called to delete the collection.
//
//////
	void iSubobj_deleteCollection(SObject* collection, bool tlDeleteSelf)
	{
		logfunc(__FUNCTION__);
		//////////
		// Free common components
		//////
			iObj_deleteCommon(collection);


		//////////
		// Free self
		//////
			if (tlDeleteSelf)
				free(collection);
	}




//////////
//
// Called to delete the page.
//
//////
	void iSubobj_deletePage(SObject* page, bool tlDeleteSelf)
	{
		logfunc(__FUNCTION__);
		//////////
		// Free common components
		//////
			iObj_deleteCommon(page);


		//////////
		// Free self
		//////
			if (tlDeleteSelf)
				free(page);
	}




//////////
//
// Called to delete the pageFrame.
//
//////
	void iSubobj_deletePageFrame(SObject* pageFrame, bool tlDeleteSelf)
	{
		logfunc(__FUNCTION__);
		//////////
		// Free common components
		//////
			iObj_deleteCommon(pageFrame);


		//////////
		// Free self
		//////
			if (tlDeleteSelf)
				free(pageFrame);
	}




//////////
//
// Called to delete the session.
//
//////
	void iSubobj_deleteSession(SObject* session, bool tlDeleteSelf)
	{
		logfunc(__FUNCTION__);
		//////////
		// Free common components
		//////
			iObj_deleteCommon(session);


		//////////
		// Free self
		//////
			if (tlDeleteSelf)
				free(session);
	}




//////////
//
// Called to delete the custom.
//
//////
	void iSubobj_deleteCustom(SObject* custom, bool tlDeleteSelf)
	{
		logfunc(__FUNCTION__);
		//////////
		// Free common components
		//////
			iObj_deleteCommon(custom);


		//////////
		// Free self
		//////
			if (tlDeleteSelf)
				free(custom);
	}




//////////
//
// Called to delete the exception.
//
//////
	void iSubobj_deleteException(SObject* exception, bool tlDeleteSelf)
	{
		logfunc(__FUNCTION__);
		//////////
		// Free common components
		//////
			iObj_deleteCommon(exception);


		//////////
		// Free self
		//////
			if (tlDeleteSelf)
				free(exception);
	}




//////////
//
// Called to delete the settings.
//
//////
	void iSubobj_deleteSettings(SObject* settings, bool tlDeleteSelf)
	{
		logfunc(__FUNCTION__);
		//////////
		// Free common components
		//////
			iObj_deleteCommon(settings);


		//////////
		// Free self
		//////
			if (tlDeleteSelf)
				free(settings);
	}




//////////
//
// Called to delete the control point.
//
//////
	void iSubobj_deleteControlPoint(SObject* controlPoint, bool tlDeleteSelf)
	{
		logfunc(__FUNCTION__);
		//////////
		// Free common components
		//////
			iObj_deleteCommon(controlPoint);


		//////////
		// Free self
		//////
			if (tlDeleteSelf)
				free(controlPoint);
	}
