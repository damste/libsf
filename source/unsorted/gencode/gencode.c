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

#define _FALSE						0
#define _TRUE						1

#define _PARAM_TYPE_NONE			-1
#define _PARAM_TYPE_MIN				0
#define _PARAM_TYPE_VOIDPTR			0
// Other types can be defined here as 0 types also for system documentation, such as "#define _PARAM_TYPE_INT 0", etc.
#define _PARAM_TYPE_FLOAT			1
#define _PARAM_TYPE_DOUBLE			2
#define _PARAM_TYPE_MAX				2

struct SIterator
{
	int		nMaxParamType;				// Max parameter type
	int		nVarParams;					// Number of parameters that are variable (up to 6 max)

	int		isValid;
	int		varParam1;					// Parameter 1 type (see _PARAM_TYPE_* constants)
	int		varParam2;					// Parameter 2 type (see _PARAM_TYPE_* constants)
	int		varParam3;					// Parameter 3 type (see _PARAM_TYPE_* constants)
	int		varParam4;					// Parameter 4 type (see _PARAM_TYPE_* constants)
	int		varParam5;					// Parameter 5 type (see _PARAM_TYPE_* constants)
	int		varParam6;					// Parameter 6 type (see _PARAM_TYPE_* constants)
};

void		generate					(int tnMaxParamType, int tnVarParams, int tnMaxParams, char* tcOutputFile);
void		generate_pattern			(int tnMaxParams, FILE* fh_c, FILE* fh_h1, FILE* fh_h2);
int			generate_pattern_type		(char* buffer, int tnType, int tnParam);
void		initializeIter				(int tnParamCount, int tnVarParams);
int			isIterValid					(void);
void		incrementIter				(void);
int			incrementIterPart			(int* iptr, int tnParam);
void		writeout					(void* data, size_t tnSize, FILE* fh);


// .c header
const char	cgc_c_header_p1[]			= "// Generated source file for calling dlls using a variable parameter pattern\n"
										  "\n";
const char	cgc_c_header_p2[]			= "#include \"";
const char	cgc_c_header_p3[]			= "\"\n";
const char	cgc_c_header_p4[]			= "\n"
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
										  "    struct SDllDispatch _dll; // The address of the function in the dll"
										  "    struct SParam rp; // Return parameter\n"
										  "\n"
										  "    int ipCount;\n"
										  "    struct SParam ip[";
const char	cgc_c_header_p5[]			= "]; // Input parameter(s)\n"
										  "}\n"
										  "\n";



// _1.h header
const char	cgc_h1_header[]				= "// Generated source file for calling dlls using a variable parameter pattern\n"
										  "\n";

// _2.h header
const char	cgc_h2_header[]				= "// Generated source file for calling dlls using a variable parameter pattern\n"
										  "\n";

// File extensions
const char cgc_c_ext[]					= ".c";
const char cgc_h1_ext[]					= "_1.h";
const char cgc_h2_ext[]					= "_2.h";

// Variable parameter type names for functions
const char	cgc_fname_void_pointer[]	= "voidptr";
const char	cgc_fname_float[]			= "float";
const char	cgc_fname_double[]			= "double";
#define _MAX_TYPE_LENGTH				sizeof(cgc_fname_void_pointer) - 1

struct SIterator gsIter;

int main(int argc, char* argv[])
{
	// The values for 4 and 16 can be received as input parameters
	generate(_PARAM_TYPE_MAX, 4, 16, "dllfuncs");

	return 0;
}

