//////////
//
// /libsf/utils/dsf/msvc++/dsf/dsf/dsf.cpp
//
//////
//
//
//////
// Version 0.60
// Copyright (c) 2013 by Rick C. Hodgin
//////
// Last update:
//     Dec.02.2013
//////
// Change log:
//     Dec.02.2013	- Initial creation
//////
//
// Top-level program for DSF.DLL. Contains all helper algorithms for creating binary characters
// of existing font sets for translation into the DSF format.
//
//////////
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
//     http://www.visual-freepro.org
//     http://www.visual-freepro.org/blog/
//     http://www.visual-freepro.org/forum/
//     http://www.visual-freepro.org/wiki/
//     http://www.visual-freepro.org/wiki/index.php/PBL
//     http://www.visual-freepro.org/wiki/index.php/Repeat_License
//
// Thank you.  And may The Lord bless you richly as you lift up your life, your
// talents, your gifts, your praise, unto Him.  In Jesus' name I pray.  Amen.
//
//////




#include "dsf_dll.h"




//////////
//
// Main DLL entry point
//
//////
	BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
	{
		//////////
		// Store the instance for global use
		//////
			ghInstance = hModule;


		//////////
		// Windows tells us why we're being invoked
		//////
			switch (ul_reason_for_call)
			{
				case DLL_PROCESS_ATTACH:
					initialize();
					break;
				case DLL_THREAD_ATTACH:
				case DLL_THREAD_DETACH:
				case DLL_PROCESS_DETACH:
					break;
			}
			return TRUE;
	}




//////////
//
// Called to obtain the bitmap of the indicated character.
//
//////
	int dsf_get_character_bitmap(int tnAscii, s8* tcBitmapFilename, s8* tcFloanFilename, s8* tcFontName, int tnHeight, int tnWidth)
	{
		return(iDsf_get_character_bitmap(tnAscii, tcBitmapFilename, tcFloanFilename, tcFontName, tnHeight, tnWidth));
	}




//////////
//
// Called to scale a bitmap to the indicated size, and clip it to some other portion.  This
// algorithm was created to allow the user to obtain a font from dsf_get_character_bitmap(),
// but then to override the default generated image to make it resized appropriately for the
// target font.
//
//////
	int dsf_scale_and_clip_bitmap(s8* tcBitmapFilenameIn, s8* tcBitmapFilenameOut, f64 tfWidth, f64 tfHeight, int tnClipLeft, int tnClipTop, int tnNewWidth, int tnNewHeight)
	{
		return(iDsf_scale_and_clip_bitmap(tcBitmapFilenameIn, tcBitmapFilenameOut, tfWidth, tfHeight, tnClipLeft, tnClipTop, tnNewWidth, tnNewHeight));
	}




//////////
//
//  Called to initiate a new session of editing.
//
//////
	int dsf_create_new_instance(void)
	{
		return(iDsf_create_new_instance());
	}




//////////
//
// Called to set the data for the font instance
//
//////
	int dsf_load_font(u32 tnInstance,	f64 tfAscent,	f64 tfUpper,	f64 tfLower,		f64 tfLeft,			f64 tfRight,
										f64 tfBase,		f64 tfDescent,	f64 tfWidth,
										f64 tfItalics,	f64 tfBold,		f64 tfUnderTop,		f64 tfUnderBot,		f64 tfStrikeTop,	f64 tfStrikeBot)
	{
		return(iDsf_load_font(	tnInstance,	tfAscent,	tfUpper,		tfLower,	tfLeft,			tfRight,
								tfBase,		tfDescent,	tfWidth,
								tfItalics,	tfBold,		tfUnderTop,		tfUnderBot,	tfStrikeTop,	tfStrikeBot	));
	}




//////////
//
// Called to load a character with its data based on (u8)tnType (S=Spline, D=Definition,
// R=Reference, L=Link). For Definition entries, tiid must be above the standard 0..255 ASCII
// character range.  Reference entries will be in the 0..255 range, but tiLnkId must refer to
// an entry 256 or above.  Link entries can refer to any item, but must also include tiLnkOrder
// to indicate what explicit item they want to modify.
//
//////
	int dsf_load_character(u32 tnInstance,	u32 tnType, u32 tiid, u32 tiOrder, s8* tcDesc10, u32 tlNewStroke, u32 tlSelected,
											f64 tfOx, f64 tfOy, f64 tfOt, f64 tfLr, f64 tfLt, f64 tfRr, f64 tfRt, 
											u32 tiSubdivs, u32 tiLnkId, u32 tiLnkOrder)
	{
		return(iDsf_load_character(	tnInstance,	tnType, tiid, tiOrder, tcDesc10, tlNewStroke, tlSelected,
									tfOx, tfOy, tfOt, tfLr, tfLt, tfRr, tfRt, 
									tiSubdivs, tiLnkId, tiLnkOrder	));
	}




//////////
//
// Called to load the indicated instance.  We search to see if a previous entry has been added
// with this information.  If so, it's updated.  If not, it's appended.
//
//////
	int dsf_load_reference(u32 tnInstance,	u32 tnType, s8* tcDesc40,
											f64 tfRef1X, f64 tfRef1Y,
											f64 tfRef2X, f64 tfRef2Y,
											f64 tfRef3X, f64 tfRef3Y,
											f64 tfRef4X, f64 tfRef4Y,
											f64 tfRef5X, f64 tfRef5Y,
											bool tlVisible, s8* tcChars1_128, s8* tcChars2_128)
	{
		return(iDsf_load_reference(	tnInstance,		tnType,		tcDesc40,
													tfRef1X,	tfRef1Y,
													tfRef2X,	tfRef2Y,
													tfRef3X,	tfRef3Y,
													tfRef4X,	tfRef4Y,
													tfRef5X,	tfRef5Y,
													tlVisible,	tcChars1_128,	tcChars2_128	));
	}




//////////
//
// Called to load the indicated instance.  We search to see if a previous entry has been added
// with this information.  If so, it's updated.  If not, it's appended.
//
//////
	int dsf_load_template(u32 tnInstance, u32 tipid, f64 tfX, f64 tfY, u32 tnRecno)
	{
		return(iDsf_load_template(tnInstance, tipid, tfX, tfY, tnRecno));
	}




//////////
//
// Called once all of the initial loading of data is complete.
//
//////
	void dsf_initial_load_complete(u32 tnInstance, u32 tnWidth, u32 tnHeight)
	{
		return(iDsf_initial_load_complete(tnInstance, tnWidth, tnHeight));
	}




//////////
//
// Called to load the indicated instance.  We search to see if a previous entry has been added
// with this information.  If so, it's updated.  If not, it's appended.
//
//////
	int dsf_get_changed_template(u32 tnInstance, u32 tipid, s8* tcY12, s8* tcX12, s8* tcRecno12, u32 tnNextNewRecno)
	{
		return(iDsf_get_changed_template(tnInstance, tipid, tcY12, tcX12, tcRecno12, tnNextNewRecno));
	}




//////////
//
// Called to load the indicated instance.  We search to see if a previous entry has been added
// with this information.  If so, it's updated.  If not, it's appended.
//
//////
	int dsf_get_deleted_template(u32 tnInstance, u32 tipid, s8* tcRecno12)
	{
		return(iDsf_get_deleted_template(tnInstance, tipid, tcRecno12));
	}




//////////
//
// Called to set the cues the user wants to see, along with whether or not the mouse should track
// near to any of the specified cues.  Will NOT issue a redraw.  Use dsf_user_cues() and then
// dsf_user_cues2() for updating cues, and then use dsf_user_settings() to issue the redraw.
//
//////
	int dsf_user_cues(u32 tnInstance,	u32 tnAscent,			u32 tnTrackAscent, 
										u32 tnUpper,			u32 tnTrackUpper, 
										u32 tnLower,			u32 tnTrackLower, 
										u32 tnBase,				u32 tnTrackBase, 
										u32 tnDescent,			u32 tnTrackDescent, 
										u32 tnStrikethrough,	u32 tnTrackStrike, 
										u32 tnUnderline,		u32 tnTrackUnderline, 
										u32 tnRefs,				u32 tnTrackRefs)
	{
		return(iDsf_user_cues(	tnInstance,		tnAscent,			tnTrackAscent, 
												tnUpper,			tnTrackUpper, 
												tnLower,			tnTrackLower, 
												tnBase,				tnTrackBase, 
												tnDescent,			tnTrackDescent, 
												tnStrikethrough,	tnTrackStrike, 
												tnUnderline,		tnTrackUnderline, 
												tnRefs,				tnTrackRefs		));
	}

	int dsf_user_cues2(u32 tnInstance,	u32 tlLeft,		u32 tnTrackLeft, 
										u32 tlRight,	u32 tnTrackRight, 
										u32 tlWidth,	u32 tnTrackWidth, 
										u32 tlTems,		u32 tnTrackTems,
										u32 tlGrid,		u32 tnTrackGrid)
	{
		return(iDsf_user_cues2(	tnInstance,	tlLeft,		tnTrackLeft, 
								tlRight,	tnTrackRight, 
								tlWidth,	tnTrackWidth, 
								tlTems,		tnTrackTems,
								tlGrid,		tnTrackGrid	));
	}




//////////
//
// Called to convey user settings.  Will issue a redraw.
//
//////
	int dsf_user_settings(u32 tnInstance,
							u32 tnDisposition, u32 tnMode, u32 tnMethod, u32 tnRange,
							u32 tlShowSplines, u32 tnSplinesType,
							u32 tlHighlighSelection, u32 tlShowPenDowns,
							u32 tlMouseCrosshairX, u32 tlMouseCrosshairY,
							u32 tlInvert,
							u32 tlZoomLens,
							u32 tlCuesUnder, 
							u32 tnSelectArea)
	{
		return(iDsf_user_settings(	tnInstance,
									tnDisposition, tnMode, tnMethod, tnRange,
									tlShowSplines, tnSplinesType,
									tlHighlighSelection, tlShowPenDowns,
									tlMouseCrosshairX, tlMouseCrosshairY,
									tlInvert,
									tlZoomLens,
									tlCuesUnder, 
									tnSelectArea	));
	}




//////////
//
// Called to indicate the user wants to make active another character for editing.  Will issue a redraw.
//
//////
	int dsf_set_active_character(u32 tnInstance, u32 tiid)
	{
		return(iDsf_set_active_character(tnInstance, tiid));
	}




