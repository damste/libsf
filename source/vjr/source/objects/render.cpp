//////////
//
// /libsf/source/vjr/source/objects/render.cpp
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
// Copyright (c) 2014-2017 by Rick C. Hodgin
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
// Renders an empty.  However, empty objects are not actually rendered.
// But they serve as placeholders for anything contained within.
//
//////
	u32 iSubobj_renderEmpty(SObject* empty)
	{
// 		SWindow*	win;
// 		SObject*	objRoot;


		logfunc(__FUNCTION__);
		//////////
		// Indicate we're no longer dirty, that we have everything rendered, but it needs publishing
		//////
			empty->isDirtyRender	= false;
			empty->isDirtyPublish	= true;
			return(0);		// Indicate that nothing was rendered which will affect the screen
	}




//////////
//
// Renders the form.
//
// Note:  The object rendering is independent of the publication of the constructed
//        bitmap.  The render operation only populates the bit buffer.  It will be
//        published at a later time, if indeed it is visible, however, it can after
//        rendering be re-directed to some other source, a disk file, or over a
//        network resource.
//
//////
	u32 iSubobj_renderForm(SObject* obj)
	{
		bool		llStatusBar, llStatus, llExclusive, llTalk;
		s32			lnWorkArea, lnError;
		u32			lnPixelsRendered;
		RECT		lrc, lrc2, lrc3;
		SBgra		backColor, borderColor, nwRgba, neRgba, swRgba, seRgba;
		COLORREF	saveColor;
		int			saveBkMode;
		HGDIOBJ		saveFont;
		s8*			lcTagName;
		SBitmap*	bmp;
		SWorkArea*	dbf;
		SWorkArea*	dbc;
		s8			buffer[_MAX_FNAME * 2];
		s8			bufferTag[80];
		s8			bufferTagName[64];


		// Make sure our environment is sane
		logfunc(__FUNCTION__);
		lnPixelsRendered = 0;
		if (obj && obj->isRendered)
		{
			//////////
			// If we need re-rendering, re-render
			//////
				// The entire bmp
				SetRect(&lrc, 0, 0, obj->bmp->bi.biWidth, obj->bmp->bi.biHeight);

				// Grab the colors
				borderColor = propBorderColor(obj);
				backColor	= propBackColor(obj);
				nwRgba		= propNwRgba(obj);
				neRgba		= propNeRgba(obj);
				swRgba		= propSwRgba(obj);
				seRgba		= propSeRgba(obj);

				// Do we need to redraw?  Or can we just copy?
				if (obj->isDirtyRender)
				{

					//////////
					// Frame it
					//////
						if (!obj->bc || !iBmp_isValidCache(&obj->bc, nwRgba.color, neRgba.color, swRgba.color, seRgba.color, obj->rc.right - obj->rc.left, obj->rc.bottom - obj->rc.top, obj->bmp->bi.biWidth, obj->bmp->bi.biHeight, 0, 0, 0, 0, 0, 0))
						{
							// The bitmap cache is no longer valid
							iBmp_deleteCache(&obj->bc);

							// Draw the window border
							if (propBorderStyle(obj) != _BORDER_STYLE_NONE)		iBmp_fillRect(obj->bmp, &lrc, nwRgba, neRgba, swRgba, seRgba, true, &obj->rcClient,	true);
							else												iBmp_fillRect(obj->bmp, &lrc, nwRgba, neRgba, swRgba, seRgba, true, NULL,			false);

							// Apply a dappling
							iBmp_dapple(obj->bmp, bmpDapple1, bmpDapple1Tmp, 215.0f, 10);

							// Save the cache
							iBmp_createCache(&obj->bc, obj->bmp, nwRgba.color, neRgba.color, swRgba.color, seRgba.color, obj->rc.right - obj->rc.left, obj->rc.bottom - obj->rc.top, obj->bmp->bi.biWidth, obj->bmp->bi.biHeight, 0, 0, 0, 0, 0, 0, true);

						} else {
							// Copy everything over from the cache
							memcpy(obj->bmp->bd, obj->bc->bmpCached->bd, obj->bc->bmpCached->bi.biSizeImage);
						}

						// Frame it
						iBmp_frameRect(obj->bmp, &lrc, borderColor, borderColor, borderColor, borderColor, false, NULL, false);

						// Draw the client area
						bmp = bmpVjrIcon;
						SetRect(&lrc2, 8, bmp->bi.biHeight + 2, lrc.right - bmp->bi.biHeight - 2, lrc.bottom - bmp->bi.biHeight - 1);
						if (propBackStyle(obj) == _BACK_STYLE_OPAQUE)
							iBmp_fillRect(obj->bmp, &lrc2, backColor, backColor, backColor, backColor, false, NULL, false);

						// Put a border around the client area
						if (propBorderStyle(obj) != _BORDER_STYLE_NONE)
						{
							InflateRect(&lrc2, 1, 1);
							iBmp_frameRect(obj->bmp, &lrc2, borderColor, borderColor, borderColor, borderColor, false, NULL, false);
						}


					//////////
					// Copy to prior rendered bitmap
					//////
						// Make sure our bmpPriorRendered exists
						obj->bmpPriorRendered = iBmp_verifyCopyIsSameSize(obj->bmpPriorRendered, obj->bmp);

						// Copy to the prior rendered version
						memcpy(obj->bmpPriorRendered->bd, obj->bmp->bd, obj->bmpPriorRendered->bi.biSizeImage);
						// Right now, we can use the bmpPriorRendered for a fast copy rather than 

				} else {
					// Render from its prior rendered version
					lnPixelsRendered += iBmp_bitBlt(obj->bmp, &lrc, obj->bmpPriorRendered);
				}


			//////////
			// Reset the area at the bottom
			//////
				// Render along the bottom
				SetRect(&lrc2,	8 + bmpArrowLl->bi.biWidth + 8,
								lrc.bottom - bmpArrowLr->bi.biHeight + 2,
								lrc.right - 8 - bmpArrowLr->bi.biHeight - 8,
								lrc.bottom - 4);

				// Render the background
				iBmp_fillRect(obj->bmp, &lrc2, swRgba, seRgba, swRgba, seRgba, true);

				// Set colors
				saveFont	= SelectObject(obj->bmp->hdc, gsFontDefaultFixedPoint9->hfont);
				saveColor	= SetTextColor(obj->bmp->hdc, RGB(whiteColor.red, whiteColor.grn, whiteColor.blu));
				saveBkMode	= SetBkMode(obj->bmp->hdc, TRANSPARENT);


			//////////
			// If SET STATUSBAR is on, update the status
			//////
				llStatusBar	= propGet_settings_StatusBar(_settings);
				llStatus	= propGet_settings_Status(_settings);
				llExclusive = propGet_settings_Exclusive(_settings);
				llTalk		= propGet_settings_Talk(_settings);

				if (llStatus)
					_asm nop;

				// No tag
				sprintf(bufferTag, "");

				// Statusbar takes precedence over status
				if (llStatusBar || llStatus)
				{
					// Render the specific entry
					if (llStatusBar)
					{
						// SET STATUSBAR is on
						if ((lnWorkArea = iDbf_get_workArea_current()) >= 0)
						{
							// Draw the name
							SetRect(&lrc3, lrc2.left + 4, lrc2.top + 1, lrc2.left + ((lrc2.right - lrc2.left) / 5), lrc2.bottom - 1);
							if ((dbf = iDbf_get_workArea_current_wa()) && dbf && dbf->isUsed)
							{
								// There is a work area
								if (iDbf_hasDbc(lnWorkArea, &dbc, &lnError) && lnError == 0 && dbc && dbc->isUsed)
								{
									// Alias (dbc!table)
									sprintf(buffer, "%s (%s!%s)", dbf->alias, dbc->alias, dbc->alias);

								} else {
									// Alias (pathname)
									sprintf(buffer, "%s (%s)", dbf->alias, dbf->tablePathname);
								}
								DrawText(obj->bmp->hdc, buffer, strlen(buffer), &lrc3, DT_LEFT | DT_VCENTER);

								// Recno / reccount
								SetRect(&lrc3, lrc3.right + 4, lrc2.top + 1, lrc3.right + ((lrc2.right - lrc2.left) / 8), lrc2.bottom - 1);
								if (dbf->currentRecord == 0)
								{
									// BOF()
									sprintf(buffer, "Record: BOF() / %u (-%%)", dbf->header.records);

								} else if (dbf->currentRecord > dbf->header.records) {
									// EOF()
									sprintf(buffer, "Record: EOF() / %u (---%%)", dbf->header.records);

								} else {
									// On a record
									sprintf(buffer, "Record: %u / %u (%.0f%%)", dbf->currentRecord, dbf->header.records, (100.0f * (f32)dbf->currentRecord / (f32)dbf->header.records));
								}
								DrawText(obj->bmp->hdc, buffer, strlen(buffer), &lrc3, DT_LEFT | DT_VCENTER);

								// Shared or exclusive
								SetRect(&lrc3, lrc3.right + 4, lrc2.top + 1, lrc2.right, lrc2.bottom - 1);
								if (dbf->isExclusive)		sprintf(buffer, "%s", cgc_exclusive);
								else						sprintf(buffer, "%s", cgc_shared);
								DrawText(obj->bmp->hdc, buffer, strlen(buffer), &lrc3, DT_LEFT | DT_VCENTER);

								// Update the tag
								lcTagName = iDbf_get_tagName(dbf, bufferTagName);
								if (dbf->isCdx)
								{
									// Has a cdx
									sprintf(bufferTag, "| CDX%s%s ", ((lcTagName) ? ":" : ""), ((lcTagName) ? lcTagName : ""));

								} else if (dbf->isSdx) {
									// Has an sdx
									sprintf(bufferTag, "| SDX%s%s ", ((lcTagName) ? ":" : ""), ((lcTagName) ? lcTagName : ""));

								} else if (dbf->isIndexLoaded) {
									// Has an idx
									sprintf(bufferTag, "| IDX ");
								}

							} else {
								// Just a selected work area
								sprintf(buffer, "Work area %d", lnWorkArea);
								DrawText(obj->bmp->hdc, buffer, strlen(buffer), &lrc3, DT_LEFT | DT_VCENTER);
							}
						}

					} else if (llStatus) {
						// SET STATUS is on
						sprintf(buffer, "SET STATUS ON -- Temporary Placeholder");
						DrawText(obj->bmp->hdc, buffer, strlen(buffer), &lrc2, DT_LEFT | DT_VCENTER);
					}

					// Talk, Exclusive
					sprintf(buffer, "%s| TALK:%s | EXCLUSIVE:%s |",
									bufferTag,
									((llTalk)		? cgc_on : cgc_off),
									((llExclusive)	? cgc_on : cgc_off));
					DrawText(obj->bmp->hdc, buffer, strlen(buffer), &lrc2, DT_RIGHT | DT_VCENTER);
				}

				// Restore colors
				SetTextColor(obj->bmp->hdc,	saveColor);
				SetBkMode(obj->bmp->hdc,	saveBkMode);
				SelectObject(obj->bmp->hdc,	saveFont);


			//////////
			// Indicate we're no longer dirty, that we have everything rendered, but it needs publishing
			//////
				obj->isDirtyRender	= false;
				obj->isDirtyPublish	= true;
		}


		// Indicate how many pixels were drawn
		return(lnPixelsRendered);
	}




