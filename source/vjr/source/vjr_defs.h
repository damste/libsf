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




//////////
// vjr.cpp
//////
//	int APIENTRY			WinMain									(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, s32 nCmdShow);
	void					iVjr_init								(HACCEL* hAccelTable);
	void					iVjr_init_loadCaskIcons					(void);
	void					iVjr_init_loadBitmapArray				(void);
	void					iVjr_createOverlayListing				(SBitmap* bmp, RECT* trc);
	void					iVjr_renderOverlayListing				(SBitmap* bmp, RECT* trc);
	void					iiVjr_renderAccomplishment				(SBitmap* bmp, RECT* trc, s32 tnRAG, cs8* tcAccomplishment, s8* tcVersion, bool tlBold, bool tlItalic, bool tlUnderline, s32 tnAdjustAccomplishmentFontSize, s32 tnAdjustVersionFontSize);
	void					iVjr_renderAccomplishments				(SBitmap* bmp, RECT* trc);

	void					iDatum_duplicate						(SDatum* datumDst, SVariable* varSrc);


//////////
// objects/base.cpp
// Note:  Property accessors are in the object_accessors.h and object_accessors.cpp source files
//////
	SObject*				iObj_create								(SThisCode* thisCode, s32 objType, SObject* objParent);
	SObject*				iObj_addChild							(SThisCode* thisCode, s32 objType, SObject* objParent);
	SObject*				iObj_copy								(SThisCode* thisCode, SObject*  template_obj, SObject* prevObj, SObject* nextObj, SObject* parent, bool tlCopyChildren, bool tlCopySiblings, bool tlCreateSeparateBitmapBuffers);
	void					iObj_delete								(SThisCode* thisCode, SObject** obj, bool tlDeleteSelf, bool tlDeleteChildren, bool tlDeleteSiblings);
	bool					iObj_setFocus							(SThisCode* thisCode, SWindow*  win, SObject* obj, bool tlClearOtherControlsWithFocus);
	void					iObj_clearFocus							(SThisCode* thisCode, SWindow*  win, SObject* obj, bool tlClearChildren, bool tlClearSiblings);
	SObject*				iObj_find_rootmostObject				(SThisCode* thisCode, SObject*  obj);
	bool					iObj_find_screenRect					(SThisCode* thisCode, SObject*  obj, RECT* rc);
	bool					iObj_find_relativeRect					(SThisCode* thisCode, SObject*  objThis, SObject* objTarget, s32 x, s32 y, RECT* rc, bool tlProcessChildren, bool tlProcessSiblings);
	SObject*				iObj_find_thisForm						(SThisCode* thisCode, SObject*  obj);
	SObject*				iObj_find_thisSubform					(SThisCode* thisCode, SObject*  obj);
	SObject*				iObj_find_thisRider						(SThisCode* thisCode, SObject*  obj);
	SObject*				iiObj_findParentObject_byType			(SThisCode* thisCode, SObject*  objStart, s32 objType, bool tlSearchSelf);
	SObject*				iiObj_findChildObject_byName			(SThisCode* thisCode, SObject*  objStart, SDatum* name, bool tlSearchSelf, bool tlSearchChildren, bool tlSearchSiblings);
	bool					iObj_isCommandWindow					(SThisCode* thisCode, SObject*  obj);
	void					iObj_setFocusHighlights					(SThisCode* thisCode, SWindow*  win, SObject* obj, s32 x, s32 y, bool tlProcessChildren, bool tlProcessSiblings);
	void					iObj_findFocusControls					(SThisCode* thisCode, SObject*  obj, SBuilder* objFocusControls, bool tlProcessSiblings);
	bool					iObj_setFocusObjectPrev					(SThisCode* thisCode, SWindow*  win, SObject* obj);
	bool					iObj_setFocusObjectNext					(SThisCode* thisCode, SWindow*  win, SObject* obj);
	bool					iObj_focus_descentCheck					(SThisCode* thisCode, SObject*  obj, bool tlCheckChildren, bool tlCheckSiblings);
	SObject*				iObj_focus_descentCheckObj				(SThisCode* thisCode, SObject*  obj, bool tlCheckChildren, bool tlCheckSiblings);
	void					iObj_setDirtyRender_ascent				(SThisCode* thisCode, SObject*  obj, bool tlMarkParents);
	void					iObj_setDirtyRender_descent				(SThisCode* thisCode, SObject*  obj, bool tlProcessChildren, bool tlProcessSiblings);
	void					iObj_setDirtyPublish_ascent				(SThisCode* thisCode, SObject*  obj, bool tlMarkParents);
	void					iObj_setDirtyPublish_descent			(SThisCode* thisCode, SObject*  obj, bool tlProcessChildren, bool tlProcessSiblings);
	u32						iObj_render								(SThisCode* thisCode, SObject*  obj, bool tlForceRender);
	bool					iObj_render_descentCheck				(SThisCode* thisCode, SObject*  obj, bool tlCheckChildren, bool tlCheckSiblings);
	u32						iObj_renderChildrenAndSiblings			(SThisCode* thisCode, SObject*  obj, bool tlRenderChildren, bool tlRenderSiblings, bool tlForceRender);
	u32						iObj_publish							(SThisCode* thisCode, SObject*  obj, RECT* rc, SBitmap* bmpDst, bool tlPublishChildren, bool tlPublishSiblings, bool tlForcePublish, s32 tnLevel);
	bool					iObj_publish_descentCheck				(SThisCode* thisCode, SObject*  obj, bool tlCheckChildren, bool tlCheckSiblings);
	CXml*					iObj_saveLayoutAs_bxml					(SThisCode* thisCode, SObject* obj, cu8* tcFilename, bool tlFullProperties, bool tlSaveChildren, bool tlSaveSiblings, bool* error, u32* errorNum);
	CXml*					iiObj_saveLayoutAs_bxml_saveObject		(SThisCode* thisCode, CXml* bxml, SObject* obj, bool tlFullProperties, bool tlSaveChildren, bool tlSaveSiblings);
	void					iObj_duplicateChain						(SThisCode* thisCode, SObject** root, SObject* chain);
	void					iObj_appendObjToParent					(SThisCode* thisCode, SObject*  parent, SObject* obj);
	void					iObj_duplicateChildren					(SThisCode* thisCode, SObject*  objDst, SObject* objSrc);
	void					iObj_setPosition						(SThisCode* thisCode, SObject*  obj, s32 tnLeft, s32 tnTop);
	void					iObj_setSize							(SThisCode* thisCode, SObject*  obj, s32 tnLeft, s32 tnTop, s32 tnWidth, s32 tnHeight);
	void					iiObj_setSize_snapForToolbar			(SThisCode* thisCode, SObject*  obj, s32* tnWidth, s32* tnHeight);
	SWindow* 				iObj_createWindowForForm				(SThisCode* thisCode, SObject*  form, SWindow* win, s32 icon);
	SVariable*				iObj_getPropertyAsVariable				(SThisCode* thisCode, SObject*  obj, s8* tcPropertyName, u32 tnPropertyNameLength, SComp* comp, bool tlCreateAsReference);
	void					iiObj_resetToDefault					(SThisCode* thisCode, SObject*  obj, bool tlResetProperties, bool tlResetMethods);
	void					iiObj_resetToDefaultCommon				(SThisCode* thisCode, SObject*  obj, bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, s32 tnPropCount);
	s32						iiObj_getBaseclassType_byName			(SThisCode* thisCode, s8* tcTextname, s32 tnTextnameLength);
	SBaseClassMap*			iiObj_getBaseclass_byName				(SThisCode* thisCode, s8* tcTextname, s32 tnTextnameLength);
	SBaseClassMap*			iiObj_getBaseclass_byType				(SThisCode* thisCode, s32 tnObjType);


