//////////
//
// /libsf/source/vjr/source/compiler/sourcelight/sourcelight.cpp
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
// Version 0.59
// Copyright (c) 2015 by Rick C. Hodgin
//////
// Last update:
//     Dec.04.2015
//////
// Change log:
//     Dec.04.2015 - Initial creation
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
//     ____                                 _      _         _      _   
//    / ___|   ___   _   _  _ __  ___  ___ | |    (_)  __ _ | |__  | |_ 
//    \___ \  / _ \ | | | || '__|/ __|/ _ \| |    | | / _` || '_ \ | __|
//     ___) || (_) || |_| || |  | (__|  __/| |___ | || (_| || | | || |_ 
//    |____/  \___/  \__,_||_|   \___|\___||_____||_| \__, ||_| |_| \__|
//                                                    |___/
//  SourceLight -- A companion utility for augmenting editors and compilers.
//
//////////




//////////
//
// Called to reset the sourceLight window to an empty state
//
//////
	void iSourceLight_reset(void)
	{
		RECT lrc;


		// If we have a sourceLight bitmap...
		if (bmpSourceLight)
		{
			// Make it all white
			SetRect(&lrc, 0, 0, bmpSourceLight->bi.biWidth, bmpSourceLight->bi.biHeight);
			iBmp_fillRect(bmpSourceLight, &lrc, whiteColor, whiteColor, whiteColor, whiteColor, false, NULL, false);

			// Reset the coordinates to the top
			gnSourceLightX	= _SOURCELIGHT_MARGIN;
			gnSourceLightY	= _SOURCELIGHT_MARGIN;
		}
	}




//////////
//
// Called to copy the sourceLight contents to the indicated object's bitmap
//
///////
	bool iSourceLight_copy(SWindow* win, SObject* obj)
	{
		SThisCode*	thisCode = NULL;
		s32			scrollX, scrollY;
		RECT		lrc;


		// Make sure our environment is sane
		if (obj && obj->bmp && bmpSourceLight)
		{
			//////////
			// Grab our scroll offsets
			//////
				scrollX = iObjProp_get_s32_direct(obj, _INDEX_SCROLLX);
				scrollY = iObjProp_get_s32_direct(obj, _INDEX_SCROLLX);


			//////////
			// Copy over the part that will fit
			//////
				iiBmp_bitBltPortion(obj->bmp, 0, 0, obj->bmp->bi.biWidth, obj->bmp->bi.biHeight, bmpSourceLight, scrollX, scrollY);


			//////////
			// Fill in any rectangles beyond the scroll
			//////
// TODO:  An optimization here would be to not overlay any portion in the lower-right both horizontally and vertically
				// Portion at the right
				if (bmpSourceLight->bi.biWidth - scrollX < obj->bmp->bi.biWidth)
				{
					// From the edge of the sourceLight content to the extent of the bitmap horizontally
					SetRect(&lrc, bmpSourceLight->bi.biWidth - scrollX, 0, obj->bmp->bi.biWidth, obj->bmp->bi.biHeight);
					iBmp_fillRect(obj->bmp, &lrc, whiteColor, whiteColor, whiteColor, whiteColor, false, NULL, false);
				}

				// Portion at the bottom
				if (bmpSourceLight->bi.biHeight - scrollY < obj->bmp->bi.biHeight)
				{
					// From the edge of the sourceLight content to the extent of the bitmap horizontally
					SetRect(&lrc, 0, bmpSourceLight->bi.biHeight - scrollY, obj->bmp->bi.biWidth, obj->bmp->bi.biHeight);
					iBmp_fillRect(obj->bmp, &lrc, whiteColor, whiteColor, whiteColor, whiteColor, false, NULL, false);
				}
		}

		// Indicate that the processing should continue
		return(true);
	}




//////////
//
// Called to update the sourceLight context based on where we are
//
//////
	void iiSourceLight_oneThread(void)
	{
		// Make sure we have a thread pool
		if (!gsThreadPool_sourceLight)
			gsThreadPool_sourceLight = iThreadPool_allocate();

		// Add the current thread
		iThreadPool_appendThread(gsThreadPool_sourceLight);
		iThreadPool_unengage_allExceptCurrent(gsThreadPool_sourceLight);
	}

	DWORD WINAPI iSourceLight_update(LPVOID lpParameter)
	{
		SObject*	obj;


// TODO:  Dec.04.2015 RCH -- code is under development
return;
		// Make sure we're the only thread running
		iiSourceLight_oneThread();

		// Grab our object
		obj = (SObject*)lpParameter;
		if (obj)
		{
			// SourceLight updates based on context
			if (obj->objType == _OBJ_TYPE_EDITBOX)
			{
				debug_nop;
			}
		}

		// All done
		iThreadPool_unengage(gsThreadPool_sourceLight);
		// Control will never return here, but Microsoft's compilers require this:
		return(0);
	}
