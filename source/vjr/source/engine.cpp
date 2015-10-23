//////////
//
// /libsf/source/vjr/source/engine.cpp
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
// Version 0.57
// Copyright (c) 2014 by Rick C. Hodgin
//////
// Last update:
//     Jul.05.2014
//////
// Change log:
//     Jul.05.2014 - Initial creation
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
//
// Called to execute a stand-alone command, such as from the command window.
//
//////
	bool iEngine_executeStandaloneCommand(SThisCode* thisCode, SLine* line)
	{
		bool			llManufactured;
		SComp*			comp;
		SComp*			compNext;
		SComp*			compThird;
		SVariable*		var;	// Ignore the GCC warning message here... I don't know why it's throwing a warning.  var is used correctly below.
		SVariable*		varExisting;
		SVariable*		varText;
		SFunctionParams	lrpar;
		SCommandData*	cmd;
		SDllFunc*		dfunc;
		bool			error;
		u32				errorNum;


		// Make sure our environment is sane
		if (line && line->sourceCode && line->sourceCode->data && line->sourceCode_populatedLength > 0)
		{
			//////////
			// Parse it
			//////
				comp = iEngine_parseSourceCodeLine(thisCode, line);


			//////////
			// Do we have anything to do?
			//////
s8 vizbuf[32768];
iComps_visualize(thisCode, comp, (s32)iComps_count(thisCode, comp), vizbuf, sizeof(vizbuf), true, &cgcFundamentalSymbols[0], &cgcKeywordsVxb[0]);
				if (!comp || comp->iCode == _ICODE_COMMENT || comp->iCode == _ICODE_LINE_COMMENT)
					return(false);


			//////////
			// Based on the first keyword, process it
			//////
				comp		= line->compilerInfo->firstComp;
				compNext	= comp->ll.nextComp;
				switch (comp->iCode)
				{
					case _ICODE_QUIT:
						// They want to quit
						iVjr_shutdown(thisCode);
						break;
//
// 					case _ICODE_CLEAR:
// 						// They want to clear the screen
// 						iSEM_navigateToTopLine(screenData, _screen);
// 						iSEM_deleteChain(&screenData, false);
// 						screen_editbox->isDirtyRender = true;
// 						iWindow_render(NULL, gWinJDebi, false);
// 						break;

					case _ICODE_QUESTION_MARK:
						// It is a "? something" command
						if (!compNext)
						{
							// Syntax error, expected "? something" got only "?"
							iSEM_appendLine(thisCode, screenData, (u8*)cgcSyntaxError, -1, false);
							iSEM_navigateToEndLine(thisCode, screenData, _screen);
							_screen_editbox->isDirtyRender = true;
							iWindow_render(NULL, gWinJDebi, false);
							return(false);

						} else {
							// It's a number, display it
							if (dfunc = iDllFunc_find_byName(thisCode, compNext->line->sourceCode->data_s8 + compNext->start, compNext->length))
							{
								// It is a DLL function
								if (dfunc->rp.type == _DLL_TYPE_VOID)
								{
									// No return value
									iError_reportByNumber(thisCode, _ERROR_INVALID_ARGUMENT_TYPE_COUNT, compNext, false);

									// Update the screen
									_screen_editbox->isDirtyRender |= iSEM_navigateToEndLine(thisCode, screenData, _screen);
									iWindow_render(NULL, gWinJDebi, false);
									return(false);
								}
								memset(&lrpar, 0, sizeof(lrpar));
								iDllFunc_dispatch(thisCode, &lrpar, dfunc, compNext);
								if (lrpar.ei.error)
									iError_reportByNumber(thisCode, lrpar.ei.errorNum, lrpar.ei.errorComp, false);

								// Grab the return value (if any)
								llManufactured	= ((lrpar.rp[0]) ? lrpar.rp[0]->isVarAllocated : false);
								var				= lrpar.rp[0];

							} else if (iCat(compNext->iCat) == _ICAT_FUNCTION) {
								// It is something like "? func(x)"
								llManufactured = true;
								memset(&lrpar, 0, sizeof(lrpar));
								iEngine_get_functionResult(thisCode, compNext, -1, &lrpar);
								if (lrpar.ei.error || !(var = lrpar.rp[0]))
								{
									// Unknown function, or parameters were not correct
									if (lrpar.ei.error)
										iError_reportByNumber(thisCode, lrpar.ei.errorNum, compNext, false);

									// Update the screen
									_screen_editbox->isDirtyRender |= iSEM_navigateToEndLine(thisCode, screenData, _screen);
									iWindow_render(NULL, gWinJDebi, false);
									return(false);
								}

							} else if (iCat(compNext->iCat) == _ICAT_GENERIC) {
								// It is something like "? k" or "? 29"
								var = iEngine_get_variableName_fromComponent(thisCode, compNext, &llManufactured, false);
								if (!var)
								{
									// Unknown parameter
									iError_report(thisCode, cgcUnrecognizedParameter, false);
									_screen_editbox->isDirtyRender |= iSEM_navigateToEndLine(thisCode, screenData, _screen);
									iWindow_render(NULL, gWinJDebi, false);
									return(false);
								}
							}
							// We have a variable we can display its contents
							varText = iVariable_convertForDisplay(NULL, var);

							// Add its contents to _screen
							iSEM_appendLine(thisCode, screenData, varText->value.data_u8, varText->value.length, false);
							iSEM_navigateToEndLine(thisCode, screenData, _screen);
							_screen_editbox->isDirtyRender = true;
							iWindow_render(NULL, gWinJDebi, false);

							// Release the variable if it was manufactured
							iVariable_delete(NULL, varText, true);
							if (llManufactured)
								iVariable_delete(NULL, var, true);
						}
						break;

					default:
						if ((comp->iCode == _ICODE_ALPHA || comp->iCode == _ICODE_ALPHANUMERIC || comp->iCode == _ICODE_DOT_VARIABLE) && compNext && compNext->iCode == _ICODE_EQUAL_SIGN)
						{
							// It is an assignment
							compThird = compNext->ll.nextComp;
							if (iCat(compThird->iCat) == _ICAT_FUNCTION)
							{
								// It is something like "? func(x)"
								memset(&lrpar, 0, sizeof(lrpar));
								iEngine_get_functionResult(thisCode, compThird, 10, &lrpar);
								if (lrpar.ei.error || !(var = lrpar.rp[0]))
								{
									// Unknown function, or parameters were not correct
									if (lrpar.ei.error)
										iError_reportByNumber(thisCode, lrpar.ei.errorNum, compThird, false);

									// Update the screen
									_screen_editbox->isDirtyRender |= iSEM_navigateToEndLine(thisCode, screenData, _screen);
									iWindow_render(NULL, gWinJDebi, false);
									return(false);
								}

							} else if (iCat(compThird->iCat) == _ICAT_GENERIC) {
								// It is something like "x = y" or "x = 29"
								if (!(var = iEngine_get_variableName_fromComponent(thisCode, compThird, &llManufactured, false)))
								{
									// Unknown parameter
									iError_report(thisCode, cgcUnrecognizedParameter, false);
									_screen_editbox->isDirtyRender |= iSEM_navigateToEndLine(thisCode, screenData, _screen);
									iWindow_render(NULL, gWinJDebi, false);
									return(false);
								}
							}

							// If we get here, we have the variable they're storing
							// Based on the name from comp, see if it's a variable we already possess
							if (comp->iCode == _ICODE_DOT_VARIABLE)
							{
								// Set the dot value
// TODO:  working here
_asm nop;
								iVariable_searchRoot_forDotName_andSet_byVar(thisCode, comp, var, &error, &errorNum);
								iVariable_delete(NULL, var, true);
								if (error)
								{
									// Unknown parameter
									iError_reportByNumber(thisCode, errorNum, comp, false);
									_screen_editbox->isDirtyRender |= iSEM_navigateToEndLine(thisCode, screenData, _screen);
									iWindow_render(NULL, gWinJDebi, false);
									return(false);
								}

							} else {
								varExisting = iVariable_searchForName(thisCode, comp->line->sourceCode->data + comp->start, comp->length, comp, true);
								if (varExisting)
								{
									// We are updating the value
									iVariable_copy(NULL, varExisting, var);
									iVariable_delete(NULL, var, true);

								} else {
									// We are creating a new variable
									iDatum_duplicate(&var->name, comp->line->sourceCode->data_u8 + comp->start, comp->length);
									iLl_appendExistingNodeAtBeginning((SLL**)&varGlobals, (SLL*)var);
								}
							}

						} else {
							// It may be a DLL
							if (dfunc = iDllFunc_find_byName(thisCode, comp->line->sourceCode->data_s8 + comp->start, comp->length))
							{
								// It is a DLL function
								memset(&lrpar, 0, sizeof(lrpar));
								iDllFunc_dispatch(thisCode, &lrpar, dfunc, comp);
								if (lrpar.ei.error)
								{
									// There was an error
									iError_reportByNumber(thisCode, lrpar.ei.errorNum, lrpar.ei.errorComp, false);

									// Update the screen
									_screen_editbox->isDirtyRender |= iSEM_navigateToEndLine(thisCode, screenData, _screen);
									iWindow_render(NULL, gWinJDebi, false);
								}

								// Indicate success or failure
								return(!lrpar.ei.error);
							}
							// If we get here, not a DLL function

							// See if it's a known command
							for (cmd = &gsKnownCommands[0]; cmd->iCode != 0; cmd++)
							{
								// Is this our command?
								if (cmd->iCode == comp->iCode)
								{
									// Yes, execute it (self-contained execution and error reporting on every command)
									memset(&lrpar, 0, sizeof(lrpar));
									cmd->command(thisCode, comp, &lrpar);
// TODO:  We should examine lrpar here for the error condition, and report it if need be
									return(!lrpar.ei.error);
								}
							}

							// Not a currently supported command
							return(false);
						}
				}
				// If we get here, we're good
				return(true);

		} else {
			// Failure
			return(false);
		}
	}




