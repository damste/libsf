//////////
//
// /libsf/source/vjr/test/vjr_test.cpp
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



// Forward declarations
void iVjr_test_parser(void);
void iVjr_test_nodes(void);




//////////
//
// Test functions used ad hoc for VJr development
//
//////
	void iVjr_test(void)
	{
		// Parser -- Dec.21.2015 RCH -- In progress
		iVjr_test_parser();

		// Nodes -- Dec.03.2015 RCH -- Appears to be working.  Test code is commented out, but still there
		iVjr_test_nodes();
	}




///////////
//
// Tests a parsing concept
//
//////
	char sample[] = "x = a + b";

	void iVjr_test_parser(void)
	{
		u32			lnId;
		SDatum		prog;
		SEM*		sem;
		SBitmap*	bmp;


		// Grab a unique ID for the image
		lnId = iGetNextUid();

		// Populate the program
		prog.data._s8	= sample;
		prog.length		= sizeof(sample) - 1;

		// Parse it into tokens
		sem = iSEM_allocate(true);
		iSEM_load_fromMemory(NULL, sem, &prog, true, false);

		// Nodify it
		iComps_chainLinkNodes(sem->firstLine->compilerInfo->firstComp);

		// Render for display
		bmp = iNode_renderBitmap(sem->firstLine->compilerInfo->firstComp->node);
//		iBmp_saveToDisk(bmp, "c:\\temp\\chain_link.bmp");
		JDebiC_bmp(bmp, true, lnId, true);
		// Parse using our algorithm
	}




