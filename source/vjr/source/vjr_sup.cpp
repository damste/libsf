//////////
//
// /libsf/source/vjr/source/vjr_sup.cpp
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




//////////
//
// Creates a new toolbar from the indicated XML file
//
//////
	SObject* iToolbar_loadFrom_xml(cu8* tcXml, u32 tnXmlLength, cs8* tcTagRoot, cs8* tcTagSub)
	{
		SBitmap*	bmpIconRef;
		CXmlp		bxml, bxmlRoot, bxmlRootSub, bxmlToolbars, bxmlToolbar, bxmlName, bxmlIcon, bxmlIconName;
		XmlDatap	xdNameData, xdIconNameData;
		SObjectp	lo, loToolbar, loContainer;
		SDatum		d;


		//////////
		// Load our bxml file
		//////
			bxml = xml_loadAs_cxml(tcXml, tnXmlLength);
			if (!bxml)
			{
				debug_break;	// Should never happen
				return(NULL);
			}


		//////////
		// Looking for <tctagRoot><tcTagSub><toolbars><icon> to iterate through each <toolbar> item within
		// <tcTagRoot>
		//////
			bxmlRoot = bxml->child(tcTagRoot);
			if (!bxmlRoot)
			{
				debug_break;	// Should not happen
				return(NULL);
			}
			

		//////////
		//	<tcTagRoot>
		//		<tcTagSub>
		//////
			bxmlRootSub = bxmlRoot->child(tcTagSub);
			if (!bxmlRootSub)
			{
				debug_break;	// Should not happen
				return(NULL);
			}
			

		//////////
		//	<tcTagRoot>
		//		<tcTagSub>
		//			<toolbars>
		//////
			bxmlToolbars = bxmlRootSub->child(cgcTag_toolbars);
			if (!bxmlToolbars)
			{
				debug_break;	// Should not happen
				return(NULL);
			}


		//////////
		// Create the container
		//////
			loContainer = iObj_create(_OBJ_TYPE_CONTAINER, NULL);
			if (!loContainer)
			{
				debug_break;	// Should never happen
				return(NULL);
			}


		//////////
		// Iterate through the toolbar looking for toolbar items
		//	<tcTagRoot>
		//		<tcTagSub>
		//			<toolbars name="...">
		//				<toolbar name="..."/>
		//////
			memset(&d, 0, sizeof(d));
			for (bxmlToolbar = bxmlToolbars->child(); bxmlToolbar; bxmlToolbar = bxmlToolbar->next())
			{
				// Looking only for the toolbar tags
				if (bxmlToolbar->tag()->length() == sizeof(cgcTag_toolbar) - 1 && _memicmp(bxmlToolbar->tag()->as_s8p(), cgcTag_toolbar, sizeof(cgcTag_toolbar) - 1) == 0)
				{
					// It's a toolbar, make sure it has a name attribute
					if ((bxmlName = bxmlToolbar->attribute(cgcTag_name)) && (xdNameData = bxmlName->data()))
					{
						// Construct the toolbar instance
						loToolbar = iObj_addChild(_OBJ_TYPE_TOOLBAR, loContainer);
						if (!loToolbar)
						{
							debug_break;	// Should never happen

						} else {
							// Assign its name
							iObjProp_set_character_direct(loToolbar, _INDEX_NAME, xdNameData->as_datum(&d));


							//////////
							//	<tcTagRoot>
							//		<tcTagSub>
							//			<toolbars name="...">
							//				<toolbar name="..."/>
							//					<icon name="..."/>
							//
							// Iterate through each icon for this toolbar
							//////
								for (bxmlIcon = bxmlToolbar->child(); bxmlIcon; bxmlIcon = bxmlIcon->next())
								{
									// Verify it's an icon tag
									if ((xdIconNameData = bxmlIcon->tag()) && iDatum_compare(xdIconNameData->as_datum(&d), cgcTag_icon, sizeof(cgcTag_icon) - 1) == 0)
									{
										// Extract the name attribute
										if ((bxmlIconName = bxmlIcon->attribute(cgcTag_name)) && (xdIconNameData = bxmlIconName->data()))
										{
											// Find out what it is
											if (xdIconNameData->length() == sizeof(cgcTag_separator) - 1 && iDatum_compare(xdIconNameData->as_datum(&d), cgcTag_separator, sizeof(cgcTag_separator) - 1) == 0)
											{
												// Append the separator
												lo = iObj_addChild(_OBJ_TYPE_SEPARATOR, loToolbar);
												if (!lo)
													debug_break;	// Should never happen

											} else {

												// Locate the associated icon
												bmpIconRef = iBmp_arrayBmp_getRef(bxmlArrayBmpIcons, bmpArray, xdIconNameData->as_s8p(), xdIconNameData->length());
												if (!bmpIconRef)
												{
													// Should never happen
													// If we get here, we're searching for the tag in xdIconNameData, which is not a known icon in the bmpArray icon strip
													debug_break;
												}

												// Append the image instance
												lo = iObj_addChild(_OBJ_TYPE_IMAGE, loToolbar);
												if (!lo)
													debug_break;	// Should never happen

												// Set the size and copy the bitmap
												iObj_setSize(lo, 0, 0, bmpIconRef->bi.biWidth, bmpIconRef->bi.biHeight);
												propSetBackStyle		(lo, _BACK_STYLE_TRANSPARENT);
												propSetBackMask			(lo, _LOGICAL_TRUE);
												propSetPictureBmp		(lo, bmpIconRef);
												propSetPictureBmpDown	(lo, bmpIconRef);
											}
										}
									}
								}

						}
					}
				}
			}


		//////////
		// Indicate the fruits of our labors
		//////
			return(loContainer);
	}




//////////
//
// Called to create toolbars on the individual object
//
//////
	bool iToolbar_applyTo_obj(SObject* objParent, SObject* objToolbarContainer, cu8* tcXml, u32 tnXmlLength, cs8* tcTagRoot, cs8* tcTagSub)
	{
		s32			lnX, lnY, lnWidth, lnHeight, lnIconWidth, lnIconHeight;
		bool		llResult, llVisible;
		CXmlp		bxml, bxmlRoot, bxmlRootSub, bxmlToolbars, bxmlToolbar, bxmlName, bxmlX, bxmlY, bxmlWidth, bxmlHeight, bxmlIconWidth, bxmlIconHeight, bxmlVisible;
		XmlDatap	xdTag, xdTagName, xdX, xdY, xdWidth, xdHeight, xdIconWidth, xdIconHeight, xdVisible;
		SObject*	loToolbarSource;		// The source instance in the toolbar container
		SObject*	loToolbarCopy;			// The copy we create
		SObject*	objToolbarItem;
		SDatum		d;


		//////////
		// Load our bxml file
		//////
			bxml = xml_loadAs_cxml(tcXml, tnXmlLength);
			if (!bxml)
			{
				debug_break;	// Should never happen
				return(false);
			}


		//////////
		// Looking for <tctagRoot><tcTagSub><layout> to iterate through each <toolbar> item within
		// <tcTagRoot>
		//////
			if (!(bxmlRoot = bxml->child(tcTagRoot)))
			{
				debug_break;	// Should not happen
				return(false);
			}
			

		//////////
		//	<tcTagRoot>
		//		<tcTagSub>
		//////
			if (!(bxmlRootSub = bxmlRoot->child(tcTagSub)))
			{
				debug_break;	// Should not happen
				return(false);
			}
			

		//////////
		//	<tcTagRoot>
		//		<tcTagSub>
		//			<layout>
		//////
			if (!(bxmlToolbars = bxmlRootSub->child(cgcTag_layout)))
			{
				debug_break;	// Should not happen
				return(false);
			}


		//////////
		// Iterate through the toolbar looking for toolbar items
		//	<tcTagRoot>
		//		<tcTagSub>
		//			<layout>
		//				<toolbar name="..."/>
		//////
			memset(&d, 0, sizeof(d));
			for (llResult = true, bxmlToolbar = bxmlToolbars->child(); bxmlToolbar; bxmlToolbar = bxmlToolbar->next())
			{
				// Looking only for toolbar entries
				if ((xdTag = bxmlToolbar->tag()) && xdTag->length() == sizeof(cgcTag_toolbar) - 1 && iDatum_compare(xdTag->as_datum(&d), cgcTag_toolbar, sizeof(cgcTag_toolbar) - 1) == 0)
				{
					// Grabbing names
					if ((bxmlName = bxmlToolbar->attribute(cgcTag_name)) && (xdTagName = bxmlName->data()))
					{
						// Make sure this toolbar reference is in the container
						if ((loToolbarSource = iiObj_findChildObject_byName(objToolbarContainer->firstChild, xdTagName->as_datum(&d), true, false, true)))
						{

							//////////
							// Construct the toolbar class copy
							//////
								loToolbarCopy = iObj_copy(loToolbarSource, NULL, NULL, NULL, true, false, true);
								if (!loToolbarCopy)
									debug_break;	// Should never happen

								// Store the parent
								loToolbarCopy->parent = objParent;

								// Right now, loToolbarCopy is an orphan object
								// Give it a parent
								if (!iLl_appendExistingNodeAtEnd((SLL**)&objParent, (SLL*)loToolbarCopy))
									debug_break;	// Should never happen

								// Locate the first icon in the toolbar
								for (objToolbarItem = loToolbarCopy->firstChild; objToolbarItem; objToolbarItem = objToolbarItem->ll.nextObj)
								{
									if (objToolbarItem->objType == _OBJ_TYPE_IMAGE)
										break;
								}


							//////////
							// Check layout properties and assign coordinates and sizes
							//////
								bxmlX			= bxmlToolbar->attribute(cgcTag_x);
								bxmlY			= bxmlToolbar->attribute(cgcTag_y);
								bxmlWidth		= bxmlToolbar->attribute(cgcTag_width);
								bxmlHeight		= bxmlToolbar->attribute(cgcTag_height);
								bxmlIconWidth	= bxmlToolbar->attribute(cgcTag_iconWidth);
								bxmlIconHeight	= bxmlToolbar->attribute(cgcTag_iconHeight);
								bxmlVisible		= bxmlToolbar->attribute(cgcTag_visible);


							//////////
							// Convert found tags to data
							//////
								xdX				= (XmlData*)iif(iIsNotNull(bxmlX),				bxmlX->data(),				NULL);
								xdY				= (XmlData*)iif(iIsNotNull(bxmlY),				bxmlY->data(),				NULL);
								xdWidth			= (XmlData*)iif(iIsNotNull(bxmlWidth),			bxmlWidth->data(),			NULL);
								xdHeight		= (XmlData*)iif(iIsNotNull(bxmlHeight),			bxmlHeight->data(),			NULL);
								xdIconWidth		= (XmlData*)iif(iIsNotNull(bxmlIconWidth),		bxmlIconWidth->data(),		NULL);
								xdIconHeight	= (XmlData*)iif(iIsNotNull(bxmlIconHeight),		bxmlIconHeight->data(),		NULL);


							//////////
							// Derive their values
							//////
								lnX				= iif(iIsNotNull(xdX),				xdX->as_s32(),		0);
								lnY				= iif(iIsNotNull(xdY),				xdY->as_s32(),		0);
								lnWidth			= iif(iIsNotNull(xdWidth),			xdWidth->as_s32(),	16);
								lnHeight		= iif(iIsNotNull(xdHeight),			xdHeight->as_s32(),	16);
								lnIconWidth		= iif(iIsNotNull(xdIconWidth),		xdIconWidth->as_s32(),	iif(iIsNotNull(objToolbarItem), objToolbarItem->rc.right - objToolbarItem->rc.left, 36));
								lnIconHeight	= iif(iIsNotNull(xdIconHeight),		xdIconHeight->as_s32(),	iif(iIsNotNull(objToolbarItem), objToolbarItem->rc.bottom - objToolbarItem->rc.top, 36));


							//////////
							// Set the visible status
							//////
								xdVisible = (XmlData*)iif(iIsNotNull(bxmlVisible), bxmlVisible->data(), NULL);
								if (xdVisible)
								{
									// Try to derive the actual value
									if (!iIsBoolText(xdVisible->as_datum(&d), &llVisible, false))
										llVisible = true;	// Fall back on true

								} else {
									// Default to visible
									llVisible = true;
								}


							//////////
							// Toolbars can be sized smaller than the icons they initially possess.
							// We trim down the icon's rectangular size to the indicated iconX and iconY sizes.
							//////
								for (objToolbarItem = loToolbarCopy->firstChild; objToolbarItem; objToolbarItem = objToolbarItem->ll.nextObj)
								{
									// Make it appropriately visible or not visible
									propSetVisible_fromBool(objToolbarItem, llVisible);

									// Is it an icon?
									if (objToolbarItem->objType == _OBJ_TYPE_IMAGE)
										iObj_setSize(objToolbarItem, objToolbarItem->rc.left, objToolbarItem->rc.top, lnIconWidth, lnIconHeight);
								}


							//////////
							// Set the properties for this toolbar
							//////
								iObj_setSize(loToolbarCopy, lnX, lnY, lnWidth, lnHeight);
								propSetVisible_fromBool(loToolbarCopy, llVisible);
								propSetMargin(loToolbarCopy, 6);

						}
					}
				}
			}


		//////////
		// Indicate the fruits of our labors
		//////
			return(llResult);

	}