//////////
//
// Parse the source code line into VJr's fixed, known, component parts.
// This process does not process variables, table names, fields, etc.
//
//////
	SComp* iEngine_parseSourceCodeLine(SThisCode* thisCode, SLine* line)
	{

		//////////
		// If we have existing compiler data, get rid of it
		//////
			if (line->compilerInfo)		iCompiler_delete(thisCode, &line->compilerInfo, false);
			else						line->compilerInfo = iCompiler_allocate(thisCode, line);		// Allocate a new one


		//////////
		// Parse out the line
		//////
			iComps_translateSourceLineTo(thisCode, &cgcFundamentalSymbols[0], line);
			if (!line->compilerInfo->firstComp)
				return(NULL);		// Nothing to compile on this line

			// Remove whitespaces [use][whitespace][foo] becomes [use][foo]
			iComps_removeLeadingWhitespaces(thisCode, line);


		//////////
		// If it's a line comment, we don't need to process it
		//////
			if (line->compilerInfo->firstComp && (line->compilerInfo->firstComp->iCode == _ICODE_COMMENT || line->compilerInfo->firstComp->iCode == _ICODE_LINE_COMMENT))
			{
				// Combine every item after this to a single comment
// TODO:  This algorithm could changed so that casks in comments show up graphically, rather than as raw comment text
				iComps_combineN(thisCode, line->compilerInfo->firstComp, 99999, line->compilerInfo->firstComp->iCode, line->compilerInfo->firstComp->iCat, line->compilerInfo->firstComp->color);

				// Return the first component
				return(line->compilerInfo->firstComp);
			}


		//////////
		// Perform natural source code fixups
		//////
			iComps_removeStartEndComments(thisCode, line);		// Remove /* comments */
			iComps_combineCasks(thisCode, line);				// Replace [(|][alpha][|)] with [(|alpha|)]
			iComps_fixupNaturalGroupings(thisCode, line);		// Fixup natural groupings [_][aaa][999] becomes [_aaa999], [999][.][99] becomes [999.99], etc.
			iComps_combineAdjacentDotForms(thisCode, line);		// Fixup [.][t][.] into [.t.] and [thisForm][.][width] into [thisForm.width]
			iComps_removeWhitespaces(thisCode, line);			// Remove all whitespaces after everything else was parsed [use][whitespace][foo] becomes [use][foo]


		//////////
		// Translate sequences to known keywords
		//////
			iComps_translateToOthers(thisCode, &cgcKeywordsVxb[0], line);


		//////////
		// Return the first component
		//////
			return(line->compilerInfo->firstComp);
	}




