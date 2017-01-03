//////////
//
// /libsf/exodus/tools/rdc/rdc_globals.h
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
// Copyright (c) 2014-2017 by Rick C. Hodgin
//////
// Last update:
//     Nov.02.2014
//////
// Change log:
//     Nov.02.2014 - Initial creation
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
// Syntax highlight colors for RDC
//////
	SBgra			colorSynHi_type					= { rgba(0, 128, 192, 255) };			// Cyanish




//////////
// iCodes specific to RDC
//////
	cs32		_ICODE_VOID				    = 200000;
	cs32		_ICODE_BOOL				    = 200001;
	cs32		_ICODE_CHAR				    = 200002;
	cs32		_ICODE_DATUM				= 200003;
	cs32		_ICODE_THREAD				= 200004;
	cs32		_ICODE_PROCESS				= 200005;
	cs32		_ICODE_CONST				= 200006;
	cs32		_ICODE_READONLY				= 200007;
	cs32		_ICODE_READWRITE			= 200008;
	cs32		_ICODE_VOLATILE				= 200009;
	cs32		_ICODE_UNSIGNED				= 200010;
	cs32		_ICODE_STATIC				= 200011;
	cs32		_ICODE_EXTERN				= 200012;
	cs32		_ICODE_SIZEOF				= 200013;
	cs32		_ICODE_OFFSETOF				= 200014;
	cs32		_ICODE_NULL_POINTER			= 200015;
	cs32		_ICODE_NULL_VALUE			= 200016;
	cs32		_ICODE_PRAGMA_DEFINE		= 200017;
	cs32		_ICODE_PRAGMA_UNDEFINE		= 200018;
	cs32		_ICODE_PRAGMA_IF			= 200019;
	cs32		_ICODE_PRAGMA_IFDEF			= 200020;
	cs32		_ICODE_PRAGMA_IFNDEF		= 200021;
	cs32		_ICODE_PRAGMA_ELSE			= 200022;
	cs32		_ICODE_PRAGMA_ELSEIF		= 200023;
	cs32		_ICODE_PRAGMA_ENDIF			= 200024;
	cs32		_ICODE_PRAGMA_ALIGN			= 200025;
	cs32		_ICODE_PRAGMA_PUSH			= 200026;
	cs32		_ICODE_PRAGMA_POP			= 200027;
	cs32		_ICODE_PRAGMA_TYPEDEF		= 200028;
	cs32		_ICODE_STRUCT				= 200029;
	cs32		_ICODE_EXTENDS				= 200030;
	cs32		_ICODE_CHILD				= 200031;
	cs32		_ICODE_UNION				= 200032;
	cs32		_ICODE_ENUM				    = 200033;
	cs32		_ICODE_NEW					= 200034;
	cs32		_ICODE_UNTIL				= 200035;
	cs32		_ICODE_ITERATE				= 200036;
	cs32		_ICODE_UNLESS				= 200037;
	cs32		_ICODE_ELSEIF				= 200038;
	cs32		_ICODE_SWITCH				= 200039;
	cs32		_ICODE_ANDIN				= 200040;
	cs32		_ICODE_OUT					= 200041;
	cs32		_ICODE_TIMEOUT				= 200042;
	cs32		_ICODE_SUCCESS				= 200043;
	cs32		_ICODE_ENGAGE				= 200044;
	cs32		_ICODE_UNENGAGE				= 200045;
	cs32		_ICODE_BREAK				= 200046;
	cs32		_ICODE_BREAK_TO				= 200047;
	cs32		_ICODE_CONTINUE_TO			= 200048;
	cs32		_ICODE_EXIT_TO              = 200049;
	cs32		_ICODE_LOOP_TO				= 200050;
	cs32		_ICODE_FLOWOUT_TO			= 200051;
	cs32		_ICODE_DLLMAIN				= 200052;
// 	cs32		_ICODE_SHORT				= 200053;
// 	cs32		_ICODE_LONG					= 200054;
	cs32		_ICODE_PURPOSE				= 200055;
	cs32		_ICODE_ROLL					= 200056;
	cs32		_ICODE_SUPER				= 200057;

	cs32		_ICAT_TYPE					= 200000;




