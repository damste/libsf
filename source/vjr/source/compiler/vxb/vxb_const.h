//////////
//
// /libsf/source/vjr/source/compiler/vxb/vxb_const.h
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
//     Jun.29.2014
//////
// Change log:
//     Jun.29.2014 - Initial creation
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
//   ___      ___   ___  ___    _______
//  |"  \    /"  | |"  \/"  |  |   _  "\
//   \   \  //  /   \   \  /   (. |_)  :)
//    \\  \/. ./     \\  \/    |:     \/
//     \.    //      /\.  \    (|  _  \\
//      \\   /      /  \   \   |: |_)  :)
//       \__/      |___/\___|  (_______/
//     Visual FreePro, Jr. XBase Compiler
//
//////////




//////////
// Known operators to the system
//////
	const u32		_SUB_INSTR_ADD									= 1;// Pattern of x + y
	const u32		_SUB_INSTR_SUBTRACT								= 2;// Pattern of x - y
	const u32		_SUB_INSTR_MULTIPLY								= 3;// Pattern of x * y
	const u32		_SUB_INSTR_DIVIDE								= 4;// Pattern of x / y
	const u32		_SUB_INSTR_MODULO								= 5;// Pattern of x % y
	const u32		_SUB_INSTR_EXPONENT								= 6;// Pattern of x^y or x**y
	const u32		_SUB_INSTR_FUNCTION								= 7;// Pattern of xyz(....)
	const u32		_SUB_INSTR_ARRAY								= 8;// Pattern of array[...]
	const u32		_SUB_INSTR_PLUS_PLUS_X							= 9;// Pattern of ++x (increment, then get value)
	const u32		_SUB_INSTR_X_PLUS_PLUS							= 10;// Pattern of x++ (get value, then increment)
	const u32		_SUB_INSTR_MINUS_MINUS_X						= 11;// Pattern of --x (decrement, then get value)
	const u32		_SUB_INSTR_X_MINUS_MINUS						= 12;// Pattern of x-- (get value, then decrement)
	const u32		_SUB_INSTR_AND									= 13;// Pattern of x AND y
	const u32		_SUB_INSTR_OR									= 14;// Pattern of x OR y
	const u32		_SUB_INSTR_NOT									= 15;// Pattern of NOT x
	const u32		_SUB_INSTR_DOT_EXPANSION						= 16;// Pattern of x.y
	const u32		_SUB_INSTR_EXCLAMATION_MARK_EXPANSION			= 17;// Pattern of x!y
	const u32		_SUB_INSTR_LESS_THAN							= 18;// Pattern of x < y
	const u32		_SUB_INSTR_GREATER_THAN							= 19;// Pattern of x > y
	const u32		_SUB_INSTR_LESS_THAN_OR_EQUAL_TO				= 20;// Pattern of x <= y
	const u32		_SUB_INSTR_GREATER_THAN_OR_EQUAL_TO				= 21;// Pattern of x >= y
	const u32		_SUB_INSTR_NOT_EQUAL_TO							= 22;// Pattern of x != y
	const u32		_SUB_INSTR_EQUAL_TO								= 23;// Pattern of x = y
	const u32		_SUB_INSTR_EXACTLY_EQUAL_TO						= 24;// Pattern of x == y
	const u32		_SUB_INSTR_FOUND_IN								= 25;// Pattern of x $ y
	const u32		_SUB_INSTR_NOT_FOUND_IN							= 26;// Pattern of x !$ y
	const u32		_SUB_INSTR_ERROR								= 1000;// An error was encountered and we stop at this source code line
	const u32		_SUB_INSTR_FLAGS								= 1001;// A flag was given for this line

	const u32		_OP_TYPE_NULL									= 0;// A NULL type, indicating a compile error occurred on this control
	const u32		_OP_TYPE_COMP									= 1;// A component
	const u32		_OP_TYPE_PARAM									= 2;// A parameter
	const u32		_OP_TYPE_LOCAL									= 3;// A local variable
	const u32		_OP_TYPE_SCOPED									= 4;// A scoped / temporary variable
	const u32		_OP_TYPE_RETURNS								= 5;// A returns variable
	const u32		_OP_TYPE_OTHER									= 6;// Some other variable which is always referenced
	const u32		_OP_TYPE_FUNCTION								= 7;// A function
	const u32		_OP_TYPE_OBJECT									= 8;// An object
	const u32		_OP_TYPE_PARENTHESIS_LEFT						= 9;// (Temporary) A left parenthesis

	const u32		_NODE_NONE										= 0;
	const u32		_NODE_PARENT									= 1;
	const u32		_NODE_PREV										= 2;
	const u32		_NODE_NEXT										= 3;
	const u32		_NODE_LEFT										= 4;
	const u32		_NODE_RIGHT										= 5;


//////////
// Logical and LogicalX definitions
//////
	const s32		_LOGICAL_FALSE									= 0;
	const s32		_LOGICAL_TRUE									= -1;
	const s32		_LOGICALX_OTHER									= 'O';
	const s32		_LOGICALX_PARTIAL								= 'P';
	const s32		_LOGICALX_EXTRA									= 'X';
	const s32		_LOGICALX_YET_ANOTHER							= 'Y';
	const s32		_LOGICALX_ZATS_ALL_FOLKS						= 'Z';


//////////
// Warnings
//////
	const u32		_WARNING_SPURIOUS_COMPONENTS_IGNORED			= 1;
	const u32		_WARNING_UNSPECIFIED_WARNING					= 2;

	// Messages
	const u8		cgcSpuriousIgnored[]							= "spurious, ignored";
	const u8		cgcUnspecifiedWarning[]							= "warning";

	// Fill ins
	const u8		cgc_notFoundOrInvalidDataType[]					= "not found or is invalid data type";

	// Messages
#ifdef _LANG_EN
	const u8		cgcVjrError[]									= "Visual FreePro, Jr. Encountered an Error";
	const s8		cgcFeatureNotYetSupported[]						= "feature not yet supported";
	const u8		cgcComponentError[]								= "Error in component, column ";
	const u8		cgcOutOfMemory[]								= "out of memory";
	const u8		cgcUnexpectedCommand[]							= "unexpected command";
	const u8		cgcContextHasChanged[]							= "context has changed";
	const u8		cgcFullRecompileRequired[]						= "full recompile required";
	const u8		cgcNotAVariable[]								= "not a variable";
	const u8		cgcNumericOverflow[]							= "numeric overflow";
	const u8		cgcNotNumeric[]									= "not numeric";
	const u8		cgcEmptyString[]								= "empty string";
	const u8		cgcSyntaxError[]								= "syntax error";
	const u8		cgcUnrecognizedParameter[]						= "unrecognized parameter";
	const u8		cgcOutOfRange[]									= "out of range";
	const u8		cgcCommaExpected[]								= "comma expected";
	const u8		cgcTooManyParameters[]							= "too many parameters";
	const u8		cgcDataTypeMismatch[]							= "data type mismatch";
	const u8		cgcFeatureNotAvailable[]						= "feature not available";
	const u8		cgcP1IsIncorrect[]								= "parameter 1 is incorrect";
	const u8		cgcP2IsIncorrect[]								= "parameter 2 is incorrect";
	const u8		cgcP3IsIncorrect[]								= "parameter 3 is incorrect";
	const u8		cgcP4IsIncorrect[]								= "parameter 4 is incorrect";
	const u8		cgcP5IsIncorrect[]								= "parameter 5 is incorrect";
	const u8		cgcP6IsIncorrect[]								= "parameter 6 is incorrect";
	const u8		cgcP7IsIncorrect[]								= "parameter 7 is incorrect";
	const u8		cgcInternalError[]								= "internal error";
	const u8		cgcInvalidArgumentTypeCountError[]				= "invalid argument, type, or count";
	const u8		cgcVariableNotFoundError[]						= "variable not found";
	const u8		cgcAliasNotFoundError[]							= "alias not found";
	const u8		cgcInvalidWorkArea[]							= "invalid work area";
	const u8		cgcAliasAlreadyInUse[]							= "alias already in use";
	const u8		cgcParenthesisExpected[]						= "parenthesis expected";
	const u8		cgcMissingParameter[]							= "missing parameter";

	const u8		cgcDbfUnableToOpenTable[]						= "unable to open table";
	const u8		cgcDbfWorkAreaAlreadyInUse[]					= "work area already in use";
	const u8		cgcDbfErrorOpeningDbc[]							= "error in opening dbc";
	const u8		cgcDbfWorkAreaNotInUse[]						= "work area not in use";
	const u8		cgcDbfErrorReadingHeader1[]						= "reading header(1)";
	const u8		cgcDbfUnknownTableType[]						= "unknown table type";
	const u8		cgcDbfMemoryAllocation[]						= "memory allocation";
	const u8		cgcDbfErrorReadingHeader2[]						= "reading header(2)";
	const u8		cgcDbfTableNameTooLong[]						= "table name too long";
	const u8		cgcDbfMemoryRow[]								= "memory row buffer";
	const u8		cgcDbfMemoryOriginal[]							= "memory original buffer";
	const u8		cgcDbfMemoryIndex[]								= "memory index buffer";
	const u8		cgcDbfInvalidWorkArea[]							= "invalid work area";
	const u8		cgcDbfNoMoreWorkAreas[]							= "no more work areas";
	const u8		cgcDbfLocking[]									= "locking";
	const u8		cgcDbfWriting[]									= "writing";
	const u8		cgcDbfSeeking[]									= "seeking";
	const u8		cgcDbfNoData[]									= "no data";
	const u8		cgcDbfUnknownMemoFormat[]						= "unknown memo format";

	const u8		cgcConflictingParameters[]						= "conflicting parameters";
	const u8		cgcParameterIsIncorrect[]						= "parameter is incorrect";
	const u8		cgcTableAlreadyInUse[]							= "table already in use";
	const u8		cgcParameterTooLong[]							= "parameter too long";
	const u8		cgcUnableToOpenDbc[]							= "unable to open container";
	const u8		cgcDivisionByZero[]								= "division by zero";
	const u8		cgcCannotBeNegative[]							= "parameter cannot be negative";
	const u8		cgcFatalSystemError_tally[]						= "system variable _tally could not be found";
	const u8		cgcCannotBeZeroOrNegative[]						= "parameter cannot be negative or 0";
	const u8		cgcUnableToAutoValidate[]						= "unable to auto-validate";
	const u8		cgcGeneralErrorDbf[]							= "dbf general error";
	const u8		cgcCannotBeZero[]								= "parameter cannot be 0";
	const u8		cgcMustBeLogical[]								= "parameter must be logical";
	const u8		cgcParameterMustBe8_16_32_64[]					= "parameter must be 8, 16, 32, or 64";
	const u8		cgcTooBigForTarget[]							= "too big for target";
	const u8		cgcNoIndexIsLoaded[]							= "no index is loaded";
	const u8		cgcInvalidIndextag[]							= "invalid index tag";
	const u8		cgcUnableToSave[]								= "unable to save";
	const u8		cgcInvalidParameters[]							= "invalid parameters";
	const u8		cgcParameterMustBeOne[]							= "parameter must be 1";
	const u8		cgcIndexCorruptNeedsRebuilt[]					= "index is corrupt and needs rebuilt";
	const u8		cgcUnableToLockForWrite[]						= "unable to lock for write";
	const u8		cgcUnableToLockForRead[]						= "unable to lock for read";
	const u8		cgcUnableToInitialize[]							= "unable to initialize";
	const u8		cgcUnknownFunction[]							= "unknown function";
	const u8		cgcDllNotFound[]								= "dll not found";
#else
	#error Language not specified
#endif