//////////
// objects/create.cpp
//////
	// Creation of individual sub-objects
	SObject*				iSubobj_createEmpty						(SThisCode* thisCode, SObject*	template_empty,			SObject* parent);
	SObject*				iSubobj_createForm						(SThisCode* thisCode, SObject*	template_form,			SObject* parent);
	SObject*				iSubobj_createSubform					(SThisCode* thisCode, SObject*	template_subform,		SObject* parent);
	SObject*				iSubobj_createCarousel					(SThisCode* thisCode, SObject*	template_carousel,		SObject* parent);
	SObject*				iSubobj_createRider						(SThisCode* thisCode, SObject*	template_rider,			SObject* parent);
	SObject*				iSubobj_createLabel						(SThisCode* thisCode, SObject*	template_label,			SObject* parent);
	SObject*				iSubobj_createTextbox					(SThisCode* thisCode, SObject*	template_textbox,		SObject* parent);
	SObject*				iSubobj_createButton					(SThisCode* thisCode, SObject*	template_button,		SObject* parent);
	SObject*				iSubobj_createEditbox					(SThisCode* thisCode, SObject*	template_editbox,		SObject* parent);
	SObject*				iSubobj_createImage						(SThisCode* thisCode, SObject*	template_image,			SObject* parent);
	SObject*				iSubobj_createCheckbox					(SThisCode* thisCode, SObject*	template_checkbox,		SObject* parent);
	SObject*				iSubobj_createOption					(SThisCode* thisCode, SObject*	template_option,		SObject* parent);
	SObject*				iSubobj_createRadio						(SThisCode* thisCode, SObject*	template_radio,			SObject* parent);
	SObject*				iSubobj_createCmdGroup					(SThisCode* thisCode, SObject*	template_CmdGroup,		SObject* parent);
	SObject*				iSubobj_createOptGroup					(SThisCode* thisCode, SObject*	template_OptGroup,		SObject* parent);
	SObject*				iSubobj_createListbox					(SThisCode* thisCode, SObject*	template_Listbox,		SObject* parent);
	SObject*				iSubobj_createCombobox					(SThisCode* thisCode, SObject*	template_Combobox,		SObject* parent);
	SObject*				iSubobj_createFormset					(SThisCode* thisCode, SObject*	template_Formset,		SObject* parent);
	SObject*				iSubobj_createToolbar					(SThisCode* thisCode, SObject*	template_Toolbar,		SObject* parent);
	SObject*				iSubobj_createSeparator					(SThisCode* thisCode, SObject*	template_Separator,		SObject* parent);
	SObject*				iSubobj_createLine						(SThisCode* thisCode, SObject*	template_Line,			SObject* parent);
	SObject*				iSubobj_createShape						(SThisCode* thisCode, SObject*	template_Shape,			SObject* parent);
	SObject*				iSubobj_createContainer					(SThisCode* thisCode, SObject*	template_Container,		SObject* parent);
	SObject*				iSubobj_createControl					(SThisCode* thisCode, SObject*	template_Control,		SObject* parent);
	SObject*				iSubobj_createGrid						(SThisCode* thisCode, SObject*	template_Grid,			SObject* parent);
	SObject*				iSubobj_createColumn					(SThisCode* thisCode, SObject*	template_Column,		SObject* parent);
	SObject*				iSubobj_createHeader					(SThisCode* thisCode, SObject*	template_Header,		SObject* parent);
	SObject*				iSubobj_createOleBound					(SThisCode* thisCode, SObject*	template_OleBound,		SObject* parent);
	SObject*				iSubobj_createOleContain				(SThisCode* thisCode, SObject*	template_OleContain,	SObject* parent);
	SObject*				iSubobj_createSpinner					(SThisCode* thisCode, SObject*	template_Spinner,		SObject* parent);
	SObject*				iSubobj_createTimer						(SThisCode* thisCode, SObject*	template_Timer,			SObject* parent);
	SObject*				iSubobj_createHyperlink					(SThisCode* thisCode, SObject*	template_Hyperlink,		SObject* parent);
	SObject*				iSubobj_createCollection				(SThisCode* thisCode, SObject*	template_Collection,	SObject* parent);
	SObject*				iSubobj_createPage						(SThisCode* thisCode, SObject*	template_Page,			SObject* parent);
	SObject*				iSubobj_createPageFrame					(SThisCode* thisCode, SObject*	template_Pageframe,		SObject* parent);
	SObject*				iSubobj_createSession					(SThisCode* thisCode, SObject*	template_Session,		SObject* parent);
	SObject*				iSubobj_createCustom					(SThisCode* thisCode, SObject*	template_Custom,		SObject* parent);
	SObject*				iSubobj_createException					(SThisCode* thisCode, SObject*	template_Exception,		SObject* parent);
	SObject*				iSubobj_createSettings					(SThisCode* thisCode, SObject*	template_Settings,		SObject* parent);


