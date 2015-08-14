//////////
//
// /libsf/li386/logician/source/logician/log_structs.h
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
// Version 0.01
// Copyright (c) 2014 by Rick C. Hodgin
//////
// Last update:
//     Aug.14.2015
//////
// Change log:
//     Aug.14.2015 - Initial creation
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




struct SLObj;
struct SLNode;
struct SLNodes;

struct SLVia;
struct SLGroup;
struct SLReal;
struct SLTalkin;
struct SLTalkout;
struct SLTalkback;
struct SLTrigger;
struct SLSignal;
struct SLData;
struct SLRegs;
struct SLLogic;
struct SLClock;
struct SLHistory;
struct SLDelta;
struct SLVent;
struct SLClone;
struct SLSticky;
struct SLDebug;
struct SLAway;
struct SLInvert;
struct SLAny1;
struct SLAll1;
struct SLDiff1;
struct SLAny0;
struct SLAll0;
struct SLDiff0;

struct SLObj
{
	SLObj*		next;							// Next object in the link list (if any)
	SLGroup*	parent;							// The group this object belongs to
	SLNodes*	nodes;							// Nodes related to this object
	s32			level;							// For vias, allows things to logically (or physically) to go up/down, in addition to groupings

	SDatum		name;							// Logician object name
	SBgra		color;							// Color to use for this node
	f32			scale;							// 1.0 = normal scale, can be larger or smaller for emphasis or de-emphasis
	f32			rotation;						// pi/4 = normal rotation, relative to standard x,y coordinate system (with 0 being east)
	SEM*		code;							// Any code associated with this object

	SDllFunc	reset;							// DLL function to call for reset
	SDllFunc	cycle;							// DLL function to call for cycle

	s32			type;							// Refers to _LOGOBJ_* constants
	union {
		SLVia*		via;						// Logician object is a via
		SLGroup*	group;						// Logician object is a group
		SLReal*		real;						// Logician object is a real
		SLTalkin*	talkin;						// Logician object is a talkin
		SLTalkout*	talkout;					// Logician object is a talkout
		SLTalkback*	talkback;					// Logician object is a talkback
		SLTrigger*	trigger;					// Logician object is a trigger
		SLSignal*	signal;						// Logician object is a signal
		SLData*		data;						// Logician object is a data
		SLRegs*		regs;						// Logician object is a regs
		SLLogic*	logic;						// Logician object is a logic
		SLClock*	clock;						// Logician object is a clock
		SLHistory*	history;					// Logician object is a history
		SLDelta*	delta;						// Logician object is a delta
		SLVent*		vent;						// Logician object is a vent
		SLClone*	clone;						// Logician object is a clone
		SLSticky*	sticky;						// Logician object is a sticky
		SLDebug*	debug;						// Logician object is a debug
		SLAway*		away;						// Logician object is a away
		SLInvert*	invert;						// Logician object is a invert
		SLAny1*		any1;						// Logician object is a any1
		SLAll1*		all1;						// Logician object is a all1
		SLDiff1*	diff1;						// Logician object is a diff1
		SLAny0*		any0;						// Logician object is a any0
		SLAll0*		all0;						// Logician object is a all0
		SLDiff0*	diff0;						// Logician object is a diff0
	};
};

struct SLNode
{
	SLNodes*	parent;							// Parent nodes grouping
	SLNode*		connectsTo;						// The node this node is connected to

	s32			direction;						// Refer to _NODEDIR_* constants
	s32			bitlines;						// How many bit lines are associated with this node?
	s8*			bytes;							// Allow up to N bitlines to be defined

	SBgra		noodle;							// Color of the noodle on this end
	f32			scale;							// 1.0 = normal scale, can be larger or smaller for emphasis or de-emphasis
	SBgra		color;							// Color to render
	f32			width;							// 1.0 = normal width, typically it grows with the number of bitlines
};

struct SLNodes
{
	SLObj*		parent;							// The object this bundle relates to

	SLNode*		first_north;					// First node which emanates from the north of the Logician object
	SLNode*		first_east;						// First node which emanates from the east of the Logician object
	SLNode*		first_south;					// First node which emanates from the south of the Logician object
	SLNode*		first_west;						// First node which emanates from the west of the Logician object
};

struct SLReg
{
	SLReg*		next;							// Next register in the chain
	SDatum		name;							// Name of this register

	s32			width;							// Width of the register
	s8*			bytes;							// Allow up to N bits to be defined
};

struct SLVia
{
	// These nodes are mated pairs in the linklist
	// The first_up and first_down are the same
	SLNode*		first_up;
	SLNode*		first_down;
};

struct SLGroup
{
	SLObj*		first_obj;						// First object in the group
};

struct SLReal
{
	SLNode*		i;								// (I)   -- Inputs
	SLNode*		o;								// (O)   -- Outputs
	SLNode*		io;								// (I/O) -- Input/outputs
};

