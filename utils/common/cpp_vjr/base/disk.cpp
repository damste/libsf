//////////
//
// /libsf/utils/common/cpp/disk.cpp
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




//////////
//
// Called to open the file using custom share settings, or explicitly shared,
// or explicitly exclusive.
//
//	tnType		-- 
//
//////
	s32 iDisk_open(cs8* tcPathname, s32 tnType, s32 tnShare, bool tlCreateIfCannotOpen)
	{
		s32	lnFh;


		//////////
		// Attempt to open if valid
		//////
			if (tcPathname)
			{
				// Try to open existing
				lnFh = _sopen(tcPathname, tnType, tnShare);
				if (lnFh == -1)
				{
					// Error opening
					switch (errno)
					{
						default:
						case EACCES:	// The path is a directory, or the file is read-only, but an "open-for-write" was specified
						case EEXIST:	// _O_CREAT and _O_EXCL flags were specified, but filename already exists
						case EINVAL:	// Invalid type or share argument
						case EMFILE:	// No more file descriptors are available
							// All valid errors, indicate failure
							break;

						case ENOENT:
							// File or path was not found
							if (tlCreateIfCannotOpen)
							{
								// Try to create
								lnFh = _creat(tcPathname, _S_IREAD | _S_IWRITE);
								// Right now, it's either open or not
							}
							break;
					}
				}

				// Indicate our (potentially new) status
				return(lnFh);
			}


		//////////
		// If we get here, could not open (or possibly create)
		//////
			return(-1);
	}

	s32 iDisk_openAs(cs8* tcPathname, s32 tnType, bool tlCreateIfCannotOpen, bool tlExclusive)
	{
		if (tlExclusive)	return(iDisk_openExclusive	(tcPathname, tnType, tlCreateIfCannotOpen));
		else				return(iDisk_openShared		(tcPathname, tnType, tlCreateIfCannotOpen));
	}

	s32 iDisk_openShared(cs8* tcPathname, s32 tnType, bool tlCreateIfCannotOpen)
	{
		// Attempt to open if valid
		if (tcPathname)
			return(iDisk_open(tcPathname, tnType, _SH_DENYNO, tlCreateIfCannotOpen));


		// If we get here, invalid filename
		return(-1);
	}

	s32 iDisk_openExclusive(cs8* tcPathname, s32 tnType, bool tlCreateIfCannotOpen)
	{
		// Attempt to open if valid
		if (tcPathname)
			return(iDisk_open(tcPathname, tnType, _SH_DENYRW, tlCreateIfCannotOpen));


		// If we get here, invalid filename
		return(-1);
	}




//////////
//
// Called to close the indicated file handle
//
//////
	s32 iDisk_close(s32 tnFile)
	{
		return(_close(tnFile));
	}




//////////
//
// Obtain the file size
//
//////
	s64 iDisk_getFileSize(s32 tnFile)
	{
		// Note:  Will return -1 if there's an error
		if (tnFile > 0)		return(_filelengthi64(tnFile));
		else				return((s64)tnFile);
	}




//////////
//
// Obtain the current file position
//
//////
	s64 iDisk_getFilePosition(s32 tnFile)
	{
		return(_lseeki64(tnFile, 0, SEEK_CUR));
	}




//////////
//
// Called to set the file position to the indicated offset
//
//////
	s64 iDisk_setFilePosition(s32 tnFile, s64 tnSeekOffset)
	{
		return(_lseeki64(tnFile, tnSeekOffset, SEEK_SET));
	}