//////////
//
// Called to obtain a variable from the component.  It will translate a literal
// into a variable, or if it's already a variable reference it will copy the
// reference.
//
//////
	SVariable* iEngine_get_variableName_fromComponent(SThisCode* thisCode, SComp* comp, bool* tlManufactured, bool tlByRef)
	{
		s32			lnI;
		s64			lnValue;
		f64			lfValue;
		bool		llDot;
		SVariable*	var;


// TODO:  Need to have this search for dot variables as well
		// Make sure our environment is sane
		if (!tlManufactured)
		{
			// This error should only exist during development when something is left off by the developer
			debug_break;
			return(NULL);
		}

		// Initially lower the flag
		*tlManufactured = false;
		if (comp)
		{
			switch (comp->iCode)
			{
				case _ICODE_NULL:
					*tlManufactured = true;
					return(iVariable_create(NULL, _VAR_TYPE_LOGICAL, NULL, false));

				case _ICODE_NUMERIC:
					// It's a raw number
					// See if it has a dot/period in it
					for (lnI = 0, llDot = false; lnI < comp->length; lnI++)
					{
						if (comp->line->sourceCode->data[comp->start + lnI] == '.')
						{
							llDot = true;
							break;
						}
					}

					// Is it integer or floating point?
					if (!llDot)
					{
						// Integer
						lnValue = iiComps_getAs_s64(comp);


						//////////
						// Create and populate our output variable
						//////
							*tlManufactured = true;
							if (lnValue >= (s64)_s32_min && lnValue <= (s64)_s32_max)
							{
								// Store as 32-bits
								var = iVariable_create(NULL, _VAR_TYPE_S32, NULL, true);
								if (var)
									*var->value.data_s32 = (s32)lnValue;

							} else {
								// Store as 64-bits
								var = iVariable_create(NULL, _VAR_TYPE_S64, NULL, true);
								if (var)
									*var->value.data_s64 = lnValue;
							}

					} else {
						// Floating point
						lfValue = iiComps_getAs_f64(comp);


						//////////
						// Create and populate our output variable
						//////
							*tlManufactured = true;
							if (lfValue >= (f64)_f32_min && lfValue <= (f64)_f32_max)
							{
								// Store as 32-bits
								var = iVariable_create(NULL, _VAR_TYPE_F32, NULL, true);
								if (var)
									*var->value.data_f32 = (f32)lfValue;

							} else {
								// Store as 64-bits
								var = iVariable_create(NULL, _VAR_TYPE_F64, NULL, true);
								if (var)
									*var->value.data_f64 = lfValue;
							}
					}


					//////////
					// Set the related comp
					//////
						if (var)
							var->compRelated = comp;


					//////////
					// Return our result
					//////
						return(var);


				case _ICODE_TRUE:
				case _ICODE_YES:
				case _ICODE_UP:
					// It's a .T. or some equivalent
					var = iVariable_create(NULL, _VAR_TYPE_LOGICAL, NULL, true);
					if (var)
					{
						*tlManufactured		= true;
						var->value.data[0]	= _LOGICAL_TRUE;
						var->compRelated	= comp;
					}
					return(var);


				case _ICODE_FALSE:
				case _ICODE_NO:
				case _ICODE_DOWN:
					// It's a .F. or some equivalent
					var = iVariable_create(NULL, _VAR_TYPE_LOGICAL, NULL, true);
					if (var)
					{
						*tlManufactured		= true;
						var->value.data[0]	= _LOGICAL_FALSE;
						var->compRelated	= comp;
					}
					return(var);


				case _ICODE_EXTRA:
					// It's a .X.
					var = iVariable_create(NULL, _VAR_TYPE_LOGICAL, NULL, true);
					if (var)
					{
						*tlManufactured		= true;
						var->value.data[0]	= _LOGICALX_EXTRA;
						var->compRelated	= comp;
					}
					return(var);


				case _ICODE_YET_ANOTHER:
					// It's a .Y.
					var = iVariable_create(NULL, _VAR_TYPE_LOGICAL, NULL, true);
					if (var)
					{
						*tlManufactured		= true;
						var->value.data[0]	= _LOGICALX_YET_ANOTHER;
						var->compRelated	= comp;
					}
					return(var);


				case _ICODE_ZATS_ALL_FOLKS:
					// It's a .X.
					var = iVariable_create(NULL, _VAR_TYPE_LOGICAL, NULL, true);
					if (var)
					{
						*tlManufactured		= true;
						var->value.data[0]	= _LOGICALX_ZATS_ALL_FOLKS;
						var->compRelated	= comp;
					}
					return(var);


				case _ICODE_ALPHANUMERIC:
				case _ICODE_ALPHA:
					// It's some kind of text, could be a field or variable
					return(iEngine_get_variableName_fromText(thisCode, comp->line->sourceCode->data_cs8 + comp->start, comp->length, comp, tlManufactured, tlByRef));


				case _ICODE_SINGLE_QUOTED_TEXT:
				case _ICODE_DOUBLE_QUOTED_TEXT:		// It's quoted text

					//////////
					// Create and populate our output variable
					//////
						*tlManufactured	= true;
						var = iVariable_create(NULL, _VAR_TYPE_CHARACTER, NULL, true);
						if (var)
							iDatum_duplicate(&var->value, comp->line->sourceCode->data_u8 + comp->start + 1, comp->length - 2);


					//////////
					// Return our result
					//////
						var->compRelated = comp;
						return(var);


				default:
					// Unknown
					break;
			}
		}
		// If we get here, failure
		return(NULL);
	}




//////////
//
// Called to lookup the variable based on text
//
//////
	SVariable* iEngine_get_variableName_fromText(SThisCode* thisCode, cs8* tcText, u32 tnTextLength, SComp* comp, bool* tlManufactured, bool tlByRef)
	{
		SVariable* var;
		SVariable* varCopy;


		//////////
		// Are we searching variables first?
		//////
			if (propGet_settings_VariablesFirst(_settings))
			{
				// Searching variables first, field names last.
				if ((var = iVariable_searchForName(thisCode, tcText, tnTextLength, NULL, true)))
				{
					// It was found in the global variables

/* We do not have work areas setup yet, so we cannot search them. :-)
				} else if (var = iWorkarea_searchFieldName(comp->line->sourceCode->data + comp->start, comp->length)) {
					// It was found in a table field
					return(var);*/
				}

			} else {
				// Search field names first, variables last.
/*				if (var = iWorkarea_searchFieldName(comp->line->sourceCode->data + comp->start, comp->length))
				{
					// It was found in a table field
					return(var);

				} else*/ if ((var = iVariable_searchForName(thisCode, tcText, tnTextLength, NULL, true))) {
					// It was found in the global variables
				}
			}


		//////////
		// If we found it, make a copy
		//////
			if (var)
			{
				// Create a copy of the variable
				if (var->varType == _VAR_TYPE_OBJECT)
				{
					// It's an object
					varCopy = iVariable_create(NULL, _VAR_TYPE_CHARACTER, NULL, true);
					if (varCopy)
						iDatum_duplicate(&varCopy->value, cgcObjectText, -1);

				} else if (var->varType == _VAR_TYPE_THISCODE) {
					// It's a thisCode reference
					varCopy = iVariable_create(NULL, _VAR_TYPE_CHARACTER, NULL, true);
					if (varCopy)
						iDatum_duplicate(&varCopy->value, cgcThisCodeText, -1);

				} else {
					// It's a traditional variable
					varCopy = iVariable_copy(NULL, var, tlByRef);
				}
				varCopy->compRelated = comp;
				return(varCopy);
			}


		// If we get here, failure
		return(NULL);
	}