//////////
// Radix conversion strings for iVariable_createByRadix()
//////
	cu8				cgcBase10[]										= "0123456789";
	cu8				cgcBase26[]										= "ABCDEFFGHIJKLMNOPQRSTUVWXYZ";
	cu8				cgcBase36[]										= "0123456789ABCDEFFGHIJKLMNOPQRSTUVWXYZ";
	cu8				cgcBase52[]										= "ABCDEFFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	cu8				cgcBase62[]										= "0123456789ABCDEFFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	cu8				cgcBase256[256]									= { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255 };
	//////////
	// No, I did not type all of these numbers. :-)
	// 	x = SPACE(0)
	// 	FOR lnI = 0 TO 255
	// 		x = x + IIF(LEN(x) != 0, ", ", SPACE(0)) + TRANSFORM(lnI)
	// 	NEXT
	// 	_cliptext = x
	//////


	// Combined items
	const s32		_ICODE_SINGLE_QUOTED_TEXT						= 90;
	const s32		_ICODE_DOUBLE_QUOTED_TEXT						= 91;

	// VJr-specific Keywords
	const s32		_ICODE_VJR										= 200;
	const s32		_ICODE_CMD										= 201;
	const s32		_ICODE_JDEBI									= 202;
	const s32		_ICODE_PROTECTED								= 203;
	const s32		_ICODE_MAIN										= 204;
	const s32		_ICODE_LOAD_LAST_FROM_VJR_USER_DBF				= 205;
	const s32		_ICODE_FLAGS									= 206;
	const s32		_ICODE_META										= 207;
	const s32		_ICODE_MEFA										= 208;
	const s32		_ICODE_MEIA										= 209;
	const s32		_ICODE_MEMA										= 210;
	const s32		_ICODE_METAICASE								= 211;
	const s32		_ICODE_MEFAICASE								= 212;
	const s32		_ICODE_MEIAICASE								= 213;
	const s32		_ICODE_MEMAICASE								= 214;
	const s32		_ICODE_FLOW										= 215;
	const s32		_ICODE_SUBFLOW									= 216;
	const s32		_ICODE_FLOWTO									= 217;
	const s32		_ICODE_FLOWOUT									= 218;
	const s32		_ICODE_FLOWOF									= 219;
	const s32		_ICODE_RGBA										= 220;
	const s32       _ICODE_LOBJECT								    = 221;
	const s32		_ICODE_PARAMS									= 222;
	const s32		_ICODE_RETURNS									= 223;
	const s32		_ICODE_AS										= 224;
	const s32		_ICODE_CHARACTER								= 225;
	const s32		_ICODE_INTEGER									= 226;
	const s32		_ICODE_FLOAT									= 227;
	const s32		_ICODE_DOUBLE									= 228;
	const s32		_ICODE_LOGICAL									= 229;
	const s32		_ICODE_S32										= 230;
	const s32		_ICODE_S64										= 231;
	const s32		_ICODE_U32										= 232;
	const s32		_ICODE_U64										= 233;
	const s32		_ICODE_F32										= 234;
	const s32		_ICODE_F64										= 235;
	const s32		_ICODE_BI										= 236;
	const s32		_ICODE_BFP										= 237;
	const s32		_ICODE_S16										= 238;
	const s32		_ICODE_S8										= 239;
	const s32		_ICODE_U16										= 240;
	const s32		_ICODE_U8										= 241;
	const s32		_ICODE_ADHOC									= 242;
	const s32		_ICODE_ENDADHOC									= 243;
	const s32		_ICODE_SETTINGS									= 244;
	const s32		_ICODE_SINGLE									= 245;		// Same as _ICODE_FLOAT
	const s32		_ICODE_STRING									= 246;		// Same as _ICODE_CHARACTER
	const s32		_ICODE_VOIDPTR									= 247;

	// Relatives
	const s32		_ICODE_THISCODE									= 600;
	const s32		_ICODE_THISCLASS								= 601;
	const s32		_ICODE_THISFORM									= 602;
	const s32		_ICODE_PARENT									= 603;

	// Stand-alones
	const s32	    _ICODE_TRUE										= 700;
	const s32	    _ICODE_FALSE									= 701;
	const s32	    _ICODE_YES										= 702;
	const s32	    _ICODE_NO										= 703;
	const s32	    _ICODE_UP										= 704;
	const s32	    _ICODE_DOWN										= 705;
	const s32	    _ICODE_OTHER									= 706;
	const s32	    _ICODE_PARTIAL									= 707;
	const s32		_ICODE_EXTRA									= 708;
	const s32	    _ICODE_YET_ANOTHER								= 709;
	const s32	    _ICODE_ZATS_ALL_FOLKS							= 710;

	// Conversions
	const s32		_ICODE_DOT_VARIABLE								= 800;

	// DLL relative
	const s32		_ICODE_WIN32API									= 900;
	const s32		_ICODE_KERNEL32									= 901;
	const s32		_ICODE_GDI32									= 902;
	const s32		_ICODE_USER32									= 903;
	const s32		_ICODE_MPR										= 904;
	const s32		_ICODE_ADVAPI32									= 905;

	// Functions
	const s32		_ICODE_ABS										= 1000;
	const s32		_ICODE_ACLASS                                   = 1001;
	const s32		_ICODE_ACOPY                                    = 1002;
	const s32		_ICODE_ACOS                                     = 1003;
	const s32		_ICODE_ADATABASES                               = 1004;
	const s32		_ICODE_ADBOBJECTS                               = 1005;
	const s32		_ICODE_ADDBS                                    = 1006;
	const s32		_ICODE_ADDOBJECT								= 1432;
	const s32		_ICODE_ADDPROPERTY                              = 1007;
	const s32		_ICODE_ADEL                                     = 1008;
	const s32		_ICODE_ADIR                                     = 1009;
	const s32		_ICODE_ADLLS                                    = 1010;
	const s32		_ICODE_ADOCKSTATE                               = 1011;
	const s32		_ICODE_AELEMENT                                 = 1012;
	const s32		_ICODE_AERROR                                   = 1013;
	const s32		_ICODE_AEVENTS                                  = 1014;
	const s32		_ICODE_AFIELDS                                  = 1015;
	const s32		_ICODE_AFONT                                    = 1016;
	const s32		_ICODE_AGAIN									= 1439;
	const s32		_ICODE_AGETCLASS                                = 1017;
	const s32		_ICODE_AGETFILEVERSION                          = 1018;
	const s32		_ICODE_AINSTANCE                                = 1019;
	const s32		_ICODE_AINS                                     = 1020;
	const s32		_ICODE_ALANGUAGE                                = 1021;
	const s32		_ICODE_ALEN                                     = 1022;
	const s32		_ICODE_ALIAS                                    = 1023;
	const s32		_ICODE_ALINES                                   = 1024;
	const s32		_ICODE_ALLTRIM                                  = 1025;
	const s32		_ICODE_ALP										= 1453;
	const s32		_ICODE_AMEMBERS                                 = 1026;
	const s32		_ICODE_AMOUSEOBJ                                = 1027;
	const s32		_ICODE_ANETRESOURCES                            = 1028;
	const s32		_ICODE_APRINTERS                                = 1029;
	const s32		_ICODE_APROCINFO                                = 1030;
	const s32		_ICODE_ASCAN                                    = 1031;
	const s32		_ICODE_ASC                                      = 1032;
	const s32		_ICODE_ASCENDING								= 1434;
	const s32		_ICODE_ASELOBJ                                  = 1033;
	const s32		_ICODE_ASESSIONS                                = 1034;
	const s32		_ICODE_ASIN                                     = 1035;
	const s32		_ICODE_ASORT                                    = 1036;
	const s32		_ICODE_ASQLHANDLES                              = 1037;
	const s32		_ICODE_ASTACKINFO                               = 1038;
	const s32		_ICODE_ASUBSCRIPT                               = 1039;
	const s32		_ICODE_AT_C                                     = 1040;
	const s32		_ICODE_AT                                       = 1041;
	const s32		_ICODE_ATAGINFO                                 = 1042;
	const s32		_ICODE_ATAN                                     = 1043;
	const s32		_ICODE_ATCLINE                                  = 1044;
	const s32		_ICODE_ATCC                                     = 1045;
	const s32		_ICODE_ATC                                      = 1046;
	const s32		_ICODE_ATLINE                                   = 1047;
	const s32		_ICODE_ATN2                                     = 1048;
	const s32		_ICODE_AUSED                                    = 1049;
	const s32		_ICODE_AUTOMATIC								= 1450;
	const s32		_ICODE_AVCXCLASSES                              = 1050;
	const s32		_ICODE_BARPROMPT                                = 1051;
	const s32		_ICODE_BARCOUNT                                 = 1052;
	const s32		_ICODE_BAR                                      = 1053;
	const s32		_ICODE_BETWEEN                                  = 1054;
	const s32		_ICODE_BGR										= 1451;
	const s32		_ICODE_BGRA										= 1452;
	const s32		_ICODE_BLU										= 1454;
	const s32		_ICODE_BINDEVENT                                = 1055;
	const s32		_ICODE_BINTOC                                   = 1056;
	const s32		_ICODE_BITS										= 1469;
	const s32		_ICODE_BITS8									= 1470;
	const s32		_ICODE_BITS16									= 1471;
	const s32		_ICODE_BITS32									= 1472;
	const s32		_ICODE_BITS64									= 1473;
	const s32		_ICODE_BITAND                                   = 1057;
	const s32		_ICODE_BITCLEAR                                 = 1058;
	const s32		_ICODE_BITLSHIFT                                = 1059;
	const s32		_ICODE_BITNOT                                   = 1060;
	const s32		_ICODE_BITOR                                    = 1061;
	const s32		_ICODE_BITRSHIFT                                = 1062;
	const s32		_ICODE_BITSET                                   = 1063;
	const s32		_ICODE_BITSLICE									= 1466;
	const s32		_ICODE_BITSTR									= 1475;
	const s32		_ICODE_BITTEST                                  = 1064;
	const s32		_ICODE_BITXOR                                   = 1065;
	const s32		_ICODE_BOF                                      = 1066;
	const s32		_ICODE_CANDIDATE                                = 1067;
	const s32		_ICODE_CAPSLOCK                                 = 1068;
	const s32		_ICODE_CAST                                     = 1069;
	const s32		_ICODE_CDOW                                     = 1070;
	const s32		_ICODE_CDX                                      = 1071;
	const s32		_ICODE_CEILING                                  = 1072;
	const s32		_ICODE_CHR                                      = 1073;
	const s32		_ICODE_CHRSAW                                   = 1074;
	const s32		_ICODE_CHRTRANC									= 1075;
	const s32		_ICODE_CHRTRAN                                  = 1076;
	const s32		_ICODE_CLEARRESULTSET                           = 1077;
	const s32		_ICODE_CMONTH                                   = 1078;
	const s32		_ICODE_CNTBAR                                   = 1079;
	const s32		_ICODE_CNTPAD                                   = 1080;
	const s32		_ICODE_COL                                      = 1081;
	const s32		_ICODE_COLORIZE									= 1459;
	const s32		_ICODE_COMARRAY                                 = 1082;
	const s32		_ICODE_COMCLASSINFO                             = 1083;
	const s32		_ICODE_COMMAND                                  = 1084;
	const s32		_ICODE_COMPOBJ                                  = 1085;
	const s32		_ICODE_COMPROP                                  = 1086;
	const s32		_ICODE_COMRETURNERROR                           = 1087;
	const s32		_ICODE_COMS                                     = 1088;
	const s32		_ICODE_CONNSTRING								= 1441;
	const s32		_ICODE_COS                                      = 1089;
	const s32		_ICODE_CPCONVERT                                = 1090;
	const s32		_ICODE_CPCURRENT                                = 1091;
	const s32		_ICODE_CPDBF                                    = 1092;
	const s32		_ICODE_CREATEBINARY                             = 1093;
	const s32		_ICODE_CREATEOBJECT                             = 1094;
	const s32		_ICODE_CREATEOBJECTEX                           = 1095;
	const s32		_ICODE_CREATEOFFLINE                            = 1096;
	const s32		_ICODE_CTOBIN                                   = 1097;
	const s32		_ICODE_CTOD                                     = 1098;
	const s32		_ICODE_CTOT                                     = 1099;
	const s32		_ICODE_CURDIR                                   = 1100;
	const s32		_ICODE_CURSORGETPROP                            = 1101;
	const s32		_ICODE_CURSORSETPROP                            = 1102;
	const s32		_ICODE_CURSORTOXML                              = 1103;
	const s32		_ICODE_CURVAL                                   = 1104;
	const s32		_ICODE_DATETIME                                 = 1105;
	const s32		_ICODE_DATETIMEX								= 1483;
	const s32		_ICODE_DATE                                     = 1106;
	const s32		_ICODE_DAY                                      = 1107;
	const s32		_ICODE_DBC                                      = 1108;
	const s32		_ICODE_DBF                                      = 1109;
	const s32		_ICODE_DBGETPROP                                = 1110;
	const s32		_ICODE_DBSETPROP                                = 1111;
	const s32		_ICODE_DBUNDLE									= 1517;
	const s32		_ICODE_DBUSED                                   = 1112;
	const s32		_ICODE_DDEABORTTRANS                            = 1113;
	const s32		_ICODE_DDEADVISE                                = 1114;
	const s32		_ICODE_DDEENABLED                               = 1115;
	const s32		_ICODE_DDEEXECUTE                               = 1116;
	const s32		_ICODE_DDEINITIATE                              = 1117;
	const s32		_ICODE_DDELASTERROR                             = 1118;
	const s32		_ICODE_DDEPOKE                                  = 1119;
	const s32		_ICODE_DDEREQUEST                               = 1120;
	const s32		_ICODE_DDES                                     = 1121;
	const s32		_ICODE_DDESETOPTION                             = 1122;
	const s32		_ICODE_DDESETSERVICE                            = 1123;
	const s32		_ICODE_DDESETTOPIC                              = 1124;
	const s32		_ICODE_DDETERMINATE                             = 1125;
	const s32		_ICODE_DEFAULTEXT                               = 1126;
	const s32		_ICODE_DELETED                                  = 1127;
	const s32		_ICODE_DESCENDING                               = 1128;
	const s32		_ICODE_DIFFERENCE                               = 1129;
	const s32		_ICODE_DIRECTORY                                = 1130;
	const s32		_ICODE_DISKSPACE                                = 1131;
	const s32		_ICODE_DISPLAYPATH                              = 1132;
	const s32		_ICODE_DMY                                      = 1133;
	const s32		_ICODE_DODEFAULT                                = 1134;
	const s32		_ICODE_DOW                                      = 1135;
	const s32		_ICODE_DRIVETYPE                                = 1136;
	const s32		_ICODE_DROPOFFLINE                              = 1137;
	const s32		_ICODE_DTOC                                     = 1138;
	const s32		_ICODE_DTOR                                     = 1139;
	const s32		_ICODE_DTOS                                     = 1140;
	const s32		_ICODE_DTOT                                     = 1141;
	const s32		_ICODE_DTOX										= 1489;
	const s32		_ICODE_DTRANSFORM                               = 1482;
	const s32		_ICODE_DUNBUNDLE								= 1518;
	const s32		_ICODE_EDITSOURCE                               = 1142;
	const s32		_ICODE_EMPTY                                    = 1143;
	const s32		_ICODE_ENDSWITH									= 1476;
	const s32		_ICODE_ENDSWITHC								= 1478;
	const s32		_ICODE_EOF                                      = 1144;
	const s32		_ICODE_ERROR                                    = 1145;
	const s32		_ICODE_EVALUATE                                 = 1146;
	const s32		_ICODE_EVENTHANDLER                             = 1147;
	const s32		_ICODE_EVL                                      = 1148;
	const s32		_ICODE_EXECSCRIPT                               = 1149;
	const s32		_ICODE_EXP                                      = 1150;
	const s32		_ICODE_FCHSIZE                                  = 1151;
	const s32		_ICODE_FCLOSE                                   = 1152;
	const s32		_ICODE_FCOUNT                                   = 1153;
	const s32		_ICODE_FCREATE                                  = 1154;
	const s32		_ICODE_FDATE                                    = 1155;
	const s32		_ICODE_FEOF                                     = 1156;
	const s32		_ICODE_FERROR                                   = 1157;
	const s32		_ICODE_FFLUSH                                   = 1158;
	const s32		_ICODE_FGETS                                    = 1159;
	const s32		_ICODE_FIELD                                    = 1160;
	const s32		_ICODE_FILETOSTR                                = 1161;
	const s32		_ICODE_FILE                                     = 1162;
	const s32		_ICODE_FILTER                                   = 1163;
	const s32		_ICODE_FKLABEL                                  = 1164;
	const s32		_ICODE_FKMAX                                    = 1165;
	const s32		_ICODE_FLDLIST                                  = 1166;
	const s32		_ICODE_FLOCK                                    = 1167;
	const s32		_ICODE_FLOOR                                    = 1168;
	const s32		_ICODE_FONTMETRIC                               = 1169;
	const s32		_ICODE_FOPEN                                    = 1170;
	const s32		_ICODE_FOR                                      = 1171;
	const s32		_ICODE_FORCEEXT                                 = 1172;
	const s32		_ICODE_FORCEFNAME								= 1446;
	const s32		_ICODE_FORCEPATH                                = 1173;
	const s32		_ICODE_FORCESTEM								= 1447;
	const s32		_ICODE_FOUND                                    = 1174;
	const s32		_ICODE_FPUTS                                    = 1175;
	const s32		_ICODE_FREAD                                    = 1176;
	const s32		_ICODE_FSEEK                                    = 1177;
	const s32		_ICODE_FSIZE                                    = 1178;
	const s32		_ICODE_FTIME                                    = 1179;
	const s32		_ICODE_FULLPATH                                 = 1180;
	const s32		_ICODE_FV                                       = 1181;
	const s32		_ICODE_FWRITE                                   = 1182;
	const s32		_ICODE_GETAUTOINCVALUE                          = 1183;
	const s32		_ICODE_GETBAR                                   = 1184;
	const s32		_ICODE_GETCOLOR                                 = 1185;
	const s32		_ICODE_GETCP                                    = 1186;
	const s32		_ICODE_GETCURSORADAPTER                         = 1187;
	const s32		_ICODE_GETDIR                                   = 1188;
	const s32		_ICODE_GETENV                                   = 1189;
	const s32		_ICODE_GETFILE                                  = 1190;
	const s32		_ICODE_GETFLDSTATE                              = 1191;
	const s32		_ICODE_GETFONT                                  = 1192;
	const s32		_ICODE_GETINTERFACE                             = 1193;
	const s32		_ICODE_GETNEXTMODIFIED                          = 1194;
	const s32		_ICODE_GETOBJECT                                = 1195;
	const s32		_ICODE_GETPAD                                   = 1196;
	const s32		_ICODE_GETPEM                                   = 1197;
	const s32		_ICODE_GETPICT                                  = 1198;
	const s32		_ICODE_GETPRINTER                               = 1199;
	const s32		_ICODE_GETRESULTSET                             = 1200;
	const s32		_ICODE_GETWORDCOUNT                             = 1201;
	const s32		_ICODE_GETWORDNUM                               = 1202;
	const s32		_ICODE_GOMONTH                                  = 1203;
	const s32		_ICODE_GRAYSCALE								= 1458;
	const s32		_ICODE_GRN										= 1455;
	const s32		_ICODE_HEADER                                   = 1204;
	const s32		_ICODE_HOME                                     = 1205;
	const s32		_ICODE_HOUR                                     = 1206;
	const s32		_ICODE_ICASE                                    = 1207;
	const s32		_ICODE_IDXCOLLATE                               = 1208;
	const s32		_ICODE_IIF                                      = 1209;
	const s32		_ICODE_IMESTATUS                                = 1210;
	const s32		_ICODE_IN										= 1435;
	const s32		_ICODE_INDBC                                    = 1211;
	const s32		_ICODE_INDEXSEEK                                = 1212;
	const s32		_ICODE_INKEY                                    = 1213;
	const s32		_ICODE_INLIST                                   = 1214;
	const s32		_ICODE_INPUTBOX                                 = 1215;
	const s32		_ICODE_INSMODE                                  = 1216;
	const s32		_ICODE_INT                                      = 1217;
	const s32		_ICODE_ISALPHA                                  = 1218;
	const s32		_ICODE_ISBLANK                                  = 1219;
	const s32		_ICODE_ISCOLOR                                  = 1220;
	const s32		_ICODE_ISDIGIT                                  = 1221;
	const s32		_ICODE_ISEXCLUSIVE                              = 1222;
	const s32		_ICODE_ISFLOCKED                                = 1223;
	const s32		_ICODE_ISLEADBYTE                               = 1224;
	const s32		_ICODE_ISLOWER                                  = 1225;
	const s32		_ICODE_ISMEMOFETCHED                            = 1226;
	const s32		_ICODE_ISMOUSE                                  = 1227;
	const s32		_ICODE_ISNULL                                   = 1228;
	const s32		_ICODE_ISPEN                                    = 1229;
	const s32		_ICODE_ISREADONLY                               = 1230;
	const s32		_ICODE_ISRLOCKED                                = 1231;
	const s32		_ICODE_ISTRANSACTABLE                           = 1232;
	const s32		_ICODE_ISUPPER                                  = 1233;
	const s32		_ICODE_JUSTDRIVE                                = 1234;
	const s32		_ICODE_JUSTEXT                                  = 1235;
	const s32		_ICODE_JUSTFNAME                                = 1236;
	const s32		_ICODE_JUSTPATH                                 = 1237;
	const s32		_ICODE_JUSTSTEM                                 = 1238;
	const s32		_ICODE_KEYMATCH                                 = 1239;
	const s32		_ICODE_KEY                                      = 1240;
	const s32		_ICODE_LOADPARAMS								= 1442;
	const s32		_ICODE_LASTKEY                                  = 1241;
	const s32		_ICODE_LEFTC                                    = 1242;
	const s32		_ICODE_LEFT                                     = 1243;
	const s32		_ICODE_LENC                                     = 1244;
	const s32		_ICODE_LEN                                      = 1245;
	const s32		_ICODE_LIKEC                                    = 1246;
	const s32		_ICODE_LIKE                                     = 1247;
	const s32		_ICODE_LINENO                                   = 1248;
	const s32		_ICODE_LOADPICTURE                              = 1249;
	const s32		_ICODE_LOCFILE                                  = 1250;
	const s32		_ICODE_LOCK                                     = 1251;
	const s32		_ICODE_LOG10                                    = 1252;
	const s32		_ICODE_LOG                                      = 1253;
	const s32		_ICODE_LOOKUP                                   = 1254;
	const s32		_ICODE_LOWER                                    = 1255;
	const s32		_ICODE_LTRIM                                    = 1256;
	const s32		_ICODE_LUPDATE                                  = 1257;
	const s32		_ICODE_MAKETRANSACTABLE                         = 1258;
	const s32		_ICODE_MALP										= 1457;
	const s32		_ICODE_MAX                                      = 1259;
	const s32		_ICODE_MCOL                                     = 1260;
	const s32		_ICODE_MDOWN                                    = 1261;
	const s32		_ICODE_MDX                                      = 1262;
	const s32		_ICODE_MDY                                      = 1263;
	const s32		_ICODE_MICROSECOND								= 1486;
	const s32		_ICODE_MEMLINES                                 = 1264;
	const s32		_ICODE_MEMORY                                   = 1265;
	const s32		_ICODE_MENU                                     = 1266;
	const s32		_ICODE_MESSAGEBOX                               = 1267;
	const s32		_ICODE_MESSAGE                                  = 1268;
	const s32		_ICODE_MINUTE                                   = 1269;
	const s32		_ICODE_MIN                                      = 1270;
	const s32		_ICODE_MLINE                                    = 1271;
	const s32		_ICODE_MOD                                      = 1272;
	const s32		_ICODE_MONTH                                    = 1273;
	const s32		_ICODE_MRKBAR                                   = 1274;
	const s32		_ICODE_MRKPAD                                   = 1275;
	const s32		_ICODE_MROW                                     = 1276;
	const s32		_ICODE_MTON                                     = 1277;
	const s32		_ICODE_MWINDOW                                  = 1278;
	const s32		_ICODE_NANOSECOND								= 1487;
	const s32		_ICODE_NCSET									= 1449;
	const s32		_ICODE_NDX                                      = 1279;
	const s32		_ICODE_NEWOBJECT                                = 1280;
	const s32		_ICODE_NODATA									= 1437;
	const s32		_ICODE_NOLOADPARAMS								= 1443;
	const s32		_ICODE_NOUNLOADPARAMS							= 1445;
	const s32		_ICODE_NOREQUERY								= 1438;
	const s32		_ICODE_NORMALIZE                                = 1281;
	const s32		_ICODE_NOUPDATE									= 1436;
	const s32		_ICODE_NTOM                                     = 1282;
	const s32		_ICODE_NUMLOCK                                  = 1283;
	const s32		_ICODE_NVL                                      = 1284;
	const s32		_ICODE_OBJNUM                                   = 1285;
	const s32		_ICODE_OBJTOCLIENT                              = 1286;
	const s32		_ICODE_OBJVAR                                   = 1287;
	const s32		_ICODE_OCCURSC									= 1431;
	const s32		_ICODE_OCCURS                                   = 1288;
	const s32		_ICODE_OEMTOANSI                                = 1289;
	const s32		_ICODE_OLDVAL                                   = 1290;
	const s32		_ICODE_ON                                       = 1291;
	const s32		_ICODE_ORDER                                    = 1292;
	const s32		_ICODE_OS                                       = 1293;
	const s32		_ICODE_OVERVIEW                                 = 1294;
	const s32		_ICODE_OUTSIDE									= 1480;
	const s32		_ICODE_PADC                                     = 1295;
	const s32		_ICODE_PADL                                     = 1296;
	const s32		_ICODE_PADR                                     = 1297;
	const s32		_ICODE_PAD                                      = 1298;
	const s32		_ICODE_PARAMETERS                               = 1299;
	const s32		_ICODE_PAYMENT                                  = 1300;
	const s32		_ICODE_PCOL                                     = 1301;
	const s32		_ICODE_PCOUNT                                   = 1302;
	const s32		_ICODE_PEMSTATUS                                = 1303;
	const s32		_ICODE_PI                                       = 1304;
	const s32		_ICODE_POPUP                                    = 1305;
	const s32		_ICODE_POW			                            = 1488;
	const s32		_ICODE_PRIMARY                                  = 1306;
	const s32		_ICODE_PRINTSTATUS                              = 1307;
	const s32		_ICODE_PRMBAR                                   = 1308;
	const s32		_ICODE_PRMPAD                                   = 1309;
	const s32		_ICODE_PROGRAM                                  = 1310;
	const s32		_ICODE_PROMPT                                   = 1311;
	const s32		_ICODE_PROPER                                   = 1312;
	const s32		_ICODE_PROW                                     = 1313;
	const s32		_ICODE_PRTINFO                                  = 1314;
	const s32		_ICODE_PUTFILE                                  = 1315;
	const s32		_ICODE_PV                                       = 1316;
	const s32		_ICODE_QUARTER                                  = 1317;
	const s32		_ICODE_RANGER									= 1448;
	const s32		_ICODE_RANGER2									= 1460;
	const s32		_ICODE_RAISEEVENT                               = 1318;
	const s32		_ICODE_RAND                                     = 1319;
	const s32		_ICODE_RATC                                     = 1320;
	const s32		_ICODE_RAT                                      = 1321;
	const s32		_ICODE_RATLINE                                  = 1322;
	const s32		_ICODE_RDLEVEL                                  = 1323;
	const s32		_ICODE_READKEY                                  = 1324;
	const s32		_ICODE_RECCOUNT                                 = 1325;
	const s32		_ICODE_RECNO                                    = 1326;
	const s32		_ICODE_RECSIZE                                  = 1327;
	const s32		_ICODE_RED										= 1456;
	const s32		_ICODE_REFERENCE								= 1519;
	const s32		_ICODE_REFRESH                                  = 1328;
	const s32		_ICODE_RELATION                                 = 1329;
	const s32		_ICODE_REPLICATE                                = 1330;
	const s32		_ICODE_REQUERY                                  = 1331;
	const s32		_ICODE_RGB                                      = 1332;
	const s32		_ICODE_RGBSCHEME                                = 1333;
	const s32		_ICODE_RIGHT                                    = 1334;
	const s32		_ICODE_RIGHTC                                   = 1335;
	const s32		_ICODE_RLOCK                                    = 1336;
	const s32		_ICODE_ROUND                                    = 1337;
	const s32		_ICODE_ROW                                      = 1338;
	const s32		_ICODE_RTOD                                     = 1339;
	const s32		_ICODE_RTRIM                                    = 1340;
	const s32		_ICODE_SAVEPICTURE                              = 1341;
	const s32		_ICODE_SCHEME                                   = 1342;
	const s32		_ICODE_SCOLS                                    = 1343;
	const s32		_ICODE_SECONDS                                  = 1344;
	const s32		_ICODE_SECONDSTOTIME							= 1490;
	const s32		_ICODE_SECONDSTOTIMEX							= 1491;
	const s32		_ICODE_SECONDSX									= 1484;
	const s32		_ICODE_SECONDSXTOTIME							= 1507;
	const s32		_ICODE_SECONDSXTOTIMEX							= 1492;
	const s32		_ICODE_SECONDSTOT								= 1513;
	const s32		_ICODE_SECONDSTOX								= 1514;
	const s32		_ICODE_SECONDSXTOT								= 1515;
	const s32		_ICODE_SECONDSXTOX								= 1516;
	const s32		_ICODE_SEC                                      = 1345;
	const s32		_ICODE_SEEK                                     = 1346;
	const s32		_ICODE_SELECT                                   = 1347;
	const s32		_ICODE_SET                                      = 1348;
	const s32		_ICODE_SETFLDSTATE                              = 1349;
	const s32		_ICODE_SETRESULTSET                             = 1350;
	const s32		_ICODE_SHARED									= 1440;
	const s32		_ICODE_SIGN                                     = 1351;
	const s32		_ICODE_SIN                                      = 1352;
	const s32		_ICODE_SKPBAR                                   = 1353;
	const s32		_ICODE_SKPPAD                                   = 1354;
	const s32		_ICODE_SLICE									= 1467;
	const s32		_ICODE_SOUNDEX                                  = 1355;
	const s32		_ICODE_SPACE                                    = 1356;
	const s32		_ICODE_SQLCANCEL                                = 1357;
	const s32		_ICODE_SQLCOLUMNS                               = 1358;
	const s32		_ICODE_SQLCOMMIT                                = 1359;
	const s32		_ICODE_SQLCONNECT                               = 1360;
	const s32		_ICODE_SQLDISCONNECT                            = 1361;
	const s32		_ICODE_SQLEXEC                                  = 1362;
	const s32		_ICODE_SQLGETPROP                               = 1363;
	const s32		_ICODE_SQLIDLEDISCONNECT                        = 1364;
	const s32		_ICODE_SQLMORERESULTS                           = 1365;
	const s32		_ICODE_SQLPREPARE                               = 1366;
	const s32		_ICODE_SQLROLLBACK                              = 1367;
	const s32		_ICODE_SQLSETPROP                               = 1368;
	const s32		_ICODE_SQLSTRINGCONNECT                         = 1369;
	const s32		_ICODE_SQLTABLES                                = 1370;
	const s32		_ICODE_SQRT                                     = 1371;
	const s32		_ICODE_SROWS                                    = 1372;
	const s32		_ICODE_STARTSWITH								= 1477;
	const s32		_ICODE_STARTSWITHC								= 1479;
	const s32		_ICODE_STRCONV                                  = 1373;
	const s32		_ICODE_STREXTRACT                               = 1374;
	const s32		_ICODE_STRTOFILE                                = 1375;
	const s32		_ICODE_STRTRANC									= 1433;
	const s32		_ICODE_STRTRAN                                  = 1376;
	const s32		_ICODE_STR                                      = 1377;
	const s32		_ICODE_STUFFC                                   = 1378;
	const s32		_ICODE_STUFF                                    = 1379;
	const s32		_ICODE_SUBSTRC                                  = 1380;
	const s32		_ICODE_SUBSTR                                   = 1381;
	const s32		_ICODE_SYSMETRIC                                = 1382;
	const s32		_ICODE_SYS                                      = 1383;
	const s32		_ICODE_SYSTEM									= 2287;
	const s32		_ICODE_TABLEREVERT                              = 1384;
	const s32		_ICODE_TABLEUPDATE                              = 1385;
	const s32		_ICODE_TAG                                      = 1386;
	const s32		_ICODE_TAGCOUNT                                 = 1387;
	const s32		_ICODE_TAGNO                                    = 1388;
	const s32		_ICODE_TAN                                      = 1389;
	const s32		_ICODE_TARGET                                   = 1390;
	const s32		_ICODE_TEXTMERGE                                = 1391;
	const s32		_ICODE_TIME                                     = 1392;
	const s32		_ICODE_TIMETOSECONDS							= 1493;
	const s32		_ICODE_TIMETOSECONDSX							= 1508;
	const s32		_ICODE_TIMETOT									= 1509;
	const s32		_ICODE_TIMETOX									= 1510;
	const s32		_ICODE_TIMEX									= 1485;
	const s32		_ICODE_TIMEXTOSECONDS							= 1494;
	const s32		_ICODE_TIMEXTOSECONDSX							= 1495;
	const s32		_ICODE_TIMEXTOT									= 1511;
	const s32		_ICODE_TIMEXTOX									= 1512;
	const s32		_ICODE_TRANSFORM                                = 1393;
	const s32		_ICODE_TRIM                                     = 1394;
	const s32		_ICODE_TTOC                                     = 1395;
	const s32		_ICODE_TTOD                                     = 1396;
	const s32		_ICODE_TTOSECONDS								= 1496;
	const s32		_ICODE_TTOSECONDSX								= 1497;
	const s32		_ICODE_TTOTIME									= 1498;
	const s32		_ICODE_TTOTIMEX									= 1499;
	const s32		_ICODE_TTOX										= 1500;
	const s32		_ICODE_TXNLEVEL                                 = 1397;
	const s32		_ICODE_TXTWIDTH                                 = 1398;
	const s32		_ICODE_TYPE                                     = 1399;
	const s32		_ICODE_TYPEDETAIL								= 1481;
	const s32		_ICODE_UNBINDEVENTS                             = 1400;
	const s32		_ICODE_UNLOADPARAMS								= 1444;
	const s32		_ICODE_UNIQUE                                   = 1401;
	const s32		_ICODE_UPDATED                                  = 1402;
	const s32		_ICODE_UPPER                                    = 1403;
	const s32		_ICODE_USED                                     = 1404;
	const s32		_ICODE_VAL                                      = 1405;
	const s32		_ICODE_VALUE									= 1520;
	const s32		_ICODE_VARREAD                                  = 1406;
	const s32		_ICODE_VARTYPE                                  = 1407;
	const s32		_ICODE_VEC										= 1461;
	const s32		_ICODE_VECCOUNT									= 1462;
	const s32		_ICODE_VECEL									= 1463;
	const s32		_ICODE_VECSLICE									= 1468;
	const s32		_ICODE_VECSTR									= 1474;
	const s32		_ICODE_VECSTUFF									= 1464;
	const s32		_ICODE_VECSYMBOL								= 1465;
	const s32		_ICODE_VERSION                                  = 1408;
	const s32		_ICODE_WBORDER                                  = 1409;
	const s32		_ICODE_WCHILD                                   = 1410;
	const s32		_ICODE_WCOLS                                    = 1411;
	const s32		_ICODE_WDOCKABLE                                = 1412;
	const s32		_ICODE_WEEK                                     = 1413;
	const s32		_ICODE_WEXIST                                   = 1414;
	const s32		_ICODE_WFONT                                    = 1415;
	const s32		_ICODE_WLAST                                    = 1416;
	const s32		_ICODE_WLCOL                                    = 1417;
	const s32		_ICODE_WLROW                                    = 1418;
	const s32		_ICODE_WMAXIMUM                                 = 1419;
	const s32		_ICODE_WMINIMUM                                 = 1420;
	const s32		_ICODE_WONTOP                                   = 1421;
	const s32		_ICODE_WOUTPUT                                  = 1422;
	const s32		_ICODE_WPARENT                                  = 1423;
	const s32		_ICODE_WREAD                                    = 1424;
	const s32		_ICODE_WROWS                                    = 1425;
	const s32		_ICODE_WTITLE                                   = 1426;
	const s32		_ICODE_WVISIBLE                                 = 1427;
	const s32		_ICODE_XMLTOCURSOR                              = 1428;
	const s32		_ICODE_XMLUPDATEGRAM                            = 1429;
	const s32		_ICODE_XTOD										= 1501;
	const s32		_ICODE_XTOSECONDS								= 1502;
	const s32		_ICODE_XTOSECONDSX								= 1503;
	const s32		_ICODE_XTOT										= 1504;
	const s32		_ICODE_XTOTIME									= 1505;
	const s32		_ICODE_XTOTIMEX									= 1506;
	const s32		_ICODE_YEAR                                     = 1430;
	// Temporary for Rick's testing:
	const s32		_ICODE__TEST									= 999999999;
	// occursc			= 1431				addobject		= 1432
	// strtranc			= 1433				ascending		= 1434
	// in				= 1435				noupdate		= 1436
	// nodata			= 1437				norequery		= 1438
	// again			= 1439				shared			= 1440
	// connstring		= 1441				loadparams		= 1442
	// noloadparams		= 1443				unloadparams	= 1444
	// nounloadparams	= 1445				forcefname		= 1446
	// forcestem		= 1447				ranger			= 1448
	// ncset			= 1449				automatic		= 1450
	// bgr				= 1451				bgra			= 1452
	// alp				= 1453				blu				= 1454
	// grn				= 1455				red				= 1456
	// malp				= 1457				grayscale		= 1458
	// colorize			= 1459				ranger2			= 1460
	// vec				= 1461				veccount		= 1462
	// vecel			= 1463				vecsstuff		= 1464
	// vecsymbol		= 1465				bitslice		= 1466
	// slice			= 1467				vecslice		= 1468
	// bits				= 1469				bits8			= 1470
	// bits16			= 1471				bits32			= 1472
	// bits64			= 1473				vecstr			= 1474
	// bitstr			= 1475				endswith		= 1476
	// startswith		= 1477				endswithc		= 1478
	// startswithc		= 1479				outside			= 1480
	// typedetail		= 1481				dtransform		= 1482
	// datetimex		= 1483				secondsx		= 1484
	// timex			= 1485				microsecond		= 1486
	// nanosecond		= 1487				pow				= 1488
	// dtox				= 1489				secondstotime	= 1490
	// secondstotimex	= 1491				secondsxtotimex	= 1492
	// timetoseconds	= 1493				timextoseconds	= 1494
	// timextosecondsx	= 1495				ttoseconds		= 1496
	// ttosecondsx		= 1497				ttotime			= 1498
	// ttotimex			= 1499				ttox			= 1500
	// xtod				= 1501				xtoseconds		= 1502
	// xtosecondsx		= 1503				xtot			= 1504
	// xtotime			= 1505				xtotimex		= 1506
	// secondsxtotime	= 1507				timetosecondsx	= 1508
	// timetot			= 1509				timetox			= 1510
	// timextot			= 1511				timextox		= 1512
	// secondstot		= 1513				secondstox		= 1514
	// secondsxtot		= 1515				secondsxtox		= 1516
	// dbundle			= 1517				dunbundle		= 1518
	// reference		= 1519				value			= 1520


