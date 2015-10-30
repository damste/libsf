//////////
//
// /libsf/source/vjr/source/compiler/vxb/vxb_structs.h
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
// Version 0.57
// Copyright (c) 2014 by Rick C. Hodgin
//////
// Last update:
//     Jun.29.2014
//////
// Change log:
//     Jun.29.2014 - Initial creation
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
//////
//   ___      ___   ___  ___    _______
//  |"  \    /"  | |"  \/"  |  |   _  "\
//   \   \  //  /   \   \  /   (. |_)  :)
//    \\  \/. ./     \\  \/    |:     \/
//     \.    //      /\.  \    (|  _  \\
//      \\   /      /  \   \   |: |_)  :)
//       \__/      |___/\___|  (_______/
//     Visual FreePro, Jr. XBase Compiler
//
//////////




struct SStartEnd;
struct SMasterList;
struct SComp;
struct SCompCallback;
struct SNode;
struct SOp;
struct SAsciiCompSearcher;
struct SStartEndCallback;
struct SLL;
struct SLLCallback;
struct SVariable;
struct SCompileStats;
struct SNoteLog;
struct SDateTimeX;




//////////
// Structures taken from Visual FreePro
//////
	struct SMasterList
	{
		SLL				ll;						// 2-way link list to hold the related pointer
		bool			used;					// Is this entry/slot used?

		// The reference pointer used to occupy this slot/position
		void*			ptr;					// The pointer associated with this entry
	};

	// The rigidity of this structure is extremely important.
	// Every item in the chain between root and last must be included in the master list!
	struct SStartEnd
	{
		SMasterList*	root;					// Root item
		SMasterList*	last;					// Last item

		// SStartEnd lists can have a master (which points to other items using the SMasterList protocol), or it can be used merely a pointer holder
		union {
			SMasterList**	master;				// Every item in the start/end chain is appended here when created (used primarily for suspension and resumption of the VVM)
			void**			ptr;
		};
		u32				masterCount;			// Number of entries in the master array (used for resizing)

		// Not used and reserved for future use
		void*			extra;					// For future expansion
	};

	struct SFunction
	{
		SLL				ll;
		bool			isPrivate;										// Used only on adhocs, and only when they are declared private (meaning they're used locally only within the one function they're declared, and are not visible to any called child functions)
		SDatum			name;											// Function name (Note that code appearing at the top of a program without being enclosed in a function will have the source code line "FUNCTION top_of_program" automatically inserted at compile time

		// Function code?
		SEM*			sem;											// Function source code
		SLine*			firstLine;										// Within sem, the first line for the function
		SLine*			lastLine;										// Within sem, the last line for the function
		// Note:  sem is a reference to the actual source code when on the stack.
		// Note:  sem->line_cursor points to the command that's currently executing

		// Knowns identified during compilation
		SVariable*		params;											// The first parameter in the function
		SVariable*		locals;											// The first local variable declared
		SVariable*		returns;										// The first return variable declared
		SVariable*		scoped;											// The first scoped/temporary variable needed by the function

		// Embedded functions within this function
		SFunction*		firstAdhoc;										// First ADHOC function contained within this function
	};

	struct SCompileStats
	{
		// Counters
		u32				sourceLineCount;								// Raw source lines, blank, comment, or otherwise
		u32				blankLineCount;									// Only blank lines, or lines that only have whitespaces
		u32				commentLineCount;								// Lines with comments
		u32				functionCount;									// Hard function or procedure definitions
		u32				methodCount;									// Methods in class code (in any form, ?CX or source code)
		u32				paramsCount;									// Number of declared parameters
		u32				localsCount;									// Number of declared local variables
		u32				scopedCount;									// Number of scoped variables in use
		u32				returnsCount;									// Number of return variables
		u32				adhocsCount;									// Number of adhoc functions
		u32				flowofsCount;									// Number of flowof functions
		u32				errorCount;										// Number of errors
		u32				warningCount;									// Number of warnings

		// Pointers
		SFunction*		firstFunction;									// First stand-alone function
		SFunction*		firstAdhoc;										// First stand-alone adhoc
		SFunction*		firstFlowof;									// First flowof function
	};

	// Used during the the compile_Vxb() functions (so one parameter is passed rather than multiple)
	struct SCompileVxbContext
	{
		// These are parameters passed at various places in compile_vxb()
		SEM*			codeBlock;										// The code block being compiled
		SCompileStats*	stats;											// Statistics about the compilee
		SCompileStats	statsLocal;										// A dummy stats block we use if the compile requester did not send their own stats in
		bool			processThisLine;								// Should this line be processed?

		// Parameters used while processing, calling sub-functions, etc.
		SLine*			line;											// Current line
		SComp*			comp;											// Current component on the current line

		SFunction*		func;											// First function in the codeBlock
		SFunction*		currentFunction;								// Current unction in the codeBlock

		SFunction*		adhoc;											// First adhoc in the codeBlock
		SFunction*		currentAdhoc;									// Current adhoc in the current function

		SFunction*		flowof;											// First flowof in the codeBlock
		SFunction*		currentFlowof;									// Current flowof in the codeBlock
	};

	struct SOp
	{
		u32				opType;											// The type of operand, see _OP_TYPE_* constants

		// Pointer to item, or first item if they are in succession (such as pointing to the left-parenthesis of a complex expression)
		bool			isOpDataAllocated;								// Is the op below allocated?  If false, then it points to one allocated elsewhere
		union {
			uptr		_opData;										// Used as a general test to see if something exists (if (op_data != 0))

			// Actual data items based on op_type
			SComp*		comp;											// The first component
			SVariable*	variable;										// Generic access to (param, local, scoped, other)
			SVariable*	param;											// A parameter variable or reference
			SVariable*	local;											// A local variable or reference
			SVariable*	scoped;											// A scoped/temporary variable or reference used for inter-source-code-line processing
			SVariable*	returns;										// A returns variable or reference
			SVariable*	other;											// Unknown item which must be looked up in the context of the runtime environment
			SObject*	obj;											// An object reference
			SFunction*	func;											// A function reference
			SFunction*	adhoc;											// An adhoc reference
			SFunction*	flowof;											// A flowof reference
		};

		// Number of components found (such as between parenthesis)
		s32				count;											// The number of components (in comp or other) as input
	};

