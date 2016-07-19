//////////
//
// /libsf/utils/common/cpp/include/colors.h
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
// Version 0.10
// Copyright (c) 2016 by Rick C. Hodgin
//////
// Last update:
//     Mar.17.2016
//////
// Change log:
//     Mar.17.2016	- Initial creation
//////
//
// This file is self-contained and handles all builder algorithms.  It can be used as an include
// file for other stand-alone projects.  It was extracted from the Visual FreePro Virtual Machine.
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
//
// Thank you.  And may The Lord bless you richly as you lift up your life, your
// talents, your gifts, your praise, unto Him.  In Jesus' name I pray.  Amen.
//
//////////




//#pragma once
#ifndef __COLORS_H__
#define __COLORS_H__


//////////
// Color constants
//////
	cu32			_disabledBackColor					= rgba(255, 255, 255, 255);
	cu32			_disabledForeColor					= rgba(192, 192, 230, 255);

	cu32			_focusObjColor_readWrite_container	= rgba(97,31,128, 255);
	cu32			_focusObjColor_readWrite_obj		= rgba(112,164,255, 255);
	cu32			_focusObjColor_readOnly				= rgba(255, 112, 112, 255);


	// Color theme per Stefano D'Amico, suggested Mar.25.2015
	cu32			_nwColor_form						= rgba(35,101,178,255);
	cu32			_neColor_form						= rgba(37,108,192,255);
	cu32			_swColor_form						= rgba(37,108,192,255);
	cu32			_seColor_form						= rgba(40,116,204,255);

	cu32			_nwColor_subform					= rgba(164,192,255,255);
	cu32			_neColor_subform					= rgba(133,185,245,255);
	cu32			_seColor_subform					= rgba(133,185,245,255);
	cu32			_swColor_subform					= rgba(164,192,255,255);

	cu32			_nwColor_focus						= rgba(205, 172, 255, 255);
	cu32			_neColor_focus						= rgba(192, 164, 235, 255);
	cu32			_swColor_focus						= rgba(192, 164, 235, 255);
	cu32			_seColor_focus						= rgba(182, 153, 226, 255);

	cu32			_whiteColor							= rgba(255, 255, 255, 255);
	cu32			_eggshellColor						= rgba(250, 245, 240, 255);
	cu32			_silverColor						= rgba(225, 225, 225, 255);
	cu32			_grayColor							= rgba(192, 192, 192, 255);
	cu32			_darkGrayColor						= rgba(128, 128, 128, 255);
	cu32			_charcoalColor						= rgba(64, 64, 64, 255);
	cu32			_blackColor							= rgba(0, 0, 0, 255);
	cu32			_selectedBackColor					= rgba(220, 235, 255, 255);
	cu32			_selectedForeColor					= rgba(0, 0, 164, 255);
	
	const SBgra		nwColor_form						= { _nwColor_form };
	const SBgra		neColor_form						= { _neColor_form };
	const SBgra		seColor_form						= { _seColor_form };
	const SBgra		swColor_form						= { _swColor_form };

	const SBgra		nwColor_subform						= { _nwColor_subform };
	const SBgra		neColor_subform						= { _neColor_subform };
	const SBgra		seColor_subform						= { _seColor_subform };
	const SBgra		swColor_subform						= { _swColor_subform };


	// Forms four-corner window color schemes (eventually these will be loaded from themes.dbf)
// Orange theme:
	const SBgra		nwColor_focus						= { _nwColor_focus };
	const SBgra		neColor_focus						= { _neColor_focus };
	const SBgra		swColor_focus						= { _swColor_focus };
	const SBgra		seColor_focus						= { _seColor_focus };

	const SBgra		nwColor_nonfocus					= { _nwColor_form };
	const SBgra		neColor_nonfocus					= { _neColor_form };
	const SBgra		swColor_nonfocus					= { _swColor_form };
	const SBgra		seColor_nonfocus					= { _seColor_form };

	// Colors for checkbox corners
	const SBgra		nwColor_checkboxOn					= { rgba(24, 153, 2, 255) };			// Green
	const SBgra		neColor_checkboxOn					= { rgba(37, 163, 3, 255) };
	const SBgra		swColor_checkboxOn					= { rgba(5, 140, 0, 255) };
	const SBgra		seColor_checkboxOn					= { rgba(131, 220, 11, 255) };
	const SBgra		nwColor_checkboxOff					= { rgba(193, 34, 34, 255) };			// Red
	const SBgra		neColor_checkboxOff					= { rgba(181, 64, 64, 255) };
	const SBgra		swColor_checkboxOff					= { rgba(171, 92, 94, 255) };
	const SBgra		seColor_checkboxOff					= { rgba(212, 128, 131, 255) };


