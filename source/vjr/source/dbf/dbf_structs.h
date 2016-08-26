//////////
//
// /libsf/source/vjr/source/dbf/dbf_structs.h
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
// Copyright (c) 2014-2015 by Rick C. Hodgin
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




//////////
//
// Structures
//
//////
	struct _isSKeyFinds;
	struct SCdxHeader;
	struct SIdxHeader;
	struct SForClause;
	struct SCdxKeyOp;
	struct SDbfRender;


	//////////////
	// Fixed DBF header portion
	//////
		struct STableHeader
		{
			u8		type;					// Offset  0, Length 1
			u8		lastUpdate[3];			// Offset  1, Length 3
			u32		records;				// Offset  4, Length 4
			u16		firstRecord;			// Offset  8, Length 2
			u16		recordLength;			// Offset 10, Length 2
			u8		reserved1[16];			// Offset 12, Length 16
			u8		flags;					// Offset 28, Length 1
			u8		codePage;				// Offset 29, Length 1
			u8		reserved2[2];			// Offset 30, Length 2
			// Total:  32 bytes
		};


	//////////
	// Field records within the variable portion of the DBF header
	// Actual DBF field record content
	//////
		struct SFieldRecord1
		{
			// Valid types:
			//		C?Character		Y?Currency	D?Date		T-DateTime
			//		B?Double		F?Float		G?General	I?Integer
			//		L?Logical		M?Memo		N?Numeric	P?Picture
			//		Q-Varbinary		V-Varchar (binary)

			u8		name[11];				// Offset  0, Length 11
			u8		type;					// offset 11, Length  1
			u32		offset;					// Offset 12, Length  4
			u8		length;					// Offset 16, Length  1
			u8		decimals;				// Offset 17, Length  1


			//////////
			// Flags:
			//		0x01 - System (not visible to user, such as null flags)
			//		0x02 - Can store NULLs
			//		0x04 - Binary (NOCPTRANS)
			//		0x0c - Auto-incrementing
			//////
				u8		flags;					// Offset 18, Length  1
				u32		autoIncNext;			// Offset 19, Length  4
				u8		autoIncStep;			// Offset 23, Length  1


			//////////
			// Miscellaneous/internal fields
			//////
				union {							// Offset 24, Length  1
					u8	reserved1;
					u8	fieldName_length;		// As used by VJr
				};

				union {
					u8	reserved2;				// Offset 25, Length  1
					u8	fillChar;				// As used by VJr
				};

				u8		reserved3;				// Offset 26, Length  1

			//////////
			// Part of reserved space, used internally
			//////
				u8		indexFixup_lengthOverride;	// Offset 27, Length  1		// For numeric fields, for example, which index on f64 equivalents
				u32		indexFixup;					// Offset 28, Length  4		// For copying to index keys, what fixup operation is required on this field?

			// Total:  32 bytes
		};


	//////////
	// More or less a copy of the SFieldRecord, but stores longer
	// field names and additional fields used by VXB/VXB++.
	//////
	// Internally, these records are always used and then
	// synchronized back to SFieldRecord1, and to the DBC
	//////
		struct SFieldRecord2
		{
			// Copy of:
			u8			name[11];				// SFieldRecord1->name
			u8			type;					// SFieldRecord1->type
			u32			offset;					// SFieldRecord1->offset
			u8			length;					// SFieldRecord1->length
			u8			decimals;				// SFieldRecord1->decimals
			u8			flags;					// SFieldRecord1->flags
			u32			autoIncNext;			// SFieldRecord1->autoIncNext
			u8			autoIncStep;			// SFieldRecord1->autoIncStep

			// New for SFieldRecord2:
			s32			fieldName_length;		// Length of the long field name derived from its dbc
			u8			name2[129];				// Long field name
			u32			fieldNumber;			// Field number within the table

			// Notes and meta data regarding the field
			s32			actualLength;			// Actual length of the field, such as integer needing to be 11 rather than 4 because of "-2147483648" (the maximum negative integer value)
// TODO:  Not yet included

			// Memo  data
			s8*			mdata;					// Current version
			u32			mdataLength;
			s8*			omdata;					// As originally loaded from disk
			u32			omdataLength;

			// Used for index creation
			u8			fillChar;				// The fill character required for this type of field
			u32			dbcRecno;				// The related dbc RECNO() this entry was found on
			u32			indexFixup;				// The fixup required to make the cdx work for this type of field

			// For selective processing
			bool		marked;					// Marked if this field is to be included

			// Used for rendering content into the buffer
			SDatum		renderHeader;			// The header (field name) used for listings
			SDatum		renderPrefix;			// The character(s) to insert before the rendered field content, typically a " for text, for example
			SDatum		renderPostfix;			// The character(s) to insert after the rendered field content, typically a " for text, for example
			SDatum		renderSpacer;			// The spacer used between fields in a list, typically a space or comma, for example
			SDatum		renderBuffer;			// Holds the render buffer, either points to renderBuffer254, or to another area for larger buffers
			s8			renderBuffer254[254];	// Holds common render content
			union {
				sptr	_renderFunc;
				s32		(*renderFunc)		(SDatum* row, SFieldRecord2* field2Ptr, SDbfRender* render);
			};
		};


	//////////
	// Memo header structure (if present)
	//////
		struct SMemoHeader
		{
			u32		nextFreeBlock;			// Next free block in the file
			u16		unused1;
			u16		blockSize;				// BLOCKSIZE (if 1..32, indicates # of 512 blocks to allocate, if 33+, indicates block size)
			// Total: 8
			s8		unused2[504];
			// Total: 512
		};


	//////////
	// Internal work area structures, relates to SELECT() locations
	//////
		struct SWorkArea
		{
			// Internal flags
			bool			isUsed;						// Is the work area used?
			sptr			thisWorkArea;				// Added to hold this entry's slot number
			bool			isCursor;					// For temporary tables, the tables, memo files, and indexes are deleted on close
			bool			isExclusive;				// true if this index was used exclusively
			bool			isNoUpdate;					// true if this is a read-only usage
			bool			isIndexLoaded;				// true if an index is loaded (idx, cdx, dcx)
			bool			isSdxLoaded;				// true if an sdx index is loaded
			bool			isCached;					// If the table's been cached, then it will be true, otherwise false
			bool			mayHaveCdxSdx;				// Only certain table types can have indexes
			bool			isVisualTable;				// Only visual tables can have DBC backlinks
			bool			isDirty;					// When data is written to the current record, but not flushed to disk, this is raised
			bool			isUnbuffered;				// Immediate writes upon every change
			bool			isDescending;				// If the table is displayed in descending order

			// Added primarily for debugging
			bool			isVisualized;				// Allows a graphical representation to be created similar to a disk defragger, with zooming in per block
			bool			isJournaled;				// Allows a journaled record of every change made

			// Names
			s8				tablePathname[_MAX_PATH];	// Filename to get to the table
			s32				tablePathnameLength;		// Length of the table filename
			s8				alias[_MAX_ALIAS_NAME_LENGTH];	// Alias associated with this
			s32				aliasLength;				// Length of the alias name


			// File handles for the related/opened table
			s32				fhDbf;						// File handle for the table
			SWorkArea*		dbc;						// The DBC this table relates to (if any)
			u32				dbc_parentRecno;			// in the DBC, the record number of the "Table" record
			u32				dbc_parentId;				// In the DBC, the parentId of the "Table" record
			u32				dbc_firstChildRecno;		// In the DBC, the record number of the first entry where the dbc_parentId is the parentId
			u32				dbc_firstFieldRecno;		// In the DBC, the record number of the first "Field" entry, which correlates to column 1 in the table, with each record after that sequentially being the next column


			// Header information
			STableHeader	header;						// Header for this table
			s8*				backlink;					// Pointer to the DBC backlink if any
			u32				backlinkLength;				// Length of the backlink filename
			u32				currentRecord;				// Current record pointed at


			// Fields
			SFieldRecord1*	fieldPtr1;					// Memory area holding the field listing (in raw FIELD_RECORD format)
			SFieldRecord2*	field2Ptr;					// Memory area holding the field listing (using a format suitable for long field names through containers)
			u32				fieldCount;					// Number of fields in the table

			// Locks
			SBuilder*		dbfLocks;					// Disk locks for shared file access

			// Memory for whatever
			union {
				uptr		_cachedTable;
				s8*			cachedTable;				// If isCached, then this holds the entire table contents as of when it was cached
			};


			//////////
			// Row data
			//////
				SDatum			row;					// Row data for current RECNO()
				SDatum			orow;					// Original row data, or after last flush
				SDatum			irow;					// Index accumulator row (for creating index keys)


			//////////
			// Memo data
			//////
				s32				fhMemo;					// Memo file handle
				SMemoHeader		memoHeader;				// Memo header
				SBuilder*		memoLocks;				// Disk locks for shared file access

			
			//////////
			// Journaling
			//////
				s32				fhJrn;					// Journal file handle
				SBuilder*		journal;				// Records transactions until written


			//////////
			// IDX and CDX index support
			//////
				s8				idxCdxDcxPathname[_MAX_PATH];	// Filename to get to the index (either .cdx, .idx, or other .?cx for internal files which have indexes)
				u32				idxCdxDcxPathnameLength;		// Length of the index filename
				_isSKeyFinds	cdx_keyOps[_MAX_CDX_TAGS];		// Room for up to N tags
				bool			isCdx;							// Is it a CDX (also DCX)?  If no, then is IDX.
				bool			isIdxCompact;					// If it's IDX, is it a compact IDX?
				u32				idxCdxDcxLastError;				// The last index error that was encountered
				s8				cdx_tagName[32];				// Name of the index tag
				u32				cdx_activeTagRootNode;			// Current active tag's root node
				union {
					// CDX/DCX support
					SCdxHeader*	cdx_root;
					s8*			_cdx_header;

					// IDX support
					SIdxHeader*	idx_header;
					s8*			_idx_header;
				};

				// Index file operations
				s32				fhIdxCdxDcx;					// File handle for the index
				SBuilder*		idxCdxDcxFileLocks;				// Locks for shared access
				SBuilder*		idxCdxDcxNodeCache;				// Cached node blocks (SCdxNodeCache)


			//////////
			// SDX (secure) index support
			//////
				s8				sdxPathname[_MAX_PATH];			// Filename to get to the index (.sdx)
				u32				sdxPathnameLength;				// Length of the index filename
				_isSKeyFinds	sdx_keyOps[_MAX_SDX_TAGS];		// Room for up to N tags
				s8				sdx_tagName[64];				// Name of the index tag
				bool			isSdx;							// Is an SDX loaded?
				union {
					// SDX support
					SSdxHeader*	sdx_root;
					s8*			_sdx_header;
				};

				// Index file operations
				s32				fhSdx;							// File handle for the index
				SBuilder*		sdxFileLocks;					// Locks for shared access
		};

		// Used when rendering data into a row
		struct SDbfRender
		{
			bool	century;									// SET CENTURY
			s8		currency;									// SET CURRENCY
			s32		date;										// SET DATE
			s32		decimals;									// SET DECIMALS
			s32		hours;										// SET HOURS
			s32		logical;									// SET LOGICAL
			s8		mark;										// SET MARK TO
			s8		point;										// SET POINT
			s8		separator;									// SET SEPARATOR
			bool	fixed;										// SET FIXED setting
			s8		format[8];									// Format to use for displaying integers, typically "%.3f" (when SET DECIMALS TO 3 is set, for example)
			s8		format_recno[8];							// Format to use for the RECNO() based on how many records there are in the file, like "%6d "
		};
