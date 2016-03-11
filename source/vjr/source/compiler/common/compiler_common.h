//////////
//
// /libsf/source/vjr/source/compiler/common/compiler_common.h
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
// Copyright (c) 2014-2015 by Rick C. Hodgin
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
// Constant integers
//////
	cu32			_COMMON_START_END_BLOCK_SIZE					= 32;			// Allocate 32 entries/slots at a time (Start/end)
	cu32			_COMMON_START_END_SMALL_BLOCK_SIZE				= 4;			// Allocate 4 entries/slots at a time (Start/end)
	cu32			_COMMON_START_END_BIG_BLOCK_SIZE				= 256;			// Allocate 256 entries/slots at a time (Start/end)
	cu32			_COMMON_BUILDER_BLOCK_SIZE						= 16384;		// Allocate 16KB at a time
	cu32			_COMMON_BUILDER_BLOCK_SIZE_BIG					= 10240000;		// Allocate 1MB at a time


//////////
// iCat values
// Note:  Use the macro iCat() to read only the lower portion without the upper bits set
//////
	const u32		_ICAT_GENERIC									= 0;
	const u32		_ICAT_COMMAND									= 1;
	const u32		_ICAT_FUNCTION									= 2;
	const u32		_ICAT_FLOW										= 3;
	const u32		_ICAT_OPERATOR									= 4;	// + - * / 
	const u32		_ICAT_CASK										= 5;	// (|cask|), etc.
	const u32		_ICAT_OPTION									= 6;	// An option like "AGAIN" on "USE xyz AGAIN"
	const u32		_ICAT_PRAGMA									= 7;	// #something
	const u32		_ICAT_DESCENT									= 8;	// ( [ { {{
	const u32		_ICAT_ASCENT									= 9;	// ) ] } }}
	const u32		_ICAT_PARAM										= 10;	// ,
	const u32		_ICAT_REFERENCE									= 11;	// @
	const u32		_ICAT_SCOPE										= 12;	// ::
	const u32		_ICAT_RANGE										= 13;	// ..
	const u32		_ICAT_COMMENT									= 14;	// * /* */ /+ +/ && //
	const u32		_ICAT_DEFINITION								= 15;	// Definition keyword, function, adhoc, struct, class, union, enum, etc.
	// Bit settings
	const u32		_ICAT_DOT										= 1 << 25;
	const u32		_ICAT_LOGIC										= 1 << 26;
	const u32		_ICAT_UNARY										= 1 << 27;
	const u32		_ICAT_BITWISE									= 1 << 28;
	const u32		_ICAT_ASSIGN									= 1 << 29;
	const u32		_ICAT_ASSIGN_OP									= 1 << 30;
	const u32		_ICAT_STOPPER									= 1 << 31;
	const u32		_ICAT_MASK										= _ICAT_DOT | _ICAT_LOGIC | _ICAT_UNARY | _ICAT_BITWISE | _ICAT_ASSIGN | _ICAT_ASSIGN_OP | _ICAT_STOPPER;


