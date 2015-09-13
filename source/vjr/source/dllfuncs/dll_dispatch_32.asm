//////////
//
// /libsf/source/vjr/commands/dllfuncs/dll_dispatch_32.asm
// Note:  This is an #include file from dllfuncs.cpp.
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
//     Aug.27.2015
//////
// Change log:
//     Aug.27.2015 - Initial creation
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
// Note:  This code is inline to the iiDllFunc_dispatch_lowLevel() function.
// Note:  See dllfuncs.cpp, and search for the #include "dll_dispatch_32.asm" source code line.
//////////
#if !defined(__solaris__)
_asm {
	//////////
	//
	// Inline assembly to push parameters onto the stack:
	//
	//		eax -- general purpose
	//		ebx	-- parameter size in bytes, and function address
	//		ecx	-- count
	//		edx	-- address of types
	//		esi	-- address of pointers
	//		edi	-- address of values, and address of return value
	//////
		//
		// The code below simulates a for loop:
		//
		//		for (initializePhase; testPhase; incrementPhase)
		//
		//////////




//	initializePhase:
			mov		gnDll_saveParamBytes,0			// Param bytes pushed on stack initially set to 0
			mov		ecx,gnDll_paramCount			// lnParamCount	= dfunc->ipCount
			mov		edx,gnDll_typesBaseRtoL			// typePtr		= &gnDll_typesBase		[lnParamCount - 1]
			mov		esi,gnDll_pointersBaseRtoL		// pointersPtr	= &gnDll_pointersBase	[lnParamCount - 1]
			mov		edi,gnDll_valuesBaseRtoL		// valuesPtr	= &gnDll_valuesBase		[lnParamCount - 1]
			jmp		testPhase




	incrementPhase:
			dec		ecx								// lnParamCount--
			sub		edx,gnDll_sizeofTypes			// --typePtr
			sub		esi,gnDll_sizeofPointers		// --pointersPtr
			sub		edi,gnDll_sizeofValues			// --valuesPtr




	testPhase:
			cmp		ecx,0							// lnParamCount > 0
			jz		physicallyDispatch

			// switch (types[lnI])
			mov		eax,dword ptr [edx]
			cmp		eax,_DLL_TYPE_S16				// case _DLL_TYPE_S16, goto push_s16
			jz		push_s16
			cmp		eax, _DLL_TYPE_U16				// case _DLL_TYPE_U16, goto push_u16
			jz		push_u16
			cmp		eax, _DLL_TYPE_S32				// case _DLL_TYPE_S32, goto push_s32
			jz		push_s32
			cmp		eax, _DLL_TYPE_U32				// case _DLL_TYPE_S64, goto push_s64
			jz		push_u32
			cmp		eax, _DLL_TYPE_F32				// case _DLL_TYPE_F32, goto push_f32
			jz		push_f32
			cmp		eax, _DLL_TYPE_F64				// case _DLL_TYPE_F64, goto push_f64
			jz		push_f64
			cmp		eax, _DLL_TYPE_S64				// case _DLL_TYPE_S64, goto push_s64
			jz		push_s64
			cmp		eax, _DLL_TYPE_U64				// case _DLL_TYPE_U64, goto push_u64
			jz		push_u64

			// If we get here, it has to be _DLL_TYPE_VP
			jmp		push_vp							// default, goto push_s16

	push_s16:
			movsx	eax,word ptr [edi]
			push	eax
			add		gnDll_saveParamBytes,4
			jmp		incrementPhase

	push_u16:
			movzx	eax,word ptr [edi]
			push	eax
			add		gnDll_saveParamBytes,4
			jmp		incrementPhase

	push_s32:
	push_u32:
	push_f32:
	push_vp:
			mov		eax,dword ptr [edi]
			push	eax
			add		gnDll_saveParamBytes,4
			jmp		incrementPhase

	push_f64:
	push_s64:
	push_u64:
			mov		eax,dword ptr [edi]
			push	eax
			mov		eax,dword ptr [edi+4]
			push	eax
			add		gnDll_saveParamBytes,8
			jmp		incrementPhase




	physicallyDispatch:
			call	gnDll_funcAddress				// Dispatch into the DLL function9
//			add		esp,gnDll_saveParamBytes		// Remove pushed parameters from the stack

			// Store return value if any
			mov		edi,gnDll_returnValuesBase

			// switch (types[lnI])
			mov		ecx,gnDll_returnType
			cmp		ecx,_DLL_TYPE_VOID
			jz		store_nothing
			cmp		ecx,_DLL_TYPE_S16				// case _DLL_TYPE_S16, goto store_s16
			jz		store_s16
			cmp		ecx, _DLL_TYPE_U16				// case _DLL_TYPE_U16, goto store_u16
			jz		store_u16
			cmp		ecx, _DLL_TYPE_S32				// case _DLL_TYPE_S32, goto store_s32
			jz		store_s32
			cmp		ecx, _DLL_TYPE_U32				// case _DLL_TYPE_S64, goto store_s64
			jz		store_u32
			cmp		ecx, _DLL_TYPE_F32				// case _DLL_TYPE_F32, goto store_f32
			jz		store_f32
			cmp		ecx, _DLL_TYPE_F64				// case _DLL_TYPE_F64, goto store_f64
			jz		store_f64
			cmp		ecx, _DLL_TYPE_S64				// case _DLL_TYPE_S64, goto store_s64
			jz		store_s64
			cmp		ecx, _DLL_TYPE_U64				// case _DLL_TYPE_U64, goto store_u64
			jz		store_u64

			// If we get here, it has to be _DLL_TYPE_VP
			jmp		store_vp						// default, goto push_s16

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
	store_vp:
			mov		dword ptr [edi],eax
			jmp		dll_dispatch_asm_code_finished

	store_s64:
	store_u64:
			mov		dword ptr [edi],eax
			mov		dword ptr [edi+4],edx
			jmp		dll_dispatch_asm_code_finished

	store_f32:
			fstp	dword ptr [edi]
			jmp		dll_dispatch_asm_code_finished

	store_f64:
			fstp	qword ptr [edi]
			jmp		dll_dispatch_asm_code_finished

	
	store_nothing:									// Nothing needs stored (just a placeholder for a jmp target)
	dll_dispatch_asm_code_finished:
			// When we get here, the asm part is completed

}
#endif