//////////
//
// Temporary manual function to create the new JDebi screen
//
//////
	void iVjr_init_jdebi_create(void)
	{
		SThisCode*	thisCode = NULL;
		SObject*	obj;
		s32			lnLeft, lnTop, lnWidth, lnHeight;
		RECT		lrc;


		//////////
		// Create the object and its sub-objects
		//////
			// Create object
			_jdebi = iObj_create(_OBJ_TYPE_FORM, NULL);
			if (!_jdebi)
				return;

			// Set the app icon and enable the border
			propSetPictureBmp(_jdebi, bmpJDebiIcon);
			propSetBorderStyle(_jdebi, _BORDER_STYLE_FIXED);

			// Give it a fixed point font
			_jdebi->p.font = iFont_create(cgcFontName_defaultFixed, 10, FW_MEDIUM, false, false);


		//////////
		// Size it to just under half the screen initially
		//////
			GetWindowRect(GetDesktopWindow(), &lrc);
			lnWidth		= (lrc.right - lrc.left);
			lnHeight	= (lrc.bottom - lrc.top);


		//////////
		// Size and position it
		//////
			lnLeft		= (lrc.right  - lrc.left) / 32;
			lnTop		= (lrc.bottom - lrc.top)  / 32;
			lnWidth		-= (2 * lnLeft);
			lnHeight	-= (2 * lnTop);
			iObj_setSize(_jdebi, lnLeft, lnTop, lnWidth, lnHeight);


		//////////
		// Create the subforms
		//////
			_sourceCode		= iObj_addChild(_OBJ_TYPE_SUBFORM, _jdebi);
			_locals			= iObj_addChild(_OBJ_TYPE_SUBFORM, _jdebi);
			_watch			= iObj_addChild(_OBJ_TYPE_SUBFORM, _jdebi);
			_cmd			= iObj_addChild(_OBJ_TYPE_SUBFORM, _jdebi);
			_debug			= iObj_addChild(_OBJ_TYPE_SUBFORM, _jdebi);
			_output			= iObj_addChild(_OBJ_TYPE_SUBFORM, _jdebi);
			_sourceLight	= iObj_addChild(_OBJ_TYPE_SUBFORM, _jdebi);
			_screen			= iObj_addChild(_OBJ_TYPE_SUBFORM, _jdebi);

			// Set the names, icons, and make them visible
			propSetName(_sourceCode,	cgcName_sourceCode,		sizeof(cgcName_sourceCode) - 1);
			propSetName(_locals,		cgcName_locals,			sizeof(cgcName_locals) - 1);
			propSetName(_watch,			cgcName_watch,			sizeof(cgcName_watch) - 1);
			propSetName(_cmd,			cgcName_command,		sizeof(cgcName_command) - 1);
			propSetName(_debug,			cgcName_debug,			sizeof(cgcName_debug) - 1);
			propSetName(_output,		cgcName_output,			sizeof(cgcName_output) - 1);
			propSetName(_sourceLight,	cgcName_sourceLight,	sizeof(cgcName_sourceLight) - 1);
			propSetName(_screen,		cgcName_screen,			sizeof(cgcName_screen) - 1);
			propSetName(_jdebi,			cgcName_jdebi,			sizeof(cgcName_jdebi) - 1);

			propSetIcon(_sourceCode,	bmpSourceCodeIcon);
			propSetIcon(_locals,		bmpLocalsIcon);
			propSetIcon(_watch,			bmpWatchIcon);
			propSetIcon(_cmd,			bmpCommandIcon);
			propSetIcon(_debug,			bmpDebugIcon);
			propSetIcon(_output,		bmpOutputIcon);
			propSetIcon(_sourceLight,	bmpSourceLightIcon);
			propSetIcon(_screen,		bmpVjrIcon);
			propSetIcon(_jdebi,			bmpJDebiIcon);

			propSetVisible(_sourceCode,		_LOGICAL_TRUE);		propSetBorderStyle(_sourceCode,		_BORDER_STYLE_FIXED);
			propSetVisible(_locals,			_LOGICAL_TRUE);		propSetBorderStyle(_locals,			_BORDER_STYLE_FIXED);
			propSetVisible(_watch,			_LOGICAL_TRUE);		propSetBorderStyle(_watch,			_BORDER_STYLE_FIXED);
			propSetVisible(_cmd,			_LOGICAL_TRUE);		propSetBorderStyle(_cmd,			_BORDER_STYLE_FIXED);
			propSetVisible(_sourceLight,	_LOGICAL_TRUE);		propSetBorderStyle(_sourceLight,	_BORDER_STYLE_FIXED);
			propSetVisible(_screen,			_LOGICAL_TRUE);		propSetBorderStyle(_screen,			_BORDER_STYLE_FIXED);


		//////////
		// Position and size each window
		//////
			lnWidth		= (_jdebi->rcClient.right - _jdebi->rcClient.left) / 8;
			lnHeight	= (_jdebi->rcClient.bottom - _jdebi->rcClient.top) / 8;
			iObj_setSize(_sourceCode,	0,						0,							4 * lnWidth,																4 * lnHeight);
			iObj_setSize(_locals,		_sourceCode->rc.right,	0,							lnWidth * 3 / 2,															3 * lnHeight / 2);
			iObj_setSize(_watch,		_locals->rc.right,		0,							(_jdebi->rcClient.right - _jdebi->rcClient.left) - _locals->rc.right,		3 * lnHeight / 2);
			iObj_setSize(_cmd,			0,						_sourceCode->rc.bottom,		4 * lnWidth,																(_jdebi->rcClient.bottom - _jdebi->rcClient.top) - _sourceCode->rc.bottom);
			iObj_setSize(_sourceLight,	_sourceCode->rc.right,	_watch->rc.bottom,			(_jdebi->rcClient.right - _jdebi->rcClient.left) - _sourceCode->rc.right,	3 * lnHeight);
			iObj_setSize(_screen,		_sourceCode->rc.right,	_sourceLight->rc.bottom,	(_jdebi->rcClient.right - _jdebi->rcClient.left) - _sourceCode->rc.right,	(_jdebi->rcClient.bottom - _jdebi->rcClient.top) - _sourceLight->rc.bottom);


		//////////
		// Add controls to the subforms
		//////
			_sourceCode_carousel	= iObj_addChild(_OBJ_TYPE_CAROUSEL,		_sourceCode);
			_sourceCode_rider		= iObj_addChild(_OBJ_TYPE_RIDER,		_sourceCode_carousel);
			_sourceCode_editbox		= iObj_addChild(_OBJ_TYPE_EDITBOX,		_sourceCode_rider);
			_locals_editbox			= iObj_addChild(_OBJ_TYPE_EDITBOX,		_locals);
//			_locals_checkbox		= iObj_addChild(_OBJ_TYPE_CHECKBOX,		_locals);
			_watch_editbox			= iObj_addChild(_OBJ_TYPE_EDITBOX,		_watch);
			_command_editbox		= iObj_addChild(_OBJ_TYPE_EDITBOX,		_cmd);
			_debug_editbox			= iObj_addChild(_OBJ_TYPE_EDITBOX,		_debug);
			_output_editbox			= iObj_addChild(_OBJ_TYPE_EDITBOX,		_output);
			_screen_editbox			= iObj_addChild(_OBJ_TYPE_EDITBOX,		_screen);
			_sourceLight_empty		= iObj_addChild(_OBJ_TYPE_EMPTY,		_sourceLight);


		//////////
		// Add the controls to the subforms, carousel, and rider
		//////
			propSetVisible(_sourceCode_carousel,	_LOGICAL_TRUE);
			propSetVisible(_sourceCode_rider,		_LOGICAL_TRUE);
			propSetVisible(_sourceCode_editbox,		_LOGICAL_TRUE);
			propSetVisible(_locals_editbox,			_LOGICAL_TRUE);
			propSetVisible(_watch_editbox,			_LOGICAL_TRUE);
			propSetVisible(_command_editbox,		_LOGICAL_TRUE);
			propSetVisible(_debug_editbox,			_LOGICAL_TRUE);
			propSetVisible(_output_editbox,			_LOGICAL_TRUE);
			propSetVisible(_screen_editbox,			_LOGICAL_TRUE);
			propSetVisible(_sourceLight_empty,		_LOGICAL_TRUE);


		//////////
		// Position and size each control
		//////
			lnHeight = (_jdebi->rcClient.bottom - _jdebi->rcClient.top) / 8;
			iObj_setSize(_sourceCode_carousel,		50,	-1,		_sourceCode->rcClient.right				- _sourceCode->rcClient.left - 49,		_sourceCode->rcClient.bottom			- _sourceCode->rcClient.top - 2);
			iObj_setSize(_sourceCode_rider,			0,	0,		_sourceCode_carousel->rcClient.right	- _sourceCode_carousel->rcClient.left,	_sourceCode_carousel->rcClient.bottom	- _sourceCode_carousel->rcClient.top);
			iObj_setSize(_sourceCode_editbox,		0,	0,		_sourceCode_rider->rcClient.right		- _sourceCode_rider->rcClient.left,		_sourceCode_rider->rcClient.bottom		- _sourceCode_rider->rcClient.top);
			iEngine_raise_event(_EVENT_RESIZE, NULL, _sourceCode_carousel, &_sourceCode_carousel->rc);
			iObj_setSize(_locals_editbox,			8,	0,		_locals->rcClient.right					- _locals->rcClient.left - 8,			_locals->rcClient.bottom				- _locals->rcClient.top);
			iObj_setSize(_watch_editbox,			8,	0,		_watch->rcClient.right					- _watch->rcClient.left - 8,			_watch->rcClient.bottom					- _watch->rcClient.top);
			iObj_setSize(_command_editbox,			8,	0,		_cmd->rcClient.right					- _cmd->rcClient.left - 8,				_cmd->rcClient.bottom					- _cmd->rcClient.top);
			iObj_setSize(_debug_editbox,			8,	0,		_debug->rcClient.right					- _debug->rcClient.left - 8,			_debug->rcClient.bottom					- _debug->rcClient.top);
			iObj_setSize(_output_editbox,			8,	0,		_output->rcClient.right					- _output->rcClient.left - 8,			_output->rcClient.bottom				- _output->rcClient.top);
			iObj_setSize(_screen_editbox,			8,	0,		_screen->rcClient.right					- _screen->rcClient.left - 8,			_screen->rcClient.bottom				- _screen->rcClient.top);
			iObj_setSize(_sourceLight_empty,		0,	0,		_sourceLight->rcClient.right			- _sourceLight->rcClient.left,			_sourceLight->rcClient.bottom			- _sourceLight->rcClient.top);


		//////////
		// Give it a caption
		//////
			propSetCaption(_jdebi, cgcJDebiTitle);


		//////////
		// SourceCode window caption and font
		//////
			propSetBackStyle(_sourceCode, _BACK_STYLE_TRANSPARENT);
			propSetCaption(_sourceCode, cgcSourceCodeTitle);

			// Adjust the caption width
			((SObject*)_sourceCode->firstChild->ll.next)->rc.right = 110;

			_sourceCode_editbox->p.font					= iFont_create(cgcFontName_defaultFixed, 10, FW_MEDIUM, false, false);
			iEngine_set_event(_EVENT_ONKEYDOWN, NULL, _sourceCode_editbox, (uptr)&iSEM_onKeyDown_sourceCode);
			propSetBorderStyle(_sourceCode_editbox, _BORDER_STYLE_FIXED);
			propSetBorderColor(_sourceCode_editbox, lineNumberBackColor);
			_sourceCode_editbox->p.sem->showCursorLine	= true;
			_sourceCode_editbox->p.sem->isSourceCode	= true;
			_sourceCode_editbox->p.sem->showLineNumbers	= true;

			// Decorate with toolbars
			iVjr_init_jdebi_addToolbars();


		//////////
		// Locals window caption and font
		//////
			obj = iiObj_findChildObject_byType(_locals, _OBJ_TYPE_LABEL);
			propSetAutoSize(obj, _LOGICAL_TRUE);
			iObjProp_set_character_direct(_locals, _INDEX_CAPTION, cgcLocalsTitle, sizeof(cgcLocalsTitle) - 1);
			_locals_editbox->p.font					= iFont_create(cgcFontName_defaultFixed, 10, FW_MEDIUM, false, false);
			iEngine_set_event(_EVENT_ONKEYDOWN, NULL, _locals_editbox, (uptr)&iSEM_onKeyDown);
			_locals_editbox->p.sem->showCursorLine	= true;
			_locals_editbox->p.sem->isSourceCode	= true;
			_locals_editbox->p.sem->showLineNumbers	= true;
			iSEM_appendLine(_locals_editbox->p.sem, NULL, 0, false);

			// Position checkbox
// 			iObj_setSize(_locals_checkbox, 100, -21, 85, 18);
// 			obj = iiObj_findChildObject_byType(_locals_checkbox, _OBJ_TYPE_LABEL);
// 			propSetCaption(obj, cgcLocals_includeGlobals);
// 			propSetVisible(_locals_checkbox, _LOGICAL_TRUE);


		//////////
		// Watch window caption and font
		//////
			iObjProp_set_character_direct(_watch, _INDEX_CAPTION, cgcWatchTitle, sizeof(cgcWatchTitle) - 1);
			_watch_editbox->p.font					= iFont_create(cgcFontName_defaultFixed, 10, FW_MEDIUM, false, false);
			iEngine_set_event(_EVENT_ONKEYDOWN, NULL, _watch_editbox, (uptr)&iSEM_onKeyDown);
			_watch_editbox->p.sem->showCursorLine	= true;
			_watch_editbox->p.sem->isSourceCode		= true;
			_watch_editbox->p.sem->showLineNumbers	= true;
			iSEM_appendLine(_watch_editbox->p.sem, NULL, 0, false);


		//////////
		// Command window caption and font
		//////
			iObjProp_set_character_direct(_cmd, _INDEX_CAPTION, cgcCommandTitle, sizeof(cgcCommandTitle) - 1);
			_command_editbox->p.font					= iFont_create(cgcFontName_defaultFixed, 10, FW_MEDIUM, false, false);
			iEngine_set_event(_EVENT_ONKEYDOWN, NULL, _command_editbox, (uptr)&iSEM_onKeyDown_sourceCode);
			_command_editbox->p.hasFocus				= true;
			_command_editbox->p.sem->showCursorLine		= true;
			_command_editbox->p.sem->isSourceCode		= true;
			_command_editbox->p.sem->showLineNumbers	= true;


		//////////
		// Debug window caption and font
		//////
			iObjProp_set_character_direct(_debug, _INDEX_CAPTION, cgcDebugTitle, sizeof(cgcDebugTitle) - 1);
			_debug_editbox->p.font					= iFont_create(cgcFontName_defaultFixed, 10, FW_MEDIUM, false, false);
			iEngine_set_event(_EVENT_ONKEYDOWN, NULL, _debug_editbox, (uptr)&iSEM_onKeyDown);
			_debug_editbox->p.sem->showCursorLine	= true;


		//////////
		// Output window caption and font
		//////
			iObjProp_set_character_direct(_output, _INDEX_CAPTION, cgcOutputTitle, sizeof(cgcOutputTitle) - 1);
			_output_editbox->p.font					= iFont_create(cgcFontName_defaultFixed, 8, FW_MEDIUM, false, false);
			iEngine_set_event(_EVENT_ONKEYDOWN, NULL, _output_editbox, (uptr)&iSEM_onKeyDown);
			_output_editbox->p.sem->showCursorLine	= true;


		//////////
		// SourceLight a caption and font
		//////
			iObjProp_set_character_direct(_sourceLight, _INDEX_CAPTION, cgcSourceLightTitle, sizeof(cgcSourceLightTitle) - 1);
			_sourceLight->p.font = iFont_create(cgcFontName_defaultFixed, 10, FW_MEDIUM, false, false);
			propSetVisible(_sourceLight, _LOGICAL_TRUE);
			propSetBackStyle(_sourceLight, _BACK_STYLE_OPAQUE);
			iEngine_set_event(_EVENT_ONRENDER, NULL, _sourceLight_empty, (uptr)&iSourceLight_copy);


		//////////
		// _screen a caption and font
		//////
			iObjProp_set_character_direct(_screen, _INDEX_CAPTION, cgcScreenTitle, sizeof(cgcScreenTitle) - 1);
			_screen->p.font = iFont_create(cgcFontName_defaultFixed, 10, FW_MEDIUM, false, false);


		//////////
		// Setup _screen's editbox
		//////
			_screen_editbox->p.font		= iFont_create(cgcFontName_defaultFixed, 10, FW_MEDIUM, false, false);
			iEngine_set_event(_EVENT_ONKEYDOWN, NULL, _screen_editbox, (uptr)&iSEM_onKeyDown);
			screenData					= _screen_editbox->p.sem;
			screenData->showCursorLine	= true;
			screenData->showEndLine		= true;
			propSetVisible(_screen, _LOGICAL_TRUE);


		//////////
		// Set it visible
		//////
			propSetVisible(_jdebi, _LOGICAL_TRUE);
	}




//////////
//
// Temporary:  Called to decorate the jdebi source code window with icons
//
//////
	void iVjr_init_jdebi_addToolbars(void)
	{
		// Make sure our environment is sane
		if (_jdebi && _sourceCode)
		{

			//////////
			// Load the master JDebi toolbars
			//////
				jdebiToolbarsContainer = iToolbar_loadFrom_xml(cgc_JDebiBxml, sizeof(cgc_JDebiBxml), cgcTag_jdebi, cgcTag_source_code);


			//////////
			// Apply whatever toolbars are live and visible as they're currently laid out
			//////
				iToolbar_applyTo_obj(_sourceCode, jdebiToolbarsContainer, cgc_JDebiLayoutBxml, sizeof(cgc_JDebiLayoutBxml), cgcTag_jdebi, cgcTag_source_code);

		}
	}




//////////
//
// Called to create the default datetime variable that are constant references
//
//////
	void iVjr_init_createDefaultDatetimes(void)
	{
		SDateTime dt;


		//////////
		// Jan.01.2000 00:00:00.000
		//////
			_datetime_Jan_01_2000 = iVariable_create(_VAR_TYPE_DATETIME, NULL, true);
			dt.julian	= 2451545;
			dt.seconds	= 0.0f;
			iDatum_duplicate(&_datetime_Jan_01_2000->value, (u8*)&dt, 8);
	}




//////////
//
// Called to build the splash screen for startup display.  This contains this format:
//
// These items to the left look like wings or road-signs, each independent.
//						 ____________________ _____________________
// 	[o New feature #1]	|                    |                     |
// 	[o New feature #2]	|   vjr_splash.bmp   |                     |
// 	[o New feature #3]	|                    |                     |
// 	[o New feature #4]	|                    |	[Loading item 1]   |
// 						|                    |	[Loading item 2]   |
// 						|                    |	[Loading item 3]   |
// 						|                    |	[Loading item N]   |
// 						|____________________|_____________________|
// The items to the right are in a traditional subform with an editbox contained within, and look like a text file.
//
//////
	SBitmap* iiVjr_buildSplashScreen(SBitmap* bmpSplash)
	{
		u32			lnX, lnY;
		SBitmap*	bmp;
		RECT		lrc, lrc2;


		// Create our target bitmap
		bmp = iBmp_allocate();
		iBmp_createBySize(bmp, bmpSplash->bi.biWidth * 3, bmpSplash->bi.biHeight, 24);

		// Fill it with the mask color
		SetRect(&lrc, 0, 0, bmp->bi.biWidth, bmp->bi.biHeight);
		iBmp_fillRect(bmp, &lrc, maskColor, maskColor, maskColor, maskColor, false, NULL, false);

		// Overlay the actual splash image
		SetRect(&lrc2, bmpSplash->bi.biWidth, 0, bmpSplash->bi.biWidth * 2, bmpSplash->bi.biHeight);
		iBmp_bitBlt(bmp, &lrc2, bmpSplash);

		// Build the right side loader item list
		SetRect(&lrc2, 2 * bmpSplash->bi.biWidth, 0, bmp->bi.biWidth, bmpSplash->bi.biHeight);
		iVjr_createOverlayListing(bmp, &lrc2);
		iVjr_renderOverlayListing(bmp, &lrc2);

		// Overlay the accomplishments
		SetRect(&lrc2, 0, 0, bmpSplash->bi.biWidth, bmpSplash->bi.biHeight);
		iVjr_renderAccomplishments(bmp, &lrc2);

		// Append the current version text
		if (iBmp_locateMarker(bmp, 240, 24, 240, &lnX, &lnY, true))
		{
			// Append the version string
			SelectObject(bmp->hdc, gsFontDefaultItalic8->hfont);
			SetTextColor(bmp->hdc, RGB(0,0,0));
			SetBkMode(bmp->hdc, TRANSPARENT);
			SetRect(&lrc, lnX, lnY, (2 * bmpSplash->bi.biWidth) - (lnX - bmpSplash->bi.biWidth), lnY + gsFontDefaultItalic8->tm.tmHeight);
			DrawText(bmp->hdc, (s8*)cgcVersionShort, sizeof(cgcVersionShort) - 1, &lrc, DT_SINGLELINE | DT_LEFT | DT_CENTER);
		}

		// Return our bitmap
		return(bmp);
	}




//////////
//
// Append to the system log
//
//////
	void iVjr_appendSystemLog(u8* tcLogText)
	{
		u8 buffer[2048];


		// Lock it down
		EnterCriticalSection(&cs_logData);

		// Append to it
		sprintf((s8*)buffer, (s8*)"[%u] %s\0", (u32)((s64)GetTickCount() - systemStartedTickCount), (s8*)tcLogText);
		iSEM_appendLine(systemLog, buffer, -1, false);

		// Release it
		LeaveCriticalSection(&cs_logData);

#ifndef _VJR_LOG_ALL
		// Render it
		if (!glShuttingDown)
			iVjr_renderOverlayListing(gSplash.bmp, &gobj_splashListing->rc);
#endif
	}




//////////
//
// Called to flush the system log to disk
//
//////
	void iVjr_flushSystemLog()
	{
		iSEM_saveToDisk(systemLog, cgcSystemLogFilename);
	}




//////////
//
// Called to release all of the allocated memory
//
//////
	void iVjr_releaseMemory(void)
	{
		iBmp_delete(&bmpArrowUl,					true, true);
		iBmp_delete(&bmpArrowUr,					true, true);
		iBmp_delete(&bmpArrowLl,					true, true);
		iBmp_delete(&bmpArrowLr,					true, true);

		// Load our icons and images
		iBmp_delete(&bmpVjrIcon,					true, true);
		iBmp_delete(&bmpJDebiIcon,					true, true);
		iBmp_delete(&bmpSourceCodeIcon,				true, true);
		iBmp_delete(&bmpLocalsIcon,					true, true);
		iBmp_delete(&bmpWatchIcon,					true, true);
		iBmp_delete(&bmpCommandIcon,				true, true);
		iBmp_delete(&bmpDebugIcon,					true, true);
		iBmp_delete(&bmpOutputIcon,					true, true);
		iBmp_delete(&bmpSourceLightIcon,			true, true);
		iBmp_delete(&bmpCarouselCarouselIcon,		true, true);
		iBmp_delete(&bmpCarouselTabsIcon,			true, true);
		iBmp_delete(&bmpCarouselPad,				true, true);
		iBmp_delete(&bmpCarouselIcon,				true, true);
		iBmp_delete(&bmpCarouselRiderTabClose,		true, true);
		iBmp_delete(&bmpNoImage,					true, true);
		iBmp_delete(&bmpClose,						true, true);
		iBmp_delete(&bmpMaximize,					true, true);
		iBmp_delete(&bmpMinimize,					true, true);
		iBmp_delete(&bmpMove,						true, true);
		iBmp_delete(&bmpCheckboxOn,					true, true);
		iBmp_delete(&bmpCheckboxOff,				true, true);
		iBmp_delete(&bmpButton,						true, true);
		iBmp_delete(&bmpTextbox,					true, true);
		iBmp_delete(&bmpStoplightRed,				true, true);
		iBmp_delete(&bmpStoplightAmber,				true, true);
		iBmp_delete(&bmpStoplightGreen,				true, true);
		iBmp_delete(&bmpStoplightBlue,				true, true);
		iBmp_delete(&bmpBreakpointAlways,			true, true);
		iBmp_delete(&bmpBreakpointAlwaysCountdown,	true, true);
		iBmp_delete(&bmpConditionalTrue,			true, true);
		iBmp_delete(&bmpConditionalFalse,			true, true);
		iBmp_delete(&bmpConditionalTrueCountdown,	true, true);
		iBmp_delete(&bmpConditionalFalseCountdown,	true, true);
		iBmp_delete(&bmpDapple1,					true, true);
		iBmp_delete(&bmpDapple2,					true, true);

		// Casks
		iVjr_releaseCaskIcons();

		// The radio image has a 44x44 dot in the upper-left.
		iBmp_delete(&bmpRadio,						true, true);
		iBmp_delete(&bmpRadioDot,					true, true);

		// Splash screen
		iBmp_delete(&bmpVjrSplash,					true, true);

		// Focus window accumulator
		iBuilder_freeAndRelease(&gFocusHighlights);

		// Default reference datetimes
		iVjr_releaseAllDefaultDatetimes();

		// Default objects
		iVjr_releaseAllDefaultObjects();

		// Main screen window
		iVjr_release_jdebi();

		// Global variables
		iVariable_delete(varGlobals,		true);
		iVariable_delete(cvarSpace1,		true);
		iVariable_delete(cvarEmptyString,	true);
		iVariable_delete(cvarSpace2000,		true);
		iVariable_delete(cvarTrue,			true);
		iVariable_delete(cvarFalse,			true);

		// Delete the splash objects and images
		iObj_delete(&gobj_splashListing,	true, true, true);
		iBmp_delete(&gSplash.bmp,			true, false);

		// Release our builders
		iWindow_releaseAll(&gWindows,		true);
		iFont_releaseAll(gFonts,			true);
	}