//////////
//
// Renders the subform.
//
//////
	u32 iSubobj_renderSubform(SObject* obj)
	{
		u32		lnPixelsRendered;
		bool	llIsFocusSubform;
		SBgra	backColor, borderColor, nwRgba, neRgba, swRgba, seRgba;
		RECT	lrc, lrc2;


		// Make sure our environment is sane
		logfunc(__FUNCTION__);
		lnPixelsRendered = 0;
		if (obj && obj->isRendered && obj->rc.right > 0 && obj->rc.bottom > 0 && obj->rc.right >= obj->rc.left && obj->rc.bottom >= obj->rc.bottom && obj->rc.right - obj->rc.left < 4400 && obj->rc.bottom - obj->rc.top < 4400)
		{
			// Grab our colors
			backColor	= propBackColor(obj);
			borderColor	= propBorderColor(obj);
			nwRgba		= propNwRgba(obj);
			neRgba		= propNeRgba(obj);
			swRgba		= propSwRgba(obj);
			seRgba		= propSeRgba(obj);

			//////////
			// If we need re-rendering, re-render
			//////
				// The entire bmp
				SetRect(&lrc, 0, 0, obj->bmp->bi.biWidth, obj->bmp->bi.biHeight);

				// Do we need to redraw?  Or can we just copy?
				if (obj->isDirtyRender)
				{
					//////////
					// Determine if a control on this subform has focus
					//////
						llIsFocusSubform = iObj_focus_descentCheck(obj, true, false);
						if (llIsFocusSubform)
						{
							// This subform has focus
							nwRgba.color = nwColor_focus.color;
							neRgba.color = neColor_focus.color;
							swRgba.color = swColor_focus.color;
							seRgba.color = seColor_focus.color;
						}


					//////////
					// Frame it
					//////
						if (!obj->bc || !iBmp_isValidCache(&obj->bc, nwRgba.color, neRgba.color, swRgba.color, seRgba.color, obj->rc.right - obj->rc.left, obj->rc.bottom - obj->rc.top, obj->bmp->bi.biWidth, obj->bmp->bi.biHeight, (u32)llIsFocusSubform, 0, 0, 0, 0, 0))
						{
							// The bitmap cache is no longer valid
							iBmp_deleteCache(&obj->bc);

							// Draw the window border
							if (propBackStyle(obj) == _BACK_STYLE_OPAQUE)
							{
								// Render the subform and client area
								iBmp_fillRect(obj->bmp, &lrc, nwRgba, neRgba, swRgba, seRgba, true, &obj->rcClient, true);
								
								// Make the client area white
								iBmp_fillRect(obj->bmp, &obj->rcClient, backColor, backColor, backColor, backColor, false, NULL, false);

							} else {
								// Render the subform
								iBmp_fillRect(obj->bmp, &lrc, nwRgba, neRgba, swRgba, seRgba, true, NULL, false);
							}

							// Apply a dappling
							iBmp_dapple(obj->bmp, bmpDapple1, bmpDapple1Tmp, 215.0f, 33);

							// Save the cache
							iBmp_createCache(&obj->bc, obj->bmp, nwRgba.color, neRgba.color, swRgba.color, seRgba.color, obj->rc.right - obj->rc.left, obj->rc.bottom - obj->rc.top, obj->bmp->bi.biWidth, obj->bmp->bi.biHeight, (u32)llIsFocusSubform, 0, 0, 0, 0, 0, true);

						} else {
							// Copy everything over from the cache
							memcpy(obj->bmp->bd, obj->bc->bmpCached->bd, obj->bc->bmpCached->bi.biSizeImage);
						}

						// Frame the client area
						if (propBorderStyle(obj) != _BORDER_STYLE_NONE)
						{
							CopyRect(&lrc2, &obj->rcClient);
							InflateRect(&lrc2, 1, 1);
							lrc2.left	= -1;
							lrc2.bottom	= obj->bmp->bi.biHeight + 1;
							iBmp_frameRect(obj->bmp, &lrc2,	borderColor, borderColor, borderColor, borderColor, false, NULL, false);
							lrc.left	= -1;
							lrc.bottom	= obj->bmp->bi.biHeight + 1;
							iBmp_frameRect(obj->bmp, &lrc,	borderColor, borderColor, borderColor, borderColor, false, NULL, false);
						}


					//////////
					// Copy to prior rendered bitmap
					//////
						// Make sure our bmpPriorRendered exists
						obj->bmpPriorRendered = iBmp_verifyCopyIsSameSize(obj->bmpPriorRendered, obj->bmp);

						// Copy to the prior rendered version
						memcpy(obj->bmpPriorRendered->bd, obj->bmp->bd, obj->bmpPriorRendered->bi.biSizeImage);
						// Right now, we can use the bmpPriorRendered for a fast copy rather than 

				} else {
					// Render from its prior rendered version
					lnPixelsRendered += iBmp_bitBlt(obj->bmp, &lrc, obj->bmpPriorRendered);
				}


			//////////
			// Indicate we're no longer dirty, that we have everything rendered, but it needs publishing
			//////
				obj->isDirtyRender = false;
				obj->isDirtyPublish	= true;
		}

		// Indicate how many pixels were drawn
		return(lnPixelsRendered);
	}




//////////
//
// Renders the carousel.  Note that carousels are not normally displayed.  The only time
// they'll be displayed by their rendered nature below is if they do not possess any riders.
//
// 		carouselFrameColor					= { rgba(94, 94, 128, 255) };			// Purleish-gray
// 		carouselBackColor					= { rgba(255, 255, 255, 255) };			// White
// 		carouselTabBackColor				= { rgba(255, 255, 255, 255) };			// White
// 		carouselTabForeColor				= { rgba(64, 64, 88, 255) };			// Darker purpleish-gray
// 		carouselTabForeColorHighlight		= { rgba(32, 32, 44, 255) };			// Darkest purpleish-gray
//
// Note:  Carousel Riders each have one child object which is the thing they convey.
// Note:  However, only one object per rider at a time can be visible.
//
//////
	u32 iSubobj_renderCarousel(SObject* obj)
	{
		s32						lnI, lnWidth, lnAlignment, lnCount, lnLeft, lnCenter, lnSize;
		u32						lnPixelsRendered, lnSha1;
		bool					llBorder, llOrientDown, llCloseable, llVisible, llTitleBar;
		SBgra					nwRgba, neRgba, swRgba, seRgba, frameColor;
		RECT					lrc, lrc2, lrc3, lrc4;
		SObjCarouselTabData*	thisTab;
		SVariable*				varTabText;
		SVariable*				varTabText_riderActive;
		SObject*				objRider;
		SObject*				objRider_visible;


		// Make sure our environment is sane
		logfunc(__FUNCTION__);
		lnPixelsRendered = 0;
		if (obj && obj->isRendered)
		{

			//////////
			// If we need re-rendering, re-render
			//////
				// The entire bmp
				SetRect(&lrc, 0, 0, obj->bmp->bi.biWidth, obj->bmp->bi.biHeight);

				// Re-render
				if (obj->isDirtyRender)
				{

					//////////
					// Frame it
					//////
						// Grab colors
						nwRgba = propNwRgba(obj);
						neRgba = propNeRgba(obj);
						swRgba = propSwRgba(obj);
						seRgba = propSeRgba(obj);


					//////////
					// Find out how many riders there are, and the size of their texts.
					/////
						SelectObject(obj->bmp->hdc, obj->p.font->hfont);
						for (objRider = obj->firstChild, lnWidth = 0, lnCount = 0, objRider_visible = NULL; objRider; objRider = objRider->ll.nextObj)
						{
							// Is it a rider?
							if (objRider->objType == _OBJ_TYPE_RIDER && propIsEnabled(objRider) && (varTabText = propRiderTab(objRider)) && varTabText->value._data && varTabText->value.length >= 1)
							{
								//////////
								// Increase our count
								//////
									++lnCount;


								//////////
								// Determine the raw text size
								//////
									SetRect(&lrc3, 0, 0, 0, 0);
									DrawText(obj->bmp->hdc, varTabText->value.data_s8, varTabText->value.length, &lrc3, DT_CALCRECT);


								//////////
								// Increase the width
								//////
									// Spacer between items
									lnWidth += ((lnWidth != 0) ? 4 : 0);

									// 2 border + 4 margin + text width + 4 margin + (close icon if closeable + 4 margin) + 2 border
									lnWidth += 2 + 4 + (lrc3.right - lrc3.left) + 4 + ((propRiderTabCloseable(objRider)) ? bmpCarouselRiderTabClose->bi.biWidth + 4 : 0) + 2;

							}

							// Is this rider the first visible one?
							if (!objRider_visible && propIsVisible(objRider))
							{
								// Store it for comparison with other content
								objRider_visible		= objRider;
								varTabText_riderActive	= varTabText;
								lnSha1					= sha1_computeAs_u32(varTabText);
							}
						}


					//////////
					// Make sure we have enough tabs space allocated
					//////
						// Make sure we have a pointer
						if (!obj->p.rcTabs)
							iBuilder_createAndInitialize(&obj->p.rcTabs, -1);

						// And that it is big enough
						lnSize = lnCount * sizeof(SObjCarouselTabData);
						iBuilder_verifySizeForNewBytes(obj->p.rcTabs, lnSize);
						obj->p.rcTabs->populatedLength = lnSize;


					//////////
					// Determine if a control on this carousel has focus
					//////
// TODO:  We need a way to determine if the focus of a sub-tab has changed... it should be by building a string expression, processing a SHA1 on it, and then using that as well
						if (true/*Force a render every time for now ... !obj->bc || !iBmp_isValidCache(&obj->bc, nwRgba.color, neRgba.color, swRgba.color, seRgba.color, obj->rc.right - obj->rc.left, obj->rc.bottom - obj->rc.top, obj->bmp->bi.biWidth, obj->bmp->bi.biHeight, (u32)objRider_visible, (u32)varTabText_riderActive, varTabText_riderActive->value._data, varTabText_riderActive->value.length, lnSha1, 0)*/)
						{

							// The bitmap cache is no longer valid
							iBmp_deleteCache(&obj->bc);


							//////////
							// Draw the default background, and apply a dappling
							//////
								iBmp_fillRect(obj->bmp, &lrc, nwRgba, neRgba, swRgba, seRgba, true, &obj->rcClient, true);
								iBmp_dapple(obj->bmp, bmpDapple1, bmpDapple1Tmp, 215.0f, 10);


							//////////
							// Overlay the frame
							//////
								llTitleBar	= propTitleBar(obj);
								llBorder	= (propBorderStyle(obj) != _BORDER_STYLE_NONE);
								if (llBorder)
								{
									// Render the border
									CopyRect(&lrc2, &obj->rcClient);
									InflateRect(&lrc2, 1, 1);
									iBmp_frameRect(obj->bmp, &lrc2, carouselFrameColor, carouselFrameColor, carouselFrameColor, carouselFrameColor, false, NULL, false);
									InflateRect(&lrc2, 1, 1);
									iBmp_frameRect(obj->bmp, &lrc2, carouselFrameColor, carouselFrameColor, carouselFrameColor, carouselFrameColor, false, NULL, false);
								}


							//////////
							// Allocate a bitmap
							// Note:  The bitmap is always allocated and rendered horizontally as though it were on the bottom
							//////
								if (!obj->p.bmpTabs || obj->p.bmpTabs->bi.biWidth != lnWidth)
								{

									//////////
									// Delete the existing bitmap (if any)
									//////
										if (obj->p.bmpTabs)
											iBmp_delete(&obj->p.bmpTabs, true, true);


									//////////
									// Create a new bitmap
									//////
										obj->p.bmpTabs = iBmp_allocate();
										if (obj->p.bmpTabs)
											iBmp_createBySize(obj->p.bmpTabs, lnWidth, bmpArrowUl->bi.biWidth + 2, 24);

								}


							//////////
							// Render the tabs
							//////
								if (obj->p.bmpTabs)
								{
									// Set the font
									SelectObject(obj->p.bmpTabs->hdc, obj->p.font->hfont);


									//////////
									// Initially populate with the entire strip with the transparent color
									//////
										iBmp_fillRect(obj->p.bmpTabs, &lrc3, maskColor, maskColor, maskColor, maskColor, false, NULL, false);


									//////////
									// Determine how to draw
									//////
										lnAlignment = propAlignment(obj);
										switch (lnAlignment)
										{
											case _ALIGNMENT_RIGHT:
											case _ALIGNMENT_TOP:
												llOrientDown = true;
												break;

											default:
//											case _ALIGNMENT_LEFT:
// 											case _ALIGNMENT_BOTTOM:
												llOrientDown = false;
												break;
										}


									//////////
									// Iterate through each rider
									//////
										thisTab = (SObjCarouselTabData*)obj->p.rcTabs->buffer;
										for (lnI = 0, objRider = obj->firstChild, lnLeft = 0; objRider; lnI++, objRider = objRider->ll.nextObj)
										{
											// Is it a rider?
											if (objRider->objType == _OBJ_TYPE_RIDER && propIsEnabled(objRider) && (varTabText = propRiderTab(objRider)) && varTabText->value._data && varTabText->value.length >= 1)
											{

												//////////
												// Determine the raw text size
												//////
													SetRect(&lrc3, 0, 0, 0, 0);
													DrawText(obj->p.bmpTabs->hdc, varTabText->value.data_s8, varTabText->value.length, &lrc3, DT_CALCRECT);


												//////////
												// Render the appropriate rectangle
												//////
													// 2 border + 4 margin + text width + 4 margin + (close icon if closeable + 4 margin) + 2 border
													llCloseable	= propRiderTabCloseable(objRider);
													lnWidth		= 2 + 4 + (lrc3.right - lrc3.left) + 4 + ((llCloseable) ? bmpCarouselRiderTabClose->bi.biWidth + 4 : 0) + 2;
													SetRect(&lrc3, lnLeft, 0, lnLeft + lnWidth, obj->p.bmpTabs->bi.biHeight);


												//////////
												// Determine the orientation
												//////
													// Border
													llVisible = propIsVisible(objRider);
													if (llOrientDown)
													{
														//////////
														// Tab looks like this:  +-------------+
														//                       |x  file.prg  |
														//                       |             |
														//////
															SetRect(&lrc4, lrc3.left + 2, lrc3.top + 2, lrc3.right - 2, lrc3.bottom - 1);


													} else {

														//////////
														//                       |             |
														// Tab looks like this:  |x  file.prg  |
														//                       +-------------+
														//////
															SetRect(&lrc4, lrc3.left + 2, lrc3.top + 1, lrc3.right - 2, lrc3.bottom - 2);

													}


												//////////
												// Store this rectangle for future mouse reference
												//////
													thisTab->rider			= objRider;
													thisTab->isCloseable	= llCloseable;
													CopyRect(&thisTab->rc, &lrc4);


												//////////
												// Determine our color
												//////
													if (llVisible)		frameColor = carouselFrameColor;			// Active tab
													else				frameColor = carouselFrameInactiveColor;	// Inactive tab


												//////////
												// Frame it
												//////
													iBmp_frameRect(obj->p.bmpTabs, &lrc3, frameColor, frameColor, frameColor, frameColor, false, NULL, false);
													InflateRect(&lrc3, -1, -1);
													iBmp_frameRect(obj->p.bmpTabs, &lrc3, frameColor, frameColor, frameColor, frameColor, false, NULL, false);


												//////////
												// Fill it
												//////
													iBmp_fillRect(obj->p.bmpTabs, &lrc4, carouselTabBackColor, carouselTabBackColor, carouselTabBackColor, carouselTabBackColor, false, NULL, false);

													// Is the mouse is over this tab right now, actively?
												     if (thisTab->isMouseOver)
														 iBmp_colorize(obj->p.bmpTabs, &lrc4, colorMouseOver, false, 0.25f);


												//////////
												// Render the text toward the right
												//////
													SetTextColor(obj->p.bmpTabs->hdc, RGB(carouselTabForeColor.red, carouselTabForeColor.grn, carouselTabForeColor.blu));
													SetBkMode(obj->p.bmpTabs->hdc, TRANSPARENT);
													lrc4.right -= 4;		// Margin between right border and text
													DrawText(obj->p.bmpTabs->hdc, varTabText->value.data_s8, varTabText->value.length, &lrc4, DT_RIGHT | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);


												//////////
												// Close button
												//////
													if (llCloseable)
													{
														lnCenter = ((lrc4.bottom + lrc4.top) / 2);
														SetRect(&lrc4, lrc4.left + 2, lnCenter - (bmpCarouselRiderTabClose->bi.biHeight / 2), lrc4.left + 2 + bmpCarouselRiderTabClose->bi.biWidth, lnCenter + (bmpCarouselRiderTabClose->bi.biHeight / 2));
														InflateRect(&lrc4, 3, 3);
														if (thisTab->isMouseOverClose)
														{
															iBmp_colorize(obj->p.bmpTabs, &lrc4, colorMouseOver, false, 0.25f);
															iBmp_frameRect(obj->p.bmpTabs, &lrc4, frameColor, frameColor, frameColor, frameColor, false, NULL, false);
														}
														CopyRect(&thisTab->rcClose, &lrc4);

														InflateRect(&lrc4, -3, -3);
														iBmp_bitBltMask(obj->p.bmpTabs, &lrc4, bmpCarouselRiderTabClose);
													}


												//////////
												// Move for the next one
												//////
													lnLeft += lnWidth + 4;
													++thisTab;
											}
										}

								}


							//////////
							// Overlay the tabs
							//////
								switch (lnAlignment)
								{
									case _ALIGNMENT_RIGHT:
										SetRect(&lrc, obj->rcClient.right, obj->rcClient.top, obj->bmp->bi.biWidth, obj->rcClient.bottom);
										iBmp_bitBlt_rotated(obj->bmp, &lrc, obj->p.bmpTabs, 90);
										break;

									case _ALIGNMENT_TOP:
										if (llTitleBar)		SetRect(&lrc, obj->rcClient.left, bmpArrowUl->bi.biHeight, obj->rcClient.right, bmpArrowUl->bi.biHeight + obj->p.bmpTabs->bi.biHeight);
										else				SetRect(&lrc, obj->rcClient.left, 0, obj->rcClient.right, obj->rcClient.top);
										iBmp_bitBlt(obj->bmp, &lrc, obj->p.bmpTabs);
										break;

									case _ALIGNMENT_LEFT:
										SetRect(&lrc, 0, obj->rcClient.top, obj->p.bmpTabs->bi.biHeight, obj->rcClient.bottom - 1);
										iBmp_bitBlt_rotated(obj->bmp, &lrc, obj->p.bmpTabs, 270);
										break;

									default:
									case _ALIGNMENT_BOTTOM:
										SetRect(&lrc, obj->rcClient.left, obj->rcClient.bottom, obj->rcClient.right, obj->bmp->bi.biHeight);
										iBmp_bitBlt(obj->bmp, &lrc, obj->p.bmpTabs);
										break;
								}

								// Copy for later reference
								CopyRect(&obj->rcExtra, &lrc);


							//////////
							// Save the cache
							//////
								iBmp_createCache(&obj->bc, obj->bmp, nwRgba.color, neRgba.color, swRgba.color, seRgba.color, obj->rc.right - obj->rc.left, obj->rc.bottom - obj->rc.top, obj->bmp->bi.biWidth, obj->bmp->bi.biHeight, (u32)objRider_visible, (u32)varTabText_riderActive, (u32)varTabText_riderActive->value._data, varTabText_riderActive->value.length, lnSha1, 0, true);

						} else {
							// Copy everything over from the cache
							memcpy(obj->bmp->bd, obj->bc->bmpCached->bd, obj->bc->bmpCached->bi.biSizeImage);
						}


					//////////
					// Copy to prior rendered bitmap
					//////
						// Make sure our bmpPriorRendered exists
						obj->bmpPriorRendered = iBmp_verifyCopyIsSameSize(obj->bmpPriorRendered, obj->bmp);

						// Copy to the prior rendered version
						memcpy(obj->bmpPriorRendered->bd, obj->bmp->bd, obj->bmpPriorRendered->bi.biSizeImage);
						// Right now, we can use the bmpPriorRendered for a fast copy rather than 

				} else {
					// Render from its prior rendered version
					lnPixelsRendered += iBmp_bitBlt(obj->bmp, &lrc, obj->bmpPriorRendered);
				}


			//////////
			// Indicate we're no longer dirty, that we have everything rendered, but it needs publishing
			//////
				obj->isDirtyRender = false;
				obj->isDirtyPublish	= true;
		}

		// Indicate status
		return(lnPixelsRendered);
	}




