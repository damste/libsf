//////////
//
// /libsf/source/vjr/source/vjr_globals.h
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
// Global Variables
//////
	HINSTANCE			ghInstance							= null0;
	bool				glShuttingDown						= false;
//	ITaskbarList*		giTaskbar							= NULL;
	SThisCode*			_thisCodeNull						= NULL;


//////////
// TOOD: We need to add semaphores to these because the ultimate goal is to allow multiple
//       threads running simultaneously, but each of them running completely independent programs.
// BEGIN
//////
	SBuilder*			gWindows							= NULL;
	SBuilder*			gFonts								= NULL;
	SBuilder*			gBreakpoints						= NULL;
//////
// END
//////////

	HWND				ghwndMsg							= null0;
	CRITICAL_SECTION	cs_uniqueIdAccess;
	CRITICAL_SECTION	cs_logData;
	u32					gnNextUniqueId						= 0;
	s64					systemStartedMs						= 0;
	u32					systemStartedTickCount				= 0;

	// For splash aria and general sound support
	static union {
		s8*				soundData_s8;
		f32*			soundData_f32;
	};
	u32					soundOffset, soundCount;

	// Main screen display history, and system log data
	SEM*				screenData							= NULL;									// The data displayed on the screen
	SEM*				systemLog							= NULL;									// The data displayed on the screen

	// Loaded DLLs
	SDllLib*			gsRootDllLib						= NULL;									// Pointer to first loaded DLL
	SDll*				gsRootDll							= NULL;									// Pointer to first function from a DLL that's been defined

	// Global variables
	SVariable*			varGlobals							= NULL;									// All global variables are stored

	// Specific variables in the global variable pool
	SVariable*			varAsciiCols					 	= NULL;
	SVariable*			varAsciiRows						= NULL;
	SVariable*			varBeautify							= NULL;
	SVariable*			varBrowser							= NULL;
	SVariable*			varBuilder							= NULL;
	SVariable*			varCalcMem							= NULL;
	SVariable*			varCalcValue						= NULL;
	SVariable*			varCliptext							= NULL;
	SVariable*			varCodesense						= NULL;
	SVariable*			varConverter						= NULL;
	SVariable*			varCoverage							= NULL;
	SVariable*			varDblclick							= NULL;
	SVariable*			varDiaryDate						= NULL;
	SVariable*			varDos								= NULL;
	SVariable*			varFoxcode							= NULL;
	SVariable*			varFoxref							= NULL;
	SVariable*			varFoxtask							= NULL;
	SVariable*			varGallery							= NULL;
	SVariable*			varGenhtml							= NULL;
	SVariable*			varGenmenu							= NULL;
	SVariable*			varGetexpr							= NULL;
	SVariable*			varIncseek							= NULL;
	SVariable*			varInclude							= NULL;
	SVariable*			varMac								= NULL;
	SVariable*			varMeta1							= NULL;
	SVariable*			varMeta2							= NULL;
	SVariable*			varMeta3							= NULL;
	SVariable*			varMeta4							= NULL;
	SVariable*			varMeta5							= NULL;
	SVariable*			varMeta6							= NULL;
	SVariable*			varMeta7							= NULL;
	SVariable*			varMeta8							= NULL;
	SVariable*			varMeta9							= NULL;
	SVariable*			varMline							= NULL;
	SVariable*			varObjectBrowser					= NULL;
	SVariable*			varPageno							= NULL;
	SVariable*			varPagetotal						= NULL;
	SVariable*			varPretext							= NULL;
	SVariable*			varReportBuilder					= NULL;
	SVariable*			varReportOutput						= NULL;
	SVariable*			varReportpreview					= NULL;
	SVariable*			varSamples							= NULL;
	SVariable*			varScctext							= NULL;
	SVariable*			varScreen							= NULL;
	SVariable*			varShell							= NULL;
	SVariable*			varSpellchk							= NULL;
	SVariable*			varStartup							= NULL;
	SVariable*			varStartupTime						= NULL;
	SVariable*			varTasklist							= NULL;
	SVariable*			varTaskpane							= NULL;
	SVariable*			varTally							= NULL;
	SVariable*			varText								= NULL;
	SVariable*			varThrottle							= NULL;
	SVariable*			varToolbox							= NULL;
	SVariable*			varTriggerlevel						= NULL;
	SVariable*			varUnix								= NULL;
	SVariable*			varVfp								= NULL;
	SVariable*			varWindows							= NULL;
	SVariable*			varWizard							= NULL;


	// Constant variables (used for reference)
	SVariable*			cvarSpace1							= NULL;									// Holds a single space, and is a constant
	SVariable*			cvarEmptyString						= NULL;
	SVariable*			cvarSpace2000						= NULL;
	SVariable*			cvarZero							= NULL;									// A constant 0
	SVariable*			cvarTrue							= NULL;									// A constant .T.
	SVariable*			cvarFalse							= NULL;									// A constant .F.
	SVariable*			cvarSix								= NULL;									// A numeric value of 6, used for padding widths
	SVariable*			cvarEight							= NULL;									// A numeric value of 8, used for BITS8()
	SVariable*			cvarSixteen							= NULL;									// A numeric value of 16, used for BITS16()
	SVariable*			cvarThirtyTwo						= NULL;									// A numeric value of 32, used for BITS32()
	SVariable*			cvarSixtyFour						= NULL;									// A numeric value of 64, used for BITS64()
	SVariable*			cvarTwoFiftyFive					= NULL;									// A numeric value of 255, used for color channels
	SVariable*			cvarFiftyPercent					= NULL;									// An f32 0.5
	SVariable*			cvarOneHundredPercent				= NULL;									// An f32 1.0
	SVariable*			cvarSetDateAmerican					= NULL;
	SVariable*			cvarSetDateAnsi						= NULL;
	SVariable*			cvarSetDateBritish					= NULL;
	SVariable*			cvarSetDateFrench					= NULL;
	SVariable*			cvarSetDateGerman					= NULL;
	SVariable*			cvarSetDateItalian					= NULL;
	SVariable*			cvarSetDateJapan						= NULL;
	SVariable*			cvarSetDateTaiwan					= NULL;
	SVariable*			cvarSetDateLong						= NULL;
	SVariable*			cvarSetDateShort						= NULL;
	SVariable*			cvarSetDateUsa						= NULL;
	SVariable*			cvarSetDateDmy						= NULL;
	SVariable*			cvarSetDateMdy						= NULL;
	SVariable*			cvarSetDateYmd						= NULL;
	SVariable*			varSetDateYyyyMmDdTHhMmSsMss		= NULL;
	SVariable*			varSetDateYyyyMmDdTHhMmSs			= NULL;



	// Default variable values used for references
	SVariable*			varDefault_null						= NULL;									// NULL
	SVariable*			varDefault_numeric					= NULL;									// "   0"
	SVariable*			varDefault_s32						= NULL;									// 0
	SVariable*			varDefault_u32						= NULL;									// 0
	SVariable*			varDefault_f32						= NULL;									// +0.0
	SVariable*			varDefault_s64						= NULL;									// 0
	SVariable*			varDefault_u64						= NULL;									// 0
	SVariable*			varDefault_f64						= NULL;									// +0.0
	SVariable*			varDefault_date						= NULL;									// "  /  /    "
	SVariable*			varDefault_datetime					= NULL;									// "  /  /       :  :     "
	SVariable*			varDefault_datetimex				= NULL;									// "  /  /       :  :  .         "
	SVariable*			varDefault_currency					= NULL;									// 0.0000
	SVariable*			varDefault_s16						= NULL;									// 0
	SVariable*			varDefault_u16						= NULL;									// 0
	SVariable*			varDefault_s8						= NULL;									// 0
	SVariable*			varDefault_u8						= NULL;									// 0
	SVariable*			varDefault_logical					= NULL;									// .F.
	SVariable*			varDefault_bitmap					= NULL;									// 1x1 white pixel bitmap
	SVariable*			varDefault_thiscode					= NULL;									// An empty function with no executable code, no parameters, no variables, and no parents

	// Focus highlight windows, and tooltip window
	SBuilder*			gFocusHighlights					= NULL;									// Holds SFocusHighlight structures
	SSplash				gSplash;																	// For the active splash screen

	// Global sourceLight accumulator window
	SBitmap*			bmpSourceLight						= NULL;									// SourceLight is always contextual.  This bitmap is constantly created and destroyed.
	s32					gnSourceLightX						= _SOURCELIGHT_MARGIN;
	s32					gnSourceLightY						= _SOURCELIGHT_MARGIN;

	// App icons
	SBitmap*			bmpVjrIcon							= NULL;
	SBitmap*			bmpVjrSplash						= NULL;
	SBitmap*			bmpJDebiIcon						= NULL;
	SBitmap*			bmpSourceCodeIcon					= NULL;
	SBitmap*			bmpLocalsIcon						= NULL;
	SBitmap*			bmpWatchIcon						= NULL;
	SBitmap*			bmpCommandIcon						= NULL;
	SBitmap*			bmpDebugIcon						= NULL;
	SBitmap*			bmpOutputIcon						= NULL;
	SBitmap*			bmpSourceLightIcon					= NULL;

	// Carousel
	SBitmap*			bmpCarouselCarouselIcon				= NULL;
	SBitmap*			bmpCarouselTabsIcon					= NULL;
	SBitmap*			bmpCarouselPad						= NULL;
	SBitmap*			bmpCarouselIcon						= NULL;
	SBitmap*			bmpCarouselRiderTabClose			= NULL;

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

	// Dapple
	SBitmap*			bmpDapple1							= NULL;
	SBitmap*			bmpDapple1Tmp						= NULL;
	SBitmap*			bmpDapple2							= NULL;
	SBitmap*			bmpDapple2Tmp						= NULL;