//////////
//
// Called to indicate what tool the user wants to use.  Will issue a redraw.
//
//////
	int dsf_set_active_tool(u32 tnInstance, u32 tnToolNumber)
	{
		return(iDsf_set_active_tool(tnInstance, tnToolNumber));
	}




//////////
//
// Called to capture the contents of the indicated window to a disk file.
//
//////////
//
// Note:  In general, minimized windows can't be captured.
// Note:  However, if the window is minimized it can still be captured using a type of hack.
// Note:  This must be done in rapid succession.  In general, it will be, but it remains slower than capturing a visible window.
// Steps:
// (1) Disable the MinAnimate() effect globally:
//		ANIMATIONINFO animInfo;
//		u32 lnOldState;
//		SystemParametersInfo(SPI_GETANIMATION, sizeof(ANIMATIONINFO), &animInfo, 0);
//		lnOldAnim = animInfo.iMinAnimate
//		animInfo.iMinAnimate = 1;
//		SystemParametersInfo(SPI_SETANIMATION, sizeof(ANIMATIONINFO), &animInfo, SPIF_SENDCHANGE);
// (2) Alter the window style to make the window appear completely transparent (so as to hide its restoration)
//		winLong = GetWindowLong(hwnd, GWL_EXSTYLE);
//		SetWindowLong(hwnd, GWL_EXSTYLE, winLong | WS_EX_LAYERED);
//		SetLayeredWindowAttributes(hwnd, 0, 1, LWA_ALPHA);
// (3) Restore the window
//		ShowWindow(hwnd, SW_SHOW);
// (4) Capture
//		PrintWindow(hwnd, lhdc, PW_CLIENTONLY);
// (5) Minimize the window
//		ShowWindow(hwnd, SW_HIDE);
// (6) Restore the original window style
//		SetWindowLong(hwnd, GWL_EXSTYLE, winLong);
// (7) Restore the original MinAnimate() effect
//		animInfo.iMinAnimate = lnOldAnim;
//		SystemParametersInfo(SPI_SETANIMATION, sizeof(ANIMATIONINFO), &animInfo, SPIF_SENDCHANGE);
//
//////
//
//////
	int dsf_get_hwnd_contents(u32 tnHwnd, s8* tcBitmapFilename)
	{
		return(iDsf_get_hwnd_contents(tnHwnd, tcBitmapFilename));
	}




//////////
//
// Called to create a scaled interface into the HWND.
//
//////
	int dsf_scaled_interface_to_hwnd(u32 tnHwnd, s8* tcIdentifer, f32 tfInitialScale)
	{
		return(iDsf_scaled_interface_to_hwnd(tnHwnd, tcIdentifer, tfInitialScale));
	}




//////////
//
// Called to show or hide the window on the taskbar
//
/////
	int dsf_window_on_taskbar(u32 tnHwnd, u32 tnShow)
	{
		return(iDsf_window_on_taskbar(tnHwnd, tnShow));
	}




//////////
//
// Called to render a markup form used for editing, or for debugging, at the indicated size.  This
// is what the font looks like in the edit window of the DSF Font Editor.
//
//////
	int dsf_render_markup(u32 tnInstance, s32 tnWidth, s32 tnHeight, u32 tlBold, u32 tlItalic, u32 tlUnderline, u32 tlStrikethrough, s8* tcBitmapPathname, u32 tnHwnd, s32 tnX, s32 tnY, s32 tnControlX, s32 tnControlY, s32 tnControlWidth, s32 tnControlHeight)
	{
		return(iDsf_render_markup(tnInstance, tnWidth, tnHeight, tlBold, tlItalic, tlUnderline, tlStrikethrough, tcBitmapPathname, tnHwnd, tnX, tnY, tnControlX, tnControlY, tnControlWidth, tnControlHeight));
	}




//////////
//
// Called to render a final form at the indicated size.  This is what the font will look like when
// generated for regular use by the system.
//
//////
	int dsf_render_final(u32 tnInstance, s32 tnWidth, s32 tnHeight, u32 tlBold, u32 tlItalic, u32 tlUnderline, u32 tlStrikethrough, s8* tcBitmapPathname, u32 tnHwnd, s32 tnX, s32 tnY)
	{
		return(iDsf_render_final(tnInstance, tnWidth, tnHeight, tlBold, tlItalic, tlUnderline, tlStrikethrough, tcBitmapPathname, tnHwnd, tnX, tnY));
	}




//////////
//
// Called to re-render a window that has been signaled that it needs re-rendering
//
//////
	int dsf_re_render(u32 tnInstance, u32 tnHwnd)
	{
		return(iDsf_re_render(tnInstance, tnHwnd));
	}




//////////
//
// Called to obtain the bitmap of the indicated character.
//
//////
	int iDsf_get_character_bitmap(int tnAscii, s8* tcBitmapFilename, s8* tcFloanFilename, s8* tcFontName, int tnHeight, int tnWidth)
	{
		int		lnResult;
		bool	llPseudo;
		char	buffer[] = "delete_me.bmp";


		//////////
		// Make sure there is a valid filename
		//////
			if (!tcBitmapFilename || strlen(tcBitmapFilename) == 0)
			{
				llPseudo			= true;
				tcBitmapFilename	= (s8*)buffer;		// Use our fake filename
			}


		//////////
		// Grab the bitmap
		//////
			lnResult = iGetCharacterBitmap(tnAscii, tcBitmapFilename, tcFontName, tnHeight, tnWidth);


		//////////
		// If they want the floan data, generate it
		//////
			if (lnResult == 0 && tcFloanFilename)
				lnResult = iGetFloanFromBitmap(tnAscii, tcBitmapFilename, tcFloanFilename);


		//////////
		// If we had to create a temporary filename, delete it
		//////
			if (llPseudo)
				DeleteFileA(tcBitmapFilename);


		//////////
		// Indicate success or failure
		//////
			return(lnResult);
	}




//////////
//
// Called to scale a bitmap to the indicated size, and clip it to some other portion.  This
// algorithm was created to allow the user to obtain a font from dsf_get_character_bitmap(),
// but then to override the default generated image to make it resized appropriately for the
// target font.
//
//////
	int iDsf_scale_and_clip_bitmap(s8* tcBitmapFilenameIn, s8* tcBitmapFilenameOut, f64 tfWidth, f64 tfHeight, int tnClipLeft, int tnClipTop, int tnNewWidth, int tnNewHeight)
	{
// TODO:  This feature may be supplanted by using the templates point system (tems), whereby points are simply manipulated rather than a physical bitmap being scaled.
		return(0);
	}




//////////
//
//  Called to initiate a new session of editing.
//
//////
	int iDsf_create_new_instance(void)
	{
		union {
			u32		_dsf;
			SDsf*	dsf;
		};


		//////////
		// Allocate our instance
		//////
			dsf = (SDsf*)iBuilder_allocateBytes(gsRootDsfs, sizeof(SDsf));


		//////////
		// Initialize it
		//////
			memset(dsf, 0, sizeof(SDsf));
			iBuilder_createAndInitialize(&dsf->chars,	-1);
			iBuilder_createAndInitialize(&dsf->refs,	-1);
			iBuilder_createAndInitialize(&dsf->hwnds,	-1);


		//////////
		// Brand it
		//////
			memcpy(&dsf->id, cgcDsfBrand, sizeof(dsf->id));
			dsf->id_size		= sizeof(SDsf);
			dsf->activeChar		= 65;				// Default to "A"


		//////////
		// Return the address as its handle
		//////
			return(_dsf);
	}




//////////
//
// Called to set the data for the font instance
//
//////
	int iDsf_load_font(u32 tnInstance,	f64 tfAscent,	f64 tfUpper,	f64 tfLower,		f64 tfLeft,			f64 tfRight,
										f64 tfBase,		f64 tfDescent,	f64 tfWidth,
										f64 tfItalics,	f64 tfBold,		f64 tfUnderTop,		f64 tfUnderBot,		f64 tfStrikeTop,	f64 tfStrikeBot)
	{
		SDsf*		dsf;
		bool		llValid;


		//////////
		// Make sure our environment is sane
		//////
			dsf = iDsf_getInstance(tnInstance, &llValid);
			if (!llValid)
				return(-1);

		//////////
		// Store the indicated data
		//////
			dsf->font.fAscent		= tfAscent;				// See the explanations in the VFP DSF project, frmEdit::create_tables()
			dsf->font.fUpper		= tfUpper;
			dsf->font.fLower		= tfLower;
			dsf->font.fLeft			= tfLeft;
			dsf->font.fRight		= tfRight;
			dsf->font.fBase			= tfBase;
			dsf->font.fDescent		= tfDescent;
			dsf->font.fWidth		= tfWidth;
			dsf->font.fItalics		= tfItalics;
			dsf->font.fBold			= tfBold;
			dsf->font.fUnderTop		= tfUnderTop;
			dsf->font.fUnderBot		= tfUnderBot;
			dsf->font.fStrikeTop	= tfStrikeTop;
			dsf->font.fStrikeBot	= tfStrikeBot;


		//////////
		// Indicate success
		//////
			return(0);
	}




//////////
//
// Called to load a character with its data based on (u8)tnType (S=Spline, D=Definition,
// R=Reference, L=Link). For Definition entries, tiid must be above the standard 0..255 ASCII
// character range.  Reference entries will be in the 0..255 range, but tiLnkId must refer to
// an entry 256 or above.  Link entries can refer to any item, but must also include tiLnkOrder
// to indicate what explicit item they want to modify.
//
//////
	int iDsf_load_character(u32 tnInstance,	u32 tnType, u32 tiid, u32 tiOrder, s8* tcDesc10, u32 tlNewStroke, u32 tlSelected,
											f64 tfOx, f64 tfOy, f64 tfOt, f64 tfLr, f64 tfLt, f64 tfRr, f64 tfRt, 
											u32 tiSubdivs, u32 tiLnkId, u32 tiLnkOrder)
	{
		SDsf*		dsf;
		SSpline*	s;
		bool		llValid;


		//////////
		// Make sure our environment is sane
		//////
			dsf = iDsf_getInstance(tnInstance, &llValid);
			if (!llValid)
				return(-1);

			// See if this character is of a higher number than previous ones
			if (tiid > dsf->maxChar)
				dsf->maxChar = tiid;


		//////////
		// Find or create the indicated character instance
		//////
			s = iDsf_find_splineInstance(dsf->chars, tiid, (u8)tnType, tiOrder, tiLnkId, tiLnkOrder);
			if (!s)
				return(-2);		// Error finding (an invalid combination was provided)


		//////////
		// Populate the data
		//////
			s->cType		= (u8)tnType;
			s->iid			= tiid;
			s->iOrder		= tiOrder;
			s->lPenDown		= ((tlNewStroke == 0) ? false : true);
			s->lSelected	= ((tlSelected == 0) ? false : true);
			s->ox			= tfOx;
			s->oy			= tfOy;
			s->ot			= tfOt;
			s->lr			= tfLr;
			s->lt			= tfLt;
			s->rr			= tfRr;
			s->rt			= tfRt;
			s->iSubdivs		= tiSubdivs;
			s->iLnkId		= tiLnkId;
			s->iLnkOrder	= tiLnkOrder;

			// Store the description
			memcpy(&s->cDesc[0], tcDesc10, 10);
		

		//////////
		// Indicate success
		//////
			return(0);
	}




