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
		SNode*		n[_NODE_COUNT];
		SComp		comp[_NODE_COUNT];
		SLine		line[_NODE_COUNT];
		SDatum		datum[_NODE_COUNT];
		SBitmap*	bmp;
		s8			buffer[_NODE_COUNT * 8];


return;
		///////////
		// Create a center node
		//////
			memset(&n, 0, sizeof(n));
			memset(&buffer, 0, sizeof(buffer));
			n[_NODE_C] = iNode_create(&n[0], NULL);


		///////////
		// Extrude nodes in every direction
		//////
			for (lnI = _NODE1_MIN; lnI < _NODE1_MAX; lnI++)
			{
				// Create a node in each direction
				if (lnI != _NODE_C)
					n[lnI] = iNode_extrude(&n[_NODE_C], lnI);

				// Hook it up to something
				n[lnI]->comp			= &comp[lnI];
				comp[lnI].line			= &line[lnI];
				line[lnI].sourceCode	= &datum[lnI];
				datum[lnI].data_s8		= &buffer[0] + strlen(buffer);
				sprintf(buffer + strlen(buffer), "%03d", lnI);
				datum[lnI].length		= strlen(datum[lnI].data_cs8);
			}


		//////////
		// Render
		//////
			bmp = iNode_renderBitmap(n[_NODE_C]);
			iBmp_saveToDisk(bmp, "c:\\temp\\node.bmp");
	}
