//////////
//
// /libsf/source/vjr/source/dbf/dbf_const.h
//
//////
// Version 0.55
// Copyright (c) 2014 by Rick C. Hodgin
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
	#define		_MAX_DBF_SLOTS				512			// Up to 512 work areas can be opened simultaneously
	#define		_MAX_DBC_SLOTS				512			// Up to 512 containers can be opened simultaneously
	#define		_MAX_SCX_SLOTS				1024		// Up to 1024 forms can be opened simultaneously
	#define		_MAX_VCX_SLOTS				2048		// Up to 2048 classes can be opened simultaneously
	#define		_MAX_FRX_SLOTS				32			// Up to 32 reports can be opened simultaneously
	#define		_MAX_MNX_SLOTS				128			// Up to 128 menus can be opened simultaneously
	#define		_MAX_CDX_TAGS				128			// Up to 128 index tags are supported per CDX, per DBF

	// Errors
	#define		_DBF_ERROR__INTERNAL_PROGRAMMER		-9999
	#define		_DBF_ERROR_WORK_AREA_ALREADY_IN_USE	-2
	#define		_DBF_ERROR_TABLE_NOT_FOUND			-3
	#define		_DBF_ERROR_ERROR_READING_HEADER1	-4
	#define		_DBF_ERROR_UNKNOWN_TABLE_TYPE		-5
	#define		_DBF_ERROR_MEMORY					-6
	#define		_DBF_ERROR_ERROR_READING_HEADER2	-7
	#define		_DBF_ERROR_TABLE_NAME_TOO_LONG		-8
	#define		_DBF_ERROR_MEMORY_ROW				-9
	#define		_DBF_ERROR_MEMORY_ORIGINAL			-10
	#define		_DBF_ERROR_MEMORY_INDEX				-11
	#define		_DBF_ERROR_DBC						-12
	#define		_DBF_ERROR_NO_MORE_WORK_AREAS		-13

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
	const u8	cgcDbcKeyName[]			= "$__dbc__$";
	const u8	cgcScxKeyName[]			= "$__scx__$";
	const u8	cgcVcxKeyName[]			= "$__vcx__$";
	const u8	cgcFrxKeyName[]			= "$__frx__$";
	const u8	cgcMnxKeyName[]			= "$__mnx__$";
	const u8	cgcObjectId[]			= "objectId";
	const u8	cgcParentId[]			= "parentId";
	const u8	cgcObjectType[]			= "objectType";
	const u8	cgcObjectName[]			= "objectName";
