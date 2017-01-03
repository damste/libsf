//////////
//
// /libsf/source/vjr/source/dbf/dbf_const.h
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
// Version 0.55
// Copyright (c) 2014-2017 by Rick C. Hodgin
//////
// Last update:
//     Nov.02.2014
//////
// Change log:
//     Nov.02.2014 - Initial creation
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
// Constants
/////
	#define		_MAX_DBF_SLOTS						512			// Up to 512 work areas can be opened simultaneously
	#define		_MAX_DBC_SLOTS						512			// Up to 512 containers can be opened simultaneously
	#define		_MAX_SCX_SLOTS						1024		// Up to 1024 forms can be opened simultaneously
	#define		_MAX_VCX_SLOTS						2048		// Up to 2048 classes can be opened simultaneously
	#define		_MAX_FRX_SLOTS						32			// Up to 32 reports can be opened simultaneously
	#define		_MAX_MNX_SLOTS						128			// Up to 128 menus can be opened simultaneously
	#define		_MAX_CDX_TAGS						128			// Up to 128 index tags are supported per CDX, per DBF
	#define		_MAX_SDX_TAGS						128			// Up to 128 index tags are supported per SDX, per DBF
	#define		_MAX_IDX_KEY_LENGTH					100			// Up to 100 bytes per IDX key
	#define		_MAX_CDX_KEY_LENGTH					240			// Up to 240 bytes per CDX key
	#define		_MAX_SDX_KEY_LENGTH					2000		// Up to 2000 bytes per SDX key
	#define		_MAX_ALIAS_NAME_LENGTH				128			// Why not? :-)

	#define		_MIN_SLEEP_INTERVAL_BETWEEN_LOCK_FILE_RETRY_ATTEMPTS 20		// Minimum of 0.05 seconds between attempts
	#define		_MAX_SLEEP_INTERVAL_BETWEEN_LOCK_FILE_RETRY_ATTEMPTS 10000	// Up to 10 seconds between retry attempts

	// Errors
	#define		_DBF_ERROR__INTERNAL_PROGRAMMER		-9999
	#define		_DBF_OKAY							0
	// Note:  Make sure these are sync'd up with iDbf_signalError()
	#define		_DBF_ERROR_WORK_AREA_NOT_IN_USE		-1
	#define		_DBF_ERROR_WORK_AREA_ALREADY_IN_USE	-2
	#define		_DBF_ERROR_UNABLE_TO_OPEN_TABLE		-3
	#define		_DBF_ERROR_ERROR_READING_HEADER1	-4
	#define		_DBF_ERROR_UNKNOWN_TABLE_TYPE		-5
	#define		_DBF_ERROR_MEMORY_ALLOCATION		-6
	#define		_DBF_ERROR_ERROR_READING_HEADER2	-7
	#define		_DBF_ERROR_TABLE_NAME_TOO_LONG		-8
	#define		_DBF_ERROR_MEMORY_ROW				-9
	#define		_DBF_ERROR_MEMORY_ORIGINAL			-10
	#define		_DBF_ERROR_MEMORY_INDEX				-11
	#define		_DBF_ERROR_DBC						-12
	#define		_DBF_ERROR_NO_MORE_WORK_AREAS		-13
	#define		_DBF_ERROR_INVALID_WORK_AREA		-14
	#define		_DBF_ERROR_LOCKING					-15
	#define		_DBF_ERROR_WRITING					-16
	#define		_DBF_ERROR_SEEKING					-17
	#define		_DBF_ERROR_NO_DATA					-18
	#define		_DBF_ERROR_UNKNOWN_MEMO_FORMAT		-19
	#define		_DBF_ERROR_UNABLE_TO_OPEN_JOURNAL	-20

	// For field flags
	#define 	_DBF_FIELD_SYSTEM					0x01
	#define 	_DBF_FIELD_NULLS					0x02
	#define 	_DBF_FIELD_BINARY					0x04
	#define 	_DBF_FIELD_AUTO_INC					0x0c
	
	// Miscellaneous access
	#define 	_BIT_1								0x1
	#define 	_BIT_2								0x2
	#define 	_BIT_4								0x4
	#define 	_BIT_8								0x8
	#define 	_BIT_16								0x10
	#define 	_BIT_32								0x20
	#define 	_BIT_64								0x40
	#define 	_BIT_128							0x80


