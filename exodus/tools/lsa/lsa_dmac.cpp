//////////
//
// /libsf/exodus/tools/lsa/lsa_dmac.cpp
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
// Called to create a define/macro define
//
//////
	bool iilsa_dmac_add(SLsaFunc* func, SLine* line, SComp* compName, SBuilder* params, SComp* compStart, SComp* compEnd, bool tlIsDefine, SLsaDMac** dmOut)
	{
		u32			lnI;
		SLsaDMac*	dm;
		s8			buffer[_MAX_PATH * 2];


		// Clear out the prior defineOut if any
		if (dmOut)
			*dmOut = NULL;

		// Make sure we have at least one define
		if (!gsLsaDMacRoot)
			iBuilder_createAndInitialize(&gsLsaDMacRoot);

		// Search existing
		iterate(lnI, gsLsaDMacRoot, dm, SLsaDMac)
		//
			
			// Does the name already exist?
			if (dm->name->text.length == compName->text.length && iDatum_compare(&dm->name->text, &compName->text) == 0)
			{
				// Generate the error
				sprintf(buffer, "Error %%d [%d,%d]: '%s' %%s, see [%d,%d] of %s", 
								line->lineNumber, compName->start,
								compName->text.data_s8,
								dm->name->line->lineNumber, dm->name->start, ((SLsaFile*)(line->file))->filename.data_s8);

				// Report the error
				iilsa_error(_LSA_ERROR_TOKEN_NAME_ALREADY_EXISTS, buffer, line);

				// Indicate failure
				return(false);
			}

		//
		iterate_end;

		// Allocate a new define record
		dm = (SLsaDMac*)iBuilder_allocateBytes(gsLsaDMacRoot, sizeof(SLsaDMac));
		if (dm)
		{
			// Store
			dm->file	= (SLsaFile*)line->file;	// The associated file
			dm->func	= func;						// The function it's related to
			dm->line	= line;						// The line related
			dm->name	= compName;					// Token name
			dm->params	= params;					// Parameters (if any)
			dm->first	= compStart;				// First component related to the token (if any)
			dm->last	= compEnd;					// Last component related to the token (if any)

			// Update the point
			if (dmOut)
				*dmOut = dm;
	
			// If we get here, success
			return(true);
		}

		// If we get here, failure
		return(false);
	}




