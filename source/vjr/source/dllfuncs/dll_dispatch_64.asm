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
EXTRN gnDll_typesBase:QWORD				;; void*
EXTRN gnDll_pointersBase:QWORD			;; void*
EXTRN gnDll_valuesBase:QWORD			;; void*
EXTRN gnDll_returnValuesBase:QWORD		;; void*
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

;; Note:  All of the code below is incorrect.  It was written before I (Rick C. Hodgin) had a proper understanding of the Win64 calling protocols.
;; Note:  It will be re-written shortly (Lord willing, and life permitting).

		;;;;;;;;;;
		;;
		;; Inline assembly to push parameters onto the stack:
		;;
		;;		r6/rsi	-- Integer number
		;;		r7/rdi	-- Floating point number
		;;		r10		-- general purpose
		;;		r11		-- parameter size in bytes, and function address
		;;		r12		-- count
		;;		r13		-- address of types
		;;		r14		-- address of pointers
		;;		r15		-- address of values, and address of return value
		;;;;;;
			;;
			;; The code below simulates a for loop:
			;;
			;;		for (initializePart; testPart; incrementPart)
			;;
			;;;;;;;;;;

			;; initializePart
			xor		rsi,rsi						;; Integer number
			xor		rdi,rdi						;; Floating pointer number
			movsxd	r12,gnDll_paramCount		;; lnParamCount		= dfunc->ipCount
			mov		r13,gnDll_typesBase			;; typePtr			= &gnDll_types		[lnParamCount - 1]
			mov		r14,gnDll_pointersBase		;; pointersPtr		= &gnDll_pointers	[lnParamCount - 1]
			mov		r15,gnDll_valuesBase		;; valuesPtr		= &gnDll_values		[lnParamCount - 1]
			jmp		push_next_param

prepare_for_next_param:
			;; incrementPart
			dec		r12							;; lnParamCount--
			movsxd	r11,gnDll_sizeofTypes
			sub		r13,r11						;; --typePtr
			movsxd	r11,gnDll_sizeofPointers
			sub		r14,r11						;; --pointersPtr
			movsxd	r11,gnDll_sizeofValues
			sub		r15,r11						;; --valuesPtr

push_next_param:
			;; testPart
			cmp		r12,0						;; lnParamCount > 0
			jz		finished_with_stack_ops

			;; switch (types[lnI])
			movsxd	r10,dword ptr [r13]
			mov		r11,_DLL_TYPE_S16
			cmp		r10,r11						;; case _DLL_TYPE_S16, goto push_s16
			jz		push_s16
			mov		r11,_DLL_TYPE_U16
			cmp		r10,r11						;; case _DLL_TYPE_U16, goto push_u16
			jz		push_u16
			mov		r11,_DLL_TYPE_S32
			cmp		r10,r11						;; case _DLL_TYPE_S32, goto push_s32
			jz		push_s32
			mov		r11,_DLL_TYPE_U32
			cmp		r10,r11						;; case _DLL_TYPE_S64, goto push_s64
			jz		push_u32
			mov		r11,_DLL_TYPE_F32
			cmp		r10,r11						;; case _DLL_TYPE_F32, goto push_f32
			jz		push_f32
			mov		r11,_DLL_TYPE_F64
			cmp		r10,r11						;; case _DLL_TYPE_F64, goto push_f64
			jz		push_f64
			mov		r11,_DLL_TYPE_S64
			cmp		r10,r11						;; case _DLL_TYPE_S64, goto push_s64
			jz		push_s64
			mov		r11,_DLL_TYPE_U64
			cmp		r10,r11						;; case _DLL_TYPE_U64, goto push_u64
			jz		push_u64

			;; If we get here, it has to be _DLL_TYPE_VP
			jmp		push_vp						;; default, goto push_s16

push_s16:
			xor		r10,r10
			movsxd	r10,dword ptr [r15]			;; Sign-extend 16-bit to 64-bit
			jmp		push_integer_common

push_u16:
			xor		r10,r10
			movsxd	r10,dword ptr [r15]			;; Zero-extend 16-bit to 64-bit
			jmp		push_integer_common

push_s32:
			movsxd	r10,dword ptr [r15]			;; Sign-extend 32-bit to 64-bit
			jmp		push_integer_common

push_u32:
			movsxd	r10,dword ptr [r15]			;; Zero-extend 32-bit to 64-bit
			jmp		push_integer_common

push_vp:	;; Generic pointer
push_s64:	;; Signed 64-bit
push_u64:	;; Unsigned 64-bit
			mov		r10,qword ptr [r15]
push_integer_common:
			cmp		rsi,0						;; First integer
			jz		push_into_rcx

			cmp		rsi,1						;; Second integer
			jz		push_into_rdx

			cmp		rsi,2						;; Third integer
			jz		push_into_r8

			cmp		rsi,3						;; Fourth integer
			jz		push_into_r9
			;; If we get here, we're beyond the fourth integer, so the rest go on the stack

