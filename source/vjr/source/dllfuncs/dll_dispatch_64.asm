;;;;;;;;;;
;;
;; /libsf/source/vjr/commands/dllfuncs/dll_dispatch_64.asm
;;
;;;;;;
;;    _     _ _     _____ _____
;;   | |   (_) |__ / ____|  ___|
;;   | |   | | '_ \\___ \|  __|
;;   | |___| | |_) |___) | |
;;   |_____|_|_.__/_____/|_|
;;
;;   Liberty Software Foundation
;; and the Village Freedom Project
;;   __     _______     ____
;;   \ \   / /  ___| __|  _ \
;;    \ \ / /| |_ | '__| |_) |
;;     \ V / |  _|| |  |  __/
;;      \_/  |_|  |_|  |_|
;;
;;;;;;
;; Version 0.58
;; Copyright (c) 2015 by Rick C. Hodgin
;;;;;;
;; Last update:
;;     Aug.27.2015
;;;;;;
;; Change log:
;;     Aug.27.2015 - Initial creation
;;;;;;
;;
;; This document is released as Liberty Software under a Repeat License, as governed
;; by the Public Benefit License v1.0 or later (PBL).
;;
;; The PBL is a public domain license with a caveat:  self accountability unto God.
;; You are free to use, copy, modify and share this software for any purpose, however,
;; it is the dr14re of those working on this project that the software remain open.
;; It is our request that you maintain it that way.  This is not a legal request unto
;; our court systems, but rather a personal matter between you and God.  Our talents
;; were received from God, and given to you through this forum.  And it is our wish
;; that those talents reach out to as many as possible in a form allowing them to wield
;; this content for their own betterment, as you are now considering doing.  And whereas
;; we could've forced the issue through something like a copyleft-protected release, the
;; truth is we are all giving an account of our lives unto God continually by the daily
;; choices we make.  And here again is another case where you get to demonstrate your
;; character unto God, and unto your fellow man.
;;
;; Jesus came to this Earth to set the captives free, to save men's eternal souls from
;; the punishment demanded by our sin.  Each one of us is given the opportunity to
;; receive Him in this world and be saved.  Whether we choose to receive Him, and follow
;; Him, and purpose our lives on the goals He has for each of us (all of which are
;; beneficial for all involved), is one way we reveal our character continually.  God
;; sees straight through to the heart, bypassing all of the words, all of the facades.
;; He is our Creator, and He knows who we are truly.
;;
;; Jesus is called "Christ" because He saves men from the eternal flames of Hell, the
;; just punishment of rebellion against God (rebellion against truth) by eternal beings,
;; which each of us are.
;;
;; Do not let His free gift escape you because of some dr14re to shortcut what is right
;; in your life. Instead, do what is right, and do it because He is who He is, and what
;; He has done to save us from such a fate.  Demonstrate to Him, to me, and to all of
;; mankind, and to all of the Heavenly hosts, exactly who you are on the inside.  Receive
;; Jesus Christ into your heart, learn of Him, of how He came here to guide us into that
;; which is of His Kingdom and will be forever hereafter we leave this world.  Do this,
;; and live.
;;
;; Every project released by Liberty Software Foundation will include a copy of the
;; pbl.txt document, which can be found at http:;;www.libsf.org/licenses/.
;;
;; For additional information about this project, or to view the license, see:
;;
;;     http:;;www.libsf.org/
;;     http:;;www.libsf.org/licenses/
;;     http:;;www.visual-freepro.org/vjr/indexmain.html
;;     http:;;www.visual-freepro.org/wiki/index.php/PBL
;;
;; Thank you.  And may The Lord bless you richly as you lift up your life, your
;; talents, your gifts, your praise, unto Him.  In Jesus' name I pray.  Amen.
;;
;;;;;;
;;
;; To add a new function, see the instructions in command_defs.h.
;;
;;

	.CODE

