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




//////////
//
// Miscellaneous functions
//
//////
	void iSetPoint(SXy_f64* p, f64 x, f64 y)
	{
		p->x = x;
		p->y = y;
	}

	void iCopyPoint(SXy_f64* pDst, SXy_f64* pSrc)
	{
		pDst->x = pSrc->x;
		pDst->y = pSrc->y;
	}




/////////
//
// Called from DllMain() one time to initialize the DSF DLL.
//
//////
	void initialize(void)
	{
		f64			lfX, lfY, lfTheta, lfRadius, lfA, lfB, lfV1, lfV2;
		bool		llPenDown;
		HRESULT		hRes;


		//////////
		// Initialize our taskbar class.
		//////
			hRes = OleInitialize(NULL);
			CoCreateInstance(CLSID_TaskbarList, 0, CLSCTX_INPROC_SERVER, IID_ITaskbarList, (void**)&giTaskbar);


		//////////
		// Initialize our global buffers
		/////
			iBuilder_createAndInitialize(&gsRootDsfs, -1);
			iBuilder_createAndInitialize(&gsDefaultChar, -1);


		//////////
		// Build an "i at the cross" for the placeholder (meaning " 'me' at the cross")
		//////
			// Cross
			iDsf_addSpline_fromToLR(gsDefaultChar, true,		0.4075,		0.975,		0.59,		0.975);
			iDsf_addSpline_fromToLR(gsDefaultChar, false,	0.4075,		0.05,		0.59,		0.05);
			iDsf_addSpline_fromToLR(gsDefaultChar, true,		0.045,		0.74,		0.955,		0.74);
			iDsf_addSpline_fromToLR(gsDefaultChar, false,	0.045,		0.62,		0.955,		0.62);

			// "i" leg
			iDsf_addSpline_fromToLR(gsDefaultChar, true,		0.775,		0.435,		0.85,		0.485);
			iDsf_addSpline_fromToLR(gsDefaultChar, false,	0.7825,		0.425,		0.865,		0.47);
			iDsf_addSpline_fromToLR(gsDefaultChar, false,	0.7875,		0.415,		0.8775,		0.45);
			iDsf_addSpline_fromToLR(gsDefaultChar, false,	0.79,		0.405,		0.8875,		0.425);
			iDsf_addSpline_fromToLR(gsDefaultChar, false,	0.7925,		0.3975,		0.8925,		0.405);
			iDsf_addSpline_fromToLR(gsDefaultChar, false,	0.7925,		0.39,		0.895,		0.39);
			iDsf_addSpline_fromToLR(gsDefaultChar, false,	0.7925,		0.14,		0.895,		0.14);
			iDsf_addSpline_fromToLR(gsDefaultChar, false,	0.795,		0.125,		0.895,		0.13);
			iDsf_addSpline_fromToLR(gsDefaultChar, false,	0.80,		0.105,		0.8975,		0.12);
			iDsf_addSpline_fromToLR(gsDefaultChar, false,	0.81,		0.08,		0.90,		0.1125);
			iDsf_addSpline_fromToLR(gsDefaultChar, false,	0.825,		0.06,		0.905,		0.1);
			iDsf_addSpline_fromToLR(gsDefaultChar, false,	0.8375,		0.0425,		0.915,		0.095);

			// "i" dot
			lfX			= 0.765;
			lfY			= 0.5225;
			lfA			= 0.1325 / 2.0;
			lfB			= 0.0925 / 2.0;
			llPenDown	= true;
			for (lfTheta = _PI / 2000.0; lfTheta < _PI; lfTheta += _PI / 8.0)
			{
				// Given:  a=major, b=minor, r=radius
				//         r = (a*b) / sqrt(b*cos(theta)^2 + a*sin(theta)^2)
				lfV1		= lfB * cos(lfTheta);
				lfV2		= lfA * sin(lfTheta);
				lfRadius	= (lfA * lfB) / sqrt(lfV1*lfV1 + lfV2*lfV2);
				iDsf_addSpline_centerThetaRadiusLR(gsDefaultChar, llPenDown, lfX, lfY, lfRadius, lfTheta, iDsf_adjustTheta(_2PI - lfTheta));
				llPenDown = false;
			}

			// Final spline
			lfTheta		= _PI - (_PI / 2000.0);
			lfV1		= lfB * cos(lfTheta);
			lfV2		= lfA * sin(lfTheta);
			lfRadius	= (lfA * lfB) / sqrt(lfV1*lfV1 + lfV2*lfV2);
			iDsf_addSpline_centerThetaRadiusLR(gsDefaultChar, llPenDown, lfX, lfY, lfRadius, lfTheta, iDsf_adjustTheta(_2PI - lfTheta));
	}




//////////
//
// Adds a new spline to the builder, computing its components based on a straight line from L to R.
//
//////
	SDsf_spline* iDsf_addSpline_fromToLR(SBuilder* b, bool tlPenDown, f64 tfXL, f64 tfYL, f64 tfXR, f64 tfYR)
	{
		SDsf_line_f64	line;
		SDsf_spline*	s;


		//////////
		// Compute the line
		//////
			line.p1.x	= tfXL;
			line.p1.y	= tfYL;
			line.p2.x	= tfXR;
			line.p2.y	= tfYR;
			iDsf_compute_line(&line);


		//////////
		// Add the midpoint as the spline, and use the slope of the line to determine the rotation.
		//////
			s = (SDsf_spline*)iBuilder_allocateBytes(b, sizeof(SDsf_spline));
			if (s)
			{
				// Initialize everything
				memset(s, 0, sizeof(SDsf_spline));

				// Populate
				s->ox	= line.mid.x;
				s->oy	= line.mid.y;
				s->ot	= line.theta;

				// Indicate the right and left side length (left and right theta is 0)
				s->lr	= line.length / 2.0f;
				s->lt	= _PI;
				s->rr	= s->lr;

//				s->tlLSelected	= true;
//				s->tlOSelected	= true;
				s->tlRSelected	= true;

				// Does this start a new pen stroke?
				s->lPenDown = tlPenDown;
			}
			return(s);
	}




//////////
//
// Adds a new spline to the builder, computing from the indicated x,y center, given a radius and
// two angles, first for L, then for R.  The line runs horizontally, which means from 0..1, which
// is from left to right in our system, as per the standard Quad 1 X,Y coordinate system.
//
//////
	SDsf_spline* iDsf_addSpline_centerThetaRadiusLR(SBuilder* b, bool tlPenDown, f64 tfX, f64 tfY, f64 tfRadius, f64 tfThetaL, f64 tfThetaR)
	{
		SDsf_spline* s;


		//////////
		// Add the midpoint as the spline, and use the slope of the line to determine the rotation.
		//////
			s = (SDsf_spline*)iBuilder_allocateBytes(b, sizeof(SDsf_spline));
			if (s)
			{
				// Initialize everything
				memset(s, 0, sizeof(SDsf_spline));

				// Populate
				s->ox	= tfX;
				s->oy	= tfY;

				// Indicate the right and left side length (left and right theta is 0)
				s->lr	= tfRadius;
				s->lt	= tfThetaL;
				s->rr	= tfRadius;
				s->rt	= tfThetaR;

// 				s->tlLSelected	= true;
// 				s->tlOSelected	= true;
				s->tlRSelected	= true;

				// Does this start a new pen stroke?
				s->lPenDown = tlPenDown;
			}
			return(s);
	}




