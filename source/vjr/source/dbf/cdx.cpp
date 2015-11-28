//////////
//
// /libsf/source/vjr/source/dbf/cdx.cpp
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
// Version 0.58
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
/////
//
//  Functions:
//
// 		cdx_open()
//		cdx_close()
// 		cdx_get_tag()
// 		cdx_validate_tag()
//		cdx_validate_keys()
//		cdx_get_all_keys()
//
//









//////////
//
// Called to open the indicated CDX associated with the table, or an explicitly named index
// (which can be either a .CDX or .IDX file, but not both LOL!).
//
//////
// Parameters:
//		wa					-- Work area
//		tcCdxFilename		-- IDX/CDX filename
//		tnCdxFilenameLength	-- Length of the filename
//		tnExplicitIndexType	--
//
//////
	u32 cdx_open(SWorkArea* wa, s8* tcCdxFilename, u32 tnCdxFilenameLength, u32 tnExplicitIndexType, bool tlValidate, bool tlDescending)
	{
		bool		llIsValid;
		u64			lnFileSize, lnNumread;
		SDiskLock*	dl;
		bool		error;
		u32			errorNum;


		//////////
		// Validate that our environment is sane
		//////
			if (!iDbf_isWorkAreaUsed(wa, &llIsValid) || !llIsValid)
				return(_CDX_ERROR_INVALID_WORK_AREA);		// Invalid work area
			if (tnCdxFilenameLength >= sizeof(wa->idxCdxDcxPathname))
				return(_CDX_ERROR_INDEX_NAME_TOO_LONG);


		//////////
		// If an index is already open, close it
		//////
			cdx_close(wa);


		//////////
		// If they specified a CDX name, use that, otherwise build the default one from the open filename path altered to the .cdx extension
		//////
			if (tcCdxFilename && tnCdxFilenameLength != 0)
			{
				// They specified a name
				tnCdxFilenameLength = min(tnCdxFilenameLength, sizeof(wa->idxCdxDcxPathname) - 1);
				memcpy(wa->idxCdxDcxPathname, tcCdxFilename, tnCdxFilenameLength);
				wa->idxCdxDcxPathnameLength = tnCdxFilenameLength;

			} else {
				// Build the name from the table name
// TODO:  The name needs to use FORCEEXT() here instead of this hard-code
				memcpy(wa->idxCdxDcxPathname, wa->tablePathname, wa->tablePathnameLength);
				memcpy(wa->idxCdxDcxPathname + wa->tablePathnameLength - 4, ".cdx", 4);
				wa->idxCdxDcxPathnameLength = wa->tablePathnameLength;
			}

			// NULL terminate
			wa->idxCdxDcxPathname[wa->idxCdxDcxPathnameLength] = 0;


		//////////
		// Determine if it was a .cdx or .idx
		//////
			wa->isCdx = false;
			wa->isSdx = false;
			if (tnExplicitIndexType == _INDEX_IDX || (tnExplicitIndexType == _INDEX_NONE && _memicmp(wa->idxCdxDcxPathname + wa->idxCdxDcxPathnameLength - sizeof(cgcIdxExtension) - 1, cgcIdxExtension, sizeof(cgcIdxExtension) - 1) == 0))
			{
				// .idx
				wa->isCdx = false;

			} else if (tnExplicitIndexType == _INDEX_CDX || (tnExplicitIndexType == _INDEX_NONE && _memicmp(wa->idxCdxDcxPathname + wa->idxCdxDcxPathnameLength - sizeof(cgcCdxExtension) - 1, cgcCdxExtension, sizeof(cgcCdxExtension) - 1) == 0)) {
				// .cdx
				wa->isCdx = true;

			} else if (tnExplicitIndexType == _INDEX_SDX || (tnExplicitIndexType == _INDEX_NONE && _memicmp(wa->idxCdxDcxPathname + wa->idxCdxDcxPathnameLength - sizeof(cgcSdxExtension) - 1, cgcSdxExtension, sizeof(cgcSdxExtension) - 1) == 0)) {
				// .sdx
				wa->isSdx = true;

			} else if (tnExplicitIndexType == _INDEX_DCX || (tnExplicitIndexType == _INDEX_NONE && _memicmp(wa->idxCdxDcxPathname + wa->idxCdxDcxPathnameLength - sizeof(cgcDcxExtension) - 1, cgcDcxExtension, sizeof(cgcDcxExtension) - 1) == 0)) {
				// .cdx, albeit in sheep's clothing
				wa->isCdx = true;

			} else {
				// Unknown, report the error
				memset(wa->idxCdxDcxPathname, 0, sizeof(wa->idxCdxDcxPathname));
				return(_CDX_ERROR_UNKNOWN_INDEX_TYPE);
			}


		//////////
		// Make sure we have a lock area
		//////
			if (!wa->idxCdxDcxFileLocks)
				iBuilder_createAndInitialize(&wa->idxCdxDcxFileLocks, -1);


		//////////
		// Open it
		//////
			if (wa->isExclusive)		wa->fhIdxCdxDcx = iDisk_openAs(wa->idxCdxDcxPathname, _O_BINARY | _O_RDWR, false, true/*Exclusive*/);
			else						wa->fhIdxCdxDcx = iDisk_openAs(wa->idxCdxDcxPathname, _O_BINARY | _O_RDWR, false, false/*Shared*/);


		//////////
		// Are we good?
		//////
			if (!wa->fhIdxCdxDcx)
				return(_CDX_ERROR_OPENING_INDEX);


		//////////
		// Find out how big it is
		//////
			lnFileSize = iDisk_getFileSize(wa->fhIdxCdxDcx);


		//////////
		// Allocate one block
		//////
			if (!wa->isCdx)
			{ // IDX

				//////////
				// Allocate
				//////
					wa->idx_header = (SIdxHeader*)malloc(sizeof(wa->idx_header));
					if (!wa->idx_header)
					{
						cdx_close(wa);
						return(_CDX_ERROR_MEMORY_IDX);
					}


				//////////
				// Read the first block
				//////
					if (wa->isExclusive)		lnNumread = iDisk_read(wa->fhIdxCdxDcx, 0, wa->idx_header, sizeof(wa->idx_header), &error, &errorNum);
					else						lnNumread = iDisk_readShared_withRetryCallback(wa->idxCdxDcxFileLocks, wa->fhIdxCdxDcx, 0, wa->idx_header, sizeof(wa->idx_header), &error, &errorNum, (uptr)&iiDbf_continueWithLockOperation, (uptr)&dl, &dl, true);


				//////////
				// Are we good?
				//////
					if (error && errorNum == _ERROR_UNABLE_TO_LOCK_FOR_READ)
					{
						// Adjust the error to make it specific
						cdx_close(wa);
						return(_CDX_ERROR_READING_HEADER_IDX);
					}

					if (error || lnNumread != sizeof(wa->idx_header))
					{
						cdx_close(wa);
						return(_CDX_ERROR_READING_HEADER_CDX);
					}


				//////////
				// See if it's a compact idx
				//////
					wa->isIdxCompact = ((wa->idx_header->options & _BIT_COMPACT_INDEX) != 0);
					if (wa->isIdxCompact)
					{
						// Compact IDX headers need to be stored in the CDX structure
						wa->cdx_root			= (SCdxHeader*)wa->idx_header;
						wa->idx_header			= NULL;
						wa->isIndexLoaded		= true;
						wa->isDescending		= tlDescending;
						wa->cdx_root->fileSize	= (u32)lnFileSize;
					}


			} else {
				// CDX

				//////////
				// Allocate
				/////
					wa->cdx_root = (SCdxHeader*)malloc(sizeof(*wa->cdx_root));
					if (!wa->cdx_root)
					{
						cdx_close(wa);
						return(_CDX_ERROR_MEMORY_CDX);
					}


				//////////
				// Read
				//////
					if (wa->isExclusive)		lnNumread = iDisk_read(wa->fhIdxCdxDcx, 0, wa->cdx_root, sizeof(*wa->cdx_root), &error, &errorNum);
					else						lnNumread = iDisk_readShared_withRetryCallback(wa->idxCdxDcxFileLocks, wa->fhIdxCdxDcx, 0, wa->cdx_root, sizeof(*wa->cdx_root), &error, &errorNum, (uptr)&iiDbf_continueWithLockOperation, (uptr)&dl, &dl, true);


				//////////
				// Are we good?
				//////
					if (error && errorNum == _ERROR_UNABLE_TO_LOCK_FOR_READ)
					{
						cdx_close(wa);
						return(_CDX_ERROR_LOCKING_HEADER_CDX);
					}

					if (error || lnNumread != sizeof(*wa->cdx_root))
					{
						cdx_close(wa);
						return(_CDX_ERROR_READING_HEADER_CDX);
					}


				//////////
				// Indicate it's a compact index, store the file size manually
				//////
					wa->isIdxCompact		= true;		// All CDXs are compact indexes
					wa->isIndexLoaded		= true;
					wa->isDescending		= tlDescending;
					wa->cdx_root->fileSize	= (u32)lnFileSize;


				//////////
				// Auto-validate the index if need be
				//////
					if (tlValidate || propGet_settings_AutoValidate(_settings))
						iCdx_validateCdx(wa, -1, NULL, 0, NULL, 0);	// Will signal ON VALIDATE messages for any errors found
			}


		// If we get here, it's opened and happy
		return(_CDX_OKAY);
	}




//////////
//
// Called to close an open index
//
//////
	u32 cdx_close(SWorkArea* wa)
	{
		s32		lnI;
		bool	llIsValid;


		//////////
		// Validate that our environment is sane
		//////
			if (!iDbf_isWorkAreaUsed(wa, &llIsValid) || !llIsValid)
				return(_DBF_ERROR_INVALID_WORK_AREA);


		//////////
		// Release any and all locks
		//////
			if (wa->idxCdxDcxFileLocks)
				iDisk_unlock_all(wa->idxCdxDcxFileLocks);


		//////////
		// If an index is already open, close it
		//////
			if (wa->isIndexLoaded)
			{
				//////////
				// Close the index file handle
				//////
					if (wa->fhIdxCdxDcx)
					{
						_close(wa->fhIdxCdxDcx);
						wa->fhIdxCdxDcx = null0;
					}


				//////////
				// Free the memory
				//////
					if (wa->isCdx)
					{
						//////////
						// Release the loaded CDX file
						//////
							if (wa->cdx_root)
							{
								free(wa->cdx_root);
								wa->cdx_root = NULL;
							}


						//////////
						// Delete any allocated key find structures
						//////
							for (lnI = 0; lnI < _MAX_CDX_TAGS; lnI++)
							{
								// Clear the FOR clause if need be
								if (wa->cdx_keyOps[lnI].forClause)
									iDbf_forClause_delete(&wa->cdx_keyOps[lnI].forClause);

								// Free key ops
								if (wa->cdx_keyOps[lnI].keyOps)
									iiFreeAndSetToNull((void**)&wa->cdx_keyOps[lnI].keyOps);
							}

					} else {
						//////////
						// Release the loaded IDX file
						//////
							if (wa->idx_header)
							{
								free(wa->idx_header);
								wa->idx_header = NULL;
							}
					}


				//////////
				// Clear out the filename
				//////
					memset(wa->idxCdxDcxPathname, 0, sizeof(wa->idxCdxDcxPathname));
					wa->idxCdxDcxPathnameLength = 0;


				//////////
				// No longer open
				//////
					wa->isIndexLoaded = false;

				// Indicate success
				return(0);
			}

			// If we get here, failure
			return(_CDX_ERROR_NO_INDEX_IN_USE);
	}




//////////
//
// Called to retrieve tag information based on the tag index
//
/////
	u32 cdx_get_tag(SWorkArea* wa,
					u32 tnTagIndex,
					s8* tcTagName,		u32 tnTagNameLength,
					s8* tcExpression,	u32 tnExpressionLength,
					s8* tcForClause,	u32 tnForClauseLength,
					s8* tcKeyLength4,
					s8* tcUnique1, s8* tcCompact1, s8* tcCompound1, s8* tcOrder1)
	{
		u32				lnI, lnJ;
		bool			llIsValid;
		SCdxHeader*		head;
		SCdxNode*		nodeTag;
		s8*				nodePtr;
		s8*				expForPtr;
		STagRoot		tagRoot;


		//////////
		// Validate that our environment is sane
		//////
			if (!iDbf_isWorkAreaUsed(wa, &llIsValid) || !llIsValid)
				return(_DBF_ERROR_INVALID_WORK_AREA);


		//////////
		// Get common pointers
		//////
			head = wa->cdx_root;			// Header is first part of file


		//////////
		// Iterate through the various tags
		//////
			if (iCdx_getRootmostCompoundTag_byTagnum(wa, head, NULL, tnTagIndex, &tagRoot))
			{
				// Copy the tag name
				for (lnI = 0; lnI < tagRoot.keyLength && lnI < tnTagNameLength; lnI++)
					tcTagName[lnI] = tagRoot.tagName[lnI];

				// Put spaces out to the end of the tag name length
				for ( ; lnI < tnTagNameLength; lnI++)
					tcTagName[lnI] = 32;

				// Grab the node with the key information
				nodeTag		= iCdx_getCompactIdxNode_byOffset(head, tagRoot.keyNode);
				nodePtr		= (s8*)nodeTag;
				expForPtr	= nodePtr + 512;

				// Copy the expression
				for (lnI = 0; lnI < tnExpressionLength && lnI < 512 && expForPtr[lnI] != 0; lnI++)
					tcExpression[lnI] = expForPtr[lnI];

				// Put spaces to the end of the expression
				for (lnJ = 0; lnI + lnJ < tnExpressionLength; lnJ++)
					tcExpression[lnI + lnJ] = 32;

				// Copy the for clause (if any)
				if (expForPtr[lnI + 1] != 0)
				{
					for (lnJ = 0, lnI += 1; lnJ < tnForClauseLength && lnI + lnJ < 512 && expForPtr[lnI + lnJ] != 0; lnJ++)
						tcForClause[lnJ] = expForPtr[lnI + lnJ];
				}

				// Store the key length
				sprintf(tcKeyLength4, "%04u", tagRoot.keyLength);

				// Store the flags if need be
				iiTwoChoice(tcCompact1,		iiCdx_isCompact		(head),		cgc_y,	cgc_n);
				iiTwoChoice(tcCompound1,	iiCdx_isCompound	(head),		cgc_y,	cgc_n);
				iiTwoChoice(tcUnique1,		iiCdx_isUnique		(head),		cgc_y,	cgc_n);
				iiTwoChoice(tcOrder1,		iiCdx_isDescending	(head),		cgc_d,	cgc_a);

				// Indicate the length of the key as a success
				return(tagRoot.keyLength);

			} else {
				// The indicated tag number does not exist
				memset(tcExpression, 32, tnExpressionLength);
				memset(tcForClause, 32, tnForClauseLength);
				memset(tcKeyLength4, 32, 4);
				*tcUnique1		= 32;
				*tcCompact1		= 32;
				*tcCompound1	= 32;
				*tcOrder1		= 32;
				return(_CDX_ERROR_NO_INDEX_IN_USE);
			}
	}




//////////
//
// Called to find the explicitly indicated key
//
//////
	u32 cdx_find_key(u32 tnWorkArea, s32 tnTagIndex, u8* tcKey, u32 tnKeyLength)
	{
		u32				lnResult, lnKeyOpCount;
		SForClause*		lsFor;
		SCdxHeader*		tagHeader;		// Holds the tag key expression and FOR clause
		SCdxKeyOp*		lsKeyOp;		// Key ops for generating the DBF keys
		STagRoot		tagRoot;
		SWorkArea*		wa;


		//////////
		// Validate that our environment is sane
		//////
			if (tnWorkArea >= _MAX_DBF_SLOTS)								return(_DBF_ERROR_INVALID_WORK_AREA);
			if (!gsWorkArea[tnWorkArea].isUsed)								return(_DBF_ERROR_WORK_AREA_NOT_IN_USE);
			if (tnKeyLength == 0 || tnKeyLength > _MAX_CDX_KEY_LENGTH)		return(_CDX_ERROR_INVALID_KEY_LENGTH);
			if (!tcKey)														return(_CDX_ERROR_INVALID_KEY);


		//////////
		// Establish our pointer
		//////
			wa = &gsWorkArea[tnWorkArea];


		//////////
		// Grab the index tag header info so we can generate the keys
		//////
			memset(&tagRoot, 0, sizeof(tagRoot));
			if (!iCdx_getRootmostCompoundTag_byTagnum(wa, wa->cdx_root, NULL, tnTagIndex, &tagRoot))
				return(_CDX_ERROR_INVALID_TAG);

			// Right now, head and tagRoot are setup
			// Grab the actual key node
			tagHeader = (SCdxHeader*)iCdx_getCompactIdxNode_byOffset(wa->cdx_root, tagRoot.keyNode);


		//////////
		// Get or build the buildOps for this key
		//////
			if (!iiCdx_get_buildOps(wa, tnTagIndex, tagHeader, &lsFor, &lsKeyOp, &lnKeyOpCount, &lnResult))
				return(_CDX_ERROR_CONTEXTUAL + lnResult);	// Something is invalid


		//////////
		// Validate the key is not too long
		//////
			if (tnKeyLength > tagHeader->keyLength)
				return(_CDX_ERROR_INVALID_KEY_LENGTH);		// Invalid key length


		//////////
		// Find the key
		//////
			return(iCdx_findKey(wa, &tagRoot, tcKey, tnKeyLength));
	}




//////////
//
// Called to find the indicated key which has been pre-loaded using the dbf_set_field_data() with
// negative field numbers, so it sets the internal cdata content rather than the data content.
// That is an "accumulation area" for the data that will searched for.  It remains sticky, so
// whatever was put in there previously remains until later changed, or until the table is closed.
// That field content is copied to our own key buffer, and then used for the find.
//
//////////////
	//
	// Note:  Data is pulled from the data loaded into dbf_set_field_data() with negative field
	//        numbers.  It automatically constructs the appropriate key on the fly.
	//////
	u32 cdx_build_and_find_key(u32 tnWorkArea, s32 tnTagIndex, u32 tnKeyLength)
	{
		u32				lnResult, lnKeyOpCount;
		SForClause*		lsFor;
		u8				keyBuffer[256];
		SCdxHeader*		tagHeader;		// Holds the tag key expression and FOR clause
		SCdxKeyOp*		cko;			// Key ops for generating the DBF keys
		STagRoot		tagRoot;
		SWorkArea*		wa;


		//////////
		// Validate that our environment is sane
		//////
			if (tnWorkArea >= _MAX_DBF_SLOTS)			return(_DBF_ERROR_INVALID_WORK_AREA);
			if (!gsWorkArea[tnWorkArea].isUsed)			return(_DBF_ERROR_WORK_AREA_NOT_IN_USE);


		//////////
		// Establish our pointer
		//////
			wa = &gsWorkArea[tnWorkArea];


		//////////
		// Grab the index tag header info so we can generate the keys
		//////
			memset(&tagRoot, 0, sizeof(tagRoot));
			if (!iCdx_getRootmostCompoundTag_byTagnum(wa, wa->cdx_root, NULL, tnTagIndex, &tagRoot))
				return(-2);

			// Right now, head and tagRoot are setup
			// Grab the actual key node
			tagHeader = (SCdxHeader*)iCdx_getCompactIdxNode_byOffset(wa->cdx_root, tagRoot.keyNode);


		//////////
		// Check for invalid index
		//////
			if (tagHeader->keyLength > _MAX_CDX_KEY_LENGTH)
				return(_CDX_ERROR_INVALID_INDEX);


		//////////
		// Get or build the buildOps for this key
		//////
			if (!iiCdx_get_buildOps(wa, tnTagIndex, tagHeader, &lsFor, &cko, &lnKeyOpCount, &lnResult))
				return(_CDX_ERROR_CONTEXTUAL + lnResult);	// Something is invalid


		//////////
		// Build keys from the DBF's index field data
		//////
			iiCdx_generateKey_byOps(wa, cko, lnKeyOpCount, keyBuffer, true);
			// Right now, keyBuffer is populated with the key to find


		//////////
		// Find the key
		//////
			return(iCdx_findKey(wa, &tagRoot, keyBuffer, tnKeyLength));
	}




