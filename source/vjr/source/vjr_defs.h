//////////
//
// /libsf/source/vjr/source/vjr_defs.h
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
//////
//
// Jun.17.2014
// Note:  The function definitions below use a naming convention to indicate some of
//        their functionality.  All functions prefixed with "i" are internal functions.
//        If you see one with "ii" or "iii" they bypass standard checks (like null pointers)
//        and are only called from the internal functions.  In general, always use the
//        "i" functions if you are unsure if something will be populated or not.  If you
//        have already tested it and know it's populated, then it is safe to call an "ii"
//        function.
//
//////
//
//




struct SObjPropMap;
struct SObjEventMap;




//////////
// vjr.cpp
//////
//	int APIENTRY			WinMain									(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, s32 nCmdShow);
	void					iVjr_createOverlayListing				(SBitmap* bmp, RECT* trc);
	void					iVjr_renderOverlayListing				(SBitmap* bmp, RECT* trc);
	void					iiVjr_renderAccomplishment				(SBitmap* bmp, RECT* trc, s32 tnRAG, cs8* tcAccomplishment, cs8* tcVersion, bool tlBold, bool tlItalic, bool tlUnderline, s32 tnAdjustAccomplishmentFontSize, s32 tnAdjustVersionFontSize);
	void					iVjr_renderAccomplishments				(SBitmap* bmp, RECT* trc);

	void					iDatum_duplicate						(SDatum* datumDst, SVariable* varSrc);


//////////
// objects/base.cpp
// Note:  Property accessors are in the object_accessors.h and object_accessors.cpp source files
//////
	SObject*				iObj_create								(s32 objType, SObject* objParent, SCallback* cb_controlPointSetup = NULL, uptr _func_cb_controlPointSetup = 0);
	SObject*				iObj_addChild							(s32 objType, SObject* objParent);
	SObject*				iObj_copy								(SObject*  template_obj, SObject* prevObj, SObject* nextObj, SObject* parent, bool tlCopyChildren, bool tlCopySiblings, bool tlCreateSeparateBitmapBuffers);
	void					iObj_delete								(SObject** obj, bool tlDeleteSelf, bool tlDeleteChildren, bool tlDeleteSiblings);
	bool					iObj_setFocus							(SWindow*  win, SObject* obj, bool tlClearOtherControlsWithFocus);
	void					iObj_clearFocus							(SWindow*  win, SObject* obj, bool tlClearChildren, bool tlClearSiblings);
	SObject*				iObj_find_rootmostObject				(SObject*  obj, bool tlStopAtRiders = false, bool tlStopAtSubforms = false, bool tlStopBeforeForm = false);
	SObject*				iObj_find_rootmostRider					(SObject*  obj, bool tlStopAtFirst = false);
	s32						iObj_enum_parentRiders					(SObject*  obj, SObject** riderListArray, s32 tnRiderListCount);
	s32						iiObj_enum_parentRiders					(SObject*  obj, SObject** riderListArray, s32 tnRiderListCount, s32& tnIndex);
	bool					iObj_find_screenRect					(SObject*  obj, RECT* rc);
	bool					iObj_find_relativeRect					(SObject*  objThis, SObject* objTarget, s32 x, s32 y, RECT* rc, bool tlProcessChildren, bool tlProcessSiblings);
	SWindow*				iObj_find_thisForm_window				(SObject*  obj);
	SObject*				iObj_find_thisForm						(SObject*  obj);
	SObject*				iObj_find_thisSubform					(SObject*  obj);
	SObject*				iObj_find_thisRider						(SObject*  obj);
	SObject*				iiObj_findParentObject_byType			(SObject*  objStart, s32 objType,  bool tlSearchSelf);
	SObject*				iiObj_findChildObject_byType			(SObject*  objStart, s32 objType,  bool tlSearchSelf = false, bool tlSearchChildren = true, bool tlSearchSiblings = false);
	SObject*				iiObj_findChildObject_byName			(SObject*  objStart, SDatum* name, bool tlSearchSelf = false, bool tlSearchChildren = true, bool tlSearchSiblings = false);
	bool					iObj_isCommandWindow					(SObject*  obj);
	bool					iObj_isPointWithin						(SObject*  obj, POINT pt, RECT* rc);
	void					iObj_setFocusHighlights					(SWindow*  win, SObject* obj, s32 x, s32 y, bool tlProcessChildren, bool tlProcessSiblings);
	void					iObj_findFocusControls					(SObject*  obj, SBuilder* objFocusControls, bool tlProcessSiblings);
	bool					iObj_setFocusObjectPrev					(SWindow*  win, SObject* obj);
	bool					iObj_setFocusObjectNext					(SWindow*  win, SObject* obj);
	bool					iObj_focus_descentCheck					(SObject*  obj, bool tlCheckChildren, bool tlCheckSiblings);
	SObject*				iObj_focus_descentCheckObj				(SObject*  obj, bool tlCheckChildren, bool tlCheckSiblings);
	void					iObj_setDirtyRender_ascent				(SObject*  obj, bool tlMarkParents, bool tlMarkSubformsDown = false);
	void					iObj_setDirtyRender_descent				(SObject*  obj, bool tlProcessChildren, bool tlProcessSiblings);
	void					iObj_setDirtyPublish_ascent				(SObject*  obj, bool tlMarkParents, bool tlMarkSubformsDown = false);
	void					iObj_setDirtyPublish_descent			(SObject*  obj, bool tlProcessChildren, bool tlProcessSiblings);
	u32						iObj_render								(SObject*  obj, bool tlForceRender);
	bool					iObj_render_descentCheck				(SObject*  obj, bool tlCheckChildren, bool tlCheckSiblings);
	u32						iObj_renderChildrenAndSiblings			(SObject*  obj, bool tlRenderChildren, bool tlRenderSiblings, bool tlForceRender);
	u32						iObj_publish							(SObject*  obj, RECT* rc, SBitmap* bmpDst, bool tlPublishChildren, bool tlPublishSiblings, bool tlForcePublish, s32 tnLevel);
	bool					iObj_publish_descentCheck				(SObject*  obj, bool tlCheckChildren, bool tlCheckSiblings);
	CXml*					iObj_saveLayoutAs_bxml					(SObject* obj, cu8* tcFilename, bool tlFullProperties, bool tlSaveChildren, bool tlSaveSiblings, bool* error, u32* errorNum);
	CXml*					iiObj_saveLayoutAs_bxml_saveObject		(CXml* bxml, SObject* obj, bool tlFullProperties, bool tlSaveChildren, bool tlSaveSiblings);
	void					iObj_duplicateChain						(SObject** root, SObject* chain);
	void					iObj_appendObjToParent					(SObject*  parent, SObject* obj);
	void					iObj_duplicateChildren					(SObject*  objDst, SObject* objSrc);
	void					iObj_setPosition						(SObject*  obj, s32 tnLeft, s32 tnTop);
	void					iObj_setSize							(SObject*  obj, s32 tnLeft, s32 tnTop, s32 tnWidth, s32 tnHeight);
	void					iiObj_setSize_snapForToolbar			(SObject*  obj, s32* tnWidth, s32* tnHeight);
	SWindow* 				iObj_createWindowForForm				(SObject*  form, SWindow* win, s32 icon);
	SBgra					iObj_getColor_ascent					(SObject*  obj, s32 tnColorIndex, bool tlMustBeOpaque, SBgra fallbackColor);
	SVariable*				iObj_getPropertyAsVariable				(SObject*  obj, s8* tcPropertyName, u32 tnPropertyNameLength, SComp* comp, bool tlCreateAsReference);
	void					iiObj_resetToDefault					(SObject*  obj, bool tlResetProperties, bool tlResetMethods);
	void					iiObj_resetToDefaultCommon				(SObject*  obj, bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, s32 tnPropCount, SObjEventMap* eventList, u32 tnEventCount);
	s32						iiObj_getBaseclassType_byName			(s8* tcTextname, s32 tnTextnameLength);
	SBaseClassMap*			iiObj_getBaseclass_byName				(s8* tcTextname, s32 tnTextnameLength);
	SBaseClassMap*			iiObj_getBaseclass_byType				(s32 tnObjType);
	void					iiObj_getRect_inWindow					(SObject* obj, RECT* rc);


