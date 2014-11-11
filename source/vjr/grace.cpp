//////////
//
// /libsf/source/vjr/grace.cpp
//
//////
// Version 0.54
// Copyright (c) 2014 by Rick C. Hodgin
//////
// Last update:
//     Nov.05.2014
//////
// Change log:
//     Nov.05.2014 - Initial creation
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
//




//////////
// Added to create and debug a basic 3D rendering screen
//////
	DWORD WINAPI iGrace(LPVOID param)
	{
		RECT		lrc;
		s64			lnLastUpdateCount;
		s32			argc;
		s8*			argv[1];
		s64			lnLastMilliseconds, lnNowMilliseconds;
		SYSTEMTIME	timeNow;


		// Create fake startups for glut
		argc = 1;
		argv[0] = (s8*)&"vjr.exe";

		GetWindowRect(GetDesktopWindow(), &lrc);
		gnWidth		= (lrc.right - lrc.left) * 3 / 4;
		gnHeight	= (lrc.bottom - lrc.top) * 3 / 4;
		glutInitWindowSize(gnWidth, gnHeight);
		glutInitWindowPosition(0, 0);
		glutInit(&argc, argv);
		glewInit();
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);
		glutCreateWindow("Grace");

		// Initialize
		iGrace_reshape(gnWidth, gnHeight);

		// Setup
		glutMouseFunc			(iGrace_mouse);
		glutMotionFunc			(iGrace_motion);
		glutPassiveMotionFunc	(iGrace_passiveMotion);
		glutKeyboardFunc		(iGrace_Key);
		glutSpecialFunc			(iGrace_special);
		glutReshapeFunc			(iGrace_reshape);
		glutDisplayFunc			(iGrace_display);
		glutIdleFunc			(iGrace_idle);

		// See if we can load the file they've specified
		Sleep(100);


		//////////
		// Main loop
		//////
			GetSystemTime(&timeNow);
			lnLastMilliseconds	= iTime_computeMilliseconds(&timeNow);
			lnLastUpdateCount	= 0;
			while (!glShuttingDown)
			{
				// If it's time, execute a loop
				if (gnGraceEventCount != lnLastUpdateCount)
				{
					lnLastUpdateCount = gnGraceEventCount;
					glutMainLoopEvent();

				} else {
					// Fire at our fps
					GetSystemTime(&timeNow);
					lnNowMilliseconds	= iTime_computeMilliseconds(&timeNow);
					if (lnNowMilliseconds - lnLastMilliseconds > gnFpsMilliseconds)
					{
						lnLastMilliseconds = lnNowMilliseconds;
						++gnGraceEventCount;
					}
				}

				// Sleep for 1 ms
				Sleep(1);
			}

		// Control will never return here
		return(0);
	}




	void iGrace_initGl_engine(void)
	{
		glMatrixMode	(GL_SMOOTH);

//////////
// We do not presently compute normals, so lighting is disabledd
// 		if (glLighting)
// 		{
// 			glEnable	(GL_LIGHTING);
// 			glEnable	(GL_LIGHT0);
// 			glMatrixMode(GL_LIGHT_MODEL_AMBIENT);
// 
// 		} else {
			glDisable	(GL_LIGHTING);
// 		}
//////////

		glEnable		(GL_DEPTH_TEST);
		glEnable		(GL_COLOR);
		glEnable		(GL_COLOR_MATERIAL);
		glEnable		(GL_ALPHA_TEST);
		glAlphaFunc		(GL_GREATER, 0.016f);
		glEnable		(GL_BLEND);
		glBlendFunc		(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable		(GL_TEXTURE_2D);
		glTexEnvf		(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_SPHERE_MAP/*GL_DECAL*//*GL_MODULATE*/);
		glTexParameterf	(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		glTexParameterf	(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf	(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf	(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		// White
		glClearColor(1.0, 1.0, 1.0, 1.0);
	}




	void iGrace_reshape(GLsizei w, GLsizei h)
	{
		gnWidth			= w;
		gnHeight		= h;
		//gfPerspective	= (GLfloat)w / (GLfloat)h;
		// Decided to use a fixed perspective for this app.  May change this later.
		gfPerspective = 1.0f;
		glViewport		(0, 0, w, h);
		glMatrixMode	(GL_PROJECTION);
		glLoadIdentity	();
		gluPerspective	(45.0, gfPerspective, 1.0, 10000.0);
		iGrace_initGl_engine();
	}




	// Mouse motion with buttons down in the window
	void iGrace_motion(s32 tnMouseX, s32 tnMouseY)
	{
		f64		lfX_new, lfY_new, lfZ_new, lfX_old, lfY_old, lfZ_old;
		bool	llRedisplay;


		//////////
		// Initialize
		//////
			llRedisplay	= false;


		//////////
		// Based on the current view, pixels on-screen correlate to different visible deltas
		//////
			iGrace_projectMousePositionToScreen(gnMouseX, gnMouseY, &lfX_new, &lfY_new, &lfZ_new);
			iGrace_projectMousePositionToScreen(tnMouseX, tnMouseY, &lfX_old, &lfY_old, &lfZ_old);


		/////////
		// Left button
		//////
			if (glMouse_leftButtonDown && !glMouse_rightButtonDown)
			{
				// Left-mouse only
				llRedisplay = true;
				gfX += (f32)(lfX_new - lfX_old);
				gfY += (f32)(lfY_new - lfY_old);


		//////////
		// Right button
		//////
			} else if (!glMouse_leftButtonDown && glMouse_rightButtonDown) {
				// Right-mouse only


		//////////
		// Both buttons
		//////
			} else {
				// Both-buttons down
			}


		//////////
		// Store the new mouse position
		//////
			gnMouseX = tnMouseX;
			gnMouseY = tnMouseY;


		//////////
		// Redraw if need be
		//////
			if (llRedisplay)
			{
				++gnGraceEventCount;
				glutPostRedisplay();
			}
	}




	// Called to project window mouse coordinates into the GL buffer and obtain the object at those coordinates
	// Note:  To prevent it from returning something invalid, I always use a background behind everything.
	void iGrace_projectMousePositionToScreen(int x, int y, f64* tfX, f64* tfY, f64* tfZ)
	{
		//////////
		// Code refactored from source, but generally used as is:
		// Adpated from a post on this thread:
		//		https://www.opengl.org/discussion_boards/showthread.php/138411-Mouse-Coordinates
		// START
		//////
			f32		winX, winY, winZ;
			s32		viewport[4];
			f64		modelview[16];
			f64		projection[16];

			glGetDoublev(GL_MODELVIEW_MATRIX,	modelview);
			glGetDoublev(GL_PROJECTION_MATRIX,	projection);
			glGetIntegerv(GL_VIEWPORT,			viewport);

			winX = (f32)x;
			winY = (f32)gnHeight - (f32)y; //(float)viewport[3] - (float)mouse.y;
			winZ = 0.0f;

			glReadPixels((int)winX, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
			if (winZ == 1.0)
			{
				// No ojbect at that location
				*tfX = 0.0f;
				*tfY = 0.0f;
				*tfZ = 0.0f;

			} else {
				// Obtain the translated form
				gluUnProject(winX, winY, winZ, modelview, projection, viewport, tfX, tfY, tfZ);
			}
		//////
		// END
		//////////
	}




	void iGrace_passiveMotion(s32 x, s32 y)
	{
		bool llRedisplay;


		llRedisplay = false;

		// Mouse motion without buttons down over the window
		// Note currently processed


		if (llRedisplay)
		{
			++gnGraceEventCount;
			glutPostRedisplay();
		}
	}




	void iGrace_mouse(s32 button, s32 state, s32 x, s32 y)
	{
		bool llRedisplay;


		llRedisplay = false;
		if (state == GLUT_DOWN)
		{
			gnMouseX = x;
			gnMouseY = y;
			switch (button)
			{
				case GLUT_LEFT_BUTTON:
					glMouse_leftButtonDown	= true;
					break;

				case GLUT_MIDDLE_BUTTON:
					glMouse_middleButtonDown = true;
					break;

				case GLUT_RIGHT_BUTTON:
					glMouse_rightButtonDown	= true;
					break;

				case GLUT_WHEEL_UP:		// Wheel up, moving in
					gfZ			-= (gfZ / gfZBase);		// Decelerates the closer in we get
					llRedisplay = true;
					break;

				case GLUT_WHEEL_DOWN:	// Wheel down, moving out
					gfZ			+= (gfZ / gfZBase);		// Accelerates the further out we get
					llRedisplay	= true;
					break;
			}
			gfZ = min(max(gfZ, 4.0f), 200.0f);

		} else {	
			glMouse_leftButtonDown		= false;
			glMouse_middleButtonDown	= false;
			glMouse_rightButtonDown		= false;
		}

		if (llRedisplay)
		{
			++gnGraceEventCount;
			glutPostRedisplay();
		}
	}




	void iGrace_Key(unsigned char key, s32 x, s32 y)
	{
		bool llRedisplay;


		llRedisplay = false;
		switch (key)
		{
			case 27:	// Escape
			case 'q':
			case 'Q':
///				exit(0);
				break;

			case 'z':
			case 'Z':
				gfZ			= gfZBase;
				llRedisplay	= true;
				break;
		}

		if (llRedisplay)
		{
			++gnGraceEventCount;
			glutPostRedisplay();
		}
	}




	void iGrace_special(s32 key, s32 x, s32 y)
	{
		bool llRedisplay;


		// Special keystroke processing
		llRedisplay = false;
		switch(key)
		{
			case  GLUT_KEY_F1:
			case  GLUT_KEY_F2:
			case  GLUT_KEY_F3:
			case  GLUT_KEY_F4:
			case  GLUT_KEY_F5:
			case  GLUT_KEY_F6:
			case  GLUT_KEY_F7:
			case  GLUT_KEY_F8:
			case  GLUT_KEY_F9:
			case  GLUT_KEY_F10:
			case  GLUT_KEY_F11:
			case  GLUT_KEY_F12:
			case  GLUT_KEY_LEFT:
			case  GLUT_KEY_UP:
			case  GLUT_KEY_RIGHT:
			case  GLUT_KEY_DOWN:
			case  GLUT_KEY_PAGE_UP:
			case  GLUT_KEY_PAGE_DOWN:
			case  GLUT_KEY_HOME:
			case  GLUT_KEY_END:
			case  GLUT_KEY_INSERT:
				break;
		}

		if (llRedisplay)
		{
			++gnGraceEventCount;
			glutPostRedisplay();
		}
	}




	void iGrace_idle(void)
	{
		// Not really used any longer because we no longer use glutMainLoop() but rather glutMainLoopEvent()
	}




	void iGrace_assignCoordinates(SObject* obj, RECT* rc, f32 tfZ)
	{
		s32		lnI, lnWidth, lnHeight;
		RECT	lrcDesktop;


		//////////
		// Get the desktop size
		//////
			GetWindowRect(GetDesktopWindow(), &lrcDesktop);
			lnWidth		= lrcDesktop.right - lrcDesktop.left;
			lnHeight	= lrcDesktop.bottom - lrcDesktop.top;


		//////////
		// Vectors
		//////
			// Upper-left
			obj->ogl.quad.v[V1].x	= (gfZBase_over_2) * ((f32)rc->left	/ lnWidth) * gfPerspective;
			obj->ogl.quad.v[V1].y	= (-gfZBase_over_2) * ((f32)rc->top		/ lnHeight);
			obj->ogl.quad.v[V1].z	= tfZ;

			obj->ogl.quad.v[V2].x	= (gfZBase_over_2) * ((f32)rc->right	/ lnWidth) * gfPerspective;
			obj->ogl.quad.v[V2].y	= obj->ogl.quad.v[V1].y;
			obj->ogl.quad.v[V2].z	= tfZ;

			obj->ogl.quad.v[V3].x	= obj->ogl.quad.v[V2].x;
			obj->ogl.quad.v[V3].y	= (-gfZBase_over_2) * ((f32)rc->bottom	/ lnHeight);
			obj->ogl.quad.v[V3].z	= tfZ;

			obj->ogl.quad.v[V4].x	= obj->ogl.quad.v[V1].x;
			obj->ogl.quad.v[V4].y	= obj->ogl.quad.v[V3].y;
			obj->ogl.quad.v[V4].z	= tfZ;


		//////////
		// Colors
		//////
			for (lnI = V1; lnI <= V4; lnI++)
			{
				obj->ogl.quad.c[lnI].r = 0.98f;	// Red
				obj->ogl.quad.c[lnI].g = 0.98f;	// Grn
				obj->ogl.quad.c[lnI].b = 0.98f;	// Blu
				obj->ogl.quad.c[lnI].a = 1.0f;	// Alp
			}


		//////////
		// Do texture coordinates (regardless of whether or not there is texture information
		//////
			// Upper-left
			obj->ogl.quad.t[V1].s	= 0.0f;
			obj->ogl.quad.t[V1].t	= 1.0f;

			// Upper-right
			obj->ogl.quad.t[V2].s	= 1.0f;
			obj->ogl.quad.t[V2].t	= 1.0f;

			// Lower-right
			obj->ogl.quad.t[V3].s	= 1.0f;
			obj->ogl.quad.t[V3].t	= 0.0f;

			// Lower-left
			obj->ogl.quad.t[V4].s	= 0.0f;
			obj->ogl.quad.t[V4].t	= 0.0f;


		//////////
		// Texture ops
		//////
			if (obj->bmp && obj->bmp->bd && obj->ogl.quad.mipmap == 0)
			{
				// Delete any previous texture
				glDeleteTextures(1, &obj->ogl.quad.mipmap);

				// Generate a new texture
				glGenTextures(1, &obj->ogl.quad.mipmap);

				// Mipmap the image
				glBindTexture(GL_TEXTURE_2D, obj->ogl.quad.mipmap);
				gluBuild2DMipmaps(GL_TEXTURE_2D, 3, obj->bmp->bi.biWidth, obj->bmp->bi.biHeight, ((obj->bmp->bi.biBitCount == 24) ? GL_BGR : GL_BGRA), GL_UNSIGNED_BYTE, obj->bmp->bd);
			}
	}




	void iGrace_display(void)
	{
		f32		lfZ;
		RECT	lrc;


		// Render if we have something to render
		if (gWinJDebi && gWinJDebi->obj)
		{
			//////////
			// We will be building centered around the origin
			//////
				SetRect(&lrc, -(gWinJDebi->rc.right - gWinJDebi->rc.left) / 2, -(gWinJDebi->rc.bottom - gWinJDebi->rc.top) / 2, 0, 0);
				SetRect(&lrc, lrc.left, lrc.top, lrc.left + (gWinJDebi->rc.right - gWinJDebi->rc.left), lrc.top + (gWinJDebi->rc.bottom - gWinJDebi->rc.top));


			//////////
			// Render
			//////
				// Start
				lfZ = 0.0f;
				iGrace_renderBegin(lfZ);

				// Apply animations
				iGrace_animate_childrenAndSiblings(gWinJDebi->obj, &lrc, true, true, lfZ);

				// Render the nodes
				iGrace_renderNode_childrenAndSiblings(gWinJDebi->obj, &lrc, true, true, lfZ);

				// Render Objects
				iGrace_renderObj_childrenAndSiblings(gWinJDebi->obj, &lrc, true, true, lfZ);

				// End
				iGrace_renderEnd();
		}
	}




	// Note:  glPushMatrix() here must match with corresponding glPopMatrix() in iGrace_renderEnd()
	void iGrace_renderBegin(f32 tfZ)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPushMatrix();


		//////////
		// Always looking straight forward at the x,y coordinate from the zoomed in z location
		//////
			gluLookAt(gfX, gfY, gfZ,
					  gfX, gfY, 0.0, 
					  0.0, 1.0, 0.0);

		//////////
		// Lighting
		//////
			if (glLighting)
			{
				// Indicate where the light is
				gfv4LightFixture[XVEC] = gfLightViewX;
				gfv4LightFixture[YVEC] = gfLightViewY;
				gfv4LightFixture[ZVEC] = (gfLightViewX + gfLightViewY) / (f32)2.0;
				glLightfv(GL_LIGHT0, GL_POSITION, gfv4LightFixture);

				glPushMatrix(); 
					glTranslatef	(gfv4LightFixture[XVEC], gfv4LightFixture[YVEC], gfv4LightFixture[ZVEC]);
					glDisable		(GL_LIGHTING);
					glColor3f		(1.0, 1.0, 0.0);
					glutWireCube	(1.0);
					glEnable		(GL_LIGHTING);
				glPopMatrix();
			}


		//////////
		// Render the white background
		//////
			glBegin(GL_QUADS);

				glColor4f	(1.0f, 1.0f, 1.0f, 1.0f);
				glVertex3f	(-500.0f, -500.0f, tfZ - 0.01f);
				glVertex3f	( 500.0f, -500.0f, tfZ - 0.01f);
				glVertex3f	( 500.0f,  500.0f, tfZ - 0.01f);
				glVertex3f	(-500.0f,  500.0f, tfZ - 0.01f);

			glEnd();
	}




	void iGrace_renderEnd(void)
	{
		//////////
		// Render finish
		//////
			glPopMatrix();
			glutSwapBuffers();
	}




	void iGrace_animate_childrenAndSiblings(SObject* obj, RECT* rc, bool tlRenderChildren, bool tlRenderSiblings, f32 tfZ)
	{
		RECT		lrc, lrcClient;
		SObject*	objSib;


		logfunc(__FUNCTION__);
		//////////
		// Make sure there is render data
		//////
			if (!obj || !isVisible(obj) || !isEnabled(obj))
				return;

		
		//////////
		// Adjust the coordinates for this item
		//////
			SetRect(&lrc,		rc->left	+ obj->rc.left,
								rc->top		+ obj->rc.top,
								rc->left	+ obj->rc.left			+ obj->bmp->bi.biWidth,
								rc->top		+ obj->rc.top			+ obj->bmp->bi.biHeight);

			SetRect(&lrcClient,	rc->left	+ obj->rcClient.left,
								rc->top		+ obj->rcClient.top,
								rc->left	+ obj->rcClient.left	+ obj->bmp->bi.biWidth,
								rc->top		+ obj->rcClient.top		+ obj->bmp->bi.biHeight);


		//////////
		// Render any children
		//////
			if (tlRenderChildren && obj->firstChild)
				iGrace_animate_childrenAndSiblings(obj->firstChild, &lrcClient, true, true, tfZ + 0.01f);


		//////////
		// Render self
		//////
			iGrace_assignCoordinates(obj, &lrc, tfZ);
			iiGrace_animate(obj);


		//////////
		// Render any siblings
		//////
			if (tlRenderSiblings && obj->ll.next)
			{
				objSib = (SObject*)obj->ll.next;
				while (objSib)
				{
					// Render this sibling
					iGrace_animate_childrenAndSiblings(objSib, rc, true, false, tfZ);

					// Move to next sibling
					objSib = (SObject*)objSib->ll.next;
				}
			}
	}




	void iiGrace_animate(SObject* obj, s64 tnMs)
	{
		s32 lnI;


		// If an animation is active, apply it
		if (obj->ogl.anim.msNext <= tnMs)
		{
			// It's time to animate the next frame
			obj->ogl.anim.msNext += obj->ogl.anim.msInterval;

			// Iterate applying any transformations
			for (lnI = V1; lnI <= V4; lnI++)
			{
				// Migrate this axis as it should be migrated
				obj->ogl.quad.v[lnI].x += obj->ogl.anim.delta.v[lnI].x;
				obj->ogl.quad.v[lnI].y += obj->ogl.anim.delta.v[lnI].y;
				obj->ogl.quad.v[lnI].z += obj->ogl.anim.delta.v[lnI].z;
			}
		}
	}




	void iGrace_renderNode_childrenAndSiblings(SObject* obj, RECT* rc, bool tlRenderChildren, bool tlRenderSiblings, f32 tfZ)
	{
		s32			lnNodeFromNum, lnNodeToNum;
		RECT		lrc, lrcClient;
		SObject*	objSib;
		SObjNode*	objNodeFrom;
		SObjNode*	objNodeTo;


		logfunc(__FUNCTION__);
		//////////
		// Make sure there is render data
		//////
			if (!obj || !isVisible(obj) || !isEnabled(obj))
				return;

		
		//////////
		// Render any children
		//////
			if (tlRenderChildren && obj->firstChild)
				iGrace_renderObj_childrenAndSiblings(obj->firstChild, &lrcClient, true, true, tfZ + 0.01f);


		//////////
		// Render nodes from the bottom of this item
		//////
			objNodeFrom		= obj->fromBottom;
			lnNodeFromNum	= 0;
			while (objNodeFrom)
			{
				//////////
				// Find out what item this points to along this node strip on the to side
				//////
					objNodeTo	= objNodeFrom->to;
					lnNodeToNum	= 0;
					while (objNodeTo->llTo.prev)
					{
						++lnNodeToNum;
						objNodeTo = (SObjNode*)objNodeTo->llTo.prev;
					}


				//////////
				// Render this node
				//////
					iiGrace_renderNode(obj, objNodeFrom, lnNodeFromNum, lnNodeToNum);


				//////////
				// Move to the next node
				//////
					++lnNodeFromNum;
					objNodeFrom = (SObjNode*)objNodeFrom->llFrom;
			}

			if (obj->fromBottom)
			{
				objNodeFrom = obj->fromBottom
			}

			if (obj->fromRight)
			{
			}


		//////////
		// Render any siblings
		//////
			if (tlRenderSiblings && obj->ll.next)
			{
				objSib = (SObject*)obj->ll.next;
				while (objSib)
				{
					// Render this sibling
					iGrace_renderNode_childrenAndSiblings(objSib, rc, true, false, tfZ);

					// Move to next sibling
					objSib = (SObject*)objSib->ll.next;
				}
			}
	}




	// Note:  This algorithm ignores Z for the bezier calculation, but rather uses a linear tsGv1->z to tsGv2->z for its orientation
	SGraceRect** iiGrace_computeNodeLine(SGraceVec* tsV1, SGraceVec* tsV2, bool tlIsP1East, bool tlIsP2West, s32* tnReturnVecCount)
	{
		s32				lnI, lnWidth;
		SGraceVec**		vecs1;
		SGraceVec**		vecs2;
		SGraceVec		v1, v2, v3, v4, v5;
		SGraceRect**	recs;
		f32				lfWidth, lfHeight;


		//////////
		// Grab our starting and ending points based on direction and orientation
		//////
			iiGrace_computeNodeLine_fivePoints(tsV1, tsV2, &v1, &v2, &v3, &v4, &v5, tlIsP1East, tlIsP2West);


		//////////
		// Compute our points
		//////
			vecs1		= iivvm_canvasVecBezier3(20, &v1, &v2, &v3);
			vecs2		= iivvm_canvasVecBezier3(20, &v5, &v4, &v3);
			recs		= (SGraceRect**)malloc(sizeof(SGraceRect) * 41);
			*tnCount	= 41;


		//////////
		// Combine them into a single SGraceRect array with color data
		//////
			lnWidth = 5;
			for (lnI = 0; lnI < 20 - 1; lnI++)
			{
				iBmp_drawArbitraryQuad(bmp, (s32)vecs1[lnI].x, (s32)vecs1[lnI].y, (s32)vecs1[lnI+1].x, (s32)vecs1[lnI+1].y, lnWidth, true, blackColor);
				iBmp_drawArbitraryQuad(bmp, (s32)vecs2[lnI].x, (s32)vecs2[lnI].y, (s32)vecs2[lnI+1].x, (s32)vecs2[lnI+1].y, lnWidth, true, blackColor);
			}
			--lnI;
			iBmp_drawArbitraryQuad(bmp, (s32)vecs1[lnI].x, (s32)vecs1[lnI].y, (s32)vecs2[lnI].x, (s32)vecs2[lnI].y, lnWidth, true, blackColor);


		//////////
		// Clean house
		//////
			free(vecs1);
			free(vecs2);
	}




	void iiGrace_renderNode(SObject* obj, SObjNode* objNodeFrom, s32 tnNodeFromNum, s32 tnNodeToNum)
	{
		iiGrace_computeNodeLine(obj->bmp, 1.0f, 1.0f);
	}




	void iGrace_renderObj_childrenAndSiblings(SObject* obj, RECT* rc, bool tlRenderChildren, bool tlRenderSiblings, f32 tfZ)
	{
		RECT		lrc, lrcClient;
		SObject*	objSib;


		logfunc(__FUNCTION__);
		//////////
		// Make sure there is render data
		//////
			if (!obj || !isVisible(obj) || !isEnabled(obj))
				return;


		//////////
		// Render any children
		//////
			if (tlRenderChildren && obj->firstChild)
				iGrace_renderObj_childrenAndSiblings(obj->firstChild, &lrcClient, true, true, tfZ + 0.01f);


		//////////
		// Render self
		//////
			iiGrace_renderObj(obj);


		//////////
		// Render any siblings
		//////
			if (tlRenderSiblings && obj->ll.next)
			{
				objSib = (SObject*)obj->ll.next;
				while (objSib)
				{
					// Render this sibling
					iGrace_renderObj_childrenAndSiblings(objSib, rc, true, false, tfZ);

					// Move to next sibling
					objSib = (SObject*)objSib->ll.next;
				}
			}
	}




	void iiGrace_renderObj(SObject* obj)
	{
		// Bind the texture for this quad
		glBindTexture(GL_TEXTURE_2D, obj->ogl.quad.mipmap);

		// Based on whether or not there's texture information, do the texture coords
		glBegin(GL_QUADS);

			glColor4f		(obj->ogl.quad.c[V1].r, obj->ogl.quad.c[V1].g, obj->ogl.quad.c[V1].b, obj->ogl.quad.c[V1].a);
			glTexCoord2d	(obj->ogl.quad.t[V1].s, obj->ogl.quad.t[V1].t);
			glNormal3f		(obj->ogl.quad.n[V1].x, obj->ogl.quad.n[V1].y, obj->ogl.quad.n[V1].z);
			glVertex3f		(obj->ogl.quad.v[V1].x, obj->ogl.quad.v[V1].y, obj->ogl.quad.v[V1].z);

			glColor4f		(obj->ogl.quad.c[V2].r, obj->ogl.quad.c[V2].g, obj->ogl.quad.c[V2].b, obj->ogl.quad.c[V2].a);
			glTexCoord2d	(obj->ogl.quad.t[V2].s, obj->ogl.quad.t[V2].t);
			glNormal3f		(obj->ogl.quad.n[V2].x, obj->ogl.quad.n[V2].y, obj->ogl.quad.n[V2].z);
			glVertex3f		(obj->ogl.quad.v[V2].x, obj->ogl.quad.v[V2].y, obj->ogl.quad.v[V2].z);

			glColor4f		(obj->ogl.quad.c[V3].r, obj->ogl.quad.c[V3].g, obj->ogl.quad.c[V3].b, obj->ogl.quad.c[V3].a);
			glTexCoord2d	(obj->ogl.quad.t[V3].s, obj->ogl.quad.t[V3].t);
			glNormal3f		(obj->ogl.quad.n[V3].x, obj->ogl.quad.n[V3].y, obj->ogl.quad.n[V3].z);
			glVertex3f		(obj->ogl.quad.v[V3].x, obj->ogl.quad.v[V3].y, obj->ogl.quad.v[V3].z);

			glColor4f		(obj->ogl.quad.c[V4].r, obj->ogl.quad.c[V4].g, obj->ogl.quad.c[V4].b, obj->ogl.quad.c[V4].a);
			glTexCoord2d	(obj->ogl.quad.t[V4].s, obj->ogl.quad.t[V4].t);
			glNormal3f		(obj->ogl.quad.n[V4].x, obj->ogl.quad.n[V4].y, obj->ogl.quad.n[V4].z);
			glVertex3f		(obj->ogl.quad.v[V4].x, obj->ogl.quad.v[V4].y, obj->ogl.quad.v[V4].z);

		glEnd();
	}




//////////
//
// Called to compute the midpoint, slope, and perpendicular slope of a vector line
//
//////
	void iiGrace_computeVecLine(SGraceVecLine* line)
	{
		// Midpoint = (x2-x1)/2, (y2-y1)/2
		line->mid.x		= (line->v1.x + line->v2.x) / 2.0f;
		line->mid.y		= (line->v1.y + line->v2.y) / 2.0f;
		line->mid.z		= (line->v1.z + line->v2.z) / 2.0f;

		// Compute our deltas
		line->delta.x	= line->v2.x - line->v1.x;
		line->delta.y	= line->v2.y - line->v1.y;
		line->delta.z	= line->v2.z - line->v1.z;

		// Length
		line->lengthXy	= (f32)sqrt(line->delta.x*line->delta.x + line->delta.y*line->delta.y);
		line->lengthXz	= (f32)sqrt(line->delta.x*line->delta.x + line->delta.z*line->delta.z);
		line->lengthYz	= (f32)sqrt(line->delta.y*line->delta.y + line->delta.z*line->delta.z);
		line->length	= (f32)sqrt(line->lengthXy*line->lengthXy + line->delta.z*line->delta.z);

		// Slope = rise over run
		line->mXy		= line->delta.y / ((line->delta.x == 0.0f) ? 0.000001f : line->delta.x);
		line->mXz		= line->delta.z / ((line->delta.x == 0.0f) ? 0.000001f : line->delta.x);
		line->mYz		= line->delta.z / ((line->delta.y == 0.0f) ? 0.000001f : line->delta.y);

		// Perpendicular slope = -1/m
		line->mpXy		= -1.0f / ((line->mXy == 0.0) ? 0.000001f : line->mXy);
		line->mpXz		= -1.0f / ((line->mXz == 0.0) ? 0.000001f : line->mXz);
		line->mpYz		= -1.0f / ((line->mYz == 0.0) ? 0.000001f : line->mYz);

		// Compute theta
		line->thetaXy	= (f32)atan2(line->delta.y, line->delta.x);
		line->thetaXz	= (f32)atan2(line->delta.z, line->delta.x);
		line->thetaYz	= (f32)atan2(line->delta.z, line->delta.y);
	}




	void iiGrace_copyAndComputeVecLine(SGraceVecLine* line, SGraceVec* p1, SGraceVec* p2)
	{
		// Copy
		memcpy(&line->v1, p1, sizeof(line->v1));
		memcpy(&line->v2, p2, sizeof(line->v2));

		// Compute
		iiGrace_computeVecLine(line);
	}




	SGraceVec** iivvm_canvasVecBezier3(s32 tnSegmentCount, SGraceVec* tsV1, SGraceVec* tsV2, SGraceVec* tsV3)
	{
		s32				lnSegment;
		f32				lfPercent, lfCosTheta1, lfSinTheta1, lfCosTheta2, lfSinTheta2;
		SGraceVec		v1, v2, pbez;
		SGraceVecLine	l1, l2;		// Static lines from bez->p1 to bez->p2, and bez->p2 to bez->p3
		SGraceVecLine	lmid;		// Dynamically computed line from l1 to l2 through segments
		SGraceVec*		vecs;


		// Allocate our return buffer
		vecs = (SXYF32*)malloc(tnSegmentCount * sizeof(SXYF32));
		memset(vecs, 0, tnSegmentCount * sizeof(SXYF32));


		//////////
		// Copy and compute our lines
		//////
			memset(&l1,   0, sizeof(l1));
			memset(&l2,   0, sizeof(l2));
			memset(&lmid, 0, sizeof(lmid));
			iiGrace_copyAndComputeVecLine(&l1, tsV1, tsV2, true);
			iiGrace_copyAndComputeVecLine(&l2, tsV2, tsV3, true);


		//////////
		// Compute our thetas for rapid use
		//////
			// L1
			lfCosTheta1		= (f32)cos(l1.thetaXy);
			lfSinTheta1		= (f32)sin(l1.thetaXy);
			// L2
			lfCosTheta2		= (f32)cos(l2.thetaXy);
			lfSinTheta2		= (f32)sin(l2.thetaXy);


		//////////
		// Now, iterate through the bezier building the points
		//////
			for (lnSegment = 0; lnSegment < tnSegmentCount; lnSegment++)
			{
				//////////
				// Get our percentage
				//////
					lfPercent = (f32)lnSegment / (f32)tnSegmentCount;


				//////////
				// Determine the two points for l1 and l2
				//////
					// P1, L1
					v1.x = tsV1->x + (lfPercent * l1.radius * lfCosTheta1);
					v1.y = tsV1->y + (lfPercent * l1.radius * lfSinTheta1);
					// P2, L2
					v2.x = tsV2->x + (lfPercent * l2.radius * lfCosTheta2);
					v2.y = tsV2->y + (lfPercent * l2.radius * lfSinTheta2);


				//////////
				// Construct the line between
				//////
					iiGrace_copyAndComputeVecLine(&lmid, &v1, &v2, true);


				//////////
				// Derive the position of this bezier point
				//////
					// PBEZ
					pbez.x = lmid.v1.x + (lfPercent * lmid.radius * (f32)cos(lmid.thetaXy));
					pbez.y = lmid.v1.y + (lfPercent * lmid.radius * (f32)sin(lmid.thetaXy));


				//////////
				// Store the point
				//////
					vecs[lnSegment].x = pbez.x;
					vecs[lnSegment].y = pbez.y;
			}

		return(vecs);
	}