EXTRN gnDll_typeStep:DWORD				;; s32
EXTRN gnDll_pointersStep:DWORD			;; s32
EXTRN gnDll_valuesStep:DWORD			;; s32
EXTRN gnDll_paramCount:DWORD			;; u32
EXTRN gnDll_returnType:DWORD			;; u32
EXTRN gnDll_sizeofTypes:DWORD			;; u32
EXTRN gnDll_sizeofPointers:DWORD		;; u32
EXTRN gnDll_sizeofValues:DWORD			;; u32
EXTRN gnDll_saveParamBytes:DWORD		;; u32
EXTRN gnDll_funcAddress:QWORD			;; void*
EXTRN gnDll_typesBaseRtoL:QWORD			;; void*
EXTRN gnDll_pointersBaseRtoL:QWORD		;; void*
EXTRN gnDll_valuesBaseRtoL:QWORD		;; void*
EXTRN gnDll_returnValuesBase:QWORD		;; void*
EXTRN gnDll_typesBaseLtoR:QWORD			;; void*
EXTRN gnDll_pointersBaseLtoR:QWORD		;; void*
EXTRN gnDll_valuesBaseLtoR:QWORD		;; void*
EXTRN gnDll_types:DWORD					;; u32
EXTRN gnDll_pointers:QWORD				;; void*
EXTRN gnDll_values:QWORD				;; SDllVals

;; Note:  These symbols must mirror the _DLL_TYPE_* symbols in vjr_const.h
;; Note:  I had difficulty getting this assembly file to recognize those constants, so I just duplicated them here.
_DLL_TYPE_VP			EQU 1
_DLL_TYPE_VOID			EQU 2
_DLL_TYPE_S16			EQU 3
_DLL_TYPE_U16			EQU 4
_DLL_TYPE_S32			EQU 5
_DLL_TYPE_U32			EQU 6
_DLL_TYPE_F32			EQU 7
_DLL_TYPE_F64			EQU 8
_DLL_TYPE_S64			EQU 9
_DLL_TYPE_U64			EQU 10
_DLL_TYPE_STRING		EQU 11
_DLL_TYPE_IDISPATCH		EQU 12




;;;;;;;;;;
;;
;; Parameter passing on Win64 is different than Win32:
;;
;;;;;;;;;;
;;
;;		Register				Win64							Extra notes
;;		--------				---------------------------		------------------------
;;		Return value:
;;			rax					int/pointer return value
;;			xmm0				floating point return value
;;		
;;		Input value:
;;			rcx					1st int / pointer 				If variadic and prototypeless functions, xmm0 is replicated here
;;			rdx					2nd int / pointer 				If variadic and prototypeless functions, xmm1 is replicated here
;;			r8					3rd int / pointer 				If variadic and prototypeless functions, xmm2 is replicated here
;;			r9					4th int / pointer 				If variadic and prototypeless functions, xmm3 is replicated here
;;		
;;		 Floating point input:
;;			 xmm0-xmm3			First four fp					First four fp and small structures
;;																Note:  For prototypeless functions, all fp values are pushed as f64, even if they're used internally as f32
;;
;;;;;;;;;;
;;
;; The format specified above for rcx,rdx,r8,r9, and xmm0,xmm1,xmm2,xmm3 is used for the first four
;; input values from left to right.  However, the remaining items are pushed from right to left onto
;; the stack.  And for variadic functions, or functions without prototypes, any values put into xmm0
;; thru xmm3 are also replicated into their corresponding cardinal location in rcx,rdx,r8,r9.
;;
;; In addition, the stack must be 16-byte aligned, and there must be (4 x 8) = 32 byte buffer created
;; by the caller(!!) for the callee to use, even if the callee doesn't require it(!!).
;;
;; Floored.
;; 
;;;;;;;;;;



PUBLIC idll_dispatch_64_asm

idll_dispatch_64_asm	PROC	C
;;;;;;;;;;
;; Note:  This code is inline to the iiDllFunc_dispatch_lowLevel() function.
;; Note:  See dllfuncs.cpp, and search for the #include "dll_dispatch_32.asm" source code line.
;;;;;;;;;;
		;;;;;;;;;;
		;;
		;; Inline assembly to push parameters onto the stack:
		;;
		;;		r6/esi	-- 1=Variadic, 0=Not variadic
		;;		r7/rdi	-- Cardinal parameter number
		;;		r10		-- general purpose
		;;		r11		-- parameter size in bytes, and function address
		;;		r12		-- count
		;;		r13		-- address of types
		;;		r14		-- address of pointers
		;;		r15		-- address of values, and address of return value
		;;;;;;
			;;
			;; The code below simulates this two-step for loop sequence:
			;;
			;;		//////////
			;;		// Phase 1
			;;		//////
			;;			// Handle first four parameters, integer, floating point, or small structs
			;;			// Processed left to right
			;;			for (initializePhase1; testPhase1; incrementPhase1)
			;;			{
			;;				// Load only integer, floating point, or small structs
			;;				// Mark each of those completed as _DLL_TYPE_VOID (so they are skipped in phase 2)
			;;			}
			;;
			;;
			;;		//////////
			;;		// Phase 2
			;;		//////
			;;			// Load any remaining parameters, one by one
			;;			// Processed right to left
			;;			for (initializePhase2; testPhase2; incrementPhase2)
			;;			{
			;;				// Skip those previously loaded
			;;				if (type != _DLL_TYPE_VOID)
			;;					// Process only non-void
			;;			}
			;;
			;;;;;;;;;;