//////////
// objects/copy.cpp
//////
	// For copy operations
	void					iiSubobj_copyEmpty						(SThisCode* thisCode, SObject*	emptyDst,		SObject*	emptySrc);
	void					iiSubobj_copyForm						(SThisCode* thisCode, SObject*	formDst,		SObject*	formSrc);
	void					iiSubobj_copySubform					(SThisCode* thisCode, SObject*	subformDst,		SObject*	subformSrc);
	void					iiSubobj_copyCarousel					(SThisCode* thisCode, SObject*	carouselDst,	SObject*	carouselSrc);
	void					iiSubobj_copyRider						(SThisCode* thisCode, SObject*	riderDst,		SObject*	riderSrc);
	void					iiSubobj_copyLabel						(SThisCode* thisCode, SObject*	labelDst,		SObject*	labelSrc);
	void					iiSubobj_copyTextbox					(SThisCode* thisCode, SObject*	textboxDst,		SObject*	textboxSrc);
	void					iiSubobj_copyButton						(SThisCode* thisCode, SObject*	buttonDst,		SObject*	buttonSrc);
	void					iiSubobj_copyEditbox					(SThisCode* thisCode, SObject*	editboxDst,		SObject*	editboxSrc);
	void					iiSubobj_copyImage						(SThisCode* thisCode, SObject*	imageDst,		SObject*	imageSrc);
	void					iiSubobj_copyCheckbox					(SThisCode* thisCode, SObject*	checkboxDst,	SObject*	checkboxSrc);
	void					iiSubobj_copyOption						(SThisCode* thisCode, SObject*	optionDst,		SObject*	optionSrc);
	void					iiSubobj_copyRadio						(SThisCode* thisCode, SObject*	radioDst,		SObject*	radioSrc);
	void					iiSubobj_copyCmdGroup					(SThisCode* thisCode, SObject*	cmdGroupDst,	SObject*	cmdGroupSrc);
	void					iiSubobj_copyOptGroup					(SThisCode* thisCode, SObject*	optGroupDst,	SObject*	optGroupSrc);
	void					iiSubobj_copyListbox					(SThisCode* thisCode, SObject*	listboxDst,		SObject*	listboxSrc);
	void					iiSubobj_copyCombobox					(SThisCode* thisCode, SObject*	comboboxDst,	SObject*	comboboxSrc);
	void					iiSubobj_copyFormset					(SThisCode* thisCode, SObject*	formsetDst,		SObject*	formsetSrc);
	void					iiSubobj_copyToolbar					(SThisCode* thisCode, SObject*	toolbarDst,		SObject*	toolbarSrc);
	void					iiSubobj_copySeparator					(SThisCode* thisCode, SObject*	separatorDst,	SObject*	separatorSrc);
	void					iiSubobj_copyLine						(SThisCode* thisCode, SObject*	lineDst,		SObject*	lineSrc);
	void					iiSubobj_copyShape						(SThisCode* thisCode, SObject*	shapeDst,		SObject*	shapeSrc);
	void					iiSubobj_copyContainer					(SThisCode* thisCode, SObject*	containerDst,	SObject*	containerSrc);
	void					iiSubobj_copyControl					(SThisCode* thisCode, SObject*	controlDst,		SObject*	controlSrc);
	void					iiSubobj_copyGrid						(SThisCode* thisCode, SObject*	gridDst,		SObject*	gridSrc);
	void					iiSubobj_copyColumn						(SThisCode* thisCode, SObject*	columnDst,		SObject*	columnSrc);
	void					iiSubobj_copyHeader						(SThisCode* thisCode, SObject*	headerDst,		SObject*	headerSrc);
	void					iiSubobj_copyOleBound					(SThisCode* thisCode, SObject*	oleBoundDst,	SObject*	oleBoundSrc);
	void					iiSubobj_copyOleContain					(SThisCode* thisCode, SObject*	oleContainDst,	SObject*	oleContainSrc);
	void					iiSubobj_copySpinner					(SThisCode* thisCode, SObject*	spinnerDst,		SObject*	spinnerSrc);
	void					iiSubobj_copyTimer						(SThisCode* thisCode, SObject*	timerDst,		SObject*	timerSrc);
	void					iiSubobj_copyHyperlink					(SThisCode* thisCode, SObject*	hyperlinkDst,	SObject*	hyperlinkSrc);
	void					iiSubobj_copyCollection					(SThisCode* thisCode, SObject*	collectionDst,	SObject*	collectionSrc);
	void					iiSubobj_copyPage						(SThisCode* thisCode, SObject*	pageDst,		SObject*	pageSrc);
	void					iiSubobj_copyPageframe					(SThisCode* thisCode, SObject*	pageframeDst,	SObject*	pageframeSrc);
	void					iiSubobj_copySession					(SThisCode* thisCode, SObject*	sessionDst,		SObject*	sessionSrc);
	void					iiSubobj_copyCustom						(SThisCode* thisCode, SObject*	customDst,		SObject*	customSrc);
	void					iiSubobj_copyException					(SThisCode* thisCode, SObject*	exceptionDst,	SObject*	exceptionSrc);