// Temporarily added until the processing engine is coded
	const s32		_ICODE_CONCATENATE								= 1900;
	const s32       _ICODE_ADD                                      = 1901;
	const s32       _ICODE_SUB                                      = 1902;
	const s32       _ICODE_MUL                                      = 1903;
	const s32       _ICODE_DIV                                      = 1904;

	// Commands
	const s32       _ICODE_ACTIVATE                                 = 2000;
//	const s32       _ICODE_ADD                                      = 2001;
	const s32		_ICODE_ADDITIVE									= 2341;
	const s32		_ICODE_ALL										= 2289;
	const s32       _ICODE_ALTER                                    = 2002;
	const s32       _ICODE_ALTERNATE                                = 2003;
	const s32		_ICODE_AMERICAN									= 2305;
	const s32       _ICODE_ANSI                                     = 2004;
	const s32       _ICODE_APP                                      = 2005;
	const s32       _ICODE_APPEND                                   = 2006;
	const s32       _ICODE_ARRAY                                    = 2007;
	const s32       _ICODE_ASSERTS                                  = 2008;
	const s32       _ICODE_ASSERT                                   = 2009;
	const s32       _ICODE_ASSIST									= 2010;
	const s32		_ICODE_AUTOCONVERT								= 2292;
	const s32       _ICODE_AUTOINCERROR                             = 2011;
	const s32       _ICODE_AUTOSAVE                                 = 2012;
	const s32		_ICODE_AUTOVALIDATE								= 2293;
	const s32       _ICODE_AVERAGE                                  = 2013;
	const s32       _ICODE_BEGIN                                    = 2014;
	const s32       _ICODE_BELL                                     = 2015;
	const s32       _ICODE_BLANK                                    = 2016;
	const s32       _ICODE_BLOCKSIZE                                = 2017;
	const s32       _ICODE_BORDER                                   = 2018;
	const s32       _ICODE_BOX                                      = 2019;
	const s32		_ICODE_BRITISH									= 2317;
	const s32       _ICODE_BROWSE                                   = 2020;
	const s32       _ICODE_BROWSEIME                                = 2021;
	const s32       _ICODE_BRSTATUS                                 = 2022;
	const s32       _ICODE_BUILD                                    = 2023;
	const s32       _ICODE_CALCULATE                                = 2024;
	const s32       _ICODE_CALL                                     = 2025;
	const s32       _ICODE_CANCEL                                   = 2026;
	const s32       _ICODE_CARRY                                    = 2027;
	const s32       _ICODE_CASE                                     = 2028;
	const s32		_ICODE_CASESENSITIVECOMPARES					= 2294;
	const s32		_ICODE_CASESENSITIVENAMES						= 2295;
	const s32       _ICODE_CATCH                                    = 2029;
	const s32       _ICODE_CD                                       = 2030;
	const s32       _ICODE_CENTURY                                  = 2031;
	const s32       _ICODE_CHANGE                                   = 2032;
	const s32       _ICODE_CHDIR                                    = 2033;
	const s32       _ICODE_CLASS                                    = 2034;
	const s32       _ICODE_CLASSLIB                                 = 2035;
	const s32       _ICODE_CLEAR                                    = 2036;
	const s32       _ICODE_CLEARS                                   = 2037;
	const s32       _ICODE_CLOCK                                    = 2038;
	const s32       _ICODE_CLOSE                                    = 2039;
	const s32       _ICODE_CLOSES                                   = 2040;
	const s32       _ICODE_COLLATE                                  = 2041;
	const s32       _ICODE_COLOR                                    = 2042;
	const s32       _ICODE_COMPATIBLE                               = 2043;
	const s32       _ICODE_COMPILE                                  = 2044;
	const s32       _ICODE_CONFIRM                                  = 2045;
	const s32       _ICODE_CONNECTION                               = 2046;
	const s32       _ICODE_CONNECTIONS                              = 2047;
	const s32       _ICODE_CONSOLE                                  = 2048;
	const s32       _ICODE_CONTINUE                                 = 2049;
	const s32       _ICODE_COPY                                     = 2050;
	const s32       _ICODE_COUNT                                    = 2051;
	const s32       _ICODE_COVERAGE                                 = 2052;
	const s32       _ICODE_CPCOMPILE                                = 2053;
	const s32       _ICODE_CPDIALOG                                 = 2054;
	const s32       _ICODE_CREATE                                   = 2055;
	const s32       _ICODE_CURRENCY                                 = 2056;
	const s32       _ICODE_CURSOR                                   = 2057;
	const s32       _ICODE_DATABASE                                 = 2058;
	const s32       _ICODE_DATASESSION                              = 2059;
	const s32       _ICODE_DEACTIVATE                               = 2060;
	const s32       _ICODE_DEBUG                                    = 2061;
	const s32       _ICODE_DEBUGOUT                                 = 2062;
	const s32       _ICODE_DECIMALS                                 = 2063;
	const s32       _ICODE_DECLARE                                  = 2064;
	const s32       _ICODE_DEFAULT                                  = 2065;
	const s32       _ICODE_DELETE                                   = 2066;
	const s32       _ICODE_DELIMITERS                               = 2067;
	const s32       _ICODE_DEVELOPMENT                              = 2068;
	const s32       _ICODE_DEVICE                                   = 2069;
	const s32		_ICODE_DEVICE_FILENAME							= 2340;
	const s32       _ICODE_DIMENSION                                = 2070;
	const s32       _ICODE_DIR                                      = 2071;
	const s32       _ICODE_DISPLAY                                  = 2072;
	const s32       _ICODE_DLLS                                     = 2073;
	const s32       _ICODE_DLL                                      = 2074;
	const s32       _ICODE_DO                                       = 2075;
	const s32       _ICODE_DOCASE                                   = 2272;
	const s32       _ICODE_DOFORM                                   = 2273;
	const s32       _ICODE_DOPROGRAM                                = 2274;
	const s32       _ICODE_DOWHILE                                  = 2275;
	const s32       _ICODE_DOCK                                     = 2076;
	const s32       _ICODE_DOEVENTS                                 = 2077;
	const s32       _ICODE_DOHISTORY                                = 2078;
	const s32       _ICODE_DROP                                     = 2079;
	const s32       _ICODE_EACH                                     = 2080;
	const s32       _ICODE_ECHO                                     = 2081;
	const s32       _ICODE_EDIT                                     = 2082;
	const s32       _ICODE_EJECT                                    = 2083;
	const s32		_ICODE_ELSE										= 2280;
	const s32       _ICODE_END                                      = 2084;
	const s32       _ICODE_ENDCASE                                  = 2085;
	const s32       _ICODE_ENDDO                                    = 2086;
	const s32       _ICODE_ENDFOR                                   = 2087;
	const s32		_ICODE_ENDFUNCTION								= 2276;
	const s32       _ICODE_ENDIF                                    = 2088;
	const s32       _ICODE_ENDPRINTJOB                              = 2089;
	const s32		_ICODE_ENDPROCEDURE								= 2277;
	const s32       _ICODE_ENDSCAN                                  = 2090;
	const s32       _ICODE_ENDTEXT                                  = 2091;
	const s32       _ICODE_ENDWITH                                  = 2092;
	const s32       _ICODE_ENGINEBEHAVIOR                           = 2093;
	const s32       _ICODE_ERASE                                    = 2094;
	const s32       _ICODE_ESCAPE                                   = 2095;
	const s32       _ICODE_EVENTLIST                                = 2096;
	const s32       _ICODE_EVENTS                                   = 2097;
	const s32       _ICODE_EVENTTRACKING                            = 2098;
	const s32       _ICODE_EXACT                                    = 2099;
	const s32       _ICODE_EXCLUSIVE                                = 2100;
	const s32       _ICODE_EXE                                      = 2101;
	const s32       _ICODE_EXIT                                     = 2102;
	const s32       _ICODE_EXPORT                                   = 2103;
	const s32       _ICODE_EXTENDED                                 = 2104;
	const s32       _ICODE_EXTERNAL                                 = 2105;
	const s32       _ICODE_FDOW                                     = 2106;
	const s32		_ICODE_FELSEIF									= 2283;
	const s32       _ICODE_FIELDS                                   = 2107;
	const s32		_ICODE_FIF										= 2284;
	const s32       _ICODE_FILES                                    = 2108;
	const s32       _ICODE_FILL                                     = 2109;
	const s32       _ICODE_FINALLY                                  = 2110;
	const s32       _ICODE_FIND                                     = 2111;
	const s32       _ICODE_FIXED                                    = 2112;
	const s32       _ICODE_FLUSH                                    = 2113;
	const s32		_ICODE_FOCUSHIGHLIGHTBORDERPIXELS				= 2296;
	const s32		_ICODE_FOCUSHIGHLIGHTPIXELS						= 2297;
	const s32       _ICODE_FORMAT                                   = 2114;
	const s32       _ICODE_FORM                                     = 2115;
	const s32       _ICODE_FREE                                     = 2116;
	const s32		_ICODE_FRENCH									= 2318;
	const s32       _ICODE_FROM                                     = 2117;
	const s32       _ICODE_FUNCTION                                 = 2118;
	const s32       _ICODE_FWEEK                                    = 2119;
	const s32       _ICODE_GATHER                                   = 2120;
	const s32       _ICODE_GENERAL                                  = 2121;
	const s32		_ICODE_GERMAN									= 2319;
	const s32       _ICODE_GETEXPR                                  = 2122;
	const s32       _ICODE_GETS                                     = 2123;
	const s32       _ICODE_GET                                      = 2124;
	const s32       _ICODE_GO                                       = 2125;
	const s32       _ICODE_GOTO                                     = 2126;
	const s32       _ICODE_HEADINGS                                 = 2127;
	const s32       _ICODE_HELP                                     = 2128;
	const s32       _ICODE_HIDE                                     = 2129;
	const s32		_ICODE_HONORBARRIERS							= 2298;
	const s32       _ICODE_HOURS                                    = 2130;
	const s32       _ICODE_ID                                       = 2131;
	const s32       _ICODE_IF                                       = 2132;
	const s32		_ICODE_IMPLICITPARAMS							= 2299;
	const s32       _ICODE_IMPORT                                   = 2133;
	const s32       _ICODE_INDEXES                                  = 2134;
	const s32       _ICODE_INDEX                                    = 2135;
	const s32		_ICODE_INDEXMETADATA							= 2300;
	const s32		_ICODE_INITIALIZEDEFAULTVALUE					= 2301;
	const s32       _ICODE_INPUT                                    = 2136;
	const s32       _ICODE_INSERT                                   = 2137;
	const s32       _ICODE_INTENSITY                                = 2138;
	const s32		_ICODE_ITALIAN									= 2320;
	const s32		_ICODE_JAPAN									= 2321;
	const s32       _ICODE_JOIN                                     = 2139;
	const s32		_ICODE_JOURNAL									= 2336;
	const s32		_ICODE_KEEP										= 2291;
	const s32       _ICODE_KEYBOARD                                 = 2140;
	const s32       _ICODE_KEYCOMP                                  = 2141;
	const s32       _ICODE_LABEL                                    = 2142;
	const s32		_ICODE_LANGUAGE									= 2302;
	const s32		_ICODE_LAST										= 2327;
	const s32		_ICODE_LELSE									= 2281;
	const s32		_ICODE_LELSEIF									= 2282;
	const s32       _ICODE_LIBRARY                                  = 2143;
	const s32		_ICODE_LIF										= 2279;
	const s32       _ICODE_LISTS                                    = 2144;
	const s32       _ICODE_LIST                                     = 2145;
	const s32       _ICODE_LOAD                                     = 2146;
	const s32		_ICODE_LOAD_RECEIVES_PARAMS						= 2303;
	const s32       _ICODE_LOCAL                                    = 2147;
	const s32       _ICODE_LOCATE                                   = 2148;
	const s32		_ICODE_LOCKSCREEN								= 2304;
	const s32       _ICODE_LOGERRORS                                = 2149;
	const s32       _ICODE_LOOP                                     = 2150;
	const s32		_ICODE_LONG										= 2332;
	const s32       _ICODE_LPARAMETERS                              = 2151;
	const s32       _ICODE_MACKEY                                   = 2152;
	const s32       _ICODE_MACROS                                   = 2153;
	const s32       _ICODE_MACRO                                    = 2154;
	const s32       _ICODE_MARGIN                                   = 2155;
	const s32       _ICODE_MARK                                     = 2156;
	const s32       _ICODE_MD                                       = 2157;
	const s32       _ICODE_MEMOWIDTH                                = 2158;
	const s32       _ICODE_MEMO                                     = 2159;
	const s32       _ICODE_MENUS                                    = 2160;
	const s32       _ICODE_MKDIR                                    = 2161;
	const s32       _ICODE_MODIFY                                   = 2162;
	const s32       _ICODE_MOUSE                                    = 2163;
	const s32       _ICODE_MOVE                                     = 2164;
	const s32       _ICODE_MTDLL                                    = 2165;
	const s32       _ICODE_MULTILOCKS                               = 2166;
	const s32		_ICODE_NAMINGCONVENTIONS						= 2306;
	const s32		_ICODE_NCSETALPHAISOPAQUE						= 2325;
	const s32		_ICODE_NCSETCEILINGFLOOR						= 2307;
	const s32		_ICODE_NCSETDATETIMEMILLISECONDS				= 2337;
	const s32		_ICODE_NCSETOPTIMIZETABLEWRITES					= 2326;
	const s32		_ICODE_NCSETOPTIMIZEVARIABLES					= 2328;
	const s32		_ICODE_NCSETSIGNSIGN2							= 2308;
	const s32       _ICODE_NEAR                                     = 2167;