;;;;;;;;;;
;; Phase 1
;;;;;;
	initializePhase1:
			xor		rsi,rsi
			xor		rdi,rdi							;; Cardinal parameter number (index into rcx,rdx,r8,r9, or xmm0,xmm1,xmm2,xmm3 as parameters are being inserted)
			mov		gnDll_saveParamBytes,0			;; Param bytes pushed on stack initially set to 0
			movsxd	r12,gnDll_paramCount			;; lnParamCount		= dfunc->ipCount
			mov		r13,gnDll_typesBaseLtoR			;; typePtr			= &gnDll_types[0]
			mov		r14,gnDll_pointersBaseLtoR		;; pointersPtr		= &gnDll_pointers[0]
			mov		r15,gnDll_valuesBaseLtoR		;; valuesPtr		= &gnDll_values[0]
			sub		rsp,32							;; Add a 32-byte (4x 8-byte) shadow area on the stack

			;; Begin
			jmp		testPhase1

	incrementPhase1:
			dec		r12								;; lnParamCount--
			movsxd	r11,gnDll_sizeofTypes
			add		r13,r11							;; ++typePtr
			movsxd	r11,gnDll_sizeofPointers
			add		r14,r11							;; ++pointersPtr
			movsxd	r11,gnDll_sizeofValues
			add		r15,r11							;; ++valuesPtr

	testPhase1:
			cmp		r12,0							;; lnParamCount > 0
			jz		initializePhase2
			cmp		rsi,4							;; Cardinal parameter number (all four slots are filled)
			jae		initializePhase2

			;; switch (types[lnI])
			movsxd	r10,dword ptr [r13]
			;; r10 is the switch() value

			;; r11 is reused for each test value
			mov		r11,_DLL_TYPE_S16
			cmp		r10,r11							;; case _DLL_TYPE_S16
			jz		store_s16_phase1

			mov		r11,_DLL_TYPE_U16
			cmp		r10,r11							;; case _DLL_TYPE_U16
			jz		store_u16_phase1

			mov		r11,_DLL_TYPE_S32
			cmp		r10,r11							;; case _DLL_TYPE_S32
			jz		store_s32_phase1

			mov		r11,_DLL_TYPE_U32
			cmp		r10,r11							;; case _DLL_TYPE_S64
			jz		store_u32_phase1

			mov		r11,_DLL_TYPE_F32
			cmp		r10,r11							;; case _DLL_TYPE_F32
			jz		store_f32_phase1

			mov		r11,_DLL_TYPE_F64
			cmp		r10,r11							;; case _DLL_TYPE_F64
			jz		store_f64_phase1

			mov		r11,_DLL_TYPE_S64
			cmp		r10,r11							;; case _DLL_TYPE_S64
			jz		store_s64_phase1

			mov		r11,_DLL_TYPE_U64
			cmp		r10,r11							;; case _DLL_TYPE_U64
			jz		store_u64_phase1
			jmp		store_pointer_phase1

	store_s16_phase1:
			xor		r10,r10
			movsxd	r10,dword ptr [r15]				;; Sign-extend 16-bit to 64-bit
			jmp		store_integer_common_phase1

	store_u16_phase1:
			xor		r10,r10
			movsxd	r10,dword ptr [r15]				;; Zero-extend 16-bit to 64-bit
			jmp		store_integer_common_phase1

	store_s32_phase1:
			movsxd	r10,dword ptr [r15]				;; Sign-extend 32-bit to 64-bit
			jmp		store_integer_common_phase1

	store_u32_phase1:
			movsxd	r10,dword ptr [r15]				;; Zero-extend 32-bit to 64-bit
			jmp		store_integer_common_phase1

	store_s64_phase1:
	store_u64_phase1:
	store_pointer_phase1:
			mov		r10,qword ptr [r15]

	store_integer_common_phase1:
			or		dword ptr [r13],080000000h		;; Indicate this parameter is complete
			cmp		rdi,0							;; First integer
			jz		store_into_rcx

			cmp		rdi,1							;; Second integer
			jz		store_into_rdx

			cmp		rdi,2							;; Third integer
			jz		store_into_r8
			jmp		store_into_r9					;; Fourth integer

	store_into_rcx:
			mov		rcx,r10							;; Store into first integer, rcx
			inc		rdi								;; Increase the counter
			jmp		incrementPhase1					;; Continue on
	store_into_rdx:
			mov		rdx,r10							;; Store into second integer, rdx
			inc		rdi								;; Increase the counter
			jmp		incrementPhase1					;; Continue on
	store_into_r8:
			mov		r8,r10							;; Store into third integer, r8
			inc		rdi								;; Increase the counter
			jmp		incrementPhase1					;; Continue on
	store_into_r9:
			mov		r9,r10							;; Store into fourth integer, r9
			inc		rdi								;; Increase the counter
			jmp		incrementPhase1					;; Continue on

	store_f32_phase1:
			or		dword ptr [r13],080000000h		;; Indicate this parameter is complete
			cmp		rdi,0							;; First floating point
			jz		store_f32_into_xmm0

			cmp		rdi,1							;; Second floating point
			jz		store_f32_into_xmm1

			cmp		rdi,2							;; Third floating point
			jz		store_f32_into_xmm2
			jmp		store_f32_into_xmm3				;; Fourth floating point

	store_f32_into_xmm0:
			movss	xmm0,real4 ptr [r15]			;; Load 32-bit floating point into xmm0
			inc		rdi								;; Increase the counter
			cmp		rsi,0							;; Is it variadic?
			jz		incrementPhase1					;; Nope
			;; Copy to rcx
			movd	rcx,xmm0
			jmp		incrementPhase1					;; Continue on

	store_f32_into_xmm1:
			movss	xmm1,real4 ptr [r15]			;; Load 32-bit floating point into xmm1
			inc		rdi								;; Increase the counter
			cmp		rsi,0							;; Is it variadic?
			jz		incrementPhase1					;; Nope
			;; Copy to rdx
			movd	rdx,xmm1
			jmp		incrementPhase1					;; Continue on

	store_f32_into_xmm2:
			movss	xmm2,real4 ptr [r15]			;; Load 32-bit floating point into xmm2
			inc		rdi								;; Increase the counter
			cmp		rsi,0							;; Is it variadic?
			jz		incrementPhase1					;; Nope
			;; Copy to r8
			movd	r8,xmm2
			jmp		incrementPhase1					;; Continue on

	store_f32_into_xmm3:
			movss	xmm3,real4 ptr [r15]			;; Load 32-bit floating point into xmm3
			inc		rdi								;; Increase the counter
			cmp		rsi,0							;; Is it variadic?
			jz		incrementPhase1					;; Nope
			;; Copy to r9
			movd	r9,xmm3
			jmp		incrementPhase1					;; Continue on

	store_f64_phase1:
			or		dword ptr [r13],080000000h		;; Indicate this parameter is complete
			cmp		rdi,0							;; First floating point
			jz		store_f64_into_xmm0

			cmp		rdi,1							;; Second floating point
			jz		store_f64_into_xmm1

			cmp		rdi,2							;; Third floating point
			jz		store_f64_into_xmm2
			jmp		store_f64_into_xmm3				;; Fourth floating point

	store_f64_into_xmm0:
			movsd	xmm0,real8 ptr [r15]			;; Load 64-bit floating point into xmm0
			inc		rdi								;; Increase the counter
			cmp		rsi,0							;; Is it variadic?
			jz		incrementPhase1					;; Nope
			;; Copy to rcx
			movd	rcx,xmm0
			jmp		incrementPhase1					;; Continue on

	store_f64_into_xmm1:
			movsd	xmm1,real8 ptr [r15]			;; Load 64-bit floating point into xmm1
			inc		rdi								;; Increase the counter
			cmp		rsi,0							;; Is it variadic?
			jz		incrementPhase1					;; Nope
			;; Copy to rdx
			movd	rdx,xmm1
			jmp		incrementPhase1					;; Continue on

	store_f64_into_xmm2:
			movsd	xmm2,real8 ptr [r15]			;; Load 64-bit floating point into xmm2
			inc		rdi								;; Increase the counter
			cmp		rsi,0							;; Is it variadic?
			jz		incrementPhase1					;; Nope
			;; Copy to r8
			movd	r8,xmm2
			jmp		incrementPhase1					;; Continue on

	store_f64_into_xmm3:
			movsd	xmm3,real8 ptr [r15]			;; Load 64-bit floating point into xmm3
			inc		rdi								;; Increase the counter
			cmp		rsi,0							;; Is it variadic?
			jz		incrementPhase1					;; Nope
			;; Copy to r9
			movd	r9,xmm3
			jmp		incrementPhase1					;; Continue on




