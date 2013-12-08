//////////
//
// /libsf/utils/dsf/msvc++/dsf/dsf/dsf.cpp
//
//////
//
//
//////
// Version 0.60
// Copyright (c) 2013 by Rick C. Hodgin
//////
// Last update:
//     Dec.02.2013
//////
// Change log:
//     Dec.02.2013	- Initial creation
//////
//
// Top-level program for DSF.DLL. Contains all helper algorithms for creating binary characters
// of existing font sets for translation into the DSF format.
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
//     http://www.visual-freepro.org/wiki/index.php/Repeat_License
//
// Thank you.  And may The Lord bless you richly as you lift up your life, your
// talents, your gifts, your praise, unto Him.  In Jesus' name I pray.  Amen.
//
//////




#include "dsf.h"




//////////
//
// Main DLL entry point
//
//////
	BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
	{
		//////////
		// Store the instance for global use
		//////
			ghInstance = hModule;


		//////////
		// Windows tells us why we're being invoked
		//////
			switch (ul_reason_for_call)
			{
				case DLL_PROCESS_ATTACH:
					initialize();
					break;
				case DLL_THREAD_ATTACH:
				case DLL_THREAD_DETACH:
				case DLL_PROCESS_DETACH:
					break;
			}
			return TRUE;
	}




//////////
//
// Called to obtain the bitmap of the indicated character.
//
//////
	int dsf_get_character_bitmap(int tnAscii, char* tcBitmapFilename, char* tcFloanFilename, char* tcFontName, int tnHeight, int tnWidth)
	{
		int		lnResult;
		bool	llPseudo;
		char	buffer[] = "delete_me.bmp";


		//////////
		// Make sure there is a valid filename
		//////
			if (!tcBitmapFilename || strlen(tcBitmapFilename) == 0)
			{
				llPseudo			= true;
				tcBitmapFilename	= (char*)buffer;		// Use our fake filename
			}


		//////////
		// Grab the bitmap
		//////
			lnResult = iGetCharacterBitmap(tnAscii, tcBitmapFilename, tcFontName, tnHeight, tnWidth);


		//////////
		// If they want the floan data, generate it
		//////
			if (lnResult == 0 && tcFloanFilename)
				lnResult = iGetFloanFromBitmap(tnAscii, tcBitmapFilename, tcFloanFilename);


		//////////
		// If we had to create a temporary filename, delete it
		//////
			if (llPseudo)
				DeleteFileA(tcBitmapFilename);


		//////////
		// Indicate success or failure
		//////
			return(lnResult);
	}




//////////
//
// Called to scale a bitmap to the indicated size, and clip it to some other portion.  This
// algorithm was created to allow the user to obtain a font from dsf_get_character_bitmap(),
// but then to override the default generated image to make it resized appropriately for the
// target font.
//
//////
	int dsf_scale_and_clip_bitmap(char* tcBitmapFilenameIn, char* tcBitmapFilenameOut, f32 tfWidth, f32 tfHeight, int tnClipLeft, int tnClipTop, int tnNewWidth, int tnNewHeight)
	{
// TODO:  This feature may be supplanted by using the templates point system, whereby points are simply manipulated rather than a physical bitmap being scaled.
// TODO:  However, "We shall see, Xur.  We shall see."  Can you name that quote? :-)  Here's another clue:  "It takes more than a sceptor to rule, Xur, even on Rylos."
// TODO:  https://www.youtube.com/watch?v=JwaRQ-_kgy8
		return(0);
	}




//////////
//
//  Called to initiate a new session of editing.
//
//////
	int dsf_create_new_instance(void)
	{
		union {
			SInstance*	p;
			u32			value;
		};


		//////////
		// Allocate our instance
		//////
			p = (SInstance*)builder_allocateBytes(instances, sizeof(SInstance));


		//////////
		// Initialize it
		//////
			memset(p, 0, sizeof(SInstance));
			builder_createAndInitialize(&p->chars,	-1);
			builder_createAndInitialize(&p->refs,	-1);
			builder_createAndInitialize(&p->hwnds,	-1);


		//////////
		// Brand it
		//////
			memcpy(&p->id, cgcDsfBrand, sizeof(p->id));
			p->id_size		= sizeof(SInstance);
			p->activeChar	= 65;				// Default to "A"


		//////////
		// Return the address as its handle
		//////
			return(value);
	}




//////////
//
// Called to set the data for the font instance
//
//////
	int dsf_set_font_data(u32 tnInstance,	f32 tfAscent,	f32 tfUpper,	f32 tfLower,		f32 tfLeft,			f32 tfRight,
											f32 tfBase,		f32 tfDescent,	f32 tfWidth,
											f32 tfItalics,	f32 tfBold,		f32 tfUnderTop,		f32 tfUnderBot,		f32 tfStrikeTop,	f32 tfStrikeBot)
	{
		SInstance*	p;
		bool		llValid;


		//////////
		// Make sure our environment is sane
		//////
			p = iGetDsfInstance(tnInstance, &llValid);
			if (!llValid)
				return(-1);

		//////////
		// Store the indicated data
		//////
			p->font.fAscent		= tfAscent;				// See the explanations in the VFP DSF project, frmEdit::create_tables()
			p->font.fUpper		= tfUpper;
			p->font.fLower		= tfLower;
			p->font.fLeft		= tfLeft;
			p->font.fRight		= tfRight;
			p->font.fBase		= tfBase;
			p->font.fDescent	= tfDescent;
			p->font.fWidth		= tfWidth;
			p->font.fItalics	= tfItalics;
			p->font.fBold		= tfBold;
			p->font.fUnderTop	= tfUnderTop;
			p->font.fUnderBot	= tfUnderBot;
			p->font.fStrikeTop	= tfStrikeTop;
			p->font.fStrikeBot	= tfStrikeBot;


		//////////
		// Indicate success
		//////
			return(0);
	}




//////////
//
// Called to load a character with its data based on (u8)tnType (S=Spline, D=Definition,
// R=Reference, L=Link). For Definition entries, tiid must be above the standard 0..255 ASCII
// character range.  Reference entries will be in the 0..255 range, but tiLnkId must refer to
// an entry 256 or above.  Link entries can refer to any item, but must also include tiLnkOrder
// to indicate what explicit item they want to modify.
//
//////
	int dsf_load_character(u32 tnInstance,	u32 tnType, u32 tiid, u32 tiOrder, s8* tcDesc10, u32 tlNewStroke, u32 tlSelected,
											f32 tfOx, f32 tfOy, f32 tfOt, f32 tfLr, f32 tfLt, f32 tfRr, f32 tfRt, 
											u32 tiSubdivs, u32 tiLnkId, u32 tiLnkOrder)
	{
		SInstance*	p;
		SSpline*	s;
		bool		llValid;


		//////////
		// Make sure our environment is sane
		//////
			p = iGetDsfInstance(tnInstance, &llValid);
			if (!llValid)
				return(-1);


		//////////
		// Find or create the indicated character instance
		//////
			s = iFindSplineInstance(p->chars, tiid, (u8)tnType, tiOrder, tiLnkId, tiLnkOrder);
			if (!s)
				return(-2);		// Error finding (an invalid combination was provided)


		//////////
		// Populate the data
		//////
			s->cType		= (u8)tnType;
			s->iid			= tiid;
			s->iOrder		= tiOrder;
			s->lPenDown	= ((tlNewStroke == 0) ? false : true);
			s->lSelected	= ((tlSelected == 0) ? false : true);
			s->ox			= tfOx;
			s->oy			= tfOy;
			s->ot			= tfOt;
			s->lr			= tfLr;
			s->lt			= tfLt;
			s->rr			= tfRr;
			s->rt			= tfRt;
			s->iSubdivs		= tiSubdivs;
			s->iLnkId		= tiLnkId;
			s->iLnkOrder	= tiLnkOrder;

			// Store the description
			memcpy(&s->cDesc[0], tcDesc10, 10);
		

		//////////
		// Indicate success
		//////
			return(0);
	}




//////////
//
// Called to load the indicated instance.  We search to see if a previous entry has been added
// with this information.  If so, it's updated.  If not, it's appended.
//
//////
	int dsf_load_reference(u32 tnInstance,	u32 tnType, s8* tcDesc40,
											f32 tfRef1X, f32 tfRef1Y,
											f32 tfRef2X, f32 tfRef2Y,
											f32 tfRef3X, f32 tfRef3Y,
											f32 tfRef4X, f32 tfRef4Y,
											f32 tfRef5X, f32 tfRef5Y,
											bool tlVisible, s8* tcChars1_128, s8* tcChars2_128)
	{
		SInstance*	p;
		SRefs*		r;
		bool		llValid;


		//////////
		// Make sure our environment is sane
		//////
			p = iGetDsfInstance(tnInstance, &llValid);
			if (!llValid)
				return(-1);


		//////////
		// Try to find the indicated data
		//////
			r = iFindRefsInstance(p->refs, (u8)tnType, tcDesc40);
			if (!r)
			{
				// It's a new entry
				r = (SRefs*)builder_allocateBytes(p->refs, sizeof(SRefs));
				if (!r)
					return(-2);		// Error allocating

				// Initialize it
				memset(r, 0, sizeof(SRefs));
			}


		//////////
		// Populate the data
		//////
			r->cType		= (u8)tnType;

			r->fref1x		= tfRef1X;
			r->fref1y		= tfRef1Y;

			r->fref2x		= tfRef2X;
			r->fref2y		= tfRef2Y;

			r->fref3x		= tfRef3X;
			r->fref3y		= tfRef3Y;

			r->fref4x		= tfRef4X;
			r->fref4y		= tfRef4Y;

			r->fref5x		= tfRef5X;
			r->fref5y		= tfRef5Y;

			r->lVisible		= tlVisible;

			memcpy(&r->cDesc[0], tcDesc40, 40);
			memcpy(&r->cChars1[0], tcChars1_128, 128);
			memcpy(&r->cChars2[0], tcChars2_128, 128);


		//////////
		// Release the floan data.  It will be re-populated later if this ref is ever referenced
		//////
			builder_FreeAndRelease(&r->floans);


		//////////
		// Indicate success
		//////
			return(0);
	}