//////////
//
// Called to SKIP N records forward or backward from the current location in the CDX.
//
//////
	u32 cdx_skip_n(u32 tnWorkArea, s32 tnTagIndex, s32 tnDelta)
	{
		return(0);
	}




//////////
//
// Called to go to the first record in the CDX.
//
//////
	u32 cdx_top(u32 tnWorkArea, s32 tnTagIndex)
	{
		return(0);
	}




//////////
//
// Called to go to the last record in the CDX.
//
//////
	u32 cdx_bottom(u32 tnWorkArea, s32 tnTagIndex)
	{
		return(0);
	}




//////////
//
// Called to validate the indicated tag.  Meta data and error space should typically be 16,384 or
// larger each.  They will have an ASCII-0 character (CHR(0)) where the actual data ends.  This can
// be used in VFP to truncate the message to its proper length.
//
// Returns a code:
//		0				- index is bad
//		others			- index is good
//
/////
	u32 cdx_validate_tag(	u32 tnWorkArea,		s32 tnTagIndex,
							s8* tcMetaData,		u32 tnMetaDataLength,
							s8* tcErrorsFound,	u32 tnErrorsFoundLength		)
	{
		SWorkArea* wa;


		//////////
		// Validate that our environment is sane
		//////
			if (tnWorkArea >= _MAX_DBF_SLOTS)			return(_DBF_ERROR_INVALID_WORK_AREA);
			if (!gsWorkArea[tnWorkArea].isUsed)			return(_DBF_ERROR_WORK_AREA_NOT_IN_USE);


		//////////
		// If an index is already open, close it
		//////
			wa = &gsWorkArea[tnWorkArea];
			if (wa->isCdx)		return(iCdx_validateCdx(wa, tnTagIndex, tcMetaData, tnMetaDataLength, tcErrorsFound, tnErrorsFoundLength));
			else				return(iCdx_validateIdx(wa,             tcMetaData, tnMetaDataLength, tcErrorsFound, tnErrorsFoundLength));
	}




//////////
//
// Called to validate the keys contained within the indicated tag.  Meta data and error space should
// typically be 16,384 or larger each.  They will have an ASCII-0 character (CHR(0)) where the actual
// data ends.  This can be used in VFP to truncate the message to its proper length.
//
// Returns a code:
//		0				- index is bad
//		others			- index is good
//
/////
	u32 cdx_validate_keys(	u32 tnWorkArea,			s32 tnTagIndex,
							s8* tcMetaData,			u32 tnMetaDataLength,
							s8* tcErrorsFound,		u32 tnErrorsFoundLength		)
	{
		SWorkArea* wa;


		//////////
		// Validate that our environment is sane
		//////
			if (tnWorkArea >= _MAX_DBF_SLOTS)			return(_DBF_ERROR_INVALID_WORK_AREA);
			if (!gsWorkArea[tnWorkArea].isUsed)			return(_DBF_ERROR_WORK_AREA_NOT_IN_USE);


		//////////
		// If an index is already open, close it
		//////
			wa = &gsWorkArea[tnWorkArea];
			if (wa->isCdx)		return(iCdx_validateCdxKeys(wa, tnWorkArea, tnTagIndex, tcMetaData, tnMetaDataLength, tcErrorsFound, tnErrorsFoundLength));
			else				return(iCdx_validateIdxKeys(wa,                         tcMetaData, tnMetaDataLength, tcErrorsFound, tnErrorsFoundLength));
	}




//////////
//
// Called to retrieve all of the keys for the indicated tag.  The keys are sequential from start
// of index through to the end.
//
// Returns a code:
//		negative		- error
//		>=1				- Number of keys returned
//
// tcDecodeExpression	- The VFP code to use to decode the index
//
/////
	u32 cdx_get_all_keys(	u32 tnWorkArea,				s32 tnTagIndex,
							u8* tcKeySpace,				u32 tnKeySpaceLength,
							u8* tcDecodeExpression,		u32 tnDecodeExpressionLength,
							s8* tcKeyLength4	)
	{
		SWorkArea* wa;


		//////////
		// Validate that our environment is sane
		//////
			if (tnWorkArea >= _MAX_DBF_SLOTS)			return(_DBF_ERROR_INVALID_WORK_AREA);
			if (!gsWorkArea[tnWorkArea].isUsed)			return(_DBF_ERROR_WORK_AREA_NOT_IN_USE);


		//////////
		// If an index is already open, close it
		//////
			wa = &gsWorkArea[tnWorkArea];
			if (wa->isCdx)		return(iCdx_getAllKeysCdx(wa, tnTagIndex, tcKeySpace, tnKeySpaceLength, tcDecodeExpression, tnDecodeExpressionLength, tcKeyLength4));
			else				return(iCdx_getAllKeysIdx(wa,             tcKeySpace, tnKeySpaceLength, tcDecodeExpression, tnDecodeExpressionLength, tcKeyLength4));
	}




//////////
//
// Called to validate that the IDX header is valid
//
//////
	bool iCdx_validateIdx(SWorkArea* wa, s8* tcMetaData, u32 tnMetaDataLength, s8* tcErrorsFound, u32 tnErrorsFoundLength)
	{
		if (wa->isIdxCompact)		return(iCdx_validateIdx_compact( wa, tcMetaData, tnMetaDataLength, tcErrorsFound, tnErrorsFoundLength));
		else						return(iCdx_validateIdx_standard(wa, tcMetaData, tnMetaDataLength, tcErrorsFound, tnErrorsFoundLength));
	}




//////////
//
// Called to process a compact index.
//
//////
	bool iCdx_validateIdx_compact(SWorkArea* wa, s8* tcMetaData, u32 tnMetaDataLength, s8* tcErrorsFound, u32 tnErrorsFoundLength)
	{
		u32					lnI, lnNode, lnMaxNode, lnKeyNumber;
		SCdxHeader*			head;
		SCdxNode*			node;
		SCdxKeyLeafRaw		key;
		STagRoot			tagRoot;
		u8					buffer[256];
		u8					output[256];
		SBuilder*			data;


		//////////
		// Get common pointers
		//////
			head = wa->cdx_root;			// Header is first part of file
			iBuilder_createAndInitialize(&data, -1);


		//////////
		// Validate the header for a compact .IDX
		//////
			iCdx_getCompactRootNode(wa, head, NULL, &tagRoot);
			lnMaxNode = (head->fileSize - 1024) / 512;
			for (lnNode = 1; lnNode < lnMaxNode; lnNode++)
			{
				//////////
				// Get and indicate the type it is
				//////
					node = iCdx_getCompactIdxNode_byNumber(head, lnNode);
					switch (node->type)
					{
						case _CDX_NODE_INDEX:		// Index node
							sprintf((s8*)buffer, "index\0");
							break;

						case _CDX_NODE_ROOT:		// Root node
							sprintf((s8*)buffer, "root\0");
							break;

						case _CDX_NODE_LEAF:		// Leaf node
							sprintf((s8*)buffer, "leaf\0");
							break;

						case _CDX_NODE_ROOT_LEAF:	// Root leaf node
							sprintf((s8*)buffer, "root+leaf\0");
							break;

						default:
							sprintf((s8*)output, "Node %u: Unknown type %u\r\n\0", lnNode, node->type);
							iBuilder_appendData(data, output, -1);
							continue;
							break;
					}
					sprintf((s8*)output, "Node %u: %s\r\n\0", lnNode, (s8*)buffer);
					iBuilder_appendData(data, output, -1);


				//////////
				// Iterate through every key for this node
				//////
					for (lnKeyNumber = 0; lnKeyNumber < node->keyCount; lnKeyNumber++)
					{
						// Get the key here
// TODO:  The value 32 here needs to be based on the field type of the index key expression
						if (iCdx_getCompactIdxKey_byNumber(head, head->keyLength, 32, lnKeyNumber, lnKeyNumber, node, &key, &tagRoot, true, true))
						{
							// Print out the key information
							memset(buffer, 0, sizeof(buffer));
							for (lnI = 0; lnI < key.keyLength && lnI < sizeof(buffer); lnI++)
								buffer[lnI] = key.key[lnI];

							// Construct the line
							if (iiGetIndexNodeType(node->type) == 2 || iiGetIndexNodeType(node->type) == 3)
							{
								// It's a leaf node
								sprintf((s8*)output, "  - Node key number %u: [%s], Record number: %u\r\n\0", lnKeyNumber, buffer, key.recordNumber);

							} else {
								// It's an index or root node
								if (wa->isIdxCompact)
								{
									// Compact indexes have both the record number and the file offset for the node
									sprintf((s8*)output, "  - Node key number %u: [%s], File Offset: %u (Record number: %u)\r\n\0", lnKeyNumber, buffer, key.fileOffset, key.record2);

								} else {
									// Standard indexes have only the file offset
									sprintf((s8*)output, "  - Node key number %u: [%s], File Offset: %u\r\n\0", lnKeyNumber, (s8*)buffer, key.fileOffset);
								}
							}

						} else {
							// Should not happen
							sprintf((s8*)output, "Trouble accessing key number %u of node %u\r\n\0", lnKeyNumber, lnNode);
						}

						// Append the data
						iBuilder_appendData(data, output, -1);
					}
			}


		//////////
		// For debugging:
		//////
			iBuilder_asciiWriteOutFile(data, (u8*)"c:\\temp\\test\\idx_info_compact.txt", false);
			iBuilder_freeAndRelease(&data);


		//////////
		// If we found no errors, indicate success
		//////
			return(true);
	}




//////////
//
// Called to process a non-compact index.
//
//////
	bool iCdx_validateIdx_standard(SWorkArea* wa, s8* tcMetaData, u32 tnMetaDataLength, s8* tcErrorsFound, u32 tnErrorsFoundLength)
	{
		u32				lnI, lnNode, lnMaxNode, lnKeyNumber;
		SIdxHeader*		head;
		SIdxNode*		node;
		SIdxKey			key;
		STagRoot		tagRoot;
		u8				buffer[256];
		u8				output[256];
		SBuilder*		data;


		//////////
		// Get common pointers
		//////
			head = wa->idx_header;			// Header is first part of file
			iBuilder_createAndInitialize(&data, -1);


		//////////
		// Validate the header for a .IDX
		//////
			lnMaxNode = (head->fileSize - 512) / 512;
			iCdx_getStandardRootNode(wa, head, NULL, &tagRoot);
			for (lnNode = 1; lnNode < lnMaxNode; lnNode++)
			{
				//////////
				// Get and indicate the type it is
				//////
					node = iCdx_getStandardIdxNode_byNumber(head, lnNode);
					switch (node->type)
					{
						case _CDX_NODE_INDEX:		// Index node
							sprintf((s8*)buffer, "index\0");
							break;

						case _CDX_NODE_ROOT:		// Root node
							sprintf((s8*)buffer, "root\0");
							break;

						case _CDX_NODE_LEAF:		// Leaf node
							sprintf((s8*)buffer, "leaf\0");
							break;

						case _CDX_NODE_ROOT_LEAF:	// Root leaf node
							sprintf((s8*)buffer, "root+leaf\0");
							break;

						default:
							debug_break;
							break;
					}
					sprintf((s8*)output, "Node %u: %s\r\n\0", lnNode, buffer);
					iBuilder_appendData(data, output, -1);


				//////////
				// Iterate through every key for this node
				//////
					for (lnKeyNumber = 0; lnKeyNumber < node->keyCount; lnKeyNumber++)
					{
						// Get the key here
						if (iCdx_getStandardIdxKey_byNumber(head, tagRoot.fillChar, lnKeyNumber, node, &key, &tagRoot, true, true))
						{
							// Print out the key information
							memset(buffer, 0, sizeof(buffer));
							for (lnI = 0; lnI < key.keyLength && lnI < sizeof(buffer); lnI++)
								buffer[lnI] = key.key[lnI];

							// Construct the line
							// Prefix
							if (node->type == 2 || node->type == 3)		sprintf((s8*)output, "  - Node key number %u: [\0", lnKeyNumber);
							else										sprintf((s8*)output, "  - Node key number %u: [\0", lnKeyNumber);
							iBuilder_appendData(data, output, -1);

							// Key
							iBuilder_appendData(data, buffer, key.keyLength);

							// Postfix
							if (node->type == 2 || node->type == 3)		sprintf((s8*)output, "], Record number: %u\r\n\0", (u32)key.record);
							else										sprintf((s8*)output, "], File Offset: %u\r\n\0",   (u32)key.record);

						} else {
							// Should not happen
							sprintf((s8*)output, "Trouble accessing key number %u of node %u\r\n\0", lnKeyNumber, lnNode);
						}
						iBuilder_appendData(data, output, -1);
					}
			}


// 		//////////
// 		// For debugging:
// 		//////
// 			iBuilder_asciiWriteOutFile(data, (u8*)"c:\\temp\\test\\idx_info_standard.txt", false);
// 			iBuilder_freeAndRelease(&data);


		//////////
		// If we found no errors, indicate success
		//////
			return(true);
	}




