//////////
//
// /libsf/source/vjr/source/dbf/cdx_structs.h
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
// Version 0.55
// Copyright (c) 2014 by Rick C. Hodgin
//////
// Last update:
//     Dec.22.2014
//////
// Change log:
//     Dec.22.2014 - Initial creation
//////
//
// This document is released as Liberty Software under a Repeat License, as governed
// by the Public Benefit License v1.0 or later (PBL).
//
// The PBL is a public domain license with a caveat:  self accountability unto God.
// You are free to use, copy, modify and share this software for any purpose, however,
// it is the desire of those working on this project that the software remain open.
// It is our request that you maintain it that way.  This is not a legal request unto
// our court systems, but rather a personal matter between you and God.  Our talents
// were received from God, and given to you through this forum.  And it is our wish
// that those talents reach out to as many as possible in a form allowing them to wield
// this content for their own betterment, as you are now considering doing.  And whereas
// we could've forced the issue through something like a copyleft-protected release, the
// truth is we are all giving an account of our lives unto God continually by the daily
// choices we make.  And here again is another case where you get to demonstrate your
// character unto God, and unto your fellow man.
//
// Jesus came to this Earth to set the captives free, to save men's eternal souls from
// the punishment demanded by our sin.  Each one of us is given the opportunity to
// receive Him in this world and be saved.  Whether we choose to receive Him, and follow
// Him, and purpose our lives on the goals He has for each of us (all of which are
// beneficial for all involved), is one way we reveal our character continually.  God
// sees straight through to the heart, bypassing all of the words, all of the facades.
// He is our Creator, and He knows who we are truly.
//
// Jesus is called "Christ" because He saves men from the eternal flames of Hell, the
// just punishment of rebellion against God (rebellion against truth) by eternal beings,
// which each of us are.
//
// Do not let His free gift escape you because of some desire to shortcut what is right
// in your life. Instead, do what is right, and do it because He is who He is, and what
// He has done to save us from such a fate.  Demonstrate to Him, to me, and to all of
// mankind, and to all of the Heavenly hosts, exactly who you are on the inside.  Receive
// Jesus Christ into your heart, learn of Him, of how He came here to guide us into that
// which is of His Kingdom and will be forever hereafter we leave this world.  Do this,
// and live.
//
// Every project released by Liberty Software Foundation will include a copy of the
// pbl.txt document, which can be found at http://www.libsf.org/licenses/.
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
//




struct SForClause;
struct SCdxKeyOp;



//////////
// Structure used for holding FOR clause tests for each record or index key
/////
	// An internal structure (_is) for speeding through successive data finds
	struct _isSKeyFinds
	{
		// FOR clause (if any)
		SForClause*		forClause;

		// Key operations to generate an index key
		SCdxKeyOp*		keyOps;
		s32				keyOpCount;				// Number of keys in key ops
	};