//////////
//
// Called to load the indicated instance.  We search to see if a previous entry has been added
// with this information.  If so, it's updated.  If not, it's appended.
//
//////
	int dsf_load_template(u32 tnInstance, u32 tipid, f32 tfX, f32 tfY, u32 tnRecno)
	{
		SInstance*	p;
		STems*		t;
		bool		llValid;


		//////////
		// Make sure our environment is sane
		//////
			p = iGetDsfInstance(tnInstance, &llValid);
			if (!llValid)
				return(-1);


		//////////
		// Try to find the indicated data
		//////
			t = iCreateNewTemsEntry(p->chars, tipid);
			if (!t)
				return(-2);		// Error allocating


		//////////
		// Populate the data
		//////
			t->fx		= tfX;
			t->fy		= tfY;
			t->recno	= tnRecno;


		//////////
		// Indicate success
		//////
			return(0);
	}




//////////
//
// Called to load the indicated instance.  We search to see if a previous entry has been added
// with this information.  If so, it's updated.  If not, it's appended.
//
//////
	int dsf_get_changed_template(u32 tnInstance, u32 tipid, s8* tcY12, s8* tcX12, s8* tcRecno12, u32 tnNextNewRecno)
	{
		u32			lnI;
		SInstance*	p;
		SBuilder*	tems;
		STems*		t;
		bool		llValid;


		//////////
		// Make sure our environment is sane
		//////
			p = iGetDsfInstance(tnInstance, &llValid);
			if (!llValid)
				return(-1);


		//////////
		// Try to find the indicated data
		//////
			tems = iGetTemsBuilder(p->chars, tipid);
			if (!tems)
				return(-2);		// Error accessing this pid


		//////////
		// Find the first changed entry
		//////
			for (lnI = 0; lnI < tems->populatedLength; lnI += sizeof(STems))
			{
				// Grab the pointer
				t = (STems*)(tems->data + lnI);

				// If it's changed, but not deleted
				if (t->changed && !t->deleted)
				{
					// Update the recno() if it's a new item
					if (t->recno == -1)
						t->recno = tnNextNewRecno;

					// Store each item
					sprintf(tcX12,		"%7.5f",	t->fx);
					sprintf(tcY12,		"%7.5f",	t->fy);
					sprintf(tcRecno12,	"%u",		t->recno);

					// Mark it no longer changed
					t->changed = false;

					// Indicate success
					return(0);
				}
			}


		//////////
		// Indicate that there are no more items
		//////
			return(-3);
	}




//////////
//
// Called to load the indicated instance.  We search to see if a previous entry has been added
// with this information.  If so, it's updated.  If not, it's appended.
//
//////
	int dsf_get_deleted_template(u32 tnInstance, u32 tipid, s8* tcRecno12)
	{
		u32			lnI;
		SInstance*	p;
		SBuilder*	tems;
		STems*		t;
		bool		llValid;


		//////////
		// Make sure our environment is sane
		//////
			p = iGetDsfInstance(tnInstance, &llValid);
			if (!llValid)
				return(-1);


		//////////
		// Try to find the indicated data
		//////
			tems = iGetTemsBuilder(p->chars, tipid);
			if (!tems)
				return(-2);		// Error accessing this pid


		//////////
		// Find the first changed entry
		//////
			for (lnI = 0; lnI < tems->populatedLength; lnI += sizeof(STems))
			{
				// Grab the pointer
				t = (STems*)(tems->data + lnI);

				// Report on previously existing deleted items.  If the user adds an item, then
				// deletes it before saving it is simply an orphan record that will be freed at exit.
				if (t->deleted && t->recno != -1)
				{
					// Store the record number
					sprintf(tcRecno12, "%u", t->recno);

					// Indicate success
					return(0);
				}
			}


		//////////
		// Indicate that there are no more items
		//////
			return(-3);
	}




//////////
//
// Called to indicate the user wants to make active another character for editing
//
//////
	int dsf_set_active_character(u32 tnInstance, u32 tiid)
	{
		SInstance*	p;
		bool		llValid;


		//////////
		// Make sure our environment is sane
		//////
			p = iGetDsfInstance(tnInstance, &llValid);
			if (!llValid)
				return(-1);


		//////////
		// Make sure that character is defined
		/////
			if (tiid * sizeof(SChars) < p->chars->populatedLength)
			{
				// It exists
				p->activeChar = tiid;
				return(0);

			} else {
				// Invalid character range
				return(-2);
			}
	}




//////////
//
// Called to render a markup form used for editing, or for debugging, at the indicated size.  This
// is what the font looks like in the edit window of the DSF Font Editor.
//
//////
	int dsf_render_markup(u32 tnInstance, s32 tnWidth, s32 tnHeight, u32 tlBold, u32 tlItalic, u32 tlUnderline, u32 tlStrikethrough, s8* tcBitmapPathname, u32 tnHwnd, s32 tnX, s32 tnY)
	{
		SInstance*	p;
		SChars*		thisChar;
		bool		llValid;


		//////////
		// Make sure our environment is sane
		//////
			p = iGetDsfInstance(tnInstance, &llValid);
			if (!llValid)
				return(-1);


		//////////
		// Find the active character instance
		//////
			thisChar = iiFindOnlyThisChars(p->chars, p->activeChar);
			if (!thisChar)
				return(-2);		// Error finding (an invalid combination was provided)


		//////////
		// Render it
		//////
			return(iRender(p, thisChar, tnWidth, tnHeight, true, tlBold, tlItalic, tlUnderline, tlStrikethrough, tcBitmapPathname, tnHwnd, tnX, tnY));
	}




//////////
//
// Called to render a final form at the indicated size.  This is what the font will look like when
// generated for regular use by the system.
//
//////
	int dsf_render_final(u32 tnInstance, s32 tnWidth, s32 tnHeight, u32 tlBold, u32 tlItalic, u32 tlUnderline, u32 tlStrikethrough, s8* tcBitmapPathname, u32 tnHwnd, s32 tnX, s32 tnY)
	{
		SInstance*	p;
		SChars*		thisChar;
		bool		llValid;


		//////////
		// Make sure our environment is sane
		//////
			p = iGetDsfInstance(tnInstance, &llValid);
			if (!llValid)
				return(-1);


		//////////
		// Find the active character instance
		//////
			thisChar = iiFindOnlyThisChars(p->chars, p->activeChar);
			if (!thisChar)
				return(-2);		// Error finding (an invalid combination was provided)


		//////////
		// Render it
		//////
			return(iRender(p, thisChar, tnWidth, tnHeight, false, tlBold, tlItalic, tlUnderline, tlStrikethrough, tcBitmapPathname, tnHwnd, tnX, tnY));
	}




/////////
//
// Called from DllMain() one time to initialize the DSF DLL.
//
//////
	void initialize(void)
	{
//		f32		lfX, lfY, lfTheta, lfRadius, lfA, lfB, lfV1, lfV2;
//		bool	llPenDown;


		//////////
		// Initialize our global buffers
		/////
			builder_createAndInitialize(&instances, -1);
			builder_createAndInitialize(&placeholder, -1);


		//////////
		// Build an "i at the cross" for the placeholder (meaning " 'me' at the cross")
		//////
			// Cross
			iAddSplineFromToLR(placeholder, true,		0.4075f,	0.975f,		0.59f,		0.975f);
			iAddSplineFromToLR(placeholder, false,		0.4075f,	0.05f,		0.59f,		0.05f);
			iAddSplineFromToLR(placeholder, true,		0.045f,		0.74f,		0.94f,		0.74f);
			iAddSplineFromToLR(placeholder, false,		0.045f,		0.62f,		0.94f,		0.62f);

// 			// "i" leg
// 			iAddSplineFromToLR(placeholder, true,		0.775f,		0.435f,		0.85f,		0.485f);
// 			iAddSplineFromToLR(placeholder, false,		0.7825f,	0.425f,		0.865f,		0.47f);
// 			iAddSplineFromToLR(placeholder, false,		0.7875f,	0.415f,		0.8775f,	0.45f);
// 			iAddSplineFromToLR(placeholder, false,		0.79f,		0.405f,		0.8875f,	0.425f);
// 			iAddSplineFromToLR(placeholder, false,		0.7925f,	0.3975f,	0.8925f,	0.405f);
// 			iAddSplineFromToLR(placeholder, false,		0.7925f,	0.39f,		0.895f,		0.39f);
// 			iAddSplineFromToLR(placeholder, false,		0.7925f,	0.14f,		0.895f,		0.14f);
// 			iAddSplineFromToLR(placeholder, false,		0.795f,		0.125f,		0.895f,		0.13f);
// 			iAddSplineFromToLR(placeholder, false,		0.80f,		0.105f,		0.8975f,	0.12f);
// 			iAddSplineFromToLR(placeholder, false,		0.81f,		0.08f,		0.90f,		0.1125f);
// 			iAddSplineFromToLR(placeholder, false,		0.825f,		0.06f,		0.905f,		0.1f);
// 			iAddSplineFromToLR(placeholder, false,		0.8375f,	0.0425f,	0.915f,		0.095f);
// 
// 			// "i" dot
// 			lfX			= 0.765f;
// 			lfY			= 0.5225f;
// 			lfA			= 0.1325f / 2.0f;
// 			lfB			= 0.0925f / 2.0f;
// 			llPenDown	= true;
// 			for (lfTheta = 0.0f; lfTheta <= _PI + 0.001; lfTheta += _PI / 10.0f)
// 			{
// 				// Given:  a=major, b=minor, r=radius
// 				//         r = (a*b) / sqrt(b*cos(theta)^2 + a*sin(theta)^2)
// 				lfV1		= lfB * cos(lfTheta);
// 				lfV2		= lfA * sin(lfTheta);
// 				lfRadius	= (lfA * lfB) / sqrt(lfV1*lfV1 + lfV2*lfV2);
// 				iAddSplineCenterThetaRadiusLR(placeholder, llPenDown, lfX, lfY, lfRadius, iAdjustTheta(_2PI - lfTheta), lfTheta);
// 				llPenDown = false;
// 			}
	}




