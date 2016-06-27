//////////
//
// /libsf/source/vjr/source/fonts.cpp
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
//     Nov.27.2014
//////
// Change log:
//     Nov.27.2014 - Initial creation
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
// Called to duplicate a font that was found from the list of known system fonts
//
//////
	SFont* iFont_duplicate(SFont* fontSource)
	{
		SFont* font;


		// Make sure our environment is sane
		font = NULL;
		if (fontSource)
		{
			// Allocate a copy
			return(iFont_create(fontSource->name.data_cu8, fontSource->_size, fontSource->_weight, ((fontSource->isItalic) ? 1 : 0), ((fontSource->isUnderline) ? 1 : 0)));
		}

		// Indicate our success or failure
		return(font);
	}





//////////
//
// Create a new font
//
//////
	SFont* iFont_create(SObject* obj)
	{
		bool		llBold, llItalic, llUnderline;
		SVariable*	varName;
		SVariable*	varPointSize;


		//////////
		// Make sure our environment is sane
		//////
			if (obj && (varName = iObjProp_get_var_byIndex(obj, _INDEX_FONTNAME)) && (varPointSize = iObjProp_get_var_byIndex(obj, _INDEX_FONTSIZE)))
			{
				// Grab the criteria
				llBold			= iiVariable_getAs_bool(iObjProp_get_logical(obj, _INDEX_FONTBOLD));
				llItalic		= iiVariable_getAs_bool(iObjProp_get_logical(obj, _INDEX_FONTITALIC));
				llUnderline		= iiVariable_getAs_bool(iObjProp_get_logical(obj, _INDEX_FONTUNDERLINE));

				// cgcFontName_windowTitleBar, 10, FW_BOLD, false, false);
				return(iFont_create(
										((varName) ? varName->value.data_cu8 : cgcFontName_default),
										iiVariable_getAs_u32(varPointSize),
										((llBold)		? FW_BOLD	: FW_NORMAL),
										((llItalic)		? 1			: 0),
										((llUnderline)	? 1			: 0)
								));
			}


		//////////
		// If we get here, error
		//////
			error_silent;
			return(iFont_create(cgcFontName_default, gnFont_defaultPointSize, FW_BOLD, 0, 0));

	}
	
	SFont* iFont_create(cu8* tcFontName, u32 tnFontSize, u32 tnFontWeight, u32 tnItalics, u32 tnUnderline)
	{
		s32		lnLength;
		u32		lnI;
		SFont*	font;
		SFont*	fontFirstUnused;


		//////////
		// See if there is an unused slot
		//////
			fontFirstUnused	= NULL;
			lnLength		= (s32)strlen((s8*)tcFontName);
			for (lnI = 0; lnI < gFonts->populatedLength; lnI += sizeof(SFont))
			{
				// Grab the pointer
				font = (SFont*)(gFonts->data_u8 + lnI);

				// If used
				if (!font->isUsed)
				{
					// Mark this one if we haven't found a free slot yet
					fontFirstUnused = font;
					break;
				}
			}


		//////////
		// Allocate a new pointer
		//////
			if (!fontFirstUnused)		font = (SFont*)iBuilder_allocateBytes(gFonts, sizeof(SFont));
			else						font = fontFirstUnused;

			// Double-check
			if (!font)
				return(font);

			// Initialize
			memset(font, 0, sizeof(SFont));


		//////////
		// Populate
		//////
			font->isUsed					= true;
			font->hdc						= CreateCompatibleDC(GetDC(GetDesktopWindow()));
			iDatum_duplicate(&font->name, tcFontName, lnLength + 1);
			font->_size						= tnFontSize;
			font->_weight					= tnFontWeight;
			font->_italics					= tnItalics;
			font->_underline				= tnUnderline;
			font->isItalic					= ((tnItalics == 0)				? false : true);
			font->isBold					= ((tnFontWeight > FW_NORMAL)	? true : false);
			font->isUnderline				= ((tnUnderline == 0)			? false : true);
			iiFont_refresh(font);


		// Indicate our success
		return(font);
	}




//////////
//
// Change the font size
//
//////
	SFont* iFont_bigger(SFont* font, bool tlDeleteAfterCreateNew)
	{
		SFont* fontNew;


		// Make sure our environment is sane
		if (font && font->_size <= 128)
		{
			// Create the larger font
			fontNew = font;
			fontNew = iFont_create(fontNew->name.data_cu8, fontNew->_size + 1, fontNew->_weight, ((fontNew->isItalic) ? 1 : 0), ((fontNew->isUnderline) ? 1 : 0));
			if (!fontNew)
				return(font);

			// Delete the reference font if instructed
			if (tlDeleteAfterCreateNew)
				iFont_delete(&font, true);

			// Indicate our status
			return(fontNew);
		}
		// If we get here, failure
		return(font);
	}

	SFont* iFont_smaller(SFont* font, bool tlDeleteAfterCreateNew)
	{
		SFont* fontNew;


		// Make sure our environment is sane
		if (font && font->_size >= 4)
		{
			// Create the larger font
			fontNew = font;
			fontNew = iFont_create(fontNew->name.data_cu8, fontNew->_size - 1, fontNew->_weight, ((fontNew->isItalic) ? 1 : 0), ((fontNew->isUnderline) ? 1 : 0));
			if (!fontNew)
				return(font);

			// Delete the reference font if instructed
			if (tlDeleteAfterCreateNew)
				iFont_delete(&font, true);

			// Indicate our status
			return(fontNew);
		}
		// If we get here, failure
		return(font);
	}