//////////
// CDX-specific structures
//////
	// Steps used in building index keys from fiel data
	struct SCdxKeyOp
	{
		u32		offsetRow;						// Offset into the row data
		u32		offsetKey;						// Offset into the key data
		s32		length;							// Length of the index key generated for the field
		s32		fieldLength;					// Length of the raw field contents
		u32		indexFixup;						// Any fixup operation to perform on this portion of the key data

		// For fields that support NULL values
		u32		null_offset;					// Offset into the row data
		u8		null_mask;						// Byte mask to determine if the field is NULL
	};

	// A CDX key pointer into a leaf node
	struct SCdxKeyLeaf
	{
		// If keyLength is 0, then this will be node, otherwise it's the record number in big-endian form (needs BSWAP run on it)
		union {
			u32		record;						// Converted from its native type to little-endian form automatically
			u32		fileOffset;					// In little-endian form
		};
		u32			record2;					// Compact indexes store both the record number and file_offset for root and index nodes
		u32			offset;						// Offset from the end of the node where this key begins

		// Pointer to the key data
		u32			keyLength;					// Length of the key


	//////////
	// Note:  There is a constraint in the design that this always be the last member.
	//        The data is copied above using memcpy(dst, src, sizeof(SCdxKeyLeaf) - sizeof(dst.keyPtr));
	//////
		u8*			keyPtr;						// Reconstructed key from its compact form
	};

	// A copy of the data in SCdxKeyLeaf, but one which holds the actual key contents, used for passing keys back and forth
	struct SCdxKeyLeafRaw
	{
		// If keyLength is 0, then this will be node, otherwise it's the record number in big-endian form (needs BSWAP run on it)
		union {
			u32		recordNumber;				// Converted from its native type to little-endian form automatically
			u32		fileOffset;					// (for index nodes) in little-endian form
		};
		u32			record2;					// Compact indexes store both the record number and file_offset for root and index nodes
		u32			offset;						// Offset from the end of the node where this key begins

		// Pointer to the key data
		u32			keyLength;					// Length of the key
		u8			key[256];					// Reconstructed key from its compact form
	};

	// Used during node traversal
	struct SCdxKeyTrailInterior
	{
		u32			record2;					// Record number
		u32			fileOffset;					// File offset to access related node
	};

	// Holds information about the leaf key header (the part which increases from offset 0)
	struct SCdxKeyTrail
	{
		u32			record;						// Record number
		u16			count_DC;					// Duplicate byte count
		u16			count_TC;					// Trailing byte count
	};

	// Holds root node information for individual CDX tags, and also raw IDX nodes
	struct STagRoot
	{
		u32			leftmostNode;				// Offset to first node of the index
		u32			highestNode;				// Offset to the highest node of the index
		bool		indexIsDesc;				// Is this a descending index?
		u32			keyLength;					// Length of the key for this tag

		u8			fillChar;					// Based on the index expression, will either be a space or null
		bool		swapEndians;				// Based on the index expression, it can be stored big-endian if it's an integer, currency, float, or double
		bool		needsSignBitToggled;		// Based on the index expression, if it's integer, currency, float or double, after the big-endian to little-endian swap, it needs the most significant bit toggled, and if negative, then it needs all bits toggled

		// Only used if a CDX node
		u32			keyNode;					// Offset to node holding key information
		u8			tagName[10];				// Tag name
	};

	// Holds information about a CDX leaf node
	struct SCdxNode
	{
		u16			type;						// 0,2		0=index node, 1=root node, 2=leaf node, 3=root+leaf. There are also types where bit3 is enabled, but I cannot find documentation as to what it is.  As such, we use the (type & 0x3) comparison for everything to mask off those bits.
		u16			keyCount;					// 2,2		Number of keys in this node which have this index key
		u32			nodeLeft;					// 4,4		Node going left, -1 if none
		u32			nodeRight;					// 8,4		Node going right, -1 if none
		// Non-compact keys begin immediately after this
												// 12,N		Up to 488 bytes for the non-compact index keys
												// 512 bytes max

		// nodeFreeSpace is only used if is an exterior/leaf node
		u16			nodeFreeSpace;				// 12,2		Number of bytes available in this node

		// The following are in compact indexes
		u32			mask_RN;					// 14,4		(RN) Record Number mask
		u8			mask_DC;					// 18,1		(DC) Duplicate byte Count mask
		u8			mask_TC;					// 19,1		(TC) Trailing byte Count mask
		u8			bits_RN;					// 20,1		Number of bits used for record number
		u8			bits_DC;					// 21,1		Number of bits used for duplicate count
		u8			bits_TC;					// 22,1		Number of bits used for trail count
		u8			totalBytesIn_RNDCTC;		// 23,1		?? Don't know
		// Keys begin immediately after this	// 24,N		Up to 488 bytes for the compact index keys
		// Key data
		u8			keyBuffer[488];				// 24,488
		// 512 bytes max
	};

	struct SCdxNodeKey
	{
		SDatum		key;						// Pointer to the key
		u32			recno;						// The associated record number
	};

	struct SCdxNodeCache
	{
//////////
//	Note:  this.keyDecodedInUse may be different than this.cachedNode->keyCount.  The this.keyDecodedInUse
//	       value indicates the number of keys currently in the node, while this.cachedNode->keyCount
//	       indicates the number of keys on the node on the disk.  In a shared environment they should
//	       always be in sync.  In an exclusive environment, they can be vastly different.
//////////
		struct {
			bool		isUsed				: 1;	// 0,1		Is this node cache entry actually in use?
			bool		isDirty				: 1;	// 1,1		Does this decode buffer contain any uncommitted changes?
			u16			free				: 12;	// 2,12		Unused
			u32			keyDecodedAllocated	: 9;	// 14,9		Allocated key count
			u32			keyDecodedInUse		: 9;	// 23,9		Decoded key (in use) count
		};											// ------
													// 0,4		32 bits total in the bit structure
		SCdxNodeKey**	keyDecodedBuffer;			// 4,4		Pointers to all of the keys in this node (first key = keys[0], second = keys[1], and so on)
		s32				nodeNum;					// 8,4		Physical node within the index file on disk (may be uncommitted, existing only in memory)
		SCdxNode*		cachedNode;					// 12,4		Node header and key buffer cached previously from disk (may be NULL)
		// Total:  16 bytes
	};

	// This structure is the first found in the CDX, but it is also the same structure used
	// for each index tag contained within.
	struct SCdxHeader
	{
		u32			root;						// 0,4		Pointer to the root node (SCdxInteriorNode*)
		u32			free;						// 4,4		Pointer to the first free node (-1 if not present) (SCdxInteriorNode*)
		union {
			u32		reserved1;					// 8,4
			u32		fileSize;					// Note:  Used internally only, this is not stored on the disk
		};
		u16			keyLength;					// 12,2		Number of bytes in each key
		u8			options;					// 14,1		1=UNIQUE, 2=Temporary index, 4=Custom index, 8=FOR clause, 16=??, 32=Compact, 64=Compound, 128=Structural index
		u8			signature;					// 15,1		Index signature

		// The last recno() obtained from the last accessed index key
		union {
			u32		reserved2;					// 16,4
			u32		lastRecno;
		};

		// The last node that the last key was at/on
		union {
			u32		reserved3;					// 20,4
			u32		lastNode;
		};

		// The last slot within the last node the last key was found at/on
		union {
			u32		reserved4;					// 24,4
			u32		lastSlotInNode;
		};

		u32			reserved5;					// 28,4
		u32			reserved6;					// 32,4
		u8			reserved7[466];				// 36,466

		u16			order;						// 502,2	0=Ascending, 1=Descending
		u16			reserved8;					// 504,2

		u16			forClauseLength;			// 506,2	Length of FOR clause
		u16			reserved9;					// 508,2

		u16			keyExpressionLength;		// 510,2	Length of index key expression
		u8			keyExpression[512];			// 512,512	The key and FOR clause expression storage area, in that order, each is NULL-terminated
		// 1024 bytes
	};

	// Pointer to each key record in an IDX leaf node
	struct SIdxKey
	{
		// Pointer to the key data
		union {
			uptr	_key;						// Same value in 32-bit form
			u8*		key;						// Pointer to the key data
		};

		u32			keyLength;					// Length of the key

		// If keyLength is 0, then this will be node, otherwise it's the record number in big-endian form (needs BSWAP run on it)
		union {
			uptr	record;						// Converted from its native type to little-endian form automatically
			u32*	node;						// In little-endian form
		};
	};

	// Every IDX node has this header
	struct SIdxNode
	{
		u16			type;						// 0,2		0=index node, 1=root node, 2=leaf node
		u16			keyCount;					// 2,2		Number of keys in this node which have this index key
		u32			nodeLeft;					// 4,4		Node going left, -1 if none
		u32			nodeRight;					// 8,4		Node going right, -1 if none
		// Immediately after this is additional variable-length data:
		// Repeating:
		//		12 + keyLength + (keyCount*4) bytes
		//		Note:  There may be garbage beyond the valid populated data stored in the index nodes, it should be ignored.
	};

	// The first node in an IDX file
	struct SIdxHeader
	{
		u32			root;						// 0,4		Offset to the root node (SIdxNode*)
		u32			free;						// 4,4		Offset to the first free node (-1 if not present) (SIdxNode*)
		u32			fileSize;					// 8,4		File size in bytes
		u16			keyLength;					// 12,2		Number of bytes in each key
		u8			options;					// 14,1		1=UNIQUE, 8=FOR clause, 32=Compact IDX
		u8			reserved1;					// 15,1
		u8			keyExpression[220];			// 16,220	Key expression itself
		u8			forClause[220];				// 236,220	FOR clause expression
		u8			reserved2[56];				// 456,56
		// Total size: 512 bytes
	};

	// This structure is the first found in the SDX
	struct SSdxHeader
	{
		s8			keyData[4096];				// 0,4096	Key data used for decrypting the rest of the SDX
		// 4096 bytes
// Note: This is a placeholder.  The remainder of the SDX file structure has not been released publicly yet.
	};




