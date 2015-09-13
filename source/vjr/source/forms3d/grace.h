//////////
//
// /libsf/source/vjr/source/forms3d/grace.h
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
//     Nov.05.2014
//////
// Change log:
//     Nov.05.2014 - Initial creation
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




#if defined(_MSC_VER)
	#include "include\GL\glew.h"
	#include "include\GL\freeglut.h"
#elif defined(__GNUC__)
	#if defined(__linux__)
		#include "GL/glew.h"
		#include "GL/freeglut.h"
	#else
		#include "include/GL/glew.h"
		#include "include/GL/freeglut.h"
	#endif
#elif defined(__solaris__)
    #warning OpenGL is not supported on Solaris
#else
	#error Unknown target for compilation (must be Windows or Linux)
#endif


//////////
// Forward structure definitions
//////
	struct SObjNode;
	struct SGraceVec;
	struct SGraceRect;
	struct SGraceVecLine;
	struct SGraceXy;
	struct SGraceLine;


//////////
// Missing from freeglut.h for some reason
//////
	#define GL_BGR			0x80E0
	#define GL_BGRA			0x80E1
	#define GLUT_WHEEL_UP	3
	#define GLUT_WHEEL_DOWN	4


//////////
// Constants to access data in vectors
//////
	#define XVEC	0
	#define YVEC	1
	#define ZVEC	2

	#define V1		0
	#define V2		1
	#define V3		2
	#define V4		3


//////////
// These constants may or may not already be defined
//////
	#ifndef _PI2
		#define _PI2 1.570796327
	#endif

	#ifndef _GRACE_OGL
		#define _GRACE_OGL
	#endif


//////////
// Forward declarations
//////
	DWORD WINAPI	iGrace									(LPVOID p);
	void			iGrace_initGl_engine					(void);
	void			iGrace_projectMousePositionToScreen		(int x, int y, f64* tfX, f64* tfY, f64* tfZ);;
	void			iGrace_assignCoordinates				(SObject* obj, RECT* rc, f32 tfZ);

	// Default functions
	void			iGrace_mouse							(s32 button, s32 state, s32 x, s32 y);
	void			iGrace_motion							(s32 x, s32 y);
	void			iGrace_passiveMotion					(s32 x, s32 y);
	void			iGrace_Key								(unsigned char key, s32 x, s32 y);
	void			iGrace_special							(s32 key, s32 x, s32 y);
#if defined(__solaris__)
	void			iGrace_reshape							(s32 w, s32 h);
#else
	void			iGrace_reshape							(GLsizei w, GLsizei h);
#endif
	void			iGrace_display							(void);
	void			iGrace_idle								(void);

	// Render functions
	void			iGrace_renderBegin						(f32 tfZ);
	void			iGrace_renderEnd						(void);

	void			iGrace_animate_childrenAndSiblings		(SObject* obj, RECT* rc, bool tlRenderChildren, bool tlRenderSiblings, f32 tfZ, s64 tnMs);
	void			iiGrace_animate							(SObject* obj, s64 tnMs);

	void			iGrace_renderNode_childrenAndSiblings	(SObject* obj, bool tlRenderChildren, bool tlRenderSiblings, f32 tfZ);
	SGraceRect*		iiGrace_computeNodeLine					(SGraceVec* tsV1, SGraceVec* tsV2, f32 tfNodeWidth, bool tlIsP1East, bool tlIsP2West, s32* tnReturnVecCount);
	void			iiGrace_positionNodeVectors				(SObjNode* objNode, SGraceVec* vFrom, SGraceVec* vTo);
	void			iiGrace_computeNodeLine_fivePoints		(SGraceVec* tsV1, SGraceVec* tsV2, SGraceVec* v1, SGraceVec* v2, SGraceVec* v3, SGraceVec* v4, SGraceVec* v5, bool tlIsP1East, bool tlIsP2West);
	void			iiGrace_renderNode						(SObjNode* objNode, f32 tfNodeWidth);

	void			iGrace_renderObj_childrenAndSiblings	(SObject* obj, bool tlRenderChildren, bool tlRenderSiblings, f32 tfZ);
	void			iiGrace_renderObj						(SObject* obj);
	void			iiGrace_renderSubdividedRect			(SGraceRect* rec, s32 tnXDivisions, s32 tnYDivisions, bool tlIssue_quadBeginAndEnd);
	void			iiGrace_vec_add							(SGraceRect* rec, s32 recV, SGraceRect* step, s32 stepV);
	void			iiGrace_vec_copy						(SGraceRect* recDst, s32 recDstV, SGraceRect* recSrc, s32 recSrcV);
	void			iiGrace_vec_render						(SGraceRect* rec, s32 rV);
	void			iiGrace_computeSteps					(SGraceRect* dst, s32 dstV, SGraceRect* rBeg, s32 rBegV, SGraceRect* rEnd, s32 rEndV, SGraceRect* step, s32 stepV, f32 tfDivisions);
	f32				iiGrace_computeStep						(f32 tfBegin, f32 tfEnd, f32 tfCount, f32* tfStep);


	// Helper functions
	void			iiGrace_copyAndComputeVecLine			(SGraceVecLine* line, SGraceVec* p1, SGraceVec* p2);
	void			iiGrace_copyAndComputeLine				(SGraceLine* line, SGraceXy* p1, SGraceXy* p2);
	SGraceVec*		iiGrace_computeVecBezier3				(s32 tnSegmentCount, SGraceVec* tsV1, SGraceVec* tsV2, SGraceVec* tsV3);