//////////
//
// Gets the contiguous components, comprised of every consecutive component hereafter,
// or the quoted content.
//
//////
	SVariable* iEngine_get_contiguousComponents(SThisCode* thisCode, SComp* comp, bool* tlManufactured, s32 valid_iCodeArray[], s32 tnValid_iCodeArrayCount)
	{
		SVariable* varPathname;


		// Make sure our environment is sane
		varPathname = NULL;
		if (comp && comp->line && comp->line->sourceCode && comp->line->sourceCode->data)
		{
			// Find out what the component is
			switch (comp->iCode)
			{
				case _ICODE_DOUBLE_QUOTED_TEXT:
				case _ICODE_SINGLE_QUOTED_TEXT:
					// By definition, quoted content is its own independent thing
					varPathname = iVariable_createAndPopulate_byText(thisCode, _VAR_TYPE_CHARACTER, comp->line->sourceCode->data_u8 + comp->start, comp->length, true);
					break;

				default:
					// Get every contiguous component
					varPathname	= iVariable_createAndPopulate_byText(thisCode, _VAR_TYPE_CHARACTER, comp->line->sourceCode->data_u8 + comp->start, iComps_getContiguousLength(thisCode, comp, valid_iCodeArray, tnValid_iCodeArrayCount, NULL), true);
					break;
			}
		}

		// Indicate where we are
		return(varPathname);
	}




//////////
//
// Called to find the function, execute it, and return the result
//
//////
	void iEngine_get_functionResult(SThisCode* thisCode, SComp* comp, s32 tnRcount, SFunctionParams* rpar)
	{
		u32				lnI, lnParamsFound;
		SFunctionData*	funcData;
		SComp*			compLeftParen;


		// Make sure our environment is sane
		if (comp && (compLeftParen = comp->ll.nextComp) && compLeftParen->iCode == _ICODE_PARENTHESIS_LEFT)
		{
			// Right now, we know we have something like:  xyz(


			//////////
			// Initialize our parameters and return variables
			//////
				memset(rpar, 0, sizeof(*rpar));


			//////////
			// Iterate through each function for matches
			//////
				funcData = &gsKnownFunctions[0];
				while (funcData && funcData->_func != 0)
				{
					// Is this the named function?
					if (funcData->iCode == comp->iCode)
					{
						//////////
						// We need to find the minimum number of parameters between)
						//////
							if (!iiEngine_getParametersBetween(thisCode, ((funcData->map_byValOrByRef) ? funcData->map_byValOrByRef : NULL), compLeftParen, &lnParamsFound, funcData->req_pcount, funcData->max_pcount, rpar))
							{
								rpar->ei.error		= true;
								rpar->ei.errorNum	= _ERROR_INVALID_PARAMETERS;
								return;
							}


						//////////
						// Update rcount and pcount
						//////
							rpar->rpMax		= funcData->max_rcount;
							rpar->rpMin		= funcData->req_rcount;
							rpar->rpCount	= ((tnRcount >= 0) ? min(tnRcount, _MAX_RETURN_COUNT) : rpar->rpMax);
							rpar->ipCount	= lnParamsFound;


						//////////
						// Perform the function
						//////
							funcData->func(NULL, rpar);


						//////////
						// Free every parameter we created
						//////
							for (lnI = 0; lnI < _MAX_PARAMETER_COUNT; lnI++)
							{

								// Delete if populated
								if (rpar->ip[lnI])
									iVariable_delete(thisCode, rpar->ip[lnI], true);

							}


						//////////
						// Return values are in rpar->returns[]
						//////
							return;

					}

					// Move to next function
					++funcData;
				}

				// If we get here, not found
				rpar->ei.error		= true;
				rpar->ei.errorNum	= _ERROR_UNKNOWN_FUNCTION;

		} else {
			// Syntax error
			rpar->ei.error		= true;
			rpar->ei.errorNum	= _ERROR_SYNTAX;
		}
	}