//////////
//
// Called to handle some shutdown cleanups
//
//////
	void iVjr_releaseAllDefaultDatetimes(void)
	{
		iVariable_delete(_datetime_Jan_01_2000, true);
	}

	void iVjr_releaseAllDefaultObjects(void)
	{
		iObj_delete(&gobj_defaultEmpty,		true, true, true);
		iObj_delete(&gobj_defaultLabel,		true, true, true);
		iObj_delete(&gobj_defaultTextbox,		true, true, true);
		iObj_delete(&gobj_defaultButton,		true, true, true);
		iObj_delete(&gobj_defaultImage,		true, true, true);
		iObj_delete(&gobj_defaultCheckbox,	true, true, true);
		iObj_delete(&gobj_defaultOption,		true, true, true);
		iObj_delete(&gobj_defaultRadio,		true, true, true);
		iObj_delete(&gobj_defaultForm,		true, true, true);
		iObj_delete(&gobj_defaultSubform,		true, true, true);
	}

	void iVjr_release_jdebi(void)
	{
		iObj_delete(&_jdebi, true, true, true);
	}

	void iVjr_releaseCaskIcons(void)
	{
		iBmp_delete(&bmpCaskIconsTiled,				true, true);
		iBmp_delete(&bmpCaskRoundLeft,				true, true);
		iBmp_delete(&bmpCaskRoundRight,				true, true);
		iBmp_delete(&bmpCaskSquareLeft,				true, true);
		iBmp_delete(&bmpCaskSquareRight,			true, true);
		iBmp_delete(&bmpCaskTriangleLeft,			true, true);
		iBmp_delete(&bmpCaskTriangleRight,			true, true);
		iBmp_delete(&bmpCaskTildeLeft,				true, true);
		iBmp_delete(&bmpCaskTildeRight,				true, true);
		iBmp_delete(&bmpCaskPips1,					true, true);
		iBmp_delete(&bmpCaskPips2,					true, true);
		iBmp_delete(&bmpCaskPips3,					true, true);
		iBmp_delete(&bmpCaskSideExtender,			true, true);
		iBmp_delete(&bmpCaskSideExtenderLeft,		true, true);
		iBmp_delete(&bmpCaskSideExtenderMiddle,		true, true);
		iBmp_delete(&bmpCaskSideExtenderRight,		true, true);
		iBmp_delete(&bmpCaskExtenderMiddle,			true, true);
		iBmp_delete(&bmpCaskExtenderLeft1,			true, true);
		iBmp_delete(&bmpCaskExtenderLeft2,			true, true);
		iBmp_delete(&bmpCaskExtenderRight2,			true, true);
		iBmp_delete(&bmpCaskExtenderRight1,			true, true);
	}




//////////
//
// Called as a central location to shutdown the system politely.
//
//////
	void iVjr_shutdown()
	{
// 		bool	error;
// 		u32		errorNum;


		// Indicate we're shutting down
		glShuttingDown = true;

#if !defined(_NONVJR_COMPILE)
		// System is shutting down
		iVjr_appendSystemLog((u8*)"Unengage VJr");

		// Tell OS to unengage our process
		iVjr_appendSystemLog((u8*)"Notify OS to shutdown");

		// Flush the log
		iVjr_flushSystemLog();

		// Save where we are
		iSEM_saveToDisk(screenData,				cgcScreenDataFilename);
		iSEM_saveToDisk(_command_editbox->p.sem,	cgcCommandHistoryFilename);

		// Save the system layout
// Temporarily disabled
//		iObj_saveLayoutAs_bxml(_jdebi, cgcScreenLayoutFilename, true, true, true, &error, &errorNum);
#endif

		// Close the allocated memory blocks
		iVjr_releaseMemory();

		// Signal quit message
		PostQuitMessage(0);
	}




//////////
//
// Called to display a splash screen.
// Note:  The incoming parameter must be a COPY of the original if
//        the original is to persist after display.
//
//////
	DWORD WINAPI iSplash_show(LPVOID/*SBitmap**/ lpParameter)
	{
		SThisCode*		thisCode = NULL;
		s32				lnLeft, lnTop;
		WNDCLASSEXA		classex;
		RECT			lrcWindow, lrcClient;
		HRGN			lrgn;
		MSG				msg;


		// Delete any existing splash screens
		iSplash_delete((LPVOID)0);

		// Store the bitmap
		gSplash.bmp = (SBitmap*)lpParameter;

		// Make sure the class is registered
		if (!GetClassInfoExA(ghInstance, (cs8*)cgcSplashClass, &classex))
		{
			// Initialize
			memset(&classex, 0, sizeof(classex));

			// Populate
			classex.cbSize				= sizeof(WNDCLASSEXA);
			classex.hInstance			= ghInstance;
			classex.style				= CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
			classex.lpszClassName		= (cs8*)cgcSplashClass;
			classex.hCursor				= LoadCursor(null0, IDC_ARROW);
			classex.lpfnWndProc			= &iSplash_wndProc;

			// Register
			RegisterClassExA(&classex);
		}

		// Create the window
		GetWindowRect(GetDesktopWindow(), &lrcWindow);
		lnLeft	= ((lrcWindow.right  - lrcWindow.left) / 2) - (gSplash.bmp->bi.biWidth  / 2);
		lnTop	= ((lrcWindow.bottom - lrcWindow.top)  / 2) - (gSplash.bmp->bi.biHeight / 2);
		gSplash.hwnd = CreateWindowEx(WS_EX_TOPMOST, (cs8*)cgcSplashClass, NULL, WS_POPUP,
											lnLeft,
											lnTop,
											gSplash.bmp->bi.biWidth,
											gSplash.bmp->bi.biHeight,
											null0, null0, GetModuleHandle(NULL), 0);

		// Process any region info
		GetClientRect(gSplash.hwnd, &lrcClient);
		lrgn = iBmp_extractRgnByMask(gSplash.bmp, &lrcClient);
		SetWindowRgn(gSplash.hwnd, lrgn, false);

		// Create a timer to send events to the window every 1/4 second
		SetTimer(gSplash.hwnd, (uptr)&gSplash, 250, 0);

		// Position above all windows
		SetWindowPos(gSplash.hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW | SWP_NOACTIVATE);

		// Read until the splash window goes bye bye
		gSplash.isEnabled = true;
		gSplash.isVisible = true;
		while (glIsMouseOverSplash || gSplash.isEnabled)
		{
			//////////
			// Read and process a message
			//////
				if (GetMessage(&msg, gSplash.hwnd, 0, 0))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);

				} else {
					Sleep(0);
				}
		}
		// Log it
		iVjr_appendSystemLog((u8*)"Splash screen unengaged");

		// Delete the timer
		KillTimer(gSplash.hwnd, 0);

		// Delete the bitmap
		iBmp_delete(&gSplash.bmp, true, true);

		// Delete the region
		DeleteObject((HGDIOBJ)lrgn);

		// Destroy the window
		DestroyWindow(gSplash.hwnd);
		gSplash.hwnd		= 0;
		gSplash.isVisible	= false;

		// All done
		return(0);
	}




//////////
//
// Called to delete the splash screen (if any)
//
//////
	DWORD WINAPI iSplash_delete(LPVOID lpParameter)
	{
		// Close any prior splash screen
		if (gSplash.isEnabled)
		{
			// Sleep for the indicated time
			Sleep((DWORD)(uptr)lpParameter);

			// Log it
			iVjr_appendSystemLog((u8*)"Splash screen can unengage");

			// Indicate no longer valid
			gSplash.isEnabled = false;
		}

		// All done
		return(0);
	}




//////////
//
// Callback to handle the splash screen thingys :-)
//
//////
	LRESULT CALLBACK iSplash_wndProc(HWND hwnd, UINT m, WPARAM w, LPARAM l)
	{
		HDC			lhdc;
		PAINTSTRUCT	ps;
		HRGN		lrgn;
		RECT		lrc;
		POINT		pt;


		if (m == WM_TIMER)
		{
			GetCursorPos(&pt);
			GetWindowRect(hwnd, &lrc);
			lrgn = CreateRectRgn(lrc.left, lrc.top, lrc.right, lrc.bottom);
			GetWindowRgn(hwnd, lrgn);
			glIsMouseOverSplash = ((PtInRegion(lrgn, pt.x - lrc.left, pt.y - lrc.top)) ? true : false);
		}

		// The only message we handle is the paint
		if (gSplash.bmp)
		{
			switch (m)
			{
				case WM_PAINT:
					// Start painting
					lhdc = BeginPaint(hwnd, &ps);

					// Paint it
					BitBlt(lhdc, 0, 0, gSplash.bmp->bi.biWidth, gSplash.bmp->bi.biHeight, gSplash.bmp->hdc, 0, 0, SRCCOPY);

					// All done
					EndPaint(hwnd, &ps);
					return(0);
			}
		}

		// Default handler
		return(DefWindowProc(hwnd, m, w, l));
	}




//////////
//
// Called to play the startup aria while the splash screen is viable.
//
//////
	DWORD WINAPI iPlay_ariaSplash(LPVOID lpParameter)
	{
		SThisCode*	thisCode = NULL;
		u32			stopTickCount;
		f32			lfVolume;
		u64			lnSoundHandle;
		u8			buffer[256];


		// Load the sound file (if it exists)
		if (iFile_readContents((s8*)lpParameter, NULL, &soundData_s8, &soundCount))
		{
			// Log it
			sprintf((s8*)buffer, "Engage %s\0", (s8*)lpParameter);
			iVjr_appendSystemLog(buffer);

			// Begin at the beginning
			soundOffset = 0;
			soundCount	/= 4;	// Each sound item is an f32

			// Attempt to create the sound stream
			lnSoundHandle	= iSound_createStream(44100, (u64)&iPlay_ariaSplash_callback);
			lfVolume		= 1.0f;//0.25f;
			iSound_playStart(lnSoundHandle, lfVolume);

			// Repeat until the splash screen is over, or the song ends
			stopTickCount = GetTickCount() + 2500;
			while (glIsMouseOverSplash || (gSplash.isEnabled && soundOffset < soundCount) || GetTickCount() < stopTickCount)
			{
				// Continue looping so long as the mouse is over
				if (glIsMouseOverSplash && soundOffset >= soundCount)
					soundOffset = 0;

				// Wait 1/10th second
				Sleep(100);
			}

			// If we haven't finished, continue until the volume turns down after one second
			while (lfVolume > 0.0f)
			{
				// Turn down the volume 1/10th
				lfVolume -= 0.025f;
				iSound_setVolume(lnSoundHandle, lfVolume);

				// Wait 1/10th second
				Sleep(100);
			}
			// Log it
			sprintf((s8*)buffer, "Unengage %s\0", (s8*)lpParameter);
			iVjr_appendSystemLog(buffer);

			// When we get here, we're done playing
			iSound_playCancel(lnSoundHandle);

			// Raise the termination flag until we can shut down the playback
			soundOffset = soundCount;

			// Free the sound buffer
			free(soundData_s8);
			soundData_s8 = NULL;

			// Clear the handle
			iSound_deleteHandle(lnSoundHandle);

		} else {
			// Log it
			sprintf((s8*)buffer, "Inquiry on sound file %s\0", (s8*)lpParameter);
			iVjr_appendSystemLog(buffer);
		}

		// Completed
		return(0);
	}

	void WINAPI iPlay_ariaSplash_callback(f32* sampleBuffer, u32 tnSamples, bool* tlContinueAfterThisSampleSet)
	{
		u32 lnI;


		// Make sure we have something to do
		for (lnI = 0; lnI < tnSamples && soundData_f32 && soundOffset < soundCount; lnI++, soundOffset++)
			sampleBuffer[lnI] = soundData_f32[soundOffset];

		// Pad with 0.0s
		for ( ; lnI < tnSamples; lnI++)
			sampleBuffer[lnI] = 0.0f;

		// Indicate if the sound should continue after this
		*tlContinueAfterThisSampleSet = (glIsMouseOverSplash || (soundOffset < soundCount));
	}




//////////
//
// Processes messages from the interface window, to forward on to the original window
//
//////
	LRESULT CALLBACK iWindow_wndProcForms(HWND h, UINT m, WPARAM w, LPARAM l)
	{
		SWindow*		win;
		POINT			lpt;
		HDC				lhdc;
		PAINTSTRUCT		ps;


		// See if we know this hwnd
		win = iWindow_findByHwnd(h);
		if (win)
		{
			// It was one of our windows
			switch (m)
			{
				case WMVJR_FIRST_CREATION:
					// Currently unused
					break;

				case WM_TIMER:
					if (win->isMoving || win->isResizing)
					{
						// Grab the mouse coordinates
						GetCursorPos(&lpt);
						win->mouseCurrent.positionInOsDesktop.x = lpt.x;
						win->mouseCurrent.positionInOsDesktop.y = lpt.y;

						// Reposition or resize
						iiMouse_processMouseEvents_windowSpecial(win);
					}
					break;

				case WM_DESTROY:
					// Currently unused
					break;

				case WM_KILLFOCUS:
				case WM_WINDOWPOSCHANGING:
					iFocusHighlight_deleteAll();
					break;

				case WM_SETFOCUS:
				case WM_WINDOWPOSCHANGED:
					iWindow_render(win, true);
					break;

				case WM_LBUTTONDOWN:
				case WM_LBUTTONUP:
				case WM_RBUTTONDOWN:
				case WM_RBUTTONUP:
				case WM_MBUTTONDOWN:
				case WM_MBUTTONUP:
				case WM_RBUTTONDBLCLK:
				case WM_LBUTTONDBLCLK:
				case WM_MBUTTONDBLCLK:
#ifdef WM_MOUSEHWHEEL
				case WM_MOUSEHWHEEL:
#endif
				case WM_MOUSEWHEEL:
				case WM_MOUSEMOVE:
				case WM_MOUSEHOVER:
					if (!win->isMoving && !win->isResizing)
						return((LRESULT)(sptr)iMouse_processMessage(win, m, w, l));
					break;

				case WM_SYSKEYDOWN:
				case WM_SYSKEYUP:
					if (w == VK_F10)		return((LRESULT)(sptr)iKeyboard_processMessage(win, ((WM_SYSKEYDOWN) ? WM_KEYDOWN : WM_KEYUP), w, l));
					else					return((LRESULT)(sptr)iKeyboard_processMessage(win, m, w, l));		// Send it as is
					break;

				case WM_KEYDOWN:
				case WM_KEYUP:
					return((LRESULT)(sptr)iKeyboard_processMessage(win, m, w, l));

				case WM_CAPTURECHANGED:
					if (win->isMoving)
					{
						// Stop the movement
//						iStopMove();

					} else if (win->isResizing) {
						// Stop the resize
//						iStopResize();

					} else {
						// Make sure our flags are lowered
						win->isMoving	= false;
						win->isResizing	= false;
					}
					break;

				case WM_PAINT:
					// Paint it
					lhdc = BeginPaint(h, &ps);
					BitBlt(lhdc, 0, 0, win->obj->bmp->bi.biWidth, win->obj->bmp->bi.biHeight, win->obj->bmp->hdc, 0, 0, SRCCOPY);
					EndPaint(h, &ps);
					return 0;
			}
		}

		// Call Windows' default procedure handler
		return(DefWindowProc(h, m, w, l));
	}




//////////
//
// Called to create the Windows-facing window for the indicated object.
// Note:  Any object can be presented in a window, though typically on form objects are.
//
//////
	SWindow* iWindow_createForObject(SObject* obj, SWindow* winReuse, s32 icon)
	{
		s32				lnWidth, lnHeight;
		SWindow*		winNew;
		WNDCLASSEXA		classex;
		SVariable*		var;
		s8				buffer[128];
		s8				bufferClass[256];


		// Make sure our environment is sane
		winNew = NULL;
		if (obj)
		{
			//////////
			// Create if need be
			//////
				if (!winReuse)		winNew = iWindow_allocate();
				else				winNew = winReuse;


			//////////
			// If we have a window, prepare it
			//////
				if (winNew)
				{
					//////////
					// Lock down
					//////
						EnterCriticalSection(&winNew->cs);


					//////////
					// Initialize
					//////
						memset(buffer, 0, sizeof(buffer));


					//////////
					// Populate
					//////
						lnWidth		= obj->rc.right - obj->rc.left;
						lnHeight	= obj->rc.bottom - obj->rc.top;
						CopyRect(&winNew->rc, &obj->rc);
						winNew->obj = obj;


					//////////
					// Create our accumulation buffer
					//////
						winNew->bmp = iBmp_allocate();
						iBmp_createBySize(winNew->bmp, lnWidth, lnHeight, 24);


					//////////
					// Register the general window class if need be
					//////
#ifdef IDI_VJR
						icon = ((icon <= 0) ? IDI_VJR : icon);
#endif
						sprintf(bufferClass, "%s%u\0", (s8*)cgcWindowClass, icon);
						if (!GetClassInfoExA(ghInstance, bufferClass, &classex))
						{
							// Initialize
							memset(&classex, 0, sizeof(classex));

							// Populate
							classex.cbSize				= sizeof(WNDCLASSEXA);
							classex.hInstance			= ghInstance;
							classex.style				= CS_OWNDC | CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
							classex.lpszClassName		= bufferClass;
#ifdef IDI_VJR
							classex.hIcon				= LoadIcon(ghInstance, MAKEINTRESOURCE(icon));
#endif
							classex.hCursor				= LoadCursor(null0, IDC_ARROW);
							classex.lpfnWndProc			= &iWindow_wndProcForms;

							// Register
							RegisterClassExA(&classex);
						}


					//////////
					// Physically create the window
					//////
						// Window name
						var = iObjProp_get_var_byIndex(obj, _INDEX_NAME);
						if (var->varType != _VAR_TYPE_CHARACTER)
						{
							// Use a default name
							memcpy(buffer, cgcName_form, sizeof(cgcName_form));

						} else {
							// Use the indicated name
							memcpy(buffer, var->value.data,	min(var->value.length, (s32)sizeof(buffer) - 1));
						}

						// Build it
						winNew->hwnd = CreateWindow(bufferClass, buffer, WS_POPUP,
														winNew->rc.left,
														winNew->rc.top,
														winNew->rc.right - winNew->rc.left,
														winNew->rc.bottom - winNew->rc.top,
														null0, null0, ghInstance, 0);

						// Set the coordinates for the form within the window
						SetRect(&obj->rc, 0, 0, lnWidth, lnHeight);

						// Initialize it internally
						PostMessage(winNew->hwnd, WMVJR_FIRST_CREATION, 0, 0);

						// If visible, show it
						if (propIsVisible(obj))
							ShowWindow(winNew->hwnd, SW_SHOW);


					//////////
					// Unlock
					//////
						LeaveCriticalSection(&winNew->cs);
				}
		}

		// Indicate our status
		return(winNew);
	}




//////////
//
// Called to delete all of the windows
//
//////
	void iWindow_releaseAll(SBuilder** windowRoot, bool tlDeleteSelf)
	{
		u32			lnI;
		SBuilder*	windows;
		SWindow*	win;


		// Make sure our environment is sane
		if (windowRoot && *windowRoot)
		{
			//////////
			// Grab the pointer
			//////
				windows = *windowRoot;


			//////////
			// Iterat to delete all windows
			//////
				for (lnI = 0; lnI < windows->populatedLength; lnI += sizeof(SWindow))
				{
					// Grab this pointer
					win = (SWindow*)(windows->data_u8 + lnI);

					// Lock it down
					EnterCriticalSection(&win->cs);

					// Delete
					if (win->isValid)
						iWindow_delete(win, false);		// Delete the window (marks itself invalid)

					// Unlock it
					LeaveCriticalSection(&win->cs);
				}


			//////////
			// Delete
			//////
				if (tlDeleteSelf)
					iBuilder_freeAndRelease(windowRoot);
		}
	}




//////////
//
// Called to delete the indicated window.
// Note:  When called, the window must be already locked (if required).
//
//////
	void iWindow_delete(SWindow* win, bool tlDeleteSelf)
	{
		// Make sure our environment is sane
		if (win && iWindow_isPointerValid(win))
		{
			// Delete it
			iBmp_delete(&win->bmp, true, true);
			iObj_delete(&win->obj, true, true, true);

			// Delete self
			if (tlDeleteSelf)
			{
				// Release the critical section
				DeleteCriticalSection(&win->cs);
				free(win);

			} else {
				win->isValid = false;
			}
		}
	}