//////////
//
// Render the rider and its children
//
//////
	u32 iSubobj_renderRider(SObject* obj)
	{
		u32		lnPixelsRendered;
		SBgra	backColor;
		RECT	lrc;


		// Make sure our environment is sane
		logfunc(__FUNCTION__);
		lnPixelsRendered = 0;
		if (obj && obj->isRendered)
		{
			if (obj->isDirtyRender)
			{

				//////////
				// Fill in the background
				//////
					SetRect(&lrc, 0, 0, obj->bmp->bi.biWidth, obj->bmp->bi.biHeight);
					if (!obj->firstChild)
					{
						// Fill in with the back color
						backColor = propBackColor(obj);
						iBmp_fillRect(obj->bmp, &lrc, backColor, backColor, backColor, backColor, false, NULL, false);

					} else {
						// Overlay the rider's child
						iBmp_bitBlt(obj->bmp, &lrc, obj->firstChild->bmp);
					}


				//////////
				// Copy to prior rendered bitmap
				//////
					// Make sure our bmpPriorRendered exists
					obj->bmpPriorRendered = iBmp_verifyCopyIsSameSize(obj->bmpPriorRendered, obj->bmp);

					// Copy to the prior rendered version
					memcpy(obj->bmpPriorRendered->bd, obj->bmp->bd, obj->bmpPriorRendered->bi.biSizeImage);
					// Right now, we can use the bmpPriorRendered for a fast copy rather than 


			} else {
				// Render from its prior rendered version
				lnPixelsRendered += iBmp_bitBlt(obj->bmp, &lrc, obj->bmpPriorRendered);
			}


			// Indicate we're no longer dirty, that we have everything rendered, but it needs publishing
			obj->isDirtyRender = false;
			obj->isDirtyPublish	= true;
		}

		// Indicate status
		return(lnPixelsRendered);
	}




//////////
//
// Renders the label.
//
//////
	u32 iSubobj_renderLabel(SObject* obj)
	{
		s32			lnBackStyle, lnAlignment;
		u32			lnPixelsRendered, lnFormat;
		SBgra		backColor, foreColor, borderColor;
		SVariable*	caption;
		SVariable*	value;
		RECT		lrc, lrc2;


		// Make sure our environment is sane
		logfunc(__FUNCTION__);
		lnPixelsRendered = 0;
		if (obj && obj->isRendered)
		{
			if (obj->isDirtyRender)
			{
				borderColor	= propBorderColor(obj);
				backColor	= propBackColor(obj);
				foreColor	= propForeColor(obj);
				lnBackStyle	= propBackStyle(obj);
				if (lnBackStyle == _BACK_STYLE_OPAQUE)
				{
					// Use the back color
					SetBkColor(obj->bmp->hdc,	RGB(backColor.red, backColor.grn, backColor.blu));
					SetTextColor(obj->bmp->hdc,	RGB(foreColor.red, foreColor.grn, foreColor.blu));

				} else {
					// Use a black and white creation
					SetBkColor(obj->bmp->hdc, RGB(255,255,255));
					SetTextColor(obj->bmp->hdc, RGB(0,0,0));
				}

				// Fill in the background
				SetRect(&lrc, 0, 0, obj->bmp->bi.biWidth, obj->bmp->bi.biHeight);
				iBmp_fillRect(obj->bmp, &lrc, whiteColor, whiteColor, whiteColor, whiteColor, false, NULL, false);

				// Set the text parameters
				SetBkMode(obj->bmp->hdc, TRANSPARENT);
				SelectObject(obj->bmp->hdc, obj->p.font->hfont);

				// Determine our orientation
				lnAlignment = propAlignment(obj);
				switch (lnAlignment)
				{
					default:
//					case _ALIGNMENT_MIDDLE_LEFT:
					case _ALIGNMENT_LEFT:
						lnFormat = DT_LEFT | DT_VCENTER;
						break;
					case _ALIGNMENT_TOP_LEFT:
						lnFormat = DT_LEFT | DT_TOP;
						break;
					case _ALIGNMENT_BOTTOM_LEFT:
						lnFormat = DT_LEFT | DT_BOTTOM;
						break;

//					case _ALIGNMENT_MIDDLE_RIGHT:
					case _ALIGNMENT_RIGHT:
						lnFormat = DT_RIGHT | DT_VCENTER;
						break;
					case _ALIGNMENT_TOP_RIGHT:
						lnFormat = DT_RIGHT | DT_TOP;
						break;
					case _ALIGNMENT_BOTTOM_RIGHT:
						lnFormat = DT_RIGHT | DT_BOTTOM;
						break;

//					case _ALIGNMENT_MIDDLE_CENTER:
					case _ALIGNMENT_CENTER:
						lnFormat = DT_CENTER | DT_VCENTER;
						break;
					case _ALIGNMENT_TOP_CENTER:
						lnFormat = DT_CENTER | DT_TOP;
						break;
					case _ALIGNMENT_BOTTOM_CENTER:
						lnFormat = DT_CENTER | DT_BOTTOM;
						break;
				}

				// Copy the rectangle
				CopyRect(&lrc2, &lrc);

				// Adjust if need be
				if (obj->parent && obj->parent->objType == _OBJ_TYPE_CHECKBOX)
					lrc.left += 4;	// Adjusts between the left-side checkbox image, and the text

				// Draw the text
				caption = iObjProp_get_var_byIndex(obj, _INDEX_CAPTION);
				DrawText(obj->bmp->hdc, caption->value.data_s8, caption->value.length, &lrc, lnFormat | DT_END_ELLIPSIS | DT_SINGLELINE);

				// And adjust back if need be
				if (obj->parent && obj->parent->objType == _OBJ_TYPE_CHECKBOX)
					lrc.left -= 4;

				// Frame rectangle
				if (propBorderStyle(obj) != _BORDER_STYLE_NONE)
					iBmp_frameRect(obj->bmp, &lrc, borderColor, borderColor, borderColor, borderColor, false, NULL, false);

				// For checkbox labels, we handle them differently
				if (obj->parent && obj->parent->objType == _OBJ_TYPE_CHECKBOX)
				{
					// Append the color marker at the end of the label
					SetRect(&lrc2, lrc.right - ((lrc.bottom - lrc.top) / 2), 0, lrc.right, lrc.bottom);
					value = iObjProp_get_var_byIndex(obj->parent, _INDEX_VALUE);
					if (get_s32(value) == 0)
					{
						// It's off, so color it red
						iBmp_fillRect(obj->bmp, &lrc2, nwColor_checkboxOff, neColor_checkboxOff, swColor_checkboxOff, seColor_checkboxOff, true, NULL, false);

					} else {
						// It's on, so color it green
						iBmp_fillRect(obj->bmp, &lrc2, nwColor_checkboxOn, neColor_checkboxOn, swColor_checkboxOn, seColor_checkboxOn, true, NULL, false);
					}

					// Colorize the area
					SetRect(&lrc2, lrc.left, lrc.top, lrc.right - ((lrc.bottom - lrc.top) / 2), lrc.bottom);
					     if (obj->ev.isMouseDown)		iBmp_colorize(obj->bmp, &lrc2, colorMouseDown,	false, 0.0f);
					else if (obj->ev.isMouseOver)		iBmp_colorize(obj->bmp, &lrc2, colorMouseOver,	false, 0.0f);

				} else if (lnBackStyle == _BACK_STYLE_OPAQUE) {
					// Colorize the area
					     if (obj->ev.isMouseDown)		iBmp_colorize(obj->bmp, &lrc, colorMouseDown,	false, 0.0f);
					else if (obj->ev.isMouseOver)		iBmp_colorize(obj->bmp, &lrc, colorMouseOver,	false, 0.0f);
				}


				//////////
				// Copy to prior rendered bitmap
				//////
					// Make sure our bmpPriorRendered exists
					obj->bmpPriorRendered = iBmp_verifyCopyIsSameSize(obj->bmpPriorRendered, obj->bmp);

					// Copy to the prior rendered version
					memcpy(obj->bmpPriorRendered->bd, obj->bmp->bd, obj->bmpPriorRendered->bi.biSizeImage);
					// Right now, we can use the bmpPriorRendered for a fast copy rather than 

			} else {
				// Render from its prior rendered version
				lnPixelsRendered += iBmp_bitBlt(obj->bmp, &lrc, obj->bmpPriorRendered);
			}


			// Indicate we're no longer dirty, that we have everything rendered, but it needs publishing
			obj->isDirtyRender = false;
			obj->isDirtyPublish	= true;
		}

		// Indicate status
		return(lnPixelsRendered);
	}