//////////
// Cask graphics
// BEGIN
//////
	SBitmap*			bmpCaskIconsTiled					= NULL;			// Single master icon file
	SBitmap*			bmpCaskRoundLeft					= NULL;
	SBitmap*			bmpCaskRoundRight					= NULL;
	SBitmap*			bmpCaskSquareLeft					= NULL;
	SBitmap*			bmpCaskSquareRight					= NULL;
	SBitmap*			bmpCaskTriangleLeft					= NULL;
	SBitmap*			bmpCaskTriangleRight				= NULL;
	SBitmap*			bmpCaskTildeLeft					= NULL;
	SBitmap*			bmpCaskTildeRight					= NULL;
	SBitmap*			bmpCaskPips1						= NULL;
	SBitmap*			bmpCaskPips2						= NULL;
	SBitmap*			bmpCaskPips3						= NULL;
	SBitmap*			bmpCaskSideExtender					= NULL;
	SBitmap*			bmpCaskSideExtenderLeft				= NULL;
	SBitmap*			bmpCaskSideExtenderMiddle			= NULL;
	SBitmap*			bmpCaskSideExtenderRight			= NULL;
	SBitmap*			bmpCaskExtenderMiddle				= NULL;
	SBitmap*			bmpCaskExtenderLeft1				= NULL;
	SBitmap*			bmpCaskExtenderLeft2				= NULL;
	SBitmap*			bmpCaskExtenderRight2				= NULL;
	SBitmap*			bmpCaskExtenderRight1				= NULL;
