//////////
//
// /libsf/source/vjr/source/sound/sound.cpp
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
// Copyright (c) 2013 by Rick C. Hodgin
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
//
// Called to initialize the sound system
//
//////
	void iSound_initialize(void)
	{
		//////////
		// Initialize our root sounds array
		//////
			memset(&gseRootSounds, 0, sizeof(gseRootSounds));


		//////////
		// Setup the desired structure
		//////
			memset(&gsdlDesired, 0, sizeof(gsdlDesired));
			gsdlDesired.freq		= gnFrequency;			// 44.1 kHz
			gsdlDesired.format		= AUDIO_S16SYS;			// 16-bit signed audio
			gsdlDesired.channels	= 1;					// Mono
			gsdlDesired.samples		= gnFrequency / 50;		// Audio buffer (larger buffers reduces risk of dropouts but increases response time)
			gsdlDesired.callback	= iSound_sdl_callback;	// Our callback function
			gsdlDesired.userdata	= NULL;					// No user data is passed


		//////////
		// Open the audio device
		//////
			glSDL_Initialized = false;
			if (SDL_Init(SDL_INIT_AUDIO) >= 0)
			{
				if (SDL_OpenAudio(&gsdlDesired, &gsdlObtained) >= 0)
				{
					// Reset the frequency and a shorthand for faster computation on tone generation
					glSDL_Initialized		= true;
					gnFrequency				= gsdlObtained.freq;			// Store our actual frequency
					gfFrequencyMultiplier	= (f32)_2PI / (f32)gnFrequency;

				} else {
					// Obtain the error
// For debugging:
//					char* error = SDL_GetError();
//					error = NULL;
				}

			} else {
				// Obtain the error
// For debugging:
//				char* error = SDL_GetError();
//				error = NULL;
			}
	}



//////////
//
// Called to begin or end playing
//
//////
	void iSound_playControl(bool tlShouldBePlaying)
	{
		// Did SDL initialize properly?
		if (glSDL_Initialized)
		{
			// Yes.
			// What do they want us to do?
			if (tlShouldBePlaying)		SDL_PauseAudio(0);		// Play it
			else						SDL_PauseAudio(1);		// Pause it
		}
	}




//////////
//
// Callback from SDL itself to fill a stream bucket
//
//////
	void iSound_sdl_callback(void* user, Uint8* stream, int length)
	{
		SThisCode*			thisCode = NULL;
		f64					lfSampleTotal;
		u32					lnI, lnLength, lnSampleCount;
		Sint16*				stream16;
		_isSSound*			lss;
		SMasterList*		lml;
		SStartEndCallback	cb;


		// Make sure our environment is sane
		if (gseRootSounds.masterCount != 0)
		{
			// Populate the streams based on inputs
			lnLength = length / sizeof(Sint16);
			cb._func	= (uptr)&iSound_requestStreams;
			cb.extra	= lnLength;
			iSEChain_iterateThroughForCallback(&gseRootSounds, &cb);
			// Once we get here, all streams have been populated

			// Iterate through each channel merging them together
			stream16 = (Sint16*)stream;
			for (lnI = 0; lnI < lnLength; lnI++)
			{
				// Build this sample's total
				lfSampleTotal	= 0.0;
				lnSampleCount	= 0;

				// Iterate through each master list entry
				lml = gseRootSounds.root;
				while (lml)
				{
					// Is this a
					if (lml->used)
					{
						// Grab this entry
						lss = (_isSSound*)lml->ptr;

						// Is it playing?
						if (lss->isPlaying && lss->samples)
						{
							// Add it to the total
							lfSampleTotal += (f64)(32767.0f * lss->samples[lnI] * lss->volume);
							++lnSampleCount;
						}
					}

					// Move to next entry
					lml = (SMasterList*)lml->ll.next;
				}

				// Is anything playing?
				if (lnSampleCount == 0)
				{
					// Nothing is currently being played, which means everything turned off during the last cycle
					// Tell SDL to stop wasting its time. :-)
					iSound_playControl(false);
					break;
				}


				// When we get here, we have our sample total
				stream16[lnI] = (Sint16)(lfSampleTotal / lnSampleCount);
			}
		}
	}