//////////
//
// Called to parse through the define/macro structures to unfurl their coding
// requirements into little segments which are either raw texts to copy, or
// parameters
//
//////
	void ilsa_dmac_unfurl(SLsaDMac* dm)
	{
		bool			llHasParams, llPrefixCrLf;
		s32				lnWhitespaces, lnParamNumber;
		u32				lnI;
		SComp*			comp;
		SComp*			compLast;
		SBuilder*		tbuilder;
		SLsaParam*		param;
		s8				buffer[1024];


		// Make sure our environment is sane
		if (dm)
		{
			// Create a builder
			tbuilder = NULL;
			iBuilder_createAndInitialize(&tbuilder);

			// If no parameters, store all as text
			llHasParams = (dm->params && dm->params->populatedLength > 0);
			
			// Iterate through every component one by one
			for (comp = dm->first, compLast = NULL; comp; comp = iComps_Nth(comp))
			{
				// Are we still on the same line?
				llPrefixCrLf = (compLast && compLast->line != comp->line);

				// Whitespaces or inter-component spacing
				     if (llPrefixCrLf)		lnWhitespaces = comp->start;
				else if (compLast)			lnWhitespaces = ((llPrefixCrLf) ? comp->start : comp->start - (compLast->start + compLast->text.length));
				else						lnWhitespaces = 0;

				// Search this component for a param name
				if (llHasParams && iiComps_isAlphanumeric_by_iCode(comp->iCode) && dm->params && iilsa_dmac_searchParams(dm->params, &comp->text, lnParamNumber, &param))
				{
					// A single name, which means we use this parameter
					++param->nRefCount;
					iilsa_dmac_unfurl_addParameter(&dm->expansion_steps, lnParamNumber, &param->name, lnWhitespaces, llPrefixCrLf, tbuilder);

				} else {
					// Append it as is as text
					iilsa_dmac_unfurl_addText(&dm->expansion_steps, &comp->text, lnWhitespaces, llPrefixCrLf, tbuilder);
				}

				// Was this component the last one for the blocK?
				if (comp == dm->last)
					break;	// Yes

				// Prepare for the next component
				compLast = comp;
			}

			// Iterate through the params and make sure all were referenced
			if (llHasParams)
			{
				// Check ref counts
				iterate(lnI, dm->params, param, SLsaParam)
				//

					// Generate a warning if it's an unreferenced parameter
					if (param->name._data && param->name.length > 0 && param->nRefCount == 0)
					{
						// Display unreferenced parameter
						sprintf(buffer, "Warning %%d [%d,%d]: '%s' %%s, see [%d,%d] define/macro '%s' of %s", 
										param->start->line->lineNumber, param->start->start,
										param->name.data_s8,
										dm->name->line->lineNumber, dm->name->start,
										dm->name->text.data_s8,
										dm->file->filename.data_s8);

						// Report the warning
						iilsa_warning(_LSA_WARNING_UNREFERENCED_PARAMETER, buffer, param->start->line, param->start);
					}

				//
				iterate_end;

			}

			// Release the builder
			iBuilder_freeAndRelease(&tbuilder);
		}
	}

	// Search for the indicated name
	bool iilsa_dmac_searchParams(SBuilder* params, SDatum* text, s32& tnParamNumber, SLsaParam** paramOut)
	{
		s32			lnParamNumber;
		u32			lnI;
		SLsaParam*	param;


		// Iterate through the parameters looking for this name
		lnParamNumber = 0;
		iterate_with_count(lnI, params, param, SLsaParam, lnParamNumber)
		//

			// Right size?
			if (param->start == param->end && param->start->text.length == text->length)
			{
				// Text match?
				if (param->start->text.length == text->length && iDatum_compare(&param->start->text, text) == 0)
				{
					// This is it
					if (paramOut)
						*paramOut = param;

					// Indicate the number
					tnParamNumber = lnParamNumber;

					// And success
					return(true);
				}
			}

		//
		iterate_end;

		// If we get here, not found
		return(false);
	}

	// Make sure we have a builder
	SBuilder* iilsa_dmac_unfurl_validateBuilder(SBuilder** expansion_stepsRoot)
	{
		// Make sure we have a pointer to builder
		if (expansion_stepsRoot)
		{
			// Default to 20 entries
			if (!*expansion_stepsRoot)
				iBuilder_createAndInitialize(expansion_stepsRoot, sizeof(SLsaExpansion) * 20);

			// Indicate status
			return(*expansion_stepsRoot);
		}

		// If we get here, failure
		return(NULL);
	}

	// Called to add the parameter
	SLsaExpansion* iilsa_dmac_unfurl_addParameter(SBuilder** expansion_stepsRoot, s32 tnParamNum, SDatum* name, s32 tnWhitespaces, bool tlPrefixCrLf, SBuilder* tbuilder)
	{
		SBuilder*		expansion_stepsBuilder;
		SLsaExpansion*	exp;


		// Store text to prefix before the parameter
		if (tnWhitespaces != 0 || tlPrefixCrLf)
			iilsa_dmac_unfurl_addText(expansion_stepsRoot, NULL, tnWhitespaces, tlPrefixCrLf, tbuilder);

		// Make sure we have a builder
		exp = NULL;
		if ((expansion_stepsBuilder = iilsa_dmac_unfurl_validateBuilder(expansion_stepsRoot)))
		{
			// Create a new entry
			exp = (SLsaExpansion*)iBuilder_allocateBytes(*expansion_stepsRoot, sizeof(SLsaExpansion));
			if (exp)
			{
				iDatum_duplicate(&exp->name, name);
				exp->nParamNum = tnParamNum + 1;	// Store the parameter
			}
		}

		// Indicate the expansion record
		return(exp);
	}

	// Called to add text from a sequence of components
	SLsaExpansion* iilsa_dmac_unfurl_addText(SBuilder** expansion_stepsRoot, SDatum* text, s32 tnWhitespaces, bool tlPrefixCrLf, SBuilder* tbuilder)
	{
		SBuilder*		expansion_stepsBuilder;
		SLsaExpansion*	exp;


		// Make sure we have a builder
		exp = NULL;
		if ((expansion_stepsBuilder = iilsa_dmac_unfurl_validateBuilder(expansion_stepsRoot)))
		{
			// Create a new entry
			exp = (SLsaExpansion*)iBuilder_allocateBytes(expansion_stepsBuilder, sizeof(SLsaExpansion));
			if (exp)
			{
				// Reset the builder
				tbuilder->populatedLength = 0;

				// Prefix with anything?
				if (tlPrefixCrLf)			iBuilder_appendCrLf(tbuilder);
				if (tnWhitespaces > 0)		iBuilder_appendWhitespaces(tbuilder, tnWhitespaces);

				// Append the text
				if (text)
					iBuilder_appendData(tbuilder, text);

				// Copy to the expansion entry
				iDatum_duplicate(&exp->text, tbuilder->data_cvp, (s32)tbuilder->populatedLength);
			}
		}

		// Indicate the expansion record
		return(exp);
	}