//////////
//
// Called to validate that the compound CDX header is valid
//
// Note:  Use tnTagIndex of -1 to validate all tags
//
//////
	s32 iCdx_validateCdx(SWorkArea* wa, s32 tnTagIndex, s8* tcMetaData, u32 tnMetaDataLength, s8* tcErrorData, u32 tnErrorDataLength)
	{
		u32				lnTagNum, lnNodeNumber, lnKeyNumber, lnStartTagNum, lnEndTagNum, lnTotalKeyCount;
		bool			llProcessed, llContinue;
		SCdxNode*		node;
		SCdxKeyLeafRaw	key, keyLast;
		STagRoot		tagRoot;
		u8				buffer[256];
		u8				output[256];
		SBuilder*		metaData;
		SBuilder*		errorData;
//		SCdxHeader*		head;
		SVariable*		varTableName;
		SVariable*		varAlias;
		SVariable*		varCdxName;
		SVariable*		varTag;
		SVariable*		varMessage;
		SVariable*		varIsError;
		SVariable*		varRebuildIndexRequired;


		//////////
		// Initialize
		//////
			if (tcMetaData)		iBuilder_createAndInitialize(&metaData, -1);
			else				metaData = NULL;

			if (tcErrorData)	iBuilder_createAndInitialize(&errorData, -1);
			else				errorData = NULL;


		//////////
		// Create callback variables
		//////
			varTableName			= iVariable_createAndPopulate_byText(_VAR_TYPE_CHARACTER,	wa->tablePathname,		wa->tablePathnameLength,		true);
			varAlias				= iVariable_createAndPopulate_byText(_VAR_TYPE_CHARACTER,	wa->alias,				wa->aliasLength,				true);
			varCdxName				= iVariable_createAndPopulate_byText(_VAR_TYPE_CHARACTER,	wa->idxCdxDcxPathname,	wa->idxCdxDcxPathnameLength,	true);
			varTag					= iVariable_create(_VAR_TYPE_CHARACTER,	NULL, true);
			varMessage				= iVariable_create(_VAR_TYPE_CHARACTER,	NULL, true);
			varIsError				= iVariable_create(_VAR_TYPE_LOGICAL,	NULL, true);
			varRebuildIndexRequired	= iVariable_create(_VAR_TYPE_LOGICAL,	NULL, true);

			// Were they all created okay?
			if (!varTableName || !varAlias || !varCdxName || !varTag || !varMessage || !varIsError || !varRebuildIndexRequired)
			{

				//////////
				// Signal the error and fail
				//////
					iError_signal(_ERROR_UNABLE_TO_AUTOVALIDATE, NULL, false, NULL, false);
					llProcessed = false;
					goto clean_house;

			}


		//////////
		// Iterate through the various tags
		//////
			// Do they want to scan all of them?
			if (tnTagIndex < 0)
			{
				// Yes
				lnStartTagNum	= 0;
				lnEndTagNum		= 999999;

			} else {
				// They just want to do one
				lnStartTagNum	= tnTagIndex;
				lnEndTagNum		= tnTagIndex;
			}

			// Iterate through one tag, or all of the tags
			for (lnTagNum = lnStartTagNum, llProcessed = false, llContinue = true; llContinue && lnTagNum <= lnEndTagNum && iCdx_getRootmostCompoundTag_byTagnum(wa, wa->cdx_root, NULL, lnTagNum, &tagRoot); lnTagNum++)
			{
				// Indicate we processed at last one thing
				llProcessed = true;


				//////////
				// Meta data
				//////
					if (metaData)
					{
						// Building the list
						iBuilder_appendData(metaData, (cu8*)"Tag: ", -1);
						iBuilder_appendData(metaData, tagRoot.tagName, sizeof(tagRoot.tagName));
						iBuilder_backoffTrailingWhitespaces(metaData);

					} else {
						// Signal validation begin
						iVariable_set_character(varTag,					tagRoot.tagName,	iiCountContiguousCharacters(&tagRoot.tagName[0], sizeof(tagRoot.tagName)));
						iVariable_set_character(varMessage,				(u8*)cgcValidateBegin,	sizeof(cgcValidateBegin) - 1);
						iVariable_set_logical(varIsError,				false);
						iVariable_set_logical(varRebuildIndexRequired,	false);
						llContinue = iEngine_signal_onValidate(varTableName, varAlias, varCdxName, varTag, varMessage, varIsError, varRebuildIndexRequired);
						if (!llContinue)
							return(0);
					}


				//////////
				// Validate the header for a this compact .IDX
				//////
					node			= iCdx_getCompactIdxNode_byOffset(wa->cdx_root, tagRoot.leftmostNode);
//					head			= (SCdxHeader*)iCdx_getCompactIdxNode_byOffset(wa->cdx_root, tagRoot.keyNode);
					lnTotalKeyCount	= 0;
					while (node)
					{
						//////////
						// Indicate the type it is
						//////
							lnNodeNumber = (u32)(((uptr)node - (uptr)wa->cdx_root - sizeof(SCdxHeader)) / 512);
							switch (node->type)
							{
								case _CDX_NODE_INDEX:		// Index node
								case _CDX_NODE_ROOT:		// Root node
								case _CDX_NODE_LEAF:		// Leaf node
								case _CDX_NODE_ROOT_LEAF:	// Root leaf node
									// These are all acceptable
									break;

								default:
									if (errorData)
									{
										// Append to the error data
										sprintf((s8*)output, "Node %u: Unknown type of node encountered, expected 0=index, 1=root, 2=leaf, 3=root+leaf, found %u=???\r\n\0", lnNodeNumber, node->type);
										iBuilder_appendData(errorData, output, -1);

									} else {
										// Signal validation error
										iVariable_set_character(varMessage,				(u8*)cgcValidateInvalidNode,	sizeof(cgcValidateInvalidNode) - 1);
										iVariable_set_logical(varIsError,				true);
										iVariable_set_logical(varRebuildIndexRequired,	true);
										llContinue = iEngine_signal_onValidate(varTableName, varAlias, varCdxName, varTag, varMessage, varIsError, varRebuildIndexRequired);
									}

									// Bad index
									goto we_are_done;
							}


						//////////
						// Iterate through every key for this node
						//////
							if (node->keyCount != 0)
							{
								// Convey the keys
								for (lnKeyNumber = 0; lnKeyNumber < node->keyCount; lnKeyNumber++)
								{
									// Get the key here
									if (iCdx_getCompactIdxKey_byNumber(wa->cdx_root, tagRoot.keyLength, tagRoot.fillChar, lnKeyNumber, lnKeyNumber, node, &key, &tagRoot, false, false))
									{
										// Indicate our key count has gone up
										++lnTotalKeyCount;

										// Print out the key information
										memset(buffer, 0, sizeof(buffer));
// Added for debugging
// if (key.keyLength > 240)
// 	debug_break;
										memcpy(buffer, key.key, key.keyLength);


										//////////
										// Compare the index to its previous value and make sure they're still in order
										//////
											if (lnKeyNumber != 0)
											{
												// Based on sort order, we must either be >= or <=
												if (tagRoot.indexIsDesc)
												{
													// Sort order is descending
													if (memcmp(&key.key, &keyLast.key, key.keyLength) > 0)
													{
														// We found a key out of order
														if (errorData)
														{
															// Append to the error list
															sprintf((s8*)output, "Key number %u is out of index order on node %u\r\n\0", lnKeyNumber, lnNodeNumber);
															iBuilder_appendData(errorData, output, -1);

														} else {
															// Signal validation error
															iVariable_set_character(varMessage,				(u8*)cgcValidateKeysOutOfOrder,	sizeof(cgcValidateKeysOutOfOrder) - 1);
															iVariable_set_logical(varIsError,				true);
															iVariable_set_logical(varRebuildIndexRequired,	false);
															llContinue = iEngine_signal_onValidate(varTableName, varAlias, varCdxName, varTag, varMessage, varIsError, varRebuildIndexRequired);
															if (!llContinue)
																goto we_are_done;
														}
													}

												} else {
													// Sort order is ascending
													if (memcmp(&key.key, &keyLast.key, key.keyLength) < 0)
													{
														// We found a key out of order
														if (errorData)
														{
															// Append to the error list
															sprintf((s8*)output, "Key number %u is out of index order on node %u\r\n\0", lnKeyNumber, lnNodeNumber);
															iBuilder_appendData(errorData, output, -1);

														} else {
															// Signal validation error
															iVariable_set_character(varMessage,				(u8*)cgcValidateKeysOutOfOrder,	sizeof(cgcValidateKeysOutOfOrder) - 1);
															iVariable_set_logical(varIsError,				true);
															iVariable_set_logical(varRebuildIndexRequired,	false);
															llContinue = iEngine_signal_onValidate(varTableName, varAlias, varCdxName, varTag, varMessage, varIsError, varRebuildIndexRequired);
															if (!llContinue)
																goto we_are_done;
														}
													}
												}
											}
											memcpy(&keyLast, &key, sizeof(key));

									} else {
										// Should not happen
										if (errorData)
										{
											// Append error information
											sprintf((s8*)output, "Unable to access key number %u of node %u\r\n\0", lnKeyNumber, lnNodeNumber);
											iBuilder_appendData(errorData, output, -1);

										} else {
											// Signal validation error
											iVariable_set_character(varMessage,				(u8*)cgcValidateKeyNotPresent,	sizeof(cgcValidateKeyNotPresent) - 1);
											iVariable_set_logical(varIsError,				true);
											iVariable_set_logical(varRebuildIndexRequired,	true);
											llContinue = iEngine_signal_onValidate(varTableName, varAlias, varCdxName, varTag, varMessage, varIsError, varRebuildIndexRequired);
										}

										goto we_are_done;
									}
								}

							} else {
								// No keys on this node
								if (node->nodeLeft != (u32)-1 || node->nodeRight != (u32)-1)
								{
									if (metaData)
									{
										sprintf((s8*)output, "No index keys were found on node %u\r\n\0", lnNodeNumber);
										iBuilder_appendData(metaData, output, -1);

									} else {
										// Signal validation error
										iVariable_set_character(varMessage,				(u8*)cgcValidateEmptyNode,	sizeof(cgcValidateEmptyNode) - 1);
										iVariable_set_logical(varIsError,				true);
										iVariable_set_logical(varRebuildIndexRequired,	false);
										llContinue = iEngine_signal_onValidate(varTableName, varAlias, varCdxName, varTag, varMessage, varIsError, varRebuildIndexRequired);
										if (!llContinue)
											goto we_are_done;
									}
								}
								//else this is the only node, which means no keys in index
							}


						//////////
						// Move to next node
						//////
							if (node->nodeRight == (u32)-1)
								break;	// All done

							// Move to the next lead node right and continue through the keys
							node = iCdx_getCompactIdxNode_byOffset(wa->cdx_root, node->nodeRight);
					}
we_are_done:

				//////////
				// Meta data -- the number of keys
				//////
					if (metaData)
					{
						sprintf((s8*)output, " %u keys in index.\r\n\0", lnTotalKeyCount);
						iBuilder_appendData(metaData, output, -1);

					} else {
						// Signal validation ends
						if (llContinue)
						{
							// We're good, indicate the number of keys
							sprintf((s8*)output, "%s, %u keys in index\0", cgcValidateEnd, lnTotalKeyCount);
							iVariable_set_character(varMessage,		output, (u32)strlen(output));

						} else {
							// Indicate we are done
							iVariable_set_character(varMessage,		(u8*)cgcValidateEnd,	sizeof(cgcValidateEnd) - 1);
						}
						iVariable_set_logical(varIsError,				false);
						iVariable_set_logical(varRebuildIndexRequired,	false);
						llContinue = iEngine_signal_onValidate(varTableName, varAlias, varCdxName, varTag, varMessage, varIsError, varRebuildIndexRequired);
					}
			}


		//////////
		// Copy the data back
		//////
			if (tcMetaData && metaData)
				memcpy(tcMetaData, metaData->data_s8, min(tnMetaDataLength, metaData->populatedLength));

			if (tcErrorData && errorData)
				memcpy(tcErrorData, errorData->data_s8, min(tnErrorDataLength, errorData->populatedLength));


		//////////
		// Clean house
		//////
clean_house:
			if (metaData)		iBuilder_freeAndRelease(&metaData);
			if (errorData)		iBuilder_freeAndRelease(&errorData);


		//////////
		// Delete any variables that actually did make it
		//////
			iVariable_delete(varTableName,				true);
			iVariable_delete(varAlias,					true);
			iVariable_delete(varCdxName,				true);
			iVariable_delete(varTag,					true);
			iVariable_delete(varMessage,				true);
			iVariable_delete(varIsError,				true);
			iVariable_delete(varRebuildIndexRequired,	true);


		//////////
		// If we found no errors, indicate success
		//////
			return(((llProcessed && llContinue) ? 1 : -1));
	}




//////////
//
// Called to validate all of the keys within the indicated tag.  This process will only work
// on single field keys, or simple concatenated string keys (a+b+c).
//
//////
	s32 iCdx_validateCdxKeys(SWorkArea* wa, u32 tnWorkArea, s32 tnTagIndex, s8* tcMetaData, u32 tnMetaDataLength, s8* tcErrorsFound, u32 tnErrorsFoundLength)
	{
		u32				lnRecno, lnDbfRecno, lnCdxRecno;
		s32				lnI, lnKey, lnCdxKeyCount, lnDbfKeyCount, lnKeyOpCount;
		bool			llResult;
		SForClause*		lsFor;
		u8				lcDecodeExpression[512];
		s8				lcKeyLength4[8];
		s8*				dbfPtr;
		s8*				cdxPtr;
		s8*				keyPtr;
		s8*				keyPtrLast;
		s8*				keyPtrUnique;
		SBuilder*		dbfKeys;
		SBuilder*		dbfKeysUnique;
		SBuilder*		cdxKeys;
		SBuilder*		metaData;
		SBuilder*		errorsFound;
		SCdxHeader*		tagHeader;	// Holds the tag key expression and FOR clause
		SCdxKeyOp*		cko;		// Key ops for generating the DBF keys
		STagRoot		tagRoot;


		//////////
		// Grab the index tag header info so we can generate the keys
		//////
			memset(&tagRoot, 0, sizeof(tagRoot));
			if (!iCdx_getRootmostCompoundTag_byTagnum(wa, wa->cdx_root, NULL, tnTagIndex, &tagRoot))
			{
				sprintf(tcMetaData, "Unable to access tag index %u\n", tnTagIndex);
				return(-1);
			}
			// Right now, head and tagRoot are setup
			// Grab the actual key node
			tagHeader = (SCdxHeader*)iCdx_getCompactIdxNode_byOffset(wa->cdx_root, tagRoot.keyNode);


		//////////
		// Initialize
		//////
			llResult	= true;		// Assume everything is correct from the get-go
			cko			= NULL;		// No ops initially allocated
			iBuilder_createAndInitialize(&dbfKeys,			-1);
			iBuilder_createAndInitialize(&dbfKeysUnique,	-1);
			iBuilder_createAndInitialize(&cdxKeys,			-1);
			iBuilder_createAndInitialize(&metaData,			-1);
			iBuilder_createAndInitialize(&errorsFound,		-1);


		//////////
		// Add meta data
		//////
			iBuilder_appendData(metaData, (cu8*)"Tag: ", -1);
			iBuilder_appendData(metaData, tagRoot.tagName, min((u32)strlen((s8*)tagRoot.tagName), 10));
			iBuilder_backoffTrailingWhitespaces(metaData);
			iBuilder_appendData(metaData, (cu8*)", INDEX ON ", -1);

			iBuilder_appendData(metaData, tagHeader->keyExpression, tagHeader->keyExpressionLength - 1);
			iBuilder_appendData(metaData, (cu8*)" ", -1);

			if (iiCdx_isUnique(tagHeader))
				iBuilder_appendData(metaData, (cu8*)"UNIQUE ", -1);

			if (iiCdx_isDescending(tagHeader))
				iBuilder_appendData(metaData, (cu8*)"DESCENDING ", -1);

			if (tagHeader->forClauseLength > 1)
			{
				iBuilder_appendData(metaData, (cu8*)"FOR ", -1);
				iBuilder_appendData(metaData, tagHeader->keyExpression + tagHeader->keyExpressionLength, tagHeader->forClauseLength - 1);
			}
			iBuilder_appendCrLf(metaData);


		//////////
		// Indexes with complex FOR clauses are not currently supported.
		// Only those which are simple logical field tests are supported.
		//////
			lsFor = NULL;
			if (iCdx_isForClauseComplex(wa, tagHeader, &lsFor))
			{
				// Tell them why we're failing this process
				if (tcMetaData)
				{
					// Store the string to return
					iBuilder_appendData(metaData, (cu8*)"Tag: ", -1);
					iBuilder_appendData(metaData, tagRoot.tagName, min((u32)strlen((s8*)tagRoot.tagName), 10));
					iBuilder_backoffTrailingWhitespaces(metaData);
					iBuilder_appendData(metaData, (cu8*)", FOR clause is too complex for current support", -1);
					goto close_and_quit;
				}
			}


		//////////
		// Generate DBF keys based on raw table data
		//////
			iBuilder_allocateBytes(dbfKeys, wa->header.records * (tagRoot.keyLength + 4));
			cko = iiCdx_generateKey_buildOps(wa, &tagHeader->keyExpression[0], &lnKeyOpCount);
			if (!cko)
			{
				// Key expression could not be parsed
				llResult = false;
				iBuilder_appendData(metaData, (cu8*)"Tag: ", -1);
				iBuilder_appendData(metaData, tagRoot.tagName, min((u32)strlen((s8*)tagRoot.tagName), 10));
				iBuilder_backoffTrailingWhitespaces(metaData);
				iBuilder_appendData(metaData, (cu8*)", key expression could not be parsed", -1);
				iBuilder_appendCrLf(metaData);
				goto close_and_quit;
			}


		//////////
		// Build keys from the DBF data
		//////
			for (lnRecno = 1, lnDbfKeyCount = 0; lnRecno <= wa->header.records; lnRecno++)
			{

				//////////
				// Load this record
				//////
					iDbf_gotoRecord(wa, lnRecno);


				//////////
				// See if it matches with our FOR clause test
				//////
					if (!iiDbf_forClause_isRowIncluded(wa, lsFor))
						continue;


				//////////
				// Generate and store the key
				//////
					iiCdx_generateKey_byOps(wa, cko, lnKeyOpCount, dbfKeys->data_u8 + (lnDbfKeyCount * (tagRoot.keyLength + 4)), false);

					// Append the record number
					*(u32*)(dbfKeys->data_u8 + (lnDbfKeyCount * (tagRoot.keyLength + 4) + tagRoot.keyLength)) = iiSwapEndian32(lnRecno);

					// Increase our key count
					++lnDbfKeyCount;

			}
			// Remove any keys that weren't included
			iBuilder_setSize(dbfKeys, lnDbfKeyCount * (tagRoot.keyLength + 4));


		//////////
		// Load every key in the index
		//////
			iBuilder_allocateBytes(cdxKeys, wa->header.records * (tagRoot.keyLength + 4));
// if (iIsNeedleInHaystack(metaData->buffer, metaData->populatedLength, "cdosname", 8))
// 	_asm nop;
			lnCdxKeyCount = iCdx_getAllKeysCdx(wa, tnTagIndex, cdxKeys->data_u8, cdxKeys->totSize, &lcDecodeExpression[0], sizeof(lcDecodeExpression), &lcKeyLength4[0]);
			// Remove any keys that weren't included
			iBuilder_setSize(cdxKeys, lnCdxKeyCount * (tagRoot.keyLength + 4));


		//////////
		// Where are we?
		//////
			if (dbfKeys->populatedLength == 0)
			{
				// There cannot be any CDX keys either
				if (cdxKeys->populatedLength == 0)
				{
					iBuilder_appendData(metaData, (cu8*)"Tag: ", -1);
					iBuilder_appendData(metaData, tagRoot.tagName, min((u32)strlen((s8*)tagRoot.tagName), 10));
					iBuilder_backoffTrailingWhitespaces(metaData);
					iBuilder_appendData(metaData, (cu8*)", DBF key count: 0, CDX key count: 0", -1);
					iBuilder_appendCrLf(metaData);
					goto close_and_quit;	// They indexes match (being as there are no indexes)!
				}
				// If we get here, the number of records does not match

			} else {
				//////////
				// Sort the DBF keys
				//////
					gnCdx_sort_keyLength = tagRoot.keyLength + 4;
					if (iiCdx_isDescending(tagHeader))	qsort(dbfKeys->buffer,	lnDbfKeyCount,	tagRoot.keyLength + 4,	iiKeys_qsortDescending_callback);
					else											qsort(dbfKeys->buffer,	lnDbfKeyCount,	tagRoot.keyLength + 4,	iiKeys_qsortAscending_callback);
			}


		//////////
		// Restore the DBF keys to their natural form if any were fixed up
		//////
			for (lnI = 0; lnI < (s32)dbfKeys->populatedLength; lnI += (tagRoot.keyLength + 4))
			{
				// Fixup any on the key data
				iiCdx_generateKey_byOps_fixup(wa, cko, lnKeyOpCount, dbfKeys->data_u8 + lnI, false);

				// Fixup the recno()
				*(u32*)(dbfKeys->buffer + lnI + tagRoot.keyLength) = iiSwapEndian32(*(u32*)(dbfKeys->buffer + lnI + tagRoot.keyLength));
			}


		//////////
		// Fixup the CDX keys to their natural form
		//////
			// Fixup any on the key data
			for (lnI = 0; lnI < (s32)cdxKeys->populatedLength; lnI += (tagRoot.keyLength + 4))
			{
				// Early out
				if (!iiCdx_generateKey_byOps_fixup(wa, cko, lnKeyOpCount, cdxKeys->data_u8 + lnI, true))
					break;
			}


		//////////
		// Iterate through all of the dbfKeys and make sure there is a matching entry in
		// the cdxKeys.  Report any errors.
		//////
			if (iiCdx_isUnique(tagHeader))
			{
				//////////
				// The index key must match the first entry found in the dbfKeys
				// Iterate through all derived keys, and create an extract of only those keys which are unique
				//////
					for (lnKey = 0, keyPtrLast = NULL; lnKey < lnDbfKeyCount; lnKey++)
					{
						//////////
						// Has the key changed?
						//////
							keyPtr = dbfKeys->buffer + (lnKey * (tagRoot.keyLength + 4));
							if (keyPtrLast == NULL || memcmp(keyPtr, keyPtrLast, tagRoot.keyLength + 4) != 0)
							{
								// The key has changed, append this one as unique
								keyPtrUnique = (s8*)iBuilder_allocateBytes(dbfKeysUnique, tagRoot.keyLength + 4);

								// Copy over
								memcpy(keyPtrUnique, keyPtr, tagRoot.keyLength + 4);

								// Store the last key
								keyPtrLast = keyPtrUnique;
							}
					}

					//////////
					// When we get here, we have our unique list
					// Swap dbfKeys and dbfKeysUnique so that dbfKeys contains the unique keys
					//////
						// Swap pointers
						iiPtrSwap((void**)&dbfKeys, (void**)&dbfKeysUnique);

						// Update our DBF key count
						lnDbfKeyCount = dbfKeys->populatedLength / (tagRoot.keyLength + 4);
			}


		//////////
		// Iterate through all of the dbfKeys and make sure there is only one matching
		// entry in cdxKeys for each.  Report any errors.
		//////
			for (lnKey = 0, dbfPtr = dbfKeys->buffer, cdxPtr = cdxKeys->buffer; lnKey < lnDbfKeyCount; lnKey++, dbfPtr += (tagRoot.keyLength + 4), cdxPtr += (tagRoot.keyLength + 4))
			{
				// Validate this key
				if (memcmp(dbfPtr, cdxPtr, tagRoot.keyLength + 4) != 0)
				{
					// We've found a discrepancy
					lnDbfRecno = *(u32*)(dbfPtr + tagRoot.keyLength);
					lnCdxRecno = *(u32*)(cdxPtr + tagRoot.keyLength);

					// Is the RECNO() the same?
					if (lnDbfRecno == lnCdxRecno)
					{
						// Yes, they are the same RECNO(), which means our keys are different
						sprintf((s8*)lcDecodeExpression, "KEYNO(%u) CDX key does not match table. Index needs rebuilt. There may be other errors.\n\0", lnDbfRecno);
						iBuilder_appendData(errorsFound, lcDecodeExpression, -1);

						// We can keep going on this error... it most likely means someone made a table change without the index open, and it may not mean catastrophic failures
						// However, the index is still damaged
						llResult = false;
						break;

					} else {
						// Nope, they are markedly different
						sprintf((s8*)lcDecodeExpression, "KEYNO(%u) key was not found in the CDX. Index needs rebuilt. There may be other errors.\n\0", lnDbfRecno);
						iBuilder_appendData(errorsFound, lcDecodeExpression, -1);

						// We cannot continue on this error.  It is the beginning of what will likely be many errors
						llResult = false;
						break;
					}
					// If we get here, we are continuing on
				}
			}
			// Indicate the result
			iBuilder_appendData(metaData, (cu8*)"Tag: ", -1);
			iBuilder_appendData(metaData, tagRoot.tagName, min((u32)strlen((s8*)tagRoot.tagName), 10));
			iBuilder_backoffTrailingWhitespaces(metaData);
			if (llResult)
			{
				// If we get here, the keys all match (by RECNO() at least) so we can continue on
				iBuilder_appendData(metaData, (cu8*)", valid", -1);

			} else {
				iBuilder_appendData(metaData, (cu8*)", invalid", -1);
			}
			iBuilder_appendCrLf(metaData);


close_and_quit:
		//////////
		// Update our meta data and errors found (if any)
		//////
			if (tcMetaData)
			{
				// Initialize
				memset(tcMetaData, 32, tnMetaDataLength);

				// Copy (if anything)
				if (metaData->populatedLength != 0)
					memcpy(tcMetaData, metaData->buffer, min(tnMetaDataLength, metaData->populatedLength));
			}
			if (tcErrorsFound)
			{
				// Initialize
				memset(tcErrorsFound, 32, tnErrorsFoundLength);

				// Copy (if anything)
				if (errorsFound->populatedLength != 0)
					memcpy(tcErrorsFound, errorsFound->buffer, min(tnErrorsFoundLength, errorsFound->populatedLength));
			}


		//////////
		// Clean house
		//////
			// Free FOR clause
			if (lsFor)
				iDbf_forClause_delete(&lsFor);

			// Free key ops
			if (cko)
				free(cko);

			// Free builders
			iBuilder_freeAndRelease(&dbfKeys);
			iBuilder_freeAndRelease(&dbfKeysUnique);
			iBuilder_freeAndRelease(&cdxKeys);
			iBuilder_freeAndRelease(&metaData);
			iBuilder_freeAndRelease(&errorsFound);


		//////////
		// Indicate our return result
		//////
			return(((llResult) ? 1 : -1));
	}

	int iiKeys_qsortDescending_callback(const void* l, const void* r)
	{
		// Return reversed memcmp result
		return(memcmp(l, r, gnCdx_sort_keyLength) * -1);
	}

	int iiKeys_qsortAscending_callback(const void* l, const void* r)
	{
		// Return memcmp result
		return(memcmp(l, r, gnCdx_sort_keyLength));
	}