//////////
// objects/reset.cpp
//////
	// For initialization
	void					iiSubobj_resetToDefaultEmpty			(SThisCode* thisCode, SObject*	empty,		bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount);
	void					iiSubobj_resetToDefaultForm				(SThisCode* thisCode, SObject*	form,		bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount);
	void					iiSubobj_resetToDefaultSubform			(SThisCode* thisCode, SObject*	subform,	bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount);
	void					iiSubobj_resetToDefaultCarousel			(SThisCode* thisCode, SObject*	carousel,	bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount);
	void					iiSubobj_resetToDefaultRider			(SThisCode* thisCode, SObject*	rider,		bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount);
	void					iiSubobj_resetToDefaultLabel			(SThisCode* thisCode, SObject*	label,		bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount);
	void					iiSubobj_resetToDefaultTextbox			(SThisCode* thisCode, SObject*	textbox,	bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount);
	void					iiSubobj_resetToDefaultButton			(SThisCode* thisCode, SObject*	button,		bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount);
	void					iiSubobj_resetToDefaultEditbox			(SThisCode* thisCode, SObject*	editbox,	bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount);
	void					iiSubobj_resetToDefaultImage			(SThisCode* thisCode, SObject*	image,		bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount);
	void					iiSubobj_resetToDefaultCheckbox			(SThisCode* thisCode, SObject*	checkbox,	bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount);
	void					iiSubobj_resetToDefaultOption			(SThisCode* thisCode, SObject*	option,		bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount);
	void					iiSubobj_resetToDefaultRadio			(SThisCode* thisCode, SObject*	radio,		bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount);
	void					iiSubobj_resetToDefaultCmdGroup			(SThisCode* thisCode, SObject*	cmdGroup,	bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount);
	void					iiSubobj_resetToDefaultOptGroup			(SThisCode* thisCode, SObject*	optGroup,	bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount);
	void					iiSubobj_resetToDefaultListbox			(SThisCode* thisCode, SObject*	listbox,	bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount);
	void					iiSubobj_resetToDefaultCombobox			(SThisCode* thisCode, SObject*	combobox,	bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount);
	void					iiSubobj_resetToDefaultFormset			(SThisCode* thisCode, SObject*	formset,	bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount);
	void					iiSubobj_resetToDefaultToolbar			(SThisCode* thisCode, SObject*	toolbar,	bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount);
	void					iiSubobj_resetToDefaultSeparator		(SThisCode* thisCode, SObject*	separator,	bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount);
	void					iiSubobj_resetToDefaultLine				(SThisCode* thisCode, SObject*	line,		bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount);
	void					iiSubobj_resetToDefaultShape			(SThisCode* thisCode, SObject*	shape,		bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount);
	void					iiSubobj_resetToDefaultContainer		(SThisCode* thisCode, SObject*	container,	bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount);
	void					iiSubobj_resetToDefaultControl			(SThisCode* thisCode, SObject*	control,	bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount);
	void					iiSubobj_resetToDefaultGrid				(SThisCode* thisCode, SObject*	grid,		bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount);
	void					iiSubobj_resetToDefaultColumn			(SThisCode* thisCode, SObject*	column,		bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount);
	void					iiSubobj_resetToDefaultHeader			(SThisCode* thisCode, SObject*	header,		bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount);
	void					iiSubobj_resetToDefaultOleBound			(SThisCode* thisCode, SObject*	oleBound,	bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount);
	void					iiSubobj_resetToDefaultOleContain		(SThisCode* thisCode, SObject*	oleContain,	bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount);
	void					iiSubobj_resetToDefaultSpinner			(SThisCode* thisCode, SObject*	spinner,	bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount);
	void					iiSubobj_resetToDefaultTimer			(SThisCode* thisCode, SObject*	timer,		bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount);
	void					iiSubobj_resetToDefaultHyperlink		(SThisCode* thisCode, SObject*	hyperlink,	bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount);
	void					iiSubobj_resetToDefaultCollection		(SThisCode* thisCode, SObject*	collection,	bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount);
	void					iiSubobj_resetToDefaultPage				(SThisCode* thisCode, SObject*	page,		bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount);
	void					iiSubobj_resetToDefaultPageframe		(SThisCode* thisCode, SObject*	pageframe,	bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount);
	void					iiSubobj_resetToDefaultSession			(SThisCode* thisCode, SObject*	session,	bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount);
	void					iiSubobj_resetToDefaultCustom			(SThisCode* thisCode, SObject*	custom,		bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount);
	void					iiSubobj_resetToDefaultException		(SThisCode* thisCode, SObject*	exception,	bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount);
	void					iiSubobj_resetToDefaultSettings			(SThisCode* thisCode, SObject*	exception,	bool tlResetProperties, bool tlResetMethods, SObjPropMap* propList, u32 tnPropCount);