//////////
//
// Adds a new spline to the builder, computing its components based on a straight line from L to R.
//
//////
	void iAddSplineFromToLR(SBuilder* b, bool tlPenDown, f32 tfXL, f32 tfYL, f32 tfXR, f32 tfYR)
	{
		SLineF32	line;
		SSpline*	s;


		//////////
		// Compute the line
		//////
			line.p1.x	= tfXL;
			line.p1.y	= tfYL;
			line.p2.x	= tfXR;
			line.p2.y	= tfYR;
			iComputeLine(&line);


		//////////
		// Add the midpoint as the spline, and use the slope of the line to determine the rotation.
		//////
			s = (SSpline*)builder_allocateBytes(b, sizeof(SSpline));
			if (s)
			{
				// Initialize everything
				memset(s, 0, sizeof(SSpline));

				// Populate
				s->ox	= line.mid.x;
				s->oy	= line.mid.y;
				s->ot	= line.theta;

				// Indicate the right and left side length (left and right theta is 0)
				s->lr	= line.length / 2.0f;
				s->lt	= _PI;
				s->rr	= s->lr;

				// Does this start a new pen stroke?
				s->lPenDown = tlPenDown;
			}
	}




//////////
//
// Adds a new spline to the builder, computing from the indicated x,y center, given a radius and
// two angles, first for L, then for R.  The line runs horizontally, which means from 0..1, which
// is from left to right in our system, as per the standard Quad 1 X,Y coordinate system.
//
//////
	void iAddSplineCenterThetaRadiusLR(SBuilder* b, bool tlPenDown, f32 tfX, f32 tfY, f32 tfRadius, f32 tfThetaL, f32 tfThetaR)
	{
		SSpline* s;


		//////////
		// Add the midpoint as the spline, and use the slope of the line to determine the rotation.
		//////
			s = (SSpline*)builder_allocateBytes(b, sizeof(SSpline));
			if (s)
			{
				// Initialize everything
				memset(s, 0, sizeof(SSpline));

				// Populate
				s->ox	= tfX;
				s->oy	= tfY;

				// Indicate the right and left side length (left and right theta is 0)
				s->lr	= tfRadius;
				s->lt	= tfThetaL;
				s->rr	= tfRadius;
				s->rt	= tfThetaR;

				// Does this start a new pen stroke?
				s->lPenDown = tlPenDown;
			}
	}




//////////
//
// Physically construct the indicated character.    It does this by sizing some known maximums, and
// generating the bitmap for our new characters using that size.  We migrate and center the bitmap
// onto the known maximum bitmap canvas, and then using scale the image down to the indicated size.
//
//		(1) "hKltfgpqy" + SPACE(1)
//		(2) "hKltfgpqy" + SPACE(1) + CHR(tnAscii)
//
// Then the second bitmap will be wider than the first, but otherwise identical.  That following
// portion is the part which is returned to the indicated filename.  An appropriate font size is
// used based on the height and width, with the final image generated being scaled to the
//
//////
	int iGetCharacterBitmap(int tnAscii, char* tcBitmapFilename, char* tcFontName, int tnHeight, int tnWidth)
	{
		int			lnWidth, lnHeight, lnMakeWidth;
		f32			lfH, lfV;
		HFONT		hfont;
		HDC			lhdc;
		HBITMAP		lhbmp2;
		RECT		lrc1, lrc2, lrcM, lrcW;
		SBGR*		bd2;
		char		mbuffer[] = "M";
		char		wbuffer[] = "W";
		char		buffer[] = "hKltfgpqy  \0";
		char		rawBuffer[_MAX_FNAME];


		//////////
		// Create the font
		//////
			lnHeight = -MulDiv(tnHeight, GetDeviceCaps(GetDC(GetDesktopWindow()), LOGPIXELSY), 72);
			hfont = CreateFontA(lnHeight, 0, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, NONANTIALIASED_QUALITY, FF_DONTCARE, tcFontName);
			if (!hfont)
				return(-1);


		//////////
		// Generate the two bitmaps
		//////
			lhdc = CreateCompatibleDC(GetDC(GetDesktopWindow()));
			SelectObject(lhdc, hfont);
			buffer[sizeof(buffer) - 3] = 0;


		//////////
		// Determine sizes
		//////
			// Bitmap 1 (without the indicated character)
			SetRect(&lrc1, 0, 0, 0, 0);
			DrawTextA(lhdc, buffer, strlen(buffer), &lrc1, DT_CALCRECT);

			// Bitmap 2 (with the indicated character)
			buffer[sizeof(buffer) - 3] = (char)tnAscii;
			SetRect(&lrc2, 0, 0, 0, 0);
			DrawTextA(lhdc, buffer, strlen(buffer), &lrc2, DT_CALCRECT);

			// M
			SetRect(&lrcM, 0, 0, 0, 0);
			DrawTextA(lhdc, mbuffer, 1, &lrcM, DT_CALCRECT);

			// W
			SetRect(&lrcW, 0, 0, 0, 0);
			DrawTextA(lhdc, wbuffer, 1, &lrcW, DT_CALCRECT);

			// Compute width and height
			lnWidth		= lrc2.right  - lrc2.left;
			lnHeight	= lrc2.bottom - lrc2.top;
			lnMakeWidth	= max(lrcM.right - lrcM.left, lrcW.right - lrcW.left);


		//////////
		// Bitmap 2
		//////
			lhbmp2 = iCreateBitmap(lhdc, lnWidth, lnHeight, 1, 24, (void**)&bd2);
			SelectObject(lhdc, lhbmp2);
			FillRect(lhdc, &lrc2, (HBRUSH)GetStockObject(WHITE_BRUSH));
			DrawTextA(lhdc, buffer, strlen(buffer), &lrc2, DT_LEFT);


		//////////
		// Write out the portion that's different to a temporary file
		//////
			memset(rawBuffer, 0, sizeof(rawBuffer));
			memcpy(rawBuffer, tcBitmapFilename, min(strlen(tcBitmapFilename), sizeof(rawBuffer) - 1));
			rawBuffer[strlen(rawBuffer) - 1] = 'q';
			lnMakeWidth = iSaveBitmap(bd2, lnWidth, lnHeight, lrc1.right - lrc1.left, rawBuffer, lnMakeWidth);


		//////////
		// Release everything
		//////
			DeleteObject((HGDIOBJ)hfont);
			DeleteObject((HGDIOBJ)lhbmp2);
			DeleteDC(lhdc);


		//////////
		// Scale the generated image up to the indicated size
		//////
			lfH = (f32)tnWidth	/ (f32)lnMakeWidth;
			lfV = (f32)tnHeight	/ (f32)lnHeight;
			iScaleImage(rawBuffer, tcBitmapFilename, lfH, lfV);
			DeleteFileA(rawBuffer);


		//////////
		// Indicate success
		//////
			return(0);
	}

	int iSaveBitmap(SBGR* bgr, int tnWidth, int tnHeight, int tnLeft, char* tcBitmapFilename, int tnMakeWidth)
	{
		int					lnY, lnRowWidth, lnWritePels, lnCopyPels, lnOffset, lnCopyWidth;
		SBGR*				lbgr;
		SBGR*				lbgrBuffer;
		BITMAPFILEHEADER	lbh;
		BITMAPINFOHEADER	lbi;
		FILE*				lfh;


		//////////
		// Create the output bitmap header
		//////    This is a test
			memset(&lbh, 0, sizeof(lbh));
			lbh.bfType		= 'MB';
			lbh.bfOffBits	= sizeof(lbh) + sizeof(lbi);

			lnCopyWidth		= max(tnWidth - tnLeft, tnMakeWidth);
			lnRowWidth		= iComputeRowWidth(tnWidth);
 
			memset(&lbi, 0, sizeof(lbi));
			lbi.biSize		= sizeof(lbi);
			lbi.biWidth		= lnCopyWidth;
			lnCopyPels		= (tnWidth - tnLeft) * 3;
			lnWritePels		= iComputeRowWidth(lbi.biWidth);
			lbi.biHeight	= tnHeight;
			lbi.biPlanes	= 1;
			lbi.biBitCount	= 24;
			lbi.biSizeImage	= lnWritePels * tnHeight;
			lbi.biXPelsPerMeter = 3270;
			lbi.biYPelsPerMeter = 3270;

			lbh.bfSize		= sizeof(lbh) + sizeof(lbi) + lbi.biSizeImage;
			

		//////////
		// Get metrics for the incoming image, and create a buffer for each line
		//////
			lnOffset	= (lbi.biWidth - (tnWidth - tnLeft)) / 2;
			lbgrBuffer	= (SBGR*)malloc(lnWritePels);
			if (lbgrBuffer)
			{
			//////////
			// Write out the header
			//////
				lfh = fopen(tcBitmapFilename, "wb+");
				if (lfh)
				{
					fwrite(&lbh, 1, sizeof(lbh), lfh);
					fwrite(&lbi, 1, sizeof(lbi), lfh);


				//////////
				// Extract out the bitmap portions.
				// Bitmaps are stored in reverse order, so we can iterate normally down through
				//////
					for (lnY = 0; lnY < tnHeight; lnY++)
					{
						//////////
						// Compute the offset to this part
						//////
							lbgr = (SBGR*)((char*)bgr + (lnY * lnRowWidth) + (tnLeft * 3));


						//////////
						// Copy to our buffer row
						//////
							memset(lbgrBuffer, 255, lnWritePels);
							memcpy(lbgrBuffer + lnOffset, lbgr, lnCopyPels);


						//////////
						// Write this row
						//////
							fwrite(lbgrBuffer, 1, lnWritePels, lfh);
					}
					// When we get here, it's saved
					fclose(lfh);
				}
				// We're done
				free(lbgrBuffer);
			}
			// Indicate how wide it is
			return(lnCopyWidth);
	}

	int iComputeRowWidth(int tnWidth)
	{
		int lnWidth;


		lnWidth = tnWidth * 3;
		if (lnWidth % 4 == 0)
			return(lnWidth);

		// Increase the width
		lnWidth += (4 - (lnWidth % 4));
		return(lnWidth);
	}

	HBITMAP iCreateBitmap(HDC thdc, int tnWidth, int tnHeight, int tnPlanes, int tnBits, void**tbd)
	{
		BITMAPINFO bi;


		//////////
		// Create a new DIB
		//////
			memset(&bi, 0, sizeof(BITMAPINFO));
			bi.bmiHeader.biSize			= sizeof(bi.bmiHeader);
			bi.bmiHeader.biWidth		= tnWidth;
			bi.bmiHeader.biHeight		= tnHeight;
			bi.bmiHeader.biPlanes		= tnPlanes;
			bi.bmiHeader.biBitCount		= tnBits;


		//////////
		// Physically create the bitmap
		//////
			return(CreateDIBSection(thdc, &bi, DIB_RGB_COLORS, tbd, NULL, 0));
	}




