//////////
//
// /libsf/utils/common/cpp/dsf.h
//
//////
// Version 0.60
// Copyright (c) 2015 by Rick C. Hodgin
//////
// Last update:
//     Dec.19.2015
//////
// Change log:
//     Dec.19.2015	- Initial creation
//////




struct SDsf_pointsDrawn
{
	SXy_s32		pt;
	SBgra		color;
};

struct SDsf_line_s32
{
	// This line is not computed, but holds two points for easy reference
	SXy_s32		p1i;
	SXy_s32		p2i;
};

struct SDsf_floanPoint
{
	f64	x;			// X coordinate of an X,Y pair
	f64	y;			// Y coordinate of an X,Y pair
};

struct SDsf_line_f64
{
	// These are the two input points
	SXy_f64		p1;
	SXy_f64		p2;

	// These are computed with iComputeLine()
	SXy_f64		delta;
	SXy_f64		mid;
	f64			length;
	f64			m;							// Slope
	f64			mp;							// Perpendicular slope
	f64			theta;						// Theta (from p1 to p2, note: add _PI to reverse the angle from p2 to p1)
	SXy_s32		p1i;
	SXy_s32		p2i;
	s32			p1_quad;
	s32			p2_quad;
};

//////////
// Structures used by DSF
//////
	struct SDsf_font
	{
		f64			fAscent;						// Maximum ascent within the 0..1 range
		f64			fUpper;							// Horizontal line of the top of the upper-case letters, and letters like h, l, k, etc
		f64			fLower;							// Horizontal line of the top of the lower-case letters, such as top of c, e, o, etc.
		f64			fLeft;							// Vertical line of the left-side of the characters
		f64			fRight;							// Vertical line of the right-side of the characters
		f64			fBase;							// Horizontal line of the base of all characters
		f64			fDescent;						// Horizontal line for the bottom of the descending characters, like y, g, q, etc.
		f64			fWidth;							// Horizontal width of the average stroke (couples with fLeft and fRight for guides)
		f64			fItalics;						// Radians to slant from PI/2 toward 0 (use negative values for reverse slant)
		f64			fBold;							// Standard percentage to add for standard bold setting
		f64			fUnderTop;						// Horizontal line for the top of the underline
		f64			fUnderBot;						// Horizontal line for the bottom of the underline
		f64			fStrikeTop;						// Horizontal line for the top of the strikethrough location
		f64			fStrikeBot;						// Horizontal line for the bottom of the strikethrough location
	};

	struct SDsf_chars
	{
		SBuilder*	splines;						// (SChar) Holds full char records
		SBuilder*	temsRaw;						// (STems) Holds all raw template points for this character (those sent from the calling app)

		// After the intial load is completed, (or in future upon resize), the temsRaw are aliased down to single instances for the visible size of the edit character window
		SBuilder*	tems;							// (STems) Holds aliased template points, one per pixel, as per temsRaw and the size of the edit character window (see dsf_initial_load_complete())
		SBuilder*	temsLines;						// (STemsLines) Holds all alpha layer rendering data for the comprising
	};

	struct SDsf_spline
	{
		s8			cType;							// S=Spline, D=Definition, R=Reference, L=Link
		u32			iid;							// Character number (ASCII character)
		s32			iOrder;							// Stroke order within the character
		s8			cDesc[10];						// A brief description of this section, usually used with lNewStroke for a new pen stroke
		bool		lPenDown;						// Used for an "i", for example, when the dot is a different stroke than the lower stock, each time the pen goes down it's a new stroke
		bool		lSelected;						// Is this item selected?
		f64			ox;								// Origin-X
		f64			oy;								// Origin-Y
		f64			ot;								// Origin-Theta (rotation)
		f64			lr;								// Left-Radius
		f64			lt;								// Left-Theta
		f64			rr;								// Right-Radius
		f64			rt;								// Right-Theta
		u32			iSubdivs;						// Automatic sub-divisions between this spline and the next one
		u32			iLnkId;							// If cType=R, the iid of the definition object; If cType=L, the iid of the link object (used with iLnkOrder to indicate which linked item this one modifies)
		s32			iLnkOrder;						// If cType=L, the item within the link object that this entry modifies

		// Used to determine if this spline has already been processed this go around
		bool		tlLProcessed;					// When the mouse goes down, these are set to false
		bool		tlOProcessed;					// As they are changed, they are raised.
		bool		tlRProcessed;					// This will prevent them from being double-processed during a single select/unselect/toggle operation

		// Used internally for editing
		bool		tlOSelected;					// Is the original selected?
		bool		tlRSelected;					// Is the left-side selected?
		bool		tlLSelected;					// Is the right-side selected?
	};

	struct SDsf_refs
	{
		s8			cType;							// Line types supported:  H=Horizontal, V=Vertical, 2=Two point, 3=Three point, 5=Five point
		s8			cDesc[40];						// Description of this reference
		f64			fref1x;							// Used for H,V,2,3,5
		f64			fref1y;							// Used for H,V,2,3,5
		f64			fref2x;							// Used for 2,3,5
		f64			fref2y;							// Used for 2,3,5
		f64			fref3x;							// Used for 3,5
		f64			fref3y;							// Used for 3,5
		f64			fref4x;							// Used for 5
		f64			fref4y;							// Used for 5
		f64			fref5x;							// Used for 5
		f64			fref5y;							// Used for 5
		bool		lVisible;						// Should this item be used
		s8			cChars1[128];					// Characters this item should be displayed on #1
		s8			cChars2[128];					// Characters this item should be displayed on #2

		SBuilder*	floans;							// Floan data for this particular entry
	};

	// Template point -- is an X,Y coordinate for part of an outline or line that was created as a template for the font.
	// Certain mathematical operations for spline placement use these for reference
	struct SDsf_tems
	{
		f64		fx;									// X of X,Y coordinate for this outline point
		f64		fy;									// Y of X,Y coordinate for this outline point
		u32		recno;								// Original record number this item came from

		u8		changed;							// Set each time this tems entry is changed
		u8		deleted;							// Set when items are deleted
	};

	struct SDsf_temsLines
	{
		SXy_f64	p1;									// P1 is from location
		SXy_f64	p2;									// P2 is to location
	};

	// SDsf structures are always branded with DSF! as first four bytes, and then length of the structure after
	const s8 cgcDsfBrand[] = "DSF!";
	struct SDsf
	{
		s8				id[4];						// Always 'DSF!' (used to identify the handle)
		u32				id_size;					// sizeof(SInstance)
		SDsf_font		font;						// Font information for this instance

		u32				activeTool;					// The current active tool
		u32				activeChar;					// The character currently being edited / displayed
		u32				maxChar;					// The maximum character found during the initial load, or created later
		u32				disposition;				// 0=select, 1=unselect, 2=toggle, 3=flip left to right, right to left, 4=flip left/middle to right/middle, and right/middle to left/middle
		u32				mode;						// 0=point, 1=spline, 2=stroke, 3=before and current, 4=current and after
		u32				method;						// 0=left, 1=middle, 2=right, 3=left+middle, 4=middle+right, 5=left+right, 6=spline, 7=point
		u32				range;						// 0=active character, 1=AZ, 2=az, 3=AZaz, 4=09, 5=AZaz09, 6=AZaz09!@.., 7=all
		u32				showSplines;				// 0=no, 1=yes
		u32				splinesType;				// 0=fill, 1=outline, 2=LOR only
		u32				highlighSelection;			// 0=no, 1=yes, should the selection be highlighted on renderings?
		u32				showPenDowns;				// 0=no, 1=yes, should the pen/brush strokes be highlighted?
		u32				mouseCrosshairX;			// 0=no, 1=yes, should the mouse X-axis crosshair be shown?
		u32				mouseCrosshairY;			// 0=no, 1=yes, should the mouse Y-axis crosshair be shown?
		u32				invert;						// 0=no, 1=yes, should the image be inverted (negative image)?
		u32				zoomLens;					// 0=no, 1=yes, should a zoom lens be shown on the image?
		u32				cuesUnder;					// 0=on top, 1=under, should the cues be rendered above or below the splines?
		u32				selectArea;					// Some value between 10..30 (how big they want the mouse select area to be)

		// User cues
		u32				ascent;						// The ascent (highest point of the font, top of umlaut above a capital letter, for example
		u32				trackAscent;				// Should the mouse track near to ascent strokes?
		u32				upper;						// The upper (highest point of an upper-case letter, or number)
		u32				trackUpper;					// Should the mouse track near to the upper-line?
		u32				lower;						// The lower (highest point of a lower-case letter)
		u32				trackLower;					// Should the mouse track near to the lower-line?
		u32				base;						// The base (base of all characters, numbers, everything drawn)
		u32				trackBase;					// Should the mouse track near to the lower-line?
		u32				descent;					// The descent (lowest point of a letter, bottom of a y or g, for example)
		u32				trackDescent;				// Should the mouse track near to the descent-line?
		u32				strikethrough;				// Strikethrough lines (upper and lower, as per the line thickness)
		u32				trackStrike;				// Should the mouse track near to the strikethrough lines?
		u32				underline;					// Underscore lines (upper and lower, as per the line thickness)
		u32				trackUnderline;				// Should the mouse track near to the underline lines?
		u32				showRefs;					// Custom references
		u32				trackRefs;					// Should the mouse track near to the custom references?
		u32				left;						// Should the left cues by visible?
		u32				trackLeft;					// Should the mouse track the left cues?
		u32				right;						// Should the right cues be visible?
		u32				trackRight;					// Should the mouse track the right cues?
		u32				width;						// Should the width be used?
		u32				trackWidth;					// Should the mouse track to the width cues?
		u32				tems;						// Should the tems be visible?
		u32				trackTems;					// Should the mouse track to the tems?
		u32				grid;						// 0=no, 1=yes, should the grid be shown?
		u32				trackGrid;					// Should the mouse track to the grid?

		SBuilder*		chars;						// (SBuilder) Characters, one SBuilder for every character, with each character SBuilder pointing to its many SChar entries
		SBuilder*		refs;						// (SRefs) References
		SBuilder*		hwnds;						// Child window references for this instance
	};


	

