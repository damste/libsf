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