//////////
// Used for processing DBF and CDX data
//////
	struct SForOp
	{
		// Row/temp data for left-hand thing
		union {
			uptr		tempIndexL;				// Index into the temporary data
			uptr		offsetL;				// Offset into the row data
		};
		uptr			lengthL;				// Length of the thing to compare (typically also always the right-hand length as well if used)

		// Row/temp data for right-hand thing
		union {
			uptr		tempIndexR;				// Index into the temporary data
			uptr		offsetR;				// Offset into the row data
		};

		// See _FOR_CLAUSE_OPS_* constants in dbf_defs.h
		u32				op;				// The operation to conduct
	};

	// Temporary data space used for constants found in the FOR expression
	struct SForTemp
	{
		s8*				data;					// Data for this temporary
		uptr			length;					// Length of the data
	};

	// For multiple entries in the FOR clause
	struct SForSubItem
	{
		u8*				start;					// Pointer to the starting item
		u8*				end;					// Where it ends
		uptr			length;					// Length

		u32				type;					// Known type
	};

	// For clauses are executed on each line to determine a result
	// They are a series of operations
	struct SForClause
	{
		SForOp*			ops;					// A list of operations to perform on the row data
		s32				opCount;				// Number of items in the for clause test
		s32				opAllocated;			// Number of ops allocated

		SForSubItem*	subitems;				// Access to sub-items in the expression
		s32				subitemCount;			// Number of subitems in use
		s32				subitemAllocated;		// Number of subitems allocated

		SForTemp*		temps;					// A list of temporaries referenced by SForClauseOp->operation
		s32				tempCount;				// Number of temporary items
		s32				tempAllocated;			// Number of temporary items allocated
	};