//////////
//
// Called to search for the named component and return its type and a reference to it if possible.
//
// Note:  The value returned may be indicated to be a variable, but that var->varType may indicate
//        another type.  It should be examined to determine the true underlying value, which may
//        alter the *tnType value accordingly.
//
//////
	bool iEngine_get_namedSourceAndType_byComp(SThisCode* thisCode, SComp* comp, void** p, s32* tnType)
	{
		s32				lnI, lnCount;
		bool			llResult, llVarsFirst;
		cs8*			lcVarName;
		u32				lnVarNameLength;
		SThisCode*		thisCodeSearch;
		SObject*		_this;
		SObject*		obj;
		SWorkArea*		wa;
		SFunction*		func;
		SFunction*		adhoc;
		SDllFunc*		dllfunc;
		SVariable*		var;


		// Make sure our environment is sane
		llResult = false;
		if (comp && p && tnType && comp->line && comp->line->sourceCode && comp->line->sourceCode->data_cs8)
		{

			//////////
			// Get the variable name we're searching for
			//////
				lcVarName		= comp->line->sourceCode->data_cs8 + comp->start;
				lnVarNameLength	= (u32)comp->length;


			///////////
			// How are we searching for the rest?
			//
			//		Variables first:	(1) standard names, (2) native names, (3) Aliases,				(4) Params, (5) Returns, (6) Locals, (7) parent chain Private, (8) Globals, (9) Fields,	(10) adhocs, (11) functions, (12) dll functions
			//		Fields first:		(1) standard names, (2) native names, (3) Aliases,	(4) Fields,	(5) Params, (6) Returns, (7) Locals, (8) parent chain Private, (9) Globals,				(10) adhocs, (11) functions, (12) dll functions
			//
			// Note:  standard names are thisForm, this, parent, cparent, cparentN
			// Note:  native names are enabled by an NCSET() setting, and refer to those things which would be listed in AMEMBERS(laMembers, this)
			//
			//////

			//////////
			// (1) standard name
			//////
				_this = thisCode->live->_this;
				if (between(comp->iCode, _ICODE_NATIVE_OBJECTS_MIN, _ICODE_NATIVE_OBJECTS_MAX))
				{
					// Yes, which one?
					switch (comp->iCode)
					{
						case _ICODE_THISFORM:
							 // thisForm
							 *p = iObj_find_thisForm(thisCode, _this);

						case _ICODE_THIS:
							 // this
							 *p = _this;

						case _ICODE_PARENT:
							// parent
							 *p = ((_this) ? _this->parent : NULL);
							 break;

						default:
							// It's a cparent or cparentN reference
							if (comp->iCode == _ICODE_CPARENT)		lnCount = 2;									// cparent is an alias for cparent1, which is the parent container's parent container (this.parent.parent)
							else									lnCount = comp->iCode - _ICODE_CPARENT0 + 1;	// cparentN begins at this.parent for cparent0, this.parent.parent for cparent1, and this.parent.parent.parent for cparent2, etc.

							// Locate the indicated cparent
							for (lnI = 0, obj = _this; obj && lnI < lnCount; lnI++)
								obj = obj->parent;

							// We now have our parent
							*p = obj;
							break;
					}

					// Determine if we were successful
					*tnType = _SOURCE_TYPE_OBJECT;
					return(*p != NULL);

				}


			//////////
			// (2) native names (if enabled)
			//////
				if (propGet_settings_ncset_directNativeMembers(_settings) && _this)
				{
					// Try to locate the native member for the current this object
					var = iObjProp_get_variable_byComp(thisCode, _this, comp);
					if (var)
					{
						// We found the native property
						*p = iVariable_copy(thisCode, var, true);
						return(true);
					}
				}


			//////////
			// (3) aliases
			//////
				iDbf_get_workArea_byAlias_byComp(thisCode, &wa, comp);
				if (wa)
				{
					// It was found as an alias
					*tnType	= _SOURCE_TYPE_ALIAS;
					*p		= wa;
					return(true);
				}


			//////////
			// If we get here, it's not a standard name, a native name, or an alias
			//////
				llVarsFirst = propGet_settings_VariablesFirst(_settings);
				if (llVarsFirst)
				{
					if (thisCode && thisCode->live)
					{
						// (4) Params
						if (thisCode->live->params)
						{
							var = iiVariable_searchForName_variables(thisCode, thisCode->live->params, lcVarName, lnVarNameLength, comp, true);
							if (var)
							{
								*tnType	= _SOURCE_TYPE_VARIABLE;
								*p		= var;
								return(true);
							}
						}

						// (5) Return variables
						if (thisCode->live->returns)
						{
							var = iiVariable_searchForName_variables(thisCode, thisCode->live->returns, lcVarName, lnVarNameLength, comp, true);
							if (var)
							{
								*tnType	= _SOURCE_TYPE_VARIABLE;
								*p		= var;
								return(true);
							}
						}

						// (6) Locals
						if (thisCode->live->locals)
						{
							var = iiVariable_searchForName_variables(thisCode, thisCode->live->locals, lcVarName, lnVarNameLength, comp, true);
							if (var)
							{
								*tnType	= _SOURCE_TYPE_VARIABLE;
								*p		= var;
								return(true);
							}
						}
		
						// (7) Search recursively up the all stack for private variables
						if (thisCode->live->privates)
						{
							for (thisCodeSearch = thisCode; thisCodeSearch; thisCodeSearch = thisCodeSearch->ll.prevThisCode)
							{
								// Search at this level
								var = iiVariable_searchForName_variables(thisCode, thisCodeSearch->live->privates, lcVarName, lnVarNameLength, comp, true);
								if (var)
								{
									*tnType	= _SOURCE_TYPE_VARIABLE;
									*p		= var;
									return(true);
								}
							}
						}
					}

					// (8) Globals
					var = iiVariable_searchForName_variables(thisCode, varGlobals, lcVarName, lnVarNameLength, comp, true);
					if (var)
					{
						*tnType	= _SOURCE_TYPE_VARIABLE;
						*p		= var;
						return(true);
					}

					// (9) Fields
					var = iiVariable_searchForName_fields(thisCode, lcVarName, lnVarNameLength, comp, true);
					if (var)
					{
						*tnType	= _SOURCE_TYPE_FIELD;
						*p		= var;
						return(true);
					}


				} else {
					// (4) Fields
					var = iiVariable_searchForName_fields(thisCode, lcVarName, lnVarNameLength, comp, true);
					if (var)
					{
						*tnType	= _SOURCE_TYPE_FIELD;
						*p		= var;
						return(true);
					}

					if (thisCode && thisCode->live)
					{
						// (5) Params
						if (thisCode->live->params)
						{
							var = iiVariable_searchForName_variables(thisCode, thisCode->live->params, lcVarName, lnVarNameLength, comp, true);
							if (var)
							{
								*tnType	= _SOURCE_TYPE_VARIABLE;
								*p		= var;
								return(true);
							}
						}

						// (6) Return variables
						if (thisCode->live->returns)
						{
							var = iiVariable_searchForName_variables(thisCode, thisCode->live->returns, lcVarName, lnVarNameLength, comp, true);
							if (var)
							{
								*tnType	= _SOURCE_TYPE_VARIABLE;
								*p		= var;
								return(true);
							}
						}

						// (7) Locals
						if (thisCode->live->locals)
						{
							var = iiVariable_searchForName_variables(thisCode, thisCode->live->locals, lcVarName, lnVarNameLength, comp, true);
							if (var)
							{
								*tnType	= _SOURCE_TYPE_VARIABLE;
								*p		= var;
								return(true);
							}
						}

						// (8) Search recursively up the all stack for private variables
						if (thisCode->live->privates)
						{
							for (thisCodeSearch = thisCode; thisCodeSearch; thisCodeSearch = thisCodeSearch->ll.prevThisCode)
							{
								// Search at this level
								var = iiVariable_searchForName_variables(thisCode, thisCodeSearch->live->privates, lcVarName, lnVarNameLength, comp, true);
								if (var)
								{
									*tnType	= _SOURCE_TYPE_VARIABLE;
									*p		= var;
									return(true);
								}
							}
						}
					}

					// (9) Globals
					var = iiVariable_searchForName_variables(thisCode, varGlobals, lcVarName, lnVarNameLength, comp, true);
					if (var)
					{
						*tnType	= _SOURCE_TYPE_VARIABLE;
						*p		= var;
						return(true);
					}
				}

		}


		//////////
		// (10) adhocs
		//////
			// Begin at current stack level, and iterate upwards
			for (thisCodeSearch = thisCode; thisCodeSearch; thisCodeSearch = thisCodeSearch->ll.prevThisCode)
			{
				// Iterate through all adhocs at this level
				for (adhoc = thisCodeSearch->func->firstAdhoc; adhoc; adhoc = adhoc->ll.nextFunc)
				{
					// Is it the same length?
					if (!adhoc->isPrivate && adhoc->name.length == lnVarNameLength)
					{
						// Is it the same name?
						if (_memicmp(adhoc->name.data_cs8, lcVarName, lnVarNameLength) == 0)
						{
							// We found it
							*tnType	= _SOURCE_TYPE_ADHOC;
							*p		= adhoc;
							return(true);
						}
					}
				}
			}


		//////////
		// (11) functions
		//////
			for (func = gsRootFunc; func; func = func->ll.nextFunc)
			{
				// Is it the same length?
				if (func->name.length == lnVarNameLength)
				{
					// Is it the same name?
					if (_memicmp(func->name.data_cs8, lcVarName, lnVarNameLength) == 0)
					{
						// We found it
						*tnType	= _SOURCE_TYPE_FUNCTION;
						*p		= func;
						return(true);
					}
				}
			}


		//////////
		// (12) dll functions
		//////
			for (dllfunc = gsRootDllFunc; dllfunc; dllfunc = dllfunc->ll.nextDllFunc)
			{
				// Is it the same length?
				if (dllfunc->name.length == lnVarNameLength)
				{
					// Is it the same name?
					if (_memicmp(dllfunc->name.data_cs8, lcVarName, lnVarNameLength) == 0)
					{
						// We found it
						*tnType	= _SOURCE_TYPE_DLLFUNC;
						*p		= dllfunc;
						return(true);
					}
				}
			}


		//////////
		// Indicate if it was found
		//////
			return(llResult);

	}