//////////
// objects/create.cpp
//////
	// Creation of individual sub-objects
	SObject*				iSubobj_create_markInitializationComplete		(SObject*	obj);
	SObject*				iSubobj_createEmpty						(SObject*	template_empty,			SObject* parent);
	SObject*				iSubobj_createForm						(SObject*	template_form,			SObject* parent);
	SObject*				iSubobj_createSubform					(SObject*	template_subform,		SObject* parent);
	SObject*				iSubobj_createCarousel					(SObject*	template_carousel,		SObject* parent);
	SObject*				iSubobj_createRider						(SObject*	template_rider,			SObject* parent);
	SObject*				iSubobj_createLabel						(SObject*	template_label,			SObject* parent);
	SObject*				iSubobj_createTextbox					(SObject*	template_textbox,		SObject* parent);
	SObject*				iSubobj_createButton					(SObject*	template_button,		SObject* parent);
	SObject*				iSubobj_createEditbox					(SObject*	template_editbox,		SObject* parent);
	SObject*				iSubobj_createImage						(SObject*	template_image,			SObject* parent);
	SObject*				iSubobj_createCheckbox					(SObject*	template_checkbox,		SObject* parent);
	SObject*				iSubobj_createOption					(SObject*	template_option,		SObject* parent);
	SObject*				iSubobj_createRadio						(SObject*	template_radio,			SObject* parent);
	SObject*				iSubobj_createCmdGroup					(SObject*	template_CmdGroup,		SObject* parent);
	SObject*				iSubobj_createOptGroup					(SObject*	template_OptGroup,		SObject* parent);
	SObject*				iSubobj_createListbox					(SObject*	template_Listbox,		SObject* parent);
	SObject*				iSubobj_createCombobox					(SObject*	template_Combobox,		SObject* parent);
	SObject*				iSubobj_createFormset					(SObject*	template_Formset,		SObject* parent);
	SObject*				iSubobj_createToolbar					(SObject*	template_Toolbar,		SObject* parent);
	SObject*				iSubobj_createSeparator					(SObject*	template_Separator,		SObject* parent);
	SObject*				iSubobj_createLine						(SObject*	template_Line,			SObject* parent);
	SObject*				iSubobj_createShape						(SObject*	template_Shape,			SObject* parent);
	SObject*				iSubobj_createContainer					(SObject*	template_Container,		SObject* parent);
	SObject*				iSubobj_createControl					(SObject*	template_Control,		SObject* parent);
	SObject*				iSubobj_createGrid						(SObject*	template_Grid,			SObject* parent);
	SObject*				iSubobj_createColumn					(SObject*	template_Column,		SObject* parent);
	SObject*				iSubobj_createHeader					(SObject*	template_Header,		SObject* parent);
	SObject*				iSubobj_createOleBound					(SObject*	template_OleBound,		SObject* parent);
	SObject*				iSubobj_createOleContain				(SObject*	template_OleContain,	SObject* parent);
	SObject*				iSubobj_createSpinner					(SObject*	template_Spinner,		SObject* parent);
	SObject*				iSubobj_createTimer						(SObject*	template_Timer,			SObject* parent);
	SObject*				iSubobj_createHyperlink					(SObject*	template_Hyperlink,		SObject* parent);
	SObject*				iSubobj_createCollection				(SObject*	template_Collection,	SObject* parent);
	SObject*				iSubobj_createPage						(SObject*	template_Page,			SObject* parent);
	SObject*				iSubobj_createPageFrame					(SObject*	template_Pageframe,		SObject* parent);
	SObject*				iSubobj_createSession					(SObject*	template_Session,		SObject* parent);
	SObject*				iSubobj_createCustom					(SObject*	template_Custom,		SObject* parent);
	SObject*				iSubobj_createException					(SObject*	template_Exception,		SObject* parent);
	SObject*				iSubobj_createSettings					(SObject*	template_Settings,		SObject* parent);
	SObject*				iSubobj_createControlPoint				(SObject*	template_ControlPoint,	SObject* parent);