// TODO:  Cask boxes, 13 additional pieces
	SBgra				caskOrange1;
	SBgra				caskOrange2;
	SBgra				caskOrange3;
	SBgra				caskRed1;
	SBgra				caskRed2;
	SBgra				caskRed3;
	SBgra				caskBlue1;
	SBgra				caskBlue2;
	SBgra				caskBlue3;
	SBgra				caskPurple1;
	SBgra				caskPurple2;
	SBgra				caskPurple3;
	SBgra				caskCyan1;
	SBgra				caskCyan2;
	SBgra				caskCyan3;
	SBgra				caskGreen1;
	SBgra				caskGreen2;
	SBgra				caskGreen3;
	SBgra				caskYellow1;
	SBgra				caskYellow2;
	SBgra				caskYellow3;
	SBgra				caskGray1;
	SBgra				caskGray2;
	SBgra				caskGray3;
	SBgra				caskWhite1;
	SBgra				caskWhite2;
	SBgra				caskWhite3;
	SBgra				caskBlack1;
	SBgra				caskBlack2;
	SBgra				caskBlack3;
//////
// END
//////////


//////////
// General icons
// BEGIN
//////
	// Actual bitmaps
	SBitmap*	bmpArrayTiled								= NULL;
	SBitmap**	bmpArray									= NULL;

	//////////
	// Note:  The structure of the bxmpArrayBmp must follow this general pattern:
	//			<jdebi>
	//				<icons file="array_bmp.bmp" ulx="2" uly="2" width="36" height="36" stridex="38" stridey="38">
	//					<icon name="internalToken" tip="A tooltip text to display when hovering"/>
	//				</icons>
	//			</jdebi>
	//////
	// Note:  This file is hard-coded into the vjr.exe build.
	//  See:  \libsf\source\vjr\source\bmps\graphics\raw_tiled\array_bmp.bxml
	//////
		CXml*	bxmlArrayBmp								= NULL;
		CXml*	bxmlArrayBmpIcons							= NULL;
