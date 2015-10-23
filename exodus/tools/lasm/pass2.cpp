//////////
//
// /libsf/exodus/tools/lasm/pass2.cpp
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
//     Oct.01.2015
//////
// Change log:
//     Oct.01.2015 - Initial creation
//////
//
// This document and all documents contained within are released as Liberty Software
// under a Repeat License, as governed by the Public Benefit License v1.0 or later
// (PBL).
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
//
// Liberty Software Foundation's lasm (LibSF Assembler).
//
//////




//////////
//
// Pass-2 -- Markers
//
//		functions
//		adhocs
//		flowofs
//		classes
//		structs
//		enums
//		labels
//
//////
	void ilasm_pass2(SLasmFile* file)
	{
		SLine*			line;
		SComp*			comp;
		SComp*			compFile;
		SLasmFile*		fileInclude;
		SLasmBlock*		func;
		SLasmBlock*		flowof;
		SLasmBlock*		adhoc;
		SLasmClass*		lclass;
		SLasmStruct*	lstruct;
		SLasmEnum*		lenum;


		// Iterate through the entire file
		for (line = file->firstLine; line; line = line->ll.nextLine)
		{
			// All lines should have compiler info, but just to be sure...
			if (!line->status.isCompleted && line->compilerInfo)
			{
//////////
// function
//////
				comp = line->compilerInfo->firstComp;
				if (comp->iCode == _ICODE_LASM_FUNCTION)
				{
					// Process the function parameters, and mark off its extents
					if (!(func = ilasm_pass2_function(file, &line, comp)))
					{
					}

					// Process any inner classes
					// Process any inner structs
					// Process any inner enums
					// Process any inner adhocs


//////////
// adhoc
//////
				} else if (comp->iCode == _ICODE_LASM_ADHOC) {
					// Process the function parameters, and mark off its extents
					if (!(func = ilasm_pass2_function(file, &line, comp)))
					{
					}

					// Process any inner classes
					// Process any inner structs
					// Process any inner enums
					// Process any inner adhocs


//////////
// flowof
//////
				} else if (comp->iCode == _ICODE_LASM_FLOWOF) {
					// Process the flowof parameters, and mark off its extents
					if (!(flowof = ilasm_pass2_flowof(file, &line, comp)))
					{
					}

					// Process any inner classes
					// Process any inner structs
					// Process any inner enums
					// Process any inner adhocs


//////////
// class
//////
				} else if (comp->iCode == _ICODE_LASM_CLASS) {
					// Process the class
					if (!(lclass = ilasm_pass2_class(file, &line, comp)))
					{
					}


//////////
// struct
//////
				} else if (comp->iCode == _ICODE_LASM_STRUCT) {
					// Process the struct
					if (!(lstruct = ilasm_pass2_struct(file, &line, comp)))
					{
					}


//////////
// enum
//////
				} else if (comp->iCode == _ICODE_LASM_ENUM) {
					// Process the enum
					if (!(lenum = ilasm_pass2_enum(file, &line, comp)))
					{
					}


//////////
// Label
//////
				} else if (ilasm_pass2_label(file, &line, comp)) {
					// Found a label


//////////
// Function prototypes can also take on the old C-style form:  void name(...) { ... }
// However, because RDC allows for non-forward declarations, this may take more than one pass to identify
//////
				} else if (!(func = ilasm_pass2_function_c_style(file, &line, comp))) {
					// Found a function

					// Process any inner classes
					// Process any inner structs
					// Process any inner enums
					// Process any inner adhocs


				} else {
					// Did not find anything on this line
				}
			}
		}
	}




//////////
//
// Process the function header
//
//////
	SLasmBlock*	ilasm_pass2_function(SLasmFile* file, SLine** lineProcessing, SComp* comp)
	{
		return(NULL);
	}




//////////
//
// Process the C-style function header, the form like:
//
//		void function(void) { ... }
//
//////
	SLasmBlock* ilasm_pass2_function_c_style(SLasmFile* file, SLine** lineProcessing, SComp* comp)
	{
		return(NULL);
	}




//////////
//
// Process the adhoc header
//
//////
	SLasmBlock*	ilasm_pass2_adhoc(SLasmFile* file, SLine** lineProcessing, SComp* comp)
	{
		return(NULL);
	}




//////////
//
// Process the flowof header
//
//////
	SLasmBlock*	ilasm_pass2_flowof(SLasmFile* file, SLine** lineProcessing, SComp* comp)
	{
		return(NULL);
	}




//////////
//
// Process the class
//
//////
	SLasmClass* ilasm_pass2_class(SLasmFile* file, SLine** lineProcessing, SComp* comp)
	{
		return(NULL);
	}




//////////
//
// Process the struct
//
//////
	SLasmStruct* ilasm_pass2_struct(SLasmFile* file, SLine** lineProcessing, SComp* comp)
	{
		return(NULL);
	}




//////////
//
// Process the enum
//
//////
	SLasmEnum* ilasm_pass2_enum(SLasmFile* file, SLine** lineProcessing, SComp* comp)
	{
		return(NULL);
	}




//////////
//
// Process the label
//
//////
	bool ilasm_pass2_label(SLasmFile* file, SLine** lineProcessing, SComp* comp)
	{
		return(false);
	}