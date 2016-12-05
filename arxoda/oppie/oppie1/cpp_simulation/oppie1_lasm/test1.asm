//////////
//
// /libsf/arxoda/oppie/oppie1/cpp_simulation/oppie1_lasm/test1.asm
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
// Copyright (c) 2014 by Rick C. Hodgin
//////
// Last update:
//     Nov.29.2014
//////
// Change log:
//     Nov.29.2014 - Initial creation
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
// START test1.asm
// C:\LIBSF\ARXODA\OPPIE\OPPIE1\CPP_SIMULATION\OPPIE1_LASM\> lasm1 test1.asm
// LibSF Oppie-1 Assembler v0.02
// Assembling test1.asm
// Wrote 2048 bytes to test1.img
//
//////

	.org 512
// Add
value1_1:
	db 10
value1_2:
	db 20

// Adc
value2_1:
	db 140
value2_2:
	db 150

// Sub
value3_1:
	db 70
value3_2:
	db 15

// Sbb
value4_1:
	db 20
value4_2:
	db 150

// Cmp
value5_1:
	db 20
value5_2:
	db 150

// Constants
zero:
	db 0
one:
	db 1
minus_one:
	db 255

	.org 544
result1:
	db 0
result2:
	db 0
result3:
	db 0
result4:
	db 0
result5:
	db 0


	.org 0
// Add
	mov		r1,value1_1
	mov		r2,value1_2
	add		r1,r2
	mov		result1,r1

// Adc
	mov		r1,value2_1
	mov		r2,value2_2
	mov		r3,zero
	add		r1,r2
	adc		r3,r3
	mov		result2,r3

// Sub
	mov		r1,value3_1
	mov		r2,value3_2
	sub		r1,r2
	mov		result3,r1

// Sbb
	mov		r1,value4_1
	mov		r2,value4_2
	mov		r3,zero
	sub		r1,r2
	sbb		r3,r3
	mov		result4,r3

// Cmp
	mov		r1,value5_1
	mov		r2,value5_2
	cmp		r1,r2
	jz		equal_to
	jc		greater_than
	mov		r4,minus_one
	mov		result5,r4
	jmp		done

equal_to:
	mov		r4,zero
	mov		result5,r4
	jmp		done

greater_than:
	mov		r4,one
	mov		result5,r4

done:
	jmp		done
// END test1.asm
