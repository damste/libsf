//////////
//
// /libsf/exodus/tools/lsa/lsa_ei.cpp
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




//////////
//
// Called to add something to the indicated file, line, or component
//
//////
	// Note:  valueTextTemplate is expected to include a %d parameter for tnValueCode, and a %s parameter for the associated text
	void iilsa_append_extraInfo(s32			tnValueCode,
								cs8*		valueTextTemplate,
								cs8*		tcValueText,
								SLine*		line,
								SComp*		comp,
								SLsaFile*	file,
								s32			tnValueBaseAddto,
								s32			tn_eiType)
	{
		s32				lnLength;
		s8				buffer[1024];
		SExtraInfo*		ei;


		//////////
		// Generate the error
		//////
			sprintf(buffer, valueTextTemplate, tnValueCode + tnValueBaseAddto, tcValueText);
			lnLength = strlen(buffer);


		//////////
		// Store the error
		//////
			     if (line)		ei = iExtraInfo_allocate(&line->extra_info, tn_eiType);
			else if (comp)		ei = iExtraInfo_allocate(&comp->extra_info, tn_eiType);
			else if (file)		ei = iExtraInfo_allocate(&file->extra_info, tn_eiType);


		//////////
		// Store the related error message
		//////
			if (ei)
				iDatum_duplicate(&ei->info, (cvp*)buffer);


		//////////
		// Print it
		//////
			printf(buffer);

			// Append a trailing CR if it doesn't already have one
			if (*(u16*)&buffer[lnLength - 2] != 'n\\' && *(u16*)&buffer[lnLength - 4] != 'n\\')
				printf("\n");

	}

	// Note:  noteTextTemplate is expected to include a %d parameter for tnErrorCode, and a %s parameter for the associated error text
	void iilsa_note(s32 tnNoteCode, cs8* noteTextTemplate, SLine* line, SComp* comp)
	{
		cs8* lcNoteText;


		//////////
		// Grab the error message
		//////
// 			switch (tnNoteCode)
// 			{
// 				default:
					// Internal error (should never happen)
					ilsa_routeThrough_silentError_forDebugging();
					lcNoteText = cgc_lsa_note_unknown_note;
// 					break;
// 			}


		//////////
		// Append the warning
		//////
			iilsa_append_extraInfo(tnNoteCode, noteTextTemplate, lcNoteText, line, comp, (SLsaFile*)line->file, _LSA_NOTE_BASE, _EXTRA_INFO_NOTE);

	}

	// Note:  warningTextTemplate is expected to include a %d parameter for tnErrorCode, and a %s parameter for the associated error text
	void iilsa_warning(s32 tnWarningCode, cs8* warningTextTemplate, SLine* line, SComp* comp)
	{
		cs8* lcWarningText;


		//////////
		// Grab the error message
		//////
			switch (tnWarningCode)
			{
				case _LSA_WARNING_UNREFERENCED_PARAMETER:
					lcWarningText = cgc_lsa_warning_unreferenced_parameter;
					break;

				case _LSA_WARNING_TOO_MANY_PARAMETERS__IGNORED:
					lcWarningText = cgc_lsa_warning_too_many_parameters__ignored;
					break;

				default:
					// Internal error (should never happen)
					ilsa_routeThrough_silentError_forDebugging();
					lcWarningText = cgc_lsa_warning_unknown_warning;
					break;
			}


		//////////
		// Append the warning
		//////
			iilsa_append_extraInfo(tnWarningCode, warningTextTemplate, lcWarningText, line, comp, (SLsaFile*)line->file, _LSA_WARNING_BASE, _EXTRA_INFO_WARNING);

	}

	// Note:  errorTextTemplate is expected to include a %d parameter for tnErrorCode, and a %s parameter for the associated error text
	void iilsa_error(s32 tnErrorCode, cs8* errorTextTemplate, SLine* line, SComp* comp)
	{
		cs8* lcErrorText;


		//////////
		// Grab the error message
		//////
			switch (tnErrorCode)
			{
				case _LSA_ERROR_TOKEN_NAME_ALREADY_EXISTS:
					lcErrorText = cgc_lsa_error_token_name_already_exists;
					break;

				default:
					// Internal error (should never happen)
					ilsa_routeThrough_silentError_forDebugging();
					lcErrorText = cgc_lsa_error_unknown_error;
					break;
			}


		//////////
		// Append the error
		//////
			iilsa_append_extraInfo(tnErrorCode, errorTextTemplate, lcErrorText, line, comp, (SLsaFile*)line->file, _LSA_ERROR_BASE, _EXTRA_INFO_ERROR);

	}
