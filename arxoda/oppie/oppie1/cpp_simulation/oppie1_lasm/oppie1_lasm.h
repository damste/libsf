//////////
//
// /libsf/arxoda/oppie/oppie1/cpp_simulation/oppie1_lasm/oppie1_lasm.h
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
// Version 0.02
// Copyright (c) 2014 by Rick C. Hodgin
//////
// Last update:
//     Nov.29.2014
//////
// Change log:
//     Nov.29.2014 - Initial creation
//////
//
// This software is released as Liberty Software under a Repeat License, as governed
// by the Public Benefit License v1.0 or later (PBL).
//
// You are free to use, copy, modify and share this software.  However, it can only
// be released under the PBL version indicated, and every project must include a copy
// of the pbl.txt document for its version as is at http://www.libsf.org/licenses/.
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




struct SCommand;


//////////
// Forward declarations
//////
	void		exit_program								(int tnExitCode);
	SComp*		iParseSourceCodeLine						(SLine* line);
	void		iCompileSourceCodeLine						(SEM* asmFile, SLine* line, s32* tnErrors, s32* tnWarnings, s32 tnPass);
	u32			iGetRegisterEncoding						(SComp* comp);
	u32			iGetLabelAddress							(SEM* asmFile, SComp* compLabelSrch);
	void		iCompile_orgHandler							(SCommand* cmd, SLine* line, SComp* compFirst, s32 tnPass);
	void		iCompile_labelHandler						(SCommand* cmd, SLine* line, SComp* compFirst, s32 tnPass);
	void		iCompile_dbDupHandler						(SCommand* cmd, SLine* line, SComp* compFirst, s32 tnPass);
	void		iCompile_dbHandler							(SCommand* cmd, SLine* line, SComp* compFirst, s32 tnPass);


//////////
// Codes unique to Oppie-1
//////
	SBgra		colorSynHi_register				= { rgba(92,92,225,255) };
	SBgra		colorSynHi_preprocessor			= { rgba(255,92,92,255) };

	// Categories of operations
	cs32		_ICAT_REGISTER					= -1000;

	// Codes of operations
	cs32		_ICODE_MOV						= -1001;
	cs32		_ICODE_ADC						= -1002;
	cs32		_ICODE_SBB						= -1003;
	cs32		_ICODE_CMP						= -1004;
	cs32		_ICODE_JNC						= -1005;
	cs32		_ICODE_JC						= -1006;
	cs32		_ICODE_JNZ						= -1007;
	cs32		_ICODE_JZ						= -1008;
	cs32		_ICODE_JMP						= -1009;
	cs32		_ICODE_R1						= -1010;
	cs32		_ICODE_R2						= -1011;
	cs32		_ICODE_R3						= -1012;
	cs32		_ICODE_R4						= -1013;
	cs32		_ICODE_ORG						= -1014;
	cs32		_ICODE_DB						= -1015;
	cs32		_ICODE_DUP						= -1016;