//////////
//
// Callback to scan through each pointer and see if the item is playing.
// Returns the first item it finds playing
//
//////
	bool iSound_DeleteValidate(SStartEndCallback* cb)
	{
		// Make sure our environment is sane
		if (cb && cb->ptr && ((_isSSound*)cb->ptr)->isPlaying)
			return(true);		// This is the match

		// If we get here, this item is not playing
		return(false);		// We need to examine more entries, indicate this one is not it
	}




//////////
//
// Called to request that each stream populate itself
//
//////
	void iSound_requestStreams(SStartEndCallback* cb)
	{
		_isSSound* lss;


		// Make sure our environment is sane
		if (cb && cb->ptr)
		{
			// Grab our pointer
			lss = (_isSSound*)cb->ptr;

			// Is this item being processed?
			if (lss->isPlaying && lss->samples)
			{
				// What exactly are we processing?
				if (lss->isStream)
				{
					// Ask the stream to fill itself
					lss->stream.filler.callback(lss->samples, (u32)cb->extra, &lss->isPlaying);
// TODO:  Based on runtime observation, when the system is very active the sound is jittery.
//        We should add a double-buffer to request the one ahead of the one that will be played
//        that way we can immediately switch over to the previous 2nd buffer while we're filling
//        the request for the next one.  A triple buffer might even be better.

				} else {
					// Generate the tone(s)
					iiSound_generateTones(lss, (u32)cb->extra);
				}
			}
		}
	}




//////////
//
// Called to generate tones upon demand
//
//////
	void iiSound_generateTones(_isSSound* tss, u32 tnSamples)
	{
		u32		lnI;
		f32		lfCount, lfTone, lfHertz1, lfHertz2, lfHertz3, lfHertz4;
		f32*	lfAccum1;
		f32*	lfAccum2;
		f32*	lfAccum3;
		f32*	lfAccum4;


		//////////
		// Is Tone 1 active?
		//////
			lfCount = 0.0f;
			if (tss->tone.fHertz1 >= 0.0f)
			{
				// Yes
				lfAccum1	= &tss->tone.fAccumulator1;
				lfHertz1	= tss->tone.fHertz1;
				++lfCount;

			} else {
				// No
				lfAccum1 = NULL;
			}


		//////////
		// Is Tone 2 active?
		//////
			if (tss->tone.fHertz2 >= 0.0f)
			{
				lfAccum2	= &tss->tone.fAccumulator2;
				lfHertz2	= tss->tone.fHertz2;
				++lfCount;

			} else {
				lfAccum2 = NULL;
			}


		//////////
		// Is Tone 3 active?
		//////
			if (tss->tone.fHertz3 >= 0.0f)
			{
				lfAccum3	= &tss->tone.fAccumulator3;
				lfHertz3	= tss->tone.fHertz3;
				++lfCount;

			} else {
				lfAccum3 = NULL;
			}


		//////////
		// Is Tone 4 active?
		//////
			if (tss->tone.fHertz4 >= 0.0f)
			{
				lfAccum4	= &tss->tone.fAccumulator4;
				lfHertz4	= tss->tone.fHertz4;
				++lfCount;

			} else {
				lfAccum4	= NULL;
				lfHertz4	= 1.0;	// Added to stop GCC from incorrectly warning about lfHertz4 not being initialized
			}


		//////////
		// Iterate through for every sample
		//////
			if (lfCount == 0.0f)
			{
				// Nothing to do, all channels are not active
				for (lnI = 0; lnI < tnSamples; lnI++)
					tss->samples[lnI] = 0.0f;

			} else {
				// Construct the (combined) tones
				for (lnI = 0; lnI < tnSamples; lnI++)
				{
					//////////
					// Reset the sample
					//////
						lfTone = 0.0f;


					//////////
					// Append the tones
					//////
						if (lfAccum1)
						{
							lfTone		+= (f32)cos(*lfAccum1 * gfFrequencyMultiplier);
							*lfAccum1	+= lfHertz1;
						}

						if (lfAccum2)
						{
							lfTone		+= (f32)cos(*lfAccum2 * gfFrequencyMultiplier);
							*lfAccum2	+= lfHertz2;
						}

						if (lfAccum3)
						{
							lfTone		+= (f32)cos(*lfAccum3 * gfFrequencyMultiplier);
							*lfAccum3	+= lfHertz3;
						}

						if (lfAccum4)
						{
							lfTone		+= (f32)cos(*lfAccum4 * gfFrequencyMultiplier);
							*lfAccum4	+= lfHertz4;
						}


					//////////
					// Store the tone
					//////
						tss->samples[lnI] = (lfTone / lfCount);


					//////////
					// Have we reached our maximum?
					//////
						if (++tss->tone.nSamplesGenerated >= tss->tone.nSamplesToGenerate)
						{
							// We are done, so next iteration this one should be deleted
							tss->isPlaying				= false;
							tss->tone.nSamplesGenerated	= 0;		// Reset
							break;		// Yes
						}

				}

				// Round out the sample buffer with silence
				for ( ; lnI < tnSamples; lnI++)
					tss->samples[lnI] = 0.0f;
			}
	}




