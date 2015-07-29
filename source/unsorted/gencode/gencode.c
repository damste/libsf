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

// Forward declarations for gencode algorithms.
void		generate							(int tnMaxParamType, int tnVarParams, int tnMaxParams, char* tcOutputFile);
void		generate_pattern					(unsigned int tnThisParam, int tnMaxParams, FILE* fh_c, FILE* fh_h1, FILE* fh_h2, FILE* fh_h3);
int			generate_pattern_type				(char* buffer, int tnType, int tnParam);
void		initializeIter						(int tnParamCount, int tnVarParams);
int			isIterValid							(void);
void		incrementIter						(void);
int			incrementIterPart					(int* iptr, int tnParam);
void		writeout_file_c						(int tnMaxParams, char* tcFunctionName, FILE* tfh);
void		writeout_file_1						(int tnMaxParams, char* tcFunctionName, FILE* tfh);
void		writeout_file_1_part				(int tnThisParam, char* tcFunctionName, char* tcPostfix, char* tcReturnType, int tnReturnTypeLength, FILE* tfh);
void		writeout_param_values				(int tnMaxLineParams, FILE* tfh);
int			writeout_param_values_this_type		(int tnThisParam, int tnMaxParams, int* iptr, int tlIncludePostfixComma, FILE* tfh);
void		writeout_param_types				(int tnMaxLineParams, FILE* tfh);
int			writeout_param_this_type			(int tnThisParam, int tnMaxParams, int* iptr, int tlIncludePostfixComma, FILE* tfh);
FILE*		createfile							(char* tcFileName);
void		writeout							(void* data, size_t tnSize, FILE* fh);



// .c header
const char	cgc_c_header_p0_1[]			= "// ";
const char	cgc_c_header_p0_2[]			= "\n";
const char	cgc_c_header_p1[]			= "// Generated source file for calling dlls using a variable parameter pattern\n"
										  "\n";
const char	cgc_c_header_p2_1[]			= "#include \"";
const char	cgc_c_header_p2_2[]			= "\"\n";
const char	cgc_c_header_p3[]			= "\n"
										  "#define _VAR_TYPE_V 0\n"
										  "#define _VAR_TYPE_F 1\n"
										  "#define _VAR_TYPE_D 2\n"
										  "\n"
										  "#define _VAR_TYPE_CHAR  0\n"
										  "#define _VAR_TYPE_SHORT 0\n"
										  "#define _VAR_TYPE_INT   0\n"
										  "#define _VAR_TYPE_LONG  0\n"
										  "\n"
										  "#define _VAR_TYPE_UNSIGNED_CHAR  0\n"
										  "#define _VAR_TYPE_UNSIGNED_SHORT 0\n"
										  "#define _VAR_TYPE_UNSIGNED_INT   0\n"
										  "#define _VAR_TYPE_UNSIGNED_LONG  0\n"
										  "\n"
										  "#define _VAR_TYPE_FLOAT  1\n"
										  "#define _VAR_TYPE_DOUBLE 2\n"
										  "\n"
										  "#define _MAX_VAR_PARAMS ";
const char	cgc_c_header_p4[]			= "\n"
										  "\n"
										  "#if defined(_WIN32) || defined(_WIN64)\n"
										  "    // #include <windows.h>\n"
										  "    int load_dll_function(struct SParamData* sd, char* dllPathname, char* functionName)\n"
										  "    {\n"
										  "        HMODULE hmod;	// If not found, un-comment #include <windows.h> above\n"
										  "\n"
										  "\n"
										  "        //////////\n"
										  "        // Open the dll\n"
										  "        //////\n"
										  "            hmod = LoadLibraryA(dllPathname);	// If not found, un-comment #include <windows.h> above\n"
										  "            if (!hmod)\n"
										  "                return(-1);	// Failure accessing dll\n"
										  "\n"
										  "\n"
										  "        //////////\n"
										  "        // Grab the function address\n"
										  "        //////\n"
										  "            // If not found, un-comment #include <windows.h> above\n"
										  "            sd->_dll.dispatch_function_address = (void*)GetProcAddress(hmod, functionName);\n"
										  "\n"
										  "\n"
										  "        //////////\n"
										  "        // Indicate success or failure\n"
										  "        //////\n"
										  "            return((sd->_dll.dispatch_function_address != 0) ? 1 : -2/*could not find function address*/);\n"
										  "\n"
										  "    }\n"
										  "#endif\n"
										  "\n"
										  "// This is the primary/top-level function to use for dispatching into a dll function\n"
										  "void dispatch_dll_function(struct SParamData* pd)\n"
										  "{\n"
										  "    int lnIndex;\n"
										  "\n"
										  "\n"
										  "    //////////\n"
										  "    // Compute index\n"
										  "    //////\n"
										  "        lnIndex =    /*pow(_MAX_VAR_PARAMS,0)*/  (pd->ip[0].type * 1)\n"
										  "#if _MAX_VAR_PARAMS >= 2\n"
										  "                 +   /*pow(_MAX_VAR_PARAMS,1)*/  (pd->ip[1].type * (_MAX_VAR_PARAMS))\n"
										  "#endif\n"
										  "#if _MAX_VAR_PARAMS >= 3\n"
										  "                 +   /*pow(_MAX_VAR_PARAMS,2)*/  (pd->ip[2].type * (_MAX_VAR_PARAMS * _MAX_VAR_PARAMS))\n"
										  "#endif\n"
										  "#if _MAX_VAR_PARAMS >= 4\n"
										  "                 +   /*pow(_MAX_VAR_PARAMS,3)*/  (pd->ip[3].type * (_MAX_VAR_PARAMS * _MAX_VAR_PARAMS * _MAX_VAR_PARAMS))\n"
										  "#endif\n"
										  "#if _MAX_VAR_PARAMS >= 5\n"
										  "                 +   /*pow(_MAX_VAR_PARAMS,4)*/  (pd->ip[4].type * (_MAX_VAR_PARAMS * _MAX_VAR_PARAMS * _MAX_VAR_PARAMS * _MAX_VAR_PARAMS))\n"
										  "#endif\n"
										  "#if _MAX_VAR_PARAMS >= 6\n"
										  "                 +   /*pow(_MAX_VAR_PARAMS,5)*/  (pd->ip[5].type * (_MAX_VAR_PARAMS * _MAX_VAR_PARAMS * _MAX_VAR_PARAMS * _MAX_VAR_PARAMS * _MAX_VAR_PARAMS))\n"
										  "#endif\n"
										  ";\n"
										  "\n"
										  "    //////////\n"
										  "    // Dispatch to the general handler by variable parameter type, which will\n"
										  "    // then dispatch to the appropriate sub-handler based on parameter count\n"
										  "    //////\n"
										  "        dll_dispatch[lnIndex].dispatch0(pd);    // Calls directly into the functions below\n"
										  "\n"
										  "}\n"
										  "\n"
										  "// The following functions are master functions called by the variable parameter\n"
										  "// portion they represent.  Within those functions are handlers for the parameter\n"
										  "// count, so that the appropriate function is dispatched.\n"
										  "\n";
