// lasm_defs.h
// Jul.04.2016 RCH -- temporarily removed
// 	bool				iilasm_pass0_define								(SLasmPass0* p0);// SLasmCmdLine* cmdLine, SLasmFile* file, SLine** lineProcessing, SComp* compDefine, SComp* compName);
// 	bool				iilasm_pass0_define__callback_bypassEscapedBraces(SCallback* cb);
// 	bool				iilasm_pass0_define__getParameters				(SLasmPass0* p0);
// 	SLasmDefine*		iilasm_pass0_lookup_define_byName				(SComp* compName, SLasmDefine* defineRoot);


// pass0.cpp
// From ilasm_pass0():
//		stores #define statements
// Jul.04.2016 RCH -- Temporarily removed.  See save_code.h.
// 				} else if (p0.comp->iCode == _ICODE_LASM_DEFINE) {
// 					// define
// 					if (!iilasm_pass0_define(&p0))
// 					{
// 						// If we need to terminate on errors
// 						if (p0.cmdLine->w.Wfatal_errors)
// 							return;		// Error was displayed by the called function
// 
// 					} else {
// 						// Line is completed
// 						ilasm_add_lineStatus(p0.line, _LASM_STATUS_COMPLETED, true);
// 					}


// Appended elsewhere in the file:
// //////////
// //
// // Parses out #define syntax, creating a new SLasmDefine structure if valid.
// //
// //////
// //
// // Syntax must be:
// //
// //		"#define"
// //		name
// //
// //		optional "("
// //			:repeat until matching ")"
// //				name
// //					optional ,
// //						loop
// //					else
// //						exit
// //			:end
// //
// //		optional {
// //			all content to matching }, with every intermediate \} escaped
// //		optional {{
// //			all content to matching }}, with every intermediate \} escaped
// //		else
// //			:repeat
// //				all content to end of line
// //				optional "\"
// //					next line
// //					loop
// //				else
// //					exit
// //			:end
// //
// //////
// 	// Note:  It is known that when this function is called, the first component is _ICODE_LASM_DEFINE
// 	bool iilasm_pass0_define(SLasmPass0* p0)
// 	{
// // 		SComp*			compDefine;
// // 		SComp*			compName;
// // 		SCallback		cb;
// // 		s8				buffer1[_MAX_FNAME];
// // 		s8				buffer2[_MAX_FNAME];
// // 		
// // 		
// // 		//////////
// // 		// Is there a valid component?
// // 		//////
// // 			compDefine	= p0->compNext;
// // 			compName	= iComps_Nth(compDefine);
// // 			if (!compName)
// // 			{
// // 				// It's a #define but nothing comes after
// // 				++compDefine->line->status.errors;
// // 				printf("--Error(%d,%d): token was expected in %s\n", compDefine->line->lineNumber, compDefine->start + compDefine->length, p0->file->fileName.data_s8);
// // 				goto politely_fail;
// // 			}
// // 
// // 
// // 		//////////
// // 		// Validate that it's alphanumeric
// // 		//////
// // 			if (!iiComps_isAlphanumeric_byContent(compName))
// // 			{
// // 				++compName->line->status.errors;
// // 				printf("--Error(%d,%d): alphanumeric was expected in %s\n", compName->line->lineNumber, compName->start, p0->file->fileName.data_s8);
// // 				goto politely_fail;
// // 			}
// // 
// // 
// // 		//////////
// // 		// Validate it's a unique symbol
// // 		//////
// // 			if ((p0->define = iilasm_pass0_lookup_define_byName(compName, gsLasmDefines)))
// // 			{
// // 				// It was already found
// // 				memcpy(buffer1, p0->define->compName->line->sourceCode.data_s8 + p0->define->compName->start, p0->define->compName->length);
// // 				memcpy(buffer2, p0->file->fileName.data_s8, p0->file->fileName.length);
// // 				buffer1[p0->define->compName->length]	= 0;
// // 				buffer2[p0->file->fileName.length]	= 0;
// // 				printf("--Error(%d,%d): token '%s' already defined in %s on (%d,%d)\n", compName->line->lineNumber, compName->start, buffer1, buffer2, p0->define->compName->line->lineNumber, p0->define->compName->start);
// // 			}
// // 
// // 
// // 		//////////
// // 		// Grab it
// // 		//////
// // 			p0->define = newAlloc(SLasmDefine, gsLasmDefines);
// // 			if (!p0->define)
// // 			{
// // 				// Internal error
// // 				++compName->line->status.errors;
// // 				printf("--Error(%d): an unexpected internal error occurred processing a #define in %s\n", compName->line->lineNumber, p0->file->fileName.data_s8);
// // 				goto politely_fail;
// // 			}
// // 
// // 			// Copy the name
// // 			p0->define->compName = compName;
// // 
// // 
// // 		//////////
// // 		// Load any optional parameters
// // 		//////
// // 			if ((p0->compNext = iComps_Nth(compName, 1, false)))
// // 			{
// // 				// Does it have parameters?
// // 				if (p0->compNext->iCode == _ICODE_PARENTHESIS_LEFT)
// // 				{
// // 					// It begins with an open parenthesis
// // 					if (!iilasm_pass0_define__getParameters(p0))
// // 					{
// // 						++p0->compNext->line->status.errors;
// // 						printf("--Error(%d,%d): unable to parse parameters in %s\n", p0->compNext->line->lineNumber, p0->compNext->start, p0->file->fileName.data_s8);
// // 						goto politely_fail;
// // 					}
// // 					// When we get here, line and compNext are pointing to the closing )
// // 
// // 					// Skip past the closing )
// // 					if (!(p0->compNext = iComps_Nth(p0->compNext)))
// // 					{
// // 						++p0->comp->line->status.errors;
// // 						printf("--Error: unexpected end of file in %s\n", p0->file->fileName.data_s8);
// // 						goto politely_fail;
// // 					}
// // 					// When we get here, we're on the first component after
// // 				}
// // 
// // 				// Is it brace content
// // 				if (p0->compNext->iCode == _ICODE_BRACE_LEFT || p0->compNext->iCode == _ICODE_DOUBLE_BRACE_LEFT)
// // 				{
// // 					// Begins with {/{{, we need to find the closing }}/}
// // 					memset(&cb, 0, sizeof(cb));
// // 					if (!iComps_scanForward_withCallback(p0->compNext, &cb, true, (uptr)&iilasm_pass0_define__callback_bypassEscapedBraces))
// // 					{
// // 						// Not found
// // 						++p0->compNext->line->status.errors;
// // 						printf("--Error(%d,%d): unable to locate matching } %s\n", p0->compNext->line->lineNumber, p0->compNext->start + p0->compNext->length, p0->file->fileName.data_s8);
// // 						goto politely_fail;
// // 					}
// // 
// // 					// Move to post-{/{{ and pre-}/}}
// // 					p0->comp	= iComps_Nth(p0->comp);
// // 					cb.comp		= iComps_Nth(cb.comp, -1);
// // 
// // 					// Copy inner content (between the { and }, and excluding those two characters)
// // 					p0->define->firstLine = iComps_copyComps_toNewLines(p0->comp, cb.comp, true, true);
// // 
// // 				} else {
// // 					// Copy everything, including multiple lines ending in '\'
// // 					p0->define->firstLine = iLine_copyComps_toNewLines_untilTerminating(p0->line, compNext, _ICODE_BACKSLASH, true, true, &cb);
// // 				}
// // 				// If we get here, success
// // 
// // 				// Unescape \{, \}, \{{, \}}, and \\ within the block
// // 				iLines_unescape_iCodes(p0->define->firstLine,	_ICODE_BRACE_LEFT,			_ICODE_BRACE_RIGHT,			_ICODE_BACKSLASH);
// // 				iLines_unescape_iCodes(p0->define->firstLine,	_ICODE_DOUBLE_BRACE_LEFT,	_ICODE_DOUBLE_BRACE_RIGHT,	-1);
// // 			}
// // 
// // 
// // 		//////////
// // 		// Position our line to the last location, which completes the #define
// // 		//////
// // 			p0->line = cb.line;
// // 
// // 
// // 
// // politely_fail:
// // 		// If we get here, error
// 		return(false);
// 	}
// 
// 	// Uses cb->value for iCode
// 	bool iilasm_pass0_define__callback_bypassEscapedBraces(SCallback* cb)
// 	{
// 		SComp* compNext;
// 
// 
// 		//////////
// 		// Is it a \{ or \} ?
// 		//////
// 			if (cb->comp->iCode == _ICODE_BACKSLASH)
// 			{
// 				// Grab the next component
// 				compNext = cb->comp->ll.nextComp;
// 
// 				// Is it { or } ?
// 				if (compNext && (compNext->iCode == _ICODE_BRACE_LEFT || compNext->iCode == _ICODE_DOUBLE_BRACE_LEFT || compNext->iCode == _ICODE_BRACE_RIGHT || compNext->iCode == _ICODE_DOUBLE_BRACE_RIGHT))
// 				{
// 					// Yes, but are they directly adjacent?
// 					if (iiComps_areCompsAdjacent(cb->comp, compNext))
// 					{
// 						// Yes, so skip this one because it's escaped
// 						cb->comp = compNext;
// 
// 						// Go ahead and keep looking after these two components are skipped
// 						return(true);
// 					}
// 				}
// 			}
// 		
// 
// 		//////////
// 		// Is it our target }?
// 		//////
// 			if (cb->comp->iCode == cb->iCode)
// 			{
// 				cb->flag = true;	// Found it
// 				return(false);		// Yes, so indicate there should be no more searching
// 			}
// 
// 
// 		//////////
// 		// If we get here, not found, so continue on searching
// 		//////
// 			return(true);
// 
// 	}
// 
// 
// 
// 
// //////////
// //
// // Called to extract parameters from a (a,b,...,z) sequence
// // Note:  Upon entry the *compProcessing should be pointing to _ICODE_PARENTHESIS_LEFT
// //
// //////
// 	bool iilasm_pass0_define__getParameters(SLasmPass0* p0)
// 	{
// // 		s32		lnI;
// // 		bool	llSkipTest;
// // 		SComp*	comp;
// // 
// // 
// // 		//////////
// // 		// Should be on opening parenthesis
// // 		//////
// // 			if (comp->iCode != _ICODE_PARENTHESIS_LEFT)
// // 			{
// // 				++p0->line->status.errors;
// // 				printf("--Error(%d,%d): unexpected internal error processing #define parameters %s\n", p0->line->lineNumber, comp->start, p0->file->fileName.data_s8);
// // 				return(false);
// // 			}
// // 
// // 
// // 		//////////
// // 		// Iterate loading each one
// // 		//////
// // 			for (lnI = 0, llSkipTest = false; lnI < _LASM_MAX_DEFINE_PARAMS && comp->iCode != _ICODE_PARENTHESIS_RIGHT; lnI++)
// // 			{
// // 
// // 				//////////
// // 				// Validate it's a token
// // 				//////
// // 					if (!llSkipTest && !iiComps_isAlphanumeric_by_iCode(comp))
// // 					{
// // 						++p0->line->status.errors;
// // 						printf("--Error(%d,%d): expected token in %s\n", p0->line->lineNumber, comp->start, p0->file->fileName.data_s8);
// // 						goto politely_fail;
// // 					}
// // 					llSkipTest = false;
// // 
// // 
// // 				//////////
// // 				// Increase count, grab the name
// // 				//////
// // 					++p0->define->paramCount;
// // 					iiDatum_duplicate_fromComp(&p0->define->params[lnI], comp);
// // 
// // 
// // 				//////////
// // 				// Skip to next parameter
// // 				//////
// // 					if (iiLine_skipTo_nextComp(&p0->line, &comp) < 0)
// // 					{
// // 						// Unexpected end of file
// // 						printf("--Error: unexpected end of file in %s\n", p0->file->fileName.data_s8);
// // 						goto politely_fail;
// // 					}
// // 
// // 
// // 				//////////
// // 				// Skip past comma
// // 				//////
// // 					if (comp->iCode == _ICODE_COMMA)
// // 					{
// // 
// // 						//////////
// // 						// Skip past it
// // 						//////
// // 							if (iiLine_skipTo_nextComp(&p0->line, &comp) < 0)
// // 							{
// // 								// Unexpected end of file
// // 								printf("--Error: unexpected end of file in %s\n", p0->file->fileName.data_s8);
// // 								goto politely_fail;
// // 							}
// // 
// // 
// // 						//////////
// // 						// Next component must be right parenthesis or alphanumeric
// // 						//////
// // 							if (comp->iCode != _ICODE_PARENTHESIS_RIGHT && !iiComps_isAlphanumeric_by_iCode(comp))
// // 							{
// // 								++p0->line->status.errors;
// // 								printf("--Error(%d,%d): expected token or right parenthesis in %s\n", p0->line->lineNumber, comp->start, p0->file->fileName.data_s8);
// // 								goto politely_fail;
// // 							}
// // 
// // 							// We don't need to double-check alphanumeric above
// // 							llSkipTest = true;
// // 
// // 					}
// // 					// When we get here, we're on either ) or the next token name
// // 
// // 			}
// // 			// When we get here, comp is sitting on )
// // 
// // 
// // 		//////////
// // 		// Success!
// // 		//////
// // 			*compProcessing = comp;
// // 			return(true);
// // 
// // 
// // politely_fail:
// // 		//////////
// // 		// Set current parameters, and then return false
// // 		//////
// // 			*compProcessing = comp;
// 			return(false);
// 	}
// 
// 
// 
// 
// //////////
// //
// // Lookup the #define by name
// //
// //////
// 	SLasmDefine* iilasm_pass0_lookup_define_byName(SComp* compName, SLasmDefine* defineRoot)
// 	{
// 		SLasmDefine* define;
// 
// 
// 		// Iterate through the defines
// 		for (define = defineRoot; define; define = (SLasmDefine*)define->ll.next)
// 		{
// 			// Is it the same length?
// 			if (define->compName->text.length == compName->text.length)
// 			{
// 				// Is it the same name?
// 				if (_memicmp(define->compName->text.data_s8, compName->text.data_s8, compName->text.length) == 0)
// 				{
// 					// Yes, this is the symbol
// 					return(define);
// 				}
// 			}
// 		}
// 
// 		// If we get here, not found
// 		return(NULL);
// 	}


// pass-0.cpp
// iilsa_pass0_include()
// Removed because it duplicates the logic seen in ilsa_includeFile_append()
//
//					// Is it an absolute path
//					if (ilsa_isAbsolutePath(p0->filename, lnFilenameLength))
//					{
//						// Error opening the file
//						lcErrorText = cgc_lsa_error_opening_include_file;
//						break;
//					}
//
//					// Iterate through the known include file paths and attempt to load its
//					ilsa_includePaths_iterate_start(&iiFile, p0->filename);
//					while (!iiFile.wasOpened)
//					{
//						// Try to open it
//						if (ilsa_includePaths_iterate_try(&iiFile, llIsFileValid, &p0->fileInclude))
//						{
//							// It was opened
//							break;
//
//						} else if (!llIsFileValid) {
//							// Something was wrong with the filename (the path might be too long)
//							// We ignore it... it will eventually fall through and error out if it's not found elsewhere
//						}
//
//						// Move to the next iteration
//						if (!ilsa_includePaths_iterate_next(&iiFile))
//						{
//							// Error opening the file
//							lcErrorText = cgc_lsa_error_opening_include_file;
//							break;
//						}
//					}
//
//					// Was the file loaded?
//					if (!iiFile.wasOpened)
//					{
