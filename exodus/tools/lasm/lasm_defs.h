//////////
//
// /libsf/exodus/tools/lasm/lasm_defs.h
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
//     Sep.12.2015
//////
// Change log:
//     Sep.12.2015 - Initial creation
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




struct SLasmFile;
struct SLasmInclude;


//////////
// lasm.cpp
//////
	void				ilasm_parse_commandLine							(SLasmCmdLine* cmdLine, s32 argc, s8* argv[]);
	void				ilasm_compile									(SLasmCmdLine* cmdLine);
	bool				ilasm_includeFile_append						(s8* tcPathname, SLasmFile** file);
	SLasmInclude*		ilasm_includePath_append						(s8* tcPathname, s32 tnPathnameLength, bool tlIsFilename);
	void				ilasm_includePaths_iterate_start				(SLasmIncludeIter* iiFile, s8* filename);
	bool				ilasm_includePaths_iterate_try					(SLasmIncludeIter* iiFile, bool& tlIsFileValid, SLasmFile** fileInclude);
	bool				ilasm_includePaths_iterate_next					(SLasmIncludeIter* iiFile);
	SLasmInclude*		ilasm_validate_trailingBackspace				(SLasmInclude* include);
	void				ilasm_fixup_directoryDividers					(s8* tcPathname, s32 tnPathnameLength);
	bool				ilasm_isAbsolutePath							(s8* tcPathname, s32 tnPathnameLength);
	void				ilasm_route_through_silentError_for_debugging	(void);

	// For component, line, or file statuses
	void				ilasm_status_comp_add							(SComp* comp, u32 tnStatus);
	void				ilasm_status_line_add							(SLine* line, u32 tnStatus, bool tlProcessComps);
	bool				ilasm_status_line_isCompleted					(SLine* line);
	void				ilasm_status_file_add							(SLasmFile* file, u32 tnStatus, bool tlProcessLines, bool tlProcessComps);

	// For parenthetical parameters, and comma delimited parameters
	s32					iilasm_params_parentheticalExtract				(SComp* compLeftParam, SBuilder** paramsRoot, bool tlMoveBeyondLineIfNeeded = true);
	s32					iilasm_params_commaDelimitedExtract				(SComp* compFirstParam, SBuilder** paramsRoot, bool tlVerifySingleParams = false, bool* tlIsSingleParam = NULL);
	s32					iilasm_params_extract_common					(SComp* compFirstParam, SBuilder** paramsRoot, bool tlMoveBeyondLineIfNeeded, s32 tniStopCode);

	// For defined tokens and macros
	bool				iilasm_dmac_add									(SLasmFile* file, SLine* line, SComp* compName, SBuilder* params, SComp* compStart, SComp* compEnd, bool tlIsDefine, SLasmDMac** dmOut = NULL);
	void				ilasm_dmac_unfurl								(SLasmDMac* dm);
	bool				iilasm_dmac_searchParams						(SBuilder* params, SDatum* text, s32& tnParamNumber);
	bool				iilasm_dmac_unfurl_validateBuilder				(SBuilder** expansion_stepsRoot);
	SLasmExpansion*		iilasm_dmac_unfurl_addParameter					(SBuilder** expansion_stepsRoot, s32 tnParamNum);
	SLasmExpansion*		iilasm_dmac_unfurl_addText						(SBuilder** expansion_stepsRoot, SDatum* text, s32 tnWhitespaces, bool tlPrefixCrLf);

	// Note, warning, error, and other forms of associated reporting
	void				ilasm_append_extraInfo							(s32 tnValueCode,	cs8* valueTextTemplate, cs8* tcValueText, SLine* line, SComp* comp, SLasmFile* file, s32 tnValueBaseAddto, s32 tn_eiType);
	void				ilasm_note										(s32 tnNoteCode,	cs8* noteTextTemplate,		SLine* line, SComp* comp = NULL, SLasmFile* file = NULL);
	void				ilasm_warning									(s32 tnWarningCode,	cs8* warningTextTemplate,	SLine* line, SComp* comp = NULL, SLasmFile* file = NULL);
	void				ilasm_error										(s32 tnErrorCode,	cs8* errorTextTemplate,		SLine* line, SComp* comp = NULL, SLasmFile* file = NULL);


//////////
// pass0.cpp
//////
	void				ilasm_pass0										(SLasmCmdLine* cmdLine, SLasmFile* file);
	bool				iilasm_pass0_include							(SLasmPass0* p0);
	bool				ilasm_pass0_define								(SLasmPass0* p0);
	bool				ilasm_pass0_macro								(SLasmPass0* p0);
	bool				ilasm_pass0_if									(SLasmPass0* p0);
	bool				ilasm_pass0_ifdef								(SLasmPass0* p0);
	bool				ilasm_pass0_ifndef								(SLasmPass0* p0);


//////////
// pass1.cpp -- Macro expansion
//////
	void				ilasm_pass1										(SLasmCmdLine* cmdLine, SLasmFile* file);


//////////
// pass2.cpp -- function, adhoc, struct, enum markers
//////
	void				ilasm_pass2										(SLasmCmdLine* cmdLine, SLasmFile* file);
	SLasmBlock*			ilasm_pass2_function							(SLasmCmdLine* cmdLine, SLasmFile* file, SLine** lineProcessing);
	SLasmStruct*		ilasm_pass2_struct								(SLasmCmdLine* cmdLine, SLasmFile* file, SLine** lineProcessing);
	SLasmEnum*			ilasm_pass2_enum								(SLasmCmdLine* cmdLine, SLasmFile* file, SLine** lineProcessing);
	bool				ilasm_pass2_label								(SLasmCmdLine* cmdLine, SLasmFile* file, SLine** lineProcessing);


//////////
// pass3.cpp -- Token parsing
//////
	void				ilasm_pass3										(SLasmCmdLine* cmdLine, SLasmFile* file);


//////////
// passX.cpp -- Opcode generation
//////
	void				ilasm_passX										(SLasmCmdLine* cmdLine, SLasmFile* file);


//////////
// passY.cpp -- Linking
//////
	void				ilasm_passY										(SLasmCmdLine* cmdLine, SLasmFile* file);


//////////
// passZ.cpp -- Output file
//////
	void				ilasm_passZ										(SLasmCmdLine* cmdLine, SLasmFile* file);
