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




//////////
// Global variables for nodes
//////
	bool				glNode_initialized						= false;
	u32					gnNode_nextUniqueId						= 0;
	CRITICAL_SECTION	cs_nodeUniqueIdAccess;




//////////
// Forward declarations (some of the functions below call themselves)
//////
	// Temporarily moved to libsf.h

#endif // __NODE_H_