//////////
// objects/copy.cpp
//////
	// For copy operations
	void					iiSubobj_copyEmpty						(SObject*	emptyDst,		SObject*	emptySrc);
	void					iiSubobj_copyForm						(SObject*	formDst,		SObject*	formSrc);
	void					iiSubobj_copySubform					(SObject*	subformDst,		SObject*	subformSrc);
	void					iiSubobj_copyCarousel					(SObject*	carouselDst,	SObject*	carouselSrc);
	void					iiSubobj_copyRider						(SObject*	riderDst,		SObject*	riderSrc);
	void					iiSubobj_copyLabel						(SObject*	labelDst,		SObject*	labelSrc);
	void					iiSubobj_copyTextbox					(SObject*	textboxDst,		SObject*	textboxSrc);
	void					iiSubobj_copyButton						(SObject*	buttonDst,		SObject*	buttonSrc);
	void					iiSubobj_copyEditbox					(SObject*	editboxDst,		SObject*	editboxSrc);
	void					iiSubobj_copyImage						(SObject*	imageDst,		SObject*	imageSrc);
	void					iiSubobj_copyCheckbox					(SObject*	checkboxDst,	SObject*	checkboxSrc);
	void					iiSubobj_copyOption						(SObject*	optionDst,		SObject*	optionSrc);
	void					iiSubobj_copyRadio						(SObject*	radioDst,		SObject*	radioSrc);
	void					iiSubobj_copyCmdGroup					(SObject*	cmdGroupDst,	SObject*	cmdGroupSrc);
	void					iiSubobj_copyOptGroup					(SObject*	optGroupDst,	SObject*	optGroupSrc);
	void					iiSubobj_copyListbox					(SObject*	listboxDst,		SObject*	listboxSrc);
	void					iiSubobj_copyCombobox					(SObject*	comboboxDst,	SObject*	comboboxSrc);
	void					iiSubobj_copyFormset					(SObject*	formsetDst,		SObject*	formsetSrc);
	void					iiSubobj_copyToolbar					(SObject*	toolbarDst,		SObject*	toolbarSrc);
	void					iiSubobj_copySeparator					(SObject*	separatorDst,	SObject*	separatorSrc);
	void					iiSubobj_copyLine						(SObject*	lineDst,		SObject*	lineSrc);
	void					iiSubobj_copyShape						(SObject*	shapeDst,		SObject*	shapeSrc);
	void					iiSubobj_copyContainer					(SObject*	containerDst,	SObject*	containerSrc);
	void					iiSubobj_copyControl					(SObject*	controlDst,		SObject*	controlSrc);
	void					iiSubobj_copyGrid						(SObject*	gridDst,		SObject*	gridSrc);
	void					iiSubobj_copyColumn						(SObject*	columnDst,		SObject*	columnSrc);
	void					iiSubobj_copyHeader						(SObject*	headerDst,		SObject*	headerSrc);
	void					iiSubobj_copyOleBound					(SObject*	oleBoundDst,	SObject*	oleBoundSrc);
	void					iiSubobj_copyOleContain					(SObject*	oleContainDst,	SObject*	oleContainSrc);
	void					iiSubobj_copySpinner					(SObject*	spinnerDst,		SObject*	spinnerSrc);
	void					iiSubobj_copyTimer						(SObject*	timerDst,		SObject*	timerSrc);
	void					iiSubobj_copyHyperlink					(SObject*	hyperlinkDst,	SObject*	hyperlinkSrc);
	void					iiSubobj_copyCollection					(SObject*	collectionDst,	SObject*	collectionSrc);
	void					iiSubobj_copyPage						(SObject*	pageDst,		SObject*	pageSrc);
	void					iiSubobj_copyPageframe					(SObject*	pageframeDst,	SObject*	pageframeSrc);
	void					iiSubobj_copySession					(SObject*	sessionDst,		SObject*	sessionSrc);
	void					iiSubobj_copyCustom						(SObject*	customDst,		SObject*	customSrc);
	void					iiSubobj_copyException					(SObject*	exceptionDst,	SObject*	exceptionSrc);


//////////
// objects/reset.cpp
//////
	// For initialization
	void					iiSubobj_resetToDefaultEmpty			(SObject*	empty,		bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount, SObjEventMap* eventList, u32 tnEventCount);
	void					iiSubobj_resetToDefaultForm				(SObject*	form,		bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount, SObjEventMap* eventList, u32 tnEventCount);
	void					iiSubobj_resetToDefaultSubform			(SObject*	subform,	bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount, SObjEventMap* eventList, u32 tnEventCount);
	void					iiSubobj_resetToDefaultCarousel			(SObject*	carousel,	bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount, SObjEventMap* eventList, u32 tnEventCount);
	void					iiSubobj_resetToDefaultRider			(SObject*	rider,		bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount, SObjEventMap* eventList, u32 tnEventCount);
	void					iiSubobj_resetToDefaultLabel			(SObject*	label,		bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount, SObjEventMap* eventList, u32 tnEventCount);
	void					iiSubobj_resetToDefaultTextbox			(SObject*	textbox,	bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount, SObjEventMap* eventList, u32 tnEventCount);
	void					iiSubobj_resetToDefaultButton			(SObject*	button,		bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount, SObjEventMap* eventList, u32 tnEventCount);
	void					iiSubobj_resetToDefaultEditbox			(SObject*	editbox,	bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount, SObjEventMap* eventList, u32 tnEventCount);
	void					iiSubobj_resetToDefaultImage			(SObject*	image,		bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount, SObjEventMap* eventList, u32 tnEventCount);
	void					iiSubobj_resetToDefaultCheckbox			(SObject*	checkbox,	bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount, SObjEventMap* eventList, u32 tnEventCount);
	void					iiSubobj_resetToDefaultOption			(SObject*	option,		bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount, SObjEventMap* eventList, u32 tnEventCount);
	void					iiSubobj_resetToDefaultRadio			(SObject*	radio,		bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount, SObjEventMap* eventList, u32 tnEventCount);
	void					iiSubobj_resetToDefaultCmdGroup			(SObject*	cmdGroup,	bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount, SObjEventMap* eventList, u32 tnEventCount);
	void					iiSubobj_resetToDefaultOptGroup			(SObject*	optGroup,	bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount, SObjEventMap* eventList, u32 tnEventCount);
	void					iiSubobj_resetToDefaultListbox			(SObject*	listbox,	bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount, SObjEventMap* eventList, u32 tnEventCount);
	void					iiSubobj_resetToDefaultCombobox			(SObject*	combobox,	bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount, SObjEventMap* eventList, u32 tnEventCount);
	void					iiSubobj_resetToDefaultFormset			(SObject*	formset,	bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount, SObjEventMap* eventList, u32 tnEventCount);
	void					iiSubobj_resetToDefaultToolbar			(SObject*	toolbar,	bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount, SObjEventMap* eventList, u32 tnEventCount);
	void					iiSubobj_resetToDefaultSeparator		(SObject*	separator,	bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount, SObjEventMap* eventList, u32 tnEventCount);
	void					iiSubobj_resetToDefaultLine				(SObject*	line,		bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount, SObjEventMap* eventList, u32 tnEventCount);
	void					iiSubobj_resetToDefaultShape			(SObject*	shape,		bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount, SObjEventMap* eventList, u32 tnEventCount);
	void					iiSubobj_resetToDefaultContainer		(SObject*	container,	bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount, SObjEventMap* eventList, u32 tnEventCount);
	void					iiSubobj_resetToDefaultControl			(SObject*	control,	bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount, SObjEventMap* eventList, u32 tnEventCount);
	void					iiSubobj_resetToDefaultGrid				(SObject*	grid,		bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount, SObjEventMap* eventList, u32 tnEventCount);
	void					iiSubobj_resetToDefaultColumn			(SObject*	column,		bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount, SObjEventMap* eventList, u32 tnEventCount);
	void					iiSubobj_resetToDefaultHeader			(SObject*	header,		bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount, SObjEventMap* eventList, u32 tnEventCount);
	void					iiSubobj_resetToDefaultOleBound			(SObject*	oleBound,	bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount, SObjEventMap* eventList, u32 tnEventCount);
	void					iiSubobj_resetToDefaultOleContain		(SObject*	oleContain,	bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount, SObjEventMap* eventList, u32 tnEventCount);
	void					iiSubobj_resetToDefaultSpinner			(SObject*	spinner,	bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount, SObjEventMap* eventList, u32 tnEventCount);
	void					iiSubobj_resetToDefaultTimer			(SObject*	timer,		bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount, SObjEventMap* eventList, u32 tnEventCount);
	void					iiSubobj_resetToDefaultHyperlink		(SObject*	hyperlink,	bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount, SObjEventMap* eventList, u32 tnEventCount);
	void					iiSubobj_resetToDefaultCollection		(SObject*	collection,	bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount, SObjEventMap* eventList, u32 tnEventCount);
	void					iiSubobj_resetToDefaultPage				(SObject*	page,		bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount, SObjEventMap* eventList, u32 tnEventCount);
	void					iiSubobj_resetToDefaultPageframe		(SObject*	pageframe,	bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount, SObjEventMap* eventList, u32 tnEventCount);
	void					iiSubobj_resetToDefaultSession			(SObject*	session,	bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount, SObjEventMap* eventList, u32 tnEventCount);
	void					iiSubobj_resetToDefaultCustom			(SObject*	custom,		bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount, SObjEventMap* eventList, u32 tnEventCount);
	void					iiSubobj_resetToDefaultException		(SObject*	exception,	bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount, SObjEventMap* eventList, u32 tnEventCount);
	void					iiSubobj_resetToDefaultSettings			(SObject*	exception,	bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount, SObjEventMap* eventList, u32 tnEventCount);
	void					iiSubobj_resetToDefaultControlPoint		(SObject*	exception,	bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount, SObjEventMap* eventList, u32 tnEventCount);