//////////
// objects/delete.cpp
//////
	// Delete individual sub-objects
	void					iObj_deleteCommon						(SThisCode* thisCode, SObject*	obj);
	void					iSubobj_deleteEmpty						(SThisCode* thisCode, SObject*	empty,		bool tlDeleteSelf);
	void					iSubobj_deleteForm						(SThisCode* thisCode, SObject*	form,		bool tlDeleteSelf);
	void					iSubobj_deleteSubform					(SThisCode* thisCode, SObject*	subform,	bool tlDeleteSelf);
	void					iSubobj_deleteCarousel					(SThisCode* thisCode, SObject*	carousel,	bool tlDeleteSelf, bool tlLeaveRiders, bool tlLeaveObjects);
	void					iSubobj_deleteRider						(SThisCode* thisCode, SObject*	rider,		bool tlDeleteSelf, bool tlLeaveObjects);
	void					iSubobj_deleteLabel						(SThisCode* thisCode, SObject*	label,		bool tlDeleteSelf);
	void					iSubobj_deleteTextbox					(SThisCode* thisCode, SObject*	textbox,	bool tlDeleteSelf);
	void					iSubobj_deleteButton					(SThisCode* thisCode, SObject*	button,		bool tlDeleteSelf);
	void					iSubobj_deleteEditbox					(SThisCode* thisCode, SObject*	editbox,	bool tlDeleteSelf);
	void					iSubobj_deleteImage						(SThisCode* thisCode, SObject*	image,		bool tlDeleteSelf);
	void					iSubobj_deleteCheckbox					(SThisCode* thisCode, SObject*	checkbox,	bool tlDeleteSelf);
	void					iSubobj_deleteOption					(SThisCode* thisCode, SObject*	option,		bool tlDeleteSelf);
	void					iSubobj_deleteRadio						(SThisCode* thisCode, SObject*	radio,		bool tlDeleteSelf);
	void					iSubobj_deleteCmdGroup					(SThisCode* thisCode, SObject*	cmdGroup,	bool tlDeleteSelf);
	void					iSubobj_deleteOptGroup					(SThisCode* thisCode, SObject*	optGroup,	bool tlDeleteSelf);
	void					iSubobj_deleteListbox					(SThisCode* thisCode, SObject*	listbox,	bool tlDeleteSelf);
	void					iSubobj_deleteCombobox					(SThisCode* thisCode, SObject*	combobox,	bool tlDeleteSelf);
	void					iSubobj_deleteFormset					(SThisCode* thisCode, SObject*	formset,	bool tlDeleteSelf);
	void					iSubobj_deleteToolbar					(SThisCode* thisCode, SObject*	toolbar,	bool tlDeleteSelf);
	void					iSubobj_deleteSeparator					(SThisCode* thisCode, SObject*	separator,	bool tlDeleteSelf);
	void					iSubobj_deleteLine						(SThisCode* thisCode, SObject*	line,		bool tlDeleteSelf);
	void					iSubobj_deleteShape						(SThisCode* thisCode, SObject*	shape,		bool tlDeleteSelf);
	void					iSubobj_deleteContainer					(SThisCode* thisCode, SObject*	container,	bool tlDeleteSelf);
	void					iSubobj_deleteControl					(SThisCode* thisCode, SObject*	control,	bool tlDeleteSelf);
	void					iSubobj_deleteGrid						(SThisCode* thisCode, SObject*	grid,		bool tlDeleteSelf);
	void					iSubobj_deleteColumn					(SThisCode* thisCode, SObject*	column,		bool tlDeleteSelf);
	void					iSubobj_deleteHeader					(SThisCode* thisCode, SObject*	header,		bool tlDeleteSelf);
	void					iSubobj_deleteOleBound					(SThisCode* thisCode, SObject*	oleBound,	bool tlDeleteSelf);
	void					iSubobj_deleteOleContain				(SThisCode* thisCode, SObject*	oleContain,	bool tlDeleteSelf);
	void					iSubobj_deleteSpinner					(SThisCode* thisCode, SObject*	spinner,	bool tlDeleteSelf);
	void					iSubobj_deleteTimer						(SThisCode* thisCode, SObject*	timer,		bool tlDeleteSelf);
	void					iSubobj_deleteHyperlink					(SThisCode* thisCode, SObject*	hyperlink,	bool tlDeleteSelf);
	void					iSubobj_deleteCollection				(SThisCode* thisCode, SObject*	collection,	bool tlDeleteSelf);
	void					iSubobj_deletePage						(SThisCode* thisCode, SObject*	page,		bool tlDeleteSelf);
	void					iSubobj_deletePageFrame					(SThisCode* thisCode, SObject*	pageFrame,	bool tlDeleteSelf);
	void					iSubobj_deleteSession					(SThisCode* thisCode, SObject*	session,	bool tlDeleteSelf);
	void					iSubobj_deleteCustom					(SThisCode* thisCode, SObject*	custom,		bool tlDeleteSelf);
	void					iSubobj_deleteException					(SThisCode* thisCode, SObject*	exception,	bool tlDeleteSelf);
	void					iSubobj_deleteSettings					(SThisCode* thisCode, SObject*	settings,	bool tlDeleteSelf);


//////////
// objects/render.cpp
//////
	// Default render of sub-objects
	u32						iSubobj_renderEmpty						(SThisCode* thisCode, SObject* empty);
	u32						iSubobj_renderForm						(SThisCode* thisCode, SObject* form);
	u32						iSubobj_renderSubform					(SThisCode* thisCode, SObject* subform);
	u32						iSubobj_renderCarousel					(SThisCode* thisCode, SObject* carousel);
	u32						iSubobj_renderRider						(SThisCode* thisCode, SObject* rider);
	u32						iSubobj_renderLabel						(SThisCode* thisCode, SObject* label);
	u32						iSubobj_renderTextbox					(SThisCode* thisCode, SObject* textbox);
	u32						iSubobj_renderButton					(SThisCode* thisCode, SObject* button);
	u32						iSubobj_renderEditbox					(SThisCode* thisCode, SObject* editbox);
	u32						iSubobj_renderImage						(SThisCode* thisCode, SObject* image);
	u32						iSubobj_renderCheckbox					(SThisCode* thisCode, SObject* checkbox);
	u32						iSubobj_renderOption					(SThisCode* thisCode, SObject* option);
	u32						iSubobj_renderRadio						(SThisCode* thisCode, SObject* radio);
	u32						iSubobj_renderCmdGroup					(SThisCode* thisCode, SObject* cmdGroup);
	u32						iSubobj_renderOptGroup					(SThisCode* thisCode, SObject* optGroup);
	u32						iSubobj_renderListbox					(SThisCode* thisCode, SObject* listbox);
	u32						iSubobj_renderCombobox					(SThisCode* thisCode, SObject* combobox);
	u32						iSubobj_renderFormset					(SThisCode* thisCode, SObject* formset);
	u32						iSubobj_renderToolbar					(SThisCode* thisCode, SObject* toolbar);
	u32						iSubobj_renderSeparator					(SThisCode* thisCode, SObject* separator);
	u32						iSubobj_renderLine						(SThisCode* thisCode, SObject* line);
	u32						iSubobj_renderShape						(SThisCode* thisCode, SObject* shape);
	u32						iSubobj_renderContainer					(SThisCode* thisCode, SObject* container);
	u32						iSubobj_renderControl					(SThisCode* thisCode, SObject* control);
	u32						iSubobj_renderGrid						(SThisCode* thisCode, SObject* grid);
	u32						iSubobj_renderColumn					(SThisCode* thisCode, SObject* column);
	u32						iSubobj_renderHeader					(SThisCode* thisCode, SObject* header);
	u32						iSubobj_renderOleBound					(SThisCode* thisCode, SObject* oleBound);
	u32						iSubobj_renderOleContain				(SThisCode* thisCode, SObject* oleContain);
	u32						iSubobj_renderSpinner					(SThisCode* thisCode, SObject* spinner);
	u32						iSubobj_renderTimer						(SThisCode* thisCode, SObject* timer);
	u32						iSubobj_renderHyperlink					(SThisCode* thisCode, SObject* hyperlink);
	u32						iSubobj_renderCollection				(SThisCode* thisCode, SObject* collection);
	u32						iSubobj_renderPage						(SThisCode* thisCode, SObject* page);
	u32						iSubobj_renderPageFrame					(SThisCode* thisCode, SObject* pageFrame);
	u32						iSubobj_renderSession					(SThisCode* thisCode, SObject* session);
	u32						iSubobj_renderCustom					(SThisCode* thisCode, SObject* custom);
	u32						iSubobj_renderException					(SThisCode* thisCode, SObject* exception);
	u32						iSubobj_renderSettings					(SThisCode* thisCode, SObject* settings);