//////////
// Constants
//////
	const f64	_2PI						= 6.28318530717959;		// 2*pi
	const f64	_3PI_2						= 4.71238898038469;		// 3*pi/2
	const f64	_4PI_3						= 4.18879020478639;		// 4*pi/3
	const f64	_PI							= 3.14159265358979;		// pi
	const f64	_2PI_3						= 2.09439510239320;		// 2*pi/3
	const f64	_PI_2						= 1.57079632679490;		// pi/2
	const f64	_PI_3						= 1.04719755119660;		// pi/3
	const f64	_PI_4						= 0.78539816339745;		// pi/4
	const f64	_PI_6						= 0.52359877559830;		// pi/6
	const f64	_SQRT2						= 1.4142135624;
	const s8	cgcPreviewWindowClass[]		= "DSF-Preview-Window-Class";
	const s8	cgcControlWindowClass[]		= "DSF-Control-Window-Class";

	const u32	_NO							= 0;
	const u32	_YES						= 1;

	const u32	_SELECT_AREA_SMALL			= 10;
	const u32	_SELECT_AREA_MEDIUM			= 20;
	const u32	_SELECT_AREA_LARGE			= 30;
	const u32	_SELECT_AREA_EXTRA_LARGE	= 80;

	const u32	_DISPOSITION_SELECT			= 0;
	const u32	_DISPOSITION_UNSELECT		= 1;
	const u32	_DISPOSITION_TOGGLE			= 2;
	const u32	_DISPOSITION_FLIP_LR		= 3;
	const u32	_DISPOSITION_FLIP_LM_RM		= 4;
	
	const u32	_MODE_POINT					= 0;
	const u32	_MODE_SPLINE				= 1;
	const u32	_MODE_STROKE				= 2;
	const u32	_MODE_BEFORE				= 3;
	const u32	_MODE_AFTER					= 4;
	
	const u32	_METHOD_LEFT				= 0;
	const u32	_METHOD_MIDDLE				= 1;
	const u32	_METHOD_RIGHT				= 2;
	const u32	_METHOD_LEFT_MIDDLE			= 3;
	const u32	_METHOD_MIDDLE_RIGHT		= 4;
	const u32	_METHOD_LEFT_RIGHT			= 5;
	const u32	_METHOD_SPLINE				= 6;
	const u32	_METHOD_POINT				= 7;
	
	const u32	_RANGE_ACTIVE_CHAR			= 0;
	const u32	_RANGE_AZ					= 1;
	const u32	_RANGE_az					= 2;
	const u32	_RANGE_AZ_az				= 3;
	const u32	_RANGE_09					= 4;
	const u32	_RANGE_AZ_az_09				= 5;
	const u32	_RANGE_AZ_az_09_PLUS		= 6;
	const u32	_RANGE_ALL					= 7;

	const u32	_TEMS_TRACK					= 0;
	const u32	_TEMS_DISPLAY				= 1;
	
	const u32	_SPLINES_FILL				= 0;
	const u32	_SPLINES_OUTLINE			= 1;
	const u32	_SPLINES_LOR				= 2;

	const u32	_TOOL_EDIT					= 1;
	const u32	_TOOL_MOVE					= 2;
	const u32	_TOOL_STRETCH				= 3;
	const u32	_TOOL_ROTATE				= 4;
	const u32	_TOOL_SCALE					= 5;

	const u32	WM_REDRAW_WINDOW			= WM_USER + 1;




