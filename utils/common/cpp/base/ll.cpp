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
// Copyright (c) 2014-2015 by Rick C. Hodgin
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
	SLL* iLl_appendNew__ll(SLL** llRoot, SLL* llHint, SLL* llNext, SLL* llPrev, u32 tnUniqueId, u32 tnSize)
	{
		SLL* ll;


		// Make sure our environment is sane
		ll = NULL;
		if (llRoot)
		{
			// Create a new node
			ll = iLl_createOrphan__ll(llPrev, llNext, tnUniqueId, tnSize);

			// Append it to the chain
			if (*llRoot)
			{
				// There is already data
				if (!llHint)
					llHint = *llRoot;

				// Iterate forward until we reach the end
				while (llHint->next)
					llHint = llHint->next;

				// Append as the next item from where we are
				llHint->next = ll;

			} else {
				// This will be the first entry
				*llRoot = ll;
			}
		}
		// Indicate our success or failure
		return(ll);
	}




//////////
//
// Creates a new 2-way linked list with optional nodePrev and nodeNext info, using
// the indicated size for the allocation (which is beyond the SLL portion at the head).
//////
	SLL* iLl_createOrphan__ll(SLL* llPrev, SLL* llNext, u32 tnUniqueId, u32 tnSize)
	{
		SLL* ll;


		// Allocate the size
		ll = (SLL*)malloc(sizeof(SLL) + tnSize);
		if (ll)
		{
			// We're good
			memset(ll, 0, tnSize);

			// Store a unique id
			ll->uniqueId	= tnUniqueId;

			// Update our pointers
			ll->prev		= llPrev;
			ll->next		= llNext;
		}

		// Indicate our success or failure
		return(ll);
	}




//////////
//
// Called to append the node at the end of the chain
//
//////
	SLL* iLl_appendNew__llAtEnd(SLL** llRoot, u32 tnSize)
	{
		SLL* ll;
		SLL* llNew;


		// Make sure our environment is sane
		llNew = NULL;
		if (llRoot)
		{
			// Allocate new
			llNew = (SLL*)malloc(tnSize);
			if (llNew)
			{
				// Initialize
				memset(llNew, 0, tnSize);

				// Determine where it goes
				if (!*llRoot)
				{
					// First entry
					*llRoot = llNew;

				} else {
					// Append to end
					ll = *llRoot;
					while (ll->next)
						ll = ll->next;

					// Append here
					ll->next		= llNew;		// Previous points here
					llNew->prev	= ll;			// We point back to previous
				}
			}
		}

		// Indicate our status
		return(llNew);
	}




//////////
//
// Called to append a new node at the beginning
//
//////
	SLL* iLl_appendNew__llAtBeginning(SLL** llRoot, u32 tnSize)
	{
		SLL* ll;
		SLL* llNew;


		// Make sure our environment is sane
		llNew = NULL;
		if (llRoot)
		{
			// Allocate new
			llNew = (SLL*)malloc(tnSize);
			if (llNew)
			{
				// Initialize
				memset(llNew, 0, tnSize);

				// Set it up
				ll	= *llRoot;
				*llRoot	= llNew;

				// If there was a previous node, insert it
				if (ll)
				{
					// Append here
					ll->prev		= llNew;		// Previous first node points to new first node
					llNew->next	= ll;			// New first node points forward to previous first node
				}
			}
		}

		// Indicate our status
		return(llNew);
	}