//////////
//
// Performs a search for the indicated macro
//
//////
	bool ilsa_dmac_find_byComp(SBuilder* sortList, SComp* comp, SLsaDMac** dmOut)
	{
		SBSearchCallback bcb;


		// Search and return result
		memset(&bcb, 0, sizeof(bcb));
		bcb._binarySearchFunc		= (uptr)&iilsa_dmac_find_byComp__callbackSearch;
		bcb._binaryValidateFunc		= (uptr)&iilsa_dmac_find_byComp__callbackValidate;
		bcb.needle					= comp;
		return(iBSearch_find(sortList, &bcb, (void**)dmOut));
	}

	s32 iilsa_dmac_find_byComp__callbackSearch(SBSearchCallback* bcb)
	{
		SLsaDMac*	dmHaystack;
		SComp*		compNeedle;
		

		// Grab the dmac
		dmHaystack = (SLsaDMac*)bcb->haystack;
		compNeedle = (SComp*)bcb->needle;

		// Compare them
		return(iDatum_compare(&compNeedle->text, &dmHaystack->name->text));
	}

	bool iilsa_dmac_find_byComp__callbackValidate(SBSearchCallback* bcb)
	{
		SLsaDMac*	dmHaystack;
		SComp*		compNeedle;


		// Grab the dmac
		dmHaystack = (SLsaDMac*)bcb->haystack;
		compNeedle = (SComp*)bcb->needle;

		// Make sure the dmac's in the same function as where we're searching from
		if (!dmHaystack->func)
			return(true);		// There is no function on this one, so we're good

		// There is a function, so the needle must match it
		return(compNeedle->line->func == (void*)dmHaystack->func);
	}