//////////
//
// Called to search the known windows for the indicated window by hwnd
//
//////
	SWindow* iWindow_findByHwnd(HWND hwnd)
	{
		u32			lnI;
		HWND		lnHwnd;
		SWindow*	win;


		// Make sure our environment is sane
		if (gWindows)
		{
			// Iterate through all known windows and see which one is which
			for (lnI = 0; lnI < gWindows->populatedLength; lnI += sizeof(SWindow))
			{
				// Grab this one
				win = (SWindow*)(gWindows->data_u8 + lnI);

				// Lock it down
				EnterCriticalSection(&win->cs);

				// Validate validity
				if (win->isValid)
				{
					// Grab the hwnd
					lnHwnd = win->hwnd;

				} else {
					lnHwnd = null0;
				}

				// Unlock it
				LeaveCriticalSection(&win->cs);

				// Is this our man?
				if (lnHwnd && lnHwnd == hwnd)
				{
					// Indicate our find
					return(win);
				}
			}
		}
		// If we get here, not found
		return(NULL);
	}




//////////
//
// Called to search the known windows for the indicated window by object
//
//////
	SWindow* iWindow_findByObj(SObject* obj)
	{
		u32			lnI;
		SObject*	wobj;
		SWindow*	win;


		// Iterate through all known windows and see which one is which
		for (lnI = 0; lnI < gWindows->populatedLength; lnI += sizeof(SWindow))
		{
			// Grab this one
			win = (SWindow*)(gWindows->data_u8 + lnI);

			// Lock it down
			EnterCriticalSection(&win->cs);

			// Validate validity
			if (win->isValid)
			{
				// Grab the object
				wobj = win->obj;

			} else {
				wobj= NULL;
			}

			// Unlock it
			LeaveCriticalSection(&win->cs);

			// Is this our man?
			if (wobj && wobj == obj)
			{
				// Indicate our find
				return(win);
			}
		}
		// If we get here, not found
		return(NULL);
	}




//////////
//
// Called to search for the window from the object on a 
//
//////
	SWindow* iWindow_findRoot_byObj(SObject* obj)
	{
		return(iWindow_findByObj(iObj_find_rootmostObject(obj)));
	}




//////////
//
// Called to
//
//////
	SWindow* iWindow_allocate(void)
	{
		u32			lnI;
		bool		llFound;
		SWindow*	win;


		// Iterate through existing slots for isValid=false windows
		for (lnI = 0; lnI < gWindows->populatedLength; lnI += sizeof(SWindow))
		{
			// Grab this one
			win = (SWindow*)(gWindows->data_u8 + lnI);

			// Lock it down
			if (TryEnterCriticalSection(&win->cs))
			{
				// Is this one invalid?
				if (!win->isValid)
				{
					// We can use this one
					llFound			= true;
					win->isValid	= true;

				} else {
					// We must continue looking
					llFound			= false;
				}

				// Unlock it
				LeaveCriticalSection(&win->cs);

				// If we found it, use it
				if (llFound)
					return(win);
			}
		}

		// If we get here, it wasn't found
		win = (SWindow*)iBuilder_allocateBytes(gWindows, sizeof(SWindow));
		if (win)
		{
			// Initialize
			memset(win, 0, sizeof(SWindow));

			// Initially populate
			InitializeCriticalSection(&win->cs);
			win->isValid = true;
		}

		// Indicate our status
		return(win);
	}




//////////
//
// Disconnect the object from the window
//
//////
	void iWindow_disconnectObj(SWindow* win, SObject* obj)
	{
		if (win && win->obj && iWindow_isPointerValid(win))
		{
			// Lock it down
			EnterCriticalSection(&win->cs);

			// Validate validity
			if (win->isValid)
				win->obj = NULL;	// Remove the object reference

			// Unlock it
			LeaveCriticalSection(&win->cs);
		}
	}




//////////
//
// Called to re-render the indicated window
//
//////
	void iWindow_render(SWindow* win, bool tlForce)
	{
		// Make sure we have something to render
		if (win && win->obj && iWindow_isPointerValid(win))
		{
			// Lock it down
			EnterCriticalSection(&win->cs);

			// Validate validity
			if (win->isValid)
			{
				// Re-render if the screen's not locked
				if (!propGet_settings_LockScreen(_settings))
				{
					// Render anything needing rendering
					iObj_renderChildrenAndSiblings(win->obj, true, true, tlForce);

					// Publish anything needing publishing
					iObj_publish(win->obj, &win->rc, win->bmp, true, true, tlForce, 0);

//////////
// Disabled ... cannot find a good (or should I say "real-time") scaling algorithm for forms bitmaps
//////
#if defined(_GRACE_COMPILE)
					// Update the openGL window
					iGrace_display();
#endif

					// Determine the focus highlights
					iObj_setFocusHighlights(win, win->obj, 0, 0, true, true);

					// And force the redraw
					InvalidateRect(win->hwnd, 0, FALSE);
				}
			}

			// Unlock
			LeaveCriticalSection(&win->cs);
		}
	}




//////////
//
// Called to begin moving the window
//
//////
	void iWindow_move(SWindow* win)
	{
		// Begin the move of this window
	}




//////////
//
// Called to minimize the window
//
//////
	void iWindow_minimize(SWindow* win)
	{
		ShowWindow(win->hwnd, SW_MINIMIZE);
	}




//////////
//
// Called to minimize the window
//
//////
	void iWindow_maximize(SWindow* win)
	{
	}




//////////
//
// Called to validate if the window pointer is valid or not
//
//////
	bool iWindow_isPointerValid(SWindow* win)
	{
		if (gWindows && win && (uptr)win >= gWindows->_data && (uptr)win <= (gWindows->_data + gWindows->populatedLength))
			return(true);	// Valid

		// If we get here, invalid
		return(false);
	}




//////////
//
// Create a new focus highlight window
//
//////
	void iFocusHighlight_create(SFocusHighlight* focus, RECT* rc)
	{
		SThisCode*	thisCode = NULL;
		s32			lnFocusHighlightPixels;
		SBgra		color;
		WNDCLASSEX	wcex;
		ATOM		atom;
		HRGN		lrgn;
		RECT		lrc, lrcp, lrcParent;


		//////////
		// Are they shunning the focus highlight borders?
		//////
			if (!glShowFocusHighlightBorder)
				return;		// Yes


		//////////
		// See if the class is already defined
		//////
			if (!GetClassInfoEx(GetModuleHandle(NULL), (cs8*)cgcFocusHighlightClass, &wcex))
			{
				// We need to create said class with our class making skills
				// If we get here, not yet registered
				memset(&wcex, 0, sizeof(wcex));
				wcex.cbSize         = sizeof(wcex);
				wcex.style          = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
				wcex.lpfnWndProc    = &iFocusHighlight_wndProc;
				wcex.hInstance      = GetModuleHandle(NULL);
				wcex.hCursor		= LoadCursor(null0, IDC_ARROW);
				wcex.lpszClassName  = (cs8*)cgcFocusHighlightClass;
				atom				= RegisterClassExA(&wcex);

				// Was it registered?
				if (!atom)
					return;		// Nope ... when we get here, failure
			}


		//////////
		// Create the window
		//////
			focus->hwnd = CreateWindowEx(WS_EX_TOOLWINDOW, (cs8*)cgcFocusHighlightClass, NULL, WS_POPUP, rc->left, rc->top, rc->right - rc->left, rc->bottom - rc->top, null0, null0, GetModuleHandle(NULL), 0);


		//////////
		// If the window needs repositioned or resized, do so
		//////
			GetWindowRect(focus->win->hwnd, &lrcp);
			CopyRect(&lrcParent, &lrcp);
			AdjustWindowRect(&lrcParent, GetWindowLong(focus->win->hwnd, GWL_STYLE), (GetMenu(focus->win->hwnd) != null0));
			lrcParent.left	= lrcp.left + (lrcp.left - lrcp.left);
			lrcParent.top	= lrcp.top  + (lrcp.top  - lrcp.top);


		//////////
		// Cut out a region for the indicated border pixel width, so the window is transparent except for where it should cut through
		//////
			GetClientRect(focus->hwnd, &lrc);
			focus->hrgn				= CreateRectRgnIndirect(&lrc);
			lnFocusHighlightPixels	= propGet_settings_focusObjPixels(_settings);
			InflateRect(&lrc, -lnFocusHighlightPixels, -lnFocusHighlightPixels);
			lrgn = CreateRectRgnIndirect(&lrc);
			CombineRgn(focus->hrgn, focus->hrgn, lrgn, RGN_XOR);		// Create a region with the inner part masked out
			SetWindowRgn(focus->hwnd, focus->hrgn, TRUE);


		//////////
		// Store the settings
		//////
			if (focus->obj->objType == _OBJ_TYPE_SUBFORM || focus->obj->objType == _OBJ_TYPE_EDITBOX)		color = focusObjColor_readWrite_container;
			else																							color = focusObjColor_readWrite_obj;

			focus->readWriteBrush	= CreateSolidBrush(RGB(color.red,							color.grn,							color.blu));
			focus->readOnlyBrush	= CreateSolidBrush(RGB(focusObjColor_readOnly.red,	focusObjColor_readOnly.grn,	focusObjColor_readOnly.blu));
			GetWindowRect(focus->hwnd, &focus->rc);


		//////////
		// Display the window
		//////
			focus->isValid = true;
			SetWindowPos(focus->hwnd, HWND_TOPMOST, lrcParent.left + rc->left, lrcParent.top + rc->top, rc->right - rc->left, rc->bottom - rc->top, ((gSplash.isVisible) ? SWP_HIDEWINDOW : SWP_SHOWWINDOW) | SWP_NOACTIVATE);
	}




//////////
//
// Called to show the active focus highlight window
//
//////
	void iFocusHighlight_show(SFocusHighlight* focus)
	{
		if (focus)
			ShowWindow(focus->hwnd, ((gSplash.isVisible) ? SW_HIDE : SW_SHOW));
	}




//////////
//
// Delete a previous window
//
//////
	void iFocusHighlight_delete(SFocusHighlight* focus)
	{
		if (focus && focus->isValid)
		{
			// Delete the window
			DestroyWindow(focus->hwnd);

			// Destroy the region
			DeleteObject((HGDIOBJ)focus->hrgn);

			// Release the variables
			memset(focus, 0, sizeof(SFocusHighlight));
		}
	}




//////////
//
// Called to delete all of the focus highlights
//
//////
	void iFocusHighlight_deleteAll(void)
	{
		u32					lnI;
		SFocusHighlight*	focus;


		// Make sure our environment is sane
		if (gFocusHighlights)
		{
			// Iterate through all focus windows
			for (lnI = 0; lnI < gFocusHighlights->populatedLength; lnI += sizeof(SFocusHighlight))
			{
				// Grab the focus
				focus = (SFocusHighlight*)(gFocusHighlights->data_u8 + lnI);

				// Delete it if it exists
				if (focus && focus->isValid)
					iFocusHighlight_delete(focus);
			}
		}
	}




//////////
//
// Called to find a focus highlight window by its hwnd
//
//////
	SFocusHighlight* iFocusHighlight_findByHwnd(HWND hwnd)
	{
		u32					lnI;
		SFocusHighlight*	focus;


		// Iterate through each item
		for (lnI = 0; lnI < gFocusHighlights->populatedLength; lnI += sizeof(SFocusHighlight))
		{
			// Grab the pointer
			focus = (SFocusHighlight*)(gFocusHighlights->data_u8 + lnI);

			// Is this it?
			if (focus->hwnd == hwnd)
				return(focus);
		}

		// If we get here, it wasn't found
		return(NULL);
	}




//////////
//
// Called to find a focus highlight window by its object
//
//////
	SFocusHighlight* iFocusHighlight_findByObj(SObject* obj)
	{
		u32					lnI;
		SFocusHighlight*	focus;


		// Iterate through each item
		for (lnI = 0; lnI < gFocusHighlights->populatedLength; lnI += sizeof(SFocusHighlight))
		{
			// Grab the pointer
			focus = (SFocusHighlight*)(gFocusHighlights->data_u8 + lnI);

			// Is this it?
			if (focus->obj == obj)
				return(focus);
		}

		// If we get here, it wasn't found
		return(NULL);
	}




//////////
//
// Handles the focus highlight borders
//
//////
	LRESULT CALLBACK iFocusHighlight_wndProc(HWND hwnd, UINT m, WPARAM w, LPARAM l)
	{
		SThisCode*			thisCode = NULL;
		SFocusHighlight*	focus;
		HDC					lhdc;
		PAINTSTRUCT			ps;


		// Find the focus window
		focus = iFocusHighlight_findByHwnd(hwnd);

		// Did we find
		if (focus && focus->isValid)
		{
			// The only message we handle is the paint
			if (m == WM_PAINT)
			{
				// Start painting
				lhdc = BeginPaint(hwnd, &ps);

				// Paint it
				if (propIsReadonly(focus->obj))
				{
					// Read-only coloring
					FillRect(lhdc, &ps.rcPaint, focus->readOnlyBrush);

				} else {
					// Read-write coloring
					FillRect(lhdc, &ps.rcPaint, focus->readWriteBrush);
				}

				// All done
				EndPaint(hwnd, &ps);
				return(0);
			}
		}

		// Default handler
		return(DefWindowProc(hwnd, m, w, l));
	}




//////////
//
// Called to allocate a tooltip structure and prepare it for display
//
//////
	STooltip* iTooltip_allocate(RECT* rc, SBitmap* bmp, s32 tnTimeoutMs, bool tlAllowMove, bool tlAllowSticky)
	{
		STooltip* tooltip;


		// Allocate a structure
		tooltip = (STooltip*)malloc(sizeof(STooltip));
		if (tooltip)
		{
			// Initialize
			memset(tooltip, 0, sizeof(STooltip));

			// Populate
			CopyRect(&tooltip->rc, rc);
			tooltip->bmp			= bmp;
			tooltip->timeoutMs		= tnTimeoutMs;
			tooltip->allowMove		= tlAllowMove;
			tooltip->allowSticky	= tlAllowSticky;
		}

		// Indicate our status
		return(tooltip);
	}




//////////
//
// Called to create a new tooltip at the indicated coordinates with the indicated text
//
//////
	void iTooltip_show(STooltip* tooltip)
	{
		CreateThread(NULL, 0, &iTooltip_thread, tooltip, 0, 0);
	}

	DWORD WINAPI iTooltip_thread(LPVOID param/*STooltip*/)
	{
		s32			lnWidth, lnHeight;
		WNDCLASSEX	wcex;
		ATOM		atom;
		MSG			msg;
		STooltip*	tooltip;

		union {
			uptr	_lpParameter;
			LPVOID	lpParameter;
		};


		//////////
		// See if the class is already defined
		//////
			lpParameter = param;
			if (!GetClassInfoEx(GetModuleHandle(NULL), (cs8*)cgcTooltipClass, &wcex))
			{
				// We need to create said class with our class making skills
				// If we get here, not yet registered
				memset(&wcex, 0, sizeof(wcex));
				wcex.cbSize         = sizeof(wcex);
				wcex.style          = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
				wcex.lpfnWndProc    = &iTooltip_wndProc;
				wcex.hInstance      = GetModuleHandle(NULL);
				wcex.hCursor		= LoadCursor(null0, IDC_ARROW);
				wcex.lpszClassName  = (cs8*)cgcTooltipClass;
				atom				= RegisterClassExA(&wcex);

				// Was it registered?
				if (!atom)
					ExitThread(-1);		// Nope ... when we get here, failure
			}


		//////////
		// Get the structure
		//////
			tooltip = (STooltip*)lpParameter;

		//////////
		// Create the window
		//////
			lnWidth			= tooltip->rc.right  - tooltip->rc.left;
			lnHeight		= tooltip->rc.bottom - tooltip->rc.top;
			tooltip->hwnd	= CreateWindowEx(WS_EX_TOOLWINDOW, (cs8*)cgcTooltipClass, NULL,
												WS_POPUP,
												tooltip->rc.left,
												tooltip->rc.top,
												lnWidth,
												lnHeight,
												null0, null0, GetModuleHandle(NULL), 0);

		//////////
		// Store the settings
		//////
#ifdef __64_BIT_COMPILER__
			// I get a warning in VS2010 if I use this code, and if I don't I get a warning in GCC... can't win. :-)
	#if defined(WIN64)

			SetWindowLong(tooltip->hwnd, GWL_USERDATA, (long)_lpParameter);
	#elif __linux__
			SetWindowLong(tooltip->hwnd, GWL_USERDATA, (uptr)lpParameter);
	#else
			#error Unknown target for compilation (must be Windows, Linux, or Solaris (OpenIndiana))
	#endif
#else
			SetWindowLong(tooltip->hwnd, GWL_USERDATA, (long)lpParameter);
#endif


		//////////
		// Display the window
		//////
			tooltip->isValid = true;
			SetWindowPos(tooltip->hwnd, HWND_TOPMOST, tooltip->rc.left, tooltip->rc.top, lnWidth, lnHeight, SWP_SHOWWINDOW | SWP_NOACTIVATE);


		//////////
		// Create the timer
		//////
			SetTimer(tooltip->hwnd, (uptr)tooltip, _TOOLTIP_TIMER_INTERVAL, 0);


		//////////
		// Process messages
		//////
			while (tooltip->isValid && GetMessage(&msg, null0, 0, 0))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			// Delete the window
			iTooltip_delete(tooltip);

			// Free self
			free(tooltip);

			// All done
			ExitThread(0);

			// The following return(0) line is required for VC98, but will never be used
			return(0);
	}




//////////
//
// Called to delete a specific tooltip
//
//////
	void iTooltip_delete(STooltip* tooltip)
	{
		// Indicate it's no longer valid
		tooltip->isValid = false;

		// Kill the timer
		KillTimer(tooltip->hwnd, (uptr)tooltip);

		// Delete the bitmap
		if (tooltip->bmp)
			iBmp_delete(&tooltip->bmp, true, true);

		// Delete the window
		DestroyWindow(tooltip->hwnd);
	}




//////////
//
// Called to handle window events based on the tooltip
//
//////
	LRESULT CALLBACK iTooltip_wndProc(HWND hwnd, UINT m, WPARAM w, LPARAM l)
	{
		HDC			lhdc;
		PAINTSTRUCT	ps;
		STooltip*	tooltip;


		// The only message we handle is the paint
		tooltip = (STooltip*)GetWindowLong(hwnd, GWL_USERDATA);		// GCC's 64-bit compiler throws a warning on this line ... I'm not sure how to remove it.
		if (tooltip)
		{
			switch (m)
			{
				case WM_LBUTTONDOWN:
				case WM_MBUTTONDOWN:
				case WM_RBUTTONDOWN:
					// They clicked on it, they want it removed
					tooltip->isValid = false;
					break;

				case WM_TIMER:
					// Decrease by our timer interval
					tooltip->timeoutMs -= _TOOLTIP_TIMER_INTERVAL;

					// If we're reached the timeout interval, delete it
					if (tooltip->timeoutMs <= 0)
						tooltip->isValid = false;

					break;

				case WM_PAINT:
					// Start painting
					lhdc = BeginPaint(hwnd, &ps);

					// Paint it
					if (tooltip->bmp)
						BitBlt(lhdc, 0, 0, tooltip->bmp->bi.biWidth, tooltip->bmp->bi.biHeight, tooltip->bmp->hdc, 0, 0, SRCCOPY);

					// All done
					EndPaint(hwnd, &ps);
					return(0);
			}
		}

		// Default handler
		return(DefWindowProc(hwnd, m, w, l));
	}




//////////
//
// Called to reset the sourceLight to an empty state
//
//////
	void iSourceLight_reset(void)
	{
		RECT lrc;


		// If we have a sourceLight bitmap...
		if (bmpSourceLight)
		{
			// Make it all white
			SetRect(&lrc, 0, 0, bmpSourceLight->bi.biWidth, bmpSourceLight->bi.biHeight);
			iBmp_fillRect(bmpSourceLight, &lrc, whiteColor, whiteColor, whiteColor, whiteColor, false, NULL, false);

			// Reset the coordinates to the top
			gnSourceLightX	= _SOURCELIGHT_MARGIN;
			gnSourceLightY	= _SOURCELIGHT_MARGIN;
		}
	}