//////////
//
// Renders the textbox.
//
//////
	u32 iSubobj_renderTextbox(SObject* obj)
	{
		u32			lnPixelsRendered, lnFormat;
		SBgra		backColor, foreColor, borderColor;
		SVariable*	value;
		RECT		lrc, lrc2;


		// Make sure our environment is sane
		logfunc(__FUNCTION__);
		lnPixelsRendered = 0;
		if (obj && obj->isRendered)
		{
			if (obj->isDirtyRender)
			{
				// Fill in the background
				SetRect(&lrc, 0, 0, obj->bmp->bi.biWidth, obj->bmp->bi.biHeight);
				iiBmp_frameInNineParts(obj->bmp, &lrc, bmpTextbox);

				// Grab the colors
				backColor	= propBackColor(obj);
				foreColor	= propForeColor(obj);
				borderColor	= propBorderColor(obj);

				// Colorize
				     if (obj->ev.isMouseDown)		iBmp_colorize(obj->bmp, &lrc, colorMouseDown,		false, 0.0f);
				else if (obj->ev.isMouseOver)		iBmp_colorize(obj->bmp, &lrc, colorMouseOver,		false, 0.0f);
				else									iBmp_colorize(obj->bmp, &lrc, propBackColor(obj),	false, 0.0f);

				// Inset slightly for the text part
				CopyRect(&lrc2, &lrc);
				InflateRect(&lrc2, -4, -4);

				// If we're opaque, draw the text inset by a margin, otherwise just overlay
				if (propBackStyle(obj) == _BACK_STYLE_OPAQUE)
				{
					// Opaque
					SetBkColor(obj->bmp->hdc, RGB(backColor.red, backColor.grn, backColor.blu));
					SetBkMode(obj->bmp->hdc, OPAQUE);

				} else {
					// Transparent
					SetBkMode(obj->bmp->hdc, TRANSPARENT);
				}

				// Set the text parameters
				SetTextColor(obj->bmp->hdc, RGB(foreColor.red, foreColor.grn, foreColor.blu));
				SelectObject(obj->bmp->hdc, obj->p.font->hfont);

				// Determine our orientation
				switch (propAlignment(obj))
				{
					default:
					case _ALIGNMENT_LEFT:
						lnFormat = DT_LEFT;
						break;

					case _ALIGNMENT_RIGHT:
						lnFormat = DT_RIGHT;
						break;

					case _ALIGNMENT_CENTER:
						lnFormat = DT_CENTER;
						break;
				}

				// Draw the text
				value = iObjProp_get_var_byIndex(obj, _INDEX_VALUE);
				DrawText(obj->bmp->hdc, value->value.data_s8, value->value.length, &lrc2, lnFormat | DT_VCENTER | DT_END_ELLIPSIS);

				// Frame rectangle
				if (propBorderStyle(obj) != _BORDER_STYLE_NONE)
					iBmp_frameRect(obj->bmp, &lrc, borderColor, borderColor, borderColor, borderColor, false, NULL, false);


				//////////
				// Copy to prior rendered bitmap
				//////
					// Make sure our bmpPriorRendered exists
					obj->bmpPriorRendered = iBmp_verifyCopyIsSameSize(obj->bmpPriorRendered, obj->bmp);

					// Copy to the prior rendered version
					memcpy(obj->bmpPriorRendered->bd, obj->bmp->bd, obj->bmpPriorRendered->bi.biSizeImage);
					// Right now, we can use the bmpPriorRendered for a fast copy rather than 

			} else {
				// Render from its prior rendered version
				lnPixelsRendered += iBmp_bitBlt(obj->bmp, &lrc, obj->bmpPriorRendered);
			}


			// Indicate we're no longer dirty, that we have everything rendered, but it needs publishing
			obj->isDirtyRender = false;
			obj->isDirtyPublish	= true;
		}

		// Indicate status
		return(lnPixelsRendered);
	}




//////////
//
// Renders the button.
//
//////
	u32 iSubobj_renderButton(SObject* obj)
	{
		u32			lnPixelsRendered, lnFormat;
		SBgra		backColor, foreColor, borderColor;
		SVariable*	caption;
		RECT		lrc, lrc2;


		// Make sure our environment is sane
		logfunc(__FUNCTION__);
		lnPixelsRendered = 0;
		if (obj && obj->isRendered)
		{
			if (obj->isDirtyRender)
			{
				// Fill in the background
				SetRect(&lrc, 0, 0, obj->bmp->bi.biWidth, obj->bmp->bi.biHeight);
				iiBmp_frameInNineParts(obj->bmp, &lrc, bmpButton);

				// Get the colors
				backColor	= propBackColor(obj);
				foreColor	= propForeColor(obj);
				borderColor	= propBorderColor(obj);

				// Colorize
				     if (obj->ev.isMouseDown)		iBmp_colorize(obj->bmp, &lrc, colorMouseDown,		false, 0.0f);
				else if (obj->ev.isMouseOver)		iBmp_colorize(obj->bmp, &lrc, colorMouseOver,		false, 0.0f);
				else									iBmp_colorize(obj->bmp, &lrc, propBackColor(obj),	false, 0.0f);

				// Inset slightly for the text part
				CopyRect(&lrc2, &lrc);
				InflateRect(&lrc2, -4, -4);

				// If we're opaque, draw the text inset by a margin, otherwise just overlay
				if (propBackStyle(obj) == _BACK_STYLE_OPAQUE)
				{
					// Opaque
					SetBkColor(obj->bmp->hdc, RGB(backColor.red, backColor.grn, backColor.blu));
					SetBkMode(obj->bmp->hdc, OPAQUE);

				} else {
					// Transparent
					SetBkMode(obj->bmp->hdc, TRANSPARENT);
				}

				// Set the text parameters
				SetTextColor(obj->bmp->hdc, RGB(foreColor.red, foreColor.grn, foreColor.blu));
				SelectObject(obj->bmp->hdc, obj->p.font->hfont);

				// Determine our orientation
				switch (propAlignment(obj))
				{
					default:
					case _ALIGNMENT_LEFT:
						lnFormat = DT_LEFT;
						break;

					case _ALIGNMENT_RIGHT:
						lnFormat = DT_RIGHT;
						break;

					case _ALIGNMENT_CENTER:
						lnFormat = DT_CENTER;
						break;
				}

				// Draw the text
				caption = iObjProp_get_var_byIndex(obj, _INDEX_CAPTION);
				DrawText(obj->bmp->hdc, caption->value.data_s8, caption->value.length, &lrc2, lnFormat | DT_VCENTER | DT_END_ELLIPSIS);

				// Frame rectangle
				if (propBorderStyle(obj) != _BORDER_STYLE_NONE)
					iBmp_frameRect(obj->bmp, &lrc, borderColor, borderColor, borderColor, borderColor, false, NULL, false);


				//////////
				// Copy to prior rendered bitmap
				//////
					// Make sure our bmpPriorRendered exists
					obj->bmpPriorRendered = iBmp_verifyCopyIsSameSize(obj->bmpPriorRendered, obj->bmp);

					// Copy to the prior rendered version
					memcpy(obj->bmpPriorRendered->bd, obj->bmp->bd, obj->bmpPriorRendered->bi.biSizeImage);
					// Right now, we can use the bmpPriorRendered for a fast copy rather than 

			} else {
				// Render from its prior rendered version
				lnPixelsRendered += iBmp_bitBlt(obj->bmp, &lrc, obj->bmpPriorRendered);
			}


			// Indicate we're no longer dirty, that we have everything rendered, but it needs publishing
			obj->isDirtyRender = false;
			obj->isDirtyPublish	= true;
		}

		// Indicate status
		return(lnPixelsRendered);
	}




//////////
//
// Renders the editbox.
//
//////
	u32 iSubobj_renderEditbox(SObject* obj)
	{
		u32		lnPixelsRendered;
		SBgra	borderColor;
		RECT	lrc;


		// Make sure our environment is sane
		logfunc(__FUNCTION__);
		lnPixelsRendered = 0;
		if (obj && obj->isRendered)
		{
			// Grab the rectangle
			iSEM_getRectAndFont(obj->p.sem, obj, &lrc);

			// Are we rendering?
			if (obj->isDirtyRender)
			{
				// Re-render
				lnPixelsRendered = iSEM_render(obj->p.sem, obj, obj->p.hasFocus);

				// Get colors
				borderColor = propBorderColor(obj);

				if (propBorderStyle(obj) != _BORDER_STYLE_NONE)
					iBmp_frameRect(obj->bmp, &lrc, borderColor, borderColor, borderColor, borderColor, false, NULL, false);

				//////////
				// Copy to prior rendered bitmap
				//////
					// Make sure our bmpPriorRendered exists
					obj->bmpPriorRendered = iBmp_verifyCopyIsSameSize(obj->bmpPriorRendered, obj->bmp);

					// Copy to the prior rendered version
					memcpy(obj->bmpPriorRendered->bd, obj->bmp->bd, obj->bmpPriorRendered->bi.biSizeImage);
					// Right now, we can use the bmpPriorRendered for a fast copy rather than 

			} else {
				// Render from its prior rendered version
				lnPixelsRendered += iBmp_bitBlt(obj->bmp, &lrc, obj->bmpPriorRendered);
			}


			// Indicate we're no longer dirty, that we have everything rendered, but it needs publishing
			obj->isDirtyRender = false;
			obj->isDirtyPublish	= true;
		}

		// Indicate status
		return(lnPixelsRendered);
	}




//////////
//
// Renders the image.
//
//////
	u32 iSubobj_renderImage(SObject* obj)
	{
		u32			lnPixelsRendered;
		bool		llDeleteBmpMask;
		SBgra		color;
		SBitmap*	bmp;
		SBitmap*	bmpMask;
		SObject*	subform;
		RECT		lrc;


		// Make sure our environment is sane
		logfunc(__FUNCTION__);
		lnPixelsRendered = 0;
		if (obj && obj->isRendered)
		{
			// Compute our rectangle for drawing
			SetRect(&lrc, 0, 0, obj->bmp->bi.biWidth, obj->bmp->bi.biHeight);
			if (obj->isDirtyRender)
			{
				//////////
				// Based on the current conditions, render the appropriate image
				//////
					if (obj->ev.isMouseDown)
					{
						// Mouse is down on this item
						bmp = iObjProp_get_bitmap(obj, _INDEX_PICTUREBMP_DOWN);

					} else if (obj->ev.isMouseOver) {
						// Mouse is over this item
						bmp = iObjProp_get_bitmap(obj, _INDEX_PICTUREBMP_OVER);

					} else {
						// Render normally
						bmp = iObjProp_get_bitmap(obj, _INDEX_PICTUREBMP);
					}


				//////////
				// Grab the background color for any mask colors
				//////
					if (propBackMask(obj))
					{
						// If we're on a subform, and it has focus, use the focus color
						if ((subform = iObj_find_thisSubform(obj)) && iObj_focus_descentCheck(subform, true, false))
						{
							// It has focus, use the focus color
							color = nwColor_focus;

						} else {
							// Search for the parent nwColor
							color = iObj_getColor_ascent(obj, _INDEX_NWCOLOR, false, nwColor_subform);
						}

						// Make a copy for the color swap
						llDeleteBmpMask	= true;
						bmpMask			= iBmp_copy(bmp);
						iBmp_swapColors(bmpMask, maskColor, color);

					} else {
						llDeleteBmpMask	= false;
						bmpMask			= bmp;
					}


				//////////
				// Render
				//////
					if (bmp->bi.biWidth == lrc.right - lrc.left && bmp->bi.biHeight == lrc.bottom - lrc.top)
					{
						// Direct copy
						lnPixelsRendered += iBmp_bitBlt(obj->bmp, &lrc, bmpMask);

					} else {
						// Scale
						// Nov.29.2015 RCH -- The scale algorithm isn't quite working properly, so we fall back on StretchBlt()
						// iBmp_scale(obj->bmp, bmp);
						SetStretchBltMode(obj->bmp->hdc, HALFTONE);
						StretchBlt(obj->bmp->hdc, lrc.left, lrc.top, lrc.right - lrc.left, lrc.bottom - lrc.top, bmpMask->hdc, 0, 0, bmpMask->bi.biWidth, bmpMask->bi.biHeight, SRCCOPY);
						lnPixelsRendered += (lrc.right - lrc.left) * (lrc.bottom - lrc.top);
					}

					// Clean up if need be
					if (llDeleteBmpMask)
						iBmp_delete(&bmpMask, true, true);


				//////////
				// For checkbox images, we colorize them differently
				//////
					if (obj->parent && obj->parent->objType == _OBJ_TYPE_CHECKBOX)
					{
						// Colorize
							 if (obj->ev.isMouseDown)		iBmp_colorize(obj->bmp, &lrc, colorMouseDown,	false, 0.0f);
						else if (obj->ev.isMouseOver)		iBmp_colorize(obj->bmp, &lrc, colorMouseOver,	false, 0.0f);
					}


				//////////
				// Copy to prior rendered bitmap
				//////
					// Make sure our bmpPriorRendered exists
					obj->bmpPriorRendered = iBmp_verifyCopyIsSameSize(obj->bmpPriorRendered, obj->bmp);

					// Copy to the prior rendered version
					memcpy(obj->bmpPriorRendered->bd, obj->bmp->bd, obj->bmpPriorRendered->bi.biSizeImage);
					// Right now, we can use the bmpPriorRendered for a fast copy rather than 

			} else {
				// Render from its prior rendered version
				lnPixelsRendered += iBmp_bitBlt(obj->bmp, &lrc, obj->bmpPriorRendered);
			}

			// Indicate we're no longer dirty, that we have everything rendered, but it needs publishing
			obj->isDirtyRender = false;
			obj->isDirtyPublish	= true;
		}

		// Indicate status
		return(lnPixelsRendered);
	}