//////////
//
// Called to search for the named component within the object and return a reference to it if possible.
//
//////
	bool iEngine_get_namedSourceAndType_ofObj_byComp(SThisCode* thisCode, SObject* obj, SComp* comp, void** p, s32* tnType)
	{
		SVariable* var;


		//////////
		// Try to locate the native property for the current this object
		//////
			var = iObjProp_get_variable_byComp(thisCode, obj, comp);
			if (var)
			{
				// We found the native property
				*p = iVariable_copy(thisCode, var, true);
				return(true);
			}


		//////////
		// See if it's an event or method
		//////
// TODO:  working here
			var = iObjProp_get_eventOrMethod_byComp(thisCode, obj, comp);
			if (var)
			{
				// We found the native property
				*p = iVariable_copy(thisCode, var, true);
				return(true);
			}


		//////////
		// If we get here, failure
		//////
			return(false);
	}




//////////
//
// Called to find the indicated setter, and execute it if found
//
//////
	void iEngine_executeSetter(SThisCode* thisCode, cs8* name, SVariable* varOld, SVariable* varNew)
	{
// TODO:  When the engine is developed and working, a found setter will suspend execution and branch to that location
	}




//////////
//
// Called to report the indicated error and relate it to the indicated variable (if any)
//
//////
	void iEngine_error(SThisCode* thisCode, u32 tnErrorNumber, SVariable* varRelated)
	{
// TODO:  Report the error and relate the variable
	}




///////////
//
// Signaled repeatedly during VALIDATE and ON VALIDATE from SET AUTOVALIDATE ON to
// convey both meta data as well as
//
//////
	bool iEngine_signal_onValidate(SThisCode* thisCode, SVariable* varTableName, SVariable* varAlias, SVariable* varCdxName, SVariable* varTag, SVariable* varcMessage, SVariable* varIsError, SVariable* varRebuildIndexRequired)
	{
		// Returns the return variable, if we should continue
		// For now, simulate continuing
		return(true);
	}