;;;;;;;;;;
;; Phase 2
;;;;;;
	initializePhase2:
			xor		rdi,rdi							;; Cardinal parameter number (index into rcx,rdx,r8,r9, or xmm0,xmm1,xmm2,xmm3 as parameters are being inserted)
			movsxd	r12,gnDll_paramCount			;; lnParamCount		= dfunc->ipCount
			mov		r13,gnDll_typesBaseRtoL			;; typePtr			= &gnDll_types		[dfunc->ipCount - 1]
			mov		r14,gnDll_pointersBaseRtoL		;; pointersPtr		= &gnDll_pointers	[dfunc->ipCount - 1]
			mov		r15,gnDll_valuesBaseRtoL		;; valuesPtr		= &gnDll_values		[dfunc->ipCount - 1]

			;; Begin
			jmp		testPhase2

	incrementPhase2:
			dec		r12								;; lnParamCount--
			movsxd	r11,gnDll_sizeofTypes
			sub		r13,r11							;; --typePtr
			movsxd	r11,gnDll_sizeofPointers
			sub		r14,r11							;; --pointersPtr
			movsxd	r11,gnDll_sizeofValues
			sub		r15,r11							;; --valuesPtr

	testPhase2:
			cmp		r12,0							;; lnParamCount > 0
			jz		physicallyDispatch				;; If branch, all done

			;; switch (types[lnI])
			movsxd	r10,dword ptr [r13]
			;; r10 is the switch() value
			;; r11 is reused for each test value
			
			;; If we've already added this parameter, skip it
			cmp		r10,080000000h					;; Is the flag raised?
			jb		continue_testing_phase2

			;; Remove the flag (for post-processing) and continue on
			and		dword ptr [r13],07fffffffh
			jmp		incrementPhase2
			
	continue_testing_phase2:
			mov		r11,_DLL_TYPE_S16
			cmp		r10,r11							;; case _DLL_TYPE_S16
			jz		store_s16_phase2

			mov		r11,_DLL_TYPE_U16
			cmp		r10,r11							;; case _DLL_TYPE_U16
			jz		store_u16_phase2

			mov		r11,_DLL_TYPE_S32
			cmp		r10,r11							;; case _DLL_TYPE_S32
			jz		store_s32_phase2

			mov		r11,_DLL_TYPE_U32
			cmp		r10,r11							;; case _DLL_TYPE_S64
			jz		store_u32_phase2

			mov		r11,_DLL_TYPE_F32
			cmp		r10,r11							;; case _DLL_TYPE_F32
			jz		store_f32_phase2

			mov		r11,_DLL_TYPE_F64
			cmp		r10,r11							;; case _DLL_TYPE_F64
			jz		store_f64_phase2

			mov		r11,_DLL_TYPE_S64
			cmp		r10,r11							;; case _DLL_TYPE_S64
			jz		store_s64_phase2

			mov		r11,_DLL_TYPE_U64
			cmp		r10,r11							;; case _DLL_TYPE_U64
			jz		store_u64_phase2
			jmp		store_pointer_phase2

	store_s16_phase2:
			xor		r10,r10
			movsxd	r10,dword ptr [r15]				;; Sign-extend 16-bit to 64-bit
			jmp		store_integer_common_phase2

	store_u16_phase2:
			xor		r10,r10
			movsxd	r10,dword ptr [r15]				;; Zero-extend 16-bit to 64-bit
			jmp		store_integer_common_phase2

	store_s32_phase2:
			movsxd	r10,dword ptr [r15]				;; Sign-extend 32-bit to 64-bit
			jmp		store_integer_common_phase2

	store_u32_phase2:
			movsxd	r10,dword ptr [r15]				;; Zero-extend 32-bit to 64-bit
			jmp		store_integer_common_phase2

	store_s64_phase2:
	store_u64_phase2:
	store_pointer_phase2:
			mov		r10,qword ptr [r15]				;; Grab the 64-bit value

	store_integer_common_phase2:
	store_f64_phase2:
			push	r10								;; Push this param onto the stack
			add		gnDll_saveParamBytes,8			;; Add in the 8 bytes pushed
			jmp		incrementPhase2					;; Continue on

	store_f32_phase2:
			xor		rax,rax
			mov		eax,dword ptr [r15]				;; Grab the 32-bit value
			push	rax								;; Store it as a 64-bit value
			add		gnDll_saveParamBytes,8			;; Add in the 4 bytes pushed
			jmp		incrementPhase2					;; Continue on
		



