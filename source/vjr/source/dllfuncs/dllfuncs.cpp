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
// These were moved to global variables to support 64-bit Win64 DLL dispatches
//////
extern "C"
{
	s32			gnDll_typeStep, gnDll_pointersStep, gnDll_valuesStep;
	u32			gnDll_paramCount, gnDll_returnType, gnDll_sizeofTypes, gnDll_sizeofPointers, gnDll_sizeofValues, gnDll_saveParamBytes;
	void*		gnDll_funcAddress;
	void*		gnDll_typesBaseRtoL;
	void*		gnDll_pointersBaseRtoL;
	void*		gnDll_valuesBaseRtoL;
#if defined(__64_BIT_COMPILER__)
	void*		gnDll_typesBaseLtoR;
	void*		gnDll_pointersBaseLtoR;
	void*		gnDll_valuesBaseLtoR;
#endif
	void*		gnDll_returnValuesBase;
	u32			gnDll_types		[_MAX_DLL_PARAMS];		// Refer to _types_* constants
	void*		gnDll_pointers	[_MAX_DLL_PARAMS];		// Pointers to data the start of every data item
	SDllVals	gnDll_values	[_MAX_DLL_PARAMS];		// Values stored if they need to be converted

	// See dll_dispatch_64.asm, an assembly language function that's called below
	extern void idll_dispatch_64_asm(void);
};