///////////
//
// Called to swap out the indicated component with the components indicated in the dmac.
// It comments out the original line, and replaces it with new line(s) swapped out after.
//
// Single component replacement:
// 		;;  mov     eax,[temp]      // Is it the temporary value?
// 			mov     eax,[ebp-08]    // Comment here
//
// Multi-component replacement:
// 		;;  cmp     @helpKey  // Comment here
// 			cmp     eax,04800h  // Comment here
//
// Multi-line replacement:
// 		;;  @PushRegs  // Comment here
// 			push    eax
// 			push    ebx
// 			push    ecx
// 			push    edx  // Comment here
//
// Parameter replacement:
//		;;  @keystroke f1
//		    cmp     eax,f1
//			// Note:  After this, the single component will be replaced in a subsequent replacement
//
//////
	bool ilsa_dmac_swapOut(SComp* compToSwapOut, SLsaDMac* dm, SComp** compOut)
	{
		bool		llLastParam;
		u32			lnParam, lnParamCount;
		SComp*		comp;
		SComp*		compFirst;
		SComp*		compLast;
		union {
			SComp*	compComma;
			SComp*	compLastOnLine;
		};
		SBuilder*	params;		// SLsaParam
		SLsaParam*	param;
		s8			buffer[1024];


		// Make sure our environment is sane
		if (compToSwapOut && dm)
		{
			// Mark where it begins
			compFirst = compToSwapOut;

			// Create a buffer to load the parameters
			params = NULL;
			iBuilder_createAndInitialize(&params);

			// Does it have parameters?
			if (dm->params && (lnParamCount	= dm->params->populatedLength / sizeof(SLsaDMac)) > 0)
			{
				// Read in the parameters
				comp = iComps_Nth(compToSwapOut);
				for (lnParam = 0, llLastParam = false; !llLastParam && lnParam < lnParamCount && comp; comp = iComps_Nth(comp), lnParam++)
				{
					// Grab a param
					param = (SLsaParam*)iBuilder_allocateBytes(params, sizeof(SLsaParam));
					if (param)
					{
						// Gather everything from here forward to the next comma (or the end of line)
						param->start	= comp;
						compComma		= iComps_scanForward_for_iCode(comp, _ICODE_COMMA, false);

						// Did we land on a comma?  Or are we at the end of the line?
						if (compComma->iCode == _ICODE_COMMA)
						{
							// Store the component before this one
							param->end	= iComps_Nth(compComma, -1);

						} else {
							// Last one on line
							param->end	= compLastOnLine;
							llLastParam	= true;
						}

					} else {
						// Should never happen
						ilsa_internal_compiler_error();
					}
				}

				// When we get here, we've reached the end of our parameters
				if (comp)
				{
					// We did not reach the end of line
					// Too many parameters
					sprintf(buffer, "Warning %%d [%d,%d]: %%s", compToSwapOut->line->lineNumber, compToSwapOut->start);

					// Report the warning
					iilsa_warning(_LSA_WARNING_TOO_MANY_PARAMETERS__IGNORED, buffer, param->start->line, param->start);

				} else {
					// We reached the end of line, terminate any existing parameters
					for ( ; lnParam < lnParamCount; lnParam++)
					{
						// Create the empty parameter
						param = (SLsaParam*)iBuilder_allocateBytes(params, sizeof(SLsaParam));
						if (param)
						{
							// It is already set to NULL
							// No code is required here, but this should be the normal path through source code

						} else {
							// Should never happen
							ilsa_internal_compiler_error();
						}
					}
				}
				// When we get here, all of the params[] which existed are populated

			} else {
				// No parameters
				compLast = compToSwapOut;
			}

			// Substitute these components
			iilsa_dmac_swapOut_comps(compFirst, compLast, dm, params);

		} else {
			// Passed parameters are invalid
			// Should never happen
			ilsa_internal_compiler_error();
		}

		// Indicate failure
		return(false);
	}




