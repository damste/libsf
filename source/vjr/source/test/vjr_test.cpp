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




//////////
//
// Test functions used ad hoc for VJr development
//
//////
	void iVjr_test(void)
	{
		s32			lnI;
		SBitmap*	bmp;
		SNode*		node;
		SNode*		nodeNew;
		SNode*		n[_NODE_COUNT];
		SComp		comp[_NODE_COUNT];
		SLine		line[_NODE_COUNT];
		SDatum		datum[_NODE_COUNT];
		s8			buffer[_NODE_COUNT * 8];


// TODO:  Dec.01.2015 RCH -- This process is working, except the extents it's retrieving are not correct, the height is more than doubled
return;
		//////////
		// Initialize
		//////
			memset(&n,		0, sizeof(n));
			memset(&comp,	0, sizeof(comp));
			memset(&line,	0, sizeof(line));
			memset(&datum,	0, sizeof(datum));
			memset(buffer,	0, sizeof(buffer));


		//////////
		// Create center node
		//////
			iNode_create(&node, NULL);


		///////////
		// Extrude nodes out in every direction (except center)
		//////
			for (lnI = _NODE1_MIN; lnI <= _NODE1_MAX; lnI++)
			{
				// Extrude, except center
				if (lnI != _NODE_C1)					nodeNew = iNode_extrude(&node, lnI);
				else									nodeNew = node;

				// Then hook it up...
				nodeNew->comp							= &comp[lnI];
				comp[lnI].line							= &line[lnI];
				line[lnI].sourceCode					= &datum[lnI];

				// ...to have its direction number
				datum[lnI].data_s8						= &buffer[0] + strlen(buffer);
				sprintf(buffer + strlen(buffer), "%03d", lnI);
				datum[lnI].length						= strlen(datum[lnI].data_cs8);
				line[lnI].sourceCode_populatedLength	= datum[lnI].length;
				comp[lnI].length						= datum[lnI].length;
				comp[lnI].start							= 0;
				comp[lnI].iCode							= 0;
			}


		//////////
		// Render
		//////
			bmp = iNode_renderBitmap(node);
			iBmp_saveToDisk(bmp, "c:\\temp\\node.bmp");

	}
