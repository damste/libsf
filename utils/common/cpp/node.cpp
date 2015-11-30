//////////
//
// /libsf/utils/common/cpp/node.cpp
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




//////////
//
// Callback structure for SLL iteration
//
//////
	#include "node.h"








//////////
//
// Called to create a new node and attach it to the default nodes provided in each direction.
//
//////
	SNode* iNode_create(SNode** root, SNode* n_defaults[_NODE_COUNT])
	{
		s32			lnI;
		SNode*		nodeNew;


		// Make sure our environment is sane
		if ((nodeNew = (SNode*)malloc(sizeof(SNode))))
		{
			// Initialize
			memset(nodeNew, 0, sizeof(SNode));

			// Populate the target
			if (root && *root)
				*root = nodeNew;

			// Hook it up to anything it needs hooked up to
			if (n_defaults)
			{
				// Connect each node
				for (lnI = 0; lnI < (s32)_NODE_COUNT; lnI++)
					nodeNew->n[lnI] = n_defaults[lnI];
			}
		}

		// Indicate our status
		return(nodeNew);
	}




//////////
//
// Extrudes a node in the indicated direction (creates a new node in that way)
//
// Suppose you're on the + node, and you want to extrude southeast:
//
//     Before:
//            2
//           / \
//          1   +       <=== current node, extrude SE
//             / \
//            3   4
//
//     After:
//            2
//           / \
//          1   +
//             / \
//            3   4
//                 \
//                  5   <=== newly inserted node, extruded at the end of the chain
//
// Note:  If you need to insert a node between + and 4, then use iNode_bump() or iNode_insert_between()
//
//////
	// Note:  rootNode should point to the node to extrude from
	SNode* iNode_extrude(SNode** rootNode, u32 tnExtrudeDirection)
	{
		SNode*		nodeLast;
		SNode*		nodeNew;


		// Make sure the environment is sane
		if (!rootNode || !between(tnExtrudeDirection, _NODE_MIN, _NODE_MAX))
			return(NULL);

		// If nothing already exists there, just create it and it will become the central node
		if (!*rootNode)
			return(iNode_create(rootNode, NULL));

		// Descend down that direction
		for (nodeLast = *rootNode; nodeLast->n[tnExtrudeDirection]; )
			nodeLast = nodeLast->n[tnExtrudeDirection];

		// Add the new offshoot, and point back-and-forth to the last one
		nodeNew = iNode_create(rootNode, NULL);
		if (nodeNew)
		{
			// New points back to last
			nodeNew->n[gnNodeMirrors[tnExtrudeDirection]]	= nodeLast;

			// Last points forward to new
			nodeLast->n[tnExtrudeDirection]					= nodeNew;
		}

		// Indicate the new item
		return(nodeNew);
	}




