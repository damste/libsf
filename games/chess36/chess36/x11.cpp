//////////
//
// x11.cpp
//
/////
//
// Graphics primitives using the X11 Windows interface
//
//

#include "chess36.h"

extern bool			gbProgramIsRunning;



int initXWindow(XWindow* xw, int width, int height, int bpp, char *title, bool createbuffer)
{
	xw->display = XOpenDisplay(NULL);
	if (!xw->display)
		return -6;

	xw->width			= width;
	xw->height			= height;
	xw->screennum		= DefaultScreen(xw->display);
	xw->screenptr		= DefaultScreenOfDisplay(xw->display);
	xw->visual			= DefaultVisualOfScreen(xw->screenptr);
	xw->depth			= DefaultDepth(xw->display, xw->screennum);

	if (bpp != -1 && xw->depth != bpp)
		return -5;

	if (xw->depth != 24)
		return -4;		// Unhandled value, we only support 24-bit pixels

	xw->pixelsize	= 4;
	xw->window		= XCreateWindow(xw->display, RootWindowOfScreen(xw->screenptr), 0, 0, xw->width, xw->height, 0, xw->depth, InputOutput, xw->visual, 0, NULL);
	if (!xw->window)
		return -3;

	XStoreName	(xw->display, xw->window, title);
	XSelectInput(xw->display, xw->window, ExposureMask | KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | EnterWindowMask | LeaveWindowMask | PointerMotionMask | FocusChangeMask);
	XMapRaised	(xw->display, xw->window);

	xw->gc				= XCreateGC(xw->display, xw->window, 0, NULL);
	xw->screensize		= xw->height * xw->width * xw->pixelsize;
	xw->virtualscreen	= (u8*)malloc(xw->screensize);
	if (!xw->virtualscreen)
		return -2;

	xw->ximage = XCreateImage(xw->display, xw->visual, xw->depth, ZPixmap, 0, (char*)xw->virtualscreen, xw->width, xw->height, 32, xw->width * xw->pixelsize);
	if (!xw->ximage)
		return -1;

	// We're good
	return 0;
}

void drawContent(XWindow* xw)
{
	XPutImage(xw->display, xw->window, xw->gc, xw->ximage, 0, 0, 0, 0, xw->ximage->width, xw->ximage->height);
	XFlush(xw->display);
}

void onBreak(int arg)
{
	gbProgramIsRunning = false;
}

void clearKeyboardBuffer(XWindow* xw)
{
	XEvent ev;
	long key;

	while (XCheckWindowEvent(xw->display, xw->window, KeyPressMask, &ev))
		key = XLookupKeysym((XKeyEvent *)&ev, 0);
}