//////////
//
// Called to raise an event.
// See:  SEvents.
//
// Note:  The return value indicates if the calling signaler should continue propagating this event through to other parent objects (at the same coordinates).
//////
	bool iEngine_raise_event(SThisCode* thisCode, u32 tnEventId, SWindow* win, SObject* obj, void* p)
	{
		if (obj)
		{
			if (tnEventId < 0 || tnEventId > _EVENT_MAX_COUNT)
			{
				// Should never happen
// TODO:  For the extra info, we could add a call stack trace here
				iError_signal(thisCode, _ERROR_INTERNAL_ERROR, NULL, true, NULL, false);
				return(false);
			}

// TODO:  Dispatch obj->ev.methods->userEventCode methods here
			// If there's no default event handler, just ignore it
			if (obj->ev.methods[tnEventId]._event == 0)
				return(true);

			// Which event?
			switch (tnEventId)
			{
				case _EVENT_ONMOUSEMOVE:
					return(obj->ev.methods[tnEventId].event_8(thisCode, win, obj,		obj->ev.varX_onMouseMove,			obj->ev.varY_onMouseMove,
																						obj->ev.varCtrl_onMouseMove,		obj->ev.varAlt_onMouseMove,			obj->ev.varShift_onMouseMove,
																						obj->ev.varClick_onMouseMove));
				case _EVENT_ONMOUSEDOWN:
					return(obj->ev.methods[tnEventId].event_8(thisCode, win, obj,		obj->ev.varX_onMouseDown,			obj->ev.varY_onMouseDown,
																						obj->ev.varCtrl_onMouseDown,		obj->ev.varAlt_onMouseDown,			obj->ev.varShift_onMouseDown,
																						obj->ev.varClick_onMouseDown));
				case _EVENT_ONMOUSEUP:
					return(obj->ev.methods[tnEventId].event_8(thisCode, win, obj,		obj->ev.varX_onMouseUp,				obj->ev.varY_onMouseUp,
																						obj->ev.varCtrl_onMouseUp,			obj->ev.varAlt_onMouseUp,			obj->ev.varShift_onMouseUp,
																						obj->ev.varClick_onMouseUp));
				case _EVENT_ONMOUSEWHEEL:
					return(obj->ev.methods[tnEventId].event_9(thisCode, win, obj,		obj->ev.varX_onMouseWheel,			obj->ev.varY_onMouseWheel,
																						obj->ev.varCtrl_onMouseWheel,		obj->ev.varAlt_onMouseWheel,		obj->ev.varShift_onMouseWheel,
																						obj->ev.varClick_onMouseWheel,
																						obj->ev.varDeltaY_onMouseWheel));
				case _EVENT_ONMOUSECLICKEX:
					return(obj->ev.methods[tnEventId].event_8(thisCode, win, obj,		obj->ev.varX_onMouseClickEx,		obj->ev.varY_onMouseClickEx,
																						obj->ev.varCtrl_onMouseClickEx,		obj->ev.varAlt_onMouseClickEx,		obj->ev.varShift_onMouseClickEx,
																						obj->ev.varClick_onMouseClickEx));
				case _EVENT_ONKEYDOWN:
					return(obj->ev.methods[tnEventId].event_10(thisCode, win, obj,		obj->ev.varCtrl_onKeyDown,			obj->ev.varAlt_onKeyDown,			obj->ev.varShift_onKeyDown,
																						obj->ev.varCaps_onKeyDown,			obj->ev.varAsciiChar_onKeyDown,		obj->ev.varVKey_onKeyDown,
																						obj->ev.varIsCAS_onKeyDown,			obj->ev.varIsAscii_onKeyDown));
				case _EVENT_ONKEYUP:
					return(obj->ev.methods[tnEventId].event_10(thisCode, win, obj,		obj->ev.varCtrl_onKeyUp,			obj->ev.varAlt_onKeyUp,				obj->ev.varShift_onKeyUp,
																						obj->ev.varCaps_onKeyUp,			obj->ev.varAsciiChar_onKeyUp,		obj->ev.varVKey_onKeyUp,
																						obj->ev.varIsCAS_onKeyUp,			obj->ev.varIsAscii_onKeyUp));
				case _EVENT_RESIZE:
					// The passed parameter p must be valid, and is the RECT* of its new size and position
					if (p)
					{
						// Signal the resize event
						return(obj->ev.methods[tnEventId].event_11(thisCode, win, obj, (RECT*)p));

					} else {
						// Should never happen, if it does it's a programming error
// TODO:  For the extra info, we could add a call stack trace here
						iError_signal(thisCode, _ERROR_INTERNAL_ERROR, NULL, true, NULL, false);
					}
					break;

				case _EVENT_ONRESIZE:
					// The passed parameter indicates a delta RECT, showing how much each axis resized
					if (p)
					{
						// Signal the onResize() event
						return(obj->ev.methods[tnEventId].event_11(thisCode, win, obj, (RECT*)p));

					} else {
						// Should never happen, if it does it's a programming error
// TODO:  For the extra info, we could add a call stack trace here
						iError_signal(thisCode, _ERROR_INTERNAL_ERROR, NULL, true, NULL, false);
					}
					break;

				case _EVENT_ONMOVED:
					// The passed parameter indicates the new RECT (new position)
					if (p)
					{
						// Signal the onMoved event
						return(obj->ev.methods[tnEventId].event_11(thisCode, win, obj, (RECT*)p));

					} else {
						// Should never happen, if it does it's a programming error
// TODO:  For the extra info, we could add a call stack trace here
						iError_signal(thisCode, _ERROR_INTERNAL_ERROR, NULL, true, NULL, false);
					}
					break;

				case _EVENT_CAROUSEL_ONTABCLOSE:
					return(obj->ev.methods[tnEventId].event_1(thisCode, win, obj));
					break;

				case _EVENT_CAROUSEL_ONTABCLICK:
				case _EVENT_CAROUSEL_ONTABMOUSEWHEEL:
				case _EVENT_CAROUSEL_ONTABMOUSEMOVE:
				case _EVENT_CAROUSEL_ONTABMOUSEDOWN:
				case _EVENT_CAROUSEL_ONTABMOUSEUP:
				case _EVENT_CAROUSEL_ONTABMOUSEENTER:
				case _EVENT_CAROUSEL_ONTABMOUSELEAVE:
					return(obj->ev.methods[tnEventId].event_12(thisCode, win, obj, p));
					break;

				default:
					// The rest of these events are all handled in the standard way
					return(obj->ev.methods[tnEventId].event_1(thisCode, win, obj));
					//	_EVENT_ONMOUSEENTER
					//	_EVENT_ONMOUSELEAVE
					//	_EVENT_ONMOUSEHOVER
					//	_EVENT_ONLOAD
					//	_EVENT_ONINIT
					//	_EVENT_ONCREATED
					//	_EVENT_ONRENDER
					//	_EVENT_ONPUBLISH
					//	_EVENT_ONQUERYUNLOAD
					//	_EVENT_ONDESTROY
					//	_EVENT_ONUNLOAD
					//	_EVENT_ONGOTFOCUS
					//	_EVENT_ONLOSTFOCUS
					//	_EVENT_ONADDOBJECT
					//	_EVENT_ONADDPROPERTY
					//	_EVENT_ONERROR
					//	_EVENT_ONSCROLLED
					//	_EVENT_ACTIVATE
					//	_EVENT_DEACTIVATE
					//	_EVENT_ONSELECT
					//	_EVENT_ONDESELECT
					//	_EVENT_ONINTERACTIVECHANGE
					//	_EVENT_ONPROGRAMMATICCHANGE
					//	_EVENT_ONSETACTIVECONTROL
					//	_EVENT_ONSPIN

			}
		}

		// Failure on this object if we get here
		// Indicate the caller should continue to signal this event on other objects
		return(true);
	}




//////////
//
// Called to set an event's destination ip address
//
//////
	bool iEngine_set_event(SThisCode* thisCode, u32 tnEventId, SWindow* win, SObject* obj, uptr tnEventAddress)
	{
		// Make sure our environment is sane
		if (obj)
		{
			// Is it a valid event range?
			if (tnEventId >= 0 && tnEventId <= _EVENT_MAX_COUNT)
			{
				// Set the event
				obj->ev.methods[tnEventId]._event = (uptr)tnEventAddress;

				// Indicate success
				return(true);
			}
		}

		// Indicate failure
		return(false);
	}




//////////
//
// Called to update the global _tally value
//
//////
	s64 iEngine_update_tally(SThisCode* thisCode, s64 tnValue)
	{
		s64 lnOldValue;


		// Grab the old value and update
		lnOldValue					= *varTally->value.data_s64;
		*varTally->value.data_s64	= tnValue;
		return(lnOldValue);
	}




//////////
//
// Called to update the global _metaN values
//
//////
	s64 iEngine_update_meta1(SThisCode* thisCode, s64 tnValue)
	{
		s64 lnOldValue;


		// Grab the old value and update
		lnOldValue					= *varMeta1->value.data_s64;
		*varMeta1->value.data_s64	= tnValue;
		return(lnOldValue);
	}

	s64 iEngine_update_meta2(SThisCode* thisCode, s64 tnValue)
	{
		s64 lnOldValue;


		// Grab the old value and update
		lnOldValue					= *varMeta2->value.data_s64;
		*varMeta2->value.data_s64	= tnValue;
		return(lnOldValue);
	}

	s64 iEngine_update_meta3(SThisCode* thisCode, s64 tnValue)
	{
		s64 lnOldValue;


		// Grab the old value and update
		lnOldValue					= *varMeta3->value.data_s64;
		*varMeta3->value.data_s64	= tnValue;
		return(lnOldValue);
	}

	s64 iEngine_update_meta4(SThisCode* thisCode, s64 tnValue)
	{
		s64 lnOldValue;


		// Grab the old value and update
		lnOldValue					= *varMeta4->value.data_s64;
		*varMeta4->value.data_s64	= tnValue;
		return(lnOldValue);
	}

	void iEngine_update_meta5(SThisCode* thisCode, SDatum* data)
	{
		iDatum_duplicate(&varMeta5->value, data);
	}

	void iEngine_update_meta6(SThisCode* thisCode, SDatum* data)
	{
		iDatum_duplicate(&varMeta6->value, data);
	}

	void iEngine_update_meta7(SThisCode* thisCode, SVariable* varSrc)
	{
		iVariable_copy(NULL, varMeta7, varSrc);
	}

	void iEngine_update_meta8(SThisCode* thisCode, SVariable* varSrc)
	{
		iVariable_copy(NULL, varMeta8, varSrc);
	}

	void iEngine_update_meta9(SThisCode* thisCode, SVariable* varSrc)
	{
		iVariable_copy(NULL, varMeta9, varSrc);
	}