//////
// END
//////////


	// For accomplishments
	SBitmap*			bmpStoplightRed						= NULL;
	SBitmap*			bmpStoplightAmber					= NULL;
	SBitmap*			bmpStoplightGreen					= NULL;
	SBitmap*			bmpStoplightBlue					= NULL;

	// For breakpoints
	SBitmap*			bmpBreakpointAlways					= NULL;
	SBitmap*			bmpBreakpointAlwaysCountdown		= NULL;
	SBitmap*			bmpConditionalTrue					= NULL;
	SBitmap*			bmpConditionalFalse					= NULL;
	SBitmap*			bmpConditionalTrueCountdown			= NULL;
	SBitmap*			bmpConditionalFalseCountdown		= NULL;


	// Default screens used by VJr
	SObject*			_settings							= NULL;
	SObject*			_screen								= NULL;
	SObject*			_screen_editbox						= NULL;
	SObject*			_jdebi								= NULL;
	SObject*			jdebiToolbarsContainer				= NULL;
	SObject*			_sourceCode							= NULL;
	SObject*			_locals								= NULL;
	SObject*			_watch								= NULL;
	SObject*			_cmd								= NULL;
	SObject*			_debug								= NULL;
	SObject*			_output								= NULL;
	SObject*			_sourceLight						= NULL;
	SObject*			_sourceLight_empty					= NULL;
	SObject*			_sourceCode_carousel				= NULL;
	SObject*			_sourceCode_rider					= NULL;
	SObject*			_sourceCode_editbox					= NULL;
	SObject*			_locals_editbox						= NULL;
	SObject*			_watch_editbox						= NULL;
	SObject*			_command_editbox					= NULL;
	SObject*			_debug_editbox						= NULL;
	SObject*			_output_editbox						= NULL;
	SObject*			gobj_splashListing					= NULL;
	SObject*			gobj_splashListingEditbox			= NULL;

	// Windows related to the objects
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
	SObject*			gobj_defaultCmdGroup				= NULL;
	SObject*			gobj_defaultOptGroup				= NULL;
	SObject*			gobj_defaultListbox					= NULL;
	SObject*			gobj_defaultCombobox				= NULL;
	SObject*			gobj_defaultFormset					= NULL;
	SObject*			gobj_defaultToolbar					= NULL;
	SObject*			gobj_defaultSeparator				= NULL;
	SObject*			gobj_defaultLine					= NULL;
	SObject*			gobj_defaultShape					= NULL;
	SObject*			gobj_defaultContainer				= NULL;
	SObject*			gobj_defaultControl					= NULL;
	SObject*			gobj_defaultGrid					= NULL;
	SObject*			gobj_defaultColumn					= NULL;
	SObject*			gobj_defaultHeader					= NULL;
	SObject*			gobj_defaultOleBound				= NULL;
	SObject*			gobj_defaultOleContain				= NULL;
	SObject*			gobj_defaultSpinner					= NULL;
	SObject*			gobj_defaultTimer					= NULL;
	SObject*			gobj_defaultHyperlink				= NULL;
	SObject*			gobj_defaultCollection				= NULL;
	SObject*			gobj_defaultPage					= NULL;
	SObject*			gobj_defaultPageFrame				= NULL;
	SObject*			gobj_defaultSession					= NULL;
	SObject*			gobj_defaultCustom					= NULL;
	SObject*			gobj_defaultException				= NULL;
	SObject*			gobj_defaultSettings				= NULL;


	//////////
	// General defaults
	//////
		SFont*			gsFontDefault						= NULL;									// Ubuntu 10 pt
		SFont*			gsFontDefault9						= NULL;									// Ubuntu 9 pt
		SFont*			gsFontDefaultBold					= NULL;									// Ubuntu 10 pt bold
		SFont*			gsFontDefaultItalic8				= NULL;									// Ubuntu 9 pt Italic
		SFont*			gsFontDefaultFixedPoint				= NULL;									// Ubuntu Mono 10 pt
		SFont*			gsWindowTitleBarFont				= NULL;									// Ubuntu Condensed Bold 12 pt
		SFont*			gsWindowTitleBarFontSubform			= NULL;									// Ubuntu Condensed Bold 10 pt
		SFont*			gsFontDefaultTooltip				= NULL;									// Ubuntu Condensed Bold 9 pt
		SFont*			gsFontCask							= NULL;									// Cask font, Ubuntu Bold 30 pt
		// Global colors
		const SBgra		whiteColor							= { _whiteColor };
		const SBgra		grayColor							= { _grayColor };
		const SBgra		blackColor							= { _blackColor };
		const SBgra		yellowColor							= { rgba(255, 255, 0, 255) };
		const SBgra		redColor							= { rgba(255, 0, 0, 255) };
		const SBgra		greenColor							= { rgba(0, 255, 0, 255) };
		const SBgra		blueColor							= { rgba(0, 0, 255, 255) };
		const SBgra		cyanColor							= { rgba(0, 255, 255, 255) };
		const SBgra		orangeColor							= { rgba(255, 200, 64, 255) };
		const SBgra		fuchsiaColor						= { rgba(255, 255, 0, 255) };
		const SBgra		darkRedColor						= { rgba(80, 0, 0, 255) };
		const SBgra		darkOrangeColor						= { rgba(128, 64, 0, 255) };
		const SBgra		darkGreenColor						= { rgba(0, 80, 0, 255) };
		const SBgra		darkBlueColor						= { rgba(0, 0, 80, 255) };
		const SBgra		pastelYellowColor					= { rgba(255, 255, 192, 255) };
		const SBgra		pastelRedColor						= { rgba(255, 210, 210, 255) };
		const SBgra		pastelOrangeColor					= { rgba(255, 215, 164, 255) };
		const SBgra		pastelGreenColor					= { rgba(192, 255, 192, 255) };
		const SBgra		pastelBlueColor						= { rgba(210, 210, 255, 255) };
		const SBgra		maskColor							= { rgba(222, 22, 222, 255) };			// Hideous fuscia (by design)
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
		SBgra			toolbarBackColor					= { _nwColor };


		// Forms four-corner window color schemes (eventually these will be loaded from themes.dbf)