/////////
// iCode values
//////
	cs32						_ICODE_CASK_SIDE_MINIMUM			= 1000001;
	cs32			_ICODE_CASK_ROUND_OPEN_PARAMS					= 1000001;
	cs32			_ICODE_CASK_ROUND_CLOSE_PARAMS					= 1000002;
	cs32			_ICODE_CASK_SQUARE_OPEN_PARAMS					= 1000003;
	cs32			_ICODE_CASK_SQUARE_CLOSE_PARAMS					= 1000004;
	cs32			_ICODE_CASK_TRIANGLE_OPEN_PARAMS				= 1000005;
	cs32			_ICODE_CASK_TRIANGLE_CLOSE_PARAMS				= 1000006;
	cs32			_ICODE_CASK_UTILITY_OPEN_PARAMS					= 1000007;
	cs32			_ICODE_CASK_UTILITY_CLOSE_PARAMS				= 1000008;
	cs32			_ICODE_CASK_CODE_OPEN_PARAMS					= 1000009;
	cs32			_ICODE_CASK_CODE_CLOSE_PARAMS					= 1000010;
	cs32			_ICODE_CASK_AUTO_OPEN_PARAMS					= 1000011;
	cs32			_ICODE_CASK_AUTO_CLOSE_PARAMS					= 1000012;
	cs32			_ICODE_CASK_ROUND_OPEN							= 1000013;
	cs32			_ICODE_CASK_ROUND_CLOSE							= 1000014;
	cs32			_ICODE_CASK_SQUARE_OPEN							= 1000015;
	cs32			_ICODE_CASK_SQUARE_CLOSE						= 1000016;
	cs32			_ICODE_CASK_TRIANGLE_OPEN						= 1000017;
	cs32			_ICODE_CASK_TRIANGLE_CLOSE						= 1000018;
	cs32			_ICODE_CASK_UTILITY_OPEN						= 1000019;
	cs32			_ICODE_CASK_UTILITY_CLOSE						= 1000020;
	cs32			_ICODE_CASK_CODE_OPEN							= 1000021;
	cs32			_ICODE_CASK_CODE_CLOSE							= 1000022;
	cs32			_ICODE_CASK_AUTO_OPEN							= 1000023;
	cs32			_ICODE_CASK_AUTO_CLOSE							= 1000024;
	cs32						_ICODE_CASK_SIDE_MAXIMUM			= 1000024;

	cs32						_ICODE_CASK_MINIMUM					= 1000101;
	cs32			_ICODE_CASK_ROUND_PARAMS						= 1000101;
	cs32			_ICODE_CASK_SQUARE_PARAMS						= 1000102;
	cs32			_ICODE_CASK_TRIANGLE_PARAMS						= 1000103;
	cs32			_ICODE_CASK_TILDE_PARAMS						= 1000104;
	cs32			_ICODE_CASK_CODE_PARAMS							= 1000105;
	cs32			_ICODE_CASK_AUTO_PARAMS							= 1000106;
	cs32			_ICODE_CASK_ROUND								= 1000107;
	cs32			_ICODE_CASK_SQUARE								= 1000108;
	cs32			_ICODE_CASK_TRIANGLE							= 1000109;
	cs32			_ICODE_CASK_TILDE								= 1000110;
	cs32			_ICODE_CASK_CODE								= 1000111;
	cs32			_ICODE_CASK_AUTO								= 1000112;
	cs32						_ICODE_CASK_MAXIMUM					= 1000112;

	// Standard types
	cs32			_ICODE_UNKNOWN									= -1;
	cs32			_ICODE_ALPHA									= 1;
	cs32			_ICODE_NUMERIC									= 2;
	cs32			_ICODE_ALPHANUMERIC								= 3;
	cs32			_ICODE_OPERATOR									= 4;
	cs32			_ICODE_WHITESPACE								= 5;
	cs32			_ICODE_PLUS										= 6;
	cs32			_ICODE_MINUS								= 7;
	cs32			_ICODE_HYPHEN								= 7;
	cs32			_ICODE_ASTERISK								= 8;
	cs32			_ICODE_MULTIPLY								= 8;
	cs32			_ICODE_BACKSLASH								= 9;
	cs32			_ICODE_DOUBLE_QUOTE								= 10;
	cs32			_ICODE_SINGLE_QUOTE								= 11;
	cs32			_ICODE_TILDE									= 12;
	cs32			_ICODE_DOT										= 13;
	cs32			_ICODE_COLON									= 14;
	cs32			_ICODE_COMMA									= 15;
	cs32			_ICODE_UNDERSCORE								= 16;
	cs32			_ICODE_AT_SIGN									= 17;
	cs32			_ICODE_QUESTION_MARK							= 18;
	cs32			_ICODE_EXCLAMATION_POINT						= 19;
	cs32			_ICODE_POUND_SIGN								= 20;
	cs32			_ICODE_PERCENT_SIGN								= 21;
	cs32			_ICODE_EXPONENT								= 22;			// ^
	cs32			_ICODE_XOR									= 22;
	cs32			_ICODE_AMPERSAND								= 23;
	cs32			_ICODE_EQUAL_SIGN								= 24;
	cs32			_ICODE_PIPE_SIGN								= 25;
	cs32			_ICODE_REVERSE_QUOTE							= 26;
	cs32			_ICODE_SEMICOLON								= 27;
	cs32			_ICODE_GREATER_THAN								= 28;
	cs32			_ICODE_LESS_THAN								= 30;
	cs32			_ICODE_PARENTHESIS_LEFT							= 31;
	cs32			_ICODE_PARENTHESIS_RIGHT						= 32;
	cs32			_ICODE_BRACKET_LEFT								= 33;
	cs32			_ICODE_BRACKET_RIGHT							= 34;
	cs32			_ICODE_BRACE_LEFT								= 35;
	cs32			_ICODE_BRACE_RIGHT								= 36;
	cs32			_ICODE_SLASH									= 37;
	cs32			_ICODE_FOUND_IN									= 38;
	cs32			_ICODE_PLUS_PLUS								= 39;
	cs32			_ICODE_MINUS_MINUS								= 40;
	cs32			_ICODE_NOT_EQUAL								= 41;
	cs32			_ICODE_LESS_THAN_OR_EQUAL_TO					= 42;
	cs32			_ICODE_GREATER_THAN_OR_EQUAL_TO					= 43;
	cs32			_ICODE_EXACTLY_EQUAL_TO							= 44;
	cs32			_ICODE_NOT_FOUND_IN								= 45;
	cs32			_ICODE_SHIFT_LEFT								= 46;
	cs32			_ICODE_SHIFT_RIGHT								= 47;
	cs32			_ICODE_SHIFT_LEFT_ASSIGNMENT					= 48;
	cs32			_ICODE_SHIFT_RIGHT_ASSIGNMENT					= 49;
	cs32			_ICODE_RANGE									= 50;
	cs32			_ICODE_ADD_EQUAL								= 51;
	cs32			_ICODE_MINUS_EQUAL								= 52;
	cs32			_ICODE_XOR_EQUAL								= 53;
	cs32			_ICODE_MULTIPLY_EQUAL							= 54;
	cs32			_ICODE_DIVIDE_EQUAL								= 55;
	cs32			_ICODE_MODULO_EQUAL								= 56;
	cs32			_ICODE_OR_ASSIGNMENT							= 57;
	cs32			_ICODE_DOLLAR_SIGN								= 58;
	cs32			_ICODE_DOUBLE_BRACE_LEFT						= 59;
	cs32			_ICODE_DOUBLE_BRACE_RIGHT						= 60;
	cs32			_ICODE_SCOPE									= 61;

	// Preprocessor
	cs32			_ICODE_DEFINE_PRAGMA							= 101;
	cs32			_ICODE_ELSE_PRAGMA								= 102;
	cs32			_ICODE_ELSEIF_PRAGMA							= 103;
	cs32			_ICODE_IF_PRAGMA								= 104;
	cs32			_ICODE_IFDEF_PRAGMA								= 105;
	cs32			_ICODE_IFNDEF_PRAGMA							= 106;
	cs32			_ICODE_INCLUDE_PRAGMA							= 107;
	cs32			_ICODE_UNDEF_PRAGMA								= 108;
	cs32			_ICODE_ENDIF_PRAGMA								= 109;

	// Miscellaneous
	cs32			_ICODE_COMMENT									= 150;
	cs32			_ICODE_LINE_COMMENT								= 151;
	cs32			_ICODE_COMMENT_START							= 152;
	cs32			_ICODE_COMMENT_END								= 153;

	// Logical operators
	const s32		_ICODE_NOT										= 500;
	const s32		_ICODE_AND										= 501;
	const s32		_ICODE_OR										= 502;