//////////
//
// Find every outline point and create a list of the same.
//
//////
	struct SFloanPoint
	{
		f64	x;			// X coordinate of an X,Y pair
		f64	y;			// Y coordinate of an X,Y pair
	};

	int iGetFloanFromBitmap(u32 tnAscii, char* tcBitmapFilename, char* tcFloanFilename)
	{
		int					lnI, lnY, lnX, lnRowWidth, lnOldFloanCount, lnNewFloanCount;
		f32					lfGray, lfLastGray;
		SBGR*				lbgr;
		SBGR*				lbgrBuffer;
		BITMAPFILEHEADER	lbh;
		BITMAPINFOHEADER	lbi;
		FILE*				lfh;
		SBuilder*			floans;
		SBuilder*			floansCsv;
		SFloanPoint			point;
		SFloanPoint*		pDst;
		SFloanPoint*		pSrc;
		s8					buffer[256];


		//////////
		// Open the indicated bitmap
		//////
			lfh = fopen(tcBitmapFilename, "rb");
			if (!lfh)
				return(-1);		// File does not exist


		//////////
		// Read in the header
		//////
			fread(&lbh, 1, sizeof(lbh), lfh);
			fread(&lbi, 1, sizeof(lbi), lfh);


		//////////
		// Make sure it's a sane bitmap
		//////
			if (lbh.bfSize != sizeof(lbh) + sizeof(lbi) + lbi.biSizeImage)
			{
				fclose(lfh);
				return(-2);				// Invalid header
			}
			if (lbi.biSize != sizeof(lbi))
			{
				fclose(lfh);
				return(-3);				// Invalid info
			}
			if (lbi.biPlanes != 1 || lbi.biBitCount != 24)
			{
				fclose(lfh);
				return(-4);				// Invalid bitmap style/format
			}
			lnRowWidth = iComputeRowWidth(lbi.biWidth);
			if (lnRowWidth * lbi.biHeight != lbi.biSizeImage)
			{
				fclose(lfh);
				return(-5);				// Invalid size
			}


		//////////
		// Load in the data
		//////
			lbgrBuffer = (SBGR*)malloc(lbi.biSizeImage);
			if (!lbgrBuffer)
			{
				fclose(lfh);
				return(-6);				// Out of memory
			}
			fread(lbgrBuffer, 1, lbi.biSizeImage, lfh);
			fclose(lfh);


		//////////
		// Increase contrast to full
		//////
			for (lnY = 0; lnY < lbi.biHeight; lnY++)
			{
				// Iterate all the way across
				lbgr = (SBGR*)((char*)lbgrBuffer + (lnY * lnRowWidth));

				// Look for where things start or stop
				for (lnX = 0; lnX < lbi.biWidth; lnX++, lbgr++)
				{
					// Determine the grayscale value of this pixel
					lfGray = (((f32)lbgr->red * 0.35f) + ((f32)lbgr->grn * 0.54f) + ((f32)lbgr->blu * 0.11f)) / 255.0f;

					// Is it visibly darkened?
					if (lfGray < 0.7f)
					{
						// Make it black
						lbgr->red = 0;
						lbgr->grn = 0;
						lbgr->blu = 0;

					} else {
						// Make it white
						lbgr->red = 255;
						lbgr->grn = 255;
						lbgr->blu = 255;
					}
				}
			}


		//////////
		// Initialize
		//////
			builder_createAndInitialize(&floans,	65536);
			builder_createAndInitialize(&floansCsv,	65536);


		//////////
		// Iterate through each row grabbing floan positions
		//////
			for (lnY = 0; lnY < lbi.biHeight; lnY++)
			{
				// Iterate all the way across
				lbgr = (SBGR*)((char*)lbgrBuffer + (lnY * lnRowWidth));

				// Look for where things start or stop
				lfLastGray = 1.0;		// Assume we start on a white pixel
				for (lnX = 0; lnX < lbi.biWidth; lnX++, lbgr++)
				{
					// Determine the grayscale value of this pixel
					lfGray = (((f32)lbgr->red * 0.35f) + ((f32)lbgr->grn * 0.54f) + ((f32)lbgr->blu * 0.11f)) / 255.0f;

					// Has something changed?
					if (fabs(lfGray - lfLastGray) > 0.9f)
					{
						// Store the position
						point.x = (f64)lnX	/ (f64)lbi.biWidth;
						point.y = (f64)lnY	/ (f64)lbi.biHeight;

						// Make sure it's on the reservation :-)
						if (point.x >= 0.0f && point.y >= 0.0f)
							builder_appendData(floans, (s8*)&point, sizeof(point));

						// Prepare for our next test
						lfLastGray = lfGray;
					}
				}
			}


		//////////
		// Iterate through each column grabbing floan positions
		//////
			for (lnX = 0; lnX < lbi.biWidth; lnX++)
			{
				// Iterate point by point in vertical columns
				lbgr = (SBGR*)((char*)lbgrBuffer + (lnX * 3));

				// Look for where things start or stop
				lfLastGray = 1.0;		// Assume we start on a white pixel
				for (lnY = 0; lnY < lbi.biHeight; lnY++)
				{
					// Determine the grayscale value of this pixel
					lfGray = (((f32)lbgr->red * 0.35f) + ((f32)lbgr->grn * 0.54f) + ((f32)lbgr->blu * 0.11f)) / 255.0f;

					// Has something changed?
					if (fabs(lfGray - lfLastGray) > 0.9f)
					{
						// Store the position
						point.x = (f64)lnX	/ (f64)lbi.biWidth;
						point.y = (f64)lnY	/ (f64)lbi.biHeight;

						// Make sure it's on the reservation :-)
						if (point.x >= 0.0f && point.y >= 0.0f)
							builder_appendData(floans, (s8*)&point, sizeof(point));

						// Prepare for our next test
						lfLastGray = lfGray;
					}

					// Move to next row on same column
					lbgr = (SBGR*)((s8*)lbgr + lnRowWidth);
				}
			}


		//////////
		// Sort the data in Y order ascending, then X ascending
		//////
			lnOldFloanCount = floans->populatedLength / sizeof(SFloanPoint);
			qsort(floans->data, lnOldFloanCount, sizeof(SFloanPoint), iiGetFloanFromBitmap_qsortCallback);


		//////////
		// Wash disparate data points
		//////
// TODO: The idea is to grab the points closest to each point, and then average to use the middle, rather than the integer alias


		//////////
		// Remove duplicates
		//////
			// Begin at the beginning
			pDst = (SFloanPoint*)floans->data;
			pSrc = pDst + 1;
			for (lnI = 1, lnNewFloanCount = 0; lnI < lnOldFloanCount; lnI++, pSrc++)
			{
				//////////
				// Is this one different?
				//////
					if (pDst->y != pSrc->y || pDst->x != pSrc->x)
					{
						// Yes, advance our destination pointer
						++pDst;

						// If we're not overwriting our pointer, then copy
						if (pDst != pSrc)
							memcpy(pDst, pSrc, sizeof(SFloanPoint));

						// Increase our count
						++lnNewFloanCount;
					}
			}


		//////////
		// Resize (floans are already in correct order)
		//////
			builder_setSize(floans, lnNewFloanCount * sizeof(SFloanPoint));


		//////////
		// Copy to our CSV
		//////
			pSrc = (SFloanPoint*)floans->data;
			for (lnI = 0; lnI < lnNewFloanCount; lnI++, pSrc++)
			{
				// Store the output
				sprintf(buffer, "%15.12f, %15.12f\n\0", pSrc->x, pSrc->y);

				// Append it to the builder
				builder_appendData(floansCsv, buffer, strlen(buffer));
			}
			builder_asciiWriteOutFile(floansCsv, tcFloanFilename);


		//////////
		// For debugging, populate the individual found points within the bitmap in green, and write it back out
		//////
			int					lnRowWidth_debug;
			SBGR*				lbgrBuffer_debug;
			BITMAPFILEHEADER	lbh_debug;
			BITMAPINFOHEADER	lbi_debug;
			FILE*				lfh_debug;

			memcpy(&lbh_debug, &lbh, sizeof(lbh));
			memcpy(&lbi_debug, &lbi, sizeof(lbi));

			lbi_debug.biWidth		= 400;
			lbi_debug.biHeight		= 400;
			lnRowWidth_debug		= iComputeRowWidth(lbi_debug.biWidth);
			lbi_debug.biSizeImage	= lnRowWidth_debug * lbi_debug.biHeight;
			lbh_debug.bfSize		= sizeof(lbh_debug) + sizeof(lbi_debug) + lbi_debug.biSizeImage;
			lbgrBuffer_debug		= (SBGR*)malloc(lbi_debug.biSizeImage);
			memset(lbgrBuffer_debug, 255, lbi_debug.biSizeImage);

			pSrc = (SFloanPoint*)floans->data;
			for (lnI = 0; lnI < lnNewFloanCount; lnI++, pSrc++)
			{
				// Re-acquire our position
				lnX = (s32)(pSrc->x * (f32)lbi_debug.biWidth);
				lnY = (s32)(pSrc->y * (f32)lbi_debug.biHeight);

				// Store it
				lbgr = (SBGR*)((s8*)lbgrBuffer_debug + (lnY * lnRowWidth_debug) + (lnX * 3));

				// Make it black
				lbgr->red	= 0;
				lbgr->grn	= 0;
				lbgr->blu	= 0;
			}
			char filename[_MAX_FNAME];
			sprintf(filename, "ascii_%03u.bmp\0", tnAscii);
			lfh_debug = fopen(filename, "wb+");
			fwrite(&lbh_debug, 1, sizeof(lbh_debug), lfh_debug);
			fwrite(&lbi_debug, 1, sizeof(lbi_debug), lfh_debug);
			fwrite(lbgrBuffer_debug, 1, lbi_debug.biSizeImage, lfh_debug);
			fclose(lfh_debug);
//			_asm nop;
//			DeleteFileA(filename);


		//////////
		// Clean house
		//////
			builder_FreeAndRelease(&floans);
			builder_FreeAndRelease(&floansCsv);


		//////////
		// Indicate our success
		//////
			return(lnNewFloanCount);
	}




