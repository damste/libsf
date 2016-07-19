//////////
//
// /libsf/exodus/tools/lsa/pass1.cpp
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
//     Sep.17.2015
//////
// Change log:
//     Sep.17.2015 - Initial creation
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
// Liberty Software Foundation's lsa (LibSF Assembler).
//
//////




//////////
//
// Pass-1 -- Macro/define expansion
//
//////
	void ilsa_pass1(void)
	{
		u32			lnI;
		SLine*		line;
		SComp*		comp;
//		SComp*		compNext;
//		SComp*		compFile;
//		SLsaFile*	fileInclude;
		SLsaDMac*	dm;
//		s8			fileName[_MAX_PATH];


		// Are there any defines or macros?
		if (gsLsaDMacRoot && gsLsaDMacRoot->populatedLength > 0)
		{

			//////////
			// Step1 -- Unfurl the macro expansion into sequences
			//////
				iterate(lnI, gsLsaDMacRoot, dm, SLsaDMac)
				//

					// Unfurl the encoding into its constituent parts
					ilsa_dmac_unfurl(dm);

				//
				iterate_end;

//////////
// Validating the unfurl process worked properly
// BEGIN
//////
	u32 lnJ;
	SBuilder* b;
	SLsaDMac* dm;
	SLsaExpansion* exp;
	s8 buffer[256];
	b = NULL;
	iBuilder_createAndInitialize(&b);
	// Report on what's there
	iterate(lnI, gsLsaDMacRoot, dm, SLsaDMac)
	//

		// Double-space
		if (lnI != 0)
			iBuilder_appendCrLf(b);

		// Add the name
		iBuilder_appendData(b, dm->name->text.data_cs8, dm->name->text.length);
		iBuilder_appendCrLf(b);

		// Are there expansion steps?
		if (dm->expansion_steps && dm->expansion_steps->_data && dm->expansion_steps->populatedLength != 0)
		{

			// Iterate through dm's expansion_steps
			iterate(lnJ, dm->expansion_steps, exp, SLsaExpansion)
			//

				// Write this step
				if (exp->nParamNum != 0)
				{
					// Text first
					if (exp->text._data && exp->text.length > 0)
						iBuilder_appendData(b, exp->text.data_cs8, exp->text.length);

					// Then parameter number
					sprintf(buffer, "{%s}", exp->name.data_cs8);
					iBuilder_appendData(b, buffer);

				} else {
					// Text
					iBuilder_appendData(b, exp->text.data_cs8, exp->text.length);
				}

			//
			iterate_end;

		} else {
			// No content, just definition of the indicated token
			iBuilder_appendData(b, "[definition only]");
		}
		iBuilder_appendCrLf(b);

	//
	iterate_end;

	iBuilder_asciiWriteOutFile(b, (cu8*)"c:\\temp\\dmac_out.txt");
	iBuilder_freeAndRelease(&b);
//////
// END
//////////

			//////////
			// Step 2 -- Applying macros
			//////
// 				for (comp = file->firstLine->firstComp; comp; comp = iComps_Nth(comp))
// 				{
// 					// All lines should have compiler info, but just to be sure...
// 					if (!ilsa_status_comp_isCompleted(comp) && iiComps_isAlphanumeric_by_iCode(comp->iCode) && ilsa_dmac_find_byComp(comp, &dm))
// 					{
// 						// Does it have parameters?
// 						if (dm->params->populatedLength != 0)
// 						{
// 							// Yes, gather the parameters
// 						} else {
// 							// Just swap out the component with this entry
// 						}
// 					}
// 				}

		}
	}