const char	cgc_c_function_prefix1[]		= "void dispatch_";
const char	cgc_c_function_prefix2[]	= "(struct SParamData* pd)\n"
										  "{\n"
										  "    switch (pd->ipCount)\n"
										  "    {\n";
const char	cgc_c_case_1[]				= "        case ";
const char	cgc_c_case_2[]				= ":  // ";
const char	cgc_c_case_3_singular[]		= " parameter\n";
const char	cgc_c_case_3_plural[]		= " parameters\n";
const char	cgc_c_switch_prefix[]		= "            switch (pd->rp.type) {\n"
										  "                default:                      pd->_dll.dispatch_";
const char	cgc_c_switch_1_prefix[]		= "(";
const char	cgc_c_switch_1_postfix[]	= ");\n"
										  "                case _VAR_TYPE_V: pd->rp._v = pd->_dll.dispatch_";
const char	cgc_c_switch_2_prefix[]		= "(";
const char	cgc_c_switch_2_postfix[]	= ");\n"
										  "                case _VAR_TYPE_F: pd->rp._f = pd->_dll.dispatch_";
const char	cgc_c_switch_3_prefix[]		= "(";
const char	cgc_c_switch_3_postfix[]	= ");\n"
										  "                case _VAR_TYPE_D: pd->rp._d = pd->_dll.dispatch_";
const char	cgc_c_switch_4_prefix[]		= "(";
const char	cgc_c_switch_4_postfix[]	= ");\n"
										  "            }\n"
										  "            break;\n";
const char	cgc_c_footer[]				= "\n"
										  "    }\n"
										  "}\n"
										  "\n";
const char	cgc_c_param_prefix_1[]		= "pd->ip[";
const char	cgc_c_param_prefix_2[]		= "].";
const char	cgc_c_param_void_pointer[]	= "_v";
const char	cgc_c_param_float[]			= "_f";
const char	cgc_c_param_double[]		= "_d";
const char	cgc_c_param_comma[]			= ", ";



// .h header
const char	cgc_h_header_p0_1[]			= "// ";
const char	cgc_h_header_p0_2[]			= "\n";
const char	cgc_h_header_p1[]			= "// Generated source file for calling dlls using a variable parameter pattern\n"
										  "\n"
										  "struct SParam\n"
										  "{\n"
										  "    int type;\n"
										  "    union {\n"
										  "        // Used internally\n"
										  "        void*  _v;\n"
										  "        float  _f;\n"
										  "        double _d;\n"
										  "\n"
										  "        // For more documentary population into explicit types\n"
										  "        char            _char;\n"
										  "        short           _short;\n"
										  "        int             _int;\n"
										  "        long            _long;\n"
										  "\n"
										  "        unsigned char   _uchar;\n"
										  "        unsigned short  _ushort;\n"
										  "        unsigned int    _uint;\n"
										  "        unsigned long   _ulong;\n"
										  "\n"
										  "        float           _float;\n"
										  "        double          _double;\n"
										  "    };\n"
										  "};\n"
										  "\n"
										  "struct SParamData\n"
										  "{\n"
										  "    struct SDllDispatch   _dll;       // The address of the function in the dll\n"
										  "    int                   ipCount;    // Input parameter count (0 thru ";
const char	cgc_h_header_p2[]			= ")\n"
										  "    struct SParam         ip[";
const char	cgc_h_header_p3[]			= "];     // Input parameters\n"
										  "    struct SParam         rp;         // Return parameter\n"
										  "};\n"
										  "\n"
										  "\n"
										  "\n"
										  "\n"
										  "////////////////////////////\n"
										  "// Sample use and reference:\n"
										  "/////////\n"
										  "//\n"
										  "//     SParamData sd;\n"
										  "//\n"
										  "//     // Load dll function\n"
										  "//     if (load_dll_function(&sd, \"c:\\path\\to\\my.dll\", \"myFunction\") != 1/*true*/)\n"
										  "//     {\n"
										  "//         // Unable to load the dll or function in the dll\n"
										  "//         // Report error\n"
										  "//\n"
										  "//     } else {\n"
										  "//         // Populate sd's parameters appropriately\n"
										  "//         // This step is manual, and custom to your application on how it's done\n"
										  "//\n"
										  "//\n"
										  "//         //////////\n"
										  "//         // Actually call the DLL:\n"
										  "//         //////\n"
										  "//             dispatch_dll_function(&sd);\n"
										  "//\n"
										  "//             // Note:  Return value (if any) is in sd->rp._* values"
										  "//\n"
										  "//     }\n";



