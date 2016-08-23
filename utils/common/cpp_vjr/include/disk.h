//////////
//
// /libsf/utils/common/cpp/disk.h
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
// Copyright (c) 2014-2015 by Rick C. Hodgin
//////
// Last update:
//	   Mar.05.2015 - Initial creation
//////
// Change log:
//	   Mar.05.2015 - Initial creation
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
//   _____   _       _
//  |  __ \ (_)     | |
//  | |  | | _  ___ | | __
//  | |  | || |/ __|| |/ /
//  | |__| || |\__ \|   <
//  |_____/ |_||___/|_|\_\
//     Disk Algorithms.
//////////




//#pragma once
#ifndef __DISK_H__
#define __DISK_H__



//////////
// The SDisk structure.
//////
	// Note:  For each SBuilder in use for the function calls below, there needs
	//        to be external semaphore locking.
	struct SDiskLock
	{
		bool		isValid;				// Is this lock currently valid (is it an active lock)?

		s32			nFile;					// File handle
		s64			nOffset;				// Offset for start of lock
		s32			nLength;				// Length of lock

		// user-defined extra data associated with this lock
		uptr		extra1;
		uptr		extra2;
		uptr		extra3;
		uptr		extra4;
	};

	struct SDiskLockCallback
	{
		SDiskLock*	dl;
		uptr		extra;


		//////////
		// For the unlock callback
		//////
			union {
				uptr	_diskUnlockCallback;
				bool	(*diskUnlockCallback)(SDiskLockCallback* dcb);
			};


		//////////
		// For the retry callback
		//////
			SYSTEMTIME	timeStart;
			SYSTEMTIME	timeNow;
			union {
				uptr	_diskRetryLockCallback;
				// Note:  There is no delay involved in the retry process, so the callback should issue a Sleep() before retrying, probably a Sleep(100)
				bool	(*diskRetryLockCallback)(SDiskLockCallback* dcb, s32 tnAttempts, s32 tnMillisecondsSpentThusFar);
			};
	};




//////////
// Forward declarations
//////
	s32				iDisk_open								(cs8* tcPathname, s32 tnType, s32 tnShare, bool tlCreateIfCannotOpen);
	s32				iDisk_openAs							(cs8* tcPathname, s32 tnType, bool tlCreateIfCannotOpen, bool tlExclusive);
	s32				iDisk_openShared						(cs8* tcPathname, s32 tnType, bool tlCreateIfCannotOpen);
	s32				iDisk_openExclusive						(cs8* tcPathname, s32 tnType, bool tlCreateIfCannotOpen);
	s32				iDisk_close								(s32 tnFile);
	s64				iDisk_getFileSize						(s32 tnFile);
	s64				iDisk_getFilePosition					(s32 tnFile);
	s64				iDisk_setFilePosition					(s32 tnFile, s64 tnSeekOffset);
	s32				iDisk_read								(s32 tnFile, s64 tnSeekOffset, void* tcData, s32 tnReadCount,  bool* tlError, u32* tnErrorNum);
	s32				iDisk_write								(s32 tnFile, s64 tnSeekOffset, void* tcData, s32 tnWriteCount, bool* tlError, u32* tnErrorNum);
	s32				iDisk_readShared_withRetryCallback		(SBuilder* lockRoot, s32 tnFile, s64 tnSeekOffset, void* tcData, s32 tnReadCount,  bool* tlError, u32* tnErrorNum, uptr tnCallbackFunction, uptr tnExtra, SDiskLock** diskLock, bool tlUnlockAfter);
	s32				iDisk_writeShared_withRetryCallback		(SBuilder* lockRoot, s32 tnFile, s64 tnSeekOffset, void* tcData, s32 tnWriteCount, bool* tlError, u32* tnErrorNum, uptr tnCallbackFunction, uptr tnExtra, SDiskLock** diskLock, bool tlUnlockAfter);
	s32				iiDisk_rwShared_withRetryCallback_common(SBuilder* lockRoot, s32 tnFile, s64 tnSeekOffset, void* tcData, s32 tnCount, bool* tlError, u32* tnErrorNum, uptr tnCallbackFunction, uptr tnExtra, SDiskLock** diskLock, bool tlUnlockAfter, u32 tnErrorNumIfError, bool tlRead);
	s32				iDisk_duplicateFileHandle				(s32 tnFile);


//////////
// Locking
// BEGIN
//////
	// Standard instance validation
	SDiskLock*		iDisk_lock_range_retryCallback			(SBuilder* lockRoot, s32 tnFile, s64 tnOffset, s32 tnLength, uptr tnCallbackFunction, uptr tnExtra = 0);
	SDiskLock*		iDisk_lock_range						(SBuilder* lockRoot, s32 tnFile, s64 tnOffset, s32 tnLength, uptr tnExtra = 0);
	bool			iDisk_unlock							(SBuilder* lockRoot, SDiskLock* dl);
	void			iDisk_unlock_all						(SBuilder* lockRoot);
	s32				iDisk_unlock_all_byCallback				(SBuilder* lockRoot, uptr tnCallbackFunction, uptr tnExtra);

	// Faster functions with no validation
	SDiskLock*		iiDisk_lock_range						(SBuilder* lockRoot, s32 tnFile, s64 tnOffset, s32 tnLength, uptr tnExtra);
	bool			iiDisk_unlock							(SBuilder* lockRoot, SDiskLock* dl);
	void			iiDisk_unlock_all						(SBuilder* lockRoot);
	s32				iiDisk_unlock_all_byCallback			(SBuilder* lockRoot, uptr tnCallbackFunction, uptr tnExtra);

	// Support functions
	bool			iiDisk_isValidLockHandle				(SBuilder* buffRoot, SDiskLock* dl);
//////
// END
//////////


	// File functions
	bool			iFile_readContents						(s8* tcFilename, FILE** tfh, s8** data, u32* dataLength);
	bool			iFile_get_justfname						(s8* tcPathname, s32 tnFilenameLength, s8** tcFname, s32* tnFnameLength);
	s32				iFile_parseIntoLines					(SLine** firstLine, s8* data, u32 dataLength);

#endif	// __DISK_H__