// 	const s32       _ICODE_NEXT                                     = 2168;
	const s32       _ICODE_NOCPTRANS                                = 2169;
	const s32       _ICODE_NOTE                                     = 2170;
	const s32       _ICODE_NOTIFY                                   = 2171;
	const s32       _ICODE_NULL                                     = 2172;
	const s32       _ICODE_NULLDISPLAY                              = 2173;
	const s32       _ICODE_OBJECTS                                  = 2174;
	const s32       _ICODE_OBJECT                                   = 2175;
	const s32       _ICODE_ODOMETER                                 = 2176;
	const s32       _ICODE_OFF                                      = 2177;
	const s32       _ICODE_OF                                       = 2178;
	const s32       _ICODE_OLEOBJECT                                = 2179;
	const s32       _ICODE_OPEN                                     = 2180;
	const s32       _ICODE_OPTIMIZE                                 = 2181;
//	const s32       _ICODE_OR                                       = 2182;
	const s32       _ICODE_PACK                                     = 2183;
	const s32       _ICODE_PAGE                                     = 2184;
	const s32       _ICODE_PALETTE                                  = 2185;
	const s32       _ICODE_PATH                                     = 2186;
	const s32       _ICODE_PDSETUP                                  = 2187;
	const s32       _ICODE_PLAY                                     = 2188;
	const s32       _ICODE_POINT                                    = 2189;
	const s32       _ICODE_POP                                      = 2190;
	const s32       _ICODE_POPUPS                                   = 2191;
	const s32		_ICODE_PRECISIONSBFP							= 2338;
	const s32		_ICODE_PRECISIONSBI								= 2339;
	const s32       _ICODE_PRINTER                                  = 2192;
	const s32       _ICODE_PRINTJOB                                 = 2193;
	const s32       _ICODE_PRIVATE                                  = 2194;
	const s32       _ICODE_PROCEDURES                               = 2195;
	const s32       _ICODE_PROCEDURE                                = 2196;
	const s32       _ICODE_PROJECT                                  = 2197;
	const s32       _ICODE_PUBLIC                                   = 2198;
	const s32       _ICODE_PUSH                                     = 2199;
	const s32       _ICODE_QUERY                                    = 2200;
	const s32       _ICODE_QUIT                                     = 2201;
	const s32       _ICODE_RD                                       = 2202;
	const s32       _ICODE_READ                                     = 2203;
	const s32       _ICODE_READBORDER                               = 2204;
	const s32       _ICODE_READERROR                                = 2205;
	const s32       _ICODE_RECALL                                   = 2206;
	const s32		_ICODE_RECOVER									= 2288;
	const s32       _ICODE_REINDEX                                  = 2207;
	const s32       _ICODE_RELEASE                                  = 2208;
	const s32       _ICODE_REMOVE                                   = 2209;
	const s32       _ICODE_RENAME                                   = 2210;
	const s32       _ICODE_REPLACE                                  = 2211;
	const s32       _ICODE_REPORT                                   = 2212;
	const s32       _ICODE_REPROCESS                                = 2213;
	const s32		_ICODE_REPROCESSATTEMPTS						= 2286;
	const s32		_ICODE_REPROCESSINTERVAL						= 2309;
	const s32		_ICODE_REPROCESSSYSTEM							= 2310;
	const s32       _ICODE_RESOURCE                                 = 2214;
	const s32		_ICODE_RESOURCES								= 2290;
	const s32       _ICODE_RESTORE                                  = 2215;
	const s32       _ICODE_RESUME                                   = 2216;
	const s32       _ICODE_RETRY                                    = 2217;
	const s32       _ICODE_RETURN                                   = 2218;
	const s32       _ICODE_RMDIR                                    = 2219;
	const s32       _ICODE_ROLLBACK                                 = 2220;
	const s32       _ICODE_RUN                                      = 2221;
	const s32       _ICODE_SAFETY                                   = 2222;
	const s32       _ICODE_SAVE                                     = 2223;
	const s32       _ICODE_SAY                                      = 2224;
	const s32       _ICODE_SCAN                                     = 2225;
	const s32       _ICODE_SCATTER                                  = 2226;
	const s32       _ICODE_SCREEN                                   = 2227;
	const s32       _ICODE_SCROLL                                   = 2228;
	const s32       _ICODE_SELECTION                                = 2229;
	const s32       _ICODE_SEPARATOR                                = 2230;
	const s32		_ICODE_SHORT									= 2333;
	const s32       _ICODE_SHOW                                     = 2231;
	const s32       _ICODE_SHUTDOWN                                 = 2232;
	const s32       _ICODE_SIZE                                     = 2233;
	const s32       _ICODE_SKIP                                     = 2234;
	const s32		_ICODE_SLOPPYPRINTING							= 2311;
	const s32       _ICODE_SORT                                     = 2235;
	const s32       _ICODE_SQL                                      = 2236;
	const s32       _ICODE_STATUS                                   = 2237;
	const s32       _ICODE_STEP                                     = 2238;
	const s32		_ICODE_STICKYPARAMETERS							= 2312;
	const s32       _ICODE_STORE                                    = 2239;
	const s32       _ICODE_STRICTDATE                               = 2240;
	const s32       _ICODE_STRUCTURE                                = 2241;
	const s32       _ICODE_SUM                                      = 2242;
	const s32       _ICODE_SUSPEND                                  = 2243;
	const s32       _ICODE_SYSFORMATS                               = 2244;
	const s32       _ICODE_SYSMENU                                  = 2245;
	const s32		_ICODE_TABLEEQUALASSIGNMENTS					= 2313;
	const s32		_ICODE_TABLEOBJECTS								= 2314;
	const s32       _ICODE_TABLEVALIDATE                            = 2246;
	const s32       _ICODE_TABLES                                   = 2247;
	const s32       _ICODE_TABLE                                    = 2248;
	const s32		_ICODE_TAIWAN									= 2322;
	const s32       _ICODE_TALK                                     = 2249;
	const s32       _ICODE_TEXT                                     = 2250;
	const s32		_ICODE_TF										= 2329;
	const s32       _ICODE_TO                                       = 2251;
	const s32       _ICODE_TOPIC                                    = 2252;
	const s32       _ICODE_TOTAL                                    = 2253;
	const s32       _ICODE_TRANSACTION                              = 2254;
	const s32       _ICODE_TRBETWEEN                                = 2255;
	const s32       _ICODE_TRIGGER                                  = 2256;
	const s32       _ICODE_TRY                                      = 2257;
	const s32       _ICODE_TYPEAHEAD                                = 2258;
	const s32		_ICODE_UD										= 2330;
	const s32       _ICODE_UDFPARMS                                 = 2259;
	const s32		_ICODE_UNLOADRECEIVESPARAMS						= 2315;
	const s32       _ICODE_UNLOCK                                   = 2260;
	const s32       _ICODE_UPDATE                                   = 2261;
	const s32		_ICODE_USA										= 2323;
	const s32       _ICODE_USE                                      = 2262;
	const s32       _ICODE_VALIDATE                                 = 2263;
	const s32		_ICODE_VARIABLESFIRST							= 2316;
	const s32		_ICODE_VECSEPARATOR								= 2334;
	const s32       _ICODE_VIEWS                                    = 2264;
	const s32       _ICODE_VIEW                                     = 2265;
	const s32		_ICODE_VISUALIZE								= 2335;
	const s32       _ICODE_WAIT                                     = 2266;
	const s32       _ICODE_WHILE                                    = 2267;
	const s32       _ICODE_WINDOWS                                  = 2268;
	const s32       _ICODE_WINDOW                                   = 2269;
	const s32       _ICODE_WITH                                     = 2270;
	const s32		_ICODE_YMD										= 2324;
	const s32		_ICODE_YN										= 2331;
	const s32       _ICODE_ZAP                                      = 2271;
	// DOCASE				= 2272			DOFORM					= 2273
	// DOPROGRAM			= 2274			DOWHILE					= 2275
	// ENDFUNCTION			= 2276			ENDPROCEDURE			= 2277
	// LELSE				= 2278			LIF						= 2279
	// ELSE					= 2280			LESLE					= 2281
	// LESLEIF				= 2282			FELSEIF					= 2283
	// FIF					= 2284			ROLL					= 2285
	// REPROCESSATTEMPTS	= 2286			SYSTEM					= 2287
	// RECOVER				= 2288			ALL						= 2289
	// RESOURCES			= 2290			KEEP					= 2291
	// AUTOCONVERT			= 2292			AUTOVALIDATE			= 2293
	// CASESENSITIVECOMPARES = 2294			CASESENSITIVENAMES		= 2295
	// FOCUSHIGHLIGHTBORDERPIXELS = 2296	FOCUSHIGHLIGHTPIXELS	= 2297
	// HONORBARRIERS		= 2298			IMPLICITPARAMS			= 2299
	// INDEXMETADATA		= 2300			INITIALIZEDEFAULTVALUE	= 2301
	// LANGUAGE				= 2302			LOAD_RECEIVES_PARAMS	= 2303
	// LOCKSCREEN			= 2304			AMERICAN				= 2305
	// NAMINGCONVENTIONS	= 2306			NCSETCEILINGFLOOR		= 2307
	// NCSETSIGNSIGN2		= 2308			REPROCESSINTERVAL		= 2309
	// REPROCESSSYSTEM		= 2310			SLOPPYPRINTING			= 2311
	// STICKYPARAMETERS		= 2312			TABLEEQUALASSIGNMENTS	= 2313
	// TABLEOBJECTS			= 2314			UNLOADRECEIVESPARAMS	= 2315
	// VARIABLESFIRST		= 2316			BRITISH					= 2317
	// FRENCH				= 2318			GERMAN					= 2319
	// ITALIAN				= 2320			JAPAN					= 2321
	// TAIWAN				= 2322			USA						= 2323
	// YMD					= 2324			NCSETALPHAISOPAQUE		= 2325
	// NCSETOPTIMIZETABLEWRITES = 2326		LAST					= 2327
	// NCSETOPTIMIZEVARIABLES = 2328		TF						= 2329
	// UD					= 2330			YN						= 2331
	// LONG					= 2332			SHORT					= 2333
	// vecseparator			= 2334			visualize				= 2335
	// journal				= 2336			NCSETDATETIMEMILLISECONDS = 2337
	// PRECISIONSBFP		= 2338			PRECISIONSBI			= 2339
	// DEVICE_FILENAME		= 2340			ADDITIVE				= 2341