// Orange theme:
		const SBgra		NwFocusColor						= { _nwFocusColor };
		const SBgra		NeFocusColor						= { _neFocusColor };
		const SBgra		SwFocusColor						= { _swFocusColor };
		const SBgra		SeFocusColor						= { _seFocusColor };
// Purple theme
// 		const SBgra		NwFocusColor						= { rgba(233, 219, 255, 255) };
// 		const SBgra		NeFocusColor						= { rgba(205, 172, 255, 255) };
// 		const SBgra		SwFocusColor						= { rgba(233, 219, 255, 255) };
// 		const SBgra		SeFocusColor						= { rgba(182, 153, 226, 255) };

		// Subforms four-corner window color schemes (eventually these will be loaded from themes.dbf)
// Golden theme:
// 		SBgra			NwColor2							= { rgba(245, 225, 175, 255) };
// 		SBgra			NeColor2							= { rgba(252, 242, 192, 25) };			// Less pastel yellow, somewhat pale
// 		SBgra			SwColor2							= { rgba(249, 222, 133, 255) };			// Orange/golden yellow
// 		SBgra			SeColor2							= { rgba(247, 210, 96, 255) };			// More orange/golden yellow
// Blue theme:
		const SBgra		NwNonfocusColor						= { _nwColor };
		const SBgra		NeNonfocusColor						= { _neColor };
		const SBgra		SwNonfocusColor						= { _swColor };
		const SBgra		SeNonfocusColor						= { _seColor };
// Orange theme:
// 		const SBgra		NwColor2							= { rgba(255, 222, 156, 255) };
// 		const SBgra		NeColor2							= { rgba(255, 200, 92, 255) };
// 		const SBgra		SwColor2							= { rgba(255, 222, 156, 255) };
// 		const SBgra		SeColor2							= { rgba(229, 180, 83, 255) };

		// Colors for checkbox corners
		const SBgra		NwCheckboxOnColor					= { rgba(24, 153, 2, 255) };			// Green
		const SBgra		NeCheckboxOnColor					= { rgba(37, 163, 3, 255) };
		const SBgra		SwCheckboxOnColor					= { rgba(5, 140, 0, 255) };
		const SBgra		SeCheckboxOnColor					= { rgba(131, 220, 11, 255) };
		const SBgra		NwCheckboxOffColor					= { rgba(193, 34, 34, 255) };			// Red
		const SBgra		NeCheckboxOffColor					= { rgba(181, 64, 64, 255) };
		const SBgra		SwCheckboxOffColor					= { rgba(171, 92, 94, 255) };
		const SBgra		SeCheckboxOffColor					= { rgba(212, 128, 131, 255) };

		// Colors for the focus window
		SBgra			focusHighlightReadWriteColor		= { rgba(112, 164, 255, 255) };
		SBgra			focusHighlightReadOnlyColor			= { rgba(255, 112, 112, 255) };


	//////////
	// Mouse options
	//////
		bool			glIsMoving							= false;
		bool			glIsResizing						= false;
		bool			glIsMouseOverSplash					= false;

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

