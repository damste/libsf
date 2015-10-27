//////////
//
// /libsf/source/vjr/source/sound/sound.h
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
//     Jul.31.2014
//////
// Change log:
//     Jul.31.2014 - Initial creation
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
// Tone
//////
	struct _isSoundTone
	{
		u32				nMilliseconds;									// How many milliseconds to generate?
		u32				nSamplesToGenerate;								// Based on milliseconds, how many samples to generate?
		u32				nSamplesGenerated;								// How many samples have been generated thus far?

		// Tone 1
		f32				fAccumulator1;									// Accumulated value for sine wave tones
		f32				fHertz1;										// Frequency

		// Tone 2
		f32				fAccumulator2;									// Accumulated value for sine wave tones
		f32				fHertz2;										// Frequency

		// Tone 3
		f32				fAccumulator3;									// Accumulated value for sine wave tones
		f32				fHertz3;										// Frequency

		// Tone 4
		f32				fAccumulator4;									// Accumulated value for sine wave tones
		f32				fHertz4;										// Frequency
	};



//////////
// Use this function as a template for the callback function sent to sound_createStream()
//////
	struct _isSSoundCallback
	{
		union {
			u64		_callback;
			void	(WINAPI *callback)	(f32* sampleBuffer, u32 tnSamples, bool* tlContinueAfterThisSampleSet);
		};
	};



//////////
// Stream
//////
	struct _isSoundStream
	{
		_isSSoundCallback filler;									// Callback to fill our stream data
	};




//////////
// Sound
//////
	struct _isSSound
	{
		SLL				ll;												// 2-way link list
		
		// Flags
		bool			isPlaying;										// Is the stream playing?
		bool			inDeleteQueue;									// Should this item be deleted when next it stops playing?

		// Stream buffer and channel volume
		// Each sound channel populates its own samples, and then these are mixed together
		f32*			samples;										// Each sample is 0.0 to 1.0 based on its value
		f32				volume;											// How loud should this channel be (0.0f - 1.0f)

		// Shared structure based on whatever identity it has
		bool			isStream;										// Is this a sound stream? no=tone
		union {
			_isSoundStream	stream;										// Sound streams are callbacks to request sound data
			_isSoundTone	tone;										// Sound tones are combined tones computed upon demand
		};
	};




//////////
// Global variables and constants
//////
#ifndef M_PI
	#define M_PI 3.14159265358979323846
#endif
	const f32		_2PI						= (f32)M_PI * 2.0f;	// 2 * pi
	bool			glSDL_Initialized			= false;			// A global flag indicating if the SDL initialized properly
	SStartEnd		gseRootSounds;									// List of all sound objects currently known about
	SDL_AudioSpec	gsdlDesired;									// What we request of SDL
	SDL_AudioSpec	gsdlObtained;									// What SDL gives us
	u16				gnFrequency					= 44100;			// We default to 44.1 kHz (standard CD-ROM quality)
	f32				gfFrequencyMultiplier		= (f32)_2PI / 44100.0f;



//////////
// Forward declarations
//////
	void			iSound_initialize			(void);
	void			iSound_playControl			(bool tlShouldBePlaying);
	void			iSound_sdl_callback			(void* user, Uint8* stream, int length);
	bool			iSound_DeleteValidate		(SStartEndCallback* cb);
	void			iSound_requestStreams		(SStartEndCallback* cb);
	void			iiSound_generateTones		(_isSSound* tss, u32 tnSamples);

	// These two create functions return a handle
	u64				iSound_createTone			(SThisCode* thisCode, f32 tfHertz1, f32 tfHertz2, f32 tfHertz3, f32 tfHertz4, u32 tnDurationMilliseconds);
	u64				iSound_createStream			(SThisCode* thisCode, u32 tnSamplesPerSecond, u64 tnSoundFillerCallbackFunction);

	// These functions are used once a tone or stream was already created
	u64				iSound_setVolume			(SThisCode* thisCode, u64 tnHandle, f32 tfVolume);	// Volume in range 0..1
	u64				iSound_playStart			(SThisCode* thisCode, u64 tnHandle, f32 tfVolume);
	u64				iSound_playCancel			(SThisCode* thisCode, u64 tnHandle);
	u64				iSound_deleteHandle			(SThisCode* thisCode, u64 tnHandle);