//////////
//
// Called to load the indicated instance.  We search to see if a previous entry has been added
// with this information.  If so, it's updated.  If not, it's appended.
//
//////
	int iDsf_load_reference(u32 tnInstance,	u32 tnType, s8* tcDesc40,
											f64 tfRef1X, f64 tfRef1Y,
											f64 tfRef2X, f64 tfRef2Y,
											f64 tfRef3X, f64 tfRef3Y,
											f64 tfRef4X, f64 tfRef4Y,
											f64 tfRef5X, f64 tfRef5Y,
											bool tlVisible, s8* tcChars1_128, s8* tcChars2_128)
	{
		SDsf*		dsf;
		SRefs*		r;
		bool		llValid;


		//////////
		// Make sure our environment is sane
		//////
			dsf = iDsf_getInstance(tnInstance, &llValid);
			if (!llValid)
				return(-1);


		//////////
		// Try to find the indicated data
		//////
			r = iDsf_find_refsInstance(dsf->refs, (u8)tnType, tcDesc40);
			if (!r)
			{
				// It's a new entry
				r = (SRefs*)iBuilder_allocateBytes(dsf->refs, sizeof(SRefs));
				if (!r)
					return(-2);		// Error allocating

				// Initialize it
				memset(r, 0, sizeof(SRefs));
			}


		//////////
		// Populate the data
		//////
			r->cType		= (u8)tnType;

			r->fref1x		= tfRef1X;
			r->fref1y		= tfRef1Y;

			r->fref2x		= tfRef2X;
			r->fref2y		= tfRef2Y;

			r->fref3x		= tfRef3X;
			r->fref3y		= tfRef3Y;

			r->fref4x		= tfRef4X;
			r->fref4y		= tfRef4Y;

			r->fref5x		= tfRef5X;
			r->fref5y		= tfRef5Y;

			r->lVisible		= tlVisible;

			memcpy(&r->cDesc[0], tcDesc40, 40);
			memcpy(&r->cChars1[0], tcChars1_128, 128);
			memcpy(&r->cChars2[0], tcChars2_128, 128);


		//////////
		// Release the floan data.  It will be re-populated later if this ref is ever referenced
		//////
			iBuilder_freeAndRelease(&r->floans);


		//////////
		// Indicate success
		//////
			return(0);
	}




//////////
//
// Called to load the indicated instance.  We search to see if a previous entry has been added
// with this information.  If so, it's updated.  If not, it's appended.
//
//////
	int iDsf_load_template(u32 tnInstance, u32 tipid, f64 tfX, f64 tfY, u32 tnRecno)
	{
		SDsf*		dsf;
		STems*		t;
		bool		llValid;


		//////////
		// Make sure our environment is sane
		//////
			if (tfX < 0.0 || tfX > 1.0 || tfY < 0.0 || tfY > 1.0)
				return(-2);		// Invalid parameter

			dsf = iDsf_getInstance(tnInstance, &llValid);
			if (!llValid)
				return(-1);


		//////////
		// Try to find the indicated data
		//////
			t = iDsf_create_newTemsEntry(dsf->chars, tipid);
			if (!t)
				return(-2);		// Error allocating


		//////////
		// Populate the data
		//////
			t->fx		= tfX;
			t->fy		= tfY;
			t->recno	= tnRecno;


		//////////
		// Indicate success
		//////
			return(0);
	}




//////////
//
// Called once all of the initial loading of data is complete.
//
//////
	void iDsf_initial_load_complete(u32 tnInstance, u32 tnWidth, u32 tnHeight)
	{
		u32				lnI, lnJ, lnTemsRawCount, lnTemsTempCount;
		f64				lfWidth, lfHeight;
		SDsf*			dsf;
		SDsf_chars*		c;
		SXy_s32*		temsTemp;
		SXy_s32*		temsTempLast;
		SBuilder*		temsTempBuilder;		// Temporary builder used to convert temsRaw into aliased pixel values
		STems*			t;
		bool			llValid;


		//////////
		// Make sure our environment is sane
		//////
			dsf = iDsf_getInstance(tnInstance, &llValid);
			if (!llValid)
				return;


		//////////
		// Convert the temsRaw into something used explicitly for the current window size
		//////
			lfWidth		= (f64)max(tnWidth,		400);
			lfHeight	= (f64)max(tnHeight,	400);


		//////////
		// Sort the lists
		//////
			for (lnI = 0; lnI < dsf->chars->populatedLength; lnI += sizeof(SDsf_chars))
			{
				//////////
				// Grab this pointer
				//////
					c = (SDsf_chars*)(dsf->chars->data + lnI);


				//////////
				// Are there any tems?
				//////
					if (c->temsRaw->populatedLength != 0)
					{
						// Initialize our builder
						iBuilder_createAndInitialize(&temsTempBuilder, -1);


						//////////
						// Iterate through and create entries in temsTemp for the aliased pixel values
						//////
							// Sort the raw list
							lnTemsRawCount = c->temsRaw->populatedLength / sizeof(STems);
							qsort(c->temsRaw->data, lnTemsRawCount, sizeof(STems), iiDsf_tems_qsortCallback);
							for (lnJ = 0; lnJ < c->temsRaw->populatedLength; lnJ += sizeof(STems))
							{
								// Grab the pointer
								t = (STems*)(c->temsRaw->data + lnJ);

								// Create the temporary list of aliased pixel values
								temsTemp = (SXy_s32*)iBuilder_allocateBytes(temsTempBuilder, sizeof(SXy_s32));
								if (temsTemp)
								{
									// Translate through to the aliased size
									temsTemp->xi	= (s32)((f64)t->fx * lfWidth);
									temsTemp->yi	= (s32)((f64)t->fy * lfHeight);
								}
							}
							// When we get here, we have a completely aliased set of coordinates


						//////////
						// Convert the aliased list into a list of real entries, unique per pixel
						//////
							// Sort the aliased list
							lnTemsTempCount = temsTempBuilder->populatedLength / sizeof(SXy_s32);
							qsort(temsTempBuilder->data, lnTemsTempCount, sizeof(SXy_s32), iiDsf_SXy_s32_qsortCallback);
							for (lnJ = 0; lnJ < temsTempBuilder->populatedLength; lnJ += sizeof(SXy_s32))
							{
								// Grab the pointer
								temsTemp = (SXy_s32*)(temsTempBuilder->data + lnJ);

								// Has it changed?
								if (lnJ == 0 || temsTempLast->xi != temsTemp->xi || temsTempLast->yi != temsTemp->yi)
								{
									// This is now our new last item
									temsTempLast = temsTemp;

									// Create the converted data
									t = (STems*)iBuilder_allocateBytes(c->tems, sizeof(STems));
									if (t)
									{
										// Translate through to the aliased size
										t->fx	= ((f64)temsTemp->xi / lfWidth)  + 0.0000001;
										t->fy	= ((f64)temsTemp->yi / lfHeight) + 0.0000001;
									}
								}
							}
							// When we get here, c->tems is populated with a list of only aliased pixel values


						//////////
						// Release our builder
						//////
							iBuilder_freeAndRelease(&temsTempBuilder);
					}
			}
	}




//////////
//
// Called to load the indicated instance.  We search to see if a previous entry has been added
// with this information.  If so, it's updated.  If not, it's appended.
//
//////
	int iDsf_get_changed_template(u32 tnInstance, u32 tipid, s8* tcY12, s8* tcX12, s8* tcRecno12, u32 tnNextNewRecno)
	{
		u32			lnI;
		SDsf*		dsf;
		SBuilder*	tems;
		STems*		t;
		bool		llValid;


		//////////
		// Make sure our environment is sane
		//////
			dsf = iDsf_getInstance(tnInstance, &llValid);
			if (!llValid)
				return(-1);


		//////////
		// Try to find the indicated data
		//////
			tems = iDsf_get_tems_rawBuilder(dsf->chars, tipid);
			if (!tems)
				return(-2);		// Error accessing this pid


		//////////
		// Find the first changed entry
		//////
			for (lnI = 0; lnI < tems->populatedLength; lnI += sizeof(STems))
			{
				// Grab the pointer
				t = (STems*)(tems->data + lnI);

				// If it's changed, but not deleted
				if (t->changed && !t->deleted)
				{
					// Update the recno() if it's a new item
					if (t->recno == -1)
						t->recno = tnNextNewRecno;

					// Store each item
					sprintf(tcX12,		"%7.5f",	t->fx);
					sprintf(tcY12,		"%7.5f",	t->fy);
					sprintf(tcRecno12,	"%u",		t->recno);

					// Mark it no longer changed
					t->changed = false;

					// Indicate success
					return(0);
				}
			}


		//////////
		// Indicate that there are no more items
		//////
			return(-3);
	}




//////////
//
// Called to load the indicated instance.  We search to see if a previous entry has been added
// with this information.  If so, it's updated.  If not, it's appended.
//
//////
	int iDsf_get_deleted_template(u32 tnInstance, u32 tipid, s8* tcRecno12)
	{
		u32			lnI;
		SDsf*		dsf;
		SBuilder*	tems;
		STems*		t;
		bool		llValid;


		//////////
		// Make sure our environment is sane
		//////
			dsf = iDsf_getInstance(tnInstance, &llValid);
			if (!llValid)
				return(-1);


		//////////
		// Try to find the indicated data
		//////
			tems = iDsf_get_tems_rawBuilder(dsf->chars, tipid);
			if (!tems)
				return(-2);		// Error accessing this pid


		//////////
		// Find the first changed entry
		//////
			for (lnI = 0; lnI < tems->populatedLength; lnI += sizeof(STems))
			{
				// Grab the pointer
				t = (STems*)(tems->data + lnI);

				// Report on previously existing deleted items.  If the user adds an item, then
				// deletes it before saving it is simply an orphan record that will be freed at exit.
				if (t->deleted && t->recno != -1)
				{
					// Store the record number
					sprintf(tcRecno12, "%u", t->recno);

					// Indicate success
					return(0);
				}
			}


		//////////
		// Indicate that there are no more items
		//////
			return(-3);
	}