push_integer_onto_stack:
			push	r10							;; Push onto the stack
			inc		rsi							;; Increment the counter
			add		gnDll_saveParamBytes,8		;; Increase the bytes on the stack
			jmp		prepare_for_next_param		;; Continue on

push_into_rcx:
			mov		rcx,r10						;; Store into first integer, rcx
			inc		rsi							;; Increase the counter
			jmp		prepare_for_next_param		;; Continue on
push_into_rdx:
			mov		rdx,r10						;; Store into second integer, rdx
			inc		rsi							;; Increase the counter
			jmp		prepare_for_next_param		;; Continue on
push_into_r8:
			mov		r8,r10						;; Store into third integer, r8
			inc		rsi							;; Increase the counter
			jmp		prepare_for_next_param		;; Continue on
push_into_r9:
			mov		r9,r10						;; Store into fourth integer, r9
			inc		rsi							;; Increase the counter
			jmp		prepare_for_next_param		;; Continue on

push_f32:
			cmp		rdi,0						;; First floating point
			jz		push_f32_into_xmm0

			cmp		rdi,1						;; Second floating point
			jz		push_f32_into_xmm1

			cmp		rdi,2						;; Third floating point
			jz		push_f32_into_xmm2

			cmp		rdi,3						;; Fourth floating point
			jz		push_f32_into_xmm3
			;; If we get here, we're beyond the fourth floating point, so the rest go on the stack

push_f32_onto_stack:
			xor		rax,rax
			mov		eax,dword ptr [r15]			;; Load 32-bit floating
			push	rax							;; Push onto the stack
			inc		rdi							;; Increase the counter
			add		gnDll_saveParamBytes,8		;; Increase the bytes on the stack
			jmp		prepare_for_next_param		;; Continue on

push_f32_into_xmm0:
			movss	xmm0,real4 ptr [r15]		;; Load 32-bit floating point into xmm0
			inc		rdi							;; Increase the counter
			jmp		prepare_for_next_param		;; Continue on

push_f32_into_xmm1:
			movss	xmm1,real4 ptr [r15]		;; Load 32-bit floating point into xmm1
			inc		rdi							;; Increase the counter
			jmp		prepare_for_next_param		;; Continue on

push_f32_into_xmm2:
			movss	xmm2,real4 ptr [r15]		;; Load 32-bit floating point into xmm2
			inc		rdi							;; Increase the counter
			jmp		prepare_for_next_param		;; Continue on

push_f32_into_xmm3:
			movss	xmm3,real4 ptr [r15]		;; Load 32-bit floating point into xmm3
			inc		rdi							;; Increase the counter
			jmp		prepare_for_next_param		;; Continue on

push_f64:
			cmp		rdi,0						;; First floating point
			jz		push_f64_into_xmm0

			cmp		rdi,1						;; Second floating point
			jz		push_f64_into_xmm1

			cmp		rdi,2						;; Third floating point
			jz		push_f64_into_xmm2

			cmp		rdi,3						;; Fourth floating point
			jz		push_f64_into_xmm3
			;; If we get here, we're beyond the fourth floating point, so the rest go on the stack

push_f64_onto_stack:
			mov		r10,qword ptr [r15]			;; Load 64-bit floating point
			push	r10							;; Push onto the stack
			inc		rdi							;; Increase the counter
			add		gnDll_saveParamBytes,8		;; Increase the bytes on the stack
			jmp		prepare_for_next_param		;; Continue on

push_f64_into_xmm0:
			movsd	xmm0,real8 ptr [r15]		;; Load 64-bit floating point into xmm0
			inc		rdi							;; Increase the counter
			jmp		prepare_for_next_param		;; Continue on

push_f64_into_xmm1:
			movsd	xmm1,real8 ptr [r15]		;; Load 64-bit floating point into xmm1
			inc		rdi							;; Increase the counter
			jmp		prepare_for_next_param		;; Continue on

push_f64_into_xmm2:
			movsd	xmm2,real8 ptr [r15]		;; Load 64-bit floating point into xmm2
			inc		rdi							;; Increase the counter
			jmp		prepare_for_next_param		;; Continue on

push_f64_into_xmm3:
			movsd	xmm3,real8 ptr [r15]		;; Load 64-bit floating point into xmm3
			inc		rdi							;; Increase the counter
			jmp		prepare_for_next_param		;; Continue on

finished_with_stack_ops:
			call	gnDll_funcAddress			;; Dispatch into the DLL function9
;;			add		esp,gnDll_saveParamBytes	;; Remove pushed parameters from the stack

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
			jmp		store_vp					;; default, goto push_s16

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

dll_dispatch_asm_code_finished:
			;; When we get here, the asm part is completed

			ret
idll_dispatch_64_asm	ENDP

END