//////////
// Strings
//////									
	const u8	cgcDbfKeyName[]						= "$__cur__$";
	const u8	cgcDbcKeyName[]						= "$__dbc__$";
	const u8	cgcScxKeyName[]						= "$__scx__$";
	const u8	cgcVcxKeyName[]						= "$__vcx__$";
	const u8	cgcFrxKeyName[]						= "$__frx__$";
	const u8	cgcMnxKeyName[]						= "$__mnx__$";
	const u8	cgcIdxExtension[]					= "idx";
	const u8	cgcCdxExtension[]					= "cdx";
	const u8	cgcSdxExtension[]					= "sdx";
	const u8	cgcDcxExtension[]					= "dcx";
	const u8	cgcJrnExtension[]					= "jrn";
	const u8	cgcObjectId[]						= "objectId";
	const u8	cgcParentId[]						= "parentId";
	const u8	cgcObjectType[]						= "objectType";
	const u8	cgcObjectName[]						= "objectName";
	const u8	cgcCode[]							= "code";
	const u8	cgcRiInfo[]							= "riInfo";
	const u8	cgcUser[]							= "user";
	const u8	cgcObjType[]						= "objType";
	const u8	cgcObjCode[]						= "objCode";
	const u8	cgcName[]							= "name";
	const u8	cgcPrompt[]							= "prompt";
	const u8	cgcCommand[]						= "command";
	const u8	cgcMessage[]						= "message";
	const u8	cgcProcType[]						= "procType";
	const u8	cgcProcedure[]						= "procedure";
	const u8	cgcSetupType[]						= "setupType";
	const u8	cgcSetup[]							= "setup";
	const u8	cgcCleanType[]						= "cleanType";
	const u8	cgcCleanup[]						= "cleanup";
	const u8	cgcMark[]							= "mark";
	const u8	cgcKeyName[]						= "keyName";
	const u8	cgcKeyLabel[]						= "keyLabel";
	const u8	cgcSkipFor[]						= "skipFor";
	const u8	cgcNameChange[]						= "nameChange";
	const u8	cgcNumItems[]						= "numItems";
	const u8	cgcLevelName[]						= "levelName";
	const u8	cgcItemNum[]						= "itemNum";
	const u8	cgcComment[]						= "comment";
	const u8	cgcLocation[]						= "location";
	const u8	cgcScheme[]							= "scheme";
	const u8	cgcSysRes[]							= "sysRes";
	const u8	cgcResName[]						= "resName";
	const u8	cgcPlatform[]						= "platform";
	const u8	cgcUniqueId[]						= "uniqueId";
	const u8	cgcTimeStamp[]						= "timeStamp";
	const u8	cgcClass[]							= "class";
	const u8	cgcClassLoc[]						= "classLoc";
	const u8	cgcBaseClass[]						= "baseClass";
	const u8	cgcObjName[]						= "objName";
	const u8	cgcParent[]							= "parent";
	const u8	cgcProperties[]						= "properties";
	const u8	cgcProtected[]						= "protected";
	const u8	cgcMethods[]						= "methods";
	const u8	cgcOle[]							= "ole";
	const u8	cgcOle2[]							= "ole2";
	const u8	cgcReserved1[]						= "reserved1";
	const u8	cgcReserved2[]						= "reserved2";
	const u8	cgcReserved3[]						= "reserved3";
	const u8	cgcReserved4[]						= "reserved4";
	const u8	cgcReserved5[]						= "reserved5";
	const u8	cgcReserved6[]						= "reserved6";
	const u8	cgcReserved7[]						= "reserved7";
	const u8	cgcReserved8[]						= "reserved8";
	const u8	cgcExpr[]							= "expr";
	const u8	cgcVpos[]							= "vpos";
	const u8	cgcHpos[]							= "hpos";
	const u8	cgcHeight[]							= "height";
	const u8	cgcWidth[]							= "width";
	const u8	cgcStyle[]							= "style";
	const u8	cgcPicture[]						= "picture";
	const u8	cgcOrder[]							= "order";
	const u8	cgcUnique[]							= "unique";
	const u8	cgcEnviron[]						= "environ";
	const u8	cgcBoxChar[]						= "boxchar";
	const u8	cgcFillChar[]						= "fillchar";
	const u8	cgcTag[]							= "tag";
	const u8	cgcTag2[]							= "tag2";
	const u8	cgcPenRed[]							= "penred";
	const u8	cgcPenGreen[]						= "pengreen";
	const u8	cgcPenBlue[]						= "penblue";
	const u8	cgcFillRed[]						= "fillred";
	const u8	cgcFillGreen[]						= "fillgreen";
	const u8	cgcFillBlue[]						= "fillblue";
	const u8	cgcPenSize[]						= "pensize";
	const u8	cgcPenPat[]							= "penpat";
	const u8	cgcFillPat[]						= "fillpat";
	const u8	cgcFontFace[]						= "fontface";
	const u8	cgcFontStyle[]						= "fontstyle";
	const u8	cgcFontSize[]						= "fontsize";
	const u8	cgcMode[]							= "mode";
	const u8	cgcRuler[]							= "ruler";
	const u8	cgcRulerLines[]						= "rulerlines";
	const u8	cgcGrid[]							= "grid";
	const u8	cgcGridY[]							= "gridy";
	const u8	cgcGridH[]							= "gridh";
	const u8	cgcFloat[]							= "float";
	const u8	cgcStretch[]						= "stretch";
	const u8	cgcStretchTop[]						= "stretchtop";
	const u8	cgcTop[]							= "top";
	const u8	cgcBottom[]							= "bottom";
	const u8	cgcSubType[]						= "subtype";
	const u8	cgcSubRest[]						= "subrest";
	const u8	cgcNoRepeat[]						= "norepeat";
	const u8	cgcResetRpt[]						= "resetrpt";
	const u8	cgcPageBreak[]						= "pagebreak";
	const u8	cgcColBreak[]						= "colbreak";
	const u8	cgcResetPage[]						= "resetpage";
	const u8	cgcGeneral[]						= "general";
	const u8	cgcSpacing[]						= "spacing";
	const u8	cgcDouble[]							= "double";
	const u8	cgcSwapHeader[]						= "swapheader";
	const u8	cgcSwapFooter[]						= "swapfooter";
	const u8	cgcEjectBefore[]					= "ejectbefor";
	const u8	cgcEjectAfter[]						= "ejectafter";
	const u8	cgcPlain[]							= "plain";
	const u8	cgcSummary[]						= "summary";
	const u8	cgcAddAlias[]						= "addalias";
	const u8	cgcOffset[]							= "offset";
	const u8	cgcTopMargin[]						= "topmargin";
	const u8	cgcBotMargin[]						= "botmargin";
	const u8	cgcTotalType[]						= "totaltype";
	const u8	cgcResetTotal[]						= "resettotal";
	const u8	cgcResoId[]							= "resoid";
	const u8	cgcCurPos[]							= "curpos";
	const u8	cgcSupAlways[]						= "supalways";
	const u8	cgcSupOvflow[]						= "supovflow";
	const u8	cgcSupRpcol[]						= "suprpcol";
	const u8	cgcGroup[]							= "group";
	const u8	cgcSupValChng[]						= "supvalchng";
	const u8	cgcSupExpr[]						= "supexpr";