//////////
//
// Called to set the cues the user wants to see, along with whether or not the mouse should track
// near to any of the specified cues.  Will NOT issue a redraw.  Use dsf_user_cues() and then
// dsf_user_cues2() for updating cues, and then use dsf_user_settings() to issue the redraw.
//
//////
	int iDsf_user_cues(u32 tnInstance,	u32 tnAscent,			u32 tnTrackAscent, 
										u32 tnUpper,			u32 tnTrackUpper, 
										u32 tnLower,			u32 tnTrackLower, 
										u32 tnBase,				u32 tnTrackBase, 
										u32 tnDescent,			u32 tnTrackDescent, 
										u32 tnStrikethrough,	u32 tnTrackStrike, 
										u32 tnUnderline,		u32 tnTrackUnderline, 
										u32 tnRefs,				u32 tnTrackRefs)
	{
		SDsf*		dsf;
		bool		llValid;


		//////////
		// Make sure our environment is sane
		//////
			dsf = iDsf_getInstance(tnInstance, &llValid);
			if (!llValid)
				return(-1);


		//////////
		// Set the values, and trigger a refresh on any markup windows
		//////
			dsf->ascent				= iDsf_validate_range(tnAscent,			 	_NO, 	_YES,	_NO);
			dsf->trackAscent		= iDsf_validate_range(tnTrackAscent,			_NO,	_YES,	_NO);
			dsf->upper				= iDsf_validate_range(tnUpper,				_NO,	_YES,	_NO);
			dsf->trackUpper			= iDsf_validate_range(tnTrackUpper,			_NO,	_YES,	_NO);
			dsf->lower				= iDsf_validate_range(tnLower,				_NO,	_YES,	_NO);
			dsf->trackLower			= iDsf_validate_range(tnTrackLower,			_NO,	_YES,	_NO);
			dsf->base				= iDsf_validate_range(tnBase,				_NO,	_YES,	_NO);
			dsf->trackBase			= iDsf_validate_range(tnTrackBase,			_NO,	_YES,	_NO);
			dsf->descent			= iDsf_validate_range(tnDescent,				_NO,	_YES,	_NO);
			dsf->trackDescent		= iDsf_validate_range(tnTrackDescent,		_NO,	_YES,	_NO);
			dsf->strikethrough		= iDsf_validate_range(tnStrikethrough,		_NO,	_YES,	_NO);
			dsf->trackStrike		= iDsf_validate_range(tnTrackStrike,			_NO,	_YES,	_NO);
			dsf->underline			= iDsf_validate_range(tnUnderline,			_NO,	_YES,	_NO);
			dsf->trackUnderline		= iDsf_validate_range(tnTrackUnderline,		_NO,	_YES,	_NO);
			dsf->showRefs			= iDsf_validate_range(tnRefs,				_NO,	_YES,	_NO);
			dsf->trackRefs			= iDsf_validate_range(tnTrackRefs,			_NO,	_YES,	_NO);
			// Note:  We do not render here because the cues and settings are usually sent sequentially, and it only triggers the render on the settings


		//////////
		// Indicate success
		//////
			return(0);
	}

	int iDsf_user_cues2(u32 tnInstance,	u32 tlLeft,		u32 tnTrackLeft, 
										u32 tlRight,	u32 tnTrackRight, 
										u32 tlWidth,	u32 tnTrackWidth, 
										u32 tlTems,		u32 tnTrackTems,
										u32 tlGrid,		u32 tnTrackGrid)
	{
		SDsf*		dsf;
		bool		llValid;


		//////////
		// Make sure our environment is sane
		//////
			dsf = iDsf_getInstance(tnInstance, &llValid);
			if (!llValid)
				return(-1);


		//////////
		// Set the values, and trigger a refresh on any markup windows
		//////
			dsf->left			= iDsf_validate_range(tlLeft,		 	_NO, 	_YES,	_NO);
			dsf->trackLeft		= iDsf_validate_range(tnTrackLeft,	 	_NO, 	_YES,	_NO);
			dsf->right			= iDsf_validate_range(tlRight,		 	_NO, 	_YES,	_NO);
			dsf->trackRight		= iDsf_validate_range(tnTrackRight,	 	_NO, 	_YES,	_NO);
			dsf->width			= iDsf_validate_range(tlWidth,		 	_NO, 	_YES,	_NO);
			dsf->trackWidth		= iDsf_validate_range(tnTrackWidth,	 	_NO, 	_YES,	_NO);
			dsf->tems			= iDsf_validate_range(tlTems,		 	_NO, 	_YES,	_NO);
			dsf->trackTems		= iDsf_validate_range(tnTrackTems,	 	_NO, 	_YES,	_NO);
			dsf->grid			= iDsf_validate_range(tlGrid,			_NO,	_YES,	_NO);
			dsf->trackGrid		= iDsf_validate_range(tnTrackGrid,		_NO,	_YES,	_NO);
			// Note:  We do not render here because the cues and settings are usually sent sequentially, and it only triggers the render on the settings


		//////////
		// Indicate success
		//////
			return(0);

	}




//////////
//
// Called to convey user settings.  Will issue a redraw.
//
//////
	int iDsf_user_settings(u32 tnInstance,
							u32 tnDisposition, u32 tnMode, u32 tnMethod, u32 tnRange,
							u32 tlShowSplines, u32 tnSplinesType,
							u32 tlHighlighSelection, u32 tlShowPenDowns,
							u32 tlMouseCrosshairX, u32 tlMouseCrosshairY,
							u32 tlInvert,
							u32 tlZoomLens,
							u32 tlCuesUnder, 
							u32 tnSelectArea)
	{
		u32				lnI;
		SDsf*			dsf;
		SDsf_hwnd*		h;
		bool			llValid;


		//////////
		// Make sure our environment is sane
		//////
			dsf = iDsf_getInstance(tnInstance, &llValid);
			if (!llValid)
				return(-1);


		//////////
		// Set the values, and trigger a refresh on any markup windows
		//////
			dsf->disposition			= iDsf_validate_range(tnDisposition,				_DISPOSITION_SELECT,	_DISPOSITION_FLIP_LM_RM,	_DISPOSITION_SELECT);
			dsf->mode					= iDsf_validate_range(tnMode,					_MODE_POINT,			_MODE_AFTER,				_MODE_POINT);
			dsf->method					= iDsf_validate_range(tnMethod,					_METHOD_LEFT,			_METHOD_POINT,				_METHOD_POINT);
			dsf->range					= iDsf_validate_range(tnRange,					_RANGE_ACTIVE_CHAR,		_RANGE_ALL,					_RANGE_ACTIVE_CHAR);
			dsf->showSplines			= iDsf_validate_range(tlShowSplines,				_NO,					_YES,						_YES);
			dsf->splinesType			= iDsf_validate_range(tnSplinesType,				_SPLINES_FILL,			_SPLINES_LOR,				_SPLINES_FILL);
			dsf->highlighSelection		= iDsf_validate_range(tlHighlighSelection,		_NO,					_YES,						_YES);
			dsf->showPenDowns			= iDsf_validate_range(tlShowPenDowns,			_NO,					_YES,						_NO);
			dsf->mouseCrosshairX		= iDsf_validate_range(tlMouseCrosshairX,			_NO,					_YES,						_YES);
			dsf->mouseCrosshairY		= iDsf_validate_range(tlMouseCrosshairY,			_NO,					_YES,						_YES);
			dsf->invert					= iDsf_validate_range(tlInvert,					_NO,					_YES,						_NO);
			dsf->zoomLens				= iDsf_validate_range(tlZoomLens,				_NO,					_YES,						_NO);
			dsf->cuesUnder				= iDsf_validate_range(tlCuesUnder,				_NO,					_YES,						_YES);
			dsf->selectArea				= iDsf_validate_range(tnSelectArea,				_SELECT_AREA_SMALL,		_SELECT_AREA_EXTRA_LARGE,	_SELECT_AREA_SMALL);


		//////////
		// Force a re-render (whether we need one or not. :-))
		//////
			for (lnI = 0; lnI < dsf->hwnds->populatedLength; lnI += sizeof(SDsf_hwnd))
			{
				// Grab the pointer
				h = (SDsf_hwnd*)(dsf->hwnds->data + lnI);

				// If it's a markup window, re-render it
				PostMessage(h->hwndParent, WM_REDRAW_WINDOW, (u32)dsf, (u32)h->hwnd);
			}


		//////////
		// Indicate success
		//////
			return(0);
	}




//////////
//
// Called to indicate the user wants to make active another character for editing.  Will issue a redraw.
//
//////
	int iDsf_set_active_character(u32 tnInstance, u32 tiid)
	{
		SDsf*		dsf;
		bool		llValid;


		//////////
		// Make sure our environment is sane
		//////
			dsf = iDsf_getInstance(tnInstance, &llValid);
			if (!llValid)
				return(-1);


		//////////
		// Make sure that character is defined
		/////
			if (tiid * sizeof(SDsf_chars) < dsf->chars->populatedLength)
			{
				// It exists
				dsf->activeChar = tiid;
				return(0);

			} else {
				// Invalid character range
				return(-2);
			}
	}




//////////
//
// Called to indicate what tool the user wants to use.  Will issue a redraw.
//
//////
	int iDsf_set_active_tool(u32 tnInstance, u32 tnToolNumber)
	{
		u32				lnI;
		SDsf*			dsf;
		SDsf_hwnd*		h;
		bool			llValid;

		//////////
		// Make sure our environment is sane
		//////
			dsf = iDsf_getInstance(tnInstance, &llValid);
			if (!llValid)
				return(-1);


		//////////
		// Set the values, and trigger a refresh on any markup windows
		//////
			dsf->activeTool		= iDsf_validate_range(tnToolNumber,		_TOOL_EDIT,		_TOOL_SCALE,	_TOOL_EDIT);


		//////////
		// Force a re-render (whether we need one or not. :-))
		//////
			for (lnI = 0; lnI < dsf->hwnds->populatedLength; lnI += sizeof(SDsf_hwnd))
			{
				// Grab the pointer
				h = (SDsf_hwnd*)(dsf->hwnds->data + lnI);

				// If it's a markup window, re-render it
				PostMessage(h->hwndParent, WM_REDRAW_WINDOW, (u32)dsf, (u32)h->hwnd);
			}


		//////////
		// Indicate success
		//////
			return(0);
	}