//////////
//
// Renders the logical checkbox control.  The checkbox is not actually rendered, but
// rather it reads from the parent whatever is underneath its rectangle at the point
// of the render request, then it draws the child objects atop itself.
//
//////
	u32 iSubobj_renderCheckbox(SObject* obj)
	{
		u32			lnPixelsRendered;
		SObject*	objChild;
		RECT		lrc;


		// Make sure our environment is sane
		logfunc(__FUNCTION__);
		lnPixelsRendered = 0;
		if (obj && obj->isRendered)
		{
			// Compute our rectangle for drawing
			SetRect(&lrc, 0, 0, obj->bmp->bi.biWidth, obj->bmp->bi.biHeight);

			// There is nothing actually rendered here, but the child renders into it
			if (obj->isDirtyRender)
			{
// TODO:  Nov.30.2015 -- Working here, this will force a redraw of children, but they should be being redrawn automatically ... so something's awry
// TODO:  Nov.30.2015 -- Also, green bmp isn't being changed, and green right-rectangle isn't being colorized
				// Render children onto this one
				for (objChild = obj->firstChild; objChild; objChild = objChild->ll.nextObj)
					iBmp_bitBlt(obj->bmp, &objChild->rc, objChild->bmp);


				//////////
				// Copy to prior rendered bitmap
				//////
					// Make sure our bmpPriorRendered exists
					obj->bmpPriorRendered = iBmp_verifyCopyIsSameSize(obj->bmpPriorRendered, obj->bmp);
// iBmp_saveToDisk(obj->bmpPriorRendered, "c:\\temp\\checkbox_prior.bmp");
// iBmp_saveToDisk(obj->bmp, "c:\\temp\\checkbox.bmp");

					// Copy to the prior rendered version
					memcpy(obj->bmpPriorRendered->bd, obj->bmp->bd, obj->bmpPriorRendered->bi.biSizeImage);
					// Right now, we can use the bmpPriorRendered for a fast copy rather than 

			} else {
				// Render from its prior rendered version
				lnPixelsRendered += iBmp_bitBlt(obj->bmp, &lrc, obj->bmpPriorRendered);
			}

			// Indicate we're no longer dirty, that we have everything rendered, but it needs publishing
			obj->isDirtyRender = false;
			obj->isDirtyPublish	= true;
		}

		// Indicate status
		return(lnPixelsRendered);
	}




//////////
//
// Renders the option.
//
//////
	u32 iSubobj_renderOption(SObject* obj)
	{
		logfunc(__FUNCTION__);


			//////////
			// Indicate we're no longer dirty, that we have everything
			//////
				obj->isDirtyRender = false;
		return(0);
	}




//////////
//
// Renders the radio.
//
//////
	u32 iSubobj_renderRadio(SObject* obj)
	{
		u32			lnPixelsRendered, lnXCenter, lnYCenter, lnSkip;
		f32			lfTheta, lfRadius;
		f64			lfValue, lfMin, lfMax;
		SBitmap*	bmpRadioScale;
		SBgra		foreColor;
		RECT		lrc, lrc2;
		s8*			lcSprintfFormat;
		s8			buffer[64];


		// Make sure our environment is sane
		logfunc(__FUNCTION__);
		lnPixelsRendered = 0;
		if (obj && obj->isRendered)
		{
			// Compute our rectangle for drawing
			SetRect(&lrc, 0, 0, obj->bmp->bi.biWidth, obj->bmp->bi.biHeight);

			if (obj->isDirtyRender)
			{
				//////////
				// Get the values
				//////
					lfValue	= iObjProp_get_f64_direct(obj, _INDEX_VALUE);
					lfMin	= iObjProp_get_f64_direct(obj, _INDEX_VALUE_MINIMUM);
					lfMax	= iObjProp_get_f64_direct(obj, _INDEX_VALUE_MAXIMUM);

					// Make sure max is greater than or equal to min, and value is in range
					lfMax	= max(lfMin, lfMax);
					lfValue	= min(max(lfValue, lfMin), lfMax);

					// Determine the percentage
					lfTheta	= (f32)((lfValue - lfMin) / (lfMax - lfMin)) * (f32)(M_PI * 2.0);

					// Color
					foreColor = propForeColor(obj);


				//////////
				// Determine the scaling ratio for the dial indicator
				//////
					// Create a copy for later scaling
					bmpRadioScale = iBmp_allocate();
					iBmp_createBySize(bmpRadioScale, bmpRadio->bi.biWidth, bmpRadio->bi.biHeight, 24);
					bmpRadioScale = iBmp_copy(bmpRadio);


				//////////
				// Compute the position the dial indicator based on settings, and build the lrc2 on it
				//////
					lfRadius	= (f32)bmpRadioScale->bi.biWidth * 0.225f;
					lnXCenter	= (u32)(((f32)bmpRadioScale->bi.biWidth  / 2.0f));
					lnYCenter	= (u32)(((f32)bmpRadioScale->bi.biHeight / 2.0f));

					// Build the rect
					SetRect(&lrc2,	(u32)(lnXCenter + (lfRadius * cos(lfTheta)) - (bmpRadioDot->bi.biWidth / 2)),
									(u32)(lnYCenter - (lfRadius * sin(lfTheta)) - (bmpRadioDot->bi.biHeight / 2)),
									0, 0);
					
					lrc2.right	= lrc2.left	+ bmpRadioDot->bi.biWidth;
					lrc2.bottom	= lrc2.top	+ bmpRadioDot->bi.biHeight;
					iBmp_bitBltMask(bmpRadioScale, &lrc2, bmpRadioDot);


				// Scale the base into it
				iBmp_scale(obj->bmp, bmpRadioScale);

				// Delete the scaled dot
				iBmp_delete(&bmpRadioScale, true, true);


				//////////
				// Draw the text of the value into the center
				//////
					lcSprintfFormat = iMath_roundTo(&lfValue, iObjProp_get_f64_direct(obj, _INDEX_ROUND_TO));
					sprintf(buffer, lcSprintfFormat, lfValue);

					if (buffer[strlen(buffer)] == '.')
						buffer[strlen(buffer)] = 0;

					lnSkip = iSkip_whitespaces(buffer, (u32)strlen(buffer));

					SetRect(&lrc2,	obj->bmp->bi.biWidth / 7,
									(obj->bmp->bi.biHeight / 2) - (obj->bmp->bi.biHeight / 7),
									obj->bmp->bi.biWidth * 6 / 7,
									(obj->bmp->bi.biHeight / 2) + (obj->bmp->bi.biHeight / 7));
					
					SetTextColor(obj->bmp->hdc, RGB(foreColor.red, foreColor.grn, foreColor.blu));
					SetBkMode(obj->bmp->hdc, TRANSPARENT);
					SelectObject(obj->bmp->hdc, ((obj->p.font) ? obj->p.font : gsFontDefault)->hfont);
					DrawText(obj->bmp->hdc, buffer + lnSkip, (int)strlen(buffer + lnSkip), &lrc2, DT_CENTER | DT_SINGLELINE | DT_VCENTER);


				// Colorize
				     if (obj->ev.isMouseDown)		iBmp_colorize(obj->bmp, &lrc, colorMouseDown,	false, 0.0f);
				else if (obj->ev.isMouseOver)		iBmp_colorize(obj->bmp, &lrc, colorMouseOver,	false, 0.0f);
				else								iBmp_colorize(obj->bmp, &lrc, propBackColor(obj),	false, 0.0f);


				//////////
				// Copy to prior rendered bitmap
				//////
					// Make sure our bmpPriorRendered exists
					obj->bmpPriorRendered = iBmp_verifyCopyIsSameSize(obj->bmpPriorRendered, obj->bmp);

					// Copy to the prior rendered version
					memcpy(obj->bmpPriorRendered->bd, obj->bmp->bd, obj->bmpPriorRendered->bi.biSizeImage);
					// Right now, we can use the bmpPriorRendered for a fast copy rather than 

			} else {
				// Render from its prior rendered version
				lnPixelsRendered += iBmp_bitBlt(obj->bmp, &lrc, obj->bmpPriorRendered);
			}

			// Indicate we're no longer dirty, that we have everything rendered, but it needs publishing
			obj->isDirtyRender = false;
			obj->isDirtyPublish	= true;
		}

		// Indicate status
		return(lnPixelsRendered);
	}




//////////
//
// Renders the cmdGroup.
//
//////
	u32 iSubobj_renderCmdGroup(SObject* obj)
	{
		u32		lnPixelsRendered;
		RECT	lrc;


		// Make sure our environment is sane
		logfunc(__FUNCTION__);
		lnPixelsRendered = 0;
		if (obj && obj->isRendered)
		{
			// Compute our rectangle for drawing
			SetRect(&lrc, 0, 0, obj->bmp->bi.biWidth, obj->bmp->bi.biHeight);
			if (obj->isDirtyRender)
			{
				// Render a white box as a placeholder
				iBmp_fillRect(obj->bmp, &lrc, whiteColor, whiteColor, whiteColor, whiteColor, false, NULL, false);


				//////////
				// Copy to prior rendered bitmap
				//////
					// Make sure our bmpPriorRendered exists
					obj->bmpPriorRendered = iBmp_verifyCopyIsSameSize(obj->bmpPriorRendered, obj->bmp);

					// Copy to the prior rendered version
					memcpy(obj->bmpPriorRendered->bd, obj->bmp->bd, obj->bmpPriorRendered->bi.biSizeImage);
					// Right now, we can use the bmpPriorRendered for a fast copy rather than 

			} else {
				// Render from its prior rendered version
				lnPixelsRendered += iBmp_bitBlt(obj->bmp, &lrc, obj->bmpPriorRendered);
			}

			// Indicate we're no longer dirty, that we have everything rendered, but it needs publishing
			obj->isDirtyRender = false;
			obj->isDirtyPublish	= true;
		}

		// Indicate status
		return(lnPixelsRendered);
	}




//////////
//
// Renders the optGroup.
//
//////
	u32 iSubobj_renderOptGroup(SObject* obj)
	{
		u32		lnPixelsRendered;
		RECT	lrc;


		// Make sure our environment is sane
		logfunc(__FUNCTION__);
		lnPixelsRendered = 0;
		if (obj && obj->isRendered)
		{
			// Compute our rectangle for drawing
			SetRect(&lrc, 0, 0, obj->bmp->bi.biWidth, obj->bmp->bi.biHeight);
			if (obj->isDirtyRender)
			{
				// Render a white box as a placeholder
				iBmp_fillRect(obj->bmp, &lrc, whiteColor, whiteColor, whiteColor, whiteColor, false, NULL, false);


				//////////
				// Copy to prior rendered bitmap
				//////
					// Make sure our bmpPriorRendered exists
					obj->bmpPriorRendered = iBmp_verifyCopyIsSameSize(obj->bmpPriorRendered, obj->bmp);

					// Copy to the prior rendered version
					memcpy(obj->bmpPriorRendered->bd, obj->bmp->bd, obj->bmpPriorRendered->bi.biSizeImage);
					// Right now, we can use the bmpPriorRendered for a fast copy rather than 

			} else {
				// Render from its prior rendered version
				lnPixelsRendered += iBmp_bitBlt(obj->bmp, &lrc, obj->bmpPriorRendered);
			}

			// Indicate we're no longer dirty, that we have everything rendered, but it needs publishing
			obj->isDirtyRender = false;
			obj->isDirtyPublish	= true;
		}

		// Indicate status
		return(lnPixelsRendered);
	}




