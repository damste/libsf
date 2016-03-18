//////////
//
// /libsf/utils/common/cpp/include/callbacks.h
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
//     Mar.17.2016
//////
// Change log:
//     Mar.17.2016	- Initial creation
//////
//
// This file is self-contained and handles all builder algorithms.  It can be used as an include
// file for other stand-alone projects.  It was extracted from the Visual FreePro Virtual Machine.
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




//#pragma once
#ifndef __CALLBACKS_H__
#define __CALLBACKS_H__

struct SLine;
struct SComp;

// Generic callback support
struct SCallback
{

	//////////
	// Callback function
	//////
		union {
			uptr	_func;
			bool	(*func)		(SCallback* cb);
		};


	//////////
	// Various data items available
	//////
		union {
			SLine*	line;
			SComp*	comp;
			void*	data1;
			SLine*	line1;
			SComp*	comp1;
		};

		union {
			void*	data2;
			SLine*	line2;
			SComp*	comp2;
		};


	//////////
	// Extra information
	//////
		bool		flag;
		void*		x;

};

#endif		// __CALLBACKS_H__