//////////
// Syntax highlight colors
//////
	SBgra			colorSynHi_comment1					= { rgba(0, 148, 0, 255) };				// Green
	SBgra			colorSynHi_comment2					= { rgba(148, 64, 148, 255) };			// Green+Cyan
	SBgra			colorSynHi_comment3					= { rgba(148, 64, 148, 255) };			// Dark purple
	SBgra			colorSynHi_function					= { rgba(164, 128, 0, 255) };			// Golden
	SBgra			colorSynHi_command					= { rgba(64, 128, 245, 255) };			// Pastel cyan-blue
	SBgra			colorSynHi_logical					= { rgba(200, 148, 0, 255) };			// Orange
	SBgra			colorSynHi_numeric					= { rgba(0, 128, 255, 255) };			// Cyan-blue
	SBgra			colorSynHi_operator					= { rgba(128, 0, 164, 255) };			// Purplish
	SBgra			colorSynHi_bracket					= { rgba(128, 0, 0, 255) };				// Red
	SBgra			colorSynHi_pragmas					= { rgba(192, 192, 192, 255) };			// Gray
	SBgra			colorSynHi_variable					= { rgba(255, 128, 0, 255) };			// Orange
	SBgra			colorSynHi_quotedText				= { rgba(235, 128, 128, 255) };			// Reddish




//////////
// Added to identify any tokens in alpha blocks which may have non-breaking-space characters
// The comp->nbspCount allows them to be rendered properly in displayed form
//////
	void ii_onFind_countNbsp(SAsciiCompSearcher* tacs, SComp* comp)
	{
		s32 lnI;


		//////////
		// Iterate through every character counting the nbsp
		//////
			for (lnI = 0; lnI < comp->length; lnI++)
			{
				// If it's a nbsp, increase the count
				if (comp->line->sourceCode->data._u8[comp->start + lnI] == 255)
					++comp->nbspCount;
			}
	}