//////////
//
// Renders the listbox.
//
//////
	u32 iSubobj_renderListbox(SObject* obj)
	{
		u32		lnPixelsRendered;
		RECT	lrc;


		// Make sure our environment is sane
		logfunc(__FUNCTION__);
		lnPixelsRendered = 0;
		if (obj && obj->isRendered)
		{
			// Compute our rectangle for drawing
			SetRect(&lrc, 0, 0, obj->bmp->bi.biWidth, obj->bmp->bi.biHeight);
			if (obj->isDirtyRender)
			{
				// Render a white box as a placeholder
				iBmp_fillRect(obj->bmp, &lrc, whiteColor, whiteColor, whiteColor, whiteColor, false, NULL, false);


				//////////
				// Copy to prior rendered bitmap
				//////
					// Make sure our bmpPriorRendered exists
					obj->bmpPriorRendered = iBmp_verifyCopyIsSameSize(obj->bmpPriorRendered, obj->bmp);

					// Copy to the prior rendered version
					memcpy(obj->bmpPriorRendered->bd, obj->bmp->bd, obj->bmpPriorRendered->bi.biSizeImage);
					// Right now, we can use the bmpPriorRendered for a fast copy rather than 

			} else {
				// Render from its prior rendered version
				lnPixelsRendered += iBmp_bitBlt(obj->bmp, &lrc, obj->bmpPriorRendered);
			}

			// Indicate we're no longer dirty, that we have everything rendered, but it needs publishing
			obj->isDirtyRender = false;
			obj->isDirtyPublish	= true;
		}

		// Indicate status
		return(lnPixelsRendered);
	}




//////////
//
// Renders the combobox.
//
//////
	u32 iSubobj_renderCombobox(SObject* obj)
	{
		u32		lnPixelsRendered;
		RECT	lrc;


		// Make sure our environment is sane
		logfunc(__FUNCTION__);
		lnPixelsRendered = 0;
		if (obj && obj->isRendered)
		{
			// Compute our rectangle for drawing
			SetRect(&lrc, 0, 0, obj->bmp->bi.biWidth, obj->bmp->bi.biHeight);
			if (obj->isDirtyRender)
			{
				// Render a white box as a placeholder
				iBmp_fillRect(obj->bmp, &lrc, whiteColor, whiteColor, whiteColor, whiteColor, false, NULL, false);


				//////////
				// Copy to prior rendered bitmap
				//////
					// Make sure our bmpPriorRendered exists
					obj->bmpPriorRendered = iBmp_verifyCopyIsSameSize(obj->bmpPriorRendered, obj->bmp);

					// Copy to the prior rendered version
					memcpy(obj->bmpPriorRendered->bd, obj->bmp->bd, obj->bmpPriorRendered->bi.biSizeImage);
					// Right now, we can use the bmpPriorRendered for a fast copy rather than 

			} else {
				// Render from its prior rendered version
				lnPixelsRendered += iBmp_bitBlt(obj->bmp, &lrc, obj->bmpPriorRendered);
			}

			// Indicate we're no longer dirty, that we have everything rendered, but it needs publishing
			obj->isDirtyRender = false;
			obj->isDirtyPublish	= true;
		}

		// Indicate status
		return(lnPixelsRendered);
	}




//////////
//
// Renders the formset.
//
//////
	u32 iSubobj_renderFormset(SObject* obj)
	{
		u32		lnPixelsRendered;
		RECT	lrc;


		// Make sure our environment is sane
		logfunc(__FUNCTION__);
		lnPixelsRendered = 0;
		if (obj && obj->isRendered)
		{
			// Compute our rectangle for drawing
			SetRect(&lrc, 0, 0, obj->bmp->bi.biWidth, obj->bmp->bi.biHeight);
			if (obj->isDirtyRender)
			{
				// Render a white box as a placeholder
				iBmp_fillRect(obj->bmp, &lrc, whiteColor, whiteColor, whiteColor, whiteColor, false, NULL, false);


				//////////
				// Copy to prior rendered bitmap
				//////
					// Make sure our bmpPriorRendered exists
					obj->bmpPriorRendered = iBmp_verifyCopyIsSameSize(obj->bmpPriorRendered, obj->bmp);

					// Copy to the prior rendered version
					memcpy(obj->bmpPriorRendered->bd, obj->bmp->bd, obj->bmpPriorRendered->bi.biSizeImage);
					// Right now, we can use the bmpPriorRendered for a fast copy rather than 

			} else {
				// Render from its prior rendered version
				lnPixelsRendered += iBmp_bitBlt(obj->bmp, &lrc, obj->bmpPriorRendered);
			}

			// Indicate we're no longer dirty, that we have everything rendered, but it needs publishing
			obj->isDirtyRender = false;
			obj->isDirtyPublish	= true;
		}

		// Indicate status
		return(lnPixelsRendered);
	}




//////////
//
// Renders the toolbar.
//
//////
	u32 iSubobj_renderToolbar(SObject* obj)
	{
		u32		lnPixelsRendered;
		SBgra	bgra;
		RECT	lrc;


		// Make sure our environment is sane
		logfunc(__FUNCTION__);
		lnPixelsRendered = 0;
		if (obj && obj->isRendered)
		{
			// Compute our rectangle for drawing
			SetRect(&lrc, 0, 0, obj->bmp->bi.biWidth, obj->bmp->bi.biHeight);
			if (obj->isDirtyRender)
			{

				//////////
				// Render a transparent background
				//////
					bgra = propBackColor(obj);
					iBmp_fillRect(obj->bmp, &lrc, bgra, bgra, bgra, bgra, false, NULL, false);


				//////////
				// Copy to prior rendered bitmap
				//////
					// Make sure our bmpPriorRendered exists
					obj->bmpPriorRendered = iBmp_verifyCopyIsSameSize(obj->bmpPriorRendered, obj->bmp);

					// Copy to the prior rendered version
					memcpy(obj->bmpPriorRendered->bd, obj->bmp->bd, obj->bmpPriorRendered->bi.biSizeImage);
					// Right now, we can use the bmpPriorRendered for a fast copy rather than 


			} else {
				// Render from its prior rendered version
				lnPixelsRendered += iBmp_bitBlt(obj->bmp, &lrc, obj->bmpPriorRendered);
			}

			// Indicate we're no longer dirty, that we have everything rendered, but it needs publishing
			obj->isDirtyRender = false;
			obj->isDirtyPublish	= true;
		}

		// Indicate status
		return(lnPixelsRendered);
	}




//////////
//
// Renders the separator.
//
//////
	u32 iSubobj_renderSeparator(SObject* obj)
	{
		u32		lnPixelsRendered;
		RECT	lrc;


		// Make sure our environment is sane
		logfunc(__FUNCTION__);
		lnPixelsRendered = 0;
		if (obj && obj->isRendered)
		{
			// Compute our rectangle for drawing
			SetRect(&lrc, 0, 0, obj->bmp->bi.biWidth, obj->bmp->bi.biHeight);
			if (obj->isDirtyRender)
			{
				// Render a white box as a placeholder
				iBmp_fillRect(obj->bmp, &lrc, whiteColor, whiteColor, whiteColor, whiteColor, false, NULL, false);


				//////////
				// Copy to prior rendered bitmap
				//////
					// Make sure our bmpPriorRendered exists
					obj->bmpPriorRendered = iBmp_verifyCopyIsSameSize(obj->bmpPriorRendered, obj->bmp);

					// Copy to the prior rendered version
					memcpy(obj->bmpPriorRendered->bd, obj->bmp->bd, obj->bmpPriorRendered->bi.biSizeImage);
					// Right now, we can use the bmpPriorRendered for a fast copy rather than 

			} else {
				// Render from its prior rendered version
				lnPixelsRendered += iBmp_bitBlt(obj->bmp, &lrc, obj->bmpPriorRendered);
			}

			// Indicate we're no longer dirty, that we have everything rendered, but it needs publishing
			obj->isDirtyRender = false;
			obj->isDirtyPublish	= true;
		}

		// Indicate status
		return(lnPixelsRendered);
	}




//////////
//
// Renders the line.
//
//////
	u32 iSubobj_renderLine(SObject* obj)
	{
		u32		lnPixelsRendered;
		RECT	lrc;


		// Make sure our environment is sane
		logfunc(__FUNCTION__);
		lnPixelsRendered = 0;
		if (obj && obj->isRendered)
		{
			// Compute our rectangle for drawing
			SetRect(&lrc, 0, 0, obj->bmp->bi.biWidth, obj->bmp->bi.biHeight);
			if (obj->isDirtyRender)
			{
				// Render a white box as a placeholder
				iBmp_fillRect(obj->bmp, &lrc, whiteColor, whiteColor, whiteColor, whiteColor, false, NULL, false);


				//////////
				// Copy to prior rendered bitmap
				//////
					// Make sure our bmpPriorRendered exists
					obj->bmpPriorRendered = iBmp_verifyCopyIsSameSize(obj->bmpPriorRendered, obj->bmp);

					// Copy to the prior rendered version
					memcpy(obj->bmpPriorRendered->bd, obj->bmp->bd, obj->bmpPriorRendered->bi.biSizeImage);
					// Right now, we can use the bmpPriorRendered for a fast copy rather than 

			} else {
				// Render from its prior rendered version
				lnPixelsRendered += iBmp_bitBlt(obj->bmp, &lrc, obj->bmpPriorRendered);
			}

			// Indicate we're no longer dirty, that we have everything rendered, but it needs publishing
			obj->isDirtyRender = false;
			obj->isDirtyPublish	= true;
		}

		// Indicate status
		return(lnPixelsRendered);
	}




//////////
//
// Renders the shape.
//
//////
	u32 iSubobj_renderShape(SObject* obj)
	{
		u32		lnPixelsRendered;
		RECT	lrc;


		// Make sure our environment is sane
		logfunc(__FUNCTION__);
		lnPixelsRendered = 0;
		if (obj && obj->isRendered)
		{
			// Compute our rectangle for drawing
			SetRect(&lrc, 0, 0, obj->bmp->bi.biWidth, obj->bmp->bi.biHeight);
			if (obj->isDirtyRender)
			{
				// Render a white box as a placeholder
				iBmp_fillRect(obj->bmp, &lrc, whiteColor, whiteColor, whiteColor, whiteColor, false, NULL, false);


				//////////
				// Copy to prior rendered bitmap
				//////
					// Make sure our bmpPriorRendered exists
					obj->bmpPriorRendered = iBmp_verifyCopyIsSameSize(obj->bmpPriorRendered, obj->bmp);

					// Copy to the prior rendered version
					memcpy(obj->bmpPriorRendered->bd, obj->bmp->bd, obj->bmpPriorRendered->bi.biSizeImage);
					// Right now, we can use the bmpPriorRendered for a fast copy rather than 

			} else {
				// Render from its prior rendered version
				lnPixelsRendered += iBmp_bitBlt(obj->bmp, &lrc, obj->bmpPriorRendered);
			}

			// Indicate we're no longer dirty, that we have everything rendered, but it needs publishing
			obj->isDirtyRender = false;
			obj->isDirtyPublish	= true;
		}

		// Indicate status
		return(lnPixelsRendered);
	}




//////////
//
// Renders the container.
//
//////
	u32 iSubobj_renderContainer(SObject* obj)
	{
		u32		lnPixelsRendered;
		RECT	lrc;


		// Make sure our environment is sane
		logfunc(__FUNCTION__);
		lnPixelsRendered = 0;
		if (obj && obj->isRendered)
		{
			// Compute our rectangle for drawing
			SetRect(&lrc, 0, 0, obj->bmp->bi.biWidth, obj->bmp->bi.biHeight);
			if (obj->isDirtyRender)
			{
				// Render a white box as a placeholder
				iBmp_fillRect(obj->bmp, &lrc, whiteColor, whiteColor, whiteColor, whiteColor, false, NULL, false);


				//////////
				// Copy to prior rendered bitmap
				//////
					// Make sure our bmpPriorRendered exists
					obj->bmpPriorRendered = iBmp_verifyCopyIsSameSize(obj->bmpPriorRendered, obj->bmp);

					// Copy to the prior rendered version
					memcpy(obj->bmpPriorRendered->bd, obj->bmp->bd, obj->bmpPriorRendered->bi.biSizeImage);
					// Right now, we can use the bmpPriorRendered for a fast copy rather than 

			} else {
				// Render from its prior rendered version
				lnPixelsRendered += iBmp_bitBlt(obj->bmp, &lrc, obj->bmpPriorRendered);
			}

			// Indicate we're no longer dirty, that we have everything rendered, but it needs publishing
			obj->isDirtyRender = false;
			obj->isDirtyPublish	= true;
		}

		// Indicate status
		return(lnPixelsRendered);
	}