//////////
//
// Called to play a tone or set of up to five harmonic tones of a specific frequency for a specified duration.
// Returns a handle which can be used to play or terminate the tone.
//
// Note:  Use -1 for hertz entries to disable that tone channel.
//
//////
	u64 iSound_createTone(f32 tfHertz1, f32 tfHertz2, f32 tfHertz3, f32 tfHertz4, u32 tnDurationMilliseconds)
	{
		_isSSound*	lss;
		bool		llResult;


		// Was SDL initialized properly?
		if (glSDL_Initialized)
		{
			// Add this item to the list of sounds
			lss = (_isSSound*)iSEChain_append(&gseRootSounds, iGetNextUid(), iGetNextUid(), sizeof(_isSSound), 1, &llResult);
			if (lss)
			{
				// Store the relevant information
				lss->isStream					= false;
				lss->tone.fHertz1				= tfHertz1;
				lss->tone.fHertz2				= tfHertz2;
				lss->tone.fHertz3				= tfHertz3;
				lss->tone.fHertz4				= tfHertz4;

				// Set our stoppers
				lss->tone.nMilliseconds			= tnDurationMilliseconds;									// How many milliseconds to generate tones for?
				lss->tone.nSamplesToGenerate	= (u32)(gnFrequency * (tnDurationMilliseconds / 1000.0f));	// Based on milliseconds, how many samples to generate?
				lss->tone.nSamplesGenerated		= 0;														// How many samples have been generated thus far?

				// Create our stream buffer
				lss->samples		= (f32*)malloc(gsdlObtained.samples * sizeof(f32));

				// All done
				return(lss->ll.uniqueId);
			}
		}
		// If we get here, failure
		return(-1);
	}




//////////
//
// Called to play a stream at the indicated frequency using callbacks.
// Returns a handle which can be used to play or terminate the stream.
//
//////
	u64 iSound_createStream(u32 tnSamplesPerSecond, u64 tnSoundFillerCallbackFunction)
	{
		_isSSound*	lss;
		bool		llResult;


		// Was SDL initialized properly?
		if (glSDL_Initialized)
		{
			// Add this item to the list of sounds
			lss = (_isSSound*)iSEChain_append(&gseRootSounds, iGetNextUid(), iGetNextUid(), sizeof(_isSSound), 1, &llResult);
			if (lss)
			{
				// Store the relevant information
				lss->isStream					= true;
				lss->stream.filler._callback	= tnSoundFillerCallbackFunction;

				// Create our stream buffer
				lss->samples					= (f32*)malloc(gsdlObtained.samples * sizeof(f32));

				// All done
				return(lss->ll.uniqueId);
			}
		}
		// If we get here, failure
		return(-1);
	}




