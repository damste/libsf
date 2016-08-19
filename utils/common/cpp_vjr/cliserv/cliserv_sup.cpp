//////////
//
// /libsf/utils/common/cpp/cliserv/cliserv_sup.cpp
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
//     Aug.02.2014
//////
// Change log:
//     Aug.02.2014 - Initial creation
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
//     http://www.visual-freepro.org/wiki/index.php/Repeat_License
//
// Thank you.  And may The Lord bless you richly as you lift up your life, your
// talents, your gifts, your praise, unto Him.  In Jesus' name I pray.  Amen.
//
//




//////////
//
// Shuts down a previously launched server listening to the specified port
//
//////
	void iCliServCleanup(void)
	{
		CClient*	lcNext;
		CClient*	lc;
		CServer*	lsNext;
		CServer*	ls;


		//////////
		// Kill all the running client threads
		//////
			lc = gcRootClient;
			while (lc)
			{
				lcNext = lc->m_next;		// Get next client (if any)
				delete lc;					// Delete this item
				lc = lcNext;				// Move to next item;
			}


		//////////
		// Kill all the running server threads
		//////
			ls = gcRootServer;
			while (ls)
			{
				lsNext = ls->m_next;		// Get next client (if any)
				delete ls;					// Delete this item
				ls = lsNext;				// Move to next item;
			}


		//////////
		// Tell WinSock2 to clean itself up
		//////
			WSACleanup();
	}




//////////
//
// Locate the native client
//
//////
	CClient* iFindClient(hostent* host, u32 tnPortNumber)
	{
		CClient* client;


		// Iterate through all that exist
		client = gcRootClient;
		while (client)
		{
			// See if this is the match
			if (client->getClientPortNumber() == tnPortNumber && CCSCommon::compareHosts(client->cscommon()->getClientHosts(), host))
				return(client);		// This is it

			// Move to next item
			client = client->m_next;
		}
		// If we get here, not found
		return(NULL);
	}




//////////
//
// Locate the server on this port, and return its default client (used for reading/writing)
//
//////
	CClient* iFindServersClient(hostent* host, u32 tnPortNumber)
	{
		CServer* server;


		// Iterate through all that exist
		server = gcRootServer;
		while (server)
		{
			// See if this is the match
			if (server->getServerPortNumber() == tnPortNumber && CCSCommon::compareHosts(server->cscommon()->getServerHosts(), host))
			{
				// We return the m_firstClient's cliserv entry
				if (server->firstClient())
				{
					// There is at least one client, return it
					return(server->firstClient());
				}
			}

				// Move to next item
				server = server->m_next;
		}
		// If we get here, not found
		return(NULL);
	}





//////////
//
// Called to make sure the ip address or remote host name is null-terminated
//
//////
	void iGetIpAddress(u8* tcDestination, u8* tcIpAddress, u32 tnIpAddressLength)
	{
		memset(tcDestination, 0, 256);
		memcpy(tcDestination, tcIpAddress, min(255, tnIpAddressLength));
	}




//////////
//
// Append a process to the chain
//
//////
	SAppProc* iCreateNewSProcess(SAppProc** root)
	{
		SAppProc*	procNew;
		SAppProc*	proc;
		SAppProc**	procLast;


		// Make sure we have a proper pointer
		procNew = NULL;
		if (root)
		{
			if (!*root)
			{
				// This is the first one
				procLast = root;

			} else {
				// We need to add to the chain
				proc = *root;
				while (proc->next)
					proc = proc->next;
				procLast = &proc->next;
			}

			// Create the new item
			procNew = (SAppProc*)malloc(sizeof(SAppProc));
			if (procNew)
			{
				// Initialize the new entry
				memset(procNew, 0, sizeof(SAppProc));

				// Initialize the semaphore
				InitializeCriticalSection(&procNew->cs_mail);
				InitializeCriticalSection(&procNew->cs_msgQueue);
				InitializeCriticalSection(&procNew->cs_pipe);
				InitializeCriticalSection(&procNew->cs_generalMessage);

				// Create the process id
				procNew->remoteId = iGetNextUniqueId();

				// Update the forward link
				*procLast = procNew;

				// All done!
			}
		}
		return(procNew);
	}