//////////
//
// Not currently supported, but defined because ... well that's just the kind of guy I am (hopeful that in the future I or other developers will step forward to contribute from their own bosom into this project)
//
//////
	s32 iCdx_validateIdxKeys(SWorkArea* wa, s8* tcMetaData, u32 tnMetaDataLength, s8* tcErrorsFound, u32 tnErrorsFoundLength)
	{
// TODO:  Not currently supported
		debug_break;
		return(-1);
	}




//////////
//
// Called to load and decode the CDX keys for the indicated node.  If they've already been cached, then if in
// non-exclusive mode it validates the node on disk still matches that which is in memory, and either dumps the
// cache and re-decodes if different, or immediately returns the cached data if still the same.  If in exclusive
// mode, then it immediate returns what was cached.  If it hasn't yet been cached, it loads and decodes, and
// then returns cached.
//
// If at any point the disk data cannot be read, the operation fails.
//
// Note:  Nodes are base-1, so the disk location is calculated as ((node-1) * 512).
//
//////
	SCdxNodeCache* iCdx_cacheNode(SWorkArea* wa, SCdxHeader* tagHeader, s32 tnNodeNum, SCdxNode** nodeDst)
	{
		s32				lnNumread;
		u32				lnI;
		s64				lnCdxSize, lnOffset;
		SDiskLock*		dl;
		SCdxNode		diskNode;
		SCdxNodeCache*	thisNodeCache;
		bool			error;
		u32				errorNum;


		//////////
		// Is our environment sane?
		//////
			if (!wa || !wa->isCdx || !tagHeader)
			{
				// Invalid environment
				wa->idxCdxDcxLastError = _CDX_ERROR_INVALID_INDEX;
				return(NULL);
			}


		//////////
		// Grab the file's size
		//////
			lnCdxSize = iDisk_getFileSize(wa->fhIdxCdxDcx);
			if (lnCdxSize < 0)
			{
				// File handle is not valid
				wa->idxCdxDcxLastError = _CDX_ERROR_INVALID_INDEX;
				return(NULL);
			}


		//////////
		// Is the node they're seeking valid?
		//////
			lnOffset = (s64)(tnNodeNum - 1) * 512;
			if (lnOffset + 511 >= lnCdxSize)
			{
				// Out of range
				wa->idxCdxDcxLastError = _CDX_ERROR_INVALID_NODE;
				return(NULL);
			}


		//////////
		// Make sure we have a node cache buffer
		//////
			if (!wa->idxCdxDcxNodeCache)
			{
				// Allocate the buffer
				iBuilder_createAndInitialize(&wa->idxCdxDcxNodeCache, -1);
				if (!wa->idxCdxDcxNodeCache || !wa->idxCdxDcxNodeCache->buffer)
				{
					// Trouble allocating
					wa->idxCdxDcxLastError = _CDX_ERROR_INTERNAL;
					return(NULL);
				}
			}


		//////////
		// When we get here, the node is within the file's size.
		// See if we already have it cached.
		//////
			for (lnI = 0, thisNodeCache = (SCdxNodeCache*)wa->idxCdxDcxNodeCache->buffer; lnI < wa->idxCdxDcxNodeCache->populatedLength; lnI++, thisNodeCache++)
			{
				// See if our node matches
				if (thisNodeCache->isUsed && thisNodeCache->nodeNum == tnNodeNum)
				{

					//////////
					// Are we exclusive?
					//////
						if (wa->isExclusive)
						{
							// Store the node data (if needed)
							if (nodeDst)
								*nodeDst = thisNodeCache->cachedNode;

							// Indicate success
							return(thisNodeCache);
						}
						// If we get here, we're shared


					//////////
					// Validate what we have cached is still in sync with whatever's presently on disk
					//////
						lnNumread = iDisk_readShared_withRetryCallback(wa->idxCdxDcxFileLocks, wa->fhIdxCdxDcx, lnOffset, &diskNode, 512, &error, &errorNum, (uptr)&iiDbf_continueWithLockOperation, (uptr)&dl, &dl, true);
						if (error || lnNumread != 512 || !dl)
						{
							// Error reading this node
							wa->idxCdxDcxLastError = _CDX_ERROR_READING_NODE;
							return(NULL);
						}
						// We've read the content


					//////////
					// Is it still the same as what we last loaded?
					//////
						if (thisNodeCache->cachedNode && memcmp(&diskNode, thisNodeCache->cachedNode, 512) == 0)
						{
							// Store the node data (if needed)
							if (nodeDst)
								*nodeDst = thisNodeCache->cachedNode;

							// Indicate success
							return(thisNodeCache);
						}


					//////////
					// We need to dump what we have and reload the cache
					//////
						iiCdx_cacheNode_delete(wa, tagHeader, thisNodeCache, true);

				}
			}
			// When we get here, we do not already have this node cached


		//////////
		// Allocate a cache node
		//////
			thisNodeCache = iiCdx_cacheNode_allocate(wa, tagHeader, tnNodeNum, true);
			if (!thisNodeCache)
			{
				wa->idxCdxDcxLastError = _CDX_ERROR_MEMORY_CDX;
				return(NULL);
			}


		//////////
		// Populate it
		//////
			thisNodeCache->cachedNode = (SCdxNode*)malloc(sizeof(SCdxNode));
			if (!thisNodeCache->cachedNode)
			{
				wa->idxCdxDcxLastError = _CDX_ERROR_MEMORY_CDX;
				return(NULL);
			}
			thisNodeCache->isUsed		= true;
			thisNodeCache->nodeNum		= tnNodeNum;

			return(NULL);
	}




//////////
//
// Called to allocate a new node for caching.
// Note:  If node is specified, it goes ahead and automatically populates the keys into the cache
//
//////
	SCdxNodeCache* iiCdx_cacheNode_allocate(SWorkArea* wa, SCdxHeader* tagHeader, s32 tnNodeNum, bool tlAutoPopulate)
	{
		SCdxNodeCache* thisNodeCache;


		//////////
		// Allocate
		//////
			thisNodeCache = (SCdxNodeCache*)iBuilder_allocateBytes(wa->idxCdxDcxNodeCache, sizeof(SCdxNodeCache));
			if (!thisNodeCache)
			{
				wa->idxCdxDcxLastError = _CDX_ERROR_MEMORY_CDX;
				return(NULL);
			}


		//////////
		// And the node buffer
		//////
			thisNodeCache->cachedNode = (SCdxNode*)malloc(sizeof(SCdxNode));
			if (!thisNodeCache->cachedNode)
			{
				wa->idxCdxDcxLastError = _CDX_ERROR_MEMORY_CDX;
				return(NULL);
			}

			// Populate hard constants
			thisNodeCache->isUsed		= true;
			thisNodeCache->nodeNum		= tnNodeNum;


		//////////
		// Populate the node?
		//////
			if (tlAutoPopulate)
				iiCdx_cacheNode_populate(wa, tagHeader, thisNodeCache, true);
// TODO:  Working here


		//////////
		// Indicate our result
		//////
			return(thisNodeCache);

	}




//////////
//
// Called to populate the previously allocated node cache with new keys read from disk.
// Will automatically de-populate if already populated.
//
//////
	void iiCdx_cacheNode_populate(SWorkArea* wa, SCdxHeader* tagHeader, SCdxNodeCache* nodeKeys, bool tlAllocateLiberally)
	{
		s32				/*lnI, lnCount,*/ lnNumread, lnKeyAllocateCount;
		SDiskLock*		dl;
// 		SCdxKeyLeafRaw	key;
// 		STagRoot		tagRoot;
		bool			error;
		u32				errorNum;


		//////////
		// Remove any existing keys
		//////
			if (nodeKeys->keyDecodedAllocated != 0 || nodeKeys->keyDecodedBuffer)
				iiCdx_cacheNode_depopulate(wa, tagHeader, nodeKeys);


		//////////
		// If there isn't already a cached node, allocate it
		//////
			if (!nodeKeys->cachedNode)
				nodeKeys->cachedNode = (SCdxNode*)malloc(sizeof(SCdxNode));


		//////////
		// Load the node (LOL)
		//////
			if (nodeKeys->cachedNode)
			{

				//////////
				// Physical read from disk
				//////
					if (wa->isExclusive)		lnNumread = iDisk_read(wa->fhIdxCdxDcx, nodeKeys->nodeNum * 512, nodeKeys->cachedNode, 512, &error, &errorNum);
					else						lnNumread = iDisk_readShared_withRetryCallback(wa->idxCdxDcxFileLocks, wa->fhIdxCdxDcx, nodeKeys->nodeNum * 512, nodeKeys->cachedNode, 512, &error, &errorNum, (uptr)&iiDbf_continueWithLockOperation, (uptr)&dl, &dl, true);


				//////////
				// Are we good?
				//////
					if (error || lnNumread != 512)
					{
						// Failure
						free(nodeKeys->cachedNode);
						nodeKeys->cachedNode = NULL;
						return;
					}


				//////////
				// Calculate allocation space for key decoding
				//////
					if (!wa->isNoUpdate && tlAllocateLiberally)
					{

						//////////
						//
						// They want to allocate extra room for additional keys beyond the number present.
						//
						// Generally speaking, the maximum number of keys that can fit in a node is less
						// than 200, with a theoretical maximum of:
						//
						//		(((488 - keylength - 4) * (N)) / 8); where (N) is:  bits_RN + bits_DC + bits_TC
						//
						// A theoretically minimum of probably 5 bits total would be possible (depending on
						// the key length and key data per node) so that would yield about 300 keys max per
						// node.  Unlikely though.  Typically keys consume about 5 bytes each, and that yields
						// a maximum of fewer than 100 keys per node (on average) due to node data overhead.
						//
						// We'll use a simple algorithm (bits per key as it exists through the populated key
						// space in the node thus far, then extended out to all of key space, and rounded up
						// by 25% for wiggle room, with a minimum allocation value of 100 keys per node):
						//
						//		N = ((1.25 * 488) / (((488 - keylength- 4) - node->nodeFreeSpace) / node->keyCount))
						//
						//////
							lnKeyAllocateCount = max(100, (s32)((1.25f * 488.0f) / (((488.0f - (f32)tagHeader->keyLength - 4.0f) - (f32)nodeKeys->cachedNode->nodeFreeSpace) / (f32)nodeKeys->cachedNode->keyCount)));

					} else {
						// Allocate for the existing number of keys
						lnKeyAllocateCount = nodeKeys->cachedNode->keyCount;
					}


				//////////
				// Allocate
				//////
					nodeKeys->keyDecodedBuffer = (SCdxNodeKey**)malloc(lnKeyAllocateCount * sizeof(SCdxNodeKey));
					if (!nodeKeys->keyDecodedBuffer)
					{
						// Failure
						free(nodeKeys->cachedNode);
						nodeKeys->cachedNode = NULL;
						return;
					}


				//////////
				// Decode
				//////
// TODO:  Working here
// 					iCdx_getCompactRootNode(wa, tagHeader, NULL, &tagRoot);
// 					for (lnI = 0, lnCount = (s32)nodeKeys->cachedNode->keyCount; lnI < lnCount; lnI++)
// 					{
// 						if (!iCdx_getCompactIdxKey_byNumber(wa->cdx_root, tagHeader->keyLength, ->fillChar, lnKeyNumber, lnKeyNumber, node, &key, &tagRoot, true, true))
// 						{
//
// 						}
// 					}
			}

	}




//////////
//
// Called to depopulate the previously populated cached keys for the indicated node cache.
// This removes both the keys and the keyBuffer (because each node rarely has the exact
// same number of keys).
//
//////
	void iiCdx_cacheNode_depopulate(SWorkArea* wa, SCdxHeader* tagHeader, SCdxNodeCache* nodeKeys)
	{
		u32 lnI;


		//////////
		// Anything to free?
		//////
			if (nodeKeys->keyDecodedBuffer)
			{
				// Iterate through each SDatum, freeing its contents
				for (lnI = 0; lnI < (u32)nodeKeys->keyDecodedAllocated; lnI++)
				{
					// Free the key
					if (nodeKeys->keyDecodedBuffer[lnI]->key.data)
						iDatum_delete(&nodeKeys->keyDecodedBuffer[lnI]->key, false);
				}

				// Release the keyBuffer
				free(nodeKeys->keyDecodedBuffer);
				nodeKeys->keyDecodedBuffer = NULL;
			}


		//////////
		// Reset the count
		//////
			nodeKeys->keyDecodedAllocated = 0;

	}




//////////
//
// Called to delete the cached node's contents.  If tlImmediateReuse is true, then the node is not marked isUsed = false,
// but rather it is kept as isUsed = true so it doesn't need to be allocated again.
//
//////
	void iiCdx_cacheNode_delete(SWorkArea* wa, SCdxHeader* tagHeader, SCdxNodeCache* nodeKeys, bool tlImmediateReuse)
	{
	}