//////////
//
// Called to verify if the indicated handle is valid
//
//////
	SDsf* iDsf_getInstance(u32 tnHandle, bool* tlValid)
	{
		union {
			u32		_p;
			SDsf*	p;
		};


		//////////
		// Make sure our environment is sane, and if so that the handle is valid
		//////
			_p = tnHandle;

			// Is it a pointer?
			if (p)
			{
				// Is it in range?
				if (_p >= gsRootDsfs->_data && _p <= gsRootDsfs->_data + gsRootDsfs->populatedLength)
				{
					// Is it identical?
					if (_memicmp(p->id, cgcDsfBrand, sizeof(p->id)) == 0 && p->id_size == sizeof(SDsf))
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
	SDsf_spline* iDsf_find_splineInstance(SBuilder* charsBuilder, u32 tnIid, u8 tcType, u32 tiOrder, u32 tiLnkId, u32 tiLnkOrder)
	{
		SDsf_chars*		thisChar;
		SBuilder*	thisSplineBuilder;


		//////////
		// Make sure our environment is sane
		//////
			if (charsBuilder && charsBuilder->data)
			{
				// Grab that builder
				thisChar = iiDsf_findOrCreate_thisChars(charsBuilder, tnIid);
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
						return(iDsf_find_splineInstance_SD(thisSplineBuilder, tnIid, tiOrder, true));


					case 'D':
					case 'd':
						// It's the same as a spline, but the definition must be an item above 255, and it's
						// not part of a character, but rather just a segment to be used by characters.
						// We search by tnIid and tiOrder
						if (tnIid <= 255)
							return(NULL);		// Error

						// Search for (and add it if need be)
						return(iDsf_find_splineInstance_SD(thisSplineBuilder, tnIid, tiOrder, true));


					case 'R':
					case 'r':
						// It's a reference. The reference must refer to an item above 255, per tiLnkId
						// We search by tnIid, tiOrder, and tiLnkId
						if (tnIid < 256)
							return(NULL);		// Error

						// Search for (and add it if need be)
						return(iDsf_find_splineInstance_R(thisSplineBuilder, tnIid, tiOrder, tiLnkId, true));


					case 'L':
					case 'l':
						// It's a link. The reference can refer to any item, but must include the tiLnkId and tiLnkOrder
						// We search by tnIid, tiOrder, tiLnkId, and tiLnkOrder

						// Search for (and add it if need be)
						return(iDsf_find_splineInstance_L(thisSplineBuilder, tnIid, tiOrder, tiLnkId, tiLnkOrder, true));

				}
			}


		// If we get here, not found
		return(NULL);
	}

	SDsf_chars* iiDsf_findOrCreate_thisChars(SBuilder* charsBuilder, u32 tnIid)
	{
		u32			lnI, lnStart, lnEnd;
		SDsf_chars*		thisChar;


		// See if there's already room for this item
		if (charsBuilder->populatedLength < tnIid * sizeof(SDsf_chars))
		{
			// We have to make room for it
			lnStart = (charsBuilder->populatedLength / sizeof(SDsf_chars));
			lnEnd	= tnIid * sizeof(SDsf_chars);
			for (lnI = lnStart; lnI <= lnEnd; lnI += sizeof(SDsf_chars))
			{
				// Grab the pointer
				thisChar = (SDsf_chars*)iBuilder_allocateBytes(charsBuilder, sizeof(SDsf_chars));

				// Initialize it
				memset(thisChar, 0, sizeof(SDsf_chars));

				// Create new builders for it
				iBuilder_createAndInitialize(&thisChar->splines,		-1);
				iBuilder_createAndInitialize(&thisChar->temsRaw,		-1);
				iBuilder_createAndInitialize(&thisChar->tems,		-1);
				iBuilder_createAndInitialize(&thisChar->temsLines,	-1);
			}
		}


		//////////
		// Return the builder
		//////
			return(iiDsf_findOnly_thisChars(charsBuilder, tnIid));
	}

	SDsf_chars* iiDsf_findOnly_thisChars(SBuilder* charsBuilder, u32 tnIid)
	{
		if (charsBuilder->populatedLength >= tnIid * sizeof(SDsf_chars))
		{
			// There is enough room for this character to exist
			return((SDsf_chars*)(charsBuilder->data + (tnIid * sizeof(SDsf_chars))));

		} else {
			// Something's awry
			return(NULL);
		}
	}

	SDsf_spline* iDsf_find_splineInstance_SD(SBuilder* thisSplineBuilder, u32 tnIid, u32 tiOrder, bool tlAddIfNotFound)
	{
		u32			lnI;
		SDsf_spline*	s;


		//////////
		// Make sure our environment is sane
		//////
			if (!thisSplineBuilder)
				return(NULL);


		//////////
		// Search for it
		//////
			for (lnI = 0; lnI < thisSplineBuilder->populatedLength; lnI += sizeof(SDsf_spline))
			{
				// Grab the pointer
				s = (SDsf_spline*)(thisSplineBuilder->data + lnI);

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
				return((SDsf_spline*)iBuilder_allocateBytes(thisSplineBuilder, sizeof(SDsf_spline)));

			} else {
				// 
				return(NULL);
			}
	}

	SDsf_spline* iDsf_find_splineInstance_R(SBuilder* thisSplineBuilder, u32 tnIid, u32 tiOrder, u32 tiLnkId, bool tlAddIfNotFound)
	{
		u32			lnI;
		SDsf_spline*	s;


		//////////
		// Make sure our environment is sane
		//////
			if (thisSplineBuilder)
				return(NULL);


		//////////
		// Search for it
		//////
			for (lnI = 0; lnI < thisSplineBuilder->populatedLength; lnI += sizeof(SDsf_spline))
			{
				// Grab the pointer
				s = (SDsf_spline*)(thisSplineBuilder->data + lnI);

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
				return((SDsf_spline*)iBuilder_allocateBytes(thisSplineBuilder, sizeof(SDsf_spline)));

			} else {
				// 
				return(NULL);
			}
	}

	SDsf_spline* iDsf_find_splineInstance_L(SBuilder* thisSplineBuilder, u32 tnIid, u32 tiOrder, u32 tiLnkId, u32 tiLnkOrder, bool tlAddIfNotFound)
	{
		u32			lnI;
		SDsf_spline*	s;


		//////////
		// Make sure our environment is sane
		//////
			if (thisSplineBuilder)
				return(NULL);


		//////////
		// Search for it
		//////
			for (lnI = 0; lnI < thisSplineBuilder->populatedLength; lnI += sizeof(SDsf_spline))
			{
				// Grab the pointer
				s = (SDsf_spline*)(thisSplineBuilder->data + lnI);

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
				return((SDsf_spline*)iBuilder_allocateBytes(thisSplineBuilder, sizeof(SDsf_spline)));

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
	SDsf_refs* iDsf_find_refsInstance(SBuilder* refs, u8 tcType, s8* tcDesc40)
	{
		s32		lnI, lnMaxCount;
		SDsf_refs*	r;


		//////////
		// Make sure our environment is sane
		//////
			if (refs && refs->data && refs->populatedLength >= sizeof(SDsf_refs))
			{
				// Get our starting and ending points
				lnMaxCount	= refs->populatedLength / sizeof(SDsf_refs);
				r			= (SDsf_refs*)refs->data;

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
	SDsf_tems* iDsf_create_newTemsEntry(SBuilder* charsBuilder, u32 tipid)
	{
		SDsf_chars*		thisChars;
		SDsf_tems*		t;


		//////////
		// Grab the thisChars parent
		//////
			thisChars = iiDsf_findOrCreate_thisChars(charsBuilder, tipid);
			if (thisChars)
			{
				// Allocate and return the new template
				t = (SDsf_tems*)iBuilder_allocateBytes(thisChars->temsRaw, sizeof(SDsf_tems));

				// Initialize the memory
				if (t)
					memset(t, 0, sizeof(SDsf_tems));

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
	SBuilder* iDsf_get_tems_rawBuilder(SBuilder* charsBuilder,u32 tipid)
	{
		SDsf_chars*		thisChars;


		//////////
		// Grab the thisChars parent
		//////
			thisChars = iiDsf_findOnly_thisChars(charsBuilder, tipid);
			if (thisChars)
			{
				// Return the template
				return(thisChars->temsRaw);

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
	int iDsf_render(SDsf* dsf, SDsf_hwnd* h, SDsf_chars* c, s32 tnWidth, s32 tnHeight, u32 tnHwndParent, s32 tnX, s32 tnY)
	{
		RECT lrc;


		//////////
		// Render the character window
		//////
			SetRect(&lrc, 0, 0, h->w, h->h);
			if (dsf->activeChar < 0)
			{
				// No valid character has been specified
				FillRect(h->hdc, &lrc, h->backDarkGrayBrush);

			} else {
				// An active character exists, render it
				if (h->markup != 0)
				{
					// Fill with the dark background for markup editing
					FillRect(h->hdc, &lrc, h->backDarkGrayBrush);

					// Render any cues
					if (dsf->cuesUnder)
						iDsf_render_cues(dsf, h, c);

					// Render the splines with markup
					if (dsf->showSplines)
						iDsf_render_splines(dsf, h, c, h->markup, h->bold, h->italic, h->underline, h->strikethrough);

					// Render any cues
					if (!dsf->cuesUnder)
						iDsf_render_cues(dsf, h, c);

					// Render the mouse coordinates
					iDsf_render_mouseCoordinates(dsf, h);

					// Render the mouse overlay for current mouse activity
					iDsf_render_mouseOverlay(dsf, h, c);

				} else {
					// Render final as black text on a white background
					FillRect(h->hdc, &lrc, (HBRUSH)GetStockObject(WHITE_BRUSH));
					iDsf_render_splines(dsf, h, c, h->markup, h->bold, h->italic, h->underline, h->strikethrough);
				}
			}


		//////////
		// 
		//////
			if (dsf->zoomLens)
				iDsf_render_zoomLens(h);


		//////////
		// Invert
		//////
			if (dsf->invert)
				iDsf_invertImage(h);	// Invert the colors


		//////////
		// Redraw after the rendering
		//////
			if (h->_hwnd)
			{
				SetRect(&lrc, 0, 0, h->w, h->h);
				if (IsWindow(h->hwnd))
					InvalidateRect(h->hwnd, &lrc, TRUE);	
			}


		// Indicate the hwnd handle we rendered
		return(h->_hwnd);
	}




//////////
//
// Called to put the mouse coordinates in the upper-right, or lower-right, depending on mouse position
//
//////
	void iDsf_render_mouseCoordinates(SDsf* dsf, SDsf_hwnd* h)
	{
		RECT	lrcX, lrcY;
		s8		bufferX[32];
		s8		bufferY[32];


		// Only draw the coordinates if we're on the area
		if (gMouse.xi >= 0 && gMouse.xi < h->w && gMouse.yi >= 0 && gMouse.yi < h->h)
		{
			// Setup the font
			SelectObject(h->hdc, h->fontXY);
			SetBkMode(h->hdc, TRANSPARENT);
			SetTextColor(h->hdc, RGB(255,255,255));

			// Get our coordinates
			sprintf(bufferX, "X:%6.4lf\0", (f64)gMouse.xi			/ (f64)h->w);
			sprintf(bufferY, "Y:%6.4lf\0", ((f64)(h->h - gMouse.yi) / (f64)h->h));		// Invert mouse Y coordinate for the calculation

			// Find out how big it is
			SetRect(&lrcX, 0, 0, 0, 0);
			SetRect(&lrcY, 0, 0, 0, 0);
			DrawTextA(h->hdc, bufferX, strlen(bufferX), &lrcX, DT_CALCRECT);
			DrawTextA(h->hdc, bufferY, strlen(bufferY), &lrcY, DT_CALCRECT);

			// Determine the actual rendering coordinates at the top
			SetRect(&lrcY, h->w - 3 - (lrcY.right - lrcY.left),			3, h->w - 3,		3 + (lrcY.bottom - lrcY.top));
			SetRect(&lrcX, lrcY.left - 3 - (lrcX.right - lrcX.left),	3, lrcY.left - 3,	3 + (lrcX.bottom - lrcX.top));

			// If the mouse is in this area, move the mouse coordinates
			if (gMouse.xi >= lrcX.left && gMouse.xi < lrcY.right && gMouse.yi >= lrcX.top && gMouse.yi < lrcX.bottom)
			{
				// Move to the bottom
				SetRect(&lrcY, h->w - 3 - (lrcY.right - lrcY.left), h->h - 3 - (lrcY.bottom - lrcY.top), h->w - 3, h->h - 3);
				SetRect(&lrcX, h->w - 3 - (lrcY.right - lrcY.left) - 3 - (lrcX.right - lrcX.left), h->h - 3 - (lrcX.bottom - lrcX.top), lrcY.left - 3, lrcY.bottom);
			}

			// Render
			DrawTextA(h->hdc, bufferX, strlen(bufferX), &lrcX, DT_CENTER | DT_VCENTER | DT_END_ELLIPSIS);
			DrawTextA(h->hdc, bufferY, strlen(bufferY), &lrcY, DT_CENTER | DT_VCENTER | DT_END_ELLIPSIS);
		}
	}




//////////
//
// Called to render any cues
//
//////
	void iDsf_render_cues(SDsf* dsf, SDsf_hwnd* h, SDsf_chars* c)
	{
		if (dsf->grid)				iDsf_render_grid(dsf, h);						// Render the grid if it's enabled
		if (dsf->tems)				iDsf_render_tems(dsf, h, c);

		if (dsf->strikethrough)		iDsf_render_quadH(dsf, h, c, dsf->font.fStrikeTop,	dsf->font.fStrikeBot,	colorStrikethrough);
		if (dsf->underline)			iDsf_render_quadH(dsf, h, c, dsf->font.fUnderTop,	dsf->font.fUnderBot,	colorUnderline);

		if (dsf->ascent)			iDsf_render_cueLineH(dsf, h, c, dsf->font.fAscent,		colorAscent);
		if (dsf->upper)				iDsf_render_cueLineH(dsf, h, c, dsf->font.fUpper,		colorUpper);
		if (dsf->lower)				iDsf_render_cueLineH(dsf, h, c, dsf->font.fLower,		colorLower);
		if (dsf->base)				iDsf_render_cueLineH(dsf, h, c, dsf->font.fBase,		colorBase);
		if (dsf->descent)			iDsf_render_cueLineH(dsf, h, c, dsf->font.fDescent,		colorDescent);
		if (dsf->left)				iDsf_render_cueLineV(dsf, h, c, dsf->font.fLeft,		colorLeft);
		if (dsf->right)				iDsf_render_cueLineV(dsf, h, c, dsf->font.fRight,		colorRight);

		if (dsf->showRefs)			iDsf_render_refs(dsf, h, c);
	}

	void iDsf_render_cueLineH(SDsf* dsf, SDsf_hwnd* h, SDsf_chars* c, f64 tfY, SBgr color)
	{
		iDsf_colorize_horizontalLine_byPixels(dsf, h, c, 0, h->w - 1, (s32)(tfY * h->h), color);
	}

	void iDsf_render_cueLineV(SDsf* dsf, SDsf_hwnd* h, SDsf_chars* c, f64 tfX, SBgr color)
	{
		iDsf_colorize_verticalLine_byPixels(dsf, h, c, 0, h->h - 1, (s32)(tfX * h->w), color);
	}

	void iDsf_render_quadH(SDsf* dsf, SDsf_hwnd* h, SDsf_chars* c, f64 tfTop, f64 tfBottom, SBgr color)
	{
		SXy_f64	p1, p2, p3, p4;


		//////////
		// Make a quad of that size
		//////
			iSetPoint(&p1,	0.0, tfTop);
			iSetPoint(&p2,	1.0, tfTop);
			iSetPoint(&p3,	1.0, tfBottom);
			iSetPoint(&p4,	0.0, tfBottom);


		//////////
		// Rendered p1..p4, p2..p3
		//////
			iDsf_fill_quad_alpha(h, &p1, &p2, &p3, &p4, color, color, color, color, 0.5, 0.5, 0.5, 0.5, gfLinePower);
	}

	// Called to render the mouse atop the current image
	void iDsf_render_mouseOverlay(SDsf* dsf, SDsf_hwnd* h, SDsf_chars* c)
	{
		SXy_s32		p1;
		SDsf_line_f64	line;
		s32			lnX, lnY, lnYLast;
		f64			lfTheta, lfThetaStep, lfA, lfB, lfV1, lfV2, lfX, lfY, lfRadius;
		SBgr		color;


		// Invert the Y mouse coordinates for rendering
		p1.xi = gMouse.xi;
		p1.yi = h->h - gMouse.yi;

		// Do we need to render the select area?
		if (glCtrlKeyDown && !(glMouseLeft || glMouseRight))		color = mousePeeakaheadColor;
		else														color = mouseColor;

		// If the CTRL key is down, compute what would be the closest point, and render that line
		if (glCtrlKeyDown)
		{
			// Compute the closest line to the mouse, but only within a certain radius
			if (iDsf_compute_closestMouseLine(&line))
			{
				// Draw a point at the center of the indicated line
				iDsf_draw_point_large(h, &line.mid, color);
			}
		}

		// Is there a reason to render the rectangles?
		if (glMouseLeft || glMouseRight)
		{
			// The mouse is pressed down, render the select area
			// Render it (we're basically drawing an oval area the mouse will interact with)
			lfRadius	= (f64)iDsf_validate_range(dsf->selectArea, _SELECT_AREA_SMALL, _SELECT_AREA_EXTRA_LARGE, _SELECT_AREA_SMALL);
			lnYLast		= -1;
			lfA			= lfRadius * 1.0;		// A is 100%
			lfB			= lfRadius * 0.7;		// B is 70%, this gives us a 10:7 oval
			lfThetaStep	= _PI / ((f64)gMouseType * 128.0);
			for (lfTheta = 0; lfTheta < _PI_2; lfTheta += lfThetaStep)
			{
				// Compute the X,Y for Quad I, then reflect for lines in Quad2..1, and Quad3..4
				lfV1		= lfB * cos(lfTheta);
				lfV2		= lfA * sin(lfTheta);
				lfRadius	= (lfA*lfB) / sqrt(lfV1*lfV1 + lfV2*lfV2);

				// Compute X and Y given this radius
				lfX			= lfRadius * cos(lfTheta);
				lfY			= lfRadius * sin(lfTheta);

				// Convert to integer
				lnY			= (s32)lfY;
				lnX			= (s32)lfX;

				// If it's changed, draw it
				if (lnY != lnYLast)
				{
					// Draw the mouse indicator there, and perform any operations
					iDsf_colorize_andProcessHorizontalLine_byPixels(dsf, h, c, p1.xi - lnX, p1.xi + lnX, p1.yi + lnY, color);		// Above
					if (lnY != 0)
						iDsf_colorize_andProcessHorizontalLine_byPixels(dsf, h, c, p1.xi - lnX, p1.xi + lnX, p1.yi - lnY, color);	// Below

					lnYLast = lnY;
				}
			}
		}

		if (p1.xi >= 0 && p1.xi < h->w && p1.yi >= 0 && p1.yi < h->h)
		{
			if (dsf->mouseCrosshairX)		iDsf_colorize_horizontalLine_byPixels(dsf, h, c, 0, h->w - 1, p1.yi, mouseColor);		// Horizontal
			if (dsf->mouseCrosshairY)		iDsf_colorize_verticalLine_byPixels(  dsf, h, c, 0, h->h - 1, p1.xi, mouseColor);		// Vertical
		}
	}

	void iDsf_render_refs(SDsf* dsf, SDsf_hwnd* h, SDsf_chars* c)
	{
	}




//////////
//
// Called to render a grid
//
//////
	void iDsf_render_grid(SDsf* dsf, SDsf_hwnd* h)
	{
		f64		lfX, lfY;
		s32		lnX, lnY;
		SBgr*	lbgr;
		SBgr	color;


		//////////
		// Depending on whether or not we're tracking to the grid it's rendered in different colors
		//////
			if (dsf->trackGrid && glMouseLeft)			color = gridTrack;		// Only if tracking, and the mouse is down
			else										color = grid;


		//////////
		// Render a grid line every 5% horizontally
		//////
			for (lfY = 0.05; lfY < 0.99; lfY += 0.05)
			{
				// Determine where this will go
				lbgr = (SBgr*)((s8*)h->bd + ((u32)(lfY * h->h) * h->rowWidth));

				// Render at this X coordinate all the way up and down
				for (lnX = 0; lnX < h->w; lnX++, lbgr++)
				{
					// Render this pixel
					lbgr->red	= color.red;
					lbgr->grn	= color.grn;
					lbgr->blu	= color.blu;
				}
			}


		//////////
		// Render a grid line every 5% vertically
		//////
			for (lfX = 0.05; lfX < 0.99; lfX += 0.05)
			{
				// Determine where this will go
				lbgr = (SBgr*)((s8*)h->bd + ((u32)(lfX * h->w) * 3));

				// Render at this X coordinate all the way up and down
				for (lnY = 0; lnY < h->h; lnY++)
				{
					// Render this pixel
					lbgr->red	= color.red;
					lbgr->grn	= color.grn;
					lbgr->blu	= color.blu;

					// Move for the next row
					lbgr = (SBgr*)((s8*)lbgr + h->rowWidth);
				}
			}
	}




//////////
//
// Called to render the indicated splines onto the character
//
//////
	void iDsf_render_splines(SDsf* dsf, SDsf_hwnd* h, SDsf_chars* c, u32 tlMarkup, u32 tlBold, u32 tlItalic, u32 tlUnderline, u32 tlStrikethrough)
	{
		u32			lnI, lnJ, lnSplineNumber, lnSplineCount;
		SXy_f64		prLast, poLast, plLast;
		SXy_f64		pr, po, pl;
		SDsf_line_f64	line, lineL, lineR, lineLLast, lineRLast, lineLtoLLast, lineRtoRLast;
		SDsf_spline*	s;
		SDsf_spline*	sLast;
		SDsf_spline*	sTest;
		SBuilder*	b;
		SBgr		colorLine;
		SBgr		quad, quadSelected, p1ColorR, p2ColorR, p3ColorR, p4ColorR, p1ColorL, p2ColorL, p3ColorL, p4ColorL;


		//////////
		// For new characters or definitions there may not yet be any splines.  We use a placeholder
		// drawn onto the character until such time
		/////
			//////////
			// Draw a placeholder (used for debugging)
			// b = placeholder;
			/////
			b = c->splines;


		//////////
		// Determine the colors
		//////
			if (tlMarkup == 0)
			{
				// It is a final render, black on white
												quad			= black;
				if (dsf->highlighSelection)		quadSelected	= blackSelected;
				else							quadSelected	= black;

			} else {
				// It is a markup render, gray on black
				if (dsf->splinesType == _SPLINES_FILL)
				{
					// Normal rendering
					quad			= gray;
					quadSelected	= ((dsf->highlighSelection) ? graySelected : gray);

				} else {
					// Outline or LOR rendering
					quad			= background;
					quadSelected	= ((dsf->highlighSelection) ? backgroundSelected : background);
				}
			}

			// Splines
			colorLine = iDsf_setLineColor(dsf);


		//////////
		// Iterate through each spline
		//////
			sLast = NULL;
			for (lnI = 0; lnI < b->populatedLength; lnI += sizeof(SDsf_spline))
			{
				// Grab the pointer
				s = (SDsf_spline*)(b->data + lnI);

				// There are negative values which store meta data
				if (s->iOrder >= 0)
				{
					//////////
					// Compute left, origin/middle, right
					//////
						iDsf_compute_LOR(s, &pl, &po, &pr);


					//////////
					// Connect the last points to the new points
					//////
						if (!s->lPenDown)
						{
							// Colors are determined by their relative point's selected color
							iDsf_compute_quadColors_R(s, sLast, quad, quadSelected, &p1ColorR, &p2ColorR, &p3ColorR, &p4ColorR);
							iDsf_compute_quadColors_L(s, sLast, quad, quadSelected, &p1ColorL, &p2ColorL, &p3ColorL, &p4ColorL);

							// Draw in filled in final mode, or when the user wants to see it in markup mode
							// Lines are drawn p1..p4, p2..p3 using the following form:
							// iFillQuad(h, &p1, &p2, &p3, &p4, p1Color, p2Color, p3Color, p4Color);
							if (tlMarkup == 0 || dsf->splinesType == _SPLINES_FILL)
							{
								iDsf_fill_quad_alpha(h, /*p1*/&poLast, /*p2*/&po, /*p3*/&pr, /*p4*/&prLast, p4ColorR, p3ColorR, p2ColorR, p1ColorR, 1.0, 1.0, 1.0, 1.0, gfLinePower);
								iDsf_fill_quad_alpha(h, /*p1*/&poLast, /*p2*/&po, /*p3*/&pl, /*p4*/&plLast, p1ColorL, p2ColorL, p3ColorL, p4ColorL, 1.0, 1.0, 1.0, 1.0, gfLinePower);
							}
						}


					//////////
					// Setup for the next stroke
					//////
						iCopyPoint(&prLast, &pr);
						iCopyPoint(&poLast, &po);
						iCopyPoint(&plLast, &pl);
						sLast = s;
				}
			}


		//////////
		// Overlay markup drawing
		//////
			if (tlMarkup != 0)
			{
				for (lnI = 0, lnSplineNumber = 0; lnI < b->populatedLength; lnI += sizeof(SDsf_spline))
				{
					// Grab the pointer
					s = (SDsf_spline*)(b->data + lnI);

					// There are negative values which store meta data
					if (s->iOrder >= 0)
					{
						//////////
						// Compute left, origin/middle, right
						//////
							iDsf_compute_LOR(s, &pl, &po, &pr);


						//////////
						// Indicate the spline number
						//////
							if (s->lPenDown)
							{
								// Start of a new stroke, find out how many splines there are in this stroke
								lnSplineNumber	= 0;
								lnSplineCount	= 1;
								for (lnJ = lnI + sizeof(SDsf_spline); lnJ < b->populatedLength; lnJ += sizeof(SDsf_spline))
								{
									// Grab the pointer
									sTest = (SDsf_spline*)(b->data + lnJ);

									// See if it's a new stroke
									if (sTest->lPenDown)
										break;

									// It's not a new stroke yet
									++lnSplineCount;
								}
								// When we get here, lnSplineCount is populated with the number of splines for this stroke
								if (lnSplineCount == 1)
								{
									// Since there's only one spline here, make the border a little more visible
									colorLine = gray;

								} else {
									// Determine the color based on the drawing mode
									colorLine = iDsf_setLineColor(dsf);
								}

							} else {
								// Increase our spline number
								++lnSplineNumber;
							}


						//////////
						// If this is the start of a new stroke, render the indicator
						//////
							if (dsf->showPenDowns)
							{
								//////////
								// For pendown strokes, render the large indicator
								//////
									if (s->lPenDown)
									{
										//////////
										// Pen down stroke
										//////
											iDsf_compute_line_fromTwoPoints(&line, &pl, &pr);				// Compute the line from L to R
											iDsf_draw_penDown(h, &line);									// Draw the pen down flow indicator

										// For the previous stroke, if any, draw the pen up indicator
										if (sLast && !sLast->lPenDown)
										{
											// Pen up stroke
											iDsf_compute_line_fromTwoPoints(&line, &plLast, &prLast);		// Compute the line from the last L to R
											iDsf_draw_penUp(h, &line);									// Draw the pen up flow indicator
										}
									}


								//////////
								// For all splines after the second, render hint arrows
								//////
									if (lnSplineNumber >= 1)
									{
										// Compute the line from L to O and O to R on both the current and the last points
										iDsf_compute_line_fromTwoPoints(&lineL, &pl, &po);
										iDsf_compute_line_fromTwoPoints(&lineR, &po, &pr);
										iDsf_compute_line_fromTwoPoints(&lineLLast, &plLast, &poLast);
										iDsf_compute_line_fromTwoPoints(&lineRLast, &poLast, &prLast);

										// Compute a line from the midpoints forward
										iDsf_compute_line_fromTwoPoints(&lineLtoLLast, &lineLLast.mid, &lineL.mid);
										iDsf_compute_line_fromTwoPoints(&lineRtoRLast, &lineRLast.mid, &lineR.mid);

										// Build quads around the endpoints
										if (lineL.length * (f64)h->w >= 9.0)
											iDsf_render_hint(h, &lineLtoLLast, &lineLtoLLast.p1);			// There's enough room to draw a hint on the left side

										if (lineR.length * (f64)h->w >= 9.0)
											iDsf_render_hint(h, &lineRtoRLast, &lineRtoRLast.p1);			// There's enough room to draw a hint on the right side
									}
							}


						//////////
						// Render this spline onto the bitmap
						//////

							// Connect the last points to the new points
							if (!s->lPenDown)
							{
								// Connect left, right as markup lines
								if (dsf->splinesType == _SPLINES_FILL || dsf->splinesType == _SPLINES_OUTLINE)
								{
									iDsf_draw_line(h, &pr, &prLast, s->tlRSelected ? colorSelected : colorLine, sLast->tlRSelected ? colorSelected : colorLine, gfLinePower);
									iDsf_draw_line(h, &po, &poLast, s->tlOSelected ? colorSelected : colorLine, sLast->tlOSelected ? colorSelected : colorLine, gfLinePower);
									iDsf_draw_line(h, &pl, &plLast, s->tlLSelected ? colorSelected : colorLine, sLast->tlLSelected ? colorSelected : colorLine, gfLinePower);
								}
								iDsf_draw_points(dsf, h, &prLast, &poLast, &plLast, sLast, colorSelected, colorR, colorO, colorL, colorRSelected, colorOSelected, colorLSelected, colorLine);

							} else {
								// Reset the spline count
								lnSplineNumber = 0;
							}

							// Connect left, middle, right as markup lines
							iDsf_draw_line(h, &po, &pr, s->tlOSelected ? colorSelected : colorLine, s->tlRSelected ? colorSelected : colorLine, gfLinePower);
							iDsf_draw_line(h, &po, &pl, s->tlOSelected ? colorSelected : colorLine, s->tlLSelected ? colorSelected : colorLine, gfLinePower);
							iDsf_draw_points(dsf, h, &pr, &po, &pl, s, colorSelected, colorR, colorO, colorL, colorRSelected, colorOSelected, colorLSelected, colorLine);


						//////////
						// Setup for the next stroke
						//////
							iCopyPoint(&prLast, &pr);
							iCopyPoint(&poLast, &po);
							iCopyPoint(&plLast, &pl);
							sLast = s;
					}
				}
			}
	}

	void iDsf_render_hint(SDsf_hwnd* h, SDsf_line_f64* line, SXy_f64* pt)
	{
		SXy_f64		pLeft;
		SXy_f64		pForward;
		SXy_f64		pRight;


		//////////
		// Move the point forward one pixel
		//////
			pt->x	= pt->x + ((1.0 / (f64)h->w)  * cos(line->theta));
			pt->y	= pt->y + ((1.0 / (f64)h->w)  * sin(line->theta));


		//////////
		// Create line moving left, forward, and right from the end of the provided line
		//////
			pLeft.x		= pt->x + ((3.0 / (f64)h->w)  * cos(line->theta - _PI_2));
			pLeft.y		= pt->y + ((3.0 / (f64)h->w)  * sin(line->theta - _PI_2));

			pForward.x	= pt->x + ((6.0 / (f64)h->w)  * cos(line->theta));
			pForward.y	= pt->y + ((6.0 / (f64)h->w)  * sin(line->theta));

			pRight.x	= pt->x + ((3.0 / (f64)h->w)  * cos(line->theta + _PI_2));
			pRight.y	= pt->y + ((3.0 / (f64)h->w)  * sin(line->theta + _PI_2));


		//////////
		// Draw the quad (which is really a triangle. :-))
		//////
			iDsf_fill_quad_alpha(h, &pLeft, &pForward, &pForward, &pRight, strokeDown, strokeDown, strokeDown, strokeDown, 1.0, 1.0, 1.0, 1.0, 2.0);
	}




//////////
//
// Called to render the markup data onto the character
//
//////
	void iDsf_render_tems(SDsf* dsf, SDsf_hwnd* h, SDsf_chars* c)
	{
// 		s32			lnX;
// 		u32			lnI, lnINext, lnTemsCount;
// 		STemsLines*	tl;
// 		STems*		p1;
// 		STems*		p2;
// 		SLineS32	line;
		u32			lnI;
		f64			lfRed, lfGrn, lfBlu, lfGray, lfMGray;
		SXy_s32		point;
		SDsf_tems*		t;
		SBgr*		lbgr;


// Note:  This commented code block was an attempt to overlay using solid areas rather than an outline.
// Note:  It didn't always work correctly due to noise in the incoming outline data.  At some point I'll
//        add smoothing algorithms which correct the noise.  Until then, we'll just use the outline.
// 		//////////
// 		// Do we need to rebuild the overlay information?
// 		//////
// 			if (c->temsLines->populatedLength == 0)
// 			{
// 				// Sort the list of tems
// 				lnTemsCount = c->tems->populatedLength / sizeof(STems);
// 				qsort(c->tems->data, lnTemsCount, sizeof(STems), iiTems_qsortCallback);
// 
// 				// Iterate through each block and grab horizontal line runs in blocks
// 				// Note:  At each horizontal stop there may be one or more pixels side-by-side.
// 				//        If they exist in this way, that grouping is considered to be a single
// 				//        group, and the line data will begin beyond it.
// 				for (lnI = 0; lnI < lnTemsCount; lnI = lnINext)
// 				{
// 					// Grab the next set of line entries for this block
// 					lnINext = iiRenderMarkup_getNextLineSegment(lnI, lnTemsCount, h, (STems*)c->tems->data, &p1, &p2);
// 
// 					// Are we still valid?
// 					if (lnINext < lnTemsCount)
// 					{
// 						//////////
// 						// Allocate space for the temsLines entry
// 						//////
// 							tl = (STemsLines*)builder_allocateBytes(c->temsLines, sizeof(STemsLines));
// 							if (tl)
// 							{
// 								// Store the from and to locations
// 								tl->p1.x	= p1->fx;
// 								tl->p1.y	= p1->fy;
// 								tl->p2.x	= p2->fx;
// 								tl->p2.y	= p2->fy;
// 							}
// 					}
// 				}
// 				// When we get here, we have all of the horizontal runs
// 			}
// 
// 
// 		//////////
// 		// Iterate through each temsLines entry
// 		//////
// 			lfRed = (f64)color.red;
// 			lfGrn = (f64)color.grn;
// 			lfBlu = (f64)color.blu;
// 			for (lnI = 0; lnI < c->temsLines->populatedLength; lnI += sizeof(STemsLines))
// 			{
// 				// Grab the pointer
// 				tl = (STemsLines*)(c->temsLines->data + lnI);
// 
// 				// Render this template onto the bitmap
// 				line.p1i.xi = (s32)(tl->p1.x * (f64)h->w);
// 				line.p1i.yi = (s32)(tl->p1.y * (f64)h->h);
// 				line.p2i.xi = (s32)(tl->p2.x * (f64)h->w);
// 				line.p2i.yi = (s32)(tl->p2.y * (f64)h->h);
// 
// 				// Are we on a visible row?
// 				if (line.p1i.yi >= 0 && line.p1i.yi < h->h)
// 				{
// 					// Get the pointer
// 					lbgr = (SBGR*)((s8*)h->bd + (line.p1i.yi * h->rowWidth) + (line.p1i.xi * 3));
// 
// 					// Determine the offset
// 					for (lnX = line.p1i.xi; lnX <= line.p2i.xi; lnX++, lbgr++)
// 					{
// 						// Are we on a visible column?
// 						if (lnX >= 0 && lnX < h->w)
// 						{
// 							// Compute grayscale
// 							lfGray		= ((0.35 * (f64)lbgr->red) + (0.54 * (f64)lbgr->grn) + (0.11 * (f64)lbgr->blu)) / 255.0;
// 							lfMGray		= 1.0 - lfGray;
// 
// 							// Render it
// 							lbgr->red	= (u8)min((u32)((lfGray * lfRed) + (lfMGray * (f64)lbgr->red)), 255);
// 							lbgr->grn	= (u8)min((u32)((lfGray * lfGrn) + (lfMGray * (f64)lbgr->grn)), 255);
// 							lbgr->blu	= (u8)min((u32)((lfGray * lfBlu) + (lfMGray * (f64)lbgr->blu)), 255);
// 						}
// 					}
// 				}
// 			}


		//////////
		// Iterate through each tems entries and draw the outline
		//////
			lfRed = (f64)colorTems.red;
			lfGrn = (f64)colorTems.grn;
			lfBlu = (f64)colorTems.blu;
			for (lnI = 0; lnI < c->tems->populatedLength; lnI += sizeof(SDsf_tems))
			{
				// Grab the pointer
				t = (SDsf_tems*)(c->tems->data + lnI);

				// Render this template onto the bitmap
				point.xi = (s32)(t->fx * (f64)h->w);
				point.yi = (s32)(t->fy * (f64)h->h);

				// Are we on a visible row?
				if (point.yi >= 0 && point.yi < h->h && point.xi >= 0 && point.xi < h->w)
				{
					// Get the pointer
					lbgr = (SBgr*)((s8*)h->bd + (point.yi * h->rowWidth) + (point.xi * 3));

					// Compute grayscale
					lfGray		= ((0.35 * (f64)lbgr->red) + (0.54 * (f64)lbgr->grn) + (0.11 * (f64)lbgr->blu)) / 255.0;
					lfMGray		= 1.0 - lfGray;

					// Render it
					lbgr->red	= (u8)iDsf_scale_intoRange(min((u32)((lfGray * lfRed) + (lfMGray * (f64)lbgr->red)), 255), 255, 32, 64);
					lbgr->grn	= (u8)iDsf_scale_intoRange(min((u32)((lfGray * lfGrn) + (lfMGray * (f64)lbgr->grn)), 255), 255, 128, 255);
					lbgr->blu	= (u8)iDsf_scale_intoRange(min((u32)((lfGray * lfBlu) + (lfMGray * (f64)lbgr->blu)), 255), 255, 32, 64);
				}
			}
	}

	// Zoom the 32x32 box around the mouse coordinates into a zoom lens overlain either on the
	// upper-left or lower-left (depending on whether or not the mouse is over the default upper-
	// left display area.  Zoom is fixed at 3x.
	void iDsf_render_zoomLens(SDsf_hwnd* h)
	{
		s32		lnX, lnY, lnX2, lnY2, lnXSrc, lnYSrc, lnXDst, lnYDst;
		RECT	lrc;
		SBgr*	lbgrSrc;
		SBgr*	lbgrDst;


		//////////
		// See if the mouse is in this default upper-left area
		//////
			SetRect(&lrc, 0, 0, 96 + 16, 96 + 16);
			if (gMouse.xi >= lrc.left && gMouse.xi < lrc.right && gMouse.yi >= lrc.top && gMouse.yi < lrc.bottom)
				SetRect(&lrc, 0, h->h - 96, 96, h->h);


		//////////
		// Copy the image into the area
		//////
			for (lnY = 0, lnYSrc = gMouse.yi - 16, lnYDst = lrc.top; lnY < 32; lnY++, lnYSrc++, lnYDst += 3)
			{
				// Compute the source pointer for the row
				lbgrSrc = (SBgr*)((s8*)h->bd + ((h->h - lnYSrc - 1) * h->rowWidth) + ((gMouse.xi - 16) * 3));

				// Copy the columns
				for (lnX = 0, lnXSrc = gMouse.xi - 16, lnXDst = lrc.left; lnX < 32; lnX++, lnXSrc++, lnXDst += 3, lbgrSrc++)
				{
					// Repeat for a 3x zoom
					for (lnY2 = 0; lnY2 < 3; lnY2++)
					{
						// Compute the destination for this row
						lbgrDst = (SBgr*)((s8*)h->bd + ((h->h - (lnYDst + lnY2)) * h->rowWidth) + (lnXDst * 3));

						// Repeat 3x for the column
						for (lnX2 = 0; lnX2 < 3; lnX2++, lbgrDst++)
						{
							// See if this is a pixel we can copy
							if (lnXSrc >= 0 && lnXSrc < h->w && lnYSrc >= 0 && lnYSrc < h->h)
							{
								// Copy this pixel
								lbgrDst->red	= (u8)min((u32)lbgrSrc->red + 32, 255);
								lbgrDst->grn	= (u8)min((u32)lbgrSrc->grn + 32, 255);
								lbgrDst->blu	= (u8)min((u32)lbgrSrc->blu + 32, 255);

							} else {
								// Render the edge
								lbgrDst->red	= white.red;
								lbgrDst->grn	= white.grn;
								lbgrDst->blu	= white.blu;
							}
						}
					}
				}
			}
	}

	// Grabs the next line segment as processing through the floans.
	u32 iiDsf_renderMarkup_getNextLineSegment(u32 tnIndex, u32 tnMaxCount, SDsf_hwnd* h, SDsf_tems* root, SDsf_tems** p1, SDsf_tems** p2)
	{
		u32			lnI, lnOffset;
		SDsf_tems*		t;
		SXy_s32		lp1, lp2;


		// Skip past while the pixels are adjacent
		t = root + tnIndex;
		for (lnOffset = 1; tnIndex + lnOffset < tnMaxCount; lnOffset++)
		{
			//////////
			// Are we still on the same row?
			//////
				lp1.yi = iiDsf_renderMarkup_getPoint((t + lnOffset + 0)->fy,		h->h);
				lp2.yi = iiDsf_renderMarkup_getPoint((t + lnOffset - 1)->fy,		h->h);
				if (lp1.yi != lp2.yi)
				{
					// We've passed to another row, we begin again, but from here
					return(iiDsf_renderMarkup_getNextLineSegment(tnIndex + lnOffset, tnMaxCount, h, root, p1, p2));
				}


			//////////
			// Are the pixels not adjacent?
			//////
				lp1.xi = iiDsf_renderMarkup_getPoint((t + lnOffset + 0)->fx,		h->w);
				lp2.xi = iiDsf_renderMarkup_getPoint((t + lnOffset - 1)->fx,		h->w);
				if (lp1.xi > lp2.xi + 1)
					break;		// Yes, they are not adjacent.  We've found the end of the grouping/run.
			

			// If we get here, we keep going because we're still on a side-by-side pixel grouping
		}

		// When we get here, we have found two pixels that are not near each other.
		*p1 = (t + lnOffset - 1);		// Last pixel in the left-side grouping
		*p2 = (t + lnOffset);			// First pixel of the right-side grouping


		//////////
		// To determine how much further we go, we now iterate forward while there are two pixels by each other until there is a gap, or end of this row
		//////
			for (lnI = 1; tnIndex + lnOffset + lnI < tnMaxCount; lnI++)
			{
				lp1.yi = iiDsf_renderMarkup_getPoint((t + lnOffset + lnI + 0)->fy,		h->h);
				lp1.xi = iiDsf_renderMarkup_getPoint((t + lnOffset + lnI + 0)->fx,		h->w);
				lp2.yi = iiDsf_renderMarkup_getPoint((t + lnOffset + lnI - 1)->fy,		h->h);
				lp2.xi = iiDsf_renderMarkup_getPoint((t + lnOffset + lnI - 1)->fx,		h->w);
				if (lp1.yi != lp2.yi || lp2.xi + 1 != lp1.xi)
				{
					lnOffset += (lnI - 1);
					break;
				}
			}


		// Indicate how far we moved
		return(tnIndex + lnOffset + 1);
	}

	s32 iiDsf_renderMarkup_getPoint(f64 tfValue01, s32 tnMultiplier)
	{
		return((s32)(tfValue01 * (f64)tnMultiplier));
	}

	SBgr iDsf_setLineColor(SDsf* dsf)
	{
		if (dsf->splinesType != _SPLINES_FILL)		return(gray);				// They don't want to see it filled in, so make it a little more visible
		else										return(black);				// They want to see it filled in, so it can be black
	}

	// Left, Origin, Right
	void iDsf_compute_LOR(SDsf_spline* s, SXy_f64* pl, SXy_f64* po, SXy_f64* pr)
	{
		// left, origin/middle, right
		iSetPoint(pl,	s->ox + (s->lr * cos(s->ot + s->lt)),	s->oy + (s->lr * sin(s->ot + s->lt)));
		iSetPoint(po,	s->ox,									s->oy);
		iSetPoint(pr,	s->ox + (s->rr * cos(s->ot + s->rt)),	s->oy + (s->rr * sin(s->ot + s->rt)));
	}

	// Order is: prLast..poLast, pr..po, which are quad1from, quad1to, quad2from, quad2to
	// iFillQuad(h, /*p1*/&prLast, /*p2*/&pr, /*p3*/&po, /*p4*/&poLast, p1ColorR, p2ColorR, p3ColorR, p4ColorR);
	void iDsf_compute_quadColors_R(SDsf_spline* s, SDsf_spline* sLast, SBgr quadNormal, SBgr quadSelected, SBgr* p1ColorR, SBgr* p2ColorR, SBgr* p3ColorR, SBgr* p4ColorR)
	{
		*p1ColorR	= ((sLast->tlRSelected)	? quadSelected : quadNormal);
		*p2ColorR	= ((s->tlRSelected)		? quadSelected : quadNormal);
		*p3ColorR	= ((s->tlOSelected)		? quadSelected : quadNormal);
		*p4ColorR	= ((sLast->tlOSelected)	? quadSelected : quadNormal);
	}

	// Order is: poLast..plLast, po..pl, which are quad1from, quad1to, quad2from, quad2to
	// iFillQuad(h, /*p1*/&poLast, /*p2*/&po, /*p3*/&pl, /*p4*/&plLast, quad1fromL, p1ColorL, p2ColorL, p3ColorL, p4ColorL);
	void iDsf_compute_quadColors_L(SDsf_spline* s, SDsf_spline* sLast, SBgr quadNormal, SBgr quadSelected, SBgr* p1ColorL, SBgr* p2ColorL, SBgr* p3ColorL, SBgr* p4ColorL)
	{
		*p1ColorL	= ((sLast->tlOSelected)	? quadSelected : quadNormal);
		*p2ColorL	= ((s->tlOSelected)		? quadSelected : quadNormal);
		*p3ColorL	= ((s->tlLSelected)		? quadSelected : quadNormal);
		*p4ColorL	= ((sLast->tlLSelected)	? quadSelected : quadNormal);
	}

	bool iDsf_compute_closestMouseLine(SDsf_line_f64* line)
	{
		// Find the closest point to the current mouse coordinates

		// Find the closest 20 points to that

		// Determine the slope of every point to every other point

		// Sort the list by slope order

		// Determine the deltas between each item

		// Sort the list by the deltas

		// Using the top 10 deltas, determine the midpoint and average slope and radius

		// Construct a line with that information
		return(false);
	}




//////////
//
// Called to compute the midpoint, slope, and perpendicular slope of a line
//
//////
	void iDsf_compute_line(SDsf_line_f64* line)
	{
		// Midpoint = (x2-x1)/2, (y2-y1)/2
		line->mid.x			= (line->p1.x + line->p2.x) / 2.0f;
		line->mid.y			= (line->p1.y + line->p2.y) / 2.0f;
		line->delta.x		= line->p2.x - line->p1.x;
		line->delta.y		= line->p2.y - line->p1.y;
		line->theta			= iDsf_adjustTheta(atan2(line->delta.y, line->delta.x));
		line->length		= sqrt(line->delta.x*line->delta.x + line->delta.y*line->delta.y);

		// Slope = rise over run
		line->m				= line->delta.y / ((line->delta.x == 0.0) ? 0.0000000000001 : line->delta.x);

		// Perpendicular slope = -1/m
		line->mp			= -1.0 / ((line->m == 0.0) ? 0.0000000000001 : line->m);

		// Integer roundings if need be
		// Start
		line->p1i.xi	= (s32)line->p1.x;
		line->p1i.yi	= (s32)line->p1.y;
		// End
		line->p2i.xi	= (s32)line->p2.x;
		line->p2i.yi	= (s32)line->p2.y;

		// Compute the quadrants if need be
		// Quads 1..4
		line->p1_quad	= iDsf_compute_quad(&line->p1);
		line->p2_quad	= iDsf_compute_quad(&line->p2);
	}

	void iDsf_compute_line_fromTwoPoints(SDsf_line_f64* line, SXy_f64* p1, SXy_f64* p2)
	{
		// p1
		line->p1.x	= p1->x;
		line->p1.y	= p1->y;

		// p2
		line->p2.x	= p2->x;
		line->p2.y	= p2->y;

		// Compute
		iDsf_compute_line(line);
	}

	// Returns the quadrant for the indicated point
	s32 iDsf_compute_quad(SXy_f64* p)
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

	void iDsf_draw_penDown(SDsf_hwnd* h, SDsf_line_f64* line)
	{
		SXy_f64	p1, p2, p3, p4;


		/////////
		// Extend out the points by 5 pixels
		//////
			// L
			line->p1.x        = line->p1.x + ((10.0 / (f64)h->w) * cos(line->theta + _PI));
			line->p1.y        = line->p1.y + ((10.0 / (f64)h->h) * sin(line->theta + _PI));
			// R
			line->p2.x        = line->p2.x + ((10.0 / (f64)h->w) * cos(line->theta));
			line->p2.y        = line->p2.y + ((10.0 / (f64)h->h) * sin(line->theta));
			iDsf_compute_line(line);


		//////////
		// Create a quad extending 10 pixels forward, 5 pixels backward
		//////
			// p1..p4
			p1.x		= line->p1.x + ((10.0 / (f64)h->w) * cos(line->theta - _PI_2));
			p1.y		= line->p1.y + ((10.0 / (f64)h->h) * sin(line->theta - _PI_2));
			p4.x		= line->p1.x + ((5.0  / (f64)h->w) * cos(line->theta + _PI_2));
			p4.y		= line->p1.y + ((5.0  / (f64)h->h) * sin(line->theta + _PI_2));
			// p2..p3
			p2.x		= line->p2.x + ((10.0 / (f64)h->w) * cos(line->theta - _PI_2));
			p2.y		= line->p2.y + ((10.0 / (f64)h->h) * sin(line->theta - _PI_2));
			p3.x		= line->p2.x + ((5.0  / (f64)h->w) * cos(line->theta + _PI_2));
			p3.y		= line->p2.y + ((5.0  / (f64)h->h) * sin(line->theta + _PI_2));


		//////////
		// Fill this quad in using a bluish cue
		//////
			iDsf_fill_quad_alpha(h, &p1, &p2, &p3, &p4, strokeDown, strokeDown, strokeDown, strokeDown, 0.0, 0.0, 1.0, 1.0, 2.0);
	}

	void iDsf_draw_penUp(SDsf_hwnd* h, SDsf_line_f64* line)
	{
		SXy_f64	p1, p2, p3, p4;


		/////////
		// Extend out the points by 5 pixels
		//////
			// L
			line->p1.x        = line->p1.x + ((10.0 / (f64)h->w) * cos(line->theta + _PI));
			line->p1.y        = line->p1.y + ((10.0 / (f64)h->h) * sin(line->theta + _PI));
			// R
			line->p2.x        = line->p2.x + ((10.0 / (f64)h->w) * cos(line->theta));
			line->p2.y        = line->p2.y + ((10.0 / (f64)h->h) * sin(line->theta));
			iDsf_compute_line(line);


		//////////
		// Create a quad extending 10 pixels back
		//////
			// p1..p4
 			p1.x		= line->p1.x + ((10.0 / (f64)h->w) * cos(line->theta + _PI_2));
 			p1.y		= line->p1.y + ((10.0 / (f64)h->h) * sin(line->theta + _PI_2));
			p4.x		= line->p1.x + ((5.0  / (f64)h->w) * cos(line->theta - _PI_2));
			p4.y		= line->p1.y + ((5.0  / (f64)h->h) * sin(line->theta - _PI_2));
			// p2..p3
			p2.x		= line->p2.x + ((10.0 / (f64)h->w) * cos(line->theta + _PI_2));
			p2.y		= line->p2.y + ((10.0 / (f64)h->h) * sin(line->theta + _PI_2));
			p3.x		= line->p2.x + ((5.0  / (f64)h->w) * cos(line->theta - _PI_2));
			p3.y		= line->p2.y + ((5.0  / (f64)h->h) * sin(line->theta - _PI_2));


		//////////
		// Fill this quad in using an orangish cue
		//////
			iDsf_fill_quad_alpha(h, &p1, &p2, &p3, &p4, strokeUp, strokeUp, strokeUp, strokeUp, 0.0, 0.0, 1.0, 1.0, 2.0);
	}

	void iDsf_draw_points(SDsf* dsf, SDsf_hwnd* h, SXy_f64* pr, SXy_f64* po, SXy_f64* pl, SDsf_spline* s, SBgr colorSelected, SBgr colorR, SBgr colorO, SBgr colorL, SBgr colorRSelected, SBgr colorOSelected, SBgr colorLSelected, SBgr colorLine)
	{
		//////////
		// Right
		//////
			if (s->tlRSelected)
			{
				iDsf_draw_point_large(h, pr, colorSelected);
				iDsf_draw_point(h, pr, colorRSelected);

			} else {
				iDsf_draw_point_large(h, pr, colorLine);
				iDsf_draw_point(h, pr, colorR);
			}


		//////////
		// Origin/middle
		//////
			if (s->tlOSelected)
			{
				iDsf_draw_point_large(h, po, colorSelected);
				iDsf_draw_point(h, po, colorOSelected);

			} else {
				iDsf_draw_point_large(h, po, colorLine);
				iDsf_draw_point(h, po, colorO);
			}


		//////////
		// Left
		//////
			if (s->tlLSelected)
			{
				iDsf_draw_point_large(h, pl, colorSelected);
				iDsf_draw_point(h, pl, colorLSelected);

			} else {
				iDsf_draw_point_large(h, pl, colorLine);
				iDsf_draw_point(h, pl, colorL);
			}
	}

	void iDsf_draw_line(SDsf_hwnd* h, SXy_f64* p1, SXy_f64* p2, SBgr colorStart, SBgr colorEnd, f64 tfPower)
	{
		SBgr_af64	colorStartAlp, colorEndAlp;


		//////////
		// Create our 1.0 alpha pseudo colors
		//////
			// start
			colorStartAlp.red	= colorStart.red;
			colorStartAlp.grn	= colorStart.grn;
			colorStartAlp.blu	= colorStart.blu;
			colorStartAlp.falp	= 1.0;

			// end
			colorEndAlp.red	= colorEnd.red;
			colorEndAlp.grn	= colorEnd.grn;
			colorEndAlp.blu	= colorEnd.blu;
			colorEndAlp.falp	= 1.0;


		//////////
		// Draw in the alpha algorithm
		//////
			iDsf_draw_lineAlpha(h, p1, p2, &colorStartAlp, &colorEndAlp, NULL, false, tfPower);
	}

	void iDsf_draw_lineAlpha(SDsf_hwnd* h, SXy_f64* p1, SXy_f64* p2, SBgr_af64* colorStart, SBgr_af64* colorEnd, SBuilder* pointsDrawn, bool tlNoDuplicates, f64 tfPower)
	{
		f64			lfPercent, lfSteps, lfStepInc, lfRadius, lfCosTheta, lfSinTheta;
		f64			lfRed, lfGrn, lfBlu, lfAlp, lfMalp, lfCos4, lfRedDelta, lfGrnDelta,lfBluDelta, lfAlpDelta;
		s32			lnX, lnY, lnXLast, lnYLast;
		SDsf_line_f64	line;
		SBgr*		lbgr;
		u8*			lMastPtr;


		//////////
		// Make sure we're not in a non-draw position
		//////
			if (p1->x == -1.0 && p1->y == -1.0)
				return;		// Do not draw this point


		//////////
		// Compute the line we'll draw along
		//////
			line.p1.x	= p1->x * (f64)h->w;
			line.p1.y	= p1->y * (f64)h->h;
			line.p2.x	= p2->x * (f64)h->w;
			line.p2.y	= p2->y * (f64)h->h;
			iDsf_compute_line(&line);
			lfCosTheta	= cos(line.theta);
			lfSinTheta	= sin(line.theta);


		//////////
		// Compute colors
		//////
			lfSteps		= line.length * _SQRT2;
			lfRedDelta	= (f64)colorEnd->red - (f64)colorStart->red;
			lfGrnDelta	= (f64)colorEnd->grn - (f64)colorStart->grn;
			lfBluDelta	= (f64)colorEnd->blu - (f64)colorStart->blu;
			lfAlpDelta	= colorEnd->falp - colorStart->falp;


		//////////
		// Proceed for the number of pixels times sqrt(2)
		//////
			lfStepInc = 1.0 / lfSteps;
			lnXLast		= -10000;
			lnYLast		= -10000;
			for (lfPercent = 0.0f; lfPercent < 1.0f; lfPercent += lfStepInc)
			{
				// Compute the radius for this point
				lfRadius = lfPercent * line.length;

				// Compute the color
				lfCos4	= 1.0 - pow(cos(lfPercent * _PI_2), tfPower);
				lfRed	= colorStart->red  + (lfRedDelta * lfCos4);
				lfGrn	= colorStart->grn  + (lfGrnDelta * lfCos4);
				lfBlu	= colorStart->blu  + (lfBluDelta * lfCos4);
				lfAlp	= colorStart->falp + (lfAlpDelta * lfCos4);
				lfMalp	= 1.0 - lfAlp;

				// Compute this point
				lnX = (s32)(line.p1.x + (lfRadius * lfCosTheta));
				lnY = (s32)(line.p1.y + (lfRadius * lfSinTheta));

				// Render it if it's visible
				if (lnX >= 0 && lnX < h->w && lnY >= 0 && lnY < h->h && !(lnX == lnXLast && lnY == lnYLast))
				{
					if (tlNoDuplicates || pointsDrawn)
					{
						// Need to see if this has already been drawn first
						lMastPtr = (u8*)(pointsDrawn->data + (lnY * h->w) + lnX);

						// If it's 0, it has not yet been drawn
						if (*lMastPtr == 0)
						{
							// We can draw it
							lbgr		= (SBgr*)((s8*)h->bd + (lnY * h->rowWidth) + (lnX * 3));
							lbgr->red	= (u8)(((f64)lbgr->red * lfMalp) + (lfRed * lfAlp));
							lbgr->grn	= (u8)(((f64)lbgr->grn * lfMalp) + (lfGrn * lfAlp));
							lbgr->blu	= (u8)(((f64)lbgr->blu * lfMalp) + (lfBlu * lfAlp));

							// Mark this bit drawn
							*lMastPtr	= 255;
						}

					} else {
						// Directly render it
						lbgr		= (SBgr*)((s8*)h->bd + (lnY * h->rowWidth) + (lnX * 3));
						lbgr->red	= (u8)(((f64)lbgr->red * lfMalp) + (lfRed * lfAlp));
						lbgr->grn	= (u8)(((f64)lbgr->grn * lfMalp) + (lfGrn * lfAlp));
						lbgr->blu	= (u8)(((f64)lbgr->blu * lfMalp) + (lfBlu * lfAlp));
					}
				}

				// Store the last point we rendered
				lnXLast		= lnX;
				lnYLast		= lnY;
			}
	}

	void iDsf_draw_line_alpha_noDuplicates(SDsf_hwnd* h, SBuilder* pointsDrawn)
	{
		u32				lnI, lnCount;
		s32				lnXLast, lnYLast;
		f64				lfAlp, lfMalp;
		SBgr*			lbgr;
		SDsf_pointsDrawn*	dp;


		//////////
		// Sort the list
		//////
			lnCount = pointsDrawn->populatedLength / sizeof(SDsf_pointsDrawn);
			qsort(pointsDrawn->data, lnCount, sizeof(SDsf_pointsDrawn), iiDsf_SPointsDrawn_qsortCallback);


		//////////
		// Render each point
		//////
			lnXLast = -10000;
			lnYLast = -10000;
			for (lnI = 0; lnI < pointsDrawn->populatedLength; lnI += sizeof(SDsf_pointsDrawn))
			{
				// Grab the pointer
				dp = (SDsf_pointsDrawn*)(pointsDrawn->data + lnI);

				// Render this item
				if (!(dp->pt.xi == lnXLast && dp->pt.yi == lnYLast))
				{
					// Grab the alpha
					lfAlp		= (f64)dp->color.alp / 255.0;
					lfMalp		= 1.0 - lfAlp;

					// Render it
					lbgr		= (SBgr*)((s8*)h->bd + (dp->pt.yi * h->rowWidth) + (dp->pt.xi * 3));
					lbgr->red	= (u8)(((f64)lbgr->red * lfMalp) + ((f64)dp->color.red * lfAlp));
					lbgr->grn	= (u8)(((f64)lbgr->grn * lfMalp) + ((f64)dp->color.grn * lfAlp));
					lbgr->blu	= (u8)(((f64)lbgr->blu * lfMalp) + ((f64)dp->color.blu * lfAlp));

					// Store for the next go so we don't do this point again
					lnXLast = dp->pt.xi;
					lnYLast = dp->pt.yi;
				}
			}
	}

	// Draw the point
	void iDsf_draw_point(SDsf_hwnd* h, SXy_f64* p1, SBgr color)
	{
		SXy_s32	p;


		// Determine the center point
		p.xi = (s32)(p1->x * (f64)h->w);
		p.yi = (s32)(p1->y * (f64)h->h);

		// Draw the circle there
		iDsf_draw_line_horizontal_byPixels(h, p.xi-1, p.xi+1, p.yi-2, color);		//   * * *
		iDsf_draw_line_horizontal_byPixels(h, p.xi-2, p.xi+2, p.yi-1, color);		// * * * * *
		iDsf_draw_line_horizontal_byPixels(h, p.xi-2, p.xi+2, p.yi-0, color);		// * * * * *
		iDsf_draw_line_horizontal_byPixels(h, p.xi-2, p.xi+2, p.yi+1, color);		// * * * * * 
		iDsf_draw_line_horizontal_byPixels(h, p.xi-1, p.xi+1, p.yi+2, color);		//   * * *
	}

	// Draw the small middle
	void iDsf_draw_point_small(SDsf_hwnd* h, SXy_f64* p1, SBgr color)
	{
		SXy_s32	p;


		// Determine the center point
		p.xi = (s32)(p1->x * (f64)h->w);
		p.yi = (s32)(p1->y * (f64)h->h);

		// Draw the circle there
// 		iDrawHorizontalLineByPixels(h, p.xi,	p.xi,	p.yi-1,	color);		//   *
// 		iDrawHorizontalLineByPixels(h, p.xi-1,	p.xi+1,	p.yi-0,	color);		// * * *
// 		iDrawHorizontalLineByPixels(h, p.xi,	p.xi,	p.yi+1,	color);		//   *
		iDsf_draw_line_horizontal_byPixels(h, p.xi,	p.xi,	p.yi,	color);		//   *
	}

	// Draw the point large
	void iDsf_draw_point_large(SDsf_hwnd* h, SXy_f64* p1, SBgr color)
	{
		SXy_s32	p;


		// Determine the center point
		p.xi = (s32)(p1->x * (f64)h->w);
		p.yi = (s32)(p1->y * (f64)h->h);

		// Draw the circle there
		iDsf_draw_line_horizontal_byPixels(h, p.xi-1, p.xi+1, p.yi-3, color);		//     * * *
		iDsf_draw_line_horizontal_byPixels(h, p.xi-2, p.xi+2, p.yi-2, color);		//   * * * * *
		iDsf_draw_line_horizontal_byPixels(h, p.xi-3, p.xi+3, p.yi-1, color);		// * * * * * * *
		iDsf_draw_line_horizontal_byPixels(h, p.xi-3, p.xi+3, p.yi-0, color);		// * * * * * * *
		iDsf_draw_line_horizontal_byPixels(h, p.xi-3, p.xi+3, p.yi+1, color);		// * * * * * * *
		iDsf_draw_line_horizontal_byPixels(h, p.xi-2, p.xi+2, p.yi+2, color);		//   * * * * *
		iDsf_draw_line_horizontal_byPixels(h, p.xi-1, p.xi+1, p.yi+3, color);		//     * * *
	}

	void iDsf_draw_line_horizontal_byPixels(SDsf_hwnd* h, s32 x1, s32 x2, s32 y, SBgr color)
	{
		s32		lnX;
		SBgr*	lbgr;


		// Is it out of bounds?
		if (y < 0 || y > h->h)
			return;

		// Get the pointer
		lbgr = (SBgr*)((s8*)h->bd + (y * h->rowWidth) + (x1 * 3));

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
	void iDsf_fill_quad_alpha(SDsf_hwnd* h, SXy_f64* p1, SXy_f64* p2, SXy_f64* p3, SXy_f64* p4, SBgr p1Color, SBgr p2Color, SBgr p3Color, SBgr p4Color, f64 tfP1Alp, f64 tfP2Alp, f64 tfP3Alp, f64 tfP4Alp, f64 tfPower)
	{
		f64			lfPercent, lfStep, lfStepCount, lfCosThetaP1P4, lfSinThetaP1P4, lfCosThetaP2P3, lfSinThetaP2P3, lfMultiplier;
		SXy_f64		lp1, lp2;
		SDsf_line_f64	p1p4, p2p3;
		bool		llNoAlpha;
		f64			lfRedP1P4Delta, lfGrnP1P4Delta, lfBluP1P4Delta, lfAlpP1P4Delta, lfRedP2P3Delta, lfGrnP2P3Delta, lfBluP2P3Delta, lfAlpP2P3Delta, lfCos4;
		SBgr_af64	colorP1P4, colorP2P3;
		SBuilder*	pointsDrawn;
		s8*			lptr;


		//////////
		// Build our lines from p1..p4, p2..p3
		//////
			// Are we rendering any that are alpha?
			llNoAlpha = false;
			if (tfP1Alp == 1.0 && tfP2Alp == 1.0 && tfP3Alp == 1.0 && tfP4Alp == 1.0)
				llNoAlpha = true;

			// Get our multiplier based on size
			lfMultiplier	= sqrt((f64)h->w * (f64)h->w + (f64)h->h * (f64)h->h) * (_SQRT2 * ((llNoAlpha) ? 1.0 : 2.0));

			// p1..p4
			p1p4.p1.x	= p1->x;
			p1p4.p1.y	= p1->y;
			p1p4.p2.x	= p4->x;
			p1p4.p2.y	= p4->y;
			iDsf_compute_line(&p1p4);
			lfCosThetaP1P4	= cos(p1p4.theta);
			lfSinThetaP1P4	= sin(p1p4.theta);

			// p2..p3
			p2p3.p1.x	= p2->x;
			p2p3.p1.y	= p2->y;
			p2p3.p2.x	= p3->x;
			p2p3.p2.y	= p3->y;
			iDsf_compute_line(&p2p3);
			lfCosThetaP2P3		= cos(p2p3.theta);
			lfSinThetaP2P3		= sin(p2p3.theta);

			// Steps
			lfStepCount	= (max(p1p4.length, p2p3.length) * lfMultiplier);
			lfStep		= 1.0 / lfStepCount;


		//////////
		// Compute the color steps for this rendering
		//////
			// p1..p4
			lfRedP1P4Delta	= (f64)p4Color.red - (f64)p1Color.red;
			lfGrnP1P4Delta	= (f64)p4Color.grn - (f64)p1Color.grn;
			lfBluP1P4Delta	= (f64)p4Color.blu - (f64)p1Color.blu;
			lfAlpP1P4Delta	= tfP4Alp - tfP1Alp;

			// p2..p3
			lfRedP2P3Delta	= (f64)p3Color.red - (f64)p2Color.red;
			lfGrnP2P3Delta	= (f64)p3Color.grn - (f64)p2Color.grn;
			lfBluP2P3Delta	= (f64)p3Color.blu - (f64)p2Color.blu;
			lfAlpP2P3Delta	= tfP3Alp - tfP2Alp;


		//////////
		// Create our points drawn buffer so duplicate points are not rendered
		//////
			if (!llNoAlpha)
			{
				// Allocate a map buffer to indicate which bits have been drawn already
				iBuilder_createAndInitialize(&pointsDrawn, -1);
				lptr = iBuilder_allocateBytes(pointsDrawn, h->w * h->h);
				memset(lptr, 0, h->w * h->h);
			}



		//////////
		// Iterate by sqrt(2) times the maximum line length
		//////
			for (lfPercent = 0.0; lfPercent < 1.0; lfPercent += lfStep)
			{
				//////////
				// Compute the points
				//////
					lp1.x	= p1p4.p1.x + (lfPercent * p1p4.length * lfCosThetaP1P4);
					lp1.y	= p1p4.p1.y + (lfPercent * p1p4.length * lfSinThetaP1P4);
					lp2.x	= p2p3.p1.x + (lfPercent * p2p3.length * lfCosThetaP2P3);
					lp2.y	= p2p3.p1.y + (lfPercent * p2p3.length * lfSinThetaP2P3);


				//////////
				// Compute the color for this leg
				//////
					// Compute the color
					lfCos4	= 1.0 - pow(cos(lfPercent * _PI_2), tfPower);

					// p1..p4
					colorP1P4.red	= p1Color.red  + (u8)(lfRedP1P4Delta * lfCos4);
					colorP1P4.grn	= p1Color.grn  + (u8)(lfGrnP1P4Delta * lfCos4);
					colorP1P4.blu	= p1Color.blu  + (u8)(lfBluP1P4Delta * lfCos4);
					colorP1P4.falp	= tfP1Alp + (lfAlpP1P4Delta * lfCos4);
					// p2..p3
					colorP2P3.red	= p2Color.red  + (u8)(lfRedP2P3Delta * lfCos4);
					colorP2P3.grn	= p2Color.grn  + (u8)(lfGrnP2P3Delta * lfCos4);
					colorP2P3.blu	= p2Color.blu  + (u8)(lfBluP2P3Delta * lfCos4);
					colorP2P3.falp	= tfP2Alp + (lfAlpP2P3Delta * lfCos4);


				//////////
				// Draw this line
				//////
					if (llNoAlpha)		iDsf_draw_lineAlpha(h, &lp1, &lp2, &colorP1P4, &colorP2P3, NULL,			false,	4.0);
					else				iDsf_draw_lineAlpha(h, &lp1, &lp2, &colorP1P4, &colorP2P3, pointsDrawn,	true,	4.0);
			}


		//////////
		// Destroy the points drawn buffer
		//////
			if (!llNoAlpha)
				iBuilder_freeAndRelease(&pointsDrawn);
	}

	void iDsf_colorize_andProcessHorizontalLine_byPixels(SDsf* dsf, SDsf_hwnd* h, SDsf_chars* c, s32 x1, s32 x2, s32 y, SBgr color)
	{
		SXy_f64 ul, lr;


		//////////
		// Make sure the values are in the correct order
		/////
			iDsf_makeSure_lowToHigh_s32(&x1, &x2);


		//////////
		// Colorize it
		//////
			iDsf_colorize_horizontalLine_byPixels(dsf, h, c, x1, x2, y, color);

		//////
		// Process it
		// Scan through this range and see if there are any splines, points, or strokes which need selected
		//////
			// Compute upper-left and lower-right range
			ul.x = (f64)x1                    / (f64)h->w;
			ul.y = ((f64)y  + 0.999999999999) / (f64)h->h;
			lr.x = ((f64)x2 + 0.999999999999) / (f64)h->w;
			lr.y = (f64)y                     / (f64)h->h;

			// Process the selection operation on this range
			iDsf_select_range(dsf, h, c, &lr, &lr);
	}

	void iDsf_colorize_horizontalLine_byPixels(SDsf* dsf, SDsf_hwnd* h, SDsf_chars* c, s32 x1, s32 x2, s32 y, SBgr color)
	{
		s32		lnX;
		f64		lfAlp, lfMalp, lfRed, lfGrn, lfBlu;
		SBgr*	lbgr;


		// Is it out of bounds?
		if (y < 0 || y >= h->h)
			return;

		// Get the pointer
		lbgr = (SBgr*)((s8*)h->bd + (y * h->rowWidth) + (x1 * 3));

		// Get the colors
		lfRed	= (f64)color.red;
		lfGrn	= (f64)color.grn;
		lfBlu	= (f64)color.blu;
		lfAlp	= 0.5;
		lfMalp	= 1.0 - lfAlp;

		// Iterate for every x
		for (lnX = x1; lnX <= x2; lnX++, lbgr++)
		{
			// Is it out of bounds?
			if (lnX >= 0 && lnX < h->w)
			{
				// Colorize it
				lbgr->red	= (u8)iDsf_scale_intoRange((s32)((lfAlp * lfRed) + (lfMalp * (f64)lbgr->red)), 255, 92, 255);
				lbgr->grn	= (u8)iDsf_scale_intoRange((s32)((lfAlp * lfGrn) + (lfMalp * (f64)lbgr->grn)), 255, 92, 255);
				lbgr->blu	= (u8)iDsf_scale_intoRange((s32)((lfAlp * lfBlu) + (lfMalp * (f64)lbgr->red)), 255, 92, 255);
			}
		}

	}

	void iDsf_colorize_andProcessVerticalLine_byPixels(SDsf* dsf, SDsf_hwnd* h, SDsf_chars* c, s32 y1, s32 y2, s32 x, SBgr color)
	{
		SXy_f64 ul, lr;


		//////////
		// Make sure the values are in the correct order
		/////
			iDsf_makeSure_lowToHigh_s32(&y1, &y2);


		//////////
		// Colorize it
		//////
			iDsf_colorize_verticalLine_byPixels(dsf, h, c, y1, y2, x, color);


		//////
		// Process it
		// Scan through this range and see if there are any splines, points, or strokes which need selected
		//////
			// Compute upper-left and lower-right range
			ul.x = (f64)x                     / (f64)h->w;
			ul.y = ((f64)y1 + 0.999999999999) / (f64)h->h;
			lr.x = ((f64)x  + 0.999999999999) / (f64)h->w;
			lr.y = (f64)y2                    / (f64)h->h;
			iDsf_select_range(dsf, h, c, &lr, &lr);
	}

	void iDsf_colorize_verticalLine_byPixels(SDsf* dsf, SDsf_hwnd* h, SDsf_chars* c, s32 y1, s32 y2, s32 x, SBgr color)
	{
		s32		lnY;
		f64		lfAlp, lfMalp, lfRed, lfGrn, lfBlu;
		SBgr*	lbgr;


		// Is it out of bounds?
		if (x < 0 || x >= h->w)
			return;

		// Get the pointer
		lbgr = (SBgr*)((s8*)h->bd + (y1 * h->rowWidth) + (x * 3));

		// Get the colors
		lfRed	= (f64)color.red;
		lfGrn	= (f64)color.grn;
		lfBlu	= (f64)color.blu;
		lfAlp	= 0.5;
		lfMalp	= 1.0 - lfAlp;

		// Iterate for every x
		for (lnY = y1; lnY <= y2; lnY++, lbgr = (SBgr*)((s8*)lbgr + h->rowWidth))
		{
			// Is it out of bounds?
			if (lnY >= 0 && lnY < h->h)
			{
				// Colorize it
				lbgr->red	= (u8)iDsf_scale_intoRange((s32)((lfAlp * lfRed) + (lfMalp * (f64)lbgr->red)), 255, 92, 255);
				lbgr->grn	= (u8)iDsf_scale_intoRange((s32)((lfAlp * lfGrn) + (lfMalp * (f64)lbgr->grn)), 255, 92, 255);
				lbgr->blu	= (u8)iDsf_scale_intoRange((s32)((lfAlp * lfBlu) + (lfMalp * (f64)lbgr->red)), 255, 92, 255);
			}
		}
	}

	void iDsf_invertImage(SDsf_hwnd* h)
	{
		s32		lnX, lnY;
		SBgr*	lbgr;


		//////////
		// Iterate through every pixel
		//////
			for (lnY = 0; lnY < h->h; lnY++)
			{
				// Begin on this row
				lbgr = (SBgr*)((s8*)h->bd + (lnY * h->rowWidth));
				for (lnX = 0; lnX < h->w; lnX++, lbgr++)
				{
					// Invert the pixel
					lbgr->red = 255 - lbgr->red;
					lbgr->grn = 255 - lbgr->grn;
					lbgr->blu = 255 - lbgr->blu;
				}
			}
	}

	u32 iDsf_scale_intoRange(s32 tnValue, s32 tnValueMax, s32 tnMinRange, s32 tnMaxRange)
	{
		if (tnValue > tnValueMax)
			tnValue = tnValueMax;

		return(tnMinRange + (s32)(((f64)tnValue / (f64)tnValueMax) * (f64)(tnMaxRange - tnMinRange)));
	}

	u32 iDsf_validate_range(s32 tnValue, s32 tnValueMin, s32 tnValueMax, s32 tnDefaultValue)
	{
		if (tnValue >= tnValueMin && tnValue <= tnValueMax)		return(tnValue);
		else													return(tnDefaultValue);
	}

	void iDsf_makeSure_lowToHigh_u32(u32* p1, u32* p2)
	{
		u32 lp;


		// Are they already sorted
		if (*p1 <= *p2)
			return;

		// Reverse them
		lp	= *p2;
		*p2	= *p1;
		*p1	= lp;
	}

	void iDsf_makeSure_lowToHigh_s32(s32* p1, s32* p2)
	{
		s32 lp;


		// Are they already sorted
		if (*p1 <= *p2)
			return;

		// Reverse them
		lp	= *p2;
		*p2	= *p1;
		*p1	= lp;
	}

	void iDsf_makeSure_lowToHigh_f64(f64* p1, f64* p2)
	{
		f64 lp;


		// Are they already sorted
		if (*p1 <= *p2)
			return;

		// Reverse them
		lp	= *p2;
		*p2	= *p1;
		*p1	= lp;
	}

	// Sort by Y, then X, ascending in both directions
	int iiDsf_tems_qsortCallback(const void* l, const void* r)
	{
		SDsf_tems*	left;
		SDsf_tems*	right;


		// Get our pointers properly
		left	= (SDsf_tems*)l;
		right	= (SDsf_tems*)r;

		// See how the cookie crumbles
		     if (left->fy < right->fy)		return(-1);		// Left is less than right
		else if (left->fy > right->fy)		return(1);		// Left is greater than right
		else if (left->fx < right->fx)		return(-1);		// Left is less than right
		else if (left->fx > right->fx)		return(1);		// Left is greater than right
		else								return(0);		// They're equal
	}

	// Sort by Y, then X, ascending in both directions
	int iiDsf_SXy_s32_qsortCallback(const void* l, const void* r)
	{
		SXy_s32*	left;
		SXy_s32*	right;


		// Get our pointers properly
		left	= (SXy_s32*)l;
		right	= (SXy_s32*)r;

		// See how the cookie crumbles
		     if (left->yi < right->yi)		return(-1);		// Left is less than right
		else if (left->yi > right->yi)		return(1);		// Left is greater than right
		else if (left->xi < right->xi)		return(-1);		// Left is less than right
		else if (left->xi > right->xi)		return(1);		// Left is greater than right
		else								return(0);		// They're equal
	}

	int iiDsf_SPointsDrawn_qsortCallback(const void* l, const void* r)
	{
		SDsf_pointsDrawn*	left;
		SDsf_pointsDrawn*	right;


		// Get our pointers properly
		left	= (SDsf_pointsDrawn*)l;
		right	= (SDsf_pointsDrawn*)r;

		// See how the cookie crumbles
		     if (left->pt.yi < right->pt.yi)		return(-1);		// Left is less than right
		else if (left->pt.yi > right->pt.yi)		return(1);		// Left is greater than right
		else if (left->pt.xi < right->pt.xi)		return(-1);		// Left is less than right
		else if (left->pt.xi > right->pt.xi)		return(1);		// Left is greater than right
		else										return(0);		// They're equal
	}




//////////
//
// Called to create a new window, or to reuse an existing window, which is for rendering displayed
// items for preview or examination.
//
//////
	SDsf_hwnd* iDsf_findOnlyHwnd_byHwnd(SBuilder* hwnds, u32 tnHwndParent, u32 tnHwnd)
	{
		u32		lnI;
		SDsf_hwnd*	h;


		//////////
		// See if the existing item exists
		//////
			for (lnI = 0; lnI < hwnds->populatedLength; lnI += sizeof(SDsf_hwnd))
			{
				// Grab this pointer
				h = (SDsf_hwnd*)(hwnds->data + lnI);

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

	SDsf_hwnd* iDsf_findOnlyHwnd_byHwndControl(SBuilder* hwnds, u32 tnHwndParent, u32 tnHwndControl)
	{
		u32		lnI;
		SDsf_hwnd*	h;


		//////////
		// See if the existing item exists
		//////
			for (lnI = 0; lnI < hwnds->populatedLength; lnI += sizeof(SDsf_hwnd))
			{
				// Grab this pointer
				h = (SDsf_hwnd*)(hwnds->data + lnI);

				// See if it's a match
				if (h->_hwndParent == tnHwndParent && h->_hwndControl == tnHwndControl)
				{
					// It's a match
					return(h);
				}
			}
			// If we get here, it wasn't found
			return(NULL);
	}

	SDsf_hwnd* iDsf_findOnlyHwnd_byHwndParent(SBuilder* hwnds, u32 tnHwndParent)
	{
		u32		lnI;
		SDsf_hwnd*	h;


		//////////
		// See if the existing item exists
		//////
			for (lnI = 0; lnI < hwnds->populatedLength; lnI += sizeof(SDsf_hwnd))
			{
				// Grab this pointer
				h = (SDsf_hwnd*)(hwnds->data + lnI);

				// See if it's a match
				if (h->_hwndParent == tnHwndParent && h->markup)
				{
					// It's a match
					return(h);
				}
			}
			// If we get here, it wasn't found
			return(NULL);
	}

	SDsf_hwnd* iDsf_findOnlyHwnd(SBuilder* hwnds, u32 tnHwndParent, s32 tnX, s32 tnY, s32 tnWidth, s32 tnHeight)
	{
		u32		lnI;
		SDsf_hwnd*	h;


		//////////
		// See if the existing item exists
		//////
			for (lnI = 0; lnI < hwnds->populatedLength; lnI += sizeof(SDsf_hwnd))
			{
				// Grab this pointer
				h = (SDsf_hwnd*)(hwnds->data + lnI);

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

	SDsf_hwnd* iDsf_findHwnd_orCreate(SBuilder* hwnds, u32 tnHwndParent, s32 tnX, s32 tnY, s32 tnWidth, s32 tnHeight, u32 tlMarkup)
	{
		SDsf_hwnd*	h;


		//////////
		// See if it already exists
		//////
			h = iDsf_findOnlyHwnd(hwnds, tnHwndParent, tnX, tnY, tnWidth, tnHeight);
			if (h)
				return(h);

		//////////
		// Add it
		//////
			h = (SDsf_hwnd*)iBuilder_allocateBytes(hwnds, sizeof(SDsf_hwnd));
			if (h)
			{
				// Initialize it
				memset(h, 0, sizeof(SDsf_hwnd));

				// Populate it
				h->_hwndParent			= tnHwndParent;
				h->x					= tnX;
				h->y					= tnY;
				h->w					= tnWidth;
				h->h					= tnHeight;
				h->markup				= tlMarkup;
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
				h->_hwnd				= iDsf_createWindow(h);
			}
			// Return our pointer
			return(h);
	}




//////////
//
// Called to constrain a quad around a line.  It is assumed that the quad runs from p1..p4, and
// p2..p3 around the line with p1..p4 being near line.p1, and p2..p3 being near line.p2.  The
// constraining distances are maximum radii out from the line to the corner points of the quad.
// If they exceed then they are reined in.  And if they are less then the flag determines if they
// are forcibly constrained to that distance.
//
//////
	void iDsf_constrain_quadAroundLine(SDsf_line_f64* lineRef, SXy_f64* p1, SXy_f64* p2, SXy_f64* p3, SXy_f64* p4, f64 tfp1Max, f64 tfp2Max, f64 tfp3Max, f64 tfp4Max, bool tlForceSize)
	{
		iDsf_constrain_lineLength(&lineRef->p1, p1, tfp1Max, tlForceSize);
		iDsf_constrain_lineLength(&lineRef->p2, p2, tfp2Max, tlForceSize);
		iDsf_constrain_lineLength(&lineRef->p2, p3, tfp3Max, tlForceSize);
		iDsf_constrain_lineLength(&lineRef->p1, p4, tfp4Max, tlForceSize);
	}

	void iDsf_constrain_lineLength(SXy_f64* po, SXy_f64* pToConstrain, f64 tfMaxLength, bool tlForceToLength)
	{
		SDsf_line_f64	line;


		//////////
		// Compute our line
		//////
			line.p1.x = po->x;
			line.p1.y = po->y;
			line.p2.x = pToConstrain->x;
			line.p2.y = pToConstrain->y;
			iDsf_compute_line(&line);
			if (tlForceToLength || line.length > tfMaxLength)
			{
				// Force the point to that length's location
				pToConstrain->x	= line.p1.x + (tfMaxLength * cos(line.theta));
				pToConstrain->y	= line.p1.y + (tfMaxLength * sin(line.theta));
			}
	}




//////////
//
// Called to adjust theta into the range 0..2pi
//
//////
	f64 iDsf_adjustTheta(f64 tfTheta)
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
// Called when the mouse is selected on this area.  Based on the selection criteria, what is
// needing to be processed will be processed.
//
//////
	void iDsf_select_range(SDsf* dsf, SDsf_hwnd* h, SDsf_chars* c, SXy_f64* ul, SXy_f64* lr)
	{
		u32			lnI;
		bool		llL, llO, llR, llSkipToNextStroke;
		SXy_f64		pl, po, pr;
		SDsf_spline*	spline;
		SDsf_spline*	splineStrokeStart;


		// Iterate through each item
		llSkipToNextStroke	= false;
		splineStrokeStart	= (SDsf_spline*)c->splines->data;
		for (lnI = 0; lnI < c->splines->populatedLength; lnI += sizeof(SDsf_spline))
		{
			// Grab the pointer
			spline = (SDsf_spline*)(c->splines->data + lnI);

			// We only process iOrder records above 0
			if (spline->iOrder > 0)
			{
				// See if this is the start of a new stroke
				if (spline->lPenDown)
				{
					// It is
					llSkipToNextStroke	= false;
					splineStrokeStart	= spline;
				}

				// Are supposed to skip to the start of the next stroke?
				if (!llSkipToNextStroke)
				{
					// Compute the three points
					iDsf_spline_compute(spline, &pl, &po, &pr);

					// If any of the points are in range, then we operate appropriately
					llL		= iDsf_isPointInRange(&pl, ul, lr);
					llO		= iDsf_isPointInRange(&po, ul, lr);
					llR		= iDsf_isPointInRange(&pr, ul, lr);
					if (llL || llO || llR)
					{
						// At least one of these points is in line
						switch (dsf->mode)
						{
							case _MODE_POINT:
								// We are selecting any matching points only
								if (llL)		iDsf_select_point(dsf, spline, &spline->tlLSelected);
								if (llO)		iDsf_select_point(dsf, spline, &spline->tlOSelected);
								if (llR)		iDsf_select_point(dsf, spline, &spline->tlRSelected);
								break;

							case _MODE_SPLINE:
								// We are selecting the entire spline
								iDsf_select_spline(dsf, spline);
								break;

							case _MODE_STROKE:
								// We are selecting the entire stroke
								iDsf_select_stroke(dsf, splineStrokeStart);
								llSkipToNextStroke = true;
								break;

							case _MODE_BEFORE:
								// We are selecting everything up to and including this spline on the stroke
								iDsf_select_strokeBefore(dsf, splineStrokeStart, spline);
								break;

							case _MODE_AFTER:
								// We are selecting everything from this spline and beyond on this stroke
								iDsf_select_strokeAfter(dsf, spline);
								llSkipToNextStroke = true;
								break;

							default:
								// A settings error
								_asm int 3;
								return;
						}
					}
				}
			}
		}
	}

	void iDsf_select_point(SDsf* dsf, SDsf_spline* spline, bool* tlSelected)
	{
		if (dsf->disposition == _DISPOSITION_FLIP_LR || dsf->disposition == _DISPOSITION_FLIP_LM_RM)
		{
			// This is an entire spline operation
			iDsf_select_spline(dsf, spline);
			return;
		}

		// If we get here, it's some other disposition
		switch (dsf->method)
		{
			case _METHOD_LEFT:
				// They want the left point selected, and the middle and right points not selected
				switch (dsf->disposition)
				{
					case _DISPOSITION_SELECT:
						// They are selecting
						if (!spline->tlLProcessed)		spline->tlLSelected = true;
						spline->tlLProcessed = true;
						break;

					case _DISPOSITION_UNSELECT:
						// They are un-selecting
						if (!spline->tlLProcessed)		spline->tlLSelected = false;
						spline->tlLProcessed = true;
						break;

					case _DISPOSITION_TOGGLE:
						// We are toggling
						if (!spline->tlLProcessed)		spline->tlLSelected = !spline->tlLSelected;
						spline->tlLProcessed = true;
						break;
				}
				break;

			case _METHOD_MIDDLE:
				// They want the middle point selected, and the left and right points not selected
				switch (dsf->disposition)
				{
					case _DISPOSITION_SELECT:
						// They are selecting
						if (!spline->tlOProcessed)		spline->tlOSelected = true;
						spline->tlOProcessed = true;
						break;

					case _DISPOSITION_UNSELECT:
						// They are un-selecting
						if (!spline->tlOProcessed)		spline->tlOSelected = false;
						spline->tlOProcessed = true;
						break;

					case _DISPOSITION_TOGGLE:
						// We are toggling
						if (!spline->tlOProcessed)		spline->tlOSelected = !spline->tlOSelected;
						spline->tlOProcessed = true;
						break;
				}
				break;

			case _METHOD_RIGHT:
				// They want the right point selected, and the left and middle points not selected
				switch (dsf->disposition)
				{
					case _DISPOSITION_SELECT:
						// They are selecting
						if (!spline->tlRProcessed)		spline->tlRSelected = true;
						spline->tlRProcessed = true;
						break;

					case _DISPOSITION_UNSELECT:
						// They are un-selecting
						if (!spline->tlRProcessed)		spline->tlRSelected = false;
						spline->tlRProcessed = true;
						break;

					case _DISPOSITION_TOGGLE:
						// We are toggling
						if (!spline->tlRProcessed)		spline->tlRSelected = !spline->tlRSelected;
						spline->tlRProcessed = true;
						break;
				}
				break;

			case _METHOD_LEFT_MIDDLE:
				// They want the left and middle points selected, and the right point not selected
				switch (dsf->disposition)
				{
					case _DISPOSITION_SELECT:
						// They are selecting
						if (!spline->tlLProcessed)		spline->tlLSelected = true;
						if (!spline->tlOProcessed)		spline->tlOSelected = true;
						spline->tlLProcessed = true;
						spline->tlOProcessed = true;
						break;

					case _DISPOSITION_UNSELECT:
						// They are un-selecting
						if (!spline->tlLProcessed)		spline->tlLSelected = false;
						if (!spline->tlOProcessed)		spline->tlOSelected = false;
						spline->tlLProcessed = true;
						spline->tlOProcessed = true;
						break;

					case _DISPOSITION_TOGGLE:
						// We are toggling
						if (!spline->tlLProcessed)		spline->tlLSelected = !spline->tlLSelected;
						if (!spline->tlOProcessed)		spline->tlOSelected = !spline->tlOSelected;
						spline->tlLProcessed = true;
						spline->tlOProcessed = true;
						break;
				}
				break;

			case _METHOD_MIDDLE_RIGHT:
				// They want the middle and right points selected, and the left point not selected
				switch (dsf->disposition)
				{
					case _DISPOSITION_SELECT:
						// They are selecting
						if (!spline->tlOProcessed)		spline->tlOSelected = true;
						if (!spline->tlRProcessed)		spline->tlRSelected = true;
						spline->tlOProcessed = true;
						spline->tlRProcessed = true;
						break;

					case _DISPOSITION_UNSELECT:
						// They are un-selecting
						if (!spline->tlOProcessed)		spline->tlOSelected = false;
						if (!spline->tlRProcessed)		spline->tlRSelected = false;
						spline->tlOProcessed = true;
						spline->tlRProcessed = true;
						break;

					case _DISPOSITION_TOGGLE:
						// We are toggling
						if (!spline->tlOProcessed)		spline->tlOSelected = !spline->tlOSelected;
						if (!spline->tlRProcessed)		spline->tlRSelected = !spline->tlRSelected;
						spline->tlOProcessed = true;
						spline->tlRProcessed = true;
						break;
				}
				break;

			case _METHOD_LEFT_RIGHT:
				// They want the left and right points selected, and the middle point not selected
				switch (dsf->disposition)
				{
					case _DISPOSITION_SELECT:
						// They are selecting
						if (!spline->tlLProcessed)		spline->tlLSelected = true;
						if (!spline->tlRProcessed)		spline->tlRSelected = true;
						spline->tlLProcessed = true;
						spline->tlRProcessed = true;
						break;

					case _DISPOSITION_UNSELECT:
						// They are un-selecting
						if (!spline->tlLProcessed)		spline->tlLSelected = false;
						if (!spline->tlRProcessed)		spline->tlRSelected = false;
						spline->tlLProcessed = true;
						spline->tlRProcessed = true;
						break;

					case _DISPOSITION_TOGGLE:
						// We are toggling
						if (!spline->tlLProcessed)		spline->tlLSelected = !spline->tlLSelected;
						if (!spline->tlRProcessed)		spline->tlRSelected = !spline->tlRSelected;
						spline->tlLProcessed = true;
						spline->tlRProcessed = true;
						break;
				}
				break;

			case _METHOD_SPLINE:
				// They want the all three, left, middle, and right points selected
				switch (dsf->disposition)
				{
					case _DISPOSITION_SELECT:
						// They are selecting
						if (!spline->tlLProcessed)		spline->tlLSelected = true;
						if (!spline->tlOProcessed)		spline->tlOSelected = true;
						if (!spline->tlRProcessed)		spline->tlRSelected = true;

						spline->tlLProcessed = true;
						spline->tlOProcessed = true;
						spline->tlRProcessed = true;
						break;

					case _DISPOSITION_UNSELECT:
						// They are un-selecting
						if (!spline->tlLProcessed)		spline->tlLSelected = false;
						if (!spline->tlOProcessed)		spline->tlOSelected = false;
						if (!spline->tlRProcessed)		spline->tlRSelected = false;

						spline->tlLProcessed = true;
						spline->tlOProcessed = true;
						spline->tlRProcessed = true;
						break;

					case _DISPOSITION_TOGGLE:
						// We are toggling
						if (!spline->tlLProcessed)		spline->tlLSelected = !spline->tlLSelected;
						if (!spline->tlOProcessed)		spline->tlOSelected = !spline->tlOSelected;
						if (!spline->tlRProcessed)		spline->tlRSelected = !spline->tlRSelected;

						spline->tlLProcessed = true;
						spline->tlOProcessed = true;
						spline->tlRProcessed = true;
						break;
				}
				break;

			case _METHOD_POINT:
				switch (dsf->disposition)
				{
					case _DISPOSITION_SELECT:
						// We are simply selecting
						if (!spline->tlLProcessed)		*tlSelected = true;
						spline->tlLProcessed = true;
						break;

					case _DISPOSITION_UNSELECT:
						// We are simply unselecting
						if (!spline->tlLProcessed)		*tlSelected = false;
						spline->tlLProcessed = true;
						break;

					case _DISPOSITION_TOGGLE:
						// We are toggling
						if (!spline->tlLProcessed)		*tlSelected = !*tlSelected;
						spline->tlLProcessed = true;
						break;
				}
				break;
		}
	}

	void iDsf_select_spline(SDsf* dsf, SDsf_spline* spline)
	{
		switch (dsf->disposition)
		{
			case _DISPOSITION_SELECT:
				// They are selecting
				if (!spline->tlLProcessed)		spline->tlLSelected = true;
				if (!spline->tlOProcessed)		spline->tlOSelected = true;
				if (!spline->tlRProcessed)		spline->tlRSelected = true;

				spline->tlLProcessed = true;
				spline->tlOProcessed = true;
				spline->tlRProcessed = true;
				break;

			case _DISPOSITION_UNSELECT:
				// They are un-selecting
				if (!spline->tlLProcessed)		spline->tlLSelected = false;
				if (!spline->tlOProcessed)		spline->tlOSelected = false;
				if (!spline->tlRProcessed)		spline->tlRSelected = false;

				spline->tlLProcessed = true;
				spline->tlOProcessed = true;
				spline->tlRProcessed = true;
				break;

			case _DISPOSITION_TOGGLE:
				// We are toggling
				if (!spline->tlLProcessed)		spline->tlLSelected = !spline->tlLSelected;
				if (!spline->tlOProcessed)		spline->tlOSelected = !spline->tlOSelected;
				if (!spline->tlRProcessed)		spline->tlRSelected = !spline->tlRSelected;

				spline->tlLProcessed = true;
				spline->tlOProcessed = true;
				spline->tlRProcessed = true;
				break;

			case _DISPOSITION_FLIP_LR:
				// We are toggling left right, or right left
				if (spline->tlLSelected)
				{
					// Switch to right
					if (!spline->tlLProcessed)		spline->tlLSelected = false;
					if (!spline->tlOProcessed)		spline->tlOSelected = false;
					if (!spline->tlRProcessed)		spline->tlRSelected = true;

				} else if (spline->tlRSelected) {
					// Switch to left
					if (!spline->tlLProcessed)		spline->tlLSelected = true;
					if (!spline->tlOProcessed)		spline->tlOSelected = false;
					if (!spline->tlRProcessed)		spline->tlRSelected = false;
				}

				spline->tlLProcessed = true;
				spline->tlOProcessed = true;
				spline->tlRProcessed = true;
				break;

			case _DISPOSITION_FLIP_LM_RM:
				// We are toggling left+middle to middle+right, or middle+right to middle+left
				if (spline->tlLSelected)
				{
					// Switch to right
					if (!spline->tlLProcessed)		spline->tlLSelected = false;
					if (!spline->tlOProcessed)		spline->tlOSelected = true;
					if (!spline->tlRProcessed)		spline->tlRSelected = true;

				} else if (spline->tlRSelected) {
					// Switch to left
					if (!spline->tlLProcessed)		spline->tlLSelected = true;
					if (!spline->tlOProcessed)		spline->tlOSelected = true;
					if (!spline->tlRProcessed)		spline->tlRSelected = false;
				}

				spline->tlLProcessed = true;
				spline->tlOProcessed = true;
				spline->tlRProcessed = true;
				break;
		}
	}

	void iDsf_select_stroke(SDsf* dsf, SDsf_spline* splineStrokeStart)
	{
		// Incomplete feature
		_asm int 3;
	}

	void iDsf_select_strokeBefore(SDsf* dsf, SDsf_spline* splineStrokeStart, SDsf_spline* splineStrokeEnd)
	{
		// Incomplete feature
		_asm int 3;
	}

	void iDsf_select_strokeAfter(SDsf* dsf, SDsf_spline* splineStrokeStart)
	{
		// Incomplete feature
		_asm int 3;
	}

	void iDsf_spline_compute(SDsf_spline* spline, SXy_f64* pl, SXy_f64* po, SXy_f64* pr)
	{
		//////////
		// Origin is a simple copy
		//////
			po->x = spline->ox;
			po->y = spline->oy;


		//////////
		// Left and right are computed based on theta and origin
		//////
			// Right
			pr->x = spline->ox + (spline->rr * cos(spline->rt + spline->ot));
			pr->y = spline->oy + (spline->rr * sin(spline->rt + spline->ot));
			// Left
			pl->x = spline->ox + (spline->lr * cos(spline->lt + spline->ot));
			pl->y = spline->oy + (spline->lr * sin(spline->lt + spline->ot));

	}

	// Test the point against the ul..lr range
	bool iDsf_isPointInRange(SXy_f64* pt, SXy_f64* ul, SXy_f64* lr)
	{
		if (pt->y >= ul->y && pt->y <= lr->y)
		{
			if (pt->x >= ul->x && pt->x <= lr->x)
			{
				// We're good
				return(true);
			}
		}
		// Not in range
		return(false);
	}




//////////
//
// Read the mouse position asynchronously
//
//////
	void iDsf_read_mousePosition(SDsf* dsf, SDsf_hwnd* h)
	{
		u32				lnI, lnJ;
		bool			llLastMouseLeft, llLastMouseRight, llLastCtrl, llLastShift, llLastAlt, llMoved, llWasOnTheReservation, llOnTheReservation, llSomethingClicked;
		HWND			hwndFocus;
		SDsf_chars*		c;
		SDsf_spline*	spline;
		POINT			pt;


		//////////
		// Does our window have the focus?
		//////
			hwndFocus = GetFocus();
			if (hwndFocus != h->hwnd && hwndFocus != h->hwndParent)
				return;		// No


		//////////
		// Grab the cursor position
		//////
			GetCursorPos(&pt);
			ScreenToClient(h->hwnd, &pt);

		
		//////////
		// Adjust for the window
		//////
			// Adjust for our window
			pt.y -= h->y;

			// See if it's moved, and if so if it's moved off the reservation
			llMoved					= !(gMouse.xi == pt.x && gMouse.yi == pt.y);
			llWasOnTheReservation	= (gMouse.xi >= 0 && gMouse.xi < h->w && gMouse.yi >= 0 && gMouse.yi < h->h);

			// Store the new value
			gMouse.xi	= pt.x;
			gMouse.yi	= pt.y;
			// See if it's on the reservation
			llOnTheReservation	= (gMouse.xi >= 0 && gMouse.xi < h->w && gMouse.yi >= 0 && gMouse.yi < h->h);


		//////////
		// Grab the key states
		//////
			llLastCtrl			= glCtrlKeyDown;
			llLastShift			= glShiftKeyDown;
			llLastAlt			= glAltKeyDown;
			llLastMouseLeft		= glMouseLeft;
			llLastMouseRight	= glMouseRight;
			glCtrlKeyDown		= (GetAsyncKeyState(VK_CONTROL) != 0);
			glShiftKeyDown		= (GetAsyncKeyState(VK_SHIFT) != 0);
			glAltKeyDown		= (GetAsyncKeyState(VK_MENU) != 0);
			glMouseLeft			= (GetAsyncKeyState(VK_LBUTTON) != 0);
			glMouseRight		= (GetAsyncKeyState(VK_RBUTTON) != 0);

			// If we are now off the reservation, then ignore the mouse clicks
			if (!llOnTheReservation)
			{
				// We are no longer on the reservation, ignore mouse activity
				llMoved				= false;
				glMouseLeft			= llLastMouseLeft;
				glMouseRight		= llLastMouseRight;
				glCtrlKeyDown		= llLastCtrl;
				glShiftKeyDown		= llLastShift;
				glAltKeyDown		= llLastAlt;
			}

			// See if a key our button has been pressed
			llSomethingClicked = (llLastMouseLeft != glMouseLeft || llLastMouseRight != glMouseRight || llLastCtrl != glCtrlKeyDown || llLastShift != glShiftKeyDown || llLastAlt != glAltKeyDown);


		//////////
		// Has the mouse moved?
		//////
			if ((llWasOnTheReservation && !llOnTheReservation) || (llOnTheReservation && (llMoved || llSomethingClicked)))
			{
				//////////
				// Has the left mouse button gone down?
				//////
					if (!llLastMouseLeft && glMouseLeft)
					{
						// Yes, set everything to being not processed
						for (lnI = 0; lnI < dsf->chars->populatedLength; lnI += sizeof(SDsf_chars))
						{
							// Grab this pointer
							c = (SDsf_chars*)(dsf->chars->data + lnI);

							// Do every spline within each character
							for (lnJ = 0; lnJ < c->splines->populatedLength; lnJ += sizeof(SDsf_spline))
							{
								// Grab this pointer
								spline = (SDsf_spline*)(c->splines->data + lnJ);

								// We only process positive orders
								if (spline->iOrder > 0)
								{
									// Set this one to not processed
									spline->tlLProcessed	= false;
									spline->tlOProcessed	= false;
									spline->tlRProcessed	= false;
								}
							}
						}
					}


				//////////
				// Post a message back to the parent to indicate this child needs to be redrawn
				//////
					PostMessage(h->hwndParent, WM_REDRAW_WINDOW, (u32)dsf, h->_hwnd);
			}
	}