//////////
//
// Called to optionally seek, then read in the indicated size.
// If no seek is required, send a negative value for tnSeekOffset.
//
//////
	s32 iDisk_read(s32 tnFile, s64 tnSeekOffset, void* tcData, s32 tnReadCount, bool* tlError, u32* tnErrorNum)
	{
		s64 lnSeekOffset;


		//////////
		// Lower the error flag
		//////
			if (tlError)		*tlError	= false;
			if (tnErrorNum)		*tnErrorNum	= _ERROR_OKAY;


		//////////
		// Optionally seek
		//////
			if (tnSeekOffset >= 0)
			{

				//////////
				// Seek
				//////
					lnSeekOffset = _lseeki64(tnFile, tnSeekOffset, SEEK_SET);


				//////////
				// Are we there?
				//////
					if (lnSeekOffset != tnSeekOffset)
					{
						if (tlError)		*tlError	= true;
						if (tnErrorNum)		*tnErrorNum	= _ERROR_DISK_SEEK_ERROR;
						return(_ERROR_DISK_SEEK_ERROR);
					}

			}


		//////////
		// Read
		//////
			return(_read(tnFile, tcData, tnReadCount));

	}




//////////
//
// Called to optionally seek, then write out the indicated size.
// If no seek is required, send a negative value for tnSeekOffset.
//
//////
	s32 iDisk_write(s32 tnFile, s64 tnSeekOffset, void* tcData, s32 tnWriteCount, bool* tlError, u32* tnErrorNum)
	{
		s64 lnSeekOffset;


		//////////
		// Lower the error flag
		//////
			if (tlError)		*tlError	= false;
			if (tnErrorNum)		*tnErrorNum	= 0;


		//////////
		// Optionally seek
		//////
			if (tnSeekOffset >= 0)
			{

				//////////
				// Seek
				//////
					lnSeekOffset = _lseeki64(tnFile, tnSeekOffset, SEEK_SET);


				//////////
				// Are we there?
				//////
					if (lnSeekOffset != tnSeekOffset)
					{
						if (tlError)		*tlError	= true;
						if (tnErrorNum)		*tnErrorNum	= _ERROR_DISK_SEEK_ERROR;
						return(_ERROR_DISK_SEEK_ERROR);
					}

			}


		//////////
		// Read
		//////
			return(_write(tnFile, tcData, tnWriteCount));

	}




//////////
//
// Called to lock, read, and optionally unlock a file with retry callback
//
//////
	s32 iDisk_readShared_withRetryCallback(SBuilder* lockRoot, s32 tnFile, s64 tnSeekOffset, void* tcData, s32 tnReadCount,  bool* tlError, u32* tnErrorNum, uptr tnCallbackFunction, uptr tnExtra, SDiskLock** diskLock, bool tlUnlockAfter)
	{
		return(iiDisk_rwShared_withRetryCallback_common(lockRoot, tnFile, tnSeekOffset, tcData, tnReadCount, tlError, tnErrorNum, tnCallbackFunction, tnExtra, diskLock, tlUnlockAfter, _ERROR_UNABLE_TO_LOCK_FOR_READ, true));
	}




//////////
//
// Called to lock, write, and optionally unlock a file with retry callback
//
//////
	s32 iDisk_writeShared_withRetryCallback(SBuilder* lockRoot, s32 tnFile, s64 tnSeekOffset, void* tcData, s32 tnWriteCount, bool* tlError, u32* tnErrorNum, uptr tnCallbackFunction, uptr tnExtra, SDiskLock** diskLock, bool tlUnlockAfter)
	{
		return(iiDisk_rwShared_withRetryCallback_common(lockRoot, tnFile, tnSeekOffset, tcData, tnWriteCount, tlError, tnErrorNum, tnCallbackFunction, tnExtra, diskLock, tlUnlockAfter, _ERROR_UNABLE_TO_LOCK_FOR_WRITE, false));
	}