// _1.h header
const char	cgc_h1_header_p0_1[]		= "// ";
const char	cgc_h1_header_p0_2[]		= "\n";
const char	cgc_h1_header_p1[]			= "// Generated source file for calling dlls using a variable parameter pattern\n"
										  "\n"
										  "struct SDllDispatch {\n"
										  "    union {\n"
										  "        void*   dispatch_function_address;  // Populate using (void*)GetProcAddress(...) or equivalent\n"
										  "\n";
const char	cgc_h1_footer_p1[]			= "    };\n"
										  "};\n";
const char	cgc_h1_prefix_common[]		= "        ";
const char	cgc_h1_prefix_void[]		= "void   ";
const char	cgc_h1_prefix_void_pointer[]= "void*  ";
const char	cgc_h1_prefix_float[]		= "float  ";
const char	cgc_h1_prefix_double[]		= "double ";
const char	cgc_h1_prefix[]				= " (*dispatch_";
const char	cgc_h1_postfix_1[]			= ")   (";
const char	cgc_h1_param_void[]			= "void";
const char	cgc_h1_param_void_pointer[]	= "void*";
const char	cgc_h1_param_float[]		= "float";
const char	cgc_h1_param_double[]		= "double";
const char	cgc_h1_param_comma[]		= ", ";
const char	cgc_h1_postfix_2[]			= ");\n";
const char	cgc_h1_postfix_vspacer[]	= "\n";



// _2.h header
const char	cgc_h2_header_p0_1[]		= "// ";
const char	cgc_h2_header_p0_2[]		= "\n";
const char	cgc_h2_header_p1[]			= "// Generated source file for calling dlls using a variable parameter pattern\n"
										  "\n"
										  "// Parameter dispatch prototype forward declarations\n";
const char	cgc_h2_prefix[]				= "void dispatch_";
const char	cgc_h2_postfix[]			= "(struct SParamData* pd);\n";
const char	cgc_h2_postfix_vspacer[]	= "\n";



// _3.h header
const char	cgc_h3_header_p0_1[]		= "// ";
const char	cgc_h3_header_p0_2[]		= "\n";
const char	cgc_h3_header_p1[]			= "// Generated source file for calling dlls using a variable parameter pattern\n"
										  "\n"
										  "// Variable holding dispatch destinations\n"
										  "struct SDllDispatch0 {\n"
										  "    void (*dispatch0) (struct SParamData* pd);\n"
										  "};\n"
										  "\n"
										  "struct SDllDispatch0 dll_dispatch[] = {\n";
const char	cgc_h3_footer[]				= "};\n";

const char	cgc_h3_prefix[]				= "    &dispatch_";
const char	cgc_h3_postfix[]			= ",\n";
const char	cgc_h3_postfix_vspacer[]	= "\n";

// File extensions
const char cgc_c_ext[]					= ".c";
const char cgc_h_ext[]					= ".h";
const char cgc_h1_ext[]					= "_1.h";
const char cgc_h2_ext[]					= "_2.h";
const char cgc_h3_ext[]					= "_3.h";