//////////
// Keywords for Oppie-1's assembler
//////
	SAsciiCompSearcher	cgcKeywordsOppie1[] =
	{
		// keyword					length		repeats?	extra (type)							first on line?		category			syntax highlight color		syntax highlight bold
		{ "mov",					3,			false,		_ICODE_MOV,								false,				_ICAT_COMMAND,		&colorSynHi_command,		false,						null },
		{ "add",					3,			false,		_ICODE_ADD,								false,				_ICAT_COMMAND,		&colorSynHi_command,		false,						null },
		{ "adc",					3,			false,		_ICODE_ADC,								false,				_ICAT_COMMAND,		&colorSynHi_command,		false,						null },
		{ "sub",					3,			false,		_ICODE_SUB,								false,				_ICAT_COMMAND,		&colorSynHi_command,		false,						null },
		{ "sbb",					3,			false,		_ICODE_SBB,								false,				_ICAT_COMMAND,		&colorSynHi_command,		false,						null },
		{ "cmp",					3,			false,		_ICODE_CMP,								false,				_ICAT_COMMAND,		&colorSynHi_command,		false,						null },
		{ "jnc",					3,			false,		_ICODE_JNC,								false,				_ICAT_COMMAND,		&colorSynHi_command,		false,						null },
		{ "jc",						2,			false,		_ICODE_JC,								false,				_ICAT_COMMAND,		&colorSynHi_command,		false,						null },
		{ "jnz",					3,			false,		_ICODE_JNZ,								false,				_ICAT_COMMAND,		&colorSynHi_command,		false,						null },
		{ "jz",						2,			false,		_ICODE_JZ,								false,				_ICAT_COMMAND,		&colorSynHi_command,		false,						null },
		{ "jmp",					3,			false,		_ICODE_JMP,								false,				_ICAT_COMMAND,		&colorSynHi_command,		false,						null },
		{ "r1",						2,			false,		_ICODE_R1,								false,				_ICAT_REGISTER,		&colorSynHi_register,		false,						null },
		{ "r2",						2,			false,		_ICODE_R2,								false,				_ICAT_REGISTER,		&colorSynHi_register,		false,						null },
		{ "r3",						2,			false,		_ICODE_R3,								false,				_ICAT_REGISTER,		&colorSynHi_register,		false,						null },
		{ "r4",						2,			false,		_ICODE_R4,								false,				_ICAT_REGISTER,		&colorSynHi_register,		false,						null },
		{ "org",					3,			false,		_ICODE_ORG,								false,				_ICAT_COMMAND,		&colorSynHi_preprocessor,	false,						null },
		{ "db",						2,			false,		_ICODE_DB,								false,				_ICAT_COMMAND,		&colorSynHi_command,		false,						null },
		{ "dup",					3,			false,		_ICODE_DUP,								false,				_ICAT_COMMAND,		&colorSynHi_command,		false,						null },
		{ 0,						0,			0,			0,										0,					0,					0,							0,							0 }
	};