//////////
//
// Called to capture the contents of the indicated window to a disk file.
//
//////////
//
// Note:  In general, minimized windows can't be captured.
// Note:  However, if the window is minimized it can still be captured using a type of hack.
// Note:  This must be done in rapid succession.  In general, it will be, but it remains slower than capturing a visible window.
// Steps:
// (1) Disable the MinAnimate() effect globally:
//		ANIMATIONINFO animInfo;
//		u32 lnOldState;
//		SystemParametersInfo(SPI_GETANIMATION, sizeof(ANIMATIONINFO), &animInfo, 0);
//		lnOldAnim = animInfo.iMinAnimate
//		animInfo.iMinAnimate = 1;
//		SystemParametersInfo(SPI_SETANIMATION, sizeof(ANIMATIONINFO), &animInfo, SPIF_SENDCHANGE);
// (2) Alter the window style to make the window appear completely transparent (so as to hide its restoration)
//		winLong = GetWindowLong(hwnd, GWL_EXSTYLE);
//		SetWindowLong(hwnd, GWL_EXSTYLE, winLong | WS_EX_LAYERED);
//		SetLayeredWindowAttributes(hwnd, 0, 1, LWA_ALPHA);
// (3) Restore the window
//		ShowWindow(hwnd, SW_SHOW);
// (4) Capture
//		PrintWindow(hwnd, lhdc, PW_CLIENTONLY);
// (5) Minimize the window
//		ShowWindow(hwnd, SW_HIDE);
// (6) Restore the original window style
//		SetWindowLong(hwnd, GWL_EXSTYLE, winLong);
// (7) Restore the original MinAnimate() effect
//		animInfo.iMinAnimate = lnOldAnim;
//		SystemParametersInfo(SPI_SETANIMATION, sizeof(ANIMATIONINFO), &animInfo, SPIF_SENDCHANGE);
//
//////
//
//////
	int iDsf_get_hwnd_contents(u32 tnHwnd, s8* tcBitmapFilename)
	{
		union {
			HWND	hwnd;
			u32		_hwnd;
		};
		HDC					lhdc;
		HBITMAP				lhbmp;
		RECT				lrc;
		BITMAPFILEHEADER	bh;
		BITMAPINFOHEADER	bi;
		SBgr*				bd;


		//////////
		// Store the parameter locally
		//////
			_hwnd = tnHwnd;


		//////////
		// Make sure it's a valid window
		//////
			if (IsWindow(hwnd))
			{
				// Get crucial window data
				GetClientRect(hwnd, &lrc);
				// Setup crucial window components
				lhdc	= CreateCompatibleDC(GetDC(hwnd));
				bd		= NULL;
				lhbmp	= iCreateBitmap(lhdc, lrc.right - lrc.left, lrc.bottom - lrc.top, 1, 24, (void**)&bd, &bh, &bi);
				SelectObject(lhdc, lhbmp);

				// Ask Windows to draw its window contents into our device context
				PrintWindow(hwnd, lhdc, PW_CLIENTONLY);

				// Save the bitmap
				iSaveBitmapByParams(&bh, &bi, bd, tcBitmapFilename);

				// Cleanup
				DeleteObject((HGDIOBJ)lhbmp);
				DeleteDC(lhdc);

				// Success
				return(0);
			}
			return(-1);
	}




//////////
//
// Called to create a scaled interface into the HWND.
//
//////
	int iDsf_scaled_interface_to_hwnd(u32 tnHwnd, s8* tcIdentifer, f32 tfInitialScale)
	{
		union {
			HWND	hwnd;
			u32		_hwnd;
		};
		HDC					lhdc;
		HBITMAP				lhbmp;
		RECT				lrc;
		BITMAPFILEHEADER	bh;
		BITMAPINFOHEADER	bi;
		SBgr*				bd;


		//////////
		// Store the parameter locally
		//////
			_hwnd = tnHwnd;


		//////////
		// Make sure it's a valid window
		//////
			if (IsWindow(hwnd))
			{
				// Get crucial window data
				GetClientRect(hwnd, &lrc);

				// Setup crucial window components
				lhdc	= CreateCompatibleDC(GetDC(hwnd));
				bd		= NULL;
				HMENU hmenu = CreateMenu();
				lhbmp	= iCreateBitmap(lhdc, lrc.right - lrc.left, lrc.bottom - lrc.top, 1, 24, (void**)&bd, &bh, &bi);
				SelectObject(lhdc, lhbmp);

				// Ask Windows to draw its window contents into our device context
				PrintWindow(hwnd, lhdc, PW_CLIENTONLY);

				// Create the scaled window implementation

				// Success
				return(0);
			}
			return(-1);
	}




//////////
//
// Called to show or hide the window on the taskbar
//
/////
	int iDsf_window_on_taskbar(u32 tnHwnd, u32 tnShow)
	{
		u32 lnResult;
		union {
			HWND	hwnd;
			u32		_hwnd;
		};


		//////////
		// If it's a window, process it
		//////
			_hwnd = tnHwnd;
			if (IsWindow(hwnd))
			{
				// Show or hide it
				if (tnShow == 0)		lnResult = giTaskbar->DeleteTab(hwnd);
				else					lnResult = giTaskbar->AddTab(hwnd);

				return(lnResult != 0);
			}
			// Failure
			return(-1);
	}




//////////
//
// Called to render a markup form used for editing, or for debugging, at the indicated size.  This
// is what the font looks like in the edit window of the DSF Font Editor.
//
//////
	int iDsf_render_markup(u32 tnInstance, s32 tnWidth, s32 tnHeight, u32 tlBold, u32 tlItalic, u32 tlUnderline, u32 tlStrikethrough, s8* tcBitmapPathname, u32 tnHwnd, s32 tnX, s32 tnY, s32 tnControlX, s32 tnControlY, s32 tnControlWidth, s32 tnControlHeight)
	{
		SDsf*			dsf;
		SDsf_hwnd*		h;
		SDsf_chars*		thisChar;
		bool			llValid;


		//////////
		// Make sure our environment is sane
		//////
			dsf = iDsf_getInstance(tnInstance, &llValid);
			if (!llValid)
				return(-1);


		//////////
		// Find the active character instance
		//////
			thisChar = iiDsf_findOnly_thisChars(dsf->chars, dsf->activeChar);
			if (!thisChar)
				return(-2);		// Error finding (an invalid combination was provided)


		//////////
		// Determine where we will update our bitmap
		//////
			h = iDsf_findHwnd_orCreate(dsf->hwnds, tnHwnd, tnX, tnY, tnWidth, tnHeight, true);
			if (!h)
				return(-3);


		//////////
		// Set it
		//////
			h->markup			= true;
			h->bold				= tlBold;
			h->italic			= tlItalic;
			h->underline		= tlUnderline;
			h->strikethrough	= tlStrikethrough;

			// Create our control window if need be
			if (!h->_hwndControl && tnControlX >= 0 && tnControlY >= 0)
				h->_hwndControl	= iDsf_createControlWindow(h, tnControlX, tnControlY, tnControlWidth, tnControlHeight);


		//////////
		// Render it
		//////
			return(iDsf_render(dsf, h, thisChar, tnWidth, tnHeight, tnHwnd, tnX, tnY));
	}




//////////
//
// Called to render a final form at the indicated size.  This is what the font will look like when
// generated for regular use by the system.
//
//////
	int iDsf_render_final(u32 tnInstance, s32 tnWidth, s32 tnHeight, u32 tlBold, u32 tlItalic, u32 tlUnderline, u32 tlStrikethrough, s8* tcBitmapPathname, u32 tnHwnd, s32 tnX, s32 tnY)
	{
		SDsf*			dsf;
		SDsf_hwnd*		h;
		SDsf_chars*		thisChar;
		bool			llValid;


		//////////
		// Make sure our environment is sane
		//////
			dsf = iDsf_getInstance(tnInstance, &llValid);
			if (!llValid)
				return(-1);


		//////////
		// Find the active character instance
		//////
			thisChar = iiDsf_findOnly_thisChars(dsf->chars, dsf->activeChar);
			if (!thisChar)
				return(-2);		// Error finding (an invalid combination was provided)


		//////////
		// Determine where we will update our bitmap
		//////
			h = iDsf_findHwnd_orCreate(dsf->hwnds, tnHwnd, tnX, tnY, tnWidth, tnHeight, false);
			if (!h)
				return(-3);


		//////////
		// Render it
		//////
			h->markup			= false;
			h->bold				= tlBold;
			h->italic			= tlItalic;
			h->underline		= tlUnderline;
			h->strikethrough	= tlStrikethrough;
			return(iDsf_render(dsf, h, thisChar, tnWidth, tnHeight, tnHwnd, tnX, tnY));
	}




//////////
//
// Called to re-render a window that has been signaled that it needs re-rendering
//
//////
	int iDsf_re_render(u32 tnInstance, u32 tnHwnd)
	{
		SDsf*			dsf;
		SDsf_chars*		thisChar;
		SDsf_hwnd*		h;
		bool			llValid;


		//////////
		// Make sure our environment is sane
		//////
			dsf = iDsf_getInstance(tnInstance, &llValid);
			if (!llValid)
				return(-1);


		//////////
		// Find the active character instance
		//////
			thisChar = iiDsf_findOnly_thisChars(dsf->chars, dsf->activeChar);
			if (!thisChar)
				return(-2);		// Error finding (an invalid combination was provided)


		//////////
		// See if we're found on this instance
		//////
			if (!IsWindow((HWND)tnHwnd))
				return(-2);		// Invalid window


		//////////
		// Search for it
		//////
			h = iDsf_findOnlyHwnd_byHwnd(dsf->hwnds, (u32)GetParent((HWND)tnHwnd), tnHwnd);
			if (h)		return(iDsf_render(dsf, h, thisChar, h->w, h->h, tnHwnd, h->x, h->y));
			else		return(-3);
	}