//////////
// Casks
//////
	cs8			cgcCaskRoundOpenParams[]						= "(||";
	cs8			cgcCaskRoundCloseParams[]						= "||)";
	cs8			cgcCaskSquareOpenParams[]						= "[||";
	cs8			cgcCaskSquareCloseParams[]						= "||]";
	cs8			cgcCaskTriangleOpenParams[]						= "<||";
	cs8			cgcCaskTriangleCloseParams[]					= "||>";
	cs8			cgcCaskUtilityOpenParams[]						= "~||";
	cs8			cgcCaskUtilityCloseParams[]						= "||~";
	cs8			cgcCaskCodeOpenParams[]							= "\\||";
	cs8			cgcCaskCodeCloseParams[]						= "||/";
	cs8			cgcCaskAutoOpenParams[]							= "/||";
	cs8			cgcCaskAutoCloseParams[]						= "||\\";
	cs8			cgcCaskRoundOpen[]								= "(|";
	cs8			cgcCaskRoundClose[]								= "|)";
	cs8			cgcCaskSquareOpen[]								= "[|";
	cs8			cgcCaskSquareClose[]							= "|]";
	cs8			cgcCaskTriangleOpen[]							= "<|";
	cs8			cgcCaskTriangleClose[]							= "|>";
	cs8			cgcCaskUtilityOpen[]							= "~|";
	cs8			cgcCaskUtilityClose[]							= "|~";
	cs8			cgcCaskCodeOpen[]								= "\\|";
	cs8			cgcCaskCodeClose[]								= "|/";
	cs8			cgcCaskAutoOpen[]								= "/|";
	cs8			cgcCaskAutoClose[]								= "|\\";

	cs8			cgcDefinePragma[]								= "#define";
	cs8			cgcElsePragma[]									= "#else";
	cs8			cgcElseifPragma[]								= "#elseif";
	cs8			cgcEndifPragma[]								= "#endif";
	cs8			cgcIfPragma[]									= "#if";
	cs8			cgcIfdefPragma[]								= "#ifdef";
	cs8			cgcIfndefPragma[]								= "#ifndef";
	cs8			cgcIncludePragma[]								= "#include";
	cs8			cgcUndefPragma[]								= "#undef";