//////////
//
// Renders the control.
//
//////
	u32 iSubobj_renderControl(SObject* obj)
	{
		u32		lnPixelsRendered;
		RECT	lrc;


		// Make sure our environment is sane
		logfunc(__FUNCTION__);
		lnPixelsRendered = 0;
		if (obj && obj->isRendered)
		{
			// Compute our rectangle for drawing
			SetRect(&lrc, 0, 0, obj->bmp->bi.biWidth, obj->bmp->bi.biHeight);
			if (obj->isDirtyRender)
			{
				// Render a white box as a placeholder
				iBmp_fillRect(obj->bmp, &lrc, whiteColor, whiteColor, whiteColor, whiteColor, false, NULL, false);


				//////////
				// Copy to prior rendered bitmap
				//////
					// Make sure our bmpPriorRendered exists
					obj->bmpPriorRendered = iBmp_verifyCopyIsSameSize(obj->bmpPriorRendered, obj->bmp);

					// Copy to the prior rendered version
					memcpy(obj->bmpPriorRendered->bd, obj->bmp->bd, obj->bmpPriorRendered->bi.biSizeImage);
					// Right now, we can use the bmpPriorRendered for a fast copy rather than 

			} else {
				// Render from its prior rendered version
				lnPixelsRendered += iBmp_bitBlt(obj->bmp, &lrc, obj->bmpPriorRendered);
			}

			// Indicate we're no longer dirty, that we have everything rendered, but it needs publishing
			obj->isDirtyRender = false;
			obj->isDirtyPublish	= true;
		}

		// Indicate status
		return(lnPixelsRendered);
	}




//////////
//
// Renders the grid.
//
//////
	u32 iSubobj_renderGrid(SObject* obj)
	{
		u32		lnPixelsRendered;
		RECT	lrc;


		// Make sure our environment is sane
		logfunc(__FUNCTION__);
		lnPixelsRendered = 0;
		if (obj && obj->isRendered)
		{
			// Compute our rectangle for drawing
			SetRect(&lrc, 0, 0, obj->bmp->bi.biWidth, obj->bmp->bi.biHeight);
			if (obj->isDirtyRender)
			{
				// Render a white box as a placeholder
				iBmp_fillRect(obj->bmp, &lrc, whiteColor, whiteColor, whiteColor, whiteColor, false, NULL, false);


				//////////
				// Copy to prior rendered bitmap
				//////
					// Make sure our bmpPriorRendered exists
					obj->bmpPriorRendered = iBmp_verifyCopyIsSameSize(obj->bmpPriorRendered, obj->bmp);

					// Copy to the prior rendered version
					memcpy(obj->bmpPriorRendered->bd, obj->bmp->bd, obj->bmpPriorRendered->bi.biSizeImage);
					// Right now, we can use the bmpPriorRendered for a fast copy rather than 

			} else {
				// Render from its prior rendered version
				lnPixelsRendered += iBmp_bitBlt(obj->bmp, &lrc, obj->bmpPriorRendered);
			}

			// Indicate we're no longer dirty, that we have everything rendered, but it needs publishing
			obj->isDirtyRender = false;
			obj->isDirtyPublish	= true;
		}

		// Indicate status
		return(lnPixelsRendered);
	}




//////////
//
// Renders the column.
//
//////
	u32 iSubobj_renderColumn(SObject* obj)
	{
		u32		lnPixelsRendered;
		RECT	lrc;


		// Make sure our environment is sane
		logfunc(__FUNCTION__);
		lnPixelsRendered = 0;
		if (obj && obj->isRendered)
		{
			// Compute our rectangle for drawing
			SetRect(&lrc, 0, 0, obj->bmp->bi.biWidth, obj->bmp->bi.biHeight);
			if (obj->isDirtyRender)
			{
				// Render a white box as a placeholder
				iBmp_fillRect(obj->bmp, &lrc, whiteColor, whiteColor, whiteColor, whiteColor, false, NULL, false);


				//////////
				// Copy to prior rendered bitmap
				//////
					// Make sure our bmpPriorRendered exists
					obj->bmpPriorRendered = iBmp_verifyCopyIsSameSize(obj->bmpPriorRendered, obj->bmp);

					// Copy to the prior rendered version
					memcpy(obj->bmpPriorRendered->bd, obj->bmp->bd, obj->bmpPriorRendered->bi.biSizeImage);
					// Right now, we can use the bmpPriorRendered for a fast copy rather than 

			} else {
				// Render from its prior rendered version
				lnPixelsRendered += iBmp_bitBlt(obj->bmp, &lrc, obj->bmpPriorRendered);
			}

			// Indicate we're no longer dirty, that we have everything rendered, but it needs publishing
			obj->isDirtyRender = false;
			obj->isDirtyPublish	= true;
		}

		// Indicate status
		return(lnPixelsRendered);
	}




//////////
//
// Renders the header.
//
//////
	u32 iSubobj_renderHeader(SObject* obj)
	{
		u32		lnPixelsRendered;
		RECT	lrc;


		// Make sure our environment is sane
		logfunc(__FUNCTION__);
		lnPixelsRendered = 0;
		if (obj && obj->isRendered)
		{
			// Compute our rectangle for drawing
			SetRect(&lrc, 0, 0, obj->bmp->bi.biWidth, obj->bmp->bi.biHeight);
			if (obj->isDirtyRender)
			{
				// Render a white box as a placeholder
				iBmp_fillRect(obj->bmp, &lrc, whiteColor, whiteColor, whiteColor, whiteColor, false, NULL, false);


				//////////
				// Copy to prior rendered bitmap
				//////
					// Make sure our bmpPriorRendered exists
					obj->bmpPriorRendered = iBmp_verifyCopyIsSameSize(obj->bmpPriorRendered, obj->bmp);

					// Copy to the prior rendered version
					memcpy(obj->bmpPriorRendered->bd, obj->bmp->bd, obj->bmpPriorRendered->bi.biSizeImage);
					// Right now, we can use the bmpPriorRendered for a fast copy rather than 

			} else {
				// Render from its prior rendered version
				lnPixelsRendered += iBmp_bitBlt(obj->bmp, &lrc, obj->bmpPriorRendered);
			}

			// Indicate we're no longer dirty, that we have everything rendered, but it needs publishing
			obj->isDirtyRender = false;
			obj->isDirtyPublish	= true;
		}

		// Indicate status
		return(lnPixelsRendered);
	}




//////////
//
// Renders the oleBound.
//
//////
	u32 iSubobj_renderOleBound(SObject* obj)
	{
		u32		lnPixelsRendered;
		RECT	lrc;


		// Make sure our environment is sane
		logfunc(__FUNCTION__);
		lnPixelsRendered = 0;
		if (obj && obj->isRendered)
		{
			// Compute our rectangle for drawing
			SetRect(&lrc, 0, 0, obj->bmp->bi.biWidth, obj->bmp->bi.biHeight);
			if (obj->isDirtyRender)
			{
				// Render a white box as a placeholder
				iBmp_fillRect(obj->bmp, &lrc, whiteColor, whiteColor, whiteColor, whiteColor, false, NULL, false);


				//////////
				// Copy to prior rendered bitmap
				//////
					// Make sure our bmpPriorRendered exists
					obj->bmpPriorRendered = iBmp_verifyCopyIsSameSize(obj->bmpPriorRendered, obj->bmp);

					// Copy to the prior rendered version
					memcpy(obj->bmpPriorRendered->bd, obj->bmp->bd, obj->bmpPriorRendered->bi.biSizeImage);
					// Right now, we can use the bmpPriorRendered for a fast copy rather than 

			} else {
				// Render from its prior rendered version
				lnPixelsRendered += iBmp_bitBlt(obj->bmp, &lrc, obj->bmpPriorRendered);
			}

			// Indicate we're no longer dirty, that we have everything rendered, but it needs publishing
			obj->isDirtyRender = false;
			obj->isDirtyPublish	= true;
		}

		// Indicate status
		return(lnPixelsRendered);
	}




//////////
//
// Renders the oleContain.
//
//////
	u32 iSubobj_renderOleContain(SObject* obj)
	{
		u32		lnPixelsRendered;
		RECT	lrc;


		// Make sure our environment is sane
		logfunc(__FUNCTION__);
		lnPixelsRendered = 0;
		if (obj && obj->isRendered)
		{
			// Compute our rectangle for drawing
			SetRect(&lrc, 0, 0, obj->bmp->bi.biWidth, obj->bmp->bi.biHeight);
			if (obj->isDirtyRender)
			{
				// Render a white box as a placeholder
				iBmp_fillRect(obj->bmp, &lrc, whiteColor, whiteColor, whiteColor, whiteColor, false, NULL, false);


				//////////
				// Copy to prior rendered bitmap
				//////
					// Make sure our bmpPriorRendered exists
					obj->bmpPriorRendered = iBmp_verifyCopyIsSameSize(obj->bmpPriorRendered, obj->bmp);

					// Copy to the prior rendered version
					memcpy(obj->bmpPriorRendered->bd, obj->bmp->bd, obj->bmpPriorRendered->bi.biSizeImage);
					// Right now, we can use the bmpPriorRendered for a fast copy rather than 

			} else {
				// Render from its prior rendered version
				lnPixelsRendered += iBmp_bitBlt(obj->bmp, &lrc, obj->bmpPriorRendered);
			}

			// Indicate we're no longer dirty, that we have everything rendered, but it needs publishing
			obj->isDirtyRender = false;
			obj->isDirtyPublish	= true;
		}

		// Indicate status
		return(lnPixelsRendered);
	}




//////////
//
// Renders the spinner.
//
//////
	u32 iSubobj_renderSpinner(SObject* obj)
	{
		u32		lnPixelsRendered;
		RECT	lrc;


		// Make sure our environment is sane
		logfunc(__FUNCTION__);
		lnPixelsRendered = 0;
		if (obj && obj->isRendered)
		{
			// Compute our rectangle for drawing
			SetRect(&lrc, 0, 0, obj->bmp->bi.biWidth, obj->bmp->bi.biHeight);
			if (obj->isDirtyRender)
			{
				// Render a white box as a placeholder
				iBmp_fillRect(obj->bmp, &lrc, whiteColor, whiteColor, whiteColor, whiteColor, false, NULL, false);


				//////////
				// Copy to prior rendered bitmap
				//////
					// Make sure our bmpPriorRendered exists
					obj->bmpPriorRendered = iBmp_verifyCopyIsSameSize(obj->bmpPriorRendered, obj->bmp);

					// Copy to the prior rendered version
					memcpy(obj->bmpPriorRendered->bd, obj->bmp->bd, obj->bmpPriorRendered->bi.biSizeImage);
					// Right now, we can use the bmpPriorRendered for a fast copy rather than 

			} else {
				// Render from its prior rendered version
				lnPixelsRendered += iBmp_bitBlt(obj->bmp, &lrc, obj->bmpPriorRendered);
			}

			// Indicate we're no longer dirty, that we have everything rendered, but it needs publishing
			obj->isDirtyRender = false;
			obj->isDirtyPublish	= true;
		}

		// Indicate status
		return(lnPixelsRendered);
	}




//////////
//
// Renders the timer.
//
//////
	u32 iSubobj_renderTimer(SObject* obj)
	{
		u32		lnPixelsRendered;
		RECT	lrc;


		// Make sure our environment is sane
		logfunc(__FUNCTION__);
		lnPixelsRendered = 0;
		if (obj && obj->isRendered)
		{
			// Compute our rectangle for drawing
			SetRect(&lrc, 0, 0, obj->bmp->bi.biWidth, obj->bmp->bi.biHeight);
			if (obj->isDirtyRender)
			{
				// Render a white box as a placeholder
				iBmp_fillRect(obj->bmp, &lrc, whiteColor, whiteColor, whiteColor, whiteColor, false, NULL, false);


				//////////
				// Copy to prior rendered bitmap
				//////
					// Make sure our bmpPriorRendered exists
					obj->bmpPriorRendered = iBmp_verifyCopyIsSameSize(obj->bmpPriorRendered, obj->bmp);

					// Copy to the prior rendered version
					memcpy(obj->bmpPriorRendered->bd, obj->bmp->bd, obj->bmpPriorRendered->bi.biSizeImage);
					// Right now, we can use the bmpPriorRendered for a fast copy rather than 

			} else {
				// Render from its prior rendered version
				lnPixelsRendered += iBmp_bitBlt(obj->bmp, &lrc, obj->bmpPriorRendered);
			}

			// Indicate we're no longer dirty, that we have everything rendered, but it needs publishing
			obj->isDirtyRender = false;
			obj->isDirtyPublish	= true;
		}

		// Indicate status
		return(lnPixelsRendered);
	}




//////////
//
// Renders the hyperlink.
//
//////
	u32 iSubobj_renderHyperlink(SObject* obj)
	{
		u32		lnPixelsRendered;
		RECT	lrc;


		// Make sure our environment is sane
		logfunc(__FUNCTION__);
		lnPixelsRendered = 0;
		if (obj && obj->isRendered)
		{
			// Compute our rectangle for drawing
			SetRect(&lrc, 0, 0, obj->bmp->bi.biWidth, obj->bmp->bi.biHeight);
			if (obj->isDirtyRender)
			{
				// Render a white box as a placeholder
				iBmp_fillRect(obj->bmp, &lrc, whiteColor, whiteColor, whiteColor, whiteColor, false, NULL, false);


				//////////
				// Copy to prior rendered bitmap
				//////
					// Make sure our bmpPriorRendered exists
					obj->bmpPriorRendered = iBmp_verifyCopyIsSameSize(obj->bmpPriorRendered, obj->bmp);

					// Copy to the prior rendered version
					memcpy(obj->bmpPriorRendered->bd, obj->bmp->bd, obj->bmpPriorRendered->bi.biSizeImage);
					// Right now, we can use the bmpPriorRendered for a fast copy rather than 

			} else {
				// Render from its prior rendered version
				lnPixelsRendered += iBmp_bitBlt(obj->bmp, &lrc, obj->bmpPriorRendered);
			}

			// Indicate we're no longer dirty, that we have everything rendered, but it needs publishing
			obj->isDirtyRender = false;
			obj->isDirtyPublish	= true;
		}

		// Indicate status
		return(lnPixelsRendered);
	}