//////////
// Colors
//////
	SBgra			tooltipNwBackColor					= { rgba(255, 254, 230, 255) };			// Pastel yellow
	SBgra			tooltipNeBackColor					= { rgba(252, 242, 192, 25) };			// Less pastel yellow, somewhat pale
	SBgra			tooltipSwBackColor					= { rgba(249, 222, 133, 255) };			// Orange/golden yellow
	SBgra			tooltipSeBackColor					= { rgba(247, 210, 96, 255) };			// More orange/golden yellow
	SBgra			tooltipForecolor					= { rgba(84, 56, 12, 255) };			// Dark chocolate brown
	SBgra			lineNumberFillColor					= { rgba(225, 245, 240, 255) };
	SBgra			lineNumberBackColor					= { rgba(215, 235, 230, 255) };
	SBgra			lineNumberForeColor					= { rgba(191, 208, 191, 255) };
	SBgra			breadcrumbBackColor					= { rgba(180, 220, 240, 255) };			// Cyanish
	SBgra			breadcrumbForeColor					= { rgba(0, 0, 164, 255) };				// Semidark blue
	SBgra			breakpointBackColor					= { rgba(180, 140, 220, 255) };			// Purplish
	SBgra			breakpointForeColor					= { rgba(64, 32, 92, 255) };			// Dark purple
	SBgra			currentStatementBackColor			= { rgba(225, 255, 192, 255) };			// Pastel lime greenish
	SBgra			currentStatementForeColor			= { rgba(0, 64, 0, 255) };				// Dark green
	SBgra			overrideMatchingBackColor			= { rgba(0, 255, 0, 255) };				// Green
	SBgra			overrideMatchingForeColor			= { rgba(0, 0, 0, 255) };				// Black
	SBgra			overrideMatchingBackColorMultiple	= { rgba(0, 255, 0, 255) };				// Green
	SBgra			overrideMatchingForeColorMultiple	= { rgba(0, 0, 0, 255) };				// Black
	SBgra			selectedBackColor					= { _selectedBackColor };				// Pastel turquoise
	SBgra			selectedForeColor					= { _selectedForeColor };				// Darkish blue
	SBgra			disabledBackColor					= { _disabledBackColor };
	SBgra			disabledForeColor					= { _disabledForeColor };
	SBgra			disabledItemBackColor				= { _disabledBackColor };
	SBgra			disabledItemForeColor				= { _disabledForeColor };
	SBgra			highlightSymbolBackColor			= { rgba(235, 220, 255, 255) };			// Very pastel purple
	SBgra			colorTracking						= { rgba(0, 0, 255, 255) };				// Blue
	f32				trackingRatio						= 0.025f;
	SBgra			colorMouseOver						= { rgba(255, 255, 0, 255) };			// Yellow
	SBgra			colorMouseDown						= { rgba(0, 255, 0, 255) };				// Green
	SBgra			editNewColor						= { rgba(64, 200, 64, 255) };			// Greenish
	SBgra			editChangedColor					= { rgba(255, 200, 64, 255) };			// Amberish
	SBgra			carouselFrameColor					= { rgba(94, 94, 128, 255) };			// Dark purleish-gray
	SBgra			carouselFrameInactiveColor			= { rgba(132, 132, 192, 255) };			// Lighter purpleish-gray
	SBgra			carouselBackColor					= { rgba(255, 255, 255, 255) };			// White
	SBgra			carouselTabBackColor				= { rgba(255, 255, 255, 255) };			// White
	SBgra			carouselTabForeColor				= { rgba(64, 64, 88, 255) };			// Darker purpleish-gray
	SBgra			carouselTabForeColorHighlight		= { rgba(32, 32, 44, 255) };			// Darkest purpleish-gray
	SBgra			toolbarBackColor					= { _nwColor_subform };

	// Colors for the focus window (highlights controls)
	SBgra			focusObjColor_readWrite_container	= { _focusObjColor_readWrite_container };
	SBgra			focusObjColor_readWrite_obj			= { _focusObjColor_readWrite_obj };
	SBgra			focusObjColor_readOnly				= { _focusObjColor_readOnly };

	// Uses an algorithm derived from Guideline 1.4 of WCAG 2 by Gregg Vanderheiden Dave Kelso, Aries Arditi
	// Black on white = 21 max contrast, with anything over 5:1 being readable at level 2, 10:1 being readable at level 3
	f32 iColors_contrastRatio_byLuminosity(SBgra fore, SBgra back)
	{
		f32 lfL1, lfL2, lfContrast;
		f32 lfFred, lfFgrn, lfFblu, lfFl, lfFredL, lfFgrnL, lfFbluL;
		f32 lfBred, lfBgrn, lfBblu, lfBl, lfBredL, lfBgrnL, lfBbluL;


		// Grab the colors as 0.0 .. 1.0 values
		lfFred = (f32)fore.red / 255.0f;
		lfFgrn = (f32)fore.grn / 255.0f;
		lfFblu = (f32)fore.blu / 255.0f;

		lfBred = (f32)back.red / 255.0f;
		lfBgrn = (f32)back.grn / 255.0f;
		lfBblu = (f32)back.blu / 255.0f;

		// Linearize (raise to 2.2 power)
		lfFredL = (f32)pow((f64)lfFred, 2.2);
		lfFgrnL = (f32)pow((f64)lfFgrn, 2.2);
		lfFbluL = (f32)pow((f64)lfFblu, 2.2);
		lfBredL = (f32)pow((f64)lfBred, 2.2);
		lfBgrnL = (f32)pow((f64)lfBgrn, 2.2);
		lfBbluL = (f32)pow((f64)lfBblu, 2.2);

		// Compute luminosity on fore and back
		lfFl = (0.2126f * lfFredL) + (0.7152f * lfFgrnL) + (0.0722f * lfFbluL);
		lfBl = (0.2126f * lfBredL) + (0.7152f * lfBgrnL) + (0.0722f * lfBbluL);

		// Get L1 max, L2 min
		lfL1 = max(lfFl, lfBl);
		lfL2 = min(lfFl, lfBl);

		// Compute the final luminosity contrast ratio
		lfContrast = 0.7f * ((lfL1 + 0.5f) / (lfL2 + 0.05f));

		// Indicate our result
		return(lfContrast);
	}

	// Taken from Checkpoint 2.2 of WCAG 1.0, values over 125 pass the "sufficient brightness" test
	f32 iColors_brightness(SBgra color)
	{
		f32 lfRed, lfGrn, lfBlu, lfBrightness;


		// Grab the colors
		lfRed = (f32)color.red / 255.0f;
		lfGrn = (f32)color.grn / 255.0f;
		lfBlu = (f32)color.blu / 255.0f;
		
		// Compute brightness
		lfBrightness = ((lfRed * 299.0f) + (lfGrn * 587.0f) + (lfBlu * 114.0f)) / 1000.0f;

		// Indicate our result
		return(lfBrightness);
	}

	// Taken from Checkpoint 2.2 of WCAG 1.0, values over 500 pass the "sufficient color difference" test
	f32 iColors_colorDifference(SBgra color1, SBgra color2)
	{
		f32 lfDifference;
		f32 lfRed1, lfGrn1, lfBlu1;
		f32 lfRed2, lfGrn2, lfBlu2;


		// Extract color channels
		lfRed1 = (f32)color1.red;
		lfGrn1 = (f32)color1.grn;
		lfBlu1 = (f32)color1.blu;

		lfRed2 = (f32)color2.red;
		lfGrn2 = (f32)color2.grn;
		lfBlu2 = (f32)color2.blu;

		// Compute the color difference
		lfDifference = (max(lfRed1, lfRed2) - min(lfRed1, lfRed2)) + (max(lfGrn1, lfGrn2) - min(lfGrn1, lfGrn2)) + (max(lfBlu1, lfBlu2) - min(lfBlu1, lfBlu2));

		// Indicate our result
		return(lfDifference);
	}

#endif	// __COLORS_H__