//////////
//
// Called to copy the sourceLight contents to the indicated object's bitmap
//
///////
	bool iSourceLight_copy(SWindow* win, SObject* obj)
	{
		SThisCode*	thisCode = NULL;
		s32			scrollX, scrollY;
		RECT		lrc;


		// Make sure our environment is sane
		if (obj && obj->bmp && bmpSourceLight)
		{
			//////////
			// Grab our scroll offsets
			//////
				scrollX = iObjProp_get_s32_direct(obj, _INDEX_SCROLLX);
				scrollY = iObjProp_get_s32_direct(obj, _INDEX_SCROLLX);


			//////////
			// Copy over the part that will fit
			//////
				iiBmp_bitBltPortion(obj->bmp, 0, 0, obj->bmp->bi.biWidth, obj->bmp->bi.biHeight, bmpSourceLight, scrollX, scrollY);


			//////////
			// Fill in any rectangles beyond the scroll
			//////
// TODO:  An optimization here would be to not overlay any portion in the lower-right both horizontally and vertically
				// Portion at the right
				if (bmpSourceLight->bi.biWidth - scrollX < obj->bmp->bi.biWidth)
				{
					// From the edge of the sourceLight content to the extent of the bitmap horizontally
					SetRect(&lrc, bmpSourceLight->bi.biWidth - scrollX, 0, obj->bmp->bi.biWidth, obj->bmp->bi.biHeight);
					iBmp_fillRect(obj->bmp, &lrc, whiteColor, whiteColor, whiteColor, whiteColor, false, NULL, false);
				}

				// Portion at the bottom
				if (bmpSourceLight->bi.biHeight - scrollY < obj->bmp->bi.biHeight)
				{
					// From the edge of the sourceLight content to the extent of the bitmap horizontally
					SetRect(&lrc, 0, bmpSourceLight->bi.biHeight - scrollY, obj->bmp->bi.biWidth, obj->bmp->bi.biHeight);
					iBmp_fillRect(obj->bmp, &lrc, whiteColor, whiteColor, whiteColor, whiteColor, false, NULL, false);
				}
		}

		// Indicate that the processing should continue
		return(true);
	}




//////////
//
// Called to read the contents of the indicated file
//
//////
	bool iFile_readContents(s8* tcFilename, FILE** tfh, s8** data, u32* dataLength)
	{
		u32		lnNumread;
		FILE*	lfh;


		// Make sure our environment is sane
		if (tcFilename && data && dataLength)
		{
			// Try to open the file
			lfh = fopen(tcFilename, "rb+");
			if (lfh)
			{
				// Find out how big it is
				fseek(lfh, 0, SEEK_END);
				*dataLength = ftell(lfh);
				fseek(lfh, 0, SEEK_SET);

				// Allocate a buffer that large
				*data = (s8*)malloc(*dataLength);
				if (*data)
				{
					// Read the contents
					lnNumread = (u32)fread(*data, 1, *dataLength, lfh);
					if (lnNumread == *dataLength)
					{
						// We read everything
						if (tfh)
						{
							// Save the file handle, return it open
							*tfh = lfh;

						} else {
							// Close the file handle
							fclose(lfh);
						}

						// Indicate success
						return(true);
					}

				} else {
					// Error allocating that much memory
					fclose(lfh);
				}
			}
		}
		// If we get here, failure
		return(false);
	}




//////////
//
// Search backwards for the start of the string, or the first \ found
//
//////
	bool iFile_get_justfname(s8* tcPathname, s32 tnFilenameLength, s8** tcFname, s32* tnFnameLength)
	{
		s32 lnI, lnLength;


		// Make sure our environment is sane
		if (tcPathname && tcFname && tnFnameLength && tnFnameLength)
		{
			// Scan backwards
			for (lnI = tnFilenameLength - 1, lnLength = 1; lnI > 0; lnI--, lnLength++)
			{
				// Have we reached the \ ?
				if (tcPathname[lnI] == '\\')
					break;
			}

			// Indicate our pointer and length
			*tcFname		= tcPathname + lnI;
			*tnFnameLength	= lnLength;

			// Indicate success
			return(true);
		}

		// If we get here, failure
		return(false);
	}




//////////
//
// Called to parse a raw file into lines
//
//////
	// Returns line count
	s32 iFile_parseIntoLines(SLine** firstLine, s8* data, u32 dataLength)
	{
		u32			lnI, lnJ, lnLast, lnLineNumber;
		SLine*		line;
		SLine**		lastLine;


		// Copy through lines into the SLine struct
		for (lnI = 0, lnLast = 0, lastLine = firstLine, lnLineNumber = 1; lnI < dataLength; )
		{

			//////////
			// Are we on a CR/LF combination?
			//////
				for (lnJ = 0; (data[lnI] == 13 || data[lnI] == 10) && lnJ < 2 && (u32)lnI < dataLength; lnJ++)
					++lnI;	// Increase also past this CR/LF character


			//////////
			// If we found a CR/LF combination
			//////
				if (lnJ != 0 || lnI >= dataLength)
				{

					//////////
					// Increase our line count
					//////
						++lnLineNumber;


					//////////
					// We've entered into a CR/LF block, append a new line
					//////
						line = (SLine*)iLl_appendNewNodeAtEnd((SLL**)lastLine, sizeof(SLine));
						if (!line)
							return(-1);		// Unexpected failure


					//////////
					// Indicate content
					//////
						line->sourceCode	= iDatum_allocate((u8*)data + lnLast, (s32)(lnI - lnJ - lnLast));
						line->lineNumber	= lnLineNumber;


					//////////
					// Indicate where we are now
					//////
						lnLast		= lnI;
						lastLine	= &line;

				} else {
					// Still going
					++lnI;
				}
				// Continue on processing the next line if we have room

		}

		// Indicate how many lines
		return(lnLineNumber);
	}




//////////
//
// Adjusts the brightness of the indicated color by the indicated percentage.
//
//////
	void iMisc_adjustColorBrightness(SBgra& color, f32 tfPercent)
	{
		f32 red, grn, blu;


		//////////
		// Adjust the color
		//////
			tfPercent	= (100.0f + tfPercent) / 100.0f;
			red			= (f32)color.red * tfPercent;
			grn			= (f32)color.grn * tfPercent;
			blu			= (f32)color.blu * tfPercent;


		//////////
		// Constrict it into range
		//////
			red			= min(max(red, 0.0f), 255.0f);
			grn			= min(max(grn, 0.0f), 255.0f);
			blu			= min(max(blu, 0.0f), 255.0f);


		//////////
		// Set the color back
		//////
			color.red	= (u8)red;
			color.grn	= (u8)grn;
			color.blu	= (u8)blu;
	}




//////////
//
// Called to shutdown the system politely, closing everything that's open
//
//////
	bool iInit_shutdownPolitely(void)
	{
		return(true);
	}

	bool iTestExactlyEqual(u8* left, u32 leftLength, cu8* right, u32 rightLength)
	{
		return(iTestExactlyEqual(left, leftLength, (u8*)right, rightLength));
	}

	bool iTestExactlyEqual(u8* left, u32 leftLength, u8* right, u32 rightLength)
	{
		// Everything must be established
		if (left && right && leftLength == rightLength)
			return(_memicmp((s8*)left, (s8*)right, leftLength) == 0);	// Test equality without regards to case

		// If we get here, no match
		return(false);
	}

	bool iTestExactlyEqual_case(u8* left, u32 leftLength, cu8* right, u32 rightLength)
	{
		return(iTestExactlyEqual_case(left, leftLength, (u8*)right, rightLength));
	}

	bool iTestExactlyEqual_case(u8* left, u32 leftLength, u8* right, u32 rightLength)
	{
		// Everything must be established
		if (left && right && leftLength == rightLength)
			return(memcmp((s8*)left, (s8*)right, leftLength) == 0);	// Test equality

		// If we get here, no match
		return(false);
	}

	bool iIsNeedleInHaystack(s8* haystack, s32 haystackLength, s8* needle, s32 needleLength)
	{
		return(iIsNeedleInHaystack(haystack, haystackLength, needle, needleLength, NULL));
	}

	// Case sensitive variation
	bool iIsNeedleInHaystackCase(s8* haystack, s32 haystackLength, s8* needle, s32 needleLength)
	{
		return(iIsNeedleInHaystackCase(haystack, haystackLength, needle, needleLength, NULL));
	}

	bool iIsNeedleInHaystack(s8* haystack, s32 haystackLength, s8* needle, s32 needleLength, u32* tnStart)
	{
		s32 lnI;


		// Make sure the lengths are valid
		if (haystackLength < 0)		haystackLength	= (s32)strlen(haystack);
		if (needleLength < 0)		needleLength	= (s32)strlen(needle);

		// Iterate to see if we find it
		for (lnI = 0; lnI <= haystackLength - needleLength; lnI++)
		{
			if (_memicmp(haystack + lnI, needle, needleLength) == 0)
			{
				// Store the offset if we're supposed to
				if (tnStart)
					*tnStart = lnI;
				// Indicate success
				return(true);
			}
		}

		// Failure
		return(false);
	}

	bool iIsNeedleInHaystackCase(s8* haystack, s32 haystackLength, s8* needle, s32 needleLength, u32* tnStart)
	{
		s32 lnI;


		// Make sure the lengths are valid
		if (haystackLength < 0)		haystackLength	= (s32)strlen(haystack);
		if (needleLength < 0)		needleLength	= (s32)strlen(needle);

		// Check to see if the specified word / phrase / whatever exists on this line
		for (lnI = 0; lnI <= haystackLength - needleLength; lnI++)
		{
			if (memcmp(haystack + lnI, needle, needleLength) == 0)
			{
				// Store the offset if we're supposed to
				if (tnStart)
					*tnStart = lnI;
				// Indicate success
				return(true);
			}
		}

		// Failure
		return(false);
	}

	// Search only for a single character without regard to case
	bool iIsCharacterInHaystack(s8* haystack, s32 haystackLength, s8 needle, u32* tnOffset)
	{
		s32		lnI;
		s8		c;


		// Make sure the length is valid
		if (haystackLength < 0)
			haystackLength	= (s32)strlen(haystack);

		// Check to see if the specified word / phrase / whatever contains this character
		c = iLowerCharacter(needle);
		for (lnI = 0; lnI < haystackLength; lnI++)
		{
			if (iLowerCharacter(haystack[lnI]) == c)
			{
				if (tnOffset)
					*tnOffset = lnI;

				return(true);
			}
		}

		// Failure
		return(false);
	}

	// Search only for a single character by case
	bool iIsCharacterInHaystackCase(s8* haystack, s32 haystackLength, s8 needle, u32* tnOffset)
	{
		s32 lnI;


		// Make sure the length is valid
		if (haystackLength < 0)
			haystackLength	= (s32)strlen(haystack);

		// Check to see if the specified word / phrase / whatever contains this character
		for (lnI = 0; lnI < haystackLength; lnI++)
		{
			if (haystack[lnI] == needle)
			{
				if (tnOffset)
					*tnOffset = lnI;

				return(true);
			}
		}

		// Failure
		return(false);
	}

	// Searches backwards for the specified character
	bool iIsCharacterInHaystackReversed(s8* haystack, s32 haystackLength, s8 needle, u32* tnOffset)
	{
		s32		lnI;
		s8		c;


		// Make sure the length is valid
		if (haystackLength < 0)
			haystackLength	= (s32)strlen(haystack);

		// Check to see if the specified word / phrase / whatever contains this character
		c = iLowerCharacter(needle);
		for (lnI = haystackLength - 1; lnI >= 0; lnI--)
		{
			if (iLowerCharacter(haystack[lnI]) == c)
			{
				if (tnOffset)
					*tnOffset = lnI;

				return(true);
			}
		}

		// Failure
		return(false);
	}

	bool iIsCharacterInHaystackReversedCase(s8* haystack, s32 haystackLength, s8 needle, u32* tnOffset)
	{
		s32 lnI;


		// Make sure the length is valid
		if (haystackLength < 0)
			haystackLength	= (s32)strlen(haystack);

		// Check to see if the specified word / phrase / whatever contains this character
		for (lnI = haystackLength - 1; lnI >= 0; lnI--)
		{
			if (haystack[lnI] == needle)
			{
				if (tnOffset)
					*tnOffset = lnI;

				return(true);
			}
		}

		// Failure
		return(false);
	}

	// We allow for:  .t., .f., .o., .p., .x., .y., .z., true, false, yes, no, 0, 1
	bool iIsBoolText(SDatum* d, bool* tlStoreValue, bool tlAllowLogicalX)
	{
		bool llResult, llStoreValue;


		//////////
		// Is the datum valid?
		//////
			llResult		= false;
			llStoreValue	= false;
			if (d && d->data && d->length > 0)
			{
				// Could be 0 or 1
				if (d->length == 1)
				{
					if (*d->data_s8 == '0')
					{
						// It's false
						llResult		= true;
						llStoreValue	= false;

					} else if (*d->data_s8 == '1') {
						// It's true
						llResult		= true;
						llStoreValue	= false;
					}


				// Can only be no
				} else if (d->length == 2) {
					if (iDatum_compare(d, cgc_no, sizeof(cgc_no) - 1) == 0)
					{
						llResult		= true;
						llStoreValue	= false;
					}


				// Can be yes, .t., .f., .o., .p., .x., .y. or .z.
				} else if (d->length == 3) {
					if (iDatum_compare(d, cgc_t_dots, sizeof(cgc_t_dots) - 1) == 0)
					{
						llResult		= true;
						llStoreValue	= true;

					} else if (iDatum_compare(d, cgc_f_dots, sizeof(cgc_f_dots) - 1) == 0) {
						llResult		= true;
						llStoreValue	= false;

					} else if (tlAllowLogicalX) {
						// Has to be .o., .p., .x., .y. or .z.
						if (iDatum_compare(d, cgc_o_dots, sizeof(cgc_o_dots) - 1) == 0) {
							llResult		= true;
							llStoreValue	= false;

						} else if (iDatum_compare(d, cgc_p_dots, sizeof(cgc_p_dots) - 1) == 0) {
							llResult		= true;
							llStoreValue	= false;

						} else if (iDatum_compare(d, cgc_x_dots, sizeof(cgc_x_dots) - 1) == 0) {
							llResult		= true;
							llStoreValue	= false;

						} else if (iDatum_compare(d, cgc_y_dots, sizeof(cgc_y_dots) - 1) == 0) {
							llResult		= true;
							llStoreValue	= false;

						} else if (iDatum_compare(d, cgc_z_dots, sizeof(cgc_z_dots) - 1) == 0) {
							llResult		= true;
							llStoreValue	= false;
						}
					}


				// Can only be true
				} else if (d->length == 4) {
					if (iDatum_compare(d, cgc_true, sizeof(cgc_true) - 1) == 0)
					{
						llResult		= true;
						llStoreValue	= true;
					}


				// Can only be false
				} else if (d->length == 5) {
					if (iDatum_compare(d, cgc_false, sizeof(cgc_false) - 1) == 0)
					{
						llResult		= true;
						llStoreValue	= false;
					}
				}
			}


		//////////
		// Store the actual value (if need be)
		//////
			if (tlStoreValue)
				*tlStoreValue = llStoreValue;


		//////////
		// Indicate our status
		//////
			return(llResult);
	}

	bool iIsNotNull(void* p)
	{
		return(p != NULL);
	}

	void* iif(bool tlTest, void* ifTrue, void* ifFalse)
	{
		if (tlTest)		return(ifTrue);
		else			return(ifFalse);
	}

	s32 iif(bool tlTest, s32 ifTrue, s32 ifFalse)
	{
		if (tlTest)		return(ifTrue);
		else			return(ifFalse);
	}

	s64 iMath_delta(s64 tnBaseValue, s64 tnSubtractionValue)
	{
		return(tnBaseValue - tnSubtractionValue);
	}




//////////
//
// Checks to see if the specified needle is found at the start of the haystack
//
//////
	bool iDoesHaystackStartWithNeedle(s8* haystack, s32 haystackLength, s8* needle, s32 needleLength)
	{
		s32 lnWhitespaces;


		// Make sure the length is valid
		if (haystackLength < 0)
			haystackLength	= (s32)strlen(haystack);

		// Skip past any whitespaces
		lnWhitespaces = 0;
		iSkip_whitespaces(haystack, (u32*)&lnWhitespaces, haystackLength);

		// Check to see if the specified word / phrase / whatever exists on this line
		if (haystackLength - lnWhitespaces >= needleLength)
		{
			if (_memicmp(haystack + lnWhitespaces, needle, needleLength) == 0)
				return(true);
		}

		// Failure
		return(false);
	}

	// Case sensitive variation
	bool iDoesHaystackStartWithNeedleCase(s8* haystack, s32 haystackLength, s8* needle, s32 needleLength)
	{
		s32 lnWhitespaces;


		// Make sure the lengths are valid
		if (haystackLength < 0)		haystackLength	= (s32)strlen(haystack);
		if (needleLength < 0)		needleLength	= (s32)strlen(needle);

		// Skip past any whitespaces
		lnWhitespaces = 0;
		iSkip_whitespaces(haystack, (u32*)&lnWhitespaces, haystackLength);

		// Check to see if the specified word / phrase / whatever exists on this line
		if (haystackLength - lnWhitespaces >= needleLength)
		{
			if (memcmp(haystack + lnWhitespaces, needle, needleLength) == 0)
				return(true);
		}

		// Failure
		return(false);
	}

	s8 iLowerCharacter(s8 ch)
	{
		if (ch >= 'A' && ch <= 'Z')
			ch += 0x20;
		return(ch);
	}




//////////
//
// Skips past whitespace characters (tabs and spaces)
// Move the offset byte forward until we're no longer sitting on a
// whitespace character, and indicate how many we skipped.
//
//////
	u32 iSkip_whitespaces(s8* source, u32* offset, u32 maxLength)
	{
		s8		c;
		u32		lnLength, lnOffset;


		// Make sure the length is valid
		if (maxLength < 0)
			maxLength = (u32)strlen(source);

		// Make sure we have valid parameters
		if (!offset)
		{
			// They didn't give us an offset, so we use our own, home-grown solution, that's right, my friend! :-)
			lnOffset	= 0;
			offset = &lnOffset;
		}

		// Move from the current location to its new location
		lnLength = 0;
		while (*offset < maxLength)
		{
			c = source[*offset];
			if (c != 32/*space*/ && c != 9/*tab*/)
				return(lnLength);		// It's no longer a whitespace

			// Move to the next position
			++lnLength;
			++*offset;
		}
		return(lnLength);
	}




//////////
//
// Called to count contiguous characters (non-nulls, non-whitespaces)
//
//////
	u32 iiCountContiguousCharacters(u8* source, u32 maxExpectedLength)
	{
		return(iiCountContiguousCharacters((s8*)source, maxExpectedLength));
	}

	u32 iiCountContiguousCharacters(s8* source, u32 maxExpectedLength)
	{
		u32 lnLength;


		// Iterate until we find a null, or whitespace, or reach the maximum expected length
		for (lnLength = 0; lnLength < maxExpectedLength; lnLength++, source++)
		{
			// See if we're on a null, or whitespace
			if (*source == 0 || *source == 9 || *source == 32)
				break;		// Yes, we're done
		}

		// Indicate our length
		return(lnLength);
	}