//////////
//
// Called to build the sequence of operations for accessing key components based on the index
// expression in keyExpression.  The operations are an array of elements which make accessing
// and creating keys very fast.
//
//////
	SCdxKeyOp* iiCdx_generateKey_buildOps(SWorkArea* wa, u8* keyExpression, s32* tnKeyOpCount)
	{
		s32			lnKeyLength, lnFieldLength, lnIndexLength, lnKeyFieldNameLength, lnLkoNum;
		sptr		lnFieldNumber;
		u32			lnFixup;
		u8*			keyStart;
		u8			fieldName[128];
		bool		llIsValid;
		SCdxKeyOp*	cko;


		//////////
		// Allocate for up to N ops
		//////
			cko = (SCdxKeyOp*)malloc(100 * sizeof(SCdxKeyOp));
			if (!cko)
				return(NULL);

			// Initialize
			memset(cko, 0, 100 * sizeof(SCdxKeyOp));


		// Iterate through each field grabbing the key data
		for (lnLkoNum = 0, lnKeyLength = 0, keyStart = keyExpression, lnFixup = _DBF_INDEX_FIXUP_NONE; *keyStart != 0; )
		{
			//////////
			// See if it's DELETED()
			//////
				llIsValid = false;
				if (_memicmp(keyStart, "deleted()", 9) == 0)
				{
					//////////
					// Add for the DELETED() flag
					//////
						lnKeyFieldNameLength		= 9;									// Length of the "DELETED()" text
						lnFieldLength				= 1;									// Always 1 byte per deleted() mark
						cko[lnLkoNum].offsetRow		= 0;									// The DELETED() tag is at offset 0 on all tables
						cko[lnLkoNum].offsetKey		= lnKeyLength;							// Where it goes in the key
						cko[lnLkoNum].length		= lnFieldLength;						// Always 1 byte per deleted() mark
						cko[lnLkoNum].fieldLength	= lnFieldLength;						// Always 1 byte per deleted() mark
						cko[lnLkoNum].indexFixup	= _DBF_INDEX_FIXUP_DELETED | lnFixup;	// Convert deleted byte to the logical test
						llIsValid					= true;

				} else if (_memicmp(keyStart, "upper(", 6) == 0) {
					// We add a fixup to everything between here and the closing parenthesis
					lnFieldLength			= 0;
					llIsValid				= true;
					lnKeyFieldNameLength	= 6;
					if (iiCdx_generateKey_buildOps_markClosingParenthesis(keyStart + 5, (s8)255))
						lnFixup = _DBF_INDEX_FIXUP_UPPER;

				} else if (_memicmp(keyStart, "lower(", 6) == 0) {
					// We add a fixup to everything between here and the closing parenthesis which performs an upper
					lnFieldLength			= 0;
					llIsValid				= true;
					lnKeyFieldNameLength	= 6;
					if (iiCdx_generateKey_buildOps_markClosingParenthesis(keyStart + 5, (s8)255))
						lnFixup = _DBF_INDEX_FIXUP_LOWER;

				} else if (*keyStart != 255) {
					//////////
					// Find out how long this key is
					//////
						lnKeyFieldNameLength = (s32)iDbf_getFieldExpression_name(keyStart, &fieldName[0]);
						if (lnKeyFieldNameLength < 1)
							goto failed_parsing;


					//////////
					// Locate this key in the current table
					//////
						lnFieldNumber = (sptr)iDbf_getField_byName2(wa, fieldName);
						if (lnFieldNumber <= 0)
							goto failed_parsing;


					//////////
					// Grab its length
					//////
						lnFieldLength = (s32)iDbf_getField_length(wa, (u32)lnFieldNumber, NULL, 0);
						lnIndexLength = (s32)iDbf_getIndex_length(wa, (u32)lnFieldNumber, NULL, 0);


					//////////
					// If the field allows NULLs, allow for that byte
					// Note:  The _DBF_INDEX_FIXUP_NULL is used for the index_fixup, so the content will be adjusted appropriately
					//////
						if (iDbf_getField_allowNulls(wa, (u32)lnFieldNumber, NULL, 0))
						{
							// Grab the offset and mask for rapid updating as we generate each field
							iDbf_getNull_offsetAndMask(wa, (u32)lnFieldNumber, &cko[lnLkoNum].null_offset, &cko[lnLkoNum].null_mask);
							++lnIndexLength;
						}


					//////////
					// Append the contents of this key to the op
					//////
						cko[lnLkoNum].offsetRow		= (u32)iDbf_getField_dataOffset(wa, (u32)lnFieldNumber);
						cko[lnLkoNum].offsetKey		= lnKeyLength;
						cko[lnLkoNum].length		= lnIndexLength;
						cko[lnLkoNum].fieldLength	= lnFieldLength;
						cko[lnLkoNum].indexFixup	= (u32)iDbf_getIndexFixupOp(wa, (u32)lnFieldNumber) | lnFixup;
						llIsValid					= true;

				} else {
					// Reset the fixup clause after the 255 termination mark
					lnFixup = _DBF_INDEX_FIXUP_NONE;
				}


				// If we're not on a
				if (llIsValid)
				{
					lnKeyLength	+= lnFieldLength;					// Move past the data stored for this key
					keyStart	+= lnKeyFieldNameLength;			// Move past this key in the key expression
					if (lnFieldLength > 0)
						++lnLkoNum;
				}


				//////////
				// Move past any fixups
				/////
					while (*keyStart == '+' || (u8)*keyStart == 255)
					{
						// Restore parenthesis
						if ((u8)*keyStart == 255)
							*keyStart = ')';

						// Move past this character
						++keyStart;
					}
		}

		// Indicate how long the key is
		*tnKeyOpCount = lnLkoNum;
		return(cko);


failed_parsing:
		free(cko);
		*tnKeyOpCount = -1;
		return(NULL);
	}

	bool iiCdx_generateKey_buildOps_markClosingParenthesis(u8* leftParenthesis, u8 fixupAscii)
	{
		s32 lnLevel;


		// Process to find the matching closing parenthesis
		lnLevel = -1;										// We are now at level -1
		++leftParenthesis;									// Move past opening (
		while (*leftParenthesis != 0)
		{
			// Where are we?
			if (*leftParenthesis == '(')
			{
				// Descending a level
				--lnLevel;

			} else if (*leftParenthesis == ')') {
				// Ascending up a level
				++lnLevel;
				if (lnLevel == 0)
				{
					// We've found our match
					*leftParenthesis = fixupAscii;
					return(true);
				}
			}

			// Move to next character
			++leftParenthesis;
		}

		// If we get here, not found
		return(false);
	}




//////////
//
// Called to generate a single key based on current DBF record, its current data (which may or may
// not be stale -- it is incumbent upon the caller here to know this), and the associated index
// header key directly.
//
//////
	u32 iiCdx_generateKey(SWorkArea* wa, SCdxHeader* head, u8* keyOut)
	{
		s32				lnKeyLength, lnFieldLength, lnKeyFieldNameLength;
		u8*				keyStart;
		u8				fieldName[128];
		SFieldRecord2*	lfptr2;


		// Iterate through each field grabbing the key data
		lnKeyLength	= 0;
		keyStart	= head->keyExpression;
		while (*keyStart != 0)
		{
			//////////
			// Find out how long this key is
			//////
				lnKeyFieldNameLength = (s32)iDbf_getFieldExpression_name(keyStart, &fieldName[0]);
				if (lnKeyFieldNameLength < 1)
					return(-1);


			//////////
			// Locate this key in the current table
			//////
				lfptr2 = iDbf_getField_byName2(wa, fieldName);
				if (!lfptr2)
					return(-2);

				// Grab its length
				lnFieldLength = lfptr2->length;


			//////////
			// Append the contents of this key
			//////
				iiDbf_getField_data2(wa, lfptr2->fieldNumber, keyOut, lnFieldLength, true);


			//////////
			// Move past the data stored for this key
			//////
				keyOut	+= lnFieldLength;
				lnKeyLength		+= lnFieldLength;


			//////////
			// Move past this key in the key expression
			//////
				keyStart += lnKeyFieldNameLength;
				if (*keyStart == '+')
					++keyStart;
		}

		// Indicate how long the key is
		return(lnKeyLength);
	}




//////////
//
// Called to populate the key by the data stored in the ops
//
//////
	void iiCdx_generateKey_byOps(SWorkArea* wa, SCdxKeyOp* keyOps, s32 tnKeyOpCount, u8* keyOut, bool tlBuildFromIndexData)
	{
		s32			lnI, lnJ;
		u8*			keyPart;
		SCdxKeyOp*	cko;
		s8*			dataSource;


		// Grab our data source
		dataSource = ((tlBuildFromIndexData) ? wa->irow.data : wa->row.data);

		// Iterate through each op at warp speed
		for (lnI = 0, cko = &keyOps[0]; lnI < tnKeyOpCount; lnI++, cko++)
		{
			// Peform the copy
			memcpy(keyOut + cko->offsetKey, dataSource + cko->offsetRow, cko->length);

			// Is there a fixup?
			if (cko->indexFixup)
			{
				// Get our pointer to this part of the key
				keyPart = keyOut + cko->offsetKey;

				// Apply the fixup
				switch (cko->indexFixup & _DBF_INDEX_FIXUP_MASK)
				{
					case _DBF_INDEX_FIXUP_SWAP_ENDIAN:
						// Fixup integers stored as 4-byte or 8-byte (currency)
						iiCdx_generateKey_byOps_fixup_swapEndian(cko, keyPart);
						break;

					case _DBF_INDEX_FIXUP_FLOAT_DOUBLE:
						// Fixup float or double
						iiCdx_generateKey_byOps_fixup_double(cko, keyPart);
						break;

					case _DBF_INDEX_FIXUP_DATETIME:
						// Fixup embedded float in datetime
						if ((keyPart[0] & 0x80) != 0)		keyPart[4] &= 0x7f;		// It is unsigned
						else								keyPart[4] |= 0x80;		// It is signed
						break;

					case _DBF_INDEX_FIXUP_LOGICAL:
						// Spaces stored on disk are converted to "F" for comparison in indexes because... that's how VFP does it
						if (keyPart[0] == 32)
							keyPart[0] = 'F';
						break;

					case _DBF_INDEX_FIXUP_DATE:
						// Dates are stored as Julian day numbers
						iiCdx_generateKey_byOps_fixup_date(cko, keyPart);
						// All done
						break;

					case _DBF_INDEX_FIXUP_DELETED:
						// Spaces stored on disk are converted to "F" for comparison in indexes because... that's how VFP does it
						if (keyPart[0] == 32)		keyPart[0] = 'F';
						else						keyPart[0] = 'T';
						break;

					case _DBF_INDEX_FIXUP_NUMERIC:
						// Numeric fields are converted to f64 for comparison
						iiCdx_generateKey_byOps_fixup_numeric(cko, keyPart, wa);
						break;
				}


				//////////
				// Perform explicit fixups
				//////
					if (cko->indexFixup & _DBF_INDEX_FIXUP_NULL)
					{
						// Scooch it over one byte
						memmove(keyPart + 1, keyPart, cko->length - 1);

						// Add in the NULL condition for this field
						*(u8*)keyPart = ((dataSource[cko->null_offset] & cko->null_mask) ? 0 : 0x80);
					}

					if (cko->indexFixup & _DBF_INDEX_FIXUP_UPPER)
					{
						// Convert the raw DBF data to upper-case
						for (lnJ = 0; lnJ < cko->length; lnJ++)
							iiUpperCase(keyPart + lnJ);
					}

					if (cko->indexFixup & _DBF_INDEX_FIXUP_LOWER)
					{
						// Convert the raw DBF data to lower-case
						for (lnJ = 0; lnJ < cko->length; lnJ++)
							iiLowerCase(keyPart + lnJ);
					}
			}
		}
	}

	void iiCdx_generateKey_byOps_fixup_swapEndian(SCdxKeyOp* lko, u8* keyPart)
	{
		switch (lko->length)
		{
			case 4: // s32 4-byte conversion
				*(u32*)keyPart = iiSwapEndian32(*(u32*)keyPart);
				break;

			case 8:	// s64 8-byte conversion
				*(u64*)keyPart = iiSwapEndian64(*(u64*)keyPart);
				break;
		}

		// Fixup the sign bit
		if ((keyPart[0] & 0x80) != 0)
		{
			// It is negative, make it positive
			switch (lko->length)
			{
				case 4: // s32 4-byte conversion
					*(u32*)keyPart = ~(*(u32*)keyPart);
					break;

				case 8:	// s64 8-byte conversion
					*(u64*)keyPart = ~(*(u64*)keyPart);
					break;
			}
			keyPart[0] &= 0x7f;

		} else {
			// Just make it positive, but with the sign bit flipped
			keyPart[0] |= 0x80;
		}
	}

	void iiCdx_generateKey_byOps_fixup_date(SCdxKeyOp* lko, u8* keyPart)
	{
		s32	lnI;
		s8	julianBuffer[16];

		if (memcmp(keyPart, "        ", 8) == 0)
		{
			// Date is blank, for this we use 0
			*(f64*)&julianBuffer[0] = 0.0;

		} else {
			// Compute Julian day number
			sprintf(julianBuffer, "%08u\0", iiJulianDayNumber_fromYyyyMmDd_s8(&keyPart[0], &keyPart[4], &keyPart[6]));
			*(f64*)&julianBuffer[0] = atof(julianBuffer);
		}

		if ((julianBuffer[7] & 0x80) != 0)
		{
			// It is negative, make it positive
			julianBuffer[7] &= 0x7f;

			// Reverse the string to store in big-endian format, while flipping all bits
			for (lnI = 0; lnI < 8; lnI++)
				keyPart[lnI] = !julianBuffer[7 - lnI];

		} else {
			// Just make it negative
			julianBuffer[7] |= 0x80;

			// Reverse the string to store in big-endian format
			for (lnI = 0; lnI < 8; lnI++)
				keyPart[lnI] = julianBuffer[7 - lnI];
		}
	}


	void iiCdx_generateKey_byOps_fixup_double(SCdxKeyOp* lko, u8* keyPart)
	{
		switch (lko->length)
		{
			case 4: // s32 4-byte conversion
				*(u32*)keyPart = iiSwapEndian32(*(u32*)keyPart);
				break;

			case 8:	// s64 8-byte conversion
				*(u64*)keyPart = iiSwapEndian64(*(u64*)keyPart);
				break;
		}

		if ((keyPart[0] & 0x80) != 0)
		{
			// It is signed, flip all bits
				 if (lko->length == 4)		*(u32*)keyPart = ~(*(u32*)keyPart);
			else if (lko->length == 8)		*(u64*)keyPart = ~(*(u64*)keyPart);

			// Mask off sign bit
			keyPart[0] &= 0x7f;

		} else {
			// It is unsigned, flip only the sign it
			keyPart[0] |= 0x80;
		}
	}

	void iiCdx_generateKey_byOps_fixup_numeric(SCdxKeyOp* lko, u8* keyPart, SWorkArea* wa)
	{
		s8 numericBuffer[256];


		//////////
		// Copy the entire numeric field contents
		//////
			memcpy(numericBuffer, wa->row.data + lko->offsetRow, lko->fieldLength);
			numericBuffer[lko->fieldLength] = 0;


		//////////
		// Grab it as an f64
		//////
			*(f64*)keyPart = atof(numericBuffer);


		//////////
		// Fixup per the normal double swap endian
		//////
			iiCdx_generateKey_byOps_fixup_double(lko, keyPart);
	}






//////////
//
// Called to apply the fixup on the indicated key (if any).
// Note:  This will undo a previous fixup to obtain the true value in it's natural form for
//         little-endian machines (like Intel's CPUs).
//
// Typical flow:
//		(1) iiCdx_generateKey_byOps() to generate keys
//		(2) Sort
//		(3) iiCdx_generateKey_byOps_fixup() to restore the key values to their usable form
//
// If used on CDX index keys, only certain operations are performed, so use tlIsCdxKey = true.
//
//////
	bool iiCdx_generateKey_byOps_fixup(SWorkArea* wa, SCdxKeyOp* keyOps, s32 tnKeyOpCount, u8* keyOut, bool tlIsCdxKey)
	{
		s32		lnI, lnJ;
		bool	llAnyFixupApplied;	// used for early-out by the caller
		u8*		keyPart;
		s8		julianBuffer[16];


		// Iterate through every op and apply any fixups
		for (lnI = 0, llAnyFixupApplied = false; lnI < tnKeyOpCount; lnI++)
		{
			// Is there a fixup?
			if (keyOps[lnI].indexFixup != _DBF_INDEX_FIXUP_NONE)
			{
				// Raise the flag
				llAnyFixupApplied = true;

				// Get our pointer to this part of the key
				keyPart = keyOut + keyOps[lnI].offsetKey;

				// Apply the fixup
				switch (keyOps[lnI].indexFixup & _DBF_INDEX_FIXUP_MASK)
				{
					case _DBF_INDEX_FIXUP_SWAP_ENDIAN:
						// Fixup integers stored as 4-byte or 8-byte (currency)
						if (tlIsCdxKey)
						{
							// CDX keys already have this done during their extraction-from-the-CDX-node algorithm
							// It's a requirement that it be done at that time because successive keys in a compact node use all of the prior bits, with only some of them adjusted.

						} else {
							// DBF-generated keys need this fixup performed
							if ((keyPart[0] & 0x80) == 0)
							{
								// It was negative, flip all bits
								*(u32*)keyPart = ~(*(u32*)keyPart);
								keyPart[0] |= 0x80;

							} else {
								// It was positive, flip only the sign it
								keyPart[0] &= 0x7f;
							}

							switch (keyOps[lnI].length)
							{
								case 4: // s32 4-byte conversion
									*(u32*)keyPart = iiSwapEndian32(*(u32*)keyPart);
									break;

								case 8:	// s64 8-byte conversion
									*(u64*)keyPart = iiSwapEndian64(*(u64*)keyPart);
									break;
							}
						}
						break;

					case _DBF_INDEX_FIXUP_FLOAT_DOUBLE:
					case _DBF_INDEX_FIXUP_NUMERIC:
						// Fixup float, double, or numeric
						if (!tlIsCdxKey || (keyOps[lnI].indexFixup & _DBF_INDEX_FIXUP_MASK) == _DBF_INDEX_FIXUP_NUMERIC)
						{
							// DBF format
							if ((keyPart[0] & 0x80) == 0)
							{
								// It was unsigned, flip all bits
									 if (keyOps[lnI].length == 4)		*(u32*)keyPart = ~(*(u32*)keyPart);
								else if (keyOps[lnI].length == 8)		*(u64*)keyPart = ~(*(u64*)keyPart);

								// It was signed, put the sign back on
								keyPart[0] |= 0x80;

							} else {
								// Mask off sign bit
								keyPart[0] &= 0x7f;
							}

							switch (keyOps[lnI].length)
							{
								case 4: // s32 4-byte conversion
									*(u32*)keyPart = iiSwapEndian32(*(u32*)keyPart);
									break;

								case 8:	// s64 8-byte conversion
									*(u64*)keyPart = iiSwapEndian64(*(u64*)keyPart);
									break;
							}
						}

						// For some reason, VFP will fill the values with ASCII-32 characters
						if (tlIsCdxKey)
						{
							// Convert all 0x20 to 0x00
							for (lnJ = 0; lnJ < keyOps[lnI].length && keyPart[lnJ] == 0x20; lnJ++)
								keyPart[lnJ] = 0;
						}
						break;

					case _DBF_INDEX_FIXUP_DATETIME:
						// Fixup embedded float in datetime
						if ((keyPart[0] & 0x80) != 0)		keyPart[4] &= 0x7f;		// It is unsigned
						else								keyPart[4] |= 0x80;		// It is signed
						break;

					case _DBF_INDEX_FIXUP_LOGICAL:
						// Spaces stored on disk are converted to "F" for comparison in indexes because... that's how VFP does it
						if (keyPart[0] == 32)
							keyPart[0] = 'F';
						break;

					case _DBF_INDEX_FIXUP_DATE:
						// Dates are stored as Julian day numbers
						memcpy(julianBuffer, keyPart, 8);
						if ((julianBuffer[7] & 0x80) != 0)
						{
							// Reverse the string from big-endian format, while flipping all bits
							for (lnI = 0; lnI < 8; lnI++)
								keyPart[lnI] = !keyPart[7 - lnI];

							// Just make it negative
							keyPart[7] |= 0x80;

						} else {
							// Reverse the string from big-endian format
							for (lnI = 0; lnI < 8; lnI++)
								keyPart[lnI] = julianBuffer[7 - lnI];

							// It is negative, make it positive and flip all bits
							keyPart[7] &= 0x7f;
						}

						// Trim off any components after the decimal
						*(f64*)&keyPart[0] = (f64)((s64)(*(f64*)&keyPart[0]));

					case _DBF_INDEX_FIXUP_DELETED:
						// Spaces stored on disk are converted to "F" for comparison in indexes because... that's how VFP does it
						if (keyPart[0] == 32 || keyPart[0] == 'F')		keyPart[0] = 'F';
						else											keyPart[0] = 'T';
				}

				// Fixup for NULL index keys
				if (!tlIsCdxKey && (keyOps[lnI].indexFixup & _DBF_INDEX_FIXUP_NULL))
				{
					// If the value is 0x80, it's not .NULL.
					if (*keyPart == 0)
					{
						// It is .NULL., so make everything 0s
						memset(keyPart + 1, 0, keyOps[lnI].length - 1);
					}
				}
			}
		}

		// Indicate if there are any fixups here
		return(llAnyFixupApplied);
	}