///////////
//
// Bumps the node you're on over, inserting a new node in its place.
//
// Suppose you're on the + node, and you want to bump it southwest, anchoring to the northwest.
// By 
//
//     Before:                   Nodes to update in the bump:
//            2                    +---+---+        8---1---5
//           / \                   |       |        |       |
//          1   b                  +   +   +        4   9   2
//             / \                 |       |        |       |
//            3   4                +---+---+        7---3---6
//
// After bump, a total of five node connections need to be updated:
//
//            2
//           / \
//          1   5
//             /
//            b
//           / \
//          3   4
//
//         Node                       Operation
//     ------------        -----------------------------
//      2, node            a   to newNode
//      5, newNode         am  to node,  b   to bumpNode
//      b, bumpNode        bm  to new,   am  to NULL
//
//		Node directions:	a	-- anchor
//							am	-- anchor-mirror
//							b	-- bump
//							bm	-- bump-mirror
//
//////
	// Note:  The anchor direction would be the one which pointed up to 2 in the above example
	// Note:  The bump direction would be the southwest direction in the above example
	SNode* iNode_bump(SNode** rootNode, u32 tnBumpDirection, u32 tnAnchorDirection)
	{
		SNode*		node;
		SNode*		nodeNew;


		// Make sure the environment is sane
		if (!rootNode || !between(tnBumpDirection, _NODE_MIN, _NODE_MAX))
			return(NULL);

		// If nothing already exists there, just create it and it will become the central node
		if (!*rootNode)
			return(iNode_create(rootNode, NULL));

		// Grab the node
		node = *rootNode;

		// Create the new node
		nodeNew = iNode_create(rootNode, NULL);
		if (nodeNew)
		{
			// New points back to the anchor bumped had
			nodeNew->n[gnNodeMirrors[tnAnchorDirection]]	= node->n[gnNodeMirrors[tnAnchorDirection]];

			// Node anchors to new
			if (node->n[gnNodeMirrors[tnAnchorDirection]])
				node->n[gnNodeMirrors[tnAnchorDirection]]->n[tnAnchorDirection] = nodeNew;

			// Bumped no longer mirror-anchors back to node
			node->n[gnNodeMirrors[tnAnchorDirection]] = NULL;

			// Bumped back to new along bumped mirror
			node->n[gnNodeMirrors[tnBumpDirection]] = nodeNew;

			// New to node along bump
			nodeNew->n[tnBumpDirection] = node;
		}

		// Indicate our result
		return(node);
	}




//////////
//
// Creates a new node and inserts it between where node1 points to node2.
//
//////
	SNode* iNode_insert_between(SNode* node1, SNode* node2, u32 tnNode1Direction, u32 tnNode2Direction)
	{
		SNode*		n[_NODE_COUNT];
		SNode*		nodeNew;


		// Make sure our environment is sane
		if (!between(tnNode1Direction, _NODE_MIN, _NODE_MAX) || !between(tnNode2Direction, _NODE_MIN, _NODE_MAX) || tnNode1Direction == tnNode2Direction)
			return(NULL);

		// Initialize
		memset(&n[0], 0, sizeof(n));

		// Create and populate our new node
		if ((nodeNew = iNode_create(NULL, &n[0])))
		{
			// New points mirror-back to node1 and node2
			nodeNew->n[gnNodeMirrors[tnNode1Direction]] = node1;
			nodeNew->n[gnNodeMirrors[tnNode2Direction]]	= node2;

			// node1 points to new
			node1->n[tnNode1Direction]	= nodeNew;

			// node2 points to n32
			node2->n[tnNode2Direction]	= nodeNew;
		}

		// Indicate our status
		return(nodeNew);
	}




//////////
//
// Called to delete the entire node leg as indicated
//
//////
	void iNode_deleteAll_politely(SNode** root, SNode* nodeStopper1, SNode* nodeStopper2, bool tlDeleteSelf, SNodeFlags* nodeFlags)
	{
		s32				lnI, lnJ;
		SNode*			node;
		SNodeFlags		_nodeFlagsLocal;


		// Make sure we have something to act upon
		if (root && (node = *root) && node != nodeStopper1 && node != nodeStopper2)
		{

			//////////
			// Traverse the delete paths that should be deleted
			//////
				for (lnI = 0; lnI < (s32)_NODE_COUNT; lnI++)
				{
					// Set the directions
					if (nodeFlags->n[lnI] && node->n[lnI])
					{
						// Populate our goDirs directions from here
						for (lnJ = 0; lnJ < (s32)_NODE_COUNT; lnJ++)
							_nodeFlagsLocal.n[lnI] = (node->n[lnI]	!= nodeStopper1);

						// Go deeper
						iNode_deleteAll_politely(&node->n[lnI], nodeStopper1, nodeStopper2, true, &_nodeFlagsLocal);
					}
				}


			//////////
			// Delete the op if need be
			//////
				if (node->opData)
				{
					// Delete op chain
					iOp_politelyDelete(&node->opData->op, false);

					// Delete the variable chain
					if (node->opData->firstVariable)
						iVariable_politelyDelete_chain(&node->opData->firstVariable, true);
				}


			//////////
			// Delete self
			//////
				if (tlDeleteSelf)
				{
					*root = NULL;
					free(node);
				}

		}
	}