;;;;;;;;;;
;; Physically dispatch
;;;;;;
	physicallyDispatch:
			call	gnDll_funcAddress			;; Dispatch into the DLL function9
			add		rsp,32						;; Remove shadow area from the stack




;;;;;;;;;;
;; Return parameter
;;;;;;
			;; Store return value if any
			mov		r15,gnDll_returnValuesBase

			;; switch (types[lnI])
			movsxd	r12,gnDll_returnType
			mov		r11,_DLL_TYPE_VOID
			cmp		r12,r11
			jz		store_nothing
			mov		r11,_DLL_TYPE_S16
			cmp		r12,r11						;; case _DLL_TYPE_S16, goto store_s16
			jz		store_s16
			mov		r11,_DLL_TYPE_U16
			cmp		r12,r11						;; case _DLL_TYPE_U16, goto store_u16
			jz		store_u16
			mov		r11,_DLL_TYPE_S32
			cmp		r12,r11						;; case _DLL_TYPE_S32, goto store_s32
			jz		store_s32
			mov		r11,_DLL_TYPE_U32
			cmp		r12,r11						;; case _DLL_TYPE_S64, goto store_s64
			jz		store_u32
			mov		r11,_DLL_TYPE_F32
			cmp		r12,r11						;; case _DLL_TYPE_F32, goto store_f32
			jz		store_f32
			mov		r11,_DLL_TYPE_F64
			cmp		r12,r11						;; case _DLL_TYPE_F64, goto store_f64
			jz		store_f64
			mov		r11,_DLL_TYPE_S64
			cmp		r12,r11						;; case _DLL_TYPE_S64, goto store_s64
			jz		store_s64
			mov		r11,_DLL_TYPE_U64
			cmp		r12,r11						;; case _DLL_TYPE_U64, goto store_u64
			jz		store_u64

			;; If we get here, it has to be _DLL_TYPE_VP
			jmp		store_vp					;; default, goto store_s16

	store_s16:
	store_u16:
			mov		word ptr [r15],ax
			jmp		dll_dispatch_asm_code_finished

	store_s32:
	store_u32:
			mov		dword ptr [r15],eax
			jmp		dll_dispatch_asm_code_finished

	store_vp:
			mov		qword ptr [r15],rax
			jmp		dll_dispatch_asm_code_finished

	store_f32:
			movss 	real4 ptr [r15],xmm0
			jmp		dll_dispatch_asm_code_finished

	store_f64:
			movsd 	real8 ptr [r15],xmm0
			jmp		dll_dispatch_asm_code_finished

	store_s64:
	store_u64:
			mov		qword ptr [r15],rax
			jmp		dll_dispatch_asm_code_finished

	store_nothing:
			;; Nothing needs stored (just a placeholder for a jmp target)


;;;;;;;;;;
;; Finished
;;;;;;
	dll_dispatch_asm_code_finished:
			;; When we get here, the asm part is completed

			ret
idll_dispatch_64_asm	ENDP

END