//////////
// objects/delete.cpp
//////
	// Delete individual sub-objects
	void					iObj_deleteCommon						(SObject*	obj);
	void					iSubobj_deleteEmpty						(SObject*	empty,		bool tlDeleteSelf);
	void					iSubobj_deleteForm						(SObject*	form,		bool tlDeleteSelf);
	void					iSubobj_deleteSubform					(SObject*	subform,	bool tlDeleteSelf);
	void					iSubobj_deleteCarousel					(SObject*	carousel,	bool tlDeleteSelf, bool tlLeaveRiders, bool tlLeaveObjects);
	void					iSubobj_deleteRider						(SObject*	rider,		bool tlDeleteSelf, bool tlLeaveObjects);
	void					iSubobj_deleteLabel						(SObject*	label,		bool tlDeleteSelf);
	void					iSubobj_deleteTextbox					(SObject*	textbox,	bool tlDeleteSelf);
	void					iSubobj_deleteButton					(SObject*	button,		bool tlDeleteSelf);
	void					iSubobj_deleteEditbox					(SObject*	editbox,	bool tlDeleteSelf);
	void					iSubobj_deleteImage						(SObject*	image,		bool tlDeleteSelf);
	void					iSubobj_deleteCheckbox					(SObject*	checkbox,	bool tlDeleteSelf);
	void					iSubobj_deleteOption					(SObject*	option,		bool tlDeleteSelf);
	void					iSubobj_deleteRadio						(SObject*	radio,		bool tlDeleteSelf);
	void					iSubobj_deleteCmdGroup					(SObject*	cmdGroup,	bool tlDeleteSelf);
	void					iSubobj_deleteOptGroup					(SObject*	optGroup,	bool tlDeleteSelf);
	void					iSubobj_deleteListbox					(SObject*	listbox,	bool tlDeleteSelf);
	void					iSubobj_deleteCombobox					(SObject*	combobox,	bool tlDeleteSelf);
	void					iSubobj_deleteFormset					(SObject*	formset,	bool tlDeleteSelf);
	void					iSubobj_deleteToolbar					(SObject*	toolbar,	bool tlDeleteSelf);
	void					iSubobj_deleteSeparator					(SObject*	separator,	bool tlDeleteSelf);
	void					iSubobj_deleteLine						(SObject*	line,		bool tlDeleteSelf);
	void					iSubobj_deleteShape						(SObject*	shape,		bool tlDeleteSelf);
	void					iSubobj_deleteContainer					(SObject*	container,	bool tlDeleteSelf);
	void					iSubobj_deleteControl					(SObject*	control,	bool tlDeleteSelf);
	void					iSubobj_deleteGrid						(SObject*	grid,		bool tlDeleteSelf);
	void					iSubobj_deleteColumn					(SObject*	column,		bool tlDeleteSelf);
	void					iSubobj_deleteHeader					(SObject*	header,		bool tlDeleteSelf);
	void					iSubobj_deleteOleBound					(SObject*	oleBound,	bool tlDeleteSelf);
	void					iSubobj_deleteOleContain				(SObject*	oleContain,	bool tlDeleteSelf);
	void					iSubobj_deleteSpinner					(SObject*	spinner,	bool tlDeleteSelf);
	void					iSubobj_deleteTimer						(SObject*	timer,		bool tlDeleteSelf);
	void					iSubobj_deleteHyperlink					(SObject*	hyperlink,	bool tlDeleteSelf);
	void					iSubobj_deleteCollection				(SObject*	collection,	bool tlDeleteSelf);
	void					iSubobj_deletePage						(SObject*	page,		bool tlDeleteSelf);
	void					iSubobj_deletePageFrame					(SObject*	pageFrame,	bool tlDeleteSelf);
	void					iSubobj_deleteSession					(SObject*	session,	bool tlDeleteSelf);
	void					iSubobj_deleteCustom					(SObject*	custom,		bool tlDeleteSelf);
	void					iSubobj_deleteException					(SObject*	exception,	bool tlDeleteSelf);
	void					iSubobj_deleteSettings					(SObject*	settings,	bool tlDeleteSelf);
	void					iSubobj_deleteControlPoint				(SObject*	controlpoint, bool tlDeleteSelf);