//////////
// VXB iCat codes
//////
	const s32		_ICAT_DOT_VARIABLE								= 100;// The . in thisForm.xyz
	const s32		_ICAT_EXCLAMATION_POINT_VARIABLE				= 101;// The ! in thisForm!xyz


//////////
// Symbols in token parsing
//////
	const s8		cgcBackslash[]									= "\\";
	const s8		cgcSlash[]										= "/";
	const s8		cgcS[]											= "S";
	const s8		cgcNullString[]									= "";
	const s8		cgcPseudoFunctionName[]							= "__top_of_code_block";
	const s8		cgcNullText[]									= ".NULL.";
	const s8		cgcObjectText[]									= "(object)";
	const s8		cgcThisCodeText[]								= "(thisCode)";
// 	const s8		cgcTText[]										= ".T.";
// 	const s8		cgcFText[]										= ".F.";
// 	const s8		cgcYText[]										= ".Y.";
// 	const s8		cgcNText[]										= ".N.";
// 	const s8		cgcUText[]										= ".U.";
// 	const s8		cgcDText[]										= ".D.";
// 	const s8		cgcOxText[]										= ".o.";// Other
// 	const s8		cgcPxText[]										= ".p.";// Partial
// 	const s8		cgcYxText[]										= ".y.";// Yet another
// 	const s8		cgcZxText[]										= ".z.";// Zat's all folks! :-)
	const s8		cgcBigInteger[]									= "(BigInteger)";
	const s8		cgcBigFloatingPoint[]							= "(BigFloatingPoint)";
	const s8		cgcPasswordCharText[]							= "o";

	const s8		cgc_textmerge_leftDelim[]						= "<<";
	const s8		cgc_textmerge_rightDelim[]						= ">>";

	const s8		cgc_asterisk[]									= "*";
	const s8		cgc_ampersandComment[]							= "&&";
	const s8		cgc_dollarSign[]								= "$";
	const s8		cgc_notFoundIn[]								= "!$";
	const s8		cgc_notEqual1[]									= "#";
	const s8		cgc_notEqual2[]									= "!=";

	const s8		cgc_abs[]										= "abs";
	const s8		cgc_aclass[]									= "aclass";
	const s8		cgc_acopy[]										= "acopy";
	const s8		cgc_acos[]										= "acos";
	const s8		cgc_adatabases[]								= "adatabases";
	const s8		cgc_adbobjects[]								= "adbobjects";
	const s8		cgc_addbs[]										= "addbs";
	const s8		cgc_addobject[]									= "addobject";
	const s8		cgc_addproperty[]								= "addproperty";
	const s8		cgc_adel[]										= "adel";
	const s8		cgc_adir[]										= "adir";
	const s8		cgc_adlls[]										= "adlls";
	const s8		cgc_adockstate[]								= "adockstate";
	const s8		cgc_aelement[]									= "aelement";
	const s8		cgc_aerror[]									= "aerror";
	const s8		cgc_aevents[]									= "aevents";
	const s8		cgc_afields[]									= "afields";
	const s8		cgc_afont[]										= "afont";
	const s8		cgc_again[]										= "again";
	const s8		cgc_agetclass[]									= "agetclass";
	const s8		cgc_agetfileversion[]							= "agetfileversion";
	const s8		cgc_ainstance[]									= "ainstance";
	const s8		cgc_ains[]										= "ains";
	const s8		cgc_alanguage[]									= "alanguage";
	const s8		cgc_alen[]										= "alen";
	const s8		cgc_alias[]										= "alias";
	const s8		cgc_alines[]									= "alines";
	const s8		cgc_alltrim[]									= "alltrim";
	const s8		cgc_alp[]										= "alp";
	const s8		cgc_amembers[]									= "amembers";
	const s8		cgc_amouseobj[]									= "amouseobj";
	const s8		cgc_anetresources[]								= "anetresources";
	const s8		cgc_aprinters[]									= "aprinters";
	const s8		cgc_aprocinfo[]									= "aprocinfo";
	const s8		cgc_ascan[]										= "ascan";
	const s8		cgc_asc[]										= "asc";
	const s8		cgc_ascending[]									= "ascending";
	const s8		cgc_aselobj[]									= "aselobj";
	const s8		cgc_asessions[]									= "asessions";
	const s8		cgc_asin[]										= "asin";
	const s8		cgc_asort[]										= "asort";
	const s8		cgc_asqlhandles[]								= "asqlhandles";
	const s8		cgc_astackinfo[]								= "astackinfo";
	const s8		cgc_asubscript[]								= "asubscript";
	const s8		cgc_at_c[]										= "at_c";
	const s8		cgc_at[]										= "at";
	const s8		cgc_ataginfo[]									= "ataginfo";
	const s8		cgc_atan[]										= "atan";
	const s8		cgc_atcline[]									= "atcline";
	const s8		cgc_atcc[]										= "atcc";
	const s8		cgc_atc[]										= "atc";
	const s8		cgc_atline[]									= "atline";
	const s8		cgc_atn2[]										= "atn2";
	const s8		cgc_aused[]										= "aused";
	const s8		cgc_avcxclasses[]								= "avcxclasses";
	const s8		cgc_barprompt[]									= "barprompt";
	const s8		cgc_barcount[]									= "barcount";
	const s8		cgc_bar[]										= "bar";
	const s8		cgc_between[]									= "between";
	const s8		cgc_bgr[]										= "bgr";
	const s8		cgc_bgra[]										= "bgra";
	const s8		cgc_bindevent[]									= "bindevent";
	const s8		cgc_bintoc[]									= "bintoc";
	const s8		cgc_bitand[]									= "bitand";
	const s8		cgc_bitclear[]									= "bitclear";
	const s8		cgc_bitlshift[]									= "bitlshift";
	const s8		cgc_bitnot[]									= "bitnot";
	const s8		cgc_bitor[]										= "bitor";
	const s8		cgc_bitrshift[]									= "bitrshift";
	const s8		cgc_bitset[]									= "bitset";
	const s8		cgc_bittest[]									= "bittest";
	const s8		cgc_bits[]										= "bits";
	const s8		cgc_bits8[]										= "bits8";
	const s8		cgc_bits16[]									= "bits16";
	const s8		cgc_bits32[]									= "bits32";
	const s8		cgc_bits64[]									= "bits64";
	const s8		cgc_bitslice[]									= "bitslice";
	const s8		cgc_bitstr[]									= "bitstr";
	const s8		cgc_bitxor[]									= "bitxor";
	const s8		cgc_blu[]										= "blu";
	const s8		cgc_bof[]										= "bof";
	const s8		cgc_candidate[]									= "candidate";
	const s8		cgc_capslock[]									= "capslock";
	const s8		cgc_cast[]										= "cast";
	const s8		cgc_cdow[]										= "cdow";
	const s8		cgc_cdx[]										= "cdx";
	const s8		cgc_ceiling[]									= "ceiling";
	const s8		cgc_chr[]										= "chr";
	const s8		cgc_chrsaw[]									= "chrsaw";
	const s8		cgc_chrtranc[]									= "chrtranc";
	const s8		cgc_chrtran[]									= "chrtran";
	const s8		cgc_clearresultset[]							= "clearresultset";
	const s8		cgc_cmonth[]									= "cmonth";
	const s8		cgc_cntbar[]									= "cntbar";
	const s8		cgc_cntpad[]									= "cntpad";
	const s8		cgc_col[]										= "col";
	const s8		cgc_colorize[]									= "cgc_colorize";
	const s8		cgc_comarray[]									= "comarray";
	const s8		cgc_comclassinfo[]								= "comclassinfo";
	const s8		cgc_command[]									= "command";
	const s8		cgc_compobj[]									= "compobj";
	const s8		cgc_comprop[]									= "comprop";
	const s8		cgc_comreturnerror[]							= "comreturnerror";
	const s8		cgc_coms[]										= "coms";
	const s8		cgc_connstring[]								= "connstring";
	const s8		cgc_cos[]										= "cos";
	const s8		cgc_cpconvert[]									= "cpconvert";
	const s8		cgc_cpcurrent[]									= "cpcurrent";
	const s8		cgc_cpdbf[]										= "cpdbf";
	const s8		cgc_createbinary[]								= "createbinary";
	const s8		cgc_createobject[]								= "createobject";
	const s8		cgc_createobjectex[]							= "createobjectex";
	const s8		cgc_createoffline[]								= "createoffline";
	const s8		cgc_ctobin[]									= "ctobin";
	const s8		cgc_ctod[]										= "ctod";
	const s8		cgc_ctot[]										= "ctot";
	const s8		cgc_curdir[]									= "curdir";
	const s8		cgc_cursorgetprop[]								= "cursorgetprop";
	const s8		cgc_cursorsetprop[]								= "cursorsetprop";
	const s8		cgc_cursortoxml[]								= "cursortoxml";
	const s8		cgc_curval[]									= "curval";
	const s8		cgc_datetime[]									= "datetime";
	const s8		cgc_datetimex[]									= "datetimex";
	const s8		cgc_date[]										= "date";
	const s8		cgc_day[]										= "day";
	const s8		cgc_dbc[]										= "dbc";
	const s8		cgc_dbf[]										= "dbf";
	const s8		cgc_dbgetprop[]									= "dbgetprop";
	const s8		cgc_dbsetprop[]									= "dbsetprop";
	const s8		cgc_dbundle[]									= "dbundle";
	const s8		cgc_dbused[]									= "dbused";
	const s8		cgc_ddeaborttrans[]								= "ddeaborttrans";
	const s8		cgc_ddeadvise[]									= "ddeadvise";
	const s8		cgc_ddeenabled[]								= "ddeenabled";
	const s8		cgc_ddeexecute[]								= "ddeexecute";
	const s8		cgc_ddeinitiate[]								= "ddeinitiate";
	const s8		cgc_ddelasterror[]								= "ddelasterror";
	const s8		cgc_ddepoke[]									= "ddepoke";
	const s8		cgc_dderequest[]								= "dderequest";
	const s8		cgc_ddes[]										= "ddes";
	const s8		cgc_ddesetoption[]								= "ddesetoption";
	const s8		cgc_ddesetservice[]								= "ddesetservice";
	const s8		cgc_ddesettopic[]								= "ddesettopic";
	const s8		cgc_ddeterminate[]								= "ddeterminate";
	const s8		cgc_defaultext[]								= "defaultext";
	const s8		cgc_deleted[]									= "deleted";
	const s8		cgc_descending[]								= "descending";
	const s8		cgc_difference[]								= "difference";
	const s8		cgc_directory[]									= "directory";
	const s8		cgc_diskspace[]									= "diskspace";
	const s8		cgc_displaypath[]								= "displaypath";
	const s8		cgc_dmy[]										= "dmy";
	const s8		cgc_dodefault[]									= "dodefault";
	const s8		cgc_dow[]										= "dow";
	const s8		cgc_drivetype[]									= "drivetype";
	const s8		cgc_dropoffline[]								= "dropoffline";
	const s8		cgc_dtoc[]										= "dtoc";
	const s8		cgc_dtor[]										= "dtor";
	const s8		cgc_dtos[]										= "dtos";
	const s8		cgc_dtot[]										= "dtot";
	const s8		cgc_dtox[]										= "dtox";
	const s8		cgc_dtransform[]								= "dtransform";
	const s8		cgc_dunbundle[]									= "dunbundle";
	const s8		cgc_editsource[]								= "editsource";
	const s8		cgc_empty[]										= "empty";
	const s8		cgc_endswith[]									= "endswith";
	const s8		cgc_endswithc[]									= "endswithc";
	const s8		cgc_eof[]										= "eof";
	const s8		cgc_error[]										= "error";
	const s8		cgc_evaluate[]									= "evaluate";
	const s8		cgc_eventhandler[]								= "eventhandler";
	const s8		cgc_evl[]										= "evl";
	const s8		cgc_execscript[]								= "execscript";
	const s8		cgc_exp[]										= "exp";
	const s8		cgc_fchsize[]									= "fchsize";
	const s8		cgc_fclose[]									= "fclose";
	const s8		cgc_fcount[]									= "fcount";
	const s8		cgc_fcreate[]									= "fcreate";
	const s8		cgc_fdate[]										= "fdate";
	const s8		cgc_feof[]										= "feof";
	const s8		cgc_ferror[]									= "ferror";
	const s8		cgc_fflush[]									= "fflush";
	const s8		cgc_fgets[]										= "fgets";
	const s8		cgc_field[]										= "field";
	const s8		cgc_filetostr[]									= "filetostr";
	const s8		cgc_file[]										= "file";
	const s8		cgc_filter[]									= "filter";
	const s8		cgc_fklabel[]									= "fklabel";
	const s8		cgc_fkmax[]										= "fkmax";
	const s8		cgc_fldlist[]									= "fldlist";
	const s8		cgc_flock[]										= "flock";
	const s8		cgc_floor[]										= "floor";
	const s8		cgc_fontmetric[]								= "fontmetric";
	const s8		cgc_fopen[]										= "fopen";
