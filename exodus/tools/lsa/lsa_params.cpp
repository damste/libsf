//////////
//
// /libsf/exodus/tools/lsa/lsa_params.cpp
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
// Copyright (c) 2016 by Rick C. Hodgin
//////
// Last update:
//     Jul.19.2016
//////
// Change log:
//     Jul.19.2016 - Initial creation
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
// Called to extract parameters...
//
//////
	// Note:  This function generates the *paramsRoot builder (if there were any parameters) ... it will have to be deleted manually by caller
	// ...beginning at the parameter after the parenthesis, and then between the two parenthesis
	s32 iilsa_params_parentheticalExtract(SComp* compLeftParam, SBuilder** paramsRoot, bool tlMoveBeyondLineIfNeeded)
	{
		return(iilsa_params_extract_common(iComps_Nth(compLeftParam, 1, tlMoveBeyondLineIfNeeded), paramsRoot, tlMoveBeyondLineIfNeeded, _ICODE_PARENTHESIS_RIGHT));
	}

	// ...beginning where we are to the end of the line
	s32 iilsa_params_commaDelimitedExtract(SComp* compFirstParam, SBuilder** paramsRoot, bool tlVerifySingleParams, bool* tlIsSingleParam)
	{
		s32				lnResult;
		u32				lnI;
		SLsaParam*		param;


		// Get our parameters
		lnResult = iilsa_params_extract_common(compFirstParam, paramsRoot, false, _ICODE_NU);
		if (lnResult > 0 && *paramsRoot && tlVerifySingleParams && tlIsSingleParam)
		{
			// Make sure each parameter is single
			*tlIsSingleParam = true;	// Assume success
			iterate(lnI, (*paramsRoot), param, SLsaParam)
			//

				// Is this parameter single?
				if (param->start != param->end)
				{
					// No
					*tlIsSingleParam = false;
					break;
				}
			//
			iterate_end;
		}

		// Indicate our result
		return(lnResult);
	}




//////////
//
// Common comma-delimited parameter extraction algorithm
//
//////
	s32 iilsa_params_extract_common(SComp* compFirstParam, SBuilder** paramsRoot, bool tlMoveBeyondLineIfNeeded, s32 tniStopCode)
	{
		bool			llStoreStart;
		s32				lnLevel;
		SComp*			comp;
		SComp*			compStart;
		SComp*			compEnd;
		SComp*			compLast;
		SLsaParam*		param;
		SBuilder*		params;


		// We know we're sitting on a left parenthesis ( character
		if (*paramsRoot == NULL)
			iBuilder_createAndInitialize(paramsRoot);
		
		if (!*paramsRoot)
			return(0);

		// Grab our param in a more manageable form
		params = *paramsRoot;

		// Scan forward looking for commas and right-parenthesis
		for (lnLevel = 0, comp = compFirstParam, compEnd = NULL, compLast = NULL, llStoreStart = true; comp; comp = iComps_Nth(comp, 1, tlMoveBeyondLineIfNeeded))
		{
			// Store the starting component (if we need to)
			if (llStoreStart)
			{
				llStoreStart	= false;
				compStart		= comp;
			}

			// Are we at the terminating code?
			if (comp->iCode == tniStopCode || (!tlMoveBeyondLineIfNeeded && !comp->ll.nextComp))
			{
				// Make sure we can populate the end
				if (!compLast)
					compLast = compStart;

				// Process
				goto end_of_parameter;
			}

			// What are we sitting on?
			switch (comp->iCode)
			{
				case _ICODE_COMMA:
end_of_parameter:
					if (lnLevel == 0)
					{
						// Everything up to the component before this is part of the parameter
						compEnd = compLast;

						// Add a new record
						param = (SLsaParam*)iBuilder_allocateBytes(params, sizeof(SLsaParam));
						if (param)
						{
							// Populate this record
							param->start	= compStart;
							param->end		= compEnd;

							// Create the name parameter
							if (param->start == param->end)		iDatum_duplicate(&param->name, &param->start->text);
							else								iDatum_duplicate(&param->name, cgc_lsa_group);
						}

						// Reset the end and prepare for next iteration
						llStoreStart	= true;
						compEnd			= NULL;
					}
					// else we just skip past
					break;

				default:
					// No code, just keep going
					break;
			}

			// If it's the terminating code, we're done
			if (comp->iCode == tniStopCode || (!tlMoveBeyondLineIfNeeded && !comp->ll.nextComp))
				break;

			// Store this component as the last component we hit/touched
			compLast = comp;
		}

		// Indicate how many parameters were extracted
		if (params->populatedLength == 0)
		{
			// Nothing was selected, reset the params array
			iBuilder_freeAndRelease(paramsRoot);

			// No parameters
			return(0);

		} else {
			// Indicate the count
			return(params->populatedLength / sizeof(SLsaParam));
		}
	}