//////////
// objects/render.cpp
//////
	// Default render of sub-objects
	u32						iSubobj_renderEmpty						(SObject* empty);
	u32						iSubobj_renderForm						(SObject* form);
	u32						iSubobj_renderSubform					(SObject* subform);
	u32						iSubobj_renderCarousel					(SObject* carousel);
	u32						iSubobj_renderRider						(SObject* rider);
	u32						iSubobj_renderLabel						(SObject* label);
	u32						iSubobj_renderTextbox					(SObject* textbox);
	u32						iSubobj_renderButton					(SObject* button);
	u32						iSubobj_renderEditbox					(SObject* editbox);
	u32						iSubobj_renderImage						(SObject* image);
	u32						iSubobj_renderCheckbox					(SObject* checkbox);
	u32						iSubobj_renderOption					(SObject* option);
	u32						iSubobj_renderRadio						(SObject* radio);
	u32						iSubobj_renderCmdGroup					(SObject* cmdGroup);
	u32						iSubobj_renderOptGroup					(SObject* optGroup);
	u32						iSubobj_renderListbox					(SObject* listbox);
	u32						iSubobj_renderCombobox					(SObject* combobox);
	u32						iSubobj_renderFormset					(SObject* formset);
	u32						iSubobj_renderToolbar					(SObject* toolbar);
	u32						iSubobj_renderSeparator					(SObject* separator);
	u32						iSubobj_renderLine						(SObject* line);
	u32						iSubobj_renderShape						(SObject* shape);
	u32						iSubobj_renderContainer					(SObject* container);
	u32						iSubobj_renderControl					(SObject* control);
	u32						iSubobj_renderGrid						(SObject* grid);
	u32						iSubobj_renderColumn					(SObject* column);
	u32						iSubobj_renderHeader					(SObject* header);
	u32						iSubobj_renderOleBound					(SObject* oleBound);
	u32						iSubobj_renderOleContain				(SObject* oleContain);
	u32						iSubobj_renderSpinner					(SObject* spinner);
	u32						iSubobj_renderTimer						(SObject* timer);
	u32						iSubobj_renderHyperlink					(SObject* hyperlink);
	u32						iSubobj_renderCollection				(SObject* collection);
	u32						iSubobj_renderPage						(SObject* page);
	u32						iSubobj_renderPageFrame					(SObject* pageFrame);
	u32						iSubobj_renderSession					(SObject* session);
	u32						iSubobj_renderCustom					(SObject* custom);
	u32						iSubobj_renderException					(SObject* exception);
	u32						iSubobj_renderSettings					(SObject* settings);
	u32						iSubobj_renderControlPoint				(SObject* controlPoint);