//////////
//
// QSORT() callback, orders data by Y ascending, then by X ascending.
//
//////
	int iiGetFloanFromBitmap_qsortCallback(const void* l, const void* r)
	{
		SFloanPoint*	left;
		SFloanPoint*	right;


		// Get our pointers properly
		left	= (SFloanPoint*)l;
		right	= (SFloanPoint*)r;

		// See how the cookie crumbles
		     if (left->y < right->y)		return(-1);		// Left is less than right
		else if (left->y > right->y)		return(1);		// Left is greater than right
		else if (left->x < right->x)		return(-1);		// Left is less than right
		else if (left->x > right->x)		return(1);		// Left is greater than right
		else								return(0);		// They're equal
	}




//////////
//
// Called to verify if the indicated handle is valid
//
//////
	SInstance* iGetDsfInstance(u32 tnHandle, bool* tlValid)
	{
		union {
			SInstance*	p;
			u32			_p;
		};


		//////////
		// Make sure our environment is sane, and if so that the handle is valid
		//////
			_p = tnHandle;

			// Is it a pointer?
			if (p)
			{
				// Is it in range?
				if (_p >= instances->_data && _p <= instances->_data + instances->populatedLength)
				{
					// Is it identical?
					if (_memicmp(p->id, cgcDsfBrand, sizeof(p->id)) == 0 && p->id_size == sizeof(SInstance))
					{
						// Valid
						*tlValid = true;
						return(p);
					}
				}
			}

			// Invalid
			*tlValid = false;
			return(NULL);
	}




//////////
//
// Called to search through the character splines, definition entries, links, etc., to find the
// matching character reference.
//
//////
	SSpline* iFindSplineInstance(SBuilder* charsBuilder, u32 tnIid, u8 tcType, u32 tiOrder, u32 tiLnkId, u32 tiLnkOrder)
	{
		SChars*		thisChar;
		SBuilder*	thisSplineBuilder;


		//////////
		// Make sure our environment is sane
		//////
			if (charsBuilder && charsBuilder->data)
			{
				// Grab that builder
				thisChar = iiFindOrCreateThisChars(charsBuilder, tnIid);
				if (!thisChar)
					return(NULL);

				// Grab this character's builder for splines/definitions
				thisSplineBuilder = thisChar->splines;

				// Find out what type this one is
				switch (tcType)
				{
					case 'S':
					case 's':
						// It's a spline, which is part of the indicated item
						// We search by tnIid and tiOrder
						if (tnIid > 255)
							return(NULL);		// Invalid spline reference

						// Search for (and add it if need be)
						return(iFindSplineInstance_SD(thisSplineBuilder, tnIid, tiOrder, true));


					case 'D':
					case 'd':
						// It's the same as a spline, but the definition must be an item above 255, and it's
						// not part of a character, but rather just a segment to be used by characters.
						// We search by tnIid and tiOrder
						if (tnIid <= 255)
							return(NULL);		// Error

						// Search for (and add it if need be)
						return(iFindSplineInstance_SD(thisSplineBuilder, tnIid, tiOrder, true));


					case 'R':
					case 'r':
						// It's a reference. The reference must refer to an item above 255, per tiLnkId
						// We search by tnIid, tiOrder, and tiLnkId
						if (tnIid < 256)
							return(NULL);		// Error

						// Search for (and add it if need be)
						return(iFindSplineInstance_R(thisSplineBuilder, tnIid, tiOrder, tiLnkId, true));


					case 'L':
					case 'l':
						// It's a link. The reference can refer to any item, but must include the tiLnkId and tiLnkOrder
						// We search by tnIid, tiOrder, tiLnkId, and tiLnkOrder

						// Search for (and add it if need be)
						return(iFindSplineInstance_L(thisSplineBuilder, tnIid, tiOrder, tiLnkId, tiLnkOrder, true));

				}
			}


		// If we get here, not found
		return(NULL);
	}

	SChars* iiFindOrCreateThisChars(SBuilder* charsBuilder, u32 tnIid)
	{
		u32			lnI, lnStart, lnEnd;
		SChars*		thisChar;


		// See if there's already room for this item
		if (charsBuilder->populatedLength < tnIid * sizeof(SChars))
		{
			// We have to make room for it
			lnStart = (charsBuilder->populatedLength / sizeof(SChars));
			lnEnd	= tnIid * sizeof(SChars);
			for (lnI = lnStart; lnI <= lnEnd; lnI += sizeof(SChars))
			{
				// Grab the pointer
				thisChar = (SChars*)builder_allocateBytes(charsBuilder, sizeof(SChars));

				// Initialize it
				memset(thisChar, 0, sizeof(SChars));

				// Create new builders for it
				builder_createAndInitialize(&thisChar->splines,		-1);
				builder_createAndInitialize(&thisChar->tems,		-1);
			}
		}


		//////////
		// Return the builder
		//////
			return(iiFindOnlyThisChars(charsBuilder, tnIid));
	}

	SChars* iiFindOnlyThisChars(SBuilder* charsBuilder, u32 tnIid)
	{
		if (charsBuilder->populatedLength >= tnIid * sizeof(SChars))
		{
			// There is enough room for this character to exist
			return((SChars*)(charsBuilder->data + (tnIid * sizeof(SChars))));

		} else {
			// Something's awry
			return(NULL);
		}
	}

	SSpline* iFindSplineInstance_SD(SBuilder* thisSplineBuilder, u32 tnIid, u32 tiOrder, bool tlAddIfNotFound)
	{
		u32			lnI;
		SSpline*	s;


		//////////
		// Make sure our environment is sane
		//////
			if (!thisSplineBuilder)
				return(NULL);


		//////////
		// Search for it
		//////
			for (lnI = 0; lnI < thisSplineBuilder->populatedLength; lnI += sizeof(SSpline))
			{
				// Grab the pointer
				s = (SSpline*)(thisSplineBuilder->data + lnI);

				// See if this is it
				if (s->iid == tnIid && s->iOrder == tiOrder)
					return(s);
			}


		//////////
		// If we get here, it wasn't found
		//////
			if (tlAddIfNotFound)
			{
				// Create a new entry
				return((SSpline*)builder_allocateBytes(thisSplineBuilder, sizeof(SSpline)));

			} else {
				// 
				return(NULL);
			}
	}

	SSpline* iFindSplineInstance_R(SBuilder* thisSplineBuilder, u32 tnIid, u32 tiOrder, u32 tiLnkId, bool tlAddIfNotFound)
	{
		u32			lnI;
		SSpline*	s;


		//////////
		// Make sure our environment is sane
		//////
			if (thisSplineBuilder)
				return(NULL);


		//////////
		// Search for it
		//////
			for (lnI = 0; lnI < thisSplineBuilder->populatedLength; lnI += sizeof(SSpline))
			{
				// Grab the pointer
				s = (SSpline*)(thisSplineBuilder->data + lnI);

				// See if this is it
				if (s->iid == tnIid && s->iOrder == tiOrder && s->iLnkId == tiLnkId)
					return(s);
			}


		//////////
		// If we get here, it wasn't found
		//////
			if (tlAddIfNotFound)
			{
				// Create a new entry
				return((SSpline*)builder_allocateBytes(thisSplineBuilder, sizeof(SSpline)));

			} else {
				// 
				return(NULL);
			}
	}

	SSpline* iFindSplineInstance_L(SBuilder* thisSplineBuilder, u32 tnIid, u32 tiOrder, u32 tiLnkId, u32 tiLnkOrder, bool tlAddIfNotFound)
	{
		u32			lnI;
		SSpline*	s;


		//////////
		// Make sure our environment is sane
		//////
			if (thisSplineBuilder)
				return(NULL);


		//////////
		// Search for it
		//////
			for (lnI = 0; lnI < thisSplineBuilder->populatedLength; lnI += sizeof(SSpline))
			{
				// Grab the pointer
				s = (SSpline*)(thisSplineBuilder->data + lnI);

				// See if this is it
				if (s->iid == tnIid && s->iOrder == tiOrder && s->iLnkId == tiLnkId && s->iLnkOrder == tiLnkOrder)
					return(s);
			}


		//////////
		// If we get here, it wasn't found
		//////
			if (tlAddIfNotFound)
			{
				// Create a new entry
				return((SSpline*)builder_allocateBytes(thisSplineBuilder, sizeof(SSpline)));

			} else {
				// 
				return(NULL);
			}
	}




