//////////
//
// /libsf/utils/common/cpp/fifo.h
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
//     Dec.28.2015
//////
// Change log:
//     Dec.28.2015 - Initial creation
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
// 	  ______  _____  ______  ____  
// 	 |  ____||_   _||  ____|/ __ \ 
// 	 | |__     | |  | |__  | |  | |
// 	 |  __|    | |  |  __| | |  | |
// 	 | |      _| |_ | |    | |__| |
// 	 |_|     |_____||_|     \____/
// FIFO -- First In, First Out storage
//////////

#ifndef __FIFO_H_
#define __FIFO_H_

struct SBuilder;

SBuilder*		gsRootFifo			= NULL;

struct SFIFO
{
	bool		isReference;
	SDatum		datum;
};


//////////
// Prototype definitions
//////
	SFIFO*		iFifo_push				(SDatum* datum, bool tlMakeReference = true);
	s32			iFifo_peek				(SDatum& datum, bool& tlIsReference);
	s32			iFifo_pop				(SDatum& datum, bool& tlIsReference);


#endif