//////////
// objects/callbacks.cpp
//////
	bool					iDefaultCallback_resize					(SWindow* win, SObject* obj, RECT* rc);
	bool					iDefaultCallback_onLoad					(SWindow* win, SObject* obj);
	bool					iDefaultCallback_onInit					(SWindow* win, SObject* obj);
	bool					iDefaultCallback_onCreated				(SWindow* win, SObject* obj);
	bool					iDefaultCallback_onResize				(SWindow* win, SObject* obj, SVariable* widthRequired_out, SVariable* heightRequired_out);
	bool					iDefaultCallback_onRender				(SWindow* win, SObject* obj);
	bool					iDefaultCallback_onPublish				(SWindow* win, SObject* obj);
	bool					iDefaultCallback_onDestroy				(SWindow* win, SObject* obj);
	bool					iDefaultCallback_onUnload				(SWindow* win, SObject* obj);
	bool					iDefaultCallback_onGotFocus				(SWindow* win, SObject* obj);
	bool					iDefaultCallback_onLostFocus			(SWindow* win, SObject* obj);
	bool					iiDefaultCallback_processMouseVariables	(							  SVariable* varX, SVariable* varY, SVariable* varCtrl, SVariable* varAlt, SVariable* varShift, SVariable* varClick, s32* lnX, s32* lnY, bool* tlCtrl, bool* tlAlt, bool* tlShift, u32* lnClick);
	bool					iDefaultCallback_onMouseClickEx			(SWindow* win, SObject* obj, SVariable* varX, SVariable* varY, SVariable* varCtrl, SVariable* varAlt, SVariable* varShift, SVariable* varClick);
	bool					iDefaultCallback_onMouseDblClickEx		(SWindow* win, SObject* obj, SVariable* varX, SVariable* varY, SVariable* varCtrl, SVariable* varAlt, SVariable* varShift, SVariable* varClick);
	bool					iDefaultCallback_onMouseWheel			(SWindow* win, SObject* obj, SVariable* varX, SVariable* varY, SVariable* varCtrl, SVariable* varAlt, SVariable* varShift, SVariable* varClick, SVariable* varUnits);
	bool					iDefaultCallback_onMouseMove			(SWindow* win, SObject* obj, SVariable* varX, SVariable* varY, SVariable* varCtrl, SVariable* varAlt, SVariable* varShift, SVariable* varClick);
	bool					iDefaultCallback_onMouseDown			(SWindow* win, SObject* obj, SVariable* varX, SVariable* varY, SVariable* varCtrl, SVariable* varAlt, SVariable* varShift, SVariable* varClick);
	bool					iDefaultCallback_onMouseUp				(SWindow* win, SObject* obj, SVariable* varX, SVariable* varY, SVariable* varCtrl, SVariable* varAlt, SVariable* varShift, SVariable* varClick);
	bool					iDefaultCallback_onMouseEnter			(SWindow* win, SObject* obj);
	bool					iDefaultCallback_onMouseLeave			(SWindow* win, SObject* obj);
	bool					iDefaultCallback_onMouseHover			(SWindow* win, SObject* obj, SVariable* varX, SVariable* varY, SVariable* varCtrl, SVariable* varAlt, SVariable* varShift, SVariable* varClick);
	bool					iiDefaultCallback_processKeyVariables	(							 SVariable* varCtrl, SVariable* varAlt, SVariable* varShift, SVariable* varCaps, SVariable* varAscii, SVariable* varVKey, SVariable* varIsCAS, SVariable* varIsAscii, bool* tlCtrl, bool* tlAlt, bool* tlShift, bool* tlCaps, bool* tlIsCAS, bool* tlIsAscii, s16* lcAscii, u16* lnVKey);
	bool					iDefaultCallback_onKeyDown				(SWindow* win, SObject* obj, SVariable* varCtrl, SVariable* varAlt, SVariable* varShift, SVariable* varCaps, SVariable* varAscii, SVariable* varVKey, SVariable* varIsCAS, SVariable* varIsAscii);
	bool					iDefaultCallback_onKeyUp				(SWindow* win, SObject* obj, SVariable* varCtrl, SVariable* varAlt, SVariable* varShift, SVariable* varCaps, SVariable* varAscii, SVariable* varVKey, SVariable* varIsCAS, SVariable* varIsAscii);
	bool					iDefaultCallback_onActivate				(SWindow* win, SObject* obj);
	bool					iDefaultCallback_onDeactivate			(SWindow* win, SObject* obj);
	bool					iDefaultCallback_onInteractiveChange	(SWindow* win, SObject* obj);
	bool					iDefaultCallback_onProgrammaticChange	(SWindow* win, SObject* obj);
	bool					iDefaultCallback_onSelect				(SWindow* win, SObject* obj);
	bool					iDefaultCallback_onDeselect				(SWindow* win, SObject* obj);
	bool					iDefaultCallback_onMoved				(SWindow* win, SObject* obj, SVariable* xOverride_out, SVariable* yOverride_out);
	bool					iDefaultCallback_onQueryUnload			(SWindow* win, SObject* obj);
	bool					iDefaultCallback_onAddObject			(SWindow* win, SObject* obj);
	bool					iDefaultCallback_onAddProperty			(SWindow* win, SObject* obj);
	bool					iDefaultCallback_onError				(SWindow* win, SObject* obj);
	bool					iDefaultCallback_onScrolled				(SWindow* win, SObject* obj);
	bool					iDefaultCallback_onSetActiveControl		(SWindow* win, SObject* obj, SVariable* toActive);
	bool					iDefaultCallback_onSpin					(SWindow* win, SObject* obj, SVariable* tnDelta, SVariable* tnDirection, SVariable* tnType);

	// Carousel tab-specific
	bool					iDefaultCallback_onTabClose				(SWindow* win, SObject* obj);
	bool					iDefaultCallback_onTabClick				(SWindow* win, SObject* obj, bool tlOnClose);
	bool					iDefaultCallback_onTabMouseWheel		(SWindow* win, SObject* obj, sptr tnClicks);
	bool					iDefaultCallback_onTabMouseMove			(SWindow* win, SObject* obj, bool tlOnClose);
	bool					iDefaultCallback_onTabMouseDown			(SWindow* win, SObject* obj, bool tlOnClose);
	bool					iDefaultCallback_onTabMouseUp			(SWindow* win, SObject* obj, bool tlOnClose);
	bool					iDefaultCallback_onTabMouseEnter		(SWindow* win, SObject* obj, bool tlOnClose);
	bool					iDefaultCallback_onTabMouseLeave		(SWindow* win, SObject* obj, bool tlOnClose);

	// Carousel / rider control point specific
	bool					iDefaultCallback_onControlPointEnter	(SWindow* win, SObject* obj);
	bool					iDefaultCallback_onControlPointLeave	(SWindow* win, SObject* obj);
	bool					iDefaultCallback_onControlPointDrop		(SWindow* win, SObject* obj);


//////////
// objects/events.cpp
//////
	void					iEvents_resetToDefault					(SObject* obj, SObjEventMap* oemap, s32 tnOemapCount);
	// Helper functions to translate strongly typed values to weakly typed variables
	bool					iiEventDispatch_onMouseMove				(SWindow* win, SObject* obj, s32 x, s32 y, bool tlCtrl, bool tlAlt, bool tlShift, u32 tnClicks);
	bool					iiEventDispatch_onMouseDown				(SWindow* win, SObject* obj, s32 x, s32 y, bool tlCtrl, bool tlAlt, bool tlShift, u32 tnClicks);
	bool					iiEventDispatch_onMouseClickEx			(SWindow* win, SObject* obj, s32 x, s32 y, bool tlCtrl, bool tlAlt, bool tlShift, u32 tnClicks);
	bool					iiEventDispatch_onMouseUp				(SWindow* win, SObject* obj, s32 x, s32 y, bool tlCtrl, bool tlAlt, bool tlShift, u32 tnClicks);
	bool					iiEventDispatch_onMouseWheel			(SWindow* win, SObject* obj, s32 x, s32 y, bool tlCtrl, bool tlAlt, bool tlShift, u32 tnClicks, s32 tnDeltaY);
	bool					iiEventDispatch_onKeyDown				(SWindow* win, SObject* obj, bool tlCtrl, bool tlAlt, bool tlShift, bool tlCaps, u16 tnAsciiChar, u16 tvKey, bool tlIsCAS, bool tlIsAscii);
	bool					iiEventDispatch_onKeyUp					(SWindow* win, SObject* obj, bool tlCtrl, bool tlAlt, bool tlShift, bool tlCaps, u16 tnAsciiChar, u16 tvKey, bool tlIsCAS, bool tlIsAscii);

	// Carousel
	bool					iEvents_carouselMouseWheel				(SWindow* win, SObject* obj, s32 lnX, s32 lnY, bool llCtrl, bool llAlt, bool llShift, u32 lnClick);
	bool					iEvents_carouselMouseMove				(SWindow* win, SObject* obj, s32 lnX, s32 lnY, bool llCtrl, bool llAlt, bool llShift, u32 lnClick);
	bool					iEvents_carouselMouseDown				(SWindow* win, SObject* obj, s32 lnX, s32 lnY, bool llCtrl, bool llAlt, bool llShift, u32 lnClick);
	bool					iEvents_carouselMouseUp					(SWindow* win, SObject* obj, s32 lnX, s32 lnY, bool llCtrl, bool llAlt, bool llShift, u32 lnClick);
	bool					iEvents_carousel_dragStart_tab			(SWindow* win, SObject* obj, SBitmap* bmp);
	bool					iEvents_carousel_dragStart_titlebar		(SWindow* win, SObject* obj, SBitmap* bmp);
	u32						iiEvents_carousel_findTarget			(SWindow* win, SObject* obj, s32 tnX, s32 tnY, SObjCarouselTabData** toctd, bool* tlHighlightChanged);


