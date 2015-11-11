//////////
//
// /libsf/source/vjr/source/datum/datum.h
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
// Copyright (c) 2014 by Rick C. Hodgin
//////
// Last update:
//     Nov.27.2014
//////
// Change log:
//     Nov.27.2014 - Initial creation
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
//  _____          _
// |  __ \        | |
// | |  | |  __ _ | |_  _   _  _ __ ___
// | |  | | / _` || __|| | | || '_ ` _ \
// | |__| || (_| || |_ | |_| || | | | | |
// |_____/  \__,_| \__| \__,_||_| |_| |_|
// Datum --- Data w/allocation and length
//
//////////




// #pragma once
#ifndef __DATUM_H__
#define __DATUM_H__


struct SDateTime;
struct SDateTimeX;
struct SDate;
struct SBgra;
struct SBgr;
struct SLine;
struct SComp;

#ifndef IDispatch
    struct IDispatch;
#endif

	struct SDatum
	{
		union {
			s8*			data;					// Content
			uptr		_data;					// Address of content
			s8*			data_s8;				// To access the data as s8
			u8*			data_u8;				// To access the data as u8
			u64*		data_u64;				// To access the data as u64
			s64*		data_s64;				// To access the data as s64
			u32*		data_u32;				// To access the data as u32
			s32*		data_s32;				// To access the data as s32
			u16*		data_u16;				// To access the data as u16
			s16*		data_s16;				// To access the data as s16
			f32*		data_f32;				// To access the data as f32
			f64*		data_f64;				// To access the data as f64
			cs8*		data_cs8;				// To access the data as cs8
			cu8*		data_cu8;				// To access the data as cu8
			void*		data_vp;				// To access the data as a void pointer
			IDispatch*	data_idispatch;			// To access the data as an IDispatch pointer

			// Common structures (used for displaying content during debugging)
			SDateTime*	data_dt;				// To access the data as a datetime
			SDateTimeX*	data_dtx;				// To access the data as a datetimex
			SDate*		data_date;				// To access the data as a date in the text-form YYYYMMDD
			SBgra*		data_bgra;				// To access the data as SBgra
			SBgr*		data_bgr;				// To access the data as SBgr
			SMapm*		data_big;				// To access the data as an arbitrary precision structure wrapped around SMapm (see 3rd_party\mapm\m_apm.h)
		};
		s32				length;					// Content length
	};

	struct SProperty
	{
		bool		name_allocated;				// Was the name datum allocated?
		bool		value_allocated;			// Was the value datum allocated?

		SDatum*		name;						// Name for this property
		SVariable*	value;						// Value for this name
	};


	void					iDatum_allocateSpace					(SDatum* datum,		s32 dataLength);
	SDatum*					iDatum_allocate							(cs8* data,			s32 dataLength = -1);
	SDatum*					iDatum_allocate							( s8* data,			s32 dataLength = -1);
	SDatum*					iDatum_allocate							(cu8* data,			s32 dataLength = -1);
	SDatum*					iDatum_allocate							( u8* data,			s32 dataLength = -1);

	void					iDatum_duplicate						(SDatum* datum,  u8* data, s32 dataLength);
	void					iDatum_duplicate						(SDatum* datum,  s8* data, s32 dataLength);
	void					iDatum_duplicate						(SDatum* datum, cu8* data, s32 dataLength);
	void					iDatum_duplicate						(SDatum* datum, cs8* data, s32 dataLength);
	void					iDatum_duplicate						(SDatum* datumDst, SDatum* datumSrc);
	void					iDatum_duplicate_fromComp				(SDatum* datum, SComp* comp);
	void					iiDatum_duplicate_fromComp				(SDatum* datum, SComp* comp);
	SDatum*					iDatum_populate_fromComp				(SDatum* datum, SComp* comp);

	bool					iDatum_resize							(SDatum* datum, s32 newDataLength);
	s32						iDatum_compare							(SDatum* datumLeft, SDatum* datumRight);
	s32						iDatum_compare							(SDatum* datumLeft, s8*  data, s32 dataLength);
	s32						iDatum_compare							(SDatum* datumLeft, cs8* data, s32 dataLength);
	s32						iDatum_compare							(SDatum* datumLeft, u8*  data, s32 dataLength);
	s32						iDatum_compare							(SDatum* datumLeft, cu8* data, s32 dataLength);
	void					iDatum_delete							(SDatum** datum);
	void					iDatum_delete							(SDatum* datum, bool tlDeleteSelf);
	void					iiDatum_delete							(SDatum* datum);

	SProperty*				iProperty_allocateAs_character_fromComp	(SComp* name, SComp* value, s32 tnOverrideNameLength = -1, s32 tnOverrideValueLength = -1);
	SProperty*				iProperty_allocateAs_character			(cu8* tcName, s32 tnNameLength, cu8* tcValue, s32 tnValueLength);
	SProperty*				iProperty_allocateAs_s32				(cu8* tcName, s32 tnNameLength, s32 tnValue);
	SProperty*				iProperty_allocateAs_s32				(SDatum* name, s32 tnValue);
	SProperty*				iiProperty_allocate						(SDatum* name, SVariable* value);
	void					iProperty_delete						(SProperty** p);
	SProperty*				iProperty_delete						(SProperty* p, bool tlDeleteSelf);

#endif