//////////
//
// Called to render a bitmap which is a visualization of the node
//
//////
	SBitmap* iNode_renderBitmap(SNode* node, SNodeFlags* nodeFlags, s32 tnMaxLength, f64 tfRodLength, s32 tnMarginWidth, s32 tnBorderWidth)
	{
		s32			lnI, lnIter_uid, lnWidth, lnHeight;
		POINTS		p;
		RECT		lrc;
		SBitmap*	bmp;
		SNodeProps	props[1];


		// Make sure our environment is sane
		bmp = NULL;
		if (node)
		{

			//////////
			// (Re-)Render everything
			//////
				// Grab a uid for render
				lnIter_uid = iGetNextUid();

				// Setup the render prop
				props->backColor	= whiteColor;
				props->foreColor	= blackColor;
				props->marginWidth	= tnMarginWidth;
				props->fillColor	= whiteColor;
				props->borderWidth	= tnBorderWidth;
				props->borderColor	= blackColor;
				props->rodColor		= grayColor;

				// Render this one
				iBmp_node_renderComp(node, 4, props, 1, lnIter_uid);

				// Kick off renderings in all directions from this root node
				for (lnI = 0; lnI < (s32)_NODE_COUNT; lnI++)
				{
					// Kick off this if we're supposed to go that way
					if (nodeFlags->n[lnI] && node->n[lnI])
					{
						// Indicate that we want to render everything out from there
						iiNode_renderBitmap(node->n[lnI], node, tnMaxLength, props, 1, lnIter_uid, true);
					}
				}


			//////////
			// Determine maximum size of the bitmap given its nodes
			//////
				// Grab a uid for get extents
				lnIter_uid = iGetNextUid();

				// Get our starting point
				SetRect(&lrc, 0, 0, 0, 0);
				p.x = 0;
				p.y = 0;
				iiNode_get_bitmapExtents(node, NULL, _NODE_SE, NULL, &lrc, p, tfRodLength, lnIter_uid, props, false);		// For initial computation, pretend we're coming down on a southeast node rod

				// Kick off a "get extents" on every rendered
				for (lnI = 0; lnI < (s32)_NODE_COUNT; lnI++)
				{
					// Kick off this if we're supposed to go that way
					if (nodeFlags->n[lnI] && node->n[lnI])
					{
						// Indicate that we want to render everything out from there
						iiNode_get_bitmapExtents(node->n[lnI], node, lnI, NULL, &lrc, p, tfRodLength, lnIter_uid, props, true);		// For initial computation, pretend we're coming down on a southeast node rod
					}
				}


			//////////
			// Render into the bmp
			//////
				bmp = iBmp_allocate();
				if (bmp)
				{
					// get our sizes
					lnWidth		= lrc.right - lrc.left;
					lnHeight	= lrc.bottom - lrc.top;

					// Create the bitmap
					iBmp_createBySize(bmp, lnWidth, lnHeight, 24);

					// Grab a uid for get extents
					lnIter_uid = iGetNextUid();

					// Get our starting point
					p.x			= (s16)-lrc.left;
					p.y			= (s16)-lrc.top;
					SetRect(&lrc, 0, 0, lnWidth, lnHeight);
					iiNode_get_bitmapExtents(node, NULL, _NODE_SE, bmp, &lrc, p, tfRodLength, lnIter_uid, props, false);		// For initial computation, pretend we're coming down on a southeast node rod

					// Kick off a render on every rendered
					for (lnI = 0; lnI < (s32)_NODE_COUNT; lnI++)
					{
						// Kick off this if we're supposed to go that way
						if (nodeFlags->n[lnI] && node->n[lnI])
						{
							// Indicate that we want to render everything out from there
							iiNode_get_bitmapExtents(node->n[lnI], node, lnI, bmp, &lrc, p, tfRodLength, lnIter_uid, props, true);		// For initial computation, pretend we're coming down on a southeast node rod
						}
					}
				}

		}

		// Indicate our rendered bitmap
		return(bmp);
	}

	// Note:  This is a 3D rendering, which populates a vector array for the iGrace() engine in node->grace
	// Note:  However, it also uses the node->bmp entries for the face bitmap
	void iiNode_renderGrace(SNode* node, SNode* nodeStopper, s32 tnMaxLength, SNodeProps props[], s32 tnPropsCount, u32 tnIter_uid, bool tlGoDeeper)
	{
		// This needs to be written
		debug_break;
	}

	// Note:  This is a 2D rendering, which renders into node->bmp
	void iiNode_renderBitmap(SNode* node, SNode* nodeStopper, s32 tnMaxLength, SNodeProps props[], s32 tnPropsCount, u32 tnIter_uid, bool tlGoDeeper)
	{
		s32		lnI;


		// Make sure we haven't already rendered this node
		if (node->iter_uid != tnIter_uid)
		{
			// Nope, render this one
			iBmp_node_renderComp(node, tnMaxLength, props, tnPropsCount, tnIter_uid);

			// Kick off all renderings from here
			if (tlGoDeeper)
			{
				for (lnI = 0; lnI < (s32)_NODE_COUNT; lnI++)
				{
					// Are we're supposed to go this way?
					if (node->n[lnI] && node->n[lnI] != nodeStopper && node->n[lnI]->iter_uid != tnIter_uid)
					{
						// Indicate that we want to render everything out from there
						iiNode_renderBitmap(node->n[lnI], nodeStopper, tnMaxLength, props, tnPropsCount, tnIter_uid, true);
					}
				}
			}
		}
	}

	// Note:  tfSquareSize is how far each side of the square should extend out from the connection point for the node lines
	void iiNode_get_bitmapExtents(SNode* node, SNode* nodeStopper, s32 tnArrivalDirection, SBitmap* bmp, RECT* rc, POINTS p_arrival, f64 tfRodLength, u32 tnIter_uid, SNodeProps* props, bool tlGoDeeper)
	{
		s32		lnI, lnWidth, lnHeight;
		f64		lfHalfHeight, lfHalfWidth;
		POINTS	p_origin, p_rodStart, p_rodEnd;
		RECT	lrc;


		// Make sure our environment is sane, and that we're not walking over ourselves
		if (node && node->bmp && node->iter_uid != tnIter_uid && between(tnArrivalDirection, (s32)_NODE_MIN, (s32)_NODE_MAX))
		{

			//////////
			// Compute this overall size
			/////
				lrc.left	= (node->bmp->bi.biWidth  / 2);
				lrc.top		= (node->bmp->bi.biHeight / 2);
				lrc.right	= lrc.left + node->bmp->bi.biWidth;
				lrc.bottom	= lrc.top  + node->bmp->bi.biHeight;

				// Simplify width and height
				lnWidth		= node->bmp->bi.biWidth;
				lnHeight	= node->bmp->bi.biHeight;


			//////////
			// Note:  rc grows in these directions, to encompass the entire creation:
			//
			//                top
			//                 -
			//
			//              +--+--+
			//   left -     +  +  +     + right
			//              +--+--+
			//
			//                 +
			//               bottom
			//////
				// Based on the arrival direction of the rod, increase rc's extents if needed
				switch (tnArrivalDirection)
				{
					case _NODE_N0:
					case _NODE_N1:
					case _NODE_N2:
						rc->left	= min(rc->left,		p_arrival.x - lrc.left);					// Connecting point:  +--+--+
						rc->top		= min(rc->top,		p_arrival.y - lnHeight);					//                    +  +  +
						rc->right	= max(rc->right,	p_arrival.x - lrc.left + lnWidth);			//                    +--o--+
						SetRect(&node->rc, p_arrival.x - lrc.left, p_arrival.y - lnHeight, p_arrival.x - lrc.left + lnWidth, p_arrival.y);
						p_origin.x	= p_arrival.x;
						p_origin.y	= p_arrival.y - (s16)lnHeight + (s16)lrc.top;
						break;

					case _NODE_E0:
					case _NODE_E1:
					case _NODE_E2:
						rc->top		= min(rc->top,		p_arrival.y - lrc.top);						// Connecting point:  +--+--+
						rc->right	= max(rc->right,	p_arrival.x + lnWidth);						//                    o  +  +
						rc->bottom	= max(rc->bottom,	p_arrival.y - lrc.top + lnHeight);			//                    +--+--+
						SetRect(&node->rc, p_arrival.x, p_arrival.y - lrc.top, p_arrival.x + lnWidth, p_arrival.y - lrc.top + lnHeight);
						p_origin.x	= p_arrival.x + (s16)lrc.left;
						p_origin.y	= p_arrival.y;
						break;

					case _NODE_C0:
					case _NODE_C1:
					case _NODE_C2:
						// Here we use the same as _NODE_S for 2D rendering							// Connecting point:  +--+--+	// Though we use the p spot for the connection
																									//                    +  o +
																									//                    +--p--+
					case _NODE_S0:
					case _NODE_S1:
					case _NODE_S2:
						rc->left	= min(rc->left,		p_arrival.x - lrc.left);					// Connecting point:  +--o--+
						rc->right	= max(rc->right,	p_arrival.x - lrc.left + lnWidth);			//                    +  +  +
						rc->bottom	= max(rc->bottom,	p_arrival.y + lnHeight);					//                    +--+--+
						SetRect(&node->rc, p_arrival.x - lrc.left, p_arrival.y, p_arrival.x - lrc.left + lnWidth, p_arrival.y + lnHeight);
						p_origin.x	= p_arrival.x;
						p_origin.y	= p_arrival.y + (s16)lrc.top;
						break;

					case _NODE_W0:
					case _NODE_W1:
					case _NODE_W2:
						rc->top		= min(rc->top,		p_arrival.y - lrc.top);						// Connecting point:  +--+--+
						rc->left	= min(rc->right,	p_arrival.x - lnWidth);						//                    +  +  o
						rc->bottom	= max(rc->bottom,	p_arrival.y - lrc.top + lnHeight);			//                    +--+--+
						SetRect(&node->rc, p_arrival.x - lnWidth, p_arrival.y - lrc.top, p_arrival.x, p_arrival.y - lrc.top + lnHeight);
						p_origin.x	= p_arrival.x - (s16)lnWidth + (s16)lrc.left;
						p_origin.y	= p_arrival.y;
						break;

					case _NODE_NE0:
					case _NODE_NE1:
					case _NODE_NE2:
						rc->right	= max(rc->right,	p_arrival.x + lnWidth);						// Connecting point:  +--+--+
						rc->top		= min(rc->top,		p_arrival.y - lnHeight);					//                    +  +  +
																									//                    o--+--+
						SetRect(&node->rc, p_arrival.x, p_arrival.y - lnHeight, p_arrival.x + lnWidth, p_arrival.y);
						p_origin.x	= p_arrival.x + (s16)lrc.left;
						p_origin.y	= p_arrival.y - (s16)lnHeight + (s16)lrc.top;
						break;

					case _NODE_SE0:
					case _NODE_SE1:
					case _NODE_SE2:
						rc->right	= max(rc->right,	p_arrival.x + lnWidth);						// Connecting point:  o--+--+
						rc->bottom	= max(rc->bottom,	p_arrival.y + lnHeight);					//                    +  +  +
																									//                    +--+--+
						SetRect(&node->rc, p_arrival.x, p_arrival.y, p_arrival.x + lnWidth, p_arrival.y + lnHeight);
						p_origin.x	= p_arrival.x + (s16)lrc.left;
						p_origin.y	= p_arrival.y + (s16)lrc.top;
						break;

					case _NODE_SW0:
					case _NODE_SW1:
					case _NODE_SW2:
						rc->left	= min(rc->left,		p_arrival.x - lnWidth);						// Connecting point:  +--+--o
						rc->bottom	= max(rc->right,	p_arrival.y + lnHeight);					//                    +  +  +
																									//                    +--+--+
						SetRect(&node->rc, p_arrival.x - lnWidth, p_arrival.y, p_arrival.x, p_arrival.y + lnHeight);
						p_origin.x	= p_arrival.x - (s16)lnWidth + (s16)lrc.left;
						p_origin.y	= p_arrival.y + (s16)lrc.top;
						break;

					case _NODE_NW0:
					case _NODE_NW1:
					case _NODE_NW2:
						rc->left	= min(rc->left,		p_arrival.x - lnWidth);						// Connecting point:  +--+--+
						rc->top		= min(rc->top,		p_arrival.y - lnHeight);					//                    +  +  +
																									//                    +--+--o
						SetRect(&node->rc, p_arrival.x - lnWidth, p_arrival.y - lnHeight, p_arrival.x, p_arrival.y);
						p_origin.x	= p_arrival.x - (s16)lnWidth  + (s16)lrc.left;
						p_origin.y	= p_arrival.y - (s16)lnHeight + (s16)lrc.top;
						break;
				}

				// Set the iteration uid
				node->iter_uid = tnIter_uid;

				// Render the rectangle (if need be)
				if (bmp)
					iBmp_bitBlt(bmp, &node->rc, node->bmp);

				// Compute distances from the origin to side and top, which then can extend to all 8 points through gnNodeRodeMaps[]
				lfHalfHeight	= (f64)(lnHeight / 2.0);
				lfHalfWidth		= (f64)(lnWidth  / 2.0);


			//////////
			// Kick off the nodes in each direction
			//////
				if (tlGoDeeper)
				{
					// Iterate off in all directions
					for (lnI = 0; lnI < (s32)_NODE_COUNT; lnI++)
					{
						// Are we're supposed to go this way?
						if (node->n[lnI] && node->n[lnI] != nodeStopper && node->n[lnI]->iter_uid != tnIter_uid)
						{
							// Determine the ending point at the connecting rod
							p_rodStart.x	= p_origin.x	+ (s32)(gsfNodeRodMaps[lnI].x * lfHalfWidth);
							p_rodStart.y	= p_origin.y	+ (s32)(gsfNodeRodMaps[lnI].y * lfHalfHeight);
							p_rodEnd.x		= p_rodStart.x	+ (s32)(gsfNodeRodMaps[lnI].x * tfRodLength);
							p_rodEnd.y		= p_rodStart.y	+ (s32)(gsfNodeRodMaps[lnI].y * tfRodLength);

							// Draw the rod between this node and the next
							iBmp_drawArbitraryLine(bmp, p_rodStart.x, p_rodStart.y, p_rodEnd.x, p_rodEnd.y, props->rodColor);

							// Fill in little connecting bullets at each end
							iBmp_drawBullet(bmp,	p_rodStart.x,	p_rodStart.y,	props->borderColor);
							iBmp_drawBullet(bmp,	p_rodEnd.x,		p_rodEnd.y,		props->borderColor);

							// Indicate that we want to render everything out from there
							iiNode_get_bitmapExtents(node->n[lnI], nodeStopper, lnI, bmp, rc, p_rodEnd, tfRodLength, tnIter_uid, props, true);
						}
					}
				}
		}
	}

	void iiNode_get_graceExtents(SNode* node, SNode* nodeStopper, s32 tnArrivalDirection, SBitmap* bmp, SGraceLine* line, POINTS p_arrival, f64 tfRodLength, u32 tnIter_uid, SNodeProps* props, bool tlGoDeeper)
	{
		// This needs written
		debug_break;
	}