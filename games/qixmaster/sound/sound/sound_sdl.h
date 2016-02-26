// sound_sdl.h

// Prototype of our callback function
void my_audio_callback(void* userdata, Uint8* stream, int len);

const double	M_PI			= 3.1415926535897923;
const int		FREQUENCY		= 44100;

// For C-based para-diddle LRLL RLRR
int		_CL				= 37 - 1;
int		_CR				= 40 - 1;

int		sbOffset		= 0;
int		sbMax			= 0;
Sint16*	songBuffer		= NULL;

double	amp				= 0.5;

SDL_AudioSpec desired;
SDL_AudioSpec obtained;

double musicalNotes[88] =
{	// 88 piano key frequencies, taken from Wikipedia
	27.5000, 29.1352, 30.8677, 32.7032, 34.6478, 36.7081, 38.8909, 41.2034, 43.6535,
	46.2493, 48.9994, 51.9131, 55.0000, 58.2705, 61.7354, 65.4064, 69.2957, 73.4162,
	77.7817, 82.4069, 87.3071, 92.4986, 97.9989, 103.826, 110.000, 116.541, 123.471,
	130.813, 138.591, 146.832, 155.563, 164.814, 174.614, 184.997, 195.998, 207.652,
	220.000, 233.082, 246.942, 261.626, 277.183, 293.665, 311.127, 329.628, 349.228,
	369.994, 391.995, 415.305, 440.000, 466.164, 493.883, 523.251, 554.365, 587.330,
	622.254, 659.255, 698.456, 739.989, 783.991, 830.609, 880.000, 932.328, 987.767,
	1046.50, 1108.73, 1174.66, 1244.51, 1318.51, 1396.91, 1479.98, 1567.98, 1661.22,
	1760.00, 1864.66, 1975.53, 2093.00, 2217.46, 2349.32, 2489.02, 2637.02, 2793.83,
	2959.96, 3135.96, 3322.44, 3520.00, 3729.31, 3951.07, 4186.01
};

void fadeIn(Sint16* stream, int samples)
{
	int		i;
	float	volume, step;


	volume	= 0.0f;
	step	= 1.0f / (float)samples;
	for (i = 0; i < samples; i++)
	{
		stream[i]	= (Sint16)((float)stream[i] * volume);
		volume		+= step;
	}
}

void fadeOut(Sint16* stream, int samples)
{
	int		i;
	float	volume, step;


	volume	= 1.0f;
	step	= 1.0f / (float)samples;
	for (i = 0; i < samples; i++)
	{
		stream[i]	= (Sint16)((float)stream[i] * volume);
		volume		-= step;
	}
}

void saveSongBufferRaw(char* tcPathname)
{
	FILE* lfh;


	fopen_s(&lfh, tcPathname, "wb+");
	if (lfh)
	{
		fwrite(songBuffer, 1, sbMax, lfh);
		fclose(lfh);
	}
}

void appendToneOntoBuffer(int tnKey, int tnToneMilliseconds, int tnPauseMilliseconds, double tfAmp)
{
	int			i, lnToneSize, lnPauseSize, lnNewSize, lnBase;
	double		v, vf, lfTone, lfAmp;
	Sint16*		lcNew;


	lnToneSize	= (int)((double)FREQUENCY * (double)tnToneMilliseconds	/ (double)1000.0f);
	lnPauseSize	= (int)((double)FREQUENCY * (double)tnPauseMilliseconds	/ (double)1000.0f);
	lnNewSize	= (lnToneSize + lnPauseSize) * sizeof(Sint16);
	if (songBuffer)
	{
		// Re-allocate
		lcNew = (Sint16*)realloc(songBuffer, sbMax + lnNewSize);

	} else {
		// Initially allocate
		lcNew	= (Sint16*)malloc(lnNewSize);
		sbMax	= 0;
	}

	if (lcNew)
	{
		// Generate the tone for that length
		vf		= musicalNotes[tnKey];
		v		= 0.0;
		lnBase	= sbMax / sizeof(Sint16);
		lfAmp	= 1.0;
		for (i = 0; i < lnToneSize; i++)
		{
			// Create the tone
			lfTone = tfAmp * lfAmp * std::cos(v * 2 * M_PI / FREQUENCY);

			// Store the tone
			lcNew[lnBase + i] = (Sint16)lfTone;

			// Increase by our frequency
			v += vf;

			// Increase the amplitude each time
			lfAmp = min(lfAmp * 2.0, 32767.0);
		}

		// Append silence
		for (i = 0; i < lnPauseSize; i++)
			lcNew[lnBase + lnToneSize + i] = /*(Sint16)((float)lcNew[lnBase + lnToneSize + i - 1] * 7.0 / 8.0)*/0;

		// Fade the notes in/out over FREQUENCY / 1000 samples
		fadeIn(lcNew + lnBase, FREQUENCY / 100);
		fadeOut(lcNew + lnBase + lnToneSize - FREQUENCY / 100, FREQUENCY / 100);

		// All done
		songBuffer	= lcNew;
		sbMax		+= lnNewSize;
	}
}