//////////
//
// Common operation for iDisk_readShared_withRetryCallback() and iDisk_writeShared_withRetryCallback()
//
//////
	s32 iiDisk_rwShared_withRetryCallback_common(SBuilder* lockRoot, s32 tnFile, s64 tnSeekOffset, void* tcData, s32 tnCount, bool* tlError, u32* tnErrorNum, uptr tnCallbackFunction, uptr tnExtra, SDiskLock** diskLock, bool tlUnlockAfter, u32 tnErrorNumIfError, bool tlRead)
	{
		s32			lnNum;
		SDiskLock*	dl;


		//////////
		// Initialize
		//////
			if (tlError)		*tlError	= false;
			if (tnErrorNum)		*tnErrorNum	= _ERROR_OKAY;


		//////////
		// Lock
		//////
			dl = iDisk_lock_range_retryCallback(lockRoot, tnFile, tnSeekOffset, tnCount, tnCallbackFunction, tnExtra);
			if (!dl)
			{
				// Error locking
				if (tlError)		*tlError = true;
				if (tnErrorNum)		*tnErrorNum = tnErrorNumIfError;

				// Indicate failure
				return(-1);
			}


		//////////
		// Read/write
		//////
			if (tlRead)		lnNum = iDisk_read (tnFile, -1, tcData, tnCount, tlError, tnErrorNum);
			else			lnNum = iDisk_write(tnFile, -1, tcData, tnCount, tlError, tnErrorNum);
			// Right now, lnNum and error are our keys ... if lnNum == tnCount and !error, it was a success


		//////////
		// Unlock
		//////
			if (tlUnlockAfter)
			{
				// Unlocking
				if (diskLock)
					*diskLock = NULL;

				// Unlock
				iDisk_unlock(lockRoot, dl);

			} else {
				// Not unlocking, signal the disk lock
				if (diskLock)
					*diskLock = dl;
			}


		//////////
		// Indicate the number written
		//////
			return(lnNum);
	}




//////////
//
// Called to duplicate the indicated file handle (if possible).
//
//////
	s32 iDisk_duplicateFileHandle(s32 tnFile)
	{
		// The OS will return a duplicate handle, or -1
		return(_dup(tnFile));
	}




//////////
//
// Called to potentially retry so long as the callback returns true.
//
//////
	SDiskLock* iDisk_lock_range_retryCallback(SBuilder* lockRoot, s32 tnFile, s64 tnOffset, s32 tnLength, uptr tnCallbackFunction, uptr tnExtra)
	{
		s32					lnAttempts, lnMillisecondsDelta;
		s64					lnMillisecondsStart;
		SDiskLock*			dl;
		SDiskLockCallback	dcb;


		//////////
		// Initialize
		//////
			memset(&dcb, 0, sizeof(dcb));
			dcb._diskRetryLockCallback	= tnCallbackFunction;
			dcb.extra					= tnExtra;
			lnAttempts = 0;


		//////////
		// Begin the trial
		//////
			GetLocalTime(&dcb.timeStart);
			lnMillisecondsStart = iTime_computeMilliseconds(&dcb.timeStart);
			while (1)
			{

				//////////
				// Try to lock
				//////
					++lnAttempts;
					dl = iDisk_lock_range(lockRoot, tnFile, tnOffset, tnLength, tnExtra);


				//////////
				// Were we successful?
				//////
					if (dl && dl->nLength == tnLength)
						return(dl);	// Yes


				//////////
				// When we get here, we need to see if they want to continue waiting or not
				//////
					GetLocalTime(&dcb.timeNow);
					lnMillisecondsDelta = (s32)iTime_computeMillisecondsBetween(&dcb.timeNow, lnMillisecondsStart);


				//////////
				// Inquire politely about our retry
				//////
					if (!dcb._diskRetryLockCallback || !dcb.diskRetryLockCallback(&dcb, lnAttempts, lnMillisecondsDelta))
					{
						// They inform us:  "No more waiting!"
						return(dl);	// Failure
					}
					// If we get here, try again

			}
	}




