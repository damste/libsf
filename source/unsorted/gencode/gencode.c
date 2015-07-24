//////////
//
// /libsf/source/unsorted/gencode/gencode.c
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
// Version 0.01
// Copyright (c) 2015 by Rick C. Hodgin
//////
// Last update:
//     Jul.23.2015
//////
// Change log:
//     Jul.23.2015 - Initial creation
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


// Generates C source code based on various parameters
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#define _PARAM_TYPE_VOIDPTR		0
#define _PARAM_TYPE_FLOAT		1
#define _PARAM_TYPE_DOUBLE		2
#define _PARAM_TYPE_MAX			2

struct SIterator
{
	int		nParamCount;
	int		nVarParams;

	int		isValid;
	int		p1;				// Parameter 1 type (see _PARAM_TYPE_* constants)
	int		p2;				// Parameter 2 type (see _PARAM_TYPE_* constants)
	int		p3;				// Parameter 3 type (see _PARAM_TYPE_* constants)
	int		p4;				// Parameter 4 type (see _PARAM_TYPE_* constants)
	int		p5;				// Parameter 5 type (see _PARAM_TYPE_* constants)
	int		p6;				// Parameter 6 type (see _PARAM_TYPE_* constants)
};

void		generate				(int tnParamCount, int tnVarParams, int tnMaxParams, char* tcOutputFile);
void		generate_pattern		(int tnMaxParams, FILE* fh);
void		generate_pattern_type	(char* buffer, int tnType, int tnParam);
void		initializeIter			(int tnParamCount, int tnVarParams);
int			isIterValid				(void);
void		incrementIter			(void);
int			incrementIterPart		(int* iptr, int tnParam);
void		writeout				(void* data, size_t tnSize, FILE* fh);

const char	cgc_header_p1[]			= "// Generated source file for calling dlls using a variable parameter pattern\n"
									  "\n"
									  "struct SParam\n"
									  "{\n"
									  "    int type;\n"
									  "    union data {\n"
									  "        void*  _v;\n"
									  "        float  _f;\n"
									  "        double _d;\n"
									  "    };"
									  "};\n"
									  "\n"
									  "struct SParamData\n"
									  "{\n"
									  "    struct SParam rp; // Return parameters\n"
									  "\n"
									  "    int ipCount;\n"
									  "    struct SParam ip[";
const char	cgc_header_p2[]			= "]; // Input parameters\n"
									  "}\n"
									  "\n";

const char	cgc_void_pointer[]		= "voidptr";
const char	cgc_float[]				= "float";
const char	cgc_double[]			= "double";

struct SIterator gsIter;

int main(int argc, char* argv[])
{
	// The values for 4 and 16 can be received as input parameters
	generate(_PARAM_TYPE_MAX, 4, 16, "dllfuncs.c");

	return 0;
}

void generate(int tnParamCount, int tnVarParams, int tnMaxParams, char* tcOutputFile)
{
	FILE*	fh;
	char	buffer[12];


	//////////
	// Open the output file
	//////
		fh = fopen(tcOutputFile, "wb+");
		if (!fh)
		{
			printf("Unable to create %s\n", tcOutputFile);
			exit(-1);
		}


	//////////
	// Write the header
	//////
		writeout((void*)cgc_header_p1, sizeof(cgc_header_p1) - 1, fh);
		sprintf(buffer, "%u", tnMaxParams);
		writeout((void*)buffer, strlen(buffer), fh);
		writeout((void*)cgc_header_p2, sizeof(cgc_header_p2) - 1, fh);


	//////////
	// Iterate through every possible variable parameter combination
	//////
		for (initializeIter(tnParamCount, tnVarParams); isIterValid(); incrementIter())
			generate_pattern(tnMaxParams, fh);


	//////////
	// All done!
	//////
		fclose(fh);

}

