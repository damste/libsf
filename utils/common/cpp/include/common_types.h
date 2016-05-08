//////////
//
// /libsf/utils/common/cpp/common_types.h
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
// Copyright (c) 2014-2015 by Rick C. Hodgin
//////
// Last update:
//     Nov.13.2014
//////
// Change log:
//     Nov.13.2014 - Initial creation
//////
//
// This software is released as Liberty Software under a Repeat License, as governed
// by the Public Benefit License v1.0 or later (PBL).
//
// You are free to use, copy, modify and share this software.  However, it can only
// be released under the PBL version indicated, and every project must include a copy
// of the pbl.txt document for its version as is at http://www.libsf.org/licenses/.
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


// Unsigned
#ifdef __GNUC__
	// gcc
	// Used for pointer sizes that mate up with pointers, but are actually integers
	#ifndef __amd64
		#define uptr uint32_t
		#define sptr int32_t
	#else
		#define uptr uint64_t
		#define sptr int64_t
	#endif
	#define u64 uint64_t
	#define u32 uint32_t
	#define u16 uint16_t
	#define u8 unsigned char

	#define s64 int64_t
	#define s32 int32_t
	#define s16 int16_t
	#define s8 char

	// Breakpoints
	#define debug_break asm("int 3");
	#define debug_nop asm("nop");

#elif defined(__solaris__)
	// solaris compiler
	// Used for pointer sizes that mate up with pointers, but are actually integers
	#ifdef __i386
		#define uptr uint32_t
		#define sptr int32_t
	#else
		#define uptr uint64_t
		#define sptr int64_t
	#endif
	#define u64 uint64_t
	#define u32 uint32_t
	#define u16 uint16_t
	#define u8 unsigned char

	#define s64 int64_t
	#define s32 int32_t
	#define s16 int16_t
	#define s8 char

	// Breakpoints
	#define debug_break asm("int 3");
	#define debug_nop asm("nop");

#else
	// Used for pointer sizes that mate up with pointers, but are actually integers
	#if !defined(__64_BIT_COMPILER__)
		// 32-bit compiler
		#define uptr unsigned int
		#define sptr int
	#else
		// 64-bit compiler
		#define uptr unsigned __int64
		#define sptr __int64
	#endif
	#define u64 unsigned __int64
	#define u32 unsigned int
	#define u16 unsigned short
	#define u8 unsigned char

	// Signed
	#define s64 __int64
	#define s32 int
	#define s16 short
	#define s8 char

	// Breakpoints
	#define debug_break _asm int 3;
	#define debug_nop _asm nop;
#endif

#if !defined(size_t)
	#define size_t sptr
#endif

// Floating point
#define f32 float
#define f64 double

// Constant signed
#define cs8 const s8
#define cs16 const s16
#define cs32 const s32
#define cs64 const s64

// Constant unsigned
#define cu8 const u8
#define cu16 const u16
#define cu32 const u32
#define cu64 const u64

// Constant floating point
#define cf32 const f32
#define cf64 const f64

// Constant pointers
#define cvp const void*
#define cs8p cs8*
#define cs16p cs16*
#define cs32p cs32*
#define cs64p cs64*
#define cu8p cu8*
#define cu16p cu16*
#define cu32p cu32*
#define cu64p cu64*

// Constants for iAccess codes
cu32	_8BIT				= 1 << 0;
cu32	_16BIT				= 1 << 1;
cu32	_32BIT				= 1 << 2;
cu32	_64BIT				= 1 << 3;
cu32	_POINTER			= 1 << 27;
cu32	_POINTER_POINTER	= 1 << 28;
cu32	_FLOATING_POINT		= 1 << 29;
cu32	_UNSIGNED			= 1 << 30;
cu32	_CONSTANT			= 1 << 31;

// Base types
cu32	_S8					= _8BIT;
cu32	_U8					= _8BIT | _UNSIGNED;
cu32	_S16				= _16BIT;
cu32	_U16				= _16BIT | _UNSIGNED;
cu32	_S32				= _32BIT;
cu32	_U32				= _32BIT | _UNSIGNED;
cu32	_S64				= _64BIT;
cu32	_U64				= _64BIT | _UNSIGNED;
cu32	_F32				= _32BIT | _FLOATING_POINT;
cu32	_F64				= _64BIT | _FLOATING_POINT;

// Pointers
cu32	_S8P				= _8BIT | _POINTER;
cu32	_U8P				= _8BIT | _POINTER | _UNSIGNED;
cu32	_S16P				= _16BIT | _POINTER;
cu32	_U16P				= _16BIT | _POINTER | _UNSIGNED;
cu32	_S32P				= _32BIT | _POINTER;
cu32	_U32P				= _32BIT | _POINTER | _UNSIGNED;
cu32	_S64P				= _64BIT | _POINTER;
cu32	_U64P				= _64BIT | _POINTER | _UNSIGNED;
cu32	_F32P				= _32BIT | _POINTER | _FLOATING_POINT;
cu32	_F64P				= _64BIT | _POINTER | _FLOATING_POINT;