//////////
// Global variables
//////
	HINSTANCE		ghInstance;
	SBuilder*		gsRootDsfs;
	SBuilder*		gsDefaultChar;
	ITaskbarList*	giTaskbar;
	UINT_PTR		gnTimer					= 0;						// Used for the markup, to read the keyboard state and mouse position 30 times per second
	SXy_s32			gMouse					= { -1, -1 };
	u32				gMouseType				= _SELECT_AREA_SMALL;
	bool			glMouseLeft;
	bool			glMouseRight;
	bool			glCtrlKeyDown			= false;
	bool			glShiftKeyDown			= false;
	bool			glAltKeyDown			= false;


//////////
// Common colors
//////
	f64				gfLinePower				= 2.0;
	SBgr			white					= { 255, 255, 255 };
	SBgr			black					= { 0, 0, 0 };
	SBgr			blackSelected			= { 0, 92, 192 };
	SBgr			gray					= { 128, 128, 128 };
	SBgr			graySelected			= { 64, 128, 192 };
	SBgr			darkGray				= { 92, 92, 92 };
	SBgr			background				= { 32, 32, 32 };
	SBgr			backgroundSelected		= { 32, 64, 96 };
	SBgr			grid					= { 92, 92, 92 };
	SBgr			gridTrack				= { 192, 192, 192 };
	SBgr			mouseColor				= { 0, 255, 255 };
	SBgr			mousePeeakaheadColor	= { 255, 255, 0 };
	SBgr			strokeUp				= { 255, 192, 192 };
	SBgr			strokeDown				= { 128, 192, 255 };
	SBgr			colorL					= { 64, 64, 215 };
	SBgr			colorO					= { 255, 64, 64 };
	SBgr			colorR					= { 64, 215, 64 };
	SBgr			colorLSelected			= { 32, 64, 215 };
	SBgr			colorOSelected			= { 128, 160, 160 };
	SBgr			colorRSelected			= { 32, 215, 160 };
	SBgr			colorSelected			= { 0, 128, 255 };
	SBgr			colorAscent				= { 192, 192, 255 };
	SBgr			colorUpper				= { 0, 255, 255 };
	SBgr			colorLower				= { 0, 255, 255 };
	SBgr			colorBase				= { 255, 255, 255 };
	SBgr			colorDescent			= { 192, 192, 255 };
	SBgr			colorStrikethrough		= { 255, 0, 255};
	SBgr			colorUnderline			= { 255, 255, 0 };
	SBgr			colorLeft				= { 255, 255, 255 };
	SBgr			colorRight				= { 255, 255, 255 };
	SBgr			colorTems				= { 22, 222, 22 };