//////////
//
// Called to obtain or create the buildOps for the indicated index tag.
//
//////
	bool iiCdx_get_buildOps(SWorkArea* wa, s32 tnTagIndex, SCdxHeader* tagHeader, SForClause** tsFor, SCdxKeyOp** tsKeyOp, u32* tnKeyOpCount, u32* tnResult)
	{
		//////////
		// Are we trying to access a key beyond what we have?
		//////
			if (tnTagIndex > _MAX_CDX_TAGS)
			{
				// We do not have facilities for this
				*tnResult = -1;
				return(false);
			}


		//////////
		// If we already have computed the FOR clause test, and the key ops, then use that
		//////
			if (wa->cdx_keyOps[tnTagIndex].forClause == NULL || wa->cdx_keyOps[tnTagIndex].keyOps == NULL)
			{
				//////////
				// Indexes with complex FOR clauses are not currently supported.
				// Only those which are simple logical field tests are supported.
				//////
					if (!wa->cdx_keyOps[tnTagIndex].forClause)
					{
						if (iCdx_isForClauseComplex(wa, tagHeader, &wa->cdx_keyOps[tnTagIndex].forClause))
						{
							*tnResult = -2;		// FOR clause is too complex
							return(false);
						}
					}


				//////////
				// Generate DBF keys based on raw table data
				//////
					wa->cdx_keyOps[tnTagIndex].keyOps = iiCdx_generateKey_buildOps(wa, &tagHeader->keyExpression[0], &wa->cdx_keyOps[tnTagIndex].keyOpCount);
					if (!wa->cdx_keyOps[tnTagIndex].keyOps)
					{
						*tnResult = -3;		// Key expression could not be parsed
						return(false);
					}
			}


		//////////
		// We have what we need
		//////
			*tsFor			= wa->cdx_keyOps[tnTagIndex].forClause;
			*tsKeyOp		= wa->cdx_keyOps[tnTagIndex].keyOps;
			*tnKeyOpCount	= wa->cdx_keyOps[tnTagIndex].keyOpCount;
			*tnResult		= 0;

			// Success
			return(true);
	}




//////////
//
// Called to traverse the indicated CDX tag root looking for the key.  This is the fastest find
// possible for finding a key in a CDX.  It performs a binary search on the key nodes, and then
// examines the first key on each node within the range to see which of the nodes the key must
// reside in.  It then decodes only that node to find the first key which matches.  If it's
// found in the first position, then the previous node is searched to see if the first matching
// record actually begins on that node.
//
// If found, it returns the record number.
// If not found, it returns _CDX_NO_FIND.
//
//////
	s32 iCdx_findKey(SWorkArea* wa, STagRoot* tagRoot, u8* keyBuffer, u32 tnKeyLength)
	{
		s32				lnTranslatedResult;
		u32				lnKeyNumber;
		SCdxNode*		node;
		SCdxKeyLeafRaw	key;


debug_break;
		//////////
		// Find the node it relates to
		//////
			node		= iCdx_getCompactIdxNode_byOffset(wa->cdx_root, tagRoot->highestNode);
			tnKeyLength	= max(min(tnKeyLength, tagRoot->keyLength), 1);
			while (node)
			{
				switch (iiGetIndexNodeType(node->type))
				{
					case _CDX_NODE_INDEX:	// Index node, pointing to other sub-indexes
					case _CDX_NODE_ROOT:	// Root node, pointing to other sub-indexes
						// Index node
						// Index nodes point to other index nodes, or leaf nodes, but not to actual terminal keys
						for (lnKeyNumber = 0; lnKeyNumber < node->keyCount; lnKeyNumber++)
						{
							// See if this key is beyond the thing we're searching for, if so then the candidate key is the previous one
							if (iCdx_getCompactIdxKey_byNumber(wa->cdx_root, tagRoot->keyLength, tagRoot->fillChar, lnKeyNumber, lnKeyNumber, node, &key, tagRoot, true, true))
							{
								//////////
								// See if this key is beyond us.
								// Refer to the cdx_logic.txt for information on this algorithm.
								//////
									if (iiCdx_translateActualResultThroughIndexOrder(tagRoot, keyBuffer, &key.key[0], tnKeyLength) <= 0)
									{
										// We've reached (=) or passed where the key should've been
										node = iCdx_getCompactIdxNode_byOffset(wa->cdx_root, key.fileOffset);
									}
									// else
									// We are continuing with the next index node key in the for loop

							} else {
								// Should never happen
								debug_break;
								break;
							}
						}
						// If we get here, the match wasn't found on this node, move to the next node (below)
						break;

					case _CDX_NODE_LEAF:		// Leaf
					case _CDX_NODE_ROOT_LEAF:	// Root, and leaf
						// Leaf node
						// Leaf nodes point to terminal keys
						for (lnKeyNumber = 0; lnKeyNumber < node->keyCount; lnKeyNumber++)
						{
							// Get the first key on this node
							if (iCdx_getCompactIdxKey_byNumber(wa->cdx_root, tagRoot->keyLength, tagRoot->fillChar, lnKeyNumber, 0, node, &key, tagRoot, true, true))
							{
								//////////
								// See if this key is beyond us.
								// Refer to the cdx_logic.txt for information on this algorithm.
								//////
									if ((lnTranslatedResult = iiCdx_translateActualResultThroughIndexOrder(tagRoot, keyBuffer, &key.key[0], tnKeyLength)) == 0)
									{
										// We found the key
										return(key.recordNumber);

									} else if (lnTranslatedResult < 0) {
										// We've passed where the key should've been
										// This means no find
										return(_CDX_FIND_NO);
									}

							} else {
								// Should not happen
								debug_break;
								break;
							}
						}
						break;
				}

				// Move to next node
				if (node->nodeRight != (u32)-1)
				{
					// Grab that node and continue
					node = iCdx_getCompactIdxNode_byOffset(wa->cdx_root, node->nodeRight);

				} else {
					// Nothing else to search
					break;
				}
			}


		//////////
		// If we get here, indicate no find
		//////
			return(_CDX_FIND_NO);
	}




//////////
//
// Called to position the record pointer of a CDX.
//
//////
	s32 iCdx_gotoTop(SWorkArea* wa)
	{
		// Make sure the index is loaded
		if (wa->isIndexLoaded)
		{
			// Is it an idx?
			if (!wa->isCdx)
				return(iIdx_gotoTop(wa));

			// If we get here, it is a cdx
// TODO:  Write this algorithm
		}

		// If we get here, no index
		return(-1);
	}

	s32 iCdx_skip(SWorkArea* wa, s32 tnDelta)
	{
		// Make sure the index is loaded
		if (wa->isIndexLoaded)
		{
			// Is it an idx?
			if (!wa->isCdx)
				return(iIdx_skip(wa, tnDelta));

			// If we get here, it is a cdx
// TODO:  Write this algorithm
		}

		// If we get here, no index
		return(-1);
	}

	s32 iCdx_gotoBottom(SWorkArea* wa)
	{
		// Make sure the index is loaded
		if (wa->isIndexLoaded)
		{
			// Is it an idx?
			if (!wa->isCdx)
				return(iIdx_gotoBottom(wa));

			// If we get here, it is a cdx
// TODO:  Write this algorithm
		}

		// If we get here, no index
		return(-1);
	}




//////////
//
// Called to position the record pointer of a IDX.
//
//////
	s32 iIdx_gotoTop(SWorkArea* wa)
	{
		// Is an index loaded?
		if (wa->isIndexLoaded)
		{
			// Is it an idx?
			if (wa->isCdx)
				return(iCdx_gotoTop(wa));

			// If we get here, it is a cdx
// TODO:  Write this algorithm
		}

		// If we get here, no index
		return(-1);
	}

	s32 iIdx_skip(SWorkArea* wa, s32 tnDelta)
	{
		// Is an index loaded?
		if (wa->isIndexLoaded)
		{
			// Is it an idx?
			if (wa->isCdx)
				return(iCdx_skip(wa, tnDelta));

			// If we get here, it is a cdx
// TODO:  Write this algorithm
		}

		// If we get here, no index
		return(-1);
	}

	s32 iIdx_gotoBottom(SWorkArea* wa)
	{
		// Is an index loaded?
		if (wa->isIndexLoaded)
		{
			// Is it an idx?
			if (wa->isCdx)
				return(iCdx_gotoBottom(wa));

			// If we get here, it is a cdx
// TODO:  Write this algorithm
		}

		// If we get here, no index
		return(-1);
	}





//////////
//
// Comparison result tree for ascending and descending indexes:
//
//															  Meaning for:
//		  Left		 Right		actual				--------------------------------
//		KeyBuffer	key.key		result				ascending			 descending
//		---------	-------		------				------------		------------
//			f		   a		  >					greater than		less than
//			f		   f		  =					equal				equal
//			f		   z		  <					less than			greater than
//
// Note:	For ascending, it is the same.
// Note:	For descending, less than and greater than are reversed.
//
//////
	s32 iiCdx_translateActualResultThroughIndexOrder(STagRoot* tagRoot, u8* keyLeft, u8* keyRight, u32 tnKeyLength)
	{
		s32 lnActualResult, lnTranslatedResult;


		//////////
		// Perform the compare
		//////
			lnActualResult = memcmp(keyLeft, keyRight, tnKeyLength);


		//////////
		// Analyze the result as per the index order
		//////
			if (tagRoot->indexIsDesc)
			{
				// We are in a descending index
				// Actual result is reversed
				if (lnActualResult > 0)
				{
					// Reverse it to < 0
					lnTranslatedResult = -1;

				} else if (lnActualResult < 0) {
					// Reverse it to > 0
					lnTranslatedResult = 1;

				} else {
					// It is equal, and does not need translated
					lnTranslatedResult = lnActualResult;
				}

			} else {
				// It is an ascending order index, and the results of memcmp() by itself are proper and do not need translated
				lnTranslatedResult = lnActualResult;
			}


		//////////
		// Indicate the translated result through the sort order
		//////
			return(lnTranslatedResult);
	}




//////////
//
// Returns all keys for an index into a contiguous string that can be extracted in VFP using
// the tcDecodeExpression source code to obtain the parts.
//
// The decode expression should be executed in VFP like this:
//
//		PUBLIC lxKey, lnI, lcKeys, lnKeyRecno
//		LOCAL lnTagNum, lcDecode, lcKeyLength, lnKeyCount
//
//		lnTagNum	= 0		&& Tag 0 is the first tag
//		lcKeys		= SPACE(RECCOUNT() * (FSIZE(lcKeyField) + 4))	&& Allocate enough space for all keys
//		lcDecode	= SPACE(2048)
//		lcKeyLength	= SPACE(3)
//		lnKeyCount	= cdx_get_all_keys(lnHandle, lnTagNum, @lcKeys, LEN(lcKeys), @lcDecode, LEN(lcDecode), @lcKeyLength3)
//
//		CREATE CURSOR c_keyData ;
//		( ;
//			key		i, ;
//			record	i ;
//		)
//
//		* Iterate to obtain each keys
//		FOR lnI = 1 TO lnKeyCount
//			* Break out the expression (Note: The returned code expressly needs lcKeys and lnI.  If you need to use different variables, use something like lcDecode = STRTRAN(lcDecode, "lnI", "myNewIterator"))
//			EXECSCRIPT(lcDecode)
//
//			* Right now:
//			*	(1) lxKey		= the actual key itself.  Use TYPE("lxKey") to determine what it is.
//			*	(2) lnKeyRecno	= the record number for this key
//
//			*INSERT INTO c_keyData (key, record) VALUES(lxKey, lnKeyRecno)
//		NEXT
//
// The decode expression for an integer key field will be these two lines of code, for example:
//		lxKey      = CTOBIN(SUBSTR(lcKeys, 1 + (((lnI-1) * 8) + 0), 4), "4")		&& Obtains the key as an encoded integer
//		lnKeyRecno = CTOBIN(SUBSTR(lcKeys, 1 + (((lnI-1) * 8) + 4), 4), "4")		&& Obtains the record number as an encoded integer
//
//////
	u32 iCdx_getAllKeysCdx(SWorkArea* wa, s32 tnTagIndex, u8* tcKeySpace, u32 tnKeySpaceLength, u8* tcDecodeExpression, u32 tnDecodeExpressionLength, s8* tcKeyLength4)
	{
		u32				lnKeyNumber, lnTotalKeyCount;
		SCdxNode*		node;
		SCdxKeyLeafRaw	key;
		STagRoot		tagRoot;
		u8				buffer[256];
		SBuilder*		keys;


		//////////
		// Get common pointers
		//////
			iBuilder_createAndInitialize(&keys, -1);


		//////////
		// Process the indicated tag
		//////
			lnTotalKeyCount	= 0;
			memset(&tagRoot, 0, sizeof(tagRoot));
			if (iCdx_getRootmostCompoundTag_byTagnum(wa, wa->cdx_root, NULL, tnTagIndex, &tagRoot))
			{
				//////////
				// Iterate through the keys
				//////
					node = iCdx_getCompactIdxNode_byOffset(wa->cdx_root, tagRoot.leftmostNode);
					while (node)
					{
						// Iterate through every key for this node
						if (node->keyCount != 0)
						{
							// Convey the keys
							for (lnKeyNumber = 0; lnKeyNumber < node->keyCount; lnKeyNumber++)
							{
								// Get the key here
								if (iCdx_getCompactIdxKey_byNumber(wa->cdx_root, tagRoot.keyLength, tagRoot.fillChar, lnKeyNumber, lnKeyNumber, node, &key, &tagRoot, true, true))
								{
									// Indicate our key count has gone up
									++lnTotalKeyCount;
									iBuilder_appendData(keys, &key.key[0],				key.keyLength);		// Append key
									iBuilder_appendData(keys, (cu8*)&key.recordNumber,	4);					// Append record number

								} else {
									// Should not happen
									debug_break;
									break;
								}
							}
						}

						// Move to next node
						if (node->nodeRight == (u32)-1)
							break;	// All done

						// Move to the next lead node right and continue through the keys
						node = iCdx_getCompactIdxNode_byOffset(wa->cdx_root, node->nodeRight);
					}
			}


			if (lnTotalKeyCount != 0)
			{
			//////////
			// Copy the data back
			//////
				if (tcKeySpace)
				{
					memset(tcKeySpace, 32, tnKeySpaceLength);
					memcpy(tcKeySpace, keys->buffer, min(tnKeySpaceLength, keys->populatedLength));
				}

				// Key length
				if (tcKeyLength4)
					sprintf(tcKeyLength4, "%04u", tagRoot.keyLength);


			//////////
			// Determine what the expression should be
			//////
				iBuilder_reset(keys);
				if (tagRoot.fillChar == 0 && (tagRoot.keyLength == 4 || tagRoot.keyLength == 8) && tagRoot.swapEndians)
				{
					// Extract as integers
					sprintf((s8*)buffer, "lxKey      = CTOBIN(SUBSTR(lcKeys, 1 + (((lnI-1) * (4 + 4)) + 0), 4), '4rs')     && Obtains the key as an encoded integer\r\n\0");
					iBuilder_appendData(keys, buffer, -1);
					sprintf((s8*)buffer, "lnKeyRecno = CTOBIN(SUBSTR(lcKeys, 1 + (((lnI-1) * (4 + 4)) + 4), 4), '4rs')     && Obtains the record number as an encoded integer\r\n\0");
					iBuilder_appendData(keys, buffer, -1);

				} else {
					// Extract as character
					sprintf((s8*)buffer, "lxKey      = SUBSTR(lcKeys, 1 + (((lnI-1) * (4 + %u)) + 0), %u)                  && Obtains the key as a string\r\n\0", tagRoot.keyLength, tagRoot.keyLength);
					iBuilder_appendData(keys, buffer, -1);
					sprintf((s8*)buffer, "lnKeyRecno = CTOBIN(SUBSTR(lcKeys, 1 + (((lnI-1) * (4 + %u)) + %u), 4), '4rs')   && Obtains the record number as an encoded integer\r\n\0", tagRoot.keyLength, tagRoot.keyLength);
					iBuilder_appendData(keys, buffer, -1);
				}
				if (tcDecodeExpression)
				{
					memset(tcDecodeExpression, 32, tnDecodeExpressionLength);
					memcpy(tcDecodeExpression, keys->buffer, min(tnDecodeExpressionLength, keys->populatedLength));
				}
			}


		//////////
		// Clean house
		//////
			iBuilder_freeAndRelease(&keys);


		//////////
		// If we found no errors, indicate success
		//////
			return(lnTotalKeyCount);
	}