//////////
//
// Compares two times
//
//////
	u64 iGetSystemtimeDiffInMilliseconds(SYSTEMTIME* newestTime, SYSTEMTIME* oldestTime)
	{
		u64 lnNewSeconds, lnOldSeconds;


		if (newestTime && oldestTime)
		{
			// Compute time in seconds for both
			iComputeSystemTimeMillieconds(newestTime, &lnNewSeconds);
			iComputeSystemTimeMillieconds(oldestTime, &lnOldSeconds);
			// Return the difference
			return(lnNewSeconds - lnOldSeconds);
		}
		// Failure due to invalid values
		return(-1);
	}




//////////
//
// Compute the time in milliseconds for the specified systemtime.
//
// Useful for comparing two times together, to find out how much time is between.
//
//////
	void iComputeSystemTimeMillieconds(SYSTEMTIME* time, u64* ms)
	{
		*ms	 = time->wMilliseconds;
		*ms	+= time->wSecond			* 1000;
		*ms	+= time->wMinute			* 1000   * 60;
		*ms	+= time->wHour				* 1000   * 60   * 60;
		*ms	+= time->wDay				* 1000   * 60   * 60   * 24;
		*ms	+= time->wMonth				* 1000   * 60   * 60   * 24   * iGetMonthStartDayOfYear(time->wMonth, time->wYear);
		*ms	+= (u64)((f64)time->wYear	* 1000.0 * 60.0 * 60.0 * 24.0 * 356.2425 /*leap year days taking into account leap year rules*/);
	}



//////////
//
// Compute the starting day of the specified year for the specified month
//
//////
	u32 iGetMonthStartDayOfYear(u32 month, u32 year)
	{
		u32 lnAddLeapYearDays, lnDaysInYear;


		// Determine if is leap year
		if (year % 400 == 0 || (year % 4 == 0 && ((year % 400) % 100) != 0))
			lnAddLeapYearDays = 1;		// Leap year every 4 years, except for centuries not evenly divisible by 400
		else
			lnAddLeapYearDays = 0;

		// See which month we're on
		lnDaysInYear = 0;
		switch (month)
		{
			case 12:	// It's December, add in November
				lnDaysInYear += 30;
			case 11:	// It's November, add in October
				lnDaysInYear += 31;
			case 10:	// It's October, add in September
				lnDaysInYear += 30;
			case 9:		// It's September, add in August
				lnDaysInYear += 31;
			case 8:		// It's August, add in July
				lnDaysInYear += 31;
			case 7:		// It's July, add in June
				lnDaysInYear += 30;
			case 6:		// It's June, add in May
				lnDaysInYear += 31;
			case 5:		// It's May, add in April
				lnDaysInYear += 30;
			case 4:		// It's April, add in March
				lnDaysInYear += 31;
			case 3:		// It's March, add in February
				lnDaysInYear += 28 + lnAddLeapYearDays;
			case 2:		// It's February, add in January
				lnDaysInYear += 31;
				return(lnDaysInYear);

			// If we get here, it's either January (0 days in year at start) or an invalid input
			default:
				return(0);
		}
	}




//////////
//
// Stores the current system time at the specified location
// Note:  This is recorded here so it can be changed / used differently in the future (if need be).
//
//////
	void iStoreCurrentTime(SYSTEMTIME* tp)
	{
		GetSystemTime(tp);
	}




//////////
//
// When times are initialized in a new structure, they are initially all nulls.
//
//////
	bool iIsTimeEmpty(SYSTEMTIME* tp)
	{
		u32 lnI;
		s8* p;


		// Iterate through every byte
		// If any of them are not NULL, it's not empty
		p = (s8*)tp;
		for (lnI = 0; lnI < sizeof(SYSTEMTIME); lnI++)
		{
			if (p[lnI] != 0)
				return(false);
		}
		// If we get here, they were all NULL
		// It's empty
		return(true);
	}




