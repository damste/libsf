//////////
//
// /libsf/utils/common/cpp/node.h
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
// Version 0.10
// Copyright (c) 2015 by Rick C. Hodgin
//////
// Last update:
//     Nov.23.2015
//////
// Change log:
//     Nov.23.2015 - Initial creation
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
//   _   _             _       
//  | \ | |           | |      
//  |  \| |  ___    __| |  ___ 
//  | . ` | / _ \  / _` | / _ \
//  | |\  || (_) || (_| ||  __/
//  |_| \_| \___/  \__,_| \___|
//    Node -- Multi-directional node algorithms (picture a cube, navigate to origin, every corner, line segment center point, and plane center point)
//////////

#ifndef __NODE_H_
#define __NODE_H_




struct SFont;
struct SBitmap;
struct SSubInstr;
struct SGraceRect;
struct SGraceLine;




//////////
// Constants
//////
	const u32									_NODE_MIN		= 0;
	const u32									_NODE0_MIN		= 0;
	const u32		_NODE_N0										= 0;
	const u32		_NODE_E0										= 1;
	const u32		_NODE_S0										= 2;
	const u32		_NODE_W0										= 3;
	const u32		_NODE_NE0										= 4;
	const u32		_NODE_SE0										= 5;
	const u32		_NODE_SW0										= 6;
	const u32		_NODE_NW0										= 7;
	const u32		_NODE_C0										= 8;
	const u32									_NODE0_MAX		= 8;
	const u32									_NODE1_MIN		= 9;
	const u32		_NODE_N											= 9;
	const u32		_NODE_N1										= 9;
	const u32		_NODE_E											= 10;
	const u32		_NODE_E1										= 10;
	const u32		_NODE_S											= 11;
	const u32		_NODE_S1										= 11;
	const u32		_NODE_W											= 12;
	const u32		_NODE_W1										= 12;
	const u32		_NODE_NE										= 13;
	const u32		_NODE_NE1										= 13;
	const u32		_NODE_SE										= 14;
	const u32		_NODE_SE1										= 14;
	const u32		_NODE_SW										= 15;
	const u32		_NODE_SW1										= 15;
	const u32		_NODE_NW										= 16;
	const u32		_NODE_NW1										= 16;
	const u32		_NODE_C											= 17;
	const u32		_NODE_C1										= 17;
	const u32									_NODE1_MAX		= 17;
	const u32									_NODE2_MIN		= 18;
	const u32		_NODE_N2										= 18;
	const u32		_NODE_E2										= 19;
	const u32		_NODE_S2										= 20;
	const u32		_NODE_W2										= 21;
	const u32		_NODE_NE2										= 22;
	const u32		_NODE_SE2										= 23;
	const u32		_NODE_SW2										= 24;
	const u32		_NODE_NW2										= 25;
	const u32		_NODE_C2										= 26;
	const u32									_NODE2_MAX		= 27;
	const u32									_NODE_MAX		= 27;
	const u32									_NODE_COUNT		= 27;
	const u32									_NODE0_COUNT	= 9;
	const u32									_NODE1_COUNT	= 9;
	const u32									_NODE2_COUNT	= 9;