//////////
// Forward declarations
//////
	void				initialize								(void);
	SDsf_spline*		iDsf_addSpline_fromToLR					(SBuilder* b, bool tlPenDown, f64 tfXL, f64 tfYL, f64 tfXR, f64 tfYR);
	SDsf_spline*		iDsf_addSpline_centerThetaRadiusLR		(SBuilder* b, bool tlPenDown, f64 tfX, f64 tfY, f64 tfRadius, f64 tfThetaL, f64 tfThetaR);

	SDsf*				iDsf_getInstance						(u32 tnHandle, bool* tlValid);
	SDsf_spline*		iDsf_find_splineInstance				(SBuilder* charsBuilder, u32 tnIid, u8 tcType, u32 tiOrder, u32 tiLnkId, u32 tiLnkOrder);
	SDsf_chars*			iiDsf_findOrCreate_thisChars			(SBuilder* charsBuilder, u32 tnIid);
	SDsf_chars*			iiDsf_findOnly_thisChars				(SBuilder* charsBuilder, u32 tnIid);
	SDsf_spline*		iDsf_find_splineInstance_SD				(SBuilder* thisSplineBuilder, u32 tnIid, u32 tiOrder, bool tlAddIfNotFound);
	SDsf_spline*		iDsf_find_splineInstance_R				(SBuilder* thisSplineBuilder, u32 tnIid, u32 tiOrder, u32 tiLnkId, bool tlAddIfNotFound);
	SDsf_spline*		iDsf_find_splineInstance_L				(SBuilder* thisSplineBuilder, u32 tnIid, u32 tiOrder, u32 tiLnkId, u32 tiLnkOrder, bool tlAddIfNotFound);
	SDsf_refs*			iDsf_find_refsInstance					(SBuilder* refs, u8 tcType, s8* tcDesc40);
	SDsf_tems*			iDsf_create_newTemsEntry				(SBuilder* charsBuilder, u32 tipid);
	SBuilder*			iDsf_get_tems_rawBuilder				(SBuilder* charsBuilder,u32 tipid);

	int					iDsf_render								(SDsf* dsf, SDsf_hwnd* h, SDsf_chars* c, s32 tnWidth, s32 tnHeight, u32 tnHwndParent, s32 tnX, s32 tnY);
	void				iDsf_render_mouseCoordinates			(SDsf* dsf, SDsf_hwnd* h);
	void				iDsf_render_cues						(SDsf* dsf, SDsf_hwnd* h, SDsf_chars* c);
	void				iDsf_render_cueLineH					(SDsf* dsf, SDsf_hwnd* h, SDsf_chars* c, f64 tfY, SBgr color);
	void				iDsf_render_cueLineV					(SDsf* dsf, SDsf_hwnd* h, SDsf_chars* c, f64 tfX, SBgr color);
	void				iDsf_render_quadH						(SDsf* dsf, SDsf_hwnd* h, SDsf_chars* c, f64 tfTop, f64 tfBottom, SBgr color);
	void				iDsf_render_mouseOverlay				(SDsf* dsf, SDsf_hwnd* h, SDsf_chars* c);
	void				iDsf_render_refs						(SDsf* dsf, SDsf_hwnd* h, SDsf_chars* c);
	void				iDsf_render_grid						(SDsf* dsf, SDsf_hwnd* h);
	void				iDsf_render_splines						(SDsf* dsf, SDsf_hwnd* h, SDsf_chars* c, u32 tlMarkup, u32 tlBold, u32 tlItalic, u32 tlUnderline, u32 tlStrikethrough);
	void				iDsf_render_hint						(SDsf_hwnd* h, SDsf_line_f64* line, SXy_f64* pt);
	void				iDsf_render_tems						(SDsf* dsf, SDsf_hwnd* h, SDsf_chars* c);
	void				iDsf_render_zoomLens					(SDsf_hwnd* h);
	u32					iiDsf_renderMarkup_getNextLineSegment	(u32 tnIndex, u32 tnMaxCount, SDsf_hwnd* h, SDsf_tems* root, SDsf_tems** p1, SDsf_tems** p2);
	s32					iiDsf_renderMarkup_getPoint				(f64 tfValue01, s32 tnMultiplier);

	SBgr				iDsf_setLineColor						(SDsf* dsf);

	void				iDsf_compute_LOR						(SDsf_spline* s, SXy_f64* pl, SXy_f64* po, SXy_f64* pr);
	void				iDsf_compute_quadColors_R				(SDsf_spline* s, SDsf_spline* sLast, SBgr quadNormal, SBgr quadSelected, SBgr* p1ColorR, SBgr* p2ColorR, SBgr* p3ColorR, SBgr* p4ColorR);
	void				iDsf_compute_quadColors_L				(SDsf_spline* s, SDsf_spline* sLast, SBgr quadNormal, SBgr quadSelected, SBgr* p1ColorL, SBgr* p2ColorL, SBgr* p3ColorL, SBgr* p4ColorL);
	bool				iDsf_compute_closestMouseLine			(SDsf_line_f64* line);
	void				iDsf_compute_line						(SDsf_line_f64* line);
	void				iDsf_compute_line_fromTwoPoints			(SDsf_line_f64* line, SXy_f64* p1, SXy_f64* p2);
	s32					iDsf_compute_quad						(SXy_f64* p);

	void				iDsf_draw_penDown						(SDsf_hwnd* h, SDsf_line_f64* line);
	void				iDsf_draw_penUp							(SDsf_hwnd* h, SDsf_line_f64* line);
	void				iDsf_draw_points						(SDsf* dsf, SDsf_hwnd* h, SXy_f64* pr, SXy_f64* po, SXy_f64* pl, SDsf_spline* s, SBgr colorSelected, SBgr colorR, SBgr colorO, SBgr colorL, SBgr colorRSelected, SBgr colorOSelected, SBgr colorLSelected, SBgr colorLine);
	void				iDsf_draw_line							(SDsf_hwnd* h, SXy_f64* p1, SXy_f64* p2, SBgr colorStart, SBgr colorEnd, f64 tfPower);
	void				iDsf_draw_lineAlpha						(SDsf_hwnd* h, SXy_f64* p1, SXy_f64* p2, SBgr_af64* colorStart, SBgr_af64* colorEnd, SBuilder* pointsDrawn, bool tlNoDuplicates, f64 tfPower);
	void				iDsf_draw_line_alpha_noDuplicates		(SDsf_hwnd* h, SBuilder* pointsDrawn);
	void				iDsf_draw_point							(SDsf_hwnd* h, SXy_f64* p1, SBgr color);
	void				iDsf_draw_point_small					(SDsf_hwnd* h, SXy_f64* p1, SBgr color);
	void				iDsf_draw_point_large					(SDsf_hwnd* h, SXy_f64* p1, SBgr color);
	void				iDsf_draw_line_horizontal_byPixels		(SDsf_hwnd* h, s32 x1, s32 x2, s32 y, SBgr color);

	void				iDsf_fill_quad_alpha							(SDsf_hwnd* h, SXy_f64* p1, SXy_f64* p2, SXy_f64* p3, SXy_f64* p4, SBgr p1Color, SBgr p2Color, SBgr p3Color, SBgr p4Color, f64 tfP1Alp, f64 tfP2Alp, f64 tfP3Alp, f64 tfP4Alp, f64 tfPower);
	void				iDsf_colorize_andProcessHorizontalLine_byPixels	(SDsf* dsf, SDsf_hwnd* h, SDsf_chars* c, s32 x1, s32 x2, s32 y, SBgr color);
	void				iDsf_colorize_horizontalLine_byPixels			(SDsf* dsf, SDsf_hwnd* h, SDsf_chars* c, s32 x1, s32 x2, s32 y, SBgr color);
	void				iDsf_colorize_andProcessVerticalLine_byPixels	(SDsf* dsf, SDsf_hwnd* h, SDsf_chars* c, s32 y1, s32 y2, s32 x, SBgr color);
	void				iDsf_colorize_verticalLine_byPixels				(SDsf* sdf, SDsf_hwnd* h, SDsf_chars* c, s32 y1, s32 y2, s32 x, SBgr color);
	void				iDsf_invertImage								(SDsf_hwnd* h);
	u32					iDsf_scale_intoRange					(s32 tnValue, s32 tnValueMax, s32 tnMinRange, s32 tnMaxRange);
	u32					iDsf_validate_range						(s32 tnValue, s32 tnValueMin, s32 tnValueMax, s32 tnDefaultValue);
	void				iDsf_makeSure_lowToHigh_u32				(u32* p1, u32* p2);
	void				iDsf_makeSure_lowToHigh_s32				(s32* p1, s32* p2);
	void				iDsf_makeSure_lowToHigh_f64				(f64* p1, f64* p2);
	int					iiDsf_tems_qsortCallback				(const void* l, const void* r);
	int					iiDsf_SXy_s32_qsortCallback				(const void* l, const void* r);
	int					iiDsf_SPointsDrawn_qsortCallback		(const void* l, const void* r);

	SDsf_hwnd*			iDsf_findOnlyHwnd_byHwnd				(SBuilder* hwnds, u32 tnHwndParent, u32 tnHwnd);
	SDsf_hwnd*			iDsf_findOnlyHwnd_byHwndControl			(SBuilder* hwnds, u32 tnHwndParent, u32 tnHwndControl);
	SDsf_hwnd*			iDsf_findOnlyHwnd_byHwndParent			(SBuilder* hwnds, u32 tnHwndParent);
	SDsf_hwnd*			iDsf_findOnlyHwnd						(SBuilder* hwnds, u32 tnHwndParent, s32 tnX, s32 tnY, s32 tnWidth, s32 tnHeight);
	SDsf_hwnd*			iDsf_findHwnd_orCreate					(SBuilder* hwnds, u32 tnHwndParent, s32 tnX, s32 tnY, s32 tnWidth, s32 tnHeight, u32 tlMarkup);

	void				iDsf_constrain_quadAroundLine			(SDsf_line_f64* lineRef, SXy_f64* p1, SXy_f64* p2, SXy_f64* p3, SXy_f64* p4, f64 tfp1Max, f64 tfp2Max, f64 tfp3Max, f64 tfp4Max, bool tlForceSize);
	void				iDsf_constrain_lineLength				(SXy_f64* po, SXy_f64* pToConstrain, f64 tfMaxLength, bool tlForceToLength);
	f64					iDsf_adjustTheta						(f64 tfTheta);
	void				iDsf_select_range						(SDsf* dsf, SDsf_hwnd* h, SDsf_chars* c, SXy_f64* ul, SXy_f64* lr);
	void				iDsf_select_point						(SDsf* dsf, SDsf_spline* spline, bool* tlSelected);
	void				iDsf_select_spline						(SDsf* dsf, SDsf_spline* spline);
	void				iDsf_select_stroke						(SDsf* dsf, SDsf_spline* splineStrokeStart);
	void				iDsf_select_strokeBefore				(SDsf* dsf, SDsf_spline* splineStrokeStart, SDsf_spline* splineStrokeEnd);
	void				iDsf_select_strokeAfter					(SDsf* dsf, SDsf_spline* splineStrokeStart);
	void				iDsf_spline_compute						(SDsf_spline* spline, SXy_f64* pl, SXy_f64* po, SXy_f64* pr);
	bool				iDsf_isPointInRange						(SXy_f64* pt, SXy_f64* ul, SXy_f64* lr);
	void				iDsf_read_mousePosition					(SDsf* dsf, SDsf_hwnd* h);