//////////
// objects/callbacks.cpp
//////
	bool					iDefaultCallback_resize					(SThisCode* thisCode, SWindow* win, SObject* obj, RECT* rc);
	bool					iDefaultCallback_onLoad					(SThisCode* thisCode, SWindow* win, SObject* obj);
	bool					iDefaultCallback_onInit					(SThisCode* thisCode, SWindow* win, SObject* obj);
	bool					iDefaultCallback_onCreated				(SThisCode* thisCode, SWindow* win, SObject* obj);
	bool					iDefaultCallback_onResize				(SThisCode* thisCode, SWindow* win, SObject* obj, SVariable* widthRequired_out, SVariable* heightRequired_out);
	bool					iDefaultCallback_onRender				(SThisCode* thisCode, SWindow* win, SObject* obj);
	bool					iDefaultCallback_onPublish				(SThisCode* thisCode, SWindow* win, SObject* obj);
	bool					iDefaultCallback_onDestroy				(SThisCode* thisCode, SWindow* win, SObject* obj);
	bool					iDefaultCallback_onUnload				(SThisCode* thisCode, SWindow* win, SObject* obj);
	bool					iDefaultCallback_onGotFocus				(SThisCode* thisCode, SWindow* win, SObject* obj);
	bool					iDefaultCallback_onLostFocus			(SThisCode* thisCode, SWindow* win, SObject* obj);
	bool					iiDefaultCallback_processMouseVariables	(SThisCode* thisCode, 							  SVariable* varX, SVariable* varY, SVariable* varCtrl, SVariable* varAlt, SVariable* varShift, SVariable* varClick, s32* lnX, s32* lnY, bool* tlCtrl, bool* tlAlt, bool* tlShift, u32* lnClick);
	bool					iDefaultCallback_onMouseClickEx			(SThisCode* thisCode, SWindow* win, SObject* obj, SVariable* varX, SVariable* varY, SVariable* varCtrl, SVariable* varAlt, SVariable* varShift, SVariable* varClick);
	bool					iDefaultCallback_onMouseDblClickEx		(SThisCode* thisCode, SWindow* win, SObject* obj, SVariable* varX, SVariable* varY, SVariable* varCtrl, SVariable* varAlt, SVariable* varShift, SVariable* varClick);
	bool					iDefaultCallback_onMouseWheel			(SThisCode* thisCode, SWindow* win, SObject* obj, SVariable* varX, SVariable* varY, SVariable* varCtrl, SVariable* varAlt, SVariable* varShift, SVariable* varClick, SVariable* varUnits);
	bool					iDefaultCallback_onMouseMove			(SThisCode* thisCode, SWindow* win, SObject* obj, SVariable* varX, SVariable* varY, SVariable* varCtrl, SVariable* varAlt, SVariable* varShift, SVariable* varClick);
	bool					iDefaultCallback_onMouseDown			(SThisCode* thisCode, SWindow* win, SObject* obj, SVariable* varX, SVariable* varY, SVariable* varCtrl, SVariable* varAlt, SVariable* varShift, SVariable* varClick);
	bool					iDefaultCallback_onMouseUp				(SThisCode* thisCode, SWindow* win, SObject* obj, SVariable* varX, SVariable* varY, SVariable* varCtrl, SVariable* varAlt, SVariable* varShift, SVariable* varClick);
	bool					iDefaultCallback_onMouseEnter			(SThisCode* thisCode, SWindow* win, SObject* obj);
	bool					iDefaultCallback_onMouseLeave			(SThisCode* thisCode, SWindow* win, SObject* obj);
	bool					iDefaultCallback_onMouseHover			(SThisCode* thisCode, SWindow* win, SObject* obj, SVariable* varX, SVariable* varY, SVariable* varCtrl, SVariable* varAlt, SVariable* varShift, SVariable* varClick);
	bool					iiDefaultCallback_processKeyVariables	(SThisCode* thisCode, 							 SVariable* varCtrl, SVariable* varAlt, SVariable* varShift, SVariable* varCaps, SVariable* varAscii, SVariable* varVKey, SVariable* varIsCAS, SVariable* varIsAscii, bool* tlCtrl, bool* tlAlt, bool* tlShift, bool* tlCaps, bool* tlIsCAS, bool* tlIsAscii, s16* lcAscii, u16* lnVKey);
	bool					iDefaultCallback_onKeyDown				(SThisCode* thisCode, SWindow* win, SObject* obj, SVariable* varCtrl, SVariable* varAlt, SVariable* varShift, SVariable* varCaps, SVariable* varAscii, SVariable* varVKey, SVariable* varIsCAS, SVariable* varIsAscii);
	bool					iDefaultCallback_onKeyUp				(SThisCode* thisCode, SWindow* win, SObject* obj, SVariable* varCtrl, SVariable* varAlt, SVariable* varShift, SVariable* varCaps, SVariable* varAscii, SVariable* varVKey, SVariable* varIsCAS, SVariable* varIsAscii);
	bool					iDefaultCallback_onActivate				(SThisCode* thisCode, SWindow* win, SObject* obj);
	bool					iDefaultCallback_onDeactivate			(SThisCode* thisCode, SWindow* win, SObject* obj);
	bool					iDefaultCallback_onInteractiveChange	(SThisCode* thisCode, SWindow* win, SObject* obj);
	bool					iDefaultCallback_onProgrammaticChange	(SThisCode* thisCode, SWindow* win, SObject* obj);
	bool					iDefaultCallback_onSelect				(SThisCode* thisCode, SWindow* win, SObject* obj);
	bool					iDefaultCallback_onDeselect				(SThisCode* thisCode, SWindow* win, SObject* obj);
	bool					iDefaultCallback_onMoved				(SThisCode* thisCode, SWindow* win, SObject* obj, SVariable* xOverride_out, SVariable* yOverride_out);
	bool					iDefaultCallback_onQueryUnload			(SThisCode* thisCode, SWindow* win, SObject* obj);
	bool					iDefaultCallback_onAddObject			(SThisCode* thisCode, SWindow* win, SObject* obj);
	bool					iDefaultCallback_onAddProperty			(SThisCode* thisCode, SWindow* win, SObject* obj);
	bool					iDefaultCallback_onError				(SThisCode* thisCode, SWindow* win, SObject* obj);
	bool					iDefaultCallback_onScrolled				(SThisCode* thisCode, SWindow* win, SObject* obj);
	bool					iDefaultCallback_onSetActiveControl		(SThisCode* thisCode, SWindow* win, SObject* obj, SVariable* toActive);
	bool					iDefaultCallback_onSpin					(SThisCode* thisCode, SWindow* win, SObject* obj, SVariable* tnDelta, SVariable* tnDirection, SVariable* tnType);

	// Carousel tab-specific
	bool					iDefaultCallback_onTabClose				(SThisCode* thisCode, SWindow* win, SObject* obj);
	bool					iDefaultCallback_onTabClick				(SThisCode* thisCode, SWindow* win, SObject* obj, bool tlOnClose);
	bool					iDefaultCallback_onTabMouseWheel		(SThisCode* thisCode, SWindow* win, SObject* obj, sptr tnClicks);
	bool					iDefaultCallback_onTabMouseMove			(SThisCode* thisCode, SWindow* win, SObject* obj, bool tlOnClose);
	bool					iDefaultCallback_onTabMouseDown			(SThisCode* thisCode, SWindow* win, SObject* obj, bool tlOnClose);
	bool					iDefaultCallback_onTabMouseUp			(SThisCode* thisCode, SWindow* win, SObject* obj, bool tlOnClose);
	bool					iDefaultCallback_onTabMouseEnter		(SThisCode* thisCode, SWindow* win, SObject* obj, bool tlOnClose);
	bool					iDefaultCallback_onTabMouseLeave		(SThisCode* thisCode, SWindow* win, SObject* obj, bool tlOnClose);