//////////
// Source code shortcuts:
// 	case _NODE_N0
// 	case _NODE_E0
// 	case _NODE_S0
// 	case _NODE_W0
// 	case _NODE_SW0
// 	case _NODE_SE0
// 	case _NODE_NW0
// 	case _NODE_NE0
// 	case _NODE_C0
//
// 	case _NODE_N:	// Aliased to: _NODE_N1
// 	case _NODE_E	// Aliased to: _NODE_E1
// 	case _NODE_S	// Aliased to: _NODE_S1
// 	case _NODE_W	// Aliased to: _NODE_W1
// 	case _NODE_SW	// Aliased to: _NODE_SW1
// 	case _NODE_SE	// Aliased to: _NODE_SE1
// 	case _NODE_NW	// Aliased to: _NODE_NW1
// 	case _NODE_NE	// Aliased to: _NODE_NE1
// 	case _NODE_C	// Aliased to: _NODE_C1
//
// 	case _NODE_N2
// 	case _NODE_E2
// 	case _NODE_S2
// 	case _NODE_W2
// 	case _NODE_SW2
// 	case _NODE_SE2
// 	case _NODE_NW2
// 	case _NODE_NE2
// 	case _NODE_C2
//////

	// A translation matrix 
	const u32	gnNodeMirrors[_NODE_COUNT] =
	{
	//	Mirror...				...of slot
		_NODE_S2,			// _NODE_N0
		_NODE_W2,			// _NODE_E0
		_NODE_N2,			// _NODE_S0
		_NODE_E2,			// _NODE_W0
		_NODE_SW2,			// _NODE_NE0
		_NODE_NW2,			// _NODE_SE0
		_NODE_NE2,			// _NODE_SW0
		_NODE_SE2,			// _NODE_NW0
		_NODE_C2,			// _NODE_C0

		_NODE_S,			// _NODE_N		// Same as _NODE_S1, _NODE_N1
		_NODE_W,			// _NODE_E		// Same as _NODE_W1, _NODE_E1
		_NODE_N,			// _NODE_S		// Same as _NODE_N1, _NODE_S1
		_NODE_E,			// _NODE_W		// Same as _NODE_E1, _NODE_W1
		_NODE_SW,			// _NODE_NE		// Same as _NODE_SW1, _NODE_NE1
		_NODE_NW,			// _NODE_SE		// Same as _NODE_NW1, _NODE_SE1
		_NODE_NE,			// _NODE_SW		// Same as _NODE_NE1, _NODE_SW1
		_NODE_SE,			// _NODE_NW		// Same as _NODE_SE1, _NODE_NW1
		_NODE_C,			// _NODE_C		// Same as _NODE_C1, _NODE_C1		// Note:  Doesn't really have a mirror

		_NODE_S0,			// _NODE_N2
		_NODE_W0,			// _NODE_E2
		_NODE_N0,			// _NODE_S2
		_NODE_E0,			// _NODE_W2
		_NODE_SW0,			// _NODE_NE2
		_NODE_NW0,			// _NODE_SE2
		_NODE_NE0,			// _NODE_SW2
		_NODE_SE0,			// _NODE_NW2
		_NODE_C0			// _NODE_C2
	};


