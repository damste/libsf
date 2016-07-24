//////////
//
// /libsf/exodus/tools/lsa/lasm_defs.h
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




struct SLsaFile;
struct SLsaInclude;


//////////
// lasm.cpp
//////
	SLsaInclude*		ilsa_init										(void);
	void				ilsa_routeThrough_silentError_forDebugging	(void);

	// lsa_cmdline.cpp
	void				ilsa_parse_commandLine							(s32 argc, s8* argv[]);

	// lsa_include.cpp
	bool				ilsa_includeFile_append							(s8* tcPathname, SLsaFile** file);
	SLsaInclude*		ilsa_includePath_append							(s8* tcPathname, s32 tnPathnameLength, bool tlIsFilename);
	void				ilsa_includePaths_iterate_start					(SLsaIncludeIter* iiFile, s8* filename);
	bool				ilsa_includePaths_iterate_try					(SLsaIncludeIter* iiFile, bool& tlIsFileValid, SLsaFile** fileInclude);
	bool				ilsa_includePaths_iterate_next					(SLsaIncludeIter* iiFile);
	s32					ilsa_validate_trailingBackspace					(s8* tcPathname, s32 tnPathnameLength);
	void				ilsa_fixup_directoryDividers					(s8* tcPathname, s32 tnPathnameLength);
	bool				ilsa_isAbsolutePath								(s8* tcPathname, s32 tnPathnameLength);

	// For component, line, or file statuses
	void				ilsa_status_comp_add							(SComp* comp, u32 tnStatus);
	void				ilsa_status_line_add							(SLine* line, u32 tnStatus, bool tlProcessComps);
	bool				ilsa_status_comp_isCompleted					(SComp* comp);
	bool				ilsa_status_line_isCompleted					(SLine* line);
	void				ilsa_status_file_add							(SLsaFile* file, u32 tnStatus, bool tlProcessLines, bool tlProcessComps);

	// For parenthetical parameters, and comma delimited parameters
	s32					iilsa_params_parentheticalExtract				(SComp* compLeftParam, SBuilder** paramsRoot, bool tlMoveBeyondLineIfNeeded = true);
	s32					iilsa_params_commaDelimitedExtract				(SComp* compFirstParam, SBuilder** paramsRoot, bool tlVerifySingleParams = false, bool* tlIsSingleParam = NULL);
	s32					iilsa_params_extract_common						(SComp* compFirstParam, SBuilder** paramsRoot, bool tlMoveBeyondLineIfNeeded, s32 tniStopCode);

	// lsa_dmac.cpp
	// For defined tokens and macros
	bool				iilsa_dmac_add									(SLsaFunc* func, SLine* line, SComp* compName, SBuilder* params, SComp* compStart, SComp* compEnd, bool tlIsDefine, SLsaDMac** dmOut = NULL);
	void				ilsa_dmac_unfurl								(SLsaDMac* dm);
	bool				iilsa_dmac_searchParams							(SBuilder* params, SDatum* text, s32& tnParamNumber, SLsaParam** paramOut);
	SBuilder*			iilsa_dmac_unfurl_validateBuilder				(SBuilder** expansion_stepsRoot);
	SLsaExpansion*		iilsa_dmac_unfurl_addParameter					(SBuilder** expansion_stepsRoot, s32 tnParamNum, SDatum* name, s32 tnWhitespaces, bool tlPrefixCrLf, SBuilder* tbuilder);
	SLsaExpansion*		iilsa_dmac_unfurl_addText						(SBuilder** expansion_stepsRoot, SDatum* text, s32 tnWhitespaces, bool tlPrefixCrLf, SBuilder* tbuilder = NULL);
	bool				ilsa_dmac_find_byComp							(SBuilder* sortList, SComp* comp, SLsaDMac** dmOut);
	s32					iilsa_dmac_find_byComp__callbackSearch			(SBSearchCallback* bcb);
	bool				iilsa_dmac_find_byComp__callbackValidate		(SBSearchCallback* bcb);
	bool				ilsa_dmac_swapOut								(SComp* compToSwapOut, SLsaDMac* dm, SComp** compOut);
	bool				iilsa_dmac_swapOut_comps						(SComp* compFirst, SComp* compLast, SLsaDMac* dm, SBuilder* params);

	// lsa_ei.cpp
	// Note, warning, error, and other forms of associated reporting
	void				iilsa_append_extraInfo							(s32 tnValueCode,	cs8* valueTextTemplate, cs8* tcValueText, SLine* line, SComp* comp, SLsaFile* file, s32 tnValueBaseAddto, s32 tn_eiType);
	void				iilsa_note										(s32 tnNoteCode,	cs8* noteTextTemplate,		SLine* line, SComp* comp = NULL);
	void				iilsa_warning									(s32 tnWarningCode,	cs8* warningTextTemplate,	SLine* line, SComp* comp = NULL);
	void				iilsa_error										(s32 tnErrorCode,	cs8* errorTextTemplate,		SLine* line, SComp* comp = NULL);


//////////
// pass0.cpp
//////
	void				ilsa_pass0										(void);
	bool				iilsa_pass0_include								(SLsaPass0* p0);
	bool				ilsa_pass0_code									(SLsaPass0* p0);
	bool				ilsa_pass0_function								(SLsaPass0* p0);
	bool				ilsa_pass0_define								(SLsaPass0* p0);
	bool				ilsa_pass0_macro								(SLsaPass0* p0);
	bool				iilsa_pass0_equ_or_equalSign					(SLsaPass0* p0, SComp* compName, SComp* compEquOrEqual);


//////////
// pass1.cpp -- Macro expansion
//////
	void				ilsa_pass1										(void);
	int					iilsa_pass1__callback_sort						(SBSearchCallback* bcb);


//////////
// pass2.cpp -- function, adhoc, struct, enum markers
//////
	void				ilsa_pass2										(void);
	SLsaBlock*			ilsa_pass2_function								(SLsaFile* file, SLine** lineProcessing);
	SLsaStruct*			ilsa_pass2_struct								(SLsaFile* file, SLine** lineProcessing);
	SLsaEnum*			ilsa_pass2_enum									(SLsaFile* file, SLine** lineProcessing);
	bool				ilsa_pass2_label								(SLsaFile* file, SLine** lineProcessing);


//////////
// pass3.cpp -- Token parsing
//////
	void				ilsa_pass3										(void);


//////////
// passX.cpp -- Opcode generation
//////
	void				ilsa_passX										(void);


//////////
// passY.cpp -- Linking
//////
	void				ilsa_passY										(void);


//////////
// passZ.cpp -- Output file
//////
	void				ilsa_passZ										(void);