//////////
// Basic symbols known to VXB
/////
	SAsciiCompSearcher	cgcFundamentalSymbols[] =
	{
		// keyword					length		repeats?	extra (type)							first on line?		category						syntax highlight color		syntax highlight bold		onCandidateMatch()		onFind()	compilerDictionaryLookup()
		{ cgcCaskRoundOpenParams,	3,			false,		_ICODE_CASK_ROUND_OPEN_PARAMS,			false,				_ICAT_CASK,						NULL,						false,						null0,					null0,		null0	},
		{ cgcCaskRoundCloseParams,	3,			false,		_ICODE_CASK_ROUND_CLOSE_PARAMS,			false,				_ICAT_CASK,						NULL,						false,						null0,					null0,		null0	},
		{ cgcCaskSquareOpenParams,	3,			false,		_ICODE_CASK_SQUARE_OPEN_PARAMS,			false,				_ICAT_CASK,						NULL,						false,						null0,					null0,		null0	},
		{ cgcCaskSquareCloseParams,	3,			false,		_ICODE_CASK_SQUARE_CLOSE_PARAMS,		false,				_ICAT_CASK,						NULL,						false,						null0,					null0,		null0	},
		{ cgcCaskTriangleOpenParams,3,			false,		_ICODE_CASK_TRIANGLE_OPEN_PARAMS,		false,				_ICAT_CASK,						NULL,						false,						null0,					null0,		null0	},
		{ cgcCaskTriangleCloseParams,3,			false,		_ICODE_CASK_TRIANGLE_CLOSE_PARAMS,		false,				_ICAT_CASK,						NULL,						false,						null0,					null0,		null0	},
		{ cgcCaskUtilityOpenParams,	3,			false,		_ICODE_CASK_UTILITY_OPEN_PARAMS,		false,				_ICAT_CASK,						NULL,						false,						null0,					null0,		null0	},
		{ cgcCaskUtilityCloseParams,3,			false,		_ICODE_CASK_UTILITY_CLOSE_PARAMS,		false,				_ICAT_CASK,						NULL,						false,						null0,					null0,		null0	},
		{ cgcCaskCodeOpenParams,	3,			false,		_ICODE_CASK_CODE_OPEN_PARAMS,			false,				_ICAT_CASK,						NULL,						false,						null0,					null0,		null0	},
		{ cgcCaskCodeCloseParams,	3,			false,		_ICODE_CASK_CODE_CLOSE_PARAMS,			false,				_ICAT_CASK,						NULL,						false,						null0,					null0,		null0	},
		{ cgcCaskAutoOpenParams,	3,			false,		_ICODE_CASK_AUTO_OPEN_PARAMS,			false,				_ICAT_CASK,						NULL,						false,						null0,					null0,		null0	},
		{ cgcCaskAutoCloseParams,	3,			false,		_ICODE_CASK_AUTO_CLOSE_PARAMS,			false,				_ICAT_CASK,						NULL,						false,						null0,					null0,		null0	},
		{ cgcCaskRoundOpen,			2,			false,		_ICODE_CASK_ROUND_OPEN,					false,				_ICAT_CASK,						NULL,						false,						null0,					null0,		null0	},
		{ cgcCaskRoundClose,		2,			false,		_ICODE_CASK_ROUND_CLOSE,				false,				_ICAT_CASK,						NULL,						false,						null0,					null0,		null0	},
		{ cgcCaskSquareOpen,		2,			false,		_ICODE_CASK_SQUARE_OPEN,				false,				_ICAT_CASK,						NULL,						false,						null0,					null0,		null0	},
		{ cgcCaskSquareClose,		2,			false,		_ICODE_CASK_SQUARE_CLOSE,				false,				_ICAT_CASK,						NULL,						false,						null0,					null0,		null0	},
		{ cgcCaskTriangleOpen,		2,			false,		_ICODE_CASK_TRIANGLE_OPEN,				false,				_ICAT_CASK,						NULL,						false,						null0,					null0,		null0	},
		{ cgcCaskTriangleClose,		2,			false,		_ICODE_CASK_TRIANGLE_CLOSE,				false,				_ICAT_CASK,						NULL,						false,						null0,					null0,		null0	},
		{ cgcCaskUtilityOpen,		2,			false,		_ICODE_CASK_UTILITY_OPEN,				false,				_ICAT_CASK,						NULL,						false,						null0,					null0,		null0	},
		{ cgcCaskUtilityClose,		2,			false,		_ICODE_CASK_UTILITY_CLOSE,				false,				_ICAT_CASK,						NULL,						false,						null0,					null0,		null0	},
		{ cgcCaskCodeOpen,			2,			false,		_ICODE_CASK_CODE_OPEN,					false,				_ICAT_CASK,						NULL,						false,						null0,					null0,		null0	},
		{ cgcCaskCodeClose,			2,			false,		_ICODE_CASK_CODE_CLOSE,					false,				_ICAT_CASK,						NULL,						false,						null0,					null0,		null0	},
		{ cgcCaskAutoOpen,			2,			false,		_ICODE_CASK_AUTO_OPEN,					false,				_ICAT_CASK,						NULL,						false,						null0,					null0,		null0	},
		{ cgcCaskAutoClose,			2,			false,		_ICODE_CASK_AUTO_CLOSE,					false,				_ICAT_CASK,						NULL,						false,						null0,					null0,		null0	},
//////////
// Note:  Cask physical appearances:
//		(||round params||)		[||square params||]		<||triangle params||>		~||utility params||~		\||code params||/		/||auto||\ cask
//		(|round|)				[|square|]				<|triangle|>				~|utility|~					\|code|/				/|auto|\ cask
//////

		// Native characters and symbols
		// Note:  If it begins with an underscore, it then uses pairs of characters for a range until it reaches trailing nullsnull
		{ "_azAZ\377\377__\000\000",1,			true,		_ICODE_ALPHA,							false,				_ICAT_GENERIC,					NULL,						false,						null0,					(uptr)&ii_onFind_countNbsp, null0	},
		{ "_09\000\000",			1,			true,		_ICODE_NUMERIC,							false,				_ICAT_GENERIC,					&colorSynHi_numeric,		false,						null0,					(uptr)&ii_onFind_countNbsp, null0	},
		{ " ",						1,			true,		_ICODE_WHITESPACE,						false,				_ICAT_GENERIC,					&colorSynHi_comment1,		false,						null0,					null0,		null0	},
		{ "\t",						1,			true,		_ICODE_WHITESPACE,						false,				_ICAT_GENERIC,					&colorSynHi_comment1,		false,						null0,					null0,		null0	},
		{ "|||",					3,			false,		_ICODE_WHITESPACE,						false,				_ICAT_GENERIC,					&colorSynHi_comment1,		false,						null0,					null0,		null0	},
		{ "___",					1,			false,		_ICODE_UNDERSCORE,						false,				_ICAT_GENERIC,					NULL,						false,						null0,					null0,		null0	},
		{ "(",						1,			false,		_ICODE_PARENTHESIS_LEFT,				false,				_ICAT_DESCENT,					&colorSynHi_bracket,		true,						null0,					null0,		null0	},
		{ ")",						1,			false,		_ICODE_PARENTHESIS_RIGHT,				false,				_ICAT_ASCENT,					&colorSynHi_bracket,		true,						null0,					null0,		null0	},
		{ "[",						1,			false,		_ICODE_BRACKET_LEFT,					false,				_ICAT_DESCENT,					&colorSynHi_bracket,		true,						null0,					null0,		null0	},
		{ "]",						1,			false,		_ICODE_BRACKET_RIGHT,					false,				_ICAT_ASCENT,					&colorSynHi_bracket,		true,						null0,					null0,		null0	},
		{ "{{",						2,			false,		_ICODE_DOUBLE_BRACE_LEFT,				false,				_ICAT_DESCENT,					&colorSynHi_bracket,		true,						null0,					null0,		null0	},
		{ "}}",						2,			false,		_ICODE_DOUBLE_BRACE_RIGHT,				false,				_ICAT_ASCENT,					&colorSynHi_bracket,		true,						null0,					null0,		null0	},
		{ "{",						1,			false,		_ICODE_BRACE_LEFT,						false,				_ICAT_DESCENT,					&colorSynHi_bracket,		true,						null0,					null0,		null0	},
		{ "}",						1,			false,		_ICODE_BRACE_RIGHT,						false,				_ICAT_ASCENT,					&colorSynHi_bracket,		true,						null0,					null0,		null0	},
		{ "++",						2,			false,		_ICODE_PLUS_PLUS,						false,				_ICAT_UNARY,					&colorSynHi_operator,		true,						null0,					null0,		null0	},
		{ "+=",						2,			false,		_ICODE_ADD_EQUAL,						false,				_ICAT_ASSIGN_OP,				&colorSynHi_operator,		false,						null0,					null0,		null0	},
		{ "+",						1,			false,		_ICODE_PLUS,							false,				_ICAT_OPERATOR,					&colorSynHi_operator,		true,						null0,					null0,		null0	},
		{ "--",						2,			false,		_ICODE_MINUS_MINUS,						false,				_ICAT_UNARY,					&colorSynHi_operator,		true,						null0,					null0,		null0	},
		{ "-=",						2,			false,		_ICODE_MINUS_EQUAL,						false,				_ICAT_ASSIGN_OP,				&colorSynHi_operator,		false,						null0,					null0,		null0	},
		{ "-",						1,			false,		_ICODE_HYPHEN,							false,				_ICAT_OPERATOR,					&colorSynHi_operator,		true,						null0,					null0,		null0	},
		{ "^=",						2,			false,		_ICODE_XOR_EQUAL,						false,				_ICAT_ASSIGN_OP,				&colorSynHi_operator,		false,						null0,					null0,		null0	},
		{ "^",						1,			false,		_ICODE_XOR,								false,				_ICAT_BITWISE,					&colorSynHi_operator,		true,						null0,					null0,		null0	},
		{ "/+",						2,			true,		_ICODE_COMMENT_START,					false,				_ICAT_COMMENT,					&colorSynHi_comment3,		false,						null0,					null0,		null0	},
		{ "+/",						2,			true,		_ICODE_COMMENT_END,						false,				_ICAT_COMMENT,					&colorSynHi_comment3,		false,						null0,					null0,		null0	},
		{ "/*",						2,			true,		_ICODE_COMMENT_START,					false,				_ICAT_COMMENT,					&colorSynHi_comment3,		false,						null0,					null0,		null0	},
		{ "*/",						2,			true,		_ICODE_COMMENT_END,						false,				_ICAT_COMMENT,					&colorSynHi_comment3,		false,						null0,					null0,		null0	},
		{ "||||",					4,			false,		_ICODE_COMMENT,							false,				_ICAT_COMMENT,					&colorSynHi_comment1,		false,						null0,					null0,		null0	},
		{ "//",						2,			true,		_ICODE_COMMENT,							true,				_ICAT_COMMENT,					&colorSynHi_comment1,		false,						null0,					null0,		null0	},
		{ "*=",						2,			false,		_ICODE_MULTIPLY_EQUAL,					false,				_ICAT_ASSIGN_OP,				&colorSynHi_operator,		false,						null0,					null0,		null0	},
		{ "*",						1,			true,		_ICODE_COMMENT,							true,				_ICAT_GENERIC,					&colorSynHi_comment1,		false,						null0,					null0,		null0	},
		{ "*",						1,			false,		_ICODE_MULTIPLY,						false,				_ICAT_OPERATOR,					&colorSynHi_comment1,		false,						null0,					null0,		null0	},
		{ "*",						1,			true,		_ICODE_ASTERISK,						false,				_ICAT_COMMENT,					&colorSynHi_operator,		true,						null0,					null0,		null0	},
		{ "\\",						1,			true,		_ICODE_BACKSLASH,						false,				_ICAT_GENERIC,					NULL,						false,						null0,					null0,		null0	},
		{ "**",						2,			false,		_ICODE_EXPONENT,						false,				_ICAT_GENERIC,					NULL,						false,						null0,					null0,		null0	},
		{ "/=",						2,			false,		_ICODE_DIVIDE_EQUAL,					false,				_ICAT_ASSIGN_OP,				&colorSynHi_operator,		false,						null0,					null0,		null0	},
		{ "/",						1,			true,		_ICODE_SLASH,							false,				_ICAT_GENERIC,					NULL,						false,						null0,					null0,		null0	},
		{ "\"",						1,			false,		_ICODE_DOUBLE_QUOTE,					false,				_ICAT_GENERIC,					NULL,						false,						null0,					null0,		null0	},
		{ "'",						1,			false,		_ICODE_SINGLE_QUOTE,					false,				_ICAT_GENERIC,					NULL,						false,						null0,					null0,		null0	},
		{ "..",						2,			false,		_ICODE_RANGE,							false,				_ICAT_RANGE,					NULL,						false,						null0,					null0,		null0	},
		{ ".",						1,			false,		_ICODE_DOT,								false,				_ICAT_DOT,						NULL,						false,						null0,					null0,		null0	},
		{ ",",						1,			false,		_ICODE_COMMA,							false,				_ICAT_PARAM,					&colorSynHi_bracket,		true,						null0,					null0,		null0	},
		{ ":=",						2,			false,		_ICODE_EQUAL_SIGN,						false,				_ICAT_ASSIGN,					&colorSynHi_operator,		true,						null0,					null0,		null0	},
		{ "::",						2,			false,		_ICODE_SCOPE,							false,				_ICAT_SCOPE,					NULL,						false,						null0,					null0,		null0	},
		{ ":",						1,			false,		_ICODE_COLON,							false,				_ICAT_GENERIC,					NULL,						false,						null0,					null0,		null0	},
		{ "_",						1,			false,		_ICODE_UNDERSCORE,						false,				_ICAT_GENERIC,					NULL,						false,						null0,					null0,		null0	},
		{ "~",						1,			false,		_ICODE_TILDE,							false,				_ICAT_BITWISE,					NULL,						false,						null0,					null0,		null0	},
		{ "@",						1,			false,		_ICODE_AT_SIGN,							false,				_ICAT_REFERENCE,				NULL,						false,						null0,					null0,		null0	},
		{ "#",						1,			false,		_ICODE_POUND_SIGN,						false,				_ICAT_LOGIC,					&colorSynHi_operator,		false,						null0,					null0,		null0	},
		{ "$",						1,			false,		_ICODE_DOLLAR_SIGN,						false,				_ICAT_LOGIC,					&colorSynHi_operator,		false,						null0,					null0,		null0	},
		{ "?",						1,			false,		_ICODE_QUESTION_MARK,					false,				_ICAT_LOGIC,					NULL,						false,						null0,					null0,		null0	},
		{ "!=",						2,			false,		_ICODE_NOT_EQUAL,						false,				_ICAT_LOGIC,					&colorSynHi_operator,		true,						null0,					null0,		null0	},
		{ "!<",						2,			false,		_ICODE_GREATER_THAN_OR_EQUAL_TO,		false,				_ICAT_LOGIC,					&colorSynHi_operator,		true,						null0,					null0,		null0	},
		{ "!>",						2,			false,		_ICODE_LESS_THAN_OR_EQUAL_TO,			false,				_ICAT_LOGIC,					&colorSynHi_operator,		true,						null0,					null0,		null0	},
		{ "!<=",					3,			false,		_ICODE_GREATER_THAN,					false,				_ICAT_LOGIC,					&colorSynHi_operator,		true,						null0,					null0,		null0	},
		{ "!>=",					3,			false,		_ICODE_LESS_THAN,						false,				_ICAT_LOGIC,					&colorSynHi_operator,		true,						null0,					null0,		null0	},
		{ "!",						1,			false,		_ICODE_EXCLAMATION_POINT,				false,				_ICAT_LOGIC | _ICAT_DOT | _ICAT_BITWISE,	&colorSynHi_logical,		true,						null0,					null0,		null0	},
		{ cgcDefinePragma,			7,			false,		_ICODE_DEFINE_PRAGMA,					true,				_ICAT_PRAGMA,					&colorSynHi_pragmas,		false,						null0,					null0,		null0	},
		{ cgcElsePragma,			5,			false,		_ICODE_ELSE_PRAGMA,						true,				_ICAT_PRAGMA,					&colorSynHi_pragmas,		false,						null0,					null0,		null0	},
		{ cgcElseifPragma,			7,			false,		_ICODE_ELSEIF_PRAGMA,					true,				_ICAT_PRAGMA,					&colorSynHi_pragmas,		false,						null0,					null0,		null0	},
		{ cgcEndifPragma,			6,			false,		_ICODE_ENDIF_PRAGMA,					true,				_ICAT_PRAGMA,					&colorSynHi_pragmas,		false,						null0,					null0,		null0	},
		{ cgcIfPragma,				3,			false,		_ICODE_IF_PRAGMA,						true,				_ICAT_PRAGMA,					&colorSynHi_pragmas,		false,						null0,					null0,		null0	},
		{ cgcIfdefPragma,			6,			false,		_ICODE_IFDEF_PRAGMA,					true,				_ICAT_PRAGMA,					&colorSynHi_pragmas,		false,						null0,					null0,		null0	},
		{ cgcIfndefPragma,			7,			false,		_ICODE_IFNDEF_PRAGMA,					true,				_ICAT_PRAGMA,					&colorSynHi_pragmas,		false,						null0,					null0,		null0	},
		{ cgcIncludePragma,			8,			false,		_ICODE_INCLUDE_PRAGMA,					true,				_ICAT_PRAGMA,					&colorSynHi_pragmas,		false,						null0,					null0,		null0	},
		{ cgcUndefPragma,			6,			false,		_ICODE_UNDEF_PRAGMA,					true,				_ICAT_PRAGMA,					&colorSynHi_pragmas,		false,						null0,					null0,		null0	},
		{ "%=",						2,			false,		_ICODE_MODULO_EQUAL,					false,				_ICAT_ASSIGN_OP,				&colorSynHi_operator,		false,						null0,					null0,		null0	},
		{ "%",						1,			false,		_ICODE_PERCENT_SIGN,					false,				_ICAT_OPERATOR,					&colorSynHi_operator,		false,						null0,					null0,		null0	},
		{ "&&",						2,			false,		_ICODE_AND,								false,				_ICAT_LOGIC,					&colorSynHi_logical,		false,						null0,					null0,		null0	},
		{ "&",						1,			false,		_ICODE_AMPERSAND,						false,				_ICAT_BITWISE,					&colorSynHi_operator,		false,						null0,					null0,		null0	},
		{ "=<",						2,			false,		_ICODE_LESS_THAN_OR_EQUAL_TO,			false,				_ICAT_LOGIC,					&colorSynHi_operator,		true,						null0,					null0,		null0	},
		{ "=>",						2,			false,		_ICODE_GREATER_THAN_OR_EQUAL_TO,		false,				_ICAT_LOGIC,					&colorSynHi_operator,		true,						null0,					null0,		null0	},
		{ "==",						2,			false,		_ICODE_EXACTLY_EQUAL_TO,				false,				_ICAT_LOGIC,					&colorSynHi_operator,		true,						null0,					null0,		null0	},
		{ "=",						1,			false,		_ICODE_EQUAL_SIGN,						false,				_ICAT_ASSIGN,					&colorSynHi_operator,		true,						null0,					null0,		null0	},
		{ "||",						2,			false,		_ICODE_OR,								false,				_ICAT_LOGIC,					&colorSynHi_logical,		false,						null0,					null0,		null0	},
		{ "|=",						2,			false,		_ICODE_OR_ASSIGNMENT,					false,				_ICAT_BITWISE | _ICAT_ASSIGN_OP, &colorSynHi_operator,		false,						null0,					null0,		null0	},
		{ "|",						1,			false,		_ICODE_PIPE_SIGN,						false,				_ICAT_BITWISE,					&colorSynHi_operator,		false,						null0,					null0,		null0	},
		{ "`",						1,			false,		_ICODE_REVERSE_QUOTE,					false,				_ICAT_GENERIC,					NULL,						false,						null0,					null0,		null0	},
		{ ";",						1,			false,		_ICODE_SEMICOLON,						false,				_ICAT_STOPPER,					NULL,						false,						null0,					null0,		null0	},
		{ "<<=",					3,			false,		_ICODE_SHIFT_LEFT_ASSIGNMENT,			false,				_ICAT_BITWISE | _ICAT_ASSIGN,	&colorSynHi_operator,		true,						null0,					null0,		null0	},
		{ "<<",						2,			false,		_ICODE_SHIFT_LEFT,						false,				_ICAT_BITWISE,					&colorSynHi_operator,		true,						null0,					null0,		null0	},
		{ ">>=",					3,			false,		_ICODE_SHIFT_RIGHT_ASSIGNMENT,			false,				_ICAT_BITWISE | _ICAT_ASSIGN,	&colorSynHi_operator,		true,						null0,					null0,		null0	},
		{ ">>",						2,			false,		_ICODE_SHIFT_RIGHT,						false,				_ICAT_BITWISE,					&colorSynHi_operator,		true,						null0,					null0,		null0	},
		{ "<=",						2,			false,		_ICODE_LESS_THAN_OR_EQUAL_TO,			false,				_ICAT_LOGIC,					&colorSynHi_operator,		true,						null0,					null0,		null0	},
		{ ">=",						2,			false,		_ICODE_GREATER_THAN_OR_EQUAL_TO,		false,				_ICAT_LOGIC,					&colorSynHi_operator,		true,						null0,					null0,		null0	},
		{ "<>",						2,			false,		_ICODE_NOT_EQUAL,						false,				_ICAT_LOGIC,					&colorSynHi_operator,		true,						null0,					null0,		null0	},
		{ ">",						1,			false,		_ICODE_GREATER_THAN,					false,				_ICAT_LOGIC,					&colorSynHi_operator,		true,						null0,					null0,		null0	},
		{ "<",						1,			false,		_ICODE_LESS_THAN,						false,				_ICAT_LOGIC,					&colorSynHi_operator,		true,						null0,					null0,		null0	},

		/* As a last-case condition, we tag every character that we didn't previously identify with the unknown tag */
		{ "_\000\377\000\000",		1,			true,		_ICODE_UNKNOWN,							false,				_ICAT_GENERIC,					NULL,						false,						null0,					null0,		null0	},
		{ 0,						0,			0,			0,										0,					0,								0,							0,							null0,					null0,		null0	},
	};