//////////
//
// Physically construct the indicated character.    It does this by sizing some known maximums, and
// generating the bitmap for our new characters using that size.  We migrate and center the bitmap
// onto the known maximum bitmap canvas, and then using scale the image down to the indicated size.
//
//		(1) "hKltfgpqy" + SPACE(1)
//		(2) "hKltfgpqy" + SPACE(1) + CHR(tnAscii)
//
// Then the second bitmap will be wider than the first, but otherwise identical.  That following
// portion is the part which is returned to the indicated filename.  An appropriate font size is
// used based on the height and width, with the final image generated being scaled to the
//
//////
	int iGetCharacterBitmap(int tnAscii, s8* tcBitmapFilename, s8* tcFontName, int tnHeight, int tnWidth)
	{
		int			lnWidth, lnHeight, lnMakeWidth;
		f64			lfH, lfV;
		HFONT		hfont;
		HDC			lhdc;
		HBITMAP		lhbmp2;
		RECT		lrc1, lrc2, lrcM, lrcW;
		SBgr*		bd2;
		char		mbuffer[]					= "M";
		char		wbuffer[]					= "W";
		char		buffer[]					= "hKltfgpqy  \0";
		char		rawBuffer[_MAX_FNAME];


		//////////
		// Create the font
		//////
			lnHeight = -MulDiv(tnHeight, GetDeviceCaps(GetDC(GetDesktopWindow()), LOGPIXELSY), 72);
			hfont = CreateFontA(lnHeight, 0, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, NONANTIALIASED_QUALITY, FF_DONTCARE, tcFontName);
			if (!hfont)
				return(-1);


		//////////
		// Generate the two bitmaps
		//////
			lhdc = CreateCompatibleDC(GetDC(GetDesktopWindow()));
			SelectObject(lhdc, hfont);
			buffer[sizeof(buffer) - 3] = 0;


		//////////
		// Determine sizes
		//////
			// Bitmap 1 (without the indicated character)
			SetRect(&lrc1, 0, 0, 0, 0);
			DrawTextA(lhdc, buffer, strlen(buffer), &lrc1, DT_CALCRECT);

			// Bitmap 2 (with the indicated character)
			buffer[sizeof(buffer) - 3] = (char)tnAscii;
			SetRect(&lrc2, 0, 0, 0, 0);
			DrawTextA(lhdc, buffer, strlen(buffer), &lrc2, DT_CALCRECT);

			// M
			SetRect(&lrcM, 0, 0, 0, 0);
			DrawTextA(lhdc, mbuffer, 1, &lrcM, DT_CALCRECT);

			// W
			SetRect(&lrcW, 0, 0, 0, 0);
			DrawTextA(lhdc, wbuffer, 1, &lrcW, DT_CALCRECT);

			// Compute width and height
			lnWidth		= lrc2.right  - lrc2.left;
			lnHeight	= lrc2.bottom - lrc2.top;
			lnMakeWidth	= max(lrcM.right - lrcM.left, lrcW.right - lrcW.left);


		//////////
		// Bitmap 2
		//////
			lhbmp2 = iCreateBitmap(lhdc, lnWidth, lnHeight, 1, 24, (void**)&bd2, NULL, NULL);
			SelectObject(lhdc, lhbmp2);
			FillRect(lhdc, &lrc2, (HBRUSH)GetStockObject(WHITE_BRUSH));
			DrawTextA(lhdc, buffer, strlen(buffer), &lrc2, DT_LEFT);


		//////////
		// Write out the portion that's different to a temporary file
		//////
			memset(rawBuffer, 0, sizeof(rawBuffer));
			memcpy(rawBuffer, tcBitmapFilename, min(strlen(tcBitmapFilename), sizeof(rawBuffer) - 1));
			rawBuffer[strlen(rawBuffer) - 1] = 'q';
			lnMakeWidth = iSaveBitmap(bd2, lnWidth, lnHeight, lrc1.right - lrc1.left, rawBuffer, lnMakeWidth);


		//////////
		// Release everything
		//////
			DeleteObject((HGDIOBJ)hfont);
			DeleteObject((HGDIOBJ)lhbmp2);
			DeleteDC(lhdc);


		//////////
		// Scale the generated image up to the indicated size
		//////
			lfH = (f64)tnWidth	/ (f64)lnMakeWidth;
			lfV = (f64)tnHeight	/ (f64)lnHeight;
			iScaleImage(rawBuffer, tcBitmapFilename, (f64)lfH, (f64)lfV);
			DeleteFileA(rawBuffer);


		//////////
		// Indicate success
		//////
			return(0);
	}

	int iSaveBitmapByParams(BITMAPFILEHEADER* tbh, BITMAPINFOHEADER* tbi, SBgr* tbd, s8* tcBitmapFilename)
	{
		FILE* lfh;


		//////////
		// Simple disk write
		//////
			lfh = fopen(tcBitmapFilename, "wb+");
			if (lfh)
			{
				// Write file header, info header, bitmap bits
				fwrite(tbh, 1, sizeof(BITMAPFILEHEADER), lfh);
				fwrite(tbi, 1, sizeof(BITMAPINFOHEADER), lfh);
				fwrite(tbd, 1, tbi->biSizeImage, lfh);
				// Close
				fclose(lfh);
				// Done
				return(0);
			}
			// Failure
			return(-1);
	}

	int iSaveBitmap(SBgr* tbd, int tnWidth, int tnHeight, int tnLeft, s8* tcBitmapFilename, int tnMakeWidth)
	{
		int					lnY, lnRowWidth, lnWritePels, lnCopyPels, lnOffset, lnCopyWidth;
		SBgr*				lbgr;
		SBgr*				lbgrBuffer;
		BITMAPFILEHEADER	lbh;
		BITMAPINFOHEADER	lbi;
		FILE*				lfh;


		//////////
		// Create the output bitmap header
		//////    This is a test
			memset(&lbh, 0, sizeof(lbh));
			lbh.bfType		= 'MB';
			lbh.bfOffBits	= sizeof(lbh) + sizeof(lbi);

			lnCopyWidth		= max(tnWidth - tnLeft, tnMakeWidth);
			lnRowWidth		= iComputeRowWidth(tnWidth);
 
			memset(&lbi, 0, sizeof(lbi));
			lbi.biSize		= sizeof(lbi);
			lbi.biWidth		= lnCopyWidth;
			lnCopyPels		= (tnWidth - tnLeft) * 3;
			lnWritePels		= iComputeRowWidth(lbi.biWidth);
			lbi.biHeight	= tnHeight;
			lbi.biPlanes	= 1;
			lbi.biBitCount	= 24;
			lbi.biSizeImage	= lnWritePels * tnHeight;
			lbi.biXPelsPerMeter = 3270;
			lbi.biYPelsPerMeter = 3270;

			lbh.bfSize		= sizeof(lbh) + sizeof(lbi) + lbi.biSizeImage;
			

		//////////
		// Get metrics for the incoming image, and create a buffer for each line
		//////
			lnOffset	= (lbi.biWidth - (tnWidth - tnLeft)) / 2;
			lbgrBuffer	= (SBgr*)malloc(lnWritePels);
			if (lbgrBuffer)
			{
			//////////
			// Write out the header
			//////
				lfh = fopen(tcBitmapFilename, "wb+");
				if (lfh)
				{
					fwrite(&lbh, 1, sizeof(lbh), lfh);
					fwrite(&lbi, 1, sizeof(lbi), lfh);


				//////////
				// Extract out the bitmap portions.
				// Bitmaps are stored in reverse order, so we can iterate normally down through
				//////
					for (lnY = 0; lnY < tnHeight; lnY++)
					{
						//////////
						// Compute the offset to this part
						//////
							lbgr = (SBgr*)((s8*)tbd + (lnY * lnRowWidth) + (tnLeft * 3));


						//////////
						// Copy to our buffer row
						//////
							memset(lbgrBuffer, 255, lnWritePels);
							memcpy(lbgrBuffer + lnOffset, lbgr, lnCopyPels);


						//////////
						// Write this row
						//////
							fwrite(lbgrBuffer, 1, lnWritePels, lfh);
					}
					// When we get here, it's saved
					fclose(lfh);
				}
				// We're done
				free(lbgrBuffer);
			}
			// Indicate how wide it is
			return(lnCopyWidth);
	}

	int iComputeRowWidth(int tnWidth)
	{
		int lnWidth;


		lnWidth = tnWidth * 3;
		if (lnWidth % 4 == 0)
			return(lnWidth);

		// Increase the width
		lnWidth += (4 - (lnWidth % 4));
		return(lnWidth);
	}

	HBITMAP iCreateBitmap(HDC thdc, int tnWidth, int tnHeight, int tnPlanes, int tnBits, void** tbd, BITMAPFILEHEADER* tbh, BITMAPINFOHEADER* tbi)
	{
		BITMAPFILEHEADER	bf;
		BITMAPINFOHEADER	bi;
		BITMAPINFOHEADER*	lbi;
		HBITMAP				lhbmp;


		//////////
		// Use remote or local
		//////
			if (tbi)		lbi = tbi;		// Use caller's
			else			lbi = &bi;		// Use ours


		//////////
		// Create a new DIB (these parts are required for CreateDIBSection to work)
		//////
			memset(lbi, 0, sizeof(BITMAPINFOHEADER));
			lbi->biSize			= sizeof(BITMAPINFOHEADER);
			lbi->biWidth		= tnWidth;
			lbi->biHeight		= tnHeight;
			lbi->biPlanes		= tnPlanes;
			lbi->biBitCount		= tnBits;


		//////////
		// Populate caller parts (these parts are also required for disk files)
		//////
			if (tbi)
			{
				lbi->biSizeImage		= iComputeRowWidth(tnWidth) * tnHeight;
				lbi->biXPelsPerMeter	= 3270;
				lbi->biYPelsPerMeter	= 3270;
			}
			if (tbh)
			{
				tbh->bfType				= 'MB';
				tbh->bfReserved1		= 0;
				tbh->bfReserved2		= 0;
				tbh->bfOffBits			= sizeof(bf) + sizeof(bi);
				tbh->bfSize				= tbh->bfOffBits + tbi->biSizeImage;
			}


		//////////
		// Physically create the bitmap
		//////
			lhbmp = CreateDIBSection(thdc, (BITMAPINFO*)lbi, DIB_RGB_COLORS, tbd, NULL, 0);
			return(lhbmp);
	}