///////////
//
// Tests the nodes.h/cpp functionality.  It creates a node structure with, depending on
// source code settings, some nodes extruded out from a center direction, and then renders
// the resulting node tree into a visible bitmap.
//
//////
	void iVjr_test_nodes(void)
	{
// 		s32			lnI;
// 		SBitmap*	bmp;
// 		SNode*		node;
// 		SNode*		nodeNew;
// 		SNodeProps	props[3];
// 		SNodeProps*	propRed;
// 		SNodeProps*	propWhite;
// 		SNodeProps*	propBlue;
// 		s8			buffer[_NODE_COUNT * 2 * 8];
// 
// 		// First level extrusion from node
// 		SComp		comp[_NODE_COUNT];
// 		SLine		line[_NODE_COUNT];
// 		SDatum		datum[_NODE_COUNT];
// 
// 		// Second level extrusion
// 		SComp		comp2[4];
// 		SLine		line2[4];
// 		SDatum		datum2[4];
// 
// 		// Third level extrusion
// 		SComp		comp3[4];
// 		SLine		line3[4];
// 		SDatum		datum3[4];
// 
// 		// Extra extrusions
// 		SComp		comp4[_NODE_COUNT];
// 		SLine		line4[_NODE_COUNT];
// 		SDatum		datum4[_NODE_COUNT];
// 
// 
// 		//////////
// 		// Initialize
// 		//////
// 			memset(&comp,	0, sizeof(comp));
// 			memset(&line,	0, sizeof(line));
// 			memset(&datum,	0, sizeof(datum));
// 			memset(&comp2,	0, sizeof(comp2));
// 			memset(&line2,	0, sizeof(line2));
// 			memset(&datum2,	0, sizeof(datum2));
// 			memset(&comp3,	0, sizeof(comp3));
// 			memset(&line3,	0, sizeof(line3));
// 			memset(&datum3,	0, sizeof(datum3));
// 			memset(&comp4,	0, sizeof(comp4));
// 			memset(&line4,	0, sizeof(line4));
// 			memset(&datum4,	0, sizeof(datum4));
// 
// 			memset(buffer,	0, sizeof(buffer));
// 			memset(&props,	0, sizeof(props));
// 
// 			propRed					= &props[0];
// 			propWhite				= &props[1];
// 			propBlue				= &props[2];
// 
// 			propRed->backColor		= pastelRedColor;
// 			propRed->foreColor		= blackColor;
// 			propRed->marginWidth	= 2;
// 			propRed->fillColor		= pastelRedColor;
// 			propRed->borderWidth	= 0;
// 			propRed->borderColor	= blackColor;
// 			propRed->font			= iFont_create(cgcFontName_windowTitleBar, 12, FW_BOLD, 1, 0);
// 
// 			propWhite->backColor	= silverColor;
// 			propWhite->foreColor	= blackColor;
// 			propWhite->marginWidth	= 2;
// 			propWhite->fillColor	= silverColor;
// 			propWhite->borderWidth	= 0;
// 			propWhite->borderColor	= grayColor;
// 
// 			propBlue->backColor		= pastelBlueColor;
// 			propBlue->foreColor		= blackColor;
// 			propBlue->marginWidth	= 2;
// 			propBlue->fillColor		= pastelBlueColor;
// 			propBlue->borderWidth	= 0;
// 			propBlue->borderColor	= blackColor;
// 
// 
// 
// 		//////////
// 		// Create center node
// 		//////
// 			iNode_create(&node, NULL);
// 
// 
// 		///////////
// 		// Extrude nodes out in every direction (except center)
// 		//////
// 			for (lnI = _NODE1_MIN; lnI <= _NODE1_MAX; lnI++)
// 			{
// 				// Extrude, except center
// 				if (lnI != _NODE_C1)					nodeNew = iNode_extrude(&node, lnI);
// 				else									nodeNew = node;
// 
// 				// Then hook it up...
// 				nodeNew->comp							= &comp[lnI];
// 				nodeNew->render_override				= propRed;
// 				comp[lnI].line							= &line[lnI];
// 				line[lnI].sourceCode					= &datum[lnI];
// 
// 				// ...to have its direction number
// 				datum[lnI].data_s8						= &buffer[0] + strlen(buffer);
// 				sprintf(buffer + strlen(buffer), "%d", lnI);
// 				datum[lnI].length						= strlen(datum[lnI].data_cs8);
// 				line[lnI].sourceCode_populatedLength	= datum[lnI].length;
// 				comp[lnI].length						= datum[lnI].length;
// 				comp[lnI].start							= 0;
// 				comp[lnI].iCode							= 0;
// 
// 				// Extend the NW node west
// 				if (lnI == _NODE_NW1)
// 				{
// 					// Change NW to blue
// 					nodeNew->render_override				= propBlue;
// 
// 					// Tests added for extrude, bump, and insert
// 					if (0)
// 					{
// 						// Extrude a new one
// 						nodeNew = iNode_extrude(&nodeNew, _NODE_W1);
// 
// 					} else if (0) {
// 						// Bump the existing one, adding a new one in-between.
// 						// Bumps southwest, anchored back to the southeast
// 						nodeNew = iNode_bump(&nodeNew, _NODE_SW1, _NODE_SE1);
// 
// 					} else if (1) {
// 						// Insert one between our new node and the middle
// 						nodeNew = iNode_insert(&nodeNew, _NODE_SE1);
// 					}
// 
// 					// Then hook it up...
// 					nodeNew->comp							= &comp4[lnI];
// 					nodeNew->render_override				= propBlue;
// 					comp4[lnI].line							= &line4[lnI];
// 					line4[lnI].sourceCode					= &datum4[lnI];
// 
// 					// ...to have its direction number
// 					datum4[lnI].data_s8						= &buffer[0] + strlen(buffer);
// 					sprintf(buffer + strlen(buffer), "inserted");
// 					datum4[lnI].length						= strlen(datum4[lnI].data_cs8);
// 					line4[lnI].sourceCode_populatedLength	= datum4[lnI].length;
// 					comp4[lnI].length						= datum4[lnI].length;
// 					comp4[lnI].start						= 0;
// 					comp4[lnI].iCode						= 0;
// 				}
// 			}
// 
// 
// 		//////////
// 		// Extrude more out on each corner
// 		//////
// 			for (lnI = 0; lnI < 4; lnI++)
// 			{
// 				// Extrude out NE,SE,SW,NW
// 				switch (lnI)
// 				{
// 					case 0:
// 						nodeNew = iNode_extrude(&node, _NODE_NE1);
// 						break;
// 					case 1:
// 						nodeNew = iNode_extrude(&node, _NODE_SE1);
// 						break;
// 					case 2:
// 						nodeNew = iNode_extrude(&node, _NODE_SW1);
// 						break;
// 					case 3:
// 						nodeNew = iNode_extrude(&node, _NODE_NW1);
// 						break;
// 				}
// 
// 				// Then hook it up...
// 				nodeNew->comp							= &comp2[lnI];
// 				nodeNew->render_override				= propWhite;
// 				comp2[lnI].line							= &line2[lnI];
// 				line2[lnI].sourceCode					= &datum2[lnI];
// 
// 				// ...to have its direction number
// 				datum2[lnI].data_s8						= &buffer[0] + strlen(buffer);
// 				sprintf(buffer + strlen(buffer), "%d", lnI);
// 				datum2[lnI].length						= strlen(datum2[lnI].data_cs8);
// 				line2[lnI].sourceCode_populatedLength	= datum2[lnI].length;
// 				comp2[lnI].length						= datum2[lnI].length;
// 				comp2[lnI].start						= 0;
// 				comp2[lnI].iCode						= 0;
// 			}
// 
// 
// 		//////////
// 		// Extrude more out on each corner
// 		//////
// 			for (lnI = 0; lnI < 4; lnI++)
// 			{
// 				// Extrude out NE,SE,SW,NW
// 				switch (lnI)
// 				{
// 					case 0:
// 						nodeNew = iNode_extrude(&node, _NODE_NE1);
// 						break;
// 					case 1:
// 						nodeNew = iNode_extrude(&node, _NODE_SE1);
// 						break;
// 					case 2:
// 						nodeNew = iNode_extrude(&node, _NODE_SW1);
// 						break;
// 					case 3:
// 						nodeNew = iNode_extrude(&node, _NODE_NW1);
// 						break;
// 				}
// 
// 				// Then hook it up...
// 				nodeNew->comp							= &comp3[lnI];
// 				nodeNew->render_override				= propBlue;
// 				comp3[lnI].line							= &line3[lnI];
// 				line3[lnI].sourceCode					= &datum3[lnI];
// 
// 				// ...to have its direction number
// 				datum3[lnI].data_s8						= &buffer[0] + strlen(buffer);
// 				sprintf(buffer + strlen(buffer), "%d", lnI);
// 				datum3[lnI].length						= strlen(datum3[lnI].data_cs8);
// 				line3[lnI].sourceCode_populatedLength	= datum3[lnI].length;
// 				comp3[lnI].length						= datum3[lnI].length;
// 				comp3[lnI].start						= 0;
// 				comp3[lnI].iCode						= 0;
// 			}
// 
// 
// 		//////////
// 		// Render
// 		//////
// 			// Dec.03.2015 RCH -- Appears to be working.
// 			bmp = iNode_renderBitmap(node);
// 			iBmp_saveToDisk(bmp, "c:\\temp\\node.bmp");
// 
	}
