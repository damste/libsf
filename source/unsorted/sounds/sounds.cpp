// sounds.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string.h>
#include <memory.h>
#include <math.h>

const int _FREQ_COUNT = 2;
const int _MAX_CYCLES = 44100;
const unsigned int _CYCLES_PER_BIT = 32;
const float freqs[] = { 6000.0f, 3000.0f, 1500.0f, 750.0f, 375.0f };

// For decoding, candidate encodings per bit
short candidates[1 << _FREQ_COUNT];
unsigned int counts[1 << _FREQ_COUNT];

unsigned char*	encoding[] = {
	(unsigned char*)"Our Father, who art in Heaven, hallowed be Thy name...",
	(unsigned char*)"Written predominantly in languages other than English.",
	(unsigned char*)"Today is the first day of the rest of my life.",
	(unsigned char*)"Thank you for having a nice day.  You're welcome.",
	(unsigned char*)"Four score and seven years ago, our forefathers..."
};

// Create N 80-character decode buffers
unsigned char decode_buffers[_FREQ_COUNT][80];

void iStoreBit(unsigned int tnDataStream, unsigned int tnBit, bool tlBit)
{
	unsigned int lnChar, lnBit;


	// Determine which char in our round-robin buffer
	lnChar	= (tnBit / 8) % 80;
	lnBit	= 7 - (tnBit % 8);
	decode_buffers[tnDataStream][lnChar] = (decode_buffers[tnDataStream][lnChar] & ~(1 << lnBit)) | ((tlBit) ? 1 << lnBit : 0);
}

int _tmain(int argc, _TCHAR* argv[])
{
	unsigned int	lnI, lnJ, lnK, lnThisChar, lnThisBit, lnTicker, lnBit, lnBitTest, lnMax, lnMaxJ;
	bool			llFlag;
	FILE*			fh;
	float			lfRadian, lfRadianInc, lfTot;
	float			f[_FREQ_COUNT];
	float			v[_FREQ_COUNT];
	short			buffer[_MAX_CYCLES];


	//////////
	// Initialize
	//////
		lfRadian	= 0.0f;
		lfRadianInc	= 1 / 44100.0f;
		for (lnI = 0; lnI < _FREQ_COUNT; lnI++)
		{
			f[lnI] = freqs[lnI];
			v[lnI] = 0.0f;
		}


	//////////
	// Generate the sample
	//////
		fh = fopen("E:\\Desktop\\sound.raw", "wb+");
		for (lnI = 0, lnTicker = 0, lnBit = 0; lnI < _MAX_CYCLES; lnI++, lfRadian += lfRadianInc, lnTicker = (lnTicker + 1) % _CYCLES_PER_BIT, lnBit += ((lnTicker == 0) ? 1 : 0))
		{
			// Update the frequencies for this value
			for (lnJ = 0; lnJ < _FREQ_COUNT; lnJ++)
			{
				// Grab the character
				lnThisChar	= (lnBit / 8) % strlen((const char*)encoding[lnJ]);
				lnThisBit	= (lnBit % 8);

				// If we're on channel 1, encode the data against the frequency
				llFlag = (((encoding[lnJ][lnThisChar] >> lnThisBit) & 0x1) != 0);
				v[lnJ] = sin(lfRadian * f[lnJ]) * ((llFlag) ? 1.0f : 0.0f);		// 1.0f if the bit is 1, 0.0f if the bit is 0
			}

			// Combine and write the output values
			for (lnJ = 0, lfTot = 0.0f; lnJ < _FREQ_COUNT; lnJ++)
				lfTot += v[lnJ];

			// Write the output
			buffer[lnI] = (short)((lfTot / _FREQ_COUNT) * 32768.0f);
		}
		fwrite(&buffer[0], 1, sizeof(buffer), fh);
		fclose(fh);


	//////////
	// Decode the sample by processing the iterations
	//////
		// Compute through the 
		for (lnI = 0, lnTicker = 0, lnBit = 0; lnI < _MAX_CYCLES; lnI++, lfRadian += lfRadianInc, lnTicker = (lnTicker + 1) % _CYCLES_PER_BIT, lnBit += ((lnTicker == 0) ? 1 : 0))
		{
			// Are we on a decode marker?
			if (lnTicker == 0)
			{
				// Are we ready to decode?
				if (lnI != 0)
				{
					// We've just reached the start of the next item, so we check our counts
					for (lnJ = 0, lnMax = 0; lnJ < (1 << _FREQ_COUNT); lnJ++)
					{
						// See where we are
						if (counts[lnJ] > lnMax)
						{
							// Store the max location
							lnMax	= counts[lnJ];
							lnMaxJ	= lnJ;
						}
					}

// TODO:  We should do some data checking here... if counts are the same, then look at the deltas to see which one is better

					// Extract the bits
					for (lnJ = 0, lnBitTest = lnMaxJ; lnJ < _FREQ_COUNT; lnJ++, lnBitTest >>= 1)
					{
						llFlag = (lnBitTest & 0x1);
						if (llFlag)
							iStoreBit(lnJ, lnBit, 1);
					}
				}

				// Reset our counts
				for (lnJ = 0; lnJ < (1 << _FREQ_COUNT); lnJ++)
					counts[lnJ] = 0;

			} else {
				//
				// Compute through the iterations at this time
				for (lnJ = 0; lnJ < (1 << _FREQ_COUNT); lnJ++)
				{
					// Compute the totals for this bit pattern
					for (lnK = 0, lnBitTest = lnJ, lfTot = 0.0f; lnK < _FREQ_COUNT; lnK++, lnBitTest >>= 1)
					{
						llFlag	= (lnBitTest & 0x1);
						lfTot	+= sin(lfRadian * f[lnJ]) * ((llFlag) ? 1.0f : 0.0f);		// 1.0f if the bit is 1, 0.0f if the bit is 0
					}

					// Store the candidate
					candidates[lnJ] = (short)(lfTot / _FREQ_COUNT);
				}
			}

			// Determine what this bit is
			for (lnJ = 0; lnJ < (1 << _FREQ_COUNT); lnJ++)
			{
				// If we're within +/- 5 of our target, count it
				if (abs(buffer[lnI] - candidates[lnJ]) < 5)
					++counts[lnJ];
			}
		}


	// Done
	return 0;
}
