//////////
//
// /libsf/utils/common/cpp/scale.h
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
// Version 0.60
// Copyright (c) 2013 by Rick C. Hodgin
//////
// Last update:
//     Nov.02.2014
//////
// Change log:
//     Nov.02.2014	- Initial creation
//////
//
// This file is self-contained and handles all scaling algorithms.  It can be used as an include
// file for other stand-alone projects.  It was extracted from offline code related to the
// Village Freedom Project.
//
//////////
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
//     http://www.visual-freepro.org
//     http://www.visual-freepro.org/blog/
//     http://www.visual-freepro.org/forum/
//     http://www.visual-freepro.org/wiki/
//     http://www.visual-freepro.org/wiki/index.php/PBL
//
// Thank you.  And may The Lord bless you richly as you lift up your life, your
// talents, your gifts, your praise, unto Him.  In Jesus' name I pray.  Amen.
//
//////
//   ____                       _____              _  _
//  |  _ \                     / ____|            | |(_)
//  | |_) | _ __ ___   _ __   | (___    ___  __ _ | | _  _ __    __ _
//  |  _ < | '_ ` _ \ | '_ \   \___ \  / __|/ _` || || || '_ \  / _` |
//  | |_) || | | | | || |_) |  ____) || (__| (_| || || || | | || (_| |
//  |____/ |_| |_| |_|| .__/  |_____/  \___|\__,_||_||_||_| |_| \__, |
//                    | |                                        __/ |
//                    |_|                                       |___/
//   Bitmap Scaling -- Simple arbitrary bitmap scaling algorithm.
//////////




struct SRGB24
{
	u8		blu;				// 24-bit RGB values in bitmap files are physically stored as BGR
	u8		grn;
	u8		red;
};

struct SRGBF24
{
	f64		blu;				// 24-bit RGB values
	f64		grn;
	f64		red;
	f64		area;				// Area of a single pixel accounting for this color component, 1.0 if encompasses entire pixel
};

struct SBitmapProcess
{
	// Input
	BITMAPINFOHEADER*	bii;
	s8*					bdi;
	u32					actualWidthI;

	// Output
	BITMAPINFOHEADER*	bio;
	s8*					bdo;
	u32					actualWidthO;

	// Holds storage data for single spanned pixels
	u32					red;
	u32					grn;
	u32					blu;

	// tpoints is a buffer created to store the conversion pixel data during accumulation
	// Use formula:
	//		tpoints	= (SRGBF24*)malloc(		((u32)(1.0/ratioV) + 3)   *
	//										((u32)(1.0/ratioH) + 3))
	//
	f64					ratioV;			// (f64)bio->biHeight	/ (f64)bii->biHeight;
	f64					ratioH;			// (f64)bio->biWidth	/ (f64)bii->biWidth;
	u32					count;			// Number of valid points in tpoints
	SRGBF24*			pixels;			// Accumulation buffer for point data needed to feed into destination

	// Temporary variables used for processing
	SRGB24*				optr;				// Output pointer to the upper-left pixel for this x,y
	SRGB24*				iptra;				// Input pointer to the left-most pixel of the first row (the anchor)
	SRGB24*				iptr;				// Input pointer to the left-most pixel for this y row
	u32					x;					// X-coordinate
	u32					y;					// Y-coordinate
	f64					ulx;				// Upper-left X
	f64					uly;				// Upper-left Y
	f64					lrx;				// Lower-right X
	f64					lry;				// Lower-right Y
	f64					widthLeft;			// Width for each left-most pixel
	f64					widthRight;			// Width for each right-most pixel
	f64					height;				// Height for a particular pixel portion (upper, lower)
	f64					area;				// Temporary computed area for various pixels
	s32					left;				// Left-side pixel offset into line
	s32					right;				// Number of pixels to reach the right-most pixel
	s32					middleStartH;		// Starting pixel offset for middle span
	s32					middleFinishH;		// Ending pixel offset for middle span
	s32					middleStartV;		// Middle starting pixel
	s32					middleFinishV;		// Middle ending pixel

	// Indicates the span from upper-left corner
	bool				spans2H;			// Spans at least 2 pixels horizontally, meaning it begins somewhere in 1.x, for example, and ends somewhere beyond 2.x
	bool				spans3H;			// Spans at least 3 pixels horizontally, meaning it begins somewhere in 1.x, for example, and ends somewhere beyond 3.x
	bool				spans2V;			// Spans at least 2 pixels vertically, meaning it begins somewhere in 1.x, for example, and ends somewhere beyond 2.x
	bool				spans3V;			// Spans at least 3 pixels vertically, meaning it begins somewhere in 1.x, for example, and ends somewhere beyond 3.x
};




//////////
// Forward declarations
//////
	u32				iScaleImage										(s8* tcBmp24FilenameIn, s8* tcBmp24FilenameOut, f64 tfHorizontalScaler, f64 tfVerticalScaler);
	u32				iComputeActualWidth								(u32 tnWidth);
	u32				iIntegersBetween								(f64 p1, f64 p2);
	void			iGetSpannedPixelColors							(SBitmapProcess* bp);
	void			iGetSpannedPixelColors1							(SBitmapProcess* bp);
	void			iGetSpannedPixelColors2							(SBitmapProcess* bp);
	void			iGetSpannedPixelColors3							(SBitmapProcess* bp);
	void			iGetSpannedPixelColors4							(SBitmapProcess* bp);
	void			iGetSpannedPixelColors5							(SBitmapProcess* bp);
	void			iGetSpannedPixelColors6							(SBitmapProcess* bp);
	void			iGetSpannedPixelColors7							(SBitmapProcess* bp);
	void			iGetSpannedPixelColors8							(SBitmapProcess* bp);
	void			iGetSpannedPixelColors9							(SBitmapProcess* bp);