// Variable parameter type names for functions
const char	cgc_fname_void_pointer[]	= "voidptr_";
const char	cgc_fname_float[]			= "float___";
const char	cgc_fname_double[]			= "double__";
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
	unsigned int	lnI;
	FILE*			lfh_c;
	FILE*			lfh_h;
	FILE*			lfh_h1;
	FILE*			lfh_h2;
	FILE*			lfh_h3;
	char			file_c[_MAX_PATH];
	char			file_h[_MAX_PATH];
	char			file_h1[_MAX_PATH];
	char			file_h2[_MAX_PATH];
	char			file_h3[_MAX_PATH];
	char			buffer[12];


	//////////
	// Create required output files
	//////
		memset(file_c,	0, sizeof(file_c));
		memset(file_h,	0, sizeof(file_h));
		memset(file_h1,	0, sizeof(file_h1));
		memset(file_h2,	0, sizeof(file_h2));
		memset(file_h3,	0, sizeof(file_h3));

		memcpy(file_c,	tcOutputFile, min(strlen(tcOutputFile), sizeof(file_c)  - sizeof(cgc_c_ext)  - 1));
		memcpy(file_h,	tcOutputFile, min(strlen(tcOutputFile), sizeof(file_h)  - sizeof(cgc_h_ext)  - 1));
		memcpy(file_h1,	tcOutputFile, min(strlen(tcOutputFile), sizeof(file_h1) - sizeof(cgc_h1_ext) - 1));
		memcpy(file_h2,	tcOutputFile, min(strlen(tcOutputFile), sizeof(file_h2) - sizeof(cgc_h2_ext) - 1));
		memcpy(file_h3,	tcOutputFile, min(strlen(tcOutputFile), sizeof(file_h3) - sizeof(cgc_h3_ext) - 1));

		sprintf(file_c	+ strlen(file_c),	cgc_c_ext);
		sprintf(file_h	+ strlen(file_h),	cgc_h_ext);
		sprintf(file_h1	+ strlen(file_h1),	cgc_h1_ext);
		sprintf(file_h2	+ strlen(file_h2),	cgc_h2_ext);
		sprintf(file_h3	+ strlen(file_h3),	cgc_h3_ext);


	//////////
	// Open the output files
	//////
		lfh_c	= createfile(file_c);		// file.c
		lfh_h	= createfile(file_h);		// file.h
		lfh_h1	= createfile(file_h1);		// file_1.h
		lfh_h2	= createfile(file_h2);		// file_2.h
		lfh_h3	= createfile(file_h3);		// file_3.h


	//////////
	// Write the headers
	//////
		// file.c
		writeout((void*)cgc_c_header_p0_1, sizeof(cgc_c_header_p0_1) - 1, lfh_c);
		writeout((void*)file_c, strlen(file_c), lfh_c);
		writeout((void*)cgc_c_header_p0_2, sizeof(cgc_c_header_p0_2) - 1, lfh_c);
		writeout((void*)cgc_c_header_p1, sizeof(cgc_c_header_p1) - 1, lfh_c);

		writeout((void*)cgc_c_header_p2_1, sizeof(cgc_c_header_p2_1) - 1, lfh_c);
		writeout((void*)file_h1, strlen(file_h1), lfh_c);
		writeout((void*)cgc_c_header_p2_2, sizeof(cgc_c_header_p2_2) - 1, lfh_c);

		writeout((void*)cgc_c_header_p2_1, sizeof(cgc_c_header_p2_1) - 1, lfh_c);
		writeout((void*)file_h2, strlen(file_h2), lfh_c);
		writeout((void*)cgc_c_header_p2_2, sizeof(cgc_c_header_p2_2) - 1, lfh_c);

		writeout((void*)cgc_c_header_p2_1, sizeof(cgc_c_header_p2_1) - 1, lfh_c);
		writeout((void*)file_h3, strlen(file_h3), lfh_c);
		writeout((void*)cgc_c_header_p2_2, sizeof(cgc_c_header_p2_2) - 1, lfh_c);

		writeout((void*)cgc_c_header_p2_1, sizeof(cgc_c_header_p2_1) - 1, lfh_c);
		writeout((void*)file_h, strlen(file_h), lfh_c);
		writeout((void*)cgc_c_header_p2_2, sizeof(cgc_c_header_p2_2) - 1, lfh_c);

		writeout((void*)cgc_c_header_p3, sizeof(cgc_c_header_p3) - 1, lfh_c);
		sprintf(buffer, "%d", tnVarParams);
		writeout((void*)buffer, strlen(buffer), lfh_c);
		writeout((void*)cgc_c_header_p4, sizeof(cgc_c_header_p4) - 1, lfh_c);

		// file.h
		writeout((void*)cgc_h_header_p0_1, sizeof(cgc_h_header_p0_1) - 1, lfh_h);
		writeout((void*)file_h, strlen(file_c), lfh_h);
		writeout((void*)cgc_h_header_p0_2, sizeof(cgc_h_header_p0_2) - 1, lfh_h);
		writeout((void*)cgc_h_header_p1, sizeof(cgc_h_header_p1) - 1, lfh_h);
		sprintf(buffer, "%d", tnMaxParams);
		writeout((void*)buffer, strlen(buffer), lfh_h);
		writeout((void*)cgc_h_header_p2, sizeof(cgc_h_header_p2) - 1, lfh_h);
		writeout((void*)buffer, strlen(buffer), lfh_h);
		writeout((void*)cgc_h_header_p3, sizeof(cgc_h_header_p3) - 1, lfh_h);

		// file_1.h
		writeout((void*)cgc_h1_header_p0_1, sizeof(cgc_h1_header_p0_1) - 1, lfh_h1);
		writeout((void*)file_h1, strlen(file_h1), lfh_h1);
		writeout((void*)cgc_h1_header_p0_2, sizeof(cgc_h1_header_p0_2) - 1, lfh_h1);
		writeout((void*)cgc_h1_header_p1, sizeof(cgc_h1_header_p1) - 1, lfh_h1);

		// file_2.h
		writeout((void*)cgc_h2_header_p0_1, sizeof(cgc_h2_header_p0_1) - 1, lfh_h2);
		writeout((void*)file_h2, strlen(file_h2), lfh_h2);
		writeout((void*)cgc_h2_header_p0_2, sizeof(cgc_h2_header_p0_2) - 1, lfh_h2);
		writeout((void*)cgc_h2_header_p1, sizeof(cgc_h2_header_p1) - 1, lfh_h2);

		// file_3.h
		writeout((void*)cgc_h3_header_p0_1, sizeof(cgc_h3_header_p0_1) - 1, lfh_h3);
		writeout((void*)file_h3, strlen(file_h3), lfh_h3);
		writeout((void*)cgc_h3_header_p0_2, sizeof(cgc_h3_header_p0_2) - 1, lfh_h3);
		writeout((void*)cgc_h3_header_p1, sizeof(cgc_h3_header_p1) - 1, lfh_h3);


	//////////
	// Iterate through every possible variable parameter combination
	//////
		for (lnI = 1, initializeIter(tnMaxParamType, tnVarParams);	isIterValid();	lnI++, incrementIter())
			generate_pattern(lnI, tnMaxParams, lfh_c, lfh_h1, lfh_h2, lfh_h3);


	//////////
	// Write footers
	//////
		writeout((void*)cgc_h1_footer_p1,	sizeof(cgc_h1_footer_p1) - 1,	lfh_h1);
		writeout((void*)cgc_h3_footer,		sizeof(cgc_h3_footer) - 1,		lfh_h3);


	//////////
	// All done!
	//////
		fclose(lfh_c);
		fclose(lfh_h1);
		fclose(lfh_h2);
		fclose(lfh_h3);

}