/*
//////////
//
// Sub-instructions are components of a source code line broken out into individual tasks.
//
// They conduct those individual operations only, being part of the larger computation
// taking place across multiple sub-instructions.
//
// This structure is used for two operations in VJr.  One is for parsing source code into
// sub-instructions, the second is for generating actual sub-instruction lists for faster
// throughput by the processing engine while still retaining LiveCode abilities.
//
//                      ______
//                     |parent|
//                     |______|
//                        ^
//                        |
//                     ___|___
//       _____        | Sub-  |        _____
//      | prev|<------| Instr |------>|next |
//      |_____|       |_______|       |_____|
//                    /       \
//                   /         \
//               ___/_         _\___
//              |left |       |right|
//              |_____|       |_____|
//
//////
*/
	// Processing ops
	struct SSubInstr
	{
		// Operation layer/level and instruction at that level
		s32				subLevel;										// The sub-instruction operation level related to the bigger picture
		s32				subInstr;										// See _SUB_INSTR_* constants, the sub-instruction being executed, such as "+" in "2 + 4"
		SOp				op;												// Any operand data for this node (if it is a terminating node)

		// Note that in some cases there can be multiple return variables.
		// When this happens, the left-most result is always the firstVariable, with each return result being then at x->next until the end
		SVariable*		firstVariable;									// As results are computed or referenced, they are stored in scoped/temporary variables
		u32				variable_count;									// The number of variables
	};

	// General nodes
	struct SNode
	{
		u32				uid;											// Unique ID for this sub-instruction

		// Directions from the central node
		union {
			SNode*		parent;											// Up to the higher node
			SNode*		north;
		};
		union {
			SNode*		prev;											// Previous item in the horizontal chain
			SNode*		west;
		};
		union {
			SNode*		next;											// Next item in the horizontal chain
			SNode*		east;
		};
		union {
			SNode*		left;											// Left node
			SNode*		extra;											// Pointer to an extra direction for this node
		};
		union {
			SNode*		right;											// Right node
			SNode*		south;
		};

		// Node data
		union {
			void*		extraData;										// General purpose data
			SSubInstr*	opData;											// When used as for processing ops
		};
	};

	struct SCompCallback
	{
		union {
			SComp*		comp;											// Component at start, and the component to continue processing after upon exit
			s8*			text;											// Raw text (depending on when it is being processed
		};
		u32				length;											// If raw text, the length of the thing being searched, otherwise 0.
		u32				iCode;											// The iCode being queried

		// Callback callbacks for adjustment
		union {
			uptr		_insertCompByComp;
			void		(*insertCompByComp)		(SComp* compRef, SComp* compNew, bool tlInsertAfter);
		};
		union {
			uptr		_insertCompByParams;
			void		(*insertCompByParams)	(SComp* compRef, SLine* line, u32 tniCode, u32 tnStart, s32 tnLength, bool tlInsertAfter);
		};
		union {
			uptr		_deleteComps;
			void		(*deleteComps)			(SComp* comp, SLine* line);
		};
		union {
			uptr		_cloneComps;
			SComp*		(*cloneComps)			(SComp* comp, SLine* line);
		};
		union {
			uptr		_mergeComps;
			SComp*		(*mergeComps)			(SComp* comp, SLine* line, u32 tnCount, u32 tniCodeNew);
		};
	};

	struct SStartEndCallback
	{
		union
		{
			uptr	_func;
			bool	(*funcBool)	(SStartEndCallback* cb);	// This callback should return false to continue searching, or true when the item is found
			void	(*funcVoid)	(SStartEndCallback* cb);
			//////
			// Uses the following format for the callback:
			//		bool func(SStartEndCallback* cb)
			//////////
		};

		// Data items for this callback
		// Primary pointer
		void*		ptr;

		union {
			// Extra1
			uptr		ex1;
			uptr		extra1;
			uptr		extra;
			uptr		count1;
			union {
				uptr	count1_1;
				uptr	count1_2;
			};
			void*		ex1Ptr;
		};

		union {
			// Extra2
			uptr		ex2;
			uptr		extra2;
			uptr		count2;
			union {
				uptr	count2_1;
				uptr	count2_2;
			};
			void*		ex2Ptr;
		};
	};

	// Holds compiler data
	struct SCompiler
	{
		// EC was designed with source code in mind, and that means a tight compiler relationship
		SLine*			parent;											// SEMLine this compiler data belongs to (parent->compilerInfo points back to here)

		// The last source code line
		SDatum*			sourceCode;										// Copy at last compile of LEFT(parent->sourceCode.data, parent->sourceCodePopulated)
		// Note:  If the source code line ended in a semicolon, the following sourceCode line(s) will be appended here on top of the semicolon until there are no more semicolon lines

		// Extra information
		SExtraInfo*		firstExtraInfo;									// Specific to the application, contains triggers on errors, warnings, notes, etc.

		// Components compiled in prior compiler passes
		SComp*			firstComp;										// Pointer to the first component identified on this line
		SComp*			firstWhitespace;								// Whitespaces are removed for ease of compilation, but they persist here for rendering and reference
		SComp*			firstComment;									// Comments are migrated over


	//////////
	// During compilation, three steps:
	//		(1) parse		-- Parse out the components into sequenced steps
	//		(2) optimize	-- Optimize away redundancy, combine literals, possibly reorder
	//		(3) generate	-- Write the sequenced engagement code for the target
	//////
		// (1) parse
		SNode*			firstNodeParsed;								// Component sequencing prior to optimization
		u32				nodeParsedCount;								// How many nodes after parsing

		// (2) optimize
		SNode*			firstNodeOptimized;								// Component sequencing after optimization
		u32				nodeOptimizedCount;								// How many nodes after optimization

		// (3) generate
		SNode*			firstNodeEngaged;								// Final generation of engagement code steps
		u32				nodeArrayCount;									// How many nodes in engagement code
	//////
	// Note:  The firstNodeEngaged code generated here will be added to the function's complete
	//        engagement code, sequenced with meta data for flow control and error reporting.
	//////////


	//////////
	// Results of compilation
	//////
		SNoteLog*	firstError;										// Noted error(s) on this source code line
		SNoteLog*	firstWarning;									// Noted warning(s) on this source code line
		SNoteLog*	firstNote;										// Noted note(s) on this source code line
	};
