//////////
//
// /libsf/source/vjr/source/dbf/cdx_const.h
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
// Copyright (c) 2014 by Rick C. Hodgin
//////
// Last update:
//     Jan.02.2015
//////
// Change log:
//     Jan.02.2015 - Initial creation
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
// Macros
//
//////
	// Grabs the node type with only the lower 2-bits being pulled through
	#define cdx_indexNodeType(n) (n & 0x3)




//////////
//
// Constants
//
/////
	// Responses to cdx_open()
	#define		_CDX_OKAY							0
	#define		_CDX_ERROR_INVALID_WORK_AREA		-201
	#define		_CDX_ERROR_UNKNOWN_INDEX_TYPE		-202
	#define		_CDX_ERROR_INDEX_NAME_TOO_LONG		-203
	#define		_CDX_ERROR_MEMORY_IDX				-204
	#define		_CDX_ERROR_READING_HEADER_IDX		-205
	#define		_CDX_ERROR_MEMORY_CDX				-206
	#define		_CDX_ERROR_READING_HEADER_CDX		-207
	#define		_CDX_ERROR_INVALID_KEY_LENGTH		-208
	#define		_CDX_ERROR_INVALID_TAG				-209
	#define		_CDX_ERROR_INVALID_KEY				-210
	#define		_CDX_ERROR_INVALID_INDEX			-211
	#define		_CDX_ERROR_NO_INDEX_IN_USE			-212
	#define		_CDX_LOCK_FAILURE					-213
	#define		_CDX_ERROR_OPENING_INDEX			-214
	#define		_CDX_ERROR_LOCKING_HEADER_IDX		-215
	#define		_CDX_ERROR_LOCKING_HEADER_CDX		-216
	#define		_CDX_ERROR_INVALID_NODE				-217
	#define		_CDX_ERROR_INTERNAL					-218
	#define		_CDX_ERROR_READING_NODE				-219
	#define		_CDX_ERROR_CONTEXTUAL				-10000

	// Index header flags
	#define		_BIT_UNIQUE							0x1
	#define		_BIT_TEMPORARY						0x2
	#define		_BIT_CUSTOM							0x4
	#define		_BIT_FOR_CLAUSE						0x8
	#define		_BIT_COMPACT_INDEX					0x20
	#define		_BIT_COMPOUND_INDEX					0x40
	#define		_BIT_STRUCTURAL_INDEX				0x80

	// Explicit index types for cdx_open()
	#define		_INDEX_NONE							0
	#define		_INDEX_IDX							1
	#define		_INDEX_CDX							2
	#define		_INDEX_SDX							3
	#define		_INDEX_DCX							4

	// CDX no find result
	#define		_CDX_FIND_NEAR						-2
	#define		_CDX_FIND_NO						-1
	#define		_CDX_FIND_EXACT						1

	// CDX node types
	#define		_CDX_NODE_INDEX						0
	#define		_CDX_NODE_ROOT						1
	#define		_CDX_NODE_LEAF						2
	#define		_CDX_NODE_ROOT_LEAF					3
	// Other node types have been observed, but I don't know what they indicate.
	// I use the function iiGetIndexNodeType() to mask off only the lower 2 bits (00,01,10,11 = 0,1,2,3)

	const s8	cgcValidateBegin[]					= "Validate begin";
	const s8	cgcValidateEnd[]					= "Validate end";
	const s8	cgcValidateInvalidNode[]			= "Invalid internal index node was encountered";
	const s8	cgcValidateKeyNotPresent[]			= "An index node indicated N keys present, unable to retrieve all of them";
	const s8	cgcValidateEmptyNode[]				= "An empty index node was found";
	const s8	cgcValidateKeysOutOfOrder[]			= "Index keys are out of order";