//////////
//
// Called to search through the existing refs entry to see if the indicated reference is found
//
//////
	SRefs* iFindRefsInstance(SBuilder* refs, u8 tcType, s8* tcDesc40)
	{
		s32		lnI, lnMaxCount;
		SRefs*	r;


		//////////
		// Make sure our environment is sane
		//////
			if (refs && refs->data && refs->populatedLength >= sizeof(SRefs))
			{
				// Get our starting and ending points
				lnMaxCount	= refs->populatedLength / sizeof(SRefs);
				r			= (SRefs*)refs->data;

				// Iterate through every ref
				for (lnI = 0; lnI < lnMaxCount; lnI++, r++)
				{
					// Is this it?
					if (r->cType == tcType && _memicmp(r->cDesc, tcDesc40, 40) == 0)
						return(r);		// Found it
				}
				// If we get here, not found
			}


		// If we get here, not found
		return(NULL);
	}




//////////
//
// Called to create a new templates entry as template data is being initially loaded
//
//////
	STems* iCreateNewTemsEntry(SBuilder* charsBuilder, u32 tipid)
	{
		SChars*		thisChars;
		STems*		t;


		//////////
		// Grab the thisChars parent
		//////
			thisChars = iiFindOrCreateThisChars(charsBuilder, tipid);
			if (thisChars)
			{
				// Allocate and return the new template
				t = (STems*)builder_allocateBytes(thisChars->tems, sizeof(STems));

				// Initialize the memory
				if (t)
					memset(t, 0, sizeof(STems));

				// Indicate our pointer
				return(t);

			} else {
				// Failure
				return(NULL);
			}
	}




//////////
//
// Locate the indicated tems for the associated thisChars
//
//////
	SBuilder* iGetTemsBuilder(SBuilder* charsBuilder,u32 tipid)
	{
		SChars*		thisChars;


		//////////
		// Grab the thisChars parent
		//////
			thisChars = iiFindOnlyThisChars(charsBuilder, tipid);
			if (thisChars)
			{
				// Return the template
				return(thisChars->tems);

			} else {
				// Failure
				return(NULL);
			}
	}




//////////
//
// Called to render the indicated character
//
//////
	int iRender(SInstance* p, SChars* c, s32 tnWidth, s32 tnHeight, u32 tlMarkup, u32 tlBold, u32 tlItalic, u32 tlUnderline, u32 tlStrikethrough, s8* tcBitmapPathname, u32 tnHwndParent, s32 tnX, s32 tnY)
	{
		SHwnd*	h;
		SHwnd	hData;
		RECT	lrc;


		//////////
		// Determine where we will update our bitmap
		//////
			if (tnHwndParent != 0)
			{
				// Find the existing hwnd, or create a new one
				h = iFindOrCreateHwnd(p->hwnds, tnHwndParent, tnX, tnY, tnWidth, tnHeight);

			} else {
				// Create a pseudo one
				h = &hData;

				// Initialize it
				memset(&hData, 0, sizeof(hData));

				// Populate it manually
				hData.rowWidth				= iComputeRowWidth(tnWidth);

				hData.bi.biSize				= sizeof(hData.bi);
				hData.bi.biWidth			= tnWidth;
				hData.bi.biHeight			= tnHeight;
				hData.bi.biPlanes			= 1;
				hData.bi.biBitCount			= 24;
				hData.bi.biXPelsPerMeter	= 3270;
				hData.bi.biYPelsPerMeter	= 3270;
				hData.bi.biSizeImage		= hData.rowWidth * tnHeight;

				hData.bh.bfType				= 'MB';
				hData.bh.bfOffBits			= sizeof(hData.bh) + sizeof(hData.bi);
				hData.bh.bfSize				= hData.bh.bfOffBits + hData.bi.biSizeImage;

				// Now the character can be rendered with this information
				hData.bd					= (SBGR*)malloc(hData.bi.biSizeImage);
			}


		//////////
		// Render the character
		//////
			SetRect(&lrc, 0, 0, h->w, h->h);
			if (p->activeChar < 0)
			{
				// No valid character has been specified
				FillRect(h->hdc, &lrc, (HBRUSH)GetStockObject(GRAY_BRUSH));

			} else {
				// An active character exists, render it
				if (tlMarkup != 0)		FillRect(h->hdc, &lrc, (HBRUSH)GetStockObject(DKGRAY_BRUSH));
				else					FillRect(h->hdc, &lrc, (HBRUSH)GetStockObject(WHITE_BRUSH));

				// Render the splines with markup lines
				iRenderSplines(p, h, c, tlMarkup, tlBold, tlItalic, tlUnderline, tlStrikethrough);

				// Render the markup
				if (tlMarkup != 0)
					iRenderMarkup(p, h, c);
			}

			// Redraw after the rendering
			if (h->_hwnd)
			{
				SetRect(&lrc, 0, 0, 10000, 10000);
				InvalidateRect(h->hwndParent, &lrc, TRUE);

				SetRect(&lrc, 0, 0, h->w, h->h);
				InvalidateRect(h->hwnd, &lrc, TRUE);	
			}


		// Indicate failure
		return(-1);
	}