//	const s8		cgc_for[]										= "for";
	const s8		cgc_forceext[]									= "forceext";
	const s8		cgc_forcefname[]								= "forcefname";
	const s8		cgc_forcepath[]									= "forcepath";
	const s8		cgc_forcestem[]									= "forcestem";
	const s8		cgc_found[]										= "found";
	const s8		cgc_fputs[]										= "fputs";
	const s8		cgc_fread[]										= "fread";
	const s8		cgc_fseek[]										= "fseek";
	const s8		cgc_fsize[]										= "fsize";
	const s8		cgc_ftime[]										= "ftime";
	const s8		cgc_fullpath[]									= "fullpath";
	const s8		cgc_fv[]										= "fv";
	const s8		cgc_fwrite[]									= "fwrite";
	const s8		cgc_getautoincvalue[]							= "getautoincvalue";
	const s8		cgc_getbar[]									= "getbar";
	const s8		cgc_getcolor[]									= "getcolor";
	const s8		cgc_getcp[]										= "getcp";
	const s8		cgc_getcursoradapter[]							= "getcursoradapter";
	const s8		cgc_getdir[]									= "getdir";
	const s8		cgc_getenv[]									= "getenv";
	const s8		cgc_getfile[]									= "getfile";
	const s8		cgc_getfldstate[]								= "getfldstate";
	const s8		cgc_getfont[]									= "getfont";
	const s8		cgc_getinterface[]								= "getinterface";
	const s8		cgc_getnextmodified[]							= "getnextmodified";
	const s8		cgc_getobject[]									= "getobject";
	const s8		cgc_getpad[]									= "getpad";
	const s8		cgc_getpem[]									= "getpem";
	const s8		cgc_getpict[]									= "getpict";
	const s8		cgc_getprinter[]								= "getprinter";
	const s8		cgc_getresultset[]								= "getresultset";
	const s8		cgc_getwordcount[]								= "getwordcount";
	const s8		cgc_getwordnum[]								= "getwordnum";
	const s8		cgc_gomonth[]									= "gomonth";
	const s8		cgc_grayscale[]									= "grayscale";
	const s8		cgc_grn[]										= "grn";
	const s8		cgc_header[]									= "header";
	const s8		cgc_home[]										= "home";
	const s8		cgc_hour[]										= "hour";
	const s8		cgc_icase[]										= "icase";
	const s8		cgc_idxcollate[]								= "idxcollate";
	const s8		cgc_iif[]										= "iif";
	const s8		cgc_imestatus[]									= "imestatus";
	const s8		cgc_in[]										= "in";
	const s8		cgc_indbc[]										= "indbc";
	const s8		cgc_indexseek[]									= "indexseek";
	const s8		cgc_inkey[]										= "inkey";
	const s8		cgc_inlist[]									= "inlist";
	const s8		cgc_inputbox[]									= "inputbox";
	const s8		cgc_insmode[]									= "insmode";
	const s8		cgc_int[]										= "int";
	const s8		cgc_isalpha[]									= "isalpha";
	const s8		cgc_isblank[]									= "isblank";
	const s8		cgc_iscolor[]									= "iscolor";
	const s8		cgc_isdigit[]									= "isdigit";
	const s8		cgc_isexclusive[]								= "isexclusive";
	const s8		cgc_isflocked[]									= "isflocked";
	const s8		cgc_isleadbyte[]								= "isleadbyte";
	const s8		cgc_islower[]									= "islower";
	const s8		cgc_ismemofetched[]								= "ismemofetched";
	const s8		cgc_ismouse[]									= "ismouse";
	const s8		cgc_isnull[]									= "isnull";
	const s8		cgc_ispen[]										= "ispen";
	const s8		cgc_isreadonly[]								= "isreadonly";
	const s8		cgc_isrlocked[]									= "isrlocked";
	const s8		cgc_istransactable[]							= "istransactable";
	const s8		cgc_isupper[]									= "isupper";
	const s8		cgc_justdrive[]									= "justdrive";
	const s8		cgc_justext[]									= "justext";
	const s8		cgc_justfname[]									= "justfname";
	const s8		cgc_justpath[]									= "justpath";
	const s8		cgc_juststem[]									= "juststem";
	const s8		cgc_keymatch[]									= "keymatch";
	const s8		cgc_keep[]										= "keep";
	const s8		cgc_key[]										= "key";
	const s8		cgc_loadParams[]								= "loadparams";
	const s8		cgc_lastkey[]									= "lastkey";
	const s8		cgc_leftc[]										= "leftc";
	const s8		cgc_left[]										= "left";
	const s8		cgc_lenc[]										= "lenc";
	const s8		cgc_len[]										= "len";
	const s8		cgc_likec[]										= "likec";
	const s8		cgc_like[]										= "like";
	const s8		cgc_lineno[]									= "lineno";
	const s8		cgc_loadpicture[]								= "loadpicture";
	const s8		cgc_locfile[]									= "locfile";
	const s8		cgc_lock[]										= "lock";
	const s8		cgc_log10[]										= "log10";
	const s8		cgc_log[]										= "log";
	const s8		cgc_lookup[]									= "lookup";
	const s8		cgc_lower[]										= "lower";
	const s8		cgc_ltrim[]										= "ltrim";
	const s8		cgc_lupdate[]									= "lupdate";
	const s8		cgc_maketransactable[]							= "maketransactable";
	const s8		cgc_malp[]										= "malp";
	const s8		cgc_max[]										= "max";
	const s8		cgc_mcol[]										= "mcol";
	const s8		cgc_mdown[]										= "mdown";
	const s8		cgc_mdx[]										= "mdx";
	const s8		cgc_mdy[]										= "mdy";
	const s8		cgc_memlines[]									= "memlines";
	const s8		cgc_memory[]									= "memory";
	const s8		cgc_menu[]										= "menu";
	const s8		cgc_messagebox[]								= "messagebox";
	const s8		cgc_message[]									= "message";
	const s8		cgc_microsecond[]								= "microsecond";
	const s8		cgc_minute[]									= "minute";
	const s8		cgc_min[]										= "min";
	const s8		cgc_mline[]										= "mline";
	const s8		cgc_mod[]										= "mod";
	const s8		cgc_month[]										= "month";
	const s8		cgc_mrkbar[]									= "mrkbar";
	const s8		cgc_mrkpad[]									= "mrkpad";
	const s8		cgc_mrow[]										= "mrow";
	const s8		cgc_mton[]										= "mton";
	const s8		cgc_mwindow[]									= "mwindow";
	const s8		cgc_nanosecond[]								= "nanosecond";
	const s8		cgc_ncset[]										= "ncset";
	const s8		cgc_ndx[]										= "ndx";
	const s8		cgc_newobject[]									= "newobject";
	const s8		cgc_noLoadParams[]								= "noloadparams";
	const s8		cgc_nodata[]									= "nodata";
	const s8		cgc_norequery[]									= "norequery";
	const s8		cgc_normalize[]									= "normalize";
	const s8		cgc_noUnloadParams[]							= "nounloadparams";
	const s8		cgc_noupdate[]									= "noupdate";
	const s8		cgc_ntom[]										= "ntom";
	const s8		cgc_numlock[]									= "numlock";
	const s8		cgc_nvl[]										= "nvl";
	const s8		cgc_objnum[]									= "objnum";
	const s8		cgc_objtoclient[]								= "objtoclient";
	const s8		cgc_objvar[]									= "objvar";
	const s8		cgc_occursc[]									= "occursc";
	const s8		cgc_occurs[]									= "occurs";
	const s8		cgc_oemtoansi[]									= "oemtoansi";
	const s8		cgc_oldval[]									= "oldval";
	const s8		cgc_on[]										= "on";
	const s8		cgc_order[]										= "order";
	const s8		cgc_os[]										= "os";
	const s8		cgc_overview[]									= "overview";
	const s8		cgc_outside[]									= "outside";
	const s8		cgc_padc[]										= "padc";
	const s8		cgc_padl[]										= "padl";
	const s8		cgc_padr[]										= "padr";
	const s8		cgc_pad[]										= "pad";
	const s8		cgc_parameters[]								= "parameters";
	const s8		cgc_payment[]									= "payment";
	const s8		cgc_pcol[]										= "pcol";
	const s8		cgc_pcount[]									= "pcount";
	const s8		cgc_pemstatus[]									= "pemstatus";
	const s8		cgc_pi[]										= "pi";
	const s8		cgc_popup[]										= "popup";
	const s8		cgc_pow[]										= "pow";
	const s8		cgc_precisionbfp[]								= "precisionbfp";
	const s8		cgc_precisionbi[]								= "precisionbi";
	const s8		cgc_primary[]									= "primary";
	const s8		cgc_printstatus[]								= "printstatus";
	const s8		cgc_prmbar[]									= "prmbar";
	const s8		cgc_prmpad[]									= "prmpad";
	const s8		cgc_program[]									= "program";
	const s8		cgc_prompt[]									= "prompt";
	const s8		cgc_proper[]									= "proper";
	const s8		cgc_prow[]										= "prow";
	const s8		cgc_prtinfo[]									= "prtinfo";
	const s8		cgc_putfile[]									= "putfile";
	const s8		cgc_pv[]										= "pv";
	const s8		cgc_quarter[]									= "quarter";
	const s8		cgc_ranger[]									= "ranger";
	const s8		cgc_ranger2[]									= "ranger2";
	const s8		cgc_raiseevent[]								= "raiseevent";
	const s8		cgc_rand[]										= "rand";
	const s8		cgc_ratc[]										= "ratc";
	const s8		cgc_rat[]										= "rat";
	const s8		cgc_ratline[]									= "ratline";
	const s8		cgc_rdlevel[]									= "rdlevel";
	const s8		cgc_readkey[]									= "readkey";
	const s8		cgc_reccount[]									= "reccount";
	const s8		cgc_recno[]										= "recno";
	const s8		cgc_recsize[]									= "recsize";
	const s8		cgc_red[]										= "red";
	const s8		cgc_refresh[]									= "refresh";
	const s8		cgc_relation[]									= "relation";
	const s8		cgc_replicate[]									= "replicate";
	const s8		cgc_requery[]									= "requery";
	const s8		cgc_rgb[]										= "rgb";
	const s8		cgc_rgbscheme[]									= "rgbscheme";
	const s8		cgc_right[]										= "right";
	const s8		cgc_rightc[]									= "rightc";
	const s8		cgc_rlock[]										= "rlock";
	const s8		cgc_round[]										= "round";
	const s8		cgc_row[]										= "row";
	const s8		cgc_rtod[]										= "rtod";
	const s8		cgc_rtrim[]										= "rtrim";
	const s8		cgc_savepicture[]								= "savepicture";
	const s8		cgc_scheme[]									= "scheme";
	const s8		cgc_scols[]										= "scols";
	const s8		cgc_seconds[]									= "seconds";
	const s8		cgc_secondstotime[]								= "secondstotime";
	const s8		cgc_secondstotimex[]							= "secondstotimex";
	const s8		cgc_secondsx[]									= "secondsx";
	const s8		cgc_secondsxtotime[]							= "secondsxtotime";
	const s8		cgc_secondsxtotimex[]							= "secondsxtotimex";
	const s8		cgc_secondstot[]								= "secondstot";
	const s8		cgc_secondstox[]								= "secondstox";
	const s8		cgc_secondsxtot[]								= "secondsxtot";
	const s8		cgc_secondsxtox[]								= "secondsxtox";
	const s8		cgc_sec[]										= "sec";
	const s8		cgc_seek[]										= "seek";
	const s8		cgc_select[]									= "select";
	const s8		cgc_set[]										= "set";
	const s8		cgc_short[]										= "short";
	const s8		cgc_setfldstate[]								= "setfldstate";
	const s8		cgc_setresultset[]								= "setresultset";
	const s8		cgc_shared[]									= "shared";
	const s8		cgc_sign[]										= "sign";
	const s8		cgc_sin[]										= "sin";
	const s8		cgc_skpbar[]									= "skpbar";
	const s8		cgc_skppad[]									= "skppad";
	const s8		cgc_slice[]										= "slice";
	const s8		cgc_soundex[]									= "soundex";
	const s8		cgc_space[]										= "space";
	const s8		cgc_sqlcancel[]									= "sqlcancel";
	const s8		cgc_sqlcolumns[]								= "sqlcolumns";
	const s8		cgc_sqlcommit[]									= "sqlcommit";
	const s8		cgc_sqlconnect[]								= "sqlconnect";
	const s8		cgc_sqldisconnect[]								= "sqldisconnect";
	const s8		cgc_sqlexec[]									= "sqlexec";
	const s8		cgc_sqlgetprop[]								= "sqlgetprop";
	const s8		cgc_sqlidledisconnect[]							= "sqlidledisconnect";
	const s8		cgc_sqlmoreresults[]							= "sqlmoreresults";
	const s8		cgc_sqlprepare[]								= "sqlprepare";
	const s8		cgc_sqlrollback[]								= "sqlrollback";
	const s8		cgc_sqlsetprop[]								= "sqlsetprop";
	const s8		cgc_sqlstringconnect[]							= "sqlstringconnect";
	const s8		cgc_sqltables[]									= "sqltables";
	const s8		cgc_sqrt[]										= "sqrt";
	const s8		cgc_srows[]										= "srows";
	const s8		cgc_startswith[]								= "startswith";
	const s8		cgc_startswithc[]								= "startswithc";
	const s8		cgc_strconv[]									= "strconv";
	const s8		cgc_strextract[]								= "strextract";
	const s8		cgc_strtofile[]									= "strtofile";
	const s8		cgc_strtranc[]									= "strtranc";
	const s8		cgc_strtran[]									= "strtran";
	const s8		cgc_str[]										= "str";
	const s8		cgc_stuffc[]									= "stuffc";
	const s8		cgc_stuff[]										= "stuff";
	const s8		cgc_substrc[]									= "substrc";
	const s8		cgc_substr[]									= "substr";
	const s8		cgc_sysmetric[]									= "sysmetric";
	const s8		cgc_sys[]										= "sys";
	const s8		cgc_tablerevert[]								= "tablerevert";
	const s8		cgc_tableupdate[]								= "tableupdate";
	const s8		cgc_tag[]										= "tag";
	const s8		cgc_taiwan[]									= "taiwan";
	const s8		cgc_tagcount[]									= "tagcount";
	const s8		cgc_tagno[]										= "tagno";
	const s8		cgc_tan[]										= "tan";
	const s8		cgc_target[]									= "target";
	const s8		cgc_textmerge[]									= "textmerge";
	const s8		cgc_time[]										= "time";
	const s8		cgc_timetoseconds[]								= "timetoseconds";
	const s8		cgc_timetosecondsx[]							= "timetosecondsx";
	const s8		cgc_timetot[]									= "timetot";
	const s8		cgc_timetox[]									= "timetox";
	const s8		cgc_timex[]										= "timex";
	const s8		cgc_timextoseconds[]							= "timextoseconds";
	const s8		cgc_timextosecondsx[]							= "timextosecondsx";
	const s8		cgc_timextot[]									= "timextot";
	const s8		cgc_timextox[]									= "timextox";
	const s8		cgc_transform[]									= "transform";
	const s8		cgc_trim[]										= "trim";
	const s8		cgc_ttoc[]										= "ttoc";
	const s8		cgc_ttod[]										= "ttod";
	const s8		cgc_ttoseconds[]								= "ttoseconds";
	const s8		cgc_ttosecondsx[]								= "ttosecondsx";
	const s8		cgc_ttotime[]									= "ttotime";
	const s8		cgc_ttotimex[]									= "ttotimex";
	const s8		cgc_ttox[]										= "ttox";
	const s8		cgc_txnlevel[]									= "txnlevel";
	const s8		cgc_txtwidth[]									= "txtwidth";
	const s8		cgc_type[]										= "type";
	const s8		cgc_typedetail[]								= "typedetail";
	const s8		cgc_unbindevents[]								= "unbindevents";
	const s8		cgc_unloadparams[]								= "unloadparams";
	const s8		cgc_unique[]									= "unique";
	const s8		cgc_updated[]									= "updated";
	const s8		cgc_upper[]										= "upper";
	const s8		cgc_used[]										= "used";
	const s8		cgc_val[]										= "val";
	const s8		cgc_varread[]									= "varread";
	const s8		cgc_vartype[]									= "vartype";
	const s8		cgc_vec[]										= "vec";
	const s8		cgc_veccount[]									= "veccount";
	const s8		cgc_vecel[]										= "vecel";
	const s8		cgc_vecslice[]									= "vecslice";
	const s8		cgc_vecstr[]									= "vecstr";
	const s8		cgc_vecstuff[]									= "vecstuff";
	const s8		cgc_vecsymbol[]									= "vecsymbol";
	const s8		cgc_version[]									= "version";
	const s8		cgc_wborder[]									= "wborder";
	const s8		cgc_wchild[]									= "wchild";
	const s8		cgc_wcols[]										= "wcols";
	const s8		cgc_wdockable[]									= "wdockable";
	const s8		cgc_week[]										= "week";
	const s8		cgc_wexist[]									= "wexist";
	const s8		cgc_wfont[]										= "wfont";
	const s8		cgc_wlast[]										= "wlast";
	const s8		cgc_wlcol[]										= "wlcol";
	const s8		cgc_wlrow[]										= "wlrow";
	const s8		cgc_wmaximum[]									= "wmaximum";
	const s8		cgc_wminimum[]									= "wminimum";
	const s8		cgc_wontop[]									= "wontop";
	const s8		cgc_woutput[]									= "woutput";
	const s8		cgc_wparent[]									= "wparent";
	const s8		cgc_wread[]										= "wread";
	const s8		cgc_wrows[]										= "wrows";
	const s8		cgc_wtitle[]									= "wtitle";
	const s8		cgc_wvisible[]									= "wvisible";
	const s8		cgc_xmltocursor[]								= "xmltocursor";
	const s8		cgc_xmlupdategram[]								= "xmlupdategram";
	const s8		cgc_xtod[]										= "xtod";
	const s8		cgc_xtoseconds[]								= "xtoseconds";
	const s8		cgc_xtosecondsx[]								= "xtosecondsx";
	const s8		cgc_xtot[]										= "xtot";
	const s8		cgc_xtotime[]									= "xtotime";
	const s8		cgc_xtotimex[]									= "xtotimex";
	const s8		cgc_year[]										= "year";
	const s8		cgc__test[]										= "_test";