//////////
//
// Called to round the value to the indicated decimal place
//
//////
	s8* iMath_roundTo(f64* tfValue, f64 tfRoundTo)
	{
		if (tfRoundTo == 1000.0)				{ *tfValue = ((f64)((s64)(*tfValue / 1000.0)) * 1000.0);						return((s8*)"%15.0lf"); }
		if (tfRoundTo == 100.0)					{ *tfValue = ((f64)((s64)(*tfValue / 100.0)) * 100.0);							return((s8*)"%15.0lf"); }
		if (tfRoundTo == 10.0)					{ *tfValue = ((f64)((s64)(*tfValue / 10.0)) * 10.0);							return((s8*)"%15.0lf"); }
		if (tfRoundTo == 1.0)					{ /* This entry added for speed, as it's likely to be a very common round */	return((s8*)"%15.0lf"); }
		if (tfRoundTo == 0.1)					{ *tfValue = ((f64)((s64)(*tfValue * 10.0)) / 10.0);							return((s8*)"%15.1lf"); }
		if (tfRoundTo == 0.01)					{ *tfValue = ((f64)((s64)(*tfValue * 100.0)) / 100.0);							return((s8*)"%15.2lf"); }
		if (tfRoundTo == 0.001)					{ *tfValue = ((f64)((s64)(*tfValue * 1000.0)) / 1000.0);						return((s8*)"%15.3lf"); }
		if (tfRoundTo == 0.0001)				{ *tfValue = ((f64)((s64)(*tfValue * 10000.0)) / 10000.0);						return((s8*)"%15.4lf"); }
		if (tfRoundTo == 0.00001)				{ *tfValue = ((f64)((s64)(*tfValue * 100000.0)) / 100000.0);					return((s8*)"%15.5lf"); }
		if (tfRoundTo == 0.000001)				{ *tfValue = ((f64)((s64)(*tfValue * 1000000.0)) / 1000000.0);					return((s8*)"%15.6lf"); }
		if (tfRoundTo == 0.0000001)				{ *tfValue = ((f64)((s64)(*tfValue * 10000000.0)) / 10000000.0);				return((s8*)"%15.7lf"); }
		if (tfRoundTo == 0.00000001)			{ *tfValue = ((f64)((s64)(*tfValue * 100000000.0)) / 100000000.0);				return((s8*)"%15.8lf"); }
		if (tfRoundTo == 0.000000001)			{ *tfValue = ((f64)((s64)(*tfValue * 1000000000.0)) / 1000000000.0);			return((s8*)"%15.9lf"); }
		if (tfRoundTo == 0.0000000001)			{ *tfValue = ((f64)((s64)(*tfValue * 10000000000.0)) / 10000000000.0);			return((s8*)"%15.10lf"); }
		if (tfRoundTo == 0.00000000001)			{ *tfValue = ((f64)((s64)(*tfValue * 100000000000.0)) / 100000000000.0);		return((s8*)"%15.11lf"); }
		if (tfRoundTo == 0.000000000001)		{ *tfValue = ((f64)((s64)(*tfValue * 1000000000000.0)) / 1000000000000.0);		return((s8*)"%15.12lf"); }
		if (tfRoundTo == 0.0000000000001)		{ *tfValue = ((f64)((s64)(*tfValue * 10000000000000.0)) / 10000000000000.0);	return((s8*)"%15.13lf"); }
		if (tfRoundTo == 100000000000000.0)		{ *tfValue = ((f64)((s64)(*tfValue / 100000000000000.0)) * 100000000000000.0);	return((s8*)"%15.0lf"); }
		if (tfRoundTo == 10000000000000.0)		{ *tfValue = ((f64)((s64)(*tfValue / 10000000000000.0)) * 10000000000000.0);	return((s8*)"%15.0lf"); }
		if (tfRoundTo == 1000000000000.0)		{ *tfValue = ((f64)((s64)(*tfValue / 1000000000000.0)) * 1000000000000.0);		return((s8*)"%15.0lf"); }
		if (tfRoundTo == 100000000000.0)		{ *tfValue = ((f64)((s64)(*tfValue / 100000000000.0)) * 100000000000.0);		return((s8*)"%15.0lf"); }
		if (tfRoundTo == 10000000000.0)			{ *tfValue = ((f64)((s64)(*tfValue / 10000000000.0)) * 10000000000.0);			return((s8*)"%15.0lf"); }
		if (tfRoundTo == 1000000000.0)			{ *tfValue = ((f64)((s64)(*tfValue / 1000000000.0)) * 1000000000.0);			return((s8*)"%15.0lf"); }
		if (tfRoundTo == 100000000.0)			{ *tfValue = ((f64)((s64)(*tfValue / 100000000.0)) * 100000000.0);				return((s8*)"%15.0lf"); }
		if (tfRoundTo == 10000000.0)			{ *tfValue = ((f64)((s64)(*tfValue / 10000000.0)) * 10000000.0);				return((s8*)"%15.0lf"); }
		if (tfRoundTo == 1000000.0)				{ *tfValue = ((f64)((s64)(*tfValue / 1000000.0)) * 1000000.0);					return((s8*)"%15.0lf"); }
		if (tfRoundTo == 100000.0)				{ *tfValue = ((f64)((s64)(*tfValue / 100000.0)) * 100000.0);					return((s8*)"%15.0lf"); }
		if (tfRoundTo == 10000.0)				{ *tfValue = ((f64)((s64)(*tfValue / 10000.0)) * 10000.0);						return((s8*)"%15.0lf"); }

		// If we get here, an unknown value
		return((s8*)"%.0lf");
	}




//////////
//
// Called to see if a value is between two others, inclusive
//
//////
	bool iMath_between(s32 tnValue, s32 tnN1, s32 tnN2)
	{
		// The math is simple :-)
		if (tnValue >= min(tnN1, tnN2) && tnValue <= max(tnN1, tnN2))
			return(true);

		// If we get here, not between
		return(false);
	}




//////////
//
// Checks to see if any point in the needle exists in the haystack, and if tlIncludeOversizes it will also
// check to see if the needle rectangle may be larger than the haystack needle, actually encompassing it.
//
// Normal needle (/// rectangle) in haystack checks:
//		// Within			// Point in		// Crosses
//		+------------+		+-----+			    +-----+
//		|            |		|/////|			    |/////|
//		|   +----+   |		|//+------+		+------+//|
//		|   |////|   |		|//|//|   |		|	|//|//|
//		|   +----+   |		+--|--x   |		|   |//|//|		... et cetera
//		|            |		   +------+		+------+//|
//		+------------+		           		    |/////|
//											    +-----+
//
// If checking oversizes, performs this check:
//		+------------+
//		|////////////|
//		|///+----+///|
//		|///|    |///|
//		|///+----+///|
//		|////////////|
//		+------------+
//
//////
	bool iMath_isRectInRect(RECT* rcHaystack, RECT* rcNeedle, bool tlIncludeOversizes)
	{
		s32		lnI;
		RECT*	lrcHaystack;
		RECT*	lrcNeedle;
		bool	llResult_left, llResult_top, llResult_right, llResult_bottom;


		// We may iterate twice depending on tlIncludeOversizes
		for (lnI = 0; lnI < 2; lnI++)
		{
			//////////
			// Determine each point
			//////
				if (lnI == 0)
				{
					// Set rcHaystack and rcNeedle
					lrcHaystack = rcHaystack;
					lrcNeedle	= rcNeedle;

				} else {
					// Swap rcHaystack and rcNeedle
					lrcHaystack = rcNeedle;
					lrcNeedle	= rcHaystack;
				}


			//////////
			// Check the bounding rectangle, if at least one point is within...
			//////
				llResult_left	= iMath_between(lrcNeedle->left,	lrcHaystack->left,	lrcHaystack->right);
				llResult_top	= iMath_between(lrcNeedle->top,		lrcHaystack->top,	lrcHaystack->bottom);
				llResult_right	= iMath_between(lrcNeedle->right,	lrcHaystack->left,	lrcHaystack->right);
				llResult_bottom	= iMath_between(lrcNeedle->bottom,	lrcHaystack->top,	lrcHaystack->bottom);


			//////////
			// Does it at any point intersect the rect?
			//////
				if (llResult_left || llResult_top || llResult_right || llResult_bottom)
					return(true);


			//////////
			// When we get here, it doesn't intersect
			//////
				if (!tlIncludeOversizes)
					break;
		}


		//////////
		// If we get here, it was not inside at any point
		//////
			return(false);
	}




//////////
//
// Called to compute the deltas between rectangle points, creating each delta in
// each relative position.
//
// Uses:
//	rcDelta.x = (rcNow.x - rcPrior.x)
//
//////
	RECT* iiMath_computeRectDeltas(RECT* rcDelta, RECT* rcNow, RECT* rcPrior)
	{
		// Compute deltas for each
		rcDelta->left	= rcNow->left - rcPrior->left;
		rcDelta->top	= rcNow->top - rcPrior->top;
		rcDelta->right	= rcNow->right - rcPrior->right;
		rcDelta->bottom	= rcNow->bottom - rcPrior->bottom;

		// Return our delta
		return(rcDelta);
	}




//////////
//
// Convert the case.
//
//////
	s8 iLowerCase(s8 c)
	{
		if (c >= 'A' && c <= 'Z')		return(c + 0x20);
		else							return(c);
	}

	s8 iUpperCase(s8 c)
	{
		if (c >= 'a' && c <= 'z')		return(c - 0x20);
		else							return(c);
	}




//////////
//
// Called to duplicate the indicated string
//
//////
	s8* iDuplicateString(s8* tcText)
	{
		u32		lnLength;
		s8*		ptr;


		// Allocate it
		lnLength	= (u32)strlen(tcText) + 1;
		ptr			= (s8*)malloc(lnLength);

		// Copy it (including the trailing null)
		if (ptr)
			memcpy(ptr, tcText, lnLength);

		// All done
		return(ptr);
	}




//////////
//
// Called to process the mouse messages.
//
//////
	s32 iMouse_processMessage(SWindow* win, UINT msg, WPARAM w, LPARAM l)
	{
		//////////
		// If we're a valid window, process the mouse
		//////
			if (win && win->obj && win->obj->rc.right > win->obj->rc.left)
			{
				// Copy the prior mouse condition to the current one
				memcpy(&win->mousePrior, &win->mouseCurrent, sizeof(win->mousePrior));

				// Translate the mouse from the scaled position to its real position
				iiMouse_translatePosition(win, (POINTS*)&l, msg);

				// Signal the event(s)
				iiMouse_processMouseEvents(win, msg, w, l);
			}
			// If we get here, invalid
			return(-1);
	}




//////////
//
// Called to translate the mouse position for the source window.
// Note:  The win parameter is required.
//
//////
	void iiMouse_translatePosition(SWindow* win, POINTS* pt, UINT msg)
	{
		POINT	lpt, lptOnOSDesktop;
		bool	llWheelMessage;


		//////////
		// Translate our SHORT points structure to the LONG point structure
		//////
			if (pt)
			{
				lpt.x = pt->x;
				lpt.y = pt->y;
				win->mouseCurrent.position.x = lpt.x;
				win->mouseCurrent.position.y = lpt.y;
			}


		//////////
		// Get the mouse flags
		//////
			iiMouse_getFlags_async(	&win->mouseCurrent.isCtrl,		&win->mouseCurrent.isAlt,			&win->mouseCurrent.isShift,
									&win->mouseCurrent.buttonLeft,	&win->mouseCurrent.buttonMiddle,	&win->mouseCurrent.buttonRight,
									&win->mouseCurrent.isCaps,
									&win->mouseCurrent.buttonAnyDown);


		//////////
		// If we're moving or resizing, also read the screen coordinate mouse data, and then return
		//////
			GetCursorPos(&lptOnOSDesktop);
			if (!(win->isMoving || win->isResizing))
			{
				// Get the mouse pointer in screen coordinates
				win->mouseCurrent.positionInOsDesktop.x = lptOnOSDesktop.x;
				win->mouseCurrent.positionInOsDesktop.y = lptOnOSDesktop.y;
				return;
			}


		//////////
		// If it's a mouse scroll, the coordinates are given in screen coordinates.
		// Subtract off the window portion
		//////
			llWheelMessage = (msg == WM_MOUSEWHEEL);
#ifdef WM_MOUSEHWHEEL
			llWheelMessage |= (msg == WM_MOUSEHWHEEL);
#endif
			if (llWheelMessage)
			{
				win->mouseCurrent.position.x -= win->rc.left;
				win->mouseCurrent.position.y -= win->rc.top;
			}
	}




//////////
//
// Process the mouse events in the client area for this form
//
//////
	s32 iiMouse_processMouseEvents(SWindow* win, UINT msg, WPARAM w, LPARAM l)
	{
		s32			lnResult;
		bool		llProcessed;
		SObject*	obj;


		//////////
		// Grab our pointer
		//////
			obj = win->obj;


		//////////
		// Determine the click flags
		//////
			obj->ev.thisClick = 0;
			obj->ev.thisClick	|= ((win->mouseCurrent.buttonLeft)		? _MOUSE_LEFT_BUTTON	: 0);
			obj->ev.thisClick	|= ((win->mouseCurrent.buttonMiddle)	? _MOUSE_MIDDLE_BUTTON	: 0);
			obj->ev.thisClick	|= ((win->mouseCurrent.buttonRight)		? _MOUSE_RIGHT_BUTTON	: 0);


		//////////
		// Iterate through objects to see where it is the mouse is traipsing
		//////
			// Note:  win->mouseLastPosition holds the coordinates
			// Note:  win->is* flags indicate both button and keyboard state conditions (ctrl, alt, shift, caps)
			llProcessed = false;
			switch (msg)
			{
				case WM_MOUSEWHEEL:
					// Signal a mouseScroll
					if (!win->isMoving && !win->isResizing)
					{
						win->mouseCurrent.wheelDeltaV	= (s32)((s16)(((u32)w) >> 16)) / WHEEL_DELTA;
						win->mouseCurrent.wheelDeltaH	= 0;
						iiMouse_processMouseEvents_common(win, obj, &obj->rc, msg, true, true, &llProcessed);
					}
					break;

#ifdef WM_MOUSEHWHEEL
				case WM_MOUSEHWHEEL:
					// Signal a mouseHScroll
					if (!win->isMoving && !win->isResizing)
					{
						win->mouseCurrent.wheelDeltaV	= 0;
						win->mouseCurrent.wheelDeltaH	= (s32)((s16)(((u32)w) >> 16)) / WHEEL_DELTA;
						iiMouse_processMouseEvents_common(win, obj, &obj->rc, msg, true, true, &llProcessed);
					}
					break;
#endif

				case WM_MOUSEMOVE:
					// Check for mouseEnter and mouseLeave, then a mouseMove
					if (!win->isMoving && !win->isResizing)
					{
						// Process normal mouse moves
						iiMouse_processMouseEvents_mouseMove(win, obj, &obj->rc, true, true, &llProcessed);

						// The mouse has moved, reset the hover counter
						obj->ev.startHoverTickCount	= GetTickCount();
						obj->ev.hasHoverSignaled		= false;
					}
					break;


				case WM_LBUTTONDOWN:
				case WM_RBUTTONDOWN:
				case WM_MBUTTONDOWN:
					// Signal a mouseDown, then a click
					if (iiMouse_processMouseEvents_common(win, obj, &obj->rc, msg, true, true, &llProcessed))
					{
						// Set the last click
						obj->ev._lastClick = obj->ev.thisClick;
					}
					break;

				case WM_LBUTTONUP:
				case WM_RBUTTONUP:
				case WM_MBUTTONUP:
					// Signal a mouseUp
					if (!win->isMoving && !win->isResizing)
					{
						// A mouse button was released
						iiMouse_processMouseEvents_common(win, obj, &obj->rc, msg, true, true, &llProcessed);
					}
					break;

				case WM_LBUTTONDBLCLK:
					// Signal a double click
//					iiMouse_processMouseEvents_client_dblClickEx(win, obj, &obj->rc, _MOUSE_LEFT_BUTTON, true, true);
					break;

				case WM_RBUTTONDBLCLK:
					// Signal a double click
//					iiMouse_processMouseEvents_client_dblClickEx(win, obj, &obj->rc, _MOUSE_RIGHT_BUTTON, true, true);
					break;

				case WM_MBUTTONDBLCLK:
					// Signal a double click
//					iiMouse_processMouseEvents_client_dblClickEx(win, obj, &obj->rc, _MOUSE_MIDDLE_BUTTON, true, true);
					break;
			}


		// Indicate our status
		lnResult = 0;
		return(lnResult);
	}




//////////
//
// Called as a common function to obtain the coordinates for the current object descent
//
//////
	bool iiMouse_processMouseEvents_getRectDescent(SWindow* win, SObject* obj, RECT* rc, RECT& lrc, RECT& lrcClient)
	{
		//////////
		// Determine the position within the parent's rectangle where this object will go
		//////
			// Adjust this item within the parent's rectangle
			SetRect(&lrc,	rc->left	+ obj->rc.left,
							rc->top		+ obj->rc.top,
							rc->left	+ obj->rc.right,
							rc->top		+ obj->rc.bottom);


		//////////
		// Are we in the client area?
		//////
			switch (obj->objType)
			{
				case _OBJ_TYPE_FORM:
				case _OBJ_TYPE_SUBFORM:
					// Adjust by the client coordinates
					SetRect(&lrcClient,	lrc.left	+ obj->rcClient.left,
										lrc.top		+ obj->rcClient.top,
										lrc.left	+ obj->rcClient.left	+ (obj->rcClient.right	- obj->rcClient.left),
										lrc.top		+ obj->rcClient.top		+ (obj->rcClient.bottom	- obj->rcClient.top));
					break;

				default:
					// Use the full coordinates
					CopyRect(&lrcClient, &lrc);
					break;
			}


		//////////
		// Clip to the parent rectangle
		//////
			if (!obj->parent || obj->parent->objType != _OBJ_TYPE_FORM)
			{
				lrc.right	= min(rc->right,	lrc.right);
				lrc.bottom	= min(rc->bottom,	lrc.bottom);
			}


		//////////
		// Indicate if we're in the client area
		//////
			return((PtInRect(&lrcClient, win->mouseCurrent.position)) ? true : false);
	}




//////////
//
// Called to process the mouse move events when the window is being moved or resized
//
//////
	void iiMouse_processMouseEvents_windowSpecial(SWindow* win)
	{
		s32 lnDeltaX, lnDeltaY;


		//////////
		// If the window is moving or resizing
		//////
			if (win->isMoving)
			{
				//////////
				// Get current mouse flags
				//////
					iiMouse_getFlags_async(	&win->mouseCurrent.isCtrl,		&win->mouseCurrent.isAlt,			&win->mouseCurrent.isShift,
											&win->mouseCurrent.buttonLeft,	&win->mouseCurrent.buttonMiddle,	&win->mouseCurrent.buttonRight,
											&win->mouseCurrent.isCaps,
											&win->mouseCurrent.buttonAnyDown);


				//////////
				// Calculate the deltas from where it began moving
				//////
					// delta = (started - current)
					lnDeltaX = win->mouseMoveResizeStart.positionInOsDesktop.x - win->mouseCurrent.positionInOsDesktop.x;
					lnDeltaY = win->mouseMoveResizeStart.positionInOsDesktop.y - win->mouseCurrent.positionInOsDesktop.y;


				//////////
				// Are we done?
				//////
					if (!win->mouseCurrent.buttonLeft)
					{
						// They've released the mouse button since the last move
						// We go ahead and process through even if it hasn't moved

					} else if (lnDeltaX == win->movingLastDeltaX && lnDeltaY == win->movingLastDeltaY) {
						// Nothing has changed this go around
						return;
					}


				//////////
				// Set our last values
				//////
					win->movingLastDeltaX = lnDeltaX;
					win->movingLastDeltaY = lnDeltaY;


				//////////
				// Position the window to its new location
				//////
					SetWindowPos(win->hwnd, null0, win->rc.left - lnDeltaX, win->rc.top - lnDeltaY, 0, 0, SWP_NOSIZE | SWP_NOZORDER);


				//////////
				// If we're done, then we're done
				//////
					if (!win->mouseCurrent.buttonLeft)
					{
						// We're done
						GetWindowRect(win->hwnd, &win->rc);
						win->isMoving = false;
					}

			} else if (win->isResizing) {
				// Resizing
			}
	}




