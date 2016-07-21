//////////
//
// /libsf/utils/common/cpp/include/bsearch.h
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
//     Jul.19.2016
//////
// Change log:
//     Jul.19.2016	- Initial creation
//////
//
// This file is self-contained and handles all general purpose binary search algorithms.  It can
// be used as an include file for other stand-alone projects.
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




//////////
// Structures
//////
	struct SBSearch
	{
		SCallback*		cb;

		void*			data;
		s32				testResult;
	};

	struct SBSearchCallback
	{

		//////////
		// For iBSearch_find()
		//////
			union {
				void*	needle;				// Set by the caller as a reference to the thing being sought after
				SDatum*	datumNeedle;
			};
			union {
				void*	haystack;			// Set by the iBSearch*() algorithms to perform the test
				SDatum*	datumHaystack;
			};
			union {
				uptr	_binarySearchFunc;
				s32		(*binarySearchFunc)	(SBSearchCallback* bcb);
			};


		//////////
		// For iBSearch_sort()
		//////
			union {
				cvp		left;
				SDatum*	datumLeft;
			};
			union {
				cvp		right;
				SDatum*	datumRight;
			};
			union {
				uptr	_qsortCmpFunc;
				s32		(*qsortCmpFunc)		(SBSearchCallback* bcb);
			};

	};


//////////
// Functions
//////
	void				iBSearch_append									(SBuilder* list, void* ptr);
	bool				iBSearch_sort									(SBuilder* list, SBSearchCallback* bcb);
	int					iiBSearch_sort__callback						(void* vbcb, cvp left, cvp right);
	bool				iBSearch_find									(SBuilder* list, SBSearchCallback* bcb, void** ptrOut, bool tlCouldHaveDuplicates = false, bool tlReturnClosestFindOnNofinds = false);




//////////
//
// Called to append the indicated content pointer to the builder.  It's
// mostly a code-documenting wrapper for a call to iBuilder_appendData().
//
//////
	void iBSearch_append(SBuilder* list, void* ptr)
	{
		// Append the pointer
		iBuilder_append_uptr(list, (u32)ptr);
	}




//////////
//
// Called to perform a qsort on the content through an indirect callback
//
//////
	bool iBSearch_sort(SBuilder* list, SBSearchCallback* bcb)
	{
		// Make sure our environment is sane
		if (list && bcb && bcb->_qsortCmpFunc)
		{
			// Sort
			qsort_s(list->buffer, list->populatedLength / sizeof(void*), sizeof(void*), &iiBSearch_sort__callback, bcb);

			// Indicate success
			return(true);
		}

		// Something's invalid
		return(false);
	}

	// qsort callback
	int iiBSearch_sort__callback(void* vbcb, cvp left, cvp right)
	{
		SBSearchCallback* bcb;


		// Store the parameters
		bcb				= (SBSearchCallback*)vbcb;
		bcb->datumLeft	= *(SDatum**)left;
		bcb->datumRight	= *(SDatum**)right;

		// Call the qsort compare function
		return(bcb->qsortCmpFunc(bcb));
	}




//////////
//
// Called to perform a binary search to find the indicated key in bcb->needle.  Sets
// bcb->haystack at each callback, and when found, updates the ptrOut record (if present).
//
//////
	bool iBSearch_find(SBuilder* list, SBSearchCallback* bcb, void** ptrOut, bool tlCouldHaveDuplicates, bool tlReturnClosestFindOnNofinds)
	{
		bool	llFound;
		s32		lnLo, lnHi, lnMid, lnResult;
		cs32	lnStep = sizeof(void*);


		// Determine the initial range
		lnLo	= 0;
		lnHi	= (list->populatedLength / lnStep) - 1;


		//////////
		// Iterate until we cross pointers, or find our entry
		//////
			lnMid = lnHi / 2;
			while (lnMid >= lnLo && lnMid <= lnHi)
			{

				//////////
				// Compare this entry
				//////
					bcb->haystack	= *(void**)(list->buffer + (lnMid * lnStep));
					lnResult		= bcb->binarySearchFunc(bcb);


				//////////
				// Was this the find?
				//////
					if (lnResult == 0)
					{
						// Yes
						if (tlCouldHaveDuplicates && lnMid > 0)
						{
							// Iterate back one and, if found, continue with our binary search to find the first duplicate match
							bcb->haystack = *(void**)(list->buffer + ((lnMid - 1) * lnStep));
							if (bcb->binarySearchFunc(bcb) == 0)
							{
								// It's still a match, so continue iterating
								goto toward_lo;
							}
							// If we get here, there was no match above (we're on the first / top match)
						}

						// We have our find
						llFound = true;
						break;

					} else if (lnResult > 0) {
						// Needle was greater than haystack
						lnLo = lnMid + 1;

					} else {
						// Needle was less than haystack
toward_lo:
						lnHi = lnMid - 1;
					}


				//////////
				// Find out where we are
				//////
					if (lnLo > lnHi)
					{
						// No find
						llFound = false;
						break;

					} else if (lnLo == lnHi) {
						// This is the last one to try
						lnMid			= lnLo;
						bcb->haystack	= *(void**)(list->buffer + (lnMid * lnStep));
						llFound = (bcb->binarySearchFunc(bcb) == 0);
						break;

					} else {
						// Continue on
						lnMid = (lnHi + lnLo) / 2;
					}

			}


		//////////
		// Indicate our find / no-find
		//////
			if (ptrOut)
				*ptrOut = ((llFound || tlReturnClosestFindOnNofinds) ? *(void**)(list->buffer + (lnMid * lnStep)) : NULL);

			// Indicate our result
			return(llFound);
	}