//////////
// objects/events.cpp
//////
	void					iEvents_resetToDefault					(SThisCode* thisCode,               SObject* obj);
	// Helper functions to translate strongly typed values to weakly typed variables
	bool					iiEventDispatch_onMouseMove				(SThisCode* thisCode, SWindow* win, SObject* obj, s32 x, s32 y, bool tlCtrl, bool tlAlt, bool tlShift, u32 tnClicks);
	bool					iiEventDispatch_onMouseDown				(SThisCode* thisCode, SWindow* win, SObject* obj, s32 x, s32 y, bool tlCtrl, bool tlAlt, bool tlShift, u32 tnClicks);
	bool					iiEventDispatch_onMouseClickEx			(SThisCode* thisCode, SWindow* win, SObject* obj, s32 x, s32 y, bool tlCtrl, bool tlAlt, bool tlShift, u32 tnClicks);
	bool					iiEventDispatch_onMouseUp				(SThisCode* thisCode, SWindow* win, SObject* obj, s32 x, s32 y, bool tlCtrl, bool tlAlt, bool tlShift, u32 tnClicks);
	bool					iiEventDispatch_onMouseWheel			(SThisCode* thisCode, SWindow* win, SObject* obj, s32 x, s32 y, bool tlCtrl, bool tlAlt, bool tlShift, u32 tnClicks, s32 tnDeltaY);
	bool					iiEventDispatch_onKeyDown				(SThisCode* thisCode, SWindow* win, SObject* obj, bool tlCtrl, bool tlAlt, bool tlShift, bool tlCaps, u16 tnAsciiChar, u16 tvKey, bool tlIsCAS, bool tlIsAscii);
	bool					iiEventDispatch_onKeyUp					(SThisCode* thisCode, SWindow* win, SObject* obj, bool tlCtrl, bool tlAlt, bool tlShift, bool tlCaps, u16 tnAsciiChar, u16 tvKey, bool tlIsCAS, bool tlIsAscii);

	// Carousel
	bool					iEvents_carouselMouseWheel				(SThisCode* thisCode, SWindow* win, SObject* obj, s32 lnX, s32 lnY, bool llCtrl, bool llAlt, bool llShift, u32 lnClick);
	bool					iEvents_carouselMouseMove				(SThisCode* thisCode, SWindow* win, SObject* obj, s32 lnX, s32 lnY, bool llCtrl, bool llAlt, bool llShift, u32 lnClick);
	bool					iEvents_carouselMouseDown				(SThisCode* thisCode, SWindow* win, SObject* obj, s32 lnX, s32 lnY, bool llCtrl, bool llAlt, bool llShift, u32 lnClick);
	bool					iEvents_carouselMouseUp					(SThisCode* thisCode, SWindow* win, SObject* obj, s32 lnX, s32 lnY, bool llCtrl, bool llAlt, bool llShift, u32 lnClick);
	bool					iEvents_carousel_dragStart_tab			(SThisCode* thisCode, SWindow* win, SObject* obj, SBitmap* bmp);
	bool					iEvents_carousel_dragStart_titlebar		(SThisCode* thisCode, SWindow* win, SObject* obj, SBitmap* bmp);
	u32						iiEvents_carousel_findTarget			(SThisCode* thisCode, SWindow* win, SObject* obj, s32 tnX, s32 tnY, SObjCarouselTabData** toctd, bool* tlHighlightChanged);


//////////
// Toolbar related
//////
	SObject*				iToolbar_loadFrom_xml					(SThisCode* thisCode,                                                   cu8* tcXml, u32 tnXmlLength, cs8* tcTagRoot, cs8* tcTagSub);
	bool					iToolbar_applyTo_obj					(SThisCode* thisCode, SObject* objParent, SObject* objToolbarContainer, cu8* tcXml, u32 tnXmlLength, cs8* tcTagRoot, cs8* tcTagSub);


//////////
// DLL-related functions
//////
	// Dll functions
	void					iiDllFunc_dispatch						(SThisCode* thisCode, SFunctionParams* rpar, SDllFunc* dfunc);
	bool					iDllFunc_add							(SThisCode* thisCode, SFunctionParams* rpar, SDllFuncParam* rp, SDllFuncParam ip[], s32 tnIpCount, SComp* compFunctionName, SComp* compAliasName, SComp* compDllName, SThisCode* onAccess, SThisCode* onAssign);
	SDllFunc*				iDllFunc_find_byName					(SThisCode* thisCode, s8* funcName, s32 lnFuncNameLength);

	// Dll library (the physical c:\path\to\theFile.dll
	SDllLib*				iDllLib_open							(SThisCode* thisCode, SComp* compDllName);