//////////
//
// Called to lock a disk range, and append the information to the buffer.
//
// Note:  It returns a pointer to the SDisk entry that was just added, however
//        it should not generally be modified directly, but only used as a handle.
//
// Note:  Examine success with this test:
//
//				SDiskLock* dl;
//				dl = iDisk_lock_range(..., lnLength...);
//				if (dl && dl->nLength == lnLength)
//				{
//				    // Success
//				} else {
//				    // Failure
//				}
//
// Note:  If success, upon exit, the file will be positioned at the locking address.
//
// Note:  If not success, it may be positioned at the locking address depending on
//                        when the error occurred.
//
//////
	SDiskLock* iDisk_lock_range(SBuilder* lockRoot, s32 tnFile, s64 tnOffset, s32 tnLength, uptr tnExtra)
	{
		// Make sure our environment is sane
		if (lockRoot && lockRoot->buffer && lockRoot->populatedLength % sizeof(SDiskLock) == 0)
		{
			// Lock it
			return(iiDisk_lock_range(lockRoot, tnFile, tnOffset, tnLength, tnExtra));

		} else {
			// Indicate error
			return(NULL);
		}
	}

	SDiskLock* iiDisk_lock_range(SBuilder* lockRoot, s32 tnFile, s64 tnOffset, s32 tnLength, uptr tnExtra)
	{
		u32			lnI;
		SDiskLock*	dl;


		//////////
		// Iterate to find an empty slot
		//////
			for (lnI = 0, dl = (SDiskLock*)lockRoot->buffer; lnI < lockRoot->populatedLength; lnI += sizeof(SDiskLock), dl++)
			{
				// Is this slot empty?
				if (!dl->isValid)
					break;	// Yes
			}


		//////////
		// When we get here, we have a slot or not
		//////
			if (lnI >= lockRoot->populatedLength)
			{
				// Create a new one
				dl = (SDiskLock*)iBuilder_appendData(lockRoot, (cs8*)NULL, sizeof(SDiskLock));
				// Note:  disk members are all initialized to 0s
			}


		//////////
		// Physically try the lock
		//////
			dl->isValid = true;
			dl->nFile	= tnFile;
			dl->nOffset	= tnOffset;
			dl->nLength	= 0;

			// Seek to the offset
			if (_lseeki64(tnFile, tnOffset, SEEK_SET) == tnOffset)
			{
				// Lock the bytes
				if (_locking(tnFile, _LK_NBLCK, tnLength) == 0)		// Note:  _LK_NBLCK attempts to lock, and if fails returns immediately, whereas _LK_LOCK would auto-retry after 1 second, and fail after 10 seconds
				{
					// Indicate a successful lock
					dl->nLength = tnLength;
				}

			} else {
				// The length being 0 will indicate the lock failed
				// So we just let it fall through
			}


		//////////
		// Indicate success or failure
		//////
			return(dl);
	}




//////////
//
// Called to unlock a previously locked disk range using iDisk_lock().
//
// Note:  After unlocking, the slot in the original buffRoot is freed, available for re-use.
//
//////
	bool iDisk_unlock(SBuilder* lockRoot, SDiskLock* dl)
	{
		// Make sure our environment is sane
		if (iiDisk_isValidLockHandle(lockRoot, dl))
		{
			// Unlock it
			return(iiDisk_unlock(lockRoot, dl));
		}

		// If we get here, failure
		return(false);
	}

	bool iiDisk_unlock(SBuilder* lockRoot, SDiskLock* dl)
	{
		bool llResult;


		// If it's a valid lock, unlock it
		llResult = false;
		if (dl->isValid)
		{
			// Seek
			if (_lseeki64(dl->nFile, dl->nOffset, SEEK_SET) == dl->nOffset)
			{
				// Unlock
				llResult = (_locking(dl->nFile, _LK_UNLCK, dl->nLength) == 0);

			} else {
				// If we get here, the file is likely no longer open, so all locks are closed
				// But, we just silently fall through
			}

			// If cleared, indicate the lock is no longer valid
			dl->isValid = !llResult;
		}

		// Indicate success or failure
		return(llResult);
	}




