//////////
//
// /libsf/utils/common/cpp/ll.cpp
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
// Copyright (c) 2014 by Rick C. Hodgin
//////
// Last update:
//     Aug.02.2014
//////
// Change log:
//     Aug.02.2014 - Initial creation
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
//     http://www.visual-freepro.org/wiki/index.php/Repeat_License
//
// Thank you.  And may The Lord bless you richly as you lift up your life, your
// talents, your gifts, your praise, unto Him.  In Jesus' name I pray.  Amen.
//
//////
//   _       _         _     _       _       _
//  | |     (_)       | |   | |     (_)     | |
//  | |      _  _ __  | | __| |      _  ___ | |_
//  | |     | || '_ \ | |/ /| |     | |/ __|| __|
//  | |____ | || | | ||   < | |____ | |\__ \| |_
//  |______||_||_| |_||_|\_\|______||_||___/ \__|
//    Link List -- Simple link list algorithms.
//////////




//////////
//
// Callback structure for SLL iteration
//
//////
	#include "ll.h"




//////////
//
// Append a new node to the list, and return the pointer.
// The nodeHint is provided and can be used to find the end of the chain faster than iterating
// from the root.  Typically it is the last returned node.  However, if NULL, this process will
// iterate from the root node forward.
//
//////
	SLL* iLl_appendNewNode(SLL** root, SLL* nodeHint, SLL* nodeNext, SLL* nodePrev, u32 tnUniqueId, u32 tnSize)
	{
		SLL* node;


		// Make sure our environment is sane
		node = NULL;
		if (root)
		{
			// Create a new node
			node = iLl_createOrphanNode(nodePrev, nodeNext, tnUniqueId, tnSize);

			// Append it to the chain
			if (*root)
			{
				// There is already data
				if (!nodeHint)
					nodeHint = *root;

				// Iterate forward until we reach the end
				while (nodeHint->next)
					nodeHint = nodeHint->next;

				// Append as the next item from where we are
				nodeHint->next = node;

			} else {
				// This will be the first entry
				*root = node;
			}
		}
		// Indicate our success or failure
		return(node);
	}




//////////
//
// Creates a new 2-way linked list with optional nodePrev and nodeNext info, using
// the indicated size for the allocation (which is beyond the SLL portion at the head).
//////
	SLL* iLl_createOrphanNode(SLL* nodePrev, SLL* nodeNext, u32 tnUniqueId, u32 tnSize)
	{
		SLL* node;


		// Allocate the size
		node = (SLL*)malloc(sizeof(SLL) + tnSize);
		if (node)
		{
			// We're good
			memset(node, 0, tnSize);

			// Store a unique id
			node->uniqueId	= tnUniqueId;

			// Update our pointers
			node->prev		= nodePrev;
			node->next		= nodeNext;
		}

		// Indicate our success or failure
		return(node);
	}




//////////
//
// Called to append the node at the end of the chain
//
//////
	SLL* iLl_appendNewNodeAtEnd(SLL** root, u32 tnSize)
	{
		SLL* node;
		SLL* nodeNew;


		// Make sure our environment is sane
		nodeNew = NULL;
		if (root)
		{
			// Allocate new
			nodeNew = (SLL*)malloc(tnSize);
			if (nodeNew)
			{
				// Initialize
				memset(nodeNew, 0, tnSize);

				// Determine where it goes
				if (!*root)
				{
					// First entry
					*root = nodeNew;

				} else {
					// Append to end
					node = *root;
					while (node->next)
						node = node->next;

					// Append here
					node->next		= nodeNew;		// Previous points here
					nodeNew->prev	= node;			// We point back to previous
				}
			}
		}

		// Indicate our status
		return(nodeNew);
	}




//////////
//
// Called to append a new node at the beginning
//
//////
	SLL* iLl_appendNewNodeAtBeginning(SLL** root, u32 tnSize)
	{
		SLL* node;
		SLL* nodeNew;


		// Make sure our environment is sane
		nodeNew = NULL;
		if (root)
		{
			// Allocate new
			nodeNew = (SLL*)malloc(tnSize);
			if (nodeNew)
			{
				// Initialize
				memset(nodeNew, 0, tnSize);

				// Set it up
				node	= *root;
				*root	= nodeNew;

				// If there was a previous node, insert it
				if (node)
				{
					// Append here
					node->prev		= nodeNew;		// Previous first node points to new first node
					nodeNew->next	= node;			// New first node points forward to previous first node
				}
			}
		}

		// Indicate our status
		return(nodeNew);
	}




/////////
//
// Called to append a node which already exists to the end
//
//////
	bool iLl_appendExistingNodeAtEnd(SLL** root, SLL* node)
	{
		bool	llAppended;
		SLL*	nodeLast;


		// Make sure our environment is sane
		llAppended = false;
		if (root && node)
		{
			// Determine where it goes
			llAppended = true;
			if (!*root)
			{
				// First entry
				*root = node;

			} else {
				// Append to end
				nodeLast = *root;
				while (nodeLast->next)
					nodeLast = nodeLast->next;

				// Append here
				nodeLast->next	= node;			// Last one currently existing points here
				node->prev		= nodeLast;		// Node points back to previous last one
			}
		}

		// Indicate our status
		return(llAppended);
	}