//////////
// Keywords for RDC
//////
	SAsciiCompSearcher	cgcKeywordsRdc[] =
	{
		// keyword					length		repeats?	extra (type)							first on line?		category			syntax highlight color		syntax highlight bold		onFind()	compilerDictionaryLookup()
		{ "void",					4,			false,		_ICODE_VOID,							false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },
		{ "bool",					4,			false,		_ICODE_BOOL,							false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },
		{ "char",					4,			false,		_ICODE_CHAR,							false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },
		{ "short",					5,			false,		_ICODE_SHORT,							false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },
		{ "int",					3,			false,		_ICODE_INT,								false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },
		{ "long",					4,			false,		_ICODE_LONG,							false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },
		{ "float",					5,			false,		_ICODE_FLOAT,							false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },
		{ "double",					6,			false,		_ICODE_DOUBLE,							false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },
		{ "alias",					5,			false,		_ICODE_ALIAS,							false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },

		{ "s8",						2,			false,		_ICODE_S8,								false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },
		{ "u8",						2,			false,		_ICODE_U8,								false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },
		{ "s16",					3,			false,		_ICODE_S16,								false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },
		{ "u16",					3,			false,		_ICODE_U16,								false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },
		{ "s32",					3,			false,		_ICODE_S32,								false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },
		{ "u32",					3,			false,		_ICODE_U32,								false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },
		{ "s64",					3,			false,		_ICODE_S64,								false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },
		{ "u64",					3,			false,		_ICODE_U64,								false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },
		{ "f32",					3,			false,		_ICODE_F32,								false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },
		{ "f64",					3,			false,		_ICODE_F64,								false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },

		{ "bi",						2,			false,		_ICODE_BI,								false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },
		{ "bfp",					3,			false,		_ICODE_BFP,								false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },
		{ "datum",					5,			false,		_ICODE_DATUM,							false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },
		{ "date",					4,			false,		_ICODE_DATE,							false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },
		{ "datetime",				8,			false,		_ICODE_DATETIME,						false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },
		{ "datetimex",				9,			false,		_ICODE_DATETIMEX,						false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },
		{ "thread",					6,			false,		_ICODE_THREAD,							false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },
		{ "process",				7,			false,		_ICODE_PROCESS,							false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },

		{ "const",					5,			false,		_ICODE_CONST,							false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },
		{ "ro",						2,			false,		_ICODE_READONLY,						false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },
		{ "rw",						2,			false,		_ICODE_READWRITE,						false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },
		{ "volatile",				8,			false,		_ICODE_VOLATILE,						false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },
		{ "hide",					4,			false,		_ICODE_HIDE,							false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },
		{ "unsigned",				8,			false,		_ICODE_UNSIGNED,						false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },
		{ "static",					5,			false,		_ICODE_STATIC,							false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },
		{ "extern",					5,			false,		_ICODE_EXTERN,							false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },
		{ "sizeof",					5,			false,		_ICODE_SIZEOF,							false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },
		{ "offsetof",				7,			false,		_ICODE_OFFSETOF,						false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },

		// Signed compare on these tokens, so length is negative
		{ "NULL",					-4,			false,		_ICODE_NULL_POINTER,					false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },
		{ "null",					-4,			false,		_ICODE_NULL_VALUE,						false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },
		{ "null0",					-5,			false,		_ICODE_NULL_VALUE,						false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },

		{ "true",					4,			false,		_ICODE_TRUE,							false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },
		{ "yes",					3,			false,		_ICODE_TRUE,							false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },
		{ "false",					4,			false,		_ICODE_FALSE,							false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },
		{ "no",						2,			false,		_ICODE_FALSE,							false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },

		{ "and",					3,			false,		_ICODE_AND,								false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },
		{ "or",						2,			false,		_ICODE_OR,								false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },
		{ "not",					3,			false,		_ICODE_NOT,								false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },

		{ "#define",				7,			false,		_ICODE_PRAGMA_DEFINE,					false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },
		{ "#undefine",				9,			false,		_ICODE_PRAGMA_UNDEFINE,					false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },
		{ "#if",					3,			false,		_ICODE_PRAGMA_IF,						false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },
		{ "#ifdef",					6,			false,		_ICODE_PRAGMA_IFDEF,					false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },
		{ "#ifndef",				7,			false,		_ICODE_PRAGMA_IFNDEF,					false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },
		{ "#else",					5,			false,		_ICODE_PRAGMA_ELSE,						false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },
		{ "#elseif",				7,			false,		_ICODE_PRAGMA_ELSEIF,					false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },
		{ "#endif",					6,			false,		_ICODE_PRAGMA_ENDIF,					false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },
		{ "#align",					6,			false,		_ICODE_PRAGMA_ALIGN,					false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },
		{ "#push",					5,			false,		_ICODE_PRAGMA_PUSH,						false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },
		{ "#pop",					4,			false,		_ICODE_PRAGMA_POP,						false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },
		{ "typedef",				7,			false,		_ICODE_PRAGMA_TYPEDEF,					false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },

		{ "struct",					6,			false,		_ICODE_STRUCT,							false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },
		{ "class",					5,			false,		_ICODE_CLASS,							false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },
		{ "operator",				8,			false,		_ICODE_OPERATOR,						false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },
		{ "extends",				7,			false,		_ICODE_EXTENDS,							false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },
		{ "parent",					6,			false,		_ICODE_PARENT,							false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },
		{ "child",					5,			false,		_ICODE_CHILD,							false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },
		{ "union",					5,			false,		_ICODE_UNION,							false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },
		{ "enum",					4,			false,		_ICODE_ENUM,							false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },
		{ "new",					3,			false,		_ICODE_NEW,								false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },
		{ "delete",					6,			false,		_ICODE_DELETE,							false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },

		{ "adhoc",					5,			false,		_ICODE_DELETE,							false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },
		{ "function",				8,			false,		_ICODE_DELETE,							false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },
		{ "purpose",				7,			false,		_ICODE_PURPOSE,							false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },
		{ "params",					6,			false,		_ICODE_DELETE,							false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },
		{ "returns",				7,			false,		_ICODE_DELETE,							false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },
		{ "inline",					6,			false,		_ICODE_DELETE,							false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },
		{ "optimize",				8,			false,		_ICODE_DELETE,							false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },
		{ "nodebug",				7,			false,		_ICODE_DELETE,							false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },
		{ "breakpoint",				10,			false,		_ICODE_DELETE,							false,				_ICAT_TYPE,			&colorSynHi_type,			false,						null0,		null0 },

		{ "do",						2,			false,		_ICODE_DO,								false,				_ICAT_GENERIC,		&colorSynHi_command,		true,						null0,		null0 },
		{ "while",					5,			false,		_ICODE_WHILE,							false,				_ICAT_GENERIC,		&colorSynHi_command,		true,						null0,		null0 },
		{ "until",					5,			false,		_ICODE_UNTIL,							false,				_ICAT_GENERIC,		&colorSynHi_command,		true,						null0,		null0 },
		{ "iterate",				8,			false,		_ICODE_ITERATE,							false,				_ICAT_GENERIC,		&colorSynHi_command,		true,						null0,		null0 },
		{ "for",					3,			false,		_ICODE_FOR,								false,				_ICAT_GENERIC,		&colorSynHi_command,		true,						null0,		null0 },
		{ "unless",					6,			false,		_ICODE_UNLESS,							false,				_ICAT_GENERIC,		&colorSynHi_command,		true,						null0,		null0 },
		{ "roll",					4,			false,		_ICODE_ROLL,							false,				_ICAT_GENERIC,		&colorSynHi_command,		true,						null0,		null0 },
		{ "if",						2,			false,		_ICODE_IF,								false,				_ICAT_GENERIC,		&colorSynHi_command,		true,						null0,		null0 },
		{ "else",					4,			false,		_ICODE_ELSE,							false,				_ICAT_GENERIC,		&colorSynHi_command,		true,						null0,		null0 },
		{ "elseif",					6,			false,		_ICODE_ELSEIF,							false,				_ICAT_GENERIC,		&colorSynHi_command,		true,						null0,		null0 },
		{ "lif",					3,			false,		_ICODE_LIF,								false,				_ICAT_GENERIC,		&colorSynHi_command,		true,						null0,		null0 },
		{ "lelse",					5,			false,		_ICODE_LELSE,							false,				_ICAT_GENERIC,		&colorSynHi_command,		true,						null0,		null0 },
		{ "lelseif",				7,			false,		_ICODE_LELSEIF,							false,				_ICAT_GENERIC,		&colorSynHi_command,		true,						null0,		null0 },
		{ "fif",					3,			false,		_ICODE_FIF,								false,				_ICAT_GENERIC,		&colorSynHi_command,		true,						null0,		null0 },
		{ "felseif",				7,			false,		_ICODE_FELSEIF,							false,				_ICAT_GENERIC,		&colorSynHi_command,		true,						null0,		null0 },
		{ "switch",					6,			false,		_ICODE_SWITCH,							false,				_ICAT_GENERIC,		&colorSynHi_command,		true,						null0,		null0 },
		{ "case",					4,			false,		_ICODE_CASE,							false,				_ICAT_GENERIC,		&colorSynHi_command,		true,						null0,		null0 },
		{ "meta",					4,			false,		_ICODE_META,							false,				_ICAT_GENERIC,		&colorSynHi_command,		true,						null0,		null0 },
		{ "mefa",					4,			false,		_ICODE_MEFA,							false,				_ICAT_GENERIC,		&colorSynHi_command,		true,						null0,		null0 },
		{ "quit",					4,			false,		_ICODE_QUIT,							false,				_ICAT_GENERIC,		&colorSynHi_command,		true,						null0,		null0 },

		{ "in",						2,			false,		_ICODE_IN,								false,				_ICAT_GENERIC,		&colorSynHi_command,		true,						null0,		null0 },
		{ "andin",					5,			false,		_ICODE_ANDIN,							false,				_ICAT_GENERIC,		&colorSynHi_command,		true,						null0,		null0 },
		{ "out",					3,			false,		_ICODE_OUT,								false,				_ICAT_GENERIC,		&colorSynHi_command,		true,						null0,		null0 },
		{ "join",					4,			false,		_ICODE_JOIN,							false,				_ICAT_GENERIC,		&colorSynHi_command,		true,						null0,		null0 },
		{ "timeout",				7,			false,		_ICODE_TIMEOUT,							false,				_ICAT_GENERIC,		&colorSynHi_command,		true,						null0,		null0 },
		{ "success",				7,			false,		_ICODE_SUCCESS,							false,				_ICAT_GENERIC,		&colorSynHi_command,		true,						null0,		null0 },

		{ "engage",					6,			false,		_ICODE_ENGAGE,							false,				_ICAT_GENERIC,		&colorSynHi_command,		true,						null0,		null0 },
		{ "unengage",				8,			false,		_ICODE_UNENGAGE,						false,				_ICAT_GENERIC,		&colorSynHi_command,		true,						null0,		null0 },

		{ "default",				7,			false,		_ICODE_DEFAULT,							false,				_ICAT_GENERIC,		&colorSynHi_command,		true,						null0,		null0 },
		{ "break",					5,			false,		_ICODE_BREAK,							false,				_ICAT_GENERIC,		&colorSynHi_command,		true,						null0,		null0 },
		{ "breakto",				7,			false,		_ICODE_BREAK_TO,						false,				_ICAT_GENERIC,		&colorSynHi_command,		true,						null0,		null0 },
		{ "continue",				8,			false,		_ICODE_CONTINUE,						false,				_ICAT_GENERIC,		&colorSynHi_command,		true,						null0,		null0 },
		{ "continueto",				10,			false,		_ICODE_CONTINUE_TO,						false,				_ICAT_GENERIC,		&colorSynHi_command,		true,						null0,		null0 },
		{ "exit",					4,			false,		_ICODE_EXIT,							false,				_ICAT_GENERIC,		&colorSynHi_command,		true,						null0,		null0 },
		{ "exitto",					6,			false,		_ICODE_EXIT_TO,							false,				_ICAT_GENERIC,		&colorSynHi_command,		true,						null0,		null0 },
		{ "loop",					4,			false,		_ICODE_LOOP,							false,				_ICAT_GENERIC,		&colorSynHi_command,		true,						null0,		null0 },
		{ "loopto",					6,			false,		_ICODE_LOOP_TO,							false,				_ICAT_GENERIC,		&colorSynHi_command,		true,						null0,		null0 },
		{ "goto",					4,			false,		_ICODE_GOTO,							false,				_ICAT_GENERIC,		&colorSynHi_command,		true,						null0,		null0 },
		{ "return",					4,			false,		_ICODE_RETURN,							false,				_ICAT_GENERIC,		&colorSynHi_command,		true,						null0,		null0 },

		{ "flow",					4,			false,		_ICODE_FLOW,							false,				_ICAT_GENERIC,		&colorSynHi_command,		true,						null0,		null0 },
		{ "flowout",				7,			false,		_ICODE_FLOWOUT,							false,				_ICAT_GENERIC,		&colorSynHi_command,		true,						null0,		null0 },
		{ "flowoutto",				9,			false,		_ICODE_FLOWOUT_TO,						false,				_ICAT_GENERIC,		&colorSynHi_command,		true,						null0,		null0 },
		{ "flowto",					6,			false,		_ICODE_FLOWTO,							false,				_ICAT_GENERIC,		&colorSynHi_command,		true,						null0,		null0 },
		{ "subflow",				7,			false,		_ICODE_SUBFLOW,							false,				_ICAT_GENERIC,		&colorSynHi_command,		true,						null0,		null0 },
		{ "meia",					4,			false,		_ICODE_MEIA,							false,				_ICAT_GENERIC,		&colorSynHi_command,		true,						null0,		null0 },
		{ "mema",					4,			false,		_ICODE_MEMA,							false,				_ICAT_GENERIC,		&colorSynHi_command,		true,						null0,		null0 },

		{ "flowof",					6,			false,		_ICODE_FLOWOF,							false,				_ICAT_GENERIC,		&colorSynHi_command,		true,						null0,		null0 },
		{ "super",					5,			false,		_ICODE_SUPER,							false,				_ICAT_GENERIC,		&colorSynHi_command,		true,						null0,		null0 },

		{ "main",					4,			false,		_ICODE_MAIN,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },
		{ "dllmain",				4,			false,		_ICODE_DLLMAIN,							false,				_ICAT_GENERIC,		&colorSynHi_command,		false,						null0,		null0 },

		// Terminates the list
		{ 0,						0,			0,			0,										0,					0,					0,							0,							0,			0 }
	};