// Pointer to pointers
cu32	_S8PP				= _8BIT | _POINTER_POINTER;
cu32	_U8PP				= _8BIT | _POINTER_POINTER | _UNSIGNED;
cu32	_S16PP				= _16BIT | _POINTER_POINTER;
cu32	_U16PP				= _16BIT | _POINTER_POINTER | _UNSIGNED;
cu32	_S32PP				= _32BIT | _POINTER_POINTER;
cu32	_U32PP				= _32BIT | _POINTER_POINTER | _UNSIGNED;
cu32	_S64PP				= _64BIT | _POINTER_POINTER;
cu32	_U64PP				= _64BIT | _POINTER_POINTER | _UNSIGNED;
cu32	_F32PP				= _32BIT | _POINTER_POINTER | _FLOATING_POINT;
cu32	_F64PP				= _64BIT | _POINTER_POINTER | _FLOATING_POINT;

// Standard forms
#define between(value, lo, hi)		(value >= lo && value <= hi)
#define _union(x, y, z)				union { x z; y _ ## z; };

// Usage:  abc = newAlloc(SAbc, gsAbcRoot);
#define newAlloc(str, var)			(str*)iLl_appendNew__llAtEnd((SLL**)&var, sizeof(str))

// Logging
#ifndef logfunc
	#define logfunc(x)
#endif


//////////
// Color macros
//////
	#define rgba(r,g,b,a)				(u32)(((a & 0xff) << 24) + \
											((r & 0xff) << 16) + \
											((g & 0xff) <<  8) + \
											((b & 0xff)))

	#define rgb(r,g,b)					(u32)((0xff       << 24) + \
											((r & 0xff) << 16) + \
											((g & 0xff) <<  8) + \
											((b & 0xff)))

	#define bgra(b,g,r,a)				(u32)(((a & 0xff) << 24) + \
											((b & 0xff) << 16) + \
											((g & 0xff) <<  8) + \
											((r & 0xff)))

	#define bgr(b,g,r)					(u32)((0xff       << 24) + \
											((b & 0xff) << 16) + \
											((g & 0xff) <<  8) + \
											((r & 0xff)))

	#define alp(rgbaColor)					(u8)((rgbaColor >> 24) & 0xff)
	#define red(rgbaColor)					(u8)((rgbaColor >> 16) & 0xff)
	#define grn(rgbaColor)					(u8)((rgbaColor >> 8)  & 0xff)
	#define blu(rgbaColor)					(u8)( rgbaColor        & 0xff)


// Shortcuts for non-NULL data arrays by arbitrary string
#define data_s8(a,b)	s8	a[sizeof(b) - 1]	= { (s8*)b }
#define data_cs8(a,b)	cs8	a[sizeof(b) - 1]	= { (cs8*)b }
#define data_u8(a,b)	u8	a[sizeof(b) - 1]	= { (u8*)b }
#define data_cu8(a,b)	cu8	a[sizeof(b) - 1]	= { (cu8*)b }
// Usages:	s8_data(name, "xyz");		// Creates s8 name[3] = "xyz";
//			cs8_data(name, "xyz");		// Creates cs8 name[3] = "xyz";
//			u8_data(name, "xyz");		// Creates u8 name[3] = "xyz";
//			cu8_data(name, "xyz");		// Creates cu8 name[3] = "xyz";

#ifndef _UPTR_ERROR
	#if defined(__64_BIT_COMPILER__)
		#define _UPTR_ERROR 0xffffffffffffffff
	#else
		#define _UPTR_ERROR 0xffffffff
	#endif
#endif

#ifndef null0
	// For a null that is not considered a pointer
	#define null0 0
#endif

#ifndef null
	// For a null that is lower-case ... as it should be. :-)
	#define null NULL
#endif

struct SBgr
{
	union {
		u8	blu;
		u8	blu_u8;
		s8	blu_s8;
	};

	union {
		u8	grn;
		u8	grn_u8;
		s8	grn_s8;
	};

	union {
		u8	red;
		u8	red_u8;
		s8	red_s8;
	};
};

// Note:  SBgra moved to vjr_stucts00.h due to lin2win dependency

struct SBgraf
{
	f32		blu;				// 24-bit RGB values in bitmap files are physically stored as BGR
	f32		grn;
	f32		red;
	f32		alp;				// For 32-bit bitmaps
	f32		area;				// Holds area
};

// Note:  This structure was moved here because of a lin2win dependency when compiling for Linux
struct SBgra
{
	union {
		u32		color;
		struct {
			union {
				u8	blu;
				u8	blu_u8;
				s8	blu_s8;
			};
			union {
				u8	grn;
				u8	grn_u8;
				s8	grn_s8;
			};
			union {
				u8	red;
				u8	red_u8;
				s8	red_s8;
			};
			union {
				u8	alp;
				u8	alp_u8;
				s8	alp_s8;
			};
        };
    };
};

struct SBgr_af64
{
	u8	blu;
	u8	grn;
	u8	red;
	f64	falp;
};

struct SXy_f64
{
	f64	x;
	f64	y;
};

struct SXy_s32
{
	s32	xi;
	s32	yi;
};