void generate_pattern(unsigned int tnThisParam, int tnMaxParams, FILE* tfh_c, FILE* tfh_h1, FILE* tfh_h2, FILE* tfh_h3)
{
	char functionName[(6 * _MAX_TYPE_LENGTH) + 1];


	//////////
	// Build the function name pattern
	//////
		memset(functionName, 0, sizeof(functionName));
		if (generate_pattern_type(functionName,							gsIter.varParam1, 1) &&
			generate_pattern_type(functionName + strlen(functionName),	gsIter.varParam2, 2) &&
			generate_pattern_type(functionName + strlen(functionName),	gsIter.varParam3, 3) &&
			generate_pattern_type(functionName + strlen(functionName),	gsIter.varParam4, 4) &&
			generate_pattern_type(functionName + strlen(functionName),	gsIter.varParam5, 5) &&
			generate_pattern_type(functionName + strlen(functionName),	gsIter.varParam6, 6))
		{
			// This if block is used as a place holder to allow as many calculations as are required above
		}


	//////////
	// General format of what's being built:
	//
	// In the .c file:
	//		void dispatch_voidptr_voidptr_voidptr_voidptr(struct SParamData* pd)
	//		{
	//		    switch (pd->ipCount)
	//		    {
	//		        case 0:	// No parameters
	//		            switch (pd->rp->type) {
	//		                default:                      pd->_dll.dispatch_voidptr_voidptr_voidptr_voidptr_00();
	//		                case _VAR_TYPE_V: pd->rp._v = pd->_dll.dispatch_voidptr_voidptr_voidptr_voidptr_0v();
	//		                case _VAR_TYPE_F: pd->rp._f = pd->_dll.dispatch_voidptr_voidptr_voidptr_voidptr_0f();
	//		                case _VAR_TYPE_D: pd->rp._d = pd->_dll.dispatch_voidptr_voidptr_voidptr_voidptr_0d();
	//		            }
	//		            break;
	//
	//		        case 1:	// One parameter
	//		            switch (pd->rp->type) {
	//		                default:                      pd->_dll.dispatch_voidptr_voidptr_voidptr_voidptr_10(pd->ip[0]._v);
	//		                case _VAR_TYPE_V: pd->rp._v = pd->_dll.dispatch_voidptr_voidptr_voidptr_voidptr_1v(pd->ip[0]._v);
	//		                case _VAR_TYPE_F: pd->rp._f = pd->_dll.dispatch_voidptr_voidptr_voidptr_voidptr_1f(pd->ip[0]._v);
	//		                case _VAR_TYPE_D: pd->rp._d = pd->_dll.dispatch_voidptr_voidptr_voidptr_voidptr_1d(pd->ip[0]._v);
	//		            }
	//		            break;
	//
	//		        case 2: // Two parameters
	//		            switch (pd->rp->type) {
	//		                default:                      pd->_dll.dispatch_voidptr_voidptr_voidptr_voidptr_20(pd->ip[0]._v, pd->ip[1]._v);
	//		                case _VAR_TYPE_V: pd->rp._v = pd->_dll.dispatch_voidptr_voidptr_voidptr_voidptr_2v(pd->ip[0]._v, pd->ip[1]._v);
	//		                case _VAR_TYPE_F: pd->rp._f = pd->_dll.dispatch_voidptr_voidptr_voidptr_voidptr_2f(pd->ip[0]._v, pd->ip[1]._v);
	//		                case _VAR_TYPE_D: pd->rp._d = pd->_dll.dispatch_voidptr_voidptr_voidptr_voidptr_2d(pd->ip[0]._v, pd->ip[1]._v);
	//		            }
	//		            break;
	//
	//		        ... and so on
	//
	//		    }
	//		}
	//
	// In the _1.h file:
	//		struct SDllDispatch {
	//		    union {
	//		        void*	dispatch_function_address;
	//
	//		        void    (*_dispatch_voidptr_voidptr_voidptr_voidptr_00)   (void);
	//		        void*   (*_dispatch_voidptr_voidptr_voidptr_voidptr_0v)   (void);
	//		        float   (*_dispatch_voidptr_voidptr_voidptr_voidptr_0f)   (void);
	//		        double  (*_dispatch_voidptr_voidptr_voidptr_voidptr_0d)   (void);
	//
	//		        void    (*_dispatch_voidptr_voidptr_voidptr_voidptr_10)   (void*);
	//		        void*   (*_dispatch_voidptr_voidptr_voidptr_voidptr_1v)   (void*);
	//		        float   (*_dispatch_voidptr_voidptr_voidptr_voidptr_1f)   (void*);
	//		        double  (*_dispatch_voidptr_voidptr_voidptr_voidptr_1d)   (void*);
	//
	//		        void    (*_dispatch_voidptr_voidptr_voidptr_voidptr_20)   (void*, void*);
	//		        void*   (*_dispatch_voidptr_voidptr_voidptr_voidptr_2v)   (void*, void*);
	//		        float   (*_dispatch_voidptr_voidptr_voidptr_voidptr_2f)   (void*, void*);
	//		        double  (*_dispatch_voidptr_voidptr_voidptr_voidptr_2d)   (void*, void*);
	//		    };
	//		};
	//
	// In the _2.h file:
	//		// Parameter dispatch prototype forward declarations
	//		void dispatch_voidptr_voidptr_voidptr_voidptr(struct SParamData* pd);
	//
	// In the _3.h file:
	//		struct SDllDispatch0 {
	//		    void (*dispatch0) (struct SParamData* pd);
	//		};
	//
	//		struct SDllDispatch0 dll_dispatch[] = {
	//		    &dispatch_voidptr_voidptr_voidptr_voidptr;
	//		};
	//
	//////


	//////////
	// file.c and file_1.h output
	//////
		writeout_file_c(tnMaxParams, functionName, tfh_c);
		writeout_file_1(tnMaxParams, functionName, tfh_h1);


	//////////
	// file_2.h output
	//////
		writeout((void*)cgc_h2_prefix,	sizeof(cgc_h2_prefix) - 1,	tfh_h2);
		writeout((void*)functionName,	strlen(functionName),		tfh_h2);
		writeout((void*)cgc_h2_postfix,	sizeof(cgc_h2_postfix) - 1,	tfh_h2);
		if (tnThisParam % (unsigned int)(gsIter.nVarParams - 1) == 0)
			writeout((void*)cgc_h2_postfix_vspacer,	sizeof(cgc_h2_postfix_vspacer) - 1,	tfh_h2);


	//////////
	// file_3.h output
	//////
		writeout((void*)cgc_h3_prefix,	sizeof(cgc_h3_prefix) - 1,	tfh_h3);
		writeout((void*)functionName,	strlen(functionName),		tfh_h3);
		writeout((void*)cgc_h3_postfix,	sizeof(cgc_h3_postfix) - 1,	tfh_h3);
		if (tnThisParam % (unsigned int)(gsIter.nVarParams - 1) == 0)
			writeout((void*)cgc_h3_postfix_vspacer,	sizeof(cgc_h3_postfix_vspacer) - 1,	tfh_h3);

}