///////////
//
// Returns all keys for an index into a contiguous string that can be extracted in VFP using
// the tcDecodeExpression source code to obtain the parts.
//
// The decode expression should be executed in VFP like this:
//
//		PUBLIC lxKey, lnI, lcKeys, lnKeyRecno
//		LOCAL lnTagNum, lcDecode, lcKeyLength, lnKeyCount
//
//		lnTagNum	= 0		&& Tag 0 is the first tag
//		lcKeys		= SPACE(RECCOUNT() * (FSIZE(lcKeyField) + 4))	&& Allocate enough space for all keys
//		lcDecode	= SPACE(2048)
//		lcKeyLength	= SPACE(3)
//		* Note:  For an IDX file, the tagnum is required, but its value is ignored
//		lnKeyCount	= cdx_get_all_keys(lnHandle, lnTagNum, @lcKeys, LEN(lcKeys), @lcDecode, LEN(lcDecode), @lcKeyLength3)
//
//		CREATE CURSOR c_keyData ;
//		( ;
//			key		i, ;
//			record	i ;
//		)
//
//		* Iterate to obtain each keys
//		FOR lnI = 1 TO lnKeyCount
//			* Break out the expression (Note: The returned code expressly needs lcKeys and lnI.  If you need to use different variables, use something like lcDecode = STRTRAN(lcDecode, "lnI", "myNewIterator"))
//			EXECSCRIPT(lcDecode)
//
//			* Right now:
//			*	(1) lxKey		= the actual key itself.  Use TYPE("lxKey") to determine what it is.
//			*	(2) lnKeyRecno	= the record number for this key
//
//			*INSERT INTO c_keyData (key, record) VALUES(lxKey, lnKeyRecno)
//		NEXT
//
// The decode expression for an integer key field will be these two lines of code, for example:
//		lxKey      = CTOBIN(SUBSTR(lcKeys, (lnI * 8) + 0, 4), "4")		&& Obtains the key as an encoded integer
//		lnKeyRecno = CTOBIN(SUBSTR(lcKeys, (lnI * 8) + 4, 4), "4")		&& Obtains the record number as an encoded integer
//
//////
	u32 iCdx_getAllKeysIdx(SWorkArea* wa, u8* tcKeySpace, u32 tnKeySpaceLength, u8* tcDecodeExpression, u32 tnDecodeExpressionLength, s8* tcKeyLength4)
	{
		u32					lnKeyNumber, lnTotalKeyCount;
		bool				llResult;
		union {
			SCdxHeader*		headCdx;
			SIdxHeader*		headIdx;
		};
		union {
			SCdxNode*		nodeCdx;
			SIdxNode*		nodeIdx;
		};
		union {
			SCdxKeyLeafRaw	keyCdx;
			SIdxKey			keyIdx;
		};
		STagRoot			tagRoot;
		u8					buffer[256];
		SBuilder*			keys;


		//////////
		// Get common pointers
		//////
			if (wa->isIdxCompact)		headCdx = wa->cdx_root;		// Header is first part of file
			else						headIdx = wa->idx_header;
			iBuilder_createAndInitialize(&keys, -1);


		//////////
		// Process the indicated tag
		//////
			lnTotalKeyCount	= 0;
			memset(&tagRoot, 0, sizeof(tagRoot));

			// Based on the type, retrieve the result
			if (wa->isIdxCompact)		llResult = iCdx_getCompactRootNode( wa, headCdx, NULL, &tagRoot);
			else						llResult = iCdx_getStandardRootNode(wa, headIdx, NULL, &tagRoot);

			// Are we good?
			if (llResult)
			{
				//////////
				// Iterate through the keys
				//////
					// Based on type, retrieve the node
					if (wa->isIdxCompact)		nodeCdx = iCdx_getCompactIdxNode_byOffset( headCdx, tagRoot.leftmostNode);
					else						nodeIdx = iCdx_getStandardIdxNode_byOffset(headIdx, tagRoot.leftmostNode);

					// Process so long as there are nodes
					while (nodeCdx)
					{
						// Iterate through every key for this node
						if (nodeCdx->keyCount != 0)
						{
							// Convey the keys
							for (lnKeyNumber = 0; lnKeyNumber < nodeCdx->keyCount; lnKeyNumber++)
							{
								// Based on the type, get the key
								if (wa->isIdxCompact)		llResult = iCdx_getCompactIdxKey_byNumber( headCdx, tagRoot.keyLength, tagRoot.fillChar, lnKeyNumber, lnKeyNumber, nodeCdx, &keyCdx, &tagRoot, true, true);
								else						llResult = iCdx_getStandardIdxKey_byNumber(headIdx,                    tagRoot.fillChar,              lnKeyNumber, nodeIdx, &keyIdx, &tagRoot, true, true);

								// Get the key here
								if (llResult)
								{
									// Indicate our key count has gone up
									++lnTotalKeyCount;
									if (wa->isIdxCompact)
									{
										// Compact
										iBuilder_appendData(keys, &keyCdx.key[0],				keyCdx.keyLength);		// Append key
										iBuilder_appendData(keys, (cu8*)&keyCdx.recordNumber,	4);					// Append record number

									} else {
										// Standard
										iBuilder_appendData(keys, &keyIdx.key[0],				keyIdx.keyLength);		// Append key
										iBuilder_appendData(keys, (cu8*)&keyIdx.record,			4);						// Append record number
									}

								} else {
									// Should not happen
									debug_break;
									break;
								}
							}
						}

						// Move to next node
						if (nodeCdx->nodeRight == (u32)-1)
							break;	// All done

						// Move to the next lead node right and continue through the keys
						if (wa->isIdxCompact)		nodeCdx = iCdx_getCompactIdxNode_byOffset( headCdx, nodeCdx->nodeRight);
						else						nodeIdx = iCdx_getStandardIdxNode_byOffset(headIdx, nodeIdx->nodeRight);
					}
			}


			if (lnTotalKeyCount != 0)
			{
			//////////
			// Copy the data back
			//////
				if (tcKeySpace)
				{
					memset(tcKeySpace, 32, tnKeySpaceLength);
					memcpy(tcKeySpace, keys->buffer, min(tnKeySpaceLength, keys->populatedLength));
				}

				// Key length
				if (tcKeyLength4)
					sprintf(tcKeyLength4, "%04u", tagRoot.keyLength);


			//////////
			// Determine what the expression should be
			//////
				iBuilder_reset(keys);
				if (tagRoot.fillChar == 0 && (tagRoot.keyLength == 4 || tagRoot.keyLength == 8) && tagRoot.swapEndians)
				{
					// Extract as integers
					sprintf((s8*)buffer, "lxKey      = CTOBIN(SUBSTR(lcKeys, 1 + (((lnI-1) * (4 + 4)) + 0), 4), '4rs')     && Obtains the key as an encoded integer\r\n\0");
					iBuilder_appendData(keys, buffer, -1);
					sprintf((s8*)buffer, "lnKeyRecno = CTOBIN(SUBSTR(lcKeys, 1 + (((lnI-1) * (4 + 4)) + 4), 4), '4rs')     && Obtains the record number as an encoded integer\r\n\0");
					iBuilder_appendData(keys, buffer, -1);

				} else {
					// Extract as character
					sprintf((s8*)buffer, "lxKey      = SUBSTR(lcKeys, 1 + (((lnI-1) * (4 + %u)) + 0), %u)                  && Obtains the key as a string\r\n\0", tagRoot.keyLength, tagRoot.keyLength);
					iBuilder_appendData(keys, buffer, -1);
					sprintf((s8*)buffer, "lnKeyRecno = CTOBIN(SUBSTR(lcKeys, 1 + (((lnI-1) * (4 + %u)) + %u), 4), '4rs')   && Obtains the record number as an encoded integer\r\n\0", tagRoot.keyLength, tagRoot.keyLength);
					iBuilder_appendData(keys, buffer, -1);
				}
				if (tcDecodeExpression)
				{
					memset(tcDecodeExpression, 32, tnDecodeExpressionLength);
					memcpy(tcDecodeExpression, keys->buffer, min(tnDecodeExpressionLength, keys->populatedLength));
				}
			}


		//////////
		// Clean house
		//////
			iBuilder_freeAndRelease(&keys);


		//////////
		// If we found no errors, indicate success
		//////
			return(lnTotalKeyCount);
	}




//////////
//
// Called to set the active index tag to the indicated tag number / index.
//
//////
	bool iCdx_setActiveTag(SWorkArea* wa, s32 tnTagIndex, STagRoot* tagRoot, bool* tlError, u32* tnErrorNum)
	{
		// Make sure our environment is sane
		if (wa && tagRoot)
		{
			// Is it a valid work area?
			if (iDbf_isWorkAreaValid(wa, NULL) && wa->isUsed)
			{
				// Is there an index loaded?
				if (wa->isIndexLoaded && wa->isCdx)
				{
					// Try to access the indicated tag
					*tlError = !iCdx_getRootmostCompoundTag_byTagnum(wa, wa->cdx_root, NULL, tnTagIndex, tagRoot);
					if (*tlError)
					{
						// Error accessing the index tag
						*tnErrorNum = _ERROR_INVALID_INDEX_TAG;

					} else {
						// We're good
						*tnErrorNum = _ERROR_OKAY;
						return(true);
					}

				} else {
					// No CDX is loaded
					*tlError	= true;
					*tnErrorNum	= _ERROR_NO_INDEX_IS_LOADED;
				}

			} else {
				// Work area is not in use
				*tlError	= true;
				*tnErrorNum	= _ERROR_INVALID_WORK_AREA;
			}

		} else {
			// Invalid parameters
			*tlError	= true;
			*tnErrorNum	= _ERROR_INTERNAL_ERROR;
		}

		// If we get here, parameter error
		return(false);
	}




//////////
//
// Called to get the indicated tag number's root node.  The tags are stored at the first non-header node
// (offset 1536) and can spill over into other nodes if there are many tags.
//
// A test with over 5,000 tags indicated the index's own tag system is its own index within the index.
// It uses the same logic to find the tag as it does to search keys within a tag.  There is no specific
// reason why index tag name lengths can't be larger than 10 characters.  It seems to be merely convention.
//
//////
	bool iCdx_getRootmostCompoundTag_byTagnum(SWorkArea* wa, SCdxHeader* head, SCdxNode* node, s32 lnTagNum, STagRoot* tagRoot)
	{
		SCdxKeyLeafRaw	key;
		SCdxHeader*		nodeTag;
		SCdxNode*		nodeFirst;


		//////////
		// Make sure our environment is sane
		//////
			// Work area
			if (!wa)
				return(false);

			// CDX
			if (!head)
			{
				// Invalid header
				wa->idxCdxDcxLastError = _CDX_ERROR_INVALID_INDEX;	// Note:  Could possibly be an internal programmer error
				return(false);
			}

			// Current node
			if (!node && !iCdx_cacheNode(wa, head, 3, &node))
			{
				// Node is not available
				wa->idxCdxDcxLastError = _CDX_ERROR_INVALID_NODE;
				return(false);
			}


		// Based on the type of node we will traverse appropriately
		while (node)
		{
			switch (node->type)
			{
				case _CDX_NODE_INDEX:	// Index node, pointing to other sub-indexes
				case _CDX_NODE_ROOT: // Root node, pointing to other sub-indexes
					// Find the first node, and visit it (left-most)
					if (!iCdx_getCompactIdxKey_byNumber(head, 10, 32, 0, 0, node, &key, tagRoot, true, true))
						return(false);		// Failure obtaining the tag name, which is a fatal error (the index is likely corrupt)

					// Continue processing
					node = iCdx_getCompactIdxNode_byOffset(head, key.fileOffset);
					break;

				case _CDX_NODE_LEAF:		// Leaf
				case _CDX_NODE_ROOT_LEAF:	// Root + leaf
					// Leaf node
					// Grab the indicated tag number
					if (lnTagNum < node->keyCount)
					{
						// It's on this node
						if (iCdx_getCompactIdxKey_byNumber(head, 10, 32, lnTagNum, lnTagNum, node, &key, tagRoot, false, false))
						{
							// We found it
							tagRoot->keyNode		= key.fileOffset;				// Offset to the tag's info node
							nodeTag					= (SCdxHeader*)iCdx_getCompactIdxNode_byOffset(head, tagRoot->keyNode);
							tagRoot->leftmostNode	= *(u32*)nodeTag;				// First 32-bits of tag's info node is the first index node
							tagRoot->keyLength		= (u32)nodeTag->keyLength;
							tagRoot->highestNode	= tagRoot->leftmostNode;

							// Determine what field type the index expression is
// TODO:  This is not fool-proof, but rather it works only with concatenated character fields, or single fields or additive single fields
							tagRoot->fillChar		= iDbf_getField_type(wa, (u8*)nodeTag + 512, &tagRoot->swapEndians, &tagRoot->needsSignBitToggled);
							tagRoot->indexIsDesc	= iiCdx_isDescending(nodeTag);

							// See if that first/highest node is an index node, if so then we descend until we find the left-most leaf node
							nodeFirst				= iCdx_getCompactIdxNode_byOffset(head, tagRoot->leftmostNode);
							memcpy(&tagRoot->tagName[0], key.key, 10);

							// If it's an index node, we need to move to the first entry
							tagRoot->leftmostNode	= iCdx_descendToLeftmostNode(head, tagRoot->keyLength, nodeFirst, tagRoot);

							// Indicate success
							return(true);
						}

					} else {
						// We have to traverse to the node to the right
						if (node->nodeRight == (u32)-1)
							return(false);		// No more nodes to traverse

						// Reduce our count by the number of keys on this node
						lnTagNum -= node->keyCount;

						// Get the right node and continue processing
						node = iCdx_getCompactIdxNode_byOffset(head, node->nodeRight);
					}
					break;

				default:
					// Should never happen.
					// It means the indicated node was loaded, but it did not identify itself as a valid _CDX_NODE_* type.
					// This usually means the index is corrupt and needs to be rebuilt.
					iError_signal(_ERROR_INVALID_CORRUPT_NEEDS_REBUILT, NULL, false, NULL, false);
					break;
			}
		}
		// If we get here, failure
		return(false);
	}




//////////
//
// Called to get the tagRoot information for the a compact-only IDX, not compound CDX
//
//////
	bool iCdx_getCompactRootNode(SWorkArea* wa, SCdxHeader* head, SCdxNode* node, STagRoot* tagRoot)
	{
// Untested code, breakpoint and examine
debug_break;

		// We allow the root tag node to be passed as NULL, and then populated with the head
		if (!node)
			node = (SCdxNode*)((s8*)head + sizeof(SCdxHeader));

		// Based on the type of node we will traverse appropriately
		while (node)
		{
			switch (iiGetIndexNodeType(node->type))
			{
				case _CDX_NODE_INDEX:	// Index node, pointing to other sub-indexes
				case _CDX_NODE_ROOT: // Root node, pointing to other sub-indexes
					// Find the first node, and visit it (left-most)
					node = iCdx_getCompactIdxNode_byOffset(head, node->nodeLeft);
					break;

				case _CDX_NODE_LEAF:		// Leaf
				case _CDX_NODE_ROOT_LEAF:	// Root + leaf
					// Leaf node
					// Populate the common fields
					tagRoot->indexIsDesc	= false;		// No indication in documentation about how to obtain this value, will need to research manually
					tagRoot->keyLength		= head->keyLength;
					tagRoot->fillChar		= iDbf_getField_type(wa, &head->keyExpression[0], &tagRoot->swapEndians, &tagRoot->needsSignBitToggled);
					tagRoot->highestNode	= sizeof(SCdxHeader);	// Always the node after head
					tagRoot->leftmostNode	= (u32)((uptr)node - (uptr)head);

					// Indicate success
					return(true);
			}
		}
		// If we get here, failure
		return(false);
	}




//////////
//
// Called to get the tagRoot information for the IDX
//
//////
	bool iCdx_getStandardRootNode(SWorkArea* wa, SIdxHeader* head, SIdxNode* node, STagRoot* tagRoot)
	{
// Untested code, breakpoint and examine
debug_break;

		// We allow the root tag node to be passed as NULL, and then populated with the head
		if (!node)
			node = (SIdxNode*)((s8*)head + sizeof(SIdxHeader));

		// Based on the type of node we will traverse appropriately
		while (node)
		{
			switch (iiGetIndexNodeType(node->type))
			{
				case _CDX_NODE_INDEX:	// Index node, pointing to other sub-indexes
				case _CDX_NODE_ROOT: // Root node, pointing to other sub-indexes
					// Find the first node, and visit it (left-most)
					node = iCdx_getStandardIdxNode_byOffset(head, node->nodeLeft);
					break;

				case _CDX_NODE_LEAF:		// Leaf
				case _CDX_NODE_ROOT_LEAF:	// Root + leaf
					// Leaf node
					// Populate the common fields
					tagRoot->indexIsDesc	= false;		// No indication in documentation about how to obtain this value, will need to research manually
					tagRoot->keyLength		= head->keyLength;
					tagRoot->fillChar		= iDbf_getField_type(wa, &head->keyExpression[0], &tagRoot->swapEndians, &tagRoot->needsSignBitToggled);
					tagRoot->highestNode	= sizeof(SIdxHeader);		// Always the node after head
					tagRoot->leftmostNode	= (u32)((uptr)node - (uptr)head);

					// Indicate success
					return(true);
			}
		}
		// If we get here, failure
		return(false);
	}




//////////
//
// Called to determine the various settings:
//
//		Unique setting.  Returns true if unique, otherwise false.
//		Descending setting.  Returns true if descending, otherwise false.
//
//////
	bool iiCdx_isCompact(SCdxHeader* head)
	{
		if ((head->options & _BIT_COMPACT_INDEX) != 0)		return(true);
		else												return(false);
	}

	bool iiCdx_isCompound(SCdxHeader* head)
	{
		if ((head->options & _BIT_COMPOUND_INDEX) != 0)		return(true);
		else												return(false);
	}

	bool iiCdx_isUnique(SCdxHeader* head)
	{
		if ((head->options & _BIT_UNIQUE) != 0)				return(true);
		else												return(false);
	}

	bool iiCdx_isDescending(SCdxHeader* head)
	{
		if (head->order != 0)								return(true);
		else												return(false);
	}

	bool iiCdx_isPrimaryKeySet(SWorkArea* wa)
	{
		// Is an index loaded?
		if (wa->isIndexLoaded)
		{
			// What type of index?
			if (!wa->isCdx)
			{
				// It's .idx
				return(true);

			} else {
				// It's .cdx
				// If there's an active tag that's been set, the active tag node will be set
				return(wa->cdx_activeTagRootNode != 0);
			}

		}

		// If we get here, no primary key is set
		return(false);
	}

	bool iCdx_isForClauseComplex(SWorkArea* wa, SCdxHeader* head, SForClause** tsFor)
	{
		s32				lnI;
		u32				lnForModifier;
		SForClause*		lsFor;
		SForSubItem*	lfsi;
		SForOp*			lfco;
		SFieldRecord2*	lfptr2;
		u8				fieldName[128];


		// Is the environment workable?
		if (wa && head)
		{
			//////////
			// Reset the for clause, which should've already been delete
			//////
				if (tsFor)		iDbf_forClause_delete(tsFor);	// Reset whatever's there
				else			return(true);					// Invalid parameter, so indicate it's too complex


			//////////
			// Is there even a FOR clause?
			//////
				if (head->forClauseLength != 0)
				{
					//////////
					// Allocate space for our for clause
					//////
						lsFor = iDbf_forClause_allocate(tsFor);
						if (!lsFor)				// TODO:  Capture some error here
							return(true);		// Unable to allocate, so indicate it is too complex


					//////////
					// Parse out what's there in successive terms, which will be something,symbols,something,symbols... for as many as there are
					//////
						if (!iiDbf_forClause_subitems_parse(head, lsFor))
						{
							// Something happened while parsing that we don't support
							iDbf_forClause_delete(tsFor);	// Reset whatever's there
							return(true);					// Too complex
						}


					//////////
					// The types of FOR clauses we allow are:
					//		Constant logical .T. or .F.
					//		Individual fields by themselves, logical, numeric, character, date, datetime, etc.
					//		Logical =,!= other field or constant in the form .T. or .F. only
					//		Numeric =,>,<,>=,<=,!= other field or constant
					//		Character =,>,<,>=,<=,!= other field or constant
					//		Character + character + character + ... =,>,<,>=,<=,!= other field or constant
					//		Date =,>,<,>=,<=,!= other field
					//////
						lnForModifier = 0;
						for (lnI = 0; lnI < lsFor->subitemCount; lnI++)
						{
							// There is only one, which is likely a constant .T. or .F., or a logical field name
							lfsi = &lsFor->subitems[lnI];
							switch (lfsi->type)
							{
								case _FOR_CLAUSE_SUBITEM_TYPE_NOT:
									// The next thing will be the opposite
									lnForModifier |= _FOR_CLAUSE_OPS_NOT;
									break;

								case _FOR_CLAUSE_SUBITEM_TYPE_ALPHANUMERIC:
									// See if it's a NOT keyword

									//////////
									// We need to do a lookup on the fieldname to make sure it exists
									//////
										iResetThenCopyString(fieldName, (s32)sizeof(fieldName), lfsi->start, (s32)lfsi->length);
										lfptr2 = iDbf_getField_byName2(wa, fieldName);
										if (!lfptr2)
										{
											// We've encountered an unknown fieldname3
											iDbf_forClause_delete(tsFor);	// Reset whatever's there
											return(true);					// Too complex
										}


									//////////
									// We have the field name, get its type, must be logical
									//////
										iDbf_getField_type(wa, lfptr2->fieldNumber, fieldName, sizeof(fieldName));
										if (fieldName[0] != 'L' && fieldName[0] != 'l')
										{
											// Unsupported type
											iDbf_forClause_delete(tsFor);	// Reset whatever's there
											return(true);					// Too complex
										}


									//////////
									// We're good.  We need to append this operation
									//////
										lfco				= iiDbf_forClause_ops_appendItem(lsFor);
										lfco->op			= _FOR_CLAUSE_OPS_EQUAL_TEMPORARY | lnForModifier;
										lfco->offsetL		= iDbf_getField_dataOffset(wa, lfptr2->fieldNumber);
										lfco->tempIndexR	= iiDbf_forClause_temp_appendConstant(lsFor, (s8*)"T", 1);
										lfco->lengthL		= 1;	// 1 byte for logical


									//////////
									// Reset for next go around
									//////
										lnForModifier = 0;
										break;


								case _FOR_CLAUSE_SUBITEM_TYPE_LOGICAL_CONSTANT:
									//////////
									// If it's true we simply ignore the test because it will always be true
									//////
										if ((_memicmp(lfsi->start, ".f.", 3) == 0 && lnForModifier == 0) || (_memicmp(lfsi->start, ".t.", 3) == 0 && lnForModifier == _FOR_CLAUSE_OPS_NOT))
										{
											// It's false, set it to something that won't ever be true
											lfco				= iiDbf_forClause_ops_appendItem(lsFor);
											lfco->op			= _FOR_CLAUSE_OPS_NOT | _FOR_CLAUSE_OPS_EQUAL_ROW_DATA;
											lfco->offsetL		= 0;	// Compare self on left...
											lfco->offsetR		= 0;	//             ...to self on right, testing for not equal, so it will always fail
											lfco->lengthL		= 1;	// for one byte (uses the deleted() mark)
										}


									//////////
									// Reset for next go around
									//////
										lnForModifier = 0;
										break;


								default:
									// We don't support whatever's here
									iDbf_forClause_delete(tsFor);	// Reset whatever's there because...
									return(true);					// Too complex
							}
						}
						// When we get here, we report it's NOT too complex
						return(false);
				}

		} else {
// TODO:  Capture some error here
		}
		// If we get here, we report it's too complex
		return(true);
	}




