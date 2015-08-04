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
	struct SValues
	{
		union {
			s16			_s16;
			s32			_s32;
			s64			_s64;

			f32			_f32;
			f64			_f64;

			s16			_u16;
			s32			_u32;
			s64			_u64;

			s8*			_s8p;
			void*		_vp;
			IDispatch*	_idispatch;

			SDatum		_datum;
		};
	};

	const u32	_types_byRef_postProcess	= 128;

	void iiDllFunc_dispatch(SThisCode* thisCode, SFunctionParams* rpar, SDllFunc* dfunc)
	{
		s32			lnI, lnTypeStep, lnPointersStep, lnValuesStep;
		u32			lnParamCount, lnReturnType, lnSizeofTypes, lnSizeofPointers, lnSizeofValues;
		void*		funcAddress;
		void*		types_base;
		void*		pointers_base;
		void*		values_base;
		void*		return_values_base;
		u32			types	[_MAX_DLL_PARAMS];		// Refer to _types_* constants
		void*		pointers[_MAX_DLL_PARAMS];		// Pointers to data the start of every data item
		SValues		values	[_MAX_DLL_PARAMS];		// Values stored if they need to be converted


		//////////
		// Initialize
		//////
			memset(&types,		0, sizeof(types));
			memset(&pointers,	0, sizeof(pointers));
			memset(&values,		0, sizeof(values));

			lnTypeStep			= sizeof(types[0]);
			lnPointersStep		= sizeof(pointers[0]);
			lnValuesStep		= sizeof(values);


		//////////
		// Build the parameter list to pass to the dll
		//////
			for (lnI = 0; lnI < rpar->ipCount; lnI++)
			{
				//////////
				// Translate the target type
				//////
					types[lnI] = dfunc->ip[lnI].type;
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
									types[lnI]			= _DLL_TYPE_VP;
									pointers[lnI]		= (void*)&rpar->ip[lnI]->value.data_s16;

								} else {
									// We must translate it, then store it back afterward
									values[lnI]._s16	= iiVariable_getAs_s16(thisCode, rpar->ip[lnI], false, &rpar->ei.error, &rpar->ei.errorNum);
									pointers[lnI]		= (void*)&values[lnI]._s16;
									types[lnI]			= _types_byRef_postProcess;
								}

							} else {
								// By value
								values[lnI]._s16	= iiVariable_getAs_s16(thisCode, rpar->ip[lnI], false, &rpar->ei.error, &rpar->ei.errorNum);
								pointers[lnI]		= (void*)&values[lnI]._s16;
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
									types[lnI]			= _DLL_TYPE_VP;
									pointers[lnI]		= (void*)&rpar->ip[lnI]->value.data_u16;

								} else {
									// We must translate it, then store it back afterward
									values[lnI]._u16	= iiVariable_getAs_u16(thisCode, rpar->ip[lnI], false, &rpar->ei.error, &rpar->ei.errorNum);
									pointers[lnI]		= (void*)&values[lnI]._u16;
									types[lnI]			= _types_byRef_postProcess;
								}

							} else {
								// By value
								values[lnI]._u16	= iiVariable_getAs_u16(thisCode, rpar->ip[lnI], false, &rpar->ei.error, &rpar->ei.errorNum);
								pointers[lnI]		= (void*)&values[lnI]._u16;
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
									types[lnI]			= _DLL_TYPE_VP;
									pointers[lnI]		= (void*)&rpar->ip[lnI]->value.data_s32;

								} else {
									// We must translate it, then store it back afterward
									values[lnI]._s32	= iiVariable_getAs_s32(thisCode, rpar->ip[lnI], false, &rpar->ei.error, &rpar->ei.errorNum);
									pointers[lnI]		= (void*)&values[lnI]._s32;
									types[lnI]			= _types_byRef_postProcess;
								}

							} else {
								// By value
								values[lnI]._s32	= iiVariable_getAs_s32(thisCode, rpar->ip[lnI], false, &rpar->ei.error, &rpar->ei.errorNum);
								pointers[lnI]		= (void*)&values[lnI]._s32;
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
									types[lnI]			= _DLL_TYPE_VP;
									pointers[lnI]		= (void*)&rpar->ip[lnI]->value.data_u32;

								} else {
									// We must translate it, then store it back afterward
									values[lnI]._u32	= iiVariable_getAs_u32(thisCode, rpar->ip[lnI], false, &rpar->ei.error, &rpar->ei.errorNum);
									pointers[lnI]		= (void*)&values[lnI]._u32;
									types[lnI]			= _types_byRef_postProcess;
								}

							} else {
								// By value
								values[lnI]._u32	= iiVariable_getAs_u32(thisCode, rpar->ip[lnI], false, &rpar->ei.error, &rpar->ei.errorNum);
								pointers[lnI]		= (void*)&values[lnI]._u32;
							}
							break;

						case _DLL_TYPE_F32:
							// Floating point 32-bit
							if (dfunc->ip[lnI].udfSetting == _UDFPARMS_REFERENCE)
							{
								// They want it updated by reference
								if (rpar->ip[lnI]->varType == _VAR_TYPE_F32)
								{
									// We can directly pass a pointer to it
									types[lnI]			= _DLL_TYPE_VP;
									pointers[lnI]		= (void*)&rpar->ip[lnI]->value.data_f32;

								} else {
									// We must translate it, then store it back afterward
									values[lnI]._f32	= iiVariable_getAs_f32(thisCode, rpar->ip[lnI], false, &rpar->ei.error, &rpar->ei.errorNum);
									pointers[lnI]		= (void*)&values[lnI]._f32;
									types[lnI]			= _types_byRef_postProcess;
								}

							} else {
								// By value
								values[lnI]._f32	= iiVariable_getAs_f32(thisCode, rpar->ip[lnI], false, &rpar->ei.error, &rpar->ei.errorNum);
								pointers[lnI]		= (void*)&values[lnI]._f32;
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
									types[lnI]			= _DLL_TYPE_VP;
									pointers[lnI]		= (void*)&rpar->ip[lnI]->value.data_f64;

								} else {
									// We must translate it, then store it back afterward
									values[lnI]._f64	= iiVariable_getAs_f64(thisCode, rpar->ip[lnI], false, &rpar->ei.error, &rpar->ei.errorNum);
									pointers[lnI]		= (void*)&values[lnI]._f64;
									types[lnI]			= _types_byRef_postProcess;
								}

							} else {
								// By value
								values[lnI]._f64	= iiVariable_getAs_f64(thisCode, rpar->ip[lnI], false, &rpar->ei.error, &rpar->ei.errorNum);
								pointers[lnI]		= (void*)&values[lnI]._f64;
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
									types[lnI]			= _DLL_TYPE_VP;
									pointers[lnI]		= (void*)&rpar->ip[lnI]->value.data_s64;

								} else {
									// We must translate it, then store it back afterward
									values[lnI]._s64	= iiVariable_getAs_s64(thisCode, rpar->ip[lnI], false, &rpar->ei.error, &rpar->ei.errorNum);
									pointers[lnI]		= (void*)&values[lnI]._s64;
									types[lnI]			= _types_byRef_postProcess;
								}

							} else {
								// By value
								values[lnI]._s64	= iiVariable_getAs_s64(thisCode, rpar->ip[lnI], false, &rpar->ei.error, &rpar->ei.errorNum);
								pointers[lnI]		= (void*)&values[lnI]._s64;
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
									types[lnI]			= _DLL_TYPE_VP;
									pointers[lnI]		= (void*)&rpar->ip[lnI]->value.data_u64;

								} else {
									// We must translate it, then store it back afterward
									values[lnI]._u64	= iiVariable_getAs_u64(thisCode, rpar->ip[lnI], false, &rpar->ei.error, &rpar->ei.errorNum);
									pointers[lnI]		= (void*)&values[lnI]._u64;
									types[lnI]			= _types_byRef_postProcess;
								}

							} else {
								// By value
								values[lnI]._u64	= iiVariable_getAs_u64(thisCode, rpar->ip[lnI], false, &rpar->ei.error, &rpar->ei.errorNum);
								pointers[lnI]		= (void*)&values[lnI]._u64;
							}
							break;

						case _DLL_TYPE_STRING:			// s8*
							if (dfunc->ip[lnI].udfSetting == _UDFPARMS_REFERENCE)
							{
								// Passed by reference (directly updateable)
								types[lnI]			= _DLL_TYPE_VP;
								pointers[lnI]		= (void*)&rpar->ip[lnI]->value.data_s8;

							} else {
								// By value
								// Make a copy of the data, and then pass it
								iDatum_duplicate(&values[lnI]._datum, &rpar->ip[lnI]->value);
								pointers[lnI]		= (void*)&rpar->ip[lnI]->value.data_s8;
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
							values[lnI]._idispatch	= rpar->ip[lnI]->value.data_idispatch;
							pointers[lnI]			= (void*)&values[lnI]._idispatch;
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
			lnSizeofTypes		= sizeof(types[0]);
			lnSizeofPointers	= sizeof(pointers[0]);
			lnSizeofValues		= sizeof(values[0]);
			funcAddress			= dfunc->funcAddress;
			lnParamCount		= dfunc->ipCount;
			types_base			= (void*)&types[dfunc->ipCount - 1];
			pointers_base		= (void*)&pointers[dfunc->ipCount - 1];
			values_base			= (void*)&values[dfunc->ipCount - 1];
			return_values_base	= (void*)&values[0];
			lnReturnType		= dfunc->rp.type;
			_asm
			{
				//////////
				//
				// Inline assembly to push parameters onto the stack:
				//
				//		eax -- general purpose
				//		ebx	-- function address
				//		ecx	-- count
				//		edx	-- address of types
				//		esi	-- address of pointers
				//		edi	-- address of values, and address of return value
				//////
					//
					// The code below simulates a for loop:
					//
					//		for (initializePart; testPart; incrementPart)
					//
					//////////

					// initializePart
					mov		ecx,lnParamCount			// lnParamCount	= dfunc->ipCount
					mov		edx,types_base				// typePtr		= &types[lnParamCount - 1]
					mov		esi,pointers_base			// pointersPtr	= &pointers[lnParamCount - 1]
					mov		edi,values_base				// valuesPtr	= &values[lnParamCount - 1]
					jmp		push_next_param

prepare_for_next_param:
					// incrementPart
					dec		ecx							// lnParamCount--
					sub		edx,lnSizeofTypes			// --typePtr
					sub		esi,lnSizeofPointers		// --pointersPtr
					sub		edi,lnSizeofValues			// --valuesPtr

push_next_param:
					// testPart
					cmp		ecx,0						// lnParamCount > 0
					jz		finished_with_stack_ops

					// switch (types[lnI])
					mov		eax,dword ptr [edx]
					cmp		eax,_DLL_TYPE_S16			// case _DLL_TYPE_S16, goto push_s16
					jz		push_s16
					cmp		eax, _DLL_TYPE_U16			// case _DLL_TYPE_U16, goto push_u16
					jz		push_u16
					cmp		eax, _DLL_TYPE_S32			// case _DLL_TYPE_S32, goto push_s32
					jz		push_s32
					cmp		eax, _DLL_TYPE_U32			// case _DLL_TYPE_S64, goto push_s64
					jz		push_u32
					cmp		eax, _DLL_TYPE_F32			// case _DLL_TYPE_F32, goto push_f32
					jz		push_f32
					cmp		eax, _DLL_TYPE_F64			// case _DLL_TYPE_F64, goto push_f64
					jz		push_f64
					cmp		eax, _DLL_TYPE_S64			// case _DLL_TYPE_S64, goto push_s64
					jz		push_s64
					cmp		eax, _DLL_TYPE_U64			// case _DLL_TYPE_U64, goto push_u64
					jz		push_u64

					// If we get here, it has to be _DLL_TYPE_VP
					jmp		push_vp						// default, goto push_s16

push_s16:
					movsx	eax,word ptr [edi]
					push	eax
					jmp		prepare_for_next_param

push_u16:
					movzx	eax,word ptr [edi]
					push	eax
					jmp		prepare_for_next_param

push_s32:
push_u32:
push_f32:
push_vp:
					mov		eax,dword ptr [edi]
					push	eax
					jmp		prepare_for_next_param

push_f64:
push_s64:
push_u64:
					mov		eax,dword ptr [edi]
					push	eax
					mov		eax,dword ptr [edi+4]
					push	eax
					jmp		prepare_for_next_param

finished_with_stack_ops:
					// Dispatch into the DLL function
					call	funcAddress

					// Store return value if any
					mov		edi,return_values_base

					// switch (types[lnI])
					mov		eax,lnReturnType
					cmp		eax,_DLL_TYPE_VOID
					jmp		store_nothing
					cmp		eax,_DLL_TYPE_S16			// case _DLL_TYPE_S16, goto store_s16
					jz		store_s16
					cmp		eax, _DLL_TYPE_U16			// case _DLL_TYPE_U16, goto store_u16
					jz		store_u16
					cmp		eax, _DLL_TYPE_S32			// case _DLL_TYPE_S32, goto store_s32
					jz		store_s32
					cmp		eax, _DLL_TYPE_U32			// case _DLL_TYPE_S64, goto store_s64
					jz		store_u32
					cmp		eax, _DLL_TYPE_F32			// case _DLL_TYPE_F32, goto store_f32
					jz		store_f32
					cmp		eax, _DLL_TYPE_F64			// case _DLL_TYPE_F64, goto store_f64
					jz		store_f64
					cmp		eax, _DLL_TYPE_S64			// case _DLL_TYPE_S64, goto store_s64
					jz		store_s64
					cmp		eax, _DLL_TYPE_U64			// case _DLL_TYPE_U64, goto store_u64
					jz		store_u64

					// If we get here, it has to be _DLL_TYPE_VP
					jmp		store_vp					// default, goto push_s16

store_s16:
					movsx	eax,ax
					mov		dword ptr [edi],eax
					jmp		dll_dispatch_asm_code_finished

store_u16:
					movzx	eax,ax
					mov		dword ptr [edi],eax
					jmp		dll_dispatch_asm_code_finished

store_s32:
store_u32:
store_f32:
store_vp:
					mov		dword ptr [edi],eax
					jmp		dll_dispatch_asm_code_finished

store_f64:
store_s64:
store_u64:
					mov		dword ptr [edi],eax
					mov		dword ptr [edi+4],edx
					jmp		dll_dispatch_asm_code_finished

store_nothing:
					// Nothing needs stored (just a placeholder for a jmp target)

dll_dispatch_asm_code_finished:
					// When we get here, the asm part is completed
			}


		//////////
		// Populate the return value into the variable
		//////
			switch (dfunc->rp.type)
			{
				case _DLL_TYPE_S16:
				case _DLL_TYPE_S32:
					iVariable_setVarType(thisCode, rpar->rp[0], _VAR_TYPE_S32);
					*rpar->rp[0]->value.data_s32 = values[0]._s32;
					break;

				case _DLL_TYPE_U16:
				case _DLL_TYPE_U32:
					iVariable_setVarType(thisCode, rpar->rp[0], _VAR_TYPE_U32);
					*rpar->rp[0]->value.data_u32 = values[0]._u32;
					break;

				case _DLL_TYPE_F32:
					iVariable_setVarType(thisCode, rpar->rp[0], _VAR_TYPE_F32);
					*rpar->rp[0]->value.data_f32 = values[0]._f32;
					break;

				case _DLL_TYPE_F64:
					iVariable_setVarType(thisCode, rpar->rp[0], _VAR_TYPE_F64);
					*rpar->rp[0]->value.data_f64 = values[0]._f64;
					break;

				case _DLL_TYPE_S64:
					iVariable_setVarType(thisCode, rpar->rp[0], _VAR_TYPE_S64);
					*rpar->rp[0]->value.data_s64 = values[0]._s64;
					break;

				case _DLL_TYPE_U64:
					iVariable_setVarType(thisCode, rpar->rp[0], _VAR_TYPE_U64);
					*rpar->rp[0]->value.data_u64 = values[0]._u64;
					break;

				case _DLL_TYPE_STRING:
					iVariable_setVarType(thisCode, rpar->rp[0], _VAR_TYPE_CHARACTER);
					iDatum_duplicate(&rpar->rp[0]->value, values[0]._s8p, strlen(values[0]._s8p));
					break;
			}


		//////////
		// Fixup any post-process variables
		//////
			for (lnI = 0; lnI < rpar->ipCount; lnI++)
			{
				// Does this one need post processing?
				if ((types[lnI] & _types_byRef_postProcess) != 0)
				{

					//////////
					// The value which was used went through values[lnI].*, and
					// now it needs to be copied / converted back to its source
					//////
						switch (dfunc->ip[lnI].type)
						{
							case _DLL_TYPE_S16:
								iVariable_set_s32_toExistingType(thisCode, &rpar->ei, rpar->ip[lnI], (s32)values[lnI]._s16);
								break;
							case _DLL_TYPE_U16:
								iVariable_set_u32_toExistingType(thisCode, &rpar->ei, rpar->ip[lnI], (u32)values[lnI]._u16);
								break;
							case _DLL_TYPE_S32:
								iVariable_set_s32_toExistingType(thisCode, &rpar->ei, rpar->ip[lnI], values[lnI]._s32);
								break;
							case _DLL_TYPE_U32:
								iVariable_set_u32_toExistingType(thisCode, &rpar->ei, rpar->ip[lnI], values[lnI]._u32);
								break;
							case _DLL_TYPE_F32:
								iVariable_set_f32_toExistingType(thisCode, &rpar->ei, rpar->ip[lnI], values[lnI]._f32);
								break;
							case _DLL_TYPE_F64:
								iVariable_set_f64_toExistingType(thisCode, &rpar->ei, rpar->ip[lnI], values[lnI]._f64);
								break;
							case _DLL_TYPE_S64:
								iVariable_set_s64_toExistingType(thisCode, &rpar->ei, rpar->ip[lnI], values[lnI]._s64);
								break;
							case _DLL_TYPE_U64:
								iVariable_set_u64_toExistingType(thisCode, &rpar->ei, rpar->ip[lnI], values[lnI]._u64);
								break;

							case _DLL_TYPE_STRING:
								// Delete the existing string, and replace with the new version
								iDatum_delete(&rpar->ip[lnI]->value, false);
								rpar->ip[lnI]->value.data_vp	= values[lnI]._datum.data_vp;
								rpar->ip[lnI]->value.length		= values[lnI]._datum.length;
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
	bool iDllFunc_add(SThisCode* thisCode, SFunctionParams* rpar, SDllFuncParam* rp, SDllFuncParam ip[], s32 tnIpCount, SComp* compFunctionName, SComp* compAliasName, SComp* compDllName, SThisCode* onAccess, SThisCode* onAssign)
	{
		s32			lnFuncNameLength;
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