void generate(int tnMaxParamType, int tnVarParams, int tnMaxParams, char* tcOutputFile)
{
	FILE*	fh_c;
	FILE*	fh_h1;
	FILE*	fh_h2;
	char	file_c[_MAX_PATH];
	char	file_h1[_MAX_PATH];
	char	file_h2[_MAX_PATH];
	char	buffer[12];


	//////////
	// Create required output files
	//////
		memset(file_c,	0, sizeof(file_c));
		memset(file_h1,	0, sizeof(file_h1));
		memset(file_h2,	0, sizeof(file_h2));

		memcpy(file_c,	tcOutputFile, min(strlen(tcOutputFile), sizeof(file_c) - sizeof(cgc_c_ext) - 1));
		memcpy(file_h1,	tcOutputFile, min(strlen(tcOutputFile), sizeof(file_h1) - sizeof(cgc_h1_ext) - 1));
		memcpy(file_h2,	tcOutputFile, min(strlen(tcOutputFile), sizeof(file_h2) - sizeof(cgc_h2_ext) - 1));

		sprintf(file_c	+ strlen(file_c),	cgc_c_ext);
		sprintf(file_h1	+ strlen(file_h1),	cgc_h1_ext);
		sprintf(file_h2	+ strlen(file_h2),	cgc_h2_ext);


	//////////
	// Open the output files
	//////
		fh_c = fopen(file_c, "wb+");
		if (!fh_c)
		{
			printf("Unable to create %s\n", file_c);
			exit(-1);
		}

		fh_h1 = fopen(file_h1, "wb+");
		if (!fh_h1)
		{
			printf("Unable to create %s\n", file_h1);
			exit(-1);
		}

		fh_h2 = fopen(file_h2, "wb+");
		if (!fh_h2)
		{
			printf("Unable to create %s\n", file_h2);
			exit(-1);
		}


	//////////
	// Write the headers
	//////
		writeout((void*)cgc_c_header_p1, sizeof(cgc_c_header_p1) - 1, fh_c);
		sprintf(buffer, "%u", tnMaxParams);
		writeout((void*)buffer, strlen(buffer), fh_c);
		writeout((void*)cgc_c_header_p2, sizeof(cgc_c_header_p2) - 1, fh_c);


	//////////
	// Iterate through every possible variable parameter combination
	//////
		for (initializeIter(tnMaxParamType, tnVarParams);	isIterValid();	incrementIter())
			generate_pattern(tnMaxParams, fh_c, fh_h1, fh_h2);


	//////////
	// All done!
	//////
		fclose(fh_c);

}

void generate_pattern(int tnMaxParams, FILE* fh_c, FILE* fh_h1, FILE* fh_h2)
{
	char buffer[(6 * _MAX_TYPE_LENGTH) + 1];


	//////////
	// Build the function name pattern
	//////
		memset(buffer, 0, sizeof(buffer));
		if (generate_pattern_type(buffer,					gsIter.varParam1, 1) &&
			generate_pattern_type(buffer + strlen(buffer),	gsIter.varParam2, 2) &&
			generate_pattern_type(buffer + strlen(buffer),	gsIter.varParam3, 3) &&
			generate_pattern_type(buffer + strlen(buffer),	gsIter.varParam4, 4) &&
			generate_pattern_type(buffer + strlen(buffer),	gsIter.varParam5, 5) &&
			generate_pattern_type(buffer + strlen(buffer),	gsIter.varParam6, 6))
		{
			// This if block is used as a place holder to allow as many calculations as are required above
		}


	//////////
	// General format of what's being built:
	//
	// In the .c file:
	//		void dispatch_voidptr_voidptr_voidptr_voidptr(struct SParamData* pd)
	//		{
	//			switch (pd->ipCount)
	//			{
	//				case 0:	// No parameters
	//					switch (pd->rp->type) {
	//						default:                       pd->_dll->_dispatch_voidptr_voidptr_voidptr_voidptr_00();
	//						case _VAR_TYPE_V: pd->rp->_v = pd->_dll->_dispatch_voidptr_voidptr_voidptr_voidptr_0v();
	//						case _VAR_TYPE_F: pd->rp->_f = pd->_dll->_dispatch_voidptr_voidptr_voidptr_voidptr_0f();
	//						case _VAR_TYPE_D: pd->rp->_d = pd->_dll->_dispatch_voidptr_voidptr_voidptr_voidptr_0d();
	//					}
	//					break;
	//
	//				case 1:	// One parameter
	//					switch (pd->rp->type) {
	//						default:                       pd->_dll->_dispatch_voidptr_voidptr_voidptr_voidptr_10(pd->ip[0]._v);
	//						case _VAR_TYPE_V: pd->rp->_v = pd->_dll->_dispatch_voidptr_voidptr_voidptr_voidptr_1v(pd->ip[0]._v);
	//						case _VAR_TYPE_F: pd->rp->_f = pd->_dll->_dispatch_voidptr_voidptr_voidptr_voidptr_1f(pd->ip[0]._v);
	//						case _VAR_TYPE_D: pd->rp->_d = pd->_dll->_dispatch_voidptr_voidptr_voidptr_voidptr_1d(pd->ip[0]._v);
	//					}
	//					break;
	//
	//				case 2: // Two parameters
	//					switch (pd->rp->type) {
	//						default:                       pd->_dll->_dispatch_voidptr_voidptr_voidptr_voidptr_20(pd->ip[0]._v, pd->ip[1]._v);
	//						case _VAR_TYPE_V: pd->rp->_v = pd->_dll->_dispatch_voidptr_voidptr_voidptr_voidptr_2v(pd->ip[0]._v, pd->ip[1]._v);
	//						case _VAR_TYPE_F: pd->rp->_f = pd->_dll->_dispatch_voidptr_voidptr_voidptr_voidptr_2f(pd->ip[0]._v, pd->ip[1]._v);
	//						case _VAR_TYPE_D: pd->rp->_d = pd->_dll->_dispatch_voidptr_voidptr_voidptr_voidptr_2d(pd->ip[0]._v, pd->ip[1]._v);
	//					}
	//					break;
	//
	//				... and so on
	//
	//			}
	//		}
	//
	// In the _1.h file:
	//		struct SDllDispatch {
	//			union {
	//				void*	dispatch_function;
	//
	//				void    _dispatch_voidptr_voidptr_voidptr_voidptr_00    (void);
	//				void*   _dispatch_voidptr_voidptr_voidptr_voidptr_0v    (void);
	//				float   _dispatch_voidptr_voidptr_voidptr_voidptr_0f    (void);
	//				double  _dispatch_voidptr_voidptr_voidptr_voidptr_0d    (void);
	//
	//				void    _dispatch_voidptr_voidptr_voidptr_voidptr_10    (void*);
	//				void*   _dispatch_voidptr_voidptr_voidptr_voidptr_1v    (void*);
	//				float   _dispatch_voidptr_voidptr_voidptr_voidptr_1f    (void*);
	//				double  _dispatch_voidptr_voidptr_voidptr_voidptr_1d    (void*);
	//
	//				void    _dispatch_voidptr_voidptr_voidptr_voidptr_20    (void*, void*);
	//				void*   _dispatch_voidptr_voidptr_voidptr_voidptr_2v    (void*, void*);
	//				float   _dispatch_voidptr_voidptr_voidptr_voidptr_2f    (void*, void*);
	//				double  _dispatch_voidptr_voidptr_voidptr_voidptr_2d    (void*, void*);
	//			};
	//		};
	//
	// In the _2.h file:
	//		void dispatch_voidptr_voidptr_voidptr_voidptr(struct SParamData* pd);
	//
	//////

// Working here...
}

