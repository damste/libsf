//////////
//
// /libsf/utils/common/cpp/include/compsearcher.h
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
//     Jun.22.2016
//////
// Change log:
//     Mar.17.2016	- Initial creation
//     Jun.22.2016  - Significant refactoring
//////
//
// This file is handles all file/line/comp related algorithms.
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




#ifndef __COMPSEARCHER_H__
#define __COMPSEARCHER_H__


struct SEM;
struct SLine;
struct SExtraInfo;


//////////
// For the lower 64K values of flag-mapped comp->iCat codes
//////
	#define iCat(x)									(x & 0xffff)
	#define iCatBits(x)								(x & _ICAT_MASK);


//////////
// Forward declaration
//////
	// Compiler functions
	SCompiler*				iCompiler_allocate							(SLine* parent);
	void					iCompiler_delete							(SCompiler** compilerInfoRoot, bool tlDeleteSelf);

	// Compile note functions
	SNoteLog*				iNoteLog_create								(SNoteLog** noteRoot, SLine* line, u32 tnStart, u32 tnEnd, u32 tnNumber, cu8* tcMessage);
	SNoteLog*				iNoteLog_create								(SNoteLog** noteRoot, SComp* comp, u32 tnNumber, cu8* tcMessage);
	void					iNoteLog_removeAll							(SNoteLog** noteRoot);

#endif 	// __COMPSEARCHER_H__