//////////
//
// Called to unlock everything contained within the buffer.
//
// Note:  After use, all locks created by iDisk_lock() will be released, and every
//        slot in the buffRoot buffer is available for re-use.
//
//////
	void iDisk_unlock_all(SBuilder* lockRoot)
	{
		// Make sure our environment is sane
		if (lockRoot && lockRoot->buffer && lockRoot->populatedLength % sizeof(SDiskLock) == 0)
		{
			// Unlock it
			iiDisk_unlock_all(lockRoot);
		}
	}

	void iiDisk_unlock_all(SBuilder* lockRoot)
	{
		u32			lnI;
		SDiskLock*	dl;


		// If it's a valid lock, unlock it
		for (lnI = 0, dl = (SDiskLock*)lockRoot->buffer; lnI < lockRoot->populatedLength; lnI += sizeof(SDiskLock), dl++)
		{
			// Is this one locked?
			if (dl->isValid)
			{
				// Seek
				if (_lseeki64(dl->nFile, dl->nOffset, SEEK_SET) == dl->nOffset)
				{
					// Unlock
					_locking(dl->nFile, _LK_UNLCK, dl->nLength);

				} else {
					// If we get here, the file is likely no longer open, so all locks are closed
					// But, we just silently fall through
				}

				// Indicate the lock is no longer valid
				dl->isValid = false;
			}
		}
	}




//////////
//
// Called to unlock a disk range by using a callback test to determine if the
// unlock should be performed on a case-by-case basis.
//
// Note:  Only those entries which are indicated are released.  The rest remain
//        locked unless they are manually unlocked.
//
//////
	s32 iDisk_unlock_all_byCallback(SBuilder* lockRoot, uptr tnFunction, uptr tnExtra)
	{
		// Make sure our environment is sane
		if (lockRoot && lockRoot->buffer && lockRoot->populatedLength % sizeof(SDiskLock) == 0)
		{
			// Unlock it
			return(iiDisk_unlock_all_byCallback(lockRoot, tnFunction, tnExtra));

		} else {
			// Something's awry, if we have a valid buffRoot, then indicate 0 records were unlocked
			return(-1);
		}
	}

	s32 iiDisk_unlock_all_byCallback(SBuilder* lockRoot, uptr tnFunction, uptr tnExtra)
	{
		u32					lnI, lnUnlockedCount;
		SDiskLock*			dl;
		SDiskLockCallback	dcb;


		// Initialize
		memset(&dcb, 0, sizeof(dcb));
		dcb._diskUnlockCallback	= tnFunction;
		dcb.extra				= tnExtra;

		// If it's a valid lock, unlock it
		for (lnI = 0, lnUnlockedCount = 0, dl = (SDiskLock*)lockRoot->buffer; lnI < lockRoot->populatedLength; lnI += sizeof(SDiskLock), dl++)
		{
			// Is this one locked?  And do they want to release it?
			if (dl->isValid && (!dcb._diskUnlockCallback || !dcb.diskUnlockCallback(&dcb)))
			{
				// Seek
				if (_lseeki64(dl->nFile, dl->nOffset, SEEK_SET) == dl->nOffset)
				{
					// Unlock
					_locking(dl->nFile, _LK_UNLCK, dl->nLength);
					++lnUnlockedCount;

				} else {
					// If we get here, the file is likely no longer open, so all locks are closed
					// But, we just silently fall through
				}

				// Indicate the lock is no longer valid
				dl->isValid = false;
			}
		}

		// Indicate our count
		return(lnUnlockedCount);
	}




//////////
//
// Check the handle to make sure it's valid
//
//////
	bool iiDisk_isValidLockHandle(SBuilder* lockRoot, SDiskLock* dl)
	{
		//////////
		// Verify the handle is valid
		//////
			if (dl && iBuilder_isPointer(lockRoot, (uptr)dl))
			{
				// It's in range, but the valid condition depends upon its property
				return(dl->isValid);

			} else {
				// Indicate failure
				return(false);
			}
	}