//////////
// Structures
//////
	struct SGraceXy
	{
		f32		x;
		f32		y;
	};

	struct SGraceLine
	{
		SGraceXy	p1;							// Point 1
		SGraceXy	p2;							// Point 2

		SGraceXy	delta;						// Delta between start and end
		SGraceXy	mid;						// Midpoint

		f32			length;						// Length
		f32			m;							// Slope
		f32			mp;							// Perpendicular slope
		f32			theta;						// Theta
	};

	struct SGraceVec
	{
		f32		x;
		f32		y;
		f32		z;
	};

	struct SGraceUv
	{
		f32		s;
		f32		t;
	};

	struct SGraceColor
	{
		f32		r;		// Red
		f32		g;		// Grn
		f32		b;		// Blu
		f32		a;		// Alpha
	};


//////////
//
//		V1__________________V2
//		 |                  |
//		 |    GraceRect     |
//		 |__________________|
//		V4                  V3
//
// When drawn, these can be drawn sub-divided into many components horizontally or vertically.
//
//////
	struct SGraceRect
	{
		// Image data
		u32				texture;
		bool			updateTextureWithNewBitmap;		// If the associated texture bitmap content needs updated

		// One for each corner
		SGraceVec		v[4];		// Vector coordinates
		SGraceVec		n[4];		// Normals
		SGraceUv		t[4];		// Texture coordinates
		SGraceColor		c[4];		// Colors
	};

	struct SGraceAnim
	{
		s32				msInterval;		// Number of milliseconds between frames
		s64				msNext;			// Milliseconds where next sequence happens

		SGraceRect		delta;
		SGraceRect		start;
		SGraceRect		end;
	};

	struct SGraceOgl
	{
		SGraceRect		quad;
		SGraceAnim		anim;
	};

	// This structure computes the line only on the x,y values
	struct SGraceVecLine
	{
		SGraceVec	v1;							// Vector 1
		SGraceVec	v2;							// Vector 2

		SGraceVec	delta;						// Delta between start and end
		SGraceVec	mid;						// Midpoint

		f32			length;						// Length in 3D
		f32			lengthXy;					// Length of X,Y line
		f32			lengthXz;					// Length of X,Z line
		f32			lengthYz;					// Length of Y,Z line

		f32			mXy;						// Slope of X,Y line
		f32			mXz;						// Slope of X,Z line
		f32			mYz;						// Slope of Y,Z line

		f32			mpXy;						// Perpendicular slope of X,Y line
		f32			mpXz;						// Perpendicular slope of X,Z line
		f32			mpYz;						// Perpendicular slope of Y,Z line

		f32			thetaXy;					// Theta (from p1 to p2 on X,Y line, note: add _PI to reverse the angle from p2 to p1)
		f32			thetaXz;					// Theta (from p1 to p2 on X,Z line, note: add _PI to reverse the angle from p2 to p1)
		f32			thetaYz;					// Theta (from p1 to p2 on Y,Z line, note: add _PI to reverse the angle from p2 to p1)
	};

	struct SGraceParams
	{
		// The window to display for the 3D render
		SWindow*	win;

		// Function prototypes
		union {
			uptr	_func_mouse;
			void	(*func_mouse)			(s32 button, s32 state, s32 x, s32 y);
		};
		union {
			uptr	_func_motion;
			void	(*func_motion)			(s32 x, s32 y);
		};
		union {
			uptr	_func_passiveMotion;
			void	(*func_passiveMotion)	(s32 x, s32 y);
		};
		union {
			uptr	_func_key;
			void	(*func_Key)				(unsigned char key, s32 x, s32 y);
		};
		union {
			uptr	_func_special;
			void	(*func_special)			(s32 key, s32 x, s32 y);
		};
		union {
			uptr	_func_reshape;
#ifdef __solaris__
			void	(*func_reshape)			(s32 w, s32 h);
#else
			void	(*func_reshape)			(GLsizei w, GLsizei h);
#endif
        };
		union {
			uptr	_func_display;
			void	(*func_display)			(void);
		};
		union {
			uptr	_func_idle;
			void	(*func_idle)			(void);
		};
	};




//////////
// Variables used by Grace
//////
	// Used for accessing the 3D render objects
	bool				glGraceInitialized		= false;
	CRITICAL_SECTION	gcs_3dObjectAccess;
	SGraceParams*		gsGraceParams			= NULL;

	s32			gnMouseX						= 400;
	s32			gnMouseY						= 400;
	bool		glMouse_leftButtonDown			= false;
	bool		glMouse_middleButtonDown		= false;
	bool		glMouse_rightButtonDown			= false;

	f32			gfLightViewX					= 0.0;
	f32			gfLightViewY					= 0.0;
	f32			gfLightViewZ					= 0.0;
	bool		glLighting						= false;
#ifdef __solaris__
	float		gfv4LightFixture[]				= {  0.0, 0.0, 50.0, 1.0 };
#else
	GLfloat		gfv4LightFixture[]				= {  0.0, 0.0, 50.0, 1.0 };
#endif

	// Used for event tracking on when to redraw a glut loop
	s64			gnGraceEventCount				= -1;
	s64			gnFpsMilliseconds				= 1000 / 33;		// 33 fps

	// Camera position and origin
	f32			gfX								= 0.0f;
	f32			gfY								= 0.0f;
	f32			gfZ								= 15.0f;
	f32			gfZBase							= 15.0f;
	f32			gfZBase_over_2					= 7.50;

	// Used during load, indicating
	s32			gnWindowWidth					= 800;
	s32			gnWindowHeight					= 800;
	f32			gfPerspective					= 1.0f;