//////////
//
// Creates / populates a generic list holding up to two search items,
// and (presently two, possibly more in the future) additional items.
//
//////
	u32 iAddToGenericList(SList** tsListRoot,
							s8* tcItem1,	u32 tnItem1Length, 
							s8* tcItem2,	u32 tnItem2Length,
							s8* tcItem3,	u32 tnItem3Length,
							s8* tcItem4,	u32 tnItem4Length,
							s8* tcMetaData,	u32 tnMetaDataLength,
							bool tlNullLengthsAreData)
	{
		SList**		listPrev;
		SList*		listNew;
		SList*		list;


		// See where we are
		if (!*tsListRoot)
		{
			// This is the first item
			listPrev = tsListRoot;

		} else {
			// Append to the chain
			list = *tsListRoot;
			while (list->next)
				list = list->next;
			listPrev = &list->next;
		}

		// Append the new item
		listNew = (SList*)malloc(sizeof(SList));
		if (listNew)
		{
			// Initialize the new structure
			memset(listNew, 0, sizeof(SList));

			// Update the forward-link
			*listPrev = listNew;

			// Indicate our referenced count
			listNew->referenceCount = 1;

			// Append the items
			if ((tcItem1 || tlNullLengthsAreData) && tnItem1Length != 0)
			{
				if (tcItem1)	listNew->item1			= iDuplicateString(tcItem1, tnItem1Length, true);
								listNew->item1Length	= tnItem1Length;
			}

			if ((tcItem2 || tlNullLengthsAreData) && tnItem2Length != 0)
			{
				if (tcItem2)	listNew->item2			= iDuplicateString(tcItem2, tnItem2Length, true);
								listNew->item2Length	= tnItem2Length;
			}

			if ((tcItem3 || tlNullLengthsAreData) && tnItem3Length != 0)
			{
				if (tcItem3)	listNew->item3			= iDuplicateString(tcItem3, tnItem3Length, true);
								listNew->item3Length	= tnItem3Length;
			}

			if ((tcItem4 || tlNullLengthsAreData) && tnItem4Length != 0)
			{
				if (tcItem4)	listNew->item4			= iDuplicateString(tcItem4, tnItem4Length, true);
								listNew->item4Length	= tnItem4Length;
			}

			if (tcMetaData && tnMetaDataLength != 0)
			{
				listNew->meta		= iDuplicateString(tcMetaData, tnMetaDataLength, true);
				listNew->metaLength	= tnMetaDataLength;
			}
		}
		// All done
		return((u32)listNew);
	}




//////////
//
// Searches the generic list for the entry, if not found, then it adds it.
// Returns 0 if already exists, !0 if added.
//
//////
	u32 iAddToGenericListIfUnique(SList** tsListRoot, s8* tcItem1, u32 tnItem1Length, s8* tcItem2, u32 tnItem2Length, s8* tcItem3, u32 tnItem3Length, s8* tcItem4, u32 tnItem4Length, s8* tcMetaData, u32 tnMetaDataLength)
	{
		SList* list;


		// See if it already exists
		list = iSearchGenericList(*tsListRoot, tcItem1, tnItem1Length, tcItem2, tnItem2Length, tcItem3, tnItem3Length, tcItem4, tnItem4Length);
		if (!list)
		{
			// It was not found, add it
			return(iAddToGenericList(tsListRoot, tcItem1, tnItem1Length, tcItem2, tnItem2Length, tcItem3, tnItem3Length, tcItem4, tnItem4Length, tcMetaData, tnMetaDataLength, false));

		} else {
			// Update the meta data
			if (tcMetaData && tnMetaDataLength != 0)
			{
				// Replace the meta data
				if (list->meta && list->metaLength != 0)
					free(list->meta);

				// Update the meta data
				list->meta			= iDuplicateString(tcMetaData, tnMetaDataLength, true);
				list->metaLength	= tnMetaDataLength;
			}
		}
		// If we get here, it already exists
		return(0);
	}




