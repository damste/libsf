//////////
//
// /libsf/source/vjr/source/sem/sem_extra_info.h
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
// Extra info contains information about a line of source code
//////
	struct SExtraInfo
	{
		SLL			ll;

		u32			identifier;						// A registered identifier with the system for this extra info block
		u32			identifier_type;				// Application defined type, identifies what's stored in this.info.data
		SDatum		info;							// The extra info block stored for this entry


		//////////
		// Functions to called when the associated line is processed in some way
		//////
		union {
			sptr	_onAccess;					// When the line is accessed
			void	(*onAccess)					(SEM* sem, SLine* line, SExtraInfo* extra_info);
		};

		union {
			sptr	_onArrival;					// When the target implementation is sitting on this line
			void	(*onArrival)				(SEM* sem, SLine* line, SExtraInfo* extra_info);
		};

		union {
			sptr	_onUpdate;					// When the line is updated
			void	(*onUpdate)					(SEM* sem, SLine* line, SExtraInfo* extra_info);
		};


		//////////
		// Function to call before freeing an entry
		//////
		union {
			sptr		_freeInternal;			// Called to free any data in this.info
			SExtraInfo*	(*freeInternal)			(SEM* sem, SLine* line, SExtraInfo* extra_info);
		};
	};




//////////
// Extra info callback codes for callbackCommon
//////
	const s32		_EXTRA_INFO_ON_ACCESS					= 1;
	const s32		_EXTRA_INFO_ON_ARRIVAL					= 2;
	const s32		_EXTRA_INFO_ON_UPDATE					= 3;


//////////
// ExtraInfo
//////
	SExtraInfo*		iExtraInfo_allocate						(SEM* sem, SLine* line, SExtraInfo** root);
	void			iExtraInfo_removeAll					(SEM* sem, SLine* line, SExtraInfo** root, bool tlDeleteSelf);
	void			iExtraInfo_access						(SEM* sem, SLine* line);
	void			iExtraInfo_arrival						(SEM* sem, SLine* line);
	void			iExtraInfo_update						(SEM* sem, SLine* line);
	void			iiExtraInfo_callbackCommon				(SEM* sem, SLine* line, s32 tnCallbackType);
