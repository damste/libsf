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
// Copyright (c) 2014 by Rick C. Hodgin
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




//////////
//
// Callback structure for SLL iteration
//
//////
	struct SLL
	{
		union {
			SLL*		next;					// Next entry in linked list
			SComp*		nextComp;
			SLine*		nextLine;
			SObject*	nextObj;
			SVariable*	nextVar;
			SThisCode*	nextThisCode;
			SExtraInfo*	nextExtraInfo;
			SFunction*	nextFunc;
			SDllFunc*	nextDllFunc;
			SNoteLog*	nextNoteLog;
		};
		union {
			SLL*		prev;					// Previous entry in linked list
			SComp*		prevComp;
			SLine*		prevLine;
			SObject*	prevObj;
			SVariable*	prevVar;
			SThisCode*	prevThisCode;
			SExtraInfo*	prevExtraInfo;
			SFunction*	prevFunc;
			SDllFunc*	prevDllFunc;
			SNoteLog*	prevNoteLog;
		};
		u32				uniqueId;				// Unique id associated with this object
	};

	struct SLLCallback
	{
		union
		{
			uptr	_func;
			bool	(*funcBool)	(SLLCallback* cb);
			void	(*funcVoid)	(SLLCallback* cb);
			//////
			// Uses the following format for the callback:
			//		void func(SLLCallback* cb)
			//		bool func(SLLCallback* cb)
			//////////
		};

		// For runtime
		SThisCode*	thisCode;

		// Data items for this callback
		SLL*	node;
		union {
			uptr	extra;
			uptr	extra1;
		};
		u32		extra2;
	};




//////////
// Forward declarations (some of the functions below call themselves)
//////
	SLL*					iLl_appendNewNode							(SLL** root, SLL* nodeHint, SLL* nodeNext, SLL* nodePrev, u32 tnUniqueId, u32 tnSize);
	SLL*					iLl_createOrphanNode						(                           SLL* nodePrev, SLL* nodeNext, u32 tnUniqueId, u32 tnSize);
	SLL*					iLl_appendNewNodeAtEnd						(SLL** root, u32 tnSize);
	SLL*					iLl_appendNewNodeAtBeginning				(SLL** root, u32 tnSize);
	bool					iLl_appendExistingNodeAtEnd					(SLL** root, SLL* node);
	bool					iLl_appendExistingNodeAtBeginning			(SLL** root, SLL* node);
	SLL*					iLl_deleteNode								(SLL* node, bool tlDeleteSelf);
	SLL*					iLl_migrateNodeToOther						(SLL** nodeSourceRoot, SLL** nodeDestinationRoot, SLL* node, bool tlInsertAtEnd);
	void					iLl_deleteNodesWithCallback					(SLLCallback* cb);
	bool					iLl_insertNode								(SLL* node, SLL* nodeRef, bool tlAfter);
	void					iLl_orphanizeNode							(SLL* node);
	void					iLl_deleteNodeChain							(SLL** root);
	void					iLl_deleteNodeChainWithCallback				(SLLCallback* cb);
	void					iLl_iterateViaCallback						(SLLCallback* cb);
	void					iLl_iterateBackwardViaCallback				(SLLCallback* cb);
	SLL*					iLl_getFirstNode							(SLL* node);
	SLL*					iLl_getLastNode								(SLL* node);
	u32						iLl_countNodesToEnd							(SLL* node);

#endif // __LL_H_

