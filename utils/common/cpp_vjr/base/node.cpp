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
// Copyright (c) 2015-2017 by Rick C. Hodgin
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
	#include "..\include\node.h"








//////////
// Called once at startup to initialize the default SNodeProps for rendering
//////
	void iNode_init(void)
	{
		if (!glNode_initialized)
		{

			// Indicate we've initialized
			glNode_initialized = true;
		}
	}




//////////
//
// Called to create a new node and attach it to the default nodes provided in each direction.
//
//////
	SNode* iNode_create(SNode** root, SComp* comp, SNode* n_defaults[_NODE_COUNT])
	{
		s32			lnI;
		SNode*		nodeNew;


		// Make sure our environment is sane
		if ((nodeNew = (SNode*)malloc(sizeof(SNode))))
		{
			// Initialize
			memset(nodeNew, 0, sizeof(SNode));

			// Populate members
			nodeNew->comp = comp;

			// Populate the target
			if (root)
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
	SNode* iNode_extrude(SNode** rootNode, s32 tnExtrudeDirection)
	{
		SNode*		nodeLast;
		SNode*		nodeNew;


		// Make sure the environment is sane
		if (!rootNode || !between(tnExtrudeDirection, _NODE_MIN, _NODE_MAX))
			return(NULL);

		// If nothing already exists there, just create it and it will become the central node
		if (!*rootNode)
			return(iNode_create(rootNode));

		// Descend down that direction
		for (nodeLast = *rootNode; nodeLast->n[tnExtrudeDirection]; )
			nodeLast = nodeLast->n[tnExtrudeDirection];

		// Add the new offshoot, and point back-and-forth to the last one
		nodeNew = iNode_create(&nodeLast->n[tnExtrudeDirection]);			// Last points forward to new
		if (nodeNew)
			nodeNew->n[gnNodeMirrors[tnExtrudeDirection]]	= nodeLast;		// New points back to last

		// Indicate the new item
		return(nodeNew);
	}




///////////
//
// Bumps the node you're on over, inserting a new node in its place.
//
// Suppose you're on the b node, and you want to bump it southwest, anchoring to the northwest (to the 2).
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
//      2, anchorNode       a  to newNode
//      5, newNode         am  to anchorNode,     b  to bumpNode,     bm to whatever bumpNode had in that direction
//      b, bumpNode        bm  to newNode,       am  to NULL
//
//		Node directions:	a	-- anchor
//							am	-- anchor-mirror
//							b	-- bump
//							bm	-- bump-mirror
//
//////
	// Note:  The anchor direction would be the one which pointed up to 2 in the above example
	// Note:  The bump direction would be the southwest direction in the above example
	SNode* iNode_bump(SNode** rootNode, s32 tnBump/*BumpDirection*/, s32 tnAnchor/*AnchorDirection*/)
	{
		s32			lnAnchorMirror, lnBumpMirror;
		SNode*		anchorNode;
		SNode*		newNode;
		SNode*		bumpNode;


		// Make sure the environment is sane
		if (!rootNode || !between(tnBump, _NODE_MIN, _NODE_MAX))
			return(NULL);

		// If nothing already exists there, just create it and it will become the central node
		if (!*rootNode)
		{
			newNode		= iNode_create(rootNode);
			*rootNode	= newNode;
			return(newNode);
		}

		// Create our mirror directions
		lnAnchorMirror	= gnNodeMirrors[tnAnchor];
		lnBumpMirror	= gnNodeMirrors[tnBump];

		// Grab the known nodes
		bumpNode		= *rootNode;
		anchorNode		= bumpNode->n[tnAnchor];

		// Create the new node
		newNode = iNode_create(rootNode);
		if (newNode)
		{
			// Update connections
			// If there is a valid anchorNode, it needs to point to the newNode
			if (anchorNode)
				anchorNode->n[lnAnchorMirror]	= newNode;						// anchorNode points to newNode

			// Hook up newNode and bumpNode
			newNode->n[tnAnchor]			= anchorNode;						// newNode anchors to anchorNOde
			newNode->n[tnBump]				= bumpNode;							// newNode attaches to bumpNode
			newNode->n[lnBumpMirror]		= bumpNode->n[lnBumpMirror];		// newNode takes on whatever existed at bumpNode's bumpMirror direction
			bumpNode->n[lnBumpMirror]		= newNode;							// bumpNode bumpMirror's to newNode
			bumpNode->n[tnAnchor]			= NULL;								// bumpNode disconnects from anchorNode
		}

		// Indicate our result
		return(newNode);
	}




//////////
//
// Creates a new node and inserts it between where node1 (*root) points to node2.
//
//////
	SNode* iNode_insert(SNode** root, s32 tnDirection)
	{
		s32			lnMirrorDirection;
		SNode*		n[_NODE_COUNT];
		SNode*		node1;
		SNode*		node2;
		SNode*		newNode;


		// Make sure our environment is sane
		if (!root || !between(tnDirection, _NODE_MIN, _NODE_MAX))
			return(NULL);

		// Initialize
		memset(&n[0], 0, sizeof(n));
		node1				= *root;
		node2				= node1->n[tnDirection];
		lnMirrorDirection	= gnNodeMirrors[tnDirection];

		// Create and populate our new node
		newNode = iNode_create(NULL, NULL, &n[0]);
		if (newNode)
		{
			// New points mirror-back to node1 and node2
			newNode->n[lnMirrorDirection]	= node1;		// newNode points to node1
			newNode->n[tnDirection]			= node2;		// newNode points to node2
			node1->n[tnDirection]			= newNode;		// node1 points to newNode

			// If there was really a node out there, hook it up
			if (node2)
				node2->n[lnMirrorDirection]	= newNode;		// node2 points to newNode
		}

		// Indicate our status
		return(newNode);
	}




//////////
//
// Called to delete the indicated node
//
//////
	void iNode_delete(SNode** root, bool tlDeleteSelf)
	{
		SNode* node;


		// Make sure our environment is sane
		if (root && (node = *root))
		{
			//////////
			// Delete the op if need be
			//////
#ifdef iOp_politelyDelete
				if (node->opData)
				{
					// Delete op chain
					iOp_politelyDelete(&node->opData->op, false);

					// Delete the variable chain
					if (node->opData->firstVariable)
						iVariable_politelyDelete_chain(&node->opData->firstVariable, true);
				}
#endif


			//////////
			// Physically release the node if need be
			//////
				if (tlDeleteSelf)
				{
					// Pass everything which points through it to its mirror, and disconnect any nodes that don't pass through
					iNode_orphanize(root);

					// Delete any extra data
					if (node->_extraData_deleteFunc)
						node->extraData_deleteFunc(node);

					// Physically release it
					*root = NULL;
					free(node);
				}

		}
	}




//////////
//
// Called to orphanize a node, to pass everything through that has mirror connections
//
//////
	void iNode_orphanize(SNode** root)
	{
		s32		lnI, lnIm;
		SNode*	nodeOrphan;
		SNode*	node;
		SNode*	mirror;


		// Make sure our environment is sane
		if (root && (nodeOrphan = *root))
		{
			// Iterate in every direction passing through
			for (lnI = 0; lnI < _NODE_MAX; lnI++)
			{
				// Compute mirror direction
				lnIm = gnNodeMirrors[lnI];

				// Grab the two pass through nodes in each direction
				node	= nodeOrphan->n[lnI];
				mirror	= nodeOrphan->n[lnIm];

				// Is there something on both sides?
				if (node && mirror)
				{
					// Yes, connect them to each other (bypassing us)
					node->n[lnIm]		= mirror;		// Node mirror points to mirror
					mirror->n[lnI]		= node;			// Mirror node points to node
					nodeOrphan->n[lnI]	= NULL;			// Completely disconnected the orphan node...
					nodeOrphan->n[lnIm]	= NULL;			// ...and in both directions

				} else if (node) {
					// There is something in node direction
					node->n[lnIm] = NULL;

				} else if (mirror) {
					// There is something in mirror direction
					mirror->n[lnI] = NULL;
				}
			}
		}
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
			// Delete
			//////
				iNode_delete(root, tlDeleteSelf);

		}
	}




//////////
//
// Called to render a bitmap which is a visualization of the node
//
//////
	SBitmap* iNode_renderBitmap(SNode* node, s32 tnMaxTokenLength, s32 tnMaxOverallLength, f64 tfRodLength, s32 tnMarginWidth, s32 tnBorderWidth, bool tlIncludeExtraInfo, bool tlGoDeeper, SNodeFlags* nodeFlags, bool tlDeeperNodesExtendInAllDirections)
	{
		s32			lnIter_uid, lnWidth, lnHeight;
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
				props[0].backColor			= whiteColor;
				props[0].foreColor			= blackColor;
				props[0].marginWidth		= tnMarginWidth;
				props[0].fillColor			= silverColor;
				props[0].borderWidth		= tnBorderWidth;
				props[0].borderColor		= darkGrayColor;
				props[0].rodColor			= charcoalColor;
				props[0].colorize			= true;
				props[0].colorizeColor		= pastelBlueColor;
#ifdef iFont_create
				props[0].font				= iFont_create(cgcFontName_defaultFixed);
#endif

				// Render out in all directions from this point
				iiNode_renderBitmap(node, node, NULL, tnMaxTokenLength, tnMaxOverallLength, props, 1, lnIter_uid, tlIncludeExtraInfo, tlGoDeeper, nodeFlags, tlDeeperNodesExtendInAllDirections);


			//////////
			// Determine extents
			//////
				// Grab a uid for get extents
				lnIter_uid = iGetNextUid();

				// Get our starting point
				SetRect(&lrc, 0, 0, 0, 0);
				p.x = 0;
				p.y = 0;

				// Get our extents
				iiNode_get_bitmapExtents(node, node, NULL, _NODE_SE, NULL, &lrc, p, p, tfRodLength, lnIter_uid, props, tlGoDeeper, nodeFlags, tlDeeperNodesExtendInAllDirections);


			//////////
			// Render
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

					// Actually render
					iiNode_get_bitmapExtents(node, node, NULL, _NODE_SE, bmp, &lrc, p, p, tfRodLength, lnIter_uid, props, tlGoDeeper, nodeFlags, tlDeeperNodesExtendInAllDirections);
				}

		}

		// Indicate our rendered bitmap
		return(bmp);
	}

	// Note:  This is a 2D rendering, which renders into node->bmp
	void iiNode_renderBitmap(SNode* node, SNode* nodeStopper1, SNode* nodeStopper2, s32 tnMaxTokenLength, s32 tnMaxOverallLength, SNodeProps props[], s32 tnPropsCount, u32 tnIter_uid, bool tlIncludeExtraInfo, bool tlGoDeeper, SNodeFlags* nodeFlags, bool tlDeeperNodesExtendInAllDirections)
	{
		// Make sure we haven't already rendered this node
		if (node->render.iter_uid != tnIter_uid)
		{

			//////////
			// Render node
			//////
#ifdef SComp
				iBmp_node_renderComp(node, tnMaxTokenLength, tnMaxOverallLength, tlIncludeExtraInfo, props, tnPropsCount, tnIter_uid);
#endif


			//////////
			// Render all connected nodes
			//////
				if (tlGoDeeper)
				{
					for (s32 lnI = 0; lnI < (s32)_NODE_COUNT; lnI++)
					{
						// We're supposed to go this way, node exists, and we haven't already rendered it
						if ((!nodeFlags || nodeFlags->n[lnI]) && node->n[lnI] && node->n[lnI]->render.iter_uid != tnIter_uid)
						{
							// And it's not self
							if (node->n[lnI] != node)
							{
								// And it's not a stopper
								if (node->n[lnI] != nodeStopper1 && node->n[lnI] != nodeStopper2)
								{
									// Indicate that we want to render everything out from there
									iiNode_renderBitmap(node->n[lnI], nodeStopper1, node, tnMaxTokenLength, tnMaxOverallLength, props, tnPropsCount, tnIter_uid, tlIncludeExtraInfo, true, ((tlDeeperNodesExtendInAllDirections) ? &gsfNodeFlags_all : nodeFlags), tlDeeperNodesExtendInAllDirections);
								}
							}
						}
					}
				}

		}
	}

	s32 iDelta(s32 tnOrigin, s32 tnPoint)
	{
		if (tnOrigin >= tnPoint)		return(tnOrigin - tnPoint);
		else							return(tnPoint - tnOrigin);
	}

	// Note:  tfSquareSize is how far each side of the square should extend out from the connection point for the node lines
	void iiNode_get_bitmapExtents(SNode* node, SNode* nodeStopper1, SNode* nodeStopper2, s32 tnArrivalDirection, SBitmap* bmp, RECT* rc, POINTS p_anchor, POINTS p_arrival, f64 tfRodLength, u32 tnIter_uid, SNodeProps* props, bool tlGoDeeper, SNodeFlags* nodeFlags, bool tlDeeperNodesExtendInAllDirections)
	{
		s32		lnI, lnWidth, lnHeight, lnHalfWidth, lnHalfHeight;
		f64		lfHalfHeight, lfHalfWidth;
		POINTS	p_origin, p_rodStart, p_rodEnd;


		// Make sure our environment is sane, and that we're not walking over ourselves
		if (node && node->render.iter_uid != tnIter_uid && between(tnArrivalDirection, (s32)_NODE_MIN, (s32)_NODE_MAX))
		{

			//////////
			// Compute the sizes
			/////
				if (node->render.bmp)
				{
					lnHalfWidth		= (node->render.bmp->bi.biWidth  / 2);
					lnHalfHeight	= (node->render.bmp->bi.biHeight / 2);
					lnWidth			= node->render.bmp->bi.biWidth;
					lnHeight		= node->render.bmp->bi.biHeight;

				} else {
					// Assume 0 size
					lnHalfWidth		= 0;
					lnHalfHeight	= 0;
					lnWidth			= 0;
					lnHeight		= 0;
				}


			//////////
			// Note:  rc grows in these directions, to encompass the entire node assembly:
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
						rc->left	= min(rc->left,		p_anchor.x + iDelta(p_anchor.x, p_arrival.x - lnHalfWidth));				// Connecting point:  +--+--+
						rc->top		= min(rc->top,		p_anchor.y - iDelta(p_anchor.y, p_arrival.y - lnHeight));					//                    +  +  +
						rc->right	= max(rc->right,	p_anchor.x + iDelta(p_anchor.x, p_arrival.x - lnHalfWidth + lnWidth));		//                    +--o--+
						p_origin.x	= p_arrival.x;
						p_origin.y	= p_arrival.y - (s16)lnHeight + (s16)lnHalfHeight;
						SetRect(&node->render.rc,	p_arrival.x - lnHalfWidth,
													p_arrival.y - lnHeight,
													p_arrival.x - lnHalfWidth + lnWidth,
													p_arrival.y);
						break;

					case _NODE_E0:
					case _NODE_E1:
					case _NODE_E2:
						rc->top		= min(rc->top,		p_anchor.y - iDelta(p_anchor.y, p_arrival.y - lnHalfHeight));				// Connecting point:  +--+--+
						rc->right	= max(rc->right,	p_anchor.x + iDelta(p_anchor.x, p_arrival.x + lnWidth));					//                    o  +  +
						rc->bottom	= max(rc->bottom,	p_anchor.y + iDelta(p_anchor.y, p_arrival.y - lnHalfHeight + lnHeight));	//                    +--+--+
						p_origin.x	= p_arrival.x + (s16)lnHalfWidth;
						p_origin.y	= p_arrival.y;
						SetRect(&node->render.rc,	p_arrival.x,
													p_arrival.y - lnHalfHeight,
													p_arrival.x + lnWidth,
													p_arrival.y - lnHalfHeight + lnHeight);
						break;

					case _NODE_C0:
					case _NODE_C1:
					case _NODE_C2:
						rc->left	= min(rc->left,		p_anchor.x - iDelta(p_anchor.x, p_arrival.x - lnHalfWidth));				// Connecting point:  +--+--+
						rc->right	= max(rc->right,	p_anchor.x + iDelta(p_anchor.x, p_arrival.x - lnHalfWidth + lnWidth));		//                    +  o  +
						rc->top		= min(rc->top,		p_anchor.y - iDelta(p_anchor.y, p_arrival.y - lnHalfHeight));				//                    +--+--+
						rc->bottom	= max(rc->bottom,	p_anchor.y + iDelta(p_anchor.y, p_arrival.y - lnHalfHeight + lnHeight));	//
						p_origin.x	= p_arrival.x;
						p_origin.y	= p_arrival.y;
						SetRect(&node->render.rc,	p_arrival.x - lnHalfWidth,
													p_arrival.y - lnHalfHeight,
													p_arrival.x - lnHalfWidth + lnWidth,
													p_arrival.y - lnHalfHeight + lnHeight);
						break;

					case _NODE_S0:
					case _NODE_S1:
					case _NODE_S2:
						rc->left	= min(rc->left,		p_anchor.x - iDelta(p_anchor.x, p_arrival.x - lnHalfWidth));				// Connecting point:  +--o--+
						rc->right	= max(rc->right,	p_anchor.x + iDelta(p_anchor.x, p_arrival.x - lnHalfWidth + lnWidth));		//                    +  +  +
						rc->bottom	= max(rc->bottom,	p_anchor.y + iDelta(p_anchor.y, p_arrival.y + lnHeight));					//                    +--+--+
						p_origin.x	= p_arrival.x;
						p_origin.y	= p_arrival.y + (s16)lnHalfHeight;
						SetRect(&node->render.rc,	p_arrival.x - lnHalfWidth,
													p_arrival.y,
													p_arrival.x - lnHalfWidth + lnWidth,
													p_arrival.y + lnHeight);
						break;

					case _NODE_W0:
					case _NODE_W1:
					case _NODE_W2:
						rc->top		= min(rc->top,		p_anchor.x - iDelta(p_anchor.y, p_arrival.y - lnHalfHeight));				// Connecting point:  +--+--+
						rc->left	= min(rc->left,		p_anchor.x - iDelta(p_anchor.x, p_arrival.x - lnWidth));					//                    +  +  o
						rc->bottom	= max(rc->bottom,	p_anchor.y + iDelta(p_anchor.y, p_arrival.y - lnHalfHeight + lnHeight));	//                    +--+--+
						p_origin.x	= p_arrival.x - (s16)lnWidth + (s16)lnHalfWidth;
						p_origin.y	= p_arrival.y;
						SetRect(&node->render.rc,	p_arrival.x - lnWidth,
													p_arrival.y - lnHalfHeight,
													p_arrival.x,
													p_arrival.y - lnHalfHeight + lnHeight);
						break;

					case _NODE_NE0:
					case _NODE_NE1:
					case _NODE_NE2:
						rc->right	= max(rc->right,	p_anchor.x + iDelta(p_anchor.x, p_arrival.x + lnWidth));					// Connecting point:  +--+--+
						rc->top		= min(rc->top,		p_anchor.y - iDelta(p_anchor.y, p_arrival.y - lnHeight));					//                    +  +  +
																																	//                    o--+--+
						p_origin.x	= p_arrival.x + (s16)lnHalfWidth;
						p_origin.y	= p_arrival.y - (s16)lnHeight + (s16)lnHalfHeight;
						SetRect(&node->render.rc,	p_arrival.x,
													p_arrival.y - lnHeight,
													p_arrival.x + lnWidth,
													p_arrival.y);
						break;

					case _NODE_SE0:
					case _NODE_SE1:
					case _NODE_SE2:
						rc->right	= max(rc->right,	p_anchor.x + iDelta(p_anchor.x, p_arrival.x + lnWidth));					// Connecting point:  o--+--+
						rc->bottom	= max(rc->bottom,	p_anchor.x + iDelta(p_anchor.y, p_arrival.y + lnHeight));					//                    +  +  +
																																	//                    +--+--+
						p_origin.x	= p_arrival.x + (s16)lnHalfWidth;
						p_origin.y	= p_arrival.y + (s16)lnHalfHeight;
						SetRect(&node->render.rc,	p_arrival.x,
													p_arrival.y,
													p_arrival.x + lnWidth,
													p_arrival.y + lnHeight);
						break;

					case _NODE_SW0:
					case _NODE_SW1:
					case _NODE_SW2:
						rc->left	= min(rc->left,		p_anchor.x - iDelta(p_anchor.x, p_arrival.x - lnWidth));					// Connecting point:  +--+--o
						rc->bottom	= max(rc->bottom,	p_anchor.y + iDelta(p_anchor.y, p_arrival.y + lnHeight));					//                    +  +  +
																																	//                    +--+--+
						p_origin.x	= p_arrival.x - (s16)lnWidth + (s16)lnHalfWidth;
						p_origin.y	= p_arrival.y + (s16)lnHalfHeight;
						SetRect(&node->render.rc,	p_arrival.x - lnWidth,
													p_arrival.y,
													p_arrival.x,
													p_arrival.y + lnHeight);
						break;

					case _NODE_NW0:
					case _NODE_NW1:
					case _NODE_NW2:
						rc->left	= min(rc->left,		p_anchor.x - iDelta(p_anchor.x, p_arrival.x - lnWidth));					// Connecting point:  +--+--+
						rc->top		= min(rc->top,		p_anchor.y - iDelta(p_anchor.y, p_arrival.y - lnHeight));					//                    +  +  +
																																	//                    +--+--o
						p_origin.x	= p_arrival.x - (s16)lnWidth  + (s16)lnHalfWidth;
						p_origin.y	= p_arrival.y - (s16)lnHeight + (s16)lnHalfHeight;
						SetRect(&node->render.rc,	p_arrival.x - lnWidth,
													p_arrival.y - lnHeight,
													p_arrival.x,
													p_arrival.y);
						break;
				}

				// Set the iteration uid
				node->render.iter_uid = tnIter_uid;

				// Render the rectangle if we're drawing
				if (bmp && node->render.bmp)
					iBmp_bitBlt(bmp, &node->render.rc, node->render.bmp);

				// Compute distances from the origin to side and top, which then can extend to all 8 points through gnNodeRodeMaps[]
				lfHalfWidth		= (f64)(lnWidth  / 2);
				lfHalfHeight	= (f64)(lnHeight / 2);
				tfRodLength		= max(tfRodLength, 8.0);


			//////////
			// Kick off the nodes in each direction
			//////
				if (tlGoDeeper)
				{
					// Iterate off in all directions
					for (lnI = 0; lnI < (s32)_NODE_COUNT; lnI++)
					{
						// Are we're supposed to go this way?
						// We're supposed to go this way, and the node exists, and we haven't already rendered it
						if ((!nodeFlags || nodeFlags->n[lnI]) && node->n[lnI] && node->n[lnI]->render.iter_uid != tnIter_uid)
						{
							// And it's not self
							if (node->n[lnI] != node)
							{
								// And it's not our stopper
								if (node->n[lnI] != nodeStopper1 && node->n[lnI] != nodeStopper2)
								{
									// Determine the ending point at the connecting rod
									p_rodStart.x	= p_origin.x	+ (s32)(gsfNodeRodMaps[lnI].x * lfHalfWidth);
									p_rodStart.y	= p_origin.y	+ (s32)(gsfNodeRodMaps[lnI].y * lfHalfHeight);
									p_rodEnd.x		= p_rodStart.x	+ (s32)(gsfNodeRodMaps[lnI].x * tfRodLength);
									p_rodEnd.y		= p_rodStart.y	+ (s32)(gsfNodeRodMaps[lnI].y * tfRodLength);

									// Draw connections to the next direction (if we're drawing)
									if (bmp)
										iBmp_drawArbitraryLine(bmp, p_rodStart.x, p_rodStart.y, p_rodEnd.x, p_rodEnd.y, props->rodColor);

									// Indicate that we want to render everything out from there
									iiNode_get_bitmapExtents(node->n[lnI], nodeStopper1, node, lnI, bmp, rc, p_anchor, p_rodEnd, tfRodLength, tnIter_uid, props, true, ((tlDeeperNodesExtendInAllDirections) ? &gsfNodeFlags_all : nodeFlags), tlDeeperNodesExtendInAllDirections);
								}
							}
						}
					}
				}

		}
	}

// 	// Note:  This is a 3D rendering, which populates a vector array for the iGrace() engine in node->grace
// 	// Note:  However, it also uses the node->bmp entries for the face bitmap
// 	void iiNode_renderGrace(SNode* node, SNode* nodeStopper1, SNode* nodeStopper2, s32 tnMaxTokenLength, s32 tnMaxOverallLength, SNodeProps props[], s32 tnPropsCount, u32 tnIter_uid, bool tlGoDeeper, SNodeFlags* nodeFlags, bool tlDeeperNodesExtendInAllDirections)
// 	{
// 		// This needs to be written
// 		debug_break;
// 	}
// 
// 	void iiNode_get_graceExtents(SNode* node, SNode* nodeStopper1, SNode* nodeStopper2, s32 tnArrivalDirection, SBitmap* bmp, SGraceLine* line, POINTS p_arrival, f64 tfRodLength, u32 tnIter_uid, SNodeProps* props, bool tlGoDeeper, SNodeFlags* nodeFlags, bool tlDeeperNodesExtendInAllDirections)
// 	{
// 		// This needs written
// 		debug_break;
// 	}
