//////////
//
// /libsf/source/vjr/commands/dllfuncs/dllfuncs.cpp
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
// Version 0.58
// Copyright (c) 2015 by Rick C. Hodgin
//////
// Last update:
//     Jul.31.2015
//////
// Change log:
//     Jul.31.2015 - Initial creation
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
//////
//
// To add a new function, see the instructions in command_defs.h.
//
//




//////////
//
// Called to call into the dll function
//
//////
	void iDllFunc_dispatch(SThisCode* thisCode, SFunctionParams* rpar, SDllFunc* dfunc)
	{
	}




//////////
//
// Add the DLL reference to their list of known functions
//
//////
	bool iDllFunc_add(SThisCode* thisCode, SFunctionParams* rpar, SDllFuncParam* rp, SDllFuncParam ip[], s32 tnIpCount, SComp* compFunctionName, SComp* compAliasName, SComp* compDllName, SThisCode* onAccess, SThisCode* onAssign)
	{
		s32			lnFuncNameLength;
		void*		funcAddress;
		SDllFunc*	dfunc;
		SDllLib*	dlib;
		char		funcName[_MAX_PATH];


		// Make sure the environment is sane
		rpar->error		= false;
		rpar->errorNum	= _ERROR_OKAY;
		if (rpar && compFunctionName && compDllName)
		{

			//////////
			// Try to open the DLL
			//////
				if (!(dlib = iDllLib_open(thisCode, compDllName)))
				{
					// Unknown
					rpar->error		= true;
					rpar->errorNum	= _ERROR_DLL_NOT_FOUND;
					return(false);
				}


			//////////
			// Try to access the function
			//////
				memset(&funcName, 0, sizeof(funcName));
				lnFuncNameLength = min(compFunctionName->length, sizeof(funcName) - 1);
				memcpy(funcName, compFunctionName->line->sourceCode->data_cs8 + compFunctionName->start, lnFuncNameLength);
				funcAddress = (void*)GetProcAddress(dlib->dllHandle, funcName);
				if (funcAddress)
				{
					// Try to find the existing function
					dfunc = iDllFunc_find_byName(thisCode, funcName, lnFuncNameLength);
					if (!dfunc)
					{
						// Create a new entry
						dfunc = (SDllFunc*)iLl_appendNewNodeAtEnd((SLL**)&gsRootDllFunc, sizeof(SDllFunc));
						if (!dfunc)
						{
							// Out of memory
							rpar->error		= true;
							rpar->errorNum	= _ERROR_OUT_OF_MEMORY;
							return(false);
						}

						// Append the name
						iDatum_duplicate(&dfunc->name, funcName, lnFuncNameLength);
					}

					// Update with the information
					memcpy(&dfunc->rp, rp, sizeof(dfunc->rp));
					memcpy(&dfunc->ip, ip, sizeof(dfunc->ip));
					dfunc->ipCount		= tnIpCount;
					dfunc->funcAddress	= funcAddress;
					dfunc->dlib			= dlib;

					// Remove the alias name (if any)
					iDatum_delete(&dfunc->alias, false);

					// Update the alias if need be
					if (compAliasName)
						iDatum_duplicate(&dfunc->alias, compAliasName->line->sourceCode->data_cs8 + compAliasName->start, compAliasName->length);

					// Store the onAccess() and onAssign() functions (if any)
					dfunc->onAccess	= onAccess;
					dfunc->onAssign	= onAssign;

					// When we get here, success
					return(true);
				}

		} else {
			// Should never happen
			rpar->error		= true;
			rpar->errorNum	= _ERROR_INTERNAL_ERROR;
		}

		// If we get here, failure
		return(false);
	}




//////////
//
// Called to locate a dll function that's been declared by name.
//
//////
	SDllFunc* iDllFunc_find_byName(SThisCode* thisCode, s8* funcName, s32 lnFuncNameLength)
	{
// TODO:  No support for overloaded functions, but there probably should be.
		SDllFunc* dfunc;


		// Make sure our function name is valid
		if (funcName && lnFuncNameLength >= 1)
		{
			// Iterate through all declared dll functions
			for (dfunc = gsRootDllFunc; dfunc; dfunc = (SDllFunc*)dfunc->ll->next)
			{
				// Raw name
				if (dfunc->name.length == lnFuncNameLength && iDatum_compare(&dfunc->name, funcName, lnFuncNameLength))
					return(dfunc);	// Found it by name

				// Alias name
				if (dfunc->alias.length == lnFuncNameLength && iDatum_compare(&dfunc->alias, funcName, lnFuncNameLength))
					return(dfunc);	// Found it by alias
			}
			// If we get here, not found
		}

		// Indicate error
		return(NULL);
	}




//////////
//
// Called to open the Dll library
//
//////
	SDllLib* iDllLib_open(SThisCode* thisCode, SComp* compDllName)
	{
		HMODULE		dllHandle;
		SDllLib*	dlib;
		char		dllName[_MAX_PATH];


		//////////
		// Initialize
		//////
			memset(dllName, 0, sizeof(dllName));
			memcpy(dllName, compDllName->line->sourceCode->data_cs8 + compDllName->start, min(compDllName->length, sizeof(dllName) - 1));


		//////////
		// Open the library
		//////
			dllHandle = LoadLibraryA(dllName);
			if (!dllHandle)
				return(NULL);	// Failure


		//////////
		// See if it already exists
		//////
			for (dlib = gsRootDllLib; dlib; dlib = (SDllLib*)dlib->ll->next)
			{
				// If the name is the same, we'll use it
				if (dlib->dllHandle == dllHandle)
				{
					// This is the existing entry we can reuse
					++dlib->refCount;
					break;
				}
			}
			// If we get here, it wasn't found


		//////////
		// Add if need be
		//////
			if (!dlib)
			{
				// Add a new entry
				dlib = (SDllLib*)iLl_appendNewNodeAtEnd((SLL**)&gsRootDllLib, sizeof(SDllLib));
				if (!dlib)
				{
					FreeLibrary(dllHandle);
					return(NULL);	// Failure
				}


				//////////
				// Copy info
				//////
					dlib->dllHandle = dllHandle;
					dlib->refCount	= 1;
					iDatum_duplicate(&dlib->dllName, compDllName->line->sourceCode->data_cs8 + compDllName->start, compDllName->length);

			}


		//////////
		// Return the entry
		//////
			return(dlib);

	}