int generate_pattern_type(char* buffer, int tnType, int tnParam)
{
	if (tnParam <= gsIter.nMaxParamType)
	{
		switch (tnType)
		{
			case _PARAM_TYPE_VOIDPTR:
				sprintf(buffer, cgc_fname_void_pointer);
				break;

			case _PARAM_TYPE_FLOAT:
				sprintf(buffer, cgc_fname_float);
				break;

			case _PARAM_TYPE_DOUBLE:
				sprintf(buffer, cgc_fname_double);
				break;

			default:
				// Should never happen
				printf("There's an error in the program, dear Lila, dear Lila. An error in the program, dear Lila, err-or.\n");
				exit(-99);
		}

		// Continuing processing if there's more to process
		return((tnParam < gsIter.nMaxParamType) ? _TRUE : _FALSE);

	} else {
		// We're done processing
		return(_FALSE);
	}
}

void initializeIter(int tnParamCount, int tnVarParams)
{
	gsIter.nMaxParamType	= tnParamCount;
	gsIter.nVarParams	= tnVarParams;

	gsIter.isValid	= _TRUE;
	gsIter.varParam1		= _PARAM_TYPE_MIN;
	gsIter.varParam2		= _PARAM_TYPE_MIN;
	gsIter.varParam3		= _PARAM_TYPE_MIN;
	gsIter.varParam4		= _PARAM_TYPE_MIN;
	gsIter.varParam5		= _PARAM_TYPE_MIN;
	gsIter.varParam6		= _PARAM_TYPE_MIN;
}

int isIterValid(void)
{
	return(gsIter.isValid);
}

void incrementIter(void)
{
	if (!incrementIterPart(&gsIter.varParam1, 1) &&
		!incrementIterPart(&gsIter.varParam2, 2) &&
		!incrementIterPart(&gsIter.varParam3, 3) &&
		!incrementIterPart(&gsIter.varParam4, 4) &&
		!incrementIterPart(&gsIter.varParam5, 5) &&
		!incrementIterPart(&gsIter.varParam6, 6))
	{
		// This if block is used as a placeholder to allow as many as are valid to pass through incrementing
	}
}

int incrementIterPart(int* iptr, int tnParam)
{
	//////////
	// Are we beyond our count of valid params?
	//////
		if (tnParam > gsIter.nMaxParamType)
			return(_FALSE);	// Yes


	//////////
	// Can we increment?
	//////
		if (*iptr < _PARAM_TYPE_MAX)
		{
			// Yes
			++*iptr;

		} else {
			// No, so wrap it around
			*iptr = _PARAM_TYPE_MIN;

			// Success is now based on whether or not this was the last param or not
			if (tnParam == gsIter.nMaxParamType)
				gsIter.isValid = _FALSE;
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