//////////
// objects/rider.cpp
//////
	void					iRider_trackMotion_mouseDown			(SObject* obj, s32 lnX, s32 lnY);


//////////
// Toolbar related
//////
	SObject*				iToolbar_loadFrom_xml					(                                                  cu8* tcXml, u32 tnXmlLength, cs8* tcTagRoot, cs8* tcTagSub);
	bool					iToolbar_applyTo_obj					(SObject* objParent, SObject* objToolbarContainer, cu8* tcXml, u32 tnXmlLength, cs8* tcTagRoot, cs8* tcTagSub);


//////////
// DLL-related functions
//////
	// Dll functions
	void					iDllFunc_dispatch						(SReturnsParams* rpar, SDllFunc* dfunc, SComp* compDllName);
	void					iiDllFunc_dispatch_lowLevel				(SReturnsParams* rpar, SDllFunc* dfunc);
	bool					iDllFunc_add							(SReturnsParams* rpar, SDllFuncParam* rp, SDllFuncParam ip[], s32 tnIpCount, SComp* compFunctionName, SComp* compAliasName, SComp* compDllName, SThisCode* onAccess, SThisCode* onAssign, bool tlNoPrototype, bool tlVariadic);
	SDllFunc*				iDllFunc_find_byName					(s8* funcName, s32 lnFuncNameLength);

	// Dll library (the physical c:\path\to\theFile.dll
	SDllLib*				iDllLib_open							(SComp* compDllName);


//////////
// vjr_init.cpp
//////
	void					iVjr_init_minimal						(void);
	void					iVjr_init								(HACCEL* hAccelTable = NULL, bool tlInitializeSound = true);
	void					iVjr_init_loadCaskIcons					(void);
	void					iVjr_init_loadBitmapArray				(void);
	void					iVjr_init_createMessageWindow			(void);
	bool					iVjr_isValid_window						(uptr tnWindow);
	void					iVjr_init_createConstants				(void);
	void					iVjr_init_createGlobalSystemVariables	(void);
	void					iiVjr_init_createGlobalSystemVariable	(SVariable** var, s32 tnType, cu8* tcName, cs8* tcInitValue = NULL, u32 tnInitValueLength = 0);
	void					iVjr_init_createDefaultObjects			(void);
	void					iVjr_init_jdebi_create					(void);
	void					iVjr_init_jdebi_addToolbars				(void);
	void					iVjr_init_createDefaultDatetimes		(void);


