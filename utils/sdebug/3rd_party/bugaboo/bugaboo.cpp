//////////
//
// /libsf/utils/sdebug/3rd_party/bugaboo/bugaboo.cpp
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
// Version 0.01
// Copyright (c) 2016 by Rick C. Hodgin
//////
// Last update:
//     May.22.2016
//////
// Change log:
//     May.22.2016 - Initial creation
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
//////
//
// SDebug is short for "Sanitizing Debugger".  It was designed to help find memory bugs.
//
// SDebug allows explicit memory ranges to be checked, along with explicit references
// to pointers being tracked.  Once the range(s) is(are) set, it allows runtime modes:
//
//		1 - Single-step through code looking for any access outside of tracked memory.
//
//		2 - Specify a function to examine, within which it looks at all memory references
//			to see if any reference is outside the tracked range.
//
//		3 - Specify a parameter or local pointer to track, which then only explicitly looks
//			at things which reference that pointer, ignoring all other memory references.
//
// Once set on a pointer or function, SDebug disassembles the function body and determines
// where each memory reference is made, and where each pointer is used.  It then sets
// breakpoints on all of those instructions.  When those breakpoints are hit, it internally
// decodes the instruction on-the-fly to determine if references are being made inside or
// outside of tracked memory ranges.
//
// Memory blocks are tracked in the general form:
//
//		preBufferCount		-- Number of bytes to examine before buffer (typically up to 64)
//		bufferStart			-- Where the buffer starts
//		bufferLength		-- Length of normal data within the buffer
//		postBufferCount		-- Number of bytes to examine after the buffer (typically up to 64)
//
//////




#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#include "/libsf/utils/common/cpp/include/common_types.h"
#include "/libsf/utils/common/cpp/include/sdebug/sdebug.h"

int main(int c, char* argv[])
{
	int		a, b;
	s8*		buffer;


	// Allocate a buffer that's one byte too small (does not support the trailing NULL from sprintf)
	// 123456789012345
	// a=1234, b=1234\n
	buffer = (s8*)malloc(15);

	// Read a couple values
	scanf("%d%d", &a, &b);

	// Overun the buffer
	sprintf(buffer, "a=%04d, b=%04d\n", a, b);
	printf(buffer);

    return 0;
}
