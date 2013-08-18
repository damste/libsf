//////////
//
// /libsf/vvm/core/vvmtests/vvmt_core/vvmt_sll4_test.cpp
//
//////
// Version 0.60
// Copyright (c) 2012, 2013 by Rick C. Hodgin
//////
// Last update:
//     Jul.24.2013
//////
// Change log:
//     Jul.24.2013	- Initial creation
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
//     http://www.visual-freepro.org
//     http://www.visual-freepro.org/blog/
//     http://www.visual-freepro.org/forum/
//     http://www.visual-freepro.org/wiki/
//     http://www.visual-freepro.org/wiki/index.php/PBL
//     http://www.visual-freepro.org/wiki/index.php/Repeat_License
//
// Thank you.  And may The Lord bless you richly as you lift up your life, your
// talents, your gifts, your praise, unto Him.  In Jesus' name I pray.  Amen.
//
//




//////////
//
// Top level for running test cases against the SHA-1 engine.
//
//////
	bool ivvmt_testSll4(u64 lnHandleLog)
	{
		SLL4* root;


		// Indicate which test
		vvm_resourcePrintf(IDS_VVM_TEST_SLL4_TESTING);


		//////////
		// #01 - Create a nine element 4-way linked list, one in the middle, and two extending out in all four directions
		//////
			if (!iivvmt_testSll4_1(lnHandleLog, &root))
				return false;		// failure


		//////////
		// #02 - Append an item before and after each element in all directions
		//////
			if (!iivvmt_testSll4_2(lnHandleLog, root))
				return false;		// failure


		//////////
		// #03 - Delete first item, middle, last item in each direction
		//////
			if (!iivvmt_testSll4_3(lnHandleLog, &root))
				return false;		// failure


		//////////
		// Clean house
		//////
			oss_ll4_deleteChain(&root, _LL4_ALL);


		// When we get here, success
		vvm_resourcePrintf(IDS_VVM_TEST_SLL4_PASSED);
		return true;
	}