int generate_pattern_type(char* buffer, int tnType, int tnParam)
{
	if (tnParam <= gsIter.nVarParams)
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
		return((tnParam < gsIter.nVarParams) ? _TRUE : _FALSE);

	} else {
		// We're done processing
		return(_FALSE);
	}
}

void initializeIter(int tnParamCount, int tnVarParams)
{
	gsIter.nMaxParamType	= tnParamCount;
	gsIter.nVarParams		= tnVarParams;

	gsIter.isValid			= _TRUE;
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
	if (incrementIterPart(&gsIter.varParam1, 1) &&
		incrementIterPart(&gsIter.varParam2, 2) &&
		incrementIterPart(&gsIter.varParam3, 3) &&
		incrementIterPart(&gsIter.varParam4, 4) &&
		incrementIterPart(&gsIter.varParam5, 5) &&
		incrementIterPart(&gsIter.varParam6, 6))
	{
		// This if block is used as a placeholder to allow as many as are valid to pass through incrementing
	}
}

int incrementIterPart(int* iptr, int tnParam)
{
	//////////
	// Are we beyond our count of variable params?
	//////
		if (tnParam > gsIter.nVarParams)
			return(_FALSE);	// Yes


	//////////
	// Can we increment?
	//////
		if (*iptr < _PARAM_TYPE_MAX)
		{
			// Yes
			++*iptr;
			return(_FALSE);

		} else {
			// No, so wrap it around
			*iptr = _PARAM_TYPE_MIN;

			// Success is now based on whether or not this was the last variable param or not
			if (tnParam == gsIter.nVarParams)
				gsIter.isValid = _FALSE;
		}


	//////////
	// Indicate our status
	//////
		return(gsIter.isValid);

}

void writeout_file_c(int tnMaxParams, char* tcFunctionName, FILE* tfh)
{
	int		lnI;
	char	buffer[8];
	char	n0[8];	// for _00 functionName postfix
	char	nv[8];	// for _0v functionName postfix
	char	nf[8];	// for _0f functionName postfix
	char	nd[8];	// for _0d functionName postfix


	//////////
	// Write function header
	//////
		writeout((void*)cgc_c_function_prefix1,		sizeof(cgc_c_function_prefix1) - 1,		tfh);
		writeout((void*)tcFunctionName,				strlen(tcFunctionName),					tfh);
		writeout((void*)cgc_c_function_prefix2,		sizeof(cgc_c_function_prefix2) - 1,		tfh);


	//////////
	// Build case statements, one for each parameter count
	//////
		for (lnI = 0; lnI <= tnMaxParams; lnI++)
		{
			//////////
			// Write the case instance header
			//////
				writeout((void*)cgc_c_case_1, sizeof(cgc_c_case_1) - 1, tfh);
				sprintf(buffer, "%d", lnI);
				writeout((void*)buffer, strlen(buffer), tfh);
				writeout((void*)cgc_c_case_2, sizeof(cgc_c_case_2) - 1, tfh);
				writeout((void*)buffer, strlen(buffer), tfh);
				if (lnI == 1)		writeout((void*)cgc_c_case_3_singular,	sizeof(cgc_c_case_3_singular) - 1,	tfh);
				else				writeout((void*)cgc_c_case_3_plural,	sizeof(cgc_c_case_3_plural) - 1,	tfh);


			//////////
			// Build postfix for this iteration
			//////
				sprintf(n0, "%d0", lnI);
				sprintf(nv, "%dv", lnI);
				sprintf(nf, "%df", lnI);
				sprintf(nd, "%dd", lnI);


			//////////
			// Write out the switch block
			//////
				writeout((void*)cgc_c_switch_prefix,	sizeof(cgc_c_switch_prefix) - 1,	tfh);
				writeout((void*)tcFunctionName,			strlen(tcFunctionName),				tfh);
				writeout((void*)n0,						strlen(n0),							tfh);
				writeout((void*)cgc_c_switch_1_prefix,	sizeof(cgc_c_switch_1_prefix) - 1,	tfh);
				writeout_param_values(lnI, tfh);
				writeout((void*)cgc_c_switch_1_postfix,	sizeof(cgc_c_switch_1_postfix) - 1,	tfh);
				writeout((void*)tcFunctionName,			strlen(tcFunctionName),				tfh);
				writeout((void*)nv,						strlen(nv),							tfh);
				writeout((void*)cgc_c_switch_2_prefix,	sizeof(cgc_c_switch_2_prefix) - 1,	tfh);
				writeout_param_values(lnI, tfh);
				writeout((void*)cgc_c_switch_2_postfix,	sizeof(cgc_c_switch_2_postfix) - 1,	tfh);
				writeout((void*)tcFunctionName,			strlen(tcFunctionName),				tfh);
				writeout((void*)nf,						strlen(nf),							tfh);
				writeout((void*)cgc_c_switch_3_prefix,	sizeof(cgc_c_switch_3_prefix) - 1,	tfh);
				writeout_param_values(lnI, tfh);
				writeout((void*)cgc_c_switch_3_postfix,	sizeof(cgc_c_switch_3_postfix) - 1,	tfh);
				writeout((void*)tcFunctionName,			strlen(tcFunctionName),				tfh);
				writeout((void*)nf,						strlen(nf),							tfh);
				writeout((void*)cgc_c_switch_4_prefix,	sizeof(cgc_c_switch_4_prefix) - 1,	tfh);
				writeout_param_values(lnI, tfh);
				writeout((void*)cgc_c_switch_4_postfix,	sizeof(cgc_c_switch_4_postfix) - 1,	tfh);

		}


	//////////
	// Write function footer
	//////
		writeout((void*)cgc_c_footer, sizeof(cgc_c_footer) - 1, tfh);

}