//////////
//
// Searches a generic list for up to two search items using the tbSearchSecondLevel
// flag to determine if the list is only matched by one search item, or by two levels.
// Note:  A generic list does not have to have search items.
//
//////
	SList* iSearchGenericList(SList* tsListRoot, s8* tcItem1, u32 tnItem1Length, 
												 s8* tcItem2, u32 tnItem2Length,
												 s8* tcItem3, u32 tnItem3Length,
												 s8* tcItem4, u32 tnItem4Length)
	{
		bool	lbMatched1, lbMatched2, lbMatched3, lbMatched4;
		SList*	list;


		// Iterate through all items
		if (tsListRoot)
		{
			list = tsListRoot;
			while (list)
			{
				// See What this list's item1 is
				lbMatched1 = false;
				if (list->item1Length == sizeof(cgcAllItems) - 1 && _memicmp(list->item1, cgcAllItems, sizeof(cgcAllItems) -1) == 0)
				{
					// It's a match on all, so this one is a match
					lbMatched1 = true;

				} else if (iIsNeedleInHaystack(list->item1, list->item1Length, tcItem1, tnItem1Length)) {
					// It was found within the list
					lbMatched1 = true;
				}
				//else we no find :-(

				if (lbMatched1)
				{
					// Go to phase2, and see if we match an item in item2
					if (tcItem2)
					{
						// See What this list's item2 is
						lbMatched2 = false;
						if (list->item2Length == sizeof(cgcAllItems) - 1 && _memicmp(list->item2, cgcAllItems, sizeof(cgcAllItems) -1) == 0)
						{
							// It's a match on all, so this one is a match
							lbMatched2 = true;

						} else if (iIsNeedleInHaystack(list->item2, list->item2Length, tcItem2, tnItem2Length)) {
							// It was found within the list
							lbMatched2 = true;
						}
						//else we no find :-(

					} else {
						// No second level match, so we assume it matched
						lbMatched2 = true;
					}

					if (lbMatched2)
					{
						// Go to phase3, and see if we match an item in item3
						if (tcItem3)
						{
							// See What this list's item3 is
							lbMatched3 = false;
							if (list->item3Length == sizeof(cgcAllItems) - 1 && _memicmp(list->item3, cgcAllItems, sizeof(cgcAllItems) -1) == 0)
							{
								// It's a match on all, so this one is a match
								lbMatched3 = true;

							} else if (iIsNeedleInHaystack(list->item3, list->item3Length, tcItem3, tnItem3Length)) {
								// It was found within the list
								lbMatched3 = true;
							}
							//else we no find :-(

						} else {
							// No second level match, so we assume it matched
							lbMatched3 = true;
						}

						if (lbMatched3)
						{
							if (tcItem4)
							{
								// See What this list's item4 is
								lbMatched4 = false;
								if (list->item4Length == sizeof(cgcAllItems) - 1 && _memicmp(list->item4, cgcAllItems, sizeof(cgcAllItems) -1) == 0)
								{
									// It's a match on all, so this one is a match
									lbMatched4 = true;

								} else if (iIsNeedleInHaystack(list->item4, list->item4Length, tcItem4, tnItem4Length)) {
									// It was found within the list
									lbMatched4 = true;
								}
								//else we no find :-(

							} else {
								// No second level match, so we assume it matched
								lbMatched4 = true;
							}

							// See where we are
							if (lbMatched4)
							{
								// We're golden!

								// Increase our reference count
								++list->referenceCount;

								// Indicate our found item
								return(list);
							}
						}
					}
					// If we get here, not found
				}

				// Move to next item
				list = list->next;
			}
		}
		// If we get here, not found
		return(NULL);
	}




//////////
//
// Called to delete the items in a generic list
//
//////
	void iDeleteGenericList(SList** tsListRoot)
	{
		SList*	listNext;
		SList*	list;


		// See where we are
		if (!tsListRoot || !*tsListRoot)
		{
			// Nothing to delete
			return;

		}

		// Delete the entire chain
		list = *tsListRoot;
		while (list)
		{
			// Grab the next pointer
			listNext = list->next;

			// Delete this list entry's items
			if (list->item1 && list->item1Length != 0)
				free(list->item1);

			if (list->item2 && list->item2Length != 0)
				free(list->item2);

			if (list->item3 && list->item3Length != 0)
				free(list->item3);

			if (list->item4 && list->item4Length != 0)
				free(list->item4);

			if (list->meta && list->metaLength != 0)
				free(list->meta);

			// Delete this list entry
			free(list);

			// Move to the next position
			list = listNext;
		}
	}




