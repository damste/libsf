//////////
//
// /libsf/exodus/tools/debi/debi_const.h
//
//////
// Version 0.80
// Copyright (c) 2014-2015 by Rick C. Hodgin
//////
// Last update:
//     Sep.12.2015
//////
// Change log:
//     Sep.12.2015 - Refactoring for Exodus OS tool support
//     Feb.13.2014 - Initial creation
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
//     http://www.visual-freepro.org/wiki/index.php/Repeat_License
//
// Thank you.  And may The Lord bless you richly as you lift up your life, your
// talents, your gifts, your praise, unto Him.  In Jesus' name I pray.  Amen.
//
//




// const.h
typedef unsigned char	u8;
typedef unsigned short	u16;
typedef unsigned long	u32;
typedef char			s8;
typedef short			s16;
typedef long			s32;
typedef float			f32;
typedef double			f64;
typedef char			bool;
#define true 1
#define false 0

u8 _null_string[] = "";

// This function is called to reach the ones below, it is constantly updated
typedef void(*DISASM_FUNC)(u8* data, struct _SDisasmData* dd);