//////////
//
// Called to append the existing node at the beginning
//
//////
	bool iLl_appendExistingNodeAtBeginning(SLL** root, SLL* node)
	{
		bool	llAppended;
		SLL*	nodeFirst;


		// Make sure our environment is sane
		llAppended = false;
		if (root && node)
		{
			// Determine where it goes
			llAppended = true;
			if (!*root)
			{
				// First entry
				*root = node;

			} else {
				// Append to beginning
				nodeFirst		= *root;
				node->next		= nodeFirst;
				nodeFirst->prev	= node;		// Ignore the GCC warning message here... I don't know why it's throwing a warning.  Everything here is populated and tested before use.
				*root			= node;
				llAppended		= true;
			}
		}

		// Indicate our status
		return(llAppended);
	}




//////////
//
// Called to delete a link list node from the chain.  It orphanizes the node first.
// It will fully delete it if tlDeleteSelf is true.  The return value is either the
// orphan node, or the node->next value if the node was fully deleted.
//
//////
	SLL* iLl_deleteNode(SLL* node, bool tlDeleteSelf)
	{
		SLL* nodeNext;


		// Make sure our environment is sane
		nodeNext = NULL;
		if (node)
		{
			//////////
			// Disconnect
			//////
				// find out what would be the next one they'll need to point to
				if (node->next)		nodeNext = node->next;
				else				nodeNext = node->prev;

				// Orphanize if need be
				if (node->prev || node->next)
					iLl_orphanizeNode(node);


			//////////
			// Delete the node
			//////
				if (tlDeleteSelf)
				{
					// Remove any link-list info
					memset(node, 0, sizeof(SLL));

					// Delete self
					free(node);

				} else {
					nodeNext = node;
				}
		}

		// Indicate our status
		return(nodeNext);
	}




//////////
//
// Called to migrate the indicated node from one source to the other.  It is not validated that
// the node exists in the first, but rather the only test performed is at least one node exists,
// and if the first node in the source is the node, and if so then it updates the first node to
// point to the one after node.
//
//////
	SLL* iLl_migrateNodeToOther(SLL** nodeSourceRoot, SLL** nodeDestinationRoot, SLL* node, bool tlInsertAtEnd)
	{
		SLL* nodeRef;
		SLL* nodeNext;


		// Make sure our environment is sane
		if (nodeSourceRoot && *nodeSourceRoot && nodeDestinationRoot && node)
		{
			//////////
			// If the first node is our node, then the first node now becomes the one after our node
			//////
				nodeNext = node->next;
				if (*nodeSourceRoot == node)
					*nodeSourceRoot = nodeNext;


			//////////
			// Unhook the node from its current location
			//////
				iLl_orphanizeNode(node);


			//////////
			// Position the node into its new location
			//////
				if (!*nodeDestinationRoot)
				{
					// There are no other nodes. Introduce this one into its new node home as the "de facto leader," as it were...
					*nodeDestinationRoot = node;

				} else {
					// There are others.  We must determine its location (without any hesitation, offered
					// up by designation, as solid indication, the state of its vocation, made known by
					// observation, and contextual revelation, for subsequent relocation)
					if (tlInsertAtEnd)		nodeRef = iLl_getLastNode(*nodeDestinationRoot);
					else					nodeRef = *nodeDestinationRoot;

					// Insert it relative to its new home (full of relatives, well ... at least one relative that we know of)
					iLl_insertNode(node, nodeRef, tlInsertAtEnd);
				}

			//////////
			// Indicate the one after the one we migrated
			//////
				return(nodeNext);

		} else {
			// Failure
			return(NULL);
		}
	}




//////////
//
// Called to delete a link list node with a callback.  If need be it orphanizes the node first.
//
//////
	void iLl_deleteNodesWithCallback(SLLCallback* cb)
	{
		if (cb && cb->node)
		{
			//////////
			// Disconnect
			//////
				if (cb->node->prev || cb->node->next)
					iLl_orphanizeNode(cb->node);


			//////////
			// Let the user say their goodbyes
			//////
				if (cb->_func)
					cb->funcVoid(cb);


			//////////
			// Delete the node
			//////
				free(cb->node);
		}
	}