//////////
//
// Called to swap out the indicated components, and build the line
//
//////
	bool iilsa_dmac_swapOut_comps(SComp* compFirst, SComp* compLast, SLsaDMac* dm, SBuilder* params)
	{
		u32				lnI;
		SLsaParam*		param;
		SLsaExpansion*	exp;
		SBuilder*		b;
		SComp*			comp;
		SComp*			compPrev;
		SComp*			compNext;
		SComp*			paramComp;
		SComp*			paramCompLast;
		SComp**			compRoot;
		SLine*			line;
		SLine*			lineNew;
		SLine*			firstLine;
		SLine*			lastLine;
		SCallback		cb;


		//////////
		// Create the macro'd content
		//////
			b = NULL;
			iBuilder_createAndInitialize(&b);
			iterate(lnI, dm->expansion_steps, exp, SLsaExpansion)
			//

				// Expand param or text
				if (exp->nParamNum > 0)
				{
					// Param
					param = (SLsaParam*)iBuilder_retrieveRecord(params, sizeof(SLsaParam), exp->nParamNum - 1);
					if (param)
					{
						// They provided content, so copy each component as is
						for (paramComp = param->start, paramCompLast = NULL; paramComp; paramCompLast = paramComp, paramComp = iComps_Nth(paramComp))
						{
							// If it's not the first component...
							if (paramCompLast)
							{
								// We may need a new line or whitespaces
								// Note:  These whitespaces in the original content may have been tabs, but here they will only be spaces
								if (paramCompLast->line != paramComp->line)
								{
									// Add CR/LF
									iBuilder_appendCrLf(b);

									// And, add whitespaces up to the start of this entry on the line
									if (paramComp->start > 0)
										iBuilder_appendWhitespaces(b, paramComp->start);

								} else if (paramCompLast->start + paramCompLast->text.length != paramComp->start) {
									// Add whitespaces between these components
									iBuilder_appendWhitespaces(b, paramComp->start - (paramCompLast->start + paramCompLast->text.length));
								}
							}

							// Copy this content
							iBuilder_appendData(b, paramComp->text.data_vp, paramComp->text.length);

							// Are we done?
							if (paramComp == param->end)
								break;	// Yes
						}

					} else {
						// Should never happen
						ilsa_internal_compiler_error();
					}

				} else {
					// Raw text copy
					iBuilder_appendData(b, exp->text.data_vp, exp->text.length);
				}

			//
			iterate_end;
			// Note:  When we get here, b->buffer is the content we need to replace


		//////////
		// Convert it out to real source code
		//////
			iFile_parseIntoLines(&firstLine, b->buffer, b->populatedLength, &lastLine);
			iComps_lex_and_parse(firstLine, true, cgcKeywordsLsa);


		//////////
		// Duplicate and comment out the line
		//////
			// Store the line pointer
			line = compFirst->line;

			// Duplicate
			lineNew = iLine_duplicate_withComps(line);

			// Prefix with a double-semicolon comment character
			iComps_insertBefore_by_iCode(line->firstComp, _ICODE_LINE_COMMENT);

			// Insert before 
			iLine_insertBefore(line, lineNew);


		//////////
		// Delete the components
		//////
			// Delete the comps in range on the line
			memset(&cb, 0, sizeof(cb));
			cb._func = (uptr)&iilsa_dmac_swapOut_comps__callback;
			iComps_deleteAll_byRange_withCallback(compFirst, compLast, &cb, &compPrev, &compNext);


		//////////
		// Was the entire line deleted?
		//////
			if (!compPrev && !compNext)
			{
				// Yes, append directly to the start of the line
				line->firstComp		= NULL;
				compRoot			= &line->firstComp;

			// Was it just everything from the beginning?
			} else if (!compPrev) {
				// Append to the start of the line
				line->firstComp		= compNext;
				compRoot			= &line->firstComp;

			// It may be something after
			} else {
				// Append after the compPrev component
				compRoot			= &compNext;
			}

			
		//////////
		// Add the dmac content?
		//////
			if (firstLine == lastLine)
			{
				// Doing a single-line injection

			} else {
				// Multiple lines are being inserted
			}


		//////////
		// Indicate success
		//////
			return(true);

	}

	bool iilsa_dmac_swapOut_comps__callback(SCallback* cb)
	{
// TODO:  working here

		// Continue iterating
		return(true);
	}