//////////
//
// Called to render the indicated splines onto the character
//
//////
	void iRenderSplines(SInstance* p, SHwnd* h, SChars* c, u32 tlMarkup, u32 tlBold, u32 tlItalic, u32 tlUnderline, u32 tlStrikethrough)
	{
		u32			lnI;
		SXYF32		p1Last, p2Last, p3Last;
		SXYF32		p1, p2, p3;
		SSpline*	s;
		SBuilder*	b;
		SBGR		spline;
		SBGR		markup = { 255, 255, 255 };


		//////////
		// For new characters or definitions there may not yet be any splines.  We use a placeholder
		// drawn onto the character until such time
		/////
			if (c->splines->populatedLength <= sizeof(SSpline))		b = placeholder;		// Draw the placeholder
			else													b = c->splines;			// Draw the character splines

			// Determine the color
			if (tlMarkup == 0)
			{
				// It is a final render, black on white
				spline.red = 0;
				spline.grn = 0;
				spline.blu = 0;

			} else {
				// It is a markup render, light gray on black
				spline.red = 128;
				spline.grn = 128;
				spline.blu = 128;
			}


		//////////
		// Iterate through each spline
		//////
			for (lnI = 0; lnI < b->populatedLength; lnI += sizeof(SSpline))
			{
				// Grab the pointer
				s = (SSpline*)(b->data + lnI);


				//////////
				// Render this spline onto the bitmap
				//////
					// Left, middle, right
					iSetPoint(&p1,	s->ox + (s->lr * cos(s->ot + s->lt)),	s->oy + (s->lr * sin(s->ot + s->lt)));
					iSetPoint(&p2,	s->ox,									s->oy);
					iSetPoint(&p3,	s->ox + (s->rr * cos(s->ot + s->rt)),	s->oy + (s->rr * sin(s->ot + s->rt)));

					// Connect the last points to the new points
					if (!s->lPenDown)
					{
						// Draw each connecting line if it's not the first stroke
						iFillQuad(h, &p1Last, &p1, &p2, &p2Last, spline);
						iFillQuad(h, &p2Last, &p2, &p3, &p3Last, spline);
					}


				//////////
				// Setup for the next stroke
				//////
					iCopyPoint(&p1Last, &p1);
					iCopyPoint(&p2Last, &p2);
					iCopyPoint(&p3Last, &p3);
			}


		//////////
		// Overlay markup
		//////
			if (tlMarkup != 0)
			{
				for (lnI = 0; lnI < b->populatedLength; lnI += sizeof(SSpline))
				{
					// Grab the pointer
					s = (SSpline*)(b->data + lnI);


					//////////
					// Render this spline onto the bitmap
					//////
						// Left, middle, right
						iSetPoint(&p1,	s->ox + (s->lr * cos(s->ot + s->lt)),	s->oy + (s->lr * sin(s->ot + s->lt)));
						iSetPoint(&p2,	s->ox,									s->oy);
						iSetPoint(&p3,	s->ox + (s->rr * cos(s->ot + s->rt)),	s->oy + (s->rr * sin(s->ot + s->rt)));

						// Connect the last points to the new points
						if (!s->lPenDown)
						{
							// Connect left, right as markup lines
							iDrawLine(h, &p1, &p1Last, markup);
							iDrawLine(h, &p3, &p3Last, markup);
						}

						// Connect left, middle, right as markup lines
						iDrawLine(h, &p1, &p2, markup);
						iDrawLine(h, &p2, &p3, markup);
						iDrawPoint(h, &p1, markup);
						iDrawPoint(h, &p2, markup);
						iDrawPoint(h, &p3, markup);


					//////////
					// Setup for the next stroke
					//////
						iCopyPoint(&p1Last, &p1);
						iCopyPoint(&p2Last, &p2);
						iCopyPoint(&p3Last, &p3);
				}
			}
	}

	void iDrawLine(SHwnd* h, SXYF32* p1, SXYF32* p2, SBGR color)
	{
		f32			lfPercent, lfStep, lfRadius, lfCosTheta, lfSinTheta;
		s32			lnX, lnY;
		SLineF32	line;
		SBGR*		lbgr;


		//////////
		// Make sure we're not in a non-draw position
		//////
			if (p1->x == -1.0f && p1->y == -1.0f)
				return;		// Do not draw this point


		//////////
		// Compute the line we'll draw along
		//////
			line.p1.x	= p1->x * (f32)h->w;
			line.p1.y	= p1->y * (f32)h->h;
			line.p2.x	= p2->x * (f32)h->w;
			line.p2.y	= p2->y * (f32)h->h;
			iComputeLine(&line);
			lfCosTheta	= cos(line.theta);
			lfSinTheta	= sin(line.theta);


		//////////
		// Proceed for the number of pixels times sqrt(2)
		//////
			lfStep = 1.0f / (line.length * _SQRT2);
			for (lfPercent = 0.0f; lfPercent < 1.0f; lfPercent += lfStep)
			{
				// Compute the radius for this point
				lfRadius = lfPercent * line.length;

				// Compute this point
				lnX = (s32)(line.p1.x + (lfRadius * lfCosTheta));
				lnY = (s32)(line.p1.y + (lfRadius * lfSinTheta));

				// Render it if it's visible
				if (lnX >= 0 && lnX < h->w && lnY >= 0 && lnY < h->h)
				{
					// Get the pointer
					lbgr = (SBGR*)((s8*)h->bd + (lnY * h->rowWidth) + (lnX * 3));

					// Render it
					lbgr->red	= color.red;
					lbgr->grn	= color.grn;
					lbgr->blu	= color.blu;
				}
			}
	}

	// Draw the point
	void iDrawPoint(SHwnd* h, SXYF32* p1, SBGR color)
	{
		SXYS32	p;


		// Determine the center point
		p.xi = (s32)(p1->x * (f32)h->w);
		p.yi = (s32)(p1->y * (f32)h->h);

		// Draw the circle there
		iDrawHorizontalLineByPixels(h, p.xi-1, p.xi+1, p.yi-2, color);		//   * * *
		iDrawHorizontalLineByPixels(h, p.xi-2, p.xi+2, p.yi-1, color);		// * * * * *
		iDrawHorizontalLineByPixels(h, p.xi-2, p.xi+2, p.yi-0, color);		// * * * * *
		iDrawHorizontalLineByPixels(h, p.xi-2, p.xi+2, p.yi+1, color);		// * * * * * 
		iDrawHorizontalLineByPixels(h, p.xi-1, p.xi+1, p.yi+2, color);		//   * * *
	}

	void iDrawHorizontalLineByPixels(SHwnd* h, s32 x1, s32 x2, s32 y, SBGR color)
	{
		s32		lnX;
		SBGR*	lbgr;


		// Is it out of bounds?
		if (y < 0 || y > h->h)
			return;

		// Get the pointer
		lbgr = (SBGR*)((s8*)h->bd + (y * h->rowWidth) + (x1 * 3));

		// Iterate for every x
		for (lnX = x1; lnX <= x2; lnX++, lbgr++)
		{
			// Is it out of bounds?
			if (lnX >= 0 && lnX < h->w)
			{
				// Render it
				lbgr->red	= color.red;
				lbgr->grn	= color.grn;
				lbgr->blu	= color.blu;
			}
		}
	}

	// Draw p1..p2 along the lines from p1..p4, p2..p3
	void iFillQuad(SHwnd* h, SXYF32* p1, SXYF32* p2, SXYF32* p3, SXYF32* p4, SBGR color)
	{
		f32			lfPercent, lfStep, lfCosThetaP1P4, lfSinThetaP1P4, lfCosThetaP2P3, lfSinThetaP2P3, lfMultiplier;
		SXYF32		lp1, lp2;
		SLineF32	p1p4, p2p3;


		//////////
		// Build our lines from p1..p4, p2..p3
		//////
			// Get our multiplier based on size
			lfMultiplier	= sqrt((f32)h->w * (f32)h->w + (f32)h->h * (f32)h->h) * _SQRT2;

			// p1..p4
			p1p4.p1.x	= p1->x;
			p1p4.p1.y	= p1->y;
			p1p4.p2.x	= p4->x;
			p1p4.p2.y	= p4->y;
			iComputeLine(&p1p4);
			lfCosThetaP1P4	= cos(p1p4.theta);
			lfSinThetaP1P4	= sin(p1p4.theta);

			// p2..p3
			p2p3.p1.x	= p2->x;
			p2p3.p1.y	= p2->y;
			p2p3.p2.x	= p3->x;
			p2p3.p2.y	= p3->y;
			iComputeLine(&p2p3);
			lfCosThetaP2P3		= cos(p2p3.theta);
			lfSinThetaP2P3		= sin(p2p3.theta);


		//////////
		// Iterate by sqrt(2) times the maximum line length
		//////
			lfStep = 1.0f / max(p1p4.length * lfMultiplier, p2p3.length * lfMultiplier);
			for (lfPercent = 0.0; lfPercent < 1.0f; lfPercent += lfStep)
			{
				// Compute the points
				lp1.x	= p1p4.p1.x + (lfPercent * p1p4.length * lfCosThetaP1P4);
				lp1.y	= p1p4.p1.y + (lfPercent * p1p4.length * lfSinThetaP1P4);
				lp2.x	= p2p3.p1.x + (lfPercent * p2p3.length * lfCosThetaP2P3);
				lp2.y	= p2p3.p1.y + (lfPercent * p2p3.length * lfSinThetaP2P3);

				// Draw this line
				iDrawLine(h, &lp1, &lp2, color);
			}
	}

	void iSetPoint(SXYF32* p, f32 x, f32 y)
	{
		p->x = x;
		p->y = y;
	}

	void iCopyPoint(SXYF32* pDst, SXYF32* pSrc)
	{
		pDst->x = pSrc->x;
		pDst->y = pSrc->y;
	}




//////////
//
// Called to render the markup data onto the character
//
//////
	void iRenderMarkup(SInstance* p, SHwnd* h, SChars* c)
	{
		s32			lnX, lnY;
		u32			lnI;
		STems*		t;
		SBGR*		lbgr;
		SBGR		color = { 22, 222, 22 };


		//////////
		// Iterate through each spline
		//////
			for (lnI = 0; lnI < c->tems->populatedLength; lnI += sizeof(STems))
			{
				// Grab the pointer
				t = (STems*)(c->tems->data + lnI);

				// Render this template onto the bitmap
				lnX = (s32)(t->fx * (f32)h->w);
				lnY = (s32)(t->fy * (f32)h->h);

				// Determine the offset
				if (lnX >= 0 && lnX < h->w && lnY >= 0 && lnY < h->h)
				{
					// Get the pointer
					lbgr = (SBGR*)((s8*)h->bd + (lnY * h->rowWidth) + (lnX * 3));

					// Render it
					lbgr->red	= color.red;
					lbgr->grn	= color.grn;
					lbgr->blu	= color.blu;
				}
			}
	}




