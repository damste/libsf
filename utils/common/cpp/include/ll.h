//////////
//
// /libsf/utils/common/cpp/ll.h
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
// Copyright (c) 2014-2015 by Rick C. Hodgin
//////
// Last update:
//     Nov.02.2014
//////
// Change log:
//     Nov.02.2014 - Initial creation
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
//
// Thank you.  And may The Lord bless you richly as you lift up your life, your
// talents, your gifts, your praise, unto Him.  In Jesus' name I pray.  Amen.
//
//////
//   _       _         _     _       _       _
//  | |     (_)       | |   | |     (_)     | |
//  | |      _  _ __  | | __| |      _  ___ | |_
//  | |     | || '_ \ | |/ /| |     | |/ __|| __|
//  | |____ | || | | ||   < | |____ | |\__ \| |_
//  |______||_||_| |_||_|\_\|______||_||___/ \__|
//    Link List -- Simple link list algorithms.
//////////

#ifndef __LL_H_
#define __LL_H_




struct SComp;
struct SObject;
struct SVariable;
struct SLine;
struct SExtraInfo;
struct SThisCode;
struct SFunction;
struct SDllFunc;
struct SNoteLog;




/* If the iGetNextUid() function is missing, use this one:
//////////
//
// Get the next Unique ID
//
//////
	u32 gnNextUniqueId = 0;
	u32 iGetNextUid()
	{
		return(gnNextUniqueId++);
	}
*/




//////////
// Forward declarations (some of the functions below call themselves)
//////
	SLL*					iLl_appendNew__ll							(SLL** llRoot, SLL* llHint, SLL* llNext, SLL* llPrev, u32 tnUniqueId, u32 tnSize);
	SLL*					iLl_createOrphan__ll						(                           SLL* llPrev, SLL* llNext, u32 tnUniqueId, u32 tnSize);
	SLL*					iLl_appendNew__llAtEnd						(SLL** llRoot, u32 tnSize, bool tlInitializeNewBlock = true);
	SLL*					iLl_appendNew__llAtBeginning				(SLL** llRoot, u32 tnSize, bool tlInitializeNewBlock = true);
	bool					iLl_appendExisting__llAtEnd					(SLL** llRoot, SLL* ll);
	bool					iLl_appendExisting__llAtBeginning			(SLL** llRoot, SLL* ll);
	SLL*					iLl_delete__ll								(SLL* ll, bool tlDeleteSelf);
	SLL*					iLl_migrate__llToOther						(SLL** llSourceRoot, SLL** llDestinationRoot, SLL* ll, bool tlInsertAtEnd);
	void					iLl_delete__llsWithCallback					(SLLCallback* cb);
	SLL*					iLl_duplicate								(SLL* ll, u32 tnSize, bool tlCopyContent);
	SLL*					iLl_duplicateChain__llWithCallback			(SLL* llSourceRoot, SLLCallback* cb, s32 tnSize);
	bool					iLl_insert__ll								(SLL* ll, SLL* llRef, bool tlAfter);
	void					iLl_orphanize__ll							(SLL* ll);
	void					iLl_delete__llChain							(SLL** llRoot);
	void					iLl_delete__llChainWithCallback				(SLLCallback* cb);
	void					iLl_iterateViaCallback						(SLLCallback* cb);
	void					iLl_iterateBackwardViaCallback				(SLLCallback* cb);
	SLL*					iLl_getFirst__ll							(SLL* ll);
	SLL*					iLl_getLast__ll								(SLL* ll);
	u32						iLl_count__llsToEnd							(SLL* ll);

#endif // __LL_H_