//////////
//
// Find every outline point and create a list of the same.
//
//////
	int iGetFloanFromBitmap(u32 tnAscii, s8* tcBitmapFilename, s8* tcFloanFilename)
	{
		int					lnI, lnY, lnX, lnRowWidth, lnOldFloanCount, lnNewFloanCount;
		f64					lfGray, lfLastGray;
		SBgr*				lbgr;
		SBgr*				lbgrBuffer;
		BITMAPFILEHEADER	lbh;
		BITMAPINFOHEADER	lbi;
		FILE*				lfh;
		SBuilder*			floans;
		SBuilder*			floansCsv;
		SDsf_floanPoint		point;
		SDsf_floanPoint*	pDst;
		SDsf_floanPoint*	pSrc;
		s8					buffer[256];


		//////////
		// Open the indicated bitmap
		//////
			lfh = fopen(tcBitmapFilename, "rb");
			if (!lfh)
				return(-1);		// File does not exist


		//////////
		// Read in the header
		//////
			fread(&lbh, 1, sizeof(lbh), lfh);
			fread(&lbi, 1, sizeof(lbi), lfh);


		//////////
		// Make sure it's a sane bitmap
		//////
			if (lbh.bfSize != sizeof(lbh) + sizeof(lbi) + lbi.biSizeImage)
			{
				fclose(lfh);
				return(-2);				// Invalid header
			}
			if (lbi.biSize != sizeof(lbi))
			{
				fclose(lfh);
				return(-3);				// Invalid info
			}
			if (lbi.biPlanes != 1 || lbi.biBitCount != 24)
			{
				fclose(lfh);
				return(-4);				// Invalid bitmap style/format
			}
			lnRowWidth = iComputeRowWidth(lbi.biWidth);
			if (lnRowWidth * lbi.biHeight != lbi.biSizeImage)
			{
				fclose(lfh);
				return(-5);				// Invalid size
			}


		//////////
		// Load in the data
		//////
			lbgrBuffer = (SBgr*)malloc(lbi.biSizeImage);
			if (!lbgrBuffer)
			{
				fclose(lfh);
				return(-6);				// Out of memory
			}
			fread(lbgrBuffer, 1, lbi.biSizeImage, lfh);
			fclose(lfh);


		//////////
		// Increase contrast to full
		//////
			for (lnY = 0; lnY < lbi.biHeight; lnY++)
			{
				// Iterate all the way across
				lbgr = (SBgr*)((s8*)lbgrBuffer + (lnY * lnRowWidth));

				// Look for where things start or stop
				for (lnX = 0; lnX < lbi.biWidth; lnX++, lbgr++)
				{
					// Determine the grayscale value of this pixel
					lfGray = (((f64)lbgr->red * 0.35f) + ((f64)lbgr->grn * 0.54f) + ((f64)lbgr->blu * 0.11f)) / 255.0f;

					// Is it visibly darkened?
					if (lfGray < 0.7f)
					{
						// Make it black
						lbgr->red = 0;
						lbgr->grn = 0;
						lbgr->blu = 0;

					} else {
						// Make it white
						lbgr->red = 255;
						lbgr->grn = 255;
						lbgr->blu = 255;
					}
				}
			}


		//////////
		// Initialize
		//////
			iBuilder_createAndInitialize(&floans,	65536);
			iBuilder_createAndInitialize(&floansCsv,	65536);


		//////////
		// Iterate through each row grabbing floan positions
		//////
			for (lnY = 0; lnY < lbi.biHeight; lnY++)
			{
				// Iterate all the way across
				lbgr = (SBgr*)((s8*)lbgrBuffer + (lnY * lnRowWidth));

				// Look for where things start or stop
				lfLastGray = 1.0;		// Assume we start on a white pixel
				for (lnX = 0; lnX < lbi.biWidth; lnX++, lbgr++)
				{
					// Determine the grayscale value of this pixel
					lfGray = (((f64)lbgr->red * 0.35f) + ((f64)lbgr->grn * 0.54f) + ((f64)lbgr->blu * 0.11f)) / 255.0f;

					// Has something changed?
					if (fabs(lfGray - lfLastGray) > 0.9f)
					{
						// Store the position
						point.x = (f64)lnX	/ (f64)lbi.biWidth;
						point.y = (f64)lnY	/ (f64)lbi.biHeight;

						// Make sure it's on the reservation :-)
						if (point.x >= 0.0 && point.y >= 0.0)
							iBuilder_appendData(floans, (s8*)&point, sizeof(point));

						// Prepare for our next test
						lfLastGray = lfGray;
					}
				}
			}


		//////////
		// Iterate through each column grabbing floan positions
		//////
			for (lnX = 0; lnX < lbi.biWidth; lnX++)
			{
				// Iterate point by point in vertical columns
				lbgr = (SBgr*)((s8*)lbgrBuffer + (lnX * 3));

				// Look for where things start or stop
				lfLastGray = 1.0;		// Assume we start on a white pixel
				for (lnY = 0; lnY < lbi.biHeight; lnY++)
				{
					// Determine the grayscale value of this pixel
					lfGray = (((f64)lbgr->red * 0.35f) + ((f64)lbgr->grn * 0.54f) + ((f64)lbgr->blu * 0.11f)) / 255.0f;

					// Has something changed?
					if (fabs(lfGray - lfLastGray) > 0.9f)
					{
						// Store the position
						point.x = (f64)lnX	/ (f64)lbi.biWidth;
						point.y = (f64)lnY	/ (f64)lbi.biHeight;

						// Make sure it's on the reservation :-)
						if (point.x >= 0.0 && point.y >= 0.0)
							iBuilder_appendData(floans, (s8*)&point, sizeof(point));

						// Prepare for our next test
						lfLastGray = lfGray;
					}

					// Move to next row on same column
					lbgr = (SBgr*)((s8*)lbgr + lnRowWidth);
				}
			}


		//////////
		// Sort the data in Y order ascending, then X ascending
		//////
			lnOldFloanCount = floans->populatedLength / sizeof(SDsf_floanPoint);
			qsort(floans->data, lnOldFloanCount, sizeof(SDsf_floanPoint), iiGetFloanFromBitmap_qsortCallback);


		//////////
		// Wash disparate data points
		//////
// TODO: The idea is to grab the points closest to each point, and then average to use the middle, rather than the integer alias


		//////////
		// Remove duplicates
		//////
			// Begin at the beginning
			pDst = (SDsf_floanPoint*)floans->data;
			pSrc = pDst + 1;
			for (lnI = 1, lnNewFloanCount = 0; lnI < lnOldFloanCount; lnI++, pSrc++)
			{
				//////////
				// Is this one different?
				//////
					if (pDst->y != pSrc->y || pDst->x != pSrc->x)
					{
						// Yes, advance our destination pointer
						++pDst;

						// If we're not overwriting our pointer, then copy
						if (pDst != pSrc)
							memcpy(pDst, pSrc, sizeof(SDsf_floanPoint));

						// Increase our count
						++lnNewFloanCount;
					}
			}


		//////////
		// Resize (floans are already in correct order)
		//////
			iBuilder_setSize(floans, lnNewFloanCount * sizeof(SDsf_floanPoint));


		//////////
		// Copy to our CSV
		//////
			pSrc = (SDsf_floanPoint*)floans->data;
			for (lnI = 0; lnI < lnNewFloanCount; lnI++, pSrc++)
			{
				// Store the output
				sprintf(buffer, "%15.12f, %15.12f\n\0", pSrc->x, pSrc->y);

				// Append it to the builder
				iBuilder_appendData(floansCsv, buffer, strlen(buffer));
			}
			iBuilder_asciiWriteOutFile(floansCsv, (cu8*)tcFloanFilename);


		//////////
		// For debugging, populate the individual found points within the bitmap in green, and write it back out
		//////
			int					lnRowWidth_debug;
			SBgr*				lbgrBuffer_debug;
			BITMAPFILEHEADER	lbh_debug;
			BITMAPINFOHEADER	lbi_debug;
			FILE*				lfh_debug;

			memcpy(&lbh_debug, &lbh, sizeof(lbh));
			memcpy(&lbi_debug, &lbi, sizeof(lbi));

			lbi_debug.biWidth		= 400;
			lbi_debug.biHeight		= 400;
			lnRowWidth_debug		= iComputeRowWidth(lbi_debug.biWidth);
			lbi_debug.biSizeImage	= lnRowWidth_debug * lbi_debug.biHeight;
			lbh_debug.bfSize		= sizeof(lbh_debug) + sizeof(lbi_debug) + lbi_debug.biSizeImage;
			lbgrBuffer_debug		= (SBgr*)malloc(lbi_debug.biSizeImage);
			memset(lbgrBuffer_debug, 255, lbi_debug.biSizeImage);

			pSrc = (SDsf_floanPoint*)floans->data;
			for (lnI = 0; lnI < lnNewFloanCount; lnI++, pSrc++)
			{
				// Re-acquire our position
				lnX = (s32)(pSrc->x * (f64)lbi_debug.biWidth);
				lnY = (s32)(pSrc->y * (f64)lbi_debug.biHeight);

				// Store it
				lbgr = (SBgr*)((s8*)lbgrBuffer_debug + (lnY * lnRowWidth_debug) + (lnX * 3));

				// Make it black
				lbgr->red	= 0;
				lbgr->grn	= 0;
				lbgr->blu	= 0;
			}
			char filename[_MAX_FNAME];
			sprintf(filename, "ascii_%03u.bmp\0", tnAscii);
			lfh_debug = fopen(filename, "wb+");
			fwrite(&lbh_debug, 1, sizeof(lbh_debug), lfh_debug);
			fwrite(&lbi_debug, 1, sizeof(lbi_debug), lfh_debug);
			fwrite(lbgrBuffer_debug, 1, lbi_debug.biSizeImage, lfh_debug);
			fclose(lfh_debug);
//			_asm nop;
//			DeleteFileA(filename);


		//////////
		// Clean house
		//////
			iBuilder_freeAndRelease(&floans);
			iBuilder_freeAndRelease(&floansCsv);


		//////////
		// Indicate our success
		//////
			return(lnNewFloanCount);
	}