void writeout_file_1(int tnMaxParams, char* tcFunctionName, FILE* tfh)
{
	int		lnI;
	char	n0[8];	// for _00 functionName postfix
	char	nv[8];	// for _0v functionName postfix
	char	nf[8];	// for _0f functionName postfix
	char	nd[8];	// for _0d functionName postfix


	//////////
	// Iterate once through for each parameter count
	//////
		for (lnI = 0; lnI <= tnMaxParams; lnI++)
		{
			// Build postfix for this iteration
			sprintf(n0, "%d0", lnI);
			sprintf(nv, "%dv", lnI);
			sprintf(nf, "%df", lnI);
			sprintf(nd, "%dd", lnI);

			// Write out this block
			writeout_file_1_part(lnI,	tcFunctionName,		n0,		(char*)cgc_h1_prefix_void,			sizeof(cgc_h1_prefix_void) - 1,				tfh);
			writeout_file_1_part(lnI,	tcFunctionName,		nv,		(char*)cgc_h1_prefix_void_pointer,	sizeof(cgc_h1_prefix_void_pointer) - 1,		tfh);
			writeout_file_1_part(lnI,	tcFunctionName,		nf,		(char*)cgc_h1_prefix_float,			sizeof(cgc_h1_prefix_float) - 1,			tfh);
			writeout_file_1_part(lnI,	tcFunctionName,		nd,		(char*)cgc_h1_prefix_double,		sizeof(cgc_h1_prefix_double) - 1,			tfh);

			// Double-space between
			writeout((void*)cgc_h1_postfix_vspacer, sizeof(cgc_h1_postfix_vspacer) - 1, tfh);
		}

}


void writeout_file_1_part(int tnThisParam, char* tcFunctionName, char* tcPostfix, char* tcReturnType, int tnReturnTypeLength, FILE* tfh)
{

	//////////
	// Append fixed parts
	//////
		writeout((void*)cgc_h1_prefix_common,	sizeof(cgc_h1_prefix_common) - 1,	tfh);	// leading spaces
		writeout((void*)tcReturnType,			tnReturnTypeLength,					tfh);	// "void"
		writeout((void*)cgc_h1_prefix,			sizeof(cgc_h1_prefix) - 1,			tfh);	// "_dispatch_"
		writeout((void*)tcFunctionName,			strlen(tcFunctionName),				tfh);	// "voidptr_voidptr_voidptr_voidptr"
		writeout((void*)tcPostfix,				strlen(tcPostfix),					tfh);	// "_00"
		writeout((void*)cgc_h1_postfix_1,		sizeof(cgc_h1_postfix_1) - 1,		tfh);	// ")   ("


	//////////
	// Append variable parameter count
	//////
		if (tnThisParam == 0)
		{
			// No parameters, so fill with "void"
			writeout((void*)cgc_h1_param_void, sizeof(cgc_h1_param_void) - 1, tfh);

		} else {
			// Multiple parameters, write out each
			writeout_param_types(tnThisParam, tfh);
		}


	//////////
	// Close it up
	//////
		writeout((void*)cgc_h1_postfix_2,		sizeof(cgc_h1_postfix_2) - 1,		tfh);	// ");\n"

}

void writeout_param_values(int tnMaxLineParams, FILE* tfh)
{
	int lnI;


	//////////
	// Process as many parameters as there are up to the first six
	//////
		if (tnMaxLineParams > 0)
		{
			if (writeout_param_values_this_type(1, tnMaxLineParams, &gsIter.varParam1, ((tnMaxLineParams > 1) ? _TRUE : _FALSE), tfh) &&
				writeout_param_values_this_type(2, tnMaxLineParams, &gsIter.varParam2, ((tnMaxLineParams > 2) ? _TRUE : _FALSE), tfh) &&
				writeout_param_values_this_type(3, tnMaxLineParams, &gsIter.varParam3, ((tnMaxLineParams > 3) ? _TRUE : _FALSE), tfh) &&
				writeout_param_values_this_type(4, tnMaxLineParams, &gsIter.varParam4, ((tnMaxLineParams > 4) ? _TRUE : _FALSE), tfh) &&
				writeout_param_values_this_type(5, tnMaxLineParams, &gsIter.varParam5, ((tnMaxLineParams > 5) ? _TRUE : _FALSE), tfh) &&
				writeout_param_values_this_type(6, tnMaxLineParams, &gsIter.varParam6, ((tnMaxLineParams > 6) ? _TRUE : _FALSE), tfh))
			{
				// There are at least seven parametes, the rest are all written out as void* values
				for (lnI = 7; lnI <= tnMaxLineParams; lnI++)
					writeout_param_values_this_type(lnI, tnMaxLineParams, NULL, ((tnMaxLineParams > lnI) ? _TRUE : _FALSE), tfh);
			}
		}

}

