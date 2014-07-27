//////////
//
// /libsf/source/vjr/vjr_globals.h
//
//////
// Version 0.36
// Copyright (c) 2014 by Rick C. Hodgin
//////
// Last update:
//     Feb.12.2014
//////
// Change log:
//     Feb.12.2014 - Initial creation
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
// Global Variables
//////
	HINSTANCE			ghInstance							= NULL;
	ITaskbarList*		giTaskbar							= NULL;
	SBuilder*			gWindows							= NULL;
	SBuilder*			gFonts								= NULL;
	HWND				ghwndMsg							= NULL;
	CRITICAL_SECTION	gcsUniqueIdAccess;
	u32					gnNextUniqueId						= 0;
	s64					systemStartedMs						= 0;


	// Window display histories
	SEM*				screenData							= NULL;									// The data displayed on the screen

	// Global variables
	SVariable*			varGlobals							= NULL;									// All global variables are stored

	// App icons
	SBitmap*			bmpVjrIcon							= NULL;
	SBitmap*			bmpJDebiIcon						= NULL;
	SBitmap*			bmpSourceCodeIcon					= NULL;
	SBitmap*			bmpLocalsIcon						= NULL;
	SBitmap*			bmpWatchIcon						= NULL;
	SBitmap*			bmpCommandIcon						= NULL;
	SBitmap*			bmpDebugIcon						= NULL;
	SBitmap*			bmpOutputIcon						= NULL;

	// When there is no image
	SBitmap*			bmpNoImage							= NULL;

	// For mouse objects
	SBitmap*			bmpMove								= NULL;									// Icons used for move, minimize, maximize, close
	SBitmap*			bmpMinimize							= NULL;
	SBitmap*			bmpMaximize							= NULL;
	SBitmap*			bmpClose							= NULL;

	// For the corner triangles
	SBitmap*			bmpArrowUl							= NULL;									// Icons used for the move arrows
	SBitmap*			bmpArrowUr							= NULL;
	SBitmap*			bmpArrowLr							= NULL;
	SBitmap*			bmpArrowLl							= NULL;

	// For checkbox
	SBitmap*			bmpCheckboxOn						= NULL;
	SBitmap*			bmpCheckboxOff						= NULL;

	// For button
	SBitmap*			bmpButton							= NULL;

	// For textbox
	SBitmap*			bmpTextbox							= NULL;

	// For radio
	SBitmap*			bmpRadio							= NULL;
	SBitmap*			bmpRadioDot							= NULL;

	// Default screens used by VJr
	SObject*			gobj_screen							= NULL;
	SObject*			gobj_jdebi							= NULL;
	SObject*			sourceCode							= NULL;
	SObject*			locals								= NULL;
	SObject*			watch								= NULL;
	SObject*			command								= NULL;
	SObject*			debug								= NULL;
	SObject*			output								= NULL;
	SObject*			sourceCode_editbox					= NULL;
	SObject*			locals_editbox						= NULL;
	SObject*			locals_autos						= NULL;
	SObject*			locals_globals						= NULL;
	SObject*			locals_readwrite					= NULL;
	SObject*			locals_refactor						= NULL;
	SObject*			locals_button						= NULL;
	SObject*			locals_textbox						= NULL;
	SObject*			locals_radio						= NULL;
	SObject*			watch_editbox						= NULL;
	SObject*			command_editbox						= NULL;
	SObject*			debug_editbox						= NULL;
	SObject*			output_editbox						= NULL;

	// Windows related to the objects
	SWindow*			gWinScreen							= NULL;
	SWindow*			gWinJDebi							= NULL;

	// Default class structures
	SObject*			gobj_defaultEmpty					= NULL;
	SObject*			gobj_defaultForm					= NULL;
	SObject*			gobj_defaultSubform					= NULL;
	SObject*			gobj_defaultLabel					= NULL;
	SObject*			gobj_defaultTextbox					= NULL;
	SObject*			gobj_defaultButton					= NULL;
	SObject*			gobj_defaultImage					= NULL;
	SObject*			gobj_defaultCheckbox				= NULL;
	SObject*			gobj_defaultOption					= NULL;
	SObject*			gobj_defaultRadio					= NULL;

	//////////
	// General defaults
	//////
		SFont*			gsFontDefault						= NULL;									// Default font, Ubuntu 10 pt
		SFont*			gsFontDefault9						= NULL;									// Default font, Ubuntu 9 pt
		SFont*			gsFontDefaultBold					= NULL;									// Default font, Ubuntu 10 pt bold
		SFont*			gsFontDefaultFixedPoint				= NULL;									// Default font, Ubuntu Mono 10 pt
		SFont*			gsWindowTitleBarFont				= NULL;									// Default font, Ubuntu Bold 12 pt
		SFont*			gsWindowTitleBarFontSubform			= NULL;									// Default font, Ubuntu Bold 10 pt
		// Global colors
		const SBgra		white								= { rgba(255, 255, 255, 255) };
		const SBgra		dark_blue							= { rgba(0, 0, 80, 255) };
		const SBgra		black								= { rgba(0, 0, 0, 255) };
		const SBgra		gray								= { rgba(192, 192, 192, 255) };
		const SBgra		breadcrumbBackColor					= { rgba(180, 220, 240, 255) };			// Cyanish
		const SBgra		breadcrumbForeColor					= { rgba(0, 0, 164, 255) };				// Semidark blue
		const SBgra		breakpointBackColor					= { rgba(180, 140, 220, 255) };			// Purplish
		const SBgra		breakpointForeColor					= { rgba(64, 32, 92, 255) };			// Dark purple
		const SBgra		currentStatementBackColor			= { rgba(200, 255, 164, 255) };			// Pastel lime greenish
		const SBgra		currentStatementForeColor			= { rgba(0, 64, 0, 255) };				// Dark green
		const SBgra		selectedBackColor					= { rgba(32, 164, 255, 255) };
		const SBgra		selectedForeColor					= { rgba(255, 255, 255, 255) };
		const SBgra		disabledBackColor					= { rgba(255, 255, 255, 255) };
		const SBgra		disabledForeColor					= { rgba(192, 192, 230, 255) };
		const SBgra		colorTracking						= { rgba(0, 0, 255, 255) };				// Blue
		f32				trackingRatio						= 0.025f;
		const SBgra		colorMouseOver						= { rgba(255, 255, 0, 255) };			// Yellow
		const SBgra		colorMouseDown						= { rgba(0, 255, 0, 255) };				// Green
		const SBgra		maskColor							= { rgba(222, 22, 222, 255) };			// Hideous fuscia (by design)

		// Four-corner window color schemes (eventually these will be loaded from themes.dbf)
		const SBgra		NwColor								= { rgba(222, 230, 255, 255) };
		const SBgra		NeColor								= { rgba(177, 204, 214, 255) };
		const SBgra		SwColor								= { rgba(255, 255, 255, 255) };
		const SBgra		SeColor								= { rgba(192, 212, 255, 255) };

		// Colors for checkbox corners
		const SBgra		NwCheckboxOnColor					= { rgba(24, 153, 2, 255) };			// Green
		const SBgra		NeCheckboxOnColor					= { rgba(37, 163, 3, 255) };
		const SBgra		SwCheckboxOnColor					= { rgba(5, 140, 0, 255) };
		const SBgra		SeCheckboxOnColor					= { rgba(131, 220, 11, 255) };
		const SBgra		NwCheckboxOffColor					= { rgba(193, 34, 34, 255) };			// Red
		const SBgra		NeCheckboxOffColor					= { rgba(209, 36, 36, 255) };
		const SBgra		SwCheckboxOffColor					= { rgba(171, 30, 39, 255) };
		const SBgra		SeCheckboxOffColor					= { rgba(213, 34, 16, 255) };


	//////////
	// Mouse options
	//////
		bool			glIsMoving							= false;
		bool			glIsResizing						= false;
// 		SXYS32			gMousePositionMoveStart				= { -1, -1 };							// Mouse position when the move started
// 		SXYS32			gMousePositionMoveEnd				= { -1, -1 };							// Mouse position when the move ended
// 		SXYS32			gMousePositionResizeStart			= { -1, -1 };							// Mouse position when the resize started
// 		SXYS32			gMousePositionResizeEnd				= { -1, -1 };							// Mouse position when the resize ended
// 
// 		SXYS32			gMousePosition						= { -1, -1 };							// Mouse position indicated by windows in the interface window
// 		bool			glMouseInClientArea					= false;								// When the mouse is in the client area, this flag is raised
// 		SXYS32			gMousePositionClientArea			= { -1, -1 };							// Mouse position in the client area of the interface window
// 		SXYS32			gnMouseDelta						= { 0, 0 };								// Change in position
// 		bool			glMouseLeftButton					= false;
// 		bool			glMouseMiddleButton					= false;
// 		bool			glMouseRightButton					= false;