//////////
//
// Called to get the indicated node by number
//
//////
	SIdxNode* iCdx_getStandardIdxNode_byNumber(SIdxHeader* head, u32 tnNodeNumber)
	{
		SIdxNode* node;


		if (head && tnNodeNumber >= 1 && tnNodeNumber * 512 <= head->fileSize - 512)
		{
			// We're within range
			node = (SIdxNode*)((s8*)head + (tnNodeNumber * 512));

		} else {
			// It is not a valid request
			node = NULL;
		}

		// Indicate our status
		return(node);
	}




//////////
//
// Called to get the indicated node by number
//
//////
	SIdxNode* iCdx_getStandardIdxNode_byOffset(SIdxHeader* head, u32 tnOffset)
	{
		SIdxNode* node;


		if (head && tnOffset >= 512 && tnOffset <= head->fileSize - 512)
		{
			// We're within range
			node = (SIdxNode*)((s8*)head + tnOffset);

		} else {
			// It is not a valid request
			node = NULL;
		}

		// Indicate our status
		return(node);
	}




//////////
//
// Called to get the standard IDX key for the indicated key number within the indicated node.
//
//////
	bool iCdx_getStandardIdxKey_byNumber(SIdxHeader* head, u8 tcFillChar, u32 tnNumber, SIdxNode* node, SIdxKey* key, STagRoot* tagRoot, bool tlFixupEndian, bool tlFixupSignBit)
	{
		u32 lnKeyLength;


		// Based on the type of node, it advances in different ways
		if (head && node && key && tnNumber < node->keyCount)
		{
			// Get a common variable for the key length
			lnKeyLength			= head->keyLength + 4;
			key->key			= (u8*)(node + 1) + (tnNumber * lnKeyLength);
			key->record			= iiSwapEndian32(*(u32*)(key->_key + head->keyLength));		// Stored in big-endian on disk, needs converted to little-endian for internal use
			key->keyLength		= head->keyLength;


			/////////
			// If we need to swap it out, then we will do so.  See how that works?
			//////
				if (tagRoot->swapEndians)
				{
					// Certain variable types are stored in a big endian form, with the sign bit toggled, and if negative then every bit inverted.
					if (tlFixupSignBit)
					{
						if ((key->key[0] & 0x80) != 0)		key->key[0] &= 0x7f;		// It is unsigned
						else								key->key[0] |= 0x80;		// It is signed
					}

					// Convert based on key length
					if (tlFixupEndian)
					{
							 if (head->keyLength == 4)		*(u32*)&key->key[0] = iiSwapEndian32(*(u32*)&key->key[0]);		// 4-byte conversion
						else if (head->keyLength == 8)		*(u64*)&key->key[0] = iiSwapEndian64(*(u64*)&key->key[0]);		// 8-byte conversion
					}
				}

			return(true);
		}
		// If we get here, failure
		return(false);
	}




//////////
//
// Called to obtain the indicated node by number
//
//////
	SCdxNode* iCdx_getCompactIdxNode_byNumber(SCdxHeader* head, u32 tnNodeNumber)
	{
		SCdxNode* node;


		if (head && tnNodeNumber >= 1 && 512 + (tnNodeNumber * 512) <= head->fileSize - 512)
		{
			// We're within range
			node = (SCdxNode*)((s8*)head + 512 + (tnNodeNumber * 512));

		} else {
			// It is not a valid request
			node = NULL;
		}

		// Indicate our status
		return(node);
	}




//////////
//
// Called to obtain the indicated node by file offset
//
//////
	SCdxNode* iCdx_getCompactIdxNode_byOffset(SCdxHeader* head, u32 tnOffset)
	{
		SCdxNode* node;


		if (head && tnOffset >= 1024 && tnOffset <= head->fileSize - 512)
		{
			// We're within range
			node = (SCdxNode*)((s8*)head + tnOffset);

		} else {
			// It is not a valid request
			node = NULL;
		}

		// Indicate our status
		return(node);
	}




//////////
//
// Called to get the compact CDX key for the indicated key number within the indicated node.
// Base-0, meaning 0 is the first key.
//
//////
//////////
// Tried to add a speedup, but it's not working... needs debugging
//////
// 	SCdxHeader*		headLast			= NULL;
// 	SCdxNode*		nodeLast			= NULL;
// 	STagRoot*		tagRootLast			= NULL;
// 	u32				keyLastNumber		= -1;
// 	SCdxKey			keyLast;
//////
// END
//////////
	bool iCdx_getCompactIdxKey_byNumber(SCdxHeader* head, u32 keyLength, u8 tcFillChar, u32 tnKeyNumberTarget, u32 tnKeyNumberThis, SCdxNode* node, SCdxKeyLeafRaw* key, STagRoot* tagRoot, bool tlFixupEndian, bool tlFixupSignBit)
	{
		u32						lnKeyLength, lnVariableLength;
		s8*						keyPtr;
		SCdxKeyTrail			keyTrail;
		SCdxKeyTrailInterior*	keyTrailInterior;
		SCdxKeyLeafRaw			keyPrior;


		// Is this us?
		if (head && node && tnKeyNumberThis < node->keyCount)
		{
			if (iiGetIndexNodeType(node->type) == 2 || iiGetIndexNodeType(node->type) == 3)
			{
				// Process the exterior/leaf node
				iiCdx_extractExteriorNode_nodeKeyAccessData(node, tnKeyNumberThis, &keyTrail);	// Node-specific key information

				// If we are duplicating bytes from the previous key, we need that key
				if (tnKeyNumberThis != 0)
				{
					// Grab the prior key, which may grab the prior key, which may grab the prior key, and so on... UGH!  What a horrible design.
					iCdx_getCompactIdxKey_byNumber(head, keyLength, tcFillChar, tnKeyNumberTarget, tnKeyNumberThis - 1, node, &keyPrior, tagRoot, false, false);

					// Copy the prior key if need be
					if (keyTrail.count_DC != 0)
						memcpy(&key->key[0], &keyPrior.key, keyTrail.count_DC);

				} else {
					// No prior key, initialize it all to 0s
					memset(&keyPrior, 0, sizeof(keyPrior));
				}

				// Determine our variable length part
				lnVariableLength	= max((s32)(keyLength - keyTrail.count_DC - keyTrail.count_TC), 0);
				key->offset			= keyPrior.offset + lnVariableLength;
				key->keyLength		= keyLength;

				// Append it in there if need be
				if (lnVariableLength != 0)
					memcpy(&key->key[keyTrail.count_DC], (s8*)node + 512 - key->offset, lnVariableLength);

				// Append the trailing blanks if need be
				if (keyTrail.count_TC != 0)
					memset(&key->key[keyLength - keyTrail.count_TC], tcFillChar, keyTrail.count_TC);

				// Store the record number
				key->recordNumber		= keyTrail.record;
				key->record2	= 0;


			} else {
				// Process the interior node
				lnKeyLength					= keyLength + sizeof(SCdxKeyTrail);
				keyPtr						= (s8*)node + 12 + (tnKeyNumberThis * lnKeyLength);
				keyTrailInterior			= (SCdxKeyTrailInterior*)(keyPtr + keyLength);
				key->fileOffset				= iiSwapEndian32(keyTrailInterior->fileOffset);
				key->record2				= iiSwapEndian32(keyTrailInterior->record2);
				key->offset					= 12 + (tnKeyNumberThis * lnKeyLength);
				key->keyLength				= keyLength;
				key->key[keyLength]			= 0;
				memcpy(key->key, keyPtr, keyLength);
			}


			/////////
			// If we need to swap it out, then we will do so.  See how that works?
			//////
				if (tagRoot->swapEndians)
				{
					// Certain variable types are stored in a big endian form, with the sign bit toggled, and if negative then every bit inverted.
					if (tlFixupEndian)
					{
						// Convert based on key length
							 if (keyLength == 4)	*(u32*)&key->key[0] = iiSwapEndian32(*(u32*)&key->key[0]);	// 4-byte conversion
						else if (keyLength == 8)	*(u64*)&key->key[0] = iiSwapEndian64(*(u64*)&key->key[0]);	// 8-byte conversion
					}

					if (tlFixupSignBit)
					{
						if ((key->key[key->keyLength - 1] & 0x80) != 0)
						{
							// It is unsigned
							key->key[key->keyLength - 1] &= 0x7f;

						} else {
							// It is signed
							if (key->keyLength == 8)
								*(u64*)key->key = ~(*(u64*)key->key);

							// Add the sign back on
							key->key[key->keyLength - 1] |= 0x80;
						}
					}
				}


			// Indicate success
			return(true);
		}
		// If we get here, failure
		return(false);
	}




//////////
//
// Called to descend the tree to find the left-most node by offset
//
//////
	u32 iCdx_descendToLeftmostNode(SCdxHeader* head, u32 keyLength, SCdxNode* node, STagRoot* tagRoot)
	{
		u32				lnNodeType;
		SCdxKeyLeafRaw	key;


		// Make sure our environment is sane
		if (head && node)
		{
			// See what node we're on
			lnNodeType = iiGetIndexNodeType(node->type);
			if (lnNodeType == 2 || lnNodeType == 3)
			{
				// We're there
				return((u32)((uptr)node - (uptr)head));

			} else if (lnNodeType == 0 || lnNodeType == 1) {
				// Index node or root node, we need to descend into the first entry
				iCdx_getCompactIdxKey_byNumber(head, keyLength, tagRoot->fillChar, 0, 0, node, &key, tagRoot, true, true);
				return(iCdx_descendToLeftmostNode(head, keyLength, iCdx_getCompactIdxNode_byOffset(head, key.fileOffset), tagRoot));

			} else {
				// Not sure what to do here
				debug_break;
				return(-1);
			}
		}
		// We should never get here
		debug_break;
		// Not sure what to do
		return(-1);
	}




//////////
//
// Swap bytes from big-endian to make a little-endian value
//
//////
	u32 iiSwapEndian32(u32 tnBigEndian)
	{
		tnBigEndian = (		((tnBigEndian & 0xff000000) >> 24)  |
							((tnBigEndian & 0x00ff0000) >> 8) 	|
							((tnBigEndian & 0x0000ff00) << 8) 	|
							((tnBigEndian & 0x000000ff) << 24)			);
		return(tnBigEndian);
	}

	u64 iiSwapEndian64(u64 tnBigEndian)
	{
		tnBigEndian = (		((tnBigEndian & 0xff00000000000000) >> 56) |
							((tnBigEndian & 0x00ff000000000000) >> 40) |
							((tnBigEndian & 0x0000ff0000000000) >> 24) |
							((tnBigEndian & 0x000000ff00000000) >> 8)  |
							((tnBigEndian & 0x00000000ff000000) << 8)  |
							((tnBigEndian & 0x0000000000ff0000) << 24) |
							((tnBigEndian & 0x000000000000ff00) << 40) |
							((tnBigEndian & 0x00000000000000ff) << 56)			);
		return(tnBigEndian);
	}




//////////
//
// Called to extract the bits which represent this portion of the key.
//
//////
	struct SSafeData {
		u8		before[4];			// Puts a buffer before keyBuffer
		u8		buffer[8];			// Maximum used will never exceed 6 bytes (4 + 1 + 1)
		u8		after[4];			// Puts a buffer after keyBuffer
	};

	void iiCdx_extractExteriorNode_nodeKeyAccessData(SCdxNode* node, u32 tnNumber, SCdxKeyTrail* keyTrail)
	{
		u32			lnBitsPerKey, lnFirstByte;
		SSafeData	data;


		// Get the number of bits per each item
		lnBitsPerKey	 = node->bits_RN + node->bits_DC + node->bits_TC;
		lnFirstByte		= sizeof(SCdxNode) + ((lnBitsPerKey * tnNumber) / 8);

		// Extract out the rough portions
		memset(&data, 0, sizeof(SSafeData));
		memcpy(data.buffer, (s8*)node + lnFirstByte, node->totalBytesIn_RNDCTC);

		// Mask off the record number
		keyTrail->record = (*((u32*)&data.buffer[0])) & node->mask_RN;
		*(u32*)&data.buffer[0] >>= node->bits_RN;

		// Grab the duplicate count
		keyTrail->count_DC = data.buffer[0] & node->mask_DC;
		*(u32*)&data.buffer[0] >>= node->bits_DC;

		// Grab the trailing count
		keyTrail->count_TC = data.buffer[0] & node->mask_TC;
	}

	void iiShiftBlockRight(u8* data, u32 tnBytes, s32 tnBits)
	{
		s32		lnI, lnJ;
		u8		lcLastBit, lcNextLastBit;


		// Iterate for the indicated number of bits
		for (lnI = 0; lnI < tnBits; lnI++)
		{
			// For each byte shift over one bit
			lcLastBit = 0;
			for (lnJ = tnBytes - 1; lnJ >= 0; lnJ--)
			{
				// Grab the next bit
				lcNextLastBit	= (data[lnJ] & 0x1) << 7;				// Get the next last bit
				data[lnJ]		= ((data[lnJ] >> 1) | lcLastBit);		// Shift and OR in the previous last bit
				lcLastBit		= lcNextLastBit;						// Move for next iteration
			}
			// When we get here, all bytes have been shifted one bit
		}
	}

	void iiPtrSwap(void** p1, void** p2)
	{
		void* t;

		t	= *p1;		// p1 to temp
		*p1	= *p2;		// p2 to p1
		*p2	= t;		// temp to p2
	}




//////////
//
// Called to copy a string to a buffer which already exists
//
//////
	u8* iResetThenCopyString(u8* tcDest, s32 tnDestLength, u8* tcSource, s32 tnSourceLength)
	{
		// Resets with a null character
		return(iResetThenCopyString(tcDest, tnDestLength, 0, tcSource, tnSourceLength));
	}

	u8* iResetThenCopyString(u8* tcDest, s32 tnDestLength, u8 lcResetChar, u8* tcSource, s32 tnSourceLength)
	{
		// Initialize it to empty...
		if (tcDest)
			memset((s8*)tcDest, lcResetChar, tnDestLength);

		// ...then copy over whatever will fit in the space
		if (tcSource)
			memcpy((s8*)tcDest, (s8*)tcSource, min(tnSourceLength, tnDestLength));

		// Indicate a pointer to their chosen target, so it will propagate through an expression if need be
		return(tcDest);
	}




//////////
//
// Based on the two choices, copies the indicated string
//
//////
	cs8* iiTwoChoice(s8* tcDest, bool tlTestValue, cs8* tcIfTrue, cs8* tcIfFalse)
	{
		cs8* lcResult;


		// Grab our value
		lcResult = ((tlTestValue) ? tcIfTrue : tcIfFalse);

		// Populate
		if (tcDest)
			memcpy(tcDest, lcResult, strlen(lcResult));

		// Indicate our choice
		return(lcResult);
	}




//////////
//
// Called to lock the entire file
//////
	uptr iiCdx_lock_file(SWorkArea* wa, STagRoot* tagRoot)
	{
		s32			lnFileSize;
		SDiskLock*	dl;


// TODO:  VJr is limited to the 2GB barrier ... if this is every removed, this code can be refactored to lock the entire file in 2GB pieces
		// See if the index is loaded
		if (wa->isIndexLoaded)
		{
			// Retry until stopped
			lnFileSize	= (s32)iDisk_getFileSize(wa->fhIdxCdxDcx);
			dl			= iDisk_lock_range_retryCallback(wa->idxCdxDcxFileLocks, wa->fhIdxCdxDcx, 0, lnFileSize, 0, 0);

			// Indicate our success or failure
			return(((dl && dl->nLength == lnFileSize) ? _CDX_OKAY : _CDX_LOCK_FAILURE));

		} else {
			// Return failure
			return(_CDX_ERROR_NO_INDEX_IN_USE);
		}
	}




//////////
//
// Called to lock the indicated range
//////
	uptr iiCdx_lock_node(SWorkArea* wa, STagRoot* tagRoot, s32 tnNode)
	{
		SDiskLock* dl;


		// See if the index is loaded
		if (wa->isIndexLoaded)
		{
			// Retry until stopped
			dl = iDisk_lock_range_retryCallback(wa->idxCdxDcxFileLocks, wa->fhIdxCdxDcx, (tnNode * 512), 512, 0, 0);

			// Indicate our success or failure
			return(((dl && dl->nLength == 512) ? _CDX_OKAY : _CDX_LOCK_FAILURE));

		} else {
			// Return failure
			return(_CDX_ERROR_NO_INDEX_IN_USE);
		}
	}




//////////
//
// Called to lock the entire file
//////
	uptr iiCdx_lock_range(SWorkArea* wa, STagRoot* tagRoot, s32 tnOffset, s32 tnLength)
	{
		SDiskLock* dl;


		// See if the index is loaded
		if (wa->isIndexLoaded)
		{
			// Retry until stopped
			dl = iDisk_lock_range_retryCallback(wa->idxCdxDcxFileLocks, wa->fhIdxCdxDcx, tnOffset, tnLength, 0, 0);

			// Indicate our success or failure
			return(((dl && dl->nLength == tnLength) ? _CDX_OKAY : _CDX_LOCK_FAILURE));

		} else {
			// Return failure
			return(_CDX_ERROR_NO_INDEX_IN_USE);
		}
	}




//////////
//
// Called to lock the entire file
//////
	bool iiCdx_unlock(SWorkArea* wa, SDiskLock* dl)
	{
		return(iDisk_unlock(wa->idxCdxDcxFileLocks, dl));
	}