//////////
//
// Called to create a new window, or to reuse an existing window, which is for rendering displayed
// items for preview or examination.
//
//////
	SHwnd* iFindOnlyHwndByHwnd(SBuilder* hwnds, u32 tnHwndParent, u32 tnHwnd)
	{
		u32		lnI;
		SHwnd*	h;


		//////////
		// See if the existing item exists
		//////
			for (lnI = 0; lnI < hwnds->populatedLength; lnI += sizeof(SHwnd))
			{
				// Grab this pointer
				h = (SHwnd*)(hwnds->data + lnI);

				// See if it's a match
				if (h->_hwndParent == tnHwndParent && h->_hwnd == tnHwnd)
				{
					// It's a match
					return(h);
				}
			}
			// If we get here, it wasn't found
			return(NULL);
	}

	SHwnd* iFindOnlyHwnd(SBuilder* hwnds, u32 tnHwndParent, s32 tnX, s32 tnY, s32 tnWidth, s32 tnHeight)
	{
		u32		lnI;
		SHwnd*	h;


		//////////
		// See if the existing item exists
		//////
			for (lnI = 0; lnI < hwnds->populatedLength; lnI += sizeof(SHwnd))
			{
				// Grab this pointer
				h = (SHwnd*)(hwnds->data + lnI);

				// See if it's a match
				if (	h->_hwndParent == tnHwndParent
					&&	h->x == tnX
					&&	h->y == tnY
					&&	h->w == tnWidth
					&&	h->h == tnHeight)
				{
					// It's a match
					return(h);
				}
			}
			// If we get here, it wasn't found
			return(NULL);
	}

	SHwnd* iFindOrCreateHwnd(SBuilder* hwnds, u32 tnHwndParent, s32 tnX, s32 tnY, s32 tnWidth, s32 tnHeight)
	{
		SHwnd*	h;


		//////////
		// See if it already exists
		//////
			h = iFindOnlyHwnd(hwnds, tnHwndParent, tnX, tnY, tnWidth, tnHeight);
			if (h)
				return(h);

		//////////
		// Add it
		//////
			h = (SHwnd*)builder_allocateBytes(hwnds, sizeof(SHwnd));
			if (h)
			{
				// Initialize it
				memset(h, 0, sizeof(SHwnd));

				// Populate it
				h->_hwndParent			= tnHwndParent;
				h->x					= tnX;
				h->y					= tnY;
				h->w					= tnWidth;
				h->h					= tnHeight;
				h->rowWidth				= iComputeRowWidth(tnWidth);

				// Bitmap info
				h->bi.biSize			= sizeof(h->bi);
				h->bi.biWidth			= tnWidth;
				h->bi.biHeight			= tnHeight;
				h->bi.biPlanes			= 1;
				h->bi.biBitCount		= 24;
				h->bi.biXPelsPerMeter	= 3270;
				h->bi.biYPelsPerMeter	= 3270;
				h->bi.biSizeImage		= h->rowWidth * tnHeight;

				// Bitmap header
				h->bh.bfType			= 'MB';
				h->bh.bfOffBits			= sizeof(h->bh) + sizeof(h->bi);
				h->bh.bfSize			= h->bh.bfOffBits + h->bi.biSizeImage;

				// Create the window
				h->_hwnd				= iCreateWindow(h);
			}
			// Return our pointer
			return(h);
	}




//////////
//
// Called to create a window of the indicated size, and setup the bitmap and DibSection bd bits.
//
//////
	u32 iCreateWindow(SHwnd* h)
	{
		ATOM			atom;
		WNDCLASSEXA		classa;
		RECT			lrc;


		//////////
		// Register the class if need be
		//////
			if (!GetClassInfoExA(ghInstance, cgcPreviewWindowClass, &classa))
			{
				// Initialize
				memset(&classa, 0, sizeof(classa));

				// Populate
				classa.cbSize				= sizeof(WNDCLASSEXA);
				classa.hInstance			= ghInstance;
				classa.style				= CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
				classa.lpszClassName		= cgcPreviewWindowClass;
				classa.lpfnWndProc			= &iWindowProcCallback;

				// Register
				atom = RegisterClassExA(&classa);
				if (!atom)
					return(0);		// Failure
			}
		


		//////////
		// Create the window
		//////
			h->hwnd = CreateWindowA(cgcPreviewWindowClass, NULL, WS_CHILD, h->x, h->y, h->w, h->h, h->hwndParent, NULL, ghInstance, (LPVOID)h);
			if (h->_hwnd)
			{
				// Create a DIB Section for accessing this window's bits
				SetRect(&h->rc, h->x, h->y, (h->x + h->w), (h->y + h->h));
				h->hdc	= CreateCompatibleDC(GetDC(h->hwnd));
				h->hbmp	= CreateDIBSection(h->hdc, (BITMAPINFO*)&h->bi, DIB_RGB_COLORS, (void**)&h->bd, NULL, 0);
				SelectObject(h->hdc, h->hbmp);

				// Make it initially gray
				SetRect(&lrc, 0, 0, h->w, h->h);
				FillRect(h->hdc, &lrc, (HBRUSH)GetStockObject(GRAY_BRUSH));
				InvalidateRect(h->hwnd, NULL, FALSE);

				// Make it visible
				ShowWindow(h->hwnd, SW_SHOW);

			} else {
				int error = GetLastError();
				_asm int 3;
			}
			return(h->_hwnd);
	}




//////////
//
// Callback for the window
//
//////
	LRESULT CALLBACK iWindowProcCallback(HWND hwnd, UINT m, WPARAM w, LPARAM l)
	{
		u32				lnI;
		PAINTSTRUCT		ps;
		HDC				lhdc;
		union {
			HWND		thisHwnd;
			u32			_thisHwnd;
		};
		union {
			HWND		hwndParent;
			u32			_hwndParent;
		};
		SHwnd*			h;
		SInstance*		s;


		thisHwnd = hwnd;
		switch (m)
		{
			// Redraw the window
			case WM_PAINT:
				// Iterate through each window to see which one this is
				hwndParent	= GetParent(hwnd);
				for (lnI = 0; lnI < instances->populatedLength; lnI += sizeof(SInstance))
				{
					// Grab the pointer
					s = (SInstance*)(instances->data + lnI);

					// See if we're found on this instance
					h = iFindOnlyHwndByHwnd(s->hwnds, _hwndParent, _thisHwnd);
					if (h)
					{
						// Paint it
						lhdc = BeginPaint(hwnd, &ps);
						BitBlt(lhdc, 0, 0, h->w, h->h, h->hdc, 0, 0, SRCCOPY);
						EndPaint(hwnd, &ps);
						// All done

						// Indicate to Windows that we processed it
						return 0;
					}
				}
				// If we get here, we are not processing this message any longer
				break;
		}

		// Call Windows' default procedure handler
		return(DefWindowProc(hwnd, m, w, l));
	}




//////////
//
// Called to compute the midpoint, slope, and perpendicular slope of a line
//
//////
	void iComputeLine(SLineF32* line)
	{
		// Midpoint = (x2-x1)/2, (y2-y1)/2
		line->mid.x			= (line->p1.x + line->p2.x) / 2.0f;
		line->mid.y			= (line->p1.y + line->p2.y) / 2.0f;
		line->delta.x		= line->p2.x - line->p1.x;
		line->delta.y		= line->p2.y - line->p1.y;
		line->theta			= iAdjustTheta(atan2(line->delta.y, line->delta.x));
		line->length		= sqrt(line->delta.x*line->delta.x + line->delta.y*line->delta.y);

		// Slope = rise over run
		line->m				= line->delta.y / ((line->delta.x == 0.0f) ? 0.000001f : line->delta.x);
		// Perpendicular slope = -1/m
		line->mp			= -1.0f / ((line->m == 0.0f) ? 0.000001f : line->m);

		// Integer roundings if need be
		// Start
		line->p1i.xi	= (s32)line->p1.x;
		line->p1i.yi	= (s32)line->p1.y;
		// End
		line->p2i.xi	= (s32)line->p2.x;
		line->p2i.yi	= (s32)line->p2.y;

		// Compute the quadrants if need be
		// Quads 1..4
		line->p1_quad	= iComputeQuad(&line->p1);
		line->p2_quad	= iComputeQuad(&line->p2);
	}




//////////
//
// Called to adjust theta into the range 0..2pi
//
//////
	f32 iAdjustTheta(f32 tfTheta)
	{
		// Validate theta is positive
		while (tfTheta < 0.0f)
			tfTheta += _2PI;

		// Validate theta is 0..2pi
		while (tfTheta > _2PI)
			tfTheta -= _2PI;

		return(tfTheta);
	}




//////////
//
// Returns the quadrant for the indicated point
//
//////
	s32 iComputeQuad(SXYF32* p)
	{
		if (p->x >= 0.0)
		{
			// Either 1 or 4
			if (p->y >= 0.0)		return(1);		// X is positive, Y is positive
			else					return(4);		// X is positive, Y is negative

		} else {
			// Either 2 or 3
			if (p->y >= 0.0)		return(2);		// X is negative, Y is positive
			else					return(3);		// X is negative, Y is negative
		}
	}
