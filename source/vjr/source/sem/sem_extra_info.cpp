//////////
//
// /libsf/source/vjr/source/sem/sem_extra_info.cpp
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
// Version 0.57
// Copyright (c) 2015 by Rick C. Hodgin
//////
// Last update:
//     Jan.11.2014
//////
// Change log:
//     Jan.11.2014 - Initial creation
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
//




//////////
//
// Called to allocate a new extra info and append it from the chain
//
//////
	SExtraInfo* iExtraInfo_allocate(SEM* sem, SLine* line, SExtraInfo** root)
	{
		SExtraInfo* ei;

		
		// Make sure our environment is sane
		ei = NULL;
		if (sem && line && root)
		{
			// Allocate a new one
			ei = (SExtraInfo*)iLl_appendNewNodeAtEnd((SLL**)root, sizeof(SExtraInfo));
		}

		// Indicate our status
		return(ei);
	}




//////////
//
// Called to free the extra info associated with this entry
//
//////
	void iExtraInfo_removeAll(SEM* sem, SLine* line, SExtraInfo** root, bool tlDeleteSelf)
	{
		SExtraInfo*		ei;
		SExtraInfo*		eiNext;


		// Make sure our environment is sane
		if (root && *root)
		{
// TODO:  COMPLETELY UNTESTED.  BREAKPOINT AND EXAMINE.
debug_break;
			// Iterate through all entries in the chain
			ei = *root;
			while (ei)
			{
				// Note the next entry
				eiNext = ei->ll.nextExtraInfo;


				//////////
				// Call any freeInternal() functions to the data contained within and manually delete the extra info block
				//////
					if (ei->_freeInternal!= 0)
						ei->freeInternal(NULL, line, ei);

					// Now, manually free the actual info block itself
					iDatum_delete(&ei->info, false);


				// Free self if need be
				if (tlDeleteSelf)
					free(ei);

				// Move to next entry
				ei = eiNext;
			}

			// Reset the root pointer
			*root = NULL;
		}
	}




//////////
//
// Called to process the extra info block's callbacks (if any)
//
//////
	void iExtraInfo_access(SEM* sem, SLine* line)
	{
		// If there's a callback, call it
		if (sem && line && line->extra_info)
			iiExtraInfo_callbackCommon(sem, line, _EXTRA_INFO_ON_ACCESS);
	}

	void iExtraInfo_arrival(SEM* sem, SLine* line)
	{
		// If there's a callback, call it
		if (sem && line && line->extra_info)
			iiExtraInfo_callbackCommon(sem, line, _EXTRA_INFO_ON_ARRIVAL);
	}

	void iExtraInfo_update(SEM* sem, SLine* line)
	{
		// If there's a callback, call it
		if (sem && line && line->extra_info)
			iiExtraInfo_callbackCommon(sem, line, _EXTRA_INFO_ON_UPDATE);
	}

	void iiExtraInfo_callbackCommon(SEM* sem, SLine* line, s32 tnCallbackType)
	{
		SExtraInfo* ei;


// TODO:  COMPLETELY UNTESTED.  BREAKPOINT AND EXAMINE.
debug_break;
		// Iterate through each one and call its host
		ei = line->extra_info;
		while (ei)
		{
			switch (tnCallbackType)
			{
				case _EXTRA_INFO_ON_ACCESS:
					// Call this one if it has an onAccess member
					if (ei->_onAccess)		ei->onAccess(sem, line, ei);
					break;

				case _EXTRA_INFO_ON_ARRIVAL:
					// Call this one if it has an onArrival member
					if (ei->_onArrival)		ei->onArrival(sem, line, ei);
					break;

				case _EXTRA_INFO_ON_UPDATE:
					// Call this one if it has an onUpdate member
					if (ei->_onUpdate)		ei->onUpdate(sem, line, ei);
					break;
			}

			// Move to next one
			ei = ei->ll.nextExtraInfo;
		}
	}