//////////
//
// Checks to see if the specified needle is found in the haystack
//
//////
	bool iIsNeedleInHaystack(s8* haystack, s32 haystackLength, s8* needle, s32 needleLength)
	{
		return(iIsNeedleInHaystack(haystack, haystackLength, needle, needleLength, NULL));
	}

	// Case sensitive variation
	bool iIsNeedleInHaystackCase(s8* haystack, s32 haystackLength, s8* needle, s32 needleLength)
	{
		return(iIsNeedleInHaystackCase(haystack, haystackLength, needle, needleLength, NULL));
	}

	bool iIsNeedleInHaystack(s8* haystack, s32 haystackLength, s8* needle, s32 needleLength, u32* tnStart)
	{
		s32 lnI;

		// Check to see if the specified word / phrase / whatever exists on this line
		if (haystackLength < 0)		haystackLength	= strlen(haystack);
		if (needleLength < 0)		needleLength	= strlen(needle);

		// Iterate to see if we find it
		for (lnI = 0; lnI <= haystackLength - needleLength; lnI++)
		{
			if (_memicmp(haystack + lnI, needle, needleLength) == 0)
			{
				// Store the offset if we're supposed to
				if (tnStart)
					*tnStart = lnI;
				// Indicate success
				return(true);
			}
		}

		// Failure
		return(false);
	}

	bool iIsNeedleInHaystackCase(s8* haystack, s32 haystackLength, s8* needle, s32 needleLength, u32* tnStart)
	{
		s32 lnI;

		// Check to see if the specified word / phrase / whatever exists on this line
		for (lnI = 0; lnI <= haystackLength - needleLength; lnI++)
		{
			if (memcmp(haystack + lnI, needle, needleLength) == 0)
			{
				// Store the offset if we're supposed to
				if (tnStart)
					*tnStart = lnI;
				// Indicate success
				return(true);
			}
		}

		// Failure
		return(false);
	}

	// Search only for a single character without regard to case
	bool iIsCharacterInHaystack(s8* haystack, s32 haystackLength, s8 needle, u32* tnOffset)
	{
		s32		lnI;
		s8		c;

		// Check to see if the specified word / phrase / whatever contains this character
		c = iLowerCharacter(needle);
		for (lnI = 0; lnI < haystackLength; lnI++)
		{
			if (iLowerCharacter(haystack[lnI]) == c)
			{
				if (tnOffset)
					*tnOffset = lnI;

				return(true);
			}
		}

		// Failure
		return(false);
	}

	// Search only for a single character by case
	bool iIsCharacterInHaystackCase(s8* haystack, s32 haystackLength, s8 needle, u32* tnOffset)
	{
		s32 lnI;

		// Check to see if the specified word / phrase / whatever contains this character
		for (lnI = 0; lnI < haystackLength; lnI++)
		{
			if (haystack[lnI] == needle)
			{
				if (tnOffset)
					*tnOffset = lnI;

				return(true);
			}
		}

		// Failure
		return(false);
	}

	// Searches backwards for the specified character
	bool iIsCharacterInHaystackReversed(s8* haystack, s32 haystackLength, s8 needle, u32* tnOffset)
	{
		s32		lnI;
		s8		c;

		// Check to see if the specified word / phrase / whatever contains this character
		c = iLowerCharacter(needle);
		for (lnI = haystackLength - 1; lnI >= 0; lnI--)
		{
			if (iLowerCharacter(haystack[lnI]) == c)
			{
				if (tnOffset)
					*tnOffset = lnI;

				return(true);
			}
		}

		// Failure
		return(false);
	}

	bool iIsCharacterInHaystackReversedCase(s8* haystack, s32 haystackLength, s8 needle, u32* tnOffset)
	{
		s32 lnI;

		// Check to see if the specified word / phrase / whatever contains this character
		for (lnI = haystackLength - 1; lnI >= 0; lnI--)
		{
			if (haystack[lnI] == needle)
			{
				if (tnOffset)
					*tnOffset = lnI;

				return(true);
			}
		}

		// Failure
		return(false);
	}




//////////
//
// Checks to see if the specified needle is found at the start of the haystack
//
//////
	bool iDoesHaystackStartWithNeedle(s8* haystack, s32 haystackLength, s8* needle, s32 needleLength)
	{
		s32 lnWhitespaces;


		// Skip past any whitespaces
		lnWhitespaces = 0;
		iSkipWhitespaces(haystack, (u32*)&lnWhitespaces, haystackLength);

		// Check to see if the specified word / phrase / whatever exists on this line
		if (haystackLength - lnWhitespaces >= needleLength)
		{
			if (_memicmp(haystack + lnWhitespaces, needle, needleLength) == 0)
				return(true);
		}

		// Failure
		return(false);
	}

	// Case sensitive variation
	bool iDoesHaystackStartWithNeedleCase(s8* haystack, s32 haystackLength, s8* needle, s32 needleLength)
	{
		s32 lnWhitespaces;


		// Skip past any whitespaces
		lnWhitespaces = 0;
		iSkipWhitespaces(haystack, (u32*)&lnWhitespaces, haystackLength);

		// Check to see if the specified word / phrase / whatever exists on this line
		if (haystackLength - lnWhitespaces >= needleLength)
		{
			if (memcmp(haystack + lnWhitespaces, needle, needleLength) == 0)
				return(true);
		}

		// Failure
		return(false);
	}

	s8 iLowerCharacter(s8 ch)
	{
		if (ch >= 'A' && ch <= 'Z')
			ch += 0x20;
		return(ch);
	}




