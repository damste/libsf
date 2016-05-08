//////////
//
// /libsf/utils/common/cpp/include/uniqueid.h
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
// Version 0.60
// Copyright (c) 2016 by Rick C. Hodgin
//////
// Last update:
//     May.07.2016
//////
// Change log:
//     May.07.2016	- Initial creation
//////
//
// This file is self-contained and handles all scaling algorithms.  It can be used as an include
// file for other stand-alone projects.  It was extracted from offline code related to the
// Village Freedom Project.
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




// Get the next Unique ID
CRITICAL_SECTION	cs_uniqueIdAccess;
bool				gl_cs_uniqueIdAccess_initialized	= false;
u32					gnNextUniqueId						= 0;

void initializeUid(void)
{
	// Make sure we've initialized our synchronous access
	if (!gl_cs_uniqueIdAccess_initialized)
	{
		InitializeCriticalSection(&cs_uniqueIdAccess);
		gl_cs_uniqueIdAccess_initialized = true;
	}
}

u32 iGetNextUid(void)
{
	u32 lnValue;

	// Synchronized access
	EnterCriticalSection(&cs_uniqueIdAccess);

	// Get our value and increment
	lnValue = gnNextUniqueId++;

	// All done
	LeaveCriticalSection(&cs_uniqueIdAccess);

	// Return that value
	return(lnValue);
}