/////////
//
// Called to append a node which already exists to the end
//
//////
	bool iLl_appendExisting__llAtEnd(SLL** llRoot, SLL* node)
	{
		bool	llAppended;
		SLL*	llLast;


		// Make sure our environment is sane
		llAppended = false;
		if (llRoot && node)
		{
			// Determine where it goes
			llAppended = true;
			if (!*llRoot)
			{
				// First entry
				*llRoot = node;

			} else {
				// Append to end
				llLast = *llRoot;
				while (llLast->next)
					llLast = llLast->next;

				// Append here
				llLast->next	= node;			// Last one currently existing points here
				node->prev		= llLast;		// Node points back to previous last one
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
	bool iLl_appendExisting__llAtBeginning(SLL** llRoot, SLL* ll)
	{
		bool	llAppended;
		SLL*	llFirst;


		// Make sure our environment is sane
		llAppended = false;
		if (llRoot && ll)
		{
			// Determine where it goes
			llAppended = true;
			if (!*llRoot)
			{
				// First entry
				*llRoot = ll;

			} else {
				// Append to beginning
				llFirst			= *llRoot;
				ll->next		= llFirst;
				llFirst->prev	= ll;		// Ignore the GCC warning message here... I don't know why it's throwing a warning.  Everything here is populated and tested before use.
				*llRoot			= ll;
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
	SLL* iLl_delete__ll(SLL* ll, bool tlDeleteSelf)
	{
		SLL* llNext;


		// Make sure our environment is sane
		llNext = NULL;
		if (ll)
		{
			//////////
			// Disconnect
			//////
				// find out what would be the next one they'll need to point to
				if (ll->next)		llNext = ll->next;
				else				llNext = ll->prev;

				// Orphanize if need be
				if (ll->prev || ll->next)
					iLl_orphanize__ll(ll);


			//////////
			// Delete the node
			//////
				if (tlDeleteSelf)
				{
					// Remove any link-list info
					memset(ll, 0, sizeof(SLL));

					// Delete self
					free(ll);

				} else {
					llNext = ll;
				}
		}

		// Indicate our status
		return(llNext);
	}




//////////
//
// Called to migrate the indicated node from one source to the other.  It is not validated that
// the node exists in the first, but rather the only test performed is at least one node exists,
// and if the first node in the source is the node, and if so then it updates the first node to
// point to the one after node.
//
//////
	SLL* iLl_migrate__llToOther(SLL** llSourceRoot, SLL** llDestinationRoot, SLL* ll, bool tlInsertAtEnd)
	{
		SLL* llRef;
		SLL* llNext;


		// Make sure our environment is sane
		if (llSourceRoot && *llSourceRoot && llDestinationRoot && ll)
		{
			//////////
			// If the first node is our node, then the first node now becomes the one after our node
			//////
				llNext = ll->next;
				if (*llSourceRoot == ll)
					*llSourceRoot = llNext;


			//////////
			// Unhook the node from its current location
			//////
				iLl_orphanize__ll(ll);


			//////////
			// Position the node into its new location
			//////
				if (!*llDestinationRoot)
				{
					// There are no other nodes. Introduce this one into its new node home as the "de facto leader," as it were...
					*llDestinationRoot = ll;

				} else {
					// There are others.  We must determine its location (without any hesitation, offered
					// up by designation, as solid indication, the state of its vocation, made known by
					// observation, and contextual revelation, for subsequent relocation)
					if (tlInsertAtEnd)		llRef = iLl_getLast__ll(*llDestinationRoot);
					else					llRef = *llDestinationRoot;

					// Insert it relative to its new home (full of relatives, well ... at least one relative that we know of)
					iLl_insert__ll(ll, llRef, tlInsertAtEnd);
				}

			//////////
			// Indicate the one after the one we migrated
			//////
				return(llNext);

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
	void iLl_delete__llsWithCallback(SLLCallback* cb)
	{
		if (cb && cb->ll)
		{
			//////////
			// Disconnect
			//////
				if (cb->ll->prev || cb->ll->next)
					iLl_orphanize__ll(cb->ll);


			//////////
			// Let the user say their goodbyes
			//////
				if (cb->_func)
					cb->funcVoid(cb);


			//////////
			// Delete the node
			//////
				free(cb->ll);
		}
	}




//////////
//
// Inserts a 2-way linked relative to the nodeRef, either before or after.  If the
// node is already connected, it is disconnected.
//
//////
	bool iLl_insert__ll(SLL* node,  SLL* nodeRef,  bool tlAfter)
	{
// TODO:  UNTESTED CODE
		// Is our environment sane?
		if (node && nodeRef)
		{
			//////////
			// Disconnect
			//////
				if (node->prev || node->next)
					iLl_orphanize__ll(node);


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
	void iLl_orphanize__ll(SLL* node)
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
	void iLl_delete__llChain(SLL** root)
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
	void iLl_delete__llChainWithCallback(SLLCallback* cb)
	{
		SLL* llNext;


		// Make sure the environment is sane
		if (cb)
		{
			// Iterate through deleting each entry
			while (cb->ll)
			{
				// Grab the next node
				llNext = cb->ll->next;

				// Perform the callback
				if (cb->_func)
					cb->funcVoid(cb);

				// Delete the node itself
				free(cb->ll);

				// Move to next node
				cb->ll = llNext;
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
			while (cb->ll)
			{

				//////////
				// Callback to compute the SHA1 on this item
				//////
					cb->funcVoid(cb);
					//vvm_sha1ComputeSha1_ProcessThisData(context, (s8*)node, tnSize);


				//////////
				// Move to next node
				//////
					cb->ll = cb->ll->next;
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
			while (cb->ll)
			{

				//////////
				// Callback to compute the SHA1 on this item
				//////
					cb->funcVoid(cb);
					//vvm_sha1ComputeSha1_ProcessThisData(context, (s8*)node, tnSize);


				//////////
				// Move to next node
				//////
					cb->ll = cb->ll->prev;
			}
	}




//////////
//
// Called to compute the SHA-1 of the current node as a 64-bit quantity
//
//////
	SLL* iLl_getFirst__ll(SLL* ll)
	{
		// Make sure the environment is sane
		if (ll)
		{
			// Iterate backwards to the top
			while (ll->prev)
				ll = ll->prev;
		}

		// Indicate where we are
		return(ll);
	}




//////////
//
// Called to compute the SHA-1 of the current node as a 64-bit quantity
//
// The parameters in the callback are:
//		ptr			-- LL node
//////
	SLL* iLl_getLast__ll(SLL* ll)
	{
		// Make sure the environment is sane
		if (ll)
		{
			// Iterate toward the end
			while (ll->next)
				ll = ll->next;
		}

		// Indicate where we are
		return(ll);
	}




//////////
//
// Called to count the nodes to the end
//
//////
	u32 iLl_count__llsToEnd(SLL* ll)
	{
		u32 lnCount;


		// Make sure the environment is sane
		lnCount = 0;
		if (ll)
		{
			// Iterate toward the end
			while (ll)
			{
				// Increase our count
				++lnCount;

				// Continue on so long as we have nodes
				ll = ll->next;
			}
		}

		// Indicate how many we found
		return(lnCount);
	}