//////////
//
// Called to call into the dll function
//
//////
	void iDllFunc_dispatch(SThisCode* thisCode, SFunctionParams* rpar, SDllFunc* dfunc, SComp* compDllName)
	{
		s32		lnI;
		u32		lnParamsFound;
		bool	llResult;

#if defined(__GNUC__)
		rpar->ei.error		= true;
		rpar->ei.errorNum	= _ERROR_FEATURE_NOT_AVAILABLE;
		rpar->ei.errorComp	= compDllName;
		return;
#endif

		// Loop entered only for structured exit on early error
		while (1)
		{

			//////////
			// We need to find the minimum number of parameters between)
			//////
				llResult = iiEngine_getParametersBetween(thisCode, NULL, iComps_getNth(thisCode, compDllName, 1), &lnParamsFound, dfunc->ipCount, dfunc->ipCount, rpar, true);
				if (!llResult || lnParamsFound != dfunc->ipCount)
				{
					rpar->ei.error		= true;
					rpar->ei.errorNum	= _ERROR_INVALID_PARAMETERS;
					break;
				}


			//////////
			// Update rpCount and ipCount
			//////
				rpar->rpCount	= ((dfunc->rp.type == _DLL_TYPE_VOID) ? 0 : 1);
				rpar->rpMax		= rpar->rpCount;
				rpar->rpMin		= rpar->rpCount;
				rpar->ipCount	= lnParamsFound;


			//////////
			// Dispatch into the DLL
			//////
				iiDllFunc_dispatch_lowLevel(thisCode, rpar, dfunc);


			// Structured exit
			// At this point, rpar->ei.error is set if error
			break;
		}


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

	void iiDllFunc_dispatch_lowLevel(SThisCode* thisCode, SFunctionParams* rpar, SDllFunc* dfunc)
	{
		s32 lnI;


		//////////
		// Initialize
		//////
			memset(&gnDll_types,	0, sizeof(gnDll_types));
			memset(&gnDll_pointers,	0, sizeof(gnDll_pointers));
			memset(&gnDll_values,	0, sizeof(gnDll_values));

			gnDll_typeStep		= sizeof(gnDll_types[0]);
			gnDll_pointersStep	= sizeof(gnDll_pointers[0]);
			gnDll_valuesStep	= sizeof(gnDll_values);


		//////////
		// Build the parameter list to pass to the dll
		//////
			for (lnI = 0; lnI < rpar->ipCount; lnI++)
			{
				//////////
				// Translate the target type
				//////
					gnDll_types[lnI] = dfunc->ip[lnI].type;
					switch (dfunc->ip[lnI].type)
					{
						case _DLL_TYPE_S16:
							// Signed 16-bit
							if (dfunc->ip[lnI].udfSetting == _UDFPARMS_REFERENCE)
							{
								// They want it updated by reference
								if (rpar->ip[lnI]->varType == _VAR_TYPE_S16)
								{
									// We can directly pass a pointer to it
									gnDll_types[lnI]		= _DLL_TYPE_VP;
									gnDll_pointers[lnI]		= (void*)&rpar->ip[lnI]->value.data_s16;

								} else {
									// We must translate it, then store it back afterward
									gnDll_values[lnI]._s16	= iiVariable_getAs_s16(thisCode, rpar->ip[lnI], false, &rpar->ei.error, &rpar->ei.errorNum);
									gnDll_pointers[lnI]		= (void*)&gnDll_values[lnI]._s16;
									gnDll_types[lnI]		= _DLL_TYPE__byRef_postProcess;
								}

							} else {
								// By value
								gnDll_values[lnI]._s16	= iiVariable_getAs_s16(thisCode, rpar->ip[lnI], false, &rpar->ei.error, &rpar->ei.errorNum);
								gnDll_pointers[lnI]		= (void*)&gnDll_values[lnI]._s16;
							}
							break;

						case _DLL_TYPE_U16:
							// Unsigned 16-bit
							if (dfunc->ip[lnI].udfSetting == _UDFPARMS_REFERENCE)
							{
								// They want it updated by reference
								if (rpar->ip[lnI]->varType == _VAR_TYPE_U16)
								{
									// We can directly pass a pointer to it
									gnDll_types[lnI]		= _DLL_TYPE_VP;
									gnDll_pointers[lnI]		= (void*)&rpar->ip[lnI]->value.data_u16;

								} else {
									// We must translate it, then store it back afterward
									gnDll_values[lnI]._u16	= iiVariable_getAs_u16(thisCode, rpar->ip[lnI], false, &rpar->ei.error, &rpar->ei.errorNum);
									gnDll_pointers[lnI]		= (void*)&gnDll_values[lnI]._u16;
									gnDll_types[lnI]		= _DLL_TYPE__byRef_postProcess;
								}

							} else {
								// By value
								gnDll_values[lnI]._u16	= iiVariable_getAs_u16(thisCode, rpar->ip[lnI], false, &rpar->ei.error, &rpar->ei.errorNum);
								gnDll_pointers[lnI]		= (void*)&gnDll_values[lnI]._u16;
							}
							break;

						case _DLL_TYPE_S32:
							// Signed 32-bit
							if (dfunc->ip[lnI].udfSetting == _UDFPARMS_REFERENCE)
							{
								// They want it updated by reference
								if (rpar->ip[lnI]->varType == _VAR_TYPE_S32)
								{
									// We can directly pass a pointer to it
									gnDll_types[lnI]		= _DLL_TYPE_VP;
									gnDll_pointers[lnI]		= (void*)&rpar->ip[lnI]->value.data_s32;

								} else {
									// We must translate it, then store it back afterward
									gnDll_values[lnI]._s32	= iiVariable_getAs_s32(thisCode, rpar->ip[lnI], false, &rpar->ei.error, &rpar->ei.errorNum);
									gnDll_pointers[lnI]		= (void*)&gnDll_values[lnI]._s32;
									gnDll_types[lnI]		= _DLL_TYPE__byRef_postProcess;
								}

							} else {
								// By value
								gnDll_values[lnI]._s32	= iiVariable_getAs_s32(thisCode, rpar->ip[lnI], false, &rpar->ei.error, &rpar->ei.errorNum);
								gnDll_pointers[lnI]		= (void*)&gnDll_values[lnI]._s32;
							}
							break;

						case _DLL_TYPE_U32:
							// Unsigned 32-bit
							if (dfunc->ip[lnI].udfSetting == _UDFPARMS_REFERENCE)
							{
								// They want it updated by reference
								if (rpar->ip[lnI]->varType == _VAR_TYPE_U32)
								{
									// We can directly pass a pointer to it
									gnDll_types[lnI]		= _DLL_TYPE_VP;
									gnDll_pointers[lnI]		= (void*)&rpar->ip[lnI]->value.data_u32;

								} else {
									// We must translate it, then store it back afterward
									gnDll_values[lnI]._u32	= iiVariable_getAs_u32(thisCode, rpar->ip[lnI], false, &rpar->ei.error, &rpar->ei.errorNum);
									gnDll_pointers[lnI]		= (void*)&gnDll_values[lnI]._u32;
									gnDll_types[lnI]		= _DLL_TYPE__byRef_postProcess;
								}

							} else {
								// By value
								gnDll_values[lnI]._u32	= iiVariable_getAs_u32(thisCode, rpar->ip[lnI], false, &rpar->ei.error, &rpar->ei.errorNum);
								gnDll_pointers[lnI]		= (void*)&gnDll_values[lnI]._u32;
							}
							break;

						case _DLL_TYPE_F32:
							// Floating point 32-bit
							if (dfunc->noPrototype)
							{
								// All 32-bit floating point values are physically passed as 64-bit doubles for no-prototype functions
								if (dfunc->ip[lnI].udfSetting == _UDFPARMS_REFERENCE)
								{
									// They want it updated by reference
									if (rpar->ip[lnI]->varType == _VAR_TYPE_F64)
									{
										// We can directly pass a pointer to it
										gnDll_types[lnI]		= _DLL_TYPE_VP;
										gnDll_pointers[lnI]		= (void*)&rpar->ip[lnI]->value.data_f64;

									} else {
										// We must translate it, then store it back afterward
										gnDll_values[lnI]._f64	= iiVariable_getAs_f64(thisCode, rpar->ip[lnI], false, &rpar->ei.error, &rpar->ei.errorNum);
										gnDll_pointers[lnI]		= (void*)&gnDll_values[lnI]._f64;
										gnDll_types[lnI]		= _DLL_TYPE__byRef_postProcess;
									}

								} else {
									// By value
									gnDll_values[lnI]._f64	= iiVariable_getAs_f64(thisCode, rpar->ip[lnI], false, &rpar->ei.error, &rpar->ei.errorNum);
									gnDll_pointers[lnI]		= (void*)&gnDll_values[lnI]._f64;
								}

							} else {
								if (dfunc->ip[lnI].udfSetting == _UDFPARMS_REFERENCE)
								{
									// They want it updated by reference
									if (rpar->ip[lnI]->varType == _VAR_TYPE_F32)
									{
										// We can directly pass a pointer to it
										gnDll_types[lnI]		= _DLL_TYPE_VP;
										gnDll_pointers[lnI]		= (void*)&rpar->ip[lnI]->value.data_f32;

									} else {
										// We must translate it, then store it back afterward
										gnDll_values[lnI]._f32	= iiVariable_getAs_f32(thisCode, rpar->ip[lnI], false, &rpar->ei.error, &rpar->ei.errorNum);
										gnDll_pointers[lnI]		= (void*)&gnDll_values[lnI]._f32;
										gnDll_types[lnI]		= _DLL_TYPE__byRef_postProcess;
									}

								} else {
									// By value
									gnDll_values[lnI]._f32	= iiVariable_getAs_f32(thisCode, rpar->ip[lnI], false, &rpar->ei.error, &rpar->ei.errorNum);
									gnDll_pointers[lnI]		= (void*)&gnDll_values[lnI]._f32;
								}
							}
							break;

						case _DLL_TYPE_F64:
							// Floating point 64-bit
							if (dfunc->ip[lnI].udfSetting == _UDFPARMS_REFERENCE)
							{
								// They want it updated by reference
								if (rpar->ip[lnI]->varType == _VAR_TYPE_F64)
								{
									// We can directly pass a pointer to it
									gnDll_types[lnI]		= _DLL_TYPE_VP;
									gnDll_pointers[lnI]		= (void*)&rpar->ip[lnI]->value.data_f64;

								} else {
									// We must translate it, then store it back afterward
									gnDll_values[lnI]._f64	= iiVariable_getAs_f64(thisCode, rpar->ip[lnI], false, &rpar->ei.error, &rpar->ei.errorNum);
									gnDll_pointers[lnI]		= (void*)&gnDll_values[lnI]._f64;
									gnDll_types[lnI]		= _DLL_TYPE__byRef_postProcess;
								}

							} else {
								// By value
								gnDll_values[lnI]._f64	= iiVariable_getAs_f64(thisCode, rpar->ip[lnI], false, &rpar->ei.error, &rpar->ei.errorNum);
								gnDll_pointers[lnI]		= (void*)&gnDll_values[lnI]._f64;
							}
							break;

						case _DLL_TYPE_S64:
							// Signed 64-bit
							if (dfunc->ip[lnI].udfSetting == _UDFPARMS_REFERENCE)
							{
								// They want it updated by reference
								if (rpar->ip[lnI]->varType == _VAR_TYPE_S64)
								{
									// We can directly pass a pointer to it
									gnDll_types[lnI]		= _DLL_TYPE_VP;
									gnDll_pointers[lnI]		= (void*)&rpar->ip[lnI]->value.data_s64;

								} else {
									// We must translate it, then store it back afterward
									gnDll_values[lnI]._s64	= iiVariable_getAs_s64(thisCode, rpar->ip[lnI], false, &rpar->ei.error, &rpar->ei.errorNum);
									gnDll_pointers[lnI]		= (void*)&gnDll_values[lnI]._s64;
									gnDll_types[lnI]		= _DLL_TYPE__byRef_postProcess;
								}

							} else {
								// By value
								gnDll_values[lnI]._s64	= iiVariable_getAs_s64(thisCode, rpar->ip[lnI], false, &rpar->ei.error, &rpar->ei.errorNum);
								gnDll_pointers[lnI]		= (void*)&gnDll_values[lnI]._s64;
							}
							break;

						case _DLL_TYPE_U64:
							// Unsigned 64-bit
							if (dfunc->ip[lnI].udfSetting == _UDFPARMS_REFERENCE)
							{
								// They want it updated by reference
								if (rpar->ip[lnI]->varType == _VAR_TYPE_U64)
								{
									// We can directly pass a pointer to it
									gnDll_types[lnI]		= _DLL_TYPE_VP;
									gnDll_pointers[lnI]		= (void*)&rpar->ip[lnI]->value.data_u64;

								} else {
									// We must translate it, then store it back afterward
									gnDll_values[lnI]._u64	= iiVariable_getAs_u64(thisCode, rpar->ip[lnI], false, &rpar->ei.error, &rpar->ei.errorNum);
									gnDll_pointers[lnI]		= (void*)&gnDll_values[lnI]._u64;
									gnDll_types[lnI]		= _DLL_TYPE__byRef_postProcess;
								}

							} else {
								// By value
								gnDll_values[lnI]._u64	= iiVariable_getAs_u64(thisCode, rpar->ip[lnI], false, &rpar->ei.error, &rpar->ei.errorNum);
								gnDll_pointers[lnI]		= (void*)&gnDll_values[lnI]._u64;
							}
							break;

						case _DLL_TYPE_STRING:			// s8*
							if (dfunc->ip[lnI].udfSetting == _UDFPARMS_REFERENCE)
							{
								// Passed by reference (directly updateable)
								gnDll_types[lnI]		= _DLL_TYPE_VP;
								gnDll_pointers[lnI]		= (void*)&rpar->ip[lnI]->value.data_s8;

							} else {
								// By value
								// Make a copy of the data, and then pass it
								iDatum_duplicate(&gnDll_values[lnI]._datum, &rpar->ip[lnI]->value);
								gnDll_pointers[lnI]		= (void*)&rpar->ip[lnI]->value.data_s8;
							}
							break;

						case _DLL_TYPE_IDISPATCH:		// void*
							if (rpar->ip[lnI]->varType != _VAR_TYPE_IDISPATCH)
							{
								// Error, the type is invalid
								rpar->ei.error		= true;
								rpar->ei.errorNum	= _ERROR_PARAMETER_IS_INCORRECT;
								rpar->ei.errorComp	= rpar->ip[lnI]->compRelated;
								return;
							}

							// Store the IDispatch pointer
							gnDll_values[lnI]._idispatch	= rpar->ip[lnI]->value.data_idispatch;
							gnDll_pointers[lnI]				= (void*)&gnDll_values[lnI]._idispatch;
							break;

						default:
							// Should never happen
							rpar->ei.error			= true;
							rpar->ei.errorNum		= _ERROR_INTERNAL_ERROR;
							rpar->ei.errorComp		= rpar->ip[lnI]->compRelated;
							return;
					}


				//////////
				// If there was an error, we're done
				//////
					if (rpar->ei.error)
						return;		// Error
			}


		//////////
		// Dispatch into the dll
		//////
			gnDll_saveParamBytes		= 0;
			gnDll_sizeofTypes			= sizeof(gnDll_types[0]);
			gnDll_sizeofPointers		= sizeof(gnDll_pointers[0]);
			gnDll_sizeofValues			= sizeof(gnDll_values[0]);
			gnDll_funcAddress			= dfunc->funcAddress;
			gnDll_paramCount			= dfunc->ipCount;
			gnDll_typesBaseRtoL			= (void*)&gnDll_types[dfunc->ipCount - 1];
			gnDll_pointersBaseRtoL		= (void*)&gnDll_pointers[dfunc->ipCount - 1];
			gnDll_valuesBaseRtoL		= (void*)&gnDll_values[dfunc->ipCount - 1];
			gnDll_returnValuesBase		= (void*)&gnDll_values[0];
			gnDll_returnType			= dfunc->rp.type;

#if defined(__32_BIT_COMPILER__)
			#include "dll_dispatch_32.asm"

#elif defined(__64_BIT_COMPILER__)
			// #include "dll_dispatch_64.asm"		// Note:  dll_dispatch_64.asm is assembled/compiled externally because Visual Studio 2010 and earlier do not support 64-bit inline assembly.
			// This code is inside dll_dispatch_64.asm, which is only assembled in x64 builds:
			gnDll_typesBaseLtoR			= (void*)&gnDll_types[0];
			gnDll_pointersBaseLtoR		= (void*)&gnDll_pointers[0];
			gnDll_valuesBaseLtoR		= (void*)&gnDll_values[0];
			idll_dispatch_64_asm();
#endif


		//////////
		// Populate the return value into the variable
		//////
			// Make sure the variable is there
			if (dfunc->rp.type != _DLL_TYPE_VOID && !rpar->rp[0])
				rpar->rp[0] = iVariable_create(thisCode, _VAR_TYPE_S32, NULL, true, 0);

			// Based on the type, populate it
			switch (dfunc->rp.type)
			{
				case _DLL_TYPE_S16:
				case _DLL_TYPE_S32:
					iVariable_setVarType(thisCode, rpar->rp[0], _VAR_TYPE_S32);
					*rpar->rp[0]->value.data_s32 = gnDll_values[0]._s32;
					break;

				case _DLL_TYPE_U16:
				case _DLL_TYPE_U32:
					iVariable_setVarType(thisCode, rpar->rp[0], _VAR_TYPE_U32);
					*rpar->rp[0]->value.data_u32 = gnDll_values[0]._u32;
					break;

				case _DLL_TYPE_F32:
					iVariable_setVarType(thisCode, rpar->rp[0], _VAR_TYPE_F32);
					*rpar->rp[0]->value.data_f32 = gnDll_values[0]._f32;
					break;

				case _DLL_TYPE_F64:
					iVariable_setVarType(thisCode, rpar->rp[0], _VAR_TYPE_F64);
					*rpar->rp[0]->value.data_f64 = gnDll_values[0]._f64;
					break;

				case _DLL_TYPE_S64:
					iVariable_setVarType(thisCode, rpar->rp[0], _VAR_TYPE_S64);
					*rpar->rp[0]->value.data_s64 = gnDll_values[0]._s64;
					break;

				case _DLL_TYPE_U64:
					iVariable_setVarType(thisCode, rpar->rp[0], _VAR_TYPE_U64);
					*rpar->rp[0]->value.data_u64 = gnDll_values[0]._u64;
					break;

				case _DLL_TYPE_STRING:
					iVariable_setVarType(thisCode, rpar->rp[0], _VAR_TYPE_CHARACTER);
					iDatum_duplicate(&rpar->rp[0]->value, gnDll_values[0]._s8p, (s32)strlen(gnDll_values[0]._s8p));
					break;
			}


		//////////
		// Fixup any post-process variables
		//////
			for (lnI = 0; lnI < rpar->ipCount; lnI++)
			{
				// Does this one need post processing?
				if ((gnDll_types[lnI] & _DLL_TYPE__byRef_postProcess) != 0)
				{

					//////////
					// The value which was used went through values[lnI].*, and
					// now it needs to be copied / converted back to its source
					//////
						switch (dfunc->ip[lnI].type)
						{
							case _DLL_TYPE_S16:
								iVariable_set_s32_toExistingType(thisCode, &rpar->ei, rpar->ip[lnI], (s32)gnDll_values[lnI]._s16);
								break;
							case _DLL_TYPE_U16:
								iVariable_set_u32_toExistingType(thisCode, &rpar->ei, rpar->ip[lnI], (u32)gnDll_values[lnI]._u16);
								break;
							case _DLL_TYPE_S32:
								iVariable_set_s32_toExistingType(thisCode, &rpar->ei, rpar->ip[lnI], gnDll_values[lnI]._s32);
								break;
							case _DLL_TYPE_U32:
								iVariable_set_u32_toExistingType(thisCode, &rpar->ei, rpar->ip[lnI], gnDll_values[lnI]._u32);
								break;
							case _DLL_TYPE_F32:
								if (dfunc->noPrototype)
								{
									// Non-prototyped functions actually physically pass 64-bit values for 32-bit definitions
									iVariable_set_f64_toExistingType(thisCode, &rpar->ei, rpar->ip[lnI], gnDll_values[lnI]._f64);

								} else {
									// Normal 32-bit conveyance
									iVariable_set_f32_toExistingType(thisCode, &rpar->ei, rpar->ip[lnI], gnDll_values[lnI]._f32);
								}
								break;
							case _DLL_TYPE_F64:
								iVariable_set_f64_toExistingType(thisCode, &rpar->ei, rpar->ip[lnI], gnDll_values[lnI]._f64);
								break;
							case _DLL_TYPE_S64:
								iVariable_set_s64_toExistingType(thisCode, &rpar->ei, rpar->ip[lnI], gnDll_values[lnI]._s64);
								break;
							case _DLL_TYPE_U64:
								iVariable_set_u64_toExistingType(thisCode, &rpar->ei, rpar->ip[lnI], gnDll_values[lnI]._u64);
								break;

							case _DLL_TYPE_STRING:
								// Delete the existing string, and replace with the new version
								iDatum_delete(&rpar->ip[lnI]->value, false);
								rpar->ip[lnI]->value.data_vp	= gnDll_values[lnI]._datum.data_vp;
								rpar->ip[lnI]->value.length		= gnDll_values[lnI]._datum.length;
								break;
						}

				}
			}
			// When we get here, we're finished

	}




//////////
//
// Add the DLL reference to their list of known functions
//
//////
	bool iDllFunc_add(SThisCode* thisCode, SFunctionParams* rpar, SDllFuncParam* rp, SDllFuncParam ip[], s32 tnIpCount, SComp* compFunctionName, SComp* compAliasName, SComp* compDllName, SThisCode* onAccess, SThisCode* onAssign, bool tlNoPrototype, bool tlVariadic)
	{
		s32			lnI, lnAttempt, lnFuncNameLength;
		void*		funcAddress;
		SDllFunc*	dfunc;
		SDllLib*	dlib;
		char		funcName[_MAX_PATH];


		// Make sure the environment is sane
		rpar->ei.error		= false;
		rpar->ei.errorNum	= _ERROR_OKAY;
		if (rpar && compFunctionName && compDllName)
		{

			//////////
			// Try to open the DLL
			//////
				if (!(dlib = iDllLib_open(thisCode, compDllName)))
				{
					// Unknown
					rpar->ei.error		= true;
					rpar->ei.errorNum	= _ERROR_DLL_NOT_FOUND;
					return(false);
				}


			//////////
			// Try to access the function
			//////
				lnFuncNameLength = min(compFunctionName->length, sizeof(funcName) - 1);
				memcpy(funcName, compFunctionName->line->sourceCode->data_cs8 + compFunctionName->start, lnFuncNameLength);
				funcName[lnFuncNameLength] = 0;

				// Iterate through twice trying to find it.  Why?
				for (lnAttempt = 0, funcAddress = 0; !funcAddress && lnAttempt < 2; lnAttempt++)
				{
					// On the second attempt...
					if (lnAttempt == 1)
					{
						// ...append an "A" after the name (it may be like "MessageBox" needing to be "MessageBoxA")
						funcName[lnFuncNameLength + 0] = 'A';
						funcName[lnFuncNameLength + 1] = 0;
					}

					// Iterate through the list of dll candidates to see if we an find the function
					for (lnI = 0; !funcAddress && lnI < _MAX_DLL_HMODULES && dlib->dllHandle[lnI]; lnI++)
						funcAddress = (void*)GetProcAddress(dlib->dllHandle[lnI], funcName);
				}

				// Did we find it?
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
							rpar->ei.error		= true;
							rpar->ei.errorNum	= _ERROR_OUT_OF_MEMORY;
							return(false);
						}

						// Append the name
						iDatum_duplicate(&dfunc->name, funcName, lnFuncNameLength);
					}

					// Update with the information
					memcpy(&dfunc->rp, rp, sizeof(dfunc->rp));
					memcpy(&dfunc->ip, ip, sizeof(dfunc->ip));
					dfunc->ipCount		= tnIpCount;
#if defined(_M_X64)
					dfunc->noPrototype	= tlNoPrototype;
					dfunc->isVariadic	= tlVariadic;
#endif
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
			rpar->ei.error		= true;
			rpar->ei.errorNum	= _ERROR_INTERNAL_ERROR;
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
				if (dfunc->name.length == lnFuncNameLength && iDatum_compare(&dfunc->name, funcName, lnFuncNameLength) == 0)
					return(dfunc);	// Found it by name

				// Alias name
				if (dfunc->alias.length == lnFuncNameLength && iDatum_compare(&dfunc->alias, funcName, lnFuncNameLength) == 0)
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
	const s8	cgc_kernel32_dll[]		= "kernel32.dll";
	const s8	cgc_gdi32_dll[]			= "gdi32.dll";
	const s8	cgc_user32_dll[]		= "user32.dll";
	const s8	cgc_mpr_dll[]			= "mpr.dll";
	const s8	cgc_advapi32_dll[]		= "advapi32.dll";

	HMODULE		ghModule_kernel32		= NULL;
	HMODULE		ghModule_gdi32			= NULL;
	HMODULE		ghModule_user32			= NULL;
	HMODULE		ghModule_mpr			= NULL;
	HMODULE		ghModule_advapi32		= NULL;

	SDllLib* iDllLib_open(SThisCode* thisCode, SComp* compDllName)
	{
		s32			lnLength;
		HMODULE		dllHandle;
		SDllLib*	dlib;
		s8			win32Dir[_MAX_PATH];
		s8			dllName[_MAX_PATH];


		//////////
		// Initialize
		//////
			lnLength = min(compDllName->length, sizeof(dllName) - 1);
			memcpy(dllName, compDllName->line->sourceCode->data_cs8 + compDllName->start, lnLength);
			dllName[lnLength] = 0;


		//////////
		// Open the library
		//////
			if (compDllName->iCode == _ICODE_WIN32API)
			{
				// Are they not yet loaded?
				if (!ghModule_kernel32 || !ghModule_gdi32 || !ghModule_user32 || !ghModule_mpr || !ghModule_advapi32)
				{
					// Grab the win32 path
					if(SUCCEEDED(SHGetFolderPath(NULL, CSIDL_SYSTEM | CSIDL_FLAG_CREATE, NULL, 0, win32Dir)))
					{
						// Load each module
						if (!ghModule_kernel32)
						{
							sprintf(dllName, "%s\\%s", win32Dir, cgc_kernel32_dll);
							ghModule_kernel32 = LoadLibrary(dllName);
						}

						if (!ghModule_gdi32)
						{
							sprintf(dllName, "%s\\%s", win32Dir, cgc_gdi32_dll);
							ghModule_gdi32 = LoadLibrary(dllName);
						}

						if (!ghModule_user32)
						{
							sprintf(dllName, "%s\\%s", win32Dir, cgc_user32_dll);
							ghModule_user32 = LoadLibrary(dllName);
						}

						if (!ghModule_mpr)
						{
							sprintf(dllName, "%s\\%s", win32Dir, cgc_mpr_dll);
							ghModule_mpr = LoadLibrary(dllName);
						}

						if (!ghModule_advapi32)
						{
							sprintf(dllName, "%s\\%s", win32Dir, cgc_advapi32_dll);
							ghModule_advapi32 = LoadLibrary(dllName);
						}
					}
				}

			} else {
				// A specific library
				dllHandle = LoadLibraryA(dllName);
				if (!dllHandle)
					return(NULL);	// Failure
			}


		//////////
		// See if it already exists
		//////
			for (dlib = gsRootDllLib; dlib; dlib = (SDllLib*)dlib->ll->next)
			{
				// If the name is the same, we'll use it
				if (compDllName->iCode == _ICODE_WIN32API)
				{
					// Look for a match for all of the handles
					if (dlib->dllHandle[0] == ghModule_kernel32 && dlib->dllHandle[1] == ghModule_gdi32 && dlib->dllHandle[2] == ghModule_user32 && dlib->dllHandle[3] == ghModule_mpr && dlib->dllHandle[4] == ghModule_advapi32)
					{
						// This is our win32api grouping
						++dlib->refCount;
						break;
					}

				} else {
					// This is the matching dll
					if (dlib->dllHandle[0] == dllHandle)
					{
						// This is the existing entry we can reuse
						++dlib->refCount;
						break;
					}
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
					if (compDllName->iCode == _ICODE_WIN32API)
					{
						// Store the win32api search handles
						dlib->dllHandle[0] = ghModule_kernel32;
						dlib->dllHandle[1] = ghModule_gdi32;
						dlib->dllHandle[2] = ghModule_user32;
						dlib->dllHandle[3] = ghModule_mpr;
						dlib->dllHandle[4] = ghModule_advapi32;

					} else {
						// Store the handle
						dlib->dllHandle[0] = dllHandle;
					}

					// Initialize the rest
					dlib->refCount = 1;
					iDatum_duplicate(&dlib->dllName, compDllName->line->sourceCode->data_cs8 + compDllName->start, compDllName->length);

			}


		//////////
		// Return the entry
		//////
			return(dlib);

	}