void paradiddle(int offsetL, int offsetR, int offsetSpeed, int count)
{
	int lnI;


	// Repeat for count iterations
	for (lnI = 0; lnI < count; lnI++)
	{
		// LRLL
		appendToneOntoBuffer(_CL + offsetL, 225 + offsetSpeed, 15, 1.0);		// par
		appendToneOntoBuffer(_CR + offsetR, 225 + offsetSpeed, 15, 0.5);		// a
		appendToneOntoBuffer(_CL + offsetL, 225 + offsetSpeed, 15, 0.75);		// did
		appendToneOntoBuffer(_CL + offsetL, 225 + offsetSpeed, 15, 0.75);		// dle

		// RLRR
		appendToneOntoBuffer(_CR + offsetR, 225 + offsetSpeed, 15, 1.0);		// par
		appendToneOntoBuffer(_CL + offsetL, 225 + offsetSpeed, 15, 0.75);		// a
		appendToneOntoBuffer(_CR + offsetR, 225 + offsetSpeed, 15, 0.5);		// did
		appendToneOntoBuffer(_CR + offsetR, 200 + offsetSpeed, 40, 0.5);		// dle
	}
}

void sound_init(void)
{
	if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_AUDIO) < 0)
	{
		fprintf(stderr, "Couldn't initialize audio: %s\n", SDL_GetError());
		exit(-1);
	}


	//////////
	// Setup the desired structure
	//////
		desired.freq		= FREQUENCY;			// 44.1 kHz
		desired.format		= AUDIO_S16SYS;			// 16-bit signed audio
		desired.channels	= 1;					// Stereo
		desired.samples		= FREQUENCY / 20;		// Audio buffer (larger buffers reduces risk of dropouts but increases response time)
		desired.callback	= my_audio_callback;	// Our callback function
		desired.userdata	= NULL;


	//////////
	// Open the audio device
	//////
		if (SDL_OpenAudio(&desired, &obtained) < 0)
		{
			fprintf(stderr, "Couldn't open audio: %s\n", SDL_GetError());
			exit(-1);
		}


	//////////
	// Prepare callback for playing
	//////
		SDL_Surface* screen = SDL_SetVideoMode(200, 200, 16, SDL_SWSURFACE);
		SDL_WM_SetCaption("Audio Example",0);


	//////////
	// Play para-diddles
	//////
		paradiddle(0-12, 0-12, -100, 2);
		paradiddle(-2-12, 2-12, -100, 2);
		paradiddle(-4-12, 0-12, -100, 2);
		paradiddle(-2-12, 2-12, -100, 2);
		saveSongBufferRaw("song.raw");


	//////////
	// Start playing, pause 5 seconds
	//////
		SDL_PauseAudio(0);

		SDL_Event event;
		bool running = true;
		bool shiftdown = false;
		while (running)
		{
			while (SDL_PollEvent(&event))
			{
				/* GLOBAL KEYS / EVENTS */
				switch (event.type)
				{
					case SDL_KEYDOWN:
						switch (event.key.keysym.sym)
						{
							case SDLK_ESCAPE:
								running = false;
								break;

							case SDLK_LSHIFT:
							case SDLK_RSHIFT:
								shiftdown = true;
								break;

							case SDLK_KP_PLUS:
								amp += 0.1;
								if (amp > 1.0)
									amp = 1.0;
								break;

							case SDLK_KP_MINUS:
								amp -= 0.1;
								if (amp <= 0.0)
									amp = 0.0;
								break;

							default:
								break;
						}
						break;

					case SDL_KEYUP:
						switch (event.key.keysym.sym)
						{
							case SDLK_LSHIFT:
							case SDLK_RSHIFT:
								shiftdown = false;
								break;
						}
						break;

					case SDL_QUIT:
						running = false;
						break;
				}
				SDL_Delay(1);
			}
			SDL_Delay(1);
		}


	//////////
	// Close the audio device
	//////
		SDL_CloseAudio();
}


void my_audio_callback(void* userdata, Uint8* stream, int len)
{
	int i;
	Sint16* stream16;


	stream16	= (Sint16*)stream;
	for (i = 0; i < len / 2; i++)
	{
		//////////
		// Pull from the song buffer, amplify by current volume level
		//////
			stream16[i] = (Sint16)(amp * (double)songBuffer[sbOffset++]);
			sbOffset	= sbOffset % (sbMax / sizeof(Sint16));
	}
}