struct SLTalkin
{
	SLNode*		lr;								// (O) -- Pull is ready (we are ready to receive)
	SLNode*		rdy;							// (I) -- Remote is ready to push (ready to send us data)
	SLNode*		l;								// (O) -- Pull (we are receiving)

	SLNode*		dl;								// (I) -- Data from pull
};

struct SLTalkout
{
	SLNode*		rdy;							// (I) -- Push is ready (we are ready to send)
	SLNode*		sr;								// (O) -- Remote is ready to pull (ready to receive data from us)
	SLNode*		s;								// (O) -- Push (we are pushing)

	SLNode*		ds;								// (O) -- Data to push
};

struct SLTalkback
{
	SLNode*		lrdy;							// (I) -- Remote is ready to push (ready to send us data)
	SLNode*		l;								// (O) -- Pull (we are receiving)
	SLNode*		srdy;							// (I) -- Remote is ready to pull (ready to receive data from us)
	SLNode*		s;								// (O) -- Push (we are pushing)

	SLNode*		dl;								// (I) -- Data from pull
	SLNode*		ds;								// (O) -- Data to push
};

struct SLTrigger
{
	SLNode*		trg;							// (I) -- Trigger

	SLNode*		vent;							// A debug vent (if any)
};

struct SLSignal
{
	s32			type;							// Refer to _SIGNAL_* constants
	SLNode*		sig;							// (I,O) -- The signal

	SLNode*		vent;							// A debug vent (if any)
};

struct SLData
{
	s32			type;							// Refer to _DATA_* constants
	SLNode*		d;								// (I,O) -- The data bits

	SLNode*		vent;							// A debug vent (if any)
};

struct SLRegs
{
	s32			count;							// Number of registers to maintain
	SLReg*		first_reg;						// First register

	SLNode*		vent;							// A debug vent (if any)
};

struct SLLogic
{
	SLNode*		vent;							// A debug vent (if any)
};

struct SLClock
{
	SLNode*		up;								// (O) UP signal on the clock
	SLNode*		hi;								// (O) HI signal on the clock
	SLNode*		dn;								// (O) DN signal on the clock
	SLNode*		lo;								// (O) LO signal on the clock
};

struct SLHistory
{
	SLNode*		din;							// (I) Data to record
	SLNode*		rec;							// (I) Record signal
	SLNode*		dout;							// (O) Pass-thru

	SLNode*		hsg;							// (O) History has been recorded
	SLNode*		ack;							// (I) HSG has been acknowledged

	s32			count;							// Number of registers
	SLReg*		first_h;						// First history register

	SLNode*		vent;							// A debug vent (if any)
};

struct SLDelta
{
	SLNode*		din;							// (I) Data to sample
	SLNode*		samp;							// (I) Sample signal
	SLNode*		dout;							// (O) Pass-thru

	SLNode*		dsg;							// (O) Delta has been recorded
	SLNode*		ack;							// (I) HSG has been acknowledged

	s32			count;							// Number of registers
	SLReg*		first_d;						// First delta register

	SLNode*		vent;							// A debug vent (if any)
};

struct SLVent
{
	SLNode*		halt;							// (I) Signal to halt processing
	SLNode*		step;							// (I) Signal to single-step
	SLNode*		dump;							// (I) Signal to dump all data
	SLNode*		dend;							// (O) When all vented registers have been dumped

	s32			count;							// Number of registers
	SLReg*		first_h;						// First history register

	SLNode*		talkback;						// A talkback (if any)
};

struct SLClone
{
	SLNode*		i;								// (I) Input signal
	SLNode*		o;								// (O) Output clones
};

struct SLSticky
{
	SLNode*		i;								// (I) Input signal
	SLNode*		rst;							// (I) Reset signal
	SLNode*		o;								// (O) Output signal
};

struct SLDebug
{
	s32			count;							// Number of registers
	SLReg*		first_d;						// First debug register

	SLNode*		vent;
};

struct SLAway
{
	bool		isCopy;							// If it's a copy, it has its own properties, otherwise it simply is a reference to the other item
	SLObj*		away;							// The Logician object this thing relates back to
};

struct SLInvert
{
	SLNode*		i;
	SLNode*		o;
};

struct SLAny1
{
	SLNode*		i1;
	SLNode*		i2;
	SLNode*		o;
};

struct SLAll1
{
	SLNode*		i1;
	SLNode*		i2;
	SLNode*		o;
};

struct SLDiff1
{
	SLNode*		i1;
	SLNode*		i2;
	SLNode*		o;
};

struct SLAny0
{
	SLNode*		i1;
	SLNode*		i2;
	SLNode*		o;
};

struct SLAll0
{
	SLNode*		i1;
	SLNode*		i2;
	SLNode*		o;
};

struct SLDiff0
{
	SLNode*		i1;
	SLNode*		i2;
	SLNode*		o;
};