//////////
//
// Called typically after some setting on the font is changed to "refresh"
// the font with the new settings in its device context.
//
//////
	void iiFont_refresh(SFont* font)
	{
		//////////
		// Create the font
		//////
			font->_sizeUsedForCreateFont	= -MulDiv(font->_size, GetDeviceCaps(GetDC(GetDesktopWindow()), LOGPIXELSY), 72);
			font->hfont						= CreateFont(font->_sizeUsedForCreateFont, 0, 0, 0, font->_weight, (font->isItalic ? 1 : 0), (font->isUnderline ? 1 : 0), false, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_NATURAL_QUALITY, FF_DONTCARE, font->name.data_s8);

			// Find out the text metrics
			GetTextMetricsA(font->hdc, &font->tm);


		//////////
		// Select the font into its context
		//////
			SelectObject(font->hdc, font->hfont);
	}




//////////
//
// Free the indicated font resource
//
//////
	void iFont_delete(SFont** fontRoot, bool tlDeleteSelf)
	{
		SFont* font;


		if (fontRoot && *fontRoot)
		{
			// Grab our pointer
			font = *fontRoot;


			//////////
			// Free components
			//////
				DeleteObject((HGDIOBJ)font->hfont);
				DeleteDC(font->hdc);
				iDatum_delete(&font->name, false);


			//////////
			// Free self
			//////
				if (tlDeleteSelf && ((uptr)font < gFonts->_data || (uptr)font > (gFonts->_data + gFonts->populatedLength)))
				{
					// Delete the memory block
					free(font);
					*fontRoot = NULL;

				} else {
					// Just mark it unused
					font->isUsed = false;
				}
		}
	}




//////////
//
// Called to release all fonts allocated in this block
//
//////
	void iFont_releaseAll(SBuilder* fontRoot, bool tlDeleteSelf)
	{
		u32		lnI;
		SFont*	font;


		// Make sure our environment is sane
		if (fontRoot)
		{
			//////////
			// Delete all allocated fonts
			//////
				for (lnI = 0; lnI < fontRoot->populatedLength; lnI += sizeof(SFont))
				{
					// Grab the pointer
					font = (SFont*)(fontRoot->data_u8 + lnI);

					// Delete this font
					if (font->isUsed)
					{
						iFont_delete(&font, false);	// Delete the font
						font->isUsed = false;		// Mark the slot unused
					}
				}


			//////////
			// Delete self
			//////
				if (tlDeleteSelf)
					iBuilder_freeAndRelease(&fontRoot);
		}
	}




//////////
//
// A particular font occupies a certain physical amount of text relative to the rectangle it inhabits.
// In order for this font to be scaled up, the font dynamics will need to change somewhat as per the limitations
// within the font design.  As such, we have to scan upward to find the closest matching font that is equal to
// or less than the ratios indicated at the current size, yet for the desired size.
//
//////
	u32 iFont_findClosestSizeMatch(s8* tcText, cu8* tcFontName, u32 tnFontSize, u32 tnFontBold, u32 tnFontItalic, u32 tnFontUnderline, u32 tnWidth, u32 tnHeight, u32 tnWidthDesired, u32 tnHeightDesired)
	{
		s32			lnI, lnJ, lnTextLength, lnFontBold;
		f64			lfRatioH, lfRatioV, lfRatioHThis, lfRatioVThis;
		SSize		size[200];
		RECT		lrc;
		SFont*		font;


		// Iterate from the current size upward for a maximum of 200 font point sizes, but also not more than 3x its current point size
		lnTextLength	= (s32)strlen(tcText);
		lnFontBold		= ((tnFontBold) ? FW_BOLD : FW_NORMAL);
		SetRect(&lrc, 0, 0, 0, 0);
		for (lnI = 0; lnI == 0 || (lnI < 200 && (s32)(tnFontSize + lnI) < (s32)(tnFontSize * 3) && lrc.bottom < (s32)((f32)tnHeightDesired * 1.25f) && lrc.right < (s32)((f32)tnWidthDesired * 1.25f)); lnI++)
		{
			// Grab this font
			font = iFont_create(tcFontName, tnFontSize + lnI, lnFontBold, tnFontItalic, tnFontUnderline);

			// Find out how big this font would be drawn for this text
			SetRect(&lrc, 0, 0, 0, 0);
			DrawText(font->hdc, tcText, lnTextLength, &lrc, DT_CALCRECT);
			size[lnI].fWidth	= (f32)(lrc.right - lrc.left);
			size[lnI].fHeight	= (f32)(lrc.bottom - lrc.top);
		}
		// When we get here, we have all of the fonts computed
		// size[0] contains the raw font
		// We search for size[1..N] which has the font which most closely matches its proportions for the tnWidthDesired, tnHeightDesired,
		// as per the ratio

		// Compute the size[0]
		lfRatioH	= (f64)(size[0].fWidth)  / (f64)tnWidth;
		lfRatioV	= (f64)(size[0].fHeight) / (f64)tnHeight;

		// Search backwards to find the first one that matches
		for (lnJ = lnI - 1; lnJ > 0; lnJ--)
		{
			if ((s32)size[lnJ].fWidth <= (s32)tnWidthDesired && (s32)size[lnJ].fHeight <= (s32)tnHeightDesired)
			{
				// Calculate this item's size
				lfRatioHThis	= (f64)(size[lnJ].fWidth)  / (f64)tnWidthDesired;
				lfRatioVThis	= (f64)(size[lnJ].fHeight) / (f64)tnHeightDesired;

				// See if we've found our font
				if (lfRatioHThis <= lfRatioH && lfRatioVThis <= lfRatioV)
					return(tnFontSize + (u32)lnJ);
			}
		}
		// If we get here, we couldn't find one ... indicate failure
		return(0);
	}