//////////
// vjr_sup.cpp
//////
	SBitmap*				iiVjr_buildSplashScreen					(SBitmap* bmpSplash);
	void					iVjr_appendSystemLog					(u8* tcLogText);
	void					iVjr_flushSystemLog						(void);
	void					iVjr_releaseMemory						(void);
	void					iVjr_releaseAllDefaultDatetimes			(void);
	void					iVjr_releaseAllDefaultObjects			(void);
	void					iVjr_release_jdebi						(void);
	void					iVjr_releaseCaskIcons					(void);
	void					iVjr_shutdown							(void);

	void					iiVjr_device_start						(SVjrDevice* device, bool* error = NULL, u32* errorNum = NULL);
	void					iiVjr_device_output_row					(SVjrDevice* device, SDatum* data, bool tlDeleteData, bool* error = NULL, u32* errorNum = NULL);
	void					iiVjr_device_end						(SVjrDevice* device, bool* error = NULL, u32* errorNum = NULL);

	void					iiVjr_settings_device_allocate			(SVjrDevice* device);
	bool					iiVjr_settings_device_allocate_fromComp	(SVjrDevice* device, SComp* compTo, bool* error = NULL, u32* errorNum = NULL);


	DWORD	WINAPI			iSplash_show							(LPVOID/*SBitmap* bmp*/ lpParameter);
	DWORD	WINAPI			iSplash_delete							(LPVOID/*bool tlWait*/ lpParameter);
	void	CALLBACK		iSplash_timerProc						(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);
	LRESULT CALLBACK		iSplash_wndProc							(HWND hwnd, UINT m, WPARAM w, LPARAM l);

	DWORD	WINAPI			iPlay_ariaSplash						(LPVOID lpParameter);
	void WINAPI				iPlay_ariaSplash_callback				(f32* sampleBuffer, u32 tnSamples, bool* tlContinueAfterThisSampleSet);

	DWORD	WINAPI			iReadEvents_messageWindow				(LPVOID lpParameter);
	LRESULT	CALLBACK		iWindow_wndProcMessage					(HWND hwnd, UINT m, WPARAM w, LPARAM l);
	LRESULT	CALLBACK		iWindow_wndProcForms					(HWND hwnd, UINT m, WPARAM w, LPARAM l);
	SWindow* 				iWindow_createForObject					(SObject* obj, SWindow* winReuse, s32 icon);
	void					iWindow_releaseAll						(SBuilder** windowRoot, bool tlDeleteSelf);
	void					iWindow_delete							(SWindow* win, bool tlDeleteSelf);
	SWindow*				iWindow_findByHwnd						(HWND hwnd);
	SWindow*				iWindow_findByObj						(SObject* obj);
	SWindow*				iWindow_findRoot_byObj					(SObject* obj);
	SWindow*				iWindow_allocate						(void);
	void					iWindow_disconnectObj					(SWindow* win, SObject* obj);
	void					iWindow_render							(SWindow* win, bool tlForceRedraw);
	void					iWindow_move							(SWindow* win);
	void					iWindow_minimize						(SWindow* win);
	void					iWindow_maximize						(SWindow* win);
	bool					iWindow_isPointerValid					(SWindow* win);

	void					iFocusHighlight_create					(SFocusHighlight* focus, RECT* rc);
	void					iFocusHighlight_show					(SFocusHighlight* focus);
	void					iFocusHighlight_delete					(SFocusHighlight* focus);
	void					iFocusHighlight_deleteAll				(void);
	SFocusHighlight*		iFocusHighlight_findByHwnd				(HWND hwnd);
	SFocusHighlight*		iFocusHighlight_findByObj				(SObject* obj);
	LRESULT CALLBACK		iFocusHighlight_wndProc					(HWND hwnd, UINT m, WPARAM w, LPARAM l);

	STooltip*				iTooltip_allocate						(RECT* rc, SBitmap* bmp, s32 tnTimeoutMs, bool tlAllowMove, bool tlAllowSticky);
	void					iTooltip_show							(STooltip* tooltip);
	DWORD WINAPI			iTooltip_thread							(LPVOID lpParameter/*STooltip*/);
	void					iTooltip_delete							(STooltip* tooltip);
	LRESULT CALLBACK		iTooltip_wndProc						(HWND hwnd, UINT m, WPARAM w, LPARAM l);

	bool					iFile_readContents						(s8* tcFilename, FILE** tfh, s8** data, u32* dataLength);
	bool					iFile_get_justfname						(s8* tcPathname, s32 tnFilenameLength, s8** tcFname, s32* tnFnameLength);
	s32						iFile_parseIntoLines					(SLine** firstLine, s8* data, u32 dataLength);

	void					iMisc_adjustColorBrightness				(SBgra& color, f32 tfPercent);
	bool					iInit_shutdownPolitely					(void);

	s8						iLowerCase								(s8 c);
	s8						iUpperCase								(s8 c);
	bool					iAreHexDigits							(u8* ptr, s32 tnLength);
	void					iiHexValue_getAs_u8						(u8* ptr, s32 tnDigits, u8* dst, bool tlDoubleIfOne = false);

	bool					iTestExactlyEqual						(u8* left, u32 leftLength, cu8* right, u32 rightLength);
	bool					iTestExactlyEqual						(u8* left, u32 leftLength,  u8* right, u32 rightLength);
	bool					iTestExactlyEqual_case					(u8* left, u32 leftLength, cu8* right, u32 rightLength);
	bool					iTestExactlyEqual_case					(u8* left, u32 leftLength,  u8* right, u32 rightLength);
	bool					iIsNeedleInHaystack						(s8* haystack, s32 haystackLength, s8* needle, s32 needleLength);
	bool					iIsNeedleInHaystackCase					(s8* haystack, s32 haystackLength, s8* needle, s32 needleLength);
	bool					iIsNeedleInHaystack						(s8* haystack, s32 haystackLength, s8* needle, s32 needleLength, u32* tnStart);
	bool					iIsNeedleInHaystackCase					(s8* haystack, s32 haystackLength, s8* needle, s32 needleLength, u32* tnStart);
	bool					iIsCharacterInHaystack					(s8* haystack, s32 haystackLength, s8 needle, u32* tnOffset);
	bool					iIsCharacterInHaystackCase				(s8* haystack, s32 haystackLength, s8 needle, u32* tnOffset);
	bool					iIsCharacterInHaystackReversed			(s8* haystack, s32 haystackLength, s8 needle, u32* tnOffset);
	bool					iIsCharacterInHaystackReversedCase		(s8* haystack, s32 haystackLength, s8 needle, u32* tnOffset);
	bool					iIsBoolText								(SDatum* d, bool* tlStoreValue, bool tlAllowLogicalX);
	bool					iIsNotNull								(void* p);
	void*					iif										(bool tlTest, void* ifTrue, void* ifFalse);
	s32						iif										(bool tlTest, s32 ifTrue, s32 ifFalse);
	bool					iDoesHaystackStartWithNeedle			(s8* haystack, s32 haystackLength, s8* needle, s32 needleLength);
	bool					iDoesHaystackStartWithNeedleCase		(s8* haystack, s32 haystackLength, s8* needle, s32 needleLength);
	s8						iLowerCharacter							(s8 ch);
	u32						iSkip_whitespaces						(s8* source, u32* offset, u32 maxLength);
	u32						iiCountContiguousCharacters				(s8* source, u32 maxExpectedLength);
	u32						iiCountContiguousCharacters				(u8* source, u32 maxExpectedLength);

	s64						iMath_delta								(s64 tnBaseValue, s64 tnSubtractionValue);
	s8*						iMath_roundTo							(f64* tfValue, f64 tfRoundTo);
	bool					iMath_between							(s32 tnValue, s32 tnN1, s32 tnN2);
	bool					iMath_isRectInRect						(RECT* rcHaystack, RECT* rcNeedle, bool tlIncludeOversizes);
	RECT*					iiMath_computeRectDeltas				(RECT* rcDelta, RECT* rcNow, RECT* rcPrior);
	bool					iMath_getAs_rrggbb						(u8* rrggbb, u8* tnBlu, u8* tnGrn, u8* tnRed);
	bool					iMath_getAs_rgb							(u8* rgb, u8* tnBlu, u8* tnGrn, u8* tnRed);

	s8*						iDuplicateString						(s8* tcText);

	// Mouse processing (callback from iWindow_wndProc()
	s32						iMouse_processMessage					(SWindow* win, UINT msg, WPARAM w, LPARAM l);
	void					iiMouse_translatePosition				(SWindow* win, POINTS* pt, UINT msg);
	s32						iiMouse_processMouseEvents				(SWindow* win, UINT msg, WPARAM w, LPARAM l);
	void					iiMouse_processMouseEvents_windowSpecial(SWindow* win);
	bool					iiMouse_processMouseEvents_mouseMove	(SWindow* win, SObject* obj, RECT* rc,         bool tlProcessChildren, bool tlProcessSiblings, bool* tlProcessed);
	bool					iiMouse_processMouseEvents_common		(SWindow* win, SObject* obj, RECT* rc, UINT m, bool tlProcessChildren, bool tlProcessSiblings, bool* tlProcessed);
//	s32						iiMouse_processMouseEvents_nonclient	(SWindow* win, UINT m, WPARAM w, LPARAM l);
	void					iiMouse_getFlags_wparam					(WPARAM w, bool* tlCtrl, bool* tlAlt, bool* tlShift, bool* tlLeft, bool* tlMiddle, bool* tlRight, bool* tlCaps, bool* tlAnyButton);
	void					iiMouse_getFlags_async					(          bool* tlCtrl, bool* tlAlt, bool* tlShift, bool* tlLeft, bool* tlMiddle, bool* tlRight, bool* tlCaps, bool* tlAnyButton);

	// For processing keystrokes
	s32						iKeyboard_processMessage				(SWindow* win, UINT m, WPARAM w, LPARAM l);

	// EditManager
	// Moved to sem.cpp and renamed sem (struct edit manager, also a reference to Sammy Edward Mitchell from the SEMware editor, which guided me from 1990s through until today Jan.11.2015 as it is still the best editor I've ever used

	// Edit Chain
	// Moved to sem_line.cpp and renamed line

	// Engine
	// Moved to engine.cpp