//////////
//
// Called to obtain the parameters between the indicated parenthesis.
//
//////
	bool iiEngine_getParametersBetween(SThisCode* thisCode, s8* map_byRefOrByVal, SComp* compLeftParen, u32* paramsFound, u32 requiredCount, u32 maxCount, SFunctionParams* rpar, bool tlForceByRef)
	{
		u32			lnI, lnParamCount;
		bool		llManufactured, llByRef, llUdfParamsByRef;
		SComp*		comp;
		SComp*		compComma;


		//////////
		// Initialize
		//////
			llUdfParamsByRef = propGet_settings_UdfParamsReference(_settings);
			for (lnI = 0; lnI < _MAX_PARAMETER_COUNT; lnI++)
				rpar->ip[lnI] = NULL;


		//////////
		// Begin at the thing to the right of the left parenthesis
		//////
			lnParamCount	= 1;
			comp			= compLeftParen->ll.nextComp;
			for (lnI = 0; comp && comp->iCode != _ICODE_PARENTHESIS_RIGHT; lnI++)
			{
				//////////
				// See if we've gone over our limit
				//////
					if (lnParamCount > maxCount)
					{
						// Too many parameters
						iError_reportByNumber(thisCode, _ERROR_TOO_MANY_PARAMETERS, comp, false);
						return(NULL);
					}


				//////////
				// The component after this must be a comma
				//////
					compComma = comp->ll.nextComp;
					if (!compComma || (compComma->iCode != _ICODE_COMMA && compComma->iCode != _ICODE_PARENTHESIS_RIGHT && lnParamCount > requiredCount))
					{
						// Comma expected error
						iError_reportByNumber(thisCode, _ERROR_COMMA_EXPECTED, comp, false);
						return(NULL);
					}


				//////////
				// Derive whatever this is as a variable
				//////
					// byRef or byVal determined by UDF setting, or by an explicit map override
					if (!map_byRefOrByVal)		llByRef = llUdfParamsByRef;
					else						llByRef = llUdfParamsByRef | (map_byRefOrByVal[lnI] == (_UDFPARMS_REFERENCE + '0'));

					// Grab the variable reference
					rpar->ip[lnI] = iEngine_get_variableName_fromComponent(thisCode, comp, &llManufactured, tlForceByRef | llByRef);


				// Move to next component
				++lnParamCount;
				comp = iComps_getNth(thisCode, compComma, 1);
			}


		//////////
		// Indicate how many we found
		//////
			*paramsFound = --lnParamCount;


		//////////
		// Indicate success
		//////
			return(lnParamCount >= requiredCount && lnParamCount <= maxCount);
	}




//////////
//
// Called to delete the indicated breakpoint
//
//////
	void iBreakpoint_delete(SThisCode* thisCode, SBreakpoint** breakpoint)
	{
		SBreakpoint* bp;


		// Make sure our environment is sane
		if (breakpoint && *breakpoint && (*breakpoint)->isUsed &&
			(uptr)*breakpoint >= gBreakpoints->_data &&
			(uptr)*breakpoint <= gBreakpoints->_data + gBreakpoints->populatedLength - sizeof(SBreakpoint))
		{
			// Get a local copy of our pointer
			bp = *breakpoint;

			// Reset the remote
			*breakpoint = NULL;

			// Delete the items as they are
			bp->isUsed = true;

			// Delete any source code for this breakpoint
			if (bp->executeCode)
				iSourceCode_delete(thisCode, &bp->executeCode);
		}
	}




//////////
//
// Called to add a new breakpoint.  It only creates the entry and populates the type.
// For conditional breakpoints, or breakpoints with code they will need to be created
// and added manually by the code in the calling algorithm.
//
//////
	SBreakpoint* iBreakpoint_add(SThisCode* thisCode, SBreakpoint** breakpoint, u32 tnType)
	{
		u32				lnI;
		SBreakpoint*	bp;


		// Make sure our environment is sane
		if (breakpoint)
		{
			//////////
			// Validate it's a known type
			//////
				switch (tnType)
				{
					case _BREAKPOINT_ALWAYS:
					case _BREAKPOINT_CONDITIONAL_TRUE:
					case _BREAKPOINT_CONDITIONAL_FALSE:
					case _BREAKPOINT_CONDITIONAL_TRUE_COUNTDOWN:
					case _BREAKPOINT_CONDITIONAL_FALSE_COUNTDOWN:
						break;

					default:
						// We don't know what to do here... silently fail
						return(NULL);
				}
				// If we get here, we're valid


			//////////
			// Make sure we've initialized our breakpoint structure
			//////
				if (!gBreakpoints)
					iBuilder_createAndInitialize(&gBreakpoints, -1);


			//////////
			// Try to find an empty slot
			//////
				for (lnI = 0; lnI < gBreakpoints->populatedLength; lnI += sizeof(SBreakpoint))
				{
					// Grab this pointer
					bp = (SBreakpoint*)(gBreakpoints->data_u8 + lnI);

					// Is this an empty slot?
					if (!bp->isUsed)
						break;	// Yes, we can reuse it
				}


			//////////
			// Allocate if we didn't find an empty slot
			//////
				if (lnI >= gBreakpoints->populatedLength)
					bp = (SBreakpoint*)iBuilder_allocateBytes(gBreakpoints, sizeof(SBreakpoint));


			//////////
			// Populate it with the basic info
			//////
				if (bp)
				{
					bp->isUsed	= true;
					bp->type	= tnType;
				}


			// Indicate our success or failure
			*breakpoint	= bp;
			return(bp);
		}

		// If we get here, failure
		return(NULL);
	}




//////////
//
// Called to delete the source code item
//
//////
	void iSourceCode_delete(SThisCode* thisCode, SSourceCode** sourceCode)
	{
		SSourceCode* sc;


		// Make sure our environment is sane
		if (sourceCode && *sourceCode)
		{
			// Get a copy of the pointer
			sc = *sourceCode;

			// Clear the pointer
			*sourceCode = NULL;

			// Delete the items
			iFunction_politelyDeleteChain(thisCode, &sc->firstFunction);
			iVariable_politelyDeleteChain(thisCode, &sc->params,		true);
			iVariable_politelyDeleteChain(thisCode, &sc->returns,		true);
			iVariable_politelyDeleteChain(thisCode, &sc->privates,		true);
			iVariable_politelyDeleteChain(thisCode, &sc->locals,		true);
			iVariable_politelyDeleteChain(thisCode, &sc->scoped,		true);
		}
	}