//////////
// Constants
//////
	cs32	_MOV_REG_REG						= 1;
	cs32	_MOV_REG_LABEL						= 2;
	cs32	_MOV_REG_99							= 3;
	cs32	_MOV_LABEL_REG						= 4;
	cs32	_MOV_99_REG							= 5;
	cs32	_ADD_REG_REG						= 6;
	cs32	_ADC_REG_REG						= 7;
	cs32	_SUB_REG_REG						= 8;
	cs32	_SBB_REG_REG						= 9;
	cs32	_CMP_REG_REG						= 10;
	cs32	_JNC_LABEL							= 11;
	cs32	_JNC_PLUS_99						= 12;
	cs32	_JNC_NEGATIVE_99					= 13;
	cs32	_JC_LABEL							= 14;
	cs32	_JC_PLUS_99							= 15;
	cs32	_JC_NEGATIVE_99						= 16;
	cs32	_JNZ_LABEL							= 17;
	cs32	_JNZ_PLUS_99						= 18;
	cs32	_JNZ_NEGATIVE_99					= 19;
	cs32	_JZ_LABEL							= 20;
	cs32	_JZ_PLUS_99							= 21;
	cs32	_JZ_NEGATIVE_99						= 22;
	cs32	_JMP_LABEL							= 23;
	cs32	_JMP_PLUS_99						= 24;
	cs32	_JMP_NEGATIVE_99					= 25;
	cs32	_ORG_99								= 26;
	cs32	_DB_DUP								= 27;
	cs32	_LABEL_COLON						= 28;
	cs32	_DB									= 29;

	// Instruction encoding types:  ORA = Opcode,Register,Address, ORR = Opcode,Register,Register, BSA = Branch,Sign,Address
	cs32	_ORA								= 1;
	cs32	_ORR								= 2;
	cs32	_BSA								= 3;

	struct SCmdPattern
	{
		s32		iCode;
		s32		iCode2;
		s32		iCat;
	};

	struct SCommand
	{
		s32			cmdType;
		s32			opcodeType;				// One of _ORA, _ORR, _BSA
		u32			opcode;					// Physical opcode encoding for the ooo bits

		// Extra information for the opcode
		s32			opcodeSign;				// Physical opcode encoding for sign bit in BSA
		s32			componentRegister;		// The register component (if any)
		s32			componentLabelOrNumber;	// The label or number component (if any)

		// For instructions
		union {
			u32		_uniqueHandler;
			void	(*uniqueHandler)(SCommand* cmd, SLine* line, SComp* compFirst, s32 tnPass);
		};
		SCmdPattern	comp[6];
	};

	SCommand gsCommands[] = {
		{ // mov reg,reg
			_MOV_REG_REG, _ORR, _OPCODE_MOV_R8_R8, 0, 0, 0,
			NULL/*no unique handler*/,
			{
				{ _ICODE_MOV, -1, -1 },
				{ -1, -1, _ICAT_REGISTER },
				{ _ICODE_COMMA, -1, -1 },
				{ -1, -1, _ICAT_REGISTER },
				{ -1, -1, -1 },
				{ -1, -1, -1 }
			}
		},

		{ // mov reg,label
			_MOV_REG_LABEL, _ORA, _OPCODE_MOV_R8_ADDR, 0, 1/*reg*/, 3/*label*/,
			NULL/*no unique handler*/,
			{
				{ _ICODE_MOV, -1, -1 },
				{ -1, -1, _ICAT_REGISTER },
				{ _ICODE_COMMA, -1, -1 },
				{ _ICODE_ALPHA, _ICODE_ALPHANUMERIC, -1 },
				{ -1, -1, -1 },
				{ -1, -1, -1 }
			}
		},

		{ // mov reg,[99]
			_MOV_REG_99, _ORA, _OPCODE_MOV_R8_ADDR, 0, 1/*reg*/, 4/*number*/,
			NULL/*no unique handler*/,
			{
				{ _ICODE_MOV, -1, -1 },
				{ -1, -1, _ICAT_REGISTER },
				{ _ICODE_COMMA, -1, -1 },
				{ _ICODE_BRACKET_LEFT, -1, -1 },
				{ _ICODE_NUMERIC, -1, -1 },
				{ _ICODE_BRACKET_RIGHT, -1, -1 }
			}
		},

		{ // mov label,reg
			_MOV_LABEL_REG, _ORA, _OPCODE_MOV_ADDR_R8, 0, 3/*reg*/, 1/*label*/,
			NULL/*no unique handler*/,
			{
				{ _ICODE_MOV, -1, -1 },
				{ _ICODE_ALPHA, _ICODE_ALPHANUMERIC, -1 },
				{ _ICODE_COMMA, -1, -1 },
				{ -1, -1, _ICAT_REGISTER },
				{ -1, -1, -1 },
				{ -1, -1, -1 }
			}
		},

		{ // mov [99],reg
			_MOV_99_REG, _ORA, _OPCODE_MOV_ADDR_R8, 0, 5/*reg*/, 2/*number*/,
			NULL/*no unique handler*/,
			{
				{ _ICODE_MOV, -1, -1 },
				{ _ICODE_BRACKET_LEFT, -1, -1 },
				{ _ICODE_NUMERIC, -1, -1 },
				{ _ICODE_BRACKET_RIGHT, -1, -1 },
				{ _ICODE_COMMA, -1, -1 },
				{ -1, -1, _ICAT_REGISTER }
			}
		},

		{ // add reg,reg
			_ADD_REG_REG, _ORR, _OPCODE_ADD_R8_R8, 0, 0, 0,	/* no specific register notation as this form only has reg,reg */
			NULL/*no unique handler*/,
			{
				{ _ICODE_ADD, -1, -1 },
				{ -1, -1, _ICAT_REGISTER },
				{ _ICODE_COMMA, -1, -1 },
				{ -1, -1, _ICAT_REGISTER },
				{ -1, -1, -1 },
				{ -1, -1, -1 }
			}
		},

		{ // adc reg,reg
			_ADC_REG_REG, _ORR, _OPCODE_ADC_R8_R8, 0, 0, 0,	/* no specific register notation as this form only has reg,reg */
			NULL/*no unique handler*/,
			{
				{ _ICODE_ADC, -1, -1 },
				{ -1, -1, _ICAT_REGISTER },
				{ _ICODE_COMMA, -1, -1 },
				{ -1, -1, _ICAT_REGISTER },
				{ -1, -1, -1 },
				{ -1, -1, -1 }
			}
		},

		{ // sub reg,reg
			_SUB_REG_REG, _ORR, _OPCODE_SUB_R8_R8, 0, 0, 0,	/* no specific register notation as this form only has reg,reg */
			NULL/*no unique handler*/,
			{
				{ _ICODE_SUB, -1, -1 },
				{ -1, -1, _ICAT_REGISTER },
				{ _ICODE_COMMA, -1, -1 },
				{ -1, -1, _ICAT_REGISTER },
				{ -1, -1, -1 },
				{ -1, -1, -1 }
			}
		},

		{ // sbb reg,reg
			_SBB_REG_REG, _ORR, _OPCODE_SBB_R8_R8, 0, 0, 0,	/* no specific register notation as this form only has reg,reg */
			NULL/*no unique handler*/,
			{
				{ _ICODE_SBB, -1, -1 },
				{ -1, -1, _ICAT_REGISTER },
				{ _ICODE_COMMA, -1, -1 },
				{ -1, -1, _ICAT_REGISTER },
				{ -1, -1, -1 },
				{ -1, -1, -1 }
			}
		},

		{ // cmp reg,reg
			_CMP_REG_REG, _ORR, _OPCODE_CMP_R8_R8, 0, 0, 0,	/* no specific register notation as this form only has reg,reg */
			NULL/*no unique handler*/,
			{
				{ _ICODE_CMP, -1, -1 },
				{ -1, -1, _ICAT_REGISTER },
				{ _ICODE_COMMA, -1, -1 },
				{ -1, -1, _ICAT_REGISTER },
				{ -1, -1, -1 },
				{ -1, -1, -1 }
			}
		},

		{ // jnc label
			_JNC_LABEL, _BSA, _OPCODE_JNC_REL_ADDR, 0/*no sign*/, 0/*no reg*/, 1/*label*/,
			NULL/*no unique handler*/,
			{
				{ _ICODE_JNC, -1, -1 },
				{ _ICODE_ALPHA, _ICODE_ALPHANUMERIC, -1 },
				{ -1, -1, -1 },
				{ -1, -1, -1 },
				{ -1, -1, -1 },
				{ -1, -1, -1 }
			}
		},

		{ // jnc +99
			_JNC_PLUS_99, _BSA, _OPCODE_JNC_REL_ADDR, _SIGN_POSITIVE, 0/*no reg*/, 2/*number*/,
			NULL/*no unique handler*/,
			{
				{ _ICODE_JNC, -1, -1 },
				{ _ICODE_PLUS, -1, -1 },
				{ _ICODE_NUMERIC, -1, -1 },
				{ -1, -1, -1 },
				{ -1, -1, -1 },
				{ -1, -1, -1 }
			}
		},

		{ // jnc -99
			_JNC_NEGATIVE_99, _BSA, _OPCODE_JNC_REL_ADDR, _SIGN_NEGATIVE, 0/*no reg*/, 2/*number*/,
			NULL/*no unique handler*/,
			{
				{ _ICODE_JNC, -1, -1 },
				{ _ICODE_HYPHEN, -1, -1 },
				{ _ICODE_NUMERIC, -1, -1 },
				{ -1, -1, -1 },
				{ -1, -1, -1 },
				{ -1, -1, -1 }
			}
		},

		{ // jc label
			_JC_LABEL, _BSA, _OPCODE_JC_REL_ADDR, 0/*no sign*/, 0/*no reg*/, 1/*label*/,
			NULL/*no unique handler*/,
			{
				{ _ICODE_JC, -1, -1 },
				{ _ICODE_ALPHA, _ICODE_ALPHANUMERIC, -1 },
				{ -1, -1, -1 },
				{ -1, -1, -1 },
				{ -1, -1, -1 },
				{ -1, -1, -1 }
			}
		},

		{ // jc +99
			_JC_PLUS_99, _BSA, _OPCODE_JC_REL_ADDR, _SIGN_POSITIVE, 0/*no reg*/, 2/*number*/,
			NULL/*no unique handler*/,
			{
				{ _ICODE_JC, -1, -1 },
				{ _ICODE_PLUS, -1, -1 },
				{ _ICODE_NUMERIC, -1, -1 },
				{ -1, -1, -1 },
				{ -1, -1, -1 },
				{ -1, -1, -1 }
			}
		},

		{ // jc -99
			_JC_NEGATIVE_99, _BSA, _OPCODE_JC_REL_ADDR, _SIGN_NEGATIVE, 0/*no reg*/, 2/*number*/,
			NULL/*no unique handler*/,
			{
				{ _ICODE_JC, -1, -1 },
				{ _ICODE_HYPHEN, -1, -1 },
				{ _ICODE_NUMERIC, -1, -1 },
				{ -1, -1, -1 },
				{ -1, -1, -1 },
				{ -1, -1, -1 }
			}
		},

		{ // jnz label
			_JNZ_LABEL, _BSA, _OPCODE_JNZ_REL_ADDR, 0/*no sign*/, 0/*no reg*/, 1/*label*/,
			NULL/*no unique handler*/,
			{
				{ _ICODE_JNZ, -1, -1 },
				{ _ICODE_ALPHA, _ICODE_ALPHANUMERIC, -1 },
				{ -1, -1, -1 },
				{ -1, -1, -1 },
				{ -1, -1, -1 },
				{ -1, -1, -1 }
			}
		},

		{ // jnz +99
			_JNZ_PLUS_99, _BSA, _OPCODE_JNZ_REL_ADDR, _SIGN_POSITIVE, 0/*no reg*/, 2/*number*/,
			NULL/*no unique handler*/,
			{
				{ _ICODE_JNZ, -1, -1 },
				{ _ICODE_PLUS, -1, -1 },
				{ _ICODE_NUMERIC, -1, -1 },
				{ -1, -1, -1 },
				{ -1, -1, -1 },
				{ -1, -1, -1 }
			}
		},

		{ // jnz -99
			_JNZ_NEGATIVE_99, _BSA, _OPCODE_JNZ_REL_ADDR, _SIGN_NEGATIVE, 0/*no reg*/, 2/*number*/,
			NULL/*no unique handler*/,
			{
				{ _ICODE_JNZ, -1, -1 },
				{ _ICODE_HYPHEN, -1, -1 },
				{ _ICODE_NUMERIC, -1, -1 },
				{ -1, -1, -1 },
				{ -1, -1, -1 },
				{ -1, -1, -1 }
			}
		},

		{ // jz label
			_JZ_LABEL, _BSA, _OPCODE_JZ_REL_ADDR, 0, 0/*no reg*/, 1/*label*/,
			NULL/*no unique handler*/,
			{
				{ _ICODE_JZ, -1, -1 },
				{ _ICODE_ALPHA, _ICODE_ALPHANUMERIC, -1 },
				{ -1, -1, -1 },
				{ -1, -1, -1 },
				{ -1, -1, -1 },
				{ -1, -1, -1 }
			}
		},

		{ // jz +99
			_JZ_PLUS_99, _BSA, _OPCODE_JZ_REL_ADDR, _SIGN_POSITIVE, 0/*no reg*/, 2/*number*/,
			NULL/*no unique handler*/,
			{
				{ _ICODE_JZ, -1, -1 },
				{ _ICODE_PLUS, -1, -1 },
				{ _ICODE_NUMERIC, -1, -1 },
				{ -1, -1, -1 },
				{ -1, -1, -1 },
				{ -1, -1, -1 }
			}
		},

		{ // jz -99
			_JZ_NEGATIVE_99, _BSA, _OPCODE_JZ_REL_ADDR, _SIGN_NEGATIVE, 0/*no reg*/, 2/*number*/,
			NULL/*no unique handler*/,
			{
				{ _ICODE_JZ, -1, -1 },
				{ _ICODE_HYPHEN, -1, -1 },
				{ _ICODE_NUMERIC, -1, -1 },
				{ -1, -1, -1 },
				{ -1, -1, -1 },
				{ -1, -1, -1 }
			}
		},

		{ // jmp label
			_JMP_LABEL, _BSA, _OPCODE_JMP_REL_ADDR, 0, 0/*no reg*/, 1/*label*/,
			NULL/*no unique handler*/,
			{
				{ _ICODE_JMP, -1, -1 },
				{ _ICODE_ALPHA, _ICODE_ALPHANUMERIC, -1 },
				{ -1, -1, -1 },
				{ -1, -1, -1 },
				{ -1, -1, -1 },
				{ -1, -1, -1 }
			}
		},

		{ // jmp +99
			_JMP_PLUS_99, _BSA, _OPCODE_JMP_REL_ADDR, _SIGN_POSITIVE, 0/*no reg*/, 2/*number*/,
			NULL/*no unique handler*/,
			{
				{ _ICODE_JMP, -1, -1 },
				{ _ICODE_PLUS, -1, -1 },
				{ _ICODE_NUMERIC, -1, -1 },
				{ -1, -1, -1 },
				{ -1, -1, -1 },
				{ -1, -1, -1 }
			}
		},

		{ // jmp -99
			_JMP_NEGATIVE_99, _BSA, _OPCODE_JMP_REL_ADDR, _SIGN_NEGATIVE, 0/*no reg*/, 2/*number*/,
			NULL/*no unique handler*/,
			{
				{ _ICODE_JMP, -1, -1 },
				{ _ICODE_HYPHEN, -1, -1 },
				{ _ICODE_NUMERIC, -1, -1 },
				{ -1, -1, -1 },
				{ -1, -1, -1 },
				{ -1, -1, -1 }
			}
		},

		{ // .org 99
			_ORG_99, -1, -1, -1, -1, -1,
			(u32)&iCompile_orgHandler,
			{
				{ _ICODE_ORG, -1, -1 },
				{ _ICODE_NUMERIC, -1, -1 },
				{ -1, -1, -1 },
				{ -1, -1, -1 },
				{ -1, -1, -1 },
				{ -1, -1, -1 }
			}
		},

		{ // db C
			_DB, -1, -1, -1, -1, -1,
			(u32)&iCompile_dbHandler,
			{
				{ _ICODE_DB, -1, -1 },
				{ _ICODE_NUMERIC, -1, -1 },
				{ -1, -1, -1 },
				{ -1, -1, -1 },
				{ -1, -1, -1 },
				{ -1, -1, -1 }
			}
		},

		{ // db N dup C
			_DB_DUP, -1, -1, -1, -1, -1,
			(u32)&iCompile_dbDupHandler,
			{
				{ _ICODE_DB, -1, -1 },
				{ _ICODE_NUMERIC, -1, -1 },
				{ _ICODE_DUP, -1, -1 },
				{ _ICODE_NUMERIC, -1, -1 },
				{ -1, -1, -1 },
				{ -1, -1, -1 }
			}
		},

		{ // label:
			_LABEL_COLON, -1, -1, -1, -1, 0/*component number for label*/,
			(u32)&iCompile_labelHandler,
			{
				{ _ICODE_LABEL, -1, -1 },
				{ -1, -1, -1 },
				{ -1, -1, -1 },
				{ -1, -1, -1 },
				{ -1, -1, -1 },
				{ -1, -1, -1 }
			}
		},

		{ // End marker
			-1, -1, -1, -1, -1, -1,
			NULL,
			{
				{ -1, -1, -1 },
				{ -1, -1, -1 },
				{ -1, -1, -1 },
				{ -1, -1, -1 },
				{ -1, -1, -1 },
				{ -1, -1, -1 }
			}
		}
	};