// Temporarily added until the processing engine is completed until the processing engine is completed
	const s8		cgc_concatenate[]								= "concatenate";
	const s8		cgc_add[]										= "add";
	const s8		cgc_sub[]										= "sub";
	const s8		cgc_mul[]										= "mul";
	const s8		cgc_div[]										= "div";

// Commands
	const s8		cgc_activate[]									= "activate";
//	const s8		cgc_add[]										= "add";
	const s8		cgc_additive[]									= "additive";
	const s8		cgc_all[]										= "all";
	const s8		cgc_alter[]										= "alter";
	const s8		cgc_alternate[]									= "alternate";
	const s8		cgc_american[]									= "american";
	const s8		cgc_ansi[]										= "ansi";
	const s8		cgc_app[]										= "app";
	const s8		cgc_append[]									= "append";
	const s8		cgc_array[]										= "array";
	const s8		cgc_asserts[]									= "asserts";
	const s8		cgc_assert[]									= "assert";
	const s8		cgc_assist[]									= "assist";
	const s8		cgc_autoincerror[]								= "autoincerror";
	const s8		cgc_automatic[]									= "automatic";
	const s8		cgc_autosave[]									= "autosave";
	const s8		cgc_average[]									= "average";
//	const s8		cgc_bar[]										= "bar";
	const s8		cgc_begin[]										= "begin";
	const s8		cgc_bell[]										= "bell";
	const s8		cgc_blank[]										= "blank";
	const s8		cgc_blocksize[]									= "blocksize";
	const s8		cgc_border[]									= "border";
	const s8		cgc_box[]										= "box";
	const s8		cgc_british[]									= "british";
	const s8		cgc_browse[]									= "browse";
	const s8		cgc_browseime[]									= "browseime";
	const s8		cgc_brstatus[]									= "brstatus";
	const s8		cgc_build[]										= "build";
	const s8		cgc_calculate[]									= "calculate";
	const s8		cgc_call[]										= "call";
	const s8		cgc_cancel[]									= "cancel";
	const s8		cgc_carry[]										= "carry";
	const s8		cgc_case[]										= "case";
	const s8		cgc_catch[]										= "catch";
	const s8		cgc_cd[]										= "cd";
	const s8		cgc_century[]									= "century";
	const s8		cgc_change[]									= "change";
	const s8		cgc_chdir[]										= "chdir";
	const s8		cgc_class[]										= "class";
	const s8		cgc_classlib[]									= "classlib";
	const s8		cgc_clear[]										= "clear";
	const s8		cgc_clears[]									= "clears";
	const s8		cgc_clock[]										= "clock";
	const s8		cgc_close[]										= "close";
	const s8		cgc_closes[]									= "closes";
	const s8		cgc_collate[]									= "collate";
	const s8		cgc_color[]										= "color";
	const s8		cgc_compatible[]								= "compatible";
	const s8		cgc_compile[]									= "compile";
	const s8		cgc_confirm[]									= "confirm";
	const s8		cgc_connection[]								= "connection";
	const s8		cgc_connections[]								= "connections";
	const s8		cgc_console[]									= "console";
	const s8		cgc_continue[]									= "continue";
	const s8		cgc_copy[]										= "copy";
	const s8		cgc_count[]										= "count";
	const s8		cgc_coverage[]									= "coverage";
	const s8		cgc_cpcompile[]									= "cpcompile";
	const s8		cgc_cpdialog[]									= "cpdialog";
	const s8		cgc_create[]									= "create";
	const s8		cgc_currency[]									= "currency";
	const s8		cgc_cursor[]									= "cursor";
	const s8		cgc_database[]									= "database";
	const s8		cgc_datasession[]								= "datasession";
//	const s8		cgc_date[]										= "date";
	const s8		cgc_deactivate[]								= "deactivate";
	const s8		cgc_debug[]										= "debug";
	const s8		cgc_debugout[]									= "debugout";
	const s8		cgc_decimals[]									= "decimals";
	const s8		cgc_declare[]									= "declare";
	const s8		cgc_default[]									= "default";
	const s8		cgc_define[]									= "define";
	const s8		cgc_delete[]									= "delete";
//	const s8		cgc_deleted[]									= "deleted";
	const s8		cgc_delimiters[]								= "delimiters";
	const s8		cgc_development[]								= "development";
	const s8		cgc_device[]									= "device";
	const s8		cgc_devicefilename[]							= "devicefilename";
	const s8		cgc_dimension[]									= "dimension";
	const s8		cgc_dir[]										= "dir";
//	const s8		cgc_directory[]									= "directory";
	const s8		cgc_display[]									= "display";
	const s8		cgc_dlls[]										= "dlls";
	const s8		cgc_dll[]										= "dll";
	const s8		cgc_do[]										= "do";
	const s8		cgc_dock[]										= "dock";
	const s8		cgc_doevents[]									= "doevents";
	const s8		cgc_dohistory[]									= "dohistory";
	const s8		cgc_drop[]										= "drop";
	const s8		cgc_each[]										= "each";
	const s8		cgc_echo[]										= "echo";
	const s8		cgc_edit[]										= "edit";
	const s8		cgc_eject[]										= "eject";
	const s8		cgc_else[]										= "else";
	const s8		cgc_end[]										= "end";
	const s8		cgc_endcase[]									= "endcase";
	const s8		cgc_enddo[]										= "enddo";
	const s8		cgc_endfor[]									= "endfor";
	const s8		cgc_endfunction[]								= "endfunction";
	const s8		cgc_endif[]										= "endif";
	const s8		cgc_endprocedure[]								= "endprocedure";
	const s8		cgc_endscan[]									= "endscan";
	const s8		cgc_endtext[]									= "endtext";
	const s8		cgc_endwith[]									= "endwith";
	const s8		cgc_enginebehavior[]							= "enginebehavior";
	const s8		cgc_erase[]										= "erase";
//	const s8		cgc_error[]										= "error";
	const s8		cgc_escape[]									= "escape";
	const s8		cgc_eventlist[]									= "eventlist";
	const s8		cgc_events[]									= "events";
	const s8		cgc_eventtracking[]								= "eventtracking";
	const s8		cgc_exact[]										= "exact";
	const s8		cgc_exclusive[]									= "exclusive";
	const s8		cgc_exe[]										= "exe";
	const s8		cgc_exit[]										= "exit";
	const s8		cgc_export[]									= "export";
	const s8		cgc_extended[]									= "extended";
	const s8		cgc_external[]									= "external";
	const s8		cgc_fdow[]										= "fdow";
	const s8		cgc_fields[]									= "fields";
	const s8		cgc_files[]										= "files";
//	const s8		cgc_file[]										= "file";
	const s8		cgc_fill[]										= "fill";
//	const s8		cgc_filter[]									= "filter";
	const s8		cgc_finally[]									= "finally";
	const s8		cgc_find[]										= "find";
	const s8		cgc_fixed[]										= "fixed";
	const s8		cgc_flush[]										= "flush";
	const s8		cgc_format[]									= "format";
	const s8		cgc_form[]										= "form";
	const s8		cgc_for[]										= "for";
	const s8		cgc_free[]										= "free";
	const s8		cgc_french[]									= "french";
	const s8		cgc_from[]										= "from";
//	const s8		cgc_fullpath[]									= "fullpath";
	const s8		cgc_function[]									= "function";
	const s8		cgc_fweek[]										= "fweek";
	const s8		cgc_gather[]									= "gather";
	const s8		cgc_general[]									= "general";
	const s8		cgc_german[]									= "german";
	const s8		cgc_getexpr[]									= "getexpr";
	const s8		cgc_gets[]										= "gets";
	const s8		cgc_get[]										= "get";
	const s8		cgc_go[]										= "go";
	const s8		cgc_goto[]										= "goto";
	const s8		cgc_headings[]									= "headings";
	const s8		cgc_help[]										= "help";
	const s8		cgc_hide[]										= "hide";
	const s8		cgc_hours[]										= "hours";
	const s8		cgc_id[]										= "id";
	const s8		cgc_if[]										= "if";
	const s8		cgc_import[]									= "import";
	const s8		cgc_indexes[]									= "indexes";
	const s8		cgc_index[]										= "index";
	const s8		cgc_input[]										= "input";
	const s8		cgc_insert[]									= "insert";
	const s8		cgc_intensity[]									= "intensity";
	const s8		cgc_italian[]									= "italian";
	const s8		cgc_japan[]										= "japan";
	const s8		cgc_join[]										= "join";
	const s8		cgc_journal[]									= "journal";
//	const s8		cgc_key[]										= "key";
	const s8		cgc_keyboard[]									= "keyboard";
	const s8		cgc_keycomp[]									= "keycomp";
	const s8		cgc_label[]										= "label";
	const s8		cgc_last[]										= "last";
	const s8		cgc_lelse[]										= "lelse";
	const s8		cgc_library[]									= "library";
	const s8		cgc_lif[]										= "lif";
	const s8		cgc_lists[]										= "lists";
	const s8		cgc_list[]										= "list";
	const s8		cgc_load[]										= "load";
	const s8		cgc_local[]										= "local";
	const s8		cgc_locate[]									= "locate";
//	const s8		cgc_lock[]										= "lock";
	const s8		cgc_logerrors[]									= "logerrors";
	const s8		cgc_long[]										= "long";
	const s8		cgc_loop[]										= "loop";
	const s8		cgc_lparameters[]								= "lparameters";
	const s8		cgc_mackey[]									= "mackey";
	const s8		cgc_macros[]									= "macros";
	const s8		cgc_macro[]										= "macro";
	const s8		cgc_margin[]									= "margin";
	const s8		cgc_mark[]										= "mark";
	const s8		cgc_md[]										= "md";
	const s8		cgc_memowidth[]									= "memowidth";
//	const s8		cgc_memory[]									= "memory";
	const s8		cgc_memo[]										= "memo";
	const s8		cgc_menus[]										= "menus";
//	const s8		cgc_menu[]										= "menu";
//	const s8		cgc_message[]									= "message";
	const s8		cgc_mkdir[]										= "mkdir";
	const s8		cgc_modify[]									= "modify";
	const s8		cgc_mouse[]										= "mouse";
	const s8		cgc_move[]										= "move";
	const s8		cgc_mtdll[]										= "mtdll";
	const s8		cgc_multilocks[]								= "multilocks";
	const s8		cgc_near[]										= "near";
	const s8		cgc_next[]										= "next";
	const s8		cgc_nocptrans[]									= "nocptrans";
	const s8		cgc_note[]										= "note";
	const s8		cgc_notify[]									= "notify";
	const s8		cgc_nulldisplay[]								= "nulldisplay";
	const s8		cgc_objects[]									= "objects";
	const s8		cgc_object[]									= "object";
	const s8		cgc_odometer[]									= "odometer";
	const s8		cgc_off[]										= "off";
	const s8		cgc_of[]										= "of";
	const s8		cgc_oleobject[]									= "oleobject";
//	const s8		cgc_on[]										= "on";
	const s8		cgc_open[]										= "open";
	const s8		cgc_optimize[]									= "optimize";
//	const s8		cgc_order[]										= "order";
	const s8		cgc_or[]										= "or";
//	const s8		cgc_overview[]									= "overview";
	const s8		cgc_pack[]										= "pack";
//	const s8		cgc_pad[]										= "pad";
	const s8		cgc_page[]										= "page";
	const s8		cgc_palette[]									= "palette";
//	const s8		cgc_parameters[]								= "parameters";
	const s8		cgc_path[]										= "path";
	const s8		cgc_pdsetup[]									= "pdsetup";
	const s8		cgc_play[]										= "play";
	const s8		cgc_point[]										= "point";
	const s8		cgc_pop[]										= "pop";
	const s8		cgc_popups[]									= "popups";
//	const s8		cgc_popup[]										= "popup";
	const s8		cgc_printer[]									= "printer";
	const s8		cgc_private[]									= "private";
	const s8		cgc_procedures[]								= "procedures";
	const s8		cgc_procedure[]									= "procedure";
	const s8		cgc_project[]									= "project";
//	const s8		cgc_prompt[]									= "prompt";
	const s8		cgc_public[]									= "public";
	const s8		cgc_push[]										= "push";
	const s8		cgc_query[]										= "query";
	const s8		cgc_quit[]										= "quit";
	const s8		cgc_rd[]										= "rd";
	const s8		cgc_read[]										= "read";
	const s8		cgc_readborder[]								= "readborder";
	const s8		cgc_readerror[]									= "readerror";
	const s8		cgc_recall[]									= "recall";
	const s8		cgc_recover[]									= "recover";
	const s8		cgc_reference[]									= "reference";
//	const s8		cgc_refresh[]									= "refresh";
	const s8		cgc_reindex[]									= "reindex";
//	const s8		cgc_relation[]									= "relation";
	const s8		cgc_release[]									= "release";
	const s8		cgc_remove[]									= "remove";
	const s8		cgc_rename[]									= "rename";
	const s8		cgc_replace[]									= "replace";
	const s8		cgc_report[]									= "report";
	const s8		cgc_reprocessattempts[]							= "reprocessattempts";
	const s8		cgc_reprocess[]									= "reprocess";
	const s8		cgc_resource[]									= "resource";
	const s8		cgc_resources[]									= "resources";
	const s8		cgc_restore[]									= "restore";
	const s8		cgc_resume[]									= "resume";
	const s8		cgc_retry[]										= "retry";
	const s8		cgc_return[]									= "return";
	const s8		cgc_rmdir[]										= "rmdir";
	const s8		cgc_rollback[]									= "rollback";
	const s8		cgc_run[]										= "run";
	const s8		cgc_safety[]									= "safety";
	const s8		cgc_save[]										= "save";
	const s8		cgc_say[]										= "say";
	const s8		cgc_scan[]										= "scan";
	const s8		cgc_scatter[]									= "scatter";
//	const s8		cgc_scheme[]									= "scheme";
	const s8		cgc_screen[]									= "screen";
	const s8		cgc_scroll[]									= "scroll";
//	const s8		cgc_seconds[]									= "seconds";
//	const s8		cgc_seek[]										= "seek";
//	const s8		cgc_select[]									= "select";
	const s8		cgc_selection[]									= "selection";
	const s8		cgc_separator[]									= "separator";
//	const s8		cgc_set[]										= "set";
	const s8		cgc_show[]										= "show";
	const s8		cgc_shutdown[]									= "shutdown";
	const s8		cgc_size[]										= "size";
	const s8		cgc_skip[]										= "skip";
	const s8		cgc_sort[]										= "sort";
//	const s8		cgc_space[]										= "space";
	const s8		cgc_sql[]										= "sql";
	const s8		cgc_status[]									= "status";
	const s8		cgc_step[]										= "step";
	const s8		cgc_store[]										= "store";
	const s8		cgc_strictdate[]								= "strictdate";
	const s8		cgc_structure[]									= "structure";
	const s8		cgc_sum[]										= "sum";
	const s8		cgc_suspend[]									= "suspend";
	const s8		cgc_sysformats[]								= "sysformats";
	const s8		cgc_sysmenu[]									= "sysmenu";
	const s8		cgc_system[]									= "system";