//////////
//
// Renders the collection.
//
//////
	u32 iSubobj_renderCollection(SObject* obj)
	{
		u32		lnPixelsRendered;
		RECT	lrc;


		// Make sure our environment is sane
		logfunc(__FUNCTION__);
		lnPixelsRendered = 0;
		if (obj && obj->isRendered)
		{
			// Compute our rectangle for drawing
			SetRect(&lrc, 0, 0, obj->bmp->bi.biWidth, obj->bmp->bi.biHeight);
			if (obj->isDirtyRender)
			{
				// Render a white box as a placeholder
				iBmp_fillRect(obj->bmp, &lrc, whiteColor, whiteColor, whiteColor, whiteColor, false, NULL, false);


				//////////
				// Copy to prior rendered bitmap
				//////
					// Make sure our bmpPriorRendered exists
					obj->bmpPriorRendered = iBmp_verifyCopyIsSameSize(obj->bmpPriorRendered, obj->bmp);

					// Copy to the prior rendered version
					memcpy(obj->bmpPriorRendered->bd, obj->bmp->bd, obj->bmpPriorRendered->bi.biSizeImage);
					// Right now, we can use the bmpPriorRendered for a fast copy rather than 

			} else {
				// Render from its prior rendered version
				lnPixelsRendered += iBmp_bitBlt(obj->bmp, &lrc, obj->bmpPriorRendered);
			}

			// Indicate we're no longer dirty, that we have everything rendered, but it needs publishing
			obj->isDirtyRender = false;
			obj->isDirtyPublish	= true;
		}

		// Indicate status
		return(lnPixelsRendered);
	}




//////////
//
// Renders the page.
//
//////
	u32 iSubobj_renderPage(SObject* obj)
	{
		u32		lnPixelsRendered;
		RECT	lrc;


		// Make sure our environment is sane
		logfunc(__FUNCTION__);
		lnPixelsRendered = 0;
		if (obj && obj->isRendered)
		{
			// Compute our rectangle for drawing
			SetRect(&lrc, 0, 0, obj->bmp->bi.biWidth, obj->bmp->bi.biHeight);
			if (obj->isDirtyRender)
			{
				// Render a white box as a placeholder
				iBmp_fillRect(obj->bmp, &lrc, whiteColor, whiteColor, whiteColor, whiteColor, false, NULL, false);


				//////////
				// Copy to prior rendered bitmap
				//////
					// Make sure our bmpPriorRendered exists
					obj->bmpPriorRendered = iBmp_verifyCopyIsSameSize(obj->bmpPriorRendered, obj->bmp);

					// Copy to the prior rendered version
					memcpy(obj->bmpPriorRendered->bd, obj->bmp->bd, obj->bmpPriorRendered->bi.biSizeImage);
					// Right now, we can use the bmpPriorRendered for a fast copy rather than 

			} else {
				// Render from its prior rendered version
				lnPixelsRendered += iBmp_bitBlt(obj->bmp, &lrc, obj->bmpPriorRendered);
			}

			// Indicate we're no longer dirty, that we have everything rendered, but it needs publishing
			obj->isDirtyRender = false;
			obj->isDirtyPublish	= true;
		}

		// Indicate status
		return(lnPixelsRendered);
	}




//////////
//
// Renders the pageFrame.
//
//////
	u32 iSubobj_renderPageFrame(SObject* obj)
	{
		u32		lnPixelsRendered;
		RECT	lrc;


		// Make sure our environment is sane
		logfunc(__FUNCTION__);
		lnPixelsRendered = 0;
		if (obj && obj->isRendered)
		{
			// Compute our rectangle for drawing
			SetRect(&lrc, 0, 0, obj->bmp->bi.biWidth, obj->bmp->bi.biHeight);
			if (obj->isDirtyRender)
			{
				// Render a white box as a placeholder
				iBmp_fillRect(obj->bmp, &lrc, whiteColor, whiteColor, whiteColor, whiteColor, false, NULL, false);


				//////////
				// Copy to prior rendered bitmap
				//////
					// Make sure our bmpPriorRendered exists
					obj->bmpPriorRendered = iBmp_verifyCopyIsSameSize(obj->bmpPriorRendered, obj->bmp);

					// Copy to the prior rendered version
					memcpy(obj->bmpPriorRendered->bd, obj->bmp->bd, obj->bmpPriorRendered->bi.biSizeImage);
					// Right now, we can use the bmpPriorRendered for a fast copy rather than 

			} else {
				// Render from its prior rendered version
				lnPixelsRendered += iBmp_bitBlt(obj->bmp, &lrc, obj->bmpPriorRendered);
			}

			// Indicate we're no longer dirty, that we have everything rendered, but it needs publishing
			obj->isDirtyRender = false;
			obj->isDirtyPublish	= true;
		}

		// Indicate status
		return(lnPixelsRendered);
	}




//////////
//
// Renders the session.
//
//////
	u32 iSubobj_renderSession(SObject* obj)
	{
		u32		lnPixelsRendered;
		RECT	lrc;


		// Make sure our environment is sane
		logfunc(__FUNCTION__);
		lnPixelsRendered = 0;
		if (obj && obj->isRendered)
		{
			// Compute our rectangle for drawing
			SetRect(&lrc, 0, 0, obj->bmp->bi.biWidth, obj->bmp->bi.biHeight);
			if (obj->isDirtyRender)
			{
				// Render a white box as a placeholder
				iBmp_fillRect(obj->bmp, &lrc, whiteColor, whiteColor, whiteColor, whiteColor, false, NULL, false);


				//////////
				// Copy to prior rendered bitmap
				//////
					// Make sure our bmpPriorRendered exists
					obj->bmpPriorRendered = iBmp_verifyCopyIsSameSize(obj->bmpPriorRendered, obj->bmp);

					// Copy to the prior rendered version
					memcpy(obj->bmpPriorRendered->bd, obj->bmp->bd, obj->bmpPriorRendered->bi.biSizeImage);
					// Right now, we can use the bmpPriorRendered for a fast copy rather than 

			} else {
				// Render from its prior rendered version
				lnPixelsRendered += iBmp_bitBlt(obj->bmp, &lrc, obj->bmpPriorRendered);
			}

			// Indicate we're no longer dirty, that we have everything rendered, but it needs publishing
			obj->isDirtyRender = false;
			obj->isDirtyPublish	= true;
		}

		// Indicate status
		return(lnPixelsRendered);
	}




//////////
//
// Renders the custom.
//
//////
	u32 iSubobj_renderCustom(SObject* obj)
	{
		u32		lnPixelsRendered;
		RECT	lrc;


		// Make sure our environment is sane
		logfunc(__FUNCTION__);
		lnPixelsRendered = 0;
		if (obj && obj->isRendered)
		{
			// Compute our rectangle for drawing
			SetRect(&lrc, 0, 0, obj->bmp->bi.biWidth, obj->bmp->bi.biHeight);
			if (obj->isDirtyRender)
			{
				// Render a white box as a placeholder
				iBmp_fillRect(obj->bmp, &lrc, whiteColor, whiteColor, whiteColor, whiteColor, false, NULL, false);


				//////////
				// Copy to prior rendered bitmap
				//////
					// Make sure our bmpPriorRendered exists
					obj->bmpPriorRendered = iBmp_verifyCopyIsSameSize(obj->bmpPriorRendered, obj->bmp);

					// Copy to the prior rendered version
					memcpy(obj->bmpPriorRendered->bd, obj->bmp->bd, obj->bmpPriorRendered->bi.biSizeImage);
					// Right now, we can use the bmpPriorRendered for a fast copy rather than 

			} else {
				// Render from its prior rendered version
				lnPixelsRendered += iBmp_bitBlt(obj->bmp, &lrc, obj->bmpPriorRendered);
			}

			// Indicate we're no longer dirty, that we have everything rendered, but it needs publishing
			obj->isDirtyRender = false;
			obj->isDirtyPublish	= true;
		}

		// Indicate status
		return(lnPixelsRendered);
	}




//////////
//
// Renders the exception.
//
//////
	u32 iSubobj_renderException(SObject* obj)
	{
		u32		lnPixelsRendered;
		RECT	lrc;


		// Make sure our environment is sane
		logfunc(__FUNCTION__);
		lnPixelsRendered = 0;
		if (obj && obj->isRendered)
		{
			// Compute our rectangle for drawing
			SetRect(&lrc, 0, 0, obj->bmp->bi.biWidth, obj->bmp->bi.biHeight);
			if (obj->isDirtyRender)
			{
				// Render a white box as a placeholder
				iBmp_fillRect(obj->bmp, &lrc, whiteColor, whiteColor, whiteColor, whiteColor, false, NULL, false);


				//////////
				// Copy to prior rendered bitmap
				//////
					// Make sure our bmpPriorRendered exists
					obj->bmpPriorRendered = iBmp_verifyCopyIsSameSize(obj->bmpPriorRendered, obj->bmp);

					// Copy to the prior rendered version
					memcpy(obj->bmpPriorRendered->bd, obj->bmp->bd, obj->bmpPriorRendered->bi.biSizeImage);
					// Right now, we can use the bmpPriorRendered for a fast copy rather than 

			} else {
				// Render from its prior rendered version
				lnPixelsRendered += iBmp_bitBlt(obj->bmp, &lrc, obj->bmpPriorRendered);
			}

			// Indicate we're no longer dirty, that we have everything rendered, but it needs publishing
			obj->isDirtyRender = false;
			obj->isDirtyPublish	= true;
		}

		// Indicate status
		return(lnPixelsRendered);
	}




//////////
//
// Renders the settings.
//
//////
	u32 iSubobj_renderSettings(SObject* obj)
	{
		u32		lnPixelsRendered;
		RECT	lrc;


		// Make sure our environment is sane
		logfunc(__FUNCTION__);
		lnPixelsRendered = 0;
		if (obj && obj->isRendered)
		{
			// Compute our rectangle for drawing
			SetRect(&lrc, 0, 0, obj->bmp->bi.biWidth, obj->bmp->bi.biHeight);
			if (obj->isDirtyRender)
			{
				// Render a white box as a placeholder
				iBmp_fillRect(obj->bmp, &lrc, whiteColor, whiteColor, whiteColor, whiteColor, false, NULL, false);


				//////////
				// Copy to prior rendered bitmap
				//////
					// Make sure our bmpPriorRendered exists
					obj->bmpPriorRendered = iBmp_verifyCopyIsSameSize(obj->bmpPriorRendered, obj->bmp);

					// Copy to the prior rendered version
					memcpy(obj->bmpPriorRendered->bd, obj->bmp->bd, obj->bmpPriorRendered->bi.biSizeImage);
					// Right now, we can use the bmpPriorRendered for a fast copy rather than 

			} else {
				// Render from its prior rendered version
				lnPixelsRendered += iBmp_bitBlt(obj->bmp, &lrc, obj->bmpPriorRendered);
			}

			// Indicate we're no longer dirty, that we have everything rendered, but it needs publishing
			obj->isDirtyRender = false;
			obj->isDirtyPublish	= true;
		}

		// Indicate status
		return(lnPixelsRendered);
	}




//////////
//
// Renders the control point.
//
//////
	u32 iSubobj_renderControlPoint(SObject* obj)
	{
		u32		lnPixelsRendered;
		RECT	lrc;


		// Make sure our environment is sane
		logfunc(__FUNCTION__);
		lnPixelsRendered = 0;
		if (obj && obj->isRendered)
		{
			// Compute our rectangle for drawing
			SetRect(&lrc, 0, 0, obj->bmp->bi.biWidth, obj->bmp->bi.biHeight);
			if (obj->isDirtyRender)
			{
				// Render a white box as a placeholder
				iBmp_fillRect(obj->bmp, &lrc, whiteColor, whiteColor, whiteColor, whiteColor, false, NULL, false);


				//////////
				// Copy to prior rendered bitmap
				//////
					// Make sure our bmpPriorRendered exists
					obj->bmpPriorRendered = iBmp_verifyCopyIsSameSize(obj->bmpPriorRendered, obj->bmp);

					// Copy to the prior rendered version
					memcpy(obj->bmpPriorRendered->bd, obj->bmp->bd, obj->bmpPriorRendered->bi.biSizeImage);
					// Right now, we can use the bmpPriorRendered for a fast copy rather than 

			} else {
				// Render from its prior rendered version
				lnPixelsRendered += iBmp_bitBlt(obj->bmp, &lrc, obj->bmpPriorRendered);
			}

			// Indicate we're no longer dirty, that we have everything rendered, but it needs publishing
			obj->isDirtyRender = false;
			obj->isDirtyPublish	= true;
		}

		// Indicate status
		return(lnPixelsRendered);
	}