//////////
//
// QSORT() callback, orders data by Y ascending, then by X ascending.
//
//////
	int iiGetFloanFromBitmap_qsortCallback(const void* l, const void* r)
	{
		SDsf_floanPoint*	left;
		SDsf_floanPoint*	right;


		// Get our pointers properly
		left	= (SDsf_floanPoint*)l;
		right	= (SDsf_floanPoint*)r;

		// See how the cookie crumbles
		     if (left->y < right->y)		return(-1);		// Left is less than right
		else if (left->y > right->y)		return(1);		// Left is greater than right
		else if (left->x < right->x)		return(-1);		// Left is less than right
		else if (left->x > right->x)		return(1);		// Left is greater than right
		else								return(0);		// They're equal
	}




//////////
//
// Called to create a window of the indicated size, and setup the bitmap and DibSection bd bits.
//
//////
	u32 iDsf_createWindow(SDsf_hwnd* h)
	{
		ATOM			atom;
		WNDCLASSEXA		classa;
		RECT			lrc;


		//////////
		// Register the class if need be
		//////
			if (!GetClassInfoExA(ghInstance, cgcPreviewWindowClass, &classa))
			{
				// Initialize
				memset(&classa, 0, sizeof(classa));

				// Populate
				classa.cbSize				= sizeof(WNDCLASSEXA);
				classa.hInstance			= ghInstance;
				classa.style				= CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
				classa.lpszClassName		= cgcPreviewWindowClass;
				classa.lpfnWndProc			= (WNDPROC)GetWindowLong(h->hwndParent, GWL_WNDPROC);

				// Register
				atom = RegisterClassExA(&classa);
				if (!atom)
					return(0);		// Failure
			}
		


		//////////
		// Create the window
		//////
			h->hwnd = CreateWindowA(cgcPreviewWindowClass, cgcPreviewWindowClass, WS_CHILD, h->x, h->y, h->w, h->h, h->hwndParent, NULL, ghInstance, (LPVOID)h);
			if (h->_hwnd)
			{
				// Update the WNDPROC handler so we receive messages
				h->oldWndProcAddress = (WNDPROC)GetWindowLong(h->hwnd, GWL_WNDPROC);
				SetWindowLong(h->hwnd, GWL_WNDPROC, (long)&iDsf_wndProc_callback);

				// Add a timer for markup windows (there should only be one)
				if (h->markup && gnTimer == 0)
					gnTimer = SetTimer(h->hwnd, (u32)h, 33, NULL);		// Create a timer to read the mouse 30 times per second

				// Create a DIB Section for accessing this window's bits
				SetRect(&h->rc, h->x, h->y, (h->x + h->w), (h->y + h->h));
				h->hdc	= CreateCompatibleDC(GetDC(h->hwnd));
				h->hbmp	= CreateDIBSection(h->hdc, (BITMAPINFO*)&h->bi, DIB_RGB_COLORS, (void**)&h->bd, NULL, 0);
				SelectObject(h->hdc, h->hbmp);

				// Create a second DIB Section for drawing real-time mouse events
				h->hdc2		= CreateCompatibleDC(GetDC(h->hwnd));
				h->hbmp2	= CreateDIBSection(h->hdc2, (BITMAPINFO*)&h->bi, DIB_RGB_COLORS, (void**)&h->bd2, NULL, 0);
				SelectObject(h->hdc2, h->hbmp2);

				// Create a gray brush
				h->backDarkGrayBrush = CreateSolidBrush(RGB(background.red, background.grn, background.blu));

				// Create a font for rendering the X,Y coordinate in the lower-right
				s32 lnHeight = -MulDiv(8, GetDeviceCaps(GetDC(GetDesktopWindow()), LOGPIXELSY), 72);
				h->fontXY = CreateFontA(lnHeight, 0, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, NONANTIALIASED_QUALITY, FF_DONTCARE, "Tahoma");

				// Make it initially gray
				SetRect(&lrc, 0, 0, h->w, h->h);
				FillRect(h->hdc, &lrc, h->backDarkGrayBrush);
				InvalidateRect(h->hwnd, NULL, FALSE);

				// Make it visible
				ShowWindow(h->hwnd, SW_SHOW);

			} else {
				int error = GetLastError();
				_asm int 3;
			}

			// Indicate our status
			return(h->_hwnd);
	}




//////////
//
// Called to create the control window for contextual things related to the selected control.
//
//////
	u32 iDsf_createControlWindow(SDsf_hwnd* h, u32 tnX, u32 tnY, u32 tnW, u32 tnH)
	{
		ATOM			atom;
		WNDCLASSEXA		classa;
		RECT			lrc;


		//////////
		// Register the class if need be
		//////
			if (!GetClassInfoExA(ghInstance, cgcControlWindowClass, &classa))
			{
				// Initialize
				memset(&classa, 0, sizeof(classa));

				// Populate
				classa.cbSize				= sizeof(WNDCLASSEXA);
				classa.hInstance			= ghInstance;
				classa.style				= CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
				classa.lpszClassName		= cgcControlWindowClass;
				classa.lpfnWndProc			= (WNDPROC)GetWindowLong(h->hwndParent, GWL_WNDPROC);

				// Register
				atom = RegisterClassExA(&classa);
				if (!atom)
					return(0);		// Failure
			}
		


		//////////
		// Create the window
		//////
			// Bitmap info
			h->biControl.biSize				= sizeof(h->biControl);
			h->biControl.biWidth			= tnW;
			h->biControl.biHeight			= tnH;
			h->biControl.biPlanes			= 1;
			h->biControl.biBitCount			= 24;
			h->biControl.biXPelsPerMeter	= 3270;
			h->biControl.biYPelsPerMeter	= 3270;
			h->biControl.biSizeImage		= h->rowWidth * tnH;

			// Bitmap header
			h->bhControl.bfType				= 'MB';
			h->bhControl.bfOffBits			= sizeof(h->bhControl) + sizeof(h->biControl);
			h->bhControl.bfSize				= h->bhControl.bfOffBits + h->biControl.biSizeImage;

			// Window
			h->hwndControl = CreateWindowA(cgcControlWindowClass, cgcControlWindowClass, WS_CHILD, tnX, tnY, tnW, tnH, h->hwndParent, NULL, ghInstance, (LPVOID)h);
			if (h->_hwndControl)
			{
				// Update the WNDPROC handler so we receive messages
				SetWindowLong(h->hwndControl, GWL_WNDPROC, (long)&iDsf_control_wndProc_callback);

				// Create a DIB Section for accessing this window's bits
				SetRect(&h->rcControl, tnX, tnY, (tnX + tnY), (tnY + tnH));
				h->hdcControl	= CreateCompatibleDC(GetDC(h->hwndControl));
				h->hbmpControl	= CreateDIBSection(h->hdcControl, (BITMAPINFO*)&h->biControl, DIB_RGB_COLORS, (void**)&h->bdControl, NULL, 0);
				SelectObject(h->hdcControl, h->hbmpControl);

				// Make it initially white
				SetRect(&lrc, 0, 0, tnW, tnH);
				FillRect(h->hdcControl, &lrc, (HBRUSH)GetStockObject(WHITE_BRUSH));
				InvalidateRect(h->hwndControl, NULL, FALSE);

				// Make it visible
				ShowWindow(h->hwndControl, SW_SHOW);

			} else {
				int error = GetLastError();
				_asm int 3;
			}

			// Indicate our status
			return(h->_hwndControl);
	}




//////////
//
// Callback for the control window
//
//////
	LRESULT CALLBACK iDsf_control_wndProc_callback(HWND hwnd, UINT m, WPARAM w, LPARAM l)
	{
		u32				lnI;
		PAINTSTRUCT		ps;
		HDC				lhdc;
		union {
			HWND		thisHwnd;
			u32			_thisHwnd;
		};
		union {
			HWND		hwndParent;
			u32			_hwndParent;
		};
		SDsf_hwnd*		h;
		SDsf*			dsf;


		// See if we know this hwnd
		thisHwnd	= hwnd;
		hwndParent	= GetParent(hwnd);
		for (lnI = 0; lnI < gsRootDsfs->populatedLength; lnI += sizeof(SDsf))
		{
			// Grab the pointer
			dsf = (SDsf*)(gsRootDsfs->data + lnI);

			// See if we're found on this instance
			h = iDsf_findOnlyHwnd_byHwndControl(dsf->hwnds, _hwndParent, _thisHwnd);
			if (h)
			{
				// It was one of our windows
				switch (m)
				{
					// Redraw the window
					case WM_PAINT:
						// Paint it
						lhdc = BeginPaint(hwnd, &ps);
						BitBlt(lhdc, 0, 0, h->w, h->h, h->hdcControl, 0, 0, SRCCOPY);
						EndPaint(hwnd, &ps);
						// All done
						// Indicate to Windows that we processed it
						return 0;
				}
				// Call Windows' default procedure handler
				return(DefWindowProc(hwnd, m, w, l));
			}
		}
		// Call Windows' default procedure handler
		return(DefWindowProc(hwnd, m, w, l));

	}




//////////
//
// Callback for the render and final windows
//
//////
	LRESULT CALLBACK iDsf_wndProc_callback(HWND hwnd, UINT m, WPARAM w, LPARAM l)
	{
		u32				lnI;
		PAINTSTRUCT		ps;
		HDC				lhdc;
		union {
			HWND		thisHwnd;
			u32			_thisHwnd;
		};
		union {
			HWND		hwndParent;
			u32			_hwndParent;
		};
		SDsf_hwnd*		h;
		SDsf*			dsf;


		// See if we know this hwnd
		thisHwnd	= hwnd;
		hwndParent	= GetParent(hwnd);
		for (lnI = 0; lnI < gsRootDsfs->populatedLength; lnI += sizeof(SDsf))
		{
			// Grab the pointer
			dsf = (SDsf*)(gsRootDsfs->data + lnI);

			// See if we're found on this instance
			h = iDsf_findOnlyHwnd_byHwnd(dsf->hwnds, _hwndParent, _thisHwnd);
			if (h)
			{
				// It was one of our windows
				switch (m)
				{
					// Get the mouse and keyboard state
					case WM_TIMER:
						iDsf_readMousePosition(dsf, h);
						break;

					// Redraw the window
					case WM_PAINT:
						// Paint it
						lhdc = BeginPaint(hwnd, &ps);
						BitBlt(lhdc, 0, 0, h->w, h->h, h->hdc, 0, 0, SRCCOPY);
						EndPaint(hwnd, &ps);
						// All done
						// Indicate to Windows that we processed it
						return 0;
				}
				// Call Windows' default procedure handler
				return(DefWindowProc(hwnd, m, w, l));
			}
		}
		// Call Windows' default procedure handler
		return(DefWindowProc(hwnd, m, w, l));
	}