//////////
//
// Called to read the contents of the indicated file
//
//////
	bool iFile_readContents(s8* tcFilename, FILE** tfh, s8** data, u32* dataLength)
	{
		u32		lnNumread;
		FILE*	lfh;


		// Make sure our environment is sane
		if (tcFilename && data && dataLength)
		{
			// Try to open the file
			lfh = fopen(tcFilename, "rb+");
			if (lfh)
			{
				// Find out how big it is
				fseek(lfh, 0, SEEK_END);
				*dataLength = ftell(lfh);
				fseek(lfh, 0, SEEK_SET);

				// Allocate a buffer that large
				*data = (s8*)malloc(*dataLength);
				if (*data)
				{
					// Read the contents
					lnNumread = (u32)fread(*data, 1, *dataLength, lfh);
					if (lnNumread == *dataLength)
					{
						// We read everything
						if (tfh)
						{
							// Save the file handle, return it open
							*tfh = lfh;

						} else {
							// Close the file handle
							fclose(lfh);
						}

						// Indicate success
						return(true);
					}

				} else {
					// Error allocating that much memory
					fclose(lfh);
				}
			}
		}
		// If we get here, failure
		return(false);
	}




//////////
//
// Search backwards for the start of the string, or the first \ found
//
//////
	bool iFile_get_justfname(s8* tcPathname, s32 tnFilenameLength, s8** tcFname, s32* tnFnameLength)
	{
		s32 lnI, lnLength;


		// Make sure our environment is sane
		if (tcPathname && tcFname && tnFnameLength && tnFnameLength)
		{
			// Scan backwards
			for (lnI = tnFilenameLength - 1, lnLength = 1; lnI > 0; lnI--, lnLength++)
			{
				// Have we reached the \ ?
				if (tcPathname[lnI] == '\\')
					break;
			}

			// Indicate our pointer and length
			*tcFname		= tcPathname + lnI;
			*tnFnameLength	= lnLength;

			// Indicate success
			return(true);
		}

		// If we get here, failure
		return(false);
	}




//////////
//
// Called to parse a raw file into lines
//
//////
	// Returns line count
	s32 iFile_parseIntoLines(SLine** firstLine, s8* data, u32 dataLength)
	{
		u32			lnI, lnJ, lnLast, lnLineNumber;
		SLine*		line;
		SLine**		lastLine;


		// Copy through lines into the SLine struct
		for (lnI = 0, lnLast = 0, lastLine = firstLine, lnLineNumber = 1; lnI < dataLength; )
		{

			//////////
			// Are we on a CR/LF combination?
			//////
				for (lnJ = 0; (data[lnI] == 13 || data[lnI] == 10) && lnJ < 2 && (u32)lnI < dataLength; lnJ++)
					++lnI;	// Increase also past this CR/LF character


			//////////
			// If we found a CR/LF combination
			//////
				if (lnJ != 0 || lnI >= dataLength)
				{

					//////////
					// Increase our line count
					//////
						++lnLineNumber;


					//////////
					// We've entered into a CR/LF block, append a new line
					//////
						line = (SLine*)iLl_appendNew__llAtEnd((SLL**)lastLine, sizeof(SLine));
						if (!line)
							return(-1);		// Unexpected failure


					//////////
					// Indicate content
					//////
						line->sourceCode	= iDatum_allocate((u8*)data + lnLast, (s32)(lnI - lnJ - lnLast));
						line->lineNumber	= lnLineNumber;


					//////////
					// Indicate where we are now
					//////
						lnLast		= lnI;
						lastLine	= &line;

				} else {
					// Still going
					++lnI;
				}
				// Continue on processing the next line if we have room

		}

		// Indicate how many lines
		return(lnLineNumber);
	}