//////////
//
// Skips past whitespace characters (tabs and spaces)
// Move the offset byte forward until we're no longer sitting on a
// whitespace character, and indicate how many we skipped.
//
//////
	u32 iSkipWhitespaces(s8* source, u32* offset, u32 maxLength)
	{
		s8		c;
		u32		lnLength, lnOffset;


		// Make sure we have valid parameters
		if (!offset)
		{
			// They didn't give us an offset, so we use our own, home-grown solution, that's right, my friend! :-)
			lnOffset	= 0;
			offset = &lnOffset;
		}

		// Move from the current location to its new location
		lnLength = 0;
		while (*offset < maxLength)
		{
			c = source[*offset];
			if (c != 32/*space*/ && c != 9/*tab*/)
				return(lnLength);		// It's no longer a whitespace

			// Move to the next position
			++lnLength;
			++*offset;
		}
		return(lnLength);
	}




//////////
//
// Called to send the indicated command plus verb to the indicated ip address, assuming
// we are connected to it and it is valid.
//
//////
	s32 iSendToIpAddress(u8* tcVerb, u32 tnVerbLength, u8* tcCommand, u32 tnCommandLength, u8* tcIpAddress, u32 tnIpAddressLength, u32 tnPortNumber)
	{
		u32			lnTxCount;
		CServer*	server;
		CClient*	client;
		CCSCommon*	cc;
		hostent*	host;				// Host name data for the ip address they're looking for
		u8			lcIpAddress[256];	// Converted version that is null-terminated
		u8*			lcCmd;				// Copy of the command


		// Duplicate the command (so we can append to our copy)
		lnTxCount	= 0;
		lcCmd		= iDuplicateString(tcCommand, tnCommandLength, false);
		if (lcCmd)
		{
			//////////
			// Append the "verb:" part, which is whatever tcVerb was specified
			//////
				memcpy(lcCmd, tcCommand, tnCommandLength);
				iAppendLabelColonValueString(&lcCmd, &tnCommandLength, (u8*)cgcVerbCmd, sizeof(cgcVerbCmd) - 1, tcVerb, tnVerbLength);


			//////////
			// Try to find the ip address in 32-bit form
			//////
				iGetIpAddress(lcIpAddress, tcIpAddress, tnIpAddressLength);
				host = gethostbyname((cs8*)lcIpAddress);
				if ((s16)host->h_addrtype < 0 || host->h_addr_list[0] == 0 || ((in_addr*)host->h_addr_list[0])->S_un.S_addr == 0)
					return(-1);		// We could not find an IP address


			//////////
			// Iterate through every server for the server attached to this portnum
			//////
				server = gcRootServer;
				while (server)
				{
					// See if this is the server to send to
					cc = server->cscommon();
					client = server->firstClient();
					while (client)
					{
						// See if this is the client to send to
						cc = client->cscommon();
						if (client->getClientPortNumber() == tnPortNumber && cc->getClientIpAddress()->sin_addr.S_un.S_addr == ((in_addr*)host->h_addr_list[0])->S_un.S_addr)
						{
							// This is our ip address and port
							++lnTxCount;
							cc->createCommQueueObjectFromBufferAndAddToToSendCommQueue(client, (s8*)lcCmd, tnCommandLength, cgcEMsg);
						}

						// Move to the next client
						client = client->m_next;
					}

					// Move to the next server
					server = server->m_next;
				}


			//////////
			// Iterate through every client for the clients attached to this portnum
			//////
				client = gcRootClient;
				while (client)
				{
					// See if this is the client to send to
					cc = client->cscommon();
					if (client->getClientPortNumber() == tnPortNumber && cc->getClientIpAddress()->sin_addr.S_un.S_addr == ((in_addr*)host->h_addr_list[0])->S_un.S_addr)
					{
						// This is our ip address and port
						++lnTxCount;
						cc->createCommQueueObjectFromBufferAndAddToToSendCommQueue(client, (s8*)lcCmd, tnCommandLength, cgcEMsg);
					}

					// Move to the next client
					client = client->m_next;
				}


			//////////
			// When we get here, we're done
			//////
				free(lcCmd);
		}
		// When we get here, all done
		if (lnTxCount == 0)		return(false);		// Failure
		else					return(true);		// Success
	}