//////////
//
// Inserts a 2-way linked relative to the nodeRef, either before or after.  If the
// node is already connected, it is disconnected.
//
//////
	bool iLl_insertNode(SLL* node,  SLL* nodeRef,  bool tlAfter)
	{
// TODO:  UNTESTED CODE
		// Is our environment sane?
		if (node && nodeRef)
		{
			//////////
			// Disconnect
			//////
				if (node->prev || node->next)
					iLl_orphanizeNode(node);


			//////////
			// Is it going before or after?
			//////
				if (tlAfter)
				{
					// Point the one after this back to node to be inserted
					if (nodeRef->next)
						nodeRef->next->prev	= node;		// The one after points back to the node we're inserting

					// Are we updating to a valid node?
					if (node)
					{
						// The node is valid, so we can update relative pointers
						// Point this node to the one that will be after
						node->next = nodeRef->next;
						node->prev = nodeRef;
					}

					// Store the pointer to the node
					nodeRef->next = node;


				} else {
					// Positioning this node before
					// Point the one before this forward to the node to be inserted
					if (nodeRef->prev)
						nodeRef->prev->next = node;

					// Are we updating to a valid node?
					if (node)
					{
						// The node is valid, so we can update relative pointers
						// Point this node to the one that will be after
						node->prev = nodeRef->prev;
						node->next = nodeRef;
					}

					// Store the pointer to the node
					nodeRef->prev = node;
				}
		}
		// Failure
		return(false);
	}




//////////
//
// Disconnects a node from its existing chain
//
//////
	void iLl_orphanizeNode(SLL* node)
	{
// TODO:  UNTESTED CODE
		// Is our environment sane?
		if (node)
		{

			//////////
			// Is there one before?
			//////
				if (node->prev)
					node->prev->next = node->next;		// Make the one before point to the one after

			//////////
			// Is there one after?
			//////
				if (node->next)
					node->next->prev = node->prev;		// Make the one after point to the one before

			//////////
			// Free up all parts
			//////
				node->next	= NULL;
				node->prev	= NULL;
		}
	}




//////////
//
// Called to delete the entire chain (beginning from where it's at
//
//////
	void iLl_deleteNodeChain(SLL** root)
	{
		SLL* node;
		SLL* nodeNext;


		// Make sure the environment is sane
		if (root)
		{
			// Iterate through deleting each entry
			node = *root;
			while (node)
			{
				// Grab the next node
				nodeNext = node->next;

				// Delete the node
				free(node);

				// Move to next item
				node = nodeNext;
			}

			// Reset the pointer
			*root = NULL;
		}
	}




//////////
//
// Called to delete the entire chain (beginning from where it's at on) using an optional callback.
// The callback should not delete the node, but only anything the node points to.
//
//////
	void iLl_deleteNodeChainWithCallback(SLLCallback* cb)
	{
		SLL* nodeNext;


		// Make sure the environment is sane
		if (cb)
		{
			// Iterate through deleting each entry
			while (cb->node)
			{
				// Grab the next node
				nodeNext = cb->node->next;

				// Perform the callback
				if (cb->_func)
					cb->funcVoid(cb);

				// Delete the node itself
				free(cb->node);

				// Move to next node
				cb->node = nodeNext;
			}
			// All done
		}
	}




//////////
//
// Called to compute the SHA-1 of the current node as a 64-bit quantity
//
//////
	void iLl_iterateViaCallback(SLLCallback* cb)
	{
		//////////
		// For each node, process its portion
		//////
			while (cb->node)
			{

				//////////
				// Callback to compute the SHA1 on this item
				//////
					cb->funcVoid(cb);
					//vvm_sha1ComputeSha1_ProcessThisData(context, (s8*)node, tnSize);


				//////////
				// Move to next node
				//////
					cb->node = cb->node->next;
			}
	}




//////////
//
// Called to iterate from the indicated node backwards
//
//////
	void iLl_iterateBackwardViaCallback(SLLCallback* cb)
	{
		//////////
		// For each node, process its portion
		//////
			while (cb->node)
			{

				//////////
				// Callback to compute the SHA1 on this item
				//////
					cb->funcVoid(cb);
					//vvm_sha1ComputeSha1_ProcessThisData(context, (s8*)node, tnSize);


				//////////
				// Move to next node
				//////
					cb->node = cb->node->prev;
			}
	}




//////////
//
// Called to compute the SHA-1 of the current node as a 64-bit quantity
//
//////
	SLL* iLl_getFirstNode(SLL* node)
	{
		// Make sure the environment is sane
		if (node)
		{
			// Iterate backwards to the top
			while (node->prev)
				node = node->prev;
		}

		// Indicate where we are
		return(node);
	}




//////////
//
// Called to compute the SHA-1 of the current node as a 64-bit quantity
//
// The parameters in the callback are:
//		ptr			-- LL node
//////
	SLL* iLl_getLastNode(SLL* node)
	{
		// Make sure the environment is sane
		if (node)
		{
			// Iterate toward the end
			while (node->next)
				node = node->next;
		}

		// Indicate where we are
		return(node);
	}




//////////
//
// Called to count the nodes to the end
//
//////
	u32 iLl_countNodesToEnd(SLL* node)
	{
		u32 lnCount;


		// Make sure the environment is sane
		lnCount = 0;
		if (node)
		{
			// Iterate toward the end
			while (node)
			{
				// Increase our count
				++lnCount;

				// Continue on so long as we have nodes
				node = node->next;
			}
		}

		// Indicate how many we found
		return(lnCount);
	}