//////////
// vjr_sup.cpp
//////
	void					iInit_createMessageWindow				(void);
	bool					isValidWindow							(uptr tnWindow);
	void					iInit_createConstants					(void);
	void					iInit_createGlobalSystemVariables		(void);
	void					iiInit_createGlobalSystemVariable		(SVariable** var, s32 tnType, cu8* tcName, cs8* tcInitValue = NULL, u32 tnInitValueLength = 0);
	void					iInit_createDefaultObjects				(void);
	void					iInit_jdebi_create						(void);
	void					iInit_jdebi_addToolbars					(void);
	void					iInit_createDefaultDatetimes			(void);
	SBitmap*				iiVjr_buildSplashScreen					(SBitmap* bmpSplash);
	void					iVjr_appendSystemLog					(SThisCode* thisCode, u8* tcLogText);
	void					iVjr_flushSystemLog						(SThisCode* thisCode);
	void					iVjr_releaseMemory						(void);
	void					iVjr_releaseAllDefaultDatetimes			(void);
	void					iVjr_releaseAllDefaultObjects			(void);
	void					iVjr_release_jdebi						(void);
	void					iVjr_releaseCaskIcons					(void);
	void					iVjr_shutdown							(SThisCode* thisCode);

	DWORD	WINAPI			iSplash_show							(LPVOID/*SBitmap* bmp*/ lpParameter);
	DWORD	WINAPI			iSplash_delete							(LPVOID/*bool tlWait*/ lpParameter);
	void	CALLBACK		iSplash_timerProc						(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);
	LRESULT CALLBACK		iSplash_wndProc							(HWND hwnd, UINT m, WPARAM w, LPARAM l);

	DWORD	WINAPI			iPlay_ariaSplash						(LPVOID lpParameter);
	void WINAPI				iPlay_ariaSplash_callback				(f32* sampleBuffer, u32 tnSamples, bool* tlContinueAfterThisSampleSet);

	DWORD	WINAPI			iReadEvents_messageWindow				(LPVOID lpParameter);
	LRESULT	CALLBACK		iWindow_wndProcMessage					(HWND hwnd, UINT m, WPARAM w, LPARAM l);
	LRESULT	CALLBACK		iWindow_wndProcForms					(HWND hwnd, UINT m, WPARAM w, LPARAM l);
	SWindow* 				iWindow_createForObject					(SThisCode* thisCode, SObject* obj, SWindow* winReuse, s32 icon);
	void					iWindow_releaseAll						(SBuilder** windowRoot, bool tlDeleteSelf);
	void					iWindow_delete							(SThisCode* thisCode, SWindow* win, bool tlDeleteSelf);
	SWindow*				iWindow_findByHwnd						(HWND hwnd);
	SWindow*				iWindow_findByObj						(SThisCode* thisCode, SObject* obj);
	SWindow*				iWindow_findRoot_byObj					(SThisCode* thisCode, SObject* obj);
	SWindow*				iWindow_allocate						(void);
	void					iWindow_disconnectObj					(SWindow* win, SObject* obj);
	void					iWindow_render							(SThisCode* thisCode, SWindow* win, bool tlForceRedraw);
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

	void					iSourceLight_reset						(void);
	bool					iSourceLight_copy						(SWindow* win, SObject* obj);

	bool					iFile_readContents						(s8* tcFilename, FILE** tfh, s8** data, u32* dataLength);
	bool					iFile_get_justfname						(s8* tcPathname, s32 tnFilenameLength, s8** tcFname, s32* tnFnameLength);

	void					iMisc_adjustColorBrightness				(SBgra& color, f32 tfPercent);
	bool					iInit_shutdownPolitely					(void);

	s8						iLowerCase								(s8 c);
	s8						iUpperCase								(s8 c);

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

	s8*						iDuplicateString						(s8* tcText);

	// Mouse processing (callback from iWindow_wndProc()
	s32						iMouse_processMessage					(SThisCode* thisCode, SWindow* win, UINT msg, WPARAM w, LPARAM l);
	void					iiMouse_translatePosition				(SThisCode* thisCode, SWindow* win, POINTS* pt, UINT msg);
	s32						iiMouse_processMouseEvents				(SThisCode* thisCode, SWindow* win, UINT msg, WPARAM w, LPARAM l);
	void					iiMouse_processMouseEvents_windowSpecial(SThisCode* thisCode, SWindow* win);
	bool					iiMouse_processMouseEvents_mouseMove	(SThisCode* thisCode, SWindow* win, SObject* obj, RECT* rc,         bool tlProcessChildren, bool tlProcessSiblings, bool* tlProcessed);
	bool					iiMouse_processMouseEvents_common		(SThisCode* thisCode, SWindow* win, SObject* obj, RECT* rc, UINT m, bool tlProcessChildren, bool tlProcessSiblings, bool* tlProcessed);
//	s32						iiMouse_processMouseEvents_nonclient	(SThisCode* thisCode, SWindow* win, UINT m, WPARAM w, LPARAM l);
	void					iiMouse_getFlags_wparam					(WPARAM w, bool* tlCtrl, bool* tlAlt, bool* tlShift, bool* tlLeft, bool* tlMiddle, bool* tlRight, bool* tlCaps, bool* tlAnyButton);
	void					iiMouse_getFlags_async					(          bool* tlCtrl, bool* tlAlt, bool* tlShift, bool* tlLeft, bool* tlMiddle, bool* tlRight, bool* tlCaps, bool* tlAnyButton);

	// For processing keystrokes
	s32						iKeyboard_processMessage				(SThisCode* thisCode, SWindow* win, UINT m, WPARAM w, LPARAM l);

	// EditManager
	// Moved to sem.cpp and renamed sem (struct edit manager, also a reference to Sammy Edward Mitchell from the SEMware editor, which guided me from 1990s through until today Jan.11.2015 as it is still the best editor I've ever used

	// Edit Chain
	// Moved to sem_line.cpp and renamed line

	// Engine
	// Moved to engine.cpp