//////////
//
// Called to process mouseEnter and mouseLeave events based on mouse movement
//
//////
	bool iiMouse_processMouseEvents_mouseMove(SWindow* win, SObject* obj, RECT* rc, bool tlProcessChildren, bool tlProcessSiblings, bool* tlProcessed)
	{
		bool		llContinue, llInClientArea;
		RECT		lrc, lrcClient;
		SObject*	objSib;


		// Make sure our object environment is sane
		llContinue = true;
		while (propIsEnabled(obj) && obj->bmp)
		{ // Block entered only for structured programming

			//////////
			// Get the rectangle we're in at this level
			/////
				llInClientArea = iiMouse_processMouseEvents_getRectDescent(win, obj, rc, lrc, lrcClient);


			//////////
			// Process any children
			//////
				if (tlProcessChildren && obj->firstChild)
				{
					llContinue = iiMouse_processMouseEvents_mouseMove(win, obj->firstChild, &lrcClient, true, true, tlProcessed);
					if (!llContinue)
						break;
				}


			//////////
			// Are we within this object?
			//////
				if (PtInRect(&lrc, win->mouseCurrent.position))
				{
					// We are in this object
					*tlProcessed = true;	// Indicate we've processed this
					if (!obj->ev.isMouseOver)
						iEngine_raise_event(_EVENT_ONMOUSEENTER, win, obj);


					// Are we in the client area?
					if (llInClientArea)
					{
						//////////
						// Signal the mouseMove event
						//////
							llContinue = iiEventDispatch_onMouseMove(win, obj,
																		win->mouseCurrent.position.x - lrc.left,
																		win->mouseCurrent.position.y - lrc.top,
																		win->mouseCurrent.isCtrl, win->mouseCurrent.isAlt, win->mouseCurrent.isShift,
																		win->obj->ev.thisClick);
							if (!llContinue)
								break;

					} else {
						// We are in the non-client area

						//////////
						// Signal the mouseMove event in the non-client area, which means negative values, or
						// values outside of the width
						//
						// For non-client areas, we translate to negative is to the left or above the client area,
						// with values extending beyond the width and height if it is in the outer area
						//////
							*tlProcessed = true;	// Indicate we've processed this
							llContinue = iiEventDispatch_onMouseMove(win, obj,
																		win->mouseCurrent.position.x - lrcClient.left,
																		win->mouseCurrent.position.y - lrcClient.top,
																		win->mouseCurrent.isCtrl, win->mouseCurrent.isAlt, win->mouseCurrent.isShift,
																		win->obj->ev.thisClick);
							if (!llContinue)
								break;
					}

				} else {
					// We are outside of this object
					if (obj->ev.isMouseOver)
						iEngine_raise_event(_EVENT_ONMOUSELEAVE, win, obj);
				}


			//////////
			// Process any siblings
			//////
				if (llContinue && tlProcessSiblings)
				{
					// Begin at the next sibling
					objSib = obj->ll.nextObj;
					while (objSib)
					{
						// Process this sibling
						llContinue = iiMouse_processMouseEvents_mouseMove(win, objSib, rc, true, false, tlProcessed);
						if (!llContinue)
							break;

						// Move to next sibling
						objSib = objSib->ll.nextObj;
					}
				}

			// Exit block
				break;
		}

		// Indicate our status
		return(llContinue);
	}




//////////
//
// Called to signal a mouseDown event, then the mouseClickEx event
//
//////
	bool iiMouse_processMouseEvents_common(SWindow* win, SObject* obj, RECT* rc, UINT m, bool tlProcessChildren, bool tlProcessSiblings, bool* tlProcessed)
	{
		bool		llInObjectArea, llInClientArea, llContinue, llEnabled, llVisible;
		RECT		lrc, lrcClient;
		SObject*	objSib;


		// Make sure our environment is sane
JDebiC_debug(win, obj);
		llContinue = true;
		if (obj)
		{
			// Only enabled, visible things receive mouse events
			llEnabled	= propIsEnabled(obj);
			llVisible	= propIsVisible(obj);
			if (llEnabled && llVisible && obj->bmp)
			{

				//////////
				// Get the rectangle we're in at this level
				//////
					llInClientArea	= iiMouse_processMouseEvents_getRectDescent(win, obj, rc, lrc, lrcClient);
					llInObjectArea	= (PtInRect(&lrc, win->mouseCurrent.position) == TRUE);


				//////////
				// Carousels always receive wheel events no matter what
				//////
					llInClientArea	= (llInObjectArea && (obj->objType == _OBJ_TYPE_CAROUSEL));


				//////////
				// Process any children
				//////
					if (tlProcessChildren && obj->firstChild)
						llContinue = iiMouse_processMouseEvents_common(win, obj->firstChild, &lrcClient, m, true, true, tlProcessed);


				//////////
				// Are we still needing processing?
				//////
					// Indicate if the mouse is still down here
					obj->ev.isMouseDown = (obj->ev.thisClick != 0);

					// Are we in this object?
					if (llInClientArea)
					{
						// What was the mouse message?
						switch (m)
						{
							case WM_LBUTTONDOWN:
							case WM_RBUTTONDOWN:
							case WM_MBUTTONDOWN:
								// Signal the mouseDown event
								*tlProcessed = true;		// Indicate we've processed this
								if (llContinue)
									llContinue = iiEventDispatch_onMouseDown(win, obj,
																				win->mouseCurrent.position.x - lrc.left,
																				win->mouseCurrent.position.y - lrc.top,
																				win->mouseCurrent.isCtrl, win->mouseCurrent.isAlt, win->mouseCurrent.isShift,
																				win->obj->ev.thisClick);

								// Signal the click event
								if (llContinue)
									llContinue = iiEventDispatch_onMouseClickEx(win, obj,
																					win->mouseCurrent.position.x - lrc.left,
																					win->mouseCurrent.position.y - lrc.top,
																					win->mouseCurrent.isCtrl, win->mouseCurrent.isAlt, win->mouseCurrent.isShift,
																					win->obj->ev.thisClick);

								break;

							case WM_LBUTTONUP:
							case WM_RBUTTONUP:
							case WM_MBUTTONUP:
								// Signal the mouseUp event
								*tlProcessed = true;		// Indicate we've processed this
								if (llContinue)
									llContinue = iiEventDispatch_onMouseUp(win, obj,
																			win->mouseCurrent.position.x - lrc.left,
																			win->mouseCurrent.position.y - lrc.top,
																			win->mouseCurrent.isCtrl, win->mouseCurrent.isAlt, win->mouseCurrent.isShift,
																			win->obj->ev.thisClick);
								break;

							case WM_MOUSEWHEEL:
#ifdef WM_MOUSEHWHEEL
							case WM_MOUSEHWHEEL:
#endif
								// Signal the mouseWheel event
								*tlProcessed = true;		// Indicate we've processed this
								if (llContinue)
									llContinue = iiEventDispatch_onMouseWheel(win, obj,
																				win->mouseCurrent.position.x - lrc.left,
																				win->mouseCurrent.position.y - lrc.top,
																				win->mouseCurrent.isCtrl, win->mouseCurrent.isAlt, win->mouseCurrent.isShift,
																				win->obj->ev.thisClick,
																				win->mouseCurrent.wheelDeltaV);
								break;
						}

					} else if (llInObjectArea) {
						//////////
						// Signal the mouseMove event in the non-client area, which means negative values, or values
						// outside of the width.  For non-client areas, we translate to negative is to the left or
						// above the client area, with values extending beyond the width and height if it is in the
						// outer area
						//////


						// What was the mouse message?
						switch (m)
						{
							case WM_LBUTTONDOWN:
							case WM_RBUTTONDOWN:
							case WM_MBUTTONDOWN:
								// Signal the mouseDown event
								*tlProcessed = true;		// Indicate we've processed this
								if (llContinue)
									llContinue = iiEventDispatch_onMouseDown(win, obj,
																				win->mouseCurrent.position.x - lrcClient.left,
																				win->mouseCurrent.position.y - lrcClient.top,
																				win->mouseCurrent.isCtrl, win->mouseCurrent.isAlt, win->mouseCurrent.isShift,
																				win->obj->ev.thisClick);


								// Signal the click event
								if (llContinue)
									llContinue = iiEventDispatch_onMouseClickEx(win, obj,
																					win->mouseCurrent.position.x - lrcClient.left,
																					win->mouseCurrent.position.y - lrcClient.top,
																					win->mouseCurrent.isCtrl, win->mouseCurrent.isAlt, win->mouseCurrent.isShift,
																					win->obj->ev.thisClick);

								break;

							case WM_LBUTTONUP:
							case WM_RBUTTONUP:
							case WM_MBUTTONUP:
								// Signal the mouseUp event
								*tlProcessed = true;		// Indicate we've processed this
								if (llContinue)
									llContinue = iiEventDispatch_onMouseUp(win, obj,
																			win->mouseCurrent.position.x - lrcClient.left,
																			win->mouseCurrent.position.y - lrcClient.top,
																			win->mouseCurrent.isCtrl, win->mouseCurrent.isAlt, win->mouseCurrent.isShift,
																			win->obj->ev.thisClick);
								break;

							case WM_MOUSEWHEEL:
#ifdef WM_MOUSEHWHEEL
							case WM_MOUSEHWHEEL:
#endif
								// Signal the mouseWheel event
								*tlProcessed = true;		// Indicate we've processed this
								if (llContinue)
									llContinue = iiEventDispatch_onMouseWheel(win, obj,
																				win->mouseCurrent.position.x - lrcClient.left,
																				win->mouseCurrent.position.y - lrcClient.top,
																				win->mouseCurrent.isCtrl, win->mouseCurrent.isAlt, win->mouseCurrent.isShift,
																				win->obj->ev.thisClick,
																				win->mouseCurrent.wheelDeltaV);
								break;
						}
					}

			}


			//////////
			// Process any siblings
			//////
				if (llContinue && tlProcessSiblings)
				{
					// Begin at the next sibling
					objSib = obj->ll.nextObj;
					while (llContinue && objSib)
					{
						// Process this sibling
						llContinue = iiMouse_processMouseEvents_common(win, objSib, rc, m, true, false, tlProcessed);
						if (!llContinue)
							break;

						// Move to next sibling
						objSib = objSib->ll.nextObj;
					}
				}

		}

		// Indicate if the caller should continue
		return(llContinue);
	}




// //////////
// //
// // Process the mouse events in the non-client area for this form
// //
// //////
// 	s32 iiMouse_processMouseEvents_nonclient(SWindow* win, UINT m, WPARAM w, LPARAM l)
// 	{
// 		s32			lnResult, lnDeltaX, lnDeltaY, lnWidth, lnHeight, lnLeft, lnTop;
// 		bool		llCtrl, llAlt, llShift, llLeft, llRight, llMiddle, llCaps;
// 		SObject*	obj;
// 		RECT		lrc;
// 		POINT		pt, ptScreen;
//
//
// 		//////////
// 		// Grab our pointer
// 		//////
// 			obj = win->obj;
//
//
// 		//////////
// 		// Determine mouse button and keyboard key attributes
// 		//////
// 			iiMouse_getFlags(&llCtrl, &llAlt, &llShift, &llLeft, &llMiddle, &llRight, &llCaps);
//
//
// 		//////////
// 		// Iterate through the known objects
// 		//////
// 			pt.x = win->mouseAdjustedPosition.x;
// 			pt.y = win->mouseAdjustedPosition.y;
//
// 			// They clicked on something
// 			if (m == WM_LBUTTONDOWN)
// 			{
// 				// Close button
// 				if (PtInRect(&obj->rcClose, pt))
// 				{
// 					// Send the quit message
// 					PostQuitMessage(0);
//
// 				// Minimize button
// 				} else if (PtInRect(&obj->rcMinimize, pt)) {
// 					// Minimize the window
// 					CloseWindow(win->hwnd);
//
// 				} else {
// 					// The mouse has gone down in a nonclient area.
// 					// Note where the mouse went down in case they are beginning a move.
// 					win->mousePositionClick.x = pt.x;
// 					win->mousePositionClick.y = pt.y;
//
// 					// Get the current mouse position
// 					GetCursorPos(&ptScreen);
// 					win->mousePositionClickScreen.x = ptScreen.x;
// 					win->mousePositionClickScreen.y = ptScreen.y;
// 				}
//
// 			} else if (m == WM_MOUSEMOVE) {
// 				// The mouse is moving
// 				if (win->isMoving)
// 				{
// 					// Update to the new position
// 					// Get the current mouse position
// 					GetCursorPos(&ptScreen);
//
// 					// Determine the deltas
// 					lnDeltaX = ptScreen.x - win->mousePositionClickScreen.x;
// 					lnDeltaY = ptScreen.y - win->mousePositionClickScreen.y;
//
// 					// Position the window at that delta
// 					GetWindowRect(win->hwnd, &lrc);
//
// 					// It has moved since the last positioning
// 					SetWindowPos(win->hwnd, NULL,
// 									obj->rc.left + lnDeltaX,
// 									obj->rc.top + lnDeltaY,
// 									obj->rc.right  - obj->rc.left,
// 									obj->rc.bottom - obj->rc.top,
// 									SWP_NOSIZE | SWP_NOREPOSITION);
//
// 				} else if (win->isResizing) {
// 					// Update to the new size
//
// 				} else if (!glIsMoving && !glIsResizing) {
// 					// They may be beginning a move or resize
// 					if (llLeft)
// 					{
// 						// Did they move in a button?
// 						if (!(PtInRect(&obj->rcIcon, pt) || PtInRect(&obj->rcMove, pt) || PtInRect(&obj->rcMinimize, pt) || PtInRect(&obj->rcMaximize, pt) || PtInRect(&obj->rcClose, pt)))
// 						{
// 							// Nope.  Are they moving in a resizing arrow?
// 							if (PtInRect(&obj->rcArrowUl, pt) || PtInRect(&obj->rcArrowUr, pt) || PtInRect(&obj->rcArrowLl, pt) || PtInRect(&obj->rcArrowLr, pt))
// 							{
// 								// We are beginning a resize
// 								win->isResizing	= true;
// 								glIsResizing	= true;
// 								SetCapture(win->hwnd);
// // TODO:  write the resizing code
//
// 							} else {
// 								// We are beginning a move
// 								win->isMoving	= true;
// 								glIsMoving		= true;
// 								SetCapture(win->hwnd);
// 							}
// 						}
// 					}
// 				}
//
// 			} else if (m == WM_LBUTTONUP) {
// 				// They've released the mouse
// 				if (win->isMoving)
// 				{
// 					// We're done moving
// 					win->isMoving	= false;
// 					glIsMoving		= false;
// 					ReleaseCapture();
//
// 					// Get the current mouse position
// 					GetCursorPos(&ptScreen);
//
// 					// Determine the deltas
// 					lnDeltaX = ptScreen.x - win->mousePositionClickScreen.x;
// 					lnDeltaY = ptScreen.y - win->mousePositionClickScreen.y;
//
// 					// Position the window finally
// 					lnWidth		= obj->rc.right  - obj->rc.left;
// 					lnHeight	= obj->rc.bottom - obj->rc.top;
// 					lnLeft		= obj->rc.left   + lnDeltaX;
// 					lnTop		= obj->rc.top    + lnDeltaY;
// 					SetRect(&obj->rc, lnLeft, lnTop, lnLeft + lnWidth, lnTop + lnHeight);
//
// 					// Position the window at that delta
// 					SetWindowPos(win->hwnd, NULL, lnLeft, lnTop, lnWidth, lnHeight, SWP_NOSIZE | SWP_NOREPOSITION);
//
// 				} else if (win->isResizing) {
// 					// We're done resizing
// 					win->isResizing = false;
// 					glIsResizing	= false;
// 					ReleaseCapture();
//
// 				} else {
// 					// The mouse is simply released.  How nice. :-)
// 					win->isMoving	= false;
// 					win->isResizing = false;
// 					glIsMoving		= false;
// 					glIsResizing	= false;
// 				}
// 			}
//
//
// 		// Indicate our status
// 		lnResult = 0;
// 		return(lnResult);
// 	}




//////////
//
// Based upon the WPARAM we determine the keys, except Alt, which is
// determined by the VK_MENU key's current state.
//
//////
	void iiMouse_getFlags_wparam(WPARAM w, bool* tlCtrl, bool* tlAlt, bool* tlShift, bool* tlLeft, bool* tlMiddle, bool* tlRight, bool* tlCaps, bool* tlAnyButton)
	{
		//////////
		// Obtain from WPARAM
		//////
			*tlCtrl			= ((w & MK_CONTROL)		!= 0);
			*tlAlt			= (GetKeyState(VK_MENU)	< 0);
			*tlShift		= ((w & MK_SHIFT)		!= 0);
			*tlLeft			= ((w & MK_LBUTTON)		!= 0);
			*tlRight		= ((w & MK_RBUTTON)		!= 0);
			*tlMiddle		= ((w & MK_MBUTTON)		!= 0);
			*tlAnyButton	= (*tlLeft || *tlMiddle || *tlRight);
	}




//////////
//
// Based upon the WPARAM we determine the keys, except Alt, which is
// determined by the VK_MENU key's current state.
//
//////
	void iiMouse_getFlags_async(bool* tlCtrl, bool* tlAlt, bool* tlShift, bool* tlLeft, bool* tlMiddle, bool* tlRight, bool* tlCaps, bool* tlAnyButton)
	{
		//////////
		// Grab each one asynchronously
		//////
			*tlCtrl			= ((GetAsyncKeyState(VK_CONTROL)	& 0x8000)	!= 0);
			*tlAlt			= (GetKeyState(VK_MENU)							< 0);
			*tlShift		= ((GetAsyncKeyState(VK_SHIFT)		& 0x8000)	!= 0);
			*tlLeft			= ((GetAsyncKeyState(VK_LBUTTON)	& 0x8000)	!= 0);
			*tlMiddle		= ((GetAsyncKeyState(VK_MBUTTON)	& 0x8000)	!= 0);
			*tlRight		= ((GetAsyncKeyState(VK_RBUTTON)	& 0x8000)	!= 0);
			*tlCaps			= (GetAsyncKeyState(VK_CAPITAL)		& 0x8000)	!= 0;
			*tlAnyButton	= (*tlLeft || *tlMiddle || *tlRight);
	}




//////////
//
// Process the indicated keystroke
//
//////
	s32 iKeyboard_processMessage(SWindow* win, UINT m, WPARAM vKey, LPARAM tnScanCode)
	{
		s16			lnAsciiChar;
		u32			lnI, lnScanCode, lnObjFocusControlsCount;
		SBuilder*	objFocusControls;
		SObject*	obj;
		bool		llCtrl, llAlt, llShift, llLeft, llMiddle, llRight, llCaps, llIsAscii, llIsCAS, llIsAnyMouseButtonDown;
		u8			keyboardState[256];


		//////////
		// Grab our key states
		//////
			iiMouse_getFlags_async(&llCtrl, &llAlt, &llShift, &llLeft, &llMiddle, &llRight, &llCaps, &llIsAnyMouseButtonDown);


		//////////
		// See if it's a printable character
		//////
			lnScanCode	= (tnScanCode & 0xff000) >> 12;
			lnAsciiChar	= 0;
			GetKeyboardState(&keyboardState[0]);
			llIsAscii	= (ToAscii((UINT)vKey, lnScanCode, &keyboardState[0], (LPWORD)&lnAsciiChar, 0) >= 1);


		//////////
		// Create buffers
		//////
			objFocusControls = NULL;
			iBuilder_createAndInitialize((SBuilder**)&objFocusControls,	64);


		//////////
		// Find out which objects within has focus
		//////
			iObj_findFocusControls(win->obj, objFocusControls, true);
			lnObjFocusControlsCount = objFocusControls->populatedLength / sizeof(SObject*);
			if (lnObjFocusControlsCount == 0)
				return(0);		// Nothing to process


		//////////
		// Determine if this keystroke is only a CTRL, SHIFT, or ALT.
		//////
			llIsCAS = (vKey == VK_SHIFT || vKey == VK_CONTROL || vKey == VK_MENU);


		//////////
		// Send it to each control with focus
		//////
			for (lnI = 0; lnI < lnObjFocusControlsCount; lnI++)
			{
				// Grab this object and its buffer
				obj	= *(SObject**)(objFocusControls->data_u8 + (lnI * sizeof(SObject*)));

				// Call the appropriate handler
				if (m == WM_KEYDOWN)
				{
					// Signal the down key event
					iiEventDispatch_onKeyDown(win, obj, llCtrl, llAlt, llShift, llCaps, lnAsciiChar, (u16)vKey, llIsCAS, llIsAscii);

				} else if (m == WM_KEYUP) {
					// Signal the up key event
					iiEventDispatch_onKeyUp(win, obj, llCtrl, llAlt, llShift, llCaps, lnAsciiChar, (u16)vKey, llIsCAS, llIsAscii);
				}
			}


		//////////
		// Release the focus control list
		//////
			if (objFocusControls)
				iBuilder_freeAndRelease(&objFocusControls);


		// All done
		return(0);
	}