//	const s8		cgc_sys[]										= "sys";
	const s8		cgc_tablevalidate[]								= "tablevalidate";
	const s8		cgc_tables[]									= "tables";
	const s8		cgc_table[]										= "table";
//	const s8		cgc_tag[]										= "tag";
	const s8		cgc_talk[]										= "talk";
//	const s8		cgc_textmerge[]									= "textmerge";
	const s8		cgc_text[]										= "text";
	const s8		cgc_tf[]										= "tf";
	const s8		cgc_to[]										= "to";
	const s8		cgc_topic[]										= "topic";
	const s8		cgc_total[]										= "total";
	const s8		cgc_transaction[]								= "transaction";
	const s8		cgc_trbetween[]									= "trbetween";
	const s8		cgc_trigger[]									= "trigger";
	const s8		cgc_try[]										= "try";
//	const s8		cgc_type[]										= "type";
	const s8		cgc_typeahead[]									= "typeahead";
	const s8		cgc_ud[]										= "ud";
	const s8		cgc_udfparms[]									= "udfparms";
//	const s8		cgc_unique[]									= "unique";
	const s8		cgc_unlock[]									= "unlock";
	const s8		cgc_update[]									= "update";
	const s8		cgc_usa[]										= "usa";
	const s8		cgc_use[]										= "use";
	const s8		cgc_validate[]									= "validate";
	const s8		cgc_value[]										= "value";
	const s8		cgc_views[]										= "views";
	const s8		cgc_view[]										= "view";
	const s8		cgc_visualize[]									= "visualize";
	const s8		cgc_wait[]										= "wait";
	const s8		cgc_while[]										= "while";
	const s8		cgc_windows[]									= "windows";
	const s8		cgc_window[]									= "window";
	const s8		cgc_with[]										= "with";
	const s8		cgc_ymd[]										= "ymd";
	const s8		cgc_yn[]										= "yn";
	const s8		cgc_zap[]										= "zap";

	// keywords
	const s8		cgc_not_dots[]									= ".not.";
	const s8		cgc_not[]										= "not";
	const s8		cgc_and_dots[]									= ".and.";
	const s8		cgc_and[]										= "and";
	const s8		cgc_or_dots[]									= ".or.";
//	const s8		cgc_or[]										= "or";

	// Relatives
	const s8		cgc_thiscode[]									= "thiscode";
	const s8		cgc_thisclass[]									= "thisclass";
	const s8		cgc_thisform[]									= "thisform";
	const s8		cgc_parent[]									= "parent";

	// Stand-alones
	const s8		cgc_null[]										= "null";
	const s8		cgc_null_dots[]									= ".null.";
	const s8		cgc_true[]										= "true";
	const s8		cgc_t_dots[]									= ".t.";
	const s8		cgc_false[]										= "false";
	const s8		cgc_f_dots[]									= ".f.";
	const s8		cgc_Y[]											= "Y";
	const s8		cgc_y[]											= "y";
	const s8		cgc_yes[]										= "yes";
	const s8		cgc_yes_dots[]									= ".y.";
	const s8		cgc_N[]											= "N";
	const s8		cgc_n[]											= "n";
	const s8		cgc_no[]										= "no";
	const s8		cgc_no_dots[]									= ".n.";
	const s8		cgc_up[]										= "up";
	const s8		cgc_up_dots[]									= ".u.";
	const s8		cgc_down[]										= "down";
	const s8		cgc_down_dots[]									= ".d.";
	const s8		cgc_o_dots[]									= ".o.";
	const s8		cgc_p_dots[]									= ".p.";
	const s8		cgc_x_dots[]									= ".x.";
	const s8		cgc_y_dots[]									= ".y.";
	const s8		cgc_z_dots[]									= ".z.";
	const s8		cgc_d[]											= "D";
	const s8		cgc_a[]											= "A";

	// DLL options (Kernel32.dll, Gdi32.dll, User32.dll, Mpr.dll, and Advapi32.dll)
	const s8		cgc_win32api[]									= "win32api";
	const s8		cgc_kernel32[]									= "kernel32";
	const s8		cgc_gdi32[]										= "gdi32";
	const s8		cgc_user32[]									= "user32";
	const s8		cgc_mpr[]										= "mpr";
	const s8		cgc_advapi32[]									= "advapi32";

	// NCSET() specific
	const s8		cgc_ncset_alphaisopaque[]						= "alphaIsOpaque";
	const s8		cgc_ncset_ceilingfloor[]						= "ceilingfloor";
	const s8		cgc_ncset_datetimemilliseconds[]				= "datetimemilliseconds";
	const s8		cgc_ncset_optimizetablewrites[]					= "optimizetablewrites";
	const s8		cgc_ncset_optimizevariables[]					= "optimizevariables";
	const s8		cgc_ncset_signsign2[]							= "signsign2";

	// VXB specific
	const s8		cgc__screen[]									= "_screen";
	const s8		cgc__vjr[]										= "_vjr";
	const s8		cgc__jdebi[]									= "_jdebi";
	const s8		cgc__cmd[]										= "_cmd";
	const s8		cgc__settings[]									= "_settings";
	const s8		cgc_protected[]									= "protected";
	const s8		cgc_main[]										= "main";
	const s8		cgc_loadlastfromvjruserdbf[]					= "loadlastfromvjruserdbf"; 
	const s8		cgc_flags[]										= "flags";
	const s8		cgc_metaicase[]									= "metaicase";
	const s8		cgc_mefaicase[]									= "mefaicase";
	const s8		cgc_meiaicase[]									= "meiaicase";
	const s8		cgc_memaicase[]									= "memaicase";
	const s8		cgc_meta[]										= "meta";
	const s8		cgc_mefa[]										= "mefa";
	const s8		cgc_meia[]										= "meia";
	const s8		cgc_mema[]										= "mema";
	const s8		cgc_flowof[]									= "flowof";
	const s8		cgc_flowout[]									= "flowout";
	const s8		cgc_flowto[]									= "flowto";
	const s8		cgc_flow[]										= "flow";
	const s8		cgc_subflow[]									= "subflow";
	const s8		cgc_rgba[]										= "rgba";
	const s8		cgc_lobject[]									= "lobject";
	const s8		cgc_params[]									= "params";
	const s8		cgc_returns[]									= "returns";
	const s8		cgc_as[]										= "as";
	const s8		cgc_character[]									= "character";
	const s8		cgc_integer[]									= "integer";
	const s8		cgc_float[]										= "float";
	const s8		cgc_double[]									= "double";
	const s8		cgc_logical[]									= "logical";
	const s8		cgc_s32[]										= "s32";
	const s8		cgc_s64[]										= "s64";
	const s8		cgc_u32[]										= "u32";
	const s8		cgc_u64[]										= "u64";
	const s8		cgc_f32[]										= "f32";
	const s8		cgc_f64[]										= "f64";
	const s8		cgc_bi[]										= "bi";
	const s8		cgc_bfp[]										= "bfp";
	const s8		cgc_s16[]										= "s16";
	const s8		cgc_s8[]										= "s8";
	const s8		cgc_u16[]										= "u16";
	const s8		cgc_u8[]										= "u8";
	const s8		cgc_adhoc[]										= "adhoc";
	const s8		cgc_endadhoc[]									= "endadhoc";
	const s8		cgc_single[]									= "single";
	const s8		cgc_string[]									= "string";
	const s8		cgc_numeric[]									= "numeric";
	const s8		cgc_unicode[]									= "unicode";
	const s8		cgc_guid8[]										= "guid8";
	const s8		cgc_guid16[]									= "guid16";
	const s8		cgc_bitmap[]									= "bitmap";
	const s8		cgc_bitmap_movie[]								= "bitmapMovie";
	const s8		cgc_vector[]									= "vector";
	const s8		cgc_unknown[]									= "unknown";


//////////
// Fundamental variable types
//////
	const u32		_VAR_TYPE_NONE									= -1;	// Used for DECLARE DLL when nothing is defined, such as DECLARE Sleep() IN WIN32API INTEGER nMilliseconds, which has no return value
	const u32						_VAR_TYPE_START					= 0;
	const u32		_VAR_TYPE_NULL									= 0;	// Note:  This is an explicit .NULL. variable type.  However, other types can also be .NULL. and retain their type.  As such, var->varType cannot be the ONLY test used.  Also check var->value.data, and var->value.length. If those are NULL or 0, then it is also .NULL.

	// Signed
	const u32						_VAR_TYPE_NUMERIC_START			= 1;
	const u32						_VAR_TYPE_NUMERIC_INTEGER_START	= 1;
	const u32						_VAR_TYPE_SIGNED_INTEGER_START	= 1;
	const u32						_VAR_TYPE_INTEGER_START			= 1;
	const u32		_VAR_TYPE_S8									= 1;
	const u32		_VAR_TYPE_S16									= 2;
	const u32		_VAR_TYPE_S32									= 3;	// Formerly _VAR_TYPE_INTEGER
	const u32		_VAR_TYPE_S64									= 4;
	const u32						_VAR_TYPE_SIGNED_INTEGER_END	= 4;

	// Unsigned
	const u32						_VAR_TYPE_UNSIGNED_INTEGER_START = 5;
	const u32		_VAR_TYPE_U8									= 5;
	const u32		_VAR_TYPE_U16									= 6;
	const u32		_VAR_TYPE_U32									= 7;
	const u32		_VAR_TYPE_U64									= 8;
	const u32						_VAR_TYPE_INTEGER_END			= 8;
	const u32						_VAR_TYPE_UNSIGNED_INTEGER_END	= 8;
	const u32						_VAR_TYPE_NUMERIC_INTEGER_END	= 8;

	// Floating point
	const u32				_VAR_TYPE_NUMERIC_FLOATING_POINT_START	= 9;
	const u32		_VAR_TYPE_NUMERIC								= 9;	// Stored as a character (like "200.50"), but converted to numeric at each reference.
	const u32		_VAR_TYPE_F32									= 10;	// _VAR_TYPE_SINGLE
	const u32		_VAR_TYPE_F64									= 11;	// _VAR_TYPE_DOUBLE
	const u32		_VAR_TYPE_CURRENCY								= 12;	// Stored as an s64 with an implied 4-decimals (divide by 10,000 to get the actual floating point value)
	const u32						_VAR_TYPE_BIG_NUMBER_START		= 13;
	const u32		_VAR_TYPE_BFP									= 13;	// Uses the big number library for floating points
	const u32				_VAR_TYPE_NUMERIC_FLOATING_POINT_END	= 13;
	const u32		_VAR_TYPE_BI									= 14;	// Uses the big number library for integers
	const u32						_VAR_TYPE_NUMERIC_END			= 14;
	const u32						_VAR_TYPE_BIG_NUMBER_END		= 14;

	// Fundamental types
	const u32		_VAR_TYPE_CHARACTER								= 15;
	const u32		_VAR_TYPE_UNICODE								= 16;
	const u32		_VAR_TYPE_DATE									= 17;
	const u32		_VAR_TYPE_DATETIME								= 18;
	const u32		_VAR_TYPE_DATETIMEX								= 19;
	const u32		_VAR_TYPE_LOGICAL								= 20;	// Note:  This includes the logicalx types, but the value stored determines the logicalx setting.
	const u32		_VAR_TYPE_GUID8									= 21;
	const u32		_VAR_TYPE_GUID16								= 22;
	const u32		_VAR_TYPE_FIELD									= 23;
	const u32		_VAR_TYPE_VECTOR								= 24;	// A vector format of multiple items with symbols between, like an ip4 address comprised of integers, 1.2.3.4, or a version 1.2.3. Support for ip6 hex:hex:hex:hex values will also be supported as vectors.

	// Extended variable types
	const u32						_VAR_TYPE_EXTENDED_START		= 25;
	const u32		_VAR_TYPE_OBJECT								= 25;	// Object reference
	const u32		_VAR_TYPE_BITMAP								= 26;	// Image reference
	const u32		_VAR_TYPE_BITMAP_MOVIE							= 27;	// Image sequence reference
	const u32		_VAR_TYPE_THISCODE								= 28;	// Code reference
	const u32		_VAR_TYPE_ARRAY									= 29;	// An array of SVariable* following three 4-byte integers indicating row dimensions.
	const u32		_VAR_TYPE_IDISPATCH								= 30;	// IDispatch object reference
	const u32						_VAR_TYPE_EXTENDED_END			= 30;
	const u32						_VAR_TYPE_END					= 30;


//////////
// For DECLARE DLL operations
//////
	const u32		_VAR_TYPE_DLL_UNDEFINED							= _VAR_TYPE_NONE;
	const u32		_VAR_TYPE_DLL_SHORT								= _VAR_TYPE_S16;
	const u32		_VAR_TYPE_DLL_INTEGER							= _VAR_TYPE_S32;
	const u32		_VAR_TYPE_DLL_SINGLE							= _VAR_TYPE_F32;
	const u32		_VAR_TYPE_DLL_DOUBLE							= _VAR_TYPE_F64;
	const u32		_VAR_TYPE_DLL_LONG								= _VAR_TYPE_S64;
	const u32		_VAR_TYPE_DLL_STRING							= _VAR_TYPE_CHARACTER;
	const u32		_VAR_TYPE_DLL_OBJECT							= _VAR_TYPE_OBJECT;


//////////
// Constants related to the varType values above
//////
	const s32		_DATETIME_BLANK_DATETIME_JULIAN					= -1;
	const f32		_DATETIME_BLANK_DATETIME_SECONDS				= -1.0f;


//////////
// Translate between variable types, and their corresponding unique variable type codes
//////
	SVarTypeXlat	gsVarTypeXlat[] =	 {	{	_VAR_TYPE_NULL,							cgc_null,			sizeof(cgc_null)		 - 1	},
											{	_VAR_TYPE_S8,							cgc_s8,				sizeof(cgc_s8)			 - 1	},
											{	_VAR_TYPE_S16,							cgc_s16,			sizeof(cgc_s16)			 - 1	},
											{	_VAR_TYPE_S32,							cgc_s32,			sizeof(cgc_s32)			 - 1	},
											{	_VAR_TYPE_S64,							cgc_s64,			sizeof(cgc_s64)			 - 1	},
											{	_VAR_TYPE_U8,							cgc_u8,				sizeof(cgc_u8)			 - 1	},
											{	_VAR_TYPE_U16,							cgc_u16,			sizeof(cgc_u16)			 - 1	},
											{	_VAR_TYPE_U32,							cgc_u32,			sizeof(cgc_u32)			 - 1	},
											{	_VAR_TYPE_U64,							cgc_u64,			sizeof(cgc_u64)			 - 1	},
											{	_VAR_TYPE_NUMERIC,						cgc_numeric,		sizeof(cgc_numeric)		 - 1	},
											{	_VAR_TYPE_F32,							cgc_f32,			sizeof(cgc_f32)			 - 1	},
											{	_VAR_TYPE_F64,							cgc_f64,			sizeof(cgc_f64)			 - 1	},
											{	_VAR_TYPE_CURRENCY,						cgc_currency,		sizeof(cgc_currency)	 - 1	},
											{	_VAR_TYPE_BFP,							cgc_bfp,			sizeof(cgc_bfp)			 - 1	},
											{	_VAR_TYPE_BI,							cgc_bi,				sizeof(cgc_bi)			 - 1	},
											{	_VAR_TYPE_CHARACTER,					cgc_character,		sizeof(cgc_character)	 - 1	},
											{	_VAR_TYPE_UNICODE,						cgc_unicode,		sizeof(cgc_unicode)		 - 1	},
											{	_VAR_TYPE_DATE,							cgc_date,			sizeof(cgc_date)		 - 1	},
											{	_VAR_TYPE_DATETIME,						cgc_datetime,		sizeof(cgc_datetime)	 - 1	},
											{	_VAR_TYPE_DATETIMEX,					cgc_datetimex,		sizeof(cgc_datetimex)	 - 1	},
											{	_VAR_TYPE_LOGICAL,						cgc_logical,		sizeof(cgc_logical)		 - 1	},
											{	_VAR_TYPE_GUID8,						cgc_guid8,			sizeof(cgc_guid8)		 - 1	},
											{	_VAR_TYPE_GUID16,						cgc_guid16,			sizeof(cgc_guid16)		 - 1	},
											{	_VAR_TYPE_FIELD,						cgc_field,			sizeof(cgc_field)		 - 1	},
											{	_VAR_TYPE_VECTOR,						cgc_vector,			sizeof(cgc_vector)		 - 1	},
											{	_VAR_TYPE_OBJECT,						cgc_object,			sizeof(cgc_object)		 - 1	},
											{	_VAR_TYPE_BITMAP,						cgc_bitmap,			sizeof(cgc_bitmap)		 - 1	},
											{	_VAR_TYPE_BITMAP_MOVIE,					cgc_bitmap_movie,	sizeof(cgc_bitmap_movie) - 1	},
											{	_VAR_TYPE_THISCODE,						cgc_thiscode,		sizeof(cgc_thiscode)	 - 1	},
											{	_VAR_TYPE_ARRAY,						cgc_array,			sizeof(cgc_array)		 - 1	}		};