void generate_pattern(int tnMaxParams, FILE* fh)
{
	char buffer[64];


	//////////
	// Build the function name pattern
	//////
		memset(buffer, 0, sizeof(buffer));

		generate_pattern_type(buffer,					gsIter.p1, 1);
		generate_pattern_type(buffer + strlen(buffer),	gsIter.p2, 2);
		generate_pattern_type(buffer + strlen(buffer),	gsIter.p3, 3);
		generate_pattern_type(buffer + strlen(buffer),	gsIter.p4, 4);
		generate_pattern_type(buffer + strlen(buffer),	gsIter.p5, 5);
		generate_pattern_type(buffer + strlen(buffer),	gsIter.p6, 6);


	//////////
	// General format of what's being built:
	//
	//		void func_voidptr_voidptr_voidptr_voidptr(struct SParamData* pd)
	//		{
	//			switch (pd->ipCount)
	//			{
	//				case 0:
	//					switch (pd->rp->type) {
	//						case _VAR_TYPE_V: pd->rp->_v = _func_voidptr_voidptr_voidptr_voidptr();
	//						case _VAR_TYPE_F: pd->rp->_f = _func_voidptr_voidptr_voidptr_voidptr();
	//						case _VAR_TYPE_D: pd->rp->_d = _func_voidptr_voidptr_voidptr_voidptr();
	//						default: _func_voidptr_voidptr_voidptr_voidptr();
	//					}
	//					break;
	//				case 1:
	//					switch (pd->rp->type) {
	//						case _VAR_TYPE_V: pd->rp->_v = _func_voidptr_voidptr_voidptr_voidptr(pd->ip[0]._v);
	//						case _VAR_TYPE_F: pd->rp->_f = _func_voidptr_voidptr_voidptr_voidptr(pd->ip[0]._v);
	//						case _VAR_TYPE_D: pd->rp->_d = _func_voidptr_voidptr_voidptr_voidptr(pd->ip[0]._v);
	//						default: _func_voidptr_voidptr_voidptr_voidptr(pd->ip[0]._v);
	//					}
	//					break;
	//				case 2:
	//					switch (pd->rp->type) {
	//						case _VAR_TYPE_V: pd->rp->_v = _func_voidptr_voidptr_voidptr_voidptr(pd->ip[0]._v, pd->ip[1]._v);
	//						case _VAR_TYPE_F: pd->rp->_f = _func_voidptr_voidptr_voidptr_voidptr(pd->ip[0]._v, pd->ip[1]._v);
	//						case _VAR_TYPE_D: pd->rp->_d = _func_voidptr_voidptr_voidptr_voidptr(pd->ip[0]._v, pd->ip[1]._v);
	//						default: _func_voidptr_voidptr_voidptr_voidptr(pd->ip[0]._v, pd->ip[1]._v);
	//					}
	//					break;
	//
	//				... and so on
	//
	//			}
	//		}
	//////

// Working here...
}

void generate_pattern_type(char* buffer, int tnType, int tnParam)
{
	if (tnParam <= gsIter.nParamCount)
	{
		switch (tnType)
		{
			case _PARAM_TYPE_VOIDPTR:
				sprintf(buffer, cgc_void_pointer);
				break;

			case _PARAM_TYPE_FLOAT:
				sprintf(buffer, cgc_float);
				break;

			case _PARAM_TYPE_DOUBLE:
				sprintf(buffer, cgc_double);
				break;

			default:
				// Should never happen
				printf("There's an error in the program, dear Lila, dear Lila. An error in the program, dear Lila, err-or.\n");
				exit(-99);
		}
	}
}

void initializeIter(int tnParamCount, int tnVarParams)
{
	gsIter.nParamCount	= tnParamCount;
	gsIter.nVarParams	= tnVarParams;

	gsIter.isValid	= 1;
	gsIter.p1		= 0;
	gsIter.p2		= 0;
	gsIter.p3		= 0;
	gsIter.p4		= 0;
	gsIter.p5		= 0;
	gsIter.p6		= 0;
}

int isIterValid(void)
{
	return(gsIter.isValid);
}

void incrementIter(void)
{
	if (	!incrementIterPart(&gsIter.p1, 1)
		&&	!incrementIterPart(&gsIter.p2, 2)
		&&	!incrementIterPart(&gsIter.p3, 3)
		&&	!incrementIterPart(&gsIter.p4, 4)
		&&	!incrementIterPart(&gsIter.p5, 5)
		&&	!incrementIterPart(&gsIter.p6, 6))
	{
		// This if block is used as a placeholder to allow as many as are valid to pass through inrementing
	}
}

int incrementIterPart(int* iptr, int tnParam)
{
	//////////
	// Are we beyond our count of valid params?
	//////
		if (tnParam > gsIter.nParamCount)
			return(0);	// Yes


	//////////
	// Can we increment?
	//////
		if (*iptr < _PARAM_TYPE_MAX)
		{
			// Yes
			++*iptr;

		} else {
			// No, so wrap it around
			*iptr = 0;

			// Success is now based on whether or not this was the last param or not
			if (tnParam == gsIter.nParamCount)
				gsIter.isValid = 0;
		}


	//////////
	// Indicate our status
	//////
		return(gsIter.isValid);
}

void writeout(void* data, size_t tnSize, FILE* fh)
{
	size_t num;


	//////////
	// Write out the data
	//////
		num = fwrite(data, 1, tnSize, fh);


	//////////
	// If there's an error, we're done
	//////
		if (num != tnSize)
		{
			printf("Error writing %d bytes to output.\n", (int)tnSize);
			exit(-2);
		}
}