//////////
//
// Called to build the listing along the right side, which is a subform with
// an editbox contained within to hold the items.
//
//////
	void iVjr_createOverlayListing(SBitmap* bmp, RECT* trc)
	{
		//////////
		// Create the object
		//////
			// Create object
			gobj_splashListing = iObj_create(_OBJ_TYPE_SUBFORM, NULL);
			if (!gobj_splashListing)
				return;

			// Set the icon and border
			iObjProp_set_bitmap_direct(gobj_splashListing, _INDEX_ICON, bmpOutputIcon);
			iObjProp_set_s32_direct(gobj_splashListing, _INDEX_BORDERSTYLE, _BORDER_STYLE_FIXED);


		//////////
		// Give it a caption
		//////
			propSetCaption(gobj_splashListing, cgcSystemLog);


		//////////
		// Size and position it
		//////
			iObj_setSize(gobj_splashListing, trc->left, trc->top, trc->right - trc->left, bmp->bi.biHeight);
			gobj_splashListing->bmp = iBmp_allocate();
			iBmp_createBySize(gobj_splashListing->bmp, trc->right - trc->left, trc->bottom - trc->top, bmp->bi.biBitCount);


		//////////
		// Add the editbox
		//////
			gobj_splashListingEditbox							= iObj_addChild(_OBJ_TYPE_EDITBOX,	gobj_splashListing);
			iObj_setSize(gobj_splashListingEditbox, 0, 0, gobj_splashListing->rcClient.right - gobj_splashListing->rcClient.left, gobj_splashListing->rcClient.bottom - gobj_splashListing->rcClient.top);
			gobj_splashListingEditbox->bmp = iBmp_allocate();
			iBmp_createBySize(gobj_splashListingEditbox->bmp, gobj_splashListing->rcClient.right - gobj_splashListing->rcClient.left, gobj_splashListing->rcClient.bottom - gobj_splashListing->rcClient.top, bmp->bi.biBitCount);
			gobj_splashListingEditbox->p.font					= iFont_create(cgcFontName_defaultFixed, 8, FW_NORMAL, false, false);
			gobj_splashListingEditbox->p.sem->font				= iFont_create(cgcFontName_defaultFixed, 8, FW_NORMAL, false, false);
			iEngine_set_event(_EVENT_ONKEYDOWN, NULL, gobj_splashListingEditbox, (uptr)&iSEM_onKeyDown);
			iObjProp_set_logical_fromLogicalConstants(gobj_splashListingEditbox, _INDEX_VISIBLE, _LOGICAL_TRUE);
			systemLog											= gobj_splashListingEditbox->p.sem;
			systemLog->showEndLine								= true;
			systemLog->showCursorLine							= true;


		//////////
		// Set it visible
		//////
			iObjProp_set_logical_fromLogicalConstants(gobj_splashListing, _INDEX_VISIBLE, _LOGICAL_TRUE);
	}




//////////
//
// Called to render the listing.
//
//////
	void iVjr_renderOverlayListing(SBitmap* bmp, RECT* trc)
	{
		SThisCode*	thisCode = NULL;
		RECT		lrc;


		// Make sure our environment is sane
		if (gobj_splashListing && gobj_splashListingEditbox)
		{
			// Move to the end of the list
			iSEM_navigateToEndLine(gobj_splashListingEditbox->p.sem, gobj_splashListing);

			if (trc && gobj_splashListing->bmp)
			{
				// Render
				iObj_renderChildrenAndSiblings(gobj_splashListing, true, true, true);

				// Publish it if we can
				if (bmp)
				{
					// Publish
					SetRect(&lrc, 0, 0, gobj_splashListing->bmp->bi.biWidth, gobj_splashListing->bmp->bi.biHeight);
					iObj_publish(gobj_splashListing, &lrc, bmp, true, true, true, 0);

					// Update our bitmap
					iBmp_bitBlt(bmp, trc, gobj_splashListing->bmp);

					// Redraw it on the OS
					InvalidateRect(gSplash.hwnd, 0, false);
				}
			}
		}
	}




//////////
//
// Physically render the accomplishment
//
//////
	#define _RED	0
	#define _AMBER	1
	#define _GREEN	2
	#define _BLUE	3

	void iiVjr_renderAccomplishment(SBitmap* bmp, RECT* trc, s32 tnRAGB, cs8* tcAccomplishment, cs8* tcVersion, bool tlBold, bool tlItalic, bool tlUnderline, s32 tnAdjustAccomplishmentFontSize, s32 tnAdjustVersionFontSize)
	{
		s32			lnWidthAccomplishment;//, lnWidthVersion;
		RECT		lrc, lrc2, lrcAccomplishment, lrcVersion;
		SBgra		baseColor, leftColor, rightColor;
		SFont*		font8;
		SFont*		font9;
		COLORREF	textColor;


		//////////
		// Construct the fonts
		//////
			font8 = iFont_create(cgcFontName_default, 8 + tnAdjustVersionFontSize,			((tlBold) ? FW_BOLD : FW_NORMAL), 0,					0);
			font9 = iFont_create(cgcFontName_default, 9 + tnAdjustAccomplishmentFontSize,	((tlBold) ? FW_BOLD : FW_NORMAL), ((tlItalic) ? 1 : 0), ((tlUnderline) ? 1 : 0));


		//////////
		// Determine how big the accomplishment and version texts are
		//////
			SelectObject(bmp->hdc, font9->hfont);
			SetRect(&lrcAccomplishment, 0, 0, bmp->bi.biWidth, bmp->bi.biHeight);
			DrawText(bmp->hdc, tcAccomplishment, (int)strlen(tcAccomplishment), &lrcAccomplishment, DT_SINGLELINE | DT_LEFT | DT_CALCRECT);


		//////////
		// Compute the size of the version text
		//////
			if (tcVersion)
			{
				// There is a version
				SelectObject(bmp->hdc, font8->hfont);
				SetRect(&lrcVersion, 0, 0, bmp->bi.biWidth, bmp->bi.biHeight);
				DrawText(bmp->hdc, tcVersion, (int)strlen(tcVersion), &lrcVersion, DT_SINGLELINE | DT_LEFT | DT_CALCRECT);

			} else {
				// No version
				SetRect(&lrcVersion, 0, 0, 0, 0);
			}


		//////////
		// Build our target size rectangle
		//////
			lnWidthAccomplishment	= lrcAccomplishment.right - lrcAccomplishment.left;
//			lnWidthVersion			= lrcVersion.right - lrcVersion.left;
//			s32 lnWidth				= bmpStoplightRed->bi.biWidth + 4 + lnWidthVersion + ((lnWidthVersion != 0) ? 12 : 0) + lnWidthAccomplishment + 4;
			SetRect(&lrc, trc->left/*trc->right - lnWidth*/, trc->top, trc->right, trc->top + bmpStoplightRed->bi.biHeight);


		//////////
		// Fill it with the gradient color
		//////
			switch (tnRAGB)
			{
				case _RED:
					baseColor = iBmp_extractColorAtPoint(bmpStoplightRed, bmpStoplightRed->bi.biWidth / 2, bmpStoplightRed->bi.biHeight / 2);
					break;

				case _AMBER:
					baseColor = iBmp_extractColorAtPoint(bmpStoplightAmber, bmpStoplightAmber->bi.biWidth / 2, bmpStoplightAmber->bi.biHeight / 2);
					break;

				case _GREEN:
					baseColor = iBmp_extractColorAtPoint(bmpStoplightGreen, bmpStoplightGreen->bi.biWidth / 2, bmpStoplightGreen->bi.biHeight / 2);
					break;

				default:
				case _BLUE:
					baseColor	= iBmp_extractColorAtPoint(bmpStoplightBlue, bmpStoplightBlue->bi.biWidth / 2, bmpStoplightBlue->bi.biHeight / 2);
					break;
			}
			leftColor = iBmp_colorCombine(baseColor, whiteColor, 0.50f);
			CopyRect(&lrc2, &lrc);
			lrc2.left	+= bmpStoplightRed->bi.biWidth;
			lrc2.right	= (lrc2.right - lrc2.left) / 4;
			iBmp_fillRect(bmp, &lrc2, leftColor, whiteColor, leftColor, whiteColor, true, NULL, false);

			lrc2.left	= lrc2.right;
			lrc2.right	= lrc.right;
			rightColor	= iBmp_colorCombine(baseColor, whiteColor, 0.10f);
			iBmp_fillRect(bmp, &lrc2, whiteColor, rightColor, whiteColor, rightColor, true, NULL, false);


		//////////
		// Overlay the appropriate signal
		//////
			switch (tnRAGB)
			{
				case _RED:
					iBmp_bitBlt(bmp, &lrc, bmpStoplightRed);
					textColor = RGB(128,32,32);
					break;

				case _AMBER:
					iBmp_bitBlt(bmp, &lrc, bmpStoplightAmber);
					textColor = RGB(112,92,64);
					break;

				case _GREEN:
					iBmp_bitBlt(bmp, &lrc, bmpStoplightGreen);
					textColor = RGB(16,128,16);
					break;

				default:
				case _BLUE:
					iBmp_bitBlt(bmp, &lrc, bmpStoplightBlue);
					textColor = RGB(32,32,128);
					break;
			}


		//////////
		// Add in the version
		//////
			// Move over for the next text (either version or accomplishment)
			++lrc.top;
			lrc.left += bmpStoplightRed->bi.biWidth + 4;
			if (tcVersion)
			{
				// Draw the version
				SelectObject(bmp->hdc, font8->hfont);
				SetTextColor(bmp->hdc, textColor);
				SetBkMode(bmp->hdc, TRANSPARENT);
				DrawText(bmp->hdc, tcVersion, (int)strlen(tcVersion), &lrc, DT_SINGLELINE | DT_LEFT);
			}


		//////////
		// Add in the accomplishment
		//////
			// SEt for the accomplishment
			lrc.left = trc->right - lnWidthAccomplishment - 4;
			SelectObject(bmp->hdc, font9->hfont);
			SetTextColor(bmp->hdc, textColor);
			SetBkMode(bmp->hdc, TRANSPARENT);
			DrawText(bmp->hdc, tcAccomplishment, (int)strlen(tcAccomplishment), &lrc, DT_SINGLELINE | DT_LEFT);


		//////////
		// Draw a frame around this region so it marks the boundaries
		//////
			SetRect(&lrc, 0, 0, trc->right, trc->top + bmpStoplightRed->bi.biHeight);
			iBmp_frameRect(bmp, &lrc, blackColor, blackColor, blackColor, blackColor, false, NULL, false);


		//////////
		// Adjust the next rect down for the next one
		//////
			trc->top	+= bmpStoplightRed->bi.biHeight;
			trc->bottom	+= bmpStoplightRed->bi.biHeight;
	}





//////////
//
// Overlay the accomplishments in this release/version.
//
//////
	void iVjr_renderAccomplishments(SBitmap* bmp, RECT* trc)
	{
		RECT lrc;


		// Begin at the top
		CopyRect(&lrc, trc);

		// System log
#ifdef _LANG_EN
	const s8 cgcFormsWorking_070[]					= "Forms working (future, James 4:15)";
	const s8 cgcCompilerCompleted_065[]				= "Compiler completed (future, James 4:15)";
	const s8 cgcRunningPrograms_060[]				= "Running programs (future, James 4:15)";
	const s8 cgcVersion_058[]						= "Refactoring, 10 new functions";
	const s8 cgcVersion_057[]						= "Hernan Cano is a VJr developer";
	const s8 cgcVersion_056[]						= "Stefano D'Amico is a VJr developer";
	const s8 cgc64bitAnd32bit_055[]					= "Native 32-bit and 64-bit Versions";
	const s8 cgcShiftSpaceInNames_054[]				= "Support for Shift+Spaces in names";
	const s8 cgcInternalPropertyRefactoring_054[]	= "Internal Property refactoring";
	const s8 cgcChrtranStrtran_052[]				= "CHRTRAN() and STRTRAN()";
	const s8 cgcBugFixesMemoryLeaksRemoved_051[]	= "Bug fixes, memory leaks removed";
	const s8 cgcEditorHighlightsWord_050[]			= "Editor highlights word under cursor";
//	const s8 cgcEditorResize_047[]					= "Editor resize CTRL+ and CTRL-";
	const s8 cgcTransformPartiallySupported_043[]	= "TRANSFORM() partially supported";
	const s8 cgcTooltipsFramed_039[]				= "Tooltips framed (hover framed)";
	const s8 cgcVersion_0_70[]						= "0." "70";
	const s8 cgcVersion_0_65[]						= "0." "65";
	const s8 cgcVersion_0_60[]						= "0." "60";
	const s8 cgcVersion_0_58[]						= "0." "58";
	const s8 cgcVersion_0_57[]						= "0." "57";
	const s8 cgcVersion_0_56[]						= "0." "56";
	const s8 cgcVersion_0_55[]						= "0." "55";
	const s8 cgcVersion_0_54[]						= "0." "54";
	const s8 cgcVersion_0_52[]						= "0." "52";
	const s8 cgcVersion_0_51[]						= "0." "51";
	const s8 cgcVersion_0_50[]						= "0." "50";
	const s8 cgcVersion_0_43[]						= "0." "43";
	const s8 cgcVersion_0_39[]						= "0." "39";
#else
	#error Language not specified
#endif

		iiVjr_renderAccomplishment(bmp, &lrc, _BLUE, cgcFormsWorking_070,							cgcVersion_0_70, false, false, false, -2, 0);
		iiVjr_renderAccomplishment(bmp, &lrc, _BLUE, cgcCompilerCompleted_065,						cgcVersion_0_65, false, false, false, -2, 0);
		iiVjr_renderAccomplishment(bmp, &lrc, _BLUE, cgcRunningPrograms_060,						cgcVersion_0_60, false, false, false, -2, 0);

		iiVjr_renderAccomplishment(bmp, &lrc, _GREEN, cgcVersion_058,								cgcVersion_0_58, false, false, false, 0, 0);

		iiVjr_renderAccomplishment(bmp, &lrc, _BLUE, cgcVersion_057,								cgcVersion_0_57, false, false, false, -2, 0);
		iiVjr_renderAccomplishment(bmp, &lrc, _BLUE, cgcVersion_056,								cgcVersion_0_56, false, false, false, -2, 0);
		iiVjr_renderAccomplishment(bmp, &lrc, _GREEN, cgc64bitAnd32bit_055,							cgcVersion_0_55, false, false, false, -2, 0);
		iiVjr_renderAccomplishment(bmp, &lrc, _GREEN, cgcShiftSpaceInNames_054,						cgcVersion_0_54, false, false, false, -2, 0);
		iiVjr_renderAccomplishment(bmp, &lrc, _GREEN, cgcInternalPropertyRefactoring_054,			cgcVersion_0_54, false, false, false, -2, 0);
		iiVjr_renderAccomplishment(bmp, &lrc, _GREEN, cgcChrtranStrtran_052,						cgcVersion_0_52, false, false, false, -2, 0);
		iiVjr_renderAccomplishment(bmp, &lrc, _GREEN, cgcBugFixesMemoryLeaksRemoved_051,			cgcVersion_0_51, false, false, false, -2, 0);
		iiVjr_renderAccomplishment(bmp, &lrc, _GREEN, cgcEditorHighlightsWord_050,					cgcVersion_0_50, false, false, false, -2, 0);

// Some work still needed:
		iiVjr_renderAccomplishment(bmp, &lrc, _AMBER, cgcTransformPartiallySupported_043,			cgcVersion_0_43, false, true, false, -1, 0);
		iiVjr_renderAccomplishment(bmp, &lrc, _AMBER, cgcTooltipsFramed_039,						cgcVersion_0_39, false, true, false, -1, 0);

//		iiVjr_renderAccomplishment(bmp, &lrc, _GREEN, "UI redesign geared toward debugger",			(s8*)"0.50", false, false, false, -2, 0);
//		iiVjr_renderAccomplishment(bmp, &lrc, _GREEN, "Editor development",							(s8*)"0.49", false, false, false, -2, 0);
//		iiVjr_renderAccomplishment(bmp, &lrc, _GREEN, "Editor line numbers, breakpoints",			(s8*)"0.48", false, false, false, -2, 0);
//		iiVjr_renderAccomplishment(bmp, &lrc, _GREEN, cgcEditorResize_047,							(s8*)"0.47", false, false, false, -2, 0);
//		iiVjr_renderAccomplishment(bmp, &lrc, _GREEN, "Casks",										(s8*)"0.46", false, true, false, -2, 0);
//		iiVjr_renderAccomplishment(bmp, &lrc, _GREEN, "Syntax highlighting",						(s8*)"0.45", false, true, false, -2, 0);
// 		iiVjr_renderAccomplishment(bmp, &lrc, _GREEN, "Tabs expanded, mouse wheel",					(s8*)"0.44", false, true, false, -2, 0);
//		iiVjr_renderAccomplishment(bmp, &lrc, _GREEN, "PADC(), PADL(), PADR()",						(s8*)"0.43", false, true, false, -2, 0);
// 		iiVjr_renderAccomplishment(bmp, &lrc, _GREEN, "OCCURS(), OCCURSC()",						(s8*)"0.43", false, true, false, -2, 0);
// 		iiVjr_renderAccomplishment(bmp, &lrc, _GREEN, "AT(), ATC(), RAT(), RATC()",					(s8*)"0.43", false, true, false, -2, 0);
// 		iiVjr_renderAccomplishment(bmp, &lrc, _GREEN, "Bugfix on function parsing",					(s8*)"0.42", false, true, false, -2, 0);
// 		iiVjr_renderAccomplishment(bmp, &lrc, _GREEN, "System log",									(s8*)"0.41", false, true, false, -2, 0);
//		iiVjr_renderAccomplishment(bmp, &lrc, _GREEN, "Focus highlight border bugfix",				(s8*)"0.41", false, true, false, -2, 0);
//		iiVjr_renderAccomplishment(bmp, &lrc, _GREEN, "Memory leak bug fixes",						(s8*)"0.41", false, true, false, -2, 0);
// 		iiVjr_renderAccomplishment(bmp, &lrc, _GREEN, "Sound support",								(s8*)"0.40", false, true, false, -2, 0);
//		iiVjr_renderAccomplishment(bmp, &lrc, _GREEN, "Focus highlight border",						(s8*)"0.39", false, true, false, -2, 0);
// 		iiVjr_renderAccomplishment(bmp, &lrc, _GREEN, "_screen editable",							(s8*)"0.39", false, true, false, -2, 0);
//		iiVjr_renderAccomplishment(bmp, &lrc, _GREEN, "MinGW GCC 4.8.1 and CodeLite",				(s8*)"0.38", false, true, false, -2, 0);
	}




//////////
//
// Called to duplicate the datum from the variable.
//
//////
	void iDatum_duplicate(SDatum* datumDst, SVariable* varSrc)
	{
		// Make sure our environment is sane
		if (datumDst && varSrc && varSrc->varType == _VAR_TYPE_CHARACTER && varSrc->value.data_u8 && varSrc->value.length > 0)
			iDatum_duplicate(datumDst, varSrc->value.data_u8, varSrc->value.length);
	}