//////////
//
// The 4-way link-list test builds everything off the root.  It first adds the "2" nodes,
// which initially occupy the positions immediate off root.  It then adds the "1" nodes, which
// are inserted between the "2" nodes and root in each direction.
//
//	           ____ north
//	          | n2 |
//	          |____|
//	          | n1 |
//	 ____ ____|____|____ ____ 
//	| w2 | w1 |root| e1 | e2 |
//	|____|____|____|____|____|
//	west      | s1 |      east
//	          |____|
//	          | s2 |
//	          |____|
//       south
//////
	bool iivvmt_testSll4_1(u64 lnHandleLog, SLL4** root)
	{
		SLL4Callback	cb;
		u64				lnSha1As64Bit;
		u32				lnSha1As32Bit;
		u8				sha20Bytes[20];
		u8				context[92];
		SLL4*			nodeNorth2;
		SLL4*			nodeSouth2;
		SLL4*			nodeWest2;
		SLL4*			nodeEast2;
		SLL4*			nodeNorth1;
		SLL4*			nodeSouth1;
		SLL4*			nodeWest1;
		SLL4*			nodeEast1;


		//////////
		// Tell them which test we're running
		//////
			vvm_resourcePrintf(IDS_VVM_TEST_SLL4_CREATE);


		//////////
		// Create a single node
		//////
			*root = i3vvmt_testSll4_1_createSll4(cgnLl4BufferSize);
			if (!*root)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_UNABLE_TO_CREATE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}
			// Initialize our callback data
			cb._func	= (u64)&i3vvmt_testSll4_1_sha1Callback;
			cb.extra1	= (u64)&context[0];
			cb.extra2	= (u64)&sha20Bytes[0];


		//////////
		// Determine the SHA-1 on that one node
		//////
			oss_sha1ComputeSha1_Start(context);
			cb.node = *root;
			oss_ll4_iterateViaCallback(&cb, _LL4_EAST);
			oss_sha1ComputeSha1_FinishAsSha1(context, sha20Bytes, false);
			oss_sha1Compute64BitFromSha1(sha20Bytes);

			lnSha1As64Bit	= oss_sha1Compute64BitFromSha1(sha20Bytes);
			lnSha1As32Bit	= oss_sha1Compute32BitFromSha1(sha20Bytes);
			if (lnSha1As64Bit != cgnTestLl41NodeSha1As64Bit || lnSha1As32Bit != cgnTestLl41NodeSha1As32Bit)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_SHA1_FAILURE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}
			// If we get here, we're good


		//////////
		// Create a node to go to the west
		//////
			nodeWest2 = i3vvmt_testSll4_1_createSll4(cgnLl4BufferSize);
			if (!nodeWest2)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_UNABLE_TO_CREATE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}


		//////////
		// Create a node to go to the east
		//////
			nodeEast2 = i3vvmt_testSll4_1_createSll4(cgnLl4BufferSize);
			if (!nodeEast2)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_UNABLE_TO_CREATE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}


		//////////
		// Create a node to go to the north
		//////
			nodeNorth2 = i3vvmt_testSll4_1_createSll4(cgnLl4BufferSize);
			if (!nodeNorth2)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_UNABLE_TO_CREATE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}


		//////////
		// Create a node to go to the south
		//////
			nodeSouth2 = i3vvmt_testSll4_1_createSll4(cgnLl4BufferSize);
			if (!nodeSouth2)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_UNABLE_TO_CREATE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}


		//////////
		// Insert the node to the west
		//////
			oss_ll4_insertEastWest(nodeWest2, *root, false);


		//////////
		// Determine the SHA-1 on the two nodes
		//////
			oss_sha1ComputeSha1_Start(context);
			cb.node = nodeWest2;
			oss_ll4_iterateViaCallback(&cb, _LL4_EAST);
			cb.node = *root;
			oss_ll4_iterateViaCallback(&cb, _LL4_WEST);
			oss_sha1ComputeSha1_FinishAsSha1(context, sha20Bytes, false);
			oss_sha1Compute64BitFromSha1(sha20Bytes);

			lnSha1As64Bit	= oss_sha1Compute64BitFromSha1(sha20Bytes);
			lnSha1As32Bit	= oss_sha1Compute32BitFromSha1(sha20Bytes);
			if (lnSha1As64Bit != cgnTestLl42NodeSha1As64Bit || lnSha1As32Bit != cgnTestLl42NodeSha1As32Bit)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL_SHA1_FAILURE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}
			// If we get here, we're good


		//////////
		// Insert the node to the east
		//////
			oss_ll4_insertEastWest(nodeEast2, *root, true);


		//////////
		// Determine the SHA-1 on the three nodes
		//////
			oss_sha1ComputeSha1_Start(context);
			cb.node = nodeWest2;
			oss_ll4_iterateViaCallback(&cb, _LL4_EAST);
			cb.node = nodeEast2;
			oss_ll4_iterateViaCallback(&cb, _LL4_WEST);
			oss_sha1ComputeSha1_FinishAsSha1(context, sha20Bytes, false);
			oss_sha1Compute64BitFromSha1(sha20Bytes);

			lnSha1As64Bit	= oss_sha1Compute64BitFromSha1(sha20Bytes);
			lnSha1As32Bit	= oss_sha1Compute32BitFromSha1(sha20Bytes);
			if (lnSha1As64Bit != cgnTestLl43NodeSha1As64Bit || lnSha1As32Bit != cgnTestLl43NodeSha1As32Bit)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL_SHA1_FAILURE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}
			// If we get here, we're good


		//////////
		// Insert the node to the north
		//////
			oss_ll4_insertNorthSouth(nodeNorth2, *root, false);


		//////////
		// Determine the SHA-1 on the two nodes
		//////
			oss_sha1ComputeSha1_Start(context);
			cb.node = nodeNorth2;
			oss_ll4_iterateViaCallback(&cb, _LL4_SOUTH);
			cb.node = *root;
			oss_ll4_iterateViaCallback(&cb, _LL4_NORTH);
			cb.node = nodeWest2;
			oss_ll4_iterateViaCallback(&cb, _LL4_EAST);
			cb.node = nodeEast2;
			oss_ll4_iterateViaCallback(&cb, _LL4_WEST);
			oss_sha1ComputeSha1_FinishAsSha1(context, sha20Bytes, false);
			oss_sha1Compute64BitFromSha1(sha20Bytes);

			lnSha1As64Bit	= oss_sha1Compute64BitFromSha1(sha20Bytes);
			lnSha1As32Bit	= oss_sha1Compute32BitFromSha1(sha20Bytes);
			if (lnSha1As64Bit != cgnTestLl44NodeSha1As64Bit || lnSha1As32Bit != cgnTestLl44NodeSha1As32Bit)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL_SHA1_FAILURE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}
			// If we get here, we're good


		//////////
		// Insert the node to the south
		//////
			oss_ll4_insertNorthSouth(nodeSouth2, *root, true);


		//////////
		// Determine the SHA-1 on the three nodes
		//////
			oss_sha1ComputeSha1_Start(context);
			cb.node = nodeNorth2;
			oss_ll4_iterateViaCallback(&cb, _LL4_SOUTH);
			cb.node = nodeSouth2;
			oss_ll4_iterateViaCallback(&cb, _LL4_NORTH);
			cb.node = nodeWest2;
			oss_ll4_iterateViaCallback(&cb, _LL4_EAST);
			cb.node = nodeEast2;
			oss_ll4_iterateViaCallback(&cb, _LL4_WEST);
			oss_sha1ComputeSha1_FinishAsSha1(context, sha20Bytes, false);
			oss_sha1Compute64BitFromSha1(sha20Bytes);

			lnSha1As64Bit	= oss_sha1Compute64BitFromSha1(sha20Bytes);
			lnSha1As32Bit	= oss_sha1Compute32BitFromSha1(sha20Bytes);
			if (lnSha1As64Bit != cgnTestLl45NodeSha1As64Bit || lnSha1As32Bit != cgnTestLl45NodeSha1As32Bit)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL_SHA1_FAILURE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}
			// If we get here, we're good


		//////////
		// Create a node to go to the west
		//////
			nodeWest1 = i3vvmt_testSll4_1_createSll4(cgnLl4BufferSize);
			if (!nodeWest1)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_UNABLE_TO_CREATE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}


		//////////
		// Create a node to go to the east
		//////
			nodeEast1 = i3vvmt_testSll4_1_createSll4(cgnLl4BufferSize);
			if (!nodeEast1)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_UNABLE_TO_CREATE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}


		//////////
		// Create a node to go to the north
		//////
			nodeNorth1 = i3vvmt_testSll4_1_createSll4(cgnLl4BufferSize);
			if (!nodeNorth1)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_UNABLE_TO_CREATE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}


		//////////
		// Create a node to go to the south
		//////
			nodeSouth1 = i3vvmt_testSll4_1_createSll4(cgnLl4BufferSize);
			if (!nodeSouth1)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL4_UNABLE_TO_CREATE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}


		//////////
		// Insert the node to the west
		//////
			oss_ll4_insertEastWest(nodeWest1, *root, false);


		//////////
		// Determine the SHA-1 on the two nodes
		//////
			oss_sha1ComputeSha1_Start(context);
			cb.node = nodeNorth2;
			oss_ll4_iterateViaCallback(&cb, _LL4_SOUTH);
			cb.node = nodeSouth2;
			oss_ll4_iterateViaCallback(&cb, _LL4_NORTH);
			cb.node = nodeWest2;
			oss_ll4_iterateViaCallback(&cb, _LL4_EAST);
			cb.node = nodeEast2;
			oss_ll4_iterateViaCallback(&cb, _LL4_WEST);
			oss_sha1ComputeSha1_FinishAsSha1(context, sha20Bytes, false);
			oss_sha1Compute64BitFromSha1(sha20Bytes);

			lnSha1As64Bit	= oss_sha1Compute64BitFromSha1(sha20Bytes);
			lnSha1As32Bit	= oss_sha1Compute32BitFromSha1(sha20Bytes);
			if (lnSha1As64Bit != cgnTestLl46NodeSha1As64Bit || lnSha1As32Bit != cgnTestLl46NodeSha1As32Bit)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL_SHA1_FAILURE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}
			// If we get here, we're good


		//////////
		// Insert the node to the east
		//////
			oss_ll4_insertEastWest(nodeEast1, *root, true);


		//////////
		// Determine the SHA-1 on the three nodes
		//////
			oss_sha1ComputeSha1_Start(context);
			cb.node = nodeNorth2;
			oss_ll4_iterateViaCallback(&cb, _LL4_SOUTH);
			cb.node = nodeSouth2;
			oss_ll4_iterateViaCallback(&cb, _LL4_NORTH);
			cb.node = nodeWest2;
			oss_ll4_iterateViaCallback(&cb, _LL4_EAST);
			cb.node = nodeEast2;
			oss_ll4_iterateViaCallback(&cb, _LL4_WEST);
			oss_sha1ComputeSha1_FinishAsSha1(context, sha20Bytes, false);
			oss_sha1Compute64BitFromSha1(sha20Bytes);

			lnSha1As64Bit	= oss_sha1Compute64BitFromSha1(sha20Bytes);
			lnSha1As32Bit	= oss_sha1Compute32BitFromSha1(sha20Bytes);
			if (lnSha1As64Bit != cgnTestLl47NodeSha1As64Bit || lnSha1As32Bit != cgnTestLl47NodeSha1As32Bit)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL_SHA1_FAILURE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}
			// If we get here, we're good


		//////////
		// Insert the node to the north
		//////
			oss_ll4_insertNorthSouth(nodeNorth1, *root, false);


		//////////
		// Determine the SHA-1 on the two nodes
		//////
			oss_sha1ComputeSha1_Start(context);
			cb.node = nodeNorth2;
			oss_ll4_iterateViaCallback(&cb, _LL4_SOUTH);
			cb.node = nodeSouth2;
			oss_ll4_iterateViaCallback(&cb, _LL4_NORTH);
			cb.node = nodeWest2;
			oss_ll4_iterateViaCallback(&cb, _LL4_EAST);
			cb.node = nodeEast2;
			oss_ll4_iterateViaCallback(&cb, _LL4_WEST);
			oss_sha1ComputeSha1_FinishAsSha1(context, sha20Bytes, false);
			oss_sha1Compute64BitFromSha1(sha20Bytes);

			lnSha1As64Bit	= oss_sha1Compute64BitFromSha1(sha20Bytes);
			lnSha1As32Bit	= oss_sha1Compute32BitFromSha1(sha20Bytes);
			if (lnSha1As64Bit != cgnTestLl48NodeSha1As64Bit || lnSha1As32Bit != cgnTestLl48NodeSha1As32Bit)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL_SHA1_FAILURE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}
			// If we get here, we're good


		//////////
		// Insert the node to the south
		//////
			oss_ll4_insertNorthSouth(nodeSouth1, *root, true);


		//////////
		// Determine the SHA-1 on the three nodes
		//////
			oss_sha1ComputeSha1_Start(context);
			cb.node = nodeNorth2;
			oss_ll4_iterateViaCallback(&cb, _LL4_SOUTH);
			cb.node = nodeSouth2;
			oss_ll4_iterateViaCallback(&cb, _LL4_NORTH);
			cb.node = nodeWest2;
			oss_ll4_iterateViaCallback(&cb, _LL4_EAST);
			cb.node = nodeEast2;
			oss_ll4_iterateViaCallback(&cb, _LL4_WEST);
			oss_sha1ComputeSha1_FinishAsSha1(context, sha20Bytes, false);
			oss_sha1Compute64BitFromSha1(sha20Bytes);

			lnSha1As64Bit	= oss_sha1Compute64BitFromSha1(sha20Bytes);
			lnSha1As32Bit	= oss_sha1Compute32BitFromSha1(sha20Bytes);
			if (lnSha1As64Bit != cgnTestLl49NodeSha1As64Bit || lnSha1As32Bit != cgnTestLl49NodeSha1As32Bit)
			{
				// Failure
				vvm_resourcePrintf(IDS_VVM_TEST_SLL_SHA1_FAILURE);
				vvm_resourcePrintf(IDS_VVM_TEST_FAIL);
				return(false);
			}
			// If we get here, we're good


		// If we get here, we're good
		vvm_resourcePrintf(IDS_VVM_TEST_PASS);
		return(true);
	}




	bool iivvmt_testSll4_2(u64 lnHandleLog, SLL4* root)
	{
		//////////
		// Tell them which test we're running
		//////
			vvm_resourcePrintf(IDS_VVM_TEST_SLL4_APPEND);


		// If we get here, we're good
		vvm_resourcePrintf(IDS_VVM_TEST_PASS);
		return(true);
	}




	bool iivvmt_testSll4_3(u64 lnHandleLog, SLL4** root)
	{
		//////////
		// Tell them which test we're running
		//////
			vvm_resourcePrintf(IDS_VVM_TEST_SLL4_DELETE);


		// If we get here, we're good
		vvm_resourcePrintf(IDS_VVM_TEST_PASS);
		return(true);
	}




	SLL4* i3vvmt_testSll4_1_createSll4(u32 tnSize)
	{
		u32		lnI;
		SLL4*	ll4;
		u8*		llInit;
		
		
		//////////
		// Create the SLL
		//////
			ll4 = oss_ll4_create(NULL, NULL, NULL, NULL, oss_getNextUniqueId(), tnSize);


		//////////
		// Prepare that value
		//////
			if (ll4)
			{
				// Iterate through every portion to initialize
				llInit = (u8*)ll4 + sizeof(SLL4);
				for (lnI = 0; lnI < tnSize; lnI++)
					llInit[lnI] = oss_getPredictableSequentialPattern(lnI, gnLlInitializerValue++);
			}


		//////////
		// Indicate our success or failure
		//////
			return(ll4);
	}




	void i3vvmt_testSll4_1_sha1Callback(SOssCbData2Void* cb)
	{
		if (cb)
		{
			// Conduct our processing
			oss_sha1ComputeSha1_ProcessThisData((u8*)cb->extra1, (s8*)cb->ptr + sizeof(SLL4), cgnLlBufferSize);
		}
	}