//////////
//
// Nodes provide a multi-ported way to hook things up.  They are intended
// to be used with components (SComp), which provide their context and all
// information they'll display.  As such, nodes is dependent upon the
// iBmp_node_renderComp() function, which renders the graphical portion of
// the node.  If you do not want to use the default rendering algorithm,
// then you can replace it with whatever you need.
//
// General 27-way node cube.  Picture a square.  At all cardinal and
// ordinal points, there are node extending out, plus one in the middle.
// Repeat this for three cross-sections of the cube, one at the front,
// one at the back, and one directly in the middle:
//
//                   parent
//                     n
//             nw      |      ne
//               \     |     /
//                +----+----+
//                |         |
//         w ---- +    o    + ---- e
//                |  center |
//      prev      +----+----+      next
//               /     |     \
//             sw      |      se
//           left      s      right
//                    down
//
// Now picture that plane placed into a three-way system.  Imagine
// looking at the image above from the e side, looking toward w:
//
//                                              Perspective view:
//                                            2          1            0
//            Side-on-view:          nw2----  +          + nw         +  ----nw0
//            2    1    0                     |\         |\           |\
//            +    +    +             w2----  + +        + + n        + +  ----n0
//            |    |    |                     |  \       |  \         |  \
//            o    o    o            sw2----  + o +      + o + ne     + o +  ----ne0
//            |    |    |                      \  |       \  |         \  |
//            +    +    +               s2----  + +        + + e        + +  ----e0
//                                               \|         \|           \|
//                                       se2----  +          + se         +  ----se0
//
// This yields a node array configuration that has 9 nodes per plane,
// with a three-way configuration constructing a perfect cube, resulting
// in 27-separate nodes.  These are called:
//
//		C0, N0, NE0, E0, SE0, S0, SW0, W0, NW0
//		C1, N1, NE1, E1, SE1, S1, SW1, W1, NW1		// Aliased to:  C, N, NE, E, SE, S, SW, W, NW
//		C2, N2, NE2, E2, SE2, S2, SW2, W2, NW2
//
//////
	// Go and map directions (from the current node)
	// Note:  The + origin is at the logical center of the screen
	struct SNodeRodMaps
	{
		// Relates to screen coordinates with a z-axis added in:
		f64		x;			//  o-y					// y is negative going up, positive going down
		f64		y;			//  |   .o+z			// z is positive going away, negative coming toward
		f64		z;			//  | .' 
	};						//  +'----o+x			// x is positive going right, negative going left
	///////
	// Holds the default rod directions for each connection based on a cube centered at C1 being at (0,0,0) and oriented normally (C0 away, C2 toward)
	//////////
			// Constant rod map values multipliers
			SNodeRodMaps gsfNodeRodMaps[_NODE_COUNT] =
			{	//	  x		  y		  z
				//	-----	-----	-----
				{	0.0,	-1.0,	1.0		},		// _NODE_N0		// Away
				{	1.0,	0.0,	1.0		},		// _NODE_E0
				{	0.0,	1.0,	1.0		},		// _NODE_S0
				{	-1.0,	0.0,	1.0		},		// _NODE_W0
				{	1.0,	-1.0,	1.0		},		// _NODE_NE0
				{	1.0,	1.0,	1.0		},		// _NODE_SE0
				{	-1.0,	1.0,	1.0		},		// _NODE_SW0
				{	-1.0,	-1.0,	1.0		},		// _NODE_NW0
				{	0.0,	0.0,	1.0		},		// _NODE_C0

				{	0.0,	-1.0,	0.0		},		// _NODE_N		// Same as _NODE_N1
				{	1.0,	0.0,	0.0		},		// _NODE_E		// Same as _NODE_E1
				{	0.0,	1.0,	0.0		},		// _NODE_S		// Same as _NODE_S1
				{	-1.0,	0.0,	0.0		},		// _NODE_W		// Same as _NODE_W1
				{	1.0,	-1.0,	0.0		},		// _NODE_NE		// Same as _NODE_NE1
				{	1.0,	1.0,	0.0		},		// _NODE_SE		// Same as _NODE_SE1
				{	-1.0,	1.0,	0.0		},		// _NODE_SW		// Same as _NODE_SW1
				{	-1.0,	-1.0,	0.0		},		// _NODE_NW		// Same as _NODE_NW1
				{	0.0,	0.0,	0.0		},		// _NODE_C		// Same as _NODE_C1

				{	0.0,	-1.0,	-1.0	},		// _NODE_N2		// Toward
				{	1.0,	0.0,	-1.0	},		// _NODE_E2
				{	0.0,	1.0,	-1.0	},		// _NODE_S2
				{	-1.0,	0.0,	-1.0	},		// _NODE_W2
				{	1.0,	-1.0,	-1.0	},		// _NODE_NE2
				{	1.0,	1.0,	-1.0	},		// _NODE_SE2
				{	-1.0,	1.0,	-1.0	},		// _NODE_SW2
				{	-1.0,	-1.0,	-1.0	},		// _NODE_NW2
				{	0.0,	0.0,	-1.0	}		// _NODE_C2
			};


	struct SNodeFlags
	{
		bool			n[_NODE_COUNT];									// A flag relates to each node direction, whether or not it should be traversed / processed / whatever
	};
	//////
	// Holds the default flag set that allows traversal in all directions
	//////////
			// Allow full traversal
			SNodeFlags gsfNodeFlags_all =
			{
				true,	// _NODE_N0
				true,	// _NODE_E0
				true,	// _NODE_S0
				true,	// _NODE_W0
				true,	// _NODE_NE0
				true,	// _NODE_SE0
				true,	// _NODE_SW0
				true,	// _NODE_NW0
				true,	// _NODE_C0

				true,	// _NODE_N		// Same as _NODE_N1
				true,	// _NODE_E		// Same as _NODE_E1
				true,	// _NODE_S		// Same as _NODE_S1
				true,	// _NODE_W		// Same as _NODE_W1
				true,	// _NODE_NE		// Same as _NODE_NE1
				true,	// _NODE_SE		// Same as _NODE_SE1
				true,	// _NODE_SW		// Same as _NODE_SW1
				true,	// _NODE_NW		// Same as _NODE_NW1
				true,	// _NODE_C		// Same as _NODE_C1

				true,	// _NODE_N2
				true,	// _NODE_E2
				true,	// _NODE_S2
				true,	// _NODE_W2
				true,	// _NODE_NE2
				true,	// _NODE_SE2
				true,	// _NODE_SW2
				true,	// _NODE_NW2
				true	// _NODE_C2
			};


	struct SNodeProps
	{
		SBgra			backColor;										// Text back color, 
		SBgra			foreColor;										// Text fore color, typically black
		s32				marginWidth;									// Width between text and the inner border
		SBgra			fillColor;										// Fill color, typically white
		s32				borderWidth;									// Width of the border in pixels
		SBgra			borderColor;									// Color of the border, typically black
		SBgra			rodColor;										// Connecting rods

		// Font settings
		SFont*			font;											// If non-NULL, font override to use, otherwise uses default font
	};

	const SBgra		node_whiteColor			= { rgba(255, 255, 255, 255) };
	const SBgra		node_silverColor		= { rgba(225, 225, 225, 255) };
	const SBgra		node_grayColor			= { rgba(192, 192, 192, 255) };
	const SBgra		node_blackColor			= { rgba(0, 0, 0, 255) };
	const SBgra		node_pastelYellowColor	= { rgba(255, 255, 128, 255) };
	const SBgra		node_pastelRedColor		= { rgba(255, 200, 200, 255) };
	const SBgra		node_pastelOrangeColor	= { rgba(255, 205, 155, 255) };
	const SBgra		node_pastelGreenColor	= { rgba(200, 255, 200, 255) };
	const SBgra		node_pastelBlueColor	= { rgba(215, 215, 255, 255) };

	SNodeProps	gsNodeProps_defaults[9] =
	{
								//	BackColor					Forecolor				Margin		FillColor					Border		BorderColor			RodColor			Font
		/* gsPropWhite */		{	node_whiteColor,			node_blackColor,		2,			node_whiteColor,			1,			node_grayColor,		node_grayColor,		NULL	},
		/* gsPropSilver */		{	node_silverColor,			node_blackColor,		2,			node_silverColor,			0,			node_grayColor,		node_grayColor,		NULL	},
		/* gsPropGray*/			{	node_grayColor,				node_blackColor,		2,			node_grayColor,				0,			node_blackColor,	node_grayColor,		NULL	},
		/* gsPropRed */			{	node_pastelRedColor,		node_blackColor,		2,			node_pastelRedColor,		0,			node_blackColor,	node_grayColor,		NULL	},
		/* gsPropBlue */		{	node_pastelBlueColor,		node_blackColor,		2,			node_pastelBlueColor,		0,			node_blackColor,	node_grayColor,		NULL	},
		/* gsPropGreen */		{	node_pastelGreenColor,		node_blackColor,		2,			node_pastelGreenColor,		0,			node_blackColor,	node_grayColor,		NULL	},
		/* gsPropYellow */		{	node_pastelYellowColor,		node_blackColor,		2,			node_pastelYellowColor,		0,			node_blackColor,	node_grayColor,		NULL	},
		/* gsPropOrange */		{	node_pastelOrangeColor,		node_blackColor,		2,			node_pastelOrangeColor,		0,			node_blackColor,	node_grayColor,		NULL	},
		/* gsPropBlack */		{	node_blackColor,			node_whiteColor,		2,			node_blackColor,			0,			node_grayColor,		node_grayColor,		NULL	},
	};

	// NodeProps defaults to use for common coloring themes			// Suggestion for use:
	SNodeProps*	gsPropSilver	= &gsNodeProps_defaults[0];			// Normal
	SNodeProps*	gsPropWhite		= &gsNodeProps_defaults[1];			// Normal
	SNodeProps*	gsPropGray		= &gsNodeProps_defaults[2];			// Processed / completed
	SNodeProps*	gsPropRed		= &gsNodeProps_defaults[3];			// Error
	SNodeProps*	gsPropBlue		= &gsNodeProps_defaults[4];			// Extra info
	SNodeProps*	gsPropGreen		= &gsNodeProps_defaults[5];			// Optional highlighted
	SNodeProps*	gsPropYellow	= &gsNodeProps_defaults[6];			// Optional highlighted
	SNodeProps*	gsPropOrange	= &gsNodeProps_defaults[7];			// Optional highlighted
	SNodeProps*	gsPropBlack		= &gsNodeProps_defaults[8];			// Highlighted

	// Holds render information for the node
	struct SNodeRender
	{
		SBitmap*	bmp;											// An image for this node's content
		RECT		rc;												// Render rc as of last computation
		u32			iter_uid;										// The last iteration this item was updated
		s32			propsIndex;										// An index into the properties for how this node is configured

		// For 3D rendering using iGrace()
		SGraceRect*	grace;											// An array of vectors outlining everything to render the node centered around (0,0,0)
		s32			graceCount;										// The number of elements in grace
	};

	struct SNode
	{
		SNode*			n[_NODE_COUNT];									// Offshoot nodes
		u32				uid;											// Unique ID for this node

		// Related info
		SComp*			comp;											// The component this node relates to
		SSubInstr*		opData;											// When used as for processing ops

		// Extra/associated data
		void*			extraData;										// General purpose data
		union {
			uptr		_extraData_deleteFunc;							// Function to call when deleting
			void		(*extraData_deleteFunc)(SNode* node);
		};

		// For graphics rendering
		SNodeRender		render;
		SNodeProps*		render_override;								// Use these properties instead of those indicated by render (used for highlighting explicit nodes)
	};