int writeout_param_values_this_type(int tnThisParam, int tnMaxParams, int* iptr, int tlIncludePostfixComma, FILE* tfh)
{
	char buffer[12];


	//////////
	// Prefix the parameter with the constant portion
	//////
		writeout((void*)cgc_c_param_prefix_1,		sizeof(cgc_c_param_prefix_1) - 1,		tfh);
		sprintf(buffer, "%d", tnThisParam);
		writeout((void*)buffer,						strlen(buffer),							tfh);
		writeout((void*)cgc_c_param_prefix_2,		sizeof(cgc_c_param_prefix_2) - 1,		tfh);


	//////////
	// Dispatch either an explicit type, or fallback on the void* type
	//////
		if (tnThisParam <= gsIter.nVarParams)
		{
			// Written out based on the type
			switch (*iptr)
			{
				case _PARAM_TYPE_VOIDPTR:
					writeout((void*)cgc_c_param_void_pointer, sizeof(cgc_c_param_void_pointer) - 1, tfh);
					break;

				case _PARAM_TYPE_FLOAT:
					writeout((void*)cgc_c_param_float, sizeof(cgc_c_param_float) - 1, tfh);
					break;

				case _PARAM_TYPE_DOUBLE:
					writeout((void*)cgc_c_param_double, sizeof(cgc_c_param_double) - 1, tfh);
					break;
			}

		} else {
			// Always void*
			writeout((void*)cgc_c_param_void_pointer, sizeof(cgc_c_param_void_pointer) - 1, tfh);
		}


	//////////
	// Append a comma if need be
	//////
		if (tlIncludePostfixComma == _TRUE)
			writeout((void*)cgc_c_param_comma, sizeof(cgc_c_param_comma) - 1, tfh);


	//////////
	// Indicate if there are more parameters
	//////
		return((tnThisParam < tnMaxParams) ? _TRUE : _FALSE);

}

void writeout_param_types(int tnMaxLineParams, FILE* tfh)
{
	int lnI;


	//////////
	// Process as many parameters as there are up to the first six
	//////
		if (writeout_param_this_type(1, tnMaxLineParams, &gsIter.varParam1, ((tnMaxLineParams > 1) ? _TRUE : _FALSE), tfh) &&
			writeout_param_this_type(2, tnMaxLineParams, &gsIter.varParam2, ((tnMaxLineParams > 2) ? _TRUE : _FALSE), tfh) &&
			writeout_param_this_type(3, tnMaxLineParams, &gsIter.varParam3, ((tnMaxLineParams > 3) ? _TRUE : _FALSE), tfh) &&
			writeout_param_this_type(4, tnMaxLineParams, &gsIter.varParam4, ((tnMaxLineParams > 4) ? _TRUE : _FALSE), tfh) &&
			writeout_param_this_type(5, tnMaxLineParams, &gsIter.varParam5, ((tnMaxLineParams > 5) ? _TRUE : _FALSE), tfh) &&
			writeout_param_this_type(6, tnMaxLineParams, &gsIter.varParam6, ((tnMaxLineParams > 6) ? _TRUE : _FALSE), tfh))
		{
			// There are at least seven parametes, the rest are all written out as void* values
			for (lnI = 7; lnI <= tnMaxLineParams; lnI++)
				writeout_param_this_type(lnI, tnMaxLineParams, NULL, ((tnMaxLineParams > lnI) ? _TRUE : _FALSE), tfh);
		}
}

int writeout_param_this_type(int tnThisParam, int tnMaxParams, int* iptr, int tlIncludePostfixComma, FILE* tfh)
{

	//////////
	// Dispatch either an explicit type, or fallback on the void* type
	//////
		if (tnThisParam <= gsIter.nVarParams)
		{
			// Written out based on the type
			switch (*iptr)
			{
				case _PARAM_TYPE_VOIDPTR:
					writeout((void*)cgc_h1_param_void_pointer, sizeof(cgc_h1_param_void_pointer) - 1, tfh);
					break;

				case _PARAM_TYPE_FLOAT:
					writeout((void*)cgc_h1_param_float, sizeof(cgc_h1_param_float) - 1, tfh);
					break;

				case _PARAM_TYPE_DOUBLE:
					writeout((void*)cgc_h1_param_double, sizeof(cgc_h1_param_double) - 1, tfh);
					break;
			}

		} else {
			// Always written out as void* beyond here
			writeout((void*)cgc_h1_param_void_pointer, sizeof(cgc_h1_param_void_pointer) - 1, tfh);
		}


	//////////
	// Append a comma if need be
	//////
		if (tlIncludePostfixComma == _TRUE)
			writeout((void*)cgc_h1_param_comma, sizeof(cgc_h1_param_comma) - 1, tfh);


	//////////
	// Indicate if there are more parameters
	//////
		return((tnThisParam < tnMaxParams) ? _TRUE : _FALSE);

}

FILE* createfile(char* tcFileName)
{
	FILE* lfh;


	//////////
	// Try to create the output file
	/////
		lfh = fopen(tcFileName, "wb+");
		if (!lfh)
		{
			printf("ERROR: Unable to create %s\n", tcFileName);
			exit(-1);
		}

	// We're good
	return(lfh);
}

void writeout(void* data, size_t tnSize, FILE* fh)
{
	size_t lnNum;


	//////////
	// Write out the data
	//////
		lnNum = fwrite(data, 1, tnSize, fh);


	//////////
	// If there's an error, we're done
	//////
		if (lnNum != tnSize)
		{
			printf("ERROR: Unable to write %d bytes to output, wrote %d.\n", (int)tnSize, (int)lnNum);
			exit(-2);
		}
}