//////////
//
// Called to set the volume either on-the-fly while the stream is playing, or before or after it plays.
//
//////
	u64 iSound_setVolume(u64 tnHandle, f32 tfVolume)
	{
		_isSSound*	lss;


		// Search for the indicated handle
		lss = (_isSSound*)iSEChain_searchByUniqueId(&gseRootSounds, tnHandle);
		if (lss && lss->samples)
		{
			// They are just updating the volume
			lss->volume	= max(min(tfVolume, 1.0f), 0.0f);

			// All done
			return(lss->ll.uniqueId);
		}
		// If we get here, failure
		return(-1);
	}




//////////
//
// Called to re/start a previous sound, or to update the volume.
//
// Usage:  oss_soundPlayStart(handle, -1.0f)         // Re/start the sound, but do not alter the volume
//         oss_soundPlayStart(handle, 0.5f)          // Change the volume of the sound, and start it if it's stopped, but if it's already started then just change the volume (don't restart the sound)
//
//////
	u64 iSound_playStart(u64 tnHandle, f32 tfVolume)
	{
		_isSSound*	lss;


		// Search for the indicated handle
		lss = (_isSSound*)iSEChain_searchByUniqueId(&gseRootSounds, tnHandle);
		if (lss && lss->samples)
		{
			// Turn it on (even if it's already on)
			lss->isPlaying	= true;

			// Did they specify to change the volume?
			if (tfVolume >= 0.0f)
			{
				// They are just updating the volume
				lss->volume	= min(tfVolume, 1.0f);

			} else {
				// They are just re/starting the sound
				if (!lss->isStream)
				{
					// For tones, we restart the sound each time they start it (unless a volume is specified)
					lss->tone.nSamplesGenerated = 0;
				}
			}

			// Tell SDL to turn itself on (in case it's off, it might already be playing)
			iSound_playControl(true);

			// All done
			return(lss->ll.uniqueId);
		}
		// If we get here, failure
		return(-1);
	}




//////////
//
// Called to cancel a playing sound
//
//////
	u64 iSound_playCancel(u64 tnHandle)
	{
		_isSSound*	lss;


		// Search for the indicated handle
		lss = (_isSSound*)iSEChain_searchByUniqueId(&gseRootSounds, tnHandle);
		if (lss && lss->samples)
		{
			// Turn it on (even if it's already on)
			lss->isPlaying = false;

			// All done
			return(lss->ll.uniqueId);
		}
		// If we get here, failure
		return(-1);
	}




//////////
//
// Called to delete a previous sound handle
//
//////
	u64 iSound_deleteHandle(u64 tnHandle)
	{
		_isSSound*			lss;
		_isSSound*			lssPlaying;
		SStartEndCallback	cb;


		// Search for the indicated handle
		lss = (_isSSound*)iSEChain_searchByUniqueId(&gseRootSounds, tnHandle);
		if (lss)
		{
			// Turn it off, and add it to the delete queue
			lss->isPlaying		= false;
			lss->inDeleteQueue	= true;

			// We need to see if this is the last item playing, and if so, then turn off SDL
			cb._func	= (uptr)&iSound_DeleteValidate;
			lssPlaying	= (_isSSound*)iSEChain_searchByCallback(&gseRootSounds, &cb);

			// Is anything else still playing?
			if (!lssPlaying)
			{
				// Nope
				iSound_playControl(false);
			}

			// All done
			return(lss->ll.uniqueId);
		}
		// If we get here, failure
		return(-1);
	}