//////////
// Global variables for nodes
//////
	bool				glNode_initialized						= false;




//////////
// Forward declarations (some of the functions below call themselves)
//////
	void					iNode_init									(void);
	SNode*					iNode_create								(SNode** root, SComp* comp = NULL, SNode* n_defaults[_NODE_COUNT] = NULL);
	SNode*					iNode_extrude								(SNode** root, s32 tnExtrudeDirection);
	SNode*					iNode_bump									(SNode** root, s32 tnBump/*BumpDirection*/, s32 tnAnchor/*AnchorDirection*/);
	SNode*					iNode_insert								(SNode** root, s32 tnDirection);
	void					iNode_delete								(SNode** root, bool tlDeleteSelf = true);
	void					iNode_orphanize								(SNode** root);
	void					iNode_deleteAll_politely					(SNode** root, SNode* nodeStopper, SNode* nodeStopper2, bool tlDeleteSelf, SNodeFlags* nodeFlags);

	// Bitmap
	SBitmap*				iNode_renderBitmap							(SNode* node, s32 tnMaxTokenLength = 6, s32 tnMaxOverallLength = 12, f64 tfRodLength = 8.0, s32 tnMarginWidth = 2, s32 tnBorderWidth = 0, bool tlIncludeExtraInfo = false,						bool tlGoDeeper = true, SNodeFlags* nodeFlags = &gsfNodeFlags_all, bool tlDeeperNodesExtendInAllDirections = true);
	void					iiNode_renderBitmap							(SNode* node, SNode* nodeStopper1, SNode* nodeStopper2, s32 tnMaxTokenLength, s32 tnMaxOverallLength, SNodeProps props[], s32 tnPropsCount, u32 tnIter_uid, bool tlIncludeExtraInfo,			bool tlGoDeeper = true, SNodeFlags* nodeFlags = &gsfNodeFlags_all, bool tlDeeperNodesExtendInAllDirections = true);
	void					iiNode_get_bitmapExtents					(SNode* node, SNode* nodeStopper1, SNode* nodeStopper2, s32 tnArrivalDirection, SBitmap* bmp, RECT* rc, POINTS p_anchor, POINTS p_arrival, f64 tfRodLength, u32 tnIter_uid, SNodeProps* props,	bool tlGoDeeper = true, SNodeFlags* nodeFlags = &gsfNodeFlags_all, bool tlDeeperNodesExtendInAllDirections = true);

// 	// OpenGL
// 	void					iiNode_renderGrace							(SNode* node, SNode* nodeStopper1, SNode* nodeStopper2, s32 tnMaxTokenLength, s32 tnMaxOverallLength, SNodeProps props[], s32 tnPropsCount, u32 tnIter_uid,								bool tlGoDeeper = true, SNodeFlags* nodeFlags = &gsfNodeFlags_all, bool tlDeeperNodesExtendInAllDirections = true);
// 	void					iiNode_get_graceExtents						(SNode* node, SNode* nodeStopper1, SNode* nodeStopper2, s32 tnArrivalDirection, SBitmap* bmp, SGraceLine* line, POINTS p_arrival, f64 tfRodLength, u32 tnIter_uid, SNodeProps* props,	bool tlGoDeeper = true, SNodeFlags* nodeFlags = &gsfNodeFlags_all, bool tlDeeperNodesExtendInAllDirections = true);

#endif // __NODE_H_

